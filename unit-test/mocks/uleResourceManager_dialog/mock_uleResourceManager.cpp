/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_uleResourceManager.cpp
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

#include "mock_uleResourceManager.h"

/* Module pointer. */
UleResourceManager *g_UleResourceManager;

extern "C" {

UleErr_e ULE_GetIPUI( rsuint8 portId,rsuint8 IPUIval[] ) {
    assert(g_UleResourceManager != NULL);
    g_UleResourceManager->ULE_GetIPUI( portId, IPUIval );
}

UleErr_e ULE_DeRegister( rsuint8 portId ) {
    assert(g_UleResourceManager != NULL);
    g_UleResourceManager->ULE_DeRegister( portId );
}

} /* */

void setMockUleResourceManagerReference(UleResourceManager *ref) {
   g_UleResourceManager = ref;
}
