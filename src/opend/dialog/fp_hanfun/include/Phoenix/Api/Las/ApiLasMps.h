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
#ifndef APILASMPS_H
#define APILASMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Las/ApiLas.h>
//#ifdef __cplusplus
//extern "C"
//{
//#endif
#define LOG_LASMPS_MESSAGE(args...) 	printf(args)
/****************************************************************************
* FUNCTION:      SendApiLasStartSessionCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_START_SESSION_CFM = 0x5501
****************************************************************************/
void SendApiLasStartSessionCfm ( RosTaskIdType Dst,
                                 ApiLasListIdType ListIdentifier,
                                                             /*!< Id of list to start
                                                                session with */
                                 ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Allocated session id
                                                                reserved for the started
                                                                session. Will be 0 in case
                                                                of rejection. */
                                 rsuint16 NoOfEntries,       /*!< Number of entries in
                                                                list related to session. */
                                 ApiLasDiscriminatorType DiscriminatorType,
                                                             /*!<
                                                                API_LIST_DISCRIMINATOR_UNDEFI
                                                                NED or
                                                                API_LIST_DISCRIMINATOR_EMC.
                                                                If
                                                                API_LIST_DISCRIMINATOR_UNDEFI
                                                                NED the following parameter
                                                                is not used */
                                 rsuint16 Discriminator,     /*!< Not used of
                                                                DiscriminatorType is 0 */
                                 ApiLasRejectReasonType RejectReason,
                                                             /*!< Reject reason in case
                                                                of reject */
                                 rsuint16 InfoElementLength,  /*!< The length of the
                                                                 Data Information Element */
                                 rsuint8 InfoElement[1]);    /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                API_IE_LAS_SORTING_FIELD_IDEN
                                                                TIFIERS */

/****************************************************************************
* FUNCTION:      SendApiLasEndSessionCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_END_SESSION_CFM = 0x5503
****************************************************************************/
void SendApiLasEndSessionCfm ( RosTaskIdType Dst,
                               ApiLasSessionIdType SessionIdentifier);
                                                             /*!< Id of session. */

