/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       HdlcHost.c
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     Mario Behringer <mario.behringer@stackforce.de>
 * @brief      Abstraction of the dialog specific CMVDECT HDLC protocol.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <Core/RtxCore.h>

#include "HostUtil.h"
#include "hdlc.h"
#include "primitive_debug.h"
#include "opend_ll_serial.h"
#include "sw_timer.h"

#include "lptim.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


/****************************************************************************
 *                     Definitions
 ****************************************************************************/
/* Set the Maximum value of the counter */
#define Period               (uint32_t) 65535

/* Set the Timeout value */
#define Timeout              (uint32_t) (18500 - 1)

/****************************************************************************
 *                     Enumerations/Type definitions/Structs
 ****************************************************************************/

/****************************************************************************
 *                     Variable declarations
 ****************************************************************************/

/****************************************************************************
 *                               Global Vars
 ****************************************************************************/

/****************************************************************************
 *                      Function Prototypes
 ****************************************************************************/

/*---------------------------------------------------------------------------*/
/* _parsedPacketFct */
/*---------------------------------------------------------------------------*/
void _parsedPacketFct( uint8_t *data, uint16_t len ) {
  // printf("RX Data:");
  // for (int i = 0; i < len; ++i) {
  //   printf("%x", data[i]);
  // }
  // printf("\n");
  LocalMainAppTask( (RosMailType *) &data[2] );
  // print_incoming_msg( (const RosMailType *) &data[2] );
  return;
}

/*---------------------------------------------------------------------------*/
/* _allocateMemory */
/*---------------------------------------------------------------------------*/
void _allocateMemory( uint8_t **data, uint16_t length ) {

  *data = malloc( length );
}

/*---------------------------------------------------------------------------*/
/* _freeMemory */
/*---------------------------------------------------------------------------*/
void _freeMemory( uint8_t *data ) {
  free( data );
}

/*---------------------------------------------------------------------------*/
/* hdlc_hostInit */
/*---------------------------------------------------------------------------*/
int8_t _sendSerialFct( uint8_t *data, uint16_t length ) {
  return openD_ll_serial_send( data, length );

}

/*---------------------------------------------------------------------------*/
/* timerTick */
/*---------------------------------------------------------------------------*/
static void _hw_timer_timeNotify( uint16_t elapsedTime )
{
  sw_timer_tick( 500 );

}

/*---------------------------------------------------------------------------*/
/* hdlc_hostInit */
/*---------------------------------------------------------------------------*/
int hdlc_hostInit( void ) {
  int8_t returnStatus;

  returnStatus = hdlc_init( &_parsedPacketFct, &_allocateMemory, &_freeMemory, &_sendSerialFct );

  lp_timer_init( &_hw_timer_timeNotify );
  lp_timer_start(Period, Timeout);

  return returnStatus;
}

/*---------------------------------------------------------------------------*/
/* hdlc_hostSend */
/*---------------------------------------------------------------------------*/
void hdlc_hostSend( uint8_t iTaskId, uint8_t *bInputDataPtr, uint16_t iLength ) {

  // printf("TX Data:");
  // for(int i = 0; i < iLength; ++i)
  // {
  //   printf("%x", bInputDataPtr[i]);
  // }
  // printf("\n");

  hdlc_infoFrameCreate(iTaskId, bInputDataPtr, iLength);
  // printf("Done.\n");
}
