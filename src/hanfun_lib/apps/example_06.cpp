// =============================================================================
/*!
 * @file       apps/example_06.cpp
 *
 * This file contains an example demonstrating how to read a custom attribute from
 * the device information service.
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

   /*
    * Custom device information service.
    */
   struct DeviceInformation:public HF::Core::DeviceInformation::Server
   {
      std::string serial;

      DeviceInformation(HF::Core::Unit0 &unit):
         Server (unit), serial ("0123456789")
      {}

      HF::Attributes::IAttribute *attribute (uint8_t uid)
      {
         if (uid == HF::Core::DeviceInformation::SERIAL_NUMBER_ATTR)
         {
            LOG (INFO) << "On device " << unit ().device ().address ()
                       << " serial number attribute read." << NL;

            return new HF::Attributes::Attribute <std::string>(this->uid (),
                                                               HF::Core::DeviceInformation::SERIAL_NUMBER_ATTR,
                                                               this, serial, true);
         }
         else
         {
            return HF::Core::DeviceInformation::Server::attribute (uid);
         }
      }
   };

   /*
    * Custom Unit 0 for node devices.
    */
   struct NodeUnit0:public HF::Devices::Node::Unit0 <DeviceInformation, HF::Core::DeviceManagement::Client,
                                                     HF::Core::AttributeReporting::Server>
   {
      NodeUnit0(HF::IDevice &device):
         HF::Devices::Node::Unit0 <DeviceInformation, HF::Core::DeviceManagement::Client,
                                   HF::Core::AttributeReporting::Server>(device)
      {}
   };

   /*!
    * Example node.
    */
   struct Node:public HF::Devices::Node::Abstract <NodeUnit0>
   {};

   // =============================================================================
   // Base
   // =============================================================================

   struct BaseUnit0:public HF::Devices::Concentrator::DefaultUnit0
   {
      BaseUnit0(HF::IDevice &device):
         HF::Devices::Concentrator::DefaultUnit0 (device)
      {}

      HF::Common::Result handle (HF::Protocol::Packet &packet, HF::Common::ByteArray &payload, uint16_t offset)
      {
         auto res = HF::Devices::Concentrator::DefaultUnit0::handle (packet, payload, offset);

         if (packet.message.type == HF::Protocol::Message::GET_ATTR_RES)
         {
            if (packet.message.itf.id == HF::Interface::DEVICE_INFORMATION)
            {
               if (packet.message.itf.member == HF::Core::DeviceInformation::SERIAL_NUMBER_ATTR)
               {
                  auto attr = new HF::Attributes::Attribute <std::string>(HF::Interface::DEVICE_INFORMATION,
                                                                          HF::Core::DeviceInformation::SERIAL_NUMBER_ATTR,
                                                                          nullptr);

                  HF::Attributes::Response resp (attr);
                  resp.unpack (payload, offset);

                  LOG (INFO) << "Got serial number " << attr->get () << " from " << packet.source.device << NL;
               }
            }
         }

         return res;
      }
   };

   /*!
    * Example concentrator.
    */
   struct Base:public HF::Devices::Concentrator::Abstract <BaseUnit0>
   {};

}  // namespace

// =============================================================================
// MAIN
// =============================================================================

int main (int argc, char **argv)
{
   UNUSED (argc);
   UNUSED (argv);

   LOG (INFO) << "Use case : Device Information service." << NL;

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

   // =============================================================================
   // Device Information
   // =============================================================================

   auto message = HF::Core::DeviceInformation::get (HF::Core::DeviceInformation::SERIAL_NUMBER_ATTR);

   LOG (INFO) << "Read serial number attribute from node1 ... " << NL;
   node1.unit0 ()->device_info ()->serial = "111";
   HF::Protocol::Address addr (1, 0);
   base.unit0 ()->send (addr, *message, nullptr);

   LOG (INFO) << "Read serial number attribute from node2 ... " << NL;

   node2.unit0 ()->device_info ()->serial = "222";
   addr.device = 2;
   base.unit0 ()->send (addr, *message, nullptr);

   delete message;

   return 0;
}
