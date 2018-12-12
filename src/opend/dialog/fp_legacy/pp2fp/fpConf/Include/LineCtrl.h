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
#ifndef LINE_CTRL_H
#define LINE_CTRL_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include "ApiHelper.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef enum LineIdType
{
  LINE_1,
  LINE_2,
  LINE_3,
  LINE_4,
  TOTAL_LINE_NUM
} LineIdType;

typedef enum LineStateType
{
  LS_UNPLUGGED,
  LS_INCOMING_CALL,
  LS_ON_HOOK,
  LS_OFF_HOOK,
  LS_CALL_INITIATED,
  LS_CALL_PROC,
  LS_CALL_DELIVERED,
  LS_INVALID
} LineStateType;

typedef enum LsPrimitiveType
{
  LS_PING_IND,
  LS_PING_RES,
  LS_SETUP_IND,
  LS_PCM_LOOPBACK_IND,
  LS_SETUP_RES,
  LS_CONNECT_IND,
  LS_ALERT_IND,
  LS_REJECT_IND,
  LS_RELEASE_IND,
  LS_CLIP_IND,
  LS_CODEC_IND,
  LS_CODEC_CFM,

  LS_INVALID_PRIMITIVE = 0xFFFF
} LsPrimitiveType;

typedef struct
{
  LsPrimitiveType Primitive;
  rsuint8 LineId;
  ApiCcBasicServiceType BasicService;
  ApiAudioDataFormatType PcmDataFormat;
  rsuint8 CodecListLength;
  ApiCodecListType CodecList;
} LsSetupIndType;

typedef struct
{
  LsPrimitiveType Primitive;
  rsuint8 LineId;
  rsuint8 OtherLineId;
  ApiCcBasicServiceType BasicService;
  ApiAudioDataFormatType PcmDataFormat;
  rsuint8 CodecListLength;
  ApiCodecListType CodecList;
} LsIntSetupIndType;

typedef struct
{
  LsPrimitiveType Primitive;
  rsuint8 LineId;
  rsuint8 OtherLineId;
} LsPcmLoopbackIndType;

typedef struct
{
  LsPrimitiveType Primitive;
  RsStatusType Status;
  rsuint8 LineId;
} LsSetupResType;

typedef struct
{
  LsPrimitiveType Primitive;
  rsuint8 LineId;
  ApiCodecListType CodecList;
} LsConnectIndType;

typedef struct
{
  LsPrimitiveType Primitive;
  rsuint8 LineId;
  ApiCodecListType CodecList;
} LsAlertIndType;

typedef struct
{
  LsPrimitiveType Primitive;
  rsuint8 LineId;
} LsReleaseIndType;

typedef struct
{
  LsPrimitiveType Primitive;
  rsuint8 LineId;
} LsRejectIndType;

typedef struct
{
  LsPrimitiveType Primitive;
  rsuint8 LineId;
  ApiCodecListType CodecList;
} LsCodecIndType;

typedef struct
{
  LsPrimitiveType Primitive;
  rsuint8 LineId;
  RsStatusType Status;
} LsCodecCfmType;

typedef union
{
  LsPrimitiveType Primitive;
  LsSetupIndType SetupInd;
  LsIntSetupIndType IntSetupInd;
  LsPcmLoopbackIndType PcmLoopbackInd;
  LsSetupResType SetupRes;
  LsConnectIndType ConnectInd;
  LsAlertIndType AlertInd;
  LsReleaseIndType ReleaseInd;
  LsRejectIndType RejectInd;
  LsCodecIndType CodecInd;
  LsCodecCfmType CodecCfm;
} LineSimMsgType;

//Type for saving call infomation inorder to save in CallLog
typedef struct
{
  ApiLasCallTypeType  CallType;
  rsuint8 NameLength;
  rsuint8 *Name;
  rsuint8 NumberLength;
  rsuint8 *Number;
} LineCallInfoType;

typedef struct
{
  LineStateType State;
  int DialStringLength;
  rsuint8 ProposedCodecListLength;
  ApiCodecListType *ProposedCodecListPtr;
  ApiCcBasicServiceType ProposedBasicService;
  ApiCcBasicServiceType InitialBasicService;
  ApiCodecInfoType UsedCodec;
  rsbool LinePstn;
} LineCtrlType;

