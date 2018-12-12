// =============================================================================
/*!
 * @file       apps/example_07.cpp
 *
 * This file contains an example usage of the Attribute reporting service.
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

#include <cassert>
#include <cmath>

#include <iomanip>

#include "hanfun.h"
#include "hanfun/debug.h"

#include "localloop.h"

// =============================================================================
// Defines
// =============================================================================

/* *INDENT-OFF* */
#define TABLE_LOG(_X)      LOG (INFO) << std::right << std::setw (15) << _X << std::left << NL

#define TABLE_STREAM(_X)   stream << "[INFO ] " << std::right << std::setw (15) << _X << std::left
/* *INDENT-ON* */

// =============================================================================
// Implementation
// =============================================================================

using namespace HF::Core::AttributeReporting;

std::ostream &operator <<(std::ostream &stream, const Report::Attribute &attr)
{
   stream << " (idx) " << attr->interface () << " (itf) " << (int) attr->uid () << " (uid)";
   return stream;
}

std::ostream &operator <<(std::ostream &stream, const Report::Periodic::Entry &entry)
{
   TABLE_STREAM ("ITF : " << entry.itf.id << " (uid) " << entry.itf.role << " (role)") << NL;
   TABLE_STREAM ("Unit : " << (int) entry.unit) << NL;

   TABLE_STREAM ("Attributes : " << (int) entry.attributes.size () << " (#)");

   return stream;
}

std::ostream &operator <<(std::ostream &stream, const Report::Event::Entry &entry)
{
   TABLE_STREAM ("ITF : " << entry.itf.id << " (uid) " << entry.itf.role << " (role)") << NL;
   TABLE_STREAM ("Unit : " << (int) entry.unit) << NL;

   TABLE_STREAM ("Fields : " << (int) entry.fields.size () << " (#)");

   return stream;
}

std::ostream &operator <<(std::ostream &stream, const Report::Event::Field &field)
{
   stream << " (idx) " << field.type << " (type) ";
   return stream;
}

std::ostream &operator <<(std::ostream &stream, const Report::Abstract &report)
{
   stream << (int) report.id << " (id) " << (int) report.type << " (type) ";
   return stream;
}

namespace
{
   /*
    * Custom attribute reporting client role implementation.
    */
   struct AttributeReporting:public HF::Core::AttributeReporting::AbstractClient
   {
      void report (HF::Core::AttributeReporting::Type type, const HF::Protocol::Address &address,
                   const HF::Common::ByteArray &payload, uint16_t offset)
      {
         UNUSED (payload);
         UNUSED (offset);

         using namespace HF::Core::AttributeReporting;

         switch (type)
         {
            //! [Periodic event processing]
            case PERIODIC:
            {
               LOG (INFO) << "Received a periodic notification from device : " << address.device << NL;

               Report::Periodic report;

               report.unpack (HF::Attributes::get_factory, payload, offset);

               TABLE_LOG ("Report : " << report);
               TABLE_LOG ("Entries : " << std::distance (report.entries.begin (),
                                                         report.entries.end ()) << " (#)");

               uint8_t unit_count = 0;
               /* *INDENT-OFF* */
               std::for_each (report.entries.begin (), report.entries.end (),
                     [&unit_count](Report::Periodic::Entry &entry)
               {
                  TABLE_LOG ("Entry : " << (int) unit_count++ << std::endl << entry);

                  uint8_t attr_count = 0;
                  std::for_each (entry.attributes.begin (), entry.attributes.end (),
                        [&attr_count](Report::Attribute attr)
                  {
                     TABLE_LOG (" Attribute : " << (int) attr_count++ << attr);

                     if (attr->interface () == HF::Interface::LEVEL_CONTROL &&
                           attr->uid () == HF::Interfaces::LevelControl::LEVEL_ATTR)
                     {
                        HF::Interfaces::LevelControl::Level *level_attr =
                        (HF::Interfaces::LevelControl::Level *) attr.get ();
                        int precent = HF::Common::to_percent <uint8_t>(level_attr->get ());
                        TABLE_LOG ("Attr Value : " << precent << "%");
                     }
                  });
               });
               /* *INDENT-ON* */

               break;
            }

            //! [Periodic event processing]
            //! [Event event processing]
            case EVENT:
            {
               LOG (INFO) << "Received an event notification : " << address.device << NL;

               Report::Event report;

               report.unpack (HF::Attributes::get_factory, payload, offset);

               TABLE_LOG ("Report : " << report);
               TABLE_LOG ("Entries : " << std::distance (report.entries.begin (),
                                                         report.entries.end ()) << " (#)");

               uint8_t unit_count = 0;
               /* *INDENT-OFF* */
               std::for_each (report.entries.begin (), report.entries.end (),
                     [&unit_count](Report::Event::Entry &entry)
               {
                  TABLE_LOG ("Entry : " << (int) unit_count++ << std::endl << entry);

                  uint8_t field_count = 0;
                  std::for_each (entry.fields.begin (), entry.fields.end (),
                        [&field_count](Report::Event::Field &field)
                  {
                     TABLE_LOG (" Field : " << (int) field_count++ << field);
                     TABLE_LOG (" Attribute : " << field.attribute->interface () << " (itf) "
                                                << (int) field.attribute->uid () << " (uid)");

                     if (field.attribute->interface () == HF::Interface::LEVEL_CONTROL &&
                           field.attribute->uid () == HF::Interfaces::LevelControl::LEVEL_ATTR)
                     {
                        HF::Interfaces::LevelControl::Level *level_attr =
                        (HF::Interfaces::LevelControl::Level *) field.attribute.get ();
                        int precent = HF::Common::to_percent <uint8_t>(level_attr->get ());
                        TABLE_LOG ("Attr Value : " << precent << "%");
                     }
                  });
               });
               /* *INDENT-ON* */

               break;
            }
            //! [Event event processing]
            default:
               break;
         }
      }

