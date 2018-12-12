/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include "opend_dataTypes.h"
#include "opend_hanfun_api.h"
#include "opend_hanfunlib_api_pp.h"

/*!
 * Static and global openD HANFUN API primitives object.
 */
static openD_hanfunApiPrimitives_t openD_hanfunApiPrimitives;

openD_status_t openD_hanfunApi_init( openD_hanfunApiPrimitives_t *hPrimitives )
{
  if( !hPrimitives )
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  openD_hanfunApiPrimitives.openD_hanfunApi_mgmtCfm = hPrimitives->openD_hanfunApi_mgmtCfm;
  openD_hanfunApiPrimitives.openD_hanfunApi_mgmtInd = hPrimitives->openD_hanfunApi_mgmtInd ;
  openD_hanfunApiPrimitives.openD_hanfunApi_bindCfm = hPrimitives->openD_hanfunApi_bindCfm;
  openD_hanfunApiPrimitives.openD_hanfunApiBindInd = hPrimitives->openD_hanfunApiBindInd;
  openD_hanfunApiPrimitives.openD_hanfunApiProfileCfm = hPrimitives->openD_hanfunApiProfileCfm;
  openD_hanfunApiPrimitives.openD_hanfunApiProfileInd = hPrimitives->openD_hanfunApiProfileInd;

  return OPEND_STATUS_OK;
}

openD_status_t openD_hanfun_profileCfm( openD_hanfunApi_profileCfm_t *hProfileConfirm )
{
  if(!openD_hanfunApiPrimitives.openD_hanfunApiProfileCfm)
  {
    return OPEND_STATUS_FAIL;
  }

  openD_hanfunApiPrimitives.openD_hanfunApiProfileCfm(hProfileConfirm);
  return OPEND_STATUS_OK;
}

openD_status_t openD_hanfun_profileInd( openD_hanfunApi_profileInd_t *hProfileInd )
{
  if(!openD_hanfunApiPrimitives.openD_hanfunApiProfileInd)
  {
    return OPEND_STATUS_FAIL;
  }

  openD_hanfunApiPrimitives.openD_hanfunApiProfileInd(hProfileInd);
  return OPEND_STATUS_OK;
}

openD_status_t openD_hanfun_devMgmtCfm( openD_hanfunApi_devMgmtCfm_t *hDevMgmtConfirm )
{
  if(!openD_hanfunApiPrimitives.openD_hanfunApi_mgmtCfm)
  {
    return OPEND_STATUS_FAIL;
  }

  openD_hanfunApiPrimitives.openD_hanfunApi_mgmtCfm(hDevMgmtConfirm);
  return OPEND_STATUS_OK;
}

openD_status_t openD_hanfun_devMgmtInd( openD_hanfunApi_devMgmtInd_t *hMgmtInd )
{
  if( !hMgmtInd )
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  if(hMgmtInd->service == OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE)
  {
    opend_hanfun_registerDevice();
  }

  return OPEND_STATUS_OK;
}
