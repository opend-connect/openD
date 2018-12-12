// =============================================================================
/*!
 * @file       tests/test_common.cpp
 *
 * This file contains the implementation of the unit tests for the common
 * functions and classes for the HAN-FUN library.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================
#include <string>
#include <map>

#include "hanfun/common.h"
#include "hanfun/uids.h"

#include "hanfun/debug.h"

#include "test_helper.h"

using namespace HF;
using namespace HF::Common;

// =============================================================================
// Byte Array
// =============================================================================

TEST_GROUP (ByteArray)
{
   ByteArray *array;

   TEST_SETUP ()
   {
      array = new ByteArray (10);
   }

   TEST_TEARDOWN ()
   {
      delete array;
   }
};

TEST (ByteArray, Create)
{
   LONGS_EQUAL (10, array->size ());

   LONGS_EQUAL (10, array->capacity ());
}

TEST (ByteArray, Write_Byte)
{
   uint8_t value = 42;

   LONGS_EQUAL (sizeof(uint8_t), array->write (0, value));

   BYTES_EQUAL (value, (*array)[0]);

   LONGS_EQUAL (sizeof(uint8_t), array->write (5, value));

   BYTES_EQUAL (value, (*array)[5]);
}

TEST (ByteArray, Write_Word)
{
   uint16_t  value = 0x5AA5;

   ByteArray expected {0x5A, 0xA5, 0x00, 0x00, 0x00, 0x5A, 0xA5, 0x00, 0x00, 0x00};

   LONGS_EQUAL (sizeof(uint16_t), array->write (0, value));

   LONGS_EQUAL (sizeof(uint16_t), array->write (5, value));

   CHECK_EQUAL (expected, (*array));
}

TEST (ByteArray, Write_DWord)
{
   uint32_t  value = 0xFF5AA5CC;

   ByteArray expected {0xFF, 0x5A, 0xA5, 0xCC, 0x00, 0xFF, 0x5A, 0xA5, 0xCC, 0x00};

   LONGS_EQUAL (sizeof(uint32_t), array->write (0, value));

   LONGS_EQUAL (sizeof(uint32_t), array->write (5, value));

   CHECK_EQUAL (expected, (*array));
}

TEST (ByteArray, Other)
{
   array->extend (10);

   LONGS_EQUAL (10, array->size ());
   LONGS_EQUAL (20, array->capacity ());

   array->ensure (4, 5);
   LONGS_EQUAL (10, array->size ());
   array->ensure (7, 5);
   LONGS_EQUAL (12, array->size ());
   LONGS_EQUAL (20, array->capacity ());

   array->ensure (15, 5);
   LONGS_EQUAL (20, array->size ());
   LONGS_EQUAL (20, array->capacity ());
}

TEST_GROUP (ByteArray_Read)
{
   ByteArray array;

   TEST_SETUP ()
   {
      array = ByteArray {0x00, 0x00, 0x00, 0x00, 0xFF, 0x5A, 0xA5, 0xCC, 0x00, 0x00};
   }
};

TEST (ByteArray, Read_Byte)
{
   uint8_t temp;
   uint8_t value = 42;

   (*array)[5] = value;

   LONGS_EQUAL (sizeof(uint8_t), array->read (0, temp));

   LONGS_EQUAL (0, temp);

   LONGS_EQUAL (sizeof(uint8_t), array->read (5, temp));

   LONGS_EQUAL (value, temp);

   temp = 0;

   temp = (*array)[5];

   LONGS_EQUAL (value, temp);
}

TEST (ByteArray_Read, Word)
{
   uint16_t temp = 0xFF;

   LONGS_EQUAL (sizeof(uint16_t), array.read (0, temp));

   LONGS_EQUAL (0, temp);

   LONGS_EQUAL (sizeof(uint16_t), array.read (5, temp));

   LONGS_EQUAL (0x5AA5, temp);
}

TEST (ByteArray_Read, DWord)
{
   uint32_t temp = 0xBB;

   LONGS_EQUAL (sizeof(uint32_t), array.read (0, temp));

   LONGS_EQUAL (0, temp);

   LONGS_EQUAL (sizeof(uint32_t), array.read (4, temp));

   LONGS_EQUAL (0xFF5AA5CC, temp);
}


TEST (ByteArray_Read, Available)
{
   LONGS_EQUAL (10, array.available (0));
   LONGS_EQUAL (5, array.available (5));

   LONGS_EQUAL (1, array.available (9));
   LONGS_EQUAL (0, array.available (10));

   LONGS_EQUAL (0, array.available (11));

   CHECK_TRUE (array.available (0, 5));
   CHECK_TRUE (array.available (4, 5));

   CHECK_FALSE (array.available (6, 5));

   CHECK_FALSE (array.available (10, 1));
}

// =============================================================================
// HF::UID
// =============================================================================

TEST_GROUP (UID)
{};

TEST (UID, NONE)
{
   UID::NONE uid;

   LONGS_EQUAL (UID::NONE_UID, uid.type ());

   uint16_t size = uid.size ();

   LONGS_EQUAL (2, size);

   ByteArray expected {0xAA, 0xAA, 0xAA,
                       UID::NONE_UID,     // UID type.
                       0x00,              // UID size.
                       0xAA, 0xAA, 0xAA};

   ByteArray array (size + 6);

   for (int i = 0; i < 3; i++)
   {
      array[i] = 0xAA;
   }

   for (int i = 5; i < 8; i++)
   {
      array[i] = 0xAA;
   }

   uint16_t wsize = uid.pack (array, 3);
   LONGS_EQUAL (size, wsize);

   CHECK_EQUAL (expected, array);

   uint16_t rsize = uid.unpack (array, 3);
   LONGS_EQUAL (size, rsize);
}

TEST (UID, DECT)
{
   UID::DECT ipui;

   LONGS_EQUAL (UID::DECT_UID, ipui.type ());

   LONGS_EQUAL (5, UID::DECT::length ());

   uint16_t size = ipui.size ();

   LONGS_EQUAL (1 + 1 + 5, size);

   ByteArray expected {0x00, 0x00, 0x00,
                       UID::DECT_UID,                // UID type.
                       0x05,                         // UID size.
                       0x00, 0x73, 0x70, 0x5A, 0xA5, // DECT value.
                       0x00, 0x00, 0x00};

   ByteArray array (size + 6);

   ipui[0] = 0x00;
   ipui[1] = 0x73;
   ipui[2] = 0x70;
   ipui[3] = 0x5A;
   ipui[4] = 0xA5;

   uint16_t wsize = ipui.pack (array, 3);
   LONGS_EQUAL (size, wsize);

   CHECK_EQUAL (expected, array);

   ipui.fill (0xFF);

   uint16_t rsize = ipui.unpack (array, 3);
   LONGS_EQUAL (size, rsize);

   BYTES_EQUAL (0x00, ipui[0]);
   BYTES_EQUAL (0x73, ipui[1]);
   BYTES_EQUAL (0x70, ipui[2]);
   BYTES_EQUAL (0x5A, ipui[3]);
   BYTES_EQUAL (0xA5, ipui[4]);

   HF::UID::UID uid = HF::UID::UID( &ipui);
   std::stringstream ss;
   ss << uid;

   STRCMP_EQUAL (std::string ("dect: 0073705AA5").c_str (), ss.str ().c_str ());
}

TEST (UID, MAC)
{
   UID::MAC mac;

   LONGS_EQUAL (UID::MAC_UID, mac.type ());
   LONGS_EQUAL (6, UID::MAC::length ());

   uint16_t size = mac.size ();

   LONGS_EQUAL (1 + 1 + 6, size);

   ByteArray expected {0x00, 0x00, 0x00,
                       UID::MAC_UID,                       // UID type.
                       0x06,                               // UID size.
                       0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, // MAC value.
                       0x00, 0x00, 0x00};

   ByteArray array (size + 6);

   mac[0] = 0x12;
   mac[1] = 0x34;
   mac[2] = 0x56;
   mac[3] = 0x78;
   mac[4] = 0x9A;
   mac[5] = 0xBC;

   uint16_t wsize = mac.pack (array, 3);
   LONGS_EQUAL (size, wsize);

   CHECK_EQUAL (expected, array);

   mac.fill (0xFF);

   uint16_t rsize = mac.unpack (array, 3);
   LONGS_EQUAL (size, rsize);

   BYTES_EQUAL (0x12, mac[0]);
   BYTES_EQUAL (0x34, mac[1]);
   BYTES_EQUAL (0x56, mac[2]);
   BYTES_EQUAL (0x78, mac[3]);
   BYTES_EQUAL (0x9A, mac[4]);
   BYTES_EQUAL (0xBC, mac[5]);

   HF::UID::UID uid = HF::UID::UID( &mac);
   std::stringstream ss;
   ss << uid;

   STRCMP_EQUAL (std::string ("mac: 12:34:56:78:9A:BC").c_str (), ss.str ().c_str ());
}

TEST (UID, URI)
{
   std::string str = "Hello World !";
   UID::URI    uri (str);

   LONGS_EQUAL (UID::URI_UID, uri.type ());

   uint16_t size = uri.size ();

   LONGS_EQUAL (1 + 1 + str.length (), size);

   ByteArray expected {0x00, 0x00, 0x00,
                       UID::URI_UID, // UID type.
                       0x0D,         // UID size.
                       0x48,         // H
                       0x65,         // e
                       0x6c,         // l
                       0x6c,         // l
                       0x6f,         // o
                       0x20,         //
                       0x57,         // W
                       0x6f,         // o
                       0x72,         // r
                       0x6c,         // l
                       0x64,         // d
                       0x20,         //
                       0x21,         // !
                       0x00, 0x00, 0x00};

   ByteArray array (size + 6);

   uint16_t  wsize = uri.pack (array, 3);
   LONGS_EQUAL (size, wsize);

   CHECK_EQUAL (expected, array);

   uri = UID::URI ("");

   uint16_t rsize = uri.unpack (array, 3);
   LONGS_EQUAL (size, rsize);

   STRCMP_EQUAL ("Hello World !", uri.str ().c_str ())
}

TEST (UID, Equals)
{
   UID::UID_T *temp;

   UID::DECT  ipui;
   UID::DECT  ipui2;

   ipui[0] = 0x00;
   ipui[1] = 0x73;
   ipui[2] = 0x70;
   ipui[3] = 0xAA;
   ipui[4] = 0xBB;

   temp    = &ipui;
   ipui2   = ipui;

   CHECK_EQUAL (ipui, *temp);
   CHECK_EQUAL (ipui, ipui2);

   UID::MAC mac;
   UID::MAC mac2;

   mac[0] = 0x00;
   mac[1] = 0x73;
   mac[2] = 0x70;
   mac[3] = 0xAA;
   mac[4] = 0xBB;
   mac[5] = 0xCC;

   temp   = &mac;
   mac2   = mac;

   CHECK_EQUAL (mac, *temp);
   CHECK_EQUAL (mac, mac2);

   UID::URI uri ("sn://1234567890");
   UID::URI uri2;

   temp = &uri;
   uri2 = uri;

   CHECK_EQUAL (uri, *temp);
   CHECK_EQUAL (uri, uri2);
}

TEST (UID, NotEquals)
{
   UID::DECT ipui;
   UID::DECT ipui2;

   ipui[0]  = 0x00;
   ipui[1]  = 0x73;
   ipui[2]  = 0x70;
   ipui[3]  = 0xAA;
   ipui[4]  = 0xBB;

   ipui2    = ipui;

   ipui2[3] = 0xCC;

   CHECK_FALSE (ipui == ipui2);

   UID::MAC mac;
   UID::MAC mac2;

   mac[0]  = 0x00;
   mac[1]  = 0x73;
   mac[2]  = 0x70;
   mac[3]  = 0xAA;
   mac[4]  = 0xBB;
   mac[5]  = 0xCC;

   mac2    = mac;
   mac2[3] = 0xCC;

   CHECK_FALSE (mac == mac2);

   UID::URI uri ("sn://1234567890");
   UID::URI uri2 ("sn://0987654321");

   CHECK_FALSE (uri == uri2);
}

// =============================================================================
// Attributes
// =============================================================================

TEST_GROUP (Attributes)
{
   struct TestInterface:public Testing::InterfaceHelper <Testing::TestInterface>
   {};

   struct TestMeasure:public Serializable
   {
      uint8_t  type;
      uint16_t value;

      uint16_t size () const
      {
         return sizeof(type) + sizeof(value);
      }

      uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
      {
         uint16_t start = offset;

         offset += array.write (offset, type);
         offset += array.write (offset, value);

         return offset - start;
      }

      uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
      {
         uint16_t start = offset;

         offset += array.read (offset, type);
         offset += array.read (offset, value);

         return offset - start;
      }

      int compare (const TestMeasure &other) const
      {
         int res = type - other.type;

         if (res == 0)
         {
            res = value - other.value;
         }

         return res;
      }

      float changed (const TestMeasure &other) const
      {
         UNUSED (other);
         return 0.0;
      }
   };
};

TEST (Attributes, API)
{
   uint8_t  data  = 0x5A;
   uint16_t data2 = 0x5A50;
   uint32_t data3 = 0x5A50;

   TestInterface itf;
   HF::Attributes::Attribute <uint8_t &>  attr (itf.uid (), 0x5B, &itf, data);
   HF::Attributes::Attribute <uint16_t &> attr2 (itf.uid (), 0x5A, &itf, data2);
   HF::Attributes::Attribute <uint32_t &> attr3 (itf.uid (), 0x5C, &itf, data3);

   LONGS_EQUAL (data2, attr2.value ());

   data2 = 0x1234;

   LONGS_EQUAL (0x1234, attr2.value ());
   LONGS_EQUAL (0x1234, attr2.get ());

   LONGS_EQUAL (1, attr.size ());
   LONGS_EQUAL (2, attr2.size ());
   LONGS_EQUAL (4, attr3.size ());
}

TEST (Attributes, API2)
{
   TestMeasure data;

   TestInterface itf;
   HF::Attributes::Attribute <TestMeasure &> attr (itf.uid (), 0x5A, &itf, data, true);

   data.type  = 0x55;
   data.value = 0x5A5A;

   LONGS_EQUAL (data.type, attr.value ().type);
   LONGS_EQUAL (data.value, attr.value ().value);
}

TEST (Attributes, Serialize_Pack)
{
   Common::ByteArray expected {0x00, 0x00, 0x00,
                               0x12, 0x34,
                               0x00, 0x00, 0x00};

   uint16_t attr = 0x1234;

   TestInterface itf;
   HF::Attributes::Attribute <uint16_t &> attr_wrapper (itf.uid (), 0x5B, &itf, attr);

   Common::ByteArray result (expected.size ());

   std::fill (result.begin (), result.end (), 0);

   uint16_t w_size = attr_wrapper.pack (result, 3);
   LONGS_EQUAL (sizeof(attr), w_size);

   CHECK_EQUAL (expected, result);
}

TEST (Attributes, Serialize_Unpack)
{
   Common::ByteArray expected {0x00, 0x00, 0x00,
                               0x12, 0x34,
                               0x00, 0x00, 0x00};

   uint16_t attr = 0x6666;

   TestInterface itf;
   HF::Attributes::Attribute <uint16_t &> attr_wrapper (itf.uid (), 0x5B, &itf, attr);

   uint16_t r_size = attr_wrapper.unpack (expected, 3);
   LONGS_EQUAL (sizeof(attr), r_size);

   CHECK_EQUAL (0x1234, attr);
}

// =============================================================================
// Common::Interface
// =============================================================================

TEST_GROUP (Common_Interface)
{};

TEST (Common_Interface, Equals)
{
   Common::Interface itf1 (0x7F5A, HF::Interface::SERVER_ROLE);
   Common::Interface itf2 (0x7F5A, HF::Interface::SERVER_ROLE);

   CHECK_TRUE (itf1 == itf2);

   itf2.role = HF::Interface::CLIENT_ROLE;

   CHECK_FALSE (itf1 == itf2);

   itf2    = itf1;

   itf2.id = itf1.id - 1;

   CHECK_FALSE (itf1 == itf2);
}
