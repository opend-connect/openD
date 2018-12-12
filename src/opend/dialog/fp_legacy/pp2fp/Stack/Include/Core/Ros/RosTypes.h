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
* ROS general types and macros. Also see \ref ros_manual.
*/

/** \page ros_manual ROS (RTX OS)
*
* The RTX OS is a <i>mail oriented</i> Operating System with a <i>timer system</i>.
* \em Mails are produced and handled by \em tasks.
* ROS is primarily single-threaded; when a mail is delivered to a task, the task
* runs until it has finished processing the mail. Tasks can be placed in \em groups with different priorities.
* Note that ROS tasks are fundamentally different from Fusion tasks/threads.
*
* A mail consists of a \em primitive and optional payload data.
* The primitive identifies the purpose of the mail and the payload data.
*
* Tasks can use <i>timers</i>, which send an application-defined mail when the timer expires.
*
* ROS is configured using a set of application-defined \em const tables, for tasks, groups and timers.
*
* Further information about:
* <UL>
* <LI>\ref RosTasks.h "Tasks, groups, init/mail functions and configuration"</LI>
* <LI>\ref RosTimers.h "Timers and configuration"</LI>
* <LI>\ref RosMails.h "Mail handling"</LI>
* <LI>\ref RosHooks.h "Hooks/callbacks"</LI>
* <LI>\ref RosTypes.h "ROS types reference."</LI>
* </UL>
*
* <hr>
*
* The following code shows two tasks. The \em Ping task starts a timer. When the
* timer expires, it sends a PING mail to the \em Pong task, which just returns a PONG mail.
*
* \code
* // Mail primitives.
* typedef enum
* {
*   OS_NULL,
*   OS_INITTASK,
*   OS_TERMINATE_TASK,
*   OS_TIMEOUT,
*   PING,
*   PONG,
*   OS_MAX_PRIM
* } PrimitiveType;
*
* // Task ID's.
* typedef enum
* {
*   PING_TASK,
*   PONG_TASK,
*   MAXTASKID
* } TaskIdType;
*
* // Timer ID's.
* typedef enum
* {
*   PING_TIMER,
*   MAXMAILTIMER
* } TimerIdType;
*
* // Prototypes.
* void PingTaskInit(RosTaskIdType TaskId);
* void PingTask(RosMailType* Mail);
* void PongTask(RosMailType* Mail);
*
* // Task configuration table.
* RS_CONST RosTaskConfigType RosTaskConfig[] =
* {
*   ROSTASK( PING_TASK,        0, PingTaskInit,  PingTask      ),
*   ROSTASK( PONG_TASK,        0, 0,             PongTask      ),
*   ROSTASK( ROS_TASKID_NONE,  0, 0,             0             ), // Terminator.
* };
*
* // Definition of the mail sent to PingTask when the PING_TIMER expires.
* const RosTimerConfigType PingTimerConfig = { PING_TASK, { OS_TIMEOUT, PING_TIMER } };
*
* // Ping task initalization.
* void PingTaskInit(RosTaskIdType TaskId)
* {
*   RosTimerStart(PING_TIMER, RS_T100MS, &PingTimerConfig);
* }
*
* // Ping task implementation (mail handler).
* void PingTask(RosMailType* Mail)
* {
*   switch (Mail->Primitive)
*   {
*     case OS_TIMEOUT:
*       // The timer expired. Send the mail to PongTask.
*       RosMailSendP0(PING_TASK, PONG_TASK, PING);
*       break;
*
*     case PONG:
*       // Start the timer again.
*       RosTimerStart(PING_TIMER, 10 * RS_T100MS, &PingTimerConfig);
*       break;
*
*     case OS_TERMINATE_TASK:
*       // Default shutdown behaviour (required).
*       RosTaskTerminated(RosMailGetDst(Mail));
*       break;
*   }
* }
*
* // Pong task implementation (mail handler).
* void PongTask(RosMailType* Mail)
* {
*   switch (Mail->Primitive)
*   {
*     case PING:
*       // Send answer mail back to where it came from.
*       RosMailSendP0(PONG_TASK, RosMailGetSrc(Mail), PONG);
*       break;
*
*     case OS_TERMINATE_TASK:
*       // Default shutdown behaviour (required).
*       RosTaskTerminated(RosMailGetDst(Mail));
*       break;
*   }
* }
* \endcode
* <br>
*/


#ifndef ROS_TYPES_H
#define ROS_TYPES_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name ROS flags/options.
*/
//@{
#ifndef ROS_FLAG_TAIL_CHECK
  #define ROS_FLAG_TAIL_CHECK 1 /*!< Tailcheck on mails. */
