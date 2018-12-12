/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_opend.cpp
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

#include "mock_opend.h"

/* Module pointer. */
Opend *g_Opend;

extern "C"{

openD_status_t openD_init( void* port ){
    assert( g_Opend != NULL );
    return g_Opend->openD_init( port );
}

openD_status_t openD_api_getStatus( void ){
    assert( g_Opend != NULL );
    return g_Opend->openD_api_getStatus( );
}

void openD_setStatusBusy( void ){
    assert( g_Opend != NULL );
    g_Opend->openD_setStatusBusy( );
}

void openD_setStatusIdle( void ){
    assert( g_Opend != NULL );
    g_Opend->openD_setStatusIdle( );
}

} /* extern */

void setMockOpendReference(Opend *ref) {
   g_Opend = ref;
}

