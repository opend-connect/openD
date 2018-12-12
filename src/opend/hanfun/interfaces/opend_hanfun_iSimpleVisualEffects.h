/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iSimpleVisualEffects.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iSimpleVisualEffects.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @addtogroup OPEND_HANFUN_INTERFACE
 * @{
 *
 * @defgroup   OPEND_HANFUN_ISIMPLEVISUALEFFECTS openD HAN-FUN iSimpleVisualEffects
 *             This module specifies the HAN-FUN simple visual effects interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ISIMPLEVISUALEFFECTS_H__
#define __OPEND_HANFUN_ISIMPLEVISUALEFFECTS_H__

#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iSimpleVisualEffects client services.
 */
typedef enum openD_hanfun_iSimpleVisualEffectsClient_service {
  /**
   * Send a ON message with the duration to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_ON,
  /**
   * Send a ON message with the duration to the given address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_ON_ADDR,
  /**
   * Send a OFF message to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_OFF,
  /**
   * Send a OFF message to the given address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_OFF_ADDR,
  /**
   * Send a BLINK message with the blinkEffect to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_BLINK,
  /**
   * Send a BLINK message with the blinkEffect to the given address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_BLINK_ADDR,
  /**
   * Send a FADE message with the fadeEffect to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_FADE,
  /**
   * Send a FADE message with the fadeEffect to the given address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_FADE_ADDR,
  /**
   * Send a BREATHE message with the breatheEffect to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_BREATHE,
  /**
   * Send a BREATHE message with the breatheEffect to the given address.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_CLIENT_BREATHE_ADDR,

} openD_hanfun_iSimpleVisualEffectsClient_service_t;

/**
 * openD Hanfun iSimpleVisualEffects server services.
 */
typedef enum openD_hanfun_iSimpleVisualEffectsServer_service {
  /**
   * ON message is received from the address @c openD_hanfun_address_t with
   * @ref openD_hanfun_iSimpleVisualEffects_onEffect_t.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_SERVER_ON_ADDR,
  /**
   * OFF message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_SERVER_OFF_ADDR,
  /**
   * BLINK message is received from the address @c openD_hanfun_address_t with
   * @ref openD_hanfun_iSimpleVisualEffects_blinkEffect_t.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_SERVER_BLINK_ADDR,
  /**
   * FADE message is received from the address @c openD_hanfun_address_t with
   * @ref openD_hanfun_iSimpleVisualEffects_fadeEffect_t.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_SERVER_FADE_ADDR,
  /**
   * BREATHE message is received from the address @c openD_hanfun_address_t with
   * @ref openD_hanfun_iSimpleVisualEffects_breatheEffect_t.
   */
  OPEND_HANFUN_ISIMPLEVISUALEFFECTS_SERVER_BREATHE_ADDR,

} openD_hanfun_iSimpleVisualEffectsServer_service_t;

/**
 * openD Hanfun iSimpleVisualEffects OnEffect structure.
 */
typedef struct openD_hanfun_iSimpleVisualEffects_onEffect {
  /**
   * Duration of how long keep the visual indicator @c ON in milliseconds.
   */
  uint16_t duration;
} openD_hanfun_iSimpleVisualEffects_onEffect_t;

/**
 * openD Hanfun iSimpleVisualEffects client request parameter structure of the @c ON service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq_on {
  /**
   * iSimpleVisualEffects onEffect.
   */
  openD_hanfun_iSimpleVisualEffects_onEffect_t onEffect;
} openD_hanfun_iSimpleVisualEffectsClientReq_on_t;

/**
 * openD Hanfun iSimpleVisualEffects client request parameter structure of the @c ON_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq_onAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * iSimpleVisualEffects onEffect.
   */
  openD_hanfun_iSimpleVisualEffects_onEffect_t onEffect;
} openD_hanfun_iSimpleVisualEffectsClientReq_onAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects server request parameter structure of the @c ON_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsServerReq_onAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * iSimpleVisualEffects onEffect.
   */
  openD_hanfun_iSimpleVisualEffects_onEffect_t onEffect;
} openD_hanfun_iSimpleVisualEffectsServerReq_onAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects client request parameter structure of the @c OFF_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq_offAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iSimpleVisualEffectsClientReq_offAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects server request parameter structure of the @c OFF_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsServerReq_offAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iSimpleVisualEffectsServerReq_offAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects BlinkEffect structure.
 */
