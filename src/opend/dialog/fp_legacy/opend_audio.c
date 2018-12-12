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
 * @file       opend_audio.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD legacy audio.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include "opend_dataTypes.h"
#include "opend_audio_api.h"

#include "opend.h"
#include "opend_states.h"
#include "msManager.h"


openD_audioApiPrimitives_t _aPrimitives;

openD_status_t openD_audioApi_init( openD_audioApiPrimitives_t *aPrimitives )
{
    if( !aPrimitives ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    _aPrimitives.openD_audioApiCfm = aPrimitives->openD_audioApiCfm;
    _aPrimitives.openD_audioApiInd = aPrimitives->openD_audioApiInd;

    return OPEND_STATUS_OK;
}

openD_status_t openD_audioApi_request( openD_audioApiReq_t *aRequest )
{
    openD_status_t ret;
    messageManager_t message;
    openD_Api_t openD_Api;

    if( !aRequest ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    /* Check openD state. */
    if( OPEND_STATUS_IDLE != openD_api_getStatus() ) {
        return OPEND_STATUS_BUSY;
    }
    /* Set the openD state into busy. */
    openD_setStatusBusy();


    openD_Api.opendApis = OPEND_APIS_AUDIO;
    openD_Api.param = aRequest;
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

void openD_audio_confirmation( openD_audioApiCfm_t *aConfirm )
{
    if( _aPrimitives.openD_audioApiCfm ) {
        _aPrimitives.openD_audioApiCfm( aConfirm );
    }
    return;
}

void openD_audio_indication( openD_audioApiInd_t *aIndication )
{
    if( _aPrimitives.openD_audioApiInd ) {
        _aPrimitives.openD_audioApiInd( aIndication );
    }
    return;
}

#ifdef __cplusplus
}
#endif
