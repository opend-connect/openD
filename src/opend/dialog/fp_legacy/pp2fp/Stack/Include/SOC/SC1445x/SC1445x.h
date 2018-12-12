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

#ifndef SC1445x_H
#define SC1445x_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <SysClock/SysClock.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef enum
{
  SCU_PER10_UART    = RSBIT0,
  SCU_PER10_ACCESS1 = RSBIT1,
  SCU_PER10_ACCESS2 = RSBIT2,
  SCU_PER10_CLASSD  = RSBIT3,
  SCU_PER10_CP      = RSBIT4,
  SCU_PER10_SPI1    = RSBIT5,
  SCU_PER10_SPI2    = RSBIT6,
  SCU_PER10_MAX
} ScPer10UserIdType;

typedef union
{
  rsuint8 Value;
  struct
  {
    rsbitfield UART     : 1;
    rsbitfield ACCESS1  : 1;
    rsbitfield ACCESS2  : 1;
    rsbitfield CLASSD   : 1;
    rsbitfield CP       : 1;
    rsbitfield SPI1     : 1;
    rsbitfield SPI2     : 1;
  };
} ScPer10UserMaskType;

typedef enum
{
  SCU_CP1_EEPROM  = RSBIT0,
  SCU_CP1_DISPLAY = RSBIT1,
  SCU_CP1_LED1    = RSBIT2,
  SCU_CP1_LED2    = RSBIT3,
  SCU_CP1_FLASH   = RSBIT4,
  SCU_CP1_MAX
} ScCp1UserIdType;

typedef union
{
  rsuint8 Value;
  struct
  {
    rsbitfield EEPROM   : 1;
    rsbitfield DISPLAY  : 1;
    rsbitfield LED1     : 1;
    rsbitfield LED2     : 1;
    rsbitfield FLASH    : 1;
  };
} ScCp1UserMaskType;

typedef enum
{
  SCU_XTAL_CPU       = RSBIT0,
  SCU_XTAL_DIP       = RSBIT1,
  SCU_XTA_MAX
} ScXtalUserIdType;

typedef union
{
  rsuint8 Value;
  struct
  {
    rsbitfield CPU      : 1;
    rsbitfield DIP      : 1;
  };
} ScXtalUserMaskType;

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
void ScPer10Request(ScPer10UserIdType UserId, ScStateType State);
void ScCp1Request(ScCp1UserIdType UserId, ScStateType State);
void ScXtalRequest(ScXtalUserIdType UserId, ScStateType State);

/****************************************************************************
* DESCRIPTION: Switches to 300kHz oscillator, powers off the xtal, and waits
* for an interrupt.
* if OnlyDipInt is TRUE, only DIP interrupt can wake up.
* if OnlyDipInt is FALSE, any interrupt source can wake up.
* returns TRUE if wakeup was caused by DIP interrupt, FALSe if wakeup caused by
* another interrupt source.
****************************************************************************/
rsbool ScMacXtalOffRequest(rsbool OnlyDipInt);

RS_END_EXTERN_C

#endif

// End of file.

