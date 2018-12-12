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
#include <Phoenix/Api/Api.h>
#include "LedCtrl.h"
#include "system.h"
#include "CfState.h"
#include "MmiCtrl.h"
#include "ApiHelper.h"
#include "Util.h"


/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/
static MmiInstanceType MmiInstance;

/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
void MmiCcSetupIndGetCallCtrlPara( ApiCcSetupIndType *p_Mail )
{
  pCfSysCtrl->PpSysPara.CallCtrlPara.ConEi              = p_Mail->ConEi;
  pCfSysCtrl->PpSysPara.CallCtrlPara.BasicService       = p_Mail->BasicService;
  pCfSysCtrl->PpSysPara.CallCtrlPara.CallClass          = p_Mail->CallClass;

  // MmiHandleStorePreferredCodec(p_Mail->InfoElement, p_Mail->InfoElementLength);
}


void MmiShowLedStatus(void)
{
  // rsuint8 i;

  switch(pCfSysCtrl->CfStateCtrl.CfState)
  {
    case CF_STATE_INIT:
      printf("## Init\n");
      break;

    case CF_STATE_STANDBY:
      printf("## Standby\n");
      break;

    case CF_STATE_UNLOCKED:
      printf("## Unlocked state\n");
      break;

    case CF_STATE_ALERTING:
      printf("## Alerting state\n");
      break;

    case CF_STATE_REGISTRATION:
      printf("## Registration\n");
      break;

    case CF_STATE_CONNECTING:
      printf("## Connecting\n");
      break;

    case CF_STATE_CONNECTED:
      printf("## Connected\n");
      break;

  }

}

/****************************************************************************
* Name   : PpMmiBuildG722CodecListInIE
* Input  : Pointer to an infoelemenet block and it's length
* Output :
*----------------------------------------------------------------------------
* Usage  : Builds a Wideband codec list and puts it in an info element block
*          According to CAT-iq Specification a CAT-iq PP should always offer
*          at least 2 codec options, including G.722+G.726
*****************************************************************************/
void PpMmiBuildG722CodecListInIE(rsuint16 *IeBlockLength, ApiInfoElementType **IeBlockPtr)
{
  //Build codec list with G.722 codec+G.726 codec
  ApiCodecListType *CodecListPtr = NULL;
  ApiCodecInfoType *CodecInfoPtr  = RcHeapAllocEx(sizeof(ApiCodecInfoType), RHF_NULL_ON_FULL);

  CodecInfoPtr->Codec             = API_CT_G722;
  CodecInfoPtr->MacDlcService     = API_MDS_1_MD;
  CodecInfoPtr->CplaneRouting     = API_CPR_CS;
  CodecInfoPtr->SlotSize          = API_SS_LS640;

  ApiBuildCodecListHeader(&CodecListPtr, API_NI_POSSIBLE);
  //Put codec from CodecInfo pointer in codec list
  ApiAddToCodecList(&CodecListPtr, CodecInfoPtr);

  CodecInfoPtr->Codec             = API_CT_G726;
  CodecInfoPtr->MacDlcService     = API_MDS_1_MD;
  CodecInfoPtr->CplaneRouting     = API_CPR_CS;
  CodecInfoPtr->SlotSize          = API_SS_FS;

  //Put codec from CodecInfo pointer in codec list
  ApiAddToCodecList(&CodecListPtr, CodecInfoPtr);

  //Put codec list in Info element
  ApiPutCodecListInIe(CodecListPtr, IeBlockPtr, IeBlockLength);
  //Free codec list since it is now located in Info element block
  ApiFreeCodecList(&CodecListPtr);

  RcHeapFreeEx(CodecInfoPtr, RHF_NULL_ON_FULL);
}

/****************************************************************************
* Name   : HandleConnectReq
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  : Send a connect request with codec of either Narrowband or wideband,
*****************************************************************************/
void HandleConnectReq(void)
{
  ApiInfoElementType *IeBlockPtr = NULL;
  rsuint16 IeBlockLength = 0;

  if(pCfSysCtrl->PpSysPara.CallCtrlPara.MmiPreferredCodec != API_CT_NONE)
  {
    switch(pCfSysCtrl->PpSysPara.CallCtrlPara.MmiPreferredCodec)                //for simplicity only handle WB and NB audio
    {
      case API_CT_G722:
        PpMmiBuildG722CodecListInIE(&IeBlockLength, &IeBlockPtr);
        break;
    }
  }
  else
  {
    //If basic Service in setup_ind is set to BASIC_SPEECH narrow band should always be used, thus disregard any codec list and dont send any codec list
    if (pCfSysCtrl->PpSysPara.CallCtrlPara.BasicService != API_BASIC_SPEECH)
    {
      PpMmiBuildG722CodecListInIE(&IeBlockLength, &IeBlockPtr);
    }
  }

  //Send connec request
  SendApiCcConnectReq ( COLA_TASK,                                              //RosTaskIdType Src,
                        pCfSysCtrl->PpSysPara.CallCtrlPara.ConEi,               //ApiCcConEiType ConEi,
                        IeBlockLength,                                          //rsuint16 InfoElementLength,
                        (void *)IeBlockPtr );                                   //rsuint8 InfoElement[1])

  //Free info element
  ApiFreeInfoElement(&IeBlockPtr);

  CfEnterState(CF_STATE_CONNECTED);
}

