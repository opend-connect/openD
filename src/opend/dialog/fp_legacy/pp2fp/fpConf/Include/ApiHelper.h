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

extern void RcHeapFreeEx(void* Block, RcHeapFlagsType Flags);

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define LS_NO_LINES 4
#define NO_HANDSETS (7+1)
#define NO_ADPCM 4

#define LS_LINE_INVALID 0xFF

#define PT_CMD_NVS_DEFAULT 0x0102
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

/*! This command is used to control the three LED?s (LED1, LED3, and LED4)
   on the CVM. The CVM can store on command sequence for each of the LED?s. */
typedef struct ApiFpSetLedReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_SET_LED_REQ = 0x400C */
  ApiLedType LED;                       /*!< The LED for which this command applies. */
  rsuint8 CommandsCount;                /*!< The number of LED commands in the
                                           Commands[] parameter. */
  ApiLedCommandType Commands[1];        /*!< NoCommands number of LED commands. */
} ApiFpSetLedReqType;

typedef struct
{
  rsuint16 SessionId; 
  rsuint16 EntryIdentifier;
  rsuint16 NoOfEntries;
  rsuint8 CurrentEntry;  
}LasSessionDataType;

/*! This type is used to store all CLIP related information. */
typedef enum RSENUMTAG(ApiRequestedCodeListType)
{
  CommonCodecListFromLocation = 0x00, /*!< This codec list is saved in Eeprom during
                                         registration/location */
  LastCommonCodecList         = 0x01, /*!< Latest received codec from HS */
  CodecForCurrentCall         = 0x02  /*!< Used codec for current call, if no active
                                         call, the codec from last call is received. */
} RSENUM8(ApiRequestedCodeListType);

typedef enum
{
  HS_NOT_REGISTERED,
  HS_OUT_OF_RANGE,
  F00_NULL,
  F01_CALL_INITIATED,
  F02_OVERLAP_SENDING,
  F03_CALL_PROCEEDING,
  F04_CALL_DELIVERED,
  F06_CALL_PRESENT,
  F07_CALL_RECEIVED,
  F10_ACTIVE,
  F11_CONFERENCE,         //KTS
  F19_RELEASE_PENDING,
  CODEC_NEGOTIATION_FROM_HS,
  CODEC_NEGOTIATION_FROM_LINE,
  CODEC_NEGOTIATION_IN_SETUP,
  HANDSET_LOCATE,
  HEADSET_INTERCEPT,
  CALL_STATE_MAX
} CallStateType;

typedef struct CallStateInfoType
{
  rsuint8 Present        : 1;
  rsuint8 Connected2Line : 1;
  rsuint8 UnUsed         : 6;
  ApiCcCallClassType CallClass;
  rsuint8 DestinationId;
  CallStateType State;
  rsuint8 LineId;
  ApiCcBasicServiceType BasicService; // used for internal call only
  ApiSystemCallIdType ApiSystemCallId;
  ApiLineIdType ApiLineId;
  rsuint8 ProposedCodecListLength;
  ApiCodecListType *ProposedCodecListPtr;
  ApiCallReferenceType CallReference;
} CallStateInfoType;


