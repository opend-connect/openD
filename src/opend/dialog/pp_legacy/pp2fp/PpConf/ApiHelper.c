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
/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include "CfState.h"
#include "ApiHelper.h"
// #include "LineCtrl.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

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
#ifndef NATALIE_V11
/****************************************************************************
* FUNCTION:      SendApiProdTestReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PROD_TEST_REQ
****************************************************************************/
void SendApiProdTestReq ( RosTaskIdType Src,
                          rsuint16 Opcode,
                          rsuint16 ParameterLength,
                          rsuint8 Parameters [1])
{
  ApiProdTestReqType*
  m = (ApiProdTestReqType*)RosMailAllocate( Src, APIPRODTEST_TASK,(rsuint16)(sizeof(ApiProdTestReqType) - 1 +
                                                                  ParameterLength));

  m->Primitive = API_PROD_TEST_REQ;
  m->Opcode = Opcode;
  m->ParameterLength = ParameterLength;
  if (Parameters )
  {
    memcpy(m->Parameters ,Parameters ,ParameterLength);
  }
  RosMailDeliver((RosMailType *)m);
}
#endif

/****************************************************************************
* FUNCTION:      ApiBuildInfoElement
* DESCRIPTION:
****************************************************************************/
void ApiBuildInfoElement(ApiInfoElementType **IeBlockPtr,
                         rsuint16 *IeBlockLengthPtr,
                         ApiIeType Ie,
                         rsuint8 IeLength,
                         rsuint8 *IeData)
{
  rsuint16 newLength = *IeBlockLengthPtr + RSOFFSETOF(ApiInfoElementType, IeData) + IeLength;

  // Allocate / reallocate a heap block to store (append) the info elemte in.
  ApiInfoElementType *p = RcHeapReallocEx(*IeBlockPtr, newLength, RHF_NULL_ON_FULL);

  if (p == NULL)
  {
    // We failed to get e new block.
    // We free the old and return with *IeBlockPtr == NULL.
    ApiFreeInfoElement(IeBlockPtr);
    *IeBlockLengthPtr = 0;
  }
  else
  {
    // Update *IeBlockPointer with the address of the new block
    *IeBlockPtr = p;
    // Append the new info element to the allocated block
    p = (ApiInfoElementType*)(((rsuint8*)p) + *IeBlockLengthPtr); // p now points to the first byte of the new info element
    p->Ie = Ie;
    p->IeLength = IeLength;
    memcpy (p->IeData, IeData, IeLength);
    // Update *IeBlockLengthPtr with the new block length
    *IeBlockLengthPtr = newLength;
  }
}


/****************************************************************************
* FUNCTION:      ApiGetNextInfoElement
* DESCRIPTION:
****************************************************************************/
ApiInfoElementType* ApiGetNextInfoElement(ApiInfoElementType *IeBlockPtr,
                                          rsuint16 IeBlockLength,
                                          ApiInfoElementType *IePtr)
{
  ApiInfoElementType *pEnd = (ApiInfoElementType*)((rsuint8*)IeBlockPtr + IeBlockLength);

  if (IePtr == NULL)
  {
    // return the first info element
    IePtr = IeBlockPtr;
  }
  else
  {
    // calc the address of the next info element
    IePtr = (ApiInfoElementType*)((rsuint8*)IePtr + RSOFFSETOF(ApiInfoElementType, IeData) + IePtr->IeLength);
  }

  if (IePtr < pEnd)
  {
    return IePtr; // return the pointer to the next info element
  }
  return NULL; // return NULL to indicate that we have reached the end
}

/****************************************************************************
* FUNCTION:      ApiGetInfoElement
* DESCRIPTION:
****************************************************************************/
ApiInfoElementType* ApiGetInfoElement(ApiInfoElementType *IeBlockPtr,
                                      rsuint16 IeBlockLength,
                                      ApiIeType Ie)
{
  ApiInfoElementType *pIe = NULL;

  #if defined RSX && defined LOG_BIG_ENDIAN_TARGET
  Ie = RS_SWAPBYTES_16(Ie);
  #endif

  while (NULL != (pIe = ApiGetNextInfoElement(IeBlockPtr, IeBlockLength, pIe)))
  {
    if (pIe->Ie == Ie)
    {
      return pIe; // return the ponter to the info element found
    }
  }
  return NULL; // return NULL to indicate that we did not find an info element wirh the IE specified
}

