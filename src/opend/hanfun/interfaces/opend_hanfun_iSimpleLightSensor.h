/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iSimpleLightSensor.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iSimpleLightSensor.
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
 * @defgroup   OPEND_HANFUN_ISIMPLELIGHTSENSOR openD HAN-FUN iSimpleLightSensor
 *             This module specifies the HAN-FUN simple light sensor interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ISIMPLELIGHTSENSOR_H__
#define __OPEND_HANFUN_ISIMPLELIGHTSENSOR_H__

#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iSimpleLightSensor client services.
 */
typedef enum openD_hanfun_iSimpleLightSensorClient_service {
  /**
   * Send a GET_ATTR message with the attribute @c VALUE_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_CLIENT_READ_VALUE,
  /**
   * Send a GET_ATTR message with the attribute @c MINIMUM_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_CLIENT_READ_MINIMUM,
  /**
   * Send a GET_ATTR message with the attribute @c MAXIMUM_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_CLIENT_READ_MAXIMUM,
  /**
   * Send a GET_ATTR message with the attribute @c TOLERANCE_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_CLIENT_READ_TOLERANCE,
  /**
   * Send a GET_ATTR_PACK message to the given address to get the values for
   * all the attributes in the server.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_CLIENT_READ_ALL,

} openD_hanfun_iSimpleLightSensorClient_service_t;

/**
 * openD Hanfun iSimpleLightSensor server services.
 */
typedef enum openD_hanfun_iSimpleLightSensorServer_service {
  /**
   * Get the value for the simple light sensor server.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_SERVER_GET_VALUE,
  /**
   * Set the value for the simple light sensor server.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_SERVER_SET_VALUE,
  /**
   * Get the minimum for the simple light sensor server.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_SERVER_GET_MINIMUM,
  /**
   * Set the minimum for the simple light sensor server.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_SERVER_SET_MINIMUM,
  /**
   * Get the maximum for the simple light sensor server.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_SERVER_GET_MAXIMUM,
  /**
   * Set the maximum for the simple light sensor server.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_SERVER_SET_MAXIMUM,
  /**
   * Get the tolerance for the simple light sensor server.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_SERVER_GET_TOLERANCE,
  /**
   * Set the tolerance for the simple light sensor server.
   */
  OPEND_HANFUN_ISIMPLELIGHTSENSOR_SERVER_SET_TOLERANCE,

} openD_hanfun_iSimpleLightSensorServer_service_t;

/**
 * openD Hanfun iSimpleLightSensor client request parameter structure of the @c READ_VALUE, @c READ_MINIMUM, @c READ_MAXIMUM, @c READ_TOLERANCE and @c READ_ALL service.
 */
typedef struct openD_hanfun_iSimpleLightSensorClientReq_addr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iSimpleLightSensorClientReq_addr_t;

/**
 * openD Hanfun iSimpleLightSensor client indication parameter structure of the @c READ_VALUE, @c READ_MINIMUM, @c READ_MAXIMUM and @c READ_TOLERANCE service.
 */
typedef struct openD_hanfun_iSimpleLightSensorClientInd_uint32 {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Value.
   */
  uint32_t value;
} openD_hanfun_iSimpleLightSensorClientInd_uint32_t;

/**
 * openD Hanfun iSimpleLightSensor client indication parameter structure of the @c READ_ALL service.
 */
typedef struct openD_hanfun_iSimpleLightSensorClientInd_attr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Values.
   */
  uint32_t value;
  uint32_t minimum;
  uint32_t maximum;
  uint32_t tolerance;
} openD_hanfun_iSimpleLightSensorClientInd_attr_t;

/**
 * openD Hanfun iSimpleLightSensor server request parameter structure of the @c SET_VALUE service.
 */
typedef struct openD_hanfun_iSimpleLightSensorServerReq_uint32 {
  /**
   * Value.
   */
  uint32_t value;
} openD_hanfun_iSimpleLightSensorServerReq_uint32_t;

