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
 * @file       opend_mgmt_types.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD mgmt types.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_MGMT_API openD Management API
 *             This file defines the management types of openD connect.
 * \{
 */

#ifndef __OPEND_MGMT_TYPES_H__
#define __OPEND_MGMT_TYPES_H__

#include "opend_dataTypes.h"

/**
 * openD MgmtApi services.
 */
typedef enum openD_mgmtApi_service {
  /**
   * Initialization.
   */
  OPEND_MGMTAPI_INIT,
  /**
   * Timeout.
   */
  OPEND_MGMTAPI_TIMEOUT,
  /**
   * DectMode.
   */
  OPEND_MGMTAPI_DECTMODE,
  /**
   * Power down control.
   */
  OPEND_MGMTAPI_POWER_DOWN_CTRL,
  /**
   * Wake up.
   */
  OPEND_MGMTAPI_WAKE_UP,
  /**
   * Keep alive indication.
   */
  OPEND_MGMTAPI_KEEP_ALIVE,
  /**
   * Force NVM default.
   */
  OPEND_MGMTAPI_FORCE_NVM_DEFAULT,
} openD_mgmtApi_service_t;

/**
 * openD MgmtApi DectModes.
 */
typedef enum openD_mgmtApi_dectMode {
  /**
   * DectMode fix part.
   */
  OPEND_MGMTAPI_DECTMODE_FP,
  /**
   * DectMode portable part.
   */
  OPEND_MGMTAPI_DECTMODE_PP,
  /**
   * DectMode HAN-FUN.
   */
  OPEND_MGMTAPI_DECTMODE_HF,
  /**
   * DectMode 6LoWPAN.
   */
  OPEND_MGMTAPI_DECTMODE_SIXLOWPAN,
} openD_mgmtApi_dectMode_t;

/**
 * openD MgmtApi indication keepAlive structure.
 */
typedef struct mgmtApiInd_keepAlive {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} mgmtApiInd_keepAlive_t;

/**
 * openD MgmtApi request structure.
 */
typedef struct openD_mgmtApiReq {
  /**
   * MgmtApi request service.
   */
  openD_mgmtApi_service_t service;
  /**
   * openD MgmtApi request parameters.
   */
  union {
    /**
     * MgmtApi parameters for a dectMode request.
     */
    openD_mgmtApi_dectMode_t dectMode;
  } param;
} openD_mgmtApiReq_t;

/**
 * openD MgmtApi confirm structure.
 */
typedef struct openD_mgmtApiCfm {
  /**
   * MgmtApi confirm service.
   */
  openD_mgmtApi_service_t service;
  /**
   * MgmtApi service status.
   */
  openD_status_t status;
} openD_mgmtApiCfm_t;

/**
 * openD MgmtApi indication structure.
 */
typedef struct openD_mgmtApiInd {
  /**
   * MgmtApi indication service.
   */
  openD_mgmtApi_service_t service;

  /**
   * openD MgmtApi indication parameters.
   */
  union {
    /**
     * MgmtApi parameter for a keepAlive indication.
     */
    mgmtApiInd_keepAlive_t keepAlive;
  } param;
} openD_mgmtApiInd_t;

/*! @} defgroup OPEND_MGMT_TYPES */

#endif /* __OPEND_MGMT_TYPES_H__ */
#ifdef __cplusplus
}
#endif
