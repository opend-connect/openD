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
// #define REGS_GCC_MODE values:
//   #define REGS_GCC_MODE 0 // Variables.
//   #define REGS_GCC_MODE 1 // Defines only.
//   #define REGS_GCC_MODE 2 // Defines + variables.
#ifndef REGS_GCC_MODE
  #define REGS_GCC_MODE 0
#endif

#if (REGS_GCC_MODE == 0)

#ifndef REGS_GCC441_H
#define REGS_GCC441_H

/****************************************************************************
* Memory map.
****************************************************************************/

#define RAM_START           0x0
#define RAM_END             0x3FFF
#define RAM_ADM_START       0x9000
#define RAM_ADM_END         0x9FFF
#define SHARED_RAM_START    0x10000
#define SHARED_RAM_END      0x17FFF
#define PROGRAM_START       0x20000
#define PROGRAM_END         0xFEEFFF
#define BOOT_ROM_START      0xFEF000
#define BOOT_FROM UART      0xFEF002
#define BOOT_FROM_QSPI      0xFEF004
#define BOOT_ROM_ID         0xFEF7F8
#define BOOT_ROM_END        0xFEF7FF
#define INT_ACK_CR16_START  0xFFFC00
#define INT_ACK_CR16_END    0xFFFFFF
#define DIP_RAM_START       0x1000000
#define DIP_RAM_END         0x10001FF
#define DIP_RAM_2_START     0x1000200
#define DIP_RAM_2_END       0x10003FF
#define DIP_RAM_3_START     0x1000400
#define DIP_RAM_3_END       0x10004FF
#define DSP_MC_RAM_START    0x1030000
#define DSP_MC_RAM_END      0x10307FF
#define DSP_MC_ROM_START    0x1040000
#define DSP_MC_ROM_END      0x104BFFF

/****************************************************************************
* QSPIC_CTRLBUS_REG
****************************************************************************/

#define QSPIC_CTRLBUS_REG_adr 0xFF0C00
#define QSPIC_CTRLBUS_REG _A_QSPIC_CTRLBUS_REG.Value
#define QSPIC_CTRLBUS_REG_bit _A_QSPIC_CTRLBUS_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short QSPIC_SET_SINGLE     : 1; // Bit 0
    unsigned short QSPIC_SET_DUAL       : 1; // Bit 1
    unsigned short QSPIC_SET_QUAD       : 1; // Bit 2
    unsigned short QSPIC_EN_CS          : 1; // Bit 3
    unsigned short QSPIC_DIS_CS         : 1; // Bit 4
  };
} QSPIC_CTRLBUS_REG_type __attribute__((aligned(2)));

extern volatile QSPIC_CTRLBUS_REG_type _A_QSPIC_CTRLBUS_REG __attribute__((aligned(2)));

#define QSPIC_CTRLBUS_QSPIC_SET_SINGLE     0x0001 // Bit 0
#define QSPIC_CTRLBUS_QSPIC_SET_DUAL       0x0002 // Bit 1
#define QSPIC_CTRLBUS_QSPIC_SET_QUAD       0x0004 // Bit 2
#define QSPIC_CTRLBUS_QSPIC_EN_CS          0x0008 // Bit 3
#define QSPIC_CTRLBUS_QSPIC_DIS_CS         0x0010 // Bit 4

/****************************************************************************
* QSPIC_CTRLMODE_REG
****************************************************************************/

#define QSPIC_CTRLMODE_REG_adr 0xFF0C04
#define QSPIC_CTRLMODE_REG _A_QSPIC_CTRLMODE_REG.Value
#define QSPIC_CTRLMODE_REG_bit _A_QSPIC_CTRLMODE_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short QSPIC_AUTO_MD        : 1; // Bit 0
    unsigned short QSPIC_CLK_MD         : 1; // Bit 1
    unsigned short QSPIC_IO2_OEN        : 1; // Bit 2
    unsigned short QSPIC_IO3_OEN        : 1; // Bit 3
    unsigned short QSPIC_IO2_DAT        : 1; // Bit 4
    unsigned short QSPIC_IO3_DAT        : 1; // Bit 5
    unsigned short QSPIC_HRDY_MD        : 1; // Bit 6
    unsigned short QSPIC_RXD_NEG        : 1; // Bit 7
    unsigned short QSPIC_RPIPE_EN       : 1; // Bit 8
    unsigned short QSPIC_PCLK_MD        : 3; // Bit 11-9
    unsigned short QSPIC_FORCENSEQ_EN   : 1; // Bit 12
  };
} QSPIC_CTRLMODE_REG_type __attribute__((aligned(2)));

extern volatile QSPIC_CTRLMODE_REG_type _A_QSPIC_CTRLMODE_REG __attribute__((aligned(2)));

#define QSPIC_CTRLMODE_QSPIC_AUTO_MD        0x0001 // Bit 0
#define QSPIC_CTRLMODE_QSPIC_CLK_MD         0x0002 // Bit 1
#define QSPIC_CTRLMODE_QSPIC_IO2_OEN        0x0004 // Bit 2
#define QSPIC_CTRLMODE_QSPIC_IO3_OEN        0x0008 // Bit 3
#define QSPIC_CTRLMODE_QSPIC_IO2_DAT        0x0010 // Bit 4
#define QSPIC_CTRLMODE_QSPIC_IO3_DAT        0x0020 // Bit 5
#define QSPIC_CTRLMODE_QSPIC_HRDY_MD        0x0040 // Bit 6
#define QSPIC_CTRLMODE_QSPIC_RXD_NEG        0x0080 // Bit 7
#define QSPIC_CTRLMODE_QSPIC_RPIPE_EN       0x0100 // Bit 8
#define QSPIC_CTRLMODE_QSPIC_PCLK_MD        0x0E00 // Bit 11-9
#define QSPIC_CTRLMODE_QSPIC_FORCENSEQ_EN   0x1000 // Bit 12

/****************************************************************************
* QSPIC_RECVDATA_REG
****************************************************************************/

#define QSPIC_RECVDATA_REG_adr 0xFF0C08
#define QSPIC_RECVDATA_REG _A_QSPIC_RECVDATA_REG

extern volatile unsigned long _A_QSPIC_RECVDATA_REG;

/****************************************************************************
* QSPIC_BURSTCMDA_REG
****************************************************************************/

#define QSPIC_BURSTCMDA_REG_adr 0xFF0C0C
#define QSPIC_BURSTCMDA_REG _A_QSPIC_BURSTCMDA_REG.Value
#define QSPIC_BURSTCMDA_REG_bit _A_QSPIC_BURSTCMDA_REG

typedef union
{
  unsigned long Value;
  struct
  {
    unsigned long QSPIC_INST           : 8; // Bit 7-0
    unsigned long QSPIC_INST_WB        : 8; // Bit 15-8
    unsigned long QSPIC_EXT_BYTE       : 8; // Bit 23-16
    unsigned long QSPIC_INST_TX_MD     : 2; // Bit 25-24
    unsigned long QSPIC_ADR_TX_MD      : 2; // Bit 27-26
    unsigned long QSPIC_EXT_TX_MD      : 2; // Bit 29-28
    unsigned long QSPIC_DMY_TX_MD      : 2; // Bit 31-30
  };
} QSPIC_BURSTCMDA_REG_type __attribute__((aligned(4)));

extern volatile QSPIC_BURSTCMDA_REG_type _A_QSPIC_BURSTCMDA_REG __attribute__((aligned(4)));

#define QSPIC_BURSTCMDA_QSPIC_INST           0x00FF // Bit 7-0
#define QSPIC_BURSTCMDA_QSPIC_INST_WB        0xFF00 // Bit 15-8
#define QSPIC_BURSTCMDA_QSPIC_EXT_BYTE       0xFF0000 // Bit 23-16
#define QSPIC_BURSTCMDA_QSPIC_INST_TX_MD     0x3000000 // Bit 25-24
#define QSPIC_BURSTCMDA_QSPIC_ADR_TX_MD      0xC000000 // Bit 27-26
#define QSPIC_BURSTCMDA_QSPIC_EXT_TX_MD      0x30000000 // Bit 29-28
#define QSPIC_BURSTCMDA_QSPIC_DMY_TX_MD      0xC0000000 // Bit 31-30

/****************************************************************************
* QSPIC_BURSTCMDB_REG
****************************************************************************/

#define QSPIC_BURSTCMDB_REG_adr 0xFF0C10
#define QSPIC_BURSTCMDB_REG _A_QSPIC_BURSTCMDB_REG.Value
#define QSPIC_BURSTCMDB_REG_bit _A_QSPIC_BURSTCMDB_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short QSPIC_DAT_RX_MD      : 2; // Bit 1-0
    unsigned short QSPIC_EXT_BYTE_EN    : 1; // Bit 2
    unsigned short QSPIC_EXT_HF_DS      : 1; // Bit 3
    unsigned short QSPIC_DMY_NUM        : 2; // Bit 5-4
    unsigned short QSPIC_INST_MD        : 1; // Bit 6
    unsigned short QSPIC_WRAP_MD        : 1; // Bit 7
    unsigned short QSPIC_WRAP_LEN       : 2; // Bit 9-8
    unsigned short QSPIC_WRAP_SIZE      : 2; // Bit 11-10
    unsigned short QSPIC_CS_HIGH_MIN    : 3; // Bit 14-12
  };
} QSPIC_BURSTCMDB_REG_type __attribute__((aligned(2)));

extern volatile QSPIC_BURSTCMDB_REG_type _A_QSPIC_BURSTCMDB_REG __attribute__((aligned(2)));

#define QSPIC_BURSTCMDB_QSPIC_DAT_RX_MD      0x0003 // Bit 1-0
#define QSPIC_BURSTCMDB_QSPIC_EXT_BYTE_EN    0x0004 // Bit 2
#define QSPIC_BURSTCMDB_QSPIC_EXT_HF_DS      0x0008 // Bit 3
#define QSPIC_BURSTCMDB_QSPIC_DMY_NUM        0x0030 // Bit 5-4
#define QSPIC_BURSTCMDB_QSPIC_INST_MD        0x0040 // Bit 6
#define QSPIC_BURSTCMDB_QSPIC_WRAP_MD        0x0080 // Bit 7
#define QSPIC_BURSTCMDB_QSPIC_WRAP_LEN       0x0300 // Bit 9-8
#define QSPIC_BURSTCMDB_QSPIC_WRAP_SIZE      0x0C00 // Bit 11-10
#define QSPIC_BURSTCMDB_QSPIC_CS_HIGH_MIN    0x7000 // Bit 14-12

/****************************************************************************
* QSPIC_STATUS_REG
****************************************************************************/

#define QSPIC_STATUS_REG_adr 0xFF0C14
#define QSPIC_STATUS_REG _A_QSPIC_STATUS_REG.Value
#define QSPIC_STATUS_REG_bit _A_QSPIC_STATUS_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short QSPIC_BUSY           : 1; // Bit 0
  };
} QSPIC_STATUS_REG_type __attribute__((aligned(2)));

extern volatile QSPIC_STATUS_REG_type _A_QSPIC_STATUS_REG __attribute__((aligned(2)));

#define QSPIC_STATUS_QSPIC_BUSY           0x0001 // Bit 0

/****************************************************************************
* QSPIC_WRITEDATA_REG
****************************************************************************/

#define QSPIC_WRITEDATA_REG_adr 0xFF0C18
#define QSPIC_WRITEDATA_REG _A_QSPIC_WRITEDATA_REG.Value
#define QSPIC_WRITEDATA_REG_bit _A_QSPIC_WRITEDATA_REG

typedef union
{
  unsigned long Value;
  union
  {
    unsigned char SINGLE               ; // Bit 7-0
    unsigned short DUAL                ; // Bit 15-0
    unsigned long QUAD                 ; // Bit 31-0
  };
} QSPIC_WRITEDATA_REG_type __attribute__((aligned(4)));

extern volatile QSPIC_WRITEDATA_REG_type _A_QSPIC_WRITEDATA_REG __attribute__((aligned(4)));

#define QSPIC_WRITEDATA_SINGLE               0x00FF // Bit 7-0
#define QSPIC_WRITEDATA_DUAL                 0xFFFF // Bit 15-0
#define QSPIC_WRITEDATA_QUAD                 0xFFFFFFFF // Bit 31-0

/****************************************************************************
* QSPIC_READDATA_REG
****************************************************************************/

#define QSPIC_READDATA_REG_adr 0xFF0C1C
#define QSPIC_READDATA_REG _A_QSPIC_READDATA_REG.Value
#define QSPIC_READDATA_REG_bit _A_QSPIC_READDATA_REG

typedef union
{
  unsigned long Value;
  union
  {
    unsigned char SINGLE               ; // Bit 7-0
    unsigned short DUAL                ; // Bit 15-0
    unsigned long QUAD                 ; // Bit 31-0
  };
} QSPIC_READDATA_REG_type __attribute__((aligned(4)));

extern volatile QSPIC_READDATA_REG_type _A_QSPIC_READDATA_REG __attribute__((aligned(4)));

#define QSPIC_READDATA_SINGLE               0x00FF // Bit 7-0
#define QSPIC_READDATA_DUAL                 0xFFFF // Bit 15-0
#define QSPIC_READDATA_QUAD                 0xFFFFFFFF // Bit 31-0

/****************************************************************************
* QSPIC_DUMMYDATA_REG
****************************************************************************/

#define QSPIC_DUMMYDATA_REG_adr 0xFF0C20
#define QSPIC_DUMMYDATA_REG _A_QSPIC_DUMMYDATA_REG.Value
#define QSPIC_DUMMYDATA_REG_bit _A_QSPIC_DUMMYDATA_REG

typedef union
{
  unsigned long Value;
  union
  {
    unsigned char SINGLE               ; // Bit 7-0
    unsigned short DUAL                ; // Bit 15-0
    unsigned long QUAD                 ; // Bit 31-0
  };
} QSPIC_DUMMYDATA_REG_type __attribute__((aligned(4)));

extern volatile QSPIC_DUMMYDATA_REG_type _A_QSPIC_DUMMYDATA_REG __attribute__((aligned(4)));

#define QSPIC_DUMMYDATA_SINGLE               0x00FF // Bit 7-0
#define QSPIC_DUMMYDATA_DUAL                 0xFFFF // Bit 15-0
#define QSPIC_DUMMYDATA_QUAD                 0xFFFFFFFF // Bit 31-0

/****************************************************************************
* QSPIC_ERASECTRL_REG
****************************************************************************/

#define QSPIC_ERASECTRL_REG_adr 0xFF0C24
#define QSPIC_ERASECTRL_REG _A_QSPIC_ERASECTRL_REG.Value
#define QSPIC_ERASECTRL_REG_bit _A_QSPIC_ERASECTRL_REG

typedef union
{
  unsigned long Value;
  struct
  {
    unsigned long                      : 12; // Bit 11-0
    unsigned long QSPIC_ERS_ADDR       : 12; // Bit 23-12
    unsigned long QSPIC_ERASE_EN       : 1; // Bit 24
    unsigned long QSPIC_ERS_STATE      : 3; // Bit 27-25
  };
} QSPIC_ERASECTRL_REG_type __attribute__((aligned(4)));

extern volatile QSPIC_ERASECTRL_REG_type _A_QSPIC_ERASECTRL_REG __attribute__((aligned(4)));

#define QSPIC_ERASECTRL_QSPIC_ERS_ADDR       0xFFF000 // Bit 23-12
#define QSPIC_ERASECTRL_QSPIC_ERASE_EN       0x1000000 // Bit 24
#define QSPIC_ERASECTRL_QSPIC_ERS_STATE      0xE000000 // Bit 27-25

/****************************************************************************
* QSPIC_ERASECMDA_REG
****************************************************************************/

#define QSPIC_ERASECMDA_REG_adr 0xFF0C28
#define QSPIC_ERASECMDA_REG _A_QSPIC_ERASECMDA_REG.Value
#define QSPIC_ERASECMDA_REG_bit _A_QSPIC_ERASECMDA_REG

typedef union
{
  unsigned long Value;
  struct
  {
    unsigned long QSPIC_ERS_INST       : 8; // Bit 7-0
    unsigned long QSPIC_WEN_INST       : 8; // Bit 15-8
    unsigned long QSPIC_SUS_INST       : 8; // Bit 23-16
    unsigned long QSPIC_RES_INST       : 8; // Bit 31-24
  };
} QSPIC_ERASECMDA_REG_type __attribute__((aligned(4)));

extern volatile QSPIC_ERASECMDA_REG_type _A_QSPIC_ERASECMDA_REG __attribute__((aligned(4)));

#define QSPIC_ERASECMDA_QSPIC_ERS_INST       0x00FF // Bit 7-0
#define QSPIC_ERASECMDA_QSPIC_WEN_INST       0xFF00 // Bit 15-8
#define QSPIC_ERASECMDA_QSPIC_SUS_INST       0xFF0000 // Bit 23-16
#define QSPIC_ERASECMDA_QSPIC_RES_INST       0xFF000000 // Bit 31-24

/****************************************************************************
* QSPIC_ERASECMDB_REG
****************************************************************************/

#define QSPIC_ERASECMDB_REG_adr 0xFF0C2C
#define QSPIC_ERASECMDB_REG _A_QSPIC_ERASECMDB_REG.Value
#define QSPIC_ERASECMDB_REG_bit _A_QSPIC_ERASECMDB_REG

typedef union
{
  unsigned long Value;
  struct
  {
    unsigned long QSPIC_ERS_TX_MD      : 2; // Bit 1-0
    unsigned long QSPIC_WEN_TX_MD      : 2; // Bit 3-2
    unsigned long QSPIC_SUS_TX_MD      : 2; // Bit 5-4
    unsigned long QSPIC_RES_TX_MD      : 2; // Bit 7-6
    unsigned long QSPIC_EAD_TX_MD      : 2; // Bit 9-8
    unsigned long QSPIC_ERS_CS_HI      : 3; // Bit 12-10
    unsigned long                      : 3; // Bit 15-13
    unsigned long QSPIC_ERSRES_HLD     : 4; // Bit 19-16
    unsigned long                      : 4; // Bit 23-20
    unsigned long QSPIC_RESSUS_DLY     : 6; // Bit 29-24
  };
} QSPIC_ERASECMDB_REG_type __attribute__((aligned(4)));

extern volatile QSPIC_ERASECMDB_REG_type _A_QSPIC_ERASECMDB_REG __attribute__((aligned(4)));

#define QSPIC_ERASECMDB_QSPIC_ERS_TX_MD      0x0003 // Bit 1-0
#define QSPIC_ERASECMDB_QSPIC_WEN_TX_MD      0x000C // Bit 3-2
#define QSPIC_ERASECMDB_QSPIC_SUS_TX_MD      0x0030 // Bit 5-4
#define QSPIC_ERASECMDB_QSPIC_RES_TX_MD      0x00C0 // Bit 7-6
#define QSPIC_ERASECMDB_QSPIC_EAD_TX_MD      0x0300 // Bit 9-8
#define QSPIC_ERASECMDB_QSPIC_ERS_CS_HI      0x1C00 // Bit 12-10
#define QSPIC_ERASECMDB_QSPIC_ERSRES_HLD     0xF0000 // Bit 19-16
#define QSPIC_ERASECMDB_QSPIC_RESSUS_DLY     0x3F000000 // Bit 29-24

/****************************************************************************
* QSPIC_BURSTBRK_REG
****************************************************************************/

#define QSPIC_BURSTBRK_REG_adr 0xFF0C30
#define QSPIC_BURSTBRK_REG _A_QSPIC_BURSTBRK_REG.Value
#define QSPIC_BURSTBRK_REG_bit _A_QSPIC_BURSTBRK_REG

typedef union
{
  unsigned long Value;
  struct
  {
    unsigned long QSPIC_BRK_WRD        : 16; // Bit 15-0
    unsigned long QSPIC_BRK_EN         : 1; // Bit 16
    unsigned long QSPIC_BRK_SZ         : 1; // Bit 17
    unsigned long QSPIC_BRK_TX_MD      : 2; // Bit 19-18
  };
} QSPIC_BURSTBRK_REG_type __attribute__((aligned(4)));

extern volatile QSPIC_BURSTBRK_REG_type _A_QSPIC_BURSTBRK_REG __attribute__((aligned(4)));

#define QSPIC_BURSTBRK_QSPIC_BRK_WRD        0xFFFF // Bit 15-0
#define QSPIC_BURSTBRK_QSPIC_BRK_EN         0x10000 // Bit 16
#define QSPIC_BURSTBRK_QSPIC_BRK_SZ         0x20000 // Bit 17
#define QSPIC_BURSTBRK_QSPIC_BRK_TX_MD      0xC0000 // Bit 19-18

/****************************************************************************
* QSPIC_STATUSCMD_REG
****************************************************************************/

#define QSPIC_STATUSCMD_REG_adr 0xFF0C34
#define QSPIC_STATUSCMD_REG _A_QSPIC_STATUSCMD_REG.Value
#define QSPIC_STATUSCMD_REG_bit _A_QSPIC_STATUSCMD_REG

typedef union
{
  unsigned long Value;
  struct
  {
    unsigned long QSPIC_RSTAT_INST     : 8; // Bit 7-0
    unsigned long QSPIC_RSTAT_TX_MD    : 2; // Bit 9-8
    unsigned long QSPIC_RSTAT_RX_MD    : 2; // Bit 11-10
    unsigned long QSPIC_BUSY_POS       : 3; // Bit 14-12
    unsigned long QSPIC_BUSY_VAL       : 1; // Bit 15
    unsigned long QSPIC_RESSTS_DLY     : 6; // Bit 21-16
    unsigned long QSPIC_STSDLY_SEL     : 1; // Bit 22
  };
} QSPIC_STATUSCMD_REG_type __attribute__((aligned(4)));

extern volatile QSPIC_STATUSCMD_REG_type _A_QSPIC_STATUSCMD_REG __attribute__((aligned(4)));

#define QSPIC_STATUSCMD_QSPIC_RSTAT_INST     0x00FF // Bit 7-0
#define QSPIC_STATUSCMD_QSPIC_RSTAT_TX_MD    0x0300 // Bit 9-8
#define QSPIC_STATUSCMD_QSPIC_RSTAT_RX_MD    0x0C00 // Bit 11-10
#define QSPIC_STATUSCMD_QSPIC_BUSY_POS       0x7000 // Bit 14-12
#define QSPIC_STATUSCMD_QSPIC_BUSY_VAL       0x8000 // Bit 15
#define QSPIC_STATUSCMD_QSPIC_RESSTS_DLY     0x3F0000 // Bit 21-16
#define QSPIC_STATUSCMD_QSPIC_STSDLY_SEL     0x400000 // Bit 22

/****************************************************************************
* QSPIC_CHCKERASE_REG
****************************************************************************/

#define QSPIC_CHCKERASE_REG_adr 0xFF0C38
#define QSPIC_CHCKERASE_REG _A_QSPIC_CHCKERASE_REG

extern volatile unsigned long _A_QSPIC_CHCKERASE_REG;

/****************************************************************************
* QSPIC_GP_REG
****************************************************************************/

#define QSPIC_GP_REG_adr 0xFF0C3C
#define QSPIC_GP_REG _A_QSPIC_GP_REG.Value
#define QSPIC_GP_REG_bit _A_QSPIC_GP_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short AHB_QSPIC_OFFSET     : 2; // Bit 1-0
    unsigned short QSPIC_MEM_OFFSET     : 3; // Bit 4-2
    unsigned short QSPI_PIN_CUR         : 2; // Bit 6-5
    unsigned short SWITCH_QSPI_SPI      : 1; // Bit 7
    unsigned short SWITCH_SPI1_SPI2     : 1; // Bit 8
  };
} QSPIC_GP_REG_type __attribute__((aligned(2)));

extern volatile QSPIC_GP_REG_type _A_QSPIC_GP_REG __attribute__((aligned(2)));

#define QSPIC_GP_AHB_QSPIC_OFFSET     0x0003 // Bit 1-0
#define QSPIC_GP_QSPIC_MEM_OFFSET     0x001C // Bit 4-2
#define QSPIC_GP_QSPI_PIN_CUR         0x0060 // Bit 6-5
#define QSPIC_GP_SWITCH_QSPI_SPI      0x0080 // Bit 7
#define QSPIC_GP_SWITCH_SPI1_SPI2     0x0100 // Bit 8

/****************************************************************************
* CLK_AMBA_REG
****************************************************************************/

#define CLK_AMBA_REG_adr 0xFF4000
#define CLK_AMBA_REG _A_CLK_AMBA_REG.Value
#define CLK_AMBA_REG_bit _A_CLK_AMBA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short HCLK_DIV             : 3; // Bit 2-0
    unsigned short PCLK_DIV             : 2; // Bit 4-3
    unsigned short SRAM1_EN             : 1; // Bit 5
    unsigned short                      : 1; // Bit 6
    unsigned short MCRAM1_EN            : 1; // Bit 7
    unsigned short                      : 1; // Bit 8
    unsigned short HCLK_PRE             : 1; // Bit 9
    unsigned short                      : 3; // Bit 12-10
    unsigned short HCLK_XTAL            : 1; // Bit 13
  };
} CLK_AMBA_REG_type __attribute__((aligned(2)));

extern volatile CLK_AMBA_REG_type _A_CLK_AMBA_REG __attribute__((aligned(2)));

#define CLK_AMBA_HCLK_DIV             0x0007 // Bit 2-0
#define CLK_AMBA_PCLK_DIV             0x0018 // Bit 4-3
#define CLK_AMBA_SRAM1_EN             0x0020 // Bit 5
#define CLK_AMBA_MCRAM1_EN            0x0080 // Bit 7
#define CLK_AMBA_HCLK_PRE             0x0200 // Bit 9
#define CLK_AMBA_HCLK_XTAL            0x2000 // Bit 13

/****************************************************************************
* CLK_CODEC_DIV_REG
****************************************************************************/

#define CLK_CODEC_DIV_REG_adr 0xFF4002
#define CLK_CODEC_DIV_REG _A_CLK_CODEC_DIV_REG.Value
#define CLK_CODEC_DIV_REG_bit _A_CLK_CODEC_DIV_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CODEC_DIV            : 7; // Bit 6-0
    unsigned short CODEC_CLK_SEL        : 2; // Bit 8-7
  };
} CLK_CODEC_DIV_REG_type __attribute__((aligned(2)));

extern volatile CLK_CODEC_DIV_REG_type _A_CLK_CODEC_DIV_REG __attribute__((aligned(2)));

#define CLK_CODEC_DIV_CODEC_DIV            0x007F // Bit 6-0
#define CLK_CODEC_DIV_CODEC_CLK_SEL        0x0180 // Bit 8-7

/****************************************************************************
* CLK_CODEC_REG
****************************************************************************/

#define CLK_CODEC_REG_adr 0xFF4004
#define CLK_CODEC_REG _A_CLK_CODEC_REG.Value
#define CLK_CODEC_REG_bit _A_CLK_CODEC_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CLK_MAIN_SEL         : 2; // Bit 1-0
    unsigned short CLK_AD_SEL           : 2; // Bit 3-2
    unsigned short CLK_DA_CLASSD_SEL    : 2; // Bit 5-4
    unsigned short CLK_DA_LSR_SEL       : 2; // Bit 7-6
    unsigned short CLK_PCM_SEL          : 2; // Bit 9-8
    unsigned short CLK_MAIN_EN          : 1; // Bit 10
    unsigned short CLK_AD_EN            : 1; // Bit 11
    unsigned short CLK_DA_CLASSD_EN     : 1; // Bit 12
    unsigned short CLK_DA_LSR_EN        : 1; // Bit 13
    unsigned short CLK_PCM_EN           : 1; // Bit 14
  };
} CLK_CODEC_REG_type __attribute__((aligned(2)));

extern volatile CLK_CODEC_REG_type _A_CLK_CODEC_REG __attribute__((aligned(2)));

#define CLK_CODEC_CLK_MAIN_SEL         0x0003 // Bit 1-0
#define CLK_CODEC_CLK_AD_SEL           0x000C // Bit 3-2
#define CLK_CODEC_CLK_DA_CLASSD_SEL    0x0030 // Bit 5-4
#define CLK_CODEC_CLK_DA_LSR_SEL       0x00C0 // Bit 7-6
#define CLK_CODEC_CLK_PCM_SEL          0x0300 // Bit 9-8
#define CLK_CODEC_CLK_MAIN_EN          0x0400 // Bit 10
#define CLK_CODEC_CLK_AD_EN            0x0800 // Bit 11
#define CLK_CODEC_CLK_DA_CLASSD_EN     0x1000 // Bit 12
#define CLK_CODEC_CLK_DA_LSR_EN        0x2000 // Bit 13
#define CLK_CODEC_CLK_PCM_EN           0x4000 // Bit 14

/****************************************************************************
* CLK_DSP_REG
****************************************************************************/

#define CLK_DSP_REG_adr 0xFF4006
#define CLK_DSP_REG _A_CLK_DSP_REG.Value
#define CLK_DSP_REG_bit _A_CLK_DSP_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CLK_DSP_DIV          : 3; // Bit 2-0
    unsigned short CLK_DSP_EN           : 1; // Bit 3
    unsigned short                      : 3; // Bit 6-4
    unsigned short                      : 1; // Bit 7
    unsigned short CLK_DSP_TIMER_SEL    : 2; // Bit 9-8
    unsigned short CLK_DSP_TIMER_EN     : 1; // Bit 10
  };
} CLK_DSP_REG_type __attribute__((aligned(2)));

extern volatile CLK_DSP_REG_type _A_CLK_DSP_REG __attribute__((aligned(2)));

#define CLK_DSP_CLK_DSP_DIV          0x0007 // Bit 2-0
#define CLK_DSP_CLK_DSP_EN           0x0008 // Bit 3
#define CLK_DSP_CLK_DSP_TIMER_SEL    0x0300 // Bit 9-8
#define CLK_DSP_CLK_DSP_TIMER_EN     0x0400 // Bit 10

/****************************************************************************
* CLK_FREQ_TRIM_REG
****************************************************************************/

#define CLK_FREQ_TRIM_REG_adr 0xFF400A
#define CLK_FREQ_TRIM_REG _A_CLK_FREQ_TRIM_REG.Value
#define CLK_FREQ_TRIM_REG_bit _A_CLK_FREQ_TRIM_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short FINE_ADJ             : 8; // Bit 7-0
    unsigned short COARSE_ADJ           : 3; // Bit 10-8
  };
} CLK_FREQ_TRIM_REG_type __attribute__((aligned(2)));

extern volatile CLK_FREQ_TRIM_REG_type _A_CLK_FREQ_TRIM_REG __attribute__((aligned(2)));

#define CLK_FREQ_TRIM_FINE_ADJ             0x00FF // Bit 7-0
#define CLK_FREQ_TRIM_COARSE_ADJ           0x0700 // Bit 10-8

/****************************************************************************
* CLK_PER_DIV_REG
****************************************************************************/

#define CLK_PER_DIV_REG_adr 0xFF400C
#define CLK_PER_DIV_REG _A_CLK_PER_DIV_REG.Value
#define CLK_PER_DIV_REG_bit _A_CLK_PER_DIV_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PER_DIV              : 7; // Bit 6-0
    unsigned short PER_CLK_SEL          : 2; // Bit 8-7
  };
} CLK_PER_DIV_REG_type __attribute__((aligned(2)));

extern volatile CLK_PER_DIV_REG_type _A_CLK_PER_DIV_REG __attribute__((aligned(2)));

#define CLK_PER_DIV_PER_DIV              0x007F // Bit 6-0
#define CLK_PER_DIV_PER_CLK_SEL          0x0180 // Bit 8-7

/****************************************************************************
* CLK_PER10_DIV_REG
****************************************************************************/

#define CLK_PER10_DIV_REG_adr 0xFF400E
#define CLK_PER10_DIV_REG _A_CLK_PER10_DIV_REG.Value
#define CLK_PER10_DIV_REG_bit _A_CLK_PER10_DIV_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PER10_DIV            : 3; // Bit 2-0
    unsigned short PER10_CLK_SEL        : 2; // Bit 4-3
    unsigned short PER20_DIV            : 3; // Bit 7-5
    unsigned short QSPI_DIV             : 2; // Bit 9-8
  };
} CLK_PER10_DIV_REG_type __attribute__((aligned(2)));

extern volatile CLK_PER10_DIV_REG_type _A_CLK_PER10_DIV_REG __attribute__((aligned(2)));

#define CLK_PER10_DIV_PER10_DIV            0x0007 // Bit 2-0
#define CLK_PER10_DIV_PER10_CLK_SEL        0x0018 // Bit 4-3
#define CLK_PER10_DIV_PER20_DIV            0x00E0 // Bit 7-5
#define CLK_PER10_DIV_QSPI_DIV             0x0300 // Bit 9-8

/****************************************************************************
* CLK_PLL_CTRL_REG
****************************************************************************/

#define CLK_PLL_CTRL_REG_adr 0xFF4010
#define CLK_PLL_CTRL_REG _A_CLK_PLL_CTRL_REG.Value
#define CLK_PLL_CTRL_REG_bit _A_CLK_PLL_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TESTMODE_SEL         : 1; // Bit 0
    unsigned short CP_ON                : 1; // Bit 1
    unsigned short PLL_OUT_DIV          : 1; // Bit 2
    unsigned short PLL_CLK_SEL          : 1; // Bit 3
    unsigned short VCO_ON               : 1; // Bit 4
    unsigned short                      : 1; // Bit 5
    unsigned short HF_SEL               : 1; // Bit 6
    unsigned short PLL_DIP_DIV          : 4; // Bit 10-7
    unsigned short DYN_SW               : 1; // Bit 11
    unsigned short DIV2_CLK_SEL         : 1; // Bit 12
  };
} CLK_PLL_CTRL_REG_type __attribute__((aligned(2)));

extern volatile CLK_PLL_CTRL_REG_type _A_CLK_PLL_CTRL_REG __attribute__((aligned(2)));

#define CLK_PLL_CTRL_TESTMODE_SEL         0x0001 // Bit 0
#define CLK_PLL_CTRL_CP_ON                0x0002 // Bit 1
#define CLK_PLL_CTRL_PLL_OUT_DIV          0x0004 // Bit 2
#define CLK_PLL_CTRL_PLL_CLK_SEL          0x0008 // Bit 3
#define CLK_PLL_CTRL_VCO_ON               0x0010 // Bit 4
#define CLK_PLL_CTRL_HF_SEL               0x0040 // Bit 6
#define CLK_PLL_CTRL_PLL_DIP_DIV          0x0780 // Bit 10-7
#define CLK_PLL_CTRL_DYN_SW               0x0800 // Bit 11
#define CLK_PLL_CTRL_DIV2_CLK_SEL         0x1000 // Bit 12

/****************************************************************************
* CLK_PLL_DIV_REG
****************************************************************************/

#define CLK_PLL_DIV_REG_adr 0xFF4012
#define CLK_PLL_DIV_REG _A_CLK_PLL_DIV_REG.Value
#define CLK_PLL_DIV_REG_bit _A_CLK_PLL_DIV_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short XD1                  : 2; // Bit 1-0
    unsigned short VD1                  : 3; // Bit 4-2
  };
} CLK_PLL_DIV_REG_type __attribute__((aligned(2)));

extern volatile CLK_PLL_DIV_REG_type _A_CLK_PLL_DIV_REG __attribute__((aligned(2)));

#define CLK_PLL_DIV_XD1                  0x0003 // Bit 1-0
#define CLK_PLL_DIV_VD1                  0x001C // Bit 4-2

/****************************************************************************
* CLK_XTAL_CTRL_REG
****************************************************************************/

#define CLK_XTAL_CTRL_REG_adr 0xFF4018
#define CLK_XTAL_CTRL_REG _A_CLK_XTAL_CTRL_REG.Value
#define CLK_XTAL_CTRL_REG_bit _A_CLK_XTAL_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short OSC300KHZ            : 1; // Bit 0
    unsigned short XTAL_DIV             : 1; // Bit 1
  };
} CLK_XTAL_CTRL_REG_type __attribute__((aligned(2)));

extern volatile CLK_XTAL_CTRL_REG_type _A_CLK_XTAL_CTRL_REG __attribute__((aligned(2)));

#define CLK_XTAL_CTRL_OSC300KHZ            0x0001 // Bit 0
#define CLK_XTAL_CTRL_XTAL_DIV             0x0002 // Bit 1

/****************************************************************************
* CLK_AUX_REG
****************************************************************************/

#define CLK_AUX_REG_adr 0xFF401A
#define CLK_AUX_REG _A_CLK_AUX_REG.Value
#define CLK_AUX_REG_bit _A_CLK_AUX_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 3; // Bit 2-0
    unsigned short BXTAL_EN             : 2; // Bit 4-3
    unsigned short OWI_DIV              : 2; // Bit 6-5
    unsigned short OWI_SEL              : 1; // Bit 7
    unsigned short XDIV                 : 1; // Bit 8
    unsigned short                      : 1; // Bit 9
    unsigned short CP_CLK_SEL           : 1; // Bit 10
    unsigned short CLASSD_FREQ          : 2; // Bit 12-11
  };
} CLK_AUX_REG_type __attribute__((aligned(2)));

