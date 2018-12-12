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
* Definition of the ApiTypes interface.
*/


#ifndef APITYPES_H
#define APITYPES_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/RsStandard.h>
#include <Phoenix/Api/RosPrimitiv.h>
/****************************************************************************
*                               Macros/Defines
****************************************************************************/
typedef struct
{
   PrimitiveType  PrimitiveIdentifier;
   uint8          bKey;
}PACKED_STRUCT KeyMessageReqType;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
}PACKED_STRUCT recSendMailP0Type;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
  uint8         bParm1;
}PACKED_STRUCT recSendMailP1Type;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
  uint8         bParm1;
  uint8         bParm2;
}PACKED_STRUCT recSendMailP2Type;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
  uint8         bParm1;
  uint8         bParm2;
  uint8         bParm3;
}PACKED_STRUCT recSendMailP3Type;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
  uint8         bData[500];
}PACKED_STRUCT recDataType;


/*! The API_LINEID_NONE is used by a PP to inform the FP that any line can
   be used. */
#define API_LINEID_NONE 0x7F

/*! The ApiLineIdInfoType is a bitarray, with the following defines. */
#define API_LINEID_INFO_SCT RSBIT1   /*!< Second call type
                                        0 ~ Second calls are handled with 'common parallel
                                        call   procedures' (e.g. VoIP lines)
                                        1 ~ Second calls are handled with in-band
                                        signalling (e.g. PSTN lines) */

/*! The ApiLineIdInfoType is a bitarray, with the following defines. */
#define API_LINEID_INFO_NDT RSBIT0   /*!< Network delay type
                                        0 ~ connected to a network with low delay (e.g. PSTN/ISDN)
                                        1 ~ connected to a network with significant delay
                                        (e.g. VoIP) */

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  //#pragma pack(push,1)
#endif

/*! This type is used to hold a handset id or a ULE terminal Id.
    Valid values: [1; N] where N is equal to the max number of handsets that
   can be registered on the FP. */
#if 0
typedef enum RSENUMTAG(ApiTerminalIdType)
{

  API_TERMINAL_ID_BROADCAST_AUDIO = 0xFF 

} RSENUM8/*16*/(ApiTerminalIdType);
#else
typedef enum RSENUMTAG(ApiTerminalIdType)
{
  API_TERMINAL_ID_BROADCAST_AUDIO = 0xFFFD, /*!< This id is used for setting up
                                               broadcast audio.
                                               Not used in current implementation */
  API_TERMINAL_ID_ALL_PP          = 0xFFFE, /*!< CVM handles setup of incoming calls.
                                               Not used in current implementation */
  API_TERMINAL_ID_INVALID         = 0xFFFF  /*!< Undefined terminal id */

} RSENUM16(ApiTerminalIdType);
#endif
/*! This type is used to describe the end point that connects the audio
   between CVM and the Host. This can be f. ex. PCM or USB. */
typedef rsuint8 ApiAudioEndPointIdType;
 /*!< Normally 0 ~ PCM0, 1 ~ PCM1 etc. */

/*! This struct is used to specify the Model ID type. */
typedef struct {
  rsuint16 MANIC;                       /*!< The manufacturer code of the device. The
                                           EMC code of the device is used as manufacturer
                                           code. */
  rsuint8 MODIC;                        /*!< The model code of the device. */
} PACKED_STRUCT ApiModelIdType;

/*! This enum defines the DECT types supported by the API. */
typedef enum RSENUMTAG(ApiDectTypeType)
{
  API_EU_DECT           = 0x00, /*!< EU DECT mode. */
  API_US_DECT           = 0x01, /*!< US DECT mode. */
  API_SA_DECT           = 0x02, /*!< SA DECT mode. */
  API_TAIWAN_DECT       = 0x03, /*!< Taiwan DECT mode. */
  API_MALAYSIA_DECT     = 0x04, /*!< Malaysia DECT mode. */
  API_CHINA_DECT        = 0x05, /*!< China DECT mode. */
  API_THAILAND_DECT     = 0x06, /*!< Thailand DECT mode. */
  API_BRAZIL_DECT       = 0x07, /*!< Brazil DECT mode. */
  API_US_DECT_EXT_FREQ  = 0x08, /*!< US DECT mode with extended freq band. */
  API_KOREAN_DECT       = 0x09, /*!< Korean DECT mode. */
  API_JAPAN_DECT        = 0x0A, /*!< Japan DECT with 2 channels mode.
                                   (In Pp used for 2 and 5 channels mode) */
  API_JAPAN_DECT_5CH    = 0x0B, /*!< Japan DECT with PHS and 5 channels mode. */
  API_DECT_TYPE_INVALID = 0xFF  /*!< [0x09; 0xFF] is invalid. */
} RSENUM8(ApiDectTypeType);

/*! This enum defines the status of the cradle detection to the MMI */
typedef enum RSENUMTAG(ApiCradleStatusType)
{
  API_CRADLE_INACTIVE    = 0x00, /*!< Cradle not detected */
  API_CRADLE_ACTIVE      = 0x01, /*!< Cradle detected */
  API_CRADLE_UNSUPPORTED = 0x02, /*!< Cradle detection not supported. */
  API_CRADLE_INVALID     = 0xFF  /*!< [0x03; 0xFF] is invalid. */
} RSENUM8(ApiCradleStatusType);

/*! This struct is used to hold both time and date info. */
typedef struct
{
  rsuint8 Year;                         /*!< Year since 1900. */
  rsuint8 Month;                        /*!< Month 1..12 */
  rsuint8 Day;                          /*!< Day 1..31 */
  rsuint8 Hour;                         /*!< Hour 0..23 */
  rsuint8 Minute;                       /*!< Minute 1..59 */
  rsuint8 Second;                       /*!< Second 1..59 */
  rsuint8 TimeZone;                     /*!< The Time Zone indicates the difference,
                                           expressed in quarters of an hour, between the
                                           local time and GMT. In the first of the two
                                           semi-octets, the first bit represents the
                                           algebraic sign of this difference (0: positive;
                                           1: negative).
                                           The Time Zone code enables the receiver to
                                           calculate the equivalent time in GMT from the
                                           other semi-octets in the element, or indicate the
                                           time zone (GMT, GMT+1H, etc.), or perform other
                                           similar calculations as required by the
                                           implementation. */
} PACKED_STRUCT ApiTimeDateCodeType;

/*! See ETSI EN 300 175-5, TIME-DATE information element */
typedef enum RSENUMTAG(ApiTimeDateInterpretationType)
{
  API_INTER_CURRENT_TIME_DATE  = 0x00, /*!< The current time/date */
  API_INTER_TIME_DURATION      = 0x01, /*!< Time duration (in Years, Months, Days and/or
                                          Hours, Minutes,
                                          Seconds, Time Zone = 0) */
  API_INTER_DELIVER_MMS_MSG    = 0x20, /*!< The time/date at which to start
                                          forwarding/delivering the MMS message */
  API_INTER_MMS_DATA_CREATED   = 0x21, /*!< The time/date the MMS user data was created */
  API_INTER_MMS_DATA_MODIFIED  = 0x22, /*!< The time/date the MMS user data was last
                                          modified */
  API_INTER_MCE_DATA_RECIEVED  = 0x23, /*!< The time/date the message was received by
                                          the MCE */
  API_INTER_DATA_ACCESSED_END  = 0x24, /*!< The time/date the message was
                                          delivered/accessed by the End Entity */
  API_INTER_TIME_DATE_STAMP_ID = 0x28  /*!< The time/date stamp for use as an identifier */
} RSENUM8(ApiTimeDateInterpretationType);

/*! See ETSI EN 300 175-5, TIME-DATE information element */
typedef enum RSENUMTAG(ApiTimeDateCodingType)
{
  API_CODING_TIME      = 0x01, /*!< Time */
  API_CODING_DATE      = 0x02, /*!< Date */
  API_CODING_TIME_DATE = 0x03  /*!< Time and date */
} RSENUM8(ApiTimeDateCodingType);

/*! String characters */
typedef rsuint8 ApiCcXCharType;

/*! This enum defies the signal types supported. */
typedef enum RSENUMTAG(ApiCcSignalType)
{
  API_CC_SIGNAL_DIAL_TONE_ON               = 0x00, /*!< Local inband dial tone */
  API_CC_SIGNAL_RINGBACK_TONE_ON           = 0x01, /*!< Local inband ringback tone */
  API_CC_SIGNAL_INTERCEPT_TONE_ON          = 0x02, /*!< Local inband intercept tone */
  API_CC_SIGNAL_NETWORK_CONGESTION_TONE_ON = 0x03, /*!< Local inband nwk.congestion tone */
  API_CC_SIGNAL_BUSY_TONE_ON               = 0x04, /*!< Local inband busy tone */
  API_CC_SIGNAL_CONFIRM_TONE_ON            = 0x05, /*!< Local inband confirm tone */
  API_CC_SIGNAL_ANSWER_TONE_ON             = 0x06, /*!< Local inband answer tone */
  API_CC_SIGNAL_CALL_WAITING_TONE_ON       = 0x07, /*!< Local inband call waiting tone */
  API_CC_SIGNAL_OFF_HOOK_WARNING_TONE      = 0x08, /*!< Local inband hookoff warning
                                                      tone */
  API_CC_SIGNAL_NEGATIVE_ACKNOWLEDGEMENT   = 0x09, /*!< Local inband neg.ack. tone */
  API_CC_SIGNAL_TONES_OFF                  = 0x3F, /*!< Tone off */
  API_CC_SIGNAL_ALERT_ON_PATTERN_0_INT     = 0x40, /*!< Internal Alert tone */
  API_CC_SIGNAL_ALERT_ON_PATTERN_1         = 0x41, /*!< External Alert tone */
  API_CC_SIGNAL_ALERT_ON_PATTERN_2         = 0x42, /*!< Custom Alert tone */
  API_CC_SIGNAL_ALERT_ON_PATTERN_3         = 0x43, /*!< Custom Alert tone */
  API_CC_SIGNAL_ALERT_ON_PATTERN_4         = 0x44, /*!< Custom Alert tone */
  API_CC_SIGNAL_ALERT_ON_PATTERN_5         = 0x45, /*!< Custom Alert tone */
  API_CC_SIGNAL_ALERT_ON_PATTERN_6         = 0x46, /*!< Custom Alert tone */
  API_CC_SIGNAL_ALERT_ON_PATTERN_7         = 0x47, /*!< Custom Alert tone */
  API_CC_SIGNAL_ALERT_ON_CONTINUOUS        = 0x48, /*!< Continuous alert */
  API_CC_SIGNAL_ALERT_OFF                  = 0x4F, /*!< Alert tone off */
  API_CC_SIGNAL_CUSTOM_FIRST               = 0x80, /*!< Custom tone */
  API_CC_SIGNAL_CUSTOM_NONE                = 0xFF  /*!< No tone */
} RSENUM8(ApiCcSignalType);

