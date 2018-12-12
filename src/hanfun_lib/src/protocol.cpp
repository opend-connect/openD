// =============================================================================
/*!
 * @file       src/protocol.cpp
 *
 * This file contains the implementation of the classes for the protocol layer
 * in the HAN-FUN specification.
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

#include "hanfun/transport.h"
#include "hanfun/protocol.h"
#include "hanfun/interface.h"

#include "hanfun/transport.h"

using namespace HF;
using namespace HF::Protocol;

// =============================================================================
// Address
// =============================================================================

// =============================================================================
// Address::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Address::size () const
{
   return min_size;
}

// =============================================================================
// Message::Address::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Address::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t dev = ((this->mod & 0x01) << 15) | (this->device & BROADCAST_ADDR);

   offset += array.write (offset, dev);

   array.write (offset, unit);

   return min_size;
}

// =============================================================================
// Message::Address::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Address::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t dev;

   offset      += array.read (offset, dev);

   this->mod    = (dev & ~BROADCAST_ADDR) >> 15;
   this->device = dev & BROADCAST_ADDR;

   array.read (offset, this->unit);

   return min_size;
}

// =============================================================================
// Message / Interface
// =============================================================================

// =============================================================================
// Message::Interface::::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Message::Interface::size () const
{
   return min_size;
}

// =============================================================================
// Message::Interface::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Message::Interface::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += Common::Interface::pack (array, offset);

   array.write (offset, this->member);

   return min_size;
}

// =============================================================================
// Message::Interface::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Message::Interface::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += Common::Interface::unpack (array, offset);

   array.read (offset, this->member);

   return min_size;
}

// =============================================================================
// Message
// =============================================================================

Message::Message(const Message &parent, uint16_t size):reference (parent.reference),
   itf (parent.itf), payload (Common::ByteArray (size)), length (0)
{
   assert (size <= MAX_PAYLOAD);

   switch (parent.type)
   {
      case COMMAND_REQ:
      case COMMAND_RESP_REQ:
         type = COMMAND_RES;
         break;
      case GET_ATTR_REQ:
         type = GET_ATTR_RES;
         break;
      case SET_ATTR_REQ:
      case SET_ATTR_RESP_REQ:
         type = SET_ATTR_RES;
         break;
      case GET_ATTR_PACK_REQ:
         type = GET_ATTR_PACK_RES;
         break;
      case SET_ATTR_PACK_REQ:
      case SET_ATTR_PACK_RESP_REQ:
         type = SET_ATTR_PACK_RES;
         break;
      case ATOMIC_SET_ATTR_PACK_REQ:
      case ATOMIC_SET_ATTR_PACK_RESP_REQ:
         type = ATOMIC_SET_ATTR_PACK_RES;
         break;
      case COMMAND_RES:
      case SET_ATTR_RES:
      case GET_ATTR_RES:
      case GET_ATTR_PACK_RES:
      case SET_ATTR_PACK_RES:
      case ATOMIC_SET_ATTR_PACK_RES:
      default:
         type = parent.type;
         break;
   }
}

// =============================================================================
// Message::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Message::size () const
{
   assert (payload.size () <= MAX_PAYLOAD);
   return min_size + payload.size ();  // Payload Length.
}

// =============================================================================
// Message::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Message::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   // Application Reference.
   offset += array.write (offset, this->reference);

   // Message Type.
   offset += array.write (offset, static_cast <uint8_t>(this->type));

   // Interface Address.
   offset += itf.pack (array, offset);

   // Payload Length.
   assert (payload.size () <= MAX_PAYLOAD);
   offset += array.write (offset, (uint16_t) payload.size ());

   assert (array.available (offset, payload.size ()));

   std::copy (payload.begin (), payload.end (), array.begin () + offset);

   offset += payload.size ();

   return offset - start;
}

// =============================================================================
// Message::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Message::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start = offset;

   // Application Reference.
   offset += array.read (offset, this->reference);

   // Message Type.
   uint8_t type = 0;
   offset    += array.read (offset, type);
   this->type = static_cast <Type>(type);

   // Interface Address
   offset += itf.unpack (array, offset);

   // Payload Length.
   offset += array.read (offset, this->length);
   assert (this->length <= MAX_PAYLOAD);

   assert (array.available (offset, this->length));

   return offset - start;
}

// =============================================================================
// Response
// =============================================================================

// =============================================================================
// Response::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Response::size () const
{
   return min_size;
}

// =============================================================================
// Response::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Response::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   array.write (offset, static_cast <uint8_t>(this->code));

   return min_size;
}

// =============================================================================
// Response::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Response::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint8_t code = 0;
   offset    += array.read (offset, code);

   this->code = static_cast <Common::Result>(code);

   return min_size;
}

// =============================================================================
// Packet
// =============================================================================

// =============================================================================
// Packet::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Packet::size () const
{
   return header_min_size +    // Protocol header size.
          message.size ();     // Message payload size.
}

// =============================================================================
// Packet::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Packet::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += source.pack (array, offset);
   offset += destination.pack (array, offset);

   uint16_t transport = 0;
   offset += array.write (offset, transport);

   offset += message.pack (array, offset);

   return offset - start;
}

// =============================================================================
// Packet::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Packet::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start = offset;

   offset += source.unpack (array, offset);
   offset += destination.unpack (array, offset);

   uint16_t transport = 0;
   offset += array.read (offset, transport);

   offset += message.unpack (array, offset);

   return offset - start;
}

// =============================================================================
// Attributes API
// =============================================================================

// =============================================================================
// GetAtrributePack::Response
// =============================================================================

// =============================================================================
// GetAttributePack::Response::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t GetAttributePack::Response::size () const
{
   uint16_t result = min_size;

   /* *INDENT-OFF* */
   std::for_each (attributes.begin(), attributes.end(),
                  [&result](HF::Attributes::IAttribute *attr)
   {
      result += attr->size(true);
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// GetAttributePack::Response::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t GetAttributePack::Response::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += Protocol::Response::pack (array, offset);

   offset += array.write (offset, (uint8_t) attributes.size ());

   /* *INDENT-OFF* */
   std::for_each (attributes.begin(), attributes.end(),
                  [&array, &offset] (HF::Attributes::IAttribute * attr)
   {
      offset += attr->pack(array, offset, true);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// GetAttributePack::Response::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t GetAttributePack::Response::unpack (const Common::ByteArray &array, uint16_t offset)
{
   // Attribute factory MUST be present for unpacking to happen.
   assert (attribute_factory != nullptr);

   if (attribute_factory == nullptr)
   {
      return 0;
   }

   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start = offset;

   offset += Protocol::Response::unpack (array, offset);
   offset += array.read (offset, count);

   for (uint8_t i = 0; i < count; i++)
   {
      uint8_t uid;

      if (!array.available (offset, sizeof(uid)))
      {
         break;
      }

      offset += array.read (offset, uid);

      HF::Attributes::IAttribute *attr = attribute_factory (uid);

      if (attr == nullptr)
      {
         break;
      }

      if (!array.available (offset, attr->size ()))
      {
         break;
      }

      offset += attr->unpack (array, offset);

      attributes.push_back (attr);
   }

   return offset - start;
}

// =============================================================================
// SetAttributePack::Request
// =============================================================================

SetAttributePack::Request::~Request()
{
   /* *INDENT-OFF* */
   std::for_each(attributes.begin(), attributes.end(),
                 [](HF::Attributes::IAttribute *attr)
   {
      delete attr;
   });
   /* *INDENT-ON* */
}

// =============================================================================
// SetAttributePack::Request::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t SetAttributePack::Request::size () const
{
   uint16_t result = min_size;

   /* *INDENT-OFF* */
   std::for_each ( attributes.begin(), attributes.end(),
                   [&result](HF::Attributes::IAttribute * attr)
   {
      result += attr->size(true);
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// SetAttributePack::Request::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t SetAttributePack::Request::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += array.write (offset, (uint8_t) attributes.size ());

   /* *INDENT-OFF* */
   std::for_each (attributes.begin (), attributes.end (),
                  [&array,&offset](HF::Attributes::IAttribute * attr)
   {
      offset += attr->pack (array, offset, true);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// SetAttributePack::Request::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t SetAttributePack::Request::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   array.read (offset, count);

   return min_size;
}

// =============================================================================
// SetAttributePack::Response::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t SetAttributePack::Response::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += array.write (offset, (uint8_t) results.size ());

   /* *INDENT-OFF* */
   std::for_each (results.begin (), results.end (), [&array,&offset](Result result)
   {
      offset += result.pack (array, offset);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// SetAttributePack::Response::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t SetAttributePack::Response::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start = offset;

   offset += array.read (offset, count);

   Result result;

   for (int i = 0; i < count; i++)
   {
      if (!array.available (offset, Result::min_size))
      {
         break;
      }

      offset += result.unpack (array, offset);

      results.push_back (result);
   }

   return offset - start;
}

// =============================================================================
// Filters Classes
// =============================================================================

// =============================================================================
// Filters::ResponseRequired::operator ()
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Filters::ResponseRequired::operator ()(const HF::Protocol::Packet &packet)
{
   if (response (packet.message.type))
   {
      Entry temp (packet);
      db.push_front (temp);
      return false;
   }

   assert (packet.link != nullptr);

   uint16_t address = (packet.source.device == Protocol::BROADCAST_ADDR ? packet.link->address () :
                                                                          packet.source.device);

   assert (address != Protocol::BROADCAST_ADDR);

   /* *INDENT-OFF* */
   auto it = std::find_if (db.begin(), db.end(), [address, &packet](const Entry entry)
   {
      return (entry.address == address) && (entry.itf == packet.message.itf) &&
              matches (entry.type, packet.message.type);
   });
   /* *INDENT-ON* */

   if (it != db.end ())
   {
      db.erase (it);
      return false;
   }

   if (request (packet.message.type, true))
   {
      return true;
   }

   return false;
}

// =============================================================================
// Helper Functions
// =============================================================================

// =============================================================================
// Protocol::request
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Protocol::request (Message::Type type, bool response)
{
   switch (type)
   {
      case Message::Type::COMMAND_RESP_REQ:
      case Message::Type::SET_ATTR_RESP_REQ:
      case Message::Type::SET_ATTR_PACK_RESP_REQ:
      case Message::Type::ATOMIC_SET_ATTR_PACK_RESP_REQ:
      {
         response = false;
      }
      case Message::Type::COMMAND_REQ:
      case Message::Type::GET_ATTR_REQ:
      case Message::Type::SET_ATTR_REQ:
      case Message::Type::GET_ATTR_PACK_REQ:
      case Message::Type::SET_ATTR_PACK_REQ:
      case Message::Type::ATOMIC_SET_ATTR_PACK_REQ:
      {
         return !response;
      }
      case Message::Type::COMMAND_RES:
      case Message::Type::SET_ATTR_RES:
      case Message::Type::GET_ATTR_RES:
      case Message::Type::GET_ATTR_PACK_RES:
      case Message::Type::SET_ATTR_PACK_RES:
      case Message::Type::ATOMIC_SET_ATTR_PACK_RES:
      default:
         return false;
   }
}

// =============================================================================
// Protocol::responce
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Protocol::response (Message::Type type)
{
   switch (type)
   {
      case Message::Type::COMMAND_REQ:
      case Message::Type::COMMAND_RESP_REQ:
      case Message::Type::GET_ATTR_REQ:
      case Message::Type::SET_ATTR_REQ:
      case Message::Type::SET_ATTR_RESP_REQ:
      case Message::Type::GET_ATTR_PACK_REQ:
      case Message::Type::SET_ATTR_PACK_REQ:
      case Message::Type::SET_ATTR_PACK_RESP_REQ:
      case Message::Type::ATOMIC_SET_ATTR_PACK_REQ:
      case Message::Type::ATOMIC_SET_ATTR_PACK_RESP_REQ:
      {
         return false;
      }
      case Message::Type::COMMAND_RES:
      case Message::Type::SET_ATTR_RES:
      case Message::Type::GET_ATTR_RES:
      case Message::Type::GET_ATTR_PACK_RES:
      case Message::Type::SET_ATTR_PACK_RES:
      case Message::Type::ATOMIC_SET_ATTR_PACK_RES:
      {
         return true;
      }
      default:
         return false;
   }
}


// =============================================================================
// Protocol::response
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Protocol::matches (Message::Type lhs, Message::Type rhs)
{
   if (lhs == rhs)
   {
      return false;
   }

   switch (lhs)
   {
      case Message::Type::COMMAND_REQ:
      case Message::Type::COMMAND_RESP_REQ:
      {
         return (rhs == Message::Type::COMMAND_RES);
      }
      case Message::Type::COMMAND_RES:
      {
         return (rhs == Message::Type::COMMAND_REQ ||
                 rhs == Message::Type::COMMAND_RESP_REQ);
      }

      case Message::Type::GET_ATTR_REQ:
      {
         return (rhs == Message::Type::GET_ATTR_RES);
      }
      case Message::Type::GET_ATTR_RES:
      {
         return (rhs == Message::Type::GET_ATTR_REQ);
      }

      case Message::Type::SET_ATTR_REQ:
      case Message::Type::SET_ATTR_RESP_REQ:
      {
         return (rhs == Message::Type::SET_ATTR_RES);
      }
      case Message::Type::SET_ATTR_RES:
      {
         return (rhs == Message::Type::SET_ATTR_REQ ||
                 rhs == Message::Type::SET_ATTR_RESP_REQ);
      }

      case Message::Type::GET_ATTR_PACK_REQ:
      {
         return (rhs == Message::Type::GET_ATTR_PACK_RES);
      }
      case Message::Type::GET_ATTR_PACK_RES:
      {
         return (rhs == Message::Type::GET_ATTR_PACK_REQ);
      }

      case Message::Type::SET_ATTR_PACK_REQ:
      case Message::Type::SET_ATTR_PACK_RESP_REQ:
      {
         return (rhs == Message::Type::SET_ATTR_PACK_RES);
      }
      case Message::Type::SET_ATTR_PACK_RES:
      {
         return (rhs == Message::Type::SET_ATTR_PACK_REQ ||
                 rhs == Message::Type::SET_ATTR_PACK_RESP_REQ);
      }

      case Message::Type::ATOMIC_SET_ATTR_PACK_REQ:
      case Message::Type::ATOMIC_SET_ATTR_PACK_RESP_REQ:
      {
         return (rhs == Message::Type::ATOMIC_SET_ATTR_PACK_RES);
      }
      case Message::Type::ATOMIC_SET_ATTR_PACK_RES:
      {
         return (rhs == Message::Type::ATOMIC_SET_ATTR_PACK_REQ ||
                 rhs == Message::Type::ATOMIC_SET_ATTR_PACK_RESP_REQ);
      }
      default:
         return false;
   }
}
