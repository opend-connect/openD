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
 * @file       opend_call.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger, Patrick Weber
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
#include "opend.h"
#include "opend_api.h"
#include "opend_call.h"
#include "opend_call_api.h"
#include "transport.h"

static void opend_call_setup_cllb();

static void opend_call_terminated_cllb();

openD_callApiPrimitives_t _cPrimitives;

openD_status_t openD_callApi_init( openD_callApiPrimitives_t *cPrimitives )
{
  if(!cPrimitives)
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  _cPrimitives.openD_callApiCfm = cPrimitives->openD_callApiCfm;
  _cPrimitives.openD_callApiInd = cPrimitives->openD_callApiInd;
  opend_iwu_call_init(&opend_call_setup_cllb, &opend_call_terminated_cllb);

  return OPEND_STATUS_OK;
}

static void opend_call_setup_cllb()
{
  openD_callApiCfm_t openD_callApiCfm;
  openD_callApiCfm.service = OPEND_CALLAPI_SETUP;
  openD_callApiCfm.status = OPEND_STATUS_OK;

  _cPrimitives.openD_callApiCfm(&openD_callApiCfm);
}

static void opend_call_terminated_cllb()
{
  openD_callApiCfm_t openD_callApiCfm;
  openD_callApiCfm.service = OPEND_CALLAPI_RELEASE;
  openD_callApiCfm.status = OPEND_STATUS_OK;

  _cPrimitives.openD_callApiCfm(&openD_callApiCfm);
}

openD_status_t openD_callApi_request( openD_callApiReq_t *cRequest )
{
    openD_status_t ret;

    if(!cRequest)
    {
      return OPEND_STATUS_ARGUMENT_INVALID;
    }

    switch( cRequest->service ) {

        case OPEND_CALLAPI_SETUP:

            opend_iwu_call_request(cRequest->param.setup.pmid[0]);

            ret = OPEND_STATUS_OK;
            break;

        case OPEND_CALLAPI_RELEASE:

            opend_iwu_release_call();

            ret = OPEND_STATUS_OK;
            break;

        default:
            ret = OPEND_STATUS_SERVICE_UNKNOWN;
    }

    return ret;
}

void openD_call_confirmation( openD_callApiCfm_t *cConfirm ) {

    if( _cPrimitives.openD_callApiCfm ) {
        _cPrimitives.openD_callApiCfm( cConfirm );
    }
    return;
}

#ifdef __cplusplus
}
#endif
