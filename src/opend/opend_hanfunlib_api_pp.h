/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfunlib_api_pp.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      openD HAN-FUN API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   OPEND_HANFUN_API_PP openD HAN-FUN API portable part
 *             This module specifies the HAN-FUN API of openD connect.
 * @{
 *
 * @defgroup   OPEND_HANFUN_INTERFACE Interfaces
 * @defgroup   OPEND_HANFUN_PROFILE Profiles
 */

#ifndef __OPEND_HANFUNLIB_API_PP_H__
#define __OPEND_HANFUNLIB_API_PP_H__

#include "opend_hanfun_api.h"

/*!
 * Device management struct for the node device.
 */
struct DeviceManagementNode: public HF::Core::DeviceManagement::Client {
  DeviceManagementNode(HF::Core::Unit0 &unit0) :
  	HF::Core::DeviceManagement::Client(unit0)
  {}

  /**
   * @brief   Register device request.
   *
   * @details Send a request to the concentrator for register a node device.
   */
  void register_device();

  /**
   * @brief   Response of register request.
   *
   * @details Response from the concentrator after the register request.
   *
   * @param   response Struct of the register response.
   */
  void registered(HF::Core::DeviceManagement::RegisterResponse &response);

  using HF::Core::DeviceManagement::Client::address;

  /**
   * @brief   Set the HANFUN address associated with this device.
   *
   * @details This method SHOULD be used to restore the HANFUN address received
   *          from a registration message.
   *
   * @param   addr HANFUN address to associated with this device.
   */
  void address(uint16_t addr);
};

/*!
 * Unit0 struct for the node device.
 */
struct Unit0Node: public HF::Devices::Node::Unit0<HF::Core::DeviceInformation::Server,
                                                  DeviceManagementNode,
                                                  HF::Core::AttributeReporting::Server>
{
  Unit0Node(HF::IDevice &device) :
    HF::Devices::Node::Unit0<HF::Core::DeviceInformation::Server, DeviceManagementNode,
    HF::Core::AttributeReporting::Server>(device)
  {}
};

/*!
 * Simple Switch struct profile for the node device.
 */
struct SimpleSwitch: public HF::Units::Unit<HF::Profiles::SimpleOnOffSwitch> {
  SimpleSwitch(uint8_t id, HF::IDevice &device) :
	  HF::Units::Unit<HF::Profiles::SimpleOnOffSwitch>(id, device)
  {}
};

/*!
 * Simple Reed struct profile for the node device.
 */
struct SimpleReed: public HF::Units::Unit<HF::Profiles::MotionDetector> {
  SimpleReed(uint8_t id, HF::IDevice &device) :
	  HF::Units::Unit<HF::Profiles::MotionDetector>(id, device)
  {}
};

/*!
 * Simple Light struct profile for the node device.
 */
class SimpleLight: public HF::Units::Unit<HF::Profiles::SimpleLight>
{
  public:

  SimpleLight (uint8_t id, HF::IDevice &device) :
    HF::Units::Unit<HF::Profiles::SimpleLight>(id, device)
  {}

  /**
   * @brief   Received turn on the led command.
   *
   * @details Save the state of the received on command in the HANFUN library.
   *
   * @param   source Source address of the received message.
   */
  void on (HF::Protocol::Address &source);

  /**
   * @brief   Received turn off the led command.
   *
   * @details Save the state of the received off command in the HANFUN library.
   *
   * @param   source Source address of the received message.
   */
  void off (HF::Protocol::Address &source);

  /**
   * @brief   Received toggle the led command.
   *
   * @details Save the state of the received toggle command in the HANFUN library.
   *
   * @param   source Source address of the received message.
   */
  void toggle (HF::Protocol::Address &source);
};

/*!
 * Device struct for the node device.
 */
struct Device: public HF::Devices::Node::Abstract<Unit0Node>
{
  public:

  /**
   * @brief   Create device instance.
   *
   * @details Create a device object for the node device with singleton.
   *
   * @retval  Device object singleton instance.
   */
  static Device * instance();

  virtual ~Device ()
  {}

  /**
   * @brief   Is the node device registered.
   *
   * @details Check if the node device is registered.
   *
   * @retval  Status of the registration. True, if the node device is registered.
   */
  bool is_registered ();

  /**
   * @brief   Receive message.
   *
   * @details Handle the received HANFUN message.
   *
   * @param   packet Received packet of the message.
   * @param   payload Received payload of the message.
   * @param   offset Offset of the received message.
   */
  void receive (HF::Protocol::Packet &packet, HF::Common::ByteArray &payload, size_t offset);

  /**
   * @brief   Connect the link.
   *
   * @details Connect the link of the node device to the transport endpoint api.
   *
   * @param   link Link of the node device for the transport endpoint api.
   */
  void connected (HF::Transport::Link *link);

  /**
   * @brief   Address of the node device.
   *
   * @details Set the address of the node device.
   *
   * @param   address Address to set for the node device.
   */
  void address (uint16_t address)
  {
    this->unit0()->device_management()->address(address);
  }

  using HF::Devices::Node::Abstract<Unit0Node>::address;

  /**
   * @brief   Node device send.
   *
   * @details Send a HANFUN packet.
   *
   * @param   packet HANFUN packet to send.
   */
  void send (HF::Protocol::Packet &packet);

  private:

  /* Private constructor for singleton object. */
  Device () :HF::Devices::Node::Abstract<Unit0Node>()
  {}
};

/**
 * @brief   openD HANFUN register device.
 *
 * @details Send a register device to the concentrator. This function is triggered by an
 *          indication after the ULE registration is finished.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t opend_hanfun_registerDevice();

/**
 * @brief   openD HANFUN create profile.
 *
 * @details Create a profile for the node device.
 *
 * @param   opend_profile Enum of the HANFUN profile.
 * @param   id ID of the HANFUN profile.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t opend_hanfun_createProfile(openD_hanfunApi_profile_t opend_profile, uint8_t id);

/*! @} defgroup OPEND_HANFUNLIB_API_PP */

#endif /* __OPEND_HANFUNLIB_API_PP_H__ */
