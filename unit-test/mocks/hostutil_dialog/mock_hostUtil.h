/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_hostUtil.h
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
#include "Core/RtxCore.h"
#include "ProjCfg.h"
#include "PortDef.h"
#include "Ros/RosCfg.h"
#include "RtxEai/RtxEai.h"

#include "HostUtil.h"
}

#include <gmock/gmock.h>

/* Module class declaration. */
class HostUtil
{
public:
   virtual ~HostUtil() {}
   virtual void ApiBuildInfoElement(ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType Ie, rsuint8 IeLength, rsuint8 *IeData) = 0;
   virtual void ApiFreeInfoElement(ApiInfoElementType **IeBlockPtr) = 0;
   virtual void ColaTask(const RosMailType *MailPtr) = 0;
   virtual EepromDataPtrType EepromReadByte(EepromDataAddressType uAddress) = 0;
   virtual void KeyFilterSetModeOneChar(KeyFilterModeType Mode) = 0;
   virtual void KeyboardFilterKeyboardInit(void) = 0;
   virtual void Las_BuildIe_ApiLasPinCode (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsuint8* PinCode) = 0;
   virtual void LocalMainAppTaskInit(void) = 0;
   virtual void LocalMainAppTask(RosMailType *MailPtr) = 0;
   virtual void RosTimerStart(RosTimerIdType TimerId, RsTimerTickType Value, const RosTimerConfigType* Config) = 0;
   virtual void RosTimerStop(RosTimerIdType TimerId) = 0;
   virtual uint8_t dialogHost_init( void ) = 0;
};


/* Module class implementaion. */
class MockHostUtil : public HostUtil
{
public:
   MOCK_METHOD5(ApiBuildInfoElement ,  void(ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType Ie, rsuint8 IeLength, rsuint8 *IeData));
   MOCK_METHOD1(ApiFreeInfoElement ,  void(ApiInfoElementType **IeBlockPtr));
   MOCK_METHOD1(ColaTask ,  void(const RosMailType *MailPtr));
   MOCK_METHOD1(EepromReadByte ,  EepromDataPtrType(EepromDataAddressType uAddress));
   MOCK_METHOD1(KeyFilterSetModeOneChar ,  void(KeyFilterModeType Mode));
   MOCK_METHOD0(KeyboardFilterKeyboardInit ,  void());
   MOCK_METHOD4(Las_BuildIe_ApiLasPinCode  , void(ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsuint8* PinCode));
   MOCK_METHOD0(LocalMainAppTaskInit, void( void ));
   MOCK_METHOD1(LocalMainAppTask ,  void(RosMailType *MailPtr));
   MOCK_METHOD3(RosTimerStart ,  void(RosTimerIdType TimerId, RsTimerTickType Value, const RosTimerConfigType* Config));
   MOCK_METHOD1(RosTimerStop ,  void(RosTimerIdType TimerId));
   MOCK_METHOD0(dialogHost_init , uint8_t( void ));
};

void setMockHostUtilReference(HostUtil *ref);
