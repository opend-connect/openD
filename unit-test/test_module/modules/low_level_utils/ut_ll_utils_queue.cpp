/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_ll_utils_queue.cpp
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
  #include "queue.h"
}


/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

/*!
 * Class definition
 */
class ut_ll_utils_queue: public testing::Test
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
 * \brief Tests the function queue_init.
 *
 * \details Verifies if the function works as expected
 *          when a null pointer is passed.
 */
TEST_F( ut_ll_utils_queue, queue_init_null_ptr )
{
    EXPECT_EQ(-1, queue_init(NULL));
}

/*!
 * \brief Tests the function queue_push.
 *
 * \details Verifies if the function works as expected
 *          when a null pointer is passed.
 */
TEST_F( ut_ll_utils_queue, queue_push_null_ptr )
{
    EXPECT_EQ(-1, queue_push(NULL, NULL, 0U));
}

/*!
 * \brief Tests the function queue_front.
 *
 * \details Verifies if the function works as expected
 *          when a null pointer is passed.
 */
TEST_F( ut_ll_utils_queue, queue_front_null_ptr )
{
    EXPECT_EQ(NULL, queue_front(NULL));
}

/*!
 * \brief Tests the function queue_pop.
 *
 * \details Verifies if the function works as expected
 *          when a null pointer is passed.
 */
TEST_F( ut_ll_utils_queue, queue_pop_null_ptr )
{
    EXPECT_EQ(-1, queue_pop(NULL));
}

/*!
 * \brief Tests if the queue module works as expected with one queue entry.
 */
TEST_F( ut_ll_utils_queue, queue_single_entry )
{
    queue_ctx_t queueCtx;
    queue_dataElement_t *queueEntry;

    uint8_t data;

    EXPECT_EQ( 0, queue_init( &queueCtx ));

    EXPECT_EQ( 0, queue_push( &queueCtx, &data, sizeof( data )));

    queueEntry = queue_front( &queueCtx );
    EXPECT_EQ( &data, queueEntry->data );
    EXPECT_EQ( sizeof( data ), queueEntry->size );

    EXPECT_EQ( 0, queue_pop( &queueCtx ));

    EXPECT_EQ( NULL, queue_front( &queueCtx ));
}

/*!
 * \brief Tests if the queue module works as expected with
 *        multiple queue entries.
 */
TEST_F( ut_ll_utils_queue, queue_multiple_entries )
{
    queue_ctx_t queueCtx;
    queue_dataElement_t *queueEntry;

    uint8_t data;
    uint8_t data2;

    EXPECT_EQ( 0, queue_init( &queueCtx ));

    EXPECT_EQ( 0, queue_push( &queueCtx, &data, sizeof( data )));
    EXPECT_EQ( 0, queue_push( &queueCtx, &data2, sizeof( data2 )));

    queueEntry = queue_front( &queueCtx );
    EXPECT_EQ( &data, queueEntry->data );
    EXPECT_EQ( sizeof( data ), queueEntry->size );

    EXPECT_EQ( 0, queue_pop( &queueCtx ));

    queueEntry = queue_front( &queueCtx );
    EXPECT_EQ( &data2, queueEntry->data );
    EXPECT_EQ( sizeof( data2 ), queueEntry->size );

    EXPECT_EQ( 0, queue_pop( &queueCtx ));

    EXPECT_EQ( NULL, queue_front( &queueCtx ));
}
