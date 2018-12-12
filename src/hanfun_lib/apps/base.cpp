// =============================================================================
/*!
 * @file       apps/base.cpp
 *
 * This file contains the implementation of the Base class that represents the
 * HAN-FUN Concentrator on the base example application.
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

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "base.h"

#include "common.h"

// #define HF_LOG_LEVEL HF_LOG_LEVEL_TRACE
#include "application.h"

#include "json/json.h"

/*!
 * @addtogroup examples
 * @{
 */

// =============================================================================
// DeviceManagement
// =============================================================================

// =============================================================================
// DeviceManagement::Entries::save
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Common::Result DeviceManagement::Entries::save (const Device &device)
{
   auto res = HF::Core::DeviceManagement::Entries::save (device);
   HF::Application::Save ();
   return res;
}

// =============================================================================
// DeviceManagement::Entries::save
// =============================================================================
/*!
 *
 */
// =============================================================================
void DeviceManagement::Entries::insert (const Device &device)
{
   HF::Core::DeviceManagement::Entries::save (device);
}

// =============================================================================
// DeviceManagement::Entries::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Common::Result DeviceManagement::Entries::destroy (const Device &device)
{
   auto res = HF::Core::DeviceManagement::Entries::destroy (device);
   HF::Application::Save ();
   return res;
}

// =============================================================================
// DeviceManagement::Server::available
// =============================================================================
/*!
 *
 */
// =============================================================================
bool DeviceManagement::Server::available (uint16_t address)
{
   if (address == 0 || address == HF::Protocol::BROADCAST_ADDR)
   {
      return false;
   }

   /* *INDENT-OFF* */
   auto it = std::find_if(entries().begin(), entries().end(),
                          [address](const HF::Core::DeviceManagement::Device &dev)
                          {
                             return address == dev.address;
                          });
   /* *INDENT-ON* */

   return it == entries ().end ();
}

// =============================================================================
// DeviceManagement::Server::next_address
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t DeviceManagement::Server::next_address ()
{
   uint16_t result = _next_address;

   _next_address = HF::Protocol::BROADCAST_ADDR;

   if (result == HF::Protocol::BROADCAST_ADDR)
   {
      result = HF::Core::DeviceManagement::Server <Entries>::next_address ();
   }

   return result;
}

// =============================================================================
// DeviceManagement::Server::deregister
// =============================================================================
/*!
 *
 */
// =============================================================================
bool DeviceManagement::Server::deregister (uint16_t address)
{
   if (address == 0 || address == HF::Protocol::BROADCAST_ADDR)
   {
      return false;
   }

   auto _entry = entry (address);

   if (_entry != nullptr)
   {
      HF::Core::DeviceManagement::Server <Entries>::deregister (_entry);
      return true;
   }

   return false;
}

// =============================================================================
// DeviceManagement::Server::save
// =============================================================================
/*!
 *
 */
// =============================================================================
void DeviceManagement::Server::save (Json::Value &root)
{
   LOG (INFO) << "Saving registration entries ..." << NL;

   unsigned i = 0;

   /* *INDENT-OFF* */
   for_each( entries ().begin (), entries ().end (),
             [&root, &i](HF::Core::DeviceManagement::Device &device)
   {
      to_json (device, root[i]);
      i++;
   });
   /* *INDENT-ON* */
}

// =============================================================================
// DeviceManagement::Server::restore
// =============================================================================
/*!
 *
 */
// =============================================================================
void DeviceManagement::Server::restore (Json::Value root)
{
   LOG (INFO) << "Restoring registration entries ..." << NL;

   HF::Core::DeviceManagement::Device device;

   for (unsigned i = 0; i < root.size (); i++)
   {
      from_json (root[i], device);
      HF::Core::DeviceManagement::Server <Entries>::entries ().insert (device);
   }
}

// =============================================================================
// BindManagement
// =============================================================================

// =============================================================================
// BindManagement::Entries::save
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Common::Result BindManagement::Entries::save (const Entry &entry)
{
   auto res = HF::Core::BindManagement::Entries::save (entry);
   HF::Application::Save ();
   return res;
}

