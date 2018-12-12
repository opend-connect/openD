// =============================================================================
/*!
 * @file       src/interfaces/simple_power_meter_server.cpp
 *
 * This file contains the implementation of the Simple Power Meter interface :
 * Server role.
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
// SimplePowerMeter / Server
// =============================================================================

Server::Server()
{
#if HF_IFT_SPM_ENERGY_ATTR
   memset (&_energy, 0, sizeof(Measurement));          // Energy measurement.
#endif

#if HF_ITF_SPM_ENERGY_AT_RESET_ATTR
   memset (&_last_energy, 0, sizeof(Measurement));     // Energy measurement at last reset.
#endif

#if HF_ITF_SPM_TIME_AT_RESET_ATTR
   memset (&_last_time, 0, sizeof(Measurement));       // Device time measurement at last reset.
#endif

#if HF_ITF_SPM_POWER_ATTR
   memset (&_power, 0, sizeof(Measurement));           // Instantaneous Power measurement.
#endif

#if HF_ITF_SPM_AVG_POWER_ATTR
   memset (&_avg_power, 0, sizeof(Measurement));       // Average Power measurement.
#endif

#if HF_ITF_SPM_AVG_POWER_INTERVAL_ATTR
   _avg_power_interval = 0;                              // Average Power Interval.
#endif

#if HF_ITF_SPM_POWER_FACTOR_ATTR
   _power_factor = 0;                                    // Power Factor.
#endif

#if HF_ITF_SPM_VOLTAGE_ATTR
   memset (&_voltage, 0, sizeof(Measurement));         // Voltage measurement.
#endif

#if HF_ITF_SPM_CURRENT_ATTR
   memset (&_current, 0, sizeof(Measurement));         // Current measurement.
#endif

#if HF_ITF_SPM_FREQUENCY_ATTR
   memset (&_frequency, 0, sizeof(Measurement));       // Frequency measurement.
#endif

#if HF_ITF_SPM_REPORT_CMD
   _report_interval = 0;
   _last_periodic   = 0;
#endif
}

// =============================================================================
// Server::report
// =============================================================================
/*!
 *
 */
// =============================================================================
Report *Server::report ()
{
   Report *report = new Report ();

   if (report != nullptr)
   {
#if HF_ITF_SPM_ENERGY_ATTR
      report->energy               = this->energy (); // Energy.
      report->enabled[ENERGY_ATTR] = true;
#endif

#if HF_ITF_SPM_ENERGY_AT_RESET_ATTR
      report->last_energy                   = this->last_energy (); // Energy at Last Reset.
      report->enabled[ENERGY_AT_RESET_ATTR] = true;
#endif

#if HF_ITF_SPM_TIME_AT_RESET_ATTR
      report->last_time                   = this->last_time (); // Time at Last Reset.
      report->enabled[TIME_AT_RESET_ATTR] = true;
#endif

#if HF_ITF_SPM_POWER_ATTR
      report->power               = this->power (); // Instantaneous Power.
      report->enabled[POWER_ATTR] = true;
#endif

#if HF_ITF_SPM_AVG_POWER_ATTR
      report->avg_power               = this->avg_power (); // Average Power.
      report->enabled[AVG_POWER_ATTR] = true;
#endif

#if HF_ITF_SPM_AVG_POWER_INTERVAL_ATTR
      // Average Power Interval.
      report->avg_power_interval               = this->avg_power_interval ();
      report->enabled[AVG_POWER_INTERVAL_ATTR] = true;
#endif

#if HF_ITF_SPM_VOLTAGE_ATTR
      report->voltage               = this->voltage (); // Voltage.
      report->enabled[VOLTAGE_ATTR] = true;
#endif

#if HF_ITF_SPM_CURRENT_ATTR
      report->current               = this->current (); // Current.
      report->enabled[CURRENT_ATTR] = true;
#endif

#if HF_ITF_SPM_FREQUENCY_ATTR
      report->frequency               = this->frequency (); // Frequency.
      report->enabled[FREQUENCY_ATTR] = true;
#endif

#if HF_ITF_SPM_POWER_FACTOR_ATTR
      report->power_factor               = this->power_factor (); // Power Factor.
      report->enabled[POWER_FACTOR_ATTR] = true;
#endif
   }

   return report;
}