extern volatile CLK_AUX_REG_type _A_CLK_AUX_REG __attribute__((aligned(2)));

#define CLK_AUX_BXTAL_EN             0x0018 // Bit 4-3
#define CLK_AUX_OWI_DIV              0x0060 // Bit 6-5
#define CLK_AUX_OWI_SEL              0x0080 // Bit 7
#define CLK_AUX_XDIV                 0x0100 // Bit 8
#define CLK_AUX_CP_CLK_SEL           0x0400 // Bit 10
#define CLK_AUX_CLASSD_FREQ          0x1800 // Bit 12-11

/****************************************************************************
* CLK_PCM_DIV_REG
****************************************************************************/

#define CLK_PCM_DIV_REG_adr 0xFF401C
#define CLK_PCM_DIV_REG _A_CLK_PCM_DIV_REG.Value
#define CLK_PCM_DIV_REG_bit _A_CLK_PCM_DIV_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PCM_DIV              : 7; // Bit 6-0
    unsigned short PCM_CLK_SEL          : 2; // Bit 8-7
    unsigned short                      : 4; // Bit 12-9
  };
} CLK_PCM_DIV_REG_type __attribute__((aligned(2)));

extern volatile CLK_PCM_DIV_REG_type _A_CLK_PCM_DIV_REG __attribute__((aligned(2)));

#define CLK_PCM_DIV_PCM_DIV              0x007F // Bit 6-0
#define CLK_PCM_DIV_PCM_CLK_SEL          0x0180 // Bit 8-7

/****************************************************************************
* CLK_ULP_CTRL_REG
****************************************************************************/

#define CLK_ULP_CTRL_REG_adr 0xFF401E
#define CLK_ULP_CTRL_REG _A_CLK_ULP_CTRL_REG.Value
#define CLK_ULP_CTRL_REG_bit _A_CLK_ULP_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short XTAL_PD              : 1; // Bit 0
    unsigned short MAIN_CLK_SEL         : 1; // Bit 1
    unsigned short CLK300K_DIV          : 2; // Bit 3-2
  };
} CLK_ULP_CTRL_REG_type __attribute__((aligned(2)));

extern volatile CLK_ULP_CTRL_REG_type _A_CLK_ULP_CTRL_REG __attribute__((aligned(2)));

#define CLK_ULP_CTRL_XTAL_PD              0x0001 // Bit 0
#define CLK_ULP_CTRL_MAIN_CLK_SEL         0x0002 // Bit 1
#define CLK_ULP_CTRL_CLK300K_DIV          0x000C // Bit 3-2

/****************************************************************************
* DMA0_A_STARTL_REG
****************************************************************************/

#define DMA0_A_STARTL_REG_adr 0xFF4400
#define DMA0_A_STARTL_REG _A_DMA0_A_STARTL_REG

extern volatile unsigned short _A_DMA0_A_STARTL_REG;

/****************************************************************************
* DMA0_A_STARTH_REG
****************************************************************************/

#define DMA0_A_STARTH_REG_adr 0xFF4402
#define DMA0_A_STARTH_REG _A_DMA0_A_STARTH_REG.Value
#define DMA0_A_STARTH_REG_bit _A_DMA0_A_STARTH_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMAx_A_STARTH        : 9; // Bit 8-0
  };
} DMA0_A_STARTH_REG_type __attribute__((aligned(2)));

extern volatile DMA0_A_STARTH_REG_type _A_DMA0_A_STARTH_REG __attribute__((aligned(2)));

#define DMA0_A_STARTH_DMAx_A_STARTH        0x01FF // Bit 8-0

/****************************************************************************
* DMA0_B_STARTL_REG
****************************************************************************/

#define DMA0_B_STARTL_REG_adr 0xFF4404
#define DMA0_B_STARTL_REG _A_DMA0_B_STARTL_REG

extern volatile unsigned short _A_DMA0_B_STARTL_REG;

/****************************************************************************
* DMA0_B_STARTH_REG
****************************************************************************/

#define DMA0_B_STARTH_REG_adr 0xFF4406
#define DMA0_B_STARTH_REG _A_DMA0_B_STARTH_REG.Value
#define DMA0_B_STARTH_REG_bit _A_DMA0_B_STARTH_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMAx_B_STARTH        : 9; // Bit 8-0
  };
} DMA0_B_STARTH_REG_type __attribute__((aligned(2)));

extern volatile DMA0_B_STARTH_REG_type _A_DMA0_B_STARTH_REG __attribute__((aligned(2)));

#define DMA0_B_STARTH_DMAx_B_STARTH        0x01FF // Bit 8-0

/****************************************************************************
* DMA0_INT_REG
****************************************************************************/

#define DMA0_INT_REG_adr 0xFF4408
#define DMA0_INT_REG _A_DMA0_INT_REG

extern volatile unsigned short _A_DMA0_INT_REG;

/****************************************************************************
* DMA0_LEN_REG
****************************************************************************/

#define DMA0_LEN_REG_adr 0xFF440A
#define DMA0_LEN_REG _A_DMA0_LEN_REG

extern volatile unsigned short _A_DMA0_LEN_REG;

/****************************************************************************
* DMA0_CTRL_REG
****************************************************************************/

#define DMA0_CTRL_REG_adr 0xFF440C
#define DMA0_CTRL_REG _A_DMA0_CTRL_REG.Value
#define DMA0_CTRL_REG_bit _A_DMA0_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMA_ON               : 1; // Bit 0
    unsigned short BW                   : 2; // Bit 2-1
    unsigned short DINT_MODE            : 1; // Bit 3
    unsigned short DREQ_MODE            : 1; // Bit 4
    unsigned short BINC                 : 1; // Bit 5
    unsigned short AINC                 : 1; // Bit 6
    unsigned short CIRCULAR             : 1; // Bit 7
    unsigned short DMA_PRIO             : 2; // Bit 9-8
    unsigned short DMA_IDLE             : 1; // Bit 10
    unsigned short DMA_INIT             : 1; // Bit 11
  };
} DMA0_CTRL_REG_type __attribute__((aligned(2)));

extern volatile DMA0_CTRL_REG_type _A_DMA0_CTRL_REG __attribute__((aligned(2)));

#define DMA0_CTRL_DMA_ON               0x0001 // Bit 0
#define DMA0_CTRL_BW                   0x0006 // Bit 2-1
#define DMA0_CTRL_DINT_MODE            0x0008 // Bit 3
#define DMA0_CTRL_DREQ_MODE            0x0010 // Bit 4
#define DMA0_CTRL_BINC                 0x0020 // Bit 5
#define DMA0_CTRL_AINC                 0x0040 // Bit 6
#define DMA0_CTRL_CIRCULAR             0x0080 // Bit 7
#define DMA0_CTRL_DMA_PRIO             0x0300 // Bit 9-8
#define DMA0_CTRL_DMA_IDLE             0x0400 // Bit 10
#define DMA0_CTRL_DMA_INIT             0x0800 // Bit 11

/****************************************************************************
* DMA0_IDX_REG
****************************************************************************/

#define DMA0_IDX_REG_adr 0xFF440E
#define DMA0_IDX_REG _A_DMA0_IDX_REG

extern volatile unsigned short _A_DMA0_IDX_REG;

/****************************************************************************
* DMA1_A_STARTL_REG
****************************************************************************/

#define DMA1_A_STARTL_REG_adr 0xFF4410
#define DMA1_A_STARTL_REG _A_DMA1_A_STARTL_REG

extern volatile unsigned short _A_DMA1_A_STARTL_REG;

/****************************************************************************
* DMA1_A_STARTH_REG
****************************************************************************/

#define DMA1_A_STARTH_REG_adr 0xFF4412
#define DMA1_A_STARTH_REG _A_DMA1_A_STARTH_REG.Value
#define DMA1_A_STARTH_REG_bit _A_DMA1_A_STARTH_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMAx_A_STARTH        : 9; // Bit 8-0
  };
} DMA1_A_STARTH_REG_type __attribute__((aligned(2)));

extern volatile DMA1_A_STARTH_REG_type _A_DMA1_A_STARTH_REG __attribute__((aligned(2)));

#define DMA1_A_STARTH_DMAx_A_STARTH        0x01FF // Bit 8-0

/****************************************************************************
* DMA1_B_STARTL_REG
****************************************************************************/

#define DMA1_B_STARTL_REG_adr 0xFF4414
#define DMA1_B_STARTL_REG _A_DMA1_B_STARTL_REG

extern volatile unsigned short _A_DMA1_B_STARTL_REG;

/****************************************************************************
* DMA1_B_STARTH_REG
****************************************************************************/

#define DMA1_B_STARTH_REG_adr 0xFF4416
#define DMA1_B_STARTH_REG _A_DMA1_B_STARTH_REG.Value
#define DMA1_B_STARTH_REG_bit _A_DMA1_B_STARTH_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMAx_B_STARTH        : 9; // Bit 8-0
  };
} DMA1_B_STARTH_REG_type __attribute__((aligned(2)));

extern volatile DMA1_B_STARTH_REG_type _A_DMA1_B_STARTH_REG __attribute__((aligned(2)));

#define DMA1_B_STARTH_DMAx_B_STARTH        0x01FF // Bit 8-0

/****************************************************************************
* DMA1_INT_REG
****************************************************************************/

#define DMA1_INT_REG_adr 0xFF4418
#define DMA1_INT_REG _A_DMA1_INT_REG

extern volatile unsigned short _A_DMA1_INT_REG;

/****************************************************************************
* DMA1_LEN_REG
****************************************************************************/

#define DMA1_LEN_REG_adr 0xFF441A
#define DMA1_LEN_REG _A_DMA1_LEN_REG

extern volatile unsigned short _A_DMA1_LEN_REG;

/****************************************************************************
* DMA1_CTRL_REG
****************************************************************************/

#define DMA1_CTRL_REG_adr 0xFF441C
#define DMA1_CTRL_REG _A_DMA1_CTRL_REG.Value
#define DMA1_CTRL_REG_bit _A_DMA1_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMA_ON               : 1; // Bit 0
    unsigned short BW                   : 2; // Bit 2-1
    unsigned short DINT_MODE            : 1; // Bit 3
    unsigned short DREQ_MODE            : 1; // Bit 4
    unsigned short BINC                 : 1; // Bit 5
    unsigned short AINC                 : 1; // Bit 6
    unsigned short CIRCULAR             : 1; // Bit 7
    unsigned short DMA_PRIO             : 2; // Bit 9-8
    unsigned short DMA_IDLE             : 1; // Bit 10
    unsigned short DMA_INIT             : 1; // Bit 11
  };
} DMA1_CTRL_REG_type __attribute__((aligned(2)));

extern volatile DMA1_CTRL_REG_type _A_DMA1_CTRL_REG __attribute__((aligned(2)));

#define DMA1_CTRL_DMA_ON               0x0001 // Bit 0
#define DMA1_CTRL_BW                   0x0006 // Bit 2-1
#define DMA1_CTRL_DINT_MODE            0x0008 // Bit 3
#define DMA1_CTRL_DREQ_MODE            0x0010 // Bit 4
#define DMA1_CTRL_BINC                 0x0020 // Bit 5
#define DMA1_CTRL_AINC                 0x0040 // Bit 6
#define DMA1_CTRL_CIRCULAR             0x0080 // Bit 7
#define DMA1_CTRL_DMA_PRIO             0x0300 // Bit 9-8
#define DMA1_CTRL_DMA_IDLE             0x0400 // Bit 10
#define DMA1_CTRL_DMA_INIT             0x0800 // Bit 11

/****************************************************************************
* DMA1_IDX_REG
****************************************************************************/

#define DMA1_IDX_REG_adr 0xFF441E
#define DMA1_IDX_REG _A_DMA1_IDX_REG

extern volatile unsigned short _A_DMA1_IDX_REG;

/****************************************************************************
* DMA2_A_STARTL_REG
****************************************************************************/

#define DMA2_A_STARTL_REG_adr 0xFF4420
#define DMA2_A_STARTL_REG _A_DMA2_A_STARTL_REG

extern volatile unsigned short _A_DMA2_A_STARTL_REG;

/****************************************************************************
* DMA2_A_STARTH_REG
****************************************************************************/

#define DMA2_A_STARTH_REG_adr 0xFF4422
#define DMA2_A_STARTH_REG _A_DMA2_A_STARTH_REG.Value
#define DMA2_A_STARTH_REG_bit _A_DMA2_A_STARTH_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMAx_A_STARTH        : 9; // Bit 8-0
  };
} DMA2_A_STARTH_REG_type __attribute__((aligned(2)));

extern volatile DMA2_A_STARTH_REG_type _A_DMA2_A_STARTH_REG __attribute__((aligned(2)));

#define DMA2_A_STARTH_DMAx_A_STARTH        0x01FF // Bit 8-0

/****************************************************************************
* DMA2_B_STARTL_REG
****************************************************************************/

#define DMA2_B_STARTL_REG_adr 0xFF4424
#define DMA2_B_STARTL_REG _A_DMA2_B_STARTL_REG

extern volatile unsigned short _A_DMA2_B_STARTL_REG;

/****************************************************************************
* DMA2_B_STARTH_REG
****************************************************************************/

#define DMA2_B_STARTH_REG_adr 0xFF4426
#define DMA2_B_STARTH_REG _A_DMA2_B_STARTH_REG.Value
#define DMA2_B_STARTH_REG_bit _A_DMA2_B_STARTH_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMAx_B_STARTH        : 9; // Bit 8-0
  };
} DMA2_B_STARTH_REG_type __attribute__((aligned(2)));

extern volatile DMA2_B_STARTH_REG_type _A_DMA2_B_STARTH_REG __attribute__((aligned(2)));

#define DMA2_B_STARTH_DMAx_B_STARTH        0x01FF // Bit 8-0

/****************************************************************************
* DMA2_INT_REG
****************************************************************************/

#define DMA2_INT_REG_adr 0xFF4428
#define DMA2_INT_REG _A_DMA2_INT_REG

extern volatile unsigned short _A_DMA2_INT_REG;

/****************************************************************************
* DMA2_LEN_REG
****************************************************************************/

#define DMA2_LEN_REG_adr 0xFF442A
#define DMA2_LEN_REG _A_DMA2_LEN_REG

extern volatile unsigned short _A_DMA2_LEN_REG;

/****************************************************************************
* DMA2_CTRL_REG
****************************************************************************/

#define DMA2_CTRL_REG_adr 0xFF442C
#define DMA2_CTRL_REG _A_DMA2_CTRL_REG.Value
#define DMA2_CTRL_REG_bit _A_DMA2_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMA_ON               : 1; // Bit 0
    unsigned short BW                   : 2; // Bit 2-1
    unsigned short DINT_MODE            : 1; // Bit 3
    unsigned short DREQ_MODE            : 1; // Bit 4
    unsigned short BINC                 : 1; // Bit 5
    unsigned short AINC                 : 1; // Bit 6
    unsigned short CIRCULAR             : 1; // Bit 7
    unsigned short DMA_PRIO             : 2; // Bit 9-8
    unsigned short DMA_IDLE             : 1; // Bit 10
    unsigned short DMA_INIT             : 1; // Bit 11
  };
} DMA2_CTRL_REG_type __attribute__((aligned(2)));

extern volatile DMA2_CTRL_REG_type _A_DMA2_CTRL_REG __attribute__((aligned(2)));

#define DMA2_CTRL_DMA_ON               0x0001 // Bit 0
#define DMA2_CTRL_BW                   0x0006 // Bit 2-1
#define DMA2_CTRL_DINT_MODE            0x0008 // Bit 3
#define DMA2_CTRL_DREQ_MODE            0x0010 // Bit 4
#define DMA2_CTRL_BINC                 0x0020 // Bit 5
#define DMA2_CTRL_AINC                 0x0040 // Bit 6
#define DMA2_CTRL_CIRCULAR             0x0080 // Bit 7
#define DMA2_CTRL_DMA_PRIO             0x0300 // Bit 9-8
#define DMA2_CTRL_DMA_IDLE             0x0400 // Bit 10
#define DMA2_CTRL_DMA_INIT             0x0800 // Bit 11

/****************************************************************************
* DMA2_IDX_REG
****************************************************************************/

#define DMA2_IDX_REG_adr 0xFF442E
#define DMA2_IDX_REG _A_DMA2_IDX_REG

extern volatile unsigned short _A_DMA2_IDX_REG;

/****************************************************************************
* DMA3_A_STARTL_REG
****************************************************************************/

#define DMA3_A_STARTL_REG_adr 0xFF4430
#define DMA3_A_STARTL_REG _A_DMA3_A_STARTL_REG

extern volatile unsigned short _A_DMA3_A_STARTL_REG;

/****************************************************************************
* DMA3_A_STARTH_REG
****************************************************************************/

#define DMA3_A_STARTH_REG_adr 0xFF4432
#define DMA3_A_STARTH_REG _A_DMA3_A_STARTH_REG.Value
#define DMA3_A_STARTH_REG_bit _A_DMA3_A_STARTH_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMAx_A_STARTH        : 9; // Bit 8-0
  };
} DMA3_A_STARTH_REG_type __attribute__((aligned(2)));

extern volatile DMA3_A_STARTH_REG_type _A_DMA3_A_STARTH_REG __attribute__((aligned(2)));

#define DMA3_A_STARTH_DMAx_A_STARTH        0x01FF // Bit 8-0

/****************************************************************************
* DMA3_B_STARTL_REG
****************************************************************************/

#define DMA3_B_STARTL_REG_adr 0xFF4434
#define DMA3_B_STARTL_REG _A_DMA3_B_STARTL_REG

extern volatile unsigned short _A_DMA3_B_STARTL_REG;

/****************************************************************************
* DMA3_B_STARTH_REG
****************************************************************************/

#define DMA3_B_STARTH_REG_adr 0xFF4436
#define DMA3_B_STARTH_REG _A_DMA3_B_STARTH_REG.Value
#define DMA3_B_STARTH_REG_bit _A_DMA3_B_STARTH_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMAx_B_STARTH        : 9; // Bit 8-0
  };
} DMA3_B_STARTH_REG_type __attribute__((aligned(2)));

extern volatile DMA3_B_STARTH_REG_type _A_DMA3_B_STARTH_REG __attribute__((aligned(2)));

#define DMA3_B_STARTH_DMAx_B_STARTH        0x01FF // Bit 8-0

/****************************************************************************
* DMA3_INT_REG
****************************************************************************/

#define DMA3_INT_REG_adr 0xFF4438
#define DMA3_INT_REG _A_DMA3_INT_REG

extern volatile unsigned short _A_DMA3_INT_REG;

/****************************************************************************
* DMA3_LEN_REG
****************************************************************************/

#define DMA3_LEN_REG_adr 0xFF443A
#define DMA3_LEN_REG _A_DMA3_LEN_REG

extern volatile unsigned short _A_DMA3_LEN_REG;

/****************************************************************************
* DMA3_CTRL_REG
****************************************************************************/

#define DMA3_CTRL_REG_adr 0xFF443C
#define DMA3_CTRL_REG _A_DMA3_CTRL_REG.Value
#define DMA3_CTRL_REG_bit _A_DMA3_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DMA_ON               : 1; // Bit 0
    unsigned short BW                   : 2; // Bit 2-1
    unsigned short DINT_MODE            : 1; // Bit 3
    unsigned short DREQ_MODE            : 1; // Bit 4
    unsigned short BINC                 : 1; // Bit 5
    unsigned short AINC                 : 1; // Bit 6
    unsigned short CIRCULAR             : 1; // Bit 7
    unsigned short DMA_PRIO             : 2; // Bit 9-8
    unsigned short DMA_IDLE             : 1; // Bit 10
    unsigned short DMA_INIT             : 1; // Bit 11
  };
} DMA3_CTRL_REG_type __attribute__((aligned(2)));

extern volatile DMA3_CTRL_REG_type _A_DMA3_CTRL_REG __attribute__((aligned(2)));

#define DMA3_CTRL_DMA_ON               0x0001 // Bit 0
#define DMA3_CTRL_BW                   0x0006 // Bit 2-1
#define DMA3_CTRL_DINT_MODE            0x0008 // Bit 3
#define DMA3_CTRL_DREQ_MODE            0x0010 // Bit 4
#define DMA3_CTRL_BINC                 0x0020 // Bit 5
#define DMA3_CTRL_AINC                 0x0040 // Bit 6
#define DMA3_CTRL_CIRCULAR             0x0080 // Bit 7
#define DMA3_CTRL_DMA_PRIO             0x0300 // Bit 9-8
#define DMA3_CTRL_DMA_IDLE             0x0400 // Bit 10
#define DMA3_CTRL_DMA_INIT             0x0800 // Bit 11

/****************************************************************************
* DMA3_IDX_REG
****************************************************************************/

#define DMA3_IDX_REG_adr 0xFF443E
#define DMA3_IDX_REG _A_DMA3_IDX_REG

extern volatile unsigned short _A_DMA3_IDX_REG;

/****************************************************************************
* TEST_ENV_REG
****************************************************************************/

#define TEST_ENV_REG_adr 0xFF4800
#define TEST_ENV_REG _A_TEST_ENV_REG.Value
#define TEST_ENV_REG_bit _A_TEST_ENV_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short BOOT                 : 1; // Bit 0
    unsigned short                      : 1; // Bit 1
    unsigned short ENV_SDI_W            : 1; // Bit 2
    unsigned short                      : 1; // Bit 3
    unsigned short ENV_SDI              : 1; // Bit 4
    unsigned short ENV_REG7_5           : 3; // Bit 7-5
  };
} TEST_ENV_REG_type __attribute__((aligned(2)));

extern volatile TEST_ENV_REG_type _A_TEST_ENV_REG __attribute__((aligned(2)));

#define TEST_ENV_BOOT                 0x0001 // Bit 0
#define TEST_ENV_ENV_SDI_W            0x0004 // Bit 2
#define TEST_ENV_ENV_SDI              0x0010 // Bit 4
#define TEST_ENV_ENV_REG7_5           0x00E0 // Bit 7-5

/****************************************************************************
* TEST_CTRL_REG
****************************************************************************/

#define TEST_CTRL_REG_adr 0xFF4802
#define TEST_CTRL_REG _A_TEST_CTRL_REG.Value
#define TEST_CTRL_REG_bit _A_TEST_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 13; // Bit 12-0
    unsigned short QSPI_HIZ             : 1; // Bit 13
  };
} TEST_CTRL_REG_type __attribute__((aligned(2)));

extern volatile TEST_CTRL_REG_type _A_TEST_CTRL_REG __attribute__((aligned(2)));

#define TEST_CTRL_QSPI_HIZ             0x2000 // Bit 13

/****************************************************************************
* TEST_CTRL2_REG
****************************************************************************/

#define TEST_CTRL2_REG_adr 0xFF4804
#define TEST_CTRL2_REG _A_TEST_CTRL2_REG.Value
#define TEST_CTRL2_REG_bit _A_TEST_CTRL2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 1; // Bit 0
    unsigned short T2_FRZ_DIS           : 1; // Bit 1
    unsigned short BXTAL_DIV            : 1; // Bit 2
  };
} TEST_CTRL2_REG_type __attribute__((aligned(2)));

extern volatile TEST_CTRL2_REG_type _A_TEST_CTRL2_REG __attribute__((aligned(2)));

#define TEST_CTRL2_T2_FRZ_DIS           0x0002 // Bit 1
#define TEST_CTRL2_BXTAL_DIV            0x0004 // Bit 2

/****************************************************************************
* TEST_CTRL3_REG
****************************************************************************/

#define TEST_CTRL3_REG_adr 0xFF4806
#define TEST_CTRL3_REG _A_TEST_CTRL3_REG

extern volatile unsigned short _A_TEST_CTRL3_REG;

/****************************************************************************
* TEST_CTRL4_REG
****************************************************************************/

#define TEST_CTRL4_REG_adr 0xFF4808
#define TEST_CTRL4_REG _A_TEST_CTRL4_REG

extern volatile unsigned short _A_TEST_CTRL4_REG;

/****************************************************************************
* BANDGAP_REG
****************************************************************************/

#define BANDGAP_REG_adr 0xFF4810
#define BANDGAP_REG _A_BANDGAP_REG.Value
#define BANDGAP_REG_bit _A_BANDGAP_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short BANDGAP_VI           : 4; // Bit 3-0
    unsigned short BANDGAP_VIT          : 2; // Bit 5-4
    unsigned short BANDGAP_I            : 3; // Bit 8-6
  };
} BANDGAP_REG_type __attribute__((aligned(2)));

extern volatile BANDGAP_REG_type _A_BANDGAP_REG __attribute__((aligned(2)));

#define BANDGAP_BANDGAP_VI           0x000F // Bit 3-0
#define BANDGAP_BANDGAP_VIT          0x0030 // Bit 5-4
#define BANDGAP_BANDGAP_I            0x01C0 // Bit 8-6

/****************************************************************************
* BAT_CTRL_REG
****************************************************************************/

#define BAT_CTRL_REG_adr 0xFF4812
#define BAT_CTRL_REG _A_BAT_CTRL_REG.Value
#define BAT_CTRL_REG_bit _A_BAT_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short REG_ON               : 1; // Bit 0
    unsigned short LDORF_ON             : 1; // Bit 1
    unsigned short LDORF_LEVEL          : 2; // Bit 3-2
    unsigned short VBATC_LEVEL          : 2; // Bit 5-4
    unsigned short VBATC_OUTPUT         : 1; // Bit 6
    unsigned short DC_ON                : 2; // Bit 8-7
    unsigned short DC_MODE_2            : 2; // Bit 10-9
    unsigned short DC_HYST              : 1; // Bit 11
    unsigned short DC_MODE_1            : 1; // Bit 12
    unsigned short DC_FREQ              : 2; // Bit 14-13
    unsigned short DC_CLK_SEL           : 1; // Bit 15
  };
} BAT_CTRL_REG_type __attribute__((aligned(2)));

extern volatile BAT_CTRL_REG_type _A_BAT_CTRL_REG __attribute__((aligned(2)));

#define BAT_CTRL_REG_ON               0x0001 // Bit 0
#define BAT_CTRL_LDORF_ON             0x0002 // Bit 1
#define BAT_CTRL_LDORF_LEVEL          0x000C // Bit 3-2
#define BAT_CTRL_VBATC_LEVEL          0x0030 // Bit 5-4
#define BAT_CTRL_VBATC_OUTPUT         0x0040 // Bit 6
#define BAT_CTRL_DC_ON                0x0180 // Bit 8-7
#define BAT_CTRL_DC_MODE_2            0x0600 // Bit 10-9
#define BAT_CTRL_DC_HYST              0x0800 // Bit 11
#define BAT_CTRL_DC_MODE_1            0x1000 // Bit 12
#define BAT_CTRL_DC_FREQ              0x6000 // Bit 14-13
#define BAT_CTRL_DC_CLK_SEL           0x8000 // Bit 15

/****************************************************************************
* BAT_CTRL2_REG
****************************************************************************/

#define BAT_CTRL2_REG_adr 0xFF4814
#define BAT_CTRL2_REG _A_BAT_CTRL2_REG.Value
#define BAT_CTRL2_REG_bit _A_BAT_CTRL2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CHARGE_LEVEL         : 5; // Bit 4-0
    unsigned short CHARGE_ON            : 1; // Bit 5
    unsigned short NTC_DISABLE          : 1; // Bit 6
    unsigned short ONE_CELL             : 1; // Bit 7
    unsigned short CHARGE_CUR           : 3; // Bit 10-8
    unsigned short SOC_ON               : 1; // Bit 11
    unsigned short SOC_CAL              : 1; // Bit 12
    unsigned short SOC_TEST1            : 1; // Bit 13
    unsigned short SOC_TEST2            : 1; // Bit 14
    unsigned short STATUS_MODE          : 1; // Bit 15
  };
} BAT_CTRL2_REG_type __attribute__((aligned(2)));

extern volatile BAT_CTRL2_REG_type _A_BAT_CTRL2_REG __attribute__((aligned(2)));

#define BAT_CTRL2_CHARGE_LEVEL         0x001F // Bit 4-0
#define BAT_CTRL2_CHARGE_ON            0x0020 // Bit 5
#define BAT_CTRL2_NTC_DISABLE          0x0040 // Bit 6
#define BAT_CTRL2_ONE_CELL             0x0080 // Bit 7
#define BAT_CTRL2_CHARGE_CUR           0x0700 // Bit 10-8
#define BAT_CTRL2_SOC_ON               0x0800 // Bit 11
#define BAT_CTRL2_SOC_CAL              0x1000 // Bit 12
#define BAT_CTRL2_SOC_TEST1            0x2000 // Bit 13
#define BAT_CTRL2_SOC_TEST2            0x4000 // Bit 14
#define BAT_CTRL2_STATUS_MODE          0x8000 // Bit 15

/****************************************************************************
* BAT_STATUS_REG
****************************************************************************/

#define BAT_STATUS_REG_adr 0xFF4816
#define BAT_STATUS_REG _A_BAT_STATUS_REG.Value
#define BAT_STATUS_REG_bit _A_BAT_STATUS_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short VBAT3_STS            : 1; // Bit 0
    unsigned short PON_STS              : 1; // Bit 1
    unsigned short CHARGE_STS           : 1; // Bit 2
    unsigned short CHARGE_I_LIMIT       : 1; // Bit 3
  };
} BAT_STATUS_REG_type __attribute__((aligned(2)));

extern volatile BAT_STATUS_REG_type _A_BAT_STATUS_REG __attribute__((aligned(2)));

#define BAT_STATUS_VBAT3_STS            0x0001 // Bit 0
#define BAT_STATUS_PON_STS              0x0002 // Bit 1
#define BAT_STATUS_CHARGE_STS           0x0004 // Bit 2
#define BAT_STATUS_CHARGE_I_LIMIT       0x0008 // Bit 3

/****************************************************************************
* BAT_SOC_HIGH_REG
****************************************************************************/

#define BAT_SOC_HIGH_REG_adr 0xFF4818
#define BAT_SOC_HIGH_REG _A_BAT_SOC_HIGH_REG

extern volatile unsigned short _A_BAT_SOC_HIGH_REG;

/****************************************************************************
* BAT_SOC_LOW_REG
****************************************************************************/

#define BAT_SOC_LOW_REG_adr 0xFF481A
#define BAT_SOC_LOW_REG _A_BAT_SOC_LOW_REG

extern volatile unsigned short _A_BAT_SOC_LOW_REG;

/****************************************************************************
* CP_CTRL_REG
****************************************************************************/

#define CP_CTRL_REG_adr 0xFF481C
#define CP_CTRL_REG _A_CP_CTRL_REG.Value
#define CP_CTRL_REG_bit _A_CP_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CP_EN                : 2; // Bit 1-0
    unsigned short CP_LEVEL1            : 2; // Bit 3-2
    unsigned short CP_LEVEL2            : 2; // Bit 5-4
    unsigned short CP_PWM1              : 1; // Bit 6
    unsigned short CP_PWM2              : 1; // Bit 7
    unsigned short CP_FREQ              : 2; // Bit 9-8
    unsigned short CP_PARALLEL          : 1; // Bit 10
    unsigned short CP_MODE              : 1; // Bit 11
    unsigned short CP_TEST_ADC1         : 1; // Bit 12
    unsigned short CP_TEST_ADC2         : 1; // Bit 13
    unsigned short CP_FORCE_MODE        : 2; // Bit 15-14
  };
} CP_CTRL_REG_type __attribute__((aligned(2)));

extern volatile CP_CTRL_REG_type _A_CP_CTRL_REG __attribute__((aligned(2)));

#define CP_CTRL_CP_EN                0x0003 // Bit 1-0
#define CP_CTRL_CP_LEVEL1            0x000C // Bit 3-2
#define CP_CTRL_CP_LEVEL2            0x0030 // Bit 5-4
#define CP_CTRL_CP_PWM1              0x0040 // Bit 6
#define CP_CTRL_CP_PWM2              0x0080 // Bit 7
#define CP_CTRL_CP_FREQ              0x0300 // Bit 9-8
#define CP_CTRL_CP_PARALLEL          0x0400 // Bit 10
#define CP_CTRL_CP_MODE              0x0800 // Bit 11
#define CP_CTRL_CP_TEST_ADC1         0x1000 // Bit 12
#define CP_CTRL_CP_TEST_ADC2         0x2000 // Bit 13
#define CP_CTRL_CP_FORCE_MODE        0xC000 // Bit 15-14

/****************************************************************************
* PAD_CTRL_REG
****************************************************************************/

#define PAD_CTRL_REG_adr 0xFF481E
#define PAD_CTRL_REG _A_PAD_CTRL_REG.Value
#define PAD_CTRL_REG_bit _A_PAD_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short P04567_OD            : 1; // Bit 0
    unsigned short P023_OD              : 1; // Bit 1
    unsigned short P001_OD              : 1; // Bit 2
    unsigned short P27_OD               : 1; // Bit 3
    unsigned short P225_OD              : 1; // Bit 4
    unsigned short P234_OD              : 1; // Bit 5
    unsigned short P21_OD               : 1; // Bit 6
    unsigned short P20_OD               : 1; // Bit 7
    unsigned short LED3_CUR             : 1; // Bit 8
    unsigned short LED4_CUR             : 1; // Bit 9
    unsigned short P4_OD                : 1; // Bit 10
    unsigned short P5_OD                : 1; // Bit 11
    unsigned short LED3_PWM             : 1; // Bit 12
    unsigned short LED4_PWM             : 1; // Bit 13
    unsigned short LED34_C_MODE         : 1; // Bit 14
  };
} PAD_CTRL_REG_type __attribute__((aligned(2)));

extern volatile PAD_CTRL_REG_type _A_PAD_CTRL_REG __attribute__((aligned(2)));

#define PAD_CTRL_P04567_OD            0x0001 // Bit 0
#define PAD_CTRL_P023_OD              0x0002 // Bit 1
#define PAD_CTRL_P001_OD              0x0004 // Bit 2
#define PAD_CTRL_P27_OD               0x0008 // Bit 3
#define PAD_CTRL_P225_OD              0x0010 // Bit 4
#define PAD_CTRL_P234_OD              0x0020 // Bit 5
#define PAD_CTRL_P21_OD               0x0040 // Bit 6
#define PAD_CTRL_P20_OD               0x0080 // Bit 7
#define PAD_CTRL_LED3_CUR             0x0100 // Bit 8
#define PAD_CTRL_LED4_CUR             0x0200 // Bit 9
#define PAD_CTRL_P4_OD                0x0400 // Bit 10
#define PAD_CTRL_P5_OD                0x0800 // Bit 11
#define PAD_CTRL_LED3_PWM             0x1000 // Bit 12
#define PAD_CTRL_LED4_PWM             0x2000 // Bit 13
#define PAD_CTRL_LED34_C_MODE         0x4000 // Bit 14

/****************************************************************************
* LED_CTRL_REG
****************************************************************************/

#define LED_CTRL_REG_adr 0xFF4820
#define LED_CTRL_REG _A_LED_CTRL_REG.Value
#define LED_CTRL_REG_bit _A_LED_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short WLED_CUR0            : 2; // Bit 1-0
    unsigned short WLED_CUR1            : 2; // Bit 3-2
    unsigned short WLED_CUR2            : 2; // Bit 5-4
    unsigned short WLED0_PWM            : 1; // Bit 6
    unsigned short WLED1_PWM            : 1; // Bit 7
    unsigned short WLED2_PWM            : 1; // Bit 8
    unsigned short WLED_PWM_CTRL        : 1; // Bit 9
  };
} LED_CTRL_REG_type __attribute__((aligned(2)));

extern volatile LED_CTRL_REG_type _A_LED_CTRL_REG __attribute__((aligned(2)));

#define LED_CTRL_WLED_CUR0            0x0003 // Bit 1-0
#define LED_CTRL_WLED_CUR1            0x000C // Bit 3-2
#define LED_CTRL_WLED_CUR2            0x0030 // Bit 5-4
#define LED_CTRL_WLED0_PWM            0x0040 // Bit 6
#define LED_CTRL_WLED1_PWM            0x0080 // Bit 7
#define LED_CTRL_WLED2_PWM            0x0100 // Bit 8
#define LED_CTRL_WLED_PWM_CTRL        0x0200 // Bit 9

/****************************************************************************
* P0_DATA_REG
****************************************************************************/

#define P0_DATA_REG_adr 0xFF4830
#define P0_DATA_REG _A_P0_DATA_REG.Value
#define P0_DATA_REG_bit _A_P0_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_DATA            : 1; // Bit 0
    unsigned short Px_1_DATA            : 1; // Bit 1
    unsigned short Px_2_DATA            : 1; // Bit 2
    unsigned short Px_3_DATA            : 1; // Bit 3
    unsigned short Px_4_DATA            : 1; // Bit 4
    unsigned short Px_5_DATA            : 1; // Bit 5
    unsigned short Px_6_DATA            : 1; // Bit 6
    unsigned short Px_7_DATA            : 1; // Bit 7
  };
} P0_DATA_REG_type __attribute__((aligned(2)));