/*! This enum defines the basic voice services supported. */
typedef enum RSENUMTAG(ApiCcBasicServiceType)
{
  API_BASIC_SPEECH    = 0x00, /*!< Basic speech using default setup attributes. */
  API_LRMS_SERVICE    = 0x05, /*!< LRMS service */
  API_WIDEBAND_SPEECH = 0x08, /*!< Wideband speech using default setup attributes. */
  API_LDS_CLASS4      = 0x09, /*!< Light data services: SUOTA (TS 102 527-4 [76]), Class
                                 4 DPRS management using default setup attributes. */
  API_LDS_CLASS3      = 0x0A, /*!< Light data services: SUOTA (TS 102 527-4 [76]), Class
                                 3 DPRS management using default setup attributes. */
  API_BS_OTHER        = 0x0F  /*!< The service is defined by adding <<IWU-ATTRIBUTES>> +
                                 <<CALL-ATTRIBUTES>> elements to the {CC-SETUP} message. */
} RSENUM8(ApiCcBasicServiceType);

/*! This enum defines the call classes supported. */
typedef enum RSENUMTAG(ApiCcCallClassType)
{
  API_CC_LIA_SERVICE = 0x02, /*!< List Access Service call */
  API_CC_MESSAGE     = 0x04, /*!< Message call */
  API_CC_NORMAL      = 0x08, /*!< Normal call */
  API_CC_INTERNAL    = 0x09, /*!< Internal call */
  API_CC_SERVICE     = 0x0B  /*!< Service call */
} RSENUM8(ApiCcCallClassType);

/*! This enum defines the possible call progress indications supported by
   the unit. */
typedef enum {
  API_IN_BAND_AVAILABLE     = 0x08, /*!< In band tones available. */
  API_IN_BAND_NOT_AVAILABLE = 0x09, /*!< In band tones is not available. */
  API_PROGRESS_INVALID      = 0xFF  /*!< [0x02; 0xFF] is reserved. */
} RSENUM8(ApiCcProgressIndType);

/*! These values are specified in ETSI EN 300 175-5 section 7.6.7 */
typedef enum RSENUMTAG(ApiCcReleaseReasonType)
{
  API_RR_NORMAL                          = 0x00, /*!< RELEASE_NORMAL */
  API_RR_UNEXPECTED_MESSAGE              = 0x01, /*!< RELEASE_UNEXPECTED_MESSAGE */
  API_RR_UNKNOWN_TRANSACTION_ID          = 0x02, /*!<  */
  API_RR_MANDATORY_IE_MISSING            = 0x03, /*!<  */
  API_RR_INVALID_IE_CONTENTS             = 0x04, /*!<  */
  API_RR_INCOMPATIBLE_SERVICE            = 0x05, /*!<  */
  API_RR_SERVICE_NOT_IMPLEMENTED         = 0x06, /*!<  */
  API_RR_NEGOTIATION_NOT_SUPPORTED       = 0x07, /*!<  */
  API_RR_INVALID_IDENTY                  = 0x08, /*!< SW_RR_INVALID_IDENTY */
  API_RR_AUTHEN_FAILED                   = 0x09, /*!< Authentication failed */
  API_RR_UNKNOWN_IDENTITY                = 0x0a, /*!< Unknown identity */
  API_RR_NEGOTIATION_FAILED              = 0x0b, /*!<  */
  API_RR_TIMER_EXPIRY                    = 0x0d, /*!< Timer expiry */
  API_RR_PARTIAL_RELEASE                 = 0x0e, /*!< Partial release */
  API_RR_UNKNOWN                         = 0x0f, /*!< Unknown */
  API_RR_USER_DETACHED                   = 0x10, /*!< User detached */
  API_RR_USER_OUT_RANGE                  = 0x11, /*!< User not in range */
  API_RR_USER_UNKNOWN                    = 0x12, /*!< User unknown */
  API_RR_USER_ACTIVE                     = 0x13, /*!< User already active */
  API_RR_USER_BUSY                       = 0x14, /*!< User busy */
  API_RR_USER_REJECTION                  = 0x15, /*!< User rejection */
  API_RR_USER_CALL_MODIFY                = 0x16, /*!<  */
  API_RR_EXTERNAL_HANDOVER_NOT_SUPPORTED = 0x21, /*!<  */
  API_RR_NETWORK_PARAMETERS_MISSING      = 0x22, /*!<  */
  API_RR_EXTERNAL_HANDOVER_RELEASE       = 0x23, /*!<  */
  API_RR_OVERLOAD                        = 0X31, /*!< Overload */
  API_RR_INSUFFICIENT_RESOURCES          = 0x32, /*!< Insufficient resources */
  API_RR_IWU_CONGESTION                  = 0x34, /*!< IWU congestion */
  API_RR_CALL_RESTRICTION                = 0x40, /*!< Proprietary error code. */
  API_RR_SECURITY_ATTACK_ASSUMED         = 0x40, /*!<  */
  API_RR_ENCRYPTION_ACTIVATION_FAILED    = 0x41, /*!<  */
  API_RR_RE_KEYING_FAILED                = 0x42, /*!<  */
  API_RR_MAX                                     /*!<  */
} RSENUM8(ApiCcReleaseReasonType);

/*! IA5 characters (see ITU-T Recommendation T.50) */
typedef rsuint8 ApiIa5CharType;

/*! Same as ApiTimeDateCodeType. */
typedef ApiTimeDateCodeType ApiCcNwkTimeDateCodeType;

/*! Specifies the type of extended release reason. */
typedef enum RSENUMTAG(ApiCcReasonExtTypeType)
{
  API_RE_NO_ERROR_CODE   = 0x00, /*!<  */
  API_RE_STD_ERROR_CODE  = 0x01, /*!< StdErrorCode */
  API_RE_SIP_REASON      = 0x02, /*!< SipCallReleaseCause. */
  API_RE_SIP_REASON_TEXT = 0x03, /*!<  */
  API_RE_MAX_REASON      = 0x04  /*!<  */
} RSENUM8(ApiCcReasonExtTypeType);

/*! Extended release reason value. */
typedef union ApiCcReleaseExtReasonValueType
{
  RsStatusType StdErrorCode;            /*!< Standard error code. */
  rsuint16 SipCallReleaseCause;         /*!< SwSipCallReleaseCauseType */
  ApiCcXCharType ErrorText[1];          /*!< SPI error text. */
} PACKED_STRUCT ApiCcReleaseExtReasonValueType;

/*! Extended release reason. */
typedef struct ApiCcReleaseExtReasonType
{
  ApiCcReasonExtTypeType ReasonExtType; /*!< Type of extended release reason. */
  ApiCcReleaseExtReasonValueType ReleaseExtReasonValue; /*!< Extended release reason
                                                            value. */
} PACKED_STRUCT ApiCcReleaseExtReasonType;

/*! This type is used to hold information elements received from the DECT
   protocol */
