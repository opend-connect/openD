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
 * @author     Heiko Berger
 * @brief      openD HAN-FUN API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
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
#include "opend_hanfun_types.h"

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
   * @param   hProfileConfirm Pointer of the HanfunApi confirm structure (@ref openD_hanfunApi_profileCfm_t).
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
 * @brief   openD HAN-FUN API initialization of primitives.
 *
 * @details Initialization of the hanfun api callbacks.
 *
 * @param   hPrimitives Pointer of the HAN-FUN API primitives structure (@ref openD_hanfunApiPrimitives_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_init( openD_hanfunApiPrimitives_t *hPrimitives );

/*! @} defgroup OPEND_HANFUN_API */

#endif /* __OPEND_HANFUN_API_H__ */