#endif
#ifndef ROS_FLAG_MAIL_STATS
  #define ROS_FLAG_MAIL_STATS 1 /*!< Maintain mailqueue statistics. */
#endif
#ifndef ROS_FLAG_TASK_MAP
  #define ROS_FLAG_TASK_MAP 1 /*!< Enable task map in RAM (allows non-consecutive TaskId's in \ref RosTaskConfig). */
#endif
#ifndef ROS_FLAG_MAILS_MUTABLE
  #define ROS_FLAG_MAILS_MUTABLE 1 /*!< Allow task mail handler to modify received mails. */
#endif
//@}

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#ifndef ROS_OVERRIDE_TYPES
  typedef rsuint8 RosTaskIdType;          /*!< For task identifiers. */
  typedef rsuint16 RosMailSizeType;       /*!< For the size field for individual mails. */
  typedef rsuintsz RosMailTotalType;      /*!< For the size field for total counters. */
  typedef rsuint16 RosPrimitiveType;      /*!< For mail primitives. */
  typedef rsuint16 RosTimerIdType;        /*!< For timer identifiers. */
  typedef rsuint16 RosTimerParameterType; /*!< For timer parameters. */
#endif

/// ROS mail queue statistics.
typedef struct
{
  RosMailTotalType CurrentQueueSize;  /*!< Current mail queue size in bytes. */
  RosMailTotalType PeakQueueSize;     /*!< Peak mail queue size in bytes. */
} RosMailStatType;

/// Empty mail (only primitive).
typedef struct
{
  RosPrimitiveType Primitive; /*!< Mail identifier. */
} RosMailEmptyType;

/// Mail with 1 byte.
typedef struct
{
  RosPrimitiveType Primitive; /*!< Mail identifier. */
  rsuint8 P1; /*!< Parameter 1. */
  RS_PADDING(1)
} RosMailP1Type;

/// Mail with 2 bytes.
typedef struct
{
  RosPrimitiveType Primitive; /*!< Mail identifier. */
  rsuint8 P1; /*!< Parameter 1. */
  rsuint8 P2; /*!< Parameter 2. */
} RosMailP2Type;

/// Mail with 3 bytes.
typedef struct
{
  RosPrimitiveType Primitive; /*!< Mail identifier. */
  rsuint8 P1; /*!< Parameter 1. */
  rsuint8 P2; /*!< Parameter 2. */
  rsuint8 P3; /*!< Parameter 3. */
  RS_PADDING(1)
} RosMailP3Type;

/// Mail with 4 bytes.
typedef struct
{
  RosPrimitiveType Primitive; /*!< Mail identifier. */
  rsuint8 P1; /*!< Parameter 1. */
  rsuint8 P2; /*!< Parameter 2. */
  rsuint8 P3; /*!< Parameter 3. */
  rsuint8 P4; /*!< Parameter 4. */
} RosMailP4Type;

/// Mail with 5 bytes.
typedef struct
{
  RosPrimitiveType Primitive; /*!< Mail identifier. */
  rsuint8 P1; /*!< Parameter 1. */
  rsuint8 P2; /*!< Parameter 2. */
  rsuint8 P3; /*!< Parameter 3. */
  rsuint8 P4; /*!< Parameter 4. */
  rsuint8 P5; /*!< Parameter 5. */
} RosMailP5Type;

/// Mail with byte array.
typedef struct
{
  RosPrimitiveType Primitive; /*!< Mail identifier. */
  rsuint8 Data[0xFE]; /*!< Payload data. */
} RosMailDataType;

/// Mail used for expired timers.
typedef struct
{
  RosPrimitiveType Primitive; /*!< Mail identifier. */
  RosTimerParameterType Parameter; /*!< User-defined parameter from the timer configuration. */
} RosMailTimeoutType;

/// Mail union.
typedef union RosMailType
{
  RosPrimitiveType Primitive; /*!< Mail identifier. */
  RosMailP1Type P1; /*!< Mail with 1 byte. */
  RosMailP2Type P2; /*!< Mail with 2 bytes. */
  RosMailP3Type P3; /*!< Mail with 3 bytes. */
  RosMailP4Type P4; /*!< Mail with 4 bytes. */
  RosMailP5Type P5; /*!< Mail with 5 bytes. */
  RosMailDataType Data; /*!< Mail with byte array. */
  RosMailTimeoutType Timeout; /*!< Mail used for expired timers. */
} RosMailType;

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

/** \cond internal */
// Deprecated.
#define RosFlags !deprecated
#define RosMaxCheckInterval !deprecated
/** \endcond */

RS_END_EXTERN_C

#endif

// End of file.

