/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_dialog_openD_hanfunApi_pp_devMgmtRequest.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     Daniel Jaeckle (STACKFORCE)
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


/** Resource under test */
#include "test_hf_transport.cpp"
#include "opend_hanfun_pp.cpp"
#include "opend_hanfun.cpp"

/** Mocks */
#include "mock_iwu.h"

/** Stubs */
#include "dialog_pp_hanfun_api_stubs.h"

/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

/*!
 * Class definition
 */
class ut_dialog_openD_hanfunApi_pp_devMgmtRequest: public testing::Test
{
    public:
        // Mock objects
        MockIwu ObjMockIwu;

        void SetUp()
        {
            setMockIwuReference(&ObjMockIwu);
        }
        void TearDown()
        {
        }
};

/*
 * Unit tests
 * */
/*!
 * \brief Tests the function openD_hanfunApi_pp_devMgmtRequest.
 *
 * \details Verifies if the function handles null pointer correctly
 */
TEST_F( ut_dialog_openD_hanfunApi_pp_devMgmtRequest, ut_dialog_openD_hanfunApi_pp_devMgmtRequest_Null_Pointer )
{
    openD_hanfunApi_devMgmtReq_t *hMgmtRequest = NULL;
    uint16_t address = 0xFFFF;

    EXPECT_EQ( OPEND_STATUS_ARGUMENT_INVALID, openD_hanfunApi_pp_devMgmtRequest( hMgmtRequest, address ) );
}
