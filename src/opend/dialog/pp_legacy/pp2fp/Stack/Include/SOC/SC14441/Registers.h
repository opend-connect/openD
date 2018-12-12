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

#ifndef REGISTERS_H
#define REGISTERS_H

/****************************************************************************
*                               Include files
****************************************************************************/

#ifndef SC14441
  #error This file is for SC14441 only!
#endif

#ifdef __IAR_SYSTEMS_ICC__
  #ifndef __KLOCWORK__
    #include <SOC/SC14441/Iar441.h>
  #else
    #include <SOC/SC14441/Msvc441.h>
  #endif
#endif
#ifdef __GNUC__
#ifdef REG_SIM_TYPE
  #include <SOC/SC14441/Msvc441.h>
#else
  #include <SOC/SC14441/Gccd441.h>
  #include <SOC/SC14441/Gccv441.h>
#endif
#endif
#ifdef _MSC_VER
  #include <SOC/SC14441/Msvc441.h>
#endif
#ifdef WIN32_BMC_SIM
  #include <Win32Sim/BmcSim/BmcSim.h>
#endif
#ifdef SYSCLOCK_MANAGER
  #include <SOC/SC1445x/SC1445x.h>
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/

// Frequency of the connected crystal.
#ifndef SC_XTAL_FREQUENCY
  #define SC_XTAL_FREQUENCY 10368000UL
#endif

#define SWRESET { DEBUG_REG_bit.SW_RESET = 1; }

#ifndef TRIGWATCHDOG
  #define TRIGWATCHDOG(x) { WATCHDOG_REG = x; }
#endif
#ifndef RUNWATCHDOG
  #define RUNWATCHDOG() { RESET_FREEZE_REG = FRZ_WDOG; }
#endif
#ifndef STOPWATCHDOG
  #define STOPWATCHDOG() { SET_FREEZE_REG = FRZ_WDOG; }
#endif

#define GDSP_MC_GEN2DSP_BRIDGE_AREA_START     (0x4000)     /*  */

/*====================================================*/
//  Px_DIR_REG
/*====================================================*/
// example
//  SET_DIR_REG(P2_DIR_REG,6,Px_DIR_INPUT_PULL_DN);
//
#define Px_DIR_INPUT          0
#define Px_DIR_INPUT_PULL_UP  1
#define Px_DIR_INPUT_PULL_DN  2
#define Px_DIR_OUTPUT         3
#define SET_DIR_REG(dir_reg, dir_bit,dir_val) {dir_reg=(dir_reg&~(3L<<(2*dir_bit))) | (((rsuint16)dir_val)<<(2*dir_bit));}

/*====================================================*/
//  ACCESS1_CTRL_REG
/*====================================================*/
#define ACCESS1_CTRL_SCK_SEL_400KHZ  RSBIT9
#define ACCESS1_CTRL_SCK_SEL_1152KHZ RSBIT10

/*====================================================*/
//  ACCESS2_CTRL_REG
/*====================================================*/
#define ACCESS2_CTRL_SCK_SEL_400KHZ  RSBIT9
#define ACCESS2_CTRL_SCK_SEL_1152KHZ RSBIT10

/*====================================================*/
//  P0_MODE_REG
/*====================================================*/
#define P0_MODE_7_MODE          (RSBIT12|RSBIT13)
  #define P0_MODE_7_P07         0
  #define P0_MODE_7_SPIDI       RSBIT12
  #define P0_MODE_7_PWM1        RSBIT13
#define P0_MODE_6_MODE          (RSBIT10|RSBIT11)
  #define P0_MODE_6_P06         0
  #define P0_MODE_6_MODE_SPIDO  RSBIT10
#define P0_MODE_5_MODE          (RSBIT8|RSBIT9)
  #define P0_MODE_5_P05         0
  #define P0_MODE_5_MODE_SPICLK RSBIT8
