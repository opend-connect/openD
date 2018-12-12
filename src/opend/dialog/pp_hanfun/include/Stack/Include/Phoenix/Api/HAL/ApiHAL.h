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
* Definition of the ApiHal interface.
*/


#ifndef APIHAL_H
#define APIHAL_H

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

/* Mail primitives:
  API_HAL_DEVICE_CONTROL_REQ = 0x5900,
  API_HAL_DEVICE_CONTROL_CFM = 0x5901,
  API_HAL_LED_REQ = 0x5902,
  API_HAL_LED_CFM = 0x5903,
  API_HAL_READ_REQ = 0x5904,
  API_HAL_READ_CFM = 0x5905,
  API_HAL_WRITE_REQ = 0x5906,
  API_HAL_WRITE_CFM = 0x5907,
  API_HAL_GPIO_FN_REGISTER_REQ=0x5910,
  API_HAL_GPIO_FN_REGISTER_CFM=0x5911,
  API_HAL_SET_GPIO_PORT_PIN_MODE_REQ=0x5912,
  API_HAL_SET_GPIO_PORT_PIN_MODE_CFM=0x5913,
  API_HAL_SET_GPIO_PORT_REQ=0x5914,
  API_HAL_SET_GPIO_PORT_CFM=0x5915,
  API_HAL_RESET_GPIO_PORT_REQ=0x5916,
  API_HAL_RESET_GPIO_PORT_CFM=0x5917,
  API_HAL_GET_GPIO_PORT_REQ=0x5918,
  API_HAL_GET_GPIO_PORT_CFM=0x5919,
  API_HAL_GET_ADC_REQ=0x5920,
  API_HAL_GET_ADC_CFM=0x5921,
End of mail primitives. */



/*! This enum defines device IDs. */
typedef enum RSENUMTAG(ApiHalDeviceIdType)
{
  AHD_NONE,   /*!< No device. */
  AHD_UART1,  /*!< UART 1. */
  AHD_UART2,  /*!< UART 2. */
  AHD_SPI1,   /*!< SPI 1. */
  AHD_SPI2,   /*!< SPI 2. */
  AHD_TIM0,   /*!< HW Timer 0 */
  AHD_MAX     /*!<  */
} RSENUM8(ApiHalDeviceIdType);

/*! This enum defines device controls. */
typedef enum RSENUMTAG(ApiHalDeviceControlType)
{
  AHC_NULL,     /*!< No control. */
  AHC_DISABLE,  /*!< Disable system device driver. A Co-located application
                   may then use the hardware. */
  AHC_ENABLE,   /*!< Enable system device driver. */
  AHC_MAX       /*!<  */
} RSENUM8(ApiHalDeviceControlType);

/*! This enum defines the LED commands supported. */
typedef enum RSENUMTAG(ApiHalLedCmdIdType)
{
  ALI_LED_OFF         = 0x00, /*!< LED off */
  ALI_LED_ON          = 0x01, /*!< LED on. */
  ALI_REPEAT_SEQUENCE = 0x02, /*!< Repeat the LED sequence. */
  ALI_INVALID         = 0xFF  /*!< 0x03- 0xFF is invalid. */
} RSENUM8(ApiHalLedCmdIdType);

/*! This struct is used to hold one LED command. */
typedef struct 
{
  ApiHalLedCmdIdType  Command;          /*!< The LED command */
  rsuint16  Duration;                   /*!< The duration in ms for ALI_LED_OFF and
                                           ALI_LED_ON. 0 = no delay/timeout.
                                           The number of times to repeat the sequence for
                                           ALI_REPEAT_SEQUENCE. 0xFFFF = repeat forever. */
} ApiHalLedCmdType;

