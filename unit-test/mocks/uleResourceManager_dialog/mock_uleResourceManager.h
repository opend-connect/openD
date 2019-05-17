/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_uleResourceManager.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

extern "C" {
#include <Phoenix/Api/Api.h>

#include <include/uleDectAPI.h>
#include <include/uleAppAPI.h>
#include <dect_driver.h>
}

#include <gmock/gmock.h>

/* Module class declaration. */
class UleResourceManager
{
public:
   virtual ~UleResourceManager() {}
   virtual UleErr_e ULE_GetIPUI( rsuint8 portId,rsuint8 IPUIval[] ) = 0;
   virtual UleErr_e ULE_DeRegister( rsuint8 portId ) = 0;
};


/* Module class implementaion. */
class MockUleResourceManager : public UleResourceManager
{
public:
   MOCK_METHOD2(ULE_GetIPUI , UleErr_e( rsuint8 portId,rsuint8 IPUIval[] ));
   MOCK_METHOD1(ULE_DeRegister , UleErr_e( rsuint8 portId ));
};

void setMockUleResourceManagerReference(UleResourceManager *ref);
