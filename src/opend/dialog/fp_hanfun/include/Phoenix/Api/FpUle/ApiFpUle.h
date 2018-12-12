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
* Definition of the ApiFpUle interface.
*/


#ifndef APIFPULE_H
#define APIFPULE_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API header files must be included. */
//#include <Api/ApiCfg.h> /* API configuration */
#include <Phoenix/Api/Types/ApiTypes.h> /* General types used. */

/****************************************************************************
*                               Macros/Defines
****************************************************************************/



#define  API_ULE_MTU_SIZE_DEFAULT  API_ULE_MTU_SIZE_MAX


/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

//#if (RTX_CORE_VERSION >= 0x0224)
//  #include <Standard/Common/RsPushPack1.h>
//#else
//  #pragma pack(push,1)
//#endif

/* Global mail primitives:
  API_FP_ULE_INIT_REQ = 0x4188,
  API_FP_ULE_INIT_CFM = 0x4189,
  API_FP_ULE_PVC_CONFIG_RES=0x41A2,
  API_FP_ULE_PVC_CONFIG_CFM=0x41A3,
  API_FP_ULE_PVC_CONFIG_REJ=0x41A4,
  API_FP_ULE_PVC_CONFIG_IND=0x41A5,
  API_FP_ULE_PVC_PENDING_IND=0x41A6,
  API_FP_ULE_PVC_PENDING_RES=0x41A7,
  API_FP_ULE_PVC_IWU_DATA_REQ=0x41A8,
  API_FP_ULE_PVC_IWU_DATA_IND=0x41A9,
  API_FP_ULE_GET_REGISTRATION_COUNT_REQ = 0x418C,
  API_FP_ULE_GET_REGISTRATION_COUNT_CFM = 0x418D,
  API_FP_ULE_DELETE_REGISTRATION_REQ = 0x4192,
  API_FP_ULE_DELETE_REGISTRATION_CFM = 0x4193,
  API_FP_ULE_GET_DEVICE_IPUI_REQ = 0x418E,
  API_FP_ULE_GET_DEVICE_IPUI_CFM = 0x418F,
  API_FP_ULE_TESTCMD_REQ = 0x418A,
  API_FP_ULE_DATA_IND = 0x4185,
  API_FP_ULE_DTR_IND = 0x4187,
  API_FP_ULE_DATA_REQ = 0x4186,
  API_FP_ULE_ABORT_DATA_REQ = 0x4190,
  API_FP_ULE_ABORT_DATA_CFM = 0x4191,
  API_FP_ULE_DATA_CFM = 0x418B,
  API_FP_ULE_FEATURES_REQ = 0x41A0,
  API_FP_ULE_FEATURES_CFM = 0x41A1,
The global mail primitives MUST be defined in Global.h! */



/*! This type is used to exchange features between the host and the DECT
   module. */
typedef enum RSENUMTAG(ApiFpUleFeatureType)
{
  API_FP_ULE_EXTENDED_TERMINAL_ID_SUPPORT = 0x01, /*!<  */
} RSENUM8(ApiFpUleFeatureType);


