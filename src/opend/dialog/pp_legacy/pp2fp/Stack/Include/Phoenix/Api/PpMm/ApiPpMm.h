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
* Definition of the ApiPpMm interface.
*/


#ifndef APIPPMM_H
#define APIPPMM_H

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
  API_PP_MM_GET_ID_REQ = 0x5100,
  API_PP_MM_GET_ID_CFM = 0x5101,
  API_PP_MM_GET_MODEL_REQ = 0x5102,
  API_PP_MM_GET_MODEL_CFM = 0x5103,
  API_PP_MM_READ_RSSI_REQ = 0x5104,
  API_PP_MM_READ_RSSI_CFM = 0x5105,
  API_PP_MM_LOCK_REQ = 0x5106,
  API_PP_MM_LOCKED_REQ = 0x5107,
  API_PP_MM_LOCKED_IND = 0x5108,
  API_PP_MM_UNLOCKED_IND = 0x5109,
  API_PP_MM_STOP_PROTOCOL_REQ = 0x510A,
  API_PP_MM_REGISTRATION_AUTO_REQ = 0x510B,
  API_PP_MM_EASY_PAIRING_SEARCH_REQ = 0x5121,
  API_PP_MM_EASY_PAIRING_SEARCH_CFM = 0x5122,
  API_PP_MM_REGISTRATION_SEARCH_REQ = 0x510C,
  API_PP_MM_REGISTRATION_SEARCH_IND = 0x510D,
  API_PP_MM_REGISTRATION_SELECTED_REQ = 0x510E,
  API_PP_MM_REGISTRATION_STOP_REQ = 0x510F,
  API_PP_MM_REGISTRATION_COMPLETE_IND = 0x5110,
  API_PP_MM_REGISTRATION_FAILED_IND = 0x5111,
  API_PP_MM_REGISTRATION_SELECTED_WITH_PLI_REQ = 0x5112,
  API_PP_MM_DELETE_LOCAL_REGISTRATION_REQ = 0x5114,
  API_PP_MM_DELETE_LOCAL_REGISTRATION_CFM = 0x5115,
  API_PP_MM_UPI_AUTHENTICATE_IND = 0x5117,
  API_PP_MM_UPI_AUTHENTICATE_RES = 0x5118,
  API_PP_MM_ACC_RIGHTS_TERM_IND = 0x511B,
  API_PP_MM_UNITDATA_IND = 0x5119,
  API_PP_MM_ALERT_BROADCAST_IND = 0x511A,
  API_PP_MM_FP_NAME_IND = 0x511D,
  API_PP_MM_ENCRYPTION_NOT_STARTED_IND = 0x511E,
  API_PP_MM_GET_EXT_HIGHER_LAYER_CAP2_REQ = 0x511F,
  API_PP_MM_GET_EXT_HIGHER_LAYER_CAP2_CFM = 0x5120,
  API_PP_MM_GET_SUBSCRIPTION_RFPI_REQ = 0x5123,
  API_PP_MM_GET_SUBSCRIPTION_RFPI_CFM = 0x5124,
End of mail primitives. */



/*! This struct is used to specify the reject reasons for a failed
   registration. */
