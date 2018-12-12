/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_hdlc.h
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
  #include "hdlc.h"
}

/* Module class declaration. */
class Hdlc
{
public:
   virtual ~Hdlc() {}
   virtual int8_t hdlc_frameCreate( uint8_t *frameBuffer, uint16_t frameBufferSize, uint8_t taskId, uint8_t *payloadData, uint16_t payloadLength ) = 0;
   virtual uint16_t hdlc_getFrameBufferLength( uint16_t payloadLength ) = 0;
   virtual int8_t hdlc_init( hdlc_parsedPacketFct_t hdlc_parsedPacket, hdlc_allocateMemoryFct_t hdlc_allocateMemory, hdlc_freeMemoryFct_t hdlc_freeMemory, hdlc_sendSerialFct_t hdlc_sendSerial ) = 0;
   virtual void hdlc_packetParseBytewise( uint8_t *data ) = 0;
};


/* Module class implementaion. */
class MockHdlc : public Hdlc
{
public:
   MOCK_METHOD5(hdlc_frameCreate ,  int8_t( uint8_t *frameBuffer, uint16_t frameBufferSize, uint8_t taskId, uint8_t *payloadData, uint16_t payloadLength ));
   MOCK_METHOD1(hdlc_getFrameBufferLength ,  uint16_t( uint16_t payloadLength ));
   MOCK_METHOD4(hdlc_init ,  int8_t( hdlc_parsedPacketFct_t hdlc_parsedPacket, hdlc_allocateMemoryFct_t hdlc_allocateMemory, hdlc_freeMemoryFct_t hdlc_freeMemory, hdlc_sendSerialFct_t hdlc_sendSerial ));
   MOCK_METHOD1(hdlc_packetParseBytewise ,  void( uint8_t *data ));
};

void setMockHdlcReference(Hdlc *ref);
