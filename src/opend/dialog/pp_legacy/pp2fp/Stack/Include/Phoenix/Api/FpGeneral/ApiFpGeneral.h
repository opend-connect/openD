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
* Definition of the ApiFpGeneral interface.
*/


#ifndef APIFPGENERAL_H
#define APIFPGENERAL_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API header files must be included. */
#include <Api/ApiCfg.h> /* API configuration */
/*! The following API header files must be included. */
#include <Phoenix/Api/Types/ApiTypes.h> /* General types used. */

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! Macros. */
#define API_FP_TIMEDATE_SYNC_ALL_HS 0xFFFF
#ifdef AUTOTEST
  #include <Tools/AutoTest/AutoTest.h>
#endif

/*! This type describes features available in this API. */
#define API_FP_EXTENDED_TERMINAL_ID_SUPPORT 0x01

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#ifdef RTX_OS_VERSION
  #include <RS/Common/RsPushPack1.h>
#elif (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_FP_RESET_REQ = 0x4000,
  API_FP_RESET_IND = 0x4001,
  API_FP_GET_FW_VERSION_REQ = 0x4002,
  API_FP_GET_FW_VERSION_CFM = 0x4003,
  API_FP_SET_CRADLE_STATUS_REQ = 0x407F,
  API_FP_CRADLE_DETECT_REQ = 0x4080,
  API_FP_CRADLE_DETECT_IND = 0x4081,
  API_FP_SET_TIME_REQ = 0x4082,
  API_FP_SET_TIME_CFM = 0x4083,
  API_FP_GET_TIME_REQ = 0x4084,
  API_FP_GET_TIME_CFM = 0x4085,
  API_FP_SET_TIME_IND = 0x4086,
  API_FP_SYNC_TIME_REQ = 0x4087,
  API_FP_SET_FEATURES_REQ = 0x40A0,
  API_FP_SET_FEATURES_CFM = 0x40A1,
  API_FP_GET_FEATURES_REQ = 0x40A2,
  API_FP_GET_FEATURES_CFM = 0x40A3,
End of mail primitives. */



/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiFpFeatureType;


/*! Mail without parameters. */
typedef struct ApifpgeneralEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApifpgeneralEmptySignalType;

/*! This mail is used by the MMI to request the API to do a SW reset. The
   API will reinitialize the unit and return an API_PP_RESET_IND when the API
   is ready to accept commands from the MMI again. */
typedef ApifpgeneralEmptySignalType ApiFpResetReqType;

/*! This mail is used to indicate that the device has been started (after
   power on or reset). This can be used by a host to detect reset of the
   device running the API if the host (MMI/application) and the API (the DECT
   system) are running on different devices. */
typedef struct ApiFpResetIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_RESET_IND = 0x4001 */
  RsStatusType Status;                  /*!< Indicates whether the device is ready or
                                           not. */
} ApiFpResetIndType;

/*! This command is used by the MMI to get the Firmware version of the
   unit. */
typedef ApifpgeneralEmptySignalType ApiFpGetFwVersionReqType;

/*! This mail is used to confirm the API_FP_GET_FW_VERSION_REQ command. */
typedef struct ApiFpGetFwVersionCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_FW_VERSION_CFM = 0x4003 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint32 VersionHex;                  /*!< The Firmware version. */
  rsuint8 LinkDate[5];                  /*!< The link date. */
  ApiDectTypeType DectType;             /*!< Specifies whether this is unit is setup for
                                           EU or US DECT. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< Possible Info elements:
                                           [API_IE_AVAILABLE_APIS] 
                                           [API_IE_LINE_ID] */
} ApiFpGetFwVersionCfmType;

/*! This mail is used by the MMI to notify the FP if a PP is placed in the cradle
    It is automatically send by the API at every change or instantly if
   requested by the API_FP_CRADLE_DETECT_REQ
    
    *This can be used if an external cradle is featured on the the host
   in-stead of  on the FP.
    **The status is to be used to tell the FP if ECO mode can be enabled */
typedef struct ApiFpSetCradleStatusReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_CRADLE_STATUS_REQ = 0x407F */
  ApiCradleStatusType ApiCradleStatus;  /*!< The current status of the cradle */
} ApiFpSetCradleStatusReqType;

/*! This mail is used by the MMI to force the API to reply instantly with
   the cradle status (API_FP_CRADLE_DETECT_IND).
    
    *This command is only valid if the FP features a cradle in the HW */
typedef ApifpgeneralEmptySignalType ApiFpCradleDetectReqType;

/*! This mail is used by the API to indicate the cradle status to the MMI.
   (If a PP is placed in the FP cradle)
    It is automatically send by the API at every change or instantly if
   requested by the API_FP_CRADLE_DETECT_REQ
    
    *This command is only valid if the FP features a cradle in the HW */
typedef struct ApiFpCradleDetectIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CRADLE_DETECT_IND = 0x4081 */
  ApiCradleStatusType ApiCradleStatus;  /*!< The current status of the cradle */
} ApiFpCradleDetectIndType;

/*! This mail is by the MMI to set real time clock to a specific timestamp,
   then distribute it to the registered PP's. */
typedef struct ApiFpSetTimeReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_TIME_REQ = 0x4082 */
  ApiTimeDateCodingType Coding;         /*!< Describes if only date, time, or both
                                           should be set. */
  ApiTimeDateInterpretationType Interpretation; /*!< Describes the time stamp
                                                    interpretation */
  ApiTimeDateCodeType ApiTimeDateCode;  /*!< The time stamp */
} ApiFpSetTimeReqType;

