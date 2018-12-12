#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger, Patrick Weber
# brief      openD rpi hanfun app
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(pp2fpConf_fp)

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Build target
#---------------------------------------------------------------------------------------

link_directories(
    ${CMAKE_SOURCE_DIR}/src/opend/dialog/fp_hanfun/include/lib_linux
    ${CMAKE_SOURCE_DIR}/src/opend/dspg/fp_hanfun/include/lib
)

file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/opend_app_pp2fpConf_fp.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

#---------------------------------------------------------------------------------------
# Include
#---------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


#---------------------------------------------------------------------------------------
# Link target
#---------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME}
    stdc++
    legacy_api
    pthread
    utils
)
