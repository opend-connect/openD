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
#include <Ros/RosCfg.h>
#include "system.h"
#include "CfState.h"
#include "CallCtrl.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

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
/****************************************************************************
* FUNCTION:      GetHandsetLedId
* DESCRIPTION:   Get the LED ID corresponding to a handset(HsId starts from 1)
****************************************************************************/
static ApiLedIdType GetHandsetLedId(rsuint8 HsId)
{
  if(HsId>0&&HsId<NO_HANDSETS)
  {
    return(HsId-1+MMI_LED_ID_OFFSET);               //HsId starts from 1
  }
  return(AL_MMI_LED_7);                             //for protection only
}

/****************************************************************************
* FUNCTION:      ShowHsPagingLed
* DESCRIPTION:   Show Handset Paging LED status
****************************************************************************/
//static void ShowHandsetPagingLed(void)
//{
//  rsuint8 i;
//  
//  for (i=1; i<NO_HANDSETS; i++)
//  {
//    if (CallState[i].State == HANDSET_LOCATE)
//    {
//      LedCtrlSet(GetHandsetLedId(i), LED_FLASHING_PATTERN_ALERTING);
//    }
//  }
//}

/****************************************************************************
* FUNCTION:      ShowHsPagingLed
* DESCRIPTION:   Show Handset Paging LED status
****************************************************************************/
static void ShowRegisteredHandsetLed(void)
{
  rsuint8 i;
  
  for (i=1; i<NO_HANDSETS; i++)
  {
    if (pCfSysCtrl->CfSysStatus.HsInfo[i].Registered)
    {
      LedCtrlSet(GetHandsetLedId(i), LED_FLASHING_PATTERN_ON);
    }
    else
    {
      LedCtrlSet(GetHandsetLedId(i), LED_FLASHING_PATTERN_OFF);
    }
  }
}

/****************************************************************************
* FUNCTION:      ShowHsPagingLed
* DESCRIPTION:   Show Handset Paging LED status
****************************************************************************/
static void ShowHandsetConnectedLed(void)
{
  rsuint8 i;
  
  for (i=1; i<NO_HANDSETS; i++)
  {
    if (CallState[i].Connected2Line)
    {
      LedCtrlSet(GetHandsetLedId(i), LED_FLASHING_PATTERN_CONNECTED);
    }
    else if(pCfSysCtrl->CfSysStatus.HsInfo[i].Registered)
    {
      LedCtrlSet(GetHandsetLedId(i), LED_FLASHING_PATTERN_ON);
    }
    else
    {
      LedCtrlSet(GetHandsetLedId(i), LED_FLASHING_PATTERN_OFF);
    }
  }
}

/****************************************************************************
* FUNCTION:      MmiShowLedStatus
* DESCRIPTION:   show status of LED's in different mode
****************************************************************************/
void MmiShowLedStatus(void)
{
  switch(pCfSysCtrl->CfStateCtrl.CfState)
  {
    case CF_STATE_STANDBY:
      {
        if(pCfSysCtrl->CfSysStatus.CfSysFlag.RegEnabled)
        {
          LedCtrlSet(SYSTEM_STATUS_LED, LED_FLASHING_PATTERN_REGISTRATION);         
        }
        else if(pCfSysCtrl->CfSysStatus.CfSysFlag.PageMode)
        {
          LedCtrlSet(SYSTEM_STATUS_LED, LED_FLASHING_PATTERN_ALERTING);          
        }
        else if(pCfSysCtrl->CfSysStatus.RegHsNum>0)
        {
          LedCtrlSet(SYSTEM_STATUS_LED, LED_FLASHING_PATTERN_ON);   //Turn off register/call led;         
        }
        else
        {
          LedCtrlSet(SYSTEM_STATUS_LED, LED_FLASHING_PATTERN_OFF);   //Turn off register/call led           
        }
        ShowRegisteredHandsetLed();
      }
      break;
      
    case CF_STATE_CALL:
      {
        LedCtrlSet(SYSTEM_STATUS_LED, LED_FLASHING_PATTERN_CONNECTED);   //Turn off register/call led
        ShowHandsetConnectedLed();       
      }
      break;
  }
  
}
// End of file.

