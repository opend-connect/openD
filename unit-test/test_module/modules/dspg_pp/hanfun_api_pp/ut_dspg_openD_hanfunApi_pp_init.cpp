/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_opend_hanfunapi_pp_init.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     Heiko Berger (STACKFORCE)
 * @author     Mario Behringer (STACKFORCE)
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

/** Include files */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdio.h>
#include <string.h>

#include "dspg_pp_hanfun_api_stubs.h"

/** Resource under test */
#include "opend_hanfun_pp.cpp"
#include "opend_hanfun.cpp"


/** Mocks */
#include "mock_iwu.h"
#include "mock_cmndlib.h"

/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

/*!
 * Class definition
 */
class ut_opend_hanfunapi_pp_init: public testing::Test
{
    public:
        // Mock objects
        MockIwu ObjMockIwu;
        MockCmndlib ObjMockCmndlib;


        void SetUp()
        {
            setMockIwuReference(&ObjMockIwu);
            setMockCmndlibReference(&ObjMockCmndlib);
        }
        void TearDown()
        {
        }
};

/*
 * Unit tests
 * */
/*!
 * \brief Tests the function openD_hanfunApi_pp_init.
 *
 * \details Verifies if the functions succeeds if the mock initIwu returns true.
 */
TEST_F( ut_opend_hanfunapi_pp_init, ut_opend_hanfunapi_pp_init_valid_init )
{
    sendFctPtr = &sendFunction;

    // Setup mock
    EXPECT_CALL( ObjMockIwu, initIwu( _, _ ) )
    .Times( 1 )
    .WillOnce( Return( true ) );

    EXPECT_CALL( ObjMockCmndlib, p_CmndMsg_System_CreateResetReq( _ ) )
    .Times( 1 )
    .WillOnce( Return( true ) );

    EXPECT_CALL( ObjMockCmndlib, p_CmndApiPacket_CreateFromCmndApiMsg( _, _ ) )
    .Times( 1 )
    .WillOnce( Return( true ) );

    EXPECT_EQ( OPEND_STATUS_OK, openD_hanfunApi_pp_init( ) );
}

/*!
 * \brief Tests the function openD_hanfunApi_pp_init.
 *
 * \details Verifies if the functions fails if the mock initIwu returns false.
 */
TEST_F( ut_opend_hanfunapi_pp_init, ut_opend_hanfunapi_pp_init_invalid_init )
{
    // Setup mock
    EXPECT_CALL( ObjMockIwu, initIwu( _, _ ) )
    .Times( 1 )
    .WillOnce( Return( false ) );

    EXPECT_EQ( OPEND_STATUS_FAIL, openD_hanfunApi_pp_init( ) );
}