// =============================================================================
// BindManagement::Entries::save
// =============================================================================
/*!
 *
 */
// =============================================================================
void BindManagement::Entries::insert (Entry &entry)
{
   HF::Core::BindManagement::Entries::save (entry);
}

// =============================================================================
// DeviceManagement::Entries::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Common::Result BindManagement::Entries::destroy (const Entry &entry)
{
   auto res = HF::Core::BindManagement::Entries::destroy (entry);
   HF::Application::Save ();
   return res;
}

// =============================================================================
// BindManagement::Server::save
// =============================================================================
/*!
 *
 */
// =============================================================================
void BindManagement::Server::save (Json::Value &root)
{
   LOG (INFO) << "Saving binding entries ..." << NL;

   unsigned i = 0;

   /* *INDENT-OFF* */
   for_each(entries().begin(), entries().end(),
            [&root, &i](const HF::Core::BindManagement::Entry &entry)
            {
               to_json (entry, root[i]);
               i++;
            });
   /* *INDENT-ON* */
}

// =============================================================================
// BindManagement::Server::restore
// =============================================================================
/*!
 *
 */
// =============================================================================
void BindManagement::Server::restore (Json::Value root)
{
   LOG (INFO) << "Restoring binding entries ..." << NL;

   for (unsigned i = 0; i < root.size (); i++)
   {
      HF::Core::BindManagement::Entry entry;
      from_json (root[i], entry);
      entries ().insert (entry);
      LOG (TRACE) << "Bind Add : " << entry.source.device
                  << " -> " << entry.destination.device << NL;
   }
}

// =============================================================================
// Events
// =============================================================================

// =============================================================================
// Events::Alert::status
// =============================================================================
/*!
 *
 */
// =============================================================================
void Events::Alert::status (HF::Protocol::Address &source, HF::Interfaces::Alert::Message &message)
{
   using namespace HF::Debug;

   LOG (INFO) << ">>>>>>>>>>>>> ALERT <<<<<<<<<<<<<" << std::endl
              << "\tSource | " << source << std::endl
              << "\tType   | 0x" << Hex <uint16_t>(message.type) << std::endl
              << "\tState  | 0x" << Hex <uint32_t>(message.state) << NL;
}

// =============================================================================
// Events::LevelControl::level_change
// =============================================================================
/*!
 *
 */
// =============================================================================
void Events::LevelControl::level_change (HF::Protocol::Address &source, uint8_t old_level,
                                         uint8_t new_level)
{
   using namespace HF::Debug;

   LOG (INFO) << ">>>>>>>>>>>>> LEVEL CONTROL <<<<<<<<<<<<<" << std::endl
              << "\tSource | " << source << std::endl
              << "\t   Old | " << Hex <uint8_t>(old_level) << std::endl
              << "\t   New | " << Hex <uint8_t>(new_level) << NL;
}

// =============================================================================
// Events::OnOff::on
// =============================================================================
/*!
 *
 */
// =============================================================================
void Events::OnOff::on (HF::Protocol::Address &source)
{
   using namespace HF::Debug;

   LOG (INFO) << ">>>>>>>>>>>>> ON-OFF <<<<<<<<<<<<<" << std::endl
              << "\tSource  | " << source << std::endl
              << "\tCommand | ON" << NL;
}

// =============================================================================
// Events::OnOff::off
// =============================================================================
/*!
 *
 */
// =============================================================================
void Events::OnOff::off (HF::Protocol::Address &source)
{
   using namespace HF::Debug;

   LOG (INFO) << ">>>>>>>>>>>>> ON-OFF <<<<<<<<<<<<<" << std::endl
              << "\tSource  | " << source << std::endl
              << "\tCommand | OFF" << NL;
}

// =============================================================================
// Events::OnOff::toggle
// =============================================================================
/*!
 *
 */