typedef enum RSENUMTAG(ApiFpUleError_t)
{
  API_FP_ULE_ERR_NO_ERROR           , /*!<  */
  API_FP_ULE_ERR_BUSY               , /*!<  */
  API_FP_ULE_ERR_BUFFER_OVERRUN     , /*!<  */
  API_FP_ULE_ERR_GLOBAL_ERROR       , /*!<  */
  API_FP_ULE_ERR_INTERFACE_MISMATCH , /*!<  */
  API_FP_ULE_ERR_UNSUPPORTED        , /*!<  */
  API_FP_ULE_ERR_RANGE_ERROR        , /*!<  */
  API_FP_ULE_ERR_NO_RESOURCES       , /*!<  */
  API_FP_ULE_ERR_DLC_NOT_READY      , /*!<  */
  API_FP_ULE_ERR_OVERSIZE_PACKET    , /*!<  */
  API_FP_ULE_ERR_UNKNOWN            , /*!<  */
  API_FP_ULE_ERR_MODE               , /*!<  */
  API_FP_ULE_ERR_UNLOCKED           , /*!<  */
  API_FP_ULE_ERR_CONNECTION         , /*!<  */
  API_FP_ULE_ERR_SIZE               , /*!<  */
  API_FP_ULE_ERR_COMMON_ERROR_COUNT , /*!<  */
  API_FP_ULE_ERR_TIMEOUT            , /*!<  */
  API_FP_ULE_ERR_NO_INSTANCE        , /*!<  */
  API_FP_ULE_ERR_NOT_LOCATED        , /*!<  */
  API_FP_ULE_ERR_NO_ACTIVE_SCALL    , /*!<  */
  API_FP_ULE_ERR_PVC_USER_REJ       , /*!<  */
  API_FP_ULE_ERR_PVC_SUSPENDED      , /*!<  */
  API_FP_ULE_ERR_FP_PVC_REQ         , /*!<  */
  API_FP_ULE_ERR_FP_PVC_SUSPENDED   , /*!<  */
  API_FP_ULE_ERR_FP_PVC_NONE_REJ    , /*!<  */
  API_FP_ULE_ERR_FP_PVC_SUSPEND_REJ , /*!<  */
  API_FP_ULE_ERR_FP_PVC_RESUME_REJ  , /*!<  */
  API_FP_ULE_ERR_PVC_MTU_PT_REJ     , /*!<  */
  API_FP_ULE_ERR_PVC_MTU_FT_REJ     , /*!<  */
  API_FP_ULE_ERR_PVC_WIN_REJ        , /*!<  */
  API_FP_ULE_ERR_PVC_LT_REJ         , /*!<  */
  API_FP_ULE_ERR_PVC_PID_REJ        , /*!<  */
  API_FP_ULE_ERR_FP_CCM             , /*!<  */
} RSENUM8(ApiFpUleError_t);

/*! ULE protocol identifier */
typedef enum RSENUMTAG(ApiFpUleProtocolId_t)
{
  API_ULE_PROTOCOL_UNDEFINED   = 0,    /*!< Undefined protocol */
  API_ULE_PROTOCOL_FUN_1       = 1,    /*!< HAN/FUN protocol Ver. 1 */
  API_ULE_PROTOCOL_PROPRIETARY = 0x80, /*!< Proprietary protocol */
} RSENUM8(ApiFpUleProtocolId_t);

/*! ULE protocol version */
typedef enum RSENUMTAG(ApiFpUleProtocolVer_t)
{
  API_ULE_PROTOCOL_VERSION_0  = 0,    /*!< ULE protocol version 0 */
  API_ULE_PROTOCOL_VERSION_1  = 1,    /*!< ULE protocol version 1 */
  API_ULE_PROTOCOL_VERSION_7F = 0x7F, /*!< ULE protocol, version  0x7f  (max) */
} RSENUM8(ApiFpUleProtocolVer_t);

/*! ULE PVC configuration parameter for DLC window size */
typedef enum RSENUMTAG(ApiFpUleWindowSize_t)
{
  API_ULE_WINDOW_SIZE_UNDEF   = 0,  /*!< Undefined, use default or PP value */
  API_ULE_WINDOW_SIZE_MIN     = 8,  /*!< DLC minimum window size */
  API_ULE_WINDOW_SIZE_DEFAULT = 16, /*!< DLC default window size */
  API_ULE_WINDOW_SIZE_MAX     = 32, /*!< DLC maximum window size */
} RSENUM8(ApiFpUleWindowSize_t);

/*! ULE PVC configuration parameter for MTU size */
typedef enum RSENUMTAG(ApiFpUleMtuSize_t)
{
  API_ULE_MTU_SIZE_UNDEF = 0,   /*!< Undefined, use default or PP value */
  API_ULE_MTU_SIZE_MIN   = 32,  /*!< MTU minimum size */
  API_ULE_MTU_SIZE_64    = 64,  /*!<  */
  API_ULE_MTU_SIZE_128   = 128, /*!<  */
  API_ULE_MTU_SIZE_256   = 256, /*!<  */
  API_ULE_MTU_SIZE_MAX   = 500, /*!< MTU maximum size  (Default value) */
} RSENUM16(ApiFpUleMtuSize_t);

/*! ULE PVC configuration parameter for MTU lifetime (determines number of
   retransmissions) */
typedef enum RSENUMTAG(ApiFpUleMtuLifetime_t)
{
  API_ULE_MTU_LIFETIME_UNDEF   = 0,    /*!< Undefined, use default or PP value */
  API_ULE_MTU_LIFETIME_MIN     = 1,    /*!< MTU minimum lifetime in frames */
  API_ULE_MTU_LIFETIME_3       = 3,    /*!<  */
  API_ULE_MTU_LIFETIME_DEFAULT = 7,    /*!< default */
  API_ULE_MTU_LIFETIME_15      = 15,   /*!<  */
  API_ULE_MTU_LIFETIME_MAX     = 1008, /*!< MTU  maximum lifetime in frames */
} RSENUM16(ApiFpUleMtuLifetime_t);

