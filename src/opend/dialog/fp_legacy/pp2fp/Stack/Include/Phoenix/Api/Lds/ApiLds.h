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
* Definition of the ApiLds interface.
*/


#ifndef APILDS_H
#define APILDS_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! Include of API configuration. */
#include <Api/ApiCfg.h>
/*! Include of common API types. */
#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! This type describes features available in this API. */
#define API_LDS_EXTENDED_TERMINAL_ID_SUPPORT 0x01

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_LDS_OPEN_REQ = 0x4800,
  API_LDS_OPEN_CFM = 0x4801,
  API_LDS_OPEN_IND = 0x4802,
  API_LDS_OPEN_RES = 0x4803,
  API_LDS_CLOSE_REQ = 0x4804,
  API_LDS_CLOSE_CFM = 0x4805,
  API_LDS_CLOSE_IND = 0x4806,
  API_LDS_REJECT_REQ = 0x4807,
  API_LDS_REJECT_IND = 0x4808,
  API_LDS_TX_READY_IND = 0x4820,
  API_LDS_TX_DATA_REQ = 0x4821,
  API_LDS_TX_DATA_CFM = 0x4822,
  API_LDS_RX_DATA_IND = 0x4823,
  API_LDS_SET_FEATURES_REQ = 0x4830,
  API_LDS_SET_FEATURES_CFM = 0x4831,
  API_LDS_GET_FEATURES_REQ = 0x4832,
  API_LDS_GET_FEATURES_CFM = 0x4833,
End of mail primitives. */



/*! This type is used to hold a device id. */
typedef ApiTerminalIdType ApiLdsDeviceIdType;

/*! This type is used to hold a port number. */
typedef rsuint32 ApiLdsPortNumberType;

/*! This enum identifies the SDU state for the data stored in a TX/RX
   buffer. */
typedef enum RSENUMTAG(ApiLdsSduStateType)
{
  ALSS_SDU_COMPLETE              = 0x00, /*!< The SDU is not fragmented. */
  ALSS_SDU_FIRST_FRAGMENT        = 0x01, /*!< First fragment of the SDU. */
  ALSS_SDU_CONTINUATION_FRAGMENT = 0x02, /*!< Continuation fragment of the SDU. */
  ALSS_SDU_LAST_FRAGMENT         = 0x03  /*!< Last fragment of the SDU. */
} RSENUM8(ApiLdsSduStateType);

/*! This enum defines the data interfaces supported by the LDS API. */
typedef enum RSENUMTAG(ApiLdsDataInterfaceType)
{
  ALDI_MAIL_INTERFACE   = 0x00, /*!< The SDU data is sent in mails between the
                                   application and the application. This option should be
                                   used if the API and the application are implemented on
                                   two different systems (e.g. CVM and MCU). */
  ALDI_MEMORY_INTERFACE = 0x01  /*!< The SDU data is passed between the API and the
                                   application by direct copy from memory to memory.
                                   Functions are used to obtain the buffers for RX and TX
                                   data. */
} RSENUM8(ApiLdsDataInterfaceType);

/*! This enum identifies the events that can be signaled by the event
   callback function. */
typedef enum RSENUMTAG(ApiLdsEventType)
{
  ALEV_TX_DONE  = 0x00, /*!< The TX buffer specified has been sent and the application
                           can now free/reuse the buffer. */
  ALEV_TX_READY = 0x01, /*!< Generated if the LU10 is ready to handle more data and no
                           data is pending for TX in the LDS API. */
  ALEV_RX_READY = 0x02  /*!< One or more RX buffers are ready for the application. */
} RSENUM8(ApiLdsEventType);

/*! This struct holds the event parameters for the ALEV_TX_DONE event. */
typedef struct ApiLdsTxDoneEventParameterType
{
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number. */
  RsStatusType Status;                  /*!< RSS_SUCCESS if the data buffer was sent
                                           successfully. */
  rsuint8 *BufferPtr;                   /*!< Pointer to buffer sent. */
  rsuint16 Size;                        /*!< The actual number of bytes sent. */
} ApiLdsTxDoneEventParameterType;