/*! This mail is used by the API to confirm the API_FP_SET_TIME_REQ
   command. */
typedef struct ApiFpSetTimeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_TIME_CFM = 0x4083 */
  RsStatusType Status;                  /*!< Indicates whether the API_FP_SET_TIME_REQ
                                           was executed correctly or not.
                                           RsStatusType is defined in the ROS */
} ApiFpSetTimeCfmType;

/*! This mail is by the MMI to request the API to return the current
   timestamp. */
typedef ApifpgeneralEmptySignalType ApiFpGetTimeReqType;

/*! This mail is used by the API to confirm the API_FP_GET_TIME_REQ command.
    It holds the current time stamp. */
typedef struct ApiFpGetTimeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_TIME_CFM = 0x4085 */
  ApiTimeDateCodeType ApiTimeDateCode;  /*!< The time stamp */
} ApiFpGetTimeCfmType;

/*! This mail is used by the API to inform the MMI that a PP wish to change
   the time and date. */
typedef struct ApiFpSetTimeIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_TIME_IND = 0x4086 */
  ApiTerminalIdType TerminalId;         /*!< Id of the handset which request to change
                                           the timedate. [1:N] */
  ApiTimeDateCodingType Coding;         /*!< Describes if only date, time, or both
                                           should be set. */
  ApiTimeDateInterpretationType Interpretation; /*!< Describes the time stamp
                                                    interpretation */
  ApiTimeDateCodeType ApiTimeDateCode;  /*!< The time stamp */
} ApiFpSetTimeIndType;

/*! This mail is by the MMI to synchronize time and date on a single PP. */
typedef struct ApiFpSyncTimeReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SYNC_TIME_REQ = 0x4087 */
  ApiTerminalIdType TerminalId;         /*!< Id of the handset which shall receive the
                                           timedate update.
                                           If set to API_FP_TIMEDATE_SYNC_ALL_HS all
                                           attached handsets will receive a TimeDate update. */
} ApiFpSyncTimeReqType;

/*! This command is used to enable/disable features in the FpGeneral API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiFpSetFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_FEATURES_REQ = 0x40A0 */
  ApiFpFeatureType ApiFpFeature;        /*!< Requested features */
} ApiFpSetFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiFpSetFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_FEATURES_CFM = 0x40A1 */
  RsStatusType Status;
  ApiFpFeatureType ApiFpFeature;        /*!< Supported features */
} ApiFpSetFeaturesCfmType;

/*! This command is used request the current feature settings. */
typedef ApifpgeneralEmptySignalType ApiFpGetFeaturesReqType;

/*! This command returns the current feature settings. */
typedef struct ApiFpGetFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_FEATURES_CFM = 0x40A3 */
  ApiFpFeatureType CurrentFeatures;     /*!< Current feature settings */
  ApiFpFeatureType AvailableFeatures;   /*!< Available feature settings */
} ApiFpGetFeaturesCfmType;

#ifdef RTX_OS_VERSION
  #include <RS/Common/RsPopPack.h>
#elif (RTX_CORE_VERSION >= 0x0224)
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
* FUNCTION:      SendApiFpResetReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_RESET_REQ = 0x4000
****************************************************************************/
void SendApiFpResetReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpGetFwVersionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_FW_VERSION_REQ = 0x4002
****************************************************************************/
void SendApiFpGetFwVersionReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpSetCradleStatusReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_CRADLE_STATUS_REQ = 0x407F
****************************************************************************/
void SendApiFpSetCradleStatusReq ( RosTaskIdType Src,
                                   ApiCradleStatusType ApiCradleStatus);
                                                             /*!< The current status of
                                                                the cradle */

/****************************************************************************
* FUNCTION:      SendApiFpCradleDetectReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CRADLE_DETECT_REQ = 0x4080
****************************************************************************/
void SendApiFpCradleDetectReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpSetTimeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_TIME_REQ = 0x4082
****************************************************************************/
void SendApiFpSetTimeReq ( RosTaskIdType Src,
                           ApiTimeDateCodingType Coding,     /*!< Describes if only
                                                                date, time, or both should
                                                                be set. */
                           ApiTimeDateInterpretationType Interpretation,
                                                             /*!< Describes the time
                                                                stamp interpretation */
                           ApiTimeDateCodeType ApiTimeDateCode);
                                                             /*!< The time stamp */

/****************************************************************************
* FUNCTION:      SendApiFpGetTimeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_TIME_REQ = 0x4084
****************************************************************************/
void SendApiFpGetTimeReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpSyncTimeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SYNC_TIME_REQ = 0x4087
****************************************************************************/
void SendApiFpSyncTimeReq ( RosTaskIdType Src,
                            ApiTerminalIdType TerminalId);   /*!< Id of the handset
                                                                which shall receive the
                                                                timedate update.
                                                                If set to
                                                                API_FP_TIMEDATE_SYNC_ALL_HS
                                                                all attached handsets will
                                                                receive a TimeDate update. */

/****************************************************************************
* FUNCTION:      SendApiFpSetFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_FEATURES_REQ = 0x40A0
****************************************************************************/
void SendApiFpSetFeaturesReq ( RosTaskIdType Src,
                               ApiFpFeatureType ApiFpFeature);
                                                             /*!< Requested features */

/****************************************************************************
* FUNCTION:      SendApiFpGetFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_FEATURES_REQ = 0x40A2
****************************************************************************/
void SendApiFpGetFeaturesReq ( RosTaskIdType Src );


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPGENERAL_H */


