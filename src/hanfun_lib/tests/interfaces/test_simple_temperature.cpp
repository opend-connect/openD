// =============================================================================
/*!
 * @file       tests/interfaces/test_simple_temperature.cpp
 *
 * This is file contains the unit tests for the Simple Temperature %Interface
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

#include "hanfun/interfaces/simple_temperature.h"

#include "test_helper.h"

using namespace HF;
using namespace HF::Common;
using namespace HF::Interfaces;

using namespace HF::Testing;

// =============================================================================
// SimpleTemperature
// =============================================================================

TEST_GROUP (SimpleTemperature)
{
   class TestSimpleTemperature:public InterfaceParentHelper <SimpleTemperature::Base>
   {};

   TestSimpleTemperature interface;
};

TEST (SimpleTemperature, UID)
{
   CHECK_EQUAL (HF::Interface::SIMPLE_TEMPERATURE, interface.uid ());
}

// =============================================================================
// SimpleTemperature Client API
// =============================================================================

TEST_GROUP (SimpleTemperatureClient)
{
   class TestSimpleTemperatureClient:public InterfaceHelper <SimpleTemperature::Client>
   {
      void read_resp (const Protocol::Address &addr, const HF::Attributes::Attribute <int16_t> &attr)
      {
         UNUSED (addr);

         int value  = (int) attr.value ();

         auto &call = mock ("SimpleTemperature::Client").actualCall ("read_resp");
         call.withParameter ("attr_uid", attr.uid ());
         call.withParameter ("attr_value", value);
      }

      void read_resp (const Protocol::Address &addr, const HF::Attributes::Attribute <uint16_t> &attr)
      {
         UNUSED (addr);
         UNUSED (attr);

         unsigned int value = (unsigned int) attr.value ();

         auto &call         = mock ("SimpleTemperature::Client").actualCall ("read_resp");
         call.withParameter ("attr_uid", attr.uid ());
         call.withParameter ("attr_value", value);
      }
   };

   TestSimpleTemperatureClient client;
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
TEST (SimpleTemperatureClient, ReadAll_Request)
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
 * @test Check if a GET_ATTR_REQ message is sent for the measured temperature attribute.
 */
