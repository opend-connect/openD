// =============================================================================
/*!
 * @file       tests/core/test_attribute_reporting.cpp
 *
 * This file contains the implementation of the unit tests for the Attribute
 * Reporting core service in HAN-FUN.
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

#include "hanfun/core/attribute_reporting.h"
#include "hanfun/units.h"

#include "hanfun/debug.h"

using namespace HF;
using namespace HF::Common;
using namespace HF::Core;
using namespace HF::Core::AttributeReporting;
using namespace HF::Testing;

// =============================================================================
// Helper Functions
// =============================================================================

// =============================================================================
// AttributeReporting::Reference
// =============================================================================

TEST_GROUP (AttrReport_Reference)
{
   Reference report;

   ByteArray expected;

   TEST_SETUP ()
   {
      report   = Reference ();
      expected = {0x00, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Reference, Size)
{
   LONGS_EQUAL (sizeof(uint8_t), report.size ())
};

TEST (AttrReport_Reference, Pack)
{
   ByteArray result (expected.size ());

   report.type = PERIODIC;
   report.id   = 0x5D;

   LONGS_EQUAL (report.size (), report.pack (result, 3));

   result      = ByteArray (expected.size ());

   report.type = EVENT;
   report.id   = 0x5D;

   result[3]  |= 0x80;

   LONGS_EQUAL (report.size (), report.pack (result, 3));
};

TEST (AttrReport_Reference, Unpack)
{
   LONGS_EQUAL (report.size (), report.unpack (expected, 3));

   LONGS_EQUAL (PERIODIC, report.type);
   LONGS_EQUAL (0x5D, report.id);

   expected[3] |= 0x80;

   LONGS_EQUAL (report.size (), report.unpack (expected, 3));

   LONGS_EQUAL (EVENT, report.type);
   LONGS_EQUAL (0x5D, report.id);
};

// =============================================================================
// AttributeReporting::Entry
// =============================================================================

TEST_GROUP (AttrReport_Entry)
{
   struct Entry:public AttributeReporting::Entry
   {};

   Entry entry;

   ByteArray expected;

   TEST_SETUP ()
   {
      entry    = Entry ();

      expected = ByteArray {0x00, 0x00, 0x00,
                            0x5A,                       // Unit ID
                            0x80, 0xAA,                 // Interface : Type + UID.
                            HF::Attributes::Pack::ALL,  // Attribute Pack ID.
                            0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Entry, Size)
{
   LONGS_EQUAL (1 + 2 + 1, entry.size ());
}

TEST (AttrReport_Entry, Empty)
{
   ByteArray temp (entry.size ());
   entry.pack (temp);
   entry.unpack (temp);
}

TEST (AttrReport_Entry, Pack)
{
   ByteArray result (expected.size ());

   entry.unit     = 0x5A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0xAA;
   entry.pack_id  = HF::Attributes::Pack::ALL;

   LONGS_EQUAL (entry.size (), entry.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Entry, Unpack)
{
   LONGS_EQUAL (entry.size (), entry.unpack (expected, 3));

   LONGS_EQUAL (0x5A, entry.unit);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, entry.itf.role);
   LONGS_EQUAL (0xAA, entry.itf.id);
   LONGS_EQUAL (HF::Attributes::Pack::ALL, entry.pack_id);
}

// =============================================================================
// AttributeReporting::Rule
// =============================================================================

TEST_GROUP (AttrReport_Rule)
{
   struct Rule:public AttributeReporting::Rule
   {};

   Rule rule;

   ByteArray expected;

   TEST_SETUP ()
   {
      rule     = Rule ();

      expected = ByteArray {0x00, 0x00, 0x00,
                            0x8A,                       // Report ID
                            0x85, 0xA5, 0xAA,           // Address : Type + UID.
                            0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Rule, Size)
{
   LONGS_EQUAL (1 + 2 + 1, rule.size ());
}

TEST (AttrReport_Rule, Empty)
{
   ByteArray temp (rule.size ());
   rule.pack (temp);
   rule.unpack (temp);
}

TEST (AttrReport_Rule, Pack)
{
   ByteArray result (expected.size ());

   rule.report.type        = EVENT;
   rule.report.id          = 0x0A;

   rule.destination.mod    = HF::Interface::SERVER_ROLE;
   rule.destination.device = 0x05A5;
   rule.destination.unit   = 0xAA;

   LONGS_EQUAL (rule.size (), rule.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Rule, Unpack)
{
   LONGS_EQUAL (rule.size (), rule.unpack (expected, 3));

   LONGS_EQUAL (EVENT, rule.report.type);
   LONGS_EQUAL (0x0A, rule.report.id);

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, rule.destination.mod);
   LONGS_EQUAL (0x05A5, rule.destination.device);
   LONGS_EQUAL (0xAA, rule.destination.unit);
}

// =============================================================================
// AttributeReporting::Periodic
// =============================================================================

// =============================================================================
// AttributeReporting::Periodic::Entry
// =============================================================================

TEST_GROUP (AttrReport_Periodic_Entry)
{
   Periodic::Entry entry;

   ByteArray expected;

   TEST_SETUP ()
   {
      entry = Periodic::Entry ();
   }
};

TEST (AttrReport_Periodic_Entry, Size)
{
   entry.pack_id = HF::Attributes::Pack::MANDATORY;

   LONGS_EQUAL (1 + 2 + 1, entry.size ());

   entry.pack_id = HF::Attributes::Pack::ALL;

   LONGS_EQUAL (1 + 2 + 1, entry.size ());

   entry.pack_id = HF::Attributes::Pack::DYNAMIC;

   entry.uids.push_back (0xA1);
   entry.uids.push_back (0xA2);
   entry.uids.push_back (0xA3);

   LONGS_EQUAL (1 + 2 + 1 + 1 + 3, entry.size ());
}

TEST (AttrReport_Periodic_Entry, Empty)
{
   ByteArray temp (entry.size ());
   entry.pack (temp);
   entry.unpack (temp);
}

TEST (AttrReport_Periodic_Entry, Pack)
{
   expected = {0xFF, 0xFF, 0xFF,
               0x5A,                            // Unit ID
               0x80, 0xAA,                      // Interface : Type + UID.
               HF::Attributes::Pack::MANDATORY, // Attribute Pack ID.
               0xFF, 0xFF, 0xFF};

   ByteArray result (expected.size ());
   std::fill_n (result.begin (), expected.size (), 0xFF);

   entry.unit     = 0x5A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0xAA;
   entry.pack_id  = HF::Attributes::Pack::MANDATORY;

   LONGS_EQUAL (entry.size (), entry.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Periodic_Entry, Pack2)
{
   expected = {0xFF, 0xFF, 0xFF,
               0x5A,                      // Unit ID
               0x80, 0xAA,                // Interface : Type + UID.
               HF::Attributes::Pack::ALL, // Attribute Pack ID.
               0xFF, 0xFF, 0xFF};

   ByteArray result (expected.size ());
   std::fill_n (result.begin (), expected.size (), 0xFF);

   entry.unit     = 0x5A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0xAA;
   entry.pack_id  = HF::Attributes::Pack::ALL;

   LONGS_EQUAL (entry.size (), entry.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Periodic_Entry, Pack3)
{
   expected = {0xFF, 0xFF, 0xFF,
               0x5A,                          // Unit ID
               0x80, 0xAA,                    // Interface : Type + UID.
               HF::Attributes::Pack::DYNAMIC, // Attribute Pack ID.
               0x03, 0xA1, 0xA2,0xA3,         // Attributes UID's
               0xFF, 0xFF, 0xFF};

   ByteArray result (expected.size ());
   std::fill_n (result.begin (), expected.size (), 0xFF);

   entry.unit     = 0x5A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0xAA;
   entry.pack_id  = HF::Attributes::Pack::DYNAMIC;

   entry.uids.push_back (0xA1);
   entry.uids.push_back (0xA2);
   entry.uids.push_back (0xA3);

   LONGS_EQUAL (entry.size (), entry.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Periodic_Entry, Unpack)
{
   expected = {0xFF, 0xFF, 0xFF,
               0x5A,                          // Unit ID
               0x80, 0xAA,                    // Interface : Type + UID.
               HF::Attributes::Pack::DYNAMIC, // Attribute Pack ID.
               0x03, 0xA1, 0xA2,0xA3,         // Attributes UID's
               0xFF, 0xFF, 0xFF};

   LONGS_EQUAL (1 + 2 + 1 + 1 + 3, entry.unpack (expected, 3));

   LONGS_EQUAL (0x5A, entry.unit);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, entry.itf.role);
   LONGS_EQUAL (0xAA, entry.itf.id);
   LONGS_EQUAL (HF::Attributes::Pack::DYNAMIC, entry.pack_id);

   LONGS_EQUAL (0x03, entry.uids.length ());

   std::vector <uint8_t> temp = {0xA1, 0xA2, 0xA3};

   CHECK_EQUAL (temp, entry.uids);
}

// =============================================================================
// AttributeReporting::Periodic::Rule
// =============================================================================

TEST_GROUP (AttrReport_Periodic_Rule)
{
   Periodic::Rule rule;

   ByteArray expected;

   TEST_SETUP ()
   {
      rule     = Periodic::Rule (0xAABBCCDD);

      expected = ByteArray {0x00, 0x00, 0x00,
                            0x0A,                   // Report ID
                            0x85, 0xA5, 0xAA,       // Address : Type + UID.
                            0xAA, 0xBB, 0xCC, 0xDD, // Report period
                            0x03,                   // Number of entries.
                                                    // Entry 1
                            0x5A,                   // Unit ID.
                            0x85, 0x5A,             // Interface.
                            HF::Attributes::Pack::MANDATORY,
                            // Entry 2
                            0x6A,                       // Unit ID.
                            0x83, 0xA5,                 // Interface.
                            HF::Attributes::Pack::ALL,
                            // Entry 3
                            0x7A,                       // Unit ID.
                            0x83, 0xEE,                 // Interface.
                            HF::Attributes::Pack::DYNAMIC,
                            0x04, 0xD1, 0xD2, 0xD3, 0xD4,
                            0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Periodic_Rule, Size)
{
   LONGS_EQUAL (1 + 2 + 1 + 4 + 1, rule.size ());

   Periodic::Entry entry;

   rule.add (entry);
   rule.add (entry);
   rule.add (entry);

   LONGS_EQUAL (1 + 2 + 1 + 4 + 1 + 3 * entry.size (), rule.size ());
}

TEST (AttrReport_Periodic_Rule, Empty)
{
   ByteArray temp (rule.size ());
   rule.pack (temp);
   rule.unpack (temp);
}

TEST (AttrReport_Periodic_Rule, Pack)
{
   ByteArray result (expected.size ());

   rule.report.type        = PERIODIC;
   rule.report.id          = 0x0A;

   rule.destination.mod    = HF::Protocol::Address::GROUP;
   rule.destination.device = 0x05A5;
   rule.destination.unit   = 0xAA;

   // NOTE : Entries are added to the front of the list.
   Periodic::Entry entry;

   entry.unit     = 0x7A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0x03EE;
   entry.pack_id  = HF::Attributes::Pack::DYNAMIC;
   entry.uids     = {0xD1, 0xD2, 0xD3, 0xD4};

   rule.add (entry);

   entry.unit     = 0x6A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0x03A5;
   entry.pack_id  = HF::Attributes::Pack::ALL;

   rule.add (entry);

   entry.unit     = 0x5A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0x055A;
   entry.pack_id  = HF::Attributes::Pack::MANDATORY;

   rule.add (entry);

   LONGS_EQUAL (rule.size (), rule.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Periodic_Rule, Unpack)
{
   Periodic::Entry entry;
   LONGS_EQUAL (1 + 1 + 2 + 1 + 4 + 1 + (1 + 2 + 1) + (1 + 2 + 1) + (1 + 2 + 1 + 4),
                rule.unpack (expected, 3));

   LONGS_EQUAL (PERIODIC, rule.report.type);
   LONGS_EQUAL (0x0A, rule.report.id);

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, rule.destination.mod);
   LONGS_EQUAL (0x05A5, rule.destination.device);
   LONGS_EQUAL (0xAA, rule.destination.unit);

   LONGS_EQUAL (0xAABBCCDD, rule.interval);
}

// =============================================================================
// AttributeReporting::Event
// =============================================================================

// =============================================================================
// AttributeReporting::Event::Field
// =============================================================================

TEST_GROUP (AttrReport_Event_Field)
{
   Event::Field field;

   ByteArray    expected;

   TEST_SETUP ()
   {
      field    = Event::Field ();

      expected = ByteArray {0x00, 0x00, 0x00,
                            0x5A,                     // Attribute UID.
                            Event::EQ,                // Event Type.
                            0x04,                     // Field size.
                            0xA1, 0xA2, 0xA3, 0xA4,   // Field value.
                            0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Event_Field, Size)
{
   field.type = Event::EQ;

   LONGS_EQUAL (1 + 1, field.size (false));
   LONGS_EQUAL (1 + 1 + 1, field.size (true));

   field.value.push_back (0xA1);
   field.value.push_back (0xA2);
   field.value.push_back (0xA3);
   field.value.push_back (0xA4);

   LONGS_EQUAL (1 + 1 + 4, field.size (false));
   LONGS_EQUAL (1 + 1 + 4 + 1, field.size (true));

   field.type = Event::COV;

   LONGS_EQUAL (1 + 1, field.size (false));
   LONGS_EQUAL (1 + 1 + 1, field.size (true));
}

TEST (AttrReport_Event_Field, Empty)
{
   ByteArray temp (field.size (true));

   field.pack (temp, 0, true);
   field.unpack (temp, 0, true);

   field.pack (temp, 0, false);
   field.unpack (temp, 0, false);
}

TEST (AttrReport_Event_Field, Pack)
{
   ByteArray result (expected.size ());

   field.type     = Event::EQ;
   field.attr_uid = 0x5A;

   field.value    = {0xA1, 0xA2, 0xA3, 0xA4};

   LONGS_EQUAL (field.size (true), field.pack (result, 3, true));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Event_Field, Pack2)
{
   expected[3] = Event::COV;
   expected[4] = 0xAA;
   expected[5] = 0x00;
   expected[6] = 0x00;
   expected[7] = 0x00;
   expected[8] = 0x00;
   expected[9] = 0x00;

   ByteArray result (expected.size ());

   field.type     = Event::COV;
   field.attr_uid = 0x5A;

   field.value.push_back (0xAA);
   field.value.push_back (0xA2);
   field.value.push_back (0xA3);
   field.value.push_back (0xA4);

   LONGS_EQUAL (field.size (false), field.pack (result, 3, false));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Event_Field, Unpack)
{
   LONGS_EQUAL (1 + 1 + 1 + 4, field.unpack (expected, 3, true));

   LONGS_EQUAL (Event::EQ, field.type);
   LONGS_EQUAL (0x5A, field.attr_uid);

   LONGS_EQUAL (0x04, field.value.size ());

   std::vector <uint8_t> temp = {0xA1, 0xA2, 0xA3, 0xA4};

   CHECK_EQUAL (temp, field.value);
}

TEST (AttrReport_Event_Field, Unpack2)
{
   expected[4] = Event::COV;
   expected[5] = 0xAA;

   LONGS_EQUAL (field.size (true), field.unpack (expected, 3, true));

   LONGS_EQUAL (Event::COV, field.type);
   LONGS_EQUAL (0x5A, field.attr_uid);

   LONGS_EQUAL (0x01, field.value.size ());

   LONGS_EQUAL (0xAA, field.value[0]);
}

// =============================================================================
// AttributeReporting::Event::Entry
// =============================================================================

TEST_GROUP (AttrReport_Event_Entry)
{
   Event::Entry entry;

   ByteArray    expected;

   TEST_SETUP ()
   {
      entry    = Event::Entry ();

      expected = ByteArray {0x00, 0x00, 0x00,
                            0x5A,                          // Unit ID
                            0x80, 0xAA,                    // Interface : Type + UID.
                            HF::Attributes::Pack::DYNAMIC, // Attribute Pack ID.
                            0x04,                          // Number of fields.
                                                           // Field 1.
                            0x5A,                          // Attribute UID.
                            Event::COV,                    // Event Type.
                            0x33,                          // Event Value.
                                                           // Field 2.
                            0x5A,                          // Attribute UID.
                            Event::HT,                     // Event Type.
                            0x01, 0xAA,                    // Event Value.
                                                           // Field 3.
                            0x5A,                          // Attribute UID.
                            Event::LT,                     // Event Type.
                            0x01, 0x55,                    // Event Value.
                                                           // Field 4.
                            0x5A,                          // Attribute UID.
                            Event::EQ,                     // Event Type.
                            0x01, 0x42,                    // Event Value.
                            0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Event_Entry, Size)
{
   Event::Field field;

   field.attr_uid = 0x5A;
   field.type     = Event::COV;
   field.value.push_back (0x55);

   entry.fields.push_back (field);

   LONGS_EQUAL (1 + 2 + 1 + 1 + 1, entry.size ());

   entry.pack_id = HF::Attributes::Pack::DYNAMIC;

   LONGS_EQUAL (1 + 2 + 1 + 1 + 1 + 1 + 1, entry.size ());

   entry.fields.push_back (field);
   entry.fields.push_back (field);

   LONGS_EQUAL (1 + 2 + 1 + 1 + 3 * field.size (true), entry.size ());
}

TEST (AttrReport_Event_Entry, Empty)
{
   ByteArray temp (entry.size ());
   entry.pack (temp);
   entry.unpack (temp);
}

TEST (AttrReport_Event_Entry, Pack)
{
   ByteArray result (expected.size ());

   entry.unit     = 0x5A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0xAA;
   entry.pack_id  = HF::Attributes::Pack::DYNAMIC;

   Event::Field field;

   field.attr_uid = 0x5A;
   field.type     = Event::COV;
   field.value    = {0x33};

   entry.fields.push_back (field);

   field.type  = Event::HT;
   field.value = {0xAA};

   entry.fields.push_back (field);

   field.type  = Event::LT;
   field.value = {0x55};

   entry.fields.push_back (field);

   field.type  = Event::EQ;
   field.value = {0x42};

   entry.fields.push_back (field);

   LONGS_EQUAL (entry.size (), entry.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Event_Entry, Unpack)
{
   entry.unpack (expected, 3);

   LONGS_EQUAL (0x5A, entry.unit);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, entry.itf.role);
   LONGS_EQUAL (0xAA, entry.itf.id);
   LONGS_EQUAL (HF::Attributes::Pack::DYNAMIC, entry.pack_id);

   LONGS_EQUAL (0x04, entry.fields.size ());

   Event::Field &field = entry.fields[0];

   LONGS_EQUAL (0x5A, field.attr_uid);
   LONGS_EQUAL (Event::COV, field.type);
   LONGS_EQUAL (0x33, field.value[0]);

   field = entry.fields[1];

   LONGS_EQUAL (0x5A, field.attr_uid);
   LONGS_EQUAL (Event::HT, field.type);
   LONGS_EQUAL (0xAA, field.value[0]);

   field = entry.fields[2];

   LONGS_EQUAL (0x5A, field.attr_uid);
   LONGS_EQUAL (Event::LT, field.type);
   LONGS_EQUAL (0x55, field.value[0]);

   field = entry.fields[3];

   LONGS_EQUAL (0x5A, field.attr_uid);
   LONGS_EQUAL (Event::EQ, field.type);
   LONGS_EQUAL (0x42, field.value[0]);
}

TEST (AttrReport_Event_Entry, Unpack2)
{
   expected = {0x00, 0x00, 0x00,
               0x5A,                      // Unit ID
               0x80, 0xAA,                // Interface : Type + UID.
               HF::Attributes::Pack::ALL, // Attribute Pack ID.
               Event::COV,                // Event Type.
               0x33,                      // Event Value.
               0x00, 0x00, 0x00};

   entry.unpack (expected, 3);

   LONGS_EQUAL (0x5A, entry.unit);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, entry.itf.role);
   LONGS_EQUAL (0xAA, entry.itf.id);
   LONGS_EQUAL (HF::Attributes::Pack::ALL, entry.pack_id);

   LONGS_EQUAL (0x01, entry.fields.size ());

   Event::Field &field = entry.fields[0];

   LONGS_EQUAL (0x00, field.attr_uid);
   LONGS_EQUAL (Event::COV, field.type);
   LONGS_EQUAL (0x33, field.value[0]);
}

// =============================================================================
// AttributeReporting::Event::Rule
// =============================================================================

TEST_GROUP (AttrReport_Event_Rule)
{
   Event::Rule rule;

   ByteArray   expected;

   TEST_SETUP ()
   {
      rule     = Event::Rule ();

      expected = {0x00, 0x00, 0x00,
                  0x8A,                          // Report ID
                  0x85, 0xA5, 0xAA,              // Address : Type + UID.
                  0x03,                          // Number of units.
                                                 // Entry 1
                  0x5A,                          // Unit ID.
                  0x80, 0xAA,                    // Interface : Type + UID.
                  HF::Attributes::Pack::DYNAMIC, // Attribute Pack ID.
                  0x01,                          // Number of fields.
                                                 // Entry 1 - Field 1.
                  0x10,                          // Attribute UID.
                  Event::COV,                    // Event Type.
                  0x33,                          // Event Value.
                                                 // Entry 2
                  0x5A,                          // Unit ID.
                  0x80, 0xAA,                    // Interface : Type + UID.
                  HF::Attributes::Pack::DYNAMIC, // Attribute Pack ID.
                  0x02,                          // Number of fields.
                                                 // Field 1.
                  0x11,                          // Attribute UID.
                  Event::HT,                     // Event Type.
                  0x01, 0xAA,                    // Event Value.
                                                 // Field 2.
                  0x12,                          // Attribute UID.
                  Event::LT,                     // Event Type.
                  0x01, 0x55,                    // Event Value.
                                                 // Entry 3
                  0x5A,                          // Unit ID.
                  0x80, 0xAA,                    // Interface : Type + UID.
                  HF::Attributes::Pack::ALL,     // Attribute Pack ID.
                  Event::COV,                    // Event Type.
                  0x88,                          // Event Value.
                  0x00, 0x00, 0x00};
   }

   Event::Entry create ()
   {
      Event::Entry entry;

      entry.unit     = 0x5A;
      entry.itf.role = HF::Interface::SERVER_ROLE;
      entry.itf.id   = 0xAA;
      entry.pack_id  = HF::Attributes::Pack::DYNAMIC;

      return entry;
   }

   uint16_t create_entry_1 ()
   {
      Event::Entry entry = create ();

      Event::Field field;
      field.attr_uid = 0x10;

      field.type     = Event::COV;
      field.value    = {0x33};

      entry.fields.push_back (field);

      rule.add (entry);

      return entry.size ();
   }

   uint16_t create_entry_2 ()
   {
      Event::Entry entry = create ();

      Event::Field field;
      field.attr_uid = 0x11;

      field.type     = Event::HT;
      field.value    = {0xAA};

      entry.fields.push_back (field);

      field.attr_uid = 0x12;
      field.type     = Event::LT;
      field.value    = {0x55};

      entry.fields.push_back (field);

      rule.add (entry);

      return entry.size ();
   }

   uint16_t create_entry_3 ()
   {
      Event::Entry entry = create ();

      entry.pack_id = HF::Attributes::Pack::ALL;

      Event::Field field;
      field       = Event::Field ();

      field.type  = Event::COV;
      field.value = {0x88};

      entry.fields.push_back (field);

      rule.add (entry);

      return entry.size ();
   }

   void initialize ()
   {
      rule.report.type        = EVENT;
      rule.report.id          = 0x0A;

      rule.destination.mod    = HF::Interface::SERVER_ROLE;
      rule.destination.device = 0x05A5;
      rule.destination.unit   = 0xAA;

      create_entry_3 ();
      create_entry_2 ();
      create_entry_1 ();
   }
};

TEST (AttrReport_Event_Rule, Size)
{
   uint16_t size = 1 + 2 + 1 + 1;

   LONGS_EQUAL (size, rule.size ());

   // Add an entry.
   size += create_entry_1 ();

   LONGS_EQUAL (size, rule.size ());

   // Add other entry.
   size += create_entry_2 ();

   LONGS_EQUAL (size, rule.size ());

   // Add yet another entry.
   size += create_entry_2 ();

   LONGS_EQUAL (size, rule.size ());
}

TEST (AttrReport_Event_Rule, Empty)
{
   ByteArray temp (rule.size ());
   rule.pack (temp);
   rule.unpack (temp);
}

TEST (AttrReport_Event_Rule, Pack)
{
   ByteArray result (expected.size ());

   initialize ();

   LONGS_EQUAL (rule.size (), rule.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Event_Rule, Unpack)
{
   initialize ();

   uint16_t size = rule.size ();

   rule = Event::Rule ();

   LONGS_EQUAL (size, rule.unpack (expected, 3));

   LONGS_EQUAL (EVENT, rule.report.type);
   LONGS_EQUAL (0x0A, rule.report.id);

   LONGS_EQUAL (HF::Interface::SERVER_ROLE, rule.destination.mod);
   LONGS_EQUAL (0x05A5, rule.destination.device);
   LONGS_EQUAL (0xAA, rule.destination.unit);

   LONGS_EQUAL (0x03, rule.entries_count ());
}

// =============================================================================
// AttributeReporting::Report
// =============================================================================

TEST_GROUP (AttrReport_Report_Entry)
{
   Report::Entry entry;
   Common::ByteArray expected;

   TEST_SETUP ()
   {
      entry    = Report::Entry ();
      expected = {0x00, 0x00, 0x00,
                  0x55,       // Unit ID.
                  0x85, 0xA5, // Interface UID.
                  0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Report_Entry, Size)
{
   LONGS_EQUAL (1 + 2 + 1, entry.size ());
};

TEST (AttrReport_Report_Entry, Empty)
{
   ByteArray temp (entry.size ());
   entry.pack (temp);
   entry.unpack (HF::Testing::FactoryGetter, temp);
}

TEST (AttrReport_Report_Entry, Pack)
{
   entry.unit     = 0x55;
   entry.itf.id   = 0x05A5;
   entry.itf.role = HF::Interface::SERVER_ROLE;

   ByteArray result (expected.size ());

   LONGS_EQUAL (entry.size (), entry.pack (result, 3));

   CHECK_EQUAL (expected, result);
};

TEST (AttrReport_Report_Entry, Unpack)
{
   LONGS_EQUAL (entry.size (), entry.unpack (HF::Testing::FactoryGetter, expected, 3));

   LONGS_EQUAL (0x55, entry.unit);
   LONGS_EQUAL (0x05A5, entry.itf.id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, entry.itf.role);
};

// =============================================================================
// AttributeReporting::Report::Periodic
// =============================================================================

TEST_GROUP (AttrReport_Report_Periodic_Entry)
{
   Report::Periodic::Entry entry;
   Common::ByteArray expected;

   TEST_SETUP ()
   {
      entry    = Report::Periodic::Entry ();
      expected = {0x00,                 0x00, 0x00,
                  0x55,                       // Unit ID.
                  0x85,                 0xA5, // Interface UID.
                  0x03,                       // Number of attributes.
                  TestInterface::ATTR1,
                  0xAA,                 0xBB,
                  TestInterface::ATTR2,
                  0xCC,                 0xDD,
                  TestInterface::ATTR3,
                  0xEE,                 0xFF,
                  0x00,                 0x00, 0x00};
   }

   TEST_TEARDOWN ()
   {}
};

TEST (AttrReport_Report_Periodic_Entry, Size)
{
   LONGS_EQUAL (1 + 2 + 1, entry.size ());
};

TEST (AttrReport_Report_Periodic_Entry, Empty)
{
   ByteArray temp (entry.size ());
   entry.pack (temp);

   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;
   entry.unpack (get_factory, temp);
}

TEST (AttrReport_Report_Periodic_Entry, Pack)
{
   entry.unit     = 0x55;
   entry.itf.id   = 0x05A5;
   entry.itf.role = HF::Interface::SERVER_ROLE;

   HF::Attributes::Factory factory            = HF::Testing::TestInterface::create_attribute;

   HF::Attributes::IAttribute *attr           = factory (TestInterface::ATTR1);

   HF::Attributes::Attribute <uint16_t> *temp = (HF::Attributes::Attribute <uint16_t> *)attr;

   temp->set (0xAABB);

   entry.add (attr);

   attr = factory (TestInterface::ATTR2);
   temp = (HF::Attributes::Attribute <uint16_t> *)attr;
   temp->set (0xCCDD);

   entry.add (attr);

   attr = factory (TestInterface::ATTR3);
   temp = (HF::Attributes::Attribute <uint16_t> *)attr;
   temp->set (0xEEFF);

   entry.add (attr);

   ByteArray result (expected.size ());

   LONGS_EQUAL (entry.size (), entry.pack (result, 3));

   CHECK_EQUAL (expected, result);
};

TEST (AttrReport_Report_Periodic_Entry, Unpack)
{
   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;
   LONGS_EQUAL (1 + 2 + 1 + 3 * (1 + 2), entry.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x55, entry.unit);
   LONGS_EQUAL (0x05A5, entry.itf.id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, entry.itf.role);

   // TODO Check attributes.
};

TEST_GROUP (AttrReport_Report_Periodic)
{
   Report::Periodic  report;
   Common::ByteArray expected;

   TEST_SETUP ()
   {
      report   = Report::Periodic ();

      expected = {0x00,                 0x00, 0x00,
                  0x0A,                       // Report ID.
                                              // Entry 1
                  0x55,                       // Unit ID.
                  0x85,                 0xA5, // Interface UID.
                  0x03,                       // Number of attributes.
                  TestInterface::ATTR1,
                  0xAA,                 0xBB,
                  TestInterface::ATTR2,
                  0xCC,                 0xDD,
                  TestInterface::ATTR3,
                  0xEE,                 0xFF,
                                              // Entry 2
                  0x56,                       // Unit ID.
                  0x85,                 0xA5, // Interface UID.
                  0x03,                       // Number of attributes.
                  TestInterface::ATTR1,
                  0x12,                 0x34,
                  TestInterface::ATTR2,
                  0x56,                 0x78,
                  TestInterface::ATTR3,
                  0x9A,                 0xBC,
                                              // Entry 2
                  0x57,                       // Unit ID.
                  0x85,                 0xA5, // Interface UID.
                  0x03,                       // Number of attributes.
                  TestInterface::ATTR1,
                  0x43,                 0x21,
                  TestInterface::ATTR2,
                  0x87,                 0x65,
                  TestInterface::ATTR3,
                  0xCB,                 0xA9,
                  0x00,                 0x00, 0x00};
   }

   TEST_TEARDOWN ()
   {}

   void create_entry_1 ()
   {
      Report::Periodic::Entry entry;

      entry.unit     = 0x55;
      entry.itf.role = HF::Interface::SERVER_ROLE;
      entry.itf.id   = 0x05A5;

      HF::Attributes::Factory factory            = HF::Testing::TestInterface::create_attribute;

      HF::Attributes::IAttribute *attr           = nullptr;

      HF::Attributes::Attribute <uint16_t> *temp = nullptr;

      attr = factory (TestInterface::ATTR1);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0xAABB);

      entry.add (attr);

      attr = factory (TestInterface::ATTR2);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0xCCDD);

      entry.add (attr);

      attr = factory (TestInterface::ATTR3);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0xEEFF);

      entry.add (attr);

      report.add (entry);
   }

   void create_entry_2 ()
   {
      Report::Periodic::Entry entry;

      entry.unit     = 0x56;
      entry.itf.role = HF::Interface::SERVER_ROLE;
      entry.itf.id   = 0x05A5;

      HF::Attributes::Factory factory            = HF::Testing::TestInterface::create_attribute;

      HF::Attributes::IAttribute *attr           = nullptr;

      HF::Attributes::Attribute <uint16_t> *temp = nullptr;

      attr = factory (TestInterface::ATTR1);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x1234);

      entry.add (attr);

      attr = factory (TestInterface::ATTR2);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x5678);

      entry.add (attr);

      attr = factory (TestInterface::ATTR3);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x9ABC);

      entry.add (attr);

      report.add (entry);
   }

   void create_entry_3 ()
   {
      Report::Periodic::Entry entry;

      entry.unit     = 0x57;
      entry.itf.role = HF::Interface::SERVER_ROLE;
      entry.itf.id   = 0x05A5;

      HF::Attributes::Factory factory            = HF::Testing::TestInterface::create_attribute;

      HF::Attributes::IAttribute *attr           = nullptr;

      HF::Attributes::Attribute <uint16_t> *temp = nullptr;

      attr = factory (TestInterface::ATTR1);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x4321);

      entry.add (attr);

      attr = factory (TestInterface::ATTR2);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x8765);

      entry.add (attr);

      attr = factory (TestInterface::ATTR3);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0xCBA9);

      entry.add (attr);

      report.add (entry);
   }
};

TEST (AttrReport_Report_Periodic, Size)
{
   LONGS_EQUAL (1, report.size ());

   create_entry_1 ();

   LONGS_EQUAL (1 + (1 + 2) + 1 + 3 * (1 + 2), report.size ());

   create_entry_2 ();

   LONGS_EQUAL (1 + 2 * ((1 + 2) + 1 + 3 * (1 + 2)), report.size ());

   create_entry_3 ();

   LONGS_EQUAL (1 + 3 * ((1 + 2) + 1 + 3 * (1 + 2)), report.size ());
};

TEST (AttrReport_Report_Periodic, Empty)
{
   ByteArray temp (report.size ());
   report.pack (temp);

   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;
   report.unpack (get_factory, temp);
}

TEST (AttrReport_Report_Periodic, Pack)
{
   create_entry_3 ();
   create_entry_2 ();
   create_entry_1 ();

   ByteArray result (expected.size ());

   report.type = AttributeReporting::PERIODIC;
   report.id   = 0x0A;

   LONGS_EQUAL (report.size (), report.pack (result, 3));

   CHECK_EQUAL (expected, result);
};

TEST (AttrReport_Report_Periodic, Unpack)
{
   create_entry_3 ();
   create_entry_2 ();
   create_entry_1 ();

   uint16_t size = report.size ();

   report = Report::Periodic ();

   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;

   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x03, std::distance (report.entries.begin (), report.entries.end ()));

   for (const auto &entry : report.entries)
   {
      LONGS_EQUAL (0x03, entry.attributes.size ());
   }
};

/*!
 * @test Test the attribute reporting event report unpack method,
 * with enough data to match the expected report and keep adding more data
 * to check parsing keeps working.
 */
