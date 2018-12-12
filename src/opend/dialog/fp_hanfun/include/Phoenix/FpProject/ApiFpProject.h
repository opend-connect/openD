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
* Definition of the ApiFpProject interface.
*/


#ifndef APIFPPROJECT_H
#define APIFPPROJECT_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
//#include <Api/ApiCfg.h>
/*! The following API files must be included. */
#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/
#define LS_NO_LINES 9//8 lines + 1 for intercom 4
/*! The size of the NVS data, that must be stored by the application */
#define API_FP_LINUX_NVS_SIZE 0x1000

/*! The maximum mail size that the application can ever receive or send,
   with the exception of API_FP_INIT_REQ. The size of the buffer used for all
   reads on /dev/dect must be at least this. (This value is not valid for
   /dev/dectdbg) */
#define API_FP_LINUX_MAX_MAIL_SIZE 0x3400

/*! Number of DECT voice channels */
#define API_FP_LINUX_VOICE_CHANNELS 4

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  //#pragma pack(push,1)
#endif

/* Mail primitives:
  API_FP_SET_LED_REQ = 0x400C,
  API_FP_SET_LED_CFM = 0x400D,
  API_FP_SET_REGISTER_REQ = 0x400E,
  API_FP_SET_REGISTER_CFM = 0x400F,
  API_FP_GET_REGISTER_REQ = 0x4010,
  API_FP_GET_REGISTER_CFM = 0x4011,
  API_FP_SET_EEPROM_REQ = 0x4012,
  API_FP_SET_EEPROM_CFM = 0x4013,
  API_FP_GET_EEPROM_REQ = 0x4014,
  API_FP_GET_EEPROM_CFM = 0x4015,
  API_FP_GET_CODEC_LIST_REQ = 0x4016,
  API_FP_GET_CODEC_LIST_CFM = 0x4017,
End of mail primitives. */

//typedef enum
//{
//  LERR_ISR_TOO_SLOW = 0, /*!< ISR was serviced too slow */
//} RSENUM8(ApiLinuxErrorCodeType);


/*! This enum defines the LED?s supported. */
typedef enum RSENUMTAG(ApiLedIdType)
{
  AL_RESERVED      = 0x00, /*!< Reserved. */
  AL_LED1          = 0x01, /*!< LED1 */
  AL_LED2_RESERVED = 0x02, /*!< LED2 can not be used as this pin is connected to the
                              EEPROM. */
  AL_LED3          = 0x03, /*!< LED3 */
  AL_LED4          = 0x04, /*!< LED4 */
  AL_INVALID       = 0xFF  /*!< [0x05; 0xFF] is invalid. */
} RSENUM8(ApiLedIdType);
typedef rsuint8 ApiLedType;

/*! This enum defines the LED command supported. */
typedef enum RSENUMTAG(ApiLedCommandCodeIdType)
{
  ALC_LED_OFF         = 0x00, /*!< LED off */
  ALC_LED_ON          = 0x01, /*!< LED on. */
  ALC_REPEAT_SEQUENCE = 0x02, /*!< Repeat the LED sequence. */
  ALC_INVALID         = 0xFF  /*!< [0x03; 0xFF] is invalid. */
} RSENUM8(ApiLedCommandCodeIdType);
typedef rsuint8 ApiLedCommandCodeType;

/*! This struct is used to hold one LED command. */
typedef struct 
{
  ApiLedCommandCodeIdType Command;      /*!< The LED command */
  rsuint16 Duration;                    /*!< The duration in ms for ALC_LED_OFF and
                                           ALC_LED_ON. 0 = no delay/timeout.
                                           The number of times to repeat the sequence for
                                           ALC_REPEAT_SEQUENCE. 0xFFFF = repeat forever. */
} PACKED_STRUCT ApiLedCommandType;

/*! This enum defines the string character formats that can be used to
   encode strings exchanged between the MCU and the handsets. */
typedef enum RSENUMTAG(ApiUsedCharIdType)
{
  AUC_DEFAULT = 0x00, /*!< Strings are encoded as described in the used IE type. */
  AUC_IA5CHAR = 0x01, /*!< Strings are encoded as IA5 character table. */
  AUC_XCHAR8  = 0x02, /*!< Strings are encoded as 8 bit XCHARTYPE. Terminating zero must
                         be included in the string, and included in the string length. */
  AUC_XCHAR16 = 0x03, /*!< Strings are encoded as 16 bit XCHARTYPE. Terminating zero
                         must be included, and included in the string length. */
  AUC_INVALID = 0xFF  /*!< [0x04; 0xFF] is reserved. */
} RSENUM8(ApiUsedCharIdType);
typedef rsuint8 ApiUsedCharType;

