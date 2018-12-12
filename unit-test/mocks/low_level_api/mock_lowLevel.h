/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_lowLevel.h
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
  #include "opend_ll.h"
}

/* Module class declaration. */
class LowLevel
{
public:
   virtual ~LowLevel() {}
   virtual int8_t openD_ll_deInit( void ) = 0;
   virtual int8_t openD_ll_init( openD_serialPort_rxCallback_t serialPort_rxCallback ) = 0;
};


/* Module class implementaion. */
class MockLowLevel : public LowLevel
{
public:
   MOCK_METHOD0(openD_ll_deInit,  int8_t( void ));
   MOCK_METHOD1(openD_ll_init,  int8_t( openD_serialPort_rxCallback_t serialPort_rxCallback  ));
};

void setMockLowLevelReference(LowLevel *ref);
