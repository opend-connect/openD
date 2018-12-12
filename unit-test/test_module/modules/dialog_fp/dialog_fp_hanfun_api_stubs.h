/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       dialog_fp_hanfun_api_stubs.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     Heiko Berger (STACKFORCE)
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

#include <stdint.h>

#include "opend_hanfun_types.h"


/**
 * @brief   Send function.
 *
 * @details Send function stub.
 *
 * @param   buffer Pointer to the buffer to send.
 * @param   len    Length of the buffer.
 */
void sendFunction(uint8_t *buffer, uint16_t len )
{
  /* Function only need as function pointer param, so just return. */
  return;
}

/**
 * @brief   Device management confirm callback.
 *
 * @details Executes the service specific device management confirmation.
 *
 * @param   hDevMgmtConfirm Pointer to the device management confirm structure.
 */
void devMgmtConfirmCallback(openD_hanfunApi_devMgmtCfm_t *hDevMgmtConfirm)
{
  /* Function only need as function pointer param, so just return. */
  return;
}

/**
 * @brief   Device management indication callback.
 *
 * @details Executes the service specific device management indication.
 *
 * @param   hDevMgmtInd Pointer to the device management confirm structure.
 */
void devMgmtIndCallback(openD_hanfunApi_devMgmtInd_t *hDevMgmtInd)
{
  /* Function only need as function pointer param, so just return. */
  return;
}

/**
 * @brief   Profile indication callback.
 *
 * @details Executes the service specific profile indication.
 *
 * @param   hProfileInd Pointer to the profile indication structure.
 */
void profileIndCallback(openD_hanfunApi_profileInd_t *hProfileInd)
{
  /* Function only need as function pointer param, so just return. */
  return;
}

/**
 * @brief   Profile confirm callback.
 *
 * @details Executes the service specific profile confirmation.
 *
 * @param   hProfileConfirm Pointer to the profile confirm structure.
 */
void profileConfirmCallback(openD_hanfunApi_profileCfm_t *hProfileConfirm)
{
  /* Function only need as function pointer param, so just return. */
  return;
}

/**
 * @brief   HanfunApi bind confirm primitive.
 *
 * @param   hBindMgmtConfirm Pointer of the HanfunApi confirm structure (@ref openD_hanfunApi_bindMgmtCfm_t).
 */
void bindMgmtConfirmCallback( openD_hanfunApi_bindMgmtCfm_t *hBindMgmtConfirm )
{
  return;
}