typedef enum RSENUMTAG(ApiPpMmRejectReasonType)
{
  API_MM_REJ_NO_REASON                      = 0x00, /*!<  */
  API_MM_REJ_TPUI_UNKNOWN                   = 0x01, /*!<  */
  API_MM_REJ_IPUI_UNKNOWN                   = 0x02, /*!<  */
  API_MM_REJ_NETWORK_ASSIGNED_ID_UNKNOWN    = 0x03, /*!<  */
  API_MM_REJ_IPEI_NOT_ACCEPTED              = 0x05, /*!<  */
  API_MM_REJ_IPUI_NOT_ACCEPTED              = 0x06, /*!<  */
  API_MM_REJ_AUTH_FAILED                    = 0x10, /*!< Authentication failed (wrong
                                                       AcCode) */
  API_MM_REJ_NO_AUTH_ALGORITHM              = 0x11, /*!<  */
  API_MM_REJ_AUTH_ALGORITHM_NOT_SUPPORTED   = 0x12, /*!<  */
  API_MM_REJ_AUTH_KEY_NOT_SUPPORTED         = 0x13, /*!<  */
  API_MM_REJ_UPI_NOT_ENTERED                = 0x14, /*!<  */
  API_MM_REJ_NO_CIPHER_ALGORITHM            = 0x17, /*!<  */
  API_MM_REJ_CIPHER_ALGORITHM_NOT_SUPPORTED = 0x18, /*!<  */
  API_MM_REJ_CIPHER_KEY_NOT_SUPPORTED       = 0x19, /*!<  */
  API_MM_REJ_INCOMPATIBLE_SERVICE           = 0x20, /*!<  */
  API_MM_REJ_FALSE_LCE_REPLY                = 0x21, /*!<  */
  API_MM_REJ_LATE_LCE_REPLY                 = 0x22, /*!<  */
  API_MM_REJ_INVALID_TPUI                   = 0x23, /*!<  */
  API_MM_REJ_TPUI_ASSIGN_LIMIT_UNACCEPT     = 0x24, /*!<  */
  API_MM_REJ_UNSUFFICIENT_MEMORY            = 0x2F, /*!< Fp Registration Database full */
  API_MM_REJ_OVERLOAD                       = 0x30, /*!<  */
  API_MM_REJ_TEST_CALL_BACK_NORM_ENBLOC     = 0x40, /*!<  */
  API_MM_REJ_TEST_CALL_BACK_NORM_PIECEWISE  = 0x41, /*!<  */
  API_MM_REJ_TEST_CALL_BACK_EMERG_ENBLOC    = 0x42, /*!<  */
  API_MM_REJ_TEST_CALL_BACK_EMERG_PIECEWISE = 0x43, /*!<  */
  API_MM_REJ_INVALID_MESSAGE                = 0x5F, /*!<  */
  API_MM_REJ_IE_ERROR                       = 0x60, /*!<  */
  API_MM_REJ_INVALID_IE_CONTENTS            = 0x64, /*!<  */
  API_MM_REJ_TIMER_EXPIRY                   = 0x70, /*!<  */
  API_MM_REJ_PLMN_NOT_ALLOWD                = 0x76, /*!<  */
  API_MM_REJ_LOCATION_AREA_NOT_ALLOWED      = 0x80, /*!<  */
  API_MM_REJ_NATIONAL_ROAMING_NOT_ALLOWED   = 0x81, /*!<  */
  API_MM_REJ_TERMINAL_IN_ACTIVE_CALL        = 0x90, /*!<  */
  API_MM_REJ_TERMINAL_IN_FWU_CALL           = 0x91, /*!<  */
  API_MM_REJ_MM_TRANSACTION_ONGOING         = 0x92  /*!<  */
} RSENUM8(ApiPpMmRejectReasonType);


/*! Mail without parameters. */
typedef struct ApippmmEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApippmmEmptySignalType;

/*! This command is used by the MMI to request the API to return a unique
   identifier for that particular PP. */
typedef ApippmmEmptySignalType ApiPpMmGetIdReqType;

/*! This mail is used by the API to return the unique PP id to the MMI. */
typedef struct ApiPpMmGetIdCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_GET_ID_CFM = 0x5101 */
  rsuint8 Id[5];                        /*!< The id of the PP. The IPEI of the PP is
                                           used to identify the PP. */
} ApiPpMmGetIdCfmType;

/*! This command is used to request a string indicating the model and
   manufacture. */
typedef ApippmmEmptySignalType ApiPpMmGetModelReqType;

/*! This mail is used to confirm the API_PP_MM_GET_MODEL_REQ command. */
typedef struct ApiPpMmGetModelCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_GET_MODEL_CFM = 0x5103 */
  ApiModelIdType ModelId;               /*!< The manufacture (MANIC) and model (MODIC)
                                           code of the PP. The EMC code of the PP is used as
                                           manufacture code. */
} ApiPpMmGetModelCfmType;

/*! This mail is used by the MMI to request the current RSSI (Radio Signal
   Strength Indication) from the protocol. */
typedef ApippmmEmptySignalType ApiPpMmReadRssiReqType;

/*! This mail is used to confirm the API_PP_MM_READ_RSSI_REQ.
    Note: The returned RSSI values are not calibrated on production units,
   please use for debugging purposes only. 
    Note: the API is only available on some project variants. */
typedef struct ApiPpMmReadRssiCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_READ_RSSI_CFM = 0x5105 */
  rsuint8 Rssi;                         /*!< RSSI (Radio Signal Strength Indication)
                                           Legal values [0x00-0x3F]
                                           0x00: equals no connection/connection lost,
                                           0x3F: equals full signal. 
                                           
                                           The RSSI is operational in both onhook and
                                           offhook mode. */
} ApiPpMmReadRssiCfmType;

