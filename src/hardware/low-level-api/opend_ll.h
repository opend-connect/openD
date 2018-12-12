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
 * @file       opend_ll.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD low-level API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_LOW_LEVEL_API openD low-level API
 *             This module specifies the low-level API of openD connect.
 * \{
 */

#ifndef __OPEND_LL_H__
#define __OPEND_LL_H__

#include <stdint.h>


typedef void (*openD_serialPort_rxCallback_t)( uint8_t* data, uint16_t length );

/*!
 * @brief   openD low-level initialization.
 * @details Initialize the low-level peripheral.
 * @retval  int8_t Status of the operation.
 */
int8_t openD_ll_init( openD_serialPort_rxCallback_t serialPort_rxCallback );

/*!
 * @brief   openD low-level de-initialization.
 * @details De-initialize the low-level peripheral.
 * @retval  int8_t Status of the operation.
 */
int8_t openD_ll_deInit( void );

/*! @} defgroup OPEND_LOW_LEVEL_API */

#endif // __OPEND_LL_SERIAL_H__

#ifdef __cplusplus
}
#endif