typedef enum RSENUMTAG(ApiIeType) 
{
  API_IE_CODEC_LIST                      = 0x01,   /*!< Holding supported audio codecs.
                                                      Associated type: ApiCodecListType */
  API_IE_MULTIKEYPAD                     = 0x02,   /*!< Holding display string to be
                                                      shown on the display
                                                      Associated type: ApiMultikeyPadType */
  API_IE_MULTI_DISPLAY                   = 0x03,   /*!< Holding keypads/digits to be dialed
                                                      Associated type: ApiMultiDisplayType */
  API_IE_CALLED_NUMBER                   = 0x04,   /*!< Holding the called number.
                                                      Associated type: ApiCalledNumberType */
  API_IE_CALLING_PARTY_NUMBER            = 0x05,   /*!< Holding calling party number of
                                                      other party (DECT / Cat-iq clip)
                                                      Associated type: ApiCallingNumberType */
  API_IE_CALLING_PARTY_NAME              = 0x06,   /*!< Holding calling party name of
                                                      other party (Cat-iq clip)
                                                      Associated type: ApiCallingNameType */
  API_IE_RELEASE_EXT_REASON              = 0x07,   /*!< Holding release/reject reason
                                                      from or to the FP swicth
                                                      Associated type:
                                                      ApiReleaseExtReasonType */
  API_IE_IWU_TO_IWU                      = 0x08,   /*!< Holding InterWorkingUnit data
                                                      (field data)
                                                      Associated type: ApiIwuToIwuType */
  API_IE_PROPRIETARY                     = 0x09,   /*!< Holding Proprietary data
                                                      (proprietary a-field data)
                                                      Associated type:
                                                      ApiEscapeToProprietaryType */
  API_IE_UNITDATA                        = 0x0A,   /*!< Holding Proprietary Unitdata
                                                      data (broadcast data)
                                                      Associated type: ApiUnitdataType */
  API_IE_MODEL_ID                        = 0x0B,   /*!< Holding the Manufacture and
                                                      Model id of the remote device.
                                                      Associated type: ApiModelIdType */
  API_IE_LINE_ID                         = 0x0C,   /*!< Holding the used line no. and
                                                      line information.
                                                      Associated type: ApiLineIdListType */
  API_IE_SYSTEM_CALL_ID                  = 0x0D,   /*!< Holding a unique call reference
                                                      Associated type:
                                                      ApiSystemCallIdListType */
  API_IE_AVAILABLE_APIS                  = 0x0E,   /*!< Set of APIs available.
                                                      Associated type: ApiAvailableApisType */
  API_IE_AUDIO_DATA_FORMAT               = 0x0F,   /*!< Audio encoding on the external
                                                      audio interface. (PCM, USB etc.)
                                                      Associated type:
                                                      ApiAudioDataFormatListType */
  API_IE_CALL_STATUS                     = 0x10,   /*!< Holding call status
                                                      Associated type:
                                                      ApiCallStatusListType */
  API_IE_TIME_DATE                       = 0x11,   /*!< Holding time date
                                                      Associated type: ApiTimeDateType */
  API_IE_PORTABLE_IDENTITY               = 0x12,   /*!< Holding portable identity
                                                      Associated type: ApiSmsPortIdType
                                                      Only available if SMS support is
                                                      enabled */
  API_IE_MMS_GEN_HEADER                  = 0x13,   /*!< Holding mms generic header
                                                      Associated type: ApiSmsMmsGenHeaderType
                                                      Only available if SMS support is
                                                      enabled */
  API_IE_MMS_OBJ_HEADER                  = 0x14,   /*!< Holding mms object header
                                                      Associated type: ApiSmsMmsObjHeaderType
                                                      Only available if SMS support is
                                                      enabled */
  API_IE_MMS_EXT_HEADER                  = 0x15,   /*!< Holding mms extended header
                                                      Associated type: ApiSmsMmsExtHeaderType
                                                      Only available if SMS support is
                                                      enabled */
  API_IE_SEGMENT_INFO                    = 0x16,   /*!< Holding segment info
                                                      Associated type: ApiSmsSegmentInfoType
                                                      Only available if SMS support is
                                                      enabled */
  API_IE_CALLED_NAME                     = 0x17,   /*!< Holding the called name and firstname.
                                                      Associated type: ApiCalledNameType */
  API_IE_BASIC_TERMCAPS                  = 0x18,   /*!< Holding the basic PP terminal
                                                      capabilities: 
                                                      Associated type: ApiBasicTermCapsType */
  API_IE_TERMCAPS                        = 0x19,   /*!< Holding the PP terminal capabilities.
                                                      Associated type: ApiTermCapsType */
  API_IE_FACILITY                        = 0x1A,   /*!< Associated type: ApiFacilityType */
  API_IE_LOCATION_STATUS                 = 0x1B,   /*!< Associated type:
                                                      ApiMmLocationStatusType */
  API_IE_FP_CAPABILITIES                 = 0x1C,   /*!< Associated type:
                                                      ApiFpCapabilitiesType */
  API_IE_FP_EXTENDED_CAPABILITIES        = 0x1D,   /*!< Associated type:
                                                      ApiFpExtendedCapabilitiesType */
  API_IE_FP_EXTENDED_CAPABILITIES2       = 0x1E,   /*!< Associated type:
                                                      ApiFpExtendedCapabilities2Type */
  API_IE_LAS_SORTING_FIELD_IDENTIFIERS   = 0x1001, /*!< Associated type:
                                                      ApiLasSortingFieldsType */
  API_IE_LAS_EDITABLE_FIELDS             = 0x1002, /*!< Associated type:
                                                      ApiLasEditableFieldsType */
  API_IE_LAS_NON_EDITABLE_FIELDS         = 0x1003, /*!< Associated type:
                                                      ApiLasNonEditableFieldsType */
  API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS = 0x1004, /*!< Associated type:
                                                      ApiLasReqFldIdentifiersType */
  API_IE_LAS_SEARCH_TEXT                 = 0x1005, /*!< Associated type:
                                                      ApiLasSearchTextType */
  API_IE_LAS_LIST_IDENTIFIERS            = 0x1006, /*!< Associated type:
                                                      ApiLasListIdentifierType */
  API_IE_LAS_NUMBER                      = 0x1007, /*!< Associated type:
                                                      ApiLasNumberType */
  API_IE_LAS_NAME                        = 0x1008, /*!< Associated type: ApiLasNameType */
  API_IE_LAS_DATE_TIME                   = 0x1009, /*!< Associated type:
                                                      ApiLasDateTimeType */
  API_IE_LAS_ENTRY_READSTATUS            = 0x100A, /*!< Associated type:
                                                      ApiLasEntryReadStatusType */
  API_IE_LAS_LINE_NAME                   = 0x100B, /*!< Associated type:
                                                      ApiLasLineNameType */
  API_IE_LAS_LINE_ID                     = 0x100C, /*!< Associated type:
                                                      ApiLasLineIdType */
  API_IE_LAS_NUMBER_OF_CALLS             = 0x100D, /*!< Associated type:
                                                      ApiLasNumberOfCallsType */
  API_IE_LAS_CALL_TYPE                   = 0x100E, /*!< Associated type: ApiLasCallType */
  API_IE_LAS_FIRST_NAME                  = 0x100F, /*!< Associated type:
                                                      ApiLasFirstNameType */
  API_IE_LAS_CONTACT_NUMBER              = 0x1010, /*!< Associated type:
                                                      ApiLasContactNumberType */
  API_IE_LAS_ASS_MELODY                  = 0x1011, /*!< Associated type:
                                                      ApiLasAssMelodyType */
  API_IE_LAS_PIN_CODE                    = 0x1012, /*!< Associated type:
                                                      ApiLasPinCodeType */
  API_IE_LAS_CLOCK_MASTER                = 0x1013, /*!< Associated type:
                                                      ApiLasClockMasterType */
  API_IE_LAS_BASE_RESET                  = 0x1014, /*!< Associated type:
                                                      ApiLasBaseResetType */
  API_IE_LAS_IP_ADDRESS_TYPE             = 0x1015, /*!< Associated type: ApiLasIpAdrType */
  API_IE_LAS_IP_ADDRESS                  = 0x1016, /*!< Associated type:
                                                      ApiLasIpAdrValueType */
  API_IE_LAS_IP_SUBNET_MASK              = 0x1017, /*!< Associated type:
                                                      ApiLasIpSubnetMaskType */
  API_IE_LAS_IP_GATEWAY                  = 0x1018, /*!< Associated type:
                                                      ApiLasIpGatewayType */
  API_IE_LAS_IP_DNS                      = 0x1019, /*!< Associated type: ApiLasIpDnsType */
  API_IE_LAS_FIRMWARE_VERSION            = 0x101A, /*!< Associated type:
                                                      ApiLasVerFirmwareType */
  API_IE_LAS_EEPROM_VERSION              = 0x101B, /*!< Associated type:
                                                      ApiLasVerEePromType */
  API_IE_LAS_HARDWARE_VERSION            = 0x101C, /*!< Associated type:
                                                      ApiLasVerHardwareType */
  API_IE_LAS_ATTACHED_HANDSETS           = 0x101D, /*!< Associated type:
                                                      ApiLasAttachedHandsetsType */
  API_IE_LAS_DIALING_PREFIX              = 0x101E, /*!< Associated type:
                                                      ApiLasDialingPrefixType */
  API_IE_LAS_FP_MELODY                   = 0x101F, /*!< Associated type:
                                                      ApiLasFpMelodyType */
  API_IE_LAS_FP_VOLUME                   = 0x1020, /*!< Associated type:
                                                      ApiLasFpVolumeType */
  API_IE_LAS_BLOCKED_NUMBERS             = 0x1021, /*!< Associated type:
                                                      ApiLasBlockedNumberType */
  API_IE_LAS_MULTIPLE_CALL               = 0x1022, /*!< Associated type:
                                                      ApiLasMultipleCallType */
  API_IE_LAS_INTRUSION_CALL              = 0x1023, /*!< Associated type:
                                                      ApiLasIntrusionCallType */
  API_IE_LAS_PERMANENT_CLIR              = 0x1024, /*!< Associated type:
                                                      ApiLasPermanentClirType */
  API_IE_LAS_CALL_FORWARDING_CFU         = 0x1025, /*!< Associated type:
                                                      ApiLasCallForwardingCfuType */
  API_IE_LAS_CALL_FORWARDING_CFNA        = 0x1026, /*!< Associated type:
                                                      ApiLasCallForwardingCfnaType */
  API_IE_LAS_CALL_FORWARDING_CFB         = 0x1027, /*!< Associated type:
                                                      ApiLasCallForwardingCfbType */
  API_IE_LAS_CALL_INTERCEPTION           = 0x1028, /*!< Associated type:
                                                      ApiLasCallInterceptionType */
  API_IE_LAS_EMISSION_MODE               = 0x1029, /*!< Associated type:
                                                      ApiLasEmissionModeType */
  API_IE_LAS_NEW_PIN_CODE                = 0x1030, /*!< Associated type:
                                                      ApiLasNewPinCodeType */
  API_IE_LAS_COUNTRY_CODE                = 0x1031, /*!< Associated type:
                                                      ApiLasCountryCodeType */
  API_IE_LAS_IPMAC                       = 0x1032, /*!< Associated type: ApiLasIpMacType */
  API_IE_LAS_DECT_MODE                   = 0x1033, /*!< Associated type:
                                                      ApiLasDectModeType */
  API_IE_LAS_PIN_PROTECTED_FIELDS        = 0x1034, /*!< Associated type:
                                                      ApiLasPinProtectedFieldsType */
  API_IE_LAS_DISABLED_FIELDS             = 0x1035, /*!< Associated type:
                                                      ApiLasDisabledFieldsType */
  API_IE_LOCKED_ENTRIES_LIST             = 0x1036, /*!< Associated type:
                                                      ApiLasLockedEntriesListType */
                                                   /*!< IE id [0x1000-0x1FFF] is
                                                      reserved for LAS */
  API_IE_RP_BABYMONITOR                  = 0x2001, /*!< Associated type:
                                                      ApiRpBabyMonitorType */
  API_IE_RP_CLIP                         = 0x2002, /*!< Associated type: ApiRpClipType */
  API_IE_RP_TAM                          = 0x2003, /*!< Associated type: ApiRpTamType */
  API_IE_AUDIO_EXT_INDEX                 = 0x3000, /*!< Associated type:
                                                      ApiAudioExtIndexType */
  API_IE_AUDIO_EXT_POINTER               = 0x3001, /*!< Associated type:
                                                      ApiAudioExtPointerType */
  API_IE_AUDIO_EXT_ARRAY                 = 0x3002, /*!< Associated type:
                                                      ApiAudioExtArrayType */
  API_IE_INVALID                         = 0xFFFF  /*!< Reserved. */
} RSENUM16(ApiIeType);

/*! This type is used to hold information elements received from the DECT
   protocol */
typedef struct
{
  ApiIeType Ie;                         /*!< Info Element Identification */
  rsuint8 IeLength;                     /*!< Info Element length in bytes */
  rsuint8 IeData[1];                    /*!< The Info Data (InfoLength number of bytes). */
} PACKED_STRUCT ApiInfoElementType;

/*! Specifies if codec can be negotiated. */
typedef enum RSENUMTAG(ApiNegotiationIndicatorType)
{
  API_NI_NOT_POSSIBLE = 0x00, /*!< Negotiation not possible */
  API_NI_POSSIBLE     = 0x01  /*!< Negotiation possible */
} RSENUM8(ApiNegotiationIndicatorType);

/*! See EN 300 175-5 section 7.7.54. */
typedef enum RSENUMTAG(ApiCodecType)
{
  API_CT_NONE             = 0x00, /*!< Codec not specified or not relevant. */
  API_CT_USER_SPECIFIC_32 = 0x01, /*!< user specific, information transfer rate 32
                                     kbit/s */
  API_CT_G726             = 0x02, /*!< G.726 ADPCM, information transfer rate 32 kbit/s */
  API_CT_G722             = 0x03, /*!< G.722, information transfer rate 64 kbit/s */
  API_CT_G711A            = 0x04, /*!< G.711 a-law PCM, information transfer rate 64
                                     kbit/s */
  API_CT_G711U            = 0x05, /*!< G.711 u-law PCM, information transfer rate 64
                                     kbit/s */
  API_CT_G7291            = 0x06, /*!< G.729.1, information transfer rate 32 kbit/s */
  API_CT_MP4_32           = 0x07, /*!< MPEG-4 ER AAC-LD, information transfer rate 32
                                     kbit/s */
  API_CT_MP4_64           = 0x08, /*!< MPEG-4 ER AAC-LD, information transfer rate 64
                                     kbit/s */
  API_CT_USER_SPECIFIC_64 = 0x09, /*!< user specific, information transfer rate 64
                                     kbit/s */
  API_CT_MAX                      /*!<  */
} RSENUM8(ApiCodecType);

