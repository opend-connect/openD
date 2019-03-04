/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       hf_transport.cpp
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
#include <sstream>
#include <cstdint>

#include <hanfun.h>
#define HF_LOG_LEVEL HF_LOG_LEVEL_TRACE
#include <application.h>
#include "hf_transport.h"

extern "C"
{
#include "apphan.h"
#include "cmbs_api.h"
#include "cmbs_util.h"
#include "appcmbs.h"
#include "appsrv.h"
#include "tcx_log.h"
#include "tcx_eep.h"
#include "tcx_util.h"
#include "appCallRouter.h"

#include "cmbs_han.h"
#include "cmbs_han_ie.h"
}

/** Specifies the header length of a HANFUN message. */
#define HANFUN_HEADER_SIZE 15U

/**
 * @brief   CMBS message callback.
 *
 * @details Handle the CMBS message callback.
 *
 * @param   pv_AppRef Pointer of the app reference.
 * @param   eventId Event ID of the CMBS.
 * @param   ie_data Pointer to IE of the CMBS.
 */
static int appcmbs_opend_callback( void *pv_AppRef, E_CMBS_EVENT_ID eventId, void *ie_data);

/** HANFUN buffer for CMBS. */
static uint8_t cmbs_hanFunBuffer[CMBS_HAN_MAX_MSG_LEN*2];

/* Holds the data of the registration state 1. */
static ST_HAN_REG_STAGE_1_STATUS regStage1Status;

/** Message sequence. */
static uint8_t msgSequence = 0U;

/* Setup TDM interface. */
ST_TDM_CONFIG g_st_TdmCfg;

/* Set to one for usb communication. */
int usb;

/* Out of use variables. */
int han;
int cfg_debug;

/* Holds the log buffer. */
extern ST_CB_LOG_BUFFER pfn_log_buffer_Cb;

/* DevMedia variable for app initialization. */
ST_CMBS_DEV g_st_DevMedia;

/* Holds the baudrate. */
extern u32 g_u32_BaudRate;

/* Setup UART configuration. */
ST_UART_CONFIG g_st_UartCfg;

/* Device control. */
ST_CMBS_DEV g_st_DevCtl;

HF::ULE::Transport * HF::ULE::Transport::instance ()
{
   static HF::ULE::Transport transport;

   return &transport;
}

void HF::ULE::Transport::initialize ()
{
  /* Can be used to initialize the hanfun library iwu. */
}

void HF::ULE::Transport::destroy ()
{
  /* Can be used for destroy the iwu initialization. */
}

void HF::ULE::Transport::connected (uint16_t dev_id, uint8_t _ipui[5])
{
   Link * link = this->find_by_id(dev_id);

   if (link == nullptr)
   {
      HF::UID::DECT ipui;
      ipui[0] = _ipui[0];
      ipui[1] = _ipui[1];
      ipui[2] = _ipui[2];
      ipui[3] = _ipui[3];
      ipui[4] = _ipui[4];
      link = new Link(dev_id, ipui, this);
      add(link);
   }
}

void HF::ULE::Transport::receive (const uint16_t dev_id, const uint8_t data[], size_t size)
{
   HF::Common::ByteArray payload(data, size);

   auto link = this->find_by_id(dev_id);

   /* Link was found send to endpoints. */
   if (link != nullptr)
   {
      HF::Devices::Concentrator::Transport::receive(link, payload);
   }
   else
   {
      LOG(ERROR) << "Could not find link for device : " << dev_id << NL;
   }
}

HF::ULE::Link * HF::ULE::Transport::find_by_id (uint16_t dev)
{
   auto it = std::find_if(links.begin(), links.end(), [dev](const HF::Transport::Link * link)
   {
      return ((HF::ULE::Link *)link)->id() == dev;
   });

   /* Link was found send to endpoints. */
   if (it != links.end())
   {
      return static_cast<HF::ULE::Link *>(*it);
   }

   return nullptr;
}

HF::ULE::Link * HF::ULE::Transport::find_by_address (uint16_t address)
{
   auto it = std::find_if(links.begin(), links.end(), [address](const HF::Transport::Link * link)
   {
      return link->address() == address;
   });

   /* Link was found. */
   if (it != links.end())
   {
      return static_cast<HF::ULE::Link *>(*it);
   }

   return nullptr;
}