typedef struct ApiFpGetCodecListReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_GET_CODEC_LIST_REQ = 0x4016 */
  ApiTerminalIdType TerminalId;           /*!< Indicates which HS. */
  ApiRequestedCodeListType ApiRequestCodeList; /*!< Indicates which codec list to
                                                   request. */
} ApiFpGetCodecListReqType;

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
* FUNCTION:      GetHsFromCallReference
* DESCRIPTION:   Returns the HS Id of the Call identified by CID
*
****************************************************************************/
unsigned char GetHsFromCallReference (ApiCallReferenceType CID);
/****************************************************************************
* FUNCTION:      FreeHostCallReference
* DESCRIPTION:   Frees a unique CallReference (Host) id of 4-bits length
*				HostCallReference 16-bit is used as a bit-mask of allocated id's
****************************************************************************/
unsigned char FreeHostCallReference (ApiCallReferenceType CID);
/****************************************************************************
* FUNCTION:      AllocateHostCallReference
* DESCRIPTION:   Allocates a unique CallReference (Host) id of 4-bits length.
*				 HostCallReference 16-bit is used as a bit-mask of allocated id's
****************************************************************************/
unsigned char AllocateHostCallReference ();
/****************************************************************************
* FUNCTION:      SendApiFpSetLedReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_LED_REQ = 0x400C
****************************************************************************/
void SendApiFpSetLedReq ( RosTaskIdType Src,
                          ApiLedType LED,                    /*!< The LED for which this
                                                                command applies. */
                          rsuint8 CommandsCount,             /*!< The number of LED
                                                                commands in the Commands[]
                                                                parameter. */
                          ApiLedCommandType Commands[1]);    /*!< NoCommands number of
                                                                LED commands. */

/****************************************************************************
* FUNCTION:      RequestLasEntry
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_LED_REQ = 0x400C
****************************************************************************/
void RequestLasEntry(rsuint16 StartIndex, rsuint16 SessionId, rsuint8 NumberOfEntries, rsuint8 NoOfIdentifiers, ApiIeType *IdentifierPtr, ApiLasListIdType ListId);                                                                

/****************************************************************************
*  FUNCTION:       ApiBuildInfoElement
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to allocate and append an info
                   element to a memory block holding previously allocated info
                   elements. This function reallocates the info element block
                   wit a new size that is the size of the existing block + the
                   size of the new info element. The IeData is copied to the
                   tail of the new block allocated.
****************************************************************************/
void ApiBuildInfoElement(ApiInfoElementType **IeBlockPtr,    /*!< Pointer to pointer
                                                                holding the address of the
                                                                memory block that the info
                                                                element allocated should be
                                                                appended to when this
                                                                function is called and
                                                                pointer to new block when
                                                                the function returns.
                                                                *IeBlockPtr is set to NULL
                                                                if this function fails to
                                                                allocate memory for the new
                                                                information element. */
                         rsuint16 *IeBlockLengthPtr,         /*!< Pointer to variable
                                                                holding the current size of
                                                                the memory block used to
                                                                store the info elements in
                                                                when the function is called
                                                                and the new size when the
                                                                function returns. */
                         ApiIeType Ie,                       /*!< Info Element
                                                                identification. */
                         rsuint8 IeLength,                   /*!< The length in bytes of
                                                                the info element that should
                                                                be appended to the info
                                                                element memory block
                                                                (**IeBlockPtr). */
                         rsuint8 *IeData);                   /*!< Pointer to the info
                                                                element data that should be
                                                                appended. */

/****************************************************************************
*  FUNCTION:       ApiFreeInfoElement
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to free an info element memory
                   block allocate by ApiBuildInfoElement().
****************************************************************************/
void ApiFreeInfoElement(ApiInfoElementType **IeBlockPtr);    /*!< Pointer to pointer
                                                                holding the address of the
                                                                memory block that should be
                                                                freed. */

/****************************************************************************
*  FUNCTION:       ApiGetInfoElement
*
*  RETURNS :       Pointer to the info element found in the info element
                   block or NULL if the info element searched for is not found
                   in the info element block.
*
*  DESCRIPTION:    This function is used to find a specific info element in
                   a memory block holding one or more info elements.
****************************************************************************/
ApiInfoElementType* ApiGetInfoElement(ApiInfoElementType *IeBlockPtr,
                                                             /*!< Pointer to the info
                                                                element block that holds one
                                                                or more info elements */
                                      rsuint16 IeBlockLength,
                                                             /*!< The size of the info
                                                                element block. */
                                      ApiIeType Ie);         /*!< Id of the info element
                                                                searched after. */

