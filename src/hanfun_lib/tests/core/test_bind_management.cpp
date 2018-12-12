// =============================================================================
/*!
 * @file       tests/core/test_bind_management.cpp
 *
 * This file contains the implementation of the tests for Bind Management Interface.
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
#include "test_helper.h"

#include "hanfun/core/bind_management.h"

// =============================================================================
// Tests
// =============================================================================

using namespace HF::Common;
using namespace HF::Core;

TEST_GROUP (BindManagement)
{};

TEST (BindManagement, EntrySize)
{
   BindManagement::Entry entry;
   LONGS_EQUAL (8, entry.size ());
}

TEST (BindManagement, EntryPack)
{
   /* *INDENT-OFF* */
   Common::ByteArray expected { 0x00, 0x00, 0x00,
                                0xF5,
                                0xA5, 0xAA,          // Source Address.
                                0x83, 0x33,          // interface.
                                0xDA, 0x5A, 0xBB,    // Destination Address.
                                0x00, 0x00, 0x00
   };
   /* *INDENT-ON* */

   BindManagement::Entry entry;

   entry.source.device      = 0x75A5;
   entry.source.mod         = 1; // This MUST be ignored by the Application.
   entry.source.unit        = 0xAA;

   entry.destination.device = 0x5A5A;
   entry.destination.mod    = 1;
   entry.destination.unit   = 0xBB;

   entry.itf.role           = HF::Interface::SERVER_ROLE;
   entry.itf.id             = 0x0333;

   Common::ByteArray data (entry.size () + 6);

   uint16_t size = entry.pack (data, 3);

   LONGS_EQUAL (entry.size (), size);

   CHECK_EQUAL (expected, data);
}

TEST (BindManagement, EntryUnpack)
{
   /* *INDENT-OFF* */
   Common::ByteArray data { 0x00, 0x00, 0x00,
                            0xF5,
                            0xA5, 0xAA,          // Source Address.
                            0x83, 0x33,          // interface.
                            0xDA, 0x5A, 0xBB,    // Destination Address.
                            0x00, 0x00, 0x00 };
   /* *INDENT-ON* */

   BindManagement::Entry entry;

   uint16_t size = entry.unpack (data, 3);

   LONGS_EQUAL (entry.size (), size);

   LONGS_EQUAL (0x75A5, entry.source.device);
   LONGS_EQUAL (1, entry.source.mod);
   LONGS_EQUAL (0xAA, entry.source.unit);

   LONGS_EQUAL (0x5A5A, entry.destination.device);
   LONGS_EQUAL (1, entry.destination.mod);
   LONGS_EQUAL (0xBB, entry.destination.unit);

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, entry.itf.role);
   LONGS_EQUAL (0x0333, entry.itf.id);
}

TEST (BindManagement, EntryEqual)
{
   BindManagement::Entry lhs;
   BindManagement::Entry rhs;

   lhs.source.mod         = 0;
   lhs.source.device      = 0x5A5A;
   lhs.source.unit        = 0xAA;

   lhs.destination.mod    = 0;
   lhs.destination.device = 0x5A5A;
   lhs.destination.unit   = 0xAA;

   lhs.itf.role           = 1;
   lhs.itf.id             = 0x7AAA;

   memcpy (&rhs, &lhs, sizeof(lhs));

   CHECK_TRUE (lhs == rhs);
   CHECK_FALSE (lhs != rhs);

   ++rhs.source.device;

   CHECK_FALSE (lhs == rhs);
   CHECK_TRUE (lhs != rhs);
}

// =============================================================================
// BindManagement - Client
// =============================================================================

