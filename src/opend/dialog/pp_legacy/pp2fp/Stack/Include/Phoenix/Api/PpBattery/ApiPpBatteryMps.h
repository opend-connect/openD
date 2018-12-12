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
#ifndef APIPPBATTERYMPS_H
#define APIPPBATTERYMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/PpBattery/ApiPpBattery.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiPpBatCapacityInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_CAPACITY_IND = 0x5401
****************************************************************************/
void SendApiPpBatCapacityInd ( RosTaskIdType Dst,
                               rsuint8 BatteryCapacity);     /*!< The current battery
                                                                capacity estimate in %. */

/****************************************************************************
* FUNCTION:      SendApiPpBatLowInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_LOW_IND = 0x5402
****************************************************************************/
void SendApiPpBatLowInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpBatEmptyInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_EMPTY_IND = 0x5403
****************************************************************************/
void SendApiPpBatEmptyInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpBatPowerOnReasonInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_POWER_ON_REASON_IND = 0x5405
****************************************************************************/
void SendApiPpBatPowerOnReasonInd ( RosTaskIdType Dst,
                                    ApiPpBatPowerOnReasonType ApiPowerOnReason);
                                                             /*!< Info on the last power
                                                                on */

/****************************************************************************
* FUNCTION:      SendApiPpBatChargeInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_CHARGE_IND = 0x5407
****************************************************************************/
void SendApiPpBatChargeInd ( RosTaskIdType Dst,
                             rsbool ChargeInd);              /*!< True if Pp is being
                                                                charged */

/****************************************************************************
* FUNCTION:      SendApiPpBatResetChargingStateCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_RESET_CHARGING_STATE_CFM = 0x5409
****************************************************************************/
void SendApiPpBatResetChargingStateCfm ( RosTaskIdType Dst,
                                         rsbool Result);     /*!< True if charging state
                                                                was reset. False when not
                                                                possible to reset state: Not
                                                                in charge state - handset
                                                                not in cradle, none
                                                                chargeable battery,
                                                                temperature to high. ? */

/****************************************************************************
* FUNCTION:      SendApiPpBatNonChargeableInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_NON_CHARGEABLE_IND = 0x5410
****************************************************************************/
void SendApiPpBatNonChargeableInd ( RosTaskIdType Dst );


#ifdef __cplusplus
}
#endif
#endif /*APIPPBATTERYMPS_H */