typedef struct openD_hanfun_iSimpleVisualEffects_blinkEffect {
  /**
   * Duty cycle of how long keep the visual indicator @c ON in milliseconds.
   */
  uint16_t duty_cycle_on;
  /**
   * Duty cycle of how long keep the visual indicator @c OFF in milliseconds.
   */
  uint16_t duty_cycle_off;
  /**
   * Number of times to repeat the ON/OFF cycle.
   */
  uint16_t number_of_cycle;
} openD_hanfun_iSimpleVisualEffects_blinkEffect_t;

/**
 * openD Hanfun iSimpleVisualEffects client request parameter structure of the @c BLINK service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq_blink {
  /**
   * iSimpleVisualEffects blinkEffect.
   */
  openD_hanfun_iSimpleVisualEffects_blinkEffect_t blinkEffect;
} openD_hanfun_iSimpleVisualEffectsClientReq_blink_t;

/**
 * openD Hanfun iSimpleVisualEffects client request parameter structure of the @c BLINK_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq_blinkAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * iSimpleVisualEffects blinkEffect.
   */
  openD_hanfun_iSimpleVisualEffects_blinkEffect_t blinkEffect;
} openD_hanfun_iSimpleVisualEffectsClientReq_blinkAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects server request parameter structure of the @c BLINK_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsServerReq_blinkAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * iSimpleVisualEffects blinkEffect.
   */
  openD_hanfun_iSimpleVisualEffects_blinkEffect_t blinkEffect;
} openD_hanfun_iSimpleVisualEffectsServerReq_blinkAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects FadeEffect structure.
 */
typedef struct openD_hanfun_iSimpleVisualEffects_fadeEffect {
  /**
   * Start brightness in percentage.
   */
  uint8_t start;
  /**
   * End brightness in percentage.
   */
  uint8_t end;
  /**
   * Time in milliseconds to go from @c start brightness to @c end brightness.
   */
  uint16_t duration;
} openD_hanfun_iSimpleVisualEffects_fadeEffect_t;

/**
 * openD Hanfun iSimpleVisualEffects client request parameter structure of the @c FADE service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq_fade {
  /**
   * iSimpleVisualEffects fadeEffect.
   */
  openD_hanfun_iSimpleVisualEffects_fadeEffect_t fadeEffect;
} openD_hanfun_iSimpleVisualEffectsClientReq_fade_t;

/**
 * openD Hanfun iSimpleVisualEffects client request parameter structure of the @c FADE_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq_fadeAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * iSimpleVisualEffects fadeEffect.
   */
  openD_hanfun_iSimpleVisualEffects_fadeEffect_t fadeEffect;
} openD_hanfun_iSimpleVisualEffectsClientReq_fadeAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects server request parameter structure of the @c FADE_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsServerReq_fadeAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * iSimpleVisualEffects fadeEffect.
   */
  openD_hanfun_iSimpleVisualEffects_fadeEffect_t fadeEffect;
} openD_hanfun_iSimpleVisualEffectsServerReq_fadeAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects BreatheEffect structure for the @c BREATHE message.
 */
typedef struct openD_hanfun_iSimpleVisualEffects_breatheEffect {
  /**
   * Start brightness in percentage.
   */
  uint8_t start;
  /**
   * Number of milliseconds to hold @c start brightness.
   */
  uint16_t start_hold;
  /**
   * Number of milliseconds to go from @c start to @c end brightness.
   */
  uint16_t ste_duration;
  /**
   * End brightness in percentage.
   */
  uint8_t end;
  /**
   * Number of milliseconds to hold @c end brightness.
   */
  uint16_t end_hold;
  /**
   * Number of milliseconds to go from @c end to @c start brightness.
   */
  uint16_t ets_duration;
  /**
   * Number of times to repeat the start/end/start cycle.
   */
  uint16_t number_of_cycle;
} openD_hanfun_iSimpleVisualEffects_breatheEffect_t;

