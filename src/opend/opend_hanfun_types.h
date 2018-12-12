/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_types.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief      openD HAN-FUN TYPES.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_HANFUN_TYPES openD HAN-FUN TYPES
 *             This file specifies the HAN-FUN TYPES of openD connect.
 * @{
 *
 */

#ifndef __OPEND_HANFUN_TYPES_H__
#define __OPEND_HANFUN_TYPES_H__

#include "opend_dataTypes.h"

#include "hanfun/profiles/opend_hanfun_pAcOutlet.h"
#include "hanfun/profiles/opend_hanfun_pAcOutletWithPowerMetering.h"
#include "hanfun/profiles/opend_hanfun_pAlertable.h"
#include "hanfun/profiles/opend_hanfun_pColourBulb.h"
#include "hanfun/profiles/opend_hanfun_pControlableThermostat.h"
#include "hanfun/profiles/opend_hanfun_pDimmableColourBulb.h"
#include "hanfun/profiles/opend_hanfun_pDimmableLight.h"
#include "hanfun/profiles/opend_hanfun_pDimmerSwitch.h"
#include "hanfun/profiles/opend_hanfun_pDoorBell.h"
#include "hanfun/profiles/opend_hanfun_pDoorOpenCloseDetector.h"
#include "hanfun/profiles/opend_hanfun_pEnvironmentMonitor.h"
#include "hanfun/profiles/opend_hanfun_pFloodDetector.h"
#include "hanfun/profiles/opend_hanfun_pGasDetector.h"
#include "hanfun/profiles/opend_hanfun_pGlassBreakDetector.h"
#include "hanfun/profiles/opend_hanfun_pMotionDetector.h"
#include "hanfun/profiles/opend_hanfun_pSimpleAirPressureSensor.h"
#include "hanfun/profiles/opend_hanfun_pSimpleButton.h"
#include "hanfun/profiles/opend_hanfun_pSimpleDetector.h"
#include "hanfun/profiles/opend_hanfun_pSimpleDoorLock.h"
#include "hanfun/profiles/opend_hanfun_pSimpleHumiditySensor.h"
#include "hanfun/profiles/opend_hanfun_pSimpleLed.h"
#include "hanfun/profiles/opend_hanfun_pSimpleLevelControl.h"
#include "hanfun/profiles/opend_hanfun_pSimpleLevelControllable.h"
#include "hanfun/profiles/opend_hanfun_pSimpleLevelControllableSwitchable.h"
#include "hanfun/profiles/opend_hanfun_pSimpleLevelControlSwitch.h"
#include "hanfun/profiles/opend_hanfun_pSimpleLight.h"
#include "hanfun/profiles/opend_hanfun_pSimpleLightSensor.h"
#include "hanfun/profiles/opend_hanfun_pSimpleOnOffSwitch.h"
#include "hanfun/profiles/opend_hanfun_pSimpleOnOffSwitchable.h"
#include "hanfun/profiles/opend_hanfun_pSimplePendant.h"
#include "hanfun/profiles/opend_hanfun_pSimplePowerMeter.h"
#include "hanfun/profiles/opend_hanfun_pSimpleTemperatureSensor.h"
#include "hanfun/profiles/opend_hanfun_pSiren.h"
#include "hanfun/profiles/opend_hanfun_pSmokeDetector.h"
#include "hanfun/profiles/opend_hanfun_pUserInterfaceLock.h"
#include "hanfun/profiles/opend_hanfun_pVibrationDetector.h"
#include "hanfun/profiles/opend_hanfun_pWindowOpenCloseDetector.h"

#include "hanfun.h"


/**
 * openD HanfunApi operation modes.
 */
typedef enum openD_hanfunApi_operationMode {
  /**
   * HAN-FUN concentrator operation mode.
   */
  OPEND_HANFUNAPI_CONCENTRATOR,
  /**
   * HAN-FUN node operation mode.
   */
  OPEND_HANFUNAPI_NODE,
} openD_hanfunApi_operationMode_t;

/**
 * openD HanfunApi device management register structure.
 */
typedef struct hanfunApiDevMgmt_register {
  /**
    * Register enable.
    */
  bool enable;
  /**
    * Device address.
    */
  uint16_t address;
} hanfunApiDevMgmt_register_t;

/**
 * openD HanfunApi device management de-register structure.
 */
typedef struct hanfunApiDevMgmt_deregister {
  /**
    * Device address.
    */
  uint16_t address;
} hanfunApiDevMgmt_deregister_t;

/**
 * openD HanfunApi device management registration element structure.
 */
typedef struct hanfunApiDevMgmt_registrationElement {
  /**
    * Device address.
    */
  uint16_t address;
  /**
    * Addresses of currently registered Devices.
    */
  uint16_t addresses[20];
  /**
    * UID.
    */
  uint8_t uid[100];
  /**
    * Size of currently registered Devices.
    */
  uint16_t size;
} hanfunApiDevMgmt_registrationElement_t;

/*!
 * Network Address.
 */
typedef struct networkAddress
{
  uint16_t mod    : 1;    //!< Address modifier.
  uint16_t device : 15;   //!< Device Address.

  uint8_t  unit;          //!< Source Unit.
} networkAddress_t;

/*!
 * Interface UID.
 */
typedef struct interfaceUid
{
  uint16_t role : 1;  //!< Interface role : Server or Client.
  uint16_t id   : 15; //!< Identifier of the interface. @see Interface::UID.
} interfaceUid_t;

/*!
 * Device pair to bind.
 */
typedef struct devicesToBind
{
  /**
    * Device1 address.
    */
  uint16_t address1;
  /**
    * Device2 address.
    */
  uint16_t address2;
} devicesToBind_t;

/**
 * openD HanfunApi bind management entries element structure.
 */
typedef struct hanfunApiBindMgmt_entriesElement {
  /**
    * Network address source.
    */
  networkAddress_t src[20];
  /**
    * Network address destination.
    */
  networkAddress_t dst[20];
  /**
   * Interface UID.
   */
  interfaceUid_t itf[20];
  /**
    * Size of the bind management entries.
    */
  uint8_t entriesSize;
  /**
    * Error handling variable for the bind management.
    */
  uint8_t error;
  /**
    * Devices to create a bind.
    */
  devicesToBind_t devicesToBind;
} hanfunApiBindMgmt_entriesElement_t;

/**
 * openD HanfunApi device management services.
 */
typedef enum openD_hanfunApi_devMgmt_service {
  /**
   * HAN-FUN device management enable registration.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_ENABLE,
  /**
   * HAN-FUN device management disable registration.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DISABLE,
  /**
   * HAN-FUN device management de-register a device.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_DEREGISTER,
  /**
   * HAN-FUN device management register a device.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE,
  /**
   * HAN-FUN device management get the first element of the registrations.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_FIRST_REGISTRATION,
  /**
   * HAN-FUN device management get the next element of the registrations.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_NEXT_REGISTRATION,
  /**
   * HAN-FUN device management no further elements of the registrations.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_NO_FURTHER_REGISTRATION,
  /**
   * HAN-FUN device management set address.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_SET_ADDRESS,
  /**
   * HAN-FUN device management get address.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_ADDRESS,
  /**
   * HAN-FUN device management get entries registration.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_REGISTRATION,
  /**
   * HAN-FUN device management get entries registration.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_LINK,
  /**
   * HAN-FUN device management get device information mandatory.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_INFORMATION_MANDATORY,
  /**
   * HAN-FUN device management get device information all.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_INFORMATION_ALL,
  /**
   * HAN-FUN device management change concentrator dect mode.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_CHANGE_CONCENTRATOR_DECT_MODE,
} openD_hanfunApi_devMgmt_service_t;

/**
 * openD HanfunApi device management request structure.
 */
typedef struct openD_hanfunApi_devMgmtReq {
  /**
   * HanfunApi device management service.
   */
  openD_hanfunApi_devMgmt_service_t service;

  /**
   * openD HanfunApi device management parameters.
   */
  union {
    hanfunApiDevMgmt_register_t dev_register;
    hanfunApiDevMgmt_deregister_t dev_deregister;
  } param;
} openD_hanfunApi_devMgmtReq_t;

/**
 * openD HanfunApi device management confirm structure.
 */
typedef struct openD_hanfunApi_devMgmtCfm {
  /**
   * HanfunApi device management service.
   */
  openD_hanfunApi_devMgmt_service_t service;
  /**
   * HanfunApi service status.
   */
  openD_status_t status;
  /**
   * openD HanfunApi device management parameters.
   */
  union {
    hanfunApiDevMgmt_registrationElement_t registrationElement;
  } param;
} openD_hanfunApi_devMgmtCfm_t;

/**
 * openD HanfunApi device management indication structure.
 */
typedef struct openD_hanfunApi_devMgmtInd {
  /**
   * HanfunApi device management service.
   */
  openD_hanfunApi_devMgmt_service_t service;
} openD_hanfunApi_devMgmtInd_t;

/**
 * openD HanfunApi bind management services.
 */
typedef enum openD_hanfunApi_bindMgmt_service {
  /**
   * HAN-FUN bind management add.
   */
  OPEND_HANFUNAPI_BIND_MANAGEMENT_ADD,
  /**
   * HAN-FUN bind management add global bind.
   */
  OPEND_HANFUNAPI_BIND_MANAGEMENT_ADD_GLOBAL_BIND,
  /**
   * HAN-FUN bind management remove.
   */
  OPEND_HANFUNAPI_BIND_MANAGEMENT_REMOVE,
  /**
   * HAN-FUN bind management remove global bind.
   */
  OPEND_HANFUNAPI_BIND_MANAGEMENT_REMOVE_GLOBAL_BIND,
  /**
   * HAN-FUN bind management get entries.
   */
  OPEND_HANFUNAPI_BIND_MANAGEMENT_ENTRIES,

} openD_hanfunApi_bindMgmt_service_t;

/**
 * openD HanfunApi bind management request structure.
 */
typedef struct openD_hanfunApi_bindMgmtReq {
  /**
   * HanfunApi bind management service.
   */
  openD_hanfunApi_bindMgmt_service_t service;
} openD_hanfunApi_bindMgmtReq_t;

/**
 * openD HanfunApi bind management confirm structure.
 */
typedef struct openD_hanfunApi_bindMgmtCfm {
  /**
   * HanfunApi bind management service.
   */
  openD_hanfunApi_bindMgmt_service_t service;
  /**
   * HanfunApi service status.
   */
  openD_status_t status;
  union {
    hanfunApiBindMgmt_entriesElement_t entriesElement;
  } param;
} openD_hanfunApi_bindMgmtCfm_t;

/**
 * openD HanfunApi bind management indication structure.
 */
typedef struct openD_hanfunApi_bindMgmtInd {
  /**
   * HanfunApi bind management service.
   */
  openD_hanfunApi_bindMgmt_service_t service;
} openD_hanfunApi_bindMgmtInd_t;

/**
 * openD HanfunApi profiles.
 */
typedef enum openD_hanfunApi_profile {
  /**
   * HAN-FUN Profile SIMPLE_ONOFF_SWITCHABLE.
   */
  OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCHABLE,
  /**
   * HAN-FUN Profile SIMPLE_ONOFF_SWITCH.
   */
  OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH,
  /**
   * HAN-FUN Profile SIMPLE_LEVEL_CONTROLLABLE.
   */
  OPEND_HANFUNAPI_SIMPLE_LEVEL_CONTROLLABLE,
  /**
   * HAN-FUN Profile SIMPLE_LEVEL_CONTROL.
   */
  OPEND_HANFUNAPI_SIMPLE_LEVEL_CONTROL,
  /**
   * HAN-FUN Profile SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE.
   */
  OPEND_HANFUNAPI_SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE,
  /**
   * HAN-FUN Profile SIMPLE_LEVEL_CONTROL_SWITCH.
   */
  OPEND_HANFUNAPI_SIMPLE_LEVEL_CONTROL_SWITCH,
  /**
   * HAN-FUN Profile AC_OUTLET.
   */
  OPEND_HANFUNAPI_AC_OUTLET,
  /**
   * HAN-FUN Profile AC_OUTLET_WITH_POWER_METERING.
   */
  OPEND_HANFUNAPI_AC_OUTLET_WITH_POWER_METERING,
  /**
   * HAN-FUN Profile SIMPLE_LIGHT.
   */
  OPEND_HANFUNAPI_SIMPLE_LIGHT,
  /**
   * HAN-FUN Profile DIMMABLE_LIGHT.
   */
  OPEND_HANFUNAPI_DIMMABLE_LIGHT,
  /**
   * HAN-FUN Profile DIMMER_SWITCH.
   */
  OPEND_HANFUNAPI_DIMMER_SWITCH,
  /**
   * HAN-FUN Profile SIMPLE_DOOR_LOCK.
   */
  OPEND_HANFUNAPI_SIMPLE_DOOR_LOCK,
  /**
   * HAN-FUN Profile DOOR_BELL.
   */
  OPEND_HANFUNAPI_DOOR_BELL,
  /**
   * HAN-FUN Profile SIMPLE_POWER_METER.
   */
  OPEND_HANFUNAPI_SIMPLE_POWER_METER,
  /**
   * HAN-FUN Profile SIMPLE_TEMPERATURE_SENSOR.
   */
  OPEND_HANFUNAPI_SIMPLE_TEMPERATURE_SENSOR,
  /**
   * HAN-FUN Profile SIMPLE_HUMIDITY_SENSOR.
   */
  OPEND_HANFUNAPI_SIMPLE_HUMIDITY_SENSOR,
  /**
   * HAN-FUN Profile SIMPLE_AIR_PRESSURE_SENSOR.
   */
  OPEND_HANFUNAPI_SIMPLE_AIR_PRESSURE_SENSOR,
  /**
   * HAN-FUN Profile SIMPLE_BUTTON.
   */
  OPEND_HANFUNAPI_SIMPLE_BUTTON,
  /**
   * HAN-FUN Profile CONTROLABLE_THERMOSTAT.
   */
  OPEND_HANFUNAPI_CONTROLABLE_THERMOSTAT,
  /**
   * HAN-FUN Profile SIMPLE_LED.
   */
  OPEND_HANFUNAPI_SIMPLE_LED,
  /**
   * HAN-FUN Profile ENVIRONMENT_MONITOR.
   */
  OPEND_HANFUNAPI_ENVIRONMENT_MONITOR,
  /**
   * HAN-FUN Profile COLOUR_BULB.
   */
  OPEND_HANFUNAPI_COLOUR_BULB,
  /**
   * HAN-FUN Profile DIMMABLE_COLOUR_BULB.
   */
  OPEND_HANFUNAPI_DIMMABLE_COLOUR_BULB,
  /**
   * HAN-FUN Profile SIMPLE_DETECTOR.
   */
  OPEND_HANFUNAPI_SIMPLE_DETECTOR,
  /**
   * HAN-FUN Profile DOOR_OPEN_CLOSE_DETECTOR.
   */
  OPEND_HANFUNAPI_DOOR_OPEN_CLOSE_DETECTOR,
  /**
   * HAN-FUN Profile WINDOW_OPEN_CLOSE_DETECTOR.
   */
  OPEND_HANFUNAPI_WINDOW_OPEN_CLOSE_DETECTOR,
  /**
   * HAN-FUN Profile MOTION_DETECTOR.
   */
  OPEND_HANFUNAPI_MOTION_DETECTOR,
  /**
   * HAN-FUN Profile SMOKE_DETECTOR.
   */
  OPEND_HANFUNAPI_SMOKE_DETECTOR,
  /**
   * HAN-FUN Profile GAS_DETECTOR.
   */
  OPEND_HANFUNAPI_GAS_DETECTOR,
  /**
   * HAN-FUN Profile FLOOD_DETECTOR.
   */
  OPEND_HANFUNAPI_FLOOD_DETECTOR,
  /**
   * HAN-FUN Profile GLASS_BREAK_DETECTOR.
   */
  OPEND_HANFUNAPI_GLASS_BREAK_DETECTOR,
  /**
   * HAN-FUN Profile VIBRATION_DETECTOR.
   */
  OPEND_HANFUNAPI_VIBRATION_DETECTOR,
  /**
   * HAN-FUN Profile SIMPLE_LIGHT_SENSOR.
   */
  OPEND_HANFUNAPI_SIMPLE_LIGHT_SENSOR,
  /**
   * HAN-FUN Profile SIREN.
   */
  OPEND_HANFUNAPI_SIREN,
  /**
   * HAN-FUN Profile ALERTABLE.
   */
  OPEND_HANFUNAPI_ALERTABLE,
  /**
   * HAN-FUN Profile SIMPLE_PENDANT.
   */
  OPEND_HANFUNAPI_SIMPLE_PENDANT,
  /**
   * HAN-FUN Profile USER_INTERFACE_LOCK.
   */
  OPEND_HANFUNAPI_USER_INTERFACE_LOCK,

} openD_hanfunApi_profile_t;

/**
 * openD HanfunApi profile request structure.
 */
typedef struct openD_hanfunApi_profileReq {
  /**
   * openD HanfunApi profile.
   */
  openD_hanfunApi_profile_t profile;

  /**
   * openD HanfunApi profile structure.
   */
  union {
    openD_hanfun_pAcOutletReq_t acOutlet;
    openD_hanfun_pAcOutletWithPowerMeteringReq_t acOutletWithPowerMetering;
    openD_hanfun_pColourBulbReq_t colourBulb;
    openD_hanfun_pControlableThermostatReq_t controlableThermostat;
    openD_hanfun_pDimmableColourBulbReq_t dimmableColourBulb;
    openD_hanfun_pDimmableLightReq_t dimmableLight;
    openD_hanfun_pDimmerSwitchReq_t dimmerSwitch;
    openD_hanfun_pDoorBellReq_t doorBell;
    openD_hanfun_pDoorOpenCloseDetectorReq_t doorOpenCloseDetector;
    openD_hanfun_pEnvironmentMonitorReq_t environmentMonitor;
    openD_hanfun_pFloodDetectorReq_t floodDetector;
    openD_hanfun_pGasDetectorReq_t gasDetector;
    openD_hanfun_pGlassBreakDetectorReq_t glassBreakDetector;
    openD_hanfun_pMotionDetectorReq_t motionDetector;
    openD_hanfun_pSimpleAirPressureSensorReq_t simpleAirPressureSensor;
    openD_hanfun_pSimpleButtonReq_t simpleButton;
    openD_hanfun_pSimpleDetectorReq_t simpleDetector;
    openD_hanfun_pSimpleDoorLockReq_t simpleDoorLock;
    openD_hanfun_pSimpleHumiditySensorReq_t simpleHumiditySensor;
    openD_hanfun_pSimpleLevelControlReq_t simpleLevelControl;
    openD_hanfun_pSimpleLevelControllableReq_t simpleLevelControllable;
    openD_hanfun_pSimpleLevelControllableSwitchableReq_t simpleLevelControllableSwitchable;
    openD_hanfun_pSimpleLevelControlSwitchReq_t simpleLevelControlSwitch;
    openD_hanfun_pSimpleLightReq_t simpleLight;
    openD_hanfun_pSimpleLightSensorReq_t simpleLightSensor;
    openD_hanfun_pSimpleOnOffSwitchReq_t simpleOnOffSwitch;
    openD_hanfun_pSimpleOnOffSwitchableReq_t simpleOnOffSwitchable;
    openD_hanfun_pSimplePendantReq_t simplePendant;
    openD_hanfun_pSimplePowerMeterReq_t simplePowerMeter;
    openD_hanfun_pSimpleTemperatureSensorReq_t simpleTemperatureSensor;
    openD_hanfun_pSirenReq_t siren;
    openD_hanfun_pSmokeDetectorReq_t smokeDetector;
    openD_hanfun_pUserInterfaceLockReq_t userInterfaceLock;
    openD_hanfun_pVibrationDetectorReq_t vibrationDetector;
    openD_hanfun_pWindowOpenCloseDetectorReq_t windowOpenCloseDetector;
  };
} openD_hanfunApi_profileReq_t;

/**
 * openD HanfunApi profile confirm structure.
 */
typedef struct openD_hanfunApi_profileCfm {
  /**
   * openD HanfunApi profile.
   */
  openD_hanfunApi_profile_t profile;
  /**
   * HanfunApi service status.
   */
  openD_status_t status;
  /**
   * openD HanfunApi profile structure.
   */
  union {
    openD_hanfun_pAcOutletCfm_t acOutlet;
    openD_hanfun_pAcOutletWithPowerMeteringCfm_t acOutletWithPowerMetering;
    openD_hanfun_pColourBulbCfm_t colourBulb;
    openD_hanfun_pControlableThermostatCfm_t controlableThermostat;
    openD_hanfun_pDimmableColourBulbCfm_t dimmableColourBulb;
    openD_hanfun_pDimmableLightCfm_t dimmableLight;
    openD_hanfun_pDoorBellCfm_t doorBell;
    openD_hanfun_pEnvironmentMonitorCfm_t environmentMonitor;
    openD_hanfun_pSimpleAirPressureSensorCfm_t simpleAirPressureSensor;
    openD_hanfun_pSimpleButtonCfm_t simpleButton;
    openD_hanfun_pSimpleDoorLockCfm_t simpleDoorLock;
    openD_hanfun_pSimpleHumiditySensorCfm_t simpleHumiditySensor;
    openD_hanfun_pSimpleLevelControllableCfm_t simpleLevelControllable;
    openD_hanfun_pSimpleLevelControllableSwitchableCfm_t simpleLevelControllableSwitchable;
    openD_hanfun_pSimpleLightCfm_t simpleLight;
    openD_hanfun_pSimpleLightSensorCfm_t simpleLightSensor;
    openD_hanfun_pSimpleOnOffSwitchableCfm_t simpleOnOffSwitchable;
    openD_hanfun_pSimpleOnOffSwitchCfm_t simpleOnOffSwitch;
    openD_hanfun_iDetectorCfm_t motionDetector;
    openD_hanfun_pSimplePowerMeterCfm_t simplePowerMeter;
    openD_hanfun_pSimpleTemperatureSensorCfm_t simpleTemperatureSensor;
    openD_hanfun_pSirenCfm_t siren;
    openD_hanfun_pUserInterfaceLockCfm_t userInterfaceLock;
  };
} openD_hanfunApi_profileCfm_t;

/**
 * openD HanfunApi profile indication structure.
 */
typedef struct openD_hanfunApi_profileInd {
  /**
   * openD HanfunApi profile.
   */
  openD_hanfunApi_profile_t profile;
  /**
   * HanfunApi service status.
   */
  openD_status_t status;
  /**
   * openD HanfunApi profile structure.
   */
  union {
    openD_hanfun_pAcOutletInd_t acOutlet;
    openD_hanfun_pAcOutletWithPowerMeteringInd_t acOutletWithPowerMetering;
    openD_hanfun_pAlertableInd_t pAlertable;
    openD_hanfun_pColourBulbInd_t colourBulb;
    openD_hanfun_pControlableThermostatInd_t  controlableThermostat;
    openD_hanfun_pDimmableColourBulbInd_t dimmableColourBulb;
    openD_hanfun_pDimmableLightInd_t dimmableLight;
    openD_hanfun_pSimpleDoorLockInd_t simpleDoorLock;
    openD_hanfun_pSimpleLedInd_t simpleLed;
    openD_hanfun_pSimpleLevelControllableInd_t simpleLevelControllable;
    openD_hanfun_pSimpleLevelControllableSwitchableInd_t simpleLevelControllableSwitchable;
    openD_hanfun_pSimpleLightInd_t simpleLight;
    openD_hanfun_pSimpleOnOffSwitchableInd_t simpleOnOffSwitchable;
    openD_hanfun_pSirenInd_t siren;
    openD_hanfun_pUserInterfaceLockInd_t userInterfaceLock;
  };
} openD_hanfunApi_profileInd_t;

/*! @} defgroup OPEND_HANFUN_TYPES */

#endif /* __OPEND_HANFUN_TYPES_H__ */
