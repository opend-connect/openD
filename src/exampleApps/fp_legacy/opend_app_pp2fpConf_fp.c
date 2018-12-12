/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_app_pp2fpConf_fp.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#include "msManager.h"

#include "opend_api.h"
#include "opend_sub_api.h"
#include "opend_mgmt_api.h"
#include "opend_audio_api.h"
#include "opend_call_api.h"

#include <termios.h>

#define ARRAY_SIZEOF(x)  (sizeof(x) / sizeof((x)[0]))

typedef enum {
  APP_STATE_INIT,
  APP_STATE_UNREGISTERED,
  APP_STATE_STANDBY,
  APP_STATE_CONNECTED,
} opendAppStates_t;

static void appPrintHelp( void );
static uint8_t app_audioVolumeUp( void );
static uint8_t app_audioVolumeDown( void );

/* openD function prototypes of application states. */
bool app_state_init( void *arg );
bool app_state_unregistered( void *arg );
bool app_state_standby( void *arg );
bool app_state_connected( void *arg );

const msManager_stateFct_t appStates[] =
{
  app_state_init,
  app_state_unregistered,
  app_state_standby,
  app_state_connected
};

msManager_ctxt_t appStateCtxt;

static uint8_t app_audioVolume = 3;

/**
 * Clean the stdin buffer to handle a new user input.
 */
static void clean_stdin_buffer(void)
{
  int buffer;
  do {
    buffer = getchar();
  } while (buffer != '\n' && buffer != EOF);
}

static void appPrintHelp(void)
{
  printf( "************************************************\n" );
  printf( "    STACKFORCE openD FP Demo Application 1.0    \n" );
  printf( "************************************************\n" );
  printf( "\n" );
  printf( "w : Open registration\n" );
  printf( "e : Close registration\n" );
  printf( "\n" );
  printf( "m : Mute\n" );
  printf( "u : Unmute\n" );
  printf( "r : Setup Call\n");
  printf( "t : Release Call\n");
  printf( "z : Mute\n");
  printf( "u : Unmute\n");
  printf( "i : Volume up\n");
  printf( "o : Volume down\n");
  printf( "\n" );
  printf( "Select an Option (Press q to close the demo app):\n" );
  printf("\n");
}

static uint8_t app_audioVolumeUp( void ) {
  if( 0x05 > app_audioVolume ) {
    app_audioVolume++;
  }
  return app_audioVolume;
}

static uint8_t app_audioVolumeDown( void ) {
  if( 0x00 < app_audioVolume ) {
    app_audioVolume--;
  }
  return app_audioVolume;
}

static void openD_callApiCfm_callback( openD_callApiCfm_t *cConfirm ) {
  /* Set primitive. */
  msManager_message_t appMessage;
  appMessage.primitive = MESSAGE_PRIMITIVE_CFM;
  appMessage.param = (void*) cConfirm;

  /* Handle call confirmation. */
  msManager_handleService( &appStateCtxt, &appMessage );

  return;
}

static void openD_mgmtApiCfm_callback( openD_mgmtApiCfm_t *mConfirm ) {
  /* Set primitive. */
  msManager_message_t appMessage;
  appMessage.primitive = MESSAGE_PRIMITIVE_CFM;
  appMessage.param = (void*) mConfirm;

  /* Handle call confirmation. */
  msManager_handleService( &appStateCtxt, &appMessage );

  return;
}

static void openD_subApiCfm_callback( openD_subApiCfm_t *sConfirm ) {
  /* Set primitive. */
  msManager_message_t appMessage;
  appMessage.primitive = MESSAGE_PRIMITIVE_CFM;
  appMessage.param = (void*) sConfirm;

  /* Handle call confirmation. */
  msManager_handleService( &appStateCtxt, &appMessage );

  return;
}

/* openD application states. */
bool app_state_init( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      /* Initialization state. */
      msManager_changeState( &appStateCtxt, APP_STATE_UNREGISTERED );
      break;

    default:
      break;
  }

  return;
}

bool app_state_unregistered( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_subApiReq_t subApiReq;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      break;

    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x77:
          /* Key 'w' KEY_REG */
          subApiReq.service = OPEND_SUBAPI_SUBSCRIBE_ENABLE;
          openD_subApi_request( &subApiReq );
          break;

        default:
          break;
      }
      break;

    case MESSAGE_PRIMITIVE_CFM:
      /* OpenD service confirmation. */
      switch( ((openD_subApiCfm_t*) message->param)->service ) {

        case OPEND_SUBAPI_SUBSCRIBE:
          if( OPEND_STATUS_OK == ((openD_subApiCfm_t*) message->param)->status ) {
            printf("Registration APP finished!\n");
            msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
          } else {
            printf("Subscription failed!\n");
          }
          break;

        default:
        break;
      }
      break;

    default:
      break;
  }

  return;
}

