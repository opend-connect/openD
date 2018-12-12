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
* ROS task types, macros and functions. Also see \ref ros_manual.
*
* <hr>
*
* \section ros_mailhandler Task Mail Handler
*
* A \em task consists of a mail function (\ref RosTaskMailFunctionType)
* and an optional init function (\ref RosTaskInitFunctionType).
*
* The mail function is called when a mail is available for the task.
* A task typically checks the primitive and performs futher processing based on that.
* A task is required to handle \ref ROS_SHUTDOWN_MAIL_PRIMITIVE, which is sent when \ref RsShutdown is requested.
* The task must eventually call \ref RosTaskTerminated when it has completed shutdown.
*
* The following code fragment shows a mail handler, which processes two mails.
*
* \code
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
*     case ROS_SHUTDOWN_MAIL_PRIMITIVE:
*       // Default shutdown behaviour (required).
*       RosTaskTerminated(RosMailGetDst(Mail));
*       break;
*   }
* }
* \endcode
*
* <hr>
*
* \section ros_initfunction Task Init Function
*
* The init function is called during startup, before interrupts are enabled.
* It can be either a application-defined function, NULL or \ref RosTaskInitMail.
*
* The following code fragment shows a init function, which starts a timer.
*
* \code
* void PingTaskInit(RosTaskIdType TaskId)
* {
*   RosTimerStart(PING_TIMER, RS_T100MS, &PingTimerConfig);
* }
* \endcode
*
* <hr>
*
* \section ros_taskconfig Task Configuration
*
* \ref RosTaskConfig points to an application-defined task configuration table.
* Each entry is \ref RosTaskConfigType with the task ID, \em flags and init/mail function.
* The table is terminated by an entry with task ID \ref ROS_TASKID_NONE.
*
* \code
* // Sample task configuration table.
* RS_CONST RosTaskConfigType RosTaskConfig[] =
* {
*   ROSTASK( PING_TASK,        0, PingTaskInit,  PingTask      ),
*   ROSTASK( PONG_TASK,        0, 0,             PongTask      ),
*   ROSTASK( ROS_TASKID_NONE,  0, 0,             0             ), // Terminator.
* };
* \endcode
*
* <hr>
*
* \section ros_taskgroups Task Groups
*
* A \em group specifies the memory area for the mail buffer for a group of tasks. All tasks in a group share the mail buffer.
* By placing tasks in multiple groups, it is possible to prioritize tasks.
* When FOS is used, each group is created in a separate thread, and the thread priotity can be specified for each group.
* However, typically just one group is used.
* Each task configuration entry has a \ref RosTaskFlagsType, which can be used to specify the task \em group.
*
* The following code fragment shows a configuration table with two groups.
* The first group listed isd group 0, the second is group 1 and so forth.
*
* \code
* // Mail buffers for each group.
* rsuint32 Mails1[0x400/sizeof(rsuint32)];
* rsuint32 Mails2[0x400/sizeof(rsuint32)];
*
* // FOS task/thread stacks for each group.
* rsuint32 Stack1[0xC0/sizeof(rsuint32)];
* rsuint32 Stack2[0xC0/sizeof(rsuint32)];
*
* // Sample group configuration table.
* RS_CONST RosGroupConfigType RosGroupConfig[] =
* {
*    ROSGROUP( Mails1, Stack1, RS_DEFAULT_TIMESLICE, FOS_TASK_PRIORITY_NORMAL       ),
*    ROSGROUP( Mails2, Stack2, RS_DEFAULT_TIMESLICE, FOS_TASK_PRIORITY_ABOVE_NORMAL ),
*    ROSGROUP( 0, 0, 0, 0 ), // Terminator.
* };
* \endcode
*
* <hr>
*
*/


#ifndef ROS_TASKS_H
#define ROS_TASKS_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define ROS_TASKID_NONE ((RosTaskIdType)-1) /*!< Task ID value for none/null task ID. */

/** \name Task flags/options.
* Task configuration flags, used in \ref RosTaskConfigType. */
//@{
#define RTF_GROUP_MASK  0x0F  /*!< Task group (0..15). */
#define RTF_SHUTDOWN    0x10  /*!< Task requires shutdown mail. */
/** \cond internal */
#define RTF_RESERVED6   0x20
#define RTF_RESERVED7   0x40
#define RTF_RESERVED8   0x80
/** \endcond */
//@}

#if (RS_SET_PACKING > 1)
  #define ROSTASK(id,flags,initf,mailf) {id,flags,{0},initf,mailf}
