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
* CR16C/GCC specific types and macros.
*/

/** \cond internal */


#ifndef RS_TARGET_INC_H
#define RS_TARGET_INC_H

/****************************************************************************
*                               Include files
****************************************************************************/

#if (RS_SYSHEADERS == 1)
  #include <stddef.h>
  #include <string.h>
#endif
#if (RS_SYSHEADERS == 0)
  #include <RsSysHeaders.h>
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define _di_() __asm__ volatile ("di" :  :  : "cc")
#define _ei_() __asm__ volatile ("ei" :  :  : "cc")

#define _eiwait_() __asm__ volatile ("eiwait" :  :  : "cc")

#define _excp_(vector) __asm__ volatile ("excp " # vector)

#define _nop_() __asm__ volatile ("nop")

#define _lpr_(procreg, src) __asm__ volatile ("lpr\t%0," procreg : /* no output */ : "r" (src) : "cc")

#define _spr_(procreg, dest) __asm__ volatile ("spr\t" procreg ",%0" : "=r" (dest))

#define _lprd_(procregd, src) __asm__ volatile ("lprd\t%0," procregd : /* no output */ : "r" (src) : "cc")

#define _sprd_(procregd, dest) __asm__ volatile ("sprd\t" procregd ",%0" : "=r" (dest))

#define RS_FAR_ADR __attribute__((data32))
#define RS_NEAR_ADR __attribute__((data16))
#define RS_RAM_ADR
#define RS_RAM_ATTR __attribute__((section("RAMCODE." RS_QUOTEy(__LINE__))))
#define RS_NO_INIT
#define RS_ROOT_SYMBOL __attribute__((used))
#define RS_NOP _nop_()
#define RS_NAKED __attribute__((naked))
#define RS_NORETURN __attribute__((noreturn))

#define RS_BREAKPOINT _excp_(bpt)

#ifndef RS_FASTCODE_ADR
  #ifdef RS_FASTCODE_SEG
    #define RS_FASTCODE_ADR __attribute__((section(RS_QUOTEy(RS_FASTCODE_SEG) "." RS_QUOTEy(__LINE__))))
  #else
    #define RS_FASTCODE_ADR
  #endif
#endif

#ifndef __NSC_CRCC__
  #if (RS_SET_PACKING)
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
#endif

#define RS_PACKED_STRUCT_BEGIN     struct
#define RS_PACKED_STRUCT_END(name) __attribute__((packed)) name
#define RS_PACKED_UNION_BEGIN      union
#define RS_PACKED_UNION_END(name)  __attribute__((packed)) name
#define RS_PACKED_MEMBER           __attribute__((packed))
#define RS_PACKED_PTR              __attribute__((packed))

#define RS_AUTOSIZE_ENUMS

#define RS_ENABLE_INT64

#define RS_OVERRIDE_INTERRUPTS

#define RS_C_INLINE __inline__ __attribute__((always_inline)) static

#ifndef RSOFFSETOF
  #define RSOFFSETOF(type, field) __builtin_offsetof(type, field)
#endif

#if (RS_RTOS_ID == RSTS_FUSION) || (RS_HOOK_PRE_HWI == 1)
  #define RSISR(fn) void fn(void)
#else
  #define RSISR(fn) __attribute__((interrupt)) void fn(void)
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef unsigned long rsuintsz;

typedef unsigned short RsIntStatusType;

typedef unsigned long RsRaType;

typedef void RsIntVecType(void);

typedef void RsIsrType(void);

typedef struct
{
  RsIsrType* Isr;
} RsIsrEntryType;

typedef enum
{
  CR16C_PSR_C = 1 << 0,
  CR16C_PSR_T = 1 << 1,
  CR16C_PSR_L = 1 << 2,
  CR16C_PSR_U = 1 << 3,
  CR16C_PSR_F = 1 << 5,
  CR16C_PSR_Z = 1 << 6,
  CR16C_PSR_N = 1 << 7,
  CR16C_PSR_E = 1 << 9,
  CR16C_PSR_P = 1 << 10,
  CR16C_PSR_I = 1 << 11
} CR16CPsrType;

