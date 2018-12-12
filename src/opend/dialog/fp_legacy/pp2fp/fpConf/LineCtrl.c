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
/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include "CfState.h"
#include "LineCtrl.h"
#include "CallCtrl.h"
#include "Util.h"

#ifdef PP_MMI_HOST_UTIL
 #include "HostUtil.h"
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define IS_HS_ATTACHED_TO_LINE(LineNo, HsNo) pCfSysCtrl->LasLineSettings[LineNo].AttachedHeadsets & 0x01<<(HsNo-1)

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/
LineCtrlType LineCtrl[TOTAL_LINE_NUM];
LinePcmSettingType LinePcmSetting;

/****************************************************************************
*                            Local variables/const
****************************************************************************/
//static ClLineSim *LineState[LS_NO_LINES];
//static IpcChannelType IpcCh;
//static bool IpcPingPending;
//static bool IpcConnected;

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/
static void* LsAllocateMailPacket(rsuint16 Length);
static void LsDeliverMail(void *MailPtr, rsuint16 Length);
static void LineMailHandler(rsuint8 *pMsg, rsuint16 Length);

/****************************************************************************
*                                Implementation
****************************************************************************/

/****************************************************************************
* FUNCTION:      LsAllocateMailPacket
* DESCRIPTION:
****************************************************************************/
static void* LsAllocateMailPacket(rsuint16 Length)
{
  return (void*)RcHeapAllocEx(Length, RHF_NULL_ON_FULL);
}

/****************************************************************************
* FUNCTION:      LineSimDeliverMail
* DESCRIPTION:
****************************************************************************/
static void LsDeliverMail(void *MailPtr, rsuint16 Length)
{
    LineMailHandler((rsuint8 *)MailPtr, Length);
    RcHeapFreeEx(MailPtr, RHF_NULL_ON_FULL);
}

/****************************************************************************
* FUNCTION:      LineCtrlInit
* DESCRIPTION:
****************************************************************************/
void LineCtrlInit( void )
{
  rsuint8 i;

  for(i=0;i<TOTAL_LINE_NUM;i++)
  {
    LineCtrl[i].State = LS_UNPLUGGED;
    LineCtrl[i].ProposedCodecListLength = 0;
    LineCtrl[i].UsedCodec.Codec = API_CT_NONE;
    LineCtrl[i].InitialBasicService = API_WIDEBAND_SPEECH;
    LineCtrl[i].LinePstn = FALSE;
  }

  LineInitPcm();
}

/****************************************************************************
* FUNCTION:      LineSimSetLineState
* DESCRIPTION:
****************************************************************************/
void LineSimSetLineState(rsuint8 LineId, LineStateType NewState)
{
  switch (NewState)
  {
    case LS_UNPLUGGED:
      LineCtrl[LineId].State = LS_UNPLUGGED;
      LineCtrl[LineId].DialStringLength = 0;
      if (LineCtrl[LineId].ProposedCodecListLength > 0)
      {
        RcHeapFreeEx(LineCtrl[LineId].ProposedCodecListPtr, RHF_NULL_ON_FULL);
        LineCtrl[LineId].ProposedCodecListLength = 0;
      }
      break;

    case LS_INCOMING_CALL:
      LineCtrl[LineId].State = LS_INCOMING_CALL;
      break;

    case LS_ON_HOOK:
      LineCtrl[LineId].State = LS_ON_HOOK;
      LineCtrl[LineId].DialStringLength = 0;
      LineCtrl[LineId].UsedCodec.Codec = API_CT_NONE;
      if (LineCtrl[LineId].ProposedCodecListLength > 0)
      {
        RcHeapFreeEx(LineCtrl[LineId].ProposedCodecListPtr, RHF_NULL_ON_FULL);
        LineCtrl[LineId].ProposedCodecListLength = 0;
      }
      break;

    case LS_OFF_HOOK:
      LineCtrl[LineId].State = LS_OFF_HOOK;
      break;

    case LS_CALL_INITIATED:
      LineCtrl[LineId].State = LS_CALL_INITIATED;
      break;

    case LS_CALL_PROC:
      LineCtrl[LineId].State = LS_CALL_PROC;
      break;

    case LS_CALL_DELIVERED:
      LineCtrl[LineId].State = LS_CALL_DELIVERED;
      break;
    default:
      break;
  }
  LineSimLineStateChange(LineId, LineCtrl[LineId].State);
}

