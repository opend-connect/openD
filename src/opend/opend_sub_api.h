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
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_SUB_API openD Subscription API
 *             This module specifies the subscription API of openD connect.
 * \{
 */

#ifndef __OPEND_SUB_API_H__
#define __OPEND_SUB_API_H__

#include <stdbool.h>
#include "opend_dataTypes.h"
#include "opend_sub_types.h"

/**
 * openD SubApi primitives structure.
 */
typedef struct openD_subApiPrimitives {
  /**
   * @brief   SubApi confirm primitive.
   *
   * @param   sConfirm Pointer of the SubApi confirm structure (@ref openD_subApiCfm_t).
   */
  void ( *openD_subApiCfm )( openD_subApiCfm_t *sConfirm );
  /**
   * @brief   SubApi indication primitive.
   *
   * @param   sIndication Pointer of the SubApi indication structure (@ref openD_subApiInd_t).
   */
  void ( *openD_subApiInd )( openD_subApiInd_t *sIndication );
} openD_subApiPrimitives_t;

/**
 * @brief   openD subscription API initialization.
 *
 * @param   sPrimitives Pointer of the subscription API primitives structure (@ref openD_subApiPrimitives_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_subApi_init( openD_subApiPrimitives_t *sPrimitives );

/**
 * @brief   openD subscription API request.
 *
 * @param   sRequest Pointer of the subscription API request structure (@ref openD_subApiReq_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_subApi_request( openD_subApiReq_t *sRequest );


/*! @} defgroup OPEND_SUB_API */

#endif /* __OPEND_SUB_API_H__ */
#ifdef __cplusplus
}
#endif
