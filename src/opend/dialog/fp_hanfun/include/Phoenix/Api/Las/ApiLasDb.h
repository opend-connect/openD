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
* Definition of the ApiLasDb interface.
*/


#ifndef APILASDB_H
#define APILASDB_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */

#include <Phoenix/Api/Types/ApiTypes.h>
#include <Phoenix/Api/Las/ApiLas.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! All mails from LAS is sent to/from the API task on the FP. */
#define APILASDB_TASK API_TASK

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


/* Global mail primitives:
  API_LAS_DB_QUERY_SUPPORTED_LISTS_IND = 0x5600,
  API_LAS_DB_QUERY_SUPPORTED_LISTS_RES = 0x5601,
  API_LAS_DB_QUERY_SUPPORTED_ENTRY_FIELDS_IND = 0x5602,
  API_LAS_DB_QUERY_SUPPORTED_ENTRY_FIELDS_RES = 0x5603,
  API_LAS_DB_LIST_SORTING_REQUEST_IND = 0x5604,
  API_LAS_DB_LIST_SORTING_REQUEST_RES = 0x5605,
  API_LAS_DB_LIST_SORTING_RELEASE_IND = 0x5606,
  API_LAS_DB_LIST_SORTING_RELEASE_RES = 0x5607,
  API_LAS_DB_TOTAL_ENTRIES_IND = 0x5608,
  API_LAS_DB_TOTAL_ENTRIES_RES = 0x5609,
  API_LAS_DB_READ_IND = 0x560A,
  API_LAS_DB_READ_RES = 0x560B,
  API_LAS_DB_EDIT_IND = 0x560C,
  API_LAS_DB_EDIT_RES = 0x560D,
  API_LAS_DB_SAVE_IND = 0x560E,
  API_LAS_DB_SAVE_RES = 0x560F,
  API_LAS_DB_SEARCH_IND = 0x5610,
  API_LAS_DB_SEARCH_RES = 0x5611,
  API_LAS_DB_DELETE_IND = 0x5612,
  API_LAS_DB_DELETE_RES = 0x5613,
  API_LAS_DB_DELETE_LIST_IND = 0x5614,
  API_LAS_DB_DELETE_LIST_RES = 0x5615,
  API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ = 0x5616,
  API_LAS_DB_NEGATIVE_ACKNOWLEDGE_IND = 0x5617,
  API_LAS_DB_DATA_PACKET_IND = 0x5618,
  API_LAS_DB_DATA_PACKET_RES = 0x5619,
  API_LAS_DB_DATA_PACKET_REQ = 0x561A,
  API_LAS_DB_DATA_PACKET_CFM = 0x561B,
  API_LAS_DB_RESET_IND = 0x5630,
  API_LAS_DB_RESET_RES = 0x5631,
  API_LAS_DB_SET_ACTIVE_DB_REQ = 0x5650,
  API_LAS_DB_SET_ACTIVE_DB_CFM = 0x5651,
  API_LAS_DB_GET_ACTIVE_DB_REQ = 0x5652,
  API_LAS_DB_GET_ACTIVE_DB_CFM = 0x5653,
  API_LAS_DB_CLEAR_DB_IND = 0x56C0,
  API_LAS_DB_CLEAR_DB_RES = 0x56C1,
The global mail primitives MUST be defined in Global.h! */



typedef rsuint16 ApiLasDbTransactionIdType;

/*! This value refers to a sorting of a list specified in a
   API_LAS_DB_SORTING _LIST_RES message. */
typedef rsuint16 ApiLasDbSortIdType;    /*!< The sorting must have a value different
                                           from 0. */


typedef enum RSENUMTAG(ApiLasDbRejectReasonType)
{
  API_LAS_DB_REJECT_LIST_NOT_SUPPORTED = 0x02, /*!< List not supported */
  API_LAS_DB_REJECT_NO_ERRORS          = 0xFF  /*!< No errors */
} RSENUM8(ApiLasDbRejectReasonType);


