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
#ifndef API_HELPER_H
#define API_HELPER_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include <Phoenix/Api/Las/ApiLas.h>
#include "LedCtrl.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define PT_CMD_NVS_DEFAULT 0x0102

#define API_PP2PP_TASK API_TASK

//temperarily defines the primitives related to PP2PP 

#define AUDIO_INFO_ind                 0x00A0
  
#define API_PP2PP_ENTER_REQ            0x4920
#define API_PP2PP_ENTER_CFM            0x4921
#define API_PP2PP_EXIT_REQ             0x4922
#define API_PP2PP_EXIT_CFM             0x4923
#define API_PP2PP_ENTER_FP_MODE_REG    0x4924
#define API_PP2PP_ENTER_FP_MODE_CFM    0x4925
#define API_PP2PP_SETUP_REQ            0x4926
#define API_PP2PP_CONNECT_IND          0x4927
#define API_PP2PP_SETUP_IND            0x4928
#define API_PP2PP_CONNECT_REQ          0x4929
#define API_PP2PP_CONNECT_CFM          0x492A
#define API_PP2PP_RELEASE_REQ          0x492B
#define API_PP2PP_RELEASE_CFM          0x492C
#define API_PP2PP_RELEASE_IND          0x492D

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef enum
{
   DC8_NULL,            DC8_NOTDEF_1,        DC8_HOME,            DC8_END,             /*   0..3   */
   DC8_NOTDEF_4,        DC8_DIAL_PAUSE,      DC8_TAB_FORWARD,     DC8_TAB_BACKWARD,    /*   4..7   */
   DC8_BACKWARD,        DC8_FORWARD,         DC8_DOWN,            DC8_UP,              /*   8..11  */
   DC8_CLEAR_DISPLAY,   DC8_CR,              DC8_FLASH_OFF,       DC8_FLASH_ON,        /*  12..15  */
   DC8_NOTDEF_10,       DC8_XON,             DC8_PULSE,           DC8_XOFF,            /*  16..19  */
   DC8_DTMF_FINITE,     DC8_REG_RECALL,      DC8_DTMF_INFINITE,   DC8_INTERNAL_CALL,   /*  20..23  */
   DC8_SERVICE,         DC8_CLEAR_EOD,       DC8_CLEAR_EOL,       DC8_ESC,             /*  24..27  */
   DC8_SUP_SERVICE,     DC8_NOTDEF_1D,       DC8_NOTDEF_1E,       DC8_NOTDEF_1F,       /*  28..31  */
   IA5_SPACE,           IA5_EXCLAMATION,     IA5_QUOTATION,       IA5_NUMBER,          /*  32..35  */
   IA5_DOLLAR,          IA5_PERCENT,         IA5_AMPERSAND,       IA5_APOSTROPHE,      /*  36..39  */
   IA5_L_PARENTESIS,    IA5_R_PARENTESIS,    IA5_ASTERISK,        IA5_PLUS_SIGN,       /*  40..43  */
   IA5_COMMA,           IA5_HYPHEN,          IA5_FULL_STOP,       IA5_SOLIDUS,         /*  44..47  */
   IA5_DIGIT_0,         IA5_DIGIT_1,         IA5_DIGIT_2,         IA5_DIGIT_3,         /*  48..51  */
   IA5_DIGIT_4,         IA5_DIGIT_5,         IA5_DIGIT_6,         IA5_DIGIT_7,         /*  52..55  */
   IA5_DIGIT_8,         IA5_DIGIT_9,         IA5_COLON,           IA5_SEMICOLON,       /*  56..59  */
   IA5_LESS_THAN,       IA5_EQUAL,           IA5_GREATER_THAN,    IA5_QUESTION_MARK,   /*  60..63  */
   IA5_AT,              IA5_LETTER_A,        IA5_LETTER_B,        IA5_LETTER_C,        /*  64..67  */
   IA5_LETTER_D,        IA5_LETTER_E,        IA5_LETTER_F,        IA5_LETTER_G,        /*  68..71  */
   IA5_LETTER_H,        IA5_LETTER_I,        IA5_LETTER_J,        IA5_LETTER_K,        /*  72..75  */
   IA5_LETTER_L,        IA5_LETTER_M,        IA5_LETTER_N,        IA5_LETTER_O,        /*  76..79  */
   IA5_LETTER_P,        IA5_LETTER_Q,        IA5_LETTER_R,        IA5_LETTER_S,        /*  80..83  */
   IA5_LETTER_T,        IA5_LETTER_U,        IA5_LETTER_V,        IA5_LETTER_W,        /*  84..87  */
   IA5_LETTER_X,        IA5_LETTER_Y,        IA5_LETTER_Z,        IA5_L_SQUAREBRACKET, /*  88..91  */
   IA5_REV_SOLIDUS,     IA5_R_SQUAREBRACKET, IA5_FLEX_ACCENT,     IA5_UNDERLINE,       /*  92..95  */
   IA5_GRAVE_ACCENT,    IA5_LETTER_a,        IA5_LETTER_b,        IA5_LETTER_c,        /*  96..99  */
   IA5_LETTER_d,        IA5_LETTER_e,        IA5_LETTER_f,        IA5_LETTER_g,        /* 100..103 */
   IA5_LETTER_h,        IA5_LETTER_i,        IA5_LETTER_j,        IA5_LETTER_k,        /* 104..107 */
   IA5_LETTER_l,        IA5_LETTER_m,        IA5_LETTER_n,        IA5_LETTER_o,        /* 108..111 */
   IA5_LETTER_p,        IA5_LETTER_q,        IA5_LETTER_r,        IA5_LETTER_s,        /* 112..115 */
   IA5_LETTER_t,        IA5_LETTER_u,        IA5_LETTER_v,        IA5_LETTER_w,        /* 116..119 */
   IA5_LETTER_x,        IA5_LETTER_y,        IA5_LETTER_z,        IA5_L_CURLYBRACKET,  /* 120..123 */
   IA5_VERTICAL_LINE,   IA5_R_CURLYBRACKET,  IA5_TILDE,           IA5_DELETE           /* 124..127 */
} RSENUM8(eIeDect8BitChars); /* Section D.2 & ITU T.50 table 5. */

