// =============================================================================
/*!
 * @file       src/core/bind_management.cpp
 *
 * This file contains the implementation of the common functionality for the
 * Bind Management core interface.
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

#include "hanfun/interface.h"
#include "hanfun/core/bind_management.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Core;
using namespace HF::Core::BindManagement;

// =============================================================================
// BindManagement::create_attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::IAttribute *BindManagement::create_attribute (uint8_t uid)
{
   return Core::create_attribute ((BindManagement::IServer *) nullptr, uid);
}

// =============================================================================
// BindManagement::Entry
// =============================================================================

// =============================================================================
// BindManagement::Entry::size
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
// BindManagement::Entry::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Entry::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += this->source.pack (array, offset);

   offset += this->itf.pack (array, offset);

   this->destination.pack (array, offset);

   return min_size;
}

// =============================================================================
// BindManagement::Entry::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Entry::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += this->source.unpack (array, offset);

   offset += this->itf.unpack (array, offset);

   this->destination.unpack (array, offset);

   return min_size;
}

// =============================================================================
// BindManagement::Entries
// =============================================================================

// =============================================================================
// Entries::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Entries::size () const
{
   return this->db.size ();
}

// =============================================================================
// Entries::save
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Entries::save (const Entry &entry)
{
   auto res              = this->db.insert (entry);

   Common::Result result = Common::Result::FAIL_ARG;

   if (res.second)
   {
      result = Common::Result::OK;
   }

   return result;
}

// =============================================================================
// Entries::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Entries::destroy (uint16_t address, Protocol::Address::Type type)
{
   /* *INDENT-OFF* */
   return destroy ([address, type](BindManagement::Entry const &entry)
   {
      if ((entry.source.device == address && entry.source.mod == type) ||
            (entry.destination.device == address && entry.destination.mod == type))
      {
         return true;
      }
      else
      {
         return false;
      }
   });
   /* *INDENT-ON* */
}

// =============================================================================
// Entries::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Entries::destroy (const Entry &entry)
{
   if (this->db.erase (entry) == 1)
   {
      return Common::Result::OK;
   }

   return Common::Result::FAIL_ARG;
}

// =============================================================================
// Entries - Query API
// =============================================================================

// =============================================================================
// Entries::find
// =============================================================================
/*!
 *
 */
// =============================================================================
EntryPtr Entries::find (const Protocol::Address &source, const Common::Interface &itf,
                        const Protocol::Address &destination) const
{
   Entry temp (source, itf, destination);

   auto  it = this->db.find (temp);

   if (it == this->db.end ())
   {
      return EntryPtr ();
   }
   else
   {
      return EntryPtr (&(*it));
   }
}

// =============================================================================
// Entries::any_of
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Entries::any_of (Protocol::Address const &source, Common::Interface const &itf) const
{
   auto range = find (source, itf);

   return range.first != db.end () || range.second != db.end ();
}

// =============================================================================
// Entries::for_each
// =============================================================================
/*!
 *
 */
// =============================================================================
void Entries::for_each (Protocol::Address const &source, Common::Interface const &itf,
                        std::function <void(const Entry &)> func) const
{
   auto range = find (source, itf);
   std::for_each (range.first, range.second, func);
}

// =============================================================================
// Entries::find
// =============================================================================
/*!
 *
 */
// =============================================================================
std::pair <Entries::iterator, Entries::iterator> Entries::find (Protocol::Address const &source,
                                                                Common::Interface const &itf) const
{
   Entry _begin (source, itf);
   Entry _end (source, itf);

   memset (&(_begin.destination), 0x00, sizeof(Protocol::Address));
   memset (&(_end.destination), 0xFF, sizeof(Protocol::Address));

   return std::make_pair (db.lower_bound (_begin), db.upper_bound (_end));
}
