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
* Definition of the ApiFpCc interface.
*/


#ifndef APIFPCC_H
#define APIFPCC_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
//#include <Api/ApiCfg.h>

#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/
#define PHOENIX_API_FP_CC
/*! This type describes features available in this API */
#define API_FP_CC_EXTENDED_TERMINAL_ID_SUPPORT 0x01

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


/* Mail primitives:
  API_FP_CC_SETUP_IND = 0x4400,
  API_FP_CC_SETUP_RES = 0x4401,
  API_FP_CC_SETUP_REQ = 0x4402,
  API_FP_CC_SETUP_CFM = 0x4403,
  API_FP_CC_SETUP_ACK_REQ = 0x4423,
  API_FP_CC_SETUP_ACK_CFM = 0x4424,
  API_FP_CC_CALL_PROC_REQ = 0x4415,
  API_FP_CC_CALL_PROC_CFM = 0x4416,
  API_FP_CC_ALERT_IND = 0x4404,
  API_FP_CC_ALERT_REQ = 0x4405,
  API_FP_CC_ALERT_CFM = 0x4406,
  API_FP_CC_CONNECT_IND = 0x4407,
  API_FP_CC_CONNECT_RES = 0x4408,
  API_FP_CC_CONNECT_REQ = 0x4409,
  API_FP_CC_CONNECT_CFM = 0x440A,
  API_FP_CC_RELEASE_IND = 0x440F,
  API_FP_CC_RELEASE_RES = 0x4410,
  API_FP_CC_RELEASE_REQ = 0x4411,
  API_FP_CC_RELEASE_CFM = 0x4412,
  API_FP_CC_REJECT_IND = 0x4413,
  API_FP_CC_INFO_IND = 0x442D,
  API_FP_CC_INFO_REQ = 0x442E,
  API_FP_CC_MODIFY_CODEC_REQ = 0x441D,
  API_FP_CC_MODIFY_CODEC_CFM = 0x441E,
  API_FP_CC_MODIFY_CODEC_IND = 0x441F,
  API_FP_CC_MODIFY_CODEC_RES = 0x4420,
  API_FP_CC_IWU_INFO_CODEC_IND = 0x4421,
  API_FP_CC_SYSTEM_CALL_ID_REQ = 0x4427,
  API_FP_CC_SYSTEM_CALL_ID_CFM = 0x4428,
  API_FP_CC_RECONNECT_AUDIO_REQ = 0x442C,
  API_FP_CC_DISCONNECT_AUDIO_REQ = 0x442F,
  API_FP_CC_SELECTED_ADPCM_IND = 0x4430,
  API_FP_CC_FEATURES_REQ = 0x4450,
  API_FP_CC_FEATURES_CFM = 0x4451,
End of mail primitives. */



/*! The definition of ApiCallInstanceType can be overloaded by the project
   configuration by usage of preprocessor define directive in
   Config\Api\ApiCfg.h. This can be used to make an alternative declaration of
   ApiCallInstanceType to be used with an alternative layout of bit fields. */
#ifndef ApiCallInstanceType

/*! This type is used to hold the instance number to uniquely identify a
   call. */
typedef struct 
{
  rsbitfield  Fp : 4;                   /*!< Bit 0-3: FP call instance number [1; 15]. */
  rsbitfield  Host  : 4;                /*!< Bit 4-7: Host call instance number [1; 15]. */
} PACKED_STRUCT ApiCallInstanceType;


#endif

/*! This type is used to hold the reference/instance number to uniquely
   identify a call.
    When a call is started from the FP, the FP allocates a
   CallReference.Instance.Fp number that is not used for other calls, and sets
   CallReference.Instance.Host to zero. The first mail returned from the host
   includes the CallReference.Instance.Host allocated by the host.
    When a call is started from the host, the host allocates a
   CallReference.Instance.Host number that is not used for other calls, and
   sets CallReference.Instance.Fp to zero. The first mail returned from the FP
   includes the CallReference.Instance.Fp allocated by the FP. */
typedef union 
{
  rsuint8 Value;                        /*!< Callreference value. */
  ApiCallInstanceType Instance;         /*!< Call instance number. */
} ApiCallReferenceType;

/*! This type is used to indicate the ADPCM selected by the CVM module.
    The number of available ADPCM blocks is hardware dependent (typical 4). */
