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
* Definition of the ApiFpAudio interface.
*/


#ifndef APIFPAUDIO_H
#define APIFPAUDIO_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! Include of API configuration. */
//#include <Api/ApiCfg.h>
/*! Include of common API types. */
#include <Phoenix/Api/Types/ApiTypes.h>
/*! The following API files must be included. */
#include <Phoenix/Api/AudioTypes/ApiAudioTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


/* Global mail primitives:
  API_FP_INIT_PCM_REQ = 0x4200,
  API_FP_INIT_PCM_CFM = 0x4201,
  API_FP_SET_PCM_LOOPBACK_REQ=0x4204,
  API_FP_SET_PCM_LOOPBACK_CFM=0x4205,
  API_FP_INIT_USB_REQ = 0x4206,
  API_FP_INIT_USB_CFM = 0x4207,
  API_FP_SET_AUDIO_FORMAT_REQ = 0x4210,
  API_FP_SET_AUDIO_FORMAT_CFM = 0x4211,
  API_FP_AUDIO_MUTE_REQ = 0x4212,
  API_FP_AUDIO_MUTE_CFM = 0x4213,
  API_FP_AUDIO_UNMUTE_REQ = 0x4214,
  API_FP_AUDIO_UNMUTE_CFM = 0x4215,
  API_FP_AUDIO_INTERNAL_CODEC_SETUP_REQ = 0x4216,
  API_FP_AUDIO_INTERNAL_CODEC_SETUP_CFM = 0x4217,
  API_FP_AUDIO_SET_HW_SRC_REQ = 0x4218,
  API_FP_AUDIO_SET_HW_SRC_CFM = 0x4219,
  API_FP_AUDIO_SET_CODEC_GAIN_REQ = 0x421A,
  API_FP_AUDIO_SET_CODEC_GAIN_CFM = 0x421B,
  API_FP_AUDIO_ENABLE_EC_REQ = 0x421C,
  API_FP_AUDIO_ENABLE_EC_CFM = 0x421D,
  API_FP_AUDIO_FEATURES_REQ = 0x4220,
  API_FP_AUDIO_FEATURES_CFM = 0x4221,
End of mail primitives. */




/*! This enum defines the MUTE options from the HOST */
typedef enum RSENUMTAG(ApiFpAudioMuteRxTxType)
{
  API_FP_MUTE_RX   = 0x01, /*!< Mute audio direction RX (Speaker) */
  API_FP_MUTE_TX   = 0x02, /*!< Mute audio direction TX (Microphone) */
  API_FP_MUTE_BOTH = 0x03  /*!< Mute both audio directions RX and TX (Speaker and Mic) */
} RSENUM8(ApiFpAudioMuteRxTxType);

/*! This enum defines the frontend setup */
typedef enum RSENUMTAG(ApiFpAudioFeIoModeType)
{
  API_AUDIO_IOMODE_OFF        = 0x00, /*!< IO+, IO- are both powered down */
  API_AUDIO_IOMODE_DIFF       = 0x01, /*!< IO+, IO- differential */
  API_AUDIO_IOMODE_SE_N       = 0x02, /*!< IO-, IO+ is powered-down */
  API_AUDIO_IOMODE_SE_P       = 0x03, /*!< IO+, IO- is powered-down */
  API_AUDIO_IOMODE_SE_N_VREFP = 0x04, /*!< IO-, IO+ is VREF */
  API_AUDIO_IOMODE_SE_P_VREFN = 0x05, /*!< IO+, IO- is VREF */
  API_AUDIO_IOMODE_DISABLED   = 0x06, /*!< IO+, IO- is disabled/high-impedance */
  API_AUDIO_IOMODE_OFF_VREFN  = 0x07, /*!< IO+ is powered down, IO- is VREF */
  API_AUDIO_IOMODE_OFF_VREFP  = 0x08, /*!< IO- is powered down, IO+ is VREF */
  API_AUDIO_IOMODE_SE_DUAL    = 0x09, /*!< IO+, IO- are both single ended */
} RSENUM8(ApiFpAudioFeIoModeType);

/*! This enum defines the audio source */
typedef enum RSENUMTAG(ApiFpAudioHardwareSrcType)
{
  API_AUDIO_NO_SRC    = 0x00, /*!< No Source */
  API_AUDIO_INT_CODEC = 0x01, /*!< Sc14480 Internal Codec. */
  API_AUDIO_PCM0      = 0x02, /*!< PCM Channel 0 */
  API_AUDIO_PCM1      = 0x03, /*!< PCM Channel 1 */
  API_AUDIO_PCM2      = 0x04, /*!< PCM Channel 2 */
  API_AUDIO_PCM3      = 0x05, /*!< PCM Channel 3 */
} RSENUM8(ApiFpAudioHardwareSrcType);