TEST_GROUP (BindManagementClient)
{
   struct TestBindManagementClient:public BindManagement::Client
   {
      TestBindManagementClient(HF::Core::Unit0 &unit):
         BindManagement::Client (unit)
      {}

      virtual ~TestBindManagementClient()
      {}

      void response (const BindManagement::CMD cmd, const Protocol::Response &response)
      {
         mock ("BindManagementClient").actualCall ("response").withParameter ("cmd", cmd).withParameter (
            "result", response.code);
         BindManagement::Client::response (cmd, response);
      }
   };

   Testing::Device *device;

   TestBindManagementClient *client;

   Protocol::Packet packet;

   TEST_SETUP ()
   {
      mock ().ignoreOtherCalls ();

      device                  = new Testing::Device ();
      client                  = new TestBindManagementClient (*device->unit0 ());

      packet                  = Protocol::Packet ();

      packet.message.type     = Protocol::Message::COMMAND_RES;
      packet.message.itf.role = HF::Interface::SERVER_ROLE;
      packet.message.itf.id   = HF::Interface::BIND_MANAGEMENT;
   }

   TEST_TEARDOWN ()
   {
      delete client;
      delete device;

      mock ().clear ();
   }
};

TEST (BindManagementClient, Add)
{
   Protocol::Address source;
   Protocol::Address destination;
   Common::Interface itf;

   source.device      = 0x1111;
   source.unit        = 0x22;

   destination.device = 0x3333;
   destination.unit   = 0x44;

   itf.id             = 0x5555;
   itf.role           = HF::Interface::SERVER_ROLE;

   mock ("AbstractDevice").expectOneCall ("send");

   client->add (source, destination, itf);

   mock ("AbstractDevice").checkExpectations ();

   LONGS_EQUAL (1, device->packets.size ());

   Protocol::Packet *packet = device->packets.back ();

   CHECK_TRUE (packet != nullptr);

   LONGS_EQUAL (0, packet->destination.device);
   LONGS_EQUAL (0, packet->destination.unit);
   LONGS_EQUAL (Protocol::Address::DEVICE, packet->destination.mod);

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, packet->message.itf.role);
   LONGS_EQUAL (client->uid (), packet->message.itf.id);
   LONGS_EQUAL (BindManagement::ADD_BIND_CMD, packet->message.itf.member);

   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, packet->message.type);

   BindManagement::Entry payload;

   payload.unpack (packet->message.payload);

   LONGS_EQUAL (source.device, payload.source.device);
   LONGS_EQUAL (source.unit, payload.source.unit);

   LONGS_EQUAL (destination.device, payload.destination.device);
   LONGS_EQUAL (destination.unit, payload.destination.unit);

   LONGS_EQUAL (itf.role, payload.itf.role);
   LONGS_EQUAL (itf.id, payload.itf.id);
}

TEST (BindManagementClient, Remove)
{
   Protocol::Address source;
   Protocol::Address destination;
   Common::Interface itf;

   source.device      = 0x1111;
   source.unit        = 0x22;

   destination.device = 0x3333;
   destination.unit   = 0x44;

   itf.id             = 0x5555;
   itf.role           = HF::Interface::SERVER_ROLE;

   mock ("AbstractDevice").expectOneCall ("send");

   client->remove (source, destination, itf);

   mock ("AbstractDevice").checkExpectations ();

   LONGS_EQUAL (1, device->packets.size ());

   Protocol::Packet *packet = device->packets.back ();

   CHECK_TRUE (packet != nullptr);

   LONGS_EQUAL (0, packet->destination.device);
   LONGS_EQUAL (0, packet->destination.unit);
   LONGS_EQUAL (Protocol::Address::DEVICE, packet->destination.mod);

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, packet->message.itf.role);
   LONGS_EQUAL (client->uid (), packet->message.itf.id);
   LONGS_EQUAL (BindManagement::REMOVE_BIND_CMD, packet->message.itf.member);

   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, packet->message.type);

   BindManagement::Entry payload;

   payload.unpack (packet->message.payload);

   LONGS_EQUAL (source.device, payload.source.device);
   LONGS_EQUAL (source.unit, payload.source.unit);

   LONGS_EQUAL (destination.device, payload.destination.device);
   LONGS_EQUAL (destination.unit, payload.destination.unit);

   LONGS_EQUAL (itf.role, payload.itf.role);
   LONGS_EQUAL (itf.id, payload.itf.id);
}

