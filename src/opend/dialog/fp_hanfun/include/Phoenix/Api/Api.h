/*
 * Copyright (c) by RTX A/S, Denmark
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of RTX A/S nor the names of its contributors
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

#ifndef API_H      
#define API_H      


//#define PHOENIX_API_FP_CODECLIST
#define PHOENIX_API_CODECLIST
#define NUMBER_OF_CODEC_LIST_ENTRIES 2
#ifndef RSOFFSETOF
  /*! \def RSOFFSETOF(type, field)
  * Computes the byte offset of \a field from the beginning of \a type. */
  #define RSOFFSETOF(type, field) ((size_t)(&((type*)0)->field))
#endif
#define SEND_API_FP_CC_SELECTED_ADPCM_IND
/****************************************************************************
*                               Include files                                 
****************************************************************************/
//System files
//#include <linux-2.6.x/include/linux/autoconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Phoenix files
#include <Phoenix/Api/RsList.h>
#include <Phoenix/Api/Linux/ApiLinux.h>
//#include <Phoenix/FpProject/ApiFpProject.h>
#include <Phoenix/Api/FpGeneral/ApiFpGeneral.h>
#include <Phoenix/Api/FpAudio/ApiFpAudio.h>
#include <Phoenix/Api/FpMm/ApiFpMm.h>
#include <Phoenix/Api/FpFwu/ApiFpFwu.h>
#include <Phoenix/Api/FpCc/ApiFpCc.h>
#include <Phoenix/Api/FpNoEmission/ApiFpNoEmission.h>
#include <Phoenix/Api/Las/ApiLas.h>
#include <Phoenix/Api/LasDb/ApiLasDb.h>
#include <Phoenix/Api/GenEveNot/ApiGenEveNot.h>
//#include <FpApp/cvmcon.h>

/****************************************************************************
*                               External                              
****************************************************************************/
extern unsigned char* (*BUSM_AllocateMail_fptr)(unsigned char uProgramId, unsigned char uTaskId, unsigned short u16Size);
extern void (*BUSM_DeliverMail_fptr)(unsigned char *Mail);
void Register_AllocateMailFunction(void *func_ptr);
void Register_DeliverMailFunction(void *func_ptr);

/****************************************************************************
*                               Defines and macros                                 
****************************************************************************/
//Debugging
#define PRINT_PH_MSG(args...) // printf(args)

//#define PHOENIX_API_FP_CODECLIST
#define PHOENIX_API_CODECLIST
#define NUMBER_OF_CODEC_LIST_ENTRIES 2
#ifndef RSOFFSETOF
  /*! \def RSOFFSETOF(type, field)
  * Computes the byte offset of \a field from the beginning of \a type. */
  #define RSOFFSETOF(type, field) ((size_t)(&((type*)0)->field))
#endif
#ifndef CATIQ_V1
	#define USER_TASK        		0x01 //0x0F // for standard API calls
	#define APILAS_TASK      		0x01
	#define CVMAPI_TASK      		0x01
	#define APIFPMM_TASK      		0x01
	#define APIFPCC_TASK      		0x01
	#define APIFPNOEMISSION_TASK    0x01
	#define APIFPGENERAL_TASK 		0x01
	#define APIFPPROJECT_TASK      	0x01
	#define APIGENEVENOT_TASK      	0x01
	#define FP_APP_TASK      		0x01
	#define APIFPAUDIO_TASK			0x01
	#define APISUOTA_TASK			0x01
	#define APIFPULE_TASK			0x01
	#define APILDS_TASK				0x01
	#define APILASDB_TASK			0x01
	#define APIHAL_TASK				0x01
	#define APIFPFWU_TASK			0x01
	#define APILINUX_TASK			0x01
	#define APIPRODTEST_TASK 		0x01
	#define APIFPLLME_TASK	 		0x01

//#ifdef HOST_MSG_QUEUE
	#define APIHOST_TASK	      	0x20 //This is for handling locally messages in the host (e.g from SIP application)
	#define APISIP_TASK	      	    0x21
