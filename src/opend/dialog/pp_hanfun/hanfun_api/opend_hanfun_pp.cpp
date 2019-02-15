/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_pp.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

extern "C"
{
#include "mmi_def.h"
}
#include "opend_dataTypes.h"
#include "opend_hanfun_api_pp.h"
#include "opend_hanfunlib_api_pp.h"
#include "opend_hanfun.h"
#include "hanfun.h"
#include <inc/hanfun/debug.h>
#include "ule.h"

#include "opend_ll_gpio.h"

/*!
 * Static and global SimpleOnOffSwitchable profile object.
 */
static SimpleSwitch * g_simple_switch = nullptr;
/*!
 * Static and global MotionDetector profile object.
 */
static SimpleReed * g_simple_reed = nullptr;
/*!
 * Static and global SimpleLight profile object.
 */
static SimpleLight * g_simple_light = nullptr;


void DeviceManagementNode::register_device()
{
  HF::Core::DeviceManagement::Client::register_device();
}

void DeviceManagementNode::address(uint16_t addr)
{
  this->_address = (addr & HF::Protocol::BROADCAST_ADDR);
}

void DeviceManagementNode::registered (HF::Core::DeviceManagement::RegisterResponse &response)
{
  HF::Core::DeviceManagement::Client::registered(response);

  return;
}

void SimpleLight::on (HF::Protocol::Address &source)
{
  openD_hanfunApi_profileInd_t hProfileInd;

  hProfileInd.profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
  hProfileInd.simpleLight.service = OPEND_HANFUN_IONOFF_SERVER_ON_ADDR;
  hProfileInd.status = OPEND_STATUS_OK;
  g_simple_light->HF::Units::Unit<HF::Profiles::SimpleLight>::on( source );
  hProfileInd.simpleLight.param.getState.state = (bool) g_simple_light->state();

  openD_hanfun_profileInd(&hProfileInd);
}

void SimpleLight::off (HF::Protocol::Address &source)
{
  openD_hanfunApi_profileInd_t hProfileInd;

  hProfileInd.profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
  hProfileInd.simpleLight.service = OPEND_HANFUN_IONOFF_SERVER_OFF_ADDR;
  hProfileInd.status = OPEND_STATUS_OK;
  g_simple_light->HF::Units::Unit<HF::Profiles::SimpleLight>::off( source );
  hProfileInd.simpleLight.param.getState.state = (bool) g_simple_light->state();

  openD_hanfun_profileInd(&hProfileInd);
}

void SimpleLight::toggle (HF::Protocol::Address &source)
{
  openD_hanfunApi_profileInd_t hProfileInd;

  hProfileInd.profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
  hProfileInd.simpleLight.service = OPEND_HANFUN_IONOFF_SERVER_TOGGLE_ADDR;
  hProfileInd.status = OPEND_STATUS_OK;
  g_simple_light->HF::Units::Unit<HF::Profiles::SimpleLight>::toggle( source );
  hProfileInd.simpleLight.param.getState.state = (bool) g_simple_light->state();

  openD_hanfun_profileInd(&hProfileInd);
}

bool Device::is_registered ()
{
  return address() != HF::Protocol::BROADCAST_ADDR;
}

void Device::receive (HF::Protocol::Packet &packet, HF::Common::ByteArray &payload, size_t offset)
{
  HF::Devices::Node::Abstract<Unit0Node>::receive(packet, payload, offset);
}

void Device::connected (HF::Transport::Link * link)
{
  HF::Devices::Node::Abstract<Unit0Node>::connected(link);
}

void Device::send (HF::Protocol::Packet &packet)
{
  HF::Devices::Node::Abstract<Unit0Node>::send(packet);
}

Device * Device::instance()
{
  static Device device;

  return &device;
}

openD_status_t openD_hanfunApi_pp_init()
{
  Device * g_device = Device::instance();
  HF::ULE::Transport * g_transport = HF::ULE::Transport::instance();

	/* Configure the transport IWU object. */
	g_transport->configure(NULL);

  /* Initialize the transport IWU object. */
	g_transport->initialize();
	if ( !g_transport->is_initialized() ) {
		return OPEND_STATUS_FAIL;
	}

  g_transport->add((HF::Transport::Endpoint *) g_device);
  g_transport->add(new HF::ULE::Link(g_transport));

  if(opend_hanfun_createProfile(OPEND_HANFUNAPI_SIMPLE_LIGHT, 1) != OPEND_STATUS_OK)
	{
		return OPEND_STATUS_FAIL;
	}

  return OPEND_STATUS_OK;
}