typedef enum
{
  CR16C_CFG_DC  = 1 << 2,
  CR16C_CFG_LDC = 1 << 3,
  CR16C_CFG_IC  = 1 << 4,
  CR16C_CFG_LIC = 1 << 5,
  CR16C_CFG_ED  = 1 << 8,
  CR16C_CFG_SR  = 1 << 9
} CR16CCfgType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

extern RS_ISRS_ADR RsIsrEntryType RsIsrs[];

/****************************************************************************
*                                Implementation
****************************************************************************/

#ifdef __NSC_CRCC__
// Cannot be inlined, compiler runs out of registers.
RsIntStatusType RsDisableInterrupts(void);
#else
RS_C_INLINE RsIntStatusType RsDisableInterrupts(void)
{
  register RsIntStatusType saved;
  _spr_("psr", saved);
  _di_();
  return saved;
}
#endif

RS_C_INLINE void RsEnableInterrupts(RsIntStatusType Saved)
{
  _lpr_("psr", Saved);
}

RS_C_INLINE unsigned char RsInterruptsEnabled(void)
{
  register RsIntStatusType saved;
  _spr_("psr", saved);
  return saved >> 9;
}

RS_C_INLINE RsRaType RsReturnAddress(void)
{
  register RsRaType RA asm("ra");
  return RA << 1;
}

void RsSetRA(RsRaType ra);

RS_C_INLINE void* RsGetSP(void)
{
  register void* p asm("sp");
  return p;
}

RS_C_INLINE void RsSetSP(void* sp)
{
  #if (RS_TOOL_ID == RSTI_GNU)
  register volatile void* volatile p asm("sp");
  #else
  register void* p asm("sp");
  #endif
  p = sp;
}

RS_C_INLINE void* RsGetISP(void)
{
  register void* p;
  _sprd_("isp", p);
  return p;
}

RS_C_INLINE void RsEiWait(void)
{
  _eiwait_();
}

RS_C_INLINE void RsDisableNesting(void)
{
  register unsigned short tpsr;
  _spr_("psr", tpsr);
  tpsr &= 0xf7ff;
  _lpr_("psr",tpsr);
}

RS_C_INLINE void RsEnableNesting(void)
{
  register unsigned short tpsr;
  _spr_("psr", tpsr);
  tpsr |= 0x0800;
  _lpr_("psr",tpsr);
  _ei_();
}

RS_C_INLINE void RsDisableIntsForced(void)
{
  _di_();
}

RS_C_INLINE void RsEnableIntsForced(void)
{
  _ei_();
}

RS_C_INLINE void RsDisableICache(void)
{
  register unsigned short saved;
  register unsigned short c;
  _spr_("psr", saved);
  _di_();
  _spr_("cfg", c);
  c &= ~CR16C_CFG_IC;
  _lpr_("cfg", c);
  _lpr_("psr", saved);
}

RS_C_INLINE void RsEnableICache(void)
{
  register unsigned short saved;
  register unsigned short c;
  _spr_("psr", saved);
  _di_();
  _spr_("cfg", c);
  c |= CR16C_CFG_IC;
  _lpr_("cfg", c);
  _lpr_("psr", saved);
}

RS_C_INLINE void RsDisableDCache(void)
{
  register unsigned short saved;
  register unsigned short c;
  _spr_("psr", saved);
  _di_();
  _spr_("cfg", c);
  c &= ~CR16C_CFG_DC;
  _lpr_("cfg", c);
  _lpr_("psr", saved);
}

RS_C_INLINE void RsEnableDCache(void)
{
  register unsigned short saved;
  register unsigned short c;
  _spr_("psr", saved);
  _di_();
  _spr_("cfg", c);
  c |= CR16C_CFG_DC;
  _lpr_("cfg", c);
  _lpr_("psr", saved);
}

