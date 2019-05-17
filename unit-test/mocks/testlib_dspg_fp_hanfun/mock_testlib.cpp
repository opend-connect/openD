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

ST_CMBS_APPL g_cmbsappl;

void app_HanRegularStart( u8 RegisterForHanMessages )
{
    assert( ObjTestlib != NULL );
    ObjTestlib->app_HanRegularStart( RegisterForHanMessages );
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

E_CMBS_RC app_DsrHanDeviceReadTable( u16 u16_NumOfEntries, u16 u16_IndexOfFirstEntry, u8 isBrief )
{
    assert( ObjTestlib != NULL );
    return ObjTestlib->app_DsrHanDeviceReadTable( u16_NumOfEntries, u16_IndexOfFirstEntry, isBrief );
}

E_CMBS_RC	cmbs_dsr_cord_OpenRegistrationExt(void * pv_AppRefHandle, u32 u32_timeout, E_CMBS_HS_REGISTER_ENABLE e_RegEnable){
    assert(ObjTestlib!=NULL);
    ObjTestlib->cmbs_dsr_cord_OpenRegistrationExt( pv_AppRefHandle, u32_timeout, e_RegEnable);
}

E_CMBS_RC	cmbs_dsr_hs_Delete(void * pv_AppRefHandle, u16 u16_Handsets){
    assert(ObjTestlib!=NULL);
    ObjTestlib->cmbs_dsr_hs_Delete( pv_AppRefHandle, u16_Handsets);
}

E_CMBS_RC	cmbs_dsr_param_Set(void * pv_AppRefHandle, E_CMBS_PARAM_TYPE e_ParamType, E_CMBS_PARAM e_Param, u8 * pu8_Data, u16 u16_DataLen){
    assert(ObjTestlib!=NULL);
    ObjTestlib->cmbs_dsr_param_Set( pv_AppRefHandle, e_ParamType, e_Param, pu8_Data, u16_DataLen);
}

}

void setMockTestlibReference( Testlib* ref )
{
    ObjTestlib = ref;
}