/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiFpAudioFeatureType;


/*! Mail without parameters. */
typedef struct ApifpaudioEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
}PACKED_STRUCT ApifpaudioEmptySignalType;

/*! This command is used by the HOST to initialize the PCM interface. */
typedef struct ApiFpInitPcmReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_INIT_PCM_REQ = 0x4200 */
  rsbool PcmEnable;                     /*!< Enable or disable the PCM interface.
                                           The remaining parameters of this message are
                                           ignored by the module if the PCM interface is
                                           disabled. */
  rsbool IsMaster;                      /*!< Controls whether the device is master or
                                           slave on the PCM interface. */
  rsbool DoClockSync;                   /*!< Valid for slave mode only (IsMaster =
                                           FALSE). If TRUE, the device will adjust its local
                                           clock to the incoming PCM frame sync signal. */
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
}PACKED_STRUCT ApiFpInitPcmReqType;

/*! This mail is used to confirm API_FP_INIT_PCM_REQ. */
typedef struct ApiFpInitPcmCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_INIT_PCM_CFM = 0x4201 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
}PACKED_STRUCT ApiFpInitPcmCfmType;

/*! This command is used by the HOST to set a loopback on the PCM channels.
   The data send on the SourceId PCM channel is loopbacked on the
   DestinationId PCM channel. The SorceId and DestinationId can be the same,
   thus the transmitted data is send back on the same PCM channel. */
typedef struct ApiFpSetPcmLoopbackReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_PCM_LOOPBACK_REQ=0x4204 */
  ApiAudioEndPointIdType SourceId;     /*!< The data channel [0;n]
                                           *The individual channels and number of channels
                                           (n) is depending on project configuration. */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration. */
} PACKED_STRUCT ApiFpSetPcmLoopbackReqType;

/*! This mail is used to confirm API_FP_SET_PCM_CODEC_REQ. */
typedef struct ApiFpSetPcmLoopbackCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_PCM_LOOPBACK_CFM=0x4205 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiAudioEndPointIdType SourceId;     /*!< The selected data channel */
  ApiAudioEndPointIdType DestinationId; /*!< The selected data channel */
} PACKED_STRUCT ApiFpSetPcmLoopbackCfmType;

/*! This command is used by the HOST to tell the audio client what audio
   format is used on the air interface.
     It is possible to enable cross codes between the CODEC supported by the
   PP and the data format of the data interface. The Host most send both this
   message and API_FP_SET_AUDIO_FORMAT_REQ, in order for the audio to be enabled.
    The HOST should set the DataFormat to AP_DATA_FORMAT_NONE when calls are
   ended to make sure that the blocks in the DSP are shut down. */
typedef struct ApiFpInitUsbReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_INIT_USB_REQ = 0x4206 */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration. */
  ApiAudioDataFormatType AudioDataFormat; /*!< The data format on the air interface.
                                              E.g. G726 or G722 */
} PACKED_STRUCT ApiFpInitUsbReqType;

/*! This mail is used to confirm API_FP_INIT_USB_REQ. */
typedef struct ApiFpInitUsbCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_INIT_USB_CFM = 0x4207 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
}PACKED_STRUCT ApiFpInitUsbCfmType;

/*! This command is used by the HOST to change the data format (CODEC) of
   one of the audio data channelsThe HOST should set the DataFormat to
   AP_DATA_FORMAT_NONE when calls are ended to make sure that the blocks in
   the DSP are shut down. */
typedef struct ApiFpSetAudioFormatReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_AUDIO_FORMAT_REQ = 0x4210 */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration. */
  ApiAudioDataFormatType AudioDataFormat; /*!< The data format of the PCM channel
                                              specified. */
}PACKED_STRUCT ApiFpSetAudioFormatReqType;

/*! This mail is used to confirm API_FP_SET_PCM_CODEC_REQ. */
typedef struct ApiFpSetAudioFormatCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_AUDIO_FORMAT_CFM = 0x4211 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration. */
  ApiAudioDataFormatType AudioDataFormat; /*!< The data format of the PCM channel
                                              specified. */
} PACKED_STRUCT ApiFpSetAudioFormatCfmType;

/*! This mail is used by the HOST to mute individual audio channels 
    (between the application and the HOST) */
