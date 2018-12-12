// =============================================================================
/*!
 * @file       src/interfaces/simple_humidity_client.cpp
 *
 * This file contains the implementation of the Simple Humidity interface : Client role.
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

#include "hanfun/interfaces/simple_humidity.h"

#include "hanfun/attributes.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::SimpleHumidity;

using namespace HF::Protocol;
using namespace HF::Attributes;

// =============================================================================
// Simple Humidity Interface : Client Role
// =============================================================================

// =============================================================================
// Client::read_all
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::read_all (Protocol::Address &addr)
{
   Message message;

   message.itf.role   = SERVER_ROLE;
   message.itf.id     = SimpleHumidity::Client::uid ();
   message.itf.member = Pack::ALL;
   message.type       = Protocol::Message::GET_ATTR_PACK_REQ;

   send (addr, message);
}

// =============================================================================
// Client::handle_attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Client::handle_attribute (Protocol::Packet &packet, Common::ByteArray &payload,
                                         uint16_t offset)
{
   Common::Result res = AbstractInterface::handle_attribute (packet, payload, offset);

   if (res != Common::Result::OK)
   {
      return res;
   }

   if (packet.message.type == Message::GET_ATTR_PACK_RES)
   {
      GetAttributePack::Response resp (create_attribute);
      resp.unpack (payload, offset);

      auto &attributes = resp.attributes;

      for (uint8_t uid = VALUE_ATTR; uid <= __LAST_ATTR__; ++uid)
      {
         auto attr = attributes[uid];

         if (nullptr != attr)
         {
            read_resp (packet.source, *(static_cast <Attribute <uint16_t> *>(attr)));
         }
      }
   }
   else if (packet.message.type == Message::GET_ATTR_RES)
   {
      auto attr = create_attribute (packet.message.itf.member);

      if (nullptr != attr)
      {
         HF::Attributes::Response resp (attr);
         resp.unpack (payload, offset);

         read_resp (packet.source, *(static_cast <Attribute <uint16_t> *>(attr)));
      }
   }

   return res;
}
