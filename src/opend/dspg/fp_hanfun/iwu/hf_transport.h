/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       hf_transport.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      HANFUN transport IWU.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   HANFUN IWU
 *             This file specifies the HANFUN IWU API.
 * @{
 */

#ifndef H_TRANSPORT_H
#define H_TRANSPORT_H

#include <hanfun.h>


namespace HF
{
  namespace ULE
  {

    class Link;

    class Transport: public HF::Devices::Concentrator::Transport
    {
      public:
      /**
      * @brief   Transport instance.
      *
      * @details Create a singleton IWU instance object.
      *
      * @param   Transport* IWU instance object.
      */
      static Transport * instance();

      /**
      * Deconstructor.
      */
      virtual ~Transport() {}

      /**
      * Initialize hanfun library iwu.
      * Currently out of use.
      * Must be overwritten as pure virtual function.
      */
      void initialize ();

      /**
      * Destroy the initialization of the hanfun library transport layer.
      */
      void destroy ();

      /**
      * @brief   Connected.
      *
      * @details Set the id and ipui in the hanfun library of the connected device.
      *
      * @param   dev_id  Device id of the connected device.
      * @param   ipui IPUI of the connected device.
      */
      void connected (uint16_t dev_id, uint8_t ipui[5]);

      /**
      * @brief   Connected.
      *
      * @details Set the id and ipui in the hanfun library of the connected device.
      *
      * @param   dev_id  Device id of the connected device.
      * @param   data Pointer to the data.
      * @param   size Size of the data.
      */
      void receive(const uint16_t dev_id, const uint8_t data[], size_t size);

      /**
      * @brief   Find by id.
      *
      * @details Find the link by id regarding of the node device.
      *
      * @param   dev Id of the device.
      */
      Link * find_by_id(uint16_t dev);

      /**
      * @brief   Find by address.
      *
      * @details Find the link by address regarding of the node device.
      *
      * @param   address Address of the device.
      */
      Link * find_by_address(uint16_t address);

      private :

      /**
      * Private constructor for singleton object.
      */
      Transport() {}
    };

    class Link: public HF::Transport::AbstractLink
    {
      protected:

      /**
      * Device id.
      */
      const uint16_t dev_id;

      /**
      * Pointer of the transport layer.
      */
      Transport *tsp;

      /**
      * Holds the IPUI.
      */
      HF::UID::DECT ipui;

      public:

      /**
      * Constructor.
      */
      Link (uint16_t dev_id, HF::UID::DECT &_ipui, Transport *tsp) :
            HF::Transport::AbstractLink(), dev_id(dev_id), tsp(tsp), ipui(_ipui)
      {}

      /**
      * Deconstructor.
      */
      virtual ~Link () {}

      /**
      * @brief   Send.
      *
      * @details Send a hanfun command.
      *
      * @param   array Reference to the data to send.
      */
      void send (HF::Common::ByteArray &array);

      /**
      * Return the uid.
      */
      const HF::UID::UID uid () const
      {
        return HF::UID::UID((HF::UID::UID_T *)&ipui);
      }

      /**
      * Set the uid.
      */
      void uid (const HF::UID::DECT &_ipui)
      {
        this->ipui = _ipui;
      }

      /**
      * Return the regarding transport layer.
      */
      HF::Transport::Layer const *transport () const
      {
        return tsp;
      }

      /**
      * Return the regarding transport layer.
      */
      uint16_t id()
      {
        return dev_id;
      }
    };

  }  // namespace ULE

}  // namespace HF

#endif /* H_TRANSPORT_H */