/*! This enum defines (memory) areas. */
typedef enum RSENUMTAG(ApiHalAreaType)
{
  AHA_MEMORY    = 0x00, /*!< Memory mapped area e.g. RAM, flash. */
  AHA_REGISTER  = 0x01, /*!< Registers. Length must be 1/2/4 bytes for 8/16/32-bits
                           access. */
  AHA_NVS       = 0x02, /*!< Non-Volatile Storage (EEPROM). */
  AHA_DSP       = 0x03, /*!< DSP. */
  AHA_FPGA      = 0x04, /*!< FPGA. */
  AHA_SEQUENCER = 0x05, /*!< Sequencer (DIP). */
} RSENUM8(ApiHalAreaType);

/*! GPIO port pin mode identifiers */
typedef enum RSENUMTAG(ApiHalGpioPortPinModeType)
{
  GPIO_PORT_PIN_MODE_INPUT           = 0x00, /*!< Input, no resistors selected */
  GPIO_PORT_PIN_MODE_INPUT_PULL_UP   = 0x01, /*!< Input, pull-up selected */
  GPIO_PORT_PIN_MODE_INPUT_PULL_DOWN = 0x02, /*!< Input, pull-down selected */
  GPIO_PORT_PIN_MODE_OUTPUT          = 0x03, /*!< Output, no resistors selected */
} RSENUM8(ApiHalGpioPortPinModeType);

/*! GPIO port pin identifiers
    High nibble selects Port, Low nibble selects Pin */
typedef enum RSENUMTAG(ApiHalGpioPortPinType)
{
  GPIO_PORT_P0_0    = 0x00, /*!< GPIO hw port pin */
  GPIO_PORT_P0_1    = 0x01, /*!<  */
  GPIO_PORT_P0_2    = 0x02, /*!<  */
  GPIO_PORT_P0_3    = 0x03, /*!<  */
  GPIO_PORT_P0_4    = 0x04, /*!<  */
  GPIO_PORT_P0_5    = 0x05, /*!<  */
  GPIO_PORT_P0_6    = 0x06, /*!<  */
  GPIO_PORT_P0_7    = 0x07, /*!<  */
  GPIO_PORT_P0_8    = 0x08, /*!<  */
  GPIO_PORT_P0_9    = 0x09, /*!<  */
  GPIO_PORT_P0_10   = 0x0A, /*!<  */
  GPIO_PORT_P0_11   = 0x0B, /*!<  */
  GPIO_PORT_P0_12   = 0x0C, /*!<  */
  GPIO_PORT_P0_13   = 0x0D, /*!<  */
  GPIO_PORT_P0_14   = 0x0E, /*!<  */
  GPIO_PORT_P0_15   = 0x0F, /*!<  */
  GPIO_PORT_P1_0    = 0x10, /*!<  */
  GPIO_PORT_P1_1    = 0x11, /*!<  */
  GPIO_PORT_P1_2    = 0x12, /*!<  */
  GPIO_PORT_P1_3    = 0x13, /*!<  */
  GPIO_PORT_P1_4    = 0x14, /*!<  */
  GPIO_PORT_P1_5    = 0x15, /*!<  */
  GPIO_PORT_P1_6    = 0x16, /*!<  */
  GPIO_PORT_P1_7    = 0x17, /*!<  */
  GPIO_PORT_P1_8    = 0x18, /*!<  */
  GPIO_PORT_P1_9    = 0x19, /*!<  */
  GPIO_PORT_P1_10   = 0x1A, /*!<  */
  GPIO_PORT_P1_11   = 0x1B, /*!<  */
  GPIO_PORT_P1_12   = 0x1C, /*!<  */
  GPIO_PORT_P1_13   = 0x1D, /*!<  */
  GPIO_PORT_P1_14   = 0x1E, /*!<  */
  GPIO_PORT_P1_15   = 0x1F, /*!<  */
  GPIO_PORT_P2_0    = 0x20, /*!<  */
  GPIO_PORT_P2_1    = 0x21, /*!<  */
  GPIO_PORT_P2_2    = 0x22, /*!<  */
  GPIO_PORT_P2_3    = 0x23, /*!<  */
  GPIO_PORT_P2_4    = 0x24, /*!<  */
  GPIO_PORT_P2_5    = 0x25, /*!<  */
  GPIO_PORT_P2_6    = 0x26, /*!<  */
  GPIO_PORT_P2_7    = 0x27, /*!<  */
  GPIO_PORT_P2_8    = 0x28, /*!<  */
  GPIO_PORT_P2_9    = 0x29, /*!<  */
  GPIO_PORT_P2_10   = 0x2A, /*!<  */
  GPIO_PORT_P2_11   = 0x2B, /*!<  */
  GPIO_PORT_P2_12   = 0x2C, /*!<  */
  GPIO_PORT_P2_13   = 0x2D, /*!<  */
  GPIO_PORT_P2_14   = 0x2E, /*!<  */
  GPIO_PORT_P2_15   = 0x2F, /*!<  */
  GPIO_PORT_P3_0    = 0x30, /*!<  */
  GPIO_PORT_P3_1    = 0x31, /*!<  */
  GPIO_PORT_P3_2    = 0x32, /*!<  */
  GPIO_PORT_P3_3    = 0x33, /*!<  */
  GPIO_PORT_P3_4    = 0x34, /*!<  */
  GPIO_PORT_P3_5    = 0x35, /*!<  */
  GPIO_PORT_P3_6    = 0x36, /*!<  */
  GPIO_PORT_P3_7    = 0x37, /*!<  */
  GPIO_PORT_P3_8    = 0x38, /*!<  */
  GPIO_PORT_P3_9    = 0x39, /*!<  */
  GPIO_PORT_P3_10   = 0x3A, /*!<  */
  GPIO_PORT_P3_11   = 0x3B, /*!<  */
  GPIO_PORT_P3_12   = 0x3C, /*!<  */
  GPIO_PORT_P3_13   = 0x3D, /*!<  */
  GPIO_PORT_P3_14   = 0x3E, /*!<  */
  GPIO_PORT_P3_15   = 0x3F, /*!<  */
  GPIO_PORT_INVALID = 0xFF, /*!<  */
} RSENUM8(ApiHalGpioPortPinType);

