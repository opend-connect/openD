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
 * @file       opend_ll_gpio.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD low-level gpio API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_LOW_LEVEL_GPIO_API openD low-level GPIO API
 *             This module specifies the low-level GPIO API of openD connect.
 * \{
 */

#ifndef __OPEND_LL_GPIO_H__
#define __OPEND_LL_GPIO_H__

#include <stdint.h>

#include "opend_ll_config.h"

/*!
  * @brief   GPIO bit RESET and bit SET enumeration.
  */
typedef enum {
  OPEND_LL_GPIO_PIN_RESET = 0,
  OPEND_LL_GPIO_PIN_SET
} openD_ll_gpio_pin_state_t;

typedef enum {
  BUTTON_INIT = 0,
  BUTTON_PENDING,
  BUTTON_PRESSED,
} openD_ll_gpio_buttonStatus_t;

typedef struct {
  openD_ll_gpio_pin_t pin;
  openD_ll_gpio_buttonStatus_t status;
  uint64_t buttonPressTime;
} openD_ll_gpio_button_ctxt_t;

typedef enum {
  OPEND_LL_GPIO_BUTTON_NOT_DEBOUNCE = 0,
  OPEND_LL_GPIO_BUTTON_DEBOUNCE
} openD_ll_gpio_button_debounce_t;

typedef enum {
  OPEND_LL_GPIO_BUTTON_NOT_PRESSED = 0,
  OPEND_LL_GPIO_BUTTON_PRESSED
} openD_ll_gpio_buttonState_t;

/*!
 * @brief   GPIO IRQ primitive.
 */
typedef void ( *openD_ll_gpio_irqCallback_t )( openD_ll_gpio_pin_t pin, openD_ll_gpio_pin_state_t state );

/*!
 * @brief   openD low-level GPIO API initialization.
 *
 * @details Initialize the GPIO peripheral.
 *
 * @param   pin                 GPIO pin.
 * @param   ll_gpio_irqCallback IRQ callback function pointer (optional).
 *
 * @retval  int8_t Status of the operation.
 */
int8_t openD_ll_gpio_init( openD_ll_gpio_pin_t pin, openD_ll_gpio_irqCallback_t ll_gpio_irqCallback );

/*!
 * @brief   openD low-level GPIO API de-initialization.
 *
 * @details De-initialize the GPIO peripheral.
 *
 * @param   pin GPIO pin.
 *
 * @retval  Status of the operation.
 */
int8_t openD_ll_gpio_deInit( openD_ll_gpio_pin_t pin );

/*!
 * @brief   openD low-level GPIO API set.
 *
 * @details Writes a GPIO pin.
 *
 * @param   pin GPIO pin.
 * @param   state State of the GPIO pin.
 */
void openD_ll_gpio_write( openD_ll_gpio_pin_t pin, openD_ll_gpio_pin_state_t state);

/*!
 * @brief   openD low-level GPIO API set.
 *
 * @details Writes a GPIO pin.
 *
 * @param   pin GPIO pin.
 * @param   state State of the GPIO pin.
 */
openD_ll_gpio_pin_state_t openD_ll_gpio_read( openD_ll_gpio_pin_t pin );


openD_ll_gpio_buttonState_t openD_ll_gpio_readButton( openD_ll_gpio_button_ctxt_t *buttonCtxt,
                                                      openD_ll_gpio_pin_t pin,
                                                      openD_ll_gpio_button_debounce_t debounce );

/*! @} defgroup OPEND_LOW_LEVEL_GPIO_API */

#endif  // __OPEND_LL_GPIO_H__

#ifdef __cplusplus
}
#endif
