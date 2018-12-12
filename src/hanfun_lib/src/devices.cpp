// =============================================================================
/*!
 * @file       src/devices.cpp
 *
 * This file contains the implementation of the common functionality for HAN-FUN
 * devices.
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
#include "hanfun/common.h"

#include "hanfun/protocol.h"

#include "hanfun/devices.h"

using namespace HF;
using namespace HF::Units;
using namespace HF::Devices;

// =============================================================================
// HF::AbstractDevice
// =============================================================================

// =============================================================================
// AbstractDevice::unit
// =============================================================================
/*!
 *
 */
// =============================================================================
Units::IUnit *AbstractDevice::unit (uint8_t id) const
{
   if (_units.empty ())
   {
      return nullptr;
   }

   /* *INDENT-OFF* */
   auto it = find_if(_units.begin(), _units.end(), [id](Units::IUnit *unit)
   {
      return unit->id () == id;
   });
   /* *INDENT-ON* */

   if (it == _units.end ())
   {
      return nullptr;
   }
   else
   {
      return *it;
   }
}

// =============================================================================
// AbstractDevice::send
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractDevice::send (Protocol::Packet &packet)
{
   if (is_local (packet) && is_registered ())
   {
      receive (packet, packet.message.payload, 0);
      return;
   }

   Transport::Link *tsp_link = packet.link;

   // Update message reference if it is a request.
   if (packet.source.device == address () && Protocol::request (packet.message.type, false))
   {
      packet.message.reference = this->next_reference++;
   }

   if (tsp_link == nullptr)
   {
      packet.link = tsp_link = link (packet.destination.device);
   }

   if (tsp_link != nullptr)
   {
      Common::ByteArray array (packet.size ());

      packet.pack (array);

      tsp_link->send (array);
   }

   response_filter (packet);
}

// =============================================================================
// HF::AbstractDevice::receive
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractDevice::receive (Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset)
{
   Common::Result result = Common::Result::FAIL_UNKNOWN;

   assert (nullptr != packet.link);

   if (is_local (packet))
   {
      IUnit *unit = this->unit (packet.destination.unit);

      if (unit != nullptr)
      {
         result = unit->handle (packet, payload, offset);
      }
   }

   // Send missing response.
   if (response_filter (packet))
   {
      Protocol::Message  *message = new Protocol::Message (packet.message, 0);
      Protocol::Response resp (result);
      message->payload = Common::ByteArray (resp.size ());

      resp.pack (message->payload);

      Protocol::Packet *resp_packet = new Protocol::Packet (*message);
      resp_packet->link = packet.link;

      delete message;

      send (*resp_packet);

      delete resp_packet;
   }
}

// =============================================================================
// AbstractDevice::periodic
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractDevice::periodic (uint32_t time)
{
   /* *INDENT-OFF* */
   std::for_each(units().begin(), units().end(), [time](Units::IUnit *unit)
   {
      unit->periodic(time);
   });
   /* *INDENT-ON* */
}

// =============================================================================
// HF::Devices::Node
// =============================================================================

// =============================================================================
// HF::Devices::Concentrator
// =============================================================================

// =============================================================================
// HF::Devices::Concentrator::AbstractBase
// =============================================================================

// =============================================================================
// Concentrator::AbstractBase::connected
// =============================================================================
/*!
 *
 */
// =============================================================================
void Concentrator::AbstractBase::connected (HF::Transport::Link *link)
{
   _links.push_front (link);

   // Check if a registration exists for this link.
   auto entry = unit0 ()->device_management ()->entry (link->uid ());

   if (entry != nullptr)
   {
      link->address (entry->address);
   }
}

// =============================================================================
// Concentrator::AbstractBase::disconnected
// =============================================================================
/*!
 *
 */
// =============================================================================
void Concentrator::AbstractBase::disconnected (HF::Transport::Link *link)
{
   _links.remove (link);
}

// =============================================================================
// Concentrator::AbstractBase::receive
// =============================================================================
/*!
 *
 */
// =============================================================================
void Concentrator::AbstractBase::receive (Protocol::Packet &packet, Common::ByteArray &payload,
                                          uint16_t offset)
{
   if (packet.destination.device == Protocol::BROADCAST_ADDR)
   {
      route_packet (packet, payload, offset);
   }
   else if (is_local (packet))  // The message is for us.
   {
      AbstractDevice::receive (packet, payload, offset);
   }
   else  // Route message to the proper device.
   {
      Protocol::Packet other = packet;
      other.link            = nullptr;

      other.message.payload = Common::ByteArray (payload.size () - offset);

      std::copy (payload.begin () + offset, payload.end (), other.message.payload.begin ());

      send (other);
   }
}

// =============================================================================
// Concentrator::AbstractBase::link
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Transport::Link *Concentrator::AbstractBase::link (uint16_t addr) const
{
   if (_links.empty ())
   {
      return nullptr;
   }

   /* *INDENT-OFF* */
   auto it = std::find_if(_links.begin(), _links.end(),
                          [addr](HF::Transport::Link *link)
                          {
                             return link->address () == addr;
                          });
   /* *INDENT-ON* */

   if (it == _links.end ())
   {
      return nullptr;
   }

   return *it;
}

