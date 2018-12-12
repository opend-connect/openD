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
* Definition of the ApiCc interface.
*/


#ifndef APICC_H
#define APICC_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! Include of API configuration header. */
#include <Api/ApiCfg.h>
/*! Include of generic API types. */
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
  API_CC_SETUP_REQ = 0x5000,
  API_CC_SETUP_ACK_IND = 0x5001,
  API_CC_CALL_PROC_IND = 0x5002,
  API_CC_ALERT_IND = 0x5003,
  API_CC_CONNECT_IND = 0x5004,
  API_CC_CONNECT_RES = 0x5005,
  API_CC_SETUP_IND = 0x500A,
  API_CC_ALERT_REQ = 0x500B,
  API_CC_CONNECT_REQ = 0x500C,
  API_CC_CONNECT_CFM = 0x500D,
  API_CC_INFO_IND = 0x5031,
  API_CC_INFO_REQ = 0x5032,
  API_CC_RELEASE_REQ = 0x5014,
  API_CC_RELEASE_CFM = 0x5015,
  API_CC_RELEASE_IND = 0x5016,
  API_CC_RELEASE_RES = 0x5017,
  API_CC_REJECT_IND = 0x5018,
  API_CC_REJECT_REQ = 0x5019,
  API_CC_IWU_INFO_IND = 0x5033,
  API_CC_IWU_INFO_REQ = 0x5034,
  API_CC_GET_CONEI_REQ = 0x5036,
  API_CC_GET_CONEI_CFM = 0x5037,
  API_CC_CONEI_CHANGE_IND = 0x502A,
  API_CC_MODIFY_CODEC_REQ = 0x501A,
  API_CC_MODIFY_CODEC_CFM = 0x501B,
  API_CC_MODIFY_CODEC_IND = 0x501C,
  API_CC_MODIFY_CODEC_RES = 0x501D,
  API_CC_IWU_INFO_CODEC_IND = 0x501E,
  API_CC_CALL_WAITING_RES = 0x5020,
  API_CC_SECOND_CALL_INTERCOM_REQ = 0x5021,
  API_CC_SECOND_CALL_EXTERNAL_REQ = 0x5022,
  API_CC_MULTIPARTY_REQ = 0x5023,
  API_CC_TRANSFER_CALL_REQ = 0x5024,
  API_CC_TOGGLE_CALL_REQ = 0x5025,
  API_CC_HOLD_CALL_REQ = 0x502B,
  API_CC_RETRIEVE_CALL_REQ = 0x502C,
  API_CC_END_CALL_REQ = 0x5026,
  API_CC_EXT_CALL_DEFLECTION_REQ = 0x502D,
  API_CC_INT_CALL_DEFLECTION_REQ = 0x502E,
  API_CC_CALL_SCREENING_ACCEPT_REQ = 0x5038,
  API_CC_CALL_SCREENING_INTERCEPT_REQ = 0x5039,
  API_CC_CLMS_DATA_IND = 0x5035,
The global mail primitives MUST be defined in Global.h! */




typedef enum RSENUMTAG(ApiCcCwAcceptType)
{
  API_CC_CW_REJECT            = 0x00, /*!< Reject waiting call */
  API_CC_CW_ACCEPT            = 0x01, /*!< Accept waiting call */
  API_CC_CW_ACCEPT_REL_ACTIVE = 0x02  /*!< Accept waiting call and release active call */
} RSENUM8(ApiCcCwAcceptType);

/*! This type is used to hold the Connection Instance, identifying the
   endpoint in the switch control. */
typedef rsuint16 ApiCcConEiType;


/*! Mail without parameters. */
typedef struct ApiccEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApiccEmptySignalType;

/*! This mail is used by the MMI to initiate a call / connection. The call
   can be:
    external outgoing call
    intercom to another PP
    service connection */
