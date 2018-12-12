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
 * @file       hdlc.h
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      API definition of the dialog specific WSM HDLC module.
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#ifndef __HDLC_H__
#define __HDLC_H__

#include <stdbool.h>
#include <stdint.h>

/** Function prototype for the hdlc parsed packet function. */
typedef void ( *hdlc_parsedPacketFct_t )( uint8_t *data, uint16_t length );

/**
 * @brief Callback function that is called when the HDLC needs memory.
 * @param data OUT Pointer to the allocated memory.
 * @param length IN Size of the memory that should be allocated.
 */
typedef void ( *hdlc_allocateMemoryFct_t )( uint8_t **data, uint16_t length );

/**
 * @brief Callback function that memory can be freed.
 * @param data IN Pointer to the memory that can be freed.
 */
typedef void ( *hdlc_freeMemoryFct_t )( uint8_t *data );

/**
 * @brief Callback function for the HDLC to transmit serial frames.
 * @param data IN Pointer to the serial frame.
 * @param length IN Length of the serial frame.
 * @return 0 success.
 *         <0 error.
 */
typedef int8_t ( *hdlc_sendSerialFct_t )( uint8_t *data, uint16_t length );

/**
 * Defines the frame types.
 * */
typedef enum {
  /* Info frame type. */
  FRAME_TYPE_INFO = 0U,
  /* Supervisory frame type. */
  FRAME_TYPE_SUPERVISORY,
  /* Unnumbered frame type. */
  FRAME_TYPE_UNNUMBERED,
} frameTypes_t;

/**
 * @brief   HDLC initialization.
 * @details This function initializes the HDLC module.
 * @param   hdlc_parsedPacket_t IN Function pointer for the callback function.
 * @retval  Status of the operation.
 *          0: Success
 *          <0:Error
 */
int8_t hdlc_init( hdlc_parsedPacketFct_t hdlc_parsedPacket,
                  hdlc_allocateMemoryFct_t hdlc_allocateMemory,
                  hdlc_freeMemoryFct_t hdlc_freeMemory, hdlc_sendSerialFct_t hdlc_sendSerial );

/**
 * @brief   HDLC get the current frame buffer length for the payload.
 * @details This function returns the needed frame buffer length for the current payload.
 * @param   payloadLength IN Current payload length.
 * @retval  Length of the needed frame buffer. 0 indicates that there was a problem.
 */
uint16_t hdlc_getInfoFrameBufferLength( uint16_t payloadLength );

/**
 * @brief   HDLC frame creation.
 * @details This function creates a HDLC frame with the given payload.
 * @param   taskId IN Task ID.
 * @param   *payloadData IN Pointer of the payload data.
 * @param   payloadLength IN Length of the playload data.
 * @retval  Status of the operation.
 *          0: Success
 *          <0:Error
 */
int8_t hdlc_infoFrameCreate( uint8_t taskId, uint8_t *payloadData, uint16_t payloadLength );

/**
 * @brief   Parses an WSM packet bytewise.
 * @details This function parses a WSM packet byte for byte and calls the callback
 *          function after a valide parse process.
 * @param   *data IN Pointer to the data memory.
 * @retval  Status of the operation.
 *          0: Success
 *          <0:Error
 */
void hdlc_packetParseBytewise( uint8_t *data );

#endif /* __HDLC_H__ */
#ifdef __cplusplus
}
#endif