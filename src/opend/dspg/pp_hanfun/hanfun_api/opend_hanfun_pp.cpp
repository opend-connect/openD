/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_pp.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include "opend_dataTypes.h"
#include "opend_hanfun_api_pp.h"
#include "opend_hanfun.h"
#include "CmndLib.h"
#include "CmndMsg_DeviceManagement.h"
#include "opend.h"
#include "CmndMsg_KeepAlive.h"
#include "CmndMsg_OnOff.h"
#include "ule.h"



static t_st_Msg        g_st_Msg;          /* Hanfun message. */
static t_stReceiveData g_ParserContext;   /* Parser context for serial communication. */
static int             g_Registered;      /* Registered flag. */
static int             g_DeviceId;        /* Device id. */
static uint8_t         g_SendResult;      /* Send result. */


/**
 * @brief   Send keep alive.
 *
 * @details The node send a keep alive message to the base.
 */
void sendKeepLive();

/**
 * @brief   RX byte received.
 *
 * @details RX byte received by the serial communication.
 *
 * @param   data Pointer to the received data.
 * @param   len Length of the received data.
 */
void rxByteReceived(uint8_t *data, uint16_t len);

openD_status_t openD_hanfunApi_pp_init()
{
  t_st_hanCmndApiMsg st_hanCmndApiMsg;
  t_st_Packet        st_Packet = { 0 };

  /* Initialize Parser Context. */
  memset(&g_ParserContext, 0, sizeof(t_stReceiveData));

  if(initIwu(sendKeepLive, rxByteReceived) != true)
  {
    return OPEND_STATUS_FAIL;
  }

  /* Send reset request. */
  p_CmndMsg_System_CreateResetReq( &st_hanCmndApiMsg );
  st_Packet.length = p_CmndApiPacket_CreateFromCmndApiMsg(st_Packet.buffer, &st_hanCmndApiMsg);

  if(sendFctPtr)
  {
    sendFctPtr(st_Packet.buffer, st_Packet.length);
  } else {
    return OPEND_STATUS_FAIL;
  }

  return OPEND_STATUS_OK;
}

openD_status_t openD_hanfunApi_pp_devMgmtRequest( openD_hanfunApi_devMgmtReq_t *hMgmtRequest, uint16_t address )
{
  /* Registration to base. */
  t_st_hanCmndApiMsg st_hanCmndApiMsg;
  t_st_Packet        st_Packet = { 0 };

  if(hMgmtRequest == NULL)
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  switch(hMgmtRequest->service){
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE:

      p_Cmnd_DeviceManagement_CreateRegisterDeviceReq( &st_hanCmndApiMsg, NULL );
      st_Packet.length = p_CmndApiPacket_CreateFromCmndApiMsg(st_Packet.buffer, &st_hanCmndApiMsg);
      p_CmndMsgLog_PrintTxBuffer(st_Packet.length, st_Packet.buffer);

      if(sendFctPtr)
      {
        sendFctPtr(st_Packet.buffer, st_Packet.length);
        return OPEND_STATUS_OK;
      }

      return OPEND_STATUS_FAIL;
      break;
    default:
      break;
  }

  return OPEND_STATUS_ARGUMENT_INVALID;
}

openD_status_t opend_hanfunApi_createProfile(openD_hanfunApi_profile_t opend_profile, uint8_t id)
{
  return OPEND_STATUS_OK;
}

void sendKeepLive()
{
	/* Keep alive to base. */
  t_st_hanCmndApiMsg st_hanCmndApiMsg;
  t_st_Packet        st_Packet = { 0 };

  p_CmndMsg_KeepAlive_CreateImAliveReq( &st_hanCmndApiMsg );
  st_Packet.length = p_CmndApiPacket_CreateFromCmndApiMsg(st_Packet.buffer, &st_hanCmndApiMsg);
  p_CmndMsgLog_PrintTxBuffer(st_Packet.length, st_Packet.buffer);

  sendFctPtr(st_Packet.buffer, st_Packet.length);
}

