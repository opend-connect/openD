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
* CR16C/IAR specific types and macros.
*
* \section isr_table Interrupt Service Routines
*
* The Core installs the interrupt vector table. Each entry in the table points
* to a Core function, which saves the current execution context, swithes to the interrupt stack
* and calls a function (prototype \ref RsIsrType "RsIsrType")  from a application-defined interrupt service routine dispatch table.
* Upon return from the interrupt service routine, the Core switches to the appropriate execution context.
*
* The following is a sample ISR table for a SC14428.
* It uses the default ISR's for the first 16 vectors, and directs the CT interrupt to CtIsr and TIMER1 interrupt to the Timer1Isr.
*
* \code
* RS_ISRS_ADR RsIsrEntryType RsIsrs[] =
* {
*   RsIsr00,    // Reserved
*   RsIsr01,    // NMI
*   RsIsr02,    // Reserved
*   RsIsr03,    // Reserved
*   RsIsr04,    // Reserved
*   RsIsr05,    // SVC
*   RsIsr06,    // DVZ
*   RsIsr07,    // FLG
*   RsIsr08,    // BPT
*   RsIsr09,    // TRC
*   RsIsr10,    // UND
*   RsIsr11,    // Reserved
*   RsIsr12,    // Illegal address
*   RsIsr13,    // Reserved
*   RsIsr14,    // DBG
*   RsIsr15,    // ISE
*   RsIsr16,    // ACCESS_INT
*   RsIsr17,    // KEYBRD
*   RsIsr18,    // P10
*   CtIsr,      // CT
*   RsIsr20,    // UART_RI
*   RsIsr21,    // UART TI
*   RsIsr22,    // SPI
*   RsIsr23,    // TIM0
*   Timer1Isr,  // TIM1
*   RsIsr25,    // CLK100
*   RsIsr26,    // DIP
*   RsIsr27,    // DSP
* };
* \endcode
*
* \section cr16c_swiisr CR16C SWI ISR
*
* \ref fos_Software_Interrupts requires the use of a hardware interrupt vector, and the application
* must implement the \c fosSwiTrap() function for activating the interrupt, and also the ISR for handling it.
* Fusion uses SWI's internally to perform context switched and handle timer ticks, so the application must support SWI's
* even it it doesnt itself create or use SWI's.
*
* The specific vector used is not important, it can be any vector that the application doesnt use for other purposes.
* The application must enable the interrupt during startyp (typically done in \ref RsHookReady). The priority should be set to the lowest of all hardware interrupts.
*
* The following is the \c fosSwiTrap() function for a SC14428, using the CT interrupt for SWI's:
* \code
* void fosSwiTrap(void)
* {
*   SET_INT_PENDING_REG = CT_INT_PEND;
* }
* \endcode
*
* The following is the ISR function for a SC14428, using the CT interrupt for SWI's:
* \code
* RSISR(CtIsr)
* {
*   RESET_INT_PENDING_REG = CT_INT_PEND;
*   fosSwiDispatch(0);
* }
* \endcode
*
* Same example, but using nested interrupts:
* \code
* RSISR(CtIsr)
* {
*   INT2_PRIORITY_REG_bit.CT_INT_PRIO = 0;
*   RsEnableNesting();
*   RESET_INT_PENDING_REG = CT_INT_PEND;
*   fosSwiDispatch(0);
*   RsDisableNesting();
*   INT2_PRIORITY_REG_bit.CT_INT_PRIO = 1;
* }
* \endcode
*
* \section cr16c_stacks CR16C Stacks
*
* \subsection cr16c_istack ISTACK
*
* The CR16C uses the ISTACK (pointed to by the \c ISP register) for saving status when an interrupt or exception/trap occurs.
* The information saved includes the \c PC and the \c PSR i.e., 6 bytes for one ISTACK \em slot.
* When the application doesnt use nesting of interrupts, the ISTACK can be very small.
* In theory it only needs to have space for one hardware interrupt, but one extra slot should be reserved in case an exception occurs in the ISR.
* Furthermore, there is a possibility that the NMI (watchdog) fires, so a spare slot is allocated. I.e., the minimum ISTACK size is 18 bytes (3 slots of 6 bytes).
* When the application uses nesting of interrupts, further slots must be reserved for the worst case when all interrupts nest upon each other.
*
* The ISTACK calculation is given in the following equation:
* \code
* ISTACK size = (number of nesting interrupts + 3) * 6 bytes
* \endcode
*
* The ISTACK area is filled with 0xEE during system startup.
*
* \subsection cr16c_cstack CSTACK
*
* The CSTACK is used for the background/idle task and all ISR's.
*
* A calculation method is not currently available, but the CSTACK should be at least 0xE0 bytes.
*
* The CSTACK area is filled with 0xAA during system startup, and the magic value 0xDEADBEEF is placed
* at the end of the stack, used for detecting overflow at runtime.
*
* \subsection cr16c_taskstack Task Stacks
*
* A task's stack needs to have space for local variables and parameters for functions called (i.e., the task's call tree).
* The Fusion RTOS uses 42 bytes on the task's stack to save the current task's context when another task is activated.
*
* A calculation method is not currently available, but a task's stack should be at least 0x50 bytes.
*
* A task stack is filled with 0xAA when the task is created, and the magic value 0xDEADBEEF is placed
* at the end of the stack, used for detecting overflow at runtime.
*
* <hr>
*
*/


