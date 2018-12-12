// =============================================================================
/*!
 * @file       apps/example_04.cpp
 *
 * This file contains an usage example of the On-Off interface.
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

#include <assert.h>

#include "hanfun.h"
#include "hanfun/debug.h"

#include "localloop.h"

// =============================================================================
// Implementation
// =============================================================================

namespace
{
   /*
    * Unit implementing the Simple On-Off Switch profile.
    */
   struct SimpleSwitch:public HF::Units::Unit <HF::Profiles::SimpleOnOffSwitch>
   {
      SimpleSwitch(uint8_t id, HF::IDevice &device):
         HF::Units::Unit <HF::Profiles::SimpleOnOffSwitch>(id, device)
      {}
   };

   /*
    * Unit implementing the Simple OnOff Switchable profile.
    */
   struct SimpleSwitchable:public HF::Units::Unit <HF::Profiles::SimpleOnOffSwitchable>
   {
      typedef HF::Units::Unit <HF::Profiles::SimpleOnOffSwitchable> _Parent;

      SimpleSwitchable(uint8_t id, HF::IDevice &device):_Parent (id, device)
      {}

      void on (HF::Protocol::Address &source)
      {
         _Parent::on (source);
         LOG (INFO) << "Command ON received ..." << NL;
      }

      void off (HF::Protocol::Address &source)
      {
         _Parent::off (source);
         LOG (INFO) << "Command OFF received ..." << NL;
      }

      void toggle (HF::Protocol::Address &source)
      {
         _Parent::toggle (source);
         LOG (INFO) << "Command TOGGLE received ..." << NL;
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

   LOG (INFO) << "Use case : On-Off interface usage" << NL;

   /*
    * Each node variable is a remote device, i.e.,
    * the Node variables are declared on the remote device
    * code and are not used on the base code.
    */
   LOG (INFO) << "Create the node instances ..." << NL;

   Node node1;

   LOG (INFO) << "Add unit to node1 instance ..." << NL;
   SimpleSwitch simple_switch (1, node1);

   Node node2;

   LOG (INFO) << "Add unit to node2 instance ..." << NL;
   SimpleSwitchable simple_switchable (1, node2);

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

   // =============================================================================
   // Send ON/OFF/TOGGLE to a specific device/unit
   // =============================================================================

   LOG (INFO) << "Send commands to a specific device/unit ..." << NL;

   HF::Protocol::Address addr (2, 1);

   // On Command.
   LOG (INFO) << "Send a ON command ..." << NL;
   simple_switch.on (addr);
   LOG (INFO) << "Switchable state should be ON : " << simple_switchable.state () << NL;
   assert (simple_switchable.state () == true);

   // Off Command.
   LOG (INFO) << "Send a OFF command ..." << NL;
   simple_switch.off (addr);
   LOG (INFO) << "Switchable state should be OFF : " << simple_switchable.state () << NL;
   assert (simple_switchable.state () == false);

   // Toggle Command
   LOG (INFO) << "Send a TOGGLE command ... " << NL;
   simple_switch.toggle (addr);
   LOG (INFO) << "Switchable state should be ON : " << simple_switchable.state () << NL;
   assert (simple_switchable.state () == true);

   LOG (INFO) << "Send a second TOGGLE command ... " << NL;
   simple_switch.toggle (addr);
   LOG (INFO) << "Switchable state should be OFF : " << simple_switchable.state () << NL;
   assert (simple_switchable.state () == false);

   // =============================================================================
   // Send ON/OFF/TOGGLE to the broadcast device/unit
   // =============================================================================

   LOG (INFO) << "Send commands to the broadcast device/unit ..." << NL;

   // Create a bind entry.
   LOG (INFO) << "Create bind entry on the base ... " << NL;
   HF::Protocol::Address source (1, 1);
   HF::Protocol::Address destination (2, 1);
   HF::Common::Interface itf (HF::Interface::ON_OFF, HF::Interface::SERVER_ROLE);

   base.unit0 ()->bind_management ()->add (source, destination, itf);
   LOG (INFO) << "There should be one bind entry ... "
              << base.unit0 ()->bind_management ()->entries ().size () << NL;
   assert (base.unit0 ()->bind_management ()->entries ().size () == 1);

   // On Command.
   LOG (INFO) << "Send a ON command ..." << NL;
   simple_switch.on ();
   LOG (INFO) << "Switchable state should be ON : " << simple_switchable.state () << NL;
   assert (simple_switchable.state () == true);

   // Off Command.
   LOG (INFO) << "Send a OFF command ..." << NL;
   simple_switch.off ();
   LOG (INFO) << "Switchable state should be OFF : " << simple_switchable.state () << NL;
   assert (simple_switchable.state () == false);

   // Toggle Command
   LOG (INFO) << "Send a TOGGLE command ... " << NL;
   simple_switch.toggle ();
   LOG (INFO) << "Switchable state should be ON : " << simple_switchable.state () << NL;
   assert (simple_switchable.state () == true);

   LOG (INFO) << "Send a second TOGGLE command ... " << NL;
   simple_switch.toggle ();
   LOG (INFO) << "Switchable state should be OFF : " << simple_switchable.state () << NL;
   assert (simple_switchable.state () == false);

   return 0;
}
