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

#ifndef COLA_H
#define COLA_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <SOC/SC1445x/SC1445x.h>
#include <stdarg.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define COLA_IF_VERSION 9

#ifndef COLA_IF
  #define COLA_IF 0
#endif
#ifndef COLA_PIC
  #define COLA_PIC 0 // Position independant code.
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef void ColaIsrType(rsuint8 vector);

typedef enum RSENUMTAG(ColaHookIdType)
{
  CHI_NONE,
  CHI_TIMER_START, // RosHookTimerStart
  CHI_TIMER_STOP, // RosHookTimerStop
  CHI_TIMER_VALUE, // RosHookTimerValue
  CHI_TIMER_EXPIRED, // RosHookTimerExpired
  CHI_MAX
} RSENUM8(ColaHookIdType);

typedef void ColaHookType(void* p);

typedef struct
{
  // ### COLA_IF_VERSION 1 ###

  // Version.
  rsuint8 ColaIfVersion;
  RosTaskIdType ColaTaskId;
  rsuint16 _padding_;

  // Task.
  void (*RsShutdown)(RsShutDownReasonType Reason, RsShutDownActionType Action);
  void (*RosTaskTerminated)(RosTaskIdType TaskId);

  // Mails.
  RosMailType* (*RosMailAllocate)(RosTaskIdType Src, RosTaskIdType Dst, RosMailSizeType Size);
  void (*RosMailDeliver)(RosMailType* Mail);
  RosMailSizeType (*RosMailGetSize)(const RosMailType* Mail);
  RosTaskIdType (*RosMailGetSrc)(const RosMailType* Mail);
  RosTaskIdType (*RosMailGetDst)(const RosMailType* Mail);

  // Timers.
  void (*RosTimerStart)(RosTimerIdType TimerId, RsTimerTickType Value, const RosTimerConfigType* Config);
  void (*RosTimerStop)(RosTimerIdType TimerId);

  // Heap.
  void* (*RcHeapAllocEx)(RcHeapSizeType Size, RcHeapFlagsType Flags);
  void* (*RcHeapReallocEx)(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags);
  void (*RcHeapFreeEx)(void* Block, RcHeapFlagsType Flags);

  // Interrupts.
  RsStatusType (*SetIsr)(rsuint8 Vector, ColaIsrType* Isr);

  // Performance counter.
  RsPerformanceTickType (*RsReadPerformanceCounter)(void);
  RsPerformanceTimeType (*RsPerformanceTicks2Time)(RsPerformanceTickType PerformanceTicks);
  RsPerformanceTickType (*RsTime2PerformanceTicks)(RsPerformanceTimeType Time);

  // ### COLA_IF_VERSION 2 ###

  // System clock manager.
  void (*ScCpuRequest)(ScCpuUserIdType UserId, ScStateType State);

  // ### COLA_IF_VERSION 3 ###

  // NVS access.
  rsuint16 ColaNvsOffset;
  rsuint16 ColaNvsSize;
  void (*NvsRead)(rsuint16 Address, rsuint16 Size, rsuint8* Data);
  void (*NvsWrite)(rsuint16 Address, rsuint16 Size, rsuint8* Data);

  // ### COLA_IF_VERSION 4 ###

  // System clock manager.
  void (*ScPer10Request)(ScPer10UserIdType UserId, ScStateType State);
  void (*ScCp1Request)(ScCp1UserIdType UserId, ScStateType State);
  void (*ScXtalRequest)(ScXtalUserIdType UserId, ScStateType State);

  // ### COLA_IF_VERSION 5 ###

  // RtxEai log comment/printf
  void (*RtxEaiVaLogComment)(rsuint8 TaskId, const char* format, va_list argptr);
  void (*RtxEaiVaPrintf)(rsuint8 TaskId, const char* format, va_list argptr);
  void (*RtxEaiClearScreen)(rsuint8 TaskId);
  void (*RtxEaiScreenGotoxy)(rsuint8 TaskId, rsuint8 X,rsuint8 Y);

  // ### COLA_IF_VERSION 6 ###
  void* (*memcpy)(void* s1, const void* s2, size_t n);
  int (*vsnprintf)(char* s, size_t n, const char* format, va_list ap);

  // ### COLA_IF_VERSION 7 ###
  RsStatusType (*SetHook)(ColaHookIdType HookId, ColaHookType* Hook);

  // ### COLA_IF_VERSION 8 ###
  void (*RcHeapGetInfo)(RcHeapTotalType* Total, RcHeapTotalType* FreeBytes);
  void (*RcHeapGetStats)(RcHeapStatType* Stats);

  // ### COLA_IF_VERSION 9 ###
  rsuint32 *RsSecondCountPtr;
  volatile RsTimerTickType *RsTimerTickCountPtr;

  // ALWAYS add new functionality at the end.
  // REMEMBER to increment COLA_IF_VERSION.

} ColaIfType;

typedef RosTaskMailFunctionType* ColaInitFunctionType(const ColaIfType* const If);

#if (COLA_PIC == 1)
typedef struct
{
  rsuint8 ColaIfVersion;
  rsuint8 _padding_[3];
  rsuint8* GotStart;
  rsuint8* GotEnd;
} ColaPicType;
#endif

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

extern const ColaIfType* ColaIf;
extern RosTaskMailFunctionType* ColaMailHandler;
extern rsuint16 ColaNvsOffset;
extern rsuint16 ColaNvsSize;

/****************************************************************************
*                             Function prototypes
****************************************************************************/

void NvsRead(rsuint16 Address, rsuint16 Size, rsuint8* Data);
void NvsWrite(rsuint16 Address, rsuint16 Size, rsuint8* Data);

RsStatusType SetIsr(rsuint8 Vector, ColaIsrType* Isr);
RsStatusType SetHook(ColaHookIdType HookId, ColaHookType* Hook);

RsStatusType ColaMailRouting(const RosMailType* Mail);

RsStatusType SetTime(rsuint32 Time);
rsuint32 GetTime(void);
rsuint32 GetTimerTickCount(void);

RS_END_EXTERN_C

#endif

// End of file.

