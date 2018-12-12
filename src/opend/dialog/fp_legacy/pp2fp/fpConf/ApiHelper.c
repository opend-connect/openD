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
#include "CallCtrl.h"
#include "LineCtrl.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/
unsigned short HostCallReference=0;
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
* FUNCTION:      FreeHostCallReference
* DESCRIPTION:   Frees a unique CallReference (Host) id of 4-bits length
*				HostCallReference 16-bit is used as a bit-mask of allocated id's
****************************************************************************/
unsigned char FreeHostCallReference (ApiCallReferenceType CID){
	HostCallReference &= ~(1 << (CID.Instance.Host));
	return 0;
}

/****************************************************************************
* FUNCTION:      AllocateHostCallReference
* DESCRIPTION:   Allocates a unique CallReference (Host) id of 4-bits length.
*				 HostCallReference 16-bit is used as a bit-mask of allocated id's
****************************************************************************/
unsigned char AllocateHostCallReference (){
	unsigned char i;
	for (i=1; i<=0x0f; i++){
		if((HostCallReference & (1<<i)) == 0 ){
			HostCallReference |= 1<<i;
			return(i);
		}
	}
	return 0;
}
/****************************************************************************
* FUNCTION:      GetHsFromCallReference
* DESCRIPTION:   Returns the HS Id of the Call identified by CID
*
****************************************************************************/
unsigned char GetHsFromCallReference (ApiCallReferenceType CID){
	unsigned char i;
	for (i=1; i<NO_HANDSETS; i++){
		if(CallState[i].CallReference.Instance.Host == CID.Instance.Host){
			return(i);
		}
	}
	return 0;
}
#ifndef NATALIE_V11
/****************************************************************************
* FUNCTION:      SendApiFpSetLedReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_LED_REQ
****************************************************************************/
void SendApiFpSetLedReq ( RosTaskIdType Src,
                          ApiLedType LED,
                          rsuint8 CommandsCount,
                          ApiLedCommandType Commands[1])
{
  ApiFpSetLedReqType*
  m = (ApiFpSetLedReqType*)RosMailAllocate( Src, APIPROJECT_TASK,(rsuint16)(sizeof(ApiFpSetLedReqType) - sizeof(ApiLedCommandType) +
                                                                   sizeof(ApiLedCommandType)*CommandsCount));
  m->Primitive = API_FP_SET_LED_REQ;
  m->LED = LED;
  m->CommandsCount = CommandsCount;
  memcpy(m->Commands,Commands,sizeof(ApiLedCommandType)*CommandsCount);
  RosMailDeliver((RosMailType *)m);
}
#endif
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
* FUNCTION:      SendApiFpGetCodecListReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_CODEC_LIST_REQ
****************************************************************************/
#ifdef NATALIE_V11
//void SendApiFpGetCodecListReq ( RosTaskIdType Src,
//                                ApiTerminalIdType TerminalId,
//                                ApiRequestedCodeListType ApiRequestCodeList)
//{
//  ApiFpGetCodecListReqType*
//  m = (ApiFpGetCodecListReqType*)RosMailAllocate( Src, APIPROJECT_TASK,(rsuint16)(sizeof(ApiFpGetCodecListReqType)));
//
//  m->Primitive = API_FP_GET_CODEC_LIST_REQ;
//  m->TerminalId = TerminalId;
//  m->ApiRequestCodeList = ApiRequestCodeList;
//  RosMailDeliver((RosMailType *)m);
//}

#else
void SendApiFpGetCodecListReq ( RosTaskIdType Src,
                                ApiHandsetIdType HandsetId,
                                ApiRequestedCodeListType ApiRequestCodeList)
{
  ApiFpGetCodecListReqType*
  m = (ApiFpGetCodecListReqType*)RosMailAllocate( Src, APIPROJECT_TASK,(rsuint16)(sizeof(ApiFpGetCodecListReqType)));

  m->Primitive = API_FP_GET_CODEC_LIST_REQ;
  m->HandsetId = HandsetId;
  m->ApiRequestCodeList = ApiRequestCodeList;
  RosMailDeliver((RosMailType *)m);
}
#endif
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
                        //RSOFFSET_OF_CODEC_IN_API_CODECLISTTYPE + CodecListPtr->NoOfCodecs * sizeof(ApiCodecInfoType),                
                        RSOFFSETOF(ApiCodecListType, Codec) + CodecListPtr->NoOfCodecs * sizeof(ApiCodecInfoType),
                        (rsuint8 *)CodecListPtr); 
  }
}

/***************************************************************************
*  FUNCTION: ApiGetNextCodecListElement
*  INPUTS  : Pointer to block in memory holding a codec list and a specific codec
*  OUTPUTS : A specific codec
*  ------------------------------------------------------------------------- 
*  DESCRIPTION:
*   Used by ApiGetCodecListElement, in order to search for a specific codec
*   in a codec list
*   
*****************************************************************************/
ApiCodecInfoType* ApiGetNextCodecListElement(ApiCodecListType *CodecListPtr, ApiCodecInfoType *pCI)
{
  ApiCodecListType *pEnd = (ApiCodecListType*)((rsuint8*)CodecListPtr + RSOFFSETOF(ApiCodecListType, Codec) +  CodecListPtr->NoOfCodecs*sizeof(ApiCodecInfoType));

  if (pCI == NULL)
  {
    // return the first info element
    pCI = CodecListPtr->Codec;
  }
  else
  {
    // calc the address of the next info element
    pCI = (ApiCodecInfoType*)((rsuint8*)pCI + sizeof(ApiCodecInfoType));
  }
   
  if ((rsuint8 *)pCI < (rsuint8 *)pEnd)
  {
    return pCI; // return the pointer to the next info element
  }
  return NULL; // return NULL to indicate that we have reached the end
}


/***************************************************************************
*  FUNCTION: ApiGetCodecListElement
*  INPUTS  : Pointer to block in memory holding a codec list and a specific codec
*  OUTPUTS : A specific codec
*  ------------------------------------------------------------------------- 
*  DESCRIPTION:
*   Used for getting a specific codec from a codec list. Returns NULL
*   if the codec is not in the codeclist
*
*****************************************************************************/
ApiCodecInfoType* ApiGetCodecListElement(ApiCodecListType *CodecListPtr, ApiCodecType Codec)  
{
  ApiCodecInfoType *pCI = NULL;

  while (NULL != (pCI = ApiGetNextCodecListElement(CodecListPtr, pCI)))
  {
    if (pCI->Codec == Codec)
    {
      return pCI; // return the ponter to the info element found
    }
  }
  return NULL; // return NULL to indicate that we did not find this codec in the codec list
}
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
// End of file.

