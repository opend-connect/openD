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
 * @file       opend_hanfun_api.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN API.
 *
 * @defgroup   OPEND_HANFUN_API openD HAN-FUN API
 *             This module specifies the HAN-FUN API of openD connect.
 * @{
 *
 * @defgroup   OPEND_HANFUN_INTERFACE Interfaces
 * @defgroup   OPEND_HANFUN_PROFILE Profiles
 */

#ifndef __OPEND_HANFUN_API_H__
#define __OPEND_HANFUN_API_H__

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
    * UID.
    */
  uint16_t uid;
} hanfunApiDevMgmt_registrationElement_t;

/**
 * openD HanfunApi device management services.
 */
typedef enum openD_hanfunApi_devMgmt_service {
  /**
   * HAN-FUN device management enable or disable registration.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER,
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
   * HAN-FUN device management get address.
   */
  OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_ADDRESS,
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
   * HAN-FUN bind management remove.
   */
  OPEND_HANFUNAPI_BIND_MANAGEMENT_REMOVE,
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

  /**
   * openD HanfunApi bind management parameters.
   */
  // union {
  // TBD;
  // } param;
} openD_hanfunApi_bindMgmtReq_t;

/**
 * openD HanfunApi bind management confirm structure.
 */
typedef struct openD_hanfunApi_bindMgmtCfm {
  /**
   * HanfunApi bind management service.
   */
  openD_hanfunApi_bindMgmt_service_t service;
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


/**
 * openD HanfunApi primitives structure.
 */
typedef struct openD_hanfunApiPrimitives {
  /**
   * @brief   HanfunApi device management confirm primitive.
   *
   * @param   hDevMgmtConfirm Pointer of the HanfunApi confirm structure (@ref openD_hanfunApi_devMgmtCfm_t).
   */
  void ( *openD_hanfunApi_mgmtCfm )( openD_hanfunApi_devMgmtCfm_t *hDevMgmtConfirm );
  /**
   * @brief   HanfunApi device management indication primitive.
   *
   * @param   hDevMgmtIndication Pointer of the HanfunApi indication structure (@ref openD_hanfunApi_devMgmtInd_t).
   */
  void ( *openD_hanfunApi_mgmtInd )( openD_hanfunApi_devMgmtInd_t *hDevMgmtIndication );

  /**
   * @brief   HanfunApi bind confirm primitive.
   *
   * @param   hBindMgmtConfirm Pointer of the HanfunApi confirm structure (@ref openD_hanfunApi_bindMgmtCfm_t).
   */
  void ( *openD_hanfunApi_bindCfm )( openD_hanfunApi_bindMgmtCfm_t *hBindMgmtConfirm );
  /**
   * @brief   HanfunApi bind indication primitive.
   *
   * @param   hBindMgmtIndication Pointer of the HanfunApi indication structure (@ref openD_hanfunApi_bindMgmtInd_t).
   */
  void ( *openD_hanfunApiBindInd )( openD_hanfunApi_bindMgmtInd_t *hBindMgmtIndication );

  /**
   * @brief   HanfunApi profile confirm primitive.
   *
   * @param   hConfirm Pointer of the HanfunApi confirm structure (@ref openD_hanfunApi_profileCfm_t).
   */
  void ( *openD_hanfunApiProfileCfm )( openD_hanfunApi_profileCfm_t *hProfileConfirm );
  /**
   * @brief   HanfunApi profile indication primitive.
   *
   * @param   hIndication Pointer of the HanfunApi indication structure (@ref openD_hanfunApi_profileInd_t).
   */
  void ( *openD_hanfunApiProfileInd )( openD_hanfunApi_profileInd_t *hProfileIndication );
} openD_hanfunApiPrimitives_t;

/**
 * @brief   openD HAN-FUN API initialization.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   hPrimitives Pointer of the HAN-FUN API primitives structure (@ref openD_hanfunApiPrimitives_t).
 * @param   operationMode Operation mode of HAN-FUN (@ref openD_hanfunApi_operationMode_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_init( openD_hanfunApiPrimitives_t *hPrimitives, openD_hanfunApi_operationMode_t operationMode );

/**
 * @brief   openD HAN-FUN API device management request.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   hMgmtRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApi_devMgmtReq_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_devMgmtRequest( openD_hanfunApi_devMgmtReq_t *hMgmtRequest );

/**
 * @brief   openD HAN-FUN API bind management request.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   hBindRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApi_bindMgmtReq_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_bindMgmtRequest( openD_hanfunApi_bindMgmtReq_t *hBindRequest );

/**
 * @brief   openD HAN-FUN API profile request.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   hProfileRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApi_profileReq_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_profileRequest( openD_hanfunApi_profileReq_t *hProfileRequest );


/*! @} defgroup OPEND_HANFUN_API */

#endif /* __OPEND_HANFUN_API_H__ */
#ifdef __cplusplus
}
#endif
