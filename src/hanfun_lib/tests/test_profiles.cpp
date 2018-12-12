// =============================================================================
/*!
 * @file       tests/test_profiles.cpp
 *
 * This file contains the implementation of the tests for the profiles.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================

#include "hanfun/profiles.h"

#include "test_helper.h"

using namespace HF;
using namespace HF::Testing;

// =============================================================================
// Defines
// =============================================================================

/* *INDENT-OFF* */
#define HELPER_CLASS(_name)                           \
struct _name:public ProfileHelper<Profiles::_name>   \
{                                                      \
   virtual ~_name() {}                                \
}
/* *INDENT-ON* */

/* *INDENT-OFF* */
#define HELPER_CLASS2(_name)                            \
struct _name:public ProfileHelper<Profiles::_name<>>   \
{                                                        \
   virtual ~_name() {}                                  \
}
/* *INDENT-ON* */

// =============================================================================
// Helper Test Classes
// =============================================================================

namespace HF
{
   namespace Testing
   {
      HELPER_CLASS (SimpleOnOffSwitchable);
      HELPER_CLASS (SimpleOnOffSwitch);
      HELPER_CLASS (SimpleLevelControllable);
      HELPER_CLASS (SimpleLevelControl);
      HELPER_CLASS (AC_Outlet);
      HELPER_CLASS (SimpleLight);
      HELPER_CLASS (SimpleDoorLock);
      HELPER_CLASS (SimpleTemperatureSensor);
      HELPER_CLASS (SimpleHumiditySensor);

      HELPER_CLASS (DoorBell);
      HELPER_CLASS (SimplePowerMeter);

      HELPER_CLASS (SimpleDetector);
      HELPER_CLASS (DoorOpenCloseDetector);
      HELPER_CLASS (WindowOpenCloseDetector);
      HELPER_CLASS (MotionDetector);
      HELPER_CLASS (SmokeDetector);
      HELPER_CLASS (GasDetector);
      HELPER_CLASS (FloodDetector);
      HELPER_CLASS (GlassBreakDetector);
      HELPER_CLASS (VibrationDetector);
      HELPER_CLASS (Siren);
      HELPER_CLASS (Alertable);

      HELPER_CLASS (SimplePendant);

      HELPER_CLASS (UserInterface);

      HELPER_CLASS (GenericApplicationLogic);

      HELPER_CLASS2 (SimpleLevelControllableSwitchable);
      HELPER_CLASS2 (SimpleLevelControlSwitch);
      HELPER_CLASS2 (AC_OutletWithPowerMetering);
      HELPER_CLASS2 (DimmableLight);
      HELPER_CLASS2 (DimmerSwitch);

   }  // namespace Testing

}  // namespace HF

// =============================================================================
// Profiles UIDs Tests
// =============================================================================

TEST_GROUP (Profiles)
{
   struct TestProfile:public InterfaceHelper < Profiles::Profile2 < 0x5A5A, TestInterface, TestInterface >>
   {};

   TEST_SETUP ()
   {
      mock ().ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      mock ().clear ();
   }
};

