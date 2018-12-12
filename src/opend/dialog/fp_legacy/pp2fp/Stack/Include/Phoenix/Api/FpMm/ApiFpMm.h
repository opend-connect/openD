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
* Definition of the ApiFpMm interface.
*/


#ifndef APIFPMM_H
#define APIFPMM_H

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

/*! This type describes features available in this API. */
#define API_FP_MM_EXTENDED_TERMINAL_ID_SUPPORT 0x01

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_FP_MM_GET_ID_REQ = 0x4004,
  API_FP_MM_GET_ID_CFM = 0x4005,
  API_FP_MM_GET_MODEL_REQ = 0x4006,
  API_FP_MM_GET_MODEL_CFM = 0x4007,
  API_FP_MM_SET_ACCESS_CODE_REQ = 0x4008,
  API_FP_MM_SET_ACCESS_CODE_CFM = 0x4009,
  API_FP_MM_GET_ACCESS_CODE_REQ = 0x400A,
  API_FP_MM_GET_ACCESS_CODE_CFM = 0x400B,
  API_FP_MM_GET_REGISTRATION_COUNT_REQ = 0x4100,
  API_FP_MM_GET_REGISTRATION_COUNT_CFM = 0x4101,
  API_FP_MM_GET_HANDSET_IPUI_REQ = 0x4109,
  API_FP_MM_GET_HANDSET_IPUI_CFM = 0x410A,
  API_FP_MM_HANDSET_PRESENT_IND = 0x4108,
  API_FP_MM_STOP_PROTOCOL_REQ = 0x410B,
  API_FP_MM_START_PROTOCOL_REQ = 0x410D,
  API_FP_MM_HANDSET_DETACH_IND = 0x410E,
  API_FP_MM_EXT_HIGHER_LAYER_CAP2_REQ = 0x410C,
  API_FP_MM_GET_NAME_REQ = 0x4110,
  API_FP_MM_GET_NAME_CFM = 0x4111,
  API_FP_MM_SET_NAME_REQ = 0x4112,
  API_FP_MM_SET_NAME_CFM = 0x4113,
  API_FP_MM_SET_REGISTRATION_MODE_REQ = 0x4105,
  API_FP_MM_SET_REGISTRATION_MODE_CFM = 0x4106,
  API_FP_MM_REGISTRATION_COMPLETE_IND = 0x4107,
  API_FP_MM_REGISTRATION_FAILED_IND = 0x4104,
  API_FP_MM_DELETE_REGISTRATION_REQ = 0x4102,
  API_FP_MM_DELETE_REGISTRATION_CFM = 0x4103,
  API_FP_MM_HANDSET_DEREGISTERED_IND = 0x410F,
  API_FP_MM_REGISTRATION_MODE_DISABLED_IND = 0x4114,
  API_FP_MM_UNITDATA_REQ = 0x4180,
  API_FP_MM_ALERT_BROADCAST_REQ = 0x4182,
  API_FP_MM_START_PROTOCOL_PCM_SYNC_REQ = 0x4183,
  API_FP_MM_GET_FP_CAPABILITIES_REQ = 0x4170,
  API_FP_MM_GET_FP_CAPABILITIES_CFM = 0x4171,
  API_FP_MM_SET_FEATURES_REQ = 0x4160,
  API_FP_MM_SET_FEATURES_CFM = 0x4161,
  API_FP_MM_GET_FEATURES_REQ = 0x4162,
  API_FP_MM_GET_FEATURES_CFM = 0x4163,
End of mail primitives. */



