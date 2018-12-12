/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_iwu.h
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
#include <gmock/gmock.h>

extern "C"{
#include "mmi_def.h"
}

class Iwu
{
    public:
        virtual ~Iwu() {}
        virtual void Enable_Registration ( uint16_t AccessCode ) = 0;
        virtual void SetLED3( bool led_on ) = 0;
};

class MockIwu : public Iwu
{
    public:
        MOCK_METHOD1( Enable_Registration, void( uint16_t AccessCode ) );
        MOCK_METHOD1( SetLED3, void( bool led_on ) );
};

void setMockIwuReference( Iwu* ref );
