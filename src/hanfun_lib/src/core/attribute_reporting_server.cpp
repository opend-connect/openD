// =============================================================================
/*!
 * @file       src/core/attribute_reporting_server.cpp
 *
 * This file contains the implementation of the functionality for the
 * Attribute Reporting service interface. Server role.
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
// find_available_id
// =============================================================================
/*!
 * Find an available report id.
 *
 * @param [in] begin    iterator for the beginning in the list of the report rules.
 * @param [in] end      iterator for the end in the list of the report rules.
 *
 * @tparam _Rule        class type of rule in the list.
 * @tparam _Rule        class type of the iterator for the list.
 *
 * @return  a new report identifier.
 */
// =============================================================================
template<typename _Rule, typename Iterator>
static uint8_t find_available_id (Iterator begin, Iterator end)
{
   // Find the next available entry.
   std::vector <uint8_t> ids;

   /* *INDENT-OFF* */
   std::for_each(begin, end, [&ids](const _Rule &rule)
   {
      ids.push_back(rule.report.id);
   });
   /* *INDENT-ON* */

   std::sort (ids.begin (), ids.end ());

   uint8_t id;

   for (id = START_ADDR; id < ALL_ADDR; id++)
   {
      auto it = std::lower_bound (ids.begin (), ids.end (), id);

      if (it == ids.end () || *it != id)
      {
         break;
      }
   }

   return id;
}

// =============================================================================
// IServer::response
// =============================================================================
/*!
 *
 */
// =============================================================================
void IServer::response (Protocol::Packet &packet, Reference &report, Common::Result result)
{
   Response *resp = new Response ();
   resp->code   = result;
   resp->report = report;

   Protocol::Message *resp_msg = new Protocol::Message (packet.message, resp->size ());

   resp->pack (resp_msg->payload);

   delete resp;

   unit ().send (packet.source, *resp_msg, packet.link);

   delete resp_msg;
}

// =============================================================================
// IServer::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result IServer::handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                       uint16_t offset)
{
   UNUSED (payload);
   UNUSED (offset);

   Reference report;

   response (packet, report, Common::Result::FAIL_RESOURCES);

   return Common::Result::FAIL_RESOURCES;
}

// =============================================================================
// Server::payload_size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Server::payload_size (Protocol::Message::Interface &itf) const
{
   switch (itf.member)
   {
      case CREATE_PERIODIC_CMD:
         return payload_size_helper <Report::Periodic::CreateMessage>();

      case CREATE_EVENT_CMD:
         return payload_size_helper <Report::Event::CreateMessage>();

      case ADD_PERIODIC_ENTRY_CMD:
         return payload_size_helper <Report::Periodic::AddEntryMessage>();

      case ADD_EVENT_ENTRY_CMD:
         return payload_size_helper <Report::Event::AddEntryMessage>();

      case DELETE_REPORT_CMD:
         return payload_size_helper <Report::DeleteMessage>();

      default:
         return 0;
   }
}

// =============================================================================
// Server::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Server::handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                       uint16_t offset)
{
   Common::Result result = AbstractInterface::check (packet.message, payload, offset);

   if (result != Common::Result::OK)
   {
      return result;
   }

   CMD cmd = static_cast <CMD>(packet.message.itf.member);

   if (packet.message.type != Protocol::Message::COMMAND_REQ &&
       packet.message.type != Protocol::Message::COMMAND_RESP_REQ)
   {
      return Common::Result::FAIL_SUPPORT;
   }

   if (!this->authorized (packet.message.itf.member, packet.source))
   {
      Reference report;

      response (packet, report, Common::Result::FAIL_AUTH);

      return Common::Result::FAIL_AUTH;
   }

   switch (cmd)
   {
      case CREATE_PERIODIC_CMD:
      {
         Report::Periodic::CreateMessage *message = new Report::Periodic::CreateMessage ();

         message->unpack (payload, offset);

         result = this->handle (*message);

         Reference report;

         if (result == Common::Result::OK)
         {
            report = periodic_rules.begin ()->report;
         }

         response (packet, report, result);

         delete message;

         break;
      }

      case ADD_PERIODIC_ENTRY_CMD:
      {
         Report::Periodic::AddEntryMessage *message = new Report::Periodic::AddEntryMessage ();

         message->unpack (payload, offset);

         result = this->handle (*message);

         response (packet, message->report, result);

         delete message;

         break;
      }

      case CREATE_EVENT_CMD:
      {
         Report::Event::CreateMessage *message = new Report::Event::CreateMessage ();

         message->unpack (payload, offset);

         result = this->handle (*message);

         Reference report;

         if (result == Common::Result::OK)
         {
            report = event_rules.begin ()->report;
         }

         response (packet, report, result);

         delete message;

         break;
      }

      case ADD_EVENT_ENTRY_CMD:
      {
         Report::Event::AddEntryMessage *message = new Report::Event::AddEntryMessage ();

         message->unpack (payload, offset);

         result = this->handle (*message);

         response (packet, message->report, result);

         delete message;

         break;
      }

      case DELETE_REPORT_CMD:
      {
         Report::DeleteMessage *message = new Report::DeleteMessage ();

         message->unpack (payload, offset);

         result = this->handle (*message);

         response (packet, message->report, result);

         delete message;

         break;
      }

      default:
         return Common::Result::FAIL_SUPPORT;
   }

   return Common::Result::OK;
}

