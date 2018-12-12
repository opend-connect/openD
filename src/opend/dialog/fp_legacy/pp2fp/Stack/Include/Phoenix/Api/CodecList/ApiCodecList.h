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
* Definition of the ApiCodecList interface.
*/


#ifndef APICODECLIST_H
#define APICODECLIST_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Api/ApiCfg.h>

#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif



/*! This struct holds all data for the codec negotiations. */
typedef struct {
  ApiNegotiationIndicatorType NegotiationIndicator; /*!< Is negotiation allowed */
  rsuint8 NoOfCodecs;                   /*!< Number of codecs in the codec list */
  ApiCodecInfoType Codec[NUMBER_OF_CODEC_LIST_ENTRIES
]; /*!< The actual codecs. */
} ApiCommonCodecListType;

/*! This struct holds all data for the codec negotiations. */
typedef struct {
  ApiCommonCodecListType CommonCodecList; /*!< This struct holds a codec list of the
                                              common codecs between the Fp and the Pp. The
                                              CommonCodecList is updated for each incoming
                                              codec list. The priority of the codecs
                                              corresponds to the incoming codec list. */
  ApiCodecType CodecForCurrentCall;     /*!< The selected codec to the current call */
} ApiCodecListHandlingType;

/*! Global variable that holds information about codecs. */
extern ApiCodecListHandlingType ApiPpCodecHandlingData;

/*! Global variable that holds the active registration. */
extern rsuint8 ApiPpActiveRegistration;


#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPopPack.h>
#else
  #pragma pack(pop)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */


/****************************************************************************
*                             Function prototypes
****************************************************************************/

/****************************************************************************
*  FUNCTION:       ApiBuildCodecListHeader
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to allocate a codec list
                   containing 0 codec elements, and with the
                   NegotiationIndicator given as parameter
****************************************************************************/
void ApiBuildCodecListHeader(ApiCodecListType **CodecListPtr,
                                                             /*!< Pointer to pointer
                                                                holding the address of the
                                                                codec list that the should
                                                                be allocated. *CodecListPtr
                                                                is set to NULL if this
                                                                function fails to allocate
                                                                memory for the new codec
                                                                element. */
                             ApiNegotiationIndicatorType NegotiationIndicator);
                                                             /*!<
                                                                Negotioantionindicator,
                                                                should set be set to
                                                                API_NI_POSSIBLE for enable
                                                                codec negotiation */

/****************************************************************************
*  FUNCTION:       ApiAddToCodecList
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to allocate and append a codec
                   element to a codec list holding previously allocated codec
                   elements. This function reallocates the codec list wit a new
                   size that is the size of the existing list + the size of the
                   new codec element. The CodecInfo is copied to the tail of
                   the new list allocated.
****************************************************************************/
void ApiAddToCodecList(ApiCodecListType **CodecListPtr,      /*!< Pointer to pointer
                                                                holding the address of the
                                                                codec list that the codec
                                                                element should be appended
                                                                to when this function is
                                                                called. *CodecListPtr is set
                                                                to NULL if this function
                                                                fails to allocate memory for
                                                                the new codec element. */
                       ApiCodecInfoType *CodecInfo);         /*!< Pointer to the codec
                                                                data that should be
                                                                appended. */

/****************************************************************************
*  FUNCTION:       ApiFreeCodecList
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to free an codec list memory block
                   allocate by ApiBuildCodecList().
****************************************************************************/
void ApiFreeCodecList(ApiCodecListType **CodecListPtr);      /*!< Pointer to pointer
                                                                holding the address of the
                                                                memory block that should be
                                                                freed. */

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

/****************************************************************************
*  FUNCTION:       ApiPutCodecListInIe
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to put a codec list in an info
                   element
****************************************************************************/
void ApiPutCodecListInIe(ApiCodecListType *CodecListPtr,     /*!< Pointer to the codec
                                                                list that holds one or more
                                                                codec list elements */
                         ApiInfoElementType **IeBlockPtr,    /*!< Pointer to pointer
                                                                holding the address of the
                                                                memory block that the codec
                                                                list allocated should be
                                                                appended. */
                         rsuint16 *IeBlockLengthPtr);        /*!< Pointer to variable
                                                                holding the current size of
                                                                the memory block used to
                                                                store the info elements. */

