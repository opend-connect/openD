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
/*! \file
* Definition of the ApiPpAudio interface.
*/


#ifndef APIPPAUDIO_H
#define APIPPAUDIO_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
#include <Api/ApiCfg.h>
/*! The following API files must be included. */
#include <Phoenix/Api/Types/ApiTypes.h>
/*! The following API files must be included. */
#include <Phoenix/Api/AudioTypes/ApiAudioTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_PP_AUDIO_OPEN_REQ = 0x5323,
  API_PP_AUDIO_CLOSE_REQ = 0x5324,
  API_PP_AUDIO_MUTE_REQ = 0x5300,
  API_PP_AUDIO_UNMUTE_REQ = 0x5301,
  API_PP_AUDIO_SET_MODE_REQ = 0x5302,
  API_PP_AUDIO_SET_VOLUME_REQ = 0x5303,
  API_PP_AUDIO_START_TONE_REQ = 0x5306,
  API_PP_AUDIO_START_TONE_EXT_REQ = 0x5328,
  API_PP_AUDIO_START_TONE_CFM = 0x5314,
  API_PP_AUDIO_STOP_TONE_REQ = 0x5307,
  API_PP_AUDIO_STOP_TONE_CFM = 0x5315,
  API_PP_AUDIO_TONE_END_IND = 0x5313,
  API_PP_AUDIO_START_MIDI_REQ = 0x530B,
  API_PP_AUDIO_START_MIDI_EXT_REQ = 0x5329,
  API_PP_AUDIO_START_MIDI_CFM = 0x5316,
  API_PP_AUDIO_STOP_MIDI_REQ = 0x530C,
  API_PP_AUDIO_STOP_MIDI_CFM = 0x5317,
  API_PP_AUDIO_MIDI_END_IND = 0x530D,
  API_PP_AUDIO_SET_ACTIVE_SOUND_VOLUME_REQ = 0x530E,
  API_PP_AUDIO_TEST_CMD_REQ = 0x530F,
  API_PP_AUDIO_START_MEDIA_SEQ_REQ = 0x5310,
  API_PP_AUDIO_START_MEDIA_SEQ_CFM = 0x5318,
  API_PP_AUDIO_STOP_MEDIA_SEQ_REQ = 0x5311,
  API_PP_AUDIO_STOP_MEDIA_SEQ_CFM = 0x5319,
  API_PP_AUDIO_MEDIA_SEQ_END_IND = 0x5312,
  API_PP_AUDIO_START_TEXT_TO_SPEECH_REQ = 0x531a,
  API_PP_AUDIO_START_TEXT_TO_SPEECH_CFM = 0x531b,
  API_PP_AUDIO_STOP_TEXT_TO_SPEECH_REQ = 0x531c,
  API_PP_AUDIO_STOP_TEXT_TO_SPEECH_CFM = 0x531d,
  API_PP_AUDIO_TEXT_TO_SPEECH_END_IND=0x531e,
  API_PP_AUDIO_START_DTMF_REQ = 0x531f,
  API_PP_AUDIO_START_DTMF_CFM = 0x5320,
  API_PP_AUDIO_STOP_DTMF_REQ = 0x5321,
  API_PP_AUDIO_STOP_DTMF_CFM = 0x5322,
  API_PP_AUDIO_START_VOICE_DETECTION_REQ = 0x5325,
  API_PP_AUDIO_STOP_VOICE_DETECTION_REQ = 0x5326,
  API_PP_AUDIO_INFO_VOICE_DETECTION_IND  = 0x5327,
  API_PP_AUDIO_INIT_PCM_REQ = 0x532A,
  API_PP_AUDIO_INIT_PCM_CFM = 0x532B,
End of mail primitives. */




/*! This enum defines the status of the cradle detection to the MMI */
typedef enum RSENUMTAG(ApiPpAudioMuteRxTxType)
{
  API_MUTE_RX   = 0x01, /*!< Mute audio direction RX (Speaker) */
  API_MUTE_TX   = 0x02, /*!< Mute audio direction TX (Microphone) */
  API_MUTE_BOTH = 0x03  /*!< Mute both audio directions RX and TX (Speaker and Mic) */
} RSENUM8(ApiPpAudioMuteRxTxType);

/*! This enum defines the destination Ids for starttone_req, thus output
   for tones.
    Destinations can be or?rd if tone should be routed to more destinations at
   the same time (only supported by some systems, otherwise behavior
   undefined). */
typedef enum RSENUMTAG(ApiPpToneLsrDeviceId)
{
  API_TONE_NO_LSR            = 0x00, /*!< No destinationId */
  API_TONE_EARPIECE_LSR      = 0x01, /*!< Tone output through the earpiece */
  API_TONE_HANDSFREE_LSR     = 0x02, /*!< Tone output through the Speakerphone */
  API_TONE_HEADSET_LSR       = 0x04, /*!< Tone output through the Headset */
  API_TONE_PCM0_LSR          = 0x08, /*!< Tone output through the PCM channel 0 */
  API_TONE_CURRENT_LSR_MIX   = 0x80, /*!< Tone output through the current source without
                                        mute */
  API_TONE_EARPIECE_LSR_MIX  = 0x81, /*!< Tone output through the earpiece, without mute */
  API_TONE_HANDSFREE_LSR_MIX = 0x82, /*!< Tone output through the Speakerphone, without
                                        mute */
  API_TONE_PCM0_LSR_MIX      = 0x88, /*!< Tone output through the PCM channel 0, without
                                        mute */
  API_TONE_HEADSET_LSR_MIX   = 0x84  /*!< Tone output through the Headset, without mute */
} RSENUM8(ApiPpToneLsrDeviceId);

