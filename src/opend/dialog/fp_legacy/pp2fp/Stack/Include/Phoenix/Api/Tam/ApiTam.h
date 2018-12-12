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
* Definition of the ApiTam interface.
*/


#ifndef APITAM_H
#define APITAM_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! Include of API configuration header. */
#include <Api/ApiCfg.h>
#include <Phoenix/Api/Types/ApiTypes.h>
#include <Phoenix/Api/Cc/ApiCc.h>

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

/* Global mail primitives:
  API_TAM_PLAY_ICM_REQ = 0x4500,
  API_TAM_PLAY_ICM_CFM= 0x4501,
  API_TAM_ICM_SEARCH_REQ = 0x4502,
  API_TAM_ICM_SEARCH_CFM = 0x4503,
  API_TAM_ICM_STATUS_REQ = 0x4504,
  API_TAM_ICM_STATUS_CFM = 0x4505,
  API_TAM_DELETE_ICM_REQ= 0x4506,
  API_TAM_DELETE_ICM_CFM = 0x4507,
  API_TAM_STOP_REQ = 0x4508,
  API_TAM_STOP_CFM = 0x4509,
  API_TAM_MARK_CURRENT_ICM_REQ = 0x450A,
  API_TAM_MARK_CURRENT_ICM_CFM = 0x450B,
  API_TAM_STATUS_IND = 0x450C,
  API_TAM_RECORD_MEMO_REQ = 0x450D,
  API_TAM_RECORD_MEMO_CFM = 0x450E,
  API_TAM_RECORD_VOICETAG_REQ = 0x450F,
  API_TAM_RECORD_VOICETAG_CFM = 0x4510,
  API_TAM_PLAY_VOICEPROMPT_REQ = 0x4511,
  API_TAM_PLAY_VOICEPROMPT_CFM= 0x4512,
  API_TAM_PLAY_VOICETAG_REQ = 0x4513,
  API_TAM_PLAY_VOICETAG_CFM = 0x4514,
  API_TAM_DELETE_VOICETAG_REQ = 0x4515,
  API_TAM_DELETE_VOICETAG_CFM = 0x4516,
  API_TAM_SET_SETTINGS_REQ = 0x4517,
  API_TAM_SET_SETTINGS_CFM = 0x4518,
  API_TAM_GET_SETTINGS_REQ = 0x4519,
  API_TAM_GET_SETTINGS_CFM = 0x451A,
  API_TAM_SET_SYSTEM_SETTINGS_REQ = 0x451B,
  API_TAM_SET_SYSTEM_SETTINGS_CFM = 0x451C,
  API_TAM_GET_SYSTEM_SETTINGS_REQ = 0x451D,
  API_TAM_GET_SYSTEM_SETTINGS_CFM = 0x451E,
  API_TAM_READ_DATA_REQ= 0x451F,
  API_TAM_READ_DATA_CFM = 0x4520,
  API_TAM_WRITE_DATA_REQ = 0x4521,
  API_TAM_WRITE_DATA_CFM= 0x4522,
  API_TAM_DELETE_ALL_ICMS_REQ= 0x4523,
  API_TAM_DELETE_ALL_ICMS_CFM= 0x4524,
  API_TAM_SETUP_REQ = 0x4525,
  API_TAM_RELEASE_REQ = 0x4526,
  API_TAM_RELEASE_CFM = 0x4527	,
  API_TAM_CONNECT_IND = 0x4528,
  API_TAM_REJECT_IND = 0x4529,
The global mail primitives MUST be defined in Global.h! */


