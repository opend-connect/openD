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
#ifndef APIFWSMPS_H
#define APIFWSMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <FWU/ApiFws/ApiFws.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFwsInitCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_INIT_CFM = 0x4F81
****************************************************************************/
void SendApiFwsInitCfm ( RosTaskIdType Dst,
                         RsStatusType Status,                /*!< RSS_SUCCESS if the FWS
                                                                module is ready to handle /
                                                                write new FW. */
                         rsuint16 MaxMsgSize);               /*!< Maximum size of an API
                                                                message. */

/****************************************************************************
* FUNCTION:      SendApiFwsTerminateCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_TERMINATE_CFM = 0x4F83
****************************************************************************/
void SendApiFwsTerminateCfm ( RosTaskIdType Dst,
                              RsStatusType Status);          /*!< Status. */

/****************************************************************************
* FUNCTION:      SendApiFwsStatusInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_STATUS_IND = 0x4F84
****************************************************************************/
void SendApiFwsStatusInd ( RosTaskIdType Dst,
                           ApiFwsStatusType FwsStatus,       /*!< Current status/state
                                                                of the FWS module. */
                           rsuint32 Progress);               /*!< The numbers of bytes
                                                                read/processed from the .fws
                                                                file. The offset of the next
                                                                byte expected if FwsStatus =
                                                                AF_STATUS_RESUME. */

/****************************************************************************
* FUNCTION:      SendApiFwsInfoInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_INFO_IND = 0x4F85
****************************************************************************/
void SendApiFwsInfoInd ( RosTaskIdType Dst,
                         ApiGuidType Guid,                   /*!< The id of the device. */
                         rsuint32 ImageId,                   /*!< The image ID can be
                                                                used to distinguish between
                                                                the different images in a
                                                                system where the FW is spilt
                                                                in multiple images. E.g. in
                                                                system having one image with
                                                                the main program and another
                                                                with the CoLA image. */
                         rsuint8 LinkDate[5],                /*!< The link date of the
                                                                current FW in the device. */
                         rsuint8 NameLength,                 /*!< The length of Name[] */
                         rsuint8 Name[1]);                   /*!< The name of the
                                                                application/device. */

/****************************************************************************
* FUNCTION:      SendApiFwsWriteCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_WRITE_CFM = 0x4F87
****************************************************************************/
void SendApiFwsWriteCfm ( RosTaskIdType Dst,
                          RsStatusType Status);              /*!< Status. */

/****************************************************************************
* FUNCTION:      SendApiFwsWriteExtDataCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_WRITE_EXT_DATA_CFM = 0x4F89
****************************************************************************/
void SendApiFwsWriteExtDataCfm ( RosTaskIdType Dst,
                                 RsStatusType Status);       /*!< Status. */

#ifdef __cplusplus
}
#endif
#endif /*APIFWSMPS_H */


