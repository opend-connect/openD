// =============================================================================
/*!
 * @file       src/core/device_information_server.cpp
 *
 * This file contains the implementation of the Device Information : Server Role.
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

#include "hanfun/core/device_information.h"

using namespace HF;
using namespace HF::Core;
using namespace HF::Core::DeviceInformation;

// =============================================================================
// API
// =============================================================================

// =============================================================================
// FriendlyName::Unit::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t FriendlyName::Unit::size () const
{
   return sizeof(uint8_t) + HF::Common::SerializableHelper <std::string>::size (name);
}

// =============================================================================
// FriendlyName::Unit::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t FriendlyName::Unit::pack (HF::Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   offset += array.write (offset, id);
   HF::Common::SerializableHelper <std::string>(name).pack (array, offset);

   return size ();
}

// =============================================================================
// FriendlyName::Unit::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t FriendlyName::Unit::unpack (const HF::Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += array.read (offset, id);
   HF::Common::SerializableHelper <std::string> temp;

   if (temp.unpack (array, offset) == 0)
   {
      return 0;
   }

   name = temp.data;

   return size ();
}

// =============================================================================
// FriendlyName::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t FriendlyName::size () const
{
   uint16_t result = min_size;

   /* *INDENT-OFF* */
   std::for_each (units.begin(), units.end(), [&result](const Unit &unit)
   {
      result += unit.size();
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// FriendlyName::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t FriendlyName::pack (HF::Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint8_t _size = units.size ();
   offset += array.write (offset, _size);

   /* *INDENT-OFF* */
   std::for_each (units.begin(), units.end(), [&array, &offset](const Unit &unit)
   {
      offset += unit.pack(array, offset);
   });
   /* *INDENT-ON* */

   return size ();
}

// =============================================================================
// FriendlyName::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t FriendlyName::unpack (const HF::Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint8_t _count = 0;
   offset += array.read (offset, _count);

   SERIALIZABLE_CHECK (array, offset, (_count * Unit::min_size));

   units.reserve (_count);

   Unit unit;

   for (uint8_t i = 0; i < _count; ++i)
   {
      uint16_t res = unit.unpack (array, offset);

      if (res == 0)
      {
         return 0;
      }

      units.push_back (unit);
      offset += res;
   }

   return size ();
}

// =============================================================================
// FriendlyName::compare
// =============================================================================
/*!
 *
 */
// =============================================================================
int FriendlyName::compare (const FriendlyName &other) const
{
   int  result = units.size () - other.units.size ();

   auto it     = units.begin ();
   auto ito    = other.units.begin ();

   for (; result == 0 && it != units.end (); ++it, ++ito)
   {
      if ((result = it->id - ito->id) == 0)
      {
         result = it->name.compare (ito->name);
      }
   }

   return result;
}

// =============================================================================
// DeviceInformation::mandatory
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *DeviceInformation::mandatory ()
{
   Protocol::Message *result = new Protocol::Message ();

   result->type       = Protocol::Message::GET_ATTR_PACK_REQ;
   result->itf.id     = HF::Interface::DEVICE_INFORMATION;
   result->itf.role   = HF::Interface::SERVER_ROLE;
   result->itf.member = HF::Attributes::MANDATORY;

   return result;
}

// =============================================================================
// DeviceInformation::all
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *DeviceInformation::all ()
{
   Protocol::Message *result = new Protocol::Message ();


   result->type       = Protocol::Message::GET_ATTR_PACK_REQ;
   result->itf.id     = HF::Interface::DEVICE_INFORMATION;
   result->itf.role   = HF::Interface::SERVER_ROLE;
   result->itf.member = HF::Attributes::ALL;

   return result;
}

// =============================================================================
// DeviceInformation::get
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *DeviceInformation::get (HF::Attributes::UIDS &uids)
{
   auto *req                 = new HF::Protocol::GetAttributePack::Request (uids);

   Protocol::Message *result = new Protocol::Message ();

   result->type       = Protocol::Message::GET_ATTR_REQ;
   result->itf.id     = HF::Interface::DEVICE_INFORMATION;
   result->itf.role   = HF::Interface::SERVER_ROLE;
   result->itf.member = HF::Attributes::DYNAMIC;

   req->pack (result->payload);

   delete req;

   return result;
}