typedef enum RSENUMTAG(ApiAdpcmType)
{
  API_SAT_ADPCM0  = 0x00, /*!<  */
  API_SAT_ADPCM1  = 0x01, /*!<  */
  API_SAT_ADPCM2  = 0x02, /*!<  */
  API_SAT_ADPCM3  = 0x03, /*!<  */
  API_SAT_ADPCM4  = 0x04, /*!<  */
  API_SAT_ADPCM5  = 0x05, /*!<  */
  API_SAT_ADPCM6  = 0x06, /*!<  */
  API_SAT_ADPCM7  = 0x07, /*!<  */
  API_SAT_ADPCM8  = 0x08, /*!<  */
  API_SAT_ADPCM9  = 0x09, /*!<  */
  API_SAT_ADPCM10 = 0x0a  /*!<  */
} RSENUM8(ApiAdpcmType);

/*! This tag describes whether the audio is connected to the Host or the
   audio is connected internally in the CVM module to another PP. */
typedef enum RSENUMTAG(ApiIntExtAudioType)
{
  API_IEA_EXT = 0x00, /*!< Audio connected to the host. */
  API_IEA_INT = 0x01  /*!< Audio connected internally. */
} RSENUM8(ApiIntExtAudioType);

/*! This type describes whereto the audio shall be connected. */
typedef struct ApiFpCcAudioIdType
{
  ApiIntExtAudioType IntExtAudio;       /*!< This informs the CVM module whether the
                                           audio shall be connected to AudioEndPointId or to
                                           the SourceTerminalId. */
  ApiAudioEndPointIdType AudioEndPointId; /*!< External call: 
                                               0x00 - 0x0n  ~ The PCM channel that is
                                               assigned to this call. */
  ApiTerminalIdType SourceTerminalId;   /*!< Internal call: PP1to PPn ~ 1 to N. */
} PACKED_STRUCT ApiFpCcAudioIdType;

/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiFpCcFeatureType;


/*! Mail without parameters. */
typedef struct ApifpccEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
}PACKED_STRUCT ApifpccEmptySignalType;

/*! This mail is used to inform the MCU when an air link has been
   established between a PP and the FP. E.g. after a user has pressed the ?off
   hook? button on a PP. The number (dial string) is included if the uses has
   entered a number before the ?off hook? button was pressed. The Host can do
   the following when this message is received:
    Accept the call and enter ?overlap sending? (F-02) state by sending
   API_FP_CC_SETUP_RES with Status = AS_SUCCESS followed by
   API_FP_CC_SETUP_ACK_REQ. This can be used if dial string is not included in
   the API_FP_CC_SETUP_IND message.
    Accept the call and enter ?active? (F-10) state directly by sending
   API_FP_CC_SETUP_RES with Status = AS_SUCCESS followed by
   API_FP_CC_CONNECT_REQ. This is done for PSTN lines normally regardless of
   whether the dial string is received in the API_FP_CC_SETUP_IND.
    Accept the call and enter ?call proceeding? (F-03) state directly by
   sending API_FP_CC_SETUP_RES with Status = AS_SUCCESS followed by API_FP_CC_CALL_PROC_REQ.
    Accept the call and enter ?call delivered? (F-04) state directly by
   sending API_FP_CC_SETUP_RES with Status = AS_SUCCESS followed by API_FP_CC_ALERT_REQ.
    Reject the call by sending API_FP_CC_SETUP_RES with Status = AS_REJECT. */
typedef struct ApiFpCcSetupIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SETUP_IND = 0x4400 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiTerminalIdType TerminalId;         /*!< Id of the calling handset. */
  ApiCcBasicServiceType BasicService;   /*!< Narrow/wide band speech encoding */
  ApiCcCallClassType CallClass;         /*!< DECT defined call classes. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_MULTIKEYPAD] 
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY] */
}PACKED_STRUCT ApiFpCcSetupIndType;

/*! This mail is used by the MCU to inform the FP about whether the
   requested call is made or not. This mail is also used to inform the FP
   about which PCM channel to use for a PP initiated call if the audio must be
   connected to the PCM interface (for external calls only). */
typedef struct ApiFpCcSetupResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SETUP_RES = 0x4401 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  RsStatusType Status;                  /*!< Indicates whether the call is accepted or
                                           not. AS_REJECTED is used to indicate that the
                                           call is rejected by the user / host and
                                           AS_SUCCESS is used to indicate that the call is
                                           accepted. */
  ApiFpCcAudioIdType AudioId;
} PACKED_STRUCT ApiFpCcSetupResType;