typedef struct ApiFpAudioMuteReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_MUTE_REQ = 0x4212 */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration. */
  ApiFpAudioMuteRxTxType MuteRxTx;      /*!< Selects the RX or TX direction which is to
                                           be muted */
}PACKED_STRUCT ApiFpAudioMuteReqType;

/*! This mail is used to confirm API_FP_AUDIO_MUTE_REQ. */
typedef struct ApiFpAudioMuteCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_MUTE_CFM = 0x4213 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration. */
  ApiFpAudioMuteRxTxType MuteRxTx;      /*!< Selects the RX or TX direction which is to
                                           be muted */
} PACKED_STRUCT ApiFpAudioMuteCfmType;

/*! This mail is used by the HOST to unmute individual audio channels 
    (between the application and the HOST) */
typedef struct ApiFpAudioUnmuteReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_UNMUTE_REQ = 0x4214 */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration. */
  ApiFpAudioMuteRxTxType MuteRxTx;     /*!< Selects the RX or TX direction which is to
                                           be muted */
}PACKED_STRUCT ApiFpAudioUnmuteReqType;

/*! This mail is used to confirm API_FP_AUDIO_UNMUTE_REQ. */
typedef struct ApiFpAudioUnmuteCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_UNMUTE_CFM = 0x4215 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration. */
  ApiFpAudioMuteRxTxType MuteRxTx;      /*!< Selects the RX or TX direction which is to
                                           be muted */
} PACKED_STRUCT ApiFpAudioUnmuteCfmType;

/*! This mail is used by the HOST  to configure the internal codec front end.
    Must be sent every time the sample frequency changes. To save power codec
   should be powered of after call ended.
When powering off the different
   modes (MicMode,MicHeadsetMode,etc.) must be set to API_AUDIO_IOMODE_OFF.
   This way you can choose to power off only parts of the front end while have
   other parts still turned on. So do not expect PowerOn = FALSE to turn
   everything off. */
typedef struct ApiFpAudioInternalCodecSetupReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_INTERNAL_CODEC_SETUP_REQ = 0x4216 */
  rsuint8 PowerOn;                      /*!< 0:Power codec off 1: Power codec on. See
                                           description. */
  rsuint8 SampleFreq;                   /*!< Sample Frequency/1000. 
                                           8 = 8000Hz 
                                           16 = 16000Hz */
  ApiFpAudioFeIoModeType MicMode;       /*!< Microphone setup. */
  ApiFpAudioFeIoModeType MicHeadsetMode; /*!< Headset Microphone setup. */
  ApiFpAudioFeIoModeType LsrMode;       /*!< Loudspeaker setup. */
  ApiFpAudioFeIoModeType ClassDMode;    /*!< ClassD setup. */
} PACKED_STRUCT ApiFpAudioInternalCodecSetupReqType;

/*! This mail is used to confirm API_FP_AUDIO_INTERNAL_CODEC_SETUP_REQ. */
typedef struct ApiFpAudioInternalCodecSetupCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_INTERNAL_CODEC_SETUP_CFM = 0x4217 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpAudioInternalCodecSetupCfmType;

/*! This mail is used by the HOST to set the routing of line audio to
   specific hardware output. Pcm or internal codec. Default setting is Pcm. So
   if PCM is used this mail does not need to be sent. The mail must be sent
   before initiating a call on the selected channel.
    Important audio format must be linear when routing to internal codec! */
typedef struct ApiFpAudioSetHwSrcReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_SET_HW_SRC_REQ = 0x4218 */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration. */
  ApiFpAudioHardwareSrcType HwSrc;     /*!< Hw source: Codec or PCM */
} ApiFpAudioSetHwSrcReqType;

/*! This mail is used to confirm API_FP_AUDIO_SET_HW_SRC_REQ. */
typedef struct ApiFpAudioSetHwSrcCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_SET_HW_SRC_CFM = 0x4219 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpAudioSetHwSrcCfmType;

/*! This mail is used by the HOST to setup the front end gain. Currently
   only the gains supported in hw will have effect. All other gain settings
   will be truncated to nearest possible gain. If ClassD hw src has been
   chosen, then currently no gain setting is possible. */
typedef struct ApiFpAudioSetCodecGainReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_SET_CODEC_GAIN_REQ = 0x421A */
  rsint8 MicGain;                       /*!< 0-30 dB in steps of 2dB. -128 will mute the
                                           microphone signal. */
  rsint8 LsrGain;                       /*!< From +2dB to -12dB in steps of 2 dB */
} PACKED_STRUCT ApiFpAudioSetCodecGainReqType;

