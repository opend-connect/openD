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
project(dialog_fp_hanfun_api)

enable_testing()

SET(MOCKED_MODULES_SOURCE_DIR ../../../../../src)

##
## Includes
##
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dialog/fp_hanfun/hanfun_api
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dialog/fp_hanfun/iwu
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dialog/fp_hanfun/include
    ${MOCKED_MODULES_SOURCE_DIR}/opend/dialog/fp_hanfun
    ${MOCKED_MODULES_SOURCE_DIR}/opend
    ${MOCKED_MODULES_SOURCE_DIR}/opend/prv
    ${MOCKED_MODULES_SOURCE_DIR}/hanfun_lib
    ${MOCKED_MODULES_SOURCE_DIR}/hanfun_lib/hanfun_lib/inc
)


##
## Add targets
##
add_executable(ut_dialog_fp_openD_hanfunApi_init ut_openD_hanfunApi_init.cpp)

##
## Link targets
##
target_link_libraries(ut_dialog_fp_openD_hanfunApi_init libgmock pthread libApp libTestHanFun mockLowLevelApi libMockDialogIwu mockUleResourceManager_dialog mockFpHanfunApp)
target_compile_definitions(ut_dialog_fp_openD_hanfunApi_init PUBLIC -DHF_APP_EXT_REG -DPAYLOADDATASIZE=496)

##
## Add tests
##
add_test(NAME ut_dialog_fp_openD_hanfunApi_init
         COMMAND ut_dialog_fp_openD_hanfunApi_init --gtest_output=xml:ut_dialog_fp_openD_hanfunApi_init.xml)
