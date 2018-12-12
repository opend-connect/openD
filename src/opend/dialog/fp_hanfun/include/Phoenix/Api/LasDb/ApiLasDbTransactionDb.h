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

#ifndef APILASDB_TRANSACTIONDB_H
#define APILASDB_TRANSACTIONDB_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Las/ApiLas.h>
#include <Phoenix/Api/LasDb/ApiLasDb.h>
#include <NwkSwitch/Las/Common/LasTypes.h>
/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef struct ApiLasDbTransactionListType ApiLasDbTransactionListType; // this needs to be declared like this because ApiLasDbTransactionListType is used in ApiLasDbTransactionType

typedef struct ApiLasDbTransactionType
{
  ApiLasDbTransactionIdType TransactionId;       // Database transaction id
  ApiLasSessionIdType       SessionIdentifier;   // Id for session
  RosPrimitiveType          NextExpectedMessage; // Primitive of the next expected message
  void                      (*Callback)(ApiLasDbTransactionListType *ApiLasDbTransactionListItem, const RosMailType *MailPtr);
  rsuint16                  Length;              // Size of Data
  rsuint8                   *Data;               // Pointer to where Data is stored
} ApiLasDbTransactionType;


struct ApiLasDbTransactionListType
{
  RsListEntryType          ListEntry;
  ApiLasDbTransactionType  ApiLasDbTransaction;
};



/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

  /****************************************************************************
*  FUNCTION:       ApiLasDb_Init_TransactionList
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function initialize the transactionlist.
****************************************************************************/
void ApiLasDb_Init_TransactionList (void);

/****************************************************************************
*  FUNCTION:       ApiLasDb_Alloc_TransactionId
*
*  RETURNS :       A number from 0-65535.
*
*  DESCRIPTION:
****************************************************************************/
LasTransactionIdType ApiLasDb_Alloc_TransactionId(void);

/****************************************************************************
*  FUNCTION:       ApiLas_SessionDb_Add
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function adds a ApiLasSessionListItem to the queue.
****************************************************************************/
void ApiLasDb_TransactionDb_Add(ApiLasDbTransactionListType* ApiLasDbTransactionList);

/****************************************************************************
*  FUNCTION:       ApiLasDb_TransactionDb_AddTransmission
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function adds a ApiLasSessionListItem to the queue.
****************************************************************************/
LasTransactionIdType ApiLasDb_TransactionDb_AddTransmission(ApiLasSessionIdType SessionIdentifier, RosPrimitiveType NextExpectedMessage);

/****************************************************************************
*  FUNCTION:       ApiLas_SessionDb_Get
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
ApiLasDbTransactionListType* ApiLasDb_TransactionDb_Get(ApiLasDbTransactionIdType TransactionId);

/****************************************************************************
*  FUNCTION:       ApiLas_SessionDb_Delete
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function deletes the ApiLasSessionListItem in
                   the queue.
****************************************************************************/
void ApiLasDb_TransactionDb_Delete(ApiLasDbTransactionListType* ApiLasDbTransactionListItem);


/****************************************************************************
*  FUNCTION:       ApiLas_SessionDb_DeleteAll
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function deletes All the ApiLasSessionListItems in
                   the queue.
****************************************************************************/
void ApiLasDb_TransactionDb_DeleteAll(void);

#ifdef __cplusplus
}
#endif
#endif /* APILASDB_TRANSACTIONDB_H */