/*! This type is used to return error info to the client. */
typedef enum RSENUMTAG(ApiTamErrorType)
{
  API_TAM_ERROR_NO_ERROR          = 0x00, /*!< Operation successful. */
  API_TAM_ERROR_NONEXISTING       = 0x01, /*!< The specified msg does not exist. */
  API_TAM_ERROR_EXISTING          = 0x02, /*!< The specified msg does exist. */
  API_TAM_ERROR_ILLEGAL_OPERATION = 0x03, /*!< The attempted operation is not legal in
                                             the current context. */
  API_TAM_ERROR_TAM_WAS_FULL      = 0x04, /*!< The Tam was full before the operation
                                             could start. */
  API_TAM_ERROR_TAM_BECAME_FULL   = 0x05, /*!< The Tam became full during the operation. */
  API_TAM_ERROR_TIMEOUT           = 0x06, /*!< The operation timed out. */
} RSENUM8(ApiTamErrorType);

/*! Generic type to hold message numbers. */
typedef rsuint8 ApiTamMsgNoType;


typedef enum RSENUMTAG(ApiTamIcmAgeType)
{
  API_TAM_ICM_NEW = 0x00, /*!< Search for new ICMs. */
  API_TAM_ICM_OLD = 0x01, /*!< Search for old ICMs. */
  API_TAM_ICM_ALL = 0x02  /*!< Search for all ICMs. */
} RSENUM8(ApiTamIcmAgeType);


typedef enum RSENUMTAG(ApiTamIcmDirType)
{
  API_TAM_DIR_FIRST    = 0x00, /*!< Search for the first ICM. */
  API_TAM_DIR_NEXT     = 0x01, /*!< Search for the next ICM. */
  API_TAM_DIR_PREVIOUS = 0x02, /*!< Search for the previous ICM. */
  API_TAM_DIR_LAST     = 0x03  /*!< Search for the last ICM. */
} RSENUM8(ApiTamIcmDirType);


typedef enum RSENUMTAG(ApiTamAnswerModeType)
{
  API_TAM_ANSWER_MODE_ANSWER_ONLY       = 0x00, /*!< Answer incoming call only. */
  API_TAM_ANSWER_MODE_ANSWER_AND_RECORD = 0x01, /*!< Answer incoming call and record
                                                   ICM. */
  API_TAM_ANSWER_MODE_MAX               = 0x02  /*!<  */
} RSENUM8(ApiTamAnswerModeType);


typedef enum RSENUMTAG(ApiTamOgmType)
{
  API_TAM_OGM_PREDEFINED = 0x00, /*!< Predefined outgoing message. */
  API_TAM_OGM_PERSONAL   = 0x01, /*!< Personal outgoing message. */
  API_TAM_OGM_MAX        = 0x02  /*!<  */
} RSENUM8(ApiTamOgmType);


typedef struct ApiTamIcmStatusType
{
  rsbool  New;
  rsuint32  TimeStamp;
  //SwNwkClipDataType  Clip;
} ApiTamIcmStatusType;


typedef struct ApiTamSignalCfgType
{
  rsuint16  SignalOnMin;
  rsuint16  SignalOnMax;
  rsuint16  SignalOffMin;
  rsuint16  SignalOffMax;
  rsuint8  SignalRepetitions;
} ApiTamSignalCfgType;


typedef struct ApiTamSettingsType
{
  rsbool  TamOn;
  rsbool  BsScreeningOn;
  rsbool  HsScreeningOn;
  rsbool  RemoteAccessOn;
  rsuint8  RingDelay;
  ApiTamAnswerModeType  AnswerMode;
  ApiTamOgmType  OgmAnswerOnly;
  ApiTamOgmType  OgmAnswerAndRec;
  rsuint8  Language;
  rsuint16  IcmMaxLength;
} ApiTamSettingsType;


typedef struct ApiTamSystemSettingsType 
{
  rsuint16  IcmTailcutTime;
  rsuint16  IcmTailcutSilenceTime;
  rsuint16  VoicetagMaxLength;
  rsuint16  SilenceTimeout;
  rsuint16  RemoteAccessTimeout;
  ApiTamSignalCfgType  SignalDtmfToneCfg;
  ApiTamSignalCfgType  SignalLongDtmfToneCfg;
  ApiTamSignalCfgType  SignalDialToneCfg;
  ApiTamSignalCfgType  SignalBusyToneCfg;
  ApiTamSignalCfgType  SignalCNGToneCfg;
} ApiTamSystemSettingsType;