extern volatile P0_DATA_REG_type _A_P0_DATA_REG __attribute__((aligned(2)));

#define P0_DATA_Px_0_DATA            0x0001 // Bit 0
#define P0_DATA_Px_1_DATA            0x0002 // Bit 1
#define P0_DATA_Px_2_DATA            0x0004 // Bit 2
#define P0_DATA_Px_3_DATA            0x0008 // Bit 3
#define P0_DATA_Px_4_DATA            0x0010 // Bit 4
#define P0_DATA_Px_5_DATA            0x0020 // Bit 5
#define P0_DATA_Px_6_DATA            0x0040 // Bit 6
#define P0_DATA_Px_7_DATA            0x0080 // Bit 7

/****************************************************************************
* P0_SET_DATA_REG
****************************************************************************/

#define P0_SET_DATA_REG_adr 0xFF4832
#define P0_SET_DATA_REG _A_P0_SET_DATA_REG.Value
#define P0_SET_DATA_REG_bit _A_P0_SET_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_SET             : 1; // Bit 0
    unsigned short Px_1_SET             : 1; // Bit 1
    unsigned short Px_2_SET             : 1; // Bit 2
    unsigned short Px_3_SET             : 1; // Bit 3
    unsigned short Px_4_SET             : 1; // Bit 4
    unsigned short Px_5_SET             : 1; // Bit 5
    unsigned short Px_6_SET             : 1; // Bit 6
    unsigned short Px_7_SET             : 1; // Bit 7
  };
} P0_SET_DATA_REG_type __attribute__((aligned(2)));

extern volatile P0_SET_DATA_REG_type _A_P0_SET_DATA_REG __attribute__((aligned(2)));

#define P0_SET_DATA_Px_0_SET             0x0001 // Bit 0
#define P0_SET_DATA_Px_1_SET             0x0002 // Bit 1
#define P0_SET_DATA_Px_2_SET             0x0004 // Bit 2
#define P0_SET_DATA_Px_3_SET             0x0008 // Bit 3
#define P0_SET_DATA_Px_4_SET             0x0010 // Bit 4
#define P0_SET_DATA_Px_5_SET             0x0020 // Bit 5
#define P0_SET_DATA_Px_6_SET             0x0040 // Bit 6
#define P0_SET_DATA_Px_7_SET             0x0080 // Bit 7

/****************************************************************************
* P0_RESET_DATA_REG
****************************************************************************/

#define P0_RESET_DATA_REG_adr 0xFF4834
#define P0_RESET_DATA_REG _A_P0_RESET_DATA_REG.Value
#define P0_RESET_DATA_REG_bit _A_P0_RESET_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_RESET           : 1; // Bit 0
    unsigned short Px_1_RESET           : 1; // Bit 1
    unsigned short Px_2_RESET           : 1; // Bit 2
    unsigned short Px_3_RESET           : 1; // Bit 3
    unsigned short Px_4_RESET           : 1; // Bit 4
    unsigned short Px_5_RESET           : 1; // Bit 5
    unsigned short Px_6_RESET           : 1; // Bit 6
    unsigned short Px_7_RESET           : 1; // Bit 7
  };
} P0_RESET_DATA_REG_type __attribute__((aligned(2)));

extern volatile P0_RESET_DATA_REG_type _A_P0_RESET_DATA_REG __attribute__((aligned(2)));

#define P0_RESET_DATA_Px_0_RESET           0x0001 // Bit 0
#define P0_RESET_DATA_Px_1_RESET           0x0002 // Bit 1
#define P0_RESET_DATA_Px_2_RESET           0x0004 // Bit 2
#define P0_RESET_DATA_Px_3_RESET           0x0008 // Bit 3
#define P0_RESET_DATA_Px_4_RESET           0x0010 // Bit 4
#define P0_RESET_DATA_Px_5_RESET           0x0020 // Bit 5
#define P0_RESET_DATA_Px_6_RESET           0x0040 // Bit 6
#define P0_RESET_DATA_Px_7_RESET           0x0080 // Bit 7

/****************************************************************************
* P0_DIR_REG
****************************************************************************/

#define P0_DIR_REG_adr 0xFF4836
#define P0_DIR_REG _A_P0_DIR_REG.Value
#define P0_DIR_REG_bit _A_P0_DIR_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_DIR             : 2; // Bit 1-0
    unsigned short Px_1_DIR             : 2; // Bit 3-2
    unsigned short Px_2_DIR             : 2; // Bit 5-4
    unsigned short Px_3_DIR             : 2; // Bit 7-6
    unsigned short Px_4_DIR             : 2; // Bit 9-8
    unsigned short Px_5_DIR             : 2; // Bit 11-10
    unsigned short Px_6_DIR             : 2; // Bit 13-12
    unsigned short Px_7_DIR             : 2; // Bit 15-14
  };
} P0_DIR_REG_type __attribute__((aligned(2)));

extern volatile P0_DIR_REG_type _A_P0_DIR_REG __attribute__((aligned(2)));

#define P0_DIR_Px_0_DIR             0x0003 // Bit 1-0
#define P0_DIR_Px_1_DIR             0x000C // Bit 3-2
#define P0_DIR_Px_2_DIR             0x0030 // Bit 5-4
#define P0_DIR_Px_3_DIR             0x00C0 // Bit 7-6
#define P0_DIR_Px_4_DIR             0x0300 // Bit 9-8
#define P0_DIR_Px_5_DIR             0x0C00 // Bit 11-10
#define P0_DIR_Px_6_DIR             0x3000 // Bit 13-12
#define P0_DIR_Px_7_DIR             0xC000 // Bit 15-14

/****************************************************************************
* P0_MODE_REG
****************************************************************************/

#define P0_MODE_REG_adr 0xFF4838
#define P0_MODE_REG _A_P0_MODE_REG.Value
#define P0_MODE_REG_bit _A_P0_MODE_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short P0_0_MODE            : 1; // Bit 0
    unsigned short P0_1_MODE            : 1; // Bit 1
    unsigned short P0_2_MODE            : 2; // Bit 3-2
    unsigned short P0_3_MODE            : 2; // Bit 5-4
    unsigned short P0_4_MODE            : 2; // Bit 7-6
    unsigned short P0_5_MODE            : 2; // Bit 9-8
    unsigned short P0_6_MODE            : 2; // Bit 11-10
    unsigned short P0_7_MODE            : 2; // Bit 13-12
  };
} P0_MODE_REG_type __attribute__((aligned(2)));

extern volatile P0_MODE_REG_type _A_P0_MODE_REG __attribute__((aligned(2)));

#define P0_MODE_P0_0_MODE            0x0001 // Bit 0
#define P0_MODE_P0_1_MODE            0x0002 // Bit 1
#define P0_MODE_P0_2_MODE            0x000C // Bit 3-2
#define P0_MODE_P0_3_MODE            0x0030 // Bit 5-4
#define P0_MODE_P0_4_MODE            0x00C0 // Bit 7-6
#define P0_MODE_P0_5_MODE            0x0300 // Bit 9-8
#define P0_MODE_P0_6_MODE            0x0C00 // Bit 11-10
#define P0_MODE_P0_7_MODE            0x3000 // Bit 13-12

/****************************************************************************
* P1_DATA_REG
****************************************************************************/

#define P1_DATA_REG_adr 0xFF4840
#define P1_DATA_REG _A_P1_DATA_REG.Value
#define P1_DATA_REG_bit _A_P1_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_DATA            : 1; // Bit 0
    unsigned short Px_1_DATA            : 1; // Bit 1
    unsigned short Px_2_DATA            : 1; // Bit 2
    unsigned short Px_3_DATA            : 1; // Bit 3
    unsigned short Px_4_DATA            : 1; // Bit 4
    unsigned short Px_5_DATA            : 1; // Bit 5
    unsigned short Px_6_DATA            : 1; // Bit 6
    unsigned short Px_7_DATA            : 1; // Bit 7
  };
} P1_DATA_REG_type __attribute__((aligned(2)));

extern volatile P1_DATA_REG_type _A_P1_DATA_REG __attribute__((aligned(2)));

#define P1_DATA_Px_0_DATA            0x0001 // Bit 0
#define P1_DATA_Px_1_DATA            0x0002 // Bit 1
#define P1_DATA_Px_2_DATA            0x0004 // Bit 2
#define P1_DATA_Px_3_DATA            0x0008 // Bit 3
#define P1_DATA_Px_4_DATA            0x0010 // Bit 4
#define P1_DATA_Px_5_DATA            0x0020 // Bit 5
#define P1_DATA_Px_6_DATA            0x0040 // Bit 6
#define P1_DATA_Px_7_DATA            0x0080 // Bit 7

/****************************************************************************
* P1_SET_DATA_REG
****************************************************************************/

#define P1_SET_DATA_REG_adr 0xFF4842
#define P1_SET_DATA_REG _A_P1_SET_DATA_REG.Value
#define P1_SET_DATA_REG_bit _A_P1_SET_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_SET             : 1; // Bit 0
    unsigned short Px_1_SET             : 1; // Bit 1
    unsigned short Px_2_SET             : 1; // Bit 2
    unsigned short Px_3_SET             : 1; // Bit 3
    unsigned short Px_4_SET             : 1; // Bit 4
    unsigned short Px_5_SET             : 1; // Bit 5
    unsigned short Px_6_SET             : 1; // Bit 6
    unsigned short Px_7_SET             : 1; // Bit 7
  };
} P1_SET_DATA_REG_type __attribute__((aligned(2)));

extern volatile P1_SET_DATA_REG_type _A_P1_SET_DATA_REG __attribute__((aligned(2)));

#define P1_SET_DATA_Px_0_SET             0x0001 // Bit 0
#define P1_SET_DATA_Px_1_SET             0x0002 // Bit 1
#define P1_SET_DATA_Px_2_SET             0x0004 // Bit 2
#define P1_SET_DATA_Px_3_SET             0x0008 // Bit 3
#define P1_SET_DATA_Px_4_SET             0x0010 // Bit 4
#define P1_SET_DATA_Px_5_SET             0x0020 // Bit 5
#define P1_SET_DATA_Px_6_SET             0x0040 // Bit 6
#define P1_SET_DATA_Px_7_SET             0x0080 // Bit 7

/****************************************************************************
* P1_RESET_DATA_REG
****************************************************************************/

#define P1_RESET_DATA_REG_adr 0xFF4844
#define P1_RESET_DATA_REG _A_P1_RESET_DATA_REG.Value
#define P1_RESET_DATA_REG_bit _A_P1_RESET_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_RESET           : 1; // Bit 0
    unsigned short Px_1_RESET           : 1; // Bit 1
    unsigned short Px_2_RESET           : 1; // Bit 2
    unsigned short Px_3_RESET           : 1; // Bit 3
    unsigned short Px_4_RESET           : 1; // Bit 4
    unsigned short Px_5_RESET           : 1; // Bit 5
    unsigned short Px_6_RESET           : 1; // Bit 6
    unsigned short Px_7_RESET           : 1; // Bit 7
  };
} P1_RESET_DATA_REG_type __attribute__((aligned(2)));

extern volatile P1_RESET_DATA_REG_type _A_P1_RESET_DATA_REG __attribute__((aligned(2)));

#define P1_RESET_DATA_Px_0_RESET           0x0001 // Bit 0
#define P1_RESET_DATA_Px_1_RESET           0x0002 // Bit 1
#define P1_RESET_DATA_Px_2_RESET           0x0004 // Bit 2
#define P1_RESET_DATA_Px_3_RESET           0x0008 // Bit 3
#define P1_RESET_DATA_Px_4_RESET           0x0010 // Bit 4
#define P1_RESET_DATA_Px_5_RESET           0x0020 // Bit 5
#define P1_RESET_DATA_Px_6_RESET           0x0040 // Bit 6
#define P1_RESET_DATA_Px_7_RESET           0x0080 // Bit 7

/****************************************************************************
* P1_DIR_REG
****************************************************************************/

#define P1_DIR_REG_adr 0xFF4846
#define P1_DIR_REG _A_P1_DIR_REG.Value
#define P1_DIR_REG_bit _A_P1_DIR_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_DIR             : 2; // Bit 1-0
    unsigned short Px_1_DIR             : 2; // Bit 3-2
    unsigned short Px_2_DIR             : 2; // Bit 5-4
    unsigned short Px_3_DIR             : 2; // Bit 7-6
    unsigned short Px_4_DIR             : 2; // Bit 9-8
    unsigned short Px_5_DIR             : 2; // Bit 11-10
    unsigned short Px_6_DIR             : 2; // Bit 13-12
    unsigned short Px_7_DIR             : 2; // Bit 15-14
  };
} P1_DIR_REG_type __attribute__((aligned(2)));

extern volatile P1_DIR_REG_type _A_P1_DIR_REG __attribute__((aligned(2)));

#define P1_DIR_Px_0_DIR             0x0003 // Bit 1-0
#define P1_DIR_Px_1_DIR             0x000C // Bit 3-2
#define P1_DIR_Px_2_DIR             0x0030 // Bit 5-4
#define P1_DIR_Px_3_DIR             0x00C0 // Bit 7-6
#define P1_DIR_Px_4_DIR             0x0300 // Bit 9-8
#define P1_DIR_Px_5_DIR             0x0C00 // Bit 11-10
#define P1_DIR_Px_6_DIR             0x3000 // Bit 13-12
#define P1_DIR_Px_7_DIR             0xC000 // Bit 15-14

/****************************************************************************
* P1_MODE_REG
****************************************************************************/

#define P1_MODE_REG_adr 0xFF4848
#define P1_MODE_REG _A_P1_MODE_REG.Value
#define P1_MODE_REG_bit _A_P1_MODE_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short P1_0_MODE            : 1; // Bit 0
    unsigned short P1_1_MODE            : 1; // Bit 1
    unsigned short P1_2_MODE            : 1; // Bit 2
    unsigned short P1_3_MODE            : 1; // Bit 3
    unsigned short P1_4_MODE            : 1; // Bit 4
    unsigned short P1_5_MODE            : 3; // Bit 7-5
    unsigned short RF_BB_MODE           : 2; // Bit 9-8
  };
} P1_MODE_REG_type __attribute__((aligned(2)));

extern volatile P1_MODE_REG_type _A_P1_MODE_REG __attribute__((aligned(2)));

#define P1_MODE_P1_0_MODE            0x0001 // Bit 0
#define P1_MODE_P1_1_MODE            0x0002 // Bit 1
#define P1_MODE_P1_2_MODE            0x0004 // Bit 2
#define P1_MODE_P1_3_MODE            0x0008 // Bit 3
#define P1_MODE_P1_4_MODE            0x0010 // Bit 4
#define P1_MODE_P1_5_MODE            0x00E0 // Bit 7-5
#define P1_MODE_RF_BB_MODE           0x0300 // Bit 9-8

/****************************************************************************
* P2_DATA_REG
****************************************************************************/

#define P2_DATA_REG_adr 0xFF4850
#define P2_DATA_REG _A_P2_DATA_REG.Value
#define P2_DATA_REG_bit _A_P2_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_DATA            : 1; // Bit 0
    unsigned short Px_1_DATA            : 1; // Bit 1
    unsigned short Px_2_DATA            : 1; // Bit 2
    unsigned short Px_3_DATA            : 1; // Bit 3
    unsigned short Px_4_DATA            : 1; // Bit 4
    unsigned short Px_5_DATA            : 1; // Bit 5
    unsigned short Px_6_DATA            : 1; // Bit 6
    unsigned short Px_7_DATA            : 1; // Bit 7
  };
} P2_DATA_REG_type __attribute__((aligned(2)));

extern volatile P2_DATA_REG_type _A_P2_DATA_REG __attribute__((aligned(2)));

#define P2_DATA_Px_0_DATA            0x0001 // Bit 0
#define P2_DATA_Px_1_DATA            0x0002 // Bit 1
#define P2_DATA_Px_2_DATA            0x0004 // Bit 2
#define P2_DATA_Px_3_DATA            0x0008 // Bit 3
#define P2_DATA_Px_4_DATA            0x0010 // Bit 4
#define P2_DATA_Px_5_DATA            0x0020 // Bit 5
#define P2_DATA_Px_6_DATA            0x0040 // Bit 6
#define P2_DATA_Px_7_DATA            0x0080 // Bit 7

/****************************************************************************
* P2_SET_DATA_REG
****************************************************************************/

#define P2_SET_DATA_REG_adr 0xFF4852
#define P2_SET_DATA_REG _A_P2_SET_DATA_REG.Value
#define P2_SET_DATA_REG_bit _A_P2_SET_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_SET             : 1; // Bit 0
    unsigned short Px_1_SET             : 1; // Bit 1
    unsigned short Px_2_SET             : 1; // Bit 2
    unsigned short Px_3_SET             : 1; // Bit 3
    unsigned short Px_4_SET             : 1; // Bit 4
    unsigned short Px_5_SET             : 1; // Bit 5
    unsigned short Px_6_SET             : 1; // Bit 6
    unsigned short Px_7_SET             : 1; // Bit 7
  };
} P2_SET_DATA_REG_type __attribute__((aligned(2)));

extern volatile P2_SET_DATA_REG_type _A_P2_SET_DATA_REG __attribute__((aligned(2)));

#define P2_SET_DATA_Px_0_SET             0x0001 // Bit 0
#define P2_SET_DATA_Px_1_SET             0x0002 // Bit 1
#define P2_SET_DATA_Px_2_SET             0x0004 // Bit 2
#define P2_SET_DATA_Px_3_SET             0x0008 // Bit 3
#define P2_SET_DATA_Px_4_SET             0x0010 // Bit 4
#define P2_SET_DATA_Px_5_SET             0x0020 // Bit 5
#define P2_SET_DATA_Px_6_SET             0x0040 // Bit 6
#define P2_SET_DATA_Px_7_SET             0x0080 // Bit 7

/****************************************************************************
* P2_RESET_DATA_REG
****************************************************************************/

#define P2_RESET_DATA_REG_adr 0xFF4854
#define P2_RESET_DATA_REG _A_P2_RESET_DATA_REG.Value
#define P2_RESET_DATA_REG_bit _A_P2_RESET_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_RESET           : 1; // Bit 0
    unsigned short Px_1_RESET           : 1; // Bit 1
    unsigned short Px_2_RESET           : 1; // Bit 2
    unsigned short Px_3_RESET           : 1; // Bit 3
    unsigned short Px_4_RESET           : 1; // Bit 4
    unsigned short Px_5_RESET           : 1; // Bit 5
    unsigned short Px_6_RESET           : 1; // Bit 6
    unsigned short Px_7_RESET           : 1; // Bit 7
  };
} P2_RESET_DATA_REG_type __attribute__((aligned(2)));

extern volatile P2_RESET_DATA_REG_type _A_P2_RESET_DATA_REG __attribute__((aligned(2)));

#define P2_RESET_DATA_Px_0_RESET           0x0001 // Bit 0
#define P2_RESET_DATA_Px_1_RESET           0x0002 // Bit 1
#define P2_RESET_DATA_Px_2_RESET           0x0004 // Bit 2
#define P2_RESET_DATA_Px_3_RESET           0x0008 // Bit 3
#define P2_RESET_DATA_Px_4_RESET           0x0010 // Bit 4
#define P2_RESET_DATA_Px_5_RESET           0x0020 // Bit 5
#define P2_RESET_DATA_Px_6_RESET           0x0040 // Bit 6
#define P2_RESET_DATA_Px_7_RESET           0x0080 // Bit 7

/****************************************************************************
* P2_DIR_REG
****************************************************************************/

#define P2_DIR_REG_adr 0xFF4856
#define P2_DIR_REG _A_P2_DIR_REG.Value
#define P2_DIR_REG_bit _A_P2_DIR_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_DIR             : 2; // Bit 1-0
    unsigned short Px_1_DIR             : 2; // Bit 3-2
    unsigned short Px_2_DIR             : 2; // Bit 5-4
    unsigned short Px_3_DIR             : 2; // Bit 7-6
    unsigned short Px_4_DIR             : 2; // Bit 9-8
    unsigned short Px_5_DIR             : 2; // Bit 11-10
    unsigned short Px_6_DIR             : 2; // Bit 13-12
    unsigned short Px_7_DIR             : 2; // Bit 15-14
  };
} P2_DIR_REG_type __attribute__((aligned(2)));

extern volatile P2_DIR_REG_type _A_P2_DIR_REG __attribute__((aligned(2)));

#define P2_DIR_Px_0_DIR             0x0003 // Bit 1-0
#define P2_DIR_Px_1_DIR             0x000C // Bit 3-2
#define P2_DIR_Px_2_DIR             0x0030 // Bit 5-4
#define P2_DIR_Px_3_DIR             0x00C0 // Bit 7-6
#define P2_DIR_Px_4_DIR             0x0300 // Bit 9-8
#define P2_DIR_Px_5_DIR             0x0C00 // Bit 11-10
#define P2_DIR_Px_6_DIR             0x3000 // Bit 13-12
#define P2_DIR_Px_7_DIR             0xC000 // Bit 15-14

/****************************************************************************
* P2_MODE_REG
****************************************************************************/

#define P2_MODE_REG_adr 0xFF4858
#define P2_MODE_REG _A_P2_MODE_REG.Value
#define P2_MODE_REG_bit _A_P2_MODE_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short P2_0_MODE            : 2; // Bit 1-0
    unsigned short P2_1_MODE            : 2; // Bit 3-2
    unsigned short P2_2_MODE            : 2; // Bit 5-4
    unsigned short P2_3_MODE            : 2; // Bit 7-6
    unsigned short P2_4_MODE            : 2; // Bit 9-8
    unsigned short P2_5_MODE            : 2; // Bit 11-10
    unsigned short INT6_MODE            : 1; // Bit 12
    unsigned short P2_6_MODE            : 1; // Bit 13
    unsigned short INT7_MODE            : 1; // Bit 14
    unsigned short P2_7_MODE            : 1; // Bit 15
  };
} P2_MODE_REG_type __attribute__((aligned(2)));

extern volatile P2_MODE_REG_type _A_P2_MODE_REG __attribute__((aligned(2)));

#define P2_MODE_P2_0_MODE            0x0003 // Bit 1-0
#define P2_MODE_P2_1_MODE            0x000C // Bit 3-2
#define P2_MODE_P2_2_MODE            0x0030 // Bit 5-4
#define P2_MODE_P2_3_MODE            0x00C0 // Bit 7-6
#define P2_MODE_P2_4_MODE            0x0300 // Bit 9-8
#define P2_MODE_P2_5_MODE            0x0C00 // Bit 11-10
#define P2_MODE_INT6_MODE            0x1000 // Bit 12
#define P2_MODE_P2_6_MODE            0x2000 // Bit 13
#define P2_MODE_INT7_MODE            0x4000 // Bit 14
#define P2_MODE_P2_7_MODE            0x8000 // Bit 15

/****************************************************************************
* P3_DATA_REG
****************************************************************************/

#define P3_DATA_REG_adr 0xFF4860
#define P3_DATA_REG _A_P3_DATA_REG.Value
#define P3_DATA_REG_bit _A_P3_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_DATA            : 1; // Bit 0
    unsigned short Px_1_DATA            : 1; // Bit 1
    unsigned short Px_2_DATA            : 1; // Bit 2
    unsigned short Px_3_DATA            : 1; // Bit 3
    unsigned short Px_4_DATA            : 1; // Bit 4
    unsigned short Px_5_DATA            : 1; // Bit 5
    unsigned short Px_6_DATA            : 1; // Bit 6
    unsigned short Px_7_DATA            : 1; // Bit 7
  };
} P3_DATA_REG_type __attribute__((aligned(2)));

extern volatile P3_DATA_REG_type _A_P3_DATA_REG __attribute__((aligned(2)));

#define P3_DATA_Px_0_DATA            0x0001 // Bit 0
#define P3_DATA_Px_1_DATA            0x0002 // Bit 1
#define P3_DATA_Px_2_DATA            0x0004 // Bit 2
#define P3_DATA_Px_3_DATA            0x0008 // Bit 3
#define P3_DATA_Px_4_DATA            0x0010 // Bit 4
#define P3_DATA_Px_5_DATA            0x0020 // Bit 5
#define P3_DATA_Px_6_DATA            0x0040 // Bit 6
#define P3_DATA_Px_7_DATA            0x0080 // Bit 7

/****************************************************************************
* P3_SET_DATA_REG
****************************************************************************/

#define P3_SET_DATA_REG_adr 0xFF4862
#define P3_SET_DATA_REG _A_P3_SET_DATA_REG.Value
#define P3_SET_DATA_REG_bit _A_P3_SET_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_SET             : 1; // Bit 0
    unsigned short Px_1_SET             : 1; // Bit 1
    unsigned short Px_2_SET             : 1; // Bit 2
    unsigned short Px_3_SET             : 1; // Bit 3
    unsigned short Px_4_SET             : 1; // Bit 4
    unsigned short Px_5_SET             : 1; // Bit 5
    unsigned short Px_6_SET             : 1; // Bit 6
    unsigned short Px_7_SET             : 1; // Bit 7
  };
} P3_SET_DATA_REG_type __attribute__((aligned(2)));

extern volatile P3_SET_DATA_REG_type _A_P3_SET_DATA_REG __attribute__((aligned(2)));

#define P3_SET_DATA_Px_0_SET             0x0001 // Bit 0
#define P3_SET_DATA_Px_1_SET             0x0002 // Bit 1
#define P3_SET_DATA_Px_2_SET             0x0004 // Bit 2
#define P3_SET_DATA_Px_3_SET             0x0008 // Bit 3
#define P3_SET_DATA_Px_4_SET             0x0010 // Bit 4
#define P3_SET_DATA_Px_5_SET             0x0020 // Bit 5
#define P3_SET_DATA_Px_6_SET             0x0040 // Bit 6
#define P3_SET_DATA_Px_7_SET             0x0080 // Bit 7

/****************************************************************************
* P3_RESET_DATA_REG
****************************************************************************/

#define P3_RESET_DATA_REG_adr 0xFF4864
#define P3_RESET_DATA_REG _A_P3_RESET_DATA_REG.Value
#define P3_RESET_DATA_REG_bit _A_P3_RESET_DATA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_RESET           : 1; // Bit 0
    unsigned short Px_1_RESET           : 1; // Bit 1
    unsigned short Px_2_RESET           : 1; // Bit 2
    unsigned short Px_3_RESET           : 1; // Bit 3
    unsigned short Px_4_RESET           : 1; // Bit 4
    unsigned short Px_5_RESET           : 1; // Bit 5
    unsigned short Px_6_RESET           : 1; // Bit 6
    unsigned short Px_7_RESET           : 1; // Bit 7
  };
} P3_RESET_DATA_REG_type __attribute__((aligned(2)));

extern volatile P3_RESET_DATA_REG_type _A_P3_RESET_DATA_REG __attribute__((aligned(2)));

#define P3_RESET_DATA_Px_0_RESET           0x0001 // Bit 0
#define P3_RESET_DATA_Px_1_RESET           0x0002 // Bit 1
#define P3_RESET_DATA_Px_2_RESET           0x0004 // Bit 2
#define P3_RESET_DATA_Px_3_RESET           0x0008 // Bit 3
#define P3_RESET_DATA_Px_4_RESET           0x0010 // Bit 4
#define P3_RESET_DATA_Px_5_RESET           0x0020 // Bit 5
#define P3_RESET_DATA_Px_6_RESET           0x0040 // Bit 6
#define P3_RESET_DATA_Px_7_RESET           0x0080 // Bit 7

/****************************************************************************
* P3_DIR_REG
****************************************************************************/

#define P3_DIR_REG_adr 0xFF4866
#define P3_DIR_REG _A_P3_DIR_REG.Value
#define P3_DIR_REG_bit _A_P3_DIR_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short Px_0_DIR             : 2; // Bit 1-0
    unsigned short Px_1_DIR             : 2; // Bit 3-2
    unsigned short Px_2_DIR             : 2; // Bit 5-4
    unsigned short Px_3_DIR             : 2; // Bit 7-6
    unsigned short Px_4_DIR             : 2; // Bit 9-8
    unsigned short Px_5_DIR             : 2; // Bit 11-10
    unsigned short Px_6_DIR             : 2; // Bit 13-12
    unsigned short Px_7_DIR             : 2; // Bit 15-14
  };
} P3_DIR_REG_type __attribute__((aligned(2)));

extern volatile P3_DIR_REG_type _A_P3_DIR_REG __attribute__((aligned(2)));

#define P3_DIR_Px_0_DIR             0x0003 // Bit 1-0
#define P3_DIR_Px_1_DIR             0x000C // Bit 3-2
#define P3_DIR_Px_2_DIR             0x0030 // Bit 5-4
#define P3_DIR_Px_3_DIR             0x00C0 // Bit 7-6
#define P3_DIR_Px_4_DIR             0x0300 // Bit 9-8
#define P3_DIR_Px_5_DIR             0x0C00 // Bit 11-10
#define P3_DIR_Px_6_DIR             0x3000 // Bit 13-12
#define P3_DIR_Px_7_DIR             0xC000 // Bit 15-14

/****************************************************************************
* P3_MODE_REG
****************************************************************************/

#define P3_MODE_REG_adr 0xFF4868
#define P3_MODE_REG _A_P3_MODE_REG.Value
#define P3_MODE_REG_bit _A_P3_MODE_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short P3_0_MODE            : 2; // Bit 1-0
    unsigned short P3_1_MODE            : 2; // Bit 3-2
    unsigned short P3_2_MODE            : 2; // Bit 5-4
    unsigned short P3_3_MODE            : 2; // Bit 7-6
    unsigned short P3_4_MODE            : 2; // Bit 9-8
    unsigned short P3_5_MODE            : 2; // Bit 11-10
    unsigned short P3_6_MODE            : 2; // Bit 13-12
    unsigned short P3_7_MODE            : 2; // Bit 15-14
  };
} P3_MODE_REG_type __attribute__((aligned(2)));

extern volatile P3_MODE_REG_type _A_P3_MODE_REG __attribute__((aligned(2)));

#define P3_MODE_P3_0_MODE            0x0003 // Bit 1-0
#define P3_MODE_P3_1_MODE            0x000C // Bit 3-2
#define P3_MODE_P3_2_MODE            0x0030 // Bit 5-4
#define P3_MODE_P3_3_MODE            0x00C0 // Bit 7-6
#define P3_MODE_P3_4_MODE            0x0300 // Bit 9-8
#define P3_MODE_P3_5_MODE            0x0C00 // Bit 11-10
#define P3_MODE_P3_6_MODE            0x3000 // Bit 13-12
#define P3_MODE_P3_7_MODE            0xC000 // Bit 15-14

/****************************************************************************
* PORT_TRACE_CTRL_REG
****************************************************************************/

#define PORT_TRACE_CTRL_REG_adr 0xFF48E0
#define PORT_TRACE_CTRL_REG _A_PORT_TRACE_CTRL_REG.Value
#define PORT_TRACE_CTRL_REG_bit _A_PORT_TRACE_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TRACE_EXT0           : 5; // Bit 4-0
    unsigned short TRACE_EXT1           : 5; // Bit 9-5
  };
} PORT_TRACE_CTRL_REG_type __attribute__((aligned(2)));

extern volatile PORT_TRACE_CTRL_REG_type _A_PORT_TRACE_CTRL_REG __attribute__((aligned(2)));

#define PORT_TRACE_CTRL_TRACE_EXT0           0x001F // Bit 4-0
#define PORT_TRACE_CTRL_TRACE_EXT1           0x03E0 // Bit 9-5

/****************************************************************************
* UART_CTRL_REG
****************************************************************************/

#define UART_CTRL_REG_adr 0xFF4900
#define UART_CTRL_REG _A_UART_CTRL_REG.Value
#define UART_CTRL_REG_bit _A_UART_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short UART_REN             : 1; // Bit 0
    unsigned short UART_TEN             : 1; // Bit 1
    unsigned short BAUDRATE             : 3; // Bit 4-2
    unsigned short TI                   : 1; // Bit 5
    unsigned short RI                   : 1; // Bit 6
    unsigned short UART_MODE            : 1; // Bit 7
    unsigned short IRDA_EN              : 1; // Bit 8
    unsigned short INV_URX              : 1; // Bit 9
    unsigned short INV_UTX              : 1; // Bit 10
  };
} UART_CTRL_REG_type __attribute__((aligned(2)));

extern volatile UART_CTRL_REG_type _A_UART_CTRL_REG __attribute__((aligned(2)));

#define UART_CTRL_UART_REN             0x0001 // Bit 0
#define UART_CTRL_UART_TEN             0x0002 // Bit 1
#define UART_CTRL_BAUDRATE             0x001C // Bit 4-2
#define UART_CTRL_TI                   0x0020 // Bit 5
#define UART_CTRL_RI                   0x0040 // Bit 6
#define UART_CTRL_UART_MODE            0x0080 // Bit 7
#define UART_CTRL_IRDA_EN              0x0100 // Bit 8
#define UART_CTRL_INV_URX              0x0200 // Bit 9
#define UART_CTRL_INV_UTX              0x0400 // Bit 10

/****************************************************************************
* UART_RX_TX_REG
****************************************************************************/

#define UART_RX_TX_REG_adr 0xFF4902
#define UART_RX_TX_REG _A_UART_RX_TX_REG

extern volatile unsigned short _A_UART_RX_TX_REG;

/****************************************************************************
* UART_CLEAR_TX_INT_REG
****************************************************************************/

#define UART_CLEAR_TX_INT_REG_adr 0xFF4904
#define UART_CLEAR_TX_INT_REG _A_UART_CLEAR_TX_INT_REG

extern volatile unsigned short _A_UART_CLEAR_TX_INT_REG;

/****************************************************************************
* UART_CLEAR_RX_INT_REG
****************************************************************************/

#define UART_CLEAR_RX_INT_REG_adr 0xFF4906
#define UART_CLEAR_RX_INT_REG _A_UART_CLEAR_RX_INT_REG

extern volatile unsigned short _A_UART_CLEAR_RX_INT_REG;

/****************************************************************************
* UART_ERROR_REG
****************************************************************************/

#define UART_ERROR_REG_adr 0xFF4908
#define UART_ERROR_REG _A_UART_ERROR_REG.Value
#define UART_ERROR_REG_bit _A_UART_ERROR_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PAR_STATUS           : 1; // Bit 0
    unsigned short DMA_PARITY_ERROR     : 1; // Bit 1
  };
} UART_ERROR_REG_type __attribute__((aligned(2)));

extern volatile UART_ERROR_REG_type _A_UART_ERROR_REG __attribute__((aligned(2)));

#define UART_ERROR_PAR_STATUS           0x0001 // Bit 0
#define UART_ERROR_DMA_PARITY_ERROR     0x0002 // Bit 1

/****************************************************************************
* UART2_CTRL_REG
****************************************************************************/

#define UART2_CTRL_REG_adr 0xFF4910
#define UART2_CTRL_REG _A_UART2_CTRL_REG.Value
#define UART2_CTRL_REG_bit _A_UART2_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short UART_REN             : 1; // Bit 0
    unsigned short UART_TEN             : 1; // Bit 1
    unsigned short BAUDRATE             : 3; // Bit 4-2
    unsigned short TI                   : 1; // Bit 5
    unsigned short RI                   : 1; // Bit 6
    unsigned short UART_MODE            : 1; // Bit 7
    unsigned short IRDA_EN              : 1; // Bit 8
    unsigned short INV_URX              : 1; // Bit 9
    unsigned short INV_UTX              : 1; // Bit 10
  };
} UART2_CTRL_REG_type __attribute__((aligned(2)));

extern volatile UART2_CTRL_REG_type _A_UART2_CTRL_REG __attribute__((aligned(2)));

#define UART2_CTRL_UART_REN             0x0001 // Bit 0
#define UART2_CTRL_UART_TEN             0x0002 // Bit 1
#define UART2_CTRL_BAUDRATE             0x001C // Bit 4-2
#define UART2_CTRL_TI                   0x0020 // Bit 5
#define UART2_CTRL_RI                   0x0040 // Bit 6
#define UART2_CTRL_UART_MODE            0x0080 // Bit 7
#define UART2_CTRL_IRDA_EN              0x0100 // Bit 8
#define UART2_CTRL_INV_URX              0x0200 // Bit 9
#define UART2_CTRL_INV_UTX              0x0400 // Bit 10

/****************************************************************************
* UART2_RX_TX_REG
****************************************************************************/

#define UART2_RX_TX_REG_adr 0xFF4912
#define UART2_RX_TX_REG _A_UART2_RX_TX_REG

extern volatile unsigned short _A_UART2_RX_TX_REG;

/****************************************************************************
* UART2_CLEAR_TX_INT_REG
****************************************************************************/

