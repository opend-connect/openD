/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iAlert.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iAlert.
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
 * @defgroup   OPEND_HANFUN_IALERT openD HAN-FUN iAlert
 *             This module specifies the HAN-FUN alert interface.
 * @{
 */

#ifndef __OPEND_HANFUN_IALERT_H__
#define __OPEND_HANFUN_IALERT_H__

#include <stdbool.h>
#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iAlert client services.
 */
typedef enum openD_hanfun_iAlertClient_service {
  /**
   * ALLERT message is received from a server.
   */
  OPEND_HANFUN_IALERT_CLIENT_STATUS,

} openD_hanfun_iAlertClient_service_t;

/**
 * openD Hanfun iAlert server services.
 */
typedef enum openD_hanfun_iAlertServer_service {
  /**
   * Get the current state for all the alerts as a bitmask.
   */
  OPEND_HANFUN_IALERT_SERVER_GET_STATE,
  /**
   * Set the state bitmask to the given value.
   */
  OPEND_HANFUN_IALERT_SERVER_SET_STATE,
  /**
   * Get the state of the alert given by index.
   */
  OPEND_HANFUN_IALERT_SERVER_GET_STATE_INDEX,
  /**
   * Set the alert given by index to value.
   */
  OPEND_HANFUN_IALERT_SERVER_SET_STATE_INDEX,
  /**
   * Clear all the alerts.
   */
  OPEND_HANFUN_IALERT_SERVER_CLEAR,
  /**
   * Enable alert at @c index.
   */
  OPEND_HANFUN_IALERT_SERVER_ENABLE_INDEX,
  /**
   * Enable all alerts.
   */
  OPEND_HANFUN_IALERT_SERVER_ENABLE_ALL,
  /**
   * Return the bitmask of the enable state of the alerts.
   */
  OPEND_HANFUN_IALERT_SERVER_GET_ENABLED,
  /**
   * Set the bitmask of the enable state of the alerts.
   */
  OPEND_HANFUN_IALERT_SERVER_SET_ENABLED,
  /**
   * Check if alert at @c index is enabled.
   */
  OPEND_HANFUN_IALERT_SERVER_GET_ENABLED_INDEX,
  /**
   * Disable alert at @c index.
   */
  OPEND_HANFUN_IALERT_SERVER_DISABLE_INDEX,
  /**
   * Check if alert at @c index is disabled.
   */
  OPEND_HANFUN_IALERT_SERVER_GET_DISABLED_INDEX,
  /**
   * Send a STATUS message to the broadcast address.
   */
  OPEND_HANFUN_IALERT_SERVER_STATUS,
  /**
   * Send a ALERT message to the device at the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_IALERT_SERVER_STATUS_ADDR,

} openD_hanfun_iAlertServer_service_t;

/**
 * openD Hanfun iAlert server confirm parameter structure of the @c GET_STATE service.
 */
typedef struct openD_hanfun_iAlertServerCfm_getState {
  /**
   * Bitmask of the alert states.
   */
  uint32_t value;
} openD_hanfun_iAlertServerCfm_getState_t;

/**
 * openD Hanfun iAlert server request parameter structure of the @c SET_STATE service.
 */
typedef struct openD_hanfun_iAlertServerReq_setState {
  /**
   * Bitmask value to set the alert states.
   */
  uint32_t value;
} openD_hanfun_iAlertServerReq_setState_t;

/**
 * openD Hanfun iAlert server request parameter structure of the @c GET_STATE_INDEX service.
 */
typedef struct openD_hanfun_iAlertServerReq_getStateIndex {
  /**
   * Index of the alert to get the state from.
   */
  uint8_t index;
} openD_hanfun_iAlertServerReq_getStateIndex_t;

/**
 * openD Hanfun iAlert server confirm parameter structure of the @c GET_STATE_INDEX service.
 */
typedef struct openD_hanfun_iAlertServerCfm_getStateIndex {
  /**
   * Index of the alert to get the state from.
   */
  bool value;
} openD_hanfun_iAlertServerCfm_getStateIndex_t;

/**
 * openD Hanfun iAlert server request parameter structure of the @c SET_STATE_INDEX service.
 */
typedef struct openD_hanfun_iAlertServerReq_setStateIndex {
  /**
   * Index of the alert to set.
   */
  uint8_t index;
  /**
   * State to set the index to.
   */
  bool value;
} openD_hanfun_iAlertServerReq_setStateIndex_t;

/**
 * openD Hanfun iAlert server request parameter structure of the @c ENABLE_INDEX service.
 */
typedef struct openD_hanfun_iAlertServerReq_enableIndex {
  /**
   * Index to the enable the alert.
   */
  uint8_t index;
} openD_hanfun_iAlertServerReq_enableIndex_t;

/**
 * openD Hanfun iAlert server confirm parameter structure of the @c GET_ENABLED service.
 */
typedef struct openD_hanfun_iAlertServerCfm_getEnabled {
  /**
   * Bitmask of the enable state of the alerts.
   */
  uint32_t value;
} openD_hanfun_iAlertServerCfm_getEnabled_t;
/**
 * openD Hanfun iAlert server request parameter structure of the @c SET_ENABLED service.
 */
typedef struct openD_hanfun_iAlertServerReq_setEnabled {
  /**
   * Value the bitmask of the enable state of the alerts to set.
   */
  uint32_t value;
} openD_hanfun_iAlertServerReq_setEnabled_t;

/**
 * openD Hanfun iAlert server request parameter structure of the @c GET_ENABLED_INDEX service.
 */
typedef struct openD_hanfun_iAlertServerReq_getEnabledIndex {
  /**
   * Index to the enable the alert.
   */
  uint8_t index;
} openD_hanfun_iAlertServerReq_getEnabledIndex_t;

/**
 * openD Hanfun iAlert server confirm parameter structure of the @c GET_ENABLED_INDEX service.
 */
typedef struct openD_hanfun_iAlertServerCfm_getEnabledIndex {
  /**
   * State of the alert at @c index.
   */
  bool value;
} openD_hanfun_iAlertServerCfm_getEnabledIndex_t;

/**
 * openD Hanfun iAlert server request parameter structure of the @c DISABLE_INDEX service.
 */
typedef struct openD_hanfun_iAlertServerReq_disableIndex {
  /**
   * Index of the alert to disable.
   */
  uint8_t index;
} openD_hanfun_iAlertServerReq_disableIndex_t;

/**
 * openD Hanfun iAlert server request parameter structure of the @c GET_DISABLED_INDEX service.
 */
typedef struct openD_hanfun_iAlertServerReq_getDisabledIndex {
  /**
   * Index to the disable the alert.
   */
  uint8_t index;
} openD_hanfun_iAlertServerReq_getDisabledIndex_t;

/**
 * openD Hanfun iAlert server confirm parameter structure of the @c GET_DISABLED_INDEX service.
 */
typedef struct openD_hanfun_iAlertServerCfm_getDisabledIndex {
  /**
   * State of the alert at @c index.
   */
  bool value;
} openD_hanfun_iAlertServerCfm_getDisabledIndex_t;

/**
 * openD Hanfun iAlert server request parameter structure of the @c STATUS service.
 */
typedef struct openD_hanfun_iAlertServerReq_status {
  /**
   * Unit type.
   */
  uint16_t unitType;
} openD_hanfun_iAlertServerReq_status_t;

/**
 * openD Hanfun iAlert server request parameter structure of the @c STATUS_ADDR service.
 */
typedef struct openD_hanfun_iAlertServerReq_statusAddr {
  /**
   * Hanfun device address to send the message to.
   */
  openD_hanfun_address_t addr;
  /**
   * Unit type.
   */
  uint16_t unitType;
} openD_hanfun_iAlertServerReq_statusAddr_t;

/**
 * openD Hanfun iAlert message structure.
 */
typedef struct openD_hanfun_iAlert_message {
  /**
   * Unit type that generated the message.
   */
  uint16_t type;
  /**
   * Current state of the server.
   */
  uint8_t state;
} openD_hanfun_iAlert_message_t;

/**
 * openD Hanfun iAlert client status structure.
 */
typedef struct openD_hanfun_iAlertClientInd_status {
  /**
   * Hanfun device source address the change was received from.
   */
  openD_hanfun_address_t source;
  /**
   * Payload for the STATUS message.
   */
  openD_hanfun_iAlert_message_t message;
} openD_hanfun_iAlertClientInd_status_t;

/**
 * openD Hanfun iAlert server request structure.
 */
typedef struct openD_hanfun_iAlertServerReq {
  /**
   * Hanfun iAlert server service.
   */
  openD_hanfun_iAlertServer_service_t service;

  /**
   * Hanfun iAlert parameters.
   */
  union {
    openD_hanfun_iAlertServerReq_setState_t setState;
    openD_hanfun_iAlertServerReq_getStateIndex_t getStateIndex;
    openD_hanfun_iAlertServerReq_setStateIndex_t setStateIndex;
    openD_hanfun_iAlertServerReq_enableIndex_t enableIndex;
    openD_hanfun_iAlertServerReq_setEnabled_t setEnabled;
    openD_hanfun_iAlertServerReq_getEnabledIndex_t getEnabledIndex;
    openD_hanfun_iAlertServerReq_disableIndex_t disableIndex;
    openD_hanfun_iAlertServerReq_getDisabledIndex_t getDisabledIndex;
    openD_hanfun_iAlertServerReq_status_t status;
    openD_hanfun_iAlertServerReq_statusAddr_t statusAddr;
  } param;
} openD_hanfun_iAlertServerReq_t;

/**
 * openD Hanfun iAlert server confirm structure.
 */
typedef struct openD_hanfun_iAlertServerCfm {
  /**
   * Hanfun iAlert server service.
   */
  openD_hanfun_iAlertServer_service_t service;

  /**
   * Hanfun iAlert parameters.
   */
  union {
    openD_hanfun_iAlertServerCfm_getState_t getState;
    openD_hanfun_iAlertServerCfm_getStateIndex_t getStateIndex;
    openD_hanfun_iAlertServerCfm_getEnabled_t getEnabled;
    openD_hanfun_iAlertServerCfm_getEnabledIndex_t getEnabledIndex;
    openD_hanfun_iAlertServerCfm_getDisabledIndex_t getDisabledIndex;
  } param;
} openD_hanfun_iAlertServerCfm_t;

/**
 * openD Hanfun iAlert client indication structure.
 */
typedef struct openD_hanfun_iAlertClientInd {
  /**
   * Hanfun iAlert client service.
   */
  openD_hanfun_iAlertClient_service_t service;

  /**
   * Hanfun iAlert parameters.
   */
  union {
    openD_hanfun_iAlertClientInd_status_t status;
  } param;
} openD_hanfun_iAlertClientInd_t;


/*! @} defgroup OPEND_HANFUN_IALERT */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_IALERT_H__ */
