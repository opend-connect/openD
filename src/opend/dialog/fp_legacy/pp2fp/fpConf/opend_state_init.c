#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_state_init.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD legacy call implementation of initialization state.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include "CfState.h"
#include "ApiHelper.h"
#include "CallCtrl.h"
#include "LineCtrl.h"
#include "Util.h"

#include "opend_mgmt.h"

#include "opend_states.h"
#include "msManager.h"

#include <stdbool.h>


typedef enum {
  INIT_SUB_STATE_NULL = 0U,
  INIT_SUB_STATE_01,
  INIT_SUB_STATE_02,
  INIT_SUB_STATE_03,
} subState_t;

static subState_t _subState = INIT_SUB_STATE_NULL;


static void _init_sub_state_01( void *param );
static void _init_sub_state_02( void *param );
static void _init_sub_state_03( void *param );

static void _init_sub_state_01( void *param ) {

  if( !param ) {
    return;
  }

  /* DIALOG - Primitive */
  switch (((RosMailType *)param)->Primitive)
  {
    case CF_S_TIMEOUT:
      break;

    case API_FP_AUDIO_UNMUTE_CFM:
      SendApiFpMmGetRegistrationCountReq ( COLA_TASK , 1);
      SendApiFpMmGetModelReq ( COLA_TASK );
      SendApiFpMmGetIdReq ( COLA_TASK );
      SendApiFpMmGetAccessCodeReq ( COLA_TASK );
      SendApiFpMacNoEmissionModeDisableReq ( COLA_TASK );

      pCfSysCtrl->LasCurrentListIdentifier = API_LAS_INTERNAL_NAMES;

      SendApiLasStartSessionReq ( COLA_TASK,
                                  pCfSysCtrl->LasCurrentListIdentifier,
                                                          // ListIdentifier,
                                  0,                      //InfoElementLength,
                                  NULL                    //rsuint8 InfoElement[1])
                                );

      _subState = INIT_SUB_STATE_02;
      break;

    default:
      break;
  }
}

static void _init_sub_state_02( void *param ) {

  uint8_t i;

  if( !param ) {
    return;
  }

  /* DIALOG - Primitive */
  switch (((RosMailType *)param)->Primitive)
  {
    case API_FP_GET_FW_VERSION_CFM:
      break;

    case API_FP_MM_GET_MODEL_CFM:
      if( ((ApiFpMmGetModelCfmType*)param)->Status == RSS_SUCCESS )
      {
        pCfSysCtrl->FpModelId = ((ApiFpMmGetModelCfmType*)param)->ModelId;
      }
      break;

    case API_FP_MM_GET_ID_CFM:
      if( ((ApiFpMmGetIdCfmType*)param)->Status == RSS_SUCCESS )
      {
        util_memcpy(pCfSysCtrl->Fpui, ((ApiFpMmGetIdCfmType*)param)->Id, 5);
      }
      break;

    case API_FP_MM_GET_ACCESS_CODE_CFM:
      if( ((ApiFpMmGetAccessCodeCfmType*)param)->Status == RSS_SUCCESS )
      {
        util_memcpy(pCfSysCtrl->Ac, ((ApiFpMmGetAccessCodeCfmType*)param)->Ac, 4);
      }
      break;

    case API_LAS_START_SESSION_CFM:
      if(((ApiLasStartSessionCfmType*)param)->ListIdentifier == pCfSysCtrl->LasCurrentListIdentifier )
      {
        pCfSysCtrl->LasSessionData[pCfSysCtrl->LasCurrentListIdentifier].SessionId = ((ApiLasStartSessionCfmType*)param)->SessionIdentifier;
        SendApiLasEndSessionReq( COLA_TASK, pCfSysCtrl->LasSessionData[pCfSysCtrl->LasCurrentListIdentifier].SessionId);
      }
      break;


    case API_FP_MM_GET_REGISTRATION_COUNT_CFM:
#ifdef NATALIE_V11
      pCfSysCtrl->CfSysStatus.RegHsNum = (((ApiFpMmGetRegistrationCountCfmType *)param)->TerminalIdCount);
      for( i=0; i<pCfSysCtrl->CfSysStatus.RegHsNum; i++)
      {
        pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmGetRegistrationCountCfmType *)param)->TerminalId[i]].Registered = 1;
        SendApiFpMmGetHandsetIpuiReq( COLA_TASK, ((ApiFpMmGetRegistrationCountCfmType *)param)->TerminalId[i]);
        CfSetCallState(((ApiFpMmGetRegistrationCountCfmType *)param)->TerminalId[i], F00_NULL);
      }