/*! This mail is used by the MCU to initiate a call / connection to a PP.
   The call can be:
    an incoming call on the line (VoIP or PSTN)
    a call from another PP or
    base initiated page of the PP used to locate the PP. */
typedef struct ApiFpCcSetupReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SETUP_REQ = 0x4402 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiTerminalIdType TerminalId;         /*!< Terminal destination for the call. */
  ApiFpCcAudioIdType AudioId;
  ApiCcBasicServiceType BasicService;   /*!< Narrow/wide band speech encoding */
  ApiCcCallClassType CallClass;         /*!< DECT defined call classes. */
  ApiCcSignalType Signal;               /*!< DECT alert pattern. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format: { Ie, IeLength,
                                           IeData[], Ie, IeLength, IeData[], ...}. Each
                                           element is packed following the
                                           ApiInfoElementType. At reception the receiving
                                           task searches through the info data package to
                                           search for the requested elements and pick out
                                           the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CALLED_NUMBER]
                                           [API_IE_CALLING_NUMBER] 
                                           [API_IE_CALLING_NAME]
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_LINE_ID]
                                           [API_IE_AUDIO_DATA_FORMAT]
                                           
                                           The FP can only call a specific PP. The
                                           destination is specified using TerminalId. 
                                           Full-featured bases can specify ?All handsets?
                                           with API_TERMINAL_ID_ALL_PP
                                            */
} PACKED_STRUCT ApiFpCcSetupReqType;

/*! This mail is used to confirm the API_FP_CC_SETUP_REQ command. */
typedef struct ApiFpCcSetupCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SETUP_CFM = 0x4403 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  rsuint8 SystemCallId;                 /*!< System-wide call ID (NG-DECT call
                                           identification) */
  RsStatusType Status;                  /*!< Indicates whether the call is made or not. */
  ApiCcBasicServiceType BasicService;   /*!< Narrow/wide band speech encoding */
  ApiCcCallClassType CallClass;         /*!< DECT defined call classes. */
  ApiFpCcAudioIdType AudioId;
} PACKED_STRUCT ApiFpCcSetupCfmType;

/*! This mail is used by the MCU to request the FP to enter the ?overlap
   sending? state and send CC-SETUP-ACK message to the PP initiating the call. */
typedef struct ApiFpCcSetupAckReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SETUP_ACK_REQ = 0x4423 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiCcSignalType Signal;               /*!< Alert signal. */
  ApiCcProgressIndType ProgressInd;     /*!< Call progress information (e.g. in band
                                           audio) */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_AUDIO_DATA_FORMAT] */
}PACKED_STRUCT ApiFpCcSetupAckReqType;

/*! This mail is used to confirm the API_FP_CC_SETUP_ACK_REQ command. */
typedef struct ApiFpCcSetupAckCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SETUP_ACK_CFM = 0x4424 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  RsStatusType Status;                  /*!< Indicates whether the call is made or not. */
}PACKED_STRUCT ApiFpCcSetupAckCfmType;

/*! This mail is used by the MCU to tell the PP that the call is delivered
   to the remote. */
typedef struct ApiFpCcCallProcReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_CALL_PROC_REQ = 0x4415 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiCcProgressIndType ProgressInd;     /*!< Call progress information (e.g. in band
                                           audio) */
  ApiCcSignalType Signal;               /*!< DECT alert pattern. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_AUDIO_DATA_FORMAT] */
}PACKED_STRUCT ApiFpCcCallProcReqType;

/*! Used by the FP to confirm the API_FP_CC_CALL_PROC_REQ. */
typedef struct ApiFpCcCallProcCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_CALL_PROC_CFM = 0x4416 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
}PACKED_STRUCT ApiFpCcCallProcCfmType;

/*! This mail is used by the FP to inform the MCU when the PP has started
   alerting / ringing when an incoming call is received. */
typedef struct ApiFpCcAlertIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_ALERT_IND = 0x4404 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CODEC_LIST]  
                                           [API_IE_PROPRIETARY] */
}PACKED_STRUCT ApiFpCcAlertIndType;

/*! This command is used by the MCU to inform the PP when the remote part
   has started the alerting / ringing. */
typedef struct ApiFpCcAlertReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_ALERT_REQ = 0x4405 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiCcProgressIndType ProgressInd;     /*!< Call progress information (e.g. in band
                                           audio). */
  ApiCcSignalType Signal;               /*!< DECT alert pattern. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_AUDIO_DATA_FORMAT] */
}PACKED_STRUCT ApiFpCcAlertReqType;