TEST (SimpleTemperatureClient, Read_Temperature_Request)
{
   mock ("Interface").expectOneCall ("send");

   client.read <SimpleTemperature::VALUE_ATTR>(addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (SimpleTemperature::VALUE_ATTR, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::GET_ATTR_REQ, client.sendMsg.type);
}

/*!
 * @test Check if a GET_ATTR_REQ message is sent for the minimum measurable temperature attribute.
 */
TEST (SimpleTemperatureClient, Read_MinTemperature_Request)
{
   mock ("Interface").expectOneCall ("send");

   client.read <SimpleTemperature::MINIMUM_ATTR>(addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (SimpleTemperature::MINIMUM_ATTR, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::GET_ATTR_REQ, client.sendMsg.type);
}

/*!
 * @test Check if a GET_ATTR_REQ message is sent for the maximum measurable temperature attribute.
 */
TEST (SimpleTemperatureClient, Read_MaxTemperature_Request)
{
   mock ("Interface").expectOneCall ("send");

   client.read <SimpleTemperature::MAXIMUM_ATTR>(addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (SimpleTemperature::MAXIMUM_ATTR, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::GET_ATTR_REQ, client.sendMsg.type);
}

/*!
 * @test Check if a GET_ATTR_REQ message is sent for the tolerance attribute.
 */
TEST (SimpleTemperatureClient, Read_Tolerance_Request)
{
   mock ("Interface").expectOneCall ("send");

   client.read <SimpleTemperature::TOLERANCE_ATTR>(addr);

   mock ("Interface").checkExpectations ();

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, client.sendMsg.itf.role);
   LONGS_EQUAL (client.uid (), client.sendMsg.itf.id);
   LONGS_EQUAL (SimpleTemperature::TOLERANCE_ATTR, client.sendMsg.itf.member);
   LONGS_EQUAL (Protocol::Message::GET_ATTR_REQ, client.sendMsg.type);
}

/*!
 * @test Check if a GET_ATTR_PACK_RES/Pack::ALL message is correctly parsed.
 */
TEST (SimpleTemperatureClient, ReadAll_Response)
{
   Protocol::Packet packet;

   packet.message.type       = Protocol::Message::GET_ATTR_PACK_RES;
   packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
   packet.message.itf.id     = HF::Interface::SIMPLE_TEMPERATURE;
   packet.message.itf.member = HF::Attributes::Pack::ALL;

   ByteArray payload = ByteArray {0x00, 0x00, 0x00,
                                  Result::OK,         // Response result
                                  0x04,               // Number of attributes

                                  // Measured Temperature
                                  SimpleTemperature::VALUE_ATTR,
                                  0x12, 0x34,

                                  // Minimum Measurable Temperature
                                  SimpleTemperature::MINIMUM_ATTR,
                                  0x56, 0x78,

                                  // Maximum Measurable Temperature
                                  SimpleTemperature::MAXIMUM_ATTR,
                                  0x9A, 0xBC,

                                  // Tolerance
                                  SimpleTemperature::TOLERANCE_ATTR,
                                  0xCD, 0xEF,

                                  0x00, 0x00, 0x00};

   auto &call = mock ("SimpleTemperature::Client").expectOneCall ("read_resp");
   call.withParameter ("attr_uid", (uint8_t) SimpleTemperature::VALUE_ATTR);
   call.withParameter ("attr_value", (int16_t) 0x1234);

   auto &call2 = mock ("SimpleTemperature::Client").expectOneCall ("read_resp");
   call2.withParameter ("attr_uid", (uint8_t) SimpleTemperature::MINIMUM_ATTR);
   call2.withParameter ("attr_value", (int16_t) 0x5678);

   auto &call3 = mock ("SimpleTemperature::Client").expectOneCall ("read_resp");
   call3.withParameter ("attr_uid", (uint8_t) SimpleTemperature::MAXIMUM_ATTR);
   call3.withParameter ("attr_value", (int16_t) 0x9ABC);

   auto &call4 = mock ("SimpleTemperature::Client").expectOneCall ("read_resp");
   call4.withParameter ("attr_uid", (uint8_t) SimpleTemperature::TOLERANCE_ATTR);
   call4.withParameter ("attr_value", (uint16_t) 0xCDEF);

   CHECK_EQUAL (Result::OK, client.handle (packet, payload, 3));

   mock ("SimpleTemperature::Client").checkExpectations ();
}

/*!
 * @test Check if a GET_ATTR_RES message for the measured temperature is correctly parsed.
 */
TEST (SimpleTemperatureClient, Read_Temperature_Response)
{
   Protocol::Packet packet;

   packet.message.type       = Protocol::Message::GET_ATTR_RES;
   packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
   packet.message.itf.id     = HF::Interface::SIMPLE_TEMPERATURE;
   packet.message.itf.member = SimpleTemperature::VALUE_ATTR;

   ByteArray payload = ByteArray {0x00, 0x00, 0x00,
                                  Result::OK,         // Response result
                                  0x12, 0x34,
                                  0x00, 0x00, 0x00};

   auto &call = mock ("SimpleTemperature::Client").expectOneCall ("read_resp");
   call.withParameter ("attr_uid", SimpleTemperature::VALUE_ATTR);
   call.withParameter ("attr_value", (int16_t) 0x1234);

   CHECK_EQUAL (Result::OK, client.handle (packet, payload, 3));

   mock ("SimpleTemperature::Client").checkExpectations ();
}

/*!
 * @test Check if a GET_ATTR_RES message for the minimum measurable temperature
 * is correctly parsed.
 */
TEST (SimpleTemperatureClient, Read_MinTemperature_Response)
{
   Protocol::Packet packet;

   packet.message.type       = Protocol::Message::GET_ATTR_RES;
   packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
   packet.message.itf.id     = HF::Interface::SIMPLE_TEMPERATURE;
   packet.message.itf.member = SimpleTemperature::MINIMUM_ATTR;

   ByteArray payload = ByteArray {0x00, 0x00, 0x00,
                                  Result::OK,         // Response result
                                  0x45, 0x67,
                                  0x00, 0x00, 0x00};

   auto &call = mock ("SimpleTemperature::Client").expectOneCall ("read_resp");
   call.withParameter ("attr_uid", SimpleTemperature::MINIMUM_ATTR);
   call.withParameter ("attr_value", (int16_t) 0x4567);

   CHECK_EQUAL (Result::OK, client.handle (packet, payload, 3));

   mock ("SimpleTemperature::Client").checkExpectations ();
}

/*!
 * @test Check if a GET_ATTR_RES message for the maximum measurable temperature
 * is correctly parsed.
 */
TEST (SimpleTemperatureClient, Read_MaxTemperature_Response)
{
   Protocol::Packet packet;

   packet.message.type       = Protocol::Message::GET_ATTR_RES;
   packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
   packet.message.itf.id     = HF::Interface::SIMPLE_TEMPERATURE;
   packet.message.itf.member = SimpleTemperature::MAXIMUM_ATTR;

   ByteArray payload = ByteArray {0x00, 0x00, 0x00,
                                  Result::OK,         // Response result
                                  0x89, 0xAB,
                                  0x00, 0x00, 0x00};

   auto &call = mock ("SimpleTemperature::Client").expectOneCall ("read_resp");
   call.withParameter ("attr_uid", SimpleTemperature::MAXIMUM_ATTR);
   call.withParameter ("attr_value", (int16_t) 0x89AB);

   CHECK_EQUAL (Result::OK, client.handle (packet, payload, 3));

   mock ("SimpleTemperature::Client").checkExpectations ();
}

/*!
 * @test Check if a GET_ATTR_RES message for the tolerance is correctly parsed.
 */
TEST (SimpleTemperatureClient, Read_Tolerance_Response)
{
   Protocol::Packet packet;

   packet.message.type       = Protocol::Message::GET_ATTR_RES;
   packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
   packet.message.itf.id     = HF::Interface::SIMPLE_TEMPERATURE;
   packet.message.itf.member = SimpleTemperature::TOLERANCE_ATTR;

   ByteArray payload = ByteArray {0x00, 0x00, 0x00,
                                  Result::OK,         // Response result
                                  0xCD, 0xEF,
                                  0x00, 0x00, 0x00};

   auto &call = mock ("SimpleTemperature::Client").expectOneCall ("read_resp");
   call.withParameter ("attr_uid", SimpleTemperature::TOLERANCE_ATTR);
   call.withParameter ("attr_value", (uint16_t) 0xCDEF);

   CHECK_EQUAL (Result::OK, client.handle (packet, payload, 3));

   mock ("SimpleTemperature::Client").checkExpectations ();
}

// =============================================================================
// SimpleTemperature Server API
// =============================================================================

TEST_GROUP (SimpleTemperatureServer)
{
   struct TestSimpleTemperatureServer:public InterfaceHelper <SimpleTemperature::Server>
   {};

   TestSimpleTemperatureServer *server;

   Protocol::Packet packet;
   ByteArray expected;

   TEST_SETUP ()
   {
      server = new TestSimpleTemperatureServer ();

      mock ("LevelControlServer").ignoreOtherCalls ();
      mock ("Interface").ignoreOtherCalls ();

      expected = ByteArray {0x00, 0x00, 0x00,
                            0x56, 0x78, // Temperature value.
                            0x00, 0x00, 0x00};

      packet.message.itf.role   = HF::Interface::SERVER_ROLE;
      packet.message.itf.id     = server->uid ();
      packet.message.itf.member = SimpleTemperature::VALUE_ATTR;

      packet.message.type       = Protocol::Message::SET_ATTR_REQ;

      packet.message.length     = expected.size ();
   }

   TEST_TEARDOWN ()
   {
      mock ().clear ();
      delete server;
   }
};

TEST (SimpleTemperatureServer, Notification_Temperature)
{
   CHECK_EQUAL (0, server->temperature ());
   mock ("Interface").expectOneCall ("notify");
   server->temperature (42);
   mock ("Interface").checkExpectations ();
   CHECK_EQUAL (42, server->temperature ());
}

//! @test Should not change temperature value.
TEST (SimpleTemperatureServer, SetAttribute_Temperature)
{
   packet.message.itf.member = SimpleTemperature::VALUE_ATTR;

   server->temperature (0x1234);

   Result result = server->handle (packet, expected, 3);
   CHECK_EQUAL (Result::FAIL_RO_ATTR, result);

   LONGS_EQUAL (0x1234, server->temperature ());
}

//! @test Should not handle message from invalid role.
TEST (SimpleTemperatureServer, Handle_Invalid_Role)
{
   packet.message.itf.role = HF::Interface::CLIENT_ROLE;

   CHECK_EQUAL (Result::FAIL_SUPPORT, server->handle (packet, expected, 3));
}

//! @test Should not handle message from invalid interface UID.
TEST (SimpleTemperatureServer, Handle_Invalid_UID)
{
   packet.message.itf.id = server->uid () + 1;

   CHECK_EQUAL (Result::FAIL_ARG, server->handle (packet, expected, 3));
}

//! @test Should not handle message with not enough payload / offset.
TEST (SimpleTemperatureServer, Handle_Invalid_Payload)
{
   CHECK_EQUAL (Result::FAIL_RO_ATTR, server->handle (packet, expected, 10));
}

//! @test Should not return valid attribute.
TEST (SimpleTemperatureServer, InvalidAttribute)
{
   auto attr = server->attribute (SimpleTemperature::__LAST_ATTR__ + 1);

   CHECK_TRUE (attr == nullptr);
}

//! @test Should return temperature attribute.
TEST (SimpleTemperatureServer, Temperature_Attribute)
{
   using namespace HF::Attributes;

   server->temperature (0x1234);

   auto attr = server->attribute (SimpleTemperature::VALUE_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (SimpleTemperature::VALUE_ATTR, attr->uid ());
   CHECK_FALSE (attr->isWritable ());

   LONGS_EQUAL (server->uid (), attr->interface ());

   POINTERS_EQUAL (server, attr->owner ());

   auto temp = static_cast <Attribute <int16_t, SimpleTemperature::Server> *>(attr);
   LONGS_EQUAL (server->temperature (), temp->value ());

   temp->value ((int16_t) 0x5678);
   LONGS_EQUAL (0x5678, server->temperature ());

   delete attr;
}

//! @test Should return minimum temperature attribute.
TEST (SimpleTemperatureServer, MinTemperature_Attribute)
{
   using namespace HF::Attributes;

   auto attr = server->attribute (SimpleTemperature::MINIMUM_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (SimpleTemperature::MINIMUM_ATTR, attr->uid ());
   CHECK_FALSE (attr->isWritable ());

   LONGS_EQUAL (server->uid (), attr->interface ());

   POINTERS_EQUAL (server, attr->owner ());

   auto temp     = static_cast <Attribute <int16_t, SimpleTemperature::Server> *>(attr);

   int16_t value = server->minimum_temperature ();
   LONGS_EQUAL (value, temp->value ());

   temp->value ((int16_t) 0x5678);
   LONGS_EQUAL (value, server->minimum_temperature ());

   delete attr;
}

//! @test Should return maximum temperature attribute.
TEST (SimpleTemperatureServer, MaxTemperature_Attribute)
{
   using namespace HF::Attributes;

   auto attr = server->attribute (SimpleTemperature::MAXIMUM_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (SimpleTemperature::MAXIMUM_ATTR, attr->uid ());
   CHECK_FALSE (attr->isWritable ());

   LONGS_EQUAL (server->uid (), attr->interface ());

   POINTERS_EQUAL (server, attr->owner ());

   auto temp     = static_cast <Attribute <int16_t, SimpleTemperature::Server> *>(attr);

   int16_t value = server->maximum_temperature ();
   LONGS_EQUAL (value, temp->value ());

   temp->value ((int16_t) 0x5678);
   LONGS_EQUAL (value, server->maximum_temperature ());

   delete attr;
}

//! @test Should return maximum temperature attribute.
TEST (SimpleTemperatureServer, Tolerance_Attribute)
{
   using namespace HF::Attributes;

   auto attr = server->attribute (SimpleTemperature::TOLERANCE_ATTR);

   CHECK_TRUE (attr != nullptr);

   LONGS_EQUAL (SimpleTemperature::TOLERANCE_ATTR, attr->uid ());
   CHECK_FALSE (attr->isWritable ());

   LONGS_EQUAL (server->uid (), attr->interface ());

   POINTERS_EQUAL (server, attr->owner ());

   auto temp     = static_cast <Attribute <uint16_t, SimpleTemperature::Server> *>(attr);

   int16_t value = server->tolerance ();
   LONGS_EQUAL (value, temp->value ());

   temp->value ((int16_t) 0x5678);
   LONGS_EQUAL (value, server->tolerance ());

   delete attr;
}
