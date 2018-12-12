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
* Definition of the ApiScl interface.
*/


#ifndef APISCL_H
#define APISCL_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! Include of API configuration. */
#include <Api/ApiCfg.h>
/*! Include of common API types */
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

/* Global mail primitives:
  API_SCL_GET_MODE_REQ = 0x4740,
  API_SCL_GET_MODE_CFM = 0x4741,
  API_SCL_SET_MODE_REQ = 0x4742,
  API_SCL_SET_MODE_CFM = 0x4743,
  API_SCL_GET_URL_REQ = 0x4744,
  API_SCL_GET_URL_CFM = 0x4745,
  API_SCL_SET_URL_REQ = 0x4746,
  API_SCL_SET_URL_CFM = 0x4747,
  API_SCL_OPERATION_REQ = 0x4748,
  API_SCL_OPERATION_CFM = 0x4749,
  API_SCL_STATUS_IND = 0x474A,
  API_SCL_VERSIONS_IND = 0x474B,
  API_SCL_GET_GUID_REQ = 0x474C,
  API_SCL_GET_GUID_CFM = 0x474D,
  API_SCL_SET_GUID_REQ = 0x474E,
  API_SCL_SET_GUID_CFM = 0x474F,
The global mail primitives MUST be defined in Global.h! */



/*! This enum id?s the client operation modes supported. */
typedef enum RSENUMTAG(ApiSclModeType)
{
  SCLM_AUTO     = 0x00, /*!< Automatic mode. The SUOTA client will check for new
                           firmware regularly. */
  SCLM_MANUAL   = 0x01, /*!< Manual mode. The SUOTA client will only check for updates
                           when explicitly requested to do so.
                           Pushed updates will be accepted. */
  SCLM_DISABLED = 0x02, /*!< The SUOTA client will only check for updates when
                           explicitly requested to do so. 
                           Pushed updates will be ignored. */
  SCLM_MAX              /*!<  */
} RSENUM8(ApiSclModeType);

/*! This enum id?s the client operations supported. */
typedef enum RSENUMTAG(ApiSclOperationType)
{
  SCLO_CANCEL    = 0x00, /*!< Cancel all operations. */
  SCLO_CHECK_NOW = 0x01, /*!< Perform check for new firmware. */
  SCLO_UPDATE    = 0x02, /*!< Begin update. */
  SCLO_MAX               /*!<  */
} RSENUM8(ApiSclOperationType);

/*! This enum id?s the interval between check for new firmware. */
typedef enum RSENUMTAG(ApiSclIntervalType)
{
  SCLI_NONE    = 0x00, /*!< Interval not relevant. */
  SCLI_DAILY   = 0x01, /*!< Check each day. */
  SCLI_WEEKLY  = 0x02, /*!< Check each week. */
  SCLI_MONTHLY = 0x03, /*!< Check each month. */
  SCLI_MAX             /*!<  */
} RSENUM8(ApiSclIntervalType);

/*! This enum id?s the SOUTA client status. */
typedef enum RSENUMTAG(ApiSclStatusType)
{
  SCLS_IDLE                           = 0x00, /*!< Client is idle. */
  SCLS_NEXT_CHECK                     = 0x01, /*!< Next check for updates will start
                                                 after delay. */
  SCLS_CHECKING                       = 0x02, /*!< Check for updates in progress. */
  SCLS_UPDATE_AVAILABLE               = 0x03, /*!< An update is available. Download will
                                                 start after delay. */
  SCLS_NO_UPDATES                     = 0x04, /*!< No updates available. */
  SCLS_DOWNLOADING                    = 0x05, /*!< Download in progress. */
  SCLS_RESETTING                      = 0x06, /*!< Device will reset shortly. */
  SCLS_COMPLETED                      = 0x07, /*!< Update completed successfully. */
  SCLS_TIMEOUT                        = 0x08, /*!< Missing response e.g. from SUOTA FP
                                                 or management/download server. */
  SCLS_GUID_MISMATCH                  = 0x09, /*!< Downloaded file is not for this
                                                 device. */
  SCLS_MAX,                                   /*!< Reserved for internal use. */
  SCLS_DOWNLOAD_FAILED                = 0x20, /*!< Download of file with indicated file
                                                 number failed. */
  SCLS_APPLICATION_FAILED             = 0x21, /*!< Application of file with indicated
                                                 file number failed. */
  SCLS_UNABLE_TO_DOWNLOAD_IN_TIME     = 0x22, /*!< Unable to download in time-New
                                                 DelayMinutes requested . */
  SCLS_REJECT_REASON                  = 0x40, /*!< Reserved for internal use. */
  SCLS_RETRY_LATER_CONNECTION_REFUSED = 0x41, /*!< Retry later ? connection refused.
                                                 Sent from FP to PP. */
  SCLS_RETRY_LATER_NO_RESOURCES       = 0x42, /*!< Retry later ? FP resources overflow.
                                                 Sent from FP to PP. */
  SCLS_FILE_NOT_FOUND                 = 0x43, /*!< The file specified does not exist.
                                                 Sent from FP to PP */
  SCLS_URL1_INVALID                   = 0x44, /*!< Invalid URL1 format. Sent from FP to
                                                 PP. */
  SCLS_URL1_UNREACHABLE               = 0x45, /*!< Unreachable URL1 (Server error). Sent
                                                 from FP to PP. */
  SCLS_CMD_FORMAT_ERROR               = 0x46, /*!< Command format error. Can be sent In
                                                 both direactions. */
  SCLS_SR_MAX                                 /*!<  */
} RSENUM8(ApiSclStatusType);