/*! GPIO port pin identifiers */
typedef enum RSENUMTAG(ApiHalGpioPortType)
{
  GPIO_PORT_P0 = 0x00, /*!< GPIO hw port */
  GPIO_PORT_P1 = 0x01, /*!<  */
  GPIO_PORT_P2 = 0x02, /*!<  */
  GPIO_PORT_P3 = 0x03, /*!<  */
} RSENUM8(ApiHalGpioPortType);

/*! GPIO pin identifiers
    Defines for pin bitmasking */
typedef enum RSENUMTAG(ApiHalGpioPinType)
{
  GPIO_PIN_0 = 0x01, /*!< GPIO hw pin */
  GPIO_PIN_1 = 0x02, /*!<  */
  GPIO_PIN_2 = 0x04, /*!<  */
  GPIO_PIN_3 = 0x08, /*!<  */
  GPIO_PIN_4 = 0x10, /*!<  */
  GPIO_PIN_5 = 0x20, /*!<  */
  GPIO_PIN_6 = 0x40, /*!<  */
  GPIO_PIN_7 = 0x80, /*!<  */
} RSENUM8(ApiHalGpioPinType);

/*! API function type used in direct port access */
typedef RsStatusType (*ApiHalGpioPortPinModeReqFnType)( ApiHalGpioPortPinType PortPin, ApiHalGpioPortPinModeType PortPinMode);

/*! API function type used in direct port access through function call */
typedef RsStatusType (*ApiHalSetGpioPortReqFnType)( ApiHalGpioPortType Port, rsuint16 Value);

/*! API function type used in direct port access through function call */
typedef RsStatusType (*ApiHalResetGpioPortReqFnType)( ApiHalGpioPortType Port, rsuint16 Value);