/*! This mail is used by the MMI to request the protocol to search and
   synchronized to a selected FP (from the registration database)
    When the PP is locked an synchronized, a API_PP_MM_LOCKED_IND will be
   returned to the MMI
    *After powering up, the PP will not start searching and synchronize to any
   FP before receiving the API_PP_MM_LOCK_REQ */
typedef struct ApiPpMmLockReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_LOCK_REQ = 0x5106 */
  rsuint8 SubscriptionNo;               /*!< The subscription number indicated the index
                                           in the registration database.
                                           
                                           0x00: Auto search, the protocol will search for
                                           all subscribed FP's in the registration database.
                                           
                                           0x01: Search  for specific FP #1
                                           0x02: Search  for specific FP #1
                                           ...
                                           0x0n: Search  for specific FP #n */
} ApiPpMmLockReqType;

/*! This mail is used by the MMI to force the API to reply instantly with
   the locked status (API_PP_MM_LOCKED_IND or API_PP_MM_UNLOCKED_IND). */
typedef ApippmmEmptySignalType ApiPpMmLockedReqType;

/*! This mail is used by the API to indicate to the MMI that the requested
   FP has been found and the that PP is now synchronized, and ready to
   initiate and receive calls.
    HigherLayerCap2 bits are indicated to the MMI to show capabilities of the
   sync'ed FP.. */
typedef struct ApiPpMmLockedIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_LOCKED_IND = 0x5108 */
  rsuint8 SubscriptionNo;               /*!< Indicates the index of the locked FP in the
                                           registration database. */
  rsuint8 FpCapBit24_31;                /*!< bit0: a31 Conference
                                           bit1: a30 Permanent CLIR
                                           bit2: a29 NG-DECT extended wideband voice
                                           bit3-6: a25-a28 DPRS
                                           bit7: a24 NG-DECT wideband voice */
  rsuint8 FpCapBit32_39;                /*!< bit0: a39 Reserved
                                           bit1: a38 Reserved
                                           bit2: a37 Reserved
                                           bit3: a36 Reserved
                                           bit4: a35 No emission
                                           bit5: a34 Multiple lines
                                           bit6: a33 Call deflection
                                           bit7: a32 Call intrusion */
  rsuint8 FpCapBit40_47;                /*!< bit0: a47 Reserved
                                           bit1: a46 Reserved
                                           bit2: a45 Light data services
                                           bit3: a44 Reserved
                                           bit4: a43 Reserved
                                           bit5: a42 Early encryption
                                           bit6: a41 Reserved
                                           bit7: a40 Reserved */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           CodecList is only included when coming from a
                                           Locate Accept.
                                           Expected Infoelements:
                                           [IE_CODEC_LIST] */
} ApiPpMmLockedIndType;

/*! This mail is used by the API to indicate to the MMI that the FP
   connection has been lost.
    After receiving this mail, the MMI has to trigger a new API_PP_MM_LOCK_REQ
   and receive a API_PP_MM_LOCLED_IND before further calls can be made
    *The API_PP_MM_UNLOCKED_IND is triggered after the protocol has received
   invalid DECT packages continuously for 5 secs. */
typedef ApippmmEmptySignalType ApiPpMmUnlockedIndType;

/*! This mail is used by the MMI to request a complete stop of the protocol.
    It can be used to force stop of am ongoing registration or to force the PP
   out of synchronization with the FP.
    After the API_PP_MM_SETOP_PROTOCOL_REQ, the protocol can be restarted by
   an API_PP_MM_LOCK_REQ or a new registration request */
typedef ApippmmEmptySignalType ApiPpMmStopProtocolReqType;

/*! This command is used by the MMI to request the API to perform an
   automatic unsupervised registration. The PP will search for FP's with the
   access rights capability bit set and automatically perform a registration
   to the first registration enabled RFPI it finds.
    The command will result in a API_PP_MM_REGISTRATION_COMPLETE_IND */
typedef struct ApiPpMmRegistrationAutoReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_REGISTRATION_AUTO_REQ = 0x510B */
  rsuint8 SubscriptionNo;               /*!< Selects the index in the PP subscription
                                           database where the registrations data should be written.
                                           [1..4] */
  rsuint8 AcCode[4];                    /*!< The authentication code of the FP. This is
                                           the "PIN" code of the FP used to verify the user
                                           for registration. The dataformat is BCD and the
                                           string is 'F' terminated (unused nibbles are set
                                           to 'F').
                                           
                                           Example.
                                             AcCode = 1234
                                             AcCode[4] = { 0xFF, 0xFF, 0x12, 0x34 } */
} ApiPpMmRegistrationAutoReqType;

