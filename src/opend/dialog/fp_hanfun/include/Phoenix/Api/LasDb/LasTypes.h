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
#ifndef LAS_H
#define LAS_H

/****************************************************************************
*                               Include files
****************************************************************************/
//#include <NwkSwitch/ISwNwkCc.h>
//#include <NwkSwitch/Las/Common/LasProprietaryTypes.h>

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#endif

typedef enum RSENUMTAG(LasPinProtectionType)
{
  LAS_PINPROTECTION_DISABLED, //
  LAS_PINPROTECTION_ENABLED,  // Pin protected entryfields can't be modified untill pin protection has been disabled
} RSENUM8(LasPinProtectionType);

typedef enum RSENUMTAG(LasSecurityType)
{
  LAS_SECURITY_DISABLED, // All rules/restrictions specified by the CapIq specification will be disabled
  LAS_SECURITY_ENABLED,  // All rules/restrictions specified by the CapIq specification will be enabled
} RSENUM8(LasSecurityType);

/* This enum defines the different list identifier. */
typedef enum RSENUMTAG(LasListIdentifierType)
{
  LAS_SUPPORTED_LISTS         = 0x00, /* List of supported lists */
  LAS_MISSED_CALLS            = 0x01, /* List with missed calls */
  LAS_OUTGOING_CALLS          = 0x02, /* List with outgoing calls */
  LAS_INCOMING_ACCEPTED_CALLS = 0x03, /* List with incoming accepted calls */
  LAS_ALL_CALLS               = 0x04, /* List with all calls */
  LAS_CONTACTS                = 0x05, /* List with contacts */
  LAS_INTERNAL_NAMES          = 0x06, /* List with internal PP names */
  LAS_DECT_SYSTEM_SETTINGS    = 0x07, /* List with DECT system settings */
  LAS_LINE_SETTINGS           = 0x08, /* List with line settings */
  LAS_ALL_INCOMING_CALLS      = 0x09, /* List with all incoming calls(includes
                                         all missed and incoming accepted calls) */
  LAS_NUMBER_OF_LISTS,
  LAS_UNDEFINED               = 0xFF, /* Used to show that no list has been selected */
} RSENUM8(LasListIdentifierType);

/*! This enum defines */
typedef enum RSENUMTAG(LasEditableType)
{
  LAS_NON_EDITABLE = FALSE, /*!<  */
  LAS_EDITABLE     = TRUE,  /*!<  */
} RSENUM8(LasEditableType);

/*! This enum defines the different Call types. */
typedef enum RSENUMTAG(LasCallTypeType)
{
  LAS_CALLTYPE_UNDEFINED = 0x00, /*!<  */
  LAS_CALLTYPE_OUTGOING  = RSBIT3, /*!<  */
  LAS_CALLTYPE_ACCEPTED  = RSBIT4, /*!<  */
  LAS_CALLTYPE_MISSED    = RSBIT5, /*!<  */
} RSENUM8(LasCallTypeType);

/*! This enum defines the different Contact number types. */
typedef enum RSENUMTAG(LasNumberTypeType)
{
  LAS_NUMBERTYPE_UNDEFINED = 0x00, /*!<  */
  LAS_NUMBERTYPE_WORK      = RSBIT1, /*!<  */
  LAS_NUMBERTYPE_MOBILE    = RSBIT2, /*!<  */
  LAS_NUMBERTYPE_FIXED     = RSBIT3, /*!<  */
  LAS_NUMBERTYPE_OWN       = RSBIT4, /*!<  */
} RSENUM8(LasNumberTypeType);

/*! This enum defines the entity which sets date and time for the DECT
   system (PP or FP). */
typedef enum RSENUMTAG(LasClockMasterTypeType)
{
  LAS_CLOCKMASTER_FP = '0', /*!<  */
  LAS_CLOCKMASTER_PP = '1', /*!<  */
} RSENUM8(LasClockMasterTypeType);

