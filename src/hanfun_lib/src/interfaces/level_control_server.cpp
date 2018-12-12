// =============================================================================
/*!
 * @file       src/interfaces/level_control_server.cpp
 *
 * This file contains the implementation of the Level Control interface : Server role.
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

#include "hanfun/interfaces/level_control.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::LevelControl;

// =============================================================================
// Level Control Interface : Server Role
// =============================================================================

// =============================================================================
// Server::level
// =============================================================================
/*!
 *
 */
// =============================================================================
uint8_t Server::level ()
{
   return this->_level;
}

// =============================================================================
// Server::level
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::level (uint8_t __level)
{
   uint8_t old = this->_level;

   this->_level = __level;

   Level old_attr (old, this);
   Level new_attr (this->_level, this);

   notify (old_attr, new_attr);
}

// =============================================================================
// Server::level
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::level (float new_level)
{
   check_and_fix (new_level);
   uint8_t value = HF::Common::from_percent <uint8_t>(new_level);
   level (value);
}

// =============================================================================
// Server::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Server::handle_attribute (Protocol::Packet &packet, Common::ByteArray &payload,
                                         uint16_t offset)
{
   uint8_t old_level     = level ();

   Common::Result result = AbstractInterface::handle_attribute (packet, payload, offset);

   if (result == Common::Result::OK && packet.message.type == Protocol::Message::SET_ATTR_REQ)
   {
      level_change (packet.source, old_level, level ());
   }

   return result;
}

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
   Message level_msg;

   if (packet.message.itf.member != LevelControl::SET_LEVEL_CMD)
   {
      return Common::Result::FAIL_SUPPORT;
   }

   level_msg.unpack (payload, offset);

   uint8_t old_value = level ();
   level (level_msg.level);

   level_change (packet.source, old_value, level_msg.level);

   return Common::Result::OK;
}

// =============================================================================
// Server::level_change
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::level_change (Protocol::Address &source, uint8_t old_level, uint8_t new_level)
{
   UNUSED (source);
   UNUSED (old_level);
   UNUSED (new_level);
}