/*! This enum defines the tones to the MMI. */
typedef enum RSENUMTAG(ApiPpAudioModeType)
{
  API_AUDIO_MODE_EARPIECE      = 0x00, /*!< PP Audio output through the earpiece */
  API_AUDIO_MODE_HEADSET       = 0x01, /*!< PP Audio output through the earpiece */
  API_AUDIO_MODE_HANDSFREE     = 0x02, /*!< PP Audio output through the Handsfree
                                          speakerphone */
  API_AUDIO_MODE_PCM0          = 0x03, /*!< PP Audio output through the PCM 0 channel */
  API_AUDIO_MODE_I2S_SW_LEFT   = 0x10, /*!< PP Audio output mode I2S, Subwoofer, left
                                          channel */
  API_AUDIO_MODE_I2S_SW_RIGHT  = 0x11, /*!< PP Audio output mode I2S, Subwoofer, right
                                          channel */
  API_AUDIO_MODE_I2S_SW_MIX    = 0x12, /*!< PP Audio output mode I2S, Subwoofer,
                                          left/right mix */
  API_AUDIO_MODE_USB_RX_STEREO = 0x13, /*!< PP Audio output mode USB, 48KHz stereo Rx
                                          only */
} RSENUM8(ApiPpAudioModeType);

/*! This enum defines the mic device for voice detection */
typedef enum RSENUMTAG(ApiPpAudioMicDeviceIdType)
{
  API_AUDIO_NO_MIC_OFF    = 0x00, /*!< Mic off */
  API_AUDIO_EARPIECE_MIC  = 0x01, /*!< Earpiece mic */
  API_AUDIO_HANDSFREE_MIC = 0x02, /*!< Handsfree mic */
  API_AUDIO_HEADSET_MIC   = 0x04, /*!< Headset mic */
  API_AUDIO_PCM0_MIC      = 0x08, /*!< PCM 0 channel mic */
} RSENUM8(ApiPpAudioMicDeviceIdType);

/*! This enum defines the audio test cmd req id's. */
typedef enum RSENUMTAG(ApiPpAudioTestCmdType)
{
  API_BYPASS_MODE_ON  = 0x00, /*!< Bypass all signal processing */
  API_BYPASS_MODE_OFF = 0x01, /*!< Bypass mode off */
} RSENUM8(ApiPpAudioTestCmdType);

/*! This enum defines the status of voice detection. */
typedef enum RSENUMTAG(ApiPpAudioDetectStatusType)
{
  API_AUDIO_DETECT_STATUS_OFF = 0x00, /*!< voice "off" detected */
  API_AUDIO_DETECT_STATUS_ON  = 0x01, /*!< voice "on" detected */
} RSENUM8(ApiPpAudioDetectStatusType);


/*! Mail without parameters. */
typedef struct ApippaudioEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApippaudioEmptySignalType;

/*! This mail is used by the MMI to open the PP audio output device. */
typedef struct ApiPpAudioOpenReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_OPEN_REQ = 0x5323 */
  ApiPpAudioModeType AudioMode;         /*!< Audio output mode selection */
} ApiPpAudioOpenReqType;

/*! This mail is used by the MMI to close PP audio output device. */
typedef ApippaudioEmptySignalType ApiPpAudioCloseReqType;

/*! This mail is used by the MMI to mute the microphone. */
typedef struct ApiPpAudioMuteReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_MUTE_REQ = 0x5300 */
  ApiPpAudioMuteRxTxType MuteRxTx;      /*!< Selects the RX or TX direction which is to
                                           be muted */
} ApiPpAudioMuteReqType;

/*! This mail is used by the MMI to unmute the microphone. */
typedef struct ApiPpAudioUnmuteReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_UNMUTE_REQ = 0x5301 */
  ApiPpAudioMuteRxTxType MuteRxTx;      /*!< Selects the RX or TX direction which is to
                                           be muted */
} ApiPpAudioUnmuteReqType;

/*! This mail is used by the MMI to set the PP audio output device. */
typedef struct ApiPpAudioSetModeReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_SET_MODE_REQ = 0x5302 */
  ApiPpAudioModeType AudioMode;         /*!< Audio output mode selection */
} ApiPpAudioSetModeReqType;

/*! This mail is used by the MMI to set the PP audio volume. */
typedef struct ApiPpAudioSetVolumeReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_SET_VOLUME_REQ = 0x5303 */
  rsuint8 VolumeStep;                   /*!< Selectable Volume steps [0..5] */
} ApiPpAudioSetVolumeReqType;