TEST (BindManagementClient, ResponseOK)
{
   ByteArray payload ({0x00, 0x00, 0x00,
                       Result::OK,  // Response Code.
                       0x00, 0x00, 0x00}
                     );

   packet.message.length     = payload.size ();
   packet.message.itf.member = BindManagement::ADD_BIND_CMD;

   mock ("BindManagementClient").expectOneCall ("response").withParameter (
      "cmd", BindManagement::ADD_BIND_CMD).withParameter ("result", Result::OK);

   Result result = client->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ("BindManagementClient").checkExpectations ();
}

TEST (BindManagementClient, ResponseFAIL)
{
   ByteArray payload ({0x00, 0x00, 0x00,
                       Result::FAIL_ARG,  // Response Code.
                       0x00, 0x00, 0x00}
                     );

   packet.message.length     = payload.size ();
   packet.message.itf.member = BindManagement::REMOVE_BIND_CMD;

   mock ("BindManagementClient").expectOneCall ("response").withParameter (
      "cmd", BindManagement::REMOVE_BIND_CMD).withParameter ("result", Result::FAIL_ARG);

   Result result = client->handle (packet, payload, 3);
   CHECK_EQUAL (Result::OK, result);

   mock ("BindManagementClient").checkExpectations ();
}

// =============================================================================
// BindManagement - Entries
// =============================================================================

TEST_GROUP (BindManagementEntries)
{
   BindManagement::Entries entries;

   Protocol::Address src;
   Protocol::Address dst;

   Common::Interface itf;

   TEST_SETUP ()
   {
      src.device = 1;
      src.unit   = 1;
      src.mod    = 0;

      dst.device = 11;
      dst.unit   = 11;
      dst.mod    = 0;

      itf.id     = 0x5A5A;
   }

   void should_create (Protocol::Address src, Protocol::Address dst, Common::Interface itf,
                       const char *file, int line)
   {
      uint16_t size = entries.size ();

      auto res      = entries.save (BindManagement::Entry (src, itf, dst));

      LONGS_EQUAL_LOCATION (size + 1, entries.size (), file, line);
      size = entries.size ();

      LONGS_EQUAL_LOCATION (Common::Result::OK, res, file, line);
   }

   void should_not_create (Protocol::Address src, Protocol::Address dst, Common::Interface itf,
                           const char *file, int line)
   {
      uint16_t size = entries.size ();

      auto res      = entries.save (BindManagement::Entry (src, itf, dst));

      LONGS_EQUAL_LOCATION (size, entries.size (), file, line);
      LONGS_EQUAL_LOCATION (Common::Result::FAIL_ARG, res, file, line);
   }

};

#define SHOULD_CREATE(src, dst, itf) \
   should_create (src, dst, itf, __FILE__, __LINE__)

#define SHOULD_NOT_CREATE(src, dst, itf) \
   should_not_create (src, dst, itf, __FILE__, __LINE__)

TEST (BindManagementEntries, Initialization)
{
   // Should be empty.
   LONGS_EQUAL (0, entries.size ());
}

TEST (BindManagementEntries, CreateEqual)
{
   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   // Should NOT create a entry with the same parameters.
   SHOULD_NOT_CREATE (src, dst, itf);
}

TEST (BindManagementEntries, CreateSrcChange)
{
   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   // Should create a new entry - Changing source address.
   src.device++;
   SHOULD_CREATE (src, dst, itf);

   src.mod++;
   SHOULD_CREATE (src, dst, itf);

   src.unit++;
   SHOULD_CREATE (src, dst, itf);
}

TEST (BindManagementEntries, CreateItfChange)
{
   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   // Should create a new entry - Changing source address.
   itf.id++;
   SHOULD_CREATE (src, dst, itf);

   itf.role++;
   SHOULD_CREATE (src, dst, itf);
}

