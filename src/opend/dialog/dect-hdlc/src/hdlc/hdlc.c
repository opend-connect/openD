/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       hdlc.c
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      Implementation of the dialog specific WSM HDLC protocol.
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include "hdlc.h"

#include "debugOutput.h"
#include "queue.h"

#ifndef WSMDATA
#include "sw_timer.h"
#endif

#include <string.h>

/*===============================================================================================*/
/*                                          DEFINITIONS                                          */
/*===============================================================================================*/

#ifndef DEBUG_OUTPUT_ENABLE
#define DEBUG_OUTPUT_ENABLE DEBUG_HDLC
#endif

/** Defines the maximal length of the payload data. */
#define PACKET_DATA_LENGTH_MAX 1000U

/** Defines the delimiter. */
#define HDLC_FLAG 0x10

/* HDLC header length (DLE + length field). */
#define HDLC_HEADER_LENGTH 3U

/* HDLC control field length */
#define HDLC_CONTROL_FIELD_LENGTH 1U

/* HDLC CRC length. */
#define HDLC_CRC_LENGTH 1U
/* HDLC Payload header length (program id + task id). */
#define HDLC_PAYLOAD_HEADER_LENGTH 2U

/* HDLC sequence counter mask. */
#define HDLC_TX_SEQUENCE_MASK 0x07

/* HDLC limit for number of not acknowledged frames. */
#define HDLC_NO_ACK_LIMIT 6

/* Increments the given sequence number x by 1. */
#define HDLC_INCREMENT_SEQUENCE_NUM( x ) ( ( x + 1 ) & HDLC_TX_SEQUENCE_MASK )

/* Retransmission timeout in ms. */
#define HDLC_RETRANSMISSION_TIMER 800

/*===============================================================================================*/
/*                                   Structures & Enumerators                                    */
/*===============================================================================================*/

/**
 * Defines the states.
 * */
typedef enum {
  PARSE_STATE_FLAG = 0U,
  PARSE_STATE_LENGTH_MSB,
  PARSE_STATE_LENGTH_LSB,
  PARSE_STATE_CONTROL,
  PARSE_STATE_DATA,
  PARSE_STATE_CRC
} parseStates_t;

/**
 * Defines the connection state.
 **/
#ifndef WSMDATA
typedef enum {
  CONNECTION_STATE_UNCONNECTED = 0,
  CONNECTION_STATE_CONNECTING,
  CONNECTION_STATE_CONNECTED
} connectionStates_t;

/*
 * HDLC flow control for HDLC_supervisoryFrameControlField_t.
 * */
typedef enum {
  HDLC_FLOW_CTRL_RR = 0,
  HDLC_FLOW_CTRL_REJ = 1,
  HDLC_FLOW_CTRL_RNR = 2,
} hdlcControlSpecType_t;

/*
 * HDLC flow control for HDLC_unnumberedFrameControlField_t.
 * */
typedef enum {
  HDLC_FLOW_UNNMB_SABM = 0,  // Set Asynchronous Balanced Mode, i.e. ask peer to reset counters
} hdlcUnnumberedSpecType_t;

typedef struct {
  uint8_t rxSeq : 3;      // Next sequence expected from peer
  uint8_t pollFinal : 1;  // If set -> peer must be answered -
  hdlcControlSpecType_t ctrlSpec : 2;
  uint8_t supervisory : 1;  // Must be 0
  uint8_t infoControl : 1;  // Must be 1
} HDLC_supervisoryFrameControlField_t;

typedef struct {
  uint8_t modifier : 3;   // Not used
  uint8_t pollFinal : 1;  // If set -> peer must be answered -
  hdlcUnnumberedSpecType_t unNmbSpec : 2;
  uint8_t unnumbered : 1;   // Must be 1
  uint8_t infoControl : 1;  // Must be 1
} HDLC_unnumberedFrameControlField_t;
#endif

typedef struct {
  uint8_t rxSequence : 3;  /* Next sequence expected from peer */
  uint8_t pollFinal : 1;   /* If set -> peer must be answered */
  uint8_t txSequence : 3;  /* Sequence of the frame */
  uint8_t infoControl : 1; /* Must be 0 */
} HDLC_infoFrameControlField_t;

