// =============================================================================
/*!
 * @file       tests/core/test_session_manager.cpp
 *
 * This file contains the implementation of the tests for the session management
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

#include "hanfun/core/session_management.h"

#include "test_helper.h"

// =============================================================================
// Tests
// =============================================================================

using namespace HF;
using namespace HF::Common;
using namespace HF::Core::SessionManagement;

// =============================================================================
// Session Management Messages
// =============================================================================

TEST_GROUP (SessionManagement)
{};

TEST (SessionManagement, StartResponse)
{
   StartResponse resp;

   LONGS_EQUAL (1 + 2, resp.size ());

   ByteArray expected {0x00, 0x00, 0x00,
                       Result::FAIL_READ_SESSION,
                       0x12, 0x34,
                       0x00, 0x00, 0x00};

   resp.code  = Result::FAIL_READ_SESSION;
   resp.count = 0x1234;

   ByteArray payload (expected.size ());

   resp.pack (payload, 3);

   CHECK_EQUAL (expected, payload);

   payload[3] = Result::FAIL_RESOURCES;
   payload[4] = 0x56;
   payload[5] = 0x78;

   resp.unpack (payload, 3);

   LONGS_EQUAL (Result::FAIL_RESOURCES, resp.code);
   LONGS_EQUAL (0x5678, resp.count);
}

TEST (SessionManagement, GetEntriesMessage)
{
   GetEntriesMessage msg;

   LONGS_EQUAL (2 + 1, msg.size ());

   ByteArray expected {0x00, 0x00, 0x00,
                       0x12, 0x34,
                       0x56,
                       0x00, 0x00, 0x00};

   msg.offset = 0x1234;
   msg.count  = 0x56;

   ByteArray payload (expected.size ());

   msg.pack (payload, 3);

   CHECK_EQUAL (expected, payload);

   payload[3] = 0x78;
   payload[4] = 0x9A;
   payload[5] = 0xBC;

   msg.unpack (payload, 3);

   LONGS_EQUAL (0x789A, msg.offset);
   LONGS_EQUAL (0xBC, msg.count);
}

TEST (SessionManagement, GetEntriesResponse)
{
   GetEntriesResponse < SerializableHelper < uint16_t >> resp;

   LONGS_EQUAL (1 + 1, resp.size ());

   resp.entries.push_back (SerializableHelper <uint16_t>(0x1234));

   LONGS_EQUAL (1 + 1 + 2, resp.size ());

   resp.entries.push_back (SerializableHelper <uint16_t>(0x5678));
   resp.entries.push_back (SerializableHelper <uint16_t>(0x9ABC));

   LONGS_EQUAL (1 + 1 + 3 * 2, resp.size ());

   Common::ByteArray expected {0x00, 0x00, 0x00,
                               Result::FAIL_AUTH,     // Status code.
                               0x03,                  // Number of entries.
                               0x12, 0x34,            // Entry 1
                               0x56, 0x78,            // Entry 2
                               0x9A, 0xBC,            // Entry 3
                               0x00, 0x00, 0x00};

   resp.code = Result::FAIL_AUTH;

   ByteArray payload (expected.size ());

   resp.pack (payload, 3);

   CHECK_EQUAL (expected, payload);

   payload[3] = Result::FAIL_RO_ATTR;
   payload[4] = 2;
   payload[5] = 0xCB;
   payload[6] = 0xA9;
   payload[7] = 0x87;
   payload[8] = 0x65;

   resp.unpack (payload, 3);

   LONGS_EQUAL (Result::FAIL_RO_ATTR, resp.code);
   LONGS_EQUAL (2, resp.entries.size ());

   LONGS_EQUAL (0xCBA9, resp.entries[0].data);
   LONGS_EQUAL (0x8765, resp.entries[1].data);
}

// =============================================================================
// Session Management Server
// =============================================================================

TEST_GROUP (SessionManagementServer)
{
   typedef Common::SerializableHelper <uint16_t> TestType;
   typedef std::vector <TestType> TestContainer;

   struct TestEntries:public Common::IEntries <TestType>, public TestContainer
   {
      uint16_t size () const
      {
         return TestContainer::size ();
      }

      Common::Result save (const TestType &value)
      {
         push_back (value);
         return Result::OK;
      }

      Common::Result destroy (const TestType &value)
      {
         /* *INDENT-OFF* */
         auto it = std::find_if(begin(), end(), [value](TestType &entry)
                                 { return entry.data == value.data; });
         /* *INDENT-ON* */

         if (it != end ())
         {
            this->erase (it);
            return Result::OK;
         }

         return Result::FAIL_ARG;
      }

      Common::Result save (uint16_t value)
      {
         push_back (TestType (value));
         return Result::OK;
      }

      Common::Result destroy (uint16_t value)
      {
         /* *INDENT-OFF* */
         auto it = std::find_if(begin(), end(), [value](TestType &entry)
                                { return entry.data == value; });
         /* *INDENT-ON* */

         if (it != end ())
         {
            this->erase (it);
            return Result::OK;
         }

         return Result::FAIL_ARG;
      }
   };

   struct TestServer:public Server <TestEntries>
   {
      uint16_t count () const
      {
         return sessions.size ();
      }

      void send (const Protocol::Address &addr, Protocol::Message &message)
      {
         auto &call = mock ("SessionManagementServer").actualCall ("send");
         call.withParameter ("addr_dev", addr.device);
         call.withParameter ("addr_unit", addr.unit);

         mock ("SessionManagementServer").setData ("response",
                                                   new Protocol::Message (message));
      }

      using AbstractServer::check_offset;
      using AbstractServer::payload_size;
      using AbstractServer::handle_command;
      using AbstractServer::invalidate;
   };

   TestServer server;

   TEST_SETUP ()
   {
      mock ().ignoreOtherCalls ();

      for (uint16_t i = 1; i <= 20; i++)
      {
         server.entries ().save (i);
      }
   }

   TEST_TEARDOWN ()
   {
      mock ().clear ();
      server.entries ().clear ();
   }
};