TEST (BindManagementEntries, CreateDstChange)
{
   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   // Should create a new entry - Changing destination address.
   dst.device++;
   SHOULD_CREATE (src, dst, itf);

   dst.mod++;
   SHOULD_CREATE (src, dst, itf);

   dst.unit++;
   SHOULD_CREATE (src, dst, itf);
}

TEST (BindManagementEntries, CreateItfAny)
{
   itf.id = HF::Interface::ANY_UID;

   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   // Should NOT create a entry with the same parameters.
   SHOULD_NOT_CREATE (src, dst, itf);
}

TEST (BindManagementEntries, DestroyOK)
{
   // Should be empty.
   LONGS_EQUAL (0, entries.size ());

   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   // Should have one element.
   LONGS_EQUAL (1, entries.size ());

   BindManagement::Entries::iterator it = entries.begin ();

   HF::Common::Result res               = entries.destroy (*it);

   LONGS_EQUAL (HF::Common::Result::OK, res);

   // Should be empty.
   LONGS_EQUAL (0, entries.size ());
}

TEST (BindManagementEntries, DestroyFAIL)
{
   // Should be empty.
   LONGS_EQUAL (0, entries.size ());

   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   // Should have one element.
   LONGS_EQUAL (1, entries.size ());

   BindManagement::Entry temp;

   HF::Common::Result    res = entries.destroy (temp);

   LONGS_EQUAL (HF::Common::Result::FAIL_ARG, res);

   // Should not be empty.
   LONGS_EQUAL (1, entries.size ());
}

TEST (BindManagementEntries, BeginEnd)
{
   CHECK_TRUE (entries.begin () == entries.end ());

   src.device++;

   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   auto it = entries.begin ();

   CHECK_FALSE (it == entries.end ());

   src.device++;

   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   CHECK_TRUE (it == entries.begin ());

   src.device -= 2;

   // Should create a new entry.
   SHOULD_CREATE (src, dst, itf);

   CHECK_FALSE (it == entries.begin ());
}

template<typename T>
void create_entries (T &entries, std::set <HF::Common::Interface> &db_itf,
                     std::set <HF::Protocol::Address> &db_addr)
{
   db_itf.insert (HF::Common::Interface (1, 0));
   db_itf.insert (HF::Common::Interface (2, 0));
   db_itf.insert (HF::Common::Interface (3, 0));

   db_itf.insert (HF::Common::Interface (1, 1));
   db_itf.insert (HF::Common::Interface (2, 1));
   db_itf.insert (HF::Common::Interface (3, 1));

   db_addr.insert (HF::Protocol::Address (1, 1, HF::Protocol::Address::DEVICE));
   db_addr.insert (HF::Protocol::Address (1, 2, HF::Protocol::Address::DEVICE));
   db_addr.insert (HF::Protocol::Address (1, 3, HF::Protocol::Address::DEVICE));

   db_addr.insert (HF::Protocol::Address (1, 1, HF::Protocol::Address::GROUP));
   db_addr.insert (HF::Protocol::Address (1, 2, HF::Protocol::Address::GROUP));
   db_addr.insert (HF::Protocol::Address (1, 3, HF::Protocol::Address::GROUP));

   db_addr.insert (HF::Protocol::Address (2, 1, HF::Protocol::Address::DEVICE));
   db_addr.insert (HF::Protocol::Address (2, 2, HF::Protocol::Address::DEVICE));
   db_addr.insert (HF::Protocol::Address (2, 3, HF::Protocol::Address::DEVICE));

   db_addr.insert (HF::Protocol::Address (2, 1, HF::Protocol::Address::GROUP));
   db_addr.insert (HF::Protocol::Address (2, 2, HF::Protocol::Address::GROUP));
   db_addr.insert (HF::Protocol::Address (2, 3, HF::Protocol::Address::GROUP));

   db_addr.insert (HF::Protocol::Address (3, 1, HF::Protocol::Address::DEVICE));
   db_addr.insert (HF::Protocol::Address (3, 2, HF::Protocol::Address::DEVICE));
   db_addr.insert (HF::Protocol::Address (3, 3, HF::Protocol::Address::DEVICE));

   db_addr.insert (HF::Protocol::Address (3, 1, HF::Protocol::Address::GROUP));
   db_addr.insert (HF::Protocol::Address (3, 2, HF::Protocol::Address::GROUP));
   db_addr.insert (HF::Protocol::Address (3, 3, HF::Protocol::Address::GROUP));

   /* *INDENT-OFF* */
   for_each (db_addr.begin (), db_addr.end (),
             [&entries, &db_itf, &db_addr] (HF::Protocol::Address const &src)
   {
      for_each (db_itf.begin (), db_itf.end (),
                [&entries, &db_itf, &db_addr, &src](HF::Common::Interface const &itf)
      {
         for_each (db_addr.begin (), db_addr.end (),
                   [&entries, &db_itf, &db_addr, &src, &itf](HF::Protocol::Address const &dst)
         {
            entries.save (BindManagement::Entry (src, itf, dst));
         });
      });
   });
   /* *INDENT-ON* */
}