typedef unsigned short RsCacheStatusType;

RS_C_INLINE RsCacheStatusType RsDisableCache(void)
{
  register unsigned short saved;
  register unsigned short c;
  _spr_("cfg", c);
  saved = c;
  #if (RS_INT_TABLE_WIDTH == RS_ITW_SHORT)
  c = 0;
  #else
  c &= ~(CR16C_CFG_IC | CR16C_CFG_DC);
  #endif
  _lpr_("cfg", c);
  return saved;
}

RS_C_INLINE void RsEnableCache(RsCacheStatusType Saved)
{
  _lpr_("cfg", Saved);
}

#define RsInvalidateICache() asm("cinv [i]")
#define RsInvalidateDCache() asm("cinv [d]")

RS_C_INLINE void fosMemcpy(unsigned char* destination, unsigned char* source, unsigned short size)
{
  memcpy(destination, source, (size_t)size);
}

RS_C_INLINE void fosMemset(unsigned char* destination, unsigned char set, unsigned short size)
{
  memset(destination, set, (size_t)size);
}

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#ifdef __NSC_CRCC__
#pragma interrupt(RsIntVecRes00)
#pragma interrupt(RsIntVecNmi01)
#pragma interrupt(RsIntVecRes02)
#pragma interrupt(RsIntVecRes03)
#pragma interrupt(RsIntVecRes04)
#pragma interrupt(RsIntVecSvc05)
#pragma interrupt(RsIntVecDvz06)
#pragma interrupt(RsIntVecFlg07)
#pragma interrupt(RsIntVecBpt08)
#pragma interrupt(RsIntVecTrc09)
#pragma interrupt(RsIntVecUnd10)
#pragma interrupt(RsIntVecRes11)
#pragma interrupt(RsIntVecIad12)
#pragma interrupt(RsIntVecRes13)
#pragma interrupt(RsIntVecDbg14)
#pragma interrupt(RsIntVecIse15)
#pragma interrupt(RsIntVec16)
#pragma interrupt(RsIntVec17)
#pragma interrupt(RsIntVec18)
#pragma interrupt(RsIntVec19)
#pragma interrupt(RsIntVec20)
#pragma interrupt(RsIntVec21)
#pragma interrupt(RsIntVec22)
#pragma interrupt(RsIntVec23)
#pragma interrupt(RsIntVec24)
#pragma interrupt(RsIntVec25)
#pragma interrupt(RsIntVec26)
#pragma interrupt(RsIntVec27)
#pragma interrupt(RsIntVec28)
#pragma interrupt(RsIntVec29)
#pragma interrupt(RsIntVec30)
#pragma interrupt(RsIntVec31)
#pragma interrupt(RsIntVec32)
#pragma interrupt(RsIntVec33)
#pragma interrupt(RsIntVec34)
#pragma interrupt(RsIntVec35)
#pragma interrupt(RsIntVec36)
#pragma interrupt(RsIntVec37)
#pragma interrupt(RsIntVec38)
#pragma interrupt(RsIntVec39)
#pragma interrupt(RsIntVec40)
#pragma interrupt(RsIntVec41)
#pragma interrupt(RsIntVec42)
#pragma interrupt(RsIntVec43)
#pragma interrupt(RsIntVec44)
#pragma interrupt(RsIntVec45)
#pragma interrupt(RsIntVec46)
#pragma interrupt(RsIntVec47)
#pragma interrupt(RsIntVec48)
#pragma interrupt(RsIntVec49)
#pragma interrupt(RsIntVec50)
#pragma interrupt(RsIntVec51)
#pragma interrupt(RsIntVec52)
#pragma interrupt(RsIntVec53)
#pragma interrupt(RsIntVec54)
#pragma interrupt(RsIntVec55)
#pragma interrupt(RsIntVec56)
#pragma interrupt(RsIntVec57)
#pragma interrupt(RsIntVec58)
#pragma interrupt(RsIntVec59)
#pragma interrupt(RsIntVec60)
#pragma interrupt(RsIntVec61)
#pragma interrupt(RsIntVec62)
#pragma interrupt(RsIntVec63)
#pragma interrupt(RsIntVec64)
#pragma interrupt(RsIntVec65)
#pragma interrupt(RsIntVec66)
#pragma interrupt(RsIntVec67)
#pragma interrupt(RsIntVec68)
#pragma interrupt(RsIntVec69)
#pragma interrupt(RsIntVec70)
#pragma interrupt(RsIntVec71)
#pragma interrupt(RsIntVec72)
#pragma interrupt(RsIntVec73)
#pragma interrupt(RsIntVec74)
#pragma interrupt(RsIntVec75)
#pragma interrupt(RsIntVec76)
#pragma interrupt(RsIntVec77)
#pragma interrupt(RsIntVec78)
#pragma interrupt(RsIntVec79)
#pragma interrupt(RsIntVec80)
#pragma interrupt(RsIntVec81)
#pragma interrupt(RsIntVec82)
#pragma interrupt(RsIntVec83)
#pragma interrupt(RsIntVec84)
#pragma interrupt(RsIntVec85)
#pragma interrupt(RsIntVec86)