/*! This struct holds the event parameters for the ALEV_TX_READY event. */
typedef struct ApiLdsTxReadyEventParameterType
{
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
} ApiLdsTxReadyEventParameterType;

/*! This struct holds the event parameters for the ALEV_RX_READY event. */
typedef struct ApiLdsRxReadyEventParameterType
{
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number. */
  RsStatusType Status;                  /*!< RSS_SUCCESS if the data is received OK
                                           RSS_BAD_DATA if an error has been detected. The
                                           application must discard the entire SDU. */
} ApiLdsRxReadyEventParameterType;

/*! This union holds the event parameters. */
typedef union ApiLdsEventParameterType
{
  ApiLdsTxDoneEventParameterType TxDone; /*!< Parameter for ALEV_TX_DONE. */
  ApiLdsTxReadyEventParameterType TxReady; /*!< Parameter for ALEV_TX_READY. */
  ApiLdsRxReadyEventParameterType RxReady; /*!< Parameter for ALEV_RX_READY. */
} ApiLdsEventParameterType;

/*! This type is used to hold a pointer to the callback function used to
   signal RX/TX buffer availability.
    For the ALEV_RX_READY event, the application my return FALSE to suspend
   receive. Receive can be resumed using ApiLdsResume(). */
typedef rsbool (*ApiLdsEventCbType)( ApiLdsEventType Event, ApiLdsEventParameterType *ParameterPtr);

/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiLdsFeatureType;


/*! Mail without parameters. */
typedef struct ApildsEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApildsEmptySignalType;

/*! This mail is used from the application to open a data connection to a
   remote device. A virtual call setup is initiated if this is the first data
   connection between the two devices, or a new instance is created in case a
   data connection has been established prior to sending this mail. 
    
    Please note that one instance only can exist on the connection between the
   two devices if class 3 or 4 is used. */
typedef struct ApiLdsOpenReqType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_OPEN_REQ = 0x4800 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device.
                                           Set to 0 if connection is requested by a PP
                                           connecting to a FP. 
                                           Set to handset id if connection is requested
                                           from FP to PP. */
  ApiLdsPortNumberType Port;            /*!< The port number used. Must be 1079 for
                                           class 3/4. */
  ApiCcBasicServiceType BasicService;   /*!< Class 4 only is supported in the current
                                           implementation. */
  ApiLdsDataInterfaceType DataInterface; /*!< Specifies whether SDU data is exchanged
                                             between the API and the application in mails or
                                             by direct memory access. */
  ApiLdsEventCbType Callback;           /*!< Pointer to call back function used when the
                                           direct memory based data interface is used. Set
                                           to NULL if mail based data interface is used. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element.
                                           Reserved for future extension of the API. Must be
                                           set to 0. */
  rsuint8 InfoElement[1];               /*!< Reserved for future extension of the API. */
} ApiLdsOpenReqType;

/*! This mail is sent to the application when the data connection has been
   created or if the data connection has been rejected. */
typedef struct ApiLdsOpenCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_OPEN_CFM = 0x4801 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number used. */
  RsStatusType Status;                  /*!< Indicates whether the call is accepted or
                                           not by the remote device. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element.
                                           Reserved for future extension of the API. Must be
                                           set to 0. */
  rsuint8 InfoElement[1];               /*!< Reserved for future extension of the API. */
} ApiLdsOpenCfmType;

/*! This mail is sent to the application when the creation of a data
   connection has been requested by the remote device. The application can
   respond with API_LDS_OPEN_RES with either RSS_SUCCESS to accept the data
   connection or RSS_REJECTED reject the call is accepted. */
