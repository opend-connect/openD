/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_lowLevelSerial.cpp
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

#include "mock_lowLevelSerial.h"

/* Module pointer. */
LowLevelSerial *g_lowLevelSerial;

extern "C"{

int8_t openD_ll_serial_deInit( const char *instance ) {
   assert(g_lowLevelSerial != NULL);
   return g_lowLevelSerial->openD_ll_serial_deInit( instance);
} /* openD_ll_serial_deInit */

int8_t openD_ll_serial_init( const char *instance, uint32_t baudrate, openD_ll_serial_rxCallback_t ll_serial_rxCallback ) {
   assert(g_lowLevelSerial != NULL);
   return g_lowLevelSerial->openD_ll_serial_init( instance, baudrate, ll_serial_rxCallback);
} /* openD_ll_serial_init */

int8_t openD_ll_serial_send( uint8_t *data, uint16_t length ) {
   assert(g_lowLevelSerial != NULL);
   return g_lowLevelSerial->openD_ll_serial_send( data, length);
} /* openD_ll_serial_send */

} /* extern */

void setMockLowLevelSerialReference(LowLevelSerial *ref) {
   g_lowLevelSerial = ref;
}