/****************************************************************************
* FUNCTION:      LineSimLineStateChange
* DESCRIPTION:
****************************************************************************/
void LineSimLineStateChange(rsuint8 LineId, LineStateType LineState)
{
  ApiInfoElementType *IeBlockPtr = NULL;
  rsuint16 IeBlockLength = 0;
  ApiCallReferenceType HsId;
  rsuint8 i;
#ifdef NATALIE_V11
  ApiFpCcAudioIdType AudioId = {API_IEA_INT, 0, 0};
#endif
  switch (LineState)
  {
    case LS_UNPLUGGED:
    case LS_ON_HOOK:
      for (i=0; i<NO_HANDSETS; i++)
      {
#ifdef NATALIE_V11
    	  HsId.Value = i;
#else
        HsId.HandsetId = i;
#endif
        if (CallState[i].LineId == LineId && CallState[i].CallClass == API_CC_NORMAL)
        {
          switch (CallState[i].State)
          {
            case F00_NULL:
            case F19_RELEASE_PENDING:
              // Ignore
              break;
            case F01_CALL_INITIATED:
            case F02_OVERLAP_SENDING:
            case F03_CALL_PROCEEDING:
            case F04_CALL_DELIVERED:
            case F06_CALL_PRESENT:
            case F07_CALL_RECEIVED:
            case F10_ACTIVE:
            case CODEC_NEGOTIATION_FROM_HS:
            case CODEC_NEGOTIATION_FROM_LINE:
            case CODEC_NEGOTIATION_IN_SETUP:
              SendApiFpCcReleaseReq(COLA_TASK, HsId, API_RR_NORMAL, IeBlockLength,(rsuint8*)IeBlockPtr);
              CallState[i].CallClass = 0;
              StopDelayAudioOpenTimer(LineId);
              SendApiFpSetAudioFormatReq(COLA_TASK, LineId, AP_DATA_FORMAT_NONE);  // Mute
              break;
            default:
              break;
          }
        }
      }
      break;

    case LS_INCOMING_CALL:
      for (i=0; i<NO_HANDSETS; i++)
      {
#ifdef NATALIE_V11
    	HsId.Value = i;
#else
        HsId.HandsetId = i;
#endif
        switch (CallState[i].State)
        {
          case F00_NULL:
          {
            if (IS_HS_ATTACHED_TO_LINE(LineId, i))
            {
              rsuint8 *CodecListLengthPtr = (rsuint8 *)RcHeapAllocEx(sizeof(rsuint8), RHF_NULL_ON_FULL);
              ApiCodecListType *CodecPtr = NULL;
              ApiCcBasicServiceType *BasicServicePtr = (ApiCcBasicServiceType *)RcHeapAllocEx(sizeof(ApiCcBasicServiceType), RHF_NULL_ON_FULL);

              CodecPtr = LineSimGetCodecList(LineId, CodecListLengthPtr, BasicServicePtr);

              if (*BasicServicePtr == API_WIDEBAND_SPEECH)
              {
#ifndef NATALIE_V11//Obsolete since Natalie v11 ??
                SendApiFpGetCodecListReq(COLA_TASK,
                                         i,
                                         CommonCodecListFromLocation);
#endif
              }
              else
              {
                ApiLineIdType id;

                //if needed wake up protocol from No emission mode
                //NoEmissionWakeUp();

                id.ApiSubId = API_SUB_LINE_ID_EXT_LINE_ID;
                id.ApiLineValue.Value = LineId;
                //MBA when don't want clip in the setup  PutClipInIe(LineId, &IeBlockPtr, &IeBlockLength);
                ApiBuildInfoElement(&IeBlockPtr,
                                    &IeBlockLength,
                                    API_IE_LINE_ID,
                                    sizeof(ApiLineIdType),
                                    (rsuint8*)&id);
#ifdef NATALIE_V11
                SendApiFpCcSetupReq(COLA_TASK,
        							HsId,                             //CallReference
                                    i,
                                    AudioId, //SourceId
                                    API_BASIC_SPEECH,
                                    API_CC_NORMAL,
                                    API_CC_SIGNAL_ALERT_ON_PATTERN_0_INT, //Signal
                                    IeBlockLength,
                                    (rsuint8*)IeBlockPtr);
#else
                SendApiFpCcSetupReq(COLA_TASK,
                                    HsId,
                                    API_BASIC_SPEECH,
                                    API_CC_NORMAL,
                                    LineId,
                                    API_CC_SIGNAL_ALERT_ON_PATTERN_0_INT,
                                    IeBlockLength,
                                    (rsuint8*)IeBlockPtr);
#endif
              }
              CallState[i].CallClass = API_CC_NORMAL;
              CallState[i].LineId = LineId;
              RcHeapFreeEx(CodecListLengthPtr, RHF_NULL_ON_FULL);
              RcHeapFreeEx(BasicServicePtr, RHF_NULL_ON_FULL);
            }
            break;
          }
          case F01_CALL_INITIATED:
          case F02_OVERLAP_SENDING:
          case F03_CALL_PROCEEDING:
          case F04_CALL_DELIVERED:
          case F06_CALL_PRESENT:
          case F07_CALL_RECEIVED:
          case F10_ACTIVE:
          case F19_RELEASE_PENDING:
          case CODEC_NEGOTIATION_FROM_HS:
          case CODEC_NEGOTIATION_FROM_LINE:
          case CODEC_NEGOTIATION_IN_SETUP:
            // Ignore
            break;
          default:
            break;
        }
      }
      break;

    case LS_OFF_HOOK:
      for (i=0; i<NO_HANDSETS; i++)
      {
//        HsId.HandsetId = i;
        if (CallState[i].LineId == LineId && CallState[i].CallClass == API_CC_NORMAL)
        {
          switch (CallState[i].State)
          {
            case F01_CALL_INITIATED:
            case F02_OVERLAP_SENDING:
            case F03_CALL_PROCEEDING:
            case F04_CALL_DELIVERED:
              // Connect audio
              ConnectAudioToLine(i, LineId);
              CfSetCallState(i, F10_ACTIVE);
              break;
            case F00_NULL:
            case F06_CALL_PRESENT:
            case F07_CALL_RECEIVED:
            case F10_ACTIVE:
            case F19_RELEASE_PENDING:
            case CODEC_NEGOTIATION_FROM_HS:
            case CODEC_NEGOTIATION_FROM_LINE:
            case CODEC_NEGOTIATION_IN_SETUP:
              // Ignore
              break;
            default:
              break;
          }
        }
      }
      break;

    case LS_CALL_INITIATED:
      for (i=0; i<NO_HANDSETS; i++)
      {
#ifdef NATALIE_V11
    	  HsId = CallState[i].CallReference;
#else
        HsId.HandsetId = i;
#endif
        if (CallState[i].LineId == LineId && CallState[i].CallClass == API_CC_NORMAL)
        {
          switch (CallState[i].State)
          {
            case F01_CALL_INITIATED:
              CfSetCallState(i, F02_OVERLAP_SENDING);
              { //SSNEW_ADD_DATA_FORMAT_ELEMENT
               switch (LinePcmSetting.PcmChannelCodec[LineId])
               {
                case 0: // Linear
                case 1: // A-Law
                case 2: // u-Law
                 {
                   ApiAudioDataFormatListType *IeData;
                   rsuint8 IeLength = RSOFFSETOF(ApiAudioDataFormatListType,ApiAudioDataFormatInfo)+sizeof(ApiAudioDataFormatInfoType)*2;

                   IeData = (ApiAudioDataFormatListType*)RcHeapAllocEx(IeLength, RHF_NULL_ON_FULL);
                   IeData->NoOfCodecs = 2;
                   {
                     ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[0];
                     p->Codec = API_CT_G722;
                     p->ApiAudioDataFormat = AP_DATA_FORMAT_LINEAR_16kHz;
                   }
                   {
                     ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[1];
                     p->Codec = API_CT_G726;
                     p->ApiAudioDataFormat = AP_DATA_FORMAT_LINEAR_8kHz;
                   }
                   ApiBuildInfoElement(&IeBlockPtr,
                                    &IeBlockLength,
                                    API_IE_AUDIO_DATA_FORMAT,
                                    IeLength,
                                    (rsuint8 *)IeData);
                 }
                 break;

                case 3: // Transparent G726
                 {
                   ApiAudioDataFormatListType *IeData;
                   rsuint8 IeLength = RSOFFSETOF(ApiAudioDataFormatListType,ApiAudioDataFormatInfo)+sizeof(ApiAudioDataFormatInfoType);

                   IeData = (ApiAudioDataFormatListType*)RcHeapAllocEx(IeLength, RHF_NULL_ON_FULL);
                   IeData->NoOfCodecs = 1;
                   {
                     ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[0];
                     p->Codec = API_CT_G726;
                     p->ApiAudioDataFormat = AP_DATA_FORMAT_G726;
                   }
                   ApiBuildInfoElement(&IeBlockPtr,
                                    &IeBlockLength,
                                    API_IE_AUDIO_DATA_FORMAT,
                                    IeLength,
                                    (rsuint8 *)IeData);
                 }
                 break;

                case 4: // Transparent G722
                 {
                   ApiAudioDataFormatListType *IeData;
                   rsuint8 IeLength = RSOFFSETOF(ApiAudioDataFormatListType,ApiAudioDataFormatInfo)+sizeof(ApiAudioDataFormatInfoType)*2;

                   IeData = (ApiAudioDataFormatListType*)RcHeapAllocEx(IeLength, RHF_NULL_ON_FULL);
                   IeData->NoOfCodecs = 2;
                   {
                     ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[0];
                     p->Codec = API_CT_G722;
                     p->ApiAudioDataFormat = AP_DATA_FORMAT_G722;
                   }
                   {
                     ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[1];
                     p->Codec = API_CT_G726;
                     p->ApiAudioDataFormat = AP_DATA_FORMAT_G726;
                   }
                   ApiBuildInfoElement(&IeBlockPtr,
                                    &IeBlockLength,
                                    API_IE_AUDIO_DATA_FORMAT,
                                    IeLength,
                                    (rsuint8 *)IeData);
                 }
                 break;

                case 5: // Loopback
                 //no data format
                 break;
               }

              }
              SendApiFpCcSetupAckReq(COLA_TASK, HsId, API_CC_SIGNAL_DIAL_TONE_ON, API_IN_BAND_NOT_AVAILABLE, IeBlockLength, (rsuint8 *)IeBlockPtr);
              break;
            case F00_NULL:
            case F02_OVERLAP_SENDING:
            case F03_CALL_PROCEEDING:
            case F04_CALL_DELIVERED:
            case F06_CALL_PRESENT:
            case F07_CALL_RECEIVED:
            case F10_ACTIVE:
            case F19_RELEASE_PENDING:
            case CODEC_NEGOTIATION_FROM_HS:
            case CODEC_NEGOTIATION_FROM_LINE:
            case CODEC_NEGOTIATION_IN_SETUP:
              // Ignore
              break;
            default:
              break;
          }
        }
      }
      break;

    case LS_CALL_PROC:
      for (i=0; i<NO_HANDSETS; i++)
      {
#ifdef NATALIE_V11
    	  HsId = CallState[i].CallReference;
#else
        HsId.HandsetId = i;
#endif
        if (CallState[i].LineId == LineId && CallState[i].CallClass == API_CC_NORMAL)
        {
          switch (CallState[i].State)
          {
            case F01_CALL_INITIATED:
            case F02_OVERLAP_SENDING:
              {
                ApiInfoElementType *InfoElement = NULL;
                rsuint16 InfoElementLength = 0;
                CfSetCallState(i, F03_CALL_PROCEEDING);
                SendApiFpCcCallProcReq(COLA_TASK, HsId, API_IN_BAND_NOT_AVAILABLE, API_CC_SIGNAL_DIAL_TONE_ON, 0, NULL);
                ApiBuildInfoElement(&InfoElement, &InfoElementLength, API_IE_LINE_ID, sizeof(ApiLineIdType), (rsuint8*)&LineIdReq);
                ApiBuildInfoElement(&InfoElement, &InfoElementLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&CallState[i].ApiSystemCallId);
//                SendApiFpCcCallInfoReq(COLA_TASK, HsId, InfoElementLength, (rsuint8*)InfoElement);       //SSINFO
                SendApiFpCcInfoReq(COLA_TASK, HsId, API_PROGRESS_INVALID, API_CC_SIGNAL_CUSTOM_NONE, InfoElementLength, (rsuint8*)InfoElement);       //SSINFO


                ApiFreeInfoElement(&InfoElement);
              }
              break;
            case F00_NULL:
            case F03_CALL_PROCEEDING:
            case F04_CALL_DELIVERED:
            case F06_CALL_PRESENT:
            case F07_CALL_RECEIVED:
            case F10_ACTIVE:
            case F19_RELEASE_PENDING:
            case CODEC_NEGOTIATION_FROM_HS:
            case CODEC_NEGOTIATION_FROM_LINE:
            case CODEC_NEGOTIATION_IN_SETUP:
              // Ignore
              break;
            default:
              break;
          }
        }
      }
      break;

    case LS_CALL_DELIVERED:
      for (i=0; i<NO_HANDSETS; i++)
      {
#ifdef NATALIE_V11
    	  HsId = CallState[i].CallReference;
#else
        HsId.HandsetId = i;
#endif
        if (CallState[i].LineId == LineId && CallState[i].CallClass == API_CC_NORMAL)
        {
          switch (CallState[i].State)
          {
            case F01_CALL_INITIATED:
            case F02_OVERLAP_SENDING:
            case F03_CALL_PROCEEDING:
              CfSetCallState(i, F04_CALL_DELIVERED);
              SendApiFpCcAlertReq(COLA_TASK, HsId, API_IN_BAND_NOT_AVAILABLE, API_CC_SIGNAL_RINGBACK_TONE_ON, 0, NULL);
              break;
            case F00_NULL:
            case F04_CALL_DELIVERED:
            case F06_CALL_PRESENT:
            case F07_CALL_RECEIVED:
            case F10_ACTIVE:
            case F19_RELEASE_PENDING:
            case CODEC_NEGOTIATION_FROM_HS:
            case CODEC_NEGOTIATION_FROM_LINE:
            case CODEC_NEGOTIATION_IN_SETUP:
              // Ignore
              break;
            default:
              break;
          }
        }
      }
      break;
    default:
      break;
  }
}


