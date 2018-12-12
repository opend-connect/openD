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

#ifndef ISIP450API_H
#define ISIP450API_H

/****************************************************************************
*                               Include files
****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/* Alle API structs are packed */
#define PACKED_STRUCT __attribute__((packed))

/* The size of the NVS data, that must be stored by the application */
#define API_FP_NVS_SIZE 0x400

/* The maximum mail size that the application can ever receive or send. The
   size of the buffer used for all reads on /dev/dect must be at least this.
   (This value is not valid for /dev/dectdbg) */
#define API_FP_MAX_MAIL_SIZE 0x1010

/* Number of ADPCM channels */
#define API_FP_ADPCM_CHANNELS 4

/*Definitions for setting the EMC, FPN fields of the rfpi*/
#define SET_CC_RFPI_EMC(PTR, X) {PTR[0]&=~0x0f; PTR[0]|=(X>>12);PTR[1]&=~0xff; PTR[1]|=(X>>4);PTR[2]&=~0xf0; PTR[2]|=(X&0x0f)<<4;}//16 bits . DO NOT SET EMC TO 0 !!
#define SET_CC_RFPI_FPN(PTR, X) {PTR[2]&=~0x0f; PTR[2]|=(X>>13);PTR[3]&=~0xff; PTR[3]|=(X>>5);PTR[4]&=~0xf1; PTR[4]|=(X&0x1f)<<3;}//17 bits . DO NOT SET FPN TO 0 !!

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#ifndef SIP450_PRIMITIV_H
typedef enum
{
#if 1 //transition from cvm
  DUMMY_DATA=0x0,
  KEY_MESSAGE,
#endif

  API_FP_INIT_REQ = 0x4600,
  API_FP_INIT_CFM = 0x4601,
  API_FP_NVS_UPDATE_IND = 0x4602,
  API_FP_NVS_UPDATE_RES = 0x4603,
  API_FP_RESET_REQ = 0x4000,
  API_FP_RESET_IND = 0x4001,
  API_FP_GET_FW_VERSION_REQ = 0x4002,
  API_FP_GET_FW_VERSION_CFM = 0x4003,
  API_FP_GET_ID_REQ = 0x4004,
  API_FP_GET_ID_CFM = 0x4005,
  API_FP_SET_ACCESS_CODE_REQ = 0x4008,
  API_FP_SET_ACCESS_CODE_CFM = 0x4009,
  API_FP_GET_ACCESS_CODE_REQ = 0x400A,
  API_FP_GET_ACCESS_CODE_CFM = 0x400B,
  API_FP_SET_EEPROM_REQ = 0x4012,
  API_FP_SET_EEPROM_CFM = 0x4013,
  API_FP_GET_EEPROM_REQ = 0x4014,
  API_FP_GET_EEPROM_CFM = 0x4015,
  API_FP_GET_REGISTRATION_COUNT_REQ = 0x4100,
  API_FP_GET_REGISTRATION_COUNT_CFM = 0x4101,
  API_FP_DELETE_REGISTRATION_REQ = 0x4102,
  API_FP_DELETE_REGISTRATION_CFM = 0x4103,
  API_FP_REGISTRATION_DELETED_IND = 0x4104,
  API_FP_SET_REGISTRATION_MODE_REQ = 0x4105,
  API_FP_SET_REGISTRATION_MODE_CFM = 0x4106,
  API_FP_REGISTRATION_COMPLETE_IND = 0x4107,
  API_FP_HANDSET_PRESENT_IND = 0x4108,
  API_FP_GET_HANDSET_IPUI_REQ = 0x4109,
  API_FP_GET_HANDSET_IPUI_CFM = 0x410A,
  API_FP_SETUP_IND = 0x4400,
  API_FP_SETUP_RES = 0x4401,
  API_FP_SETUP_REQ = 0x4402,
  API_FP_SETUP_CFM = 0x4403,
  API_FP_SETUP_ACK_REQ = 0x4423,
  API_FP_SETUP_ACK_CFM = 0x4424,
  API_FP_ALERT_IND = 0x4404,
  API_FP_ALERT_REQ = 0x4405,
  API_FP_ALERT_CFM = 0x4406,
  API_FP_CONNECT_IND = 0x4407,
  API_FP_CONNECT_RES = 0x4408,
  API_FP_CONNECT_REQ = 0x4409,
  API_FP_CONNECT_CFM = 0x440A,
  API_FP_SIGNAL_REQ = 0x440B,
  API_FP_SIGNAL_CFM = 0x440C,
  API_FP_SEND_CLIP_REQ = 0x440D,
  API_FP_SEND_CLIP_CFM = 0x440E,
  API_FP_RELEASE_IND = 0x440F,
  API_FP_RELEASE_RES = 0x4410,
  API_FP_RELEASE_REQ = 0x4411,
  API_FP_RELEASE_CFM = 0x4412,
  API_FP_REJECT_IND = 0x4413,
  API_FP_MULTIKEYPAD_IND = 0x4414,
  API_FP_CALL_PROC_REQ = 0x4415,
  API_FP_CALL_PROC_CFM = 0x4416,
  API_FP_IWU_TO_IWU_REQ = 0x4417,
  API_FP_IWU_TO_IWU_CFM = 0x4418,
  API_FP_IWU_TO_IWU_IND = 0x4419,
  API_FP_PROPRIETARY_REQ = 0x441A,
  API_FP_PROPRIETARY_CFM = 0x441B,
  API_FP_PROPRIETARY_IND = 0x441C,
  API_FP_MODIFY_CODEC_REQ = 0x441D,
  API_FP_MODIFY_CODEC_CFM = 0x441E,
  API_FP_MODIFY_CODEC_IND = 0x441F,
  API_FP_MODIFY_CODEC_RES = 0x4420,
  API_FP_CODEC_INFO_IND = 0x4421,
  API_FP_CALLED_NUMBER_IND = 0x4422,

#if 1 //transition from cvm
  API_FP_GET_MODEL_REQ=0x4006,
  API_FP_GET_MODEL_CFM=0x4007,
  API_FP_SET_LED_REQ=0x400C,  
  API_FP_SET_LED_CFM=0x400D, 
  API_FP_SET_REGISTER_REQ=0x400E,
  API_FP_SET_REGISTER_CFM=0x400F,
  API_FP_GET_REGISTER_REQ=0x4010,
  API_FP_GET_REGISTER_CFM=0x4011,  
  API_FP_INIT_PCM_REQ=0x4200,
  API_FP_INIT_PCM_CFM=0x4201,
  API_FP_SET_PCM_CODEC_REQ=0x4202,
  API_FP_SET_PCM_CODEC_CFM=0x4203,
  API_FP_FWU_ENABLE_REQ=0x4F00,
  API_FP_FWU_ENABLE_CFM=0x4F01,
  API_FP_FWU_DEVICE_NOTIFY_IND=0x4F02,
  API_FP_FWU_UPDATE_REQ=0x4F03,
  API_FP_FWU_UPDATE_CFM=0x4F04,
  API_FP_FWU_UPDATE_IND=0x4F05,
  API_FP_FWU_UPDATE_RES=0x4F06,
  API_FP_FWU_GET_BLOCK_IND=0x4F07,
  API_FP_FWU_GET_BLOCK_RES=0x4F08,
  API_FP_FWU_GET_CRC_IND=0x4F09,
  API_FP_FWU_GET_CRC_RES=0x4F0A,
  API_FP_FWU_COMPLETE_IND=0x4F0B,
  API_FP_FWU_STATUS_IND=0x4F0C,  
#endif  
  
} ApiPrimitiveIdType;
typedef uint16 Sip450ApiPrimitiveType;

typedef Sip450ApiPrimitiveType PrimitiveType;
#define RosPrimitiveType Sip450ApiPrimitiveType
#endif

/* This enum defines the error codes that can be returned from the CVM /
   Handsets to the MCU. */
typedef enum {
  AS_SUCCESS       = 0x00, /* The request completed successfully. */
  AS_NOT_CONNECTED = 0x01, /* No connection to the handset. */
  AS_NOT_SUPPORTED = 0x02, /* The request is not supported. */
  AS_BAD_ARGUMENTS = 0x03, /* One or more arguments are not correct. */
  AS_BAD_ADDRESS   = 0x04, /* The address is incorrect. */
  AS_BAD_HANDLE    = 0x05, /* The handle is invalid. */
  AS_BAD_DATA      = 0x06, /* The data is invalid. */
  AS_BAD_LENGTH    = 0x07, /* The command length is incorrect. */
  AS_NO_MEMORY     = 0x08, /* Not enough storage is available to process this command. */
  AS_NO_DEVICE     = 0x09, /* No such handset / device. */
  AS_NO_DATA       = 0x0A, /* No data is available. */
  AS_NOT_READY     = 0x0B, /* The device is not ready. */
  AS_CANCELLED     = 0x0C, /* The operation was cancelled. */
  AS_BUSY          = 0x0D, /* The device or resource (e.g. line) is busy. */
  AS_TIMEOUT       = 0x0E, /* This operation returned because the timeout period
                              expired. */
  AS_NOT_FOUND     = 0x0F, /* Element not found. */
  AS_DENIED        = 0x10, /* Access denied or authentication failed. */
  AS_REJECTED      = 0x11, /* Rejected (e.g. by user). */
  AS_NO_RESOURCE   = 0x12, /* Not enough resources are available to process this
                              command. */
  AS_CALL_DROPPED  = 0x13, /* The call was dropped (out of range or dead battery). */
  AS_FAILED        = 0x14, /* The requested command failed. */
  AS_UNSPECIFIED   = 0xFF  /* Unspecified error. */
} ApiStatusIdType;
typedef uint8 ApiStatusType;

/* This struct is used to specify the Model ID type. */
typedef struct {
  uint16  MANIC;                        /* The manufacture code of the device. The EMC
                                           code of the device is used as manufacture code. */
  uint8  MODIC;                         /* The model code of the device. */
} PACKED_STRUCT ApiModelIdType;

/* This enum defines the DECT types supported by the CVM. */
typedef enum {
  AD_EU_DECT = 0x00, /* EU DECT */
  AD_US_DECT = 0x01, /* US DECT */
  AD_INVALID = 0xFF  /* [0x02; 0xFF] is invalid. */
} ApiDectTypeIdType;
typedef uint8 ApiDectTypeType;

/* This type is used to hold the handset id identifying a connection
   between the CVM and a handset. */
typedef struct {
  uint8  HandsetId : 4;                 /* Bit 0-3: The handset Id. Valid values: [1; N]
                                           where N is equal to the max number of handsets
                                           that can be registered on the CVM. */
  uint8  Instance  : 4;                 /* Bit 4-7: Reserved; MUST be set to 0 always. */
} PACKED_STRUCT ApiHandsetIdBitType;
typedef uint8 ApiHandsetIdType;

/* This enum defines the possible call progress indications supported by
   the CVM. */
typedef enum {
  AP_IN_BAND_AVAILABLE     = 0x00, /* In band tones available. */
  AP_IN_BAND_NOT_AVAILABLE = 0x01, /* In band tones is not available. */
  AP_INVALID               = 0xFF  /* [0x02; 0xFF] is reserved. */
} ApiProgressIndIdType;
typedef uint8 ApiProgressIndType;

/* This enum defines the basic voice services supported. */
typedef enum
{
  ABS_BASIC_SPEECH    = 0x00, /* Basic speech */
  ABS_WIDEBAND_SPEECH = 0x08  /* Wideband speech */
} ApiBasicServiceIdType;
typedef uint8 ApiBasicServiceType;

/* This enum defines the call classes supported. */
typedef enum
{
  ACC_NORMAL   = 0x08, /* Normal call */
  ACC_INTERNAL = 0x09, /* Internal call */
  ACC_SERVICE  = 0x0B  /* Service call */
} ApiCallClassIdType;
typedef uint8 ApiCallClassType;

/* This enum defines the possible values supported by the Signal parameter
   of some of the mails in the PP Call Handling section (from the DECT
   specification ETS 300 175-5). */
typedef enum {
  ASV_DIAL_TONE_ON               = 0x00, /*  */
  ASV_RINGBACK_TONE_ON           = 0x01, /*  */
  ASV_INTERCEPT_TONE_ON          = 0x02, /*  */
  ASV_NETWORK_CONGESTION_TONE_ON = 0x03, /*  */
  ASV_BUSY_TONE_ON               = 0x04, /*  */
  ASV_CONFIRM_TONE_ON            = 0x05, /*  */
  ASV_ANSWER_TONE_ON             = 0x06, /*  */
  ASV_CALL_WAITING_TONE_ON       = 0x07, /*  */
  ASV_TONES_OFF                  = 0x3F, /*  */
  ASV_ALERTING_ON_PATTERN0_INT   = 0x40, /*  */
  ASV_ALERTING_ON_PATTERN1       = 0x41, /*  */
  ASV_ALERTING_ON_PATTERN2       = 0x42, /*  */
  ASV_ALERTING_ON_PATTERN3       = 0x43, /*  */
  ASV_ALERTING_ON_PATTERN4       = 0x44, /*  */
  ASV_ALERTING_ON_PATTERN5       = 0x45, /*  */
  ASV_ALERTING_ON_PATTERN6       = 0x46, /*  */
  ASV_ALERTING_ON_PATTERN7       = 0x47, /*  */
  ASV_ALERTING_OFF               = 0x4F, /*  */
  ASV_CUSTOM_FIRST               = 0x80, /*  */
  ASV_CUSTOM_NONE                = 0xFF  /*  */
} ApiSignalValueIdType;
typedef uint8 ApiSignalValueType;

