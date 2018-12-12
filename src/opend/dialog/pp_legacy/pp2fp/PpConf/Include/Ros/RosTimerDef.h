/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
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
	KEY_SCAN_TIMER,
	LED1_FLASH_TIMER,
	LED2_FLASH_TIMER,
	LED3_FLASH_TIMER,
	LED4_FLASH_TIMER,
	LED5_FLASH_TIMER,
	LED6_FLASH_TIMER,
	LED7_FLASH_TIMER,
	REGISTRATION_TIMER,
	CONNECTION_TIMER,
	MELODY_RELOAD_TIMER,
	UNMUTE_AUDIO_TIMER,
	CF_STATE_TIMER,
	COLA_TIMER_NUMBER,

  COLA_LAST_TIMER=0x10FF,
  MAX_TIMER_ID
} RSENUM16(TimerIdentifier);

#define COLA_TIMER_FIRST KEY_SCAN_TIMER

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#endif

