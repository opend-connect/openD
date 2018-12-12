/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_ll_utils_swTimer.cpp
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
  #include "opend_sw_timer.h"
}


/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

/** Global variables */
bool timerCallbackCalled;
bool timerCallbackCalled2;
bool timerCallbackCalled3;

/*!
 * Class definition
 */
class ut_ll_utils_swTimer: public testing::Test
{
    public:

      void SetUp()
      {
        timerCallbackCalled = false;
        timerCallbackCalled2 = false;
        timerCallbackCalled3 = false;
      }
      void TearDown()
      {
      }
};

void swTimerCallback( void ){
    timerCallbackCalled = true;
}

void swTimerCallback2( void ){
    timerCallbackCalled2 = true;
}

void swTimerCallback3( void ){
    timerCallbackCalled3 = true;
}

void swTimerCbAddingTimer( void ){
    openD_sw_timer_start( 500, swTimerCallback );
}


/*
 * Unit tests
 * */

/*!
 * \brief Tests the software timer.
 *
 * \details Verifies if the function works as expected using a single timer.
 */
TEST_F( ut_ll_utils_swTimer, openD_sw_timer_singleTimeout )
{
    openD_sw_timer_start( 1000, swTimerCallback );

    openD_sw_timer_tick(500);
    EXPECT_FALSE(timerCallbackCalled);

    openD_sw_timer_tick(500);
    EXPECT_TRUE(timerCallbackCalled);
}

/*!
 * \brief Tests the software timer.
 *
 * \details Verifies if the function works as expected using multiple
 *          timer that expire at the same time.
 */
TEST_F( ut_ll_utils_swTimer, openD_sw_timer_multiple_timer_same_timeout )
{
    openD_sw_timer_start( 1000, swTimerCallback );
    openD_sw_timer_start( 1000, swTimerCallback2 );

    openD_sw_timer_tick(500);
    EXPECT_FALSE(timerCallbackCalled);
    EXPECT_FALSE(timerCallbackCalled2);

    openD_sw_timer_tick(500);
    EXPECT_TRUE(timerCallbackCalled);
    EXPECT_TRUE(timerCallbackCalled2);
}

/*!
 * \brief Tests the software timer.
 *
 * \details Verifies if the function works as expected when multiple
 *          timers are started.
 */
TEST_F( ut_ll_utils_swTimer, openD_sw_timer_multiple_timer_ordered )
{
    openD_sw_timer_start( 500, swTimerCallback );
    openD_sw_timer_start( 1500, swTimerCallback2 );
    openD_sw_timer_start( 2000, swTimerCallback3 );

    openD_sw_timer_tick(500);
    EXPECT_TRUE(timerCallbackCalled);
    EXPECT_FALSE(timerCallbackCalled2);
    EXPECT_FALSE(timerCallbackCalled3);

    openD_sw_timer_tick(500);
    EXPECT_FALSE(timerCallbackCalled2);
    EXPECT_FALSE(timerCallbackCalled3);

    openD_sw_timer_tick(500);
    EXPECT_TRUE(timerCallbackCalled2);
    EXPECT_FALSE(timerCallbackCalled3);

    openD_sw_timer_tick(500);
    EXPECT_TRUE(timerCallbackCalled3);
}

/*!
 * \brief Tests the software timer.
 *
 * \details Verifies if the function works as expected when multiple
 *          timers are started.
 */
TEST_F( ut_ll_utils_swTimer, openD_sw_timer_multiple_timer_mixed_order )
{
    openD_sw_timer_start( 500, swTimerCallback );
    openD_sw_timer_start( 2000, swTimerCallback3 );
    openD_sw_timer_start( 1500, swTimerCallback2 );

    openD_sw_timer_tick(500);
    EXPECT_TRUE(timerCallbackCalled);
    EXPECT_FALSE(timerCallbackCalled2);
    EXPECT_FALSE(timerCallbackCalled3);

    openD_sw_timer_tick(500);
    EXPECT_FALSE(timerCallbackCalled2);
    EXPECT_FALSE(timerCallbackCalled3);

    openD_sw_timer_tick(500);
    EXPECT_TRUE(timerCallbackCalled2);
    EXPECT_FALSE(timerCallbackCalled3);

    openD_sw_timer_tick(500);
    EXPECT_TRUE(timerCallbackCalled3);
}

/*!
 * \brief Tests the software timer.
 *
 * \details Verifies if the function works as expected when a new timer is
 *          added inside the timer callback function.
 */
TEST_F( ut_ll_utils_swTimer, openD_sw_timer_cb_adds_new_timer )
{
    openD_sw_timer_start( 500, swTimerCbAddingTimer );

    openD_sw_timer_tick(500);
    EXPECT_FALSE(timerCallbackCalled);

    openD_sw_timer_tick(500);
    EXPECT_TRUE(timerCallbackCalled);
}
