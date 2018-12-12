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
* ROS timer types, macros and functions. Also see \ref ros_manual.
*
* ROS \em timers are used from ROS \em tasks. A timer is identifed by a \ref RosTimerIdType value,
* which must be unique. The timer ID is used when starting and stopping the timer.
*
* A timer is started with \ref RosTimerStart, which includes the timer value and a specification of the mail to send when the timer expires.
* All timer \em values are specified using the \ref RS_T10MS, \ref RS_T100MS and \ref RS_T1SEC macros. E.g. 300 ms is specified as 3 * RS_T100MS.
* A timer is stopped with \ref RosTimerStop.
*
* The mail to send when a timer expires is defined using \ref RosTimerConfigType,
* which includes the destination task, mail primitive and one additonal parameter.
*
* \code
* // Sample timeout mail.
* const RosTimerConfigType PingTimerConfig = ROSTIMER(PING_TASK, OS_TIMEOUT, PING_TIMER);
*
* // Start timer to expire after 300 ms.
* RosTimerStart(PING_TIMER, 3 * RS_T100MS, &PingTimerConfig);
* \endcode
*
* <hr>
*
*/


#ifndef ROS_TIMERS_H
#define ROS_TIMERS_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/// Timer configuration entry.
typedef struct
{
  RosTaskIdType Owner;      /*!< Owner task Identifier. */
  RS_PADDING(1)
  RosMailTimeoutType Mail;  /*!< Mail sent when timer expires. */
} RosTimerConfigType;

#if (RS_SET_PACKING > 1)
  #define ROSTIMER(task,primitive,parameter) { task, {0}, { primitive, parameter } }
#else
  #define ROSTIMER(task,primitive,parameter) { task, { primitive, parameter } } /*!< Initialize a \ref RosTimerConfigType block. */
#endif

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/// Next timeout value i.e. the value of the shortest timer running.
extern RS_FASTDATA_ADR RsTimerTickType RosNextTimeout;

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/** \name Timer functions.
*/
//@{

/// Start a timer.
/** \param TimerId timer identifier.
* \param Value Specifies when the timer is to expire.
* \param Config Specifies the mail to send when the timer expires. */
void RosTimerStart(RosTimerIdType TimerId, RsTimerTickType Value, const RosTimerConfigType* Config);

/// Stop a timer.
/** \param TimerId */
void RosTimerStop(RosTimerIdType TimerId);

/// Get owner task ID for a running timer.
/** \param TimerId timer identifier.
* \return Owner task ID, or ROS_TASKID_NONE if the timer is stopped. */
RosTaskIdType RosTimerOwner(RosTimerIdType TimerId);

/// Returns number of running timers.
/** \return Number of running timers. */
rsuint16 RosTimerCount(void);
//@}

/// Returns how many ms that will be charged to the ROS timers on the next run of the timer system.
/** \return ms. */
RsTimerTickType RosPendingMs(void);

RS_END_EXTERN_C

#endif

// End of file.