typedef enum RSENUMTAG(ApiTamDataTaskErrorType)
{
  API_TAM_DATA_TASK_NO_ERROR = 0x00, /*!<  */
  API_TAM_DATA_TASK_ERROR    = 0x01  /*!<  */
} RSENUM8(ApiTamDataTaskErrorType);

/*! Unique command ID?s for all messages to be sent between TAM Client
   (PP/FP) and TAM server */
typedef enum RSENUMTAG(ApiTamCmdType)
{
  TAM_CMD_PLAY_ICM_REQ            = 0x00, /*!<  */
  TAM_CMD_PLAY_ICM_CFM            = 0x01, /*!<  */
  TAM_CMD_ICM_SEARCH_REQ          = 0x02, /*!<  */
  TAM_CMD_ICM_SEARCH_CFM          = 0x03, /*!<  */
  TAM_CMD_ICM_STATUS_REQ          = 0x04, /*!<  */
  TAM_CMD_ICM_STATUS_CFM          = 0x05, /*!<  */
  TAM_CMD_DELETE_ICM_REQ          = 0x06, /*!<  */
  TAM_CMD_DELETE_ICM_CFM          = 0x07, /*!<  */
  TAM_CMD_STOP_REQ                = 0x08, /*!<  */
  TAM_CMD_STOP_CFM                = 0x09, /*!<  */
  TAM_CMD_MARK_CURRENT_ICM_REQ    = 0x0A, /*!<  */
  TAM_CMD_MARK_CURRENT_ICM_CFM    = 0x0B, /*!<  */
  TAM_CMD_STATUS_IND              = 0x0C, /*!<  */
  TAM_CMD_RECORD_MEMO_REQ         = 0x0D, /*!<  */
  TAM_CMD_RECORD_MEMO_CFM         = 0x0E, /*!<  */
  TAM_CMD_RECORD_VOICETAG_REQ     = 0x0F, /*!<  */
  TAM_CMD_RECORD_VOICETAG_CFM     = 0x10, /*!<  */
  TAM_CMD_PLAY_VOICEPROMPT_REQ    = 0x11, /*!<  */
  TAM_CMD_PLAY_VOICEPROMPT_CFM    = 0x12, /*!<  */
  TAM_CMD_PLAY_VOICETAG_REQ       = 0x13, /*!<  */
  TAM_CMD_PLAY_VOICETAG_CFM       = 0x14, /*!<  */
  TAM_CMD_DELETE_VOICETAG_REQ     = 0x15, /*!<  */
  TAM_CMD_DELETE_VOICETAG_CFM     = 0x16, /*!<  */
  TAM_CMD_SET_SETTINGS_REQ        = 0x17, /*!<  */
  TAM_CMD_SET_SETTINGS_CFM        = 0x18, /*!<  */
  TAM_CMD_GET_SETTINGS_REQ        = 0x19, /*!<  */
  TAM_CMD_GET_SETTINGS_CFM        = 0x1A, /*!<  */
  TAM_CMD_SET_SYSTEM_SETTINGS_REQ = 0x1B, /*!<  */
  TAM_CMD_SET_SYSTEM_SETTINGS_CFM = 0x1C, /*!<  */
  TAM_CMD_GET_SYSTEM_SETTINGS_REQ = 0x1D, /*!<  */
  TAM_CMD_GET_SYSTEM_SETTINGS_CFM = 0x1E, /*!<  */
  TAM_CMD_READ_DATA_REQ           = 0x1F, /*!<  */
  TAM_CMD_READ_DATA_CFM           = 0x20, /*!<  */
  TAM_CMD_WRITE_DATA_REQ          = 0x21, /*!<  */
  TAM_CMD_WRITE_DATA_CFM          = 0x22, /*!<  */
  TAM_CMD_DELETE_ALL_ICMS_REQ     = 0x23, /*!<  */
  TAM_CMD_DELETE_ALL_ICMS_CFM     = 0x24, /*!<  */
  TAM_CMD_SETUP_REQ               = 0x25, /*!<  */
  TAM_CMD_RELEASE_REQ             = 0x26, /*!<  */
  TAM_CMD_RELEASE_CFM             = 0x27, /*!<  */
  TAM_CMD_CONNECT_IND             = 0x28  /*!<  */
} RSENUM8(ApiTamCmdType);



