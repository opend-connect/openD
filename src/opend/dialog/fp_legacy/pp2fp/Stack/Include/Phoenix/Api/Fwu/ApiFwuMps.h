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
#ifndef APIFWUMPS_H
#define APIFWUMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <FWU/Api/ApiFwu.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFwuEnableCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_ENABLE_CFM = 0x4F01
****************************************************************************/
void SendApiFwuEnableCfm ( RosTaskIdType Dst,
                           RsStatusType Status);             /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFwuDeviceNotifyInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_DEVICE_NOTIFY_IND = 0x4F02
****************************************************************************/
void SendApiFwuDeviceNotifyInd ( RosTaskIdType Dst,
                                 rsuint8 Present,            /*!< 0: absent 
                                                                1: present */
                                 ApiTerminalIdType DeviceNr,  /*!< Device number. 0 = FP
                                                                  (1..n=PP's) */
                                 rsuint32 DeviceId,          /*!< Unique device id. */
                                 rsuint32 TargetData,        /*!< Information block
                                                                offset in area. */
                                 ApiFwuModeType FwuMode,     /*!< FWU Mode. */
                                 rsuint8 LinkDate[5],        /*!< The link date of the
                                                                current FW in the device. */
                                 ApiFwuRangeType Range);     /*!< The start address and
                                                                the size of the FW in the
                                                                target device. */

/****************************************************************************
* FUNCTION:      SendApiFwuUpdateCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_UPDATE_CFM = 0x4F04
****************************************************************************/
void SendApiFwuUpdateCfm ( RosTaskIdType Dst,
                           ApiTerminalIdType DeviceNr,       /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                           RsStatusType Status);             /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFwuUpdateInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_UPDATE_IND = 0x4F05
****************************************************************************/
void SendApiFwuUpdateInd ( RosTaskIdType Dst,
                           ApiTerminalIdType DeviceNr,       /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                           rsuint32 DeviceId,                /*!< Unique device id. */
                           rsuint32 TargetData,              /*!< Information block
                                                                offset in area. */
                           ApiFwuModeType FwuMode,           /*!< FWU Mode. */
                           rsuint8 LinkDate[5],              /*!< The link date of the
                                                                current FW in the device. */
                           ApiFwuRangeType Range);           /*!< The start address and
                                                                the size of the FW in the
                                                                target. */

/****************************************************************************
* FUNCTION:      SendApiFwuGetBlockInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_GET_BLOCK_IND = 0x4F07
****************************************************************************/
void SendApiFwuGetBlockInd ( RosTaskIdType Dst,
                             ApiTerminalIdType DeviceNr,     /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                             rsuint32 PrvContext,            /*!< Provider context;
                                                                identifies the FWU session. */
                             rsuint32 Address,               /*!< Current address. */
                             rsuint32 Size);                 /*!< Max size of returned
                                                                block. */

/****************************************************************************
* FUNCTION:      SendApiFwuGetCrcInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_GET_CRC_IND = 0x4F09
****************************************************************************/
void SendApiFwuGetCrcInd ( RosTaskIdType Dst,
                           ApiTerminalIdType DeviceNr,       /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                           rsuint32 PrvContext,              /*!< Provider context;
                                                                identifies the FWU session. */
                           rsuint32 Address,                 /*!< Current address. */
                           rsuint32 Size);                   /*!< Max size of block
                                                                CRC?ed. */

/****************************************************************************
* FUNCTION:      SendApiFwuCompleteInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_COMPLETE_IND = 0x4F0B
****************************************************************************/
void SendApiFwuCompleteInd ( RosTaskIdType Dst,
                             rsuint32 PrvContext);           /*!< Provider context;
                                                                identifies the FWU session. */

/****************************************************************************
* FUNCTION:      SendApiFwuStatusInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_STATUS_IND = 0x4F0C
****************************************************************************/
void SendApiFwuStatusInd ( RosTaskIdType Dst,
                           ApiTerminalIdType BusyDeviceNr,   /*!< The id of the device
                                                                being updated currently.
                                                                0xFF is used if no device is
                                                                active. */
                           rsuint8 StatusLength,             /*!< Size of Status[]. */
                           rsuint8
 Status[1]);              /*!< The FWU status of each
                                                                device in the system. */

/****************************************************************************
* FUNCTION:      SendApiFwuMultiCrcInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_MULTI_CRC_IND = 0x4F0D
****************************************************************************/
void SendApiFwuMultiCrcInd ( RosTaskIdType Dst,
                             ApiTerminalIdType DeviceNr,     /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                             rsuint32 PrvContext,            /*!< Provider context;
                                                                identifies the FWU session. */
                             rsuint32 Address,               /*!< Current address. */
                             rsuint8 CrcSizesCount,          /*!< The number of CRC
                                                                sizes. */
                             rsuint16 CrcSizes[1]);          /*!< Array holding the size
                                                                of each block to caculate
                                                                CRC over. The size of
                                                                CrcSizes[] is
                                                                CrcSizesCount*sizeof
                                                                (rsuint16). */

/****************************************************************************
* FUNCTION:      SendApiFwuSetFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_SET_FEATURES_CFM = 0x4F11
****************************************************************************/
void SendApiFwuSetFeaturesCfm ( RosTaskIdType Dst,
                                RsStatusType Status,         /*!<  */
                                ApiFwuFeatureType ApiFwuFeature);
                                                             /*!< Supported features */

/****************************************************************************
* FUNCTION:      SendApiFwuGetFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWU_GET_FEATURES_CFM = 0x4F13
****************************************************************************/
void SendApiFwuGetFeaturesCfm ( RosTaskIdType Dst,
                                ApiFwuFeatureType CurrentFeatures,
                                                             /*!< Current feature
                                                                settings */
                                ApiFwuFeatureType AvailableFeatures);
                                                             /*!< Available feature
                                                                settings */

#ifdef __cplusplus
}
#endif
#endif /*APIFWUMPS_H */