// =============================================================================
void Events::OnOff::toggle (HF::Protocol::Address &source)
{
   using namespace HF::Debug;

   LOG (INFO) << ">>>>>>>>>>>>> ON-OFF <<<<<<<<<<<<<" << std::endl
              << "\tSource  | " << source << std::endl
              << "\tCommand | TOGGLE" << NL;
}

// =============================================================================
// Events::SimplePowerMeter::report
// =============================================================================
/*!
 *
 */
// =============================================================================
void Events::SimplePowerMeter::report (HF::Protocol::Address &source,
                                       HF::Interfaces::SimplePowerMeter::Report &report)
{
   using namespace HF::Debug;

   UNUSED (report);
   LOG (INFO) << ">>>>>>>>>>>>> Simple Power Meter <<<<<<<<<<<<<" << std::endl
              << "\tSource  | " << source << std::endl
              << "\tReport  | " << NL;
}

// =============================================================================
// Commands
// =============================================================================

static void handle_device_infomation (HF::Common::ByteArray &payload, uint16_t offset)
{
   HF::Protocol::GetAttributePack::Response response (HF::Core::DeviceInformation::create_attribute);

   response.unpack (payload, offset);

   using namespace HF::Core::DeviceInformation;
   using namespace HF::Attributes;
   using namespace HF::Debug;

   uint8_t log_width = 20;

   LOG (INFO) << "====== Device Information : Attributes ======" << std::endl
              << std::right << std::setw (log_width) << std::setfill (' ');

   /* *INDENT-OFF* */
   std::for_each (response.attributes.begin (), response.attributes.end (),
                  [log_width](const HF::Attributes::IAttribute *attr)
   {
      LOG (APP) << std::right << std::setw (log_width) << std::setfill (' ');

      switch (attr->uid ())
      {
         case CORE_VERSION_ATTR:
         {
            auto *version = adapt <uint8_t>(attr);
            LOG (APP) << "Core (" << Hex <uint8_t>(attr->uid ()) << ") | 0x"
                      << Hex <uint8_t>(version->get ());
            break;
         }
         case PROFILE_VERSION_ATTR:
         {
            auto *version = adapt <uint8_t>(attr);
            LOG (APP) << "Profile (" << Hex <uint8_t>(attr->uid ()) << ") | 0x"
                      << Hex <uint8_t>(version->get ());
            break;
         }
         case INTERFACE_VERSION_ATTR:
         {
            auto *version = adapt <uint8_t>(attr);
            LOG (APP) << "Interface (" << Hex <uint8_t>(attr->uid ()) << ") | 0x"
                      << std::right << Hex <uint8_t>(version->get ());
            break;
         }
         case EXTRA_CAP_ATTR:
         {
            auto *extra_cap = adapt <uint8_t>(attr);
            LOG (APP) << "Extra Cap. (" << Hex <uint8_t>(attr->uid ()) << ") | 0x"
                      << Hex <uint8_t>(extra_cap->get ());
            break;
         }
         case MIN_SLEEP_TIME_ATTR:
         {
            auto *min_sleep = adapt <uint32_t>(attr);
            LOG (APP) << "Min. Sleep (" << Hex <uint8_t>(attr->uid ()) << ") | 0x"
                      << Hex <uint32_t>(min_sleep->get ());
            break;
         }
         case ACTUAL_RESP_TIME_ATTR:
         {
            auto *actual_time = adapt <uint32_t>(attr);
            LOG (APP) << "Actual Resp. Time (" << Hex <uint8_t>(attr->uid ()) << ") | 0x"
                      << Hex <uint32_t>(actual_time->get ());
            break;
         }
         case APP_VERSION_ATTR:
         {
            auto *version = adapt <std::string>(attr);
            LOG (APP) << "APP Version (" << Hex <uint8_t>(attr->uid ()) << ") | "
                      << version->get ();
            break;
         }
         case HW_VERSION_ATTR:
         {
            auto *version = adapt <std::string>(attr);
            LOG (APP) << "HW Version (" << Hex <uint8_t>(attr->uid ()) << ") | "
                      << version->get ();
            break;
         }
         case EMC_ATTR:
         {
            auto *emc = adapt <uint16_t>(attr);
            LOG (APP) << "EMC (" << Hex <uint8_t>(attr->uid ()) << ") | 0x"
                      << Hex <uint16_t>(emc->get ());
            break;
         }
         case DECT_ID_ATTR:
         {
            auto *dect = adapt < std::vector < uint8_t >> (attr);
            LOG (APP) << "DECT (" << Hex <uint8_t>(attr->uid ()) << ") | ";

            auto value = dect->get ();

            std::for_each(value.begin (), value.end (), [](uint8_t byte)
            {
               LOG (APP) << byte;
            });

            break;
         }
         case MANUFACTURE_NAME_ATTR:
         {
            auto *name = adapt <std::string>(attr);
            LOG (APP) << "Manuf. Name (" << Hex <uint8_t>(attr->uid ()) << ") | "
                      << name->get ();
            break;
         }
         case LOCATION_ATTR:
         {
            auto *location = adapt <std::string>(attr);
            LOG (APP) << "Location (" << Hex <uint8_t>(attr->uid ()) << ") | "
                      << location->get ();
            break;
         }
         case ENABLED_ATTR:
         {
            auto *enabled = adapt <uint8_t>(attr);
            LOG (APP) << "Enable (" << Hex <uint8_t>(attr->uid ()) << ") | 0x"
                      << Hex <uint8_t>(enabled->get ());
            break;
         }
         case FRIENDLY_NAME_ATTR:
         {
            auto *names_attr = adapt <FriendlyName>(attr);
            LOG (APP) << "Friendly Name (" << Hex <uint8_t>(attr->uid ()) << ") |";
            auto const &names = names_attr->get ();

            std::for_each (names.units.begin (), names.units.end (),
                           [](const FriendlyName::Unit &unit)
            {
               LOG (APP) << " (" << (int) unit.id << ") " << unit.name;
            });

            break;
         }
         case UID_ATTR:
         {
            auto *uid = adapt <HF::UID::UID>(attr);
            LOG (APP) << "UID (" << Hex <uint8_t>(attr->uid ()) << ") | "
                      << uid->get ();
            break;
         }
         case SERIAL_NUMBER_ATTR:
         {
            auto *serial = adapt <std::string>(attr);
            LOG (APP) << "Serial Number (" << Hex <uint8_t>(attr->uid ()) << ") | "
                      << serial->get ();
            break;
         }
         default:
         {
            LOG (APP) << "Unknown | UID - " << attr->uid () << std::endl;
            break;
         }
      }

      LOG (APP) << std::endl;

   });
   /* *INDENT-ON* */

   LOG (INFO) << "====== Device Information : Attributes ======" << NL;
}