/*! API function type used in direct port access through function call */
typedef ApiHalGpioPortType (*ApiHalGetGpioPortReqFnType)( ApiHalGpioPortType Port);

/*! API function type used in direct port access through function call 
    Used to hand direct port accesses function pointers to the application. */
typedef struct ApiHalGpioFnType
{
  ApiHalGpioPortPinModeReqFnType  PortPinModeReqFn;
  ApiHalSetGpioPortReqFnType  SetGpioPortReqFn;
  ApiHalResetGpioPortReqFnType  ResetGpioPortReqFn;
  ApiHalGetGpioPortReqFnType  GetGpioPortReqFn;
} ApiHalGpioFnType;

/*! This enum defines ADC id. */
typedef enum RSENUMTAG(ApiHalAdcIdType)
{
  ADC_0                        = 0x00, /*!<  */
  ADC_1                        = 0x01, /*!<  */
  ADC_2                        = 0x02, /*!<  */
  CALLER_ID_OUTPUT_AS_INPUT    = 0x03, /*!<  */
  CODEC_HEADSET_DETECTION      = 0x04, /*!<  */
  RINGING_OPAMP                = 0x05, /*!<  */
  VBAT                         = 0x05, /*!<  */
  TEMPERATURE_SENSOR           = 0x06, /*!<  */
  PARALLEL_SET_DETECTION_OPAMP = 0x07, /*!<  */
  MAX_ADC_ENTRIES              = 0x08, /*!<  */
} RSENUM8(ApiHalAdcIdType);


/*! Mail without parameters. */
typedef struct ApihalEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApihalEmptySignalType;

/*! This mail is sent from the application to control a device (driver).
    It is intended for the application (usually a COLA application) to disable
   a specific device driver (together with the interrupt used). The
   application can then takes over and use its own driver with a custom
   interrupt handler. */
typedef struct ApiHalDeviceControlReqType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_DEVICE_CONTROL_REQ = 0x5900 */
  ApiHalDeviceIdType DeviceId;          /*!< Device ID. */
  ApiHalDeviceControlType Control;      /*!< Type of control. */
} ApiHalDeviceControlReqType;

/*! Control confirmation. */
typedef struct ApiHalDeviceControlCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_DEVICE_CONTROL_CFM = 0x5901 */
  RsStatusType Status;                  /*!< Status for the request.
                                           RSS_SUCCESS: Success.
                                           RSS_NOT_SUPPORTED: The device does not support
                                           the control requested.
                                           RSS_NOT_FOUND: No such device. */
  ApiHalDeviceIdType DeviceId;          /*!< Device ID. */
  ApiHalDeviceControlType Control;      /*!< Type of control. */
} ApiHalDeviceControlCfmType;

/*! This command is used to control the LEDs on the CVM. The CVM can store
   one command sequence for each of the LEDs. */
typedef struct ApiHalLedReqType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_LED_REQ = 0x5902 */
  rsuint8 LedNr;                        /*!< The LED for which this command applies
                                           (1..N). */
  rsuint8 CmdCount;                     /*!< The number of LED commands in the
                                           Commands[] parameter. */
  ApiHalLedCmdType Commands[1];         /*!< CmdCount number of LED commands. */
} ApiHalLedReqType;

/*! This mail is used to confirm the API_HAL_LED_REQ command. */
typedef struct ApiHalLedCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_LED_CFM = 0x5903 */
  RsStatusType Status;                  /*!< Status for the request.
                                           RSS_SUCCESS: Success.
                                           RSS_NO_DEVICE: The LED requested does not exist. */
} ApiHalLedCfmType;

/*! This command is used to read data from the CVM module. */
typedef struct ApiHalReadReqType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_READ_REQ = 0x5904 */
  ApiHalAreaType Area;                  /*!< Identification of the addressing area. */
  rsuint32 Address;                     /*!< Address within the area. */
  rsuint16 Length;                      /*!< Number of bytes to read. The actual number
                                           of bytes returned may differ due to message size
                                           limits or alignment restrictions. */
} ApiHalReadReqType;

