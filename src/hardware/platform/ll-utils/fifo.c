/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       fifo.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Mario Behringer, <mario.behringer@stackforce.de>
 * @brief      openD FIFO buffer.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */

#include "fifo.h"

/*==============================================================================
                            LOCAL FUNCTIONS
==============================================================================*/

/*
 * Returns the next index.
 *
 * @param fifo  Fifo for which the next index should be returned.
 * @param index Current index that should be incremented.
 * @return Next index.
 */
uint16_t _getIndexNext(fifo_t *fifo, uint16_t index)
{
  if(index == 0xffff)
  {
    /* Prevent overflow. */
    return 0;
  }

  index++;

  return index % fifo->bufferSize;
}

/*==============================================================================
                            FUNCTIONS
==============================================================================*/

/*----------------------------------------------------------------------------*/
/*! openD_fifo_init() */
/*----------------------------------------------------------------------------*/
bool openD_fifo_init(fifo_t *fifo, uint8_t *buffer, uint16_t bufferSize)
{
  if(!fifo || !buffer || !bufferSize)
  {
    return false;
  }

  fifo->buffer = buffer;
  fifo->bufferSize = bufferSize;
  fifo->writeIndex = 0;
  fifo->readIndex = 0;
  fifo->bytesWritten = 0;

  return true;
}

/*----------------------------------------------------------------------------*/
/*! openD_fifo_write() */
/*----------------------------------------------------------------------------*/
bool openD_fifo_write(fifo_t *fifo, uint8_t data)
{
  if(!fifo ||
     !fifo->buffer ||
     (0 == openD_fifo_remaining(fifo)))
  {
    return false;
  }

  fifo->buffer[fifo->writeIndex] = data;
  fifo->writeIndex = _getIndexNext(fifo, fifo->writeIndex);
  fifo->bytesWritten++;

  return true;
}

/*----------------------------------------------------------------------------*/
/*! openD_fifo_read() */
/*----------------------------------------------------------------------------*/
bool openD_fifo_read(fifo_t *fifo, uint8_t *data)
{
  if(!fifo || !data ||
     openD_fifo_isEmpty(fifo))
  {
    return false;
  }

  *data = fifo->buffer[fifo->readIndex];
  fifo->readIndex = _getIndexNext(fifo, fifo->readIndex);
  fifo->bytesWritten--;

  return true;
}

/*----------------------------------------------------------------------------*/
/*! openD_fifo_remaining() */
/*----------------------------------------------------------------------------*/
uint16_t openD_fifo_remaining(fifo_t *fifo)
{
  uint16_t remaining;

  if(!fifo)
  {
    return 0;
  }

  remaining = fifo->bufferSize - fifo->bytesWritten;

  return remaining;
}

/*----------------------------------------------------------------------------*/
/*! openD_fifo_isEmpty() */
/*----------------------------------------------------------------------------*/
bool openD_fifo_isEmpty(fifo_t *fifo)
{
  bool isEmpty = false;

  if(!fifo)
  {
    return false;
  }

  if(fifo->bufferSize == openD_fifo_remaining(fifo))
  {
    isEmpty = true;
  }

  return isEmpty;
}
