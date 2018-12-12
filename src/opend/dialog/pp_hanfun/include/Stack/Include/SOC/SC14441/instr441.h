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
#ifndef INSTR480_H__
#define INSTR480_H__


// --- DIP control commands, see AN-D-031

// TIM                              402  422  424  404  405  408  428  430  438  480  481 
#define  BR             0x01   //    X    X    X    X    X    X    X    X    X    X    X  
#define  BR_B0          0x10   //                             X    X    X    X    X    X  
#define  BR_B1          0x11   //                             X    X    X    X    X    X  
#define  BR_B2          0x1A   //                                                      X  
#define  BRK            0x6E   //    X    X    X    X    X    X    X    X    X    X    X  
#define  JMP            0x02   //    X    X    X    X    X    X    X    X    X    X    X  
#define  JMP1           0x03   //    X    X    X    X    X    X    X    X    X    X    X  
#define  JC             0x13   //                                  X    X    X    X    X  
#define  RTN            0x04   //    X    X    X    X    X    X    X    X    X    X    X  
#define  JMPF           0x12   //                             X    X    X    X    X    X  
#define  JMPF0          0x1D   //                                                      X  
#define  JMPF2          0x1B   //                                                      X  
#define  RTNF           0x14   //                             X    X    X    X    X    X  
#define  RTNO           0x17   //                                                      X  
#define  WNT            0x08   //    X    X    X    X    X    X    X    X    X    X    X  
#define  WT             0x09   //    X    X    X    X    X    X    X    X    X    X    X  
#define  PAG_ON         0x18   //                             X    X    X    X    X    X  
#define  PAG_OFF        0x19   //                             X    X    X    X    X    X  
#define  WTT            0x47   //                                                      X  
#define  WSC            0x48   //         X    X    X    X    X    X    X    X    X    X  
#define  RFEN           0x0B   //    X    X    X    X    X    X    X    X    X    X    X  
#define  RFDIS          0x0A   //    X    X    X    X    X    X    X    X    X    X    X  
#define  BK_A           0x0E   //    X    X    X    X    X    X    X    X    X    X    X  
#define  BK_A1          0x05   //         X    X                   X    X    X    X    X  
#define  BK_A2          0x1E   //                                  X    X    X    X    X  
#define  BK_A3          0x15   //                                  X    X    X    X    X  
#define  BK_MA          0x16   //                                  X    X    X    X    X  
#define  BK_C           0x0F   //    X    X    X    X    X    X    X    X    X    X    X  
#define  BK_MC          0x1F   //                                  X    X    X    X    X  
#define  SLOTZERO       0x0D   //    X    X    X    X    X    X    X    X    X    X    X  
#define  EN_SL_ADJ      0x2C   //    X    X    X    X    X    X    X    X    X    X    X  
#define  WNTP1          0x07   //    X    X    X    X    X    X    X    X    X    X    X  
#define  WNTM1          0x06   //    X    X    X    X    X    X    X    X    X    X    X  
#define  LD_PTR         0x0C   //    X    X    X    X    X    X    X    X    X    X    X  
#define  LD_PTR2        0x1C   //                                  X    X    X    X    X  
#define  UNLCK          0x28   //    X    X    X    X    X    X    X    X    X    X    X  
#define  BCPV           0x4B   //                             X    X    X    X    X    X  
                                                                                          
// ADPCM                                                                                  
#define  A_NORM         0xC5   //    X    X    X    X    X    X    X    X    X    X    X  
#define  A_LDR          0xC6   //    X    X    X    X    X    X    X    X    X    X    X  
#define  A_LDW          0xC7   //    X    X    X    X    X    X    X    X    X    X    X  
#define  A_LDR1         0xCE   //         X    X    X    X         X    X    X    X    X  
#define  A_LDW1         0xCF   //         X    X    X    X         X    X    X    X    X  
#define  A_LDR2         0xD6   //                                  X    X    X    X    X  
#define  A_LDW2         0xD7   //                                  X    X    X    X    X  
#define  A_LDR3         0xDE   //                                  X    X    X    X    X  
#define  A_LDW3         0xDF   //                                  X    X    X    X    X  
#define  A_RX           0x49   //                                  X    X    X    X    X  
#define  A_TX           0x4A   //                                  X    X    X    X    X  
//#define  A_ST18         0xE1   //    X                                                  
                                                                                          
