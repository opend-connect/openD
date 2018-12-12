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

#ifndef FPAPPLIBLASFCN_H
#define FPAPPLIBLASFCN_H

/****************************************************************************
*                               Include files
****************************************************************************/
//Type definitions

//Framework/Kernel

//Interfaces
#include <Phoenix/FpAppLib/LasDb/FpAppLibLasDbSessionDb.h>

//Configurations

//Private

/****************************************************************************
*                              Macro definitions
****************************************************************************/
//#define FPAPPLIBLAS_TEST
#ifdef FPAPPLIBLAS_TEST
extern void EepromFlush(void);
#define EEPROMFLUSH() EepromFlush()
#else
#define EEPROMFLUSH() {(void)0;}
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


/****************************************************************************
*                           Global variables/const
****************************************************************************/


/****************************************************************************
*                             Function prototypes
****************************************************************************/
void LasDb_General_CreateConnectionItem(FpAppLibLasDbConnectionListType** LasConnection, rsuint16 LengthOfData, rsbool (*CallBack)(const RosMailType* MailPtr, FpAppLibLasDbConnectionListType* LasConnection));
void LasDb_General_DestroyConnectionItem(FpAppLibLasDbConnectionListType** LasConnection);

rsbool LasDb_General_StartSessionReq(FpAppLibLasDbConnectionListType* LasConnection, const RosMailType* MailPtr, rsuint16 NextState, ApiLasListIdType ListIdentifier);
rsbool LasDb_General_EndSessionReq(FpAppLibLasDbConnectionListType* LasConnection, PrimitiveType CurrentMail, rsuint16 NextState);

//void LasIntNames_SearchReq(ApiLasSessionIdType SessionIdentifier, rsuint8 HandsetId);
//void LasIntNames_SaveReq(ApiLasSessionIdType SessionIdentifier, ApiLasEntryIdType EntryIdentifier, rsuint8 HandsetId);
//void LasIntNames_DeleteReq(ApiLasSessionIdType SessionIdentifier, ApiLasEntryIdType EntryIdentifier);
//
//void LasLineSettings_ReadAttachedHandsetsReq(ApiLasSessionIdType SessionIdentifier, ApiLasEntryIndexType StartIndex);
//void LasLineSettings_EditAttachedHandsetsReq(ApiLasSessionIdType SessionIdentifier, ApiLasEntryIdType EntryIdentifier);
//void LasLineSettings_SaveAttachedHandsetsReq(ApiLasSessionIdType SessionIdentifier, ApiLasEntryIdType EntryIdentifier, rsuint8* Bitmap, rsuint8 LengthOfBitmap);
//
//
//void   LasLineSettings_GetAttachedHandsets(ApiInfoElementType *IeBlockPtr, rsuint16 IeBlockLength, rsuint8** Bitmap, rsuint8 *LengthOfBitmap);
//rsbool LasLineSettings_CheckAttachedHandsets(rsuint8* Bitmap, rsuint8 LengthOfBitmap, rsuint8 HandsetId);
//void   LasLineSettings_SetAttachedHandsets(rsuint8** Bitmap, rsuint8 *LengthOfBitmap, rsuint8 HandsetId);
//void   LasLineSettings_ClearAttachedHandsets(rsuint8* Bitmap, rsuint8 LengthOfBitmap, rsuint8 HandsetId);
//
//void LasSystemSettings_ReadClockMasterReq(ApiLasSessionIdType SessionIdentifier);
//void LasSystemSettings_GetClockMaster(ApiInfoElementType *IeBlockPtr, rsuint16 IeBlockLength, ApiLasClockMasterTypeType *ClockMaster);
//void LasSystemSettings_ReadVersionNumbersReq(ApiLasSessionIdType SessionIdentifier);
//void LasSystemSettings_GetFwVersion(ApiInfoElementType *IeBlockPtr, rsuint16 IeBlockLength, rsuint8* *FwVersion, rsuint8 *LengthOfFwVersion);
//void LasSystemSettings_GetEeVersion(ApiInfoElementType *IeBlockPtr, rsuint16 IeBlockLength, rsuint8* *EeVersion, rsuint8 *LengthOfEeVersion);
//void LasSystemSettings_GetHwVersion(ApiInfoElementType *IeBlockPtr, rsuint16 IeBlockLength, rsuint8* *HwVersion, rsuint8 *LengthOfHwVersion);
//void LasSystemSettings_EditVersionNumbersReq(ApiLasSessionIdType SessionIdentifier, ApiLasEntryIdType EntryIdentifier);

rsbool LasDb_General_ReadReq(FpAppLibLasDbConnectionListType* LasConnection,
		const RosMailType* MailPtr,
		rsuint16 NextState,
		ApiLasListIdType ListIdentifier);
rsbool LasDb_General_EditReq(FpAppLibLasDbConnectionListType* LasConnection,
		const RosMailType* MailPtr,
		rsuint16 NextState,
		ApiLasListIdType ListIdentifier);
rsbool LasDb_General_SaveReq(FpAppLibLasDbConnectionListType* LasConnection,
		const RosMailType* MailPtr,
		rsuint16 NextState,
		ApiLasListIdType ListIdentifier);



#endif //FPAPPLIBLASFCN_H

