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
#ifndef APIFPFWU10MPS_H
#define APIFPFWU10MPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpFwu/ApiFpFwu10.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpFwuDeviceNotify10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_DEVICE_NOTIFY10_IND = 0x4F02
****************************************************************************/
void SendApiFpFwuDeviceNotify10Ind ( RosTaskIdType Dst,
                                     rsuint8 Present,        /*!< 0: absent 
                                                                1: present */
                                     rsuint8 DeviceNr,       /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                                     rsuint32 DeviceId,      /*!< Unique device id. */
                                     rsuint32 TargetData,    /*!< Information block
                                                                offset in area. */
                                     ApiFwuModeType FwuMode,  /*!< FWU Mode. */
                                     rsuint8 LinkDate[5],    /*!< The link date of the
                                                                current FW in the device. */
                                     ApiFwuRangeType Range);  /*!< The start address and
                                                                 the size of the FW in the
                                                                 target device. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuUpdate10Cfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_UPDATE10_CFM = 0x4F04
****************************************************************************/
void SendApiFpFwuUpdate10Cfm ( RosTaskIdType Dst,
                               rsuint8 DeviceNr,             /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                               RsStatusType Status);         /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuUpdate10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_UPDATE10_IND = 0x4F05
****************************************************************************/
void SendApiFpFwuUpdate10Ind ( RosTaskIdType Dst,
                               rsuint8 DeviceNr,             /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                               rsuint32 DeviceId,            /*!< Unique device id. */
                               rsuint32 TargetData,          /*!< Information block
                                                                offset in area. */
                               ApiFwuModeType FwuMode,       /*!< FWU Mode. */
                               rsuint8 LinkDate[5],          /*!< The link date of the
                                                                current FW in the device. */
                               ApiFwuRangeType Range);       /*!< The start address and
                                                                the size of the FW in the
                                                                target. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuGetBlock10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_GET_BLOCK10_IND = 0x4F07
****************************************************************************/
void SendApiFpFwuGetBlock10Ind ( RosTaskIdType Dst,
                                 rsuint8 DeviceNr,           /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                                 rsuint32 PrvContext,        /*!< Provider context;
                                                                identifies the FWU session. */
                                 rsuint32 Address,           /*!< Current address. */
                                 rsuint32 Size);             /*!< Max size of returned
                                                                block. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuGetCrc10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_GET_CRC10_IND = 0x4F09
****************************************************************************/
void SendApiFpFwuGetCrc10Ind ( RosTaskIdType Dst,
                               rsuint8 DeviceNr,             /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                               rsuint32 PrvContext,          /*!< Provider context;
                                                                identifies the FWU session. */
                               rsuint32 Address,             /*!< Current address. */
                               rsuint32 Size);               /*!< Max size of block
                                                                CRC?ed. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuStatus10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_STATUS10_IND = 0x4F0C
****************************************************************************/
void SendApiFpFwuStatus10Ind ( RosTaskIdType Dst,
                               rsuint8 BusyDeviceNr,         /*!< The id of the device
                                                                being updated currently.
                                                                0xFF is used if no device is
                                                                active. */
                               rsuint8 StatusLength,         /*!< Size of Status[]. */
                               rsuint8
 Status[1]);          /*!< The FWU status of each
                                                                device in the system. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuMultiCrc10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_MULTI_CRC10_IND = 0x4F0D
****************************************************************************/
void SendApiFpFwuMultiCrc10Ind ( RosTaskIdType Dst,
                                 rsuint8 DeviceNr,           /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                                 rsuint32 PrvContext,        /*!< Provider context;
                                                                identifies the FWU session. */
                                 rsuint32 Address,           /*!< Current address. */
                                 rsuint8 CrcSizesCount,      /*!< The number of CRC
                                                                sizes. */
                                 rsuint16 CrcSizes[1]);      /*!< Array holding the size
                                                                of each block to caculate
                                                                CRC over. The size of
                                                                CrcSizes[] is
                                                                CrcSizesCount*sizeof
                                                                (rsuint16). */

#ifdef __cplusplus
}
#endif
#endif /*APIFPFWU10MPS_H */


