// =============================================================================
/*!
 * @file       src/core/device_management_client.cpp
 *
 * This file contains the implementation of the Device Management : Client Role.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 ULE Alliance
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 *
 * Initial development by Bithium S.A. [http://www.bithium.com]
 */
// =============================================================================

#include "hanfun/profiles.h"

#include "hanfun/core/device_information.h"
#include "hanfun/core/device_management.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Core;
using namespace HF::Core::DeviceManagement;

// =============================================================================
// DeviceManagementClient
// =============================================================================

// =============================================================================
// Client::register_device
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::register_device ()
{
   Protocol::Address addr (0, 0);

   RegisterMessage   *payload = new RegisterMessage (DeviceInformation::EMC);

   HF::IDevice &device        = unit ().device ();

   /* *INDENT-OFF* */
   for_each (device.units ().begin (), device.units ().end (),
             [&payload](const Units::IUnit *dev_unit)
   {
      /*
       * Add a unit entry if not unit 0 or unit 0 has optional interfaces.
       */
      if (dev_unit != nullptr && (dev_unit->id () != 0 ||
          (dev_unit->id () == 0 && dev_unit->interfaces().size() != 0)))
      {
         payload->units.push_back (Unit(*dev_unit));
      }
   });
   /* *INDENT-ON* */

   Protocol::Message message (payload->size ());

   message.itf.role   = SERVER_ROLE;
   message.itf.id     = Client::uid ();
   message.itf.member = REGISTER_CMD;

   payload->pack (message.payload);

   send (addr, message);

   delete payload;
}

// =============================================================================
// Client::deregister
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::deregister (uint16_t address)
{
   DeregisterMessage payload (address);

   Protocol::Address addr (0, 0);
   Protocol::Message message (payload.size ());

   message.itf.role   = SERVER_ROLE;
   message.itf.id     = Client::uid ();
   message.itf.member = DEREGISTER_CMD;

   payload.pack (message.payload);

   send (addr, message);
}

// =============================================================================
// Client::payload_size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Client::payload_size (Protocol::Message::Interface &itf) const
{
   switch (itf.member)
   {
      case REGISTER_CMD:
         return payload_size_helper <RegisterResponse>();

      case DEREGISTER_CMD:
         return payload_size_helper <Protocol::Response>();

      case START_SESSION_CMD:
         return SessionMgr::payload_size (SessionManagement::START);

      case GET_ENTRIES_CMD:
         return SessionMgr::payload_size (SessionManagement::GET);

      case END_SESSION_CMD:
         return SessionMgr::payload_size (SessionManagement::END);

      default:
         return 0;
   }
}

// =============================================================================
// Client::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Client::handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                       uint16_t offset)
{
   switch (packet.message.itf.member)
   {
      case REGISTER_CMD:
      {
         RegisterResponse registration;
         registration.unpack (payload, offset);
         registered (registration);

         break;
      }
      case DEREGISTER_CMD:
      {
         Protocol::Response response;
         response.unpack (payload, offset);
         deregistered (response);

         break;
      }
      case START_SESSION_CMD:
      {
         return SessionMgr::handle_command (SessionManagement::START, packet, payload, offset);
      }
      case GET_ENTRIES_CMD:
      {
         return SessionMgr::handle_command (SessionManagement::GET, packet, payload, offset);
      }
      case END_SESSION_CMD:
      {
         return SessionMgr::handle_command (SessionManagement::END, packet, payload, offset);
      }
      default:
         return Common::Result::FAIL_UNKNOWN;
   }

   return Common::Result::OK;
}

// =============================================================================
// Client::registered
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::registered (RegisterResponse &response)
{
   if (response.code == Common::Result::OK)
   {
      this->_address = response.address;
   }
}

// =============================================================================
// Client::deregistered
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::deregistered (Protocol::Response &response)
{
   if (response.code == Common::Result::OK)
   {
      this->_address = Protocol::BROADCAST_ADDR;
   }
}
