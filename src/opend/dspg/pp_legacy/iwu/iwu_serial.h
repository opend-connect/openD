/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       iwu_serial.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      openD interworking unit api.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   SERIAL api
 *             This file specifies the serial protocol.
 * @{
 */

#include "fifo.h"

/**
 * @brief   Notify at command.
 *
 * @details Serial notify at command callback.
 *
 * @param   atCommand Pointer that hold the received at command.
 * @param   size Size of the received at command.
 */
typedef void (*notify_at_command)(uint8_t atCommand[], uint16_t size);

/**
 * @brief   Check receiving at command.
 *
 * @details Check if at commands are received.
 */
void check_receiving_at_command();

/**
 * @brief   Serial send.
 *
 * @details Send the buffer with serial.
 *
 * @param   data Pointer to data to transmit with serial communication.
 * @param   len Length of the buffer to send.
 *
 * @retval  Status of the operation. (1 = success, 0 = fail)
 */
int8_t iwu_serial_send(uint8_t *data, uint16_t len);

/**
 * @brief   Serial initialization.
 *
 * @details Initialize the serial communication.
 *
 * @param   portname Port to open for the serial communication.
 * @param   at_command Function pointer with the notify at command callback.
 *
 * @retval  Status of the operation. (-1 = fail)
 */
int8_t iwu_serial_init(notify_at_command at_command);
