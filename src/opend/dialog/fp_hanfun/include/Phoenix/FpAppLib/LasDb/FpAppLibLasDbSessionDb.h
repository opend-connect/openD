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

#ifndef FpAppLibLasDbSESSIONDB_H
#define FpAppLibLasDbSESSIONDB_H

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
typedef struct FpAppLibLasDbConnectionListType FpAppLibLasDbConnectionListType; // this needs to be declared like this because FpAppLibLasDbConnectionListType is used in FpAppLibLasSessionType

typedef struct FpAppLibLasDbSessionType
{
  // Las Session Data
  ApiLasSessionIdType SessionIdentifier;        // Id for session
  ApiLasListIdType    ListIdentifier;           // List id used in session
  rsuint16            NumberOfEntries;          // Number of entries in the list
  // State machine data
  rsuint16             State;                    // Current state
  RosPrimitiveType    NextExpectedMail;         // Id of the next expected mail
  ApiLasDbSortIdType	SortId;
  rsuint16            LengthOfData;             // Length of data array
  rsuint8             *Data;                    // Data array
  rsbool (*CallBack)(const RosMailType* MailPtr, FpAppLibLasDbConnectionListType* LasConnectionListItem); // CallBack function
} PACKED_STRUCT FpAppLibLasDbSessionType;


struct FpAppLibLasDbConnectionListType
{
  RsListEntryType        ListEntry;
  FpAppLibLasDbSessionType LasSession;
}PACKED_STRUCT ;



/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

void FpAppLibLasDbSessionDbInit (void);

/****************************************************************************
*  FUNCTION:       FpAppLibLasDb_Add_ConnectionListItem
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function adds a SwNwkLasConnectionListItem to the queue.
****************************************************************************/
void FpAppLibLasDb_Add_ConnectionListItem(FpAppLibLasDbConnectionListType* LasConnectionListItem);


/****************************************************************************
*  FUNCTION:       FpAppLibLasDb_Delete_ConnectionListItem
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function deletes the SwNwkLasConnectionListItem in
                   the queue.
****************************************************************************/
void FpAppLibLasDb_Delete_ConnectionListItem(FpAppLibLasDbConnectionListType* LasConnectionListItem);



/****************************************************************************
*  FUNCTION:       FpAppLibLasDb_Find_LasConnectionListSessionIdentifier
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
FpAppLibLasDbConnectionListType* FpAppLibLasDb_Find_LasConnectionListSessionIdentifier(ApiLasSessionIdType SessionIdentifier);

/****************************************************************************
*  FUNCTION:       FpAppLibLasDb_Find_LasConnectionListListIdentifier
*
*  RETURNS :       The pointer is NULL, if there is no more data.
*
*  DESCRIPTION:
****************************************************************************/
FpAppLibLasDbConnectionListType* FpAppLibLasDb_Find_LasConnectionListListIdentifier(ApiLasListIdType ListIdentifier);
#ifdef __cplusplus
}
#endif
#endif // FPAPPLIBLASSESSIONDB_H


