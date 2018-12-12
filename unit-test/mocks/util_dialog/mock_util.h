/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_util.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

extern "C"{
#include <Core/RtxCore.h>
// #include <Ros/RosCfg.h>
}

/* Module class declaration. */
class Util
{
public:
   virtual ~Util() {}
   virtual void *itos(rsuint8 i, void *buf ) = 0;
   virtual rsuint8 util_memcmp(const void *Ptr1, const void *Ptr2, rsuint8 len) = 0;
   virtual void *util_memcpy(void *dst, const void *src, rsuint8 len) = 0;
   virtual void *util_memset(void *dst, rsuint8 c, rsuint8 n) = 0;
};


/* Module class implementaion. */
class MockUtil : public Util
{
public:
   MOCK_METHOD2(itos, void*(rsuint8 i, void *buf ));
   MOCK_METHOD3(util_memcmp, rsuint8 (const void *Ptr1, const void *Ptr2, rsuint8 len));
   MOCK_METHOD3(util_memcpy, void*(void *dst, const void *src, rsuint8 len));
   MOCK_METHOD3(util_memset, void*(void *dst, rsuint8 c, rsuint8 n));
};

void setMockUtilReference(Util *ref);
