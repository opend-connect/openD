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
 * @author     Patrick Weber, Heiko Berger
 * @brief      Dialog low-level serial implementation for nucleo-l4.
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

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_uart.h"

#include "stm32l4_uart.h"

#include <stdbool.h>
#include <string.h>

/* HAL UART object. */
UART_HandleTypeDef uartHandle_01;

/* FIFO UART context. */
stm32l4_uart_t stm32l4_uart_01;

#define TX_FIFO_BUFFER_SIZE 255U

/* TX fifo buffer. */
uint8_t txFifoBuffer[ TX_FIFO_BUFFER_SIZE ];

openD_ll_serial_rxCallback_t _rxCallback;


void HAL_UART_MspInit( UART_HandleTypeDef *huart ) {
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable peripherals and GPIO Clocks. */
  __HAL_RCC_GPIOA_CLK_ENABLE( );
  __HAL_RCC_GPIOA_CLK_ENABLE( );

  /* Enable USART1 clock. */
  __HAL_RCC_USART1_CLK_ENABLE( );

  /* Configure peripheral GPIO. */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  /* UART TX GPIO pin configuration. */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );
  /* UART RX GPIO pin configuration. */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );

  /* Configure the NVIC for UART. */
  HAL_NVIC_SetPriority( USART1_IRQn, 0U, 1U );
  HAL_NVIC_EnableIRQ( USART1_IRQn );

  return;
}

void HAL_UART_MspDeInit( UART_HandleTypeDef *huart ) {

  /* Reset peripherals */
  __HAL_RCC_USART1_FORCE_RESET( );
  __HAL_RCC_USART1_RELEASE_RESET( );

  /* Disable peripherals and GPIO Clocks. */
  HAL_GPIO_DeInit( GPIOA, GPIO_PIN_9 );
  HAL_GPIO_DeInit( GPIOA, GPIO_PIN_10 );

  /* Disable the NVIC for UART. */
  HAL_NVIC_DisableIRQ( USART1_IRQn );

  return;
}


int8_t openD_ll_serial_init( const char* instance, uint32_t baudrate,
                             openD_ll_serial_rxCallback_t rxCallback ) {

  if( ! rxCallback ) {
    return -1;
  }

  _rxCallback = rxCallback;

  /* Configure the UART object */
  uartHandle_01.Instance = USART1;
  uartHandle_01.Init.BaudRate = baudrate;
  uartHandle_01.Init.WordLength = UART_WORDLENGTH_8B;
  uartHandle_01.Init.StopBits = UART_STOPBITS_2;
  uartHandle_01.Init.Parity = UART_PARITY_NONE;
  uartHandle_01.Init.HwFlowCtl = UART_HWCONTROL_NONE; /* (RTS and CTS signals) */
  uartHandle_01.Init.Mode = UART_MODE_TX_RX;

  if( HAL_UART_Init( &uartHandle_01 ) != HAL_OK ) {
    return -1;
  }

  return stm32l4_uart_init( &stm32l4_uart_01, &uartHandle_01, NULL, 0U, txFifoBuffer, TX_FIFO_BUFFER_SIZE );

}

int8_t openD_ll_serial_deInit( const char* instance ) {

  if( HAL_UART_DeInit( &uartHandle_01 ) != HAL_OK ) {
    return -1;
  }

  return 0;
}

int8_t openD_ll_serial_send( uint8_t *data, uint16_t length ) {

  stm32l4_uart_write( &stm32l4_uart_01, data, length );

  return 0;
}

/*!
 * Tx Transfer completed callback.
 */
void HAL_UART_TxCpltCallback( UART_HandleTypeDef *uartHandle ) {

  if( uartHandle == &uartHandle_01 ) {
    stm32l4_uart_txCplt( &stm32l4_uart_01 );
  }

  return;
}

/*!
 * Rx Transfer completed callback.
 */
void HAL_UART_RxCpltCallback( UART_HandleTypeDef *uartHandle ) {

  /* Call the RX callback function. */
  if( _rxCallback ) {
    _rxCallback( &stm32l4_uart_01.rxData, 0x01 );
  }

  stm32l4_uart_rxCplt( &stm32l4_uart_01 );

  return;
}

/*!
 * UART error callback.
 */
void HAL_UART_ErrorCallback( UART_HandleTypeDef *UartHandle ) {
  stm32l4_uart_rxCplt( &stm32l4_uart_01 );
}

/*!
 * UART interrupt request handler.
 */
void USART1_IRQHandler( void ) {
  HAL_UART_IRQHandler( &uartHandle_01 );
}
