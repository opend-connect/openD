/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_testLib.h
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
#include "apphan.h"
#include "appmsgparser.h"
}

class Testlib
{
    public:
        virtual ~Testlib() {}
        virtual void app_HanRegularStart( u8 RegisterForHanMessages ) = 0;
        virtual void initMsgParser( hsSuccessfullyRegistered registeredClb ) = 0;
        virtual E_CMBS_RC app_SrvSubscriptionOpenExt( u32 u32_timeout,E_CMBS_HS_REGISTER_ENABLE e_RegEnable ) = 0;
        virtual E_CMBS_RC app_SrvSubscriptionClose( void ) = 0;
        virtual E_CMBS_RC app_DsrHanDeleteDevice( u16 u16_DeviceId, bool b_BlackList ) = 0;
};

class MockTestlib : public Testlib
{
    public:
        MOCK_METHOD1( app_HanRegularStart, void( u8 RegisterForHanMessages ) );
        MOCK_METHOD1( initMsgParser, void( hsSuccessfullyRegistered registeredClb ) );
        MOCK_METHOD2( app_SrvSubscriptionOpenExt, E_CMBS_RC( u32 u32_timeout,E_CMBS_HS_REGISTER_ENABLE e_RegEnable ) );
        MOCK_METHOD0( app_SrvSubscriptionClose, E_CMBS_RC( void ) );
        MOCK_METHOD2( app_DsrHanDeleteDevice, E_CMBS_RC( u16 u16_DeviceId, bool b_BlackList ) );
};

void setMockTestlibReference( Testlib* ref );