/****************************************************************************
* FUNCTION:      SendApiLasQuerySupportedEntryFieldsCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_CFM = 0x5505
****************************************************************************/
void SendApiLasQuerySupportedEntryFieldsCfm ( RosTaskIdType Dst,
                                              ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
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
* FUNCTION:      SendApiLasReadEntriesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_READ_ENTRIES_CFM = 0x5507
****************************************************************************/
void SendApiLasReadEntriesCfm ( RosTaskIdType Dst,
                                ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                                ApiLasEntryIndexType StartIndex,
                                                             /*!< Smallest index value
                                                                of list response [0x1 -
                                                                0x3FFF] */
                                rsuint8 NumberOfEntries);    /*!< Number of delivered
                                                                entries [0-0xFF] */

/****************************************************************************
* FUNCTION:      SendApiLasEditEntryCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_EDIT_ENTRY_CFM = 0x5509
****************************************************************************/
void SendApiLasEditEntryCfm ( RosTaskIdType Dst,
                              ApiLasSessionIdType SessionIdentifier);
                                                             /*!< Id of session. */

/****************************************************************************
* FUNCTION:      SendApiLasSaveEntryCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_SAVE_ENTRY_CFM = 0x550B
****************************************************************************/
void SendApiLasSaveEntryCfm ( RosTaskIdType Dst,
                              ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                              ApiLasEntryIdType EntryIdentifier,
                                                             /*!< Id of entry. */
                              ApiLasEntryIndexType PositionNumber,
                                                             /*!< Indicates the
                                                                (possible new) index number
                                                                of the entry in the list. */
                              rsuint16 NoOfEntries);         /*!< Total number of
                                                                available entries in the
                                                                list. */

/****************************************************************************
* FUNCTION:      SendApiLasDeleteEntryCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DELETE_ENTRY_CFM = 0x550D
****************************************************************************/
void SendApiLasDeleteEntryCfm ( RosTaskIdType Dst,
                                ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                                rsuint16 NumberOfEntriesLeft);
                                                             /*!< Number of entries left
                                                                in the list after deletion */

/****************************************************************************
* FUNCTION:      SendApiLasDeleteListCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DELETE_LIST_CFM = 0x550F
****************************************************************************/
void SendApiLasDeleteListCfm ( RosTaskIdType Dst,
                               ApiLasSessionIdType SessionIdentifier);
                                                             /*!< Id of session. */

/****************************************************************************
* FUNCTION:      SendApiLasSearchEntriesCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_SEARCH_ENTRIES_CFM = 0x5511
****************************************************************************/
void SendApiLasSearchEntriesCfm ( RosTaskIdType Dst,
                                  ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                                  ApiLasEntryIndexType StartIndex,
                                                             /*!< Index number of first
                                                                returned list entry. */
                                  rsuint8 NumberOfEntries);  /*!< Number of returned
                                                                entries. */

/****************************************************************************
* FUNCTION:      SendApiLasNegativeAcknowledgeInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_NEGATIVE_ACKNOWLEDGE_IND = 0x5512
****************************************************************************/
void SendApiLasNegativeAcknowledgeInd ( RosTaskIdType Dst,
                                        ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                                        ApiLasNegativeAcknowledgeReasonType RejectReason);
                                                             /*!< Reject reason */

/****************************************************************************
* FUNCTION:      SendApiLasDataPacketInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DATA_PACKET_IND = 0x5513
****************************************************************************/
void SendApiLasDataPacketInd ( RosTaskIdType Dst,
                               ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                               ApiLasEntryIdType EntryIdentifier,
                                                             /*!< Id of entry. */
                               rsbool Last,                  /*!< Indicate if packet is
                                                                the last one. */
                               rsuint16 InfoElementLength,   /*!< The length of the Data
                                                                Information Element */
                               rsuint8 InfoElement[1]);      /*!< The InfoElement can
                                                                hold a number Info Elements
                                                                placed in the format (ApiInfoElementType):
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Valid Info elements for
                                                                this command:
                                                                See section 4 for available
                                                                info elements. */

/****************************************************************************
* FUNCTION:      SendApiLasBaseResetInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_BASE_RESET_IND = 0x5580
****************************************************************************/
void SendApiLasBaseResetInd ( RosTaskIdType Dst,
                              ApiLasSessionIdType SessionIdentifier);
                                                             /*!< Id of session. */

/****************************************************************************
* FUNCTION:      SendApiLasStatusInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_STATUS_IND = 0x5581
****************************************************************************/
void SendApiLasStatusInd ( RosTaskIdType Dst,
                           ApiLasSessionIdType SessionIdentifier,
                                                             /*!< Id of session. */
                           ApiLasStatusType Status);         /*!< Status. */

/****************************************************************************
* FUNCTION:      SendApiLasGetFieldProtectionCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_GET_FIELD_PROTECTION_CFM = 0x5583
****************************************************************************/
void SendApiLasGetFieldProtectionCfm ( RosTaskIdType Dst,
                                       ApiLasListIdType ListIdentifier,
                                                             /*!< Id of list. */
                                       RsStatusType Status,  /*!< Command status, either
                                                                RSS_SUCCESS or
                                                                RSS_NOT_SUPPORTED. */
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
                                                                API_IE_LAS_DISABLED_FIELDS
                                                                API_IE_LAS_EDITABLE_FIELDS
                                                                API_IE_LAS_NON_EDITABLE_FIELDS
                                                                API_IE_LAS_PIN_PROTECTED_FIE
                                                                LDS */

/****************************************************************************
* FUNCTION:      SendApiLasSetFieldProtectionCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_SET_FIELD_PROTECTION_CFM = 0x5585
****************************************************************************/
void SendApiLasSetFieldProtectionCfm ( RosTaskIdType Dst,
                                       ApiLasListIdType ListIdentifier,
                                                             /*!< Id of list. */
                                       RsStatusType Status);  /*!< Command status,
                                                                 either RSS_SUCCESS or
                                                                 RSS_NOT_SUPPORTED. */

/****************************************************************************
* FUNCTION:      SendApiLasGetLockedEntriesListCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_GET_LOCKED_ENTRIES_LIST_CFM = 0x5587
****************************************************************************/
void SendApiLasGetLockedEntriesListCfm ( RosTaskIdType Dst,
                                         RsStatusType Status,
                                                             /*!< Command status, either
                                                                RSS_SUCCESS or
                                                                RSS_NOT_SUPPORTED. */
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
                                                                API_IE_LAS_LOCK_ENTRIES_LIST
                                                                 */

/****************************************************************************
* FUNCTION:      SendApiLasDbClearCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LAS_DB_CLEAR_CFM = 0x55C1
****************************************************************************/
void SendApiLasDbClearCfm ( RosTaskIdType Dst,
                            ApiLasSessionIdType SessionIdentifier);
                                                             /*!< Id of session. */

#ifdef __cplusplus
}
#endif
#endif /*APILASMPS_H */


