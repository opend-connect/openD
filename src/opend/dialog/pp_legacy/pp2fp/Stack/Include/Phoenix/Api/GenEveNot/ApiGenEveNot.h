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
* Definition of the ApiGenEveNot interface.
*/


#ifndef APIGENEVENOT_H
#define APIGENEVENOT_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API configuration file must be included. */
#include <Api/ApiCfg.h>
/*! Include of common API types . */
#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! Used as ApiLineIdType when the event is not related to any line. */
#define API_LINE_ID_INVALID 0xFF

/*! This type describes features available in this API. */
#define API_FP_GENEVENOT_EXTENDED_TERMINAL_ID_SUPPORT 0x01

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_FP_GENEVENOT_EVENT_REQ = 0x5700,
  API_FP_GENEVENOT_EVENT_IND = 0x5701,
  API_FP_GENEVENOT_PP_EVENT_IND = 0x5702,
  API_FP_GENEVENOT_FEATURES_REQ =  0x5708,
  API_FP_GENEVENOT_FEATURES_CFM =  0x5709,
  API_PP_GENEVENOT_EVENT_REQ = 0x5703,
  API_PP_GENEVENOT_EVENT_IND = 0x5704,
End of mail primitives. */



/*! Include of LAS API types. */
#ifdef PHOENIX_API_LAS
#include <Phoenix/Api/Las/ApiLas.h>
#endif

/*! Specified as a bitfield with handset number 1 as bit no. 0. */
typedef rsuint32 ApiGenAttachedHandsetsType;

/*! This enum holds the different line identifier sub types */
typedef enum RSENUMTAG(ApiGenLineIdSubType)
{
  API_GEN_LINEIDSUB_EXT         = 0x00, /*!< Line identifier for external call */
  API_GEN_LINEIDSUB_RELATING_TO = 0x03, /*!< Releating to */
  API_GEN_LINEIDSUB_ALL         = 0x04  /*!< All lines */
} RSENUM8(ApiGenLineIdSubType);

/*! This enum holds the different types of Generic Event Notifications */
typedef enum RSENUMTAG(ApiGenEveNotEventType)
{
  API_GEN_MESSAGE_WAITING = 0x00, /*!< Voice message waiting notification type */
  API_GEN_MISSED_CALL     = 0x01, /*!< Missed call notification type */
  API_GEN_WEB_CONTENT     = 0x02, /*!< Web content notification type */
  API_GEN_LIST_CHANGE_IND = 0x03, /*!< List change notification type */
  API_GEN_SW_UPGRADE_IND  = 0x04, /*!< Software upgrade indication */
  API_GEN_PROPREITARY     = 0x40  /*!< Propreitary event type. Properitary event types
                                     can be added as needed in the range [0x40 - 0x7F] */
} RSENUM8(ApiGenEveNotEventType);

/*! This enum describes the event sub types to be used when the event is an
   API_GEN_MESSAGE_WAITING event. */
typedef enum RSENUMTAG(ApiGenEveNotMessageWaitingEventSubType)
{
  API_GEN_MWS_UNKNOWN       = 0x00, /*!< Unkown message subtype */
  API_GEN_MWS_VOICE_MESSAGE = 0x01, /*!< Voice message subtype */
  API_GEN_MWS_SMS_MESSAGE   = 0x02, /*!< SMS message subtype */
  API_GEN_MWS_EMAIL_MESSAGE = 0x03, /*!< E-mail message subtype */
  API_GEN_MWS_NO_SUBTYPE    = 0xFF  /*!< No message subtype */
} RSENUM8(ApiGenEveNotMessageWaitingEventSubType);

/*! This enum describes the event sub types to be used when the event is an
   API_GEN_MISSED_CALL event. */
typedef enum RSENUMTAG(ApiGenEveNotMissedCallEventSubType)
{
  API_GEN_MCS_UNKNOWN         = 0x00, /*!< Unknown missed call subtype */
  API_GEN_MCS_NEW_MISSED_CALL = 0x01, /*!< New missed voice call arrived */
  API_GEN_MCS_LIST_MODIFIED   = 0x02, /*!< No new missed call, but number of unread
                                         entries may have changed */
  API_GEN_MCS_NO_SUBTYPE      = 0xFF  /*!< No missed call subtype */
} RSENUM8(ApiGenEveNotMissedCallEventSubType);

