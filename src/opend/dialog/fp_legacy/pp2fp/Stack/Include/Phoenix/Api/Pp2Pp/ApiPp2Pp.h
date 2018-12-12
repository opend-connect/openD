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
* Definition of the ApiPp2Pp interface.
*/


#ifndef APIPP2PP_H
#define APIPP2PP_H

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
  API_PP2PP_ENTER_REQ = 0x4920,
  API_PP2PP_ENTER_CFM = 0x4921,
  API_PP2PP_EXIT_REQ = 0x4922,
  API_PP2PP_EXIT_CFM = 0x4923,
  API_PP2PP_ENTER_FP_MODE_REQ = 0x4924,
  API_PP2PP_ENTER_FP_MODE_CFM = 0x4925,
  API_PP2PP_SETUP_REQ = 0x4926,
  API_PP2PP_CONNECT_IND = 0x4927,
  API_PP2PP_SETUP_IND = 0x4928,
  API_PP2PP_CONNECT_REQ = 0x4929,
  API_PP2PP_CONNECT_CFM = 0x492A,
  API_PP2PP_RELEASE_REQ = 0x492B,
  API_PP2PP_RELEASE_CFM = 0x492C,
  API_PP2PP_RELEASE_IND = 0x492D,
The global mail primitives MUST be defined in Global.h! */




/*! Mail without parameters. */
typedef struct Apipp2ppEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} Apipp2ppEmptySignalType;

/*! This mail is sent from the application to set the protocol stack into
   Pp2Pp mode.
    In Pp2Pp mode the Pp can accept calls from other Pp with the same GroupId.
     */
typedef struct ApiPp2ppEnterReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP2PP_ENTER_REQ = 0x4920 */
  rsuint16 wGroupId;                    /*!< The GroupId is selected as a random number
                                           common for the group of PPs intended for mutual
                                           communication in direct communication mode. The
                                           GroupId shall be in decimal nibble coded format,
                                           so that entering via the keypad is possible,
                                           (range: 001 to 999). */
  rsuint8 bHandsetId;                   /*!< The HandetId is used by the PP when it
                                           initiates a PP-to-PP call by starting to transmit
                                           a dummy
                                           bearer. It will also be used as a portable
                                           directory number when the PP is paged in a
                                           PP-to-PP mode. It is a 2 digit decimal number
                                           coded in the same format as the GroupId and may
                                           be entered via the keypad or by other means, 
                                           (range: 01 to 99). */
} ApiPp2ppEnterReqType;

/*! This mail is used as a control confirmation on the API_PP2PP_ENTER_REQ. */
typedef Apipp2ppEmptySignalType ApiPp2ppEnterCfmType;

/*! This mail is sent from the application to exit Pp2Pp mode and set the
   protocol stack into normal mode. */
typedef Apipp2ppEmptySignalType ApiPp2ppExitReqType;

/*! This mail is used as a control confirmation on the API_PP2PP_EXIT_REQ. */
typedef Apipp2ppEmptySignalType ApiPp2ppExitCfmType;

/*! This mail is sent from the application to set the stack into Pp2Pp FP
   mode to "simulate" an FP. In this mode calls can be setup to the other Pp's
   in Pp2Pp mode with the same GroupId. */
typedef Apipp2ppEmptySignalType ApiPp2ppEnterFpModeReqType;

/*! This mail is used as a control confirmation on the
   API_PP2PP_ENTER_FP_MODE_REQ. */
typedef Apipp2ppEmptySignalType ApiPp2ppEnterFpModeCfmType;

/*! This mail is sent from the application to setup a call to specific or
   all Pp's in Pp2Pp mode with the same GroupId.
    
    Before Setting up a call, the Pp needs to be in Pp2Pp and FP mode 
    (done by the API's: API_PP2PP_ENTER_REQ and API_PP2PP_ENTER_FP_MODE_REQ) */
