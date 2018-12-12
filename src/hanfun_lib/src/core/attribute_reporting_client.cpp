// =============================================================================
/*!
 * @file       src/core/attribute_reporting_client.cpp
 *
 * This file contains the implementation of the functionality for the
 * Attribute Reporting service interface. Client role.
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
// Client::payload_size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Client::payload_size (Protocol::Message &message) const
{
   if (message.type == Protocol::Message::COMMAND_REQ ||
       message.type == Protocol::Message::COMMAND_RESP_REQ)
   {
      switch (message.itf.member)
      {
         case PERIODIC_REPORT_CMD:
            return payload_size_helper <Report::Periodic>();

         case EVENT_REPORT_CMD:
            return payload_size_helper <Report::Event>();

         default:
            return 0;
      }
   }
   else
   {
      return AbstractInterface::payload_size (message);
   }
}

// =============================================================================
// Client::payload_size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Client::payload_size (Protocol::Message::Interface &itf) const
{
   switch (itf.member)
   {
      case CREATE_PERIODIC_CMD:
      case ADD_PERIODIC_ENTRY_CMD:
      case CREATE_EVENT_CMD:
      case ADD_EVENT_ENTRY_CMD:
      case DELETE_REPORT_CMD:
         return payload_size_helper <Response>();

      default:
         return 0;
   }
}

// =============================================================================
// Client::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Client::handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                       uint16_t offset)
{
   CMD cmd = static_cast <CMD>(packet.message.itf.member);

   if (packet.message.type == Protocol::Message::COMMAND_RES)
   {
      Response *response = new Response ();

      response->unpack (payload, offset);

      switch (cmd)
      {
         case CREATE_PERIODIC_CMD:
         case CREATE_EVENT_CMD:
         {
            this->created (packet.source, *response);
            break;
         }

         case ADD_PERIODIC_ENTRY_CMD:
         case ADD_EVENT_ENTRY_CMD:
         {
            this->added (packet.source, *response);
            break;
         }

         case DELETE_REPORT_CMD:
         {
            this->deleted (packet.source, *response);
            break;
         }

         default:
            return Common::Result::FAIL_SUPPORT;
      }

      delete response;

      return Common::Result::OK;
   }
   else if (packet.message.type == Protocol::Message::COMMAND_REQ ||
            packet.message.type == Protocol::Message::COMMAND_RESP_REQ)
   {
      switch (cmd)
      {
         case PERIODIC_REPORT_CMD:
         {
            report (PERIODIC, packet.source, payload, offset);
            break;
         }

         case EVENT_REPORT_CMD:
         {
            report (EVENT, packet.source, payload, offset);
            break;
         }
         default:
            return Common::Result::FAIL_SUPPORT;
      }

      return Common::Result::OK;
   }

   return Common::Result::FAIL_SUPPORT;
}

// =============================================================================
// AbstractClient
// =============================================================================

// =============================================================================
// AbstractClient::create
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractClient::create (Protocol::Address &destination)
{
   HF::Protocol::Address rule_destination;
   rule_destination.device = unit ().device ().address ();
   rule_destination.unit   = unit ().id ();

   auto msg = HF::Core::AttributeReporting::create (rule_destination);

   destination.unit = 0;

   send (destination, *msg);

   delete msg;
}

// =============================================================================
// AbstractClient::create
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractClient::create (Protocol::Address &destination, uint32_t interval)
{
   HF::Protocol::Address rule_destination;
   rule_destination.device = unit ().device ().address ();
   rule_destination.unit   = unit ().id ();

   auto msg = AttributeReporting::create (rule_destination, interval);

   destination.unit = 0;

   send (destination, *msg);

   delete msg;
}

// =============================================================================
// AbstractClient::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractClient::destroy (Protocol::Address &destination, Type type, uint8_t report_id)
{
   auto msg = AttributeReporting::destroy (type, report_id);

   send (destination, *msg);

   delete msg;
}

// =============================================================================
// AbstractClient::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractClient::destroy (Protocol::Address &destination, Reference report)
{
   auto msg = AttributeReporting::destroy (report);

   send (destination, *msg);

   delete msg;
}

// =============================================================================
// AbstractClient::add
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractClient::add (Protocol::Address &destination, Reference report,
                          periodic_iterator begin, periodic_iterator end)
{
   auto msg = AttributeReporting::add (report, begin, end);

   send (destination, *msg);

   delete msg;
}

// =============================================================================
// AbstractClient::add
// =============================================================================
/*!
 *
 */
// =============================================================================
void AbstractClient::add (Protocol::Address &destination, Reference report,
                          event_iterator begin, event_iterator end)
{
   auto msg = AttributeReporting::add (report, begin, end);

   send (destination, *msg);

   delete msg;
}
