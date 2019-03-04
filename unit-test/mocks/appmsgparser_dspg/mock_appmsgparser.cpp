/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_appmsgparser.cpp
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
#include "cmbs_api.h"
#include "appmsgparser.h"
}

#include "mock_appmsgparser.h"

/* Module pointer. */
AppMsgParser *ObjAppMsgParser;

extern "C"{

  void initMsgParserCall(hsSuccessfullyConnected connectedClb, hsSuccessfullyReleased releasedClb){
      assert(ObjAppMsgParser!=NULL);
      ObjAppMsgParser->initMsgParserCall(connectedClb, releasedClb);
  } 

} /* extern */

void setMockAppMsgParserReference(AppMsgParser *ref) {
   ObjAppMsgParser = ref;
}

