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
 * @file       fifo.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger, Mario Behringer
 * @brief      utils FIFO buffer.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   UTILS_FIFO
 *             This module specifies the fifo API.
 * @{
 */

#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdint.h>
#include <stdbool.h>


/*! Fifo context structure.
    Do not touch this structure from outside the fifo module. */
typedef struct
{
  /*! Pointer to the fifo buffer. */
  uint8_t *buffer;
  /*! Size of the fifo buffer. */
  uint16_t bufferSize;
  /*! Current read index. */
  uint8_t readIndex;
  /*! Current write index. */
  uint8_t writeIndex;
  uint16_t bytesWritten;
}fifo_t;

/*!
 * @brief  Initiailizes a fifo.
 *
 * @param  fifo_t fifo to init.
 * @param  buffer Pointer to a buffer for this fifo.
 * @param  bufferSize Size of the buffer.
 * @return True if the initialization was successfull.
 */
bool openD_fifo_init(fifo_t *fifo, uint8_t *buffer, uint16_t bufferSize);

/*!
 * @brief   Calculates the remaining bytes in the fifo.
 *
 * @param   fifo Fifo to check for remaining space.
 * @return  Amount of remaining space in the fifo.
 */
uint16_t openD_fifo_remaining(fifo_t *fifo);

/*!
 * @brief   Check if the FIFO is full.
 *
 * @param   fifo Fifo to check.
 * @return  True if the fifo is full.
 */
bool openD_fifo_isFull(fifo_t *fifo);

/*!
 * @brief   Check if the FIFO is empty.
 *
 * @param   fifo Fifo to check.
 * @return  True if the fifo is empty.
 */
bool openD_fifo_isEmpty(fifo_t *fifo);


/*!
 * @brief   utils FIFO API write.
 *
 * @details Write one byte in the FIFO buffer.
 *
 * @param   fifo Fifo to write in.
 * @param   data Data to write in the buffer.
 * @return  True if writing was successfull.
 */
bool openD_fifo_write(fifo_t *fifo, uint8_t data);

/*!
 * @brief   utils FIFO API read.
 *
 * @details Read one byte from the FIFO buffer.
 *
 * @param   fifo Fifo to read from.
 * @param   data[OUT] Value stored in the fifo.
 *
 * @return  True if reading was successfull.
 */
bool openD_fifo_read(fifo_t *fifo, uint8_t *data);

/*! @} defgroup UTILS_FIFO */

#endif // __FIFO_H__

#ifdef __cplusplus
}
#endif
