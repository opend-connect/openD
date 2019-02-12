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
#include "system.h"
#include "LineCtrl.h"
#include "CallCtrl.h"
#include "CfState.h"
#include "Util.h"
#include "ApiHelper.h"

#ifdef PP_MMI_HOST_UTIL
 #include "HostUtil.h"
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define DELAY_AUDIO_OPEN_TIMEOUT 100
/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/

/****************************************************************************
*                            Local variables/const
****************************************************************************/
const ApiCodecInfoType CodecG722 = {API_CT_G722, API_MDS_1_MD, API_CPR_CS, API_SS_LS640};
const ApiCodecInfoType CodecG726 = {API_CT_G726, API_MDS_1_MD, API_CPR_CS, API_SS_FS};



/****************************************************************************
*                          Local Function prototypes
****************************************************************************/


/****************************************************************************
*                                Implementation
****************************************************************************/

void ApiFpCcSetupReq( ApiCallReferenceType CallReference, ApiTerminalIdType terminalId ) {

  ApiInfoElementType *IeBlockPtr = NULL;
  ApiFpCcAudioIdType AudioId= {API_IEA_INT, 0, 0};
  ApiLineIdType TempLineId;
  rsuint16 IeBlockLength = 0;

  CallState[ terminalId ].CallClass = API_CC_NORMAL; //normal external call
  CallState[ terminalId ].BasicService = API_WIDEBAND_SPEECH;
  CallState[ terminalId ].DestinationId = terminalId;
  CallState[ terminalId ].CallReference = CallReference;

  AudioId.IntExtAudio = API_IEA_INT;
  AudioId.SourceTerminalId = terminalId;

  ApiCallStatusType tempCallStatus;
  tempCallStatus.CallStatusSubId = API_SUB_CALL_STATUS;
  tempCallStatus.CallStatusValue.State = API_CSS_CALL_SETUP;
  ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusType), (rsuint8*)&tempCallStatus);

  ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&CallState[terminalId].ApiSystemCallId);

  //If we are making an outgoing call from ContactList check for LineId
  TempLineId.ApiSubId = API_SUB_LINE_ID_EXT_LINE_ID;
  TempLineId.ApiLineValue.Value = API_LINEID_NONE;  // line id none
  ApiBuildInfoElement(&IeBlockPtr,
                      &IeBlockLength,
                      API_IE_LINE_ID,
                      sizeof(ApiLineIdType),
                      (rsuint8*)&TempLineId);

  CfSetCallState( terminalId, F06_CALL_PRESENT);

  SendApiFpCcSetupReq(COLA_TASK,
                      CallReference,                                    //CallReference
                      CallState[ terminalId ].DestinationId ,           //ApiTerminalIdType
                      AudioId,                                          //SourceId
                      CallState[ terminalId ].BasicService,             //BasicService
                      CallState[ terminalId ].CallClass,                //CallClass
                      API_CC_SIGNAL_ALERT_ON_PATTERN_0_INT,             //Signal
                      IeBlockLength,
                      (rsuint8 *)IeBlockPtr);

  //Remember to free the Info element block from heap;
  ApiFreeInfoElement(&IeBlockPtr);

  return;
}

/******************************************************************************
* Name   : CfStopStateTimer
* Input  :
*-----------------------------------------------------------------------------
* Usage  : Starts the STATE time-out timer for the specified
*          line-device.
******************************************************************************/
void
StartDelayAudioOpenTimer(rsuint8 LineId)
{
  RosTimerStart(L1_DELAY_AUDIO_OPEN_TIMER+LineId, DELAY_AUDIO_OPEN_TIMEOUT, &ColaTimerCfgTable[ColaTimerCfgTableIdx(L1_DELAY_AUDIO_OPEN_TIMER+LineId)]);
}


/******************************************************************************
* Name   : StopDelayAudioOpenTimer
* Input  : <LineId> PSTN line device id - NOT A OS TIMER ID
*-----------------------------------------------------------------------------
* Usage  : Stops the STATE time-out timer for the specified
*          line-device.
******************************************************************************/
void
StopDelayAudioOpenTimer(rsuint8 LineId)
{
  RosTimerStop(L1_DELAY_AUDIO_OPEN_TIMER+LineId);
}

/****************************************************************************
* FUNCTION:      CfSetCallState
* DESCRIPTION:
****************************************************************************/
void CfSetCallState(rsuint8 HandsetId, CallStateType State)
{
  CallState[HandsetId].State = State;
  if (State == F00_NULL)
  {
    CallState[HandsetId].Connected2Line = FALSE;
    CallState[HandsetId].Present = FALSE;
    CallState[HandsetId].CallClass = 0;
    CallState[HandsetId].DestinationId = 0;
    CallState[HandsetId].LineId = 0xFF;
    CallState[HandsetId].BasicService = API_BASIC_SPEECH;
    CallState[HandsetId].ApiSystemCallId.ApiSubId = API_SUB_CALL_ID_INVALID;
    CallState[HandsetId].ApiSystemCallId.ApiSystemCallId = 0;
    CallState[HandsetId].ApiLineId.ApiSubId = API_SUB_LINE_ID_INVALID;
    CallState[HandsetId].ApiLineId.ApiLineValue.Value = 0x7F;
    if(CallState[HandsetId].ProposedCodecListPtr!=NULL)
    {
    RcHeapFreeEx(CallState[HandsetId].ProposedCodecListPtr, RHF_NULL_ON_FULL);
      CallState[HandsetId].ProposedCodecListPtr=NULL;
    }
    CallState[HandsetId].ProposedCodecListLength = 0;
    FreeHostCallReference(CallState[HandsetId].CallReference);
    CallState[HandsetId].CallReference.Value = 0;
  }
}

/****************************************************************************
* FUNCTION:      CfGetLineId
* DESCRIPTION:
****************************************************************************/
rsuint8 CfGetLineId(rsuint8 HandsetId )
{
  return (CallState[HandsetId].LineId);
}
/****************************************************************************
* FUNCTION:      CfGetLineUserNo
* DESCRIPTION:
****************************************************************************/
rsuint8 CfGetLineUserNo(rsuint8 LineId )
{
  rsuint8 i, HandsetNo=0;

  for( i=1; i<NO_HANDSETS; i++)
  {
    if(CallState[i].State==F10_ACTIVE && CallState[i].Connected2Line==TRUE && CallState[i].LineId==LineId)
    {
      HandsetNo++;
    }
  }
  return HandsetNo;
}

/****************************************************************************
* FUNCTION:      ApiFpIntSendCallingPartyNumber
* DESCRIPTION:
****************************************************************************/
void ApiFpIntSendCallingPartyNumber(ApiCallReferenceType HsId)                  //send out the calling party HS number
{
  ApiInfoElementType *IeBlockPtr = NULL;
  rsuint16 IeBlockLength = 0;
  ApiCallingNumberType ApiCallingNumber;

  ApiCallingNumber.NumberType = ANT_NETWORK_SPECIFIC;
  ApiCallingNumber.Npi = ANPI_PRIVATE;
  ApiCallingNumber.PresentationInd = API_PRESENTATION_ALLOWED;
  ApiCallingNumber.ScreeningInd = API_USER_PROVIDED_VERIFIED_PASSED;
  ApiCallingNumber.NumberLength = 1;
  ApiCallingNumber.Number[0]=IA5_DIGIT_0+CallState[GetHsFromCallReference(HsId)].DestinationId;
  ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_CALLING_PARTY_NUMBER, sizeof(ApiCallingNumberType), (rsuint8*)&(ApiCallingNumber));

  SendApiFpCcInfoReq(COLA_TASK, HsId, API_PROGRESS_INVALID, API_CC_SIGNAL_TONES_OFF, IeBlockLength, (rsuint8 *)IeBlockPtr);

  ApiFreeInfoElement((ApiInfoElementType **)&IeBlockPtr);
}