// =============================================================================
// Concentrator::AbstractBase::route_packet
// =============================================================================
/*!
 *
 */
// =============================================================================
void Concentrator::AbstractBase::route_packet (Protocol::Packet &packet, Common::ByteArray &payload,
                                               uint16_t offset)
{
   typedef std::pair<Protocol::Address,Common::Interface> RoutePair;
   /* *INDENT-OFF* */
   static std::array<RoutePair, 8> route_pairs {{  // | Idx | Device    | Unit      | Interface |
                                                   // | --- | --------- | --------- | --------- |
     { Protocol::Address(), Common::Interface() }, // |  0  | Single    | Single    | Single    |
     { Protocol::Address(), Interface::Any()    }, // |  1  | Single    | Single    | Any       |
     { Protocol::Address(), Common::Interface() }, // |  2  | Single    | Broadcast | Single    |
     { Protocol::Address(), Interface::Any()    }, // |  3  | Single    | Broadcast | Any       |
     { Protocol::Address(), Common::Interface() }, // |  4  | Broadcast | Broadcast | Single    |
     { Protocol::Address(), Interface::Any()    }, // |  5  | Broadcast | Broadcast | Any       |
     { Protocol::Address(), Common::Interface() }, // |  6  | Broadcast | Single    | Single    |
     { Protocol::Address(), Interface::Any()    }  // |  7  | Broadcast | Single    | Any       |
   }};
   /* *INDENT-ON* */

   // Only route messages that are commands.
   if (!(packet.message.type == Protocol::Message::COMMAND_REQ ||
         packet.message.type == Protocol::Message::COMMAND_RESP_REQ))
   {
      return;
   }

   route_pairs[0].first = packet.source;
   route_pairs[0].second = packet.message.itf;

   route_pairs[1].first = packet.source;

   route_pairs[2].first.device = packet.source.device;
   route_pairs[2].second = packet.message.itf;

   route_pairs[3].first.device = packet.source.device;

   route_pairs[4].second = packet.message.itf;

   route_pairs[6].first.unit = packet.source.unit;
   route_pairs[6].second = packet.message.itf;

   route_pairs[7].first.unit = packet.source.unit;

   // Find bind entries for device.
   auto &entries = unit0 ()->bind_management ()->entries ();

   if (std::none_of (route_pairs.begin(), route_pairs.end(),
                     [&entries](const RoutePair &pair)
   {
      return entries.any_of (pair.first, pair.second);
   }))
   {
      return;
   }

   // Send packets to binded destination devices.
   Protocol::Packet other = packet;

   other.message.payload = Common::ByteArray (payload.size () - offset);

   std::copy (payload.begin () + offset, payload.end (), other.message.payload.begin ());

   auto process_entry = [this, &other, &packet](const Core::BindManagement::Entry &entry)
                        {
                           other.destination = entry.destination;
                           other.link        = this->is_local (other) ? packet.link : nullptr;
                           this->send (other);
                        };

   std::for_each(route_pairs.begin(), route_pairs.end(),
                 [&entries, &process_entry](const RoutePair &pair)
   {
      entries.for_each (pair.first, pair.second, process_entry);
   });
}

// =============================================================================
// HF::Devices::Concentrator::Transport
// =============================================================================

void Concentrator::Transport::destroy ()
{
   remove ((HF::Transport::Endpoint *) nullptr);
   remove ((HF::Transport::Link *) nullptr);
}

// =============================================================================
// HF::Devices::Concentrator::Transport::remove
// =============================================================================
/*!
 *
 */
// =============================================================================
void Concentrator::Transport::remove (HF::Transport::Link *link)
{
   if (link != nullptr)
   {
      /* *INDENT-OFF* */
      std::for_each(endpoints.begin(), endpoints.end(), [link](HF::Transport::Endpoint *ep)
      {
         ep->disconnected (link);
      });
      /* *INDENT-ON* */

      links.remove (link);

      delete link;
   }
   else
   {
      /* *INDENT-OFF* */
      std::for_each (links.begin (), links.end (), [this](HF::Transport::Link *link)
      {
         std::for_each(endpoints.begin(), endpoints.end(), [link](HF::Transport::Endpoint *ep)
         {
            ep->disconnected (link);
         });

         delete link;
      });
      /* *INDENT-ON* */

      links.clear ();
   }
}

// =============================================================================
// HF::Devices::Concentrator::Transport::find
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Transport::Link *Concentrator::Transport::find (uint16_t address)
{
   /* *INDENT-OFF* */
   auto it = std::find_if(links.begin(), links.end(),
                          [address](const HF::Transport::Link *link)
                          {
                             return link->address () == address;
                          });
   /* *INDENT-ON* */

   // Link was found.
   if (it != links.end ())
   {
      return *it;
   }

   return nullptr;
}
