/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_pDimmerSwitch.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pDimmerSwitch.
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
 * @defgroup   OPEND_HANFUN_PDIMMERSWITCH openD HAN-FUN pDimmerSwitch
 *             This module specifies the HAN-FUN dimmer switch profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PDIMMERSWITCH_H__
#define __OPEND_HANFUN_PDIMMERSWITCH_H__

#include "../interfaces/opend_hanfun_iLevelControl.h"
#include "../interfaces/opend_hanfun_iOnOff.h"

/**
 * openD Hanfun pDimmerSwitch interfaces.
 */
typedef enum openD_hanfun_pDimmerSwitch_interface {
  /**
   * Interface iOnOff.
   */
  OPEND_HANFUN_PDIMMERSWITCH_IONOFF,
  /**
   * Interface iLevelControl.
   */
  OPEND_HANFUN_PDIMMERSWITCH_ILEVELCONTROL,
} openD_hanfun_pDimmerSwitch_interface_t;

/**
 * openD Hanfun pDimmerSwitch profile request structure.
 */
typedef struct openD_hanfun_pDimmerSwitchReq {
  /**
   * Interface.
   */
  openD_hanfun_pDimmerSwitch_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffClientReq_t onOff;
    openD_hanfun_iLevelControlClientReq_t levelControl;
  };
} openD_hanfun_pDimmerSwitchReq_t;


/*! @} defgroup OPEND_HANFUN_PDIMMERSWITCH */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PDIMMERSWITCH_H__ */

