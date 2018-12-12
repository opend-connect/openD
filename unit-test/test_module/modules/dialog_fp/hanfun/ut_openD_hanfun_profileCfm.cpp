/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_opend_hanfun_profilecfm.cpp
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
#include "opend_hanfun.cpp"

#include "dialog_fp_hanfun_api_stubs.h"

/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

/*!
 * Class definition
 */
class ut_opend_hanfun_profilecfm: public testing::Test
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
 * \brief Tests the function openD_hanfun_profileCfm.
 *
 * \details Verifies if the function works as expected when do not
 *          an initialization.
 */
TEST_F( ut_opend_hanfun_profilecfm, ut_opend_hanfun_profilecfm_NULL_Pointer )
{
  openD_hanfunApi_profileCfm_t hProfileConfirm;

  EXPECT_EQ( OPEND_STATUS_FAIL, openD_hanfun_profileCfm(&hProfileConfirm) );
}

/*!
 * \brief Tests the function openD_hanfun_profileCfm.
 *
 * \details Verifies if the function works as expected when do
 *          an initialization.
 */
TEST_F( ut_opend_hanfun_profilecfm, ut_opend_hanfun_profilecfm_valid_Pointer )
{
  /* Set the confirmation and indication callbacks. */
  openD_hanfunApiPrimitives.openD_hanfunApiProfileCfm = profileConfirmCallback;

  EXPECT_EQ( openD_hanfunApi_init(&openD_hanfunApiPrimitives), OPEND_STATUS_OK );

  openD_hanfunApi_profileCfm_t hProfileConfirm;

  EXPECT_EQ( OPEND_STATUS_OK, openD_hanfun_profileCfm(&hProfileConfirm) );
}