/*! This enum defines the IP Address types */
typedef enum RSENUMTAG(LasIpAdrTypeType)
{
  LAS_IPADRTYPE_UNDEFINED = 0x00,   /*!<  */
  LAS_IPADRTYPE_STATIC    = RSBIT4, /*!<  */
  LAS_IPADRTYPE_DHCP      = RSBIT5, /*!<  */
} RSENUM8(LasIpAdrTypeType);

/*! This enum defines the Base Reset states */
typedef enum RSENUMTAG(LasBaseResetTypeType)
{
  LAS_BASERESET_NO  = '0', /*!<  */
  LAS_BASERESET_YES = '1', /*!<  */
} RSENUM8(LasBaseResetTypeType);

/*! This enum defines the Emission mode states */
typedef struct LasEmissionModeType
{
  rsbitfield NoEmissionMode  : 1;       /* 'No emission mode' status */
  rsbitfield Unused  : 7;               /* not defined yet */
} LasEmissionModeType;

/*! This enum defines the IP Address format */
typedef enum RSENUMTAG(LasIpAdrFormatType)
{
  LAS_IPADRFORMAT_IPV4      = 0x00, /*!<  */
  LAS_IPADRFORMAT_IPV6      = 0x01, /*!<  */
} RSENUM8(LasIpAdrFormatType);

/*! This enum defines the Multiple calls modes */
typedef enum RSENUMTAG(LasMultipleCallModeType)
{
  LAS_MULTIPLECALLMODE_SINGLE_CALL   = '0', /*!<  */
  LAS_MULTIPLECALLMODE_MULTIPLE_CALL = '1', /*!<  */
} RSENUM8(LasMultipleCallModeType);

/*! This enum defines the Intrusion calls modes */
typedef enum RSENUMTAG(LasIntrusionCallModeType)
{
  LAS_INTRUSIONCALL_NOT_ALLOWED = '0', /*!<  */
  LAS_INTRUSIONCALL_ALLOWED     = '1', /*!<  */
} RSENUM8(LasIntrusionCallModeType);

/*! This enum defined permanent CLIR types */
typedef enum RSENUMTAG(LasPermanentClirTypeType)
{
  LAS_PERMANENTCLIR_OFF = 0x30, /*!< CLIR de-activated for all calls */
  LAS_PERMANENTCLIR_ON  = 0x31, /*!< CLIR activated for all calls */
} RSENUM8(LasPermanentClirTypeType);

/*! This enum defined call forwarding types */
typedef enum RSENUMTAG(LasCallForwardStateType)
{
  LAS_CF_DEACTIVATE = 0x30, /*!< Call forward de-activated for all calls */
  LAS_CF_ACTIVATE   = 0x31, /*!< Call forward activated for all calls */
} RSENUM8(LasCallForwardStateType);

/*! This enum defines the allowed call interception states. */
typedef enum RSENUMTAG(LasCallInterceptionTypeType)
{
  LAS_CALLINTERCEPTION_NOT_ALLOWED = 0x30, /*!<  */
  LAS_CALLINTERCEPTION_ALLOWED     = 0x31, /*!<  */
} RSENUM8(LasCallInterceptionTypeType);


typedef enum RSENUMTAG(LasSearchOptionsType)
{
  LAS_SEARCH_EXACT_MATCH               = 0x00, /* exact match with whole target field required */
  LAS_SEARCH_BEST_MATCH_CURRENT_INDEX  = 0x01, /* exact match as with 00H option tried, current start index returned if exact match fails */
  LAS_SEARCH_BEST_MATCH_PREVIOUS_INDEX = 0x02  /* exact match as with 00H option tried, previous start index returned if exact match fails */
} RSENUM8(LasSearchOptionsType);

typedef enum RSENUMTAG(LasSearchCaseOptionsType)
{
  LAS_SEARCH_CASE_INSENSITIVE = 0x00,
  LAS_SEARCH_CASE_SENSITIVE   = 0x01
} RSENUM8(LasSearchCaseOptionsType);

