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
* Definition of the ApiFpNoEmission interface.
*/


#ifndef APIFPNOEMISSION_H
#define APIFPNOEMISSION_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


/* Global mail primitives:
  API_FP_MAC_NO_EMISSION_MODE_ENABLE_REQ = 0x4600,
  API_FP_MAC_NO_EMISSION_MODE_DISABLE_REQ = 0x4601,
  API_FP_MAC_NO_EMISSION_MODE_STOP_REQ = 0x4602,
  API_FP_MAC_NO_EMISSION_MODE_PENDING_IND = 0x4603,
  API_FP_MAC_NO_EMISSION_MODE_ACTIVE_IND = 0x4604,
  API_FP_MAC_NO_EMISSION_MODE_STOP_IND = 0x4605,
  API_FP_MAC_NO_EMISSION_MODE_SET_PREF_CARRIER_REQ = 0x4606,
The global mail primitives MUST be defined in Global.h! */



/*! Mail without parameters. */
typedef struct ApifpnoemissionEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApifpnoemissionEmptySignalType;

/*! This mail is send from the FpApplication to enable No Emission mode. */
typedef ApifpnoemissionEmptySignalType ApiFpMacNoEmissionModeEnableReqType;

/*! This mail is send from the FpApplication to disable No Emission mode. */
typedef ApifpnoemissionEmptySignalType ApiFpMacNoEmissionModeDisableReqType;

/*! This mail is send from the FpApplication to leave No Emission State to
   be able to make calls. */
typedef ApifpnoemissionEmptySignalType ApiFpMacNoEmissionModeStopReqType;

/*! This mail is used to inform the Application when the PP is answering an
   incoming call. */
typedef ApifpnoemissionEmptySignalType ApiFpMacNoEmissionModePendingIndType;

/*! Signals to the Application that the FP protocol has entered No Emission
   State */
typedef ApifpnoemissionEmptySignalType ApiFpMacNoEmissionModeActiveIndType;

/*! Signals to the Application that the FP protocol has left No Emission
   State */
typedef ApifpnoemissionEmptySignalType ApiFpMacNoEmissionModeStopIndType;

/*! This mail is used by the FpApplication to set the preferred carrier to
   use when exiting No emission mode. */
typedef struct ApiFpMacNoEmissionModeSetPrefCarrierReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_MAC_NO_EMISSION_MODE_SET_PREF_CARRIER_REQ = 0x4606 */
  rsuint8 PrefCarrier;                  /*!< The preferred carrier:
                                             0x00..0x09: Selected carrier 0-9
                                             0xFF: No preferred carrier */
}PACKED_STRUCT ApiFpMacNoEmissionModeSetPrefCarrierReqType;


#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiFpMacNoEmissionModeEnableReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MAC_NO_EMISSION_MODE_ENABLE_REQ = 0x4600
****************************************************************************/
void SendApiFpMacNoEmissionModeEnableReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMacNoEmissionModeDisableReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MAC_NO_EMISSION_MODE_DISABLE_REQ = 0x4601
****************************************************************************/
void SendApiFpMacNoEmissionModeDisableReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMacNoEmissionModeStopReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MAC_NO_EMISSION_MODE_STOP_REQ = 0x4602
****************************************************************************/
void SendApiFpMacNoEmissionModeStopReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiFpMacNoEmissionModeSetPrefCarrierReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MAC_NO_EMISSION_MODE_SET_PREF_CARRIER_REQ = 0x4606
****************************************************************************/
void SendApiFpMacNoEmissionModeSetPrefCarrierReq ( RosTaskIdType Src,
                                                   rsuint8 PrefCarrier);
                                                             /*!< The preferred carrier:
                                                                  0x00..0x09: Selected
                                                                carrier 0-9
                                                                  0xFF: No preferred
                                                                carrier */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPNOEMISSION_H */


