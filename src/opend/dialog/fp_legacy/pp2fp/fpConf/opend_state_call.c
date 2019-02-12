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
#include "CfState.h"
#include "CallCtrl.h"
#include "LineCtrl.h"
#include "LedCtrl.h"
#include "MmiCtrl.h"
#include <SOC/SC14441/Registers.h>

#include "keyMessage.h"

#include "opend.h"
#include "opend_audio.h"
#include "opend_call.h"

#include "opend_states.h"
#include "msManager.h"
/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/
CallStateInfoType CallState[NO_HANDSETS]; // HandsetId [1;6]
ApiLineIdType LineIdReq;
rsuint8 VolAdjustDir;
/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/
#ifdef FP_AUDIO_SUPPORT
void AudioFpOff( void );
void AudioFpSetup(ApiPpAudioModeType AudioMode);
#endif //FP_AUDIO_SUPPORT
/****************************************************************************
*                                Implementation
***************************************************************************/
static bool _message_primitive_user_audio( void *param ) {

  openD_audioApiCfm_t aConfirm;
  bool ret = true;

  if( !param ) {
    return false;
  }


  switch(((openD_audioApiReq_t *)param)->service)
  {
    case OPEND_AUDIOAPI_SET_VOLUME:
      /* Send openD audio confirmation to the application. */
      aConfirm.service = OPEND_AUDIOAPI_SET_VOLUME;
      aConfirm.status = OPEND_STATUS_FAIL;
      openD_audio_confirmation( &aConfirm );
      break;

    case OPEND_AUDIOAPI_SET_MUTE:

      if( ((openD_audioApiReq_t *)param)->param.setMute.enable ) {
        SendApiFpAudioMuteReq(COLA_TASK, 0, API_FP_MUTE_BOTH);
      } else {
        SendApiFpAudioUnmuteReq(COLA_TASK, 0, API_FP_MUTE_BOTH);
      }

      /* Send openD audio confirmation to the application. */
      aConfirm.service = OPEND_AUDIOAPI_SET_MUTE;
      aConfirm.status = OPEND_STATUS_OK;
      openD_audio_confirmation( &aConfirm );
      break;

    default:
      ret = false;
      break;
  }

  return ret;
}

static bool _message_primitive_user_call( void *param ) {

  bool ret = true;

  if( !param ) {
    return false;
  }

  rsuint8 handsetId = 0;

  switch(((openD_callApiReq_t *)param)->service)
  {
    case OPEND_CALLAPI_RELEASE:
      handsetId = ( ((openD_callApiReq_t *)param)->param.setup.pmid[1] ) - '0';
      /* Release connection. */
      SendApiFpCcReleaseReq ( COLA_TASK,
                             CallState[handsetId].CallReference,    //ApiCallReferenceType
                             API_RR_NORMAL,                         //ApiCcReleaseReasonType Reason,
                             0,                                     //tsuint16 InfoElementLength,
                             NULL);                                 //tsuint8 InfoElement[1])
      break;

    default:
      ret = false;
      break;
  }

  return ret;
}

static bool _message_primitive_cfm_ind( void *param ) {

  openD_callApiInd_t cIndication;
  openD_callApiCfm_t cConfirm;

  switch(((RosMailType *)param)->Primitive)
  {
#ifdef FP_AUDIO_SUPPORT
    case API_FP_AUDIO_INTERNAL_CODEC_SETUP_CFM:
      switch (pCfSysCtrl->CfSysStatus.AudioMode) {
        case API_AUDIO_MODE_EARPIECE:
          CODEC_LSR_REG = (CODEC_LSR_REG & 0xFFE4) | 0x0012; //patch for the DIFF mode
          break;
        case API_AUDIO_MODE_HANDSFREE:
        default:
          CLK_CODEC_REG = (CLK_CODEC_REG & 0xEFFF); //ClassD input to DSP_CODEC_OUT_REG
          break;
      }
      break;

#endif
    case API_FP_MM_SET_REGISTRATION_MODE_CFM:
      break;

    case API_FP_CC_RELEASE_CFM:
      CallCtrlMailHandler((RosMailType *)param);

      /* Send openD call confirmation to the application. */
      cConfirm.service = OPEND_CALLAPI_RELEASE;
      cConfirm.status = OPEND_STATUS_OK;
      openD_call_confirmation( &cConfirm );
      // break;

    case API_FP_CC_REJECT_IND:
    case API_FP_CC_RELEASE_IND:
      {
        rsuint8 LineUserNo, LineId;
#ifdef NATALIE_V11
        LineId = CfGetLineId(((ApiFpCcReleaseIndType *)param)->CallReference.Instance.Host);
#else
        LineId = CfGetLineId(((ApiFpCcReleaseIndType *)param)->CallReference.HandsetId);
#endif
        LineUserNo = CfGetLineUserNo(LineId);

        CallCtrlMailHandler((RosMailType *)param);

        /* Audio off. */
        AudioFpOff();

        // if( LineUserNo == 1 ) {
          /* Change to standby state. */
          msManager_changeState( &opendStateCtxt, OPEND_STATE_STANDBY );

          /* Send openD call indication to the application. */
          cIndication.service = OPEND_CALLAPI_RELEASE;
          openD_call_indication( &cIndication );
        // } else {
        //   printf("No state change to standby, because a other line is active.\n");
        // }
      }
      break;

    case API_FP_CC_MODIFY_CODEC_IND:
      {
        ApiCallReferenceType HsId;
#ifdef NATALIE_V11
        HsId = ((ApiFpCcModifyCodecIndType*)param)->CallReference;
#else
        HsId.HandsetId = ((ApiFpCcModifyCodecIndType*)param)->CallReference.HandsetId;
#endif
        SendApiFpCcModifyCodecRes(COLA_TASK, HsId, RSS_REJECTED);
      }
      break;
  }

  return true;
}