typedef enum RSENUMTAG(LasRejectReasonType)
{
  LAS_REJECT_NOT_ENOUGH_RESOURCES       = 0x00, /* Not enough resources */
  LAS_REJECT_LIST_ALREADY_IN_USE        = 0x01, /* List already used by another session. */
  LAS_REJECT_LIST_NOT_SUPPORTED         = 0x02, /* List not supported */
  LAS_REJECT_MAX_NR_OF_SESSIONS_REACHED = 0x03,  /* Maximum number of sessions supported by the FP reached */
  LAS_REJECT_NO_ERRORS                  = 0xFF
} RSENUM8(LasRejectReasonType);

/* This enum defines various errors codes */
typedef enum RSENUMTAG(LasNegativeAcknowledgeReasonType)
{
  LAS_INVALID_RANGE           = 0x00, /*!< Invalid range */
  LAS_ENTRY_NOT_AVAILABLE     = 0x01, /*!< Entry not available */
  LAS_INVALID_SESSION_NO      = 0x02, /*!< Invalid session number */
  LAS_TEMP_NOT_POSSIBLE       = 0x03, /*!< Temporarily not possible */
  LAS_ENTRY_FORMAT_INCORRECT  = 0x04, /*!< Entry format incorrect */
  LAS_INVALID_START_INDEX     = 0x05, /*!< Invalid start index */
  LAS_PROCEDURE_NOT_SUPPORTED = 0x06, /*!< Procedure not supported */
  LAS_PROCEDURE_NOT_ALLOWED   = 0x07, /*!< Procedure not allowed */
  LAS_CONTENT_NOT_ACCEPTED    = 0x08, /*!< Content not accepted */
  LAS_LIST_FULL               = 0x09, /*!< List full */
  LAS_INCORRECT_PIN           = 0x0A, /*!< Incorrect PIN */
  LAS_PIN_CODE_REQUIRED       = 0x0B, /*!< PIN code required */
  LAS_NO_ERRORS               = 0xFF, /*!< No Errors */
} RSENUM8(LasNegativeAcknowledgeReasonType);

typedef enum RSENUMTAG(LasCommandType)
{
  // LAS commands
  LAS_CMD_START_SESSION_REQ          = 0x00,
  LAS_CMD_START_SESSION_CFM          = 0x01,
  LAS_CMD_END_SESSION_REQ            = 0x02,
  LAS_CMD_END_SESSION_CFM            = 0x03,
  LAS_CMD_QUERY_SUP_ENTRY_FIELDS_REQ = 0x04,
  LAS_CMD_QUERY_SUP_ENTRY_FIELDS_CFM = 0x05,
  LAS_CMD_READ_ENTRIES_REQ           = 0x06,
  LAS_CMD_READ_ENTRIES_CFM           = 0x07,
  LAS_CMD_EDIT_ENTRY_REQ             = 0x08,
  LAS_CMD_EDIT_ENTRY_CFM             = 0x09,
  LAS_CMD_SAVE_ENTRY_REQ             = 0x0A,
  LAS_CMD_SAVE_ENTRY_CFM             = 0x0B,
  LAS_CMD_DELETE_ENTRY_REQ           = 0x0C,
  LAS_CMD_DELETE_ENTRY_CFM           = 0x0D,
  LAS_CMD_DELETE_LIST_REQ            = 0x0E,
  LAS_CMD_DELETE_LIST_CFM            = 0x0F,
  LAS_CMD_SEARCH_ENTRIES_REQ         = 0x10,
  LAS_CMD_SEARCH_ENTRIES_CFM         = 0x11,
  LAS_CMD_NEGATIVE_ACK_IND           = 0x12,
  LAS_CMD_DATA_PACKET                = 0x13,
  LAS_CMD_DATA_PACKET_LAST           = 0x14,

  // LAS Propietary commands (Should be placed from 0x80 and up)
  LAS_CMD_BASE_RESET_IND             = 0x80,

  // LAS Propietary debug commands (Should be placed from 0xC0 and up)
  LAS_CMD_DB_CLEAR_REQ               = 0xC0,
  LAS_CMD_DB_CLEAR_CFM               = 0xC1,

  LAS_CMD_UNDEFINED                  = 0xFF
} RSENUM8(LasCommandType);

