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
#ifndef APIFPULE10MPS_H
#define APIFPULE10MPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpUle/ApiFpUle10.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpUleDeleteRegistration10Cfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_DELETE_REGISTRATION10_CFM = 0x4193
****************************************************************************/
void SendApiFpUleDeleteRegistration10Cfm ( RosTaskIdType Dst,
                                           RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */
                                           rsuint8 DeviceId);
                                                             /*!< The Id of the deleted
                                                                device. */

/****************************************************************************
* FUNCTION:      SendApiFpUleGetDeviceIpui10Cfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_ULE_GET_DEVICE_IPUI10_CFM = 0x418F
****************************************************************************/
void SendApiFpUleGetDeviceIpui10Cfm ( RosTaskIdType Dst,
                                      RsStatusType Status,   /*!< Indicates whether the
                                                                command succeeded or not. */
                                      rsuint8 DeviceId,      /*!< The Id for which the
                                                                IPUI is read. */
                                      rsuint8 IPUI[5]);      /*!< The IPUI. */

#ifdef __cplusplus
}
#endif
#endif /*APIFPULE10MPS_H */