// =============================================================================
// Commands::Unit::handle
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Common::Result Commands::Unit::handle (HF::Protocol::Packet &packet,
                                           HF::Common::ByteArray &payload, uint16_t offset)
{
   UNUSED (packet);
   UNUSED (payload);
   UNUSED (offset);

   if (packet.message.type == HF::Protocol::Message::GET_ATTR_PACK_RES &&
       packet.message.itf.id == HF::Interface::DEVICE_INFORMATION)
   {
      handle_device_infomation (payload, offset);
      return HF::Common::Result::OK;
   }

   return HF::Common::Result::FAIL_ARG;
}

// =============================================================================
// Base
// =============================================================================

// =============================================================================
// Base::receive
// =============================================================================
/*!
 *
 */
// =============================================================================
void Base::receive (HF::Protocol::Packet &packet, HF::Common::ByteArray &payload, uint16_t offset)
{
   LOG (DEBUG) << ">>>>>>>>>>>>> Message Received <<<<<<<<<<<<<" << NL;

   LOG (TRACE) << "Payload : " << payload << NL;

   LOG (DEBUG) << std::endl << packet << NL;

   HF::Devices::Concentrator::Abstract <Unit0>::receive (packet, payload, offset);
}

// =============================================================================
// Base::has_bind
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Base::has_bind (uint16_t dev_addr_1, uint16_t dev_addr_2)
{
   HF::Protocol::Address source (dev_addr_1, 1);
   HF::Common::Interface itf (HF::Interface::ON_OFF, HF::Interface::SERVER_ROLE);
   HF::Protocol::Address destination (dev_addr_2, 1);

   return _unit0.bind_management ()->entries ().find (source, itf, destination) != nullptr;
}

