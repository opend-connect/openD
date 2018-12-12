#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions===============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
# authors:  Patrick Weber
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(openD-platform-raspberrypi VERSION 1.0.0)
set(PROJECT_SEMVER_VERSION_SUFFIX "beta.1")

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Product info
#---------------------------------------------------------------------------------------
set(PROJECT_PRODUCT_COMPANY "STACKFORCE" CACHE STRING "company")
set(PROJECT_PRODUCT_NAME    "openD connect - Platform driver for Raspberry Pi" CACHE STRING "product")

# Project version
if(PROJECT_SEMVER_VERSION_SUFFIX)
set(PROJECT_SEMVER_VERSION ${PROJECT_VERSION}-${PROJECT_SEMVER_VERSION_SUFFIX})
else()
set(PROJECT_SEMVER_VERSION ${PROJECT_VERSION})
endif()

#---------------------------------------------------------------------------------------
# Options
#---------------------------------------------------------------------------------------
set(CMAKE_C_STANDARD 99)

#---------------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------------
list(APPEND ${PROJECT_NAME}_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/serialPort.c"
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    pthread
    ll-utils
)
