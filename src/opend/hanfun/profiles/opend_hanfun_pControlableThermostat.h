/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_pControlableThermostat.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pControlableThermostat.
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
 * @defgroup   OPEND_HANFUN_PCONTROLABLETHERMOSTAT openD HAN-FUN pControlableThermostat
 *             This module specifies the HAN-FUN controlable thermostat profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PCONTROLABLETHERMOSTAT_H__
#define __OPEND_HANFUN_PCONTROLABLETHERMOSTAT_H__

#include "../interfaces/opend_hanfun_iOnOff.h"
#include "../interfaces/opend_hanfun_iSimpleThermostat.h"

/**
 * openD Hanfun pControlableThermostat interfaces.
 */
typedef enum openD_hanfun_pControlableThermostat_interface {
  /**
   * Interface iOnOff.
   */
  OPEND_HANFUN_PCONTROLABLETHERMOSTAT_IONOFF,
  /**
   * Interface iLevelControl.
   */
  OPEND_HANFUN_PCONTROLABLETHERMOSTAT_ILEVELCONTROL,
} openD_hanfun_pControlableThermostat_interface_t;

/**
 * openD Hanfun pControlableThermostat profile request structure.
 */
typedef struct openD_hanfun_pControlableThermostatReq {
  /**
   * Interface.
   */
  openD_hanfun_pControlableThermostat_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerReq_t onOff;
    openD_hanfun_iSimpleThermostatServerReq_t simpleThermostat;
  };
} openD_hanfun_pControlableThermostatReq_t;

/**
 * openD Hanfun pControlableThermostat profile confirm structure.
 */
typedef struct openD_hanfun_pControlableThermostatCfm {
  /**
   * Interface.
   */
  openD_hanfun_pControlableThermostat_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerCfm_t onOff;
    openD_hanfun_iSimpleThermostatServerCfm_t simpleThermostat;
  };
} openD_hanfun_pControlableThermostatCfm_t;

/**
 * openD Hanfun pControlableThermostat profile indication structure.
 */
typedef struct openD_hanfun_pControlableThermostatInd {
  /**
   * Interface.
   */
  openD_hanfun_pControlableThermostat_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerInd_t onOff;
    openD_hanfun_iSimpleThermostatServerInd_t simpleThermostat;
  };
} openD_hanfun_pControlableThermostatInd_t;


/*! @} defgroup OPEND_HANFUN_PCONTROLABLETHERMOSTAT */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PCONTROLABLETHERMOSTAT_H__ */