typedef struct ApiPp2ppEnterReqType
{
  RosPrimitiveType Primitive;
  rsuint16         wGroupId;
  rsuint8          bHsId;
} ApiPp2ppEnterReqType;

typedef struct ApiPp2ppSetupReqType
{
  RosPrimitiveType Primitive;
  rsuint8          bDestHsId;
} ApiPp2ppSetupReqType;

typedef struct ApiPp2ppEnterFpModeReqType
{
  RosPrimitiveType Primitive;
} ApiPp2ppEnterFpModeReqType;

typedef struct ApiPp2ppConnectReqType
{
  RosPrimitiveType Primitive;
} ApiPp2ppConnectReqType;

typedef struct ApiPp2ppExitReqType
{
  RosPrimitiveType Primitive;
} ApiPp2ppExitReqType;

typedef struct ApiPp2ppReleaseReqType
{
  RosPrimitiveType Primitive;
} ApiPp2ppReleaseReqType;

/*! This mail is used as an indication for incoming call from other Pp */
typedef struct ApiPp2ppSetupIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP2PP_SETUP_IND = 0x4928 */
  rsuint8 bHandsetId;                   /*!< The HandetId is used by the PP when it
                                           initiates a PP-to-PP call by starting to transmit
                                           a dummy
                                           bearer. It will also be used as a portable
                                           directory number when the PP is paged in a
                                           PP-to-PP mode. It is a 2 digit decimal number
                                           coded in the same format as the GroupId and may
                                           be entered via the keypad or by other means, 
                                           (range: 01 to 99). */
} ApiPp2ppSetupIndType;

/****************************************************************************
*                            Global variables/const
****************************************************************************/

/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
/****************************************************************************
* FUNCTION:      SendApiProdTestReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PROD_TEST_REQ
****************************************************************************/
extern void SendApiProdTestReq ( RosTaskIdType Src,
                                 rsuint16 Opcode,
                                 rsuint16 ParameterLength,
                                 rsuint8 Parameters [1]);

/****************************************************************************
* FUNCTION:      RcHeapFreeEx
* DESCRIPTION:
****************************************************************************/
extern void RcHeapFreeEx(void* Block, RcHeapFlagsType Flags);

extern void SendApiPp2ppEnterReq( RosTaskIdType Src, rsuint16 wGroupId, rsuint8 bHsId);
extern void SendApiPp2ppSetupReq( RosTaskIdType Src, rsuint8 bDestHsId);
extern void SendApiPp2ppEnterFpModeReq( RosTaskIdType Src );
extern void SendApiPp2ppConnectReq( RosTaskIdType Src );
extern void SendApiPp2ppExitReq( RosTaskIdType Src );
extern void SendApiPp2ppReleaseReq( RosTaskIdType Src );
#endif //API_HELPER_H