bool app_state_standby( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_subApiReq_t subApiReq;
  openD_callApiReq_t callApiReq;
  openD_mgmtApiReq_t mgmtApiReq;
  char handsetId;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x72:
          /* Key 'r' Setup call */
          callApiReq.service = OPEND_CALLAPI_SETUP;
          clean_stdin_buffer();
          handsetId = getchar();
          clean_stdin_buffer();
          callApiReq.param.setup.pmid[0] = handsetId;
          openD_callApi_request( &callApiReq );
          break;

        case 0x65:
          /* Key 'e' KEY_DEREG */
          subApiReq.service = OPEND_SUBAPI_SUBSCRIPTION_DELETE;
          openD_subApi_request( &subApiReq );
          break;

        case 0x78:
          /* Key 'x' KEY_DEFAULT */
          mgmtApiReq.service = OPEND_MGMTAPI_FORCE_NVM_DEFAULT;
          openD_mgmtApi_request( &mgmtApiReq );
          break;

        default:
          break;
      }
      break;

    case MESSAGE_PRIMITIVE_CFM:
      /* OpenD service confirmation. */
      switch( ((openD_subApiCfm_t*) message->param)->service ) {
        case OPEND_CALLAPI_SETUP:
          if( OPEND_STATUS_OK == ((openD_callApiCfm_t*) message->param)->status ) {
            printf("Call setup APP succesfully!\n");
            system("/home/dlg_ule/pactl-load-module.sh");
            msManager_changeState( &appStateCtxt, APP_STATE_CONNECTED );
          } else {
            printf("Subscription failed!\n");
          }
          break;

        case OPEND_SUBAPI_SUBSCRIPTION_DELETE:
          if( OPEND_STATUS_OK == ((openD_callApiCfm_t*) message->param)->status ) {
            printf("Deregistration APP finished!\n");
            msManager_changeState( &appStateCtxt, APP_STATE_UNREGISTERED );
          } else {
            printf("Subscription delete failed!\n");
          }
          break;

        default:
          break;
      }
      break;

    default:
      break;
  }

  return;
}

bool app_state_connected( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_callApiReq_t callApiReq;
  openD_audioApiReq_t audioApiReq;
  char callId;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      /* Set the default audio volume. */
      audioApiReq.service = OPEND_AUDIOAPI_SET_VOLUME;
      audioApiReq.param.setVolume.level = app_audioVolume;
      openD_audioApi_request( &audioApiReq );
      break;

    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x74:
          /* Key 't' Release call */
          callApiReq.service = OPEND_CALLAPI_RELEASE;
          clean_stdin_buffer();
          callId = getchar();
          clean_stdin_buffer();
          callApiReq.param.setup.pmid[1] = callId;
          openD_callApi_request( &callApiReq );

        case 0x69:
          /* Key 'i' Volume up */
          audioApiReq.service = OPEND_AUDIOAPI_SET_VOLUME;
          audioApiReq.param.setVolume.level = app_audioVolumeUp();
          openD_audioApi_request( &audioApiReq );
          break;

        case 0x6F:
          /* Key 'o' Volume down */
          audioApiReq.service = OPEND_AUDIOAPI_SET_VOLUME;
          audioApiReq.param.setVolume.level = app_audioVolumeDown();
          openD_audioApi_request( &audioApiReq );
          break;

        case 0x7A:
          /* Key 'z' Mute */
          audioApiReq.service = OPEND_AUDIOAPI_SET_MUTE;
          audioApiReq.param.setMute.enable = true;
          openD_audioApi_request( &audioApiReq );
          break;

        case 0x75:
          /* Key 'u' Unmute */
          audioApiReq.service = OPEND_AUDIOAPI_SET_MUTE;
          audioApiReq.param.setMute.enable = false;
          openD_audioApi_request( &audioApiReq );
          break;

        default:
          break;
      }
      break;

    case MESSAGE_PRIMITIVE_CFM:
      /* OpenD service confirmation. */
      switch( ((openD_subApiCfm_t*) message->param)->service ) {
        case OPEND_CALLAPI_RELEASE:
          if( OPEND_STATUS_OK == ((openD_callApiCfm_t*) message->param)->status ) {
            printf("Call APP released!\n");
            msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
          } else {
            printf("Release failed!\n");
          }
          break;

        default:
          break;
      }

    default:
      break;
  }

  return;
}


int main(int argc, char* argv[]) {

  /* Variable to store the user input. */
  char key;

  if( OPEND_STATUS_OK == openD_init( NULL ) ) {

  }

  /* Initialization of the openD call API. */
  openD_callApiPrimitives_t cPrimitives;
  cPrimitives.openD_callApiCfm = &openD_callApiCfm_callback;
  openD_callApi_init( &cPrimitives );

  /* Initialization of the openD mgmt API. */
  openD_mgmtApiPrimitives_t mPrimitives;
  mPrimitives.openD_mgmtApiCfm = &openD_mgmtApiCfm_callback;
  openD_mgmtApi_init( &mPrimitives );

  /* Initialization of the openD sub API. */
  openD_subApiPrimitives_t sPrimitives;
  sPrimitives.openD_subApiCfm = &openD_subApiCfm_callback;
  openD_subApi_init( &sPrimitives );

  /* Initialization of message state manager. */
  msManager_init( &appStateCtxt, appStates, ARRAY_SIZEOF(appStates) );

  /* Change to the initialization state. */
  msManager_changeState( &appStateCtxt, APP_STATE_INIT );

  do {
    key = getchar();
    /* Key 'a' */
    if( 0x61 == key ) {
      appPrintHelp();
    }
    else if( 'q' != key ) {
      msManager_message_t appMessage;
      appMessage.primitive = MESSAGE_PRIMITIVE_USER;
      appMessage.param = (void*) &key;
      msManager_handleService( &appStateCtxt, &appMessage );
    }
  } while( key != 'q' );

  return 0;
}
