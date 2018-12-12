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
#ifndef APILDSMPS_H
#define APILDSMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Lds/ApiLds.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiLdsOpenCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_OPEN_CFM = 0x4801
****************************************************************************/
void SendApiLdsOpenCfm ( RosTaskIdType Dst,
                         ApiLdsDeviceIdType DeviceId,        /*!< The device id of the
                                                                remote device. */
                         ApiLdsPortNumberType Port,          /*!< The port number used. */
                         RsStatusType Status,                /*!< Indicates whether the
                                                                call is accepted or not by
                                                                the remote device. */
                         rsuint16 InfoElementLength,         /*!< The length of the Data
                                                                Information Element.
                                                                Reserved for future
                                                                extension of the API. Must
                                                                be set to 0. */
                         rsuint8 InfoElement[1]);            /*!< Reserved for future
                                                                extension of the API. */

/****************************************************************************
* FUNCTION:      SendApiLdsOpenInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_OPEN_IND = 0x4802
****************************************************************************/
void SendApiLdsOpenInd ( RosTaskIdType Dst,
                         ApiLdsDeviceIdType DeviceId,        /*!< The id of the remote
                                                                device. 0 if the remote
                                                                device is a FP and handset
                                                                id if the remote device is a
                                                                PP. */
                         ApiLdsPortNumberType Port,          /*!< The port number used.
                                                                1079 for class 3/4. */
                         ApiCcBasicServiceType BasicService,  /*!< Class 4 is supported
                                                                 only. */
                         rsuint16 InfoElementLength,         /*!< The length of the Data
                                                                Information Element.
                                                                Reserved for future
                                                                extension of the API. Must
                                                                be set to 0. */
                         rsuint8 InfoElement[1]);            /*!< Reserved for future
                                                                extension of the API. */

/****************************************************************************
* FUNCTION:      SendApiLdsCloseCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_CLOSE_CFM = 0x4805
****************************************************************************/
void SendApiLdsCloseCfm ( RosTaskIdType Dst,
                          ApiLdsDeviceIdType DeviceId,       /*!< The device id of the
                                                                remote device. */
                          ApiLdsPortNumberType Port);        /*!< The port number used. */

/****************************************************************************
* FUNCTION:      SendApiLdsCloseInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_CLOSE_IND = 0x4806
****************************************************************************/
void SendApiLdsCloseInd ( RosTaskIdType Dst,
                          ApiLdsDeviceIdType DeviceId,       /*!< The device id of the
                                                                remote device. */
                          ApiLdsPortNumberType Port,         /*!< The port number used. */
                          ApiCcReleaseReasonType Reason);    /*!< Release reason. */

/****************************************************************************
* FUNCTION:      SendApiLdsRejectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_REJECT_IND = 0x4808
****************************************************************************/
void SendApiLdsRejectInd ( RosTaskIdType Dst,
                           ApiLdsDeviceIdType DeviceId,      /*!< The device id of the
                                                                remote device. */
                           ApiLdsPortNumberType Port,        /*!< The port number used. */
                           ApiCcReleaseReasonType Reason);   /*!< Reject reason.	 */

/****************************************************************************
* FUNCTION:      SendApiLdsTxReadyInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_TX_READY_IND = 0x4820
****************************************************************************/
void SendApiLdsTxReadyInd ( RosTaskIdType Dst,
                            ApiLdsDeviceIdType DeviceId);    /*!< The device id of the
                                                                remote device. */

/****************************************************************************
* FUNCTION:      SendApiLdsTxDataCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_TX_DATA_CFM = 0x4822
****************************************************************************/
void SendApiLdsTxDataCfm ( RosTaskIdType Dst,
                           ApiLdsDeviceIdType DeviceId,      /*!< The device id of the
                                                                remote device. */
                           ApiLdsPortNumberType Port,        /*!< The port number. */
                           RsStatusType Status,              /*!< Indicates the result
                                                                of the request:
                                                                RSS_SUCCESS if the data is queued
                                                                RSS_NO_MEMORY if the TX
                                                                buffer in the device is full.
                                                                RSS_BAD_DATA if the
                                                                SequenceNumer parameter of
                                                                the request is different
                                                                from the one expected.
                                                                RSS_NOT_SUPPORTED if the
                                                                mail based data interface is
                                                                not selected during the
                                                                connection establishment. */
                           rsuint8 SequenceNumber);          /*!< The sequence number
                                                                from the request that this
                                                                mails confirms. */

/****************************************************************************
* FUNCTION:      SendApiLdsRxDataInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_RX_DATA_IND = 0x4823
****************************************************************************/
void SendApiLdsRxDataInd ( RosTaskIdType Dst,
                           ApiLdsDeviceIdType DeviceId,      /*!< The device id of the
                                                                remote device. */
                           ApiLdsPortNumberType Port,        /*!< The port number. */
                           RsStatusType Status,              /*!< Indicates the whether
                                                                the RX data is valid:
                                                                RSS_SUCCESS if the data is
                                                                received OK
                                                                RSS_BAD_DATA if an error
                                                                has been detected. The
                                                                application must discard the
                                                                entire SDU. */
                           ApiLdsSduStateType SduState,      /*!< Indicates if the mail contains:
                                                                A complete SDU.
                                                                First fragment of the SDU.
                                                                Continuation fragment of
                                                                the SDU.
                                                                Last fragment of the SDU. */
                           rsbool More,                      /*!< Used as followed if
                                                                the chopping option is used:
                                                                FALSE: This is the last
                                                                segment (or the only one) of
                                                                an application packet.
                                                                TRUE: The next segment of
                                                                the same application packet
                                                                follows in next SDU 
                                                                Set to FALSE (0) if
                                                                chopping is not used. */
                           rsuint8 SequenceNumber,           /*!< Set to 0 for the first
                                                                time this mail is sent on
                                                                the connection and
                                                                incremented by one for
                                                                subsequent mails. */
                           rsuint16 DataLength,              /*!< The size in bytes of
                                                                the data parameter. */
                           rsuint8 Data[1]);                 /*!< The SDU data. */

/****************************************************************************
* FUNCTION:      SendApiLdsFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_FEATURES_CFM = 0x4831
****************************************************************************/
void SendApiLdsFeaturesCfm ( RosTaskIdType Dst,
                             RsStatusType Status,            /*!<  */
                             ApiLdsFeatureType ApiLdsFeature);
                                                             /*!< Supported features */

#ifdef __cplusplus
}
#endif
#endif /*APILDSMPS_H */


