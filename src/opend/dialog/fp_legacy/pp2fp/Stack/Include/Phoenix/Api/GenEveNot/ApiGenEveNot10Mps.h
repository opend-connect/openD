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
#ifndef APIGENEVENOT10MPS_H
#define APIGENEVENOT10MPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/GenEveNot/ApiGenEveNot10.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpGenevenotPpEvent10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GENEVENOT_PP_EVENT10_IND = 0x5702
****************************************************************************/
void SendApiFpGenevenotPpEvent10Ind ( RosTaskIdType Dst,
                                      rsuint8 HandsetId,     /*!< HandsetId of handset
                                                                that sent the event. */
                                      rsuint8 CountOfEvents,  /*!< Number of event
                                                                 notifications in the mail */
                                      rsuint16 LengthOfData,  /*!< Length of
                                                                 notification data in bytes. */
                                      rsuint8 Data[1]);      /*!< Notification data.
                                                                This shall be formatted as
                                                                one or more
                                                                ApiGenEveNotEventNotification
                                                                Type or
                                                                ApiGenEveNotProprietaryEventN
                                                                otificationType. */

#ifdef __cplusplus
}
#endif
#endif /*APIGENEVENOT10MPS_H */


