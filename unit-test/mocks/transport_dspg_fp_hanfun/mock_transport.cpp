/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_transport.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

#include "mock_transport.h"

/* Module pointer. */
Hf_transport *g_transport;


openD_status_t initUleApp() {
   assert(g_transport != NULL);
   g_transport->initUleApp();
} /* transport_init */

void set_deviceEntryList( ST_IE_HAN_EXTENDED_DEVICE_ENTRIES *pst_HANExtendedDeviceEntry ) {
   assert(g_transport != NULL);
   g_transport->set_deviceEntryList( pst_HANExtendedDeviceEntry );
} /* set_deviceEntryList */



void setMockTransportReference(Hf_transport *transportParam) {
   g_transport = transportParam;
}
