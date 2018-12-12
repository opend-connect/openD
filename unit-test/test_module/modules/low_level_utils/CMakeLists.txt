#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger (STACKFORCE), Patrick Weber (STACKFORCE)
# brief
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

cmake_minimum_required(VERSION 2.8)


##
## PROJECT
##
project(ut-ll-utils)

enable_testing()

SET(MOCKED_MODULES_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src)
SET(LOW_LEVEL_UTILS_DIR ${MOCKED_MODULES_SOURCE_DIR}/hardware/platform/ll-utils)

##
## Includes
##
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${LOW_LEVEL_UTILS_DIR}
)

##
## Add targets
##
add_executable(ut_ll_utils_queue ut_ll_utils_queue.cpp
                                 ${LOW_LEVEL_UTILS_DIR}/queue.c)
add_executable(ut_ll_utils_fifo ut_ll_utils_fifo.cpp
                                 ${LOW_LEVEL_UTILS_DIR}/fifo.c)
add_executable(ut_ll_utils_swTimer ut_ll_utils_swTimer.cpp
                                 ${LOW_LEVEL_UTILS_DIR}/opend_sw_timer.c)

##
## Link targets
##
target_link_libraries(ut_ll_utils_queue libApp libgmock pthread)
target_link_libraries(ut_ll_utils_fifo libApp libgmock pthread)
target_link_libraries(ut_ll_utils_swTimer libApp libgmock pthread)

##
## Add tests
##
add_test(NAME ut_ll_utils_queue
         COMMAND ut_ll_utils_queue --gtest_output=xml:ut_ll_utils_queue.xml)
add_test(NAME ut_ll_utils_fifo
         COMMAND ut_ll_utils_fifo --gtest_output=xml:ut_ll_utils_fifo.xml)
add_test(NAME ut_ll_utils_swTimer
         COMMAND ut_ll_utils_swTimer --gtest_output=xml:ut_ll_utils_swTimer.xml)