/* This enum defines the release reason codes supported. */
typedef enum
{
  ARR_NORMAL                 = 0x00, /*  */
  ARR_UNEXPECTED_MESSAGE     = 0x01, /*  */
  ARR_INVALID_IDENTY         = 0x08, /*  */
  ARR_AUTHEN_FAILED          = 0x09, /*  */
  ARR_UNKNOWN_IDENTITY       = 0x0A, /*  */
  ARR_TIMER_EXPIRY           = 0x0d, /*  */
  ARR_PARTIAL_RELEASE        = 0x0e, /*  */
  ARR_UNKNOWN                = 0x0f, /*  */
  ARR_USER_DETACHED          = 0x10, /*  */
  ARR_USER_OUT_RANGE         = 0x11, /*  */
  ARR_USER_UNKNOWN           = 0x12, /*  */
  ARR_USER_ACTIVE            = 0x13, /*  */
  ARR_USER_BUSY              = 0x14, /*  */
  ARR_USER_REJECTION         = 0x15, /*  */
  ARR_INSUFFICIENT_RESOURCES = 0x32, /*  */
  ARR_IWU_CONGESTION         = 0x34, /*  */
  ARR_CALL_RESTRICTION       = 0x40, /*  */
  ARR_INVALID                = 0xFF  /*  */
} ApiReleaseReasonIdType;
typedef uint8 ApiReleaseReasonType;

/* This enum defines the number types supported. */
typedef enum 
{
  ANT_UNKNOWN          = 0x00, /* Unknown */
  ANT_INTERNATIONAL    = 0x01, /* International number */
  ANT_NATIONAL         = 0x02, /* National number */
  ANT_NETWORK_SPECIFIC = 0x03, /* Network specific number */
  ANT_SUBSCRIBER       = 0x04, /* Subscriber number */
  ANT_ABBREVIATED      = 0x06, /* Abbreviated number */
  ANT_INVALID          = 0xFF  /*  */
} ApiNumberTypeIdType;
typedef uint8 ApiNumberTypeType;

/* This enum defines the numbering planes supported. NOTE: If ANPI_SIP is
   selected the SIP interface must check the called number. If the number
   already contains ?sip:? the SIP interface shall pass the number unchanged.
   Otherwise the SIP interface must form the number as specified in RFC 3261.
   (E.g. sip:<number>@xxx.yyy) */
typedef enum
{
  ANPI_UNKNOWN         = 0x00, /* Unknown */
  ANPI_E164_ISDN       = 0x01, /* ISDN/telephony plan ITU-T Recommendations E.164/E.163 */
  ANPI_X121            = 0x03, /* Data plan ITU-T Recommendation X.121 */
  ANPI_TCP_IP          = 0x07, /* TCP/IP address */
  ANPI_NATIONAL        = 0x08, /* National standard plan */
  ANPI_PRIVATE         = 0x09, /* Private plan */
  ANPI_SIP             = 0x0A, /* SIP addressing scheme, "To:" or "From:"  field (see
                                  RFC 3261) */
  ANPI_INTERNET        = 0x0B, /* Internet character format address */
  ANPI_LAN_MAC         = 0x0C, /* LAN MAC address */
  ANPI_X400            = 0x0D, /* ITU-T Recommendation X.400 [63] address */
  ANPI_PROFILE_SERVICE = 0x0E, /* Profile service specific alphanumeric identifier */
  ANPI_INVALID         = 0xFF  /*  */
} ApiNpiIdType;
typedef uint8 ApiNpiType;

/* This enum defines the presentation indicator values that can be used on
   calling name and number received from the network. */
typedef enum 
{
  API_PRESENTATION_ALLOWED    = 0x00, /* Presentation allowed. */
  API_PRESENTATION_RESTRICTED = 0x01, /* Presentation restricted. */
  API_PRESENTATION_NUMBER_NA  = 0x02, /* Number not available. */
  API_INVALID                 = 0xFF  /* [0x03; 0xFF] is reserved. */
} ApiPresentationIndicatorIdType;
typedef uint8 ApiPresentationIndicatorType;

/* This enum defines the string coding formats that can be used to encode
   strings exchanged between the MCU and the handsets. */
typedef enum 
{
  AUA_DECT             = 0x00, /* IA5 chars used. */
  AUA_NETWORK_SPECIFIC = 0xFF  /*  */
} ApiUsedAlphabetIdType;
typedef uint8 ApiUsedAlphabetType;

/* This enum defines the string character formats that can be used to
   encode strings exchanged between the MCU and the handsets. */
typedef enum 
{
  AUC_DEFAULT = 0x00, /* Strings are encoded as described in the used IE type. */
  AUC_IA5CHAR = 0x01, /* Strings are encoded as IA5 character table. */
  AUC_XCHAR8  = 0x02, /* Strings are encoded as 8 bit XCHARTYPE. Terminating zero must
                         be included in the string, and included in the string length. */
  AUC_XCHAR16 = 0x03, /* Strings are encoded as 16 bit XCHARTYPE. Terminating zero must
                         be included, and included in the string length. */
  AUC_INVALID = 0xFF  /* [0x04; 0xFF] is reserved. */
} ApiUsedCharIdType;
typedef uint8 ApiUsedCharType;

/* This type is used to hold information about the number called / dialled
   on a handset. */
typedef struct
{
  ApiNumberTypeType  NumberType;        /* Number type */
  ApiNpiType  Npi;                      /* Numbering Plan Identification */
  uint8  NumberLength;                  /* Number length in bytes */
  uint8  Number[1];                     /* The number as IA5 string (NumberLength number
                                           of bytes). */
} PACKED_STRUCT ApiCalledNumberType;

/* This is used to present the calling party number.
    This is also used in intercom call setup to identify the calling handset.
    For the coding of the IE <<Calling party number>> see [3] section F.1.3.2
   Internal Call CLIP procedure description.
    The Presentation indicator is always set to ?Presentation allowed? and the
   Screening indicator is always set to ?User-provided, not screened?. */
typedef struct 
{
  ApiNumberTypeType  NumberType;        /* Number type */
  ApiNpiType  Npi;                      /* Numbering Plan Identification */
  ApiPresentationIndicatorType  PresentationInd; /* Presentation indicator. */
  uint8  NumberLength;                  /* Number length in bytes */
  uint8  Number[1];                     /* The number as IA5 string (NumberLength number
                                           of bytes). */
} PACKED_STRUCT ApiCallingNumberType;

/* This type is used to hold information about the number called / dialled
   on a handset. The Presentation indicator is always set to ?Presentation
   allowed? and the Screening indicator is always set to ?User-provided, not
   screened? */
typedef struct
{
  ApiUsedAlphabetType  UsedAlphabet;    /* Specifies the encoding of the name. */
  ApiPresentationIndicatorType  PresentationInd; /* Presentation indicator. */
  uint8  NameLength;                    /* Name length in bytes */
  uint8  Name[1];                       /* The name (NameLength number of bytes). */
} PACKED_STRUCT ApiCallingNameType;

/* This enum defines the CLIP reason codes supported. */
typedef enum {
  ACRT_NO_REASON                   = 0x00, /*  */
  ACRT_CLIP_UNAVAILABLE            = 0x01, /*  */
  ACRT_CLIP_PRIVATE                = 0x02, /*  */
  ACRT_CLIP_OUT_OF_AREA            = 0x03, /*  */
  ACRT_CLIP_CHECKSUM_ERROR         = 0x04, /*  */
  ACRT_CLIP_TIMEOUT                = 0x05, /*  */
  ACRT_CLIP_TIME_DATE_FORMAT_ERROR = 0x06, /*  */
  ACRT_CLIP_NO_DATA                = 0x07, /* No CLIP data detected */
  ACTR_CLIP_COIN_PHONE_CALL        = 0x08, /* Taiwan addition */
  ACTR_CLIP_INTERNATIONAL          = 0x09, /* Taiwan addition */
  ACRT_INVALID                     = 0xFF  /* Unspecified */
} ApiClipReasonIdType;
typedef uint8 ApiClipReasonType;

/* This struct is used to hold date info only. */
typedef struct 
{
  uint8  Year;
  uint8  Month;
  uint8  Day;
} PACKED_STRUCT ApiDateCodeType;

