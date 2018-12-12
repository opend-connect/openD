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
* Definition of the ApiProdTest interface.
*/


#ifndef APIPRODTEST_H
#define APIPRODTEST_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
#include <Api/ApiCfg.h>

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
  API_PROD_TEST_REQ = 0x4FFE,
  API_PROD_TEST_CFM = 0x4FFF,
The global mail primitives MUST be defined in Global.h! */




/*! Mail without parameters. */
typedef struct ApiprodtestEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApiprodtestEmptySignalType;

/*! This mail is used by the MCU to send a Production test command to the
   unit */
typedef struct ApiProdTestReqType
{
  RosPrimitiveType Primitive;            /*!< API_PROD_TEST_REQ = 0x4FFE */
  rsuint16 Opcode;                      /*!< Op-code identifying the HW test command. */
  rsuint16 ParameterLength;             /*!< The total length in bytes of the
                                           parameters. */
  rsuint8 Parameters [1];               /*!< Optional parameters. */
} ApiProdTestReqType;

/*! This mail is used to confirm the API_PROD_TEST_REQ command and return
   requested parameters */
typedef struct ApiProdTestCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PROD_TEST_CFM = 0x4FFF */
  rsuint16 Opcode;                      /*!< Op-code identifying the HW test command. */
  rsuint16 ParameterLength;             /*!< The total length in bytes of the
                                           parameters. */
  rsuint8 Parameters [1];               /*!< Optional parameters. */
} ApiProdTestCfmType;

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
* FUNCTION:      SendApiProdTestReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PROD_TEST_REQ = 0x4FFE
****************************************************************************/
void SendApiProdTestReq ( RosTaskIdType Src,
                          rsuint16 Opcode,                   /*!< Op-code identifying
                                                                the HW test command. */
                          rsuint16 ParameterLength,          /*!< The total length in
                                                                bytes of the parameters. */
                          rsuint8 Parameters [1]);           /*!< Optional parameters. */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIPRODTEST_H */


