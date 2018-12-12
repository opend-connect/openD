// =============================================================================
/*!
 * @file       apps/base_app.cpp
 *
 * This file contains an example for a HAN-FUN base application.
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
#include <string>

#include <unistd.h>

#include <forward_list>
#include <algorithm>

#include "hanfun.h"

#include "base.h"

#include "application.h"

#include "common.h"

#include "json/json.h"

/*!
 * @addtogroup examples
 * @{
 */

// =============================================================================
// Defines
// =============================================================================

#ifndef HF_APP_CONFIG_FILE
   #define HF_APP_CONFIG_FILE   "./hanfun.json"    //!< JSON database file.
#endif

// =============================================================================
// Global Variables
// =============================================================================

//! Concentrator instance.
static Base base;

// =============================================================================
// Commands
// =============================================================================

/*!
 * ListRegs List registrations command.
 */
COMMAND (ListRegs, "lr", "lr:list registrations.")
{
   UNUSED (args);

   auto &devices = base.unit0 ()->device_management ()->entries ();

   LOG (APP) << std::setfill (' ');
   LOG (APP) << "HAN-FUN" << "  Registered Devices (" << (int) devices.size () << "):" << NL;

   /* *INDENT-OFF* */
   std::for_each(devices.begin(), devices.end(), [](const HF::Core::DeviceManagement::Device &device)
   {
      LOG (APP) << (base.link (device.address) != nullptr ? "+ " : "- ");
      LOG (APP) << std::right << std::setw (5) << device.address << " | ";
      LOG (APP) << device.uid << NL;
   });
   /* *INDENT-ON* */
}

/*!
 * List binds command.
 */
COMMAND (ListBinds, "lb", "lb:list binds.")
{
   UNUSED (args);

   HF::Core::BindManagement::Entries &entries = base.unit0 ()->bind_management ()->entries ();

   LOG (APP) << "HAN-FUN Binds (" << entries.size () << "):" << NL;
   LOG (APP) << "\t" << std::left << std::setfill(' ')
             << std::setw(16) << "Source"
             << std::setw(18) << "| Destination"
             << "| Interface" << std::endl
             << "\t" << std::setfill('-')
             << std::setw(15) << "-"
             << std::setw(18) << " | "
             << std::setw(12) << " | " << std::endl
             << std::setfill(' ');

   /* *INDENT-OFF* */
   std::for_each (entries.begin (), entries.end (),
                  [](const HF::Core::BindManagement::Entry &entry)
   {
      LOG (APP) << "\t" << entry.source << " | " << entry.destination << " | "
                << entry.itf << NL;
   });
   /* *INDENT-ON* */
}

/*!
 * Setup registration command.
 */
COMMAND (Register, "r", "r 1 x:register device x.\nr 0:exit registration mode.")
{
   if (args.size () > 0 && args[0] == "0") //!< Disable Registration
   {
#ifdef HF_APP_EXT_REG

      if (HF::Application::Registration (false))
      {
         LOG (INFO) << "Disable Registration mode: SUCCESS" << NL;
      }
      else
      {
         LOG (WARN) << "Disable Registration mode: FAIL" << NL;
      }

#endif
   }
   else if (args.size () > 1 && args[0] == "1") //!< Enable Registration
   {
      uint16_t address = STRTOL (args[1]);

      if (base.unit0 ()->device_management ()->available (address) && address != 0 &&
          address < HF::Protocol::BROADCAST_ADDR)
      {
         base.unit0 ()->device_management ()->next_address (address);
#ifdef HF_APP_EXT_REG

         if (HF::Application::Registration (true))
         {
            LOG (INFO) << "Enable Registration mode: SUCCESS" << NL;
         }
         else
         {
            LOG (WARN) << "[HANFUN] Enable Registration mode: FAIL" << NL;
         }

#endif
         LOG (INFO) << "Next Registration will have address : " << (int) address << NL;
      }
      else
      {
         LOG (ERROR) << "Registration impossible: address " << (int) address
                     << "  not available." << NL;
      }

      return;
   }

   LOG (APP) << usage (true) << NL;
}

/*!
 * De-register device command.
 */