/*! This enum defines the CLIP reason codes supported. */
typedef enum RSENUMTAG(ApiClipReasonIdType)
{
  ACRT_NO_REASON                   = 0x00, /*!<  */
  ACRT_CLIP_UNAVAILABLE            = 0x01, /*!<  */
  ACRT_CLIP_PRIVATE                = 0x02, /*!<  */
  ACRT_CLIP_OUT_OF_AREA            = 0x03, /*!<  */
  ACRT_CLIP_CHECKSUM_ERROR         = 0x04, /*!<  */
  ACRT_CLIP_TIMEOUT                = 0x05, /*!<  */
  ACRT_CLIP_TIME_DATE_FORMAT_ERROR = 0x06, /*!<  */
  ACRT_CLIP_NO_DATA                = 0x07, /*!< No CLIP data detected */
  ACTR_CLIP_COIN_PHONE_CALL        = 0x08, /*!< Taiwan addition */
  ACTR_CLIP_INTERNATIONAL          = 0x09, /*!< Taiwan addition */
  ACRT_INVALID                     = 0xFF  /*!< Unspecified */
} RSENUM8(ApiClipReasonIdType);
typedef rsuint8 ApiClipReasonType;

/*! This byte contains the number of waiting messages. */
typedef rsuint8 ApiNmssType;            /*!< 0 indicates 0 messages. */


typedef enum RSENUMTAG(ApiVmwiIdType)
{
  AV_OFF = 0,    /*!< Deactivation (indicator off) */
  AV_ON  = 0xFF, /*!< Activation (indicator on) */
} RSENUM8(ApiVmwiIdType);
typedef rsuint8 ApiVmwiType;

/*! This type is used to store all CLIP related information. */
typedef struct 
{
  ApiClipReasonType ReasonCode;         /*!< Reason code */
  ApiClipReasonType ReasonName;         /*!< Reason code */
  ApiUsedCharType UsedChar;             /*!< This describes the encoding of the strings
                                           in name and number. */
  rsuint8 NumberLen;                    /*!< Number length */
  rsuint8 NameLen;                      /*!< Name Length */
  rsuint8 TimeDateLen;                  /*!< Length of time date */
  rsuint8 VmwiLen;                      /*!< Length of message waiting indicator */
  rsuint8 NmssLen;                      /*!< Lengt of SS element. */
  rsuint8 Data[1];                      /*!< {ApiCallingNumberType}[NumberLen],
                                           {ApiCallingNameType}[NameLen],
                                           {ApiTimeDateType}[TimeDateLen],
                                           {ApiVmwiType}[VmwiLen],
                                           {ApiNmssType}[NmssLen]. */
} PACKED_STRUCT ApiClipDataType;

/*! This type is used to store all CLIP related information. */
typedef enum RSENUMTAG(ApiRequestedCodeListType)
{
  CommonCodecListFromLocation = 0x00, /*!< This codec list is saved in Eeprom during
                                         registration/location */
  LastCommonCodecList         = 0x01, /*!< Latest received codec from HS */
  CodecForCurrentCall         = 0x02  /*!< Used codec for current call, if no active
                                         call, the codec from last call is received. */
} RSENUM8(ApiRequestedCodeListType);


/*! Mail without parameters. */
typedef struct ApifpprojectEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApifpprojectEmptySignalType;

/*! This mail is used by the application to start the DECT driver. The mail
   contains the NVS data stored by the DECT driver during earlier uses (See
   API_FP_NVS_UPDATE_IND). If this is the first time the DECT driver is used,
   then use API_FP_INIT_DEFAULT_REQ instead of this. The DECT driver will
   return an API_FP_INIT_CFM in response.
    This mail must be sent as the first after driver load. Until it is sent
   all other mails will be ignored. It must only be sent once. */
typedef struct ApiFpLinuxInitReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LINUX_INIT_REQ = 0x4700 */
  rsuint8 NvsData[API_FP_LINUX_NVS_SIZE]; /*!< NVS Data. Omit this to start with a new
                                              defaulted EEPROM. */
} PACKED_STRUCT ApiFpLinuxInitReqType;