typedef enum RSENUMTAG(ApiLasDbTotalEntriesFilterType)
{
  API_LAS_DB_FILTER_ALL_ENTRIES    = 0x0, /*!< All entries in the list should be
                                             included in the count. */
  API_LAS_DB_FILTER_UNREAD_ENTRIES = 0x1, /*!< Only entries marked as unread should be
                                             included in the count. */
  API_LAS_DB_FILTER_READ_ENTRIES   = 0x2, /*!< Only entries marked as read should be
                                             included in the count. */
} RSENUM8(ApiLasDbTotalEntriesFilterType);


typedef enum RSENUMTAG(ApiLasDbActiveDbType)
{
  API_LAS_ACTIVEDB_LOCAL = 0x0, /*!< LAS shall use its local database. */
  API_LAS_ACTIVEDB_HOST  = 0x1, /*!< LAS shall use the Host database. */
} RSENUM8(ApiLasDbActiveDbType);


typedef enum RSENUMTAG(ApiLasDbAcceptType)
{
  API_LAS_DB_ACCEPTED     = 0x0, /*!<  */
  API_LAS_DB_NOT_ACCEPTED = 0x1, /*!<  */
} RSENUM8(ApiLasDbAcceptType);

/*! This enum defines various errors codes */
typedef enum RSENUMTAG(ApiLasDbNegativeAcknowledgeReasonType)
{
  API_LAS_DB_INVALID_RANGE           = 0x00, /*!< Invalid range */
  API_LAS_DB_ENTRY_NOT_AVAILABLE     = 0x01, /*!< Entry not available */
  API_LAS_DB_INVALID_TRANSACTIONID   = 0x02, /*!<  */
  API_LAS_DB_TEMP_NOT_POSSIBLE       = 0x03, /*!< Temporarily not possible */
  API_LAS_DB_ENTRY_FORMAT_INCORRECT  = 0x04, /*!<  */
  API_LAS_DB_INVALID_START_INDEX     = 0x05, /*!<  */
  API_LAS_DB_PROCEDURE_NOT_SUPPORTED = 0x06, /*!<  */
  API_LAS_DB_PROCEDURE_NOT_ALLOWED   = 0x07, /*!<  */
  API_LAS_DB_CONTENT_NOT_ACCEPTED    = 0x08, /*!<  */
  API_LAS_DB_LIST_FULL               = 0x09, /*!<  */
  API_LAS_DB_UNEXPECTED_COMMAND      = 0x0A  /*!< Command associated with the
                                                TransactionId doesn?t match. */
} RSENUM8(ApiLasDbNegativeAcknowledgeReasonType);


/*! Mail without parameters. */
typedef struct ApilasdbEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
}PACKED_STRUCT ApilasdbEmptySignalType;

/*! This message is sent from the API to the Host in order to retrieve
   information about which lists is supported. */
typedef struct ApiLasDbQuerySupportedListsIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_QUERY_SUPPORTED_LISTS_IND = 0x5600 */
  ApiLasDbTransactionIdType TransactionId;
}PACKED_STRUCT ApiLasDbQuerySupportedListsIndType;

/*! This message is sent from the Host to the API to reply with a list of
   supported lists. */
typedef struct ApiLasDbQuerySupportedListsResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_QUERY_SUPPORTED_LISTS_RES = 0x5601 */
  ApiLasDbTransactionIdType TransactionId;
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_LIST_IDENTIFIERS */
}PACKED_STRUCT ApiLasDbQuerySupportedListsResType;

/*! This message is sent from the API to the Host in order to retrieve
   information about which entry fields a given list supports. */
typedef struct ApiLasDbQuerySupportedEntryFieldsIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_QUERY_SUPPORTED_ENTRY_FIELDS_IND = 0x5602 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;
}PACKED_STRUCT ApiLasDbQuerySupportedEntryFieldsIndType;

/*! This message is sent from the Host to the API with a list of editable
   fields and non editable fields. If the list supports more than one field of
   the same type this has to be repeated as many times as it is supported. */
typedef struct ApiLasDbQuerySupportedEntryFieldsResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_QUERY_SUPPORTED_ENTRY_FIELDS_RES = 0x5603 */
  ApiLasDbTransactionIdType TransactionId;
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_EDITABLE_FIELDS
                                           API_IE_LAS_NON_EDITABLE_FIELDS */
}PACKED_STRUCT ApiLasDbQuerySupportedEntryFieldsResType;

/*! This message is sent from the API to the Host in order to request a
   specific sorting of the entry fields in a list. */
typedef struct ApiLasDbListSortingRequestIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_LIST_SORTING_REQUEST_IND = 0x5604 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_SORTING_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasDbListSortingRequestIndType;

/*! This message is sent from the Host to the API with information of the
   actual sorting. This can either be equal to the requested sorting or
   reflect a default sorting in the data base. */
typedef struct ApiLasDbListSortingRequestResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_LIST_SORTING_REQUEST_RES = 0x5605 */
  ApiLasDbTransactionIdType TransactionId;
  rsuint16 TotalNumberOfEntries;        /*!< Number of entries currently stored in the
                                           list */
  ApiLasDbSortIdType SortId;            /*!< This Id will be used by LAS to refer to the
                                           appended sorting. */
  ApiLasDbRejectReasonType RejectReason; /*!< If the requested ListId doesn?t exist:
                                             RejectReason = 
                                             API_LAS_DB_REJECT_LIST_NOT_SUPPORTED 
                                             
                                             Otherwise:
                                             RejectReason =  
                                             API_LAS_DB_REJECT_NO_ERRORS */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_SORTING_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasDbListSortingRequestResType;

/*! This message is sent from the API to inform Host that this sorting is
   not used by LAS for the time being. The Host can chose to keep this sorting
   in order to be able to give a fast response the next time a PP requests
   this sorting, or to remove the sorting in order to free memory. */
typedef struct ApiLasDbListSortingReleaseIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_LIST_SORTING_RELEASE_IND = 0x5606 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;
  ApiLasDbSortIdType SortId;
}PACKED_STRUCT ApiLasDbListSortingReleaseIndType;

/*! This message is sent from the Host to the API. */
typedef struct ApiLasDbListSortingReleaseResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_LIST_SORTING_RELEASE_RES = 0x5607 */
  ApiLasDbTransactionIdType TransactionId;
}PACKED_STRUCT ApiLasDbListSortingReleaseResType;

/*! This message is sent from the API to the Host in order to request the
   number of actual stored entries in a list. */
typedef struct ApiLasDbTotalEntriesIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_TOTAL_ENTRIES_IND = 0x5608 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;
  ApiLasDbTotalEntriesFilterType Filter; /*!< Filter defining which entries should be
                                             counted */
}PACKED_STRUCT ApiLasDbTotalEntriesIndType;

/*! This message is sent from the Host to the API with information of the
   actual sorting this can either be equal to the requested sorting or reflect
   a default sorting in the data base. */
typedef struct ApiLasDbTotalEntriesResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_TOTAL_ENTRIES_RES = 0x5609 */
  ApiLasDbTransactionIdType TransactionId;
  rsuint16 TotalEntries;                /*!< Number of stored entries. */
}PACKED_STRUCT ApiLasDbTotalEntriesResType;

/*! This message is sent from the API to the Host and initiates the reading
   of one or more entries in a list. The wanted fields for each entry are
   specified. If a field type is stored more than once in an entry, then all
   fields of this type shall be returned.
    
    Possible error cases:
    In case the StartIndex is larger than the number of entries in the list
   the API_LAS_DB_READ_IND should be rejected with a
   API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ with RejectReason set to API_LAS_DB_INVALID_START_INDEX
    
    In case the StartIndex  + NumberOfEntries exceeds the number of entries in
   the list, only available entries should be read and the NumberOfEntries
   value in API_LAS_DB_READ_RES should indicate how many entries was read.
     */
typedef struct ApiLasDbReadIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_READ_IND = 0x560A */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;              /*!< The sorting method of the list. */
  ApiLasDbSortIdType SortId;            /*!< The sorting of the list. */
  ApiLasEntryIndexType StartIndex;      /*!< Start number [0-0x3FFF] where:
                                           0: Last entry in list
                                           0x1 - 0x3FFF: Entry number in list */
  rsuint8 NumberOfEntries;              /*!< Number of requested entries [0x1-0x7F] */
  ApiLasReadDirectionType ReadDirection; /*!< This determines if entries shall be read
                                             forward or backward from the StartIndex. */
  ApiLasReadStatusType ReadStatus;      /*!< Flag for requesting setting/resetting of
                                           the ?Read status? field for all read entrie. This
                                           field only applies to a list having a ?Read
                                           status? field, and is otherwise ignored. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasDbReadIndType;

/*! This message is sent from the Host to the API to inform how many items
   will be returned. The data itself shall be returned in one or more
   API_LAS_DB_DATA_PACKET_REQ messages. The API_LAS_DB_DATA_PACKET_REQ
   messages shall use the same TransactionId as this message. */