/*! This mail is used to confirm API_FP_AUDIO_SET_CODEC_GAIN_REQ. */
typedef struct ApiFpAudioSetCodecGainCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_SET_CODEC_GAIN_CFM = 0x421B */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpAudioSetCodecGainCfmType;

/*! Enable Echo canceller on requested line. This feature is not available
   in standard sw. */
typedef struct ApiFpAudioEnableEcReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_ENABLE_EC_REQ = 0x421C */
  ApiAudioEndPointIdType DestinationId; /*!< The data channel [0;n]
                                             *The individual channels and number of
                                             channels (n) is depending on project
                                             configuration */
  rsbool Enable;                        /*!< Enable or disable EC. */
  rsbool KeepCoef;                      /*!< Memory effect in the EC: If true, keep the
                                           same coefficients for next call, otherwise start
                                           from zero. */
} PACKED_STRUCT ApiFpAudioEnableEcReqType;

/*! This mail is used to confirm API_FP_AUDIO_ENABLE_EC_REQ. */
typedef struct ApiFpAudioEnableEcCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_ENABLE_EC_CFM = 0x421D */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpAudioEnableEcCfmType;

/*! This command is used to enable/disable features in the FpAudio API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiFpAudioFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_FEATURES_REQ = 0x4220 */
  ApiFpAudioFeatureType ApiFpAudioFeature; /*!< Requested features */
} PACKED_STRUCT ApiFpAudioFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiFpAudioFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_AUDIO_FEATURES_CFM = 0x4221 */
  RsStatusType Status;
  ApiFpAudioFeatureType ApiFpAudioFeature; /*!< Supported features */
} PACKED_STRUCT ApiFpAudioFeaturesCfmType;


