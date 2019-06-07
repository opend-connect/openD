/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mockcmdlib.cpp
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
#include "mock_cmndlib.h"

Cmndlib* ObjCmndlib;

bool p_Cmnd_DeviceManagement_CreateRegisterDeviceReq( OUT t_st_hanCmndApiMsg* pst_hanCmndApiMsg, const t_st_hanCmndIeBaseWanted* pst_baseWanted )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_Cmnd_DeviceManagement_CreateRegisterDeviceReq( pst_hanCmndApiMsg, pst_baseWanted );
}

u16 p_CmndApiPacket_CreateFromCmndApiMsg( OUT u8* pu8_Buffer, const t_st_hanCmndApiMsg* p_Msg )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_CmndApiPacket_CreateFromCmndApiMsg( pu8_Buffer, p_Msg );
}

void p_CmndMsgLog_PrintTxBuffer( u16 u16_BufferLen, const u8* u8_Buffer )
{
    assert( ObjCmndlib != NULL );
    ObjCmndlib->p_CmndMsgLog_PrintTxBuffer( u16_BufferLen, u8_Buffer );
}

bool p_CmndMsg_KeepAlive_CreateImAliveReq( OUT t_st_hanCmndApiMsg* pst_hanCmndApiMsg )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_CmndMsg_KeepAlive_CreateImAliveReq( pst_hanCmndApiMsg );
}

bool p_CmndMsg_OnOff_CreateToggleReq( OUT t_st_hanCmndApiMsg* pst_hanCmndApiMsg, u8 u8_UnitId )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_CmndMsg_OnOff_CreateToggleReq( pst_hanCmndApiMsg, u8_UnitId );
}

bool p_hanCmndApi_HandleByte( t_stReceiveData* context, u8 byte, OUT t_st_Msg* msg )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_hanCmndApi_HandleByte( context, byte, msg );
}

bool p_CmndMsg_IeGet( IN const t_st_hanCmndApiMsg* pst_Msg, tpf_CmndIeGetter pf_Getter, OUT void* pv_IeValue, u16 u16_IeSize )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_CmndMsg_IeGet( pst_Msg, pf_Getter, pv_IeValue, u16_IeSize );
}

void keepAliveTimerStart( void )
{
    assert( ObjCmndlib != NULL );
    ObjCmndlib->keepAliveTimerStart( );
}

bool p_CmndMsg_System_CreateResetReq( OUT t_st_hanCmndApiMsg* pst_hanCmndApiMsg )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_CmndMsg_System_CreateResetReq( pst_hanCmndApiMsg );
}

t_en_hanCmndInfoElemType p_CMND_IE_GETTER_CMND_IE_GENERAL_STATUS( t_st_StreamBuffer* pst_Stream, void* pv_Ie )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_CMND_IE_GETTER_CMND_IE_GENERAL_STATUS( pst_Stream, pv_Ie );
}

t_en_hanCmndInfoElemType p_CMND_IE_GETTER_CMND_IE_RESPONSE( t_st_StreamBuffer* pst_Stream, void* pv_Ie )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_CMND_IE_GETTER_CMND_IE_RESPONSE( pst_Stream, pv_Ie );
}

t_en_hanCmndInfoElemType p_CMND_IE_GETTER_CMND_IE_REGISTRATION_RESPONSE( t_st_StreamBuffer* pst_Stream, void* pv_Ie )
{
    assert( ObjCmndlib != NULL );
    return ObjCmndlib->p_CMND_IE_GETTER_CMND_IE_REGISTRATION_RESPONSE( pst_Stream, pv_Ie );
}

void setMockCmndlibReference( Cmndlib* ref )
{
    ObjCmndlib = ref;
}