// =============================================================================
// Server::handle
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Server::handle (const Report::Periodic::CreateMessage &message)
{
   Periodic::Rule *rule = new Periodic::Rule (message.interval);

   if (rule == nullptr)
   {
      return Common::Result::FAIL_RESOURCES;
   }

   uint8_t report_id = find_available_id <Periodic::Rule>(periodic_rules.begin (),
                                                          periodic_rules.end ());

   if (report_id == ALL_ADDR)
   {
      delete rule;
      return Common::Result::FAIL_RESOURCES;
   }

   rule->destination = message.destination;
   rule->report.id   = report_id;

   periodic_rules.push_front (*rule);

   delete rule;

   return Common::Result::OK;
}

// =============================================================================
// Server::handle
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Server::handle (const Report::Periodic::AddEntryMessage &message)
{
   /* *INDENT-OFF* */
   auto it = std::find_if(periodic_rules.begin(), periodic_rules.end(),
                          [&message](const Periodic::Rule &rule)
                          {
                             return rule.report.id == message.report.id;
                          });
   /* *INDENT-ON* */

   if (it == periodic_rules.end ())
   {
      return Common::Result::FAIL_ARG;
   }

   /* *INDENT-OFF* */
   std::for_each (message.cbegin(), message.cend(), [it](const Periodic::Entry &entry)
   {
      it->add(entry);
   });
   /* *INDENT-ON* */

   return Common::Result::OK;
}

// =============================================================================
// Server::handle
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Server::handle (const Report::Event::CreateMessage &message)
{
   Event::Rule *rule = new Event::Rule ();

   if (rule == nullptr)
   {
      return Common::Result::FAIL_RESOURCES;
   }

   uint8_t report_id = find_available_id <Event::Rule>(event_rules.begin (), event_rules.end ());

   if (report_id == ALL_ADDR)
   {
      delete rule;
      return Common::Result::FAIL_RESOURCES;
   }

   rule->destination = message.destination;
   rule->report.id   = report_id;

   event_rules.push_front (*rule);

   delete rule;

   return Common::Result::OK;
}

// =============================================================================
// Server::handle
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Server::handle (const Report::Event::AddEntryMessage &message)
{
   /* *INDENT-OFF* */
   auto it = std::find_if(event_rules.begin(), event_rules.end(),
                          [&message](const Event::Rule &rule)
                          {
                             return rule.report.id == message.report.id;
                          });
   /* *INDENT-ON* */

   if (it == event_rules.end ())
   {
      return Common::Result::FAIL_ARG;
   }

   /* *INDENT-OFF* */
   std::for_each (message.cbegin(), message.cend(), [it](const Event::Entry &entry)
   {
      it->add(entry);
   });
   /* *INDENT-ON* */

   return Common::Result::OK;
}

// =============================================================================
// Server::handle
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result Server::handle (const Report::DeleteMessage &message)
{
   Common::Result result = Common::Result::FAIL_UNKNOWN;

   switch (message.report.type)
   {
      case PERIODIC:
      {
         if (message.report.id == ALL_ADDR)
         {
            periodic_rules.clear ();
         }
         else
         {
            /* *INDENT-OFF* */
            auto it = std::find_if(periodic_rules.begin(), periodic_rules.end(),
                                   [&message](const Periodic::Rule &rule)
                                   {
                                      return rule.report.id == message.report.id;
                                   });
            /* *INDENT-ON* */

            if (it == periodic_rules.end ())
            {
               return Common::Result::FAIL_ARG;
            }

            /* *INDENT-OFF* */
            periodic_rules.remove_if([&message](const Periodic::Rule &rule)
            {
               return rule.report.id == message.report.id;
            });
            /* *INDENT-ON* */
         }

         result = Common::Result::OK;

         break;
      }
      case EVENT:
      {
         if (message.report.id == ALL_ADDR)
         {
            event_rules.clear ();
         }
         else
         {
            /* *INDENT-OFF* */
            auto it = std::find_if(event_rules.begin(), event_rules.end(),
                                   [&message](const Event::Rule &rule)
                                   {
                                      return rule.report.id == message.report.id;
                                   });
            /* *INDENT-ON* */

            if (it == event_rules.end ())
            {
               return Common::Result::FAIL_ARG;
            }

            /* *INDENT-OFF* */
            event_rules.remove_if([&message](const Event::Rule &rule)
            {
               return rule.report.id == message.report.id;
            });
            /* *INDENT-ON* */
         }

         result = Common::Result::OK;

         break;
      }
      default:
         break;
   }

   return result;
}

