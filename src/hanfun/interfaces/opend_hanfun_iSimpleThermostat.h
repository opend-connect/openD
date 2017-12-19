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
 * @file       opend_hanfun_iSimpleThermostat.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iSimpleThermostat.
 *
 * @addtogroup OPEND_HANFUN_INTERFACE
 * @{
 *
 * @defgroup   OPEND_HANFUN_ISIMPLETHERMOSTAT openD HAN-FUN iSimpleThermostat
 *             This module specifies the HAN-FUN simple thermostat interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ISIMPLETHERMOSTAT_H__
#define __OPEND_HANFUN_ISIMPLETHERMOSTAT_H__

#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iSimpleThermostat client services.
 */
typedef enum openD_hanfun_iSimpleThermostatClient_service {
  /**
   * Send a @c BOOST_START message to the device with the given address or
   * indicates that a BOOST_START message is received.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_CLIENT_BOOSTSTART,
  /**
   * Send a @c BOOST_STOP message to the device with the given address or
   * indicates that a BOOST_STOP message is received.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_CLIENT_BOOSTSTOP,

} openD_hanfun_iSimpleThermostatClient_service_t;

/**
 * openD Hanfun iSimpleThermostat server services.
 */
typedef enum openD_hanfun_iSimpleThermostatServer_service {
  /**
   * BOOST_START message is received from the address @c openD_hanfun_address_t
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_BOOSTSTART,
  /**
   * BOOST_STOP message is received from the address @c openD_hanfun_address_t
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_BOOSTSTOP,
  /**
   * Get the supported modes for the Simple Thermostat server.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_SUPPORTEDMODES,
  /**
   * Set the supported modes for the Simple Thermostat server.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_SUPPORTEDMODES,
  /**
   * Get the current Heat/Cool mode for the Simple Thermostat server.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_MODE,
  /**
   * Set the current mode for the Simple Thermostat server.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_MODE,
  /**
   * Get the current FAN mode for the Simple Thermostat server.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_FANMODE,
  /**
   * Set the current FAN mode for the Simple Thermostat server.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_FANMODE,
  /**
   * Get the current temperature for the Heat mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_HEATMODETEMPERATURE,
  /**
   * Set the current temperature for the Heat mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_HEATMODETEMPERATURE,
  /**
   * Get the current temperature for the Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_COOLMODETEMPERATURE,
  /**
   * Set the current temperature for the Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_COOLMODETEMPERATURE,
  /**
   * Get the current heat temperature for the Heat/Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_AUTOMODEHEATTEMPERATURE,
  /**
   * Set the current heat temperature for the Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_AUTOMODEHEATTEMPERATURE,
  /**
   * Get the current cool temperature for the Heat/Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_AUTOMODECOOLTEMPERATURE,
  /**
   * Set the current cool temperature for the Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_AUTOMODECOOLTEMPERATURE,
  /**
   * Get the current temperature offset for the Heat mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_HEATMODETEMPERATUREOFFSET,
  /**
   * Set the current temperature for the Heat mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_HEATMODETEMPERATUREOFFSET,
  /**
   * Get the current temperature offset for the Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_COOLMODETEMPERATUREOFFSET,
  /**
   * Set the current temperature for the Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_COOLMODETEMPERATUREOFFSET,
  /**
   * Get the current temperature offset for the Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_GET_BOOSTDURATION,
  /**
   * Set the current temperature for the Cool mode.
   */
  OPEND_HANFUN_ISIMPLETHERMOSTAT_SERVER_SET_BOOSTDURATION,

} openD_hanfun_iSimpleThermostatServer_service_t;

/**
 * openD Hanfun iSimpleThermostat client request parameter structure of the @c BOOSTSTART and @c BOOSTSTOP service.
 */
typedef struct openD_hanfun_iSimpleThermostatClientReq_addr {
  /**
   * Hanfun address of the device to send the message to.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iSimpleThermostatClientReq_addr_t;

/**
 * openD Hanfun iSimpleThermostat client indication parameter structure of the @c SHORTPRESS, @c LONGPRESS, @c EXTRALONGPRESS and @c DOUBLECLICKPRESS service.
 */
typedef struct openD_hanfun_iSimpleThermostatClientInd_addr {
  /**
   * Hanfun address of the device to send the message to.
   */
  openD_hanfun_address_t addr;
  /**
   * Hanfun result of the command.
   */
  openD_hanfun_result_t result;
} openD_hanfun_iSimpleThermostatClientInd_addrResult_t;

/**
 * openD Hanfun iSimpleThermostat server indication parameter structure of the @c BOOSTSTART and @c BOOSTSTOP service.
 */
typedef struct openD_hanfun_iSimpleThermostatServerInd_addr {
  /**
   * Hanfun address of the device to send the message to.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iSimpleThermostatServerInd_addr_t;

/**
 * openD Hanfun iSimpleThermostat server request parameter structure of the @c SET_SUPPORTEDMODES, @c SET_MODE, @c SET_FANMODE and @c SET_BOOSTDURATION service.
 */
typedef struct openD_hanfun_iSimpleThermostatServerReq_uint8 {
  /**
   * Value.
   */
  uint8_t value;
} openD_hanfun_iSimpleThermostatServerReq_uint8_t;

/**
 * openD Hanfun iSimpleThermostat server confirm parameter structure of the @c GET_SUPPORTEDMODES, @c GET_MODE, @c GET_FANMODE and @c GET_BOOSTDURATION service.
 */
typedef struct openD_hanfun_iSimpleThermostatServerCfm_uint8 {
  /**
   * Value.
   */
  uint8_t value;
} openD_hanfun_iSimpleThermostatServerCfm_uint8_t;

/**
 * openD Hanfun iSimpleThermostat server request parameter structure of the @c SET_HEATMODETEMPERATURE, @c SET_COOLMODETEMPERATURE, @c SET_AUTOMODEHEATTEMPERATURE, @c SET_AUTOMODECOOLTEMPERATURE, @c SET_HEATMODETEMPERATUREOFFSET and @c SET_COOLMODETEMPERATUREOFFSET service.
 */
typedef struct openD_hanfun_iSimpleThermostatServerReq_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleThermostatServerReq_uint16_t;

/**
 * openD Hanfun iSimpleThermostat server confirm parameter structure of the @c GET_HEATMODETEMPERATURE, @c GET_COOLMODETEMPERATURE, @c GET_AUTOMODEHEATTEMPERATURE, @c GET_AUTOMODECOOLTEMPERATURE, @c GET_HEATMODETEMPERATUREOFFSET and @c GET_COOLMODETEMPERATUREOFFSET service.
 */
typedef struct openD_hanfun_iSimpleThermostatServerCfm_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleThermostatServerCfm_uint16_t;

/**
 * openD Hanfun iSimpleThermostat client request structure.
 */
typedef struct openD_hanfun_iSimpleThermostatClientReq {
  /**
   * Hanfun iSimpleThermostat client service.
   */
  openD_hanfun_iSimpleThermostatClient_service_t service;

  /**
   * Hanfun iSimpleThermostat parameters.
   */
  union {
    openD_hanfun_iSimpleThermostatClientReq_addr_t boostStart;
    openD_hanfun_iSimpleThermostatClientReq_addr_t boostStop;
  } param;
} openD_hanfun_iSimpleThermostatClientReq_t;

/**
 * openD Hanfun iSimpleThermostat client indication structure.
 */
typedef struct openD_hanfun_iSimpleThermostatClientInd {
  /**
   * Hanfun iSimpleThermostat client service.
   */
  openD_hanfun_iSimpleThermostatClient_service_t service;

  /**
   * Hanfun iSimpleThermostat parameters.
   */
  union {
    openD_hanfun_iSimpleThermostatClientInd_addrResult_t boostStart;
    openD_hanfun_iSimpleThermostatClientInd_addrResult_t boostStop;
  } param;
} openD_hanfun_iSimpleThermostatClientInd_t;

/**
 * openD Hanfun iSimpleThermostat server request structure.
 */
typedef struct openD_hanfun_iSimpleThermostatServerReq {
  /**
   * Hanfun iSimpleThermostat server service.
   */
  openD_hanfun_iSimpleThermostatServer_service_t service;

  /**
   * Hanfun iSimpleThermostat parameters.
   */
  union {
    openD_hanfun_iSimpleThermostatServerReq_uint8_t supportedModes;
    openD_hanfun_iSimpleThermostatServerReq_uint8_t mode;
    openD_hanfun_iSimpleThermostatServerReq_uint8_t fanMode;
    openD_hanfun_iSimpleThermostatServerReq_uint16_t heatModeTemperature;
    openD_hanfun_iSimpleThermostatServerReq_uint16_t coolModeTemperature;
    openD_hanfun_iSimpleThermostatServerReq_uint16_t autoModeHeatTemperature;
    openD_hanfun_iSimpleThermostatServerReq_uint16_t autoModeCoolTemperature;
    openD_hanfun_iSimpleThermostatServerReq_uint16_t heatModeTemperatureOffset;
    openD_hanfun_iSimpleThermostatServerReq_uint16_t coolModeTemperatureOffset;
    openD_hanfun_iSimpleThermostatServerCfm_uint8_t boostDuration;
  } param;
} openD_hanfun_iSimpleThermostatServerReq_t;

/**
 * openD Hanfun iSimpleThermostat server confirm structure.
 */
typedef struct openD_hanfun_iSimpleThermostatServerCfm {
  /**
   * Hanfun iSimpleThermostat server service.
   */
  openD_hanfun_iSimpleThermostatServer_service_t service;

  /**
   * Hanfun iSimpleThermostat parameters.
   */
  union {
    openD_hanfun_iSimpleThermostatServerCfm_uint8_t supportedModes;
    openD_hanfun_iSimpleThermostatServerCfm_uint8_t mode;
    openD_hanfun_iSimpleThermostatServerCfm_uint8_t fanMode;
    openD_hanfun_iSimpleThermostatServerCfm_uint16_t heatModeTemperature;
    openD_hanfun_iSimpleThermostatServerCfm_uint16_t coolModeTemperature;
    openD_hanfun_iSimpleThermostatServerCfm_uint16_t autoModeHeatTemperature;
    openD_hanfun_iSimpleThermostatServerCfm_uint16_t autoModeCoolTemperature;
    openD_hanfun_iSimpleThermostatServerCfm_uint16_t heatModeTemperatureOffset;
    openD_hanfun_iSimpleThermostatServerCfm_uint16_t coolModeTemperatureOffset;
    openD_hanfun_iSimpleThermostatServerCfm_uint8_t boostDuration;
  } param;
} openD_hanfun_iSimpleThermostatServerCfm_t;

/**
 * openD Hanfun iSimpleThermostat server indication structure.
 */
typedef struct openD_hanfun_iSimpleThermostatServerInd {
  /**
   * Hanfun iSimpleThermostat server service.
   */
  openD_hanfun_iSimpleThermostatServer_service_t service;

  /**
   * Hanfun iSimpleThermostat parameters.
   */
  union {
    openD_hanfun_iSimpleThermostatServerInd_addr_t boostStart;
    openD_hanfun_iSimpleThermostatServerInd_addr_t boostStop;
  } param;
} openD_hanfun_iSimpleThermostatServerInd_t;


/*! @} defgroup OPEND_HANFUN_ISIMPLETHERMOSTAT */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ISIMPLETHERMOSTAT_H__ */
#ifdef __cplusplus
}
#endif