/*! See EN 300 175-5 section 7.7.54. */
typedef enum RSENUMTAG(ApiMacDlcServiceType)
{
  API_MDS_1_MD   = 0x00, /*!< DLC service LU1, MAC service: In_minimum_delay */
  API_MDS_1_ND   = 0x01, /*!< DLC service LU1, MAC service In_normal_delay */
  API_MDS_1_IED  = 0x02, /*!< DLC service LU1, MAC service Ip_error_detect */
  API_MDS_1_IQED = 0x03, /*!< DLC service LU1, MAC service Ipq_error_detect */
  API_MDS_7_ND   = 0x04, /*!< DLC service LU7, MAC service In_normal_delay */
  API_MDS_1_NDF  = 0x05  /*!< DLC service LU1, MAC service In_normal_delay, framed as TS
                            102 527-1 [76], clause C.1 */
} RSENUM8(ApiMacDlcServiceType);

/*! See EN 300 175-5 section 7.7.54. */
typedef enum RSENUMTAG(ApiCplaneRoutingType)
{
  API_CPR_CS    = 0x00, /*!< CS only */
  API_CPR_CS_CF = 0x01, /*!< CS preferred/CF accepted */
  API_CPR_CF_CS = 0x02, /*!< CF preferred/CS accepted */
  API_CPR_CF    = 0x03  /*!< CF only */
} RSENUM8(ApiCplaneRoutingType);

/*! See EN 300 175-5 section 7.7.54. */
typedef enum RSENUMTAG(ApiSlotSizeType)
{
  API_SS_HS    = 0x00, /*!< Half slot; j = 0. */
  API_SS_LS640 = 0x01, /*!< Long slot; j = 640 */
  API_SS_LS672 = 0x02, /*!< Long slot; j = 672 */
  API_SS_FS    = 0x04, /*!< Full slot */
  API_SS_DS    = 0x05  /*!< Double slot */
} RSENUM8(ApiSlotSizeType);

/*! Parameters for a codec. */
typedef struct ApiCodecInfoType
{
  ApiCodecType Codec;                   /*!< Codec type. */
  ApiMacDlcServiceType MacDlcService;   /*!< MAC/DLC service type. */
  ApiCplaneRoutingType CplaneRouting;   /*!< C-plane routing type. */
  ApiSlotSizeType SlotSize;             /*!< Slot size needed. */
} PACKED_STRUCT ApiCodecInfoType;

/*! Codec listing. */
typedef struct ApiCodecListType
{
  ApiNegotiationIndicatorType NegotiationIndicator; /*!< Negotiation possible or not. */
  rsuint8 NoOfCodecs;                   /*!< Number of codecs. */
  ApiCodecInfoType Codec[1];            /*!< Codec data. */
} PACKED_STRUCT ApiCodecListType;

/*! See EN 300 175-5 section 7.7.27. */
typedef struct ApiMultikeyPadType
{
  ApiIa5CharType Multikeypad[1];        /*!< Multikeypads */
} PACKED_STRUCT ApiMultikeyPadType;

/*! See EN 300 175-5 section 7.7.26. */
typedef struct ApiMultiDisplayType
{
  ApiIa5CharType MultiDisplay[1];       /*!< Display string */
} PACKED_STRUCT ApiMultiDisplayType;

/*! See EN 300 175-5 section 7.7.7. */
typedef enum RSENUMTAG(ApiNumberTypeType)
{
  ANT_UNKNOWN          = 0x00, /*!< Unknown */
  ANT_INTERNATIONAL    = 0x01, /*!< International number */
  ANT_NATIONAL         = 0x02, /*!< National number */
  ANT_NETWORK_SPECIFIC = 0x03, /*!< Network specific number */
  ANT_SUBSCRIBER       = 0x04, /*!< Subscriber number */
  ANT_ABBREVIATED      = 0x06, /*!< Abbreviated number */
  ANT_INVALID          = 0xFF  /*!<  */
} RSENUM8(ApiNumberTypeType);

/*! This enum defines the numbering planes supported. NOTE: If ANPI_SIP is
   selected the SIP interface must check the called number. If the number
   already contains sip: the SIP interface shall pass the number unchanged.
   Otherwise the SIP interface must form the number as specified in RFC 3261.
   (E.g. sip:number@xxx.yyy). Also see EN 300 175-5 section 7.7.7. */
typedef enum RSENUMTAG(ApiNpiType)
{
  ANPI_UNKNOWN         = 0x00, /*!< Unknown */
  ANPI_E164_ISDN       = 0x01, /*!< ISDN/telephony plan ITU-T Recommendations
                                  E.164/E.163 */
  ANPI_X121            = 0x03, /*!< Data plan ITU-T Recommendation X.121 */
  ANPI_TCP_IP          = 0x07, /*!< TCP/IP address */
  ANPI_NATIONAL        = 0x08, /*!< National standard plan */
  ANPI_PRIVATE         = 0x09, /*!< Private plan */
  ANPI_SIP             = 0x0A, /*!< SIP addressing scheme, To: or From:  field (see RFC
                                  3261) */
  ANPI_INTERNET        = 0x0B, /*!< Internet character format address */
  ANPI_LAN_MAC         = 0x0C, /*!< LAN MAC address */
  ANPI_X400            = 0x0D, /*!< ITU-T Recommendation X.400 [63] address */
  ANPI_PROFILE_SERVICE = 0x0E, /*!< Profile service specific alphanumeric identifier */
  ANPI_INVALID         = 0xFF  /*!<  */
} RSENUM8(ApiNpiType);

/*! This enum defines the presentation indicator values that can be used on
   calling name and number received from the network. Also see EN 300 175-5
   section 7.7.9. */
typedef enum RSENUMTAG(ApiPresentationIndicatorType)
{
  API_PRESENTATION_ALLOWED        = 0x00, /*!< Presentation allowed. */
  API_PRESENTATION_RESTRICTED     = 0x01, /*!< Presentation restricted. */
  API_PRESENTATION_NUMBER_NA      = 0x02, /*!< Number not available. */
  API_PRESENTATION_HANSET_LOCATOR = 0X03, /*!< Used to locate physically handsets (have
                                             them ring) f. ex.by pressing a physical or
                                             logical button on the FP. */
  API_INVALID                     = 0xFF  /*!< [0x04; 0xFF] is reserved. */
} RSENUM8(ApiPresentationIndicatorType);

/*! This enum defines the presentation indicator values that can be used on
   calling name received from the network. Also see EN 300 175-5 section
   7.7.53. */
typedef enum RSENUMTAG(ApiScreeningIndicatorType)
{
  API_USER_PROVIDED_NOT_SCREENED    = 0x00, /*!< User-provided, not screened. */
  API_USER_PROVIDED_VERIFIED_PASSED = 0x01, /*!< User-provided, verified and passed. */
  API_USER_PROVIDED_VERIFIED_FAILED = 0x02, /*!< User-provided, verified and failed. */
  API_NETWORK_PROVIDED              = 0X03, /*!< Network provided. */
  API_SCR_INVALID                   = 0xFF  /*!< [0x04; 0xFF] is reserved. */
} RSENUM8(ApiScreeningIndicatorType);

/*! This enum defines the string coding formats that can be used to encode
   strings exchanged between the MCU and the handsets. */
typedef enum RSENUMTAG(ApiUsedAlphabetType)
{
  AUA_DECT             = 0x00, /*!< IA5 chars used. */
  AUA_UTF8             = 0x01, /*!< UTF-8 chars used. */
  AUA_NETWORK_SPECIFIC = 0xFF  /*!<  */
} RSENUM8(ApiUsedAlphabetType);

/*! This type is used to hold information about the number called / dialled
   on a handset. */
typedef struct
{
  ApiNumberTypeType NumberType;         /*!< Number type */
  ApiNpiType Npi;                       /*!< Numbering Plan Identification */
  rsuint8 NumberLength;                 /*!< Number length in bytes */
  rsuint8 Number[1];                    /*!< The number as IA5 string (NumberLength
                                           number of bytes). */
} PACKED_STRUCT ApiCalledNumberType;

/*! This type is used to hold information about the name of called /
   dialled number on a handset. The Screening indicator is always set to
   either User-provided or Network provided. */
typedef struct
{
  ApiUsedAlphabetType UsedAlphabet;     /*!< Specifies the encoding of the name. */
  ApiScreeningIndicatorType ScreeningInd; /*!< Screening indicator */
  rsuint8 NameLength;                   /*!< Name length in bytes */
  rsuint8 FirstNameLength;              /*!< FirstName length in bytes */
  rsuint8 Name[1];                      /*!< The name(s) (NameLength number of bytes +
                                           FirstNameLength number of bytes). */
} PACKED_STRUCT ApiCalledNameType;

/*! This is used to present the calling party number.
    This is also used in intercom call setup to identify the calling handset.
    For the coding of the Calling party number IE see [3] section F.1.3.2
   Internal Call CLIP procedure description.
    The Presentation indicator is always set to Presentation allowed and the
   Screening indicator is always set to User-provided, not screened. */
typedef struct 
{
  ApiNumberTypeType NumberType;         /*!< Number type */
  ApiNpiType Npi;                       /*!< Numbering Plan Identification */
  ApiPresentationIndicatorType PresentationInd; /*!< Presentation indicator. */
  ApiScreeningIndicatorType ScreeningInd; /*!< Screening indicator */
  rsuint8 NumberLength;                 /*!< Number length in bytes */
  rsuint8 Number[1];                    /*!< The number as IA5 string (NumberLength
                                           number of bytes). */
} PACKED_STRUCT ApiCallingNumberType;

/*! This type is used to hold information about the number called / dialled
   on a handset. The Presentation indicator is always set to Presentation
   allowed and the Screening indicator is always set to User-provided, not
   screened */
typedef struct
{
  ApiUsedAlphabetType UsedAlphabet;     /*!< Specifies the encoding of the name. */
  ApiPresentationIndicatorType PresentationInd; /*!< Presentation indicator. */
  ApiScreeningIndicatorType ScreeningInd; /*!< Screening indicator */
  rsuint8 NameLength;                   /*!< Name length in bytes */
  rsuint8 Name[1];                      /*!< The name (NameLength number of bytes). */
} PACKED_STRUCT ApiCallingNameType;

