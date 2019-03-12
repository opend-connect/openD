#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger (STACKFORCE)
# brief      openD API
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(opendApi)

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Build interface libraries
#---------------------------------------------------------------------------------------

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hanfun>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hanfun/interfaces>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hanfun/profiles>
)

add_library(${PROJECT_NAME}Prv INTERFACE)

target_include_directories(${PROJECT_NAME}Prv INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/prv>
)

add_library(${PROJECT_NAME}Han INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hanfun>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hanfun/interfaces>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/hanfun/profiles>
)

#---------------------------------------------------------------------------------------
# Add subdirectories and build target
#---------------------------------------------------------------------------------------

if(BOARD STREQUAL DialogMmiRpi OR BOARD STREQUAL DialogMmiNucleo)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dialog)

elseif(BOARD STREQUAL DspgDectRpi OR BOARD STREQUAL DspgDectNucleo)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dspg)

endif()
