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
 * @file       opend_mgmt_api.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD management API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_MGMT_API openD Management API
 *             This module specifies the management API of openD connect.
 * \{
 */

#ifndef __OPEND_MGMT_API_H__
#define __OPEND_MGMT_API_H__

#include "opend_dataTypes.h"
#include "opend_mgmt_types.h"

/**
 * openD MgmtApi primitives structure.
 */
typedef struct openD_mgmtApiPrimitives {
  /**
   * @brief   MgmtApi confirm primitive.
   *
   * @param   mConfirm Pointer of the management API confirm structure (@ref openD_mgmtApiCfm_t).
   */
  void ( *openD_mgmtApiCfm )( openD_mgmtApiCfm_t *mConfirm );
  /**
   * @brief   MgmtApi indication primitive.
   *
   * @param   mIndication Pointer of the management API indication structure (@ref openD_mgmtApiInd_t).
   */
  void ( *openD_mgmtApiInd )( openD_mgmtApiInd_t *mIndication );
} openD_mgmtApiPrimitives_t;

/**
 * @brief   openD management API initialization.
 *
 * @param   mPrimitives Pointer of the management API primitives structure (@ref openD_mgmtApiPrimitives_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_mgmtApi_init( openD_mgmtApiPrimitives_t *mPrimitives );

/**
 * @brief   openD management API request.
 *
 * @param   mRequest Pointer of the management API request structure (@ref openD_mgmtApiReq_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_mgmtApi_request( openD_mgmtApiReq_t *mRequest );


/*! @} defgroup OPEND_MGMT_API */

#endif /* __OPEND_MGMT_API_H__ */
#ifdef __cplusplus
}
#endif
