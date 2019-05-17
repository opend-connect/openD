/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_lowLevelGpio.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

extern "C"{
  #include "opend_ll_gpio.h"
}

/* Module class declaration. */
class LowLevelGpio
{
public:
   virtual ~LowLevelGpio() {}
   virtual int8_t openD_ll_gpio_deInit( openD_ll_gpio_pin_t pin ) = 0;
   virtual int8_t openD_ll_gpio_init( openD_ll_gpio_pin_t pin, openD_ll_gpio_irqCallback_t ll_gpio_irqCallback ) = 0;
   virtual openD_ll_gpio_pin_state_t openD_ll_gpio_read( openD_ll_gpio_pin_t pin ) = 0;
   virtual openD_ll_gpio_buttonState_t openD_ll_gpio_readButton( openD_ll_gpio_button_ctxt_t *buttonCtxt, openD_ll_gpio_pin_t pin, openD_ll_gpio_button_debounce_t debounce ) = 0;
   virtual void openD_ll_gpio_write( openD_ll_gpio_pin_t pin, openD_ll_gpio_pin_state_t state) = 0;
};


/* Module class implementaion. */
class MockLowLevelGpio : public LowLevelGpio
{
public:
   MOCK_METHOD1(openD_ll_gpio_deInit ,  int8_t( openD_ll_gpio_pin_t pin ));
   MOCK_METHOD2(openD_ll_gpio_init ,  int8_t( openD_ll_gpio_pin_t pin, openD_ll_gpio_irqCallback_t ll_gpio_irqCallback ));
   MOCK_METHOD1(openD_ll_gpio_read ,  openD_ll_gpio_pin_state_t( openD_ll_gpio_pin_t pin ));
   MOCK_METHOD3(openD_ll_gpio_readButton ,  openD_ll_gpio_buttonState_t( openD_ll_gpio_button_ctxt_t *buttonCtxt, openD_ll_gpio_pin_t pin, openD_ll_gpio_button_debounce_t debounce ));
   MOCK_METHOD2(openD_ll_gpio_write ,  void( openD_ll_gpio_pin_t pin, openD_ll_gpio_pin_state_t state));
};

void setMockLowLevelGpioReference(LowLevelGpio *ref);
