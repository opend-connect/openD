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

project(ll-utils)
cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD 99)

list(APPEND ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/queue.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/fifo.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/opend_sw_timer.c"
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