/*! See EN 300 175-5 section 7.7.23. */
typedef enum RSENUMTAG(ApiDiscriminatorType)
{
  API_DT_UNSPECIFIED = 0x0, /*!<  */
  API_DT_EMC         = 0x1, /*!<  */
} RSENUM8(ApiDiscriminatorType);

/*! See EN 300 175-5 section 7.7.23. */
typedef enum RSENUMTAG(ApiProtocolDiscriminatorType)
{
  API_PROT_DISC_USER_SPECIFIC              = 0x00, /*!<  */
  API_PROT_DISC_OSI_HIGH_LAYER_PROTOCOL    = 0x01, /*!<  */
  API_PROT_DISC_ITU_T_X244                 = 0x02, /*!<  */
  API_PROT_DISC_LIST_ACCESS                = 0X03, /*!<  */
  API_PROT_DISC_IA5_CHARACTERS             = 0x04, /*!<  */
  API_PROT_DISC_LIGHT_DATA_SERVICE         = 0x06, /*!<  */
  API_PROT_DISC_ITU_T_V120                 = 0x07, /*!<  */
  API_PROT_DISC_ITU_T_Q931_MESSAGE         = 0x08, /*!<  */
  API_PROT_DISC_ITU_T_Q931_ELEMENTS        = 0x09, /*!<  */
  API_PROT_DISC_ITU_T_Q931_PARTIAL_MESSAGE = 0x0A, /*!<  */
  API_PROT_DISC_GSM_RECOM_04_08_MESSAGE    = 0x10, /*!<  */
  API_PROT_DISC_GSM_RECOM_04_08_ELEMENTS   = 0x11, /*!<  */
  API_PROT_DISC_GSM_LMRS                   = 0x14, /*!<  */
  API_PROT_DISC_RLL_ACCESS_PROFILE         = 0x15, /*!<  */
  API_PROT_DISC_WRS                        = 0x16, /*!<  */
  API_PROT_DISC_DECT_ISDN_INTERM_C_PLAN    = 0x20, /*!<  */
  API_PROT_DISC_DECT_ISDN_INTERM_U_PLAN    = 0x21, /*!<  */
  API_PROT_DISC_DECT_ISDN_INTERM_SYSTEM    = 0x22, /*!<  */
  API_PROT_DISC_TERMINAL_DATA              = 0x23, /*!<  */
  API_PROT_DISC_UNKNOWN                    = 0x3F, /*!<  */
  API_PROT_DISC_INVALID                    = 0xFF  /*!<  */
} RSENUM8(ApiProtocolDiscriminatorType);

/*! This type is used to send IWU to IWU information element. Also see EN
   300 175-5 section 7.7.23. */
typedef struct ApiIwuToIwuType
{
  rsbool TransmitReject;                /*!< TRUE for transmission. 
                                           FALSE for reject. (not supported) */
  ApiProtocolDiscriminatorType IwuProtocolDiscriminator; /*!< Protocol Discriminator. */
  ApiDiscriminatorType Discriminator;   /*!< Discriminator. If set to API_DT_EMC EMC
                                           field below is used */
  rsuint16 EmcCode;                     /*!< EMC - Used when Discriminator is set to
                                           API_DT_EMC. */
  rsuint16 Length;                      /*!< Length of proprietary content in bytes. */
  rsuint8 Content[1];                   /*!< Proprietary content */
} PACKED_STRUCT ApiIwuToIwuType;

/*! This type is used to send escape to proprietary information element */
typedef struct ApiEscapeToProprietaryType
{
  ApiDiscriminatorType Discriminator;   /*!< Discriminator.
                                           If set to 0x1 EMC filed below is used */
  rsuint16 EmcCode;                     /*!< EMC
                                           Used when Discriminator is set to EMC. */
  rsuint16 Length;                      /*!< Length of propietary content in bytes. */
  rsuint8 Content[1];                   /*!< Propietary content */
} PACKED_STRUCT ApiEscapeToProprietaryType;

/*! This type is used to send facility information element */
typedef struct ApiFacilityType
{
  rsuint8 ServiceDiscriminator;         /*!< Discriminator. */
  rsuint16 Length;                      /*!< Length of component in bytes. */
  rsuint8 Component[1];                 /*!< Facility component data. */
} PACKED_STRUCT ApiFacilityType;

/*! This type is used to send escape to proprietary information element */
typedef struct ApiUnitdataType
{
  rsuint8 Content[1];                   /*!< Propietary Unitdata content */
} PACKED_STRUCT ApiUnitdataType;

/*! This enum defines sub identifiers for line id. For more information see
   ETSI EN 300 175-5 Ch.7.756 */
typedef enum RSENUMTAG(ApiLineIdentifierSubType)
{
  API_SUB_LINE_ID_EXT_LINE_ID         = 0x00, /*!<  */
  API_SUB_LINE_ID_INT_SOURCE_LINE_ID  = 0x01, /*!<  */
  API_SUB_LINE_ID_INT_TARGET_LINE_ID  = 0x02, /*!<  */
  API_SUB_LINE_ID_RELATING_TO_LINE_ID = 0x03, /*!<  */
  API_SUB_LINE_ID_ALL_LINES_ID        = 0x04, /*!<  */
  API_SUB_LINE_TYPE_INFO              = 0x05, /*!<  */
  API_SUB_LINE_ID_INVALID             = 0xFF  /*!< [0x06; 0xFF] is reserved. */
} RSENUM8(ApiLineIdentifierSubType);

/*! This type carries various information regarding the line. */
typedef rsuint8 ApiLineIdInfoType;

/*! This defines the values related to the sub id. */
typedef union ApiLineIdValueType
{
  ApiLineIdInfoType Info;               /*!< Info. */
  rsuint8 Value;                        /*!< Line number, range from 0 -127, 0x7F
                                           corresponding to no line is selected. */
} PACKED_STRUCT ApiLineIdValueType;

/*! This type contains line information. */
typedef struct ApiLineIdType
{
  ApiLineIdentifierSubType ApiSubId;    /*!< Line ID type. */
  ApiLineIdValueType ApiLineValue;      /*!< Value. */
} PACKED_STRUCT ApiLineIdType;

/*! This type is used for sending an API_IE_LINE_ID information element. */
typedef struct ApiLineIdListType
{
  ApiLineIdType ApiLineId[1];           /*!< Line IDs. */
} PACKED_STRUCT ApiLineIdListType;

/*! This enum defines sub identifiers for call id. For more information see
   ETSI EN 300 175-5 Ch.7.756 */
typedef enum RSENUMTAG(ApiCallIdentifierSubType)
{
  API_SUB_CALL_ID         = 0x00, /*!<  */
  API_SUB_CALL_ID_UPDATE  = 0x01, /*!<  */
  API_SUB_CALL_ID_INVALID = 0xFF  /*!< [0x02; 0xFF] is reserved. */
} RSENUM8(ApiCallIdentifierSubType);

/*! This type is used for sending system Call id. */
typedef struct ApiSystemCallIdType
{
  ApiCallIdentifierSubType ApiSubId;    /*!< Call ID type. */
  rsuint8 ApiSystemCallId;              /*!< Unique Call reference nr, range from 0
                                           -127. The value is automatically assigned by the
                                           Switch in the Fp when a new client is added. */
} PACKED_STRUCT ApiSystemCallIdType;

/*! This type is used for sending system Call id in an
   API_IE_SYSTEM_CALL_ID information element. */
typedef struct ApiSystemCallIdListType
{
  ApiSystemCallIdType ApiSystemCallId[1]; /*!< System call ID. */
} PACKED_STRUCT ApiSystemCallIdListType;

/*! This enum defines sub identifiers for call status. For more information
   see ETSI EN 300 175-5 Ch.7.7.56 */
typedef enum RSENUMTAG(ApiCallStatusSubType)
{
  API_SUB_CALL_STATUS         = 0x01, /*!<  */
  API_SUB_CALL_STATUS_REASON  = 0x02, /*!<  */
  API_SUB_CALL_STATUS_INVALID = 0xFF  /*!< [0x03; 0xFF] is reserved. */
} RSENUM8(ApiCallStatusSubType);

/*! Call state status. */
typedef enum RSENUMTAG(ApiCallStatusStateType)
{
  API_CSS_IDLE                    = 0x00, /*!< Idle. */
  API_CSS_CALL_SETUP              = 0x01, /*!< Setup. */
  API_CSS_CALL_SETUP_ACK          = 0x02, /*!< Setup ack. */
  API_CSS_CALL_PROC               = 0x03, /*!< Proceeding. */
  API_CSS_CALL_ALERTING           = 0x04, /*!< Alerting. */
  API_CSS_CALL_CONNECT            = 0x05, /*!< Connecting. */
  API_CSS_CALL_DISCONNECTING     = 0x06, /*!< Disconnecting. */
  API_CSS_CALL_HOLD               = 0x09, /*!< Hold. */
  API_CSS_CALL_INTERCEPTED        = 0x0A, /*!< Intercepted. */
  API_CSS_CALL_CONFERENCE         = 0x0B, /*!< Conference connected. */
  API_CSS_CALL_TRANSFER           = 0x0C, /*!< Call under transfer */
  API_CSS_CALL_REMOTE_HOLD        = 0x0D, /*!< Call status of the call on remote party
                                             side */
  API_CSS_CALL_REMOTE_CONNECT    = 0x0E, /*!< Call status of the call on remote party
                                             side */
  API_CSS_CALL_SCREENING_SETUP   = 0x21, /*!< Call screening setup indication */
  API_CSS_CALL_SCREENING_CONNECT = 0x22, /*!< Call screening connect indication */
} RSENUM8(ApiCallStatusStateType);

/*! Call status reason for failure. */
typedef enum RSENUMTAG(ApiCallStatusReasonType)
{
  API_CSR_SYSTEM_BUSY                = 0x00, /*!< System busy. */
  API_CSR_LINE_IN_USE                = 0x01, /*!< Line busy. */
  API_CSR_CONTROL_CODE_NOT_SUPPORTED = 0x02, /*!< Unsupported control code. */
  API_CSR_CONTROL_CODE_FAILED        = 0x03, /*!< Use of control code failed. */
  API_CSR_USER_BUSY                  = 0x10, /*!< User is busy, */
  API_CSR_NUMBER_NOT_AVAILABLE       = 0x11  /*!< Number specified is not available. */
} RSENUM8(ApiCallStatusReasonType);

/*! Union value of call status. */
typedef union ApiCallStatusValueType
{
  ApiCallStatusStateType State;         /*!< State. */
  ApiCallStatusReasonType Reason;       /*!< Reason. */
  rsuint8 Value;                        /*!< General value. */
} PACKED_STRUCT ApiCallStatusValueType;