bool opend_state_call( void *param ) {

  openD_callApiInd_t cIndication;
  bool ret = true;

  if( !param ) {
    return false;
  }

  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      /* Initialization state. */
      printf("State - CALL\n");

#ifdef FP_AUDIO_SUPPORT
      pCfSysCtrl->CfSysStatus.AudioMode = API_AUDIO_MODE_HEADSET;
      AudioFpSetup(pCfSysCtrl->CfSysStatus.AudioMode);
#endif /* FP_AUDIO_SUPPORT */
      MmiShowLedStatus();
      break;

    case MESSAGE_PRIMITIVE_USER:
      if( !((openD_Api_t *)message->param) ) {
        return false;
      }

      switch( ((openD_Api_t *)message->param)->opendApis ) {
        case OPEND_APIS_AUDIO:
          ret = _message_primitive_user_audio( ((openD_Api_t *)message->param)->param );
          break;

        case OPEND_APIS_CALL:
          ret = _message_primitive_user_call( ((openD_Api_t *)message->param)->param );
          break;

        default:
          break;
      }
      break;

    case MESSAGE_PRIMITIVE_CFM_IND:
      ret = _message_primitive_cfm_ind( message->param );
      break;

    default:
      break;
  }
  return ret;
}


#ifdef FP_AUDIO_SUPPORT

void AudioFpOff() {

  SendApiFpAudioInternalCodecSetupReq(
      COLA_TASK,
      0,                       // 0 = power off 1 = power on
      16,                      // SampleFreq
      API_AUDIO_IOMODE_OFF,    // MicMode
      API_AUDIO_IOMODE_OFF,    // MicHeadsetMode
      API_AUDIO_IOMODE_OFF,    // LsrMode
      API_AUDIO_IOMODE_OFF     // ClassDMode
  );
}

void AudioFpSetup(ApiPpAudioModeType AudioMode){
	switch (AudioMode){
	case API_AUDIO_MODE_EARPIECE:
		SendApiFpAudioInternalCodecSetupReq(
				COLA_TASK,
				1,                                // 0 = power off 1 = power on
				16,                               // SampleFreq
				API_AUDIO_IOMODE_DIFF,            // MicMode
				API_AUDIO_IOMODE_OFF,             // MicHeadsetMode
				API_AUDIO_IOMODE_DIFF,            // LsrMode
				//          #ifdef USE_CLASSD_DIFFERENTIAL
				//                          API_AUDIO_IOMODE_DIFF             // ClassDMode
				//          #else
				API_AUDIO_IOMODE_OFF              // ClassDMode
				//          #endif
		);

		//CODEC_LSR_REG = (CODEC_LSR_REG & 0xff74) | 0x0012;   //patch for the DIFF mode
		break;

	case API_AUDIO_MODE_HEADSET:
		SendApiFpAudioInternalCodecSetupReq(
				COLA_TASK,
				1,                           // 0 = power off 1 = power on
				16,                          // SampleFreq
				API_AUDIO_IOMODE_OFF,        // MicMode
				API_AUDIO_IOMODE_SE_P_VREFN, // MicHeadsetMode
				API_AUDIO_IOMODE_SE_P_VREFN/*API_AUDIO_IOMODE_SE_N_VREFP*/, // LsrMode
				//          #ifdef USE_CLASSD_DIFFERENTIAL
				//                               API_AUDIO_IOMODE_DIFF        // ClassDMode
				//          #else
				API_AUDIO_IOMODE_OFF         // ClassDMode
				//          #endif
		);
		break;
	case API_AUDIO_MODE_HANDSFREE:
	default:
		SendApiFpAudioInternalCodecSetupReq(
				COLA_TASK,
				1,                           // 0 = power off 1 = power on
				16,                          // SampleFreq
				API_AUDIO_IOMODE_OFF,        // MicMode
				API_AUDIO_IOMODE_SE_P_VREFN, // MicHeadsetMode
				API_AUDIO_IOMODE_SE_P_VREFN/*API_AUDIO_IOMODE_SE_N_VREFP*/, // LsrMode
//#ifdef USE_CLASSD_DIFFERENTIAL
				API_AUDIO_IOMODE_DIFF        // ClassDMode
//#else
//				API_AUDIO_IOMODE_OFF         // ClassDMode
//#endif
		);
		//      #ifdef USE_CLASSD_DIFFERENTIAL
		//CLK_CODEC_REG = (CLK_CODEC_REG & 0xEFFF); //ClassD input to DSP_CODEC_OUT_REG
		//      #endif
		break;
	}
	// Connect PCM0 to Codec
	SendApiFpAudioSetHwSrcReq(
			COLA_TASK,
			0,                  // DestinationId (PCM0-PCM3)
			API_AUDIO_INT_CODEC // PCM or Codec; type: ApiFpAudioHardwareSrcType
	);

	SendApiFpSetAudioFormatReq(
	   COLA_TASK,
	   0,
	   AP_DATA_FORMAT_LINEAR_16kHz
	);
}
#endif //FP_AUDIO_SUPPORT
// End of file.