#define P0_MODE_4_MODE          (RSBIT6|RSBIT7)
  #define P0_MODE_4_P04         0
  #define P0_MODE_4_SPIEN       RSBIT6
#define P0_MODE_3_MODE          (RSBIT4|RSBIT5)
  #define P0_MODE_3_P03         0
  #define P0_MODE_3_SCL2        RSBIT4
#define P0_MODE_2_MODE          (RSBIT2|RSBIT3)
  #define P0_MODE_2_P02         0
  #define P0_MODE_2_SDA2        RSBIT2
#define P0_MODE_1_MODE          RSBIT1
  #define P0_MODE_1_P01         0
  #define P0_MODE_1_PWM0        RSBIT1
#define P0_MODE_0_MODE          RSBIT0
  #define P0_MODE_0_P00         0
  #define P0_MODE_0_MODE_UTX    RSBIT0

/*====================================================*/
//  P1_MODE_REG
/*====================================================*/
#define P1_RF_BB_MODE           (RSBIT8|RSBIT9)
#define P1_MODE_5_MODE          (RSBIT5|RSBIT6|RSBIT7)
#define P1_MODE_4_MODE          RSBIT4
  #define P1_MODE_4_P14_2MA     0
  #define P1_MODE_4_P14_1MA     RSBIT4
#define P1_MODE_3_MODE          RSBIT3
  #define P1_MODE_3_P13_2MA     0
  #define P1_MODE_3_P13_1MA     RSBIT3
#define P1_MODE_2_MODE          RSBIT2
#define P1_MODE_1_MODE          RSBIT1
#define P1_MODE_0_MODE          RSBIT0
  #define P1_MODE_0_P10         0
  #define P1_MODE_0_ADC1        RSBIT0

/*====================================================*/
//  P2_MODE_REG
/*====================================================*/
#define P2_MODE_7_MODE          RSBIT15
  #define P2_7_MODE_P27         0
  #define P2_7_MODE_BXTAL       RSBIT15
#define P2_MODE_6_MODE          RSBIT13
  #define P2_6_MODE_P26         0
  #define P2_6_MODE_WFTIN       RSBIT13
#define P2_MODE_5_MODE          (RSBIT10|RSBIT11)
  #define P2_5_MODE_P25         0
  #define P2_5_MODE_FSC         RSBIT10
  #define P2_5_MODE_SF          RSBIT11
  #define P2_5_MODE_RESERVED    (RSBIT10|RSBIT11)
#define P2_MODE_4_MODE          (RSBIT8|RSBIT9)
  #define P2_4_MODE_P24         0
  #define P2_4_MODE_PCMDO       RSBIT8
  #define P2_4_MODE_SCL1        RSBIT9
  #define P2_4_MODE_DP3         (RSBIT8|RSBIT9)
#define P2_MODE_3_MODE          (RSBIT6|RSBIT7)
  #define P2_3_MODE_P23         0
  #define P2_3_MODE_PCMDI       RSBIT6
  #define P2_3_MODE_SDA1        RSBIT7
  #define P2_3_MODE_DP2         (RSBIT6|RSBIT7)
#define P2_MODE_2_MODE          (RSBIT4|RSBIT5)
  #define P2_2_MODE_P22         0
  #define P2_2_MODE_PCMCLK      RSBIT4
  #define P2_2_MODE_CLK100      RSBIT5
  #define P2_2_MODE_RESERVED    (RSBIT4|RSBIT5)
#define P2_MODE_1_MODE          (RSBIT2|RSBIT3)
  #define P2_1_MODE_P21         0
  #define P2_1_MODE_ECZ2        RSBIT2
  #define P2_1_MODE_PWM1        RSBIT3
  #define P2_1_MODE_LED4        (RSBIT2|RSBIT3)
#define P2_MODE_0_MODE          (RSBIT0|RSBIT1)
  #define P2_0_MODE_P20         0
  #define P2_0_MODE_ECZ1        RSBIT0
  #define P2_0_MODE_PWM0        RSBIT1
  #define P2_0_MODE_LED3        (RSBIT0|RSBIT1)