typedef struct ApiPp2ppSetupReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP2PP_SETUP_REQ = 0x4926 */
  rsuint8 bHandsetId;                   /*!< The HandetId is used by the PP when it
                                           initiates a PP-to-PP call by starting to transmit
                                           a dummy
                                           bearer. It will also be used as a portable
                                           directory number when the PP is paged in a
                                           PP-to-PP mode. It is a 2 digit decimal number
                                           coded in the same format as the GroupId and may
                                           be entered via the keypad or by other means, 
                                           (range: 01 to 99).
                                           
                                           HandsetId can be set to 0xFF to "call all" */
} ApiPp2ppSetupReqType;

/*! This mail is used as a confirmation on the API_PP2PP_SETUP_REQ,
   indicating that a PP has answered the call. */
typedef Apipp2ppEmptySignalType ApiPp2ppConnectIndType;

/*! This mail is used as an indication for incoming call from other Pp */
typedef struct ApiPp2ppSetupIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP2PP_SETUP_IND = 0x4928 */
  rsuint8 bHandsetId;                   /*!< The HandetId is used by the PP when it
                                           initiates a PP-to-PP call by starting to transmit
                                           a dummy
                                           bearer. It will also be used as a portable
                                           directory number when the PP is paged in a
                                           PP-to-PP mode. It is a 2 digit decimal number
                                           coded in the same format as the GroupId and may
                                           be entered via the keypad or by other means, 
                                           (range: 01 to 99). */
} ApiPp2ppSetupIndType;

/*! This mail is sent from the application to answer and incoming call
   (received by API_PP2PP_SETUP_REQ) */
typedef Apipp2ppEmptySignalType ApiPp2ppConnectReqType;

/*! This mail is used as a control confirmation on the
   API_PP2PP_CONNECT_REQ. */
typedef Apipp2ppEmptySignalType ApiPp2ppConnectCfmType;

/*! This mail is sent from the application to release an ongoing call. */
typedef Apipp2ppEmptySignalType ApiPp2ppReleaseReqType;

/*! This mail is used as a control confirmation on the
   API_PP2PP_RELEASE_REQ. */
typedef Apipp2ppEmptySignalType ApiPp2ppReleaseCfmType;

/*! This mail is used as an indication that the other Pp of an ongoing call
   has released the connection. */
typedef Apipp2ppEmptySignalType ApiPp2ppReleaseIndType;

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
* FUNCTION:      SendApiPp2ppEnterReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_ENTER_REQ = 0x4920
****************************************************************************/
void SendApiPp2ppEnterReq ( RosTaskIdType Src,
                            rsuint16 wGroupId,               /*!< The GroupId is
                                                                selected as a random number
                                                                common for the group of PPs
                                                                intended for mutual
                                                                communication in direct
                                                                communication mode. The
                                                                GroupId shall be in decimal
                                                                nibble coded format, so that
                                                                entering via the keypad is
                                                                possible, (range: 001 to
                                                                999). */
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
* FUNCTION:      SendApiPp2ppExitReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_EXIT_REQ = 0x4922
****************************************************************************/
void SendApiPp2ppExitReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPp2ppEnterFpModeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_ENTER_FP_MODE_REQ = 0x4924
****************************************************************************/
void SendApiPp2ppEnterFpModeReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPp2ppSetupReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_SETUP_REQ = 0x4926
****************************************************************************/
void SendApiPp2ppSetupReq ( RosTaskIdType Src,
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
                                                                (range: 01 to 99).
                                                                
                                                                HandsetId can be set to
                                                                0xFF to "call all" */

/****************************************************************************
* FUNCTION:      SendApiPp2ppConnectReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_CONNECT_REQ = 0x4929
****************************************************************************/
void SendApiPp2ppConnectReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPp2ppReleaseReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP2PP_RELEASE_REQ = 0x492B
****************************************************************************/
void SendApiPp2ppReleaseReq ( RosTaskIdType Src );


/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIPP2PP_H */


