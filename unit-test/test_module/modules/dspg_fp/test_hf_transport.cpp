/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       test_hf_transport.cpp
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

}

void HF::ULE::Transport::receive (const uint8_t dev_id, const uint8_t data[], size_t size)
{

}

HF::ULE::Link * HF::ULE::Transport::find_by_id (uint16_t dev)
{

   return nullptr;
}

HF::ULE::Link * HF::ULE::Transport::find_by_address (uint16_t address)
{
   return nullptr;
}

void HF::ULE::Link::send (HF::Common::ByteArray &array)
{

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

}