// =============================================================================
// Helper functions.
// =============================================================================

// =============================================================================
// create_report_entry
// =============================================================================
/*!
 *
 */
// =============================================================================
static Report::Periodic::Entry *create_report_entry (const Units::IUnit *unit,
                                                     const Common::Interface &itf,
                                                     uint8_t pack_id,
                                                     const HF::Attributes::UIDS &uids)
{
   auto result = new Report::Periodic::Entry (unit->id (), itf);

   auto attrs  = unit->attributes (itf, pack_id, uids);
   /* *INDENT-OFF* */
   std::for_each (attrs.begin(), attrs.end(), [result](HF::Attributes::IAttribute *attr)
   {
      result->add (attr);
   });
   /* *INDENT-ON* */

   return result;
}

// =============================================================================
// fill_report
// =============================================================================
/*!
 *
 */
// =============================================================================
static void fill_report (Report::Periodic *report, const Periodic::Entry &entry,
                         const Units::IUnit *unit)
{
   assert (report != nullptr);
   assert (unit != nullptr);

   if (entry.itf.id == HF::Interface::ANY_UID)
   {
      // Search the official interfaces.
      uint16_t count;
      const Common::Interface *itf = Profiles::interfaces (unit->uid (), count);

      assert (itf != nullptr);

      if (itf != nullptr)
      {
         for (uint16_t i = 0; i < count; ++i, ++itf)
         {
            Report::Periodic::Entry *_entry = create_report_entry (unit, *itf, entry.pack_id,
                                                                   entry.uids);
            report->add (*_entry);

            delete _entry;
         }
      }
   }
   else
   {
      Report::Periodic::Entry *_entry = create_report_entry (unit, entry.itf, entry.pack_id,
                                                             entry.uids);
      report->add (*_entry);

      delete _entry;
   }
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
   /* *INDENT-OFF* */
   std::for_each(periodic_rules.begin (), periodic_rules.end (),
                 [this, time](Periodic::Rule &rule)
   {
      if ((time/rule.interval) == 0 ||
          (uint32_t) std::abs ((int64_t)time - rule.last_time) < rule.interval)
      {
         return;
      }

      rule.last_time = time;

      Protocol::Message * message = new Protocol::Message ();
      message->itf.role = HF::Interface::CLIENT_ROLE;
      message->itf.id = HF::Interface::ATTRIBUTE_REPORTING;
      message->itf.member = PERIODIC_REPORT_CMD;

      Report::Periodic * report = new Report::Periodic(rule.report.id);

      std::for_each(rule.cbegin(), rule.cend(), [this, report](const Periodic::Entry &entry)
      {
         Units::IUnit * _unit = this->unit().device().unit(entry.unit);
         assert (_unit != nullptr);
         if (_unit != nullptr)
         {
            fill_report(report, entry, _unit);
         }
      });

      message->payload = Common::ByteArray (report->size());

      report->pack(message->payload);

      this->send (rule.destination, *message);

      delete report;
      delete message;
   });
   /* *INDENT-ON* */
}

// =============================================================================
// Server::notify
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::notify (uint8_t unit, const HF::Attributes::IAttribute &old_value,
                     const HF::Attributes::IAttribute &new_value)
{
   /* *INDENT-OFF* */
   std::for_each (event_rules.begin (), event_rules.end (),
                  [this, unit, &old_value, &new_value](const Event::Rule &rule)
   {
      std::vector<Report::Event::Entry *> entries;
      std::for_each (rule.cbegin (), rule.cend (),
                     [unit, &entries, &old_value, &new_value](const Event::Entry &entry)
      {
         if (entry.unit == unit && entry.itf.id == new_value.interface())
         {
            entries.push_back (Report::Event::process (entry, old_value, new_value));
         }
      });

      if (std::any_of (entries.begin(), entries.end(),
                       [](const Report::Event::Entry * entry) { return entry != nullptr; }))
      {
         Report::Event * report = new Report::Event (rule.report.id);

         std::for_each (entries.begin(), entries.end(), [report](Report::Event::Entry * entry)
         {
            if (entry != nullptr)
            {
               report->add(*entry);
               delete entry;
            }
         });

         Protocol::Message * message = new Protocol::Message ();

         message->itf.role   = HF::Interface::CLIENT_ROLE;
         message->itf.id     = HF::Interface::ATTRIBUTE_REPORTING;
         message->itf.member = EVENT_REPORT_CMD;

         message->payload = Common::ByteArray (report->size());

         report->pack(message->payload);

         this->send (rule.destination, *message);

         delete report;
         delete message;
      }

   });
   /* *INDENT-ON* */
}

// =============================================================================
// Server::entries_count
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t Server::count (Type type) const
{
   switch (type)
   {
      case PERIODIC:
         return std::distance (periodic_rules.begin (), periodic_rules.end ());

      case EVENT:
         return std::distance (event_rules.begin (), event_rules.end ());

      default:
         return 0;
   }
}
