/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       iwu_serial.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "iwu_serial.h"
#include "opend_ll_serial.h"

/*! Structure to store incoming at commands. */
typedef struct{
  uint8_t iwuCmdBuffer[256];
  uint16_t bytesWritten;
} iwuRxCmdBuffer_t;

uint32_t baudrate = 115200;

uint32_t Period = 65535;

uint32_t Timeout = 18500 - 1;

/*! Store incoming commands. */
static iwuRxCmdBuffer_t rxCmdBuffer;

/* UART instance 1, currently 2 is out of use */
static const char uart1 = 1;

/* Function pointer to notify that an at command is received. */
static notify_at_command at_command_callback;

/*!
 * @brief   Serial RX callback notify.
 *
 * @details Read the received 10 bytes and send them back.
 */
static void _serial_rxNotify( uint8_t *buffer, uint16_t len )
{
  memcpy(&rxCmdBuffer.iwuCmdBuffer[rxCmdBuffer.bytesWritten], buffer, len);
  rxCmdBuffer.bytesWritten += len;

    if(*buffer == '\n')
    {
      if(!at_command_callback) return;

      at_command_callback(rxCmdBuffer.iwuCmdBuffer, rxCmdBuffer.bytesWritten);
      rxCmdBuffer.bytesWritten = 0;
    }
}

int8_t iwu_serial_init(notify_at_command at_command)
{
  at_command_callback = at_command;

  rxCmdBuffer.bytesWritten = 0;

  return openD_ll_serial_init( &uart1, 115200, &_serial_rxNotify);
}

int8_t iwu_serial_send(uint8_t *data, uint16_t len)
{
  openD_ll_serial_send( data, len );
  return 0;
}