void HF::ULE::Link::send (HF::Common::ByteArray &array)
{
  ST_IE_HAN_MSG stIe_Msg = {0};
  ST_IE_HAN_MSG_CTL st_HANMsgCtl = { 0,0,0 };

  /* Parse the bytes like in the hanfun specification. */
  stIe_Msg.u16_SrcDeviceId              = ((uint16_t) array.at(0) << 0x08) | (array.at(1) & 0x00FF);
  stIe_Msg.u8_SrcUnitId                 = array.at(2);
  stIe_Msg.u8_DstAddressType            = (array.at(3) >> 0x07) & 0x01;
  stIe_Msg.u16_DstDeviceId              = dev_id;
  stIe_Msg.u8_DstUnitId                 = array.at(5);
  stIe_Msg.st_MsgTransport.u16_Reserved = 0x0000;
  stIe_Msg.u8_MsgSequence               = msgSequence++;
  stIe_Msg.e_MsgType                    = array.at(9);
  stIe_Msg.u8_InterfaceType             = (array.at(10) >> 0x07) & 0x01;
  stIe_Msg.u16_InterfaceId              = (((uint16_t) array.at(10) & 0x007F) << 0x08) | (array.at(11) & 0x00FF);
  stIe_Msg.u8_InterfaceMember           = array.at(12);
  stIe_Msg.u16_DataLen                  = ((uint16_t) array.at(13) << 0x08) | (array.at(14) & 0x00FF);
  if( stIe_Msg.u16_DataLen > 0U ) {
    stIe_Msg.pu8_Data                   = &array.at(15);
  }

  /* Push message to fifo. */
  cmbs_util_FifoPush(Get_UleMsgFifo(dev_id), &stIe_Msg);

#ifdef TRY_TO_SEND_DIRECTLY
  /* Try to send message directly. */
  app_DsrHanMsgSend(1, 0, &st_HANMsgCtl, &stIe_Msg);
#else
  /* Tx request: */
  app_DsrHanMsgSendTxRequest( dev_id );
#endif

  return;
}

bool HF::Application::Registration (bool mode)
{
  /* Can be used for registration. */
}

void HF::Application::Deregister (uint16_t address)
{
  /* Can be used for deregistration. */
}

void initUleApp(int argc, char **argv)
{
  char *psz_ComDevName = NULL;
  u8 u8_Port = 0;
  ST_IE_SYPO_SPECIFICATION SYPOParameters;
  bool SYPO_enabled = FALSE;
  int menu = 1;
  u16 u16_TargetVersion;

  appcmbs_opend_setCallbackFct( &appcmbs_opend_callback );

  memset(&SYPOParameters, 0, sizeof(SYPOParameters));
  /* Use USB communication. */
  usb = 1;

  if (u8_Port == 0 && psz_ComDevName == 0 )
  {
    /* tcx_DetectComPort is useful for windows or linux port 0. */
    u8_Port = tcx_DetectComPort(TRUE, &g_st_DevCtl.e_DevType); /* interactive mode */
  }

  if (psz_ComDevName)
  {
    printf("COMDEV: %s\n", psz_ComDevName);
  }
  else
  {
    printf("COMPORT: %d\n", u8_Port);
  }

  if ( tcx_LogOutputCreate() != CMBS_RC_OK )
  {
    exit(1);
  }

  if ( tcx_HostLogOutputCreate() != CMBS_RC_OK )
  {
    exit(1);
  }

  /* Configurate the usb port. */
  if ( usb == 1 )
  {
    tcx_USBConfig(u8_Port, g_u32_BaudRate);
  }

  /* Register callback functions for log buffer handling. */
  pfn_log_buffer_Cb.pfn_cmbs_api_log_outgoing_packet_prepare_cb = tcx_LogOutgoingPacketPrepare;
  pfn_log_buffer_Cb.pfn_cmbs_api_log_outgoing_packet_part_write_cb = tcx_LogOutgoingPacketPartWrite;
  pfn_log_buffer_Cb.pfn_cmbs_api_log_outgoing_packet_write_finish_cb = tcx_LogOutgoingPacketWriteFinish;
  pfn_log_buffer_Cb.pfn_cmbs_api_log_incoming_packet_write_finish_cb = tcx_LogIncomingPacketWriteFinish;
  pfn_log_buffer_Cb.pfn_cmbs_api_log_write_log_buffer_cb = tcx_LogWriteLogBuffer;

  /* Initialization of the cmbs application. */
  if ( appcmbs_Initialize(NULL, &g_st_DevCtl, &g_st_DevMedia, &pfn_log_buffer_Cb) != CMBS_RC_OK )
  {
    CFR_DBG_ERROR("TCX ERROR: !!! Host could not be started up!\n");
  }
  else
  {
    AppCallRouter_Init ();

    u16_TargetVersion = cmbs_api_ModuleVersionGet();

    /* Try to get HW Chip version. */
    if ( (u16_TargetVersion & 0xFF00) != 0x0000 &&   // Bootloader
         (u16_TargetVersion & 0xF000) != 0x2000 &&   // CMBS 2xxx version (e.g. 2.99.9) - Old IE Header structure
         (u16_TargetVersion & 0xFF00) != 0x0200 )    // CMBS 02xx version (e.g. 2.99) - Old IE Header structure
    {
      app_SrvHWVersionGet(TRUE);
    }
    if((u16_TargetVersion & 0xFF00) != 0x0000) //Booter does not support this event
    {
      printf("Getting MAX Buffer size...\n");
      appcmbs_MaxTransferSizeGet();
    }

    printf("Start Cordless Stack\n");
    if ( SYPO_enabled )
    {
      appcmbs_CordlessStart(&SYPOParameters);
    }
    else
    {
      appcmbs_CordlessStart(NULL);
    }

    if ( menu )
    {
      return;
    }
    else
    {
      while ( 1 )
      {
        SleepMs(3000);
      }
    }
  }

  appcmbs_Cleanup();
  tcx_EepClose();
  tcx_LogCloseLogfile();
  tcx_HostLogCloseLogfile();
  tcx_LogCloseTracefile();
  tcx_HostLogOutputDestroy();
  tcx_LogOutputDestroy();
  printf("Press ENTER to exit...");
  exit(1);
}

