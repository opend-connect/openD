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
#ifndef APIFPGENERALMPS_H
#define APIFPGENERALMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpGeneral/ApiFpGeneral.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpResetInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_RESET_IND = 0x4001
****************************************************************************/
void SendApiFpResetInd ( RosTaskIdType Dst,
                         RsStatusType Status);               /*!< Indicates whether the
                                                                device is ready or not. */

/****************************************************************************
* FUNCTION:      SendApiFpGetFwVersionCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_FW_VERSION_CFM = 0x4003
****************************************************************************/
void SendApiFpGetFwVersionCfm ( RosTaskIdType Dst,
                                RsStatusType Status,         /*!< Indicates whether the
                                                                command succeeded or not. */
                                rsuint32 VersionHex,         /*!< The Firmware version. */
                                rsuint8 LinkDate[5],         /*!< The link date. */
                                ApiDectTypeType DectType,    /*!< Specifies whether this
                                                                is unit is setup for EU or
                                                                US DECT. */
                                rsuint16 InfoElementLength,  /*!< The length of the Data
                                                                Information Element */
                                rsuint8 InfoElement[1]);     /*!< Possible Info elements:
                                                                [API_IE_AVAILABLE_APIS] 
                                                                [API_IE_LINE_ID] */

/****************************************************************************
* FUNCTION:      SendApiFpCradleDetectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CRADLE_DETECT_IND = 0x4081
****************************************************************************/
void SendApiFpCradleDetectInd ( RosTaskIdType Dst,
                                ApiCradleStatusType ApiCradleStatus);
                                                             /*!< The current status of
                                                                the cradle */

/****************************************************************************
* FUNCTION:      SendApiFpSetTimeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_TIME_CFM = 0x4083
****************************************************************************/
void SendApiFpSetTimeCfm ( RosTaskIdType Dst,
                           RsStatusType Status);             /*!< Indicates whether the
                                                                API_FP_SET_TIME_REQ was
                                                                executed correctly or not.
                                                                RsStatusType is defined in
                                                                the ROS */

/****************************************************************************
* FUNCTION:      SendApiFpGetTimeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_TIME_CFM = 0x4085
****************************************************************************/
void SendApiFpGetTimeCfm ( RosTaskIdType Dst,
                           ApiTimeDateCodeType ApiTimeDateCode);
                                                             /*!< The time stamp */

/****************************************************************************
* FUNCTION:      SendApiFpSetTimeInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_TIME_IND = 0x4086
****************************************************************************/
void SendApiFpSetTimeInd ( RosTaskIdType Dst,
                           ApiTerminalIdType TerminalId,     /*!< Id of the handset
                                                                which request to change the
                                                                timedate. [1:N] */
                           ApiTimeDateCodingType Coding,     /*!< Describes if only
                                                                date, time, or both should
                                                                be set. */
                           ApiTimeDateInterpretationType Interpretation,
                                                             /*!< Describes the time
                                                                stamp interpretation */
                           ApiTimeDateCodeType ApiTimeDateCode);
                                                             /*!< The time stamp */

/****************************************************************************
* FUNCTION:      SendApiFpFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FEATURES_CFM = 0x40A1
****************************************************************************/
void SendApiFpFeaturesCfm ( RosTaskIdType Dst,
                            RsStatusType Status,             /*!<  */
                            ApiFpFeatureType ApiFpFeature);  /*!< Supported features */

#ifdef __cplusplus
}
#endif
#endif /*APIFPGENERALMPS_H */


