/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_msAndStateManager.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
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

extern "C"
{
  /** Resource under test */
  #include "msManager.h"
}


/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

/*!
 * Class definition
 */
class ut_msAndStateManager: public testing::Test
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
 * \brief Tests the function msManager_init.
 *
 * \details Verifies if the function is stable when a null pointer is passed.
 */
TEST_F( ut_msAndStateManager, msManager_init_null_pointer )
{
  msManager_init(NULL, NULL, 0);
}

/*!
 * \brief Tests the function msManager_changeState.
 *
 * \details Verifies if the function is stable when a null pointer is passed.
 */
TEST_F( ut_msAndStateManager, msManager_changeState_null_pointer )
{
  msManager_state_t numberOfStates;

  msManager_changeState(NULL, numberOfStates);
}

/*!
 * \brief Tests the function msManager_handleService.
 *
 * \details Verifies if the function is stable when a null pointer is passed.
 */
TEST_F( ut_msAndStateManager, msManager_handleService_null_pointer )
{
  msManager_handleService(NULL, NULL);
}