/*! This enum defines start session reject types to the MMI */
typedef enum RSENUMTAG(ApiMmRejectReasonType)
{
  MM_REJ_NO_REJECT_REASON               = 0x00, /*!< No Reason. */
  MM_REJ_TPUI_UNKNOWN                   = 0x01, /*!<  */
  MM_REJ_IPUI_UNKNOWN                   = 0x02, /*!<  */
  MM_REJ_NETWORK_ASSIGNED_ID_UNKNOWN    = 0x03, /*!<  */
  MM_REJ_IPEI_NOT_ACCEPTED              = 0x05, /*!<  */
  MM_REJ_IPUI_NOT_ACCEPTED              = 0x06, /*!<  */
  MM_REJ_AUTH_FAILED                    = 0x10, /*!< Wrong AcCode */
  MM_REJ_NO_AUTH_ALGORITHM              = 0x11, /*!<  */
  MM_REJ_AUTH_ALGORITHM_NOT_SUPPORTED   = 0x12, /*!<  */
  MM_REJ_AUTH_KEY_NOT_SUPPORTED         = 0x13, /*!<  */
  MM_REJ_UPI_NOT_ENTERED                = 0x14, /*!<  */
  MM_REJ_NO_CIPHER_ALGORITHM            = 0x17, /*!<  */
  MM_REJ_CIPHER_ALGORITHM_NOT_SUPPORTED = 0x18, /*!<  */
  MM_REJ_CIPHER_KEY_NOT_SUPPORTED       = 0x19, /*!<  */
  MM_REJ_INCOMPATIBLE_SERVICE           = 0x20, /*!<  */
  MM_REJ_FALSE_LCE_REPLY                = 0x21, /*!<  */
  MM_REJ_LATE_LCE_REPLY                 = 0x22, /*!<  */
  MM_REJ_INVALID_TPUI                   = 0x23, /*!<  */
  MM_REJ_TPUI_ASSIGN_LIMIT_UNACCEPT     = 0x24, /*!<  */
  MM_REJ_UNSUFFICIENT_MEMORY            = 0x2F, /*!< Subscription database full */
  MM_REJ_OVERLOAD                       = 0x30, /*!<  */
  MM_REJ_TEST_CALL_BACK_NORM_ENBLOC     = 0x40, /*!<  */
  MM_REJ_TEST_CALL_BACK_NORM_PIECEWISE  = 0x41, /*!<  */
  MM_REJ_TEST_CALL_BACK_EMERG_ENBLOC    = 0x42, /*!<  */
  MM_REJ_TEST_CALL_BACK_EMERG_PIECEWISE = 0x43, /*!<  */
  MM_REJ_INVALID_MESSAGE                = 0x5F, /*!<  */
  MM_REJ_IE_ERROR                       = 0x60, /*!<  */
  MM_REJ_INVALID_IE_CONTENTS            = 0x64, /*!<  */
  MM_REJ_TIMER_EXPIRY                   = 0x70, /*!<  */
  MM_REJ_PLMN_NOT_ALLOWD                = 0x76, /*!<  */
  MM_REJ_LOCATION_AREA_NOT_ALLOWED      = 0x80, /*!<  */
  MM_REJ_NATIONAL_ROAMING_NOT_ALLOWED   = 0x81, /*!<  */
  MM_REJ_TERMINAL_IN_ACTIVE_CALL        = 0x90, /*!<  */
  MM_REJ_TERMINAL_IN_FWU_CALL           = 0x91, /*!<  */
  MM_REJ_MM_TRANSACTION_ONGOING         = 0x92  /*!< No errors */
} RSENUM8(ApiMmRejectReasonType);

/*! This enum defines how the protocols can by synchronized via the PCM
   bus. */
typedef enum RSENUMTAG(ApiMmProtocolPcmSyncType)
{
  MM_START_PROTOCOL_PCM_SYNC_SLAVE            = 0x00, /*!< . */
  MM_START_PROTOCOL_PCM_SYNC_MASTER           = 0x01, /*!<  */
  MM_START_PROTOCOL_PCM_SYNC_SLAVE_1_FS_DELAY = 0x02, /*!<  */
} RSENUM8(ApiMmProtocolPcmSyncType);

/*! This enum defines how the protocols can by synchronized via the PCM
   bus. */
typedef enum RSENUMTAG(ApiMmRegistrationModeType)
{
  MM_REGISTRATION_MODE_DISABLED   = 0x00, /*!< Registration mode is enabled. */
  MM_REGISTRATION_MODE_CONTINUOUS = 0x01, /*!< Registration will stay enabled until it
                                             is disabled by host. */
  MM_REGISTRATION_MODE_SINGLE     = 0x02, /*!< Registration mode will automatically be
                                             disabled after one handset has been
                                             successfully registered. */
} RSENUM8(ApiMmRegistrationModeType);