#else
      pCfSysCtrl->CfSysStatus.RegHsNum = (((ApiFpMmGetRegistrationCountCfmType *)param)->HandsetIdLength);
      for( i=0; i<pCfSysCtrl->CfSysStatus.RegHsNum; i++)
      {
        pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmGetRegistrationCountCfmType *)param)->HandsetId[i]].Registered = 1;
        SendApiFpMmGetHandsetIpuiReq( COLA_TASK, ((ApiFpMmGetRegistrationCountCfmType *)param)->HandsetId[i]);
        CfSetCallState(((ApiFpMmGetRegistrationCountCfmType *)param)->HandsetId[i], F00_NULL);
      }
#endif
      break;

    case API_FP_MM_GET_HANDSET_IPUI_CFM:
      if( ((ApiFpMmGetHandsetIpuiCfmType*)param)->Status == RSS_SUCCESS )
      {
#ifdef NATALIE_V11
        memcpy(pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmGetHandsetIpuiCfmType*)param)->TerminalId].Ipui,((ApiFpMmGetHandsetIpuiCfmType*)param)->IPUI, 5);
#else
        memcpy(pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmGetHandsetIpuiCfmType*)param)->HandsetId].Ipui,((ApiFpMmGetHandsetIpuiCfmType*)param)->IPUI, 5);
#endif
      }
      break;

    case API_LAS_END_SESSION_CFM:
#ifdef NATALIE_V11
        SendApiFpMmStartProtocolReq(COLA_TASK);
        LineCtrlInit();
#else
      HostLasInitialzeLineSettings();
#endif
      _subState = INIT_SUB_STATE_03;
      break;
  }
}

static void _init_sub_state_03( void *param ) {

  uint8_t i;
  openD_mgmtApiCfm_t mConfirm;

  if( !param ) {
    return;
  }

  /* DIALOG - Primitive */
  switch (((RosMailType *)param)->Primitive)
  {
    case API_LAS_START_SESSION_CFM:
    case API_LAS_SAVE_ENTRY_CFM:
    case API_LAS_DATA_PACKET_IND:
      HostLasTask((RosMailType *)param);
      break;

    case API_LAS_END_SESSION_CFM:
      for(i=0;i<=API_LAS_ALL_INCOMING_CALLS;i++)
        ClearLasSessionData(i);
      SendApiFpMmStartProtocolReq(COLA_TASK);
      LineCtrlInit();
      break;


    case API_FP_INIT_PCM_CFM:
      if( ((ApiFpInitPcmCfmType*)param)->Status == RSS_SUCCESS )
      {
        pCfSysCtrl->CfSysStatus.CfSysFlag.PcmInited=TRUE;
      }

      /* Send openD subscription confirmation to the application. */
      mConfirm.service = OPEND_MGMTAPI_INIT;
      mConfirm.status = OPEND_STATUS_OK;
      openD_mgmt_confirmation( &mConfirm );

      /* Change to standby state. */
      msManager_changeState( &opendStateCtxt, OPEND_STATE_STANDBY );
      _subState = INIT_SUB_STATE_NULL;
      break;

  }
}

bool opend_state_init( void *param ) {

  if( !param ) {
    return false;
  }

  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      /* Initialization state. */
      _subState = INIT_SUB_STATE_01;
      SendApiFpSetFeaturesReq(COLA_TASK, API_FP_EXTENDED_TERMINAL_ID_SUPPORT);
      SendApiFpAudioUnmuteReq(COLA_TASK, 0, API_FP_MUTE_BOTH);
      SendApiFpAudioUnmuteReq(COLA_TASK, 1, API_FP_MUTE_BOTH);
      SendApiFpAudioUnmuteReq(COLA_TASK, 2, API_FP_MUTE_BOTH);
      SendApiFpAudioUnmuteReq(COLA_TASK, 3, API_FP_MUTE_BOTH);
      break;

    case MESSAGE_PRIMITIVE_CFM_IND:

      switch ( _subState ) {
        case INIT_SUB_STATE_01:
          _init_sub_state_01( message->param );
          break;

        case INIT_SUB_STATE_02:
          _init_sub_state_02( message->param );
          break;

        case INIT_SUB_STATE_03:
          _init_sub_state_03( message->param );
          break;

        default:
          break;
      }

      break;

    default:
      break;
  }

  return true;
}

#ifdef __cplusplus
}
#endif
