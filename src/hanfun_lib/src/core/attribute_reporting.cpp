// =============================================================================
/*!
 * @file       src/core/attribute_reporting.cpp
 *
 * This file contains the implementation of the common functionality for the
 * Attribute Reporting service interface.
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

#include "hanfun/core/attribute_reporting.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Core;
using namespace HF::Core::AttributeReporting;

// =============================================================================
// DeviceManagement::create_attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::IAttribute *AttributeReporting::create_attribute (uint8_t uid)
{
   return Core::create_attribute ((AttributeReporting::Server *) nullptr, uid);
}

// =============================================================================
// Identifier::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Reference::size () const
{
   return min_size;
}

// =============================================================================
// Identifier::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Reference::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint8_t temp = ((type & 0x01) << 7) | (id & 0x7F);

   array.write (offset, temp);

   return min_size;
}

// =============================================================================
// Identifier::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Reference::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint8_t temp = 0;
   array.read (offset, temp);

   type = ((temp & 0x80) != 0);
   id   = temp & 0x7F;

   return min_size;
}

// =============================================================================
// Entry::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Entry::size () const
{
   return min_size;
}

// =============================================================================
// Entry::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Entry::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += array.write (offset, this->unit);

   offset += itf.pack (array, offset);

   array.write (offset, this->pack_id);

   return min_size;
}

// =============================================================================
// Entry::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Entry::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += array.read (offset, this->unit);

   offset += itf.unpack (array, offset);

   array.read (offset, this->pack_id);

   return min_size;
}

// =============================================================================
// Rule::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Rule::size () const
{
   return min_size;
}

// =============================================================================
// Rule::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Rule::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += report.pack (array, offset);

   destination.pack (array, offset);

   return min_size;
}

// =============================================================================
// Rule::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Rule::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += report.unpack (array, offset);

   destination.unpack (array, offset);

   return min_size;
}

// =============================================================================
// Periodic API
// =============================================================================

// =============================================================================
// Periodic::Entry::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Periodic::Entry::size () const
{
   uint16_t result = AttributeReporting::Entry::size ();

   if (pack_id == HF::Attributes::Pack::DYNAMIC)
   {
      result += uids.size ();
   }

   return result;
}

// =============================================================================
// Periodic::Entry::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Periodic::Entry::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += AttributeReporting::Entry::pack (array, offset);

   if (pack_id == HF::Attributes::Pack::DYNAMIC)
   {
      offset += uids.pack (array, offset);
   }

   return offset - start;
}

// =============================================================================
// Periodic::Entry::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Periodic::Entry::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start = offset;

   offset += AttributeReporting::Entry::unpack (array, offset);

   if (pack_id == HF::Attributes::Pack::DYNAMIC)
   {
      offset += uids.unpack (array, offset);
   }

   return offset - start;
}

// =============================================================================
// Periodic::Rule::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Periodic::Rule::size () const
{
   uint16_t result = min_size;

   /* *INDENT-OFF* */
   std::for_each (entries.begin(), entries.end(), [&result](const Entry &entry)
   {
      result += entry.size();
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// Periodic::Rule::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Periodic::Rule::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += AttributeReporting::Rule::pack (array, offset);

   offset += array.write (offset, interval);

   uint8_t _size = std::distance (entries.begin (), entries.end ());

   offset += array.write (offset, _size);

   /* *INDENT-OFF* */
   std::for_each (entries.begin (), entries.end (),
                  [&offset, &array](const Entry &entry)
   {
      offset += entry.pack (array, offset);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// Periodic::Rule::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Periodic::Rule::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start = offset;

   offset += AttributeReporting::Rule::unpack (array, offset);

   assert (report.type == PERIODIC);

   if (report.type != PERIODIC)
   {
      return 0;
   }

   offset += array.read (offset, interval);

   clear ();

   uint8_t size = 0;
   offset += array.read (offset, size);

   SERIALIZABLE_CHECK (array, offset, (size * Entry::min_size));

   Entry entry;

   for (uint8_t i = 0; i < size; i++)
   {
      uint16_t res = entry.unpack (array, offset);

      if (res)
      {
         add (entry);
         offset += res;
      }
      else
      {
         break;
      }
   }

   return offset - start;
}

// =============================================================================
// Event API.
// =============================================================================

// =============================================================================
// Event::Field::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Event::Field::size (bool with_uid) const
{
   uint16_t result = min_size;

   // Number of bytes in value.
   result += (type != Event::COV ? value.size () : 0);

   // Attribute UID for dynamic entries.
   if (with_uid)
   {
      result += sizeof(uint8_t);
   }

   return result;
}

// =============================================================================
// Event::Field::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Event::Field::pack (Common::ByteArray &array, uint16_t offset, bool with_uid) const
{
   SERIALIZABLE_CHECK (array, offset, size (with_uid));

   uint16_t start = offset;

   if (with_uid)
   {
      offset += array.write (offset, attr_uid);
   }

   offset += array.write (offset, (uint8_t) type);

   if (type == Event::COV)
   {
      uint8_t temp = (value.size () != 0 ? value.at (0) : 0);
      offset += array.write (offset, temp);
   }
   else
   {
      offset += array.write (offset, (uint8_t) value.size ());

      auto dst = array.begin ();
      std::advance (dst, offset);

      std::copy (value.begin (), value.end (), dst);

      offset += value.size ();
   }

   return offset - start;
}

// =============================================================================
// Event::Field::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Event::Field::unpack (const Common::ByteArray &array, uint16_t offset, bool with_uid)
{
   SERIALIZABLE_CHECK (array, offset, size (with_uid));

   uint16_t start = offset;

   if (with_uid)
   {
      offset += array.read (offset, attr_uid);
   }

   uint8_t temp = 0;
   offset += array.read (offset, temp);

   type    = static_cast <Event::Type>(temp);

   if (type == Event::COV)
   {
      temp = 1;
   }
   else
   {
      // Read value size.
      offset += array.read (offset, temp);
   }

   SERIALIZABLE_CHECK (array, offset, temp);

   auto it = array.begin ();
   std::advance (it, offset);

   value = Common::ByteArray (temp);

   std::copy_n (it, temp, value.begin ());

   offset += value.size ();

   return offset - start;
}

// =============================================================================
// Event::Entry::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Event::Entry::size () const
{
   bool attr_uid   = false;

   uint16_t result = AttributeReporting::Entry::size ();

   if (this->pack_id == HF::Attributes::Pack::DYNAMIC)
   {
      attr_uid = true;
      result  += sizeof(uint8_t);
   }
   else if (fields.size () == 0)
   {
      result += (sizeof(uint8_t) + sizeof(uint8_t));
   }

   /* *INDENT-OFF* */
   std::for_each(fields.begin(), fields.end(),
                 [&result, attr_uid](const Event::Field &field)
   {
      result += field.size(attr_uid);
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// Event::Entry::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Event::Entry::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   bool attr_uid  = false;

   offset += AttributeReporting::Entry::pack (array, offset);

   if (this->pack_id == HF::Attributes::Pack::DYNAMIC)
   {
      attr_uid = true;
      offset  += array.write (offset, (uint8_t) fields.size ());
   }
   else if (fields.size () == 0)
   {
      offset += array.write (offset, (uint8_t) COV);
      offset += array.write (offset, (uint8_t) 0);
   }

   /* *INDENT-OFF* */
   std::for_each(fields.begin(), fields.end(),
                 [&offset, &array, attr_uid](const Event::Field &field)
   {
      offset += field.pack(array, offset, attr_uid);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// Event::Entry::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Event::Entry::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start = offset;

   offset += AttributeReporting::Entry::unpack (array, offset);

   if (this->pack_id == HF::Attributes::Pack::DYNAMIC)
   {
      uint8_t _size = 0;
      offset += array.read (offset, _size);

      SERIALIZABLE_CHECK (array, offset, (_size * Event::Field::min_size));

      Event::Field field;

      for (uint8_t i = 0; i < _size; i++)
      {
         uint16_t res = field.unpack (array, offset, true);

         if (res)
         {
            fields.push_back (field);
            offset += res;
         }
         else
         {
            break;
         }
      }
   }
   else
   {
      Event::Field field;
      uint16_t res = field.unpack (array, offset, false);

      if (res)
      {
         fields.push_back (field);
         offset += res;
      }
   }

   return offset - start;
}

// =============================================================================
// Event::Rule::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Event::Rule::size () const
{
   uint16_t result = min_size;

   /* *INDENT-OFF* */
   std::for_each (entries.begin(), entries.end(), [&result](const Entry &entry)
   {
      result += entry.size();
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// Event::Rule::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Event::Rule::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += AttributeReporting::Rule::pack (array, offset);

   uint8_t _size = std::distance (entries.begin (), entries.end ());

   offset += array.write (offset, _size);

   /* *INDENT-OFF* */
   std::for_each (entries.begin (), entries.end (), [&offset, &array](const Entry &entry)
   {
      offset += entry.pack (array, offset);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// Event::Rule::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Event::Rule::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start = offset;

   offset += AttributeReporting::Rule::unpack (array, offset);

   uint8_t _size = 0;
   offset += array.read (offset, _size);

   SERIALIZABLE_CHECK (array, offset, (_size * Entry::min_size));

   Entry entry;

   for (uint8_t i = 0; i < _size; i++)
   {
      uint16_t res = entry.unpack (array, offset);

      if (res)
      {
         entries.push_front (entry);
         offset += res;
      }
      else
      {
         break;
      }
   }

   return offset - start;
}

// =============================================================================
// Report API - Notification Messages
// =============================================================================

// =============================================================================
// Report::Entry::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Entry::size () const
{
   return min_size;
}

// =============================================================================
// Report::Entry::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Entry::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += array.write (offset, unit);

   offset += itf.pack (array, offset);

   offset += array.write (offset, count ());

   return offset - start;
}

// =============================================================================
// Report::Entry::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Entry::unpack (HF::Attributes::FactoryGetter get_factory,
                                const Common::ByteArray &array, uint16_t offset)
{
   assert (get_factory != nullptr);

   if (!array.available (offset, min_size))
   {
      return 0;
   }

   uint16_t start = offset;

   offset += array.read (offset, unit);

   offset += itf.unpack (array, offset);

   uint8_t _count = 0;
   offset += array.read (offset, _count);

   HF::Attributes::Factory factory = get_factory (itf);

   assert (factory != nullptr);

   if (factory == nullptr)
   {
      goto end;
   }

   for (uint8_t i = 0; i < _count; i++)
   {
      uint16_t res = unpack (factory, array, offset);

      if (res == 0)
      {
         break;
      }

      offset += res;
   }

   end:
   return offset - start;
}

// =============================================================================
// Report::Periodic::Entry::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::Entry::size () const
{
   uint16_t result = Report::Entry::size ();

   /* *INDENT-OFF* */
   std::for_each(attributes.begin(), attributes.end(), [&result](const Attribute &attr)
   {
      result += attr->size(true);
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// Report::Periodic::Entry::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::Entry::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += Report::Entry::pack (array, offset);

   /* *INDENT-OFF* */
   std::for_each(attributes.begin(), attributes.end(), [&offset, &array](const Attribute &attr)
   {
      offset += attr->pack(array, offset, true);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// Report::Periodic::Entry::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::Entry::unpack (HF::Attributes::Factory factory,
                                          const Common::ByteArray &array, uint16_t offset)
{
   if (!array.available (offset, sizeof(uint8_t)))
   {
      return 0;
   }

   uint16_t start = offset;

   uint8_t  uid   = 0;
   offset += array.read (offset, uid);

   auto attr = factory (uid);

   assert (attr != nullptr);

   if (attr == nullptr)
   {
      return 0;
   }

   if (!array.available (offset, attr->size ()))
   {
      delete attr;
      return 0;
   }

   uint16_t _size = attr->unpack (array, offset);

   if (_size == 0)
   {
      delete attr;
      return 0;
   }

   add (attr);
   offset += _size;

   return offset - start;
}

// =============================================================================
// Report::Periodic::Entry::add
// =============================================================================
/*!
 *
 */
// =============================================================================
void Report::Periodic::Entry::add (HF::Attributes::IAttribute * &attr)
{
   attributes.push_back (Attribute (std::move (attr)));
}

// =============================================================================
// Report::Periodic::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::size () const
{
   uint16_t result = Report::Abstract::size ();

   /* *INDENT-OFF* */
   std::for_each(entries.begin(), entries.end(), [&result](const Entry &entry)
   {
      result += entry.size();
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// Report::Periodic::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += Report::Abstract::pack (array, offset);

   /* *INDENT-OFF* */
   std::for_each(entries.begin(), entries.end(), [&offset, &array](const Entry &entry)
   {
      offset += entry.pack(array, offset);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// Report::Periodic::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::unpack (HF::Attributes::FactoryGetter get_factory,
                                   const Common::ByteArray &array, uint16_t offset)
{
   if (!array.available (offset, min_size))
   {
      return 0;
   }

   uint16_t start = offset;

   offset += Report::Abstract::unpack (array, offset);

   for (Entry entry; array.available (offset, Entry::min_size); entry = Entry ())
   {
      uint16_t res = entry.unpack (get_factory, array, offset);

      if (res != 0)
      {
         add (entry);
         offset += res;
      }
      else
      {
         break;
      }
   }

   return offset - start;
}

// =============================================================================
// Report::Periodic::add
// =============================================================================
/*!
 *
 */
// =============================================================================
void Report::Periodic::add (Report::Periodic::Entry &entry)
{
   entries.push_front (std::move (entry));
}

// =============================================================================
// Report::Event
// =============================================================================

// =============================================================================
// Report::Event::Field::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::Field::size () const
{
   return min_size + (nullptr != attribute ? attribute->size (false) : 0);
}

// =============================================================================
// Report::Event::Field::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::Field::pack (Common::ByteArray &array, uint16_t offset) const
{
   assert (nullptr != attribute);

   if (nullptr == attribute)
   {
      return 0;
   }

   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += array.write (offset, (uint8_t) attribute->uid ());
   offset += array.write (offset, (uint8_t) type);

   offset += attribute->pack (array, offset);

   return offset - start;
}

// =============================================================================
// Report::Event::Field::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::Field::unpack (HF::Attributes::Factory factory,
                                       const Common::ByteArray &array, uint16_t offset)
{
   if (!array.available (offset, min_size))
   {
      return 0;
   }

   uint16_t start = offset;

   uint8_t  temp  = 0xFF;
   offset += array.read (offset, temp);   // Read Attribute UID.

   auto attr = factory (temp);

   assert (attr != nullptr);

   if (attr == nullptr)
   {
      return 0;
   }

   offset += array.read (offset, temp);   // Read Field Type.
   type    = static_cast <AttributeReporting::Event::Type>(temp);

   assert (type >= AttributeReporting::Event::COV && type <= AttributeReporting::Event::EQ);

   if (type < AttributeReporting::Event::COV || type > AttributeReporting::Event::EQ)
   {
      return 0;
   }

   if (!array.available (offset, attr->size ()))
   {
      delete attr;
      return 0;
   }

   set_attribute (attr);

   uint16_t _size = attr->unpack (array, offset);

   if (_size == 0)
   {
      set_attribute (nullptr);
      return 0;
   }

   offset += _size;

   return offset - start;
}

// =============================================================================
// Report::Event::Entry::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::Entry::size () const
{
   uint16_t result = Report::Entry::size ();

   /* *INDENT-OFF* */
   std::for_each (fields.begin (), fields.end (), [&result](const Field &field)
   {
      result += field.size ();
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// Report::Event::Entry::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::Entry::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += Report::Entry::pack (array, offset);

   /* *INDENT-OFF* */
   std::for_each (fields.begin (), fields.end (), [&offset, &array](const Field &field)
   {
      offset += field.pack (array, offset);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// Report::Event::Entry::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::Entry::unpack (HF::Attributes::Factory factory,
                                       const Common::ByteArray &array, uint16_t offset)
{
   Field field;
   uint16_t result = field.unpack (factory, array, offset);

   if (result != 0)
   {
      add (field);
   }

   return result;
}

// =============================================================================
// Report::Event::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::size () const
{
   uint16_t result = Reference::size ();

   /* *INDENT-OFF* */
   std::for_each(entries.begin(), entries.end(), [&result](const Entry &entry)
   {
      result += entry.size();
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// Report::Event::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += Report::Abstract::pack (array, offset);

   /* *INDENT-OFF* */
   std::for_each(entries.begin(), entries.end(), [&offset, &array](const Entry &entry)
   {
      offset += entry.pack(array, offset);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// Report::Event::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::unpack (HF::Attributes::FactoryGetter get_factory,
                                const Common::ByteArray &array, uint16_t offset)
{
   if (!array.available (offset, min_size))
   {
      return 0;
   }

   uint16_t start = offset;

   offset += Report::Abstract::unpack (array, offset);

   for (Entry entry; array.available (offset, Entry::min_size); entry = Entry ())
   {
      uint16_t res = entry.unpack (get_factory, array, offset);

      if (res != 0)
      {
         offset += res;
         add (entry);
      }
   }

   return offset - start;
}

// =============================================================================
// Report - Message API
// =============================================================================

// =============================================================================
// Report::CreateMessage::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::CreateMessage::size () const
{
   return min_size;
}

// =============================================================================
// Report::CreateMessage::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::CreateMessage::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   destination.pack (array, offset);

   return min_size;
}

// =============================================================================
// Report::CreateMessage::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::CreateMessage::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   destination.unpack (array, offset);

   return min_size;
}

// =============================================================================
// Report::Periodic::CreateMessage::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::CreateMessage::size () const
{
   return Report::CreateMessage::size () + sizeof(interval);
}

// =============================================================================
// Report::Periodic::CreateMessage::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::CreateMessage::pack (Common::ByteArray &array, uint16_t offset) const
{
   uint16_t start = offset;

   offset += Report::CreateMessage::pack (array, offset);

   offset += array.write (offset, interval);

   return offset - start;
}

// =============================================================================
// Report::Periodic::CreateMessage::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::CreateMessage::unpack (const Common::ByteArray &array, uint16_t offset)
{
   uint16_t start = offset;

   offset += Report::CreateMessage::unpack (array, offset);

   offset += array.read (offset, interval);

   return offset - start;
}

// =============================================================================
// Report::DeleteMessage::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::DeleteMessage::size () const
{
   return min_size;
}

// =============================================================================
// Report::DeleteMessage::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::DeleteMessage::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   report.pack (array, offset);

   return min_size;
}

// =============================================================================
// Report::DeleteMessage::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::DeleteMessage::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   report.unpack (array, offset);

   return min_size;
}

// =============================================================================
// Report::AddEntryMessage::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::AddEntryMessage::size () const
{
   return min_size;
}

// =============================================================================
// Report::AddEntryMessage::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::AddEntryMessage::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += report.pack (array, offset);

   array.write (offset, count ());

   return min_size;
}

// =============================================================================
// Report::AddEntryMessage::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::AddEntryMessage::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start = offset;

#ifndef NDEBUG
   uint8_t type = report.type;
#endif

   offset += report.unpack (array, offset);
   assert (type == report.type);

   uint8_t _count = 0;
   offset += array.read (offset, _count);

   SERIALIZABLE_CHECK (array, offset, (_count * entry_size ()));

   for (uint8_t i = 0; i < _count; i++)
   {
      uint16_t res = unpack_entry (array, offset);

      if (res)
      {
         offset += res;
      }
      else
      {
         break;
      }
   }

   return offset - start;
}

// =============================================================================
// Report::Periodic::AddEntryMessage::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::AddEntryMessage::size () const
{
   uint16_t result = Report::AddEntryMessage::size ();

   /* *INDENT-OFF* */
   std::for_each (entries.begin(), entries.end(),
                  [&result](const AttributeReporting::Periodic::Entry &entry)
   {
      result += entry.size();
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// Report::Periodic::AddEntryMessage::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::AddEntryMessage::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += Report::AddEntryMessage::pack (array, offset);

   /* *INDENT-OFF* */
   std::for_each (entries.begin(), entries.end(),
                  [&array, &offset](const AttributeReporting::Periodic::Entry &entry)
   {
      offset += entry.pack (array, offset);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// Report::Periodic::AddEntryMessage::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Periodic::AddEntryMessage::unpack_entry (const Common::ByteArray &array,
                                                          uint16_t offset)
{
   uint16_t start = offset;

   AttributeReporting::Periodic::Entry entry;

   offset += entry.unpack (array, offset);

   entries.push_front (entry);

   return offset - start;
}

// =============================================================================
// Report::Event::AddEntryMessage::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::AddEntryMessage::size () const
{
   uint16_t result = Report::AddEntryMessage::size ();

   /* *INDENT-OFF* */
   std::for_each (entries.begin(), entries.end(),
                  [&result](const AttributeReporting::Event::Entry &entry)
   {
      result += entry.size();
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// Report::Event::AddEntryMessage::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::AddEntryMessage::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   offset += Report::AddEntryMessage::pack (array, offset);

   /* *INDENT-OFF* */
   std::for_each (entries.begin(), entries.end(),
                  [&array, &offset](const AttributeReporting::Event::Entry &entry)
   {
      offset += entry.pack (array, offset);
   });
   /* *INDENT-ON* */

   return offset - start;
}

// =============================================================================
// Report::Event::AddEntryMessage::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::Event::AddEntryMessage::unpack_entry (const Common::ByteArray &array, uint16_t offset)
{
   uint16_t start = offset;

   AttributeReporting::Event::Entry entry;

   offset += entry.unpack (array, offset);

   entries.push_front (entry);

   return offset - start;
}

// =============================================================================
// process_field
// =============================================================================
/*!
 * This function receives an Event::Field, the old and new values for an
 * attribute and checks if a Report::Event::Field needs to be created.
 *
 * @param [in] field       Event::Field associated with the attribute being processed.
 * @param [in] old_value   old value for the attribute.
 * @param [in] new_value   new value for the attribute.
 *
 * @return  a pointer to Report::Event::Field object if the condition in @c filed was met,
 *          @c nullptr otherwise.
 */
// =============================================================================
static Report::Event::Field *process_field (const AttributeReporting::Event::Field &field,
                                            const HF::Attributes::IAttribute &old_value,
                                            const HF::Attributes::IAttribute &new_value)
{
   bool generate = false;

   if (field.type == Event::COV)
   {
      if (field.value[0] == 0x00)
      {
         generate = true;
      }
      else
      {
         float expected = (float) field.value[0] / 0xFF;
         float actual   = new_value.changed (old_value);

         if (expected < actual)
         {
            generate = true;
         }
      }
   }
   else
   {
      if (new_value.size (false) > field.value.size ())
      {
         return nullptr;
      }

      HF::Attributes::IAttribute *attr = old_value.clone ();
      attr->unpack (field.value, 0);

      switch (field.type)
      {
         case Event::HT:
         {
            generate = new_value > *attr;
            break;
         }
         case Event::LT:
         {
            generate = new_value < *attr;
            break;
         }
         case Event::EQ:
         {
            generate = new_value == *attr;
            break;
         }
         default:
            break;
      }

      delete attr;
   }

   if (generate)
   {
      Report::Event::Field *_field = new Report::Event::Field ();
      _field->set_attribute (new_value.clone ());
      return _field;
   }

   return nullptr;
}

// =============================================================================
// Report::Event::process
// =============================================================================
/*!
 *
 */
// =============================================================================
Report::Event::Entry *Report::Event::process (const AttributeReporting::Event::Entry &entry,
                                              const HF::Attributes::IAttribute &old_value,
                                              const HF::Attributes::IAttribute &new_value)
{
   Report::Event::Entry *result = nullptr;

   std::vector <Event::Field *> fields;

   if (entry.pack_id == HF::Attributes::DYNAMIC)
   {
      /* *INDENT-OFF* */
      std::for_each (entry.fields.begin (),entry.fields.end (),
                     [&fields, &old_value, &new_value](const AttributeReporting::Event::Field &field)
      {
         if (field.attr_uid == new_value.uid())
         {
            fields.push_back(process_field(field, old_value, new_value));
         }
      });
      /* *INDENT-ON* */
   }
   else
   {
      const HF::Interface *itf = new_value.owner ();

      assert (itf != nullptr);

      if (itf == nullptr)
      {
         return result;
      }

      HF::Attributes::UIDS expected_uids = itf->attributes (entry.pack_id);

      uint8_t actual_uid                 = new_value.uid ();

      // Find if attribute is in pack ID.
      if (std::any_of (expected_uids.begin (), expected_uids.end (),
                       [actual_uid](uint8_t uid) {return uid == actual_uid;}
                      ))
      {
         const AttributeReporting::Event::Field &field = *entry.fields.begin ();
         fields.push_back (process_field (field, old_value, new_value));
      }
   }

   if (std::any_of (fields.begin (), fields.end (),
                    [](const Event::Field *field) {return field != nullptr;}
                   ))
   {
      result = new Report::Event::Entry (entry.unit, entry.itf);

      /* *INDENT-OFF* */
      std::for_each (fields.begin (), fields.end (), [result](Event::Field *field)
      {
         if (field != nullptr)
         {
            result->add (*field);
            delete field;
         }
      });
      /* *INDENT-ON* */
   }

   return result;
}

// =============================================================================
// Message API
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
   return HF::Protocol::Response::size () + report.size ();
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
   uint16_t start = offset;

   offset += HF::Protocol::Response::pack (array, offset);

   offset += report.pack (array, offset);

   return offset - start;
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
   uint16_t start = offset;

   offset += HF::Protocol::Response::unpack (array, offset);

   offset += report.unpack (array, offset);

   return offset - start;
}

// =============================================================================
// AttributeReporting::create
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *AttributeReporting::create (Protocol::Address &destination)
{
   Report::Event::CreateMessage *create_msg = new Report::Event::CreateMessage ();

   assert (create_msg != nullptr);

   if (create_msg == nullptr)
   {
      return nullptr;
   }

   create_msg->destination = destination;

   Protocol::Message *message = new Protocol::Message (create_msg->size ());

   assert (message != nullptr);

   if (message == nullptr)
   {
      return nullptr;
   }

   create_msg->pack (message->payload);

   delete create_msg;

   message->type       = Protocol::Message::COMMAND_REQ;
   message->itf.role   = HF::Interface::SERVER_ROLE;
   message->itf.id     = HF::Interface::ATTRIBUTE_REPORTING;
   message->itf.member = AttributeReporting::CREATE_EVENT_CMD;

   return message;
}

// =============================================================================
// AttributeReporting::create
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *AttributeReporting::create (Protocol::Address &destination, uint32_t interval)
{
   Report::Periodic::CreateMessage *create_msg = new Report::Periodic::CreateMessage ();

   assert (create_msg != nullptr);

   if (create_msg == nullptr)
   {
      return nullptr;
   }

   create_msg->destination = destination;
   create_msg->interval    = interval;

   Protocol::Message *message = new Protocol::Message (create_msg->size ());

   assert (message != nullptr);

   if (message == nullptr)
   {
      return nullptr;
   }

   create_msg->pack (message->payload);

   delete create_msg;

   message->type       = Protocol::Message::COMMAND_REQ;
   message->itf.role   = HF::Interface::SERVER_ROLE;
   message->itf.id     = HF::Interface::ATTRIBUTE_REPORTING;
   message->itf.member = AttributeReporting::CREATE_PERIODIC_CMD;

   return message;
}

// =============================================================================
// AttributeReporting::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *AttributeReporting::destroy (AttributeReporting::Type type, uint8_t report_id)
{
   Reference report (type, report_id);
   return destroy (report);
}

// =============================================================================
// AttributeReporting::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *AttributeReporting::destroy (Reference report)
{
   Report::DeleteMessage *delete_msg = new Report::DeleteMessage ();
   assert (delete_msg != nullptr);

   if (delete_msg == nullptr)
   {
      return nullptr;
   }

   delete_msg->report = report;

   Protocol::Message *message = new Protocol::Message (delete_msg->size ());
   assert (message != nullptr);

   if (message == nullptr)
   {
      return nullptr;
   }

   delete_msg->pack (message->payload);

   delete delete_msg;

   message->type       = Protocol::Message::COMMAND_REQ;
   message->itf.role   = HF::Interface::SERVER_ROLE;
   message->itf.id     = HF::Interface::ATTRIBUTE_REPORTING;
   message->itf.member = AttributeReporting::DELETE_REPORT_CMD;

   return message;
}

// =============================================================================
// AttributeReporting::add
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *AttributeReporting::add (Reference report,
                                            std::vector <Periodic::Entry>::iterator begin,
                                            std::vector <Periodic::Entry>::iterator end)
{
   if (report.type != PERIODIC)
   {
      return nullptr;
   }

   Report::Periodic::AddEntryMessage *add_msg = new Report::Periodic::AddEntryMessage ();
   assert (add_msg != nullptr);

   if (add_msg == nullptr)
   {
      return nullptr;
   }

   add_msg->report = report;
   /* *INDENT-OFF* */
   std::for_each (begin, end, [add_msg](Periodic::Entry &entry)
   {
      add_msg->add (entry);
   });
   /* *INDENT-ON* */

   Protocol::Message * message = new Protocol::Message (add_msg->size ());
   assert (message != nullptr);

   if (message == nullptr)
   {
      return nullptr;
   }

   add_msg->pack (message->payload);

   delete add_msg;

   message->type       = Protocol::Message::COMMAND_REQ;
   message->itf.role   = HF::Interface::SERVER_ROLE;
   message->itf.id     = HF::Interface::ATTRIBUTE_REPORTING;
   message->itf.member = AttributeReporting::ADD_PERIODIC_ENTRY_CMD;

   return message;
}

// =============================================================================
// AttributeReporting::add
// =============================================================================
/*!
 *
 */
// =============================================================================
Protocol::Message *AttributeReporting::add (Reference report,
                                            std::vector <Event::Entry>::iterator begin,
                                            std::vector <Event::Entry>::iterator end)
{
   if (report.type != EVENT)
   {
      return nullptr;
   }

   Report::Event::AddEntryMessage *add_msg = new Report::Event::AddEntryMessage ();
   assert (add_msg != nullptr);

   if (add_msg == nullptr)
   {
      return nullptr;
   }

   add_msg->report = report;
   std::for_each (begin, end, [add_msg](const Event::Entry &entry) {
                     add_msg->add (entry);
                  }
                 );

   Protocol::Message *message = new Protocol::Message (add_msg->size ());
   assert (message != nullptr);

   if (message == nullptr)
   {
      return nullptr;
   }

   add_msg->pack (message->payload);

   delete add_msg;

   message->type       = Protocol::Message::COMMAND_REQ;
   message->itf.role   = HF::Interface::SERVER_ROLE;
   message->itf.id     = HF::Interface::ATTRIBUTE_REPORTING;
   message->itf.member = AttributeReporting::ADD_EVENT_ENTRY_CMD;

   return message;
}
