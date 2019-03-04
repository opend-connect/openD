/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       transport.cpp
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

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "application.h"

#include "apphan.h"
#include "cmbs_api.h"
#include "cmbs_util.h"
#include "appcmbs.h"
#include "appsrv.h"
#include "tcx_log.h"
#include "tcx_eep.h"
#include "tcx_util.h"
#include "appCallRouter.h"

#include "opend_sub.h"

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


void transport_init( )
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

static bool cmbs_checkResponse( void* ie_data )
{
  void* ie = NULL;
  uint16_t ieType = 0U;
  ST_IE_RESPONSE ieResponse;
  ieResponse.e_Response = CMBS_RESPONSE_ERROR;
  bool ret = false;

  if( ie_data )
  {
    cmbs_api_ie_GetFirst(ie_data, &ie, &ieType);

    while(ie != NULL)
    {
      if( CMBS_IE_RESPONSE == ieType )
      {
        cmbs_api_ie_ResponseGet(ie, &ieResponse);
        if( CMBS_RESPONSE_OK == ieResponse.e_Response )
        {
          ret = true;
          ie = NULL;
        }
      }
      cmbs_api_ie_GetNext(ie_data, &ie, &ieType);
    }
  }

  return ret;
}
int appcmbs_opend_callback(void *pv_AppRef, E_CMBS_EVENT_ID eventId, void *ie_data)
{
  openD_subApiCfm_t sConfirm;
  sConfirm.status = OPEND_STATUS_FAIL;

  /* Map confirmation and indication callbacks. */
  switch( eventId )
  {
    case CMBS_EV_DSR_CORD_OPENREG_RES:
      sConfirm.service = OPEND_SUBAPI_SUBSCRIBE_ENABLE;
      if( cmbs_checkResponse( ie_data ) ) {
        sConfirm.status = OPEND_STATUS_OK;
      }
      openD_sub_confirmation( &sConfirm );
      break;

    default:
      break;
  }

  return 0;
}
