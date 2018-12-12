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
/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <PortDef.h>
#include "LedCtrl.h"
#include "system.h"
#include "ApiHelper.h"
#include "Util.h"

#ifdef PCCOMPILE
 #include "HostUtil.h"
#endif


/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define SET_D1_ON {P2_SET_DATA_REG=P2_SET_DATA_Px_1_SET;}
#define SET_D2_ON {P2_SET_DATA_REG=P2_SET_DATA_Px_6_SET;}
#define SET_D3_ON {P3_SET_DATA_REG=P3_SET_DATA_Px_3_SET;}
#define SET_D4_ON {P3_SET_DATA_REG=P3_SET_DATA_Px_4_SET;}
#define SET_D5_ON {P3_SET_DATA_REG=P3_SET_DATA_Px_5_SET;}
#define SET_D6_ON {P3_SET_DATA_REG=P3_SET_DATA_Px_6_SET;}
#define SET_D7_ON {P3_SET_DATA_REG=P3_SET_DATA_Px_7_SET;}
#define SET_D8_ON {P1_SET_DATA_REG=P1_SET_DATA_Px_5_SET;}

#define SET_D1_OFF {P2_RESET_DATA_REG=P2_RESET_DATA_Px_1_RESET;}
#define SET_D2_OFF {P2_RESET_DATA_REG=P2_RESET_DATA_Px_6_RESET;}
#define SET_D3_OFF {P3_RESET_DATA_REG=P3_RESET_DATA_Px_3_RESET;}
#define SET_D4_OFF {P3_RESET_DATA_REG=P3_RESET_DATA_Px_4_RESET;}
#define SET_D5_OFF {P3_RESET_DATA_REG=P3_RESET_DATA_Px_5_RESET;}
#define SET_D6_OFF {P3_RESET_DATA_REG=P3_RESET_DATA_Px_6_RESET;}
#define SET_D7_OFF {P3_RESET_DATA_REG=P3_RESET_DATA_Px_7_RESET;}
#define SET_D8_OFF {P1_RESET_DATA_REG=P1_RESET_DATA_Px_5_RESET;}

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef struct LedStatusCtrlType{
  rsuint8 CmdIdx;
  LedFlashingPatternType LedFLashingPattern;
}LedStatusCtrlType;

typedef struct LedStatusType{
  rsuint8 LedStatusMarker;
  LedStatusCtrlType LedStatusCtrl[MEM_LED_NUM];
}LedStatusType;

/****************************************************************************
*                            Global variables/const
****************************************************************************/

/****************************************************************************
*                            Local variables/const
****************************************************************************/
static const LedFlashingCmdType LedFlashingCmdTable[LED_FLASHING_PATTERN_TOTAL]=
{
  {1,{{ALC_LED_OFF, 0}                                                                                          }},//LED_FLASHING_PATTERN_OFF,
  {1,{{ALC_LED_ON, 0}                                                                                           }},//LED_FLASHING_PATTERN_ON,
  {3,{{ALC_LED_ON, 1000},{ALC_LED_OFF, 1000},{ALC_REPEAT_SEQUENCE, 0xFFFF}                                      }},//LED_FLASHING_PATTERN_SLOW,
  {3,{{ALC_LED_ON, 100}, {ALC_LED_OFF, 100}, {ALC_REPEAT_SEQUENCE, 0xFFFF}                                      }},//LED_FLASHING_PATTERN_FAST,
  {6,{{ALC_LED_ON, 100}, {ALC_LED_OFF, 100}, {ALC_LED_ON, 100}, {ALC_LED_OFF, 700},{ALC_REPEAT_SEQUENCE, 0xFFFF}}} //LED_FLASHING_PATTERN_ALERTING,
};

static LedStatusType LedStatus;

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
/****************************************************************************
* FUNCTION:      RevertApiLedCommand
* DESCRIPTION:   revert Api LED command, for Dialog hardware only
****************************************************************************/
static void RevertApiLedCommand(LedFlashingCmdType *LedFlashingCmdPtr)
{
  rsuint8 i;

  for(i=0;i<LedFlashingCmdPtr->CommandsCount;i++)
  {
    if(LedFlashingCmdPtr->Commands[i].Command==ALC_LED_OFF)
      LedFlashingCmdPtr->Commands[i].Command=ALC_LED_ON;
    else if(LedFlashingCmdPtr->Commands[i].Command==ALC_LED_ON)
      LedFlashingCmdPtr->Commands[i].Command=ALC_LED_OFF;
  }
}

