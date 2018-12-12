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

#ifndef FWSTYPES_H
#define FWSTYPES_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define FWS_FILEVERSION 0x04

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning( default : 4820) // padding added
#endif

typedef enum
{
  FC_NONE           = 0x0000, // FwsHeaderType
  FC_FILEHEADER     = 0x0001, // FwsFileHeaderType
  FC_GUID           = 0x0002, // FwsGuidType
  FC_NAME           = 0x0003, // FwsNameType
  FC_TIMESTAMP      = 0x0004, // FwsTimestampType
  FC_LABEL          = 0x0005, // FwsLabelType
  FC_ERASE          = 0x0006, // FwsEraseType
  FC_WRITE          = 0x0007, // FwsWriteType
  FC_CRC            = 0x0008, // FwsCrcType
  FC_END            = 0x0009, // FwsHeaderType
  // Version 2.
  FC_DEVICE_MD5     = 0x000A, // FwsDeviceMd5Type
  FC_BEGIN_FILE_MD5 = 0x000B, // FwsHeaderType
  FC_END_FILE_MD5   = 0x000C, // FwsFileMd5Type
  // Version 3.
  FC_AREA_MD5       = 0x000D, // FwsDeviceMd5Type
  // Version 4.
  FC_IMAGEID        = 0x000E, // FwsImageIdType
  // Make sure enum is 16 bits.
  FC_MAX=0xFFFF
} RSENUM16(FwsCommandIdType);

typedef struct
{
  rsuint16 Size;
  FwsCommandIdType Command;
} FwsHeaderType;

#ifndef GUID_H
typedef union
{
  struct
  {
    rsuint32 Data1;
    rsuint16 Data2;
    rsuint16 Data3;
    rsuint8  Data4[8];
  };
  rsuint8 Data[1];
} GuidType;
#endif

typedef struct
{
  const GuidType* Guid;
  const rsuint8* LinkDate;
  const rschar* Name;
  const rschar* Label;
  rschar Magic[4]; // "FWS\0"
} FwsInfoType;

typedef struct
{
  rsuint16 Year;
  rsuint8 Month;
  rsuint8 Day;
  rsuint8 Hour;
  rsuint8 Minute;
} TimestampType;

typedef struct
{
  FwsHeaderType Header;
  rschar Magic[3];  // Characters "FWS".
  rsuint8 Version;  // FWS_FILEVERSION
} FwsFileHeaderType;

typedef struct
{
  FwsHeaderType Header;
  GuidType Guid;
} FwsGuidType;

typedef struct
{
  FwsHeaderType Header;
  rschar Name[102];
} FwsNameType;

typedef struct
{
  FwsHeaderType Header;
  TimestampType Timestamp;
} FwsTimestampType;

typedef struct
{
  FwsHeaderType Header;
  rschar Label[102];
} FwsLabelType;

typedef struct
{
  FwsHeaderType Header;
  rsuint32 Address;
  rsuint32 Size;
} FwsEraseType;

typedef struct
{
  FwsHeaderType Header;
  rsuint32 Address;
  rsuint8 Data[4];
} FwsWriteType;

typedef struct
{
  FwsHeaderType Header;
  rsuint32 Address;
  rsuint16 Size;
  rsuint16 Crc;
} FwsCrcType;

typedef struct
{
  FwsHeaderType Header;
  rsuint32 Address;
  rsuint32 Size;
  rsuint8 Digest[16];
} FwsDeviceMd5Type;

typedef struct
{
  FwsHeaderType Header;
  rsuint8 Digest[16];
} FwsFileMd5Type;

typedef struct
{
  FwsHeaderType Header;
  rsuint32 ImageId;
} FwsImageIdType;

typedef union
{
  FwsHeaderType Header;
  FwsFileHeaderType FileHeader;
  FwsGuidType Guid;
  FwsNameType Name;
  FwsTimestampType Timestamp;
  FwsLabelType Label;
  FwsEraseType Erase;
  FwsWriteType Write;
  FwsCrcType Crc;
  FwsDeviceMd5Type DMd5;
  FwsFileMd5Type FMd5;
  FwsImageIdType ImageId;
  rsuint8 Data[1];
} FwsCommandType;

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/****************************************************************************
*                             Function prototypes
****************************************************************************/

RS_END_EXTERN_C

#endif

// End of file.