typedef struct ApiCcSetupReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_SETUP_REQ = 0x5000 */
  ApiCcConEiType ConEi;                 /*!< The connection instance for the connection.
                                           The ConEi is supplied by the MMI. A utility
                                           function (TBD) is available for the MMI to
                                           request an individual ConEi  for this call. */
  ApiCcBasicServiceType BasicService;   /*!< Narrow/wide band speech encoding */
  ApiCcCallClassType CallClass;         /*!< DECT defined call classes. */
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
                                           [API_IE_MULTIKEYPAD] 
                                           [API_IE_CALLING_NUMBER]
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_LINE_ID] */
} ApiCcSetupReqType;

/*! This mail is used to indicate that the base needs dial info to proceed
   with the call */
typedef struct ApiCcSetupAckIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_SETUP_ACK_IND = 0x5001 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           the setup_req.
                                           For this call/connection the selected connection
                                           instance should be used for following call
                                           handling mails */
  ApiCcProgressIndType ProgressInd;     /*!< Inband information */
  ApiCcSignalType Signal;               /*!< Alert signal. This is used to request the
                                           MMI to start a certain local tone. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY] */
} ApiCcSetupAckIndType;

/*! This mail is used to inform the MMI of the call progress.
    No more dialed digits will be accepted. */
typedef struct ApiCcCallProcIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CALL_PROC_IND = 0x5002 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  ApiCcProgressIndType ProgressInd;     /*!< Inband information */
  ApiCcSignalType Signal;               /*!< Alert signal. Can be used to control which
                                           ringer melody to be used. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CODEC_LIST] */
} ApiCcCallProcIndType;

/*! This mail is used to inform the MMI when the called party has started
   alerting / ringing. No more dialed digits will be accepted. */
typedef struct ApiCcAlertIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_ALERT_IND = 0x5003 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  ApiCcProgressIndType ProgressInd;     /*!< Inband information */
  ApiCcSignalType Signal;               /*!< Alert signal. Can be used to control which
                                           ringer melody to be used. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CODEC_LIST] */
} ApiCcAlertIndType;

/*! This mail is used to inform the MMI when the called party has answered
   the call. The audio shall be unmuted if not already done. */
typedef struct ApiCcConnectIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CONNECT_IND = 0x5004 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CODEC_LIST] */
} ApiCcConnectIndType;

/*! This mail informs the FP that the audio is connected. In many
   implementations it is not used, and the FP just connects the audio a short
   time after the connect_ind is sent. */
typedef struct ApiCcConnectResType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CONNECT_RES = 0x5005 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CODEC_LIST] */
} ApiCcConnectResType;

/*! This mail is used to inform the MMI of an incoming air link from the
   protocol. E.g. incoming call from the PSTN, intercom calls, service
   connections, etc... */
typedef struct ApiCcSetupIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_SETUP_IND = 0x500A */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  ApiCcBasicServiceType BasicService;   /*!< Narrow/wide band speech encoding */
  ApiCcCallClassType CallClass;         /*!< DECT defined call classes. */
  ApiCcSignalType Signal;               /*!< Alert signal. Can be used to control which
                                           ringer melody is used at Called endpoint. */
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
                                           [API_IE_CALLING_PARTY_NUMBER] 
                                           [API_IE_CALLING_PARTY_NAME]
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcSetupIndType;

/*! This mail is used by the MMI to inform the protocol that a SetupInd has
   been received and that MMI has indicated the alert to the user. */
typedef struct ApiCcAlertReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_ALERT_REQ = 0x500B */
  ApiCcConEiType ConEi;                 /*!< The handset id and connection instance. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CODEC_LIST] */
} ApiCcAlertReqType;

/*! This mail is used by the MMI to request the protocol to answer the
   call. */
typedef struct ApiCcConnectReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CONNECT_REQ = 0x500C */
  ApiCcConEiType ConEi;                 /*!< The handset id and connection instance. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CODEC_LIST] */
} ApiCcConnectReqType;

/*! This mail is used by the API to inform the MMI that the connection is established.
    The audio path to the handset is established and shall now be unmuted, if
   not already done. */
