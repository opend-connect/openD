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

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Api/ApiCfg.h>

#ifdef AUTOTEST
  #include <Tools/AutoTest/AutoTest.h>
#endif


#if defined(PHOENIX_API_CC) || defined(PHOENIX_API_FP_UT_CC)
  #include <Phoenix/Api/Cc/ApiCc.h>
#endif

#ifdef PHOENIX_API_FP_GENERAL
  #include <Phoenix/Api/FpGeneral/ApiFpGeneral.h>
#endif

#ifdef PHOENIX_API_FP_AUDIO
  #include <Phoenix/Api/FpAudio/ApiFpAudio.h>
#endif

#ifdef PHOENIX_API_AUDIO
  #include <Phoenix/Api/Audio/ApiAudio.h>
#endif


#ifdef PHOENIX_API_FP_MM
  #include <Phoenix/Api/FpMm/ApiFpMm.h>
#endif

#ifdef PHOENIX_API_FP_LLME
  #include <Phoenix/Api/FpLlme/ApiFpLlme.h>
#endif

#ifdef PHOENIX_API_FP_CC
  #include <Phoenix/Api/FpCc/ApiFpCc.h>
#endif

#ifdef PHOENIX_API_FP_NO_EMISSION
  #include <Phoenix/Api/FpNoEmission/ApiFpNoEmission.h>
#endif

#ifdef PHOENIX_API_PP_GENERAL
  #include <Phoenix/Api/PpGeneral/ApiPpGeneral.h>
#endif

#ifdef PHOENIX_API_PP_AUDIO
  #include <Phoenix/Api/PpAudio/ApiPpAudio.h>
#endif

#ifdef PHOENIX_API_PP_BATTERY
  #include <Phoenix/Api/PpBattery/ApiPpBattery.h>
#endif

#ifdef PHOENIX_API_PP_MM
  #include <Phoenix/Api/PpMm/ApiPpMm.h>
#endif

#ifdef PHOENIX_API_LAS
  #include <Phoenix/Api/Las/ApiLas.h>

#ifdef PHOENIX_API_LASDB // This API needs PHOENIX_API_LAS to be enabled !
  #include <Phoenix/Api/LasDb/ApiLasDb.h>
#endif
#endif

#ifdef PHOENIX_API_PP_NO_EMISSION
  #include <Phoenix/Api/PpNoEmission/ApiPpNoEmission.h>
#endif

#ifdef PHOENIX_API_GENEVENOT
  #include <Phoenix/Api/GenEveNot/ApiGenEveNot.h>
#endif

#ifdef PHOENIX_API_PROD_TEST
  #include <Phoenix/Api/ProdTest/ApiProdTest.h>
#endif

#ifdef PHOENIX_API_SMS
  #include <Phoenix/Api/Sms/ApiSms.h>
#endif

#ifdef PHOENIX_API_FP_PROJECT
  #include <Api/ApiFpProject.h>
#endif

#ifdef PHOENIX_API_PP_PROJECT
  #include <Api/ApiPpProject.h>
#endif

#ifdef PHOENIX_API_IMAGECONTROL
  #include <Phoenix/Api/ImageControl/ApiImageControl.h>
#endif

#ifdef PHOENIX_API_PP_SS
  #include <Phoenix/Api/PpSs/ApiPpSs.h>
#endif

#ifdef PHOENIX_API_FP_SS
  #include <Phoenix/Api/FpSs/ApiFpSs.h>
#endif

#ifdef PHOENIX_API_HAL
  #include <Phoenix/Api/HAL/ApiHAL.h>
#endif

#ifdef PHOENIX_API_PP_ULE
  #include <Phoenix/Api/PpUle/ApiPpUle.h>
#endif

#if defined PHOENIX_API_FP_ULE || defined PHOENIX_API_FP_ULP
  #include <Phoenix/Api/FpUle/ApiFpUle.h>
#endif

#ifdef PHOENIX_API_LDS
  #include <Phoenix/Api/Lds/ApiLds.h>
#endif

#ifdef PHOENIX_API_PP2PP
  #include <Phoenix/Api/Pp2Pp/ApiPp2Pp.h>
#endif

#ifdef PHOENIX_API_SUOTA
  #include <Phoenix/Api/Suota/ApiSuota.h>
#endif

#ifdef PHOENIX_API_SCL
  #include <Phoenix/Api/SCL/ApiScl.h>
#endif

#ifdef PHOENIX_API_CODECLIST
  #include <Phoenix/Api/CodecList/ApiCodecList.h>
#endif

#ifdef PHOENIX_API_LINUX
  #include <Phoenix/Api/Linux/ApiLinux.h>
#endif

#ifdef PHOENIX_API_LED
  #include <Phoenix/Api/LED/ApiLed.h>
#endif

#ifdef PHOENIX_API_HEADSET
  #include <Phoenix/Api/Headset/ApiHeadset.h>
#endif

#ifdef PHOENIX_API_CLSS
  #include <Phoenix/Api/Clss/ApiClss.h>
#endif

#ifdef PHOENIX_API_NVSMAP
  #include <Phoenix/Api/NvsMap/ApiNvsMap.h>
#endif

#ifdef PHOENIX_API_USB
  #include <Phoenix/Api/Usb/ApiUsb.h>
#endif

#ifdef PHOENIX_API_PSAPP
  #include <Phoenix/Api/PsApp/ApiPsApp.h>
#endif

#ifdef PHOENIX_API_PP_MIC
  #include <Phoenix/Api/PpMic/ApiPpMic.h>
#endif

#ifdef PHOENIX_API_FP_MIC
  #include <Phoenix/Api/FpMic/ApiFpMic.h>
#endif

#ifdef PHOENIX_API_ISP
  #include <Isp/Api/ApiIsp.h>
#endif

#ifdef PHOENIX_API_FP_FWU
  #include <FWU/Api/ApiFwu.h>
#endif

#ifdef PHOENIX_API_FWS
  #include <FWU/ApiFws/ApiFws.h>
#endif

//Type definitions

//Framework/Kernel

//Interfaces

//Configurations

//Private

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#if RS_ENDIAN_TYPE == RS_BIG_ENDIAN
#define API_ENDIAN_HANDLER
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


/****************************************************************************
*                           Global variables/const
****************************************************************************/
#ifdef PHOENIX_API_FP_UT_CC
  extern RosTaskIdType ApiDstTask;
#endif



/****************************************************************************
*                             Function prototypes
****************************************************************************/

#ifdef PHOENIX_API_FP_PROJECT_HANDLER // For Platform / project specific API handling
  void ApiFpProjectHandler(const RosMailType* MailPtr);
#endif

#ifdef PHOENIX_API_PP_PROJECT_HANDLER // For Platform / project specific API handling
  void ApiPpProjectHandler(const RosMailType* MailPtr);
#endif


// The following functions must be implemented in ApiCfg:
#if defined(PHOENIX_API_PP_GENERAL) || defined(PHOENIX_API_FP_GENERAL)
  ApiDectTypeType ApiCfgGetDectType(void);
  rsuint32 ApiCfgGetVersionHexFormat(void);
  rsuint8* ApiCfgGetLinkDate(void);
  ApiCradleStatusType ApiCfgGetCradleStatus(void);
  rsuint8 ApiCfgGetModic(void);
#endif

#ifdef PHOENIX_API_PP_MM
rsbool GetApiPpMmLockedState(void);
#endif

#ifdef API_ENDIAN_HANDLER
void ApiEndianComHandler(rsuint8 *MailPtr, rsbool FromTargetEndian);
#endif

#endif