/*! This mail is by the MMI to request the API to start a selected tone / melody
    *If the tone is started in API_AUDIO_MODE_EARPIECE, API_AUDIO_MODE_HEADSET
   it will be played as an inband tone.
    
    This command is not to be used in new applications. It is to be replaced
   with API_PP_AUDIO_START_TONE_EXT_REQ instead. */
typedef struct ApiPpAudioStartToneReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_TONE_REQ = 0x5306 */
  rsuint8 ToneIndex;                    /*!< The selected predefined tone */
  rsint8 VolumeDb;                      /*!< Volume setting in dB -128 <-> 127 dB */
  rsbool TrackGenVol;                   /*!< Follow general volume ( If set VolumeIndex
                                           is used as offset) */
  ApiPpToneLsrDeviceId Dest;            /*!< Destination device */
} ApiPpAudioStartToneReqType;

/*! This mail is by the MMI to request the API to start a selected tone / melody.
    
    The play type is defined by one of the following infoelements.
     
    API_IE_AUDIO_EXT_INDEX
        selects tone from preprogrammed tonetable 
       (like the original command API_PP_AUDIO_START_TONE_REQ)
    
     API_IE_AUDIO_EXT_POINTER
      Selects a preprogrammed tone table 
       (which can be programmed in COLA flash area)
    
     API_IE_AUDIO_EXT_ARRAY
      Melody data is included directly in the API mail.
    
    
    *If the tone is started in API_AUDIO_MODE_EARPIECE, API_AUDIO_MODE_HEADSET
   it will be played as an inband tone. */
typedef struct ApiPpAudioStartToneExtReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_TONE_EXT_REQ = 0x5328 */
  rsint8 VolumeDb;                      /*!< Volume setting in dB -128 <-> 127 dB */
  rsbool TrackGenVol;                   /*!< Follow general volume 
                                           ( If set VolDb is used as offset) */
  ApiPpToneLsrDeviceId Dest;            /*!< Destination device */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           One of these Infoelements are possible at a time:
                                           [API_IE_AUDIO_EXT_INDEX] 
                                           [API_IE_AUDIO_EXT_POINTER] 
                                           [API_IE_AUDIO_EXT_ARRAY] */
} ApiPpAudioStartToneExtReqType;

/*! This mail is used to confirm API_FP_AUDIO_START_TONE_REQ or a
   API_FP_AUDIO_START_TONE_EXT_REQ. */
typedef struct ApiPpAudioStartToneCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_TONE_CFM = 0x5314 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStartToneCfmType;

/*! This mail is by the MMI to request the API to stop a playing tone /
   melody */
typedef ApippaudioEmptySignalType ApiPpAudioStopToneReqType;

/*! This mail is used to confirm API_FP_AUDIO_STOP_TONE_REQ. */
typedef struct ApiPpAudioStopToneCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_STOP_TONE_CFM = 0x5315 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStopToneCfmType;

/*! This mail is by the API  to indicate to the MMI that a playing tone /
   melody has ended (played to its end) */
typedef ApippaudioEmptySignalType ApiPpAudioToneEndIndType;

/*! This mail is by the MMI to request the API to start a selected midi melody
    *midi melodies are only available in idle mode (standby with no active call).
    
    This command is not to be used in new applications. It is to be replaced
   with API_PP_AUDIO_START_MIDI_EXT_REQ instead. */
typedef struct ApiPpAudioStartMidiReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_MIDI_REQ = 0x530B */
  rsuint8 MidiMelodyIndex;              /*!< The selected midi melody to be played */
  rsint8 VolumeDb;                      /*!< Volume setting in dB -128 <-> 127 dB */
  rsbool TrackGenVol;                   /*!< Follow general volume ( If set VolumeIndex
                                           is used as offset). Only valid if supported by
                                           sw, else ignored. */
  ApiPpToneLsrDeviceId Dest;            /*!< Destination device */
} ApiPpAudioStartMidiReqType;

/*! This mail is by the MMI to request the API to start a selected midi melody
    
    The play type is defined by one of the following infoelements.
     
    API_IE_AUDIO_EXT_INDEX
        selects tone from preprogrammed tonetable 
       (like the original command API_PP_AUDIO_START_MIDI_REQ)
    
     API_IE_AUDIO_EXT_POINTER
      Selects a preprogrammed tone table 
       (which can be programmed in COLA flash area)
    
    *midi melodies are only available in idle mode (standby with no active
   call). */
typedef struct ApiPpAudioStartMidiExtReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_MIDI_EXT_REQ = 0x5329 */
  rsint8 VolumeDb;                      /*!< Volume setting in dB -128 <-> 127 dB */
  rsbool TrackGenVol;                   /*!< Follow general volume ( If set VolumeIndex
                                           is used as offset). Only valid if supported by
                                           sw, else ignored. */
  ApiPpToneLsrDeviceId Dest;            /*!< Destination device */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           One of these Infoelements are possible at a time
                                           [API_IE_AUDIO_EXT_INDEX] 
                                           [API_IE_AUDIO_EXT_POINTER] */
} ApiPpAudioStartMidiExtReqType;

