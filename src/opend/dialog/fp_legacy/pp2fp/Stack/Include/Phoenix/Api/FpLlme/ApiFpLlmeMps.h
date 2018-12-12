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
#ifndef APIFPLLMEMPS_H
#define APIFPLLMEMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpLlme/ApiFpLlme.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpLlmeGetRssiCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LLME_GET_RSSI_CFM = 0x47B1
****************************************************************************/
void SendApiFpLlmeGetRssiCfm ( RosTaskIdType Dst,
                               RsStatusType Status,          /*!< Indicates whether the
                                                                command succeeded or not.
                                                                Command will only report
                                                                SUCCESS if connection is
                                                                active. */
                               ApiTerminalIdType TerminalId,
                                                             /*!< Selected Pp */
                               rsuint8 Rssi);                /*!< Received Signal
                                                                Strength Indication for the
                                                                selected Pp. Range
                                                                0x00-0x3F. */

/****************************************************************************
* FUNCTION:      SendApiFpLlmeGetPerformanceTableCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LLME_GET_PERFORMANCE_TABLE_CFM = 0x47B3
****************************************************************************/
void SendApiFpLlmeGetPerformanceTableCfm ( RosTaskIdType Dst,
                                           RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */
                                           ApiTerminalIdType TerminalId,
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

/****************************************************************************
* FUNCTION:      SendApiFpLlmeSetFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LLME_SET_FEATURES_CFM = 0x47B5
****************************************************************************/
void SendApiFpLlmeSetFeaturesCfm ( RosTaskIdType Dst,
                                   RsStatusType Status,      /*!<  */
                                   ApiFpLlmeFeatureType ApiFpLlmeFeature);
                                                             /*!< Supported features */

/****************************************************************************
* FUNCTION:      SendApiFpLlmeGetFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LLME_GET_FEATURES_CFM = 0x41B7
****************************************************************************/
void SendApiFpLlmeGetFeaturesCfm ( RosTaskIdType Dst,
                                   ApiFpLlmeFeatureType CurrentFeatures,
                                                             /*!< Current feature
                                                                settings */
                                   ApiFpLlmeFeatureType AvailableFeatures);
                                                             /*!< Available feature
                                                                settings */

#ifdef __cplusplus
}
#endif
#endif /*APIFPLLMEMPS_H */


