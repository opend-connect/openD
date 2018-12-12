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
* Definition of the ApiSuota interface.
*/


#ifndef APISUOTA_H
#define APISUOTA_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! Include of API configuration. */
//#include <Api/ApiCfg.h>
/*! Include of common API types. */
#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! This type describes features available in this API */
#define API_SUOTA_EXTENDED_TERMINAL_ID_SUPPORT 0x01

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

//#if (RTX_CORE_VERSION >= 0x0224)
//  #include <Standard/Common/RsPushPack1.h>
//#else
//  #pragma pack(push,1)
//#endif

/* Mail primitives:
  API_SUOTA_SW_VERSION_INFO_REQ = 0x4880,
  API_SUOTA_SW_VERSION_INFO_IND = 0x4881,
  API_SUOTA_NEW_SW_AVAILABLE_REQ = 0x4882,
  API_SUOTA_NEW_SW_AVAILABLE_IND = 0x4883,
  API_SUOTA_NEGATIVE_ACK_REQ = 0x4884,
  API_SUOTA_NEGATIVE_ACK_IND = 0x4885,
  API_SUOTA_FEATURES_REQ = 0x4890,
  API_SUOTA_FEATURES_CFM = 0x4891,
End of mail primitives. */



/*! This type is used to hold a device id. */
typedef ApiTerminalIdType ApiSuotaDeviceIdType; /*!< 0: base
                                           1..n: handset number */

/*! This type is used to hold the EMC. */
typedef rsuint16 ApiSuotaEmcType;

/*! This type is used to hold a file number. */
typedef rsuint8 ApiSuotaFileNumberType;

/*! This type is used to hold a SW update delay (in minutes). */
typedef rsuint16 ApiSuotaDelayType;

/*! This enum identifies the SW update reason codes supported. */
typedef enum RSENUMTAG(ApiSuotaFlagsType)
{
  ASF_NONE                      = 0x00, /*!< No flags set. */
  ASF_USER_INITIATED_SW_UPGRADE = 0x01  /*!< User initiated software upgrade. */
} RSENUM8(ApiSuotaFlagsType);

/*! This enum id?s the SW update reason codes supported. */
typedef enum RSENUMTAG(ApiSuotaReasonType)
{
  ASR_SUCCESS                    = 0x00, /*!< Success of previous files application.
                                            Request for a new file (indicated by "file
                                            number" field). */
  ASR_DOWNLOAD_FAILED            = 0x01, /*!< Download of file with indicated file
                                            number failed. */
  ASR_APPLICATION_FAILED         = 0x02, /*!< Application of file with indicated file
                                            number failed. */
  ASR_UNABLE_TO_DOWNLOAD_IN_TIME = 0x03  /*!< Unable to download in time-New
                                            DelayMinutes requested . */
} RSENUM8(ApiSuotaReasonType);

/*! This enum id?s the user interaction types supported. */
typedef enum RSENUMTAG(ApiSuotaUserInteractionType)
{
  ASUI_NO_USER_INTERACTION       = 0x00, /*!< No user interaction required. */
  ASUI_USER_INTERACTION_REQUIRED = 0x01, /*!< User interaction required. */
  ASUI_UNDEFINED                 = 0x02  /*!< User interaction undefined. */
} RSENUM8(ApiSuotaUserInteractionType);

/*! This enum id?s the Reject reason codes supported. */
typedef enum RSENUMTAG(ApiSuotaRejectReasonType)
{
  ASRR_RESERVED                       = 0x00, /*!< Reserved. */
  ASRR_RETRY_LATER_CONNECTION_REFUSED = 0x01, /*!< Retry later ? connection refused.
                                                 Sent from FP to PP. */
  ASRR_RETRY_LATER_NO_RESOURCES       = 0x02, /*!< Retry later ? FP resources overflow.
                                                 Sent from FP to PP. */
  ASRR_FILE_NOT_FOUND                 = 0x03, /*!< The file specified does not exist.
                                                 Sent from FP to PP. */
  ASRR_URL1_INVALID                   = 0x04, /*!< Invalid URL1 format. Sent from FP to
                                                 PP. */
  ASRR_URL1_UNREACHABLE               = 0x05, /*!< Unreachable URL1 (Server error). Sent
                                                 from FP to PP. */
  ASRR_CMD_FORMAT_ERROR               = 0x06  /*!< Command format error. Can be sent In
                                                 both direactions. */
} RSENUM8(ApiSuotaRejectReasonType);

