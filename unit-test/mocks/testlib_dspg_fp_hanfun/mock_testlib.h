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
#include "cmbs_api.h"
#include "appcmbs.h"
}

class Testlib
{
    public:
        virtual ~Testlib() {}
        virtual void app_HanRegularStart( u8 RegisterForHanMessages ) = 0;
        virtual E_CMBS_RC app_SrvSubscriptionOpenExt( u32 u32_timeout,E_CMBS_HS_REGISTER_ENABLE e_RegEnable ) = 0;
        virtual E_CMBS_RC app_SrvSubscriptionClose( void ) = 0;
        virtual E_CMBS_RC app_DsrHanDeleteDevice( u16 u16_DeviceId, bool b_BlackList ) = 0;
        virtual E_CMBS_RC app_DsrHanDeviceReadTable( u16 u16_NumOfEntries, u16 u16_IndexOfFirstEntry, u8 isBrief ) = 0;

        virtual E_CMBS_RC cmbs_dsr_cord_OpenRegistrationExt(void * pv_AppRefHandle, u32 u32_timeout, E_CMBS_HS_REGISTER_ENABLE e_RegEnable) = 0;
        virtual E_CMBS_RC cmbs_dsr_hs_Delete( void * pv_AppRefHandle, u16 u16_Handsets ) = 0;
        virtual E_CMBS_RC cmbs_dsr_param_Set( void * pv_AppRefHandle, E_CMBS_PARAM_TYPE e_ParamType, E_CMBS_PARAM e_Param, u8 * pu8_Data, u16 u16_DataLen ) = 0;
};

class MockTestlib : public Testlib
{
    public:
        MOCK_METHOD1( app_HanRegularStart, void( u8 RegisterForHanMessages ) );
        MOCK_METHOD2( app_SrvSubscriptionOpenExt, E_CMBS_RC( u32 u32_timeout,E_CMBS_HS_REGISTER_ENABLE e_RegEnable ) );
        MOCK_METHOD0( app_SrvSubscriptionClose, E_CMBS_RC( void ) );
        MOCK_METHOD2( app_DsrHanDeleteDevice, E_CMBS_RC( u16 u16_DeviceId, bool b_BlackList ) );
        MOCK_METHOD3( app_DsrHanDeviceReadTable, E_CMBS_RC( u16 u16_NumOfEntries, u16 u16_IndexOfFirstEntry, u8 isBrief ) );

        MOCK_METHOD3( cmbs_dsr_cord_OpenRegistrationExt, E_CMBS_RC (void * pv_AppRefHandle, u32 u32_timeout, E_CMBS_HS_REGISTER_ENABLE e_RegEnable) );
        MOCK_METHOD2( cmbs_dsr_hs_Delete, E_CMBS_RC (void * pv_AppRefHandle, u16 u16_Handsets) );
        MOCK_METHOD5( cmbs_dsr_param_Set, E_CMBS_RC (void * pv_AppRefHandle, E_CMBS_PARAM_TYPE e_ParamType, E_CMBS_PARAM e_Param, u8 * pu8_Data, u16 u16_DataLen) );
};

void setMockTestlibReference( Testlib* ref );