typedef struct ApiLdsOpenIndType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_OPEN_IND = 0x4802 */
  ApiLdsDeviceIdType DeviceId;          /*!< The id of the remote device. 0 if the
                                           remote device is a FP and handset id if the
                                           remote device is a PP. */
  ApiLdsPortNumberType Port;            /*!< The port number used. 1079 for class 3/4. */
  ApiCcBasicServiceType BasicService;   /*!< Class 4 is supported only. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element.
                                           Reserved for future extension of the API. Must be
                                           set to 0. */
  rsuint8 InfoElement[1];               /*!< Reserved for future extension of the API. */
} ApiLdsOpenIndType;

/*! This mail is used from the application to accept an incoming data
   connection and connect the U-Plane. */
typedef struct ApiLdsOpenResType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_OPEN_RES = 0x4803 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number used. */
  RsStatusType Status;                  /*!< Indicates whether the call is accepted or
                                           not. RSS_REJECTED is used to indicate that the
                                           call is rejected by the user / host and
                                           RSS_SUCCESS is used to indicate that the virtual
                                           call is accepted. */
  ApiLdsDataInterfaceType DataInterface; /*!< Specifies whether SDU data is exchanged
                                             between the API and the application in mails or
                                             by direct memory access. */
  ApiLdsEventCbType Callback;           /*!< Pointer to call back function. Can be used
                                           when the application and the API are implemented
                                           in the same memory space and the mail based data
                                           interface is not used. Set to NULL if not used. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element.
                                           Reserved for future extension of the API. Must be
                                           set to 0. */
  rsuint8 InfoElement[1];               /*!< Reserved for future extension of the API. */
} ApiLdsOpenResType;

/*! This mail is used from the application to close the data connection
   specified. The virtual call is release when all data connection instances
   have been released. Setting the Instance parameter to 0 will request the
   API to release all instances and release the virtual call. */
typedef struct ApiLdsCloseReqType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_CLOSE_REQ = 0x4804 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number used. */
  ApiCcReleaseReasonType Reason;        /*!< Release reason. */
} ApiLdsCloseReqType;

/*! This mail is sent to the application when the data connection has been
   closed. */
typedef struct ApiLdsCloseCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_CLOSE_CFM = 0x4805 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number used. */
} ApiLdsCloseCfmType;

/*! This mail is sent to the application when the data connection has been
   released by the remote device. */
typedef struct ApiLdsCloseIndType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_CLOSE_IND = 0x4806 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number used. */
  ApiCcReleaseReasonType Reason;        /*!< Release reason. */
} ApiLdsCloseIndType;

/*! This mail is used from the application to e.g. reject an incoming data connection.
    Deprecated, use API_LDS_OPEN_RES with Status=RSS_REJECTED. */
typedef struct ApiLdsRejectReqType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_REJECT_REQ = 0x4807 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number used. */
  ApiCcReleaseReasonType Reason;        /*!< Reject reason. */
} ApiLdsRejectReqType;

/*! This mail is sent to the application if e.g. the setup has been
   rejected by the remote device. */
typedef struct ApiLdsRejectIndType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_REJECT_IND = 0x4808 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number used. */
  ApiCcReleaseReasonType Reason;        /*!< Reject reason.	 */
} ApiLdsRejectIndType;

/*! This mail is used by the LDS API to inform the APP when it is ready to
   handle TX data. This mail is sent right after data connection setup to
   inform the application when the API is ready to handle TX data. */
typedef struct ApiLdsTxReadyIndType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_TX_READY_IND = 0x4820 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
} ApiLdsTxReadyIndType;

/*! This mail is used by the application to send a SDU or fragment of a SDU
   to the remote device. Fragmentation of SDU?s are supported to reduce the
   over all buffer requirements. Fragmentation of SDU?s on this level should
   be used carefully as it is not possible to send another SDU before all
   fragments of a SDU has been sent! */
