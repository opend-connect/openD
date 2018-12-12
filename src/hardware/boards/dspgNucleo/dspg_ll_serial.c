/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       dspg_ll_serial.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief      DSPG low-level serial implementation for nucleo-l4.
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

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_9
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_10
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* UART handle. */
UART_HandleTypeDef huart1;

/* UART handle used for CMND communication. */
UART_HandleTypeDef *G_hUart = &huart1;

/* UART for debug prints. */
UART_HandleTypeDef huart2;

/* Uart RX function pointer. */
openD_ll_serial_rxCallback_t _rxCallback;

/* FIFO UART context. */
stm32l4_uart_t stm32l4_uart_01;

#define TX_FIFO_BUFFER_SIZE 255U

/* TX fifo buffer. */
uint8_t txFifoBuffer[ TX_FIFO_BUFFER_SIZE ];

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  /* BusFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  /* UsageFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  /* SVCall_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
  /* DebugMonitor_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
  /* PendSV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(huart->Instance==USART1)
  {

  /* Peripheral clock enable */
  __HAL_RCC_USART1_CLK_ENABLE();

  /* USART1 GPIO Configuration  */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; //GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Peripheral interrupt init */
  HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if (huart->Instance==USART2)
  {
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Enable USART2 clock */
    __HAL_RCC_USART2_CLK_ENABLE();

    /*##-2- Configure peripheral GPIO ##########################################*/
    /* UART TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = GPIO_PIN_2;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* UART RX GPIO pin configuration  */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }

}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==USART1)
  {

    __HAL_RCC_USART1_CLK_DISABLE();

    /* USART1 GPIO Configuration */
    HAL_GPIO_DeInit(GPIOA, USART_TX_Pin|USART_RX_Pin);

    /* Peripheral interrupt DeInit*/
    HAL_NVIC_DisableIRQ(USART1_IRQn);

  }
  /* USER CODE BEGIN USART1_MspDeInit 1 */
  if(huart->Instance==USART2)
  {

    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /* USART1 GPIO Configuration */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);

  }

  /* USER CODE END USART1_MspDeInit 1 */

}


int8_t openD_ll_serial_init( const char* instance, uint32_t baudrate,
                             openD_ll_serial_rxCallback_t rxCallback ) {

  if( ! rxCallback ) {
    return -1;
  }

  _rxCallback = rxCallback;

  huart1.Instance = USART1;
  huart1.Init.BaudRate = baudrate;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    return -1;
  }
  __HAL_UART_ENABLE_IT( &huart1, UART_IT_RXNE );

  return stm32l4_uart_init( &stm32l4_uart_01, &huart1, NULL, 0U, txFifoBuffer, TX_FIFO_BUFFER_SIZE );
}

int8_t openD_ll_serial_deInit( const char* instance ) {

  if( HAL_UART_DeInit( &huart1 ) != HAL_OK ) {
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

  if( uartHandle == &huart1 ) {
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
  HAL_UART_IRQHandler( &huart1 );
}
