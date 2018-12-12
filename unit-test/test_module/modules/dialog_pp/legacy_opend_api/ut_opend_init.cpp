/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_opend_init.cpp
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

extern "C"
{
/** Resource under test */
#include "opend.h"
}

/** Mocks */
#include "mock_lowLevel.h"
#include "mock_hdlcHost.h"
#include "mock_hostUtil.h"

/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

/*!
 * Class definition
 */
class ut_dialog_legacy_pp_openD_init: public testing::Test
{
    public:
        // Mock objects
        MockLowLevel ObjLowLevel;
        MockHdlcHost ObjHdlcHost;
        MockHostUtil ObjHostUtil;

        void SetUp()
        {
            setMockLowLevelReference(&ObjLowLevel);
            setMockHdlcHostReference(&ObjHdlcHost);
            setMockHostUtilReference(&ObjHostUtil);
        }
        void TearDown()
        {
        }
};

/*
 * Unit tests
 * */

/*!
 * \brief Tests the function openD_init.
 *
 * \details Verifies if the function works as expected.
 */
TEST_F( ut_dialog_legacy_pp_openD_init, openD_init )
{
    EXPECT_EQ( OPEND_STATUS_OK, openD_init( NULL ) );
}
