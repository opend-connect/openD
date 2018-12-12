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
* Definition of the ApiHeadset interface.
*/


#ifndef APIHEADSET_H
#define APIHEADSET_H

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
  API_HEADSET_DETECT_HEADSET_IND = 0x5D00,
  API_HEADSET_HOOK_IND = 0x5D01,
The global mail primitives MUST be defined in Global.h! */



/*! This enum defines the headset detect state types to the MMI */
typedef enum RSENUMTAG(ApiHeadsetDetectHeadsetStateType)
{
  API_HEADSET_HEADSET_PLUGGED   = 0x00, /*!<  */
  API_HEADSET_HEADSET_UNPLUGGED = 0x01, /*!<  */
} RSENUM8(ApiHeadsetDetectHeadsetStateType);

/*! This enum defines the hook state types to the MMI */
typedef enum RSENUMTAG(ApiHeadsetHookStateType)
{
  API_HEADSET_HOOK_PRESSED  = 0x00, /*!<  */
  API_HEADSET_HOOK_RELEASED = 0x01, /*!<  */
} RSENUM8(ApiHeadsetHookStateType);


/*! Mail without parameters. */
typedef struct ApiheadsetEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApiheadsetEmptySignalType;

/*! This mail is used by the API to indicate that the state of the headset
   has changed. it has either been plugged in or unplugged. */
typedef struct ApiHeadsetDetectHeadsetIndType
{
  RosPrimitiveType Primitive;            /*!< API_HEADSET_DETECT_HEADSET_IND = 0x5D00 */
  ApiHeadsetDetectHeadsetStateType HeadsetState; /*!< Indicates the state of the
                                                     headset - if it is plugged or
                                                     unplugged. */
} ApiHeadsetDetectHeadsetIndType;

/*! This mail is used by the API to indicate that the state of the headset
   hook button has changed. it has either been pressed or released. */
typedef struct ApiHeadsetHookIndType
{
  RosPrimitiveType Primitive;            /*!< API_HEADSET_HOOK_IND = 0x5D01 */
  ApiHeadsetHookStateType HookState;    /*!< Indicates the state of the hook button - if
                                           it is pressed or released. */
} ApiHeadsetHookIndType;

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

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIHEADSET_H */


