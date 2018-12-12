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

#include <Core/RtxCore.h>
#include <ProjCfg.h>
#include <PortDef.h>
#include <Ros/RosCfg.h>
#include <RtxEai/RtxEai.h>
#include "keyMessage.h"
#include "HostUtil.h"

#include "opend_dataTypes.h"
#include "opend_call_api.h"


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
    RosMailType* pMail = NULL;

    if( !cRequest ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    switch( cRequest->service ) {

        case OPEND_CALLAPI_SETUP:
            /* Set Dialog request with key message KEY_MESSAGE. */
            pMail = (RosMailType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailP1Type));
            pMail->P2.Primitive = KEY_MESSAGE;
            pMail->P2.P1 = KEY_HOOK;
            pMail->P2.P2 = cRequest->param.setup.pmid[0];

            ret = OPEND_STATUS_OK;
            break;

        case OPEND_CALLAPI_RELEASE:
            /* Set Dialog request with key message KEY_MESSAGE. */
            pMail = (RosMailType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailP1Type));
            pMail->P1.Primitive = KEY_MESSAGE;
            pMail->P1.P1 = KEY_HOOK;

            ret = OPEND_STATUS_OK;
            break;

        default:
            ret = OPEND_STATUS_SERVICE_UNKNOWN;
    }

    if(pMail) {
        /* Forward KEY_MESSAGE. */
        LocalMainAppTask((RosMailType*)pMail);
        RosMailFree((RosMailType*)pMail);
    }

    return ret;
}

void openD_call_confirmation( openD_callApiCfm_t *cConfirm ) {

    if( _cPrimitives.openD_callApiCfm ) {
        _cPrimitives.openD_callApiCfm( cConfirm );
    }
    return;
}

void openD_call_indication( openD_callApiInd_t *cIndication ) {

    if( _cPrimitives.openD_callApiInd ) {
        _cPrimitives.openD_callApiInd( cIndication );
    }
    return;
}

#ifdef __cplusplus
}
#endif
