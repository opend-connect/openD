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
#ifndef APIFPMM10MPS_H
#define APIFPMM10MPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpMm/ApiFpMm10.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpMmGetRegistrationCount10Cfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_REGISTRATION_COUNT10_CFM = 0x4101
****************************************************************************/
void SendApiFpMmGetRegistrationCount10Cfm ( RosTaskIdType Dst,
                                            RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */
                                            rsuint8 MaxNoHandsets,
                                                             /*!< The maximum number of
                                                                handsets that can be
                                                                registered. */
                                            rsuint8 HandsetIdLength,
                                                             /*!< The number of handsets
                                                                registered currently. */
                                            rsuint8 HandsetId[1]);
                                                             /*!< Array of Ids of the
                                                                handsets registered. 
(Index
                                                                0 to HandsetIdLength-1 is
                                                                used.) */

/****************************************************************************
* FUNCTION:      SendApiFpMmGetHandsetIpui10Cfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_GET_HANDSET_IPUI10_CFM = 0x410A
****************************************************************************/
void SendApiFpMmGetHandsetIpui10Cfm ( RosTaskIdType Dst,
                                      RsStatusType Status,   /*!< Indicates whether the
                                                                command succeeded or not. */
                                      rsuint8 HandsetId,     /*!< The Id for which the
                                                                IPUI is read. */
                                      rsuint8 IPUI[5],       /*!< The IPUI. */
                                      rsuint16 InfoElementLength,
                                                             /*!< (OPTIONAL) The length
                                                                of the Data Information
                                                                Element */
                                      rsuint8 InfoElement[1]);
                                                             /*!< (OPTIONAL) The
                                                                InfoElementList can hold a
                                                                number Info Elements placed
                                                                in the in the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                Phoenix_PP_API_Types.doc)
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Info elements:
                                                                [API_IE_CODECLIST]
                                                                [API_IE_BASIC_TERMCAPS] 
                                                                [API_IE_LOCATION_STATUS] */

/****************************************************************************
* FUNCTION:      SendApiFpMmHandsetPresent10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_HANDSET_PRESENT10_IND = 0x4108
****************************************************************************/
void SendApiFpMmHandsetPresent10Ind ( RosTaskIdType Dst,
                                      rsuint8 HandsetId,     /*!< Id of the handset that
                                                                has made a location update. */
                                      rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                      rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                Phoenix_PP_API_Types.doc)
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Info elements:
                                                                [API_IE_CODECLIST] 
                                                                [API_IE_MODEL_ID]
                                                                [API_IE_TERMCAPS] */

/****************************************************************************
* FUNCTION:      SendApiFpMmHandsetDetach10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_HANDSET_DETACH10_IND = 0x410E
****************************************************************************/
void SendApiFpMmHandsetDetach10Ind ( RosTaskIdType Dst,
                                     rsuint8 HandsetId,      /*!< Id of the handset that
                                                                has made a location update. */
                                     rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                     rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                Phoenix_PP_API_Types.doc)
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Info elements:
                                                                [API_IE_MODEL_ID] */

/****************************************************************************
* FUNCTION:      SendApiFpMmRegistrationComplete10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_REGISTRATION_COMPLETE10_IND = 0x4107
****************************************************************************/
void SendApiFpMmRegistrationComplete10Ind ( RosTaskIdType Dst,
                                            RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not.
                                                                RsStatusType is defined in
                                                                the ROS */
                                            rsuint8 HandsetId,
                                                             /*!< Id of the handset that
                                                                was registered to the FP */
                                            rsuint16 InfoElementLength,
                                                             /*!< The length of the Data
                                                                Information Element */
                                            rsuint8 InfoElement[1]);
                                                             /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                Phoenix_PP_API_Types.doc)
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Infoelements:
                                                                [API_IE_CODECLIST]
                                                                [API_IE_MODEL_ID]
                                                                [API_IE_TERMCAPS] */

/****************************************************************************
* FUNCTION:      SendApiFpMmDeleteRegistration10Cfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_DELETE_REGISTRATION10_CFM = 0x4103
****************************************************************************/
void SendApiFpMmDeleteRegistration10Cfm ( RosTaskIdType Dst,
                                          RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not. */
                                          rsuint8 HandsetId);
                                                             /*!< Index of the handset
                                                                that shall be deleted. */

/****************************************************************************
* FUNCTION:      SendApiFpMmHandsetDeregistered10Ind
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_MM_HANDSET_DEREGISTERED10_IND = 0x410F
****************************************************************************/
void SendApiFpMmHandsetDeregistered10Ind ( RosTaskIdType Dst,
                                           rsuint8 HandsetId);
                                                             /*!< Index of the handset
                                                                that has been deleted. */

#ifdef __cplusplus
}
#endif
#endif /*APIFPMM10MPS_H */