/*! This command is used by the MMI to request the API to perform a search
   for registration enabled Fp with A29_EWB capability bit set.
    The command will result in a API_PP_MM_EASY_PAIRING_SEARCH_CFM
     */
typedef ApippmmEmptySignalType ApiPpMmEasyPairingSearchReqType;

/*! This mail is used to inform the MMI found registration enabled RFPI's.
    Parameters hold the selected RFPI and the FP extended higher layer
   capabilities part2, refer to ETSI EN 300 175-5 V2.2.6 (2009-11) Annex F.3 */
typedef struct ApiPpMmEasyPairingSearchCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_EASY_PAIRING_SEARCH_CFM = 0x5122 */
  rsuint8 Rfpi[5];                      /*!< The RFPI (Radio Fixed Part Identifier) of
                                           the found FP */
  rsuint8 FpCapBit24_31;                /*!< bit0: a31 Conference
                                           bit1: a30 Permanent CLIR
                                           bit2: a29 NG-DECT extended wideband voice
                                           bit3-6: a25-a28 DPRS
                                           bit7: a24 NG-DECT wideband voice */
  rsuint8 FpCapBit32_39;                /*!< bit0: a39 Reserved
                                           bit1: a38 Reserved
                                           bit2: a37 Reserved
                                           bit3: a36 Reserved
                                           bit4: a35 No emission
                                           bit5: a34 Multiple lines
                                           bit6: a33 Call deflection
                                           bit7: a32 Call intrusion */
  rsuint8 FpCapBit40_47;                /*!< bit0: a47 Reserved
                                           bit1: a46 Reserved
                                           bit2: a45 Light data services
                                           bit3: a44 Reserved
                                           bit4: a43 Reserved
                                           bit5: a42 Early encryption
                                           bit6: a41 Reserved
                                           bit7: a40 Reserved */
} ApiPpMmEasyPairingSearchCfmType;

/*! This command is used by the MMI to request the API to start searching
   for registration enabled RFPI's. Found RFPI(s) will be returned in the
   API_PP_MM_REGISTRATION_SEARCH_IND. */
typedef struct ApiPpMmRegistrationSearchReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_REGISTRATION_SEARCH_REQ = 0x510C */
  ApiMmSearchModeType SearchMode;       /*!< Defines if search should search
                                           continuously finding more FP's or single which
                                           will stop after finding the first registration
                                           enabled FP. */
} ApiPpMmRegistrationSearchReqType;

/*! This mail is used to inform the MMI found registration enabled RFPI's.
    Parameters hold the selected RFPI and the FP extended higher layer
   capabilities part2, refer to ETSI EN 300 175-5 V2.2.6 (2009-11) Annex F.3
    FP extended higher layer capabilities part2, refer to ETSI EN 300 175-5
   V2.2.6 (2009-11) Annex F.3 */
typedef struct ApiPpMmRegistrationSearchIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_REGISTRATION_SEARCH_IND = 0x510D */
  rsuint8 Rfpi[5];                      /*!< The RFPI (Radio Fixed Part Identifier) of
                                           the found FP */
  rsuint8 FpCapBit24_31;                /*!< bit0: a31 Conference
                                           bit1: a30 Permanent CLIR
                                           bit2: a29 NG-DECT extended wideband voice
                                           bit3-6: a25-a28 DPRS
                                           bit7: a24 NG-DECT wideband voice */
  rsuint8 FpCapBit32_39;                /*!< bit0: a39 Reserved
                                           bit1: a38 Reserved
                                           bit2: a37 Reserved
                                           bit3: a36 Reserved
                                           bit4: a35 No emission
                                           bit5: a34 Multiple lines
                                           bit6: a33 Call deflection
                                           bit7: a32 Call intrusion */
  rsuint8 FpCapBit40_47;                /*!< bit0: a47 Reserved
                                           bit1: a46 Reserved
                                           bit2: a45 Light data services
                                           bit3: a44 Reserved
                                           bit4: a43 Reserved
                                           bit5: a42 Early encryption
                                           bit6: a41 Reserved
                                           bit7: a40 Reserved */
} ApiPpMmRegistrationSearchIndType;

