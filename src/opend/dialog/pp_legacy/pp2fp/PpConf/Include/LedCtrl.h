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
#ifndef LED_CTRL_H
#define LED_CTRL_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>


/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define LED_FLASHING_PATTERN_COUNT_MAX 6


/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
/*! This enum defines the LED?s supported. */
typedef enum RSENUMTAG(ApiLedIdType)
{
  AL_RESERVED      = 0x00, /*!< Reserved. */
#ifdef NATALIE_V11
  AL_LED1          = 0x01, /*!< LED1 */
  AL_LED3          = 0x02, /*!< LED3 */
  AL_LED4          = 0x03, /*!< LED4 */
#else
  AL_LED1          = 0x01, /*!< LED1 */
  AL_LED2_RESERVED = 0x02, /*!< LED2 can not be used as this pin is connected to the
                              EEPROM. */
  AL_LED3          = 0x03, /*!< LED3 */
  AL_LED4          = 0x04, /*!< LED4 */
#endif
  AL_SYS_LED_TOTAL,        //Total LED used by stack software
  AL_MMI_LED_1,
  AL_MMI_LED_2,
  AL_MMI_LED_3,
  AL_MMI_LED_4,
  AL_MMI_LED_5,
  AL_MMI_LED_6,
  AL_MMI_LED_7,
  AL_MMI_LED_8,  
  AL_LED_TOTAL,               
  AL_INVALID       = 0xFF  /*!< [0x05; 0xFF] is invalid. */
} RSENUM8(ApiLedIdType);

typedef rsuint8 ApiLedType;

#define SYSTEM_STATUS_LED AL_LED3

#define MMI_LED_ID_OFFSET AL_MMI_LED_1
#define MMI_LED_ID(led)   (led-MMI_LED_ID_OFFSET)
#define MMI_LED_1         (AL_MMI_LED_1-MMI_LED_ID_OFFSET)
#define MMI_LED_2         (AL_MMI_LED_2-MMI_LED_ID_OFFSET)
#define MMI_LED_3         (AL_MMI_LED_3-MMI_LED_ID_OFFSET)
#define MMI_LED_4         (AL_MMI_LED_4-MMI_LED_ID_OFFSET)
#define MMI_LED_5         (AL_MMI_LED_5-MMI_LED_ID_OFFSET)
#define MMI_LED_6         (AL_MMI_LED_6-MMI_LED_ID_OFFSET)
#define MMI_LED_7         (AL_MMI_LED_7-MMI_LED_ID_OFFSET)
#define MMI_LED_8         (AL_MMI_LED_8-MMI_LED_ID_OFFSET)
#define MEM_LED_NUM       (AL_LED_TOTAL-MMI_LED_ID_OFFSET)

/*! This enum defines the LED command supported. */
typedef enum RSENUMTAG(ApiLedCommandCodeIdType)
{
  ALC_LED_OFF         = 0x00, /*!< LED off */
  ALC_LED_ON          = 0x01, /*!< LED on. */
  ALC_REPEAT_SEQUENCE = 0x02, /*!< Repeat the LED sequence. */
  ALC_INVALID         = 0xFF  /*!< [0x03; 0xFF] is invalid. */
} RSENUM8(ApiLedCommandCodeIdType);
typedef rsuint8 ApiLedCommandCodeType;

/*! This struct is used to hold one LED command. */
typedef struct 
{
  ApiLedCommandCodeIdType  Command;     /*!< The LED command */
  rsuint16  Duration;                   /*!< The duration in ms for ALC_LED_OFF and
                                           ALC_LED_ON. 0 = no delay/timeout.
                                           The number of times to repeat the sequence for
                                           ALC_REPEAT_SEQUENCE. 0xFFFF = repeat forever. */
} ApiLedCommandType;

typedef enum RSENUMTAG(LedFlashingPatternType)
{
  LED_FLASHING_PATTERN_OFF,
  LED_FLASHING_PATTERN_ON,
  LED_FLASHING_PATTERN_SLOW,  
  LED_FLASHING_PATTERN_FAST,
  LED_FLASHING_PATTERN_ALERTING,
  LED_FLASHING_PATTERN_TOTAL
} RSENUM8(LedFlashingPatternType);

#define LED_FLASHING_PATTERN_REGISTRATION LED_FLASHING_PATTERN_FAST
#define LED_FLASHING_PATTERN_CONNECTED    LED_FLASHING_PATTERN_SLOW

typedef struct 
{
  rsuint8 CommandsCount;
  ApiLedCommandType Commands[LED_FLASHING_PATTERN_COUNT_MAX];
} LedFlashingCmdType;

/****************************************************************************
*                            Global variables/const
****************************************************************************/


/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
extern void LedCtrlInit(void);
extern void LedCtrlSwitchPinIO(void);
extern void LedCtrlSet(ApiLedType led, LedFlashingPatternType flashingPattern);
extern void LedCtrlFlashingTimerTimeOut(RosTimerIdType LedFlashingTimerId);
extern void LedCtrlShowStatus(void);
#endif //LED_CTRL_H
// End of file.

