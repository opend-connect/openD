#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iSimpleAirPressure.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iSimpleAirPressure.
 *
 * @addtogroup OPEND_HANFUN_INTERFACE
 * @{
 *
 * @defgroup   OPEND_HANFUN_ISIMPLEAIRPRESSURE openD HAN-FUN iSimpleAirPressure
 *             This module specifies the HAN-FUN simple air pressure interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ISIMPLEAIRPRESSURE_H__
#define __OPEND_HANFUN_ISIMPLEAIRPRESSURE_H__

#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iSimpleAirPressure server services.
 */
typedef enum openD_hanfun_iSimpleAirPressureServer_service {
  /**
   * Get the value for the simple air pressure server.
   */
  OPEND_HANFUN_ISIMPLEAIRPRESSURE_SERVER_GET_VALUE,
  /**
   * Set the value for the simple air pressure server.
   */
  OPEND_HANFUN_ISIMPLEAIRPRESSURE_SERVER_SET_VALUE,
  /**
   * Get the minimum for the simple air pressure server.
   */
  OPEND_HANFUN_ISIMPLEAIRPRESSURE_SERVER_GET_MINIMUM,
  /**
   * Set the minimum for the simple air pressure server.
   */
  OPEND_HANFUN_ISIMPLEAIRPRESSURE_SERVER_SET_MINIMUM,
  /**
   * Get the maximum for the simple air pressure server.
   */
  OPEND_HANFUN_ISIMPLEAIRPRESSURE_SERVER_GET_MAXIMUM,
  /**
   * Set the maximum for the simple air pressure server.
   */
  OPEND_HANFUN_ISIMPLEAIRPRESSURE_SERVER_SET_MAXIMUM,
  /**
   * Get the tolerance for the simple air pressure server.
   */
  OPEND_HANFUN_ISIMPLEAIRPRESSURE_SERVER_GET_TOLERANCE,
  /**
   * Set the tolerance for the simple air pressure server.
   */
  OPEND_HANFUN_ISIMPLEAIRPRESSURE_SERVER_SET_TOLERANCE,

} openD_hanfun_iSimpleAirPressureServer_service_t;

/**
 * openD Hanfun iSimpleAirPressure server request parameter structure of the @c SET_VALUE, @c SET_MINIMUM, @c SET_MAXIMUM and @c SET_TOLERANCE service.
 */
typedef struct openD_hanfun_iSimpleAirPressureServerReq_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleAirPressureServerReq_uint16_t;

/**
 * openD Hanfun iSimpleAirPressure server confirm parameter structure of the @c SET_VALUE, @c SET_MINIMUM, @c SET_MAXIMUM and @c SET_TOLERANCE service.
 */
typedef struct openD_hanfun_iSimpleAirPressureServerCfm_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleAirPressureServerCfm_uint16_t;

/**
 * openD Hanfun iSimpleAirPressure server request structure.
 */
typedef struct openD_hanfun_iSimpleAirPressureServerReq {
  /**
   * Hanfun iSimpleAirPressure server service.
   */
  openD_hanfun_iSimpleAirPressureServer_service_t service;

  /**
   * Hanfun iSimpleAirPressure parameters.
   */
  union {
    openD_hanfun_iSimpleAirPressureServerReq_uint16_t setValue;
    openD_hanfun_iSimpleAirPressureServerReq_uint16_t setMinimum;
    openD_hanfun_iSimpleAirPressureServerReq_uint16_t setMaximum;
    openD_hanfun_iSimpleAirPressureServerReq_uint16_t setTolerance;
  } param;
} openD_hanfun_iSimpleAirPressureServerReq_t;

/**
 * openD Hanfun iSimpleAirPressure server confirm structure.
 */
typedef struct openD_hanfun_iSimpleAirPressureServerCfm_t {
  /**
   * Hanfun iSimpleAirPressure server service.
   */
  openD_hanfun_iSimpleAirPressureServer_service_t service;

  /**
   * Hanfun iSimpleAirPressure parameters.
   */
  union {
    openD_hanfun_iSimpleAirPressureServerCfm_uint16_t getValue;
    openD_hanfun_iSimpleAirPressureServerCfm_uint16_t getMinimum;
    openD_hanfun_iSimpleAirPressureServerCfm_uint16_t getMaximum;
    openD_hanfun_iSimpleAirPressureServerCfm_uint16_t getTolerance;
  } param;
} openD_hanfun_iSimpleAirPressureServerCfm_t;


/*! @} defgroup OPEND_HANFUN_ISIMPLEAIRPRESSURE */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ISIMPLEAIRPRESSURE_H__ */
#ifdef __cplusplus
}
#endif
