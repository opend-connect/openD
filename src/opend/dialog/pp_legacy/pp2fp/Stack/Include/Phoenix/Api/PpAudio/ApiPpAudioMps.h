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
#ifndef APIPPAUDIOMPS_H
#define APIPPAUDIOMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/PpAudio/ApiPpAudio.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiPpAudioStartToneCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_TONE_CFM = 0x5314
****************************************************************************/
void SendApiPpAudioStartToneCfm ( RosTaskIdType Dst,
                                  RsStatusType Status);      /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopToneCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_TONE_CFM = 0x5315
****************************************************************************/
void SendApiPpAudioStopToneCfm ( RosTaskIdType Dst,
                                 RsStatusType Status);       /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioToneEndInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_TONE_END_IND = 0x5313
****************************************************************************/
void SendApiPpAudioToneEndInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpAudioStartMidiCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_MIDI_CFM = 0x5316
****************************************************************************/
void SendApiPpAudioStartMidiCfm ( RosTaskIdType Dst,
                                  RsStatusType Status);      /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopMidiCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_MIDI_CFM = 0x5317
****************************************************************************/
void SendApiPpAudioStopMidiCfm ( RosTaskIdType Dst,
                                 RsStatusType Status);       /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioMidiEndInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_MIDI_END_IND = 0x530D
****************************************************************************/
void SendApiPpAudioMidiEndInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpAudioStartMediaSeqCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_MEDIA_SEQ_CFM = 0x5318
****************************************************************************/
void SendApiPpAudioStartMediaSeqCfm ( RosTaskIdType Dst,
                                      RsStatusType Status);  /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopMediaSeqCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_MEDIA_SEQ_CFM = 0x5319
****************************************************************************/
void SendApiPpAudioStopMediaSeqCfm ( RosTaskIdType Dst,
                                     RsStatusType Status);   /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStartTextToSpeechCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_TEXT_TO_SPEECH_CFM = 0x531b
****************************************************************************/
void SendApiPpAudioStartTextToSpeechCfm ( RosTaskIdType Dst,
                                          RsStatusType Status);
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopTextToSpeechCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_TEXT_TO_SPEECH_CFM = 0x531d
****************************************************************************/
void SendApiPpAudioStopTextToSpeechCfm ( RosTaskIdType Dst,
                                         RsStatusType Status);
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioTextToSpeechEndInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_TEXT_TO_SPEECH_END_IND=0x531e
****************************************************************************/
void SendApiPpAudioTextToSpeechEndInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpAudioStartDtmfCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_DTMF_CFM = 0x5320
****************************************************************************/
void SendApiPpAudioStartDtmfCfm ( RosTaskIdType Dst,
                                  RsStatusType Status);      /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopDtmfCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_DTMF_CFM = 0x5322
****************************************************************************/
void SendApiPpAudioStopDtmfCfm ( RosTaskIdType Dst,
                                 RsStatusType Status);       /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioInfoVoiceDetectionInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_INFO_VOICE_DETECTION_IND  = 0x5327
****************************************************************************/
void SendApiPpAudioInfoVoiceDetectionInd ( RosTaskIdType Dst,
                                           ApiPpAudioDetectStatusType DetectStatus);
                                                             /*!< 0 = voice "off"
                                                                detected 
                                                                1 = voice "on" detected */

/****************************************************************************
* FUNCTION:      SendApiPpAudioInitPcmCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_INIT_PCM_CFM = 0x532B
****************************************************************************/
void SendApiPpAudioInitPcmCfm ( RosTaskIdType Dst,
                                RsStatusType Status);        /*!< Indicates whether the
                                                                command succeeded or not. */

#ifdef __cplusplus
}
#endif
#endif /*APIPPAUDIOMPS_H */


