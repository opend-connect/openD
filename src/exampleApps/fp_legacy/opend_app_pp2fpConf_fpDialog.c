/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_app_pp2fpConf_fpDialog.c
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

static void openD_audioApiCfm_callback( openD_audioApiCfm_t *aConfirm ) {

  if( !aConfirm ) {
    return;
  }
    switch( aConfirm->service ) {

      case OPEND_AUDIOAPI_SET_VOLUME:
        if( OPEND_STATUS_OK == aConfirm->status ) {
          printf("Set audio successfull!\n");
        } else {
          printf("Set audio failed!\n");
        }
        break;

      case OPEND_AUDIOAPI_SET_MUTE:
        if( OPEND_STATUS_OK == aConfirm->status ) {
          printf("Set mute/unmute successfull!\n");
        } else {
          printf("Set mute/unmute failed!\n");
        }
        break;

    default:
      break;
  }
  return;
}

static void openD_audioApiInd_callback( openD_audioApiInd_t *aIndication ) {

  if( !aIndication ) {
    return;
  }
    switch( aIndication->service ) {

    default:
      break;
  }
  return;
}

static void openD_mgmtApiCfm_callback( openD_mgmtApiCfm_t *mConfirm ) {

  if( !mConfirm ) {
    return;
  }
    switch( mConfirm->service ) {
      case OPEND_MGMTAPI_INIT:
        if( OPEND_STATUS_OK == mConfirm->status ) {
          printf("Module init initialized!\n");
          msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
        } else {
          printf("Module init failed!\n");
        }
        break;

    default:
      break;
  }
  return;
}

static void openD_mgmtApiInd_callback( openD_mgmtApiInd_t *mIndication ) {

  if( !mIndication ) {
    return;
  }
    switch( mIndication->service ) {

    default:
      break;
  }
  return;
}

static void openD_callApiCfm_callback( openD_callApiCfm_t *cConfirm ) {

  if( !cConfirm ) {
    return;
  }

  switch( cConfirm->service ) {
    case OPEND_CALLAPI_SETUP:
      if( OPEND_STATUS_OK == cConfirm->status ) {
        /* Call setup was successfull. */
        printf("Call setup successfull!\n");
        // system("/home/dlg_ule/pactl-load-module.sh");
        msManager_changeState( &appStateCtxt, APP_STATE_CONNECTED );
      } else {
        printf("Call setup failed!\n");
      }
      break;

    case OPEND_CALLAPI_RELEASE:
      if( OPEND_STATUS_OK == cConfirm->status ) {
        /* Release call was successfull. */
        printf("Release call successfull!\n");
        msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
      } else {
        printf("Release call failed!\n");
      }
      break;

    default:
      break;
  }
  return;
}

static void openD_callApiInd_callback( openD_callApiInd_t *cIndication ) {

  if( !cIndication ) {
    return;
  }

  switch( cIndication->service ) {
    case OPEND_CALLAPI_SETUP:
      /* Incoming call setup was successfull. */
      printf("Incoming call setup was successfull!\n");
      msManager_changeState( &appStateCtxt, APP_STATE_CONNECTED );
      break;

    case OPEND_CALLAPI_RELEASE:
      /* Call release successfull. */
      printf("Call release was successfull!\n");
      msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
      break;

    case OPEND_CALLAPI_CONNECTION_STATUS_RINGING:
      /* Ringing. */
      printf("Connection status: ringing!\n");
      break;

    default:
      break;
  }
  return;
}

static void openD_subApiCfm_callback( openD_subApiCfm_t *sConfirm ) {

  if( !sConfirm ) {
    return;
  }

  switch( sConfirm->service ) {
    case OPEND_SUBAPI_GET_REGISTRATION_STATE:
      /* Get registration state. */
      if( OPEND_STATUS_OK == sConfirm->status ) {
        if( sConfirm->param.registrationState.isRegistered ) {
          printf("Get subscription state successfull!\n");
          msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
        } else {
          printf("Device not registered!\n");
        }
      }
      break;

    case OPEND_SUBAPI_SUBSCRIBE:
      if( OPEND_STATUS_OK == sConfirm->status ) {
        printf("Subscription successfull!\n");
        msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
      } else {
        printf("Subscription failed!\n");
      }
      break;

    case OPEND_SUBAPI_SUBSCRIBE_ENABLE:
      if( OPEND_STATUS_OK == sConfirm->status ) {
        printf("Subscription enabled!\n");
      } else {
        printf("Subscription enable failed!\n");
      }
      break;

    case OPEND_SUBAPI_SUBSCRIPTION_DELETE:
      if( OPEND_STATUS_OK == sConfirm->status ) {
        /* Subscription delete was successfull. */
        printf("Subscription delete successfull!\n");
        msManager_changeState( &appStateCtxt, APP_STATE_UNREGISTERED );
      } else {
        printf("Subscription delete failed!\n");
      }
      break;

    default:
      break;
  }
  return;
}

