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
#ifndef APIPPMMMPS_H
#define APIPPMMMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/PpMm/ApiPpMm.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiPpMmGetIdCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_GET_ID_CFM = 0x5101
****************************************************************************/
void SendApiPpMmGetIdCfm ( RosTaskIdType Dst,
                           rsuint8 Id[5]);                   /*!< The id of the PP. The
                                                                IPEI of the PP is used to
                                                                identify the PP. */

/****************************************************************************
* FUNCTION:      SendApiPpMmGetModelCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_GET_MODEL_CFM = 0x5103
****************************************************************************/
void SendApiPpMmGetModelCfm ( RosTaskIdType Dst,
                              ApiModelIdType ModelId);       /*!< The manufacture
                                                                (MANIC) and model (MODIC)
                                                                code of the PP. The EMC code
                                                                of the PP is used as
                                                                manufacture code. */

/****************************************************************************
* FUNCTION:      SendApiPpMmReadRssiCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_READ_RSSI_CFM = 0x5105
****************************************************************************/
void SendApiPpMmReadRssiCfm ( RosTaskIdType Dst,
                              rsuint8 Rssi);                 /*!< RSSI (Radio Signal
                                                                Strength Indication)
                                                                Legal values [0x00-0x3F]
                                                                0x00: equals no
                                                                connection/connection lost,
                                                                0x3F: equals full signal. 
                                                                
                                                                The RSSI is operational in
                                                                both onhook and offhook
                                                                mode. */

/****************************************************************************
* FUNCTION:      SendApiPpMmSetTermcapCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_SET_TERMCAP_CFM = 0x5126
****************************************************************************/
void SendApiPpMmSetTermcapCfm ( RosTaskIdType Dst,
                                RsStatusType Status);        /*!< Indicates whether the
                                                                command succeeded or not.
                                                                RsStatusType is defined in
                                                                the ROS */

/****************************************************************************
* FUNCTION:      SendApiPpMmGetTermcapCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_GET_TERMCAP_CFM = 0x5128
****************************************************************************/
void SendApiPpMmGetTermcapCfm ( RosTaskIdType Dst,
                                RsStatusType Status,         /*!< Indicates whether the
                                                                command succeeded or not.
                                                                RsStatusType is defined in
                                                                the ROS */
                                rsuint16 InfoElementLength,  /*!< The length of the Data
                                                                Information Element */
                                rsuint8 InfoElement[1]);     /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                "Phoenix_API_Types.doc")
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Infoelements:
                                                                [API_IE_TERMCAPS] */

