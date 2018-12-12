/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_rosMail.cpp
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

#include "mock_rosMail.h"

extern "C"{
#include "RosMails.h"
}

/* Module pointer. */
RosMail *g_RosMail;

extern "C"{

RosMailType* RosMailAllocate(RosTaskIdType Src, RosTaskIdType Dst, RosMailSizeType Size) {
   assert(g_RosMail != NULL);
   return g_RosMail->RosMailAllocate( Src, Dst, Size);
} /* RosMailAllocate */

void RosMailFree(RosMailType* Mail){
   assert(g_RosMail != NULL);
   g_RosMail->RosMailFree(Mail);
}/* RosMailFree */

void RosMailDeliver(RosMailType* Mail) {
   assert(g_RosMail != NULL);
   g_RosMail->RosMailDeliver( Mail);
} /* RosMailDeliver */

RosMailSizeType RosMailGetSize(const RosMailType* Mail) {
   assert(g_RosMail != NULL);
   return g_RosMail->RosMailGetSize( Mail);
} /* RosMailGetSize */

void RosMailSendCopy(RosTaskIdType Src, RosTaskIdType Dst, const RosMailType* Mail, RosMailSizeType Size) {
   assert(g_RosMail != NULL);
   g_RosMail->RosMailSendCopy( Src, Dst, Mail, Size);
} /* RosMailSendCopy */

void RosMailSendP0(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive) {
   assert(g_RosMail != NULL);
   g_RosMail->RosMailSendP0( Src, Dst, Primitive);
} /* RosMailSendP0 */

void RosMailSendP1(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1) {
   assert(g_RosMail != NULL);
   g_RosMail->RosMailSendP1( Src, Dst, Primitive, P1);
} /* RosMailSendP1 */

void RosMailSendP2(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2) {
   assert(g_RosMail != NULL);
   g_RosMail->RosMailSendP2( Src, Dst, Primitive, P1, P2);
} /* RosMailSendP2 */

void RosMailSendP3(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2, rsuint8 P3) {
   assert(g_RosMail != NULL);
   g_RosMail->RosMailSendP3( Src, Dst, Primitive, P1, P2, P3);
} /* RosMailSendP3 */

void RosMailSendP4(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2, rsuint8 P3, rsuint8 P4) {
   assert(g_RosMail != NULL);
   g_RosMail->RosMailSendP4( Src, Dst, Primitive, P1, P2, P3, P4);
} /* RosMailSendP4 */

// void RosMailSetDst(RosMailType* Mail, RosTaskIdType Dst) {
//    assert(g_RosMail != NULL);
//    g_RosMail->RosMailSetDst( Mail, Dst);
// } /* RosMailSetDst */

// void RosMailSetSrc(RosMailType* Mail, RosTaskIdType Src) {
//    assert(g_RosMail != NULL);
//    g_RosMail->RosMailSetSrc( Mail, Src);
// } /* RosMailSetSrc */

} /* extern */

void setMockRosMailPointer(RosMail *RosMailParam) {
   g_RosMail = RosMailParam;
}

