/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_iwu.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

/** Include files */
#include <assert.h>
#include <gmock/gmock.h>
#include <stdint.h>
#include "mock_iwu.h"

Iwu* ObjIwu;

extern "C"{

void Enable_Registration ( uint16_t AccessCode )
{
    assert( ObjIwu != NULL );
    ObjIwu->Enable_Registration( AccessCode );
}

void SetLED3( bool led_on )
{
    assert( ObjIwu != NULL );
    ObjIwu->SetLED3( led_on );
}

}

void setMockIwuReference( Iwu* ref )
{
    ObjIwu = ref;
}
