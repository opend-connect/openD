// =============================================================================
/*!
 * @file       tests/test_interfaces.cpp
 *
 * This file contains the implementation of the tests for the common functionality
 * of the interfaces.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================

#include "hanfun/interface.h"
#include "hanfun/attributes.h"

#include "test_helper.h"

using namespace HF;
using namespace HF::Testing;
using namespace HF::Common;

// =============================================================================
// AbstractInterface
// =============================================================================

//! AbstractInterface test group.
TEST_GROUP (AbstractInterface)
{
   TestInterface *itf;
   Protocol::Packet packet;
   ByteArray payload;

   TEST_SETUP ()
   {
      itf                     = new TestInterface (HF::Interface::SERVER_ROLE, 0x5AA5);

      packet.message.itf.id   = itf->uid ();
      packet.message.itf.role = itf->role ();

      mock ().ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      delete itf;

      mock ().clear ();
   }
};

/*!
 * @test Should handle request message coming from the same interface and
 *       from the same role.
 */
TEST (AbstractInterface, Handle_Request)
{
   packet.message.type = Message::COMMAND_REQ;

   CHECK_EQUAL (Result::OK, itf->handle (packet, payload, 0));

   itf->_role = HF::Interface::CLIENT_ROLE;

   CHECK_EQUAL (Result::FAIL_SUPPORT, itf->handle (packet, payload, 0));

   packet.message.itf.role = HF::Interface::SERVER_ROLE;
   packet.message.itf.id   = 0x7AAA;

   CHECK_EQUAL (Result::FAIL_ARG, itf->handle (packet, payload, 0));
}

/*!
 * @test Should handle request message coming from the same interface and
 *       from the same role.
 */
TEST (AbstractInterface, Handle_RequestResp)
{
   packet.message.type = Message::COMMAND_RESP_REQ;

   CHECK_EQUAL (Result::OK, itf->handle (packet, payload, 0));

   itf->_role = HF::Interface::CLIENT_ROLE;

   CHECK_EQUAL (Result::FAIL_SUPPORT, itf->handle (packet, payload, 0));

   packet.message.itf.role = HF::Interface::SERVER_ROLE;
   packet.message.itf.id   = 0x7AAA;

   CHECK_EQUAL (Result::FAIL_ARG, itf->handle (packet, payload, 0));
}

// =============================================================================
// AbstractInterface::Attributes
// =============================================================================

// =============================================================================
// AbstractInterface::GetAttribute
// =============================================================================

//! @test Should handle valid get attribute requests.
TEST (AbstractInterface, Handle_GetAttribute_Valid)
{
   packet.message.type       = Protocol::Message::GET_ATTR_REQ;
   packet.message.itf.member = TestInterface::ATTR1;

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 0);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (itf->_uid, itf->sendMsg.itf.id);
   LONGS_EQUAL (itf->_role, itf->sendMsg.itf.role);
   LONGS_EQUAL (TestInterface::ATTR1, itf->sendMsg.itf.member);

   HF::Attributes::Response attr_res (itf->attribute (TestInterface::ATTR1));

   attr_res.unpack (itf->sendMsg.payload);

   CHECK_EQUAL (Result::OK, attr_res.code);

   CHECK_TRUE (attr_res.attribute != nullptr);

   CHECK_FALSE (attr_res.attribute->isWritable ());

   LONGS_EQUAL (TestInterface::ATTR1, attr_res.attribute->uid ());

   LONGS_EQUAL (itf->uid (), attr_res.attribute->interface ());
}

//! @test Should handle invalid get attribute requests.
TEST (AbstractInterface, Handle_GetAttribute_Invalid)
{
   packet.message.type       = Protocol::Message::GET_ATTR_REQ;
   packet.message.itf.member = TestInterface::ATTR3 + 4;

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 0);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (itf->_uid, itf->sendMsg.itf.id);
   LONGS_EQUAL (itf->_role, itf->sendMsg.itf.role);
   LONGS_EQUAL (packet.message.itf.member, itf->sendMsg.itf.member);

   HF::Attributes::Response attr_res;
   attr_res.unpack (itf->sendMsg.payload);

   CHECK_EQUAL (Result::FAIL_SUPPORT, attr_res.code);

   CHECK_TRUE (attr_res.attribute == nullptr);
}

// =============================================================================
// AbstractInterface::SetAttribute
// =============================================================================
//! @test Should handle valid set attribute requests.
TEST (AbstractInterface, Handle_SetAttribute_Valid)
{
   packet.message.type       = Protocol::Message::SET_ATTR_REQ;
   packet.message.itf.member = TestInterface::ATTR3;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x5A, 0xAA,  // Attribute value.
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A53, itf->attr3);

   mock ("Interface").expectNCalls (0, "send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5AAA, itf->attr3);
}