TEST (SessionManagementServer, StartSession)
{
   server.start_session (0x1234);

   LONGS_EQUAL (1, server.count ());

   CHECK_TRUE (server.exists (0x1234));

   CHECK_TRUE (server.is_valid (0x1234));
}

TEST (SessionManagementServer, Invalidate)
{
   server.start_session (0x1234);

   CHECK_TRUE (server.exists (0x1234));

   CHECK_TRUE (server.is_valid (0x1234));

   server.invalidate ();

   CHECK_TRUE (server.exists (0x1234));

   CHECK_FALSE (server.is_valid (0x1234));
}

TEST (SessionManagementServer, EndSession)
{
   server.start_session (0x1234);

   CHECK_TRUE (server.exists (0x1234));

   CHECK_TRUE (server.is_valid (0x1234));

   server.end_session (0x1234);

   CHECK_FALSE (server.exists (0x1234));

   CHECK_FALSE (server.is_valid (0x1234));
}

TEST (SessionManagementServer, CheckOffset)
{
   uint8_t count = 3;

   LONGS_EQUAL (Result::FAIL_ARG, server.check_offset (5, count, 4));
   LONGS_EQUAL (Result::FAIL_ARG, server.check_offset (5, count, 5));

   LONGS_EQUAL (Result::OK, server.check_offset (1, count, 5));

   LONGS_EQUAL (Result::OK, server.check_offset (3, count, 5));

   LONGS_EQUAL (2, count);
}

TEST (SessionManagementServer, PayloadSize)
{
   LONGS_EQUAL (0, server.payload_size (START));
   LONGS_EQUAL (GetEntriesMessage ().size (), server.payload_size (GET));
   LONGS_EQUAL (0, server.payload_size (END));
}

TEST (SessionManagementServer, EntriesWrapper)
{
   LONGS_EQUAL (20, server.entries ().size ());

   server.start_session (0x1234);

   server.entries ().save (0x9876);

   LONGS_EQUAL (21, server.entries ().size ());
   CHECK_TRUE (server.exists (0x1234));
   CHECK_FALSE (server.is_valid (0x1234));

   server.start_session (0x1234);

   CHECK_TRUE (server.is_valid (0x1234));

   server.entries ().destroy (0x9876);

   LONGS_EQUAL (20, server.entries ().size ());
   CHECK_TRUE (server.exists (0x1234));
   CHECK_FALSE (server.is_valid (0x1234));
}