TEST (BindManagementEntries, FindRange)
{
   std::set <HF::Common::Interface> db_itf;
   std::set <HF::Protocol::Address> db_addr;

   create_entries (this->entries, db_itf, db_addr);

   LONGS_EQUAL (18 * 6 * 18, entries.size ());

   auto it    = entries.begin ();

   auto range = entries.find ((*it).source, (*it).itf);

   LONGS_EQUAL (18, distance (range.first, range.second));

   /* *INDENT-OFF* */
   for_each (range.first, range.second, [&db_addr] (HF::Core::BindManagement::Entry const &entry)
   {
      db_addr.erase (entry.destination);
   });
   /* *INDENT-ON* */

   CHECK_TRUE (db_addr.empty ());
}

TEST (BindManagementEntries, Find)
{
   HF::Protocol::Address src (2, 2, HF::Protocol::Address::DEVICE);
   HF::Protocol::Address dst (3, 2, HF::Protocol::Address::GROUP);

   HF::Common::Interface itf (3, 0);

   LONGS_EQUAL (0, entries.size ());

   auto res = entries.save (BindManagement::Entry (src, itf, dst));

   LONGS_EQUAL (Common::Result::OK, res);
   LONGS_EQUAL (1, entries.size ());
}

TEST (BindManagementEntries, DestroyPredicate)
{
   std::set <HF::Common::Interface> db_itf;
   std::set <HF::Protocol::Address> db_addr;

   create_entries (this->entries, db_itf, db_addr);

   LONGS_EQUAL (18 * 6 * 18, entries.size ());

   uint16_t addr  = db_addr.begin ()->device;

   uint16_t count = 0;

   /* *INDENT-OFF* */
   Common::Result res = this->entries.destroy([addr, &count](BindManagement::Entry const &entry)
   {
      if (entry.source.device == addr)
      {
         count++;
      }
      return entry.source.device == addr;
   });
   /* *INDENT-ON* */

   LONGS_EQUAL (Common::Result::OK, res);

   LONGS_EQUAL ((18 - 6) * 6 * 18, entries.size ());
}

TEST (BindManagementEntries, DestroyAddress)
{
   std::set <HF::Common::Interface> db_itf;
   std::set <HF::Protocol::Address> db_addr;

   create_entries (this->entries, db_itf, db_addr);

   LONGS_EQUAL (18 * 6 * 18, entries.size ());

   uint16_t addr                = db_addr.begin ()->device;
   Protocol::Address::Type type = static_cast <Protocol::Address::Type>(db_addr.begin ()->mod);

   Common::Result res           = this->entries.destroy (addr, type);

   LONGS_EQUAL (Common::Result::OK, res);

   LONGS_EQUAL ((18 - 3) * 6 * (18 - 3), entries.size ());
}