/*! Mail without parameters. */
typedef struct ApisclEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApisclEmptySignalType;

/*! This mail is used from the MMI to read the SUOTA client operation mode. */
typedef struct ApiSclGetModeReqType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_GET_MODE_REQ = 0x4740 */
} ApiSclGetModeReqType;

/*! Current SUOTA client operation mode. */
typedef struct ApiSclGetModeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_GET_MODE_CFM = 0x4741 */
  ApiSclModeType Mode;                  /*!< Current SUOTA client operation mode. */
  ApiSclIntervalType Interval;          /*!< Check interval for automatic mode. */
} ApiSclGetModeCfmType;

/*! This mail is used from the MMI to change the SUOTA client operation
   mode. */
typedef struct ApiSclSetModeReqType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_SET_MODE_REQ = 0x4742 */
  ApiSclModeType Mode;                  /*!< New operation mode: Auto, manual. */
  ApiSclIntervalType Interval;          /*!< Check interval for automatic mode. */
} ApiSclSetModeReqType;

/*! Confirmation of operation mode change. */
typedef struct ApiSclSetModeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_SET_MODE_CFM = 0x4743 */
  RsStatusType Status;                  /*!< Status. */
} ApiSclSetModeCfmType;

/*! This mail is used from the MMI to read the SUOTA client URL. */
typedef struct ApiSclGetUrlReqType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_GET_URL_REQ = 0x4744 */
} ApiSclGetUrlReqType;

/*! Current SUOTA client URL. */
typedef struct ApiSclGetUrlCfmType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_GET_URL_CFM = 0x4745 */
  rsuint16 Length;                      /*!< The length in bytes of the URL. */
  rsuint8 Url[1];                       /*!< The URL as array of IA5 chars. */
} ApiSclGetUrlCfmType;

/*! This mail is used from the MMI to change the SUOTA client URL. */
typedef struct ApiSclSetUrlReqType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_SET_URL_REQ = 0x4746 */
  rsuint16 Length;                      /*!< The length in bytes of the URL.
                                           If length=0 is used, the SUOTA client will
                                           restore the default URL. */
  rsuint8 Url[1];                       /*!< The URL as array of IA5 chars. */
} ApiSclSetUrlReqType;

/*! Confirmation of operation mode change. */
typedef struct ApiSclSetUrlCfmType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_SET_URL_CFM = 0x4747 */
  RsStatusType Status;                  /*!< Status. */
} ApiSclSetUrlCfmType;

/*! This mail is used from the MMI to start or cancel SUOTA client
   operations. */
typedef struct ApiSclOperationReqType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_OPERATION_REQ = 0x4748 */
  ApiSclOperationType Operation;        /*!< Operation to perform. */
} ApiSclOperationReqType;

/*! Confirmation of operation command. */
typedef struct ApiSclOperationCfmType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_OPERATION_CFM = 0x4749 */
  RsStatusType Status;                  /*!< Status:
                                           RSS_NOT_SUPPORTED: Unknown operation.
                                           RSS_BUSY: E.g. if attempting check now while an
                                           operation is already in progress.
                                           RSS_NOT_READY: E.g. if attempting begin update
                                           while no operation is in progress. */
} ApiSclOperationCfmType;

/*! This mail is sent from the SUOTA client to the MMI to provide status
   and progress information. */
