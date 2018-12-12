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
project(dialog_fp_sub)

enable_testing()

##
## Variables
##
SET(MOCKED_MODULES_SOURCE_DIR ../../../../../src)
SET(DIALOG_LEGACY_FP_DIR ${MOCKED_MODULES_SOURCE_DIR}/opend/dialog/fp_legacy)
SET(MODULE_UNDER_TEST_DIR ${DIALOG_LEGACY_FP_DIR})

##
## Includes
##
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${DIALOG_LEGACY_FP_DIR}/pp2fp/iwu
    ${DIALOG_LEGACY_FP_DIR}/pp2fp/Stack/Include
    ${DIALOG_LEGACY_FP_DIR}/pp2fp/fpConf/Include
    ${MODULE_UNDER_TEST_DIR}
    ${MOCKED_MODULES_SOURCE_DIR}/opend
    ${MOCKED_MODULES_SOURCE_DIR}/opend/prv)

##
## File under test
##
SET(FILE_UNDER_TEST ${MODULE_UNDER_TEST_DIR}/opend_sub.c)

##
## Add targets
##
add_executable(ut_dialog_fp_openD_sub_confirmation ${FILE_UNDER_TEST} ut_openD_sub_confirmation.cpp)
add_executable(ut_dialog_fp_openD_sub_indication ${FILE_UNDER_TEST} ut_openD_sub_indication.cpp)

##
## Link targets
##
target_link_libraries(ut_dialog_fp_openD_sub_confirmation libgmock pthread libApp mockmsManager mockOpend)
target_link_libraries(ut_dialog_fp_openD_sub_indication libgmock pthread libApp mockmsManager mockOpend)

##
## Add tests
##
add_test(NAME ut_dialog_fp_openD_sub_confirmation
         COMMAND ut_dialog_fp_openD_sub_confirmation --gtest_output=xml:ut_dialog_fp_openD_sub_confirmation.xml)
add_test(NAME ut_dialog_fp_openD_sub_indication
         COMMAND ut_dialog_fp_openD_sub_indication --gtest_output=xml:ut_dialog_fp_openD_sub_indication.xml)
