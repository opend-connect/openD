// =============================================================================
/*!
 * @file       apps/example_03.cpp
 *
 * This file contains an usage example of the Alert interface.
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

#include "hanfun.h"
#include "hanfun/debug.h"

#include "localloop.h"

// =============================================================================
// Implementation
// =============================================================================

namespace
{
   /*
    * Unit implementing the Simple Detector profile.
    */
   struct SimpleDetector:public HF::Units::Unit <HF::Profiles::SimpleDetector>
   {
      SimpleDetector(uint8_t id, HF::IDevice &device):
         HF::Units::Unit <HF::Profiles::SimpleDetector>(id, device)
      {}
   };

   /*
    * Unit implementing the Alertable profile, to receive alert events.
    */
   struct AlertSink:public HF::Units::Unit <HF::Profiles::Alertable>
   {
      AlertSink(uint8_t id, HF::IDevice &device):
         HF::Units::Unit <HF::Profiles::Alertable>(id, device)
      {}

      void status (HF::Protocol::Address &source, HF::Interfaces::Alert::Message &message)
      {
         HF::Units::Unit <HF::Profiles::Alertable>::status (source, message);

         LOG (INFO) << "Alert received " << std::hex << std::showbase
                    << message.state << " !" << NL;
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

   LOG (INFO) << "Use case : Alert interface usage" << NL;

   /*
    * Each node variable is a remote device, i.e.,
    * the Node variables are declared on the remote device
    * code and are not used on the base code.
    */
   LOG (INFO) << "Create the node instances ..." << NL;

   Node node1;

   LOG (INFO) << "Add unit to node1 instance ..." << NL;
   SimpleDetector simple_detector (1, node1);

   Node node2;

   LOG (INFO) << "Add unit to node2 instance ..." << NL;
   AlertSink alert_sink (1, node2);

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
   // Send alerts a specific device/unit.
   // =============================================================================

   LOG (INFO) << "Send alerts to a specific device/unit ... " << NL;

   HF::Protocol::Address addr (2, 1);

   LOG (INFO) << "Send alert on ..." << NL;
   simple_detector.alert (addr, true);

   LOG (INFO) << "Send alert off ... " << NL;
   simple_detector.alert (addr, false);

   // =============================================================================
   // Send alerts to the broadcast device/unit.
   // =============================================================================

   LOG (INFO) << "Send alerts to the broadcast device/unit ... " << NL;

   // Create a bind entry.
   LOG (INFO) << "Create bind entry on the base ... " << NL;
   HF::Protocol::Address source (1, 1);
   HF::Protocol::Address destination (2, 1);
   HF::Common::Interface itf (HF::Interface::ALERT, HF::Interface::CLIENT_ROLE);

   base.unit0 ()->bind_management ()->add (source, destination, itf);
   LOG (INFO) << "There should be one bind entry ... "
              << base.unit0 ()->bind_management ()->entries ().size () << NL;
   assert (base.unit0 ()->bind_management ()->entries ().size () == 1);

   LOG (INFO) << "Send alert on to the broadcast device/unit ... " << NL;
   simple_detector.alert (true);

   LOG (INFO) << "Send alert off to the broadcast device/unit ... " << NL;
   simple_detector.alert (false);

   return 0;
}