/*! This mail is used to confirm API_FP_AUDIO_START_MIDI_REQ or a
   API_FP_AUDIO_START_MIDI_EXT_REQ */
typedef struct ApiPpAudioStartMidiCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_MIDI_CFM = 0x5316 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStartMidiCfmType;

/*! This mail is by the MMI  to request the API to stop a playing midi
   melody */
typedef ApippaudioEmptySignalType ApiPpAudioStopMidiReqType;

/*! This mail is used to confirm API_FP_AUDIO_STOP_MIDI_REQ. */
typedef struct ApiPpAudioStopMidiCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_STOP_MIDI_CFM = 0x5317 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStopMidiCfmType;

/*! This mail is by the API  to indicate to the MMI that a playing midi
   melody has ended (played to its end) */
typedef ApippaudioEmptySignalType ApiPpAudioMidiEndIndType;

/*! This mail is used by the MMI to request the API to set the active sound
   volume level for selected melody (3 polyphonic melody), Midi melody or
   tones. */
typedef struct ApiPpAudioSetActiveSoundVolumeReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_SET_ACTIVE_SOUND_VOLUME_REQ = 0x530E */
  rsint8 VolumeDb;                      /*!< Volume setting in dB -128 <-> 127 dB */
} ApiPpAudioSetActiveSoundVolumeReqType;

/*! This mail is used by the MMI to request the API to send a specific
   audio test command. */
typedef struct ApiPpAudioTestCmdReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_TEST_CMD_REQ = 0x530F */
  ApiPpAudioTestCmdType TestCmd;        /*!< Test Command (TBD) */
} ApiPpAudioTestCmdReqType;

/*! This mail is by the MMI to request the API to start a selected media sequence
    *media sequences  are only available in API_AUDIO_MODE_HANDSFREE  mode. */
typedef struct ApiPpAudioStartMediaSeqReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_MEDIA_SEQ_REQ = 0x5310 */
  rsuint8 Index;                        /*!< The selected media sequence to be played */
  rsint8 VolumeDb;                      /*!< Volume setting in dB -128 <-> 127 dB */
  rsbool TrackGenVol;                   /*!< Follow general volume ( If set VolumeIndex
                                           is used as offset) */
  ApiPpToneLsrDeviceId Dest;            /*!< Destination device */
} ApiPpAudioStartMediaSeqReqType;

/*! This mail is used to confirm API_FP_AUDIO_START_MEDIA_SEQ_REQ. */
typedef struct ApiPpAudioStartMediaSeqCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_MEDIA_SEQ_CFM = 0x5318 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStartMediaSeqCfmType;

/*! This mail is by the MMI  to request the API to stop a playing media
   sequence melody */
typedef ApippaudioEmptySignalType ApiPpAudioStopMediaSeqReqType;

/*! This mail is used to confirm API_FP_AUDIO_STOP_MEDIA_SEQ_REQ. */
typedef struct ApiPpAudioStopMediaSeqCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_STOP_MEDIA_SEQ_CFM = 0x5319 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStopMediaSeqCfmType;

/*! This mail is sent by the API  to indicate to the MMI that a playing
   media sequence has ended (played to its end) */
typedef ApippaudioEmptySignalType ApiPpAudioMediaSeqEndIndType;

/*! This mail is send by the MMI to request the API to start text to speech
    . */
typedef struct ApiPpAudioStartTextToSpeechReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_TEXT_TO_SPEECH_REQ = 0x531a */
  rsint8 VolumeDb;                      /*!< Volume setting in dB -128 <-> 127 dB */
  rsbool TrackGenVol;                   /*!< Follow general volume ( If set VolumeIndex
                                           is used as offset) */
  ApiPpToneLsrDeviceId Dest;            /*!< Destination device */
  rsuint8 LengthOfText;                 /*!< The number of chars to convert to speech */
  rsuint8 Buffer[1];                    /*!< The buffer containing char. */
} ApiPpAudioStartTextToSpeechReqType;

/*! This mail is used to confirm API_PP_AUDIO_START_TEXT_TO_SPEECH_REQ. */
typedef struct ApiPpAudioStartTextToSpeechCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_TEXT_TO_SPEECH_CFM = 0x531b */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStartTextToSpeechCfmType;

/*! This mail is by the MMI  to request the API to stop a playing text to
   speech sequence */
typedef ApippaudioEmptySignalType ApiPpAudioStopTextToSpeechReqType;

/*! This mail is used to confirm API_PP_AUDIO_STOP_TEXT_TO_SPEECH_REQ. */
typedef struct ApiPpAudioStopTextToSpeechCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_STOP_TEXT_TO_SPEECH_CFM = 0x531d */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStopTextToSpeechCfmType;

/*! This mail is sent by the API  to indicate to the MMI that a text to
   speech convertion has ended (played to its end) */
typedef ApippaudioEmptySignalType ApiPpAudioTextToSpeechEndIndType;