typedef struct ApiCcConnectCfmType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CONNECT_CFM = 0x500D */
  ApiCcConEiType ConEi;                 /*!< The handset id and connection instance. */
} ApiCcConnectCfmType;

/*! This mail is used to send various information from FP to PP. */
typedef struct ApiCcInfoIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_INFO_IND = 0x5031 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           the setup_req.
                                           For this call/connection the selected connection
                                           instance should be used for following call
                                           handling mails */
  ApiCcProgressIndType ProgressInd;     /*!< Inband information */
  ApiCcSignalType Signal;               /*!< Alert signal. This is used to request the
                                           MMI to start a certain local tone. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CALLING_PARTY_NUMBER] 
                                           [API_IE_CALLING_PARTY_NAME]
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID]
                                           [API_IE_CALL_STATUS]
                                           [API_IE_MULTI_DISPLAY] */
} ApiCcInfoIndType;

/*! This mail is used to send various information from PP to FP */
typedef struct ApiCcInfoReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_INFO_REQ = 0x5032 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           the setup_req.
                                           For this call/connection the selected connection
                                           instance should be used for following call
                                           handling mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_MULTIKEYPAD]
                                           [API_IE_CALLED_NUMBER]
                                           [API_IE_CODEC_LIST] 
                                           [API_IE_IWU_TO_IWU] 
                                           [API_IE_PROPRIETARY]
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcInfoReqType;

/*! This mail is used by the MMI to terminate a call. */
typedef struct ApiCcReleaseReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_RELEASE_REQ = 0x5014 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  ApiCcReleaseReasonType Reason;        /*!< DECT reason code */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_RELEASE_EXT_REASON]
                                           [API_IE_PROPRIETARY] */
} ApiCcReleaseReqType;

/*! This mail is used indicate to the MMI a confirmation of the
   API_FP_RELEASE_REQ command. */
typedef struct ApiCcReleaseCfmType
{
  RosPrimitiveType Primitive;            /*!< API_CC_RELEASE_CFM = 0x5015 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_PROPRIETARY] */
} ApiCcReleaseCfmType;

/*! This mail is used to inform the MMI when the connected party has
   terminated the ongoing call or reject an incoming call. */
typedef struct ApiCcReleaseIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_RELEASE_IND = 0x5016 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  ApiCcReleaseReasonType Reason;        /*!< DECT reason code */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_RELEASE_EXT_REASON]
                                           [API_IE_PROPRIETARY] */
} ApiCcReleaseIndType;

/*! This mail is used by the MMI to inform the handset when the call is
   released, ie. the MMI has muted the audio. */
typedef struct ApiCcReleaseResType
{
  RosPrimitiveType Primitive;            /*!< API_CC_RELEASE_RES = 0x5017 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_PROPRIETARY] */
} ApiCcReleaseResType;

/*! This mail is used to inform the MMI when e.g. a connection setup has
   been rejected */
typedef struct ApiCcRejectIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_REJECT_IND = 0x5018 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  ApiCcReleaseReasonType Reason;        /*!< DECT reason code */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_RELEASE_EXT_REASON] */
} ApiCcRejectIndType;

/*! This mail is used by the MMI to reject a call. */
typedef struct ApiCcRejectReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_REJECT_REQ = 0x5019 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  ApiCcReleaseReasonType Reason;        /*!< DECT reason code */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [IE_RELEASE_EXT_REASON] */
} ApiCcRejectReqType;

/*! This mail is used by the MMI to receive IWU Info messages during a
   call. Typically used to receive messages using LRMS. */
typedef struct ApiCcIwuInfoIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_IWU_INFO_IND = 0x5033 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements: 
                                           [API_IE_MMS_GEN_HEADER]
                                           [API_IE_MMS_OBJ_HEADER]
                                           [API_IE_MMS_EXT_HEADER]
                                           [API_IE_TIME_DATE]
                                           [API_IE_SEGMENT_INFO]
                                           [API_IE_IWU_TO_IWU]
                                           
                                           NOTE:
                                           Some of the Infoelements are only available if
                                           SMS support is enabled */
} ApiCcIwuInfoIndType;