void RsIntVecRes00(void);
void RsIntVecNmi01(void);
void RsIntVecRes02(void);
void RsIntVecRes03(void);
void RsIntVecRes04(void);
void RsIntVecSvc05(void);
void RsIntVecDvz06(void);
void RsIntVecFlg07(void);
void RsIntVecBpt08(void);
void RsIntVecTrc09(void);
void RsIntVecUnd10(void);
void RsIntVecRes11(void);
void RsIntVecIad12(void);
void RsIntVecRes13(void);
void RsIntVecDbg14(void);
void RsIntVecIse15(void);
void RsIntVec16(void);
void RsIntVec17(void);
void RsIntVec18(void);
void RsIntVec19(void);
void RsIntVec20(void);
void RsIntVec21(void);
void RsIntVec22(void);
void RsIntVec23(void);
void RsIntVec24(void);
void RsIntVec25(void);
void RsIntVec26(void);
void RsIntVec27(void);
void RsIntVec28(void);
void RsIntVec29(void);
void RsIntVec30(void);
void RsIntVec31(void);
void RsIntVec32(void);
void RsIntVec33(void);
void RsIntVec34(void);
void RsIntVec35(void);
void RsIntVec36(void);
void RsIntVec37(void);
void RsIntVec38(void);
void RsIntVec39(void);
void RsIntVec40(void);
void RsIntVec41(void);
void RsIntVec42(void);
void RsIntVec43(void);
void RsIntVec44(void);
void RsIntVec45(void);
void RsIntVec46(void);
void RsIntVec47(void);
void RsIntVec48(void);
void RsIntVec49(void);
void RsIntVec50(void);
void RsIntVec51(void);
void RsIntVec52(void);
void RsIntVec53(void);
void RsIntVec54(void);
void RsIntVec55(void);
void RsIntVec56(void);
void RsIntVec57(void);
void RsIntVec58(void);
void RsIntVec59(void);
void RsIntVec60(void);
void RsIntVec61(void);
void RsIntVec62(void);
void RsIntVec63(void);
void RsIntVec64(void);
void RsIntVec65(void);
void RsIntVec66(void);
void RsIntVec67(void);
void RsIntVec68(void);
void RsIntVec69(void);
void RsIntVec70(void);
void RsIntVec71(void);
void RsIntVec72(void);
void RsIntVec73(void);
void RsIntVec74(void);
void RsIntVec75(void);
void RsIntVec76(void);
void RsIntVec77(void);
void RsIntVec78(void);
void RsIntVec79(void);
void RsIntVec80(void);
void RsIntVec81(void);
void RsIntVec82(void);
void RsIntVec83(void);
void RsIntVec84(void);
void RsIntVec85(void);
void RsIntVec86(void);
#endif