      void created (const HF::Protocol::Address &address,
                    const HF::Core::AttributeReporting::Response &response)
      {
         LOG (INFO) << "Report rule created on device : " << address.device << NL;
         LOG (INFO) << "  Code : " << (int) response.code << NL;
         LOG (INFO) << "  Type : " << (int) response.report.type << NL;
         LOG (INFO) << "  Id   : " << (int) response.report.id << NL;
      }

      void added (const HF::Protocol::Address &address,
                  const HF::Core::AttributeReporting::Response &response)
      {
         LOG (INFO) << "Report rule entries created on device : " << address.device << NL;
         LOG (INFO) << "  Code : " << (int) response.code << NL;
         LOG (INFO) << "  Type : " << (int) response.report.type << NL;
         LOG (INFO) << "  Id   : " << (int) response.report.id << NL;
      }
   };

   /*
    * Unit implementing the Simple %Level Control profile.
    */
   struct SimpleLevelControl:public HF::Units::Unit <HF::Profiles::SimpleLevelControl, AttributeReporting>
   {
      SimpleLevelControl(uint8_t id, HF::IDevice &device):
         HF::Units::Unit <HF::Profiles::SimpleLevelControl, AttributeReporting>(id, device)
      {}

      AttributeReporting *attribute_reporting () const
      {
         return const_cast <AttributeReporting *>(get <0>());
      }
   };

   /*
    * Unit implementing the Simple Level Controllable profile.
    */
   struct SimpleLevelControllable:public HF::Units::Unit <HF::Profiles::SimpleLevelControllable>
   {
      typedef HF::Units::Unit <HF::Profiles::SimpleLevelControllable> _Parent;

      SimpleLevelControllable(uint8_t id, HF::IDevice &device):
         _Parent (id, device)
      {}

      void level_change (HF::Protocol::Address &source, uint8_t old_level, uint8_t new_level)
      {
         _Parent::level_change (source, old_level, new_level);
         LOG (INFO) << "Level Change : "
                    << (int) HF::Common::to_percent (old_level)
                    << "\% -> "
                    << (int) HF::Common::to_percent (new_level)
                    << "\%" << NL;
      }
   };

   /*
    * Example node.
    */
   struct Node:public HF::Devices::Node::Node
   {};

   /*
    * Example concentrator.
    */
   struct Base:public HF::Devices::Concentrator::Concentrator
   {};

}  // namespace

// =============================================================================
// MAIN
// =============================================================================

