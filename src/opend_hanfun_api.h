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

#include "hanfun/profiles/opend_hanfun_pSimpleLevelControllable.h"
#include "hanfun/profiles/opend_hanfun_pSimpleOnOffSwitchable.h"

/**
 * openD HanfunApi operation modes.
 */
typedef enum openD_hanfunApiOperationMode {
  /**
   * HAN-FUN concentrator operation mode.
   */
  HANFUNAPI_CONCENTRATOR,
  /**
   * HAN-FUN node operation mode.
   */
  HANFUNAPI_NODE,
} openD_hanfunApiOperationMode_t;


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
typedef enum openD_hanfunApiDevMgmtService {
  /**
   * HAN-FUN device management enable or disable registration.
   */
  HANFUNAPI_DEVICE_MANAGEMENT_REGISTER,
  /**
   * HAN-FUN device management de-register a device.
   */
  HANFUNAPI_DEVICE_MANAGEMENT_DEREGISTER,
  /**
   * HAN-FUN device management register a device.
   */
  HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE,
  /**
   * HAN-FUN device management get the first element of the registrations.
   */
  HANFUNAPI_DEVICE_MANAGEMENT_GET_FIRST_REGISTRATION,
  /**
   * HAN-FUN device management get the next element of the registrations.
   */
  HANFUNAPI_DEVICE_MANAGEMENT_GET_NEXT_REGISTRATION,
  /**
   * HAN-FUN device management no further elements of the registrations.
   */
  HANFUNAPI_DEVICE_MANAGEMENT_NO_FURTHER_REGISTRATION,
  /**
   * HAN-FUN device management get address.
   */
  HANFUNAPI_DEVICE_MANAGEMENT_GET_ADDRESS,
} openD_hanfunApiDevMgmtService_t;

/**
 * openD HanfunApi device management request structure.
 */
typedef struct openD_hanfunApiDevMgmtReq {
  /**
   * HanfunApi device management service.
   */
  openD_hanfunApiDevMgmtService_t service;

  /**
   * openD HanfunApi device management parameters.
   */
  union {
    hanfunApiDevMgmt_register_t dev_register;
    hanfunApiDevMgmt_deregister_t dev_deregister;
  } param;
} openD_hanfunApiDevMgmtReq_t;

/**
 * openD HanfunApi device management confirm structure.
 */
typedef struct openD_hanfunApiDevMgmtConfirm {
  /**
   * HanfunApi device management service.
   */
  openD_hanfunApiDevMgmtService_t service;
  /**
   * openD HanfunApi device management parameters.
   */
  union {
    hanfunApiDevMgmt_registrationElement_t registrationElement;
  } param;
} openD_hanfunApiDevMgmtConfirm_t;

/**
 * openD HanfunApi device management indication structure.
 */
typedef struct openD_hanfunApiDevMgmtIndication {
  /**
   * HanfunApi device management service.
   */
  openD_hanfunApiDevMgmtService_t service;
} openD_hanfunApiDevMgmtIndication_t;


/**
 * openD HanfunApi bind management services.
 */
typedef enum openD_hanfunApiBindMgmtService {
  /**
   * HAN-FUN bind management add.
   */
  HANFUNAPI_BIND_MANAGEMENT_ADD,
  /**
   * HAN-FUN bind management remove.
   */
  HANFUNAPI_BIND_MANAGEMENT_REMOVE,
  /**
   * HAN-FUN bind management get entries.
   */
  HANFUNAPI_BIND_MANAGEMENT_ENTRIES,

} openD_hanfunApiBindMgmtService_t;

/**
 * openD HanfunApi bind management request structure.
 */
typedef struct openD_hanfunApiBindMgmtReq {
  /**
   * HanfunApi bind management service.
   */
  openD_hanfunApiBindMgmtService_t service;

  /**
   * openD HanfunApi bind management parameters.
   */
  // union {
  // TBD;
  // } param;
} openD_hanfunApiBindMgmtReq_t;

/**
 * openD HanfunApi bind management confirm structure.
 */
typedef struct openD_hanfunApiBindMgmtConfirm {
  /**
   * HanfunApi bind management service.
   */
  openD_hanfunApiBindMgmtService_t service;
} openD_hanfunApiBindMgmtConfirm_t;

/**
 * openD HanfunApi bind management indication structure.
 */
typedef struct openD_hanfunApiBindMgmtIndication {
  /**
   * HanfunApi bind management service.
   */
  openD_hanfunApiBindMgmtService_t service;
} openD_hanfunApiBindMgmtIndication_t;


/**
 * openD HanfunApi profiles.
 */
