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
#include <iostream>

extern "C" {
#include "msManager.h"
#include "opend_api.h"
#include "opend_sub_api.h"
#include "opend_mgmt_api.h"
#include "opend_audio_api.h"
#include "opend_call_api.h"
#include <termios.h>
#include "udp_server.h"
}

#include <../../json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;
/* json library object. */
json j;


using namespace std;

/* Save the json protocol param2 to setup/release a call. */
string handsetOrCallId;
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
          j["version"] = "1.0.0";
          j["module"] = "legacy";
          j["primitive"] = "confirmation";
          j["service"] = "setAudio";
          j["status"] = "OK";
          j["param1"] = "0";
          j["param2"] = "0";
          j["param3"] = "0";
          size_t len = strlen((j.dump()).c_str())+1;
          udp_send((j.dump()).c_str(), len);
        } else {
          j["version"] = "1.0.0";
          j["module"] = "legacy";
          j["primitive"] = "confirmation";
          j["service"] = "setAudio";
          j["status"] = "ERR";
          j["param1"] = "0";
          j["param2"] = "0";
          j["param3"] = "0";
          size_t len = strlen((j.dump()).c_str())+1;
          udp_send((j.dump()).c_str(), len);
        }
        break;

      case OPEND_AUDIOAPI_SET_MUTE:
        if( OPEND_STATUS_OK == aConfirm->status ) {
          j["version"] = "1.0.0";
          j["module"] = "legacy";
          j["primitive"] = "confirmation";
          j["service"] = "muteUnmute";
          j["status"] = "OK";
          j["param1"] = "0";
          j["param2"] = "0";
          j["param3"] = "0";
          size_t len = strlen((j.dump()).c_str())+1;
          udp_send((j.dump()).c_str(), len);
        } else {
          j["version"] = "1.0.0";
          j["module"] = "legacy";
          j["primitive"] = "confirmation";
          j["service"] = "muteUnmute";
          j["status"] = "ERR";
          j["param1"] = "0";
          j["param2"] = "0";
          j["param3"] = "0";
          size_t len = strlen((j.dump()).c_str())+1;
          udp_send((j.dump()).c_str(), len);
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
  /* Set primitive. */
  msManager_message_t appMessage;
  appMessage.primitive = MESSAGE_PRIMITIVE_CFM;
  appMessage.param = (void*) cConfirm;

  switch( ((openD_subApiCfm_t*) appMessage.param)->service ) {

    case OPEND_CALLAPI_SETUP:
      if( OPEND_STATUS_OK == ((openD_callApiCfm_t*) appMessage.param)->status ) {
        printf("Call setup APP succesfully!\n");
        j["version"] = "1.0.0";
        j["module"] = "legacy";
        j["primitive"] = "confirmation";
        j["service"] = "setupCall";
        j["status"] = "OK";
        j["param1"] = std::to_string( static_cast<int>( ((openD_callApiCfm_t*) appMessage.param)->param.setup.pmid[0]) );
        j["param2"] = "0";
        j["param3"] = "0";
        size_t len = strlen((j.dump()).c_str())+1;
        udp_send((j.dump()).c_str(), len);
        msManager_changeState( &appStateCtxt, APP_STATE_CONNECTED );
      } else {
        printf("Subscription failed!\n");
      }
      break;
  }
}