typedef union {
  uint8_t byte;
  union {
    HDLC_infoFrameControlField_t infoFrame;
#ifndef WSMDATA
    HDLC_supervisoryFrameControlField_t supervisoryFrame;
    HDLC_unnumberedFrameControlField_t unnumberedFrame;
#endif
  } fields;
} HDLC_controlField_t;

/**
 * HDLC packet structure.
 * */
typedef struct {
  uint16_t dataLength;
  uint16_t dataIndex;
  HDLC_controlField_t controlField;
  uint8_t data[PACKET_DATA_LENGTH_MAX];
  uint8_t crc;
} hdlcPacket_t;

typedef struct {
  parseStates_t parseState;
  uint8_t expectedRxSequence;
  uint8_t nextTxSequence;
#ifndef WSMDATA
  connectionStates_t connectionState;
  uint8_t expectedAcknowledgement;
  uint8_t unacknowledgedFrameCounter;
#endif
} hdlc_ctxt_t;


/*===============================================================================================*/
/*                                       Global variables                                        */
/*===============================================================================================*/

/** HDLC context. */
hdlc_ctxt_t hdlc_ctxt;

/** HDLC packet. */
hdlcPacket_t hdlcPacket;

#ifndef WSMDATA
/** Storage for not acknowledged HDLC frames */
uint8_t *unacknowledgedFrames[HDLC_TX_SEQUENCE_MASK + 1];

/* Queue for unsent frames. */
queue_ctx_t unsentFrameQueue;
#endif

/** Parsed packet function. */
static hdlc_parsedPacketFct_t _parsedPacketFct;
/** Allocate memory function. */
static hdlc_allocateMemoryFct_t _allocateMemoryFct;
/** Free memory function. */
static hdlc_freeMemoryFct_t _freeMemoryFct;
/** Serial send function. */
static hdlc_sendSerialFct_t _sendSerialFct;

/*===============================================================================================*/
/*                                          Prototypes                                           */
/*===============================================================================================*/

static uint8_t _calcCheckSum( uint8_t *data, uint16_t length );
static uint16_t _getFrameBufferLength( frameTypes_t frameType, uint16_t payloadLength );
static void _configureControlField( frameTypes_t frameType, HDLC_controlField_t *controlField,
                                    bool pollFinal );
static void _handleReceivedInfoFrame( void );
static void _handleReceivedFrame( void );


/**
 * @brief   HDLC frame creation.
 * @details This function creates a HDLC frame with the given payload.
 * @param   Type of the frame that should be created.
 * @param   *frameBuffer OUT Pointer to a memory section for the HDLC frame.
 * @param   frameBufferSize IN Buffer size of the frame buffer.
 * @param   taskId IN Task ID.
 * @param   *payloadData IN Pointer of the payload data.
 * @param   payloadLength IN Length of the playload data.
 * @param   pollFinal IN True if poll final flag should be set.
 * @retval  Status of the operation.
 *          1: Frame has been queued. Do not transmit via serial.
 *          0: Success
 *          <0:Error
 */
static int8_t _frameCreate( frameTypes_t frameType, uint8_t *frameBuffer, uint16_t frameBufferSize,
                            uint8_t taskId, uint8_t *payloadData, uint16_t payloadLength,
                            bool pollFinal );

#ifndef WSMDATA
/**
 * @brief Checks if a <= b < c.
 *
 * @param a Lower limit.
 * @param b Value that should be in range.
 * @param c Upper limit.
 *
 * @return True if a <= b < c.
 */
static bool _between( unsigned char a, unsigned int b, unsigned int c );

/**
 * @brief Checks for queued frames and transmit one if the conditions allow to do so.
 */
static void _sendQueuedFrame( void );

/**
 * @brief Some HDLC parameters should be reset in case a unnumbered frame is received.
 *
 * This functions resets all required parameter.
 */
static void _resetHdlc( void );

/***
 * @brief Validates the sequence number of a received frame and handles the acknowledgement.
 */
static void _validateAcknowledge( HDLC_controlField_t controlField );

/* Callback function to handle retransmissions in case a timer expires.*/
static void _retransmissionTimerCallback( void );