//! @test Should handle invalid set attribute requests.
TEST (AbstractInterface, Handle_SetAttribute_Invalid)
{
   packet.message.type       = Protocol::Message::SET_ATTR_REQ;
   packet.message.itf.member = TestInterface::ATTR3 + 4;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x5A, 0xAA,  // Attribute value.
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A51, itf->attr1);

   mock ("Interface").expectNCalls (0, "send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::FAIL_SUPPORT, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5A51, itf->attr1);
}

//! @test Should handle invalid set attribute requests.
TEST (AbstractInterface, Handle_SetAttribute_ReadOnly)
{
   packet.message.type       = Protocol::Message::SET_ATTR_REQ;
   packet.message.itf.member = TestInterface::ATTR1;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x5A, 0xAA,  // Attribute value.
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A51, itf->attr1);

   mock ("Interface").expectNCalls (0, "send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::FAIL_RO_ATTR, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5A51, itf->attr1);
}

//! @test Should handle valid set response required attribute requests.
TEST (AbstractInterface, Handle_SetAttributeResponse_Valid)
{
   packet.message.type       = Protocol::Message::SET_ATTR_RESP_REQ;
   packet.message.itf.member = TestInterface::ATTR3;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x5A, 0xAA,  // Attribute value.
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A53, itf->attr3);

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5AAA, itf->attr3);
}

//! @test Should handle invalid set response required attribute requests.
TEST (AbstractInterface, Handle_SetAttributeResponse_Invalid)
{
   packet.message.type       = Protocol::Message::SET_ATTR_RESP_REQ;
   packet.message.itf.member = TestInterface::ATTR3 + 4;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x5A, 0xAA,  // Attribute value.
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A51, itf->attr1);

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (itf->_uid, itf->sendMsg.itf.id);
   LONGS_EQUAL (itf->_role, itf->sendMsg.itf.role);
   LONGS_EQUAL (packet.message.itf.member, itf->sendMsg.itf.member);

   Response res;
   res.unpack (itf->sendMsg.payload);

   CHECK_EQUAL (Result::FAIL_SUPPORT, res.code);

   LONGS_EQUAL (0x5A51, itf->attr1);
}

//! @test Should handle invalid set response required attribute requests.
TEST (AbstractInterface, Handle_SetAttributeResponse_ReadOnly)
{
   packet.message.type       = Protocol::Message::SET_ATTR_RESP_REQ;
   packet.message.itf.member = TestInterface::ATTR1;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x5A, 0xAA,  // Attribute value.
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A51, itf->attr1);

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (itf->_uid, itf->sendMsg.itf.id);
   LONGS_EQUAL (itf->_role, itf->sendMsg.itf.role);
   LONGS_EQUAL (packet.message.itf.member, itf->sendMsg.itf.member);

   Response res;
   res.unpack (itf->sendMsg.payload);

   CHECK_EQUAL (Result::FAIL_RO_ATTR, res.code);

   LONGS_EQUAL (0x5A51, itf->attr1);
}

// =============================================================================
// AbstractInterface::GetHF::Attributes::Pack
// =============================================================================

//! @test Should handle valid get attribute pack requests for mandatory attributes.
TEST (AbstractInterface, Handle_GetAttributesPack_Mandatory)
{
   packet.message.type       = Protocol::Message::GET_ATTR_PACK_REQ;
   packet.message.itf.member = HF::Attributes::Pack::MANDATORY;

   payload                   = ByteArray {0x00, 0x00, 0x00};

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (itf->_uid, itf->sendMsg.itf.id);
   LONGS_EQUAL (itf->_role, itf->sendMsg.itf.role);

   GetAttributePack::Response attr_resp;
   attr_resp.attribute_factory = &(TestInterface::create_attribute);
   attr_resp.unpack (itf->sendMsg.payload);

   CHECK_EQUAL (Result::OK, attr_resp.code);

   LONGS_EQUAL (1, attr_resp.attributes.size ());

   HF::Attributes::IAttribute *attr = attr_resp.attributes[TestInterface::ATTR1];

   CHECK_TRUE (attr == nullptr);

   attr = attr_resp.attributes[TestInterface::ATTR2];

   CHECK_TRUE (attr == nullptr);

   attr = attr_resp.attributes[TestInterface::ATTR3];

   CHECK_TRUE (attr != nullptr);
}

