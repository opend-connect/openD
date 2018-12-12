/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
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

#ifndef KEY_MESSAGE_H
#define KEY_MESSAGE_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Core/RtxCore.h>
#include <ProjCfg.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/
typedef rsuint8 KeyIdType;
typedef rsuint8 KeyboardKeyIndexType;
typedef rsuint8 KeyboardKeyStateStoreType;

typedef enum
{
   HW_DKEY3=0,
   HW_DKEY4,
   HW_MKEY1,
   HW_MKEY2,
   HW_MKEY3,
   HW_MKEY4,
   HW_MKEY5,
   HW_MKEY6,
   HW_MKEY7,
   HW_MKEY8,
   HWKEY_MAX,
} RSENUM8(HW_KEY_ENUM_TYPE);

#define HWKEY_FIRST HW_DKEY3

typedef enum
{
  KEY_SCAN_LEVEL_1,
  KEY_SCAN_LEVEL_2,
  KEY_SCAN_LEVEL_3,
  KEY_SCAN_MAX_LEVEL,
} RSENUM8(KEY_SCAN_LEVEL_TYPE);

#define KEY_SCAN_TIME              5*RS_T1MS
#define KEY_SCAN_DEBOUNCE_CYCLE    6

/****************************************************************************
*                                Key definitions
****************************************************************************/
#define KEY_NULL              0x00

//Cvm Mainboard key defines
#define KEY_HOOK              0xF2 //F2
#define KEY_REG               0xF3 //F3
#define KEY_VOL               0xF5 //F5
#define KEY_DEFAULT           0xF6 //F6

//CvmCon Pc Options key defines
//#define KEY_F1       0xF1 //F7 (HELP)
//#define KEY_F7       0xF7 //F7 (GET_STACK_INFO)
//#define KEY_F8       0xF8 //F8 (GET_OTP_INFO)
//#define KEY_F9       0xF9 //F9 (GET_IMAGECFG)
//#define KEY_F11      0xFB //F11 (TOGGLE_STACK)
//#define KEY_F12      0xFC //F12 (TOGGLE COLA)

//Cvm Daughterboard key defines
#define KEY_1        0x31 //1
#define KEY_2        0x32 //2
#define KEY_3        0x33 //3
#define KEY_4        0x34 //4
#define KEY_5        0x35 //5
#define KEY_6        0x36 //6
#define KEY_7        0x37 //7
#define KEY_8        0x38 //8

#define KEY_MODE     KEY_REG


#define KEY_MESSAGE_REQ_PAGE     0x01 //F2 (diabled)
#define KEY_MESSAGE_REQ_REG      0x02 //F3
#define KEY_MESSAGE_REQ_DEREG    0x03 //F4
#define KEY_MESSAGE_REQ_DEFAULT  0x04 //F6

#define KEY_MESSAGE_REQ_SET_AC   0x05

#define KEY_MESSAGE_REQ_MUTE     0x06
#define KEY_MESSAGE_REQ_UNMUTE   0x07


/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef enum
{
  KeyboardKey_Up = 0,
  KeyboardKey_Down = 1,
  KeyboardKey_StateMax
} RSENUM8(KeyboardKeyStateType);


typedef struct
{
  KEY_SCAN_LEVEL_TYPE   KeyScanLevel;
  KeyIdType             Keys[KEY_SCAN_MAX_LEVEL];
} KeyScanCtrlTableType;


/****************************************************************************
*                           Global variables/const
****************************************************************************/


/****************************************************************************
*                             Function prototypes
****************************************************************************/
void KeyScannerInit(void);
void KeyboardScanKeys(void);


#endif // #ifndef KEY_MESSAGE_H