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
#ifndef APIPPULEMPS_H
#define APIPPULEMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/PpUle/ApiPpUle.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiPpUleInitCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_INIT_CFM=0x5A01
****************************************************************************/
void SendApiPpUleInitCfm ( RosTaskIdType Dst,
                           rsbool IsUlpWakeup,               /*!< Indicates whether
                                                                startup was a ULE wake-up or
                                                                cold boot. */
                           ApiPpUleWakeupEventType_t WakeupEvent,
                                                             /*!< Wakeup event type */
                           ApiPpUleActivityStatus_t ActivityStatus,
                                                             /*!< Activity status */
                           rsuint8 BpaStatus,                /*!< Performance data for
                                                                BPA  (For debug usage) */
                           rsuint16 ResumeCounter,           /*!< Activity counter */
                           rsuint16 DbgDataLength,           /*!< Length of debug data  
                                                                (default =0) */
                           rsuint8* DbgDataPtr);             /*!< Pointer to debug data 
                                                                (default= NULL) */

/****************************************************************************
* FUNCTION:      SendApiPpUlePvcConfigCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_PVC_CONFIG_CFM=0x5A28
****************************************************************************/
void SendApiPpUlePvcConfigCfm ( RosTaskIdType Dst,
                                ApiPpUleProtocolVer_t ProtocolVer,
                                                             /*!< Peer Protocol version */
                                ApiPpUleMtuSize_t MtuPtSize,  /*!< MTU size in PT->FT
                                                                 direction */
                                ApiPpUleMtuSize_t MtuFtSize,  /*!< MTU size in FT->PT
                                                                 direction */
                                ApiPpUleMtuLifetime_t MtuLifetime,
                                                             /*!< MAC layer maximum 
                                                                lifetime */
                                ApiPpUleWindowSize_t WindowSize,
                                                             /*!< DLC layer window size */
                                ApiPpUlePage_t Page_1,       /*!< Paging channel 1 */
                                ApiPpUlePage_t Page_2);      /*!< Paging Channel 2 */

/****************************************************************************
* FUNCTION:      SendApiPpUlePvcConfigRej
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_PVC_CONFIG_REJ=0x5A29
****************************************************************************/
void SendApiPpUlePvcConfigRej ( RosTaskIdType Dst,
                                ApiPpUleError_t Reason,      /*!< Indicates why the PVC
                                                                configuration failed */
                                rsuint16 Value);             /*!< If  possible, value of
                                                                rejected parameter */

/****************************************************************************
* FUNCTION:      SendApiPpUlePvcConfigInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_PVC_CONFIG_IND=0x5A2E
****************************************************************************/
void SendApiPpUlePvcConfigInd ( RosTaskIdType Dst,
                                ApiPpUleError_t Reason);     /*!< Indicates why the PVC
                                                                configuration is needed */

/****************************************************************************
* FUNCTION:      SendApiPpUlePvcPendingInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_PVC_PENDING_IND=0x5A2A
****************************************************************************/
void SendApiPpUlePvcPendingInd ( RosTaskIdType Dst,
                                 ApiPpUleProtocolId_t ProtocolId);
                                                             /*!< ID of the ULE selected
                                                                protocol */

/****************************************************************************
* FUNCTION:      SendApiPpUlePvcIwuDataInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_PVC_IWU_DATA_IND=0x5A2D
****************************************************************************/
void SendApiPpUlePvcIwuDataInd ( RosTaskIdType Dst,
                                 rsuint16 InfoElementLength,  /*!< Data length */
                                 rsuint8 InfoElement[1]);    /*!< Data */

/****************************************************************************
* FUNCTION:      SendApiPpUleSetupAgainInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_SETUP_AGAIN_IND=0x5A2F
****************************************************************************/
void SendApiPpUleSetupAgainInd ( RosTaskIdType Dst,
                                 rsuint16 Delay);            /*!< Delay in ms */

/****************************************************************************
* FUNCTION:      SendApiPpUleStartLocateInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_START_LOCATE_IND=0x5A30
****************************************************************************/
void SendApiPpUleStartLocateInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpUleHighPagingModeInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_HIGH_PAGING_MODE_IND=0x5A31
****************************************************************************/
void SendApiPpUleHighPagingModeInd ( RosTaskIdType Dst,
                                     rsuint16 Delay);        /*!< Delay in ms */

/****************************************************************************
* FUNCTION:      SendApiPpUleLcePagingModeInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_LCE_PAGING_MODE_IND=0x5A32
****************************************************************************/
void SendApiPpUleLcePagingModeInd ( RosTaskIdType Dst,
                                    ApiPpUleDbPageMode_t PagingMode,
                                                             /*!< Paging mode */
                                    rsuint16 Delay);         /*!< Delay in ms */

/****************************************************************************
* FUNCTION:      SendApiPpUleStartVoiceCallInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_START_VOICE_CALL_IND=0x5A33
****************************************************************************/
void SendApiPpUleStartVoiceCallInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpUleInfoCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_INFO_CFM=0x5A09
****************************************************************************/
void SendApiPpUleInfoCfm ( RosTaskIdType Dst,
                           ApiPpUleMode_t Mode,              /*!<  */
                           rsuint32 UlpTimer);               /*!<  */