// =============================================================================
// BindManagement - Server
// =============================================================================

TEST_GROUP (BindManagementServer)
{
   struct TestBindManagementServer:public HF::Core::BindManagement::DefaultServer
   {
      TestBindManagementServer(HF::Devices::Concentrator::IUnit0 &unit):
         HF::Core::BindManagement::DefaultServer (unit)
      {}

      virtual ~TestBindManagementServer()
      {}

      // =============================================================================

      MockSupport &mock ()
      {
         return ::mock ("Core::BindManagement::Server");
      }

      MockActualCall &mock_fn (const SimpleString &functionName)
      {
         return this->mock ().actualCall (functionName);
      }

      // =============================================================================

      Common::Result add (const Protocol::Address &source, const Protocol::Address &destination,
                          const Common::Interface &itf)
      {
         MockActualCall &call = mock_fn ("add");

         if (call.hasReturnValue ())
         {
            return (Common::Result) call.returnValue ().getIntValue ();
         }
         else
         {
            return HF::Core::BindManagement::DefaultServer::add (source, destination, itf);
         }
      }

      Result remove (const Protocol::Address &source, const Protocol::Address &destination,
                     const Common::Interface &itf)
      {
         MockActualCall &call = mock_fn ("remove");

         if (call.hasReturnValue ())
         {
            return (Common::Result) call.returnValue ().getIntValue ();
         }
         else
         {
            return HF::Core::BindManagement::DefaultServer::remove (source, destination, itf);
         }
      }
   };

   TestBindManagementServer *server;
   Testing::Concentrator    *device;

   Protocol::Packet packet;

   TEST_SETUP ()
   {
      device                  = new Testing::Concentrator ();
      server                  = new TestBindManagementServer (*device->unit0 ());

      packet                  = Protocol::Packet ();

      packet.message.type     = Protocol::Message::COMMAND_REQ;
      packet.message.itf.role = HF::Interface::SERVER_ROLE;
      packet.message.itf.id   = HF::Interface::BIND_MANAGEMENT;

      mock ().ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      delete server;
      delete device;

      mock ().clear ();
   }

   MockSupport &mock_s ()
   {
      return server->mock ();
   }

   void CreateDeviceEntries (BindManagement::Entry &entry, HF::Profiles::UID src, HF::Profiles::UID dst)
   {
      DeviceManagement::Device *dev = new DeviceManagement::Device ();

      DeviceManagement::Unit   unit;

      unit.id      = 0x22;
      unit.profile = src;

      dev->address = 0x1111;
      dev->units.push_back (unit);
      dev->emc     = 0xabcd;

      device->unit0 ()->device_management ()->entries ().save (*dev);
      delete dev;

      dev          = new DeviceManagement::Device ();

      unit.id      = 0x44;
      unit.profile = dst;

      dev->address = 0x3333;
      dev->units.push_back (unit);
      dev->emc     = 0xabcd;

      device->unit0 ()->device_management ()->entries ().save (*dev);
      delete dev;

      entry.source.device      = 0x1111;
      entry.source.unit        = 0x22;

      entry.destination.device = 0x3333;
      entry.destination.unit   = 0x44;

      entry.itf.role           = HF::Interface::SERVER_ROLE;
      entry.itf.id             = HF::Interface::ON_OFF;
   }
};

TEST (BindManagementServer, HandleAdd)
{
   BindManagement::Entry entry;

   entry.source.device       = 0x1111;
   entry.source.unit         = 0x22;

   entry.destination.device  = 0x3333;
   entry.destination.unit    = 0x44;

   entry.itf.role            = HF::Interface::SERVER_ROLE;
   entry.itf.id              = 0x5555;

   packet.message.length     = entry.size () + 6;
   packet.message.itf.member = BindManagement::ADD_BIND_CMD;

   packet.message.payload    = ByteArray (packet.message.length);

   entry.pack (packet.message.payload, 3);

   mock_s ().expectOneCall ("add").andReturnValue (Common::Result::OK);

   Common::Result res = server->handle (packet, packet.message.payload, 3);
   LONGS_EQUAL (Common::Result::OK, res);

   mock ().checkExpectations ();
}

