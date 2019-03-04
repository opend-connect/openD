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
 * @file       opend_sub.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */
#include "string.h"

#include "opend_dataTypes.h"
#include "opend.h"
#include "opend_api.h"
#include "opend_sub.h"
#include "opend_sub_api.h"
#include "apphan.h"
#include "appmsgparser.h"
#include "appsrv.h"

#include <stdlib.h>

openD_subApiPrimitives_t _sPrimitives;

static void opend_deregistration_finished_cllb();

static void opend_get_registration_state_cllb(void *param);

void registerSuccessClb(uint16_t address, uint8_t handsetId);

openD_status_t openD_subApi_init( openD_subApiPrimitives_t *sPrimitives )
{
    if(!sPrimitives)
    {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    _sPrimitives.openD_subApiCfm = sPrimitives->openD_subApiCfm;
    _sPrimitives.openD_subApiInd = sPrimitives->openD_subApiInd;

    initMsgParserSub(registerSuccessClb);
    initMsgParserDeSub(opend_deregistration_finished_cllb);

    return OPEND_STATUS_OK;
}

void registerSuccessClb(uint16_t address, uint8_t handsetId)
{
  openD_subApiCfm_t openD_subApiCfm;
  openD_subApiCfm.service = OPEND_SUBAPI_SUBSCRIBE;
  openD_subApiCfm.status = OPEND_STATUS_OK;
  openD_subApiCfm.param.handsetId.id = handsetId;
  _sPrimitives.openD_subApiCfm(&openD_subApiCfm);
}

static void opend_deregistration_finished_cllb(void *param)
{
  openD_subApiCfm_t openD_subApiCfm;
  openD_subApiCfm.service = OPEND_SUBAPI_SUBSCRIPTION_DELETE;
  openD_subApiCfm.status = OPEND_STATUS_OK;
  openD_subApiCfm.param.registrationState.isRegistered = false;
  _sPrimitives.openD_subApiCfm(&openD_subApiCfm);
}

static void opend_get_registration_state_cllb(void *param)
{
  uint8_t *success = (uint8_t*) (param+8);

  openD_subApiCfm_t openD_subApiCfm;
  openD_subApiCfm.service = OPEND_SUBAPI_GET_REGISTRATION_STATE;
  openD_subApiCfm.status = OPEND_STATUS_OK;

  if(memcmp(success, "1", 1) == 0)
  {
    openD_subApiCfm.param.registrationState.isRegistered = true;
  }
  else
  {
    openD_subApiCfm.param.registrationState.isRegistered = false;
  }

  _sPrimitives.openD_subApiCfm(&openD_subApiCfm);
}

openD_status_t openD_subApi_request( openD_subApiReq_t *sRequest )
{
    openD_status_t ret;

    if(!sRequest)
    {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    switch( sRequest->service ) {

        case OPEND_SUBAPI_SUBSCRIBE_ENABLE:

            app_SrvSubscriptionOpenExt( 120, CMBS_HS_REG_ENABLE_ALL );

            ret = OPEND_STATUS_OK;
            break;

        case OPEND_SUBAPI_SUBSCRIPTION_DELETE:

            app_DsrHanDeleteDevice(1, false);

            ret = OPEND_STATUS_OK;
            break;

        case OPEND_SUBAPI_GET_REGISTRATION_STATE:

            ret = OPEND_STATUS_OK;

            break;

        default:
            ret = OPEND_STATUS_SERVICE_UNKNOWN;
    }

    return ret;
}

void openD_sub_confirmation( openD_subApiCfm_t *sConfirm ) {

    if(!sConfirm){
        return;
    }


    if( _sPrimitives.openD_subApiCfm ) {
        _sPrimitives.openD_subApiCfm( sConfirm );
    }
    return;
}

#ifdef __cplusplus
}
#endif