/*! This mail is used by the MMI to send IWU Info messages during a call.
   Typically used to send messages using LRMS. */
typedef struct ApiCcIwuInfoReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_IWU_INFO_REQ = 0x5034 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements: 
                                           [API_IE_MMS_GEN_HEADER]
                                           [API_IE_MMS_OBJ_HEADER]
                                           [API_IE_MMS_EXT_HEADER]
                                           [API_IE_TIME_DATE]
                                           [API_IE_SEGMENT_INFO]
                                           [API_IE_IWU_TO_IWU]
                                           
                                           NOTE:
                                           Some of the Infoelements are only available if
                                           SMS support is enabled */
} ApiCcIwuInfoReqType;

/*! This command is used to request a connection EI for a new connection. */
typedef ApiccEmptySignalType ApiCcGetConeiReqType;

/*! This command is used to confirm the API_CC_GET_CONEI_REQ command. */
typedef struct ApiCcGetConeiCfmType
{
  RosPrimitiveType Primitive;            /*!< API_CC_GET_CONEI_CFM = 0x5037 */
  ApiCcConEiType ConEi;                 /*!< Connection endpoint identifier */
} ApiCcGetConeiCfmType;

/*! This mail is used to inform the MMI when the switch control have
   changed the ConEI of the ongoing call. When the MMI receives this mail, the
   NewConEi should be used in stead of the original ConeEi as connection
   reference for the call. */
typedef struct ApiCcConeiChangeIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CONEI_CHANGE_IND = 0x502A */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. */
  ApiCcConEiType NewConEi;              /*!< The New Instance of the connection
                                           re-assigned by switch control. For further
                                           signaling the handling of the call/connection the
                                           received NewConEi should be used. */
} ApiCcConeiChangeIndType;

/*! This mail is used by the MMI to request a CODEC change for a
   connection. */
typedef struct ApiCcModifyCodecReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_MODIFY_CODEC_REQ = 0x501A */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Required Infoelements:
                                           [API_IE_CODEC_LIST]
                                           The Codec list shall contain one and only one
                                           codec. */
} ApiCcModifyCodecReqType;

/*! Used by the MMI to confirm the API_CC_MODIFY_CODEC_REQ. If the change
   is accepted then the audio must be muted. */
typedef struct ApiCcModifyCodecCfmType
{
  RosPrimitiveType Primitive;            /*!< API_CC_MODIFY_CODEC_CFM = 0x501B */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiCcModifyCodecCfmType;

/*! This mail is used to inform the MMI when a handset has requested a
   CODEC change for a connection. */
typedef struct ApiCcModifyCodecIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_MODIFY_CODEC_IND = 0x501C */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_CODEC_LIST]
                                           The Codec list shall contain one and only one
                                           codec. */
} ApiCcModifyCodecIndType;

/*! This mail is used by the MMI to accept or reject a code change
   requested by a handset. If the change is accepted, then the audio must be
   muted. */
typedef struct ApiCcModifyCodecResType
{
  RosPrimitiveType Primitive;            /*!< API_CC_MODIFY_CODEC_RES = 0x501D */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiCcModifyCodecResType;

/*! This mail is used by the API to inform the MMI when the CODEC has been
   changed for a connection and the audio shall be unmuted. */
typedef struct ApiCcIwuInfoCodecIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_IWU_INFO_CODEC_IND = 0x501E */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                            [API_IE_CODEC_LIST]
                                           The Codec list shall contain one and only one
                                           codec. */
} ApiCcIwuInfoCodecIndType;

/*! This mail is used by the MMI to either accept or reject the call waiting.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x35} to the switch control if Accept is TRUE otherwise {0x1c,
   0x36}. */
