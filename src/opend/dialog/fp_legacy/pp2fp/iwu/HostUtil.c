/*
 * Copyright (c) by RTX A/S, Denmark
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of RTX A/S nor the names of its contributors
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
*                               Include files
****************************************************************************/
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include <Core/RtxCore.h>
#include <ProjCfg.h>
#include <PortDef.h>
#include <Ros/RosCfg.h>
#include <RtxEai/RtxEai.h>

#include "HostUtil.h"
#include "DynTim.h"

#include <Phoenix/Api/Api.h>
#if RC_HEAP_IMPLEMENTATION == RHI_USER
#include "malloc.h"
#include "stdlib.h"
#endif

#ifdef __linux__
#include "HdlcHost.h"
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/
rsuint16 ColaNvsOffset = 0xF00;
rsuint16 ColaNvsSize = 0x100;

// static rsuint8   bMailArr[100];
// static RosTaskIdType   bTaskId;
// static RosMailSizeType w16Size;
RegSimType RegSim;
//CvmConOptions
extern void HandleCvmConOptions(const RosMailType* MailPtr);
extern rsbool CvmConOptionsHelpState;

// variables needed for timer
uint32_t timer_tmout=0;
uint8_t TimerThreadRunning;
/****************************************************************************
*                            Function declarations
****************************************************************************/
extern void rsx_InitTask(rsuint32 iTaskId, char *szTaskName, rsuint32 iKeyPrimitive, TaskWindowPtr FunkPtr);
extern void rsx_SendMail(rsuint32 iTaskId, rsuint32 iLength, rsuint8 *bDataPtr);
extern void rsx_SendMailP1(rsuint32 iTaskId, rsuint16 Primitive, rsuint8 bParm1);
extern void rsx_SendMailP2(rsuint32 iTaskId, rsuint16 Primitive, rsuint8 bParm1, rsuint8 bParm2);
extern void ProjectPrintHelpText(void);

/****************************************************************************
*                            Function implementations
****************************************************************************/
void RsError(RsErrorIdType Error, RsErrorInfoType Info) {}
void RcHeapFreeEx(void* Block, RcHeapFlagsType Flags) { free(Block); }

void MyThreadTimerFunction(void);

/****************************************************************************
* Name   :
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
void RosTimerStop(RosTimerIdType TimerId)
{
  DynMmiStopTimer(TimerId);
}

/****************************************************************************
* Name   :
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
void RosTimerStart(RosTimerIdType TimerId, RsTimerTickType Value, const RosTimerConfigType* Config)
{
  DynMmiCreateTimer(TimerId);
  DynMmiStartTimer (TimerId, Value);
}
#ifdef NATALIE_V11
#ifdef __linux__
RosMailType* RosMailAllocate(RosTaskIdType Src, RosTaskIdType Dst, RosMailSizeType Size)
{
	unsigned char *bConPtr;
	bConPtr = (unsigned char *)malloc(Size+4);//1: uProgramId, 1: uTaskId, 2: u16Size
	if(!bConPtr){
		printf("Inside %s MALLOC FAILED  !!!!!!!!!!!!!!!!! \n\n\n\n", __FUNCTION__);
		while(1);
	}
	*bConPtr = Src;
	*(bConPtr+1) = Dst;
	*(unsigned short*)(bConPtr+2) = Size;
//	printf("%s: bConPtr+4 = 0x%x \n", __FUNCTION__,  bConPtr+4);
	return((RosMailType*)(bConPtr+4));
}

void RosMailDeliver(RosMailType* Mail)
{
	unsigned char *bConPtr=(unsigned char *)Mail-4;
	unsigned short ConLength = *(unsigned short*)(bConPtr+2);
#if 0
	unsigned char  ConTask = *(bConPtr+1);
	int i;
	printf("\n BUSM_DeliverMail (0x%02X) Size(%d): ", ConTask, ConLength);
	for(i=0;i<ConLength;i++){
		printf("%X ", ((unsigned char *)Mail)[i]);
	}
	printf("\n ");
#endif
        hdlc_hostSend(*(bConPtr + 1), bConPtr + 4, ConLength);
        // printf("bConPtr = 0x%x \n", bConPtr);
	if (bConPtr) {
		free(bConPtr);
		bConPtr = NULL;
	}
}

void RosMailFree(RosMailType* Mail)
{
		unsigned char *bConPtr=(unsigned char *)Mail-4;
		free(bConPtr);
}
#else // use REPS on Windows
#include "../Lib/include/IRepsClient.h"
extern uint32 RepsSendPacket( uint8 TaskId, uint8 *Data, uint16 TxBufferLength);
/****************************************************************************
* Name   : RosMailAllocate
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
RosMailType* RosMailAllocate(RosTaskIdType Src, RosTaskIdType Dst, RosMailSizeType Size)
{
	unsigned char *bConPtr;
	bConPtr = (unsigned char *)malloc(Size+4);//1: uProgramId, 1: uTaskId, 2: u16Size
	if(!bConPtr){
		printf("Inside %s MALLOC FAILED  !!!!!!!!!!!!!!!!! \n\n\n\n", __FUNCTION__);
		while(1);
	}
	*bConPtr = Src;
	*(bConPtr+1) = Dst;
	*(unsigned short*)(bConPtr+2) = Size;
    //printf("%s: bConPtr+4 = 0x%x \n", __FUNCTION__,  bConPtr+4);
	return((RosMailType*)(bConPtr+4));
}

/****************************************************************************
* Name   : RosMailDeliver
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
void RosMailDeliver(RosMailType* Mail)
{
	unsigned char *bConPtr=(unsigned char *)Mail-4;
	unsigned short ConLength = *(unsigned short*)(bConPtr+2);
#if 0
	unsigned char  ConTask = *(bConPtr+1);
	int i;
	printf("\n BUSM_DeliverMail: ");
	for(i=0;i<ConLength;i++){
		printf("%X ", ((unsigned char *)Mail)[i]);
	}
	printf("\n ");
#endif

	print_outgoing_msg(Mail);
	RepsSendPacket(*(bConPtr+1), bConPtr+4, ConLength+2);
	//	printf("bConPtr = 0x%x \n", bConPtr);
	free(bConPtr);
}
/****************************************************************************
* Name   : RosMailFree
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
void RosMailFree(RosMailType* Mail)
{
		unsigned char *bConPtr=(unsigned char *)Mail-4;
#if 0
		int i;
		unsigned char  ConTask = *(bConPtr+1);
		unsigned short ConLength = *(unsigned short*)(bConPtr+2);
		printf("\n RosMailFree: ");
		for(i=0;i<ConLength;i++){
			printf("%X ", ((unsigned char *)Mail)[i]);
		}
		printf("\n ");
		printf("bConPtr = 0x%x \n", bConPtr);
#endif
		free(bConPtr);
}
#endif // __linux__
#else // !NATALIE_V11
/****************************************************************************
* Name   : RosMailAllocate
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
RosMailType* RosMailAllocate(RosTaskIdType Src, RosTaskIdType Dst, RosMailSizeType Size)
{
   w16Size = Size;
   bTaskId = Dst;
   return (RosMailType*) bMailArr;
}

/****************************************************************************
* Name   : RosMailDeliver
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
void RosMailDeliver(RosMailType* Mail)
{
   rsx_SendMail(bTaskId, w16Size, bMailArr);
}
#endif // NATALIE_V11
/****************************************************************************
* Name   : PrintHelpText
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
void PrintHelpTextProdtest(void)
{
  {
	Printf("------------------------------------------------------------\n\n");
  }
}


/****************************************************************************
* Name   :
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
void LocalMainAppTaskInit(void)
{
#ifdef NATALIE_V11
	Printf("Application Console (press: F1 for help / F1 twice for Extended CvmCon Prodtest Options)");
#else
	rsx_InitTask(API_TASK, "Application Console (press: F1 for help / F1 twice for Extended CvmCon Prodtest Options)", KEY_MESSAGE, (TaskWindowPtr)LocalMainAppTask);
#endif
  rsx_StartTimer(1, API_TASK, TIMEOUT, 0 );

  Printf("Ready.\n");

  { // initialise ColaTask
	typedef struct
    {
      RosPrimitiveType Primitive; /*!< Mail identifier. */
    } RosMailEmptyType;