/*! This mail is by the MMI to request the API to play a DTMF tone */
typedef struct ApiPpAudioStartDtmfReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_DTMF_REQ = 0x531f */
  rsuint8 DtmfIndex;                    /*!< DTMF to play:
                                           0:DTMF 0
                                           1:DTMF 1 
                                           2:DTMF 2
                                           3:DTMF 3
                                           4:DTMF 4
                                           5:DTMF 5
                                           6:DTMF 6
                                           7:DTMF 7
                                           8:DTMF 8
                                           9:DTMF 9
                                           10:DTMF A
                                           11:DTMF B
                                           12:DTMF C
                                           13:DTMF D
                                           14:DTMF *
                                           15:DTMF # */
  rsuint16 Length;                      /*!< Time in ms. 0 means infinite, and tone must
                                           be stoped, with a stop request. */
  rsint8 VolumeDb;                      /*!< Volume setting in dB -128 <-> 127 dB */
  rsbool TrackGenVol;                   /*!< Follow general volume ( If set VolumeIndex
                                           is used as offset) */
  ApiPpToneLsrDeviceId Dest;            /*!< Destination device */
} ApiPpAudioStartDtmfReqType;

/*! This mail is used to confirm API_FP_AUDIO_START_DTMF_REQ. */
typedef struct ApiPpAudioStartDtmfCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_DTMF_CFM = 0x5320 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStartDtmfCfmType;

/*! This mail is by the MMI to request the API to stop a playing dtmf */
typedef ApippaudioEmptySignalType ApiPpAudioStopDtmfReqType;

/*! This mail is used to confirm API_FP_AUDIO_STOP_DTMF_REQ. */
typedef struct ApiPpAudioStopDtmfCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_STOP_DTMF_CFM = 0x5322 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioStopDtmfCfmType;

/*! This mail is used by the MMI to activate voicedetection. */
typedef struct ApiPpAudioStartVoiceDetectionReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_START_VOICE_DETECTION_REQ = 0x5325 */
  rsint8 Threshold;                     /*!< threshold, threshold in dB for detecting
                                           voice signal
                                           range 0 to -128 */
  rsuint16 OnTime;                      /*!< time required for detecting voice "on" in
                                           ms */
  rsuint16 OffTime;                     /*!< time required for detecting voice "off" in
                                           ms */
  ApiPpAudioMicDeviceIdType Mic;        /*!< which MIC to use in idle-mode */
} ApiPpAudioStartVoiceDetectionReqType;

/*! This mail is used by the MMI to de-activate voicedetection. */
typedef ApippaudioEmptySignalType ApiPpAudioStopVoiceDetectionReqType;

/*! This mail is used to indicate a change in voice detection to the MMI. */
typedef struct ApiPpAudioInfoVoiceDetectionIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_INFO_VOICE_DETECTION_IND  = 0x5327 */
  ApiPpAudioDetectStatusType DetectStatus; /*!< 0 = voice "off" detected 
                                               1 = voice "on" detected */
} ApiPpAudioInfoVoiceDetectionIndType;

/*! This command is used by the HOST to initialize the PCM interface. The
   PCM interface is not clocked correctly before there is an active audio
   connection. */
typedef struct ApiPpAudioInitPcmReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_INIT_PCM_REQ = 0x532A */
  rsbool PcmEnable;                     /*!< Enable or disable the PCM interface.
                                           The remaining parameters of this message are
                                           ignored by the module if the PCM interface is
                                           disabled. */
  rsbool IsMaster;                      /*!< Controls whether the device is master or
                                           slave on the PCM interface. */
  rsbool Reserved;                      /*!< For further use. Must be set to 0. */
  ApiPcmFscFreqType PcmFscFreq;         /*!< PCM  FSC frequency; 8,16, or 32kHz. */
  ApiPcmFscLengthType PcmFscLength;     /*!< The length of the FSC pulse. 1, 8, 16, 32
                                           or 48 bits. Or special slave mode setting, see
                                           type description. */
  rsbool PcmFscStartAligned ;           /*!< If true FSC starts at the same time as MSB
                                           bit of PCM channel 0 data, otherwise it starts 1
                                           clocks cycle before data. */
  ApiPcmClkType PcmClk;                 /*!< The clock frequency generated by the module
                                           if the module is master on the PCM interface.
                                           Ignored if the device is slave. */
  rsbool PcmClkOnRising;                /*!< Controls whether PCM data is clocked out on
                                           rising or falling edge of the PCM_CLK. */
  rsuint8 PcmClksPerBit;                /*!< Number of bit clocks per data bit. See
                                           datasheet for options. */
  rsbool PcmFscInvert;                  /*!< If true, FSC is inverted. */
  rsuint8 PcmCh0Delay;                  /*!< 5 bit delay value in number of 8 bits. 
                                           Delay of data bits in number of channels. */
  rsbool PcmDoutIsOpenDrain;            /*!< Controls whether PCM_DOUT is push-pull (0)
                                           or open drain (1). 
                                           Sets DSP_PCM_CTRL_REG.PCM_PPOD to the value
                                           specified by PcmDoOd. Can be used if the I/O
                                           levels (VDDIO) on the PCM interface is 1.8V. Must
                                           be set to 1 if multiple devices are connected to
                                           the PCM bus.
                                           DSP_PCM_CTRL_REG.PCM_PPOD is set to 0 after
                                           reset. */
  rsbool PcmIsOpenDrain;                /*!< Controls the PCM_DI, PCM_DO, PCM_CLK, and
                                           PCM_FSC I/O mode.
                                           0: Normal mode.
                                           1: Forced to open drain if output and pull-up
                                           resistor is always disabled if input (back-drive
                                           protection). 
                                           Sets PAD_CTRL_REG.P225_OD and
                                           PAD_CTRL_REG.P234_OD to the value specified by
                                           PcmOd. Must be set to 1 if the I/O levels (VDDIO)
                                           on the PCM interface is > 1.8V. VDDIO up to 3.45V
                                           is supported if set to 1. PAD_CTRL_REG.P225_OD
                                           and PAD_CTRL_REG.P234_OD are set to 0 after reset.
                                           Please note that PAD_CTRL_REG.P234_OD = 1
                                           overrules DSP_PCM_CTRL_REG.PCM_PPOD. */
} ApiPpAudioInitPcmReqType;