/*! ULE PVC configuration initiator */
typedef enum RSENUMTAG(ApiFpUlePageCh_t)
{
  API_ULE_BROADCAST_CH =1, /*!< This is a broadcast channel */
  API_ULE_PAGING_CH    =2, /*!< This is a paging channel */
} RSENUM8(ApiFpUlePageCh_t);

/*! ULE paging channel parameters, Id and periodicity.                     
                                                   
    Max value for Id  is dependent of  the periodicity.   
    Max value for Pexp is 15,  that?s an max periodicity on 32768  frames */
typedef struct ApiFpUlePage_t
{
  ApiFpUlePageCh_t  Descriptor;         /*!< Selects broadcast or paging */
  rsuint16  Id;                         /*!< Paging id */
  rsuint8  Pexp;                        /*!< Periodicity in frames  = 2^Pexp  (max 15) */
} PACKED_STRUCT ApiFpUlePage_t;

/*! ULE PVC configuration initiator */
typedef enum RSENUMTAG(ApiFpUlePvcInitiator_t)
{
  API_ULE_PP_INITIATOR =0, /*!< PP is supposed  to initiate service change */
  API_ULE_FP_INITIATOR =1, /*!< FP is supposed  to initiate service change */
} RSENUM8(ApiFpUlePvcInitiator_t);

/*! Defines ULE Protocol parameters */
typedef struct ApiFpUleProtocol_t
{
  ApiFpUleProtocolId_t  Id;             /*!< 0 undefined protocol 
                                           1 ULE FUN #1 protocol
                                           >127 Proprietary ULE protocol */
  ApiFpUleProtocolVer_t  Ver;           /*!< 7 bit Protocol version number, default  0 */
  rsuint16  Emc;                        /*!< EMC code */
} PACKED_STRUCT ApiFpUleProtocol_t;


/*! Mail without parameters. */
typedef struct ApifpuleEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} PACKED_STRUCT ApifpuleEmptySignalType;

/*! Initialize ULE operation of the FP. Until this mail is sent, the FP
   will not set the ULE capabilities bits, and already enrolled ULE devices
   will not function properly. The possible configurations will depend on the
   memory available for ULE operation in the target. See also
   API_FP_ULE_INIT_CFM. If ULE support is not required simply do not send this
   mail. This mail should only be sent once. */
typedef struct ApiFpUleInitReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_INIT_REQ = 0x4188 */
  rsuint16 MaxUlpDevices;               /*!< Maximum ULE devices allowed enrolling. If
                                           this is larger than number of subscriptions, the
                                           value is truncated.  If more than MaxUlpDevices
                                           are already registered, they will all be allowed
                                           to work. Range 1-0xFF. */
} PACKED_STRUCT ApiFpUleInitReqType;

/*! ULE initialization confirmation */
typedef struct ApiFpUleInitCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_INIT_CFM = 0x4189 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint16 MaxUlpDevices;               /*!< Maximum ULE devices supported by the FP.
                                            0 if not known. */
  rsuint16 UpLinkBuffers;               /*!< Number of ULE uplink buffers allocated.
                                            0 if not known */
} PACKED_STRUCT ApiFpUleInitCfmType;

/*! Used to setup the ULE protocol data, shall only be sent after the ULE
   API is initialized.
    During the ULE protocol configuration other mails may be received or
   transmitted as part of the PVC configuration, see MSC for description. */
typedef struct ApiFpUlePvcConfigResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_PVC_CONFIG_RES=0x41A2 */
  ApiTerminalIdType TerminalId;         /*!< Terminal Id. */
  ApiFpUlePvcInitiator_t Initiator;     /*!< Initiator  PT=0,   FT otherwise  (default
                                           PT) */
  ApiFpUleMtuSize_t MtuPtSize;          /*!< MTU size in PT->FT direction */
  ApiFpUleMtuSize_t MtuFtSize;          /*!< MTU size in FT->PT direction */
  ApiFpUleMtuLifetime_t MtuLifetime;    /*!< MAC layer maximum  lifetime */
  ApiFpUleWindowSize_t WindowSize;      /*!< DLC layer window size */
  rsuint8 ProtocolCount;                /*!< Number of defined ULE  protocols */
  ApiFpUleProtocol_t Protocol[1];       /*!< ULE protocols */
} PACKED_STRUCT ApiFpUlePvcConfigResType;