/* Retransmits not acknowledged frames. */
static void _retransmitFrames( void );

static void _sendFrame( frameTypes_t frameType, bool pollFinal );
static void _handleReceivedSupervisoryFrame( void );
static void _handleReceivedUnnumberedFrame( void );
#endif

/*===============================================================================================*/
/*                                           Functions */
/*===============================================================================================*/

/*-----------------------------------------------------------------------------------------------*/
/* _retransmissionTimerCallback() */
/*-----------------------------------------------------------------------------------------------*/
#ifndef WSMDATA
static void _retransmissionTimerCallback( void ) {
  _retransmitFrames( );
}
#endif

/*-----------------------------------------------------------------------------------------------*/
/* _retransmitFrames() */
/*-----------------------------------------------------------------------------------------------*/
#ifndef WSMDATA
static void _retransmitFrames( void ) {
  uint8_t firstUnacknowledgedIndex;
  uint8_t *frame;

  /*
   * SW timer does not have a stop function.
   * Therefore the code in this function should only be executed in case there are unacknowledged
   * frames.
   */
  if( hdlc_ctxt.unacknowledgedFrameCounter ) {

    if( CONNECTION_STATE_CONNECTED != hdlc_ctxt.connectionState ) {
      /* We need to setup a connection first. */
      _sendFrame( FRAME_TYPE_UNNUMBERED, true );
    } else {

      firstUnacknowledgedIndex = hdlc_ctxt.expectedAcknowledgement;

      for( uint8_t i = 0; i < hdlc_ctxt.unacknowledgedFrameCounter; i++ ) {

        HDLC_controlField_t *controlField;
        uint16_t frameLength;

        /* Get the control field */
        frame = unacknowledgedFrames[firstUnacknowledgedIndex];

        if( frame ) {
          controlField = (HDLC_controlField_t *) &frame[3];

          /* Check if the poll final flag has to be set. */
          if( ( i + 1 ) == hdlc_ctxt.unacknowledgedFrameCounter ) {
            /* Set the pollFinal flag.  */
            controlField->fields.infoFrame.pollFinal = true;
          } else {
            /* Reset the pollFinal flag. */
            /* Set the pollFinal flag.  */
            controlField->fields.infoFrame.pollFinal = true;
          }

          /* Refresh RX sequence. */
          controlField->fields.infoFrame.rxSequence = hdlc_ctxt.expectedRxSequence;

          frameLength = ( uint16_t )( ( frame[1] << 8 ) & 0xFF00 );
          frameLength = ( uint16_t )( frame[2] & 0x00FF );

          /* Recalculate the CRC. */
          frame[frameLength + HDLC_HEADER_LENGTH] = _calcCheckSum( &frame[3], frameLength );

          _sendSerialFct( frame, frameLength + HDLC_HEADER_LENGTH + HDLC_CRC_LENGTH );
          firstUnacknowledgedIndex = HDLC_INCREMENT_SEQUENCE_NUM( firstUnacknowledgedIndex );
        }
      }

      /* Restart retransmission timer. */
      sw_timer_start( HDLC_RETRANSMISSION_TIMER, _retransmissionTimerCallback );
    }
  }
}
#endif

/*-----------------------------------------------------------------------------------------------*/
/* _calcCheckSum() */
/*-----------------------------------------------------------------------------------------------*/
static uint8_t _calcCheckSum( uint8_t *data, uint16_t length ) {

  uint8_t checkSum = 0;

  for( uint16_t i = 0; i < length; i++ ) {
    checkSum += data[i];
  }

  return checkSum;
}

/*-----------------------------------------------------------------------------------------------*/
/* _getFrameBufferLength() */
/*-----------------------------------------------------------------------------------------------*/
static uint16_t _getFrameBufferLength( frameTypes_t frameType, uint16_t payloadLength ) {
  uint32_t calcLength = HDLC_HEADER_LENGTH + HDLC_CONTROL_FIELD_LENGTH + HDLC_CRC_LENGTH;

  if( FRAME_TYPE_INFO == frameType ) {
    /* Info frame types have program and task id and may contain payload. */
    calcLength += ( payloadLength + HDLC_PAYLOAD_HEADER_LENGTH );
  } else if( payloadLength != 0U ) {
    /* Supervisory and unnumbered frames can not contain payload.
       Therefore return 0 to indicate an error. */
    return 0;
  }

  if( calcLength > 0xFFFF ) {
    return 0;
  }

  return (uint16_t) calcLength;
}

