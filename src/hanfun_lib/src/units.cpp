// =============================================================================
/*!
 * @file       src/units.cpp
 *
 * This file contains the implementation of the common functionality for
 * the HAN-FUN Units.
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

#include "hanfun/units.h"
#include "hanfun/devices.h"

// =============================================================================
// API
// =============================================================================

using namespace HF::Units;

// =============================================================================
// AbstractUnit::send
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractUnit::send (const Protocol::Address &addr, Protocol::Message &message,
                         Transport::Link *link)
{
   Protocol::Packet *packet = new Protocol::Packet (message);

   packet->destination   = addr;
   packet->source.device = device ().address ();
   packet->source.unit   = id ();
   packet->link          = link;

   device ().send (*packet);

   message.reference = packet->message.reference;

   delete packet;
}

// =============================================================================
// AbstractUnit::notify
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractUnit::notify (const HF::Attributes::IAttribute &old_value,
                           const HF::Attributes::IAttribute &new_value) const
{
   device ().unit0 ()->attribute_reporting ()->notify (this->id (), old_value, new_value);
}
