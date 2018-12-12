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

#ifndef ROSTIMERDEF_H
#define ROSTIMERDEF_H

/****************************************************************************
*                               Include files
****************************************************************************/


/****************************************************************************
*                              Macro definitions
****************************************************************************/


/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef enum RSENUMTAG(TimerIdentifier)
{
  COLA_FIRST_TIMER=0x1000,
  // Add application timer ID's here.
  APP_LED_TIMER,
  MMI_STATE_TIMER,
  MMI_LED_TIMER,
  MMI_POLL_TIMER,
  MMI_RESET_TIMER,
  UART_LOG_TIMER,
  USER_TASK_TIMER,
  DUMMY_MESSAGE_TIMER,
  LOCK_TIMER,
  REGISTRATION_TIMER,
  USER_SW_COUNTER_TIMER,
  LR_TIMER,
  LOGGING_TIMER,
  SEND_LOG_TIMER,
  SMARTPLUG_TIMER,
  RSSI_MEAS_TIMER,
  CAPP_TIMER,
  COLA_LAST_TIMER=0x10FF,
  MAX_TIMER_ID
} RSENUM16(TimerIdentifier);

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#endif