/*-----------------------------------------------------------------------------------------------*/
/* _configureControlField() */
/*-----------------------------------------------------------------------------------------------*/
static void _configureControlField( frameTypes_t frameType, HDLC_controlField_t *controlField,
                                    bool pollFinal ) {
  switch( frameType ) {
    case FRAME_TYPE_INFO:
      controlField->fields.infoFrame.rxSequence = hdlc_ctxt.expectedRxSequence;
      controlField->fields.infoFrame.pollFinal = 1;  // Always 1 for info frames.
      controlField->fields.infoFrame.txSequence = hdlc_ctxt.nextTxSequence;
      controlField->fields.infoFrame.infoControl = 0U;  // Must be 0.
      hdlc_ctxt.nextTxSequence = HDLC_INCREMENT_SEQUENCE_NUM( hdlc_ctxt.nextTxSequence );
      break;
#ifndef WSMDATA
    case FRAME_TYPE_SUPERVISORY:
      controlField->fields.supervisoryFrame.rxSeq = hdlc_ctxt.expectedRxSequence;
      controlField->fields.supervisoryFrame.pollFinal = pollFinal;
      controlField->fields.supervisoryFrame.ctrlSpec = HDLC_FLOW_CTRL_RR;
      controlField->fields.supervisoryFrame.supervisory = 0;  // Supervisory frame
      controlField->fields.supervisoryFrame.infoControl = 1;
      break;
    case FRAME_TYPE_UNNUMBERED:
      controlField->fields.unnumberedFrame.modifier = 0;
      controlField->fields.unnumberedFrame.pollFinal = pollFinal;
      controlField->fields.unnumberedFrame.unNmbSpec = HDLC_FLOW_UNNMB_SABM;
      controlField->fields.unnumberedFrame.unnumbered = 1;
      controlField->fields.unnumberedFrame.infoControl = 1;
      break;
#endif
    default:
      break;
  }
}

#ifndef WSMDATA
/*-----------------------------------------------------------------------------------------------*/
/* _sendQueuedFrame() */
/*-----------------------------------------------------------------------------------------------*/
static void _sendQueuedFrame( void ) {

  if( ( CONNECTION_STATE_CONNECTED == hdlc_ctxt.connectionState ) &&
      /* Check if the do not exceed the limit of unacknowledged frames. */
      ( hdlc_ctxt.unacknowledgedFrameCounter < HDLC_NO_ACK_LIMIT ) ) {

    queue_dataElement_t *queuedFrame = queue_front( &unsentFrameQueue );

    if( queuedFrame ) {

      uint8_t *framePointer = (uint8_t *) queuedFrame->data;
      HDLC_controlField_t controlField;
      _configureControlField( FRAME_TYPE_INFO, &controlField, true );

      /* Set the control field */
      framePointer[3] = (uint8_t) controlField.byte;
      framePointer[( queuedFrame->size - 1 )] += framePointer[3];

      sw_timer_start( HDLC_RETRANSMISSION_TIMER, _retransmissionTimerCallback );
      hdlc_ctxt.unacknowledgedFrameCounter++;

      if( unacknowledgedFrames[controlField.fields.infoFrame.txSequence] != NULL ) {
        /* Should never happen, but in case it does this line prevents from memory leaks. */
        _freeMemoryFct( unacknowledgedFrames[controlField.fields.infoFrame.txSequence] );
      }
      unacknowledgedFrames[controlField.fields.infoFrame.txSequence] = queuedFrame->data;

      _sendSerialFct( framePointer, (uint16_t) queuedFrame->size );
      queue_pop( &unsentFrameQueue );
    }
  }
}
#endif

