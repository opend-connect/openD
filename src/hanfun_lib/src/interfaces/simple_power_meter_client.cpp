// =============================================================================
/*!
 * @file       src/interfaces/simple_power_meter_client.cpp
 *
 * This file contains the implementation of the Simple Power Meter interface :
 * Client role.
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
// SimplePowerMeter / Client
// =============================================================================

// =============================================================================
// Client::handle_command
// =============================================================================
/*!
 * @todo This needs more validation when reading a report received.
 */
// =============================================================================
Common::Result Client::handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                       uint16_t offset)
{
   if (packet.message.itf.member != REPORT_CMD)
   {
      return Common::Result::FAIL_SUPPORT;
   }

   Report report;

   offset += report.unpack (payload, offset);

   this->report (packet.source, report);

   return Common::Result::OK;
}
