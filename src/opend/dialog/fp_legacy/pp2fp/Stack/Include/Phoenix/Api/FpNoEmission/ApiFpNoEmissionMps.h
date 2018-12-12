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
#ifndef APIFPNOEMISSIONMPS_H
#define APIFPNOEMISSIONMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpNoEmission/ApiFpNoEmission.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpMacNoEmissionModePendingInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MAC_NO_EMISSION_MODE_PENDING_IND = 0x4603
****************************************************************************/
void SendApiFpMacNoEmissionModePendingInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiFpMacNoEmissionModeActiveInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MAC_NO_EMISSION_MODE_ACTIVE_IND = 0x4604
****************************************************************************/
void SendApiFpMacNoEmissionModeActiveInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiFpMacNoEmissionModeStopInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MAC_NO_EMISSION_MODE_STOP_IND = 0x4605
****************************************************************************/
void SendApiFpMacNoEmissionModeStopInd ( RosTaskIdType Dst );


#ifdef __cplusplus
}
#endif
#endif /*APIFPNOEMISSIONMPS_H */