//#endif
	#define RosMailAllocate(x, y, z) (BUSM_AllocateMail_fptr(x, y, z))
	#define RosMailDeliver(x) (BUSM_DeliverMail_fptr((uint8*)x))
//	#define RosMailType uint8

//#define PROJCFG_NUMBER_OF_SUBSCRIPTIONS 0x06

//Added by sitel
//	#define GET_FIRST_AVAILABLE_LINE
//	#define CALLS_PER_LINE 2 //ONLY values 1 and 2 are supported !!!!
//#ifndef RSOFFSETOF
//  /*! \def RSOFFSETOF(type, field)
//  * Computes the byte offset of \a field from the beginning of \a type. */
//  #define RSOFFSETOF(type, field) ((size_t)(&((type*)0)->field))
//#endif
#else
	//#define USER_TASK      0x0F // for standard API calls
#endif

#define LS_NO_LINES 9//8 lines + 1 for intercom 4
typedef union
{
  PrimitiveType Primitive;
  ApiLinuxInitReqType ApiLinuxInitReq;
  ApiLinuxInitCfmType ApiLinuxInitCfm;
  ApiLinuxNvsUpdateIndType ApiLinuxNvsUpdateInd;
//  ApiFpLinuxNvsUpdateResType ApiFpLinuxNvsUpdateRes;
  ApiFpResetReqType ApiFpResetReq;
  ApiFpResetIndType ApiFpResetInd;
  ApiFpGetFwVersionReqType ApiFpGetFwVersionReq;
  ApiFpGetFwVersionCfmType ApiFpGetFwVersionCfm;
  //ApifpprojectEmptySignalType ApiFpGetIdReq;
  ApiFpMmGetIdCfmType ApiFpMmGetIdCfm;
  ApiFpMmSetAccessCodeReqType ApiFpMmSetAccessCodeReq;
  ApiFpMmSetAccessCodeCfmType ApiFpMmSetAccessCodeCfm;
  ApiFpMmGetAccessCodeReqType ApiFpMmGetAccessCodeReq;
  ApiFpMmGetAccessCodeCfmType ApiFpMmGetAccessCodeCfm;
  //ApiFpSetEepromReqType ApiFpSetEepromReq;
  //ApiFpSetEepromCfmType ApiFpSetEepromCfm;
  //ApiFpGetEepromReqType ApiFpGetEepromReq;
  //ApiFpGetEepromCfmType ApiFpGetEepromCfm;
  ApiFpMmGetRegistrationCountReqType ApiFpMmGetRegistrationCountReq;
  ApiFpMmGetRegistrationCountCfmType ApiFpMmGetRegistrationCountCfm;
  ApiFpMmDeleteRegistrationReqType ApiFpMmDeleteRegistrationReq;
  ApiFpMmDeleteRegistrationCfmType ApiFpMmDeleteRegistrationCfm;
 // ApiFpMmRegistrationDeletedIndType ApiFpMmRegistrationDeletedInd;
  ApiFpMmSetRegistrationModeReqType ApiFpMmSetRegistrationModeReq;
  ApiFpMmSetRegistrationModeCfmType ApiFpMmSetRegistrationModeCfm;
  ApiFpMmRegistrationCompleteIndType ApiFpMmRegistrationCompleteInd;
  ApiFpMmHandsetPresentIndType ApiFpMmHandsetPresentInd;
  ApiFpMmGetHandsetIpuiReqType ApiFpMmGetHandsetIpuiReq;
  ApiFpMmGetHandsetIpuiCfmType ApiFpMmGetHandsetIpuiCfm;
  ApiFpCcSetupIndType ApiFpCcSetupInd;
  ApiFpCcSetupResType ApiFpCcSetupRes;
  ApiFpCcSetupReqType ApiFpCcSetupReq;
  ApiFpCcSetupCfmType ApiFpCcSetupCfm;
  ApiFpCcSetupAckReqType ApiFpCcSetupAckReq;
  ApiFpCcSetupAckCfmType ApiFpCcSetupAckCfm;
  ApiFpCcAlertIndType ApiFpCcAlertInd;
  ApiFpCcAlertReqType ApiFpCcAlertReq;
  ApiFpCcAlertCfmType ApiFpCcAlertCfm;
  ApiFpCcConnectIndType ApiFpCcConnectInd;
  ApiFpCcConnectResType ApiFpCcConnectRes;
  ApiFpCcConnectReqType ApiFpCcConnectReq;
  ApiFpCcConnectCfmType ApiFpCcConnectCfm;
//  ApiFpSignalReqType ApiFpSignalReq;
//  ApiFpSignalCfmType ApiFpSignalCfm;
//  ApiFpSendClipReqType ApiFpSendClipReq;
//  ApiFpSendClipCfmType ApiFpSendClipCfm;
  ApiFpCcReleaseIndType ApiFpCcReleaseInd;
  ApiFpCcReleaseResType ApiFpCcReleaseRes;
  ApiFpCcReleaseReqType ApiFpCcReleaseReq;
  ApiFpCcReleaseCfmType ApiFpCcReleaseCfm;
  ApiFpCcRejectIndType ApiFpCcRejectInd;
//  ApiFpMultikeypadIndType ApiFpMultikeypadInd;
//  ApiFpCallProcReqType ApiFpCallProcReq;
//  ApiFpCallProcCfmType ApiFpCallProcCfm;
//  ApiFpIwuToIwuReqType ApiFpIwuToIwuReq;
//  ApiFpIwuToIwuCfmType ApiFpIwuToIwuCfm;
//  ApiFpIwuToIwuIndType ApiFpIwuToIwuInd;
//  ApiFpProprietaryReqType ApiFpProprietaryReq;
//  ApiFpProprietaryCfmType ApiFpProprietaryCfm;
//  ApiFpProprietaryIndType ApiFpProprietaryInd;
  ApiFpCcModifyCodecReqType ApiFpCcModifyCodecReq;
  ApiFpCcModifyCodecCfmType ApiFpCcModifyCodecCfm;
  ApiFpCcModifyCodecIndType ApiFpCcModifyCodecInd;
  ApiFpCcModifyCodecResType ApiFpCcModifyCodecRes;
  ApiFpCcIwuInfoCodecIndType ApiFpCcIwuInfoCodecInd;
//  ApiFpCalledNumberIndType ApiFpCalledNumberInd;
  ApiFpCcInfoIndType ApiFpCcInfoInd;
#if 0 //cvm
  ApiFpFwuDeviceNotifyIndType ApiFpFwuDeviceNotifyInd;
  ApiFpFwuUpdateCfmType ApiFpFwuUpdateCfm;
  ApiFpFwuStatusIndType ApiFpFwuStatusInd;
  ApiFpFwuUpdateIndType ApiFpFwuUpdateInd;
  ApiFpFwuGetCrcIndType ApiFpFwuGetCrcInd;  
  ApiFpSetLedReqType ApiFpSetLedReq;
  ApiFpSetLedCfmType ApiFpSetLedCfm;
  ApiFpInitPcmReqType ApiFpInitPcmReq;
  ApiFpInitPcmCfmType ApiFpInitPcmCfm;  
  ApiFpSetPcmCodecReqType ApiFpSetPcmCodecReq;
  ApiFpSetPcmCodecCfmType ApiFpSetPcmCodecCfm;  
  ApiFpSetRegisterReqType ApiFpSetRegisterReq;
  ApiFpSetRegisterCfmType ApiFpSetRegisterCfm;
  ApiFpGetRegisterReqType ApiFpGetRegisterReq;
  ApiFpGetRegisterCfmType ApiFpGetRegisterCfm;  
#endif  
} PACKED_STRUCT Sip450ApiMailType;

   
#endif