TEST (AttrReport_Report_Periodic, Unpack2)
{
   expected.push_back (0x02);

   create_entry_3 ();
   create_entry_2 ();
   create_entry_1 ();

   uint16_t size = report.size ();

   report = Report::Periodic ();

   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;

   size += Report::Entry::min_size;
   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x04, std::distance (report.entries.begin (), report.entries.end ()));

   LONGS_EQUAL (0x00, report.entries.front ().attributes.size ());

   report = Report::Periodic ();

   // Add extra bytes : Attribute UID.
   expected.push_back (TestInterface::ATTR2);

   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x04, std::distance (report.entries.begin (), report.entries.end ()));

   LONGS_EQUAL (0x00, report.entries.front ().attributes.size ());

   report = Report::Periodic ();

   // Add extra bytes : Attribute value incomplete.
   expected.push_back (0xEE);

   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x04, std::distance (report.entries.begin (), report.entries.end ()));

   LONGS_EQUAL (0x00, report.entries.front ().attributes.size ());

   report = Report::Periodic ();

   // Add extra bytes : Attribute value complete.
   expected.push_back (0xEE);

   size += sizeof(uint8_t) + sizeof(uint16_t);
   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x04, std::distance (report.entries.begin (), report.entries.end ()));

   LONGS_EQUAL (0x01, report.entries.front ().attributes.size ());
};