/*! This command is used by the MMI to request the API to perform a
   supervised registration. The PP will register to the selected RFPI.
    The command will result in a API_PP_MM_REGISTRATION_IND */
typedef struct ApiPpMmRegistrationSelectedReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_REGISTRATION_SELECTED_REQ = 0x510E */
  rsuint8 SubscriptionNo;               /*!< Selects the index in the PP subscription
                                           database where the registrations data should be written.
                                           [1..4] */
  rsuint8 AcCode[4];                    /*!< The authentication code of the FP. This is
                                           the "PIN" code of the FP used to verify the user
                                           for registration. The dataformat is BCD and the
                                           string is 'F' terminated (unused nibbles are set
                                           to 'F').
                                           
                                           Example.
                                             AcCode = 1234
                                             AcCode[4] = { 0xFF, 0xFF, 0x12, 0x34 } */
  rsuint8 Rfpi[5];                      /*!< The RFPI to register to in HEX format. */
} ApiPpMmRegistrationSelectedReqType;

/*! This command is used by the MMI to request the API to cancel
   registration mode (stop searching for RFPI's) */
typedef ApippmmEmptySignalType ApiPpMmRegistrationStopReqType;

/*! This mail is used to inform the MCU when a handset has been registered.
   A CODEC list is included if the handset supports wide band audio (CAT-iq
   handset). */
typedef struct ApiPpMmRegistrationCompleteIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_REGISTRATION_COMPLETE_IND = 0x5110 */
  rsuint8 HandsetId;                    /*!< Id of the handset that was registered to
                                           the API. */
  rsbool KnownFp;                       /*!< Returns if the unit is a known (same
                                           manufactorer). 
                                           This is useful in the DECT version where you can
                                           register the PP to other manufacturer FP's.
                                           It is judged on the FixedEMC and returns
                                           1: Same Manufactorer ID in FP/PP
                                           0: Different Manufactorer ID in FP/PP */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Expected Infoelements:
                                           [IE_CODEC_LIST] */
} ApiPpMmRegistrationCompleteIndType;

/*! This mail is used to inform the MMI when the PP has failed the
   registration. */
typedef struct ApiPpMmRegistrationFailedIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_REGISTRATION_FAILED_IND = 0x5111 */
  ApiPpMmRejectReasonType Reason;       /*!< Reason of the failed registration */
} ApiPpMmRegistrationFailedIndType;

/*! This command is used by the MMI to request the API to perform a
   supervised registration. The PP will register to the selected RFPI
   including PLI.
    The command will result in a API_PP_MM_REGISTRATION_IND */
typedef struct ApiPpMmRegistrationSelectedWithPliReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_REGISTRATION_SELECTED_WITH_PLI_REQ = 0x5112 */
  rsuint8 SubscriptionNo;               /*!< Selects the index in the PP subscription
                                           database where the registrations data should be written.
                                           [1..4] */
  rsuint8 AcCode[4];                    /*!< The authentication code of the FP. This is
                                           the "PIN" code of the FP used to verify the user
                                           for registration. The dataformat is BCD and the
                                           string is 'F' terminated (unused nibbles are set
                                           to 'F').
                                           
                                           Example.
                                             AcCode = 1234
                                             AcCode[4] = { 0xFF, 0xFF, 0x12, 0x34 } */
  rsuint8 Rfpi[5];                      /*!< The RFPI to register to in HEX format. */
  rsuint8 Pli;                          /*!< Park bit length */
} ApiPpMmRegistrationSelectedWithPliReqType;

/*! This command is used by the MMI to request the API to delete a
   registered PP locally.
    This means that the registration entry in the FP will not be deleted! */
typedef struct ApiPpMmDeleteLocalRegistrationReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_DELETE_LOCAL_REGISTRATION_REQ = 0x5114 */
  rsuint8 SubscriptionNo;               /*!< Selects the index in the PP subscription
                                           database where the registrations data should be
                                           deleted. */
} ApiPpMmDeleteLocalRegistrationReqType;

/*! This mail is used by the API to confirm the
   API_PP_MM_DELETE_REGISTRATION_REQ command. */
typedef struct ApiPpMmDeleteLocalRegistrationCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_DELETE_LOCAL_REGISTRATION_CFM = 0x5115 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or not.
                                           RsStatusType is defined in the ROS */
  rsuint8 SubscriptionNo;               /*!< Indicates the index in the PP subscription
                                           database where the registrations data has been
                                           deleted. */
} ApiPpMmDeleteLocalRegistrationCfmType;

