// =============================================================================
/*!
 * @file       tests/test_protocol.cpp
 *
 * This file contains the implementation of the unit tests for the protocol
 * layer in the HAN-FUN specification.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================
#include <algorithm>
#include <random>

#include "test_helper.h"

#include "hanfun/protocol.h"
#include "hanfun/interface.h"

using namespace std;
using namespace HF;
using namespace HF::Protocol;
using namespace HF::Common;

// =============================================================================
// Message / Address
// =============================================================================

TEST_GROUP (Message_Address)
{
   ByteArray expected_1;
   ByteArray expected_2;

   Protocol::Address addr;

   TEST_SETUP ()
   {
      expected_1 = ByteArray {0x00, 0x00, 0x00, 0xFA, 0xAA, 0x55, 0x00, 0x00, 0x00};

      expected_2 = ByteArray {0x00, 0x00, 0x00, 0x7A, 0xAA, 0x55, 0x00, 0x00, 0x00};
   }
};

TEST (Message_Address, Default)
{
   LONGS_EQUAL (0, addr.mod);
   LONGS_EQUAL (Protocol::BROADCAST_ADDR, addr.device);
   LONGS_EQUAL (Protocol::BROADCAST_UNIT, addr.unit);
}

TEST (Message_Address, Size)
{
   LONGS_EQUAL (3, addr.size ());
}

TEST (Message_Address, Pack)
{
   addr.mod    = 1;
   addr.device = 0x7AAA;
   addr.unit   = 0x55;

   ByteArray array (addr.size () + 6);

   uint16_t  wsize = addr.pack (array, 3);
   LONGS_EQUAL (addr.size (), wsize);

   CHECK_EQUAL (expected_1, array);

   addr.mod    = 0;
   addr.device = 0x7AAA;
   addr.unit   = 0x55;

   wsize       = addr.pack (array, 3);
   LONGS_EQUAL (addr.size (), wsize);

   CHECK_EQUAL (expected_2, array);
}

TEST (Message_Address, Unpack)
{
   uint16_t rsize = addr.unpack (expected_1, 3);
   LONGS_EQUAL (addr.size (), rsize);

   LONGS_EQUAL (1, addr.mod);
   LONGS_EQUAL (0x7AAA, addr.device);
   LONGS_EQUAL (0x55, addr.unit);

   rsize = addr.unpack (expected_2, 3);
   LONGS_EQUAL (addr.size (), rsize);

   LONGS_EQUAL (0, addr.mod);
   LONGS_EQUAL (0x7AAA, addr.device);
   LONGS_EQUAL (0x55, addr.unit);
}

// =============================================================================
// Message / Interface
// =============================================================================

TEST_GROUP (Message_Interface)
{
   ByteArray expected_1;
   ByteArray expected_2;

   Message::Interface addr;

   TEST_SETUP ()
   {
      expected_1 = ByteArray {0x00, 0x00, 0x00,
                              0xFA,
                              0xAA,  // Server Role / Interface UID.
                              0x55,  // Interface Member.
                              0x00, 0x00, 0x00};

      expected_2 = ByteArray {0x00, 0x00, 0x00,
                              0x7A,
                              0xAA,  // Client Role / Interface UID.
                              0x55,  // Interface Member.
                              0x00, 0x00, 0x00};
   }
};

TEST (Message_Interface, Size)
{
   LONGS_EQUAL (3, addr.size ());
}

TEST (Message_Interface, Pack)
{
   addr.role   = 1;
   addr.id     = 0x7AAA;
   addr.member = 0x55;

   ByteArray array (addr.size () + 6);

   uint16_t  wsize = addr.pack (array, 3);
   LONGS_EQUAL (addr.size (), wsize);

   CHECK_EQUAL (expected_1, array);

   addr.role   = 0;
   addr.id     = 0x7AAA;
   addr.member = 0x55;

   wsize       = addr.pack (array, 3);
   LONGS_EQUAL (addr.size (), wsize);

   CHECK_EQUAL (expected_2, array);
}

TEST (Message_Interface, Unpack)
{
   uint16_t rsize = addr.unpack (expected_1, 3);
   LONGS_EQUAL (addr.size (), rsize);

   LONGS_EQUAL (1, addr.role);
   LONGS_EQUAL (0x7AAA, addr.id);
   LONGS_EQUAL (0x55, addr.member);

   rsize = addr.unpack (expected_2, 3);
   LONGS_EQUAL (addr.size (), rsize);

   LONGS_EQUAL (0, addr.role);
   LONGS_EQUAL (0x7AAA, addr.id);
   LONGS_EQUAL (0x55, addr.member);
}

// =============================================================================
// Message
// =============================================================================

TEST_GROUP (Message)
{
   struct TestMessage:public Message
   {
      using Message::length;
   };

   TestMessage message;

   ByteArray   expected;

   Testing::Payload payload;
   TEST_SETUP ()
   {
      expected = ByteArray {0x00, 0x00, 0x00,
                            0xAA,                       // Application Reference.
                            Message::COMMAND_RESP_REQ,  // Message Type.
                            0xFA, 0xAA, 0x55,           // Interface Address.
                            0x01, 0xAA,                 // Payload length.
                            0x00, 0x00, 0x00};
      payload = Testing::Payload (0x01AA);

      expected.reserve (expected.size () + payload.size ());
      expected.insert (expected.begin () + 10, payload.data.begin (), payload.data.end ());
   }

   TEST_TEARDOWN ()
   {}
};

TEST (Message, Size)
{
   LONGS_EQUAL (0, message.payload.size ());
   LONGS_EQUAL (7, message.size ());

   message.payload = ByteArray (42);

   LONGS_EQUAL (7 + 42, message.size ());
}

TEST (Message, Pack)
{
   message.reference  = 0xAA;
   message.type       = Message::COMMAND_RESP_REQ;

   message.itf.role   = HF::Interface::SERVER_ROLE;
   message.itf.id     = 0x7AAA;
   message.itf.member = 0x55;

   payload.pack (message.payload);

   uint16_t  size = message.size ();
   ByteArray array (size + 6);

   uint16_t  wsize = message.pack (array, 3);
   LONGS_EQUAL (size, wsize);

   CHECK_EQUAL (expected, array);
}

TEST (Message, Unpack)
{
   uint16_t rsize = message.unpack (expected, 3);
   LONGS_EQUAL (7, rsize);

   LONGS_EQUAL (0xAA, message.reference);
   LONGS_EQUAL (Message::COMMAND_RESP_REQ, message.type);

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, message.itf.role);
   LONGS_EQUAL (0x7AAA, message.itf.id);
   LONGS_EQUAL (0x55, message.itf.member);

   LONGS_EQUAL (0x01AA, message.length);
   Testing::Payload temp (payload.size ());

   temp.unpack (expected, 3 + 7);

   CHECK_EQUAL (payload.data, temp.data);
}

// =============================================================================
// Packet
// =============================================================================

TEST_GROUP (Packet)
{
   class TestPayload
   {
      public:

      uint8_t data;

      uint16_t size () const
      {
         return sizeof(uint8_t);
      }

      uint16_t pack (ByteArray &array, uint16_t offset = 0) const
      {
         uint16_t start = offset;

         array.extend (size ());
         array.insert (array.begin () + offset, size (), 0);

         offset += array.write (offset, this->data);

         return offset - start;
      }

      uint16_t unpack (const ByteArray &array, uint16_t offset = 0)
      {
         uint16_t start = offset;

         offset += array.read (offset, this->data);

         return offset - start;
      }
   };

   TestPayload *payload;
   Packet *packet;

   ByteArray expected;

   TEST_SETUP ()
   {
      expected = ByteArray {0x00, 0x00, 0x00,
                            0x7A, 0xAA,            // Source device Address.
                            0x55,                  // Source unit.
                            0xF5, 0x55,            // Destination device Address.
                            0xAA,                  // Destination unit.
                            0x00, 0x00,            // Transport header.
                            0xCC,                  // Application Reference.
                            Message::COMMAND_REQ,  // Message Type.
                            0xFA, 0xAA, 0x55,      // Interface Address.
                            0x00, 0x01,            // Payload length.
                            0xAB,                  // Payload data.
                            0x00, 0x00, 0x00};

      payload = new TestPayload ();
      packet  = new Packet ();
   }

   TEST_TEARDOWN ()
   {
      delete packet;
      delete payload;
   }
};

TEST (Packet, Size)
{
   Protocol::Address addr;

   uint16_t size = 2 * addr.size () +       // Network address
                   sizeof(uint16_t) +       // Transport header.
                   packet->message.size (); // Payload size.

   LONGS_EQUAL (size, packet->size ());
}

TEST (Packet, Pack)
{
   packet->source.mod         = Protocol::Address::DEVICE;
   packet->source.device      = 0x7AAA;
   packet->source.unit        = 0x55;

   packet->destination.mod    = Protocol::Address::GROUP;
   packet->destination.device = 0x7555;
   packet->destination.unit   = 0xAA;

   packet->message.reference  = 0xCC;
   packet->message.type       = Message::COMMAND_REQ;
   packet->message.itf.role   = 1;
   packet->message.itf.id     = 0x7AAA;
   packet->message.itf.member = 0x55;

   payload->data              = 0xAB;

   payload->pack (packet->message.payload);

   ByteArray array (packet->size () + 6);

   uint16_t  wsize = packet->pack (array, 3);
   LONGS_EQUAL (6 + 2 + 7 + 1, wsize);

   CHECK_EQUAL (expected, array);
}

TEST (Packet, Unpack)
{
   uint16_t rsize = packet->unpack (expected, 3);
   LONGS_EQUAL (6 + 2 + 7, rsize);

   LONGS_EQUAL (Protocol::Address::DEVICE, packet->source.mod);
   LONGS_EQUAL (0x7AAA, packet->source.device);
   LONGS_EQUAL (0x55, packet->source.unit);

   LONGS_EQUAL (Protocol::Address::GROUP, packet->destination.mod);
   LONGS_EQUAL (0x7555, packet->destination.device);
   LONGS_EQUAL (0xAA, packet->destination.unit);

   LONGS_EQUAL (0xCC, packet->message.reference);
   LONGS_EQUAL (Message::COMMAND_REQ, packet->message.type);
   LONGS_EQUAL (1, packet->message.itf.role);
   LONGS_EQUAL (0x7AAA, packet->message.itf.id);
   LONGS_EQUAL (0x55, packet->message.itf.member);

   payload->unpack (expected, 3 + rsize);

   LONGS_EQUAL (0xAB, payload->data);
}

// =============================================================================
// Response
// =============================================================================

TEST_GROUP (Response)
{
   Response  *response;

   ByteArray expected;

   TEST_SETUP ()
   {
      /* *INDENT-OFF* */
      expected = ByteArray { 0x00, 0x00, 0x00,
                              Result::FAIL_ARG,
                              0x00, 0x00, 0x00 };
      /* *INDENT-ON* */

      response = new Response ();
   }

   TEST_TEARDOWN ()
   {
      delete response;
   }
};