// =============================================================================
// DeviceInformation::get
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *DeviceInformation::get (uint8_t uid)
{
   Protocol::Message *result = new Protocol::Message ();

   result->type       = Protocol::Message::GET_ATTR_REQ;
   result->itf.id     = HF::Interface::DEVICE_INFORMATION;
   result->itf.role   = HF::Interface::SERVER_ROLE;
   result->itf.member = uid;

   return result;
}

// =============================================================================
// DeviceInformation::Server::attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::IAttribute *DeviceInformation::Server::attribute (uint8_t uid)
{
   HF::Attributes::UIDS uids = attributes(HF::Attributes::Pack::ALL);
   if (std::any_of (uids.begin(), uids.end(),
                    [uid] (uint8_t attr_uid) { return uid == attr_uid; }))
   {
      return Core::create_attribute (this, uid);
   }
   else
   {
      return nullptr;
   }
}

// =============================================================================
// DeviceInformation::Server::attributes
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::UIDS DeviceInformation::Server::attributes (uint8_t pack_id) const
{
   HF::Attributes::UIDS result;

   switch (pack_id)
   {
      case HF::Attributes::Pack::ALL:
      {
         result.push_back (UID_ATTR);
         result.push_back (EMC_ATTR);
      }
      case HF::Attributes::Pack::MANDATORY:
      {
         result.push_back (EXTRA_CAP_ATTR);
         result.push_back (INTERFACE_VERSION_ATTR);
         result.push_back (PROFILE_VERSION_ATTR);
         result.push_back (CORE_VERSION_ATTR);
         break;
      }
      default:
         break;
   }

   std::reverse (result.begin (), result.end ());

   return result;
}

// =============================================================================
// DeviceInformation::create_attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::IAttribute *DeviceInformation::create_attribute (uint8_t uid)
{
   return Core::create_attribute ((DeviceInformation::Server *) nullptr, uid);
}

// =============================================================================
// DeviceInformation::Server::paging
// =============================================================================
/*!
 *
 */
// =============================================================================
void DeviceInformation::Server::paging (bool value)
{
   if (value)
   {
      capabilities (capabilities () | (value << 0));
   }
   else
   {
      capabilities (capabilities () & (~(1 << 0)));
   }
}

// =============================================================================
// DeviceInformation::Server::has_paging
// =============================================================================
/*!
 *
 */
// =============================================================================
bool DeviceInformation::Server::has_paging () const
{
   return (_capabilities & (1 << 0)) != 0;
}

// =============================================================================
// DeviceInformation::Server::broadcast
// =============================================================================
/*!
 *
 */
// =============================================================================
void DeviceInformation::Server::broadcast (bool value)
{
   if (value)
   {
      capabilities (capabilities () | (value << 1));
   }
   else
   {
      capabilities (capabilities () & (~(1 << 1)));
   }
}

// =============================================================================
// DeviceInformation::Server::has_broadcast
// =============================================================================
/*!
 *
 */
// =============================================================================
bool DeviceInformation::Server::has_broadcast () const
{
   return (_capabilities & (1 << 1)) != 0;
}

// =============================================================================
// DeviceInformation::Server::capabilities
// =============================================================================
/*!
 *
 */
// =============================================================================
void DeviceInformation::Server::capabilities (uint8_t value)
{
   auto old_value = new HF::Attributes::Attribute <uint8_t>(HF::Interface::DEVICE_INFORMATION,
                                                            EXTRA_CAP_ATTR, this, _capabilities);

   this->_capabilities = value;

   auto new_value = create_attribute (EXTRA_CAP_ATTR);

   notify (*old_value, *new_value);

   delete old_value;
   delete new_value;
}

// =============================================================================
// DeviceInformation::Server::capabilities
// =============================================================================
/*!
 *
 */
// =============================================================================
uint8_t DeviceInformation::Server::capabilities ()
{
   return _capabilities;
}
