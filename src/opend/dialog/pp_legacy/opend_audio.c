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

#include <Core/RtxCore.h>
#include <ProjCfg.h>
#include <PortDef.h>
#include <Ros/RosCfg.h>
#include <RtxEai/RtxEai.h>
#include "keyMessage.h"
#include "HostUtil.h"

#include "opend_dataTypes.h"
#include "opend_audio_api.h"

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
    RosMailType* pMail = NULL;

    if( !aRequest ) {
        return OPEND_STATUS_ARGUMENT_INVALID;
    }

    switch( aRequest->service ) {

        case OPEND_AUDIOAPI_SET_MUTE:
            if( aRequest->param.setMute.enable ) {
                /* Set Dialog request with key message KEY_MESSAGE. */
                pMail = (RosMailType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailP1Type));
                pMail->P1.Primitive = KEY_MESSAGE;
                pMail->P1.P1 = KEY_MESSAGE_REQ_MUTE;
            } else {
                /* Set Dialog request with key message KEY_MESSAGE. */
                pMail = (RosMailType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailP1Type));
                pMail->P1.Primitive = KEY_MESSAGE;
                pMail->P1.P1 = KEY_MESSAGE_REQ_UNMUTE;
            }

            ret = OPEND_STATUS_OK;
            break;

        case OPEND_AUDIOAPI_SET_VOLUME:
            /* Set Dialog request with key message KEY_MESSAGE. */
            pMail = (RosMailType*)RosMailAllocate(API_TASK, API_TASK, sizeof(RosMailP2Type));
            pMail->P2.Primitive = KEY_MESSAGE;
            pMail->P2.P1 = KEY_VOL;
            pMail->P2.P2 = aRequest->param.setVolume.level;

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
