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
#ifndef APIFPMMMPS_H
#define APIFPMMMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpMm/ApiFpMm.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpMmGetIdCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_ID_CFM = 0x4005
****************************************************************************/
void SendApiFpMmGetIdCfm ( RosTaskIdType Dst,
                           RsStatusType Status,              /*!< Indicates whether the
                                                                command succeeded or not */
                           rsuint8 Id[5]);                   /*!< The id of the FP. The
                                                                RFPI of the FP is
                                                                transmitted in the
                                                                dummybearer and used as FP
                                                                identification for the PPs
                                                                when registering and
                                                                locking. */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetModelCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_MODEL_CFM = 0x4007
****************************************************************************/
void SendApiFpMmGetModelCfm ( RosTaskIdType Dst,
                              RsStatusType Status,           /*!< Indicates whether the
                                                                command succeeded or not */
                              ApiModelIdType ModelId);       /*!< The manufacture
                                                                (MANIC) and model (MODIC)
                                                                code of the FP. The EMC code
                                                                of the FP is used as
                                                                manufacture code. */

/****************************************************************************
* FUNCTION:      SendApiFpMmSetAccessCodeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_SET_ACCESS_CODE_CFM = 0x4009
****************************************************************************/
void SendApiFpMmSetAccessCodeCfm ( RosTaskIdType Dst,
                                   RsStatusType Status);     /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetAccessCodeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_ACCESS_CODE_CFM = 0x400B
****************************************************************************/
void SendApiFpMmGetAccessCodeCfm ( RosTaskIdType Dst,
                                   RsStatusType Status,      /*!< Indicates whether the
                                                                command succeeded or not. */
                                   rsuint8 Ac[4]);           /*!< The authentication
                                                                code of the FP. This is the
                                                                PIN code of the FP used to
                                                                verify the user for
                                                                registration. The dataformat
                                                                is BCD and the string is 'F'
                                                                terminated (unused nibbles
                                                                are set to 'F').
                                                                
                                                                Example.
                                                                  AcCode = 1234
                                                                  AcCode[4] = { 0xFF, 0xFF,
                                                                0x12, 0x34 } */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetRegistrationCountCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_REGISTRATION_COUNT_CFM = 0x4101
****************************************************************************/
void SendApiFpMmGetRegistrationCountCfm ( RosTaskIdType Dst,
                                          RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */
                                          ApiTerminalIdType MaxNoHandsets,
                                                             /*!< Maximum number of
                                                                handsets that can be
                                                                registered. */
                                          ApiTerminalIdType TerminalIdCount,
                                                             /*!< Number of entries in
                                                                TerminalId array. */
                                          ApiTerminalIdType TerminalId[1]);
                                                             /*!< Array of Ids of the
                                                                handsets registered. 
(Index
                                                                0 to HandsetIdLength-1 is
                                                                used.) */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetHandsetIpuiCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_HANDSET_IPUI_CFM = 0x410A
****************************************************************************/
void SendApiFpMmGetHandsetIpuiCfm ( RosTaskIdType Dst,
                                    RsStatusType Status,     /*!< Indicates whether the
                                                                command succeeded or not. */
                                    ApiTerminalIdType TerminalId,
                                                             /*!< The Id for which the
                                                                IPUI is read. */
                                    rsuint8 IPUI[5],         /*!< The IPUI. */
                                    rsuint16 InfoElementLength,
                                                             /*!< (OPTIONAL) The length
                                                                of the Data Information
                                                                Element */
                                    rsuint8 InfoElement[1]);  /*!< (OPTIONAL) The
                                                                 InfoElementList can hold a
                                                                 number Info Elements placed
                                                                 in the in the format
                                                                 
                                                                 { Ie, IeLength, IeData[],
                                                                 Ie, IeLength, IeData[],
                                                                 ...} 
                                                                 
                                                                 Each element is packed
                                                                 following the 
                                                                 ApiInfoElementType (which
                                                                 is defined in the
                                                                 Phoenix_PP_API_Types.doc)
                                                                 
                                                                 At reception the receiving
                                                                 task should search through
                                                                 the info data package to
                                                                 search for the requested
                                                                 elements and pick out the
                                                                 info data.
                                                                 
                                                                 Expected Info elements:
                                                                 [API_IE_CODECLIST]
                                                                 [API_IE_BASIC_TERMCAPS] 
                                                                 [API_IE_LOCATION_STATUS] */

/****************************************************************************
* FUNCTION:      SendApiFpMmHandsetPresentInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_HANDSET_PRESENT_IND = 0x4108
****************************************************************************/
void SendApiFpMmHandsetPresentInd ( RosTaskIdType Dst,
                                    ApiTerminalIdType TerminalId,
                                                             /*!< Id of the handset that
                                                                has made a location update. */
                                    rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                    rsuint8 InfoElement[1]);  /*!< The InfoElementList
                                                                 can hold a number Info
                                                                 Elements placed in the in
                                                                 the format
                                                                 
                                                                 { Ie, IeLength, IeData[],
                                                                 Ie, IeLength, IeData[],
                                                                 ...} 
                                                                 
                                                                 Each element is packed
                                                                 following the 
                                                                 ApiInfoElementType (which
                                                                 is defined in the
                                                                 Phoenix_PP_API_Types.doc)
                                                                 
                                                                 At reception the receiving
                                                                 task should search through
                                                                 the info data package to
                                                                 search for the requested
                                                                 elements and pick out the
                                                                 info data.
                                                                 
                                                                 Expected Info elements:
                                                                 [API_IE_CODECLIST] 
                                                                 [API_IE_MODEL_ID]
                                                                 [API_IE_TERMCAPS] */

