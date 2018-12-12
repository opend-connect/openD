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

#include "keyMessage.h"


#include "opend_call.h"

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
* FUNCTION:         S_CfStateConnecting
* INPUTS:           CfMailType *p_Mail
* OUTPUTS:          none
* DESCRIPTION:      State function, called when system is in "Connecting" state
*************************************************************************/
DECL_STATE_FN(S_CfStateConnecting)
{
  openD_callApiCfm_t cConfirm;

  switch (((RosMailType *)p_Mail)->Primitive)
  {
    case CF_S_ENTER:
      MmiShowLedStatus();
      SendApiCcGetConeiReq( COLA_TASK );
      // RosTimerStart(CONNECTION_TIMER, CONNECTION_TIMEOUT, &ColaTimerCfgTable[ColaTimerCfgTableIdx(CONNECTION_TIMER)]);
      break;

    case API_CC_GET_CONEI_CFM:

      // pCfSysCtrl->PpSysPara.AudioMode=API_AUDIO_MODE_HEADSET;
      // SendApiPpAudioSetVolumeReq(COLA_TASK, 0);                       //Set volume
      // SendApiPpAudioOpenReq(COLA_TASK, pCfSysCtrl->PpSysPara.AudioMode);

      // SendApiPpAudioSetVolumeReq(COLA_TASK, pCfSysCtrl->PpSysPara.PpMmiPara.MmiAudioVol);       //Set volume
      // SendApiPpAudioUnmuteReq(COLA_TASK, API_MUTE_BOTH);                                        //ApiPpAudioMuteRxTxType MuteRxTx

      if( '6' == pCfSysCtrl->PpSysPara.DestHsId ) {
        pCfSysCtrl->PpSysPara.MmiConEi=((ApiCcGetConeiCfmType *)p_Mail)->ConEi;
        SetupExtOutgoingCall( pCfSysCtrl->PpSysPara.MmiConEi, '0' );
      } else {
        SetupIntOutgoingCall( ((ApiCcGetConeiCfmType *)p_Mail)->ConEi, pCfSysCtrl->PpSysPara.DestHsId-'0' );
      }
      break;

    case API_CC_SETUP_ACK_IND: //overlap sending waiting for dial digits
      //set audio Mode
      pCfSysCtrl->PpSysPara.AudioMode=API_AUDIO_MODE_HEADSET;
      SendApiPpAudioSetVolumeReq(COLA_TASK, 0);                       //Set volume
      SendApiPpAudioOpenReq(COLA_TASK, pCfSysCtrl->PpSysPara.AudioMode);
      SendApiPpAudioUnmuteReq(COLA_TASK, API_MUTE_BOTH);                                        //ApiPpAudioMuteRxTxType MuteRxTx

      CfEnterState(CF_STATE_CONNECTED);
      break;

    case API_CC_CONNECT_IND:
      //set audio Mode
      pCfSysCtrl->PpSysPara.AudioMode=API_AUDIO_MODE_HEADSET;
      SendApiPpAudioSetVolumeReq(COLA_TASK, 0);                       //Set volume
      SendApiPpAudioOpenReq(COLA_TASK, pCfSysCtrl->PpSysPara.AudioMode);
      SendApiPpAudioUnmuteReq(COLA_TASK, API_MUTE_BOTH);

      CfEnterState(CF_STATE_CONNECTED);
      break;

    case TIMEOUT:
      switch (((RosMailType*)p_Mail)->Timeout.Parameter)
      {
        case CONNECTION_TIMER:
          SendApiCcReleaseReq ( COLA_TASK,                          //RosTaskIdType Src,
                                  pCfSysCtrl->PpSysPara.MmiConEi,     //ApiCcConEiType ConEi,
                                  API_RR_NORMAL,                      //ApiCcReleaseReasonType Reason,
                                  0,                                  //tsuint16 InfoElementLength,
                                  NULL );                             //tsuint8 InfoElement[1])

          CfEnterState(CF_STATE_STANDBY);

          /* Send openD call confirmation to the application. */
          cConfirm.service = OPEND_CALLAPI_SETUP;
          cConfirm.status = OPEND_STATUS_FAIL;
          openD_call_confirmation( &cConfirm );
          break;
      }
      break;

    case API_CC_RELEASE_IND: // just in case
       SendApiCcReleaseRes ( COLA_TASK,                               //RosTaskIdType Src,
                             pCfSysCtrl->PpSysPara.MmiConEi,          //ApiCcConEiType ConEi,
                             0,                                       //rsuint16 InfoElementLength,
                             NULL);                        //rsuint8 InfoElement[1];

    //intentionally fall through
    case API_CC_RELEASE_CFM:
    case API_CC_REJECT_IND:
      CfEnterState(CF_STATE_STANDBY);

      /* Send openD call confirmation to the application. */
      cConfirm.service = OPEND_CALLAPI_SETUP;
      cConfirm.status = OPEND_STATUS_FAIL;
      openD_call_confirmation( &cConfirm );
      break;

    case CF_S_LEAVE:
      RosTimerStop(CONNECTION_TIMER);
      break;
  }
}


// End of file.

