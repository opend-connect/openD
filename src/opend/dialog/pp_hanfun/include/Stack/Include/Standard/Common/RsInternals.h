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

#ifndef RS_INTERNALS_H
#define RS_INTERNALS_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Core/ROS/RosInternals.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#if (RS_PROTECTION == RSPT_NONE)
  #if (RS_RTOS_ID != RSTS_NONE)
    !error Heap protection needed, build with CB_PROTECTION=mutex.
  #endif
  #define RCH_SAVED
  #define RCH_LOCK
  #define RCH_UNLOCK
#endif
#if (RS_PROTECTION == RSPT_MUTEX)
  #define RCH_SAVED
  #define RCH_LOCK fosMutexObtain(RCH_MUTEX, FOS_TRUE, 0)
  #define RCH_UNLOCK fosMutexRelease(RCH_MUTEX)
#endif
#if (RS_PROTECTION == RSPT_INTERRUPT)
  #define RCH_SAVED RsIntStatusType saved;
  #define RCH_LOCK saved = RsDisableInterrupts()
  #define RCH_UNLOCK RsEnableInterrupts(saved)
#endif

#define RS_LOG_STR_CHARS 0x400

#ifdef RS_LOG_HWIS
  #define RSLOGHWIBEGIN(vector) RsLogHwiBegin(vector)
  #define RSLOGHWIEND(vector) RsLogHwiEnd(vector)
#else
  #define RSLOGHWIBEGIN(vector)
  #define RSLOGHWIEND(vector)
#endif

#ifdef RS_LOG_SWITCHES
  #define RSLOGFIRSTSWITCH(task) RsLogFirstSwitch(task)
  #define RSLOGSWITCH1(task) RsLogSwitch1(task)
  #define RSLOGSWITCH2(task) RsLogSwitch2(task)
  #define RSLOGPREHWI(task) RsLogPreHwi(task)
  #define RSLOGPOSTHWI(task) RsLogPostHwi(task)
#else
  #define RSLOGFIRSTSWITCH(task)
  #define RSLOGSWITCH1(task)
  #define RSLOGSWITCH2(task)
  #define RSLOGPREHWI(task)
  #define RSLOGPOSTHWI(task)
#endif

#ifdef RS_LOG_EI_DI
  #define RSLOGINTDI(task,level) RsLogIntDi(task,level)
  #define RSLOGINTEI(task,level) RsLogIntEi(task,level)
  #define RSLOGEXTDI(thd,level) RsLogExtDi(thd,level)
  #define RSLOGEXTEI(thd,level) RsLogExtEi(thd,level)
  #define RSLOGEXTWAITEXT(threadid,extthreadid) RsLogExtWaitExt(threadid,extthreadid)
  #define RSLOGEXTWAITINT(threadid,task) RsLogExtWaitInt(threadid,task)
#else
  #define RSLOGINTDI(task,level)
  #define RSLOGINTEI(task,level)
  #define RSLOGEXTDI(thd,level)
  #define RSLOGEXTEI(thd,level)
  #define RSLOGEXTWAITEXT(threadid,extthreadid)
  #define RSLOGEXTWAITINT(threadid,task)
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
void RsSegInit(void);
void RsLocksInit(void);
void RsErrorInit(void);

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
#ifdef RC_HEAP_H
  #if (RC_HEAP_IMPLEMENTATION == RHI_USER)
    void RsHeapInit(void);
    rsbool RsHeapCheck(void);
    void* RsHeapAlloc(RcHeapSizeType Size);
    void* RsHeapAllocZ(RcHeapSizeType Size);
    void RsHeapFree(void* Block);
    RcHeapSizeType RsHeapGetBlockSize(void* Block);
    rsbool RsHeapBlockValid(void* Block);
  #else
    #define RsHeapInit RcHeapInit
    #define RsHeapCheck RcHeapCheck
    #define RsHeapAllocZ RcHeapAllocZ
    #define RsHeapAlloc RcHeapAlloc
    #define RsHeapFree RcHeapFree
    #define RsHeapGetBlockSize RcHeapGetBlockSize
    #define RsHeapBlockValid RcHeapBlockValid
    #define RsHeapSetRa RcHeapSetRa
  #endif
#endif

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
void RsExit(void);
void RsRunStartup(void);
void RsRunExit(void);
void RsIntVectorFixup(void);

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
void RsOds(const char* format, ...);
void RsLog(const char* str);
void RsLogSave(void);

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
void RsHwiDispatch(rsuint8 vector);

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
#ifdef RS_LOG_HWIS
void RsLogHwiBegin(rsuint8 vector);
void RsLogHwiEnd(rsuint8 vector);
#endif
#ifdef RS_LOG_SWITCHES
void RsLogFirstSwitch(fosTask* task);
void RsLogSwitch1(fosTask* task);
void RsLogSwitch2(fosTask* task);
void RsLogPreHwi(fosTask* task);
void RsLogPostHwi(fosTask* task);
#endif
#ifdef RS_LOG_EI_DI
void RsLogIntDi(fosTask* task, LONG Level);
void RsLogIntEi(fosTask* task, LONG Level);
void RsLogExtDi(ULONG ThreadId, LONG Level);
void RsLogExtEi(ULONG ThreadId, LONG Level);
void RsLogExtWaitExt(ULONG ThreadId, ULONG ExtThreadId);
void RsLogExtWaitInt(ULONG ThreadId, fosTask* task);
#endif
#ifdef RS_LOG_READYLIST
void RsDumpReadyList(void);
void RsLogReadyListPush(fosTask* task);
void RsLogReadyListPop(u8 priority, fosTask* task);
void RsLogReadyListDelete(fosTask* task);
#endif

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
void RsITimersInit(void);
void RsITimersExec(rsuint16 ElapsedTicks);

RS_END_EXTERN_C

#endif

// End of file.