#else
  #define ROSTASK(id,flags,initf,mailf) {id,flags,initf,mailf} /*!< Declare a task in the \ref RosTaskConfig table. */
#endif

#if (RS_QUEUES == RSQT_HEAP)
  #if (RS_POINTER_SIZE == 8)
    #define ROSGROUP(mails,stack,slice,priority) {0,0,{0},stack,sizeof(stack),slice,priority,0,0}
  #else
    #define ROSGROUP(mails,stack,slice,priority) {0,0,stack,sizeof(stack),slice,priority,0,0}
  #endif
#else
  #if (RS_POINTER_SIZE == 8)
    #define ROSGROUP(mails,stack,slice,priority) {mails,sizeof(mails),{0},stack,sizeof(stack),slice,priority,0,0} /*!< Declare a group in the \ref RosGroupConfig table. */
  #else
    #define ROSGROUP(mails,stack,slice,priority) {mails,sizeof(mails),stack,sizeof(stack),slice,priority,0,0} /*!< Declare a group in the \ref RosGroupConfig table. */
  #endif
#endif

/** \name Mail primitives.
* Init/shutdown mail primitives. */
//@{
#ifndef ROS_INIT_MAIL_PRIMITIVE
  #define ROS_INIT_MAIL_PRIMITIVE 0x7 /*!< Application defined primitive for init mails. */
#endif
#ifndef ROS_SHUTDOWN_MAIL_PRIMITIVE
  #define ROS_SHUTDOWN_MAIL_PRIMITIVE 0x8 /*!< Application defined primitive for shutdown mails. */
#endif
//@}

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/// Prototype for a task init function, called during startup.
/** \param TaskId The ID for the task being initialized. */
typedef void RosTaskInitFunctionType(RosTaskIdType TaskId);

/// Prototype for a task mail function, called when a mail is available.
/** \param Mail The mail to be processed. */
typedef void RosTaskMailFunctionType(const RosMailType* Mail);

typedef rsuint8 RosTaskFlagsType; /*!< For task flags/options. */

/// Task configuration entry.
typedef struct
{
  RosTaskIdType TaskId; /*!< Task Identifier. */
  RosTaskFlagsType TaskFlags; /*!< Task group (0..15). */
  RS_PADDING(RS_POINTER_SIZE-2)
  RosTaskInitFunctionType* InitFunction; /*!< Task init function. Can be user-defined, \ref RosTaskInitMail, or null. */
  RosTaskMailFunctionType* MailFunction; /*!< Task mail function. Can be user-definer or \ref RosTaskDummy. */
} RosTaskConfigType;

/// Group configuration entry.
typedef struct
{
  void* MailQueue; /*!< Address of mail queue. */
  rsuintsz MailQueueSize; /*!< Size of mail queue. */
  RS_PADDING64(4)
  void* stackP; /*!< For fosTaskCreate. */
  rsuint16 stackSize; /*!< For fosTaskCreate. */
  rsuint16 timeSlice; /*!< For fosTaskCreate. */
  rsuint8 priority; /*!< For fosTaskCreate. */
  rsuint8 Reserved1; /*!< Reserved for future use. */
  rsuint16 Reserved2; /*!< Reserved for future use. */
} RosGroupConfigType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/// ROS group configuration table.
extern RS_CONST RosGroupConfigType RosGroupConfig[];

/// ROS task configuration table.
extern RS_CONST RosTaskConfigType RosTaskConfig[];

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/// Task init function that sends a mail with ROS_INIT_MAIL_PRIMITIVE to the task.
/** \param TaskId The ID for the task being initialized. */
void RosTaskInitMail(RosTaskIdType TaskId);

/// Dummy task mail function.
/** \param Mail The mail to be processed. */
void RosTaskDummy(const RosMailType* Mail);

/// Called by a task during shutdown, to indicated to ROS that it has terminated.
/** \param TaskId The ID for the task that it has terminated. */
void RosTaskTerminated(RosTaskIdType TaskId);

/// Get mail queue statistics.
/** \param GroupMask Identifies the group to retrive statistics for.
* \param Stats Pointer to variable that receives the statistics. */
void RosMailGetQueueStats(RosTaskFlagsType GroupMask, RosMailStatType* Stats);

/// Get configuration entry for a task.
/** \param TaskId The ID for the task to find configuration for.
* \return Pointer to task configuration or null. */
const RosTaskConfigType* RosGetTaskConfig(RosTaskIdType TaskId);

/** \cond internal */
// Deprecated.
#define RosInitMailPrimitive !deprecated
#define RosShutdownMailPrimitive !deprecated
/** \endcond */

RS_END_EXTERN_C

#endif

// End of file.