/*====================================================*/
//  RF_SYNTH_CTRL1_REG
/*====================================================*/
#define RF_SYNTH_CTRL1_VCO_EXTERNAL   (0x0001)
#define RF_SYNTH_CTRL1_VCO_VTUNE_MID  (0x0002)
#define RF_SYNTH_CTRL1_VCO_MOD_EN     (0x0004)
#define RF_SYNTH_CTRL1_VCO_CUR_SET    (0x0008)
#define RF_SYNTH_CTRL1_LF_VCO_DIS     (0x0010)
#define RF_SYNTH_CTRL1_VCO_TUNE_EXT   (0x0020)
#define RF_SYNTH_CTRL1_DIV2_EN_ALL    (0x0080)
#define RF_SYNTH_CTRL1_DIV2_CUR_SET   (0x0700)
#define RF_SYNTH_CTRL1_PFD_SLOW_RESET (0x1000)
#define RF_SYNTH_CTRL1_PFD_POLARITY   (0x2000)
#define RF_SYNTH_CTRL1_GDAC_VCO_DIS   (0x4000)
#define RF_SYNTH_CTRL1_VCO_MOD_EXT    (0x8000)


/*====================================================*/
//  DSP_OVERFLOW_REG
/*====================================================*/
/*====================================================*/
//  CLK_CODEC_REG
/*====================================================*/
#define CLK_CODEC_CLK_PCM_SEL_1152   (0x0000)
#define CLK_CODEC_CLK_PCM_SEL_2304   (0x0200)
#define CLK_CODEC_CLK_PCM_SEL_4608   (0x0300)
#define DSP_OVERFLOW_M_IRQ_EN        RSBIT15
#define DSP_OVERFLOW_M_WTF_EN        RSBIT14
#define DSP_OVERFLOW_M_INT5_EN       RSBIT13
#define DSP_OVERFLOW_M_INT4_EN       RSBIT12
#define DSP_OVERFLOW_M_INT3_EN       RSBIT11
#define DSP_OVERFLOW_M_INT2_EN       RSBIT10
#define DSP_OVERFLOW_M_INT1_EN       RSBIT9
#define DSP_OVERFLOW_M_INT0_EN       RSBIT8
#define DSP_OVERFLOW_IRQ             RSBIT7
#define DSP_OVERFLOW_WTF             RSBIT6
#define DSP_OVERFLOW_INT5            RSBIT5
#define DSP_OVERFLOW_INT4            RSBIT4
#define DSP_OVERFLOW_INT3            RSBIT3
#define DSP_OVERFLOW_INT2            RSBIT2
#define DSP_OVERFLOW_INT1            RSBIT1
#define DSP_OVERFLOW_INT0            RSBIT0
#define DSP_OVERFLOW_INT0_5          0x1f

/*====================================================*/
//  DSP_PCM_CTRL_REG
/*====================================================*/
#define DSP_PCM_CTRL_PCM_FSC0LEN_1   (0x0000)
#define DSP_PCM_CTRL_PCM_FSC0LEN_8   (0x0008)
#define DSP_PCM_CTRL_PCM_FSC0LEN_16  (0x0010)
#define DSP_PCM_CTRL_PCM_FSC0LEN_32  (0x0018)

/*====================================================*/
//  DSP_MAIN_SYNC0_REG
/*====================================================*/
#define DSP_MAIN_SYNC0_4KHZ  0
#define DSP_MAIN_SYNC0_8KHZ  1
#define DSP_MAIN_SYNC0_16KHZ 2
#define DSP_MAIN_SYNC0_PD    3

