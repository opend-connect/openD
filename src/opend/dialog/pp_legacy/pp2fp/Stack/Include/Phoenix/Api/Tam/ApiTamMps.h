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
#ifndef APITAMMPS_H
#define APITAMMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Tam/ApiTam.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiTamPlayIcmCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_PLAY_ICM_CFM= 0x4501
****************************************************************************/
void SendApiTamPlayIcmCfm ( RosTaskIdType Dst,
                            ApiTamErrorType ErrorCode);      /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamIcmSearchCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_ICM_SEARCH_CFM = 0x4503
****************************************************************************/
void SendApiTamIcmSearchCfm ( RosTaskIdType Dst,
                              ApiTamErrorType ErrorCode,     /*!<  */
                              ApiTamMsgNoType IcmNo);        /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamIcmStatusCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_ICM_STATUS_CFM = 0x4505
****************************************************************************/
void SendApiTamIcmStatusCfm ( RosTaskIdType Dst,
                              ApiTamErrorType ErrorCode,     /*!<  */
                              ApiTamIcmStatusType Status);   /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamDeleteIcmCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_DELETE_ICM_CFM = 0x4507
****************************************************************************/
void SendApiTamDeleteIcmCfm ( RosTaskIdType Dst,
                              ApiTamErrorType ErrorCode);    /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamStopCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_STOP_CFM = 0x4509
****************************************************************************/
void SendApiTamStopCfm ( RosTaskIdType Dst,
                         ApiTamErrorType ErrorCode);         /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamMarkCurrentIcmCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_MARK_CURRENT_ICM_CFM = 0x450B
****************************************************************************/
void SendApiTamMarkCurrentIcmCfm ( RosTaskIdType Dst,
                                   ApiTamErrorType ErrorCode);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamStatusInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_STATUS_IND = 0x450C
****************************************************************************/
void SendApiTamStatusInd ( RosTaskIdType Dst,
                           rsbool TamOn,                     /*!<  */
                           rsbool TamFull,                   /*!<  */
                           rsbool NewMsgs);                  /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamRecordMemoCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_RECORD_MEMO_CFM = 0x450E
****************************************************************************/
void SendApiTamRecordMemoCfm ( RosTaskIdType Dst,
                               ApiTamErrorType ErrorCode);   /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamRecordVoicetagCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_RECORD_VOICETAG_CFM = 0x4510
****************************************************************************/
void SendApiTamRecordVoicetagCfm ( RosTaskIdType Dst,
                                   ApiTamErrorType ErrorCode);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamPlayVoicepromptCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_PLAY_VOICEPROMPT_CFM= 0x4512
****************************************************************************/
void SendApiTamPlayVoicepromptCfm ( RosTaskIdType Dst,
                                    ApiTamErrorType ErrorCode);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamPlayVoicetagCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_PLAY_VOICETAG_CFM = 0x4514
****************************************************************************/
void SendApiTamPlayVoicetagCfm ( RosTaskIdType Dst,
                                 ApiTamErrorType ErrorCode);  /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamDeleteVoicetagCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_DELETE_VOICETAG_CFM = 0x4516
****************************************************************************/
void SendApiTamDeleteVoicetagCfm ( RosTaskIdType Dst,
                                   ApiTamErrorType ErrorCode);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamSetSettingsCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_SET_SETTINGS_CFM = 0x4518
****************************************************************************/
void SendApiTamSetSettingsCfm ( RosTaskIdType Dst,
                                ApiTamErrorType ErrorCode,   /*!<  */
                                ApiTamSettingsType TamSettings);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamGetSettingsCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_GET_SETTINGS_CFM = 0x451A
****************************************************************************/
void SendApiTamGetSettingsCfm ( RosTaskIdType Dst,
                                ApiTamErrorType ErrorCode,   /*!<  */
                                ApiTamSettingsType TamSettings);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamSetSystemSettingsCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_SET_SYSTEM_SETTINGS_CFM = 0x451C
****************************************************************************/
void SendApiTamSetSystemSettingsCfm ( RosTaskIdType Dst,
                                      ApiTamErrorType ErrorCode,
                                                             /*!<  */
                                      ApiTamSystemSettingsType TamSystemSettings);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamGetSystemSettingsCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_GET_SYSTEM_SETTINGS_CFM = 0x451E
****************************************************************************/
void SendApiTamGetSystemSettingsCfm ( RosTaskIdType Dst,
                                      ApiTamErrorType ErrorCode,
                                                             /*!<  */
                                      ApiTamSystemSettingsType TamSystemSettings);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamReadDataCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_READ_DATA_CFM = 0x4520
****************************************************************************/
void SendApiTamReadDataCfm ( RosTaskIdType Dst,
                             ApiTamDataTaskErrorType Result,  /*!<  */
                             rsuint8 Length,                 /*!<  */
                             rsuint8 Data[1]);               /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamWriteDataCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_WRITE_DATA_CFM= 0x4522
****************************************************************************/
void SendApiTamWriteDataCfm ( RosTaskIdType Dst,
                              ApiTamDataTaskErrorType Result);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamDeleteAllIcmsCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_DELETE_ALL_ICMS_CFM= 0x4524
****************************************************************************/
void SendApiTamDeleteAllIcmsCfm ( RosTaskIdType Dst,
                                  ApiTamErrorType ErrorCode);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamReleaseCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_RELEASE_CFM = 0x4527	
****************************************************************************/
void SendApiTamReleaseCfm ( RosTaskIdType Dst,
                            ApiCcConEiType	 MmiConEi,        /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                            rsuint16 InfoElementLength,      /*!< The length of the Data
                                                                Information Element */
                            rsuint8 InfoElement[1]);         /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_RP_TAM] */

/****************************************************************************
* FUNCTION:      SendApiTamConnectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_CONNECT_IND = 0x4528
****************************************************************************/
void SendApiTamConnectInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiTamRejectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_REJECT_IND = 0x4529
****************************************************************************/
void SendApiTamRejectInd ( RosTaskIdType Dst,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           ApiCcReleaseReasonType Reason);   /*!< DECT reason code */

#ifdef __cplusplus
}
#endif
#endif /*APITAMMPS_H */


