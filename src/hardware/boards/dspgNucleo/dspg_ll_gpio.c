/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       dspg_ll_gpio.c
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

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"

#include "opend_ll_gpio.h"

#include <stdint.h>
#include <stdbool.h>


int8_t openD_ll_gpio_init( openD_ll_gpio_pin_t pin, openD_ll_gpio_irqCallback_t ll_gpio_irqCallback ) {

  int8_t ret = 0;
  GPIO_InitTypeDef GPIO_InitStruct;

  switch( pin ) {
    case OPEND_LL_GPIO_PIN_USER_BUTTON_01:

      /* Enable peripherals and GPIO Clocks. */
      __HAL_RCC_GPIOC_CLK_ENABLE( );

      /* Configure peripheral GPIO. */
      GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
      GPIO_InitStruct.Pin = OPEND_LL_GPIO_PIN_USER_BUTTON_01_Pin;
      HAL_GPIO_Init( OPEND_LL_GPIO_PIN_USER_BUTTON_01_Port, &GPIO_InitStruct );
      break;

    case OPEND_LL_GPIO_PIN_USER_LED_01:

      /* Enable peripherals and GPIO Clocks. */
      __HAL_RCC_GPIOA_CLK_ENABLE( );

      /* Configure peripheral GPIO. */
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
      GPIO_InitStruct.Pin = OPEND_LL_GPIO_PIN_USER_LED_01_Pin;
      HAL_GPIO_Init( OPEND_LL_GPIO_PIN_USER_LED_01_Port, &GPIO_InitStruct );
      break;

    default:
      ret = -1;
      break;
  }

  return ret;
}

int8_t openD_ll_gpio_deInit( openD_ll_gpio_pin_t pin ) {

  int8_t ret = 0;

  switch( pin ) {
    case OPEND_LL_GPIO_PIN_USER_BUTTON_01:
      HAL_GPIO_DeInit(OPEND_LL_GPIO_PIN_USER_BUTTON_01_Port, OPEND_LL_GPIO_PIN_USER_BUTTON_01_Pin);
      break;

    case OPEND_LL_GPIO_PIN_USER_LED_01:
      HAL_GPIO_DeInit(OPEND_LL_GPIO_PIN_USER_LED_01_Port, OPEND_LL_GPIO_PIN_USER_LED_01_Pin);
      break;

    default:
      ret = -1;
      break;
  }

  return ret;
}

void openD_ll_gpio_write( openD_ll_gpio_pin_t pin, openD_ll_gpio_pin_state_t state) {

  switch( pin ) {
    case OPEND_LL_GPIO_PIN_USER_LED_01:
      HAL_GPIO_WritePin( OPEND_LL_GPIO_PIN_USER_LED_01_Port, OPEND_LL_GPIO_PIN_USER_LED_01_Pin, (GPIO_PinState) state);
      break;

    default:
      break;
  }

  return;
}

openD_ll_gpio_pin_state_t openD_ll_gpio_read( openD_ll_gpio_pin_t pin ) {

  openD_ll_gpio_pin_state_t state = OPEND_LL_GPIO_PIN_RESET;

  switch( pin ) {
    case OPEND_LL_GPIO_PIN_USER_BUTTON_01:
      state =  HAL_GPIO_ReadPin( OPEND_LL_GPIO_PIN_USER_BUTTON_01_Port, OPEND_LL_GPIO_PIN_USER_BUTTON_01_Pin);
      break;

    default:
      break;
  }

  return state;
}

openD_ll_gpio_buttonState_t openD_ll_gpio_readButton( openD_ll_gpio_button_ctxt_t *buttonCtxt,
                                                      openD_ll_gpio_pin_t pin ) {

  openD_ll_gpio_buttonState_t state = OPEND_LL_GPIO_BUTTON_NOT_PRESSED;
  uint32_t currentTicks = (uint32_t) HAL_GetTick();

  if( OPEND_LL_GPIO_PIN_RESET == openD_ll_gpio_read( pin ) ) {

    if( BUTTON_INIT == buttonCtxt->status ) {
      buttonCtxt->buttonPressTime = currentTicks;
      buttonCtxt->status = BUTTON_PENDING;
    }

    if( BUTTON_PENDING == buttonCtxt->status ) {
      if ( ( currentTicks - buttonCtxt->buttonPressTime ) > 10U ) {
        state = OPEND_LL_GPIO_BUTTON_PRESSED;
        buttonCtxt->status = BUTTON_PRESSED;
      }
    }
    else if ( BUTTON_PRESSED == buttonCtxt->status ) {
      if( ( currentTicks - buttonCtxt->buttonPressTime ) > 1000U ) {
        buttonCtxt->status = BUTTON_INIT;
      }
    }
  } else {
    if( ( currentTicks - buttonCtxt->buttonPressTime ) > 1000U ) {
      buttonCtxt->status = BUTTON_INIT;
    }
  }

  return state;
}
