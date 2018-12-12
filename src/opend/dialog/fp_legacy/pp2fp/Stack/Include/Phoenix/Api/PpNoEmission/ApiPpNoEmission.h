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
* Definition of the ApiPpNoEmission interface.
*/


#ifndef APIPPNOEMISSION_H
#define APIPPNOEMISSION_H

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

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Global mail primitives:
  API_PP_MAC_NO_EMISSION_MODE_ENABLE_REQ = 0x5C00,
  API_PP_MAC_NO_EMISSION_MODE_DISABLE_REQ = 0x5C01,
  API_PP_MAC_NO_EMISSION_MODE_STOP_REQ = 0x5C02,
  API_PP_MAC_NO_EMISSION_MODE_PENDING_IND = 0x5C03,
  API_PP_MAC_NO_EMISSION_MODE_ACTIVE_IND = 0x5C04,
  API_PP_MAC_NO_EMISSION_MODE_STOP_IND = 0x5C05,
The global mail primitives MUST be defined in Global.h! */




/*! Mail without parameters. */
typedef struct ApippnoemissionEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApippnoemissionEmptySignalType;

/*! This mail is send from the PpApplication to enable No Emission mode.
    This command is intended for debugging/test purposes only. */
typedef ApippnoemissionEmptySignalType ApiPpMacNoEmissionModeEnableReqType;

/*! This mail is send from the PpApplication to disable No Emission mode.
    This command is intended for debugging/test purposes only. */
typedef ApippnoemissionEmptySignalType ApiPpMacNoEmissionModeDisableReqType;

/*! This mail is send from the PpApplication to leave No Emission State to
   be able to make calls. */
typedef ApippnoemissionEmptySignalType ApiPpMacNoEmissionModeStopReqType;

/*! Signals to the PpApplication that the protocol of the FP has entered
   count down state to No Emission State */
typedef ApippnoemissionEmptySignalType ApiPpMacNoEmissionModePendingIndType;

/*! Signals to the PpApplication that the protocol of the FP has entered No
   Emission State */
typedef ApippnoemissionEmptySignalType ApiPpMacNoEmissionModeActiveIndType;

/*! Signals to the PpApplication that the protocol of the FP has left No
   Emission State */
typedef ApippnoemissionEmptySignalType ApiPpMacNoEmissionModeStopIndType;

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
* FUNCTION:      SendApiPpMacNoEmissionModeEnableReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MAC_NO_EMISSION_MODE_ENABLE_REQ = 0x5C00
****************************************************************************/
void SendApiPpMacNoEmissionModeEnableReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMacNoEmissionModeDisableReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MAC_NO_EMISSION_MODE_DISABLE_REQ = 0x5C01
****************************************************************************/
void SendApiPpMacNoEmissionModeDisableReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpMacNoEmissionModeStopReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MAC_NO_EMISSION_MODE_STOP_REQ = 0x5C02
****************************************************************************/
void SendApiPpMacNoEmissionModeStopReq ( RosTaskIdType Src );


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIPPNOEMISSION_H */