/****************************************************************************
* FUNCTION:      ApiFpCcSetupInd
* DESCRIPTION:
****************************************************************************/
void ApiFpCcSetupInd(ApiFpCcSetupIndType *MailPtr)
{
  rsuint8 lineId = 0xFF;
  rsuint8 destId = 0; //intercom destination number [0x01-0x06]

  rsuint8 codecListLength = 0;
  //info element pointers
  rsuint8 multikeypadLength = 0;
  Ia5CharType *pMultikeypad = NULL;
  ApiCodecListType *codecListPtr = NULL;
#ifdef NATALIE_V11
  ApiFpCcAudioIdType AudioId= {API_IEA_EXT, 0, 0};
  rsuint8 handsetId = MailPtr->TerminalId;
  ApiCallReferenceType HsId = MailPtr->CallReference;
  HsId.Instance.Host = AllocateHostCallReference();
  CallState[handsetId].CallReference=HsId;
#else
  rsuint8 handsetId = MailPtr->CallReference.HandsetId;
  ApiCallReferenceType HsId;
  HsId.HandsetId = handsetId;
#endif

  if (MailPtr->InfoElementLength > 0)
  {
    ApiInfoElementType *pIe = NULL;

    // API_IE_MULTIKEYPAD
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_MULTIKEYPAD);
    if (pIe != NULL)
    {
      multikeypadLength = pIe->IeLength;
      pMultikeypad = (Ia5CharType*)pIe->IeData;
    }

    // API_IE_CALLED_NUMBER
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_CALLED_NUMBER);
    if (pIe != NULL)
    {
    }

    // API_IE_CODEC_LIST
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_CODEC_LIST);
    if (pIe != NULL)
    {
      // API_IE_CODEC_LIST
      codecListPtr = (ApiCodecListType*)pIe->IeData;
      codecListLength = pIe->IeLength;
    }

    // API_IE_IWU_TO_IWU
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_IWU_TO_IWU);
    if (pIe != NULL)
    {
      //FIX ME: Unhandled API_IE_IWU_TO_IWU
    }

    // API_IE_PROPRIETARY
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_PROPRIETARY);
    if (pIe != NULL)
    {
      //FIX ME: Unhandled API_IE_PROPRIETARY
    }

    // API_IE_LINE_ID //////////
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_LINE_ID);
    if (pIe != NULL)
    {
      LineIdReq.ApiSubId = ((ApiLineIdType*)(pIe->IeData))->ApiSubId;
      LineIdReq.ApiLineValue.Value = ((ApiLineIdType*)(pIe->IeData))->ApiLineValue.Value;
    }
    else
    {
      LineIdReq.ApiLineValue.Value = 0x7F;
    }
    //update callstate array with the received info element(s)
    CallState[handsetId].ApiLineId = LineIdReq;

    //API_IE_SYSTEM_CALL_ID //////////
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_SYSTEM_CALL_ID);
    if (pIe != NULL)
    {
      //update callstate array with the received info element(s)
      CallState[handsetId].ApiSystemCallId.ApiSubId = ((ApiSystemCallIdType*)(pIe->IeData))->ApiSubId;
      CallState[handsetId].ApiSystemCallId.ApiSystemCallId  = ((ApiSystemCallIdType*)(pIe->IeData))->ApiSystemCallId;
    }
  }

  switch (CallState[handsetId].State)
  {
    case F00_NULL:
      switch(MailPtr->CallClass)
      {
        case API_CC_NORMAL: //////////////////////////////////////////////////////////////////////////////////////////////////////////
          { //// NORMAL EXTERNAL CALL ////////////////////////////////////////////////////////////////////////////////////////////////
            //KTS_TEMP:
            //tempararily for this project: always assign line#1
            //lineId = LsGetLine(handsetId, LineIdReq.ApiLineValue.Value-1); //minus one since we have chosen to used line id 1 to 4 in LAS
            lineId = 0;
#ifdef RHEA
//            AudioId.SourceTerminalId=MailPtr->TerminalId;
#endif
            if(CfGetLineUserNo(lineId)>=NO_ADPCM)   //reject the connection when all the ADPCM channels are occupied
            {
#ifdef NATALIE_V11
              SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_REJECTED, AudioId);
#else
              SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_REJECTED, 0);
#endif
              CallState[handsetId].Connected2Line = FALSE;
            }
            else
            {
              CallState[handsetId].LineId = lineId;

              if (lineId >= LS_NO_LINES)
              {
                // We did not get the line
#ifdef NATALIE_V11
              SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_REJECTED, AudioId);
#else
                SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_REJECTED, 0);
#endif
                CallState[handsetId].Connected2Line = FALSE;
              }
              else
              {
                RsStatusType status = RSS_SUCCESS;
                // We got a line
#ifdef NATALIE_V11
                AudioId.AudioEndPointId=lineId;
                SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_SUCCESS, AudioId);
#else
                SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_SUCCESS, lineId);
#endif
                CfSetCallState(handsetId, F01_CALL_INITIATED);
                CallState[handsetId].CallClass = API_CC_NORMAL;
                CallState[handsetId].Connected2Line = TRUE;
                CallState[handsetId].ProposedCodecListLength = codecListLength;

                if((LineCtrl[lineId].State==LS_OFF_HOOK)&&(MailPtr->BasicService!=LineCtrl[lineId].ProposedBasicService))
                {
                  status = RSS_REJECTED;         //KTS: reject connection when a Narrowband handset try to join a wideband conference and vice versa
                }
                else
                {
#ifdef RHEA
                	if(!codecListLength && MailPtr->BasicService == API_WIDEBAND_SPEECH){
                		ApiCodecListType p;
                		p.NegotiationIndicator=API_NI_POSSIBLE; /*!< Negotiation possible or not. */
                		p.NoOfCodecs=1;               	  /*!< Number of codecs. */
                		p.Codec[0]=CodecG722;            /*!< Codec data. */
                		codecListPtr=&p;
                		codecListLength=6;
                	}
#endif
                  status = LineSimSetup(lineId, MailPtr->BasicService, codecListLength, codecListPtr);
                }

                if (status != RSS_SUCCESS)
                {
                  SendApiFpCcReleaseReq(COLA_TASK, HsId, API_RR_USER_BUSY, 0, NULL);
                  CallState[handsetId].Connected2Line = FALSE;
                  CallState[handsetId].CallClass = 0;
                  CfSetCallState(handsetId, F00_NULL);
                }
              }
            }
          }
          break;

        case API_CC_INTERNAL: ////////////////////////////////////////////////////////////////////////////////////////////////////////
          {
            ApiInfoElementType *IeBlockPtr = NULL;
            rsuint16 IeBlockLength = 0;

            //KTS: for this intercom application audio will not route via PCM so noneed line
            CallState[handsetId].LineId = 0xFF;
#ifdef NATALIE_V11
                AudioId.IntExtAudio = API_IEA_INT;
                AudioId.SourceTerminalId=API_TERMINAL_ID_INVALID;
#endif
            {
              //We did not get the line
              CallState[handsetId].Connected2Line = FALSE;

              CfSetCallState(handsetId, F01_CALL_INITIATED);
              CallState[handsetId].CallClass = API_CC_INTERNAL;
              CallState[handsetId].BasicService = MailPtr->BasicService;

              CallState[handsetId].ProposedCodecListLength = 0;
              if(codecListLength)
              {
                CallState[handsetId].ProposedCodecListLength=codecListLength;
                CallState[handsetId].ProposedCodecListPtr = (ApiCodecListType*)RcHeapAllocEx(codecListLength, RHF_NULL_ON_FULL);
                memcpy(CallState[handsetId].ProposedCodecListPtr, codecListPtr, codecListLength);
              }

              //try to check whether the destination Hs Id is attached
              if(pMultikeypad != NULL)
              { //check if valid intercom dest PP
                if((multikeypadLength > 0) &&                                           //check if dst hs no present
                   (pMultikeypad[0]-'0' > 0) &&  (pMultikeypad[0]-'0' < NO_HANDSETS) && //check if dst hs is valid
                   (CallState[(pMultikeypad[0]-'0')].State == F00_NULL) &&              //check if dst hs is ready
                   (pMultikeypad[0]-'0' !=  handsetId)&&                                //check if src=dst
                   (CallState[pMultikeypad[0]-'0'].State != HS_NOT_REGISTERED))
                {

                  destId = (pMultikeypad[0]-'0');
#ifdef NATALIE_V11
                AudioId.SourceTerminalId=destId;
                SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_SUCCESS, AudioId);
#else
                  SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_SUCCESS, (destId|0x80));
#endif
                  CallState[handsetId].DestinationId = destId;

                  {
                    ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&CallState[handsetId].ApiSystemCallId);
                    SendApiFpCcCallProcReq(COLA_TASK, HsId, API_IN_BAND_NOT_AVAILABLE, API_CC_SIGNAL_DIAL_TONE_ON, IeBlockLength, (rsuint8 *)IeBlockPtr);
                    ApiFreeInfoElement((ApiInfoElementType **)&IeBlockPtr);
                  }
                }
                else
                { //called number selected unavailable!
#ifdef NATALIE_V11
                	SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_UNAVAILABLE, AudioId);
#else
                  SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_UNAVAILABLE, 0);
#endif
                  CfSetCallState(handsetId, F00_NULL);
                  return;
                }
              }
              else
              {
                //intercom audio routing via CVM and destination Hs Id not provided in Setup message is not implemented.

              }
            }
          }
          break;

        case API_CC_SERVICE: // service call not supported
#ifdef NATALIE_V11
        	SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_REJECTED, AudioId);
#else
          SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_REJECTED, 0);
#endif
          break;
      }
      break;

    case F01_CALL_INITIATED:
    case F02_OVERLAP_SENDING:
    case F03_CALL_PROCEEDING:
    case F04_CALL_DELIVERED:
    case F06_CALL_PRESENT:
    case F07_CALL_RECEIVED:

    case F19_RELEASE_PENDING:
    case CODEC_NEGOTIATION_FROM_HS:
    case CODEC_NEGOTIATION_FROM_LINE:
    case CODEC_NEGOTIATION_IN_SETUP:
    case HANDSET_LOCATE:
    case HEADSET_INTERCEPT:
#ifdef NATALIE_V11
        	SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_REJECTED, AudioId);
#else
      SendApiFpCcSetupRes(COLA_TASK, HsId, RSS_REJECTED, 0);
#endif
      break;
  }

}