/****************************************************************************
*  FUNCTION:       ApiGetCodecListFromIe
*
*  RETURNS :       Pointer to the codec list that holds one or more codec
                   list elements
*
*  DESCRIPTION:    This function is used to get a codec list from an info
                   element
****************************************************************************/
ApiCodecListType* ApiGetCodecListFromIe(ApiInfoElementType *IeBlockPtr,
                                                             /*!< Pointer to the info
                                                                element block that holds one
                                                                or more info elements */
                                        rsuint16 IeBlockLength);
                                                             /*!< The size of the info
                                                                element block. */

/****************************************************************************
*  FUNCTION:       ApiGetCommonCodecListFromEeprom
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used to get the current codec list from
                   eeprom. 
****************************************************************************/
void ApiGetCommonCodecListFromEeprom(void);

/****************************************************************************
*  FUNCTION:       ApiMatchCodecLists
*
*  RETURNS :       The result is put in the struct ApiCodecHandlingData
*
*  DESCRIPTION:    This function is used to compare to the Fp codec list
                   with the Pp codec list, 
****************************************************************************/
void ApiMatchCodecLists(ApiCodecListType *FpCodecListPtr);   /*!< Pointer to Fp codec
                                                                list */

/****************************************************************************
*  FUNCTION:       ApiAddNewSupportedCodecToCommonCodecList
*
*  RETURNS :       The result is put in the struct ApiCodecHandlingData
*
*  DESCRIPTION:    This function is used to compare to the Fp codec list
                   with the Pp codec list, 
****************************************************************************/
void ApiAddNewSupportedCodecToCommonCodecList(ApiCodecListType * IncomingCodecListPtr
);
                                                             /*!< Pointer to incomming
                                                                codec list */

/****************************************************************************
*  FUNCTION:       ApiSaveCommonCodecListInEeprom
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used for saving the common codec list
                   in Eeprom
****************************************************************************/
void ApiSaveCommonCodecListInEeprom(void);

/****************************************************************************
*  FUNCTION:       ApiGetCommonCodecListPtr
*
*  RETURNS :       Pointer to common codec list
*
*  DESCRIPTION:    This function is used by the MMI to get a pointer to the
                   common codec list for the FP and PP. 
****************************************************************************/
ApiCodecListType* ApiGetCommonCodecListPtr(void);

/****************************************************************************
*  FUNCTION:       ApiGetCommonCodecListInIe
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used by the MMI to get the common codec
                   list for the FP and PP, which is packed in an Info element
****************************************************************************/
void ApiGetCommonCodecListInIe(rsuint16 *InfoElementLength,  /*!< The length of the Data
                                                                Information Element */
                               ApiInfoElementType *InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                 [API_IE_CODEC_LIST] */

/****************************************************************************
*  FUNCTION:       ApiGetCurrentCodecList
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used by the MMI to request the codec
                   for the current call. If no call is active the return info
                   element block will be emty.
****************************************************************************/
void ApiGetCurrentCodecList(rsuint16 *InfoElementLength,     /*!< The length of the Data
                                                                Information Element */
                            ApiInfoElementType *InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the format:
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Possible Infoelements:
                                                                 [API_IE_CODEC_LIST] */

/****************************************************************************
*  FUNCTION:       ApiIsCodecListSupported
*
*  RETURNS :       TRUE if codec list during registration was received,
                   otherwise FALSE
*
*  DESCRIPTION:    This function is used to test if any codec list was
                   received during registration, if this is not the case FALSE
                   is returned, since GAB device is assumed
****************************************************************************/
rsbool ApiIsCodecListSupported(void);

/****************************************************************************
*  FUNCTION:       ApiInitializeApiCodecHandlingData
*
*  RETURNS :       void
*
*  DESCRIPTION:    This function is used in startup in order to initialize
                   ApiCodecHandlingData. 
****************************************************************************/
void ApiInitializeApiCodecHandlingData(void);


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APICODECLIST_H */


