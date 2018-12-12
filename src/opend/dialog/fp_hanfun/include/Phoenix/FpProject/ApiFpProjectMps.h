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
#ifndef APIFPPROJECTMPS_H
#define APIFPPROJECTMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/FpProject/ApiFpProject.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiFpSetLedCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_LED_CFM = 0x400D
****************************************************************************/
void SendApiFpSetLedCfm ( RosTaskIdType Dst,
                          RsStatusType Status);              /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpSetRegisterCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_REGISTER_CFM = 0x400F
****************************************************************************/
void SendApiFpSetRegisterCfm ( RosTaskIdType Dst,
                               RsStatusType Status);         /*!< Indicates whether the
                                                                command succeeded or not. */

/****************************************************************************
* FUNCTION:      SendApiFpGetRegisterCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_REGISTER_CFM = 0x4011
****************************************************************************/
void SendApiFpGetRegisterCfm ( RosTaskIdType Dst,
                               RsStatusType Status,          /*!< Indicates whether the
                                                                command succeeded or not. */
                               rsuint32 RegisterAddress,     /*!< The address of the
                                                                register. */
                               rsuint16 Data);               /*!< The data read from the
                                                                register. */

/****************************************************************************
* FUNCTION:      SendApiFpSetEepromCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_SET_EEPROM_CFM = 0x4013
****************************************************************************/
void SendApiFpSetEepromCfm ( RosTaskIdType Dst,
                             RsStatusType Status,            /*!< Indicates whether the
                                                                command succeeded or not. */
                             rsuint16 Address,               /*!< Offset in the EEPROM */
                             rsuint8 DataLength);            /*!< The number of bytes
                                                                written to the EEPROM. */

/****************************************************************************
* FUNCTION:      SendApiFpGetEepromCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_EEPROM_CFM = 0x4015
****************************************************************************/
void SendApiFpGetEepromCfm ( RosTaskIdType Dst,
                             RsStatusType Status,            /*!< Indicates whether the
                                                                command succeeded or not. */
                             rsuint16 Address,               /*!< Offset in the EEPROM. */
                             rsuint8 DataLength,             /*!< The number of bytes to
                                                                read from the EEPROM. */
                             rsuint8 Data[1]);               /*!< The data read from the
                                                                EEPROM. */

/****************************************************************************
* FUNCTION:      SendApiFpGetCodecListCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_GET_CODEC_LIST_CFM = 0x4017
****************************************************************************/
void SendApiFpGetCodecListCfm ( RosTaskIdType Dst,
                                ApiTerminalIdType HandsetId,  /*!< Indicates which HS. */
                                ApiRequestedCodeListType ApiRequestCodeList,
                                                             /*!< Indicates which codec
                                                                list to request. */
                                rsuint16 InfoElementLength,  /*!< The length in bytes of
                                                                the info element that should
                                                                be appended to the info
                                                                element memory block
                                                                (**IeBlockPtr). */
                                rsuint8 InfoElement[1]);     /*!< Pointer to the info
                                                                element data that should be appended.
                                                                This will always hold
                                                                [API_IE_CODEC_LIST] */

#ifdef __cplusplus
}
#endif
#endif /*APIFPPROJECTMPS_H */