/*! This command is used by the FP to request the PP MMI to authenticate
   him self.
    When receiving this, the MMI should prompt the user to manually enter the
   UPI (User Personal Identifier) code. When the user has entered the code,
   the MMI should answer with the API_PP_MM_UPI_AUTHENTICATE_RES */
typedef ApippmmEmptySignalType ApiPpMmUpiAuthenticateIndType;

/*! This mail is used by the MMI  to confirm the API_PP_MM_UPI_AUTHENTICATE_IND
    It holds up to 8 digits entered by the user. */
typedef struct ApiPpMmUpiAuthenticateResType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_UPI_AUTHENTICATE_RES = 0x5118 */
  rsuint8 Upi[4];                       /*!< 5 bytes holding the UPI
                                           
                                           The UPI authentication code of the FP. This is a
                                           "PIN" code of the FP used to verify the user
                                           during location and in normal use. The dataformat
                                           is BCD and the string is 'F' terminated (unused
                                           nubbled are set to 'F'). 
                                           
                                           Example.
                                             API = 1234
                                             Upi[4] = { 0xFF, 0xFF, 0x12, 0x34 } */
} ApiPpMmUpiAuthenticateResType;

/*! This mail is send to the MMI to indicate that the FP has deleted this
   Pp registration */
typedef ApippmmEmptySignalType ApiPpMmAccRightsTermIndType;

/*! This mail is used by the API to indicate to the MMI that it has
   received packed of proprietary data, broadcasted from the FP.
    The unitdata broadcast is a connectionless transmission so no
   answer/confirm is necessary from the PP. It can hold up to 19 bytes in one package.
    *The unitdata can be received both when idle or in a call. */
typedef struct ApiPpMmUnitdataIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_UNITDATA_IND = 0x5119 */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the 
                                           ApiInfoElementType (which is defined in the
                                           "Phoenix_API_Types.doc")
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Expected Infoelements:
                                           [API_IE_UNITDATA] */
} ApiPpMmUnitdataIndType;

/*! This mail is used by the API to indicate to the MMI that it has
   received and incoming call request in the form of an alert broadcast from
   the FP.
    The alert broadcast is a connectionless transmission. To answer the alert
   the PP needs to send an outgoing setup_req to establish the cobnnection. */
typedef struct ApiPpMmAlertBroadcastIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_ALERT_BROADCAST_IND = 0x511A */
  ApiMmSignalType Signal;               /*!< Alert signal. Can be used to control which
                                           ringer melody is used at Called endpoint.
                                           
                                           The possible signal types are defined in
                                           ApiMmSignalType (which is defined in the
                                           "Phoenix_API_Types.doc")
                                            */
} ApiPpMmAlertBroadcastIndType;

/*! This mail is used by the API to indicate to the MMI that it has
   received an FpName from the FP. Especially if doing a manual registration
   with user selection of the FP (the search_req) its convenient to be able to
   display the name of the Fp to the user instead of only the RFPI.
    The FpName might be received at the PP when synchronizing to the FP in
   normal mode and while doing registration. */
typedef struct ApiPpMmFpNameIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_FP_NAME_IND = 0x511D */
  rsuint8 FpNameLength;                 /*!< The length of the received Fp name */
  rsuint8 FpName[1];                    /*!< The received FP name.
                                           Can hold from 0 to 17 chars */
} ApiPpMmFpNameIndType;

/*! This mail is send to the MMI to indicate that the FP has not started
   the encryption
    Time offset before encryption check can be set in eeprom
   (EncStartCheckTime) */
typedef ApippmmEmptySignalType ApiPpMmEncryptionNotStartedIndType;

/*! This mail is used by the MMI to request the extended higher layer
   capabilities part2 of the FP on which the PP is currently locked. */
typedef ApippmmEmptySignalType ApiPpMmGetExtHigherLayerCap2ReqType;

/*! This mail is used by the API to inform the MMI about the FP extended
   higher layer capabilities part2, refer to ETSI EN 300 175-5 V2.2.6
   (2009-11) Annex F.3 */