#define UART2_CLEAR_TX_INT_REG_adr 0xFF4914
#define UART2_CLEAR_TX_INT_REG _A_UART2_CLEAR_TX_INT_REG

extern volatile unsigned short _A_UART2_CLEAR_TX_INT_REG;

/****************************************************************************
* UART2_CLEAR_RX_INT_REG
****************************************************************************/

#define UART2_CLEAR_RX_INT_REG_adr 0xFF4916
#define UART2_CLEAR_RX_INT_REG _A_UART2_CLEAR_RX_INT_REG

extern volatile unsigned short _A_UART2_CLEAR_RX_INT_REG;

/****************************************************************************
* UART2_ERROR_REG
****************************************************************************/

#define UART2_ERROR_REG_adr 0xFF4918
#define UART2_ERROR_REG _A_UART2_ERROR_REG.Value
#define UART2_ERROR_REG_bit _A_UART2_ERROR_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PAR_STATUS           : 1; // Bit 0
    unsigned short DMA_PARITY_ERROR     : 1; // Bit 1
  };
} UART2_ERROR_REG_type __attribute__((aligned(2)));

extern volatile UART2_ERROR_REG_type _A_UART2_ERROR_REG __attribute__((aligned(2)));

#define UART2_ERROR_PAR_STATUS           0x0001 // Bit 0
#define UART2_ERROR_DMA_PARITY_ERROR     0x0002 // Bit 1

/****************************************************************************
* ACCESS1_IN_OUT_REG
****************************************************************************/

#define ACCESS1_IN_OUT_REG_adr 0xFF4920
#define ACCESS1_IN_OUT_REG _A_ACCESS1_IN_OUT_REG

extern volatile unsigned short _A_ACCESS1_IN_OUT_REG;

/****************************************************************************
* ACCESS1_CTRL_REG
****************************************************************************/

#define ACCESS1_CTRL_REG_adr 0xFF4922
#define ACCESS1_CTRL_REG _A_ACCESS1_CTRL_REG.Value
#define ACCESS1_CTRL_REG_bit _A_ACCESS1_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short EN_ACCESS_BUS        : 1; // Bit 0
    unsigned short ACKn                 : 1; // Bit 1
    unsigned short SCL_VAL              : 1; // Bit 2
    unsigned short SDA_VAL              : 1; // Bit 3
    unsigned short ACCESSx_INT          : 1; // Bit 4
    unsigned short EN_ACCESS_INT        : 1; // Bit 5
    unsigned short SCL_OD               : 1; // Bit 6
    unsigned short SDA_OD               : 1; // Bit 7
    unsigned short SCK_NUM              : 1; // Bit 8
    unsigned short SCK_SEL              : 2; // Bit 10-9
  };
} ACCESS1_CTRL_REG_type __attribute__((aligned(2)));

extern volatile ACCESS1_CTRL_REG_type _A_ACCESS1_CTRL_REG __attribute__((aligned(2)));

#define ACCESS1_CTRL_EN_ACCESS_BUS        0x0001 // Bit 0
#define ACCESS1_CTRL_ACKn                 0x0002 // Bit 1
#define ACCESS1_CTRL_SCL_VAL              0x0004 // Bit 2
#define ACCESS1_CTRL_SDA_VAL              0x0008 // Bit 3
#define ACCESS1_CTRL_ACCESSx_INT          0x0010 // Bit 4
#define ACCESS1_CTRL_EN_ACCESS_INT        0x0020 // Bit 5
#define ACCESS1_CTRL_SCL_OD               0x0040 // Bit 6
#define ACCESS1_CTRL_SDA_OD               0x0080 // Bit 7
#define ACCESS1_CTRL_SCK_NUM              0x0100 // Bit 8
#define ACCESS1_CTRL_SCK_SEL              0x0600 // Bit 10-9

/****************************************************************************
* ACCESS1_CLEAR_INT_REG
****************************************************************************/

#define ACCESS1_CLEAR_INT_REG_adr 0xFF4924
#define ACCESS1_CLEAR_INT_REG _A_ACCESS1_CLEAR_INT_REG

extern volatile unsigned short _A_ACCESS1_CLEAR_INT_REG;

/****************************************************************************
* ACCESS2_IN_OUT_REG
****************************************************************************/

#define ACCESS2_IN_OUT_REG_adr 0xFF4930
#define ACCESS2_IN_OUT_REG _A_ACCESS2_IN_OUT_REG

extern volatile unsigned short _A_ACCESS2_IN_OUT_REG;

/****************************************************************************
* ACCESS2_CTRL_REG
****************************************************************************/

#define ACCESS2_CTRL_REG_adr 0xFF4932
#define ACCESS2_CTRL_REG _A_ACCESS2_CTRL_REG.Value
#define ACCESS2_CTRL_REG_bit _A_ACCESS2_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short EN_ACCESS_BUS        : 1; // Bit 0
    unsigned short ACKn                 : 1; // Bit 1
    unsigned short SCL_VAL              : 1; // Bit 2
    unsigned short SDA_VAL              : 1; // Bit 3
    unsigned short ACCESSx_INT          : 1; // Bit 4
    unsigned short EN_ACCESS_INT        : 1; // Bit 5
    unsigned short SCL_OD               : 1; // Bit 6
    unsigned short SDA_OD               : 1; // Bit 7
    unsigned short SCK_NUM              : 1; // Bit 8
    unsigned short SCK_SEL              : 2; // Bit 10-9
  };
} ACCESS2_CTRL_REG_type __attribute__((aligned(2)));

extern volatile ACCESS2_CTRL_REG_type _A_ACCESS2_CTRL_REG __attribute__((aligned(2)));

#define ACCESS2_CTRL_EN_ACCESS_BUS        0x0001 // Bit 0
#define ACCESS2_CTRL_ACKn                 0x0002 // Bit 1
#define ACCESS2_CTRL_SCL_VAL              0x0004 // Bit 2
#define ACCESS2_CTRL_SDA_VAL              0x0008 // Bit 3
#define ACCESS2_CTRL_ACCESSx_INT          0x0010 // Bit 4
#define ACCESS2_CTRL_EN_ACCESS_INT        0x0020 // Bit 5
#define ACCESS2_CTRL_SCL_OD               0x0040 // Bit 6
#define ACCESS2_CTRL_SDA_OD               0x0080 // Bit 7
#define ACCESS2_CTRL_SCK_NUM              0x0100 // Bit 8
#define ACCESS2_CTRL_SCK_SEL              0x0600 // Bit 10-9

/****************************************************************************
* ACCESS2_CLEAR_INT_REG
****************************************************************************/

#define ACCESS2_CLEAR_INT_REG_adr 0xFF4934
#define ACCESS2_CLEAR_INT_REG _A_ACCESS2_CLEAR_INT_REG

extern volatile unsigned short _A_ACCESS2_CLEAR_INT_REG;

/****************************************************************************
* SPI_CTRL_REG
****************************************************************************/

#define SPI_CTRL_REG_adr 0xFF4940
#define SPI_CTRL_REG _A_SPI_CTRL_REG.Value
#define SPI_CTRL_REG_bit _A_SPI_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SPI_ON               : 1; // Bit 0
    unsigned short SPI_PHA              : 1; // Bit 1
    unsigned short SPI_POL              : 1; // Bit 2
    unsigned short SPI_CLK              : 2; // Bit 4-3
    unsigned short SPI_DO               : 1; // Bit 5
    unsigned short SPI_SMN              : 1; // Bit 6
    unsigned short SPI_WORD             : 2; // Bit 8-7
    unsigned short SPI_RST              : 1; // Bit 9
    unsigned short SPI_FORCE_DO         : 1; // Bit 10
    unsigned short SPI_TXH              : 1; // Bit 11
    unsigned short SPI_DI               : 1; // Bit 12
    unsigned short SPI_INT_BIT          : 1; // Bit 13
    unsigned short SPI_MINT             : 1; // Bit 14
    unsigned short SPI_EN_CTRL          : 1; // Bit 15
  };
} SPI_CTRL_REG_type __attribute__((aligned(2)));

extern volatile SPI_CTRL_REG_type _A_SPI_CTRL_REG __attribute__((aligned(2)));

#define SPI_CTRL_SPI_ON               0x0001 // Bit 0
#define SPI_CTRL_SPI_PHA              0x0002 // Bit 1
#define SPI_CTRL_SPI_POL              0x0004 // Bit 2
#define SPI_CTRL_SPI_CLK              0x0018 // Bit 4-3
#define SPI_CTRL_SPI_DO               0x0020 // Bit 5
#define SPI_CTRL_SPI_SMN              0x0040 // Bit 6
#define SPI_CTRL_SPI_WORD             0x0180 // Bit 8-7
#define SPI_CTRL_SPI_RST              0x0200 // Bit 9
#define SPI_CTRL_SPI_FORCE_DO         0x0400 // Bit 10
#define SPI_CTRL_SPI_TXH              0x0800 // Bit 11
#define SPI_CTRL_SPI_DI               0x1000 // Bit 12
#define SPI_CTRL_SPI_INT_BIT          0x2000 // Bit 13
#define SPI_CTRL_SPI_MINT             0x4000 // Bit 14
#define SPI_CTRL_SPI_EN_CTRL          0x8000 // Bit 15

/****************************************************************************
* SPI_RX_TX_REG0
****************************************************************************/

#define SPI_RX_TX_REG0_adr 0xFF4942
#define SPI_RX_TX_REG0 _A_SPI_RX_TX_REG0

extern volatile unsigned short _A_SPI_RX_TX_REG0;

/****************************************************************************
* SPI_RX_TX_REG1
****************************************************************************/

#define SPI_RX_TX_REG1_adr 0xFF4944
#define SPI_RX_TX_REG1 _A_SPI_RX_TX_REG1

extern volatile unsigned short _A_SPI_RX_TX_REG1;

/****************************************************************************
* SPI_CLEAR_INT_REG
****************************************************************************/

#define SPI_CLEAR_INT_REG_adr 0xFF4946
#define SPI_CLEAR_INT_REG _A_SPI_CLEAR_INT_REG

extern volatile unsigned short _A_SPI_CLEAR_INT_REG;

/****************************************************************************
* SPI_CTRL_REG1
****************************************************************************/

#define SPI_CTRL_REG1_adr 0xFF4948
#define SPI_CTRL_REG1 _A_SPI_CTRL_REG1.Value
#define SPI_CTRL_REG1_bit _A_SPI_CTRL_REG1

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SPI_FIFO_MODE        : 2; // Bit 1-0
    unsigned short SPI_PRIORITY         : 1; // Bit 2
    unsigned short SPI_BUSY             : 1; // Bit 3
  };
} SPI_CTRL_REG1_type __attribute__((aligned(2)));

extern volatile SPI_CTRL_REG1_type _A_SPI_CTRL_REG1 __attribute__((aligned(2)));

#define SPI_CTRL_SPI_FIFO_MODE        0x0003 // Bit 1-0
#define SPI_CTRL_SPI_PRIORITY         0x0004 // Bit 2
#define SPI_CTRL_SPI_BUSY             0x0008 // Bit 3

/****************************************************************************
* SPI2_CTRL_REG
****************************************************************************/

#define SPI2_CTRL_REG_adr 0xFF4950
#define SPI2_CTRL_REG _A_SPI2_CTRL_REG.Value
#define SPI2_CTRL_REG_bit _A_SPI2_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SPI_ON               : 1; // Bit 0
    unsigned short SPI_PHA              : 1; // Bit 1
    unsigned short SPI_POL              : 1; // Bit 2
    unsigned short SPI_CLK              : 2; // Bit 4-3
    unsigned short SPI_DO               : 1; // Bit 5
    unsigned short SPI_SMN              : 1; // Bit 6
    unsigned short SPI_WORD             : 2; // Bit 8-7
    unsigned short SPI_RST              : 1; // Bit 9
    unsigned short SPI_FORCE_DO         : 1; // Bit 10
    unsigned short SPI_TXH              : 1; // Bit 11
    unsigned short SPI_DI               : 1; // Bit 12
    unsigned short SPI_INT_BIT          : 1; // Bit 13
    unsigned short SPI_MINT             : 1; // Bit 14
    unsigned short SPI_EN_CTRL          : 1; // Bit 15
  };
} SPI2_CTRL_REG_type __attribute__((aligned(2)));

extern volatile SPI2_CTRL_REG_type _A_SPI2_CTRL_REG __attribute__((aligned(2)));

#define SPI2_CTRL_SPI_ON               0x0001 // Bit 0
#define SPI2_CTRL_SPI_PHA              0x0002 // Bit 1
#define SPI2_CTRL_SPI_POL              0x0004 // Bit 2
#define SPI2_CTRL_SPI_CLK              0x0018 // Bit 4-3
#define SPI2_CTRL_SPI_DO               0x0020 // Bit 5
#define SPI2_CTRL_SPI_SMN              0x0040 // Bit 6
#define SPI2_CTRL_SPI_WORD             0x0180 // Bit 8-7
#define SPI2_CTRL_SPI_RST              0x0200 // Bit 9
#define SPI2_CTRL_SPI_FORCE_DO         0x0400 // Bit 10
#define SPI2_CTRL_SPI_TXH              0x0800 // Bit 11
#define SPI2_CTRL_SPI_DI               0x1000 // Bit 12
#define SPI2_CTRL_SPI_INT_BIT          0x2000 // Bit 13
#define SPI2_CTRL_SPI_MINT             0x4000 // Bit 14
#define SPI2_CTRL_SPI_EN_CTRL          0x8000 // Bit 15

/****************************************************************************
* SPI2_RX_TX_REG0
****************************************************************************/

#define SPI2_RX_TX_REG0_adr 0xFF4952
#define SPI2_RX_TX_REG0 _A_SPI2_RX_TX_REG0

extern volatile unsigned short _A_SPI2_RX_TX_REG0;

/****************************************************************************
* SPI2_RX_TX_REG1
****************************************************************************/

#define SPI2_RX_TX_REG1_adr 0xFF4954
#define SPI2_RX_TX_REG1 _A_SPI2_RX_TX_REG1

extern volatile unsigned short _A_SPI2_RX_TX_REG1;

/****************************************************************************
* SPI2_CLEAR_INT_REG
****************************************************************************/

#define SPI2_CLEAR_INT_REG_adr 0xFF4956
#define SPI2_CLEAR_INT_REG _A_SPI2_CLEAR_INT_REG

extern volatile unsigned short _A_SPI2_CLEAR_INT_REG;

/****************************************************************************
* SPI2_CTRL_REG1
****************************************************************************/

#define SPI2_CTRL_REG1_adr 0xFF4958
#define SPI2_CTRL_REG1 _A_SPI2_CTRL_REG1.Value
#define SPI2_CTRL_REG1_bit _A_SPI2_CTRL_REG1

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SPI_FIFO_MODE        : 2; // Bit 1-0
    unsigned short SPI_PRIORITY         : 1; // Bit 2
    unsigned short SPI_BUSY             : 1; // Bit 3
  };
} SPI2_CTRL_REG1_type __attribute__((aligned(2)));

extern volatile SPI2_CTRL_REG1_type _A_SPI2_CTRL_REG1 __attribute__((aligned(2)));

#define SPI2_CTRL_SPI_FIFO_MODE        0x0003 // Bit 1-0
#define SPI2_CTRL_SPI_PRIORITY         0x0004 // Bit 2
#define SPI2_CTRL_SPI_BUSY             0x0008 // Bit 3

/****************************************************************************
* ADC_CTRL_REG
****************************************************************************/

#define ADC_CTRL_REG_adr 0xFF4960
#define ADC_CTRL_REG _A_ADC_CTRL_REG.Value
#define ADC_CTRL_REG_bit _A_ADC_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ADC_START            : 1; // Bit 0
    unsigned short ADC_AUTO             : 1; // Bit 1
    unsigned short ADC_ALT              : 1; // Bit 2
    unsigned short ADC_IN_3_0           : 4; // Bit 6-3
    unsigned short ADC_TEST             : 4; // Bit 10-7
    unsigned short ADC_INT              : 1; // Bit 11
    unsigned short ADC_MINT             : 1; // Bit 12
    unsigned short ADC0_PR_DIS          : 1; // Bit 13
    unsigned short ADC1_PR_DIS          : 1; // Bit 14
    unsigned short ADC2_PR_DIS          : 1; // Bit 15
  };
} ADC_CTRL_REG_type __attribute__((aligned(2)));

extern volatile ADC_CTRL_REG_type _A_ADC_CTRL_REG __attribute__((aligned(2)));

#define ADC_CTRL_ADC_START            0x0001 // Bit 0
#define ADC_CTRL_ADC_AUTO             0x0002 // Bit 1
#define ADC_CTRL_ADC_ALT              0x0004 // Bit 2
#define ADC_CTRL_ADC_IN_3_0           0x0078 // Bit 6-3
#define ADC_CTRL_ADC_TEST             0x0780 // Bit 10-7
#define ADC_CTRL_ADC_INT              0x0800 // Bit 11
#define ADC_CTRL_ADC_MINT             0x1000 // Bit 12
#define ADC_CTRL_ADC0_PR_DIS          0x2000 // Bit 13
#define ADC_CTRL_ADC1_PR_DIS          0x4000 // Bit 14
#define ADC_CTRL_ADC2_PR_DIS          0x8000 // Bit 15

/****************************************************************************
* ADC_CTRL1_REG
****************************************************************************/

#define ADC_CTRL1_REG_adr 0xFF4962
#define ADC_CTRL1_REG _A_ADC_CTRL1_REG.Value
#define ADC_CTRL1_REG_bit _A_ADC_CTRL1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ADC_IN_3_0_1         : 4; // Bit 3-0
  };
} ADC_CTRL1_REG_type __attribute__((aligned(2)));

extern volatile ADC_CTRL1_REG_type _A_ADC_CTRL1_REG __attribute__((aligned(2)));

#define ADC_CTRL1_ADC_IN_3_0_1         0x000F // Bit 3-0

/****************************************************************************
* ADC_CLEAR_INT_REG
****************************************************************************/

#define ADC_CLEAR_INT_REG_adr 0xFF4964
#define ADC_CLEAR_INT_REG _A_ADC_CLEAR_INT_REG

extern volatile unsigned short _A_ADC_CLEAR_INT_REG;

/****************************************************************************
* ADC0_REG
****************************************************************************/

#define ADC0_REG_adr 0xFF4966
#define ADC0_REG _A_ADC0_REG.Value
#define ADC0_REG_bit _A_ADC0_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ADC0_VAL             : 10; // Bit 9-0
  };
} ADC0_REG_type __attribute__((aligned(2)));

extern volatile ADC0_REG_type _A_ADC0_REG __attribute__((aligned(2)));

#define ADC0_ADC0_VAL             0x03FF // Bit 9-0

/****************************************************************************
* ADC1_REG
****************************************************************************/

#define ADC1_REG_adr 0xFF4968
#define ADC1_REG _A_ADC1_REG.Value
#define ADC1_REG_bit _A_ADC1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ADC1_VAL             : 10; // Bit 9-0
  };
} ADC1_REG_type __attribute__((aligned(2)));

extern volatile ADC1_REG_type _A_ADC1_REG __attribute__((aligned(2)));

#define ADC1_ADC1_VAL             0x03FF // Bit 9-0

/****************************************************************************
* TIMER_CTRL_REG
****************************************************************************/

#define TIMER_CTRL_REG_adr 0xFF4970
#define TIMER_CTRL_REG _A_TIMER_CTRL_REG.Value
#define TIMER_CTRL_REG_bit _A_TIMER_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TIM0_CTRL            : 1; // Bit 0
    unsigned short TIM1_CTRL            : 1; // Bit 1
    unsigned short CLK_CTRL0            : 1; // Bit 2
    unsigned short CLK_CTRL1            : 1; // Bit 3
    unsigned short WDOG_CTRL            : 1; // Bit 4
    unsigned short TIM1_MODE            : 1; // Bit 5
    unsigned short CLK_DIV8             : 1; // Bit 6
    unsigned short TIM2_CTRL            : 1; // Bit 7
  };
} TIMER_CTRL_REG_type __attribute__((aligned(2)));

extern volatile TIMER_CTRL_REG_type _A_TIMER_CTRL_REG __attribute__((aligned(2)));

#define TIMER_CTRL_TIM0_CTRL            0x0001 // Bit 0
#define TIMER_CTRL_TIM1_CTRL            0x0002 // Bit 1
#define TIMER_CTRL_CLK_CTRL0            0x0004 // Bit 2
#define TIMER_CTRL_CLK_CTRL1            0x0008 // Bit 3
#define TIMER_CTRL_WDOG_CTRL            0x0010 // Bit 4
#define TIMER_CTRL_TIM1_MODE            0x0020 // Bit 5
#define TIMER_CTRL_CLK_DIV8             0x0040 // Bit 6
#define TIMER_CTRL_TIM2_CTRL            0x0080 // Bit 7

/****************************************************************************
* TIMER0_ON_REG
****************************************************************************/

#define TIMER0_ON_REG_adr 0xFF4972
#define TIMER0_ON_REG _A_TIMER0_ON_REG

extern volatile unsigned short _A_TIMER0_ON_REG;

/****************************************************************************
* TIMER0_RELOAD_M_REG
****************************************************************************/

#define TIMER0_RELOAD_M_REG_adr 0xFF4974
#define TIMER0_RELOAD_M_REG _A_TIMER0_RELOAD_M_REG

extern volatile unsigned short _A_TIMER0_RELOAD_M_REG;

/****************************************************************************
* TIMER0_RELOAD_N_REG
****************************************************************************/

#define TIMER0_RELOAD_N_REG_adr 0xFF4976
#define TIMER0_RELOAD_N_REG _A_TIMER0_RELOAD_N_REG

extern volatile unsigned short _A_TIMER0_RELOAD_N_REG;

/****************************************************************************
* TIMER1_RELOAD_M_REG
****************************************************************************/

#define TIMER1_RELOAD_M_REG_adr 0xFF4978
#define TIMER1_RELOAD_M_REG _A_TIMER1_RELOAD_M_REG

extern volatile unsigned short _A_TIMER1_RELOAD_M_REG;

/****************************************************************************
* TIMER1_RELOAD_N_REG
****************************************************************************/

#define TIMER1_RELOAD_N_REG_adr 0xFF497A
#define TIMER1_RELOAD_N_REG _A_TIMER1_RELOAD_N_REG

extern volatile unsigned short _A_TIMER1_RELOAD_N_REG;

/****************************************************************************
* TIMER2_DUTY1_REG
****************************************************************************/

#define TIMER2_DUTY1_REG_adr 0xFF497C
#define TIMER2_DUTY1_REG _A_TIMER2_DUTY1_REG.Value
#define TIMER2_DUTY1_REG_bit _A_TIMER2_DUTY1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TIM2_DUTY1           : 14; // Bit 13-0
  };
} TIMER2_DUTY1_REG_type __attribute__((aligned(2)));

extern volatile TIMER2_DUTY1_REG_type _A_TIMER2_DUTY1_REG __attribute__((aligned(2)));

#define TIMER2_DUTY1_TIM2_DUTY1           0x3FFF // Bit 13-0

/****************************************************************************
* TIMER2_DUTY2_REG
****************************************************************************/

#define TIMER2_DUTY2_REG_adr 0xFF497E
#define TIMER2_DUTY2_REG _A_TIMER2_DUTY2_REG.Value
#define TIMER2_DUTY2_REG_bit _A_TIMER2_DUTY2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TIM2_DUTY2           : 14; // Bit 13-0
  };
} TIMER2_DUTY2_REG_type __attribute__((aligned(2)));

extern volatile TIMER2_DUTY2_REG_type _A_TIMER2_DUTY2_REG __attribute__((aligned(2)));

#define TIMER2_DUTY2_TIM2_DUTY2           0x3FFF // Bit 13-0

/****************************************************************************
* TIMER2_FREQ_REG
****************************************************************************/

#define TIMER2_FREQ_REG_adr 0xFF4980
#define TIMER2_FREQ_REG _A_TIMER2_FREQ_REG.Value
#define TIMER2_FREQ_REG_bit _A_TIMER2_FREQ_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TIM2_FREQ            : 14; // Bit 13-0
  };
} TIMER2_FREQ_REG_type __attribute__((aligned(2)));

extern volatile TIMER2_FREQ_REG_type _A_TIMER2_FREQ_REG __attribute__((aligned(2)));

#define TIMER2_FREQ_TIM2_FREQ            0x3FFF // Bit 13-0

/****************************************************************************
* TIMER2_DUTY3_REG
****************************************************************************/

#define TIMER2_DUTY3_REG_adr 0xFF4982
#define TIMER2_DUTY3_REG _A_TIMER2_DUTY3_REG.Value
#define TIMER2_DUTY3_REG_bit _A_TIMER2_DUTY3_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TIM2_DUTY3           : 14; // Bit 13-0
  };
} TIMER2_DUTY3_REG_type __attribute__((aligned(2)));

extern volatile TIMER2_DUTY3_REG_type _A_TIMER2_DUTY3_REG __attribute__((aligned(2)));

#define TIMER2_DUTY3_TIM2_DUTY3           0x3FFF // Bit 13-0

/****************************************************************************
* TONE_CTRL1_REG
****************************************************************************/

#define TONE_CTRL1_REG_adr 0xFF4990
#define TONE_CTRL1_REG _A_TONE_CTRL1_REG.Value
#define TONE_CTRL1_REG_bit _A_TONE_CTRL1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short GATESRC1             : 2; // Bit 1-0
    unsigned short CLKSRC1              : 2; // Bit 3-2
    unsigned short TIMER_RELOAD1        : 4; // Bit 7-4
    unsigned short CT1_INT              : 1; // Bit 8
    unsigned short MCT1_INT             : 1; // Bit 9
    unsigned short GATE_EDGE1           : 1; // Bit 10
  };
} TONE_CTRL1_REG_type __attribute__((aligned(2)));

extern volatile TONE_CTRL1_REG_type _A_TONE_CTRL1_REG __attribute__((aligned(2)));

#define TONE_CTRL1_GATESRC1             0x0003 // Bit 1-0
#define TONE_CTRL1_CLKSRC1              0x000C // Bit 3-2
#define TONE_CTRL1_TIMER_RELOAD1        0x00F0 // Bit 7-4
#define TONE_CTRL1_CT1_INT              0x0100 // Bit 8
#define TONE_CTRL1_MCT1_INT             0x0200 // Bit 9
#define TONE_CTRL1_GATE_EDGE1           0x0400 // Bit 10

/****************************************************************************
* TONE_COUNTER1_REG
****************************************************************************/

#define TONE_COUNTER1_REG_adr 0xFF4992
#define TONE_COUNTER1_REG _A_TONE_COUNTER1_REG

extern volatile unsigned short _A_TONE_COUNTER1_REG;

/****************************************************************************
* TONE_LATCH1_REG
****************************************************************************/

#define TONE_LATCH1_REG_adr 0xFF4994
#define TONE_LATCH1_REG _A_TONE_LATCH1_REG

extern volatile unsigned short _A_TONE_LATCH1_REG;

/****************************************************************************
* TONE_CLEAR_INT1_REG
****************************************************************************/

#define TONE_CLEAR_INT1_REG_adr 0xFF4996
#define TONE_CLEAR_INT1_REG _A_TONE_CLEAR_INT1_REG

extern volatile unsigned short _A_TONE_CLEAR_INT1_REG;

/****************************************************************************
* TONE_CTRL2_REG
****************************************************************************/

#define TONE_CTRL2_REG_adr 0xFF4998
#define TONE_CTRL2_REG _A_TONE_CTRL2_REG.Value
#define TONE_CTRL2_REG_bit _A_TONE_CTRL2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short GATESRC2             : 2; // Bit 1-0
    unsigned short CLKSRC2              : 2; // Bit 3-2
    unsigned short TIMER_RELOAD2        : 4; // Bit 7-4
    unsigned short CT2_INT              : 1; // Bit 8
    unsigned short MCT2_INT             : 1; // Bit 9
    unsigned short GATE_EDGE2           : 1; // Bit 10
  };
} TONE_CTRL2_REG_type __attribute__((aligned(2)));

extern volatile TONE_CTRL2_REG_type _A_TONE_CTRL2_REG __attribute__((aligned(2)));

#define TONE_CTRL2_GATESRC2             0x0003 // Bit 1-0
#define TONE_CTRL2_CLKSRC2              0x000C // Bit 3-2
#define TONE_CTRL2_TIMER_RELOAD2        0x00F0 // Bit 7-4
#define TONE_CTRL2_CT2_INT              0x0100 // Bit 8
#define TONE_CTRL2_MCT2_INT             0x0200 // Bit 9
#define TONE_CTRL2_GATE_EDGE2           0x0400 // Bit 10

/****************************************************************************
* TONE_COUNTER2_REG
****************************************************************************/

#define TONE_COUNTER2_REG_adr 0xFF499A
#define TONE_COUNTER2_REG _A_TONE_COUNTER2_REG

extern volatile unsigned short _A_TONE_COUNTER2_REG;

/****************************************************************************
* TONE_LATCH2_REG
****************************************************************************/

#define TONE_LATCH2_REG_adr 0xFF499C
#define TONE_LATCH2_REG _A_TONE_LATCH2_REG

extern volatile unsigned short _A_TONE_LATCH2_REG;

/****************************************************************************
* TONE_CLEAR_INT2_REG
****************************************************************************/

#define TONE_CLEAR_INT2_REG_adr 0xFF499E
#define TONE_CLEAR_INT2_REG _A_TONE_CLEAR_INT2_REG

extern volatile unsigned short _A_TONE_CLEAR_INT2_REG;

/****************************************************************************
* KEY_GP_INT_REG
****************************************************************************/

#define KEY_GP_INT_REG_adr 0xFF49B0
#define KEY_GP_INT_REG _A_KEY_GP_INT_REG.Value
#define KEY_GP_INT_REG_bit _A_KEY_GP_INT_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short INT6_CTRL            : 3; // Bit 2-0
    unsigned short INT7_CTRL            : 3; // Bit 5-3
    unsigned short INT8_CTRL            : 3; // Bit 8-6
    unsigned short                      : 1; // Bit 9
  };
} KEY_GP_INT_REG_type __attribute__((aligned(2)));

extern volatile KEY_GP_INT_REG_type _A_KEY_GP_INT_REG __attribute__((aligned(2)));

#define KEY_GP_INT_INT6_CTRL            0x0007 // Bit 2-0
#define KEY_GP_INT_INT7_CTRL            0x0038 // Bit 5-3
#define KEY_GP_INT_INT8_CTRL            0x01C0 // Bit 8-6

/****************************************************************************
* KEY_BOARD_INT_REG
****************************************************************************/

#define KEY_BOARD_INT_REG_adr 0xFF49B2
#define KEY_BOARD_INT_REG _A_KEY_BOARD_INT_REG.Value
#define KEY_BOARD_INT_REG_bit _A_KEY_BOARD_INT_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short INT0_EN              : 1; // Bit 0
    unsigned short INT1_EN              : 1; // Bit 1
    unsigned short INT2_EN              : 1; // Bit 2
    unsigned short INT3_EN              : 1; // Bit 3
    unsigned short INT4_EN              : 1; // Bit 4
    unsigned short INT5_EN              : 1; // Bit 5
    unsigned short INT_CHARGE_EN        : 1; // Bit 6
    unsigned short INT_PON_EN           : 1; // Bit 7
    unsigned short CHARGE_CTRL          : 1; // Bit 8
    unsigned short PON_CTRL             : 1; // Bit 9
    unsigned short KEY_LEVEL            : 1; // Bit 10
    unsigned short KEY_REL              : 1; // Bit 11
    unsigned short CHARGE_EDGE          : 1; // Bit 12
    unsigned short VBATC_EDGE           : 1; // Bit 13
    unsigned short VBATC_EN             : 1; // Bit 14
  };
} KEY_BOARD_INT_REG_type __attribute__((aligned(2)));

extern volatile KEY_BOARD_INT_REG_type _A_KEY_BOARD_INT_REG __attribute__((aligned(2)));

#define KEY_BOARD_INT_INT0_EN              0x0001 // Bit 0
#define KEY_BOARD_INT_INT1_EN              0x0002 // Bit 1
#define KEY_BOARD_INT_INT2_EN              0x0004 // Bit 2
#define KEY_BOARD_INT_INT3_EN              0x0008 // Bit 3
#define KEY_BOARD_INT_INT4_EN              0x0010 // Bit 4
#define KEY_BOARD_INT_INT5_EN              0x0020 // Bit 5
#define KEY_BOARD_INT_INT_CHARGE_EN        0x0040 // Bit 6
#define KEY_BOARD_INT_INT_PON_EN           0x0080 // Bit 7
#define KEY_BOARD_INT_CHARGE_CTRL          0x0100 // Bit 8
#define KEY_BOARD_INT_PON_CTRL             0x0200 // Bit 9
#define KEY_BOARD_INT_KEY_LEVEL            0x0400 // Bit 10
#define KEY_BOARD_INT_KEY_REL              0x0800 // Bit 11
#define KEY_BOARD_INT_CHARGE_EDGE          0x1000 // Bit 12
#define KEY_BOARD_INT_VBATC_EDGE           0x2000 // Bit 13
#define KEY_BOARD_INT_VBATC_EN             0x4000 // Bit 14

/****************************************************************************
* KEY_DEBOUNCE_REG
****************************************************************************/

#define KEY_DEBOUNCE_REG_adr 0xFF49B4
#define KEY_DEBOUNCE_REG _A_KEY_DEBOUNCE_REG.Value
#define KEY_DEBOUNCE_REG_bit _A_KEY_DEBOUNCE_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DEBOUNCE             : 6; // Bit 5-0
    unsigned short KEY_REPEAT           : 6; // Bit 11-6
  };
} KEY_DEBOUNCE_REG_type __attribute__((aligned(2)));

extern volatile KEY_DEBOUNCE_REG_type _A_KEY_DEBOUNCE_REG __attribute__((aligned(2)));

#define KEY_DEBOUNCE_DEBOUNCE             0x003F // Bit 5-0
#define KEY_DEBOUNCE_KEY_REPEAT           0x0FC0 // Bit 11-6

/****************************************************************************
* KEY_STATUS_REG
****************************************************************************/

#define KEY_STATUS_REG_adr 0xFF49B6
#define KEY_STATUS_REG _A_KEY_STATUS_REG.Value
#define KEY_STATUS_REG_bit _A_KEY_STATUS_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short KEY_STATUS           : 5; // Bit 4-0
  };
} KEY_STATUS_REG_type __attribute__((aligned(2)));

extern volatile KEY_STATUS_REG_type _A_KEY_STATUS_REG __attribute__((aligned(2)));

#define KEY_STATUS_KEY_STATUS           0x001F // Bit 4-0

/****************************************************************************
* ULP_CTRL_REG
****************************************************************************/

#define ULP_CTRL_REG_adr 0xFF4A00
#define ULP_CTRL_REG _A_ULP_CTRL_REG.Value
#define ULP_CTRL_REG_bit _A_ULP_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ULP_ENABLE           : 1; // Bit 0
    unsigned short ULP_MAIN_SLEEP       : 1; // Bit 1
    unsigned short ULP_TIMER_ON         : 1; // Bit 2
    unsigned short ULP_TIMER_WEN        : 1; // Bit 3
    unsigned short ULP_TIMER_REN        : 1; // Bit 4
    unsigned short ULP_TRIG_EN          : 1; // Bit 5
    unsigned short ULP_XTAL_ON          : 1; // Bit 6
    unsigned short ULP_OSC_ON           : 1; // Bit 7
    unsigned short ULP_CLK_SEL          : 1; // Bit 8
    unsigned short ULP_LATCH_CNT        : 1; // Bit 9
  };
} ULP_CTRL_REG_type __attribute__((aligned(2)));

extern volatile ULP_CTRL_REG_type _A_ULP_CTRL_REG __attribute__((aligned(2)));

#define ULP_CTRL_ULP_ENABLE           0x0001 // Bit 0
#define ULP_CTRL_ULP_MAIN_SLEEP       0x0002 // Bit 1
#define ULP_CTRL_ULP_TIMER_ON         0x0004 // Bit 2
#define ULP_CTRL_ULP_TIMER_WEN        0x0008 // Bit 3
#define ULP_CTRL_ULP_TIMER_REN        0x0010 // Bit 4
#define ULP_CTRL_ULP_TRIG_EN          0x0020 // Bit 5
#define ULP_CTRL_ULP_XTAL_ON          0x0040 // Bit 6
#define ULP_CTRL_ULP_OSC_ON           0x0080 // Bit 7
#define ULP_CTRL_ULP_CLK_SEL          0x0100 // Bit 8
#define ULP_CTRL_ULP_LATCH_CNT        0x0200 // Bit 9

/****************************************************************************
* ULP_TRIG_REG
****************************************************************************/

#define ULP_TRIG_REG_adr 0xFF4A02
#define ULP_TRIG_REG _A_ULP_TRIG_REG.Value
#define ULP_TRIG_REG_bit _A_ULP_TRIG_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ULP_TRIG             : 12; // Bit 11-0
  };
} ULP_TRIG_REG_type __attribute__((aligned(2)));