// BMC                                                                                    
#define  B_ST           0x31   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_TX           0x31   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_ST2          0x21   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_PPT          0x22   //              X    X    X    X    X    X    X    X    X  
#define  B_AT           0x32   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_AT2          0x37   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_BT           0x34   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_BTFM         0x23   //              X    X    X    X    X    X    X    X    X  
#define  B_BTFU         0x25   //    X    X    X    X    X    X B_BT2 in 420              
#define  B_BTFP         0x35   //    X    X    X    X    X    X B_BTP in 420              
#define  B_BTDU         0x71   //              X    X    X    X    X    X    X    X    X  
#define  B_BTDP         0x72   //              X    X    X    X    X    X    X    X    X  
#define  B_BTDM         0x96   //                                                      X  
#define  B_ON           0x27   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_XON          0x27   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_XOFF         0x26   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_SR           0x29   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_AR           0x3A   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_AR2          0x3F   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_RON          0x2F   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_RINV         0x2E   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_BR           0x3C   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_BRFU         0x2D   //    X    X    X    X    X    X B_BR2 in 420              
//#define  B_BR2          0x2D   //    X    X    X    X    X    X B_BR2 in 420            
#define  B_BRFP         0x3D   //    X    X    X    X    X    X B_BRP in 420              
#define  B_BRFD         0x2A   //              X    X    X    X    X    X    X    X    X  
#define  B_BRDU         0x79   //              X    X    X    X    X    X    X    X    X  
#define  B_BRDP         0x7A   //              X    X    X    X    X    X    X    X    X  
#define  B_BRDD         0x9E   //                                                      X  
#define  B_NIC          0x9F   //                             X    X    X    X    X    X  
#define  B_XR           0x2B   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_XT           0x24   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_WB_ON        0x65   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_WB_OFF       0x64   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_WRS          0x39   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_WRS2         0x38   //                             X    X    X    X    X    X  
#define  B_UNLCK        0x98   //                             X    X    X    X    X    X  
#define  B_RC           0x33   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_RST          0x20   //    X    X    X    X    X    X    X    X    X    X    X  
#define  B_DIV1         0x4F   //                        X    X    X    X    X    X    X  
#define  B_DIV2         0x4E   //                        X    X    X    X    X    X    X  
#define  B_DIV4         0x4D   //                        X    X    X    X    X    X    X  
#define  B_BTLU         0x95   //                                                 X    X  
#define  B_BTLM         0x93   //                                                 X    X  
#define  B_BTLP         0x75   //                                                 X    X  
#define  B_BRLU         0x9D   //                                                 X    X  
#define  B_BRLD         0x9A   //                                                 X    X  
#define  B_BRLP         0x7D   //                                                 X    X  
                                                                                          
                                                                                          
// --- Encryption                                                                         
#define  D_LDK          0x50   //    X    X    X    X    X    X    X    X    X    X    X  
#define  D_PREP         0x44   //    X    X    X    X    X    X    X    X    X    X    X  
#define  D_PREP2        0x45   //                                  X    X    X    X    X  
#define  D_WRS          0x5F   //    X    X    X    X    X    X    X    X    X    X    X  
#define  D_LDS          0x57   //    X    X    X    X    X    X    X    X    X    X    X  
#define  D_RST          0x40   //    X    X    X    X    X    X    X    X    X    X    X  
                                                                                          
// --- Micro wire                                                                         
#define  M_WR           0xB9   //    X    X    X    X    X    X    X    X    X    X    X  
#define  M_RD           0xBC   //                                       X    X    X    X  
#define  M_RST          0xA9   //    X    X    X    X    X    X    X    X    X    X    X  
#define  M_INI0         0xA0   //              X    X    X    X    X    X    X    X    X  
#define  M_INI1         0xA1   //              X    X    X    X    X    X    X    X    X  
#define  M_CON          0xAA   //                                  X    X    X    X    X  
#define  MEN1N          0xA4   //    X    X    X    X    X    X    X    X    X    X    X  
#define  MEN1           0xA5   //    X    X    X    X    X    X    X    X    X    X    X  
                                                                                          