typedef struct
{
#ifdef NATALIE_V11
	  rsbool PcmEnable;
	  rsbool IsMaster;
	  rsbool DoClockSync;
	  ApiPcmFscFreqType PcmFscFreq;
	  ApiPcmFscLengthType PcmFscLength;
	  rsbool PcmFscStartAligned ;
	  ApiPcmClkType PcmClk;
	  rsbool PcmClkOnRising;
	  rsuint8 PcmClksPerBit;
	  rsbool PcmFscInvert;
	  rsuint8 PcmCh0Delay;
	  rsbool PcmDoutIsOpenDrain;
	  rsbool PcmIsOpenDrain;
#else
  ApiPcmEnableType      PcmEnabled;
  ApiPcmMasterSlaveType PcmMode;
  ApiPcmFscFreqType     PcmFsc;
  ApiPcmFscLengthType   PcmFscLength;
  ApiPcmFscStartType    PcmFscStart;
  ApiPcmClkType         PcmClk;
  ApiPcmClkModeType     PcmClkMode;
  ApiPcmOdType          PcmDoOd;
  ApiPcmOdType          PcmOd;
#endif
  rsuint8               PcmChannelCodec[TOTAL_LINE_NUM];
} LinePcmSettingType;
/****************************************************************************
*                            Global variables/const
****************************************************************************/
extern LineCtrlType LineCtrl[TOTAL_LINE_NUM];
extern LinePcmSettingType LinePcmSetting;

/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
extern void LineInitPcm(void);
extern void LineCtrlInit( void );
extern void LineSimSetLineState(rsuint8 LineId, LineStateType State);
extern void SetInitialBasicService(rsuint8 LineId, ApiCcBasicServiceType BasicService);

extern LineStateType LineSimGetLineState(rsuint8 LineId);
extern void LineSimLineStateChange(rsuint8 LineId, LineStateType LineState);

extern ApiCodecListType* LineSimGetCodecList(rsuint8 LineId, rsuint8 *CodecListLengthPtr, ApiCcBasicServiceType *BasicServicePtr);
extern void LineSimSetCodecList(rsuint8 LineId, rsuint8 CodecListLength, ApiCodecListType* CodecListPtr, ApiCcBasicServiceType BasicService);
extern RsStatusType LineSimSelectCodec(rsuint8 LineId, ApiCodecInfoType SelectedCodec);
extern ApiCodecInfoType LineSimGetSelectedCodec(rsuint8 LineId );
extern ApiAudioDataFormatType LineSimGetPcmDataFormat(rsuint8 LineId);

extern RsStatusType LineSimSetup(rsuint8 LineId, ApiCcBasicServiceType BasicService, rsuint8 CodecListLength, ApiCodecListType *CodecListPtr);
extern RsStatusType LineSimConnect(rsuint8 LineId, rsuint8 CodecListLength, ApiCodecListType * CodecListPtr);
extern RsStatusType LineSimRelease(rsuint8 LineId);
extern RsStatusType LineSimReject(rsuint8 LineId);

extern void SendLsSetupInd(rsuint8 LineId);
extern void SendPcmLoopbackInd(rsuint8 LineId, rsuint8 OtherLineId, ApiAudioDataFormatType PcmDestinationId);
extern void SendLsSetupRes(rsuint8 LineId, RsStatusType Status);
extern void SendLsConnectInd(rsuint8 LineId, ApiCodecListType *CodecListPtr);
extern void SendLsAlertInd(rsuint8 LineId, ApiCodecListType *CodecListPtr);
extern void SendLsReleaseInd(rsuint8 LineId);
extern void SendLsRejectInd(rsuint8 LineId);

extern void DoLsSetupInd(rsuint8 LineId, ApiCcBasicServiceType BasicService, ApiAudioDataFormatType PcmDataFormat, rsuint8 CodecListLength, ApiCodecListType *CodecListPtr);
extern void DoLsSetupRes(rsuint8 LineId, RsStatusType Status);
extern void DoLsConnectInd(rsuint8 LineId, ApiCodecListType *CodecListPtr);
extern void DoLsReleaseInd(rsuint8 LineId);
extern void DoLsRejectInd(rsuint8 LineId);

#endif //LINE_CTRL_H
// End of file.
