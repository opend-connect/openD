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

#ifndef RS_TARGET_INC_H
#define RS_TARGET_INC_H

/****************************************************************************
*                               Include files
****************************************************************************/

#if (_MSC_VER < 1400)
  #pragma message Not tested with older MSVC versions.
#endif
#if (_MSC_VER >= 1600)
  #pragma warning( disable : 4987) // nonstandard extension used: 'throw (...)'
#endif

#pragma warning( disable : 4061) // enumerator 'nn' in switch of enum 'type' is not explicitly handled by a case label
#pragma warning( disable : 4062) // enumerator 'nn' in switch of enum 'type' is not handled
#pragma warning( disable : 4100) // unreferenced formal parameter
#pragma warning( disable : 4121) // alignment of a member was sensitive to packing
#pragma warning( disable : 4201) // nonstandard extension used : nameless struct/union
#pragma warning( disable : 4214) // nonstandard extension used : bit field types other than int
#pragma warning( disable : 4255) // 'xx' : no function prototype given: converting '()' to '(void)'
#pragma warning( disable : 4668) // 'xx' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#pragma warning( disable : 4711) // function 'xx' selected for automatic inline expansion
#pragma warning( disable : 4820) // padding added
#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN // Reduce windows.h
#endif
#ifndef VC_EXTRALEAN
  #define VC_EXTRALEAN // Exclude rarely-used stuff from Windows headers
#endif
#pragma warning( disable : 4365) // signed/unsigned mismatch
#pragma warning( disable : 4826) // Conversion from 'const void *' to 'void *' is sign-extended. This may cause unexpected runtime behavior.
#include <windows.h>
#pragma warning( default : 4365) // signed/unsigned mismatch
#pragma warning( default : 4826) // Conversion from 'const void *' to 'void *' is sign-extended. This may cause unexpected runtime behavior.
#include <tchar.h>
#ifdef __GNUC__
#include <x86intrin.h>
#else
#include <intrin.h>
#endif
#pragma warning( default : 4265) // class has virtual functions, but destructor is not virtual

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define RS_FAR_ADR
#define RS_NEAR_ADR
#define RS_RAM_ADR
#define RS_RAM_ATTR
#define RS_NO_INIT
#define RS_ROOT_SYMBOL
#define RS_NOP __nop()
#define RS_NAKED
#define RS_NORETURN

#define RS_BREAKPOINT DebugBreak()

#ifdef RS_SET_PACKING
  #pragma pack(RS_SET_PACKING)
#endif

#define RS_ENABLE_INT64

#ifdef _WIN64
  #define RS_POINTER_SIZE 8
#endif

#define RS_OVERRIDE_TICK_TYPES

#define RS_CONST

#ifdef _DEBUG
  #define RS_OVERRIDE_ASSERT
  #define RSASSERT(p) ((p) ? (void)0 : RS_BREAKPOINT)
#endif

#define RS_C_INLINE __inline

#define FOS_START_ON_INT_STACK

#if (RS_RTOS_ID == RSTS_FUSION)
  #define FOS_VIRTUAL_HWIS
#endif

#define RSISR(fn) void fn(void)

typedef unsigned long rsuintsz;

/// For saving interrupt status, returned from \ref RsDisableInterrupts.
typedef unsigned long RsIntStatusType;

typedef ULONG_PTR RsRaType; /*!< Return address. */

#ifdef __cplusplus
extern "C"
#endif
/// Get return address of the current function i.e. the address after the branch/call/jump instruction.
/** \return Return address. */
__forceinline RsRaType RsReturnAddress(void)
{
  return (RsRaType)_ReturnAddress();
}

/** \cond internal */

#define RsSetRA(ra)

#define RsEiWait()

#define RsDisableICache()
#define RsEnableICache()
#define RsDisableDCache()
#define RsEnableDCache()
#define RsInvalidateICache()
#define RsInvalidateDCache()

#ifdef __cplusplus
extern "C"
#endif
__forceinline void fosMemcpy(unsigned char* destination, unsigned char* source, unsigned short size)
{
  memcpy(destination, source, size);
}

#ifdef __cplusplus
extern "C"
#endif
__forceinline void fosMemset(unsigned char* destination, unsigned char set, unsigned short size)
{
  memset(destination, set, size);
}

/** \endcond */

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef unsigned long RsTimerTickType; /*!< For timer tick values. */
typedef unsigned long long RsPerformanceTickType; /*!< For performance/profiling tick values. */
typedef unsigned short RsPerformanceTimeType; /*!< For performance/profiling time values. */

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
* DESCRIPTION:
****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif

// End of file.

