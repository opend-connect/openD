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
#include "opend_sub_api.h"

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
    RosMailType* pMail = NULL;

    if( !sRequest ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    switch( sRequest->service ) {

        case OPEND_SUBAPI_SUBSCRIBE:

            /* Set Dialog request with key message KEY_MESSAGE. */
            pMail = (RosMailType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailP1Type));
            pMail->P1.Primitive = KEY_MESSAGE;
            pMail->P1.P1 = KEY_MESSAGE_REQ_REG;

            ret = OPEND_STATUS_OK;
            break;

        case OPEND_SUBAPI_SET_AC:

            /* Set access code. */
            pMail = (RosMailType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailP5Type));
            pMail->P5.Primitive = KEY_MESSAGE;
            pMail->P5.P1 = KEY_MESSAGE_REQ_SET_AC;
            pMail->P5.P2 = sRequest->param.setAc.ac[0];
            pMail->P5.P3 = sRequest->param.setAc.ac[1];
            pMail->P5.P4 = sRequest->param.setAc.ac[2];
            pMail->P5.P5 = sRequest->param.setAc.ac[3];

            ret = OPEND_STATUS_OK;
            break;

        case OPEND_SUBAPI_SUBSCRIPTION_DELETE:

            /* Set Dialog request with key message KEY_MESSAGE. */
            pMail = (RosMailType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailP1Type));
            pMail->P1.Primitive = KEY_MESSAGE;
            pMail->P1.P1 = KEY_MESSAGE_REQ_DEREG;

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
