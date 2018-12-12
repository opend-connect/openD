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

#ifndef FPAPPLIBLASCALLLOG_H
#define FPAPPLIBLASCALLLOG_H

/****************************************************************************
*                               Include files
****************************************************************************/
//Type definitions
#include <Phoenix/Api/Types/ApiTypes.h> 
#include <Phoenix/Api/Las/ApiLas.h>
//Framework/Kernel

//Interfaces

//Configurations

//Private

/****************************************************************************
*                              Macro definitions
****************************************************************************/
typedef struct
{
  ApiLasCallTypeType  CallType;
  rsuint8 LineId;
  rsuint8 NameLength;
  rsuint8 Name[16];
  rsuint8 NumberLength;
  rsuint8 Number[22];
  ApiTimeDateCodeType TimeStamp;
  rsuint16 EntryId;
} CallInfoType;

typedef struct CallLogSaveType
{
	ApiLasListIdType 	 ListId;
	ApiLasEntryIndexType EntryIndex;
	rsuint16             TotalEntries;
	void                 (*DB_GetEntry)(unsigned char, CallInfoType *);
	rsuint8				 Direction;
	rsuint8				 MarkRead;
	rsuint8				 Custom;
	rsuint8				 Matching;
	rsuint8				 CaseSensitive;
	ApiIeType			 SortingFields[2];
	rsuint8              LengthOfSortingFields;
	rsuint8              *Search;
	rsuint8              LengthOfSearch;
} PACKED_STRUCT CallLogSaveType;

//typedef struct ApiHostCallLogSaveType
//{
//  RosPrimitiveType Primitive;            /* */
//  CallLogSaveType  CallLogInfo;
//} ApiHostCallLogSaveType;

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


/****************************************************************************
*                           Global variables/const
****************************************************************************/


/****************************************************************************
*                             Function prototypes
****************************************************************************/
void CallLogSave(CallLogSaveType* p );

void ListGetReq(CallLogSaveType* p );

#endif //FPAPPLIBLASCALLLOG_H