// =============================================================================
// AttributeReporting::Report::Event
// =============================================================================

TEST_GROUP (AttrReport_Report_Event_Field)
{
   Report::Event::Field field;
   ByteArray expected;

   TEST_SETUP ()
   {
      field    = Report::Event::Field ();

      expected = {0x00,                           0x00, 0x00,
                  TestInterface::ATTR1,
                  AttributeReporting::Event::COV,
                  0x12,                           0x34,
                  0x00,                           0x00, 0x00};
   }

   void add_attribute ()
   {
      HF::Attributes::Factory factory            = HF::Testing::TestInterface::create_attribute;

      HF::Attributes::IAttribute *attr           = nullptr;

      HF::Attributes::Attribute <uint16_t> *temp = nullptr;

      attr = factory (TestInterface::ATTR1);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x1234);

      field.set_attribute (attr);
   }
};

TEST (AttrReport_Report_Event_Field, Size)
{
   add_attribute ();

   LONGS_EQUAL (1 + 1 + 2, field.size ());
}

TEST (AttrReport_Report_Event_Field, Empty)
{
   // Field require an attribute.
   add_attribute ();

   ByteArray temp (field.size ());
   field.pack (temp);

   HF::Attributes::Factory factory = TestInterface::create_attribute;
   field.unpack (factory, temp);
}