/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiFpMmFeatureType;


/*! Mail without parameters. */
typedef struct ApifpmmEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApifpmmEmptySignalType;

/*! This command is used by the MMI to request the API to return a unique
   identifier for that particular FP. */
typedef ApifpmmEmptySignalType ApiFpMmGetIdReqType;

/*! This mail is used by the API to return the unique FP id to the MMI. */
typedef struct ApiFpMmGetIdCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_ID_CFM = 0x4005 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not */
  rsuint8 Id[5];                        /*!< The id of the FP. The RFPI of the FP is
                                           transmitted in the dummybearer and used as FP
                                           identification for the PPs when registering and
                                           locking. */
} ApiFpMmGetIdCfmType;

/*! This command is used to request a string indicating the model and
   manufacture. */
typedef ApifpmmEmptySignalType ApiFpMmGetModelReqType;

/*! This mail is used to confirm the API_FP_MM_GET_MODEL_REQ command. */
typedef struct ApiFpMmGetModelCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_MODEL_CFM = 0x4007 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not */
  ApiModelIdType ModelId;               /*!< The manufacture (MANIC) and model (MODIC)
                                           code of the FP. The EMC code of the FP is used as
                                           manufacture code. */
} ApiFpMmGetModelCfmType;

/*! This command is used to set the DECT access code. */
typedef struct ApiFpMmSetAccessCodeReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_SET_ACCESS_CODE_REQ = 0x4008 */
  rsuint8 Ac[4];                        /*!< The authentication code of the FP. This is
                                           the PIN code of the FP used to verify the user
                                           for registration. The dataformat is BCD and the
                                           string is 'F' terminated (unused nibbles are set
                                           to 'F').
                                           
                                           Example.
                                             AcCode = 1234
                                             AcCode[4] = { 0xFF, 0xFF, 0x12, 0x34 } */
} ApiFpMmSetAccessCodeReqType;

/*! This mail is used to confirm the API_FP_SET_ACCESS_CODE_REQ command. */
typedef struct ApiFpMmSetAccessCodeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_SET_ACCESS_CODE_CFM = 0x4009 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiFpMmSetAccessCodeCfmType;

/*! This command is used to get the DECT access code. */
typedef ApifpmmEmptySignalType ApiFpMmGetAccessCodeReqType;

/*! This mail is used to confirm the API_FP_GET_ACCESS_CODE_REQ command. */
typedef struct ApiFpMmGetAccessCodeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_ACCESS_CODE_CFM = 0x400B */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint8 Ac[4];                        /*!< The authentication code of the FP. This is
                                           the PIN code of the FP used to verify the user
                                           for registration. The dataformat is BCD and the
                                           string is 'F' terminated (unused nibbles are set
                                           to 'F').
                                           
                                           Example.
                                             AcCode = 1234
                                             AcCode[4] = { 0xFF, 0xFF, 0x12, 0x34 } */
} ApiFpMmGetAccessCodeCfmType;

/*! This command is used by the MMI to request the maximum number of PP's
   that can be registered to the FP, the number of PP's and the IPEI Ids of
   the PP's registered currently. */
typedef struct ApiFpMmGetRegistrationCountReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_REGISTRATION_COUNT_REQ = 0x4100 */
  ApiTerminalIdType StartTerminalId;    /*!< Start index for terminal IDs returned. */
} ApiFpMmGetRegistrationCountReqType;

/*! This mail is used by the API to confirm the
   API_FP_MM_GET_REGISTRATION_COUNT_REQ command. */
typedef struct ApiFpMmGetRegistrationCountCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_REGISTRATION_COUNT_CFM = 0x4101 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiTerminalIdType MaxNoHandsets;      /*!< Maximum number of handsets that can be
                                           registered. */
  ApiTerminalIdType TerminalIdCount;    /*!< Number of entries in TerminalId array. */
  ApiTerminalIdType TerminalId[1];      /*!< Array of Ids of the handsets registered.
                                           
(Index 0 to HandsetIdLength-1 is used.) */
} ApiFpMmGetRegistrationCountCfmType;