/***************************************************************************
* Name   : MmiHandleIntCallingPartyNumber
* Input  : Pointer to Infoelements and the length of this
* Output :
*----------------------------------------------------------------------------
* Usage  :  Check and store Calling Handset Id
*****************************************************************************/
void MmiHandleIntCallingPartyNumber(rsuint8 *InfoElement, rsuint16 InfoElementLength)
{
  ApiInfoElementType *pIe;
  ApiCallingNumberType *pApiCallingNumber;
  rsuint8 HsNo;

  // check if infoelement is present
  if (InfoElement != NULL && InfoElementLength != 0)
  {
    pIe = ApiGetInfoElement((ApiInfoElementType *)InfoElement,
                            InfoElementLength,
                            API_IE_CALLING_PARTY_NUMBER);
    if (pIe != NULL)
    {
      pApiCallingNumber = (ApiCallingNumberType*)(pIe->IeData);

      HsNo=pApiCallingNumber->Number[0]-IA5_DIGIT_0;

      if(pApiCallingNumber->NumberLength==1
        &&pApiCallingNumber->NumberType==ANT_NETWORK_SPECIFIC
        &&pApiCallingNumber->Npi==ANPI_PRIVATE
        &&pApiCallingNumber->PresentationInd==API_PRESENTATION_ALLOWED
        &&pApiCallingNumber->ScreeningInd==API_USER_PROVIDED_VERIFIED_PASSED
        &&HsNo<NO_HANDSETS
        &&HsNo>0
        &&HsNo!=pCfSysCtrl->PpSysPara.PpMmiPara.HandsetId)                      //checking whether this is a valid Calling Handset ID
      {
        pCfSysCtrl->PpSysPara.DestHsId = HsNo;
      }
    }
  }
}

/****************************************************************************
* Name   : SetupIntOutgoingCall
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  : sets up intercom call (default using WB audio)
*****************************************************************************/
void SetupIntOutgoingCall( ApiCcConEiType MmiConEi, rsuint8 DestHsId )
{
  //setup internal call with callclass WidebandBand voice, and attach a codec list
  ApiInfoElementType *IeBlockPtr = NULL;
  rsuint16 IeBlockLength = 0;
  rsuint8 MmiDialDigitBuffer[1];

  //use wideband by default
  pCfSysCtrl->PpSysPara.CallCtrlPara.ConEi = MmiConEi;
  pCfSysCtrl->PpSysPara.CallCtrlPara.BasicService = API_WIDEBAND_SPEECH;
  pCfSysCtrl->PpSysPara.CallCtrlPara.CallClass = API_CC_INTERNAL;
  pCfSysCtrl->PpSysPara.CallCtrlPara.MmiPreferredCodec = API_CT_G722;

  PpMmiBuildG722CodecListInIE(&IeBlockLength, &IeBlockPtr);

  MmiDialDigitBuffer[0]=DestHsId+'0';

  ApiBuildInfoElement(&IeBlockPtr,
                      &IeBlockLength,
                      API_IE_MULTIKEYPAD,
                      1,
                      (rsuint8*)MmiDialDigitBuffer);

  SendApiCcSetupReq( COLA_TASK,                                                 //RosTaskIdType Src,
                     pCfSysCtrl->PpSysPara.CallCtrlPara.ConEi,                  //ApiCcConEiType ConEi,
                     pCfSysCtrl->PpSysPara.CallCtrlPara.BasicService,           //ApiCcBasicServiceType BasicService,
                     pCfSysCtrl->PpSysPara.CallCtrlPara.CallClass,              //ApiCcCallClassType CallClass,
                     IeBlockLength,                                             //rsuint16 InfoElementLength,
                     (rsuint8 *)IeBlockPtr);                                    //rsuint8 InfoElement[1])

  ApiFreeInfoElement(&IeBlockPtr);
}

/****************************************************************************
* Name   : SetupExtOutgoingCall
* Input  :
* Output :
*----------------------------------------------------------------------------
* Usage  : sets up external call
*          with selection of wideband/narrowband callclass
*****************************************************************************/
void SetupExtOutgoingCall( ApiCcConEiType MmiConEi, Ia5CharType pMultikeypad )
{
  //setup external call with callclass WidebandBand voice, and attach a codec list
  ApiInfoElementType *IeBlockPtr = NULL;
  rsuint16 IeBlockLength = 0;

  util_memset(&MmiInstance, 0, sizeof(MmiInstanceType));

  //use wideband by default
  MmiInstance.MmiBasicService = API_WIDEBAND_SPEECH;
  PpMmiBuildG722CodecListInIE(&IeBlockLength, &IeBlockPtr);
  MmiInstance.MmiCallClass = API_CC_NORMAL;       //normal external call

  // send setup_req
  {
    ApiLineIdType TempLineId;
    //If we are making an outgoing call from ContactList check for LineId
    TempLineId.ApiSubId = API_SUB_LINE_ID_EXT_LINE_ID;
    TempLineId.ApiLineValue.Value = API_LINEID_NONE;  // line id none

    // build API_IE_LINE_ID infoelement
    ApiBuildInfoElement(&IeBlockPtr,
                        &IeBlockLength,
                        API_IE_LINE_ID,
                        sizeof(ApiLineIdType),
                        (rsuint8*)&TempLineId);

    ApiBuildInfoElement(&IeBlockPtr,
                        &IeBlockLength,
                        API_IE_MULTIKEYPAD,
                        1U,
                        (rsuint8*)&pMultikeypad);

    SendApiCcSetupReq ( COLA_TASK,            //RosTaskIdType Src,
                        MmiConEi,             //ApiCcConEiType ConEi,
                        MmiInstance.MmiBasicService,      //ApiCcBasicServiceType BasicService,
                        MmiInstance.MmiCallClass,         //ApiCcCallClassType CallClass,
                        IeBlockLength,        //rsuint16 InfoElementLength,
                        (rsuint8 *)IeBlockPtr);  //rsuint8 InfoElement[1])
    //Remember to free the Info element block from heap;
    ApiFreeInfoElement(&IeBlockPtr);
  }
}

// End of file.