/*! This mail is used to confirm the API_FP_CC_ALLERT_REQ command. */
typedef struct ApiFpCcAlertCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_ALERT_CFM = 0x4406 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
}PACKED_STRUCT ApiFpCcAlertCfmType;

/*! This mail is used to inform the MCU when a user has pressed the hook
   key to answer an incoming call on a PP. */
typedef struct ApiFpCcConnectIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_CONNECT_IND = 0x4407 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_PROPRIETARY] */
}PACKED_STRUCT ApiFpCcConnectIndType;

/*! This command is used by the MCU to inform the PP whether the call was
   accepted or not. */
typedef struct ApiFpCcConnectResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_CONNECT_RES = 0x4408 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  RsStatusType Status;                  /*!< Indicates whether the call was accepted
                                           (AS_SUCCESS) or not (AS_REJECTED). */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements: 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_AUDIO_DATA_FORMAT] */
}PACKED_STRUCT ApiFpCcConnectResType;

/*! This command is used by the MCU to request the FP to establish a
   connection to the PP specified. */
typedef struct ApiFpCcConnectReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_CONNECT_REQ = 0x4409 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_AUDIO_DATA_FORMAT] */
}PACKED_STRUCT ApiFpCcConnectReqType;

/*! This mail is used to confirm the API_FP_CC_CONNECT_REQ command. */
typedef struct ApiFpCcConnectCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_CONNECT_CFM = 0x440A */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_PROPRIETARY] */
}PACKED_STRUCT ApiFpCcConnectCfmType;

/*! This mail is used to inform the MCU when a user has pressed the on hook
   key to disconnect an ongoing call or reject an incoming call. */
typedef struct ApiFpCcReleaseIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_RELEASE_IND = 0x440F */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiCcReleaseReasonType Reason;        /*!< Release reason. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_RELEASE_EXT_REASON]
                                           [API_IE_CODECLIST] */
}PACKED_STRUCT ApiFpCcReleaseIndType;

/*! This mail is used by the MCU to inform the PP when the call is
   released. */
typedef struct ApiFpCcReleaseResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_RELEASE_RES = 0x4410 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  RsStatusType Status;                  /*!< Indicates whether the call is release or
                                           not. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_PROPRIETARY] */
}PACKED_STRUCT ApiFpCcReleaseResType;

/*! This mail is used by the MCU to terminate a call. */
typedef struct ApiFpCcReleaseReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_RELEASE_REQ = 0x4411 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiCcReleaseReasonType Reason;        /*!< Release reason. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_RELEASE_EXT_REASON]
                                           [API_IE_PROPRIETARY] */
}PACKED_STRUCT ApiFpCcReleaseReqType;

/*! This mail is used to confirm the API_FP_CC_RELEASE_REQ command. */
typedef struct ApiFpCcReleaseCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_RELEASE_CFM = 0x4412 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_PROPRIETARY] */
}PACKED_STRUCT ApiFpCcReleaseCfmType;

/*! This mail is used to inform the MCU when e.g. a connection setup has
   been rejected. */
typedef struct ApiFpCcRejectIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_REJECT_IND = 0x4413 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiCcReleaseReasonType Reason;        /*!< Reject reason. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_RELEASE_EXT_REASON] */
}PACKED_STRUCT ApiFpCcRejectIndType;

/*! This mail is used to send various information from PP to FP */
typedef struct ApiFpCcInfoIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_INFO_IND = 0x442D */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_MULTIKEYPAD]
                                           [API_IE_CALLED_NUMBER]
                                            [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID] */
}PACKED_STRUCT ApiFpCcInfoIndType;

/*! This mail is used to send various information from FP to PP. */
typedef struct ApiFpCcInfoReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_INFO_REQ = 0x442E */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiCcProgressIndType ProgressInd;     /*!< Inband information
                                           
                                           *If set to API_PROGRESS_INVALID (0xFF) it will
                                           be ignored by target. */
  ApiCcSignalType Signal;               /*!< Alert signal. This is used to request the
                                           MMI to start a certain local tone.
                                           
                                           *If set to API_CC_SIGNAL_CUSTOM_NONE (0xFF) it
                                           will be ignored by target. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CALLING_PARTY_NUMBER] 
                                           [API_IE_CALLING_PARTY_NAME]
                                            [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID]
                                           [API_IE_CALL_STATUS] */
}PACKED_STRUCT ApiFpCcInfoReqType;

