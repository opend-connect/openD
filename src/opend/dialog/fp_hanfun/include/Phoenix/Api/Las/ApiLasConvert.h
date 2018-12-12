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
#ifndef APILASCONVERT_H
#define APILASCONVERT_H


/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Las/ApiLas.h>

#ifdef PHOENIX_API_LAS
#include <NwkSwitch/Las/Common/LasTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
rsbool   ApiLasConvertLasDataToApiIe(const ApiLasListIdType ListIdentifier,const LasDataPacketEntryType *LasDataPacketEntry, ApiInfoElementType **ieBlockPtr, rsuint16 *ieBlockLength);
void     ApiLasConvertApiIeToLasData (const ApiLasListIdType ListIdentifier, const rsuint16 EntryIdentifier, const rsuint8* ieBlockPtr, const rsuint16 ieBlockLength, LasDataPacketEntryType* LasDataPacketEntry);

rsuint16 ApiLasCalculateAirDataLength(const rsuint8* pData);
void     ApiLasConvertDataToAir(const rsuint8* pData, rsuint8 *LasAirData, const rsuint16 LasAirDataLength );
rsbool   ApiLasConvertAirToData(rsuint8** pData, const rsuint8 *LasAirData, const rsuint16 LasAirDataLength);


/****************************************************************************
*  FUNCTION:       ApiLasConvertApiIeToLasFieldId
*
*  RETURNS :       Las field identifier.
*
*  DESCRIPTION:    This function converts an ApiIeType to a Las field
                   identifier.
****************************************************************************/
LasFieldIdentifierType ApiLasConvertApiIeToLasFieldId(const ApiIeType ApiIeFieldId,
                                                             /*!< ApiIe field identifier */
                                                      const ApiLasListIdType ListIdentifier);

/****************************************************************************
*  FUNCTION:       ApiLasConvertAllApiIeToLasFieldId
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function converts a list of ApiIeType to Las field
                   identifiers.
****************************************************************************/
void ApiLasConvertAllApiIeToLasFieldId(const ApiIeType *ApiIeFieldId,
                                                             /*!< List of ApiIe field
                                                                identifiers */
                                       const rsuint8 ApiIeFieldIdLength,
                                                             /*!< Length of ApiIeFieldId
                                                                in bytes. */
                                       const ApiLasListIdType ListIdentifier,
                                       LasFieldIdentifierType **LasFieldId,
                                                             /*!< List of Las field
                                                                identifiers */
                                       rsuint8 *LasFieldIdLength);
                                                             /*!< Length of LasFieldId
                                                                in bytes. */

/****************************************************************************
*  FUNCTION:       ApiLasConvertLasFieldIdToApiIe
*
*  RETURNS :       ApiIe field identifier.
*
*  DESCRIPTION:    This function converts an ApiIeType to a Las field
                   identifier.
****************************************************************************/
ApiIeType ApiLasConvertLasFieldIdToApiIe(const LasFieldIdentifierType FieldIdentifier,
                                                             /*!< Las field identifier */
                                         const ApiLasListIdType ListIdentifier);

/****************************************************************************
*  FUNCTION:       ApiLasConvertAllLasFieldIdToApiIe
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function converts a list of ApiIeType to Las field
                   identifiers.
****************************************************************************/
void ApiLasConvertAllLasFieldIdToApiIe(const LasFieldIdentifierType *LasFieldId,
                                                             /*!< List of Las field
                                                                identifiers */
                                       const rsuint8 LasFieldIdLength ,
                                                             /*!< Length of LasFieldId
                                                                in bytes. */
                                       const ApiLasListIdType ListIdentifier,
                                       ApiIeType *ApiIeFieldId ,
                                                             /*!< List of ApiIe field
                                                                identifiers */
                                       rsuint8 *ApiIeFieldIdLength);
                                                             /*!< Length of ApiIe in
                                                                bytes. */
#ifdef __cplusplus
}
#endif
#endif // PHOENIX_API_LAS
#endif //APILASCONVERT_H