TEST (AttrReport_Report_Event_Field, Pack)
{
   add_attribute ();

   ByteArray result (expected.size ());

   LONGS_EQUAL (field.size (), field.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Report_Event_Field, Unpack)
{
   HF::Attributes::Factory factory = TestInterface::create_attribute;

   LONGS_EQUAL (4, field.unpack (factory, expected, 3));

   LONGS_EQUAL (AttributeReporting::Event::COV, field.type);
   LONGS_EQUAL (TestInterface::ATTR1, field.attribute->uid ());

   HF::Attributes::Attribute <uint16_t> *temp = (HF::Attributes::Attribute <uint16_t> *)field.attribute.get ();

   LONGS_EQUAL (0x1234, temp->get ())
}

TEST_GROUP (AttrReport_Report_Event_Entry)
{
   Report::Event::Entry entry;
   ByteArray expected;

   TEST_SETUP ()
   {
      entry    = Report::Event::Entry ();

      expected = {0x00,                           0x00, 0x00,
                  0x55,                                 // Unit ID.
                  0x85,                           0xA5, // Interface UID.
                  0x03,                                 // Number of attributes.
                  TestInterface::ATTR1,
                  AttributeReporting::Event::COV,
                  0x12,                           0x34,
                  TestInterface::ATTR2,
                  AttributeReporting::Event::EQ,
                  0x56,                           0x78,
                  TestInterface::ATTR3,
                  AttributeReporting::Event::HT,
                  0x9A,                           0xBC,
                  0x00,                           0x00, 0x00};
   }

   void add_field (AttributeReporting::Event::Type type, uint8_t uid, uint16_t value)
   {
      Report::Event::Field field;

      field.type = type;

      HF::Attributes::Factory factory            = HF::Testing::TestInterface::create_attribute;

      HF::Attributes::IAttribute *attr           = nullptr;

      HF::Attributes::Attribute <uint16_t> *temp = nullptr;

      attr = factory (uid);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (value);

      field.set_attribute (attr);

      entry.add (field);
   }

   void check_field (uint8_t index, AttributeReporting::Event::Type type, uint8_t uid,
                     uint16_t value, const char *fileName, int lineNumber)
   {
      check_index (type, entry.fields[index].type, index, "Field Type", fileName, lineNumber);

      check_index (uid, entry.fields[index].attribute->uid (), index, "Field Attr UID",
                   fileName, lineNumber);

      HF::Attributes::Attribute <uint16_t> *temp =
         (HF::Attributes::Attribute <uint16_t> *)entry.fields[index].attribute.get ();

      check_index (value, temp->get (), index, "Field Attr Value", fileName, lineNumber);
   }
};

#define CHECK_FIELD(__index, __type, __uid, __value) \
   check_field (__index, __type, __uid, __value, __FILE__, __LINE__)

TEST (AttrReport_Report_Event_Entry, Size)
{
   LONGS_EQUAL (1 + 2 + 1, entry.size ());

   add_field (AttributeReporting::Event::COV, TestInterface::ATTR1, 0x1234);

   LONGS_EQUAL (1 + 2 + 1 + (1 + 1 + 2), entry.size ());

   add_field (AttributeReporting::Event::EQ, TestInterface::ATTR2, 0x5678);

   LONGS_EQUAL (1 + 2 + 1 + 2 * (1 + 1 + 2), entry.size ());

   add_field (AttributeReporting::Event::HT, TestInterface::ATTR3, 0x9ABC);

   LONGS_EQUAL (1 + 2 + 1 + 3 * (1 + 1 + 2), entry.size ());
}

TEST (AttrReport_Report_Event_Entry, Empty)
{
   ByteArray temp (entry.size ());
   entry.pack (temp);

   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;
   entry.unpack (get_factory, temp);
}

TEST (AttrReport_Report_Event_Entry, Pack)
{
   entry.unit     = 0x55;
   entry.itf.id   = 0x05A5;
   entry.itf.role = HF::Interface::SERVER_ROLE;

   add_field (AttributeReporting::Event::COV, TestInterface::ATTR1, 0x1234);
   add_field (AttributeReporting::Event::EQ, TestInterface::ATTR2, 0x5678);
   add_field (AttributeReporting::Event::HT, TestInterface::ATTR3, 0x9ABC);

   ByteArray result (expected.size ());

   LONGS_EQUAL (entry.size (), entry.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Report_Event_Entry, Unpack)
{
   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;
   LONGS_EQUAL (1 + 2 + 1 + 3 * (1 + 1 + 2), entry.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x55, entry.unit);
   LONGS_EQUAL (0x05A5, entry.itf.id);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, entry.itf.role);

   CHECK_FIELD (0, AttributeReporting::Event::COV, TestInterface::ATTR1, 0x1234);
   CHECK_FIELD (1, AttributeReporting::Event::EQ, TestInterface::ATTR2, 0x5678);
   CHECK_FIELD (2, AttributeReporting::Event::HT, TestInterface::ATTR3, 0x9ABC);
}

TEST_GROUP (AttrReport_Report_Event)
{
   Report::Event report;
   Common::ByteArray expected;

   TEST_SETUP ()
   {
      report   = Report::Event ();

      expected = {0x00,                 0x00, 0x00,
                  0x8A,                       // Report ID.
                                              // Entry 1
                  0x55,                       // Unit ID.
                  0x85,                 0xA5, // Interface UID.
                  0x03,                       // Number of Fields.
                  TestInterface::ATTR1,
                  Event::COV,
                  0xAA,                 0xBB,
                  TestInterface::ATTR2,
                  Event::HT,
                  0xCC,                 0xDD,
                  TestInterface::ATTR3,
                  Event::LT,
                  0xEE,                 0xFF,
                                              // Entry 2
                  0x56,                       // Unit ID.
                  0x85,                 0xA5, // Interface UID.
                  0x03,                       // Number of fields.
                  TestInterface::ATTR1,
                  Event::COV,
                  0x12,                 0x34,
                  TestInterface::ATTR2,
                  Event::HT,
                  0x56,                 0x78,
                  TestInterface::ATTR3,
                  Event::LT,
                  0x9A,                 0xBC,
                                              // Entry 3
                  0x57,                       // Unit ID.
                  0x85,                 0xA5, // Interface UID.
                  0x03,                       // Number of fields.
                  TestInterface::ATTR1,
                  Event::COV,
                  0x43,                 0x21,
                  TestInterface::ATTR2,
                  Event::HT,
                  0x87,                 0x65,
                  TestInterface::ATTR3,
                  Event::LT,
                  0xCB,                 0xA9,
                  0x00,                 0x00, 0x00};
   }

   TEST_TEARDOWN ()
   {}

   void create_entry_1 ()
   {
      Report::Event::Entry entry;

      entry.unit     = 0x55;
      entry.itf.role = HF::Interface::SERVER_ROLE;
      entry.itf.id   = 0x05A5;

      HF::Attributes::Factory factory            = HF::Testing::TestInterface::create_attribute;

      HF::Attributes::IAttribute *attr           = nullptr;

      HF::Attributes::Attribute <uint16_t> *temp = nullptr;

      attr = factory (TestInterface::ATTR1);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0xAABB);

      Report::Event::Field field;
      field.type = Event::COV;
      field.set_attribute (attr);

      entry.add (field);

      attr = factory (TestInterface::ATTR2);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0xCCDD);

      field.type = Event::HT;
      field.set_attribute (attr);

      entry.add (field);

      attr = factory (TestInterface::ATTR3);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0xEEFF);

      field.type = Event::LT;
      field.set_attribute (attr);

      entry.add (field);

      report.add (entry);
   }

   void create_entry_2 ()
   {
      Report::Event::Entry entry;

      entry.unit     = 0x56;
      entry.itf.role = HF::Interface::SERVER_ROLE;
      entry.itf.id   = 0x05A5;

      HF::Attributes::Factory factory            = HF::Testing::TestInterface::create_attribute;

      HF::Attributes::IAttribute *attr           = nullptr;

      HF::Attributes::Attribute <uint16_t> *temp = nullptr;

      attr = factory (TestInterface::ATTR1);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x1234);

      Report::Event::Field field;
      field.type = Event::COV;
      field.set_attribute (attr);

      entry.add (field);

      attr = factory (TestInterface::ATTR2);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x5678);

      field.type = Event::HT;
      field.set_attribute (attr);

      entry.add (field);

      attr = factory (TestInterface::ATTR3);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x9ABC);

      field.type = Event::LT;
      field.set_attribute (attr);

      entry.add (field);

      report.add (entry);
   }

   void create_entry_3 ()
   {
      Report::Event::Entry entry;

      entry.unit     = 0x57;
      entry.itf.role = HF::Interface::SERVER_ROLE;
      entry.itf.id   = 0x05A5;

      HF::Attributes::Factory factory            = HF::Testing::TestInterface::create_attribute;

      HF::Attributes::IAttribute *attr           = nullptr;

      HF::Attributes::Attribute <uint16_t> *temp = nullptr;

      attr = factory (TestInterface::ATTR1);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x4321);

      Report::Event::Field field;
      field.type = Event::COV;
      field.set_attribute (attr);

      entry.add (field);

      attr = factory (TestInterface::ATTR2);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0x8765);

      field.type = Event::HT;
      field.set_attribute (attr);

      entry.add (field);

      attr = factory (TestInterface::ATTR3);
      temp = (HF::Attributes::Attribute <uint16_t> *)attr;
      temp->set (0xCBA9);

      field.type = Event::LT;
      field.set_attribute (attr);

      entry.add (field);

      report.add (entry);
   }
};

