/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iSimpleHumidity.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iSimpleHumidity.
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
 * @defgroup   OPEND_HANFUN_ISIMPLEHUMIDITY openD HAN-FUN iSimpleHumidity
 *             This module specifies the HAN-FUN simple humidity interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ISIMPLEHUMIDITY_H__
#define __OPEND_HANFUN_ISIMPLEHUMIDITY_H__

#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iSimpleHumidity client services.
 */
typedef enum openD_hanfun_iSimpleHumidityClient_service {
  /**
   * Send a GET_ATTR message with the attribute @c VALUE_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLEHUMIDITY_CLIENT_READ_VALUE,
  /**
   * Send a GET_ATTR message with the attribute @c TOLERANCE_ATTR to the given address.
   */
  OPEND_HANFUN_ISIMPLEHUMIDITY_CLIENT_READ_TOLERANCE,
  /**
   * Send a GET_ATTR_PACK message to the given address to get the values for
   * all the attributes in the server.
   */
  OPEND_HANFUN_ISIMPLEHUMIDITY_CLIENT_READ_ALL,

} openD_hanfun_iSimpleHumidityClient_service_t;

/**
 * openD Hanfun iSimpleHumidity server services.
 */
typedef enum openD_hanfun_iSimpleHumidityServer_service {
  /**
   * Get the current measured humidity.
   */
  OPEND_HANFUN_ISIMPLEHUMIDITY_SERVER_GET_HUMIDITY,
  /**
   * Set the current measured humidity.
   */
  OPEND_HANFUN_ISIMPLEHUMIDITY_SERVER_SET_HUMIDITY,
  /**
   * Get the tolerance attribute.
   */
  OPEND_HANFUN_ISIMPLEHUMIDITY_SERVER_GET_TOLERANCE,

} openD_hanfun_iSimpleHumidityServer_service_t;

/**
 * openD Hanfun iSimpleHumidity client request parameter structure of the @c READ_VALUE, @c READ_TOLERANCE and @c READ_ALL service.
 */
typedef struct openD_hanfun_iSimpleHumidityClientReq_addr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iSimpleHumidityClientReq_addr_t;

/**
 * openD Hanfun iSimpleHumidity client indication parameter structure of the @c READ_VALUE and @c READ_TOLERANCE service.
 */
typedef struct openD_hanfun_iSimpleHumidityClientInd_uint16 {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleHumidityClientInd_uint16_t;

/**
 * openD Hanfun iSimpleHumidity client indication parameter structure of the @c READ_ALL service.
 */
typedef struct openD_hanfun_iSimpleHumidityClientInd_attr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Values.
   */
  uint16_t value;
  uint16_t tolerance;
} openD_hanfun_iSimpleHumidityClientInd_attr_t;

/**
 * openD Hanfun iSimpleHumidity server request parameter structure of the @c SET_HUMIDITY service.
 */
typedef struct openD_hanfun_iSimpleHumidityServerReq_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleHumidityServerReq_uint16_t;

/**
 * openD Hanfun iSimpleHumidity server confirm parameter structure of the @c GET_HUMIDITY and @c GET_TOLERANCE service.
 */
typedef struct openD_hanfun_iSimpleHumidityServerCfm_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleHumidityServerCfm_uint16_t;

/**
 * openD Hanfun iSimpleHumidity client request structure.
 */
typedef struct openD_hanfun_iSimpleHumidityClientReq {
  /**
   * Hanfun iSimpleHumidity client service.
   */
  openD_hanfun_iSimpleHumidityClient_service_t service;

  /**
   * Hanfun iSimpleHumidity parameters.
   */
  union {
    openD_hanfun_iSimpleHumidityClientReq_addr_t readValue;
    openD_hanfun_iSimpleHumidityClientReq_addr_t readTolerance;
    openD_hanfun_iSimpleHumidityClientReq_addr_t readAll;
  } param;
} openD_hanfun_iSimpleHumidityClientReq_t;

/**
 * openD Hanfun iSimpleHumidity client indication structure.
 */
typedef struct openD_hanfun_iSimpleHumidityClientInd {
  /**
   * Hanfun iSimpleHumidity client service.
   */
  openD_hanfun_iSimpleHumidityClient_service_t service;

  /**
   * Hanfun iSimpleHumidity parameters.
   */
  union {
    openD_hanfun_iSimpleHumidityClientInd_uint16_t readValue;
    openD_hanfun_iSimpleHumidityClientInd_uint16_t readTolerance;
    openD_hanfun_iSimpleHumidityClientInd_attr_t readAllAttr;
  } param;
} openD_hanfun_iSimpleHumidityClientInd_t;

/**
 * openD Hanfun iSimpleHumidity server request structure.
 */
typedef struct openD_hanfun_iSimpleHumidityServerReq {
  /**
   * Hanfun iSimpleHumidity server service.
   */
  openD_hanfun_iSimpleHumidityServer_service_t service;

  /**
   * Hanfun iSimpleHumidity parameters.
   */
  union {
    openD_hanfun_iSimpleHumidityServerReq_uint16_t setHumidity;
  } param;
} openD_hanfun_iSimpleHumidityServerReq_t;

/**
 * openD Hanfun iSimpleHumidity server confirm structure.
 */
typedef struct openD_hanfun_iSimpleHumidityServerCfm {
  /**
   * Hanfun iSimpleHumidity server service.
   */
  openD_hanfun_iSimpleHumidityServer_service_t service;

  /**
   * Hanfun iSimpleHumidity parameters.
   */
  union {
    openD_hanfun_iSimpleHumidityServerCfm_uint16_t getHumidity;
    openD_hanfun_iSimpleHumidityServerCfm_uint16_t getTolerance;
  } param;
} openD_hanfun_iSimpleHumidityServerCfm_t;


/*! @} defgroup OPEND_HANFUN_ISIMPLEHUMIDITY */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ISIMPLEHUMIDITY_H__ */

