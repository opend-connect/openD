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

#include "HostUtil.h"
#include "CfState.h"
#include "Util.h"
#include "HdlcHost.h"

#include "msManager.h"

#include "hdlc.h"
#include "opend_ll_serial.h"

#include "opend_states.h"
#include "opend_dataTypes.h"
#include "opend.h"
#include "opend_api.h"

#define ARRAY_SIZEOF(x)  (sizeof(x) / sizeof((x)[0]))

static openD_status_t opendApiStatus = OPEND_STATUS_FAIL;

const msManager_stateFct_t opend_states[] =
{
  opend_state_init,
  opend_state_standby,
  opend_state_call
};

CfSysCtrlType CfSysCtrl, *pCfSysCtrl;


static void _uartRxCallback( uint8_t *data, uint16_t len )
{
  hdlc_packetParseBytewise( data );
  return;
}

openD_status_t openD_init( void *port )
{
    if( !port ) {
      return OPEND_STATUS_ARGUMENT_INVALID;
    }

    pCfSysCtrl = &CfSysCtrl;
    util_memset((void *)(&pCfSysCtrl->CfSysStatus), 0, sizeof(CfSysStatusType));

    /* Initialization of message state manager. */
    msManager_init( &opendStateCtxt, opend_states, ARRAY_SIZEOF(opend_states) );


    /* Initialize serial port. */
    if( 0 > openD_ll_serial_init( (char*) port, 115200, _uartRxCallback ) ) {
      return OPEND_STATUS_ARGUMENT_INVALID;
    }


    /* Init HDLC driver. */
    hdlc_hostInit();

    /* Init Dialog hardware. */
    if( dialogHost_init() )
    {
      return OPEND_STATUS_FAIL;
    }

    opendApiStatus = OPEND_STATUS_IDLE;
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
