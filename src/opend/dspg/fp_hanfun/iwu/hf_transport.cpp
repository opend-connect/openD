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
}


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

void HF::ULE::Transport::connected (uint8_t dev_id, uint8_t _ipui[5])
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

void HF::ULE::Transport::receive (const uint8_t dev_id, const uint8_t data[], size_t size)
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
  ST_IE_HAN_MSG			  stIe_Msg = {0};
  ST_IE_HAN_MSG_CTL 	st_HANMsgCtl = { 0,0,0 };

  /* Parse the bytes like in the hanfun specification. */
  stIe_Msg.u16_SrcDeviceId	            = array.at(0);
  stIe_Msg.u8_SrcUnitId		              = array.at(2);
  stIe_Msg.u16_DstDeviceId              = getAddress()[array.at(4)];
  stIe_Msg.u8_DstUnitId                 = array.at(5);
  stIe_Msg.u8_DstAddressType            = (array.at(3) >> 7) & 0x0001;
  stIe_Msg.st_MsgTransport.u16_Reserved	= 0;
  stIe_Msg.u8_MsgSequence				        = 53;
  stIe_Msg.e_MsgType					          = array.at(9);
  stIe_Msg.u8_InterfaceType				      = (array.at(10) >> 7) & 0x0001;
  stIe_Msg.u16_InterfaceId				      = (array.at(10) & 0x7F) << 8;
  stIe_Msg.u8_InterfaceMember           = array.at(12);
  stIe_Msg.u16_DataLen                  = array.at(14);

	/* Tx request: */

	app_DsrHanMsgSendTxRequest(stIe_Msg.u16_DstDeviceId);
  SleepMs(3000);

  /* Send the hanfun commando. */

  app_DsrHanMsgSend(12, stIe_Msg.u16_DstDeviceId, &st_HANMsgCtl, &stIe_Msg);
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