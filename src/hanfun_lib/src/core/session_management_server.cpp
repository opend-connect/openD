// =============================================================================
/*!
 * @file       src/core/session_manangement_server.cpp
 *
 * This file contains the implementation of the session management functionality
 * for the server side.
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

#include "hanfun/core/session_management.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Common;
using namespace HF::Core::SessionManagement;

// =============================================================================
// AbstractServer::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result AbstractServer::handle_command (CMD cmd, Protocol::Packet &packet,
                                               Common::ByteArray &payload, uint16_t offset)
{
   // Don't process group address.
   if (packet.source.mod == HF::Protocol::Address::GROUP)
   {
      return Common::Result::FAIL_ARG;
   }

   Result result = Result::OK;

   Protocol::Message resp_msg (packet.message, 0);

   switch (cmd)
   {
      case START:
      {
         start_session (packet.source.device);

         StartResponse resp;
         result           = resp.code = Result::OK;
         resp.count       = entries_size ();

         resp_msg.payload = Common::ByteArray (resp.size ());
         resp.pack (resp_msg.payload);

         break;
      }
      case GET:
      {
         result = check_session (packet.source.device, resp_msg.payload);

         if (result == Result::OK)
         {
            GetEntriesMessage msg;
            msg.unpack (payload, offset);
            result = entries (msg.offset, msg.count, resp_msg.payload);
         }

         break;
      }
      case END:
      {
         end_session (packet.source.device);

         Protocol::Response resp;
         result           = resp.code = Result::OK;
         resp_msg.payload = Common::ByteArray (resp.size ());
         resp.pack (resp_msg.payload);

         break;
      }
      default:
         return Result::FAIL_SUPPORT;
   }

   send (packet.source, resp_msg);

   return result;
}

// =============================================================================
// AbstractServer::check_session
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result AbstractServer::check_session (uint16_t address, Common::ByteArray &payload) const
{
   Result result = Result::OK;

   if (!exists (address))
   {
      result = Result::FAIL_READ_SESSION;
   }
   else if (!is_valid (address))
   {
      result = Result::FAIL_MODIFIED;
   }

   if (result != Result::OK)
   {
      GetEntriesEmptyResponse resp;
      resp.code = result;
      payload   = Common::ByteArray (resp.size ());
      resp.pack (payload);
   }

   return result;
}

// =============================================================================
// AbstractServer::check_offset
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result AbstractServer::check_offset (uint16_t offset, uint8_t &count, uint16_t size) const
{
   if (offset >= size)
   {
      return Common::Result::FAIL_ARG;
   }
   else if (offset + count >= size)
   {
      count = size - offset;
   }

   return Common::Result::OK;
}

// =============================================================================
// AbstractServer::payload_size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t AbstractServer::payload_size (CMD cmd) const
{
   switch (cmd)
   {
      case GET:
         return GetEntriesMessage::min_size;

      case START:
      case END:
      default:
         return 0;
   }
}
