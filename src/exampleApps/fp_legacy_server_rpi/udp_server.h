/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       udp_server.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      udp server side api.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   UDP server api
 *             This file specifies the udp server side.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>

/**
 * @brief   UDP initialization.
 *
 * @details Initialize the udp server side.
 */
void udp_init();

/**
 * @brief   Receive udp data.
 *
 * @details Receive udp data from client side.
 *
 * @param   buffer Pointer to the received data.
 */
void udp_receive(char *buffer);

/**
 * @brief   UDP send.
 *
 * @details Send udp data with a defined length to the client.
 *
 * @param   data Pointer to the data to send.
 * @param   len Length of the data to send.
 */
void udp_send(const char *data, size_t len);


#ifdef __cplusplus
}
#endif