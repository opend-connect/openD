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
project(dspg_fp_hanfun_opend_api)

enable_testing()

SET(MOCKED_MODULES_SOURCE_DIR ../../../../../src)

##
## Includes
##
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/fp_hanfun/hanfun_api
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/test/appcmbs
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/cmbs
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/frame
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/include
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/test
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/test/ListAccess
    ${MOCKED_MODULES_SOURCE_DIR}/opend
    ${MOCKED_MODULES_SOURCE_DIR}/opend/prv
    ${MOCKED_MODULES_SOURCE_DIR}/hanfun_lib
    ${MOCKED_MODULES_SOURCE_DIR}/hanfun_lib/hanfun_lib/inc
    ${MOCKED_MODULES_SOURCE_DIR}/hardware/low-level-api
)


##
## Add targets
##
add_executable(ut_dspg_hanfun_fp_openD_init ut_opend_init.cpp)

##
## Link targets
##
target_link_libraries(ut_dspg_hanfun_fp_openD_init libgmock pthread libApp mockLowLevelApi)

##
## Definitions
##
target_compile_definitions(ut_dspg_hanfun_fp_openD_init PUBLIC -DCMBS_BUF_SIZE=2560)

##
## Add tests
##
add_test(NAME ut_dspg_hanfun_fp_openD_init
         COMMAND ut_dspg_hanfun_fp_openD_init --gtest_output=xml:ut_dspg_hanfun_fp_openD_init.xml)