#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiFpInitPcmReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_INIT_PCM_REQ = 0x4200
****************************************************************************/
void SendApiFpInitPcmReq ( RosTaskIdType Src,
                           rsbool PcmEnable,                 /*!< Enable or disable the
                                                                PCM interface.
                                                                The remaining parameters of
                                                                this message are ignored by
                                                                the module if the PCM
                                                                interface is disabled. */
                           rsbool IsMaster,                  /*!< Controls whether the
                                                                device is master or slave on
                                                                the PCM interface. */
                           rsbool DoClockSync,               /*!< Valid for slave mode
                                                                only (IsMaster = FALSE). If
                                                                TRUE, the device will adjust
                                                                its local clock to the
                                                                incoming PCM frame sync
                                                                signal. */
                           ApiPcmFscFreqType PcmFscFreq,     /*!< PCM  FSC frequency;
                                                                8,16, or 32kHz. */
                           ApiPcmFscLengthType PcmFscLength,  /*!< The length of the FSC
                                                                 pulse. 1, 8, 16, 32 or 48
                                                                 bits. Or special slave mode
                                                                 setting, see type
                                                                 description. */
                           rsbool PcmFscStartAligned ,       /*!< If true FSC starts at
                                                                the same time as MSB bit of
                                                                PCM channel 0 data,
                                                                otherwise it starts 1 clocks
                                                                cycle before data. */
                           ApiPcmClkType PcmClk,             /*!< The clock frequency
                                                                generated by the module if
                                                                the module is master on the
                                                                PCM interface. Ignored if
                                                                the device is slave. */
                           rsbool PcmClkOnRising,            /*!< Controls whether PCM
                                                                data is clocked out on
                                                                rising or falling edge of
                                                                the PCM_CLK. */
                           rsuint8 PcmClksPerBit,            /*!< Number of bit clocks
                                                                per data bit. See datasheet
                                                                for options. */
                           rsbool PcmFscInvert,              /*!< If true, FSC is
                                                                inverted. */
                           rsuint8 PcmCh0Delay,              /*!< 5 bit delay value in
                                                                number of 8 bits.  Delay of
                                                                data bits in number of
                                                                channels. */
                           rsbool PcmDoutIsOpenDrain,        /*!< Controls whether
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
                           rsbool PcmIsOpenDrain);           /*!< Controls the PCM_DI,
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

/****************************************************************************
* FUNCTION:      SendApiFpSetPcmLoopbackReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_PCM_LOOPBACK_REQ=0x4204
****************************************************************************/
void SendApiFpSetPcmLoopbackReq ( RosTaskIdType Src,
                                  ApiAudioEndPointIdType SourceId,
                                                             /*!< The data channel [0;n]
                                                                *The individual channels
                                                                and number of channels (n)
                                                                is depending on project
                                                                configuration. */
                                  ApiAudioEndPointIdType DestinationId);
                                                             /*!< The data channel [0;n]
                                                                *The individual channels
                                                                and number of channels (n)
                                                                is depending on project
                                                                configuration. */

/****************************************************************************
* FUNCTION:      SendApiFpInitUsbReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_INIT_USB_REQ = 0x4206
****************************************************************************/
void SendApiFpInitUsbReq ( RosTaskIdType Src,
                           ApiAudioEndPointIdType DestinationId,
                                                             /*!< The data channel [0;n]
                                                                *The individual channels
                                                                and number of channels (n)
                                                                is depending on project
                                                                configuration. */
                           ApiAudioDataFormatType AudioDataFormat);
                                                             /*!< The data format on the
                                                                air interface. E.g. G726 or
                                                                G722 */

/****************************************************************************
* FUNCTION:      SendApiFpSetAudioFormatReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_AUDIO_FORMAT_REQ = 0x4210
****************************************************************************/
void SendApiFpSetAudioFormatReq ( RosTaskIdType Src,
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
* FUNCTION:      SendApiFpAudioMuteReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_MUTE_REQ = 0x4212
****************************************************************************/
void SendApiFpAudioMuteReq ( RosTaskIdType Src,
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
* FUNCTION:      SendApiFpAudioUnmuteReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_UNMUTE_REQ = 0x4214
****************************************************************************/
void SendApiFpAudioUnmuteReq ( RosTaskIdType Src,
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
* FUNCTION:      SendApiFpAudioInternalCodecSetupReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_INTERNAL_CODEC_SETUP_REQ = 0x4216
****************************************************************************/
void SendApiFpAudioInternalCodecSetupReq ( RosTaskIdType Src,
                                           rsuint8 PowerOn,  /*!< 0:Power codec off 1:
                                                                Power codec on. See
                                                                description. */
                                           rsuint8 SampleFreq,
                                                             /*!< Sample Frequency/1000. 
                                                                8 = 8000Hz 
                                                                16 = 16000Hz */
                                           ApiFpAudioFeIoModeType MicMode,
                                                             /*!< Microphone setup. */
                                           ApiFpAudioFeIoModeType MicHeadsetMode,
                                                             /*!< Headset Microphone
                                                                setup. */
                                           ApiFpAudioFeIoModeType LsrMode,
                                                             /*!< Loudspeaker setup. */
                                           ApiFpAudioFeIoModeType ClassDMode);
                                                             /*!< ClassD setup. */

/****************************************************************************
* FUNCTION:      SendApiFpAudioSetHwSrcReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_SET_HW_SRC_REQ = 0x4218
****************************************************************************/
void SendApiFpAudioSetHwSrcReq ( RosTaskIdType Src,
                                 ApiAudioEndPointIdType DestinationId,
                                                             /*!< The data channel [0;n]
                                                                *The individual channels
                                                                and number of channels (n)
                                                                is depending on project
                                                                configuration. */
                                 ApiFpAudioHardwareSrcType HwSrc);
                                                             /*!< Hw source: Codec or
                                                                PCM */

/****************************************************************************
* FUNCTION:      SendApiFpAudioSetCodecGainReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_SET_CODEC_GAIN_REQ = 0x421A
****************************************************************************/
void SendApiFpAudioSetCodecGainReq ( RosTaskIdType Src,
                                     rsint8 MicGain,         /*!< 0-30 dB in steps of
                                                                2dB. -128 will mute the
                                                                microphone signal. */
                                     rsint8 LsrGain);        /*!< From +2dB to -12dB in
                                                                steps of 2 dB */

/****************************************************************************
* FUNCTION:      SendApiFpAudioEnableEcReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_ENABLE_EC_REQ = 0x421C
****************************************************************************/
void SendApiFpAudioEnableEcReq ( RosTaskIdType Src,
                                 ApiAudioEndPointIdType DestinationId,
                                                             /*!< The data channel [0;n]
                                                                *The individual channels
                                                                and number of channels (n)
                                                                is depending on project
                                                                configuration */
                                 rsbool Enable,              /*!< Enable or disable EC. */
                                 rsbool KeepCoef);           /*!< Memory effect in the
                                                                EC: If true, keep the same
                                                                coefficients for next call,
                                                                otherwise start from zero. */

/****************************************************************************
* FUNCTION:      SendApiFpAudioFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_AUDIO_FEATURES_REQ = 0x4220
****************************************************************************/
void SendApiFpAudioFeaturesReq ( RosTaskIdType Src,
                                 ApiFpAudioFeatureType ApiFpAudioFeature);
                                                             /*!< Requested features */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPAUDIO_H */