/**
 * openD Hanfun iSimpleVisualEffects client request parameter structure of the @c BREATHE service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq_breathe {
  /**
   * iSimpleVisualEffects breatheEffect.
   */
  openD_hanfun_iSimpleVisualEffects_breatheEffect_t breatheEffect;
} openD_hanfun_iSimpleVisualEffectsClientReq_breathe_t;

/**
 * openD Hanfun iSimpleVisualEffects client request parameter structure of the @c BREATHE_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq_breatheAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * iSimpleVisualEffects breatheEffect.
   */
  openD_hanfun_iSimpleVisualEffects_breatheEffect_t breatheEffect;
} openD_hanfun_iSimpleVisualEffectsClientReq_breatheAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects server request parameter structure of the @c BREATHE_ADDR service.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsServerReq_breatheAddr {
  /**
   * Hanfun device address.
   */
  openD_hanfun_address_t addr;
  /**
   * iSimpleVisualEffects breatheEffect.
   */
  openD_hanfun_iSimpleVisualEffects_breatheEffect_t breatheEffect;
} openD_hanfun_iSimpleVisualEffectsServerReq_breatheAddr_t;

/**
 * openD Hanfun iSimpleVisualEffects client request structure.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsClientReq {
  /**
   * Hanfun iSimpleVisualEffects client service.
   */
  openD_hanfun_iSimpleVisualEffectsClient_service_t service;

  /**
   * Hanfun iSimpleVisualEffects parameters.
   */
  union {
    openD_hanfun_iSimpleVisualEffectsClientReq_on_t on;
    openD_hanfun_iSimpleVisualEffectsClientReq_onAddr_t onAddr;
    openD_hanfun_iSimpleVisualEffectsClientReq_offAddr_t offAddr;
    openD_hanfun_iSimpleVisualEffectsClientReq_blink_t blink;
    openD_hanfun_iSimpleVisualEffectsClientReq_blinkAddr_t blinkAddr;
    openD_hanfun_iSimpleVisualEffectsClientReq_fade_t fade;
    openD_hanfun_iSimpleVisualEffectsClientReq_fadeAddr_t fadeAddr;
    openD_hanfun_iSimpleVisualEffectsClientReq_breathe_t breathe;
    openD_hanfun_iSimpleVisualEffectsClientReq_breatheAddr_t breatheAddr;
  } param;
} openD_hanfun_iSimpleVisualEffectsClientReq_t;

/**
 * openD Hanfun iSimpleVisualEffects server indication structure.
 */
typedef struct openD_hanfun_iSimpleVisualEffectsServerInd {
  /**
   * Hanfun iSimpleVisualEffects server service.
   */
  openD_hanfun_iSimpleVisualEffectsServer_service_t service;

  /**
   * Hanfun iSimpleVisualEffects parameters.
   */
  union {
    openD_hanfun_iSimpleVisualEffectsServerReq_onAddr_t onAddr;
    openD_hanfun_iSimpleVisualEffectsServerReq_offAddr_t offAddr;
    openD_hanfun_iSimpleVisualEffectsServerReq_blinkAddr_t blinkAddr;
    openD_hanfun_iSimpleVisualEffectsServerReq_fadeAddr_t fadeAddr;
    openD_hanfun_iSimpleVisualEffectsServerReq_breatheAddr_t breatheAddr;
  } param;
} openD_hanfun_iSimpleVisualEffectsServerInd_t;


/*! @} defgroup OPEND_HANFUN_ISIMPLEVISUALEFFECTS */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ISIMPLEVISUALEFFECTS_H__ */

