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
 * @file       opend_state_standby.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD legacy call implementation of standby state.
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
#include "system.h"
#include "CfState.h"
#include "LineCtrl.h"
#include "CallCtrl.h"
#include "Util.h"
#include "LedCtrl.h"
#include "MmiCtrl.h"
#include "helper.h"

#include "opend_sub.h"
#include "opend_call.h"

#include "opend.h"
#include "opend_states.h"
#include "msManager.h"

#include <stdint.h>
#include <stdbool.h>


ApiCallReferenceType HsId;
ApiTerminalIdType terminalId;
uint8_t ac[4];

bool _message_primitive_user_sub( void *param );
bool _message_primitive_user_call( void *param );
bool _message_primitive_cfm_ind( void *param );

bool _message_primitive_user_sub( void *param ) {

  bool ret = true;
  uint8_t i;
  openD_subApiInd_t sIndication;
  openD_subApiCfm_t sConfirm;

  if( !param ) {
    return false;
  }

  switch(((openD_subApiReq_t *)param)->service)
  {
    case OPEND_SUBAPI_SUBSCRIBE_ENABLE:													//registration key pressed = toggle registration mode
      if((!pCfSysCtrl->CfSysStatus.CfSysFlag.EnterRegModeReq)&&(!pCfSysCtrl->CfSysStatus.CfSysFlag.RegEnabled)) //system is not in registration mode, and no registration request before
      {
        pCfSysCtrl->CfSysStatus.CfSysFlag.EnterRegModeReq = TRUE;   //User has requested to enter Registration Mode
        SendApiFpMmSetRegistrationModeReq(COLA_TASK, TRUE, FALSE);  //Registration request sent
        RosTimerStart(REG_TIMER, REG_TIMEOUT_TIME, &ColaTimerCfgTable[ColaTimerCfgTableIdx(REG_TIMER)]); //start a 3-minute registration timer
      }
      else if((pCfSysCtrl->CfSysStatus.CfSysFlag.EnterRegModeReq)&&(pCfSysCtrl->CfSysStatus.CfSysFlag.RegEnabled)) //system is in registration mode, and a registration request was sent before
      {
        pCfSysCtrl->CfSysStatus.CfSysFlag.EnterRegModeReq = FALSE; //User has requested to enter Registration Mode, and the system is now in
        SendApiFpMmSetRegistrationModeReq(COLA_TASK, FALSE, FALSE);                                                 //If in registration mode, disable Registration
        RosTimerStop(REG_TIMER);
      }
      break;

    case OPEND_SUBAPI_SUBSCRIPTION_DELETE:                                                                                                 //work around: due to the way keyboard driver is designed, a KEY_REG will be received prio to this key
      if((pCfSysCtrl->CfSysStatus.CfSysFlag.EnterRegModeReq)&&(pCfSysCtrl->CfSysStatus.CfSysFlag.RegEnabled))       //need to exit registration mode first
      {
        pCfSysCtrl->CfSysStatus.CfSysFlag.EnterRegModeReq = FALSE;                                                  //User has requested to enter Registration Mode, and the system is now in
        SendApiFpMmSetRegistrationModeReq(COLA_TASK, FALSE, FALSE);                                                 //If in registration mode, disable Registration
        RosTimerStop(REG_TIMER);
      }
                                                                                                                    //Deregistration key pressed, dereg all
      for (i=1; i<NO_HANDSETS; i++)
      {
        if(pCfSysCtrl->CfSysStatus.HsInfo[i].Registered)
        {
          SendApiFpMmDeleteRegistrationReq(COLA_TASK, i);
        }
      }
      break;

    case OPEND_SUBAPI_GET_REGISTRATION_STATE:
      for( i=0; i<NO_HANDSETS; i++)
      {
        if( pCfSysCtrl->CfSysStatus.HsInfo[i].Registered == 1 ) {
          sIndication.service = OPEND_SUBAPI_GET_REGISTRATION_STATE;
          sIndication.param.registrationState.isRegistered = 1;
          sIndication.param.registrationState.pmid[0] = i;
          openD_sub_indication( &sIndication );
        }
      }
      break;

      case OPEND_SUBAPI_SET_AC:
        ac[0] = ((RosMailP5Type *)param)->P2;
        ac[1] = ((RosMailP5Type *)param)->P3;
        ac[2] = ((RosMailP5Type *)param)->P4;
        ac[3] = ((RosMailP5Type *)param)->P5;
        SendApiFpMmSetAccessCodeReq ( COLA_TASK, ac);
        break;

    default:
      ret = false;
      break;
  }

  return ret;
}

