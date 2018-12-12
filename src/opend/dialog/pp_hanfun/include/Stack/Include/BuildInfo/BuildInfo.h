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

#ifndef BUILDINFO_H
#define BUILDINFO_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

// Typically set in makefile:
// IAR: BASICCOMPILEROPTIONS+=-DBUILDINFO_DATA_ADR=__data24
// gcc: BASICCOMPILEROPTIONS+=-DBUILDINFO_DATA_ADR=__attribute__((data24))
#ifndef BUILDINFO_DATA_ADR
  #define BUILDINFO_DATA_ADR
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

extern BUILDINFO_DATA_ADR const unsigned char  ReleaseLabel[];
extern BUILDINFO_DATA_ADR const unsigned short VersionHexFormat;
extern BUILDINFO_DATA_ADR const unsigned short VersionBranchHexFormat;
extern BUILDINFO_DATA_ADR const unsigned char  VersionStrFormat[];
extern BUILDINFO_DATA_ADR const unsigned char  ProgrammerId[];
extern BUILDINFO_DATA_ADR const unsigned char  LinkDate[5];
#ifdef BUILDINFO_ENABLE_SYSTEMNAME
extern BUILDINFO_DATA_ADR const unsigned char  BldInfo_SystemName[];
#endif
#ifdef BUILDINFO_ENABLE_PRODUCTID
extern BUILDINFO_DATA_ADR const unsigned long  BldInfo_ProductId;
#endif
#ifdef BUILDINFO_ENABLE_BUILDNO
extern BUILDINFO_DATA_ADR const unsigned short BldInfo_BuildNo;
#endif
#ifdef BUILDINFO_ENABLE_COMMENT
extern BUILDINFO_DATA_ADR const unsigned char  BldInfo_Comment[];;
#endif

/****************************************************************************
*                             Function prototypes
****************************************************************************/

RS_END_EXTERN_C

#endif