/****************************************************************************
* FUNCTION:      ApiFpCcCallProcCfm
* DESCRIPTION:
****************************************************************************/
void ApiFpCcCallProcCfm(ApiFpCcCallProcCfmType *MailPtr)
{
#ifdef NATALIE_V11
  ApiFpCcAudioIdType AudioId= {API_IEA_INT, 0, 0};
  ApiCallReferenceType HsId = MailPtr->CallReference;
  rsuint8 handsetId = GetHsFromCallReference(HsId);
#else
  ApiCallReferenceType HsId;
  rsuint8 handsetId = MailPtr->CallReference.HandsetId;
  HsId.HandsetId = handsetId;
#endif
  switch (CallState[handsetId].State)
  {
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
    case HANDSET_LOCATE:
      break;

    case F01_CALL_INITIATED:
      if(MailPtr->Status == RSS_SUCCESS)
      {
        switch(CallState[handsetId].CallClass)
        {
          case API_CC_NORMAL:
            //not our case to handle ..
            break;

          case API_CC_INTERNAL:
            {
              ApiInfoElementType *IeBlockPtr = NULL;
              rsuint16 IeBlockLength = 0;
              ApiCallReferenceType destHsId;
              rsuint8 destId = CallState[handsetId].DestinationId;

              {
                ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&CallState[handsetId].ApiSystemCallId);
                SendApiFpCcInfoReq(COLA_TASK, HsId, API_PROGRESS_INVALID, API_CC_SIGNAL_TONES_OFF, IeBlockLength, (rsuint8 *)IeBlockPtr);
                ApiFreeInfoElement((ApiInfoElementType **)&IeBlockPtr);
                IeBlockLength = 0;
              }

              CfSetCallState(handsetId, F03_CALL_PROCEEDING);

              CallState[destId].CallClass = API_CC_INTERNAL;
              CallState[destId].BasicService =  CallState[handsetId].BasicService;
              CallState[destId].DestinationId = handsetId;

              {
#ifdef NATALIE_V11
            	  AudioId.IntExtAudio = API_IEA_INT;
            	  AudioId.SourceTerminalId = handsetId;
                  destHsId.Instance.Host = AllocateHostCallReference();//destId;
                  destHsId.Instance.Fp = 0;
                  CallState[destId].CallReference.Value = destHsId.Value;
#else
                destHsId.HandsetId = destId;
#endif

                { //add API_IE_CALL_STATUS to setup_ack
                  ApiCallStatusType tempCallStatus;
                  tempCallStatus.CallStatusSubId = API_SUB_CALL_STATUS;
                  tempCallStatus.CallStatusValue.State = API_CSS_CALL_SETUP;
                  ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusType), (rsuint8*)&tempCallStatus);
                }
                ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&(CallState[handsetId].ApiSystemCallId));
#ifdef NATALIE_V11
                SendApiFpCcSetupReq(COLA_TASK,
                                    destHsId,                             //CallReference
                                    destId,
                                    AudioId, //SourceId
                                    CallState[destId].BasicService,       //BasicService
                                    CallState[destId].CallClass,          //CallClass
                                    API_CC_SIGNAL_ALERT_ON_PATTERN_0_INT, //Signal
                                    IeBlockLength,
                                    (rsuint8*)IeBlockPtr);

#else
                SendApiFpCcSetupReq(COLA_TASK,
                                    destHsId,                             //CallReference
                                    CallState[destId].BasicService,       //BasicService
                                    CallState[destId].CallClass,          //CallClass
                                    CallState[destId].DestinationId|0x80, //SourceId
                                    API_CC_SIGNAL_ALERT_ON_PATTERN_0_INT, //Signal
                                    IeBlockLength,
                                    (rsuint8*)IeBlockPtr);
#endif
                //Free the allocated memory for the infoelement block
                ApiFreeInfoElement(&IeBlockPtr);
              }
            }
            break;
        }

      }
      break;

  }
}

/****************************************************************************
* FUNCTION:      ApiFpCcSetupCfm
* DESCRIPTION:
****************************************************************************/
void ApiFpCcSetupCfm(ApiFpCcSetupCfmType *MailPtr)
{
#ifdef NATALIE_V11
	  rsuint8 handsetId = GetHsFromCallReference(MailPtr->CallReference);//MailPtr->CallReference.Instance.Host;
	  CallState[handsetId].CallReference = MailPtr->CallReference;
#else
  rsuint8 handsetId = MailPtr->CallReference.HandsetId;
#endif
  //update callstate array with the received info element(s)
  CallState[handsetId].ApiSystemCallId.ApiSubId = API_SUB_CALL_ID;
  CallState[handsetId].ApiSystemCallId.ApiSystemCallId = MailPtr->SystemCallId;

  switch (CallState[handsetId].State)
  {
    case F00_NULL:
      if (MailPtr->Status == RSS_SUCCESS)
      {
        CfSetCallState(handsetId, F06_CALL_PRESENT);
      }
      else
      {
      }
      break;
    case HANDSET_LOCATE:
      if (MailPtr->Status != RSS_SUCCESS)
      {
        CfSetCallState(handsetId, F00_NULL);
      }
      break;
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
//      UnexpectedMessage("API_FP_SETUP_CFM", CallState[handsetId].State);
      break;
  }
}

/****************************************************************************
* FUNCTION:      ApiFpCcAlertInd
* DESCRIPTION:
****************************************************************************/
void ApiFpCcAlertInd(ApiFpCcAlertIndType *MailPtr)
{
  ApiCodecListType *codecListPtr = NULL;
  rsuint8 CodecListLength = 0;
  ApiCallReferenceType HsId;
#ifdef NATALIE_V11
	  rsuint8 handsetId = GetHsFromCallReference(MailPtr->CallReference);//MailPtr->CallReference.Instance.Host;
	  HsId = MailPtr->CallReference;
#else
  rsuint8 handsetId = MailPtr->CallReference.HandsetId;
  HsId.HandsetId = handsetId;
#endif


  if (MailPtr->InfoElementLength > 0)
  {
    ApiInfoElementType *pIe = NULL;

    // API_IE_CODEC_LIST
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_CODEC_LIST);
    if (pIe != NULL)
    {
      CodecListLength = pIe->IeLength;
      codecListPtr = (ApiCodecListType*)pIe->IeData;
    }

    //SystemcallId
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_SYSTEM_CALL_ID);
    if (pIe != NULL)
    {
      CallState[handsetId].ApiSystemCallId.ApiSubId         = ((ApiSystemCallIdType*)(pIe->IeData))->ApiSubId;
      CallState[handsetId].ApiSystemCallId.ApiSystemCallId  = ((ApiSystemCallIdType*)(pIe->IeData))->ApiSystemCallId;
    }

    // API_IE_PROPRIETARY
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_PROPRIETARY);
    if (pIe != NULL)
    {
      //FIX ME: Handle proprietary data
    }
  }

  switch (CallState[handsetId].State)
  {
    case F06_CALL_PRESENT:
      CfSetCallState(handsetId, F07_CALL_RECEIVED);
      if (CallState[handsetId].CallClass == API_CC_INTERNAL)
      {
        ApiInfoElementType *IeBlockPtr = NULL;
        rsuint16 IeBlockLength = 0;
        ApiCallReferenceType destHsId;
        ApiCallReferenceType HsId;
        rsuint8 desthandsetId = CallState[handsetId].DestinationId;
#ifdef NATALIE_V11
        destHsId = CallState[desthandsetId].CallReference;
        HsId = CallState[handsetId].CallReference;
#else
        destHsId.HandsetId = CallState[handsetId].DestinationId;
        HsId.HandsetId = handsetId;
#endif
        ApiFpIntSendCallingPartyNumber(HsId);                                   //Send out Calling party number in CC_INFO

        //add coedclist to infoelement block
        if(CodecListLength)
        {
           CallState[handsetId].ProposedCodecListLength = CodecListLength;
           CallState[handsetId].ProposedCodecListPtr = (ApiCodecListType*)RcHeapAllocEx(CodecListLength, RHF_NULL_ON_FULL);
           util_memcpy(CallState[handsetId].ProposedCodecListPtr, codecListPtr, CodecListLength);

           CallState[desthandsetId].ProposedCodecListLength = CodecListLength;
           CallState[desthandsetId].ProposedCodecListPtr = (ApiCodecListType*)RcHeapAllocEx(CodecListLength, RHF_NULL_ON_FULL);
           util_memcpy(CallState[desthandsetId].ProposedCodecListPtr, codecListPtr, CodecListLength);

           ApiPutCodecListInIe(codecListPtr,
                               &IeBlockPtr,
                               &IeBlockLength);
        }

        //add system call id to infoelement block
        ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&(CallState[desthandsetId].ApiSystemCallId));//(rsuint8*)&SystemCallId);

        { //add API_IE_CALL_STATUS to setup_ack
           ApiCallStatusType tempCallStatus;
           tempCallStatus.CallStatusSubId = API_SUB_CALL_STATUS;
           tempCallStatus.CallStatusValue.State = API_CSS_CALL_ALERTING;
           ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusType), (rsuint8*)&tempCallStatus);
        }

        SendApiFpCcAlertReq(COLA_TASK,
                          destHsId,
                          API_IN_BAND_NOT_AVAILABLE,
                          API_CC_SIGNAL_DIAL_TONE_ON,
                          IeBlockLength,
                          (rsuint8*)IeBlockPtr);

        //KTS_CHECK
        //ApiFreeInfoElement(&IeBlockPtr);
        ApiFreeInfoElement((ApiInfoElementType **)&IeBlockPtr);


        //LineSimAlert(CallState[handsetId].LineId, CodecListLength, codecListPtr);

      }
      else
      {
        if (CodecListLength>0)
        {
          CallState[handsetId].ProposedCodecListLength = CodecListLength;
          CallState[handsetId].ProposedCodecListPtr = (ApiCodecListType*)RcHeapAllocEx(CodecListLength, RHF_NULL_ON_FULL);
          util_memcpy(CallState[handsetId].ProposedCodecListPtr, codecListPtr, CodecListLength);
        }

        //KTS_TEST
        //LineSimAlert(CallState[handsetId].LineId, CodecListLength, codecListPtr);

        {
          ApiInfoElementType *IeBlockPtr = NULL;
          rsuint16 IeBlockLength = 0;
          //add API_IE_SYSTEM_CALL_ID
          ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&CallState[handsetId].ApiSystemCallId);

          //KTS_TEST
          //not needed now
          //PutClipInIe(CallState[handsetId].LineId, &IeBlockPtr, &IeBlockLength);

          SendApiFpCcInfoReq(COLA_TASK, HsId, API_PROGRESS_INVALID, API_CC_SIGNAL_TONES_OFF, IeBlockLength, (rsuint8 *)IeBlockPtr);

          //KTS_CHECK: need to check why it is crashed
          //ApiFreeInfoElement(&IeBlockPtr);
          ApiFreeInfoElement((ApiInfoElementType **)&IeBlockPtr);
        }

      }
      break;
    case HANDSET_LOCATE:
      //Ignore
      break;
    case F01_CALL_INITIATED:
    case F02_OVERLAP_SENDING:
    case F03_CALL_PROCEEDING:
    case F00_NULL:
    case F04_CALL_DELIVERED:
    case F07_CALL_RECEIVED:
    case F10_ACTIVE:
    case F19_RELEASE_PENDING:
    case CODEC_NEGOTIATION_FROM_HS:
    case CODEC_NEGOTIATION_FROM_LINE:
    case CODEC_NEGOTIATION_IN_SETUP:
      //KTS_TEST
      //UnexpectedMessage("API_FP_ALERT_IND", CallState[handsetId].State);
      break;
  }
}