openD_status_t opend_hanfun_createProfile(openD_hanfunApi_profile_t opend_profile, uint8_t id)
{
  Device * g_device = Device::instance();

  switch(opend_profile){
    case OPEND_HANFUNAPI_SIMPLE_LIGHT:
      g_simple_light = new SimpleLight(id, *g_device);
      break;
    case OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCHABLE:
      g_simple_switch = new SimpleSwitch(id, *g_device);
      break;
    case OPEND_HANFUNAPI_MOTION_DETECTOR:
      g_simple_reed = new SimpleReed(id, *g_device);
      break;
    default:
      return OPEND_STATUS_ARGUMENT_INVALID;
      break;
  }

  return OPEND_STATUS_OK;
}

openD_status_t opend_hanfun_registerDevice()
{
  Device * g_device = Device::instance();

  /* Turn off user LED to show that the ULE registration was successful. */
  openD_ll_gpio_write( OPEND_LL_GPIO_PIN_USER_LED_01, OPEND_LL_GPIO_PIN_RESET );

  openD_hanfunApi_devMgmtCfm_t hDevMgmtConfirm;

  /* Set the node device address. */
	if(MmiCtrl.hanfun_address==0){
    g_device->address(HF::Protocol::BROADCAST_ADDR);
  }
  else{
    g_device->address(MmiCtrl.hanfun_address);
  }
  hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_SET_ADDRESS;
  hDevMgmtConfirm.status = OPEND_STATUS_OK;
  openD_hanfun_devMgmtCfm(&hDevMgmtConfirm);

  /* Get the node device address. */
  uint16_t deviceAddress = g_device->address();
  hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_ADDRESS;
  hDevMgmtConfirm.status = OPEND_STATUS_OK;
  hDevMgmtConfirm.param.registrationElement.address = deviceAddress;
  openD_hanfun_devMgmtCfm(&hDevMgmtConfirm);

  /* Send a register device request. */
  g_device->unit0()->device_management()->register_device();
  hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE;
  hDevMgmtConfirm.status = OPEND_STATUS_OK;
  openD_hanfun_devMgmtCfm(&hDevMgmtConfirm);

  return OPEND_STATUS_OK;
}

openD_status_t openD_hanfunApi_pp_devMgmtRequest( openD_hanfunApi_devMgmtReq_t *hMgmtRequest, uint16_t address )
{
  Device * g_device = Device::instance();

  if(hMgmtRequest == NULL)
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  switch(hMgmtRequest->service){
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE:
      if (!g_device->is_registered())
      {
        /* Enable the ULE registration and turn on LED3. */
        Enable_Registration(ACCESS_CODE);
        openD_ll_gpio_write( OPEND_LL_GPIO_PIN_USER_LED_01, OPEND_LL_GPIO_PIN_SET );
      }
      break;

    default:
      break;
  }

  return OPEND_STATUS_ARGUMENT_INVALID;
}

openD_status_t openD_hanfunApi_pp_profileRequest( openD_hanfunApi_profileReq_t *hProfileRequest )
{
  openD_hanfunApi_profileCfm_t hProfileConfirm;

  if(hProfileRequest == NULL)
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  switch( hProfileRequest->profile )
  {
    case OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH:
      switch( hProfileRequest->simpleOnOffSwitch.service )
      {
        case OPEND_HANFUN_IONOFF_CLIENT_TOGGLE:
          /* Send a toggle request. */
          g_simple_switch->toggle();
          hProfileConfirm.status = OPEND_STATUS_OK;
          hProfileConfirm.simpleOnOffSwitch.service = OPEND_HANFUN_IONOFF_CLIENT_TOGGLE;
          openD_hanfun_profileCfm(&hProfileConfirm);
          return OPEND_STATUS_OK;
          break;

        default:
          break;
      }
      break;
    case OPEND_HANFUNAPI_MOTION_DETECTOR:
      switch( hProfileRequest->motionDetector.service )
      {
        case OPEND_HANFUN_iDETECTOR_ALERT:
          /* Send an alert request. */
          g_simple_reed->alert(1);
          hProfileConfirm.status = OPEND_STATUS_OK;
          hProfileConfirm.motionDetector.service = OPEND_HANFUN_iDETECTOR_ALERT;
          openD_hanfun_profileCfm(&hProfileConfirm);
          return OPEND_STATUS_OK;
          break;

        default:
          break;
      }
      break;

    default:
      break;
  }

  hProfileConfirm.status = OPEND_STATUS_FAIL;
  openD_hanfun_profileCfm(&hProfileConfirm);
  return OPEND_STATUS_ARGUMENT_INVALID;
}