/*! Received  if and when the PVC configuration succeeded */
typedef struct ApiFpUlePvcConfigCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_PVC_CONFIG_CFM=0x41A3 */
  ApiTerminalIdType TerminalId;         /*!< Terminal Id. */
  ApiFpUleProtocolId_t ProtocolId;      /*!< ULE protocol */
  ApiFpUleMtuSize_t MtuPtSize;          /*!< MTU size in PT->FT direction */
  ApiFpUleMtuSize_t MtuFtSize;          /*!< MTU size in FT->PT direction */
  ApiFpUleMtuLifetime_t MtuLifetime;    /*!< MAC layer maximum  lifetime */
  ApiFpUleWindowSize_t WindowSize;      /*!< DLC layer window size */
} PACKED_STRUCT ApiFpUlePvcConfigCfmType;

/*! Received if the PVC configuration failed. */
typedef struct ApiFpUlePvcConfigRejType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_PVC_CONFIG_REJ=0x41A4 */
  ApiTerminalIdType TerminalId;         /*!< Terminal Id. */
  ApiFpUleError_t Reason;               /*!< Indicates why the PVC configuration failed */
  rsuint16 Value;                       /*!< If  possible, value of  rejected parameter */
} PACKED_STRUCT ApiFpUlePvcConfigRejType;

/*! Received if PVC needs a new configuration or a reconfiguration. */
typedef struct ApiFpUlePvcConfigIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_PVC_CONFIG_IND=0x41A5 */
  ApiTerminalIdType TerminalId;         /*!< Terminal Id. */
} PACKED_STRUCT ApiFpUlePvcConfigIndType;

/*! Received during PVC configuration, indicates that proprietary protocol
   configuration can be started. */
typedef struct ApiFpUlePvcPendingIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_PVC_PENDING_IND=0x41A6 */
  ApiTerminalIdType TerminalId;         /*!< Terminal Id. */
  ApiFpUleProtocolId_t ProtocolId;      /*!< ID of the ULE selected protocol */
} PACKED_STRUCT ApiFpUlePvcPendingIndType;

/*! Send when the proprietary configuration is done. */
typedef struct ApiFpUlePvcPendingResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_PVC_PENDING_RES=0x41A7 */
  ApiTerminalIdType TerminalId;         /*!< Terminal Id. */
  ApiFpUleError_t Status;               /*!< If no errors then PVC configuration is
                                           continued, otherwise the configuration is
                                           terminated. */
  rsuint8 PageChCount;
  ApiFpUlePage_t PageChannel[1];
} PACKED_STRUCT ApiFpUlePvcPendingResType;

/*! Transmitted during the proprietary protocol configuration */
typedef struct ApiFpUlePvcIwuDataReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_PVC_IWU_DATA_REQ=0x41A8 */
  ApiTerminalIdType TerminalId;         /*!< Terminal Id. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the 
                                           ApiInfoElementType (which is defined in the
                                           Phoenix_PP_API_Types.doc)
                                           
                                            */
} PACKED_STRUCT ApiFpUlePvcIwuDataReqType;

/*! Received during the proprietary protocol configuration */
typedef struct ApiFpUlePvcIwuDataIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_PVC_IWU_DATA_IND=0x41A9 */
  ApiTerminalIdType TerminalId;         /*!< Terminal Id. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the 
                                           ApiInfoElementType (which is defined in the
                                           Phoenix_PP_API_Types.doc)
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                            */
} PACKED_STRUCT ApiFpUlePvcIwuDataIndType;

/*! This command is used by the MMI to request the maximum number of ULE 
   devices that can be registered to the FP, the number of devices currently
   registered and a bitmask giving the device ID?s, by which the matching
   IPUI?s can be retrieved. */
typedef ApifpuleEmptySignalType ApiFpUleGetRegistrationCountReqType;

/*! This mail is used by the API to confirm the
   API_FP_ULE_GET_REGISTRATION_COUNT_REQ command. */