#ifndef RS_TARGET_INC_H
#define RS_TARGET_INC_H

/****************************************************************************
*                               Include files
****************************************************************************/

#if (RS_SYSHEADERS == 1)
  #ifdef _DLIB_CONFIG_FILE
    #include <string.h>
    #include <stddef.h>
  #else
    #ifdef __cplusplus
    extern "C"
    {
      #include <string.h>
    }
    #else
      #include <string.h>
    #endif
    #include <clib/sysmac.h>
  #endif
#endif
#if (RS_SYSHEADERS == 0)
  #include <RsSysHeaders.h>
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \cond internal */
#ifdef __KLOCWORK__
  #define __data32
  #define __data24
  #define asm(a)
  #define RS_RAM_ADR
  #define RS_C_INLINE
#endif
/** \endcond */

// IAR's NULL definition is not C++ compatible => Use the one in RsStandard.h.
#undef NULL

/** \name Function/variable Macros
* Macros for modifying the default signature and placement of functions and variables. */
//@{
#if (__DATA_MODEL__ == __DATA_MODEL_SMALL__ || __DATA_MODEL__ == __DATA_MODEL_INDEXED__)
  typedef unsigned short rsuintsz;
#endif
#if (__DATA_MODEL__ == __DATA_MODEL_MEDIUM__ || __DATA_MODEL__ == __DATA_MODEL_LARGE__)
  typedef unsigned long rsuintsz;  /*!< 16-bit or 32-bit unsigned quantity, depending on data model. */
#endif
#if (__IAR_SYSTEMS_ICC__ < 7)
  #define RS_FAR_ADR __data24        /*!< Places variables and constants in far memory. */
#else
  #define RS_FAR_ADR __data32        /*!< Places variables and constants in far memory. */
#endif
#define RS_NEAR_ADR __data16       /*!< Places variables and constants in near memory. */
#ifndef RS_RAM_ADR
  #define RS_RAM_ADR @ "RAMCODE"     /*!< Places functions in RAM (instead of ROM/flash). */
#endif
#define RS_RAM_ATTR                /*!< Places functions in RAM (instead of ROM/flash). */
#define RS_NO_INIT __no_init       /*!< Surpresses initialization of variables. */
#define RS_ROOT_SYMBOL __root      /*!< Ensures that a function or variable is included in the object code even if unused. */
#define RS_NOP asm("nop")          /*!< Inserts no operation instruction. */
#define RS_NAKED __task            /*!< Prevent compiler from generating prologue/epilogue sequences for a function. */
#define RS_NORETURN __noreturn     /*!< Inform compiler that a function will never return. */
//@}

/*! \name Breakpoint
* Halts the program in the debugger.
*/
//@{
#define RS_BREAKPOINT asm("excp bpt") /*!< Halts the program in the debugger. */
//@}

