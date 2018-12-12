// =============================================================================
/*!
 * @file       src/core/session_manangement_client.cpp
 *
 * This file contains the implementation of the session management functionality
 * for the client side.
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
// AbstractClient::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result AbstractClient::handle_command (CMD cmd, Protocol::Packet &packet,
                                               Common::ByteArray &payload, uint16_t offset)
{
   UNUSED (packet);

   switch (cmd)
   {
      case START:
      {
         StartResponse response;
         response.unpack (payload, offset);
         session_started (response);
         break;
      }
      case END:
      {
         Protocol::Response response;
         response.unpack (payload, offset);
         session_ended (response);
         break;
      }
      default:
      {
         return Result::FAIL_SUPPORT;
      }
   }

   return Result::OK;
}

// =============================================================================
// AbstractServer::payload_size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t AbstractClient::payload_size (CMD cmd) const
{
   switch (cmd)
   {
      case GET:
         return GetEntriesMessage::min_size;

      case START:
         return StartResponse::min_size;

      case END:
         return Protocol::Response::min_size;

      default:
         return 0;

         break;
   }
}
