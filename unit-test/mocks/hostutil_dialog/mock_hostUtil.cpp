/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_hostUtil.cpp
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

#include "mock_hostUtil.h"

/* Module pointer. */
HostUtil *g_HostUtil;

extern "C"{

void ApiBuildInfoElement(ApiInfoElementType **IeBlockPtr, rsuint16 *IeBlockLengthPtr, ApiIeType Ie, rsuint8 IeLength, rsuint8 *IeData) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->ApiBuildInfoElement( IeBlockPtr, IeBlockLengthPtr, Ie, IeLength, IeData);
} /* void ApiBuildInfoElement */

void ApiFreeInfoElement(ApiInfoElementType **IeBlockPtr) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->ApiFreeInfoElement( IeBlockPtr);
} /* void ApiFreeInfoElement */

void ColaTask(const RosMailType *MailPtr) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->ColaTask( MailPtr);
} /* void ColaTask */

EepromDataPtrType EepromReadByte(EepromDataAddressType uAddress) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->EepromReadByte( uAddress);
} /* EepromDataPtrType EepromReadByte */

void KeyFilterSetModeOneChar(KeyFilterModeType Mode) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->KeyFilterSetModeOneChar( Mode);
} /* void KeyFilterSetModeOneChar */

void KeyboardFilterKeyboardInit(void) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->KeyboardFilterKeyboardInit();
} /* void KeyboardFilterKeyboardInit */

void Las_BuildIe_ApiLasPinCode (ApiInfoElementType** IeBlockPtr, rsuint16* IeBlockLengthPtr, rsbool Editable, rsuint8* PinCode) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->Las_BuildIe_ApiLasPinCode( IeBlockPtr, IeBlockLengthPtr, Editable, PinCode);
} /* void Las_BuildIe_ApiLasPinCode  */

void LocalMainAppTaskInit(void){
    assert(g_HostUtil != NULL);
    return g_HostUtil->LocalMainAppTaskInit();
}

void LocalMainAppTask(RosMailType *MailPtr) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->LocalMainAppTask( MailPtr);
} /* void LocalMainAppTask */

void RosTimerStart(RosTimerIdType TimerId, RsTimerTickType Value, const RosTimerConfigType* Config) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->RosTimerStart( TimerId, Value, Config);
} /* void RosTimerStart */

void RosTimerStop(RosTimerIdType TimerId) {
   assert(g_HostUtil != NULL);
   return g_HostUtil->RosTimerStop( TimerId);
} /* void RosTimerStop */

uint8_t dialogHost_init( void ) {
    assert(g_HostUtil != NULL);
    g_HostUtil->dialogHost_init();
}

} /* */

void setMockHostUtilReference(HostUtil *ref) {
   g_HostUtil = ref;
}