// =============================================================================
// Server::periodic
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::periodic (uint32_t time)
{
   UNUSED (time);

#if HF_ITF_SPM_REPORT_CMD

   if (_report_interval > 0 && std::abs ((int64_t) _last_periodic - time) >= _report_interval)
   {
      Protocol::Address addr;

      Report *report = this->report ();

      Protocol::Message message (report->size ());

      message.itf.role   = CLIENT_ROLE;
      message.itf.id     = Server::uid ();
      message.itf.member = REPORT_CMD;

      report->pack (message.payload);

      send (addr, message);

      _last_periodic = time;

      delete report;
   }

#endif
}

// =============================================================================
// Server::attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::IAttribute *Server::attribute (uint8_t uid)
{
   Attributes attr = static_cast <Attributes>(uid);

   switch (attr)
   {
#if HF_ITF_SPM_ENERGY_ATTR
      case ENERGY_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_ENERGY_AT_RESET_ATTR
      case ENERGY_AT_RESET_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_TIME_AT_RESET_ATTR
      case TIME_AT_RESET_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_POWER_ATTR
      case POWER_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_AVG_POWER_ATTR
      case AVG_POWER_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_AVG_POWER_INTERVAL_ATTR
      case AVG_POWER_INTERVAL_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_VOLTAGE_ATTR
      case VOLTAGE_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_CURRENT_ATTR
      case CURRENT_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_FREQUENCY_ATTR
      case FREQUENCY_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_POWER_FACTOR_ATTR
      case POWER_FACTOR_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif

#if HF_ITF_SPM_REPORT_INTERVAL_ATTR
      case REPORT_INTERVAL_ATTR:
      {
         return Interfaces::create_attribute (this, uid);
      }
#endif
      default:
         return nullptr;
   }
}

// =============================================================================
// Server::attribute_uids
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::UIDS Server::attributes (uint8_t pack_id) const
{
   HF::Attributes::UIDS result;

   if (pack_id == HF::Attributes::Pack::ALL)
   {
#if HF_ITF_SPM_POWER_ATTR
      result.push_back (POWER_ATTR);
#endif
#if HF_ITF_SPM_AVG_POWER_ATTR
      result.push_back (AVG_POWER_ATTR);
#endif
#if HF_ITF_SPM_AVG_POWER_INTERVAL_ATTR
      result.push_back (AVG_POWER_INTERVAL_ATTR);
#endif
#if HF_ITF_SPM_VOLTAGE_ATTR
      result.push_back (VOLTAGE_ATTR);
#endif
#if HF_ITF_SPM_CURRENT_ATTR
      result.push_back (CURRENT_ATTR);
#endif
#if HF_ITF_SPM_FREQUENCY_ATTR
      result.push_back (FREQUENCY_ATTR);
#endif
#if HF_ITF_SPM_POWER_FACTOR_ATTR
      result.push_back (POWER_FACTOR_ATTR);
#endif
   }

#if HF_ITF_SPM_ENERGY_ATTR
   #if !HF_ITF_SPM_RESET_CMD

   if (pack_id == HF::Attributes::Pack::ALL)
   #endif
   {
      result.push_back (ENERGY_ATTR);
   }

#endif

#if HF_ITF_SPM_ENERGY_AT_RESET_ATTR
   #if !HF_ITF_SPM_RESET_CMD

   if (pack_id == HF::Attributes::Pack::ALL)
   #endif
   {
      result.push_back (ENERGY_AT_RESET_ATTR);
   }

#endif

#if HF_ITF_SPM_TIME_AT_RESET_ATTR
   #if !HF_ITF_SPM_RESET_CMD

   if (pack_id == HF::Attributes::Pack::ALL)
   #endif
   {
      result.push_back (TIME_AT_RESET_ATTR);
   }

#endif

#if HF_ITF_SPM_REPORT_INTERVAL_ATTR
   #if !HF_ITF_SPM_REPORT_CMD

   if (pack_id == HF::Attributes::Pack::ALL)
   #endif
   {
      result.push_back (REPORT_INTERVAL_ATTR);
   }

#endif

   return result;
}