/****************************************************************************
* FUNCTION:      ApiFpCcConnectInd
* DESCRIPTION:
****************************************************************************/
void ApiFpCcConnectInd(ApiFpCcConnectIndType *MailPtr)
{
  rsuint8 i;
  ApiCallReferenceType HsId;
    ApiCodecListType *codecListPtr = NULL;
  rsuint8 CodecListLength = 0;
#ifdef NATALIE_V11
  rsuint8 handsetId = GetHsFromCallReference(MailPtr->CallReference);//MailPtr->CallReference.Instance.Host;
  HsId = MailPtr->CallReference;
#else
  rsuint8 handsetId = MailPtr->CallReference.HandsetId;
  HsId.HandsetId = handsetId;
#endif
//  ApiCallReferenceType HsId;
//  HsId.HandsetId = handsetId;

  if (MailPtr->InfoElementLength > 0)
  {
    ApiInfoElementType *pIe = NULL;

    // API_IE_CODEC_LIST
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_CODEC_LIST);
    if (pIe != NULL)
    {
      CodecListLength = pIe->IeLength;
      codecListPtr = (ApiCodecListType*)pIe->IeData;
    }

    //SystemcallId
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_SYSTEM_CALL_ID);
    if (pIe != NULL)
    {
      CallState[handsetId].ApiSystemCallId.ApiSubId         = ((ApiSystemCallIdType*)(pIe->IeData))->ApiSubId;
      CallState[handsetId].ApiSystemCallId.ApiSystemCallId  = ((ApiSystemCallIdType*)(pIe->IeData))->ApiSystemCallId;
    }

    // API_IE_PROPRIETARY
    pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                             MailPtr->InfoElementLength,
                             API_IE_PROPRIETARY);
    if (pIe != NULL)
    {
      //FIX ME: Handle proprietary data
    }
  }

  switch (CallState[handsetId].State)
  {
    case F06_CALL_PRESENT:
    case F07_CALL_RECEIVED:
      CfSetCallState(handsetId, F10_ACTIVE);
      switch(CallState[handsetId].CallClass)
      {
        case API_CC_NORMAL:
        {
          rsuint8 *CodecListLengthPtr = (rsuint8 *)RcHeapAllocEx(sizeof(rsuint8), RHF_NULL_ON_FULL);
          ApiCcBasicServiceType *BasicServicePtr = (ApiCcBasicServiceType *)RcHeapAllocEx(sizeof(ApiCcBasicServiceType), RHF_NULL_ON_FULL);
          ApiCodecListType TempCodecList;
          //set audio format
          ApiAudioDataFormatType pcmDataFormat = LineSimGetPcmDataFormat(CallState[handsetId].LineId);

          TempCodecList.NegotiationIndicator = API_NI_POSSIBLE;
          TempCodecList.NoOfCodecs = 1;
          TempCodecList.Codec[0] = CodecG726;

          if (pcmDataFormat != AP_DATA_FORMAT_INVALID)
          {
           StopDelayAudioOpenTimer(CallState[handsetId].LineId);
           SendApiFpSetAudioFormatReq(COLA_TASK,
                                      CallState[handsetId].LineId,
                                      pcmDataFormat);
          }

          LineSimGetCodecList(CallState[handsetId].LineId, CodecListLengthPtr, BasicServicePtr);
          RcHeapFreeEx((void *)CodecListLengthPtr, RHF_NULL_ON_FULL);                                            //Free the memory


          if (*BasicServicePtr == API_WIDEBAND_SPEECH)
          {
           if (CodecListLength > 0)
           {
             LineSimConnect(CallState[handsetId].LineId, CodecListLength, codecListPtr);
           }
           else
           {
             //Tjek if codeclist was send in alert/setup_ack
             if (CallState[handsetId].ProposedCodecListLength == 0)
             {
               //Connect as GAB hs
               LineSimConnect(CallState[handsetId].LineId, 6, &TempCodecList);
             }
             else
             {
               LineSimConnect(CallState[handsetId].LineId, CallState[handsetId].ProposedCodecListLength, CallState[handsetId].ProposedCodecListPtr);
               CallState[handsetId].ProposedCodecListLength = 0;
               RcHeapFreeEx((void *)CallState[handsetId].ProposedCodecListPtr, RHF_NULL_ON_FULL);
             }
           }
          }
          else
          {
            //If basic service is set to basic speech, used codec 726
            LineSimConnect(CallState[handsetId].LineId, 6, &TempCodecList);
            CallState[handsetId].ProposedCodecListLength = 0;
            RcHeapFreeEx((void *)(CallState[handsetId].ProposedCodecListPtr), RHF_NULL_ON_FULL);
          }
          RcHeapFreeEx((void *)BasicServicePtr, RHF_NULL_ON_FULL);
          CallState[handsetId].Connected2Line = TRUE;
  //SSTRANSP        ApiAudioDataFormatType pcmDataFormat = LineSimGetPcmDataFormat(CallState[handsetId].LineId);
  //SSTRANSP        if (pcmDataFormat != AP_DATA_FORMAT_INVALID)
  //SSTRANSP        {
  //SSTRANSP          SendApiFpSetAudioFormatReq(CVMAPI_TASK,
  //SSTRANSP                                  CallState[handsetId].LineId,
  //SSTRANSP                                  pcmDataFormat);
  //SSTRANSP        }
  //SSTRANSP        else
  //SSTRANSP        {
  //SSTRANSP          //AP_DATA_FORMAT_INVALID is returned if this PCM channel is set in loopback mode
  //SSTRANSP          //SendApiFpSetPcmLoopbackReq(CVMAPI_TASK, CallState[handsetId].LineId);
  //SSTRANSP        }
          for (i=0; i<NO_HANDSETS; i++)
          {
           if (CallState[i].CallClass == API_CC_NORMAL && CallState[i].State != F10_ACTIVE)
           {
             ApiCallReferenceType HsIdTemp;
#ifdef NATALIE_V11
             HsIdTemp.Value = CallState[handsetId].CallReference.Value;//i;
#else
             HsIdTemp.HandsetId = i;
#endif
             SendApiFpCcReleaseReq(COLA_TASK, HsIdTemp, API_RR_NORMAL,0 ,NULL);
           }
          }

          SendApiFpCcConnectRes(COLA_TASK, HsId, RSS_SUCCESS, 0, NULL); // 'CC-CONNECT-ACK' in the ETSI spec.

          { // send CC_INFO_REQ with API_IE_SYSTEM_CALL_ID and API_IE_CALL_STATUS
            ApiInfoElementType *IeBlockPtr = NULL; // ie block pointer for SetupAckReq
            rsuint16 IeBlockLength = 0;

            //add API_IE_SYSTEM_CALL_ID setup_ack
            ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&CallState[handsetId].ApiSystemCallId);

            { //add API_IE_CALL_STATUS to setup_ack
              ApiCallStatusType tempCallStatus;
              tempCallStatus.CallStatusSubId = API_SUB_CALL_STATUS;
              tempCallStatus.CallStatusValue.State = API_CSS_CALL_CONNECT;
              ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusType), (rsuint8*)&tempCallStatus);
            }
            SendApiFpCcInfoReq(COLA_TASK, HsId, API_PROGRESS_INVALID, API_CC_SIGNAL_TONES_OFF, IeBlockLength, (rsuint8 *)IeBlockPtr);
            ApiFreeInfoElement(&IeBlockPtr);
          }

        }
        break;


        case API_CC_INTERNAL:
          {
            ApiInfoElementType *IeBlockPtr = NULL;
            rsuint16 IeBlockLength = 0;
            ApiCallReferenceType destHsId;
            rsuint8 desthandsetId = CallState[handsetId].DestinationId;
            ApiCallReferenceType srcHsId;
#ifdef NATALIE_V11
            destHsId = CallState[desthandsetId].CallReference;
            srcHsId = HsId;
#else
            destHsId.HandsetId = desthandsetId;
            srcHsId.HandsetId = handsetId;
#endif
            SendApiFpCcConnectRes(COLA_TASK, HsId, RSS_SUCCESS, 0, NULL);

            { // send CC_INFO_REQ with API_IE_SYSTEM_CALL_ID and API_IE_CALL_STATUS
              ApiInfoElementType *IeBlockPtr = NULL; // ie block pointer for SetupAckReq
              rsuint16 IeBlockLength = 0;


              //add system call id to infoelement block
              ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&(CallState[handsetId].ApiSystemCallId));//(rsuint8*)&SystemCallId);

              { //add API_IE_CALL_STATUS to setup_req
                ApiCallStatusType tempCallStatus;
                tempCallStatus.CallStatusSubId = API_SUB_CALL_STATUS;
                tempCallStatus.CallStatusValue.State = API_CSS_CALL_CONNECT;
                ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusType), (rsuint8*)&tempCallStatus);
              }

              SendApiFpCcInfoReq(COLA_TASK, HsId, API_PROGRESS_INVALID, API_CC_SIGNAL_TONES_OFF, IeBlockLength, (rsuint8 *)IeBlockPtr);

              ApiFreeInfoElement(&IeBlockPtr);
            }

            if(CodecListLength)
            {
              if(codecListPtr->NoOfCodecs == 1)
              {
                //SSDEB: send connect_req without codec list (already selected)
                //check if proposed codec equals selected codec
                if(CallState[desthandsetId].ProposedCodecListPtr != NULL)
                {
                  if(codecListPtr->Codec[0].Codec != CallState[desthandsetId].ProposedCodecListPtr->Codec[0].Codec)
                  {
                    if(codecListPtr->Codec[0].Codec == API_CT_G726)
                    {
                      ApiInfoElementType *IeBlockPtr = NULL;
                      rsuint16 IeBlockLength = 0;

                      ApiCodecListType TempCodecList;
                      TempCodecList.NegotiationIndicator = API_NI_POSSIBLE;
                      TempCodecList.NoOfCodecs = 1;
                      TempCodecList.Codec[0] = CodecG726;

                      //KTS: protection: in case that the intercom doesn't go through PCM
                      if(CallState[handsetId].LineId<LS_NO_LINES&&CallState[desthandsetId].LineId<LS_NO_LINES)
                      {
                        //updddate linesim with correct codec
                        LineSimSelectCodec(CallState[handsetId].LineId, TempCodecList.Codec[0]);
                        LineSimSelectCodec(CallState[desthandsetId].LineId, TempCodecList.Codec[0]);
                      }
                      ApiPutCodecListInIe(&TempCodecList,
                                          &IeBlockPtr,
                                          &IeBlockLength);
                      SendApiFpCcModifyCodecReq(COLA_TASK, destHsId, IeBlockLength, (rsuint8*)IeBlockPtr);
                      ApiFreeInfoElement(&IeBlockPtr);
                    }
                  }
                }
                else
                {
                  ApiPutCodecListInIe(codecListPtr,
                                      &IeBlockPtr,
                                      &IeBlockLength);

                  //KTS: protection: in case that the intercom doesn't go through PCM
                  if(CallState[handsetId].LineId<LS_NO_LINES&&CallState[desthandsetId].LineId<LS_NO_LINES)
                  {
                    LineSimSelectCodec(CallState[handsetId].LineId, codecListPtr->Codec[0]);
                    LineSimSelectCodec(CallState[desthandsetId].LineId, codecListPtr->Codec[0]);
                  }
                }
              }
              else
              {
                ApiPutCodecListInIe(codecListPtr,
                                    &IeBlockPtr,
                                    &IeBlockLength);

                  //KTS: protection: in case that the intercom doesn't go through PCM
                  if(CallState[handsetId].LineId<LS_NO_LINES&&CallState[desthandsetId].LineId<LS_NO_LINES)
                  {
                    LineSimSelectCodec(CallState[handsetId].LineId, codecListPtr->Codec[0]);
                    LineSimSelectCodec(CallState[desthandsetId].LineId, codecListPtr->Codec[0]);
                  }
              }
            }
            else
            {
              //check if codec list already received in alert
              //*Siemens C38H does not send a codec (G726) back in normal intercom
              if(CallState[handsetId].ProposedCodecListLength == 0)
              {
                ApiCodecListType TempCodecList;
                TempCodecList.NegotiationIndicator = API_NI_POSSIBLE;
                TempCodecList.NoOfCodecs = 1;

                // if no coedec list is received in alert or here in connect we make our own matching the basicservice
                if (CallState[handsetId].BasicService == API_WIDEBAND_SPEECH)
                {
                  TempCodecList.Codec[0] = CodecG722;
                }
                else
                {
                  TempCodecList.Codec[0] = CodecG726;
                }
                //KTS: protection: in case that the intercom doesn't go through PCM
                if(CallState[handsetId].LineId<LS_NO_LINES&&CallState[desthandsetId].LineId<LS_NO_LINES)
                {
                  //updddate linesim with correct codec
                  LineSimSelectCodec(CallState[handsetId].LineId, TempCodecList.Codec[0]);
                  LineSimSelectCodec(CallState[desthandsetId].LineId, TempCodecList.Codec[0]);
                }
                ApiPutCodecListInIe(&TempCodecList,
                                    &IeBlockPtr,
                                    &IeBlockLength);
              }
            }
            //KTS: protection: in case that the intercom doesn't go through PCM
            if(CallState[handsetId].LineId<LS_NO_LINES)
            {
              //set audio format
              ApiAudioDataFormatType pcmDataFormat = LineSimGetPcmDataFormat(CallState[handsetId].LineId);

              if (pcmDataFormat != AP_DATA_FORMAT_INVALID)
              {
               StopDelayAudioOpenTimer(CallState[handsetId].LineId);
               SendApiFpSetAudioFormatReq(COLA_TASK,
                                          CallState[handsetId].LineId,
                                          pcmDataFormat);
              }
            }

            //add system call id to infoelement block
            ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&(CallState[desthandsetId].ApiSystemCallId));//(rsuint8*)&SystemCallId);

            { //add API_IE_CALL_STATUS to setup_req
              ApiCallStatusType tempCallStatus;
              tempCallStatus.CallStatusSubId = API_SUB_CALL_STATUS;
              tempCallStatus.CallStatusValue.State = API_CSS_CALL_CONNECT;
              ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusType), (rsuint8*)&tempCallStatus);
            }

            SendApiFpCcConnectReq(COLA_TASK,
                                  destHsId,
                                  IeBlockLength,
                                  (rsuint8*)IeBlockPtr);

            //Free the allocated memory for the infoelement block
            ApiFreeInfoElement(&IeBlockPtr);
          }
          break;

        default:
          break;
      }
      break;

    case HANDSET_LOCATE:
      //Handset found relase the connction
      for (i=0; i<NO_HANDSETS; i++)
      {
        if (CallState[i].State == HANDSET_LOCATE)
        {
#ifdef NATALIE_V11
        	HsId.Value = CallState[i].CallReference.Value;//i;
#else
          HsId.HandsetId = i;
#endif
          SendApiFpCcReleaseReq(COLA_TASK, HsId, API_RR_NORMAL,0 ,NULL);
        }
      }
      break;

    case F00_NULL:
    case F01_CALL_INITIATED:
    case F02_OVERLAP_SENDING:
    case F03_CALL_PROCEEDING:
    case F04_CALL_DELIVERED:
    case F10_ACTIVE:
    case F19_RELEASE_PENDING:
    case CODEC_NEGOTIATION_FROM_HS:
    case CODEC_NEGOTIATION_FROM_LINE:
    case CODEC_NEGOTIATION_IN_SETUP:
    case HEADSET_INTERCEPT:
      SendApiFpCcConnectRes(COLA_TASK, HsId, RSS_REJECTED, 0, NULL);
      break;
  }
}