typedef struct ApiLdsTxDataReqType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_TX_DATA_REQ = 0x4821 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number. */
  ApiLdsSduStateType SduState;          /*!< Indicates if the mail contains:
                                           A complete SDU.
                                           First fragment of the SDU.
                                           Continuation fragment of the SDU.
                                           Last fragment of the SDU. */
  rsbool More;                          /*!< Used as followed if the chopping option is used:
                                           FALSE: This is the last segment (or the only
                                           one) of an application packet.
                                           TRUE: The next segment of the same application
                                           packet follows in next SDU 
                                           Should be set to FALSE (0) if chopping is not
                                           used. */
  rsuint8 SequenceNumber;               /*!< Set to 0 for the first time this mail is
                                           sent and incremented by one for subsequent mails.
                                           Used to detect missing TX data fragments due to
                                           e.g. TX buffer overrun. */
  rsuint16 DataLength;                  /*!< The size in bytes of the data parameter. */
  rsuint8 Data[1];                      /*!< The SDU data. */
} ApiLdsTxDataReqType;

/*! This mail is sent by the API when the TX data has been queued for TX or
   if the TX buffer is full. The API will send API_LDS_TX_READY_IND once a TX
   buffer is available again in case a negative CFM is sent back to the
   application because the TX buffer is full. */
typedef struct ApiLdsTxDataCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_TX_DATA_CFM = 0x4822 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number. */
  RsStatusType Status;                  /*!< Indicates the result of the request:
                                           RSS_SUCCESS if the data is queued
                                           RSS_NO_MEMORY if the TX buffer in the device is full.
                                           RSS_BAD_DATA if the SequenceNumer parameter of
                                           the request is different from the one expected.
                                           RSS_NOT_SUPPORTED if the mail based data
                                           interface is not selected during the connection
                                           establishment. */
  rsuint8 SequenceNumber;               /*!< The sequence number from the request that
                                           this mails confirms. */
} ApiLdsTxDataCfmType;

/*! This mail is used by the API to send data received to the application.
   The RX data is removed from the RX buffer in the LDS API once this mail is
   sent. It is the responsibility of the application to insure that the RX
   data is handled. */
typedef struct ApiLdsRxDataIndType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_RX_DATA_IND = 0x4823 */
  ApiLdsDeviceIdType DeviceId;          /*!< The device id of the remote device. */
  ApiLdsPortNumberType Port;            /*!< The port number. */
  RsStatusType Status;                  /*!< Indicates the whether the RX data is valid:
                                           RSS_SUCCESS if the data is received OK
                                           RSS_BAD_DATA if an error has been detected. The
                                           application must discard the entire SDU. */
  ApiLdsSduStateType SduState;          /*!< Indicates if the mail contains:
                                           A complete SDU.
                                           First fragment of the SDU.
                                           Continuation fragment of the SDU.
                                           Last fragment of the SDU. */
  rsbool More;                          /*!< Used as followed if the chopping option is used:
                                           FALSE: This is the last segment (or the only
                                           one) of an application packet.
                                           TRUE: The next segment of the same application
                                           packet follows in next SDU 
                                           Set to FALSE (0) if chopping is not used. */
  rsuint8 SequenceNumber;               /*!< Set to 0 for the first time this mail is
                                           sent on the connection and incremented by one for
                                           subsequent mails. */
  rsuint16 DataLength;                  /*!< The size in bytes of the data parameter. */
  rsuint8 Data[1];                      /*!< The SDU data. */
} ApiLdsRxDataIndType;

/*! This command is used to enable/disable features in the Lds API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiLdsSetFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_SET_FEATURES_REQ = 0x4830 */
  ApiLdsFeatureType ApiLdsFeature;      /*!< Requested features */
} ApiLdsSetFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiLdsSetFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_SET_FEATURES_CFM = 0x4831 */
  RsStatusType Status;
  ApiLdsFeatureType ApiLdsFeature;      /*!< Supported features */
} ApiLdsSetFeaturesCfmType;

/*! This command is used request the current feature settings. */
typedef ApildsEmptySignalType ApiLdsGetFeaturesReqType;

