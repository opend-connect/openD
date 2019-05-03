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
 * @file       opend_dataTypes.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD data types.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_DATATYPES openD Data types
 *             This header file declares the openD specific data types.
 * \{
 */

#ifndef __OPEND_DATATYPES_H__
#define __OPEND_DATATYPES_H__

#include <stdint.h>

/**
 * Radio Fixed Part Identity (RFPI).
 */
typedef uint8_t rfpi_t[5];

/**
 * Access code (AC).
 */
typedef uint8_t ac_t[4];

/**
 * Portable part MAC Identity (PMID).
 * |      X X X X      |              PMIF              |
 * | 4 bits (not used) |             20 bits            |
 */
typedef uint8_t pmid_t[3];

/**
 * International Portable User Identity (IPUI)
 * |  PUT   |                    PUN                    |
 * | 4 bits |                   36 bits                 |
 */
typedef uint8_t ipui_t[5];

/**
 * openD Status
 */
typedef enum
{
  /**
   * openD success status.
   */
  OPEND_STATUS_OK,
  /**
   * openD idle status.
   */
  OPEND_STATUS_IDLE,
  /**
   * openD busy status.
   */
  OPEND_STATUS_BUSY,
  /**
   * openD generic fail status.
   */
  OPEND_STATUS_FAIL,
  /**
   * openD unknown service status.
   */
  OPEND_STATUS_SERVICE_UNKNOWN,
  /**
   * openD invalid argument status.
   */
  OPEND_STATUS_ARGUMENT_INVALID,
  /**
   * openD status: Initialization of the serial interface failed.
   */
  OPEND_STATUS_SERIAL_INIT_FAIL,

} openD_status_t;


/*! @} defgroup OPEND_DATATYPES */

#endif /* __OPEND_DATATYPES_H__ */
#ifdef __cplusplus
}
#endif
