/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       lptim.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief      openD hardware timer.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */

#include <stdbool.h>
#include <string.h>

#include "stm32l4xx_hal.h"
#include "lptim.h"


/* TIM handle declaration */
LPTIM_HandleTypeDef LptimHandle;

/* Set the Maximum value of the counter */
uint32_t Period = 0;

/* Set the Timeout value */
uint32_t Timeout = 0;

/* Upper layer low power timer timeout event function */
static lp_timer_callback timeoutNotify;


/*!
 * Enable Low Speed Clock (LSI)
 */
static void LSI_ClockEnable(void);

/*!
 * @brief   HAL LPTIM initialization.
 *
 * @details Initialize an LPTIM object.
 *
 * @param   hlptim LPTIM object to initialize.
 */
void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef *hlptim);


static void LSI_ClockEnable(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;

  /* Enable LSI clock */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Re-target the LSI to Clock the LPTIM Counter */
  RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPTIM1;
  RCC_PeriphCLKInitStruct.Lptim1ClockSelection = RCC_LPTIM1CLKSOURCE_LSI;  
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);
}

void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef *hlptim)
{
  /* GPIO_InitTypeDef GPIO_InitStruct; */

  /* Enable LPTIM clock */
  __HAL_RCC_LPTIM1_CLK_ENABLE();

  /* Force the LPTIM Periheral Clock Reset */
  __HAL_RCC_LPTIM1_FORCE_RESET();

  /* Release the LPTIM Periheral Clock Reset */
  __HAL_RCC_LPTIM1_RELEASE_RESET();

  /* Enable and set LPTIM Interrupt to the highest priority */
  HAL_NVIC_SetPriority(LPTIM1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(LPTIM1_IRQn);

  /* Enable the LSE source */
  LSI_ClockEnable();
}

int8_t lp_timer_init( lp_timer_callback ll_timer_callback )
{
  timeoutNotify = ll_timer_callback;

  LptimHandle.Instance = LPTIM1;
  LptimHandle.Init.Clock.Source       = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
  LptimHandle.Init.Clock.Prescaler    = LPTIM_PRESCALER_DIV1;
  LptimHandle.Init.Trigger.Source     = LPTIM_TRIGSOURCE_SOFTWARE;
  LptimHandle.Init.UpdateMode         = LPTIM_UPDATE_IMMEDIATE;
  LptimHandle.Init.OutputPolarity     = LPTIM_OUTPUTPOLARITY_HIGH;
  LptimHandle.Init.CounterSource      = LPTIM_COUNTERSOURCE_INTERNAL;

  /* Initialize LPTIM peripheral according to the passed parameters */
  if (HAL_LPTIM_Init(&LptimHandle) != HAL_OK)
  {
    return -1;
  }

  return 0;
}

int8_t lp_timer_start( uint32_t period, uint32_t timeout )
{
  Period = period;
  Timeout = timeout;
  /*
   *  Period = 65535
   *  Pulse  = 37000 - 1
   *  LSI_Frequency (LSI_VALUE) = 37000Hz
   *  According to this configuration (LPTIMER clocked by LSI & compare = 18499,
   *  the Timeout period = (compare + 1)/LSI_Frequency = 1s
   */
  if (HAL_LPTIM_TimeOut_Start_IT(&LptimHandle, period, timeout) != HAL_OK)
  {
    return -1;
  }
  return 0;
}

void HAL_LPTIM_CompareMatchCallback(LPTIM_HandleTypeDef *hlptim)
{
  timeoutNotify(500);

  /* Start the interrupt based low power timer */
  HAL_LPTIM_SetOnce_Start_IT(&LptimHandle, Period, Timeout);
}

void LPTIM1_IRQHandler(void)
{
  HAL_LPTIM_IRQHandler(&LptimHandle);
}
