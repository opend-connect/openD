// =============================================================================
/*!
 * @file       tests/interfaces/test_level_control.cpp
 *
 * This is file contains the unit tests for the Level Control Interface implementation.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================

#include "hanfun/interfaces/level_control.h"

#include "test_helper.h"

using namespace HF;
using namespace HF::Common;
using namespace HF::Interfaces;

using namespace HF::Testing;

// =============================================================================
// LevelControl
// =============================================================================

TEST_GROUP (LevelControl)
{
   class TestLevelControl:public InterfaceParentHelper <LevelControl::Base>
   {};

   TestLevelControl interface;
};

TEST (LevelControl, UID)
{
   CHECK_EQUAL (HF::Interface::LEVEL_CONTROL, interface.uid ());
}

// =============================================================================
// LevelControlClient
// =============================================================================

//! Test Group for LevelControlClient interface class.
TEST_GROUP (LevelControlClient)
{
   class TestLevelControlClient:public InterfaceHelper <LevelControl::Client>
   {};

   TestLevelControlClient client;
   Protocol::Address addr;

   TEST_SETUP ()
   {
      mock ().ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      mock ().clear ();
   }
};

//! @test Should send an LevelControl::SET_LEVEL_CMD message.
TEST (LevelControlClient, Level)
{
   mock ("Interface").expectOneCall ("send");

   client.level (addr, (uint8_t) 0x42);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (LevelControl::SET_LEVEL_CMD, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, client.sendMsg.type);

   LevelControl::Level level;

   level.unpack (client.sendMsg.payload);

   BYTES_EQUAL (0x42, level.get ());
}

// =============================================================================
// LevelControlServer Tests
// =============================================================================;

TEST_GROUP (LevelControlServer)
{
   class TestLevelControlServer:public InterfaceHelper <LevelControl::Server>
   {
      public:

      void level_change (HF::Protocol::Address &source, uint8_t old_level, uint8_t new_level)
      {
         mock ("LevelControlServer").actualCall ("level_change");
         LevelControl::Server::level_change (source, old_level, new_level);
      }
   };

   TestLevelControlServer server;

   Protocol::Packet packet;
   ByteArray expected;

   TEST_SETUP ()
   {
      mock ("LevelControlServer").ignoreOtherCalls ();
      mock ("Interface").ignoreOtherCalls ();

      expected = ByteArray {0x00, 0x00, 0x00,
                            0xAA,  // Level value.
                            0x00, 0x00, 0x00};

      packet.message.itf.role   = HF::Interface::SERVER_ROLE;
      packet.message.itf.id     = server.uid ();
      packet.message.itf.member = LevelControl::LEVEL_ATTR;

      packet.message.type       = Protocol::Message::SET_ATTR_REQ;

      packet.message.length     = expected.size ();
   }

   TEST_TEARDOWN ()
   {
      mock ().clear ();
   }
};

TEST (LevelControlServer, Level)
{
   CHECK_EQUAL (0, server.level ());
   mock ("Interface").expectOneCall ("notify");
   server.level ((uint8_t) 42);
   mock ("Interface").checkExpectations ();
   CHECK_EQUAL (42, server.level ());
}

//! @test Should handle valid message.
TEST (LevelControlServer, Handle_Valid_Message)
{
   mock ("LevelControlServer").expectOneCall ("level_change");

   Result result = server.handle (packet, expected, 3);
   CHECK_EQUAL (Result::OK, result);

   LONGS_EQUAL (0xAA, server.level ());

   mock ("LevelControlServer").checkExpectations ();
}

//! @test Should not handle message from invalid role.
TEST (LevelControlServer, Handle_Invalid_Role)
{
   packet.message.itf.role = HF::Interface::CLIENT_ROLE;

   CHECK_EQUAL (Result::FAIL_SUPPORT, server.handle (packet, expected, 3));
}

//! @test Should not handle message from invalid interface UID.
TEST (LevelControlServer, Handle_Invalid_UID)
{
   packet.message.itf.id = server.uid () + 1;

   CHECK_EQUAL (Result::FAIL_ARG, server.handle (packet, expected, 3));
}

//! @test Should not handle message with invalid payload size.
TEST (LevelControlServer, Handle_Invalid_Payload_Size)
{
   LevelControl::Level level_attr;
   packet.message.length = level_attr.size () - 1;

   CHECK_EQUAL (Result::FAIL_ARG, server.handle (packet, expected, 3));
}

//! @test Should not handle message with not enough payload / offset.
TEST (LevelControlServer, Handle_Invalid_Payload)
{
   CHECK_EQUAL (Result::FAIL_ARG, server.handle (packet, expected, 10));
}

//! @test Should return attribute.
TEST (LevelControlServer, Attribute)
{
   HF::Attributes::IAttribute *attr = server.attribute (LevelControl::__LAST_ATTR__ + 1);

   CHECK_TRUE (attr == nullptr);

   attr = server.attribute (LevelControl::LEVEL_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (LevelControl::LEVEL_ATTR, attr->uid ());
   CHECK_TRUE (attr->isWritable ());

   LONGS_EQUAL (server.uid (), attr->interface ());

   delete attr;
}