/*! Mail without parameters. */
typedef struct ApitamEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApitamEmptySignalType;

/*!  */
typedef struct ApiTamPlayIcmReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_PLAY_ICM_REQ = 0x4500 */
  ApiTamMsgNoType IcmNo;
  rsbool MarkAsOld;
} ApiTamPlayIcmReqType;

/*!  */
typedef struct ApiTamPlayIcmCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_PLAY_ICM_CFM= 0x4501 */
  ApiTamErrorType ErrorCode;
} ApiTamPlayIcmCfmType;

/*! . */
typedef struct ApiTamIcmSearchReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_ICM_SEARCH_REQ = 0x4502 */
  ApiTamMsgNoType IcmNo;
  ApiTamIcmAgeType IcmAge;
  ApiTamIcmDirType IcmDir;
} ApiTamIcmSearchReqType;

/*!  */
typedef struct ApiTamIcmSearchCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_ICM_SEARCH_CFM = 0x4503 */
  ApiTamErrorType ErrorCode;
  ApiTamMsgNoType IcmNo;
} ApiTamIcmSearchCfmType;

/*!  */
typedef struct ApiTamIcmStatusReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_ICM_STATUS_REQ = 0x4504 */
  ApiTamMsgNoType IcmNo;
} ApiTamIcmStatusReqType;

/*!  */
typedef struct ApiTamIcmStatusCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_ICM_STATUS_CFM = 0x4505 */
  ApiTamErrorType ErrorCode;
  ApiTamIcmStatusType Status;
} ApiTamIcmStatusCfmType;

/*!  */
typedef struct ApiTamDeleteIcmReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_DELETE_ICM_REQ= 0x4506 */
  ApiTamMsgNoType IcmNo;
} ApiTamDeleteIcmReqType;

/*!  */
typedef struct ApiTamDeleteIcmCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_DELETE_ICM_CFM = 0x4507 */
  ApiTamErrorType ErrorCode;
} ApiTamDeleteIcmCfmType;

/*!  */
typedef ApitamEmptySignalType ApiTamStopReqType;

/*! . */
typedef struct ApiTamStopCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_STOP_CFM = 0x4509 */
  ApiTamErrorType ErrorCode;
} ApiTamStopCfmType;

/*! . */
typedef struct ApiTamMarkCurrentIcmReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_MARK_CURRENT_ICM_REQ = 0x450A */
  ApiTamMsgNoType IcmNo;
} ApiTamMarkCurrentIcmReqType;

/*! . */
typedef struct ApiTamMarkCurrentIcmCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_MARK_CURRENT_ICM_CFM = 0x450B */
  ApiTamErrorType ErrorCode;
} ApiTamMarkCurrentIcmCfmType;

/*!  */
typedef struct ApiTamStatusIndType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_STATUS_IND = 0x450C */
  rsbool TamOn;
  rsbool TamFull;
  rsbool NewMsgs;
} ApiTamStatusIndType;

/*!  */
typedef struct ApiTamRecordMemoReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_RECORD_MEMO_REQ = 0x450D */
  rsuint32 Timestamp;
} ApiTamRecordMemoReqType;