#define DSP_MAIN_SYNC0_RAMOUT3_SYNC_BIT 14
#define DSP_MAIN_SYNC0_RAMOUT2_SYNC_BIT 12
#define DSP_MAIN_SYNC0_RAMOUT1_SYNC_BIT 10
#define DSP_MAIN_SYNC0_RAMOUT0_SYNC_BIT  8
#define DSP_MAIN_SYNC0_RAMIN3_SYNC_BIT   6
#define DSP_MAIN_SYNC0_RAMIN2_SYNC_BIT   4
#define DSP_MAIN_SYNC0_RAMIN1_SYNC_BIT   2
#define DSP_MAIN_SYNC0_RAMIN0_SYNC_BIT   0

/*====================================================*/
//  DSP_MAIN_SYNC1_REG
/*====================================================*/
#define DSP_MAIN_SYNC1_PCM_SYNC_8KHZ  (0x0000)
#define DSP_MAIN_SYNC1_PCM_SYNC_16KHZ (0x4000)
#define DSP_MAIN_SYNC1_PCM_SYNC_32KHZ (0x8000)

#define DSP_MAIN_SYNC1_SYNC_PD            3
#define DSP_MAIN_SYNC1_SYNC_8KHZ_INV      3  // only DSP_SYNC0..2 fields
#define DSP_MAIN_SYNC1_SYNC_32KHZ         2  // not allowed for ADC_SYNC field
#define DSP_MAIN_SYNC1_SYNC_16KHZ         1
#define DSP_MAIN_SYNC1_SYNC_8KHZ          0

#define DSP_MAIN_SYNC1_PCM_SYNC_BIT      14
#define DSP_MAIN_SYNC1_ADC_SYNC_BIT      12
#define DSP_MAIN_SYNC1_DA_LSR_SYNC_BIT   10
#define DSP_MAIN_SYNC1_DA_CLSD_SYNC_BIT   8
#define DSP_MAIN_SYNC1_AD_SYNC_BIT        6
#define DSP_MAIN_SYNC1_DSP_SYNC2_BIT      4
#define DSP_MAIN_SYNC1_DSP_SYNC1_BIT      2
#define DSP_MAIN_SYNC1_DSP_SYNC0_BIT      0

#define DSP_MAIN_CTRL_MCNTR_BIT           8  // bit 8,9
#define DSP_MAIN_CTRL_MCNTR_RESET         0
#define DSP_MAIN_CTRL_MCNTR_FREERUN       1
#define DSP_MAIN_CTRL_MCNTR_ANORM         2
#define DSP_MAIN_CTRL_MCNTR_ANORM_X       3


/*====================================================*/
//  DSP_REG_BANK
/*====================================================*/

