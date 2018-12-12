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
/*! \file
* Linux/GCC specific types and macros.
*/

/** \cond internal */


#ifndef RS_TARGET_INC_H
#define RS_TARGET_INC_H

/****************************************************************************
*                               Include files
****************************************************************************/

#if (RS_SYSHEADERS == 1)
  #ifdef __KERNEL__
    #ifdef __cplusplus
      extern "C"
      {
        #include <linux/types.h>
        #include <linux/string.h>
        #include <linux/spinlock.h>
      }
    #else
      #include <stddef.h>
      #include <asm/types.h>
      #include <asm/system.h>
      #include <asm/byteorder.h>
      #include <linux/string.h>
      #include <linux/spinlock.h>
    #endif
  #else
    #include <string.h>
    #ifdef __linux__
      #include <endian.h>
    #endif
  #endif
#endif
#if (RS_SYSHEADERS == 0)
  #include <RsSysHeaders.h>
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define RS_FAR_ADR
#define RS_NEAR_ADR
#define RS_RAM_ADR
#define RS_RAM_ATTR
#define RS_NO_INIT
#define RS_ROOT_SYMBOL __attribute__((used))
#define RS_NOP nop()
#define RS_NAKED __attribute__((naked))
#define RS_NORETURN __attribute__((noreturn))

#ifdef __i386__
  #define RS_BREAKPOINT __asm__ volatile ("int $0x03")
#endif
#if defined(__CR16__) || defined(__CR16C__) || defined(__CR16CP__)
  #define RS_BREAKPOINT __asm__ volatile ("excp bpt")
#endif
#ifdef __mips__
  #define RS_BREAKPOINT __asm__ volatile ("break %0" : : "i" (512))
#endif

#ifdef RS_SET_PACKING
  #if (RS_SET_PACKING == 1)
    #pragma pack(1)
  #endif
  #if (RS_SET_PACKING == 2)
    #pragma pack(2)
  #endif
  #if (RS_SET_PACKING == 4)
    #pragma pack(4)
  #endif
#endif

#define RS_PACKED_STRUCT_BEGIN     struct
#define RS_PACKED_STRUCT_END(name) __attribute__((packed)) name
#define RS_PACKED_UNION_BEGIN      union
#define RS_PACKED_UNION_END(name)  __attribute__((packed)) name
#define RS_PACKED_MEMBER           __attribute__((packed))
#define RS_PACKED_PTR              __attribute__((packed))

#if defined(__CR16__) || defined(__CR16C__) || defined(__CR16CP__)
  #define RS_AUTOSIZE_ENUMS
#endif

#ifdef __KERNEL__
  #ifdef __LITTLE_ENDIAN
    #define RS_ENDIAN_TYPE RS_LITTLE_ENDIAN
  #endif
  #ifdef __BIG_ENDIAN
    #define RS_ENDIAN_TYPE RS_BIG_ENDIAN
  #endif
#else
  #ifdef __BYTE_ORDER
    #if (__BYTE_ORDER == __LITTLE_ENDIAN)
      #define RS_ENDIAN_TYPE RS_LITTLE_ENDIAN
    #endif
    #if (__BYTE_ORDER == __BIG_ENDIAN)
      #define RS_ENDIAN_TYPE RS_BIG_ENDIAN
    #endif
  #endif
  #ifdef _BYTE_ORDER
    #if (_BYTE_ORDER == _LITTLE_ENDIAN)
      #define RS_ENDIAN_TYPE RS_LITTLE_ENDIAN
    #endif
    #if (_BYTE_ORDER == _BIG_ENDIAN)
      #define RS_ENDIAN_TYPE RS_BIG_ENDIAN
    #endif
  #endif
#endif

#ifdef __KERNEL__
  #define RS_OVERRIDE_INTERRUPTS
  #define RS_OVERRIDE_ERROR
  #define RS_UNLOCK_ON_ERROR
#endif

#define RS_ENABLE_INT64

#ifdef __LP64__
  #define RS_OVERRIDE_TYPES
  #define RS_POINTER_SIZE 8
  typedef char rschar;                  /*!< Plain char for strings. */
  typedef unsigned char rsuint8;        /*!< 8-bit unsigned quantity. */
  typedef signed char rsint8;           /*!< 8-bit signed quantity. */
  typedef unsigned short rsuint16;      /*!< 16-bit unsigned quantity. */
  typedef signed short rsint16;         /*!< 16-bit signed quantity. */
  typedef unsigned int rsuint32;        /*!< 32-bit unsigned quantity. */
  typedef signed int rsint32;           /*!< 32-bit signed quantity. */
  typedef unsigned char rsbitfield;     /*!< For use as bitfields. */
  typedef unsigned char rsbool;         /*!< boolean quantity. */
  typedef unsigned long long rsuint64;  /*!< 64-bit unsigned quantity. */
  typedef signed long long rsint64;     /*!< 64-bit signed quantity. */
  typedef unsigned long long rsuintptr; /*!< Unsigned quantity, same size as a pointer, 32 or 64 bits. */
#endif

#define RS_C_INLINE __inline__ static

#define RSISR(fn) void fn(void)

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef unsigned long rsuintsz;

typedef unsigned long RsIntStatusType;

typedef unsigned long RsRaType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __KERNEL__
extern spinlock_t RsLock;
#endif

/****************************************************************************
*                                Implementation
****************************************************************************/

static __inline__ RsRaType RsReturnAddress(void)
{
  #if defined(__CR16C__) || defined(__CR16CP__)
  register RsRaType ra asm("ra");
  register volatile RsRaType t = ra;
  return t << 1;
  #else
  return (RsRaType)__builtin_return_address(0);
  #endif
}

static __inline__ void RsSetRA(RsRaType ra)
{
  ;
}

#ifdef __KERNEL__
#ifndef __cplusplus
static __inline__ RsIntStatusType RsDisableInterrupts(void)
{
  RsIntStatusType saved=0;
  local_irq_save(saved);
  #ifdef irqs_disabled_flags
  if (!irqs_disabled_flags(saved))
  {
    spin_lock(&RsLock);
  }
  #endif
  return saved;
}

static __inline__ void RsEnableInterrupts(RsIntStatusType Saved)
{
  #ifdef irqs_disabled_flags
  if (!irqs_disabled_flags(Saved))
  {
    spin_unlock(&RsLock);
  }
  #endif
  local_irq_restore(Saved);
}

static __inline__ unsigned char RsInterruptsEnabled(void)
{
  if (irqs_disabled())
  {
    return 0;
  }
  return 1;
}

static __inline__ void RsDisableIntsForced(void)
{
  local_irq_disable();
}

static __inline__ void RsEnableIntsForced(void)
{
  local_irq_enable();
}
#endif
#endif

static __inline__ void fosMemcpy(unsigned char* destination, unsigned char* source, unsigned short size)
{
  memcpy(destination, source, (size_t)size);
}

static __inline__ void fosMemset(unsigned char* destination, unsigned char set, unsigned short size)
{
  memset(destination, set, (size_t)size);
}

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif

// End of file.