/*! This mail is used by the MCU to request a CODEC change for a
   connection. */
typedef struct ApiFpCcModifyCodecReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_MODIFY_CODEC_REQ = 0x441D */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CODEC_LIST] */
}PACKED_STRUCT ApiFpCcModifyCodecReqType;

/*! Used by the FP to confirm the API_FP_CC_MODIFY_CODEC_REQ. */
typedef struct ApiFpCcModifyCodecCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_MODIFY_CODEC_CFM = 0x441E */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number.
 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
}PACKED_STRUCT ApiFpCcModifyCodecCfmType;

/*! This mail is used to inform the MCU when a PP has requested a CODEC
   change for a connection. */
typedef struct ApiFpCcModifyCodecIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_MODIFY_CODEC_IND = 0x441F */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CODEC_LIST] */
}PACKED_STRUCT ApiFpCcModifyCodecIndType;

/*! This mail is used by the MCU to accept or reject a code change
   requested by a PP. */
typedef struct ApiFpCcModifyCodecResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_MODIFY_CODEC_RES = 0x4420 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  RsStatusType Status;                  /*!< AS_SUCESS if the MCU accepts the CODEC
                                           change request or AS_REJECTED otherwise. */
}PACKED_STRUCT ApiFpCcModifyCodecResType;

/*! This mail is used by the FP to inform the MCU when the CODEC has been
   changed for a connection. */
typedef struct ApiFpCcIwuInfoCodecIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_IWU_INFO_CODEC_IND = 0x4421 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task searches through
                                           the info data package to search for the requested
                                           elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           [API_IE_CODEC_LIST] */
}PACKED_STRUCT ApiFpCcIwuInfoCodecIndType;

/*! This mail is sent from the application to the FP to request a new
   SystemCallId for a waiting call. */
typedef struct ApiFpCcSystemCallIdReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SYSTEM_CALL_ID_REQ = 0x4427 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number */
}PACKED_STRUCT ApiFpCcSystemCallIdReqType;

/*! This mail is sent from the FP to the application in return to a
   SystemCallId request. */
typedef struct ApiFpCcSystemCallIdCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SYSTEM_CALL_ID_CFM = 0x4428 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number */
  rsuint8 SystemCallId;                 /*!< System-wide call ID (NG-DECT call
                                           identification) */
}PACKED_STRUCT ApiFpCcSystemCallIdCfmType;

/*! This mail is used by the MCU to inform the FP how to route the audio.
    If the audio is routed between 2 handsets, it will be connected on the FP
   and does thus not use a PCM channel. */
typedef struct ApiFpCcReconnectAudioReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_RECONNECT_AUDIO_REQ = 0x442C */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiFpCcAudioIdType AudioId;
} PACKED_STRUCT ApiFpCcReconnectAudioReqType;

/*!  */
typedef struct ApiFpCcDisconnectAudioReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_DISCONNECT_AUDIO_REQ = 0x442F */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
} PACKED_STRUCT ApiFpCcDisconnectAudioReqType;

/*! This mail informs the Host about the selected ADPCM block. It is only
   to be used when the supplied audio handling is not used.
    The mail is sent at the time the ADPCM block is allocated.
    SW_NWK_SEND_SELECTED_ADPCM_IND must be defined. */
typedef struct ApiFpCcSelectedAdpcmIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SELECTED_ADPCM_IND = 0x4430 */
  ApiCallReferenceType CallReference;   /*!< Call reference/instance number. */
  ApiAdpcmType Adpcm;                   /*!< Selected ADPCM block */
} ApiFpCcSelectedAdpcmIndType;

/*! This command is used to enable/disable features in the FpCc API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiFpCcFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_FEATURES_REQ = 0x4450 */
  ApiFpCcFeatureType ApiFpCcFeature;    /*!< Requested features */
} PACKED_STRUCT ApiFpCcFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiFpCcFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_FEATURES_CFM = 0x4451 */
  RsStatusType Status;
  ApiFpCcFeatureType ApiFpCcFeature;    /*!< Supported features */
} PACKED_STRUCT ApiFpCcFeaturesCfmType;

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPopPack.h>
#else
  //#pragma pack(pop)
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
* FUNCTION:      SendApiFpCcSetupRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SETUP_RES = 0x4401
****************************************************************************/
void SendApiFpCcSetupRes ( RosTaskIdType Src,
                           ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                           RsStatusType Status,              /*!< Indicates whether the
                                                                call is accepted or not.
                                                                AS_REJECTED is used to
                                                                indicate that the call is
                                                                rejected by the user / host
                                                                and AS_SUCCESS is used to
                                                                indicate that the call is
                                                                accepted. */
                           ApiFpCcAudioIdType AudioId);      /*!<  */

