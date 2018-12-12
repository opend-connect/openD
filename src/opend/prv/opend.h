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
 * @file       opend.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND openD
 *             This header file specifies the internal openD interfaces.
 * \{
 */

#ifndef __OPEND_H__
#define __OPEND_H__

#include "opend_dataTypes.h"
#include "opend_api.h"

typedef enum {
  OPEND_APIS_GENERIC = 0x00,
  OPEND_APIS_AUDIO,
  OPEND_APIS_CALL,
  OPEND_APIS_MGMT,
  OPEND_APIS_SUB,
  OPEND_APIS_HANFUN,
} openD_Apis_t;

typedef struct {
  openD_Apis_t opendApis;
  void* param;
} openD_Api_t;

/**
 * @brief   Send function pointer.
 *
 * @details Send function callback primitive.
 *
 * @param   buffer Pointer to the buffer to send.
 * @param   len    Length of the buffer.
 */
typedef int8_t (*sendFct_t)(uint8_t *buffer, uint16_t len);

void openD_setStatusBusy( void );

void openD_setStatusIdle( void );

sendFct_t sendFctPtr;

/*! @} defgroup OPEND */

#endif /* __OPEND_H__ */
#ifdef __cplusplus
}
#endif
