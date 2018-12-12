/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iSimpleTemperature.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iSimpleTemperature.
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
 * @defgroup   OPEND_HANFUN_ISIMPLETEMPERATURE openD HAN-FUN iSimpleTemperature
 *             This module specifies the HAN-FUN simple temperature interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ISIMPLETEMPERATURE_H__
#define __OPEND_HANFUN_ISIMPLETEMPERATURE_H__

#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iSimpleTemperature client services.
 */
typedef enum openD_hanfun_iSimpleTemperatureClient_service {
  /**
   * Send a GET_ATTR message with the attribute @c VALUE_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_CLIENT_READ_VALUE,
  /**
   * Send a GET_ATTR message with the attribute @c MINIMUM_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_CLIENT_READ_MINIMUM,
  /**
   * Send a GET_ATTR message with the attribute @c MAXIMUM_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_CLIENT_READ_MAXIMUM,
  /**
   * Send a GET_ATTR message with the attribute @c TOLERANCE_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_CLIENT_READ_TOLERANCE,
  /**
   * Send a GET_ATTR_PACK message to the given address to get the values for
   * all the attributes in the server.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_CLIENT_READ_ALL,
} openD_hanfun_iSimpleTemperatureClient_service_t;

/**
 * openD Hanfun iSimpleTemperature server services.
 */
typedef enum openD_hanfun_iSimpleTemperatureServer_service {
  /**
   * Get the current measured temperature.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_SERVER_GET_TEMPERATURE,
  /**
   * Set the current measured temperature.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_SERVER_SET_TEMPERATURE,
  /**
   * Get the minimum measurable temperature.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_SERVER_GET_MINIMUM,
  /**
   * Get the maximum measurable temperature.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_SERVER_GET_MAXIMUM,
  /**
   * Get the tolerance attribute.
   */
  OPEND_HANFUN_ISIMPLETEMPERATURE_SERVER_GET_TOLERANCE,

} openD_hanfun_iSimpleTemperatureServer_service_t;

/**
 * openD Hanfun iSimpleTemperature client request parameter structure of the @c READ_VALUE, @c READ_MINIMUM, @c READ_MAXIMUM, @c READ_TOLERANCE and @c READ_ALL service.
 */
typedef struct openD_hanfun_iSimpleTemperatureClientReq_addr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iSimpleTemperatureClientReq_addr_t;

/**
 * openD Hanfun iSimpleTemperature client indication parameter structure of the @c READ_VALUE, @c READ_MINIMUM and @c READ_MAXIMUM service.
 */
typedef struct openD_hanfun_iSimpleTemperatureClientInd_int16 {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Value.
   */
  int16_t value;
} openD_hanfun_iSimpleTemperatureClientInd_int16_t;

/**
 * openD Hanfun iSimpleTemperature client indication parameter structure of the @c READ_TOLERANCE service.
 */
typedef struct openD_hanfun_iSimpleTemperatureClientInd_uint16 {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleTemperatureClientInd_uint16_t;

/**
 * openD Hanfun iSimpleTemperature client indication parameter structure of the @c READ_ALL service.
 */
typedef struct openD_hanfun_iSimpleTemperatureClientInd_attr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Values.
   */
  int16_t value;
  int16_t minimum;
  int16_t maximum;
  uint16_t tolerance;
} openD_hanfun_iSimpleTemperatureClientInd_attr_t;

/**
 * openD Hanfun iSimpleTemperature server request parameter structure of the @c SET_TEMPERATURE service.
 */
typedef struct openD_hanfun_iSimpleTemperatureServerReq_int16 {
  /**
   * Value.
   */
  int16_t value;
} openD_hanfun_iSimpleTemperatureServerReq_int16_t;

/**
 * openD Hanfun iSimpleTemperature server confirm parameter structure of the @c GET_TEMPERATURE, @c GET_MINIMUM and @c GET_MAXIMUM service.
 */
typedef struct openD_hanfun_iSimpleTemperatureServerCfm_int16 {
  /**
   * Value.
   */
  int16_t value;
} openD_hanfun_iSimpleTemperatureServerCfm_int16_t;

/**
 * openD Hanfun iSimpleTemperature server confirm parameter structure of the @c GET_TOLERANCE service.
 */
typedef struct openD_hanfun_iSimpleTemperatureServerCfm_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleTemperatureServerCfm_uint16_t;

/**
 * openD Hanfun iSimpleTemperature client request structure.
 */
typedef struct openD_hanfun_iSimpleTemperatureClientReq {
  /**
   * Hanfun iSimpleTemperature client service.
   */
  openD_hanfun_iSimpleTemperatureClient_service_t service;

  /**
   * Hanfun iSimpleTemperature parameters.
   */
  union {
    openD_hanfun_iSimpleTemperatureClientReq_addr_t readValue;
    openD_hanfun_iSimpleTemperatureClientReq_addr_t readMinimum;
    openD_hanfun_iSimpleTemperatureClientReq_addr_t readMaximum;
    openD_hanfun_iSimpleTemperatureClientReq_addr_t readTolerance;
    openD_hanfun_iSimpleTemperatureClientReq_addr_t readAll;
  } param;
} openD_hanfun_iSimpleTemperatureClientReq_t;

/**
 * openD Hanfun iSimpleTemperature client indication structure.
 */
typedef struct openD_hanfun_iSimpleTemperatureClientInd {
  /**
   * Hanfun iSimpleTemperature client service.
   */
  openD_hanfun_iSimpleTemperatureClient_service_t service;

  /**
   * Hanfun iSimpleTemperature parameters.
   */
  union {
    openD_hanfun_iSimpleTemperatureClientInd_int16_t readValue;
    openD_hanfun_iSimpleTemperatureClientInd_int16_t readMinimum;
    openD_hanfun_iSimpleTemperatureClientInd_int16_t readMaximum;
    openD_hanfun_iSimpleTemperatureClientInd_uint16_t readTolerance;
    openD_hanfun_iSimpleTemperatureClientInd_attr_t readAllAttr;
  } param;
} openD_hanfun_iSimpleTemperatureClientInd_t;

/**
 * openD Hanfun iSimpleTemperature server request structure.
 */
typedef struct openD_hanfun_iSimpleTemperatureServerReq {
  /**
   * Hanfun iSimpleTemperature server service.
   */
  openD_hanfun_iSimpleTemperatureServer_service_t service;

  /**
   * Hanfun iSimpleTemperature parameters.
   */
  union {
    openD_hanfun_iSimpleTemperatureServerReq_int16_t setTemperature;
  } param;
} openD_hanfun_iSimpleTemperatureServerReq_t;

/**
 * openD Hanfun iSimpleTemperature server confirm structure.
 */
typedef struct openD_hanfun_iSimpleTemperatureServerCfm {
  /**
   * Hanfun iSimpleTemperature server service.
   */
  openD_hanfun_iSimpleTemperatureServer_service_t service;

  /**
   * Hanfun iSimpleTemperature parameters.
   */
  union {
    openD_hanfun_iSimpleTemperatureServerCfm_int16_t getTemperature;
    openD_hanfun_iSimpleTemperatureServerCfm_int16_t getMinimum;
    openD_hanfun_iSimpleTemperatureServerCfm_int16_t getMaximum;
    openD_hanfun_iSimpleTemperatureServerCfm_uint16_t getTolerance;
  } param;
} openD_hanfun_iSimpleTemperatureServerCfm_t;


/*! @} defgroup OPEND_HANFUN_ISIMPLETEMPERATURE */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ISIMPLETEMPERATURE_H__ */
