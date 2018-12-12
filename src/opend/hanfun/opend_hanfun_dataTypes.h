/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_dataTypes.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN data types.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_HANFUN_DATATYPES openD Hanfun data types
 *             This header file declares the openD HAN-FUN specific data types.
 * @{
 */

#ifndef __OPEND_HANFUN_DATATYPES_H__
#define __OPEND_HANFUN_DATATYPES_H__

#include <stdint.h>

/*
 * openD Hanfun broadcast - device address.
 */
#define OPEND_HANFUN_ADDRESS_BROADCAST_DEVICE = 0x7FFF;
/*
 * openD Hanfun broadcast - unit address.
 */
#define OPEND_HANFUN_ADDRESS_BROADCAST_UNIT = 0xFF;


typedef enum openD_hanfun_address_modType
{
  /*
   * Destination address is for single device.
   */
  OPEND_HANFUN_ADDRESS_MODTYPE_DEVICE = 0,
  /*
   * Destination address is for a group of devices.
   */
  OPEND_HANFUN_ADDRESS_MODTYPE_GROUP  = 1,
} openD_hanfun_address_modType_t;

/**
 * openD Hanfun address structure.
 */
typedef struct openD_hanfun_address {
  /**
    * Address modifier.
    */
  uint16_t mod: 1;
  /**
    * Device Address.
    */
  uint16_t device: 15;
  /**
    * Unit.
    */
  uint8_t unit;
} openD_hanfun_address_t;

/**
 * openD Hanfun address structure.
 */
typedef enum openD_hanfun_result
{
  /**
   * Request OK.
   */
  OK = 0x00,
  /**
   * Fail - Not Authorized.
   */
  FAIL_AUTH = 0x01,
  /**
   * Fail - Invalid Argument.
   */
  FAIL_ARG = 0x02,
  /**
   * Fail - Not Supported.
   */
  FAIL_SUPPORT = 0x03,
  /**
   * Fail - Read only attribute.
   */
  FAIL_RO_ATTR = 0x04,
  /**
   * Fail - Read Session not established.
   */
  FAIL_READ_SESSION = 0x20,
  /**
   * Fail - Entries table modified.
   */
  FAIL_MODIFIED = 0x21,
  /**
   * Fail - Not enough resources.
   */
  FAIL_RESOURCES = 0xFE,
  /**
   * Fail - Unknown reason.
   */
  FAIL_UNKNOWN = 0xFF,
} openD_hanfun_result_t;


/*! @} defgroup OPEND_HANFUN_DATATYPES */

#endif /* __OPEND_HANFUN_DATATYPES_H__ */