/****************************************************************************
* FUNCTION:      SendApiPpUleSubsStatusCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_SUBS_STATUS_CFM=0x5A1F
****************************************************************************/
void SendApiPpUleSubsStatusCfm ( RosTaskIdType Dst,
                                 RsStatusType Status);       /*!< RSS_SUCCESS:
                                                                Subscription
                                                                exists.
RSS_NO_DATA: No
                                                                subscription. */

/****************************************************************************
* FUNCTION:      SendApiPpUleSubsDeleteCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_SUBS_DELETE_CFM=0x5A21
****************************************************************************/
void SendApiPpUleSubsDeleteCfm ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpUleLocateRej
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_LOCATE_REJ=0x5A34
****************************************************************************/
void SendApiPpUleLocateRej ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpUleDbPageEnableCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_DB_PAGE_ENABLE_CFM=0x5A23
****************************************************************************/
void SendApiPpUleDbPageEnableCfm ( RosTaskIdType Dst,
                                   RsStatusType Status);     /*!< RSS_SUCCESS:  Paging
                                                                is enabled */

/****************************************************************************
* FUNCTION:      SendApiPpUleResumeErrorInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_RESUME_ERROR_IND=0x5A26
****************************************************************************/
void SendApiPpUleResumeErrorInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpUleHibernateReadCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_HIBERNATE_READ_CFM=0x5A0F
****************************************************************************/
void SendApiPpUleHibernateReadCfm ( RosTaskIdType Dst,
                                    ApiPpUleNvsClientId_t nvs_client_id,
                                                             /*!<
                                                                API_PP_ULE_NVS_CLIENT_APP */
                                    rsuint8 Length,          /*!< Length of data */
                                    rsuint8 Data[1]);        /*!<  */

/****************************************************************************
* FUNCTION:      SendApiPpUleHibernateWriteCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_HIBERNATE_WRITE_CFM=0x5A11
****************************************************************************/
void SendApiPpUleHibernateWriteCfm ( RosTaskIdType Dst,
                                     ApiPpUleNvsClientId_t nvs_client_id);
                                                             /*!<
                                                                API_PP_ULE_NVS_CLIENT_APP */

/****************************************************************************
* FUNCTION:      SendApiPpUleReadyInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_READY_IND=0x5A15
****************************************************************************/
void SendApiPpUleReadyInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpUleDtrInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_DTR_IND=0x5A16
****************************************************************************/
void SendApiPpUleDtrInd ( RosTaskIdType Dst,
                          ApiPpUleError_t
 Status);          /*!< Result of pending data transmission.
                                                                API_PP_ULE_ERR_NO_ERROR: 
                                                                Data was Acknowledged.
                                                                All other means Data was
                                                                not Acknowledged. */

/****************************************************************************
* FUNCTION:      SendApiPpUleDataInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_DATA_IND=0x5A17
****************************************************************************/
void SendApiPpUleDataInd ( RosTaskIdType Dst,
                           rsbool ReadyToTransmit,           /*!< Indicates whether the
                                                                ULE-API is ready for data
                                                                transmit or not */
                           rsuint16 Length,                  /*!< Length of data */
                           rsuint8 Data[1]);                 /*!<  */

/****************************************************************************
* FUNCTION:      SendApiPpUleDataCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_DATA_CFM=0x5A25
****************************************************************************/
void SendApiPpUleDataCfm ( RosTaskIdType Dst,
                           ApiPpUleError_t Result);          /*!< RSS_SUCCESS if data is
                                                                accepted for transmission
                                                                otherwise an error code that
                                                                indicates why data couldn?t
                                                                be transmitted. */

/****************************************************************************
* FUNCTION:      SendApiPpUleDbPageInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_DB_PAGE_IND= 0x5A24
****************************************************************************/
void SendApiPpUleDbPageInd ( RosTaskIdType Dst,
                             rsuint8 PageId);                /*!< BitOffset  that
                                                                triggered this paging
                                                                message 
                                                                See A.2.1 in ETSI- TS
                                                                102-939-1 */

/****************************************************************************
* FUNCTION:      SendApiPpUleHalGetPortCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_HAL_GET_PORT_CFM=0x5A1C
****************************************************************************/
void SendApiPpUleHalGetPortCfm ( RosTaskIdType Dst,
                                 ApiPpUleGpioId_t gpio_id,   /*!< GPIO identifier */
                                 rsuint16 value);            /*!< Port value */

/****************************************************************************
* FUNCTION:      SendApiPpUleHalPortInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_HAL_PORT_IND=0x5A1D
****************************************************************************/
void SendApiPpUleHalPortInd ( RosTaskIdType Dst,
                              ApiPpUleGpioId_t gpio_id,      /*!< GPIO identifier */
                              rsuint16 value);               /*!< Port value */

#ifdef __cplusplus
}
#endif
#endif /*APIPPULEMPS_H */