typedef struct ApiLasDbReadResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_READ_RES = 0x560B */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasEntryIndexType StartIndex;      /*!< Smallest index value of list response [0x1
                                           - 0x3FFF]. Also when reading backwards. */
  rsuint8 NumberOfEntries;              /*!< Number of delivered entries [0-0xFF] */
}PACKED_STRUCT ApiLasDbReadResType;

/*! This message is sent from the API to the Host and initiates the reading
   specific entry in a list. The intention is to modify the entry, and the
   Host should therefore prevent changes until the entry is stored again.
    If a field type is stored more than once in an entry, then all fields of
   this type shall be returned.
    
    Possible error cases:
    In case the EntryIdentifier doesn?t exist in the list the
   API_LAS_DB_EDIT_IND should be rejected with a
   API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ with RejectReason set to API_LAS_DB_ENTRY_NOT_AVAILABLE.
    
    In case the EntryIdentifier currently can?t be edited the
   API_LAS_DB_EDIT_IND should be rejected with a
   API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ with RejectReason set to API_LAS_DB_TEMP_NOT_POSSIBLE.
     */
typedef struct ApiLasDbEditIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_EDIT_IND = 0x560C */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;
  ApiLasDbSortIdType SortId;            /*!< The sorting of the list. */
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasDbEditIndType;

/*! This mail is used by the Host to tell the API that the entry has been
   locked and are ready for edit. 
    The content of the entry shall be transmitted in data packets with this
   TransactionId. */
typedef struct ApiLasDbEditResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_EDIT_RES = 0x560D */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
}PACKED_STRUCT ApiLasDbEditResType;

/*! This message is sent from the API to the Host and initiates the storing
   specific entry in a list.
    The content of the entry is transmitted in data packets.
    If the EntryIdentifier is different from 0 this is the result of an edit.
   In this case any stored field that is not returned shall be deleted. This
   message shall also remove the lock. */
typedef struct ApiLasDbSaveIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_SAVE_IND = 0x560E */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;
  ApiLasDbSortIdType SortId;            /*!< The sorting of the list. */
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. If the value is 0, then the
                                           entry is new and no identifier has been assigned
                                           yet. */
}PACKED_STRUCT ApiLasDbSaveIndType;

/*! This mail is used by the Host to tell the API that the entry has been
   stored. */
typedef struct ApiLasDbSaveResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_SAVE_RES = 0x560F */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
  ApiLasEntryIndexType PositionNumber;  /*!< Indicates the index number of the entry in
                                           the list. */
  rsuint16 TotalNumberOfEntries;        /*!< Number of entries currently stored in the
                                           list */
}PACKED_STRUCT ApiLasDbSaveResType;

/*! This message is sent from the API to the Host to request the search for
   one or more entries. */
typedef struct ApiLasDbSearchIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_SEARCH_IND = 0x5610 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;
  ApiLasDbSortIdType SortId;            /*!< The sorting method of the list. */
  ApiLasSearchOptionType SearchOption;  /*!< Option that should be used in search */
  ApiLasSearchCaseOptionType SearchCaseOption; /*!< Case option that should be used in
                                                   search */
  rsuint8 NumberOfEntries;              /*!< Number of requested entries [0x1 ? 0x7F] */
  ApiLasReadDirectionType ReadDirection; /*!< This determines if entries shall be read
                                             forward or backward from the matched entry. */
  ApiLasReadStatusType ReadStatus;      /*!< Flag for requesting setting/resetting of
                                           the ?Read status? field for all read entrie. This
                                           field only applies to a list having a ?Read
                                           status? field, and is otherwise ignored. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_SEARCH_TEXT
                                           API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS */
}PACKED_STRUCT ApiLasDbSearchIndType;