TEST (Response, Size)
{
   LONGS_EQUAL (1, response->size ());
}

TEST (Response, Pack)
{
   response->code = Result::FAIL_ARG;

   uint16_t  size = response->size ();

   ByteArray array (response->size () + 6);

   uint16_t  wsize = response->pack (array, 3);
   LONGS_EQUAL (size, wsize);

   CHECK_EQUAL (expected, array);
}

TEST (Response, Unpack)
{
   uint16_t rsize = response->unpack (expected, 3);
   LONGS_EQUAL (1, rsize);  // Response code.

   LONGS_EQUAL (Result::FAIL_ARG, response->code);
}

// =============================================================================
// Attributes Messages
// =============================================================================

TEST_GROUP (AttributesProtocol)
{};

// =============================================================================
// GetAttributePack::Request
// =============================================================================

TEST (AttributesProtocol, GetAttributePack_Request_Pack)
{
   GetAttributePack::Request request;

   for (uint8_t i = 1; i <= 20; i++)
   {
      request.attributes.push_back (i);
   }

   ByteArray expected ({0x00, 0x00, 0x00,
                        0x14, // Number of attribute uid's.
                              // Attribute uid's.
                        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                        0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
                        0x00, 0x00, 0x00}
                      );

   ByteArray result (expected.size ());

   fill (result.begin (), result.end (), 0);

   request.pack (result, 3);

   CHECK_EQUAL (expected, result);
}