/*!  */
typedef struct ApiTamRecordMemoCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_RECORD_MEMO_CFM = 0x450E */
  ApiTamErrorType ErrorCode;
} ApiTamRecordMemoCfmType;

/*!  */
typedef struct ApiTamRecordVoicetagReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_RECORD_VOICETAG_REQ = 0x450F */
  rsuint32 Timestamp;
  ApiTamMsgNoType VoiceTag;
  rsbool OverWrite;
} ApiTamRecordVoicetagReqType;

/*!  */
typedef struct ApiTamRecordVoicetagCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_RECORD_VOICETAG_CFM = 0x4510 */
  ApiTamErrorType ErrorCode;
} ApiTamRecordVoicetagCfmType;

/*!  */
typedef struct ApiTamPlayVoicepromptReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_PLAY_VOICEPROMPT_REQ = 0x4511 */
  ApiTamMsgNoType VoicePrompt;          /*!< TAM_VOICEPROMPT_ANSWER_ONLY
                                           TAM_VOICEPROMPT_ANSWER_AND_RECORD */
} ApiTamPlayVoicepromptReqType;

/*!  */
typedef struct ApiTamPlayVoicepromptCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_PLAY_VOICEPROMPT_CFM= 0x4512 */
  ApiTamErrorType ErrorCode;
} ApiTamPlayVoicepromptCfmType;

/*!  */
typedef struct ApiTamPlayVoicetagReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_PLAY_VOICETAG_REQ = 0x4513 */
  ApiTamMsgNoType Voicetag;
} ApiTamPlayVoicetagReqType;

/*!  */
typedef struct ApiTamPlayVoicetagCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_PLAY_VOICETAG_CFM = 0x4514 */
  ApiTamErrorType ErrorCode;
} ApiTamPlayVoicetagCfmType;

/*!  */
typedef struct ApiTamDeleteVoicetagReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_DELETE_VOICETAG_REQ = 0x4515 */
  ApiTamMsgNoType VoiceTag;
} ApiTamDeleteVoicetagReqType;

/*!  */
typedef struct ApiTamDeleteVoicetagCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_DELETE_VOICETAG_CFM = 0x4516 */
  ApiTamErrorType ErrorCode;
} ApiTamDeleteVoicetagCfmType;

/*!  */
typedef struct ApiTamSetSettingsReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_SET_SETTINGS_REQ = 0x4517 */
  ApiTamSettingsType TamSettings;
} ApiTamSetSettingsReqType;

/*!  */
typedef struct ApiTamSetSettingsCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_SET_SETTINGS_CFM = 0x4518 */
  ApiTamErrorType ErrorCode;
  ApiTamSettingsType TamSettings;
} ApiTamSetSettingsCfmType;

/*!  */
typedef ApitamEmptySignalType ApiTamGetSettingsReqType;

/*!  */
typedef struct ApiTamGetSettingsCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_GET_SETTINGS_CFM = 0x451A */
  ApiTamErrorType ErrorCode;
  ApiTamSettingsType TamSettings;
} ApiTamGetSettingsCfmType;

/*!  */
typedef struct ApiTamSetSystemSettingsReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_SET_SYSTEM_SETTINGS_REQ = 0x451B */
  ApiTamSystemSettingsType TamSystemSettings;
} ApiTamSetSystemSettingsReqType;

/*!  */
typedef struct ApiTamSetSystemSettingsCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_SET_SYSTEM_SETTINGS_CFM = 0x451C */
  ApiTamErrorType ErrorCode;
  ApiTamSystemSettingsType TamSystemSettings;
} ApiTamSetSystemSettingsCfmType;

/*!  */
typedef ApitamEmptySignalType ApiTamGetSystemSettingsReqType;

/*!  */
typedef struct ApiTamGetSystemSettingsCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_GET_SYSTEM_SETTINGS_CFM = 0x451E */
  ApiTamErrorType ErrorCode;
  ApiTamSystemSettingsType TamSystemSettings;
} ApiTamGetSystemSettingsCfmType;

