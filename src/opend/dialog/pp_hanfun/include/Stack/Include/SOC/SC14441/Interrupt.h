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

#ifndef INTERRUPT_H
#define INTERRUPT_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Interrup.h>

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

#define ACCESS12_VECTOR_NR 16
#define KEYB_VECTOR_NR 17
#define UART2_RI_TI_VECTOR_NR 18
#define CT_CLASSD_VECTOR_NR 19
#define UART_RI_VECTOR_NR 20
#define UART_TI_VECTOR_NR 21
#define SPI_VECTOR_NR 22
#define TIM0_VECTOR_NR 23
#define TIM1_VECTOR_NR 24
#define CLK100_VECTOR_NR 25
#define DIP_VECTOR_NR 26
#define AD_VECTOR_NR 27
#define SPI2_VECTOR_NR 28
#define DSP_VECTOR_NR 29
#define ULP_VECTOR_NR 30

#if (RS_RTOS_ID == RSTS_FUSION) || (RS_HOOK_PRE_HWI == 1)
  #define DEFAULT_INTERRUPT_HANDLER(v) RsIsr##v
#else
  #define DEFAULT_INTERRUPT_HANDLER(v) RsIntVec##v
#endif

#ifndef ACCESS12_INTERRUPT_HANDLER
  #define ACCESS12_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(16)
#endif
#ifndef KEYB_INTERRUPT_HANDLER
  #define KEYB_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(17)
#endif
#ifndef UART2_RI_TI_INTERRUPT_HANDLER
  #define UART2_RI_TI_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(18)
#endif
#ifndef CT_CLASSD_INTERRUPT_HANDLER
  #define CT_CLASSD_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(19)
#endif
#ifndef UART_RI_INTERRUPT_HANDLER
  #define UART_RI_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(20)
#endif
#ifndef UART_TI_INTERRUPT_HANDLER
  #define UART_TI_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(21)
#endif
#ifndef SPI_INTERRUPT_HANDLER
  #define SPI_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(22)
#endif
#ifndef TIM0_INTERRUPT_HANDLER
  #define TIM0_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(23)
#endif
#ifndef TIM1_INTERRUPT_HANDLER
  #define TIM1_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(24)
#endif
#ifndef CLK100_INTERRUPT_HANDLER
  #define CLK100_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(25)
#endif
#ifndef DIP_INTERRUPT_HANDLER
  #define DIP_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(26)
#endif
#ifndef AD_INTERRUPT_HANDLER
  #define AD_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(27)
#endif
#ifndef SPI2_INTERRUPT_HANDLER
  #define SPI2_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(28)
#endif
#ifndef DSP_INTERRUPT_HANDLER
  #define DSP_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(29)
#endif
#ifndef ULP_INTERRUPT_HANDLER
  #define ULP_INTERRUPT_HANDLER DEFAULT_INTERRUPT_HANDLER(30)
#endif

/****************************************************************************
*                        Interrupt priority control macros
****************************************************************************/

#ifndef RSISR
  #define RSISR(fn) void fn(rsuint8 Vector)
#endif
RS_BEGIN_EXTERN_C
RSISR(ACCESS12_INTERRUPT_HANDLER);
RSISR(KEYB_INTERRUPT_HANDLER);
RSISR(UART2_RI_TI_INTERRUPT_HANDLER);
RSISR(CT_CLASSD_INTERRUPT_HANDLER);
RSISR(UART_RI_INTERRUPT_HANDLER);
RSISR(UART_TI_INTERRUPT_HANDLER);
RSISR(SPI_INTERRUPT_HANDLER);
RSISR(TIM0_INTERRUPT_HANDLER);
RSISR(TIM1_INTERRUPT_HANDLER);
RSISR(CLK100_INTERRUPT_HANDLER);
RSISR(DIP_INTERRUPT_HANDLER);
RSISR(AD_INTERRUPT_HANDLER);
RSISR(SPI2_INTERRUPT_HANDLER);
RSISR(DSP_INTERRUPT_HANDLER);
RSISR(ULP_INTERRUPT_HANDLER);
RS_END_EXTERN_C

