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
#ifndef APIFPULEMPS_H
#define APIFPULEMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpUle/ApiFpUle.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpUleInitCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_INIT_CFM = 0x4189
****************************************************************************/
void SendApiFpUleInitCfm ( RosTaskIdType Dst,
                           RsStatusType Status,              /*!< Indicates whether the
                                                                command succeeded or not. */
                           rsuint16 MaxUlpDevices,           /*!< Maximum ULE devices
                                                                supported by the FP.
                                                                 0 if not known. */
                           rsuint16 UpLinkBuffers);          /*!< Number of ULE uplink
                                                                buffers allocated.
                                                                 0 if not known */

/****************************************************************************
* FUNCTION:      SendApiFpUlePvcConfigCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_PVC_CONFIG_CFM=0x41A3
****************************************************************************/
void SendApiFpUlePvcConfigCfm ( RosTaskIdType Dst,
                                ApiTerminalIdType TerminalId,
                                                             /*!< Terminal Id. */
                                ApiFpUleProtocolId_t ProtocolId,
                                                             /*!< ULE protocol */
                                ApiFpUleMtuSize_t MtuPtSize,  /*!< MTU size in PT->FT
                                                                 direction */
                                ApiFpUleMtuSize_t MtuFtSize,  /*!< MTU size in FT->PT
                                                                 direction */
                                ApiFpUleMtuLifetime_t MtuLifetime,
                                                             /*!< MAC layer maximum 
                                                                lifetime */
                                ApiFpUleWindowSize_t WindowSize);
                                                             /*!< DLC layer window size */

/****************************************************************************
* FUNCTION:      SendApiFpUlePvcConfigRej
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_PVC_CONFIG_REJ=0x41A4
****************************************************************************/
void SendApiFpUlePvcConfigRej ( RosTaskIdType Dst,
                                ApiTerminalIdType TerminalId,
                                                             /*!< Terminal Id. */
                                ApiFpUleError_t Reason,      /*!< Indicates why the PVC
                                                                configuration failed */
                                rsuint16 Value);             /*!< If  possible, value of
                                                                 rejected parameter */

/****************************************************************************
* FUNCTION:      SendApiFpUlePvcConfigInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_PVC_CONFIG_IND=0x41A5
****************************************************************************/
void SendApiFpUlePvcConfigInd ( RosTaskIdType Dst,
                                ApiTerminalIdType TerminalId);
                                                             /*!< Terminal Id. */

/****************************************************************************
* FUNCTION:      SendApiFpUlePvcPendingInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_PVC_PENDING_IND=0x41A6
****************************************************************************/
void SendApiFpUlePvcPendingInd ( RosTaskIdType Dst,
                                 ApiTerminalIdType TerminalId,
                                                             /*!< Terminal Id. */
                                 ApiFpUleProtocolId_t ProtocolId);
                                                             /*!< ID of the ULE selected
                                                                protocol */

/****************************************************************************
* FUNCTION:      SendApiFpUlePvcIwuDataInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_PVC_IWU_DATA_IND=0x41A9
****************************************************************************/
void SendApiFpUlePvcIwuDataInd ( RosTaskIdType Dst,
                                 ApiTerminalIdType TerminalId,
                                                             /*!< Terminal Id. */
                                 rsuint16 InfoElementLength,  /*!< The length of the
                                                                 Data Information Element */
                                 rsuint8 InfoElement[1]);    /*!< The InfoElementList
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
                                                                 */

/****************************************************************************
* FUNCTION:      SendApiFpUleGetRegistrationCountCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_GET_REGISTRATION_COUNT_CFM = 0x418D
****************************************************************************/
void SendApiFpUleGetRegistrationCountCfm ( RosTaskIdType Dst,
                                           RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */
                                           rsuint8 MaxNoHs,  /*!< Max numbers of
                                                                handsets bit used, always
                                                                placed in start of bitmask
                                                                and always zero, may be used
                                                                as offset into
                                                                DeviceIdBitArr */
                                           rsuint8 MaxNoDevices,
                                                             /*!< The maximum number of
                                                                ULE devices that can be
                                                                registered. */
                                           rsuint8 NoDevices,
                                                             /*!< The number of ULE
                                                                devices registered
                                                                currently. */
                                           rsuint8 Length,   /*!< Byte length of
                                                                DeviceIdBitArr */
                                           rsuint8 DeviceIdBitArr[1]);
                                                             /*!< Bit array of
                                                                registered ULE device Id?s. */

/****************************************************************************
* FUNCTION:      SendApiFpUleDeleteRegistrationCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_DELETE_REGISTRATION_CFM = 0x4193
****************************************************************************/
void SendApiFpUleDeleteRegistrationCfm ( RosTaskIdType Dst,
                                         RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */
                                         ApiTerminalIdType TerminalId);
                                                             /*!< The Id of the deleted
                                                                device. */

/****************************************************************************
* FUNCTION:      SendApiFpUleGetDeviceIpuiCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_GET_DEVICE_IPUI_CFM = 0x418F
****************************************************************************/
void SendApiFpUleGetDeviceIpuiCfm ( RosTaskIdType Dst,
                                    RsStatusType Status,     /*!< Indicates whether the
                                                                command succeeded or not. */
                                    ApiTerminalIdType TerminalId,
                                                             /*!< The Id for which the
                                                                IPUI is read. */
                                    rsuint8 IPUI[5]);        /*!< The IPUI. */

/****************************************************************************
* FUNCTION:      SendApiFpUleDataInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_DATA_IND = 0x4185
****************************************************************************/
void SendApiFpUleDataInd ( RosTaskIdType Dst,
                           ApiTerminalIdType TerminalId,     /*!< Portable part number */
                           rsuint16 Length,                  /*!< Length of data */
                           rsuint8 Data[1]);                 /*!< Data. */

/****************************************************************************
* FUNCTION:      SendApiFpUleDtrInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_DTR_IND = 0x4187
****************************************************************************/
void SendApiFpUleDtrInd ( RosTaskIdType Dst,
                          ApiTerminalIdType TerminalId,      /*!< Portable part number */
                          RsStatusType Status);              /*!< Status of last data
                                                                transmission,  RSS_SUCCESS
                                                                if data has been transmitted
                                                                and acknowledge  otherwise 
                                                                RSS_FAILED. */

/****************************************************************************
* FUNCTION:      SendApiFpUleDataCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_DATA_CFM = 0x418B
****************************************************************************/
void SendApiFpUleDataCfm ( RosTaskIdType Dst,
                           ApiTerminalIdType TerminalId,     /*!< Portable part number */
                           RsStatusType Status);             /*!< Status for the data
                                                                request */

void SendApiFpUleDatapoll( RosTaskIdType Dst,
        ApiTerminalIdType TerminalId,
        rsuint16 Value,
        rsuint8 Data[1]);
/****************************************************************************
* FUNCTION:      SendApiFpUleFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_FEATURES_CFM = 0x41A1
****************************************************************************/
void SendApiFpUleFeaturesCfm ( RosTaskIdType Dst,
                               RsStatusType Status,          /*!<  */
                               ApiFpUleFeatureType ApiFpUleFeature);
                                                             /*!< Supported features */

#ifdef __cplusplus
}
#endif
#endif /*APIFPULEMPS_H */


