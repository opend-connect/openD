/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_api_fp.h
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
 * @defgroup   OPEND_HANFUN_API_FP openD HAN-FUN API fixed part
 *             This module specifies the HAN-FUN API of openD connect.
 * @{
 *
 * @defgroup   OPEND_HANFUN_INTERFACE Interfaces
 * @defgroup   OPEND_HANFUN_PROFILE Profiles
 */

#ifndef __OPEND_HANFUN_API_FP_H__
#define __OPEND_HANFUN_API_FP_H__

#include "opend_hanfun_api.h"


namespace DeviceManagement
{
  /*!
   * Device management entries class.
   */
  struct Entries:public HF::Core::DeviceManagement::Entries
  {
    /**
     * @brief   Save configuration.
     *
     * @details Save the device management configuration in an entry.
     *
     * @param   device Device to save the configuration.
     *
     * @retval  Result of the operation.
     */
    HF::Common::Result save (const HF::Core::DeviceManagement::Device &device);

    /**
     * @brief   Destroy configuration.
     *
     * @details Destroy the device management configuration in an entry.
     *
     * @param   device Device to destroy the configuration.
     *
     * @retval  Result of the operation.
     */
    HF::Common::Result destroy (const HF::Core::DeviceManagement::Device &device);
  };

  /*!
   * Device Management class.
   */
  struct Server:public HF::Core::DeviceManagement::Server <Entries>
  {
    Server(HF::Core::Unit0 &unit):
      HF::Core::DeviceManagement::Server <Entries>(unit),
      _next_address (HF::Protocol::BROADCAST_ADDR)
    {}

    virtual ~Server() {}

    /**
     * @brief   Next address.
     *
     * @details Handle the next device address.
     *
     * @param   addr Address to set as next device address.
     *
     * @retval  Next address.
     */
    uint16_t next_address (uint16_t addr)
    {
      _next_address = addr;
      return _next_address;
    }

    /**
     * @brief   Available address.
     *
     * @details Handle the next device address.
     *
     * @param   address Address to set as next device address.
     *
     * @retval  Next address.
     */
    bool available (uint16_t address);

    /**
     * @brief   Deregister a device.
     *
     * @details Address of the device to deregister
     *
     * @param   address Address of the device to deregister.
     *
     * @retval  Status of the operation.
     */
    bool deregister (uint16_t address);

    protected:

    using HF::Core::DeviceManagement::Server <Entries>::deregister;

    uint16_t _next_address;

    uint16_t next_address ();
  };
}

namespace BindManagement
{
  /*!
   * Bind management entries class.
   */
  struct Entries:public HF::Core::BindManagement::Entries
  {
    typedef HF::Core::BindManagement::Entry Entry;
    typedef HF::Core::BindManagement::EntryPtr EntryPtr;

    /**
     * @brief   Save entry.
     *
     * @details Save the bind management configuration in an entry.
     *
     * @param   entry Entry to save.
     *
     * @retval  Result of the operation.
     */
    HF::Common::Result save (const Entry &entry);

    /**
     * @brief   Destroy entry.
     *
     * @details Destroy the bind management configuration in an entry.
     *
     * @param   entry Entry to destroy.
     *
     * @retval  Result of the operation.
     */
    HF::Common::Result destroy (const Entry &entry);

    /**
     * @brief   Insert entry.
     *
     * @details Insert the bind management configuration entry.
     *
     * @param   entry Entry to insert.
     */
    void insert (Entry &entry);
  };

  /*!
   * Bind management class.
   */
  struct Server:public HF::Core::BindManagement::Server <Entries>
  {
    Server(HF::Devices::Concentrator::IUnit0 &unit):
           HF::Core::BindManagement::Server <Entries>(unit)
    {}
  };

}

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

namespace Commands
{
  typedef HF::Interfaces::Alert::Server Alert;
  typedef HF::Interfaces::LevelControl::Client LevelControl;
  typedef HF::Interfaces::OnOff::Client OnOff;
  typedef HF::Interfaces::SimplePowerMeter::Server SimplePowerMeter;

  struct Unit:public HF::Units::Unit <HF::Profiles::GenericApplicationLogic, Alert,
                                      LevelControl, OnOff, SimplePowerMeter>
  {
    Unit(uint8_t id, HF::IDevice &device):HF::Units::Unit <HF::Profiles::GenericApplicationLogic,
                                                           Alert, LevelControl, OnOff,
                                                           SimplePowerMeter>(id, device)
    {}

    /*!
     * Return a reference to the Alert object.
     */
    Alert &alert ()
    {
      return *const_cast <Alert *>(get <0>());
    }

    /*!
     * Return a reference to the LevelControl object.
     */
    LevelControl &level_control ()
    {
      return *const_cast <LevelControl *>(get <1>());
    }

    /*!
     * Return a reference to the OnOff object.
     */
    OnOff &on_off ()
    {
      return *const_cast <OnOff *>(get <2>());
    }

    /*!
     * Return a reference to the SimplePowerMeter object.
     */
    SimplePowerMeter &simple_power_meter ()
    {
      return *const_cast <SimplePowerMeter *>(get <3>());
    }

    /**
     * @brief   Handle device information.
     *
     * @details Handle the received device information confirmation.
     *
     * @param   packet Received HANFUN packet.
     * @param   payload Received payload.
     * @param   offset Offset of the received message.
     *
     * @retval  Result of the operation.
     */
    HF::Common::Result handle (HF::Protocol::Packet &packet, HF::Common::ByteArray &payload,
                               uint16_t offset);
  };
}

/*!
 * Macro for Unit 0 with inheritance of the used templates.
 */
typedef HF::Devices::Concentrator::Unit0 <HF::Core::DeviceInformation::Server,
                                          DeviceManagement::Server,
                                          HF::Core::AttributeReporting::Server,
                                          BindManagement::Server> Unit0;

/*!
 * A struct for the HANFUN fix part.
 */
struct FP:public HF::Devices::Concentrator::Abstract <Unit0>
{
  Commands::Unit commands;

  /**
   * @brief   Create FP instance.
   *
   * @details Create a FP object for the concentrator FP with singleton.
   *
   * @retval  FP object singleton instance.
   */
  static FP * instance();

  virtual ~FP()
  {}

  /**
   * @brief   Receive message.
   *
   * @details Handle the received HANFUN message.
   *
   * @param   packet Received HANFUN packet.
   * @param   payload Received payload.
   * @param   offset Offset of the received message.
   */
  void receive (HF::Protocol::Packet &packet, HF::Common::ByteArray &payload, uint16_t offset);

  using HF::Devices::Concentrator::Abstract <Unit0>::link;

  /**
   * @brief   HANFUN iwu links.
   *
   * @details Provide the HANFUN iwu links.
   *
   * @retval  List of the current links.
   */
  std::forward_list <HF::Transport::Link *> &links()
  {
    return _links;
  }

  /**
   * @brief   Has bind.
   *
   * @details Check if the devices have a bind.
   *
   * @param   dev_addr_1 Address of the first device.
   * @param   dev_addr_2 Address of the second device.
   *
   * @retval  Status of the operation.
   */
  bool has_bind (uint16_t dev_addr_1, uint16_t dev_addr_2);

  /**
   * @brief   Bind.
   *
   * @details Bind two devices.
   *
   * @param   dev_addr_1 Address of the first device.
   * @param   dev_addr_2 Address of the second device.
   *
   * @retval  Error handling value of the operation.
   */
  uint8_t bind (uint16_t dev_addr_1, uint16_t dev_addr_2);

  /**
   * @brief   Bind.
   *
   * @details Bind two devices.
   *
   * @param   dev_addr_1 Address of the first device.
   * @param   dev_addr_2 Address of the second device.
   *
   * @retval  Error handling value of the operation.
   */
  bool unbind (uint16_t dev_addr_1, uint16_t dev_addr_2);

  private:

  FP():HF::Devices::Concentrator::Abstract <Unit0>(),
    commands(1, *this)
  {}
};

/**
 * @brief   openD HAN-FUN API initialization.
 *
 * @details Initialization of the hanfun api with the iwu.
 *
 * @param   transport Pointer of the transport iwu for the concentrator.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_fp_init( HF::Transport::Layer *transport );

/**
 * @brief   openD HAN-FUN API device management request.
 *
 * @details Sends a device management request to a device. You can choose between different services.
 *          For example, you can deregister a device.
 *
 * @param   hMgmtRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApi_devMgmtReq_t).
 * @param   address Device address to send the request.
 * @param   address Second device address to bind.
 * @param   dectMode DECT mode.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_fp_devMgmtRequest( openD_hanfunApi_devMgmtReq_t *hMgmtRequest, uint16_t address = 0, uint8_t dectMode = 0 );

/**
 * @brief   openD HAN-FUN API bind management request.
 *
 * @details Bind management request with different services.
 *          This can be used to create binds of devices.
 *
 * @param   hBindRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApi_bindMgmtReq_t).
 * @param   address1 First device address to bind.
 * @param   address2 Second device address to bind.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_fp_bindMgmtRequest( openD_hanfunApi_bindMgmtReq_t *hBindRequest, uint16_t address1 = 0, uint16_t address2 = 0 );

/**
 * @brief   openD HAN-FUN API profile request.
 *
 * @details Sends a profile request to a device. You can choose between different profiles, each with different services.
 *          For example, a led of a registered device can be switched on or off.
 *
 * @param   hProfileRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApi_profileReq_t).
 * @param   address Address of the device to send the request.
 * @param   unit Unit of the device to send the request.
 *
 * @retval  Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_hanfunApi_fp_profileRequest( openD_hanfunApi_profileReq_t *hProfileRequest, uint16_t address = 0, uint16_t unit = 0 );


/*! @} defgroup OPEND_HANFUN_API_FP */

#endif /* __OPEND_HANFUN_API_FP_H__ */
