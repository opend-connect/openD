/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_dialog_opend_hanfun_createProfile.cpp
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





/** Resource under test */
#include "test_hf_transport.cpp"
#include "opend_hanfun_pp.cpp"
#include "opend_hanfun.cpp"


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
class ut_dialog_opend_hanfun_createProfile: public testing::Test
{
    public:

      void SetUp()
      {
      }
      void TearDown()
      {
      }
};

/*
 * Unit tests
 * */
/*!
 * \brief Tests the function opend_hanfun_createProfile_simpleOnOffSwitch.
 *
 * \details Verifies if the functions succeeds if the mock initIwu returns true.
 */
TEST_F( ut_dialog_opend_hanfun_createProfile, ut_dialog_opend_hanfun_createProfile_simpleOnOffSwitch )
{
    openD_hanfunApi_profile_t profile = OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH;
    uint8_t id;

    EXPECT_EQ( OPEND_STATUS_OK, opend_hanfun_createProfile( profile, id ) );
}

/*!
 * \brief Tests the function opend_hanfun_createProfile_simpleLight.
 *
 * \details Verifies if the functions succeeds if the mock initIwu returns true.
 */
TEST_F( ut_dialog_opend_hanfun_createProfile, ut_dialog_opend_hanfun_createProfile_simpleLight)
{
    openD_hanfunApi_profile_t profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
    uint8_t id;

    EXPECT_EQ( OPEND_STATUS_OK, opend_hanfun_createProfile( profile, id ) );
}
