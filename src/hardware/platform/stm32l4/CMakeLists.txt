#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions===============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
# author:  Patrick Weber
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(stm32l4)

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Options
#---------------------------------------------------------------------------------------
enable_language(ASM)

#---------------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------------
file(GLOB ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:platform-config,INTERFACE_INCLUDE_DIRECTORIES>>
)

target_link_libraries( ${PROJECT_NAME}
                            stm32l4xx
                            ll-utils
)