TEST (Profiles, UIDs)
{
   Profiles::IProfile *profile = nullptr;

   // =============================================================================
   // Home Control Unit Types
   // =============================================================================

   profile = new SimpleOnOffSwitchable ();
   CHECK_EQUAL (Profiles::SIMPLE_ONOFF_SWITCHABLE, profile->uid ());
   delete profile;

   profile = new SimpleOnOffSwitch ();
   CHECK_EQUAL (Profiles::SIMPLE_ONOFF_SWITCH, profile->uid ());
   delete profile;

   profile = new SimpleLevelControllable ();
   CHECK_EQUAL (Profiles::SIMPLE_LEVEL_CONTROLLABLE, profile->uid ());
   delete profile;

   profile = new SimpleLevelControl ();
   CHECK_EQUAL (Profiles::SIMPLE_LEVEL_CONTROL, profile->uid ());
   delete profile;

   profile = new SimpleLevelControllableSwitchable ();
   CHECK_EQUAL (Profiles::SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE, profile->uid ());
   delete profile;

   profile = new SimpleLevelControlSwitch ();
   CHECK_EQUAL (Profiles::SIMPLE_LEVEL_CONTROL_SWITCH, profile->uid ());
   delete profile;

   profile = new AC_Outlet ();
   CHECK_EQUAL (Profiles::AC_OUTLET, profile->uid ());
   delete profile;

   profile = new AC_OutletWithPowerMetering ();
   CHECK_EQUAL (Profiles::AC_OUTLET_WITH_POWER_METERING, profile->uid ());
   delete profile;

   profile = new SimpleLight ();
   CHECK_EQUAL (Profiles::SIMPLE_LIGHT, profile->uid ());
   delete profile;

   profile = new DimmableLight ();
   CHECK_EQUAL (Profiles::DIMMABLE_LIGHT, profile->uid ());
   delete profile;

   profile = new DimmerSwitch ();
   CHECK_EQUAL (Profiles::DIMMER_SWITCH, profile->uid ());
   delete profile;

   profile = new SimpleDoorLock ();
   CHECK_EQUAL (Profiles::SIMPLE_DOOR_LOCK, profile->uid ());
   delete profile;

   profile = new DoorBell ();
   CHECK_EQUAL (Profiles::DOOR_BELL, profile->uid ());
   delete profile;

   profile = new Testing::SimplePowerMeter ();
   CHECK_EQUAL (Profiles::SIMPLE_POWER_METER, profile->uid ());
   delete profile;

   profile = new Testing::SimpleTemperatureSensor ();
   CHECK_EQUAL (Profiles::SIMPLE_TEMPERATURE_SENSOR, profile->uid ());
   delete profile;

   profile = new Testing::SimpleHumiditySensor ();
   CHECK_EQUAL (Profiles::SIMPLE_HUMIDITY_SENSOR, profile->uid ());
   delete profile;

   // =============================================================================
   // Security Unit Types
   // =============================================================================

   profile = new SimpleDetector ();
   CHECK_EQUAL (Profiles::SIMPLE_DETECTOR, profile->uid ());
   delete profile;

   profile = new DoorOpenCloseDetector ();
   CHECK_EQUAL (Profiles::DOOR_OPEN_CLOSE_DETECTOR, profile->uid ());
   delete profile;

   profile = new WindowOpenCloseDetector ();
   CHECK_EQUAL (Profiles::WINDOW_OPEN_CLOSE_DETECTOR, profile->uid ());
   delete profile;

   profile = new MotionDetector ();
   CHECK_EQUAL (Profiles::MOTION_DETECTOR, profile->uid ());
   delete profile;

   profile = new SmokeDetector ();
   CHECK_EQUAL (Profiles::SMOKE_DETECTOR, profile->uid ());
   delete profile;

   profile = new GasDetector ();
   CHECK_EQUAL (Profiles::GAS_DETECTOR, profile->uid ());
   delete profile;

   profile = new FloodDetector ();
   CHECK_EQUAL (Profiles::FLOOD_DETECTOR, profile->uid ());
   delete profile;

   profile = new GlassBreakDetector ();
   CHECK_EQUAL (Profiles::GLASS_BREAK_DETECTOR, profile->uid ());
   delete profile;

   profile = new VibrationDetector ();
   CHECK_EQUAL (Profiles::VIBRATION_DETECTOR, profile->uid ());
   delete profile;

   profile = new Siren ();
   CHECK_EQUAL (Profiles::SIREN, profile->uid ());
   delete profile;

   profile = new Alertable ();
   CHECK_EQUAL (Profiles::ALERTABLE, profile->uid ());
   delete profile;

   // =============================================================================
   // Home care Unit Types
   // =============================================================================

   profile = new SimplePendant ();
   CHECK_EQUAL (Profiles::SIMPLE_PENDANT, profile->uid ());
   delete profile;

   // =============================================================================
   // Application Unit Types
   // =============================================================================

   profile = new UserInterface ();
   CHECK_EQUAL (Profiles::USER_INTERFACE, profile->uid ());
   delete profile;

   profile = new GenericApplicationLogic ();
   CHECK_EQUAL (Profiles::GENERIC_APPLICATION, profile->uid ());
   delete profile;
}

TEST (Profiles, Detector)
{
   Protocol::Address addr;
   SimpleDetector    detector;

   addr.mod    = Protocol::Address::DEVICE;
   addr.device = 42;
   addr.unit   = 33;

   mock ("Interface").expectOneCall ("send");

   detector.alert (addr, true);

   mock ("Interface").checkExpectations ();

   CHECK_TRUE (detector.sendMsg.payload.size () != 0);

   Interfaces::Alert::Message status_msg;
   status_msg.unpack (detector.sendMsg.payload);

   CHECK_EQUAL (1, status_msg.state);
   CHECK_EQUAL (detector.uid (), status_msg.type);

   LONGS_EQUAL (Protocol::Address::DEVICE, detector.addr.mod);
   LONGS_EQUAL (42, detector.addr.device);
   LONGS_EQUAL (33, detector.addr.unit);
}

TEST (Profiles, Profile2_Handle)
{
   Common::ByteArray data;
   Protocol::Packet  packet;

   TestProfile profile;

   profile.first ()->_uid   = 0x5A51;
   profile.second ()->_uid  = 0x5A52;

   profile.first ()->_role  = Interface::SERVER_ROLE;
   profile.second ()->_role = Interface::CLIENT_ROLE;

   packet.message.type = Message::COMMAND_REQ;

   // Call first interface.

   packet.message.itf.role = profile.first ()->_role;
   packet.message.itf.id   = profile.first ()->_uid;

   mock ("Interface").expectOneCall ("handle_command").onObject (profile.first ());

   Common::Result result = profile.handle (packet, data, 0);
   CHECK_EQUAL (Common::Result::OK, result);

   mock ("Interface").checkExpectations ();

   // Call second interface.

   packet.message.itf.role = profile.second ()->_role;
   packet.message.itf.id   = profile.second ()->_uid;

   mock ("Interface").expectOneCall ("handle_command").onObject (profile.second ());

   result = profile.handle (packet, data, 0);
   CHECK_EQUAL (Common::Result::OK, result);

   mock ("Interface").checkExpectations ();
}