/*! This enum describes the event sub types to be used when the event is an
   API_GEN_WEB_CONTENT event. */
typedef enum RSENUMTAG(ApiGenEveNotWebContentEventSubType)
{
  API_GEN_WCS_UNKNOWN         = 0x00, /*!< Unknown web content subtype */
  API_GEN_WCS_RSS_DESCRIPTION = 0x01, /*!< RSS description subtype */
  API_GEN_WCS_NO_SUBTYPE      = 0xFF  /*!< No web content subtype */
} RSENUM8(ApiGenEveNotWebContentEventSubType);

/*! This enum describes the event sub types to be used when the event is an
   API_GEN_SW_UPGRADE_IND event. */
typedef enum RSENUMTAG(ApiGenEveNotSwUpgradeEventSubType)
{
  API_GEN_SWU_UNKNOWN          = 0x00, /*!< Unknown */
  API_GEN_SWU_FIRMWARE_UPGRADE = 0x01, /*!< Firmware upgrade */
  API_GEN_SWU_PROPRIETARY      = 0x40  /*!< Reserved for proprietary upgrade codes */
} RSENUM8(ApiGenEveNotSwUpgradeEventSubType);

/*! List change event. */
typedef enum RSENUMTAG(ApiGenEveNotLcEventType)
{
  API_GEN_LC_EVENT_NEW       = 0x00, /*!< A new entry has been added to the list. */
  API_GEN_LC_EVENT_MODIFY    = 0x01, /*!< An existing entry has been edited. */
  API_GEN_LC_EVENT_DELETE    = 0x02, /*!< An entry has been deleted. */
  API_GEN_LC_EVENT_RS_UNREAD = 0x03, /*!< An entry has been marked as unread. */
  API_GEN_LC_EVENT_RS_READ   = 0x04  /*!< An entry has been marked as read. */
} RSENUM8(ApiGenEveNotLcEventType);

/*! List changed (added). */
#ifdef PHOENIX_API_LAS
typedef struct ApiGenEveNotLcDataGeneralType
{
  rsuint8 LengthOfEntryFields;          /*!< Number of entry fields that was modified */
  ApiIeType EntryFields[1];             /*!< List of entry field ids that was modified */
} ApiGenEveNotLcDataGeneralType;
#endif

/*! List changed (added/deleted). */
#ifdef PHOENIX_API_LAS
typedef struct ApiGenEveNotLcDataDeleteType
{
  rsuint16 ieBlockLength;
  ApiInfoElementType ieBlockPtr[1];
} ApiGenEveNotLcDataDeleteType;
#endif

/*! List change (added). */
#ifdef PHOENIX_API_LAS
typedef union ApiGenEveNotLcDataUnionType
{
  ApiGenEveNotLcDataGeneralType General;
  ApiGenEveNotLcDataDeleteType Delete;
} ApiGenEveNotLcDataUnionType;
#endif

/*! List change (added). */
#ifdef PHOENIX_API_LAS
typedef struct ApiGenEveNotListChangeAddDataType
{
  ApiGenEveNotLcEventType ListEventType;
  ApiLasEntryIdType EntryIdentifier;    /*!< EntryIdentifier of the entry that was
                                           modified (0 if entire list was modified). */
  ApiLasEntryIndexType CurrentIndex;    /*!< Current (new) index of the entry that was
                                           modified (0 if entire list was modified or an
                                           entry was deleted). */
  ApiGenEveNotLcDataUnionType Data;
} ApiGenEveNotListChangeAddDataType;
#endif

/*! This type describes the actual event notification. It consists of an
   event type, one of the corresponding event subtypes and the event
   multiplicity which should be used to indicate how many unconsulted events
   of the specific type that is waiting. */
typedef struct ApiGenEveNotEventNotificationType
{
  ApiGenEveNotEventType EventType;      /*!< The event notification type */
  rsuint8 EventSubType;                 /*!< The related event notification sub type. */
  rsuint16 EventMultiplicity;           /*!< The event multiplicity which indicates how
                                           many unconsulted events of the specific sub type
                                           that is waiting. */
  rsuint16 LengthOfData;                /*!< Length of additional event data */
  rsuint8 Data[1];                      /*!< Additional event data (Only available on Fp
                                           API). In case of no additional event data
                                           (LengthOfData = 0) this byte shall not be
                                           included in the total length of the event. */
} ApiGenEveNotEventNotificationType;