typedef struct ApiCcCallWaitingResType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CALL_WAITING_RES = 0x5020 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  ApiCcCwAcceptType Accept;             /*!< Accept = 1 if the Call Waiting is accepted. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the format:
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcCallWaitingResType;

/*! This mail is sent from MMI to request a second intercom call. (putting
   the other call party on hold call the selected second party)
    When received by the API it will then send a Multi-Keypad info element
   with {0x17, keypad} to the switch control.
    
    If the multikeypad is a ?*? then it will be interpreted as a call to all handsets.
    In case there is no ambiguity (i.e. when there are only two registered PPs
   switched on), the MultikeypadLength can be 0. */
typedef struct ApiCcSecondCallIntercomReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_SECOND_CALL_INTERCOM_REQ = 0x5021 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_MULTIKEYPAD] */
} ApiCcSecondCallIntercomReqType;

/*! This mail is sent from MMI to request a second external call. (putting
   the other call party on hold, then call the selected second party)
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x15, keypad} to the switch control. */
typedef struct ApiCcSecondCallExternalReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_SECOND_CALL_EXTERNAL_REQ = 0x5022 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_MULTIKEYPAD]
                                           [API_IE_LINE_ID] */
} ApiCcSecondCallExternalReqType;

/*! This mail is sent from MMI to request a multiparty call.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x32} to the switch control.
    The current call and a held call will be joined. */
typedef struct ApiCcMultipartyReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_MULTIPARTY_REQ = 0x5023 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcMultipartyReqType;

/*! This mail is sent from MMI to transfer a call to another party.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x34} to the switch control. */
typedef struct ApiCcTransferCallReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_TRANSFER_CALL_REQ = 0x5024 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcTransferCallReqType;

/*! This mail is sent from MMI to toggle between two call parties. (e.g.
   the PSTN line and a handset)
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x31} to the switch control. */
typedef struct ApiCcToggleCallReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_TOGGLE_CALL_REQ = 0x5025 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcToggleCallReqType;

/*! This mail is used by the MMI to put the active call on hold.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x41} to the switch control. */
typedef struct ApiCcHoldCallReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_HOLD_CALL_REQ = 0x502B */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcHoldCallReqType;

/*! This mail is used by the MMI to retrieve a held call.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x42} to the switch control. */
typedef struct ApiCcRetrieveCallReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_RETRIEVE_CALL_REQ = 0x502C */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcRetrieveCallReqType;

/*! This mail is used by the MMI to end the call that is indicated by the SystemCallId.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x33} to the switch control. */
typedef struct ApiCcEndCallReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_END_CALL_REQ = 0x5026 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_LINE_ID]
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcEndCallReqType;

/*! This mail is used by the MMI to request redirection of an incoming call
   to an external party.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x39, 0x15} to the switch control. */
typedef struct ApiCcExtCallDeflectionReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_EXT_CALL_DEFLECTION_REQ = 0x502D */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_MULTIKEYPAD] */
} ApiCcExtCallDeflectionReqType;

/*! This mail is used by the MMI to request redirection of an incoming call
   to an internal party.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x39, 0x17} to the switch control. */
typedef struct ApiCcIntCallDeflectionReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_INT_CALL_DEFLECTION_REQ = 0x502E */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_MULTIKEYPAD] */
} ApiCcIntCallDeflectionReqType;

/*! This mail is used by the MMI to accept a call screening setup req.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x48} to the switch control. */
typedef struct ApiCcCallScreeningAcceptReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CALL_SCREENING_ACCEPT_REQ = 0x5038 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcCallScreeningAcceptReqType;

/*! This mail is used by the MMI to connect to a screened call and stop the TAM.
    When received by the API it will then send a Multi-Keypad info element
   with {0x1c, 0x49} to the switch control. */
typedef struct ApiCcCallScreeningInterceptReqType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CALL_SCREENING_INTERCEPT_REQ = 0x5039 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_SYSTEM_CALL_ID] */
} ApiCcCallScreeningInterceptReqType;

/*! This mail is used by the API to send incoming CLMS data with
   infoelements to the MMI. */