/*! This mail returns the data read. */
typedef struct ApiHalReadCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_READ_CFM = 0x5905 */
  RsStatusType Status;                  /*!< Status for the request.
                                           RSS_SUCCESS: Success.
                                           RSS_NO_DEVICE: The area specified is invalid.
                                           RSS_BAD_ADDRESS: The address specified is not
                                           valid for the area.
                                           RSS_BAD_LENGTH: The length specified is not
                                           valid for the area. */
  ApiHalAreaType Area;                  /*!< Identification of the addressing area. */
  rsuint32 Address;                     /*!< Address within the area. */
  rsuint16 Length;                      /*!< Number of bytes read. */
  rsuint8 Data[1];                      /*!< Data that was read. */
} ApiHalReadCfmType;

/*! This command is used to read data from the CVM module. */
typedef struct ApiHalWriteReqType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_WRITE_REQ = 0x5906 */
  ApiHalAreaType Area;                  /*!< Identification of the addressing area. */
  rsuint32 Address;                     /*!< Address within the area. */
  rsuint16 Length;                      /*!< Number of bytes to write. */
  rsuint8 Data[1];                      /*!< Data to write. */
} ApiHalWriteReqType;

/*! This mail returns status for the write request. */
typedef struct ApiHalWriteCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_WRITE_CFM = 0x5907 */
  RsStatusType Status;                  /*!< Status for the request.
                                           RSS_SUCCESS: Success.
                                           RSS_NO_DEVICE: The area specified is invalid.
                                           RSS_BAD_ADDRESS: The address specified is not
                                           valid for the area. */
  ApiHalAreaType Area;                  /*!< Identification of the addressing area. */
  rsuint32 Address;                     /*!< Address within the area. */
  rsuint16 Length;                      /*!< Number of bytes written. */
} ApiHalWriteCfmType;

/*! Used to request pointers to direct port access functions in the API */
typedef ApihalEmptySignalType ApiHalGpioFnRegisterReqType;

/*! Confirmation with requested pointers to direct port access functions in
   the API */
typedef struct ApiHalGpioFnRegisterCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_GPIO_FN_REGISTER_CFM=0x5911 */
  ApiHalGpioFnType* ApiHalGetGpioFn;
} ApiHalGpioFnRegisterCfmType;

/*! Set the selected pin to Gpio in the specified mode */
typedef struct ApiHalSetGpioPortPinModeReqType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_SET_GPIO_PORT_PIN_MODE_REQ=0x5912 */
  ApiHalGpioPortPinType PortPin;        /*!< Port pin identifier 
                                           High nibble selects Port, low nibble selects Pin */
  ApiHalGpioPortPinModeType PortPinMode; /*!< Selects the operation mode of the
                                             PortPin. 
                                             (Input, Output, PullUp or PullDown) */
} ApiHalSetGpioPortPinModeReqType;

/*! Confirmation about the specified GPIO */
typedef struct ApiHalSetGpioPortPinModeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_SET_GPIO_PORT_PIN_MODE_CFM=0x5913 */
  RsStatusType Status;                  /*!< Status for the request.
                                           RSS_SUCCESS: Success.
                                           RSS_NO_RESOURCE: The port is not valid */
  ApiHalGpioPortPinType PortPin;        /*!< Port pin identifier
                                           High nibble indicates Port, low nibble indicates
                                           Pin */
} ApiHalSetGpioPortPinModeCfmType;

/*! Set a  GPIO port. */
typedef struct ApiHalSetGpioPortReqType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_SET_GPIO_PORT_REQ=0x5914 */
  ApiHalGpioPortType Port;              /*!< GPIO port identifier */
  rsuint16 Value;                       /*!< port value: Bitmask of the GPIO pins to be
                                           set high. Unaddressed pins are left untouched in
                                           their original state. */
} ApiHalSetGpioPortReqType;