TEST (SessionManagementServer, HandleStart)
{
   Protocol::Packet packet;

   packet.source.device = 0x5AA5;
   packet.source.unit   = 0x33;

   Common::ByteArray payload;

   auto &call = mock ("SessionManagementServer").expectOneCall ("send");
   call.withParameter ("addr_dev", packet.source.device);
   call.withParameter ("addr_unit", packet.source.unit);

   LONGS_EQUAL (Result::OK, server.handle_command (START, packet, payload));

   mock ("SessionManagementServer").checkExpectations ();

   CHECK_TRUE (server.exists (packet.source.device));
   CHECK_TRUE (server.is_valid (packet.source.device));

   auto res     = mock ("SessionManagementServer").getData ("response").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   StartResponse resp;
   resp.unpack (message->payload);

   LONGS_EQUAL (Result::OK, resp.code);
   LONGS_EQUAL (server.entries ().size (), resp.count);

   delete message;
}

TEST (SessionManagementServer, HandleEnd)
{
   server.start_session (0x5AA5);

   Protocol::Packet packet;

   packet.source.device = 0x5AA5;
   packet.source.unit   = 0x33;

   Common::ByteArray payload;

   auto &call = mock ("SessionManagementServer").expectOneCall ("send");
   call.withParameter ("addr_dev", packet.source.device);
   call.withParameter ("addr_unit", packet.source.unit);

   LONGS_EQUAL (Result::OK, server.handle_command (END, packet, payload));

   mock ("SessionManagementServer").checkExpectations ();

   CHECK_FALSE (server.is_valid (packet.source.device));
   CHECK_FALSE (server.exists (packet.source.device));

   auto res     = mock ("SessionManagementServer").getData ("response").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   Protocol::Response resp;
   resp.unpack (message->payload);

   LONGS_EQUAL (Result::OK, resp.code);

   delete message;
}

TEST (SessionManagementServer, HandleGet_NoSession)
{
   Protocol::Packet packet;

   packet.source.device = 0x5AA5;
   packet.source.unit   = 0x33;

   Common::ByteArray payload;

   auto &call = mock ("SessionManagementServer").expectOneCall ("send");
   call.withParameter ("addr_dev", packet.source.device);
   call.withParameter ("addr_unit", packet.source.unit);

   LONGS_EQUAL (Result::FAIL_READ_SESSION, server.handle_command (GET, packet, payload));

   mock ("SessionManagementServer").checkExpectations ();

   CHECK_FALSE (server.is_valid (packet.source.device));
   CHECK_FALSE (server.exists (packet.source.device));

   auto res     = mock ("SessionManagementServer").getData ("response").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   Protocol::Response resp;
   resp.unpack (message->payload);

   LONGS_EQUAL (Result::FAIL_READ_SESSION, resp.code);

   delete message;
}

TEST (SessionManagementServer, HandleGet_DataChanged)
{
   server.start_session (0x5AA5);
   server.invalidate ();

   Protocol::Packet packet;

   packet.source.device = 0x5AA5;
   packet.source.unit   = 0x33;

   Common::ByteArray payload;

   auto &call = mock ("SessionManagementServer").expectOneCall ("send");
   call.withParameter ("addr_dev", packet.source.device);
   call.withParameter ("addr_unit", packet.source.unit);

   LONGS_EQUAL (Result::FAIL_MODIFIED, server.handle_command (GET, packet, payload));

   mock ("SessionManagementServer").checkExpectations ();

   CHECK_FALSE (server.is_valid (packet.source.device));
   CHECK_TRUE (server.exists (packet.source.device));

   auto res     = mock ("SessionManagementServer").getData ("response").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   Protocol::Response resp;
   resp.unpack (message->payload);

   LONGS_EQUAL (Result::FAIL_MODIFIED, resp.code);

   delete message;
}

TEST (SessionManagementServer, HandleGet_OutOfBounds)
{
   server.start_session (0x5AA5);

   Protocol::Packet packet;

   packet.source.device = 0x5AA5;
   packet.source.unit   = 0x33;

   GetEntriesMessage msg;
   msg.offset = 30;
   msg.count  = 5;

   Common::ByteArray payload = Common::ByteArray (msg.size ());
   msg.pack (payload);

   auto &call = mock ("SessionManagementServer").expectOneCall ("send");
   call.withParameter ("addr_dev", packet.source.device);
   call.withParameter ("addr_unit", packet.source.unit);

   LONGS_EQUAL (Result::FAIL_ARG, server.handle_command (GET, packet, payload));

   mock ("SessionManagementServer").checkExpectations ();

   auto res     = mock ("SessionManagementServer").getData ("response").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   GetEntriesEmptyResponse resp;
   resp.unpack (message->payload);

   LONGS_EQUAL (Result::FAIL_ARG, resp.code);

   delete message;
}

