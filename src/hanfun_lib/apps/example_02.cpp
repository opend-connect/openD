// =============================================================================
/*!
 * @file       apps/example_02.cpp
 *
 * This file contains an example demonstrating registration event handling.
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
   // =============================================================================
   // Node
   // =============================================================================
   //! [Node custom code]

   /*
    * Custom Device Management service for the node.
    */
   struct DeviceManagementClient:public HF::Core::DeviceManagement::Client
   {
      DeviceManagementClient(HF::Core::Unit0 &unit):
         HF::Core::DeviceManagement::Client (unit)
      {}

      void registered (HF::Core::DeviceManagement::RegisterResponse &response)
      {
         HF::Core::DeviceManagement::Client::registered (response);

         LOG (INFO) << ">>> Registration response <<<" << NL;
         LOG (INFO) << "   Code : " << (int) response.code << NL;
         LOG (INFO) << "Address : " << response.address << NL;
         LOG (INFO) << "    EMC : " << response.emc << NL;
      }
   };

   /*
    * Custom Unit 0 for node with the custom Device Management service.
    */
   struct NodeUnit0:public HF::Devices::Node::Unit0 <HF::Core::DeviceInformation::Server,
                                                     DeviceManagementClient,
                                                     HF::Core::AttributeReporting::Server>
   {
      NodeUnit0(HF::IDevice &device):
         HF::Devices::Node::Unit0 <HF::Core::DeviceInformation::Server, DeviceManagementClient,
                                   HF::Core::AttributeReporting::Server>(device)
      {}
   };

   /*
    * Example node.
    */
   struct Node:public HF::Devices::Node::Abstract <NodeUnit0>
   {};

   //! [Node custom code]

   // =============================================================================
   // Concentrator
   // =============================================================================
   //! [Concentrator custom code]

   /*
    * Custom Device Management service for the concentrator.
    */
   struct DeviceManagementServer:public HF::Core::DeviceManagement::DefaultServer
   {
      DeviceManagementServer(HF::Core::Unit0 &unit):
         HF::Core::DeviceManagement::DefaultServer (unit)
      {}

      void registered (HF::Core::DeviceManagement::DevicePtr &device)
      {
         LOG (INFO) << "Device " << device->uid << " registered !" << NL;
      }
   };

   /*
    * Custom Unit 0 for concentrator with the custom Device Management service.
    */
   struct BaseUnit0:public HF::Devices::Concentrator::Unit0 <HF::Core::DeviceInformation::Server,
                                                             DeviceManagementServer,
                                                             HF::Core::AttributeReporting::Server,
                                                             HF::Core::BindManagement::DefaultServer>
   {
      BaseUnit0(HF::IDevice &device):
         HF::Devices::Concentrator::Unit0 <HF::Core::DeviceInformation::Server,
                                           DeviceManagementServer,
                                           HF::Core::AttributeReporting::Server,
                                           HF::Core::BindManagement::DefaultServer>(device)
      {}
   };

   /*
    * Example concentrator.
    */
   struct Base:public HF::Devices::Concentrator::Abstract <BaseUnit0>
   {};

   //! [Concentrator custom code]

}  // namespace

// =============================================================================
// MAIN
// =============================================================================

int main (int argc, char **argv)
{
   UNUSED (argc);
   UNUSED (argv);

   LOG (INFO) << "Use case : Handling registration events" << NL;

   /*
    * Each node variable is a remote device, i.e.,
    * the Node variables are declared on the remote device
    * code and are not used on the base code.
    */
   LOG (INFO) << "Create the node instances ..." << NL;

   Node node1;
   Node node2;

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

   // Register two devices.

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

   return 0;
}
