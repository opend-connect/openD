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
 * @author     Patrick Weber
 * @brief      openD legacy subscription.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <Core/RtxCore.h>
#include <ProjCfg.h>
#include <PortDef.h>
#include <Ros/RosCfg.h>
#include <RtxEai/RtxEai.h>
#include "keyMessage.h"
#include "HostUtil.h"

#include "opend_dataTypes.h"
#include "opend.h"
#include "opend_api.h"
#include "opend_sub.h"
#include "opend_sub_api.h"

#include "opend_states.h"
#include "msManager.h"

openD_subApiPrimitives_t _sPrimitives;

openD_status_t openD_subApi_init( openD_subApiPrimitives_t *sPrimitives )
{
    if( !sPrimitives ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    _sPrimitives.openD_subApiCfm = sPrimitives->openD_subApiCfm;
    _sPrimitives.openD_subApiInd = sPrimitives->openD_subApiInd;

    return OPEND_STATUS_OK;
}

openD_status_t openD_subApi_request( openD_subApiReq_t *sRequest )
{
    openD_status_t ret;
    messageManager_t message;
    openD_Api_t openD_Api;

    if( !sRequest ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    /* Check openD state. */
    if( OPEND_STATUS_IDLE != openD_api_getStatus() ) {
        return OPEND_STATUS_BUSY;
    }
    /* Set the openD state into busy. */
    openD_setStatusBusy();


    openD_Api.opendApis = OPEND_APIS_SUB;
    openD_Api.param = sRequest;
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

void openD_sub_confirmation( openD_subApiCfm_t *sConfirm ) {

    if( _sPrimitives.openD_subApiCfm ) {
        _sPrimitives.openD_subApiCfm( sConfirm );
    }
    return;
}

void openD_sub_indication( openD_subApiInd_t *sIndication ) {

    if( _sPrimitives.openD_subApiInd ) {
        _sPrimitives.openD_subApiInd( sIndication );
    }
    return;
}

#ifdef __cplusplus
}
#endif
