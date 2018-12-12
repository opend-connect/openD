// =============================================================================
/*!
 * @file       apps/example_05.cpp
 *
 * This file contains an example use of the Level control interface.
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

#include "hanfun.h"
#include "hanfun/debug.h"

#include "localloop.h"

// =============================================================================
// Implementation
// =============================================================================

namespace
{
   /*
    * Unit implementing the Simple %Level Control profile.
    */
   struct SimpleLevelControl:public HF::Units::Unit <HF::Profiles::SimpleLevelControl>
   {
      SimpleLevelControl(uint8_t id, HF::IDevice &device):
         HF::Units::Unit <HF::Profiles::SimpleLevelControl>(id, device)
      {}
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

   LOG (INFO) << "Set initial level value ... 10\%" << NL;
   level_controllable.level (10.0f);

   // =============================================================================
   // Send change level message to a specific device/unit
   // =============================================================================

   LOG (INFO) << "Send level change to a specific device/unit ..." << NL;

   HF::Protocol::Address addr (2, 1);

   LOG (INFO) << "Change level to 20\% ..." << NL;
   level_control.level (addr, 20.0f);

   LOG (INFO) << "Level Controllable should have new level value : "
              << (int) HF::Common::to_percent (level_controllable.level ()) << "\%" << NL;
   assert (level_controllable.level () == HF::Common::from_percent <uint8_t>(20.0));

   // =============================================================================
   // Send change level message to the broadcast device/unit
   // =============================================================================

   LOG (INFO) << "Send level change to the broadcast device/unit ..." << NL;

   // Create a bind entry.
   LOG (INFO) << "Create bind entry on the base ... " << NL;
   HF::Protocol::Address source (1, 1);
   HF::Protocol::Address destination (2, 1);
   HF::Common::Interface itf (HF::Interface::LEVEL_CONTROL, HF::Interface::SERVER_ROLE);

   base.unit0 ()->bind_management ()->add (source, destination, itf);
   LOG (INFO) << "There should be one bind entry ... "
              << base.unit0 ()->bind_management ()->entries ().size () << NL;
   assert (base.unit0 ()->bind_management ()->entries ().size () == 1);

   LOG (INFO) << "Change level to 50\% ..." << NL;
   level_control.level (50.0f);

   LOG (INFO) << "Level Controllable should have new level value : "
              << (int) HF::Common::to_percent (level_controllable.level ()) << "\%" << NL;
   assert (level_controllable.level () == HF::Common::from_percent <uint8_t>(50));

   return 0;
}
