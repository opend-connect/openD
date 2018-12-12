/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#include "HostUtil.h"
#include "hdlc.h"
#include "primitive_debug.h"
#include "serialPort.h"
#include "sw_timer.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/****************************************************************************
 *                     Definitions
 ****************************************************************************/
/****************************************************************************
 *                     Enumerations/Type definitions/Structs
 ****************************************************************************/

/****************************************************************************
 *                     Variable declarations
 ****************************************************************************/

/****************************************************************************
 *                               Global Vars
 ****************************************************************************/
/** Timer tick thread. */
pthread_t timerTickHandler;
pthread_mutex_t hdlcMutex;

/****************************************************************************
 *                      Function Prototypes
 ****************************************************************************/
/*---------------------------------------------------------------------------*/
/* _parsedPacketFct */
/*---------------------------------------------------------------------------*/
void _parsedPacketFct( uint8_t *data, uint16_t len ) {

  printf("RX Data:");
  for (int i = 0; i < len; ++i) {
    printf("%02x ", data[i]);
  }
  printf("\n");

  LocalMainAppTask( (RosMailType *) &data[2] );
  // print_incoming_msg( (const RosMailType *) &data[2] );
  return;
}

/*---------------------------------------------------------------------------*/
/* _allocateMemory */
/*---------------------------------------------------------------------------*/
void _allocateMemory( uint8_t **data, uint16_t length ) {

  *data = malloc( length );
}

/*---------------------------------------------------------------------------*/
/* _freeMemory */
/*---------------------------------------------------------------------------*/
void _freeMemory( uint8_t *data ) {
  free( data );
}

/*---------------------------------------------------------------------------*/
/* hdlc_hostInit */
/*---------------------------------------------------------------------------*/
int8_t _sendSerialFct( uint8_t *data, uint16_t length ) {
  return serialPort_write( data, length );
}

/*---------------------------------------------------------------------------*/
/* timerTick */
/*---------------------------------------------------------------------------*/
void *timerTick( void ) {
  /* 500 milliseconds.  */
  struct timespec sleepTime;
  sleepTime.tv_sec = 0;
  sleepTime.tv_nsec = 500000000;

  while( 1 ) {
    /* Suspend thread execution for 500 milliseconds. */
    nanosleep( &sleepTime, NULL );

    /* Update the timer interval. */
    pthread_mutex_lock( &hdlcMutex );
    sw_timer_tick( 500 );
    pthread_mutex_unlock( &hdlcMutex );
  }
}

/*---------------------------------------------------------------------------*/
/* hdlc_hostInit */
/*---------------------------------------------------------------------------*/
int hdlc_hostInit( void ) {
  int8_t returnStatus;

  if( returnStatus >= 0 ) {
    returnStatus = hdlc_init( &_parsedPacketFct, &_allocateMemory, &_freeMemory, &_sendSerialFct );
  }

  if( ( pthread_create( &timerTickHandler, NULL, (void *) &timerTick, NULL ) ) ) {
    printf( "Timer tick thread creation failed!\n" );
  }
  pthread_detach( timerTickHandler );

  return returnStatus;
}

/*---------------------------------------------------------------------------*/
/* hdlc_hostSend */
/*---------------------------------------------------------------------------*/
void hdlc_hostSend( uint8_t iTaskId, uint8_t *bInputDataPtr, uint16_t iLength ) {

  printf("TX Data:");
  for(int i = 0; i < iLength; ++i)
  {
    printf("%02x ", bInputDataPtr[i]);
  }
  printf("\n");

  pthread_mutex_lock( &hdlcMutex );
  hdlc_infoFrameCreate( iTaskId, bInputDataPtr, iLength );
  pthread_mutex_unlock( &hdlcMutex );
}
