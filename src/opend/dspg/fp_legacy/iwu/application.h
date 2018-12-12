/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       application.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      iwu application api.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   HANFUN IWU
 *             This file specifies the IWU api for the application.
 * @{
 */

#ifndef HF_APP_H
#define HF_APP_H

/**
 * @brief   Initialize ule app.
 *
 * @details Initialization of the ule application.
 *
 * @param   argc Holds the number of parameters.
 * @param   argv Pointer of the pointer parameters.
 */
void initUleApp(int argc, char **argv);

#endif /* HF_APP_H */