int main (int argc, char **argv)
{
   UNUSED (argc);
   UNUSED (argv);

   LOG (INFO) << "Use case : Level Control interface usage" << NL;

   /*
    * Each node variable is a remote device, i.e.,
    * the Node variables are declared on the remote device
    * code and are not used on the base code.
    */
   LOG (INFO) << "Create the node instances ..." << NL;

   Node node1;

   LOG (INFO) << "Add unit to node1 instance ..." << NL;
   SimpleLevelControl level_control (1, node1);

   Node node2;

   LOG (INFO) << "Add unit to node2 instance ..." << NL;
   SimpleLevelControllable level_controllable (1, node2);

   /*
    * This instance represents the base application.
    */
   LOG (INFO) << "Create the base instance ..." << NL;
   Base base;

   LOG (INFO) << "Create transport instance" << NL;
   Localloop loop;

   /*
    * Setup the network.
    *
    * This simulates the devices connecting to the base using for
    * example a TCP/IP connection or a DECT ULE PVC.
    */
   LOG (INFO) << "Network setup ..." << NL;

   loop.set_base (&base);
   loop.add_node (&node1, "node_1");
   loop.add_node (&node2, "node_2");

   // Register the two devices.

   // Node 1 is unregistered.
   assert (node1.address () == HF::Protocol::BROADCAST_ADDR);

   LOG (INFO) << "Registering node1 ... " << NL;
   node1.unit0 ()->device_management ()->register_device ();
   LOG (INFO) << "Node1 address ... " << node1.address () << NL;

   // Node 1 is registered
   assert (node1.address () == 1);

   // Node 2 is unregistered.
   assert (node2.address () == HF::Protocol::BROADCAST_ADDR);

   LOG (INFO) << "Registering node2 ... " << NL;
   node2.unit0 ()->device_management ()->register_device ();
   LOG (INFO) << "Node2 address ... " << node2.address () << NL;

   // Node 2 is registered
   assert (node2.address () == 2);

   LOG (INFO) << "There should be two registered devices ... "
              << base.unit0 ()->device_management ()->entries ().size () << NL;

   assert (base.unit0 ()->device_management ()->entries ().size () == 2);

   LOG (INFO) << "Set initial level value ... 15\%" << NL;
   level_controllable.level (15.0f);

   HF::Protocol::Address addr (2, 0);

   // =============================================================================
   // Periodic Notification
   // =============================================================================

   using namespace HF::Core::AttributeReporting;

   LOG (INFO) << "====== Periodic Notifications ======" << NL;

   // Create a periodic rule.
   level_control.attribute_reporting ()->create (addr, 6);

   // Create another periodic rule.
   level_control.attribute_reporting ()->create (addr, 15);

   // Create the rule entries.
   std::vector <Periodic::Entry> periodic_entries (1);

   auto &entry = periodic_entries.front ();

   // Create an entry to receive all mandatory attributes.
   entry.unit     = 1;
   entry.itf.id   = HF::Interface::LEVEL_CONTROL;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.pack_id  = HF::Attributes::Pack::MANDATORY;

   Reference report_ref (PERIODIC, 1);

   // Add entries to rule 1
   level_control.attribute_reporting ()->add (addr, report_ref, periodic_entries.begin (),
                                              periodic_entries.end ());


   // Add entries to rule 2
   report_ref.id = 2;
   level_control.attribute_reporting ()->add (addr, report_ref, periodic_entries.begin (),
                                              periodic_entries.end ());

   // Simulate remote device HAN-FUN periodic processing.
   LOG (INFO) << ">>> Simulate node periodic processing <<<" << NL;

   for (int time = 0; time < 35; time++)
   {
      LOG (INFO) << "Time : " << time << "s" << NL;
      node2.periodic (time);

      // At these times the level changes.
      if (time == 10)
      {
         // Another node changes the value.
         LOG (INFO) << "Level changes to 25 % by an another node." << NL;
         HF::Protocol::Address addr (node2.address (), 1);
         level_control.level (addr, 25.0f);
      }
      else if (time == 25)
      {
         // The value is changed on the actual node.
         LOG (INFO) << "Level changes to 55 % on the actual node." << NL;
         level_controllable.level (55.0f);
      }
   }

   // =============================================================================
   // Event Notification
   // =============================================================================

   LOG (INFO) << "====== Event Notifications ======" << NL;

   LOG (INFO) << "Set initial level value ... 15\%" << NL;
   level_controllable.level (15.0f);

   // Create a periodic rule.
   level_control.attribute_reporting ()->create (addr);

   // Create another periodic rule.
   level_control.attribute_reporting ()->create (addr);

   // Create the rule entries.
   std::vector <Event::Entry> event_entries;

   Event::Entry evt_entry;

   // Create an entry to receive changes on .
   evt_entry.unit     = 1;
   evt_entry.itf.id   = HF::Interface::LEVEL_CONTROL;
   evt_entry.itf.role = HF::Interface::SERVER_ROLE;
   evt_entry.pack_id  = HF::Attributes::Pack::DYNAMIC;

   // Create the condition to send a report when level values is lower that to 5%
   Event::Field field (Event::LT, HF::Interfaces::LevelControl::LEVEL_ATTR);
   field.value = {HF::Common::from_percent <uint8_t>(5.0f)};  // 5%;

   evt_entry.fields.push_back (field);

   // Create the condition to send a report when level values is equal to 60%
   field.type  = Event::EQ;
   field.value = {HF::Common::from_percent <uint8_t>(60.0f)};  // 60%;

   evt_entry.fields.push_back (field);

   // Create the condition to send a report when level values is greater that to 85%
   field.type  = Event::HT;
   field.value = {HF::Common::from_percent <uint8_t>(85.0f)};  // 85%;

   evt_entry.fields.push_back (field);

   Reference evt_report_ref (HF::Core::AttributeReporting::EVENT, 1);

   event_entries.push_back (evt_entry);

   // Add entries to rule 1
   level_control.attribute_reporting ()->add (addr, evt_report_ref, event_entries.begin (),
                                              event_entries.end ());

   // Create another set of rules in second rule.
   event_entries.clear ();
   evt_entry.fields.clear ();

   // Create the condition to send a report when level values is lower that to 10%
   field.type  = Event::LT;
   field.value = {HF::Common::from_percent <uint8_t>(10.0f)};  // 10%;

   evt_entry.fields.push_back (field);

   field.type  = Event::EQ;
   field.value = {HF::Common::from_percent <uint8_t>(40.0f)};  // 40%;

   evt_entry.fields.push_back (field);

   // Create the condition to send a report when level values is greater that to 90%
   field.type  = Event::HT;
   field.value = {HF::Common::from_percent <uint8_t>(75.0f)};  // 75%;

   evt_entry.fields.push_back (field);

   event_entries.push_back (evt_entry);

   // Add entries to rule 2
   evt_report_ref.id = 2;
   level_control.attribute_reporting ()->add (addr, evt_report_ref, event_entries.begin (),
                                              event_entries.end ());

   LOG (INFO) << ">>> Simulate node level change <<<" << NL;

   addr.unit = 1;

   LOG (INFO) << "== Change level to 30 % ..." << NL;
   level_control.level (addr, 30.0f);

   LOG (INFO) << "== Change level to 40 % ..." << NL;
   level_control.level (addr, 40.0f);

   LOG (INFO) << "== Change level to 50 % ..." << NL;
   level_control.level (addr, 50.0f);

   LOG (INFO) << "== Change level to 60 % ..." << NL;
   level_control.level (addr, 60.0f);

   LOG (INFO) << "== Change level to 70 % ..." << NL;
   level_control.level (addr, 40.0f);

   LOG (INFO) << "== Change level to 80 % ..." << NL;
   level_control.level (addr, 80.0f);

   LOG (INFO) << "== Change level to 90 % ..." << NL;
   level_control.level (addr, 90.0f);

   LOG (INFO) << "== Change level to 20% ..." << NL;
   level_control.level (addr, 20.0f);

   LOG (INFO) << "== Change level to 15% ..." << NL;
   level_control.level (addr, 15.0f);

   LOG (INFO) << "== Change level to 10% ..." << NL;
   level_control.level (addr, 10.0f);

   LOG (INFO) << "== Change level to  7% ..." << NL;
   level_control.level (addr, 7.0f);

   LOG (INFO) << "== Change level to  5% ..." << NL;
   level_control.level (addr, 5.0f);

   LOG (INFO) << "== Change level to  1% ..." << NL;
   level_control.level (addr, 1.0f);

   return 0;
}
