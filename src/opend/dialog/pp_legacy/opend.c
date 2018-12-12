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
 * @file       opend.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD API.
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
#include "HostUtil.h"

#include "hdlc.h"
#include "HdlcHost.h"

#include "opend_ll.h"

#include "opend_dataTypes.h"
#include "opend_api.h"

#include <stdio.h>

static openD_status_t opendApiStatus = OPEND_STATUS_FAIL;

void serialPort_rxCallback( uint8_t* data, uint16_t length ) {

  hdlc_packetParseBytewise( data );

  return;
}

openD_status_t openD_init( void *port )
{

    openD_ll_init( serialPort_rxCallback );

    /* Initialization HDLC. */
    hdlc_hostInit( );

    LocalMainAppTaskInit();

    return OPEND_STATUS_OK;
}

openD_status_t openD_api_getStatus( void ) {
  return opendApiStatus;
}

void openD_setStatusBusy( void ) {
  opendApiStatus = OPEND_STATUS_BUSY;
}

void openD_setStatusIdle( void ) {
  opendApiStatus = OPEND_STATUS_IDLE;
}

#ifdef __cplusplus
}
#endif