/*! This command is used by the MMI to request the IPUI of one of the
   handsets registered. */
typedef struct ApiFpMmGetHandsetIpuiReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_HANDSET_IPUI_REQ = 0x4109 */
  ApiTerminalIdType TerminalId;         /*!< The Id of the handset that the MCU wants
                                           the IPUI for. */
} ApiFpMmGetHandsetIpuiReqType;

/*! This mail is used by the API to confirm the
   API_FP_MM_GET_HANDSET_IPUI_REQ command.
    The InfoElementLength and InfoElement fields are optional. Check that the
   size of the received mail is >
   RSOFFSETOF(ApiFpMmGetHandsetIpuiCfmType,InfoElementLength) before using
   these fields. */
typedef struct ApiFpMmGetHandsetIpuiCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_HANDSET_IPUI_CFM = 0x410A */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiTerminalIdType TerminalId;         /*!< The Id for which the IPUI is read. */
  rsuint8 IPUI[5];                      /*!< The IPUI. */
  rsuint16 InfoElementLength;           /*!< (OPTIONAL) The length of the Data
                                           Information Element */
  rsuint8 InfoElement[1];               /*!< (OPTIONAL) The InfoElementList can hold a
                                           number Info Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the 
                                           ApiInfoElementType (which is defined in the
                                           Phoenix_PP_API_Types.doc)
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Expected Info elements:
                                            [API_IE_BASIC_TERMCAPS] 
                                           [API_IE_LOCATION_STATUS] */
} ApiFpMmGetHandsetIpuiCfmType;

/*! This mail is used to inform the Host when a PP has made a location
   update. This happens right after registration, when the PP is powered up
   and when it gets in to range again when it has been out of range. A CODEC
   list is included if the PP supports wide band audio (CAT-iq handset). */
typedef struct ApiFpMmHandsetPresentIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_HANDSET_PRESENT_IND = 0x4108 */
  ApiTerminalIdType TerminalId;         /*!< Id of the handset that has made a location
                                           update. */
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
                                           
                                           Expected Info elements:
                                           [API_IE_CODECLIST] 
                                           [API_IE_MODEL_ID]
                                           [API_IE_TERMCAPS] */
} ApiFpMmHandsetPresentIndType;

/*! This mail is used by the MMI to request a complete stop of the protocol.
    When stopped the FP will stop transmitting the dummybearer so all PP's
   will be unlocked. To restart the protocol the FP needs to be powercycled or
   reset by the API command API_FP_RESET_REQ.
     */
typedef ApifpmmEmptySignalType ApiFpMmStopProtocolReqType;

/*! This mail is used by the MMI to request a complete start of the protocol.
    After powerup, the Fp the protocol will remain idle, not transmitting the
   dummybearer. After receiving API_FP_MM_START_PROTOCOL_REQ the FP will start
   transmitting the dummybearer so all PP's will be able to lock to the base.
     */
typedef ApifpmmEmptySignalType ApiFpMmStartProtocolReqType;

/*! This mail is used to inform the Host when a PP is detached. This can
   happen when the handset is controlled powered off e.g. the user turns off
   the handset. */
typedef struct ApiFpMmHandsetDetachIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_HANDSET_DETACH_IND = 0x410E */
  ApiTerminalIdType TerminalId;         /*!< Id of the handset that has made a location
                                           update. */
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
                                           
                                           Expected Info elements:
                                           [API_IE_MODEL_ID] */
} ApiFpMmHandsetDetachIndType;

/*! This command is used by the MMI to request the FP to set extended
   higher layer capabilities part2, refer to ETSI EN 300 175-5 V2.2.6
   (2009-11) Annex F.3
    After FP reset the capability bits a24,a29,a34,a35,a37 are set to 1, all
   other bits are set to 0. I.e. the 3 bytes default to 0x84, 0x34 and 0. */
