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
* Definition of the ApiPpBattery interface.
*/


#ifndef APIPPBATTERY_H
#define APIPPBATTERY_H

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
  API_PP_BAT_CAPACITY_REQ = 0x5400,
  API_PP_BAT_CAPACITY_IND = 0x5401,
  API_PP_BAT_LOW_IND = 0x5402,
  API_PP_BAT_EMPTY_IND = 0x5403,
  API_PP_BAT_POWER_ON_REASON_REQ = 0x5404,
  API_PP_BAT_POWER_ON_REASON_IND = 0x5405,
  API_PP_BAT_CHARGE_REQ = 0x5406,
  API_PP_BAT_CHARGE_IND = 0x5407,
  API_PP_BAT_RESET_CHARGING_STATE_REQ = 0x5408,
  API_PP_BAT_RESET_CHARGING_STATE_CFM = 0x5409,
  API_PP_BAT_NON_CHARGEABLE_IND = 0x5410,
The global mail primitives MUST be defined in Global.h! */



/*! This enum defines power on reasons to the MMI */
typedef enum RSENUMTAG(ApiPpBatPowerOnReasonType)
{
  API_NORMAL_POWER_ON         = 0x00, /*!<  */
  API_SOFTWARE_RESET_POWER_ON = 0x01, /*!<  */
  API_NEW_BATTERY_POWER_ON    = 0x02, /*!<  */
  API_CRADLE_POWER_ON         = 0x03, /*!<  */
  API_UNKNOWN_POWER_ON        = 0xFF  /*!<  */
} RSENUM8(ApiPpBatPowerOnReasonType);


/*! Mail without parameters. */
typedef struct ApippbatteryEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApippbatteryEmptySignalType;

/*! This mail is used by the MMI to force the API to reply instantly with
   the current battery capacity estimate (API_PP_BAT_CAPACITY_IND). */
typedef ApippbatteryEmptySignalType ApiPpBatCapacityReqType;

/*! This mail is used by the API to indicate the current capacity
   estimation to the MMI.
    It is automatically send when the capacity change by 1%, or instantly if
   requested by the API_PP_BAT_CAPACITY_REQ */
typedef struct ApiPpBatCapacityIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_BAT_CAPACITY_IND = 0x5401 */
  rsuint8 BatteryCapacity;              /*!< The current battery capacity estimate in %. */
} ApiPpBatCapacityIndType;

/*! This mail is used by the API to indicate to the MMI that the battery is low.
    When the MMI receives this mail it should indicate to the user that the
   battery is low.
    The battery low state is judged by a voltage measurement. */
typedef ApippbatteryEmptySignalType ApiPpBatLowIndType;

/*! This mail is used by the API to indicate to the MMI that the battery is empty.
    When the MMI receives this mail it should clean up and then power off the
   PP with the API_PP_POWER_OFF_REQ.
    The battery low state is judged by a voltage measurement. */
typedef ApippbatteryEmptySignalType ApiPpBatEmptyIndType;

/*! This mail is used by the MMI to request the API to reply with
   information for last power on. */
typedef ApippbatteryEmptySignalType ApiPpBatPowerOnReasonReqType;

/*! This mail is used by the API to inform the MMI about the reason for the
   last power on. */
typedef struct ApiPpBatPowerOnReasonIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_BAT_POWER_ON_REASON_IND = 0x5405 */
  ApiPpBatPowerOnReasonType ApiPowerOnReason; /*!< Info on the last power on */
} ApiPpBatPowerOnReasonIndType;

/*! This mail is used by the MMI to ask if the Pp is being charged, 
   (API_PP_BAT_CAPACITY_IND). */
typedef ApippbatteryEmptySignalType ApiPpBatChargeReqType;

/*! This mail is used by the API to indicate if the Pp is being charged to
   the MMI. 
     */
typedef struct ApiPpBatChargeIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_BAT_CHARGE_IND = 0x5407 */
  rsbool ChargeInd;                     /*!< True if Pp is being charged */
} ApiPpBatChargeIndType;

/*! This mail is used by the MMI to reset charging state. 
     */
typedef ApippbatteryEmptySignalType ApiPpBatResetChargingStateReqType;

/*! Reset battery charging state confirm mail. */
typedef struct ApiPpBatResetChargingStateCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_BAT_RESET_CHARGING_STATE_CFM = 0x5409 */
  rsbool Result;                        /*!< True if charging state was reset. False
                                           when not possible to reset state: Not in charge
                                           state - handset not in cradle, none chargeable
                                           battery, temperature to high. ? */
} ApiPpBatResetChargingStateCfmType;

/*! This mail is used by the API to indicate if a non-chargeable battery
   has been detected. 
     */
typedef ApippbatteryEmptySignalType ApiPpBatNonChargeableIndType;

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
* FUNCTION:      SendApiPpBatCapacityReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_CAPACITY_REQ = 0x5400
****************************************************************************/
void SendApiPpBatCapacityReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpBatPowerOnReasonReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_POWER_ON_REASON_REQ = 0x5404
****************************************************************************/
void SendApiPpBatPowerOnReasonReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpBatChargeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_CHARGE_REQ = 0x5406
****************************************************************************/
void SendApiPpBatChargeReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpBatResetChargingStateReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_BAT_RESET_CHARGING_STATE_REQ = 0x5408
****************************************************************************/
void SendApiPpBatResetChargingStateReq ( RosTaskIdType Src );


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIPPBATTERY_H */