/****************************************************************************
* FUNCTION:      SendApiFpCcSetupReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SETUP_REQ = 0x4402
****************************************************************************/
void SendApiFpCcSetupReq ( RosTaskIdType Src,
                           ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                           ApiTerminalIdType TerminalId,     /*!< Terminal destination
                                                                for the call. */
                           ApiFpCcAudioIdType AudioId,       /*!<  */
                           ApiCcBasicServiceType BasicService,
                                                             /*!< Narrow/wide band
                                                                speech encoding */
                           ApiCcCallClassType CallClass,     /*!< DECT defined call
                                                                classes. */
                           ApiCcSignalType Signal,           /*!< DECT alert pattern. */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the
                                                                format: { Ie, IeLength,
                                                                IeData[], Ie, IeLength,
                                                                IeData[], ...}. Each element
                                                                is packed following the
                                                                ApiInfoElementType. At
                                                                reception the receiving task
                                                                searches through the info
                                                                data package to search for
                                                                the requested elements and
                                                                pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CALLED_NUMBER]
                                                                [API_IE_CALLING_NUMBER] 
                                                                [API_IE_CALLING_NAME]
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_LINE_ID]
                                                                [API_IE_AUDIO_DATA_FORMAT]
                                                                
                                                                The FP can only call a
                                                                specific PP. The destination
                                                                is specified using
                                                                TerminalId. 
                                                                Full-featured bases can
                                                                specify ?All handsets? with API_TERMINAL_ID_ALL_PP
                                                                 */

/****************************************************************************
* FUNCTION:      SendApiFpCcSetupAckReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SETUP_ACK_REQ = 0x4423
****************************************************************************/
void SendApiFpCcSetupAckReq ( RosTaskIdType Src,
                              ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                              ApiCcSignalType Signal,        /*!< Alert signal. */
                              ApiCcProgressIndType ProgressInd,
                                                             /*!< Call progress
                                                                information (e.g. in band
                                                                audio) */
                              rsuint16 InfoElementLength,    /*!< The length of the Data
                                                                Information Element */
                              rsuint8 InfoElement[1]);       /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_AUDIO_DATA_FORMAT] */

/****************************************************************************
* FUNCTION:      SendApiFpCcCallProcReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_CALL_PROC_REQ = 0x4415
****************************************************************************/
void SendApiFpCcCallProcReq ( RosTaskIdType Src,
                              ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                              ApiCcProgressIndType ProgressInd,
                                                             /*!< Call progress
                                                                information (e.g. in band
                                                                audio) */
                              ApiCcSignalType Signal,        /*!< DECT alert pattern. */
                              rsuint16 InfoElementLength,    /*!< The length of the Data
                                                                Information Element */
                              rsuint8 InfoElement[1]);       /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_AUDIO_DATA_FORMAT] */

/****************************************************************************
* FUNCTION:      SendApiFpCcAlertReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_ALERT_REQ = 0x4405
****************************************************************************/
void SendApiFpCcAlertReq ( RosTaskIdType Src,
                           ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                           ApiCcProgressIndType ProgressInd,  /*!< Call progress
                                                                 information (e.g. in band
                                                                 audio). */
                           ApiCcSignalType Signal,           /*!< DECT alert pattern. */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_AUDIO_DATA_FORMAT] */

/****************************************************************************
* FUNCTION:      SendApiFpCcConnectRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_CONNECT_RES = 0x4408
****************************************************************************/
void SendApiFpCcConnectRes ( RosTaskIdType Src,
                             ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                             RsStatusType Status,            /*!< Indicates whether the
                                                                call was accepted
                                                                (AS_SUCCESS) or not
                                                                (AS_REJECTED). */
                             rsuint16 InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                             rsuint8 InfoElement[1]);        /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements: 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_AUDIO_DATA_FORMAT] */

