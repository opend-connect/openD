/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_hdlcHost.cpp
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

#include "mock_hdlcHost.h"

/* Module pointer. */
HdlcHost *g_HdlcHost;

extern "C"{

void hdlc_hostInit(void) {
   assert(g_HdlcHost != NULL);
   g_HdlcHost->hdlc_hostInit();
} /* hdlc_hostSend */

void hdlc_hostSend(unsigned char iTaskId, unsigned char *bInputDataPtr, unsigned short iLength) {
   assert(g_HdlcHost != NULL);
   g_HdlcHost->hdlc_hostSend( iTaskId, bInputDataPtr, iLength );
} /* hdlc_hostSend */

} /* extern */

void setMockHdlcHostReference(HdlcHost *ref) {
   g_HdlcHost = ref;
}

