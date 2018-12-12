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

#include "opend_ll.h"
#include "opend_ll_serial.h"

#include "hdlc.h"

#include "opend_dataTypes.h"
#include "opend_api.h"

void serialPort_rxCallback( uint8_t* data, uint16_t length ) {

  hdlc_packetParseBytewise( data );
  return;
}

openD_status_t openD_init( void *port )
{

    openD_ll_serial_init( (char *) port, 115200U, serialPort_rxCallback );

    return OPEND_STATUS_OK;
}

#ifdef __cplusplus
}
#endif