typedef struct
{
   volatile rsuint16 DSP_MAIN_SYNC0_reg;
   volatile rsuint16 DSP_MAIN_SYNC1_reg;
   volatile rsuint16 DSP_MAIN_CNT_reg;
   volatile rsuint16 DSP_ADC1S_reg;
   volatile rsuint16 DSP_ADC0S_reg;
   volatile rsuint16 DSP_CLASSD_reg;
   volatile rsuint16 DSP_CODEC_MIC_GAIN_reg;
   volatile rsuint16 DSP_CODEC_OUT_reg;
   volatile rsuint16 DSP_CODEC_IN_reg;
   volatile rsuint16 DSP_RAM_OUT0_reg;
   volatile rsuint16 DSP_RAM_OUT1_reg;
   volatile rsuint16 DSP_RAM_OUT2_reg;
   volatile rsuint16 DSP_RAM_OUT3_reg;
   volatile rsuint16 DSP_RAM_IN0_reg;
   volatile rsuint16 DSP_RAM_IN1_reg;
   volatile rsuint16 DSP_RAM_IN2_reg;
   volatile rsuint16 DSP_RAM_IN3_reg;
   volatile rsuint16 DSP_ZCROSS1_OUT_reg;
   volatile rsuint16 DSP_ZCROSS2_OUT_reg;
   volatile rsuint16 DSP_PCM_OUT0_reg;
   volatile rsuint16 DSP_PCM_OUT1_reg;
   volatile rsuint16 DSP_PCM_OUT2_reg;
   volatile rsuint16 DSP_PCM_OUT3_reg;
   volatile rsuint16 DSP_PCM_IN0_reg;
   volatile rsuint16 DSP_PCM_IN1_reg;
   volatile rsuint16 DSP_PCM_IN2_reg;
   volatile rsuint16 DSP_PCM_IN3_reg;
   volatile rsuint16 DSP_PCM_CTRL_reg;
   volatile rsuint16 DSP_PHASE_INFO_reg;
   volatile rsuint16 Reserved1;
   volatile rsuint16 DSP_MAIN_CTRL_reg;
   volatile rsuint16 DSP_CLASSD_BUZZOFF_reg;

   volatile rsuint16 DSP_PCM_OUT4_reg;
   volatile rsuint16 DSP_PCM_OUT5_reg;
   volatile rsuint16 DSP_PCM_IN4_reg;
   volatile rsuint16 DSP_PCM_IN5_reg;
   volatile rsuint16 DSP_CODEC2_IN_reg;
   rsuint16 reserved_1027fcA[3];
   // Gen2Dsp1
   volatile rsuint16 DSP_CTRL_reg;
   volatile rsuint16 DSP_PC_reg;
   volatile rsuint16 DSP_PC_START_reg;
   volatile rsuint16 DSP_IRQ_START_reg;
   volatile rsuint16 DSP_INT_reg;
   volatile rsuint16 DSP_INT_MASK_reg;
   volatile rsuint16 DSP_INT_PRIO1_reg;
   volatile rsuint16 DSP_INT_PRIO2_reg;
   volatile rsuint16 DSP_OVERFLOW_reg;
   volatile rsuint16 DSP_JTBL_reg;
   volatile rsuint16 DSP_AUX_reg;
   rsuint16 reserved_1027fe6[5];
   volatile rsuint16 DSP_IREG;
   rsuint16 reserved_1027ff2;
   volatile rsuint16 DSP_INOUT_REG_LSW;
   volatile rsuint16 DSP_INOUT_REG_MSW;
   volatile rsuint16 DSP_TIMERL_reg;
   volatile rsuint16 DSP_TIMERH_reg;
   volatile rsuint16 DSP_TIMER_CTRL_reg;
} DspRegBank1_t;

RS_BEGIN_EXTERN_C
extern DspRegBank1_t * const DspRegBank1;
RS_END_EXTERN_C

// DSP ROM1/2 Data Table Addresses ( Gen2Dsp address values)
#define _CFFT_TWIDDLE_128			     0x8000 
#define _CFFT_WINDOW_SINE128		     0x8100 
#define _CFFT_WINDOW_TRIANGLE128	     0x8180 
#define _DCT_QTABLE_ROM				     0x8200 
#define _DCT_ZIGZAG_ADDR_PTR		     0x8280 
#define _G726_TBL_INTLV				     0x82C0 
#define _G726_TBL_VPTR                   0x82D8
#define _G726_TBL_VYLP_TH                0x82DD 
#define _G726_TBL_VYU_TH2                0x82E3 
#define _G726_TBL_VLIMITS                0x82ED 
#define _G722_TX_TBL_Q6M8			     0x82F0
#define _G722_TX_TBL_MISIL			     0x830D
#define _G722_TX_TBL_QQ4M8			     0x834D
#define _G722_RX_TBL_QQ2M8_NOTPADDED     0x835D 
#define _G722_TX_TBL_WL				     0x8361 
#define _G722_RX_TBL_WH_NONPADDED	     0x8371 
#define _G722_TX_TBL_ILB			     0x8375 
#define _G722_TX_TBL_H				     0x8395 
#define _G722_RX_TBL_QQ6M8			     0x83A1 


/*====================================================*/
//  CODEC_LSR_REG modes
/*====================================================*/

