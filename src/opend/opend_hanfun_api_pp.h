/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_api_pp.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      openD HAN-FUN API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_HANFUN_API_PP openD HAN-FUN API portable part
 *             This module specifies the HAN-FUN API of openD connect.
 * @{
 *
 * @defgroup   OPEND_HANFUN_INTERFACE Interfaces
 * @defgroup   OPEND_HANFUN_PROFILE Profiles
 */

#ifndef __OPEND_HANFUN_API_PP_H__
#define __OPEND_HANFUN_API_PP_H__

#include "opend_hanfun_api.h"

/**
 * @brief   openD HAN-FUN API initialization.
 *
 * @details Initialization of the hanfun api with the iwu.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_pp_init();

/**
 * @brief   openD HAN-FUN API device management request.
 *
 * @details Device management requests of the different profiles.
 *
 * @param   hMgmtRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApi_devMgmtReq_t).
 * @param   address Address to send the request.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_pp_devMgmtRequest( openD_hanfunApi_devMgmtReq_t *hMgmtRequest, uint16_t address = 0 );

/**
 * @brief   openD HAN-FUN API profile request.
 *
 * @details Profile request with different services.
 *
 * @param   hProfileRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApi_profileReq_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_pp_profileRequest( openD_hanfunApi_profileReq_t *hProfileRequest );

/**
 * @brief   openD HANFUN create profile.
 *
 * @details Create a profile for the node device.
 *
 * @param   opend_profile Enum of the HANFUN profile.
 * @param   id ID of the HANFUN profile.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t opend_hanfun_createProfile(openD_hanfunApi_profile_t opend_profile, uint8_t id);

/*! @} defgroup OPEND_HANFUN_API_PP */

#endif /* __OPEND_HANFUN_API_PP_H__ */
