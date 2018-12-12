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

#ifndef DYNMMITIM_H
#define DYNMMITIM_H

/****************************************************************************
*                               Include files                                
****************************************************************************/

/****************************************************************************
*                              Macro definitions                             
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs                  
****************************************************************************/

/* Global primitives: 
   DYNMMI_TIMEOUT_IND,
The global primitives MUST be defined in Global.h! */

/* Timer status of a dynamic allocated timer. */
enum DynMmiTimerStatusEnum
{
   DYNMMI_TIMER_STOPPED = 0x00,
   DYNMMI_TIMER_EXPIRED = 0x01,           /* Timer is expired, but the timeout 
                                          mail is not handled yet. */
   DYNMMI_TIMER_RUNNING = 0x02,
   DYNMMI_TIMER_INVALID = 0x03            /* Timer does not exist. */
};

/* Timer status type. */
typedef rsuint8 DynMmiTimerStatusType;


/* This mail is send when a timer is expired. */
typedef struct
{
   PrimitiveType Primitive;
   RosTimerIdType TimerId;
} DynMmiTimeoutIndType;

/****************************************************************************
*                           Global variables/const                           
****************************************************************************/

/****************************************************************************
*                             Function prototypes                            
****************************************************************************/
/****************************************************************************
*  DESCRIPTION:   This function creates a timer.
****************************************************************************/
rsbool DynMmiCreateTimer(RosTimerIdType TimerId);

/****************************************************************************
*  DESCRIPTION:   This function deletes a dynamic allocated timer.
****************************************************************************/
void DynMmiDestroyTimer(RosTimerIdType TimerId);

/****************************************************************************
*  DESCRIPTION:   This function starts a timer.
****************************************************************************/
void DynMmiStartTimer(RosTimerIdType TimerId, RsTimerTickType Time);

/****************************************************************************
*  DESCRIPTION:   This function stops the timer. Remember that a timer 
                  expire mail may already have been put on the mail queue.
****************************************************************************/
void DynMmiStopTimer(RosTimerIdType TimerId);

/****************************************************************************
*  DESCRIPTION:   This function is used to expire a timer (Test only).
****************************************************************************/
void DynMmiExpireTimer (RosTaskIdType TaskId, RosTimerIdType TimerId);

/****************************************************************************
*  DESCRIPTION:   This function is called from BtSiTimerTick().
****************************************************************************/
void DynMmiTimerTick(void);

/****************************************************************************
*  DESCRIPTION:   This function is called from BtSiTimerTick().
****************************************************************************/
void DynMmiRunTimerSystem (void);

/****************************************************************************
*  DESCRIPTION:   This function returns the current status of the timer. It 
*                 shall be used when a timeout indication is received, to 
*                 verify that the timer has not previously been stopped. If 
*                 the status is "expired" it will be changed to "stopped", 
*                 when this function is called.
****************************************************************************/
DynMmiTimerStatusType DynMmiTimerStatus(RosTaskIdType TaskId, RosTimerIdType TimerId);


/****************************************************************************
*  DESCRIPTION:   This function returns the remaining time before the timer 
*                 expires.
*                 If the timer does not exist or is stopped, 0 is returned.
****************************************************************************/
RsTimerTickType DynMmiRemainingTime(RosTimerIdType TimerId);

/****************************************************************************
*  DESCRIPTION:   This function is used to release all memeory allocated when
*                 the core is shut down.
****************************************************************************/
void DynMmiTerminateTimerSystem(void);


#endif /* DYNMMITIM_H */


