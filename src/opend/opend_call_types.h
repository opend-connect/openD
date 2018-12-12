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
 * @file       opend_call_types.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD call types.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_CALL_API openD Call API
 *             This file defines the call types of openD connect.
 * \{
 */

#ifndef __OPEND_CALL_TYPES_H__
#define __OPEND_CALL_TYPES_H__

#include "opend_dataTypes.h"

/**
 * openD CallApi services.
 */
typedef enum openD_callApi_service {
  /**
   * Setup.
   */
  OPEND_CALLAPI_SETUP,
  /**
   * Release.
   */
  OPEND_CALLAPI_RELEASE,
  /**
   * Connection status ringing.
   */
  OPEND_CALLAPI_CONNECTION_STATUS_RINGING,
  /**
   * Connection status connect.
   */
  OPEND_CALLAPI_CONNECTION_STATUS_CONNECT,
  /**
   * Connection status reject.
   */
  OPEND_CALLAPI_CONNECTION_STATUS_REJECT,

} openD_callApi_service_t;

/**
 * openD SubApi request setup structure.
 */
typedef struct callApiReq_setup {
  /**
    * Subscribe enable.
    */
  pmid_t pmid;
} callApiReq_setup_t;

/**
 * openD SubApi request release structure.
 */
typedef struct callApiReq_release {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} callApiReq_release_t;

/**
 * openD SubApi indication setup structure.
 */
typedef struct callApiInd_setup {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} callApiInd_setup_t;

/**
 * openD SubApi indication release structure.
 */
typedef struct callApiInd_release {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} callApiInd_release_t;

/**
 * openD SubApi indication connectionStatus_ringing structure.
 */
typedef struct callApiInd_connectionStatus_ringing {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} callApiInd_connectionStatus_ringing_t;

/**
 * openD SubApi indication connectionStatus_connect structure.
 */
typedef struct callApiInd_connectionStatus_connect {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} callApiInd_connectionStatus_connect_t;

/**
 * openD SubApi indication connectionStatus_reject structure.
 */
typedef struct callApiInd_connectionStatus_reject {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} callApiInd_connectionStatus_reject_t;

/**
 * openD CallApi request structure.
 */
typedef struct openD_callApiReq {
  /**
   * CallApi request service.
   */
  openD_callApi_service_t service;

  /**
   * openD CallApi request parameters.
   */
  union {
    /**
     * CallApi parameters for a setup request.
     */
    callApiReq_setup_t setup;
    /**
     * CallApi parameters for a release request.
     */
    callApiReq_release_t release;
  } param;
} openD_callApiReq_t;

/**
 * openD CallApi confirm structure.
 */
typedef struct openD_callApiCfm {
  /**
   * CallApi confirm service.
   */
  openD_callApi_service_t service;
  /**
   * CallApi service status.
   */
  openD_status_t status;
  union {
    /**
     * CallApi parameters for a setup request.
     */
    callApiReq_setup_t setup;
  } param;
} openD_callApiCfm_t;

/**
 * openD CallApi indication structure.
 */
typedef struct openD_callApiInd {
  /**
   * CallApi indication service.
   */
  openD_callApi_service_t service;

  /**
   * openD CallApi indication parameters.
   */
  union {
    /**
     * CallApi parameter for a setup indication.
     */
    callApiInd_setup_t setup;
    /**
     * CallApi parameter for a release indication.
     */
    callApiInd_release_t release;
    /**
     * CallApi parameter for a connectionStatus_ringing indication.
     */
    callApiInd_connectionStatus_ringing_t connectionStatus_ringing;
    /**
     * CallApi parameter for a connectionStatus_connect indication.
     */
    callApiInd_connectionStatus_connect_t connectionStatus_connect;
    /**
     * CallApi parameter for a connectionStatus_reject indication.
     */
    callApiInd_connectionStatus_reject_t connectionStatus_reject;
  } param;
} openD_callApiInd_t;

/*! @} defgroup OPEND_CALL_TYPES */

#endif /* __OPEND_CALL_TYPES_H__ */
#ifdef __cplusplus
}
#endif
