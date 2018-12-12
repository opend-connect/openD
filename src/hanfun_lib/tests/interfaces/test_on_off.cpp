// =============================================================================
/*!
 * @file       tests/interfaces/test_on_off.cpp
 *
 * This is file contains the unit tests for the On-Off Interface implementation.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================

#include "hanfun/interfaces/on_off.h"

#include "test_helper.h"

using namespace HF;
using namespace HF::Interfaces;

using namespace HF::Testing;

// =============================================================================
// OnOff
// =============================================================================

//! Test Group for OnOff interface parent class.
TEST_GROUP (OnOff)
{
   class TestOnOff:public InterfaceParentHelper <OnOff::Base>
   {};

   TestOnOff interface;
};

//! @test OnOff::uid should return @c Interface::ON_OFF.
TEST (OnOff, UID)
{
   CHECK_EQUAL (Interface::ON_OFF, interface.uid ());
}

// =============================================================================
// OnOffClient
// =============================================================================

//! Test Group for OnOffClient interface class.
TEST_GROUP (OnOffClient)
{
   class TestOnOffClient:public InterfaceHelper <OnOff::Client>
   {};

   TestOnOffClient client;
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

//! @test Should send an ON_CMD message.
TEST (OnOffClient, On)
{
   mock ("Interface").expectOneCall ("send");

   client.on (addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (OnOff::ON_CMD, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, client.sendMsg.type);
}

//! @test Should send an OFF_CMD message.
TEST (OnOffClient, Off)
{
   mock ("Interface").expectOneCall ("send");

   client.off (addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (OnOff::OFF_CMD, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, client.sendMsg.type);
}

//! @test Should send an TOGGLE_CMD message.
TEST (OnOffClient, Toggle)
{
   mock ("Interface").expectOneCall ("send");

   client.toggle (addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (OnOff::TOGGLE_CMD, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, client.sendMsg.type);
}

// =============================================================================
// OnOffServer
// =============================================================================

//! Test Group for OnOffServer interface class.
TEST_GROUP (OnOffServer)
{
   class DefaultTestOnOffServer:public InterfaceHelper <OnOff::Server>
   {};

   class TestOnOffServer:public InterfaceHelper <OnOff::Server>
   {
      void on (HF::Protocol::Address &source)
      {
         UNUSED (source);
         mock ("OnOffServer").actualCall ("on");
         InterfaceHelper <OnOff::Server>::on (source);
      }

      void off (HF::Protocol::Address &source)
      {
         UNUSED (source);
         mock ("OnOffServer").actualCall ("off");
         InterfaceHelper <OnOff::Server>::off (source);
      }

      void toggle (HF::Protocol::Address &source)
      {
         UNUSED (source);
         mock ("OnOffServer").actualCall ("toggle");
         InterfaceHelper <OnOff::Server>::toggle (source);
      }
   };

   TestOnOffServer   server;
   Protocol::Packet  packet;
   Common::ByteArray expected;

   TEST_SETUP ()
   {
      packet.message.itf.role   = Interface::SERVER_ROLE;
      packet.message.itf.id     = server.uid ();
      packet.message.itf.member = 0xFF;

      mock ("OnOffServer").ignoreOtherCalls ();
      mock ("Interface").ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      mock ().clear ();
   }
};

TEST (OnOffServer, State)
{
   mock ("Interface").expectNCalls (2, "notify");

   CHECK_FALSE (server.state ());

   server.state (true);
   CHECK_TRUE (server.state ());

   server.state (false);
   CHECK_FALSE (server.state ());

   mock ("Interface").checkExpectations ();
}

TEST (OnOffServer, DefaultCallbacks)
{
   DefaultTestOnOffServer server;

   CHECK_FALSE (server.state ());

   HF::Protocol::Address source;

   server.on (source);
   CHECK_TRUE (server.state ());

   server.off (source);
   CHECK_FALSE (server.state ());

   server.toggle (source);
   CHECK_TRUE (server.state ());

   server.toggle (source);
   CHECK_FALSE (server.state ());
}

//! @test Should handle valid @c OnOff::ON_CMD message.
TEST (OnOffServer, Handle_Valid_On_Message)
{
   mock ("OnOffServer").expectOneCall ("on");

   packet.message.itf.member = OnOff::ON_CMD;

   Common::Result result = server.handle (packet, expected, 3);
   CHECK_EQUAL (Common::Result::OK, result);

   mock ("OnOffServer").checkExpectations ();
}

//! @test Should handle valid @c OnOff::OFF_CMD message.
TEST (OnOffServer, Handle_Valid_Off_Message)
{
   mock ("OnOffServer").expectOneCall ("off");

   packet.message.itf.member = OnOff::OFF_CMD;

   Common::Result result = server.handle (packet, expected, 3);
   CHECK_EQUAL (Common::Result::OK, result);

   mock ("OnOffServer").checkExpectations ();
}

//! @test Should handle valid @c OnOff::TOGGLE_CMD message.
TEST (OnOffServer, Handle_Valid_Toggle_Message)
{
   mock ("OnOffServer").expectOneCall ("toggle");

   packet.message.itf.member = OnOff::TOGGLE_CMD;

   Common::Result result = server.handle (packet, expected, 3);
   CHECK_EQUAL (Common::Result::OK, result);

   mock ("OnOffServer").checkExpectations ();
}

//! @test Should not handle message from invalid role.
TEST (OnOffServer, Handle_Invalid_Role)
{
   packet.message.itf.role = Interface::SERVER_ROLE;

   CHECK_EQUAL (Common::Result::FAIL_SUPPORT, server.handle (packet, expected, 3));
}

//! @test Should not handle message from invalid interface UID.
TEST (OnOffServer, Handle_Invalid_UID)
{
   packet.message.itf.id = server.uid () + 1;

   CHECK_EQUAL (Common::Result::FAIL_ARG, server.handle (packet, expected, 3));
}

//! @test Should return attribute.
TEST (OnOffServer, Attribute)
{
   HF::Attributes::IAttribute *attr = server.attribute (OnOff::__LAST_ATTR__ + 1);

   CHECK_TRUE (attr == nullptr);

   attr = server.attribute (OnOff::STATE_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (OnOff::STATE_ATTR, attr->uid ());
   CHECK_FALSE (attr->isWritable ());

   LONGS_EQUAL (server.uid (), attr->interface ());

   delete attr;
}
