/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_hdlcHost.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */


/* Module class declaration. */
class HdlcHost
{
public:
   virtual ~HdlcHost() {}
   virtual void hdlc_hostInit(void) = 0;
   virtual void hdlc_hostSend(unsigned char iTaskId, unsigned char *bInputDataPtr, unsigned short iLength) = 0;
};


/* Module class implementaion. */
class MockHdlcHost : public HdlcHost
{
public:
   MOCK_METHOD0(hdlc_hostInit, void( void ));
   MOCK_METHOD3(hdlc_hostSend ,  void( unsigned char iTaskId, unsigned char *bInputDataPtr, unsigned short iLength ));
};

void setMockHdlcHostReference(HdlcHost *ref);
