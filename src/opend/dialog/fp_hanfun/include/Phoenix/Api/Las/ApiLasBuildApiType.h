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

#ifndef APILASBUILDAPITYPE_H
#define APILASBUILDAPITYPE_H

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
void Las_BuildType_ApiLasPinCode (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsuint8* PinCode);
void Las_BuildType_ApiLasClockMaster (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasClockMasterTypeType ClockMaster);
void Las_BuildType_ApiLasBaseReset (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasBaseResetTypeType Reset);
void Las_BuildType_ApiLasIpAdrType (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasIpAdrTypeType IpAddressType);
void Las_BuildType_ApiLasIpAdrValue (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasIpAdrFormatType IpAddressFormat, rsuint8* Digits);
void Las_BuildType_ApiLasIpSubnetMask (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasIpAdrFormatType IpAddressFormat, rsuint8* Digits);
void Las_BuildType_ApiLasIpGateway (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasIpAdrFormatType IpAddressFormat, rsuint8* Digits);
void Las_BuildType_ApiLasIpDns (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasIpAdrFormatType IpAddressFormat, rsuint8* Digits);
void Las_BuildType_ApiLasVerFirmware (rsuint8** IeData, rsuint8* IeLength, rsbool PinProtected, rsuint8 LengthOfCharacter, rsuint8* Character);
void Las_BuildType_ApiLasVerEeProm (rsuint8** IeData, rsuint8* IeLength, rsbool PinProtected, rsuint8 LengthOfCharacter, rsuint8* Character);
void Las_BuildType_ApiLasVerHardware (rsuint8** IeData, rsuint8* IeLength, rsbool PinProtected, rsuint8 LengthOfCharacter, rsuint8* Character);
void Las_BuildType_ApiLasEmissionMode (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasNoEmissionModeType NoEmissionMode);
void Las_BuildType_ApiLasNewPinCode (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, rsuint8* PinCode);



void Las_BuildType_ApiLasLineName (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, rsuint8* LineName, rsuint8 LengthOfLineName);
void Las_BuildType_ApiLasLineId (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLineIdentifierSubType IdentifierSubtype, rsuint8* LineIdentifier, rsuint8 LengthOfLineIdentifier);
void Las_BuildType_ApiLasAttachedHandsets (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, rsuint8* Bitmap, rsuint8 LengthOfBitmap);
void Las_BuildType_ApiLasDialingPrefix (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, rsuint8* Number, rsuint8 LengthOfNumber);
void Las_BuildType_ApiLasFpMelody (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, rsuint8 Value);
void Las_BuildType_ApiLasFpVolume (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, rsuint8 Volume);
void Las_BuildType_ApiLasBlockedNumber (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, rsuint8 NumberOfNumbers, rsuint8* Numbers, rsuint16 LengthOfNumbers);
void Las_BuildType_ApiLasMultipleCall (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasMultipleCallModeType MultipleCallMode);
void Las_BuildType_ApiLasIntrusionCall (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasIntrusionCallModeType IntrusionCallMode);
void Las_BuildType_ApiLasPermanentClir (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasPermanentClirTypeType ClirMode, rsuint8 LengthOfActivationCode, rsuint8 LengthOfDeactivationCode, rsuint8* ClirCodes);
rsbool Las_BuildType_ApiLasCallForwardingCfu (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasCallForwardStateType State, rsuint8 LengthOfActivationCode, rsuint8 LengthOfDeactivationCode, rsuint8 LengthOfCfNumber, rsuint8 *Data);
rsbool Las_BuildType_ApiLasCallForwardingCfna (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasCallForwardStateType State, rsuint8 DelayTime, rsuint8 LengthOfActivationCode, rsuint8 LengthOfDeactivationCode, rsuint8 LengthOfCfNumber, rsuint8 *Data);
rsbool Las_BuildType_ApiLasCallForwardingCfb (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasCallForwardStateType State, rsuint8 LengthOfActivationCode, rsuint8 LengthOfDeactivationCode, rsuint8 LengthOfCfNumber, rsuint8 *Data);


void Las_BuildType_ApiLasNumberOfCalls (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsuint8 NumberOfCalls);
void Las_BuildType_ApiLasCallType (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, ApiLasCallTypeType CallType);
void Las_BuildType_ApiLasName (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsuint8 LengthOfName, rsuint8* Name);
void Las_BuildType_ApiLasFirstName (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsuint8 LengthOfFirstName, rsuint8* FirstName);
void Las_BuildType_ApiLasContactNumber (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsuint8 NumberOfNumbers, rsuint16 LengthOfNumbers, rsuint8* Numbers);
void Las_BuildType_ApiLasAssMelody (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, rsuint8 MelodyId);
void Las_BuildType_ApiLasCallInterception (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, ApiLasCallInterceptionTypeType CallInterception);
void Las_BuildType_ApiLasNumber (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsbool PinProtected, rsbool Internal, rsbool Own, rsuint8 LengthOfNumber, rsuint8* Number);

void Las_BuildType_ApiLasDateTime (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, rsuint8 Year, rsuint8 Month, rsuint8 Day, rsuint8 Hour, rsuint8 Min, rsuint8 Sec, rsuint8 TimeZone);
void Las_BuildType_ApiLasEntryReadStatus (rsuint8** IeData, rsuint8* IeLength, rsbool Editable, ApiLasReadStatusType ReadStatus);


#ifdef __cplusplus
}
#endif
#endif //APILASBUILDAPITYPE_H