/****************************************************************************
*  FUNCTION:       ApiGetNextInfoElement
*
*  RETURNS :       Pointer to the next info element following IePtr or NULL
                   if the end of the info element block is reached.
*
*  DESCRIPTION:    This function is used to get the next info element after
                   IePtr in an info element block. 
****************************************************************************/
ApiInfoElementType* ApiGetNextInfoElement(ApiInfoElementType *IeBlockPtr,
                                                             /*!< Pointer to the info
                                                                element block that holds one
                                                                or more info elements */
                                          rsuint16 IeBlockLength,
                                                             /*!< The size of the info
                                                                element block. */
                                          ApiInfoElementType *IePtr);
                                                             /*!< The pointer to the
                                                                info element for which the
                                                                next info element is
                                                                requested. The first info
                                                                element is returned if IePtr
                                                                is NULL. */

/****************************************************************************
*  FUNCTION:       ApiRemoveInfoElement
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to Remove an info element from an
                   info element block. 
****************************************************************************/
void ApiRemoveInfoElement(ApiInfoElementType **IeBlockPtr,   /*!< Pointer to pointer to
                                                                the info element block that
                                                                holds the info elements
                                                                which is to be removed */
                          rsuint16 *IeBlockLength,           /*!< Pointer to the size of
                                                                the info element block. */
                          ApiIeType Ie);                     /*!< Id of the info element
                                                                which is to be removed. */

/****************************************************************************
* FUNCTION:      SendApiFpGetCodecListReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_CODEC_LIST_REQ = 0x4016
****************************************************************************/
void SendApiFpGetCodecListReq ( RosTaskIdType Src,
                                ApiTerminalIdType TerminalId,  /*!< Indicates which HS. */
                                ApiRequestedCodeListType ApiRequestCodeList);
                                                             /*!< Indicates which codec
                                                                list to request. */
/****************************************************************************
*  FUNCTION:       ApiGetCodecListElement
*
*  RETURNS :       Pointer to the codec element found in the codec list or
                   NULL if the codec element searched for is not found in the
                   codec list.
*
*  DESCRIPTION:    This function is used to find a specific codec element
                   in a codec list holding one or more codec elements.
****************************************************************************/
ApiCodecInfoType* ApiGetCodecListElement(ApiCodecListType *CodecListPtr,
                                                             /*!< Pointer to the codec
                                                                list, in where the codec
                                                                element should be found */
                                         ApiCodecType Codec);
                                                             /*!< Codec type that should
                                                                be fetched. */
/****************************************************************************
*  FUNCTION:       ApiGetNextCodecListElement
*
*  RETURNS :       Pointer to the next Codec element following pCI or NULL
                   if the end of the codec list is reached.
*
*  DESCRIPTION:    This function is used to get the next codec element
                   after pCI in a codec list. 
****************************************************************************/
ApiCodecInfoType* ApiGetNextCodecListElement(ApiCodecListType *CodecListPtr,
                                                             /*!< Pointer to the codec
                                                                list that holds one or more
                                                                codec list elements */
                                             ApiCodecInfoType *pCI);
                                                             /*!< The pointer to the
                                                                codec element for which the
                                                                next codec element is
                                                                requested. The first codec
                                                                element is returned if pCI
                                                                is NULL. */

/***************************************************************************
*  FUNCTION: ApiPutCodecListInIe
*  INPUTS  : Pointer to block in memory holding a codec list and a pointer to 
*            a block in memory holding infoelements, and a pointer to the length 
*            of the infoelements
*  OUTPUTS : none
*  ------------------------------------------------------------------------- 
*  DESCRIPTION:
*     This function puts a codec list in a infoelement, if the infoelementblock 
*     is NULL a new block is allocated
*
*****************************************************************************/
void ApiPutCodecListInIe(ApiCodecListType *CodecListPtr, 
                         ApiInfoElementType **IeBlockPtr, 
                         rsuint16 *IeBlockLengthPtr);                                                                
                         
#endif //API_HELPER_H

