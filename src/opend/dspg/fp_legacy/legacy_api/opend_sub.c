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
#include "cmbs_api.h"
#include "appcmbs.h"
#include "apphan.h"
#include "appmsgparser.h"
#include "appsrv.h"

#include <stdlib.h>

openD_subApiPrimitives_t _sPrimitives;

extern ST_CMBS_APPL g_cmbsappl;
static void opend_deregistration_finished_cllb();

void registerSuccessClb(uint16_t address, uint8_t handsetId);

openD_status_t openD_subApi_init( openD_subApiPrimitives_t *sPrimitives )
{
    if(!sPrimitives)
    {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    _sPrimitives.openD_subApiCfm = sPrimitives->openD_subApiCfm;
    _sPrimitives.openD_subApiInd = sPrimitives->openD_subApiInd;

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

openD_status_t openD_subApi_request( openD_subApiReq_t *sRequest )
{
    openD_status_t ret = OPEND_STATUS_FAIL;
    E_CMBS_RC cmbs_ret;

    if(!sRequest)
    {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    switch( sRequest->service ) {

        case OPEND_SUBAPI_SUBSCRIBE_ENABLE:
            /* Open registration. */
            cmbs_ret = cmbs_dsr_cord_OpenRegistrationExt(g_cmbsappl.pv_CMBSRef, 120, CMBS_HS_REG_ENABLE_ALL);
            break;

        case OPEND_SUBAPI_SUBSCRIPTION_DELETE:
            /* Delete all registered handsets. */
            cmbs_ret = cmbs_dsr_hs_Delete(g_cmbsappl.pv_CMBSRef, 0xFFFF);
            break;

        case OPEND_SUBAPI_SET_AC:
            /* Set authentication PIN code. */
            cmbs_ret = cmbs_dsr_param_Set(g_cmbsappl.pv_CMBSRef, CMBS_PARAM_TYPE_EEPROM, CMBS_PARAM_AUTH_PIN, sRequest->param.setAc.ac, CMBS_PARAM_PIN_CODE_LENGTH);
            break;

        default:
            ret = OPEND_STATUS_SERVICE_UNKNOWN;
            break;
    }

    if( OPEND_STATUS_SERVICE_UNKNOWN != ret ) {
        switch(cmbs_ret)
        {
            case CMBS_RC_OK:
                ret = OPEND_STATUS_OK;
                break;
            case CMBS_RC_ERROR_PARAMETER:
                ret = OPEND_STATUS_ARGUMENT_INVALID;
                break;
            case CMBS_RC_ERROR_MEDIA_BUSY:
                ret = OPEND_STATUS_BUSY;
            default:
                ret = OPEND_STATUS_FAIL;
                break;
        }
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
