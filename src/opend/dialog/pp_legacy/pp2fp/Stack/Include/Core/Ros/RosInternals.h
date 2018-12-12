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

#ifndef ROS_INTERNALS_H
#define ROS_INTERNALS_H

/** \cond internal */

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

// Mail flags.
#define RMF_QUEUED  0x01
#define RMF_TIMEOUT 0x02
#define RMF_DFC     0x04

// Mail tail check.
#ifndef ROS_TAIL_CHECK_SIZE
  #define ROS_TAIL_CHECK_SIZE 3
#endif
#if (ROS_TAIL_CHECK_SIZE == 0 || ROS_TAIL_CHECK_SIZE > 10)
  !error ROS_TAIL_CHECK_SIZE out of range
#endif
#define ROS_TAIL_CHECK_VALUE 0xBB
#define ROS_TAIL_CHECK_VALUE32 0xBBBBBBBB

// Event mask
#define ROS_EVENT_KILL  0x1
#define ROS_EVENT_KICK  0x2

#ifndef ROS_MAX_STALL_COUNT
  #define ROS_MAX_STALL_COUNT 100
#endif

#if (RS_QUEUES == RSQT_STATIC)
  #define RosIsIdle(pg) ((pg->Head == pg->Tail) || pg->Stall)
#endif
#if (RS_QUEUES == RSQT_HEAP)
  #define RosIsIdle(pg) (RsListIsEmpty(&pg->Queue) || pg->Stall)
#endif

#ifndef ROS_LOG_MAIL_COUNT
  #define ROS_LOG_MAIL_COUNT 0x10 // Must be power of 2.
#endif

#define ROS_MAX_MAIL_SIZE ((((1UL << ((sizeof(RosMailSizeType)*8UL)-1UL))-1UL)*2UL)-RSOFFSETOF(RosMailEntryType,Mail))

#ifndef ROS_MAX_CHECK_INTERVAL
  #define ROS_MAX_CHECK_INTERVAL 987UL
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning( disable : 4820) // padding added
#endif

typedef union
{
  struct
  {
    rsbitfield LowPrio : 1;
    rsbitfield HighPrio : 1;
    rsbitfield : 6;
  };
  rsuint8 v;
} RosGroupFlagsType;

typedef struct RosGroupType
{
  struct RosGroupType* Next;
  rsuint8 GroupId;
  RosGroupFlagsType Flags;
  RosTaskIdType NumActiveTasks;
  rsuint8 DeliverPending;
  rsuint16 TotalMails;
  volatile rsuint8 Stall;
  RS_PADDING(1)
  RosMailStatType Stats;
  #if (RS_RTOS_ID == RSTS_FUSION)
  fosEvent Event;
  fosTask Thread;
  #endif
  #if (RS_QUEUES == RSQT_STATIC)
  rsuint8* End;
  rsuint8* Head;
  rsuint8* Tail;
  rsuint8 Mails[0x40];
  #endif
  #if (RS_QUEUES == RSQT_HEAP)
  RsListEntryType Queue;
  #endif
} RosGroupType;

typedef struct
{
  RosTaskIdType Src;
  RosTaskIdType Dst;
  RosPrimitiveType Primitive;
} RosLogEntryType;

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

extern RS_FASTDATA_ADR RosGroupType* RosGroups;

#ifdef ROS_LOG_MAILS
extern RS_FASTDATA_ADR RosLogEntryType RosLogEntries[ROS_LOG_MAIL_COUNT];
extern RS_FASTDATA_ADR rsuint8 RosLogIdx;
#endif

#if (RS_ITIMERS == 1)
extern RS_FASTDATA_ADR RsITimerType RosITimer;
#endif

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
void RosCreateGroups(void);
RosGroupType* RosGetGroup(RosTaskIdType TaskId);
void RosInit(void);
rsbool RosRunAll(void);
rsbool RosAllIdle(void);

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
void RosCreateTasks(void);

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
#ifdef RS_ACTIVE_TASK_MAP
rsuint8 RosIsTaskActive(RosTaskIdType TaskId);
#else
#ifdef RS_C_INLINE
RS_C_INLINE rsuint8 RosIsTaskActive(RosTaskIdType TaskId) { return 1; }
#else
rsuint8 RosIsTaskActive(RosTaskIdType TaskId);
#endif
#endif

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
void RosAllTaskInit(void);
void RosDoTaskInit(rsuint8 GroupId);
rsuint8 RosDoTaskTerminate(void);

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
void RosCreateTimers(void);
void RosRunTimers(void);
rsbool RosIsTimerExpired(RosTimerIdType TimerId, RsTimerTickType Value);
void RosTimerTick(rsuint16 ElapsedTicks);

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
#if (RS_ROS_INLINE == 1)
RS_C_INLINE void RosMailSetFlags(RosMailType* Mail, rsuint8 Flags)
{
  RosMailEntryType* pe = RSCONTAININGOFFSET(Mail, RosMailEntryType, Mail);
  pe->Flags |= Flags;
}
#else
void RosMailSetFlags(RosMailType* Mail, rsuint8 Flags);
#endif

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
rsbool RosMailDispatch(RosGroupType* pg);
void RosHookMailDeliver(RosMailEntryType* pe);

/****************************************************************************
* DESCRIPTION:
****************************************************************************/
#if (RS_TARGET_FAMILY == RSTF_CR16C || RS_TARGET_FAMILY == RSTF_ARM)
#ifdef RS_C_INLINE
RS_C_INLINE void RosWakeupGroup(RosGroupType* Group)
{
  #if (RS_RTOS_ID == RSTS_FUSION)
  fosEventSet(&Group->Event, FOS_EVENT_OR, ROS_EVENT_KICK);
  #endif
}
#else
void RosWakeupGroup(RosGroupType* Group);
#endif
#else
void RosWakeupGroup(RosGroupType* Group);
#endif

#ifdef ROS_LOG_MAILS
void RosLogMail(RosMailEntryType* pe);
#endif

RS_END_EXTERN_C

/** \endcond */

#endif

// End of file.

