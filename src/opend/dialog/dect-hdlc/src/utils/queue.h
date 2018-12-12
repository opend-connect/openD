#ifdef __cplusplus
extern "C" {
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
 * @file       queue.h
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      Queue API.
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdint.h>
#include <stddef.h>

typedef struct {
  size_t size;
  void *data;
} queue_dataElement_t;

typedef struct queue_element {
  struct queue_element *next;
  queue_dataElement_t dataElement;
} queue_element_t;


typedef struct {
  queue_element_t *first, *last;
} queue_ctx_t;

int8_t queue_init( queue_ctx_t *ctx );
int8_t queue_push( queue_ctx_t *ctx, void *data, size_t size );
queue_dataElement_t* queue_front( queue_ctx_t *ctx );
int8_t queue_pop( queue_ctx_t *ctx );

#endif /* __QUEUE_H__ */
#ifdef __cplusplus
}
#endif