typedef struct ApiCcClmsDataIndType
{
  RosPrimitiveType Primitive;            /*!< API_CC_CLMS_DATA_IND = 0x5035 */
  ApiCcConEiType ConEi;                 /*!< The Instance of the connection defined by
                                           switch control. For this call/connection the
                                           received ConnectionEi should be used for
                                           responding mails */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElementList can hold a number Info
                                           Elements placed in the in the format
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Each element is packed following the ApiInfoElementType.
                                           
                                           At reception the receiving task should search
                                           through the info data package to search for the
                                           requested elements and pick out the info data.
                                           
                                           Possible Infoelements:
                                           [API_IE_PORTABLE_IDENTITY]
                                           [API_IE_MMS_GEN_HEADER]
                                           [API_IE_MMS_OBJ_HEADER]
                                           [API_IE_MMS_EXT_HEADER]
                                           [API_IE_TIME_DATE]
                                           [API_IE_SEGMENT_INFO]
                                           [API_IE_IWU_TO_IWU]
                                           
                                           NOTE:
                                           Some of the Infoelements are only available if
                                           SMS support is enabled */
} ApiCcClmsDataIndType;

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
* FUNCTION:      SendApiCcSetupReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_SETUP_REQ = 0x5000
****************************************************************************/
void SendApiCcSetupReq ( RosTaskIdType Src,
                         ApiCcConEiType ConEi,               /*!< The connection
                                                                instance for the connection.
                                                                The ConEi is supplied by the
                                                                MMI. A utility function
                                                                (TBD) is available for the
                                                                MMI to request an individual
                                                                ConEi  for this call. */
                         ApiCcBasicServiceType BasicService,  /*!< Narrow/wide band
                                                                 speech encoding */
                         ApiCcCallClassType CallClass,       /*!< DECT defined call
                                                                classes. */
                         rsuint16 InfoElementLength,         /*!< The length of the Data
                                                                Information Element */
                         rsuint8 InfoElement[1]);            /*!< The InfoElementList
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
                                                                [API_IE_MULTIKEYPAD] 
                                                                [API_IE_CALLING_NUMBER]
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_LINE_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcConnectRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CONNECT_RES = 0x5005
****************************************************************************/
void SendApiCcConnectRes ( RosTaskIdType Src,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiCcAlertReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_ALERT_REQ = 0x500B
****************************************************************************/
void SendApiCcAlertReq ( RosTaskIdType Src,
                         ApiCcConEiType ConEi,               /*!< The handset id and
                                                                connection instance. */
                         rsuint16 InfoElementLength,         /*!< The length of the Data
                                                                Information Element */
                         rsuint8 InfoElement[1]);            /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiCcConnectReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CONNECT_REQ = 0x500C
****************************************************************************/
void SendApiCcConnectReq ( RosTaskIdType Src,
                           ApiCcConEiType ConEi,             /*!< The handset id and
                                                                connection instance. */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiCcInfoReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_INFO_REQ = 0x5032
****************************************************************************/
void SendApiCcInfoReq ( RosTaskIdType Src,
                        ApiCcConEiType ConEi,                /*!< The Instance of the
                                                                connection defined by the setup_req.
                                                                For this call/connection
                                                                the selected connection
                                                                instance should be used for
                                                                following call handling
                                                                mails */
                        rsuint16 InfoElementLength,          /*!< The length of the Data
                                                                Information Element */
                        rsuint8 InfoElement[1]);             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_MULTIKEYPAD]
                                                                [API_IE_CALLED_NUMBER]
                                                                [API_IE_CODEC_LIST] 
                                                                [API_IE_IWU_TO_IWU] 
                                                                [API_IE_PROPRIETARY]
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcReleaseReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_RELEASE_REQ = 0x5014
****************************************************************************/
void SendApiCcReleaseReq ( RosTaskIdType Src,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           ApiCcReleaseReasonType Reason,    /*!< DECT reason code */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_RELEASE_EXT_REASON]
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiCcReleaseRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_RELEASE_RES = 0x5017
****************************************************************************/
void SendApiCcReleaseRes ( RosTaskIdType Src,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_PROPRIETARY] */

/****************************************************************************
* FUNCTION:      SendApiCcRejectReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_REJECT_REQ = 0x5019
****************************************************************************/
void SendApiCcRejectReq ( RosTaskIdType Src,
                          ApiCcConEiType ConEi,              /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                          ApiCcReleaseReasonType Reason,     /*!< DECT reason code */
                          rsuint16 InfoElementLength,        /*!< The length of the Data
                                                                Information Element */
                          rsuint8 InfoElement[1]);           /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [IE_RELEASE_EXT_REASON] */

/****************************************************************************
* FUNCTION:      SendApiCcIwuInfoReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_IWU_INFO_REQ = 0x5034
****************************************************************************/
void SendApiCcIwuInfoReq ( RosTaskIdType Src,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements: 
                                                                [API_IE_MMS_GEN_HEADER]
                                                                [API_IE_MMS_OBJ_HEADER]
                                                                [API_IE_MMS_EXT_HEADER]
                                                                [API_IE_TIME_DATE]
                                                                [API_IE_SEGMENT_INFO]
                                                                [API_IE_IWU_TO_IWU]
                                                                
                                                                NOTE:
                                                                Some of the Infoelements
                                                                are only available if SMS
                                                                support is enabled */

/****************************************************************************
* FUNCTION:      SendApiCcGetConeiReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_GET_CONEI_REQ = 0x5036
****************************************************************************/
void SendApiCcGetConeiReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiCcModifyCodecReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_MODIFY_CODEC_REQ = 0x501A
****************************************************************************/
void SendApiCcModifyCodecReq ( RosTaskIdType Src,
                               ApiCcConEiType ConEi,         /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                               rsuint16 InfoElementLength,   /*!< The length of the Data
                                                                Information Element */
                               rsuint8 InfoElement[1]);      /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Required Infoelements:
                                                                [API_IE_CODEC_LIST]
                                                                The Codec list shall
                                                                contain one and only one
                                                                codec. */

/****************************************************************************
* FUNCTION:      SendApiCcModifyCodecRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_MODIFY_CODEC_RES = 0x501D
****************************************************************************/
void SendApiCcModifyCodecRes ( RosTaskIdType Src,
                               ApiCcConEiType ConEi,         /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                               RsStatusType Status);         /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiCcCallWaitingRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CALL_WAITING_RES = 0x5020
****************************************************************************/
void SendApiCcCallWaitingRes ( RosTaskIdType Src,
                               ApiCcConEiType ConEi,         /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                               ApiCcCwAcceptType Accept,     /*!< Accept = 1 if the Call
                                                                Waiting is accepted. */
                               rsuint16 InfoElementLength,   /*!< The length of the Data
                                                                Information Element */
                               rsuint8 InfoElement[1]);      /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcSecondCallIntercomReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_SECOND_CALL_INTERCOM_REQ = 0x5021
****************************************************************************/
void SendApiCcSecondCallIntercomReq ( RosTaskIdType Src,
                                      ApiCcConEiType ConEi,  /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                                      rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                      rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_MULTIKEYPAD] */

/****************************************************************************
* FUNCTION:      SendApiCcSecondCallExternalReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_SECOND_CALL_EXTERNAL_REQ = 0x5022
****************************************************************************/
void SendApiCcSecondCallExternalReq ( RosTaskIdType Src,
                                      ApiCcConEiType ConEi,  /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                                      rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                      rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_MULTIKEYPAD]
                                                                [API_IE_LINE_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcMultipartyReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_MULTIPARTY_REQ = 0x5023
****************************************************************************/
void SendApiCcMultipartyReq ( RosTaskIdType Src,
                              ApiCcConEiType ConEi,          /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                              rsuint16 InfoElementLength,    /*!< The length of the Data
                                                                Information Element */
                              rsuint8 InfoElement[1]);       /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcTransferCallReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_TRANSFER_CALL_REQ = 0x5024
****************************************************************************/
void SendApiCcTransferCallReq ( RosTaskIdType Src,
                                ApiCcConEiType ConEi,        /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                                rsuint16 InfoElementLength,  /*!< The length of the Data
                                                                Information Element */
                                rsuint8 InfoElement[1]);     /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcToggleCallReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_TOGGLE_CALL_REQ = 0x5025
****************************************************************************/
void SendApiCcToggleCallReq ( RosTaskIdType Src,
                              ApiCcConEiType ConEi,          /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                              rsuint16 InfoElementLength,    /*!< The length of the Data
                                                                Information Element */
                              rsuint8 InfoElement[1]);       /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcHoldCallReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_HOLD_CALL_REQ = 0x502B
****************************************************************************/
void SendApiCcHoldCallReq ( RosTaskIdType Src,
                            ApiCcConEiType ConEi,            /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                            rsuint16 InfoElementLength,      /*!< The length of the Data
                                                                Information Element */
                            rsuint8 InfoElement[1]);         /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcRetrieveCallReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_RETRIEVE_CALL_REQ = 0x502C
****************************************************************************/
void SendApiCcRetrieveCallReq ( RosTaskIdType Src,
                                ApiCcConEiType ConEi,        /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                                rsuint16 InfoElementLength,  /*!< The length of the Data
                                                                Information Element */
                                rsuint8 InfoElement[1]);     /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcEndCallReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_END_CALL_REQ = 0x5026
****************************************************************************/
void SendApiCcEndCallReq ( RosTaskIdType Src,
                           ApiCcConEiType ConEi,             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_LINE_ID]
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcExtCallDeflectionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_EXT_CALL_DEFLECTION_REQ = 0x502D
****************************************************************************/
void SendApiCcExtCallDeflectionReq ( RosTaskIdType Src,
                                     ApiCcConEiType ConEi,   /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                                     rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                     rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_MULTIKEYPAD] */

/****************************************************************************
* FUNCTION:      SendApiCcIntCallDeflectionReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_INT_CALL_DEFLECTION_REQ = 0x502E
****************************************************************************/
void SendApiCcIntCallDeflectionReq ( RosTaskIdType Src,
                                     ApiCcConEiType ConEi,   /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                                     rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                     rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_MULTIKEYPAD] */

/****************************************************************************
* FUNCTION:      SendApiCcCallScreeningAcceptReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CALL_SCREENING_ACCEPT_REQ = 0x5038
****************************************************************************/
void SendApiCcCallScreeningAcceptReq ( RosTaskIdType Src,
                                       ApiCcConEiType ConEi,  /*!< The Instance of the
                                                                 connection defined by
                                                                 switch control. For this
                                                                 call/connection the
                                                                 received ConnectionEi
                                                                 should be used for
                                                                 responding mails */
                                       rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                       rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_SYSTEM_CALL_ID] */

/****************************************************************************
* FUNCTION:      SendApiCcCallScreeningInterceptReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_CC_CALL_SCREENING_INTERCEPT_REQ = 0x5039
****************************************************************************/
void SendApiCcCallScreeningInterceptReq ( RosTaskIdType Src,
                                          ApiCcConEiType ConEi,
                                                             /*!< The Instance of the
                                                                connection defined by switch
                                                                control. For this
                                                                call/connection the received
                                                                ConnectionEi should be used
                                                                for responding mails */
                                          rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                          rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                [API_IE_SYSTEM_CALL_ID] */


/****************************************************************************
*                             Function prototypes
****************************************************************************/
/****************************************************************************
*  FUNCTION:       ApiCcGetConEi
*
*  RETURNS :       The Connection Instance.
*
*  DESCRIPTION:    This function is used to allocate a unique connection
                   instance (call id) to be used when setting up a call from
                   the app. The connection instance returned must be used when
                   API_CC_SETUP_REQ is sent.
****************************************************************************/
ApiCcConEiType ApiCcGetConEi(void);


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APICC_H */