TEST (AttrReport_Report_Event, Size)
{
   LONGS_EQUAL (1, report.size ());

   create_entry_1 ();

   LONGS_EQUAL (1 + (1 + 2) + 1 + 3 * (1 + 1 + 2), report.size ());

   create_entry_2 ();

   LONGS_EQUAL (1 + 2 * ((1 + 2) + 1 + 3 * (1 + 1 + 2)), report.size ());

   create_entry_3 ();

   LONGS_EQUAL (1 + 3 * ((1 + 2) + 1 + 3 * (1 + 1 + 2)), report.size ());
};

TEST (AttrReport_Report_Event, Empty)
{
   ByteArray temp (report.size ());
   report.pack (temp);

   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;
   report.unpack (get_factory, temp);
}

TEST (AttrReport_Report_Event, Pack)
{
   report.type = AttributeReporting::EVENT;
   report.id   = 0x0A;

   create_entry_3 ();
   create_entry_2 ();
   create_entry_1 ();

   ByteArray result (expected.size ());

   LONGS_EQUAL (report.size (), report.pack (result, 3));

   CHECK_EQUAL (expected, result);
};

/*!
 * @test Test the attribute reporting event report unpack method,
 * with enough data to match the expected report.
 */
TEST (AttrReport_Report_Event, Unpack)
{
   create_entry_3 ();
   create_entry_2 ();
   create_entry_1 ();

   uint16_t size = report.size ();

   report = Report::Event ();

   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;

   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x03, std::distance (report.entries.begin (), report.entries.end ()));

   for (const auto &entry : report.entries)
   {
      LONGS_EQUAL (0x03, entry.fields.size ());
   }
};

/*!
 * @test Test the attribute reporting event report unpack method,
 * with enough data to match the expected report and keep adding more data
 * to check parsing keeps working.
 */
TEST (AttrReport_Report_Event, Unpack2)
{
   // Add extra byte.
   expected.push_back (0x02);

   create_entry_3 ();
   create_entry_2 ();
   create_entry_1 ();

   uint16_t size = report.size ();

   report = Report::Event ();

   HF::Attributes::FactoryGetter get_factory = HF::Testing::FactoryGetter;

   LONGS_EQUAL (size + Report::Entry::min_size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x04, std::distance (report.entries.begin (), report.entries.end ()));

   LONGS_EQUAL (0x00, report.entries.front ().fields.size ());

   report = Report::Event ();

   // Add extra bytes : Invalid field.
   expected.push_back (TestInterface::ATTR2);

   size += Report::Entry::min_size;
   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x04, std::distance (report.entries.begin (), report.entries.end ()));

   LONGS_EQUAL (0x00, report.entries.front ().fields.size ());

   report = Report::Event ();

   expected.push_back (Event::LT);

   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x04, std::distance (report.entries.begin (), report.entries.end ()));

   LONGS_EQUAL (0x00, report.entries.front ().fields.size ());

   report = Report::Event ();

   expected.push_back (0xEE);

   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x04, std::distance (report.entries.begin (), report.entries.end ()));

   LONGS_EQUAL (0x00, report.entries.front ().fields.size ());

   report = Report::Event ();

   expected.push_back (0xEE);

   // Add field size and attribute value size to read size expected value.
   size += Report::Event::Field::min_size + sizeof(uint16_t);
   LONGS_EQUAL (size, report.unpack (get_factory, expected, 3));

   LONGS_EQUAL (0x04, std::distance (report.entries.begin (), report.entries.end ()));

   LONGS_EQUAL (0x01, report.entries.front ().fields.size ());
};

// =============================================================================
// Message API
// =============================================================================