/*! Confirmation about the specified GPIO port
    Returns the actual value of the port, even if the port set was
   unsuccessful */
typedef struct ApiHalSetGpioPortCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_SET_GPIO_PORT_CFM=0x5915 */
  RsStatusType Status;                  /*!< Status for the request.
                                           RSS_SUCCESS: Success.
                                           RSS_NO_RESOURCE: The port is not valid */
  ApiHalGpioPortType Port;              /*!< GPIO port identifier */
  rsuint16 value;                       /*!< Port value (bitmasked for entire port) */
} ApiHalSetGpioPortCfmType;

/*! Resets a  GPIO port. */
typedef struct ApiHalResetGpioPortReqType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_RESET_GPIO_PORT_REQ=0x5916 */
  ApiHalGpioPortType Port;              /*!< GPIO port identifier */
  rsuint16 Value;                       /*!< port value: Bitmask of the GPIO pins to be
                                           reset low. Unaddressed pins are left untouched in
                                           their original state. */
} ApiHalResetGpioPortReqType;

/*! Confirmation about the specified GPIO port
    Returns the actual value of the port, even if the port set was
   unsuccessful */
typedef struct ApiHalResetGpioPortCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_RESET_GPIO_PORT_CFM=0x5917 */
  RsStatusType Status;                  /*!< Status for the request.
                                           RSS_SUCCESS: Success.
                                           RSS_NO_RESOURCE: The port is not valid */
  ApiHalGpioPortType Port;              /*!< GPIO port identifier */
  rsuint16 value;                       /*!< Port value (bitmasked for entire port) */
} ApiHalResetGpioPortCfmType;

/*! Request current status for aGPIO port */
typedef struct ApiHalGetGpioPortReqType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_GET_GPIO_PORT_REQ=0x5918 */
  ApiHalGpioPortType Port;              /*!< GPIO port identifier */
} ApiHalGetGpioPortReqType;

/*! Confirmation about the specified GPIO port */
typedef struct ApiHalGetGpioPortCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_GET_GPIO_PORT_CFM=0x5919 */
  RsStatusType Status;                  /*!< Status for the request.
                                           RSS_SUCCESS: Success.
                                           RSS_NO_RESOURCE: The port is not valid */
  ApiHalGpioPortType Port;              /*!< GPIO port identifier */
  rsuint16 value;                       /*!< Port value (bitmasked for entire port) */
} ApiHalGetGpioPortCfmType;

/*! Request ADC values */
typedef struct ApiHalGetAdcReqType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_GET_ADC_REQ=0x5920 */
  ApiHalAdcIdType ADCId;                /*!< Id of the ADC */
} ApiHalGetAdcReqType;

/*! Confirmation about the specified ADC value */
typedef struct ApiHalGetAdcCfmType
{
  RosPrimitiveType Primitive;            /*!< API_HAL_GET_ADC_CFM=0x5921 */
  RsStatusType Status;                  /*!< Status for the request.
                                           RSS_SUCCESS: Success.
                                           RSS_BUSY: The ADC busy */
  ApiHalAdcIdType ADCId;                /*!< Id of the ADC */
  rsuint16 value;                       /*!< ADC value */
} ApiHalGetAdcCfmType;

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
* FUNCTION:      SendApiHalDeviceControlReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_DEVICE_CONTROL_REQ = 0x5900
****************************************************************************/
void SendApiHalDeviceControlReq ( RosTaskIdType Src,
                                  ApiHalDeviceIdType DeviceId,
                                                             /*!< Device ID. */
                                  ApiHalDeviceControlType Control);
                                                             /*!< Type of control. */

