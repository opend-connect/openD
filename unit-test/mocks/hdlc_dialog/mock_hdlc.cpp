/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_hdlc.cpp
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

#include <gmock/gmock.h>

extern "C"{

}

#include "mock_hdlc.h"

/* Module pointer. */
Hdlc *g_Hdlc;

extern "C"{

int8_t hdlc_frameCreate( uint8_t *frameBuffer, uint16_t frameBufferSize, uint8_t taskId, uint8_t *payloadData, uint16_t payloadLength ) {
   assert(g_Hdlc != NULL);
   return g_Hdlc->hdlc_frameCreate( frameBuffer, frameBufferSize, taskId, payloadData, payloadLength);
} /* hdlc_frameCreate */

uint16_t hdlc_getFrameBufferLength( uint16_t payloadLength ) {
   assert(g_Hdlc != NULL);
   return g_Hdlc->hdlc_getFrameBufferLength( payloadLength);
} /* hdlc_getFrameBufferLength */

int8_t hdlc_init( hdlc_parsedPacketFct_t hdlc_parsedPacket, hdlc_allocateMemoryFct_t hdlc_allocateMemory, hdlc_freeMemoryFct_t hdlc_freeMemory, hdlc_sendSerialFct_t hdlc_sendSerial ) {
   assert(g_Hdlc != NULL);
   return g_Hdlc->hdlc_init( hdlc_parsedPacket, hdlc_allocateMemory, hdlc_freeMemory, hdlc_sendSerial);
} /* hdlc_init */

void hdlc_packetParseBytewise( uint8_t *data ) {
   assert(g_Hdlc != NULL);
   g_Hdlc->hdlc_packetParseBytewise( data);
} /* hdlc_packetParseBytewise */

} /* extern */

void setMockHdlcReference(Hdlc *ref) {
   g_Hdlc = ref;
}

