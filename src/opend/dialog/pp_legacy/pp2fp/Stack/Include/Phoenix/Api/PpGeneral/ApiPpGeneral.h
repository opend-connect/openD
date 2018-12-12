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
* Definition of the ApiPpGeneral interface.
*/


#ifndef APIPPGENERAL_H
#define APIPPGENERAL_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
#include <Api/ApiCfg.h>
/*! The following API files must be included. */
#include <Phoenix/Api/Types/ApiTypes.h>

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
  API_PP_GET_FW_VERSION_REQ = 0x5200,
  API_PP_GET_FW_VERSION_CFM = 0x5201,
  API_PP_RESET_REQ = 0x5202,
  API_PP_RESET_IND = 0x5203,
  API_PP_POWER_OFF_REQ = 0x5204,
  API_PP_CRADLE_DETECT_REQ = 0x5205,
  API_PP_CRADLE_DETECT_IND = 0x5206,
  API_PP_SET_TIME_REQ = 0x5207,
  API_PP_SET_TIME_CFM = 0x5208,
  API_PP_SYNC_TIME_REQ = 0x520B,
  API_PP_GET_TIME_REQ = 0x5209,
  API_PP_GET_TIME_CFM = 0x520A,
End of mail primitives. */




/*! Mail without parameters. */
typedef struct ApippgeneralEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApippgeneralEmptySignalType;

/*! This command is used by the MMI to get the Firmware version of the
   unit. */
typedef ApippgeneralEmptySignalType ApiPpGetFwVersionReqType;

/*! This mail is used to confirm the API_PP_GET_FW_VERSION_REQ command. */
typedef struct ApiPpGetFwVersionCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_GET_FW_VERSION_CFM = 0x5201 */
  rsuint32 VersionHex;                  /*!< The Firmware version. */
  rsuint8 LinkDate[5];                  /*!< The link date. */
  ApiDectTypeType DectType;             /*!< Specifies whether this is unit is setup for
                                           EU or US DECT. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< Possible Info elements:
                                           [API_IE_AVAILABLE_APIS] */
} ApiPpGetFwVersionCfmType;

/*! This mail is used by the MMI to request the API to do a SW reset. The
   API will reinitialize the unit and return an API_PP_RESET_IND when the API
   is ready to accept commands from the MMI again. */
typedef ApippgeneralEmptySignalType ApiPpResetReqType;

/*! This mail is used by the API to indicate to the MMI that the API is
   ready to accept commands from the MMI. */
typedef ApippgeneralEmptySignalType ApiPpResetIndType;

/*! This mail is used by the MMI to request the API to power down the unit. 
    API_PP_POWER_OFF_REQ turns off the unit immediately. It doesn't return any
   cfm message. */
typedef ApippgeneralEmptySignalType ApiPpPowerOffReqType;

/*! This mail is used by the MMI to force the API to reply instantly with
   the cradle status (API_PP_BAT_CRADLE_IND). */
typedef ApippgeneralEmptySignalType ApiPpCradleDetectReqType;

/*! This mail is used by the API to indicate the cradle status to the MMI.
    It is automatically send by the API at every change or instantly if
   requested by the API_PP_BAT_CRADLE_REQ */
typedef struct ApiPpCradleDetectIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_CRADLE_DETECT_IND = 0x5206 */
  ApiCradleStatusType ApiCradleStatus;  /*!< The current status of the cradle */
} ApiPpCradleDetectIndType;

/*! This mail is by the MMI to request the FP to set its real time clock to
   a specific timestamp, then distribute it to the registered PP's. This mail
   should only be sent if the ClockMaster in Dect System Settings List is set
   to PP, otherwise the entered time will not be set, and instead the time on
   the Fp will be distributed. */
typedef struct ApiPpSetTimeReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_SET_TIME_REQ = 0x5207 */
  ApiTimeDateCodingType Coding;         /*!< Describes if only date, time, or both
                                           should be set. */
  ApiTimeDateInterpretationType Interpretation; /*!< Describes the time stamp
                                                    interpretation */
  ApiTimeDateCodeType ApiTimeDateCode;  /*!< The time stamp */
} ApiPpSetTimeReqType;

/*! This mail is used by the API to confirm the API_PP_SET_TIME_REQ
   command. */
typedef struct ApiPpSetTimeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_SET_TIME_CFM = 0x5208 */
  RsStatusType Status;                  /*!< Indicates whether the API_PP_SET_TIME_REQ
                                           was executed correctly or not.
                                           RsStatusType is defined in the ROS */
} ApiPpSetTimeCfmType;

/*! This mail is by the MMI to request the FP to distribute the FP time to
   all registered PP's. This mail should only be sent if the ClockMaster in
   Dect System Settings List is set yo Fp */
typedef ApippgeneralEmptySignalType ApiPpSyncTimeReqType;

/*! This mail is by the MMI to request the API to return the current
   timestamp on the PP. */
typedef ApippgeneralEmptySignalType ApiPpGetTimeReqType;

/*! This mail is used by the API to confirm the API_PP_GET_TIME_REQ command.
    It holds the current time stamp. */
typedef struct ApiPpGetTimeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_GET_TIME_CFM = 0x520A */
  ApiTimeDateCodeType ApiTimeDateCode;  /*!< The time stamp */
} ApiPpGetTimeCfmType;

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
* FUNCTION:      SendApiPpGetFwVersionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_GET_FW_VERSION_REQ = 0x5200
****************************************************************************/
void SendApiPpGetFwVersionReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpResetReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_RESET_REQ = 0x5202
****************************************************************************/
void SendApiPpResetReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpPowerOffReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_POWER_OFF_REQ = 0x5204
****************************************************************************/
void SendApiPpPowerOffReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpCradleDetectReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_CRADLE_DETECT_REQ = 0x5205
****************************************************************************/
void SendApiPpCradleDetectReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpSetTimeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_SET_TIME_REQ = 0x5207
****************************************************************************/
void SendApiPpSetTimeReq ( RosTaskIdType Src,
                           ApiTimeDateCodingType Coding,     /*!< Describes if only
                                                                date, time, or both should
                                                                be set. */
                           ApiTimeDateInterpretationType Interpretation,
                                                             /*!< Describes the time
                                                                stamp interpretation */
                           ApiTimeDateCodeType ApiTimeDateCode);
                                                             /*!< The time stamp */

/****************************************************************************
* FUNCTION:      SendApiPpSyncTimeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_SYNC_TIME_REQ = 0x520B
****************************************************************************/
void SendApiPpSyncTimeReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpGetTimeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_GET_TIME_REQ = 0x5209
****************************************************************************/
void SendApiPpGetTimeReq ( RosTaskIdType Src );


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIPPGENERAL_H */