extern volatile ULP_TRIG_REG_type _A_ULP_TRIG_REG __attribute__((aligned(2)));

#define ULP_TRIG_ULP_TRIG             0x0FFF // Bit 11-0

/****************************************************************************
* ULP_PORT_REG
****************************************************************************/

#define ULP_PORT_REG_adr 0xFF4A04
#define ULP_PORT_REG _A_ULP_PORT_REG.Value
#define ULP_PORT_REG_bit _A_ULP_PORT_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ULP_PORT_VAL         : 1; // Bit 0
    unsigned short ULP_PORT_DIR         : 2; // Bit 2-1
    unsigned short ULP_PORT_IE          : 1; // Bit 3
    unsigned short ULP_PORT_TRIG        : 2; // Bit 5-4
    unsigned short ULP_PORT_WEN         : 1; // Bit 6
    unsigned short ULP_PORT_MODE        : 1; // Bit 7
  };
} ULP_PORT_REG_type __attribute__((aligned(2)));

extern volatile ULP_PORT_REG_type _A_ULP_PORT_REG __attribute__((aligned(2)));

#define ULP_PORT_ULP_PORT_VAL         0x0001 // Bit 0
#define ULP_PORT_ULP_PORT_DIR         0x0006 // Bit 2-1
#define ULP_PORT_ULP_PORT_IE          0x0008 // Bit 3
#define ULP_PORT_ULP_PORT_TRIG        0x0030 // Bit 5-4
#define ULP_PORT_ULP_PORT_WEN         0x0040 // Bit 6
#define ULP_PORT_ULP_PORT_MODE        0x0080 // Bit 7

/****************************************************************************
* ULP_PHASE_REG
****************************************************************************/

#define ULP_PHASE_REG_adr 0xFF4A06
#define ULP_PHASE_REG _A_ULP_PHASE_REG.Value
#define ULP_PHASE_REG_bit _A_ULP_PHASE_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ULP_PHASE            : 9; // Bit 8-0
    unsigned short                      : 6; // Bit 14-9
    unsigned short ULP_PH_BUSY          : 1; // Bit 15
  };
} ULP_PHASE_REG_type __attribute__((aligned(2)));

extern volatile ULP_PHASE_REG_type _A_ULP_PHASE_REG __attribute__((aligned(2)));

#define ULP_PHASE_ULP_PHASE            0x01FF // Bit 8-0
#define ULP_PHASE_ULP_PH_BUSY          0x8000 // Bit 15

/****************************************************************************
* ULP_TIMERL_REG
****************************************************************************/

#define ULP_TIMERL_REG_adr 0xFF4A08
#define ULP_TIMERL_REG _A_ULP_TIMERL_REG

extern volatile unsigned short _A_ULP_TIMERL_REG;

/****************************************************************************
* ULP_TIMERH_REG
****************************************************************************/

#define ULP_TIMERH_REG_adr 0xFF4A0A
#define ULP_TIMERH_REG _A_ULP_TIMERH_REG

extern volatile unsigned short _A_ULP_TIMERH_REG;

/****************************************************************************
* ULP_WAKEUPL_REG
****************************************************************************/

#define ULP_WAKEUPL_REG_adr 0xFF4A0C
#define ULP_WAKEUPL_REG _A_ULP_WAKEUPL_REG

extern volatile unsigned short _A_ULP_WAKEUPL_REG;

/****************************************************************************
* ULP_WAKEUPH_REG
****************************************************************************/

#define ULP_WAKEUPH_REG_adr 0xFF4A0E
#define ULP_WAKEUPH_REG _A_ULP_WAKEUPH_REG

extern volatile unsigned short _A_ULP_WAKEUPH_REG;

/****************************************************************************
* ULP_STATUS_REG
****************************************************************************/

#define ULP_STATUS_REG_adr 0xFF4A10
#define ULP_STATUS_REG _A_ULP_STATUS_REG.Value
#define ULP_STATUS_REG_bit _A_ULP_STATUS_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ULP_TIMER_STS        : 1; // Bit 0
    unsigned short ULP_PORT_STS         : 1; // Bit 1
    unsigned short ULP_TIMER_STSR       : 1; // Bit 2
    unsigned short ULP_PORT_STSR        : 1; // Bit 3
    unsigned short ULP_XTAL_VAL         : 1; // Bit 4
    unsigned short ULP_XTAL_OK          : 1; // Bit 5
    unsigned short ULP_OSC_VAL          : 1; // Bit 6
    unsigned short ULP_WAKEUP_VAL       : 1; // Bit 7
    unsigned short ULP_TRIG_VAL         : 1; // Bit 8
  };
} ULP_STATUS_REG_type __attribute__((aligned(2)));

extern volatile ULP_STATUS_REG_type _A_ULP_STATUS_REG __attribute__((aligned(2)));

#define ULP_STATUS_ULP_TIMER_STS        0x0001 // Bit 0
#define ULP_STATUS_ULP_PORT_STS         0x0002 // Bit 1
#define ULP_STATUS_ULP_TIMER_STSR       0x0004 // Bit 2
#define ULP_STATUS_ULP_PORT_STSR        0x0008 // Bit 3
#define ULP_STATUS_ULP_XTAL_VAL         0x0010 // Bit 4
#define ULP_STATUS_ULP_XTAL_OK          0x0020 // Bit 5
#define ULP_STATUS_ULP_OSC_VAL          0x0040 // Bit 6
#define ULP_STATUS_ULP_WAKEUP_VAL       0x0080 // Bit 7
#define ULP_STATUS_ULP_TRIG_VAL         0x0100 // Bit 8

/****************************************************************************
* ULP_TEST_REG
****************************************************************************/

#define ULP_TEST_REG_adr 0xFF4A12
#define ULP_TEST_REG _A_ULP_TEST_REG

extern volatile unsigned short _A_ULP_TEST_REG;

/****************************************************************************
* WATCHDOG_REG
****************************************************************************/

#define WATCHDOG_REG_adr 0xFF4C00
#define WATCHDOG_REG _A_WATCHDOG_REG

extern volatile unsigned short _A_WATCHDOG_REG;

/****************************************************************************
* SET_FREEZE_REG
****************************************************************************/

#define SET_FREEZE_REG_adr 0xFF5000
#define SET_FREEZE_REG _A_SET_FREEZE_REG

extern volatile unsigned short _A_SET_FREEZE_REG __attribute__((aligned(2)));

/****************************************************************************
* RESET_FREEZE_REG
****************************************************************************/

#define RESET_FREEZE_REG_adr 0xFF5002
#define RESET_FREEZE_REG _A_RESET_FREEZE_REG

extern volatile unsigned short _A_RESET_FREEZE_REG __attribute__((aligned(2)));

#define FRZ_DIP                        0x0001
#define FRZ_TIM0                       0x0002
#define FRZ_TIM1                       0x0004
#define FRZ_WDOG                       0x0008
#define FRZ_DMA0                       0x0010
#define FRZ_DMA1                       0x0020
#define FRZ_DMA2                       0x0040
#define FRZ_DMA3                       0x0080

/****************************************************************************
* DEBUG_REG
****************************************************************************/

#define DEBUG_REG_adr 0xFF5004
#define DEBUG_REG _A_DEBUG_REG.Value
#define DEBUG_REG_bit _A_DEBUG_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CLK100_EDGE          : 1; // Bit 0
    unsigned short CLK100_NEG           : 1; // Bit 1
    unsigned short CLK100_POS           : 1; // Bit 2
    unsigned short CLK100_SRC           : 1; // Bit 3
    unsigned short ENV_B01              : 1; // Bit 4
    unsigned short                      : 2; // Bit 6-5
    unsigned short SW_RESET             : 1; // Bit 7
    unsigned short                      : 1; // Bit 8
    unsigned short                      : 1; // Bit 9
    unsigned short                      : 1; // Bit 10
    unsigned short CR16_DBGM            : 1; // Bit 11
    unsigned short ALIAS_DIPRAM         : 1; // Bit 12
    unsigned short OWI_SEL_SYNC         : 1; // Bit 13
  };
} DEBUG_REG_type __attribute__((aligned(2)));

extern volatile DEBUG_REG_type _A_DEBUG_REG __attribute__((aligned(2)));

#define DEBUG_CLK100_EDGE          0x0001 // Bit 0
#define DEBUG_CLK100_NEG           0x0002 // Bit 1
#define DEBUG_CLK100_POS           0x0004 // Bit 2
#define DEBUG_CLK100_SRC           0x0008 // Bit 3
#define DEBUG_ENV_B01              0x0010 // Bit 4
#define DEBUG_SW_RESET             0x0080 // Bit 7
#define DEBUG_CR16_DBGM            0x0800 // Bit 11
#define DEBUG_ALIAS_DIPRAM         0x1000 // Bit 12
#define DEBUG_OWI_SEL_SYNC         0x2000 // Bit 13

/****************************************************************************
* CACHE_CTRL_REG
****************************************************************************/

#define CACHE_CTRL_REG_adr 0xFF5010
#define CACHE_CTRL_REG _A_CACHE_CTRL_REG.Value
#define CACHE_CTRL_REG_bit _A_CACHE_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CACHE_SIZE           : 3; // Bit 2-0
    unsigned short                      : 1; // Bit 3
    unsigned short CACHE_MODE           : 2; // Bit 5-4
    unsigned short CACHE_LOCK           : 1; // Bit 6
    unsigned short                      : 1; // Bit 7
    unsigned short ICACHE_B_SIZE        : 1; // Bit 8
    unsigned short                      : 1; // Bit 9
    unsigned short DCACHE_B_SIZE        : 1; // Bit 10
  };
} CACHE_CTRL_REG_type __attribute__((aligned(2)));

extern volatile CACHE_CTRL_REG_type _A_CACHE_CTRL_REG __attribute__((aligned(2)));

#define CACHE_CTRL_CACHE_SIZE           0x0007 // Bit 2-0
#define CACHE_CTRL_CACHE_MODE           0x0030 // Bit 5-4
#define CACHE_CTRL_CACHE_LOCK           0x0040 // Bit 6
#define CACHE_CTRL_ICACHE_B_SIZE        0x0100 // Bit 8
#define CACHE_CTRL_DCACHE_B_SIZE        0x0400 // Bit 10

/****************************************************************************
* CACHE_LEN0_REG
****************************************************************************/

#define CACHE_LEN0_REG_adr 0xFF5012
#define CACHE_LEN0_REG _A_CACHE_LEN0_REG.Value
#define CACHE_LEN0_REG_bit _A_CACHE_LEN0_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CACHE_LEN0           : 9; // Bit 8-0
  };
} CACHE_LEN0_REG_type __attribute__((aligned(2)));

extern volatile CACHE_LEN0_REG_type _A_CACHE_LEN0_REG __attribute__((aligned(2)));

#define CACHE_LEN0_CACHE_LEN0           0x01FF // Bit 8-0

/****************************************************************************
* CACHE_START0_REG
****************************************************************************/

#define CACHE_START0_REG_adr 0xFF5014
#define CACHE_START0_REG _A_CACHE_START0_REG.Value
#define CACHE_START0_REG_bit _A_CACHE_START0_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CACHE_START0         : 9; // Bit 8-0
  };
} CACHE_START0_REG_type __attribute__((aligned(2)));

extern volatile CACHE_START0_REG_type _A_CACHE_START0_REG __attribute__((aligned(2)));

#define CACHE_START0_CACHE_START0         0x01FF // Bit 8-0

/****************************************************************************
* CACHE_LEN1_REG
****************************************************************************/

#define CACHE_LEN1_REG_adr 0xFF5016
#define CACHE_LEN1_REG _A_CACHE_LEN1_REG.Value
#define CACHE_LEN1_REG_bit _A_CACHE_LEN1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CACHE_LEN1           : 9; // Bit 8-0
  };
} CACHE_LEN1_REG_type __attribute__((aligned(2)));

extern volatile CACHE_LEN1_REG_type _A_CACHE_LEN1_REG __attribute__((aligned(2)));

#define CACHE_LEN1_CACHE_LEN1           0x01FF // Bit 8-0

/****************************************************************************
* CACHE_START1_REG
****************************************************************************/

#define CACHE_START1_REG_adr 0xFF5018
#define CACHE_START1_REG _A_CACHE_START1_REG.Value
#define CACHE_START1_REG_bit _A_CACHE_START1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CACHE_START1         : 9; // Bit 8-0
  };
} CACHE_START1_REG_type __attribute__((aligned(2)));

extern volatile CACHE_START1_REG_type _A_CACHE_START1_REG __attribute__((aligned(2)));

#define CACHE_START1_CACHE_START1         0x01FF // Bit 8-0

/****************************************************************************
* CACHE_STATUS_REG
****************************************************************************/

#define CACHE_STATUS_REG_adr 0xFF501A
#define CACHE_STATUS_REG _A_CACHE_STATUS_REG.Value
#define CACHE_STATUS_REG_bit _A_CACHE_STATUS_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 10; // Bit 9-0
    unsigned short ICACHE_HIT           : 1; // Bit 10
    unsigned short DCACHE_HIT           : 1; // Bit 11
    unsigned short CACHE_TOUCH_TOGGLE   : 1; // Bit 12
    unsigned short CACHE_TOUCH          : 1; // Bit 13
  };
} CACHE_STATUS_REG_type __attribute__((aligned(2)));

extern volatile CACHE_STATUS_REG_type _A_CACHE_STATUS_REG __attribute__((aligned(2)));

#define CACHE_STATUS_ICACHE_HIT           0x0400 // Bit 10
#define CACHE_STATUS_DCACHE_HIT           0x0800 // Bit 11
#define CACHE_STATUS_CACHE_TOUCH_TOGGLE   0x1000 // Bit 12
#define CACHE_STATUS_CACHE_TOUCH          0x2000 // Bit 13

/****************************************************************************
* CACHE_TEST_REG
****************************************************************************/

#define CACHE_TEST_REG_adr 0xFF501C
#define CACHE_TEST_REG _A_CACHE_TEST_REG.Value
#define CACHE_TEST_REG_bit _A_CACHE_TEST_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CACHE_TEST           : 1; // Bit 0
  };
} CACHE_TEST_REG_type __attribute__((aligned(2)));

extern volatile CACHE_TEST_REG_type _A_CACHE_TEST_REG __attribute__((aligned(2)));

#define CACHE_TEST_CACHE_TEST           0x0001 // Bit 0

/****************************************************************************
* TRACE_CTRL_REG
****************************************************************************/

#define TRACE_CTRL_REG_adr 0xFF5020
#define TRACE_CTRL_REG _A_TRACE_CTRL_REG.Value
#define TRACE_CTRL_REG_bit _A_TRACE_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TRACE_SIZE           : 3; // Bit 2-0
    unsigned short TRACE_COND           : 1; // Bit 3
    unsigned short EXT_EVENTS_ON        : 1; // Bit 4
    unsigned short DIP_EVENTS_ON        : 1; // Bit 5
    unsigned short DSP_EVENTS_ON        : 1; // Bit 6
    unsigned short BUS_EVENTS_ON        : 1; // Bit 7
    unsigned short D_TRACE_EV_ON        : 1; // Bit 8
    unsigned short I_TRACE_EV_ON        : 1; // Bit 9
    unsigned short D_TRACE_ON           : 1; // Bit 10
    unsigned short I_TRACE_ON           : 1; // Bit 11
    unsigned short TRACE_COND_EXT       : 3; // Bit 14-12
    unsigned short TRACE_MODE           : 1; // Bit 15
  };
} TRACE_CTRL_REG_type __attribute__((aligned(2)));

extern volatile TRACE_CTRL_REG_type _A_TRACE_CTRL_REG __attribute__((aligned(2)));

#define TRACE_CTRL_TRACE_SIZE           0x0007 // Bit 2-0
#define TRACE_CTRL_TRACE_COND           0x0008 // Bit 3
#define TRACE_CTRL_EXT_EVENTS_ON        0x0010 // Bit 4
#define TRACE_CTRL_DIP_EVENTS_ON        0x0020 // Bit 5
#define TRACE_CTRL_DSP_EVENTS_ON        0x0040 // Bit 6
#define TRACE_CTRL_BUS_EVENTS_ON        0x0080 // Bit 7
#define TRACE_CTRL_D_TRACE_EV_ON        0x0100 // Bit 8
#define TRACE_CTRL_I_TRACE_EV_ON        0x0200 // Bit 9
#define TRACE_CTRL_D_TRACE_ON           0x0400 // Bit 10
#define TRACE_CTRL_I_TRACE_ON           0x0800 // Bit 11
#define TRACE_CTRL_TRACE_COND_EXT       0x7000 // Bit 14-12
#define TRACE_CTRL_TRACE_MODE           0x8000 // Bit 15

/****************************************************************************
* TRACE_STATUS_REG
****************************************************************************/

#define TRACE_STATUS_REG_adr 0xFF5022
#define TRACE_STATUS_REG _A_TRACE_STATUS_REG.Value
#define TRACE_STATUS_REG_bit _A_TRACE_STATUS_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TRACE_IDX            : 11; // Bit 10-0
    unsigned short                      : 1; // Bit 11
    unsigned short                      : 1; // Bit 12
    unsigned short TRACE_TOUCH_TOGGLE   : 1; // Bit 13
    unsigned short TRACE_EOB            : 1; // Bit 14
    unsigned short TRACE_BUSY           : 1; // Bit 15
  };
} TRACE_STATUS_REG_type __attribute__((aligned(2)));

extern volatile TRACE_STATUS_REG_type _A_TRACE_STATUS_REG __attribute__((aligned(2)));

#define TRACE_STATUS_TRACE_IDX            0x07FF // Bit 10-0
#define TRACE_STATUS_TRACE_TOUCH_TOGGLE   0x2000 // Bit 13
#define TRACE_STATUS_TRACE_EOB            0x4000 // Bit 14
#define TRACE_STATUS_TRACE_BUSY           0x8000 // Bit 15

/****************************************************************************
* TRACE_START0_REG
****************************************************************************/

#define TRACE_START0_REG_adr 0xFF5024
#define TRACE_START0_REG _A_TRACE_START0_REG.Value
#define TRACE_START0_REG_bit _A_TRACE_START0_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TRACE_START0         : 15; // Bit 14-0
  };
} TRACE_START0_REG_type __attribute__((aligned(2)));

extern volatile TRACE_START0_REG_type _A_TRACE_START0_REG __attribute__((aligned(2)));

#define TRACE_START0_TRACE_START0         0x7FFF // Bit 14-0

/****************************************************************************
* TRACE_LEN0_REG
****************************************************************************/

#define TRACE_LEN0_REG_adr 0xFF5026
#define TRACE_LEN0_REG _A_TRACE_LEN0_REG.Value
#define TRACE_LEN0_REG_bit _A_TRACE_LEN0_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TRACE_LEN0           : 15; // Bit 14-0
  };
} TRACE_LEN0_REG_type __attribute__((aligned(2)));

extern volatile TRACE_LEN0_REG_type _A_TRACE_LEN0_REG __attribute__((aligned(2)));

#define TRACE_LEN0_TRACE_LEN0           0x7FFF // Bit 14-0

/****************************************************************************
* TRACE_START1_REG
****************************************************************************/

#define TRACE_START1_REG_adr 0xFF5028
#define TRACE_START1_REG _A_TRACE_START1_REG.Value
#define TRACE_START1_REG_bit _A_TRACE_START1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TRACE_START1         : 15; // Bit 14-0
  };
} TRACE_START1_REG_type __attribute__((aligned(2)));

extern volatile TRACE_START1_REG_type _A_TRACE_START1_REG __attribute__((aligned(2)));

#define TRACE_START1_TRACE_START1         0x7FFF // Bit 14-0

/****************************************************************************
* TRACE_LEN1_REG
****************************************************************************/

#define TRACE_LEN1_REG_adr 0xFF502A
#define TRACE_LEN1_REG _A_TRACE_LEN1_REG.Value
#define TRACE_LEN1_REG_bit _A_TRACE_LEN1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TRACE_LEN1           : 15; // Bit 14-0
  };
} TRACE_LEN1_REG_type __attribute__((aligned(2)));

extern volatile TRACE_LEN1_REG_type _A_TRACE_LEN1_REG __attribute__((aligned(2)));

#define TRACE_LEN1_TRACE_LEN1           0x7FFF // Bit 14-0

/****************************************************************************
* TRACE_TIMERL_REG
****************************************************************************/

#define TRACE_TIMERL_REG_adr 0xFF502C
#define TRACE_TIMERL_REG _A_TRACE_TIMERL_REG

extern volatile unsigned short _A_TRACE_TIMERL_REG;

/****************************************************************************
* TRACE_TIMERH_REG
****************************************************************************/

#define TRACE_TIMERH_REG_adr 0xFF502E
#define TRACE_TIMERH_REG _A_TRACE_TIMERH_REG

extern volatile unsigned short _A_TRACE_TIMERH_REG;

/****************************************************************************
* SET_INT_PENDING_REG
****************************************************************************/

#define SET_INT_PENDING_REG_adr 0xFF5400
#define SET_INT_PENDING_REG _A_SET_INT_PENDING_REG

extern volatile unsigned short _A_SET_INT_PENDING_REG __attribute__((aligned(2)));

/****************************************************************************
* RESET_INT_PENDING_REG
****************************************************************************/

#define RESET_INT_PENDING_REG_adr 0xFF5402
#define RESET_INT_PENDING_REG _A_RESET_INT_PENDING_REG

extern volatile unsigned short _A_RESET_INT_PENDING_REG __attribute__((aligned(2)));

#define ACCESS_INT_PEND                0x0001
#define KEYB_INT_PEND                  0x0002
#define UART2_RI_TI_INT_PEND           0x0004
#define CT_CLASSD_INT_PEND             0x0008
#define UART_RI_INT_PEND               0x0010
#define UART_TI_INT_PEND               0x0020
#define SPI_INT_PEND                   0x0040
#define TIM0_INT_PEND                  0x0080
#define TIM1_INT_PEND                  0x0100
#define CLK100_INT_PEND                0x0200
#define DIP_INT_PEND                   0x0400
#define AD_INT_PEND                    0x0800
#define SPI2_INT_PEND                  0x1000
#define DSP_INT_PEND                   0x2000
#define ULP_INT_PEND                   0x4000

/****************************************************************************
* INT0_PRIORITY_REG
****************************************************************************/

#define INT0_PRIORITY_REG_adr 0xFF5404
#define INT0_PRIORITY_REG _A_INT0_PRIORITY_REG.Value
#define INT0_PRIORITY_REG_bit _A_INT0_PRIORITY_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SPI2_INT_PRIO        : 3; // Bit 2-0
    unsigned short                      : 1; // Bit 3
    unsigned short DSP_INT_PRIO         : 3; // Bit 6-4
    unsigned short                      : 1; // Bit 7
    unsigned short ULP_INT_PRIO         : 3; // Bit 10-8
  };
} INT0_PRIORITY_REG_type __attribute__((aligned(2)));

extern volatile INT0_PRIORITY_REG_type _A_INT0_PRIORITY_REG __attribute__((aligned(2)));

#define INT0_PRIORITY_SPI2_INT_PRIO        0x0007 // Bit 2-0
#define INT0_PRIORITY_DSP_INT_PRIO         0x0070 // Bit 6-4
#define INT0_PRIORITY_ULP_INT_PRIO         0x0700 // Bit 10-8

/****************************************************************************
* INT1_PRIORITY_REG
****************************************************************************/

#define INT1_PRIORITY_REG_adr 0xFF5406
#define INT1_PRIORITY_REG _A_INT1_PRIORITY_REG.Value
#define INT1_PRIORITY_REG_bit _A_INT1_PRIORITY_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TIM1_INT_PRIO        : 3; // Bit 2-0
    unsigned short                      : 1; // Bit 3
    unsigned short CLK100_INT_PRIO      : 3; // Bit 6-4
    unsigned short                      : 1; // Bit 7
    unsigned short DIP_INT_PRIO         : 3; // Bit 10-8
    unsigned short                      : 1; // Bit 11
    unsigned short AD_INT_PRIO          : 3; // Bit 14-12
  };
} INT1_PRIORITY_REG_type __attribute__((aligned(2)));

extern volatile INT1_PRIORITY_REG_type _A_INT1_PRIORITY_REG __attribute__((aligned(2)));

#define INT1_PRIORITY_TIM1_INT_PRIO        0x0007 // Bit 2-0
#define INT1_PRIORITY_CLK100_INT_PRIO      0x0070 // Bit 6-4
#define INT1_PRIORITY_DIP_INT_PRIO         0x0700 // Bit 10-8
#define INT1_PRIORITY_AD_INT_PRIO          0x7000 // Bit 14-12

/****************************************************************************
* INT2_PRIORITY_REG
****************************************************************************/

#define INT2_PRIORITY_REG_adr 0xFF5408
#define INT2_PRIORITY_REG _A_INT2_PRIORITY_REG.Value
#define INT2_PRIORITY_REG_bit _A_INT2_PRIORITY_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short UART_RI_INT_PRIO     : 3; // Bit 2-0
    unsigned short                      : 1; // Bit 3
    unsigned short UART_TI_INT_PRIO     : 3; // Bit 6-4
    unsigned short                      : 1; // Bit 7
    unsigned short SPI_INT_PRIO         : 3; // Bit 10-8
    unsigned short                      : 1; // Bit 11
    unsigned short TIM0_INT_PRIO        : 3; // Bit 14-12
  };
} INT2_PRIORITY_REG_type __attribute__((aligned(2)));

extern volatile INT2_PRIORITY_REG_type _A_INT2_PRIORITY_REG __attribute__((aligned(2)));

#define INT2_PRIORITY_UART_RI_INT_PRIO     0x0007 // Bit 2-0
#define INT2_PRIORITY_UART_TI_INT_PRIO     0x0070 // Bit 6-4
#define INT2_PRIORITY_SPI_INT_PRIO         0x0700 // Bit 10-8
#define INT2_PRIORITY_TIM0_INT_PRIO        0x7000 // Bit 14-12

/****************************************************************************
* INT3_PRIORITY_REG
****************************************************************************/

#define INT3_PRIORITY_REG_adr 0xFF540A
#define INT3_PRIORITY_REG _A_INT3_PRIORITY_REG.Value
#define INT3_PRIORITY_REG_bit _A_INT3_PRIORITY_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ACCESS_INT_PRIO      : 3; // Bit 2-0
    unsigned short                      : 1; // Bit 3
    unsigned short KEYB_INT_PRIO        : 3; // Bit 6-4
    unsigned short                      : 1; // Bit 7
    unsigned short UART2_RI_TI_INT_PRIO  : 3; // Bit 10-8
    unsigned short                      : 1; // Bit 11
    unsigned short CT_CLASSD_INT_PRIO   : 3; // Bit 14-12
  };
} INT3_PRIORITY_REG_type __attribute__((aligned(2)));

extern volatile INT3_PRIORITY_REG_type _A_INT3_PRIORITY_REG __attribute__((aligned(2)));

#define INT3_PRIORITY_ACCESS_INT_PRIO      0x0007 // Bit 2-0
#define INT3_PRIORITY_KEYB_INT_PRIO        0x0070 // Bit 6-4
#define INT3_PRIORITY_UART2_RI_TI_INT_PRIO  0x0700 // Bit 10-8
#define INT3_PRIORITY_CT_CLASSD_INT_PRIO   0x7000 // Bit 14-12

/****************************************************************************
* PC_START_REG
****************************************************************************/

#define PC_START_REG_adr 0xFF540C
#define PC_START_REG _A_PC_START_REG.Value
#define PC_START_REG_bit _A_PC_START_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PC_START10           : 2; // Bit 1-0
    unsigned short PC_START             : 14; // Bit 15-2
  };
} PC_START_REG_type __attribute__((aligned(2)));

extern volatile PC_START_REG_type _A_PC_START_REG __attribute__((aligned(2)));

#define PC_START_PC_START10           0x0003 // Bit 1-0
#define PC_START_PC_START             0xFFFC // Bit 15-2

/****************************************************************************
* CODEC_MIC_REG
****************************************************************************/

#define CODEC_MIC_REG_adr 0xFF5800
#define CODEC_MIC_REG _A_CODEC_MIC_REG.Value
#define CODEC_MIC_REG_bit _A_CODEC_MIC_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short MIC_MODE             : 2; // Bit 1-0
    unsigned short MIC_PD               : 1; // Bit 2
    unsigned short MIC_MUTE             : 1; // Bit 3
    unsigned short MIC_GAIN             : 4; // Bit 7-4
    unsigned short MIC_OFFCOM_SG        : 1; // Bit 8
    unsigned short MIC_OFFCOM_ON        : 1; // Bit 9
    unsigned short DSP_CTRL             : 1; // Bit 10
    unsigned short MICH_ON              : 1; // Bit 11
    unsigned short MIC_CADJ             : 2; // Bit 13-12
    unsigned short MICHP_ON             : 1; // Bit 14
    unsigned short MIC_LSR_ON           : 1; // Bit 15
  };
} CODEC_MIC_REG_type __attribute__((aligned(2)));

extern volatile CODEC_MIC_REG_type _A_CODEC_MIC_REG __attribute__((aligned(2)));

#define CODEC_MIC_MIC_MODE             0x0003 // Bit 1-0
#define CODEC_MIC_MIC_PD               0x0004 // Bit 2
#define CODEC_MIC_MIC_MUTE             0x0008 // Bit 3
#define CODEC_MIC_MIC_GAIN             0x00F0 // Bit 7-4
#define CODEC_MIC_MIC_OFFCOM_SG        0x0100 // Bit 8
#define CODEC_MIC_MIC_OFFCOM_ON        0x0200 // Bit 9
#define CODEC_MIC_DSP_CTRL             0x0400 // Bit 10
#define CODEC_MIC_MICH_ON              0x0800 // Bit 11
#define CODEC_MIC_MIC_CADJ             0x3000 // Bit 13-12
#define CODEC_MIC_MICHP_ON             0x4000 // Bit 14
#define CODEC_MIC_MIC_LSR_ON           0x8000 // Bit 15

/****************************************************************************
* CODEC_LSR_REG
****************************************************************************/

#define CODEC_LSR_REG_adr 0xFF5802
#define CODEC_LSR_REG _A_CODEC_LSR_REG.Value
#define CODEC_LSR_REG_bit _A_CODEC_LSR_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short LSRP_MODE            : 2; // Bit 1-0
    unsigned short LSRP_PD              : 1; // Bit 2
    unsigned short LSRN_MODE            : 2; // Bit 4-3
    unsigned short LSRN_PD              : 1; // Bit 5
    unsigned short LSRATT               : 3; // Bit 8-6
    unsigned short LSREN_SE             : 1; // Bit 9
  };
} CODEC_LSR_REG_type __attribute__((aligned(2)));

extern volatile CODEC_LSR_REG_type _A_CODEC_LSR_REG __attribute__((aligned(2)));

#define CODEC_LSR_LSRP_MODE            0x0003 // Bit 1-0
#define CODEC_LSR_LSRP_PD              0x0004 // Bit 2
#define CODEC_LSR_LSRN_MODE            0x0018 // Bit 4-3
#define CODEC_LSR_LSRN_PD              0x0020 // Bit 5
#define CODEC_LSR_LSRATT               0x01C0 // Bit 8-6
#define CODEC_LSR_LSREN_SE             0x0200 // Bit 9

/****************************************************************************
* CODEC_VREF_REG
****************************************************************************/

#define CODEC_VREF_REG_adr 0xFF5804
#define CODEC_VREF_REG _A_CODEC_VREF_REG.Value
#define CODEC_VREF_REG_bit _A_CODEC_VREF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short VREF_PD              : 1; // Bit 0
    unsigned short VREF_FILT_PD         : 1; // Bit 1
    unsigned short VREF_FILT_CADJ       : 2; // Bit 3-2
    unsigned short VREF_INIT            : 1; // Bit 4
    unsigned short AMP1V5_PD            : 1; // Bit 5
    unsigned short VREF_BG_PD           : 1; // Bit 6
    unsigned short BIAS_PD              : 1; // Bit 7
    unsigned short AGND_LSR_PD          : 1; // Bit 8
    unsigned short REFINT_PD            : 1; // Bit 9
  };
} CODEC_VREF_REG_type __attribute__((aligned(2)));

extern volatile CODEC_VREF_REG_type _A_CODEC_VREF_REG __attribute__((aligned(2)));

#define CODEC_VREF_VREF_PD              0x0001 // Bit 0
#define CODEC_VREF_VREF_FILT_PD         0x0002 // Bit 1
#define CODEC_VREF_VREF_FILT_CADJ       0x000C // Bit 3-2
#define CODEC_VREF_VREF_INIT            0x0010 // Bit 4
#define CODEC_VREF_AMP1V5_PD            0x0020 // Bit 5
#define CODEC_VREF_VREF_BG_PD           0x0040 // Bit 6
#define CODEC_VREF_BIAS_PD              0x0080 // Bit 7
#define CODEC_VREF_AGND_LSR_PD          0x0100 // Bit 8
#define CODEC_VREF_REFINT_PD            0x0200 // Bit 9

/****************************************************************************
* CODEC_TONE_REG
****************************************************************************/

#define CODEC_TONE_REG_adr 0xFF5806
#define CODEC_TONE_REG _A_CODEC_TONE_REG.Value
#define CODEC_TONE_REG_bit _A_CODEC_TONE_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CID_PD               : 1; // Bit 0
    unsigned short CID_PR_DIS           : 1; // Bit 1
    unsigned short RNG_PD               : 1; // Bit 2
    unsigned short RNG_PR_DIS           : 1; // Bit 3
    unsigned short PARA_PD              : 1; // Bit 4
    unsigned short PARA_PR_DIS          : 1; // Bit 5
    unsigned short RNG_CMP_PD           : 1; // Bit 6
  };
} CODEC_TONE_REG_type __attribute__((aligned(2)));

extern volatile CODEC_TONE_REG_type _A_CODEC_TONE_REG __attribute__((aligned(2)));

#define CODEC_TONE_CID_PD               0x0001 // Bit 0
#define CODEC_TONE_CID_PR_DIS           0x0002 // Bit 1
#define CODEC_TONE_RNG_PD               0x0004 // Bit 2
#define CODEC_TONE_RNG_PR_DIS           0x0008 // Bit 3
#define CODEC_TONE_PARA_PD              0x0010 // Bit 4
#define CODEC_TONE_PARA_PR_DIS          0x0020 // Bit 5
#define CODEC_TONE_RNG_CMP_PD           0x0040 // Bit 6

/****************************************************************************
* CODEC_ADDA_REG
****************************************************************************/

#define CODEC_ADDA_REG_adr 0xFF5808
#define CODEC_ADDA_REG _A_CODEC_ADDA_REG.Value
#define CODEC_ADDA_REG_bit _A_CODEC_ADDA_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DA_PD                : 1; // Bit 0
    unsigned short AD_PD                : 1; // Bit 1
    unsigned short DA_CADJ              : 2; // Bit 3-2
    unsigned short AD_CADJ              : 2; // Bit 5-4
    unsigned short DA_DITH_OFF          : 1; // Bit 6
    unsigned short AD_DITH_OFF          : 1; // Bit 7
    unsigned short DA_HBW               : 1; // Bit 8
    unsigned short LPF_PD               : 1; // Bit 9
    unsigned short LPF_BW               : 3; // Bit 12-10
    unsigned short ADC_VREF_LSR         : 2; // Bit 14-13
    unsigned short AUTO_SYNC            : 1; // Bit 15
  };
} CODEC_ADDA_REG_type __attribute__((aligned(2)));

extern volatile CODEC_ADDA_REG_type _A_CODEC_ADDA_REG __attribute__((aligned(2)));

#define CODEC_ADDA_DA_PD                0x0001 // Bit 0
#define CODEC_ADDA_AD_PD                0x0002 // Bit 1
#define CODEC_ADDA_DA_CADJ              0x000C // Bit 3-2
#define CODEC_ADDA_AD_CADJ              0x0030 // Bit 5-4
#define CODEC_ADDA_DA_DITH_OFF          0x0040 // Bit 6
#define CODEC_ADDA_AD_DITH_OFF          0x0080 // Bit 7
#define CODEC_ADDA_DA_HBW               0x0100 // Bit 8
#define CODEC_ADDA_LPF_PD               0x0200 // Bit 9
#define CODEC_ADDA_LPF_BW               0x1C00 // Bit 12-10
#define CODEC_ADDA_ADC_VREF_LSR         0x6000 // Bit 14-13
#define CODEC_ADDA_AUTO_SYNC            0x8000 // Bit 15

/****************************************************************************
* CODEC_OFFSET1_REG
****************************************************************************/

#define CODEC_OFFSET1_REG_adr 0xFF580A
#define CODEC_OFFSET1_REG _A_CODEC_OFFSET1_REG

extern volatile unsigned short _A_CODEC_OFFSET1_REG;

/****************************************************************************
* CODEC_TEST_CTRL_REG
****************************************************************************/