/*! This type is used for sending call status. */
typedef struct ApiCallStatusType
{
  ApiCallStatusSubType CallStatusSubId; /*!< Identifier for value. */
  ApiCallStatusValueType CallStatusValue; /*!< Value. */
} PACKED_STRUCT ApiCallStatusType;

/*! This type is used for sending call status in an API_IE_CALL_STATUS
   information element. */
typedef struct ApiCallStatusListType
{
  ApiCallStatusType ApiCallStatus[1];   /*!< Call status. */
} PACKED_STRUCT ApiCallStatusListType;

/*! Set of APIs available. */
typedef struct
{
  rsbitfield FpAudio : 1;               /*!< FpAudio API available. */
  rsbitfield FpCc : 1;                  /*!< FpCc API available. */
  rsbitfield FpFwu : 1;                 /*!< FpFwu API available. */
  rsbitfield FpGeneral : 1;             /*!< FpGeneral API available. */
  rsbitfield FpMm : 1;                  /*!< FpMm API available. */
  rsbitfield PpAudio : 1;               /*!< PpAudio API available. */
  rsbitfield PpBattery : 1;             /*!< PpBattery API available. */
  rsbitfield PpGeneral : 1;             /*!< PpGeneral API available. */
  rsbitfield PpLas : 1;                 /*!< PpLas API available. */
  rsbitfield PpMm : 1;                  /*!< PpMm API available. */
  rsbitfield FpLas : 1;                 /*!< FpLas API available. */
  rsbitfield Image : 1;                 /*!< Image control API available. */
  rsbitfield Hal : 1;                   /*!< HAL API available. */
  rsbitfield Lds : 1;                   /*!< LDS  API available. */
  rsbitfield Suota : 1;                 /*!< SUOTA API available. */
  rsbitfield Scl : 1;                   /*!< SCL API available. */
  rsbitfield NvsMap : 1;                /*!< NVSMAP API available. */
  rsbitfield FpHMm : 1;                 /*!< Helios FpMm API available. */
  rsbitfield ExtendedTerminalIdSupport:1; /*!< APIs supports 16 bit terminal ids. */
  rsbitfield _spare2_ : 5;              /*!< Reserved. */
  rsbitfield _spare3_ : 8;              /*!< Reserved. */
} PACKED_STRUCT ApiAvailableApiBitsType;

/*! Set of APIs available. */
typedef union
{
  rsuint32 Value;                       /*!< Value. */
  ApiAvailableApiBitsType Apis;         /*!< Bit field. */
} PACKED_STRUCT ApiAvailableApisType;

/*! This enum defines the CODEC's (PCM data format) supported by the FP on
   the PCM interface. */
typedef enum RSENUMTAG(ApiAudioDataFormatType)
{
  AP_DATA_FORMAT_NONE                       = 0x00, /*!< No CODEC selected. */
  AP_DATA_FORMAT_LINEAR_8kHz                = 0x01, /*!< Linear PCM, 8kHz sample rate.
                                                       Used for narrowband calls (G.726). */
  AP_DATA_FORMAT_LINEAR_16kHz               = 0x02, /*!< Linear PCM, 16kHz sample rate.
                                                       Used for wideband calls (G.722). */
  AP_DATA_FORMAT_G726                       = 0x03, /*!< G.726 - ADPCM, 8 KHz sample
                                                       rate. */
  AP_DATA_FORMAT_G722                       = 0x04, /*!< G.722 - Sub-band ADPCM, 16 KHz
                                                       sample rate. */
  AP_DATA_FORMAT_G711A                      = 0x05, /*!< G.711 - A-law, 8 KHz sample
                                                       rate. Used for narrowband calls
                                                       (G.726). */
  AP_DATA_FORMAT_G711U                      = 0x06, /*!< G.711 - u-law, 8 KHz sample
                                                       rate. Used for narrowband calls
                                                       (G.726). */
  AP_DATA_FORMAT_CWB_ALAW                   = 0x07, /*!< Compressed wideband using
                                                       A-law, 16 KHz sample rate. The 16 bit
                                                       PCM data is encoded as two 8 bit
                                                       audio samples if 8 KHz frame sync is
                                                       used. Used for wideband calls
                                                       (G.722). */
  AP_DATA_FORMAT_CWB_ULAW                   = 0x08, /*!< Compressed wideband using
                                                       u-law, 16 KHz sample rate. The 16 bit
                                                       PCM data is encoded as two 8 bit
                                                       audio samples if 8 KHz frame sync is
                                                       used. Used for wideband calls
                                                       (G.722). */
  AP_DATA_FORMAT_CWB_ALAW_REVERSE_BYTEORDER = 0x09, /*!< Same as CWB_ALAW, but with
                                                       reverse byte order on PCM bus. MSB is
                                                       most recent sample. */
  AP_DATA_FORMAT_CWB_ULAW_REVERSE_BYTEORDER = 0x0A, /*!< Same as CWB_ULAW, but with
                                                       reverse byte order on PCM bus. LSB is
                                                       most recent sample. */
  AP_DATA_FORMAT_G7222_660_kbps             = 0x20, /*!< G.722.2, 6.60 kbps. */
  AP_DATA_FORMAT_G7222_885_kbps             = 0x21, /*!< G.722.2, 8.85 kbps. */
  AP_DATA_FORMAT_G7222_1265_kbps            = 0x22, /*!< G.722.2, 12.65 kbps. */
  AP_DATA_FORMAT_G7222_1585_kbps            = 0x23, /*!< G.722.2, 15.85 kbps. */
  AP_DATA_FORMAT_G7222_2385_kbps            = 0x24, /*!< G.722.2, 23.85 kbps. */
  AP_DATA_FORMAT_LINEAR_32kHz               = 0x25, /*!< Linear PCM samplerate 32kHz */
  AP_DATA_FORMAT_LINEAR_48kHz               = 0x26, /*!< Linear PCM samplerate 48kHz */
  AP_DATA_FORMAT_INVALID                    = 0xFF  /*!< [0x0B; 0xFF] is reserved. */
} RSENUM8(ApiAudioDataFormatType);

/*! This struct defines the relation between the encoding used on the air
   interface between the FP and the PP and the audio format delivered to the
   host. */
typedef struct ApiAudioDataFormatInfoType
{
  ApiCodecType Codec;                   /*!< Codec type. */
  ApiAudioDataFormatType ApiAudioDataFormat; /*!< Audio data format */
} PACKED_STRUCT ApiAudioDataFormatInfoType;

/*! The relationship between codec and audio format to the host must be
   given for all offered codecs when a call is established.
    This information has to be given from the host to the FP target once
   before the audio is connected. The FP target needs to know which audio data
   format it shall deliver to the external audio interface (f.ex PCM bus) at
   the time the audio is connected.
    It can be delivered in one of the following messages:
    API_FP_CC_SETUP_REQ, API_FP_CC_SETUP_ACK_REQ, API_FP_CC_ALERT_REQ,
   API_FP_CC_CALL_PROC_REQ, API_FP_CC_CONNECT_REQ, API_FP_CC_CONNECT_RES. */
typedef struct ApiAudioDataFormatListType
{
  rsuint8 NoOfCodecs;                   /*!< Number of offered codecs */
  ApiAudioDataFormatInfoType ApiAudioDataFormatInfo[1]; /*!< Information for each
                                                            codec. */
} PACKED_STRUCT ApiAudioDataFormatListType;

/*! Standard GUID. */
typedef struct ApiGuidType
{
  rsuint32 Data1;                       /*!< Part 1. */
  rsuint16 Data2;                       /*!< Part 2. */
  rsuint16 Data3;                       /*!< Part 3. */
  rsuint8 Data4[8];                     /*!< Part 4. */
} PACKED_STRUCT ApiGuidType;

/*! Basic PP terminal capabilites. See ETSI EN 300 175-5 section 7.7.41. */
typedef struct ApiBasicTermCapsType
{
  rsuint8 Flags0;                       /*!< Bit0: Wideband Voice.
                                           Bit1: Extended Wideband Voice.
                                           Bit2: Headset Management.
                                           Bit3: Early Encryption.
                                           Bit4: Associated Melody.
                                           Bit5: Unused.
                                           Bit6: Unused.
                                           Bit7: Unused. */
  rsuint8 Flags1;                       /*!< Bit0: DPRS Class 3.
                                           Bit1: DPRS Class 4.
                                           Bit2: Light Data Services.
                                           Bit3: Unused.
                                           Bit4: Unused.
                                           Bit5: Unused.
                                           Bit6: Unused.
                                           Bit7: Unused. */
  rsuint8 EchoParameters;               /*!< 0x0: N/A.
                                           0x1: Minimum TCLw.
                                           0x2: TCLw > 46 dB.
                                           0x3: TCLw > 55 dB. */
} PACKED_STRUCT ApiBasicTermCapsType;