COMMAND (Deregister, "d", "d x:de-register device x.")
{
   if (args.size () < 1)
   {
      LOG (APP) << usage (true) << NL;
      return;
   }

   uint16_t address = STRTOL (args[0]);

#ifdef HF_APP_EXT_REG
   // External de-registration.
   HF::Application::Deregister (address);
#endif

   /* HAN-FUN de-registration */
   bool res = base.unit0 ()->device_management ()->deregister (address);
   LOG (INFO) << "Device " << (int) address << " de-registration: "
              << (res ? "SUCCESS" : "FAIL") << " !" << NL;
}

/*!
 * Create bind command.
 */
COMMAND (Bind, "b", "b x y:associate device x with device y (bind).")
{
   if (args.size () < 2)
   {
      LOG (APP) << usage (true) << NL;
      return;
   }

   uint16_t arg1 = STRTOL (args[0]);
   uint16_t arg2 = STRTOL (args[1]);

   uint8_t  err  = base.bind (arg1, arg2);

   switch (err)
   {
      case 0:
      {
         LOG (INFO) << "Bind created !" << NL;
         break;
      }
      case 1:
      {
         LOG (WARN) << "Bind already created !" << NL;
         break;
      }
      case 2:
      case 3:
      {
         LOG (ERROR) << "Bind impossible: " << NL;

         if ((err & 0x01) != 0)
         {
            LOG (ERROR) << "  - Second device does not exist !" << NL;
         }
         else
         {
            LOG (ERROR) << "  - Fist device does not exist !" << NL;
         }

         break;
      }
      default:
         LOG (ERROR) << "No match for bind !" << NL;
         break;
   }
}

/*!
 * Destroy bind command.
 */
COMMAND (Unbind, "u", "u x y:unbind device x with y.")
{
   UNUSED (args);

   if (args.size () < 2)
   {
      LOG (APP) << usage (true) << NL;
      return;
   }

   uint16_t arg1 = STRTOL (args[0]);
   uint16_t arg2 = STRTOL (args[1]);

   if (base.unbind (arg1, arg2))
   {
      LOG (INFO) << "Bind: " << arg1 << " - " << arg2 << " removed !" << NL;
   }
   else
   {
      LOG (ERROR) << "Bind: does not exist !" << NL;
   }
}

/*!
 * Global binds command.
 */
COMMAND (GlobalBind, "gb", "gb 1:create bind to receive all interface events.\n"
                           "gb 0:remove bind to receive all interface events.")
{
   if (args.size () < 1)
   {
      LOG (APP) << usage (true) << NL;
      return;
   }

   uint16_t arg1 = STRTOL (args[0]);

   HF::Common::Interface itf(HF::Interface::ANY_UID);
   HF::Protocol::Address source;
   HF::Protocol::Address dest (0, 1);

   if (arg1 == 1)
   {
      // Bind any interface.
      auto res = base.unit0 ()->bind_management ()->add (source, dest, itf);
      assert (res == HF::Common::Result::OK);
      UNUSED (res);
   }
   else if (arg1 == 0)
   {
      // Bind any interface.
      auto res = base.unit0 ()->bind_management ()->remove (source, dest, itf);
      assert (res == HF::Common::Result::OK);
      UNUSED (res);
   }
   else
   {
      LOG (APP) << usage (true) << NL;
   }
}

/*!
 * Send ON command.
 */
COMMAND (On, "on", "on d u:Send an ON command to device/unit pair.")
{
   if (args.size () < 2)
   {
      LOG (APP) << usage (true) << NL;
      return;
   }

   uint16_t arg1 = STRTOL (args[0]);
   uint16_t arg2 = STRTOL (args[1]);

   HF::Protocol::Address device (arg1, arg2);
   base.commands.on_off ().on (device);
}

/*!
 * Send OFF command.
 */
COMMAND (Off, "off", "off d u:Send an OFF command to device/unit pair.")
{
   if (args.size () < 2)
   {
      LOG (APP) << usage (true) << NL;
      return;
   }

   uint16_t arg1 = STRTOL (args[0]);
   uint16_t arg2 = STRTOL (args[1]);

   HF::Protocol::Address device (arg1, arg2);
   base.commands.on_off ().off (device);
}

/*!
 * Send TOGGLE command.
 */