#ifdef NATALIE_V11
    {
      RosMailEmptyType* pMail = (RosMailEmptyType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailEmptyType));
      pMail->Primitive = INITTASK;
      ColaTask((RosMailType*)pMail);
      HandleCvmConOptions((RosMailType*)pMail);
	    RosMailFree((RosMailType* )pMail);
    }
#else
    {
      RosMailEmptyType* pMail = (RosMailEmptyType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailEmptyType));
      pMail->Primitive = INITTASK;
      ColaTask((RosMailType*)pMail);
    }
    {
      RosMailEmptyType* pMail = (RosMailEmptyType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailEmptyType));
      pMail->Primitive = INITTASK;
      HandleCvmConOptions((RosMailType*)pMail);
    }
#endif
  }
}

/****************************************************************************
* Name   :
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  :
*****************************************************************************/
void LocalMainAppTask(RosMailType *MailPtr)
{

  if(TIMEOUT == MailPtr->Primitive) {
      //Printf("RX: LOCAL_TIMEOUT (internal pc hostapp timer)\n");
      DynMmiTimerTick();
      rsx_StartTimer(1, API_TASK, TIMEOUT, 0 );
  }

  HandleCvmConOptions(MailPtr);

  ColaTask(MailPtr);

}

uint8_t dialogHost_init( void )
{
	pthread_t hTimerThread;
	TimerThreadRunning = 1;
	// Create the timer thread to begin execution on its own.
	if ( pthread_create( &hTimerThread, NULL, (void *)&MyThreadTimerFunction, NULL)) {
		printf("hTimerThread thread creation failed\n");
		return 1;
	}
	pthread_detach(hTimerThread);


	return 0;
}

void dialogHost_deInit( void )
{
	TimerThreadRunning = 0;
}

/****************************************************************************
* Name   : rsx_StartTimer
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  : Sets timer to send a TIMEOUT event every Time ticks
*****************************************************************************/
void rsx_StartTimer(unsigned long Time, uint16_t Task, uint16_t Primitive, uint16_t TimerId){
	timer_tmout=Time;
}
/****************************************************************************
* Name   : rsx_StopTimer
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  : Stops timer from sending TIMEOUT events
*****************************************************************************/
void rsx_StopTimer(uint16_t TimerId){
	timer_tmout=0;
}
/****************************************************************************
* Name   : MyThreadTimerFunction
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  : Thread implementing timer functionality
*****************************************************************************/
void MyThreadTimerFunction( void )
{
	RosMailEmptyType* pMail;
	while(TimerThreadRunning){
		sleep(4);
		if(timer_tmout){
#if 1
				pMail = (RosMailEmptyType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailEmptyType));
				pMail->Primitive = TIMEOUT;
				LocalMainAppTask((RosMailType*)pMail);
				RosMailFree((RosMailType*)pMail);
#else
			if(timer_cnt<timer_tmout)
				timer_cnt++;
			else{
				timer_cnt=0;
				pMail = (RosMailEmptyType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailEmptyType));
				pMail->Primitive = TIMEOUT;
				LocalMainAppTask((RosMailType*)pMail);
				RosMailFree((RosMailType*)pMail);
			}
#endif
		}

	}

	pthread_exit(0);
}