/***********************************************************************
 Field identifiers for each list
***********************************************************************/
#define LAS_FIELDID_UNDEFINED 0xFF

/* This enum defines valid fields in list of supported lists */
typedef enum RSENUMTAG(LasFldIdSupportedListType)
{
  LAS_FIELDID_SUPPORTEDLISTS_LIST_IDENTIFIER = 0x01, /* Identifiers of all supported lists */
} RSENUM8(LasFldIdSupportedListType);

/* This enum defined valid fields in missed calls lists */
typedef enum RSENUMTAG(LasFldIdMissedCallType)
{
  LAS_FIELDID_MISSEDCALLS_NUMBER          = 0x01, /* Number of calling party */
  LAS_FIELDID_MISSEDCALLS_NAME            = 0x02, /* Name of calling party */
  LAS_FIELDID_MISSEDCALLS_DATE_TIME       = 0x03, /* Date & time of calling party */
  LAS_FIELDID_MISSEDCALLS_READSTATUS      = 0x04, /* Showed first time */
  LAS_FIELDID_MISSEDCALLS_LINE_NAME       = 0x05, /* Line name of calling party */
  LAS_FIELDID_MISSEDCALLS_LINE_ID         = 0x06, /* Line id of calling party */
  LAS_FIELDID_MISSEDCALLS_NUMBER_OF_CALLS = 0x07, /* Number of missed calls from this calling
                                               party */
} RSENUM8(LasFldIdMissedCallType);

/* This enum defined valid fields in outgoing calls lists */
typedef enum RSENUMTAG(LasFldIdOutgoingCallType)
{
  LAS_FIELDID_OUTGOINGCALLS_NUMBER    = 0x01, /* Number of called party */
  LAS_FIELDID_OUTGOINGCALLS_NAME      = 0x02, /* Name of called party */
  LAS_FIELDID_OUTGOINGCALLS_DATE_TIME = 0x03, /* Date & time of called party */
  LAS_FIELDID_OUTGOINGCALLS_LINE_NAME = 0x04, /* Line name used for call */
  LAS_FIELDID_OUTGOINGCALLS_LINE_ID   = 0x05, /* Line id used for call */
} RSENUM8(LasFldIdOutgoingCallType);

/* This enum defined valid fields in incoming accepted calls lists */
typedef enum RSENUMTAG(LasFldIdAcceptedCallType)
{
  LAS_FIELDID_INCOMINGCALLS_NUMBER    = 0x01, /* Number of calling party */
  LAS_FIELDID_INCOMINGCALLS_NAME      = 0x02, /* Name of calling party */
  LAS_FIELDID_INCOMINGCALLS_DATE_TIME = 0x03, /* Date & time of calling party */
  LAS_FIELDID_INCOMINGCALLS_LINE_NAME = 0x04, /* Line name used for call */
  LAS_FIELDID_INCOMINGCALLS_LINE_ID   = 0x05, /* Line id used for call */
} RSENUM8(LasFldIdAcceptedCallType);

/* This enum defined valid fields in all calls lists */
typedef enum RSENUMTAG(LasFldIdAllCallType)
{
  LAS_FIELDID_ALLCALLS_CALL_TYPE = 0x01, /* Coding of the list:
                                             missed/accepted/outgoing */
  LAS_FIELDID_ALLCALLS_NUMBER    = 0x02, /* Number of called/calling party */
  LAS_FIELDID_ALLCALLS_NAME      = 0x03, /* Name of called/calling party */
  LAS_FIELDID_ALLCALLS_DATE_TIME = 0x04, /* Date & time the missed call */
  LAS_FIELDID_ALLCALLS_LINE_NAME = 0x05, /* Line name used for call */
  LAS_FIELDID_ALLCALLS_LINE_ID   = 0x06, /* Line id used for call */
} RSENUM8(LasFldIdAllCallType);

