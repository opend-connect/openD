/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_opendStates.cpp
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

extern "C"{

}

#include "mock_opendStates.h"

/* Module pointer. */
OpendStates *g_opendStates;

extern "C"{

bool opend_state_call( void *param ) {
   assert(g_opendStates != NULL);
   return g_opendStates->opend_state_call( param);
} /* opend_state_call */

bool opend_state_init( void *param ) {
   assert(g_opendStates != NULL);
   return g_opendStates->opend_state_init( param);
} /* opend_state_init */

bool opend_state_standby( void *param ) {
   assert(g_opendStates != NULL);
   return g_opendStates->opend_state_standby( param);
} /* opend_state_standby */

} /* extern */

void setMockOpendStatesReference(OpendStates *ref) {
   g_opendStates = ref;
}