/*!  */
typedef ApitamEmptySignalType ApiTamReadDataReqType;

/*!  */
typedef struct ApiTamReadDataCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_READ_DATA_CFM = 0x4520 */
  ApiTamDataTaskErrorType Result;
  rsuint8 Length;
  rsuint8 Data[1];
} ApiTamReadDataCfmType;

/*!  */
typedef struct ApiTamWriteDataReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_WRITE_DATA_REQ = 0x4521 */
  rsuint8 Length;
  rsuint8 Data[1];
} ApiTamWriteDataReqType;

/*!  */
typedef struct ApiTamWriteDataCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_WRITE_DATA_CFM= 0x4522 */
  ApiTamDataTaskErrorType Result;
} ApiTamWriteDataCfmType;

/*!  */
typedef struct ApiTamDeleteAllIcmsReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_DELETE_ALL_ICMS_REQ= 0x4523 */
  ApiTamIcmAgeType IcmAge;
} ApiTamDeleteAllIcmsReqType;

/*!  */
typedef struct ApiTamDeleteAllIcmsCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_DELETE_ALL_ICMS_CFM= 0x4524 */
  ApiTamErrorType ErrorCode;
} ApiTamDeleteAllIcmsCfmType;

/*!  */
typedef struct ApiTamSetupReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_SETUP_REQ = 0x4525 */
  ApiCcConEiType	 MmiConEi;
} ApiTamSetupReqType;

/*!  */
typedef struct ApiTamReleaseReqType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_RELEASE_REQ = 0x4526 */
  ApiCcConEiType	 MmiConEi;
  ApiCcReleaseReasonType Reason;
} ApiTamReleaseReqType;

/*! This mail is used indicate to the MMI a confirmation of the
   API_TAM_RELEASE_REQ command. */
typedef struct ApiTamReleaseCfmType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_RELEASE_CFM = 0x4527	 */
  ApiCcConEiType	 MmiConEi;             /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
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
                                           [API_IE_RP_TAM] */
} ApiTamReleaseCfmType;

/*! This mail is used to inform the MCU when the TAM_CLIENT is connected to
   the TAM. */
typedef ApitamEmptySignalType ApiTamConnectIndType;

/*! This mail is used to inform the MCU when the TAM_CLIENT is connected to
   the TAM */
typedef struct ApiTamRejectIndType
{
  RosPrimitiveType Primitive;            /*!< API_TAM_REJECT_IND = 0x4529 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  ApiCcReleaseReasonType Reason;        /*!< DECT reason code */
} ApiTamRejectIndType;

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
* FUNCTION:      SendApiTamPlayIcmReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_PLAY_ICM_REQ = 0x4500
****************************************************************************/
void SendApiTamPlayIcmReq ( RosTaskIdType Src,
                            ApiTamMsgNoType IcmNo,           /*!<  */
                            rsbool MarkAsOld);               /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamIcmSearchReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_ICM_SEARCH_REQ = 0x4502
****************************************************************************/
void SendApiTamIcmSearchReq ( RosTaskIdType Src,
                              ApiTamMsgNoType IcmNo,         /*!<  */
                              ApiTamIcmAgeType IcmAge,       /*!<  */
                              ApiTamIcmDirType IcmDir);      /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamIcmStatusReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_ICM_STATUS_REQ = 0x4504
****************************************************************************/
void SendApiTamIcmStatusReq ( RosTaskIdType Src,
                              ApiTamMsgNoType IcmNo);        /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamDeleteIcmReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_DELETE_ICM_REQ= 0x4506
****************************************************************************/
void SendApiTamDeleteIcmReq ( RosTaskIdType Src,
                              ApiTamMsgNoType IcmNo);        /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamStopReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_STOP_REQ = 0x4508