TEST (BindManagementServer, HandleAdd2)
{
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_ONOFF_SWITCHABLE);

   packet.message.length     = entry.size () + 6;
   packet.message.itf.member = BindManagement::ADD_BIND_CMD;

   packet.message.payload    = ByteArray (packet.message.length);

   entry.pack (packet.message.payload, 3);

   mock_s ().expectOneCall ("add");
   mock ("AbstractDevice").expectOneCall ("send");

   Common::Result res = server->handle (packet, packet.message.payload, 3);
   LONGS_EQUAL (Common::Result::OK, res);

   mock ().checkExpectations ();
}

TEST (BindManagementServer, HandleRemove)
{
   BindManagement::Entry entry;

   entry.source.device       = 0x1111;
   entry.source.unit         = 0x22;

   entry.destination.device  = 0x3333;
   entry.destination.unit    = 0x44;

   entry.itf.role            = HF::Interface::SERVER_ROLE;
   entry.itf.id              = 0x5555;

   packet.message.length     = entry.size () + 6;
   packet.message.itf.member = BindManagement::REMOVE_BIND_CMD;

   packet.message.payload    = ByteArray (packet.message.length);

   entry.pack (packet.message.payload, 3);

   mock_s ().expectOneCall ("remove").andReturnValue (Common::Result::OK);

   Common::Result res = server->handle (packet, packet.message.payload, 3);
   LONGS_EQUAL (Common::Result::OK, res);

   mock ().checkExpectations ();
}

TEST (BindManagementServer, HandleRemove2)
{
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_ONOFF_SWITCHABLE);

   packet.message.length     = entry.size () + 6;
   packet.message.itf.member = BindManagement::ADD_BIND_CMD;

   packet.message.payload    = ByteArray (packet.message.length);

   entry.pack (packet.message.payload, 3);

   Common::Result res = server->handle (packet, packet.message.payload, 3);
   LONGS_EQUAL (Common::Result::OK, res);

   packet.message.itf.member = BindManagement::REMOVE_BIND_CMD;

   mock_s ().expectOneCall ("remove");
   mock ("AbstractDevice").expectOneCall ("send");

   res = server->handle (packet, packet.message.payload, 3);
   LONGS_EQUAL (Common::Result::OK, res);

   mock ().checkExpectations ();
}


TEST (BindManagementServer, AddMatch)
{
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_ONOFF_SWITCHABLE);

   LONGS_EQUAL (0, server->entries ().size ());

   mock_s ().expectOneCall ("add");

   auto res = server->add (entry.source, entry.destination, entry.itf);

   mock ().checkExpectations ();

   LONGS_EQUAL (Common::Result::OK, res);

   LONGS_EQUAL (1, server->entries ().size ());

   // Should not add if entry already present.

   mock_s ().expectOneCall ("add");

   res = server->add (entry.source, entry.destination, entry.itf);

   mock ().checkExpectations ();

   LONGS_EQUAL (Common::Result::OK, res);

   LONGS_EQUAL (1, server->entries ().size ());
}

TEST (BindManagementServer, AddMatchFromConcentrator)
{
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_ONOFF_SWITCHABLE);

   HF::Units::Unit <HF::Profiles::SimpleOnOffSwitch> unit (1, *device);

   LONGS_EQUAL (0, server->entries ().size ());

   entry.source.device      = 0x0;
   entry.source.unit        = 0x1;
   entry.destination.device = 0x3333;
   entry.destination.unit   = 0x44;

   auto res = server->add (entry.source, entry.destination, entry.itf);

   mock ().checkExpectations ();

   LONGS_EQUAL (Common::Result::OK, res);
   LONGS_EQUAL (1, server->entries ().size ());
}

