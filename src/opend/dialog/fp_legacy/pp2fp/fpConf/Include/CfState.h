/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#ifndef CF_STATE_H
#define CF_STATE_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include "ApiHelper.h"
#include "LasHelper.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/
// #ifndef PCCOMPILE
#define FP_AUDIO_SUPPORT //Enable audio support in FP configuration
// #endif
#define CF_STATE_TIMEOUT_KEEP 0xffff

#define DECL_STATE_FN(Name) void Name(CfMailType *p_Mail)

typedef rsuint8 Ia5CharType;

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef enum RSENUMTAG(CfStateType)
{
  CF_STATE_INIT = 0,
  CF_STATE_STANDBY,
  CF_STATE_CALL,
  CF_STATE_TOTAL
} RSENUM8(CfStateType);

typedef enum RSENUMTAG(CfSubStateType)
{
  CF_SUB_STATE_NULL=0,
  CF_INIT_SUB_STATE_1,
  CF_INIT_SUB_STATE_2,
  CF_INIT_SUB_STATE_3,
  CF_INIT_SUB_STATE_4,
  CF_INIT_SUB_STATE_5,
  CF_CALL_SUB_STATE_1,
  CF_CALL_SUB_STATE_2,
  CF_CALL_SUB_STATE_3,
  CF_CALL_SUB_STATE_4
} RSENUM8(CfSubStateType);

typedef enum RSENUMTAG(CfLocalPrimitiveIdType)
{
  CF_S_INIT = 0xff00,
  CF_S_ENTER,
  CF_S_LEAVE,
  CF_S_TIMEOUT,
  CF_S_LAST_ID,
} RSENUM16(CfLocalPrimitiveIdType);

typedef struct
{
  CfStateType CfState;
  CfStateType NextState;
  CfSubStateType CfSubState;
  rsbitfield InitState  :1;
  rsbitfield Unuseded   :7;
} CfStateCtrlType;

typedef struct
{
  rsbitfield PcmInited          :1;
  rsbitfield RegEnabled         :1;           //bit indicating that system is in registeration mode
  rsbitfield EnterRegModeReq    :1;           //bit indicating that user pressed a key to request to enter registration mode
  rsbitfield PageMode           :1;
  rsbitfield Unused             :4;
} CfSysFlagType;

typedef struct
{
  rsbitfield Registered :1;
  rsbitfield Unuseded   :7;
  rsuint8 Ipui[5];
} HsInfoType;

typedef struct
{
  rsuint8 AttachedHeadsets;
  rsbool PermanentClir;
}LasLineSettingsType;

typedef struct
{
  ApiCallReferenceType CallReference;
  ApiCallReferenceType HsId;
  ApiCcCallClassType CallClass;
} CallInfoType;

typedef struct
{
  rsuint8 RegHsNum;
  HsInfoType HsInfo[NO_HANDSETS];
  CfSysFlagType CfSysFlag;
  CallInfoType CallInfo;
#ifdef FP_AUDIO_SUPPORT
  ApiPpAudioModeType AudioMode;
#endif
} CfSysStatusType;

typedef struct
{
  CfStateCtrlType CfStateCtrl;
  CfSysStatusType CfSysStatus;

  ApiModelIdType FpModelId;
  rsuint8 Ac[4];
  rsuint8 Fpui[5];

  rsuint8 LasCurrentListIdentifier;
  LasSessionDataType LasSessionData[NUMBER_OF_LISTS_IN_LAS];
  LasLineSettingsType LasLineSettings[LS_NO_LINES];
  rsuint8 LasState[NUMBER_OF_LISTS_IN_LAS];
  rsuint8 New_Hs;
  rsuint8 Hs_No;
  rsbool ClearAttachedHs;
} CfSysCtrlType;

typedef struct
{
  CfLocalPrimitiveIdType Primitive;
} CfStateLocalTaskType;

typedef struct
{
  RosPrimitiveType  Primitive;
} CfInitTaskType;

typedef union
{
  RosMailType              RosMail;
  CfStateLocalTaskType     CfStateTaskMsg;
} CfMailType;

typedef void (*CfStateFnType)(CfMailType *p_Mail);

typedef struct
{
  CfStateFnType   StateFn;
} CfStateTblType;

/****************************************************************************
*                            Global variables/const
****************************************************************************/
extern CfSysCtrlType CfSysCtrl, *pCfSysCtrl;
extern const CfStateTblType  CF_STATE_TBL[CF_STATE_TOTAL];
extern ApiLineIdType LineIdReq;

/****************************************************************************
*                            Local variables/const
****************************************************************************/
extern void CfStartStateTimer(rsuint16 n_Time1Ms);
extern void CfStopStateTimer(void);
extern CfStateType CfGetState(void);
extern CfSubStateType CfGetSubState(void);
extern void CfSetSubState( CfSubStateType ss );
extern void CfProcessMail( rsuint8 *p_Mail  );
extern void CfSetStateExt_( CfStateType n_State, rsuint16 n_TimeOut);
extern rsbool CfIsStateChanged(void);
extern void CfSetState_(CfStateType n_State);
extern void CfEnterStateExt(CfStateType n_State, rsuint16 n_TimeOut);
extern void CfEnterState(CfStateType n_State);
extern void CfTaskInit(void);
extern void CfTaskHandler(const RosMailType* Mail);
/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
#endif //CF_STATE_H
// End of file.