/*! This mail is used by the Host to tell the API if a match is found. */
typedef struct ApiLasDbSearchResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_SEARCH_RES = 0x5611 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasEntryIndexType StartIndex;      /*!< Smallest index value of list response [0x1
                                           - 0x3FFF]. Also when reading backwards. */
  rsuint8 NumberOfEntries;              /*!< Number of returned entries.
                                           If no match is found, then this shall be set to
                                           0, and no data packets shall be sent. */
}PACKED_STRUCT ApiLasDbSearchResType;

/*! This message is sent from the API to the Host to request the deletion
   of an entry.
    
    Possible error cases:
    In case the EntryIdentifier doesn?t exist in the list the
   API_LAS_DB_DELETE_IND should be rejected with a
   API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ with RejectReason set to API_LAS_DB_ENTRY_NOT_AVAILABLE.
    
    In case the EntryIdentifier is currently locked for edited the
   API_LAS_DB_DELETE_IND should be rejected with a
   API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ with RejectReason set to API_LAS_DB_TEMP_NOT_POSSIBLE.
     */
typedef struct ApiLasDbDeleteIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_DELETE_IND = 0x5612 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry.[0x1 - 0x3FFF] */
}PACKED_STRUCT ApiLasDbDeleteIndType;

/*! This mail is used by the Host to tell the API that the entry has been
   deleted. */
typedef struct ApiLasDbDeleteResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_DELETE_RES = 0x5613 */
  ApiLasDbTransactionIdType TransactionId;
  rsuint16 NumberOfEntriesLeft;         /*!< Number of entries left in the list after
                                           deletion */
}PACKED_STRUCT ApiLasDbDeleteResType;

/*! This message is sent from the API to the Host to request the deletion
   of a list.
    
    Possible error cases:
    In case the list contains entries currently locked for edited the
   API_LAS_DB_DELETE_LIST_IND should be rejected with a
   API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ with RejectReason set to API_LAS_DB_TEMP_NOT_POSSIBLE.
     */
typedef struct ApiLasDbDeleteListIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_DELETE_LIST_IND = 0x5614 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasListIdType ListId;
}PACKED_STRUCT ApiLasDbDeleteListIndType;

/*! This mail is used by the Host to tell the API that the list has been
   deleted. */
typedef struct ApiLasDbDeleteListResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_DELETE_LIST_RES = 0x5615 */
  ApiLasDbTransactionIdType TransactionId;
}PACKED_STRUCT ApiLasDbDeleteListResType;

/*! This mail is used by the Host to tell the API that the previous command
   failed. */
typedef struct ApiLasDbNegativeAcknowledgeReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ = 0x5616 */
  ApiLasDbTransactionIdType TransactionId; /*!< This is the Id of the failed command. */
  ApiLasDbNegativeAcknowledgeReasonType RejectReason; /*!< Reject reason */
}PACKED_STRUCT ApiLasDbNegativeAcknowledgeReqType;

/*! This mail is used by the API to tell the Host that the previous command
   failed. */
typedef struct ApiLasDbNegativeAcknowledgeIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_NEGATIVE_ACKNOWLEDGE_IND = 0x5617 */
  ApiLasDbTransactionIdType TransactionId; /*!< This is the Id of the failed command. */
  ApiLasDbNegativeAcknowledgeReasonType RejectReason; /*!< Reject reason */
}PACKED_STRUCT ApiLasDbNegativeAcknowledgeIndType;

/*! This mail is used by the API to send data to the Host.
    The data content can be distributed over several data packet messages. */
typedef struct ApiLasDbDataPacketIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_DATA_PACKET_IND = 0x5618 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
  rsbool Last;                          /*!< Indicate if packet is the last one. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           See section Error! Reference source not found.
                                           ?Supported list fields? in [3] for available info
                                           elements. */
}PACKED_STRUCT ApiLasDbDataPacketIndType;

/*! This mail is sent from the Host to the API to confirm that the data is
   received, and that the Host is ready to receive more data. */
typedef struct ApiLasDbDataPacketResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_DATA_PACKET_RES = 0x5619 */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
}PACKED_STRUCT ApiLasDbDataPacketResType;

/*! This mail is used by the Host to send data to the API.
    The data content can be distributed over several data packet messages.
    The message length must not exceed EAP max. packet size. */
typedef struct ApiLasDbDataPacketReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_DATA_PACKET_REQ = 0x561A */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
  rsbool Last;                          /*!< Indicate if packet is the last one. */
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           See section Error! Reference source not found.
                                           ?Supported list fields? in [3] for available info
                                           elements. */
}PACKED_STRUCT ApiLasDbDataPacketReqType;

/*! This mail is sent from the API to the Host to confirm that the data is
   received, and that the API is ready to receive more data. */
typedef struct ApiLasDbDataPacketCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_DATA_PACKET_CFM = 0x561B */
  ApiLasDbTransactionIdType TransactionId;
  ApiLasEntryIdType EntryIdentifier;    /*!< Id of entry. */
}PACKED_STRUCT ApiLasDbDataPacketCfmType;

/*! This mail is used by the API to order the Host to set the selected
   lists to their default values. */
typedef struct ApiLasDbResetIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_RESET_IND = 0x5630 */
  ApiLasDbTransactionIdType TransactionId;
  rsuint16 InfoElementLength;           /*!< The length of the Data Information Element */
  rsuint8 InfoElement[1];               /*!< The InfoElement can hold a number Info
                                           Elements placed in the format (ApiInfoElementType):
                                           
                                           { Ie, IeLength, IeData[], Ie, IeLength,
                                           IeData[], ...} 
                                           
                                           Valid Info elements for this command:
                                           API_IE_LAS_LIST_IDENTIFIERS.
                                           
                                           If this info element contains
                                           API_LAS_SUPPORTED_LISTS then all lists shall be
                                           reset. */
}PACKED_STRUCT ApiLasDbResetIndType;

/*! This mail is sent from the Host to the API to confirm that the lists
   have been reset to their default values. */
typedef struct ApiLasDbResetResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_RESET_RES = 0x5631 */
  ApiLasDbTransactionIdType TransactionId;
}PACKED_STRUCT ApiLasDbResetResType;

/*! This mail is sent from the Host to the API to request the API to use
   the specified data base. */
typedef struct ApiLasDbSetActiveDbReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_SET_ACTIVE_DB_REQ = 0x5650 */
  ApiLasDbActiveDbType ActiveDb;
}PACKED_STRUCT ApiLasDbSetActiveDbReqType;

/*! This mail is sent from the API to the Host to accept the specified data
   base. */
typedef struct ApiLasDbSetActiveDbCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_SET_ACTIVE_DB_CFM = 0x5651 */
  ApiLasDbAcceptType Accept;
}PACKED_STRUCT ApiLasDbSetActiveDbCfmType;

/*! This mail is sent from the Host to the API to request the API to send
   the id of the current active database. */
typedef struct ApiLasDbGetActiveDbReqType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_GET_ACTIVE_DB_REQ = 0x5652 */
}PACKED_STRUCT ApiLasDbGetActiveDbReqType;

/*! This mail is sent from the API to the Host to inform the Host about
   which database that is currently used. */
typedef struct ApiLasDbGetActiveDbCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_GET_ACTIVE_DB_CFM = 0x5653 */
  ApiLasDbActiveDbType ActiveDb;
}PACKED_STRUCT ApiLasDbGetActiveDbCfmType;

/*! This mail is used by the MMI to clear a specified list in FP. 
    This command can only be used with a Phoenix based FPs which support LAS
   and should only be used for debug/test purpose and not for application use. */
typedef struct ApiLasDbClearDbIndType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_CLEAR_DB_IND = 0x56C0 */
  ApiLasDbTransactionIdType TransactionId; /*!< Id of Transaction. */
  ApiLasListIdType ListIdentifier;      /*!< Id of list to clear. Any list can be
                                           cleared from any session.  
                                           If API_LAS_SUPPORTED_LISTS is selected all lists
                                           are cleared */
}PACKED_STRUCT ApiLasDbClearDbIndType;

/*! This mail is used by the API to inform the MMI that the list has been cleared.
    This command can only be used with a Phoenix based FPs which support LAS
   and should only be used for debug/test purpose and not for application use. */
typedef struct ApiLasDbClearDbResType
{
  RosPrimitiveType Primitive;            /*!< API_LAS_DB_CLEAR_DB_RES = 0x56C1 */
  ApiLasDbTransactionIdType TransactionId; /*!< Id of Transaction. */
}PACKED_STRUCT ApiLasDbClearDbResType;