typedef struct ApiSclStatusIndType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_STATUS_IND = 0x474A */
  ApiSclStatusType Status;              /*!< Current status. For the status values
                                           SCLS_COMPLETED, SCLS_NO_UPDATES and
                                           SCLS_UPDATE_AVAILABLE a API_SCL_VERSIONS_IND will
                                           follow this mail:. */
  rsuint8 Progress;                     /*!< 0..100%. */
  rsuint32 Delay;                       /*!< Delay before next attempt, in seconds. */
} ApiSclStatusIndType;

/*! This mail is sent from the SUOTA client to the MMI to provide
   information about current and new SW version, when a new SW version is
   available. */
typedef struct ApiSclVersionsIndType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_VERSIONS_IND = 0x474B */
  rsbool WaitingForUser;                /*!< Set true when the souta client is waiting
                                           for user confirmation before update is stated.
                                           Confirmation or cancellation is done by sending
                                           API_SCL_OPERATION_REQ with SCLO_UPDATE or
                                           SCLO_CANCEL. */
  rsuint8 CurrentVersionLength;         /*!< The length of the string stored in the
                                           following CurrentVersion parameter. Max length is
                                           20. */
  rsuint8 CurrentVersion[20];           /*!< The current SW version identification
                                           string as array of  IA5 chars. */
  rsuint8 NewVersionLength;             /*!< The length of the string stored in the
                                           following NewVersion parameter. Max length is 20. */
  rsuint8 NewVersion[20];               /*!< The new SW version identification string as
                                           array of  IA5 chars. */
} ApiSclVersionsIndType;

/*! This mail is used from the MMI to read the SUOTA client GUID. */
typedef struct ApiSclGetGuidReqType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_GET_GUID_REQ = 0x474C */
} ApiSclGetGuidReqType;

/*! Current SUOTA client GUID. */
typedef struct ApiSclGetGuidCfmType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_GET_GUID_CFM = 0x474D */
  RsStatusType Status;                  /*!< Status:
                                           RSS_SUCCES: The GUID returned is the default.
                                           RSS_UNKNOWN: The GUID returned is not the
                                           default. */
  ApiGuidType Guid;                     /*!< Device identifier. */
} ApiSclGetGuidCfmType;

/*! This mail is used from the MMI to change the SUOTA client GUID. If any
   bytes in the GUID are 0xFF, the SUOTA client resets the GUID to the
   built-in default value. */
typedef struct ApiSclSetGuidReqType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_SET_GUID_REQ = 0x474E */
  ApiGuidType Guid;                     /*!< Device identifier. */
} ApiSclSetGuidReqType;

/*! Confirmation of operation mode change. */
typedef struct ApiSclSetGuidCfmType
{
  RosPrimitiveType Primitive;            /*!< API_SCL_SET_GUID_CFM = 0x474F */
  RsStatusType Status;                  /*!< Status. */
} ApiSclSetGuidCfmType;

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
* FUNCTION:      SendApiSclGetModeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_GET_MODE_REQ = 0x4740
****************************************************************************/
void SendApiSclGetModeReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiSclSetModeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_SET_MODE_REQ = 0x4742
****************************************************************************/
void SendApiSclSetModeReq ( RosTaskIdType Src,
                            ApiSclModeType Mode,             /*!< New operation mode:
                                                                Auto, manual. */
                            ApiSclIntervalType Interval);    /*!< Check interval for
                                                                automatic mode. */

/****************************************************************************
* FUNCTION:      SendApiSclGetUrlReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_GET_URL_REQ = 0x4744
****************************************************************************/
void SendApiSclGetUrlReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiSclSetUrlReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_SET_URL_REQ = 0x4746
****************************************************************************/
void SendApiSclSetUrlReq ( RosTaskIdType Src,
                           rsuint16 Length,                  /*!< The length in bytes of
                                                                the URL.
                                                                If length=0 is used, the
                                                                SUOTA client will restore
                                                                the default URL. */
                           rsuint8 Url[1]);                  /*!< The URL as array of
                                                                IA5 chars. */

/****************************************************************************
* FUNCTION:      SendApiSclOperationReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_OPERATION_REQ = 0x4748
****************************************************************************/
void SendApiSclOperationReq ( RosTaskIdType Src,
                              ApiSclOperationType Operation);
                                                             /*!< Operation to perform. */

/****************************************************************************
* FUNCTION:      SendApiSclGetGuidReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_GET_GUID_REQ = 0x474C
****************************************************************************/
void SendApiSclGetGuidReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiSclSetGuidReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SCL_SET_GUID_REQ = 0x474E
****************************************************************************/
void SendApiSclSetGuidReq ( RosTaskIdType Src,
                            ApiGuidType Guid);               /*!< Device identifier. */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APISCL_H */