/*! This mail is used by the application to start the DECT driver when no
   NVS data exists, i.e. the first time the driver is loaded onto a new piece
   of hardware. The initialization is identical to API_FP_INIT_REQ, except
   that no NVS data is included in this mail, and instead the driver will
   perform an NVS factory default programming. Expect to receive many
   API_FP_NVS_UPDATE_IND. After the default programming the DECT driver will
   return an API_FP_INIT_CFM in response. */
typedef ApifpprojectEmptySignalType ApiFpLinuxInitDefaultReqType;

/*! Confirmation for API_FP_INIT_REQ.
    The mail contains information about the addresses of the voice channel
   buffers used by the device driver. */
typedef struct ApiFpLinuxInitCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LINUX_INIT_CFM = 0x4702 */
  rsuint32 RxVoiceBufferAddr[API_FP_LINUX_VOICE_CHANNELS]; /*!< DECT receive buffer
                                                               addresses  (i.e. SIP transmit
                                                               direction). TBD: Not sure
                                                               whether these will be needed. */
  rsuint32 TxVoiceBufferAddr[API_FP_LINUX_VOICE_CHANNELS]; /*!< DECT transmit buffer
                                                               addresses  (i.e. SIP receive 
                                                               direction) . TBD: Not sure
                                                               whether these will be needed. */
} PACKED_STRUCT ApiFpLinuxInitCfmType;

/*! This mail is sent from the DECT driver, when changes have to be stored
   in NVS. The application must save the data in order to supply it the next
   time the DECT driver is initialized with API_FP_INIT_REQ. There is no
   confirmation mail. 
     */
typedef struct ApiFpLinuxNvsUpdateIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LINUX_NVS_UPDATE_IND = 0x4703 */
  rsuint16 NvsOffset;                   /*!< Offset into NVS to store this data. */
  rsuint16 NvsDataLength;               /*!< Length of NvsData field. */
  rsuint8 NvsData[1];                   /*!< Variable length data contains length bytes
                                           of NVS data to be stored. */
} PACKED_STRUCT ApiFpLinuxNvsUpdateIndType;

/*! This mail is sent from the DECT driver, in case of critical internal
   errors. See the error code for additional information 
     */
typedef struct ApiFpLinuxInternalErrorType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LINUX_INTERNAL_ERROR = 0x4704 */
  ApiLinuxErrorCodeType ErrorCode;      /*!< Error code. */
}PACKED_STRUCT ApiFpLinuxInternalErrorType;

/*! This command is used to control the three LED?s (LED1, LED3, and LED4)
   on the CVM. The CVM can store on command sequence for each of the LED?s. */
typedef struct ApiFpSetLedReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_LED_REQ = 0x400C */
  ApiLedType LED;                       /*!< The LED for which this command applies. */
  rsuint8 CommandsCount;                /*!< The number of LED commands in the
                                           Commands[] parameter. */
  ApiLedCommandType Commands[1];        /*!< NoCommands number of LED commands. */
} PACKED_STRUCT ApiFpSetLedReqType;

/*! This mail is used to confirm the API_FP_SET_LED_REQ command. */
typedef struct ApiFpSetLedCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_LED_CFM = 0x400D */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpSetLedCfmType;

/*! This command is used to modify a register in the SC14480 chip on the
   CVM module. Please see [1] for a description of the registers in the
   SC14480 chip. This is implemented as: *(rsuint16) RegisterAddress =
   ((*(rsuint16) RegisterAddress)  &amp; ~Mask) | (Data &amp; Mask) */
typedef struct ApiFpSetRegisterReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_REGISTER_REQ = 0x400E */
  rsuint32 RegisterAddress;             /*!< The address of the register. */
  rsuint16 Data;                        /*!< The value that should be written to the
                                           register. */
  rsuint16 Mask;                        /*!< Mask that defines which bits to modify in
                                           the register. */
} PACKED_STRUCT ApiFpSetRegisterReqType;

/*! This mail is used to confirm the API_FP_SET_REGISTER_REQ command. */
typedef struct ApiFpSetRegisterCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_REGISTER_CFM = 0x400F */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpSetRegisterCfmType;

/*! This command is used to read the value of a register in the SC14480
   chip on the CVM module. Please see [2] for a description of the registers
   in the SC14480 chip. */
typedef struct ApiFpGetRegisterReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_REGISTER_REQ = 0x4010 */
  rsuint32 RegisterAddress;             /*!< The address of the register. */
} PACKED_STRUCT ApiFpGetRegisterReqType;

