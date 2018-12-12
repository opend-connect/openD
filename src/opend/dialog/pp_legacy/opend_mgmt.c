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
 * @file       opend_mgmt.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD legacy management.
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
#include "opend_mgmt_api.h"
#include "opend_mgmt.h"


openD_mgmtApiPrimitives_t _mPrimitives;

openD_status_t openD_mgmtApi_init( openD_mgmtApiPrimitives_t *mPrimitives )
{
    if( !mPrimitives ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    _mPrimitives.openD_mgmtApiCfm = mPrimitives->openD_mgmtApiCfm;
    _mPrimitives.openD_mgmtApiInd = mPrimitives->openD_mgmtApiInd;

    return OPEND_STATUS_OK;
}

openD_status_t openD_mgmtApi_request( openD_mgmtApiReq_t *mRequest )
{
    openD_status_t ret;

    if( !mRequest ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    /* Check openD state. */
    if( OPEND_STATUS_IDLE != openD_api_getStatus() ) {
        return OPEND_STATUS_BUSY;
    }
    /* Set the openD state into busy. */
    openD_setStatusBusy();

    switch( mRequest->service ) {

        default:
            ret = OPEND_STATUS_SERVICE_UNKNOWN;
    }

    /* Release the openD state. */
    openD_setStatusIdle();
    return ret;
}

void openD_mgmt_confirmation( openD_mgmtApiCfm_t *mConfirm ) {

    if( _mPrimitives.openD_mgmtApiCfm ) {
        _mPrimitives.openD_mgmtApiCfm( mConfirm );
    }
    return;
}

void openD_mgmt_indication( openD_mgmtApiInd_t *mIndication ) {

    if( _mPrimitives.openD_mgmtApiInd ) {
        _mPrimitives.openD_mgmtApiInd( mIndication );
    }
    return;
}

#ifdef __cplusplus
}
#endif
