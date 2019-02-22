/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       main_hanfun.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      Demo Application
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include "opend_hanfun_api_pp.h"
#include "ule.h"

#include "opend_api.h"
#include "opend_ll_gpio.h"

using namespace std;

static bool deviceRegistered;

openD_ll_gpio_button_ctxt_t button01;

/**
 * @brief   Update the application-specific LED.
 *
 * @details The function updates the status of the application-specific LED.
 *
 * @param   led_on_off Current state of the LED.
 */
std::function<void(bool led_on_off)> update = [](bool led_on_off)
{
	if( led_on_off ) {
		openD_ll_gpio_write( OPEND_LL_GPIO_PIN_USER_LED_01, OPEND_LL_GPIO_PIN_SET );
	} else {
		openD_ll_gpio_write( OPEND_LL_GPIO_PIN_USER_LED_01, OPEND_LL_GPIO_PIN_RESET );
	}
};

/**
 * @brief   Device management confirm callback.
 *
 * @details Executes the service specific device management confirmation.
 *
 * @param   hDevMgmtConfirm Pointer to the device management confirm structure.
 */
void devMgmtConfirmCallback(openD_hanfunApi_devMgmtCfm_t *hDevMgmtConfirm);

/**
 * @brief   Profile indication callback.
 *
 * @details Executes the service specific profile indication.
 *
 * @param   hProfileInd Pointer to the profile indication structure.
 */
void profileIndCallback(openD_hanfunApi_profileInd_t *hProfileInd);

/**
 * @brief   Profile confirm callback.
 *
 * @details Executes the service specific profile confirmation.
 *
 * @param   hProfileConfirm Pointer to the profile confirm structure.
 */
void profileConfirmCallback(openD_hanfunApi_profileCfm_t *hProfileConfirm);


void devMgmtConfirmCallback(openD_hanfunApi_devMgmtCfm_t *hDevMgmtConfirm)
{
  openD_status_t confirmAndIndStatusByte;

  switch(hDevMgmtConfirm->service)
  {
	  case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE:
	    confirmAndIndStatusByte = hDevMgmtConfirm->status;
      if(confirmAndIndStatusByte == OPEND_STATUS_OK)
      {
        successConInd();
        deviceRegistered = true;
      }
      else
      {
        failureConInd();
        deviceRegistered = false;
      }
	    break;
	  default:
	    break;
  }
}

void profileIndCallback( openD_hanfunApi_profileInd_t *hProfileInd )
{
  if(hProfileInd->status != OPEND_STATUS_OK)
	{
		return;
	}

  switch(hProfileInd->profile)
  {
    case OPEND_HANFUNAPI_SIMPLE_LIGHT:
      switch(hProfileInd->simpleLight.service)
	    {
		    case OPEND_HANFUN_IONOFF_SERVER_TOGGLE_ADDR:
		      /* Toggle the application-specific LED. */
		      update(hProfileInd->simpleLight.param.getState.state);
		      break;
        case OPEND_HANFUN_IONOFF_SERVER_ON_ADDR:
		      /* Turn on the application-specific LED. */
          update(hProfileInd->simpleLight.param.getState.state);
          break;
		    case OPEND_HANFUN_IONOFF_SERVER_OFF_ADDR:
		      /* Turn off the application-specific LED. */
          update(hProfileInd->simpleLight.param.getState.state);
		      break;
		    default:
		      break;
	  }
	    break;
	  default:
	    break;
  }
}

void profileConfirmCallback(openD_hanfunApi_profileCfm_t *hProfileConfirm)
{
  /* Add your application code here. */
}

/* Handle the button input of the application user. */
static int handle_user_input( void )
{

  if( OPEND_LL_GPIO_BUTTON_PRESSED == openD_ll_gpio_readButton( &button01, OPEND_LL_GPIO_PIN_USER_BUTTON_01 ) ) {

#if defined PROFILE_SIMPLE_LIGHT
    openD_hanfunApi_devMgmtReq_t hMgmtRequest;
    hMgmtRequest.service=OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE;
    /* Send a device management register request to the concentrator. */
    if( openD_hanfunApi_pp_devMgmtRequest(&hMgmtRequest) == OPEND_STATUS_OK ) {

    }
#elif defined PROFILE_SIMPLE_SWITCH
    if(deviceRegistered == false)
    {
      openD_hanfunApi_devMgmtReq_t hMgmtRequest;
      hMgmtRequest.service=OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE;
      /* Send a device management register request to the concentrator. */
      if( openD_hanfunApi_pp_devMgmtRequest(&hMgmtRequest) == OPEND_STATUS_OK ) {

      }
    }
    else
    {
      openD_hanfunApi_profileReq_t hProfileRequest;
      hProfileRequest.profile=OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH;
      hProfileRequest.simpleOnOffSwitch.service=OPEND_HANFUN_IONOFF_CLIENT_TOGGLE;
      /* Send a profile toggle request to the concentrator. */
      if( openD_hanfunApi_pp_profileRequest(&hProfileRequest) == OPEND_STATUS_OK ) {

      }
    }
#endif
  }
  return 1;
}


/* main application */
int main(int argc, char *argv[])
{

  openD_init( NULL );

  deviceRegistered = false;

  /* Variable for the openD primitives. */
	openD_hanfunApiPrimitives openD_hanfunApiPrimitives;

  /* Set the confirmation and indication callbacks. */
  openD_hanfunApiPrimitives.openD_hanfunApiProfileCfm = profileConfirmCallback;
	openD_hanfunApiPrimitives.openD_hanfunApi_mgmtCfm = devMgmtConfirmCallback;
	openD_hanfunApiPrimitives.openD_hanfunApiProfileInd = profileIndCallback;

  /* Initialize the openD HANFUN API primitives. */
	if(openD_hanfunApi_init(&openD_hanfunApiPrimitives) == OPEND_STATUS_OK)
	{

	}

  if(openD_hanfunApi_pp_init() == OPEND_STATUS_OK)
	{

  }

#if defined PROFILE_SIMPLE_LIGHT
  if(opend_hanfunApi_createProfile(OPEND_HANFUNAPI_SIMPLE_LIGHT, 1) != OPEND_STATUS_OK)
  {

  }
#elif defined PROFILE_SIMPLE_SWITCH
  if(opend_hanfunApi_createProfile(OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH, 1) != OPEND_STATUS_OK)
  {

  }
#endif

  while( 1 )
	{
    handle_user_input();
	}

  /* Destroy the application. */
  exitApp();

	return 0;
}
