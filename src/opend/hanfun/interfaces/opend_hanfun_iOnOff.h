/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iOnOff.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iOnOff.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @addtogroup OPEND_HANFUN_INTERFACE
 * @{
 *
 * @defgroup   OPEND_HANFUN_IONOFF openD HAN-FUN iOnOff
 *             This module specifies the HAN-FUN on/off interface.
 * @{
 */

#ifndef __OPEND_HANFUN_IONOFF_H__
#define __OPEND_HANFUN_IONOFF_H__

#include <stdbool.h>

#include "../opend_hanfun_dataTypes.h"

#include "hanfun.h"

/**
 * openD Hanfun iOnOff client services.
 */
typedef enum openD_hanfun_iOnOffClient_service {
  /**
   * Send a ON message to the device at the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_IONOFF_CLIENT_ON_ADDR,
  /**
   * Send a ON message to the broadcast address.
   */
  OPEND_HANFUN_IONOFF_CLIENT_ON,
  /**
   * Send a OFF message to the device at the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_IONOFF_CLIENT_OFF_ADDR,
  /**
   * Send a OFF message to the broadcast address.
   */
  OPEND_HANFUN_IONOFF_CLIENT_OFF,
  /**
   * Send a TOGGLE message to the device at the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_IONOFF_CLIENT_TOGGLE_ADDR,
  /**
   * Send a TOGGLE message to the broadcast address.
   */
  OPEND_HANFUN_IONOFF_CLIENT_TOGGLE,

} openD_hanfun_iOnOffClient_service_t;

/**
 * openD Hanfun iOnOff server services.
 */
typedef enum openD_hanfun_iOnOffServer_service {
  /**
   * ON message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_IONOFF_SERVER_ON_ADDR,
  /**
   * OFF message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_IONOFF_SERVER_OFF_ADDR,
  /**
   * TOGGLE message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_IONOFF_SERVER_TOGGLE_ADDR,
  /**
   * Set the state attribute to given value.
   */
  OPEND_HANFUN_IONOFF_SERVER_SET_STATE,
  /**
   * Get the current state of the interface.
   */
  OPEND_HANFUN_IONOFF_SERVER_GET_STATE,
} openD_hanfun_iOnOffServer_service_t;

/**
 * openD Hanfun iOnOff client request parameter structure of the @c ON_ADDR, @c OFF_ADDR and @c TOGGLE_ADDR service.
 */
typedef struct openD_hanfun_iOnOffClientReq_addr {
  /**
   * Hanfun address of the device to send the message to.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iOnOffClientReq_addr_t;

/**
 * openD Hanfun iOnOff server indication parameter structure of the @c ON_ADDR, @c OFF_ADDR and @c TOGGLE_ADDR service.
 */
typedef struct openD_hanfun_iOnOffServerInd_addr {
  /**
   * Hanfun address of the device to send the message to.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iOnOffServerInd_addr_t;

/**
 * openD Hanfun iOnOff server request parameter structure of the @c SET_STATE service.
 */
typedef struct openD_hanfun_iOnOffServerReq_setState {
  /**
   * State of the interface to set.
   */
  bool state;
} openD_hanfun_iOnOffServerReq_setState_t;

/**
 * openD Hanfun iOnOff server confirm parameter structure of the @c GET_STATE service.
 */
typedef struct openD_hanfun_iOnOffServerCfm_getState {
  /**
   * State of the interface.
   */
  bool state;
} openD_hanfun_iOnOffServerCfm_getState_t;

/**
 * openD Hanfun iOnOff server indication parameter structure of the @c GET_STATE service.
 */
typedef struct openD_hanfun_iOnOffServerInd_getState {
  /**
   * State of the interface.
   */
  bool state;
} openD_hanfun_iOnOffServerInd_getState_t;

/**
 * openD Hanfun iOnOff client request structure.
 */
typedef struct openD_hanfun_iOnOffClientReq {
  /**
   * Hanfun iOnOff client service.
   */
  openD_hanfun_iOnOffClient_service_t service;

  /**
   * Hanfun iOnOff parameters.
   */
  union {
    openD_hanfun_iOnOffClientReq_addr_t onAddr;
    openD_hanfun_iOnOffClientReq_addr_t offAddr;
    openD_hanfun_iOnOffClientReq_addr_t toggleAddr;
  } param;
} openD_hanfun_iOnOffClientReq_t;

/**
 * openD Hanfun iOnOff client confirm structure.
 */
typedef struct openD_hanfun_iOnOffClientCfm {
  /**
   * Hanfun iOnOff client service.
   */
  openD_hanfun_iOnOffClient_service_t service;
} openD_hanfun_iOnOffClientCfm_t;

/**
 * openD Hanfun iOnOff server request structure.
 */
typedef struct openD_hanfun_iOnOffServerReq {
  /**
   * Hanfun iOnOff service.
   */
  openD_hanfun_iOnOffServer_service_t service;

  /**
   * Hanfun iOnOff server parameters.
   */
  union {
    openD_hanfun_iOnOffServerReq_setState_t setState;
  } param;
} openD_hanfun_iOnOffServerReq_t;

/**
 * openD Hanfun iOnOff server confirm structure.
 */
typedef struct openD_hanfun_iOnOffServerCfm {
  /**
   * Hanfun iOnOff server service.
   */
  openD_hanfun_iOnOffServer_service_t service;
  /**
   * Hanfun iOnOff parameters.
   */
  union {
    openD_hanfun_iOnOffServerCfm_getState_t getState;
  } param;
} openD_hanfun_iOnOffServerCfm_t;

/**
 * openD Hanfun iOnOff server indication structure.
 */
typedef struct openD_hanfun_iOnOffServerInd {
  /**
   * Hanfun iOnOff server service.
   */
  openD_hanfun_iOnOffServer_service_t service;

  /**
   * Hanfun iOnOff parameters.
   */
  union {
    openD_hanfun_iOnOffServerInd_addr_t onAddr;
    openD_hanfun_iOnOffServerInd_addr_t offAddr;
    openD_hanfun_iOnOffServerInd_addr_t toggleAddr;
  } param;
} openD_hanfun_iOnOffServerInd_t;


/*! @} defgroup OPEND_HANFUN_IONOFF */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_IONOFF_H__ */