static void openD_subApiInd_callback( openD_subApiInd_t *sIndication ) {

  if( !sIndication ) {
    return;
  }

  switch( sIndication->service ) {
    case OPEND_SUBAPI_SUBSCRIBE:
        printf("Subscription successfull!\n");
        msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
      break;

    default:
      break;
  }
  return;
}


/* openD application states. */
bool app_state_init( void *param ) {

  openD_mgmtApiReq_t mgmtApiReq;
  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      printf("app_state_init\n");

      mgmtApiReq.service = OPEND_MGMTAPI_INIT;
      if( OPEND_STATUS_OK == openD_mgmtApi_request( &mgmtApiReq ) ) {
        /* Initialization state. */
        msManager_changeState( &appStateCtxt, APP_STATE_UNREGISTERED );
      }
      break;

    default:
      break;
  }

  return true;
}

bool app_state_unregistered( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_subApiReq_t subApiReq;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      printf("app_state_unregistered\n");
      break;

    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x77:
          /* Key 'w' Subscribe */
          subApiReq.service = OPEND_SUBAPI_SUBSCRIBE_ENABLE;
          openD_subApi_request( &subApiReq );
          break;

        default:
          break;
      }
      break;

    default:
      break;
  }

  return true;
}

bool app_state_standby( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_subApiReq_t subApiReq;
  openD_callApiReq_t callApiReq;
  openD_mgmtApiReq_t mgmtApiReq;
  char handsetId;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      printf("app_state_standby\n");
      break;

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

        case 0x77:
          /* Key 'w' Subscribe */
          subApiReq.service = OPEND_SUBAPI_SUBSCRIBE_ENABLE;
          openD_subApi_request( &subApiReq );
          break;

        case 0x65:
          /* Key 'e' Subscription delete */
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

    default:
      break;
  }

  return true;
}

bool app_state_connected( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_callApiReq_t callApiReq;
  openD_audioApiReq_t audioApiReq;
  char callId;

  printf("app_state_connected\n");

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
          break;

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

    default:
      break;
  }

  return true;
}


int main(int argc, char* argv[]) {

  char key;
  char* portname = NULL;

  /* Check arguments. */
  switch (argc)
  {
    case 3: /* 2 args: -d <portname> */
      if (!strncmp(argv[1], "-d", strlen("-d"))) {
        portname = argv[2];
      }
      break;
    case 2: /* 1 arg: <portname> */
      portname = argv[1];
      break;
    case 1: /* No argument. */
    default:
      printf("No argument given!\n");
      return 0;
      break;
  }

  if( OPEND_STATUS_OK != openD_init( portname ) ) {
    printf("Error occurred!\n");
    return 0;
  }

  /* Initialization of the openD audio API. */
  openD_audioApiPrimitives_t aPrimitives;
  aPrimitives.openD_audioApiCfm = &openD_audioApiCfm_callback;
  aPrimitives.openD_audioApiInd = &openD_audioApiInd_callback;
  openD_audioApi_init( &aPrimitives );

  /* Initialization of the openD call API. */
  openD_callApiPrimitives_t cPrimitives;
  cPrimitives.openD_callApiCfm = &openD_callApiCfm_callback;
  cPrimitives.openD_callApiInd = &openD_callApiInd_callback;
  openD_callApi_init( &cPrimitives );

  /* Initialization of the openD mgmt API. */
  openD_mgmtApiPrimitives_t mPrimitives;
  mPrimitives.openD_mgmtApiCfm = &openD_mgmtApiCfm_callback;
  mPrimitives.openD_mgmtApiInd = &openD_mgmtApiInd_callback;
  openD_mgmtApi_init( &mPrimitives );

  /* Initialization of the openD sub API. */
  openD_subApiPrimitives_t sPrimitives;
  sPrimitives.openD_subApiCfm = &openD_subApiCfm_callback;
  sPrimitives.openD_subApiInd = &openD_subApiInd_callback;
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