/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiSuotaFeatureType;


/*! Mail without parameters. */
typedef struct ApisuotaEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApisuotaEmptySignalType;

/*! This mail is used from the SUOTA client application to enquire whether
   a new SW is available for download. This mail triggers the PP to send a
   ?handset version indication? (IWU_to_ IWU FACILITY) message to the FP. */
typedef struct ApiSuotaSwVersionInfoReqType
{
  RosPrimitiveType Primitive;            /*!< API_SUOTA_SW_VERSION_INFO_REQ = 0x4880 */
  ApiSuotaEmcType Emc;                  /*!< The EMC of the device. */
  ApiSuotaFileNumberType FileNumber;    /*!< The file number. Used to identify the
                                           current file if the SW to update is stored in
                                           multiple files. */
  ApiSuotaFlagsType Flags;              /*!< Indicates whether the update is initiated
                                           by the user. */
  ApiSuotaReasonType Reason;            /*!< The reason for this command. */
  rsuint8 SwVersionIdLength;            /*!< The length of the string stored in the
                                           following SwVersionId parameter. Max length is
                                           20. */
  rsuint8 SwVersionId[20];              /*!< The SW version identification string as
                                           array of  IA5 chars. */
  rsuint8 HwVersionIdLength;            /*!< The length of the string stored in the
                                           following HwVersionId parameter. Max length is
                                           20. */
  rsuint8 HwVersionId[20];              /*!< The HW version identification string as
                                           array of  IA5 chars. */
  rsuint16 UrlLength;                   /*!< The length in bytes of the URL. */
  rsuint8 Url[1];                       /*!< The URL as array of IA5 chars. */
} PACKED_STRUCT ApiSuotaSwVersionInfoReqType;

/*! This mail is sent to the SUOTA server application on the FP when a 
   ?handset version indication? FACILITY message is received from the PP. */
typedef struct ApiSuotaSwVersionInfoIndType
{
  RosPrimitiveType Primitive;            /*!< API_SUOTA_SW_VERSION_INFO_IND = 0x4881 */
  ApiSuotaDeviceIdType DeviceId;        /*!< Id of the source. */
  ApiSuotaEmcType Emc;                  /*!< The EMC of the device requesting the SW
                                           info. */
  ApiSuotaFileNumberType FileNumber;    /*!< The file number. Used to identify the
                                           current file if the SW to update is stored in
                                           multiple files. */
  ApiSuotaFlagsType Flags;              /*!< Indicates whether the update is initiated
                                           by the user. */
  ApiSuotaReasonType Reason;            /*!< The reason for this command. */
  rsuint8 SwVersionIdLength;            /*!< The length of the string stored in the
                                           following SwVersionId parameter. Max length is
                                           20. */
  rsuint8 SwVersionId[20];              /*!< The SW version identification string as
                                           array of  IA5 chars. */
  rsuint8 HwVersionIdLength;            /*!< The length of the string stored in the
                                           following HwVersionId parameter. Max length is
                                           20. */
  rsuint8 HwVersionId[20];              /*!< The HW version identification string as
                                           array of  IA5 chars. */
  rsuint16 UrlLength;                   /*!< The length in bytes of the URL. */
  rsuint8 Url[1];                       /*!< The URL as array of IA5 chars. */
} PACKED_STRUCT ApiSuotaSwVersionInfoIndType;

/*! This mail is sent from the SUOTA server application on the FP when new
   SW version information has been received from the software upgrade
   management server (MS). The information is sent to the PP in a ?handset
   version available? (IWU_to_ IWU FACILITY) message. */