TEST (SessionManagementServer, HandleGet_OutOfBounds2)
{
   server.start_session (0x5AA5);

   Protocol::Packet packet;

   packet.source.device = 0x5AA5;
   packet.source.unit   = 0x33;

   GetEntriesMessage msg;
   msg.offset = 15;
   msg.count  = 10;

   Common::ByteArray payload = Common::ByteArray (msg.size ());
   msg.pack (payload);

   auto &call = mock ("SessionManagementServer").expectOneCall ("send");
   call.withParameter ("addr_dev", packet.source.device);
   call.withParameter ("addr_unit", packet.source.unit);

   LONGS_EQUAL (Result::OK, server.handle_command (GET, packet, payload));

   mock ("SessionManagementServer").checkExpectations ();

   auto res     = mock ("SessionManagementServer").getData ("response").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   GetEntriesResponse <TestType> resp;
   resp.unpack (message->payload);

   LONGS_EQUAL (Result::OK, resp.code);
   LONGS_EQUAL (5, resp.entries.size ());

   delete message;
}

TEST (SessionManagementServer, HandleGet_Ok)
{
   server.start_session (0x5AA5);

   Protocol::Packet packet;

   packet.source.device = 0x5AA5;
   packet.source.unit   = 0x33;

   GetEntriesMessage msg;
   msg.offset = 5;
   msg.count  = 10;

   Common::ByteArray payload = Common::ByteArray (msg.size ());
   msg.pack (payload);

   auto &call = mock ("SessionManagementServer").expectOneCall ("send");
   call.withParameter ("addr_dev", packet.source.device);
   call.withParameter ("addr_unit", packet.source.unit);

   LONGS_EQUAL (Result::OK, server.handle_command (GET, packet, payload));

   mock ("SessionManagementServer").checkExpectations ();

   auto res     = mock ("SessionManagementServer").getData ("response").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   GetEntriesResponse <TestType> resp;
   resp.unpack (message->payload);

   LONGS_EQUAL (Result::OK, resp.code);
   LONGS_EQUAL (10, resp.entries.size ());

   delete message;
}

// =============================================================================
// Session Management Client
// =============================================================================

TEST_GROUP (SessionManagementClient)
{
   typedef Common::SerializableHelper <uint16_t> TestType;

   struct TestClient:public Client <TestType>
   {
      void send (const Protocol::Address &addr, Protocol::Message &message)
      {
         auto &call = mock ("SessionManagementClient").actualCall ("send");
         call.withParameter ("addr_dev", addr.device);
         call.withParameter ("addr_unit", addr.unit);

         mock ("SessionManagementClient").setData ("message", new Protocol::Message (message));
      }

      using Client <TestType>::handle_command;

      void start_session () const
      {
         Client <TestType>::request <HF::Interface::SERVER_ROLE, 0x1234, 0x91>();
      }

      void get_entries (uint16_t offset, uint8_t count = 0) const
      {
         Client <TestType>::get_entries <HF::Interface::SERVER_ROLE, 0x1234, 0x92>(offset,
                                                                                   count);
      }

      void end_session () const
      {
         Client <TestType>::request <HF::Interface::SERVER_ROLE, 0x1234, 0x93>();
      }

      void entries (const GetEntriesResponse <TestType> &response)
      {
         auto &call = mock ("SessionManagementClient").actualCall ("entries");
         call.withParameter ("code", response.code);
         call.withParameter ("size", response.entries.size ());
      }

      void session_started (StartResponse &response)
      {
         auto &call = mock ("SessionManagementClient").actualCall ("session_started");
         call.withParameter ("code", response.code);
         call.withParameter ("count", response.count);
      }

      void session_ended (Protocol::Response &response)
      {
         auto &call = mock ("SessionManagementClient").actualCall ("session_ended");
         call.withParameter ("code", response.code);
      }
   };

   TestClient client;

   TEST_SETUP ()
   {
      mock ().ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      mock ().clear ();
   }
};

TEST (SessionManagementClient, Start)
{
   auto &call = mock ("SessionManagementClient").expectOneCall ("send");
   call.withParameter ("addr_dev", 0);
   call.withParameter ("addr_unit", 0);

   client.start_session ();

   mock ("SessionManagementClient").checkExpectations ();

   auto res     = mock ("SessionManagementClient").getData ("message").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   LONGS_EQUAL (0x1234, message->itf.id);
   LONGS_EQUAL (0x91, message->itf.member);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, message->itf.role);

   delete message;
}

