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

/*!
 * IWU registration finished confirmation callback.
 */
static notify_state_machine state_machine_callback;

/**
 * @brief   Create command buffer.
 *
 * @details Create AT command buffer for the TX state.
 *
 * @param   at_Command TX state to create the AT command buffer.
 * @param   cmdBuffer Buffer to write the AT command into.
 *
 * @retval  Length of the created AT command..
 */
static uint8_t createCommand(tx_states at_Command, uint8_t *cmdBuffer);

extern char *receiveDataAlrt[4];
extern char callHandsetId;

void receive_at_command(uint8_t atCommand[], uint16_t size)
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

void init_at_commands(notify_state_machine state_machine)
{
  state_machine_callback = state_machine;
}

static uint8_t createCommand(tx_states at_Command, uint8_t *cmdBuffer)
{
  uint8_t atCmdLen = 0;
  char *atCmd = NULL;
  bool freeAtCmdMemory = false;

  if(at_Command == REGISTRATION_SEARCH_BASE)
  {
    atCmd = "AT+SSCH=80\r";
    atCmdLen = strlen(atCmd);
  }
  if(at_Command == REGISTRATION_SEARCH_BASE_PIN)
  {
    atCmd = "AT+SSUB=0000\r";
    atCmdLen = strlen(atCmd);
  }
  if(at_Command == CALL_SETUP)
  {
    atCmd = (char *)malloc(10);
    if(atCmd)
    {
      strcpy(atCmd, "AT+CALL=");
      strncat(atCmd, &callHandsetId, 1);
      strcat(atCmd, "\r");
      atCmdLen = strlen(atCmd);
      freeAtCmdMemory = true;
    }
  }
  if(at_Command == TERMINATE_CALL)
  {
    atCmd = (char *)malloc(11);
    if(atCmd)
    {
      strcpy(atCmd, "AT+CREL=");
      strncat(atCmd, receiveDataAlrt[1],2);
      strcat(atCmd, "\r");
      atCmdLen = strlen(atCmd);
      freeAtCmdMemory = true;
    }
  }
  if(at_Command == DEREGISTRATION)
  {
    atCmd = "AT+DSUB\r";
    atCmdLen = strlen(atCmd);
  }
  if(at_Command == GET_REGISTRATION_STATE)
  {
    atCmd = "AT+ISUB=00\r";
    atCmdLen = strlen(atCmd);
  }
  if(at_Command == ANSWER_CALL)
  {
    atCmd = (char *)malloc(11);
    if(atCmd)
    {
      strcpy(atCmd, "AT+CANS=");
      strncat(atCmd, receiveDataAlrt[1],2);
      strcat(atCmd, "\r");
      atCmdLen = strlen(atCmd);
      freeAtCmdMemory = true;
    }
  }
  if(at_Command == AUDIO_SMOD)
  {
    atCmd = "AT+SMOD=0\r";
    atCmdLen = strlen(atCmd);
  }
  if(at_Command == AUDIO_FDHF)
  {
    atCmd = "AT+FDHF=1\r";
    atCmdLen = strlen(atCmd);
  }
  if(at_Command == AUDIO_SKEY)
  {
    atCmd = "AT+SKEY=0000\r";
    atCmdLen = strlen(atCmd);
  }

  if(NULL != atCmd)
  {
    memcpy(cmdBuffer, atCmd, atCmdLen);

    if(freeAtCmdMemory)
    {
      free(atCmd);
    }
  }

  return atCmdLen;
}

uint8_t send_at_command(tx_states at_Command, uint8_t *buffer)
{
  uint8_t len = 0;

  switch(at_Command)
  {
    case REGISTRATION_SEARCH_BASE:
    case REGISTRATION_SEARCH_BASE_PIN:
    case CALL_SETUP:
    case TERMINATE_CALL:
    case DEREGISTRATION:
    case GET_REGISTRATION_STATE:
    case ANSWER_CALL:
    case AUDIO_SMOD:
    case AUDIO_FDHF:
    case AUDIO_SKEY:
      len = createCommand(at_Command, buffer);
      break;
    case AUDIO_INIT:
    case INIT:
      break;
  }

  return len;
}
