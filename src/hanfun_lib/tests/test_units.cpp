// =============================================================================
/*!
 * @file       tests/test_units.cpp
 *
 * This file contains the implementation of the tests for the unit implementation.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================

#include "hanfun/units.h"

#include "test_helper.h"

using namespace HF;
using namespace HF::Common;
using namespace HF::Testing;

// =============================================================================
// Defines
// =============================================================================

// =============================================================================
// Helper Classes
// =============================================================================

namespace
{
   struct OnOff:public HF::Interfaces::OnOff::Client
   {};

   struct LevelControl:public HF::Interfaces::LevelControl::Server
   {
      public:

      void level_change (HF::Protocol::Address &source, uint8_t old_level, uint8_t new_level)
      {
         mock ("LevelControl").actualCall ("level_change");
         HF::Interfaces::LevelControl::Server::level_change (source, old_level, new_level);
      }
   };

   struct TestUnit:public HF::Units::Unit <HF::Profiles::GenericApplicationLogic, OnOff, LevelControl>
   {
      TestUnit(uint8_t id, HF::IDevice &device):
         HF::Units::Unit <HF::Profiles::GenericApplicationLogic, OnOff, LevelControl>(id, device)
      {}

      OnOff *on_off () const
      {
         return const_cast <OnOff *>(get <0>());
      }

      LevelControl *level_control () const
      {
         return const_cast <LevelControl *>(get <1>());
      }
   };

}  // namespace


// =============================================================================
// Tests
// =============================================================================

TEST_GROUP (Unit)
{
   Testing::Device *device;
   TestUnit *unit;

   TEST_SETUP ()
   {
      device = new Testing::Device ();
      unit   = new TestUnit (1, *device);

      mock ().ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      delete unit;
      delete device;

      mock ().clear ();
   }
};

TEST (Unit, Role)
{
   LONGS_EQUAL (HF::Interface::CLIENT_ROLE, unit->on_off ()->role ());
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, unit->level_control ()->role ());
}

TEST (Unit, Interfaces)
{
   auto itfs = unit->interfaces ();

   LONGS_EQUAL (2, itfs.size ());

   LONGS_EQUAL (unit->on_off ()->uid (), itfs[0].id);
   LONGS_EQUAL (unit->on_off ()->role (), itfs[0].role);

   LONGS_EQUAL (unit->level_control ()->uid (), itfs[1].id);
   LONGS_EQUAL (unit->level_control ()->role (), itfs[1].role);
}

TEST (Unit, Handle_OnOff)
{
   mock ("AbstractDevice").expectNCalls (3, "send");

   unit->on_off ()->on ();
   unit->on_off ()->off ();
   unit->on_off ()->toggle ();

   mock ("AbstractDevice").checkExpectations ();
}

TEST (Unit, Handle_LevelControl)
{
   ByteArray payload = {0x00, 0x00, 0x00,
                        0x55, // Level value.
                        0x00, 0x00, 0x00};

   Protocol::Packet packet;

   packet.message.type       = Protocol::Message::SET_ATTR_REQ;

   packet.message.itf.role   = HF::Interface::SERVER_ROLE;
   packet.message.itf.id     = HF::Interface::LEVEL_CONTROL;
   packet.message.itf.member = HF::Interfaces::LevelControl::LEVEL_ATTR;
   packet.message.length     = payload.size ();

   mock ("LevelControl").expectOneCall ("level_change");

   Result result = unit->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   LONGS_EQUAL (0x55, unit->level_control ()->level ());

   mock ("LevelControl").checkExpectations ();
}

TEST (Unit, CreateDestroy)
{
   Testing::Device device;
   LONGS_EQUAL (1, device.units ().size ());

   TestUnit *unit = new TestUnit (1, device);
   LONGS_EQUAL (2, device.units ().size ());

   delete unit;

   LONGS_EQUAL (1, device.units ().size ());
}
