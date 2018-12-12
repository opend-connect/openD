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

#ifndef DECODEARG_H
#define DECODEARG_H

/****************************************************************************
*                               Include files
****************************************************************************/
//Type definitions
#include <win32sim/common/std-def.h>

//Framework/Kernel

//Interfaces

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
typedef enum RsxBinLogType
{
  BINLOGTYPE_NONE,
  BINLOGTYPE_EAP,
  BINLOGTYPE_UART
} RsxBinLogType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/
extern char szPrimitivPath[255];   // Custom path to primitive file
extern char szEeTreePath[255];     // Custom path to eeprom tree file
extern char szRepsServerName[255]; // Reps Server name

extern char szInputFile[300];
extern boolean BatchRead;
extern RsxBinLogType BinLogType;

extern uint8 EfrCom;
extern uint32 EfrBps;

/****************************************************************************
*                             Function prototypes
****************************************************************************/
void DecodeArguments(void);

#ifdef __cplusplus
   }
#endif
#endif //DECODEARG_H