/****************************************************************************
* FUNCTION:      SendApiFpMmHandsetDetachInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_HANDSET_DETACH_IND = 0x410E
****************************************************************************/
void SendApiFpMmHandsetDetachInd ( RosTaskIdType Dst,
                                   ApiTerminalIdType TerminalId,
                                                             /*!< Id of the handset that
                                                                has made a location update. */
                                   rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                   rsuint8 InfoElement[1]);  /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                Phoenix_PP_API_Types.doc)
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Info elements:
                                                                [API_IE_MODEL_ID] */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetNameCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_NAME_CFM = 0x4111
****************************************************************************/
void SendApiFpMmGetNameCfm ( RosTaskIdType Dst,
                             RsStatusType Status,            /*!< RSS_SUCCESS or error
                                                                status. RSS_REJECTED if LAS
                                                                must be used. */
                             rsuint8 Max,                    /*!< Maximum length of
                                                                name. */
                             rsuint8 Length,                 /*!< Current length of
                                                                name. */
                             rsuint8 Data[1]);               /*!< Name characters. */

/****************************************************************************
* FUNCTION:      SendApiFpMmSetNameCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_SET_NAME_CFM = 0x4113
****************************************************************************/
void SendApiFpMmSetNameCfm ( RosTaskIdType Dst,
                             RsStatusType Status);           /*!< RSS_SUCCESS or error
                                                                status. RSS_REJECTED if LAS
                                                                must be used. */

/****************************************************************************
* FUNCTION:      SendApiFpMmSetRegistrationModeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_SET_REGISTRATION_MODE_CFM = 0x4106
****************************************************************************/
void SendApiFpMmSetRegistrationModeCfm ( RosTaskIdType Dst,
                                         RsStatusType Status);
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpMmRegistrationCompleteInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_REGISTRATION_COMPLETE_IND = 0x4107
****************************************************************************/
void SendApiFpMmRegistrationCompleteInd ( RosTaskIdType Dst,
                                          RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not.
                                                                RsStatusType is defined in
                                                                the ROS */
                                          ApiTerminalIdType TerminalId,
                                                             /*!< Id of the handset that
                                                                was registered to the FP */
                                          rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                          rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                Phoenix_PP_API_Types.doc)
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Infoelements:
                                                                [API_IE_CODECLIST]
                                                                [API_IE_MODEL_ID]
                                                                [API_IE_TERMCAPS] */

/****************************************************************************
* FUNCTION:      SendApiFpMmRegistrationFailedInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_REGISTRATION_FAILED_IND = 0x4104
****************************************************************************/
void SendApiFpMmRegistrationFailedInd ( RosTaskIdType Dst,
                                        ApiMmRejectReasonType Reason,
                                                             /*!< Indicates the reason
                                                                for failing. RsStatusType is
                                                                defined in the ROS */
                                        rsuint8 IPUI[5]);    /*!< The IPUI of the failed
                                                                PP. */

/****************************************************************************
* FUNCTION:      SendApiFpMmDeleteRegistrationCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_DELETE_REGISTRATION_CFM = 0x4103
****************************************************************************/
void SendApiFpMmDeleteRegistrationCfm ( RosTaskIdType Dst,
                                        RsStatusType Status,  /*!< Indicates whether the
                                                                 command succeeded or not. */
                                        ApiTerminalIdType TerminalId);
                                                             /*!< Index of the handset
                                                                that shall be deleted. */

/****************************************************************************
* FUNCTION:      SendApiFpMmHandsetDeregisteredInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_HANDSET_DEREGISTERED_IND = 0x410F
****************************************************************************/
void SendApiFpMmHandsetDeregisteredInd ( RosTaskIdType Dst,
                                         ApiTerminalIdType TerminalId);
                                                             /*!< Index of the handset
                                                                that has been deleted. */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetFpCapabilitiesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_FP_CAPABILITIES_CFM = 0x4171
****************************************************************************/
void SendApiFpMmGetFpCapabilitiesCfm ( RosTaskIdType Dst,
                                       rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                       rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                Phoenix_PP_API_Types.doc)
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Infoelements:
                                                                [API_IE_FP_CAPABILITIES]
                                                                [API_IE_FP_EXTENDED_CAPABILITIES]
                                                                [API_IE_FP_EXTENDED_CAPABILI
                                                                TIES2] */

/****************************************************************************
* FUNCTION:      SendApiFpMmFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_FEATURES_CFM = 0x4161
****************************************************************************/
void SendApiFpMmFeaturesCfm ( RosTaskIdType Dst,
                              RsStatusType Status,           /*!<  */
                              ApiFpMmFeatureType ApiFpMmFeature);
                                                             /*!< Supported features */

#ifdef __cplusplus
}
#endif
#endif /*APIFPMMMPS_H */