static void openD_callApiInd_callback( openD_callApiInd_t *cIndication ) {

  if( !cIndication ) {
    return;
  }

  switch( cIndication->service ) {
    case OPEND_CALLAPI_CONNECTION_STATUS_RINGING:
      /* Ringing. */
      printf("Connection status: ringing!\n");
      break;

    case OPEND_CALLAPI_RELEASE:
      {
        printf("Call APP released!\n");
        j["version"] = "1.0.0";
        j["module"] = "legacy";
        j["primitive"] = "indication";
        j["service"] = "releaseCall";
        j["status"] = "OK";
        j["param1"] = "0";
        j["param2"] = "0";
        j["param3"] = "0";
        size_t len = strlen((j.dump()).c_str())+1;
        udp_send((j.dump()).c_str(), len);
        msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
      }
      break;

    case OPEND_CALLAPI_SETUP:
      {
        printf("Call setup APP succesfully!\n");
        j["version"] = "1.0.0";
        j["module"] = "legacy";
        j["primitive"] = "indication";
        j["service"] = "setupCall";
        j["status"] = "OK";
        j["param1"] = std::to_string( static_cast<int>( cIndication->param.setup.pmid[0]) );
        j["param2"] = "0";
        j["param3"] = "0";
        size_t len = strlen((j.dump()).c_str())+1;
        udp_send((j.dump()).c_str(), len);
        msManager_changeState( &appStateCtxt, APP_STATE_CONNECTED );
      }
      break;

    default:
      break;
  }
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

static void openD_subApiInd_callback( openD_subApiInd_t *sIndication ) {

  size_t len;

  if( !sIndication ) {
    return;
  }

  switch( sIndication->service ) {
    case OPEND_SUBAPI_SUBSCRIBE:
      printf("Registration APP finished!\n");
      j["version"] = "1.0.0";
      j["module"] = "legacy";
      j["primitive"] = "confirmation";
      j["service"] = "openRegistrationWindow";
      j["status"] = "OK";
      j["param1"] = std::to_string( static_cast<int>( sIndication->param.subscribe.pmid[0] ) );
      j["param2"] = "0";
      j["param3"] = "0";
      len = strlen((j.dump()).c_str())+1;
      udp_send((j.dump()).c_str(), len);
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
            j["version"] = "1.0.0";
            j["module"] = "legacy";
            j["primitive"] = "confirmation";
            j["service"] = "openRegistrationWindow";
            j["status"] = "OK";
            j["param1"] = std::to_string( static_cast<int>( ((openD_subApiCfm_t*) message->param)->param.handsetId.id) );
            j["param2"] = "0";
            j["param3"] = "0";
            size_t len = strlen((j.dump()).c_str())+1;
            udp_send((j.dump()).c_str(), len);
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

  return true;
}

bool app_state_standby( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;
  openD_subApiReq_t subApiReq;
  openD_callApiReq_t callApiReq;
  openD_mgmtApiReq_t mgmtApiReq;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x77:
          /* Key 'w' KEY_REG */
          subApiReq.service = OPEND_SUBAPI_SUBSCRIBE_ENABLE;
          openD_subApi_request( &subApiReq );
          break;

        case 0x72:
          /* Key 'r' Setup call */
          callApiReq.service = OPEND_CALLAPI_SETUP;
          memcpy(callApiReq.param.setup.pmid, handsetOrCallId.c_str(), (handsetOrCallId.size() + 1));
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

        case OPEND_SUBAPI_SUBSCRIBE:
          if( OPEND_STATUS_OK == ((openD_subApiCfm_t*) message->param)->status ) {
            printf("Registration APP finished!\n");
            j["version"] = "1.0.0";
            j["module"] = "legacy";
            j["primitive"] = "confirmation";
            j["service"] = "openRegistrationWindow";
            j["status"] = "OK";
            j["param1"] = std::to_string( static_cast<int>( ((openD_subApiCfm_t*) message->param)->param.handsetId.id) );
            j["param2"] = "0";
            j["param3"] = "0";
            size_t len = strlen((j.dump()).c_str())+1;
            udp_send((j.dump()).c_str(), len);
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

  return true;
}

bool app_state_connected( void *param ) {

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
          memcpy(&callApiReq.param.setup.pmid[1], handsetOrCallId.c_str(), (handsetOrCallId.size() + 1));
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
            j["version"] = "1.0.0";
            j["module"] = "legacy";
            j["primitive"] = "confirmation";
            j["service"] = "releaseCall";
            j["status"] = "OK";
            j["param1"] = "0";
            j["param2"] = "0";
            j["param3"] = "0";
            size_t len = strlen((j.dump()).c_str())+1;
            udp_send((j.dump()).c_str(), len);
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

  return true;
}


int main(int argc, char* argv[]) {

  /* Variable to store the user input. */
  char *portname = NULL;
  json j;
  udp_init();

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

  bool executeApp = true;

  while(executeApp)
  {
    char buffer[1024];
    udp_receive(buffer);
    printf("%s\n", (void*) buffer);
    j = json::parse(buffer);
    string version = j.at("version").get<std::string>();
    string module = j.at("module").get<std::string>();
    string primitive = j.at("primitive").get<std::string>();
    string service = j.at("service").get<std::string>();
    string status = j.at("status").get<std::string>();
    string key = j.at("param1").get<std::string>();
    handsetOrCallId = j.at("param2").get<std::string>();
    string param3 = j.at("param3").get<std::string>();

    /* Key 'a' */
    if( memcmp("a", key.c_str(), 1) == 0 ) {
      appPrintHelp();
    }
    else if( memcmp("q", key.c_str(), 1) != 0 ) {
      msManager_message_t appMessage;
      appMessage.primitive = MESSAGE_PRIMITIVE_USER;
      appMessage.param = (void*) key.c_str();
      msManager_handleService( &appStateCtxt, &appMessage );
    }
    else if( memcmp("q", key.c_str(), 1) == 0 ) {
      executeApp = false;
    }
  }

  return 0;
}
