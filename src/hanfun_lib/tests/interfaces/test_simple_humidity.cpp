// =============================================================================
/*!
 * @file       tests/interfaces/test_simple_humidity.cpp
 *
 * This is file contains the unit tests for the Simple Humidity %Interface
 * implementation.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2015 ULE Alliance
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 *
 * Initial development by Bithium S.A. [http://www.bithium.com]
 */
// =============================================================================

#include "hanfun/interfaces/simple_humidity.h"

#include "test_helper.h"

using namespace HF;
using namespace HF::Common;
using namespace HF::Interfaces;

using namespace HF::Testing;

// =============================================================================
// SimpleHumidity
// =============================================================================

TEST_GROUP (SimpleHumidity)
{
   class TestSimpleHumidity:public InterfaceParentHelper <SimpleHumidity::Base>
   {};

   TestSimpleHumidity interface;
};

TEST (SimpleHumidity, UID)
{
   CHECK_EQUAL (HF::Interface::SIMPLE_HUMIDITY, interface.uid ());
}

// =============================================================================
// SimpleHumidity Client API
// =============================================================================

TEST_GROUP (SimpleHumidityClient)
{
   class TestSimpleHumidityClient:public InterfaceHelper <SimpleHumidity::Client>
   {
      void read_resp (const Protocol::Address &addr, const HF::Attributes::Attribute <uint16_t> &attr)
      {
         UNUSED (addr);

         unsigned int value = (unsigned int) attr.value ();

         auto &call         = mock ("SimpleHumidity::Client").actualCall ("read_resp");
         call.withParameter ("attr_uid", attr.uid ());
         call.withParameter ("attr_value", value);
      }
   };

   TestSimpleHumidityClient client;
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

/*!
 * @test Check if a GET_ATTR_PACK_REQ message is sent.
 */
TEST (SimpleHumidityClient, ReadAll_Request)
{
   mock ("Interface").expectOneCall ("send");

   client.read_all (addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (Attributes::Pack::ALL, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::GET_ATTR_PACK_REQ, client.sendMsg.type);
}

/*!
 * @test Check if a GET_ATTR_REQ message is sent for the measured humidity attribute.
 */
TEST (SimpleHumidityClient, Read_Humidity_Request)
{
   mock ("Interface").expectOneCall ("send");

   client.read <SimpleHumidity::VALUE_ATTR>(addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (SimpleHumidity::VALUE_ATTR, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::GET_ATTR_REQ, client.sendMsg.type);
}

/*!
 * @test Check if a GET_ATTR_REQ message is sent for the tolerance attribute.
 */
TEST (SimpleHumidityClient, Read_Tolerance_Request)
{
   mock ("Interface").expectOneCall ("send");

   client.read <SimpleHumidity::TOLERANCE_ATTR>(addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (SimpleHumidity::TOLERANCE_ATTR, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::GET_ATTR_REQ, client.sendMsg.type);
}

/*!
 * @test Check if a GET_ATTR_PACK_RES/Pack::ALL message is correctly parsed.
 */
TEST (SimpleHumidityClient, ReadAll_Response)
{
   Protocol::Packet packet;

   packet.message.type       = Protocol::Message::GET_ATTR_PACK_RES;
   packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
   packet.message.itf.id     = HF::Interface::SIMPLE_HUMIDITY;
   packet.message.itf.member = HF::Attributes::Pack::ALL;

   ByteArray payload = ByteArray {0x00, 0x00, 0x00,
                                  Result::OK,         // Response result
                                  0x02,               // Number of attributes

                                  // Measured Humidity
                                  SimpleHumidity::VALUE_ATTR,
                                  0x12, 0x34,

                                  // Tolerance
                                  SimpleHumidity::TOLERANCE_ATTR,
                                  0xCD, 0xEF,

                                  0x00, 0x00, 0x00};

   auto &call = mock ("SimpleHumidity::Client").expectOneCall ("read_resp");
   call.withParameter ("attr_uid", (uint8_t) SimpleHumidity::VALUE_ATTR);
   call.withParameter ("attr_value", (uint16_t) 0x1234);

   auto &call2 = mock ("SimpleHumidity::Client").expectOneCall ("read_resp");
   call2.withParameter ("attr_uid", (uint8_t) SimpleHumidity::TOLERANCE_ATTR);
   call2.withParameter ("attr_value", (uint16_t) 0xCDEF);

   CHECK_EQUAL (Result::OK, client.handle (packet, payload, 3));

   mock ("SimpleHumidity::Client").checkExpectations ();
}

/*!
 * @test Check if a GET_ATTR_RES message for the measured humidity is correctly parsed.
 */
TEST (SimpleHumidityClient, Read_Humidity_Response)
{
   Protocol::Packet packet;

   packet.message.type       = Protocol::Message::GET_ATTR_RES;
   packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
   packet.message.itf.id     = HF::Interface::SIMPLE_HUMIDITY;
   packet.message.itf.member = SimpleHumidity::VALUE_ATTR;

   ByteArray payload = ByteArray {0x00, 0x00, 0x00,
                                  Result::OK,         // Response result
                                  0x12, 0x34,
                                  0x00, 0x00, 0x00};

   auto &call = mock ("SimpleHumidity::Client").expectOneCall ("read_resp");
   call.withParameter ("attr_uid", SimpleHumidity::VALUE_ATTR);
   call.withParameter ("attr_value", (int16_t) 0x1234);

   CHECK_EQUAL (Result::OK, client.handle (packet, payload, 3));

   mock ("SimpleHumidity::Client").checkExpectations ();
}

/*!
 * @test Check if a GET_ATTR_RES message for the tolerance is correctly parsed.
 */
TEST (SimpleHumidityClient, Read_Tolerance_Response)
{
   Protocol::Packet packet;

   packet.message.type       = Protocol::Message::GET_ATTR_RES;
   packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
   packet.message.itf.id     = HF::Interface::SIMPLE_HUMIDITY;
   packet.message.itf.member = SimpleHumidity::TOLERANCE_ATTR;

   ByteArray payload = ByteArray {0x00, 0x00, 0x00,
                                  Result::OK,         // Response result
                                  0xCD, 0xEF,
                                  0x00, 0x00, 0x00};

   auto &call = mock ("SimpleHumidity::Client").expectOneCall ("read_resp");
   call.withParameter ("attr_uid", SimpleHumidity::TOLERANCE_ATTR);
   call.withParameter ("attr_value", (uint16_t) 0xCDEF);

   CHECK_EQUAL (Result::OK, client.handle (packet, payload, 3));

   mock ("SimpleHumidity::Client").checkExpectations ();
}

// =============================================================================
// SimpleHumidity Server API
// =============================================================================

TEST_GROUP (SimpleHumidityServer)
{
   struct TestSimpleHumidityServer:public InterfaceHelper <SimpleHumidity::Server>
   {};

   TestSimpleHumidityServer *server;

   Protocol::Packet packet;
   ByteArray expected;

   TEST_SETUP ()
   {
      server = new TestSimpleHumidityServer ();

      mock ("Interface").ignoreOtherCalls ();

      expected = ByteArray {0x00, 0x00, 0x00,
                            0x56, 0x78, // Humidity value.
                            0x00, 0x00, 0x00};

      packet.message.itf.role   = HF::Interface::SERVER_ROLE;
      packet.message.itf.id     = server->uid ();
      packet.message.itf.member = SimpleHumidity::VALUE_ATTR;

      packet.message.type       = Protocol::Message::SET_ATTR_REQ;

      packet.message.length     = expected.size ();
   }

   TEST_TEARDOWN ()
   {
      mock ().clear ();
      delete server;
   }
};

TEST (SimpleHumidityServer, Notification_Humidity)
{
   CHECK_EQUAL (0, server->humidity ());
   mock ("Interface").expectOneCall ("notify");
   server->humidity (42);
   mock ("Interface").checkExpectations ();
   CHECK_EQUAL (42, server->humidity ());
}

//! @test Should not change humidity value.
TEST (SimpleHumidityServer, SetAttribute_Humidity)
{
   packet.message.itf.member = SimpleHumidity::VALUE_ATTR;

   server->humidity (0x1234);

   Result result = server->handle (packet, expected, 3);
   CHECK_EQUAL (Result::FAIL_RO_ATTR, result);

   LONGS_EQUAL (0x1234, server->humidity ());
}

//! @test Should not handle message from invalid role.
TEST (SimpleHumidityServer, Handle_Invalid_Role)
{
   packet.message.itf.role = HF::Interface::CLIENT_ROLE;

   CHECK_EQUAL (Result::FAIL_SUPPORT, server->handle (packet, expected, 3));
}

//! @test Should not handle message from invalid interface UID.
TEST (SimpleHumidityServer, Handle_Invalid_UID)
{
   packet.message.itf.id = server->uid () + 1;

   CHECK_EQUAL (Result::FAIL_ARG, server->handle (packet, expected, 3));
}

//! @test Should not handle message with not enough payload / offset.
TEST (SimpleHumidityServer, Handle_Invalid_Payload)
{
   CHECK_EQUAL (Result::FAIL_RO_ATTR, server->handle (packet, expected, 10));
}

//! @test Should not return valid attribute.
TEST (SimpleHumidityServer, InvalidAttribute)
{
   auto attr = server->attribute (SimpleHumidity::__LAST_ATTR__ + 1);

   CHECK_TRUE (attr == nullptr);
}

//! @test Should return humidity attribute.
TEST (SimpleHumidityServer, Humidity_Attribute)
{
   using namespace HF::Attributes;

   server->humidity (0x1234);

   auto attr = server->attribute (SimpleHumidity::VALUE_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (SimpleHumidity::VALUE_ATTR, attr->uid ());
   CHECK_FALSE (attr->isWritable ());

   LONGS_EQUAL (server->uid (), attr->interface ());

   POINTERS_EQUAL (server, attr->owner ());

   auto temp = static_cast <Attribute <int16_t, SimpleHumidity::Server> *>(attr);
   LONGS_EQUAL (server->humidity (), temp->value ());

   temp->value ((int16_t) 0x5678);
   LONGS_EQUAL (0x5678, server->humidity ());

   delete attr;
}

//! @test Should return maximum humidity attribute.
TEST (SimpleHumidityServer, Tolerance_Attribute)
{
   using namespace HF::Attributes;

   auto attr = server->attribute (SimpleHumidity::TOLERANCE_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (SimpleHumidity::TOLERANCE_ATTR, attr->uid ());
   CHECK_FALSE (attr->isWritable ());

   LONGS_EQUAL (server->uid (), attr->interface ());

   POINTERS_EQUAL (server, attr->owner ());

   auto temp     = static_cast <Attribute <uint16_t, SimpleHumidity::Server> *>(attr);

   int16_t value = server->tolerance ();
   LONGS_EQUAL (value, temp->value ());

   temp->value ((int16_t) 0x5678);
   LONGS_EQUAL (value, server->tolerance ());

   delete attr;
}