#define CODEC_TEST_CTRL_REG_adr 0xFF580C
#define CODEC_TEST_CTRL_REG _A_CODEC_TEST_CTRL_REG.Value
#define CODEC_TEST_CTRL_REG_bit _A_CODEC_TEST_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TCR                  : 12; // Bit 11-0
    unsigned short COR_ON               : 1; // Bit 12
    unsigned short COR_STAT             : 1; // Bit 13
    unsigned short CODEC_PROT           : 1; // Bit 14
  };
} CODEC_TEST_CTRL_REG_type __attribute__((aligned(2)));

extern volatile CODEC_TEST_CTRL_REG_type _A_CODEC_TEST_CTRL_REG __attribute__((aligned(2)));

#define CODEC_TEST_CTRL_TCR                  0x0FFF // Bit 11-0
#define CODEC_TEST_CTRL_COR_ON               0x1000 // Bit 12
#define CODEC_TEST_CTRL_COR_STAT             0x2000 // Bit 13
#define CODEC_TEST_CTRL_CODEC_PROT           0x4000 // Bit 14

/****************************************************************************
* CODEC_OFFSET2_REG
****************************************************************************/

#define CODEC_OFFSET2_REG_adr 0xFF580E
#define CODEC_OFFSET2_REG _A_CODEC_OFFSET2_REG

extern volatile unsigned short _A_CODEC_OFFSET2_REG;

/****************************************************************************
* CODEC_MIC_AUTO_REG
****************************************************************************/

#define CODEC_MIC_AUTO_REG_adr 0xFF5816
#define CODEC_MIC_AUTO_REG _A_CODEC_MIC_AUTO_REG.Value
#define CODEC_MIC_AUTO_REG_bit _A_CODEC_MIC_AUTO_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short MIC_CONFIG           : 3; // Bit 2-0
  };
} CODEC_MIC_AUTO_REG_type __attribute__((aligned(2)));

extern volatile CODEC_MIC_AUTO_REG_type _A_CODEC_MIC_AUTO_REG __attribute__((aligned(2)));

#define CODEC_MIC_AUTO_MIC_CONFIG           0x0007 // Bit 2-0

/****************************************************************************
* CODEC_LSR_AUTO_REG
****************************************************************************/

#define CODEC_LSR_AUTO_REG_adr 0xFF5818
#define CODEC_LSR_AUTO_REG _A_CODEC_LSR_AUTO_REG.Value
#define CODEC_LSR_AUTO_REG_bit _A_CODEC_LSR_AUTO_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short LSR_CONFIG           : 3; // Bit 2-0
  };
} CODEC_LSR_AUTO_REG_type __attribute__((aligned(2)));

extern volatile CODEC_LSR_AUTO_REG_type _A_CODEC_LSR_AUTO_REG __attribute__((aligned(2)));

#define CODEC_LSR_AUTO_LSR_CONFIG           0x0007 // Bit 2-0

/****************************************************************************
* CLASSD_CTRL_REG
****************************************************************************/

#define CLASSD_CTRL_REG_adr 0xFF5C00
#define CLASSD_CTRL_REG _A_CLASSD_CTRL_REG.Value
#define CLASSD_CTRL_REG_bit _A_CLASSD_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CLASSD_PD            : 1; // Bit 0
    unsigned short CLASSD_PROT          : 1; // Bit 1
    unsigned short CLASSD_VOUT          : 2; // Bit 3-2
    unsigned short CLASSD_CLIP          : 3; // Bit 6-4
    unsigned short CLASSD_INT_BIT       : 1; // Bit 7
    unsigned short CLASSD_DITH_D        : 2; // Bit 9-8
    unsigned short CLASSD_DITH_A        : 2; // Bit 11-10
    unsigned short CLASSD_MODE          : 1; // Bit 12
    unsigned short CLASSD_MINT          : 1; // Bit 13
    unsigned short CLASSD_MOPEN         : 1; // Bit 14
    unsigned short CLASSD_POPEN         : 1; // Bit 15
  };
} CLASSD_CTRL_REG_type __attribute__((aligned(2)));

extern volatile CLASSD_CTRL_REG_type _A_CLASSD_CTRL_REG __attribute__((aligned(2)));

#define CLASSD_CTRL_CLASSD_PD            0x0001 // Bit 0
#define CLASSD_CTRL_CLASSD_PROT          0x0002 // Bit 1
#define CLASSD_CTRL_CLASSD_VOUT          0x000C // Bit 3-2
#define CLASSD_CTRL_CLASSD_CLIP          0x0070 // Bit 6-4
#define CLASSD_CTRL_CLASSD_INT_BIT       0x0080 // Bit 7
#define CLASSD_CTRL_CLASSD_DITH_D        0x0300 // Bit 9-8
#define CLASSD_CTRL_CLASSD_DITH_A        0x0C00 // Bit 11-10
#define CLASSD_CTRL_CLASSD_MODE          0x1000 // Bit 12
#define CLASSD_CTRL_CLASSD_MINT          0x2000 // Bit 13
#define CLASSD_CTRL_CLASSD_MOPEN         0x4000 // Bit 14
#define CLASSD_CTRL_CLASSD_POPEN         0x8000 // Bit 15

/****************************************************************************
* CLASSD_CLEAR_INT_REG
****************************************************************************/

#define CLASSD_CLEAR_INT_REG_adr 0xFF5C02
#define CLASSD_CLEAR_INT_REG _A_CLASSD_CLEAR_INT_REG

extern volatile unsigned short _A_CLASSD_CLEAR_INT_REG;

/****************************************************************************
* CLASSD_BUZZER_REG
****************************************************************************/

#define CLASSD_BUZZER_REG_adr 0xFF5C04
#define CLASSD_BUZZER_REG _A_CLASSD_BUZZER_REG.Value
#define CLASSD_BUZZER_REG_bit _A_CLASSD_BUZZER_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CLASSD_BUZ_GAIN      : 4; // Bit 3-0
    unsigned short CLASSD_BUZ_MODE      : 1; // Bit 4
  };
} CLASSD_BUZZER_REG_type __attribute__((aligned(2)));

extern volatile CLASSD_BUZZER_REG_type _A_CLASSD_BUZZER_REG __attribute__((aligned(2)));

#define CLASSD_BUZZER_CLASSD_BUZ_GAIN      0x000F // Bit 3-0
#define CLASSD_BUZZER_CLASSD_BUZ_MODE      0x0010 // Bit 4

/****************************************************************************
* CLASSD_TEST_REG
****************************************************************************/

#define CLASSD_TEST_REG_adr 0xFF5C06
#define CLASSD_TEST_REG _A_CLASSD_TEST_REG.Value
#define CLASSD_TEST_REG_bit _A_CLASSD_TEST_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CLASSD_SWITCH        : 1; // Bit 0
    unsigned short CLASSD_RST_D         : 1; // Bit 1
    unsigned short CLASSD_RST_A         : 1; // Bit 2
    unsigned short CLASSD_FORCE         : 1; // Bit 3
    unsigned short CLASSD_ANA_TEST      : 3; // Bit 6-4
  };
} CLASSD_TEST_REG_type __attribute__((aligned(2)));

extern volatile CLASSD_TEST_REG_type _A_CLASSD_TEST_REG __attribute__((aligned(2)));

#define CLASSD_TEST_CLASSD_SWITCH        0x0001 // Bit 0
#define CLASSD_TEST_CLASSD_RST_D         0x0002 // Bit 1
#define CLASSD_TEST_CLASSD_RST_A         0x0004 // Bit 2
#define CLASSD_TEST_CLASSD_FORCE         0x0008 // Bit 3
#define CLASSD_TEST_CLASSD_ANA_TEST      0x0070 // Bit 6-4

/****************************************************************************
* CLASSD_NR_REG
****************************************************************************/

#define CLASSD_NR_REG_adr 0xFF5C08
#define CLASSD_NR_REG _A_CLASSD_NR_REG.Value
#define CLASSD_NR_REG_bit _A_CLASSD_NR_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CLASSD_NR_ACTIVE     : 1; // Bit 0
    unsigned short CLASSD_NR_LVL        : 3; // Bit 3-1
    unsigned short CLASSD_NR_TON        : 4; // Bit 7-4
    unsigned short CLASSD_NR_HYST       : 2; // Bit 9-8
    unsigned short CLASSD_NR_ZERO       : 2; // Bit 11-10
    unsigned short CLASSD_NR_MODE       : 1; // Bit 12
  };
} CLASSD_NR_REG_type __attribute__((aligned(2)));

extern volatile CLASSD_NR_REG_type _A_CLASSD_NR_REG __attribute__((aligned(2)));

#define CLASSD_NR_CLASSD_NR_ACTIVE     0x0001 // Bit 0
#define CLASSD_NR_CLASSD_NR_LVL        0x000E // Bit 3-1
#define CLASSD_NR_CLASSD_NR_TON        0x00F0 // Bit 7-4
#define CLASSD_NR_CLASSD_NR_HYST       0x0300 // Bit 9-8
#define CLASSD_NR_CLASSD_NR_ZERO       0x0C00 // Bit 11-10
#define CLASSD_NR_CLASSD_NR_MODE       0x1000 // Bit 12

/****************************************************************************
* DIP_STACK_REG
****************************************************************************/

#define DIP_STACK_REG_adr 0xFF6000
#define DIP_STACK_REG _A_DIP_STACK_REG.Value
#define DIP_STACK_REG_bit _A_DIP_STACK_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short STACK_REG            : 8; // Bit 7-0
    unsigned short STACK_BANK           : 2; // Bit 9-8
  };
} DIP_STACK_REG_type __attribute__((aligned(2)));

extern volatile DIP_STACK_REG_type _A_DIP_STACK_REG __attribute__((aligned(2)));

#define DIP_STACK_STACK_REG            0x00FF // Bit 7-0
#define DIP_STACK_STACK_BANK           0x0300 // Bit 9-8

/****************************************************************************
* DIP_PC_REG
****************************************************************************/

#define DIP_PC_REG_adr 0xFF6002
#define DIP_PC_REG _A_DIP_PC_REG.Value
#define DIP_PC_REG_bit _A_DIP_PC_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DIP_PC               : 8; // Bit 7-0
    unsigned short DIP_BANK             : 2; // Bit 9-8
  };
} DIP_PC_REG_type __attribute__((aligned(2)));

extern volatile DIP_PC_REG_type _A_DIP_PC_REG __attribute__((aligned(2)));

#define DIP_PC_DIP_PC               0x00FF // Bit 7-0
#define DIP_PC_DIP_BANK             0x0300 // Bit 9-8

/****************************************************************************
* DIP_STATUS_REG
****************************************************************************/

#define DIP_STATUS_REG_adr 0xFF6004
#define DIP_STATUS_REG _A_DIP_STATUS_REG.Value
#define DIP_STATUS_REG_bit _A_DIP_STATUS_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DIP_INT_VEC          : 4; // Bit 3-0
    unsigned short PD1_INT              : 1; // Bit 4
    unsigned short DIP_BRK_INT          : 1; // Bit 5
    unsigned short PRESCALER            : 1; // Bit 6
    unsigned short URST                 : 1; // Bit 7
  };
} DIP_STATUS_REG_type __attribute__((aligned(2)));

extern volatile DIP_STATUS_REG_type _A_DIP_STATUS_REG __attribute__((aligned(2)));

#define DIP_STATUS_DIP_INT_VEC          0x000F // Bit 3-0
#define DIP_STATUS_PD1_INT              0x0010 // Bit 4
#define DIP_STATUS_DIP_BRK_INT          0x0020 // Bit 5
#define DIP_STATUS_PRESCALER            0x0040 // Bit 6
#define DIP_STATUS_URST                 0x0080 // Bit 7

/****************************************************************************
* DIP_CTRL_REG
****************************************************************************/

#define DIP_CTRL_REG_adr 0xFF6006
#define DIP_CTRL_REG _A_DIP_CTRL_REG.Value
#define DIP_CTRL_REG_bit _A_DIP_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DIP_INT_VEC          : 4; // Bit 3-0
    unsigned short PD1_INT              : 1; // Bit 4
    unsigned short DIP_BRK_INT          : 1; // Bit 5
    unsigned short PRESCALER            : 1; // Bit 6
    unsigned short URST                 : 1; // Bit 7
  };
} DIP_CTRL_REG_type __attribute__((aligned(2)));

extern volatile DIP_CTRL_REG_type _A_DIP_CTRL_REG __attribute__((aligned(2)));

#define DIP_CTRL_DIP_INT_VEC          0x000F // Bit 3-0
#define DIP_CTRL_PD1_INT              0x0010 // Bit 4
#define DIP_CTRL_DIP_BRK_INT          0x0020 // Bit 5
#define DIP_CTRL_PRESCALER            0x0040 // Bit 6
#define DIP_CTRL_URST                 0x0080 // Bit 7

/****************************************************************************
* DIP_STATUS1_REG
****************************************************************************/

#define DIP_STATUS1_REG_adr 0xFF6008
#define DIP_STATUS1_REG _A_DIP_STATUS1_REG.Value
#define DIP_STATUS1_REG_bit _A_DIP_STATUS1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DIP_VNMI_VEC         : 4; // Bit 3-0
  };
} DIP_STATUS1_REG_type __attribute__((aligned(2)));

extern volatile DIP_STATUS1_REG_type _A_DIP_STATUS1_REG __attribute__((aligned(2)));

#define DIP_STATUS1_DIP_VNMI_VEC         0x000F // Bit 3-0

/****************************************************************************
* DIP_CTRL1_REG
****************************************************************************/

#define DIP_CTRL1_REG_adr 0xFF600A
#define DIP_CTRL1_REG _A_DIP_CTRL1_REG.Value
#define DIP_CTRL1_REG_bit _A_DIP_CTRL1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DIP_VNMI_VEC         : 4; // Bit 3-0
  };
} DIP_CTRL1_REG_type __attribute__((aligned(2)));

extern volatile DIP_CTRL1_REG_type _A_DIP_CTRL1_REG __attribute__((aligned(2)));

#define DIP_CTRL1_DIP_VNMI_VEC         0x000F // Bit 3-0

/****************************************************************************
* DIP_SLOT_NUMBER_REG
****************************************************************************/

#define DIP_SLOT_NUMBER_REG_adr 0xFF600C
#define DIP_SLOT_NUMBER_REG _A_DIP_SLOT_NUMBER_REG.Value
#define DIP_SLOT_NUMBER_REG_bit _A_DIP_SLOT_NUMBER_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SLOT_CNTER           : 5; // Bit 4-0
  };
} DIP_SLOT_NUMBER_REG_type __attribute__((aligned(2)));

extern volatile DIP_SLOT_NUMBER_REG_type _A_DIP_SLOT_NUMBER_REG __attribute__((aligned(2)));

#define DIP_SLOT_NUMBER_SLOT_CNTER           0x001F // Bit 4-0

/****************************************************************************
* DIP_CTRL2_REG
****************************************************************************/

#define DIP_CTRL2_REG_adr 0xFF600E
#define DIP_CTRL2_REG _A_DIP_CTRL2_REG.Value
#define DIP_CTRL2_REG_bit _A_DIP_CTRL2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DBUF                 : 1; // Bit 0
    unsigned short PRE_ACT              : 1; // Bit 1
    unsigned short BRK_PRE_OVR          : 1; // Bit 2
    unsigned short                      : 1; // Bit 3
    unsigned short PD1_INT              : 1; // Bit 4
    unsigned short DIP_BRK              : 1; // Bit 5
    unsigned short                      : 1; // Bit 6
    unsigned short EN_8DIV9             : 1; // Bit 7
    unsigned short SLOTCNT_RES          : 1; // Bit 8
    unsigned short FR_BMC               : 1; // Bit 9
    unsigned short MFR_DSC              : 1; // Bit 10
    unsigned short ZERO_DSC             : 1; // Bit 11
  };
} DIP_CTRL2_REG_type __attribute__((aligned(2)));

extern volatile DIP_CTRL2_REG_type _A_DIP_CTRL2_REG __attribute__((aligned(2)));

#define DIP_CTRL2_DBUF                 0x0001 // Bit 0
#define DIP_CTRL2_PRE_ACT              0x0002 // Bit 1
#define DIP_CTRL2_BRK_PRE_OVR          0x0004 // Bit 2
#define DIP_CTRL2_PD1_INT              0x0010 // Bit 4
#define DIP_CTRL2_DIP_BRK              0x0020 // Bit 5
#define DIP_CTRL2_EN_8DIV9             0x0080 // Bit 7
#define DIP_CTRL2_SLOTCNT_RES          0x0100 // Bit 8
#define DIP_CTRL2_FR_BMC               0x0200 // Bit 9
#define DIP_CTRL2_MFR_DSC              0x0400 // Bit 10
#define DIP_CTRL2_ZERO_DSC             0x0800 // Bit 11

/****************************************************************************
* DIP_MOD_SEL_REG
****************************************************************************/

#define DIP_MOD_SEL_REG_adr 0xFF6012
#define DIP_MOD_SEL_REG _A_DIP_MOD_SEL_REG.Value
#define DIP_MOD_SEL_REG_bit _A_DIP_MOD_SEL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short ARMOD0               : 1; // Bit 0
    unsigned short ARMOD1               : 1; // Bit 1
    unsigned short ARMOD2               : 1; // Bit 2
    unsigned short ARMOD3               : 1; // Bit 3
    unsigned short AWMOD0               : 1; // Bit 4
    unsigned short AWMOD1               : 1; // Bit 5
    unsigned short AWMOD2               : 1; // Bit 6
    unsigned short AWMOD3               : 1; // Bit 7
  };
} DIP_MOD_SEL_REG_type __attribute__((aligned(2)));

extern volatile DIP_MOD_SEL_REG_type _A_DIP_MOD_SEL_REG __attribute__((aligned(2)));

#define DIP_MOD_SEL_ARMOD0               0x0001 // Bit 0
#define DIP_MOD_SEL_ARMOD1               0x0002 // Bit 1
#define DIP_MOD_SEL_ARMOD2               0x0004 // Bit 2
#define DIP_MOD_SEL_ARMOD3               0x0008 // Bit 3
#define DIP_MOD_SEL_AWMOD0               0x0010 // Bit 4
#define DIP_MOD_SEL_AWMOD1               0x0020 // Bit 5
#define DIP_MOD_SEL_AWMOD2               0x0040 // Bit 6
#define DIP_MOD_SEL_AWMOD3               0x0080 // Bit 7

/****************************************************************************
* DIP_MOD_VAL_REG
****************************************************************************/

#define DIP_MOD_VAL_REG_adr 0xFF6014
#define DIP_MOD_VAL_REG _A_DIP_MOD_VAL_REG.Value
#define DIP_MOD_VAL_REG_bit _A_DIP_MOD_VAL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short MODULO0              : 8; // Bit 7-0
    unsigned short MODULO1              : 8; // Bit 15-8
  };
} DIP_MOD_VAL_REG_type __attribute__((aligned(2)));

extern volatile DIP_MOD_VAL_REG_type _A_DIP_MOD_VAL_REG __attribute__((aligned(2)));

#define DIP_MOD_VAL_MODULO0              0x00FF // Bit 7-0
#define DIP_MOD_VAL_MODULO1              0xFF00 // Bit 15-8

/****************************************************************************
* DIP_DC01_REG
****************************************************************************/

#define DIP_DC01_REG_adr 0xFF6016
#define DIP_DC01_REG _A_DIP_DC01_REG.Value
#define DIP_DC01_REG_bit _A_DIP_DC01_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short FRAME                : 4; // Bit 3-0
    unsigned short MFRAME_LOW           : 12; // Bit 15-4
  };
} DIP_DC01_REG_type __attribute__((aligned(2)));

extern volatile DIP_DC01_REG_type _A_DIP_DC01_REG __attribute__((aligned(2)));

#define DIP_DC01_FRAME                0x000F // Bit 3-0
#define DIP_DC01_MFRAME_LOW           0xFFF0 // Bit 15-4

/****************************************************************************
* DIP_DC23_REG
****************************************************************************/

#define DIP_DC23_REG_adr 0xFF6018
#define DIP_DC23_REG _A_DIP_DC23_REG.Value
#define DIP_DC23_REG_bit _A_DIP_DC23_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short MFRAME_HIGH          : 12; // Bit 11-0
  };
} DIP_DC23_REG_type __attribute__((aligned(2)));

extern volatile DIP_DC23_REG_type _A_DIP_DC23_REG __attribute__((aligned(2)));

#define DIP_DC23_MFRAME_HIGH          0x0FFF // Bit 11-0

/****************************************************************************
* DIP_DC34_REG
****************************************************************************/

#define DIP_DC34_REG_adr 0xFF601A
#define DIP_DC34_REG _A_DIP_DC34_REG

extern volatile unsigned short _A_DIP_DC34_REG;

/****************************************************************************
* BMC_CTRL_REG
****************************************************************************/

#define BMC_CTRL_REG_adr 0xFF6400
#define BMC_CTRL_REG _A_BMC_CTRL_REG.Value
#define BMC_CTRL_REG_bit _A_BMC_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 4; // Bit 3-0
    unsigned short                      : 1; // Bit 4
    unsigned short                      : 1; // Bit 5
    unsigned short                      : 1; // Bit 6
    unsigned short                      : 1; // Bit 7
    unsigned short SIO_PD               : 1; // Bit 8
    unsigned short                      : 4; // Bit 12-9
    unsigned short BCNT_INH             : 1; // Bit 13
  };
} BMC_CTRL_REG_type __attribute__((aligned(2)));

extern volatile BMC_CTRL_REG_type _A_BMC_CTRL_REG __attribute__((aligned(2)));

#define BMC_CTRL_SIO_PD               0x0100 // Bit 8
#define BMC_CTRL_BCNT_INH             0x2000 // Bit 13

/****************************************************************************
* BMC_CTRL2_REG
****************************************************************************/

#define BMC_CTRL2_REG_adr 0xFF6402
#define BMC_CTRL2_REG _A_BMC_CTRL2_REG.Value
#define BMC_CTRL2_REG_bit _A_BMC_CTRL2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 3; // Bit 2-0
    unsigned short RCV_CTL              : 5; // Bit 7-3
    unsigned short RCK_SEL              : 1; // Bit 8
    unsigned short BF_CNT_HLD           : 1; // Bit 9
  };
} BMC_CTRL2_REG_type __attribute__((aligned(2)));

extern volatile BMC_CTRL2_REG_type _A_BMC_CTRL2_REG __attribute__((aligned(2)));

#define BMC_CTRL2_RCV_CTL              0x00F8 // Bit 7-3
#define BMC_CTRL2_RCK_SEL              0x0100 // Bit 8
#define BMC_CTRL2_BF_CNT_HLD           0x0200 // Bit 9

/****************************************************************************
* BMC_TX_SFIELDL_REG
****************************************************************************/

#define BMC_TX_SFIELDL_REG_adr 0xFF6404
#define BMC_TX_SFIELDL_REG _A_BMC_TX_SFIELDL_REG

extern volatile unsigned short _A_BMC_TX_SFIELDL_REG;

/****************************************************************************
* BMC_TX_SFIELDH_REG
****************************************************************************/

#define BMC_TX_SFIELDH_REG_adr 0xFF6406
#define BMC_TX_SFIELDH_REG _A_BMC_TX_SFIELDH_REG

extern volatile unsigned short _A_BMC_TX_SFIELDH_REG;

/****************************************************************************
* BMC_RX_SFIELDL_REG
****************************************************************************/

#define BMC_RX_SFIELDL_REG_adr 0xFF6408
#define BMC_RX_SFIELDL_REG _A_BMC_RX_SFIELDL_REG

extern volatile unsigned short _A_BMC_RX_SFIELDL_REG;

/****************************************************************************
* BMC_RX_SFIELDH_REG
****************************************************************************/

#define BMC_RX_SFIELDH_REG_adr 0xFF640A
#define BMC_RX_SFIELDH_REG _A_BMC_RX_SFIELDH_REG

extern volatile unsigned short _A_BMC_RX_SFIELDH_REG;

/****************************************************************************
* RF_BURST_MODE_CTRL0_REG
****************************************************************************/

#define RF_BURST_MODE_CTRL0_REG_adr 0xFF7000
#define RF_BURST_MODE_CTRL0_REG _A_RF_BURST_MODE_CTRL0_REG.Value
#define RF_BURST_MODE_CTRL0_REG_bit _A_RF_BURST_MODE_CTRL0_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CN                   : 7; // Bit 6-0
    unsigned short RFCAL                : 6; // Bit 12-7
    unsigned short RSSI_PA_MODE         : 1; // Bit 13
    unsigned short FAD                  : 2; // Bit 15-14
  };
} RF_BURST_MODE_CTRL0_REG_type __attribute__((aligned(2)));

extern volatile RF_BURST_MODE_CTRL0_REG_type _A_RF_BURST_MODE_CTRL0_REG __attribute__((aligned(2)));

#define RF_BURST_MODE_CTRL0_CN                   0x007F // Bit 6-0
#define RF_BURST_MODE_CTRL0_RFCAL                0x1F80 // Bit 12-7
#define RF_BURST_MODE_CTRL0_RSSI_PA_MODE         0x2000 // Bit 13
#define RF_BURST_MODE_CTRL0_FAD                  0xC000 // Bit 15-14

/****************************************************************************
* RF_BURST_MODE_CTRL1_REG
****************************************************************************/

#define RF_BURST_MODE_CTRL1_REG_adr 0xFF7002
#define RF_BURST_MODE_CTRL1_REG _A_RF_BURST_MODE_CTRL1_REG.Value
#define RF_BURST_MODE_CTRL1_REG_bit _A_RF_BURST_MODE_CTRL1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CN                   : 7; // Bit 6-0
    unsigned short RFCAL                : 6; // Bit 12-7
    unsigned short RSSI_PA_MODE         : 1; // Bit 13
    unsigned short FAD                  : 2; // Bit 15-14
  };
} RF_BURST_MODE_CTRL1_REG_type __attribute__((aligned(2)));

extern volatile RF_BURST_MODE_CTRL1_REG_type _A_RF_BURST_MODE_CTRL1_REG __attribute__((aligned(2)));

#define RF_BURST_MODE_CTRL1_CN                   0x007F // Bit 6-0
#define RF_BURST_MODE_CTRL1_RFCAL                0x1F80 // Bit 12-7
#define RF_BURST_MODE_CTRL1_RSSI_PA_MODE         0x2000 // Bit 13
#define RF_BURST_MODE_CTRL1_FAD                  0xC000 // Bit 15-14

/****************************************************************************
* RF_BURST_MODE_CTRL2_REG
****************************************************************************/

#define RF_BURST_MODE_CTRL2_REG_adr 0xFF7004
#define RF_BURST_MODE_CTRL2_REG _A_RF_BURST_MODE_CTRL2_REG.Value
#define RF_BURST_MODE_CTRL2_REG_bit _A_RF_BURST_MODE_CTRL2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CN                   : 7; // Bit 6-0
    unsigned short RFCAL                : 6; // Bit 12-7
    unsigned short RSSI_PA_MODE         : 1; // Bit 13
    unsigned short FAD                  : 2; // Bit 15-14
  };
} RF_BURST_MODE_CTRL2_REG_type __attribute__((aligned(2)));

extern volatile RF_BURST_MODE_CTRL2_REG_type _A_RF_BURST_MODE_CTRL2_REG __attribute__((aligned(2)));

#define RF_BURST_MODE_CTRL2_CN                   0x007F // Bit 6-0
#define RF_BURST_MODE_CTRL2_RFCAL                0x1F80 // Bit 12-7
#define RF_BURST_MODE_CTRL2_RSSI_PA_MODE         0x2000 // Bit 13
#define RF_BURST_MODE_CTRL2_FAD                  0xC000 // Bit 15-14

/****************************************************************************
* RF_BURST_MODE_CTRL3_REG
****************************************************************************/

#define RF_BURST_MODE_CTRL3_REG_adr 0xFF7006
#define RF_BURST_MODE_CTRL3_REG _A_RF_BURST_MODE_CTRL3_REG.Value
#define RF_BURST_MODE_CTRL3_REG_bit _A_RF_BURST_MODE_CTRL3_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CN                   : 7; // Bit 6-0
    unsigned short RFCAL                : 6; // Bit 12-7
    unsigned short RSSI_PA_MODE         : 1; // Bit 13
    unsigned short FAD                  : 2; // Bit 15-14
  };
} RF_BURST_MODE_CTRL3_REG_type __attribute__((aligned(2)));

extern volatile RF_BURST_MODE_CTRL3_REG_type _A_RF_BURST_MODE_CTRL3_REG __attribute__((aligned(2)));

#define RF_BURST_MODE_CTRL3_CN                   0x007F // Bit 6-0
#define RF_BURST_MODE_CTRL3_RFCAL                0x1F80 // Bit 12-7
#define RF_BURST_MODE_CTRL3_RSSI_PA_MODE         0x2000 // Bit 13
#define RF_BURST_MODE_CTRL3_FAD                  0xC000 // Bit 15-14

/****************************************************************************
* RF_ALW_EN_REG
****************************************************************************/

#define RF_ALW_EN_REG_adr 0xFF7008
#define RF_ALW_EN_REG _A_RF_ALW_EN_REG.Value
#define RF_ALW_EN_REG_bit _A_RF_ALW_EN_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PA_FINAL_STAGE_ALW_EN  : 1; // Bit 0
    unsigned short PA_DRIVER_STAGE_ALW_EN  : 1; // Bit 1
    unsigned short PORT2_ALW_EN         : 1; // Bit 2
    unsigned short PORT1_ALW_EN         : 1; // Bit 3
    unsigned short PLLCLOSED_ALW_EN     : 1; // Bit 4
    unsigned short SYNTH_ALW_EN         : 1; // Bit 5
    unsigned short BIAS_ALW_EN          : 1; // Bit 6
    unsigned short RSSIPH_ALW_EN        : 1; // Bit 7
    unsigned short DEM_ALW_EN           : 1; // Bit 8
    unsigned short ADC_ALW_EN           : 1; // Bit 9
    unsigned short IF_ALW_EN            : 1; // Bit 10
    unsigned short LNAMIX_ALW_EN        : 1; // Bit 11
    unsigned short PA_ALW_EN            : 1; // Bit 12
  };
} RF_ALW_EN_REG_type __attribute__((aligned(2)));

extern volatile RF_ALW_EN_REG_type _A_RF_ALW_EN_REG __attribute__((aligned(2)));

#define RF_ALW_EN_PA_FINAL_STAGE_ALW_EN  0x0001 // Bit 0
#define RF_ALW_EN_PA_DRIVER_STAGE_ALW_EN  0x0002 // Bit 1
#define RF_ALW_EN_PORT2_ALW_EN         0x0004 // Bit 2
#define RF_ALW_EN_PORT1_ALW_EN         0x0008 // Bit 3
#define RF_ALW_EN_PLLCLOSED_ALW_EN     0x0010 // Bit 4
#define RF_ALW_EN_SYNTH_ALW_EN         0x0020 // Bit 5
#define RF_ALW_EN_BIAS_ALW_EN          0x0040 // Bit 6
#define RF_ALW_EN_RSSIPH_ALW_EN        0x0080 // Bit 7
#define RF_ALW_EN_DEM_ALW_EN           0x0100 // Bit 8
#define RF_ALW_EN_ADC_ALW_EN           0x0200 // Bit 9
#define RF_ALW_EN_IF_ALW_EN            0x0400 // Bit 10
#define RF_ALW_EN_LNAMIX_ALW_EN        0x0800 // Bit 11
#define RF_ALW_EN_PA_ALW_EN            0x1000 // Bit 12

/****************************************************************************
* RF_PORT_RSSI_SI_REG
****************************************************************************/

#define RF_PORT_RSSI_SI_REG_adr 0xFF700A
#define RF_PORT_RSSI_SI_REG _A_RF_PORT_RSSI_SI_REG.Value
#define RF_PORT_RSSI_SI_REG_bit _A_RF_PORT_RSSI_SI_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SO_PORT_VAL          : 8; // Bit 7-0
    unsigned short EO_RSSI_VAL          : 8; // Bit 15-8
  };
} RF_PORT_RSSI_SI_REG_type __attribute__((aligned(2)));

extern volatile RF_PORT_RSSI_SI_REG_type _A_RF_PORT_RSSI_SI_REG __attribute__((aligned(2)));

#define RF_PORT_RSSI_SI_SO_PORT_VAL          0x00FF // Bit 7-0
#define RF_PORT_RSSI_SI_EO_RSSI_VAL          0xFF00 // Bit 15-8

/****************************************************************************
* RF_TX_SI_REG
****************************************************************************/

#define RF_TX_SI_REG_adr 0xFF700C
#define RF_TX_SI_REG _A_RF_TX_SI_REG.Value
#define RF_TX_SI_REG_bit _A_RF_TX_SI_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SO_TX_VAL            : 8; // Bit 7-0
    unsigned short EO_TX_VAL            : 8; // Bit 15-8
  };
} RF_TX_SI_REG_type __attribute__((aligned(2)));

extern volatile RF_TX_SI_REG_type _A_RF_TX_SI_REG __attribute__((aligned(2)));

#define RF_TX_SI_SO_TX_VAL            0x00FF // Bit 7-0
#define RF_TX_SI_EO_TX_VAL            0xFF00 // Bit 15-8

/****************************************************************************
* RF_RX_SI_REG
****************************************************************************/

#define RF_RX_SI_REG_adr 0xFF700E
#define RF_RX_SI_REG _A_RF_RX_SI_REG.Value
#define RF_RX_SI_REG_bit _A_RF_RX_SI_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SO_RX_VAL            : 8; // Bit 7-0
    unsigned short EO_RX_VAL            : 8; // Bit 15-8
  };
} RF_RX_SI_REG_type __attribute__((aligned(2)));

extern volatile RF_RX_SI_REG_type _A_RF_RX_SI_REG __attribute__((aligned(2)));

#define RF_RX_SI_SO_RX_VAL            0x00FF // Bit 7-0
#define RF_RX_SI_EO_RX_VAL            0xFF00 // Bit 15-8

/****************************************************************************
* RF_PORT1_DCF_REG
****************************************************************************/

#define RF_PORT1_DCF_REG_adr 0xFF7010
#define RF_PORT1_DCF_REG _A_RF_PORT1_DCF_REG.Value
#define RF_PORT1_DCF_REG_bit _A_RF_PORT1_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short EN_BY_TX             : 1; // Bit 12
    unsigned short EN_BY_RX             : 1; // Bit 13
    unsigned short SSI                  : 1; // Bit 14
  };
} RF_PORT1_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_PORT1_DCF_REG_type _A_RF_PORT1_DCF_REG __attribute__((aligned(2)));

#define RF_PORT1_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_PORT1_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_PORT1_DCF_EN_BY_TX             0x1000 // Bit 12
#define RF_PORT1_DCF_EN_BY_RX             0x2000 // Bit 13
#define RF_PORT1_DCF_SSI                  0x4000 // Bit 14

/****************************************************************************
* RF_PORT2_DCF_REG
****************************************************************************/

#define RF_PORT2_DCF_REG_adr 0xFF7012
#define RF_PORT2_DCF_REG _A_RF_PORT2_DCF_REG.Value
#define RF_PORT2_DCF_REG_bit _A_RF_PORT2_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short EN_BY_TX             : 1; // Bit 12
    unsigned short EN_BY_RX             : 1; // Bit 13
    unsigned short SSI                  : 1; // Bit 14
  };
} RF_PORT2_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_PORT2_DCF_REG_type _A_RF_PORT2_DCF_REG __attribute__((aligned(2)));

#define RF_PORT2_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_PORT2_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_PORT2_DCF_EN_BY_TX             0x1000 // Bit 12
#define RF_PORT2_DCF_EN_BY_RX             0x2000 // Bit 13
#define RF_PORT2_DCF_SSI                  0x4000 // Bit 14

/****************************************************************************
* RF_PA_DRIVER_STAGE_DCF_REG
****************************************************************************/

#define RF_PA_DRIVER_STAGE_DCF_REG_adr 0xFF7014
#define RF_PA_DRIVER_STAGE_DCF_REG _A_RF_PA_DRIVER_STAGE_DCF_REG.Value
#define RF_PA_DRIVER_STAGE_DCF_REG_bit _A_RF_PA_DRIVER_STAGE_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short EN_BY_TX             : 1; // Bit 12
    unsigned short EN_BY_RX             : 1; // Bit 13
    unsigned short SSI                  : 1; // Bit 14
  };
} RF_PA_DRIVER_STAGE_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_PA_DRIVER_STAGE_DCF_REG_type _A_RF_PA_DRIVER_STAGE_DCF_REG __attribute__((aligned(2)));

#define RF_PA_DRIVER_STAGE_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_PA_DRIVER_STAGE_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_PA_DRIVER_STAGE_DCF_EN_BY_TX             0x1000 // Bit 12
#define RF_PA_DRIVER_STAGE_DCF_EN_BY_RX             0x2000 // Bit 13
#define RF_PA_DRIVER_STAGE_DCF_SSI                  0x4000 // Bit 14

