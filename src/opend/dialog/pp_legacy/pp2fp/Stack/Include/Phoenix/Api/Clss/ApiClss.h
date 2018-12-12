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
* Definition of the ApiClss interface.
*/


#ifndef APICLSS_H
#define APICLSS_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
#include <Api/ApiCfg.h>

#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! This type describes features available in this API */
#define API_CLSS_EXTENDED_TERMINAL_ID_SUPPORT 0x01

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_CLSS_REQ = 0x5C40,
  API_CLSS_IND = 0x5C41,
  API_CLSS_SET_IWU_TO_IWU_REQ = 0x5C42,
  API_CLSS_SET_IWU_TO_IWU_CFM = 0x5C43,
  API_CLSS_SET_FEATURES_REQ = 0x5C48,
  API_CLSS_SET_FEATURES_CFM = 0x5C49,
  API_CLSS_GET_FEATURES_REQ = 0x5C4A,
  API_CLSS_GET_FEATURES_CFM = 0x5C4B,
End of mail primitives. */



/*! This type is used to hold a device id. */
typedef ApiTerminalIdType ApiClssDeviceIdType; /*!< 1..n: handset number */

/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiClssFeatureType;


/*! Mail without parameters. */
typedef struct ApiclssEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApiclssEmptySignalType;

/*! This mail is used by the MMI to send a FACILITY message. */
typedef struct ApiClssReqType
{
  RosPrimitiveType Primitive;            /*!< API_CLSS_REQ = 0x5C40 */
  ApiClssDeviceIdType DeviceId;         /*!< Id of the destination */
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
                                           API_IE_PROPRIETARY
                                           API_IE_IWU_TO_IWU */
} ApiClssReqType;

/*! This mail is used to inform the MMI of a FACILITY message. */
typedef struct ApiClssIndType
{
  RosPrimitiveType Primitive;            /*!< API_CLSS_IND = 0x5C41 */
  ApiClssDeviceIdType DeviceId;         /*!< Id of the source. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Info elements:
                                           API_IE_PROPRIETARY
                                           API_IE_IWU_TO_IWU */
} ApiClssIndType;

/*! This mail is used by the Host to inform the API which API_IE_IWU_TO_IWU
   it wants to receive. The mail must be sent for each
   IwuProtocolDiscriminator to be received.
    This setting is common for all handsets. */
typedef struct ApiClssSetIwuToIwuReqType
{
  RosPrimitiveType Primitive;            /*!< API_CLSS_SET_IWU_TO_IWU_REQ = 0x5C42 */
  ApiProtocolDiscriminatorType IwuProtocolDiscriminator; /*!< IWU protocol
                                                             discriminator. */
} ApiClssSetIwuToIwuReqType;

/*! This mail is used by the MMI to initiate a CISS connection. */
typedef struct ApiClssSetIwuToIwuCfmType
{
  RosPrimitiveType Primitive;            /*!< API_CLSS_SET_IWU_TO_IWU_CFM = 0x5C43 */
  RsStatusType Status;                  /*!< Indicates whether the
                                           API_CLSS_SET_IWU_TO_IWU_REQ was executed
                                           correctly or not.
                                           RsStatusType is defined in the ROS */
} ApiClssSetIwuToIwuCfmType;

/*! This command is used to enable/disable features in the CLSS API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiClssSetFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_CLSS_SET_FEATURES_REQ = 0x5C48 */
  ApiClssFeatureType ApiClssFeature;    /*!< Requested features */
} ApiClssSetFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiClssSetFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_CLSS_SET_FEATURES_CFM = 0x5C49 */
  RsStatusType Status;
  ApiClssFeatureType ApiClssFeature;    /*!< Supported features */
} ApiClssSetFeaturesCfmType;

/*! This command is used request the current feature settings. */
typedef ApiclssEmptySignalType ApiClssGetFeaturesReqType;

/*! This command returns the current feature settings. */
typedef struct ApiClssGetFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_CLSS_GET_FEATURES_CFM = 0x5C4B */
  ApiClssFeatureType CurrentFeatures;   /*!< Current feature settings */
  ApiClssFeatureType AvailableFeatures; /*!< Available feature settings */
} ApiClssGetFeaturesCfmType;

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
* FUNCTION:      SendApiClssReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CLSS_REQ = 0x5C40
****************************************************************************/
void SendApiClssReq ( RosTaskIdType Src,
                      ApiClssDeviceIdType DeviceId,          /*!< Id of the destination */
                      rsuint16 InfoElementLength,            /*!< The length of the Data
                                                                Information Element */
                      rsuint8 InfoElement[1]);               /*!< The InfoElementList
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
                                                                API_IE_PROPRIETARY
                                                                API_IE_IWU_TO_IWU */

/****************************************************************************
* FUNCTION:      SendApiClssSetIwuToIwuReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CLSS_SET_IWU_TO_IWU_REQ = 0x5C42
****************************************************************************/
void SendApiClssSetIwuToIwuReq ( RosTaskIdType Src,
                                 ApiProtocolDiscriminatorType IwuProtocolDiscriminator);
                                                             /*!< IWU protocol
                                                                discriminator. */

/****************************************************************************
* FUNCTION:      SendApiClssSetFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CLSS_SET_FEATURES_REQ = 0x5C48
****************************************************************************/
void SendApiClssSetFeaturesReq ( RosTaskIdType Src,
                                 ApiClssFeatureType ApiClssFeature);
                                                             /*!< Requested features */

/****************************************************************************
* FUNCTION:      SendApiClssGetFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CLSS_GET_FEATURES_REQ = 0x5C4A
****************************************************************************/
void SendApiClssGetFeaturesReq ( RosTaskIdType Src );


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APICLSS_H */


