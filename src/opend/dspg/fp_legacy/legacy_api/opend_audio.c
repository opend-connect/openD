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
#include "opend_audio_api.h"

/* Not supported with DHX91 hardware. */

openD_status_t openD_audioApi_init( openD_audioApiPrimitives_t *aPrimitives )
{
  return OPEND_STATUS_SERVICE_UNKNOWN;
}

openD_status_t openD_audioApi_request( openD_audioApiReq_t *aRequest )
{
  return OPEND_STATUS_SERVICE_UNKNOWN;
}

#ifdef __cplusplus
}
#endif
