/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_msManager.cpp
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
#include "msManager.h"
}

#include "mock_msManager.h"

/* Module pointer. */
MsManager *g_MsManager;

extern "C"{

void msManager_changeState( msManager_ctxt_t * const ctxt, const msManager_state_t state ) {
   assert(g_MsManager != NULL);
   g_MsManager->msManager_changeState( ctxt, state );
} /* msManager_changeState */

bool msManager_handleService( msManager_ctxt_t * const ctxt, msManager_message_t * const message ) {
   assert(g_MsManager != NULL);
   return g_MsManager->msManager_handleService( ctxt, message );
} /* msManager_handleService */

void msManager_init( msManager_ctxt_t * const ctxt, const msManager_stateFct_t states[], const msManager_state_t statesNum ) {
   assert(g_MsManager != NULL);
   g_MsManager->msManager_init( ctxt, states, statesNum );
} /* msManager_init */

} /* extern */

void setMockMsManagerReference(MsManager *ref) {
   g_MsManager = ref;
}