#define CODEC_LSR_LSR_MODE_AGND  0  // AGND ref
#define CODEC_LSR_LSR_MODE_DA_LP 1  // DA-diff via extra LP filter
#define CODEC_LSR_LSR_MODE_DA    2  // DA-diff
#define CODEC_LSR_LSR_MODE_SE    3  // DA-single-ended


/*====================================================*/
//  CODEC_MIC_REG modes
/*====================================================*/
  #define CODEC_MIC_MIC_MODE_NORMAL  0
  #define CODEC_MIC_MIC_MODE_MICPLUS 1
  #define CODEC_MIC_MIC_MODE_MICNEG  2
  #define CODEC_MIC_MIC_MODE_DISABLE 3

/*====================================================*/
//  CLK_CODEC_REG Mode
/*====================================================*/
// CLK_CODEC_REG
#define CLK_CODEC_PCM_SEL_BIT        8
#define CLK_CODEC_LSR_SEL_BIT        6
#define CLK_CODEC_DA_CLASSD_SEL_BIT  4
#define CLK_CODEC_AD_SEL_BIT         2
#define CLK_CODEC_MAIN_SEL_BIT       0


#define CLK_CODEC_CLK_SEL_1152   0
#define CLK_CODEC_CLK_SEL_2304   2
#define CLK_CODEC_CLK_SEL_4608   3

/*====================================================*/
/*====================================================*/
//  CODEC_TONE_REG
/*====================================================*/
#define CODEC_TONE_CID_PR_PD       RSBIT1
#define CODEC_TONE_RNG_PR_PD       RSBIT3

#define SET_PORT1(bit)  P1_SET_DATA_REG = (1<<bit)
#define CLR_PORT1(bit)  P1_RESET_DATA_REG = (1<<bit)
#define GET_PORT1(bit)  (P1_DATA_REG & (1<<bit))

#define SET_PORT2(bit)  P2_SET_DATA_REG = (1<<bit)
#define CLR_PORT2(bit)  P2_RESET_DATA_REG = (1<<bit)
#define SET_PORT3(bit)  P3_SET_DATA_REG = (1<<bit)
#define CLR_PORT3(bit)  P3_RESET_DATA_REG = (1<<bit)

/* TONE_CTRLn_REQ */
// 9
#define MCT_INT                     RSBIT9
// 8
#define CT_INT                      RSBIT8
// 7-4
#define TIMER_RELOAD_DIV1           0x00
#define TIMER_RELOAD_DIV2           0x10
#define TIMER_RELOAD_DIV3           0x20
#define TIMER_RELOAD_DIV4           0x30
#define TIMER_RELOAD_DIV5           0x40
#define TIMER_RELOAD_DIV6           0x50
#define TIMER_RELOAD_DIV7           0x60
#define TIMER_RELOAD_DIV8           0x70
#define TIMER_RELOAD_DIV9           0x80
#define TIMER_RELOAD_DIV10          0x90
#define TIMER_RELOAD_DIV11          0xa0
#define TIMER_RELOAD_DIV12          0xb0
#define TIMER_RELOAD_DIV13          0xc0
#define TIMER_RELOAD_DIV14          0xd0
#define TIMER_RELOAD_DIV15          0xe0
#define TIMER_RELOAD_DIV16          0xf0
// 3-2
#define CLKSRC_144KHZ               0x0
#define CLKSRC_METERING             0x4
#define CLKSRC_ECZ                  0x8
#define CLKSRC_ECZ2                 0xC
// 1-0
#define GATESRC_CLK100              0x0
#define GATESRC_RINGING_VBAT3       0x1
#define GATESRC_ECZ                 0x2
#define GATESRC_ECZ2                0x3

//  BAT_CTRL_REG - Power on/off
/*====================================================*/
#define SET_POWER_ON_LATCH BAT_CTRL_REG_bit.REG_ON=1
#define CLR_POWER_ON_LATCH BAT_CTRL_REG_bit.REG_ON=0

