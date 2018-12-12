/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iSimpleButton.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iSimpleButton.
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
 * @defgroup   OPEND_HANFUN_ISIMPLEBUTTON openD HAN-FUN iSimpleButton
 *             This module specifies the HAN-FUN simple button interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ISIMPLEBUTTON_H__
#define __OPEND_HANFUN_ISIMPLEBUTTON_H__

#include <stdint.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iSimpleButton client services.
 */
typedef enum openD_hanfun_iSimpleButtonClient_service {
  /**
   * SHORT_PRESS message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_CLIENT_SHORTPRESS,
  /**
   * LONG_PRESS message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_CLIENT_LONGPRESS,
  /**
   * EXTRA_LONG_PRESS message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_CLIENT_EXTRALONGPRESS,
  /**
   * DOUBLE_CLICK_PRESS message is received from the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_CLIENT_DOUBLECLICKPRESS,

} openD_hanfun_iSimpleButtonClient_service_t;

/**
 * openD Hanfun iSimpleButton server services.
 */
typedef enum openD_hanfun_iSimpleButtonServer_service {
  /**
   * Send a BUTTON_PRESSED message to the device to the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_PRESSED_ADDR,
  /**
   * Send a BUTTON_PRESSED message to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_PRESSED,
  /**
   * Send a BUTTON_RELEASED message to the device to the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_RELEASED_ADDR,
  /**
   * Send a BUTTON_RELEASED message to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_RELEASED,
  /**
   * Send a SHORT_PRESS message to the device to the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_SHORTPRESS_ADDR,
  /**
   * Send a SHORT_PRESS message to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_SHORTPRESS,
  /**
   * Send a LONG_PRESS message to the device to the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_LONGPRESS_ADDR,
  /**
   * Send a LONG_PRESS message to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_LONGPRESS,
  /**
   * Send a EXTRA_LONG_PRESS message to the device to the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_EXTRALONGPRESS_ADDR,
  /**
   * Send a EXTRA_LONG_PRESS message to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_EXTRALONGPRESS,
  /**
   * Send a DOUBLE_CLICK_PRESS message to the device to the given address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_DOUBLECLICKPRESS_ADDR,
  /**
   * Send a DOUBLE_CLICK_PRESS message to the broadcast address.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_DOUBLECLICKPRESS,
  /**
   * Get the Short Press Max Duration for the Simple Button server.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_GET_SHORTPRESSMAXDURATION,
  /**
   * Set the Short Press Max Duration for the Simple Button server.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_SET_SHORTPRESSMAXDURATION,
  /**
   * Get the Extra Long Press Min Duration for the Simple Button server.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_GET_EXTRALONGPRESSMINDURATION,
  /**
   * Set the Extra Long Press Min Duration for the Simple Button server.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_SET_EXTRALONGPRESSMINDURATION,
  /**
   * Get the Double Click Gap Duration for the Simple Button server.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_GET_DOUBLECLICKGAPDURATION,
  /**
   * Set the Double Click Gap Duration for the Simple Button server.
   */
  OPEND_HANFUN_ISIMPLEBUTTON_SERVER_SET_DOUBLECLICKGAPDURATION,

} openD_hanfun_iSimpleButtonServer_service_t;

/**
 * openD Hanfun iSimpleButton client indication parameter structure of the @c SHORTPRESS, @c LONGPRESS, @c EXTRALONGPRESS and @c DOUBLECLICKPRESS service.
 */
typedef struct openD_hanfun_iSimpleButtonClientInd_addr {
  /**
   * Hanfun address of the device to send the message to.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iSimpleButtonClientInd_addr_t;

/**
 * openD Hanfun iSimpleButton server request parameter structure of the @c SHORTPRESS_ADDR, @c LONGPRESS_ADDR, @c EXTRALONGPRESS_ADDR and @c DOUBLECLICKPRESS_ADDR service.
 */
typedef struct openD_hanfun_iSimpleButtonServerReq_addr {
  /**
   * Hanfun address of the device to send the message to.
   */
  openD_hanfun_address_t addr;
} openD_hanfun_iSimpleButtonServerReq_addr_t;

/**
 * openD Hanfun iSimpleButton server request parameter structure of the @c PRESSED_ADDR and @c RELEASED_ADDR service.
 */
typedef struct openD_hanfun_iSimpleButtonServerReq_addrTime {
  /**
   * Hanfun address of the device to send the message to.
   */
  openD_hanfun_address_t addr;
  /**
   * Time in milliseconds the button was pressed/released.
   */
  uint16_t timestamp;
} openD_hanfun_iSimpleButtonServerReq_addrTime_t;

/**
 * openD Hanfun iSimpleButton server request parameter structure of the @c PRESSED and @c RELEASED service.
 */
typedef struct openD_hanfun_iSimpleButtonServerReq_time {
  /**
   * Time in milliseconds the button was pressed/released.
   */
  uint16_t timestamp;
} openD_hanfun_iSimpleButtonServerReq_time_t;

/**
 * openD Hanfun iSimpleButton server request parameter structure of the @c SET_SHORTPRESSMAXDURATION, @c SET_EXTRALONGPRESSMINDURATION and @c SET_DOUBLECLICKGAPDURATION service.
 */
typedef struct openD_hanfun_iSimpleButtonServerReq_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleButtonServerReq_uint16_t;

/**
 * openD Hanfun iSimpleButton server confirm parameter structure of the @c GET_SHORTPRESSMAXDURATION, @c GET_EXTRALONGPRESSMINDURATION and @c GET_DOUBLECLICKGAPDURATION service.
 */
typedef struct openD_hanfun_iSimpleButtonServerCfm_uint16 {
  /**
   * Value.
   */
  uint16_t value;
} openD_hanfun_iSimpleButtonServerCfm_uint16_t;

/**
 * openD Hanfun iSimpleButton client indication structure.
 */
typedef struct openD_hanfun_iSimpleButtonClientInd {
  /**
   * Hanfun iSimpleButton client service.
   */
  openD_hanfun_iSimpleButtonClient_service_t service;

  /**
   * Hanfun iSimpleButton parameters.
   */
  union {
    openD_hanfun_iSimpleButtonClientInd_addr_t shortPress;
    openD_hanfun_iSimpleButtonClientInd_addr_t longPress;
    openD_hanfun_iSimpleButtonClientInd_addr_t extraLongPress;
    openD_hanfun_iSimpleButtonClientInd_addr_t doubleClickPress;
  } param;
} openD_hanfun_iSimpleButtonClientInd_t;

/**
 * openD Hanfun iSimpleButton server request structure.
 */
typedef struct openD_hanfun_iSimpleButtonServerReq {
  /**
   * Hanfun iSimpleButton server service.
   */
  openD_hanfun_iSimpleButtonServer_service_t service;

  /**
   * Hanfun iSimpleButton parameters.
   */
  union {
    openD_hanfun_iSimpleButtonServerReq_addrTime_t pressedAddr;
    openD_hanfun_iSimpleButtonServerReq_time_t pressed;
    openD_hanfun_iSimpleButtonServerReq_addrTime_t releasedAddr;
    openD_hanfun_iSimpleButtonServerReq_time_t released;
    openD_hanfun_iSimpleButtonServerReq_addr_t shortPress;
    openD_hanfun_iSimpleButtonServerReq_addr_t longPress;
    openD_hanfun_iSimpleButtonServerReq_addr_t extraLongPress;
    openD_hanfun_iSimpleButtonServerReq_addr_t doubleClickPress;
    openD_hanfun_iSimpleButtonServerReq_uint16_t shortPressMaxDuration;
    openD_hanfun_iSimpleButtonServerReq_uint16_t extraLongPressMinDuration;
    openD_hanfun_iSimpleButtonServerReq_uint16_t doubleClickGapDuration;
  } param;
} openD_hanfun_iSimpleButtonServerReq_t;

/**
 * openD Hanfun iSimpleButton server confirm structure.
 */
typedef struct openD_hanfun_iSimpleButtonServerCfm {
  /**
   * Hanfun iSimpleButton server service.
   */
  openD_hanfun_iSimpleButtonServer_service_t service;

  /**
   * Hanfun iSimpleButton parameters.
   */
  union {
    openD_hanfun_iSimpleButtonServerCfm_uint16_t shortPressMaxDuration;
    openD_hanfun_iSimpleButtonServerCfm_uint16_t extraLongPressMinDuration;
    openD_hanfun_iSimpleButtonServerCfm_uint16_t doubleClickGapDuration;
  } param;
} openD_hanfun_iSimpleButtonServerCfm_t;


/*! @} defgroup OPEND_HANFUN_ISIMPLEBUTTON */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ISIMPLEBUTTON_H__ */