typedef struct ApiSuotaNewSwAvailableReqType
{
  RosPrimitiveType Primitive;            /*!< API_SUOTA_NEW_SW_AVAILABLE_REQ = 0x4882 */
  ApiSuotaDeviceIdType DeviceId;        /*!< Id of the destination */
  ApiSuotaDelayType Delay;              /*!< specifies a delay in minutes that the
                                           client should wait before the download of the new
                                           SW is started. */
  ApiSuotaUserInteractionType UserInteraction; /*!< Indicates whether user interaction
                                                   is required to do the SW update. */
  rsuint8 SwVersionIdLength;            /*!< The length of the string stored in the
                                           following SwVersionId parameter. Max length is
                                           20. */
  rsuint8 SwVersionId[20];              /*!< The SW version identification string as
                                           array of  IA5 chars. */
  rsuint16 UrlLength;                   /*!< The length in bytes of the URL. UrlLength =
                                           0 is used to indicate that no new SW is available
                                           for download. */
  rsuint8 Url[1];                       /*!< The URL as array of IA5 chars. */
} PACKED_STRUCT ApiSuotaNewSwAvailableReqType;

/*! This mail is sent to the SUOTA client application when the requested SW
   version information, sent in a ?handset version available? (IWU_to_ IWU
   FACILITY) message, is received from the FP. */
typedef struct ApiSuotaNewSwAvailableIndType
{
  RosPrimitiveType Primitive;            /*!< API_SUOTA_NEW_SW_AVAILABLE_IND = 0x4883 */
  ApiSuotaDelayType Delay;              /*!< specifies a delay in minutes that the
                                           client should wait before the download of the new
                                           SW is started. */
  ApiSuotaUserInteractionType UserInteraction; /*!< Indicates whether user interaction
                                                   is required to do the SW update. */
  rsuint8 SwVersionIdLength;            /*!< The length of the string stored in the
                                           following SwVersionId parameter. Max length is
                                           20. */
  rsuint8 SwVersionId[20];              /*!< The SW version identification string as
                                           array of  IA5 chars. */
  rsuint16 UrlLength;                   /*!< The length in bytes of the URL. UrlLength =
                                           0 is used to indicate that no new SW is available
                                           for download. */
  rsuint8 Url[1];                       /*!< The URL as array of IA5 chars. */
} PACKED_STRUCT ApiSuotaNewSwAvailableIndType;

/*! This mail is used to request a ?Negative acknowledgement? FACILITY
   message to be sent. This mail can be used on both sides. */
typedef struct ApiSuotaNegativeAckReqType
{
  RosPrimitiveType Primitive;            /*!< API_SUOTA_NEGATIVE_ACK_REQ = 0x4884 */
  ApiSuotaDeviceIdType DeviceId;        /*!< Id of the destination . */
  ApiSuotaRejectReasonType Reason;      /*!< Reject reason. */
} PACKED_STRUCT ApiSuotaNegativeAckReqType;

/*! This mail is sent to the application when a ?Negative acknowledgement?
   FACILITY message has been received from the remote. */
typedef struct ApiSuotaNegativeAckIndType
{
  RosPrimitiveType Primitive;            /*!< API_SUOTA_NEGATIVE_ACK_IND = 0x4885 */
  ApiSuotaDeviceIdType DeviceId;        /*!< Id of the source. */
  ApiSuotaRejectReasonType Reason;      /*!< Reject reason. */
} PACKED_STRUCT ApiSuotaNegativeAckIndType;

//#if (RTX_CORE_VERSION >= 0x0224)
//  #include <Standard/Common/RsPopPack.h>
//#else
//  #pragma pack(pop)
//#endif
/*! This command is used to enable/disable features in the Suota API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiSuotaFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_SUOTA_FEATURES_REQ = 0x4890 */
  ApiSuotaFeatureType ApiSuotaFeature;  /*!< Requested features */
} PACKED_STRUCT ApiSuotaFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiSuotaFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_SUOTA_FEATURES_CFM = 0x4891 */
  RsStatusType Status;
  ApiSuotaFeatureType ApiSuotaFeature;  /*!< Supported features */
} PACKED_STRUCT ApiSuotaFeaturesCfmType;

