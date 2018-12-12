// =============================================================================
/*!
 * @file       apps/example_08.cpp
 *
 * This file contains an example demonstrating the catch all bind management
 * functionality.
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
   // Alarms
   // =============================================================================

   /*
    * Unit implementing the Simple %Detector profile.
    */
   struct SimpleDetector:public HF::Units::Unit <HF::Profiles::SimpleDetector>
   {
      SimpleDetector(uint8_t id, HF::IDevice &device):
         HF::Units::Unit <HF::Profiles::SimpleDetector>(id, device)
      {}
   };

   /*
    * Example alarm node.
    */
   struct Alarm:public HF::Devices::Node::Node
   {
      // Simple detector unit.
      SimpleDetector detector;

      Alarm():detector (1, *this)  // Place unit at id 1.
      {}
   };

   // =============================================================================
   // Light
   // =============================================================================

   /*
    * Unit implementing the Simple OnOff Switchable profile.
    */
   struct SimpleLight:public HF::Units::Unit <HF::Profiles::SimpleLight>
   {
      typedef HF::Units::Unit <HF::Profiles::SimpleLight> _Parent;

      SimpleLight(uint8_t id, HF::IDevice &device):_Parent (id, device)
      {}

      void on (HF::Protocol::Address &source)
      {
         _Parent::on (source);
         LOG (INFO) << device ().address () << " : Command ON received ..." << NL;
      }

      void off (HF::Protocol::Address &source)
      {
         _Parent::off (source);
         LOG (INFO) << device ().address () << " : Command OFF received ..." << NL;
      }

      void toggle (HF::Protocol::Address &source)
      {
         _Parent::toggle (source);
         LOG (INFO) << device ().address () << " : Command TOGGLE received ..." << NL;
      }
   };

   /*
    * Example light node.
    */
   struct Light:public HF::Devices::Node::Node
   {
      // Simple detector unit.
      SimpleLight simple_light;

      Light():simple_light (1, *this)  // Place unit at id 1.
      {}
   };

   // =============================================================================
   // Base
   // =============================================================================

   /*
    * Custom alert receiver.
    */
   struct AlertSink:public HF::Interfaces::Alert::Client
   {
      void status (HF::Protocol::Address &source, HF::Interfaces::Alert::Message &message)
      {
         LOG (INFO) << "Alert received from " << source.device << "/" << (int) source.unit << " : "
                    << message.state << NL;

         auto _unit                 = static_cast <HF::Units::Unit <HF::Profiles::SimpleOnOffSwitch, AlertSink> *>(&unit ());

         HF::Protocol::Address addr = source;
         addr.device += 3;
         _unit->toggle (addr);
      }

      virtual HF::Units::IUnit &unit () const = 0;
   };

   /*
    * Unit implementing the Simple On-Off Switch profile and %Alert client interface.
    */
   struct Alarm2Switch:public HF::Units::Unit <HF::Profiles::SimpleOnOffSwitch, AlertSink>
   {
      Alarm2Switch(uint8_t id, HF::IDevice &device):
         HF::Units::Unit <HF::Profiles::SimpleOnOffSwitch, AlertSink>(id, device)
      {}
   };

   /*
    * Example concentrator.
    */
   struct Base:public HF::Devices::Concentrator::Concentrator
   {
      Alarm2Switch alarm2switch;

      Base():alarm2switch (1, *this)
      {}
   };

}  // namespace

// =============================================================================
// MAIN
// =============================================================================

int main (int argc, char **argv)
{
   UNUSED (argc);
   UNUSED (argv);

   LOG (INFO) << "Use case : Catch all binding rules." << NL;

   /*
    * Each node variable is a remote device, i.e.,
    * the Node variables are declared on the remote device
    * code and are not used on the base code.
    */
   LOG (INFO) << "Create the node instances ..." << NL;

   Alarm alarm_1;
   Alarm alarm_2;
   Alarm alarm_3;

   Light light_4;
   Light light_5;
   Light light_6;

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

   loop.add_node (&alarm_1, "alarm_1");
   loop.add_node (&alarm_2, "alarm_2");
   loop.add_node (&alarm_3, "alarm_3");

   loop.add_node (&light_4, "light_4");
   loop.add_node (&light_5, "light_5");
   loop.add_node (&light_6, "light_6");

   // Register devices.

   LOG (INFO) << "Registering alarm_1 ... " << NL;
   alarm_1.unit0 ()->device_management ()->register_device ();
   LOG (INFO) << "Alarm1 address ... " << alarm_1.address () << NL;
   assert (alarm_1.address () == 1);

   LOG (INFO) << "Registering alarm_2 ... " << NL;
   alarm_2.unit0 ()->device_management ()->register_device ();
   LOG (INFO) << "Alarm2 address ... " << alarm_2.address () << NL;
   assert (alarm_2.address () == 2);

   LOG (INFO) << "Registering alarm_3 ... " << NL;
   alarm_3.unit0 ()->device_management ()->register_device ();
   LOG (INFO) << "Alarm3 address ... " << alarm_3.address () << NL;
   assert (alarm_3.address () == 3);

   LOG (INFO) << "Registering light_4 ... " << NL;
   light_4.unit0 ()->device_management ()->register_device ();
   LOG (INFO) << "Node4 address ... " << light_4.address () << NL;
   assert (light_4.address () == 4);

   LOG (INFO) << "Registering light_5 ... " << NL;
   light_5.unit0 ()->device_management ()->register_device ();
   LOG (INFO) << "Node5 address ... " << light_5.address () << NL;
   assert (light_5.address () == 5);

   LOG (INFO) << "Registering light_6 ... " << NL;
   light_6.unit0 ()->device_management ()->register_device ();
   LOG (INFO) << "Node6 address ... " << light_6.address () << NL;
   assert (light_6.address () == 6);

   LOG (INFO) << "There should be 6 registered devices ... "
              << base.unit0 ()->device_management ()->entries ().size () << NL;
   assert (base.unit0 ()->device_management ()->entries ().size () == 6);

   LOG (INFO) << "=== Setup catch all binding for alert interface ===" << NL;
   LOG (INFO) << "Alert commands will be sent to unit 1 on the base." << NL;

   HF::Protocol::Address source;
   HF::Protocol::Address destination (0, 1);
   HF::Common::Interface itf (HF::Interface::ALERT, HF::Interface::CLIENT_ROLE);

   base.unit0 ()->bind_management ()->add (source, destination, itf);
   LOG (INFO) << "There should be one bind entry ... "
              << base.unit0 ()->bind_management ()->entries ().size () << NL;
   assert (base.unit0 ()->bind_management ()->entries ().size () == 1);

   LOG (INFO) << "=== Sending alarms should toggle the corresponding lights ===" << NL;
   LOG (INFO) << "1 -> 4 | 2 -> 5 | 3 -> 6" << NL;

   LOG (INFO) << "Alarm 1 ON ..." << NL;
   alarm_1.detector.alert (true);

   LOG (INFO) << "Alarm 2 ON ..." << NL;
   alarm_2.detector.alert (true);

   LOG (INFO) << "Alarm 3 ON ..." << NL;
   alarm_3.detector.alert (true);

   LOG (INFO) << "Alarm 2 OFF ..." << NL;
   alarm_2.detector.alert (false);

   LOG (INFO) << "Alarm 3 OFF ..." << NL;
   alarm_3.detector.alert (false);

   LOG (INFO) << "Alarm 1 OFF ..." << NL;
   alarm_1.detector.alert (false);

   return 0;
}