typedef struct ApiFpMmExtHigherLayerCap2ReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_EXT_HIGHER_LAYER_CAP2_REQ = 0x410C */
  rsuint8 FpCapBit24_31;                /*!< bit7: a24 NG-DECT wideband voice 
                                           bit6-3: a28-a25 DPRS
                                           bit2: a29 NG-DECT extended wideband voice
                                           bit1: a30 Permanent CLIR
                                           bit0: a31 Conference */
  rsuint8 FpCapBit32_39;                /*!< bit7: a32 Call intrusion
                                           bit6: a33 Call deflection
                                           bit5: a34 Multiple lines
                                           bit4: a35 No emission
                                           bit3: a36 Reserved
                                           bit2: a37 Easy pairing
                                           bit1: a38 Reserved
                                           bit0: a39 Reserved */
  rsuint8 FpCapBit40_47;                /*!< bit7: a40 Reserved
                                           bit6: a41 Reserved
                                           bit5: a42 Early encryption
                                           bit4: a43 Reserved
                                           bit3: a44 Reserved
                                           bit2: a45 Light data services
                                           bit1: a46 Reserved
                                           bit0: a47 Reserved */
} ApiFpMmExtHigherLayerCap2ReqType;

/*! This command is used to get the FP name. Only valid for systems without
   LAS. Systems with LAS must access the name through the DECT system settings
   list. */
typedef ApifpmmEmptySignalType ApiFpMmGetNameReqType;

/*! Get FP name response. */
typedef struct ApiFpMmGetNameCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_NAME_CFM = 0x4111 */
  RsStatusType Status;                  /*!< RSS_SUCCESS or error status. RSS_REJECTED
                                           if LAS must be used. */
  rsuint8 Max;                          /*!< Maximum length of name. */
  rsuint8 Length;                       /*!< Current length of name. */
  rsuint8 Data[1];                      /*!< Name characters. */
} ApiFpMmGetNameCfmType;

/*! This command is used to set the FP name. Only valid for systems without
   LAS. Systems with LAS must access the name through the DECT system settings
   list. */
typedef struct ApiFpMmSetNameReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_SET_NAME_REQ = 0x4112 */
  rsuint8 Length;                       /*!< Length of name. */
  rsuint8 Data[1];                      /*!< Name characters. */
} ApiFpMmSetNameReqType;

/*! Set FP name response. */
typedef struct ApiFpMmSetNameCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_SET_NAME_CFM = 0x4113 */
  RsStatusType Status;                  /*!< RSS_SUCCESS or error status. RSS_REJECTED
                                           if LAS must be used. */
} ApiFpMmSetNameCfmType;

/*! This command is used by the MMI to request the FP to enter or exit
   registration mode. */
typedef struct ApiFpMmSetRegistrationModeReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_SET_REGISTRATION_MODE_REQ = 0x4105 */
  ApiMmRegistrationModeType RegistrationEnabled; /*!< 1: Registration is enabled
                                                     0: Registration is disabled */
  rsuint8 DeleteLastHandset;            /*!< This flag determines what happens if we
                                           have the maximum number of handsets registered
                                           and the user tries to register a new handset.
                                           1: The FP will delete the last handset in the list.
                                           0: The registration will be rejected. */
} ApiFpMmSetRegistrationModeReqType;

/*! This mail is used by the API to confirm the
   API_FP_MM_SET_REGISTRATION_MODE_REQ command. */
typedef struct ApiFpMmSetRegistrationModeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_SET_REGISTRATION_MODE_CFM = 0x4106 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiFpMmSetRegistrationModeCfmType;

/*! This mail is used to inform the MMI when a PP has been registered. A
   CODEC list is included if the PP supports wide band audio (CAT-iq handset). */
typedef struct ApiFpMmRegistrationCompleteIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_REGISTRATION_COMPLETE_IND = 0x4107 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or not.
                                           RsStatusType is defined in the ROS */
  ApiTerminalIdType TerminalId;         /*!< Id of the handset that was registered to
                                           the FP */
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
                                           
                                           Expected Infoelements:
                                           [API_IE_CODECLIST]
                                           [API_IE_MODEL_ID]
                                           [API_IE_TERMCAPS] */
} ApiFpMmRegistrationCompleteIndType;

/*! This mail is used to inform the MMI when a PP has tried to register to
   the FP, but failed. If available, a reject reason will be included. */
typedef struct ApiFpMmRegistrationFailedIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_REGISTRATION_FAILED_IND = 0x4104 */
  ApiMmRejectReasonType Reason;         /*!< Indicates the reason for failing.
                                           RsStatusType is defined in the ROS */
  rsuint8 IPUI[5];                      /*!< The IPUI of the failed PP. */
} ApiFpMmRegistrationFailedIndType;

/*! This command is used by the MMI to request the API to delete a
   registered PP */
typedef struct ApiFpMmDeleteRegistrationReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_DELETE_REGISTRATION_REQ = 0x4102 */
  ApiTerminalIdType TerminalId;         /*!< Index of the handset that shall be deleted. */
} ApiFpMmDeleteRegistrationReqType;

/*! This mail is used by the API to confirm the
   API_FP_MM_DELETE_REGISTRATION_REQ command. */
typedef struct ApiFpMmDeleteRegistrationCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_DELETE_REGISTRATION_CFM = 0x4103 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  ApiTerminalIdType TerminalId;         /*!< Index of the handset that shall be deleted. */
} ApiFpMmDeleteRegistrationCfmType;

/*! This mail indicates that a handset has acknowledged a deregistration
   request. In case the handset is turned off or out of range this indication
   will not be sent until the handset has located. */
typedef struct ApiFpMmHandsetDeregisteredIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_HANDSET_DEREGISTERED_IND = 0x410F */
  ApiTerminalIdType TerminalId;         /*!< Index of the handset that has been deleted. */
} ApiFpMmHandsetDeregisteredIndType;

/*! This mail indicates that registration mode has been disabled by the
   protocol. */
typedef ApifpmmEmptySignalType ApiFpMmRegistrationModeDisabledIndType;

/*! This mail is used by the MMI to broadcast unitdata to the PPs.
    The unitdata broadcast is a connectionless transmission so no acknowledge
   of the data is possible. The unitdata package can hold up to 19 bytes
   (IeLength = 17).
    The time between unitdata packages should be at least 400ms.
    Unitdata packages can be received by the PP both when idle or in a call. */
typedef struct ApiFpMmUnitdataReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_UNITDATA_REQ = 0x4180 */
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
                                           
                                           Expected Infoelements:
                                           [API_IE_UNITDATA] */
} ApiFpMmUnitdataReqType;

/*! This mail is used by the MMI to broadcast to the PP's that they have
   received an incoming call request.The alert broadcast is a connectionless
   transmission. */
typedef struct ApiFpMmAlertBroadcastReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_ALERT_BROADCAST_REQ = 0x4182 */
  ApiMmSignalType Signal;               /*!< Alert signal. Can be used to control which
                                           ringer melody is used at Called endpoint.
                                           
                                           The possible signal types are defined in
                                           ApiMmSignalType (which is defined in the
                                           Phoenix_API_Types.doc)
                                            */
} ApiFpMmAlertBroadcastReqType;

/*! This command is used by the MMI to request the FP protocol to start
   synchronized via the PCM Framesync signal. PCM Hardware must be configured
   in all units before sending this message. All slaves must be started first,
   and finally the Master is started. 
     */
typedef struct ApiFpMmStartProtocolPcmSyncReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_START_PROTOCOL_PCM_SYNC_REQ = 0x4183 */
  ApiMmProtocolPcmSyncType IsMaster;    /*!< Start as the master or slave FP. */
} ApiFpMmStartProtocolPcmSyncReqType;

/*! This command is used by the MMI to request the FP protocol Basic and
   Extended FP Capabilities. */
typedef ApifpmmEmptySignalType ApiFpMmGetFpCapabilitiesReqType;

/*! This mail is used to inform the MMI of the FP protocol Basic and
   Extended FP Capabilities.
    Rrequested by the API_FP_MM_GET_FP_CAPABILITIES_REQ */
typedef struct ApiFpMmGetFpCapabilitiesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_FP_CAPABILITIES_CFM = 0x4171 */
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
                                           
                                           Expected Infoelements:
                                           [API_IE_FP_CAPABILITIES]
                                           [API_IE_FP_EXTENDED_CAPABILITIES]
                                           [API_IE_FP_EXTENDED_CAPABILITIES2] */
} ApiFpMmGetFpCapabilitiesCfmType;

