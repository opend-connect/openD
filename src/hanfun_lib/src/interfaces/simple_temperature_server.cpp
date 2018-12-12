// =============================================================================
/*!
 * @file       src/interfaces/simple_temperature_server.cpp
 *
 * This file contains the implementation of the Simple Temperature interface : Server role.
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

#include "hanfun/interfaces/simple_temperature.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::SimpleTemperature;

// =============================================================================
// Simple Temperature Interface : Server Role
// =============================================================================

// =============================================================================
// Server::temperature
// =============================================================================
/*!
 *
 */
// =============================================================================
int16_t Server::temperature ()
{
   return _value;
}

// =============================================================================
// Server::set_temperature
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::temperature (int16_t __value)
{
   uint8_t old = this->_value;

   this->_value = __value;

   Temperature old_attr (old, this);
   Temperature new_attr (this->_value, this);

   notify (old_attr, new_attr);
}

// =============================================================================
// Server::minimum_temperature
// =============================================================================
/*!
 *
 */
// =============================================================================
int16_t Server::minimum_temperature ()
{
   return _minimum;
}

// =============================================================================
// Server::maximum_temperature
// =============================================================================
/*!
 *
 */
// =============================================================================
int16_t Server::maximum_temperature ()
{
   return _maximum;
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
      SimpleTemperature::VALUE_ATTR,
      SimpleTemperature::MINIMUM_ATTR,
      SimpleTemperature::MAXIMUM_ATTR,
      SimpleTemperature::TOLERANCE_ATTR,
   });
   /* *INDENT-ON* */
}
