/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       dialog_ll_serial.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */

#include "opend_ll_serial.h"
#include "serialPort.h"

#include <stdint.h>


int8_t openD_ll_serial_init( const char *instance, uint32_t baudrate,
                             openD_ll_serial_rxCallback_t ll_serial_rxCallback ) {

  serialPort_init_t serialPort_init;
  serialPort_init.portname = instance;
  serialPort_init.baudrate = E_SERIAL_PORT_BAUDRATE_115200;
  serialPort_init.rxBytesBlock = 1U;

  return (int8_t) serialPort_open( &serialPort_init, ll_serial_rxCallback );
}

int8_t openD_ll_serial_deInit( const char *instance ) {

  return (int8_t) serialPort_close( );
}

int8_t openD_ll_serial_send( uint8_t *data, uint16_t length ) {

  return serialPort_write( data, length );
}
