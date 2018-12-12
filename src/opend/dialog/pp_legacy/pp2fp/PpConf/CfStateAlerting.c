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
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include "system.h"
#include "CfState.h"
#include "LedCtrl.h"
#include "ApiHelper.h"
#include "Util.h"
#include "MmiCtrl.h"
#include <AudioCfg/MelodyTab.h>

#include "keyMessage.h"

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
****************************************************************************/

/*************************************************************************
* FUNCTION:         S_CfStateAlerting
* INPUTS:           CfMailType *p_Mail
* OUTPUTS:          none
* DESCRIPTION:      State function, called when system is in "Alerting" state.
*                   When PP is called it will enter Alerting state, the paging
*                   is answered, it will enter "Connected" state
*************************************************************************/
DECL_STATE_FN(S_CfStateAlerting)
{
  switch (((RosMailType *)p_Mail)->Primitive)
  {
    case CF_S_ENTER:
      VolAdjustDir = 1;                                                         //default volume adjust direction: incrementing
      MmiShowLedStatus();
      RosTimerStart(CONNECTION_TIMER, CONNECTION_TIMEOUT, &ColaTimerCfgTable[ColaTimerCfgTableIdx(CONNECTION_TIMER)]);            //start a connection timer
      break;

    case API_CC_CONNECT_CFM:                                                    //enter "Connected" state
      pCfSysCtrl->PpSysPara.AudioMode=API_AUDIO_MODE_HEADSET;
      SendApiPpAudioSetVolumeReq(COLA_TASK, 0);                                 //Set volume
      SendApiPpAudioOpenReq ( COLA_TASK, pCfSysCtrl->PpSysPara.AudioMode );     //Open and unmute Audio
      CfEnterState(CF_STATE_CONNECTED);
      break;

    case KEY_MESSAGE:
      switch(((RosMailType *)p_Mail)->P1.P1)
      {
        case KEY_HOOK:                                                          //for test purpose, use Hook On Key to stop the connection
          HandleConnectReq();
          break;
      }
      break;

    case TIMEOUT:
      break;

    case API_CC_INFO_IND:
      MmiHandleIntCallingPartyNumber(((ApiCcInfoIndType *)p_Mail)->InfoElement, ((ApiCcInfoIndType *)p_Mail)->InfoElementLength);
      MmiShowLedStatus();
      break;

    case API_CC_RELEASE_IND:
      SendApiCcReleaseRes ( COLA_TASK,                                          //RosTaskIdType Src,
                            pCfSysCtrl->PpSysPara.CallCtrlPara.ConEi,           //ApiCcConEiType ConEi,
                            0,                                                  //rsuint16 InfoElementLength,
                            NULL);                                              //rsuint8 InfoElement[1];

     //intentionally fall through

    case API_CC_RELEASE_CFM:
    case API_CC_REJECT_IND:
      CfEnterState(CF_STATE_STANDBY);
      break;

    case CF_S_LEAVE:
      SendApiPpAudioStopToneReq( COLA_TASK );
      RosTimerStop(CONNECTION_TIMER);
      break;

    default:
      return;
      break;
  }
}


// End of file.

