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

#ifndef FPAPPLIBLASSESSIONDB_H
#define FPAPPLIBLASSESSIONDB_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Types/ApiTypes.h>
#include <Phoenix/Api/RsList.h>
#include <Phoenix/Api/Las/ApiLas.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef struct FpAppLibLasConnectionListType FpAppLibLasConnectionListType; // this needs to be declared like this because FpAppLibLasConnectionListType is used in FpAppLibLasSessionType

typedef struct FpAppLibLasSessionType
{
  // Las Session Data
  ApiLasSessionIdType SessionIdentifier;        // Id for session
  ApiLasListIdType    ListIdentifier;           // List id used in session
  rsuint16            NumberOfEntries;          // Number of entries in the list
  // State machine data
  rsuint8             State;                    // Current state
  RosPrimitiveType    NextExpectedMail;         // Id of the next expected mail
  rsuint16            LengthOfData;             // Length of data array
  rsuint8             *Data;                    // Data array
  rsbool (*CallBack)(const RosMailType* MailPtr, FpAppLibLasConnectionListType* LasConnectionListItem); // CallBack function
} PACKED_STRUCT FpAppLibLasSessionType;


struct FpAppLibLasConnectionListType
{
  RsListEntryType        ListEntry;
  FpAppLibLasSessionType LasSession;
}PACKED_STRUCT ;



/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

void FpAppLibLasSessionDbInit (void);

/****************************************************************************
*  FUNCTION:       FpAppLibLas_Add_ConnectionListItem
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function adds a SwNwkLasConnectionListItem to the queue.
****************************************************************************/
void FpAppLibLas_Add_ConnectionListItem(FpAppLibLasConnectionListType* LasConnectionListItem);


/****************************************************************************
*  FUNCTION:       FpAppLibLas_Delete_ConnectionListItem
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function deletes the SwNwkLasConnectionListItem in
                   the queue.
****************************************************************************/
void FpAppLibLas_Delete_ConnectionListItem(FpAppLibLasConnectionListType* LasConnectionListItem);


#if 0
/****************************************************************************
*  FUNCTION:       SwNwkLas_Get_ConnectionListItemEi
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
extern FpAppLibLasConnectionListType* FpAppLibLas_Get_ConnectionListItemEi(SwCallEIType Ei);





/****************************************************************************
*  FUNCTION: SwNwkLasFindDstEi
*
*  INPUTS  : DstCallerId
*  OUTPUTS :
*  RETURNS : Ei of destination - or SW_EI_NONE if no service connection is found
*
*  DESCRIPTION: Searches for service connection for DstCallerId.
****************************************************************************/
extern SwNwkLasConnectionType* SwNwkLasFindDstEi(SwCallerIdType DstCallerId);


/****************************************************************************
*  FUNCTION: SwNwkLas_Add_SessionListItem
*
*  INPUTS  :
*  OUTPUTS :
*  RETURNS :
*
*  DESCRIPTION: Adds data for a LAS session to a connection.
****************************************************************************/
extern void SwNwkLas_Add_SessionListItem(SwNwkLasConnectionListType* SwNwkLasConnectionListItem, SwNwkLasSessionListType* SwNwkLasSessionList);


/****************************************************************************
*  FUNCTION: SwNwkLas_Delete_SessionListItem
*
*  INPUTS  :
*  OUTPUTS :
*  RETURNS :
*
*  DESCRIPTION: Removes data for a LAS session from a connection.
****************************************************************************/
void FpAppLibLas_Delete_SessionListItem(FpAppLibLasSessionType* LasSession);


/****************************************************************************
*  FUNCTION:       SwNwkLas_Get_SessionListItem_ItemSortId
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
extern SwNwkLasSessionListType* SwNwkLas_Get_SessionListItem_ItemSortId(LasListIdentifierType ListIdentifier, LasListSortingIdentifierType SortId);


/****************************************************************************
*  FUNCTION:       SwNwkLas_Get_SessionListItemSessionIdentifier
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
extern SwNwkLasSessionListType* SwNwkLas_Get_SessionListItemSessionIdentifier(SwNwkLasConnectionListType* SwNwkLasConnectionListItem, LasSessionIdentifierType  SessionIdentifier);


/****************************************************************************
*  FUNCTION:       SwNwkLas_Get_SessionListItem_LockedEntryIdentifier
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
extern SwNwkLasSessionListType* SwNwkLas_Get_SessionListItem_LockedEntryIdentifier(LasListIdentifierType ListIdentifier, rsuint16 EntryIdentifier);

/****************************************************************************
*  FUNCTION:       SwNwkLas_Get_SessionListItem_AnyLockedEntryIdentifier
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
extern SwNwkLasSessionListType* SwNwkLas_Get_SessionListItem_AnyLockedEntryIdentifier(LasListIdentifierType ListIdentifier);

/****************************************************************************
*  FUNCTION:       SwNwkLas_Get_AnySessionListItem_SessionIdentifier
*
*  RETURNS :       The pointer is NULL, if SessionIdentifier is not found
*
*  DESCRIPTION:    This function search for a SessionIdentifier the connection
                   the queue.
****************************************************************************/
extern SwNwkLasSessionListType* SwNwkLas_Get_AnySessionListItem_SessionIdentifier(LasSessionIdentifierType SessionId);
#endif
/****************************************************************************
*  FUNCTION:       FpAppLibLas_Find_LasConnectionListSessionIdentifier
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
FpAppLibLasConnectionListType* FpAppLibLas_Find_LasConnectionListSessionIdentifier(ApiLasSessionIdType SessionIdentifier);

/****************************************************************************
*  FUNCTION:       FpAppLibLas_Find_LasConnectionListListIdentifier
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
FpAppLibLasConnectionListType* FpAppLibLas_Find_LasConnectionListListIdentifier(ApiLasListIdType ListIdentifier);
#ifdef __cplusplus
}
#endif
#endif // FPAPPLIBLASSESSIONDB_H


