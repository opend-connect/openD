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

#ifndef API_HAL_TYPES_H
#define API_HAL_TYPES_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <DevDrv/Classes/SerCom/DrvClassSerCom.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define API_HAL_SERCOM 0x01
#define API_HAL_LEDS   0x02
#define API_HAL_READ   0x04
#define API_HAL_WRITE  0x08
#define API_HAL_GPIO   0x10
#define API_HAL_TIM0   0x20
//#define API_HAL_ 0x40
//#define API_HAL_ 0x80

#ifndef API_HAL_OPTIONS
  #define API_HAL_OPTIONS (API_HAL_SERCOM | API_HAL_LEDS | API_HAL_READ | API_HAL_WRITE | API_HAL_GPIO | API_HAL_TIM0)
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef const DrvClassSerCom_CmdDataType* GetDrvIfType(void);

typedef struct
{
  ApiHalDeviceIdType DeviceId;
  GetDrvIfType* GetDrvIf;
} ApiHalSerComDriverType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

extern const ApiHalSerComDriverType ApiHalSerComDrivers[];

/****************************************************************************
*                             Function prototypes
****************************************************************************/

RS_END_EXTERN_C

// Project specific implementation.
void ApiHalSetLed(rsuint8 Idx, rsbool On);

#endif

