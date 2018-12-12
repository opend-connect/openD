/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
#define MAX_PACKET_LENGTH 4000
#define MIN_PACKET_LENGTH 1   // Control frames have length 1
#define BUSM_FLOW_FINAL         0x08
#define BUSM_FLOW_RX_SEQ_MASK   0x07
#define BUSM_FLOW_TX_SEQ_MASK   0x70
#define BUSM_FLOW_CONTROL_FRAME 0x80
#define BUSM_FLOW_CONTROL_MASK  0x70
#define BUSM_FLOW_CONTROL_SHIFT 4

typedef enum
{
  BUSM_UNLOCKED,
  BUSM_LOCK_PENDING,
  BUSM_LOCKED
}ENUM8(eBusmState);

typedef enum
{
  INFORMATION_FRAME,
  SUPERVISORY_FRAME,
  UNNUMBERED_FRAME,
  MAX_FRAME
} ENUM8(eFrameTypeEnum);

typedef enum
{
  BUSM_FLOW_CTRL_RR  = 0 ,
  BUSM_FLOW_CTRL_REJ = 1 ,
  BUSM_FLOW_CTRL_RNR = 2 ,
} ENUM8(BusmCtrlSpecType);

typedef enum
{
  BUSM_FLOW_UNNMB_SABM = 0,  // Set Asynchronous Balanced Mode, i.e. ask peer to reset counters
} ENUM8(BusmUnNmbSpecType);

typedef struct
{
  uint8 RxSeq       : 3; // Next sequence expected from peer
  uint8 PollFinal   : 1; // If set -> peer must be answered
  uint8 TxSeq       : 3; // Sequence of this frame
  uint8 InfoControl : 1; // Must be 0
} BUSM_InfoFrameType;

typedef struct
{
  uint8 RxSeq               : 3; // Next sequence expected from peer
  uint8 PollFinal           : 1; // If set -> peer must be answered -
  BusmCtrlSpecType CtrlSpec : 2; 
  uint8 Supervisory         : 1; // Must be 0
  uint8 InfoControl         : 1; // Must be 1
} BUSM_SuperVisoryControlFrameType;

typedef struct
{
  uint8 Modifier                : 3; // Not used
  uint8 PollFinal               : 1; // If set -> peer must be answered - 
  BusmUnNmbSpecType UnNmbSpec   : 2;
  uint8 Unnumbered              : 1; // Must be 1
  uint8 InfoControl             : 1; // Must be 1
} BUSM_UnnumberedControlFrameType;

// Types for length and sequence fields in buffer
typedef uint16 BUSM_PacketLengthType;
typedef uint8 BUSM_SequenceNrType;
typedef uint8 BUSM_DleType;

// Type for paylaod header
typedef struct 
{
  uint8 uProgId;
  uint8 uTaskId;
} BUSM_PayloadHeaderType;

// Buffer header, a mail in the buffer is organized as: BUSM_BufferHeaderType - Mail - BUSM_TailMarkerType
typedef struct
{
  //BUSM_PacketLengthType length; // length filtered out in RSX
  BUSM_SequenceNrType uControl;
  BUSM_PayloadHeaderType payloadHead;
} BUSM_BufferHeaderType;


typedef struct
{
  BUSM_DleType Dle;
  uint8 uLengthMSB;
  uint8 uLengthLSB;
  BUSM_InfoFrameType uControl;
  BUSM_PayloadHeaderType payloadHead;
  uint8 payloadTail[1];  // Equals zero length package with 1 CRC byte
} __attribute__((packed)) BUSM_FrameType;

#define BUSM_HDLC_SEQ_MOD 0x07
#define BUSM_MAX_OUTSTANDING_FRAMES 0x06
#define BUSM_MAX_FRAMES_BEFORE_FINAL_FLAG 0x03

//#ifndef HAVE_STRUCT_TIMESPEC
//#define HAVE_STRUCT_TIMESPEC 1
typedef struct  {
        long tv_sec;
        long tv_nsec;
}timespec;
//#endif /* HAVE_STRUCT_TIMESPEC */

typedef struct 
{
  uint8   bExpectedRxSeq; 
  uint8   bNextTxSeq;
  uint8   bTxNoAckCnt;
  uint8   bExpectedAck;
  timespec tNoAckNowledge;
  eBusmState eHdlcState;
} sHdlcControlType;

#define NO_ACKNOWLEDGE_TIMEOUT 0.2 //200 ms


typedef struct 
{
  int  iTaskId;
  int  iLength;
  void *Next;
  uint8 Data[1]; // variable length
} sUnsentInfoframes;

// Queue stuff.
struct QueueStorage {
  struct QueueStorage *Next;
  void *Data;
};

typedef struct {
  struct QueueStorage *First,*Last;
} QueueRecord;

typedef struct {
  uint8 bLength;
  uint8 bData[1];
} QueueElement;


/****************************************************************************
*                    Function prototypes/external definitions
****************************************************************************/
extern void bus232_ResetHDLCprotocol(void);
extern void bus232_SendPacketToUnit(int iTaskId, int iLength, unsigned char *bInputDataPtr);
extern void sendmail_ReceivePacket(uint16 Length, uint8 *bDataPtr);
uint8 InitRs232(int Port, int BaudRate);
//static void bus232_RetransmitFrame(BUSM_FrameType *bInputDataPtr, uint8 boolPollFinal);
//static void bus232_SendUnnumberedFrame(int iTaskId, uint8 boolPollFinal);
//static uint8 Between(unsigned char a, unsigned int b, unsigned int c);
//static uint8 RsxSwpCheckReceivedFrame(uint8 *RxFrame);