/* This enum defined valid fields in All incoming calls lists */
typedef enum RSENUMTAG(LasFldIdAllIncomingCallType)
{
  LAS_FIELDID_ALLINCOMINGCALLS_NUMBER          = 0x01, /* Number of calling party */
  LAS_FIELDID_ALLINCOMINGCALLS_NAME            = 0x02, /* Name of calling party */
  LAS_FIELDID_ALLINCOMINGCALLS_DATE_TIME       = 0x03, /* Date & time of calling party */
  LAS_FIELDID_ALLINCOMINGCALLS_READSTATUS      = 0x04, /* Showed first time */
  LAS_FIELDID_ALLINCOMINGCALLS_LINE_NAME       = 0x05, /* Line name of calling party */
  LAS_FIELDID_ALLINCOMINGCALLS_LINE_ID         = 0x06, /* Line id of calling party */
  LAS_FIELDID_ALLINCOMINGCALLS_NUMBER_OF_CALLS = 0x07, /* Number of missed calls from this calling
                                               party */
} RSENUM8(LasFldIdAllIncomingCallType);

/* This enum defined valid fields in contact lists */
typedef enum RSENUMTAG(LasFldIdContactType)
{
  LAS_FIELDID_CONTACT_NAME       = 0x01, /* Name of the contactg (last name) */
  LAS_FIELDID_CONTACT_FIRST_NAME = 0x02, /* First name of contact */
  LAS_FIELDID_CONTACT_NUMBER     = 0x03, /* Number of the contact */
  LAS_FIELDID_CONTACT_ASS_MELODY = 0x04, /* Associated ringing melody */
  LAS_FIELDID_CONTACT_LINE_ID    = 0x05, /* Line id used for the call */
} RSENUM8(LasFldIdContactType);

/* This enum defined valid fields in internal names lists */
typedef enum RSENUMTAG(LasFldIdInternalNamesType)
{
  LAS_FIELDID_INTERNAL_NUMBER           = 0x01, /* Terminal identity number */
  LAS_FIELDID_INTERNAL_NAME             = 0x02, /* Name of the internal party */
  LAS_FIELDID_INTERNAL_CALLINTERCEPTION = 0x03, /* Setting indicating if Call Interception is allowed */
} RSENUM8(LasFldIdInternalNamesType);

/* This enum defined valid fields in DECT system settings lists */
typedef enum RSENUMTAG(LasFldIdDectSettingsType)
{
  LAS_FIELDID_SYSTEMSETTINGS_CURRENT_PINCODE = 0x01, /* PIN code used for validation of current pincode*/
  LAS_FIELDID_SYSTEMSETTINGS_CLOCKMASTER     = 0x02, /* Entity which sets date and time for DECT system (PP or FP) */
  LAS_FIELDID_SYSTEMSETTINGS_BASERESET       = 0x03, /* Reset to default factory settings */
  LAS_FIELDID_SYSTEMSETTINGS_IPTYPE          = 0x04, /* DHCP or static (default: manufacturer) */
  LAS_FIELDID_SYSTEMSETTINGS_IPVALUE         = 0x05, /* Editable for static IP */
  LAS_FIELDID_SYSTEMSETTINGS_IPSUBNET        = 0x06, /* Editable for static IP */
  LAS_FIELDID_SYSTEMSETTINGS_IPGATEWAY       = 0x07, /* Only for static IP */
  LAS_FIELDID_SYSTEMSETTINGS_IPDNS           = 0x08, /* Only for static IP */
  LAS_FIELDID_SYSTEMSETTINGS_FIRMWAREVERSION = 0x09, /* Software version on the FP */
  LAS_FIELDID_SYSTEMSETTINGS_EEPROMVERSION   = 0x0A, /* EEPROM version on FP */
  LAS_FIELDID_SYSTEMSETTINGS_HARDWAREVERSION = 0x0B, /* Hardware version on FP */
  LAS_FIELDID_SYSTEMSETTINGS_EMISSIONMODE    = 0x0C, /* Emission mode */
  LAS_FIELDID_SYSTEMSETTINGS_NEW_PINCODE     = 0x0D, /* PIN code used when current pin code should be modified*/
  // Proprietary fields
  LAS_FIELDID_SYSTEMSETTINGS_P_BASENAME      = 0x81, /* FP Name */
  LAS_FIELDID_SYSTEMSETTINGS_P_COUNTRYCODE   = 0x82, /* FP country selection */
  LAS_FIELDID_SYSTEMSETTINGS_P_IPMAC         = 0x83, /* FP IP mac address */
  LAS_FIELDID_SYSTEMSETTINGS_P_DECT_MODE     = 0x84, /* FP dect mode */
} RSENUM8(LasFldIdDectSettingsType);