// =============================================================================
// Base::bind
// =============================================================================
/*!
 *
 */
// =============================================================================
uint8_t Base::bind (uint16_t dev_addr_1, uint16_t dev_addr_2)
{
   if (this->has_bind (dev_addr_1, dev_addr_2))
   {
      return 1;
   }

   HF::Protocol::Address source (dev_addr_1, 1);
   HF::Common::Interface itf (HF::Interface::ON_OFF, HF::Interface::SERVER_ROLE);
   HF::Protocol::Address destination (dev_addr_2, 1);

   auto res = _unit0.bind_management ()->add (source, destination, itf);

   if (res == HF::Common::OK)
   {
      return 0;
   }

   if (_unit0.device_management ()->entry (dev_addr_1) == nullptr)
   {
      return 2;
   }

   if (_unit0.device_management ()->entry (dev_addr_2) == nullptr)
   {
      return 3;
   }

   return 4;
}

// =============================================================================
// Base::unbind
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Base::unbind (uint16_t dev_addr_1, uint16_t dev_addr_2)
{
   HF::Protocol::Address source (dev_addr_1, 1);
   HF::Common::Interface itf (HF::Interface::ON_OFF, HF::Interface::SERVER_ROLE);
   HF::Protocol::Address destination (dev_addr_2, 1);

   return _unit0.bind_management ()->remove (source, destination, itf) == HF::Common::Result::OK;
}

// =============================================================================
// Helper Functions
// =============================================================================

static std::string json_uid (uint16_t uid)
{
   std::ostringstream convert;

   convert << "0x" << std::setfill ('0') << std::setw (sizeof(uint16_t) * 2)
           << std::hex << uid;

   return convert.str ();
}

static uint16_t json_uid (std::string uid)
{
   return STRTOL_HEX (uid.substr (2));
}

// =============================================================================
// to_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void to_json (const HF::Common::Interface &interface, Json::Value &node)
{
   if (interface.role == HF::Interface::SERVER_ROLE)
   {
      node["role"] = "server";
   }
   else
   {
      node["role"] = "client";
   }

   node["id"] = json_uid (interface.id);
}

// =============================================================================
// to_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void to_json (const HF::UID::UID &uid, Json::Value &node)
{
   switch (uid.type ())
   {
      case HF::UID::NONE_UID:
      {
         node["type"]  = "none";
         node["value"] = 0;
      }

      case HF::UID::DECT_UID: // RFPI
      {
         node["type"] = "dect";

         const HF::UID::DECT *dect = static_cast <const HF::UID::DECT *>(uid.raw ());

         for (uint8_t i = 0; i < HF::UID::DECT::length (); i++)
         {
            node["value"][i] = (int) (*dect)[i];
         }

         break;
      }

      case HF::UID::MAC_UID:
      {
         node["type"] = "mac";

         const HF::UID::MAC *mac = static_cast <const HF::UID::MAC *>(uid.raw ());

         for (int i = 0; i < 6; i++)
         {
            node["value"][i] = (int) (*mac)[i];
         }

         break;
      }

      case HF::UID::URI_UID:
      {
         node["type"]  = "uri";
         node["value"] = static_cast <const HF::UID::URI *>(uid.raw ())->str ();
         break;
      }
   }
}

// =============================================================================
// to_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void to_json (const HF::Core::DeviceManagement::Unit &unit, Json::Value &node)
{
   node["id"]      = unit.id;

   node["profile"] = json_uid (unit.profile);

   for (unsigned i = 0; i < unit.interfaces.size (); i++)
   {
      to_json (unit.interfaces[i], node["opts"][i]);
   }
}

