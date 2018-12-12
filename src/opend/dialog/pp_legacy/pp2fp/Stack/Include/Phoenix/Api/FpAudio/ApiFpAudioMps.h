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
#ifndef APIFPAUDIOMPS_H
#define APIFPAUDIOMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpAudio/ApiFpAudio.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpInitPcmCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_INIT_PCM_CFM = 0x4201
****************************************************************************/
void SendApiFpInitPcmCfm ( RosTaskIdType Dst,
                           RsStatusType Status);             /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpSetPcmLoopbackCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_PCM_LOOPBACK_CFM=0x4205
****************************************************************************/
void SendApiFpSetPcmLoopbackCfm ( RosTaskIdType Dst,
                                  RsStatusType Status,       /*!< Indicates whether the
                                                                command succeeded or not. */
                                  ApiAudioEndPointIdType SourceId,
                                                             /*!< The selected data
                                                                channel */
                                  ApiAudioEndPointIdType DestinationId);
                                                             /*!< The selected data
                                                                channel */

/****************************************************************************
* FUNCTION:      SendApiFpInitUsbCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_INIT_USB_CFM = 0x4207
****************************************************************************/
void SendApiFpInitUsbCfm ( RosTaskIdType Dst,
                           RsStatusType Status);             /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpSetAudioFormatCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_AUDIO_FORMAT_CFM = 0x4211
****************************************************************************/
void SendApiFpSetAudioFormatCfm ( RosTaskIdType Dst,
                                  RsStatusType Status,       /*!< Indicates whether the
                                                                command succeeded or not. */
                                  ApiAudioEndPointIdType DestinationId,
                                                             /*!< The data channel [0;n]
                                                                *The individual channels
                                                                and number of channels (n)
                                                                is depending on project
                                                                configuration. */
                                  ApiAudioDataFormatType AudioDataFormat);
                                                             /*!< The data format of the
                                                                PCM channel specified. */

/****************************************************************************
* FUNCTION:      SendApiFpAudioMuteCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_MUTE_CFM = 0x4213
****************************************************************************/
void SendApiFpAudioMuteCfm ( RosTaskIdType Dst,
                             RsStatusType Status,            /*!< Indicates whether the
                                                                command succeeded or not. */
                             ApiAudioEndPointIdType DestinationId,
                                                             /*!< The data channel [0;n]
                                                                *The individual channels
                                                                and number of channels (n)
                                                                is depending on project
                                                                configuration. */
                             ApiFpAudioMuteRxTxType MuteRxTx);
                                                             /*!< Selects the RX or TX
                                                                direction which is to be
                                                                muted */

/****************************************************************************
* FUNCTION:      SendApiFpAudioUnmuteCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_UNMUTE_CFM = 0x4215
****************************************************************************/
void SendApiFpAudioUnmuteCfm ( RosTaskIdType Dst,
                               RsStatusType Status,          /*!< Indicates whether the
                                                                command succeeded or not. */
                               ApiAudioEndPointIdType DestinationId,
                                                             /*!< The data channel [0;n]
                                                                *The individual channels
                                                                and number of channels (n)
                                                                is depending on project
                                                                configuration. */
                               ApiFpAudioMuteRxTxType MuteRxTx);
                                                             /*!< Selects the RX or TX
                                                                direction which is to be
                                                                muted */

/****************************************************************************
* FUNCTION:      SendApiFpAudioInternalCodecSetupCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_INTERNAL_CODEC_SETUP_CFM = 0x4217
****************************************************************************/
void SendApiFpAudioInternalCodecSetupCfm ( RosTaskIdType Dst,
                                           RsStatusType Status);
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpAudioSetHwSrcCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_SET_HW_SRC_CFM = 0x4219
****************************************************************************/
void SendApiFpAudioSetHwSrcCfm ( RosTaskIdType Dst,
                                 RsStatusType Status);       /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpAudioSetCodecGainCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_SET_CODEC_GAIN_CFM = 0x421B
****************************************************************************/
void SendApiFpAudioSetCodecGainCfm ( RosTaskIdType Dst,
                                     RsStatusType Status);   /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpAudioEnableEcCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_ENABLE_EC_CFM = 0x421D
****************************************************************************/
void SendApiFpAudioEnableEcCfm ( RosTaskIdType Dst,
                                 RsStatusType Status);       /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpAudioSetFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_SET_FEATURES_CFM = 0x4221
****************************************************************************/
void SendApiFpAudioSetFeaturesCfm ( RosTaskIdType Dst,
                                    RsStatusType Status,     /*!<  */
                                    ApiFpAudioFeatureType ApiFpAudioFeature);
                                                             /*!< Supported features */

/****************************************************************************
* FUNCTION:      SendApiFpAudioGetFeaturesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_GET_FEATURES_CFM = 0x4224
****************************************************************************/
void SendApiFpAudioGetFeaturesCfm ( RosTaskIdType Dst,
                                    ApiFpAudioFeatureType CurrentFeatures,
                                                             /*!< Current feature
                                                                settings */
                                    ApiFpAudioFeatureType AvailableFeatures);
                                                             /*!< Available feature
                                                                settings */

#ifdef __cplusplus
}
#endif
#endif /*APIFPAUDIOMPS_H */


