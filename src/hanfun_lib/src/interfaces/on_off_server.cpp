// =============================================================================
/*!
 * @file       src/interfaces/on_off_client.cpp
 *
 * This file contains the implementation of the On-Off interface : Server role.
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

#include "hanfun/interfaces/on_off.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::OnOff;

// =============================================================================
// On-Off Interface : Server Role
// =============================================================================

// =============================================================================
// Server::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Server::handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                       uint16_t offset)
{
   UNUSED (payload);
   UNUSED (offset);

   CMD cmd = static_cast <CMD>(packet.message.itf.member);

   switch (cmd)
   {
      case ON_CMD:
         on (packet.source);
         break;
      case OFF_CMD:
         off (packet.source);
         break;
      case TOGGLE_CMD:
         toggle (packet.source);
         break;
      default:
         return Common::Result::FAIL_SUPPORT;
   }

   return Common::Result::OK;
}

// =============================================================================
// Server::on
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::on (HF::Protocol::Address &source)
{
   UNUSED (source);
   state (true);
}

// =============================================================================
// Server::off
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::off (HF::Protocol::Address &source)
{
   UNUSED (source);
   state (false);
}

// =============================================================================
// Server::toggle
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::toggle (HF::Protocol::Address &source)
{
   UNUSED (source);
   state (!state ());
}

// =============================================================================
// Server::state
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::state (bool state)
{
   bool old = this->_state;

   this->_state = state;

   State old_attr (old, this);
   State new_attr (this->_state, this);

   notify (old_attr, new_attr);
}

// =============================================================================
// Server::state
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Server::state ()
{
   return _state;
}