static void cmbs_hanFunMsgRegState1Notification( void* ie_data )
{
  void* ie = NULL;
  uint16_t ieType = 0U, deviceId = 0U;
  ST_HAN_GENERAL_STATUS status;
  ST_HAN_REG_STAGE_1_STATUS regStatus;

  if(!ie_data) {
    return;
  }

  cmbs_api_ie_GetFirst( ie_data, &ie, &ieType );

  while ( ie )
  {
    switch ( ieType )
    {
      case CMBS_IE_HAN_GENERAL_STATUS:
        cmbs_api_ie_HANGeneralStatusGet( ie, &status );
        break;
      case CMBS_IE_HAN_DEVICE:
        cmbs_api_ie_HANDeviceGet( ie, &deviceId );
        break;
      case CMBS_IE_HAN_DEVICE_REG_STAGE1_OK_STATUS_PARAMS:
        cmbs_api_ie_HANRegStage1OKResParamsGet ( ie, &regStage1Status );
        break;
      default:
        break;
    }
    cmbs_api_ie_GetNext( ie_data, &ie, &ieType );
  }

  return;
}

static void cmbs_hanFunMsgRegState3Notification( void* ie_data )
{
  void* ie = NULL;
  uint16_t ieType = 0U, deviceId = 0U;
  ST_HAN_GENERAL_STATUS status;

  if(!ie_data) {
    return;
  }

  cmbs_api_ie_GetFirst( ie_data, &ie, &ieType );

  while ( ie )
  {
    switch ( ieType )
    {
      case CMBS_IE_HAN_GENERAL_STATUS:
        cmbs_api_ie_HANGeneralStatusGet( ie, &status );
        break;
      case CMBS_IE_HAN_DEVICE:
        cmbs_api_ie_HANDeviceGet( ie, &deviceId );
        break;
    }
    cmbs_api_ie_GetNext( ie_data, &ie, &ieType );
  }

  if( CMBS_RESPONSE_OK == status.u16_Status )
  {

    /* HAN-FUN Transport Layer over Dialog's ULE Stack. */
    HF::ULE::Transport * transport = HF::ULE::Transport::instance();

    /* Data for the register finished indication. */
    const uint8_t data[] = { 0x7F, 0xFF, 0, 0, 0, 0, 0, 0, 0, 1, 0x80, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    /* Size of the register finished data. */
    size_t size = sizeof(data);

    /* Notify the HANFUN library about the connected device. */
    transport->connected(deviceId, regStage1Status.u8_IPUI);

    /* Register finished indication received. */
    transport->receive(deviceId, data, size);
  }

  return;
}

static int8_t cmbs_hanFunMsgSendTxStartRequestRes( void* ie_data )
{
  void* ie = NULL;
  uint16_t ieType = 0U, deviceId = 0U, fail_reason = 0U;
  ST_IE_RESPONSE ieResponse;

  cmbs_api_ie_GetFirst( ie_data, &ie, &ieType );

  while( ie != NULL )
  {
    switch ( ieType )
    {
      case CMBS_IE_RESPONSE:
        cmbs_api_ie_ResponseGet( ie, &ieResponse);
        break;
      case CMBS_IE_HAN_DEVICE:
        cmbs_api_ie_HANDeviceGet( ie, &deviceId);
        break;
      case CMBS_IE_HAN_TX_REQ_RES_REASON:
        cmbs_api_ie_HANTxReqResReasonGet( ie, (uint16_t*) &fail_reason);
        break;
    }
    cmbs_api_ie_GetNext( ie_data, &ie, &ieType );
  }

  if( CMBS_RESPONSE_OK != ieResponse.e_Response )
  {
    if( CMBS_HAN_ULE_TX_REQ_RES_DEVICE_ALREADY_IN_LINK == fail_reason )
    {
      /* Send Tx request. */
      ST_IE_HAN_MSG *stIe_Msg;
      ST_IE_HAN_MSG_CTL st_HANMsgCtl = { 0,0,0 };

      stIe_Msg = (ST_IE_HAN_MSG*) cmbs_util_FifoGet(Get_UleMsgFifo(deviceId));
      if(stIe_Msg) {
        app_DsrHanMsgSend(1, 0, &st_HANMsgCtl, stIe_Msg);
      }

      return 0;
    } else {
      cmbs_util_FifoPop(Get_UleMsgFifo(deviceId));
      return -1;
    }
  }

  return 0;
}

static int8_t cmbs_hanFunMsgSendRes( void* ie_data )
{
  void* ie = NULL;
  uint16_t ieType = 0U, deviceId = 0U;
  E_CMBS_IE_TYPE fail_reason = CMBS_IE_UNDEF;
  ST_IE_RESPONSE ieResponse;
  int8_t ret = -1;

  cmbs_api_ie_GetFirst( ie_data, &ie, &ieType );

  while( ie != NULL )
  {
    switch ( ieType )
    {
      case  CMBS_IE_RESPONSE:
        cmbs_api_ie_ResponseGet( ie, &ieResponse);
        break;
      case CMBS_IE_HAN_DEVICE:
        cmbs_api_ie_HANDeviceGet( ie, &deviceId);
        break;
      case CMBS_IE_HAN_SEND_FAIL_REASON:
        cmbs_api_ie_HANSendErrorReasonGet( ie, (uint16_t*) &fail_reason);
        break;
    }
    cmbs_api_ie_GetNext( ie_data, &ie, &ieType );
  }

  if( CMBS_RESPONSE_OK != ieResponse.e_Response )
  {
    if( (CMBS_HAN_SEND_MSG_REASON_DEVICE_NOT_IN_LINK_ERROR == fail_reason) ||
        (CMBS_HAN_SEND_MSG_REASON_NO_TX_REQUEST == fail_reason) )
    {
      /* Send Tx request. */
      app_DsrHanMsgSendTxRequest( deviceId );
      ret = 1;
    } else {
      /* Tx error, Tx abort. */
      ret = -1;
    }
  } else {
    /* Tx success. */
    ret = 0;
  }

  cmbs_util_FifoPop(Get_UleMsgFifo(deviceId));
  app_DsrHanMsgSendTxEnd( deviceId );
  return ret;
}

static void cmbs_hanFunMsgSendTxReady( void* ie_data )
{
  void* ie = NULL;
  uint16_t ieType = 0U, deviceId = 0U;
  ST_IE_HAN_MSG_CTL st_HANMsgCtl = { 0,0,0 };
  ST_IE_HAN_MSG *stIe_Msg;

  cmbs_api_ie_GetFirst( ie_data, &ie, &ieType );

  while( ie != NULL )
  {
    switch ( ieType )
    {
      case CMBS_IE_HAN_DEVICE:
        cmbs_api_ie_HANDeviceGet( ie, &deviceId);
        break;
      default:
        break;
    }
    cmbs_api_ie_GetNext( ie_data, &ie, &ieType );
  }

  /* Send message. */
  stIe_Msg = (ST_IE_HAN_MSG*) cmbs_util_FifoGet(Get_UleMsgFifo( deviceId ));
  if(stIe_Msg) {
    app_DsrHanMsgSend(1, 0, &st_HANMsgCtl, stIe_Msg);
  }

  return;
}

static int8_t cmbs_hanFunMsgRecv( void* ie_data )
{
  void* ie = NULL;
  uint16_t ieType = 0U, deviceId = 0U;
  ST_IE_HAN_MSG ie_han_msg;
  bool ieReceived = FALSE;

  ie_han_msg.pu8_Data = cmbs_hanFunBuffer + 15U;
  cmbs_api_ie_GetFirst(ie_data, &ie, &ieType);
  while(ie != NULL)
  {
    if ( CMBS_IE_HAN_MSG == ieType )
    {
      cmbs_api_ie_HANMsgGet(ie, &ie_han_msg);
      ieReceived = TRUE;
    }
    cmbs_api_ie_GetNext(ie_data, &ie, &ieType);
  }

  if(!ieReceived)
  {
    return -1;
  }

  /* Generate original HANFUN packet. */
  cmbs_hanFunBuffer[0] = (uint8_t) (ie_han_msg.u16_SrcDeviceId >> 8U);
  cmbs_hanFunBuffer[1] = (uint8_t) ie_han_msg.u16_SrcDeviceId;
  cmbs_hanFunBuffer[2] = ie_han_msg.u8_SrcUnitId;
  cmbs_hanFunBuffer[3] = (ie_han_msg.u8_DstAddressType << 7 ) & 0x80;
  cmbs_hanFunBuffer[3] |= (uint8_t) ((ie_han_msg.u16_DstDeviceId >> 8U) & 0x7F);
  cmbs_hanFunBuffer[4] = (uint8_t) ie_han_msg.u16_DstDeviceId;
  cmbs_hanFunBuffer[5] = ie_han_msg.u8_DstUnitId;
  cmbs_hanFunBuffer[6] = 0x00; /* RFU */
  cmbs_hanFunBuffer[7] = 0x00; /* RFU */
  cmbs_hanFunBuffer[8] = ie_han_msg.u8_MsgSequence;
  cmbs_hanFunBuffer[9] = ie_han_msg.e_MsgType;
  cmbs_hanFunBuffer[10] = (ie_han_msg.u8_InterfaceType << 7 ) & 0x80;
  cmbs_hanFunBuffer[10] |= (uint8_t) ((ie_han_msg.u16_InterfaceId >> 8U) & 0x7F);
  cmbs_hanFunBuffer[11] = (uint8_t) ie_han_msg.u16_InterfaceId;
  cmbs_hanFunBuffer[12] = (uint8_t) ie_han_msg.u8_InterfaceMember;
  cmbs_hanFunBuffer[13] = (uint8_t) (ie_han_msg.u16_DataLen >> 8U);
  cmbs_hanFunBuffer[14] = (uint8_t) ie_han_msg.u16_DataLen;

  /* HAN-FUN Transport Layer over Dialog's ULE Stack. */
  HF::ULE::Transport * transport = HF::ULE::Transport::instance();

  /* Size of the register finished data. */
  size_t size = ie_han_msg.u16_DataLen + HANFUN_HEADER_SIZE;

  /* Register finished indication received. */
  transport->receive(ie_han_msg.u16_SrcDeviceId, cmbs_hanFunBuffer, size);

  return 0;
}

static int appcmbs_opend_callback( void *pv_AppRef, E_CMBS_EVENT_ID eventId, void *ie_data)
{
  int8_t ret;

  switch(eventId)
  {
    case CMBS_EV_DSR_HAN_MSG_RECV:
      cmbs_hanFunMsgRecv( ie_data );
      break;

    case CMBS_EV_DSR_HAN_DEVICE_REG_STAGE_1_NOTIFICATION:
      cmbs_hanFunMsgRegState1Notification( ie_data );
      break;

    case CMBS_EV_DSR_HAN_DEVICE_REG_STAGE_3_NOTIFICATION:
      cmbs_hanFunMsgRegState3Notification( ie_data );
      break;

    case CMBS_EV_DSR_HAN_MSG_SEND_TX_START_REQUEST_RES:
      ret = cmbs_hanFunMsgSendTxStartRequestRes( ie_data );
      if ( 0 > ret ) {
        /* TX error. */
      }
      break;

    case CMBS_EV_DSR_HAN_MSG_SEND_TX_READY:
      /* Send message. */
      cmbs_hanFunMsgSendTxReady( ie_data );
      break;

    case CMBS_EV_DSR_HAN_MSG_SEND_RES:
      /* Check the send response. */
      ret = cmbs_hanFunMsgSendRes( ie_data );
      if( 0 == ret ) {
        /* TX success. */
      } else if ( 0 > ret ) {
         /* TX error. */
      }
      break;

    case CMBS_EV_DSR_HAN_MSG_SEND_TX_ENDED:
      break;

    default:
      break;
  }

  return 0;
}
