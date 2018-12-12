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

#ifndef APILASBUILDIE_H
#define APILASBUILDIE_H

/****************************************************************************
*                               Include files
****************************************************************************/
//Type definitions

//Framework/Kernel

//Interfaces
#include <Phoenix/Api/Types/ApiTypes.h>
#include <Phoenix/Api/Las/ApiLas.h>

//Configurations

//Private

#ifdef __cplusplus
extern "C"
{
#endif
/****************************************************************************
*                              Macro definitions
****************************************************************************/


/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


/****************************************************************************
*                           Global variables/const
****************************************************************************/


/****************************************************************************
*                             Function prototypes
****************************************************************************/
void Las_BuildIe_ApiLasSortingFields (ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType* SortingFields, rsuint8 LengthOfSortingFields);
void Las_BuildIe_ApiLasEditableFields (ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType* FieldIdentifiers, rsuint8 LengthOfFieldIdentifiers);
void Las_BuildIe_ApiLasNonEditableFields (ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType* FieldIdentifiers, rsuint8 LengthOfFieldIdentifiers);
void Las_BuildIe_ApiLasReqFldIdentifiers (ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType* FieldIdentifiers, rsuint8 LengthOfFieldIdentifiers);
void Las_BuildIe_ApiLasSearchText (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsuint8* Characters, rsuint8 LengthOfCharacters);
void Las_BuildIe_ApiLasListIdentifier (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, ApiLasListIdType* ListIdentifiers, rsuint8 LengthOfListIdentifiers);
void Las_BuildIe_ApiLasNumber (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsbool Internal, rsbool Own, rsuint8* Number, rsuint8 LengthOfNumber);
void Las_BuildIe_ApiLasName (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsuint8* Name, rsuint8 LengthOfName);
void Las_BuildIe_ApiLasDateTime (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsuint8 Year, rsuint8 Month, rsuint8 Day, rsuint8 Hour, rsuint8 Min, rsuint8 Sec, rsuint8 TimeZone);
void Las_BuildIe_ApiLasEntryReadStatus (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, ApiLasReadStatusType ReadStatus);
void Las_BuildIe_ApiLasLineName (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsuint8* LineName, rsuint8 LengthOfLineName);
void Las_BuildIe_ApiLasLineId (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLineIdentifierSubType IdentifierSubtype, rsuint8* LineIdentifier, rsuint8 LengthOfLineIdentifier);
void Las_BuildIe_ApiLasNumberOfCalls (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsuint8 NumberOfCalls);
void Las_BuildIe_ApiLasCallType (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, ApiLasCallTypeType CallType);
void Las_BuildIe_ApiLasFirstName (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsuint8* FirstName, rsuint8 LengthOfFirstName);
void Las_BuildIe_ApiLasContactNumber (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, /*rsuint8 Default,*/ rsuint8 NumberOfNumbers, rsuint16 LengthOfNumbers, rsuint8* Numbers);
void Las_BuildIe_ApiLasAssMelody (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsuint8 MelodyId);
void Las_BuildIe_ApiLasCallInterception (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasCallInterceptionTypeType CallInterception);
void Las_BuildIe_ApiLasPinCode (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsuint8* PinCode);
void Las_BuildIe_ApiLasClockMaster (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasClockMasterTypeType ClockMaster);
void Las_BuildIe_ApiLasBaseReset (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasBaseResetTypeType Reset);
void Las_BuildIe_ApiLasIpAdrType (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasIpAdrTypeType IpAddressType);

void Las_BuildIe_ApiLasVerFirmware (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool PinProtected, rsuint8* Character, rsuint8 LengthOfCharacter);
void Las_BuildIe_ApiLasVerEeProm (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool PinProtected, rsuint8* Character, rsuint8 LengthOfCharacter);
void Las_BuildIe_ApiLasVerHardware (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool PinProtected, rsuint8* Character, rsuint8 LengthOfCharacter);
void Las_BuildIe_ApiLasEmissionMode (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool PinProtected, rsbool Editable, ApiLasNoEmissionModeType NoEmissionMode);
void Las_BuildIe_ApiLasNewPinCode (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsuint8* PinCode);
void Las_BuildIe_ApiLasAttachedHandsets (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsuint8* Bitmap, rsuint8 LengthOfBitmap);
void Las_BuildIe_ApiLasDialingPrefix (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsuint8* Number, rsuint8 LengthOfNumber);
void Las_BuildIe_ApiLasFpMelody (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsuint8 Value);
void Las_BuildIe_ApiLasFpVolume (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsuint8 Volume);
void Las_BuildIe_ApiLasBlockedNumber (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsuint8 NumberOfNumbers, rsuint16 LengthOfNumbers, rsuint8* Numbers);
void Las_BuildIe_ApiLasMultipleCall (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasMultipleCallModeType MultipleCallMode);
void Las_BuildIe_ApiLasIntrusionCall (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasIntrusionCallModeType IntrusionCallMode);
void Las_BuildIe_ApiLasPermanentClir (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasPermanentClirTypeType ClirMode, rsuint8 LengthOfActivationCode, rsuint8 LengthOfDeactivationCode, rsuint8* ClirCodes);
rsbool Las_BuildIe_ApiLasCallForwardingCfu (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasCallForwardStateType State, rsuint8 LengthOfActivationCode, rsuint8 LengthOfDeactivationCode, rsuint8 LengthOfCfNumber, rsuint8 *Data);
rsbool Las_BuildIe_ApiLasCallForwardingCfna (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasCallForwardStateType State, rsuint8 DelayTime, rsuint8 LengthOfActivationCode, rsuint8 LengthOfDeactivationCode, rsuint8 LengthOfCfNumber, rsuint8 *Data);
rsbool Las_BuildIe_ApiLasCallForwardingCfb (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasCallForwardStateType State, rsuint8 LengthOfActivationCode, rsuint8 LengthOfDeactivationCode, rsuint8 LengthOfCfNumber, rsuint8 *Data);

rsbool Las_BuildIe_ApiLasCountryCode (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiLasCountryCodeTypeType CountryCode);
rsbool Las_BuildIe_ApiLasIpMac (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, rsuint16 LengthOfIpMac, rsuint8* IpMac);
rsbool Las_BuildIe_ApiLasDectMode (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsbool PinProtected, ApiDectTypeType DectMode);

void Las_BuildIe_ApiLasPinProtectedFields (ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType* FieldIdentifiers, rsuint8 LengthOfFieldIdentifiers);
void Las_BuildIe_ApiLasDisabledFields (ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType* FieldIdentifiers, rsuint8 LengthOfFieldIdentifiers);

void Las_BuildIe_ApiLasLockedEntriesList (ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, rsuint8* LockedEntriesList, rsuint8 LengthOfLockedEntriesList);

#ifdef __cplusplus
}
#endif
#endif //APILASBUILDIE_H