openD_status_t openD_hanfunApi_pp_profileRequest( openD_hanfunApi_profileReq_t *hProfileRequest )
{
  openD_hanfunApi_profileCfm_t hProfileConfirm;
  t_st_hanCmndApiMsg st_hanCmndApiMsg;
  t_st_Packet        st_Packet = { 0 };

  if(hProfileRequest == NULL)
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  switch( hProfileRequest->profile )
  {
    case OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH:
      switch( hProfileRequest->simpleOnOffSwitch.service )
      {
        case OPEND_HANFUN_IONOFF_CLIENT_TOGGLE:

          hProfileConfirm.status = OPEND_STATUS_OK;
          hProfileConfirm.simpleOnOffSwitch.service = OPEND_HANFUN_IONOFF_CLIENT_TOGGLE;

          p_CmndMsg_OnOff_CreateToggleReq( &st_hanCmndApiMsg, 0 );
          st_Packet.length = p_CmndApiPacket_CreateFromCmndApiMsg(st_Packet.buffer, &st_hanCmndApiMsg);
          p_CmndMsgLog_PrintTxBuffer(st_Packet.length, st_Packet.buffer);
          if(sendFctPtr)
          {
            sendFctPtr(st_Packet.buffer, st_Packet.length);
          }

          openD_hanfun_profileCfm(&hProfileConfirm);
          return OPEND_STATUS_OK;
          break;
        default:
          break;
      }
      break;
    case OPEND_HANFUNAPI_MOTION_DETECTOR:
      switch( hProfileRequest->motionDetector.service )
      {
        case OPEND_HANFUN_iDETECTOR_ALERT:

          hProfileConfirm.status = OPEND_STATUS_OK;
          hProfileConfirm.motionDetector.service = OPEND_HANFUN_iDETECTOR_ALERT;
          openD_hanfun_profileCfm(&hProfileConfirm);
          return OPEND_STATUS_OK;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

  hProfileConfirm.status = OPEND_STATUS_FAIL;
  openD_hanfun_profileCfm(&hProfileConfirm);
  return OPEND_STATUS_ARGUMENT_INVALID;
}

void rxByteReceived(uint8_t *data, uint16_t len)
{
  bool haveMessage = p_hanCmndApi_HandleByte(&g_ParserContext, *data, &g_st_Msg);
  if ( haveMessage)
  {
    openD_hanfunApi_profileInd_t hProfileInd;
    openD_hanfunApi_devMgmtCfm_t hDevMgmtConfirm;
    switch (g_st_Msg.serviceId)
    {
      case CMND_SERVICE_ID_GENERAL:
        if (g_st_Msg.messageId == CMND_MSG_GENERAL_HELLO_IND)
        {
          /* Handle the hello indication, the first message sent by the
             DU-EB after reset release and firmware boot. */
          t_st(CMND_IE_GENERAL_STATUS) st_IeGenStatus;
          /* Extract device id if registered, store into global g_DeviceId. */
          if ( p_CmndMsg_IeGet(&g_st_Msg, p_CMND_IE_GETTER(CMND_IE_GENERAL_STATUS), &st_IeGenStatus, sizeof(st_IeGenStatus) ) )
          {
            g_Registered = (CMND_GEN_STATUS_REGISTERED == st_IeGenStatus.u8_RegStatus);
            if (g_Registered)
            {
                g_DeviceId = st_IeGenStatus.u16_DeviceID;
            }
          }
        }
        break;
      case CMND_SERVICE_ID_ON_OFF:
        if(g_st_Msg.messageId == CMND_MSG_ONOFF_ON_REQ)
        {
          hProfileInd.profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
          hProfileInd.simpleLight.service = OPEND_HANFUN_IONOFF_SERVER_ON_ADDR;
          hProfileInd.simpleLight.param.onAddr.addr.device = g_st_Msg.unitId;
          hProfileInd.status = OPEND_STATUS_OK;
          openD_hanfun_profileInd(&hProfileInd);
        }
        if(g_st_Msg.messageId == CMND_MSG_ONOFF_OFF_REQ)
        {
          hProfileInd.profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
          hProfileInd.simpleLight.service = OPEND_HANFUN_IONOFF_SERVER_OFF_ADDR;
          hProfileInd.simpleLight.param.onAddr.addr.device = g_st_Msg.unitId;
          hProfileInd.status = OPEND_STATUS_OK;
          openD_hanfun_profileInd(&hProfileInd);
        }
        if(g_st_Msg.messageId == CMND_MSG_ONOFF_TOGGLE_REQ)
        {
          hProfileInd.profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
          hProfileInd.simpleLight.service = OPEND_HANFUN_IONOFF_SERVER_TOGGLE_ADDR;
          hProfileInd.simpleLight.param.onAddr.addr.device = g_st_Msg.unitId;
          hProfileInd.status = OPEND_STATUS_OK;
          openD_hanfun_profileInd(&hProfileInd);
        }
      break;
      case CMND_SERVICE_ID_DEVICE_MANAGEMENT:
			  if ( g_st_Msg.messageId == CMND_MSG_DEV_MGNT_REGISTER_DEVICE_CFM )
			  {
          /* Handle confirmation to Registration request and extract the confirmation result. */
          printf("REGISTER_CONF");
          t_st(CMND_IE_RESPONSE) st_IeResponse;
          hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE;

          /* Extract result, store into global g_u8_SendResult. */
	        if ( p_CmndMsg_IeGet(&g_st_Msg, p_CMND_IE_GETTER(CMND_IE_RESPONSE), &st_IeResponse, sizeof(st_IeResponse) ) )
          {
            g_SendResult = st_IeResponse.u8_Result;
            if( g_SendResult == 0 )
            {
              printf("Register success");
              hDevMgmtConfirm.status = OPEND_STATUS_OK;
              openD_hanfun_devMgmtCfm(&hDevMgmtConfirm);
              keepAliveTimerStart();
            }
            else
            {
              printf("Register fail");
              hDevMgmtConfirm.status = OPEND_STATUS_FAIL;
              openD_hanfun_devMgmtCfm(&hDevMgmtConfirm);
            }
	        }
			  }
			  else if ( g_st_Msg.messageId == CMND_MSG_DEV_MGNT_REGISTER_DEVICE_IND )
			  {
          /* Handle answer to "Registration" request and extract the registration result. */
          printf("REGISTER_IND");
          t_st_hanCmndIeRegistrationResponse  ieResponse = {0};

          /*
           * Extract result, store into global g_SendResult.
           * If successful, store device Id into global g_DeviceId.
           */
          if( p_CmndMsg_IeGet(&g_st_Msg, p_CMND_IE_GETTER(CMND_IE_REGISTRATION_RESPONSE), &ieResponse, sizeof(ieResponse) ) )
          {
            g_SendResult = ieResponse.u8_ResponseCode;
            g_DeviceId = ieResponse.u16_DeviceAddress;

            if (g_SendResult == 0)
            {
              g_Registered = 1;
            }
            else
            {
              g_Registered = 0;
            }
          }
			  }
    }
  }
}