#ifndef __NSC_CRCC__
void RsIntVecRes00(void) __attribute__((interrupt));
void RsIntVecNmi01(void) __attribute__((interrupt));
void RsIntVecRes02(void) __attribute__((interrupt));
void RsIntVecRes03(void) __attribute__((interrupt));
void RsIntVecRes04(void) __attribute__((interrupt));
void RsIntVecSvc05(void) __attribute__((interrupt));
void RsIntVecDvz06(void) __attribute__((interrupt));
void RsIntVecFlg07(void) __attribute__((interrupt));
void RsIntVecBpt08(void) __attribute__((interrupt));
void RsIntVecTrc09(void) __attribute__((interrupt));
void RsIntVecUnd10(void) __attribute__((interrupt));
void RsIntVecRes11(void) __attribute__((interrupt));
void RsIntVecIad12(void) __attribute__((interrupt));
void RsIntVecRes13(void) __attribute__((interrupt));
void RsIntVecDbg14(void) __attribute__((interrupt));
void RsIntVecIse15(void) __attribute__((interrupt));
void RsIntVec16(void) __attribute__((interrupt));
void RsIntVec17(void) __attribute__((interrupt));
void RsIntVec18(void) __attribute__((interrupt));
void RsIntVec19(void) __attribute__((interrupt));
void RsIntVec20(void) __attribute__((interrupt));
void RsIntVec21(void) __attribute__((interrupt));
void RsIntVec22(void) __attribute__((interrupt));
void RsIntVec23(void) __attribute__((interrupt));
void RsIntVec24(void) __attribute__((interrupt));
void RsIntVec25(void) __attribute__((interrupt));
void RsIntVec26(void) __attribute__((interrupt));
void RsIntVec27(void) __attribute__((interrupt));
void RsIntVec28(void) __attribute__((interrupt));
void RsIntVec29(void) __attribute__((interrupt));
void RsIntVec30(void) __attribute__((interrupt));
void RsIntVec31(void) __attribute__((interrupt));
void RsIntVec32(void) __attribute__((interrupt));
void RsIntVec33(void) __attribute__((interrupt));
void RsIntVec34(void) __attribute__((interrupt));
void RsIntVec35(void) __attribute__((interrupt));
void RsIntVec36(void) __attribute__((interrupt));
void RsIntVec37(void) __attribute__((interrupt));
void RsIntVec38(void) __attribute__((interrupt));
void RsIntVec39(void) __attribute__((interrupt));
void RsIntVec40(void) __attribute__((interrupt));
void RsIntVec41(void) __attribute__((interrupt));
void RsIntVec42(void) __attribute__((interrupt));
void RsIntVec43(void) __attribute__((interrupt));
void RsIntVec44(void) __attribute__((interrupt));
void RsIntVec45(void) __attribute__((interrupt));
void RsIntVec46(void) __attribute__((interrupt));
void RsIntVec47(void) __attribute__((interrupt));
void RsIntVec48(void) __attribute__((interrupt));
void RsIntVec49(void) __attribute__((interrupt));
void RsIntVec50(void) __attribute__((interrupt));
void RsIntVec51(void) __attribute__((interrupt));
void RsIntVec52(void) __attribute__((interrupt));
void RsIntVec53(void) __attribute__((interrupt));
void RsIntVec54(void) __attribute__((interrupt));
void RsIntVec55(void) __attribute__((interrupt));
void RsIntVec56(void) __attribute__((interrupt));
void RsIntVec57(void) __attribute__((interrupt));
void RsIntVec58(void) __attribute__((interrupt));
void RsIntVec59(void) __attribute__((interrupt));
void RsIntVec60(void) __attribute__((interrupt));
void RsIntVec61(void) __attribute__((interrupt));
void RsIntVec62(void) __attribute__((interrupt));
void RsIntVec63(void) __attribute__((interrupt));
void RsIntVec64(void) __attribute__((interrupt));
void RsIntVec65(void) __attribute__((interrupt));
void RsIntVec66(void) __attribute__((interrupt));
void RsIntVec67(void) __attribute__((interrupt));
void RsIntVec68(void) __attribute__((interrupt));
void RsIntVec69(void) __attribute__((interrupt));
void RsIntVec70(void) __attribute__((interrupt));
void RsIntVec71(void) __attribute__((interrupt));
void RsIntVec72(void) __attribute__((interrupt));
void RsIntVec73(void) __attribute__((interrupt));
void RsIntVec74(void) __attribute__((interrupt));
void RsIntVec75(void) __attribute__((interrupt));
void RsIntVec76(void) __attribute__((interrupt));
void RsIntVec77(void) __attribute__((interrupt));
void RsIntVec78(void) __attribute__((interrupt));
void RsIntVec79(void) __attribute__((interrupt));
void RsIntVec80(void) __attribute__((interrupt));
void RsIntVec81(void) __attribute__((interrupt));
void RsIntVec82(void) __attribute__((interrupt));
void RsIntVec83(void) __attribute__((interrupt));
void RsIntVec84(void) __attribute__((interrupt));
void RsIntVec85(void) __attribute__((interrupt));
void RsIntVec86(void) __attribute__((interrupt));
#endif