/****************************************************************************
* FUNCTION:      SendApiHalLedReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_LED_REQ = 0x5902
****************************************************************************/
void SendApiHalLedReq ( RosTaskIdType Src,
                        rsuint8 LedNr,                       /*!< The LED for which this
                                                                command applies (1..N). */
                        rsuint8 CmdCount,                    /*!< The number of LED
                                                                commands in the Commands[]
                                                                parameter. */
                        ApiHalLedCmdType Commands[1]);       /*!< CmdCount number of LED
                                                                commands. */

/****************************************************************************
* FUNCTION:      SendApiHalReadReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_READ_REQ = 0x5904
****************************************************************************/
void SendApiHalReadReq ( RosTaskIdType Src,
                         ApiHalAreaType Area,                /*!< Identification of the
                                                                addressing area. */
                         rsuint32 Address,                   /*!< Address within the
                                                                area. */
                         rsuint16 Length);                   /*!< Number of bytes to
                                                                read. The actual number of
                                                                bytes returned may differ
                                                                due to message size limits
                                                                or alignment restrictions. */

/****************************************************************************
* FUNCTION:      SendApiHalWriteReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_WRITE_REQ = 0x5906
****************************************************************************/
void SendApiHalWriteReq ( RosTaskIdType Src,
                          ApiHalAreaType Area,               /*!< Identification of the
                                                                addressing area. */
                          rsuint32 Address,                  /*!< Address within the
                                                                area. */
                          rsuint16 Length,                   /*!< Number of bytes to
                                                                write. */
                          rsuint8 Data[1]);                  /*!< Data to write. */

/****************************************************************************
* FUNCTION:      SendApiHalGpioFnRegisterReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_GPIO_FN_REGISTER_REQ=0x5910
****************************************************************************/
void SendApiHalGpioFnRegisterReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiHalSetGpioPortPinModeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_SET_GPIO_PORT_PIN_MODE_REQ=0x5912
****************************************************************************/
void SendApiHalSetGpioPortPinModeReq ( RosTaskIdType Src,
                                       ApiHalGpioPortPinType PortPin,
                                                             /*!< Port pin identifier 
                                                                High nibble selects Port,
                                                                low nibble selects Pin */
                                       ApiHalGpioPortPinModeType PortPinMode);
                                                             /*!< Selects the operation
                                                                mode of the PortPin. 
                                                                (Input, Output, PullUp or
                                                                PullDown) */

/****************************************************************************
* FUNCTION:      SendApiHalSetGpioPortReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_SET_GPIO_PORT_REQ=0x5914
****************************************************************************/
void SendApiHalSetGpioPortReq ( RosTaskIdType Src,
                                ApiHalGpioPortType Port,     /*!< GPIO port identifier */
                                rsuint16 Value);             /*!< port value: Bitmask of
                                                                the GPIO pins to be set
                                                                high. Unaddressed pins are
                                                                left untouched in their
                                                                original state. */

/****************************************************************************
* FUNCTION:      SendApiHalResetGpioPortReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_RESET_GPIO_PORT_REQ=0x5916
****************************************************************************/
void SendApiHalResetGpioPortReq ( RosTaskIdType Src,
                                  ApiHalGpioPortType Port,   /*!< GPIO port identifier */
                                  rsuint16 Value);           /*!< port value: Bitmask of
                                                                the GPIO pins to be reset
                                                                low. Unaddressed pins are
                                                                left untouched in their
                                                                original state. */

/****************************************************************************
* FUNCTION:      SendApiHalGetGpioPortReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_GET_GPIO_PORT_REQ=0x5918
****************************************************************************/
void SendApiHalGetGpioPortReq ( RosTaskIdType Src,
                                ApiHalGpioPortType Port);    /*!< GPIO port identifier */

/****************************************************************************
* FUNCTION:      SendApiHalGetAdcReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HAL_GET_ADC_REQ=0x5920
****************************************************************************/
void SendApiHalGetAdcReq ( RosTaskIdType Src,
                           ApiHalAdcIdType ADCId);           /*!< Id of the ADC */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIHAL_H */