TEST (AttributesProtocol, GetAttributePack_Request_Unpack)
{
   ByteArray expected ({0x00, 0x00, 0x00,
                        0x14, // Number of attribute uid's.
                              // Attribute uid's.
                        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                        0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
                        0x00, 0x00, 0x00}
                      );

   GetAttributePack::Request request;

   request.unpack (expected, 3);

   LONGS_EQUAL (20, request.attributes.length ());

   for (uint8_t i = 1; i <= 20; i++)
   {
      check_index <int>((int) i, (int) request.attributes[i - 1], i - 1, "Attribute UID", __FILE__, __LINE__);
   }
}

// =============================================================================
// GetAttributePack::Response
// =============================================================================

TEST (AttributesProtocol, GetAttributePack_Response_Pack)
{
   Testing::TestInterface itf;
   GetAttributePack::Response response;

   itf.attr1 = 0xAAAA;
   itf.attr2 = 0xBBBB;
   itf.attr3 = 0xCCCC;

   response.attributes.push_back (itf.attribute (itf.ATTR1));
   response.attributes.push_back (itf.attribute (itf.ATTR2));
   response.attributes.push_back (itf.attribute (itf.ATTR3));

   ByteArray expected ({0x00, 0x00, 0x00,
                        Result::OK,                                           // Response code.
                        0x03,                                                 // Number of attribute uid's.
                        0x01, 0xAA, 0xAA, 0x02, 0xBB, 0xBB, 0x03, 0xCC, 0xCC, // Attribute's.
                        0x00, 0x00, 0x00}
                      );

   ByteArray result (expected.size ());

   fill (result.begin (), result.end (), 0);

   response.pack (result, 3);

   CHECK_EQUAL (expected, result);
}

