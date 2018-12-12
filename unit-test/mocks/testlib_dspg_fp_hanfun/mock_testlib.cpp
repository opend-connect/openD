/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_testLib.cpp
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
#include "mock_testlib.h"

Testlib* ObjTestlib;

extern "C"{


void app_HanRegularStart( u8 RegisterForHanMessages )
{
    assert( ObjTestlib != NULL );
    ObjTestlib->app_HanRegularStart( RegisterForHanMessages );
}

void initMsgParser( hsSuccessfullyRegistered registeredClb )
{
    assert( ObjTestlib != NULL );
    ObjTestlib->initMsgParser( registeredClb );
}

E_CMBS_RC app_SrvSubscriptionOpenExt( u32 u32_timeout,E_CMBS_HS_REGISTER_ENABLE e_RegEnable )
{
    assert( ObjTestlib != NULL );
    return ObjTestlib->app_SrvSubscriptionOpenExt( u32_timeout, e_RegEnable );
}

E_CMBS_RC app_SrvSubscriptionClose( void )
{
    assert( ObjTestlib != NULL );
    return ObjTestlib->app_SrvSubscriptionClose( );
}

E_CMBS_RC app_DsrHanDeleteDevice( u16 u16_DeviceId, bool b_BlackList )
{
    assert( ObjTestlib != NULL );
    return ObjTestlib->app_DsrHanDeleteDevice( u16_DeviceId, b_BlackList );
}

}

void setMockTestlibReference( Testlib* ref )
{
    ObjTestlib = ref;
}
