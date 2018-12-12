#ifdef __cplusplus
extern "C" {
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
 * @file       stm32l4_uart.h
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
 * @defgroup   UART_API UART
 * \{
 */

#ifndef __STM32L4_UART_H__
#define __STM32L4_UART_H__

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_uart.h"

#include "fifo.h"

#include <stdint.h>

typedef struct {
  UART_HandleTypeDef* uartHandle;
  /* FIFO buffer RX object */
  fifo_t fifoBufferRx;
  /* FIFO buffer TX object */
  fifo_t fifoBufferTx;
  uint8_t rxData;
} stm32l4_uart_t;

int8_t stm32l4_uart_init( stm32l4_uart_t *ctxt, UART_HandleTypeDef *uartHandle,
                          uint8_t *rxFifoBuffer, uint16_t rxFifoBufferSize,
                          uint8_t *txFifoBuffer, uint16_t txFifoBufferSize );

uint16_t stm32l4_uart_write( stm32l4_uart_t *uart, uint8_t *data, uint16_t length );

uint16_t stm32l4_uart_read( stm32l4_uart_t *uart, uint8_t *buffer, uint16_t length );

void stm32l4_uart_txCplt( stm32l4_uart_t *uart );

void stm32l4_uart_rxCplt( stm32l4_uart_t *uart );


/*! @} defgroup UART_API */

#endif  // __STM32L4_UART_H__

#ifdef __cplusplus
}
#endif
