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
 * @file       opend_sixlowpan_api.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD 6LoWPAN API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_SIXLOWPAN_API openD 6LoWPAN API
 *             This module specifies the 6LoWPAN API of openD connect.
 * \{
 */

#ifndef __OPEND_SIXLOWPAN_API_H__
#define __OPEND_SIXLOWPAN_API_H__

#include "opend_dataTypes.h"

/**
 * openD SixlowpanApi services.
 */
typedef enum openD_sixlowpanApi_service {

/** TBD */
  TBD,
} openD_sixlowpanApi_service_t;

/**
 * openD SixlowpanApi request structure.
 */
typedef struct openD_sixlowpanApiReq {
  /**
   * SixlowpanApi request service.
   */
  openD_sixlowpanApi_service_t service;
} openD_sixlowpanApiReq_t;

/**
 * openD SixlowpanApi confirm structure.
 */
typedef struct openD_sixlowpanApiCfm {
  /**
   * SixlowpanApi confirm service.
   */
  openD_sixlowpanApi_service_t service;
  /**
   * SixlowpanApi service status.
   */
  openD_status_t status;
} openD_sixlowpanApiCfm_t;

/**
 * openD SixlowpanApi indication structure.
 */
typedef struct openD_sixlowpanApiInd {
  /**
   * SixlowpanApi indication service.
   */
  openD_sixlowpanApi_service_t service;
} openD_sixlowpanApiInd_t;

/**
 * openD SixlowpanApi primitives structure.
 */
typedef struct openD_sixlowpanApiPrimitives {
  /**
   * @brief   SixlowpanApi confirm primitive.
   *
   * @param   sixConfirm Pointer of the SixlowpanApi confirm structure (@ref openD_sixlowpanApiCfm_t).
   */
  void ( *openD_sixlowpanApiCfm )( openD_sixlowpanApiCfm_t *sixConfirm );
  /**
   * @brief   SixlowpanApi indication primitive.
   *
   * @param   sixIndication Pointer of the SixlowpanApi indication structure (@ref openD_sixlowpanApiInd_t).
   */
  void ( *openD_sixlowpanApiInd )( openD_sixlowpanApiInd_t *sixIndication );
} openD_sixlowpanApiPrimitives_t;

/**
 * @brief   openD 6LoWPAN initialization.
 *
 * @param   sixPrimitives Pointer of the 6LoWPAN API primitives structure (@ref openD_sixlowpanApiPrimitives_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_sixlowpanApi_init( openD_sixlowpanApiPrimitives_t *sixPrimitives );

/**
 * @brief   openD 6LoWPAN API request.
 *
 * @param   sixRequest Pointer of the 6LoWPAN API request structure (@ref openD_sixlowpanApiReq_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_sixlowpanApi_request( openD_sixlowpanApiReq_t *sixRequest );


/*! @} defgroup OPEND_SIXLOWPAN_API */

#endif /* __OPEND_SIXLOWPAN_API_H__ */
#ifdef __cplusplus
}
#endif
