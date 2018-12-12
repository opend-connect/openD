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
 * @author     Patrick Weber
 * @brief      openD legacy call.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include "MmiCtrl.h"

#include "opend_dataTypes.h"

#include "opend_dataTypes.h"
#include "opend.h"
#include "opend_api.h"
#include "opend_call.h"
#include "opend_call_api.h"

#include "opend.h"
#include "opend_states.h"
#include "msManager.h"

openD_callApiPrimitives_t _cPrimitives;

openD_status_t openD_callApi_init( openD_callApiPrimitives_t *cPrimitives )
{
    if( !cPrimitives ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    _cPrimitives.openD_callApiCfm = cPrimitives->openD_callApiCfm;
    _cPrimitives.openD_callApiInd = cPrimitives->openD_callApiInd;

    return OPEND_STATUS_OK;
}

openD_status_t openD_callApi_request( openD_callApiReq_t *cRequest )
{
    openD_status_t ret;
    messageManager_t message;
    openD_Api_t openD_Api;

    if( !cRequest ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    /* Check openD state. */
    if( OPEND_STATUS_IDLE != openD_api_getStatus() ) {
        return OPEND_STATUS_BUSY;
    }
    /* Set the openD state into busy. */
    openD_setStatusBusy();


    openD_Api.opendApis = OPEND_APIS_CALL;
    openD_Api.param = cRequest;
    message.primitive = MESSAGE_PRIMITIVE_USER;
    message.param = &openD_Api;
    if( msManager_handleService( &opendStateCtxt, &message ) ) {
        ret = OPEND_STATUS_OK;
    } else {
        ret = OPEND_STATUS_FAIL;
    }

    /* Release the openD state. */
    openD_setStatusIdle();
    return ret;
}

void openD_call_confirmation( openD_callApiCfm_t *cConfirm )
{
    if( _cPrimitives.openD_callApiCfm ) {
        _cPrimitives.openD_callApiCfm( cConfirm );
    }
    return;
}

void openD_call_indication( openD_callApiInd_t *cIndication )
{
    if( _cPrimitives.openD_callApiInd ) {
        _cPrimitives.openD_callApiInd( cIndication );
    }
    return;
}


#ifdef __cplusplus
}
#endif
