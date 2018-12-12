// =============================================================================
/*!
 * @file       src/interfaces/alert_client.cpp
 *
 * This file contains the implementation of the Alert interface : Client role.
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

#include "hanfun/interfaces/alert.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::Alert;

// =============================================================================
// Alert Interface : Client Role
// =============================================================================

// =============================================================================
// Client::handle_commands
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Client::handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                       uint16_t offset)
{
   if (packet.message.itf.member != STATUS_CMD)
   {
      return Common::Result::FAIL_SUPPORT;
   }

   Message alert_msg;

   alert_msg.unpack (payload, offset);

   status (packet.source, alert_msg);

   return Common::Result::OK;
}
