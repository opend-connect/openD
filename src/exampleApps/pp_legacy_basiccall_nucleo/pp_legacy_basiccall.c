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

#include "opend_ll_serial.h"
#include "opend_ll_gpio.h"

#define ARRAY_SIZEOF(x)  (sizeof(x) / sizeof((x)[0]))

#define setupCallHandsetId (char) '6'

/**
 * Object to handle user register button.
 */
openD_ll_gpio_button_ctxt_t button01;

typedef enum {
  APP_STATE_INIT,
  APP_STATE_UNREGISTERED,
  APP_STATE_STANDBY,
  APP_STATE_CONNECTED,
} opendAppStates_t;

static uint8_t app_audioVolume( void );

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

static uint8_t audioVolume = 3U;

static uint8_t app_audioVolume( void ) {
  if( 0x05 > audioVolume ) {
    audioVolume++;
  } else {
    audioVolume = 0U;
  }
  return audioVolume;
}

static void openD_audioApiCfm_callback( openD_audioApiCfm_t *aConfirm ) {

  if( !aConfirm ) {
    return;
  }
    switch( aConfirm->service ) {

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
        msManager_changeState( &appStateCtxt, APP_STATE_CONNECTED );
      }
      break;

    case OPEND_CALLAPI_RELEASE:
      if( OPEND_STATUS_OK == cConfirm->status ) {
        /* Release call was successfull. */
        msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
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
    case OPEND_CALLAPI_RELEASE:
      /* Released call, change to standby state. */
      msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
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
          msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
        }
      }
      break;

    case OPEND_SUBAPI_SUBSCRIBE:
      if( OPEND_STATUS_OK == sConfirm->status ) {
        /* Subscription was successfull, change state to standby. */
        msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
      }
      break;

    case OPEND_SUBAPI_SUBSCRIPTION_DELETE:
      if( OPEND_STATUS_OK == sConfirm->status ) {
        /* Subscription delete was successfull. */
        msManager_changeState( &appStateCtxt, APP_STATE_UNREGISTERED );
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
      /* Subscripted, change state to standby. */
      msManager_changeState( &appStateCtxt, APP_STATE_STANDBY );
      break;

    case OPEND_SUBAPI_SUBSCRIPTION_DELETE:
      /* Subscription was deleted. */
      msManager_changeState( &appStateCtxt, APP_STATE_UNREGISTERED );
      break;

    default:
      break;
  }
  return;
}


/* openD application states. */
bool app_state_init( void *param ) {

  msManager_message_t *message = (msManager_message_t *) param;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      /* Initialization state. */
      if( OPEND_STATUS_OK == openD_init( NULL ) ) {
        msManager_changeState( &appStateCtxt, APP_STATE_UNREGISTERED );
      }

      /* Set access code. */
      openD_subApiReq_t openD_subApiReq;
      openD_subApiReq.service = OPEND_SUBAPI_SET_AC;
      openD_subApiReq.param.setAc.ac[0] = 0xFF;
      openD_subApiReq.param.setAc.ac[1] = 0xFF;
      openD_subApiReq.param.setAc.ac[2] = 0x00;
      openD_subApiReq.param.setAc.ac[3] = 0x00;
      openD_subApi_request( &openD_subApiReq );
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
      /* Check is the device already registered. */
      subApiReq.service = OPEND_SUBAPI_GET_REGISTRATION_STATE;
      openD_subApi_request( &subApiReq );
      break;

    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x72:
          /* Key 'r' KEY_REG */
          subApiReq.service = OPEND_SUBAPI_SUBSCRIBE;
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
  openD_callApiReq_t callApiReq;
  openD_subApiReq_t subApiReq;
  openD_mgmtApiReq_t mgmtApiReq;

  switch( message->primitive )
  {
    case MESSAGE_PRIMITIVE_INIT:
      break;

    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {

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

        case 0x72:
          /* Key 'r' Setup call */
          callApiReq.service = OPEND_CALLAPI_SETUP;
          callApiReq.param.setup.pmid[0] = setupCallHandsetId;
          openD_callApi_request( &callApiReq );
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
      audioApiReq.param.setVolume.level = audioVolume;
      openD_audioApi_request( &audioApiReq );
      break;

    case MESSAGE_PRIMITIVE_USER:
      /* User interaction. */
      switch( (*((char*) message->param)) ) {
        case 0x72:
          /* Key 'r' Release call */
          callApiReq.service = OPEND_CALLAPI_RELEASE;
          openD_callApi_request( &callApiReq );

        case 0x69:
          /* Key 'i' Volume up */
          audioApiReq.service = OPEND_AUDIOAPI_SET_VOLUME;
          audioApiReq.param.setVolume.level = app_audioVolume();
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

/* Handle the button input of the application user. */
static int handle_user_input( void )
{

  if( OPEND_LL_GPIO_BUTTON_PRESSED == openD_ll_gpio_readButton( &button01, OPEND_LL_GPIO_PIN_USER_BUTTON_01 ) ) {

      msManager_message_t appMessage;
      appMessage.primitive = MESSAGE_PRIMITIVE_USER;
      appMessage.param = (void*) "r";
      msManager_handleService( &appStateCtxt, &appMessage );
  }

  return 1;
}

int main(int argc, char* argv[]) {

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

  while( 1 )
  {
    handle_user_input();
	}

  return 0;
}
