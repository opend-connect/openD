/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_util.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

#include <gmock/gmock.h>

extern "C"{

}

#include "mock_util.h"

/* Module pointer. */
Util *g_Util;

extern "C"{

void* itos(rsuint8 i, void *buf ) {
   assert(g_Util != NULL);
   return g_Util->itos( i, buf);
} /* void itos */

rsuint8 util_memcmp(const void *Ptr1, const void *Ptr2, rsuint8 len) {
   assert(g_Util != NULL);
   return g_Util->util_memcmp( Ptr1, Ptr2, len);
} /* rsuint8 util_memcmp */

void* util_memcpy(void *dst, const void *src, rsuint8 len) {
   assert(g_Util != NULL);
   return g_Util->util_memcpy( dst, src, len);
} /* void util_memcpy */

void* util_memset(void *dst, rsuint8 c, rsuint8 n) {
   assert(g_Util != NULL);
   return g_Util->util_memset( dst, c, n);
} /* void util_memset */

} /* extern */

void setMockUtilPointer(Util *UtilParam) {
   g_Util = UtilParam;
}