/****************************************************************************
* FUNCTION:      ApiFpCcConnectCfm
* DESCRIPTION:
****************************************************************************/
void ApiFpCcConnectCfm(ApiFpCcConnectCfmType *MailPtr)
{
#ifdef NATALIE_V11
	  rsuint8 handsetId = GetHsFromCallReference(MailPtr->CallReference);//MailPtr->CallReference.Instance.Host;
#else
  rsuint8 handsetId = MailPtr->CallReference.HandsetId;
  ApiCallReferenceType DstHsId;
  DstHsId.HandsetId = CallState[handsetId].DestinationId;
#endif

  switch (CallState[handsetId].State)
  {
    case F01_CALL_INITIATED:
    case F02_OVERLAP_SENDING:
    case F03_CALL_PROCEEDING:
    case F04_CALL_DELIVERED:
    case F10_ACTIVE:
      if (MailPtr->Status != RSS_SUCCESS)
      {
        //LogMessage("API_FP_CONNECT_CFM with Status != RSS_SUCCESS is received!");
      }
      else
      {
        CfSetCallState(handsetId, F10_ACTIVE);
      }
      break;

    case F00_NULL:
    case F06_CALL_PRESENT:
    case F07_CALL_RECEIVED:
    case F19_RELEASE_PENDING:
    case CODEC_NEGOTIATION_FROM_HS:
    case CODEC_NEGOTIATION_FROM_LINE:
    case CODEC_NEGOTIATION_IN_SETUP:
    case HANDSET_LOCATE:
      //UnexpectedMessage("API_FP_CONNECT_CFM", CallState[handsetId].State);
      break;
  }
}

