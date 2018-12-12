/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       transport.c
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

#include "iwu_serial.h"
#include "at_commands.h"
#include "transport.h"

#include "msManager.h"

/*!
 * Get the size of one element.
 */
#define ARRAY_SIZEOF(x)  (sizeof(x) / sizeof((x)[0]))

char callHandsetId;

/*!
 * States for the legacy iwu state machine.
 */
typedef enum {
  OPEND_STATE_INIT,
  OPEND_STATE_UNREGISTERED,
  OPEND_STATE_REGISTERED,
  OPEND_STATE_CONNECTED,
} opendIwuStates_t;

/* Structure to store outgoing AT commands. */
typedef struct{
  uint8_t dataBuffer[256];
  uint16_t dataWritten;
} atCmdBuffer_t;

/* Function pointer for registration finished callback. */
static iwu_registration_cllb registration_cfm;

/* Function pointer for call setup callback. */
static iwu_call_setup_cllb call_setup_cfm;

/* Function pointer for call terminated callback. */
static iwu_call_terminated_cllb call_terminated_cfm;

/* Function pointer for deregistration callback. */
static iwu_deregistration_cllb deregistration_cfm;

/* Function pointer for get registration state callback. */
static iwu_get_registration_state registration_state;

/* Save the last legacy state. */
tx_states legacy_last_state;

/* Save the last legacy RX state. */
rx_states_t legacy_RX_last_state = STARTUP;

/* Storage for outgoing AT commands. */
static atCmdBuffer_t atCmdBuffer;

/* IWU message manager object. */
msManager_ctxt_t iwu_msManager_ctxt;

/**
 * @brief   openD state init.
 *
 * @details Initialization state of the legacy iwu state machine.
 *
 * @param   param Pointer that holds data for current state.
 * @return  Always true.
 */
bool opend_state_init( void *param );

/**
 * @brief   openD state unregistered.
 *
 * @details Unregistered state of the legacy iwu state machine.
 *
 * @param   param Pointer that holds data for current state.
 * @return  Always true.
 */
bool opend_state_unregistered( void *param );

/**
 * @brief   openD state registered.
 *
 * @details Registered state of the legacy iwu state machine.
 *
 * @param   param Pointer that holds data for current state.
 * @return  Always true.
 */
bool opend_state_registered( void *param );

/**
 * @brief   openD state Connected.
 *
 * @details Connected state of the legacy iwu state machine.
 *
 * @param   param Pointer that holds data for current state.
 * @return  Always true.
 */
bool opend_state_connected( void *param );

void opend_iwu_sub_init(iwu_registration_cllb registration_cllb, iwu_deregistration_cllb deregistration_cllb, iwu_get_registration_state registration_state_cllb)
{
  registration_cfm = registration_cllb;
  deregistration_cfm = deregistration_cllb;
  registration_state = registration_state_cllb;
}

void opend_iwu_call_init(iwu_call_setup_cllb call_setup_cllb, iwu_call_terminated_cllb call_terminated_cllb)
{
  call_setup_cfm = call_setup_cllb;
  call_terminated_cfm = call_terminated_cllb;
}

/*!
 * Array to parse iwu enum state with associated function.
 */
const msManager_stateFct_t iwuStates[] =
{
  opend_state_init,
  opend_state_unregistered,
  opend_state_registered,
  opend_state_connected,
};

char *receiveDataAlrt[4];

void legacy_state_machine_callback( rx_states_t state, void *param )
{
  msManager_message_t iwuMessage;

  char** data = (char**) param;

  switch(state)
  {
    case ALRT:
      receiveDataAlrt[0] = data[0];
      receiveDataAlrt[1] = data[1];
      receiveDataAlrt[2] = data[2];
      receiveDataAlrt[3] = data[3];
      legacy_RX_last_state = ALRT;
      break;
    case OK:
      if(legacy_last_state == AUDIO_INIT)
      {
        atCmdBuffer.dataWritten = send_at_command(AUDIO_FDHF, atCmdBuffer.dataBuffer);
        iwu_serial_send(atCmdBuffer.dataBuffer, atCmdBuffer.dataWritten);
        legacy_last_state = AUDIO_FDHF;
      }
      iwuMessage.primitive = MESSAGE_PRIMITIVE_CFM;
      msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
      legacy_RX_last_state = OK;
      break;
    case IREG:
      /* Check the last RX state. */
      if(legacy_RX_last_state == OK)
      {
        /* Check the last state. */
        if(legacy_last_state == REGISTRATION_SEARCH_BASE || legacy_last_state == REGISTRATION_SEARCH_BASE_PIN)
        {
          char *receiveData[4];
          receiveData[0] = data[0];
          receiveData[1] = data[1];
          receiveData[2] = data[2];
          receiveData[3] = data[3];
          iwuMessage.param = receiveData[0];
          iwuMessage.primitive = MESSAGE_PRIMITIVE_IND;
          msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
        }
      }
      legacy_RX_last_state = IREG;
      break;
    case CSTS:
      receiveDataAlrt[0] = data[0];
      receiveDataAlrt[1] = data[1];
      receiveDataAlrt[2] = data[2];
      receiveDataAlrt[3] = data[3];
      /* Check the last RX state and the last state. */
      if( (legacy_RX_last_state == OK && legacy_last_state == CALL_SETUP) || (legacy_RX_last_state == OK && legacy_last_state == ANSWER_CALL) )
      {
        iwuMessage.primitive = MESSAGE_PRIMITIVE_IND;
        msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
      }
      legacy_RX_last_state = CSTS;
      break;
    case DREG:
      /* Check the last RX state and the last state. */
      if(legacy_RX_last_state == OK && legacy_last_state == DEREGISTRATION)
      {
        char *receiveData[4];
        receiveData[0] = data[0];
        receiveData[1] = data[1];
        receiveData[2] = data[2];
        receiveData[3] = data[3];
        iwuMessage.param = receiveData[1];
        iwuMessage.primitive = MESSAGE_PRIMITIVE_IND;
        msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
      }
      legacy_RX_last_state = DREG;
      break;
    case ISUB:
      legacy_RX_last_state = ISUB;
      char *receiveData[4];
      receiveData[0] = data[0];
      receiveData[1] = data[1];
      receiveData[2] = data[2];
      receiveData[3] = data[3];
      iwuMessage.param = receiveData[1];
      iwuMessage.primitive = MESSAGE_PRIMITIVE_CFM;
      msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
      break;
    case CEND:
      legacy_RX_last_state = CEND;
      iwuMessage.primitive = MESSAGE_PRIMITIVE_IND;
      msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
      break;
    case STARTUP:
    default:
      break;
  }
}

