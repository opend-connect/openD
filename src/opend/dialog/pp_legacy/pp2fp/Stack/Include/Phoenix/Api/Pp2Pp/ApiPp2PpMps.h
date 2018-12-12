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
#ifndef APIPP2PPMPS_H
#define APIPP2PPMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Pp2Pp/ApiPp2Pp.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiPp2ppEnterCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_ENTER_CFM = 0x4921
****************************************************************************/
void SendApiPp2ppEnterCfm ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPp2ppExitCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_EXIT_CFM = 0x4923
****************************************************************************/
void SendApiPp2ppExitCfm ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPp2ppEnterFpModeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_ENTER_FP_MODE_CFM = 0x4925
****************************************************************************/
void SendApiPp2ppEnterFpModeCfm ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPp2ppConnectInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_CONNECT_IND = 0x4927
****************************************************************************/
void SendApiPp2ppConnectInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPp2ppSetupInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_SETUP_IND = 0x4928
****************************************************************************/
void SendApiPp2ppSetupInd ( RosTaskIdType Dst,
                            rsuint8 bHandsetId);             /*!< The HandetId is used
                                                                by the PP when it initiates
                                                                a PP-to-PP call by starting
                                                                to transmit a dummy
                                                                bearer. It will also be
                                                                used as a portable directory
                                                                number when the PP is paged
                                                                in a PP-to-PP mode. It is a
                                                                2 digit decimal number coded
                                                                in the same format as the
                                                                GroupId and may be entered
                                                                via the keypad or by other
                                                                means, 
                                                                (range: 01 to 99). */

/****************************************************************************
* FUNCTION:      SendApiPp2ppConnectCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_CONNECT_CFM = 0x492A
****************************************************************************/
void SendApiPp2ppConnectCfm ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPp2ppReleaseCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_RELEASE_CFM = 0x492C
****************************************************************************/
void SendApiPp2ppReleaseCfm ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPp2ppReleaseInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_RELEASE_IND = 0x492D
****************************************************************************/
void SendApiPp2ppReleaseInd ( RosTaskIdType Dst );


#ifdef __cplusplus
}
#endif
#endif /*APIPP2PPMPS_H */