/* This enum defined valid fields in DECT system settings lists */
typedef enum RSENUMTAG(LasFldIdLineSettingsType)
{
  LAS_FIELDID_LINESETTINGS_LINE_NAME            = 0x01, /* Name of line */
  LAS_FIELDID_LINESETTINGS_LINE_ID              = 0x02, /* Line identifier */
  LAS_FIELDID_LINESETTINGS_ATTACHED_HANDSETS    = 0x03, /* List of handsets attached to line */
  LAS_FIELDID_LINESETTINGS_DIALING_PREFIX       = 0x04, /* Prefix for called party numbers if defined */
  LAS_FIELDID_LINESETTINGS_FP_MELODY            = 0x05, /* Melody on FP linked to this line. */
  LAS_FIELDID_LINESETTINGS_FP_VOLUME            = 0x06, /* Melody volume on FP linked to this line. */
  LAS_FIELDID_LINESETTINGS_BLOCKED_PHONE_NUMBER = 0x07, /* Forbidden called party numbers on the line */
  LAS_FIELDID_LINESETTINGS_MULTIPLE_CALLS_MODE  = 0x08, /* Current mode of line: single call or multiple call */
  LAS_FIELDID_LINESETTINGS_INTRUSION_CALL       = 0x09, /* Intrusion call: yes/no */
  LAS_FIELDID_LINESETTINGS_PERMANENT_CLIR       = 0x0A, /* Restrict number for all outgoing calls on this line */
  LAS_FIELDID_LINESETTINGS_CALL_FORWARDING_CFU  = 0x0B, /* Stores the type and number of the call forwarding unconditional */
  LAS_FIELDID_LINESETTINGS_CALL_FORWARDING_CFNA = 0x0C, /* Stores the type and number of the call forwarding on no answer */
  LAS_FIELDID_LINESETTINGS_CALL_FORWARDING_CFB  = 0x0D, /* Stores the type and number of the call forwarding on busy */
} RSENUM8(LasFldIdLineSettingsType);


typedef enum RSENUMTAG(LasCallLogTypeType)
{
  LAS_CALLLOG_CALLTYPE_UNDEFINED     = 0x00,
  LAS_CALLLOG_CALLTYPE_MISSED_CALL   = 0x01,
  LAS_CALLLOG_CALLTYPE_INCOMING_CALL = 0x02,
  LAS_CALLLOG_CALLTYPE_OUTGOING_CALL = 0x03
} RSENUM8(LasCallLogTypeType);


typedef rsuint16 LasTransactionIdType;
typedef rsuint16 LasListSortingIdentifierType;

typedef rsuint16 LasSessionIdentifierType;
typedef rsuint16 LasEntryIdentifierType;
typedef rsuint16 LasEntryIndexType;
typedef rsuint8  LasFieldIdentifierType;

/***********************************************************************
 Las field types
***********************************************************************/
typedef rsuint8 LasContactNumberAttributesInfoType;

typedef struct LasContactNumberAttributesType
{
  rsbitfield Own  : 1;                  /*!< Own property is used to identify in the
                                           contact list, contact numbers belonging to the
                                           user of the system */
  rsbitfield Fixed  : 1;                /*!< Indicates that the number is a ?Fixed?
                                           number. */
  rsbitfield Mobile  : 1;               /*!< Indicates that the number is a ?Mobile?
                                           number. */
  rsbitfield Work  : 1;                 /*!< Indicates that the number is a ?Work?
                                           number. */
  rsbitfield Unused  : 4;               /*!< not defined yet */
} LasContactNumberAttributesType;


typedef union
{
  LasContactNumberAttributesType     b;
  LasContactNumberAttributesInfoType c;
} LasContactAttribUnionType;


