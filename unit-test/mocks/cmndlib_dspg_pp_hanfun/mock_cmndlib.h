/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_cmndlib.h
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
#include "CmndLib.h"
#include "CmndMsg_DeviceManagement.h"
#include "CmndMsg_KeepAlive.h"
}

class Cmndlib
{
    public:
        virtual ~Cmndlib() {}
        virtual bool p_Cmnd_DeviceManagement_CreateRegisterDeviceReq( OUT t_st_hanCmndApiMsg* pst_hanCmndApiMsg, const t_st_hanCmndIeBaseWanted* pst_baseWanted ) = 0;
        virtual u16 p_CmndApiPacket_CreateFromCmndApiMsg( OUT u8* pu8_Buffer, const t_st_hanCmndApiMsg* p_Msg ) = 0;
        virtual void p_CmndMsgLog_PrintTxBuffer( u16 u16_BufferLen, const u8* u8_Buffer ) = 0;
        virtual bool p_CmndMsg_KeepAlive_CreateImAliveReq( OUT t_st_hanCmndApiMsg* pst_hanCmndApiMsg ) = 0;
        virtual bool p_hanCmndApi_HandleByte( t_stReceiveData* context, u8 byte, OUT t_st_Msg* msg ) = 0;
        virtual bool p_CmndMsg_IeGet( IN const t_st_hanCmndApiMsg* pst_Msg, tpf_CmndIeGetter pf_Getter, OUT void* pv_IeValue, u16 u16_IeSize ) = 0;
        virtual void keepAliveTimerStart( void ) = 0;
        virtual t_en_hanCmndInfoElemType p_CMND_IE_GETTER_CMND_IE_GENERAL_STATUS( t_st_StreamBuffer* pst_Stream, void* pv_Ie ) = 0;
        virtual t_en_hanCmndInfoElemType p_CMND_IE_GETTER_CMND_IE_RESPONSE( t_st_StreamBuffer* pst_Stream, void* pv_Ie ) = 0;
        virtual t_en_hanCmndInfoElemType p_CMND_IE_GETTER_CMND_IE_REGISTRATION_RESPONSE( t_st_StreamBuffer* pst_Stream, void* pv_Ie ) = 0;
};

class MockCmndlib : public Cmndlib
{
    public:
        MOCK_METHOD2( p_Cmnd_DeviceManagement_CreateRegisterDeviceReq, bool( OUT t_st_hanCmndApiMsg* pst_hanCmndApiMsg, const t_st_hanCmndIeBaseWanted* pst_baseWanted ) );
        MOCK_METHOD2( p_CmndApiPacket_CreateFromCmndApiMsg, u16( OUT u8* pu8_Buffer, const t_st_hanCmndApiMsg* p_Msg ) );
        MOCK_METHOD2( p_CmndMsgLog_PrintTxBuffer, void( u16 u16_BufferLen, const u8* u8_Buffer ) );
        MOCK_METHOD1( p_CmndMsg_KeepAlive_CreateImAliveReq, bool( OUT t_st_hanCmndApiMsg* pst_hanCmndApiMsg ) );
        MOCK_METHOD3( p_hanCmndApi_HandleByte, bool( t_stReceiveData* context, u8 byte, OUT t_st_Msg* msg ) );
        MOCK_METHOD4( p_CmndMsg_IeGet, bool( IN const t_st_hanCmndApiMsg* pst_Msg, tpf_CmndIeGetter pf_Getter, OUT void* pv_IeValue, u16 u16_IeSize ) );
        MOCK_METHOD0( keepAliveTimerStart, void( void ) );
        MOCK_METHOD2( p_CMND_IE_GETTER_CMND_IE_GENERAL_STATUS, t_en_hanCmndInfoElemType( t_st_StreamBuffer* pst_Stream, void* pv_Ie ) );
        MOCK_METHOD2( p_CMND_IE_GETTER_CMND_IE_RESPONSE, t_en_hanCmndInfoElemType( t_st_StreamBuffer* pst_Stream, void* pv_Ie ) );
        MOCK_METHOD2( p_CMND_IE_GETTER_CMND_IE_REGISTRATION_RESPONSE, t_en_hanCmndInfoElemType( t_st_StreamBuffer* pst_Stream, void* pv_Ie ) );
};

void setMockCmndlibReference( Cmndlib* ref );