// =============================================================================
// to_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void to_json (const HF::Core::DeviceManagement::Device &device, Json::Value &node)
{
   node["address"] = device.address;

   for (unsigned i = 0; i < device.units.size (); i++)
   {
      to_json (device.units[i], node["units"][i]);
   }

   node["emc"] = json_uid (device.emc);

   to_json (device.uid, node["uid"]);
}

// =============================================================================
// to_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void to_json (const HF::Protocol::Address &address, Json::Value &node)
{
   node["mod"]    = (int) address.mod;
   node["device"] = (int) address.device;
   node["unit"]   = (int) address.unit;
}

// =============================================================================
// to_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void to_json (const HF::Core::BindManagement::Entry &entry, Json::Value &node)
{
   to_json (entry.source, node["src"]);
   to_json (entry.destination, node["dst"]);
   to_json (entry.itf, node["itf"]);
}

// =============================================================================
// from_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void from_json (Json::Value &node, HF::Common::Interface &interface)
{
   std::string role = node.get ("role", "client").asString ();

   if (role[0] == 's' || role[0] == 'S')
   {
      interface.role = HF::Interface::SERVER_ROLE;
   }
   else
   {
      interface.role = HF::Interface::CLIENT_ROLE;
   }

   interface.id = json_uid (node.get ("id", "0x7FFF").asString ());
}

// =============================================================================
// from_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void from_json (Json::Value &node, HF::UID::UID &uid)
{
   std::string uid_type = node.get ("type", "none").asString ();

   if (uid_type == "none")
   {
      HF::UID::NONE *none = new HF::UID::NONE;
      uid = none;
   }
   else if (uid_type == "dect")
   {
      HF::UID::DECT *dect = new HF::UID::DECT;

      for (unsigned i = 0; i < node["value"].size (); ++i)
      {
         (*dect)[i] = (uint8_t) node["value"][i].asUInt ();
      }

      uid = dect;
   }
   else if (uid_type == "mac")
   {
      HF::UID::MAC *mac = new HF::UID::MAC;

      for (unsigned i = 0; i < node["value"].size (); ++i)
      {
         (*mac)[i] = (uint8_t) node["value"][i].asUInt ();
      }

      uid = mac;
   }
   else if (uid_type == "uri")
   {
      HF::UID::URI *uri = new HF::UID::URI;
      uri->value = node["value"].asString ();
      uid        = uri;
   }
}

// =============================================================================
// from_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void from_json (Json::Value &node, HF::Core::DeviceManagement::Unit &unit)
{
   unit.id      = (uint8_t) node.get ("id", HF::Protocol::BROADCAST_UNIT).asUInt ();

   unit.profile = json_uid (node.get ("profile", "0x7FFF").asString ());

   for (unsigned i = 0; i < node["opts"].size (); i++)
   {
      unit.interfaces.push_back (0);
      from_json (node["opts"][i], unit.interfaces[i]);
   }
}

// =============================================================================
// from_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void from_json (Json::Value &node, HF::Core::DeviceManagement::Device &dev)
{
   dev.address = (uint16_t) node.get ("address", HF::Protocol::BROADCAST_ADDR).asUInt ();

   for (unsigned i = 0; i < node["units"].size (); i++)
   {
      dev.units.push_back (0);
      from_json (node["units"][i], dev.units[i]);
   }

   dev.emc = json_uid (node.get ("emc", "0x0000").asString ());

   from_json (node["uid"], dev.uid);
}

// =============================================================================
// from_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void from_json (Json::Value &node, HF::Protocol::Address &addr)
{
   addr.mod    = (uint16_t) node.get ("mod", 0).asUInt ();
   addr.device = (uint16_t) node.get ("device", 0).asUInt ();
   addr.unit   = (uint8_t) node.get ("unit", 0).asUInt ();
}

// =============================================================================
// from_json
// =============================================================================
/*!
 *
 */
// =============================================================================
void from_json (Json::Value &node, HF::Core::BindManagement::Entry &entry)
{
   from_json (node["src"], entry.source);
   from_json (node["dst"], entry.destination);
   from_json (node["itf"], entry.itf);
}

/*! @} */
