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
 * @file       opend_audio_types.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD audio types.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_AUDIO_API openD Audio API
 *             This module specifies the audio types of openD connect.
 * \{
 */

#ifndef __OPEND_AUDIO_TYPES_H__
#define __OPEND_AUDIO_TYPES_H__

#include <stdbool.h>
#include "opend_dataTypes.h"

/**
 * openD AudioApi services.
 */
typedef enum openD_audioApi_service {
  /**
   * Set mute state.
   */
  OPEND_AUDIOAPI_SET_MUTE,
  /**
   * Set volume.
   */
  OPEND_AUDIOAPI_SET_VOLUME,
  /**
   * Get mute state.
   */
  OPEND_AUDIOAPI_GET_MUTE,
  /**
   * Get volume.
   */
  OPEND_AUDIOAPI_GET_VOLUME,
} openD_audioApi_service_t;

/**
 * openD AudioApi request mute structure.
 */
typedef struct audioApiReq_mute {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
  /**
    * Mute enable.
    */
  bool enable;
} audioApiReq_mute_t;

/**
 * openD AudioApi request volume structure.
 */
typedef struct audioApiReq_volume {
  /**
   * Portable part MAC Identity (PMID).
   */
  pmid_t pmid;
  /**
    * Volume level.
    */
  uint8_t level;
} audioApiReq_volume_t;

/**
 * openD AudioApi request structure.
 */
typedef struct openD_audioApiReq {
  /**
   * AudioApi request service.
   */
  openD_audioApi_service_t service;

  /**
   * openD AudioApi request parameters.
   */
  union {
    /**
     * AudioApi parameters for a mute request.
     */
    audioApiReq_mute_t setMute;
    /**
     * AudioApi parameters for a volume request.
     */
    audioApiReq_volume_t setVolume;
  } param;
} openD_audioApiReq_t;

/**
 * openD AudioApi confirm structure.
 */
typedef struct openD_audioApiCfm {
  /**
   * AudioApi confirm service.
   */
  openD_audioApi_service_t service;
  /**
   * AudioApi service status.
   */
  openD_status_t status;
  /**
   * openD AudioApi request parameters.
   */
  union {
    /**
     * AudioApi parameters for a mute request.
     */
    audioApiReq_mute_t getMute;
    /**
     * AudioApi parameters for a volume request.
     */
    audioApiReq_volume_t getVolume;
  } param;
} openD_audioApiCfm_t;

/**
 * openD AudioApi indication structure.
 */
typedef struct openD_audioApiInd {
  /**
   * AudioApi indication service.
   */
  openD_audioApi_service_t service;
} openD_audioApiInd_t;

/*! @} defgroup OPEND_AUDIO_TYPES */

#endif /* __OPEND_AUDIO_TYPES_H__ */
#ifdef __cplusplus
}
#endif