/****************************************************************************
* FUNCTION:      LineSimGetLineState
* DESCRIPTION:
****************************************************************************/
LineStateType LineSimGetLineState(rsuint8 LineId)
{
  return LineCtrl[LineId].State;
}

/****************************************************************************
* FUNCTION:      LineSimGetCodecList
* DESCRIPTION:
****************************************************************************/
ApiCodecListType* LineSimGetCodecList(rsuint8 LineId, rsuint8 *CodecListLengthPtr, ApiCcBasicServiceType *BasicServicePtr)
{
  *CodecListLengthPtr = LineCtrl[LineId].ProposedCodecListLength;
  *BasicServicePtr = LineCtrl[LineId].ProposedBasicService;

  if (LineCtrl[LineId].ProposedCodecListLength)
  {
    return LineCtrl[LineId].ProposedCodecListPtr;
  }
  return NULL;
}

/****************************************************************************
* FUNCTION:      LineSimSetInitialBasicService
* DESCRIPTION:
****************************************************************************/
void LineSimSetInitialBasicService(rsuint8 LineId, ApiCcBasicServiceType BasicService)
{
  LineCtrl[LineId].InitialBasicService = BasicService;
}

/****************************************************************************
* FUNCTION:      LineSimSetCodecList
* DESCRIPTION:
****************************************************************************/
void LineSimSetCodecList(rsuint8 LineId, rsuint8 CodecListLength, ApiCodecListType* CodecListPtr, ApiCcBasicServiceType BasicService)
{
  LineCtrl[LineId].ProposedBasicService = BasicService;
  if (LineCtrl[LineId].ProposedCodecListLength > 0)
  {
    RcHeapFreeEx(LineCtrl[LineId].ProposedCodecListPtr, RHF_NULL_ON_FULL);;
    LineCtrl[LineId].ProposedCodecListLength = 0;
  }
  if (CodecListLength > 0)
  {
#ifdef NATALIE_V11
    if (LinePcmSetting.PcmFscFreq == AP_FSC_FREQ_8KHZ && // 8KHz Frame sync
#else
    if (LinePcmSetting.PcmFsc == AP_FSC_FREQ_8KHZ && // 8KHz Frame sync
#endif
        LinePcmSetting.PcmChannelCodec[LineId] == 0)                   // Linear PCM
    {
      // Only G726 is supported
      ApiCodecListType codecList = {API_NI_POSSIBLE, 1, {{API_CT_G726, API_MDS_1_MD, API_CPR_CS, API_SS_FS}}};
      LineCtrl[LineId].ProposedCodecListLength = sizeof(ApiCodecListType);

      LineCtrl[LineId].ProposedCodecListPtr = (ApiCodecListType*)RcHeapAllocEx(LineCtrl[LineId].ProposedCodecListLength, RHF_NULL_ON_FULL);
      util_memcpy(LineCtrl[LineId].ProposedCodecListPtr, &codecList, LineCtrl[LineId].ProposedCodecListLength);
      LineCtrl[LineId].ProposedBasicService = API_BASIC_SPEECH;
    }
    else
    {
      LineCtrl[LineId].ProposedCodecListLength = CodecListLength;
      LineCtrl[LineId].ProposedCodecListPtr = (ApiCodecListType*)RcHeapAllocEx(CodecListLength, RHF_NULL_ON_FULL);
      util_memcpy(LineCtrl[LineId].ProposedCodecListPtr, CodecListPtr, CodecListLength);
    }
  }
}

/****************************************************************************
* FUNCTION:      LineSimSelectCodec
* DESCRIPTION:
****************************************************************************/
RsStatusType LineSimSelectCodec(rsuint8 LineId, ApiCodecInfoType SelectedCodec)
{
  RsStatusType Status = RSS_SUCCESS;
  LineCtrl[LineId].UsedCodec = SelectedCodec;
  return Status;
}

/****************************************************************************
* FUNCTION:      GetSelectedCodec
* DESCRIPTION:
****************************************************************************/
ApiCodecInfoType LineSimGetSelectedCodec(rsuint8 LineId)
{
  if (LineCtrl[LineId].UsedCodec.Codec == API_CT_NONE && LineCtrl[LineId].ProposedCodecListLength > 0)
  {
    LineSimSelectCodec(LineId, LineCtrl[LineId].ProposedCodecListPtr->Codec[0]);
  }
  return LineCtrl[LineId].UsedCodec;
}

/****************************************************************************
* FUNCTION:      LineInitPcm
* DESCRIPTION:
****************************************************************************/
void LineInitPcm(void)
{
#ifdef NATALIE_V11
	  rsuint8 PcmEnable = 0x1, IsMaster = 0x1, DoClockSync = 0x0, PcmFscFreq = 0x1, PcmFscLength = 0x0, PcmFscStartAligned = 0x0;
  rsuint8 PcmClk = 0x0, PcmClkOnRising = 0x0, PcmClksPerBit = 0x1, PcmFscInvert = 0x0, PcmCh0Delay = 0x0, PcmDoutIsOpenDrain = 0x0, PcmIsOpenDrain = 0x0;
  //hard-coded
  LinePcmSetting.PcmEnable = 1;//APE_ENABLED;
  LinePcmSetting.IsMaster = 1;//APM_MASTER;
  LinePcmSetting.DoClockSync = 0;
  LinePcmSetting.PcmFscFreq = AP_FSC_FREQ_16KHZ;
  LinePcmSetting.PcmFscLength = AP_FSC_LENGTH_1;
  LinePcmSetting.PcmFscStartAligned = 1;//APF_START_1_BIT_BEFORE;
  LinePcmSetting.PcmClk = AP_PCM_CLK_1152;
  LinePcmSetting.PcmClkOnRising = 0;
  LinePcmSetting.PcmClksPerBit = 1;
  LinePcmSetting.PcmFscInvert = 0;
  LinePcmSetting.PcmCh0Delay = 0;
  LinePcmSetting.PcmDoutIsOpenDrain = 0;
  LinePcmSetting.PcmIsOpenDrain = 0;


	SendApiFpInitPcmReq( COLA_TASK, PcmEnable, IsMaster,DoClockSync, PcmFscFreq, PcmFscLength, PcmFscStartAligned ,PcmClk, PcmClkOnRising,
	                     PcmClksPerBit,  PcmFscInvert, PcmCh0Delay, PcmDoutIsOpenDrain, PcmIsOpenDrain);
#else
  //hard-coded
  LinePcmSetting.PcmEnabled = APE_ENABLED;
  LinePcmSetting.PcmMode = APM_MASTER;
  LinePcmSetting.PcmFsc = AP_FSC_FREQ_16KHZ;
  LinePcmSetting.PcmFscLength = AP_FSC_LENGTH_1;
  LinePcmSetting.PcmFscStart = APF_START_1_BIT_BEFORE;
  LinePcmSetting.PcmClk = AP_PCM_CLK_1152;
  LinePcmSetting.PcmClkMode = AP_CLK_MODE_RISING;
  LinePcmSetting.PcmDoOd = APO_DISABLED;
  LinePcmSetting.PcmOd = APO_DISABLED;

  SendApiFpInitPcmReq(COLA_TASK,
                      LinePcmSetting.PcmEnabled,
                      LinePcmSetting.PcmMode,
                      LinePcmSetting.PcmFsc,
                      LinePcmSetting.PcmFscLength,
                      LinePcmSetting.PcmFscStart,
                      LinePcmSetting.PcmClk,
                      LinePcmSetting.PcmClkMode,
                      LinePcmSetting.PcmDoOd,
                      LinePcmSetting.PcmOd);
#endif
}

/****************************************************************************
* FUNCTION:      GetPcmDataFormat
* DESCRIPTION:
****************************************************************************/
ApiAudioDataFormatType LineSimGetPcmDataFormat(rsuint8 LineId)
{
  ApiAudioDataFormatType format = AP_DATA_FORMAT_NONE;

  LineSimGetSelectedCodec(LineId);

  switch (LineCtrl[LineId].UsedCodec.Codec)
  {
    case API_CT_NONE:
    case API_CT_G726:
      switch (LinePcmSetting.PcmChannelCodec[LineId])
      {
        case 0: // Linear
          format = AP_DATA_FORMAT_LINEAR_8kHz;
          break;
        case 1: // A-Law
          format = AP_DATA_FORMAT_G711A;
          break;
        case 2: // u-Law
          format = AP_DATA_FORMAT_G711U;
          break;

        case 3: // Transparent G726
          format = AP_DATA_FORMAT_G726;
          break;

        case 4: // Transparent G722
          format = AP_DATA_FORMAT_G722;
          break;

        case 5: // Loopback
          format = AP_DATA_FORMAT_INVALID;
          break;
      }
      break;
    case API_CT_G722:
      switch (LinePcmSetting.PcmChannelCodec[LineId])
      {
        case 0: // Linear
#ifdef NATALIE_V11
          if (LinePcmSetting.PcmFscFreq)
#else
          if (LinePcmSetting.PcmFsc)
#endif
          {
            format = AP_DATA_FORMAT_LINEAR_16kHz;
          }
          else
          {
            //not supported
            //ShowMessage("G.722 is not supported with 8KHz linear PCM!");
          }
          break;
        case 1: // A-Law
          format = AP_DATA_FORMAT_CWB_ALAW;  //Ricco
          break;
        case 2: // u-Law
          format = AP_DATA_FORMAT_CWB_ULAW;  //Ricco
          break;
        case 3: // Transparent G726
          format = AP_DATA_FORMAT_G726;
          break;

        case 4: // Transparent G722
          format = AP_DATA_FORMAT_G722;
          break;

        case 5: // Loopback
          format = AP_DATA_FORMAT_INVALID;
          break;
      }
      break;
    default:
      //ShowMessage("Unsupported AIR Codec used!");
      break;
  }
  return format;
}

/****************************************************************************
* FUNCTION:      LineSimSetup
* DESCRIPTION:
****************************************************************************/
RsStatusType LineSimSetup(rsuint8 LineId, ApiCcBasicServiceType BasicService, rsuint8 CodecListLength, ApiCodecListType *CodecListPtr)
{
  RsStatusType status = RSS_SUCCESS;
  switch (LineCtrl[LineId].State)
  {
    case LS_ON_HOOK:
      if(CodecListPtr)
      {
        if(CodecListPtr->NoOfCodecs > 1) // if codec already selected, don't reply with codec selection
        {
          LineSimSetCodecList(LineId, CodecListLength, CodecListPtr, BasicService);
        }
        else if(CodecListPtr->NoOfCodecs == 1) // if codec already selected, don't reply with codec selection
        {
          switch(BasicService)
          {
            case API_WIDEBAND_SPEECH: //SSDEBX
              {
                // Pack G722 and  G726
                const ApiCodecInfoType CodecG722 = {API_CT_G722, API_MDS_1_MD, API_CPR_CS, API_SS_LS640};
                const ApiCodecInfoType CodecG726 = {API_CT_G726, API_MDS_1_MD, API_CPR_CS, API_SS_FS};

                LineCtrl[LineId].ProposedCodecListLength = sizeof(ApiCodecListType)+sizeof(ApiCodecInfoType);
                LineCtrl[LineId].ProposedCodecListPtr = (ApiCodecListType*)RcHeapAllocEx(LineCtrl[LineId].ProposedCodecListLength, RHF_NULL_ON_FULL);
                LineCtrl[LineId].ProposedCodecListPtr->NegotiationIndicator = API_NI_POSSIBLE;
                LineCtrl[LineId].ProposedCodecListPtr->NoOfCodecs = 2;
                util_memcpy((rsuint8*)&LineCtrl[LineId].ProposedCodecListPtr->Codec[0], (rsuint8*)&CodecG722, 4);
                util_memcpy((rsuint8*)&LineCtrl[LineId].ProposedCodecListPtr->Codec[1], (rsuint8*)&CodecG726, 4);
                LineCtrl[LineId].ProposedBasicService = API_WIDEBAND_SPEECH;
              }
              break;

            case API_BASIC_SPEECH:
              {
                // Pack G726
                const ApiCodecInfoType CodecG726 = {API_CT_G726, API_MDS_1_MD, API_CPR_CS, API_SS_FS};

                LineCtrl[LineId].ProposedCodecListLength = sizeof(ApiCodecListType *);
                LineCtrl[LineId].ProposedCodecListPtr = (ApiCodecListType*)RcHeapAllocEx(LineCtrl[LineId].ProposedCodecListLength, RHF_NULL_ON_FULL);
                LineCtrl[LineId].ProposedCodecListPtr->NegotiationIndicator = API_NI_POSSIBLE;
                LineCtrl[LineId].ProposedCodecListPtr->NoOfCodecs = 1;
                util_memcpy((rsuint8*)&LineCtrl[LineId].ProposedCodecListPtr->Codec[0], (rsuint8*)&CodecG726, 4);
                LineCtrl[LineId].ProposedBasicService = API_BASIC_SPEECH;
              }
              break;
          }
        }
      }
      else
      { // if no codec exist reply with codec selection
        LineSimSetCodecList(LineId, CodecListLength, CodecListPtr, BasicService);
      }
      if ( LineCtrl[LineId].LinePstn == TRUE)
      {
        // We simulate a PSTN line -> Go directly to off hook state
        SendLsSetupInd(LineId);
        LineSimSetLineState(LineId, LS_OFF_HOOK);
      }
      else if (LineCtrl[LineId].DialStringLength > 0)
      {
        // The user has entered a number
        SendLsSetupInd(LineId);
        LineSimSetLineState(LineId, LS_CALL_PROC);
      }
      else
      {
        //we need a phone number to call to
        //LineSimSetLineState(LineId, LS_CALL_INITIATED);
        //KTS: offhook directly
        LineSimSetLineState(LineId, LS_OFF_HOOK);
      }
      break;

    case LS_INCOMING_CALL:
      LineSimSetLineState(LineId, LS_OFF_HOOK);
      break;

    case LS_OFF_HOOK:
      if(CodecListPtr)
      {
        //If more than one Codec available, select the codec used currently
        if(CodecListPtr->NoOfCodecs > 1) // if codec already selected, don't reply with codec selection
        {
          //select the codec used currently
        }
        else if(CodecListPtr->NoOfCodecs == 1) // if codec already selected, don't reply with codec selection
        {
          if( BasicService == API_BASIC_SPEECH && LineCtrl[LineId].UsedCodec.Codec == API_CT_G722 )
          {
            status = RSS_REJECTED;
            break;
          }
        }
      }
      LineSimSetLineState(LineId, LS_OFF_HOOK);
      break;

    default:
      status = RSS_REJECTED;
  }
  return status;
}

/****************************************************************************
* FUNCTION:      Release
* DESCRIPTION:
****************************************************************************/
RsStatusType LineSimRelease(rsuint8 LineId)
{
  RsStatusType status = RSS_SUCCESS;
  switch (LineCtrl[LineId].State)
  {
    case LS_INCOMING_CALL:
    case LS_OFF_HOOK:
    case LS_CALL_INITIATED:
    case LS_CALL_PROC:
    case LS_CALL_DELIVERED:
      SendLsReleaseInd(LineId);
      LineSimSetLineState(LineId, LS_ON_HOOK);
      break;

    default:
      status = RSS_REJECTED;
  }
  return status;
}

/****************************************************************************
* FUNCTION:      Reject
* DESCRIPTION:
****************************************************************************/
RsStatusType LineSimReject(rsuint8 LineId)
{
  SendLsRejectInd(LineId);
  LineSimSetLineState(LineId, LS_ON_HOOK);
  return RSS_SUCCESS;
}

/****************************************************************************
* FUNCTION:      Reject
* DESCRIPTION:
****************************************************************************/
RsStatusType LineSimConnect(rsuint8 LineId, rsuint8 CodecListLength, ApiCodecListType * CodecListPtr)
{
  RsStatusType status = RSS_SUCCESS;
  switch (LineCtrl[LineId].State)
  {
    case LS_ON_HOOK:
    case LS_INCOMING_CALL:
    case LS_CALL_INITIATED:
    case LS_CALL_PROC:
    case LS_CALL_DELIVERED:
      if (CodecListLength > 0)
      {
        LineSimSelectCodec(LineId, CodecListPtr->Codec[0]);
      }
      LineSimSetLineState(LineId, LS_OFF_HOOK);
      break;

    default:
      status = RSS_REJECTED;
  }
  return status;
}

/****************************************************************************
* FUNCTION:      Intercom Setup
* DESCRIPTION:
****************************************************************************/
RsStatusType LineSimIntSetup(rsuint8 LineId, rsuint8 OtherLineId, ApiCcBasicServiceType BasicService, rsuint8 CodecListLength, ApiCodecListType *CodecListPtr)
{
  if (LineId < LS_NO_LINES)
  {
    RsStatusType status = RSS_SUCCESS;
    switch (LineCtrl[LineId].State)
    {
      case LS_ON_HOOK:
        LineSimSetCodecList(LineId, CodecListLength, CodecListPtr, BasicService);
        LineSimSetLineState(LineId, LS_OFF_HOOK);
        break;

      case LS_INCOMING_CALL:
        LineSimSetLineState(LineId, LS_OFF_HOOK);
        break;

      default:
        status = RSS_REJECTED;
    }
    return status;
  }
  return RSS_BAD_HANDLE;
}


/****************************************************************************
* FUNCTION:      SendLsSetupInd
* DESCRIPTION:
****************************************************************************/
void SendLsSetupInd(rsuint8 LineId)
{
  {
    rsuint16 l = RSOFFSETOF(LsSetupIndType, CodecList) + LineCtrl[LineId].ProposedCodecListLength;
    LsSetupIndType* m = (LsSetupIndType*)LsAllocateMailPacket(l);
    m->Primitive = LS_SETUP_IND;
    m->LineId = LineId;
    m->BasicService = LineCtrl[LineId].ProposedBasicService;
    m->PcmDataFormat = LinePcmSetting.PcmChannelCodec[LineId];
    m->CodecListLength = LineCtrl[LineId].ProposedCodecListLength;
    if (LineCtrl[LineId].ProposedCodecListLength)
    {
      util_memcpy(&m->CodecList, LineCtrl[LineId].ProposedCodecListPtr, LineCtrl[LineId].ProposedCodecListLength);
    }
    RosMailDeliver((RosMailType *)m);
    LsDeliverMail((rsuint8 *)m, l);
  }
}

/****************************************************************************
* FUNCTION:      SendLsSetupRes
* DESCRIPTION:
****************************************************************************/
void SendLsSetupRes(rsuint8 LineId, RsStatusType Status)
{
  {
    LsSetupResType* m = (LsSetupResType*)LsAllocateMailPacket(sizeof(LsSetupResType));
    m->Primitive = LS_SETUP_RES;
    m->Status = Status;
    m->LineId = LineId;
    LsDeliverMail((rsuint8 *)m, sizeof(LsSetupResType));
  }
}

/****************************************************************************
* FUNCTION:      SendLsReleaseInd
* DESCRIPTION:
****************************************************************************/
void SendLsReleaseInd(rsuint8 LineId)
{
  {
    LsReleaseIndType* m = (LsReleaseIndType*)LsAllocateMailPacket(sizeof(LsReleaseIndType));
    m->Primitive = LS_RELEASE_IND;
    m->LineId = LineId;
    LsDeliverMail((rsuint8 *)m, sizeof(LsReleaseIndType));
  }
}

/****************************************************************************
* FUNCTION:      SendLsRejectInd
* DESCRIPTION:
****************************************************************************/
void SendLsRejectInd(rsuint8 LineId)
{
  {
    LsRejectIndType* m = (LsRejectIndType*)LsAllocateMailPacket(sizeof(LsRejectIndType));
    m->Primitive = LS_REJECT_IND;
    m->LineId = LineId;
    LsDeliverMail((rsuint8 *)m, sizeof(LsRejectIndType));
  }
}

/****************************************************************************
* FUNCTION:      DoLsSetupInd
* DESCRIPTION:
****************************************************************************/
void DoLsSetupInd(rsuint8 LineId, ApiCcBasicServiceType BasicService, ApiAudioDataFormatType PcmDataFormat, rsuint8 CodecListLength, ApiCodecListType *CodecListPtr)
{
  switch(LineCtrl[LineId].State)
  {
    case LS_ON_HOOK:
      LineCtrl[LineId].ProposedBasicService = BasicService;
      //Check that incoming call supports GAP
      if (BasicService == API_WIDEBAND_SPEECH && ApiGetCodecListElement(CodecListPtr, API_CT_G726) == NULL)
      {
        SendLsSetupRes(LineId, RSS_REJECTED);
        break;
      }
      if (LinePcmSetting.PcmChannelCodec[LineId] < 5 && PcmDataFormat < 5) // Check for loopback mode
      {
        LinePcmSetting.PcmChannelCodec[LineId] = PcmDataFormat;
      }
      if (LineCtrl[LineId].ProposedCodecListLength)
      {
        RcHeapFreeEx(LineCtrl[LineId].ProposedCodecListPtr, RHF_NULL_ON_FULL);
      }
      LineCtrl[LineId].ProposedCodecListLength = CodecListLength;
      if (LineCtrl[LineId].ProposedCodecListLength)
      {
        LineCtrl[LineId].ProposedCodecListPtr = (ApiCodecListType*)RcHeapAllocEx(LineCtrl[LineId].ProposedCodecListLength, RHF_NULL_ON_FULL);
        util_memcpy(LineCtrl[LineId].ProposedCodecListPtr, CodecListPtr, LineCtrl[LineId].ProposedCodecListLength);
      }
      //THK: Maybe this should not be done
      if (CodecListPtr->NoOfCodecs == 1)
      {
        LineSimSelectCodec(LineId, CodecListPtr->Codec[0]);
      }

      LineSimSetLineState(LineId, LS_INCOMING_CALL);
      SendLsSetupRes(LineId, RSS_SUCCESS);
      break;

    default:
      SendLsSetupRes(LineId, RSS_REJECTED);

  }
}

/****************************************************************************
* FUNCTION:      DoLsSetupRes
* DESCRIPTION:
****************************************************************************/
void DoLsSetupRes(rsuint8 LineId, RsStatusType Status)
{
  switch(LineCtrl[LineId].State)
  {
    case LS_CALL_INITIATED:
      LineSimSetLineState(LineId, LS_CALL_PROC);
      break;
    default:
      break;
  }
}

/****************************************************************************
* FUNCTION:      DoLsConnectInd
* DESCRIPTION:
****************************************************************************/
void DoLsConnectInd(rsuint8 LineId, ApiCodecListType *CodecListPtr)
{
  switch(LineCtrl[LineId].State)
  {
    case LS_CALL_INITIATED:
    case LS_CALL_PROC:
    case LS_CALL_DELIVERED:
      LineSimSelectCodec(LineId, CodecListPtr->Codec[0]);
      LineSimSetLineState(LineId, LS_OFF_HOOK);
      break;
    case LS_OFF_HOOK:
      if (LineCtrl[LineId].UsedCodec.Codec != API_CT_NONE && CodecListPtr->Codec[0].Codec != LineCtrl[LineId].UsedCodec.Codec)
      {
        LineSimSelectCodec(LineId, CodecListPtr->Codec[0]);
        //KTS: not support
        //HostSimLineCodecChanged(LineId, CodecListPtr, LS_CONNECT_IND);
      }
    default:
      break;
  }
}

/****************************************************************************
* FUNCTION:      DoLsReleaseInd
* DESCRIPTION:
****************************************************************************/
void DoLsReleaseInd(rsuint8 LineId)
{
  LineSimSetLineState(LineId, LS_ON_HOOK);
}

/****************************************************************************
* FUNCTION:      DoLsRejectInd
* DESCRIPTION:
****************************************************************************/
void DoLsRejectInd(rsuint8 LineId)
{
  LineSimSetLineState(LineId, LS_ON_HOOK);
}

/****************************************************************************
* FUNCTION:      LineMailHandler
* DESCRIPTION:
****************************************************************************/
static void LineMailHandler(rsuint8 *pMsg, rsuint16 Length)
{
  LineSimMsgType *pM = (LineSimMsgType*)pMsg;
  rsuint8 lineId;
  rsuint8 i;

  // Handle
  switch(pM->Primitive)
  {
    case LS_SETUP_IND:
      lineId = pM->SetupInd.LineId;
      if (lineId < LS_NO_LINES)
      { // check for intercom already pending and don't setup if release if so !!!
        if(LineSimGetLineState(lineId) == LS_ON_HOOK)
        {
          DoLsSetupInd(lineId, pM->SetupInd.BasicService,
                               pM->SetupInd.PcmDataFormat,
                               pM->SetupInd.CodecListLength,
                               &pM->SetupInd.CodecList);
        }
      }
      break;

    case LS_SETUP_RES:
      lineId = pM->SetupRes.LineId;
      if (lineId < LS_NO_LINES)
      {
        DoLsSetupRes(lineId, pM->SetupRes.Status);
      }
      break;

    case LS_CONNECT_IND:
      lineId = pM->ConnectInd.LineId;
      if (lineId < LS_NO_LINES)
      {
        DoLsConnectInd(lineId, &pM->ConnectInd.CodecList);
      }
      break;

    case LS_RELEASE_IND:
      lineId = pM->ReleaseInd.LineId;
      if (lineId < LS_NO_LINES)
      {
        for (i=0; i<NO_HANDSETS; i++)
        { // check for intercom call and don't release if so !!!
          if( (CallState[i].LineId == lineId) &&
              (CallState[i].CallClass == API_CC_INTERNAL) )
          {
            switch(CallState[i].State)
            {
              case F01_CALL_INITIATED:
              case F02_OVERLAP_SENDING:
              case F03_CALL_PROCEEDING:
              case F04_CALL_DELIVERED:
              case F06_CALL_PRESENT:
              case F07_CALL_RECEIVED:
              case F10_ACTIVE:
              case F19_RELEASE_PENDING:
                // ignore release
                return;
              default:
                break;
            }
          }
        }
        DoLsReleaseInd(lineId);
      }
      break;

    case LS_REJECT_IND:
      lineId = pM->RejectInd.LineId;
      if (lineId < LS_NO_LINES)
      {
        DoLsRejectInd(lineId);
      }
      break;
    default:
      break;
  }
}

// End of file.
