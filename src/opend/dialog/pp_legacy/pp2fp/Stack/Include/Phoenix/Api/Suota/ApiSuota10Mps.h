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
#ifndef APISUOTA10MPS_H
#define APISUOTA10MPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Suota/ApiSuota.h>
#include <Phoenix/Api/Suota/ApiSuota10.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiSuotaSwVersionInfo10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SUOTA_SW_VERSION_INFO10_IND = 0x4881
****************************************************************************/
void SendApiSuotaSwVersionInfo10Ind ( RosTaskIdType Dst,
                                      ApiSuotaDeviceId10Type DeviceId,
                                                             /*!< Id of the source. */
                                      ApiSuotaEmcType Emc,   /*!< The EMC of the device
                                                                requesting the SW info. */
                                      ApiSuotaFileNumberType FileNumber,
                                                             /*!< The file number. Used
                                                                to identify the current file
                                                                if the SW to update is
                                                                stored in multiple files. */
                                      ApiSuotaFlagsType Flags,
                                                             /*!< Indicates whether the
                                                                update is initiated by the
                                                                user. */
                                      ApiSuotaReasonType Reason,
                                                             /*!< The reason for this
                                                                command. */
                                      rsuint8 SwVersionIdLength,
                                                             /*!< The length of the
                                                                string stored in the
                                                                following SwVersionId
                                                                parameter. Max length is 20. */
                                      rsuint8 SwVersionId[20],
                                                             /*!< The SW version
                                                                identification string as
                                                                array of  IA5 chars. */
                                      rsuint8 HwVersionIdLength,
                                                             /*!< The length of the
                                                                string stored in the
                                                                following HwVersionId
                                                                parameter. Max length is 20. */
                                      rsuint8 HwVersionId[20],
                                                             /*!< The HW version
                                                                identification string as
                                                                array of  IA5 chars. */
                                      rsuint16 UrlLength,    /*!< The length in bytes of
                                                                the URL. */
                                      rsuint8 Url[1]);       /*!< The URL as array of
                                                                IA5 chars. */

/****************************************************************************
* FUNCTION:      SendApiSuotaNegativeAck10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SUOTA_NEGATIVE_ACK10_IND = 0x4885
****************************************************************************/
void SendApiSuotaNegativeAck10Ind ( RosTaskIdType Dst,
                                    ApiSuotaDeviceId10Type DeviceId,
                                                             /*!< Id of the source. */
                                    ApiSuotaRejectReasonType Reason);
                                                             /*!< Reject reason. */

#ifdef __cplusplus
}
#endif
#endif /*APISUOTA10MPS_H */