#if (RS_RTOS_ID == RSTS_FUSION) || (RS_HOOK_PRE_HWI == 1)
  #define RSISR(fn) void fn(void) /*!< Declare interrupt service routine. Example: RSISR(Timer1Isr)  */
#else
  #define RSISR(fn) __interrupt void fn(void)
#endif

/** \cond internal */

#define RS_QUOTEa(x) #x
#define RS_QUOTEb(x) RS_QUOTEa(x)

#ifndef RS_FASTCODE_ADR
  #ifdef RS_FASTCODE_SEG
    #define RS_FASTCODE_ADR @ RS_QUOTEb(RS_FASTCODE_SEG)
  #else
    #define RS_FASTCODE_ADR
  #endif
#endif

#define __INTRINSICS_H // Prevent casual inclusion of intrinsics.h
__intrinsic void RS_FAR_ADR * __memcpy_generic(void RS_FAR_ADR *, void RS_FAR_ADR const *, long);
__intrinsic void RS_FAR_ADR * __memset_generic(void RS_FAR_ADR *, int, long);
#if (__DATA_MODEL__ == __DATA_MODEL_SMALL__)
  #define memcpy __memcpy_generic
#endif

#define RSOFFSETOF(type, field) (__INTADDR__((&((type*)0)->field)))

#define RS_AUTOSIZE_ENUMS

#ifdef RS_SET_PACKING
  #pragma pack(RS_SET_PACKING)
#endif

#if (__IAR_SYSTEMS_ICC__ >= 8)
  #define RS_ENABLE_INT64
#endif

#define RS_OVERRIDE_INTERRUPTS

#ifndef RS_C_INLINE
  #if (__IAR_SYSTEMS_ICC__ > 5)
    #define RS_C_INLINE _Pragma("inline=forced")
  #endif
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef enum
{
  CR16C_REG_R0 = 0,
  CR16C_REG_R1,
  CR16C_REG_R2,
  CR16C_REG_R3,
  CR16C_REG_R4,
  CR16C_REG_R5,
  CR16C_REG_R6,
  CR16C_REG_R7,
  CR16C_REG_R8,
  CR16C_REG_R9,
  CR16C_REG_R10,
  CR16C_REG_R11,
  CR16C_REG_R12,
  CR16C_REG_R13,
  CR16C_REG_RA,
  CR16C_REG_SP,
  CR16C_REG_PSR = 0x100,
  CR16C_REG_CFG,
  CR16C_REG_INTB,
  CR16C_REG_ISP,
  CR16C_REG_USP,
  CR16C_REG_DSR,
  CR16C_REG_DCR
} CR16CRegType;

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

/** \endcond */

/// For saving interrupt status, returned from \ref RsDisableInterrupts.
typedef unsigned long RsIntStatusType;

#pragma inline=forced
RsIntStatusType RsDisableInterrupts(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  RsIntStatusType saved = __get_processor_register(CR16C_REG_PSR);
  asm("di");
  #ifndef __CR16CP__
  RS_NOP;
  #endif
  return saved;
}

#pragma inline=forced
void RsEnableInterrupts(RsIntStatusType Saved)
{
  __intrinsic void __set_processor_register(int, unsigned long);
  __set_processor_register(CR16C_REG_PSR, Saved);
  #ifndef __CR16CP__
  RS_NOP;
  #endif
}

#pragma inline=forced
unsigned char RsInterruptsEnabled(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  unsigned short saved = __get_processor_register(CR16C_REG_PSR);
  return saved >> 9;
}

typedef unsigned long RsRaType; /*!< Return address. */

#pragma inline=forced
/// Get return address of the current function i.e. the address after the branch/call/jump instruction.
/** \return Return address. */
RsRaType RsReturnAddress(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  return __get_processor_register(CR16C_REG_RA) << 1;
}

/** \cond internal */

#pragma inline=forced
void RsSetRA(RsRaType ra)
{
  __intrinsic void __set_processor_register(int, unsigned long);
  __set_processor_register(CR16C_REG_RA, (ra >> 1));
}