/****************************************************************************
* FUNCTION:      SendApiPpMmLockedInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_LOCKED_IND = 0x5108
****************************************************************************/
void SendApiPpMmLockedInd ( RosTaskIdType Dst,
                            rsuint8 SubscriptionNo,          /*!< Indicates the index of
                                                                the locked FP in the
                                                                registration database. */
                            rsuint8 FpCapBit24_31,           /*!< bit0: a31 Conference
                                                                bit1: a30 Permanent CLIR
                                                                bit2: a29 NG-DECT extended
                                                                wideband voice
                                                                bit3-6: a25-a28 DPRS
                                                                bit7: a24 NG-DECT wideband
                                                                voice */
                            rsuint8 FpCapBit32_39,           /*!< bit0: a39 Reserved
                                                                bit1: a38 Reserved
                                                                bit2: a37 Reserved
                                                                bit3: a36 Reserved
                                                                bit4: a35 No emission
                                                                bit5: a34 Multiple lines
                                                                bit6: a33 Call deflection
                                                                bit7: a32 Call intrusion */
                            rsuint8 FpCapBit40_47,           /*!< bit0: a47 Reserved
                                                                bit1: a46 Reserved
                                                                bit2: a45 Light data services
                                                                bit3: a44 Reserved
                                                                bit4: a43 Reserved
                                                                bit5: a42 Early encryption
                                                                bit6: a41 Reserved
                                                                bit7: a40 Reserved */
                            rsuint16 InfoElementLength,      /*!< The length of the Data
                                                                Information Element */
                            rsuint8 InfoElement[1]);         /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                CodecList is only included
                                                                when coming from a Locate Accept.
                                                                Expected Infoelements:
                                                                [IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiPpMmUnlockedInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_UNLOCKED_IND = 0x5109
****************************************************************************/
void SendApiPpMmUnlockedInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpMmEasyPairingSearchCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_EASY_PAIRING_SEARCH_CFM = 0x5122
****************************************************************************/
void SendApiPpMmEasyPairingSearchCfm ( RosTaskIdType Dst,
                                       rsuint8 Rfpi[5],      /*!< The RFPI (Radio Fixed
                                                                Part Identifier) of the
                                                                found FP */
                                       rsuint8 FpCapBit24_31,
                                                             /*!< bit0: a31 Conference
                                                                bit1: a30 Permanent CLIR
                                                                bit2: a29 NG-DECT extended
                                                                wideband voice
                                                                bit3-6: a25-a28 DPRS
                                                                bit7: a24 NG-DECT wideband
                                                                voice */
                                       rsuint8 FpCapBit32_39,
                                                             /*!< bit0: a39 Reserved
                                                                bit1: a38 Reserved
                                                                bit2: a37 Reserved
                                                                bit3: a36 Reserved
                                                                bit4: a35 No emission
                                                                bit5: a34 Multiple lines
                                                                bit6: a33 Call deflection
                                                                bit7: a32 Call intrusion */
                                       rsuint8 FpCapBit40_47);
                                                             /*!< bit0: a47 Reserved
                                                                bit1: a46 Reserved
                                                                bit2: a45 Light data services
                                                                bit3: a44 Reserved
                                                                bit4: a43 Reserved
                                                                bit5: a42 Early encryption
                                                                bit6: a41 Reserved
                                                                bit7: a40 Reserved */

/****************************************************************************
* FUNCTION:      SendApiPpMmRegistrationSearchInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_REGISTRATION_SEARCH_IND = 0x510D
****************************************************************************/
void SendApiPpMmRegistrationSearchInd ( RosTaskIdType Dst,
                                        rsuint8 Rfpi[5],     /*!< The RFPI (Radio Fixed
                                                                Part Identifier) of the
                                                                found FP */
                                        rsuint8 FpCapBit24_31,
                                                             /*!< bit0: a31 Conference
                                                                bit1: a30 Permanent CLIR
                                                                bit2: a29 NG-DECT extended
                                                                wideband voice
                                                                bit3-6: a25-a28 DPRS
                                                                bit7: a24 NG-DECT wideband
                                                                voice */
                                        rsuint8 FpCapBit32_39,
                                                             /*!< bit0: a39 Reserved
                                                                bit1: a38 Reserved
                                                                bit2: a37 Reserved
                                                                bit3: a36 Reserved
                                                                bit4: a35 No emission
                                                                bit5: a34 Multiple lines
                                                                bit6: a33 Call deflection
                                                                bit7: a32 Call intrusion */
                                        rsuint8 FpCapBit40_47);
                                                             /*!< bit0: a47 Reserved
                                                                bit1: a46 Reserved
                                                                bit2: a45 Light data services
                                                                bit3: a44 Reserved
                                                                bit4: a43 Reserved
                                                                bit5: a42 Early encryption
                                                                bit6: a41 Reserved
                                                                bit7: a40 Reserved */

/****************************************************************************
* FUNCTION:      SendApiPpMmRegistrationCompleteInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_REGISTRATION_COMPLETE_IND = 0x5110
****************************************************************************/
void SendApiPpMmRegistrationCompleteInd ( RosTaskIdType Dst,
                                          rsuint8 HandsetId,  /*!< Id of the handset
                                                                 that was registered to the
                                                                 API. */
                                          rsbool KnownFp,    /*!< Returns if the unit is
                                                                a known (same manufactorer). 
                                                                This is useful in the DECT
                                                                version where you can
                                                                register the PP to other
                                                                manufacturer FP's.
                                                                It is judged on the
                                                                FixedEMC and returns
                                                                1: Same Manufactorer ID in FP/PP
                                                                0: Different Manufactorer
                                                                ID in FP/PP */
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
                                                                following the ApiInfoElementType.
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Infoelements:
                                                                [IE_CODEC_LIST] */

/****************************************************************************
* FUNCTION:      SendApiPpMmRegistrationFailedInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_REGISTRATION_FAILED_IND = 0x5111
****************************************************************************/
void SendApiPpMmRegistrationFailedInd ( RosTaskIdType Dst,
                                        ApiMmRejectReasonType Reason);
                                                             /*!< Reason of the failed
                                                                registration */

/****************************************************************************
* FUNCTION:      SendApiPpMmDeleteLocalRegistrationCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_DELETE_LOCAL_REGISTRATION_CFM = 0x5115
****************************************************************************/
void SendApiPpMmDeleteLocalRegistrationCfm ( RosTaskIdType Dst,
                                             RsStatusType Status,
                                                             /*!< Indicates whether the
                                                                command succeeded or not.
                                                                RsStatusType is defined in
                                                                the ROS */
                                             rsuint8 SubscriptionNo);
                                                             /*!< Indicates the index in
                                                                the PP subscription database
                                                                where the registrations data
                                                                has been deleted. */

/****************************************************************************
* FUNCTION:      SendApiPpMmUpiAuthenticateInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_UPI_AUTHENTICATE_IND = 0x5117
****************************************************************************/
void SendApiPpMmUpiAuthenticateInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpMmAccRightsTermInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_ACC_RIGHTS_TERM_IND = 0x511B
****************************************************************************/
void SendApiPpMmAccRightsTermInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpMmUnitdataInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_UNITDATA_IND = 0x5119
****************************************************************************/
void SendApiPpMmUnitdataInd ( RosTaskIdType Dst,
                              rsuint16 InfoElementLength,    /*!< The length of the Data
                                                                Information Element */
                              rsuint8 InfoElement[1]);       /*!< The InfoElementList
                                                                can hold a number Info
                                                                Elements placed in the in
                                                                the format
                                                                
                                                                { Ie, IeLength, IeData[],
                                                                Ie, IeLength, IeData[], ...} 
                                                                
                                                                Each element is packed
                                                                following the 
                                                                ApiInfoElementType (which
                                                                is defined in the
                                                                "Phoenix_API_Types.doc")
                                                                
                                                                At reception the receiving
                                                                task should search through
                                                                the info data package to
                                                                search for the requested
                                                                elements and pick out the
                                                                info data.
                                                                
                                                                Expected Infoelements:
                                                                [API_IE_UNITDATA] */

/****************************************************************************
* FUNCTION:      SendApiPpMmAlertBroadcastInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_ALERT_BROADCAST_IND = 0x511A
****************************************************************************/
void SendApiPpMmAlertBroadcastInd ( RosTaskIdType Dst,
                                    ApiMmSignalType Signal);  /*!< Alert signal. Can be
                                                                 used to control which
                                                                 ringer melody is used at
                                                                 Called endpoint.
                                                                 
                                                                 The possible signal types
                                                                 are defined in
                                                                 ApiMmSignalType (which is
                                                                 defined in the
                                                                 "Phoenix_API_Types.doc")
                                                                  */

/****************************************************************************
* FUNCTION:      SendApiPpMmFpNameInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_FP_NAME_IND = 0x511D
****************************************************************************/
void SendApiPpMmFpNameInd ( RosTaskIdType Dst,
                            rsuint8 FpNameLength,            /*!< The length of the
                                                                received Fp name */
                            rsuint8 FpName[1]);              /*!< The received FP name.
                                                                Can hold from 0 to 17 chars */

/****************************************************************************
* FUNCTION:      SendApiPpMmEncryptionNotStartedInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_ENCRYPTION_NOT_STARTED_IND = 0x511E
****************************************************************************/
void SendApiPpMmEncryptionNotStartedInd ( RosTaskIdType Dst );


/****************************************************************************
* FUNCTION:      SendApiPpMmGetExtHigherLayerCap2Cfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_GET_EXT_HIGHER_LAYER_CAP2_CFM = 0x5120
****************************************************************************/
void SendApiPpMmGetExtHigherLayerCap2Cfm ( RosTaskIdType Dst,
                                           rsuint8 FpCapBit24_31,
                                                             /*!< bit0: a31 Conference
                                                                bit1: a30 Permanent CLIR
                                                                bit2: a29 NG-DECT extended
                                                                wideband voice
                                                                bit3-6: a25-a28 DPRS
                                                                bit7: a24 NG-DECT wideband
                                                                voice */
                                           rsuint8 FpCapBit32_39,
                                                             /*!< bit0: a39 Reserved
                                                                bit1: a38 Reserved
                                                                bit2: a37 Reserved
                                                                bit3: a36 Reserved
                                                                bit4: a35 No emission
                                                                bit5: a34 Multiple lines
                                                                bit6: a33 Call deflection
                                                                bit7: a32 Call intrusion */
                                           rsuint8 FpCapBit40_47);
                                                             /*!< bit0: a47 Reserved
                                                                bit1: a46 Reserved
                                                                bit2: a45 Light data services
                                                                bit3: a44 Reserved
                                                                bit4: a43 Reserved
                                                                bit5: a42 Early encryption
                                                                bit6: a41 Reserved
                                                                bit7: a40 Reserved */

/****************************************************************************
* FUNCTION:      SendApiPpMmGetSubscriptionRfpiCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_MM_GET_SUBSCRIPTION_RFPI_CFM = 0x5124
****************************************************************************/
void SendApiPpMmGetSubscriptionRfpiCfm ( RosTaskIdType Dst,
                                         rsuint8 SubscriptionNo,
                                                             /*!< The subscription
                                                                number indicated the index
                                                                in the subscription
                                                                database. [1..4] */
                                         rsuint8 Rfpi[5]);   /*!< The RFPI (Radio Fixed
                                                                Part Identifier) of the
                                                                selected subscription. */

#ifdef __cplusplus
}
#endif
#endif /*APIPPMMMPS_H */