TEST (AttributesProtocol, GetAttributePack_Response_Unpack)
{
   ByteArray expected ({0x00, 0x00, 0x00,
                        Result::OK,                                           // Response code.
                        0x03,                                                 // Number of attribute uid's.
                        0x01, 0xAA, 0xAA, 0x02, 0xBB, 0xBB, 0x03, 0xCC, 0xCC, // Attribute's.
                        0x00, 0x00, 0x00}
                      );

   GetAttributePack::Response response (Testing::TestInterface::create_attribute);

   response.unpack (expected, 3);

   LONGS_EQUAL (3, response.attributes.size ());

   HF::Attributes::IAttribute *attr                  = response.attributes[Testing::TestInterface::ATTR1];
   HF::Attributes::Attribute <uint16_t> *attr_proper = static_cast <HF::Attributes::Attribute <uint16_t> *>(attr);

   LONGS_EQUAL (0xAAAA, attr_proper->get ());

   attr        = response.attributes[Testing::TestInterface::ATTR2];
   attr_proper = static_cast <HF::Attributes::Attribute <uint16_t> *>(attr);

   LONGS_EQUAL (0xBBBB, attr_proper->get ());

   attr        = response.attributes[Testing::TestInterface::ATTR3];
   attr_proper = static_cast <HF::Attributes::Attribute <uint16_t> *>(attr);

   LONGS_EQUAL (0xCCCC, attr_proper->get ());
}

// =============================================================================
// SetAttributePack::Request
// =============================================================================

TEST (AttributesProtocol, SetAttributePack_Request_Pack)
{
   Testing::TestInterface itf;
   SetAttributePack::Request request;

   itf.attr1 = 0xAAAA;
   itf.attr2 = 0xBBBB;
   itf.attr3 = 0xCCCC;

   request.attributes.push_back (itf.attribute (itf.ATTR1));
   request.attributes.push_back (itf.attribute (itf.ATTR2));
   request.attributes.push_back (itf.attribute (itf.ATTR3));

   ByteArray expected ({0x00, 0x00, 0x00,
                        0x03,                                                 // Number of attribute uid's.
                        0x01, 0xAA, 0xAA, 0x02, 0xBB, 0xBB, 0x03, 0xCC, 0xCC, // Attribute's.
                        0x00, 0x00, 0x00}
                      );

   ByteArray result (expected.size ());

   fill (result.begin (), result.end (), 0);

   request.pack (result, 3);

   CHECK_EQUAL (expected, result);
}

