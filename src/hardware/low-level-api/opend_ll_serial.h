#ifdef __cplusplus
extern "C" {
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_ll_serial.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief      openD low-level serial API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_LOW_LEVEL_SERIAL_API openD low-level serial API
 *             This module specifies the low-level serial API of openD connect.
 * \{
 */

#ifndef __OPEND_LL_SERIAL_H__
#define __OPEND_LL_SERIAL_H__

#include <stdint.h>

/*!
 * @brief   Serial receive primitive.
 */
typedef void ( *openD_ll_serial_rxCallback_t )( uint8_t *data, uint16_t len );

/*!
 * @brief   openD low-level serial API initialization.
 *
 * @details Initialize the UART peripheral.
 *
 * @param   instance                   Instance of the UART communication.
 * @param   baudrate                   Baudrate of the UART communication.
 * @param   openD_ll_serial_rxCallback Callback to notify RX UART receive.
 *
 * @retval  int8_t Status of the operation.
 */
int8_t openD_ll_serial_init( const char *instance, uint32_t baudrate,
                             openD_ll_serial_rxCallback_t ll_serial_rxCallback );

/*!
 * @brief   openD low-level serial API de-initialization.
 *
 * @details DeInitialize the UART peripheral.
 *
 * @param   instance Instance of the UART communication.
 *
 * @retval  Status of the operation.
 */
int8_t openD_ll_serial_deInit( const char *instance );

/*!
 * @brief   openD low-level serial API send.
 *
 * @details Send data with serial communication.
 *
 * @param   data Data array to send.
 * @param   length Length of the data array to send.
 *
 * @retval  Status of the operation.
 */
int8_t openD_ll_serial_send( uint8_t *data, uint16_t length );


/*! @} defgroup OPEND_LOW_LEVEL_SERIAL_API */

#endif  // __OPEND_LL_SERIAL_H__

#ifdef __cplusplus
}
#endif