/*-----------------------------------------------------------------------------------------------*/
/* _resetHdlc() */
/*-----------------------------------------------------------------------------------------------*/
#ifndef WSMDATA
static void _resetHdlc( void ) {
  hdlc_ctxt.expectedRxSequence = 0x00;
  hdlc_ctxt.nextTxSequence = 0x00;
  hdlc_ctxt.connectionState = CONNECTION_STATE_UNCONNECTED;
  hdlc_ctxt.unacknowledgedFrameCounter = 0x00;
  hdlc_ctxt.expectedAcknowledgement = 0x00;
}
#endif

/*-----------------------------------------------------------------------------------------------*/
/* _between() */
/*-----------------------------------------------------------------------------------------------*/
#ifndef WSMDATA
static bool _between( unsigned char a, unsigned int b, unsigned int c ) {
  return ( ( ( a <= b ) && ( b < c ) ) || ( ( c < a ) && ( a <= b ) ) ||
           ( ( b < c ) && ( c < a ) ) );
}
#endif

/*-----------------------------------------------------------------------------------------------*/
/* _validateAcknowledge() */
/*-----------------------------------------------------------------------------------------------*/
#ifndef WSMDATA
static void _validateAcknowledge( HDLC_controlField_t controlField ) {

  while( _between(
      hdlc_ctxt.expectedAcknowledgement,
      ( controlField.fields.infoFrame.rxSequence + HDLC_TX_SEQUENCE_MASK ) & HDLC_TX_SEQUENCE_MASK,
      hdlc_ctxt.nextTxSequence ) ) {

    // Free acknowledged frames
    hdlc_ctxt.unacknowledgedFrameCounter--;

    if( unacknowledgedFrames[hdlc_ctxt.expectedAcknowledgement] ) {
      /* Free the acknowledged frame. */
      _freeMemoryFct( unacknowledgedFrames[hdlc_ctxt.expectedAcknowledgement] );
      unacknowledgedFrames[hdlc_ctxt.expectedAcknowledgement] = NULL;
    }

    if( hdlc_ctxt.unacknowledgedFrameCounter == 0 ) {
      /* Normally, the software timer should be stopped here,
         but the timer module does not support this.
         Therefore just do nothing. */
    }

    /* Increase the expected acknowledgement. */
    hdlc_ctxt.expectedAcknowledgement =
        HDLC_INCREMENT_SEQUENCE_NUM( hdlc_ctxt.expectedAcknowledgement );

    /* Handle queued frames. */
    _sendQueuedFrame( );
  }
}
#endif

/*-----------------------------------------------------------------------------------------------*/
/* _frameCreate() */
/*-----------------------------------------------------------------------------------------------*/
static int8_t _frameCreate( frameTypes_t frameType, uint8_t *frameBuffer, uint16_t frameBufferSize,
                            uint8_t taskId, uint8_t *payloadData, uint16_t payloadLength,
                            bool pollFinal ) {

  bool queueFrame = false;
  int8_t status = 0;
  HDLC_controlField_t controlField;
  uint16_t totalFrameLength = _getFrameBufferLength( frameType, payloadLength );
  uint16_t frameLength = totalFrameLength - 3U - HDLC_CRC_LENGTH;

  if( !frameBuffer && ( frameBufferSize < totalFrameLength ) ) {
    return -1;
  }

#ifndef WSMDATA
  if( ( FRAME_TYPE_INFO == frameType ) &&
      /* Check if HDLC is connected. */
      ( ( CONNECTION_STATE_CONNECTED != hdlc_ctxt.connectionState ) ||
        /* Check for the unacknowledged frame counter. */
        ( hdlc_ctxt.unacknowledgedFrameCounter > HDLC_NO_ACK_LIMIT ) ) ) {

    /* HDLC is not ready to transmit info frames. */
    queueFrame = true;
    status = 1;
  }
#endif

  /* Flage. */
  frameBuffer[0] = 0x10;

  /* Length */
  frameBuffer[1] = ( uint8_t )( ( frameLength & 0xFF00 ) >> 8 );
  frameBuffer[2] = ( uint8_t )( frameLength & 0x00FF );

  /* Configuration field is only set when the frame is not queued.
     For queued frames it must be done later (due to sequence number). */
  if( false == queueFrame ) {
    /* Configure the control field. */
    _configureControlField( frameType, &controlField, pollFinal );

    frameBuffer[3] = (uint8_t) controlField.byte;
  } else {
    /* Ensure that control field is 0 for queued frames, so that the checksum calculation is not
     * influenced. */
    frameBuffer[3] = 0;
  }


  if( FRAME_TYPE_INFO == frameType ) {

    /* Program Id */
    frameBuffer[4] = 0x00;

    /* Task Id */
    frameBuffer[5] = taskId;

    /* Payload */
    if( payloadLength ) {
      memcpy( &frameBuffer[6], payloadData, payloadLength );
    }
  }

  /* Checksum */
  frameBuffer[totalFrameLength - 1U] = _calcCheckSum( &frameBuffer[3], frameLength );

#ifndef WSMDATA
  if( FRAME_TYPE_INFO == frameType ) {
    if( false == queueFrame ) {
      sw_timer_start( HDLC_RETRANSMISSION_TIMER, _retransmissionTimerCallback );
      hdlc_ctxt.unacknowledgedFrameCounter++;
      if( unacknowledgedFrames[controlField.fields.infoFrame.txSequence] != NULL ) {
        /* Should never happen, but in case it does this line prevents from memory leaks. */
        _freeMemoryFct( unacknowledgedFrames[controlField.fields.infoFrame.txSequence] );
      }
      unacknowledgedFrames[controlField.fields.infoFrame.txSequence] = frameBuffer;
    } else {
      /* Frame should be queued. */
      queue_push( &unsentFrameQueue, (void *) frameBuffer, (size_t) frameBufferSize );
    }
  }
#endif

  return status;
}

