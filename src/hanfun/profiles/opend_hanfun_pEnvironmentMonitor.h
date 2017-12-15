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
 * @file       opend_hanfun_pEnvironmentMonitor.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pEnvironmentMonitor.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PENVIRONMENTMONITOR openD HAN-FUN pEnvironmentMonitor
 *             This module specifies the HAN-FUN environment monitor profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PENVIRONMENTMONITOR_H__
#define __OPEND_HANFUN_PENVIRONMENTMONITOR_H__

#include "../interfaces/opend_hanfun_iSimpleTemperature.h"
#include "../interfaces/opend_hanfun_iSimpleHumidity.h"
#include "../interfaces/opend_hanfun_iSimpleAirPressure.h"

/**
 * openD Hanfun pEnvironmentMonitor interfaces.
 */
typedef enum openD_hanfun_pEnvironmentMonitor_interface {
  /**
   * Interface iSimpleTemperature.
   */
  OPEND_HANFUN_PENVIRONMENTMONITOR_ISIMPLETEMPERATURE,
  /**
   * Interface iSimpleHumidity.
   */
  OPEND_HANFUN_PENVIRONMENTMONITOR_ISIMPLEHUMIDITY,
  /**
   * Interface iSimpleAirPressure.
   */
  OPEND_HANFUN_PENVIRONMENTMONITOR_ISIMPLEAIRPRESSURE,
} openD_hanfun_pEnvironmentMonitor_interface_t;

/**
 * openD Hanfun pEnvironmentMonitor profile request structure.
 */
typedef struct openD_hanfun_pEnvironmentMonitorReq {
  /**
   * Interface.
   */
  openD_hanfun_pEnvironmentMonitor_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iSimpleTemperatureServerReq_t simpleTemperature;
    openD_hanfun_iSimpleHumidityServerReq_t simpleHumidityServer;
    openD_hanfun_iSimpleAirPressureServerReq_t simpleAirPressure;
  };
} openD_hanfun_pEnvironmentMonitorReq_t;

/**
 * openD Hanfun pEnvironmentMonitor profile confirm structure.
 */
typedef struct openD_hanfun_pEnvironmentMonitorCfm {
  /**
   * Interface.
   */
  openD_hanfun_pEnvironmentMonitor_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iSimpleTemperatureServerCfm_t simpleTemperature;
    openD_hanfun_iSimpleHumidityServerCfm_t simpleHumidityServer;
    openD_hanfun_iSimpleAirPressureServerCfm_t simpleAirPressure;
  };
} openD_hanfun_pEnvironmentMonitorCfm_t;


/*! @} defgroup OPEND_HANFUN_PENVIRONMENTMONITOR */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PENVIRONMENTMONITOR_H__ */
#ifdef __cplusplus
}
#endif