#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiLasDbQuerySupportedListsRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_QUERY_SUPPORTED_LISTS_RES = 0x5601
****************************************************************************/
void SendApiLasDbQuerySupportedListsRes ( RosTaskIdType Src,
                                          ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                                          rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                          rsuint8 InfoElement[1]);
                                                             /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_LIST_IDENTIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasDbQuerySupportedEntryFieldsRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_QUERY_SUPPORTED_ENTRY_FIELDS_RES = 0x5603
****************************************************************************/
void SendApiLasDbQuerySupportedEntryFieldsRes ( RosTaskIdType Src,
                                                ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                                                rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                                rsuint8 InfoElement[1]);
                                                             /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_EDITABLE_FIELDS
                                                                API_IE_LAS_NON_EDITABLE_FIEL
                                                                DS */

/****************************************************************************
* FUNCTION:      SendApiLasDbListSortingRequestRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_LIST_SORTING_REQUEST_RES = 0x5605
****************************************************************************/
void SendApiLasDbListSortingRequestRes ( RosTaskIdType Src,
                                         ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                                         rsuint16 TotalNumberOfEntries,
                                                             /*!< Number of entries
                                                                currently stored in the list */
                                         ApiLasDbSortIdType SortId,
                                                             /*!< This Id will be used
                                                                by LAS to refer to the
                                                                appended sorting. */
                                         ApiLasDbRejectReasonType RejectReason,
                                                             /*!< If the requested
                                                                ListId doesn?t exist:
                                                                RejectReason = 
                                                                API_LAS_DB_REJECT_LIST_NOT_SU
                                                                PPORTED 
                                                                
                                                                Otherwise:
                                                                RejectReason =  
                                                                API_LAS_DB_REJECT_NO_ERRORS */
                                         rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                         rsuint8 InfoElement[1]);
                                                             /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_SORTING_FIELD_IDE
                                                                NTIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasDbListSortingReleaseRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_LIST_SORTING_RELEASE_RES = 0x5607
****************************************************************************/
void SendApiLasDbListSortingReleaseRes ( RosTaskIdType Src,
                                         ApiLasDbTransactionIdType TransactionId);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiLasDbTotalEntriesRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_TOTAL_ENTRIES_RES = 0x5609
****************************************************************************/
void SendApiLasDbTotalEntriesRes ( RosTaskIdType Src,
                                   ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                                   rsuint16 TotalEntries);   /*!< Number of stored
                                                                entries. */

/****************************************************************************
* FUNCTION:      SendApiLasDbReadRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_READ_RES = 0x560B
****************************************************************************/
void SendApiLasDbReadRes ( RosTaskIdType Src,
                           ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                           ApiLasEntryIndexType StartIndex,  /*!< Smallest index value
                                                                of list response [0x1 -
                                                                0x3FFF]. Also when reading
                                                                backwards. */
                           rsuint8 NumberOfEntries);         /*!< Number of delivered
                                                                entries [0-0xFF] */

/****************************************************************************
* FUNCTION:      SendApiLasDbEditRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_EDIT_RES = 0x560D
****************************************************************************/
void SendApiLasDbEditRes ( RosTaskIdType Src,
                           ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                           ApiLasEntryIdType EntryIdentifier);
                                                             /*!< Id of entry. */

/****************************************************************************
* FUNCTION:      SendApiLasDbSaveRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_SAVE_RES = 0x560F
****************************************************************************/
void SendApiLasDbSaveRes ( RosTaskIdType Src,
                           ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                           ApiLasEntryIdType EntryIdentifier,
                                                             /*!< Id of entry. */
                           ApiLasEntryIndexType PositionNumber,
                                                             /*!< Indicates the index
                                                                number of the entry in the
                                                                list. */
                           rsuint16 TotalNumberOfEntries);   /*!< Number of entries
                                                                currently stored in the list */

