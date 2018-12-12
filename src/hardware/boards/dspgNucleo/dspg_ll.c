/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       dspg_ll.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      DSPG low-level API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */

#include "opend_ll.h"
#include "opend_ll_gpio.h"
#include "opend_ll_serial.h"

#include "mcu.h"
#include "lptim.h"

#include <stdint.h>
#include <stddef.h>


/* Set the Maximum value of the counter */
#define Period               (uint32_t) 65535

/* Set the Timeout value */
#define Timeout              (uint32_t) (18500 - 1)


int8_t openD_ll_init( openD_serialPort_rxCallback_t serialPort_rxCallback ) {

  /* MCU initialization. */
  mcu_init();

  openD_ll_gpio_init( OPEND_LL_GPIO_PIN_USER_BUTTON_01, NULL );
  openD_ll_gpio_init( OPEND_LL_GPIO_PIN_USER_LED_01, NULL );

  return 0;
}
