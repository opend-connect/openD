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
 * @file       messageManager.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      Message handler.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */

#ifndef __MESSAGEMANAGER_H__
#define __MESSAGEMANAGER_H__

#include <stdint.h>

#include "stateManager.h"

/**
 * Messages primitives.
 */
typedef enum {
  MESSAGE_PRIMITIVE_INIT = 0x00,
  MESSAGE_PRIMITIVE_LEAVE,
  MESSAGE_PRIMITIVE_TIMEOUT,
  MESSAGE_PRIMITIVE_REQ,
  MESSAGE_PRIMITIVE_CFM,
  MESSAGE_PRIMITIVE_IND,
  MESSAGE_PRIMITIVE_RES,
  MESSAGE_PRIMITIVE_REQ_RES,
  MESSAGE_PRIMITIVE_CFM_IND,
  MESSAGE_PRIMITIVE_USER,

} messageManager_primitives_t;

/**
 * Structure of messages.
 */
typedef struct {
  messageManager_primitives_t primitive;
  void *param;
} messageManager_t;

#endif /* __MESSAGEMANAGER_H__ */
#ifdef __cplusplus
}
#endif