#pragma inline=forced
void* RsGetSP(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  return (void*)(ptrdiff_t)__get_processor_register(CR16C_REG_SP);
}

#pragma inline=forced
void RsSetSP(void* sp)
{
  __intrinsic void __set_processor_register(int, unsigned long);
  __set_processor_register(CR16C_REG_SP, (unsigned long)(sp));
}

#pragma inline=forced
void* RsGetISP(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  return (void*)(ptrdiff_t)__get_processor_register(CR16C_REG_ISP);
}

#pragma inline=forced
void RsEiWait(void)
{
  asm("eiwait");
}

#pragma inline=forced
void RsDisableNesting(void)
{
  __intrinsic void __clear_PSR_I_bit(void);
  __clear_PSR_I_bit();
}

#pragma inline=forced
void RsEnableNesting(void)
{
  __intrinsic void __set_PSR_I_bit(void);
  __set_PSR_I_bit();
  asm("ei");
  #ifndef __CR16CP__
  RS_NOP;
  #endif
}

#pragma inline=forced
void RsDisableIntsForced(void)
{
  asm("di");
  #ifndef __CR16CP__
  RS_NOP;
  #endif
}

#pragma inline=forced
void RsEnableIntsForced(void)
{
  asm("ei");
  #ifndef __CR16CP__
  RS_NOP;
  #endif
}

#pragma inline=forced
void RsDisableICache(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  __intrinsic void __set_processor_register(int, unsigned long);
  unsigned long saved = __get_processor_register(CR16C_REG_PSR);
  asm("di");
  #ifndef __CR16CP__
  RS_NOP;
  #endif
  __set_processor_register(CR16C_REG_CFG, __get_processor_register(CR16C_REG_CFG) & (unsigned long)~CR16C_CFG_IC);
  __set_processor_register(CR16C_REG_PSR, saved);
  #ifndef __CR16CP__
  RS_NOP;
  #endif
}

#pragma inline=forced
void RsEnableICache(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  __intrinsic void __set_processor_register(int, unsigned long);
  unsigned long saved = __get_processor_register(CR16C_REG_PSR);
  asm("di");
  #ifndef __CR16CP__
  RS_NOP;
  #endif
  __set_processor_register(CR16C_REG_CFG, __get_processor_register(CR16C_REG_CFG) | CR16C_CFG_IC);
  __set_processor_register(CR16C_REG_PSR, saved);
  #ifndef __CR16CP__
  RS_NOP;
  #endif
}

#pragma inline=forced
void RsDisableDCache(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  __intrinsic void __set_processor_register(int, unsigned long);
  unsigned long saved = __get_processor_register(CR16C_REG_PSR);
  asm("di");
  #ifndef __CR16CP__
  RS_NOP;
  #endif
  __set_processor_register(CR16C_REG_CFG, __get_processor_register(CR16C_REG_CFG) & (unsigned long)~CR16C_CFG_DC);
  __set_processor_register(CR16C_REG_PSR, saved);
  #ifndef __CR16CP__
  RS_NOP;
  #endif
}

#pragma inline=forced
void RsEnableDCache(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  __intrinsic void __set_processor_register(int, unsigned long);
  unsigned long saved = __get_processor_register(CR16C_REG_PSR);
  asm("di");
  #ifndef __CR16CP__
  RS_NOP;
  #endif
  __set_processor_register(CR16C_REG_CFG, __get_processor_register(CR16C_REG_CFG) | CR16C_CFG_DC);
  __set_processor_register(CR16C_REG_PSR, saved);
  #ifndef __CR16CP__
  RS_NOP;
  #endif
}

/// For saving cache status, returned from \ref RsDisableCache.
typedef unsigned short RsCacheStatusType;

