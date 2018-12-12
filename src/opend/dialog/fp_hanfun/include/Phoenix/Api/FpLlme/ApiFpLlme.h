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
* Definition of the ApiFpLlme interface.
*/


#ifndef APIFPLLME_H
#define APIFPLLME_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API header files must be included. */
/*! The following API header files must be included. */
//#include <ApiTypes.h>
#include <Phoenix/Api/Types/ApiTypes.h> /* General types used. */

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! This type describes features available in this API. */
#define API_FP_LLME_EXTENDED_TERMINAL_ID_SUPPORT 0x01

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

//#if (RTX_CORE_VERSION >= 0x0224)
//  #include <Standard/Common/RsPushPack1.h>
//#else
//  #pragma pack(push,1)
//#endif

/* Mail primitives:
  API_FP_LLME_GET_RSSI_REQ = 0x47B0,
  API_FP_LLME_GET_RSSI_CFM = 0x47B1,
  API_FP_LLME_GET_PERFORMANCE_TABLE_REQ = 0x47B2,
  API_FP_LLME_GET_PERFORMANCE_TABLE_CFM = 0x47B3,
  API_FP_LLME_FEATURES_REQ = 0x47B4,
  API_FP_LLME_FEATURES_CFM = 0x47B5,
End of mail primitives. */



/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiFpLlmeFeatureType;


/*! Mail without parameters. */
typedef struct ApifpllmeEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApifpllmeEmptySignalType;

/*! This mail is used by the API to request the signal strength of an
   ongoing call to the MMI. */
typedef struct ApiFpLlmeGetRssiReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LLME_GET_RSSI_REQ = 0x47B0 */
  ApiTerminalIdType TerminalId;        /*!< Selects which Pp to receive RSSI from */
} PACKED_STRUCT ApiFpLlmeGetRssiReqType;

/*! This mail is used by the API to return signal strength of an ongoing
   call to the MMI. */
typedef struct ApiFpLlmeGetRssiCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LLME_GET_RSSI_CFM = 0x47B1 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. Command will only report SUCCESS if
                                           connection is active. */
  ApiTerminalIdType TerminalId;        /*!< Selected Pp */
  rsuint8 Rssi;                         /*!< Received Signal Strength Indication for the
                                           selected Pp. Range 0x00-0x3F. */
} PACKED_STRUCT ApiFpLlmeGetRssiCfmType;

/*! This command is used by the MMI to request the API to return the
   protocol performance table with connection statistics for a specific Pp. */
typedef struct ApiFpLlmeGetPerformanceTableReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LLME_GET_PERFORMANCE_TABLE_REQ = 0x47B2 */
  ApiTerminalIdType TerminalId;        /*!< Selects which Pp to receive statistics from */
} PACKED_STRUCT ApiFpLlmeGetPerformanceTableReqType;

/*! This mail is used by the API to return the performance table to the MMI.
    The info will represent the latest cc connection while ongoing or completed.
    PerformanceTable counters will be reset when setting up a new connection. */
typedef struct ApiFpLlmeGetPerformanceTableCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LLME_GET_PERFORMANCE_TABLE_CFM = 0x47B3 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiTerminalIdType TerminalId;        /*!< Receiving info from Pp */
  rsuint32 PerformanceHandovers;        /*!< Number of Handovers in last call */
  rsuint32 PerformanceSyncFailures;     /*!< SyncFailures in last call */
  rsuint32 PerformanceControlFieldErrs; /*!< PerformanceControlFieldErrs in last call
                                            (ACRC) */
  rsuint32 PerformancePayloadErrs;      /*!< PerformancePayloadErrs in call (XCRC) */
  rsuint32 PerformanceSlidingCollisions; /*!< PerformanceSlidingCollisions in last call
                                             (ZCRC) */
  rsuint32 PerformanceLinkErrsQbit;     /*!< PerformanceLinkErrsQbit in last call (QErr) */
} PACKED_STRUCT ApiFpLlmeGetPerformanceTableCfmType;

/*! This command is used to enable/disable features in the FpLlme API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiFpLlmeFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LLME_FEATURES_REQ = 0x47B4 */
  ApiFpLlmeFeatureType ApiFpLlmeFeature; /*!< Requested features */
} PACKED_STRUCT ApiFpLlmeFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiFpLlmeFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_LLME_FEATURES_CFM = 0x47B5 */
  RsStatusType Status;
  ApiFpLlmeFeatureType ApiFpLlmeFeature; /*!< Supported features */
} PACKED_STRUCT ApiFpLlmeFeaturesCfmType;

//#if (RTX_CORE_VERSION >= 0x0224)
//  #include <Standard/Common/RsPopPack.h>
//#else
//  #pragma pack(pop)
//#endif

#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiFpLlmeGetRssiReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LLME_GET_RSSI_REQ = 0x47B0
****************************************************************************/
void SendApiFpLlmeGetRssiReq ( RosTaskIdType Src,
                               ApiTerminalIdType TerminalId);
                                                             /*!< Selects which Pp to
                                                                receive RSSI from */

/****************************************************************************
* FUNCTION:      SendApiFpLlmeGetPerformanceTableReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LLME_GET_PERFORMANCE_TABLE_REQ = 0x47B2
****************************************************************************/
void SendApiFpLlmeGetPerformanceTableReq ( RosTaskIdType Src,
                                           ApiTerminalIdType TerminalId);
                                                             /*!< Selects which Pp to
                                                                receive statistics from */

/****************************************************************************
* FUNCTION:      SendApiFpLlmeFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_LLME_FEATURES_REQ = 0x47B4
****************************************************************************/
void SendApiFpLlmeFeaturesReq ( RosTaskIdType Src,
                                ApiFpLlmeFeatureType ApiFpLlmeFeature);
                                                             /*!< Requested features */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPLLME_H */


