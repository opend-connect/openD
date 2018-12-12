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
#ifndef APIFPLLME10MPS_H
#define APIFPLLME10MPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpLlme/ApiFpLlme10.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpLlmeGetRssi10Cfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LLME_GET_RSSI10_CFM = 0x47B1
****************************************************************************/
void SendApiFpLlmeGetRssi10Cfm ( RosTaskIdType Dst,
                                 RsStatusType Status,        /*!< Indicates whether the
                                                                command succeeded or not.
                                                                Command will only report
                                                                SUCCESS if connection is
                                                                active. */
                                 rsuint8 HandsetId,          /*!< Selected Pp */
                                 rsuint8 Rssi);              /*!< Received Signal
                                                                Strength Indication for the
                                                                selected Pp. Range
                                                                0x00-0x3F. */

/****************************************************************************
* FUNCTION:      SendApiFpLlmeGetPerformanceTable10Cfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LLME_GET_PERFORMANCE_TABLE10_CFM = 0x47B3
****************************************************************************/
void SendApiFpLlmeGetPerformanceTable10Cfm ( RosTaskIdType Dst,
                                             RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */
                                             rsuint8 HandsetId,
                                                             /*!< Receiving info from Pp */
                                             rsuint32 PerformanceHandovers,
                                                             /*!< Number of Handovers in
                                                                last call */
                                             rsuint32 PerformanceSyncFailures,
                                                             /*!< SyncFailures in last
                                                                call */
                                             rsuint32 PerformanceControlFieldErrs,
                                                             /*!<
                                                                PerformanceControlFieldErrs
                                                                in last call (ACRC) */
                                             rsuint32 PerformancePayloadErrs,
                                                             /*!< PerformancePayloadErrs
                                                                in call (XCRC) */
                                             rsuint32 PerformanceSlidingCollisions,
                                                             /*!<
                                                                PerformanceSlidingCollisions
                                                                in last call (ZCRC) */
                                             rsuint32 PerformanceLinkErrsQbit);
                                                             /*!<
                                                                PerformanceLinkErrsQbit in
                                                                last call (QErr) */

#ifdef __cplusplus
}
#endif
#endif /*APIFPLLME10MPS_H */


