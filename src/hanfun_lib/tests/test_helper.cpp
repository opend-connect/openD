// =============================================================================
/*!
 * @file       tests/test_helper.cpp
 *
 * This file contains helper functions used the tests.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "CppUTest/CommandLineTestRunner.h"

#include "test_helper.h"

// =============================================================================
// Helper Functions
// =============================================================================

STRING_FROM (HF::Common::Interface)

SimpleString StringFrom (const std::vector <uint8_t> &array)
{
   SimpleString result = "";

   for (uint16_t i = 0; i < array.size (); i++)
   {
      result += StringFromFormat ("%02X ", array[i]);
   }

   return result;
}

SimpleString StringFrom (const HF::Common::Serializable &data)
{
   SimpleString result = "0x";

   Common::ByteArray array (data.size ());

   uint16_t size = data.pack (array);

   result += HexStringFrom ((long int) size);
   result += " : ";
   result += StringFrom (array);

   return result;
}

HF::Attributes::Factory HF::Testing::FactoryGetter (HF::Common::Interface itf)
{
   HF::Attributes::Factory result = HF::Attributes::get_factory (itf);

   if (result == nullptr)
   {
      result = TestInterface::create_attribute;
   }

   return result;
}

// =============================================================================
// Library Overrides
// =============================================================================

#if Backtrace_FOUND

extern const char *__progname;

void __assert_fail (const char *__assertion, const char *__file, unsigned int __line,
                    const char *__function)
{
   fprintf (stderr, "%s: %s:%d: %s Assertion `%s' failed.\n", __progname, __file, __line, __function, __assertion);
   // Backtrace.
   int nptrs;
#define SIZE   100
   void *buffer[100];

   nptrs = backtrace (buffer, SIZE);

   backtrace_symbols_fd (buffer, nptrs, STDERR_FILENO);

   abort ();
}

#endif

// =============================================================================
// Main
// =============================================================================

int main (int ac, char **av)
{
   return CommandLineTestRunner::RunAllTests (ac, av);
}