/*! PP terminal capabilites. See ETSI EN 300 175-5 section 7.7.41. */
typedef struct ApiTermCapsType
{
  rsuint8 Byte3;                        /*!< Bit 0-3: Display capabilities
                                           Bit 4-6: Tone Capabilities */
  rsuint8 Byte3b;                       /*!< Bit 0-1: A-VOL
                                           Bit 2-3: N-REJ
                                           Bit 4-6: Echo parameters */
  rsuint8 Byte3c;                       /*!< Slot type capability */
  rsuint8 Byte3d;                       /*!< Number of stored display characters (MS) */
  rsuint8 Byte3e;                       /*!< Number of stored display characters (LS) */
  rsuint8 Byte3f;                       /*!< Number of lines in (physical) display */
  rsuint8 Byte3g;                       /*!< Number of characters/line */
  rsuint8 Byte3h;                       /*!< Scrolling behaviour field */
  rsuint8 Byte4;                        /*!< Profile indicator_1 
                                           Bit 0: CAP supported
                                           Bit 1: GAP supported
                                           Bit 2: DECT/GSM interworking profile supported
                                           Bit 3: ISDN End-system supported
                                           Bit 4: LRMS supported
                                           Bit 5: DPRS Stream supported
                                           Bit 6: DPRS asymmetric bearers supported */
  rsuint8 Byte4a;                       /*!< Profile indicator_2
                                           Bit 0: DPRS Class 2 management and B-field
                                           procedures supported
                                           Bit 1: Data Services Profile D, Class 2 supported
                                           Bit 2: ISDN Intermediate Access Profile supported
                                           Bit 3: DECT/UMTS-GSM interworking - UMTS-GSM
                                           Bearer service supported
                                           Bit 4: DECT/UMTS-GSM interworking - UMTS-GSM SMS
                                           service supported
                                           Bit 5: DECT/UMTS-GSM interworking - UMTS-GSM
                                           Facsimile service supported
                                           Bit 6: RAP 1 Profile supported */
  rsuint8 Byte4b;                       /*!< Profile indicator_3
                                           Bit 0: DECT/GSM dual mode terminal
                                           Bit 1: WRS supported
                                           Bit 2: SMS over LRMS supported
                                           Bit 3: DMAP supported
                                           Bit 4: Multiport CTA
                                           Bit 5: Ethernet supported
                                           Bit 6: Token Ring supported */
  rsuint8 Byte4c;                       /*!< Profile indicator_4
                                           Bit 0: IP supported
                                           Bit 1: PPP supported
                                           Bit 2: V.24 supported
                                           Bit 3: CF supported
                                           Bit 4: IPQ services supported
                                           Bit 5: RAP 2 Profile supported
                                           Bit 6: Generic Media Encapsulation transport
                                           (DPRS) supported */
  rsuint8 Byte4d;                       /*!< Profile indicator_5
                                           Bit 0: 2-level modulation scheme supported (B+Z field)
                                           Bit 1: 4-level modulation scheme supported (B+Z field)
                                           Bit 2: 8-level modulation scheme supported (B+Z field)
                                           Bit 3: 16-level modulation scheme supported (B+Z field)
                                           Bit 4: 2-level modulation scheme supported (A field)
                                           Bit 5: 4-level modulation scheme supported (A field)
                                           Bit 6: 8-level modulation scheme supported (A
                                           field) */
  rsuint8 Byte4e;                       /*!< Profile indicator_6
                                           Bit 0: DECT/UMTS interworking profile supported
                                           Bit 1: DECT/UMTS interworking - GPRS services supported
                                           Bit 2: Basic ODAP supported
                                           Bit 3: F-MMS Interworking profile supported
                                           Bit 4: Channel GF supported
                                           Bit 5: PT with fast hopping radio
                                           Bit 6: Capability to support "no emission" mode */
  rsuint8 Byte4f;                       /*!< Profile indicator_7
                                           Bit 0: 64-level modulation scheme supported (B+Z
                                           field)  
                                           Bit 1: NG-DECT Part 1: Wideband voice supported
                                           Bit 2: Support of NG-DECT Part 3
                                           Bit 3: Support of the "Headset management" feature
                                           Bit 4: Support of "Re-keying" and "default
                                           cipher key early encryption mechanism"
                                           Bit 5: Support of 'associated melody' per contact
                                           Bit 6: Support of NG-DECT Part 5	 */
  rsuint8 Byte4g;                       /*!< Profile indicator_8
                                           Bit 0: E+U-type mux and channel IPF basic
                                           procedures supported
                                           Bit 1: Channel IPF advanced procedures supported
                                           Bit 2: Channel SIPF supported
                                           Bit 3-6: DPRS/NG-DECT Packet Data Category: */
  rsuint8 Byte4h;                       /*!< Profile indicator_9
                                           Bit 0: DPRS Class 3 management and A-field
                                           procedures (DPRS-M.30) supported
                                           Bit 1: DPRS Class 4 management and A-field
                                           procedures (DPRS-M.30) supported
                                           Bit 2: Reserved for DECT ULE
                                           Bit 3: Reserved for DECT ULE
                                           Bit 4: Reserved for DECT ULE
                                           Bit 5: Support of Light data services
                                           Bit 6: Reserved */
  rsuint8 Byte4i;                       /*!< Profile indicator_10
                                           Bit 0: Support of "Date and Time recovery"
                                           procedure in NG-DECT Part 5
                                           Bit 1: Support of "Extended list change
                                           indication" procedure
                                           Bit 2-6: Reserved */
  rsuint8 Byte5;                        /*!< Bit 0-2: Control codes
                                           Bit 3: 0
                                           Bit 4: 0
                                           Bit 5: DSC2
                                           Bit 6: DSAA2 */
  rsuint8 Byte5a;                       /*!< escape to 8 bit character sets_1 */
  rsuint8 Byte6;                        /*!< Bit 0: sp4
                                           Bit 1: sp3
                                           Bit 2: sp2
                                           Bit 3: sp1
                                           Bit 4: sp0
                                           Bit 5-6: Blind slot indication */
  rsuint8 Byte6a;                       /*!< Bit 0: sp11
                                           Bit 1: sp10
                                           Bit 2: sp9
                                           Bit 3: sp8
                                           Bit 4: sp7
                                           Bit 5: sp6
                                           Bit 6: sp5 */
} PACKED_STRUCT ApiTermCapsType;

/*! Fixed Part Capabilities */
typedef struct ApiFpCapabilitiesType
{
  rsuint8 FpCapBit12_15;                /*!< FP capabilities a12-a15
                                           Bit 7: reserved
                                           Bit 6: reserved
                                           Bit 5: reserved
                                           Bit 4: reserved
                                           Bit 3: a12 Extended fixed part info 
                                           Bit 2: a13 Double duplex bearer connections
                                           Bit 1: a14 Reserved
                                           Bit 0: a15 Double slot */
  rsuint8 FpCapBit16_23;                /*!< FP capabilities a16-a23
                                           Bit 7: a16 Half slot
                                           Bit 6: a17 Full slot
                                           Bit 5: a18 Frequency control
                                           Bit 4: a19 Page repetition 
                                           Bit 3: a20 C/O setup on dummy allowed 
                                           Bit 2: a21 C/L uplink
                                           Bit 1: a22 C/L downlink
                                           Bit 0: a23 Basic A-field set up */
  rsuint8 FpCapBit24_31;                /*!< FP capabilities a24-a31
                                           Bit 7: a24 Advanced A-field set up
                                           Bit 6: a25 B-field set up
                                           Bit 5: a26 CF messages
                                           Bit 4: a27 IN_minimum delay 
                                           Bit 3: a28 IN_normal_delay 
                                           Bit 2: a29 IP_error_detection
                                           Bit 1: a30 IP_error_correction
                                           Bit 0: a31 Multibearer connections */
  rsuint8 FpCapBit32_39;                /*!< FP capabilities a32-a49
                                           Bit 7: a32 ADPCM/G.721 Voice service
                                           Bit 6: a33 GAP/PAP basic speech
                                           Bit 5: a34 Non-voice circuit switched service
                                           Bit 4: a35 Non-voice packet switched service 
                                           Bit 3: a36 Standard authentication required 
                                           Bit 2: a37 Standard ciphering supported
                                           Bit 1: a38 Location registration supported
                                           Bit 0: a39 SIM services available */
  rsuint8 FpCapBit40_47;                /*!< FP capabilities a40-a47
                                           Bit 7: a40 Non-static Fixed Part (FP)
                                           Bit 6: a41 CISS service available
                                           Bit 5 a42 CLMS service available
                                           Bit 4: a43 COMS service available 
                                           Bit 3: a44 Access rights requests supported
                                           Bit 2: a45 External handover supported
                                           Bit 1: a46 Connection handover supported
                                           Bit 0: a47 Reserved */
} PACKED_STRUCT ApiFpCapabilitiesType;

/*! Extended fixed Part Capabilities */
typedef struct ApiFpExtendedCapabilitiesType
{
  rsuint8 FpExtCapBit12_15;             /*!< FP Extended capabilities a12-a15
                                           Bit 7: reserved
                                           Bit 6: reserved
                                           Bit 5: reserved
                                           Bit 4: reserved
                                           Bit 3: a12 CRFP Hops
                                           Bit 2: a13 CRFP is allowed
                                           Bit 1: a14 CRFP encryption: CRFP encryption supported
                                           Bit 0: a15 REP Hosp: REP not supported */
  rsuint8 FpExtCapBit16_23;             /*!< FP Extended capabilities a16-a23
                                           Bit 7: a16 REP Hosp: REP not supported
                                           Bit 6: a17 REP capabilities: REP not supported
                                           Bit 5: a18 Synchronization fiels options:
                                           Prolonged preamble
                                           Bit 4: a19 Synchronization fiels options:
                                           Prolonged preamble 
                                           Bit 3: a20 Reserved 
                                           Bit 2: a21 MAC suspend and resume
                                           Bit 1: a22 Ipq services supported
                                           Bit 0: a23 Extended FP info part 2 */
  rsuint8 FpExtCapBit24_31;             /*!< FP Extended capabilities a24-a31
                                           Bit 7: a24 Reserved
                                           Bit 6: a25 F-MMS Interworking profile supported
                                           Bit 5: a26 Basic ODAP supported
                                           Bit 4: a27 Generic Media Encapsulation transport (DPRS)
                                           Bit 3: a28 IP Roaming unrestricted supported
                                           Bit 2: a29 Ethernet
                                           Bit 1: a30 Token Ring
                                           Bit 0: a31 IP */
  rsuint8 FpExtCapBit32_39;             /*!< FP Extended capabilities a32-a49
                                           Bit 7: a32 PPP
                                           Bit 6: a33 V.24
                                           Bit 5: a34 Reserved
                                           Bit 4: a35 Reserved
                                           Bit 3: a36 RAP Part 1 Profile
                                           Bit 2: a37 ISDN Intermediate system
                                           Bit 1: a38 Sync to GPRS achived
                                           Bit 0: a39 Location registration with TPUI
                                           allowed */
  rsuint8 FpExtCapBit40_47;             /*!< FP Extended capabilities a40-a47
                                           Bit 7: a40 Emergency call supported
                                           Bit 6: a41 Assymetric bearers supported
                                           Bit 5: a42 Reserved
                                           Bit 4: a43 LRMS
                                           Bit 3: a44 Data service Profile D
                                           Bit 2: a45 DPRS Stream
                                           Bit 1: a46 DPRS FREL
                                           Bit 0: a47 ISDN Data Services */
} PACKED_STRUCT ApiFpExtendedCapabilitiesType;

