/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_opendStates.h
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
class OpendStates
{
public:
   virtual ~OpendStates() {}
   virtual bool opend_state_call( void *param ) = 0;
   virtual bool opend_state_init( void *param ) = 0;
   virtual bool opend_state_standby( void *param ) = 0;
};


/* Module class implementaion. */
class MockOpendStates : public OpendStates
{
public:
   MOCK_METHOD1(opend_state_call ,  bool( void *param ));
   MOCK_METHOD1(opend_state_init ,  bool( void *param ));
   MOCK_METHOD1(opend_state_standby ,  bool( void *param ));
};

void setMockOpendStatesReference(OpendStates *ref);