typedef struct ApiFpUleGetRegistrationCountCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_GET_REGISTRATION_COUNT_CFM = 0x418D */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint8 MaxNoHs;                      /*!< Max numbers of handsets bit used, always
                                           placed in start of bitmask and always zero, may
                                           be used as offset into DeviceIdBitArr */
  rsuint8 MaxNoDevices;                 /*!< The maximum number of ULE devices that can
                                           be registered. */
  rsuint8 NoDevices;                    /*!< The number of ULE devices registered
                                           currently. */
  rsuint8 Length;                       /*!< Byte length of DeviceIdBitArr */
  rsuint8 DeviceIdBitArr[1];            /*!< Bit array of registered ULE device Id?s. */
} PACKED_STRUCT ApiFpUleGetRegistrationCountCfmType;
/*! This mail is used by the API to locally delete the devices registration
   data. No attempt to delete data in the actual device is done, if this is
   needed use the MM function instead. */
typedef struct ApiFpUleDeleteRegistrationReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_DELETE_REGISTRATION_REQ = 0x4192 */
  ApiTerminalIdType TerminalId;         /*!< The Id of the device that should be
                                           deleted. */
} PACKED_STRUCT ApiFpUleDeleteRegistrationReqType;

/*! This mail is used to inform the API of the result of deleting the
   registration data. */
typedef struct ApiFpUleDeleteRegistrationCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_DELETE_REGISTRATION_CFM = 0x4193 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiTerminalIdType TerminalId;         /*!< The Id of the deleted device. */
} PACKED_STRUCT ApiFpUleDeleteRegistrationCfmType;

/*! This command is used by the MMI to request the IPUI of one of the ULE
   devices registered. */
typedef struct ApiFpUleGetDeviceIpuiReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_GET_DEVICE_IPUI_REQ = 0x418E */
  ApiTerminalIdType TerminalId;         /*!< The Id of the Device that the MCU wants the
                                           IPUI for. */
} PACKED_STRUCT ApiFpUleGetDeviceIpuiReqType;

/*! This mail is used by the API to confirm the
   API_FP_ULE_GET_DEVICE_IPUI_REQ command. */
typedef struct ApiFpUleGetDeviceIpuiCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_GET_DEVICE_IPUI_CFM = 0x418F */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiTerminalIdType TerminalId;         /*!< The Id for which the IPUI is read. */
  rsuint8 IPUI[5];                      /*!< The IPUI. */
} PACKED_STRUCT ApiFpUleGetDeviceIpuiCfmType;

/*! Undocumented  - development/test purpose only */
typedef struct ApiFpUleTestcmdReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_TESTCMD_REQ = 0x418A */
  ApiTerminalIdType TerminalId;         /*!< Portable part number */
  rsuint8 Cmd;                          /*!< Test command */
  rsuint8 Length;                       /*!< Test command data length */
  rsuint8 Data[1];                      /*!< Test command  data */
} PACKED_STRUCT ApiFpUleTestcmdReqType;

/*! This mail indicates that data has been received from the PP. */
typedef struct ApiFpUleDataIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_DATA_IND = 0x4185 */
  ApiTerminalIdType TerminalId;         /*!< Portable part number */
  rsuint16 Length;                       /*!< Length of data */
  rsuint8 Data[1];                      /*!< Data. */
} PACKED_STRUCT ApiFpUleDataIndType;

/*! ?Data transmit ready?  indication. Means that any previous packet has
   been transmitted and the ULE-API is ready for a new data transmit via
   API_FP_ULE_DATA_REQ. */
typedef struct ApiFpUleDtrIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_DTR_IND = 0x4187 */
  ApiTerminalIdType TerminalId;         /*!< Portable part number */
  RsStatusType Status;                  /*!< Status of last data transmission, 
                                           RSS_SUCCESS if data has been transmitted and
                                           acknowledge  otherwise  RSS_FAILED. */
} PACKED_STRUCT ApiFpUleDtrIndType;

/*! This mail is used by the API for sending data to the PP. */
typedef struct ApiFpUleDataReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_DATA_REQ = 0x4186 */
  ApiTerminalIdType TerminalId;         /*!< Portable part number */
  rsuint8 DlcCtrl;                      /*!< DLC control data
                                             Bit7 =  0/1   1= Use dummy bearer  paging.
                                            */
  rsuint16 Length;                       /*!< Length */
  rsuint8 Data[1];                      /*!< Data. */
} PACKED_STRUCT ApiFpUleDataReqType;