/*! This command is used to enable/disable features in the FpMe API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiFpMmSetFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_SET_FEATURES_REQ = 0x4160 */
  ApiFpMmFeatureType ApiFpMmFeature;    /*!< Requested features */
} ApiFpMmSetFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiFpMmSetFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_SET_FEATURES_CFM = 0x4161 */
  RsStatusType Status;
  ApiFpMmFeatureType ApiFpMmFeature;    /*!< Supported features */
} ApiFpMmSetFeaturesCfmType;

/*! This command is used request the current feature settings. */
typedef ApifpmmEmptySignalType ApiFpMmGetFeaturesReqType;

/*! This command returns the current feature settings. */
typedef struct ApiFpMmGetFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MM_GET_FEATURES_CFM = 0x4163 */
  ApiFpMmFeatureType CurrentFeatures;   /*!< Current feature settings */
  ApiFpMmFeatureType AvailableFeatures; /*!< Available feature settings */
} ApiFpMmGetFeaturesCfmType;

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
* FUNCTION:      SendApiFpMmGetIdReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_ID_REQ = 0x4004
****************************************************************************/
void SendApiFpMmGetIdReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMmGetModelReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_MODEL_REQ = 0x4006
****************************************************************************/
void SendApiFpMmGetModelReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMmSetAccessCodeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_SET_ACCESS_CODE_REQ = 0x4008
****************************************************************************/
void SendApiFpMmSetAccessCodeReq ( RosTaskIdType Src,
                                   rsuint8 Ac[4]);           /*!< The authentication
                                                                code of the FP. This is the
                                                                PIN code of the FP used to
                                                                verify the user for
                                                                registration. The dataformat
                                                                is BCD and the string is 'F'
                                                                terminated (unused nibbles
                                                                are set to 'F').
                                                                
                                                                Example.
                                                                  AcCode = 1234
                                                                  AcCode[4] = { 0xFF, 0xFF,
                                                                0x12, 0x34 } */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetAccessCodeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_ACCESS_CODE_REQ = 0x400A
****************************************************************************/
void SendApiFpMmGetAccessCodeReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMmGetRegistrationCountReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_REGISTRATION_COUNT_REQ = 0x4100
****************************************************************************/
void SendApiFpMmGetRegistrationCountReq ( RosTaskIdType Src,
                                          ApiTerminalIdType StartTerminalId);
                                                             /*!< Start index for
                                                                terminal IDs returned. */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetHandsetIpuiReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_HANDSET_IPUI_REQ = 0x4109
****************************************************************************/
void SendApiFpMmGetHandsetIpuiReq ( RosTaskIdType Src,
                                    ApiTerminalIdType TerminalId);
                                                             /*!< The Id of the handset
                                                                that the MCU wants the IPUI
                                                                for. */

/****************************************************************************
* FUNCTION:      SendApiFpMmStopProtocolReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_STOP_PROTOCOL_REQ = 0x410B
****************************************************************************/
void SendApiFpMmStopProtocolReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMmStartProtocolReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_START_PROTOCOL_REQ = 0x410D
****************************************************************************/
void SendApiFpMmStartProtocolReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMmExtHigherLayerCap2Req
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_EXT_HIGHER_LAYER_CAP2_REQ = 0x410C
****************************************************************************/
void SendApiFpMmExtHigherLayerCap2Req ( RosTaskIdType Src,
                                        rsuint8 FpCapBit24_31,
                                                             /*!< bit7: a24 NG-DECT
                                                                wideband voice 
                                                                bit6-3: a28-a25 DPRS
                                                                bit2: a29 NG-DECT extended
                                                                wideband voice
                                                                bit1: a30 Permanent CLIR
                                                                bit0: a31 Conference */
                                        rsuint8 FpCapBit32_39,
                                                             /*!< bit7: a32 Call intrusion
                                                                bit6: a33 Call deflection
                                                                bit5: a34 Multiple lines
                                                                bit4: a35 No emission
                                                                bit3: a36 Reserved
                                                                bit2: a37 Easy pairing
                                                                bit1: a38 Reserved
                                                                bit0: a39 Reserved */
                                        rsuint8 FpCapBit40_47);
                                                             /*!< bit7: a40 Reserved
                                                                bit6: a41 Reserved
                                                                bit5: a42 Early encryption
                                                                bit4: a43 Reserved
                                                                bit3: a44 Reserved
                                                                bit2: a45 Light data services
                                                                bit1: a46 Reserved
                                                                bit0: a47 Reserved */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetNameReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_NAME_REQ = 0x4110
