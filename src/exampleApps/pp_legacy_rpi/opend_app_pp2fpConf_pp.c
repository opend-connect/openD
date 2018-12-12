/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_app_pp2fpConf_pp.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
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

static void appPrintHello( char * portname );
static void appPrintHelp( void );
static uint8_t app_audioVolumeUp( void );
static uint8_t app_audioVolumeDown( void );

/* openD function prototypes of application states. */
void app_state_init( void *arg );
void app_state_unregistered( void *arg );
void app_state_standby( void *arg );
void app_state_connected( void *arg );

const msManager_stateFct_t appStates[] =
{
  app_state_init,
  app_state_unregistered,
  app_state_standby,
  app_state_connected
};

msManager_ctxt_t appStateCtxt;
static uint8_t app_audioVolume = 3;


static void appPrintHello( char * portname ) {
  printf("\nUsage: %s [options] <serial device> \n", portname);
  printf("  <serial device> \t : path to device to be used, e.g. /dev/ttyUSB0\n");
  printf("Available options: \n");
  printf("  -d \t\t : Enable debug print of stack messages.\n");
  printf("  -h \t\t : Print this help.\n");
}

static void appPrintHelp(void)
{
  printf("---------------------------------------------------------------\n");
  printf("CVMCON HOSTAPP HELP: PcTools Keys:\n");
  printf("  'w'=Registration: KEY_REG (Long REG key)\n");
  printf("  'e'=De-Registration: KEY_DEREG (ExtraLong REG key)\n");
  printf("  'r'=Setup Call\n");
  printf("  't'=Release Call\n");
  printf("  'z'=Mute: KEY_MUTE\n");
  printf("  'u'=Unmute: KEY_UNMUTE\n");
  printf("  'i'=Volume up: KEY_VOLUME\n");
  printf("  'o'=Volume down: KEY_VOLUME\n");
  printf("\n");
  printf("EXTENDED CVMCON PRODTEST OPTIONS:\n");
  printf("  'y'=CvmCom prod test functions\n");
  printf("  'x'=KEY_DEFAULT (Long PON key)\n");
  printf("  'c'=Get StackInfo (Id, LinkDate, SwVerion, DectMode)\n");
  printf("           OTPInfo (Id, Modulation, Freq, Bandgap)\n");
  printf("  'v'=Get ImageCfg (Status on FP/PP Stack and COLA)\n");
  printf("  'b'=Toggle between DectModes\n");
  printf("  'n'=Toggle between FP/PP StackImage (and default eeprom)\n");
  printf("  'm'=Toggle between COLA Enabled/Disabled\n");
  printf("\n");
  printf("  'q' =quit\n");
  printf("---------------------------------------------------------------\n");
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
void app_state_init( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      /* Initialization state. */
      if( OPEND_STATUS_OK == openD_init() ) {
        msManager_changeState( &appStateCtxt, APP_STATE_UNREGISTERED );
      }
      break;

    default:
      break;
  }

  return;
}

void app_state_unregistered( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_subApiReq_t subApiReq;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      /* Check is the device already registered. */
      subApiReq.service = OPEND_SUBAPI_GET_REGISTRATION_STATE;
      openD_subApi_request( &subApiReq );
      break;

    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x77:
        /* Key 'w' KEY_REG */
          subApiReq.service = OPEND_SUBAPI_SUBSCRIBE;
          openD_subApi_request( &subApiReq );
          break;

        default:
          break;
      }
      break;

    case MESSAGE_PRIMITIVE_CFM:
      /* OpenD service confirmation. */
      switch( ((openD_subApiCfm_t*) message->param)->service ) {
        case OPEND_SUBAPI_GET_REGISTRATION_STATE:
          /* Get registration state. */
          if( OPEND_STATUS_OK == ((openD_subApiCfm_t*) message->param)->status ) {
            if( ((openD_subApiCfm_t*) message->param)->param.registrationState.isRegistered ) {
              msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
            } else {
              printf("Device not registered!\n");
            }
          }
          break;

        case OPEND_SUBAPI_SUBSCRIBE:
          if( OPEND_STATUS_OK == ((openD_subApiCfm_t*) message->param)->status ) {
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

void app_state_standby( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_subApiReq_t subApiReq;
  openD_callApiReq_t callApiReq;
  openD_mgmtApiReq_t mgmtApiReq;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x72:
        /* Key 'r' Setup call */
          callApiReq.service = OPEND_CALLAPI_SETUP;
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
            msManager_changeState( &appStateCtxt, APP_STATE_CONNECTED );
          } else {
            printf("Subscription failed!\n");
          }
          break;

        case OPEND_SUBAPI_SUBSCRIPTION_DELETE:
          if( OPEND_STATUS_OK == ((openD_callApiCfm_t*) message->param)->status ) {
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

void app_state_connected( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_callApiReq_t callApiReq;
  openD_audioApiReq_t audioApiReq;

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

  char key;
  char* portname = NULL;

  // check for args
  switch (argc)
  {
    case 3: // Two args: -d tty
      if (!strncmp(argv[1], "-d", strlen("-d"))) {
        /* Enable debug messages. */
        //TODO: When implementing HDLC!
        // enable_stack_msg_debug();
        portname = argv[2];
        printf("Using device %s...\n", portname);
      }
      break;
    case 2: // One arg
      if (!strncmp(argv[1], "-h", strlen("-h"))) {
        /* Print help. */
        appPrintHello(argv[0]);
        return 0;
      } else if (strncmp(argv[1], "-h", strlen("-h"))
            && strncmp(argv[1], "-d", strlen("-d"))) {
        // if no -d or -h handle as it is a tty arg
        portname = argv[1];
        printf("Using device %s...\n", portname);
      }
      break;
    case 1: // No arg
    default:
      printf("No argument given\n");
      /* Print help and exit */
      appPrintHello(argv[0]);
      return 0;

      break;
  }

  //TODO: When implementing HDLC!
  /* Initialization of the HDLC. */
  if(portname) {
    if (hdlc_Init(portname)) {
      printf("Error opening device %s\n", portname);
      return 1;
    }
  } else {
    /* Print help and exit. */
    appPrintHello(argv[0]);
    return 0;
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

    if( 0x61 == key ) { //Key 'a'
      appPrintHelp();
    }
    else if( 'q' != key ) {
      msManager_message_t appMessage;
      appMessage.primitive = MESSAGE_PRIMITIVE_USER;
      appMessage.param = (void*) &key;
      msManager_handleService( &appStateCtxt, &appMessage );
    }
  } while( key != 'q' );

  //TODO: When implementing HDLC!
  // opend_deInit()
  // TimerThreadRunning = 0;

  return 0;
}
