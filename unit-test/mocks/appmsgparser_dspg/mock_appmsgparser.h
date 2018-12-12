/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_appmsgparser.h
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
#include "cmbs_api.h"
#include "appmsgparser.h"
}

/* Module class declaration. */
class AppMsgParser
{
  public:
    virtual ~AppMsgParser() {}
    virtual void initMsgParserSub(hsSuccessfullyRegistered registeredClb) = 0;
    virtual void initMsgParserCall(hsSuccessfullyConnected connectedClb, hsSuccessfullyReleased releasedClb) = 0;
    virtual void initMsgParserDeSub(hsSuccessfullyDeregistered deregisteredClb) = 0;
};


/* Module class implementaion. */
class MockAppMsgParser : public AppMsgParser
{
  public:
    MOCK_METHOD1( initMsgParserSub, void( hsSuccessfullyRegistered registeredClb ) );
    MOCK_METHOD2( initMsgParserCall, void( hsSuccessfullyConnected connectedClb, hsSuccessfullyReleased releasedClb) );
    MOCK_METHOD1( initMsgParserDeSub, void( hsSuccessfullyDeregistered deregisteredClb ) );
}; 

void setMockAppMsgParserReference(AppMsgParser *ref);
