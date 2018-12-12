// =============================================================================
/*!
 * @file       src/interfaces/simple_power_meter.cpp
 *
 * This file contains the implementation of the common functionality for the
 * Simple Power Meter interface.
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

#include "hanfun/interfaces/simple_power_meter.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::SimplePowerMeter;

// =============================================================================
// SimplePowerMeter / Report
// =============================================================================

Report::Report()
{
   memset (&energy, 0, sizeof(Measurement));          // Energy measurement.

   memset (&last_energy, 0, sizeof(Measurement));     // Energy measurement at last reset.
   memset (&last_time, 0, sizeof(Measurement));       // Device time measurement at last reset.

   memset (&power, 0, sizeof(Measurement));           // Instantaneous Power measurement.
   memset (&avg_power, 0, sizeof(Measurement));       // Average Power measurement.

   avg_power_interval = 0;                              // Average Power Interval.

   power_factor       = 0;                              // Power Factor.

   memset (&voltage, 0, sizeof(Measurement));         // Voltage measurement.
   memset (&current, 0, sizeof(Measurement));         // Current measurement.
   memset (&frequency, 0, sizeof(Measurement));       // Frequency measurement.

   std::fill (enabled.begin (), enabled.end (), false);
}

// =============================================================================
// Report::size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::size () const
{
   uint16_t result = min_size;

   if (enabled[ENERGY_ATTR])
   {
      result += (sizeof(uint8_t) + energy.size ()); // Energy measurement.
   }

   if (enabled[ENERGY_AT_RESET_ATTR])
   {
      result += (sizeof(uint8_t) + last_energy.size ()); // Energy measurement at last reset.
   }

   if (enabled[TIME_AT_RESET_ATTR])
   {
      result += (sizeof(uint8_t) + last_time.size ());   // Device time measurement at last reset.
   }

   if (enabled[POWER_ATTR])
   {
      result += (sizeof(uint8_t) + power.size ());     // Instantaneous Power measurement.
   }

   if (enabled[AVG_POWER_ATTR])
   {
      result += (sizeof(uint8_t) + avg_power.size ()); // Average Power measurement.
   }

   if (enabled[AVG_POWER_INTERVAL_ATTR])
   {
      result += (sizeof(uint8_t) + sizeof(avg_power_interval)); // Average Power Interval.
   }

   if (enabled[POWER_FACTOR_ATTR])
   {
      result += (sizeof(uint8_t) + sizeof(power_factor)); // Power Factor.
   }

   if (enabled[VOLTAGE_ATTR])
   {
      result += (sizeof(uint8_t) + voltage.size ()); // Voltage measurement.
   }

   if (enabled[CURRENT_ATTR])
   {
      result += (sizeof(uint8_t) + current.size ()); // Current measurement.
   }

   if (enabled[FREQUENCY_ATTR])
   {
      result += (sizeof(uint8_t) + frequency.size ()); // Frequency measurement.
   }

   return result;
}

// =============================================================================
// Report::pack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::pack (Common::ByteArray &array, uint16_t offset) const
{
   SERIALIZABLE_CHECK (array, offset, size ());

   uint16_t start = offset;

   uint8_t  id    = 0;

   // Number of attributes.

   id      = std::count (enabled.begin (), enabled.end (), true);
   offset += array.write (offset, id);

   // Energy measurement.
   id = static_cast <uint8_t>(ENERGY_ATTR);

   if (enabled[id])
   {
      offset += array.write (offset, id);
      offset += energy.pack (array, offset);
   }

   // Energy measurement at last reset.
   id = static_cast <uint8_t>(ENERGY_AT_RESET_ATTR);

   if (enabled[id])
   {
      offset += array.write (offset, id);
      offset += last_energy.pack (array, offset);
   }

   // Device time measurement at last reset.
   id = static_cast <uint8_t>(TIME_AT_RESET_ATTR);

   if (enabled[id])
   {
      offset += array.write (offset, id);
      offset += last_time.pack (array, offset);
   }

   // Instantaneous Power measurement.
   if (enabled[id])
   {
      id      = static_cast <uint8_t>(POWER_ATTR);
      offset += array.write (offset, id);
      offset += power.pack (array, offset);
   }

   // Average Power measurement.
   if (enabled[id])
   {
      id      = static_cast <uint8_t>(AVG_POWER_ATTR);
      offset += array.write (offset, id);
      offset += avg_power.pack (array, offset);
   }

   // Average Power Interval.
   if (enabled[id])
   {
      id      = static_cast <uint8_t>(AVG_POWER_INTERVAL_ATTR);
      offset += array.write (offset, id);
      offset += array.write (offset, avg_power_interval);
   }

   // Power Factor.
   id = static_cast <uint8_t>(POWER_FACTOR_ATTR);

   if (enabled[id])
   {
      offset += array.write (offset, id);
      offset += array.write (offset, power_factor);
   }

   // Voltage measurement.
   id = static_cast <uint8_t>(VOLTAGE_ATTR);

   if (enabled[id])
   {
      offset += array.write (offset, id);
      offset += voltage.pack (array, offset);
   }

   // Current measurement.
   id = static_cast <uint8_t>(CURRENT_ATTR);

   if (enabled[id])
   {
      offset += array.write (offset, id);
      offset += current.pack (array, offset);
   }

   // Frequency measurement.
   id = static_cast <uint8_t>(FREQUENCY_ATTR);

   if (enabled[id])
   {
      offset += array.write (offset, id);
      offset += frequency.pack (array, offset);
   }

   return offset - start;
}

// =============================================================================
// Report::unpack
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Report::unpack (const Common::ByteArray &array, uint16_t offset)
{
   SERIALIZABLE_CHECK (array, offset, min_size);

   uint16_t start      = offset;

   uint8_t  attr_count = 0;

   offset += array.read (offset, attr_count);  //! @todo Should check attribute count.
   assert (attr_count <= __LAST_ATTR__);

   for (uint8_t i = 0; i < attr_count; i++)
   {
      uint8_t  id    = 0;
      uint16_t _size = sizeof(id);

      assert (array.available (offset, _size));

      if (!array.available (offset, _size))
      {
         break;
      }

      offset += array.read (offset, id);

      if (id < ENERGY_ATTR || id > __LAST_ATTR__)
      {
         break;
      }

      _size = Measurement::min_size;

      if (id == AVG_POWER_INTERVAL_ATTR)
      {
         _size = sizeof(avg_power_interval);
      }
      else if (id == AVG_POWER_INTERVAL_ATTR)
      {
         _size = sizeof(power_factor);
      }

      // Not enough data to read attribute.
      assert (array.available (offset, _size));

      if (!array.available (offset, min_size))
      {
         offset -= sizeof(id);
         break;
      }

      enabled[id] = true;

      switch (id)
      {
         case ENERGY_ATTR:   // Energy Attribute ID.
            offset += energy.unpack (array, offset);
            break;
         case ENERGY_AT_RESET_ATTR:   // Energy at Last Reset Attribute ID.
            offset += last_energy.unpack (array, offset);
            break;
         case TIME_AT_RESET_ATTR:   // Time at Last Reset Attribute ID.
            offset += last_time.unpack (array, offset);
            break;
         case POWER_ATTR:   // Instantaneous Power Attribute ID.
            offset += power.unpack (array, offset);
            break;
         case AVG_POWER_ATTR:   // Average Power Attribute ID.
            offset += avg_power.unpack (array, offset);
            break;
         case AVG_POWER_INTERVAL_ATTR:   // Average Power Interval Attribute ID.
            offset += array.read (offset, avg_power_interval);
            break;
         case VOLTAGE_ATTR:   // Voltage Attribute ID.
            offset += voltage.unpack (array, offset);
            break;
         case CURRENT_ATTR:   // Current Attribute ID.
            offset += current.unpack (array, offset);
            break;
         case FREQUENCY_ATTR:   // Frequency Attribute ID.
            offset += frequency.unpack (array, offset);
            break;
         case POWER_FACTOR_ATTR:   // Power Factor Attribute ID.
            offset += array.read (offset, power_factor);
            break;
         default:
            break;
      }
   }

   return offset - start;
}

// =============================================================================
// SimplePowerMeter::create_attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::IAttribute *SimplePowerMeter::create_attribute (uint8_t uid)
{
   return Interfaces::create_attribute ((SimplePowerMeter::Server *) nullptr, uid);
}