typedef enum openD_hanfunApiProfile {
  /**
   * HAN-FUN Profile SIMPLE_ONOFF_SWITCHABLE.
   */
  HANFUNAPI_SIMPLE_ONOFF_SWITCHABLE,
  /**
   * HAN-FUN Profile SIMPLE_ONOFF_SWITCH.
   */
  HANFUNAPI_SIMPLE_ONOFF_SWITCH,
  /**
   * HAN-FUN Profile SIMPLE_LEVEL_CONTROLLABLE.
   */
  HANFUNAPI_SIMPLE_LEVEL_CONTROLLABLE,
  /**
   * HAN-FUN Profile SIMPLE_LEVEL_CONTROL.
   */
  HANFUNAPI_SIMPLE_LEVEL_CONTROL,
  /**
   * HAN-FUN Profile SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE.
   */
  HANFUNAPI_SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE,
  /**
   * HAN-FUN Profile SIMPLE_LEVEL_CONTROL_SWITCH.
   */
  HANFUNAPI_SIMPLE_LEVEL_CONTROL_SWITCH,
  /**
   * HAN-FUN Profile AC_OUTLET.
   */
  HANFUNAPI_AC_OUTLET,
  /**
   * HAN-FUN Profile AC_OUTLET_WITH_POWER_METERING.
   */
  HANFUNAPI_AC_OUTLET_WITH_POWER_METERING,
  /**
   * HAN-FUN Profile SIMPLE_LIGHT.
   */
  HANFUNAPI_SIMPLE_LIGHT,
  /**
   * HAN-FUN Profile DIMMABLE_LIGHT.
   */
  HANFUNAPI_DIMMABLE_LIGHT,

  /** Other HAN-FUN Profiles ... */

} openD_hanfunApiProfile_t;

/**
 * openD HanfunApi profile request structure.
 */
typedef struct openD_hanfunApiProfileReq {
  /**
   * HanfunApi profile.
   */
  openD_hanfunApiProfile_t profile;

  /**
   * openD HanfunApi profile.
   */
  union {
    openD_hanfunApi_pSimpleOnOffSwitchable_t simpleOnOffSwitchable;
    openD_hanfunApi_pSimpleLevelControllable_t simpleLevelControllable;
  } p;
} openD_hanfunApiProfileReq_t;

/**
 * openD HanfunApi profile confirm structure.
 */
typedef struct openD_hanfunApiProfileConfirm {
  /**
   * HanfunApi profile.
   */
  openD_hanfunApiProfile_t profile;
} openD_hanfunApiProfileConfirm_t;

/**
 * openD HanfunApi profile indication structure.
 */
typedef struct openD_hanfunApiProfileIndication {
  /**
   * HanfunApi profile.
   */
  openD_hanfunApiProfile_t profile;
} openD_hanfunApiProfileIndication_t;


/**
 * openD HanfunApi primitives structure.
 */
typedef struct openD_hanfunApiPrimitives {
  /**
   * @brief   HanfunApi device management confirm primitive.
   *
   * @param   hDevMgmtConfirm Pointer of the HanfunApi confirm structure (@ref openD_hanfunApiDevMgmtConfirm_t).
   */
  void ( *openD_hanfunApiMgmtConfirm )( openD_hanfunApiDevMgmtConfirm_t *hDevMgmtConfirm );
  /**
   * @brief   HanfunApi device management indication primitive.
   *
   * @param   hDevMgmtIndication Pointer of the HanfunApi indication structure (@ref openD_hanfunApiDevMgmtIndication_t).
   */
  void ( *openD_hanfunApiMgmtIndication )( openD_hanfunApiDevMgmtIndication_t *hDevMgmtIndication );

  /**
   * @brief   HanfunApi bind confirm primitive.
   *
   * @param   hBindMgmtConfirm Pointer of the HanfunApi confirm structure (@ref openD_hanfunApiBindMgmtConfirm_t).
   */
  void ( *openD_hanfunApiBindConfirm )( openD_hanfunApiBindMgmtConfirm_t *hBindMgmtConfirm );
  /**
   * @brief   HanfunApi bind indication primitive.
   *
   * @param   hBindMgmtIndication Pointer of the HanfunApi indication structure (@ref openD_hanfunApiBindMgmtIndication_t).
   */
  void ( *openD_hanfunApiBindIndication )( openD_hanfunApiBindMgmtIndication_t *hBindMgmtIndication );

  /**
   * @brief   HanfunApi profile confirm primitive.
   *
   * @param   hConfirm Pointer of the HanfunApi confirm structure (@ref openD_hanfunApiProfileConfirm_t).
   */
  void ( *openD_hanfunApiProfileConfirm )( openD_hanfunApiProfileConfirm_t *hProfileConfirm );
  /**
   * @brief   HanfunApi profile indication primitive.
   *
   * @param   hIndication Pointer of the HanfunApi indication structure (@ref openD_hanfunApiProfileIndication_t).
   */
  void ( *openD_hanfunApiProfileIndication )( openD_hanfunApiProfileIndication_t *hProfileIndication );
} openD_hanfunApiPrimitives_t;

/**
 * @brief   openD HAN-FUN API initialization.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   hPrimitives Pointer of the HAN-FUN API primitives structure (@ref openD_hanfunApiPrimitives_t).
 * @param   operationMode Operation mode of HAN-FUN (@ref openD_hanfunApiOperationMode_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_init( openD_hanfunApiPrimitives_t *hPrimitives, openD_hanfunApiOperationMode_t operationMode );

/**
 * @brief   openD HAN-FUN API device management request.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   hMgmtRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApiDevMgmtReq_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_devMgmtRequest( openD_hanfunApiDevMgmtReq_t *hMgmtRequest );

/**
 * @brief   openD HAN-FUN API bind management request.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   hBindRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApiBindMgmtReq_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_bindMgmtRequest( openD_hanfunApiBindMgmtReq_t *hBindRequest );

/**
 * @brief   openD HAN-FUN API profile request.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   hProfileRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApiProfileReq_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_profileRequest( openD_hanfunApiProfileReq_t *hProfileRequest );


/*! @} defgroup OPEND_HANFUN_API */

#endif /* __OPEND_HANFUN_API_H__ */
#ifdef __cplusplus
}
#endif
