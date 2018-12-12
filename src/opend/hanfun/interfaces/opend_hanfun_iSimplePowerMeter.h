/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iSimplePowerMeter.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iSimplePowerMeter.
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
 * @defgroup   OPEND_HANFUN_ISIMPLEPOWERMETER openD HAN-FUN iSimplePowerMeter
 *             This module specifies the HAN-FUN simple power meter interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ISIMPLEPOWERMETER_H__
#define __OPEND_HANFUN_ISIMPLEPOWERMETER_H__

#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iSimplePowerMeter client services.
 */
typedef enum openD_hanfun_iSimplePowerMeterClient_service {
  /**
   * Report message from a server.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_CLIENT_REPORT,

} openD_hanfun_iSimplePowerMeterClient_service_t;

/**
 * openD Hanfun iSimplePowerMeter server services.
 */
typedef enum openD_hanfun_iSimplePowerMeterServer_service {
  /**
   * Get the energy measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_ENERGY,
  /**
   * Set the energy measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_ENERGY,
  /**
   * Get the energy measurement value at the last reset.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_LASTENERGY,
  /**
   * Set the energy measurement value at the last reset.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_LASTENERGY,
  /**
   * Get the device time value at the last reset.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_LASTTIME,
  /**
   * Set the device time value at the last reset.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_LASTTIME,
  /**
   * Get the instantaneous power measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_POWER,
  /**
   * Set the instantaneous power measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_POWER,
  /**
   * Get the average power measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_AVGPOWER,
  /**
   * Set the average power measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_AVGPOWER,
  /**
   * Get the average power interval value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_AVGPOWERINTERVAL,
  /**
   * Set the average power interval measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_AVGPOWERINTERVAL,
  /**
   * Get the power factor value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_POWERFACTOR,
  /**
   * Set the power factor measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_POWERFACTOR,
  /**
   * Get the voltage measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_VOLTAGE,
  /**
   * Set the voltage measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_VOLTAGE,
  /**
   * Get the current measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_CURRENT,
  /**
   * Set the current measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_CURRENT,
  /**
   * Get the frequency measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_FREQUENCY,
  /**
   * Set the frequency energy measurement value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_FREQUENCY,
  /**
   * Get the report interval value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_GET_REPORTINTERVAL,
  /**
   * Set the report interval value for the meter.
   */
  OPEND_HANFUN_ISIMPLEPOWERMETER_SERVER_SET_REPORTINTERVAL,

} openD_hanfun_iSimplePowerMeterServer_service_t;

/**
 * openD Hanfun iSimplePowerMeter measurement structure.
 */
typedef struct openD_hanfun_iSimplePowerMeter_measurement {
  /**
   * Measurement precision.
   */
  uint8_t  unit;
  /**
   * Measurement value.
   */
  uint32_t value;
} openD_hanfun_iSimplePowerMeter_measurement_t;

/**
 * openD Hanfun iSimplePowerMeter report structure.
 */
typedef struct openD_hanfun_iSimplePowerMeter_report {
  /**
   * Energy measurement.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t energy;
  /**
   * Energy measurement at last reset.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t last_energy;
  /**
   * Device time measurement at last reset.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t last_time;
  /**
   * Instantaneous Power measurement.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t power;
  /**
   * Average Power measurement.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t avg_power;
  /**
   * Average Power Interval.
   */
  uint16_t avg_power_interval;
  /**
   * Power Factor.
   */
  uint8_t power_factor;
  /**
   * Voltage measurement.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t voltage;
  /**
   * Current measurement.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t current;
  /**
   * Frequency measurement.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t frequency;

} openD_hanfun_iSimplePowerMeter_report_t;

/**
 * openD Hanfun iSimplePowerMeter client indication parameter structure of the @c REPORT service.
 */
typedef struct openD_hanfun_iSimplePowerMeterClientInd_report {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * Report.
   */
  openD_hanfun_iSimplePowerMeter_report_t report;

} openD_hanfun_iSimplePowerMeterClientInd_report_t;

/**
 * openD Hanfun iSimplePowerMeter server request parameter structure of the @c SET_ENERGY, @c SET_LASTENERGY, @c SET_LASTTIME, @c SET_POWER, @c SET_AVGPOWER, @c SET_VOLTAGE, @c SET_CURRENT and @c SET_FREQUENCY service.
 */
typedef struct openD_hanfun_iSimplePowerMeterServerReq_measurement {
  /**
   * Value.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t value;
} openD_hanfun_iSimplePowerMeterServerReq_measurement_t;

/**
 * openD Hanfun iSimplePowerMeter server confirm parameter structure of the @c GET_ENERGY, @c GET_LASTENERGY, @c GET_LASTTIME, @c GET_POWER, @c GET_AVGPOWER, @c GET_VOLTAGE, @c GET_CURRENT and @c GET_FREQUENCY service.
 */
typedef struct openD_hanfun_iSimplePowerMeterServerCfm_measurement {
  /**
   * Value.
   */
  openD_hanfun_iSimplePowerMeter_measurement_t value;
} openD_hanfun_iSimplePowerMeterServerCfm_measurement_t;

/**
 * openD Hanfun iSimplePowerMeter server request parameter structure of the @c SET_AVGPOWERINTERVAL and @c SET_REPORTINTERVAL service.
 */
typedef struct openD_hanfun_iSimplePowerMeterServerReq_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimplePowerMeterServerReq_uint16_t;

/**
 * openD Hanfun iSimplePowerMeter server confirm parameter structure of the @c GET_AVGPOWERINTERVAL and @c GET_REPORTINTERVAL service.
 */
typedef struct openD_hanfun_iSimplePowerMeterServerCfm_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimplePowerMeterServerCfm_uint16_t;

/**
 * openD Hanfun iSimplePowerMeter server request parameter structure of the @c SET_POWERFACTOR service.
 */
typedef struct openD_hanfun_iSimplePowerMeterServerReq_uint8 {
  /**
   * Value.
   */
  uint8_t value;
} openD_hanfun_iSimplePowerMeterServerReq_uint8_t;

/**
 * openD Hanfun iSimplePowerMeter server confirm parameter structure of the @c GET_POWERFACTOR service.
 */
typedef struct openD_hanfun_iSimplePowerMeterServerCfm_uint8 {
  /**
   * Value.
   */
  uint8_t value;
} openD_hanfun_iSimplePowerMeterServerCfm_uint8_t;

/**
 * openD Hanfun iSimplePowerMeter client indication structure.
 */
typedef struct openD_hanfun_iSimplePowerMeterClientInd {
  /**
   * Hanfun iSimplePowerMeter client service.
   */
  openD_hanfun_iSimplePowerMeterClient_service_t service;

  /**
   * Hanfun iSimplePowerMeter parameters.
   */
  union {
    openD_hanfun_iSimplePowerMeterClientInd_report_t report;
  } param;
} openD_hanfun_iSimplePowerMeterClientInd_t;

/**
 * openD Hanfun iSimplePowerMeter server request structure.
 */
typedef struct openD_hanfun_iSimplePowerMeterServerReq {
  /**
   * Hanfun iSimplePowerMeter server service.
   */
  openD_hanfun_iSimplePowerMeterServer_service_t service;

  /**
   * Hanfun iSimplePowerMeter parameters.
   */
  union {
    openD_hanfun_iSimplePowerMeterServerReq_measurement_t setEnergy;
    openD_hanfun_iSimplePowerMeterServerReq_measurement_t setLastEnergy;
    openD_hanfun_iSimplePowerMeterServerReq_measurement_t setLastTime;
    openD_hanfun_iSimplePowerMeterServerReq_measurement_t setPower;
    openD_hanfun_iSimplePowerMeterServerReq_measurement_t setAvgPower;
    openD_hanfun_iSimplePowerMeterServerReq_uint16_t setAvgPowerInterval;
    openD_hanfun_iSimplePowerMeterServerReq_uint8_t setPowerFactor;
    openD_hanfun_iSimplePowerMeterServerReq_measurement_t setVoltage;
    openD_hanfun_iSimplePowerMeterServerReq_measurement_t setCurrent;
    openD_hanfun_iSimplePowerMeterServerReq_measurement_t setFrequency;
    openD_hanfun_iSimplePowerMeterServerReq_uint8_t setReportInterval;
  } param;
} openD_hanfun_iSimplePowerMeterServerReq_t;

/**
 * openD Hanfun iSimplePowerMeter server confirm structure.
 */
typedef struct openD_hanfun_iSimplePowerMeterServerCfm {
  /**
   * Hanfun iSimplePowerMeter server service.
   */
  openD_hanfun_iSimplePowerMeterServer_service_t service;

  /**
   * Hanfun iSimplePowerMeter parameters.
   */
  union {
    openD_hanfun_iSimplePowerMeterServerCfm_measurement_t getEnergy;
    openD_hanfun_iSimplePowerMeterServerCfm_measurement_t getLastEnergy;
    openD_hanfun_iSimplePowerMeterServerCfm_measurement_t getLastTime;
    openD_hanfun_iSimplePowerMeterServerCfm_measurement_t getPower;
    openD_hanfun_iSimplePowerMeterServerCfm_measurement_t getAvgPower;
    openD_hanfun_iSimplePowerMeterServerCfm_uint16_t getAvgPowerInterval;
    openD_hanfun_iSimplePowerMeterServerCfm_uint8_t getPowerFactor;
    openD_hanfun_iSimplePowerMeterServerCfm_measurement_t getVoltage;
    openD_hanfun_iSimplePowerMeterServerCfm_measurement_t getCurrent;
    openD_hanfun_iSimplePowerMeterServerCfm_measurement_t getFrequency;
    openD_hanfun_iSimplePowerMeterServerCfm_uint8_t getReportInterval;
  } param;
} openD_hanfun_iSimplePowerMeterServerCfm_t;


/*! @} defgroup OPEND_HANFUN_ISIMPLEPOWERMETER */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ISIMPLEPOWERMETER_H__ */
