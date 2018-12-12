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
#ifndef APIFPCCMPS_H
#define APIFPCCMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpCc/ApiFpCc.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpCcSetupInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SETUP_IND = 0x4400
****************************************************************************/
void SendApiFpCcSetupInd ( RosTaskIdType Dst,
                           ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                           ApiTerminalIdType TerminalId,     /*!< Id of the calling
                                                                handset. */
                           ApiCcBasicServiceType BasicService,
                                                             /*!< Narrow/wide band
                                                                speech encoding */
                           ApiCcCallClassType CallClass,     /*!< DECT defined call
                                                                classes. */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_MULTIKEYPAD] 
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiFpCcSetupCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SETUP_CFM = 0x4403
****************************************************************************/
void SendApiFpCcSetupCfm ( RosTaskIdType Dst,
                           ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                           rsuint8 SystemCallId,             /*!< System-wide call ID
                                                                (NG-DECT call
                                                                identification) */
                           RsStatusType Status,              /*!< Indicates whether the
                                                                call is made or not. */
                           ApiCcBasicServiceType BasicService,
                                                             /*!< Narrow/wide band
                                                                speech encoding */
                           ApiCcCallClassType CallClass,     /*!< DECT defined call
                                                                classes. */
                           ApiFpCcAudioIdType AudioId);      /*!<  */

/****************************************************************************
* FUNCTION:      SendApiFpCcSetupAckCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SETUP_ACK_CFM = 0x4424
****************************************************************************/
void SendApiFpCcSetupAckCfm ( RosTaskIdType Dst,
                              ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                              RsStatusType Status);          /*!< Indicates whether the
                                                                call is made or not. */

/****************************************************************************
* FUNCTION:      SendApiFpCcCallProcCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_CALL_PROC_CFM = 0x4416
****************************************************************************/
void SendApiFpCcCallProcCfm ( RosTaskIdType Dst,
                              ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                              RsStatusType Status);          /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpCcAlertInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_ALERT_IND = 0x4404
****************************************************************************/
void SendApiFpCcAlertInd ( RosTaskIdType Dst,
                           ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CODEC_LIST]  
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiFpCcAlertCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_ALERT_CFM = 0x4406
****************************************************************************/
void SendApiFpCcAlertCfm ( RosTaskIdType Dst,
                           ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                           RsStatusType Status);             /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpCcConnectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_CONNECT_IND = 0x4407
****************************************************************************/
void SendApiFpCcConnectInd ( RosTaskIdType Dst,
                             ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                             rsuint16 InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                             rsuint8 InfoElement[1]);        /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiFpCcConnectCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_CONNECT_CFM = 0x440A
****************************************************************************/
void SendApiFpCcConnectCfm ( RosTaskIdType Dst,
                             ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                             RsStatusType Status,            /*!< Indicates whether the
                                                                command succeeded or not. */
                             rsuint16 InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                             rsuint8 InfoElement[1]);        /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiFpCcReleaseInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_RELEASE_IND = 0x440F
****************************************************************************/
void SendApiFpCcReleaseInd ( RosTaskIdType Dst,
                             ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                             ApiCcReleaseReasonType Reason,  /*!< Release reason. */
                             rsuint16 InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                             rsuint8 InfoElement[1]);        /*!< The InfoElementList
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
                                                                [API_IE_RELEASE_EXT_REASON]
                                                                [API_IE_CODECLIST] */

/****************************************************************************
* FUNCTION:      SendApiFpCcReleaseCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_RELEASE_CFM = 0x4412
****************************************************************************/
void SendApiFpCcReleaseCfm ( RosTaskIdType Dst,
                             ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                             RsStatusType Status,            /*!< Indicates whether the
                                                                command succeeded or not. */
                             rsuint16 InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                             rsuint8 InfoElement[1]);        /*!< The InfoElementList
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
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiFpCcRejectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_REJECT_IND = 0x4413
****************************************************************************/
void SendApiFpCcRejectInd ( RosTaskIdType Dst,
                            ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                            ApiCcReleaseReasonType Reason,   /*!< Reject reason. */
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
                                                                [API_IE_RELEASE_EXT_REASON] */

/****************************************************************************
* FUNCTION:      SendApiFpCcInfoInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_INFO_IND = 0x442D
****************************************************************************/
void SendApiFpCcInfoInd ( RosTaskIdType Dst,
                          ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                          rsuint16 InfoElementLength,        /*!< The length of the Data
                                                                Information Element */
                          rsuint8 InfoElement[1]);           /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
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
                                                                [API_IE_MULTIKEYPAD]
                                                                [API_IE_CALLED_NUMBER]
                                                                 [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiFpCcModifyCodecCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_MODIFY_CODEC_CFM = 0x441E
****************************************************************************/
void SendApiFpCcModifyCodecCfm ( RosTaskIdType Dst,
                                 ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number.
 */
                                 RsStatusType Status);       /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpCcModifyCodecInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_MODIFY_CODEC_IND = 0x441F
****************************************************************************/
void SendApiFpCcModifyCodecInd ( RosTaskIdType Dst,
                                 ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                                 rsuint16 InfoElementLength,  /*!< The length of the
                                                                 Data Information Element */
                                 rsuint8 InfoElement[1]);    /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiFpCcIwuInfoCodecInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_IWU_INFO_CODEC_IND = 0x4421
****************************************************************************/
void SendApiFpCcIwuInfoCodecInd ( RosTaskIdType Dst,
                                  ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                                  rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                  rsuint8 InfoElement[1]);   /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiFpCcSystemCallIdCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SYSTEM_CALL_ID_CFM = 0x4428
****************************************************************************/
void SendApiFpCcSystemCallIdCfm ( RosTaskIdType Dst,
                                  ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number */
                                  rsuint8 SystemCallId);     /*!< System-wide call ID
                                                                (NG-DECT call
                                                                identification) */

/****************************************************************************
* FUNCTION:      SendApiFpCcSelectedAdpcmInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SELECTED_ADPCM_IND = 0x4430
****************************************************************************/
void SendApiFpCcSelectedAdpcmInd ( RosTaskIdType Dst,
                                   ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                                   ApiAdpcmType Adpcm);      /*!< Selected ADPCM block */

/****************************************************************************
* FUNCTION:      SendApiFpCcSetFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SET_FEATURES_CFM = 0x4451
****************************************************************************/
void SendApiFpCcSetFeaturesCfm ( RosTaskIdType Dst,
                                 RsStatusType Status,        /*!<  */
                                 ApiFpCcFeatureType ApiFpCcFeature);
                                                             /*!< Supported features */

/****************************************************************************
* FUNCTION:      SendApiFpCcGetFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_GET_FEATURES_CFM = 0x4453
****************************************************************************/
void SendApiFpCcGetFeaturesCfm ( RosTaskIdType Dst,
                                 ApiFpCcFeatureType CurrentFeatures,
                                                             /*!< Current feature
                                                                settings */
                                 ApiFpCcFeatureType AvailableFeatures);
                                                             /*!< Available feature
                                                                settings */

#ifdef __cplusplus
}
#endif
#endif /*APIFPCCMPS_H */