TEST (SessionManagementClient, Get)
{
   auto &call = mock ("SessionManagementClient").expectOneCall ("send");
   call.withParameter ("addr_dev", 0);
   call.withParameter ("addr_unit", 0);

   client.get_entries (0x1234, 0x56);

   mock ("SessionManagementClient").checkExpectations ();

   auto res     = mock ("SessionManagementClient").getData ("message").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   LONGS_EQUAL (0x1234, message->itf.id);
   LONGS_EQUAL (0x92, message->itf.member);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, message->itf.role);

   GetEntriesMessage req;
   req.unpack (message->payload);

   LONGS_EQUAL (0x1234, req.offset);
   LONGS_EQUAL (0x56, req.count);

   delete message;
}

TEST (SessionManagementClient, End)
{
   auto &call = mock ("SessionManagementClient").expectOneCall ("send");
   call.withParameter ("addr_dev", 0);
   call.withParameter ("addr_unit", 0);

   client.end_session ();

   mock ("SessionManagementClient").checkExpectations ();

   auto res     = mock ("SessionManagementClient").getData ("message").getObjectPointer ();

   auto message = static_cast <const Protocol::Message *>(res);

   LONGS_EQUAL (0x1234, message->itf.id);
   LONGS_EQUAL (0x93, message->itf.member);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, message->itf.role);

   delete message;
}

TEST (SessionManagementClient, Handle_Started)
{
   Protocol::Packet packet;

   packet.source.device = 0x0;
   packet.source.unit   = 0x0;

   StartResponse resp;
   resp.code  = Result::OK;
   resp.count = 0x55;

   Common::ByteArray payload = Common::ByteArray (resp.size ());
   resp.pack (payload);

   auto &call = mock ("SessionManagementClient").expectOneCall ("session_started");
   call.withParameter ("code", Result::OK);
   call.withParameter ("count", 0x55);

   LONGS_EQUAL (Result::OK, client.handle_command (START, packet, payload));

   mock ("SessionManagementClient").checkExpectations ();
}

TEST (SessionManagementClient, Handle_Entries)
{
   Protocol::Packet packet;

   packet.source.device = 0x0;
   packet.source.unit   = 0x0;

   GetEntriesResponse <TestType> resp;

   // FAIL - Session not established;

   resp.code = Result::FAIL_READ_SESSION;

   Common::ByteArray payload = Common::ByteArray (resp.size ());
   resp.pack (payload);

   auto &call_1 = mock ("SessionManagementClient").expectOneCall ("entries");
   call_1.withParameter ("code", Result::FAIL_READ_SESSION);
   call_1.withParameter ("size", 0);

   LONGS_EQUAL (Result::OK, client.handle_command (GET, packet, payload));

   mock ("SessionManagementClient").checkExpectations ();

   // FAIL - Entries modified.

   resp.code = Result::FAIL_MODIFIED;
   resp.pack (payload);

   auto &call_2 = mock ("SessionManagementClient").expectOneCall ("entries");
   call_2.withParameter ("code", Result::FAIL_MODIFIED);
   call_2.withParameter ("size", 0);

   LONGS_EQUAL (Result::OK, client.handle_command (GET, packet, payload));

   mock ("SessionManagementClient").checkExpectations ();

   // OK - Got some entries.

   resp.code = Result::OK;
   resp.entries.push_back (TestType (0x1234));
   resp.entries.push_back (TestType (0x5678));
   resp.entries.push_back (TestType (0x9ABC));

   payload = Common::ByteArray (resp.size ());
   resp.pack (payload);

   auto &call_3 = mock ("SessionManagementClient").expectOneCall ("entries");
   call_3.withParameter ("code", Result::OK);
   call_3.withParameter ("size", 3);

   LONGS_EQUAL (Result::OK, client.handle_command (GET, packet, payload));

   mock ("SessionManagementClient").checkExpectations ();
}

TEST (SessionManagementClient, Handle_End)
{
   Protocol::Packet packet;

   packet.source.device = 0x0;
   packet.source.unit   = 0x0;

   Protocol::Response resp;
   resp.code = Result::FAIL_ARG;

   Common::ByteArray payload = Common::ByteArray (resp.size ());
   resp.pack (payload);

   auto &call = mock ("SessionManagementClient").expectOneCall ("session_ended");
   call.withParameter ("code", Result::FAIL_ARG);

   LONGS_EQUAL (Result::OK, client.handle_command (END, packet, payload));

   mock ("SessionManagementClient").checkExpectations ();
}