/****************************************************************************
* FUNCTION:      ApiFpCcReleaseInd
* DESCRIPTION:
****************************************************************************/
void ApiFpCcReleaseInd(ApiFpCcReleaseIndType *MailPtr)
{
  rsuint8 LineId;

  ApiCallReferenceType HsId;
#ifdef NATALIE_V11
  rsuint8 handsetId = GetHsFromCallReference(MailPtr->CallReference);//MailPtr->CallReference.Instance.Host;
  HsId = MailPtr->CallReference;
#else
  rsuint8 handsetId = MailPtr->CallReference.HandsetId;
  HsId.HandsetId = handsetId;
#endif
  switch (CallState[handsetId].State)
  {
    case F00_NULL:
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
      SendApiFpCcReleaseRes(COLA_TASK, HsId, RSS_SUCCESS, 0, NULL);

      LineId = CfGetLineId(handsetId);

      if (CallState[handsetId].CallClass == API_CC_INTERNAL)
      {
        if (CallState[handsetId].DestinationId > 0 && CallState[CallState[handsetId].DestinationId].State != F00_NULL)
        {
          ApiCallReferenceType destHsId;
#ifdef NATALIE_V11
          destHsId = CallState[CallState[handsetId].DestinationId].CallReference;
          SendApiFpCcReleaseReq(COLA_TASK, destHsId, API_RR_NORMAL, 0, NULL);

          //KTS: INTEERCOM not going through PCM
          if(CallState[GetHsFromCallReference(destHsId)].LineId<LS_NO_LINES)
            LineSimRelease(CallState[GetHsFromCallReference(destHsId)].LineId);
          CfSetCallState(GetHsFromCallReference(destHsId) , F00_NULL);
#else
          destHsId.HandsetId = CallState[handsetId].DestinationId;
          SendApiFpCcReleaseReq(COLA_TASK, destHsId, API_RR_NORMAL, 0, NULL);

          //KTS: INTEERCOM not going through PCM
          if(CallState[destHsId.HandsetId].LineId<LS_NO_LINES)
            LineSimRelease(CallState[destHsId.HandsetId].LineId);
          CfSetCallState(destHsId.HandsetId , F00_NULL);
#endif
        }
        CfSetCallState(handsetId, F00_NULL);
      }
      else if (CallState[handsetId].CallClass == API_CC_NORMAL)
      {
        if(CfGetLineUserNo(LineId)==1)
        {
          LineSimRelease(CallState[handsetId].LineId);
          SendApiFpSetAudioFormatReq(COLA_TASK, CallState[handsetId].LineId, AP_DATA_FORMAT_NONE);  // close audio
        }

        StopDelayAudioOpenTimer(CallState[handsetId].LineId);
        CfSetCallState(handsetId, F00_NULL);
        CallState[handsetId].Connected2Line = FALSE;
      }
      break;

  }
}

/****************************************************************************
* FUNCTION:      ApiFpCcReleaseCfm
* DESCRIPTION:
****************************************************************************/
void ApiFpCcReleaseCfm(ApiFpCcReleaseCfmType *MailPtr)
{
#ifdef NATALIE_V11
	  rsuint8 handsetId = GetHsFromCallReference(MailPtr->CallReference);//MailPtr->CallReference.Instance.Host;
#else
  rsuint8 handsetId = MailPtr->CallReference.HandsetId;
#endif
  switch (CallState[handsetId].State)
  {
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
    case HANDSET_LOCATE:
    case HEADSET_INTERCEPT:
      CfSetCallState(handsetId, F00_NULL);
      break;

    case F00_NULL:
      //UnexpectedMessage("API_FP_RELEASE_CFM", CallState[handsetId].State);
      break;
  }
}

/****************************************************************************
* FUNCTION:      ApiFpCcRejectInd
* DESCRIPTION:
****************************************************************************/
void ApiFpCcRejectInd(ApiFpCcRejectIndType *MailPtr)
{
#ifdef NATALIE_V11
	  rsuint8 handsetId = GetHsFromCallReference(MailPtr->CallReference);//MailPtr->CallReference.Instance.Host;
#else
  rsuint8 handsetId = MailPtr->CallReference.HandsetId;
#endif
  switch (CallState[handsetId].State)
  {
    case F06_CALL_PRESENT:
    case F07_CALL_RECEIVED:
      if (CallState[handsetId].CallClass == API_CC_INTERNAL)
      {
        if (CallState[handsetId].DestinationId > 0 && CallState[CallState[handsetId].DestinationId].State != F00_NULL)
        {
          ApiCallReferenceType destHsId;
#ifdef NATALIE_V11
          destHsId = CallState[CallState[handsetId].DestinationId].CallReference;
          SendApiFpCcReleaseReq(COLA_TASK, destHsId, API_RR_NORMAL, 0, NULL);

          //KTS: protection: in case that the intercom doesn't go through PCM
          if(CallState[GetHsFromCallReference(destHsId)].LineId<LS_NO_LINES)
            LineSimRelease(CallState[GetHsFromCallReference(destHsId)].LineId);
#else
          destHsId.HandsetId = CallState[handsetId].DestinationId;
          SendApiFpCcReleaseReq(COLA_TASK, destHsId, API_RR_NORMAL, 0, NULL);

          //KTS: protection: in case that the intercom doesn't go through PCM
          if(CallState[destHsId.HandsetId].LineId<LS_NO_LINES)
          LineSimRelease(CallState[destHsId.HandsetId].LineId);
#endif
        }
      }
      else if (CallState[handsetId].CallClass == API_CC_NORMAL)
      {
        LineSimReject(CallState[handsetId].LineId);
      }

      //KTS: protection: in case that the intercom doesn't go through PCM
      if(CallState[handsetId].LineId<LS_NO_LINES)
      LineSimRelease(CallState[handsetId].LineId);
      CfSetCallState(handsetId, F00_NULL);
      break;

      // no break, fall through intended
    case F01_CALL_INITIATED:
    case F03_CALL_PROCEEDING:
    case F04_CALL_DELIVERED:
    case F10_ACTIVE:
    case F19_RELEASE_PENDING:
    case CODEC_NEGOTIATION_FROM_HS:
    case CODEC_NEGOTIATION_FROM_LINE:
    case CODEC_NEGOTIATION_IN_SETUP:
    case HANDSET_LOCATE:
      if (CallState[handsetId].CallClass == API_CC_INTERNAL)
      {
        if (CallState[handsetId].DestinationId > 0 && CallState[CallState[handsetId].DestinationId].State != F00_NULL)
        {
          ApiCallReferenceType destHsId;
#ifdef NATALIE_V11
          destHsId = CallState[CallState[handsetId].DestinationId].CallReference;
          SendApiFpCcReleaseReq(COLA_TASK, destHsId, API_RR_NORMAL, 0, NULL);

          //KTS: protection: in case that the intercom doesn't go through PCM
          if(CallState[GetHsFromCallReference(destHsId)].LineId<LS_NO_LINES)
            LineSimRelease(CallState[GetHsFromCallReference(destHsId)].LineId);
#else
          destHsId.HandsetId = CallState[handsetId].DestinationId;
          SendApiFpCcReleaseReq(COLA_TASK, destHsId, API_RR_NORMAL, 0, NULL);

          //KTS: protection: in case that the intercom doesn't go through PCM
          if(CallState[destHsId.HandsetId].LineId<LS_NO_LINES)
          LineSimRelease(CallState[destHsId.HandsetId].LineId);
#endif
        }
        //KTS: protection: in case that the intercom doesn't go through PCM
        if(CallState[handsetId].LineId<LS_NO_LINES)
        {
        LineSimRelease(CallState[handsetId].LineId);
        SendApiFpSetAudioFormatReq(COLA_TASK, CallState[handsetId].LineId, AP_DATA_FORMAT_NONE);
        StopDelayAudioOpenTimer(CallState[handsetId].LineId);
        }
        CfSetCallState(handsetId, F00_NULL);
      }
      else if (CallState[handsetId].CallClass == API_CC_NORMAL)
      {
        rsuint8 LineId;

        LineId = CallState[handsetId].LineId;
        CfSetCallState(handsetId, F00_NULL);
        if(CfGetLineUserNo(LineId)==0)
        {
          LineSimRelease(CallState[handsetId].LineId);
          SendApiFpSetAudioFormatReq(COLA_TASK, CallState[handsetId].LineId, AP_DATA_FORMAT_NONE);  // close audio
          StopDelayAudioOpenTimer(CallState[handsetId].LineId);
        }
      }
      break;

    case F02_OVERLAP_SENDING:
      if (CallState[handsetId].CallClass == API_CC_INTERNAL)
      {
        if (CallState[handsetId].DestinationId > 0 && CallState[CallState[handsetId].DestinationId].State != F00_NULL)
        {
          ApiCallReferenceType destHsId;
#ifdef NATALIE_V11
          destHsId = CallState[CallState[handsetId].DestinationId].CallReference;
          SendApiFpCcReleaseReq(COLA_TASK, destHsId, API_RR_NORMAL, 0, NULL);
          //KTS: protection: in case that the intercom doesn't go through PCM
          if(CallState[handsetId].LineId<LS_NO_LINES&&CallState[GetHsFromCallReference(destHsId)].LineId<LS_NO_LINES)
          {
            LineSimRelease(CallState[GetHsFromCallReference(destHsId)].LineId);
            LineSimRelease(CallState[handsetId].LineId);
          }
#else
          destHsId.HandsetId = CallState[handsetId].DestinationId;
          SendApiFpCcReleaseReq(COLA_TASK, destHsId, API_RR_NORMAL, 0, NULL);
          //KTS: protection: in case that the intercom doesn't go through PCM
          if(CallState[handsetId].LineId<LS_NO_LINES&&CallState[destHsId.HandsetId].LineId<LS_NO_LINES)
          {
          LineSimRelease(CallState[destHsId.HandsetId].LineId);
          LineSimRelease(CallState[handsetId].LineId);
        }
#endif
        }
        else
        {
          //KTS: protection: in case that the intercom doesn't go through PCM
          if(CallState[handsetId].LineId<LS_NO_LINES)
          {
          LineSimReject(CallState[handsetId].LineId);
        }
      }
      }
      else if (CallState[handsetId].CallClass == API_CC_NORMAL)
      {
        LineSimRelease(CallState[handsetId].LineId);
      }

      //KTS: protection: in case that the intercom doesn't go through PCM
      if(CallState[handsetId].LineId<LS_NO_LINES)
      {
      StopDelayAudioOpenTimer(CallState[handsetId].LineId);
      SendApiFpSetAudioFormatReq(COLA_TASK, CallState[handsetId].LineId, AP_DATA_FORMAT_NONE);
      }
      CfSetCallState(handsetId, F00_NULL);
      break;

    case F00_NULL:
      break;
  }
}