//! @test Should handle valid get attribute pack requests for all attributes.
TEST (AbstractInterface, Handle_GeAttributesPack_All)
{
   packet.message.type       = Protocol::Message::GET_ATTR_PACK_REQ;
   packet.message.itf.member = HF::Attributes::Pack::ALL;

   payload                   = ByteArray {0x00, 0x00, 0x00};

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (itf->_uid, itf->sendMsg.itf.id);
   LONGS_EQUAL (itf->_role, itf->sendMsg.itf.role);

   GetAttributePack::Response attr_resp;
   attr_resp.attribute_factory = &(TestInterface::create_attribute);
   attr_resp.unpack (itf->sendMsg.payload);

   CHECK_EQUAL (Result::OK, attr_resp.code);

   LONGS_EQUAL (3, attr_resp.attributes.size ());

   HF::Attributes::IAttribute *attr = attr_resp.attributes[TestInterface::ATTR1];

   CHECK_TRUE (attr != nullptr);

   attr = attr_resp.attributes[TestInterface::ATTR2];

   CHECK_TRUE (attr != nullptr);

   attr = attr_resp.attributes[TestInterface::ATTR3];

   CHECK_TRUE (attr != nullptr);
}

//! @test Should handle valid get attribute pack requests.
TEST (AbstractInterface, Handle_GetAttributesPack_Valid)
{
   packet.message.type       = Protocol::Message::GET_ATTR_PACK_REQ;
   packet.message.itf.member = HF::Attributes::Pack::DYNAMIC;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x02,  // Number of attribute uid's.
                                                 // Attribute uid's.
                                          0x01, 0x03,
                                          0x00, 0x00, 0x00};

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (itf->_uid, itf->sendMsg.itf.id);
   LONGS_EQUAL (itf->_role, itf->sendMsg.itf.role);

   GetAttributePack::Response attr_resp;
   attr_resp.attribute_factory = &(TestInterface::create_attribute);
   attr_resp.unpack (itf->sendMsg.payload);

   CHECK_EQUAL (Result::OK, attr_resp.code);

   LONGS_EQUAL (2, attr_resp.attributes.size ());

   HF::Attributes::IAttribute *attr = attr_resp.attributes[TestInterface::ATTR1];

   CHECK_TRUE (attr != nullptr);

   attr = attr_resp.attributes[TestInterface::ATTR2];

   CHECK_TRUE (attr == nullptr);

   attr = attr_resp.attributes[TestInterface::ATTR3];

   CHECK_TRUE (attr != nullptr);
}

//! @test Should handle invalid get attribute requests.
TEST (AbstractInterface, Handle_GetAttributePack_Invalid)
{
   packet.message.type       = Protocol::Message::GET_ATTR_PACK_REQ;
   packet.message.itf.member = HF::Attributes::Pack::DYNAMIC;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x03,  // Number of attribute uid's.
                                                 // Attribute uid's.
                                          0x01, 0x03, 0x04,
                                          0x00, 0x00, 0x00};

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::FAIL_SUPPORT, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (itf->_uid, itf->sendMsg.itf.id);
   LONGS_EQUAL (itf->_role, itf->sendMsg.itf.role);

   LONGS_EQUAL (Message::GET_ATTR_PACK_RES, itf->sendMsg.type);

   GetAttributePack::Response attr_resp;
   attr_resp.attribute_factory = &(TestInterface::create_attribute);
   attr_resp.unpack (itf->sendMsg.payload);

   CHECK_EQUAL (Result::FAIL_SUPPORT, attr_resp.code);

   LONGS_EQUAL (2, attr_resp.attributes.size ());

   HF::Attributes::IAttribute *attr = attr_resp.attributes[TestInterface::ATTR1];

   CHECK_TRUE (attr != nullptr);

   attr = attr_resp.attributes[TestInterface::ATTR2];

   CHECK_TRUE (attr == nullptr);

   attr = attr_resp.attributes[TestInterface::ATTR3];

   CHECK_TRUE (attr != nullptr);
}

// =============================================================================
// AbstractInterface::SetAttributePack
// =============================================================================

//! @test Should handle set attribute pack requests.
TEST (AbstractInterface, Handle_SetAttributePack)
{
   packet.message.type       = Protocol::Message::SET_ATTR_PACK_REQ;
   packet.message.itf.member = 0;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x04,              // Number of attributes
                                          0x01, 0xAA, 0xAA,  // Attribute 1 - Valid/RO
                                          0x02, 0xBB, 0xBB,  // Attribute 2 - Valid/RO
                                          0x03, 0xCC, 0xCC,  // Attribute 3 - Valid/RW
                                          0x04, 0xDD, 0xDD,  // Attribute 4 - Invalid
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A51, itf->attr1);
   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0x5A53, itf->attr3);

   mock ("Interface").expectNCalls (0, "send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5A51, itf->attr1);
   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0xCCCC, itf->attr3);
}