COMMAND (Toggle, "toggle", "toggle d u:Send a TOGGLE command to device/unit pair.")
{
   if (args.size () < 2)
   {
      LOG (APP) << usage (true) << NL;
      return;
   }

   uint16_t arg1 = STRTOL (args[0]);
   uint16_t arg2 = STRTOL (args[1]);

   HF::Protocol::Address device (arg1, arg2);
   base.commands.on_off ().toggle (device);
}

COMMAND (Raw, "raw", "raw <raw data>:simulate receiving a packet from the network.")
{
   HF::Common::ByteArray data;

   data.reserve (args.size ());

   /* *INDENT-OFF* */
   std::for_each (args.begin (), args.end (), [&data](std::string byte)
   {
      uint8_t temp = STRTOL_HEX (byte);
      data.push_back (temp);
   });
   /* *INDENT-ON* */

   HF::Protocol::Packet packet;
   uint16_t offset = packet.unpack (data);

   packet.link = base.link (packet.source.device);
   base.receive (packet, data, offset);
}

/*!
 * Get Device information.
 */
COMMAND (DevInfo, "di", "di m d:Get device information mandatory attributes.\n"
                        "di a d:Get device information all attributes.")
{
   if (args.size () < 2)
   {
      LOG (APP) << usage (true) << NL;
      return;
   }

   uint16_t arg1 = STRTOL (args[1]);

   HF::Protocol::Address device (arg1, 0);

   HF::Protocol::Message *msg = nullptr;

   if (args[0] == "m")
   {
      msg = HF::Core::DeviceInformation::mandatory ();
   }
   else if (args[0] == "a")
   {
      msg = HF::Core::DeviceInformation::all ();
   }

   if (msg != nullptr)
   {
      base.commands.send (device, *msg, nullptr);
      delete msg;
   }
   else
   {
      LOG (APP) << usage (true) << NL;
   }
}

COMMAND (Links, "ll", "ll :list links.")
{
   UNUSED (args);

   auto &links = base.links();

   /* *INDENT-OFF* */
   std::for_each(links.begin(), links.end(), [](const HF::Transport::Link *link)
   {
      LOG (APP) << std::setw (5) << link->address() << " | ";
      LOG (APP) << link->uid() << NL;
   });
   /* *INDENT-ON* */

}

// =============================================================================
// HF::Application::Initialize
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::Application::Initialize (HF::Transport::Layer &transport)
{
   LOG (TRACE) << __PRETTY_FUNCTION__ << NL;

   transport.initialize ();

   transport.add (&base);

   COMMAND_ADD (ListRegs);
   COMMAND_ADD (ListBinds);
   COMMAND_ADD (Register);
   COMMAND_ADD (Deregister);
   COMMAND_ADD (Bind);
   COMMAND_ADD (Unbind);
   COMMAND_ADD (GlobalBind);
   COMMAND_ADD (On);
   COMMAND_ADD (Off);
   COMMAND_ADD (Toggle);
   COMMAND_ADD (Raw);
   COMMAND_ADD (DevInfo);
   COMMAND_ADD (Links);

   Restore ();
}

// =============================================================================
// HF::Application::Save
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::Application::Save ()
{
   Json::Value root;
   Json::StyledWriter writer;
   std::ofstream ofs (HF_APP_CONFIG_FILE);

   base.unit0 ()->device_management ()->save (root["core"]["device_management"]);
   base.unit0 ()->bind_management ()->save (root["core"]["bind_management"]);

   if (ofs.is_open ())
   {
      ofs << root;
      ofs.close ();
   }

   Saved ();
}

// =============================================================================
// HF::Application::Restore
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::Application::Restore ()
{
   Json::Reader  reader;
   Json::Value   root;

   std::ifstream ifs (HF_APP_CONFIG_FILE);

   if (reader.parse (ifs, root, false) == false)
   {
      LOG (WARN) << "Reading configuration file !!" << reader.getFormattedErrorMessages () << NL;
   }
   else
   {
      base.unit0 ()->device_management ()->restore (root["core"]["device_management"]);
      base.unit0 ()->bind_management ()->restore (root["core"]["bind_management"]);
   }

   ifs.close ();

   Restored ();
}
/*! @} */
