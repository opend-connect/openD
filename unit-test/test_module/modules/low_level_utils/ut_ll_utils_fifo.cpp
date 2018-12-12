/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_ll_utils_fifo.cpp
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
  #include "fifo.h"
}


/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

/*!
 * Class definition
 */
class ut_ll_utils_fifo: public testing::Test
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
 * \brief Tests the function openD_fifoopenD_fifo_init_remaining.
 *
 * \details Verifies if the function is stable when all parameters are valid.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_init)
{
  uint8_t buffer;
  fifo_t fifo;

  EXPECT_TRUE(openD_fifo_init(&fifo, &buffer, 1));
}

/*!
 * \brief Tests the function openD_fifoopenD_fifo_init_remaining.
 *
 * \details Verifies if the function is stable when a null pointer are
 *          passed as parameter or the buffer length is 0.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_init_null_ptr)
{
  uint8_t buffer;
  fifo_t fifo;

  EXPECT_FALSE(openD_fifo_init(NULL, &buffer, 1));

  EXPECT_FALSE(openD_fifo_init(&fifo, NULL, 1));

  EXPECT_FALSE(openD_fifo_init(&fifo, &buffer, 0));
}

/*!
 * \brief Tests the function openD_fifo_remaining.
 *
 * \details Verifies if the function is stable when a null pointer is passed.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_remaining_null_ptr )
{
    EXPECT_EQ(0U, openD_fifo_remaining(NULL));
}

/*!
 * \brief Tests the fifo module function openD_fifo_remaining.
 *
 * \details Verifies if the module returns the correct fifo size.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_remaining_all_sizes )
{
    fifo_t fifo;
    uint8_t buffer;

    for(uint16_t fifoSize = 1; fifoSize < 0xFFFF; ++fifoSize)
    {
      EXPECT_TRUE(openD_fifo_init(&fifo, &buffer, fifoSize)) << "at size: " << fifoSize;
      EXPECT_EQ(fifoSize, openD_fifo_remaining(&fifo));
    }
}

/*!
 * \brief Tests the function openD_fifo_isEmpty.
 *
 * \details Verifies if the function is stable when a null pointer is passed.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_isEmpty_null_ptr )
{
    EXPECT_FALSE(openD_fifo_isEmpty(NULL));
}

/*!
 * \brief Tests the function openD_fifo_isEmpty.
 *
 * \details Verifies if the function is working properly.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_isEmpty )
{
    fifo_t fifo;
    uint8_t buffer;

    EXPECT_TRUE(openD_fifo_init(&fifo, &buffer, 1));
    EXPECT_TRUE(openD_fifo_isEmpty(&fifo));
}

/*!
 * \brief Tests the function openD_fifo_write.
 *
 * \details Verifies if the function is stable when a null pointer is passed.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_write_null_ptr )
{
    uint8_t data;

    EXPECT_FALSE(openD_fifo_write(NULL, data));
}

/*!
 * \brief Tests the function openD_fifo_read.
 *
 * \details Verifies if the function is stable when a null pointer is passed.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_read_null_ptr )
{
    uint8_t data;

    EXPECT_FALSE(openD_fifo_read(NULL, &data));
}

/*!
 * \brief Tests the fifo module.
 *
 * \details Verifies if reading and writing some bytes is working properly.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_read_write_some_bytes )
{
    uint8_t readData;
    uint8_t data[10];
    uint8_t buffer[10];

    uint8_t numToWrite = 8;

    fifo_t fifo;

    openD_fifo_init(&fifo, buffer, sizeof(buffer));

    for(uint8_t dataIndex = 0x00; dataIndex < numToWrite; dataIndex++)
    {
       data[dataIndex] = dataIndex;
       EXPECT_TRUE(openD_fifo_write(&fifo, dataIndex));
    }

    for(uint16_t dataIndex = 0x00; dataIndex < numToWrite; dataIndex++)
    {
       EXPECT_TRUE(openD_fifo_read(&fifo, &readData));
       EXPECT_EQ(data[dataIndex], readData);
    }

    EXPECT_TRUE(openD_fifo_isEmpty(&fifo));
}

/*!
 * \brief Tests the fifo module.
 *
 * \details Verifies if reading and writing some bytes twice is working properly.
 */
TEST_F( ut_ll_utils_fifo, openD_fifo_read_write_some_bytes_twice )
{
    uint8_t readData;
    uint8_t data[10];
    uint8_t buffer[10];

    uint8_t numToWrite = 10;

    fifo_t fifo;

    openD_fifo_init(&fifo, buffer, sizeof(buffer));

    for(uint8_t dataIndex = 0x00; dataIndex < numToWrite; dataIndex++)
    {
       data[dataIndex] = dataIndex;
       EXPECT_TRUE(openD_fifo_write(&fifo, dataIndex));
    }

    for(uint16_t dataIndex = 0x00; dataIndex < numToWrite; dataIndex++)
    {
       EXPECT_TRUE(openD_fifo_read(&fifo, &readData));
       EXPECT_EQ(data[dataIndex], readData);
    }

    for(uint8_t dataIndex = 0x00; dataIndex < numToWrite; dataIndex++)
    {
       data[dataIndex] = dataIndex;
       EXPECT_TRUE(openD_fifo_write(&fifo, dataIndex));
    }

    for(uint16_t dataIndex = 0x00; dataIndex < numToWrite; dataIndex++)
    {
       EXPECT_TRUE(openD_fifo_read(&fifo, &readData));
       EXPECT_EQ(data[dataIndex], readData);
    }
}