****************************************************************************/
void SendApiTamStopReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiTamMarkCurrentIcmReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_MARK_CURRENT_ICM_REQ = 0x450A
****************************************************************************/
void SendApiTamMarkCurrentIcmReq ( RosTaskIdType Src,
                                   ApiTamMsgNoType IcmNo);   /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamRecordMemoReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_RECORD_MEMO_REQ = 0x450D
****************************************************************************/
void SendApiTamRecordMemoReq ( RosTaskIdType Src,
                               rsuint32 Timestamp);          /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamRecordVoicetagReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_RECORD_VOICETAG_REQ = 0x450F
****************************************************************************/
void SendApiTamRecordVoicetagReq ( RosTaskIdType Src,
                                   rsuint32 Timestamp,       /*!<  */
                                   ApiTamMsgNoType VoiceTag,  /*!<  */
                                   rsbool OverWrite);        /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamPlayVoicepromptReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_PLAY_VOICEPROMPT_REQ = 0x4511
****************************************************************************/
void SendApiTamPlayVoicepromptReq ( RosTaskIdType Src,
                                    ApiTamMsgNoType VoicePrompt);
                                                             /*!< TAM_VOICEPROMPT_ANSWER_ONLY
                                                                TAM_VOICEPROMPT_ANSWER_AND_R
                                                                ECORD */

/****************************************************************************
* FUNCTION:      SendApiTamPlayVoicetagReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_PLAY_VOICETAG_REQ = 0x4513
****************************************************************************/
void SendApiTamPlayVoicetagReq ( RosTaskIdType Src,
                                 ApiTamMsgNoType Voicetag);  /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamDeleteVoicetagReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_DELETE_VOICETAG_REQ = 0x4515
****************************************************************************/
void SendApiTamDeleteVoicetagReq ( RosTaskIdType Src,
                                   ApiTamMsgNoType VoiceTag);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamSetSettingsReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_SET_SETTINGS_REQ = 0x4517
****************************************************************************/
void SendApiTamSetSettingsReq ( RosTaskIdType Src,
                                ApiTamSettingsType TamSettings);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamGetSettingsReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_GET_SETTINGS_REQ = 0x4519
****************************************************************************/
void SendApiTamGetSettingsReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiTamSetSystemSettingsReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_SET_SYSTEM_SETTINGS_REQ = 0x451B
****************************************************************************/
void SendApiTamSetSystemSettingsReq ( RosTaskIdType Src,
                                      ApiTamSystemSettingsType TamSystemSettings);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamGetSystemSettingsReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_GET_SYSTEM_SETTINGS_REQ = 0x451D
****************************************************************************/
void SendApiTamGetSystemSettingsReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiTamReadDataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_READ_DATA_REQ= 0x451F
****************************************************************************/
void SendApiTamReadDataReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiTamWriteDataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_WRITE_DATA_REQ = 0x4521
****************************************************************************/
void SendApiTamWriteDataReq ( RosTaskIdType Src,
                              rsuint8 Length,                /*!<  */
                              rsuint8 Data[1]);              /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamDeleteAllIcmsReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_DELETE_ALL_ICMS_REQ= 0x4523
****************************************************************************/
void SendApiTamDeleteAllIcmsReq ( RosTaskIdType Src,
                                  ApiTamIcmAgeType IcmAge);  /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamSetupReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_SETUP_REQ = 0x4525
****************************************************************************/
void SendApiTamSetupReq ( RosTaskIdType Src,
                          ApiCcConEiType	 MmiConEi);         /*!<  */

/****************************************************************************
* FUNCTION:      SendApiTamReleaseReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_TAM_RELEASE_REQ = 0x4526
****************************************************************************/
void SendApiTamReleaseReq ( RosTaskIdType Src,
                            ApiCcConEiType	 MmiConEi,        /*!<  */
                            ApiCcReleaseReasonType Reason);  /*!<  */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APITAM_H */


