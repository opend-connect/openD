/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_lowLevel.cpp
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

#include "mock_lowLevel.h"

/* Module pointer. */
LowLevel *g_lowLevel;

extern "C"{

int8_t openD_ll_deInit( void ) {
   assert(g_lowLevel != NULL);
   return g_lowLevel->openD_ll_deInit();
} /* openD_ll_deInit */

int8_t openD_ll_init( openD_serialPort_rxCallback_t serialPort_rxCallback  ) {
   assert(g_lowLevel != NULL);
   return g_lowLevel->openD_ll_init( serialPort_rxCallback );
} /* openD_ll_init */

} /* extern */

void setMockLowLevelReference(LowLevel *ref) {
   g_lowLevel = ref;
}

