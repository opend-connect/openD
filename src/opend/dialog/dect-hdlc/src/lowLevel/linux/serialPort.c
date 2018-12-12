/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       serialPort.c
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      Implementation of a serial port controller for a Linux based system.
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include "serialPort.h"

#include "debugOutput.h"
#include "mmem.h"
#include "queue.h"

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#ifndef DEBUG_OUTPUT_ENABLE
#define DEBUG_OUTPUT_ENABLE DEBUG_SERIAL_PORT
#endif

/** Serial port file descriptor. */
static int serialPort_fd;

/** TX thread. */
pthread_t threadTx;
/** TX thread state. */
volatile bool stopTxTask;
/** Queue context for TX. */
queue_ctx_t queue_ctx_tx;
/** Mutex semaphore TX. */
pthread_mutex_t mutexTx;

/** RX thread. */
pthread_t threadRx;
/** RX callback function. */
serialPort_rxCallback_t _serialPort_rxCallbackFct;
/** RX thread state. */
volatile bool stopRxTask;

/** Number of RX bytes for blocking mode. */
static uint16_t rxBytesBlock;

void *txTask( void );
void *rxTask( void );


static int _getBaudrate( serialPort_baudrate_t baudrate ) {

  switch( baudrate ) {
    case E_SERIAL_PORT_BAUDRATE_1200:
      return B1200;
      break;
    case E_SERIAL_PORT_BAUDRATE_4800:
      return B4800;
      break;
    case E_SERIAL_PORT_BAUDRATE_9600:
      return B9600;
      break;
    case E_SERIAL_PORT_BAUDRATE_19200:
      return B19200;
      break;
    case E_SERIAL_PORT_BAUDRATE_38400:
      return B38400;
      break;
    case E_SERIAL_PORT_BAUDRATE_57600:
      return B57600;
      break;
    case E_SERIAL_PORT_BAUDRATE_115200:
      return B115200;
      break;
    default:
      break;
  }

  return -1;
}

static int _set_interfaceAttributes( int fd, serialPort_init_t *serialPort_init ) {
  struct termios tty;

  memset( &tty, 0x00, sizeof( tty ) );

  if( tcgetattr( fd, &tty ) != 0 ) {
    DEBUG_WARNING( "%d - Get serial attributes..", errno );
    return -1;
  }

  int baudrate = _getBaudrate( serialPort_init->baudrate );
  cfsetospeed( &tty, baudrate );
  cfsetispeed( &tty, baudrate );

  /* Input */
  /* Ignore BREAK condition on input. */
  tty.c_iflag &= ~( IGNBRK | INLCR | ICRNL );
  /* Disable XON/OFF control. */
  tty.c_iflag &= ~( IXON | IXOFF | IXANY );

  /* Output */
  tty.c_oflag = 0;

  /* Control */
  tty.c_cflag &= ~CSIZE;               /* Clears the mask for setting the data size. */
  tty.c_cflag |= CS8;                  /* Set 8 data bits. */
  tty.c_cflag |= ( CREAD | CLOCAL );   /* Enable receive and ignore modem control lines. */
  tty.c_cflag &= ~( PARENB | PARODD ); /* Disable parity generation and check. */
  tty.c_cflag &= ~CSTOPB;              /* Set two stop bits. */
  tty.c_cflag &= ~CRTSCTS;             /* Disable RTS/CTS (hardware) flow control. (not in POSIX) */

  /* Local */
  tty.c_lflag = 0; /* Noncanonical mode. */

  /* Noncanonical input mode.
     MIN == 0, TIME > 0 (read with timeout) */
  tty.c_cc[VMIN] = 0;
  tty.c_cc[VTIME] = 5; /* Blocks read with a timeout of 0.5 seconds. */


  if( tcsetattr( fd, TCSANOW, &tty ) != 0 ) {
    DEBUG_WARNING( "%d - Set serial attributes..", errno );
    return -1;
  }

  return 0;
}

static void _set_rxMode( int fd, unsigned int block ) {
  struct termios tty;

  memset( &tty, 0, sizeof tty );
  if( tcgetattr( fd, &tty ) != 0 ) {
    DEBUG_WARNING( "%d - Get serial attributes..", errno );
    return;
  }

  /* Set blocking or non blocking mode and a timeout of 0.5 seconds. */
  tty.c_cc[VMIN] = block ? 1 : 0;
  tty.c_cc[VTIME] = 5;

  if( tcsetattr( fd, TCSANOW, &tty ) != 0 ) {
    DEBUG_WARNING( "%d - Set serial attributes.", errno );
  }

  return;
}