void RsIsr00(void);
void RsIsr01(void);
void RsIsr02(void);
void RsIsr03(void);
void RsIsr04(void);
void RsIsr05(void);
void RsIsr06(void);
void RsIsr07(void);
void RsIsr08(void);
void RsIsr09(void);
void RsIsr10(void);
void RsIsr11(void);
void RsIsr12(void);
void RsIsr13(void);
void RsIsr14(void);
void RsIsr15(void);
void RsIsr16(void);
void RsIsr17(void);
void RsIsr18(void);
void RsIsr19(void);
void RsIsr20(void);
void RsIsr21(void);
void RsIsr22(void);
void RsIsr23(void);
void RsIsr24(void);
void RsIsr25(void);
void RsIsr26(void);
void RsIsr27(void);
void RsIsr28(void);
void RsIsr29(void);
void RsIsr30(void);
void RsIsr31(void);
void RsIsr32(void);
void RsIsr33(void);
void RsIsr34(void);
void RsIsr35(void);
void RsIsr36(void);
void RsIsr37(void);
void RsIsr38(void);
void RsIsr39(void);
void RsIsr40(void);
void RsIsr41(void);
void RsIsr42(void);
void RsIsr43(void);
void RsIsr44(void);
void RsIsr45(void);
void RsIsr46(void);
void RsIsr47(void);
void RsIsr48(void);
void RsIsr49(void);
void RsIsr50(void);
void RsIsr51(void);
void RsIsr52(void);
void RsIsr53(void);
void RsIsr54(void);
void RsIsr55(void);
void RsIsr56(void);
void RsIsr57(void);
void RsIsr58(void);
void RsIsr59(void);
void RsIsr60(void);
void RsIsr61(void);
void RsIsr62(void);
void RsIsr63(void);
void RsIsr64(void);
void RsIsr65(void);
void RsIsr66(void);
void RsIsr67(void);
void RsIsr68(void);
void RsIsr69(void);
void RsIsr70(void);
void RsIsr71(void);
void RsIsr72(void);
void RsIsr73(void);
void RsIsr74(void);
void RsIsr75(void);
void RsIsr76(void);
void RsIsr77(void);
void RsIsr78(void);
void RsIsr79(void);
void RsIsr80(void);
void RsIsr81(void);
void RsIsr82(void);
void RsIsr83(void);
void RsIsr84(void);
void RsIsr85(void);
void RsIsr86(void);
/** \endcond */

#ifdef __cplusplus
}
#endif

#endif

// End of file.

