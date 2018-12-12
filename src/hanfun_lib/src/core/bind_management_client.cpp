// =============================================================================
/*!
 * @file       src/core/bind_management_client.cpp
 *
 * This file contains the implementation of the Bind Management : Client Role.
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

#include "hanfun/core/bind_management.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Core;
using namespace HF::Core::BindManagement;

// =============================================================================
// BindManagement::Client.
// =============================================================================

// =============================================================================
// Client::add
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::add (const Protocol::Address &source, const Protocol::Address &destination,
                  const Common::Interface &itf)
{
   Protocol::Address addr (0, 0);

   BindManagement::Entry *payload = new BindManagement::Entry ();

   payload->source      = source;
   payload->destination = destination;
   payload->itf         = itf;

   Protocol::Message message (payload->size ());

   message.itf.role   = SERVER_ROLE;
   message.itf.id     = BindManagement::Client::uid ();
   message.itf.member = ADD_BIND_CMD;

   payload->pack (message.payload);

   send (addr, message);

   delete payload;
}

// =============================================================================
// Client::remove
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::remove (const Protocol::Address &source, const Protocol::Address &destination,
                     const Common::Interface &itf)
{
   Protocol::Address addr (0, 0);

   BindManagement::Entry *payload = new BindManagement::Entry ();

   payload->source      = source;
   payload->destination = destination;
   payload->itf         = itf;

   Protocol::Message message (payload->size ());

   message.itf.role   = SERVER_ROLE;
   message.itf.id     = BindManagement::Client::uid ();
   message.itf.member = REMOVE_BIND_CMD;

   payload->pack (message.payload);

   send (addr, message);

   delete payload;
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
      case ADD_BIND_CMD:
      case REMOVE_BIND_CMD:
         return Protocol::Response::min_size;

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
// BindManagement::Client::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result BindManagement::Client::handle_command (Protocol::Packet &packet,
                                                       Common::ByteArray &payload, uint16_t offset)
{
   Common::Result result   = Common::Result::FAIL_UNKNOWN;

   BindManagement::CMD cmd = static_cast <BindManagement::CMD>(packet.message.itf.member);

   switch (cmd)
   {
      case ADD_BIND_CMD:
      case REMOVE_BIND_CMD:
      {
         Protocol::Response response;
         response.unpack (payload, offset);

         this->response (cmd, response);
         result = Common::Result::OK;
         break;
      }
      case START_SESSION_CMD:
         return SessionMgr::handle_command (SessionManagement::START, packet, payload, offset);

      case GET_ENTRIES_CMD:
         return SessionMgr::handle_command (SessionManagement::GET, packet, payload, offset);

      case END_SESSION_CMD:
         return SessionMgr::handle_command (SessionManagement::END, packet, payload, offset);

      default:
         break;
   }

   return result;
}

// =============================================================================
// BindManagement::Client::response
// =============================================================================
/*!
 *
 */
// =============================================================================
void BindManagement::Client::response (const BindManagement::CMD cmd,
                                       const Protocol::Response &response)
{
   UNUSED (cmd);
   UNUSED (response);
}