typedef struct ApiFptraceType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_DATA_REQ = 0x4186 */

  rsuint8 Data[1];                      /*!< Data. */
} PACKED_STRUCT ApiFptraceType;

/*! This mail is used by the API for aborting an already scheduled data
   transmission to the PP.
     Only aborted if PP not has started transmitting. */
typedef struct ApiFpUleAbortDataReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_ABORT_DATA_REQ = 0x4190 */
  ApiTerminalIdType TerminalId;         /*!< Portable part number */
} PACKED_STRUCT ApiFpUleAbortDataReqType;

/*! This mail is used by the API for informing PP about status of the
   aborted. data transmission. */
typedef struct ApiFpUleAbortDataCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_ABORT_DATA_CFM = 0x4191 */
  ApiTerminalIdType TerminalId;         /*!< Portable part number */
  RsStatusType Status;                  /*!< RSS_BAD_ADDRESS  
                                             TPUI not avaible
                                           RSS_UNAVAILABLE 
                                             Not setup to transmit data
                                           RSS_BUSY  
                                             Transmitting data is started
                                           RSS_NO_DATA
                                             Zero data length 
                                           RSS_SUCCESS */
  rsuint8 DlcCtrl;                      /*!< DLC control data */
  rsuint16 Length;                       /*!< Length */
  rsuint8 Data[1];                      /*!< Data. */
} PACKED_STRUCT ApiFpUleAbortDataCfmType;

/*! Confirmation that API_FP_ULE_DATA_REQ has been handled. */
typedef struct ApiFpUleDataCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_DATA_CFM = 0x418B */
  ApiTerminalIdType TerminalId;         /*!< Portable part number */
  RsStatusType Status;                  /*!< Status for the data request */
} PACKED_STRUCT ApiFpUleDataCfmType;

/*! This command is used to enable/disable features in the FpUle API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiFpUleFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_FEATURES_REQ = 0x41A0 */
  ApiFpUleFeatureType ApiFpUleFeature;  /*!< Requested features */
} PACKED_STRUCT ApiFpUleFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiFpUleFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_ULE_FEATURES_CFM = 0x41A1 */
  RsStatusType Status;
  ApiFpUleFeatureType ApiFpUleFeature;  /*!< Supported features */
} PACKED_STRUCT ApiFpUleFeaturesCfmType;

#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiFpUleInitReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_INIT_REQ = 0x4188
****************************************************************************/
void SendApiFpUleInitReq ( RosTaskIdType Src,
                           rsuint16 MaxUlpDevices);          /*!< Maximum ULE devices
                                                                allowed enrolling. If this
                                                                is larger than number of
                                                                subscriptions, the value is
                                                                truncated.  If more than
                                                                MaxUlpDevices are already
                                                                registered, they will all be
                                                                allowed to work. Range
                                                                1-0xFF. */

/****************************************************************************
* FUNCTION:      SendApiFpUlePvcConfigRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_PVC_CONFIG_RES=0x41A2
****************************************************************************/
void SendApiFpUlePvcConfigRes ( RosTaskIdType Src,
                                ApiTerminalIdType TerminalId,
                                                             /*!< Terminal Id. */
                                ApiFpUlePvcInitiator_t Initiator,
                                                             /*!< Initiator  PT=0,   FT
                                                                otherwise  (default PT) */
                                ApiFpUleMtuSize_t MtuPtSize,  /*!< MTU size in PT->FT
                                                                 direction */
                                ApiFpUleMtuSize_t MtuFtSize,  /*!< MTU size in FT->PT
                                                                 direction */
                                ApiFpUleMtuLifetime_t MtuLifetime,
                                                             /*!< MAC layer maximum 
                                                                lifetime */
                                ApiFpUleWindowSize_t WindowSize,
                                                             /*!< DLC layer window size */
                                rsuint8 ProtocolCount,       /*!< Number of defined ULE 
                                                                protocols */
                                ApiFpUleProtocol_t Protocol[1]);
                                                             /*!< ULE protocols */

/****************************************************************************
* FUNCTION:      SendApiFpUlePvcPendingRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_PVC_PENDING_RES=0x41A7
****************************************************************************/
void SendApiFpUlePvcPendingRes ( RosTaskIdType Src,
                                 ApiTerminalIdType TerminalId,
                                                             /*!< Terminal Id. */
                                 ApiFpUleError_t Status,     /*!< If no errors then PVC
                                                                configuration is continued,
                                                                otherwise the configuration
                                                                is terminated. */
                                 rsuint8 PageChCount,        /*!<  */
                                 ApiFpUlePage_t PageChannel[1]);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiFpUlePvcIwuDataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_PVC_IWU_DATA_REQ=0x41A8