#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiSuotaSwVersionInfoReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SUOTA_SW_VERSION_INFO_REQ = 0x4880
****************************************************************************/
void SendApiSuotaSwVersionInfoReq ( RosTaskIdType Src,
                                    ApiSuotaEmcType Emc,     /*!< The EMC of the device. */
                                    ApiSuotaFileNumberType FileNumber,
                                                             /*!< The file number. Used
                                                                to identify the current file
                                                                if the SW to update is
                                                                stored in multiple files. */
                                    ApiSuotaFlagsType Flags,  /*!< Indicates whether the
                                                                 update is initiated by the
                                                                 user. */
                                    ApiSuotaReasonType Reason,
                                                             /*!< The reason for this
                                                                command. */
                                    rsuint8 SwVersionIdLength,
                                                             /*!< The length of the
                                                                string stored in the
                                                                following SwVersionId
                                                                parameter. Max length is 20. */
                                    rsuint8 SwVersionId[20],  /*!< The SW version
                                                                 identification string as
                                                                 array of  IA5 chars. */
                                    rsuint8 HwVersionIdLength,
                                                             /*!< The length of the
                                                                string stored in the
                                                                following HwVersionId
                                                                parameter. Max length is 20. */
                                    rsuint8 HwVersionId[20],  /*!< The HW version
                                                                 identification string as
                                                                 array of  IA5 chars. */
                                    rsuint16 UrlLength,      /*!< The length in bytes of
                                                                the URL. */
                                    rsuint8 Url[1]);         /*!< The URL as array of
                                                                IA5 chars. */

/****************************************************************************
* FUNCTION:      SendApiSuotaNewSwAvailableReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SUOTA_NEW_SW_AVAILABLE_REQ = 0x4882
****************************************************************************/
void SendApiSuotaNewSwAvailableReq ( RosTaskIdType Src,
                                     ApiSuotaDeviceIdType DeviceId,
                                                             /*!< Id of the destination */
                                     ApiSuotaDelayType Delay,
                                                             /*!< specifies a delay in
                                                                minutes that the client
                                                                should wait before the
                                                                download of the new SW is
                                                                started. */
                                     ApiSuotaUserInteractionType UserInteraction,
                                                             /*!< Indicates whether user
                                                                interaction is required to
                                                                do the SW update. */
                                     rsuint8 SwVersionIdLength,
                                                             /*!< The length of the
                                                                string stored in the
                                                                following SwVersionId
                                                                parameter. Max length is 20. */
                                     rsuint8 SwVersionId[20],
                                                             /*!< The SW version
                                                                identification string as
                                                                array of  IA5 chars. */
                                     rsuint16 UrlLength,     /*!< The length in bytes of
                                                                the URL. UrlLength = 0 is
                                                                used to indicate that no new
                                                                SW is available for
                                                                download. */
                                     rsuint8 Url[1]);        /*!< The URL as array of
                                                                IA5 chars. */

/****************************************************************************
* FUNCTION:      SendApiSuotaNegativeAckReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SUOTA_NEGATIVE_ACK_REQ = 0x4884
****************************************************************************/
void SendApiSuotaNegativeAckReq ( RosTaskIdType Src,
                                  ApiSuotaDeviceIdType DeviceId,
                                                             /*!< Id of the destination
                                                                . */
                                  ApiSuotaRejectReasonType Reason);
                                                             /*!< Reject reason. */

/****************************************************************************
* FUNCTION:      SendApiSuotaFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_SUOTA_FEATURES_REQ = 0x4890
****************************************************************************/
void SendApiSuotaFeaturesReq ( RosTaskIdType Src,
                               ApiSuotaFeatureType ApiSuotaFeature);
                                                             /*!< Requested features */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APISUOTA_H */