/*! Extended Fixed Part Capabilities 2. */
typedef struct ApiFpExtendedCapabilities2Type
{
  rsuint8 FpExtCap2Bit12_15;            /*!< FP Extended capabilities a12-a15
                                           Bit 7: reserved
                                           Bit 6: reserved
                                           Bit 5: reserved
                                           Bit 4: reserved
                                           Bit 3: a12 Long slot support (j = 640)
                                           Bit 2: a13 Long slot support (j = 672)
                                           Bit 1: a14 Reserved for future standardization
                                           Bit 0: a15 Reserved for future standardization */
  rsuint8 FpExtCap2Bit16_23;            /*!< FP Extended capabilities a16-a23
                                           Bit 7: a16 Reserved for future standardization
                                           Bit 6: a17 Reserved for future standardization
                                           Bit 5: a18 Reserved for future standardization
                                           Bit 4: a19 Reserved for future standardization 
                                           Bit 3: a20 Reserved for future standardization
                                           Bit 2: a21 Reserved for future standardization
                                           Bit 1: a22 Reserved for future standardization
                                           Bit 0: a23 Reserved for future standardization */
  rsuint8 FpExtCap2Bit24_31;            /*!< FP Extended capabilities a24-a31
                                           Bit 7: a24 NG-DECT Wideband voice
                                           Bit 6: a25 NG-DECT Packet Data Category
                                           Bit 5: a26 NG-DECT Packet Data Category
                                           Bit 4: a27 NG-DECT Packet Data Category 
                                           Bit 3: a28 NG-DECT Packet Data Category
                                           Bit 2: a29 NG-DECT Extended wideband voice supported
                                           Bit 1: a30 NG-DECT Extended voice: Permanent CLIR
                                           Bit 0: a31 NG-DECT Extended voice: Third party
                                           conference call (external or internal) */
  rsuint8 FpExtCap2Bit32_39;            /*!< FP Extended capabilities a32-a49
                                           Bit 7: a32 NG-DECT Extended voice: Intrusion call
                                           Bit 6: a33 NG-DECT Extended voice: Call deflection
                                           Bit 5: a34 NG-DECT Extended voice:Multiple lines
                                           Bit 4: a35 No emission mode supported 
                                           Bit 3: a36 Additional feature set nr.1 for
                                           extended wideband voice supported
                                           Bit 2: a37 Reserved
                                           Bit 1: a38 Reserved 
                                           Bit 0: a39 Reserved for DECT ULE */
  rsuint8 FpExtCap2Bit40_47;            /*!< FP Extended capabilities a40-a47
                                           Bit 7: a40 Reserved for DECT ULE
                                           Bit 6: a41 Reserved for DECT ULE
                                           Bit 5: a42 Support of Re.keying and early encryption
                                           Bit 4: a43 DSAA2 supported 
                                           Bit 3: a44 DSC2 supported
                                           Bit 2: a45 light data services supported
                                           Bit 1: a46 Reserved
                                           Bit 0: a47 Reserved */
} PACKED_STRUCT ApiFpExtendedCapabilities2Type;

/*! This type is used to select tone melody index for the
   API_PP_AUDIO_START_TONE_EXT_REQ and API_PP_AUDIO_START_MIDI_EXT_REQ */
typedef struct ApiAudioExtIndexType
{
  rsuint8 ExtIndex;                     /*!< Index of tones and melodies
                                           The index refferes to the project specific
                                           melody/midi table in the stack, holding
                                           predefined melodies */
} PACKED_STRUCT ApiAudioExtIndexType;

/*! This type is used to select tone melody location for the
   API_PP_AUDIO_START_TONE_EXT_REQ and API_PP_AUDIO_START_MIDI_EXT_REQ */
typedef struct ApiAudioExtPointerType
{
  rsuint8 *ExtPointer;                  /*!< Pointer to address of tones and melodies.
                                           The custom tones and melodies are intended to be
                                           programmed in flash (fx. in the COLA area) */
} PACKED_STRUCT ApiAudioExtPointerType;

/*! This type is used to send an array of tone data for the
   API_PP_AUDIO_START_TONE_EXT_REQ and API_PP_AUDIO_START_MIDI_EXT_REQ */
typedef struct ApiAudioExtArrayType
{
  rsuint8 ExtPolyTones;                 /*!< Number of of simultaneous tones */
  rsuint8 ExtLoop;                      /*!< Number of repeats */
  rsuint16 ExtBpm;                      /*!< Beats per minute */
  rsuint8 ExtArray[1];                  /*!< Array of tone and melody data.
                                           See programming guide for examples on how to
                                           program. */
} PACKED_STRUCT ApiAudioExtArrayType;

/*! This type defines the signal types received when receiving alert
   broadcast */
typedef enum RSENUMTAG(ApiMmSignalType)
{
  API_MM_ALERT_ON_PATTERN_0                = 0x00, /*!<  */
  API_MM_ALERT_ON_PATTERN_1                = 0x01, /*!<  */
  API_MM_ALERT_ON_PATTERN_2                = 0x02, /*!<  */
  API_MM_ALERT_ON_PATTERN_3                = 0x03, /*!<  */
  API_MM_ALERT_ON_PATTERN_4                = 0x04, /*!<  */
  API_MM_ALERT_ON_PATTERN_5                = 0x05, /*!<  */
  API_MM_ALERT_ON_PATTERN_6                = 0x06, /*!<  */
  API_MM_ALERT_ON_PATTERN_7                = 0x07, /*!<  */
  API_MM_ALERT_ON_CONTINOUS                = 0x08, /*!<  */
  API_MM_INCOMMING_CALL_RELEASED_BY_THE_FP = 0x0A, /*!<  */
  API_MM_INCOMMING_CALL_HAS_BEEN_ANSWERED  = 0x0B, /*!<  */
  API_MM_ALERT_OFF                         = 0x0F  /*!<  */
} RSENUM8(ApiMmSignalType);

/*! This type defines the signal types received when receiving alert
   broadcast */
typedef enum RSENUMTAG(ApiMmSearchModeType)
{
  API_MM_CONTINOUS_SEARCH = 0x00, /*!<  */
  API_MM_SINGLE_SEARCH    = 0x01  /*!<  */
} RSENUM8(ApiMmSearchModeType);

/*! This type defines the handset location status. */
typedef enum RSENUMTAG(ApiMmLocationStatusType)
{
  API_MM_LS_UNKNOWN  = 0x00, /*!< Unknown location status. Handset may or may not be
                                able to make calls. */
  API_MM_LS_DETACHED = 0x01, /*!< Handset has powered off. */
  API_MM_LS_LOCATED  = 0x02  /*!< Handset has performed location update and is probably
                                able to make calls. */
} RSENUM8(ApiMmLocationStatusType);


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
*                             Function prototypes
****************************************************************************/

/****************************************************************************
*  FUNCTION:       ApiBuildInfoElement
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to allocate and append an info
                   element to a memory block holding previously allocated info
                   elements. This function reallocates the info element block
                   wit a new size that is the size of the existing block + the
                   size of the new info element. The IeData is copied to the
                   tail of the new block allocated.
****************************************************************************/
void ApiBuildInfoElement(ApiInfoElementType **IeBlockPtr,    /*!< Pointer to pointer
                                                                holding the address of the
                                                                memory block that the info
                                                                element allocated should be
                                                                appended to when this
                                                                function is called and
                                                                pointer to new block when
                                                                the function returns.
                                                                *IeBlockPtr is set to NULL
                                                                if this function fails to
                                                                allocate memory for the new
                                                                information element. */
                         rsuint16 *IeBlockLengthPtr,         /*!< Pointer to variable
                                                                holding the current size of
                                                                the memory block used to
                                                                store the info elements in
                                                                when the function is called
                                                                and the new size when the
                                                                function returns. */
                         ApiIeType Ie,                       /*!< Info Element
                                                                identification. */
                         rsuint8 IeLength,                   /*!< The length in bytes of
                                                                the info element that should
                                                                be appended to the info
                                                                element memory block
                                                                (**IeBlockPtr). */
                         rsuint8 *IeData);                   /*!< Pointer to the info
                                                                element data that should be
                                                                appended. */

/****************************************************************************
*  FUNCTION:       ApiFreeInfoElement
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to free an info element memory
                   block allocate by ApiBuildInfoElement().
****************************************************************************/
void ApiFreeInfoElement(ApiInfoElementType **IeBlockPtr);    /*!< Pointer to pointer
                                                                holding the address of the
                                                                memory block that should be
                                                                freed. */

/****************************************************************************
*  FUNCTION:       ApiGetInfoElement
*
*  RETURNS :       Pointer to the info element found in the info element
                   block or NULL if the info element searched for is not found
                   in the info element block.
*
*  DESCRIPTION:    This function is used to find a specific info element in
                   a memory block holding one or more info elements.
****************************************************************************/
ApiInfoElementType* ApiGetInfoElement(ApiInfoElementType *IeBlockPtr,
                                                             /*!< Pointer to the info
                                                                element block that holds one
                                                                or more info elements */
                                      rsuint16 IeBlockLength,
                                                             /*!< The size of the info
                                                                element block. */
                                      ApiIeType Ie);         /*!< Id of the info element
                                                                searched after. */

/****************************************************************************
*  FUNCTION:       ApiGetNextInfoElement
*
*  RETURNS :       Pointer to the next info element following IePtr or NULL
                   if the end of the info element block is reached.
*
*  DESCRIPTION:    This function is used to get the next info element after
                   IePtr in an info element block. 
****************************************************************************/
ApiInfoElementType* ApiGetNextInfoElement(ApiInfoElementType *IeBlockPtr,
                                                             /*!< Pointer to the info
                                                                element block that holds one
                                                                or more info elements */
                                          rsuint16 IeBlockLength,
                                                             /*!< The size of the info
                                                                element block. */
                                          ApiInfoElementType *IePtr);
                                                             /*!< The pointer to the
                                                                info element for which the
                                                                next info element is
                                                                requested. The first info
                                                                element is returned if IePtr
                                                                is NULL. */

/****************************************************************************
*  FUNCTION:       ApiRemoveInfoElement
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to Remove an info element from an
                   info element block. 
****************************************************************************/
void ApiRemoveInfoElement(ApiInfoElementType **IeBlockPtr,   /*!< Pointer to pointer to
                                                                the info element block that
                                                                holds the info elements
                                                                which is to be removed */
                          rsuint16 *IeBlockLength,           /*!< Pointer to the size of
                                                                the info element block. */
                          ApiIeType Ie);                     /*!< Id of the info element
                                                                which is to be removed. */

/****************************************************************************
*  FUNCTION:       ApiGuid2Str
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to convert a GUID to its string
                   representation.
****************************************************************************/
rschar* ApiGuid2Str(rschar* Str,
                    const ApiGuidType* Guid);

/****************************************************************************
*  FUNCTION:       ApiStr2Guid
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to convert a GUID formatted string
                   to its binary representation.
****************************************************************************/
void ApiStr2Guid(ApiGuidType* Guid,
                 const rschar* Str);

/****************************************************************************
*  FUNCTION:       ApiCfgGetExtendedTerminalIdSupport
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to read if Extended Terminal Id
                   support is enabled or not.
                   FALSE = version 10 - TRUE = version 11
****************************************************************************/
rsbool ApiCfgGetExtendedTerminalIdSupport(void);

/****************************************************************************
*  FUNCTION:       ApiCfgSetExtendedTerminalIdSupport
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to enable or disable Extended
                   Terminal Id support.
****************************************************************************/
void ApiCfgSetExtendedTerminalIdSupport(rsbool Value);       /*!< FALSE = version 10 -
                                                                TRUE = version 11 */


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APITYPES_H */