/*! This mail is used to confirm API_AUDIO_INIT_PCM_REQ. */
typedef struct ApiPpAudioInitPcmCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_AUDIO_INIT_PCM_CFM = 0x532B */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiPpAudioInitPcmCfmType;

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPopPack.h>
#else
  #pragma pack(pop)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiPpAudioOpenReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_OPEN_REQ = 0x5323
****************************************************************************/
void SendApiPpAudioOpenReq ( RosTaskIdType Src,
                             ApiPpAudioModeType AudioMode);  /*!< Audio output mode
                                                                selection */

/****************************************************************************
* FUNCTION:      SendApiPpAudioCloseReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_CLOSE_REQ = 0x5324
****************************************************************************/
void SendApiPpAudioCloseReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpAudioMuteReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_MUTE_REQ = 0x5300
****************************************************************************/
void SendApiPpAudioMuteReq ( RosTaskIdType Src,
                             ApiPpAudioMuteRxTxType MuteRxTx);
                                                             /*!< Selects the RX or TX
                                                                direction which is to be
                                                                muted */

/****************************************************************************
* FUNCTION:      SendApiPpAudioUnmuteReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_UNMUTE_REQ = 0x5301
****************************************************************************/
void SendApiPpAudioUnmuteReq ( RosTaskIdType Src,
                               ApiPpAudioMuteRxTxType MuteRxTx);
                                                             /*!< Selects the RX or TX
                                                                direction which is to be
                                                                muted */

/****************************************************************************
* FUNCTION:      SendApiPpAudioSetModeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_SET_MODE_REQ = 0x5302
****************************************************************************/
void SendApiPpAudioSetModeReq ( RosTaskIdType Src,
                                ApiPpAudioModeType AudioMode);
                                                             /*!< Audio output mode
                                                                selection */

/****************************************************************************
* FUNCTION:      SendApiPpAudioSetVolumeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_SET_VOLUME_REQ = 0x5303
****************************************************************************/
void SendApiPpAudioSetVolumeReq ( RosTaskIdType Src,
                                  rsuint8 VolumeStep);       /*!< Selectable Volume
                                                                steps [0..5] */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStartToneReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_TONE_REQ = 0x5306
****************************************************************************/
void SendApiPpAudioStartToneReq ( RosTaskIdType Src,
                                  rsuint8 ToneIndex,         /*!< The selected
                                                                predefined tone */
                                  rsint8 VolumeDb,           /*!< Volume setting in dB
                                                                -128 <-> 127 dB */
                                  rsbool TrackGenVol,        /*!< Follow general volume
                                                                ( If set VolumeIndex is used
                                                                as offset) */
                                  ApiPpToneLsrDeviceId Dest);
                                                             /*!< Destination device */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStartToneExtReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_TONE_EXT_REQ = 0x5328