typedef struct ApiPpMmGetExtHigherLayerCap2CfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_GET_EXT_HIGHER_LAYER_CAP2_CFM = 0x5120 */
  rsuint8 FpCapBit24_31;                /*!< bit0: a31 Conference
                                           bit1: a30 Permanent CLIR
                                           bit2: a29 NG-DECT extended wideband voice
                                           bit3-6: a25-a28 DPRS
                                           bit7: a24 NG-DECT wideband voice */
  rsuint8 FpCapBit32_39;                /*!< bit0: a39 Reserved
                                           bit1: a38 Reserved
                                           bit2: a37 Reserved
                                           bit3: a36 Reserved
                                           bit4: a35 No emission
                                           bit5: a34 Multiple lines
                                           bit6: a33 Call deflection
                                           bit7: a32 Call intrusion */
  rsuint8 FpCapBit40_47;                /*!< bit0: a47 Reserved
                                           bit1: a46 Reserved
                                           bit2: a45 Light data services
                                           bit3: a44 Reserved
                                           bit4: a43 Reserved
                                           bit5: a42 Early encryption
                                           bit6: a41 Reserved
                                           bit7: a40 Reserved */
} ApiPpMmGetExtHigherLayerCap2CfmType;

/*! This mail is used by the MMI to request the RFPI associated with a
   specific subscription number. */
typedef struct ApiPpMmGetSubscriptionRfpiReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_GET_SUBSCRIPTION_RFPI_REQ = 0x5123 */
  rsuint8 SubscriptionNo;               /*!< The subscription number indicated the index
                                           in the subscription database. [1..4] */
} ApiPpMmGetSubscriptionRfpiReqType;

/*! This mail is used to inform the MMI about the RFPI found at the
   selected subscription number. */
typedef struct ApiPpMmGetSubscriptionRfpiCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_MM_GET_SUBSCRIPTION_RFPI_CFM = 0x5124 */
  rsuint8 SubscriptionNo;               /*!< The subscription number indicated the index
                                           in the subscription database. [1..4] */
  rsuint8 Rfpi[5];                      /*!< The RFPI (Radio Fixed Part Identifier) of
                                           the selected subscription. */
} ApiPpMmGetSubscriptionRfpiCfmType;

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
* FUNCTION:      SendApiPpMmGetIdReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_GET_ID_REQ = 0x5100
****************************************************************************/
void SendApiPpMmGetIdReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMmGetModelReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_GET_MODEL_REQ = 0x5102
****************************************************************************/
void SendApiPpMmGetModelReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMmReadRssiReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_READ_RSSI_REQ = 0x5104
****************************************************************************/
void SendApiPpMmReadRssiReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMmLockReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_LOCK_REQ = 0x5106
****************************************************************************/
void SendApiPpMmLockReq ( RosTaskIdType Src,
                          rsuint8 SubscriptionNo);           /*!< The subscription
                                                                number indicated the index
                                                                in the registration database.
                                                                
                                                                0x00: Auto search, the
                                                                protocol will search for all
                                                                subscribed FP's in the
                                                                registration database.
                                                                
                                                                0x01: Search  for specific
                                                                FP #1
                                                                0x02: Search  for specific
                                                                FP #1
                                                                ...
                                                                0x0n: Search  for specific
                                                                FP #n */

/****************************************************************************
* FUNCTION:      SendApiPpMmLockedReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_LOCKED_REQ = 0x5107
****************************************************************************/
void SendApiPpMmLockedReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMmStopProtocolReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_STOP_PROTOCOL_REQ = 0x510A
****************************************************************************/
void SendApiPpMmStopProtocolReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMmRegistrationAutoReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_REGISTRATION_AUTO_REQ = 0x510B
****************************************************************************/
void SendApiPpMmRegistrationAutoReq ( RosTaskIdType Src,
                                      rsuint8 SubscriptionNo,
                                                             /*!< Selects the index in
                                                                the PP subscription database
                                                                where the registrations data
                                                                should be written.
                                                                [1..4] */
                                      rsuint8 AcCode[4]);    /*!< The authentication
                                                                code of the FP. This is the
                                                                "PIN" code of the FP used to
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
* FUNCTION:      SendApiPpMmEasyPairingSearchReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_EASY_PAIRING_SEARCH_REQ = 0x5121
****************************************************************************/
void SendApiPpMmEasyPairingSearchReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMmRegistrationSearchReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_REGISTRATION_SEARCH_REQ = 0x510C
****************************************************************************/
void SendApiPpMmRegistrationSearchReq ( RosTaskIdType Src,
                                        ApiMmSearchModeType SearchMode);
                                                             /*!< Defines if search
                                                                should search continuously
                                                                finding more FP's or single
                                                                which will stop after
                                                                finding the first
                                                                registration enabled FP. */

