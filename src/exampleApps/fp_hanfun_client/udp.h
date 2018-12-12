/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       udp.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      UDP client module API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   UDP UDP client module API
 *             This file specifies the UDP client module.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/**
 * @brief   Receive udp data.
 *
 * @details Receive udp data callback.
 *
 * @param   data Pointer to the received data.
 */
typedef void (*receiveUdpData)(char *data);

/**
 * @brief   UDP initialization.
 *
 * @details Initialize the udp client side.
 *
 * @param   rxUdpData Function pointer to the receive udp data callback.
 */
void udp_init(receiveUdpData rxUdpData);

/**
 * @brief   RX thread init.
 *
 * @details Initialize the RX thread.
 *
 * @retval  int Status of the operation. (-1 = fail)
 */
int rxThread_init();

/**
 * @brief   UDP send.
 *
 * @details Send udp data with a defined length to the server.
 *
 * @param   data Pointer to the data to send.
 * @param   len Length of the data to send.
 */
void udp_send(const char *data, size_t len);

/**
 * @brief   UDP send hello.
 *
 * @details Send udp data to the server as initialization.
 */
void udpSendHello();

/*! @} defgroup UDP */

#ifdef __cplusplus
}
#endif

/*! @} */
