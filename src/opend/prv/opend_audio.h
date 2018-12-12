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
 * @file       opend_audio.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD audio interface.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_AUDIO openD audio interface
 *             This file specifies the interface to the customer stack side.
 * \{
 */

#ifndef __OPEND_AUDIO_H__
#define __OPEND_AUDIO_H__

#include "opend_dataTypes.h"
#include "opend_audio_types.h"

void openD_audio_confirmation( openD_audioApiCfm_t *aConfirm );

void openD_audio_indication( openD_audioApiInd_t *aIndication );


/*! @} defgroup OPEND_AUDIO */

#endif /* __OPEND_AUDIO_H__ */
#ifdef __cplusplus
}
#endif