/****************************************************************************
* RF_PA_FINAL_STAGE_DCF_REG
****************************************************************************/

#define RF_PA_FINAL_STAGE_DCF_REG_adr 0xFF7016
#define RF_PA_FINAL_STAGE_DCF_REG _A_RF_PA_FINAL_STAGE_DCF_REG.Value
#define RF_PA_FINAL_STAGE_DCF_REG_bit _A_RF_PA_FINAL_STAGE_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short EN_BY_TX             : 1; // Bit 12
    unsigned short EN_BY_RX             : 1; // Bit 13
    unsigned short SSI                  : 1; // Bit 14
  };
} RF_PA_FINAL_STAGE_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_PA_FINAL_STAGE_DCF_REG_type _A_RF_PA_FINAL_STAGE_DCF_REG __attribute__((aligned(2)));

#define RF_PA_FINAL_STAGE_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_PA_FINAL_STAGE_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_PA_FINAL_STAGE_DCF_EN_BY_TX             0x1000 // Bit 12
#define RF_PA_FINAL_STAGE_DCF_EN_BY_RX             0x2000 // Bit 13
#define RF_PA_FINAL_STAGE_DCF_SSI                  0x4000 // Bit 14

/****************************************************************************
* RF_PLLCLOSED_DCF_REG
****************************************************************************/

#define RF_PLLCLOSED_DCF_REG_adr 0xFF7018
#define RF_PLLCLOSED_DCF_REG _A_RF_PLLCLOSED_DCF_REG.Value
#define RF_PLLCLOSED_DCF_REG_bit _A_RF_PLLCLOSED_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short DIS                  : 1; // Bit 12
    unsigned short                      : 1; // Bit 13
    unsigned short SSI                  : 1; // Bit 14
  };
} RF_PLLCLOSED_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_PLLCLOSED_DCF_REG_type _A_RF_PLLCLOSED_DCF_REG __attribute__((aligned(2)));

#define RF_PLLCLOSED_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_PLLCLOSED_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_PLLCLOSED_DCF_DIS                  0x1000 // Bit 12
#define RF_PLLCLOSED_DCF_SSI                  0x4000 // Bit 14

/****************************************************************************
* RF_SYNTH_DCF_REG
****************************************************************************/

#define RF_SYNTH_DCF_REG_adr 0xFF701A
#define RF_SYNTH_DCF_REG _A_RF_SYNTH_DCF_REG.Value
#define RF_SYNTH_DCF_REG_bit _A_RF_SYNTH_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short DIS                  : 1; // Bit 12
  };
} RF_SYNTH_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_SYNTH_DCF_REG_type _A_RF_SYNTH_DCF_REG __attribute__((aligned(2)));

#define RF_SYNTH_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_SYNTH_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_SYNTH_DCF_DIS                  0x1000 // Bit 12

/****************************************************************************
* RF_BIAS_DCF_REG
****************************************************************************/

#define RF_BIAS_DCF_REG_adr 0xFF701C
#define RF_BIAS_DCF_REG _A_RF_BIAS_DCF_REG.Value
#define RF_BIAS_DCF_REG_bit _A_RF_BIAS_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short DIS                  : 1; // Bit 12
  };
} RF_BIAS_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_BIAS_DCF_REG_type _A_RF_BIAS_DCF_REG __attribute__((aligned(2)));

#define RF_BIAS_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_BIAS_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_BIAS_DCF_DIS                  0x1000 // Bit 12

/****************************************************************************
* RF_RSSIPH_DCF_REG
****************************************************************************/

#define RF_RSSIPH_DCF_REG_adr 0xFF701E
#define RF_RSSIPH_DCF_REG _A_RF_RSSIPH_DCF_REG.Value
#define RF_RSSIPH_DCF_REG_bit _A_RF_RSSIPH_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short DIS                  : 1; // Bit 12
  };
} RF_RSSIPH_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_RSSIPH_DCF_REG_type _A_RF_RSSIPH_DCF_REG __attribute__((aligned(2)));

#define RF_RSSIPH_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_RSSIPH_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_RSSIPH_DCF_DIS                  0x1000 // Bit 12

/****************************************************************************
* RF_DEM_DCF_REG
****************************************************************************/

#define RF_DEM_DCF_REG_adr 0xFF7020
#define RF_DEM_DCF_REG _A_RF_DEM_DCF_REG.Value
#define RF_DEM_DCF_REG_bit _A_RF_DEM_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short DIS                  : 1; // Bit 12
    unsigned short                      : 1; // Bit 13
    unsigned short SSI                  : 1; // Bit 14
  };
} RF_DEM_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_DEM_DCF_REG_type _A_RF_DEM_DCF_REG __attribute__((aligned(2)));

#define RF_DEM_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_DEM_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_DEM_DCF_DIS                  0x1000 // Bit 12
#define RF_DEM_DCF_SSI                  0x4000 // Bit 14

/****************************************************************************
* RF_ADC_DCF_REG
****************************************************************************/

#define RF_ADC_DCF_REG_adr 0xFF7022
#define RF_ADC_DCF_REG _A_RF_ADC_DCF_REG.Value
#define RF_ADC_DCF_REG_bit _A_RF_ADC_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short DIS                  : 1; // Bit 12
    unsigned short                      : 1; // Bit 13
    unsigned short SSI                  : 1; // Bit 14
  };
} RF_ADC_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_ADC_DCF_REG_type _A_RF_ADC_DCF_REG __attribute__((aligned(2)));

#define RF_ADC_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_ADC_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_ADC_DCF_DIS                  0x1000 // Bit 12
#define RF_ADC_DCF_SSI                  0x4000 // Bit 14

/****************************************************************************
* RF_IF_DCF_REG
****************************************************************************/

#define RF_IF_DCF_REG_adr 0xFF7024
#define RF_IF_DCF_REG _A_RF_IF_DCF_REG.Value
#define RF_IF_DCF_REG_bit _A_RF_IF_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short DIS                  : 1; // Bit 12
    unsigned short                      : 1; // Bit 13
    unsigned short SSI                  : 1; // Bit 14
  };
} RF_IF_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_IF_DCF_REG_type _A_RF_IF_DCF_REG __attribute__((aligned(2)));

#define RF_IF_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_IF_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_IF_DCF_DIS                  0x1000 // Bit 12
#define RF_IF_DCF_SSI                  0x4000 // Bit 14

/****************************************************************************
* RF_LNAMIX_DCF_REG
****************************************************************************/

#define RF_LNAMIX_DCF_REG_adr 0xFF7026
#define RF_LNAMIX_DCF_REG _A_RF_LNAMIX_DCF_REG.Value
#define RF_LNAMIX_DCF_REG_bit _A_RF_LNAMIX_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short DIS                  : 1; // Bit 12
    unsigned short                      : 1; // Bit 13
    unsigned short SSI                  : 1; // Bit 14
  };
} RF_LNAMIX_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_LNAMIX_DCF_REG_type _A_RF_LNAMIX_DCF_REG __attribute__((aligned(2)));

#define RF_LNAMIX_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_LNAMIX_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_LNAMIX_DCF_DIS                  0x1000 // Bit 12
#define RF_LNAMIX_DCF_SSI                  0x4000 // Bit 14

/****************************************************************************
* RF_PA_DCF_REG
****************************************************************************/

#define RF_PA_DCF_REG_adr 0xFF7028
#define RF_PA_DCF_REG _A_RF_PA_DCF_REG.Value
#define RF_PA_DCF_REG_bit _A_RF_PA_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short SET_OFFSET           : 6; // Bit 5-0
    unsigned short RESET_OFFSET         : 6; // Bit 11-6
    unsigned short DIS                  : 1; // Bit 12
    unsigned short RX_SENSITIVE         : 1; // Bit 13
    unsigned short PADR_SSI             : 2; // Bit 15-14
  };
} RF_PA_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_PA_DCF_REG_type _A_RF_PA_DCF_REG __attribute__((aligned(2)));

#define RF_PA_DCF_SET_OFFSET           0x003F // Bit 5-0
#define RF_PA_DCF_RESET_OFFSET         0x0FC0 // Bit 11-6
#define RF_PA_DCF_DIS                  0x1000 // Bit 12
#define RF_PA_DCF_RX_SENSITIVE         0x2000 // Bit 13
#define RF_PA_DCF_PADR_SSI             0xC000 // Bit 15-14

/****************************************************************************
* RF_FAD_WINDOW_DCF_REG
****************************************************************************/

#define RF_FAD_WINDOW_DCF_REG_adr 0xFF702A
#define RF_FAD_WINDOW_DCF_REG _A_RF_FAD_WINDOW_DCF_REG.Value
#define RF_FAD_WINDOW_DCF_REG_bit _A_RF_FAD_WINDOW_DCF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short FAD_SWAP             : 6; // Bit 5-0
    unsigned short FAD_DECIDE           : 6; // Bit 11-6
  };
} RF_FAD_WINDOW_DCF_REG_type __attribute__((aligned(2)));

extern volatile RF_FAD_WINDOW_DCF_REG_type _A_RF_FAD_WINDOW_DCF_REG __attribute__((aligned(2)));

#define RF_FAD_WINDOW_DCF_FAD_SWAP             0x003F // Bit 5-0
#define RF_FAD_WINDOW_DCF_FAD_DECIDE           0x0FC0 // Bit 11-6

/****************************************************************************
* RF_RFCAL_CTRL_REG
****************************************************************************/

#define RF_RFCAL_CTRL_REG_adr 0xFF7040
#define RF_RFCAL_CTRL_REG _A_RF_RFCAL_CTRL_REG.Value
#define RF_RFCAL_CTRL_REG_bit _A_RF_RFCAL_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short RFCAL_STEPS          : 3; // Bit 2-0
    unsigned short RFCAL_MODE           : 2; // Bit 4-3
    unsigned short RFCAL_PERIOD         : 2; // Bit 6-5
  };
} RF_RFCAL_CTRL_REG_type __attribute__((aligned(2)));

extern volatile RF_RFCAL_CTRL_REG_type _A_RF_RFCAL_CTRL_REG __attribute__((aligned(2)));

#define RF_RFCAL_CTRL_RFCAL_STEPS          0x0007 // Bit 2-0
#define RF_RFCAL_CTRL_RFCAL_MODE           0x0018 // Bit 4-3
#define RF_RFCAL_CTRL_RFCAL_PERIOD         0x0060 // Bit 6-5

/****************************************************************************
* RF_DEM_CTRL_REG
****************************************************************************/

#define RF_DEM_CTRL_REG_adr 0xFF7044
#define RF_DEM_CTRL_REG _A_RF_DEM_CTRL_REG.Value
#define RF_DEM_CTRL_REG_bit _A_RF_DEM_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DEM_INVERT           : 1; // Bit 0
    unsigned short SLICE_EN             : 1; // Bit 1
    unsigned short                      : 5; // Bit 6-2
    unsigned short SLICE_EARLY          : 1; // Bit 7
    unsigned short SLICE_VAL            : 8; // Bit 15-8
  };
} RF_DEM_CTRL_REG_type __attribute__((aligned(2)));

extern volatile RF_DEM_CTRL_REG_type _A_RF_DEM_CTRL_REG __attribute__((aligned(2)));

#define RF_DEM_CTRL_DEM_INVERT           0x0001 // Bit 0
#define RF_DEM_CTRL_SLICE_EN             0x0002 // Bit 1
#define RF_DEM_CTRL_SLICE_EARLY          0x0080 // Bit 7
#define RF_DEM_CTRL_SLICE_VAL            0xFF00 // Bit 15-8

/****************************************************************************
* RF_PREAMBLE_REG
****************************************************************************/

#define RF_PREAMBLE_REG_adr 0xFF7046
#define RF_PREAMBLE_REG _A_RF_PREAMBLE_REG.Value
#define RF_PREAMBLE_REG_bit _A_RF_PREAMBLE_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PREAMBLE_DEL         : 6; // Bit 5-0
    unsigned short AFC_VAL              : 2; // Bit 7-6
    unsigned short AFC_EN               : 1; // Bit 8
    unsigned short AFC_SETTLE_DEL       : 2; // Bit 10-9
    unsigned short PREAMBLE_SYM         : 2; // Bit 12-11
    unsigned short GATE_DATA            : 1; // Bit 13
    unsigned short HALF_BIT_RATE        : 1; // Bit 14
    unsigned short SYNC_RX_DATA         : 1; // Bit 15
  };
} RF_PREAMBLE_REG_type __attribute__((aligned(2)));

extern volatile RF_PREAMBLE_REG_type _A_RF_PREAMBLE_REG __attribute__((aligned(2)));

#define RF_PREAMBLE_PREAMBLE_DEL         0x003F // Bit 5-0
#define RF_PREAMBLE_AFC_VAL              0x00C0 // Bit 7-6
#define RF_PREAMBLE_AFC_EN               0x0100 // Bit 8
#define RF_PREAMBLE_AFC_SETTLE_DEL       0x0600 // Bit 10-9
#define RF_PREAMBLE_PREAMBLE_SYM         0x1800 // Bit 12-11
#define RF_PREAMBLE_GATE_DATA            0x2000 // Bit 13
#define RF_PREAMBLE_HALF_BIT_RATE        0x4000 // Bit 14
#define RF_PREAMBLE_SYNC_RX_DATA         0x8000 // Bit 15

/****************************************************************************
* RF_RSSI_REG
****************************************************************************/

#define RF_RSSI_REG_adr 0xFF7048
#define RF_RSSI_REG _A_RF_RSSI_REG.Value
#define RF_RSSI_REG_bit _A_RF_RSSI_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short RFCAL_CAP            : 6; // Bit 5-0
    unsigned short                      : 2; // Bit 7-6
    unsigned short RSSI_VAL             : 6; // Bit 13-8
    unsigned short FAD_CHOICE           : 1; // Bit 14
  };
} RF_RSSI_REG_type __attribute__((aligned(2)));

extern volatile RF_RSSI_REG_type _A_RF_RSSI_REG __attribute__((aligned(2)));

#define RF_RSSI_RFCAL_CAP            0x003F // Bit 5-0
#define RF_RSSI_RSSI_VAL             0x3F00 // Bit 13-8
#define RF_RSSI_FAD_CHOICE           0x4000 // Bit 14

/****************************************************************************
* RF_PORT_CTRL_REG
****************************************************************************/

#define RF_PORT_CTRL_REG_adr 0xFF704A
#define RF_PORT_CTRL_REG _A_RF_PORT_CTRL_REG.Value
#define RF_PORT_CTRL_REG_bit _A_RF_PORT_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PORT1_INV            : 1; // Bit 0
    unsigned short                      : 1; // Bit 1
    unsigned short                      : 1; // Bit 2
    unsigned short                      : 1; // Bit 3
    unsigned short ANT_INACTIVE_VAL     : 1; // Bit 4
  };
} RF_PORT_CTRL_REG_type __attribute__((aligned(2)));

extern volatile RF_PORT_CTRL_REG_type _A_RF_PORT_CTRL_REG __attribute__((aligned(2)));

#define RF_PORT_CTRL_PORT1_INV            0x0001 // Bit 0
#define RF_PORT_CTRL_ANT_INACTIVE_VAL     0x0010 // Bit 4

/****************************************************************************
* RF_PAD_IO_REG
****************************************************************************/

#define RF_PAD_IO_REG_adr 0xFF704C
#define RF_PAD_IO_REG _A_RF_PAD_IO_REG.Value
#define RF_PAD_IO_REG_bit _A_RF_PAD_IO_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short P0_OE                : 1; // Bit 0
    unsigned short P0N_OE               : 1; // Bit 1
    unsigned short P1_OE                : 1; // Bit 2
    unsigned short P2_OE                : 1; // Bit 3
    unsigned short                      : 1; // Bit 4
    unsigned short                      : 1; // Bit 5
    unsigned short P0_IE                : 1; // Bit 6
    unsigned short PAD_OE               : 6; // Bit 12-7
  };
} RF_PAD_IO_REG_type __attribute__((aligned(2)));

extern volatile RF_PAD_IO_REG_type _A_RF_PAD_IO_REG __attribute__((aligned(2)));

#define RF_PAD_IO_P0_OE                0x0001 // Bit 0
#define RF_PAD_IO_P0N_OE               0x0002 // Bit 1
#define RF_PAD_IO_P1_OE                0x0004 // Bit 2
#define RF_PAD_IO_P2_OE                0x0008 // Bit 3
#define RF_PAD_IO_P0_IE                0x0040 // Bit 6
#define RF_PAD_IO_PAD_OE               0x1F80 // Bit 12-7

/****************************************************************************
* RF_PLL_CTRL1_REG
****************************************************************************/

#define RF_PLL_CTRL1_REG_adr 0xFF7050
#define RF_PLL_CTRL1_REG _A_RF_PLL_CTRL1_REG.Value
#define RF_PLL_CTRL1_REG_bit _A_RF_PLL_CTRL1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CH_ZERO              : 13; // Bit 12-0
    unsigned short SGN_NEG              : 1; // Bit 13
    unsigned short CS_MO                : 2; // Bit 15-14
  };
} RF_PLL_CTRL1_REG_type __attribute__((aligned(2)));

extern volatile RF_PLL_CTRL1_REG_type _A_RF_PLL_CTRL1_REG __attribute__((aligned(2)));

#define RF_PLL_CTRL1_CH_ZERO              0x1FFF // Bit 12-0
#define RF_PLL_CTRL1_SGN_NEG              0x2000 // Bit 13
#define RF_PLL_CTRL1_CS_MO                0xC000 // Bit 15-14

/****************************************************************************
* RF_PLL_CTRL2_REG
****************************************************************************/

#define RF_PLL_CTRL2_REG_adr 0xFF7052
#define RF_PLL_CTRL2_REG _A_RF_PLL_CTRL2_REG.Value
#define RF_PLL_CTRL2_REG_bit _A_RF_PLL_CTRL2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short GAUSS_GAIN           : 8; // Bit 7-0
    unsigned short MODINDEX             : 6; // Bit 13-8
    unsigned short MODE20M              : 1; // Bit 14
  };
} RF_PLL_CTRL2_REG_type __attribute__((aligned(2)));

extern volatile RF_PLL_CTRL2_REG_type _A_RF_PLL_CTRL2_REG __attribute__((aligned(2)));

#define RF_PLL_CTRL2_GAUSS_GAIN           0x00FF // Bit 7-0
#define RF_PLL_CTRL2_MODINDEX             0x3F00 // Bit 13-8
#define RF_PLL_CTRL2_MODE20M              0x4000 // Bit 14

/****************************************************************************
* RF_PLL_CTRL3_REG
****************************************************************************/

#define RF_PLL_CTRL3_REG_adr 0xFF7054
#define RF_PLL_CTRL3_REG _A_RF_PLL_CTRL3_REG.Value
#define RF_PLL_CTRL3_REG_bit _A_RF_PLL_CTRL3_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short FASTLOCK_PERIOD      : 10; // Bit 9-0
    unsigned short FASTLOCK             : 1; // Bit 10
    unsigned short LOCK_TIME            : 2; // Bit 12-11
  };
} RF_PLL_CTRL3_REG_type __attribute__((aligned(2)));

extern volatile RF_PLL_CTRL3_REG_type _A_RF_PLL_CTRL3_REG __attribute__((aligned(2)));

#define RF_PLL_CTRL3_FASTLOCK_PERIOD      0x03FF // Bit 9-0
#define RF_PLL_CTRL3_FASTLOCK             0x0400 // Bit 10
#define RF_PLL_CTRL3_LOCK_TIME            0x1800 // Bit 12-11

/****************************************************************************
* RF_PLL_CTRL4_REG
****************************************************************************/

#define RF_PLL_CTRL4_REG_adr 0xFF7056
#define RF_PLL_CTRL4_REG _A_RF_PLL_CTRL4_REG.Value
#define RF_PLL_CTRL4_REG_bit _A_RF_PLL_CTRL4_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short MODCAL_PERIOD        : 8; // Bit 7-0
    unsigned short MODCAL_TRIG          : 1; // Bit 8
    unsigned short                      : 2; // Bit 10-9
    unsigned short SD2_ORDER            : 2; // Bit 12-11
    unsigned short KMOD_ALPHA           : 3; // Bit 15-13
  };
} RF_PLL_CTRL4_REG_type __attribute__((aligned(2)));

extern volatile RF_PLL_CTRL4_REG_type _A_RF_PLL_CTRL4_REG __attribute__((aligned(2)));

#define RF_PLL_CTRL4_MODCAL_PERIOD        0x00FF // Bit 7-0
#define RF_PLL_CTRL4_MODCAL_TRIG          0x0100 // Bit 8
#define RF_PLL_CTRL4_SD2_ORDER            0x1800 // Bit 12-11
#define RF_PLL_CTRL4_KMOD_ALPHA           0xE000 // Bit 15-13

/****************************************************************************
* RF_SLICER_REG
****************************************************************************/

#define RF_SLICER_REG_adr 0xFF7058
#define RF_SLICER_REG _A_RF_SLICER_REG.Value
#define RF_SLICER_REG_bit _A_RF_SLICER_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short TRACK_SLICE          : 1; // Bit 0
    unsigned short DECIDE_ON_AVG        : 1; // Bit 1
    unsigned short SLICE_LOW            : 6; // Bit 7-2
  };
} RF_SLICER_REG_type __attribute__((aligned(2)));

extern volatile RF_SLICER_REG_type _A_RF_SLICER_REG __attribute__((aligned(2)));

#define RF_SLICER_TRACK_SLICE          0x0001 // Bit 0
#define RF_SLICER_DECIDE_ON_AVG        0x0002 // Bit 1
#define RF_SLICER_SLICE_LOW            0x00FC // Bit 7-2

/****************************************************************************
* RF_SLICER_RESULT_REG
****************************************************************************/

#define RF_SLICER_RESULT_REG_adr 0xFF705A
#define RF_SLICER_RESULT_REG _A_RF_SLICER_RESULT_REG.Value
#define RF_SLICER_RESULT_REG_bit _A_RF_SLICER_RESULT_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 6; // Bit 5-0
    unsigned short AFC_VAL              : 2; // Bit 7-6
    unsigned short SLICE_VAL            : 8; // Bit 15-8
  };
} RF_SLICER_RESULT_REG_type __attribute__((aligned(2)));

extern volatile RF_SLICER_RESULT_REG_type _A_RF_SLICER_RESULT_REG __attribute__((aligned(2)));

#define RF_SLICER_RESULT_AFC_VAL              0x00C0 // Bit 7-6
#define RF_SLICER_RESULT_SLICE_VAL            0xFF00 // Bit 15-8

/****************************************************************************
* RF_GAUSS_GAIN_RESULT_REG
****************************************************************************/

#define RF_GAUSS_GAIN_RESULT_REG_adr 0xFF705C
#define RF_GAUSS_GAIN_RESULT_REG _A_RF_GAUSS_GAIN_RESULT_REG

extern volatile unsigned short _A_RF_GAUSS_GAIN_RESULT_REG;

/****************************************************************************
* RF_BURST_MODE_SHADOW1_REG
****************************************************************************/

#define RF_BURST_MODE_SHADOW1_REG_adr 0xFF7070
#define RF_BURST_MODE_SHADOW1_REG _A_RF_BURST_MODE_SHADOW1_REG.Value
#define RF_BURST_MODE_SHADOW1_REG_bit _A_RF_BURST_MODE_SHADOW1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CN_SHW               : 8; // Bit 7-0
    unsigned short RFCAL_SHW            : 6; // Bit 13-8
    unsigned short RSSI_MODE_SHW        : 1; // Bit 14
  };
} RF_BURST_MODE_SHADOW1_REG_type __attribute__((aligned(2)));

extern volatile RF_BURST_MODE_SHADOW1_REG_type _A_RF_BURST_MODE_SHADOW1_REG __attribute__((aligned(2)));

#define RF_BURST_MODE_SHADOW1_CN_SHW               0x00FF // Bit 7-0
#define RF_BURST_MODE_SHADOW1_RFCAL_SHW            0x3F00 // Bit 13-8
#define RF_BURST_MODE_SHADOW1_RSSI_MODE_SHW        0x4000 // Bit 14

/****************************************************************************
* RF_BURST_MODE_SHADOW2_REG
****************************************************************************/

#define RF_BURST_MODE_SHADOW2_REG_adr 0xFF7072
#define RF_BURST_MODE_SHADOW2_REG _A_RF_BURST_MODE_SHADOW2_REG.Value
#define RF_BURST_MODE_SHADOW2_REG_bit _A_RF_BURST_MODE_SHADOW2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short FAD_SHW              : 2; // Bit 1-0
    unsigned short TX_ASSERT            : 1; // Bit 2
    unsigned short RX_ASSERT            : 1; // Bit 3
    unsigned short SHADOW_EN            : 1; // Bit 4
  };
} RF_BURST_MODE_SHADOW2_REG_type __attribute__((aligned(2)));

extern volatile RF_BURST_MODE_SHADOW2_REG_type _A_RF_BURST_MODE_SHADOW2_REG __attribute__((aligned(2)));

#define RF_BURST_MODE_SHADOW2_FAD_SHW              0x0003 // Bit 1-0
#define RF_BURST_MODE_SHADOW2_TX_ASSERT            0x0004 // Bit 2
#define RF_BURST_MODE_SHADOW2_RX_ASSERT            0x0008 // Bit 3
#define RF_BURST_MODE_SHADOW2_SHADOW_EN            0x0010 // Bit 4

/****************************************************************************
* RF_DCF_MONITOR_REG
****************************************************************************/

#define RF_DCF_MONITOR_REG_adr 0xFF7074
#define RF_DCF_MONITOR_REG _A_RF_DCF_MONITOR_REG.Value
#define RF_DCF_MONITOR_REG_bit _A_RF_DCF_MONITOR_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DP0_SEL              : 4; // Bit 3-0
    unsigned short DP1_SEL              : 4; // Bit 7-4
    unsigned short DP2_SEL              : 4; // Bit 11-8
    unsigned short DP3_SEL              : 4; // Bit 15-12
  };
} RF_DCF_MONITOR_REG_type __attribute__((aligned(2)));

extern volatile RF_DCF_MONITOR_REG_type _A_RF_DCF_MONITOR_REG __attribute__((aligned(2)));

#define RF_DCF_MONITOR_DP0_SEL              0x000F // Bit 3-0
#define RF_DCF_MONITOR_DP1_SEL              0x00F0 // Bit 7-4
#define RF_DCF_MONITOR_DP2_SEL              0x0F00 // Bit 11-8
#define RF_DCF_MONITOR_DP3_SEL              0xF000 // Bit 15-12

/****************************************************************************
* RF_SYNTH_CTRL1_REG
****************************************************************************/

#define RF_SYNTH_CTRL1_REG_adr 0xFF7080
#define RF_SYNTH_CTRL1_REG _A_RF_SYNTH_CTRL1_REG

extern volatile unsigned short _A_RF_SYNTH_CTRL1_REG;

/****************************************************************************
* RF_SYNTH_CTRL2_REG
****************************************************************************/

#define RF_SYNTH_CTRL2_REG_adr 0xFF7082
#define RF_SYNTH_CTRL2_REG _A_RF_SYNTH_CTRL2_REG

extern volatile unsigned short _A_RF_SYNTH_CTRL2_REG;

/****************************************************************************
* RF_AGC_REG
****************************************************************************/

#define RF_AGC_REG_adr 0xFF7084
#define RF_AGC_REG _A_RF_AGC_REG

extern volatile unsigned short _A_RF_AGC_REG;

/****************************************************************************
* RF_AGC12_TH_REG
****************************************************************************/

#define RF_AGC12_TH_REG_adr 0xFF7086
#define RF_AGC12_TH_REG _A_RF_AGC12_TH_REG

extern volatile unsigned short _A_RF_AGC12_TH_REG;

/****************************************************************************
* RF_AGC12_ALPHA_REG
****************************************************************************/

#define RF_AGC12_ALPHA_REG_adr 0xFF7088
#define RF_AGC12_ALPHA_REG _A_RF_AGC12_ALPHA_REG

extern volatile unsigned short _A_RF_AGC12_ALPHA_REG;

/****************************************************************************
* RF_DC_OFFSET_REG
****************************************************************************/

#define RF_DC_OFFSET_REG_adr 0xFF708C
#define RF_DC_OFFSET_REG _A_RF_DC_OFFSET_REG

extern volatile unsigned short _A_RF_DC_OFFSET_REG;

/****************************************************************************
* RF_DC_OFFSET34_REG
****************************************************************************/

#define RF_DC_OFFSET34_REG_adr 0xFF708E
#define RF_DC_OFFSET34_REG _A_RF_DC_OFFSET34_REG

extern volatile unsigned short _A_RF_DC_OFFSET34_REG;

/****************************************************************************
* RF_IQ_DC_OFFSET_REG
****************************************************************************/

#define RF_IQ_DC_OFFSET_REG_adr 0xFF7090
#define RF_IQ_DC_OFFSET_REG _A_RF_IQ_DC_OFFSET_REG

extern volatile unsigned short _A_RF_IQ_DC_OFFSET_REG;

/****************************************************************************
* RF_IF_CTRL_REG
****************************************************************************/

#define RF_IF_CTRL_REG_adr 0xFF7092
#define RF_IF_CTRL_REG _A_RF_IF_CTRL_REG

extern volatile unsigned short _A_RF_IF_CTRL_REG;

/****************************************************************************
* RF_REF_OSC_REG
****************************************************************************/

#define RF_REF_OSC_REG_adr 0xFF7094
#define RF_REF_OSC_REG _A_RF_REF_OSC_REG

extern volatile unsigned short _A_RF_REF_OSC_REG;

/****************************************************************************
* RF_ADC_CTRL_REG
****************************************************************************/

#define RF_ADC_CTRL_REG_adr 0xFF7096
#define RF_ADC_CTRL_REG _A_RF_ADC_CTRL_REG

extern volatile unsigned short _A_RF_ADC_CTRL_REG;

/****************************************************************************
* RF_RFIO_CTRL_REG
****************************************************************************/

#define RF_RFIO_CTRL_REG_adr 0xFF7098
#define RF_RFIO_CTRL_REG _A_RF_RFIO_CTRL_REG

extern volatile unsigned short _A_RF_RFIO_CTRL_REG;

/****************************************************************************
* RF_BIAS_CTRL_REG
****************************************************************************/

#define RF_BIAS_CTRL_REG_adr 0xFF709A
#define RF_BIAS_CTRL_REG _A_RF_BIAS_CTRL_REG

extern volatile unsigned short _A_RF_BIAS_CTRL_REG;

/****************************************************************************
* RF_DRIFT_TEST_REG
****************************************************************************/

#define RF_DRIFT_TEST_REG_adr 0xFF709C
#define RF_DRIFT_TEST_REG _A_RF_DRIFT_TEST_REG

extern volatile unsigned short _A_RF_DRIFT_TEST_REG;

/****************************************************************************
* RF_TEST_MODE_REG
****************************************************************************/

#define RF_TEST_MODE_REG_adr 0xFF709E
#define RF_TEST_MODE_REG _A_RF_TEST_MODE_REG

extern volatile unsigned short _A_RF_TEST_MODE_REG;

/****************************************************************************
* RF_LDO_TEST_REG
****************************************************************************/

#define RF_LDO_TEST_REG_adr 0xFF70A0
#define RF_LDO_TEST_REG _A_RF_LDO_TEST_REG

extern volatile unsigned short _A_RF_LDO_TEST_REG;

/****************************************************************************
* RF_PLL_CTRL5_REG
****************************************************************************/

#define RF_PLL_CTRL5_REG_adr 0xFF70AC
#define RF_PLL_CTRL5_REG _A_RF_PLL_CTRL5_REG

extern volatile unsigned short _A_RF_PLL_CTRL5_REG;

/****************************************************************************
* RF_PLL_CTRL6_REG
****************************************************************************/

#define RF_PLL_CTRL6_REG_adr 0xFF70AE
#define RF_PLL_CTRL6_REG _A_RF_PLL_CTRL6_REG

extern volatile unsigned short _A_RF_PLL_CTRL6_REG;

/****************************************************************************
* RF_BBADC_CTRL_REG
****************************************************************************/

#define RF_BBADC_CTRL_REG_adr 0xFF70B0
#define RF_BBADC_CTRL_REG _A_RF_BBADC_CTRL_REG.Value
#define RF_BBADC_CTRL_REG_bit _A_RF_BBADC_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short RF_BBADC_TEST1       : 3; // Bit 2-0
    unsigned short PA_CASCODE_LEVEL     : 3; // Bit 5-3
    unsigned short RF_BBADC_TEST0       : 10; // Bit 15-6
  };
} RF_BBADC_CTRL_REG_type __attribute__((aligned(2)));

extern volatile RF_BBADC_CTRL_REG_type _A_RF_BBADC_CTRL_REG __attribute__((aligned(2)));

#define RF_BBADC_CTRL_RF_BBADC_TEST1       0x0007 // Bit 2-0
#define RF_BBADC_CTRL_PA_CASCODE_LEVEL     0x0038 // Bit 5-3
#define RF_BBADC_CTRL_RF_BBADC_TEST0       0xFFC0 // Bit 15-6

/****************************************************************************
* RF_PA_CTRL1_REG
****************************************************************************/

#define RF_PA_CTRL1_REG_adr 0xFF70B2
#define RF_PA_CTRL1_REG _A_RF_PA_CTRL1_REG.Value
#define RF_PA_CTRL1_REG_bit _A_RF_PA_CTRL1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 4; // Bit 3-0
    unsigned short PA_CUR_SET1          : 4; // Bit 7-4
    unsigned short PA_CUR_SET2          : 4; // Bit 11-8
    unsigned short PA_ATT_SET           : 4; // Bit 15-12
  };
} RF_PA_CTRL1_REG_type __attribute__((aligned(2)));

extern volatile RF_PA_CTRL1_REG_type _A_RF_PA_CTRL1_REG __attribute__((aligned(2)));

#define RF_PA_CTRL1_PA_CUR_SET1          0x00F0 // Bit 7-4
#define RF_PA_CTRL1_PA_CUR_SET2          0x0F00 // Bit 11-8
#define RF_PA_CTRL1_PA_ATT_SET           0xF000 // Bit 15-12

/****************************************************************************
* RF_PA_CTRL2_REG
****************************************************************************/

#define RF_PA_CTRL2_REG_adr 0xFF70B4
#define RF_PA_CTRL2_REG _A_RF_PA_CTRL2_REG.Value
#define RF_PA_CTRL2_REG_bit _A_RF_PA_CTRL2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 8; // Bit 7-0
    unsigned short RAMP_SPEED1          : 4; // Bit 11-8
    unsigned short RAMP_SPEED2          : 4; // Bit 15-12
  };
} RF_PA_CTRL2_REG_type __attribute__((aligned(2)));

extern volatile RF_PA_CTRL2_REG_type _A_RF_PA_CTRL2_REG __attribute__((aligned(2)));

#define RF_PA_CTRL2_RAMP_SPEED1          0x0F00 // Bit 11-8
#define RF_PA_CTRL2_RAMP_SPEED2          0xF000 // Bit 15-12

/****************************************************************************
* RF_IFCAL_RESULT_REG
****************************************************************************/

#define RF_IFCAL_RESULT_REG_adr 0xFF70B6
#define RF_IFCAL_RESULT_REG _A_RF_IFCAL_RESULT_REG

extern volatile unsigned short _A_RF_IFCAL_RESULT_REG;

/****************************************************************************
* RF_DC_OFFSET12_REG
****************************************************************************/

#define RF_DC_OFFSET12_REG_adr 0xFF70B8
#define RF_DC_OFFSET12_REG _A_RF_DC_OFFSET12_REG

extern volatile unsigned short _A_RF_DC_OFFSET12_REG;

/****************************************************************************
* RF_AGC_RESULT_REG
****************************************************************************/

#define RF_AGC_RESULT_REG_adr 0xFF70BA
#define RF_AGC_RESULT_REG _A_RF_AGC_RESULT_REG

extern volatile unsigned short _A_RF_AGC_RESULT_REG;

/****************************************************************************
* RF_GAUSS_GAIN_MSB_REG
****************************************************************************/

#define RF_GAUSS_GAIN_MSB_REG_adr 0xFF70BC
#define RF_GAUSS_GAIN_MSB_REG _A_RF_GAUSS_GAIN_MSB_REG

extern volatile unsigned short _A_RF_GAUSS_GAIN_MSB_REG;

/****************************************************************************
* RF_RXFE_CTRL_REG
****************************************************************************/

#define RF_RXFE_CTRL_REG_adr 0xFF70BE
#define RF_RXFE_CTRL_REG _A_RF_RXFE_CTRL_REG

extern volatile unsigned short _A_RF_RXFE_CTRL_REG;

/****************************************************************************
* RF_FAFC_CTRL_REG
****************************************************************************/