bool opend_state_init( void *param )
{
  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      iwu_serial_init(&receive_at_command);
      init_at_commands(legacy_state_machine_callback);
      msManager_changeState( &iwu_msManager_ctxt, OPEND_STATE_UNREGISTERED );
      break;
    default:
      break;
  }

  return true;
}

bool opend_state_unregistered( void *param )
{
  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      break;
    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x72:
          /* Key 'r' KEY_REG */
          atCmdBuffer.dataWritten = send_at_command(REGISTRATION_SEARCH_BASE, atCmdBuffer.dataBuffer);
          iwu_serial_send(atCmdBuffer.dataBuffer, atCmdBuffer.dataWritten);
          legacy_last_state = REGISTRATION_SEARCH_BASE;
          break;
        case 0x67:
          /* Key 'g' KEY_GET_REG */
          atCmdBuffer.dataWritten = send_at_command(GET_REGISTRATION_STATE, atCmdBuffer.dataBuffer);
          iwu_serial_send(atCmdBuffer.dataBuffer, atCmdBuffer.dataWritten);
          legacy_last_state = GET_REGISTRATION_STATE;
          break;
        default:
          break;
      }
      break;
    case MESSAGE_PRIMITIVE_CFM:
      if(legacy_last_state == GET_REGISTRATION_STATE && legacy_RX_last_state == ISUB)
      {
        /* Check the success byte and change state if 1. */
        if(memcmp((message->param+REGISTRATION_CFM_SUCCESSBYTE_ADDRESS), "1", 1) == 0)
        {
          /* Get registration state IWU succesfully! */
          msManager_changeState( &iwu_msManager_ctxt, OPEND_STATE_REGISTERED );
        }
        if(!registration_state){
          return true;
        }
        registration_state(message->param);
      }
      break;
    case MESSAGE_PRIMITIVE_IND:
      /* Check the last state. */
      if(legacy_last_state == REGISTRATION_SEARCH_BASE)
      {
        atCmdBuffer.dataWritten = send_at_command(REGISTRATION_SEARCH_BASE_PIN, atCmdBuffer.dataBuffer);
        iwu_serial_send(atCmdBuffer.dataBuffer, atCmdBuffer.dataWritten);
        legacy_last_state = REGISTRATION_SEARCH_BASE_PIN;
      }
      if(legacy_last_state == REGISTRATION_SEARCH_BASE_PIN)
      {
        uint8_t *success = (uint8_t*) (message->param+REGISTRATION_CFM_SUCCESSBYTE_ADDRESS);
        /* Check the success byte and change state if 1. */
        if(memcmp(success, "1", 1) == 0)
        {
          /* Registration IWU finished! */
          msManager_changeState( &iwu_msManager_ctxt, OPEND_STATE_REGISTERED );
        }
        if(!registration_cfm){
          return true;
        }
        registration_cfm(message->param);
      }
      break;
    default:
      break;
  }

  return true;
}