/****************************************************************************
* FUNCTION:      LedCtrlSwitchPinIO
* DESCRIPTION:   Switch LED control pins to output
****************************************************************************/
void LedCtrlSwitchPinIO(void)
{
  P1_DIR_REG |= (P1_DIR_Px_5_DIR);
  P2_DIR_REG |= (P2_DIR_Px_1_DIR|P2_DIR_Px_6_DIR);
  P3_DIR_REG |= (P3_DIR_Px_3_DIR|P3_DIR_Px_4_DIR|P3_DIR_Px_5_DIR|P3_DIR_Px_6_DIR|P3_DIR_Px_7_DIR);

  P2_MODE_REG &= ~(P2_MODE_P2_1_MODE|P2_MODE_P2_6_MODE);
  P3_MODE_REG &= ~(P3_MODE_P3_3_MODE|P3_MODE_P3_4_MODE|P3_MODE_P3_5_MODE|P3_MODE_P3_6_MODE|P3_MODE_P3_7_MODE);
}

/****************************************************************************
* FUNCTION:      LedCtrlHwInit
* DESCRIPTION:   Initialization of the LED hardware
****************************************************************************/
static void LedCtrlInitHw(void)
{
  PAD_CTRL_REG &= ~PAD_CTRL_P21_OD;
  LedCtrlSwitchPinIO();
}

/****************************************************************************
* FUNCTION:      LedCtrlShowStatus
* DESCRIPTION:   show the LED status according to the status marker
****************************************************************************/
void LedCtrlShowStatus(void)
{
  rsuint8 i;

  for(i=0;i<MEM_LED_NUM;i++)
  {
    switch(i)
    {
      case MMI_LED_1:
        if(LedStatus.LedStatusMarker&(1<<i))
        {
          SET_D1_ON;
        }
        else
        {
          SET_D1_OFF;
        }
        break;

      case MMI_LED_2:
        if(LedStatus.LedStatusMarker&(1<<i))
        {
          SET_D2_ON;
        }
        else
        {
          SET_D2_OFF;
        }
        break;

      case MMI_LED_3:
        if(LedStatus.LedStatusMarker&(1<<i))
        {
          SET_D3_ON;
        }
        else
        {
          SET_D3_OFF;
        }
        break;

      case MMI_LED_4:
        if(LedStatus.LedStatusMarker&(1<<i))
        {
          SET_D4_ON;
        }
        else
        {
          SET_D4_OFF;
        }
        break;

      case MMI_LED_5:
        if(LedStatus.LedStatusMarker&(1<<i))
        {
          SET_D5_ON;
        }
        else
        {
          SET_D5_OFF;
        }
        break;

      case MMI_LED_6:
        if(LedStatus.LedStatusMarker&(1<<i))
        {
          SET_D6_ON;
        }
        else
        {
          SET_D6_OFF;
        }
        break;

      case MMI_LED_7:
        if(LedStatus.LedStatusMarker&(1<<i))
        {
          SET_D7_ON;
        }
        else
        {
          SET_D7_OFF;
        }
        break;

      case MMI_LED_8:
        if(LedStatus.LedStatusMarker&(1<<i))
        {
          SET_D8_ON;
        }
        else
        {
          SET_D8_OFF;
        }
        break;
    }
  }
}

/****************************************************************************
* FUNCTION:      LedCtrlStartFlashing
* DESCRIPTION:
****************************************************************************/
static void LedCtrlUpdateStatus(ApiLedType led)
{
  #define LedFLashingPattern  (LedStatus.LedStatusCtrl[MMI_LED_ID(led)].LedFLashingPattern)
  #define CmdIdx              (LedStatus.LedStatusCtrl[MMI_LED_ID(led)].CmdIdx)

  //if(led>=MMI_LED_ID_OFFSET)
  if(led>=MMI_LED_ID_OFFSET && led<AL_LED_TOTAL)
  {
    if(LedFlashingCmdTable[LedFLashingPattern].Commands[CmdIdx].Command==ALC_LED_ON)
    {
      LedStatus.LedStatusMarker |= (1 << MMI_LED_ID(led));
    }
    else
    {
      LedStatus.LedStatusMarker &= ~(1 << MMI_LED_ID(led));
    }
    LedCtrlShowStatus();                                                                  //show the status right away

    if(LedFlashingCmdTable[LedFLashingPattern].Commands[CmdIdx].Duration != 0)            //should ensure that it is not 0xFFFF also
    {
      RosTimerStart(LED1_FLASH_TIMER+MMI_LED_ID(led),                                     //start flashing timer
                    LedFlashingCmdTable[LedFLashingPattern].Commands[CmdIdx].Duration,
                    &ColaTimerCfgTable[ColaTimerCfgTableIdx(LED1_FLASH_TIMER+MMI_LED_ID(led))]);
    }
  }

  #undef LedFLashingPattern
  #undef CmdIdx
}