/****************************************************************************
* FUNCTION:      LsGetLine
* DESCRIPTION:
****************************************************************************/
rsuint8 LsGetLine(rsuint8 HandsetId, rsuint8 RequestLineId)
{
  if (RequestLineId < LS_NO_LINES)
  {
    rsbool lineIdFound = FALSE;
    rsuint8 nrOfHandsets;

    for(nrOfHandsets = 1; nrOfHandsets < NO_HANDSETS; nrOfHandsets++ )
    {
      if(CallState[nrOfHandsets].LineId == RequestLineId)
      {
        lineIdFound = TRUE;
      }
    }
    if(lineIdFound == FALSE)
    {
      if(LineSimGetLineState(RequestLineId)==LS_ON_HOOK)
      {
        return RequestLineId;
      }
    }
    return LS_LINE_INVALID;
  }
  return LS_LINE_INVALID;
}

/****************************************************************************
* FUNCTION:      ConnectAudioToLine
* DESCRIPTION:
****************************************************************************/
void ConnectAudioToLine(rsuint8 HandsetId, rsuint8 LineId)
{
  RsStatusType ConnectStatus = RSS_SUCCESS;
  ApiCallReferenceType HsId;
  ApiInfoElementType *IeAckBlockPtr = NULL; // ie block pointer for SetupAckReq
  rsuint16 IeAckBlockLength = 0;
  ApiInfoElementType *IeConBlockPtr = NULL; // ie block pointer for ConnectReq
  rsuint16 IeConBlockLength = 0;

  ApiCodecListType codecList;

  ApiAudioDataFormatType pcmDataFormat = LineSimGetPcmDataFormat(LineId);
#ifdef NATALIE_V11
  HsId = CallState[HandsetId].CallReference;
#else
  HsId.HandsetId = HandsetId;
#endif
  codecList.NegotiationIndicator = API_NI_POSSIBLE;
  codecList.NoOfCodecs = 1;
  codecList.Codec[0] = LineSimGetSelectedCodec(LineId);

  if (pcmDataFormat != AP_DATA_FORMAT_INVALID)
  {
    StopDelayAudioOpenTimer(LineId);
    SendApiFpSetAudioFormatReq(COLA_TASK, LineId, pcmDataFormat);
  }
  else
  {
    //AP_DATA_FORMAT_INVALID is returned if this PCM channel is set in loopback mode
    //SendApiFpSetPcmLoopbackReq(COLA_TASK, LineId);
  }

  if (codecList.Codec[0].Codec == API_CT_NONE)
  {
    //Basicservice is set to bacisspeech, thus send narrowband codec, PI task will remove codec if HS is GAB
    codecList.Codec[0] = CodecG726;
  }
  ConnectStatus = LineSimSelectCodec(LineId, codecList.Codec[0]);
  if (ConnectStatus == RSS_SUCCESS)
  {
    {
      // find dataformat matching the selected line
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
            { // add G722 codec to codec list
              ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[0];
              p->Codec = API_CT_G722;
              p->ApiAudioDataFormat = AP_DATA_FORMAT_LINEAR_16kHz;
            }
            { // add G726 codec to codec list
              ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[1];
              p->Codec = API_CT_G726;
              p->ApiAudioDataFormat = AP_DATA_FORMAT_LINEAR_8kHz;
            }
            //build infoelement for ConnectReq
            ApiBuildInfoElement(&IeConBlockPtr,
                                &IeConBlockLength,
                                API_IE_AUDIO_DATA_FORMAT,
                                IeLength,
                                (rsuint8 *)IeData);

            //build infoelement for SetupAckReq
            ApiBuildInfoElement(&IeAckBlockPtr,
                                &IeAckBlockLength,
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
            { // add G726 codec to codec list
              ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[0];
              p->Codec = API_CT_G726;
              p->ApiAudioDataFormat = AP_DATA_FORMAT_G726;
            }

            //build infoelement for ConnectReq
            ApiBuildInfoElement(&IeConBlockPtr,
                                &IeConBlockLength,
                                API_IE_AUDIO_DATA_FORMAT,
                                IeLength,
                                (rsuint8 *)IeData);

            //build infoelement for SetupAckReq
            ApiBuildInfoElement(&IeAckBlockPtr,
                                &IeAckBlockLength,
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
            { // add G722 codec to codec list
              ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[0];
              p->Codec = API_CT_G722;
              p->ApiAudioDataFormat = AP_DATA_FORMAT_G722;
            }
            { // add G726 codec to codec list
              ApiAudioDataFormatInfoType* p = (ApiAudioDataFormatInfoType*)&IeData->ApiAudioDataFormatInfo[1];
              p->Codec = API_CT_G726;
              p->ApiAudioDataFormat = AP_DATA_FORMAT_G726;
            }

            //build infoelement for ConnectReq
            ApiBuildInfoElement(&IeConBlockPtr,
                                &IeConBlockLength,
                                API_IE_AUDIO_DATA_FORMAT,
                                IeLength,
                                (rsuint8 *)IeData);

            //build infoelement for SetupAckReq
            ApiBuildInfoElement(&IeAckBlockPtr,
                                &IeAckBlockLength,
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
#ifndef RHEA
    if(CallState[HandsetId].ProposedCodecListLength != 6)
#endif
    {
      // add selected codec to setup_ack_req (to support Siemens Gigaset)
      codecList.NegotiationIndicator = API_NI_POSSIBLE;
      codecList.NoOfCodecs = 1;
      codecList.Codec[0] = LineSimGetSelectedCodec(LineId);
    }
    ApiPutCodecListInIe(&codecList, &IeAckBlockPtr, &IeAckBlockLength);

    //add API_IE_SYSTEM_CALL_ID setup_ack
    ApiBuildInfoElement(&IeAckBlockPtr, &IeAckBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&CallState[HandsetId].ApiSystemCallId);

    { //add API_IE_CALL_STATUS to setup_ack
      ApiCallStatusType tempCallStatus;
      tempCallStatus.CallStatusSubId = API_SUB_CALL_STATUS;
      tempCallStatus.CallStatusValue.State = API_CSS_CALL_SETUP_ACK;
      ApiBuildInfoElement(&IeAckBlockPtr, &IeAckBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusType), (rsuint8*)&tempCallStatus);
    }

    { //add API_IE_LINE_ID to setup_ack
      ApiLineIdType id[2];
      id[0].ApiSubId = API_SUB_LINE_ID_EXT_LINE_ID;
      id[0].ApiLineValue.Value = CallState[HandsetId].LineId;
      id[1].ApiSubId = API_SUB_LINE_TYPE_INFO;
      id[1].ApiLineValue.Value = API_LINEID_INFO_NDT;
      ApiBuildInfoElement(&IeAckBlockPtr, &IeAckBlockLength, API_IE_LINE_ID, sizeof(id), (rsuint8*)&id);
    }
#ifndef RHEA
    if(CallState[HandsetId].State != HEADSET_INTERCEPT)
    { // do not send setupack if in  headset intercept
      SendApiFpCcSetupAckReq(COLA_TASK, HsId, API_CC_SIGNAL_DIAL_TONE_ON, API_IN_BAND_NOT_AVAILABLE, IeAckBlockLength, (rsuint8 *)IeAckBlockPtr);
    }
#endif
    ApiFreeInfoElement(&IeAckBlockPtr);


    if(CallState[HandsetId].State == HEADSET_INTERCEPT)
    {
      ApiCodecListType TempCodecList;
      TempCodecList.NegotiationIndicator = API_NI_POSSIBLE;
      TempCodecList.NoOfCodecs = 1;

      switch(LineSimGetPcmDataFormat(CallState[HandsetId].LineId))
      {
        case AP_DATA_FORMAT_LINEAR_8kHz: //0x01
          TempCodecList.Codec[0] = CodecG726;
          ApiPutCodecListInIe(&TempCodecList,
                              &IeConBlockPtr,
                              &IeConBlockLength);
          break;

        case AP_DATA_FORMAT_LINEAR_16kHz: //0x02
          TempCodecList.Codec[0] = CodecG722;
          ApiPutCodecListInIe(&TempCodecList,
                             &IeConBlockPtr,
                              &IeConBlockLength);
          break;
      }
    }
#ifdef RHEA
    //add API_IE_SYSTEM_CALL_ID setup_ack
    ApiBuildInfoElement(&IeConBlockPtr, &IeConBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&CallState[HandsetId].ApiSystemCallId);

    { //add API_IE_CALL_STATUS to setup_ack
      ApiCallStatusType tempCallStatus;
      tempCallStatus.CallStatusSubId = API_SUB_CALL_STATUS;
      tempCallStatus.CallStatusValue.State = API_CSS_CALL_CONNECT;
      ApiBuildInfoElement(&IeConBlockPtr, &IeConBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusType), (rsuint8*)&tempCallStatus);
    }
    {
      // add selected codec to setup_ack_req (to support Siemens Gigaset)
      codecList.NegotiationIndicator = API_NI_POSSIBLE;
      codecList.NoOfCodecs = 1;
      codecList.Codec[0] = LineSimGetSelectedCodec(LineId);
    }
    ApiPutCodecListInIe(&codecList, &IeConBlockPtr, &IeConBlockLength);
#endif
    // send connect_req without codec list (already send in setup_ack_req)
    SendApiFpCcConnectReq(COLA_TASK, HsId, IeConBlockLength, (rsuint8*)IeConBlockPtr);
    ApiFreeInfoElement(&IeConBlockPtr);
  }
  else
  {
    //Unsupported codec, release call
    LineSimRelease(LineId);
    CfSetCallState(HandsetId, F00_NULL);
    StopDelayAudioOpenTimer(LineId);
    SendApiFpSetAudioFormatReq(COLA_TASK, LineId, AP_DATA_FORMAT_NONE);  // close audio
    SendApiFpCcReleaseReq(COLA_TASK,  HsId, API_RR_UNEXPECTED_MESSAGE, 0, NULL);
  }
}

/****************************************************************************
* FUNCTION:      CallCtrlMailHandler
* DESCRIPTION:
****************************************************************************/
void CallCtrlMailHandler( RosMailType* p_Mail)
{
  switch (p_Mail->Primitive)
  {
    case API_FP_CC_SETUP_CFM: ApiFpCcSetupCfm((ApiFpCcSetupCfmType *)p_Mail); break;
    case API_FP_CC_SETUP_IND: ApiFpCcSetupInd((ApiFpCcSetupIndType*)p_Mail); break;
    case API_FP_CC_CALL_PROC_CFM: ApiFpCcCallProcCfm((ApiFpCcCallProcCfmType *)p_Mail); break;
    case API_FP_CC_ALERT_IND: ApiFpCcAlertInd((ApiFpCcAlertIndType *)p_Mail); break;
    case API_FP_CC_CONNECT_IND: ApiFpCcConnectInd((ApiFpCcConnectIndType *)p_Mail); break;
    case API_FP_CC_CONNECT_CFM: ApiFpCcConnectCfm((ApiFpCcConnectCfmType *)p_Mail); break;
    case API_FP_CC_REJECT_IND: ApiFpCcRejectInd((ApiFpCcRejectIndType *)p_Mail); break;
    case API_FP_CC_RELEASE_IND: ApiFpCcReleaseInd((ApiFpCcReleaseIndType *)p_Mail); break;
    case API_FP_CC_RELEASE_CFM: ApiFpCcReleaseCfm((ApiFpCcReleaseCfmType *)p_Mail); break;

  }
}

/****************************************************************************
* FUNCTION:      SendHsLocator
* DESCRIPTION:   Handset Paging
****************************************************************************/
void SendHsLocator(void)
{
  rsuint8 i;
  ApiCallReferenceType HsId;
  ApiInfoElementType *IeBlockPtr = NULL;
  rsuint16 IeBlockLength = 0;
  ApiLineIdType id;
  //ApiCodecListType codecList = {1,1,{{2,0,0,4}}};
  rsuint8 name[14] = {'H','A','N','D','S','E','T',' ','L','O','C','A','T','E'};
  rsuint8 CallingNameLength = sizeof(ApiCallingNameType)+14;
  ApiCallingNameType *CallingName = (ApiCallingNameType *)RcHeapAllocEx(CallingNameLength, RHF_NULL_ON_FULL);
  #ifdef NATALIE_V11
  ApiFpCcAudioIdType AudioId = {API_IEA_INT, 0, 0};
#endif
  CallingName->UsedAlphabet = AUA_DECT;
  CallingName->PresentationInd = API_PRESENTATION_HANSET_LOCATOR;
  CallingName->NameLength = 14;
  //CallingName->Name[0] = 'H';
  util_memcpy((void*)(CallingName->Name), (void*)&name, 14);


  //if needed wake up protocol from No emission mode
  //NoEmissionWakeUp();

  ApiBuildInfoElement( &IeBlockPtr,
                       &IeBlockLength,
                       API_IE_CALLING_PARTY_NAME,
                       CallingNameLength,
                       (rsuint8*)CallingName);

  RcHeapFreeEx(CallingName, RHF_NULL_ON_FULL);


  id.ApiSubId = API_SUB_LINE_ID_EXT_LINE_ID;
  id.ApiLineValue.Value = 0x7F;

  ApiBuildInfoElement(&IeBlockPtr,
                      &IeBlockLength,
                      API_IE_LINE_ID,
                      sizeof(ApiLineIdType),
                      (rsuint8*)&id);

  { //add API_IE_CALL_STATUS to setup_ack
    ApiCallStatusType tempCallStatus;
    tempCallStatus.CallStatusSubId = API_SUB_CALL_STATUS;
    tempCallStatus.CallStatusValue.State = API_CSS_CALL_SETUP;
    ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusType), (rsuint8*)&tempCallStatus);
  }

  for (i=0; i<NO_HANDSETS; i++)
  {
#ifdef NATALIE_V11
	  HsId.Value = 0;//No need to identify calls in HS locating
#else
    HsId.HandsetId = i;
#endif

    switch (CallState[i].State)
    {
      case F00_NULL:
        CfSetCallState(i, HANDSET_LOCATE);
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
                            0,
                            API_CC_SIGNAL_ALERT_ON_PATTERN_0_INT,
                            IeBlockLength,
                            (rsuint8*)IeBlockPtr);
#endif
        break;

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
    }
  }

  ApiFreeInfoElement(&IeBlockPtr);
}

/****************************************************************************
* FUNCTION:      StopHsLocating
* DESCRIPTION:   stop Handset paging
****************************************************************************/
void StopHsLocating(void)
{
  rsuint8 i;
  ApiCallReferenceType HsId;

  for (i=0; i<NO_HANDSETS; i++)
  {
    if (CallState[i].State == HANDSET_LOCATE)
    {
#ifdef NATALIE_V11
    	HsId.Value = 0;//i;
#else
      HsId.HandsetId = i;
#endif
      SendApiFpCcReleaseReq(COLA_TASK, HsId, API_RR_NORMAL,0 ,NULL);
      CfSetCallState(i, F00_NULL);
    }
  }
}

/****************************************************************************
* FUNCTION:      CheckPagingMode
* DESCRIPTION:   check whether there are any handset in paging mode
****************************************************************************/
rsbool CheckPagingMode(void)
{
  rsuint8 i;

  for (i=0; i<NO_HANDSETS; i++)
  {
    if (CallState[i].State == HANDSET_LOCATE)
    {
      return TRUE;
    }
  }
  return FALSE;
}
// End of file.
