// =============================================================================
/*!
 * @file       tests/interface/test_alert.cpp
 *
 * This is file contains the unit tests for the Alert Interface implementation.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================
#include <string>

#include "hanfun/interfaces/alert.h"

#include "test_helper.h"

using namespace HF;
using namespace HF::Common;
using namespace HF::Interfaces;

// =============================================================================
// Alert
// =============================================================================

//! Test Group for Alert interface parent class.
TEST_GROUP (Alert)
{
   class TestAlert:public Testing::InterfaceParentHelper <Alert::Base>
   {};

   TestAlert interface;
};

//! @test Alert::uid should return @c HF::Interface::ALERT.
TEST (Alert, UID)
{
   CHECK_EQUAL (HF::Interface::ALERT, interface.uid ());
}

// =============================================================================
// Alert / Messages
// =============================================================================

//! Alert::Message test group.
TEST_GROUP (AlertMessage)
{
   Alert::Message *message;

   ByteArray expected;

   TEST_SETUP ()
   {
      message  = new Alert::Message ();

      expected = ByteArray {0x00, 0x00, 0x00,
                            0x5A, 0xA5,              // Unit Type.
                            0xFF, 0xA5, 0x5A, 0xBB,  // State.
                            0x00, 0x00, 0x00};
   }

   TEST_TEARDOWN ()
   {
      delete message;
   }

};

//! @test Alert::Message::size should return the correct value.
TEST (AlertMessage, Size)
{
   LONGS_EQUAL (6, message->size ());

   LONGS_EQUAL (0, message->type);
   LONGS_EQUAL (0, message->state);
}

//! @test Alert::Message::pack should write the correct values to the ByteArray.
TEST (AlertMessage, Pack)
{
   message->type  = 0x5AA5;
   message->state = 0xFFA55ABB;

   ByteArray array (message->size () + 6);

   uint16_t  wsize = message->pack (array, 3);

   LONGS_EQUAL (message->size (), wsize);

   CHECK_EQUAL (expected, array);
}

//! @test Alert::Message::unpack should read the correct values from the ByteArray.
TEST (AlertMessage, Unpack)
{
   uint16_t rsize = message->unpack (expected, 3);

   LONGS_EQUAL (message->size (), rsize);

   LONGS_EQUAL (0x5AA5, message->type);
   LONGS_EQUAL (0xFFA55ABB, message->state);
}

// =============================================================================
// AlertServer
// =============================================================================

//! Test Group for AlertServer interface class.
TEST_GROUP (AlertServer)
{
   struct TestAlertServer:public Testing::InterfaceHelper <Alert::Server>
   {
      using Alert::Server::create_status;
   };

   TestAlertServer *server;

   TEST_SETUP ()
   {
      server = new TestAlertServer ();
      mock ("Interface").ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      delete server;
      mock ().clear ();
   }
};

#define CHECK_ALARM(_expected, _state, _index) \
   check_index <bool>(_expected, _state, _index, "Alarm", __FILE__, __LINE__)

//! @test Should disable all alarms.
TEST (AlertServer, DisableAll)
{
   mock ("Interface").expectOneCall ("notify");
   CHECK_EQUAL (UINT32_MAX, server->enabled ());
   server->disableAll ();
   CHECK_EQUAL (0, server->enabled ());
   mock ("Interface").checkExpectations ();
}

//! @test Should enable all alarms.
TEST (AlertServer, EnableAll)
{
   mock ("Interface").expectNCalls (2, "notify");
   server->disableAll ();
   server->enableAll ();
   CHECK_EQUAL (UINT32_MAX, server->enabled ());
   mock ("Interface").checkExpectations ();
}

//! @test Should enable only the selected alarm.
TEST (AlertServer, Enable)
{
   mock ("Interface").expectOneCall ("notify");
   server->disableAll ();

   CHECK_FALSE (server->enabled (42));

   mock ("Interface").expectNCalls (2 * 32, "notify");

   for (int i = 0; i < 32; i++)
   {
      server->enable (i);

      CHECK_ALARM (true, server->enabled (i), i);
      CHECK_ALARM (false, server->disabled (i), i);

      for (int j = 0; j < 32; j++)
      {
         if (j != i)
         {
            CHECK_ALARM (false, server->enabled (j), j);
            CHECK_ALARM (true, server->disabled (j), j);
         }
      }

      server->disable (i);
   }

   mock ("Interface").checkExpectations ();
}

//! @test Should disable only the selected alarm.
TEST (AlertServer, Disable)
{
   mock ("Interface").expectOneCall ("notify");
   server->enableAll ();

   CHECK_TRUE (server->disabled (42));

   mock ("Interface").expectNCalls (2 * 32, "notify");

   for (int i = 0; i < 32; i++)
   {
      server->disable (i);

      CHECK_ALARM (false, server->enabled (i), i);
      CHECK_ALARM (true, server->disabled (i), i);

      for (int j = 0; j < 32; j++)
      {
         if (j != i)
         {
            CHECK_ALARM (true, server->enabled (j), j);
            CHECK_ALARM (false, server->disabled (j), j);
         }
      }

      server->enable (i);
   }

   mock ("Interface").checkExpectations ();
}

//! @test Should change the alarm state correctly.
TEST (AlertServer, State)
{
   CHECK_FALSE (server->state (42, true));

   CHECK_FALSE (server->state (42));

   CHECK_EQUAL (0, server->state ());

   mock ("Interface").expectNCalls (2 * 32, "notify");

   // Check individual assignment.
   for (int i = 0; i < 32; i++)
   {
      CHECK_ALARM (true, server->state (i, true), i);
      CHECK_ALARM (true, server->state (i), i);

      for (int j = 0; j < 32; j++)
      {
         if (i != j)
         {
            CHECK_ALARM (false, server->state (j), j);
         }
      }

      CHECK_TRUE (server->state (i, false));
      CHECK_FALSE (server->state (i));
   }

   mock ("Interface").expectNCalls (32, "notify");

   // Check clear.
   for (int i = 0; i < 32; i++)
   {
      server->state (i, true);
   }

   CHECK_EQUAL (UINT32_MAX, server->state ());

   mock ("Interface").expectOneCall ("notify");
   server->clear ();

   CHECK_EQUAL (0, server->state ());

   mock ("Interface").checkExpectations ();
}

//! @test Should create the correct Alert::Message.
TEST (AlertServer, Status)
{
   server->disableAll ();
   server->enable (3);
   server->clear ();

   server->state (3, true);

   Alert::Message *msg = server->create_status (5);

   CHECK_FALSE (msg == nullptr);

   CHECK_EQUAL (8, msg->state);
   CHECK_EQUAL (5, msg->type);

   delete msg;
}

//! @test Should send the a Alert::Message.
TEST (AlertServer, Status2)
{
   server->disableAll ();
   server->enable (3);
   server->clear ();
   server->state (3, true);

   Protocol::Address addr;

   mock ("Interface").expectOneCall ("send");

   server->status (addr, 5);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (HF::Interface::CLIENT_ROLE, server->sendMsg.itf.role);
   LONGS_EQUAL (server->uid (), server->sendMsg.itf.id);
   LONGS_EQUAL (Alert::STATUS_CMD, server->sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, server->sendMsg.type);

   Alert::Message alert_msg;

   alert_msg.unpack (server->sendMsg.payload);

   LONGS_EQUAL (5, alert_msg.type);
   LONGS_EQUAL (0x00000008, alert_msg.state);
}

//! @test Should return attribute.
TEST (AlertServer, Attribute)
{
   HF::Attributes::IAttribute *attr = server->attribute (Alert::__LAST_ATTR__ + 1);

   CHECK_TRUE (attr == nullptr);

   attr = server->attribute (Alert::STATE_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (Alert::STATE_ATTR, attr->uid ());
   CHECK_FALSE (attr->isWritable ());

   LONGS_EQUAL (server->uid (), attr->interface ());

   delete attr;

   attr = server->attribute (Alert::ENABLE_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (Alert::ENABLE_ATTR, attr->uid ());
   CHECK_TRUE (attr->isWritable ());

   LONGS_EQUAL (server->uid (), attr->interface ());

   delete attr;
}

// =============================================================================
// AlertClient
// =============================================================================

//! Test Group for AlertClient interface class.
TEST_GROUP (AlertClient)
{
   struct TestAlertClient:public Testing::InterfaceHelper <Alert::Client>
   {
      uint16_t profile_uid;
      uint32_t state;

      TestAlertClient():profile_uid (0), state (0) {}

      void status (HF::Protocol::Address &source, Alert::Message &message)
      {
         mock ("AlertClient").actualCall ("status");

         Testing::InterfaceHelper <Alert::Client>::status (source, message);

         profile_uid = message.type;
         state       = message.state;
      }
   };

   TestAlertClient  *client;

   Protocol::Packet packet;
   ByteArray expected;

   TEST_SETUP ()
   {
      mock ("AlertClient").ignoreOtherCalls ();

      client   = new TestAlertClient ();

      expected = ByteArray {0x00, 0x00, 0x00,
                            0x5A, 0xA5,              // Unit Type.
                            0xFF, 0xA5, 0x5A, 0xBB,  // State.
                            0x00, 0x00, 0x00};

      packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
      packet.message.itf.id     = client->uid ();
      packet.message.itf.member = Alert::STATUS_CMD;

      packet.message.length     = expected.size ();
   }

   TEST_TEARDOWN ()
   {
      delete client;
      mock ().clear ();
   }
};

//! @test Should handle valid message.
TEST (AlertClient, Handle_Valid_Message)
{
   mock ("AlertClient").expectOneCall ("status");

   Result result = client->handle (packet, expected, 3);
   CHECK_EQUAL (Result::OK, result);

   LONGS_EQUAL (0x5AA5, client->profile_uid);
   LONGS_EQUAL (0xFFA55ABB, client->state);

   mock ("AlertClient").checkExpectations ();
}

//! @test Should not handle message from invalid role.
TEST (AlertClient, Handle_Invalid_Role)
{
   packet.message.itf.role = HF::Interface::SERVER_ROLE;

   CHECK_EQUAL (Result::FAIL_SUPPORT, client->handle (packet, expected, 3));
}

//! @test Should not handle message from invalid interface UID.
TEST (AlertClient, Handle_Invalid_UID)
{
   packet.message.itf.id = client->uid () + 1;

   CHECK_EQUAL (Result::FAIL_ARG, client->handle (packet, expected, 3));
}

//! @test Should not handle message with invalid payload size.
TEST (AlertClient, Handle_Invalid_Payload_Size)
{
   Alert::Message alert_msg;
   packet.message.length = alert_msg.size () - 1;

   CHECK_EQUAL (Result::FAIL_ARG, client->handle (packet, expected, 3));
}

//! @test Should not handle message with not enough payload.
TEST (AlertClient, Handle_Invalid_Payload)
{
   CHECK_EQUAL (Result::FAIL_ARG, client->handle (packet, expected, 10));
}
