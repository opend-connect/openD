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
 * @file       opend_api.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_API openD API
 *             This module specifies the unified API of openD connect.
 * \{
 */

#ifndef __OPEND_API_H__
#define __OPEND_API_H__

#include "opend_dataTypes.h"


/**
 * @brief   openD API initialization.
 *
 * @details Initialize the openD API.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_init( void *port );

/**
 * @brief   openD API get status.
 *
 * @details Get the status of the operation.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_api_getStatus( void );


/*! @} defgroup OPEND_API */

#endif /* __OPEND_API_H__ */
#ifdef __cplusplus
}
#endif
