// =============================================================================
/*!
 * @file       src/interfaces/on_off_client.cpp
 *
 * This file contains the implementation of the On-Off interface : Client role.
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
// On-Off Interface : Client Role
// =============================================================================

// =============================================================================
// Client::on
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::on (Protocol::Address &addr)
{
   Protocol::Message message;

   message.itf.role   = SERVER_ROLE;
   message.itf.id     = Client::uid ();
   message.itf.member = ON_CMD;

   send (addr, message);
}

// =============================================================================
// Client::off
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::off (Protocol::Address &addr)
{
   Protocol::Message message;

   message.itf.role   = SERVER_ROLE;
   message.itf.id     = Client::uid ();
   message.itf.member = OFF_CMD;

   send (addr, message);
}

// =============================================================================
// Client::toggle
// =============================================================================
/*!
 *
 */
// =============================================================================
void Client::toggle (Protocol::Address &addr)
{
   Protocol::Message message;

   message.itf.role   = SERVER_ROLE;
   message.itf.id     = Client::uid ();
   message.itf.member = TOGGLE_CMD;

   send (addr, message);
}