/****************************************************************************
* FUNCTION:      SendApiPpMmRegistrationSelectedReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_REGISTRATION_SELECTED_REQ = 0x510E
****************************************************************************/
void SendApiPpMmRegistrationSelectedReq ( RosTaskIdType Src,
                                          rsuint8 SubscriptionNo,
                                                             /*!< Selects the index in
                                                                the PP subscription database
                                                                where the registrations data
                                                                should be written.
                                                                [1..4] */
                                          rsuint8 AcCode[4],  /*!< The authentication
                                                                 code of the FP. This is the
                                                                 "PIN" code of the FP used
                                                                 to verify the user for
                                                                 registration. The
                                                                 dataformat is BCD and the
                                                                 string is 'F' terminated
                                                                 (unused nibbles are set to 'F').
                                                                 
                                                                 Example.
                                                                   AcCode = 1234
                                                                   AcCode[4] = { 0xFF,
                                                                 0xFF, 0x12, 0x34 } */
                                          rsuint8 Rfpi[5]);  /*!< The RFPI to register
                                                                to in HEX format. */

/****************************************************************************
* FUNCTION:      SendApiPpMmRegistrationStopReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_REGISTRATION_STOP_REQ = 0x510F
****************************************************************************/
void SendApiPpMmRegistrationStopReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMmRegistrationSelectedWithPliReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_REGISTRATION_SELECTED_WITH_PLI_REQ = 0x5112
****************************************************************************/
void SendApiPpMmRegistrationSelectedWithPliReq ( RosTaskIdType Src,
                                                 rsuint8 SubscriptionNo,
                                                             /*!< Selects the index in
                                                                the PP subscription database
                                                                where the registrations data
                                                                should be written.
                                                                [1..4] */
                                                 rsuint8 AcCode[4],
                                                             /*!< The authentication
                                                                code of the FP. This is the
                                                                "PIN" code of the FP used to
                                                                verify the user for
                                                                registration. The dataformat
                                                                is BCD and the string is 'F'
                                                                terminated (unused nibbles
                                                                are set to 'F').
                                                                
                                                                Example.
                                                                  AcCode = 1234
                                                                  AcCode[4] = { 0xFF, 0xFF,
                                                                0x12, 0x34 } */
                                                 rsuint8 Rfpi[5],
                                                             /*!< The RFPI to register
                                                                to in HEX format. */
                                                 rsuint8 Pli);
                                                             /*!< Park bit length */

/****************************************************************************
* FUNCTION:      SendApiPpMmDeleteLocalRegistrationReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_DELETE_LOCAL_REGISTRATION_REQ = 0x5114
****************************************************************************/
void SendApiPpMmDeleteLocalRegistrationReq ( RosTaskIdType Src,
                                             rsuint8 SubscriptionNo);
                                                             /*!< Selects the index in
                                                                the PP subscription database
                                                                where the registrations data
                                                                should be deleted. */

/****************************************************************************
* FUNCTION:      SendApiPpMmUpiAuthenticateRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_UPI_AUTHENTICATE_RES = 0x5118
****************************************************************************/
void SendApiPpMmUpiAuthenticateRes ( RosTaskIdType Src,
                                     rsuint8 Upi[4]);        /*!< 5 bytes holding the UPI
                                                                
                                                                The UPI authentication code
                                                                of the FP. This is a "PIN"
                                                                code of the FP used to
                                                                verify the user during
                                                                location and in normal use.
                                                                The dataformat is BCD and
                                                                the string is 'F' terminated
                                                                (unused nubbled are set to
                                                                'F'). 
                                                                
                                                                Example.
                                                                  API = 1234
                                                                  Upi[4] = { 0xFF, 0xFF,
                                                                0x12, 0x34 } */

/****************************************************************************
* FUNCTION:      SendApiPpMmGetExtHigherLayerCap2Req
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_GET_EXT_HIGHER_LAYER_CAP2_REQ = 0x511F
****************************************************************************/
void SendApiPpMmGetExtHigherLayerCap2Req ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMmGetSubscriptionRfpiReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_GET_SUBSCRIPTION_RFPI_REQ = 0x5123
****************************************************************************/
void SendApiPpMmGetSubscriptionRfpiReq ( RosTaskIdType Src,
                                         rsuint8 SubscriptionNo);
                                                             /*!< The subscription
                                                                number indicated the index
                                                                in the subscription
                                                                database. [1..4] */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIPPMM_H */


