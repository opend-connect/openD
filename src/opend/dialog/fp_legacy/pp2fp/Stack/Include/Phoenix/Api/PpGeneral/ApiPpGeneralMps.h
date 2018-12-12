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
#ifndef APIPPGENERALMPS_H
#define APIPPGENERALMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/PpGeneral/ApiPpGeneral.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiPpGetFwVersionCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_GET_FW_VERSION_CFM = 0x5201
****************************************************************************/
void SendApiPpGetFwVersionCfm ( RosTaskIdType Dst,
                                rsuint32 VersionHex,         /*!< The Firmware version. */
                                rsuint8 LinkDate[5],         /*!< The link date. */
                                ApiDectTypeType DectType,    /*!< Specifies whether this
                                                                is unit is setup for EU or
                                                                US DECT. */
                                rsuint16 InfoElementLength,  /*!< The length of the Data
                                                                Information Element */
                                rsuint8 InfoElement[1]);     /*!< Possible Info elements:
                                                                [API_IE_AVAILABLE_APIS] */

/****************************************************************************
* FUNCTION:      SendApiPpResetInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_RESET_IND = 0x5203
****************************************************************************/
void SendApiPpResetInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpCradleDetectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_CRADLE_DETECT_IND = 0x5206
****************************************************************************/
void SendApiPpCradleDetectInd ( RosTaskIdType Dst,
                                ApiCradleStatusType ApiCradleStatus);
                                                             /*!< The current status of
                                                                the cradle */

/****************************************************************************
* FUNCTION:      SendApiPpSetTimeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_SET_TIME_CFM = 0x5208
****************************************************************************/
void SendApiPpSetTimeCfm ( RosTaskIdType Dst,
                           RsStatusType Status);             /*!< Indicates whether the
                                                                API_PP_SET_TIME_REQ was
                                                                executed correctly or not.
                                                                RsStatusType is defined in
                                                                the ROS */

/****************************************************************************
* FUNCTION:      SendApiPpGetTimeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_GET_TIME_CFM = 0x520A
****************************************************************************/
void SendApiPpGetTimeCfm ( RosTaskIdType Dst,
                           ApiTimeDateCodeType ApiTimeDateCode);
                                                             /*!< The time stamp */

#ifdef __cplusplus
}
#endif
#endif /*APIPPGENERALMPS_H */


