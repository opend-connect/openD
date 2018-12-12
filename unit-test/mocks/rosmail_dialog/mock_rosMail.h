/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_rosMail.h
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
}

/* Module class declaration. */
class RosMail
{
public:
   virtual ~RosMail() {}
   virtual RosMailType* RosMailAllocate(RosTaskIdType Src, RosTaskIdType Dst, RosMailSizeType Size) = 0;
   virtual void RosMailFree(RosMailType* Mail) = 0;
   virtual void RosMailDeliver(RosMailType* Mail) = 0;
   virtual RosMailSizeType RosMailGetSize(const RosMailType* Mail) = 0;
   virtual RosTaskIdType RosMailGetSrc(const RosMailType* Mail) = 0;
   virtual void RosMailSendCopy(RosTaskIdType Src, RosTaskIdType Dst, const RosMailType* Mail, RosMailSizeType Size) = 0;
   virtual void RosMailSendP0(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive) = 0;
   virtual void RosMailSendP1(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1) = 0;
   virtual void RosMailSendP2(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2) = 0;
   virtual void RosMailSendP3(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2, rsuint8 P3) = 0;
   virtual void RosMailSendP4(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2, rsuint8 P3, rsuint8 P4) = 0;
   virtual void RosMailSetSrc(RosMailType* Mail, RosTaskIdType Src) = 0;
};


/* Module class implementaion. */
class MockRosMail : public RosMail
{
public:
   MOCK_METHOD3(RosMailAllocate ,  RosMailType*(RosTaskIdType Src, RosTaskIdType Dst, RosMailSizeType Size));
   MOCK_METHOD1(RosMailFree, void(RosMailType* Mail));
   MOCK_METHOD1(RosMailDeliver ,  void(RosMailType* Mail));
   MOCK_METHOD1(RosMailGetDst ,  RosTaskIdType(const RosMailType* Mail));
   MOCK_METHOD1(RosMailGetSize ,  RosMailSizeType(const RosMailType* Mail));
   MOCK_METHOD1(RosMailGetSrc ,  RosTaskIdType(const RosMailType* Mail));
   MOCK_METHOD4(RosMailSendCopy ,  void(RosTaskIdType Src, RosTaskIdType Dst, const RosMailType* Mail, RosMailSizeType Size));
   MOCK_METHOD3(RosMailSendP0 ,  void(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive));
   MOCK_METHOD4(RosMailSendP1 ,  void(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1));
   MOCK_METHOD5(RosMailSendP2 ,  void(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2));
   MOCK_METHOD6(RosMailSendP3 ,  void(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2, rsuint8 P3));
   MOCK_METHOD7(RosMailSendP4 ,  void(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2, rsuint8 P3, rsuint8 P4));
   MOCK_METHOD2(RosMailSetDst ,  void(RosMailType* Mail, RosTaskIdType Dst));
   MOCK_METHOD2(RosMailSetSrc ,  void(RosMailType* Mail, RosTaskIdType Src));
};

void setMockRosMailPointer(RosMail *RosMailParam);