****************************************************************************/
void SendApiPpAudioStartToneExtReq ( RosTaskIdType Src,
                                     rsint8 VolumeDb,        /*!< Volume setting in dB
                                                                -128 <-> 127 dB */
                                     rsbool TrackGenVol,     /*!< Follow general volume 
                                                                ( If set VolDb is used as
                                                                offset) */
                                     ApiPpToneLsrDeviceId Dest,
                                                             /*!< Destination device */
                                     rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                     rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                One of these Infoelements
                                                                are possible at a time:
                                                                [API_IE_AUDIO_EXT_INDEX] 
                                                                [API_IE_AUDIO_EXT_POINTER] 
                                                                [API_IE_AUDIO_EXT_ARRAY] */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopToneReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_TONE_REQ = 0x5307
****************************************************************************/
void SendApiPpAudioStopToneReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpAudioStartMidiReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_MIDI_REQ = 0x530B
****************************************************************************/
void SendApiPpAudioStartMidiReq ( RosTaskIdType Src,
                                  rsuint8 MidiMelodyIndex,   /*!< The selected midi
                                                                melody to be played */
                                  rsint8 VolumeDb,           /*!< Volume setting in dB
                                                                -128 <-> 127 dB */
                                  rsbool TrackGenVol,        /*!< Follow general volume
                                                                ( If set VolumeIndex is used
                                                                as offset). Only valid if
                                                                supported by sw, else
                                                                ignored. */
                                  ApiPpToneLsrDeviceId Dest);
                                                             /*!< Destination device */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStartMidiExtReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_MIDI_EXT_REQ = 0x5329
****************************************************************************/
void SendApiPpAudioStartMidiExtReq ( RosTaskIdType Src,
                                     rsint8 VolumeDb,        /*!< Volume setting in dB
                                                                -128 <-> 127 dB */
                                     rsbool TrackGenVol,     /*!< Follow general volume
                                                                ( If set VolumeIndex is used
                                                                as offset). Only valid if
                                                                supported by sw, else
                                                                ignored. */
                                     ApiPpToneLsrDeviceId Dest,
                                                             /*!< Destination device */
                                     rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                     rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                One of these Infoelements
                                                                are possible at a time
                                                                [API_IE_AUDIO_EXT_INDEX] 
                                                                [API_IE_AUDIO_EXT_POINTER] */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopMidiReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_MIDI_REQ = 0x530C
****************************************************************************/
void SendApiPpAudioStopMidiReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpAudioSetActiveSoundVolumeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_SET_ACTIVE_SOUND_VOLUME_REQ = 0x530E
****************************************************************************/
void SendApiPpAudioSetActiveSoundVolumeReq ( RosTaskIdType Src,
                                             rsint8 VolumeDb);
                                                             /*!< Volume setting in dB
                                                                -128 <-> 127 dB */

/****************************************************************************
* FUNCTION:      SendApiPpAudioTestCmdReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_TEST_CMD_REQ = 0x530F
****************************************************************************/
void SendApiPpAudioTestCmdReq ( RosTaskIdType Src,
                                ApiPpAudioTestCmdType TestCmd);
                                                             /*!< Test Command (TBD) */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStartMediaSeqReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_MEDIA_SEQ_REQ = 0x5310
****************************************************************************/
void SendApiPpAudioStartMediaSeqReq ( RosTaskIdType Src,
                                      rsuint8 Index,         /*!< The selected media
                                                                sequence to be played */
                                      rsint8 VolumeDb,       /*!< Volume setting in dB
                                                                -128 <-> 127 dB */
                                      rsbool TrackGenVol,    /*!< Follow general volume
                                                                ( If set VolumeIndex is used
                                                                as offset) */
                                      ApiPpToneLsrDeviceId Dest);
                                                             /*!< Destination device */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopMediaSeqReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_MEDIA_SEQ_REQ = 0x5311
****************************************************************************/
void SendApiPpAudioStopMediaSeqReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpAudioMediaSeqEndInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_MEDIA_SEQ_END_IND = 0x5312
****************************************************************************/
void SendApiPpAudioMediaSeqEndInd ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpAudioStartTextToSpeechReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_TEXT_TO_SPEECH_REQ = 0x531a
****************************************************************************/
void SendApiPpAudioStartTextToSpeechReq ( RosTaskIdType Src,
                                          rsint8 VolumeDb,   /*!< Volume setting in dB
                                                                -128 <-> 127 dB */
                                          rsbool TrackGenVol,
                                                             /*!< Follow general volume
                                                                ( If set VolumeIndex is used
                                                                as offset) */
                                          ApiPpToneLsrDeviceId Dest,
                                                             /*!< Destination device */
                                          rsuint8 LengthOfText,
                                                             /*!< The number of chars to
                                                                convert to speech */
                                          rsuint8 Buffer[1]);
                                                             /*!< The buffer containing
                                                                char. */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopTextToSpeechReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_TEXT_TO_SPEECH_REQ = 0x531c
****************************************************************************/
void SendApiPpAudioStopTextToSpeechReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpAudioStartDtmfReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_DTMF_REQ = 0x531f
****************************************************************************/
void SendApiPpAudioStartDtmfReq ( RosTaskIdType Src,
                                  rsuint8 DtmfIndex,         /*!< DTMF to play:
                                                                0:DTMF 0
                                                                1:DTMF 1 
                                                                2:DTMF 2
                                                                3:DTMF 3
                                                                4:DTMF 4
                                                                5:DTMF 5
                                                                6:DTMF 6
                                                                7:DTMF 7
                                                                8:DTMF 8
                                                                9:DTMF 9
                                                                10:DTMF A
                                                                11:DTMF B
                                                                12:DTMF C
                                                                13:DTMF D
                                                                14:DTMF *
                                                                15:DTMF # */
                                  rsuint16 Length,           /*!< Time in ms. 0 means
                                                                infinite, and tone must be
                                                                stoped, with a stop request. */
                                  rsint8 VolumeDb,           /*!< Volume setting in dB
                                                                -128 <-> 127 dB */
                                  rsbool TrackGenVol,        /*!< Follow general volume
                                                                ( If set VolumeIndex is used
                                                                as offset) */
                                  ApiPpToneLsrDeviceId Dest);
                                                             /*!< Destination device */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopDtmfReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_DTMF_REQ = 0x5321
****************************************************************************/
void SendApiPpAudioStopDtmfReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpAudioStartVoiceDetectionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_START_VOICE_DETECTION_REQ = 0x5325
****************************************************************************/
void SendApiPpAudioStartVoiceDetectionReq ( RosTaskIdType Src,
                                            rsint8 Threshold,
                                                             /*!< threshold, threshold
                                                                in dB for detecting voice signal
                                                                range 0 to -128 */
                                            rsuint16 OnTime,  /*!< time required for
                                                                 detecting voice "on" in ms */
                                            rsuint16 OffTime,
                                                             /*!< time required for
                                                                detecting voice "off" in ms */
                                            ApiPpAudioMicDeviceIdType Mic);
                                                             /*!< which MIC to use in
                                                                idle-mode */

/****************************************************************************
* FUNCTION:      SendApiPpAudioStopVoiceDetectionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_STOP_VOICE_DETECTION_REQ = 0x5326
****************************************************************************/
void SendApiPpAudioStopVoiceDetectionReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpAudioInitPcmReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_AUDIO_INIT_PCM_REQ = 0x532A
****************************************************************************/
void SendApiPpAudioInitPcmReq ( RosTaskIdType Src,
                                rsbool PcmEnable,            /*!< Enable or disable the
                                                                PCM interface.
                                                                The remaining parameters of
                                                                this message are ignored by
                                                                the module if the PCM
                                                                interface is disabled. */
                                rsbool IsMaster,             /*!< Controls whether the
                                                                device is master or slave on
                                                                the PCM interface. */
                                rsbool Reserved,             /*!< For further use. Must
                                                                be set to 0. */
                                ApiPcmFscFreqType PcmFscFreq,
                                                             /*!< PCM  FSC frequency;
                                                                8,16, or 32kHz. */
                                ApiPcmFscLengthType PcmFscLength,
                                                             /*!< The length of the FSC
                                                                pulse. 1, 8, 16, 32 or 48
                                                                bits. Or special slave mode
                                                                setting, see type
                                                                description. */
                                rsbool PcmFscStartAligned ,  /*!< If true FSC starts at
                                                                the same time as MSB bit of
                                                                PCM channel 0 data,
                                                                otherwise it starts 1 clocks
                                                                cycle before data. */
                                ApiPcmClkType PcmClk,        /*!< The clock frequency
                                                                generated by the module if
                                                                the module is master on the
                                                                PCM interface. Ignored if
                                                                the device is slave. */
                                rsbool PcmClkOnRising,       /*!< Controls whether PCM
                                                                data is clocked out on
                                                                rising or falling edge of
                                                                the PCM_CLK. */
                                rsuint8 PcmClksPerBit,       /*!< Number of bit clocks
                                                                per data bit. See datasheet
                                                                for options. */
                                rsbool PcmFscInvert,         /*!< If true, FSC is
                                                                inverted. */
                                rsuint8 PcmCh0Delay,         /*!< 5 bit delay value in
                                                                number of 8 bits.  Delay of
                                                                data bits in number of
                                                                channels. */
                                rsbool PcmDoutIsOpenDrain,   /*!< Controls whether
                                                                PCM_DOUT is push-pull (0) or
                                                                open drain (1). 
                                                                Sets
                                                                DSP_PCM_CTRL_REG.PCM_PPOD to
                                                                the value specified by
                                                                PcmDoOd. Can be used if the
                                                                I/O levels (VDDIO) on the
                                                                PCM interface is 1.8V. Must
                                                                be set to 1 if multiple
                                                                devices are connected to the
                                                                PCM bus.
                                                                DSP_PCM_CTRL_REG.PCM_PPOD
                                                                is set to 0 after reset. */
                                rsbool PcmIsOpenDrain);      /*!< Controls the PCM_DI,
                                                                PCM_DO, PCM_CLK, and PCM_FSC
                                                                I/O mode.
                                                                0: Normal mode.
                                                                1: Forced to open drain if
                                                                output and pull-up resistor
                                                                is always disabled if input
                                                                (back-drive protection). 
                                                                Sets PAD_CTRL_REG.P225_OD
                                                                and PAD_CTRL_REG.P234_OD to
                                                                the value specified by
                                                                PcmOd. Must be set to 1 if
                                                                the I/O levels (VDDIO) on
                                                                the PCM interface is > 1.8V.
                                                                VDDIO up to 3.45V is
                                                                supported if set to 1.
                                                                PAD_CTRL_REG.P225_OD and
                                                                PAD_CTRL_REG.P234_OD are set
                                                                to 0 after reset.
                                                                Please note that
                                                                PAD_CTRL_REG.P234_OD = 1
                                                                overrules
                                                                DSP_PCM_CTRL_REG.PCM_PPOD. */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIPPAUDIO_H */


