/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       queue.c
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      Queue implementation.
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include "queue.h"

#include "debugOutput.h"
#include "mmem.h"

#include <stddef.h>

#ifndef DEBUG_OUTPUT_ENABLE
#define DEBUG_OUTPUT_ENABLE DEBUG_QUEUE
#endif


int8_t queue_init( queue_ctx_t *ctx ) {

  if( !ctx ) {
    return -1;
  }

  ctx->first = NULL;
  ctx->last = NULL;

  return 0;
}

int8_t queue_push( queue_ctx_t *ctx, void *data, size_t size ) {
  queue_element_t *tmpElement;

  if( !ctx ) {
    return -1;
  }

  tmpElement = (queue_element_t *) MMEM_ALLOC( sizeof( queue_element_t ) );

  tmpElement->next = NULL;
  tmpElement->dataElement.size = size;
  tmpElement->dataElement.data = data;

  if( NULL == ctx->first ) {
    ctx->first = tmpElement;
    ctx->last = tmpElement;
  } else {
    ctx->last->next = tmpElement;
    ctx->last = tmpElement;
  }

  return 0;
}

queue_dataElement_t* queue_front( queue_ctx_t *ctx ) {

  if( !( ctx->first ) || !( ctx ) ) {
    return NULL;
  }

  return &(ctx->first->dataElement);
}

int8_t queue_pop( queue_ctx_t *ctx ) {
  queue_element_t *tmpElement;

  if( !ctx ) {
    return -1;
  }

  tmpElement = ctx->first;
  ctx->first = ctx->first->next;

  MMEM_FREE( (void *) tmpElement );

  return 0;
}