#define  M_WRS          0xB8   //    Special use only (KM)                                
                                                                                          
// MICRO controller                                                                       
#define  U_INT0         0x61   //    X    X    X    X    X    X    X    X    X    X    X  
#define  U_INT1         0x6B   //    X    X    X    X    X    X    X    X    X    X    X  
#define  U_INT2         0x6D   //    X    X    X    X    X    X    X    X    X    X    X  
#define  U_INT3         0x6F   //    X    X    X    X    X    X    X    X    X    X    X  
#define  U_PSC          0x60   //    X    X    X    X    X    X    X    X    X    X    X  
#define  U_VINT         0x63   //    X    X    X    X    X    X    X    X    X    X    X  
#define  U_VNMI         0x4C   //                                  X    X    X    X    X  
                                                                                          
// RF control                                                                             
#define  R_LD0          0x80   //                                                 X    X  
#define  R_LDH0         0x81   //                                                 X    X  
#define  R_LDL0         0x82   //                                                 X    X  
#define  R_LD1          0x84   //                                                 X    X  
#define  R_LDH1         0x85   //                                                 X    X  
#define  R_LDL1         0x86   //                                                 X    X  
#define  R_LD2          0x88   //                                                 X    X  
#define  R_LDH2         0x89   //                                                 X    X  
#define  R_LDL2         0x8A   //                                                 X    X  


//#define BMCCLOCKPRC  0x40   // select clock prescaler
//#define BMCRESET     0x80   // reset BMC



#define BMCBANKSHIFT    3      //Number of address bits shifted left in BK_C


// Special instruction arguments 
#define ADPCM0       0xfd
#define ADPCM1       0xfe
#define ARGPTR       0xff

// FAD antenna select signals
#define FADANT1      0x05
#define FADANT2      0x04
#define FADANTSEL    0x00
#define RSSIMEAS     0x06  


// copy to projcfg.h file: used to make project specific implementation possible
//#define BMC_CTRL_IV_NUM      4
//#define BMC_CTRL_CK_NUM      8
typedef struct
{
  rsuint8 SyncCfg;      // S_err[0..3],INV_RDI,INV_TDO,SenseA,PP/Fpn
  rsuint8 Slide_Mask;   // Slide[0..3] Mask[0..3]
  rsuint8 CmVol;        // CM5, CM, Vol[5..0]
  rsuint8 DAC;          // Don, TM_ANA, DAC[0..5]
  rsuint8 DpllAdpWin;   // DPLL[0..2], ADP, WIN[0..3]
  rsuint8 Misc;         // ENCoff, SenseS, Ron, nc, SCoff, DOFr, M[0..1]
  rsuint8 MFR0_FR_nr;   // MFR[0..3],FR_nr[0..3]
  rsuint8 MFR4;         // MFR[4..11]
  rsuint8 MFR12;        // MFR[12..19]
  rsuint8 MFR20_IV28;   // IV[28..31],MFR[20..23]
#ifdef BMC_CTRL_IV_NUM
#if (BMC_CTRL_IV_NUM!=0)
  rsuint8 IV32[BMC_CTRL_IV_NUM];  // IV[32..39],IV[40..47],IV[48..55],IV[56..63]
#endif
#endif
#ifdef BMC_CTRL_CK_NUM
#if (BMC_CTRL_CK_NUM!=0)
  rsuint8 CK[BMC_CTRL_CK_NUM];       // CK_0, CK_1, CK_2, CK_3, CK_4, CK_5, CK_6, CK_7
#endif
#endif
} BmcControlType;


typedef struct
{
  rsuint8 ADCresult;
  rsuint8 CRCresult;
  rsuint8 SlideError;
  rsuint8 ReceivePhase;
  rsuint8 Ones;
  #ifndef BSUB_EXCLUDE
    rsuint8 B5_B10_CRC; // 6 bit Bn_CRC
  #endif
} DipRxStatusType;

// Crc result masks
#define SYNCMASK     0x80
#define ACRCMASK     0x40
#define B32CRCMASK   0x20
#define XCRCMASK     0x02
#define ZMASK        0x01
#define NOACCESSPATT 0x24

#endif