/*! This command returns the current feature settings. */
typedef struct ApiLdsGetFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LDS_GET_FEATURES_CFM = 0x4833 */
  ApiLdsFeatureType CurrentFeatures;    /*!< Current feature settings */
  ApiLdsFeatureType AvailableFeatures;  /*!< Available feature settings */
} ApiLdsGetFeaturesCfmType;

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
* FUNCTION:      SendApiLdsOpenReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_OPEN_REQ = 0x4800
****************************************************************************/
void SendApiLdsOpenReq ( RosTaskIdType Src,
                         ApiLdsDeviceIdType DeviceId,        /*!< The device id of the
                                                                remote device.
                                                                Set to 0 if connection is
                                                                requested by a PP connecting
                                                                to a FP. 
                                                                Set to handset id if
                                                                connection is requested from
                                                                FP to PP. */
                         ApiLdsPortNumberType Port,          /*!< The port number used.
                                                                Must be 1079 for class 3/4. */
                         ApiCcBasicServiceType BasicService,  /*!< Class 4 only is
                                                                 supported in the current
                                                                 implementation. */
                         ApiLdsDataInterfaceType DataInterface,
                                                             /*!< Specifies whether SDU
                                                                data is exchanged between
                                                                the API and the application
                                                                in mails or by direct memory
                                                                access. */
                         ApiLdsEventCbType Callback,         /*!< Pointer to call back
                                                                function used when the
                                                                direct memory based data
                                                                interface is used. Set to
                                                                NULL if mail based data
                                                                interface is used. */
                         rsuint16 InfoElementLength,         /*!< The length of the Data
                                                                Information Element.
                                                                Reserved for future
                                                                extension of the API. Must
                                                                be set to 0. */
                         rsuint8 InfoElement[1]);            /*!< Reserved for future
                                                                extension of the API. */

/****************************************************************************
* FUNCTION:      SendApiLdsOpenRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_OPEN_RES = 0x4803
****************************************************************************/
void SendApiLdsOpenRes ( RosTaskIdType Src,
                         ApiLdsDeviceIdType DeviceId,        /*!< The device id of the
                                                                remote device. */
                         ApiLdsPortNumberType Port,          /*!< The port number used. */
                         RsStatusType Status,                /*!< Indicates whether the
                                                                call is accepted or not.
                                                                RSS_REJECTED is used to
                                                                indicate that the call is
                                                                rejected by the user / host
                                                                and RSS_SUCCESS is used to
                                                                indicate that the virtual
                                                                call is accepted. */
                         ApiLdsDataInterfaceType DataInterface,
                                                             /*!< Specifies whether SDU
                                                                data is exchanged between
                                                                the API and the application
                                                                in mails or by direct memory
                                                                access. */
                         ApiLdsEventCbType Callback,         /*!< Pointer to call back
                                                                function. Can be used when
                                                                the application and the API
                                                                are implemented in the same
                                                                memory space and the mail
                                                                based data interface is not
                                                                used. Set to NULL if not
                                                                used. */
                         rsuint16 InfoElementLength,         /*!< The length of the Data
                                                                Information Element.
                                                                Reserved for future
                                                                extension of the API. Must
                                                                be set to 0. */
                         rsuint8 InfoElement[1]);            /*!< Reserved for future
                                                                extension of the API. */

/****************************************************************************
* FUNCTION:      SendApiLdsCloseReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_CLOSE_REQ = 0x4804
****************************************************************************/
void SendApiLdsCloseReq ( RosTaskIdType Src,
                          ApiLdsDeviceIdType DeviceId,       /*!< The device id of the
                                                                remote device. */
                          ApiLdsPortNumberType Port,         /*!< The port number used. */
                          ApiCcReleaseReasonType Reason);    /*!< Release reason. */