bool opend_state_registered( void *param )
{
  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      break;
    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x65:
          /* Key 'e' KEY_DEREG */
          atCmdBuffer.dataWritten = send_at_command(DEREGISTRATION, atCmdBuffer.dataBuffer);
          iwu_serial_send(atCmdBuffer.dataBuffer, atCmdBuffer.dataWritten);
          legacy_last_state = DEREGISTRATION;
          break;
        case 0x72:
          if(legacy_RX_last_state == ALRT)
          {
            /* Key 'r' ANSWER_CALL */
            atCmdBuffer.dataWritten = send_at_command(ANSWER_CALL, atCmdBuffer.dataBuffer);
            iwu_serial_send(atCmdBuffer.dataBuffer, atCmdBuffer.dataWritten);
            legacy_last_state = ANSWER_CALL;
          }
          else
          {
            /* Key 'w' Setup call */
            atCmdBuffer.dataWritten = send_at_command(CALL_SETUP, atCmdBuffer.dataBuffer);
            iwu_serial_send(atCmdBuffer.dataBuffer, atCmdBuffer.dataWritten);
            legacy_last_state = CALL_SETUP;
          }
          break;
        default:
          break;
      }
      break;
    case MESSAGE_PRIMITIVE_CFM:
      break;
    case MESSAGE_PRIMITIVE_IND:
      /* Check the last state. */
      if(legacy_last_state == CALL_SETUP)
      {
        /* Call setup IWU succesfully! */
        msManager_changeState( &iwu_msManager_ctxt, OPEND_STATE_CONNECTED );
        if(!call_setup_cfm){
          return true;
        }
        call_setup_cfm();
      }
      if(legacy_last_state == DEREGISTRATION)
      {
        /* Check the success byte and change state if 1. */
        if(memcmp(message->param, "01", 2) == 0)
        {
          /* Deregistration IWU finished! */
          msManager_changeState( &iwu_msManager_ctxt, OPEND_STATE_UNREGISTERED );
        }
        if(!deregistration_cfm){
          return true;
        }
        deregistration_cfm(message->param);
      }
      if(legacy_last_state == ANSWER_CALL)
      {
        /* Key 'w' ANSWER_CALL */
        /* Call answer IWU succesfully! */
        msManager_changeState( &iwu_msManager_ctxt, OPEND_STATE_CONNECTED );
        if(!call_setup_cfm){
          return true;
        }
        call_setup_cfm();
      }
      break;
    default:
      break;
  }

  return true;
}

bool opend_state_connected( void *param )
{
  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      opend_iwu_audio_init();
      break;
    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x77:
          /* Key 'w' Release call */
          atCmdBuffer.dataWritten = send_at_command(TERMINATE_CALL, atCmdBuffer.dataBuffer);
          iwu_serial_send(atCmdBuffer.dataBuffer, atCmdBuffer.dataWritten);
          legacy_last_state = TERMINATE_CALL;
          break;
        default:
          break;
      }
      break;
    case MESSAGE_PRIMITIVE_CFM:
      /* Check the last state. */
      if(legacy_last_state == TERMINATE_CALL)
      {
        /* Call IWU terminated! */
        msManager_changeState( &iwu_msManager_ctxt, OPEND_STATE_REGISTERED );
        if(!call_terminated_cfm){
          return true;
        }
        call_terminated_cfm();
      }
      break;
    case MESSAGE_PRIMITIVE_IND:
      /* Check the last state. */
      if(legacy_RX_last_state == CEND)
      {
        /* Call IWU terminated! */
        msManager_changeState( &iwu_msManager_ctxt, OPEND_STATE_REGISTERED );
        if(!call_terminated_cfm){
          return true;
        }
        call_terminated_cfm();
      }
      break;
    default:
      break;
  }

  return true;
}

void opend_iwu_init()
{
  /* Initialization of message state manager. */
  msManager_init( &iwu_msManager_ctxt, iwuStates, ARRAY_SIZEOF(iwuStates) );

  /* Change to the initialization state. */
  msManager_changeState( &iwu_msManager_ctxt, OPEND_STATE_INIT );
}

void opend_iwu_audio_init()
{
  atCmdBuffer.dataWritten = send_at_command(AUDIO_SMOD, atCmdBuffer.dataBuffer);
  iwu_serial_send(atCmdBuffer.dataBuffer, atCmdBuffer.dataWritten);
  legacy_last_state = AUDIO_INIT;
}

void opend_iwu_register_request()
{
  msManager_message_t iwuMessage;
  iwuMessage.primitive = MESSAGE_PRIMITIVE_USER;
  iwuMessage.param = (void*) "r";
  msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
}

void opend_iwu_get_registration_state()
{
  msManager_message_t iwuMessage;
  iwuMessage.primitive = MESSAGE_PRIMITIVE_USER;
  iwuMessage.param = (void*) "g";
  msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
}

void opend_iwu_call_request(char setupCallHandsetId)
{
  callHandsetId = setupCallHandsetId;

  msManager_message_t iwuMessage;
  iwuMessage.primitive = MESSAGE_PRIMITIVE_USER;
  iwuMessage.param = (void*) "r";
  msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
}

void opend_iwu_release_call()
{
  msManager_message_t iwuMessage;
  iwuMessage.primitive = MESSAGE_PRIMITIVE_USER;
  iwuMessage.param = (void*) "w";
  msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
}

void opend_iwu_deregister_request()
{
  msManager_message_t iwuMessage;
  iwuMessage.primitive = MESSAGE_PRIMITIVE_USER;
  iwuMessage.param = (void*) "e";
  msManager_handleService( &iwu_msManager_ctxt, &iwuMessage );
}
