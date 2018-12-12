// =============================================================================
/*!
 * @file       src/interfaces/alert.cpp
 *
 * This file contains the implementation of the common functionality for the
 * Alert interface.
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

// =============================================================================
// Alert / Message
// =============================================================================

// =============================================================================
// Alert::Message::Message
// =============================================================================
/*!
 *
 */
// =============================================================================
Alert::Message::Message(uint16_t type, uint32_t state):
   type (type), state (state)
{}

// =============================================================================
// Alert::Message::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Alert::Message::size () const
{
   return min_size;
}

// =============================================================================
// Alert::Message::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Alert::Message::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += array.write (offset, this->type);

   array.write (offset, this->state);

   return min_size;
}

// =============================================================================
// Alert::Message::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Alert::Message::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   offset += array.read (offset, this->type);

   array.read (offset, this->state);

   return min_size;
}

// =============================================================================
// Alert
// =============================================================================

// =============================================================================
// HF::Interfaces::Alert::create_attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::IAttribute *HF::Interfaces::Alert::create_attribute (uint8_t uid)
{
   return Interfaces::create_attribute (((Alert::Server *) nullptr), uid);
}
