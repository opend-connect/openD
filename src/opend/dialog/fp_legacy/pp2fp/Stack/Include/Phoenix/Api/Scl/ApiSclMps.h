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
#ifndef APISCLMPS_H
#define APISCLMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Scl/ApiScl.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiSclGetModeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_GET_MODE_CFM = 0x4741
****************************************************************************/
void SendApiSclGetModeCfm ( RosTaskIdType Dst,
                            ApiSclModeType Mode,             /*!< Current SUOTA client
                                                                operation mode. */
                            ApiSclIntervalType Interval);    /*!< Check interval for
                                                                automatic mode. */

/****************************************************************************
* FUNCTION:      SendApiSclSetModeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_SET_MODE_CFM = 0x4743
****************************************************************************/
void SendApiSclSetModeCfm ( RosTaskIdType Dst,
                            RsStatusType Status);            /*!< Status. */

/****************************************************************************
* FUNCTION:      SendApiSclGetUrlCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_GET_URL_CFM = 0x4745
****************************************************************************/
void SendApiSclGetUrlCfm ( RosTaskIdType Dst,
                           rsuint16 Length,                  /*!< The length in bytes of
                                                                the URL. */
                           rsuint8 Url[1]);                  /*!< The URL as array of
                                                                IA5 chars. */

/****************************************************************************
* FUNCTION:      SendApiSclSetUrlCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_SET_URL_CFM = 0x4747
****************************************************************************/
void SendApiSclSetUrlCfm ( RosTaskIdType Dst,
                           RsStatusType Status);             /*!< Status. */

/****************************************************************************
* FUNCTION:      SendApiSclOperationCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_OPERATION_CFM = 0x4749
****************************************************************************/
void SendApiSclOperationCfm ( RosTaskIdType Dst,
                              RsStatusType Status);          /*!< Status:
                                                                RSS_NOT_SUPPORTED: Unknown operation.
                                                                RSS_BUSY: E.g. if
                                                                attempting check now while
                                                                an operation is already in progress.
                                                                RSS_NOT_READY: E.g. if
                                                                attempting begin update
                                                                while no operation is in
                                                                progress. */

/****************************************************************************
* FUNCTION:      SendApiSclStatusInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_STATUS_IND = 0x474A
****************************************************************************/
void SendApiSclStatusInd ( RosTaskIdType Dst,
                           ApiSclStatusType Status,          /*!< Current status. For
                                                                the status values
                                                                SCLS_COMPLETED,
                                                                SCLS_NO_UPDATES and
                                                                SCLS_UPDATE_AVAILABLE a
                                                                API_SCL_VERSIONS_IND will
                                                                follow this mail:. */
                           rsuint8 Progress,                 /*!< 0..100%. */
                           rsuint32 Delay);                  /*!< Delay before next
                                                                attempt, in seconds. */

/****************************************************************************
* FUNCTION:      SendApiSclVersionsInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_VERSIONS_IND = 0x474B
****************************************************************************/
void SendApiSclVersionsInd ( RosTaskIdType Dst,
                             rsbool WaitingForUser,          /*!< Set true when the
                                                                souta client is waiting for
                                                                user confirmation before
                                                                update is stated.
                                                                Confirmation or cancellation
                                                                is done by sending
                                                                API_SCL_OPERATION_REQ with
                                                                SCLO_UPDATE or SCLO_CANCEL. */
                             rsuint8 CurrentVersionLength,   /*!< The length of the
                                                                string stored in the
                                                                following CurrentVersion
                                                                parameter. Max length is 20. */
                             rsuint8 CurrentVersion[20],     /*!< The current SW version
                                                                identification string as
                                                                array of  IA5 chars. */
                             rsuint8 NewVersionLength,       /*!< The length of the
                                                                string stored in the
                                                                following NewVersion
                                                                parameter. Max length is 20. */
                             rsuint8 NewVersion[20]);        /*!< The new SW version
                                                                identification string as
                                                                array of  IA5 chars. */

/****************************************************************************
* FUNCTION:      SendApiSclGetGuidCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_GET_GUID_CFM = 0x474D
****************************************************************************/
void SendApiSclGetGuidCfm ( RosTaskIdType Dst,
                            RsStatusType Status,             /*!< Status:
                                                                RSS_SUCCES: The GUID
                                                                returned is the default.
                                                                RSS_UNKNOWN: The GUID
                                                                returned is not the default. */
                            ApiGuidType Guid);               /*!< Device identifier. */

/****************************************************************************
* FUNCTION:      SendApiSclSetGuidCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_SET_GUID_CFM = 0x474F
****************************************************************************/
void SendApiSclSetGuidCfm ( RosTaskIdType Dst,
                            RsStatusType Status);            /*!< Status. */

#ifdef __cplusplus
}
#endif
#endif /*APISCLMPS_H */