TEST (AttributesProtocol, SetAttributePack_Request_Unpack)
{
   ByteArray expected ({0x00, 0x00, 0x00,
                        0x03,             // Number of attribute uid's.
                        0x01, 0xAA, 0xAA, // Attribute 1
                        0x02, 0xBB, 0xBB, // Attribute 2
                        0x03, 0xCC, 0xCC, // Attribute 3
                        0x00, 0x00, 0x00}
                      );

   Testing::TestInterface itf;
   SetAttributePack::Request request;

   CHECK_FALSE (itf.attr1 == 0xAAAA);
   CHECK_FALSE (itf.attr2 == 0xBBBB);
   CHECK_FALSE (itf.attr3 == 0xCCCC);

   request.unpack (expected, 3);

   LONGS_EQUAL (3, request.count);

   CHECK_FALSE (itf.attr1 == 0xAAAA);
   CHECK_FALSE (itf.attr2 == 0xBBBB);
   CHECK_FALSE (itf.attr3 == 0xCCCC);
}

// =============================================================================
// SetAttributePack::Response
// =============================================================================

TEST (AttributesProtocol, SetAttributePack_Response_Pack)
{
   SetAttributePack::Response response;

   SetAttributePack::Response::Result temp;

   temp.uid  = Testing::TestInterface::ATTR1;
   temp.code = Result::OK;

   response.results.push_back (temp);

   temp.uid  = Testing::TestInterface::ATTR2;
   temp.code = Result::FAIL_RO_ATTR;

   response.results.push_back (temp);

   temp.uid  = Testing::TestInterface::ATTR3 + 3;
   temp.code = Result::FAIL_SUPPORT;

   response.results.push_back (temp);

   ByteArray expected ({0x00, 0x00, 0x00,
                        0x03,                       // Number of attribute uid's.
                        0x01, Result::OK,           // Attribute 1
                        0x02, Result::FAIL_RO_ATTR, // Attribute 2
                        0x06, Result::FAIL_SUPPORT, // Attribute 3
                        0x00, 0x00, 0x00}
                      );
   ByteArray result (expected.size ());

   fill (result.begin (), result.end (), 0);

   response.pack (result, 3);

   CHECK_EQUAL (expected, result);
}

TEST (AttributesProtocol, SetAttributePack_Response_Unpack)
{
   ByteArray expected ({0x00, 0x00, 0x00,
                        0x03,                       // Number of attribute uid's.
                        0x01, Result::OK,           // Attribute 1
                        0x02, Result::FAIL_RO_ATTR, // Attribute 2
                        0x06, Result::FAIL_SUPPORT, // Attribute 3
                        0x00, 0x00, 0x00}
                      );

   SetAttributePack::Response response;

   response.unpack (expected, 3);

   LONGS_EQUAL (3, response.results.size ());

   SetAttributePack::Response::Result result;

   result = response.results[0];

   LONGS_EQUAL (0x01, result.uid);
   LONGS_EQUAL (Result::OK, result.code);

   result = response.results[1];

   LONGS_EQUAL (0x02, result.uid);
   LONGS_EQUAL (Result::FAIL_RO_ATTR, result.code);

   result = response.results[2];

   LONGS_EQUAL (0x06, result.uid);
   LONGS_EQUAL (Result::FAIL_SUPPORT, result.code);
}

// =============================================================================
// Filters
// =============================================================================

/* === ResponseRequired === */