/*! This type describes the format of a Proprietary event notification. */
typedef struct ApiGenEveNotProprietaryEventNotificationType
{
  ApiGenEveNotEventType EventType;      /*!< The event notification type. All
                                           proprietary events shall be in the range [0x40 -
                                           0x7F]. */
  rsuint16 Discriminator;               /*!< The discriminator field shall contain the
                                           EMC. */
  rsuint8 LengthOfData;                 /*!< Length proprietary event data. */
  rsuint8 Data[1];                      /*!< Proprietary event data. */
} ApiGenEveNotProprietaryEventNotificationType;

/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiFpGenEveNotFeatureType;


/*! Mail without parameters. */
typedef struct ApigenevenotEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApigenevenotEmptySignalType;

/*! This mail is sent from the FpApplication to sent a generic events
   notification. */
typedef struct ApiFpGenevenotEventReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GENEVENOT_EVENT_REQ = 0x5700 */
  rsbool EnableIndication;              /*!< If TRUE then an API_GENEVENOT_EVENT_IND
                                           will be returned through the API. */
  ApiGenLineIdSubType LineIdSubType;    /*!< The line identifier subtype of the line
                                           related to the event. */
  rsuint8 LineIdValue;                  /*!< Range 0x00-0x7F
                                           API_LINE_ID_INVALID = 0xFF indicates that no
                                           line ID is added */
  ApiGenAttachedHandsetsType AttachedHandsets; /*!< The clients (PP) to be notified of
                                                   the event. */
  rsuint8 EventNotificationCount;       /*!< Number of event notifications in the mail. */
  rsuint16 LengthOfData;                /*!< Length of notification data in bytes. */
  rsuint8 Data[1];                      /*!< Notification data. This shall be formatted
                                           as one or more ApiGenEveNotEventNotificationType
                                           or ApiGenEveNotProprietaryEventNotificationType. */
} ApiFpGenevenotEventReqType;

/*! This mail is used to inform the FpApplication when there is an events
   notification from the FP. */
typedef struct ApiFpGenevenotEventIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GENEVENOT_EVENT_IND = 0x5701 */
  ApiGenLineIdSubType LineIdSubType;    /*!< The line identifier subtype of the line
                                           related to the event */
  rsuint8 LineIdValue;                  /*!< Range 0x00-0x7F
                                           API_LINE_ID_INVALID = 0xFF indicates that no
                                           line ID is added */
  rsuint8 CountOfEvents;                /*!< Number of event notifications in the mail */
  rsuint16 LengthOfData;                /*!< Length of notification data in bytes. */
  rsuint8 Data[1];                      /*!< Notification data. This shall be formatted
                                           as one or more ApiGenEveNotEventNotificationType
                                           or ApiGenEveNotProprietaryEventNotificationType. */
} ApiFpGenevenotEventIndType;

/*! This mail is used to inform the FpApplication when there is an events
   notification sent from a PP. */
typedef struct ApiFpGenevenotPpEventIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GENEVENOT_PP_EVENT_IND = 0x5702 */
  ApiTerminalIdType TerminalId;         /*!< HandsetId of handset that sent the event. */
  rsuint8 CountOfEvents;                /*!< Number of event notifications in the mail */
  rsuint16 LengthOfData;                /*!< Length of notification data in bytes. */
  rsuint8 Data[1];                      /*!< Notification data. This shall be formatted
                                           as one or more ApiGenEveNotEventNotificationType
                                           or ApiGenEveNotProprietaryEventNotificationType. */
} ApiFpGenevenotPpEventIndType;

/*! This command is used to enable/disable features in the FpGenevenot API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiFpGenevenotFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GENEVENOT_FEATURES_REQ =  0x5708 */
  ApiFpGenEveNotFeatureType ApiFpGenEveNotFeature; /*!< Requested features */
} ApiFpGenevenotFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiFpGenevenotFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GENEVENOT_FEATURES_CFM =  0x5709 */
  RsStatusType Status;
  ApiFpGenEveNotFeatureType ApiFpGenEveNotFeature; /*!< Supported features */
} ApiFpGenevenotFeaturesCfmType;