#define RF_FAFC_CTRL_REG_adr 0xFF70C0
#define RF_FAFC_CTRL_REG _A_RF_FAFC_CTRL_REG.Value
#define RF_FAFC_CTRL_REG_bit _A_RF_FAFC_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short FAFC_EN              : 1; // Bit 0
    unsigned short FAFC_MEAN            : 1; // Bit 1
    unsigned short FAST_AFC_EN          : 1; // Bit 2
    unsigned short FAST_VAL             : 8; // Bit 10-3
  };
} RF_FAFC_CTRL_REG_type __attribute__((aligned(2)));

extern volatile RF_FAFC_CTRL_REG_type _A_RF_FAFC_CTRL_REG __attribute__((aligned(2)));

#define RF_FAFC_CTRL_FAFC_EN              0x0001 // Bit 0
#define RF_FAFC_CTRL_FAFC_MEAN            0x0002 // Bit 1
#define RF_FAFC_CTRL_FAST_AFC_EN          0x0004 // Bit 2
#define RF_FAFC_CTRL_FAST_VAL             0x07F8 // Bit 10-3

/****************************************************************************
* RF_FAFC_RESULT_REG
****************************************************************************/

#define RF_FAFC_RESULT_REG_adr 0xFF70C2
#define RF_FAFC_RESULT_REG _A_RF_FAFC_RESULT_REG

extern volatile unsigned short _A_RF_FAFC_RESULT_REG;

/****************************************************************************
* RF_TEST_MODE2_REG
****************************************************************************/

#define RF_TEST_MODE2_REG_adr 0xFF70C4
#define RF_TEST_MODE2_REG _A_RF_TEST_MODE2_REG.Value
#define RF_TEST_MODE2_REG_bit _A_RF_TEST_MODE2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PA_CUR_SET3          : 6; // Bit 5-0
    unsigned short PA_ICTRL_ENABLE      : 1; // Bit 6
    unsigned short RF_TEST_MODE0        : 9; // Bit 15-7
  };
} RF_TEST_MODE2_REG_type __attribute__((aligned(2)));

extern volatile RF_TEST_MODE2_REG_type _A_RF_TEST_MODE2_REG __attribute__((aligned(2)));

#define RF_TEST_MODE2_PA_CUR_SET3          0x003F // Bit 5-0
#define RF_TEST_MODE2_PA_ICTRL_ENABLE      0x0040 // Bit 6
#define RF_TEST_MODE2_RF_TEST_MODE0        0xFF80 // Bit 15-7

/****************************************************************************
* CHIP_TEST1_REG
****************************************************************************/

#define CHIP_TEST1_REG_adr 0xFFFBF4

#define CHIP_TEST1_REG *((volatile unsigned char*)0xFFFBF4)

extern volatile unsigned short _A_CHIP_TEST1_REG;

/****************************************************************************
* CHIP_TEST2_REG
****************************************************************************/

#define CHIP_TEST2_REG_adr 0xFFFBF5

#define CHIP_TEST2_REG *((volatile unsigned char*)0xFFFBF5)

extern volatile unsigned short _A_CHIP_TEST2_REG;

/****************************************************************************
* CHIP_ID1_REG
****************************************************************************/

#define CHIP_ID1_REG_adr 0xFFFBF8

#define CHIP_ID1_REG *((volatile unsigned char*)0xFFFBF8)

extern volatile unsigned short _A_CHIP_ID1_REG;

/****************************************************************************
* CHIP_ID2_REG
****************************************************************************/

#define CHIP_ID2_REG_adr 0xFFFBF9

#define CHIP_ID2_REG *((volatile unsigned char*)0xFFFBF9)

extern volatile unsigned short _A_CHIP_ID2_REG;

/****************************************************************************
* CHIP_ID3_REG
****************************************************************************/

#define CHIP_ID3_REG_adr 0xFFFBFA

#define CHIP_ID3_REG *((volatile unsigned char*)0xFFFBFA)

extern volatile unsigned short _A_CHIP_ID3_REG;

/****************************************************************************
* CHIP_SWC_REG
****************************************************************************/

#define CHIP_SWC_REG_adr 0xFFFBFB

#define CHIP_SWC_REG *((volatile unsigned char*)0xFFFBFB)

extern volatile unsigned short _A_CHIP_SWC_REG;

/****************************************************************************
* CHIP_REVISION_REG
****************************************************************************/

#define CHIP_REVISION_REG_adr 0xFFFBFC

#define CHIP_REVISION_REG *((volatile unsigned char*)0xFFFBFC)

extern volatile unsigned short _A_CHIP_REVISION_REG;

/****************************************************************************
* CHIP_CONFIG1_REG
****************************************************************************/

#define CHIP_CONFIG1_REG_adr 0xFFFBFD

#define CHIP_CONFIG1_REG *((volatile unsigned char*)0xFFFBFD)

extern volatile unsigned short _A_CHIP_CONFIG1_REG;

/****************************************************************************
* CHIP_CONFIG2_REG
****************************************************************************/

#define CHIP_CONFIG2_REG_adr 0xFFFBFE

#define CHIP_CONFIG2_REG *((volatile unsigned char*)0xFFFBFE)

extern volatile unsigned short _A_CHIP_CONFIG2_REG;

/****************************************************************************
* CHIP_CONFIG3_REG
****************************************************************************/

#define CHIP_CONFIG3_REG_adr 0xFFFBFF

#define CHIP_CONFIG3_REG *((volatile unsigned char*)0xFFFBFF)

extern volatile unsigned short _A_CHIP_CONFIG3_REG;

/****************************************************************************
* DSP_MAIN_SYNC0_REG
****************************************************************************/

#define DSP_MAIN_SYNC0_REG_adr 0x1027F80
#define DSP_MAIN_SYNC0_REG _A_DSP_MAIN_SYNC0_REG.Value
#define DSP_MAIN_SYNC0_REG_bit _A_DSP_MAIN_SYNC0_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short RAMIN0_SYNC          : 2; // Bit 1-0
    unsigned short RAMIN1_SYNC          : 2; // Bit 3-2
    unsigned short RAMIN2_SYNC          : 2; // Bit 5-4
    unsigned short RAMIN3_SYNC          : 2; // Bit 7-6
    unsigned short RAMOUT0_SYNC         : 2; // Bit 9-8
    unsigned short RAMOUT1_SYNC         : 2; // Bit 11-10
    unsigned short RAMOUT2_SYNC         : 2; // Bit 13-12
    unsigned short RAMOUT3_SYNC         : 2; // Bit 15-14
  };
} DSP_MAIN_SYNC0_REG_type __attribute__((aligned(2)));

extern volatile DSP_MAIN_SYNC0_REG_type _A_DSP_MAIN_SYNC0_REG __attribute__((aligned(2)));

#define DSP_MAIN_SYNC0_RAMIN0_SYNC          0x0003 // Bit 1-0
#define DSP_MAIN_SYNC0_RAMIN1_SYNC          0x000C // Bit 3-2
#define DSP_MAIN_SYNC0_RAMIN2_SYNC          0x0030 // Bit 5-4
#define DSP_MAIN_SYNC0_RAMIN3_SYNC          0x00C0 // Bit 7-6
#define DSP_MAIN_SYNC0_RAMOUT0_SYNC         0x0300 // Bit 9-8
#define DSP_MAIN_SYNC0_RAMOUT1_SYNC         0x0C00 // Bit 11-10
#define DSP_MAIN_SYNC0_RAMOUT2_SYNC         0x3000 // Bit 13-12
#define DSP_MAIN_SYNC0_RAMOUT3_SYNC         0xC000 // Bit 15-14

/****************************************************************************
* DSP_MAIN_SYNC1_REG
****************************************************************************/

#define DSP_MAIN_SYNC1_REG_adr 0x1027F82
#define DSP_MAIN_SYNC1_REG _A_DSP_MAIN_SYNC1_REG.Value
#define DSP_MAIN_SYNC1_REG_bit _A_DSP_MAIN_SYNC1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DSP_SYNC0            : 2; // Bit 1-0
    unsigned short DSP_SYNC1            : 2; // Bit 3-2
    unsigned short DSP_SYNC2            : 2; // Bit 5-4
    unsigned short AD_SYNC              : 2; // Bit 7-6
    unsigned short DA_CLASSD_SYNC       : 2; // Bit 9-8
    unsigned short DA_LSR_SYNC          : 2; // Bit 11-10
    unsigned short ADC_SYNC             : 2; // Bit 13-12
    unsigned short PCM_SYNC             : 2; // Bit 15-14
  };
} DSP_MAIN_SYNC1_REG_type __attribute__((aligned(2)));

extern volatile DSP_MAIN_SYNC1_REG_type _A_DSP_MAIN_SYNC1_REG __attribute__((aligned(2)));

#define DSP_MAIN_SYNC1_DSP_SYNC0            0x0003 // Bit 1-0
#define DSP_MAIN_SYNC1_DSP_SYNC1            0x000C // Bit 3-2
#define DSP_MAIN_SYNC1_DSP_SYNC2            0x0030 // Bit 5-4
#define DSP_MAIN_SYNC1_AD_SYNC              0x00C0 // Bit 7-6
#define DSP_MAIN_SYNC1_DA_CLASSD_SYNC       0x0300 // Bit 9-8
#define DSP_MAIN_SYNC1_DA_LSR_SYNC          0x0C00 // Bit 11-10
#define DSP_MAIN_SYNC1_ADC_SYNC             0x3000 // Bit 13-12
#define DSP_MAIN_SYNC1_PCM_SYNC             0xC000 // Bit 15-14

/****************************************************************************
* DSP_MAIN_CNT_REG
****************************************************************************/

#define DSP_MAIN_CNT_REG_adr 0x1027F84
#define DSP_MAIN_CNT_REG _A_DSP_MAIN_CNT_REG.Value
#define DSP_MAIN_CNT_REG_bit _A_DSP_MAIN_CNT_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DSP_MAIN_CNT         : 8; // Bit 7-0
    unsigned short DSP_MAIN_REL         : 8; // Bit 15-8
  };
} DSP_MAIN_CNT_REG_type __attribute__((aligned(2)));

extern volatile DSP_MAIN_CNT_REG_type _A_DSP_MAIN_CNT_REG __attribute__((aligned(2)));

#define DSP_MAIN_CNT_DSP_MAIN_CNT         0x00FF // Bit 7-0
#define DSP_MAIN_CNT_DSP_MAIN_REL         0xFF00 // Bit 15-8

/****************************************************************************
* DSP_ADC1S_REG
****************************************************************************/

#define DSP_ADC1S_REG_adr 0x1027F86
#define DSP_ADC1S_REG _A_DSP_ADC1S_REG

extern volatile unsigned short _A_DSP_ADC1S_REG;

/****************************************************************************
* DSP_ADC0S_REG
****************************************************************************/

#define DSP_ADC0S_REG_adr 0x1027F88
#define DSP_ADC0S_REG _A_DSP_ADC0S_REG

extern volatile unsigned short _A_DSP_ADC0S_REG;

/****************************************************************************
* DSP_CLASSD_REG
****************************************************************************/

#define DSP_CLASSD_REG_adr 0x1027F8A
#define DSP_CLASSD_REG _A_DSP_CLASSD_REG

extern volatile unsigned short _A_DSP_CLASSD_REG;

/****************************************************************************
* DSP_CODEC_MIC_GAIN_REG
****************************************************************************/

#define DSP_CODEC_MIC_GAIN_REG_adr 0x1027F8C
#define DSP_CODEC_MIC_GAIN_REG _A_DSP_CODEC_MIC_GAIN_REG.Value
#define DSP_CODEC_MIC_GAIN_REG_bit _A_DSP_CODEC_MIC_GAIN_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 12; // Bit 11-0
    unsigned short DSP_MIC_GAIN         : 4; // Bit 15-12
  };
} DSP_CODEC_MIC_GAIN_REG_type __attribute__((aligned(2)));

extern volatile DSP_CODEC_MIC_GAIN_REG_type _A_DSP_CODEC_MIC_GAIN_REG __attribute__((aligned(2)));

#define DSP_CODEC_MIC_GAIN_DSP_MIC_GAIN         0xF000 // Bit 15-12

/****************************************************************************
* DSP_CODEC_OUT_REG
****************************************************************************/

#define DSP_CODEC_OUT_REG_adr 0x1027F8E
#define DSP_CODEC_OUT_REG _A_DSP_CODEC_OUT_REG

extern volatile unsigned short _A_DSP_CODEC_OUT_REG;

/****************************************************************************
* DSP_CODEC_IN_REG
****************************************************************************/

#define DSP_CODEC_IN_REG_adr 0x1027F90
#define DSP_CODEC_IN_REG _A_DSP_CODEC_IN_REG

extern volatile unsigned short _A_DSP_CODEC_IN_REG;

/****************************************************************************
* DSP_RAM_OUT0_REG
****************************************************************************/

#define DSP_RAM_OUT0_REG_adr 0x1027F92
#define DSP_RAM_OUT0_REG _A_DSP_RAM_OUT0_REG

extern volatile unsigned short _A_DSP_RAM_OUT0_REG;

/****************************************************************************
* DSP_RAM_OUT1_REG
****************************************************************************/

#define DSP_RAM_OUT1_REG_adr 0x1027F94
#define DSP_RAM_OUT1_REG _A_DSP_RAM_OUT1_REG

extern volatile unsigned short _A_DSP_RAM_OUT1_REG;

/****************************************************************************
* DSP_RAM_OUT2_REG
****************************************************************************/

#define DSP_RAM_OUT2_REG_adr 0x1027F96
#define DSP_RAM_OUT2_REG _A_DSP_RAM_OUT2_REG

extern volatile unsigned short _A_DSP_RAM_OUT2_REG;

/****************************************************************************
* DSP_RAM_OUT3_REG
****************************************************************************/

#define DSP_RAM_OUT3_REG_adr 0x1027F98
#define DSP_RAM_OUT3_REG _A_DSP_RAM_OUT3_REG

extern volatile unsigned short _A_DSP_RAM_OUT3_REG;

/****************************************************************************
* DSP_RAM_IN0_REG
****************************************************************************/

#define DSP_RAM_IN0_REG_adr 0x1027F9A
#define DSP_RAM_IN0_REG _A_DSP_RAM_IN0_REG

extern volatile unsigned short _A_DSP_RAM_IN0_REG;

/****************************************************************************
* DSP_RAM_IN1_REG
****************************************************************************/

#define DSP_RAM_IN1_REG_adr 0x1027F9C
#define DSP_RAM_IN1_REG _A_DSP_RAM_IN1_REG

extern volatile unsigned short _A_DSP_RAM_IN1_REG;

/****************************************************************************
* DSP_RAM_IN2_REG
****************************************************************************/

#define DSP_RAM_IN2_REG_adr 0x1027F9E
#define DSP_RAM_IN2_REG _A_DSP_RAM_IN2_REG

extern volatile unsigned short _A_DSP_RAM_IN2_REG;

/****************************************************************************
* DSP_RAM_IN3_REG
****************************************************************************/

#define DSP_RAM_IN3_REG_adr 0x1027FA0
#define DSP_RAM_IN3_REG _A_DSP_RAM_IN3_REG

extern volatile unsigned short _A_DSP_RAM_IN3_REG;

/****************************************************************************
* DSP_ZCROSS1_OUT_REG
****************************************************************************/

#define DSP_ZCROSS1_OUT_REG_adr 0x1027FA2
#define DSP_ZCROSS1_OUT_REG _A_DSP_ZCROSS1_OUT_REG.Value
#define DSP_ZCROSS1_OUT_REG_bit _A_DSP_ZCROSS1_OUT_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 15; // Bit 14-0
    unsigned short DSP_ZCROSSx          : 1; // Bit 15
  };
} DSP_ZCROSS1_OUT_REG_type __attribute__((aligned(2)));

extern volatile DSP_ZCROSS1_OUT_REG_type _A_DSP_ZCROSS1_OUT_REG __attribute__((aligned(2)));

#define DSP_ZCROSS1_OUT_DSP_ZCROSSx          0x8000 // Bit 15

/****************************************************************************
* DSP_ZCROSS2_OUT_REG
****************************************************************************/

#define DSP_ZCROSS2_OUT_REG_adr 0x1027FA4
#define DSP_ZCROSS2_OUT_REG _A_DSP_ZCROSS2_OUT_REG.Value
#define DSP_ZCROSS2_OUT_REG_bit _A_DSP_ZCROSS2_OUT_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 15; // Bit 14-0
    unsigned short DSP_ZCROSSx          : 1; // Bit 15
  };
} DSP_ZCROSS2_OUT_REG_type __attribute__((aligned(2)));

extern volatile DSP_ZCROSS2_OUT_REG_type _A_DSP_ZCROSS2_OUT_REG __attribute__((aligned(2)));

#define DSP_ZCROSS2_OUT_DSP_ZCROSSx          0x8000 // Bit 15

/****************************************************************************
* DSP_PCM_OUT0_REG
****************************************************************************/

#define DSP_PCM_OUT0_REG_adr 0x1027FA6
#define DSP_PCM_OUT0_REG _A_DSP_PCM_OUT0_REG

extern volatile unsigned short _A_DSP_PCM_OUT0_REG;

/****************************************************************************
* DSP_PCM_OUT1_REG
****************************************************************************/

#define DSP_PCM_OUT1_REG_adr 0x1027FA8
#define DSP_PCM_OUT1_REG _A_DSP_PCM_OUT1_REG

extern volatile unsigned short _A_DSP_PCM_OUT1_REG;

/****************************************************************************
* DSP_PCM_OUT2_REG
****************************************************************************/

#define DSP_PCM_OUT2_REG_adr 0x1027FAA
#define DSP_PCM_OUT2_REG _A_DSP_PCM_OUT2_REG

extern volatile unsigned short _A_DSP_PCM_OUT2_REG;

/****************************************************************************
* DSP_PCM_OUT3_REG
****************************************************************************/

#define DSP_PCM_OUT3_REG_adr 0x1027FAC
#define DSP_PCM_OUT3_REG _A_DSP_PCM_OUT3_REG

extern volatile unsigned short _A_DSP_PCM_OUT3_REG;

/****************************************************************************
* DSP_PCM_IN0_REG
****************************************************************************/

#define DSP_PCM_IN0_REG_adr 0x1027FAE
#define DSP_PCM_IN0_REG _A_DSP_PCM_IN0_REG

extern volatile unsigned short _A_DSP_PCM_IN0_REG;

/****************************************************************************
* DSP_PCM_IN1_REG
****************************************************************************/

#define DSP_PCM_IN1_REG_adr 0x1027FB0
#define DSP_PCM_IN1_REG _A_DSP_PCM_IN1_REG

extern volatile unsigned short _A_DSP_PCM_IN1_REG;

/****************************************************************************
* DSP_PCM_IN2_REG
****************************************************************************/

#define DSP_PCM_IN2_REG_adr 0x1027FB2
#define DSP_PCM_IN2_REG _A_DSP_PCM_IN2_REG

extern volatile unsigned short _A_DSP_PCM_IN2_REG;

/****************************************************************************
* DSP_PCM_IN3_REG
****************************************************************************/

#define DSP_PCM_IN3_REG_adr 0x1027FB4
#define DSP_PCM_IN3_REG _A_DSP_PCM_IN3_REG

extern volatile unsigned short _A_DSP_PCM_IN3_REG;

/****************************************************************************
* DSP_PCM_CTRL_REG
****************************************************************************/

#define DSP_PCM_CTRL_REG_adr 0x1027FB6
#define DSP_PCM_CTRL_REG _A_DSP_PCM_CTRL_REG.Value
#define DSP_PCM_CTRL_REG_bit _A_DSP_PCM_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short PCM_EN               : 1; // Bit 0
    unsigned short PCM_MASTER           : 1; // Bit 1
    unsigned short DSP_PCM_SYNC         : 1; // Bit 2
    unsigned short PCM_FSC0LEN          : 2; // Bit 4-3
    unsigned short PCM_FSC0DEL          : 1; // Bit 5
    unsigned short PCM_PPOD             : 1; // Bit 6
    unsigned short PCM_CLKINV           : 1; // Bit 7
    unsigned short PCM_FSCINV           : 1; // Bit 8
    unsigned short PCM_CLK_BIT          : 1; // Bit 9
    unsigned short PCM_CH0_DEL          : 5; // Bit 14-10
    unsigned short PCM_FSC0LEN48        : 1; // Bit 15
  };
} DSP_PCM_CTRL_REG_type __attribute__((aligned(2)));

extern volatile DSP_PCM_CTRL_REG_type _A_DSP_PCM_CTRL_REG __attribute__((aligned(2)));

#define DSP_PCM_CTRL_PCM_EN               0x0001 // Bit 0
#define DSP_PCM_CTRL_PCM_MASTER           0x0002 // Bit 1
#define DSP_PCM_CTRL_DSP_PCM_SYNC         0x0004 // Bit 2
#define DSP_PCM_CTRL_PCM_FSC0LEN          0x0018 // Bit 4-3
#define DSP_PCM_CTRL_PCM_FSC0DEL          0x0020 // Bit 5
#define DSP_PCM_CTRL_PCM_PPOD             0x0040 // Bit 6
#define DSP_PCM_CTRL_PCM_CLKINV           0x0080 // Bit 7
#define DSP_PCM_CTRL_PCM_FSCINV           0x0100 // Bit 8
#define DSP_PCM_CTRL_PCM_CLK_BIT          0x0200 // Bit 9
#define DSP_PCM_CTRL_PCM_CH0_DEL          0x7C00 // Bit 14-10
#define DSP_PCM_CTRL_PCM_FSC0LEN48        0x8000 // Bit 15

/****************************************************************************
* DSP_PHASE_INFO_REG
****************************************************************************/

#define DSP_PHASE_INFO_REG_adr 0x1027FB8
#define DSP_PHASE_INFO_REG _A_DSP_PHASE_INFO_REG

extern volatile unsigned short _A_DSP_PHASE_INFO_REG;

/****************************************************************************
* DSP_MAIN_CTRL_REG
****************************************************************************/

#define DSP_MAIN_CTRL_REG_adr 0x1027FBC
#define DSP_MAIN_CTRL_REG _A_DSP_MAIN_CTRL_REG.Value
#define DSP_MAIN_CTRL_REG_bit _A_DSP_MAIN_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DSP_MAIN_PRESET      : 8; // Bit 7-0
    unsigned short DSP_MAIN_CTRL        : 2; // Bit 9-8
    unsigned short PCM_DOMAIN           : 1; // Bit 10
    unsigned short AD_DOMAIN            : 1; // Bit 11
    unsigned short LSR_DOMAIN           : 1; // Bit 12
    unsigned short CLASSD_DOMAIN        : 1; // Bit 13
  };
} DSP_MAIN_CTRL_REG_type __attribute__((aligned(2)));

extern volatile DSP_MAIN_CTRL_REG_type _A_DSP_MAIN_CTRL_REG __attribute__((aligned(2)));

#define DSP_MAIN_CTRL_DSP_MAIN_PRESET      0x00FF // Bit 7-0
#define DSP_MAIN_CTRL_DSP_MAIN_CTRL        0x0300 // Bit 9-8
#define DSP_MAIN_CTRL_PCM_DOMAIN           0x0400 // Bit 10
#define DSP_MAIN_CTRL_AD_DOMAIN            0x0800 // Bit 11
#define DSP_MAIN_CTRL_LSR_DOMAIN           0x1000 // Bit 12
#define DSP_MAIN_CTRL_CLASSD_DOMAIN        0x2000 // Bit 13

/****************************************************************************
* DSP_CLASSD_BUZZOFF_REG
****************************************************************************/

#define DSP_CLASSD_BUZZOFF_REG_adr 0x1027FBE
#define DSP_CLASSD_BUZZOFF_REG _A_DSP_CLASSD_BUZZOFF_REG.Value
#define DSP_CLASSD_BUZZOFF_REG_bit _A_DSP_CLASSD_BUZZOFF_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 15; // Bit 14-0
    unsigned short BUZZOFF              : 1; // Bit 15
  };
} DSP_CLASSD_BUZZOFF_REG_type __attribute__((aligned(2)));

extern volatile DSP_CLASSD_BUZZOFF_REG_type _A_DSP_CLASSD_BUZZOFF_REG __attribute__((aligned(2)));

#define DSP_CLASSD_BUZZOFF_BUZZOFF              0x8000 // Bit 15

/****************************************************************************
* DSP_PCM_OUT4_REG
****************************************************************************/

#define DSP_PCM_OUT4_REG_adr 0x1027FC0
#define DSP_PCM_OUT4_REG _A_DSP_PCM_OUT4_REG

extern volatile unsigned short _A_DSP_PCM_OUT4_REG;

/****************************************************************************
* DSP_PCM_OUT5_REG
****************************************************************************/

#define DSP_PCM_OUT5_REG_adr 0x1027FC2
#define DSP_PCM_OUT5_REG _A_DSP_PCM_OUT5_REG

extern volatile unsigned short _A_DSP_PCM_OUT5_REG;

/****************************************************************************
* DSP_PCM_IN4_REG
****************************************************************************/

#define DSP_PCM_IN4_REG_adr 0x1027FC4
#define DSP_PCM_IN4_REG _A_DSP_PCM_IN4_REG

extern volatile unsigned short _A_DSP_PCM_IN4_REG;

/****************************************************************************
* DSP_PCM_IN5_REG
****************************************************************************/

#define DSP_PCM_IN5_REG_adr 0x1027FC6
#define DSP_PCM_IN5_REG _A_DSP_PCM_IN5_REG

extern volatile unsigned short _A_DSP_PCM_IN5_REG;

/****************************************************************************
* DSP_CODEC2_IN_REG
****************************************************************************/

#define DSP_CODEC2_IN_REG_adr 0x1027FC8
#define DSP_CODEC2_IN_REG _A_DSP_CODEC2_IN_REG

extern volatile unsigned short _A_DSP_CODEC2_IN_REG;

/****************************************************************************
* DSP_CTRL_REG
****************************************************************************/

#define DSP_CTRL_REG_adr 0x1027FD0
#define DSP_CTRL_REG _A_DSP_CTRL_REG.Value
#define DSP_CTRL_REG_bit _A_DSP_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DIP_DSP_VEC          : 2; // Bit 1-0
    unsigned short DSP_EN               : 1; // Bit 2
    unsigned short DSP_CLK_EN           : 1; // Bit 3
    unsigned short DSP_CR16_INT         : 1; // Bit 4
    unsigned short DSP_PATCH            : 1; // Bit 5
    unsigned short                      : 2; // Bit 7-6
    unsigned short DBG_EN               : 1; // Bit 8
  };
} DSP_CTRL_REG_type __attribute__((aligned(2)));

extern volatile DSP_CTRL_REG_type _A_DSP_CTRL_REG __attribute__((aligned(2)));

#define DSP_CTRL_DIP_DSP_VEC          0x0003 // Bit 1-0
#define DSP_CTRL_DSP_EN               0x0004 // Bit 2
#define DSP_CTRL_DSP_CLK_EN           0x0008 // Bit 3
#define DSP_CTRL_DSP_CR16_INT         0x0010 // Bit 4
#define DSP_CTRL_DSP_PATCH            0x0020 // Bit 5
#define DSP_CTRL_DBG_EN               0x0100 // Bit 8

/****************************************************************************
* DSP_PC_REG
****************************************************************************/

#define DSP_PC_REG_adr 0x1027FD2
#define DSP_PC_REG _A_DSP_PC_REG

extern volatile unsigned short _A_DSP_PC_REG;

/****************************************************************************
* DSP_PC_START_REG
****************************************************************************/

#define DSP_PC_START_REG_adr 0x1027FD4
#define DSP_PC_START_REG _A_DSP_PC_START_REG

extern volatile unsigned short _A_DSP_PC_START_REG;

/****************************************************************************
* DSP_IRQ_START_REG
****************************************************************************/

#define DSP_IRQ_START_REG_adr 0x1027FD6
#define DSP_IRQ_START_REG _A_DSP_IRQ_START_REG.Value
#define DSP_IRQ_START_REG_bit _A_DSP_IRQ_START_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 4; // Bit 3-0
    unsigned short DSP_IRQ_START        : 12; // Bit 15-4
  };
} DSP_IRQ_START_REG_type __attribute__((aligned(2)));

extern volatile DSP_IRQ_START_REG_type _A_DSP_IRQ_START_REG __attribute__((aligned(2)));

#define DSP_IRQ_START_DSP_IRQ_START        0xFFF0 // Bit 15-4

/****************************************************************************
* DSP_INT_REG
****************************************************************************/

#define DSP_INT_REG_adr 0x1027FD8
#define DSP_INT_REG _A_DSP_INT_REG

extern volatile unsigned short _A_DSP_INT_REG;

/****************************************************************************
* DSP_INT_MASK_REG
****************************************************************************/

#define DSP_INT_MASK_REG_adr 0x1027FDA
#define DSP_INT_MASK_REG _A_DSP_INT_MASK_REG

extern volatile unsigned short _A_DSP_INT_MASK_REG;

/****************************************************************************
* DSP_INT_PRIO1_REG
****************************************************************************/

#define DSP_INT_PRIO1_REG_adr 0x1027FDC
#define DSP_INT_PRIO1_REG _A_DSP_INT_PRIO1_REG.Value
#define DSP_INT_PRIO1_REG_bit _A_DSP_INT_PRIO1_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DSP_INT2_PRIO        : 3; // Bit 2-0
    unsigned short                      : 1; // Bit 3
    unsigned short DSP_INT1_PRIO        : 3; // Bit 6-4
    unsigned short                      : 1; // Bit 7
    unsigned short DSP_INT0_PRIO        : 3; // Bit 10-8
  };
} DSP_INT_PRIO1_REG_type __attribute__((aligned(2)));

extern volatile DSP_INT_PRIO1_REG_type _A_DSP_INT_PRIO1_REG __attribute__((aligned(2)));

#define DSP_INT_PRIO1_DSP_INT2_PRIO        0x0007 // Bit 2-0
#define DSP_INT_PRIO1_DSP_INT1_PRIO        0x0070 // Bit 6-4
#define DSP_INT_PRIO1_DSP_INT0_PRIO        0x0700 // Bit 10-8

/****************************************************************************
* DSP_INT_PRIO2_REG
****************************************************************************/

#define DSP_INT_PRIO2_REG_adr 0x1027FDE
#define DSP_INT_PRIO2_REG _A_DSP_INT_PRIO2_REG.Value
#define DSP_INT_PRIO2_REG_bit _A_DSP_INT_PRIO2_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DSP_INT5_PRIO        : 3; // Bit 2-0
    unsigned short                      : 1; // Bit 3
    unsigned short DSP_INT4_PRIO        : 3; // Bit 6-4
    unsigned short                      : 1; // Bit 7
    unsigned short DSP_INT3_PRIO        : 3; // Bit 10-8
  };
} DSP_INT_PRIO2_REG_type __attribute__((aligned(2)));

extern volatile DSP_INT_PRIO2_REG_type _A_DSP_INT_PRIO2_REG __attribute__((aligned(2)));

#define DSP_INT_PRIO2_DSP_INT5_PRIO        0x0007 // Bit 2-0
#define DSP_INT_PRIO2_DSP_INT4_PRIO        0x0070 // Bit 6-4
#define DSP_INT_PRIO2_DSP_INT3_PRIO        0x0700 // Bit 10-8

/****************************************************************************
* DSP_OVERFLOW_REG
****************************************************************************/

#define DSP_OVERFLOW_REG_adr 0x1027FE0
#define DSP_OVERFLOW_REG _A_DSP_OVERFLOW_REG.Value
#define DSP_OVERFLOW_REG_bit _A_DSP_OVERFLOW_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short INT_OVERFLOW         : 6; // Bit 5-0
    unsigned short WTF_OVERFLOW         : 1; // Bit 6
    unsigned short IRQ_OVERFLOW         : 1; // Bit 7
    unsigned short M_INT_OVERFLOW       : 6; // Bit 13-8
    unsigned short M_WTF_OVERFLOW       : 1; // Bit 14
    unsigned short M_IRQ_OVERFLOW       : 1; // Bit 15
  };
} DSP_OVERFLOW_REG_type __attribute__((aligned(2)));

extern volatile DSP_OVERFLOW_REG_type _A_DSP_OVERFLOW_REG __attribute__((aligned(2)));

#define DSP_OVERFLOW_INT_OVERFLOW         0x003F // Bit 5-0
#define DSP_OVERFLOW_WTF_OVERFLOW         0x0040 // Bit 6
#define DSP_OVERFLOW_IRQ_OVERFLOW         0x0080 // Bit 7
#define DSP_OVERFLOW_M_INT_OVERFLOW       0x3F00 // Bit 13-8
#define DSP_OVERFLOW_M_WTF_OVERFLOW       0x4000 // Bit 14
#define DSP_OVERFLOW_M_IRQ_OVERFLOW       0x8000 // Bit 15

/****************************************************************************
* DSP_JTBL_REG
****************************************************************************/

#define DSP_JTBL_REG_adr 0x1027FE2
#define DSP_JTBL_REG _A_DSP_JTBL_REG.Value
#define DSP_JTBL_REG_bit _A_DSP_JTBL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short                      : 9; // Bit 8-0
    unsigned short DSP_JTBL             : 7; // Bit 15-9
  };
} DSP_JTBL_REG_type __attribute__((aligned(2)));

extern volatile DSP_JTBL_REG_type _A_DSP_JTBL_REG __attribute__((aligned(2)));

#define DSP_JTBL_DSP_JTBL             0xFE00 // Bit 15-9

/****************************************************************************
* DSP_AUX_REG
****************************************************************************/

#define DSP_AUX_REG_adr 0x1027FE4
#define DSP_AUX_REG _A_DSP_AUX_REG.Value
#define DSP_AUX_REG_bit _A_DSP_AUX_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short CR16_SHRA            : 1; // Bit 0
  };
} DSP_AUX_REG_type __attribute__((aligned(2)));

extern volatile DSP_AUX_REG_type _A_DSP_AUX_REG __attribute__((aligned(2)));

#define DSP_AUX_CR16_SHRA            0x0001 // Bit 0

/****************************************************************************
* DBG_IREG_REG
****************************************************************************/

#define DBG_IREG_REG_adr 0x1027FF0
#define DBG_IREG_REG _A_DBG_IREG_REG

extern volatile unsigned short _A_DBG_IREG_REG;

/****************************************************************************
* DBG_INOUT_REG_LSW
****************************************************************************/

#define DBG_INOUT_REG_LSW_adr 0x1027FF4
#define DBG_INOUT_REG_LSW _A_DBG_INOUT_REG_LSW

extern volatile unsigned short _A_DBG_INOUT_REG_LSW;

/****************************************************************************
* DBG_INOUT_REG_MSW
****************************************************************************/

#define DBG_INOUT_REG_MSW_adr 0x1027FF6
#define DBG_INOUT_REG_MSW _A_DBG_INOUT_REG_MSW

extern volatile unsigned short _A_DBG_INOUT_REG_MSW;

/****************************************************************************
* DSP_TIMER_REG
****************************************************************************/

#define DSP_TIMER_REG_adr 0x1027FF8
#define DSP_TIMER_REG _A_DSP_TIMER_REG

extern volatile unsigned long _A_DSP_TIMER_REG;

/****************************************************************************
* DSP_TIMER_CTRL_REG
****************************************************************************/

#define DSP_TIMER_CTRL_REG_adr 0x1027FFC
#define DSP_TIMER_CTRL_REG _A_DSP_TIMER_CTRL_REG.Value
#define DSP_TIMER_CTRL_REG_bit _A_DSP_TIMER_CTRL_REG

typedef union
{
  unsigned short Value;
  struct
  {
    unsigned short DSP_TIM_CTRL         : 1; // Bit 0
    unsigned short DSP_TIM_STOP         : 1; // Bit 1
    unsigned short DSP_TIM_MODE         : 2; // Bit 3-2
    unsigned short DSP_TIM_MEM          : 1; // Bit 4
    unsigned short DSP_TIM_BRIDGE       : 1; // Bit 5
    unsigned short DSP_TIM_JMP          : 1; // Bit 6
    unsigned short DSP_TIM_PATCH        : 1; // Bit 7
  };
} DSP_TIMER_CTRL_REG_type __attribute__((aligned(2)));

extern volatile DSP_TIMER_CTRL_REG_type _A_DSP_TIMER_CTRL_REG __attribute__((aligned(2)));

#define DSP_TIMER_CTRL_DSP_TIM_CTRL         0x0001 // Bit 0
#define DSP_TIMER_CTRL_DSP_TIM_STOP         0x0002 // Bit 1
#define DSP_TIMER_CTRL_DSP_TIM_MODE         0x000C // Bit 3-2
#define DSP_TIMER_CTRL_DSP_TIM_MEM          0x0010 // Bit 4
#define DSP_TIMER_CTRL_DSP_TIM_BRIDGE       0x0020 // Bit 5
#define DSP_TIMER_CTRL_DSP_TIM_JMP          0x0040 // Bit 6
#define DSP_TIMER_CTRL_DSP_TIM_PATCH        0x0080 // Bit 7

#endif

#endif