/****************************************************************************
* FUNCTION:      SendApiLasDbSearchRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_SEARCH_RES = 0x5611
****************************************************************************/
void SendApiLasDbSearchRes ( RosTaskIdType Src,
                             ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                             ApiLasEntryIndexType StartIndex,
                                                             /*!< Smallest index value
                                                                of list response [0x1 -
                                                                0x3FFF]. Also when reading
                                                                backwards. */
                             rsuint8 NumberOfEntries);       /*!< Number of returned entries.
                                                                If no match is found, then
                                                                this shall be set to 0, and
                                                                no data packets shall be
                                                                sent. */

/****************************************************************************
* FUNCTION:      SendApiLasDbDeleteRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_DELETE_RES = 0x5613
****************************************************************************/
void SendApiLasDbDeleteRes ( RosTaskIdType Src,
                             ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                             rsuint16 NumberOfEntriesLeft);  /*!< Number of entries left
                                                                in the list after deletion */

/****************************************************************************
* FUNCTION:      SendApiLasDbDeleteListRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_DELETE_LIST_RES = 0x5615
****************************************************************************/
void SendApiLasDbDeleteListRes ( RosTaskIdType Src,
                                 ApiLasDbTransactionIdType TransactionId);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiLasDbNegativeAcknowledgeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ = 0x5616
****************************************************************************/
void SendApiLasDbNegativeAcknowledgeReq ( RosTaskIdType Src,
                                          ApiLasDbTransactionIdType TransactionId,
                                                             /*!< This is the Id of the
                                                                failed command. */
                                          ApiLasDbNegativeAcknowledgeReasonType RejectReason);
                                                             /*!< Reject reason */

/****************************************************************************
* FUNCTION:      SendApiLasDbNegativeAcknowledgeInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_NEGATIVE_ACKNOWLEDGE_IND = 0x5617
****************************************************************************/
void SendApiLasDbNegativeAcknowledgeInd ( RosTaskIdType Src,
                                          ApiLasDbTransactionIdType TransactionId,
                                                             /*!< This is the Id of the
                                                                failed command. */
                                          ApiLasDbNegativeAcknowledgeReasonType RejectReason);
                                                             /*!< Reject reason */

/****************************************************************************
* FUNCTION:      SendApiLasDbDataPacketRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_DATA_PACKET_RES = 0x5619
****************************************************************************/
void SendApiLasDbDataPacketRes ( RosTaskIdType Src,
                                 ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                                 ApiLasEntryIdType EntryIdentifier);
                                                             /*!< Id of entry. */

/****************************************************************************
* FUNCTION:      SendApiLasDbDataPacketReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_DATA_PACKET_REQ = 0x561A
****************************************************************************/
void SendApiLasDbDataPacketReq ( RosTaskIdType Src,
                                 ApiLasDbTransactionIdType TransactionId,
                                                             /*!<  */
                                 ApiLasEntryIdType EntryIdentifier,
                                                             /*!< Id of entry. */
                                 rsbool Last,                /*!< Indicate if packet is
                                                                the last one. */
                                 rsuint16 InfoElementLength,  /*!< The length of the
                                                                 Data Information Element */
                                 rsuint8 InfoElement[1]);    /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                See section Error!
                                                                Reference source not found.
                                                                ?Supported list fields? in
                                                                [3] for available info
                                                                elements. */

/****************************************************************************
* FUNCTION:      SendApiLasDbResetRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_RESET_RES = 0x5631
****************************************************************************/
void SendApiLasDbResetRes ( RosTaskIdType Src,
                            ApiLasDbTransactionIdType TransactionId);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiLasDbSetActiveDbReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_SET_ACTIVE_DB_REQ = 0x5650
****************************************************************************/
void SendApiLasDbSetActiveDbReq ( RosTaskIdType Src,
                                  ApiLasDbActiveDbType ActiveDb);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiLasDbGetActiveDbReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_GET_ACTIVE_DB_REQ = 0x5652
****************************************************************************/
void SendApiLasDbGetActiveDbReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiLasDbClearDbInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_CLEAR_DB_IND = 0x56C0
****************************************************************************/
void SendApiLasDbClearDbInd ( RosTaskIdType Src,
                              ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Id of Transaction. */
                              ApiLasListIdType ListIdentifier);
                                                             /*!< Id of list to clear.
                                                                Any list can be cleared from
                                                                any session.  
                                                                If API_LAS_SUPPORTED_LISTS
                                                                is selected all lists are
                                                                cleared */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APILASDB_H */