TEST (Profiles, InterfaceMapping)
{
   uint16_t count;
   const HF::Common::Interface *itf;

   // HF::Profiles::SIMPLE_ONOFF_SWITCHABLE
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_ONOFF_SWITCHABLE, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SIMPLE_ONOFF_SWITCH
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_ONOFF_SWITCH, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::CLIENT_ROLE, itf->role);

   // HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::LEVEL_CONTROL, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SIMPLE_LEVEL_CONTROL
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_LEVEL_CONTROL, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::LEVEL_CONTROL, itf->id);
   LONGS_EQUAL (HF::Interface::CLIENT_ROLE, itf->role);

   // HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (2, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   ++itf;

   LONGS_EQUAL (HF::Interface::LEVEL_CONTROL, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SIMPLE_LEVEL_CONTROL_SWITCH
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_LEVEL_CONTROL_SWITCH, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (2, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::CLIENT_ROLE, itf->role);

   ++itf;

   LONGS_EQUAL (HF::Interface::LEVEL_CONTROL, itf->id);
   LONGS_EQUAL (HF::Interface::CLIENT_ROLE, itf->role);

   // HF::Profiles::AC_OUTLET
   itf = Profiles::interfaces (HF::Profiles::AC_OUTLET, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::AC_OUTLET_WITH_POWER_METERING
   itf = Profiles::interfaces (HF::Profiles::AC_OUTLET_WITH_POWER_METERING, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (2, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   ++itf;

   LONGS_EQUAL (HF::Interface::SIMPLE_POWER_METER, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SIMPLE_LIGHT
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_LIGHT, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::DIMMABLE_LIGHT
   itf = Profiles::interfaces (HF::Profiles::DIMMABLE_LIGHT, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (2, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   ++itf;

   LONGS_EQUAL (HF::Interface::LEVEL_CONTROL, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::DIMMER_SWITCH
   itf = Profiles::interfaces (HF::Profiles::DIMMER_SWITCH, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (2, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::CLIENT_ROLE, itf->role);

   ++itf;

   LONGS_EQUAL (HF::Interface::LEVEL_CONTROL, itf->id);
   LONGS_EQUAL (HF::Interface::CLIENT_ROLE, itf->role);

   // HF::Profiles::SIMPLE_DOOR_LOCK
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_DOOR_LOCK, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::DOOR_BELL
   itf = Profiles::interfaces (HF::Profiles::DOOR_BELL, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SIMPLE_POWER_METER
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_POWER_METER, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::SIMPLE_POWER_METER, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SIMPLE_TEMPERATURE_SENSOR
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_TEMPERATURE_SENSOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::SIMPLE_TEMPERATURE, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SIMPLE_HUMIDITY_SENSOR
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_HUMIDITY_SENSOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::SIMPLE_HUMIDITY, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SIMPLE_DETECTOR
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_DETECTOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::DOOR_OPEN_CLOSE_DETECTOR
   itf = Profiles::interfaces (HF::Profiles::DOOR_OPEN_CLOSE_DETECTOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::WINDOW_OPEN_CLOSE_DETECTOR
   itf = Profiles::interfaces (HF::Profiles::WINDOW_OPEN_CLOSE_DETECTOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::MOTION_DETECTOR
   itf = Profiles::interfaces (HF::Profiles::MOTION_DETECTOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SMOKE_DETECTOR
   itf = Profiles::interfaces (HF::Profiles::SMOKE_DETECTOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::GAS_DETECTOR
   itf = Profiles::interfaces (HF::Profiles::GAS_DETECTOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::FLOOD_DETECTOR
   itf = Profiles::interfaces (HF::Profiles::FLOOD_DETECTOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::GLASS_BREAK_DETECTOR
   itf = Profiles::interfaces (HF::Profiles::GLASS_BREAK_DETECTOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::VIBRATION_DETECTOR
   itf = Profiles::interfaces (HF::Profiles::VIBRATION_DETECTOR, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::SIREN
   itf = Profiles::interfaces (HF::Profiles::SIREN, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ON_OFF, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::ALERTABLE
   itf = Profiles::interfaces (HF::Profiles::ALERTABLE, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::CLIENT_ROLE, itf->role);

   // HF::Profiles::SIMPLE_PENDANT
   itf = Profiles::interfaces (HF::Profiles::SIMPLE_PENDANT, count);
   CHECK_FALSE (itf == nullptr);
   LONGS_EQUAL (1, count);

   LONGS_EQUAL (HF::Interface::ALERT, itf->id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, itf->role);

   // HF::Profiles::USER_INTERFACE
   itf = Profiles::interfaces (HF::Profiles::USER_INTERFACE, count);
   CHECK_TRUE (itf == nullptr);
   LONGS_EQUAL (0, count);

   // HF::Profiles::GENERIC_APPLICATION
   itf = Profiles::interfaces (HF::Profiles::GENERIC_APPLICATION, count);
   CHECK_TRUE (itf == nullptr);
   LONGS_EQUAL (0, count);
}