bool _message_primitive_user_call( void *param ) {

  bool ret = true;

  if( !param ) {
    return false;
  }

  ApiCallReferenceType CallReference;
  ApiTerminalIdType TerminalId;
  rsuint8 handsetId = 0;

  switch(((openD_callApiReq_t *)param)->service)
  {
    case OPEND_CALLAPI_SETUP:
      terminalId = asciiToHex(((openD_callApiReq_t *)param)->param.setup.pmid[0]);
      CallReference.Instance.Fp = 0;
      CallReference.Instance.Host = terminalId;
      ApiFpCcSetupReq( CallReference, terminalId );

      break;

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

bool _message_primitive_cfm_ind( void *param ) {

  uint8_t i;
  openD_subApiCfm_t sConfirm;
  openD_subApiInd_t sIndication;
  openD_callApiCfm_t cConfirm;
  openD_callApiInd_t cIndication;

  if( !param ) {
    return false;
  }

  switch(((RosMailType *)param)->Primitive)
  {
    case TIMEOUT:
      switch (((RosMailType *)param)->Timeout.Parameter)
      {
        case REG_TIMER:
          pCfSysCtrl->CfSysStatus.CfSysFlag.EnterRegModeReq = FALSE;    //User has requested to enter Registration Mode, and the system is now in
          SendApiFpMmSetRegistrationModeReq(COLA_TASK, FALSE, FALSE);   //Registration timeout, stop registration
          break;
      }
      break;

    case API_FP_MM_DELETE_REGISTRATION_CFM:
      if(((ApiFpMmDeleteRegistrationCfmType*)param)->Status == RSS_SUCCESS)
      {
#ifdef NATALIE_V11
        pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmDeleteRegistrationCfmType*)param)->TerminalId].Registered = FALSE;
#else
        pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmDeleteRegistrationCfmType*)param)->HandsetId].Registered = FALSE;
#endif
        pCfSysCtrl->CfSysStatus.RegHsNum--;
      }

      if(pCfSysCtrl->CfSysStatus.RegHsNum==0)
      {
        MmiShowLedStatus();;
      }

      /* Send openD subscription confirmation to the application. */
      sConfirm.service = OPEND_SUBAPI_SUBSCRIPTION_DELETE;
      sConfirm.status = OPEND_STATUS_OK;
      openD_sub_confirmation( &sConfirm );
      break;

    case API_FP_MM_SET_REGISTRATION_MODE_CFM:
      if(pCfSysCtrl->CfSysStatus.CfSysFlag.EnterRegModeReq)
      {
        pCfSysCtrl->CfSysStatus.CfSysFlag.RegEnabled=TRUE;
      }
      else
      {
        pCfSysCtrl->CfSysStatus.CfSysFlag.RegEnabled=FALSE;
      }

      /* Send openD subscription confirmation to the application. */
      sConfirm.service = OPEND_SUBAPI_SUBSCRIBE_ENABLE;
      sConfirm.status = OPEND_STATUS_OK;
      openD_sub_confirmation( &sConfirm );

      MmiShowLedStatus();
      printf("API_FP_MM_SET_REGISTRATION_MODE_CFM\n");
      break;

    case API_FP_MM_REGISTRATION_COMPLETE_IND:
      pCfSysCtrl->CfSysStatus.CfSysFlag.EnterRegModeReq=FALSE;
#ifdef NATALIE_V11
      SendApiFpMmGetRegistrationCountReq ( COLA_TASK, 1 );
      HostLasAttachHsToAllLines(((ApiFpMmRegistrationCompleteIndType *)param)->TerminalId, FALSE);
#else
      SendApiFpMmGetRegistrationCountReq ( COLA_TASK );
      HostLasAttachHsToAllLines(((ApiFpMmRegistrationCompleteIndType *)param)->HandsetId, FALSE);
