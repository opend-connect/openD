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
#ifndef APIIMAGECONTROLMPS_H
#define APIIMAGECONTROLMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/ImageControl/ApiImageControl.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiImageInfoCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_IMAGE_INFO_CFM = 0x5801
****************************************************************************/
void SendApiImageInfoCfm ( RosTaskIdType Dst,
                           RsStatusType Status,              /*!< Status for the image:
                                                                RSS_SUCCESS: Image is running.
                                                                RSS_NO_DATA: No image
                                                                header found at this index.
                                                                RSS_OFFLINE: Disabled.
                                                                RSS_BLOCKED: System mismatch.
                                                                RSS_NOT_FOUND: End of list */
                           rsuint8 ImageIndex,               /*!< Index of the image. */
                           ApiImageIdType ImageId,           /*!< General ID of the
                                                                image. */
                           rsuint32 DeviceId,                /*!< 32-bit device ID. This
                                                                is the same as the FWU
                                                                device ID. */
                           rsuint8 LinkDate[5],              /*!< The firmware
                                                                build/link date of the
                                                                image. */
                           rsuint8 NameLength,               /*!< Number of bytes in the
                                                                Data field used for the
                                                                image name. */
                           rsuint8 LabelLength,              /*!< Number of bytes in the
                                                                Data field used for the
                                                                image release label. */
                           rsuint8 Data[1]);                 /*!< Image name and release
                                                                label. */

/****************************************************************************
* FUNCTION:      SendApiImageActivateCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_IMAGE_ACTIVATE_CFM = 0x5803
****************************************************************************/
void SendApiImageActivateCfm ( RosTaskIdType Dst,
                               RsStatusType Status);         /*!< Status for the request:
                                                                RSS_PENDING: The image
                                                                activation was accepted and
                                                                the device will reset shortly.
                                                                RSS_NO_DATA: The ImageIndex
                                                                was invalid.
                                                                RSS_BAD_FUNCTION: The image
                                                                specified is not runnable.
                                                                RSS_NOT_FOUND: Invalid
                                                                index. */

#ifdef __cplusplus
}
#endif
#endif /*APIIMAGECONTROLMPS_H */


