// =============================================================================
/*!
 * @file       apps/node_app.cpp
 *
 * This file contains the implementation of the example application for a
 * HAN-FUN Node.
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

#include <unistd.h>

#include <forward_list>
#include <algorithm>

#include "node.h"

#include "common.h"

#include "application.h"

/*!
 * @addtogroup examples
 * @{
 */

// =============================================================================
// Global Variables.
// =============================================================================

//! HAN-FUN Node instance.
static Node node;

//! Simple Light unit.
static SimpleLight *simple_light = nullptr;

//! Simple Switch unit.
static SimpleSwitch *simple_switch = nullptr;

// =============================================================================
// Commands
// =============================================================================

/*!
 * Register node command.
 */
COMMAND (Register, "r", "r:register device")
{
   UNUSED (args);
   LOG (TRACE) << __PRETTY_FUNCTION__ << NL;

   node.unit0 ()->device_management ()->register_device ();
}

/*!
 * Print node address command.
 */
COMMAND (Address, "a", "a:device address")
{
   UNUSED (args);
   LOG (TRACE) << __PRETTY_FUNCTION__ << NL;

   LOG (APP) << "Device Address : " << node.address () << NL;
}

/*!
 * Change device to a simple light.
 */
COMMAND (SimpleLight, "sl", "sl:set device as a simple light")
{
   UNUSED (args);
   LOG (TRACE) << __PRETTY_FUNCTION__ << NL;

   if (simple_switch != nullptr)
   {
      delete simple_switch;
   }

   if (simple_light == nullptr)
   {
      simple_light = new SimpleLight (1, node);
   }

   LOG (APP) << "Device is now a Simple Light !" << NL;
}

/*!
 * Change device to a simple switch.
 */
COMMAND (SimpleSwitch, "ss", "ss:set device as a simple switch")
{
   UNUSED (args);
   LOG (TRACE) << __PRETTY_FUNCTION__ << NL;

   if (simple_light != nullptr)
   {
      delete simple_light;
   }

   if (simple_switch == nullptr)
   {
      simple_switch = new SimpleSwitch (1, node);
   }

   LOG (APP) << "Device is now a Simple Switch !" << NL;
}

/*!
 * Send an on command from the simple switch.
 */
COMMAND (On, "on", "on:On Command")
{
   UNUSED (args);
   LOG (TRACE) << __PRETTY_FUNCTION__ << NL;

   if (simple_switch != nullptr)
   {
      simple_switch->on ();
   }
   else
   {
      LOG (ERROR) << "Simple Switch not configured !" << NL;
   }
}

/*!
 * Send an off command from the simple switch.
 */
COMMAND (Off, "off", "off:Off Command")
{
   UNUSED (args);
   LOG (TRACE) << __PRETTY_FUNCTION__ << NL;

   if (simple_switch != nullptr)
   {
      simple_switch->off ();
   }
   else
   {
      LOG (ERROR) << "Simple Switch not configured !" << NL;
   }
}

/*!
 * Send a toggle command from the simple switch.
 */
COMMAND (Toggle, "toggle", "toggle:Toggle Command")
{
   UNUSED (args);
   LOG (TRACE) << __PRETTY_FUNCTION__ << NL;

   if (simple_switch != nullptr)
   {
      simple_switch->toggle ();
   }
   else
   {
      LOG (ERROR) << "Simple Switch not configured !" << NL;
   }
}

// =============================================================================
// API
// =============================================================================

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

   transport.add (&node);

   COMMAND_ADD (Register);
   COMMAND_ADD (Address);
   COMMAND_ADD (SimpleLight);
   COMMAND_ADD (SimpleSwitch);
   COMMAND_ADD (On);
   COMMAND_ADD (Off);
   COMMAND_ADD (Toggle);

   HF::Application::Restore ();
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
   Restored ();
}

/*! @} */