/****************************************************************************
* FUNCTION:      SendApiFpCcConnectReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_CONNECT_REQ = 0x4409
****************************************************************************/
void SendApiFpCcConnectReq ( RosTaskIdType Src,
                             ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                             rsuint16 InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                             rsuint8 InfoElement[1]);        /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_AUDIO_DATA_FORMAT] */

/****************************************************************************
* FUNCTION:      SendApiFpCcReleaseRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_RELEASE_RES = 0x4410
****************************************************************************/
void SendApiFpCcReleaseRes ( RosTaskIdType Src,
                             ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                             RsStatusType Status,            /*!< Indicates whether the
                                                                call is release or not. */
                             rsuint16 InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                             rsuint8 InfoElement[1]);        /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
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
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiFpCcReleaseReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_RELEASE_REQ = 0x4411
****************************************************************************/
void SendApiFpCcReleaseReq ( RosTaskIdType Src,
                             ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                             ApiCcReleaseReasonType Reason,  /*!< Release reason. */
                             rsuint16 InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                             rsuint8 InfoElement[1]);        /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
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
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_RELEASE_EXT_REASON]
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiFpCcInfoReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_INFO_REQ = 0x442E
****************************************************************************/
void SendApiFpCcInfoReq ( RosTaskIdType Src,
                          ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                          ApiCcProgressIndType ProgressInd,  /*!< Inband information
                                                                
                                                                *If set to
                                                                API_PROGRESS_INVALID (0xFF)
                                                                it will be ignored by
                                                                target. */
                          ApiCcSignalType Signal,            /*!< Alert signal. This is
                                                                used to request the MMI to
                                                                start a certain local tone.
                                                                
                                                                *If set to
                                                                API_CC_SIGNAL_CUSTOM_NONE
                                                                (0xFF) it will be ignored by
                                                                target. */
                          rsuint16 InfoElementLength,        /*!< The length of the Data
                                                                Information Element */
                          rsuint8 InfoElement[1]);           /*!< The InfoElementList
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
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_CALLING_PARTY_NUMBER
                                                                ] 
                                                                [API_IE_CALLING_PARTY_NAME]
                                                                 [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID]
                                                                [API_IE_CALL_STATUS] */

/****************************************************************************
* FUNCTION:      SendApiFpCcModifyCodecReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_MODIFY_CODEC_REQ = 0x441D
****************************************************************************/
void SendApiFpCcModifyCodecReq ( RosTaskIdType Src,
                                 ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                                 rsuint16 InfoElementLength,  /*!< The length of the
                                                                 Data Information Element */
                                 rsuint8 InfoElement[1]);    /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task searches through the
                                                                info data package to search
                                                                for the requested elements
                                                                and pick out the info data.
                                                                
                                                                Possible Info elements:
                                                                [API_IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiFpCcModifyCodecRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_MODIFY_CODEC_RES = 0x4420
****************************************************************************/
void SendApiFpCcModifyCodecRes ( RosTaskIdType Src,
                                 ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                                 RsStatusType Status);       /*!< AS_SUCESS if the MCU
                                                                accepts the CODEC change
                                                                request or AS_REJECTED
                                                                otherwise. */

/****************************************************************************
* FUNCTION:      SendApiFpCcSystemCallIdReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SYSTEM_CALL_ID_REQ = 0x4427
****************************************************************************/
void SendApiFpCcSystemCallIdReq ( RosTaskIdType Src,
                                  ApiCallReferenceType CallReference);
                                                             /*!< Call
                                                                reference/instance number */

/****************************************************************************
* FUNCTION:      SendApiFpCcReconnectAudioReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_RECONNECT_AUDIO_REQ = 0x442C
****************************************************************************/
void SendApiFpCcReconnectAudioReq ( RosTaskIdType Src,
                                    ApiCallReferenceType CallReference,
                                                             /*!< Call
                                                                reference/instance number. */
                                    ApiFpCcAudioIdType AudioId);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiFpCcDisconnectAudioReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_DISCONNECT_AUDIO_REQ = 0x442F
****************************************************************************/
void SendApiFpCcDisconnectAudioReq ( RosTaskIdType Src,
                                     ApiCallReferenceType CallReference);
                                                             /*!< Call
                                                                reference/instance number. */

/****************************************************************************
* FUNCTION:      SendApiFpCcFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_FEATURES_REQ = 0x4450
****************************************************************************/
void SendApiFpCcFeaturesReq ( RosTaskIdType Src,
                              ApiFpCcFeatureType ApiFpCcFeature);
                                                             /*!< Requested features */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPCC_H */


