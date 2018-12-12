// =============================================================================
/*!
 * @file       src/common.cpp
 *
 * This file contains the implementation of the common classes and functions
 * of the HAN-FUN library.
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
#include "hanfun/interface.h"

using namespace HF;
using namespace HF::Common;

// =============================================================================
// Defines
// =============================================================================

#define BYTE_1_MASK   0x000000FF
#define BYTE_2_MASK   0x0000FF00
#define BYTE_3_MASK   0x00FF0000
#define BYTE_4_MASK   0xFF000000

// =============================================================================
// Helper Functions
// =============================================================================

// =============================================================================
// API Classes
// =============================================================================

// =============================================================================
// ByteArray
// =============================================================================

ByteArray::ByteArray(uint16_t size):std::vector <uint8_t>(size, 0)
{}

ByteArray::ByteArray(const uint8_t data[], const uint16_t size):vector (size, 0)
{
   memcpy (this->data (), data, size);
}

// =============================================================================
// ByteArray::write
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t ByteArray::write (uint16_t offset, uint8_t data)
{
   at (offset) = data;
   return sizeof(uint8_t);
}

// =============================================================================
// ByteArray::write
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t ByteArray::write (uint16_t offset, uint16_t data)
{
   at (offset)     = (data & BYTE_2_MASK) >> 8;
   at (offset + 1) = (data & BYTE_1_MASK);

   return sizeof(uint16_t);
}

// =============================================================================
// ByteArray::write
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t ByteArray::write (uint16_t offset, uint32_t data)
{
   at (offset)     = (data & BYTE_4_MASK) >> 24;
   at (offset + 1) = (data & BYTE_3_MASK) >> 16;
   at (offset + 2) = (data & BYTE_2_MASK) >> 8;
   at (offset + 3) = (data & BYTE_1_MASK);

   return sizeof(uint32_t);
}

// =============================================================================
// ByteArray::read
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t ByteArray::read (uint16_t offset, uint8_t &data) const
{
   data = at (offset);
   return sizeof(uint8_t);
}

// =============================================================================
// ByteArray::read
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t ByteArray::read (uint16_t offset, uint16_t &data) const
{
   data = ((uint16_t) at (offset)) << 8 | at (offset + 1);

   return sizeof(uint16_t);
}

// =============================================================================
// ByteArray::read
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t ByteArray::read (uint16_t offset, uint32_t &data) const
{
   data  = ((uint32_t) at (offset)) << 24;
   data |= ((uint32_t) at (offset + 1)) << 16;
   data |= ((uint32_t) at (offset + 2)) << 8;
   data |= ((uint32_t) at (offset + 3));

   return sizeof(uint32_t);
}

// =============================================================================
// Interface
// =============================================================================

// =============================================================================
// Interface::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Common::Interface::size () const
{
   return min_size;
}

// =============================================================================
// Interface::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Common::Interface::pack (ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t uid = ((this->role & 0x01) << 15) | (this->id & HF::Interface::ANY_UID);

   array.write (offset, uid);

   return min_size;
}

// =============================================================================
// Interface::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Common::Interface::unpack (const ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t uid = 0;
   array.read (offset, uid);

   this->role = (uid & ~HF::Interface::ANY_UID) >> 15;
   this->id   = uid & HF::Interface::ANY_UID;

   return min_size;
}
