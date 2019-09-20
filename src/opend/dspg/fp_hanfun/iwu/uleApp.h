/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       uleApp.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      ULE application api.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   HANFUN ULE APP
 *             This file specifies the ULE api for the application.
 * @{
 */

#ifndef ULE_APP_H
#define ULE_APP_H

#include "opend_dataTypes.h"

/**
 * @brief   Initialize ule app.
 *
 * @details Initialization of the ule application.
 */
openD_status_t initUleApp( void );

/**
 * @brief   De-Initialize ule app.
 *
 * @details De-Initialization of the ule application.
 */
openD_status_t deInitUleApp( void );

#endif /* ULE_APP_H */
