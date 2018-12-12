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
project(ut-utils)

enable_testing()

SET(MOCKED_MODULES_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src)
SET(UTILS_DIR ${MOCKED_MODULES_SOURCE_DIR}/utils)

##
## Includes
##
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${UTILS_DIR}
)

##
## Add targets
##
add_executable(ut_msAndStateManager ut_msAndStateManager.cpp
                                    ${UTILS_DIR}/msManager.c
                                    ${UTILS_DIR}/stateManager.c)

##
## Link targets
##
target_link_libraries(ut_msAndStateManager libApp libgmock pthread)

##
## Add tests
##
add_test(NAME ut_msAndStateManager
         COMMAND ut_msAndStateManager --gtest_output=xml:ut_msAndStateManager.xml)