#endif
      SendApiFpMmSetRegistrationModeReq(COLA_TASK, FALSE, FALSE);                                   //Exit Registration mode

      printf( "HandsetId: %d - ", ((ApiFpMmRegistrationCompleteIndType *)param)->TerminalId );
      printf( "IPUI: %02x ", pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmRegistrationCompleteIndType *)param)->TerminalId].Ipui[0]);
      printf( "%02x ", pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmRegistrationCompleteIndType *)param)->TerminalId].Ipui[1]);
      printf( "%02x ", pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmRegistrationCompleteIndType *)param)->TerminalId].Ipui[2]);
      printf( "%02x ", pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmRegistrationCompleteIndType *)param)->TerminalId].Ipui[3]);
      printf( "%02x \n", pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmRegistrationCompleteIndType *)param)->TerminalId].Ipui[4]);

      /* Send openD subscription indication to the application. */
      sIndication.service = OPEND_SUBAPI_SUBSCRIBE;
      util_memcpy(sIndication.param.subscribe.ipui, pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmRegistrationCompleteIndType *)param)->TerminalId].Ipui, 5);
      util_memcpy(sIndication.param.subscribe.pmid, &((ApiFpMmRegistrationCompleteIndType *)param)->TerminalId, 1);
      openD_sub_indication( &sIndication );

      MmiShowLedStatus();
      break;

    case API_FP_MM_GET_REGISTRATION_COUNT_CFM:
#ifdef NATALIE_V11
      pCfSysCtrl->CfSysStatus.RegHsNum = (((ApiFpMmGetRegistrationCountCfmType *)param)->TerminalIdCount);
      for( i=0; i<pCfSysCtrl->CfSysStatus.RegHsNum; i++)
      {
        pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmGetRegistrationCountCfmType *)param)->TerminalId[i]].Registered = 1;
        CfSetCallState(((ApiFpMmGetRegistrationCountCfmType *)param)->TerminalId[i], F00_NULL);
        SendApiFpMmGetHandsetIpuiReq( COLA_TASK, ((ApiFpMmGetRegistrationCountCfmType *)param)->TerminalId[i]);
      }
#else
      pCfSysCtrl->CfSysStatus.RegHsNum = (((ApiFpMmGetRegistrationCountCfmType *)param)->HandsetIdLength);
      for( i=0; i<pCfSysCtrl->CfSysStatus.RegHsNum; i++)
      {
        pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmGetRegistrationCountCfmType *)param)->HandsetId[i]].Registered = 1;
        CfSetCallState(((ApiFpMmGetRegistrationCountCfmType *)param)->HandsetId[i], F00_NULL);
        SendApiFpMmGetHandsetIpuiReq( COLA_TASK, ((ApiFpMmGetRegistrationCountCfmType *)param)->HandsetId[i]);
      }
#endif
      MmiShowLedStatus();
      break;

    case API_FP_MM_GET_HANDSET_IPUI_CFM:
      if( ((ApiFpMmGetHandsetIpuiCfmType*)param)->Status == RSS_SUCCESS )
      {
#ifdef NATALIE_V11
        util_memcpy(pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmGetHandsetIpuiCfmType*)param)->TerminalId].Ipui,((ApiFpMmGetHandsetIpuiCfmType*)param)->IPUI, 5);
#else
        util_memcpy(pCfSysCtrl->CfSysStatus.HsInfo[((ApiFpMmGetHandsetIpuiCfmType*)param)->HandsetId].Ipui,((ApiFpMmGetHandsetIpuiCfmType*)param)->IPUI, 5);
#endif
      }
      break;

    case API_FP_CC_SETUP_IND:
      CallCtrlMailHandler((RosMailType *)param);
#ifdef NATALIE_V11
      pCfSysCtrl->CfSysStatus.CallInfo.HsId.Value = ((ApiFpCcSetupIndType*)param)->TerminalId; //save HandsetId /*!< Id of the calling handset. */
      pCfSysCtrl->CfSysStatus.CallInfo.CallReference = ((ApiFpCcSetupCfmType*)param)->CallReference; /*!< Call reference/instance number. */
      pCfSysCtrl->CfSysStatus.CallInfo.CallClass = ((ApiFpCcSetupIndType*)param)->CallClass;
#else
      pCfSysCtrl->CfSysStatus.CallInfo.HsId.HandsetId = ((ApiFpCcSetupIndType*)param)->CallReference.HandsetId; //save HandsetId
#endif

      if( pCfSysCtrl->CfSysStatus.CallInfo.CallClass != API_CC_INTERNAL )
      {
        /* Send openD call indication to the application. */
        cIndication.service = OPEND_CALLAPI_SETUP;
        util_memcpy(cIndication.param.setup.pmid, &((ApiFpCcSetupIndType*)param)->TerminalId, 2);
        openD_call_indication( &cIndication );

        /* Change to call state. */
        msManager_changeState( &opendStateCtxt, OPEND_STATE_CALL );
      }
      break;

    case API_FP_CC_SETUP_CFM:
      CallCtrlMailHandler((RosMailType *)param);
