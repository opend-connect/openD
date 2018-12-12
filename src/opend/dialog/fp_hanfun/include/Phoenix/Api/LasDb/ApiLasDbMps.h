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
#ifndef APILASDBMPS_H
#define APILASDBMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/LasDb/ApiLasDb.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiLasDbQuerySupportedListsInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_QUERY_SUPPORTED_LISTS_IND = 0x5600
****************************************************************************/
void SendApiLasDbQuerySupportedListsInd ( RosTaskIdType Dst,
                                          ApiLasDbTransactionIdType TransactionId);
                                                             /*!< Transaction ID. */

/****************************************************************************
* FUNCTION:      SendApiLasDbQuerySupportedEntryFieldsInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_QUERY_SUPPORTED_ENTRY_FIELDS_IND = 0x5602
****************************************************************************/
void SendApiLasDbQuerySupportedEntryFieldsInd ( RosTaskIdType Dst,
                                                ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                                                ApiLasListIdType ListId);
                                                             /*!< List ID. */

/****************************************************************************
* FUNCTION:      SendApiLasDbListSortingRequestInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_LIST_SORTING_REQUEST_IND = 0x5604
****************************************************************************/
void SendApiLasDbListSortingRequestInd ( RosTaskIdType Dst,
                                         ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                                         ApiLasListIdType ListId,
                                                             /*!< List ID. */
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
* FUNCTION:      SendApiLasDbListSortingReleaseInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_LIST_SORTING_RELEASE_IND = 0x5606
****************************************************************************/
void SendApiLasDbListSortingReleaseInd ( RosTaskIdType Dst,
                                         ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                                         ApiLasListIdType ListId,
                                                             /*!< List ID. */
                                         ApiLasDbSortIdType SortId);
                                                             /*!< Sort ID. */

/****************************************************************************
* FUNCTION:      SendApiLasDbTotalEntriesInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_TOTAL_ENTRIES_IND = 0x5608
****************************************************************************/
void SendApiLasDbTotalEntriesInd ( RosTaskIdType Dst,
                                   ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                                   ApiLasListIdType ListId,  /*!< List ID. */
                                   ApiLasDbTotalEntriesFilterType Filter);
                                                             /*!< Filter defining which
                                                                entries should be counted */

/****************************************************************************
* FUNCTION:      SendApiLasDbReadInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_READ_IND = 0x560A
****************************************************************************/
void SendApiLasDbReadInd ( RosTaskIdType Dst,
                           ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                           ApiLasListIdType ListId,          /*!< The sorting method of
                                                                the list. */
                           ApiLasDbSortIdType SortId,        /*!< The sorting of the
                                                                list. */
                           ApiLasEntryIndexType StartIndex,  /*!< Start number
                                                                [0-0x3FFF] where:
                                                                0: Last entry in list
                                                                0x1 - 0x3FFF: Entry number
                                                                in list */
                           rsuint8 NumberOfEntries,          /*!< Number of requested
                                                                entries [0x1-0x7F] */
                           ApiLasReadDirectionType ReadDirection,
                                                             /*!< This determines if
                                                                entries shall be read
                                                                forward or backward from the
                                                                StartIndex. */
                           ApiLasReadStatusType ReadStatus,  /*!< Flag for requesting
                                                                setting/resetting of the
                                                                ?Read status? field for all
                                                                read entrie. This field only
                                                                applies to a list having a
                                                                ?Read status? field, and is
                                                                otherwise ignored. */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_REQUESTED_FIELD_I
                                                                DENTIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasDbEditInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_EDIT_IND = 0x560C
****************************************************************************/
void SendApiLasDbEditInd ( RosTaskIdType Dst,
                           ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                           ApiLasListIdType ListId,          /*!< List ID. */
                           ApiLasDbSortIdType SortId,        /*!< The sorting of the
                                                                list. */
                           ApiLasEntryIdType EntryIdentifier,
                                                             /*!< Id of entry. */
                           rsuint16 InfoElementLength,       /*!< The length of the Data
                                                                Information Element */
                           rsuint8 InfoElement[1]);          /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_REQUESTED_FIELD_I
                                                                DENTIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasDbSaveInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_SAVE_IND = 0x560E
****************************************************************************/
void SendApiLasDbSaveInd ( RosTaskIdType Dst,
                           ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                           ApiLasListIdType ListId,          /*!< List ID. */
                           ApiLasDbSortIdType SortId,        /*!< The sorting of the
                                                                list. */
                           ApiLasEntryIdType EntryIdentifier);
                                                             /*!< Id of entry. If the
                                                                value is 0, then the entry
                                                                is new and no identifier has
                                                                been assigned yet. */

/****************************************************************************
* FUNCTION:      SendApiLasDbSearchInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_SEARCH_IND = 0x5610
****************************************************************************/
void SendApiLasDbSearchInd ( RosTaskIdType Dst,
                             ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                             ApiLasListIdType ListId,        /*!< List ID. */
                             ApiLasDbSortIdType SortId,      /*!< The sorting method of
                                                                the list. */
                             ApiLasSearchOptionType SearchOption,
                                                             /*!< Option that should be
                                                                used in search */
                             ApiLasSearchCaseOptionType SearchCaseOption,
                                                             /*!< Case option that
                                                                should be used in search */
                             rsuint8 NumberOfEntries,        /*!< Number of requested
                                                                entries [0x1 ? 0x7F] */
                             ApiLasReadDirectionType ReadDirection,
                                                             /*!< This determines if
                                                                entries shall be read
                                                                forward or backward from the
                                                                matched entry. */
                             ApiLasReadStatusType ReadStatus,
                                                             /*!< Flag for requesting
                                                                setting/resetting of the
                                                                ?Read status? field for all
                                                                read entrie. This field only
                                                                applies to a list having a
                                                                ?Read status? field, and is
                                                                otherwise ignored. */
                             rsuint16 InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                             rsuint8 InfoElement[1]);        /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_SEARCH_TEXT
                                                                API_IE_LAS_REQUESTED_FIELD_I
                                                                DENTIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasDbDeleteInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_DELETE_IND = 0x5612
****************************************************************************/
void SendApiLasDbDeleteInd ( RosTaskIdType Dst,
                             ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                             ApiLasListIdType ListId,        /*!< List ID. */
                             ApiLasEntryIdType EntryIdentifier);
                                                             /*!< Id of entry.[0x1 -
                                                                0x3FFF] */

/****************************************************************************
* FUNCTION:      SendApiLasDbDeleteListInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_DELETE_LIST_IND = 0x5614
****************************************************************************/
void SendApiLasDbDeleteListInd ( RosTaskIdType Dst,
                                 ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                                 ApiLasListIdType ListId);   /*!< List ID. */

/****************************************************************************
* FUNCTION:      SendApiLasDbDataPacketInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_DATA_PACKET_IND = 0x5618
****************************************************************************/
void SendApiLasDbDataPacketInd ( RosTaskIdType Dst,
                                 ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
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
* FUNCTION:      SendApiLasDbDataPacketCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_DATA_PACKET_CFM = 0x561B
****************************************************************************/
void SendApiLasDbDataPacketCfm ( RosTaskIdType Dst,
                                 ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                                 ApiLasEntryIdType EntryIdentifier);
                                                             /*!< Id of entry. */

/****************************************************************************
* FUNCTION:      SendApiLasDbResetInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_RESET_IND = 0x5630
****************************************************************************/
void SendApiLasDbResetInd ( RosTaskIdType Dst,
                            ApiLasDbTransactionIdType TransactionId,
                                                             /*!< Transaction ID. */
                            rsuint16 InfoElementLength,      /*!< The length of the Data
                                                                Information Element */
                            rsuint8 InfoElement[1]);         /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_LIST_IDENTIFIERS.
                                                                
                                                                If this info element
                                                                contains
                                                                API_LAS_SUPPORTED_LISTS then
                                                                all lists shall be reset. */

/****************************************************************************
* FUNCTION:      SendApiLasDbSetActiveDbCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_SET_ACTIVE_DB_CFM = 0x5651
****************************************************************************/
void SendApiLasDbSetActiveDbCfm ( RosTaskIdType Dst,
                                  ApiLasDbAcceptType Accept);
                                                             /*!< Transaction ID. */

/****************************************************************************
* FUNCTION:      SendApiLasDbGetActiveDbCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_GET_ACTIVE_DB_CFM = 0x5653
****************************************************************************/
void SendApiLasDbGetActiveDbCfm ( RosTaskIdType Dst,
                                  ApiLasDbActiveDbType ActiveDb);
                                                             /*!< Transaction ID. */

/****************************************************************************
* FUNCTION:      SendApiLasDbClearDbRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_CLEAR_DB_RES = 0x56C1
****************************************************************************/
void SendApiLasDbClearDbRes ( RosTaskIdType Dst,
                              ApiLasDbTransactionIdType TransactionId);
                                                             /*!< Id of Transaction. */

#ifdef __cplusplus
}
#endif
#endif /*APILASDBMPS_H */


