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
* Definition of the ApiImageControl interface.
*/


#ifndef APIIMAGECONTROL_H
#define APIIMAGECONTROL_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
#include <Api/ApiCfg.h>
/*! The following API files must be included. */
#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! Bitset defining the image ID. */
#define API_IMAGE_ID_SYSTEM RSBIT0   /*!< System */


#define API_IMAGE_ID_COLA RSBIT1   /*!< Co-Located Application. */


#define API_IMAGE_ID_FP RSBIT2   /*!< FP functionality. */


#define API_IMAGE_ID_PP RSBIT3   /*!< PP functionality. */


#define API_IMAGE_ID_ULP RSBIT4   /*!< ULP functionality. */

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_IMAGE_INFO_REQ = 0x5800,
  API_IMAGE_INFO_CFM = 0x5801,
  API_IMAGE_ACTIVATE_REQ = 0x5802,
  API_IMAGE_ACTIVATE_CFM = 0x5803,
End of mail primitives. */



/*! Bitset defining the image ID. */
typedef rsuint32 ApiImageIdType;        /*!< Set of API_IMAGE_ID_xx. */


/*! Mail without parameters. */
typedef struct ApiimagecontrolEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApiimagecontrolEmptySignalType;

/*! This mail is sent from the application to fetch information about of
   available images. */
typedef struct ApiImageInfoReqType
{
  RosPrimitiveType Primitive;            /*!< API_IMAGE_INFO_REQ = 0x5800 */
  rsuint8 ImageIndex;                   /*!< Index of the image wanted.
                                           The first image has index 0. */
} ApiImageInfoReqType;

/*! Information about an image. */
typedef struct ApiImageInfoCfmType
{
  RosPrimitiveType Primitive;            /*!< API_IMAGE_INFO_CFM = 0x5801 */
  RsStatusType Status;                  /*!< Status for the image:
                                           RSS_SUCCESS: Image is running.
                                           RSS_NO_DATA: No image header found at this index.
                                           RSS_OFFLINE: Disabled.
                                           RSS_BLOCKED: System mismatch.
                                           RSS_NOT_FOUND: End of list */
  rsuint8 ImageIndex;                   /*!< Index of the image. */
  ApiImageIdType ImageId;               /*!< General ID of the image. */
  rsuint32 DeviceId;                    /*!< 32-bit device ID. This is the same as the
                                           FWU device ID. */
  rsuint8 LinkDate[5];                  /*!< The firmware build/link date of the image. */
  rsuint8 NameLength;                   /*!< Number of bytes in the Data field used for
                                           the image name. */
  rsuint8 LabelLength;                  /*!< Number of bytes in the Data field used for
                                           the image release label. */
  rsuint8 Data[1];                      /*!< Image name and release label. */
} ApiImageInfoCfmType;

/*! This mail is sent from the application to activate an image.. */
typedef struct ApiImageActivateReqType
{
  RosPrimitiveType Primitive;            /*!< API_IMAGE_ACTIVATE_REQ = 0x5802 */
  rsuint8 ImageIndex;                   /*!< Index of the image that should be activated.
                                           0xFF means no change in index i.e. only change
                                           COLA activationg. */
  rsbool ActivateCola;                  /*!< Set true to activate Co-Located Application
                                           (COLA) for the ImageIndex specified. */
} ApiImageActivateReqType;

/*! This mail. */
typedef struct ApiImageActivateCfmType
{
  RosPrimitiveType Primitive;            /*!< API_IMAGE_ACTIVATE_CFM = 0x5803 */
  RsStatusType Status;                  /*!< Status for the request:
                                           RSS_PENDING: The image activation was accepted
                                           and the device will reset shortly.
                                           RSS_NO_DATA: The ImageIndex was invalid.
                                           RSS_BAD_FUNCTION: The image specified is not runnable.
                                           RSS_NOT_FOUND: Invalid index. */
} ApiImageActivateCfmType;

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
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiImageInfoReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_IMAGE_INFO_REQ = 0x5800
****************************************************************************/
void SendApiImageInfoReq ( RosTaskIdType Src,
                           rsuint8 ImageIndex);              /*!< Index of the image wanted.
                                                                The first image has index
                                                                0. */

/****************************************************************************
* FUNCTION:      SendApiImageActivateReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_IMAGE_ACTIVATE_REQ = 0x5802
****************************************************************************/
void SendApiImageActivateReq ( RosTaskIdType Src,
                               rsuint8 ImageIndex,           /*!< Index of the image
                                                                that should be activated.
                                                                0xFF means no change in
                                                                index i.e. only change COLA
                                                                activationg. */
                               rsbool ActivateCola);         /*!< Set true to activate
                                                                Co-Located Application
                                                                (COLA) for the ImageIndex
                                                                specified. */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIIMAGECONTROL_H */