/* This struct is used to hold time info only. */
typedef struct 
{
  uint8  Hour;
  uint8  Minute;
  uint8  Second;
  uint8  TimeZone;                      /* The Time Zone indicates the difference,
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
} PACKED_STRUCT ApiTimeCodeType;

/* This struct is used to hold both time and date info. */
typedef struct
{
  uint8  Year;
  uint8  Month;
  uint8  Day;
  uint8  Hour;
  uint8  Minute;
  uint8  Second;
  uint8  TimeZone;                      /* The Time Zone indicates the difference,
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

/* This union is sued to hold the time and date or just the time or the
   date. */
typedef union 
{
  ApiDateCodeType  DateCode;
  ApiTimeCodeType  TimeCode;
  ApiTimeDateCodeType  TimeDateCode;
} ApiTimeDateValueType;

/* Specifies the time format. */
typedef enum 
{
  ATDC_UNUSED    = 0x00, /*  */
  ATDC_TIME      = 0x01, /*  */
  ATDC_DATE      = 0x02, /*  */
  ADTC_TIME_DATE = 0x03  /*  */
} ApiTimeDateCodingIdType;
typedef uint8 ApiTimeDateCodingType;

/* Specifies the time data interpretation. */
typedef enum 
{
  ATDI_CURRENT       = 0,    /* The current time/date */
  ATDI_DURATION      = 1,    /* Time duration (in Years, Months, Days and/or Hours,
                                Minutes, Seconds, Time Zone = 0) */
  ATDI_MMS_START     = 0x20, /* The time/date at which to start forwarding/delivering
                                the MMS message */
  ATDI_MMS_CREATE    = 0x21, /* The time/date the MMS user data was created */
  ATDI_MMS_MODIFIED  = 0x22, /* The time/date the MMS user data was last modified */
  ATDI_MMS_RECEIVED  = 0x23, /* The time/date the message was received by the MCE */
  ATDI_MMS_DELIVERED = 0x24, /* The time/date the message was delivered/accessed by the
                                End Entity */
  ATDI_IDENTIFIER    = 0x28  /* The time/date stamp for use as an identifier */
} ApiTimeDateInterpretationIdType;
typedef uint8 ApiTimeDateInterpretationType;

/* This type is used to hold time and date information when included in a
   CLIP message. */
typedef struct
{
  ApiTimeDateCodingType  Coding;
  ApiTimeDateInterpretationType  Interpretation;
  ApiTimeDateValueType  TimeDate;
} PACKED_STRUCT ApiTimeDateType;

/* This byte contains the number of waiting messages. */
typedef uint8 ApiNmssType;              /* 0 indicates 0 messages. */


typedef enum 
{
  AV_OFF = 0,    /* Deactivation (indicator off) */
  AV_ON  = 0xFF, /* Activation (indicator on) */
} ApiVmwiIdType;
typedef uint8 ApiVmwiType;

/* This type is used to store all CLIP related information. */
typedef struct 
{
  ApiClipReasonType  ReasonCode;        /* Reason code */
  ApiClipReasonType  ReasonName;        /* Reason code */
  ApiUsedCharType  UsedChar;            /* This describes the encoding of the strings in
                                           name and number. */
  uint8  NumberLen;                     /* Number length */
  uint8  NameLen;                       /* Name Length */
  uint8  TimeDateLen;                   /* Length of time date */
  uint8  VmwiLen;                       /* Length of message waiting indicator */
  uint8  NmssLen;                       /* Lengt of SS element. */
  uint8  Data[1];                       /* {ApiCallingNumberType}[NumberLen],
                                           {ApiCallingNameType}[NameLen],
                                           {ApiTimeDateType}[TimeDateLen],
                                           {ApiVmwiType}[VmwiLen],
                                           {ApiNmssType}[NmssLen]. */
} PACKED_STRUCT ApiClipDataType;

/* This enum defines the possible CODEC types that can be exchanged between
   the CVM and the handsets during CODEC negotiation. */
typedef enum
{
  ACT_NONE             = 0x00, /*  */
  ACT_USER_SPECIFIC_32 = 0x01, /* User specific, information transfer rate 32 kbit/s */
  ACT_G726             = 0x02, /* G.726 ADPCM, information transfer rate 32 kbit/s */
  ACT_G722             = 0x03, /* G.722, , information transfer rate 64 kbit/s */
  ACT_G711A            = 0x04, /* G.711 A-law PCM, information transfer rate 64 kbit/s */
  ACT_G711U            = 0x05, /* G.711 u-law PCM, information transfer rate 64 kbit/s */
  ACT_G7291            = 0x06, /* G.729.1, information transfer rate 32 kbit/s */
  ACT_MP4_32           = 0x07, /* MPEG-4 ER AAC-LD, information transfer rate 32 kbit/s */
  ACT_MP4_64           = 0x08, /* MPEG-4 ER AAC-LD, information transfer rate 64 kbit/s */
  ACT_USER_SPECIFIC_64 = 0x09, /* User specific, information transfer rate 64 kbit/s */
  ACT_INVALID          = 0xFF  /* [0x0A; 0xFF]is reserved */
} ApiCodecIdType;
typedef uint8 ApiCodecType;

/* This enum defines the MAC DLC service types supported. */
typedef enum
{
  AMDS_1_MD    = 0x00, /* DLC service LU1, MAC service: In_minimum_delay */
  AMDS_1_ND    = 0x01, /* DLC service LU1, MAC service In_normal_delay */
  AMDS_1_IED   = 0x02, /* DLC service LU1, MAC service Ip_error_detect */
  AMDS_1_IQED  = 0x03, /* DLC service LU1, MAC service Ipq_error_detect */
  AMDS_7_ND    = 0x04, /* DLC service LU7, MAC service In_normal_delay */
  AMDS_1_NDF   = 0x05, /* DLC service LU1, MAC service In_normal_delay, framed as TS 102
                          527-1 [76], clause C.1 */
  AMDS_INVALID = 0xFF  /* [0x06; 0xFF] is reserved */
} ApiMacDlcServiceIdType;
typedef uint8 ApiMacDlcServiceType;

/* This enum defines the C-plan routings supported. */
typedef enum 
{
  ACPR_CS      = 0x00, /* CS only */
  ACPR_CS_CF   = 0x01, /* CS preferred/CF accepted */
  ACPR_CF_CS   = 0x02, /* CF preferred/CS accepted */
  ACPR_CF      = 0x03, /* CF only */
  ACPR_INVALID = 0xFF  /* [0x04; 0xFF] is reserved */
} ApiCplaneRoutingIdType;
typedef uint8 ApiCplaneRoutingType;

/* This enum defines the RF slot formats supported. */
typedef enum
{
  ASS_HS      = 0x00, /* Half slot; j = 0. */
  ASS_LS640   = 0x01, /* Long slot; j = 640 */
  ASS_LS672   = 0x02, /* Long slot; j = 672 */
  ASS_FS      = 0x04, /* Full slot */
  ASS_DS      = 0x05, /* Double slot */
  ASS_INVALID = 0xFF  /* [0x06; 0xFF] is reserved */
} ApiSlotSizeIdType;
typedef uint8 ApiSlotSizeType;

/* This struct holds all the CODEC related information. */
typedef struct ApiCodecInfoType
{
  ApiCodecType  Codec;
  ApiMacDlcServiceType  MacDlcService;
  ApiCplaneRoutingType  CplaneRouting;
  ApiSlotSizeType  SlotSize;
} PACKED_STRUCT ApiCodecInfoType;


typedef enum
{
  ANI_NOT_POSSIBLE = 0x00, /*  */
  ANI_POSSIBLE     = 0x01, /*  */
  ANI_INVALID      = 0xFF  /* [0x02; 0xFF] is reserved */
} ApiNegotiationIndicatorIdType;
typedef uint8 ApiNegotiationIndicatorType;

/* This type is used to hold information about a complete CODEC list. */
typedef struct ApiCodecListType
{
  ApiNegotiationIndicatorType  NegotiationIndicator;
  uint8  NoOfCodecs;
  ApiCodecInfoType  Codec[1];           /* NoOfCodecs elements */
} PACKED_STRUCT ApiCodecListType;

/* This enum defines the user specific protocol discriminator values
   supported in IWU to IWU and escape to proprietary information element. */
typedef enum 
{
  ADT_UNSPECIFIED = 0x00, /* Unspecified */
  ADT_EMC         = 0x01, /* The EMC is used to identify the IWU?s supported. */
  ADT_INVALID     = 0xFF  /* [0x02; 0xFF] is reserved. */
} ApiDiscriminatorIdType;
typedef uint8 ApiDiscriminatorType;

/* This type is used to send IWU to IWU information elements */
typedef struct
{
  uint8  TransmitReject;                /* TRUE (0x01) for transmission. 
                                           FALSE (0x00) for reject. */
  uint8  IwuProtocolDiscriminator;      /* Protocol Discriminator. */
  ApiDiscriminatorType  Discriminator;  /* Discriminator.
                                           Only valid for IwuProtocolDiscriminator set to 0
                                           (User Specific) */
  uint16  EmcCode;                      /* Used when Discriminator is set to EMC. */
  uint16  Length;                       /* Length of IWU content in bytes. */
  uint8  Data[1];                       /* IWU content */
} PACKED_STRUCT ApiIwuToIwuType;

/* This type is used to send escape to proprietary information elements. */
typedef struct 
{
  ApiDiscriminatorType  Discriminator;  /* Discriminator. */
  uint16  EmcCode;                      /* Used when Discriminator is set to EMC. */
  uint16  Length;                       /* Length of proprietary content in bytes. */
  uint8  Data[1];                       /* Proprietary content */
} PACKED_STRUCT ApiEscapeToProprietaryType;


typedef struct Isip450apiEmptySignalType
{
  PrimitiveType Primitive;
} PACKED_STRUCT Isip450apiEmptySignalType;

/* This mail is used by the application to start the DECT driver. The mail
   contains the NVS data stored by the DECT driver during earlier uses (See
   API_FP_NVS_UPDATE_IND). If this is the first time the DECT driver is used,
   then the NVS data must be set to all 0xFF, and then defaulted using the
   production test interface. The DECT driver will return an API_FP_INIT_CFM
   in response.
    The mail is only required to be sent once after Linux boot. Until it is
   sent all other mails will be ignored. */
typedef struct ApiFpInitReqType
{
  PrimitiveType Primitive;            /* API_FP_INIT_REQ = 0x4600 */
  uint8 NvsData[API_FP_NVS_SIZE];
} PACKED_STRUCT ApiFpInitReqType;

/* Confirmation for API_FP_INIT_REQ.
    The mail contains information about the addresses of the ADPCM buffers
   used by the device driver. */
typedef struct ApiFpInitCfmType
{
  PrimitiveType Primitive;            /* API_FP_INIT_CFM = 0x4601 */
  uint32 AdpcmRxBufferAddr[API_FP_ADPCM_CHANNELS]; /* ADPCM DECT receive buffer
                                                       addresses  (i.e. SIP transmit
                                                       direction) */
  uint32 AdpcmTxBufferAddr[API_FP_ADPCM_CHANNELS]; /* ADPCM DECT transmit buffer
                                                       addresses  (i.e. SIP receive 
                                                       direction) */
} PACKED_STRUCT ApiFpInitCfmType;

/* This mail is sent from the DECT driver, when changes has to be stored in
   NVS. The application must save the data in order to supply it the next time
   the DECT driver is initialized with API_FP_INIT_REQ. The application must
   confirm this with API_FP_NVS_UPDATE_RES. 
     */
typedef struct ApiFpNvsUpdateIndType
{
  PrimitiveType Primitive;            /* API_FP_NVS_UPDATE_IND = 0x4602 */
  uint16 SeqNo;                         /* Sequence number. Use this in
                                           API_FP_NVS_UPDATE_RES */
  uint16 NvsOffset;                     /* Offset into NVS to store this data. */
  uint16 Length;                        /* Length of NvsData field. */
  uint8 NvsData[1];                     /* Variable length data contains length bytes of
                                           NVS data to be stored. */
} PACKED_STRUCT ApiFpNvsUpdateIndType;

/* This mail is sent from the application in response to
   API_FP_NVS_UPDATE_IND. 
     */
typedef struct ApiFpNvsUpdateResType
{
  PrimitiveType Primitive;            /* API_FP_NVS_UPDATE_RES = 0x4603 */
  uint16 SeqNo;                         /* Sequence number from API_FP_NVS_UPDATE_IND */
} PACKED_STRUCT ApiFpNvsUpdateResType;

/* This mail is used by the MCU to request the CVM to do a SW reset. The
   CVM will reinitialize the serial connection (see section 7.3) and return an
   API_FP_RESET_IND when the CVM is ready to accept commands from the Host
   again. */
typedef Isip450apiEmptySignalType ApiFpResetReqType;

/* This mail is used by CVM to indicate that it has been started (after
   power on or reset). The CVM is ready to accept commands from the MCU when
   this mail has been sent. */
typedef struct ApiFpResetIndType
{
  PrimitiveType Primitive;            /* API_FP_RESET_IND = 0x4001 */
  ApiStatusType Status;                 /* Indicates whether the CVM is ready or not. */
} PACKED_STRUCT ApiFpResetIndType;

/* This command is used by the MCU to get the FW version of the CVM. */
typedef Isip450apiEmptySignalType ApiFpGetFwVersionReqType;

/* This mail is used to confirm the API_FP_GET_FW_VERSION_REQ command. */
typedef struct ApiFpGetFwVersionCfmType
{
  PrimitiveType Primitive;            /* API_FP_GET_FW_VERSION_CFM = 0x4003 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint32 VersionHex;                    /* The FW version. */
  uint8 LinkDate[5];                    /* The link date. */
  ApiDectTypeType DectType;             /* Specifies whether this is unit is setup for
                                           EU or US DECT. */
} PACKED_STRUCT ApiFpGetFwVersionCfmType;

/* This command is used by the MCU to request the CVM to return a unique
   identifier for that particular base station. */
typedef Isip450apiEmptySignalType ApiFpGetIdReqType;

/* This mail is used by the CVM to return the unique base station id to the
   MCU. */
typedef struct ApiFpGetIdCfmType
{
  PrimitiveType Primitive;            /* API_FP_GET_ID_CFM = 0x4005 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint8 Id[5];                          /* The id of the base station. The RFPI of the
                                           base is used to identify the base. */
} PACKED_STRUCT ApiFpGetIdCfmType;

/* This command is used to set the DECT access code in the CVM. */
typedef struct ApiFpSetAccessCodeReqType
{
  PrimitiveType Primitive;            /* API_FP_SET_ACCESS_CODE_REQ = 0x4008 */
  uint8 Ac[2];                          /* The access code stored as 4 nibbles. E.g.
                                           Access code 1234 is stores as Ac[0]=0x12, Ac[1]=
                                           0x34 */
} PACKED_STRUCT ApiFpSetAccessCodeReqType;

/* This mail is used to confirm the API_FP_SET_ACCESS_CODE_REQ command. */
typedef struct ApiFpSetAccessCodeCfmType
{
  PrimitiveType Primitive;            /* API_FP_SET_ACCESS_CODE_CFM = 0x4009 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpSetAccessCodeCfmType;

/* This command is used to get the DECT access code stored in the CVM. */
typedef Isip450apiEmptySignalType ApiFpGetAccessCodeReqType;

/* This mail is used to confirm the API_FP_GET_ACCESS_CODE_REQ command. */
typedef struct ApiFpGetAccessCodeCfmType
{
  PrimitiveType Primitive;            /* API_FP_GET_ACCESS_CODE_CFM = 0x400B */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint8 Ac[2];                          /* The access code stored as 4 nibbles. E.g.
                                           Access code 1234 is stores as Ac[0]=0x12, Ac[1]=
                                           0x34 */
} PACKED_STRUCT ApiFpGetAccessCodeCfmType;

/* This command is used to modify the content of the EEPROM. This should be
   used with caution! */
typedef struct ApiFpSetEepromReqType
{
  PrimitiveType Primitive;            /* API_FP_SET_EEPROM_REQ = 0x4012 */
  uint16 Address;                       /* Offset in the EEPROM */
  uint8 DataLength;                     /* The number of bytes to write to the EEPROM. */
  uint8 Data[1];                        /* The data to be written to the EEPROM. */
} PACKED_STRUCT ApiFpSetEepromReqType;

/* This mail is used to confirm the API_FP_SET_EEPROM_REQ command. */
typedef struct ApiFpSetEepromCfmType
{
  PrimitiveType Primitive;            /* API_FP_SET_EEPROM_CFM = 0x4013 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint16 Address;                       /* Offset in the EEPROM */
  uint8 DataLength;                     /* The number of bytes written to the EEPROM. */
} PACKED_STRUCT ApiFpSetEepromCfmType;

/* This command is used to read data from the EEPROM. */
typedef struct ApiFpGetEepromReqType
{
  PrimitiveType Primitive;            /* API_FP_GET_EEPROM_REQ = 0x4014 */
  uint16 Address;                       /* Offset in the EEPROM. */
  uint8 DataLength;                     /* The number of bytes to read from the EEPROM. */
} PACKED_STRUCT ApiFpGetEepromReqType;

/* This mail is used to confirm the API_FP_GET_EEPROM_REQ command. */
typedef struct ApiFpGetEepromCfmType
{
  PrimitiveType Primitive;            /* API_FP_GET_EEPROM_CFM = 0x4015 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint16 Address;                       /* Offset in the EEPROM. */
  uint8 DataLength;                     /* The number of bytes to read from the EEPROM. */
  uint8 Data[1];                        /* The data read from the EEPROM. */
} PACKED_STRUCT ApiFpGetEepromCfmType;

/* This command is used by the MCU to request the maximum number of
   handsets that can be registered to the CVM, the number of handsets and the
   Handset Ids of the handsets registered currently. */
typedef Isip450apiEmptySignalType ApiFpGetRegistrationCountReqType;

/* This mail is used by the CVM to confirm the
   API_FP_GET_REGISTRATION_COUNT_REQ command. */
typedef struct ApiFpGetRegistrationCountCfmType
{
  PrimitiveType Primitive;            /* API_FP_GET_REGISTRATION_COUNT_CFM = 0x4101 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint8 MaxNoHandsets;                  /* The maximum number of handsets that can be
                                           registered. */
  uint8 HandsetIdLength;                /* The number of handsets registered currently. */
  uint8 HandsetId[1];                   /* Array of Ids of the handsets registered.
                                           
(Index 0 to HandsetIdLength-1 is used.) */
} PACKED_STRUCT ApiFpGetRegistrationCountCfmType;

/* This command is used by the MCU to request the CVM to delete a
   registered handset. */
typedef struct ApiFpDeleteRegistrationReqType
{
  PrimitiveType Primitive;            /* API_FP_DELETE_REGISTRATION_REQ = 0x4102 */
  uint8 HandsetId;                      /* Index of the handset that shall be deleted. */
} PACKED_STRUCT ApiFpDeleteRegistrationReqType;

/* This mail is used by the CVM to confirm the
   API_FP_DELETE_REGISTRATION_REQ command. */
typedef struct ApiFpDeleteRegistrationCfmType
{
  PrimitiveType Primitive;            /* API_FP_DELETE_REGISTRATION_CFM = 0x4103 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint8 HandsetId;                      /* Index of the handset that shall be deleted. */
} PACKED_STRUCT ApiFpDeleteRegistrationCfmType;

/* This mail is used to inform the MCU when a registered handset has been
   deleted initiated from the handset. */
typedef struct ApiFpRegistrationDeletedIndType
{
  PrimitiveType Primitive;            /* API_FP_REGISTRATION_DELETED_IND = 0x4104 */
  uint8 HandsetId;                      /* Index of the handset that is deleted. */
} PACKED_STRUCT ApiFpRegistrationDeletedIndType;

/* This command is used by the MCU to request the CVM to enter or exit
   registration mode. */
typedef struct ApiFpSetRegistrationModeReqType
{
  PrimitiveType Primitive;            /* API_FP_SET_REGISTRATION_MODE_REQ = 0x4105 */
  uint8 RegistrationEnabled;            /* 1: Registration is enabled
                                           0: Registration is disabled */
  uint8 DeleteLastHandset;              /* This flag determines what happens if we have
                                           the maximum number of handsets registered and the
                                           user tries to register a new handset.
                                           1: The CVM will delete the last handset (#6).
                                           0: The registration will be rejected. */
} PACKED_STRUCT ApiFpSetRegistrationModeReqType;

/* This mail is used by the CVM to confirm the
   API_FP_SET_REGISTRATION_MODE_REQ command. */
typedef struct ApiFpSetRegistrationModeCfmType
{
  PrimitiveType Primitive;            /* API_FP_SET_REGISTRATION_MODE_CFM = 0x4106 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpSetRegistrationModeCfmType;

/* This mail is used to inform the MCU when a handset has been registered.
   A CODEC list is included if the handset supports wide band audio (CAT-iq
   handset). */
typedef struct ApiFpRegistrationCompleteIndType
{
  PrimitiveType Primitive;            /* API_FP_REGISTRATION_COMPLETE_IND = 0x4107 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint8 HandsetId;                      /* Id of the handset that was registered to the
                                           CVM. */
  ApiModelIdType ModelId;               /* The manufacture (MANIC) and model (MODIC)
                                           code of the base. The EMC code of the base is
                                           used as manufacture code. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType*}[CodecListLength] 
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpRegistrationCompleteIndType;

/* This mail is used to inform the Host when a handset has made a location
   update. This happens right after registration, when the handset is powered
   up and when it gets in to range again when it has been out of range. A
   CODEC list is included if the handset supports wide band audio (CAT-iq
   handset). */
typedef struct ApiFpHandsetPresentIndType
{
  PrimitiveType Primitive;            /* API_FP_HANDSET_PRESENT_IND = 0x4108 */
  uint8 HandsetId;                      /* Id of the handset that has made a location
                                           update. */
  ApiModelIdType ModelId;               /* The manufacture (MANIC) and model (MODIC)
                                           code of the base. The EMC code of the base is
                                           used as manufacture code. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType*}[CodecListLength]
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpHandsetPresentIndType;

/* This command is used by the MCU to request the IPUI of one of the
   handsets registered. */
typedef struct ApiFpGetHandsetIpuiReqType
{
  PrimitiveType Primitive;            /* API_FP_GET_HANDSET_IPUI_REQ = 0x4109 */
  uint8 HandsetId;                      /* The Id of the handset that the MCU wants the
                                           IPUI for. */
} PACKED_STRUCT ApiFpGetHandsetIpuiReqType;

/* This mail is used by the CVM to confirm the API_FP_GET_HANDSET_IPUI_REQ
   command. */
typedef struct ApiFpGetHandsetIpuiCfmType
{
  PrimitiveType Primitive;            /* API_FP_GET_HANDSET_IPUI_CFM = 0x410A */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint8 HandsetId;                      /* The Id for which the IPUI is read. */
  uint8 IPUI[5];                        /* The IPUI. */
} PACKED_STRUCT ApiFpGetHandsetIpuiCfmType;

/* This mail is used to inform the MCU when an air link has been
   established between a handset and the CVM. E.g. after a user has pressed
   the ?off hook? button on a handset. The number (dial string) is included if
   the uses has entered a number before the ?off hook? button was pressed. The
   Host can do the following when this message is received:
    Accept the call and enter ?overlap sending? (F-02) state by sending
   API_FP_SETUP_RES with Status = AS_SUCCESS followed by API_FP_SETUP_ACK_REQ.
   This can be used if dial string is not included in the API_FP_SETUP_IND message.
    Accept the call and enter ?active? (F-10) state directly by sending
   API_FP_SETUP_RES with Status = AS_SUCCESS followed by API_FP_CONNECT_REQ.
   This is done for PSTN lines normally regardless of whether the dial string
   is received in the API_FP_SETUP_IND.
    Accept the call and enter ?call proceeding? (F-03) state directly by
   sending API_FP_SETUP_RES with Status = AS_SUCCESS followed by API_FP_CALL_PROC_REQ.
    Accept the call and enter ?call delivered? (F-04) state directly by
   sending API_FP_SETUP_RES with Status = AS_SUCCESS followed by API_FP_ALERT_REQ.
    Reject the call by sending API_FP_SETUP_RES with Status = AS_REJECT. */
typedef struct ApiFpSetupIndType
{
  PrimitiveType Primitive;            /* API_FP_SETUP_IND = 0x4400 */
  ApiHandsetIdType HandsetId;           /* The id of the handset that has initiated the
                                           connection and the connection instance allocated
                                           for that connection. */
  uint8 DestinationId;                  /* Used to identify the selected line for an
                                           external call in a system supporting multiple
                                           lines. Will be 0 always if the handset initiating
                                           the call is an ?unknown DECT GAP? handset. 
                                           Note: This parameter should be ignored
                                           currently, as the CAT-iq specification of this
                                           feature is not completed yet. */
  ApiBasicServiceType BasicService;     /* Narrow/wide band speech encoding */
  ApiCallClassType CallClass;           /* DECT defined call classes. */
  uint8 KeypadLength;                   /* The length of ?other call related
                                           information?. */
  uint8 CalledNumberLength;             /* The length of the called number. */
  uint8 CallingNumberLength;            /* The length of the number identifying the
                                           calling handset. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 IwuLength;                      /* The length of optional DECT IWU information
                                           that the handset wants to send to the host. */
  uint8 ProprietaryLength;              /* The length of optional proprietary
                                           information element that the handset wants to
                                           send to the host. */
  uint8 Data[1];                        /* {uint8}[KeypadLength], 
                                           {ApiCalledNumberType}[CalledNumberLength], 
                                           {ApiCallingNumberType}[CallingNumberLength], 
                                           {ApiCodecListType}[CodecListLength], 
                                           {ApiIwuToIwuType}[IwuLength]},
                                           {ApiEscapeToProprietaryType}[ProprietaryLength]
                                           I.e. KeypadLength number of bytes with multi
                                           keypad data, followed by CalledNumberLength
                                           number of bytes holding the called number,
                                           followed by CallingNumberLength number of bytes
                                           holding the number of the calling handset,
                                           followed by CodecListLength number of bytes
                                           holding the CODEC list followed by IwuLength
                                           number of bytes with IWU information followed by
                                           ProprietaryLength of proprietary information. */
} PACKED_STRUCT ApiFpSetupIndType;

/* This mail is used by the MCU to inform the CVM about whether the
   requested call is made or not. This mail is also used to inform the CVM
   about which PCM channel to use for a handset initiated call if the audio
   must be connected to the PCM interface (for external calls only). */
typedef struct ApiFpSetupResType
{
  PrimitiveType Primitive;            /* API_FP_SETUP_RES = 0x4401 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the call is accepted or
                                           not. AS_REJECTED is used to indicate that the
                                           call is rejected by the user / host and
                                           AS_SUCCESS is used to indicate that the call is
                                           accepted. */
  uint8 DestinationId;                  /* UNUSED ON SIP450!
                                           External call: The PCM channel that is assigned
                                           to this call [0; 3].
                                           Internal call: Not used. */
} PACKED_STRUCT ApiFpSetupResType;

/* This mail is used by the MCU to initiate a call / connection to a
   handset. The call can be:
    an incoming call on the line (VoIP or PSTN)
    a call from another handset or
    base initiated page of the handset used to locate the handset. */
typedef struct ApiFpSetupReqType
{
  PrimitiveType Primitive;            /* API_FP_SETUP_REQ = 0x4402 */
  ApiHandsetIdType HandsetId;           /* The id of the handset that the CVM shall
                                           establish a connection to and the connection
                                           instance that the CVM shall use for that
                                           connection. */
  ApiBasicServiceType BasicService;     /* Narrow/wide band speech encoding */
  ApiCallClassType CallClass;           /* DECT defined call classes. */
  uint8 SourceId;                       /* UNUSED ON SIP450!
                                           External call: The PCM channel that is assigned
                                           to this call.
                                           Internal call: 0 = base; 1-n Handset1-n. */
  ApiSignalValueType Signal;            /* DECT alert pattern. */
  uint8 ClipLength;                     /* CLIP length. The ApiClipDataType is packed in
                                           an IWU when sending it t the handset. It is hence
                                           not understood / handles by all DECT GAP / CAT-iq
                                           compliant handsets. */
  uint8 CallingNumberLength;            /* The length of the number identifying the
                                           calling part. */
  uint8 CallingNameLength;              /* Then length of the name identifying the
                                           calling part. */
  uint8 CodecListLength;                /* CODEC List length. */
  uint8 IwuLength;                      /* The length of optional DECT IWU to IWU
                                           information that the host wants to send to the
                                           handset. */
  uint8 ProprietaryLength;              /* The length of optional proprietary
                                           information element. */
  uint8 Data[1];                        /* {ApiClipDataType}[ClipLength], 
                                           {ApiCallingNumberType}[CallingNumberLength], 
                                           {ApiCallingNameType}[CallingNameLength],
                                           {ApiCodecListType}[CodecListLength], 
                                           {ApiIwuToIwuType}[IwuLength]},
                                           {ApiEscapeToProprietaryType}[ProprietaryLength]
                                           I.e. ClipLength number of bytes with CLIP data,
                                           followed by CallingNumberLength number of bytes
                                           holding the number of the calling party, followed
                                           by CallingNameLength number of bytes holding the
                                           name of the calling party as IA5 string, followed
                                           by CodecListLength number of bytes holding the
                                           CODEC list followed by IwuLength number of bytes
                                           with IWU information followed by
                                           ProprietaryLength of proprietary information. */
} PACKED_STRUCT ApiFpSetupReqType;

/* This mail is used to confirm the API_FP_SETUP_REQ command. */
typedef struct ApiFpSetupCfmType
{
  PrimitiveType Primitive;            /* API_FP_SETUP_CFM = 0x4403 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the call is made or not. */
  ApiBasicServiceType BasicService;     /* Narrow/wide band speech encoding */
  ApiCallClassType CallClass;           /* DECT defined call classes. */
  uint8 SourceId;                       /* External call: The PCM channel that is
                                           assigned to this call.
                                           Internal call: 0 = base; 1-n Handset1-n. */
} PACKED_STRUCT ApiFpSetupCfmType;

/* This mail is used by the MCU to request the CVM to enter the ?overlap
   sending? state and send CC-SETUP-ACK message to the handset initiating the
   call. */
typedef struct ApiFpSetupAckReqType
{
  PrimitiveType Primitive;            /* API_FP_SETUP_ACK_REQ = 0x4423 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiSignalValueType Signal;            /* Alert signal. */
  ApiProgressIndType ProgressInd;       /* Call progress information (e.g. in band
                                           audio) */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 IwuLength;                      /* The length of optional DECT IWU information
                                           that the host wants to send to the handset. */
  uint8 ProprietaryLength;              /* The length of optional proprietary
                                           information element that the host wants to send
                                           to the handset. */
  uint8 Data[1];                        /* {ApiCodecListType}[CodecListLength], 
                                           {ApiIwuToIwuType}[IwuLength]},
                                           {ApiEscapeToProprietaryType}[ProprietaryLength]
                                           I.e. CodecListLength number of bytes holding the
                                           CODEC list followed by IwuLength number of bytes
                                           with IWU information followed by
                                           ProprietaryLength of proprietary information. */
} PACKED_STRUCT ApiFpSetupAckReqType;

/* This mail is used to confirm the API_FP_SETUP_ACK_REQ command. */
typedef struct ApiFpSetupAckCfmType
{
  PrimitiveType Primitive;            /* API_FP_SETUP_ACK_CFM = 0x4424 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the call is made or not. */
} PACKED_STRUCT ApiFpSetupAckCfmType;

/* This mail is used by the CVM to inform the MCU when the handset has
   started alerting / ringing when an incoming call is received. */
typedef struct ApiFpAlertIndType
{
  PrimitiveType Primitive;            /* API_FP_ALERT_IND = 0x4404 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType}[CodecListLength]
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpAlertIndType;

/* This command is used by the MCU to inform the handset when the remote
   part has started the alerting / ringing. */
typedef struct ApiFpAlertReqType
{
  PrimitiveType Primitive;            /* API_FP_ALERT_REQ = 0x4405 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiProgressIndType ProgressInd;       /* Call progress information (e.g. in band
                                           audio). */
  ApiSignalValueType Signal;            /* DECT alert pattern. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType}[CodecListLength]
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpAlertReqType;

/* This mail is used to confirm the API_FP_ALLERT_REQ command. */
typedef struct ApiFpAlertCfmType
{
  PrimitiveType Primitive;            /* API_FP_ALERT_CFM = 0x4406 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpAlertCfmType;

/* This mail is used to inform the MCU when a user has pressed the hook key
   to answer an incoming call on a handset. */
typedef struct ApiFpConnectIndType
{
  PrimitiveType Primitive;            /* API_FP_CONNECT_IND = 0x4407 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
#ifndef CVM480
  uint8 AdpcmChannel;                   /* Adpcm channel used for this call (0-3) */
#endif
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType}[CodecListLength]
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpConnectIndType;

/* This command is used by the MCU to inform the handset whether the call
   was accepted or not. */
typedef struct ApiFpConnectResType
{
  PrimitiveType Primitive;            /* API_FP_CONNECT_RES = 0x4408 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the call was accepted
                                           (AS_SUCCESS) or not (AS_REJECTED). */
} PACKED_STRUCT ApiFpConnectResType;

/* This command is used by the MCU to request the CVM to establish a
   connection to the handset specified. */
typedef struct ApiFpConnectReqType
{
  PrimitiveType Primitive;            /* API_FP_CONNECT_REQ = 0x4409 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType}[CodecListLength]
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpConnectReqType;

/* This mail is used to confirm the API_FP_CONNECT_REQ command. */
typedef struct ApiFpConnectCfmType
{
  PrimitiveType Primitive;            /* API_FP_CONNECT_CFM = 0x440A */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
#ifndef CVM480
  uint8 AdpcmChannel;                   /* Adpcm channel used for this call (0-3) */
#endif
} PACKED_STRUCT ApiFpConnectCfmType;

/* This command is used by the MCU to request the handset to: 
    Start ringing to indicate an incoming call. 
    Play tones, e.g. dial back tone if no in band tones are generated on
   outgoing calls.
    For external calls this message is sent each time a ring is detected on
   the line managed by the MCU. This message will be following the ringer
   cadence on the PSTN line interface if the incoming call is received there. */
typedef struct ApiFpSignalReqType
{
  PrimitiveType Primitive;            /* API_FP_SIGNAL_REQ = 0x440B */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiSignalValueType Signal;            /* Signal / alert type. */
} PACKED_STRUCT ApiFpSignalReqType;

/* This mail is used to confirm the API_FP_SIGNAL_REQ command. */
typedef struct ApiFpSignalCfmType
{
  PrimitiveType Primitive;            /* API_FP_SIGNAL_CFM = 0x440C */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpSignalCfmType;

/* This command is used by the MCU to send the CLIP received on the line to
   a handset. This message is used if the CLIP is received after the
   API_FP_SETUP_REQ has been sent by the MCU. */
typedef struct ApiFpSendClipReqType
{
  PrimitiveType Primitive;            /* API_FP_SEND_CLIP_REQ = 0x440D */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 ClipLength;                     /* CLIP length. The ApiClipDataType is packed in
                                           an IWU when sending it t the handset. It is hence
                                           not understood / handles by all DECT GAP / CAT-iq
                                           compliant handsets. */
  uint8 CallingNumberLength;            /* The length of the number identifying the
                                           calling part. */
  uint8 CallingNameLength;              /* Then length of the name identifying the
                                           calling part. */
  uint8 Data[1];                        /* {ApiClipDataType}[ClipLength],
                                           {ApiCallingNumberType}[CallingNumberLength], 
                                           {ApiCallingNameType}[CallingNameLength]
                                           ClipLength number of bytes holding the CLIP info
                                           ? */
} PACKED_STRUCT ApiFpSendClipReqType;

/* This mail is used to confirm the API_FP_SEND_CLIP_REQ command. */
typedef struct ApiFpSendClipCfmType
{
  PrimitiveType Primitive;            /* API_FP_SEND_CLIP_CFM = 0x440E */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpSendClipCfmType;

/* This mail is used to inform the MCU when a user has pressed the on hook
   key to disconnect an ongoing call or reject an incoming call. */
typedef struct ApiFpReleaseIndType
{
  PrimitiveType Primitive;            /* API_FP_RELEASE_IND = 0x440F */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiReleaseReasonType Reason;          /* Release reason. */
} PACKED_STRUCT ApiFpReleaseIndType;

/* This mail is used by the MCU to inform the handset when the call is
   released. */
typedef struct ApiFpReleaseResType
{
  PrimitiveType Primitive;            /* API_FP_RELEASE_RES = 0x4410 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the call is release or not. */
} PACKED_STRUCT ApiFpReleaseResType;

/* This mail is used by the MCU to terminate a call. */
typedef struct ApiFpReleaseReqType
{
  PrimitiveType Primitive;            /* API_FP_RELEASE_REQ = 0x4411 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiReleaseReasonType Reason;          /* Release reason. */
} PACKED_STRUCT ApiFpReleaseReqType;

/* This mail is used to confirm the API_FP_RELEASE_REQ command. */
typedef struct ApiFpReleaseCfmType
{
  PrimitiveType Primitive;            /* API_FP_RELEASE_CFM = 0x4412 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpReleaseCfmType;

/* This mail is used to inform the MCU when e.g. a connection setup has
   been rejected. */
typedef struct ApiFpRejectIndType
{
  PrimitiveType Primitive;            /* API_FP_REJECT_IND = 0x4413 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiReleaseReasonType Reason;          /* Reject reason. */
} PACKED_STRUCT ApiFpRejectIndType;

/* This mail is used to inform the MCU about digits entered on the handset.
   E.g. when a phone number was entered on the handset before off hook was
   pressed or when key is pressed after the connection has been established. */
typedef struct ApiFpMultikeypadIndType
{
  PrimitiveType Primitive;            /* API_FP_MULTIKEYPAD_IND = 0x4414 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 KeypadLength;                   /* Keypad length (in bytes). */
  uint8 Data[1];                        /* KeypadLength number of bytes. */
} PACKED_STRUCT ApiFpMultikeypadIndType;

/* This mail is used by the MCU to tell the handset that the call is
   delivered to the remote. */
typedef struct ApiFpCallProcReqType
{
  PrimitiveType Primitive;            /* API_FP_CALL_PROC_REQ = 0x4415 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiProgressIndType ProgressInd;       /* Call progress information (e.g. in band
                                           audio) */
  ApiSignalValueType Signal;            /* DECT alert pattern. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType*}[CodecListLength]
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpCallProcReqType;

/* Used by the CVM to confirm the API_FP_CALL_PROC_REQ. */
typedef struct ApiFpCallProcCfmType
{
  PrimitiveType Primitive;            /* API_FP_CALL_PROC_CFM = 0x4416 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpCallProcCfmType;

/* This mail is used by the MCU to send an IWU information element to a
   handset. */
typedef struct ApiFpIwuToIwuReqType
{
  PrimitiveType Primitive;            /* API_FP_IWU_TO_IWU_REQ = 0x4417 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 IwuLength;                      /* The length of the IWU info. */
  uint8 Data[1];                        /* {ApiIwuToIwuType}[IwuLength]
                                           IwuLength number of bytes holding the IWU. */
} PACKED_STRUCT ApiFpIwuToIwuReqType;

/* Used by the CVM to confirm the API_FP_IWU_TO_IWU_REQ. */
typedef struct ApiFpIwuToIwuCfmType
{
  PrimitiveType Primitive;            /* API_FP_IWU_TO_IWU_CFM = 0x4418 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpIwuToIwuCfmType;

/* This mail is used by the CVM to send an IWU information element received
   from a handset to the MCU. */
typedef struct ApiFpIwuToIwuIndType
{
  PrimitiveType Primitive;            /* API_FP_IWU_TO_IWU_IND = 0x4419 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 IwuLength;                      /* The length of the IWU info. */
  uint8 Data[1];                        /* {ApiIwuToIwuType}[IwuLength]
                                           IwuLength number of bytes holding the IWU. */
} PACKED_STRUCT ApiFpIwuToIwuIndType;

/* This mail is used by the MCU to send a proprietary information element
   to a handset. */
typedef struct ApiFpProprietaryReqType
{
  PrimitiveType Primitive;            /* API_FP_PROPRIETARY_REQ = 0x441A */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 ProprietaryLength;              /* The length of the Proprietary info. */
  uint8 Data[1];                        /* {ApiEscapeToProprietaryType}[ ProprietaryLength]
                                           ProprietaryLength number of bytes holding the
                                           proprietary information element. */
} PACKED_STRUCT ApiFpProprietaryReqType;

/* Used by the CVM to confirm the API_FP_PROPRIETARY_REQ. */
typedef struct ApiFpProprietaryCfmType
{
  PrimitiveType Primitive;            /* API_FP_PROPRIETARY_CFM = 0x441B */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpProprietaryCfmType;

/* This mail is used by the CVM to send a proprietary information element
   received from a handset to the MCU. */
typedef struct ApiFpProprietaryIndType
{
  PrimitiveType Primitive;            /* API_FP_PROPRIETARY_IND = 0x441C */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 ProprietaryLength;              /* The length of the Proprietary info. */
  uint8 Data[1];                        /* {ApiEscapeToProprietaryType}[ ProprietaryLength]
                                           ProprietaryLength number of bytes holding the
                                           proprietary information element. */
} PACKED_STRUCT ApiFpProprietaryIndType;

/* This mail is used by the MCU to request a CODEC change for a connection. */
typedef struct ApiFpModifyCodecReqType
{
  PrimitiveType Primitive;            /* API_FP_MODIFY_CODEC_REQ = 0x441D */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType}[CodecListLength]
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpModifyCodecReqType;

/* Used by the CVM to confirm the API_FP_MODIFY_CODEC_REQ. */
typedef struct ApiFpModifyCodecCfmType
{
  PrimitiveType Primitive;            /* API_FP_MODIFY_CODEC_CFM = 0x441E */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpModifyCodecCfmType;

/* This mail is used to inform the MCU when a handset has requested a CODEC
   change for a connection. */
typedef struct ApiFpModifyCodecIndType
{
  PrimitiveType Primitive;            /* API_FP_MODIFY_CODEC_IND = 0x441F */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType}[CodecListLength]
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpModifyCodecIndType;

/* This mail is used by the MCU to accept or reject a code change requested
   by a handset. */
typedef struct ApiFpModifyCodecResType
{
  PrimitiveType Primitive;            /* API_FP_MODIFY_CODEC_RES = 0x4420 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  ApiStatusType Status;                 /* AS_SUCESS if the MCU accepts the CODEC change
                                           request or AS_REJECTED otherwise. */
} PACKED_STRUCT ApiFpModifyCodecResType;

/* This mail is used by the CVM to inform the MCU when the CODEC has been
   changed for a connection. */
typedef struct ApiFpCodecInfoIndType
{
  PrimitiveType Primitive;            /* API_FP_CODEC_INFO_IND = 0x4421 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 CodecListLength;                /* The length of the CODEC list. */
  uint8 Data[1];                        /* {ApiCodecListType}[CodecListLength]
                                           CodecListLength number of bytes holding the
                                           CODEC list. */
} PACKED_STRUCT ApiFpCodecInfoIndType;

/* This mail is used by the CVM to inform the MCU when a CC-INFO message
   including a Called number element has been received from the Handset. This
   will only happen in the ?Overlapped sending? state in CC. */
typedef struct ApiFpCalledNumberIndType
{
  PrimitiveType Primitive;            /* API_FP_CALLED_NUMBER_IND = 0x4422 */
  ApiHandsetIdType HandsetId;           /* The handset id and connection instance. */
  uint8 CalledNumberLength;             /* The length of the called number. */
  uint8 Data[1];                        /* {ApiCalledNumberType}[CalledNumberLength]. */
} PACKED_STRUCT ApiFpCalledNumberIndType;



/****************************************************************************
*                     Enumerations/Type definitions/Structs SITEL PORT - BEGIN
****************************************************************************/
#define SITELPACKED  PACKED_STRUCT
typedef uint8 ApiPcmClkModeType;

typedef enum
{
  HS_NOT_REGISTERED,
  HS_OUT_OF_RANGE,
  F00_NULL,
  F01_CALL_INITIATED,
  F02_OVERLAP_SENDING,
  F03_CALL_PROCEEDING,
  F04_CALL_DELIVERED,
  F06_CALL_PRESENT,//incoming call, before handset rings
  F07_CALL_RECEIVED,//incoming call, while handset is ringing
  F10_ACTIVE,//call established
  F19_RELEASE_PENDING,
  CALL_STATE_MAX
} CallStateType;

/* PCM enable/disable enum. */
typedef enum {
  APE_DISABLE = 0x00, /* The PCM interface is disabled. */
  APE_ENABLED = 0x01, /* The PCM interface is enabled. */
  APE_INVALID = 0xFF  /* [0x02; 0xFF] is invalid. */
} ApiPcmEnableIdType;
typedef uint8 ApiPcmEnableType;

/* PCM master/slave enum. */
typedef enum {
  APM_SLAVE               = 0x00, /* The CVM is slave on the PCM interface. The CVM will
                                     synchronies its own clock to the PCM clock generated by
                                     the PCM master. This requires the PCM master clock to
                                     have an accuracy of 5ppm. */
  APM_MASTER              = 0x01, /* The CVM is master on the POCM interface. */
  APM_SLAVE_NO_CLOCK_SYNC = 0x02, /* The CVM is slave on the PCM interface. The CVM will
                                     not synchronies it own clock, but repeat/remove samples
                                     to compensate for the phase difference between the two
                                     clock domains. */
  APM_INVALID             = 0xFF  /* [0x03; 0xFF] is invalid. */
} ApiPcmMasterSlaveIdType;
typedef uint8 ApiPcmMasterSlaveType;

/* The enum defines the PCM FSC frequencies supported by the CVM. */
typedef enum {
  AP_FSC_FREQ_8KHZ    = 0x00, /* PCM FSC frequency is 8 KHz. */
  AP_FSC_FREQ_16KHZ   = 0x01, /* PCM FSC frequency is 16 KHz. */
  AP_FSC_FREQ_INVALID = 0xFF  /* [0x02; 0xFF] is invalid. */
} ApiPcmFscFreqIdType;
typedef uint8 ApiPcmFscFreqType;

/* This enum defines the FSC pulse length settings supported by the CVM
   when the CVM is master on the PCM interface. */
typedef enum {
  AP_FSC_LENGTH_1       = 0x00, /* The length of PCM FSC pulse is equal to 1 data bit. */
  AP_FSC_LENGTH_8       = 0x01, /* The length of PCM FSC pulse is equal to 8 data bits. */
  AP_FSC_LENGTH_16      = 0x02, /* The length of PCM FSC pulse is equal to 16 data bits. */
  AP_FSC_LENGTH_32      = 0x03, /* The length of PCM FSC pulse is equal to 32 data bits. */
  AP_FSC_LENGTH_INVALID = 0xFF  /* [0x04; 0xFF] is invalid. */
} ApiPcmFscLengthIdType;
typedef uint8 ApiPcmFscLengthType;

/* This enum defines the possible start position of the FCS pulse. */
typedef enum {
  APF_START_1_BIT_BEFORE = 0x00, /* The FSC pulse starts 1 data bit before MSB bit of
                                    the PCM channel 0 data. */
  APF_START_ALIGNED      = 0x01, /* The FSC pulse starts at the same time as the MSB bit
                                    of the PCM channel 0 data. */
  APF_START_INVALID      = 0xFF  /* [0x02; 0xFF] is invalid. */
} ApiPcmFscStartIdType;
typedef uint8 ApiPcmFscStartType;

/* This enum defines the possible PCM_CLK frequencies (1 clock/bit)
   supported by the CVM module when it is master on the PCM interface. */
typedef enum {
  AP_PCM_CLK_1152    = 0x00, /* 1.152 MHz */
  AP_PCM_CLK_2304    = 0x01, /* 2.304 MHz */
  AP_PCM_CLK_4608    = 0x02, /* 4.608 MHz */
  AP_PCM_CLK_INVALID = 0xFF  /* [0x03; 0xFF] is invalid. */
} ApiPcmClkIdType;
typedef uint8 ApiPcmClkType;

/* This enum defines the possible PCM Clock modes. The CVM supports both
   rising and falling edge PCM clock operation. */
typedef enum {
  AP_CLK_MODE_RISING  = 0x00, /* Data on PCM_DI, PCM_DO, PCM_FSC is clocked out on the
                                 rising edge of PCM_CLK and clocked in on the falling edge. */
  AP_CLK_MODE_FALLING = 0x01, /* Data on PCM_DI, PCM_DO, PCM_FSC is clocked out on the
                                 falling edge of PCM_CLK and clocked in on the rising edge. */
  AP_CLK_MODE_INVALID = 0xFF  /* [0x02; 0xFF] is invalid. */
} ApiPcmClkModeIdType;
//vm
//typedef uint8 ApiPcmClkModeType;







typedef struct {
  ApiPcmEnableType        PcmEnable;
  ApiPcmMasterSlaveIdType PcmMasterSlaveId;
  ApiPcmFscFreqType       PcmFscFreq;
  ApiPcmFscLengthType     PcmFscLength;
  ApiPcmFscStartType      PcmFscStart;
  ApiPcmClkType           PcmClk;
  ApiPcmClkModeType       PcmClkMode;
}/*SITELPACKED*/ PcmConfigType;

typedef enum {
  PCM_CFG_FALSE     = 0x00,
  PCM_CFG           = 0x01,
  PCM_CFG_ENABLE    = 0x02,
  PCM_CFG_MODE      = 0x03,
  PCM_CFG_FSC_FREQ  = 0x04,
  PCM_CFG_FSC_LEN   = 0x05,
  PCM_CFG_FSC_START = 0x06,
  PCM_CFG_CLK_FREQ  = 0x07,
  PCM_CFG_INTF_CLK  = 0x08
} PcmCfgModeType;

/* This enum is used to identify the individual PCM data channels [0; 3] */
typedef enum {
  AP_CHANNEL_0       = 0x00, /* PCM channel 0. */
  AP_CHANNEL_1       = 0x01, /* PCM channel 1. */
  AP_CHANNEL_2       = 0x02, /* PCM channel 2. */
  AP_CHANNEL_3       = 0x03, /* PCM channel 3. */
  AP_CHANNEL_INVALID = 0xFF  /* [0x04; 0xFF] is invalid. */
} ApiPcmChannelIdType;
typedef uint8 ApiPcmChannelType;

/* This enum defines the CODEC?s (PCM data format) supported by the CVM on
   the PCM interface. */
typedef enum {
  AP_DATA_FORMAT_NONE         = 0x00, /* No CODEC selected. */
  AP_DATA_FORMAT_LINEAR_8kHz  = 0x01, /* Linear PCM, 8kHz sample rate. Used for
                                         narrowband calls (G.726). */
  AP_DATA_FORMAT_LINEAR_16kHz = 0x02, /* Linear PCM, 16kHz sample rate. Used for
                                         wideband calls (G.722). */
  AP_DATA_FORMAT_G726         = 0x03, /* G.726 - ADPCM, 8 KHz sample rate.
                                         Not implemented. */
  AP_DATA_FORMAT_G722         = 0x04, /* G.722 - Sub-band ADPCM, 16 KHz sample rate.
                                         Not implemented. */
  AP_DATA_FORMAT_G711A        = 0x05, /* G.711 - A-law, 8 KHz sample rate. Used for
                                         narrowband calls (G.726). */
  AP_DATA_FORMAT_G711U        = 0x06, /* G.711 - �-law, 8 KHz sample rate. Used for
                                         narrowband calls (G.726). */
  AP_DATA_FORMAT_CWB_ALAW     = 0x07, /* Compressed wideband using A-law, 16 KHz sample
                                         rate. The 16 bit PCM data is encoded as two 8 bit
                                         audio samples if 8 KHz frame sync is used. Used for
                                         wideband calls (G.722). */
  AP_DATA_FORMAT_CWB_ULAW     = 0x08, /* Compressed wideband using �-law, 16 KHz sample
                                         rate. The 16 bit PCM data is encoded as two 8 bit
                                         audio samples if 8 KHz frame sync is used. Used for
                                         wideband calls (G.722). */
  AP_DATA_FORMAT_INVALID      = 0xFF  /* [0x09; 0xFF] is reserved. */
} ApiPcmDataFormatIdType;
typedef uint8 ApiPcmDataFormatType;


/* This command is used by the MCU to change the data format (CODEC) of one
   of the PCM data channels. It is possible to enable cross codes between the
   CODEC supported by the handset and the data format of the PCM interface.
   See [3] for more info about the possible cross CODEC combinations supported
   by the CVM. */
typedef struct ApiFpSetPcmCodecReqType
{
  PrimitiveType Primitive;            /* API_FP_SET_PCM_CODEC_REQ = 0x4202 */
  ApiPcmChannelType PcmChannel;         /* The PCM channel [0;3] */
  ApiPcmDataFormatType PcmDataFormat;   /* The data format of the PCM channel specified. */
}SITELPACKED ApiFpSetPcmCodecReqType;

/* This mail is used to confirm API_FP_SET_PCM_CODEC_REQ. */
typedef struct ApiFpSetPcmCodecCfmType
{
  PrimitiveType Primitive;            /* API_FP_SET_PCM_CODEC_CFM = 0x4203 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
}SITELPACKED ApiFpSetPcmCodecCfmType;

#if 0
typedef struct _ListEntryType
{
   struct _ListEntryType *Flink;
   struct _ListEntryType *Blink;
} ListEntryType, *pListEntryType;

typedef struct
{
//vm
//  HANDLE hFile;
//  HANDLE hMap;
//  LPVOID pMap;
//  DWORD Size;
	int hFile;
	unsigned char *hMap;
	unsigned char *pMap;	
	uint16 Size;
}SITELPACKED FileMapDataType;

typedef struct
{
  char Filename[256];
  FileMapDataType Map;
} FileDataType;
#endif
typedef struct
{
   PrimitiveType  PrimitiveIdentifier;
   uint8          bKey;
}SITELPACKED KeyMessageReqType;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
}SITELPACKED recSendMailP0Type;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
  uint8         bParm1;
}SITELPACKED recSendMailP1Type;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
  uint8         bParm1;
  uint8         bParm2;
}SITELPACKED recSendMailP2Type;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
  uint8         bParm1;
  uint8         bParm2;
  uint8         bParm3;
}SITELPACKED recSendMailP3Type;

typedef struct
{
  PrimitiveType PrimitiveIdentifier;
  uint8         bData[500];
}SITELPACKED recDataType;

/* The FWU Manager in the CVM uses this mail to indicate the current status
   to the FWU Provider in the MCU. The MCU does not have to handle this mail. */
typedef struct ApiFpFwuStatusIndType
{
  PrimitiveType Primitive;            /* API_FP_FWU_STATUS_IND = 0x4F0C */
  uint8 BusyDeviceNr;                   /* The id of the device being updated currently.
                                           0xFF is used if no device is active. */
  uint8 StatusLength;                   /* Size of Status[]. */
  uint8 Status[1];                     /* The FWU status of each device in the system. */
}SITELPACKED ApiFpFwuStatusIndType;

/* This mail is used by the CVM to confirm the API_FP_FWU_UPDATE_REQ
   command. */
typedef struct ApiFpFwuUpdateCfmType
{
  PrimitiveType Primitive;            /* API_FP_FWU_UPDATE_CFM = 0x4F04 */
  uint8 DeviceNr;                       /* Device number. 0 = CVM  (1..n=handsets) */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
}SITELPACKED ApiFpFwuUpdateCfmType;

/* This enum identifies the FWU modes supported by the CVM firmware. */
typedef enum {
  AFM_FWU         = 0x00, /* The dedicated FWU program in the FLASH. */
  AFM_MAIN        = 0x01, /* The main program in the FLASH. */
  AFM_UNSPECIFIED = 0xFF  /* Invalid. */
} ApiFwuModeIdType;
typedef uint8 ApiFwuModeType;

/* This type is used to specify the range of FWU blocks. */
typedef struct {
  uint32  StartAddr;                    /* The start address of the block. */
  uint32  Size;                         /* The size of the block. */
}SITELPACKED ApiFwuRangeType;

/* This mail is used by the FWU Manager in the CVM to request information
   about the new FW available for the device specified. */
typedef struct ApiFpFwuUpdateIndType
{
  PrimitiveType Primitive;            /* API_FP_FWU_UPDATE_IND = 0x4F05 */
  uint8 DeviceNr;                       /* Device number. 0 = CVM  (1..n=handsets) */
  uint32 DeviceId;                      /* Unique device id. */
  uint32 TargetData;                    /* Information block offset in area. */
  ApiFwuModeType FwuMode;               /* FWU Mode. */
  uint8 LinkDate[5];                    /* The link date of the current FW in the
                                           device. */
  ApiFwuRangeType Range;                /* The start address and the size of the FW in
                                           the target. */
}SITELPACKED ApiFpFwuUpdateIndType;

/* This mail is used by the FWU Manager in the CVM to request the CRC for a
   FW block from the FWU Provider in the MCU. */
typedef struct ApiFpFwuGetCrcIndType
{
  PrimitiveType Primitive;            /* API_FP_FWU_GET_CRC_IND = 0x4F09 */
  uint8 DeviceNr;                       /* Device number. 0 = CVM  (1..n=handsets) */
  uint32 PrvContext;                    /* Provider context; identifies the FWU session. */
  uint32 Address;                       /* Current address. */
  uint32 Size;                          /* Max size of block CRC?ed. */
}SITELPACKED ApiFpFwuGetCrcIndType;

typedef struct _ListEntryType
{
   struct _ListEntryType *Flink;
   struct _ListEntryType *Blink;
} ListEntryType, *pListEntryType;

typedef struct
{
  uint32 InfoOffset;  // FWU_INFO_OFFSET
  uint32 Address;     // E.g. FWU_LOW_AREA_ADR
  uint32 Size;        // E.g. FWU_LOW_AREA_SIZE
  uint32 DeviceId;    // FWU_DEVICEID
  uint8 LinkDate[5];  // Linkdate.
  uint8 reserved[3];
  uint32 ImageBlocks;
}SITELPACKED FwuAreaInfoType;

typedef struct
{
  uint32 Address;
  uint32 Size;
  uint8 Data[1];
  uint8 _align_[3];
}SITELPACKED FwuImageBlockType;

typedef struct
{
  ListEntryType Link;
  FwuAreaInfoType* Area;
  FwuImageBlockType* Blocks;
}SITELPACKED PrvContextType;

typedef struct
{
  uint32 Address;
  uint32 Size;
  uint8* Data;
}SITELPACKED DataBlockType;
//vm 
typedef struct
{
//vm
//  HANDLE hFile;
//  HANDLE hMap;
//  LPVOID pMap;
//  DWORD Size;
	int hFile;
	unsigned char *hMap;
	unsigned char *pMap;	
	uint16 Size;
}SITELPACKED FileMapDataType;

typedef struct
{
  char Filename[256];
  FileMapDataType Map;
} FileDataType;

/* The FWU Manager in the CVM uses this mail to indicate to the FWU
   Provider in the MCU that the FWU session is terminated. The FWU session is
   terminates when the complete FW ha been downloaded to the CVM, but it will
   also be terminated  befor a reset neede to switch from e.g. the mian
   program to the FWU program. Finally the seesion can be terminated as result
   of an error detected by the FWU manager in the CVM module. It is hence
   necessary for the FWU provider to check the link date and the FwuMode in
   the API_FP_FWU_DEVICE_NOTIFY_IND and restart the FWU process if
   needed.Normally the FWU process must be restarted once, that is after the
   CVM module has reset to switch from the mian program to the FWU program in
   the FLASH. */
typedef struct ApiFpFwuCompleteIndType
{
  PrimitiveType Primitive;            /* API_FP_FWU_COMPLETE_IND = 0x4F0B */
  uint32 PrvContext;                    /* Provider context; identifies the FWU session. */
}SITELPACKED ApiFpFwuCompleteIndType;

typedef struct
{
  uint32 StartAdr;
  uint32 Size;
}SITELPACKED FwuRangeType;

typedef union
{
  char IsoCode[2];
  uint16 Value;
} FwuLangIdType;

typedef struct
{
  uint32 DeviceId;
  uint32 FwuTargetData;
  uint8 Mode;
  uint8 LinkDate[5];
  FwuLangIdType LangId;
  FwuRangeType Area;
}SITELPACKED FwuDeviceInfoType;

typedef struct
{
  char Magic[3];  // Characters "FWU".
  uint8 Version;  // FWU_FILEVERSION
  FwuAreaInfoType Low;
  FwuAreaInfoType High;
  uint16 Crc;
  uint8 reserved[2];
}SITELPACKED FwuFileHeaderType;

/* This mail is used by the FWU Manager in the CVM to inform the FWU
   Provider about the devices available for FW download. Only one device, the
   CVM module self, is supported in this implementation. */
typedef struct ApiFpFwuDeviceNotifyIndType
{
  PrimitiveType Primitive;            /* API_FP_FWU_DEVICE_NOTIFY_IND = 0x4F02 */
  uint8 Present;                        /* 0: absent 
                                           1: present */
  uint8 DeviceNr;                       /* Device number. 0 = CVM  (1..n=handsets) */
  uint32 DeviceId;                      /* Unique device id. */
  uint32 TargetData;                    /* Information block offset in area. */
  ApiFwuModeType FwuMode;               /* FWU Mode. */
  uint8 LinkDate[5];                    /* The link date of the current FW in the
                                           device. */
  ApiFwuRangeType Range;                /* The start address and the size of the FW in
                                           the target device. */
}SITELPACKED ApiFpFwuDeviceNotifyIndType;

/* This mail is used by the FWU Provider in the MCU to return FW
   information to the FWU Manager in the CVM. */
typedef struct ApiFpFwuUpdateResType
{
  PrimitiveType Primitive;            /* API_FP_FWU_UPDATE_RES = 0x4F06 */
  uint8 DeviceNr;                       /* Device number. 0 = CVM  (1..n=handsets) */
  uint8 LinkDate[5];                    /* Link date for current area. */
  uint32 PrvContext;                    /* Provider context. Used in all subsequent
                                           mails to identify the FWU update sessions. */
  uint32 RangesCount;                   /* The number of FWU ranges. */
  ApiFwuRangeType Ranges[1];            /* Array holding the address and size of each
                                           block range. The size of Ranges[] is
                                           RangesCount*sizeof (RtxFwuRangeType). */
}SITELPACKED ApiFpFwuUpdateResType;

/* This mail is used by the FWU Manager in the CVM to request a FW block
   from the FWU Provider in the MCU. */
typedef struct ApiFpFwuGetBlockIndType
{
  PrimitiveType Primitive;            /* API_FP_FWU_GET_BLOCK_IND = 0x4F07 */
  uint8 DeviceNr;                       /* Device number. 0 = CVM  (1..n=handsets) */
  uint32 PrvContext;                    /* Provider context; identifies the FWU session. */
  uint32 Address;                       /* Current address. */
  uint32 Size;                          /* Max size of returned block. */
}SITELPACKED ApiFpFwuGetBlockIndType;

/* This mail is used by the FWU Provider in the MCU to return a FW block to
   the FWU Manager in the CVM. */
typedef struct ApiFpFwuGetBlockResType
{
  PrimitiveType Primitive;            /* API_FP_FWU_GET_BLOCK_RES = 0x4F08 */
  uint8 DeviceNr;                       /* Device number. 0 = CVM  (1..n=handsets) */
  uint32 PrvContext;                    /* Provider context; identifies the FWU session. */
  uint32 Address;                       /* Current address. */
  uint32 DataLength;                    /* Size of data. */
  uint8 Data[1];                        /* DataLength bytes of FW data. */
}SITELPACKED ApiFpFwuGetBlockResType;

/* This mail is used by the FWU Provider in the MCU to return the requested
   CRC to the FWU Manager in the CVM. */
typedef struct ApiFpFwuGetCrcResType
{
  PrimitiveType Primitive;            /* API_FP_FWU_GET_CRC_RES = 0x4F0A */
  uint8 DeviceNr;                       /* Device number. 0 = CVM  (1..n=handsets) */
  uint32 PrvContext;                    /* Provider context; identifies the FWU session. */
  uint32 Address;                       /* Address. */
  uint32 Size;                          /* Size of block CRC?ed. */
  uint16 Crc;                           /* CRC. */
}SITELPACKED ApiFpFwuGetCrcResType;

/* This enum defines the DECT types supported by the CVM. */
// typedef enum {
  // AD_EU_DECT = 0x00, /* EU DECT */
  // AD_US_DECT = 0x01, /* US DECT */
  // AD_INVALID = 0xFF  /* [0x02; 0xFF] is invalid. */
// } ApiDectTypeIdType;
// typedef uint8 ApiDectTypeType;

#if 0
/* This mail is used to confirm the API_FP_GET_FW_VERSION_REQ command. */
typedef struct ApiFpGetFwVersionCfmType
{
  PrimitiveType Primitive;            /* API_FP_GET_FW_VERSION_CFM = 0x4003 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint32 VersionHex;                    /* The FW version. */
  uint8 LinkDate[5];                    /* The link date. */
  ApiDectTypeType DectType;             /* Specifies whether this is unit is setup for
                                           EU or US DECT. */
}SITELPACKED ApiFpGetFwVersionCfmType;

typedef struct ApiFpSetAccessCodeReqType
{
  PrimitiveType Primitive;            /* API_FP_SET_ACCESS_CODE_REQ = 0x4008 */
  uint8 Ac[2];                          /* The access code stored as 4 nibbles. E.g.
                                           Access code 1234 is stores as Ac[0]=0x12, Ac[1]=
                                           0x34 */
} SITELPACKED ApiFpSetAccessCodeReqType;

/* This mail is used to confirm the API_FP_SET_ACCESS_CODE_REQ command. */
typedef struct ApiFpSetAccessCodeCfmType
{
  PrimitiveType Primitive;            /* API_FP_SET_ACCESS_CODE_CFM = 0x4009 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
}SITELPACKED ApiFpSetAccessCodeCfmType;

typedef struct ApiFpGetAccessCodeCfmType
{
  PrimitiveType Primitive;            /* API_FP_GET_ACCESS_CODE_CFM = 0x400B */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint8 Ac[2];                          /* The access code stored as 4 nibbles. E.g.
                                           Access code 1234 is stores as Ac[0]=0x12, Ac[1]=
                                           0x34 */
}SITELPACKED ApiFpGetAccessCodeCfmType;
#endif

//PCM DEFINITIONS
/* PCM open drain enable/disable enum. */
typedef enum {
  APO_DISABLED = 0x00, /* The PCM I/O open drain disabled. */
  APO_ENABLED  = 0x01, /* The PCM I/O open drain enabled */
  APO_INVALID  = 0xFF  /* [0x02; 0xFF] is invalid. */
} ApiPcmOdIdType;
typedef uint8 ApiPcmOdType;
/* This command is used by the MCU to initialize the PCM interface. */
typedef struct ApiFpInitPcmReqType
{
  PrimitiveType Primitive;            /* API_FP_INIT_PCM_REQ = 0x4200 */
  ApiPcmEnableType PcmEnable;           /* Enable or disable the PCM interface.
                                           The remaining parameters of this message are
                                           ignored by the CVM if the PCM interface is
                                           disabled. */
  ApiPcmMasterSlaveType PcmMasterSlave; /* Controls whether the CVM is master or slave
                                            on the PCM interface. */
  ApiPcmFscFreqType PcmFscFreq;         /* PCM  FSC frequency; 8 or 16 KHz. */
  ApiPcmFscLengthType PcmFscLength;     /* The length of the FSC pulse. 1, 8, 16 or 32
                                           bits. */
  ApiPcmFscStartType PcmFscStart;       /* The start time of the FSC pulse. Can be 1
                                           data bit before MSB bit or at the same time as
                                           MSB bit of PCM channel 0 data. */
  ApiPcmClkType PcmClk;                 /* The clock frequency generated by the CVM if
                                           the CVM is master on the PCM interface. Ignored
                                           if the CVM is slave. */
  ApiPcmClkModeType PcmClkMode;         /* Controls whether PCM data is clocked out on
                                           raising or falling edge of the PCM_CLK. */
  ApiPcmOdType PcmDoOd;                 /* Controls whether PCM_DOUT is push-pull (0) or
                                           open drain (1). 
                                           Sets DSP_PCM_CTRL_REG.PCM_PPOD to the value
                                           specified by PcmDoOd. Can be used if the I/O
                                           levels (VDDIO) on the PCM interface is 1.8V. Must
                                           be set to 1 if multiple devices are connected to
                                           the PCM bus.
                                           DSP_PCM_CTRL_REG.PCM_PPOD is set to 0 after
                                           reset. */
  ApiPcmOdType PcmOd;                   /* Controls the PCM_DI, PCM_DO, PCM_CLK, and
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
}SITELPACKED ApiFpInitPcmReqType;

/* This mail is used to confirm API_FP_INIT_PCM_REQ. */
typedef struct ApiFpInitPcmCfmType
{
  PrimitiveType Primitive;            /* API_FP_INIT_PCM_CFM = 0x4201 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
}SITELPACKED ApiFpInitPcmCfmType;

//LED DEFINITIONS
/* This enum defines the LED?s supported. */
typedef enum {
  AL_RESERVED      = 0x00, /* Reserved. */
  AL_LED1          = 0x01, /* LED1 */
  AL_LED2_RESERVED = 0x02, /* LED2 can not be used as this pin is connected to the
                              EEPROM. */
  AL_LED3          = 0x03, /* LED3 */
  AL_LED4          = 0x04, /* LED4 */
  AL_INVALID       = 0xFF  /* [0x05; 0xFF] is invalid. */
} ApiLedIdType;
typedef uint8 ApiLedType;

/* This enum defines the LED command supported. */
typedef enum {
  ALC_LED_OFF         = 0x00, /* LED off */
  ALC_LED_ON          = 0x01, /* LED on. */
  ALC_REPEAT_SEQUENCE = 0x02, /* Repeat the LED sequence. */
  ALC_INVALID         = 0xFF  /* [0x03; 0xFF] is invalid. */
} ApiLedCommandCodeIdType;

/* This struct is used to hold one LED command. */
typedef struct 
{
  ApiLedCommandCodeIdType  Command;     /* The LED command */
  uint16  Duration;                     /* The duration in ms for ALC_LED_OFF and
                                           ALC_LED_ON. 0 = no delay/timeout.
                                           The number of times to repeat the sequence for
                                           ALC_REPEAT_SEQUENCE. 0xFFFF = repeat forever. */
}SITELPACKED ApiLedCommandType;

/* This command is used to control the three LED?s (LED1, LED3, and LED4)
   on the CVM. The CVM can store on command sequence for each of the LED?s. */
typedef struct ApiFpSetLedReqType
{
  PrimitiveType Primitive;            /* API_FP_SET_LED_REQ = 0x400C */
  ApiLedType LED;                       /* The LED for which this command applies. */
  uint8 CommandsCount;                  /* The number of LED commands in the Commands[]
                                           parameter. */
  ApiLedCommandType Commands[1];        /* NoCommands number of LED commands. */
}SITELPACKED ApiFpSetLedReqType;

/* This mail is used to confirm the API_FP_SET_LED_REQ command. */
typedef struct ApiFpSetLedCfmType
{
  PrimitiveType Primitive;            /* API_FP_SET_LED_CFM = 0x400D */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
}SITELPACKED ApiFpSetLedCfmType;

typedef struct
{
  uint8 Present        : 1;
  uint8 Connected2Line : 1;
  uint8 UnUsed         : 6;
  ApiCallClassType CallClass;
  uint8 DestinationId;
  CallStateType State;
  uint8 LineId;
  uint8 ProposedCodecListLength;
  ApiCodecListType *ProposedCodecListPtr;
  ApiBasicServiceType BasicService; // used for internal call only
  //Added for SC1445x 
  uint8 RequestedCodec; // codec requested by the peer. Used in incoming call
}PACKED_STRUCT CallStateInfoType;
// const char* ApiPcmEnableIdName[]= {
  // "APE_DISABLE",
  // "APE_ENABLED"
// };

// const char* ApiPcmMasterSlaveIdName[] = {
  // "APM_SLAVE",
  // "APM_MASTER",
  // "APM_SLAVE_NO_CLOCK_SYNC"
// };

// const char* ApiPcmFscFreqIdName[] = {
  // "AP_FSC_FREQ_8KHZ",
  // "AP_FSC_FREQ_16KHZ"
// };

// const char* ApiPcmFscLengthIdName[] = {
  // "AP_FSC_LENGTH_1",
  // "AP_FSC_LENGTH_8",
  // "AP_FSC_LENGTH_16",
  // "AP_FSC_LENGTH_32"
// };

// const char* ApiPcmFscStartIdName[] = {
  // "APF_START_1_BIT_BEFORE",
  // "APF_START_ALIGNED"
// };

// const char* ApiPcmClkIdName[] = {
  // "AP_PCM_CLK_1152",
  // "AP_PCM_CLK_2304",
  // "AP_PCM_CLK_4608"
// };

// const char* ApiPcmClkModeIdName[] = {
  // "AP_CLK_MODE_RISING",
  // "AP_CLK_MODE_FALLING"
// };

// const char* ApiCodecTypeName[] = {
  // "ACT_NONE",
  // "ACT_USER_SPECIFIC_32",
  // "ACT_G726",
  // "ACT_G722",
  // "ACT_G711A",
  // "ACT_G711U",
  // "ACT_G7291",
  // "ACT_MP4_32",
  // "ACT_MP4_64",
  // "ACT_USER_SPECIFIC_64",
  // "ACT_INVALID"
// };
/* This command is used to modify a register in the SC14480 chip on the CVM
   module. Please see [2] for a description of the registers in the SC14480
   chip. This is implemented as: *(uint16) RegisterAddress = ((*(uint16)
   RegisterAddress) & ~Mask) | (Data & Mask) */
typedef struct ApiFpSetRegisterReqType
{
  PrimitiveType Primitive;            /* API_FP_SET_REGISTER_REQ = 0x400E */
  uint32 RegisterAddress;               /* The address of the register. */
  uint16 Data;                          /* The value that should be written to the
                                           register. */
  uint16 Mask;                          /* Mask that defines which bits to modify in the
                                           register. */
}SITELPACKED ApiFpSetRegisterReqType;

/* This mail is used to confirm the API_FP_SET_REGISTER_REQ command. */
typedef struct ApiFpSetRegisterCfmType
{
  PrimitiveType Primitive;            /* API_FP_SET_REGISTER_CFM = 0x400F */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
}SITELPACKED ApiFpSetRegisterCfmType;

/* This command is used to read the value of a register in the SC14480 chip
   on the CVM module. Please see [2] for a description of the registers in the
   SC14480 chip. */
typedef struct ApiFpGetRegisterReqType
{
  PrimitiveType Primitive;            /* API_FP_GET_REGISTER_REQ = 0x4010 */
  uint32 RegisterAddress;               /* The address of the register. */
}SITELPACKED ApiFpGetRegisterReqType;

/* This mail is used to confirm the API_FP_GET_REGISTER_REQ command. */
typedef struct ApiFpGetRegisterCfmType
{
  PrimitiveType Primitive;            /* API_FP_GET_REGISTER_CFM = 0x4011 */
  ApiStatusType Status;                 /* Indicates whether the command succeeded or
                                           not. */
  uint32 RegisterAddress;               /* The address of the register. */
  uint16 Data;                          /* The data read from the register. */
}SITELPACKED ApiFpGetRegisterCfmType;


/****************************************************************************
*                     Enumerations/Type definitions/Structs SITEL PORT - END
****************************************************************************/


typedef union
{
  PrimitiveType Primitive;
  ApiFpInitReqType ApiFpInitReq;
  ApiFpInitCfmType ApiFpInitCfm;
  ApiFpNvsUpdateIndType ApiFpNvsUpdateInd;
  ApiFpNvsUpdateResType ApiFpNvsUpdateRes;
  ApiFpResetReqType ApiFpResetReq;
  ApiFpResetIndType ApiFpResetInd;
  ApiFpGetFwVersionReqType ApiFpGetFwVersionReq;
  ApiFpGetFwVersionCfmType ApiFpGetFwVersionCfm;
  ApiFpGetIdReqType ApiFpGetIdReq;
  ApiFpGetIdCfmType ApiFpGetIdCfm;
  ApiFpSetAccessCodeReqType ApiFpSetAccessCodeReq;
  ApiFpSetAccessCodeCfmType ApiFpSetAccessCodeCfm;
  ApiFpGetAccessCodeReqType ApiFpGetAccessCodeReq;
  ApiFpGetAccessCodeCfmType ApiFpGetAccessCodeCfm;
  ApiFpSetEepromReqType ApiFpSetEepromReq;
  ApiFpSetEepromCfmType ApiFpSetEepromCfm;
  ApiFpGetEepromReqType ApiFpGetEepromReq;
  ApiFpGetEepromCfmType ApiFpGetEepromCfm;
  ApiFpGetRegistrationCountReqType ApiFpGetRegistrationCountReq;
  ApiFpGetRegistrationCountCfmType ApiFpGetRegistrationCountCfm;
  ApiFpDeleteRegistrationReqType ApiFpDeleteRegistrationReq;
  ApiFpDeleteRegistrationCfmType ApiFpDeleteRegistrationCfm;
  ApiFpRegistrationDeletedIndType ApiFpRegistrationDeletedInd;
  ApiFpSetRegistrationModeReqType ApiFpSetRegistrationModeReq;
  ApiFpSetRegistrationModeCfmType ApiFpSetRegistrationModeCfm;
  ApiFpRegistrationCompleteIndType ApiFpRegistrationCompleteInd;
  ApiFpHandsetPresentIndType ApiFpHandsetPresentInd;
  ApiFpGetHandsetIpuiReqType ApiFpGetHandsetIpuiReq;
  ApiFpGetHandsetIpuiCfmType ApiFpGetHandsetIpuiCfm;
  ApiFpSetupIndType ApiFpSetupInd;
  ApiFpSetupResType ApiFpSetupRes;
  ApiFpSetupReqType ApiFpSetupReq;
  ApiFpSetupCfmType ApiFpSetupCfm;
  ApiFpSetupAckReqType ApiFpSetupAckReq;
  ApiFpSetupAckCfmType ApiFpSetupAckCfm;
  ApiFpAlertIndType ApiFpAlertInd;
  ApiFpAlertReqType ApiFpAlertReq;
  ApiFpAlertCfmType ApiFpAlertCfm;
  ApiFpConnectIndType ApiFpConnectInd;
  ApiFpConnectResType ApiFpConnectRes;
  ApiFpConnectReqType ApiFpConnectReq;
  ApiFpConnectCfmType ApiFpConnectCfm;
  ApiFpSignalReqType ApiFpSignalReq;
  ApiFpSignalCfmType ApiFpSignalCfm;
  ApiFpSendClipReqType ApiFpSendClipReq;
  ApiFpSendClipCfmType ApiFpSendClipCfm;
  ApiFpReleaseIndType ApiFpReleaseInd;
  ApiFpReleaseResType ApiFpReleaseRes;
  ApiFpReleaseReqType ApiFpReleaseReq;
  ApiFpReleaseCfmType ApiFpReleaseCfm;
  ApiFpRejectIndType ApiFpRejectInd;
  ApiFpMultikeypadIndType ApiFpMultikeypadInd;
  ApiFpCallProcReqType ApiFpCallProcReq;
  ApiFpCallProcCfmType ApiFpCallProcCfm;
  ApiFpIwuToIwuReqType ApiFpIwuToIwuReq;
  ApiFpIwuToIwuCfmType ApiFpIwuToIwuCfm;
  ApiFpIwuToIwuIndType ApiFpIwuToIwuInd;
  ApiFpProprietaryReqType ApiFpProprietaryReq;
  ApiFpProprietaryCfmType ApiFpProprietaryCfm;
  ApiFpProprietaryIndType ApiFpProprietaryInd;
  ApiFpModifyCodecReqType ApiFpModifyCodecReq;
  ApiFpModifyCodecCfmType ApiFpModifyCodecCfm;
  ApiFpModifyCodecIndType ApiFpModifyCodecInd;
  ApiFpModifyCodecResType ApiFpModifyCodecRes;
  ApiFpCodecInfoIndType ApiFpCodecInfoInd;
  ApiFpCalledNumberIndType ApiFpCalledNumberInd;
#if 1 //cvm
  ApiFpFwuDeviceNotifyIndType ApiFpFwuDeviceNotifyInd;
  ApiFpFwuUpdateCfmType ApiFpFwuUpdateCfm;
  ApiFpFwuStatusIndType ApiFpFwuStatusInd;
  ApiFpFwuUpdateIndType ApiFpFwuUpdateInd;
  ApiFpFwuGetCrcIndType ApiFpFwuGetCrcInd;  
  ApiFpSetLedReqType ApiFpSetLedReq;
  ApiFpSetLedCfmType ApiFpSetLedCfm;
  ApiFpInitPcmReqType ApiFpInitPcmReq;
  ApiFpInitPcmCfmType ApiFpInitPcmCfm;  
  ApiFpSetPcmCodecReqType ApiFpSetPcmCodecReq;
  ApiFpSetPcmCodecCfmType ApiFpSetPcmCodecCfm;  
  ApiFpSetRegisterReqType ApiFpSetRegisterReq;
  ApiFpSetRegisterCfmType ApiFpSetRegisterCfm;
  ApiFpGetRegisterReqType ApiFpGetRegisterReq;
  ApiFpGetRegisterCfmType ApiFpGetRegisterCfm;  
#endif  
} PACKED_STRUCT Sip450ApiMailType;

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/




#ifdef __cplusplus
}
#endif
#endif /*ISIP450API_H */