/****************************************************************************
* FUNCTION:      SendApiLdsRejectReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_REJECT_REQ = 0x4807
****************************************************************************/
void SendApiLdsRejectReq ( RosTaskIdType Src,
                           ApiLdsDeviceIdType DeviceId,      /*!< The device id of the
                                                                remote device. */
                           ApiLdsPortNumberType Port,        /*!< The port number used. */
                           ApiCcReleaseReasonType Reason);   /*!< Reject reason. */

/****************************************************************************
* FUNCTION:      SendApiLdsTxDataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_TX_DATA_REQ = 0x4821
****************************************************************************/
void SendApiLdsTxDataReq ( RosTaskIdType Src,
                           ApiLdsDeviceIdType DeviceId,      /*!< The device id of the
                                                                remote device. */
                           ApiLdsPortNumberType Port,        /*!< The port number. */
                           ApiLdsSduStateType SduState,      /*!< Indicates if the mail contains:
                                                                A complete SDU.
                                                                First fragment of the SDU.
                                                                Continuation fragment of
                                                                the SDU.
                                                                Last fragment of the SDU. */
                           rsbool More,                      /*!< Used as followed if
                                                                the chopping option is used:
                                                                FALSE: This is the last
                                                                segment (or the only one) of
                                                                an application packet.
                                                                TRUE: The next segment of
                                                                the same application packet
                                                                follows in next SDU 
                                                                Should be set to FALSE (0)
                                                                if chopping is not used. */
                           rsuint8 SequenceNumber,           /*!< Set to 0 for the first
                                                                time this mail is sent and
                                                                incremented by one for
                                                                subsequent mails. Used to
                                                                detect missing TX data
                                                                fragments due to e.g. TX
                                                                buffer overrun. */
                           rsuint16 DataLength,              /*!< The size in bytes of
                                                                the data parameter. */
                           rsuint8 Data[1]);                 /*!< The SDU data. */

/****************************************************************************
* FUNCTION:      SendApiLdsSetFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_SET_FEATURES_REQ = 0x4830
****************************************************************************/
void SendApiLdsSetFeaturesReq ( RosTaskIdType Src,
                                ApiLdsFeatureType ApiLdsFeature);
                                                             /*!< Requested features */

/****************************************************************************
* FUNCTION:      SendApiLdsGetFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LDS_GET_FEATURES_REQ = 0x4832
****************************************************************************/
void SendApiLdsGetFeaturesReq ( RosTaskIdType Src );



/****************************************************************************
*                             Function prototypes
****************************************************************************/
/****************************************************************************
*  FUNCTION:       ApiLdsSendData
*
*  RETURNS :       Returns:
                   RSS_SUCCES if all data is copied to internal TX buffer and
                   the BufferPtr buffer can be reused or freed by the application.
                   RSS_PENDING if the API could not copy all the data from the
                   BufferPtr buffer to the internal TX buffer. The application
                   must NOT free or reuse the buffer to an ALEV_TX_DONE event
                   has been received.
                   ?RSS_error_code?  if an error has been detected. The
                   application must try again later or disconnect the data
                   connection.
*
*  DESCRIPTION:    This function is used to request the API to start the
                   transmission of the data packet specified. A reference to
                   the buffer is stored internally in the API and the
                   application must not free/reuse the buffer before it has
                   been sent completely, which is indicted by the ALEV_TX_DONE
                   event. The API reads from the buffer in chunks as the data
                   is copied to the TX holding buffer used by the lower layer
                   (LU10). It is therefore important the TX buffer specified is
                   linear and accessible by memcpy() called within the API.  
                   
                   Fragmentation of SDU?s are supported to reduce the over all
                   buffer requirements. Fragmentation of SDU?s on this level
                   should be used carefully as it is not possible to send
                   another SDU before all fragments of a SDU has been sent!
****************************************************************************/
RsStatusType ApiLdsSendData(ApiLdsDeviceIdType DeviceId,     /*!< The device id of the
                                                                remote device. */
                            ApiLdsPortNumberType Port,       /*!< The port number. */
                            ApiLdsSduStateType SduState,     /*!< Indicates if the
                                                                buffer contains:
                                                                A complete SDU.
                                                                First fragment of the SDU.
                                                                Continuation fragment of
                                                                the SDU.
                                                                Last fragment of the SDU. */
                            rsbool More,                     /*!< Used as followed if
                                                                the chopping option is used:
                                                                FALSE: This is the last
                                                                segment (or the only one) of
                                                                an application packet.
                                                                TRUE: The next segment of
                                                                the same application packet
                                                                follows in next SDU 
                                                                Should be set to FALSE (0)
                                                                if chopping is not used. */
                            rsuint16 Size,                   /*!< The size in bytes of
                                                                the buffer. */
                            const rsuint8 *BufferPtr);       /*!< Pointer to linear data
                                                                packet/buffer. */