int serialPort_open( serialPort_init_t *serialPort_init,
                     serialPort_rxCallback_t serialPort_rxCallbackFct ) {

  int i;

  if( !serialPort_init ) {
    return -1;
  }

  _serialPort_rxCallbackFct = serialPort_rxCallbackFct;
  rxBytesBlock = serialPort_init->rxBytesBlock;


  /* Initialize TX queue. */
  queue_init( &queue_ctx_tx );

  /* Open serial port. */
  serialPort_fd = open( serialPort_init->portname, O_RDWR | O_NOCTTY | O_SYNC );
  if( serialPort_fd < 0 ) {
    DEBUG_WARNING( "%d - Opening %s: %s", errno, serialPort_init->portname, strerror( errno ) );
    return serialPort_fd;
  }

  /* Configurate interface. */
  _set_interfaceAttributes( serialPort_fd, serialPort_init );
  /* Set the RX blocking mode. */
  _set_rxMode( serialPort_fd, 1 );

  /* Initialize TX and RX thread. */
  stopRxTask = false;
  stopTxTask = false;

  if( ( i = pthread_create( &threadTx, NULL, (void *) &txTask, NULL ) ) ) {
    DEBUG_WARNING( "TX thread creation failed!\n" );
  }
  pthread_detach( threadTx );

  if( ( i = pthread_create( &threadRx, NULL, (void *) &rxTask, NULL ) ) ) {
    DEBUG_WARNING( "RX thread creation failed!\n" );
  }
  pthread_detach( threadRx );


  return serialPort_fd;
}

int serialPort_close( void ) {

  int ret;

  /* Stop TX and RX thread. */
  stopTxTask = true;
  stopRxTask = true;

  /* Close serial port. */
  ret = close( serialPort_fd );

  return ret;
}


int8_t serialPort_write( uint8_t *data, uint16_t len ) {

  int8_t ret;
  uint8_t *data1;

  if( len ) {

    data1 = (uint8_t *) MMEM_ALLOC( len );
    memcpy( data1, data, len );

    pthread_mutex_lock( &mutexTx );

    ret = queue_push( &queue_ctx_tx, (void *) data1, len );

    pthread_mutex_unlock( &mutexTx );
  }

  return ret;
}

int8_t serialPort_writeBlocking( uint8_t *data, uint16_t len ) {
  return (int8_t) write( serialPort_fd, data, len );
}

int8_t serialPort_readBlocking( uint8_t *buffer, uint16_t len ) {
  return (int8_t) read( serialPort_fd, buffer, len );
}

void *txTask( void ) {

  int8_t ret = -1;
  queue_dataElement_t *txData;
  struct timespec timeOut, remains;

  usleep( 10000 );

  while( false == stopTxTask ) {

    pthread_mutex_lock( &mutexTx );

    txData = queue_front( &queue_ctx_tx );

    /* Check if packs are exists. */
    if( txData ) {
      ret = serialPort_writeBlocking( txData->data, txData->size );
      queue_pop( &queue_ctx_tx );

      /* Erase data. */
      MMEM_FREE( txData->data );

      pthread_mutex_unlock( &mutexTx );

      if( ret > 0 ) {
      } else {
        DEBUG_WARNING( "Not able to send byte.\n" );
      }
    } else {

      pthread_mutex_unlock( &mutexTx );

      /* 50 milliseconds.  */
      timeOut.tv_sec = 0;
      timeOut.tv_nsec = 10000000;
      /* Suspend thread execution for 50 milliseconds. */
      nanosleep( &timeOut, &remains );
    }
  }

  stopRxTask = false;
  pthread_exit( 0 );
}

void *rxTask( void ) {

  int ret;
  uint8_t buffer[rxBytesBlock];

  while( false == stopRxTask ) {

    ret = serialPort_readBlocking( buffer, rxBytesBlock );

    if( ret > 0 ) {
      if( _serialPort_rxCallbackFct ) {
        _serialPort_rxCallbackFct( buffer, ret );
      }
    } else {
      DEBUG_WARNING( "Not able to read byte.\n" );
    }
  }

  stopRxTask = false;
  pthread_exit( 0 );
}