****************************************************************************/
void SendApiFpMmGetNameReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMmSetNameReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_SET_NAME_REQ = 0x4112
****************************************************************************/
void SendApiFpMmSetNameReq ( RosTaskIdType Src,
                             rsuint8 Length,                 /*!< Length of name. */
                             rsuint8 Data[1]);               /*!< Name characters. */

/****************************************************************************
* FUNCTION:      SendApiFpMmSetRegistrationModeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_SET_REGISTRATION_MODE_REQ = 0x4105
****************************************************************************/
void SendApiFpMmSetRegistrationModeReq ( RosTaskIdType Src,
                                         ApiMmRegistrationModeType RegistrationEnabled,
                                                             /*!< 1: Registration is enabled
                                                                0: Registration is disabled */
                                         rsuint8 DeleteLastHandset);
                                                             /*!< This flag determines
                                                                what happens if we have the
                                                                maximum number of handsets
                                                                registered and the user
                                                                tries to register a new handset.
                                                                1: The FP will delete the
                                                                last handset in the list.
                                                                0: The registration will be
                                                                rejected. */

/****************************************************************************
* FUNCTION:      SendApiFpMmDeleteRegistrationReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_DELETE_REGISTRATION_REQ = 0x4102
****************************************************************************/
void SendApiFpMmDeleteRegistrationReq ( RosTaskIdType Src,
                                        ApiTerminalIdType TerminalId);
                                                             /*!< Index of the handset
                                                                that shall be deleted. */

/****************************************************************************
* FUNCTION:      SendApiFpMmUnitdataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_UNITDATA_REQ = 0x4180
****************************************************************************/
void SendApiFpMmUnitdataReq ( RosTaskIdType Src,
                              rsuint16 InfoElementLength,    /*!< The length of the Data
                                                                Information Element */
                              rsuint8 InfoElement[1]);       /*!< The InfoElementList
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
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Infoelements:
                                                                [API_IE_UNITDATA] */

/****************************************************************************
* FUNCTION:      SendApiFpMmAlertBroadcastReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_ALERT_BROADCAST_REQ = 0x4182
****************************************************************************/
void SendApiFpMmAlertBroadcastReq ( RosTaskIdType Src,
                                    ApiMmSignalType Signal);  /*!< Alert signal. Can be
                                                                 used to control which
                                                                 ringer melody is used at
                                                                 Called endpoint.
                                                                 
                                                                 The possible signal types
                                                                 are defined in
                                                                 ApiMmSignalType (which is
                                                                 defined in the
                                                                 Phoenix_API_Types.doc)
                                                                  */

/****************************************************************************
* FUNCTION:      SendApiFpMmStartProtocolPcmSyncReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_START_PROTOCOL_PCM_SYNC_REQ = 0x4183
****************************************************************************/
void SendApiFpMmStartProtocolPcmSyncReq ( RosTaskIdType Src,
                                          ApiMmProtocolPcmSyncType IsMaster);
                                                             /*!< Start as the master or
                                                                slave FP. */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetFpCapabilitiesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_FP_CAPABILITIES_REQ = 0x4170
****************************************************************************/
void SendApiFpMmGetFpCapabilitiesReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMmSetFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_SET_FEATURES_REQ = 0x4160
****************************************************************************/
void SendApiFpMmSetFeaturesReq ( RosTaskIdType Src,
                                 ApiFpMmFeatureType ApiFpMmFeature);
                                                             /*!< Requested features */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_FEATURES_REQ = 0x4162
****************************************************************************/
void SendApiFpMmGetFeaturesReq ( RosTaskIdType Src );


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPMM_H */


