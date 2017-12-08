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
 * @file       opend_call_api.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD call API.
 *
 * @defgroup   OPEND_CALL_API openD Call API
 *             This module specifies the call API of openD connect.
 * \{
 */

#ifndef __OPEND_CALL_API_H__
#define __OPEND_CALL_API_H__

#include "opend_dataTypes.h"

/**
 * openD CallApi services.
 */
typedef enum openD_callApi {
  /**
   * Setup.
   */
  CALLAPI_SETUP,
  /**
   * Release.
   */
  CALLAPI_RELEASE,
  /**
   * ConnectionStatus.
   */
  CALLAPI_CONNECTION_STATUS_RINGING,

  CALLAPI_CONNECTION_STATUS_CONNECT,

  CALLAPI_CONNECTION_STATUS_REJECT,
} openD_callApiServices_t;

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
   * CallApi request type.
   */
  openD_callApiServices_t type;

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
typedef struct openD_callApiConfirm {
  /**
   * CallApi service type.
   */
  openD_callApiServices_t type;
  /**
   * CallApi service status.
   */
  openD_status_t status;
} openD_callApiConfirm_t;

/**
 * openD CallApi indication structure.
 */
typedef struct openD_callApiIndication {
  /**
   * CallApi service type.
   */
  openD_callApiServices_t type;

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
} openD_callApiIndication_t;

/**
 * openD CallApi primitives structure.
 */
typedef struct openD_callApiPrimitives {
  /**
   * @brief   CallApi confirm primitive.
   *
   * @param   cConfirm Pointer of the CallApi confirm structure (@ref openD_callApiConfirm_t).
   */
  void ( *openD_callApiConfirm )( openD_callApiConfirm_t *cConfirm );
  /**
   * @brief   CallApi indication primitive.
   *
   * @param   cIndication Pointer of the CallApi indication structure (@ref openD_callApiIndication_t).
   */
  void ( *openD_callApiIndication )( openD_callApiIndication_t *cIndication );
} openD_callApiPrimitives_t;

/**
 * @brief   openD call API initialization.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   cPrimitives Pointer of the call API primitives structure (@ref openD_callApiPrimitives_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_callApi_init( openD_callApiPrimitives_t *cPrimitives );

/**
 * @brief   openD call API request.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   cRequest Pointer of the call API request structure (@ref openD_callApiReq_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_callApi_request( openD_callApiReq_t *cRequest );


/*! @} defgroup OPEND_CALL_API */

#endif /* __OPEND_CALL_API_H__ */
#ifdef __cplusplus
}
#endif
