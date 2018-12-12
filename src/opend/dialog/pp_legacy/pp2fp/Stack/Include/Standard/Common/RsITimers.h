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
*
* \section rsitimer_usage Interrupt Timers
*
* Interrupt timers execute directly from the system timer interrupt service routine.
*
* The data for an interrupt timer is held in a \ref RsITimerType control block.
* The user must provide the storage for the \ref RsITimerType control block while the timer is running.
* It is usually just declared in the C file where it is being used.
* The control block must be intialized using \ref RsITimerInit before the first call to \ref RsITimerStart or \ref RsITimerStop.
*
* A timer is started using \ref RsITimerStart. Timer values are in milliseconds, but actual resolution depends on the OS.
* The \c Timeout function specified in \ref RsITimerType control block is called when the timer expires.
*
* Interrupt timers are always one-shot i.e. a timer must be started again when it expires.
* <br><br>
*/


#if (RS_ITIMERS == 1)

#ifndef RS_ITIMERS_H
#define RS_ITIMERS_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

struct RsITimerType;

/// Prototype for timeout function.
/** \param Timer Pointer to timer instance. */
typedef void RsITimeoutType(struct RsITimerType* Timer);

/// Data for a timer instance. The owner must provide storage for this structure while the timer is used.
typedef struct RsITimerType
{
  RsListEntryType Link; /*!< Used internally for timer management. */
  RsTimerTickType Value; /*!< Timeout value in ms. */
  RsITimeoutType* Timeout; /*!< Function called at timeout. User provided. */
  void* Context; /*!< Opaque context for the timer. This field is not touched by the timer system. */
} RsITimerType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/// Initialize a timer instance. A timer must be initialized (once) before in can be started.
/** \param Timer Pointer to timer instance.
* \param Timeout Function to be called at timeout.
* \param Context User context for the timer. */
void RsITimerInit(RsITimerType* Timer, RsITimeoutType* Timeout, void* Context);

/// Start a timer. This function may be called on a running timer to change or reset the timeout value.
/** \param Timer Pointer to timer instance.
* \param Value Timeout value in ms. */
void RsITimerStart(RsITimerType* Timer, RsTimerTickType Value);

/// Stop a timer.
/** \param Timer Pointer to timer instance. */
void RsITimerStop(RsITimerType* Timer);

/// Shorten a running timer. This function may be called on a running timer to reduce the timeout value.
/** \param Timer Pointer to timer instance.
* \param Value Timeout value in ms. */
void RsITimerShorten(RsITimerType* Timer, RsTimerTickType Value);

RS_END_EXTERN_C

#endif
#endif

// EOF.


