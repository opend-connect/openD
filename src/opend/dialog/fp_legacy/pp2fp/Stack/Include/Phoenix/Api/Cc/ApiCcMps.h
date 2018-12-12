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
#ifndef APICCMPS_H
#define APICCMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Cc/ApiCc.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiCcSetupAckInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_SETUP_ACK_IND = 0x5001
****************************************************************************/
void SendApiCcSetupAckInd ( RosTaskIdType Dst,
                            ApiCcConEiType ConEi,            /*!< The Instance of the
                                                                connection defined by the setup_req.
                                                                For this call/connection
                                                                the selected connection
                                                                instance should be used for
                                                                following call handling
                                                                mails */
                            ApiCcProgressIndType ProgressInd,
                                                             /*!< Inband information */
                            ApiCcSignalType Signal,          /*!< Alert signal. This is
                                                                used to request the MMI to
                                                                start a certain local tone. */
                            rsuint16 InfoElementLength,      /*!< The length of the Data
                                                                Information Element */
                            rsuint8 InfoElement[1]);         /*!< The InfoElementList
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
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiCcCallProcInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CALL_PROC_IND = 0x5002
****************************************************************************/
void SendApiCcCallProcInd ( RosTaskIdType Dst,
                            ApiCcConEiType ConEi,            /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                            ApiCcProgressIndType ProgressInd,
                                                             /*!< Inband information */
                            ApiCcSignalType Signal,          /*!< Alert signal. Can be
                                                                used to control which
                                                                ringer melody to be used. */
                            rsuint16 InfoElementLength,      /*!< The length of the Data
                                                                Information Element */
                            rsuint8 InfoElement[1]);         /*!< The InfoElementList
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
                                                                [API_IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiCcAlertInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_ALERT_IND = 0x5003
****************************************************************************/
void SendApiCcAlertInd ( RosTaskIdType Dst,
                         ApiCcConEiType ConEi,               /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                         ApiCcProgressIndType ProgressInd,   /*!< Inband information */
                         ApiCcSignalType Signal,             /*!< Alert signal. Can be
                                                                used to control which
                                                                ringer melody to be used. */
                         rsuint16 InfoElementLength,         /*!< The length of the Data
                                                                Information Element */
                         rsuint8 InfoElement[1]);            /*!< The InfoElementList
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
                                                                [API_IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiCcConnectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CONNECT_IND = 0x5004
****************************************************************************/
void SendApiCcConnectInd ( RosTaskIdType Dst,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
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
                                                                [API_IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiCcSetupInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_SETUP_IND = 0x500A
****************************************************************************/
void SendApiCcSetupInd ( RosTaskIdType Dst,
                         ApiCcConEiType ConEi,               /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                         ApiCcBasicServiceType BasicService,  /*!< Narrow/wide band
                                                                 speech encoding */
                         ApiCcCallClassType CallClass,       /*!< DECT defined call
                                                                classes. */
                         ApiCcSignalType Signal,             /*!< Alert signal. Can be
                                                                used to control which
                                                                ringer melody is used at
                                                                Called endpoint. */
                         rsuint16 InfoElementLength,         /*!< The length of the Data
                                                                Information Element */
                         rsuint8 InfoElement[1]);            /*!< The InfoElementList
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
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CALLING_PARTY_NUMBER
                                                                ] 
                                                                [API_IE_CALLING_PARTY_NAME]
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcConnectCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CONNECT_CFM = 0x500D
****************************************************************************/
void SendApiCcConnectCfm ( RosTaskIdType Dst,
                           ApiCcConEiType ConEi);            /*!< The handset id and
                                                                connection instance. */

/****************************************************************************
* FUNCTION:      SendApiCcInfoInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_INFO_IND = 0x5031
****************************************************************************/
void SendApiCcInfoInd ( RosTaskIdType Dst,
                        ApiCcConEiType ConEi,                /*!< The Instance of the
                                                                connection defined by the setup_req.
                                                                For this call/connection
                                                                the selected connection
                                                                instance should be used for
                                                                following call handling
                                                                mails */
                        ApiCcProgressIndType ProgressInd,    /*!< Inband information */
                        ApiCcSignalType Signal,              /*!< Alert signal. This is
                                                                used to request the MMI to
                                                                start a certain local tone. */
                        rsuint16 InfoElementLength,          /*!< The length of the Data
                                                                Information Element */
                        rsuint8 InfoElement[1]);             /*!< The InfoElementList
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
                                                                [API_IE_CALLING_PARTY_NUMBER
                                                                ] 
                                                                [API_IE_CALLING_PARTY_NAME]
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID]
                                                                [API_IE_CALL_STATUS]
                                                                [API_IE_MULTI_DISPLAY] */

/****************************************************************************
* FUNCTION:      SendApiCcReleaseCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_RELEASE_CFM = 0x5015
****************************************************************************/
void SendApiCcReleaseCfm ( RosTaskIdType Dst,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
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
* FUNCTION:      SendApiCcReleaseInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_RELEASE_IND = 0x5016
****************************************************************************/
void SendApiCcReleaseInd ( RosTaskIdType Dst,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           ApiCcReleaseReasonType Reason,    /*!< DECT reason code */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
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
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiCcRejectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_REJECT_IND = 0x5018
****************************************************************************/
void SendApiCcRejectInd ( RosTaskIdType Dst,
                          ApiCcConEiType ConEi,              /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                          ApiCcReleaseReasonType Reason,     /*!< DECT reason code */
                          rsuint16 InfoElementLength,        /*!< The length of the Data
                                                                Information Element */
                          rsuint8 InfoElement[1]);           /*!< The InfoElementList
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
* FUNCTION:      SendApiCcIwuInfoInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_IWU_INFO_IND = 0x5033
****************************************************************************/
void SendApiCcIwuInfoInd ( RosTaskIdType Dst,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
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
                                                                [API_IE_MMS_GEN_HEADER]
                                                                [API_IE_MMS_OBJ_HEADER]
                                                                [API_IE_MMS_EXT_HEADER]
                                                                [API_IE_TIME_DATE]
                                                                [API_IE_SEGMENT_INFO]
                                                                [API_IE_IWU_TO_IWU]
                                                                
                                                                NOTE:
                                                                Some of the Infoelements
                                                                are only available if SMS
                                                                support is enabled */

/****************************************************************************
* FUNCTION:      SendApiCcGetConeiCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_GET_CONEI_CFM = 0x5037
****************************************************************************/
void SendApiCcGetConeiCfm ( RosTaskIdType Dst,
                            ApiCcConEiType ConEi);           /*!< Connection endpoint
                                                                identifier */

/****************************************************************************
* FUNCTION:      SendApiCcConeiChangeInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CONEI_CHANGE_IND = 0x502A
****************************************************************************/
void SendApiCcConeiChangeInd ( RosTaskIdType Dst,
                               ApiCcConEiType ConEi,         /*!< The Instance of the
                                                                connection defined by switch
                                                                control. */
                               ApiCcConEiType NewConEi);     /*!< The New Instance of
                                                                the connection re-assigned
                                                                by switch control. For
                                                                further signaling the
                                                                handling of the
                                                                call/connection the received
                                                                NewConEi should be used. */

/****************************************************************************
* FUNCTION:      SendApiCcModifyCodecCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_MODIFY_CODEC_CFM = 0x501B
****************************************************************************/
void SendApiCcModifyCodecCfm ( RosTaskIdType Dst,
                               ApiCcConEiType ConEi,         /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                               RsStatusType Status);         /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiCcModifyCodecInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_MODIFY_CODEC_IND = 0x501C
****************************************************************************/
void SendApiCcModifyCodecInd ( RosTaskIdType Dst,
                               ApiCcConEiType ConEi,         /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                               rsuint16 InfoElementLength,   /*!< The length of the Data
                                                                Information Element */
                               rsuint8 InfoElement[1]);      /*!< The InfoElementList
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
                                                                [API_IE_CODEC_LIST]
                                                                The Codec list shall
                                                                contain one and only one
                                                                codec. */

/****************************************************************************
* FUNCTION:      SendApiCcIwuInfoCodecInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_IWU_INFO_CODEC_IND = 0x501E
****************************************************************************/
void SendApiCcIwuInfoCodecInd ( RosTaskIdType Dst,
                                ApiCcConEiType ConEi,        /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                                rsuint16 InfoElementLength,  /*!< The length of the Data
                                                                Information Element */
                                rsuint8 InfoElement[1]);     /*!< The InfoElementList
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
                                                                 [API_IE_CODEC_LIST]
                                                                The Codec list shall
                                                                contain one and only one
                                                                codec. */

/****************************************************************************
* FUNCTION:      SendApiCcClmsDataInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CLMS_DATA_IND = 0x5035
****************************************************************************/
void SendApiCcClmsDataInd ( RosTaskIdType Dst,
                            ApiCcConEiType ConEi,            /*!< The Instance of the
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
                                                                [API_IE_PORTABLE_IDENTITY]
                                                                [API_IE_MMS_GEN_HEADER]
                                                                [API_IE_MMS_OBJ_HEADER]
                                                                [API_IE_MMS_EXT_HEADER]
                                                                [API_IE_TIME_DATE]
                                                                [API_IE_SEGMENT_INFO]
                                                                [API_IE_IWU_TO_IWU]
                                                                
                                                                NOTE:
                                                                Some of the Infoelements
                                                                are only available if SMS
                                                                support is enabled */

#ifdef __cplusplus
}
#endif
#endif /*APICCMPS_H */


