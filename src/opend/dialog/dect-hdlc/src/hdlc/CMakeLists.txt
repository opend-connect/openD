#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
# author     Patrick Weber
# brief      Dialog HDLC low level driver.
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(dialog-hdlc)
cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD 99)

list(APPEND ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/hdlc.c"
)

###############################################################################
# Target CVMDECT
###############################################################################
add_library(${PROJECT_NAME}-cvmdect ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME}-cvmdect PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}-cvmdect
    dialog-hdlc-utils
)

target_compile_definitions(${PROJECT_NAME}-cvmdect PRIVATE
    -DDEBUG_HDLC
)

###############################################################################
# Target WSMDATA
###############################################################################
add_library(${PROJECT_NAME}-wsmdata ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME}-wsmdata PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}-wsmdata
    dialog-hdlc-utils
)

target_compile_definitions(${PROJECT_NAME}-wsmdata PRIVATE
    -DDEBUG_HDLC
    -DWSMDATA
)
