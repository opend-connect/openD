/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_lowLevelGpio.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

#include <gmock/gmock.h>

#include "mock_lowLevelGpio.h"

/* Module pointer. */
LowLevelGpio *g_lowLevelGpio;

extern "C"{

int8_t openD_ll_gpio_deInit( openD_ll_gpio_pin_t pin ) {
   assert(g_lowLevelGpio != NULL);
   return g_lowLevelGpio->openD_ll_gpio_deInit( pin);
} /* openD_ll_gpio_deInit */

int8_t openD_ll_gpio_init( openD_ll_gpio_pin_t pin, openD_ll_gpio_irqCallback_t ll_gpio_irqCallback ) {
   assert(g_lowLevelGpio != NULL);
   return g_lowLevelGpio->openD_ll_gpio_init( pin, ll_gpio_irqCallback);
} /* openD_ll_gpio_init */

openD_ll_gpio_pin_state_t openD_ll_gpio_read( openD_ll_gpio_pin_t pin ) {
   assert(g_lowLevelGpio != NULL);
   return g_lowLevelGpio->openD_ll_gpio_read( pin);
} /* openD_ll_gpio_read */

openD_ll_gpio_buttonState_t openD_ll_gpio_readButton( openD_ll_gpio_button_ctxt_t *buttonCtxt, openD_ll_gpio_pin_t pin ) {
   assert(g_lowLevelGpio != NULL);
   return g_lowLevelGpio->openD_ll_gpio_readButton( buttonCtxt, pin);
} /* openD_ll_gpio_readButton */

void openD_ll_gpio_write( openD_ll_gpio_pin_t pin, openD_ll_gpio_pin_state_t state) {
   assert(g_lowLevelGpio != NULL);
   g_lowLevelGpio->openD_ll_gpio_write( pin, state);
} /* openD_ll_gpio_write */

} /* extern */

void setMockLowLevelGpioReference(LowLevelGpio *ref) {
   g_lowLevelGpio = ref;
}