/****************************************************************************
* FUNCTION:      ApiFreeInfoElement
* DESCRIPTION:
****************************************************************************/
void ApiFreeInfoElement(ApiInfoElementType **IeBlockPtr)
{
 if (*IeBlockPtr)
 {
 #ifdef WIN32_SIM
   RcHeapFree(*IeBlockPtr);
 #else
   RcHeapFreeEx((void*)*IeBlockPtr, RHF_NULL_ON_FULL);
 #endif
   *IeBlockPtr = NULL;
 }
}

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
                         rsuint16 *IeBlockLengthPtr)
{
  if (CodecListPtr != NULL)
  {
    ApiBuildInfoElement(IeBlockPtr,
                        IeBlockLengthPtr,
                        API_IE_CODEC_LIST,
                        RSOFFSETOF(ApiCodecListType, Codec) + CodecListPtr->NoOfCodecs * sizeof(ApiCodecInfoType),
                        (rsuint8 *)CodecListPtr);
  }
}


/***************************************************************************
*  FUNCTION: ApiBuildCodecListHeader
*  INPUTS  : Pointer to block in memory holding a codec list, if NULL a
*            place is allocated. And the negotiationIndicator indication,
*            if negotiation is possible or not
*  OUTPUTS : none
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*   This function builds a codec list headed, inorder to biuld a compleate
*   codeclist this function should be call followed by ApiAddToCodecList
*   in order to added actual codec to the CodecList
*
*****************************************************************************/
void ApiBuildCodecListHeader(ApiCodecListType **CodecListPtr, ApiNegotiationIndicatorType  NegotiationIndicator)
{
  ApiCodecListType *p = RcHeapReallocEx(*CodecListPtr, sizeof(ApiCodecListType), RHF_NULL_ON_FULL);  //Klocwork

  if (p == NULL)
  {
    // We failed to get e new block.
    // We free the old and return with *CodecListPtr == NULL.
    ApiFreeCodecList(CodecListPtr);
  }
  else
  {
    p->NegotiationIndicator = NegotiationIndicator;
    p->NoOfCodecs = 0;
    *CodecListPtr = p;
  }
}

/***************************************************************************
*  FUNCTION: ApiAddToCodecList
*  INPUTS  : Pointer to block in memory holding a codec list, and the codec
*            that are to be appended to the codec list
*  OUTPUTS : none
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*   This function appends a codec to an existing codec list, the number of
*   codecs in the codec list is incremented. ApiBuildCodecListHeader should
*   be used first inorder to build an emty codec list
*
*****************************************************************************/
void ApiAddToCodecList(ApiCodecListType **CodecListPtr, ApiCodecInfoType *CodecInfo)
{
  ApiCodecListType *p;  //Klocwork
  rsuint16 newLength;

  if (*CodecListPtr == NULL)
  {
    //The codeclist does not contain a header, use ApiBuildCodecListHeader, before adding to the codec list
    return;
  }

  newLength = (rsuint16) (sizeof(ApiCodecListType) + (*CodecListPtr)->NoOfCodecs*sizeof(ApiCodecInfoType));  //Klocwork

  // Reallocate a heap block to store (append) the info elemte in.
  p = RcHeapReallocEx(*CodecListPtr, newLength, RHF_NULL_ON_FULL);

  if (p == NULL)
  {
    // We failed to get e new block.
    // We free the old and return with *CodecListPtr == NULL.
    ApiFreeCodecList(CodecListPtr);
  }
  else
  {
    ApiCodecInfoType *tempCodec;  //Klocwork
    // Update *CodecListPtr with the address of the new block
    *CodecListPtr = p;
    // Append the new info element to the allocated block
    tempCodec = (ApiCodecInfoType*)(((rsuint8*)p) + RSOFFSETOF(ApiCodecListType, Codec) + (*CodecListPtr)->NoOfCodecs*sizeof(ApiCodecInfoType)); // p now points to the first byte of the new info element
    tempCodec->Codec          = CodecInfo->Codec;
    tempCodec->MacDlcService  = CodecInfo->MacDlcService;
    tempCodec->CplaneRouting  = CodecInfo->CplaneRouting;
    tempCodec->SlotSize       = CodecInfo->SlotSize;
    //Increment the number of codecs in the codec list
    (*CodecListPtr)->NoOfCodecs++;
  }
}

/***************************************************************************
*  FUNCTION: ApiFreeCodecList
*  INPUTS  : Pointer to block in memory holding a codec list
*  OUTPUTS : none
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*   the function frees the Codeclist allocated by ApiBuildCodecListHeader.
*   This function shall always be called if ApiBuildCodecListHeader has be
*   called, inorder to free the block of memory used by the codec list
*
*****************************************************************************/
void ApiFreeCodecList(ApiCodecListType **CodecListPtr)
{
  if (*CodecListPtr)
  {
    RcHeapFreeEx((void*)*CodecListPtr, RHF_NULL_ON_FULL);
    *CodecListPtr = NULL;
  }
}

// End of file.

