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
project(dspg_fp_mgmt_api)

enable_testing()

##
## Variables
##
SET(MOCKED_MODULES_SOURCE_DIR ../../../../../src)
SET(DSPG_LEGACY_FP_DIR ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/fp_legacy)
SET(MODULE_UNDER_TEST_DIR ${DSPG_LEGACY_FP_DIR}/legacy_api)

##
## Includes
##
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${DSPG_LEGACY_FP_DIR}/iwu
    ${MODULE_UNDER_TEST_DIR}
    ${MOCKED_MODULES_SOURCE_DIR}/opend
    ${MOCKED_MODULES_SOURCE_DIR}/opend/prv)

##
## File under test
##
SET(FILE_UNDER_TEST ${MODULE_UNDER_TEST_DIR}/opend_mgmt.c)

##
## Add targets
##
add_executable(ut_dspg_fp_openD_mgmtApi_init ${FILE_UNDER_TEST} ut_openD_mgmtApi_init.cpp)
add_executable(ut_dspg_fp_openD_mgmtApi_request ${FILE_UNDER_TEST} ut_openD_mgmtApi_request.cpp)

##
## Link targets
##
target_link_libraries(ut_dspg_fp_openD_mgmtApi_init libgmock pthread libApp)
target_link_libraries(ut_dspg_fp_openD_mgmtApi_request libgmock pthread libApp)

##
## Add tests
##
add_test(NAME ut_dspg_fp_openD_mgmtApi_init
         COMMAND ut_dspg_fp_openD_mgmtApi_init --gtest_output=xml:ut_dspg_fp_openD_mgmtApi_init.xml)
add_test(NAME ut_dspg_fp_openD_mgmtApi_request
         COMMAND ut_dspg_fp_openD_mgmtApi_request --gtest_output=xml:ut_dspg_fp_openD_mgmtApi_request.xml)
