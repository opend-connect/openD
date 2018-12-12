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
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_CALL_API openD Call API
 *             This module specifies the call API of openD connect.
 * \{
 */

#ifndef __OPEND_CALL_API_H__
#define __OPEND_CALL_API_H__

#include "opend_dataTypes.h"
#include "opend_call_types.h"

/**
 * openD CallApi primitives structure.
 */
typedef struct openD_callApiPrimitives {
  /**
   * @brief   CallApi confirm primitive.
   *
   * @param   cConfirm Pointer of the CallApi confirm structure (@ref openD_callApiCfm_t).
   */
  void ( *openD_callApiCfm )( openD_callApiCfm_t *cConfirm );
  /**
   * @brief   CallApi indication primitive.
   *
   * @param   cIndication Pointer of the CallApi indication structure (@ref openD_callApiInd_t).
   */
  void ( *openD_callApiInd )( openD_callApiInd_t *cIndication );
} openD_callApiPrimitives_t;

/**
 * @brief   openD call API initialization.
 *
 * @param   cPrimitives Pointer of the call API primitives structure (@ref openD_callApiPrimitives_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_callApi_init( openD_callApiPrimitives_t *cPrimitives );

/**
 * @brief   openD call API request.
 *
 * @param   cRequest Pointer of the call API request structure (@ref openD_callApiReq_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_callApi_request( openD_callApiReq_t *cRequest );


/*! @} defgroup OPEND_CALL_API */

#endif /* __OPEND_CALL_API_H__ */
#ifdef __cplusplus
}
#endif