/*-----------------------------------------------------------------------------------------------*/
/* _sendFrame() */
/*-----------------------------------------------------------------------------------------------*/
#ifndef WSMDATA
static void _sendFrame( frameTypes_t frameType, bool pollFinal ) {
  uint8_t *frame;
  uint16_t frameLength = _getFrameBufferLength( frameType, 0 );

  _allocateMemoryFct( &frame, frameLength );

  if( frame ) {
    _frameCreate( frameType, frame, frameLength, 0, NULL, 0, pollFinal );
    _sendSerialFct( frame, frameLength );
    _freeMemoryFct( frame );
  }
}
#endif

/*-----------------------------------------------------------------------------------------------*/
/* _handleReceivedInfoFrame() */
/*-----------------------------------------------------------------------------------------------*/
static void _handleReceivedInfoFrame( void ) {

#if WSMDATA
  if( _parsedPacketFct ) {
    _parsedPacketFct( hdlcPacket.data, hdlcPacket.dataLength );
  }
#else
  bool validateAndIndicate = false;

  if( hdlc_ctxt.connectionState == CONNECTION_STATE_CONNECTED ) {
    if( hdlcPacket.controlField.fields.infoFrame.txSequence == hdlc_ctxt.expectedRxSequence ) {
      /* Increase the expected sequence number. */
      hdlc_ctxt.expectedRxSequence = HDLC_INCREMENT_SEQUENCE_NUM( hdlc_ctxt.expectedRxSequence );
      validateAndIndicate = true;
    }


    if( hdlcPacket.controlField.fields.infoFrame.pollFinal == 1 ) {
      _sendFrame( FRAME_TYPE_SUPERVISORY, false );
    }
  } else {
    _sendFrame( FRAME_TYPE_UNNUMBERED, true );
    hdlc_ctxt.connectionState = CONNECTION_STATE_CONNECTING;
  }

  if( true == validateAndIndicate ) {
    /* Need to use a variable here instead of calling the function directly above to respect the
     * frame order of the old HDLC driver. */
    _validateAcknowledge( hdlcPacket.controlField );

    if( _parsedPacketFct ) {
      _parsedPacketFct( hdlcPacket.data, hdlcPacket.dataLength );
    }
  }
#endif
}

