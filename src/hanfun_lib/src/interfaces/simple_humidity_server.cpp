// =============================================================================
/*!
 * @file       src/interfaces/simple_humidity_server.cpp
 *
 * This file contains the implementation of the Simple Humidity interface : Server role.
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

#include "hanfun/interfaces/simple_humidity.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::SimpleHumidity;

// =============================================================================
// Simple Humidity Interface : Server Role
// =============================================================================

// =============================================================================
// Server::humidity
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Server::humidity ()
{
   return _value;
}

// =============================================================================
// Server::set_humidity
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::humidity (uint16_t __value)
{
   uint8_t old = this->_value;

   this->_value = __value;

   Humidity old_attr (old, this);
   Humidity new_attr (this->_value, this);

   notify (old_attr, new_attr);
}

// =============================================================================
// Server::tolerance
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Server::tolerance ()
{
   return _tolerance;
}

// =============================================================================
// Server::attributes
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::UIDS Server::attributes (uint8_t pack_id) const
{
   UNUSED (pack_id);
   /* *INDENT-OFF* */
   return HF::Attributes::UIDS({
      SimpleHumidity::VALUE_ATTR,
      SimpleHumidity::TOLERANCE_ATTR,
   });
   /* *INDENT-ON* */
}
