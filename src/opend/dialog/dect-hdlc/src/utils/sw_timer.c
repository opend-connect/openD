/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       sw_timer.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      Software timer.
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */

#include "sw_timer.h"

#include "mmem.h"

#include <stdlib.h>



/*!
 * Software timer structure.
 */
struct swTimer {
  struct swTimer *next;
  uint32_t timeout;
  sw_timeoutCallback timeoutCallback;
};

/*!
 * Software timer type.
 */
typedef struct swTimer swTimer_t;

/* Global variable of the software timer */
swTimer_t *first = NULL;

/* Current time of low power timer [ms] */
uint16_t currentTime = 0;


void sw_timer_tick( uint16_t elapsedTime ) {
  currentTime = currentTime + elapsedTime;

  swTimer_t *ptr;

  ptr = first;

  if( currentTime == 65000 ) {
    currentTime = 0;
    while( ptr != NULL ) {
      ptr->timeout = ptr->timeout - 65000;
      ptr = ptr->next;
    }
  }

  ptr = first;

  while( ptr != NULL ) {
    if( currentTime >= ptr->timeout ) {
      sw_timeoutCallback callback;
      /* Store the callback function ptr temporarily.
         So timer can be handled first. */
      callback = ptr->timeoutCallback;

      ptr = ptr->next;

      MMEM_FREE( first );

      first = ptr;

      if( callback ) {
        callback( );
      }
    } else {
      break;
    }
  }
}

void sw_timer_start( uint16_t timeout, sw_timeoutCallback timeoutCallback ) {
  swTimer_t *ptr, *ptrLastOne;

  ptr = first;

  /*
   * Inserting the timer 3 different cases have to be considered:
   *   1. There is no first timer or the first timer is bigger. Insert it first.
   *   2. There are many timers, check at which place we have to insert it
   *   3. Timeout value of all existing timer is less. Insert at last place
   */

  /* Check if there is an existing timer. */
  if( ( first == NULL ) ||
      /* Or if the first timer is bigger than the new one. */
      ( ( ptr->timeout - currentTime ) > timeout ) ) {
    /* Insert timer at first place. */
    first = (swTimer_t *) MMEM_ALLOC( sizeof( swTimer_t ) );
    first->timeout = ( uint32_t )( timeout + currentTime );
    first->timeoutCallback = timeoutCallback;
    /* There is no next timer. */
    first->next = ptr;
  } else {
    /* Run through the list of existing pointer. */
    while( ptr->next != NULL ) {
      ptrLastOne = ptr;
      ptr = ptr->next;
      if( ( ptr->timeout - currentTime ) > timeout ) {
        /*
         * 2. One of the existing timer is bigger than the new one.
         *    Insert it here.
         */
        ptrLastOne->next = (swTimer_t *) MMEM_ALLOC( sizeof( *ptr ) );
        swTimer_t *newPtr = ptrLastOne->next;

        newPtr->timeout = ( uint32_t )( timeout + currentTime );
        newPtr->timeoutCallback = timeoutCallback;

        ptrLastOne->next->next = ptr;

        /* Timer is insereted. Exit function here! */
        return;
      }
    }

    /*
     * 3.  In case there is no bigger timer the new one is inserted here as one.
     */
    ptr->next = (swTimer_t *) MMEM_ALLOC( sizeof( *ptr ) );

    ptr = ptr->next;

    ptr->timeout = ( uint32_t )( timeout + currentTime );
    ptr->timeoutCallback = timeoutCallback;

    ptr->next = NULL;
  }
}
