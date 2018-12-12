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
#ifndef APIHALMPS_H
#define APIHALMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Hal/ApiHAL.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiHalDeviceControlCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_DEVICE_CONTROL_CFM = 0x5901
****************************************************************************/
void SendApiHalDeviceControlCfm ( RosTaskIdType Dst,
                                  RsStatusType Status,       /*!< Status for the request.
                                                                RSS_SUCCESS: Success.
                                                                RSS_NOT_SUPPORTED: The
                                                                device does not support the
                                                                control requested.
                                                                RSS_NOT_FOUND: No such
                                                                device. */
                                  ApiHalDeviceIdType DeviceId,
                                                             /*!< Device ID. */
                                  ApiHalDeviceControlType Control);
                                                             /*!< Type of control. */

/****************************************************************************
* FUNCTION:      SendApiHalLedCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_LED_CFM = 0x5903
****************************************************************************/
void SendApiHalLedCfm ( RosTaskIdType Dst,
                        RsStatusType Status);                /*!< Status for the request.
                                                                RSS_SUCCESS: Success.
                                                                RSS_NO_DEVICE: The LED
                                                                requested does not exist. */

/****************************************************************************
* FUNCTION:      SendApiHalReadCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_READ_CFM = 0x5905
****************************************************************************/
void SendApiHalReadCfm ( RosTaskIdType Dst,
                         RsStatusType Status,                /*!< Status for the request.
                                                                RSS_SUCCESS: Success.
                                                                RSS_NO_DEVICE: The area
                                                                specified is invalid.
                                                                RSS_BAD_ADDRESS: The
                                                                address specified is not
                                                                valid for the area.
                                                                RSS_BAD_LENGTH: The length
                                                                specified is not valid for
                                                                the area. */
                         ApiHalAreaType Area,                /*!< Identification of the
                                                                addressing area. */
                         rsuint32 Address,                   /*!< Address within the
                                                                area. */
                         rsuint16 Length,                    /*!< Number of bytes read. */
                         rsuint8 Data[1]);                   /*!< Data that was read. */

/****************************************************************************
* FUNCTION:      SendApiHalWriteCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_WRITE_CFM = 0x5907
****************************************************************************/
void SendApiHalWriteCfm ( RosTaskIdType Dst,
                          RsStatusType Status,               /*!< Status for the request.
                                                                RSS_SUCCESS: Success.
                                                                RSS_NO_DEVICE: The area
                                                                specified is invalid.
                                                                RSS_BAD_ADDRESS: The
                                                                address specified is not
                                                                valid for the area. */
                          ApiHalAreaType Area,               /*!< Identification of the
                                                                addressing area. */
                          rsuint32 Address,                  /*!< Address within the
                                                                area. */
                          rsuint16 Length);                  /*!< Number of bytes
                                                                written. */

/****************************************************************************
* FUNCTION:      SendApiHalGpioFnRegisterCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_GPIO_FN_REGISTER_CFM=0x5911
****************************************************************************/
void SendApiHalGpioFnRegisterCfm ( RosTaskIdType Dst,
                                   ApiHalGpioFnType* ApiHalGetGpioFn);
                                                             /*!<  */

/****************************************************************************
* FUNCTION:      SendApiHalSetGpioPortPinModeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_SET_GPIO_PORT_PIN_MODE_CFM=0x5913
****************************************************************************/
void SendApiHalSetGpioPortPinModeCfm ( RosTaskIdType Dst,
                                       RsStatusType Status,  /*!< Status for the request.
                                                                RSS_SUCCESS: Success.
                                                                RSS_NO_RESOURCE: The port
                                                                is not valid */
                                       ApiHalGpioPortPinType PortPin);
                                                             /*!< Port pin identifier
                                                                High nibble indicates Port,
                                                                low nibble indicates Pin */

/****************************************************************************
* FUNCTION:      SendApiHalSetGpioPortCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_SET_GPIO_PORT_CFM=0x5915
****************************************************************************/
void SendApiHalSetGpioPortCfm ( RosTaskIdType Dst,
                                RsStatusType Status,         /*!< Status for the request.
                                                                RSS_SUCCESS: Success.
                                                                RSS_NO_RESOURCE: The port
                                                                is not valid */
                                ApiHalGpioPortType Port,     /*!< GPIO port identifier */
                                rsuint16 value);             /*!< Port value (bitmasked
                                                                for entire port) */

/****************************************************************************
* FUNCTION:      SendApiHalResetGpioPortCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_RESET_GPIO_PORT_CFM=0x5917
****************************************************************************/
void SendApiHalResetGpioPortCfm ( RosTaskIdType Dst,
                                  RsStatusType Status,       /*!< Status for the request.
                                                                RSS_SUCCESS: Success.
                                                                RSS_NO_RESOURCE: The port
                                                                is not valid */
                                  ApiHalGpioPortType Port,   /*!< GPIO port identifier */
                                  rsuint16 value);           /*!< Port value (bitmasked
                                                                for entire port) */

/****************************************************************************
* FUNCTION:      SendApiHalGetGpioPortCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_GET_GPIO_PORT_CFM=0x5919
****************************************************************************/
void SendApiHalGetGpioPortCfm ( RosTaskIdType Dst,
                                RsStatusType Status,         /*!< Status for the request.
                                                                RSS_SUCCESS: Success.
                                                                RSS_NO_RESOURCE: The port
                                                                is not valid */
                                ApiHalGpioPortType Port,     /*!< GPIO port identifier */
                                rsuint16 value);             /*!< Port value (bitmasked
                                                                for entire port) */

#ifdef __cplusplus
}
#endif
#endif /*APIHALMPS_H */