/*! This mail is used to send a generic event notification from the
   PpApplication to the base. */
typedef struct ApiPpGenevenotEventReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_GENEVENOT_EVENT_REQ = 0x5703 */
  rsuint8 EventNotificationCount;       /*!< Number of event notifications in the mail. */
  rsuint16 LengthOfData;                /*!< Length of notification data in bytes. */
  rsuint8 Data[1];                      /*!< Notification data. This shall be formatted
                                           as one or more ApiGenEveNotEventNotificationType
                                           or ApiGenEveNotProprietaryEventNotificationType. */
} ApiPpGenevenotEventReqType;

/*! This mail is used to inform the PPApplication when there is an events
   notification from the FP. */
typedef struct ApiPpGenevenotEventIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_GENEVENOT_EVENT_IND = 0x5704 */
  ApiGenLineIdSubType LineIdSubType;    /*!< The line identifier subtype of the line
                                           related to the event */
  rsuint8 LineIdValue;                  /*!< Range 0x00-0x7F
                                           API_LINE_ID_INVALID = 0xFF indicates that no
                                           line ID is added */
  rsuint8 CountOfEvents;                /*!< Number of event notifications in the mail */
  rsuint16 LengthOfData;                /*!< Length of notification data in bytes. */
  rsuint8 Data[1];                      /*!< Notification data. This shall be formatted
                                           as one or more ApiGenEveNotEventNotificationType
                                           or ApiGenEveNotProprietaryEventNotificationType. */
} ApiPpGenevenotEventIndType;

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
* FUNCTION:      SendApiFpGenevenotEventReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GENEVENOT_EVENT_REQ = 0x5700
****************************************************************************/
void SendApiFpGenevenotEventReq ( RosTaskIdType Src,
                                  rsbool EnableIndication,   /*!< If TRUE then an
                                                                API_GENEVENOT_EVENT_IND will
                                                                be returned through the API. */
                                  ApiGenLineIdSubType LineIdSubType,
                                                             /*!< The line identifier
                                                                subtype of the line related
                                                                to the event. */
                                  rsuint8 LineIdValue,       /*!< Range 0x00-0x7F
                                                                API_LINE_ID_INVALID = 0xFF
                                                                indicates that no line ID is
                                                                added */
                                  ApiGenAttachedHandsetsType AttachedHandsets,
                                                             /*!< The clients (PP) to be
                                                                notified of the event. */
                                  rsuint8 EventNotificationCount,
                                                             /*!< Number of event
                                                                notifications in the mail. */
                                  rsuint16 LengthOfData,     /*!< Length of notification
                                                                data in bytes. */
                                  rsuint8 Data[1]);          /*!< Notification data.
                                                                This shall be formatted as
                                                                one or more
                                                                ApiGenEveNotEventNotification
                                                                Type or
                                                                ApiGenEveNotProprietaryEventN
                                                                otificationType. */

/****************************************************************************
* FUNCTION:      SendApiFpGenevenotFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GENEVENOT_FEATURES_REQ =  0x5708
****************************************************************************/
void SendApiFpGenevenotFeaturesReq ( RosTaskIdType Src,
                                     ApiFpGenEveNotFeatureType ApiFpGenEveNotFeature);
                                                             /*!< Requested features */

/****************************************************************************
* FUNCTION:      SendApiPpGenevenotEventReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_GENEVENOT_EVENT_REQ = 0x5703
****************************************************************************/
void SendApiPpGenevenotEventReq ( RosTaskIdType Src,
                                  rsuint8 EventNotificationCount,
                                                             /*!< Number of event
                                                                notifications in the mail. */
                                  rsuint16 LengthOfData,     /*!< Length of notification
                                                                data in bytes. */
                                  rsuint8 Data[1]);          /*!< Notification data.
                                                                This shall be formatted as
                                                                one or more
                                                                ApiGenEveNotEventNotification
                                                                Type or
                                                                ApiGenEveNotProprietaryEventN
                                                                otificationType. */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIGENEVENOT_H */