typedef struct LasContactNumberItemType
{
  LasContactAttribUnionType  Attributes; /*!< Number attributes. */
  rsuint8  LengthOfNumber;              /*!< Length of Number in bytes. */
  rsuint8  Number[1];                   /*!< First digit in array */
} LasContactNumberItemType;


/***********************************************************************
 Las command types
***********************************************************************/
/* This type is common for all las req and cfm messages, except for LasStartSessionReqType !*/
typedef struct LasCommonCmdType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  rsuint8                  Data[1];
}LasCommonCmdType;

typedef struct LasStartSessionReqType1
{
  LasCommandType        LasCommand;
  LasListIdentifierType ListIdentifier;
  rsuint8               NumberOfSortingFields;
  rsuint8               SortingFields[1];
}LasStartSessionReqType1;

typedef struct LasStartSessionReqType
{
  LasCommandType          LasCommand;
  LasListIdentifierType   ListIdentifier;
  rsuint8                 NumberOfSortingFields;
  LasFieldIdentifierType *SortingFields;
}LasStartSessionReqType;
//
//GZ
typedef enum RSENUMTAG(SwDiscriminatorType)
{
  SW_DT_UNSPECIFIED = 0x0, /*!<  */
  SW_DT_EMC         = 0x1, /*!<  */
} RSENUM8(SwDiscriminatorType);

typedef struct LasStartSessionCfmType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasListIdentifierType    ListIdentifier;
  rsuint16                 TotalNumberOfEntries;
  SwDiscriminatorType      Discriminator;
  rsuint16                 EmcCode;                    /* EMC. Used when Discriminator is set to EMC. */
  LasRejectReasonType      RejectReason;
  rsuint8                  NumberOfSortingFields;
  LasFieldIdentifierType   *SortingFields;
}LasStartSessionCfmType;

typedef struct LasEndSessionReqType
{
  LasCommandType            LasCommand;
  LasSessionIdentifierType  SessionIdentifier;
}LasEndSessionReqType;

typedef struct LasEndSessionCfmType
{
  LasCommandType            LasCommand;
  LasSessionIdentifierType  SessionIdentifier;
}LasEndSessionCfmType;

typedef struct LasQuerySupEntryFieldsReqType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
}LasQuerySupEntryFieldsReqType;

typedef struct LasQuerySupEntryFieldsCfmType
{
  LasCommandType            LasCommand;
  LasSessionIdentifierType  SessionIdentifier;
  rsuint8                   NumberOfEditableFields;
  LasFieldIdentifierType   *EditableFields;
  rsuint8                   NumberOfNonEditableFields;
  LasFieldIdentifierType   *NonEditableFields;
}LasQuerySupEntryFieldsCfmType;

typedef enum RSENUMTAG(LasReadDirectionType)
{
  LAS_READDIRECTION_FORWARD  = 0x00, /* Forward (in ascending list index order) */
  LAS_READDIRECTION_BACKWARD = 0x01  /* Backward (in descending list index order) */
} RSENUM8(LasReadDirectionType);

/*! Enum definition for LasReadStatusType */
typedef enum RSENUMTAG(LasReadStatusType)
{
  LAS_READSTATUS_UNCHANGED = 0x00, /*!< All read entries ?Read status? field shall
                                        be left unchanged */
  LAS_READSTATUS_READ      = 0x7F, /*!< All read entries ?Read status? field shall
                                        be reset (i.e. marked as read) */
  LAS_READSTATUS_UNREAD    = 0xFF, /*!< All read entries ?Read status? field shall
                                        be set (i.e. marked as unread) */
} RSENUM8(LasReadStatusType);


typedef struct LasReadEntriesReqType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasEntryIndexType        StartIndex;
  LasReadDirectionType     ReadDirection;               // Not part of the LAS AIR interface
  LasReadStatusType        ReadStatus;
  rsuint8                  NumberOfEntries;
  rsuint8                  NumberOfFieldIdentifiers; // Not part of the LAS AIR interface
  LasFieldIdentifierType   *FieldIdentifier;
}LasReadEntriesReqType;