/*====================================================*/
//  RF_REG_ID  - Macro to find RF register index from its address
/*====================================================*/
#ifdef PCCOMPILE // Necessary because some registers are remapped to bmcsim
#define RF_REG_ID(rfreg) (rsuint8) (((rsuint32)&RegSim._##rfreg-(rsuint32)&RegSim._RF_BURST_MODE_CTRL0_REG)/2)
#else
#define RF_REG_ID(rfreg) (rsuint8) ((rfreg##_adr-RF_BURST_MODE_CTRL0_REG_adr)/2)
#endif
#define RF_REG_MW_READ RSBIT7

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

#ifndef PCCOMPILE
  /* DIP sequencer RAM */
  #if defined(__KLOCWORK__) || defined(__GNUC__)
  extern volatile rsuint16 BMC_SRam[640] __attribute__((data32));
  #else
  __root __no_init volatile rsuint16 BMC_SRam[640] @ 0x1000000;
  #endif
#endif

/****************************************************************************
*                             Function prototypes
****************************************************************************/
rsbool RsInterlockedBitTestAndSet0(rsuint8 volatile *dest);
rsbool RsInterlockedBitTestAndSet1(rsuint8 volatile *dest);
rsbool RsInterlockedBitTestAndSet2(rsuint8 volatile *dest);
rsbool RsInterlockedBitTestAndSet3(rsuint8 volatile *dest);
rsbool RsInterlockedBitTestAndSet4(rsuint8 volatile *dest);
rsbool RsInterlockedBitTestAndSet5(rsuint8 volatile *dest);
rsbool RsInterlockedBitTestAndSet6(rsuint8 volatile *dest);
rsbool RsInterlockedBitTestAndSet7(rsuint8 volatile *dest);

// Set the bit specified at the address specified. 8-bit access will be used.
// Returns previous status of the bit.
RS_C_INLINE rsbool RsInterlockedBitTestAndSet(rsuint8 volatile *dest, rsint8 bitpos)
{
  #ifndef PCCOMPILE
  if (bitpos == 0) { return RsInterlockedBitTestAndSet0(dest); }
  if (bitpos == 1) { return RsInterlockedBitTestAndSet1(dest); }
  if (bitpos == 2) { return RsInterlockedBitTestAndSet2(dest); }
  if (bitpos == 3) { return RsInterlockedBitTestAndSet3(dest); }
  if (bitpos == 4) { return RsInterlockedBitTestAndSet4(dest); }
  if (bitpos == 5) { return RsInterlockedBitTestAndSet5(dest); }
  if (bitpos == 6) { return RsInterlockedBitTestAndSet6(dest); }
  if (bitpos == 7) { return RsInterlockedBitTestAndSet7(dest); }
  return 0;
  #else
  // The implementation for PC compile is not thread safe. It just mimics the target result
  rsuint8 tmp = *dest;
  if (bitpos == 0) { *dest |= RSBIT0; return ((tmp & RSBIT0) == RSBIT0); }
  if (bitpos == 1) { *dest |= RSBIT1; return ((tmp & RSBIT1) == RSBIT1); }
  if (bitpos == 2) { *dest |= RSBIT2; return ((tmp & RSBIT2) == RSBIT2); }
  if (bitpos == 3) { *dest |= RSBIT3; return ((tmp & RSBIT3) == RSBIT3); }
  if (bitpos == 4) { *dest |= RSBIT4; return ((tmp & RSBIT4) == RSBIT4); }
  if (bitpos == 5) { *dest |= RSBIT5; return ((tmp & RSBIT5) == RSBIT5); }
  if (bitpos == 6) { *dest |= RSBIT6; return ((tmp & RSBIT6) == RSBIT6); }
  if (bitpos == 7) { *dest |= RSBIT7; return ((tmp & RSBIT7) == RSBIT7); }
  return 0;
  #endif
}
#endif

// End of file.

