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
#include "Util.h"
#include "MmiCtrl.h"

#include "keyMessage.h"


#include "opend_call.h"
#include "opend_audio.h"

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
rsuint8 VolAdjustDir;

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
/*************************************************************************
* FUNCTION:         S_CfStateConnected
* INPUTS:           CfMailType *p_Mail
* OUTPUTS:          none
* DESCRIPTION:      State function, called when system is in "Connected" state.
*************************************************************************/
DECL_STATE_FN(S_CfStateConnected)
{
  openD_callApiCfm_t cConfirm;
  openD_callApiInd_t cIndication;
  openD_audioApiCfm_t aConfirm;

  switch (((RosMailType *)p_Mail)->Primitive)
  {
    case CF_S_ENTER:
      VolAdjustDir = 1;                                                         //volume adjustment: increasing.

      MmiShowLedStatus();

      //Check and Set Volume
      if(pCfSysCtrl->PpSysPara.PpMmiPara.MmiAudioVol>=AUDIO_NUMBER_OF_VOL_STEPS)          //protection
      {
        pCfSysCtrl->PpSysPara.PpMmiPara.MmiAudioVol=(AUDIO_NUMBER_OF_VOL_STEPS/2);
      }

      RosTimerStart(UNMUTE_AUDIO_TIMER, UNMUTE_AUDIO_TIMEOUT, &ColaTimerCfgTable[ColaTimerCfgTableIdx(UNMUTE_AUDIO_TIMER)]);

      CfSetSubState(CF_SUB_STATE_CONNECTED);

      /* Send openD call confirmation to the application. */
      cConfirm.service = OPEND_CALLAPI_SETUP;
      cConfirm.status = OPEND_STATUS_OK;
      openD_call_confirmation( &cConfirm );
      break;

    case KEY_MESSAGE:
      if(CfGetSubState()==CF_SUB_STATE_CONNECTED)                     //Only accept keys when connected
      {
        switch(((RosMailType *)p_Mail)->P1.P1)
        {
          case KEY_HOOK: // hook on
            // release connection (and all instances)
            SendApiCcReleaseReq ( COLA_TASK,                          //RosTaskIdType Src,
                                  pCfSysCtrl->PpSysPara.MmiConEi,     //ApiCcConEiType ConEi,
                                  API_RR_NORMAL,                      //ApiCcReleaseReasonType Reason,
                                  0,                                  //tsuint16 InfoElementLength,
                                  NULL );                             //tsuint8 InfoElement[1])

            SendApiPpAudioStopToneReq ( COLA_TASK );                  //RosTaskIdType Src,
            CfSetSubState(CF_SUB_STATE_RELEASE_PENDING);
            break;

          case KEY_MODE:
            //toggle between the 3 modes
            if(pCfSysCtrl->PpSysPara.AudioMode == API_AUDIO_MODE_HANDSFREE)
            {
              pCfSysCtrl->PpSysPara.AudioMode = API_AUDIO_MODE_EARPIECE;
            }
            else
            {
              pCfSysCtrl->PpSysPara.AudioMode++;
            }
            SendApiPpAudioSetModeReq(COLA_TASK, pCfSysCtrl->PpSysPara.AudioMode);     //Set audio mode
            break;

          case KEY_VOL:
            VolAdjustDir = ((RosMailType *)p_Mail)->P2.P2;
            SendApiPpAudioSetVolumeReq( COLA_TASK, VolAdjustDir );

            /* Send openD audio confirmation to the application. */
            aConfirm.service = OPEND_AUDIOAPI_SET_VOLUME;
            aConfirm.status = OPEND_STATUS_OK;
            openD_audio_confirmation( &aConfirm );
            break;

          case KEY_MESSAGE_REQ_MUTE:
            SendApiPpAudioMuteReq(COLA_TASK, API_MUTE_BOTH);

            /* Send openD audio confirmation to the application. */
            aConfirm.service = OPEND_AUDIOAPI_SET_MUTE;
            aConfirm.status = OPEND_STATUS_OK;
            openD_audio_confirmation( &aConfirm );
            break;

          case KEY_MESSAGE_REQ_UNMUTE:
            SendApiPpAudioUnmuteReq(COLA_TASK, API_MUTE_BOTH);

            /* Send openD audio confirmation to the application. */
            aConfirm.service = OPEND_AUDIOAPI_SET_MUTE;
            aConfirm.status = OPEND_STATUS_OK;
            openD_audio_confirmation( &aConfirm );
            break;

          default:
            break;
        }
      }
      break;

    case TIMEOUT:
      switch (((RosMailType*)p_Mail)->Timeout.Parameter)
      {
        case UNMUTE_AUDIO_TIMER:
          SendApiPpAudioSetVolumeReq(COLA_TASK, VolAdjustDir );       //Set volume
          SendApiPpAudioUnmuteReq(COLA_TASK, API_MUTE_BOTH);                                        //ApiPpAudioMuteRxTxType MuteRxTx
          break;
      }
      break;

    case API_CC_RELEASE_IND: // just in case
       SendApiCcReleaseRes ( COLA_TASK,                               //RosTaskIdType Src,
                             pCfSysCtrl->PpSysPara.MmiConEi,          //ApiCcConEiType ConEi,
                             0,                                       //rsuint16 InfoElementLength,
                             NULL);                                   //rsuint8 InfoElement[1];
      //intentionally fall through
    case API_CC_REJECT_IND:
      CfEnterState(CF_STATE_STANDBY);

      /* Send openD call indication to the application. */
      cIndication.service = OPEND_CALLAPI_RELEASE;
      openD_call_indication( &cIndication );
      break;

    case API_CC_RELEASE_CFM:
      CfEnterState(CF_STATE_STANDBY);

      /* Send openD call confirmation to the application. */
      cConfirm.service = OPEND_CALLAPI_RELEASE;
      cConfirm.status = OPEND_STATUS_OK;
      openD_call_confirmation( &cConfirm );
      break;

    case CF_S_LEAVE:
      SendApiHalWriteReq( COLA_TASK,                                                      //save Audio volume and Audio Mode
                          AHA_NVS,
                          ColaNvsOffset+RSOFFSETOF(PpMmiParaType, MmiAudioVol),
                          sizeof(rsuint8),
                          (rsuint8*)&(pCfSysCtrl->PpSysPara.PpMmiPara.MmiAudioVol));
      break;
  }
}


// End of file.