/*! This mail is used to confirm the API_FP_GET_REGISTER_REQ command. */
typedef struct ApiFpGetRegisterCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_REGISTER_CFM = 0x4011 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint32 RegisterAddress;             /*!< The address of the register. */
  rsuint16 Data;                        /*!< The data read from the register. */
} PACKED_STRUCT ApiFpGetRegisterCfmType;

/*! This command is used to modify the content of the EEPROM. This should
   be used with caution! */
typedef struct ApiFpSetEepromReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_EEPROM_REQ = 0x4012 */
  rsuint16 Address;                     /*!< Offset in the EEPROM */
  rsuint8 DataLength;                   /*!< The number of bytes to write to the EEPROM. */
  rsuint8 Data[1];                      /*!< The data to be written to the EEPROM. */
} PACKED_STRUCT ApiFpSetEepromReqType;

/*! This mail is used to confirm the API_FP_SET_EEPROM_REQ command. */
typedef struct ApiFpSetEepromCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_EEPROM_CFM = 0x4013 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint16 Address;                     /*!< Offset in the EEPROM */
  rsuint8 DataLength;                   /*!< The number of bytes written to the EEPROM. */
} PACKED_STRUCT ApiFpSetEepromCfmType;

/*! This command is used to read data from the EEPROM. */
typedef struct ApiFpGetEepromReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_EEPROM_REQ = 0x4014 */
  rsuint16 Address;                     /*!< Offset in the EEPROM. */
  rsuint8 DataLength;                   /*!< The number of bytes to read from the
                                           EEPROM. */
} PACKED_STRUCT ApiFpGetEepromReqType;

/*! This mail is used to confirm the API_FP_GET_EEPROM_REQ command. */
typedef struct ApiFpGetEepromCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_EEPROM_CFM = 0x4015 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint16 Address;                     /*!< Offset in the EEPROM. */
  rsuint8 DataLength;                   /*!< The number of bytes to read from the
                                           EEPROM. */
  rsuint8 Data[1];                      /*!< The data read from the EEPROM. */
} PACKED_STRUCT ApiFpGetEepromCfmType;

/*! This mail is used to get codec list for a specific HS.  The codec list
   can either be the one save in Eeprom, during registration/location, or it
   can be the latest received from the HS, or finally it can be the currently
   used during call. This is indicated in ApiRequestCodeList */
typedef struct ApiFpGetCodecListReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_CODEC_LIST_REQ = 0x4016 */
  ApiTerminalIdType HandsetId;          /*!< Indicates which HS. */
  ApiRequestedCodeListType ApiRequestCodeList; /*!< Indicates which codec list to
                                                   request. */
} PACKED_STRUCT ApiFpGetCodecListReqType;

/*! This mail is used to confirm the API_FP_GET_CODECLIST_REQ command. This
   mail will always hold an infoelement containing a codec list. The codec
   list can either be the one save in Eeprom, during registration/location, or
   it can be the latest received from the HS, or finally it can be the
   currently used during call. This is indicated in ApiRequestCodeList */
typedef struct ApiFpGetCodecListCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_CODEC_LIST_CFM = 0x4017 */
  ApiTerminalIdType HandsetId;          /*!< Indicates which HS. */
  ApiRequestedCodeListType ApiRequestCodeList; /*!< Indicates which codec list to
                                                   request. */
  rsuint16 InfoElementLength;           /*!< The length in bytes of the info element
                                           that should be appended to the info element
                                           memory block (**IeBlockPtr). */
  rsuint8 InfoElement[1];               /*!< Pointer to the info element data that
                                           should be appended.
                                           This will always hold
                                           [API_IE_CODEC_LIST] */
} PACKED_STRUCT ApiFpGetCodecListCfmType;

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
* FUNCTION:      SendApiFpLinuxInitReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LINUX_INIT_REQ = 0x4700
****************************************************************************/
void SendApiFpLinuxInitReq ( RosTaskIdType Src,
                             rsuint8 NvsData[API_FP_LINUX_NVS_SIZE]);
                                                             /*!< NVS Data. Omit this to
                                                                start with a new defaulted
                                                                EEPROM. */

