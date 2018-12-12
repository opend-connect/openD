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
* Definition of the ApiPpProject interface.
*/


#ifndef APIPPPROJECT_H
#define APIPPPROJECT_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API header files must be included. */
#include <Api/ApiCfg.h> /* API configuration */

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
  API_PP_VBATT_ENABLE_REQ=0x4382,
  API_PP_VBATT_REQ=0x4380,
  API_PP_VBATT_ENABLE_CFM=0x4383,
  API_PP_VBATT_CFM=0x4381,
The global mail primitives MUST be defined in Global.h! */



/*! Mail without parameters. */
typedef struct ApippprojectEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApippprojectEmptySignalType;
typedef struct ApiPpVbattEnableReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_VBATT_ENABLE_REQ=0x4382 */
  rsuint8 Enable;                       /*!< Enable > 0 and  Disable =0 */
} ApiPpVbattEnableReqType;
typedef struct ApiPpVbattReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_VBATT_REQ=0x4380 */
} ApiPpVbattReqType;

/*! Used to return  Enable/Disable status for VBATT measurement.
     */
typedef struct ApiPpVbattEnableCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_VBATT_ENABLE_CFM=0x4383 */
  rsuint8 Status;                       /*!< Enabled  > 0, Disabled =0 */
} ApiPpVbattEnableCfmType;

/*! This will return the latest battery voltage measurements. 
    The values read via this API is the raw ADC values. To convert these into
   the actual battery voltage use this formula: Vbattery = (ADCvalue * 5,12)/1023
     */
typedef struct ApiPpVbattCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_VBATT_CFM=0x4381 */
  rsuint16 VbattIdle;                   /*!< ADC value measured in IDLE state */
  rsuint16 VbattRx;                     /*!< ADC value measured during an RX slot */
  rsuint16 VbattTx;                     /*!< ADC value measured during a TX slot */
} ApiPpVbattCfmType;

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
* FUNCTION:      SendApiPpVbattEnableReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_VBATT_ENABLE_REQ=0x4382
****************************************************************************/
void SendApiPpVbattEnableReq ( RosTaskIdType Src,
                               rsuint8 Enable);              /*!< Enable > 0 and 
                                                                Disable =0 */

/****************************************************************************
* FUNCTION:      SendApiPpVbattReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_VBATT_REQ=0x4380
****************************************************************************/
void SendApiPpVbattReq ( RosTaskIdType Src );


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIPPPROJECT_H */