/*-----------------------------------------------------------------------------------------------*/
/* _handleReceivedSupervisoryFrame() */
/*-----------------------------------------------------------------------------------------------*/
#ifndef WSMDATA
static void _handleReceivedSupervisoryFrame( void ) {

  if( hdlc_ctxt.connectionState != CONNECTION_STATE_CONNECTED ) {
    _sendFrame( FRAME_TYPE_UNNUMBERED, true );
    hdlc_ctxt.connectionState = CONNECTION_STATE_CONNECTING;
  } else {
    _validateAcknowledge( hdlcPacket.controlField );
  }
}
#endif

/*-----------------------------------------------------------------------------------------------*/
/* _handleReceivedUnnumberedFrame() */
/*-----------------------------------------------------------------------------------------------*/
#ifndef WSMDATA
static void _handleReceivedUnnumberedFrame( void ) {

  if( hdlcPacket.controlField.fields.unnumberedFrame.pollFinal == 1 ) {
    _resetHdlc( );
    hdlc_ctxt.connectionState = CONNECTION_STATE_CONNECTED;
    _sendFrame( FRAME_TYPE_UNNUMBERED, false );
    /* Check for unsent frames and transmit them if needed. */
    _sendQueuedFrame( );
  } else {
    if( hdlc_ctxt.connectionState == CONNECTION_STATE_CONNECTING ) {
      _resetHdlc( );
      hdlc_ctxt.connectionState = CONNECTION_STATE_CONNECTED;
      /* Check for unsent frames and transmit them if needed. */
      _sendQueuedFrame( );
    }
  }
}
#endif

/*-----------------------------------------------------------------------------------------------*/
/* _handleReceivedFrame() */
/*-----------------------------------------------------------------------------------------------*/
static void _handleReceivedFrame( void ) {

  if( hdlcPacket.controlField.fields.infoFrame.infoControl == 0 ) {
    _handleReceivedInfoFrame( );
  }
#ifndef WSMDATA
  else if( hdlcPacket.controlField.fields.supervisoryFrame.supervisory == 0 ) {
    _handleReceivedSupervisoryFrame( );
  } else {
    _handleReceivedUnnumberedFrame( );
  }
#endif
}

/*-----------------------------------------------------------------------------------------------*/
/* hdlc_init() */
/*-----------------------------------------------------------------------------------------------*/
int8_t hdlc_init( hdlc_parsedPacketFct_t parsedPacketFct,
                  hdlc_allocateMemoryFct_t allocateMemoryFct, hdlc_freeMemoryFct_t freeMemoryFct,
                  hdlc_sendSerialFct_t sendSerialFct ) {

#if WSMDATA
  if( !parsedPacketFct ) {
    return -1;
  }
#else
  if( !parsedPacketFct || !allocateMemoryFct || !freeMemoryFct || !sendSerialFct ) {
    return -1;
  }
#endif

  _parsedPacketFct = parsedPacketFct;
  _allocateMemoryFct = allocateMemoryFct;
  _freeMemoryFct = freeMemoryFct;
  _sendSerialFct = sendSerialFct;

  /* Variable initialization. */
  hdlc_ctxt.expectedRxSequence = 0x00;
  hdlc_ctxt.nextTxSequence = 0x00;
  hdlc_ctxt.parseState = 0x00;
  hdlcPacket.dataLength = 0x00;
  hdlcPacket.dataIndex = 0x00;
  hdlcPacket.crc = 0x00;

#ifndef WSMDATA
  hdlc_ctxt.connectionState = CONNECTION_STATE_UNCONNECTED;
  hdlc_ctxt.unacknowledgedFrameCounter = 0x00;
  hdlc_ctxt.expectedAcknowledgement = 0x00;

  for( uint8_t i = 0; i < HDLC_TX_SEQUENCE_MASK; i++ ) {
    unacknowledgedFrames[i] = NULL;
  }

  queue_init( &unsentFrameQueue );

  hdlc_ctxt.connectionState = CONNECTION_STATE_CONNECTING;
  _sendFrame( FRAME_TYPE_UNNUMBERED, true );


  /* Default payload for info frame that is sent at startup. */
  uint8_t infoFrameData[] = {0x00, 0xFF};
  hdlc_infoFrameCreate( 0, infoFrameData, sizeof( infoFrameData ) );
#endif

  return 0;
}

