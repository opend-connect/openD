/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_pColourBulb.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pColourBulb.
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
 * @defgroup   OPEND_HANFUN_PCOLOURBULB openD HAN-FUN pColourBulb
 *             This module specifies the HAN-FUN colour bulb profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PCOLOURBULB_H__
#define __OPEND_HANFUN_PCOLOURBULB_H__

#include "../interfaces/opend_hanfun_iOnOff.h"
#include "../interfaces/opend_hanfun_iColourControl.h"

/**
 * openD Hanfun pColourBulb interfaces.
 */
typedef enum openD_hanfun_pColourBulb_interface {
  /**
   * Interface iOnOff.
   */
  OPEND_HANFUN_PCOLOURBULB_IONOFF,
  /**
   * Interface iColourControl.
   */
  OPEND_HANFUN_PCOLOURBULB_ICOLOURCONTROL,
} openD_hanfun_pColourBulb_interface_t;

/**
 * openD Hanfun pColourBulb profile request structure.
 */
typedef struct openD_hanfun_pColourBulbReq {
  /**
   * Interface.
   */
  openD_hanfun_pColourBulb_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerReq_t onOff;
    openD_hanfun_iColourControlServerReq_t colourControl;
  };
} openD_hanfun_pColourBulbReq_t;

/**
 * openD Hanfun pColourBulb profile confirm structure.
 */
typedef struct openD_hanfun_pColourBulbCfm {
  /**
   * Interface.
   */
  openD_hanfun_pColourBulb_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerCfm_t onOff;
    openD_hanfun_iColourControlServerCfm_t colourControl;
  };
} openD_hanfun_pColourBulbCfm_t;

/**
 * openD Hanfun pColourBulb profile indication structure.
 */
typedef struct openD_hanfun_pColourBulbInd {
  /**
   * Interface.
   */
  openD_hanfun_pColourBulb_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerInd_t onOff;
    openD_hanfun_iColourControlServerInd_t colourControl;
  };
} openD_hanfun_pColourBulbInd_t;


/*! @} defgroup OPEND_HANFUN_PCOLOURBULB */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PCOLOURBULB_H__ */

