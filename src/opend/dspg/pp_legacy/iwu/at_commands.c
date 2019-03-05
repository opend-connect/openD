/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       at_commands.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "at_commands.h"

/** AT command prefix. */
#define AT_PREFIX "AT+"
/** AT command prefix length. */
#define AT_PREFIX_LENGTH 4U

/*!
 * IWU registration finished confirmation callback.
 */
static notify_state_machine state_machine_callback;

extern char *receiveDataAlrt[4];
extern char callHandsetId;


void at_commands_parse(uint8_t atCommand[], uint16_t size)
{
  if(!state_machine_callback) return;

  if( (memcmp(atCommand, "+ALRT", 5) == 0) )
  {
    /* Tok the string "+ALRT=XXXXX,X,X\n" */
    char *ptr[4];
    ptr[0] = strtok((char*)atCommand, ":,\n");
    /* rfpi */
    ptr[1] = strtok(NULL, "=,\n");
    /* hs number */
    ptr[2] = strtok(NULL, "=,\n");
    /* success byte */
    ptr[3] = strtok(NULL, "=,\n");
    state_machine_callback(ALRT, ptr);
    return;
  }
  if( (memcmp(atCommand, "+CEND", 5) == 0) )
  {
    state_machine_callback(CEND, NULL);
    return;
  }
  if(memcmp(atCommand, "OK", 2) == 0)
  {
    state_machine_callback(OK, NULL);
    return;
  }
  if(memcmp(atCommand, "+IREG", 5) == 0)
  {
    /* Tok the string "+IREG=XXXXX,X,X\n" */
    char *ptr[4];
    ptr[0] = strtok((char*)atCommand, "=,\n");
    /* rfpi */
    ptr[1] = strtok(NULL, "=,\n");
    /* hs number */
    ptr[2] = strtok(NULL, "=,\n");
    /* success byte */
    ptr[3] = strtok(NULL, "=,\n");
    state_machine_callback(IREG, ptr);
    return;
  }
  if(memcmp(atCommand, "+DREG", 5) == 0)
  {
    /* Tok the string "+DREG=XXXXX,X\n" */
    char *ptr[4];
    ptr[0] = strtok((char*)atCommand, "=,\n");
    /* rfpi */
    ptr[1] = strtok(NULL, "=,\n");
    /* hs number */
    ptr[2] = strtok(NULL, "=,\n");
    /* success byte */
    ptr[3] = strtok(NULL, "=,\n");
    state_machine_callback(DREG, ptr);
    return;
  }
  if(memcmp(atCommand, "+CSTS", 5) == 0)
  {
    /* Tok the string "+ALRT=XXXXX,X,X\n" */
    char *ptr[4];
    ptr[0] = strtok((char*)atCommand, ":,\n");
    /* rfpi */
    ptr[1] = strtok(NULL, "=,\n");
    /* hs number */
    ptr[2] = strtok(NULL, "=,\n");
    /* success byte */
    ptr[3] = strtok(NULL, "=,\n");
    state_machine_callback(CSTS, ptr);
    return;
  }
  if(memcmp(atCommand, "+ISUB", 5) == 0)
  {
    /* Tok the string "+ISUB=X,XXXXX,X\n" */
    char *ptr[4];
    ptr[0] = strtok((char*)atCommand, "=,\n");
    /* hs number */
    ptr[1] = strtok(NULL, "=,\n");
    /* rfpi */
    ptr[2] = strtok(NULL, "=,\n");
    /* registration status */
    ptr[3] = strtok(NULL, "=,\n");
    state_machine_callback(ISUB, ptr);
    return;
  }
}

void at_commands_init(notify_state_machine state_machine)
{
  state_machine_callback = state_machine;
}

uint8_t at_commands_create(tx_states at_Command, void* data, uint8_t *buffer, uint8_t bufferLen)
{
  char* atBuffer = (char*) buffer;
  char *atPrefix = AT_PREFIX;

  /* Copy AT prefix to the buffer. */
  if( bufferLen >= AT_PREFIX_LENGTH ) {
    strcpy(atBuffer, atPrefix);
    bufferLen -= strlen(atPrefix);
  } else {
    return 0;
  }

  switch(at_Command)
  {
    case REGISTRATION_SEARCH_BASE:
      if( bufferLen < 9U ) {
        return 0;
      }
      /* Begin Searching a base. */
      strcat(atBuffer, "SSCH=80\r");
      break;

    case REGISTRATION_SEARCH_BASE_PIN:
      if( !data || ( bufferLen < 11U ) ) {
        return 0;
      }

      /* Generate SSUB AT command with pin. */
      strcat(atBuffer, "SSUB=");
      strncat(atBuffer, data, 4U);
      strcat(atBuffer, "\r");
      break;

    case CALL_SETUP:
      if( bufferLen < 8U ) {
        return 0;
      }

      /* Generate CALL AT command with handset id. */
      strcat(atBuffer, "CALL=");
      strncat(atBuffer, &callHandsetId, 1);
      strcat(atBuffer, "\r");
      break;

    case TERMINATE_CALL:
      if( bufferLen < 9U ) {
        return 0;
      }

      /* Generate CALL release AT command with call id. */
      strcat(atBuffer, "CREL=");
      strncat(atBuffer, receiveDataAlrt[1],2);
      strcat(atBuffer, "\r");
      break;

    case DEREGISTRATION:
      if( bufferLen < 6U ) {
        return 0;
      }
      /* Deregister a handset. */
      strcat(atBuffer, "DSUB\r");
      break;

    case GET_REGISTRATION_STATE:
      if( bufferLen < 9U ) {
        return 0;
      }
      /* Get registration info. */
      strcat(atBuffer, "ISUB=00\r");
      break;

    case ANSWER_CALL:
      if( bufferLen < 9U ) {
        return 0;
      }

      /* Generate CALL answer AT command with call id. */
      strcat(atBuffer, "CANS=");
      strncat(atBuffer, receiveDataAlrt[1],2);
      strcat(atBuffer, "\r");
      break;

    case AUDIO_SMOD:
      if( bufferLen < 8U ) {
        return 0;
      }
      /* Switch audio path. */
      strcat(atBuffer, "SMOD=0\r");
      break;

    case AUDIO_FDHF:
      if( bufferLen < 8U ) {
        return 0;
      }
      /* Switch audio path. */
      strcat(atBuffer, "FDHF=1\r");
      break;

    case AUDIO_SKEY:
      if( bufferLen < 11U ) {
        return 0;
      }
      /* Full Duplex handsfree. */
      strcat(atBuffer, "SKEY=0000\r");
      break;

    case AUDIO_INIT:
    case INIT:
    default:
      buffer = NULL;
      break;
  }

  return strlen((char*) buffer);;
}
