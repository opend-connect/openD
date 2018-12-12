/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_pSimpleOnOffSwitch.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSimpleOnOffSwitch.
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
 * @defgroup   OPEND_HANFUN_PSIMPLEONOFFSWITCH openD HAN-FUN pSimpleOnOffSwitch
 *             This module specifies the HAN-FUN simple on/off switch profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIMPLEONOFFSWITCH_H__
#define __OPEND_HANFUN_PSIMPLEONOFFSWITCH_H__

#include "../interfaces/opend_hanfun_iOnOff.h"

/**
 * openD Hanfun pSimpleOnOffSwitch profile request structure.
 */
typedef openD_hanfun_iOnOffClientReq_t openD_hanfun_pSimpleOnOffSwitchReq_t;

/**
 * openD Hanfun pSimpleOnOffSwitch profile confirm structure.
 */
typedef openD_hanfun_iOnOffClientCfm_t openD_hanfun_pSimpleOnOffSwitchCfm_t;

/*! @} defgroup OPEND_HANFUN_PSIMPLEONOFFSWITCH */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIMPLEONOFFSWITCH_H__ */

