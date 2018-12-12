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
/*! \file
* Hook functions (callbacks). These functions are called out from ROS.
*/


#ifndef ROS_HOOKS_H
#define ROS_HOOKS_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

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

/** \name ROS execution hooks.
*/
//@{

#if (ROS_HOOK_TIMER_PRE_CHECK == 1)
/// Timer tick polling. This function is called when \ref ROS_HOOK_TIMER_PRE_CHECK is set to 1.
/** Called from ROS before the timer system is checked, for every timer tick. */
void RosHookTimerPreCheck(void);
#else
  #define RosHookTimerPreCheck !disabled
#endif

#if (ROS_HOOK_MAIL_QUEUE_PRE_CHECK == 1)
/// Mail queue polling. This function is called when \ref ROS_HOOK_MAIL_QUEUE_PRE_CHECK is set to 1.
/** Called from ROS before the mail queue is checked.
* Use with care, as there is no starvation check. */
void RosHookMailQueuePreCheck(void);
#else
  #define RosHookMailQueuePreCheck !disabled
#endif

#if (ROS_HOOK_MAIL_QUEUE_EMPTY == 1)
/// Mail queue empty polling. This function is called when \ref ROS_HOOK_MAIL_QUEUE_EMPTY is set to 1.
/** Called from ROS when the mail queue is empty.
* Use with care, as there is no starvation check.
* If the system is busy, this function may not be called for several seconds or even minutes. */
void RosHookMailQueueEmpty(void);
#else
  #define RosHookMailQueueEmpty !disabled
#endif

#if (ROS_HOOK_MAIL_PRE_DELIVERY == 1)
/// Mail pre-delivery polling. This function is called when \ref ROS_HOOK_MAIL_PRE_DELIVERY is set to 1.
/** Called from ROS when a mail is about to be delivered to a task.
* The \a Dst can be modified. E.g. set it to \ref ROS_TASKID_NONE to discard the mail.
* \param Src Source (sender) task ID.
* \param Dst Pointer to destination (receiver) task ID.
* \param Size Mail size.
* \param Mail The mail packet. */
void RosHookMailPreDelivery(RosTaskIdType Src, RosTaskIdType* Dst, RosMailSizeType Size, RosMailType* Mail);
#else
  #define RosHookMailPreDelivery !disabled
#endif

#if (ROS_HOOK_MAIL_POST_DELIVERY == 1)
/// Mail post-delivery polling.
/** Called from ROS after a mail was delivered i.e. after the destination task has processed the mail.
* \param Src Source (sender) task ID.
* \param Dst Destination (receiver) task ID.
* \param Size Mail size.
* \param Mail The mail packet.
* \param Time Mail processing time. Only valid when using FOS and profiling is enabled.
* Note that the time provided is only a rough estimate, it doesnt take into account any processing time used by interrupts or higher-priority tasks. */
void RosHookMailPostDelivery(RosTaskIdType Src, RosTaskIdType Dst, RosMailSizeType Size, const RosMailType* Mail, RsPerformanceTimeType Time);
#else
  #define RosHookMailPostDelivery !disabled
#endif

#if (ROS_HOOK_TASK_PRE_INIT == 1)
/// Task pre-init polling. This function is called when \ref ROS_HOOK_TASK_PRE_INIT is set to 1.
/** Called from ROS when a task initializer function is about to be called.
* \param TaskId Task ID of the task about to be initialized. */
void RosHookTaskPreInit(RosTaskIdType TaskId);
#else
  #define RosHookTaskPreInit !disabled
#endif

#if (ROS_HOOK_TIMER_START == 1)
/// Timer start hook. This function is called when \ref ROS_HOOK_TIMER_START is set to 1.
/** Called from ROS when a ROS timer is started.
* \param TimerId timer identifier.
* \param Value Specifies when the timer is to expire. */
void RosHookTimerStart(RosTimerIdType TimerId, RsTimerTickType Value);
#else
  #define RosHookTimerStart !disabled
#endif

#if (ROS_HOOK_TIMER_STOP == 1)
/// Timer stop hook. This function is called when \ref ROS_HOOK_TIMER_STOP is set to 1.
/** Called from ROS when a ROS timer is stopped.
* \param TimerId timer identifier. */
void RosHookTimerStop(RosTimerIdType TimerId);
#else
  #define RosHookTimerStop !disabled
#endif

#if (ROS_HOOK_TIMER_VALUE == 1)
/// Timer value hook. This function is called when \ref ROS_HOOK_TIMER_VALUE is set to 1.
/** Called from ROS when a ROS timer's value is changed (decremented).
* \param TimerId timer identifier.
* \param Value New value. */
void RosHookTimerValue(RosTimerIdType TimerId, RsTimerTickType Value);
#else
  #define RosHookTimerValue !disabled
#endif

#if (ROS_HOOK_TIMER_EXPIRED == 1)
/// Timer expired hook. This function is called when \ref ROS_HOOK_TIMER_EXPIRED is set to 1.
/** Called from ROS when a ROS timer's value is changed (decremented).
* \param TimerId timer identifier. */
void RosHookTimerExpired(RosTimerIdType TimerId);
#else
  #define RosHookTimerExpired !disabled
#endif
//@}

/** \cond internal */
// Deprecated hooks.
#define RosHookMailAllocated !deprecated
#define RosHookMailQueued !deprecated
#define RosHookMailQueuePostCheck !deprecated
#define RosHookMailAllocated !deprecated
#define RosHookMailQueued !deprecated
#define RosHookDfcPreCall !deprecated
/** \endcond */

RS_END_EXTERN_C

#endif

// End of file.