/**
 * openD Hanfun iSimpleLightSensor server confirm parameter structure of the @c GET_VALUE, GET_MINIMUM, GET_MAXIMUM and GET_TOLERANCE service.
 */
typedef struct openD_hanfun_iSimpleLightSensorServerCfm_uint32 {
  /**
   * Value.
   */
  uint32_t value;
} openD_hanfun_iSimpleLightSensorServerCfm_uint32_t;

/**
 * openD Hanfun iSimpleLightSensor client request structure.
 */
typedef struct openD_hanfun_iSimpleLightSensorClientReq {
  /**
   * Hanfun iSimpleLightSensor client service.
   */
  openD_hanfun_iSimpleLightSensorClient_service_t service;

  /**
   * Hanfun iSimpleLightSensor parameters.
   */
  union {
    openD_hanfun_iSimpleLightSensorClientReq_addr_t readValue;
    openD_hanfun_iSimpleLightSensorClientReq_addr_t readMinimum;
    openD_hanfun_iSimpleLightSensorClientReq_addr_t readMaximum;
    openD_hanfun_iSimpleLightSensorClientReq_addr_t readTolerance;
    openD_hanfun_iSimpleLightSensorClientReq_addr_t readAll;
  } param;
} openD_hanfun_iSimpleLightSensorClientReq_t;

/**
 * openD Hanfun iSimpleLightSensor client indication structure.
 */
typedef struct openD_hanfun_iSimpleLightSensorClientInd {
  /**
   * Hanfun iSimpleLightSensor client service.
   */
  openD_hanfun_iSimpleLightSensorClient_service_t service;

  /**
   * Hanfun iSimpleLightSensor parameters.
   */
  union {
    openD_hanfun_iSimpleLightSensorClientInd_uint32_t readValue;
    openD_hanfun_iSimpleLightSensorClientInd_uint32_t readMinimum;
    openD_hanfun_iSimpleLightSensorClientInd_uint32_t readMaximum;
    openD_hanfun_iSimpleLightSensorClientInd_uint32_t readTolerance;
    openD_hanfun_iSimpleLightSensorClientInd_attr_t readAllAttr;
  } param;
} openD_hanfun_iSimpleLightSensorClientInd_t;

/**
 * openD Hanfun iSimpleLightSensor server request structure.
 */
typedef struct openD_hanfun_iSimpleLightSensorServerReq {
  /**
   * Hanfun iSimpleLightSensor server service.
   */
  openD_hanfun_iSimpleLightSensorServer_service_t service;

  /**
   * Hanfun iSimpleLightSensor parameters.
   */
  union {
    openD_hanfun_iSimpleLightSensorServerReq_uint32_t setValue;
    openD_hanfun_iSimpleLightSensorServerReq_uint32_t setMinimum;
    openD_hanfun_iSimpleLightSensorServerReq_uint32_t setMaximum;
    openD_hanfun_iSimpleLightSensorServerReq_uint32_t setTolerance;
  } param;
} openD_hanfun_iSimpleLightSensorServerReq_t;

/**
 * openD Hanfun iSimpleLightSensor server confirm structure.
 */
typedef struct openD_hanfun_iSimpleLightSensorServerCfm {
  /**
   * Hanfun iSimpleLightSensor server service.
   */
  openD_hanfun_iSimpleLightSensorServer_service_t service;

  /**
   * Hanfun iSimpleLightSensor parameters.
   */
  union {
    openD_hanfun_iSimpleLightSensorServerCfm_uint32_t getValue;
    openD_hanfun_iSimpleLightSensorServerCfm_uint32_t getMinimum;
    openD_hanfun_iSimpleLightSensorServerCfm_uint32_t getMaximum;
    openD_hanfun_iSimpleLightSensorServerCfm_uint32_t getTolerance;
  } param;
} openD_hanfun_iSimpleLightSensorServerCfm_t;


/*! @} defgroup OPEND_HANFUN_ISIMPLELIGHTSENSOR */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ISIMPLELIGHTSENSOR_H__ */
