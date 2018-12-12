/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       stm32l4_uart.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      STM32L4 UART
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */

#include "stm32l4_uart.h"

#include "fifo.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_uart.h"

#include <stdbool.h>
#include <string.h>

static uint8_t txData;

int8_t stm32l4_uart_init( stm32l4_uart_t *ctxt, UART_HandleTypeDef *uartHandle,
                          uint8_t *rxFifoBuffer, uint16_t rxFifoBufferSize,
                          uint8_t *txFifoBuffer, uint16_t txFifoBufferSize ) {

  if( (rxFifoBufferSize && (!rxFifoBuffer)) ||
      (txFifoBufferSize && (!txFifoBuffer)) ) {
        return -1;
  }
  ctxt->uartHandle = uartHandle;

  openD_fifo_init(&ctxt->fifoBufferTx, txFifoBuffer, txFifoBufferSize);
  openD_fifo_init(&ctxt->fifoBufferRx, rxFifoBuffer, rxFifoBufferSize);

  /* Activate the RX callback */
  HAL_UART_Receive_IT( ctxt->uartHandle, &ctxt->rxData, 0x01 );

  return 0;
}

uint16_t stm32l4_uart_write( stm32l4_uart_t *uart, uint8_t *data, uint16_t length ) {

  /* Checks if free space in the FIFO. */
  if( length > openD_fifo_remaining( &uart->fifoBufferTx ) ) {
    return 0U;
  }

  bool txFifoTx = openD_fifo_isEmpty( &uart->fifoBufferTx );

  for( uint16_t i = 0U; i < length; i++ ) {
    openD_fifo_write( &uart->fifoBufferTx, data[i] );
  }

  if( txFifoTx ) {
    if( openD_fifo_read( &uart->fifoBufferTx, &txData ) ) {

      /* Start the transmission process */
      if( HAL_UART_Transmit_IT( uart->uartHandle, &txData, 0x01 ) == HAL_OK ) {
        return length;
      }
    }
  } else {
    return length;
  }

  return 0U;
}

uint16_t stm32l4_uart_read( stm32l4_uart_t *uart, uint8_t *buffer, uint16_t length ) {

  uint16_t i;

  if( !buffer ) {
    return 0U;
  }

  for( i = 0U; i < length; i++ ) {
    if( !openD_fifo_read( &uart->fifoBufferRx, &buffer[i] ) ) {
      break;
    }
  }

  return i;
}

void stm32l4_uart_txCplt( stm32l4_uart_t *uart ) {

  if( openD_fifo_read( &uart->fifoBufferTx, &txData ) ) {
    /* Start the transmission process again. */
    HAL_UART_Transmit_IT( uart->uartHandle, &txData, 0x01 );
  }

  return;
}

void stm32l4_uart_rxCplt( stm32l4_uart_t *uart ) {

  /* Put UART peripheral in reception process */
  HAL_UART_Receive_IT( uart->uartHandle, &uart->rxData, 0x01 );

  return;
}