TEST_GROUP (AttrReport_Report_CreateMessage)
{
   Report::CreateMessage message;
   ByteArray expected;

   TEST_SETUP ()
   {
      message  = Report::CreateMessage ();

      expected = {0x00, 0x00, 0x00,
                  0x8A, 0x5A, // Device Address.
                  0xBB,       // Device unit.
                  0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Report_CreateMessage, Size)
{
   LONGS_EQUAL (2 + 1, message.size ());
}

TEST (AttrReport_Report_CreateMessage, Empty)
{
   ByteArray temp (message.size ());
   message.pack (temp);
   message.unpack (temp);
}

TEST (AttrReport_Report_CreateMessage, Pack)
{
   message.destination.mod    = Protocol::Address::GROUP;
   message.destination.device = 0x0A5A;
   message.destination.unit   = 0xBB;

   ByteArray result (expected.size ());

   LONGS_EQUAL (message.size (), message.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Report_CreateMessage, Unpack)
{
   LONGS_EQUAL (message.size (), message.unpack (expected, 3));

   LONGS_EQUAL (Protocol::Address::GROUP, message.destination.mod);
   LONGS_EQUAL (0x0A5A, message.destination.device);
   LONGS_EQUAL (0xBB, message.destination.unit);
}

TEST_GROUP (AttrReport_Report_Periodic_CreateMessage)
{
   Report::Periodic::CreateMessage message;
   ByteArray expected;

   TEST_SETUP ()
   {
      message  = Report::Periodic::CreateMessage ();

      expected = {0x00, 0x00, 0x00,
                  0x8A, 0x5A, // Device Address.
                  0xBB,       // Device unit.
                  0xAA, 0xBB, 0xCC,0xDD,
                  0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Report_Periodic_CreateMessage, Size)
{
   LONGS_EQUAL (2 + 1 + 4, message.size ());
}

TEST (AttrReport_Report_Periodic_CreateMessage, Empty)
{
   ByteArray temp (message.size ());
   message.pack (temp);
   message.unpack (temp);
}

TEST (AttrReport_Report_Periodic_CreateMessage, Pack)
{
   message.destination.mod    = Protocol::Address::GROUP;
   message.destination.device = 0x0A5A;
   message.destination.unit   = 0xBB;
   message.interval           = 0xAABBCCDD;

   ByteArray result (expected.size ());

   LONGS_EQUAL (message.size (), message.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Report_Periodic_CreateMessage, Unpack)
{
   LONGS_EQUAL (message.size (), message.unpack (expected, 3));

   LONGS_EQUAL (Protocol::Address::GROUP, message.destination.mod);
   LONGS_EQUAL (0x0A5A, message.destination.device);
   LONGS_EQUAL (0xBB, message.destination.unit);
   LONGS_EQUAL (0xAABBCCDD, message.interval);
}

TEST_GROUP (AttrReport_Report_DeleteMessage)
{
   Report::DeleteMessage message;
   ByteArray expected;

   TEST_SETUP ()
   {
      message  = Report::DeleteMessage ();

      expected = {0x00, 0x00, 0x00,
                  0x8A, // Report identification.
                  0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Report_DeleteMessage, Size)
{
   LONGS_EQUAL (1, message.size ());
}

TEST (AttrReport_Report_DeleteMessage, Empty)
{
   ByteArray temp (message.size ());
   message.pack (temp);
   message.unpack (temp);
}

TEST (AttrReport_Report_DeleteMessage, Pack)
{
   message.report.type = Type::EVENT;
   message.report.id   = 0x0A;

   ByteArray result (expected.size ());

   LONGS_EQUAL (message.size (), message.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Report_DeleteMessage, Unpack)
{
   LONGS_EQUAL (message.size (), message.unpack (expected, 3));

   LONGS_EQUAL (Type::EVENT, message.report.type);
   LONGS_EQUAL (0x0A, message.report.id);
}

TEST_GROUP (AttrReport_Report_AddEntryMessage)
{
   struct TestMessage:public Report::AddEntryMessage
   {
      std::array <uint8_t, 4> entries;

      uint8_t count () const
      {
         return entries.size ();
      }

      uint16_t size () const
      {
         return Report::AddEntryMessage::size () + entries.size ();
      }

      uint16_t pack (Common::ByteArray &array, uint16_t offset = 0)
      {
         uint16_t start = offset;

         offset += Report::AddEntryMessage::pack (array, offset);

         /* *INDENT-OFF* */
         std::for_each (entries.begin (), entries.end (), [&array, &offset](uint8_t value)
         {
            offset += array.write (offset, value);
         });
         /* *INDENT-ON* */

         return offset - start;
      }

      uint16_t unpack_entry (const Common::ByteArray &array, uint16_t offset = 0)
      {
         static uint8_t count = 0;
         uint16_t start       = offset;

         offset += array.read (offset, entries[count++]);

         return offset - start;
      }
   };

   TestMessage message;
   ByteArray   expected;

   TEST_SETUP ()
   {
      message  = TestMessage ();

      expected = {0x00, 0x00, 0x00,
                  0x8A, // Report identification.
                  0x04, // Number of entries.
                  0x12, 0x34, 0x56,0x78,
                  0x00, 0x00, 0x00};
   }
};

TEST (AttrReport_Report_AddEntryMessage, Size)
{
   LONGS_EQUAL (1 + 1 + 4, message.size ());
}

TEST (AttrReport_Report_AddEntryMessage, Empty)
{
   ByteArray temp (message.size ());
   message.pack (temp);
   message.unpack (temp);
}

TEST (AttrReport_Report_AddEntryMessage, Pack)
{
   message.report.type = Type::EVENT;
   message.report.id   = 0x0A;

   message.entries[0]  = 0x12;
   message.entries[1]  = 0x34;
   message.entries[2]  = 0x56;
   message.entries[3]  = 0x78;

   ByteArray result (expected.size ());

   LONGS_EQUAL (message.size (), message.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Report_AddEntryMessage, Unpack)
{
   message.report.type = Type::EVENT;

   LONGS_EQUAL (message.size (), message.unpack (expected, 3));

   LONGS_EQUAL (Type::EVENT, message.report.type);
   LONGS_EQUAL (0x0A, message.report.id);

   LONGS_EQUAL (0x12, message.entries[0]);
   LONGS_EQUAL (0x34, message.entries[1]);
   LONGS_EQUAL (0x56, message.entries[2]);
   LONGS_EQUAL (0x78, message.entries[3]);
}


TEST_GROUP (AttrReport_Report_Periodic_AddEntryMessage)
{
   Report::Periodic::AddEntryMessage message;

   ByteArray expected;

   TEST_SETUP ()
   {
      message  = Report::Periodic::AddEntryMessage ();

      expected = {0x00,                            0x00, 0x00,
                  0x0A,                                  // Report ID
                  0x03,                                  // Number of entries.
                                                         // Entry 1
                  0x5A,                                  // Unit ID.
                  0x85,                            0x5A, // Interface.
                  HF::Attributes::Pack::MANDATORY,
                  // Entry 2
                  0x6A,                                  // Unit ID.
                  0x83,                            0xA5, // Interface.
                  HF::Attributes::Pack::ALL,
                  // Entry 3
                  0x7A,                                  // Unit ID.
                  0x83,                            0xEE, // Interface.
                  HF::Attributes::Pack::DYNAMIC,
                  0x04,                            0xD1, 0xD2,0xD3,0xD4,
                  0x00,                            0x00, 0x00};
   }
};

TEST (AttrReport_Report_Periodic_AddEntryMessage, Size)
{
   LONGS_EQUAL (1 + 1, message.size ());

   Periodic::Entry entry;

   message.add (entry);
   message.add (entry);
   message.add (entry);

   LONGS_EQUAL (1 + 1 + 3 * entry.size (), message.size ());
}

TEST (AttrReport_Report_Periodic_AddEntryMessage, Empty)
{
   ByteArray temp (message.size ());
   message.pack (temp);
   message.unpack (temp);
}


TEST (AttrReport_Report_Periodic_AddEntryMessage, Pack)
{
   ByteArray result (expected.size ());

   message.report.id = 0x0A;

   // NOTE : Entries are added to the front of the list.
   Periodic::Entry entry;

   entry.unit     = 0x7A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0x03EE;
   entry.pack_id  = HF::Attributes::Pack::DYNAMIC;
   entry.uids     = {0xD1, 0xD2, 0xD3, 0xD4};

   message.add (entry);

   entry.unit     = 0x6A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0x03A5;
   entry.pack_id  = HF::Attributes::Pack::ALL;

   message.add (entry);

   entry.unit     = 0x5A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.itf.id   = 0x055A;
   entry.pack_id  = HF::Attributes::Pack::MANDATORY;

   message.add (entry);

   LONGS_EQUAL (message.size (), message.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Report_Periodic_AddEntryMessage, Unpack)
{
   LONGS_EQUAL (1 + 1 + (1 + 2 + 1) + (1 + 2 + 1) + (1 + 2 + 1 + 1 + 4),
                message.unpack (expected, 3));

   LONGS_EQUAL (PERIODIC, message.report.type);
   LONGS_EQUAL (0x0A, message.report.id);

   LONGS_EQUAL (0x03, std::distance (message.begin (), message.end ()));
}

TEST_GROUP (AttrReport_Report_Event_AddEntryMessage)
{
   Report::Event::AddEntryMessage message;

   ByteArray expected;

   TEST_SETUP ()
   {
      message  = Report::Event::AddEntryMessage ();

      expected = {0x00, 0x00, 0x00,
                  0x8A,                          // Report ID
                  0x03,                          // Number of units.
                                                 // Entry 1
                  0x5A,                          // Unit ID.
                  0x80, 0xAA,                    // Interface : Type + UID.
                  HF::Attributes::Pack::DYNAMIC, // Attribute Pack ID.
                  0x01,                          // Number of fields.
                                                 // Entry 1 - Field 1.
                  0x10,                          // Attribute UID.
                  Event::COV,                    // Event Type.
                  0x33,                          // Event Value.
                                                 // Entry 2
                  0x5A,                          // Unit ID.
                  0x80, 0xAA,                    // Interface : Type + UID.
                  HF::Attributes::Pack::DYNAMIC, // Attribute Pack ID.
                  0x02,                          // Number of fields.
                                                 // Field 1.
                  0x11,                          // Attribute UID.
                  Event::HT,                     // Event Type.
                  0x01, 0xAA,                    // Event Value.
                                                 // Field 2.
                  0x12,                          // Attribute UID.
                  Event::LT,                     // Event Type.
                  0x01, 0x55,                    // Event Value.
                                                 // Entry 3
                  0x5A,                          // Unit ID.
                  0x80, 0xAA,                    // Interface : Type + UID.
                  HF::Attributes::Pack::ALL,     // Attribute Pack ID.
                  Event::COV,                    // Event Type.
                  0x88,                          // Event Value.
                  0x00, 0x00, 0x00};
   }

   Event::Entry create ()
   {
      Event::Entry entry;

      entry.unit     = 0x5A;
      entry.itf.role = HF::Interface::SERVER_ROLE;
      entry.itf.id   = 0xAA;
      entry.pack_id  = HF::Attributes::Pack::DYNAMIC;

      return entry;
   }

   uint16_t create_entry_1 ()
   {
      Event::Entry entry = create ();

      Event::Field field;
      field.attr_uid = 0x10;

      field.type     = Event::COV;
      field.value    = {0x33};

      entry.fields.push_back (field);

      message.add (entry);

      return entry.size ();
   }

   uint16_t create_entry_2 ()
   {
      Event::Entry entry = create ();

      Event::Field field;
      field.attr_uid = 0x11;

      field.type     = Event::HT;
      field.value    = {0xAA};

      entry.fields.push_back (field);

      field.attr_uid = 0x12;
      field.type     = Event::LT;
      field.value    = {0x55};

      entry.fields.push_back (field);

      message.add (entry);

      return entry.size ();
   }

   uint16_t create_entry_3 ()
   {
      Event::Entry entry = create ();

      entry.pack_id = HF::Attributes::Pack::ALL;

      Event::Field field;
      field       = Event::Field ();

      field.type  = Event::COV;
      field.value = {0x88};

      entry.fields.push_back (field);

      message.add (entry);

      return entry.size ();
   }

   void initialize ()
   {
      message.report.id = 0x0A;

      create_entry_3 ();
      create_entry_2 ();
      create_entry_1 ();
   }
};

TEST (AttrReport_Report_Event_AddEntryMessage, Size)
{
   uint16_t size = 1 + 1;

   LONGS_EQUAL (size, message.size ());

   // Add an entry.
   size += create_entry_1 ();

   LONGS_EQUAL (size, message.size ());

   // Add other entry.
   size += create_entry_2 ();

   LONGS_EQUAL (size, message.size ());

   // Add yet another entry.
   size += create_entry_2 ();

   LONGS_EQUAL (size, message.size ());
}

TEST (AttrReport_Report_Event_AddEntryMessage, Empty)
{
   ByteArray temp (message.size ());
   message.pack (temp);
   message.unpack (temp);
}

TEST (AttrReport_Report_Event_AddEntryMessage, Pack)
{
   ByteArray result (expected.size ());

   initialize ();

   LONGS_EQUAL (message.size (), message.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttrReport_Report_Event_AddEntryMessage, Unpack)
{
   initialize ();

   uint16_t size = message.size ();

   message = Report::Event::AddEntryMessage ();

   LONGS_EQUAL (size, message.unpack (expected, 3));

   LONGS_EQUAL (EVENT, message.report.type);
   LONGS_EQUAL (0x0A, message.report.id);

   LONGS_EQUAL (0x03, std::distance (message.begin (), message.end ()));
}

// =============================================================================
// AttributeReporting::Response
// =============================================================================

TEST_GROUP (AttributeReporting_Response)
{
   AttributeReporting::Response response;

   ByteArray expected;

   TEST_SETUP ()
   {
      response = AttributeReporting::Response ();

      expected = {0x00,                   0x00, 0x00,
                  Result::FAIL_RESOURCES,
                  0x8A,
                  0x00,                   0x00, 0x00};
   }
};

TEST (AttributeReporting_Response, Size)
{
   LONGS_EQUAL (1 + 1, response.size ());
}

TEST (AttributeReporting_Response, Empty)
{
   ByteArray temp (response.size ());
   response.pack (temp);
   response.unpack (temp);
}


TEST (AttributeReporting_Response, Pack)
{
   response.code        = Result::FAIL_RESOURCES;
   response.report.type = AttributeReporting::EVENT;
   response.report.id   = 0x0A;

   ByteArray result (expected.size ());

   LONGS_EQUAL (response.size (), response.pack (result, 3));

   CHECK_EQUAL (expected, result);
}

TEST (AttributeReporting_Response, Unpack)
{
   LONGS_EQUAL (response.size (), response.unpack (expected, 3));

   LONGS_EQUAL (Result::FAIL_RESOURCES, response.code);
   LONGS_EQUAL (AttributeReporting::EVENT, response.report.type);
   LONGS_EQUAL (0x0A, response.report.id);
}

// =============================================================================
// Service & Interface
// =============================================================================

// =============================================================================
// AttributeReporting - Tests
// =============================================================================

TEST_GROUP (AttributeReporting)
{};

TEST (AttributeReporting, CreateEventReport)
{
   Protocol::Address dst;

   dst.mod    = Protocol::Address::DEVICE;
   dst.device = 0x5A5A;
   dst.unit   = 0xDD;

   Protocol::Message *message = AttributeReporting::create (dst);

   CHECK_FALSE (message == nullptr);

   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, message->type);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, message->itf.role);
   LONGS_EQUAL (HF::Interface::ATTRIBUTE_REPORTING, message->itf.id);
   LONGS_EQUAL (AttributeReporting::CREATE_EVENT_CMD, message->itf.member);

   Report::Event::CreateMessage payload;
   payload.unpack (message->payload);

   LONGS_EQUAL (payload.destination.mod, Protocol::Address::DEVICE);
   LONGS_EQUAL (payload.destination.device, 0x5A5A);
   LONGS_EQUAL (payload.destination.unit, 0xDD);

   delete message;
}

TEST (AttributeReporting, CreatePeriodicReport)
{
   Protocol::Address dst;

   dst.mod    = Protocol::Address::DEVICE;
   dst.device = 0x5A5A;
   dst.unit   = 0xDD;

   Protocol::Message *message = AttributeReporting::create (dst, 0x12345678);

   CHECK_FALSE (message == nullptr);

   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, message->type);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, message->itf.role);
   LONGS_EQUAL (HF::Interface::ATTRIBUTE_REPORTING, message->itf.id);
   LONGS_EQUAL (AttributeReporting::CREATE_PERIODIC_CMD, message->itf.member);

   Report::Periodic::CreateMessage payload;
   payload.unpack (message->payload);

   LONGS_EQUAL (payload.destination.mod, Protocol::Address::DEVICE);
   LONGS_EQUAL (payload.destination.device, 0x5A5A);
   LONGS_EQUAL (payload.destination.unit, 0xDD);
   LONGS_EQUAL (payload.interval, 0x12345678);

   delete message;
}

TEST (AttributeReporting, DeleteReport)
{
   Reference report (PERIODIC, 0x55);

   Protocol::Message *message = AttributeReporting::destroy (report);

   CHECK_FALSE (message == nullptr);

   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, message->type);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, message->itf.role);
   LONGS_EQUAL (HF::Interface::ATTRIBUTE_REPORTING, message->itf.id);
   LONGS_EQUAL (AttributeReporting::DELETE_REPORT_CMD, message->itf.member);

   Report::DeleteMessage payload;
   payload.unpack (message->payload);

   LONGS_EQUAL (payload.report.type, PERIODIC);
   LONGS_EQUAL (payload.report.id, 0x55);

   delete message;
}

TEST (AttributeReporting, AddPeriodicEntry)
{
   std::vector <Periodic::Entry> entries (3);

   Reference report (EVENT, 0x55);

   Protocol::Message *message = AttributeReporting::add (report, entries.begin (), entries.end ());
   CHECK_TRUE (message == nullptr);

   report  = Reference (PERIODIC, 0x55);
   message = AttributeReporting::add (report, entries.begin (), entries.end ());

   CHECK_FALSE (message == nullptr);

   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, message->type);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, message->itf.role);
   LONGS_EQUAL (HF::Interface::ATTRIBUTE_REPORTING, message->itf.id);
   LONGS_EQUAL (AttributeReporting::ADD_PERIODIC_ENTRY_CMD, message->itf.member);

   Report::Periodic::AddEntryMessage payload;
   payload.unpack (message->payload);

   LONGS_EQUAL (payload.report.type, PERIODIC);
   LONGS_EQUAL (payload.report.id, 0x55);
   LONGS_EQUAL (0x03, std::distance (payload.begin (), payload.end ()));

   delete message;
}

TEST (AttributeReporting, AddEventEntry)
{
   std::vector <Event::Entry> entries (3);

   Reference report (PERIODIC, 0x55);

   Protocol::Message *message = AttributeReporting::add (report, entries.begin (), entries.end ());
   CHECK_TRUE (message == nullptr);

   report  = Reference (EVENT, 0x55);
   message = AttributeReporting::add (report, entries.begin (), entries.end ());

   CHECK_FALSE (message == nullptr);

   LONGS_EQUAL (Protocol::Message::COMMAND_REQ, message->type);
   LONGS_EQUAL (HF::Interface::SERVER_ROLE, message->itf.role);
   LONGS_EQUAL (HF::Interface::ATTRIBUTE_REPORTING, message->itf.id);
   LONGS_EQUAL (AttributeReporting::ADD_EVENT_ENTRY_CMD, message->itf.member);

   Report::Event::AddEntryMessage payload;
   payload.unpack (message->payload);

   LONGS_EQUAL (payload.report.type, EVENT);
   LONGS_EQUAL (payload.report.id, 0x55);
   LONGS_EQUAL (0x03, std::distance (payload.begin (), payload.end ()));

   delete message;
}

TEST_GROUP (AttributeReporting_Client)
{
   struct TestAttributeReportingClient:public InterfaceHelper <AttributeReporting::Client>
   {
      TestAttributeReportingClient():
         InterfaceHelper <AttributeReporting::Client>()
      {}

      void report (Type type, const Protocol::Address &address,
                   const Common::ByteArray &payload, uint16_t offset)
      {
         UNUSED (type);
         UNUSED (address);
         UNUSED (payload);
         UNUSED (offset);

         mock ("AttributeReporting::Client").actualCall ("report").withParameter ("type", type);
      }

      void created (const Protocol::Address &address,
                    const AttributeReporting::Response &response)
      {
         UNUSED (address);
         UNUSED (response);

         mock ("AttributeReporting::Client").actualCall ("created");
      }

      void added (const Protocol::Address &address,
                  const AttributeReporting::Response &response)
      {
         UNUSED (address);
         UNUSED (response);

         mock ("AttributeReporting::Client").actualCall ("added");
      }

      void deleted (const Protocol::Address &address,
                    const AttributeReporting::Response &response)
      {
         UNUSED (address);
         UNUSED (response);

         mock ("AttributeReporting::Client").actualCall ("deleted");
      }
   };

   TestAttributeReportingClient client;

   Protocol::Packet packet;

   TEST_SETUP ()
   {
      client                = TestAttributeReportingClient ();

      packet                = Protocol::Packet ();

      packet.message.itf.id = HF::Interface::ATTRIBUTE_REPORTING;

      mock ().ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      mock ().clear ();
   }

   void create_response (uint8_t member)
   {
      AttributeReporting::Response response;
      response.code             = Common::Result::FAIL_UNKNOWN;
      response.report.type      = EVENT;
      response.report.id        = 0x5A;

      packet.message.itf.role   = HF::Interface::SERVER_ROLE;
      packet.message.type       = HF::Protocol::Message::COMMAND_RES;
      packet.message.payload    = ByteArray (response.size ());
      packet.message.length     = packet.message.payload.size ();
      packet.message.itf.member = member;

      response.pack (packet.message.payload);
   }
};

TEST (AttributeReporting_Client, Created_Periodic)
{
   create_response (CREATE_PERIODIC_CMD);

   mock ("AttributeReporting::Client").expectOneCall ("created");

   LONGS_EQUAL (Common::Result::OK, client.handle (packet, packet.message.payload, 0));

   mock ("AttributeReporting::Client").checkExpectations ();
}

TEST (AttributeReporting_Client, Created_Event)
{
   create_response (CREATE_EVENT_CMD);

   mock ("AttributeReporting::Client").expectOneCall ("created");

   LONGS_EQUAL (Common::Result::OK, client.handle (packet, packet.message.payload, 0));

   mock ("AttributeReporting::Client").checkExpectations ();
}

TEST (AttributeReporting_Client, Added_Periodic)
{
   create_response (ADD_PERIODIC_ENTRY_CMD);

   mock ("AttributeReporting::Client").expectOneCall ("added");

   LONGS_EQUAL (Common::Result::OK, client.handle (packet, packet.message.payload, 0));

   mock ("AttributeReporting::Client").checkExpectations ();
}

TEST (AttributeReporting_Client, Added_Event)
{
   create_response (ADD_EVENT_ENTRY_CMD);

   mock ("AttributeReporting::Client").expectOneCall ("added");

   LONGS_EQUAL (Common::Result::OK, client.handle (packet, packet.message.payload, 0));

   mock ("AttributeReporting::Client").checkExpectations ();
}

TEST (AttributeReporting_Client, Deleted)
{
   create_response (DELETE_REPORT_CMD);

   mock ("AttributeReporting::Client").expectOneCall ("deleted");

   LONGS_EQUAL (Common::Result::OK, client.handle (packet, packet.message.payload, 0));

   mock ("AttributeReporting::Client").checkExpectations ();
}

TEST (AttributeReporting_Client, Report_Periodic)
{
   Report::Periodic report;

   packet.message.itf.role   = HF::Interface::CLIENT_ROLE;
   packet.message.type       = HF::Protocol::Message::COMMAND_REQ;
   packet.message.payload    = ByteArray (report.size ());
   packet.message.length     = packet.message.payload.size ();
   packet.message.itf.member = PERIODIC_REPORT_CMD;

   report.pack (packet.message.payload);

   mock ("AttributeReporting::Client").expectOneCall ("report").withParameter ("type", PERIODIC);

   LONGS_EQUAL (Common::Result::OK, client.handle (packet, packet.message.payload, 0));

   mock ("AttributeReporting::Client").checkExpectations ();
}

TEST (AttributeReporting_Client, Report_Event)
{
   Report::Event report;

   packet.message.payload    = ByteArray (report.size ());
   packet.message.length     = packet.message.payload.size ();
   packet.message.itf.member = EVENT_REPORT_CMD;
   packet.message.type       = HF::Protocol::Message::COMMAND_REQ;

   report.pack (packet.message.payload);

   mock ("AttributeReporting::Client").expectOneCall ("report").withParameter ("type", EVENT);

   LONGS_EQUAL (Common::Result::OK, client.handle (packet, packet.message.payload, 0));

   mock ("AttributeReporting::Client").checkExpectations ();
}

// =============================================================================
// AttributeReporting::Server
// =============================================================================

TEST_GROUP (AttributeReporting_Server)
{
   Testing::Concentrator *base;
   AttributeReporting::Server *server;

   Testing::Unit *unit;

   TEST_SETUP ()
   {
      base   = new Testing::Concentrator ();
      server = new AttributeReporting::Server (*base->unit0 ());

      base->unit0 ()->attribute_reporting (server);

      unit = new Testing::Unit (1, *base);

      mock ().ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      delete unit;
      delete base;

      mock ().clear ();
   }

   void setup_event_rule (Event::Type type)
   {
      Event::Field field;
      Event::Rule  rule;
      Event::Entry entry;

      field.attr_uid = TestInterface::ATTR1;
      field.type     = type;
      field.value    = {0x12, 0x34, 0x56, 0x78};

      entry.itf.id   = 0x7ABC;
      entry.pack_id  = HF::Attributes::DYNAMIC;
      entry.unit     = 1;

      entry.fields.push_back (field);

      rule.report.id = 0x5A;
      rule.add (entry);

      server->event_rules.push_front (rule);
   }

   void check_event_report (const char *file, int line)
   {
      auto packet = base->packets.front ();

      Report::Event report;
      report.unpack (HF::Testing::FactoryGetter, packet->message.payload, 0);

      LONGS_EQUAL_LOCATION (0x5A, report.id, file, line);
      LONGS_EQUAL_LOCATION (EVENT, report.type, file, line);
      LONGS_EQUAL_LOCATION (1, std::distance (report.entries.begin (), report.entries.end ()), file, line)

      auto &entry2 = *report.entries.begin ();

      LONGS_EQUAL_LOCATION (1, entry2.unit, file, line);
      CHECK_EQUAL_LOCATION (0x7ABC, entry2.itf.id, file, line);

      LONGS_EQUAL_LOCATION (1, entry2.fields.size (), file, line);
   }
};

TEST (AttributeReporting_Server, Periodic)
{
   Periodic::Rule  rule (50);
   Periodic::Entry entry;

   entry.itf.id   = 0x5A5A;
   entry.itf.role = HF::Interface::SERVER_ROLE;
   entry.pack_id  = HF::Attributes::MANDATORY;
   entry.unit     = 1;

   rule.report.id = 0x5A;
   rule.add (entry);

   unit->attr3 = 0x1234;

   server->periodic_rules.push_front (rule);

   LONGS_EQUAL (0, base->packets.size ());

   server->periodic (10);

   LONGS_EQUAL (0, base->packets.size ());

   server->periodic (60);

   LONGS_EQUAL (1, base->packets.size ());

   // Check report.
   auto packet = base->packets.front ();

   Report::Periodic report;
   report.unpack (HF::Testing::FactoryGetter, packet->message.payload, 0);

   LONGS_EQUAL (0x5A, report.id);
   LONGS_EQUAL (PERIODIC, report.type);
   LONGS_EQUAL (1, std::distance (report.entries.begin (), report.entries.end ()))

   auto &entry2 = *report.entries.begin ();

   LONGS_EQUAL (entry.unit, entry2.unit);
   CHECK_EQUAL (entry.itf, entry2.itf);

   server->periodic (80);

   LONGS_EQUAL (1, base->packets.size ());
}

#define CHECK_EVENT_REPORT()   check_event_report (__FILE__, __LINE__)

TEST (AttributeReporting_Server, Event_Equal)
{
   setup_event_rule (Event::EQ);

   uint32_t old_value = 0x12345679;
   uint32_t new_value = 0x1234567A;

   HF::Attributes::Attribute <uint32_t &> old_attr (0x7ABC, TestInterface::ATTR1, old_value);
   HF::Attributes::Attribute <uint32_t &> new_attr (0x7ABC, TestInterface::ATTR1, new_value);

   server->notify (1, old_attr, new_attr);

   LONGS_EQUAL (0, base->packets.size ());

   new_value = 0x12345678;

   server->notify (1, old_attr, new_attr);

   LONGS_EQUAL (1, base->packets.size ());

   // Check report.
   CHECK_EVENT_REPORT ();
}

TEST (AttributeReporting_Server, Event_Lower)
{
   setup_event_rule (Event::LT);

   uint32_t old_value = 0x12345679;
   uint32_t new_value = 0x1234567A;

   HF::Attributes::Attribute <uint32_t &> old_attr (0x7ABC, TestInterface::ATTR1, old_value);
   HF::Attributes::Attribute <uint32_t &> new_attr (0x7ABC, TestInterface::ATTR1, new_value);

   server->notify (1, old_attr, new_attr);

   LONGS_EQUAL (0, base->packets.size ());

   new_value = 0x12345670;

   server->notify (1, old_attr, new_attr);

   LONGS_EQUAL (1, base->packets.size ());

   // Check report.
   CHECK_EVENT_REPORT ();
}

TEST (AttributeReporting_Server, Event_Upper)
{
   setup_event_rule (Event::HT);

   uint32_t old_value = 0x12345670;
   uint32_t new_value = 0x12345675;

   HF::Attributes::Attribute <uint32_t &> old_attr (0x7ABC, TestInterface::ATTR1, old_value);
   HF::Attributes::Attribute <uint32_t &> new_attr (0x7ABC, TestInterface::ATTR1, new_value);

   server->notify (1, old_attr, new_attr);

   LONGS_EQUAL (0, base->packets.size ());

   new_value = 0x1234567A;

   server->notify (1, old_attr, new_attr);

   LONGS_EQUAL (1, base->packets.size ());

   // Check report.
   CHECK_EVENT_REPORT ();
}

TEST (AttributeReporting_Server, Handle_Create_Periodic)
{
   Protocol::Address dst;

   dst.mod    = Protocol::Address::DEVICE;
   dst.device = 0x5A5A;
   dst.unit   = 0xDD;

   Protocol::Message *message = AttributeReporting::create (dst, 0x12345678);

   CHECK_FALSE (message == nullptr);

   Protocol::Packet packet (*message);

   packet.message.length = packet.message.payload.size ();

   delete message;

   // Create a rule entry.
   LONGS_EQUAL (Result::OK, server->handle (packet, packet.message.payload, 0));

   LONGS_EQUAL (1, server->count (AttributeReporting::PERIODIC));
   LONGS_EQUAL (1, base->packets.size ());

   auto resp_pkt = base->packets.back ();

   AttributeReporting::Response resp;
   resp.unpack (resp_pkt->message.payload, 0);

   LONGS_EQUAL (Result::OK, resp.code);
   LONGS_EQUAL (AttributeReporting::PERIODIC, resp.report.type);
   LONGS_EQUAL (1, resp.report.id);

   // Create another rule.

   LONGS_EQUAL (Result::OK, server->handle (packet, packet.message.payload, 0));

   LONGS_EQUAL (2, server->count (AttributeReporting::PERIODIC));
   LONGS_EQUAL (2, base->packets.size ());

   resp_pkt = base->packets.back ();

   resp.unpack (resp_pkt->message.payload, 0);

   LONGS_EQUAL (Result::OK, resp.code);
   LONGS_EQUAL (AttributeReporting::PERIODIC, resp.report.type);
   LONGS_EQUAL (2, resp.report.id);
}

TEST (AttributeReporting_Server, Handle_Create_Event)
{
   Protocol::Address dst;

   dst.mod    = Protocol::Address::DEVICE;
   dst.device = 0x5A5A;
   dst.unit   = 0xDD;

   Protocol::Message *message = AttributeReporting::create (dst);

   CHECK_FALSE (message == nullptr);

   Protocol::Packet packet (*message);

   packet.message.length = packet.message.payload.size ();

   delete message;

   // Create a rule entry.
   LONGS_EQUAL (Result::OK, server->handle (packet, packet.message.payload, 0));

   LONGS_EQUAL (1, server->count (AttributeReporting::EVENT));
   LONGS_EQUAL (1, base->packets.size ());

   auto resp_pkt = base->packets.back ();

   AttributeReporting::Response resp;
   resp.unpack (resp_pkt->message.payload, 0);

   LONGS_EQUAL (Result::OK, resp.code);
   LONGS_EQUAL (AttributeReporting::EVENT, resp.report.type);
   LONGS_EQUAL (1, resp.report.id);

   // Create another rule.

   LONGS_EQUAL (Result::OK, server->handle (packet, packet.message.payload, 0));

   LONGS_EQUAL (2, server->count (AttributeReporting::EVENT));
   LONGS_EQUAL (2, base->packets.size ());

   resp_pkt = base->packets.back ();

   resp.unpack (resp_pkt->message.payload, 0);

   LONGS_EQUAL (Result::OK, resp.code);
   LONGS_EQUAL (AttributeReporting::EVENT, resp.report.type);
   LONGS_EQUAL (2, resp.report.id);
}