#define SET_ACCESS12_INT_PRIO(prio)     { RsIntStatusType saved = RsDisableInterrupts(); INT3_PRIORITY_REG_bit.ACCESS_INT_PRIO = prio;      RsEnableInterrupts(saved); }
#define SET_KEYB_INT_PRIO(prio)         { RsIntStatusType saved = RsDisableInterrupts(); INT3_PRIORITY_REG_bit.KEYB_INT_PRIO = prio;        RsEnableInterrupts(saved); }
#define SET_UART2_RI_TI_INT_PRIO(prio)  { RsIntStatusType saved = RsDisableInterrupts(); INT3_PRIORITY_REG_bit.UART2_RI_TI_INT_PRIO = prio; RsEnableInterrupts(saved); }
#define SET_CT_CLASSD_INT_PRIO(prio)    { RsIntStatusType saved = RsDisableInterrupts(); INT3_PRIORITY_REG_bit.CT_CLASSD_INT_PRIO = prio;   RsEnableInterrupts(saved); }
#define SET_UART_RI_INT_PRIO(prio)      { RsIntStatusType saved = RsDisableInterrupts(); INT2_PRIORITY_REG_bit.UART_RI_INT_PRIO = prio;     RsEnableInterrupts(saved); }
#define SET_UART_TI_INT_PRIO(prio)      { RsIntStatusType saved = RsDisableInterrupts(); INT2_PRIORITY_REG_bit.UART_TI_INT_PRIO = prio;     RsEnableInterrupts(saved); }
#define SET_SPI_INT_PRIO(prio)          { RsIntStatusType saved = RsDisableInterrupts(); INT2_PRIORITY_REG_bit.SPI_INT_PRIO = prio;         RsEnableInterrupts(saved); }
#define SET_TIM0_INT_PRIO(prio)         { RsIntStatusType saved = RsDisableInterrupts(); INT2_PRIORITY_REG_bit.TIM0_INT_PRIO = prio;        RsEnableInterrupts(saved); }
#define SET_TIM1_INT_PRIO(prio)         { RsIntStatusType saved = RsDisableInterrupts(); INT1_PRIORITY_REG_bit.TIM1_INT_PRIO = prio;        RsEnableInterrupts(saved); }
#define SET_CLK100_INT_PRIO(prio)       { RsIntStatusType saved = RsDisableInterrupts(); INT1_PRIORITY_REG_bit.CLK100_INT_PRIO = prio;      RsEnableInterrupts(saved); }
#define SET_DIP_INT_PRIO(prio)          { RsIntStatusType saved = RsDisableInterrupts(); INT1_PRIORITY_REG_bit.DIP_INT_PRIO = prio;         RsEnableInterrupts(saved); }
#define SET_AD_INT_PRIO(prio)           { RsIntStatusType saved = RsDisableInterrupts(); INT1_PRIORITY_REG_bit.AD_INT_PRIO = prio;          RsEnableInterrupts(saved); }
#define SET_SPI2_INT_PRIO(prio)         { RsIntStatusType saved = RsDisableInterrupts(); INT0_PRIORITY_REG_bit.SPI2_INT_PRIO = prio;        RsEnableInterrupts(saved); }
#define SET_DSP_INT_PRIO(prio)          { RsIntStatusType saved = RsDisableInterrupts(); INT0_PRIORITY_REG_bit.DSP_INT_PRIO = prio;         RsEnableInterrupts(saved); }
#define SET_ULP_INT_PRIO(prio)          { RsIntStatusType saved = RsDisableInterrupts(); INT0_PRIORITY_REG_bit.ULP_INT_PRIO = prio;         RsEnableInterrupts(saved); }

#define CLEAR_PENDING_ACCESS12_INTERRUPT    RESET_INT_PENDING_REG = ACCESS_INT_PEND
#define CLEAR_PENDING_KEYB_INTERRUPT        RESET_INT_PENDING_REG = KEYB_INT_PEND
#define CLEAR_PENDING_UART2_RI_TI_INTERRUPT RESET_INT_PENDING_REG = UART2_RI_TI_INT_PEND
#define CLEAR_PENDING_CT_CLASSD_INTERRUPT   RESET_INT_PENDING_REG = CT_CLASSD_INT_PEND
#define CLEAR_PENDING_UART_RI_INTERRUPT     RESET_INT_PENDING_REG = UART_RI_INT_PEND
#define CLEAR_PENDING_UART_TI_INTERRUPT     RESET_INT_PENDING_REG = UART_TI_INT_PEND
#define CLEAR_PENDING_SPI_INTERRUPT         RESET_INT_PENDING_REG = SPI_INT_PEND
#define CLEAR_PENDING_TIM0_INTERRUPT        RESET_INT_PENDING_REG = TIM0_INT_PEND
#define CLEAR_PENDING_TIM1_INTERRUPT        RESET_INT_PENDING_REG = TIM1_INT_PEND
#define CLEAR_PENDING_CLK100_INTERRUPT      RESET_INT_PENDING_REG = CLK100_INT_PEND
#define CLEAR_PENDING_DIP_INTERRUPT         RESET_INT_PENDING_REG = DIP_INT_PEND
#define CLEAR_PENDING_AD_INTERRUPT          RESET_INT_PENDING_REG = AD_INT_PEND
#define CLEAR_PENDING_SPI2_INTERRUPT        RESET_INT_PENDING_REG = SPI2_INT_PEND
#define CLEAR_PENDING_DSP_INTERRUPT         RESET_INT_PENDING_REG = DSP_INT_PEND
#define CLEAR_PENDING_ULP_INTERRUPT         RESET_INT_PENDING_REG = ULP_INT_PEND

#endif

// End of file.