/*-----------------------------------------------------------------------------------------------*/
/* hdlc_getInfoFrameBufferLength() */
/*-----------------------------------------------------------------------------------------------*/
uint16_t hdlc_getInfoFrameBufferLength( uint16_t payloadLength ) {

  return _getFrameBufferLength( FRAME_TYPE_INFO, payloadLength );
}

/*-----------------------------------------------------------------------------------------------*/
/* hdlc_infoFrameCreate() */
/*-----------------------------------------------------------------------------------------------*/
int8_t hdlc_infoFrameCreate( uint8_t taskId, uint8_t *payloadData, uint16_t payloadLength ) {
  int8_t status = -1;

  uint8_t *frame;
  uint16_t frameLength = _getFrameBufferLength( FRAME_TYPE_INFO, payloadLength );

  _allocateMemoryFct( &frame, frameLength );

  if( frame ) {
    status = _frameCreate( FRAME_TYPE_INFO, frame, frameLength, taskId, payloadData, payloadLength,
                           true );
    if( 0 == status ) {
      /* Transmit frame. */
      _sendSerialFct( frame, frameLength );
    } else if( 1 == status ) {
      /* Frame has been added to the queue.
         Indicate to the caller that everything is alright. */
      status = 0;
    } else {
      /* Something failed. Should not happen */
    }
  }

  return status;
}

/*-----------------------------------------------------------------------------------------------*/
/* hdlc_packetParseBytewise() */
/*-----------------------------------------------------------------------------------------------*/
void hdlc_packetParseBytewise( uint8_t *data ) {

  /* Check memory overrun. */
  if( hdlcPacket.dataIndex >= PACKET_DATA_LENGTH_MAX ) {
    if( HDLC_FLAG == *data ) {
      hdlc_ctxt.parseState = PARSE_STATE_LENGTH_MSB;
      return;
    }
  }

  switch( hdlc_ctxt.parseState ) {
    case PARSE_STATE_FLAG:
      /* Check for flag. */
      if( HDLC_FLAG == *data ) {
        hdlc_ctxt.parseState = PARSE_STATE_LENGTH_MSB;
      }
      break;

    case PARSE_STATE_LENGTH_MSB:
      /* Set length MSB. */
      hdlcPacket.dataLength = ( ( ( (uint16_t) *data ) << 8U ) & 0xFF00 );
      hdlc_ctxt.parseState = PARSE_STATE_LENGTH_LSB;
      break;

    case PARSE_STATE_LENGTH_LSB:
      /* Set length LSB. */
      hdlcPacket.dataLength |= ( ( (uint16_t) *data ) & 0x00FF );
      hdlc_ctxt.parseState = PARSE_STATE_CONTROL;

      break;

    case PARSE_STATE_CONTROL:
      /* Get the control field. */
      hdlcPacket.controlField.byte = *data;
      /* Calculate CRC. */
      hdlcPacket.crc = *data;

      /* Decrease the length by the control field length. */
      hdlcPacket.dataLength -= 1;

      /* Check if the data index has reached the data length. */
      if( hdlcPacket.dataIndex >= hdlcPacket.dataLength ) {
        /* There is no data payload. Proceed with CRC. */
        hdlc_ctxt.parseState = PARSE_STATE_CRC;
      } else {
        /* There is data payload to be received. */
        hdlc_ctxt.parseState = PARSE_STATE_DATA;
      }
      break;

    case PARSE_STATE_DATA:
      /*  Data. */
      hdlcPacket.data[hdlcPacket.dataIndex++] = *data;

      /* Calculate CRC. */
      hdlcPacket.crc += *data;

      /* Check if the data index has reached the data length. */
      if( hdlcPacket.dataIndex >= hdlcPacket.dataLength ) {
        hdlc_ctxt.parseState = PARSE_STATE_CRC;
      }
      break;

    case PARSE_STATE_CRC:
      /*  CRC. */
      if( hdlcPacket.crc == *data ) {
        _handleReceivedFrame( );
      }
      /* FALLTHRU */

    default:
      /*  Parser re-initialization. */
      hdlc_ctxt.parseState = PARSE_STATE_FLAG;
      hdlcPacket.dataIndex = 0x00;
      hdlcPacket.crc = 0x00;
      break;
  }

  return;
}
