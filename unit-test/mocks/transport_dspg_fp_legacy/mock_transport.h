/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_transport.h
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
#include "transport.h"
#include "opend_dataTypes.h"
}

/* Module class declaration. */
class Transport
{
public:
   virtual ~Transport() {}
   virtual openD_status_t transport_init() = 0;
   virtual openD_status_t transport_deInit() = 0;
};


/* Module class implementaion. */
class MockTransport : public Transport
{
public:
   MOCK_METHOD0(transport_init ,  openD_status_t());
   MOCK_METHOD0(transport_deInit ,  openD_status_t());
};

void setMockTransportReference(Transport *transportParam);
