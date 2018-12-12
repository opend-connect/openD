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
 * @file       serialPort.h
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      API definition of a serial port controller for a Linux based system.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#ifndef __SERIAL_PORT_H__
#define __SERIAL_PORT_H__

#include <stdint.h>

/**
 * Defines the supported baudrate.
 * */
typedef enum {
  E_SERIAL_PORT_BAUDRATE_1200,
  E_SERIAL_PORT_BAUDRATE_4800,
  E_SERIAL_PORT_BAUDRATE_9600,
  E_SERIAL_PORT_BAUDRATE_19200,
  E_SERIAL_PORT_BAUDRATE_38400,
  E_SERIAL_PORT_BAUDRATE_57600,
  E_SERIAL_PORT_BAUDRATE_115200,
} serialPort_baudrate_t;

/**
 * Serial port initialization structure.
 * */
typedef struct {
  /** Serial port name, e.g. /dev/ttyUSB0. */
  const char *portname;
  /** Serial port baudrate. */
  serialPort_baudrate_t baudrate;
  /** Defines up to how many bytes should the RX be blocked. */
  uint16_t rxBytesBlock;
} serialPort_init_t;

/** Function prototype for the serial port RX callback function. */
typedef void ( *serialPort_rxCallback_t )( uint8_t *data, uint16_t len );


/**
 * @brief   Serial port open.
 * @details This function opens a serial port.
 * @param   serialPort_init IN Pointer to a serial port initialization structure.
 * @param   serialPort_rxCallbackFct IN Function pointer for the RX callback function.
 * @retval  int Status of the operation.
 *          0: Success
 *          <0:Error
 */
int serialPort_open( serialPort_init_t *serialPort_init,
                     serialPort_rxCallback_t serialPort_rxCallbackFct );

/**
 * @brief   Serial port write.
 * @details This function closes the serial port.
 * @retval  int Status of the operation.
 *          0: Success
 *          <0:Error
 */
int serialPort_close( void );

/**
 * @brief   Serial port write.
 * @details This function sends data via the serial port in non-blocking mode.
 * @param   *data IN Pointer to the data memory.
 * @param   len IN Length of the data memory.
 * @retval  int Status of the operation.
 *          0: Success
 *          <0:Error
 */
int8_t serialPort_write( uint8_t *data, uint16_t len );

/**
 * @brief   Serial port write in blocking mode.
 * @details This function sends data via the serial port in blocking mode.
 * @param   *data IN Pointer to the data memory.
 * @param   len IN Length of the data memory.
 * @retval  int Status of the operation.
 *          0: Success
 *          <0:Error
 */
int8_t serialPort_writeBlocking( uint8_t *data, uint16_t len );

/**
 * @brief   Serial port read in blocking mode.
 * @details This function reads data from the serial port in blocking mode.
 * @param   *buffer OUT Pointer to a buffer.
 * @param   len IN Length of the data buffer.
 * @retval  int Status of the operation.
 *          0: Success
 *          <0:Error
 */
int8_t serialPort_readBlocking( uint8_t *buffer, uint16_t len );

#endif /* __SERIAL_PORT_H__ */
#ifdef __cplusplus
}
#endif
