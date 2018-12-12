/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ule.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief      ule iwu API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   ULE_IWU_API ule interworking unit API
 *             This module specifies the ule iwu API.
 * \{
 */

#ifndef __ULE_H__
#define __ULE_H__


#include <stdlib.h>

/**
 * @brief   Byte received callback primitive.
 *
 * @param   data Pointer to the received data.
 * @param   len Length of the received data.
 */
typedef void (*byteReceivedClb)(uint8_t *data, uint16_t len);

/**
 * @brief   Keep alive callback primitive.
 */
typedef void (*keepAliveClb)();

/**
 * @brief   Keep alive timer start.
 *
 * @details Start the hardware timer to send a keep alive message.
 */
void keepAliveTimerStart();

/**
 * @brief   Initialize iwu.
 *
 * @details Initialization of the interworking unit.
 *
 * @param   keepAlive Pointer to the keep alive callback function.
 * @param   byteReceived Pointer to the byte received callback function.
 */
bool initIwu(keepAliveClb keepAlive, byteReceivedClb byteReceived);

/**
 * @brief   Success confirmation indication.
 *
 * @details Success confirmation and indication led blinking.
 */
void successConInd();

/**
 * @brief   Failure confirmation indication.
 *
 * @details Failure confirmation and indication led blinking.
 */
void failureConInd();

/**
 * @brief   Exit app.
 *
 * @details Exit application and destroy transport layer.
 */
void exitApp();

/*! @} defgroup ULE_IWU_API */

#endif // __ULE_H__
