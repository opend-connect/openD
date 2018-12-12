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

#ifndef MELODYTAB_H
#define MELODYTAB_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef enum RSENUMTAG(MelodyIdType)
{
  API_TONE_DIAL                     = 0x00,
  API_TONE_RINGBACK                 = 0x01,
  API_TONE_INTERCEPT                = 0x02,
  API_TONE_NETWORK_CONGESTION       = 0x03,
  API_TONE_BUSY                     = 0x04,
  API_TONE_CONFIRM                  = 0x05,
  API_TONE_ANSWER                   = 0x06,
  API_TONE_CALL_WAITING             = 0x07,
  API_TONE_OFF_HOOK_WARNING         = 0x08,
  API_TONE_NEGATIVE_ACKNOWLEDGEMENT = 0x09,
  API_TONE_CONFERENCE               = 0x0A,
  API_TONE_KEY_CLICK                = 0x0B,
  API_TONE_SUCCESS                  = 0x0C,
  API_TONE_ERROR                    = 0x0D,
  API_TONE_LOW_BATT                 = 0x0E,
  API_TONE_NO_NETWORK               = 0x0F,
  API_TONE_REGISTRATION_FAIL        = 0x10,
  API_TONE_ALARM_SOUND              = 0x11,
  API_TONE_TEST_500HZ               = 0x12,
  API_TONE_TEST_1000HZ              = 0x13,
  API_TONE_TEST_3000HZ              = 0x14,
  API_TONE_TEST_6000HZ              = 0x15,
  API_RING_MELODY_1_ID              = 0x16,
  API_RING_MELODY_2_ID              = 0x17,
  API_RING_MELODY_3_ID              = 0x18,
  API_RING_MELODY_4_ID              = 0x19,
  TONE_LAST_ID
} RSENUM8(MelodyIdType);

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#endif


