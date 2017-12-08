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
 * @file       opend_sub_api.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD subscription API.
 *
 * @defgroup   OPEND_SUB_API openD Subscription API
 *             This module specifies the subscription API of openD connect.
 * \{
 */

#ifndef __OPEND_SUB_API_H__
#define __OPEND_SUB_API_H__

#include <stdbool.h>
#include "opend_dataTypes.h"

/**
 * openD SubApi services.
 */
typedef enum openD_subApi {
  /**
   * Subscribe enable.
   */
  SUBAPI_SUBSCRIBE_ENABLE,
  /**
   * Subscribe.
   */
  SUBAPI_SUBSCRIBE,
  /**
   * Subscribe delete.
   */
  SUBAPI_SUBSCRIPTION_DELETE,
  /**
   * Set access code.
   */
  SUBAPI_SET_AC,
} openD_subApiServices_t;

/**
 * openD SubApi request subscribeEnable structure.
 */
typedef struct subApiReq_subscribeEnable {
  /**
    * Subscribe enable.
    */
  bool enable;
} subApiReq_subscribeEnable_t;

/**
 * openD SubApi request subscribe structure.
 */
typedef struct subApiReq_subscribe {
  /**
   * Radio Fixed Part Identity (RFPI).
   */
  rfpi_t rfpi;
  /**
   * Access code (AC).
   */
  ac_t ac;
} subApiReq_subscribe_t;

/**
 * openD SubApi request subscriptionDelete structure.
 */
typedef struct subApiReq_subscriptionDelete {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} subApiReq_subscriptionDelete_t;

/**
 * openD SubApi request setAc structure.
 */
typedef struct subApiReq_setAc {
  /**
   * Access code (AC).
   */
  ac_t ac;
} subApiReq_setAc_t;

/**
 * openD SubApi indication subscribe structure.
 */
typedef struct subApiInd_subscribe {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
  /**
   * International Portable User Identity (IPUI).
   */
  ipui_t ipui;
} subApiInd_subscribe_t;

/**
 * openD SubApi indication subscriptionDelete structure.
 */
typedef struct subApiInd_subscriptionDelete {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
} subApiInd_subscriptionDelete_t;

/**
 * openD SubApi request structure.
 */
typedef struct openD_subApiReq {
  /**
   * SubApi request type.
   */
  openD_subApiServices_t type;

  /**
   * openD SubApi request parameters.
   */
  union {
    /**
     * SubApi parameters for a subscribeEnable request.
     */
    subApiReq_subscribeEnable_t subscribeEnable;
    /**
     * SubApi parameters for a subscribe request.
     */
    subApiReq_subscribe_t subscribe;
    /**
     * SubApi parameters for a subscriptionDelete request.
     */
    subApiReq_subscriptionDelete_t subscriptionDelete;
    /**
     * SubApi parameters for a setAc request.
     */
    subApiReq_setAc_t setAc;
  } param;
} openD_subApiReq_t;

/**
 * openD SubApi confirm structure.
 */
typedef struct openD_subApiConfirm {
  /**
   * SubApi service type.
   */
  openD_subApiServices_t type;
  /**
   * SubApi service status.
   */
  openD_status_t status;
} openD_subApiConfirm_t;

/**
 * openD SubApi indication structure.
 */
typedef struct openD_subApiIndication {
  /**
   * SubApi service type.
   */
  openD_subApiServices_t type;

  /**
   * openD SubApi indication parameters.
   */
  union {
    /**
     * SubApi parameter for a subscribe indication.
     */
    subApiInd_subscribe_t subscribe;
    /**
     * SubApi parameter for a subscriptionDelete indication.
     */
    subApiInd_subscriptionDelete_t subscriptionDelete;
  } param;
} openD_subApiIndication_t;

/**
 * openD SubApi primitives structure.
 */
typedef struct openD_subApiPrimitives {
  /**
   * @brief   SubApi confirm primitive.
   *
   * @param   sConfirm Pointer of the SubApi confirm structure (@ref openD_subApiConfirm_t).
   */
  void ( *openD_subApiConfirm )( openD_subApiConfirm_t *sConfirm );
  /**
   * @brief   SubApi indication primitive.
   *
   * @param   sIndication Pointer of the SubApi indication structure (@ref openD_subApiIndication_t).
   */
  void ( *openD_subApiIndication )( openD_subApiIndication_t *sIndication );
} openD_subApiPrimitives_t;

/**
 * @brief   openD subscription API initialization.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   sPrimitives Pointer of the subscription API primitives structure (@ref openD_subApiPrimitives_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_subApi_init( openD_subApiPrimitives_t *sPrimitives );

/**
 * @brief   openD subscription API request.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @param   sRequest Pointer of the subscription API request structure (@ref openD_subApiReq_t).
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_subApi_request( openD_subApiReq_t *sRequest );


/*! @} defgroup OPEND_SUB_API */

#endif /* __OPEND_SUB_API_H__ */
#ifdef __cplusplus
}
#endif
