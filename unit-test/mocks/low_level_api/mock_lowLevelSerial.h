/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_lowLevelSerial.h
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
  #include "opend_ll_serial.h"
}

/* Module class declaration. */
class LowLevelSerial
{
public:
   virtual ~LowLevelSerial() {}
   virtual int8_t openD_ll_serial_deInit( const char *instance ) = 0;
   virtual int8_t openD_ll_serial_init( const char *instance, uint32_t baudrate, openD_ll_serial_rxCallback_t ll_serial_rxCallback ) = 0;
   virtual int8_t openD_ll_serial_send( uint8_t *data, uint16_t length ) = 0;
};


/* Module class implementaion. */
class MockLowLevelSerial : public LowLevelSerial
{
public:
   MOCK_METHOD1(openD_ll_serial_deInit ,  int8_t( const char *instance ));
   MOCK_METHOD3(openD_ll_serial_init ,  int8_t( const char *instance, uint32_t baudrate, openD_ll_serial_rxCallback_t ll_serial_rxCallback ));
   MOCK_METHOD2(openD_ll_serial_send ,  int8_t( uint8_t *data, uint16_t length ));
};

void setMockLowLevelSerialReference(LowLevelSerial *ref);