//! @test Should handle valid set response pack response required attribute requests.
TEST (AbstractInterface, Handle_SetAttributePackResponse)
{
   packet.message.type       = Protocol::Message::SET_ATTR_PACK_RESP_REQ;
   packet.message.itf.member = 0;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x04,              // Number of attributes
                                          0x01, 0xAA, 0xAA,  // Attribute 1 - Valid/RO
                                          0x02, 0xBB, 0xBB,  // Attribute 2 - Valid/RO
                                          0x03, 0xCC, 0xCC,  // Attribute 3 - Valid/RW
                                          0x04, 0xDD, 0xDD,  // Attribute 4 - Invalid
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A51, itf->attr1);
   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0x5A53, itf->attr3);

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5A51, itf->attr1);
   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0xCCCC, itf->attr3);

   SetAttributePack::Response response;
   response.unpack (itf->sendMsg.payload);

   LONGS_EQUAL (4, response.results.size ());

   LONGS_EQUAL (TestInterface::ATTR1, response.results[0].uid);
   LONGS_EQUAL (Result::FAIL_RO_ATTR, response.results[0].code);

   LONGS_EQUAL (TestInterface::ATTR2, response.results[1].uid);
   LONGS_EQUAL (Result::FAIL_RO_ATTR, response.results[1].code);

   LONGS_EQUAL (TestInterface::ATTR3, response.results[2].uid);
   LONGS_EQUAL (Result::OK, response.results[2].code);

   LONGS_EQUAL (0x04, response.results[3].uid);
   LONGS_EQUAL (Result::FAIL_SUPPORT, response.results[3].code);
}

//! @test Should fast fail on set response pack requests.
TEST (AbstractInterface, Handle_SetAttributePack_FastFail)
{
   packet.message.type       = Protocol::Message::SET_ATTR_PACK_RESP_REQ;
   packet.message.itf.member = 0;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x04,              // Number of attributes
                                          0x01, 0xAA, 0xAA,  // Attribute 1 - Valid/RO
                                          0x04, 0xDD, 0xDD,  // Attribute 4 - Invalid
                                          0x02, 0xBB, 0xBB,  // Attribute 2 - Valid/RO
                                          0x03, 0xCC, 0xCC,  // Attribute 3 - Valid/RW
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A51, itf->attr1);
   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0x5A53, itf->attr3);

   mock ("Interface").expectOneCall ("send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5A51, itf->attr1);
   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0x5A53, itf->attr3);

   SetAttributePack::Response response;
   response.unpack (itf->sendMsg.payload);

   LONGS_EQUAL (2, response.results.size ());

   LONGS_EQUAL (TestInterface::ATTR1, response.results[0].uid);
   LONGS_EQUAL (Result::FAIL_RO_ATTR, response.results[0].code);

   LONGS_EQUAL (0x04, response.results[1].uid);
   LONGS_EQUAL (Result::FAIL_SUPPORT, response.results[1].code);
}

// =============================================================================
// AbstractInterface::AtomicSetAttributePack
// =============================================================================

//! @test Should handle atomic set attribute pack requests.
TEST (AbstractInterface, Handle_AtomicSetAttributePack)
{
   packet.message.type       = Protocol::Message::ATOMIC_SET_ATTR_PACK_REQ;
   packet.message.itf.member = 0;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x01,              // Number of attributes
                                          0x03, 0xCC, 0xCC,  // Attribute 3 - Valid/RW
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A53, itf->attr3);

   mock ("Interface").expectNCalls (0, "send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5A51, itf->attr1);
   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0xCCCC, itf->attr3);
}

//! @test Should handle atomic set attribute pack requests.
TEST (AbstractInterface, Handle_AtomicSetAttributePack_Fail)
{
   packet.message.type       = Protocol::Message::ATOMIC_SET_ATTR_PACK_REQ;
   packet.message.itf.member = 0;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x02,              // Number of attributes
                                          0x02, 0xBB, 0xBB,  // Attribute 2 - Valid/RO
                                          0x03, 0xCC, 0xCC,  // Attribute 3 - Valid/RW
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0x5A53, itf->attr3);

   mock ("Interface").expectNCalls (0, "send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0x5A53, itf->attr3);
}

//! @test Should handle atomic set attribute pack requests.
TEST (AbstractInterface, Handle_AtomicSetAttributePack_Fail2)
{
   packet.message.type       = Protocol::Message::ATOMIC_SET_ATTR_PACK_REQ;
   packet.message.itf.member = 0;

   payload                   = ByteArray {0x00, 0x00, 0x00,
                                          0x02,              // Number of attributes
                                          0x03, 0xBB, 0xBB,  // Attribute 2 - Valid/RW
                                          0x04, 0xCC, 0xCC,  // Attribute 4 - Invalid
                                          0x00, 0x00, 0x00};

   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0x5A53, itf->attr3);

   mock ("Interface").expectNCalls (0, "send");

   Result result = itf->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ().checkExpectations ();

   LONGS_EQUAL (0x5A52, itf->attr2);
   LONGS_EQUAL (0x5A53, itf->attr3);
}
