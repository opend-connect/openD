/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      openD HAN-FUN.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_HANFUN_API openD HAN-FUN
 *             This module specifies the Interface to the customer stack side.
 * @{
 *
 * @defgroup   OPEND_HANFUN_INTERFACE Interfaces
 * @defgroup   OPEND_HANFUN_PROFILE Profiles
 */

#ifndef __OPEND_HANFUN_H__
#define __OPEND_HANFUN_H__

#include "opend_dataTypes.h"
#include "opend_hanfun_types.h"

/**
 * @brief   openD HANFUN API device management confirmation.
 *
 * @details Device management confirmation to call the HANFUN API primitive callback.
 *
 * @param   hDevMgmtConfirm Pointer of the HANFUN API device management
 *          confirmation primitive structure.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfun_devMgmtCfm( openD_hanfunApi_devMgmtCfm_t *hDevMgmtConfirm );

/**
 * @brief   openD HANFUN API device management indication.
 *
 * @details Device management indication to call the HANFUN API primitive callback.
 *
 * @param   hMgmtInd Pointer of the HANFUN API device management
 *          indication primitive structure.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfun_devMgmtInd( openD_hanfunApi_devMgmtInd_t *hMgmtInd );

/**
 * @brief   openD HANFUN API profile confirmation.
 *
 * @details Profile confirmation to call the HANFUN API primitive callback.
 *
 * @param   hProfileConfirm Pointer of the HAN-FUN API profile
 *          confirmation primitive structure.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfun_profileCfm( openD_hanfunApi_profileCfm_t *hProfileConfirm );

/**
 * @brief   openD HANFUN API profile indication.
 *
 * @details Profile indication to call the HANFUN API primitive callback.
 *
 * @param   hProfileInd Pointer of the HAN-FUN API profile
 *          indication primitive structure.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfun_profileInd( openD_hanfunApi_profileInd_t *hProfileInd );

/**
 * @brief   openD HANFUN API bind management confirmation.
 *
 * @details Bind management confirmation to call the HANFUN API primitive callback.
 *
 * @param   hBindMgmtConfirm Pointer of the HANFUN API bind management
 *          confirmation primitive structure.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfun_bindMgmtCfm( openD_hanfunApi_bindMgmtCfm_t *hBindMgmtConfirm );


/*! @} defgroup OPEND_HANFUN */

#endif /* __OPEND_HANFUN_H__ */