#ifdef NATALIE_V11
      pCfSysCtrl->CfSysStatus.CallInfo.CallReference = ((ApiFpCcSetupCfmType*)param)->CallReference; /*!< Call reference/instance number. */
      pCfSysCtrl->CfSysStatus.CallInfo.CallClass = ((ApiFpCcSetupCfmType*)param)->CallClass;
#else
      pCfSysCtrl->CfSysStatus.CallInfo.HsId.HandsetId = ((ApiFpCcSetupCfmType*)param)->CallReference.HandsetId; //save HandsetId
#endif

      rsuint8 handsetId = GetHsFromCallReference( ((ApiFpCcSetupCfmType*)param)->CallReference );

      /* Send openD call confirmation to the application. */
      cConfirm.service = OPEND_CALLAPI_SETUP;
      util_memcpy(cConfirm.param.setup.pmid, &handsetId, 1);
      cConfirm.status = OPEND_STATUS_OK;
      openD_call_confirmation( &cConfirm );
      break;

    case API_FP_CC_ALERT_IND:
      CallCtrlMailHandler((RosMailType *)param);
      MmiShowLedStatus();

      /* Send openD call confirmation to the application. */
      cIndication.service = OPEND_CALLAPI_CONNECTION_STATUS_RINGING;
      openD_call_indication( &cIndication );
      break;

    case API_FP_CC_REJECT_IND:
      CallCtrlMailHandler((RosMailType *)param);
      if(pCfSysCtrl->CfSysStatus.CfSysFlag.PageMode)
      {
        pCfSysCtrl->CfSysStatus.CfSysFlag.PageMode=CheckPagingMode();
      }
      MmiShowLedStatus();
      break;

    case API_FP_CC_RELEASE_IND:
      CallCtrlMailHandler((RosMailType *)param);

      /* Send openD call indication to the application. */
      cIndication.service = OPEND_CALLAPI_RELEASE;
      openD_call_indication( &cIndication );
      break;

    case API_FP_CC_CONNECT_IND:
      CallCtrlMailHandler((RosMailType *)param);

      if( pCfSysCtrl->CfSysStatus.CallInfo.CallClass != API_CC_INTERNAL )
      {
        /* Change to standby state. */
        msManager_changeState( &opendStateCtxt, OPEND_STATE_CALL );
      }
      break;

    case API_FP_MM_HANDSET_PRESENT_IND:
      terminalId = ((ApiFpMmHandsetPresentIndType*)param)->TerminalId;
      printf("API_FP_MM_HANDSET_PRESENT_IND, %d\n", terminalId);
      /* Send openD subscription indication to the application. */
      sIndication.service = OPEND_SUBAPI_SUBSCRIBE;
      sIndication.param.subscribe.pmid[0] = terminalId;
      openD_sub_indication( &sIndication );
      break;

    case API_FP_MM_SET_ACCESS_CODE_CFM:
      util_memcpy(pCfSysCtrl->Ac, ac, 4);

      /* Send openD subscription confirmation to the application. */
      sConfirm.service = OPEND_SUBAPI_SET_AC;
      sConfirm.status = OPEND_STATUS_OK;
      openD_sub_confirmation( &sConfirm );
      break;

    case API_FP_CC_CALL_PROC_CFM:
      CallCtrlMailHandler((RosMailType *)param);
      break;

  }

  return true;
}

bool opend_state_standby( void *param ) {

  bool ret = true;
  uint8_t i;

  if( !param ) {
    return false;
  }

  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      /* Initialization state. */

      printf("State - STANDBY\n");

      for(i=0;i<TOTAL_LINE_NUM;i++)
        LineSimSetLineState(i, LS_ON_HOOK);

      MmiShowLedStatus();
      break;

    case MESSAGE_PRIMITIVE_USER:
      if( !((openD_Api_t *)message->param) ) {
        return false;
      }

      switch( ((openD_Api_t *)message->param)->opendApis ) {
        case OPEND_APIS_SUB:
          ret = _message_primitive_user_sub( ((openD_Api_t *)message->param)->param );
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

#ifdef __cplusplus
}
#endif