typedef struct LasReadEntriesCfmType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasEntryIndexType        StartIndex;
  rsuint8                  NumberOfEntries;
}LasReadEntriesCfmType;

typedef struct LasEditEntryReqType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  rsuint16                 EntryIdentifier;
  rsuint8                  NumberOfFieldIdentifiers; // Not part of the LAS AIR interface
  LasFieldIdentifierType   *FieldIdentifier;
}LasEditEntryReqType;

typedef struct LasEditEntryCfmType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
}LasEditEntryCfmType;

typedef struct LasSaveEntryReqType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasEntryIdentifierType   EntryIdentifier;
}LasSaveEntryReqType;

typedef struct LasSaveEntryCfmType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasEntryIdentifierType   EntryIdentifier;
  LasEntryIndexType        PositionIndex;
  rsuint16                 NumberOfEntries;
}LasSaveEntryCfmType;

typedef struct LasDeleteEntryReqType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasEntryIdentifierType   EntryIdentifier;
}LasDeleteEntryReqType;

typedef struct LasDeleteEntryCfmType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  rsuint16                 NumberOfEntriesLeft;
}LasDeleteEntryCfmType;

typedef struct LasDeleteListReqType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
}LasDeleteListReqType;

typedef struct LasDeleteListCfmType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
}LasDeleteListCfmType;

typedef struct LasSearchEntriesReqType
{
  LasCommandType            LasCommand;
  LasSessionIdentifierType  SessionIdentifier;
  LasSearchOptionsType      SearchOption;        // Not part of the LAS AIR interface
  LasSearchCaseOptionsType  SearchCaseOption;    // SearchOption and SearchCaseOption are collected as one value in the LAS Air format
  rsuint8                   LengthOfSearchValue;
  rsuint8                   *SearchValue;
  rsuint8                   NumberOfEntries;
  LasReadDirectionType      ReadDirection;                // Not part of the LAS AIR interface
  LasReadStatusType         ReadStatus;
  rsuint8                   NumberOfFieldIdentifiers; // Not part of the LAS AIR interface
  LasFieldIdentifierType    *FieldIdentifier;
}LasSearchEntriesReqType;

typedef struct LasSearchEntriesCfmType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasEntryIndexType        StartIndex;
  rsuint8                  NumberOfEntries;
}LasSearchEntriesCfmType;

typedef struct LasNegativeAckIndType
{
  LasCommandType                   LasCommand;
  LasSessionIdentifierType         SessionIdentifier;
  LasNegativeAcknowledgeReasonType RejectReason;
}LasNegativeAckIndType;

typedef struct LasDataPacketType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  rsuint16                 LengthOfContent; // Not part of the LAS AIR interface
  rsuint8                  *Content;
}LasDataPacketType;


typedef struct LasDataPacketEntryType
{
  LasEntryIdentifierType EntryIdentifier;
  rsuint16               EntryLength;
  rsuint8                *EntryData;
}LasDataPacketEntryType;


typedef struct LasDataPacketFieldType
{
  LasFieldIdentifierType FieldIdentifier;
  rsuint16               FieldLength; // NB. FieldOptions is included in this length !
  rsuint16               FieldOptions;
  rsuint8                *FieldData;
}LasDataPacketFieldType;


/***********************************************************************
 Las Proprietary command types
***********************************************************************/
typedef struct LasBaseResetIndType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
}LasBaseResetIndType;

typedef struct LasDbClearReqType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasListIdentifierType    ListIdentifier;
}LasDbClearReqType;

typedef struct LasDbClearCfmType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
}LasDbClearCfmType;


typedef struct LasDbInfoReqType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasListIdentifierType    ListIdentifier;
}LasDbInfoReqType;

typedef struct LasDbInfoCfmType
{
  LasCommandType           LasCommand;
  LasSessionIdentifierType SessionIdentifier;
  LasListIdentifierType    ListIdentifier;
  rsuint16                 CurrentNumberOfEntries;
  rsuint16                 MaxNumberOfEntries;
}LasDbInfoCfmType;



#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPopPack.h>
#endif

#endif