/****************************************************************************
*  FUNCTION:       ApiLdsReceiveData
*
*  RETURNS :       RSS_SUCCESS if data is received/copied to RX buffer.
                   RSS_NO_DATA if no RX data was ready.
*
*  DESCRIPTION:    This function is used to read the data from the buffer
                   holding the SDU or fragment of a SDU received. The
                   application must do the reassembly of the SDU in case it is
                   delivered in multiple fragments. This approach is selected
                   to reduce the buffer needed in the API and to enable the
                   application to deliver the SDU data to the desired memory
                   location directly (without having to copy the SDU data an
                   extra time) or pass the received data on the fly as it
                   receives. 
****************************************************************************/
RsStatusType ApiLdsReceiveData(ApiLdsDeviceIdType DeviceId,  /*!< The device id of the
                                                                remote device. */
                               ApiLdsPortNumberType *PortPtr,
                                                             /*!< Output indication the
                                                                port number the SDU is
                                                                received on. */
                               ApiLdsSduStateType *SduStatePtr,
                                                             /*!< Output indicating if
                                                                the buffer contains:
                                                                A complete SDU.
                                                                First fragment of the SDU.
                                                                Continuation fragment of
                                                                the SDU.
                                                                Last fragment of the SDU. */
                               rsbool *MorePtr,              /*!< Output used as
                                                                followed if the chopping
                                                                option is used:
                                                                FALSE: This is the last
                                                                segment (or the only one) of
                                                                an application packet.
                                                                TRUE: The next segment of
                                                                the same application packet
                                                                follows in next SDU 
                                                                Set to FALSE (0) if
                                                                chopping is not used. */
                               rsuint16 *SizePtr,            /*!< The size in bytes of
                                                                the buffer specified by
                                                                BufferPtr when the function
                                                                is called and the actual
                                                                number of bytes copied when
                                                                the function returns. */
                               rsuint8 *BufferPtr);          /*!< Pointer to RX buffer
                                                                whereto this function copies
                                                                the data received. */

/****************************************************************************
*  FUNCTION:       ApiLdsGetReceivedDataSize
*
*  RETURNS :       The length in bytes of the next RX buffer ready for the
                   application. 0 is returned if no data is available.
*
*  DESCRIPTION:    This function is used to get the size of the next data
                   block/buffer ready to be read by the application. 
****************************************************************************/
rsuint16 ApiLdsGetReceivedDataSize(ApiLdsDeviceIdType DeviceId,
                                                             /*!< The device id of the
                                                                remote device. */
                                   ApiLdsPortNumberType *PortPtr);
                                                             /*!< Output indication the
                                                                port number the SDU is
                                                                received on. */

/****************************************************************************
*  FUNCTION:       ApiLdsResume
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to resume receive, which was
                   previously suspended by the application (by returning FALSE
                   from the ApiLdsEventCbType callback).
****************************************************************************/
void ApiLdsResume(ApiLdsDeviceIdType DeviceId,               /*!< The device id of the
                                                                remote device. */
                  ApiLdsPortNumberType Port);                /*!< The port number. */


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APILDS_H */