TEST (BindManagementServer, AddMatchToConcentrator)
{
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_ONOFF_SWITCHABLE);

   HF::Units::Unit <HF::Profiles::SimpleLight> sl_unit (2, *device);

   LONGS_EQUAL (0, server->entries ().size ());

   entry.source.device      = 0x1111;
   entry.source.unit        = 0x22;
   entry.destination.device = 0x0;
   entry.destination.unit   = 0x2;

   auto res = server->add (entry.source, entry.destination, entry.itf);

   mock ().checkExpectations ();

   LONGS_EQUAL (Common::Result::OK, res);
   LONGS_EQUAL (1, server->entries ().size ());
}

TEST (BindManagementServer, AddMatchCatchAll)
{
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_ONOFF_SWITCHABLE);

   entry.source.device = HF::Protocol::BROADCAST_ADDR;
   entry.source.unit   = HF::Protocol::BROADCAST_UNIT;

   auto res = server->add (entry.source, entry.destination, entry.itf);

   mock ().checkExpectations ();

   LONGS_EQUAL (Common::Result::OK, res);
   LONGS_EQUAL (1, server->entries ().size ());
}

TEST (BindManagementServer, AddNoMatch)
{
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE);

   mock_s ().expectOneCall ("add");

   auto res = server->add (entry.source, entry.destination, entry.itf);
   LONGS_EQUAL (Common::Result::FAIL_ARG, res);

   mock ().checkExpectations ();
}

TEST (BindManagementServer, AddNoMatchButAnyItf)
{
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE);

   entry.itf.id = HF::Interface::ANY_UID;

   mock_s ().expectOneCall ("add");

   auto res = server->add (entry.source, entry.destination, entry.itf);
   LONGS_EQUAL (Common::Result::OK, res);

   mock ().checkExpectations ();
}

TEST (BindManagementServer, RemoveMatch)
{
   // Create entry.
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_ONOFF_SWITCHABLE);

   // Create the entry.
   auto temp = server->add (entry.source, entry.destination, entry.itf);
   LONGS_EQUAL (Common::Result::OK, temp);

   // Try to remove entry.
   mock_s ().expectOneCall ("remove");

   Common::Result res = server->remove (entry.source, entry.destination, entry.itf);
   LONGS_EQUAL (Common::Result::OK, res);

   mock ().checkExpectations ();
}

TEST (BindManagementServer, RemoveNoMatch)
{
   // Create entry.
   BindManagement::Entry entry;
   CreateDeviceEntries (entry, HF::Profiles::SIMPLE_ONOFF_SWITCH, HF::Profiles::SIMPLE_ONOFF_SWITCHABLE);

   // Try to remove entry.
   mock_s ().expectOneCall ("remove");

   Common::Result res = server->remove (entry.source, entry.destination, entry.itf);
   LONGS_EQUAL (Common::Result::FAIL_ARG, res);

   mock ().checkExpectations ();
}

TEST (BindManagementServer, EntriesSession)
{
   // Create entry.
   BindManagement::Entry entry;

   for (uint8_t i = 0; i < 20; i++)
   {
      entry.source.device      = 0x1111 + i;
      entry.source.unit        = 0x22 + i;
      entry.destination.device = 0x1111 + i;
      entry.destination.unit   = 0x44 + i;
      server->entries ().save (entry);
   }

   LONGS_EQUAL (20, server->entries ().size ());

   server->sessions ().start_session (0x1234);

   entry.destination.device++;
   server->entries ().save (entry);

   LONGS_EQUAL (21, server->entries ().size ());
   CHECK_FALSE (server->sessions ().is_valid (0x1234));

   server->sessions ().start_session (0x1234);
   CHECK_TRUE (server->sessions ().is_valid (0x1234));

   server->entries ().destroy (entry);

   LONGS_EQUAL (20, server->entries ().size ());
   CHECK_FALSE (server->sessions ().is_valid (0x1234));
}