/****************************************************************************
* FUNCTION:      LedCtrlInit
* DESCRIPTION:   Initialization of the LED Ctrl structure
****************************************************************************/
void LedCtrlInit(void)
{
  LedCtrlInitHw();
  util_memset((void *)&LedStatus, 0, sizeof(LedStatusType));
  LedCtrlShowStatus();
}

/****************************************************************************
* FUNCTION:      LedCtrlSet
* DESCRIPTION:   Function to change a specific LED status
****************************************************************************/
void LedCtrlSet(ApiLedType led, LedFlashingPatternType flashingPattern)
{
  if(led<AL_SYS_LED_TOTAL)
  {
#ifdef RTX_DEV_BOARD  //for Dialog board the logic of AL_LED3 is just opposite
    SendApiFpSetLedReq(COLA_TASK, led, LedFlashingCmdTable[flashingPattern].CommandsCount, (ApiLedCommandType *)(LedFlashingCmdTable[flashingPattern].Commands));
#else                 //Need to revert the LED logic if it is to control AL_LED3
    LedFlashingCmdType *LedFlashingCmdPtr=(LedFlashingCmdType*)RcHeapAllocEx(sizeof(LedFlashingCmdType), RHF_NULL_ON_FULL);

    util_memcpy(LedFlashingCmdPtr,(LedFlashingCmdType *)(&LedFlashingCmdTable[flashingPattern]),sizeof(LedFlashingCmdType));
#ifdef NATALIE_V11
    SendApiHalLedReq(COLA_TASK, led, LedFlashingCmdPtr->CommandsCount, (ApiLedCommandType *)(LedFlashingCmdPtr->Commands));
#else
    RevertApiLedCommand(LedFlashingCmdPtr);
    SendApiFpSetLedReq(COLA_TASK, led, LedFlashingCmdPtr->CommandsCount, (ApiLedCommandType *)(LedFlashingCmdPtr->Commands));
#endif
    RcHeapFreeEx(LedFlashingCmdPtr, RHF_NULL_ON_FULL);
#endif //RTX_DEV_BOARD
  }
  //else
  else if(led<AL_LED_TOTAL)
  {
    if(LedStatus.LedStatusCtrl[MMI_LED_ID(led)].LedFLashingPattern == flashingPattern)    //if not changed, do nothing
      return;

    RosTimerStop(LED1_FLASH_TIMER+MMI_LED_ID(led));         //Stop the specific LED flashing Timer first

    LedStatus.LedStatusCtrl[MMI_LED_ID(led)].CmdIdx=0;
    LedStatus.LedStatusCtrl[MMI_LED_ID(led)].LedFLashingPattern=flashingPattern;
    LedCtrlUpdateStatus(led);                               //update LED status
  }
}

/****************************************************************************
* FUNCTION:      LedCtrlFlashingTimerTimeOut
* DESCRIPTION:   When a LED flashing Timer Timeout,
****************************************************************************/
void LedCtrlFlashingTimerTimeOut(RosTimerIdType LedFlashingTimerId)
{
  #define LedFLashingPattern  (LedStatus.LedStatusCtrl[LedIdx].LedFLashingPattern)
  #define CmdIdx              (LedStatus.LedStatusCtrl[LedIdx].CmdIdx)

  rsuint8 LedIdx=LedFlashingTimerId-LED1_FLASH_TIMER;

  if(CmdIdx+1<LedFlashingCmdTable[LedFLashingPattern].CommandsCount)
  {
    CmdIdx++;
  }

  if(LedFlashingCmdTable[LedFLashingPattern].Commands[CmdIdx].Command==ALC_REPEAT_SEQUENCE)
  {
    CmdIdx=0;
  }
  LedCtrlUpdateStatus(LedIdx+MMI_LED_ID_OFFSET);                               //update LED status

  #undef LedFLashingPattern
  #undef CmdIdx
}
// End of file.

