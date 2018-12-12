/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_pDoorBell.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pDoorBell.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PDOORBELL openD HAN-FUN pDoorBell
 *             This module specifies the HAN-FUN door bell profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PDOORBELL_H__
#define __OPEND_HANFUN_PDOORBELL_H__

#include "../interfaces/opend_hanfun_iAlert.h"

/**
 * openD Hanfun pDoorBell profile request structure.
 */
typedef openD_hanfun_iAlertServerReq_t openD_hanfun_pDoorBellReq_t;

/**
 * openD Hanfun pDoorBell profile confirm structure.
 */
typedef openD_hanfun_iAlertServerCfm_t openD_hanfun_pDoorBellCfm_t;


/*! @} defgroup OPEND_HANFUN_PDOORBELL */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PDOORBELL_H__ */