#pragma inline=forced
RsCacheStatusType RsDisableCache(void)
{
  __intrinsic unsigned long __get_processor_register(int);
  __intrinsic void __set_processor_register(int, unsigned long);
  unsigned long saved = __get_processor_register(CR16C_REG_CFG);
  #if (RS_INT_TABLE_WIDTH == RS_ITW_SHORT)
  __set_processor_register(CR16C_REG_CFG, 0);
  #else
  __set_processor_register(CR16C_REG_CFG, saved & (unsigned long)~(CR16C_CFG_IC | CR16C_CFG_DC));
  #endif
  return (RsCacheStatusType)saved;
}

#pragma inline=forced
void RsEnableCache(RsCacheStatusType Saved)
{
  __intrinsic void __set_processor_register(int, unsigned long);
  __set_processor_register(CR16C_REG_CFG, Saved);
}

#define RsInvalidateICache() asm("cinv [i]")
#define RsInvalidateDCache() asm("cinv [d]")

#pragma inline=forced
#ifdef __cplusplus
extern "C"
#endif
void fosMemcpy(unsigned char* destination, unsigned char* source, unsigned short size)
{
  memcpy(destination, source, size);
}

#pragma inline=forced
#ifdef __cplusplus
extern "C"
#endif
void fosMemset(unsigned char* destination, unsigned char set, unsigned short size)
{
  memset(destination, set, size);
}

/** \endcond */

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/// Vector table entries.
typedef __interrupt void RsIntVecType(void);

/// Prototype for interrupt service routines.
typedef void RsIsrType(void);

/// ISR table entries.
typedef struct
{
  RsIsrType* Isr; /*!< Interrupt Service Routine. */
} RsIsrEntryType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/// Interrupt service routine dispatch table.
extern RS_ISRS_ADR RsIsrEntryType RsIsrs[];

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/** \cond internal */

/// Reserved 0 interrupt vector.
__interrupt void RsIntVecRes00(void);

/// Non-Maskable interrupt vector.
__interrupt void RsIntVecNmi01(void);

/// Reserved 2 interrupt vector.
__interrupt void RsIntVecRes02(void);

/// Reserved 3 interrupt vector.
__interrupt void RsIntVecRes03(void);

/// Reserved 4 interrupt vector.
__interrupt void RsIntVecRes04(void);

/// Supervisor Call trap vector.
__interrupt void RsIntVecSvc05(void);

/// Divide by Zero trap vector.
__interrupt void RsIntVecDvz06(void);

/// Flag trap vector.
__interrupt void RsIntVecFlg07(void);

/// Breakpoint trap vector.
__interrupt void RsIntVecBpt08(void);

/// Trace trap vector.
__interrupt void RsIntVecTrc09(void);

/// Undefined Instruction trap vector.
__interrupt void RsIntVecUnd10(void);

/// Reserved 11 interrupt vector.
__interrupt void RsIntVecRes11(void);

/// Illegal Address trap vector.
__interrupt void RsIntVecIad12(void);

/// Reserved 13 interrupt vector.
__interrupt void RsIntVecRes13(void);

/// Debug trap vector.
__interrupt void RsIntVecDbg14(void);

/// In-System Emulator interrupt vector.
__interrupt void RsIntVecIse15(void);

/// Device interrupt vectors.
__interrupt void RsIntVec16(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec17(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec18(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec19(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec20(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec21(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec22(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec23(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec24(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec25(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec26(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec27(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec28(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec29(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec30(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec31(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec32(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec33(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec34(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec35(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec36(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec37(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec38(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec39(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec40(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec41(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec42(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec43(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec44(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec45(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec46(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec47(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec48(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec49(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec50(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec51(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec52(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec53(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec54(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec55(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec56(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec57(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec58(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec59(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec60(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec61(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec62(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec63(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec64(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec65(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec66(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec67(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec68(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec69(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec70(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec71(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec72(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec73(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec74(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec75(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec76(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec77(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec78(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec79(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec80(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec81(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec82(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec83(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec84(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec85(void) RS_FASTCODE_ADR;
__interrupt void RsIntVec86(void) RS_FASTCODE_ADR;

/// Device interrupt service routines.
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

