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
 * @file       opend_audio_api.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD audio API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_AUDIO_API openD Audio API
 *             This module specifies the audio API of openD connect.
 * \{
 */

#ifndef __OPEND_AUDIO_API_H__
#define __OPEND_AUDIO_API_H__

#include <stdbool.h>
#include "opend_dataTypes.h"
#include "opend_audio_types.h"

/**
 * openD AudioApi primitives structure.
 */
typedef struct openD_audioApiPrimitives {
  /**
   * @brief   AudioApi confirm primitive.
   *
   * @param   aConfirm Pointer to the AudioApi confirm structure (@ref openD_audioApiCfm_t).
   */
  void ( *openD_audioApiCfm )( openD_audioApiCfm_t *aConfirm );
  /**
   * @brief   AudioApi indication primitive.
   *
   * @param   aIndication Pointer to the AudioApi indication structure (@ref openD_audioApiInd_t).
   */
  void ( *openD_audioApiInd )( openD_audioApiInd_t *aIndication );
} openD_audioApiPrimitives_t;

/**
 * @brief   openD audio API initialization.
 *
 * @param   aPrimitives Pointer of the audio API primitives structure (@ref openD_audioApiPrimitives_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_audioApi_init( openD_audioApiPrimitives_t *aPrimitives );

/**
 * @brief   openD audio API request.
 *
 * @param   aRequest Pointer of the audio API request structure (@ref openD_audioApiReq_t).
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_audioApi_request( openD_audioApiReq_t *aRequest );


/*! @} defgroup OPEND_AUDIO_API */

#endif /* __OPEND_AUDIO_API_H__ */
#ifdef __cplusplus
}
#endif