****************************************************************************/
void SendApiFpUlePvcIwuDataReq ( RosTaskIdType Src,
                                 ApiTerminalIdType TerminalId,
                                                             /*!< Terminal Id. */
                                 rsuint16 InfoElementLength,  /*!< The length of the
                                                                 Data Information Element */
                                 rsuint8 InfoElement[1]);    /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                Phoenix_PP_API_Types.doc)
                                                                
                                                                 */

/****************************************************************************
* FUNCTION:      SendApiFpUleGetRegistrationCountReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_GET_REGISTRATION_COUNT_REQ = 0x418C
****************************************************************************/
void SendApiFpUleGetRegistrationCountReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpUleDeleteRegistrationReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_DELETE_REGISTRATION_REQ = 0x4192
****************************************************************************/
void SendApiFpUleDeleteRegistrationReq ( RosTaskIdType Src,
                                         ApiTerminalIdType TerminalId);
                                                             /*!< The Id of the device
                                                                that should be deleted. */

/****************************************************************************
* FUNCTION:      SendApiFpUleGetDeviceIpuiReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_GET_DEVICE_IPUI_REQ = 0x418E
****************************************************************************/
void SendApiFpUleGetDeviceIpuiReq ( RosTaskIdType Src,
                                    ApiTerminalIdType TerminalId);
                                                             /*!< The Id of the Device
                                                                that the MCU wants the IPUI
                                                                for. */

/****************************************************************************
* FUNCTION:      SendApiFpUleTestcmdReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_TESTCMD_REQ = 0x418A
****************************************************************************/
void SendApiFpUleTestcmdReq ( RosTaskIdType Src,
                              ApiTerminalIdType TerminalId,  /*!< Portable part number */
                              rsuint8 Cmd,                   /*!< Test command */
                              rsuint8 Length,                /*!< Test command data
                                                                length */
                              rsuint8 Data[1]);              /*!< Test command  data */

/****************************************************************************
* FUNCTION:      SendApiFpUleDataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_DATA_REQ = 0x4186
****************************************************************************/
void SendApiFpUleDataReq ( RosTaskIdType Src,
                           ApiTerminalIdType TerminalId,     /*!< Portable part number */
                           rsuint8 DlcCtrl,                  /*!< DLC control data
                                                                  Bit7 =  0/1   1= Use
                                                                dummy bearer  paging.
                                                                 */
                           rsuint16 Length,                   /*!< Length */
                           rsuint8 Data[1]);                 /*!< Data. */

/****************************************************************************
* FUNCTION:      SendApiFpUleAbortDataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_ABORT_DATA_REQ = 0x4190
****************************************************************************/
void SendApiFpUleAbortDataReq ( RosTaskIdType Src,
                                ApiTerminalIdType TerminalId);
                                                             /*!< Portable part number */

void SendApiFpTraceReq ( RosTaskIdType Src,
                           rsuint16 Length,
                           rsuint8 Data[1]);
/****************************************************************************
* FUNCTION:      SendApiFpUleAbortDataCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_ABORT_DATA_CFM = 0x4191
****************************************************************************/
void SendApiFpUleAbortDataCfm ( RosTaskIdType Src,
                                ApiTerminalIdType TerminalId,
                                                             /*!< Portable part number */
                                RsStatusType Status,         /*!< RSS_BAD_ADDRESS  
                                                                  TPUI not avaible
                                                                RSS_UNAVAILABLE 
                                                                  Not setup to transmit data
                                                                RSS_BUSY  
                                                                  Transmitting data is started
                                                                RSS_NO_DATA
                                                                  Zero data length 
                                                                RSS_SUCCESS */
                                rsuint8 DlcCtrl,             /*!< DLC control data */
                                rsuint16 Length,              /*!< Length */
                                rsuint8 Data[1]);            /*!< Data. */

/****************************************************************************
* FUNCTION:      SendApiFpUleFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_FEATURES_REQ = 0x41A0
****************************************************************************/
void SendApiFpUleFeaturesReq ( RosTaskIdType Src,
                               ApiFpUleFeatureType ApiFpUleFeature);
                                                             /*!< Requested features */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPULE_H */


