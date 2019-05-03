/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       transport.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      HANFUN transport IWU.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   Transport IWU
 *             This file specifies the Transport IWU API.
 * @{
 */

#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "opend_dataTypes.h"

/**
 * @brief   Initialize the transport.
 *
 * @details Initialization of the transport.
 */
openD_status_t transport_init( void );

/**
 * @brief   De-Initialize the transport.
 *
 * @details De-Initialization of the transport.
 */
openD_status_t transport_deInit( void );

#endif /* TRANSPORT_H */