/****************************************************************************
* FUNCTION:      SendApiFpLinuxInitDefaultReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LINUX_INIT_DEFAULT_REQ = 0x4701
****************************************************************************/
void SendApiFpLinuxInitDefaultReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpLinuxInitCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LINUX_INIT_CFM = 0x4702
****************************************************************************/
void SendApiFpLinuxInitCfm ( RosTaskIdType Src,
                             rsuint32 RxVoiceBufferAddr[API_FP_LINUX_VOICE_CHANNELS],
                                                             /*!< DECT receive buffer
                                                                addresses  (i.e. SIP
                                                                transmit direction). TBD:
                                                                Not sure whether these will
                                                                be needed. */
                             rsuint32 TxVoiceBufferAddr[API_FP_LINUX_VOICE_CHANNELS]);
                                                             /*!< DECT transmit buffer
                                                                addresses  (i.e. SIP receive
                                                                 direction) . TBD: Not sure
                                                                whether these will be
                                                                needed. */

/****************************************************************************
* FUNCTION:      SendApiFpLinuxNvsUpdateInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LINUX_NVS_UPDATE_IND = 0x4703
****************************************************************************/
void SendApiFpLinuxNvsUpdateInd ( RosTaskIdType Src,
                                  rsuint16 NvsOffset,        /*!< Offset into NVS to
                                                                store this data. */
                                  rsuint16 NvsDataLength,    /*!< Length of NvsData
                                                                field. */
                                  rsuint8 NvsData[1]);       /*!< Variable length data
                                                                contains length bytes of NVS
                                                                data to be stored. */

/****************************************************************************
* FUNCTION:      SendApiFpLinuxInternalError
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LINUX_INTERNAL_ERROR = 0x4704
****************************************************************************/
void SendApiFpLinuxInternalError ( RosTaskIdType Src,
                                   ApiLinuxErrorCodeType ErrorCode);
                                                             /*!< Error code. */

/****************************************************************************
* FUNCTION:      SendApiFpSetLedReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_LED_REQ = 0x400C
****************************************************************************/
void SendApiFpSetLedReq ( RosTaskIdType Src,
                          ApiLedType LED,                    /*!< The LED for which this
                                                                command applies. */
                          rsuint8 CommandsCount,             /*!< The number of LED
                                                                commands in the Commands[]
                                                                parameter. */
                          ApiLedCommandType Commands[1]);    /*!< NoCommands number of
                                                                LED commands. */

/****************************************************************************
* FUNCTION:      SendApiFpSetRegisterReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_REGISTER_REQ = 0x400E
****************************************************************************/
void SendApiFpSetRegisterReq ( RosTaskIdType Src,
                               rsuint32 RegisterAddress,     /*!< The address of the
                                                                register. */
                               rsuint16 Data,                /*!< The value that should
                                                                be written to the register. */
                               rsuint16 Mask);               /*!< Mask that defines
                                                                which bits to modify in the
                                                                register. */

/****************************************************************************
* FUNCTION:      SendApiFpGetRegisterReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_REGISTER_REQ = 0x4010
****************************************************************************/
void SendApiFpGetRegisterReq ( RosTaskIdType Src,
                               rsuint32 RegisterAddress);    /*!< The address of the
                                                                register. */

/****************************************************************************
* FUNCTION:      SendApiFpSetEepromReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_EEPROM_REQ = 0x4012
****************************************************************************/
void SendApiFpSetEepromReq ( RosTaskIdType Src,
                             rsuint16 Address,               /*!< Offset in the EEPROM */
                             rsuint8 DataLength,             /*!< The number of bytes to
                                                                write to the EEPROM. */
                             rsuint8 Data[1]);               /*!< The data to be written
                                                                to the EEPROM. */

/****************************************************************************
* FUNCTION:      SendApiFpGetEepromReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_EEPROM_REQ = 0x4014
****************************************************************************/
void SendApiFpGetEepromReq ( RosTaskIdType Src,
                             rsuint16 Address,               /*!< Offset in the EEPROM. */
                             rsuint8 DataLength);            /*!< The number of bytes to
                                                                read from the EEPROM. */

/****************************************************************************
* FUNCTION:      SendApiFpGetCodecListReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_CODEC_LIST_REQ = 0x4016
****************************************************************************/
void SendApiFpGetCodecListReq ( RosTaskIdType Src,
                                ApiTerminalIdType HandsetId,  /*!< Indicates which HS. */
                                ApiRequestedCodeListType ApiRequestCodeList);
                                                             /*!< Indicates which codec
                                                                list to request. */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPPROJECT_H */


