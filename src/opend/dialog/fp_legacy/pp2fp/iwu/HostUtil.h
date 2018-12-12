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

#ifndef __PP_MMI_HOST_UTIL_H
#define __PP_MMI_HOST_UTIL_H

#include <stdint.h>
#include <Core/RtxCore.h>
#include <Phoenix/Api/Types/ApiTypes.h>
#include <win32sim/debug/dbg_intf.h>
/****************************************************************************
*                                   Defines
****************************************************************************/
extern rsuint16 ColaNvsOffset;
extern rsuint16 ColaNvsSize;


#define MMI_AUDIO_HANDLING_ENABLED // used to enable audio commands control in the mmi (mute/unmute/tones/headset)

#define DBG_INTF_REDEFINE_PRINTF
#define LOCAL_TIMER_ID 6

#define NUMBER_OF_CODEC_LIST_ENTRIES 2
#define EEPROM_SIZE 0x2F4C


uint8_t dialogHost_init( void );

extern void LocalMainAppTaskInit(void);
extern void LocalMainAppTask(RosMailType *MailPtr);
extern void ColaTask(const RosMailType *MailPtr);

typedef rsuint16 RcHeapSizeType; /*!< Type used for the size field for individual heap blocks. */

extern void ApiBuildInfoElement(ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType Ie, rsuint8 IeLength, rsuint8 *IeData);
extern void ApiFreeInfoElement(ApiInfoElementType **IeBlockPtr);
extern RcHeapSizeType RcHeapGetBlockSize(void* Block);

typedef rsuint8  EepromDataPtrType;       // Type used for the pointer to the data to write
typedef rsuint16 EepromDataAddressType;   // Type used for addressing into the eeprom
typedef rsuint16 EepromDataLengthType;
extern EepromDataPtrType EepromReadByte(EepromDataAddressType uAddress);
extern rsbool DisplayActive;

extern void RosTimerStop(RosTimerIdType TimerId);
extern void RosTimerStart(RosTimerIdType TimerId, RsTimerTickType Value, const RosTimerConfigType* Config);

extern void RcHeapFreeEx(void* Block, RcHeapFlagsType Flags);

typedef enum
{
  KEY_FILTER_NUM_MODE,
  KEY_FILTER_ALPHA_CAPITAL_MODE,
  KEY_FILTER_MODE_MAX
} RSENUM8(KeyFilterModeType);
extern void KeyFilterSetModeOneChar(KeyFilterModeType Mode);

extern void KeyboardFilterKeyboardInit(void);

extern void Las_BuildIe_ApiLasPinCode (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsuint8* PinCode);
//extern void* RcHeapReallocEx(void* Block, RcHeapSizeType Size, RcHeapFlagsType Flags);
//extern void RcHeapFreeEx(void* Block, RcHeapFlagsType Flags);
#ifdef NATALIE_V11
extern void RosMailFree(RosMailType* Mail);
#endif
#endif //__PP_MMI_HOST_UTIL