TEST_GROUP (ResponseRequired)
{
   struct FilterTest:public HF::Protocol::Filters::ResponseRequired
   {

      void clear ()
      {
         db.clear ();
      }
   };

   FilterTest filter;
   Testing::Link link;

   Packet packet;

   TEST_SETUP ()
   {
      filter.clear ();
      packet.link = &link;

      std::random_device rd;
      std::mt19937 gen (rd ());
      std::uniform_int_distribution <uint16_t> dist1 (0, 0x7FFF);
      std::uniform_int_distribution <uint8_t>  dist2 (0, 0xFF);

      auto g_id   = std::bind (dist1, gen);
      auto g_unit = std::bind (dist2, gen);

      packet.message.itf.id     = g_id ();
      packet.message.itf.member = g_unit ();

      packet.source.device      = g_id ();
      packet.source.unit        = g_unit ();

      packet.destination.device = g_id ();
      packet.destination.unit   = g_unit ();
   }
};

TEST (ResponseRequired, ShouldNotAddCommands)
{
   LONGS_EQUAL (0, filter.size ());

   std::vector <Protocol::Message::Type> types {
      Protocol::Message::COMMAND_REQ,
      Protocol::Message::COMMAND_RESP_REQ,
      Protocol::Message::GET_ATTR_REQ,
      Protocol::Message::SET_ATTR_REQ,
      Protocol::Message::SET_ATTR_RESP_REQ,
      Protocol::Message::GET_ATTR_PACK_REQ,
      Protocol::Message::SET_ATTR_PACK_REQ,
      Protocol::Message::SET_ATTR_PACK_RESP_REQ,
      Protocol::Message::ATOMIC_SET_ATTR_PACK_REQ,
      Protocol::Message::ATOMIC_SET_ATTR_PACK_RESP_REQ,
   };

   /* *INDENT-OFF* */
   std::for_each (types.begin (), types.end (), [this](Protocol::Message::Type type)
   {
      packet.message.type = type;
      filter (packet);
   });
   /* *INDENT-ON* */

   LONGS_EQUAL (0, filter.size ());
}

TEST (ResponseRequired, ShouldAddResponses)
{
   LONGS_EQUAL (0, filter.size ());

   std::vector <Protocol::Message::Type> types {
      Protocol::Message::COMMAND_RES,
      Protocol::Message::SET_ATTR_RES,
      Protocol::Message::GET_ATTR_RES,
      Protocol::Message::GET_ATTR_PACK_RES,
      Protocol::Message::SET_ATTR_PACK_RES,
      Protocol::Message::ATOMIC_SET_ATTR_PACK_RES,
   };

   /* *INDENT-OFF* */
   std::for_each (types.begin (), types.end (), [this](Protocol::Message::Type type)
   {
      packet.message.type = type;
      filter (packet);
   });
   /* *INDENT-ON* */

   LONGS_EQUAL (types.size (), filter.size ());
}

TEST (ResponseRequired, NoResponse)
{
   LONGS_EQUAL (0, filter.size ());

   packet.message.type = Protocol::Message::COMMAND_RES;

   filter (packet);

   packet.message.type = Protocol::Message::COMMAND_RESP_REQ;
   std::swap(packet.source, packet.destination);

   CHECK_FALSE (filter (packet));

   LONGS_EQUAL (0, filter.size ());
}

/*!
 * Regression test.
 *
 * Registration response message destination address does not match the
 * incoming packet source address.
 */
TEST (ResponseRequired, NoResponse2)
{
   LONGS_EQUAL (0, filter.size ());

   packet.message.type = Protocol::Message::COMMAND_RES;

   filter (packet);

   packet.message.type = Protocol::Message::COMMAND_RESP_REQ;
   std::swap(packet.source, packet.destination);

   link.address(packet.source.device);

   packet.source.device = HF::Protocol::BROADCAST_ADDR;
   packet.source.unit = HF::Protocol::BROADCAST_UNIT;

   CHECK_FALSE (filter (packet));

   LONGS_EQUAL (0, filter.size ());
}

TEST (ResponseRequired, ResponseNeeded)
{
   LONGS_EQUAL (0, filter.size ());

   packet.message.type = Protocol::Message::SET_ATTR_PACK_RES;

   filter (packet);

   packet.message.type = Protocol::Message::COMMAND_RESP_REQ;
   std::swap (packet.source, packet.destination);

   CHECK_TRUE (filter (packet));

   LONGS_EQUAL (1, filter.size ());
}
