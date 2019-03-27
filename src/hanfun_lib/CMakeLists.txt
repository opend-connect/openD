#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
# author     Patrick Weber (STACKFORCE), Heiko Berger (STACKFORCE)
# brief      File for creating the HANFUN library.
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Project name
#---------------------------------------------------------------------------------------

project(hanfunLib)

#---------------------------------------------------------------------------------------
# Compiler / Linker settings
#---------------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 11)

#---------------------------------------------------------------------------------------
# Build target
#---------------------------------------------------------------------------------------

file(GLOB ${PROJECT_NAME}_SOURCES
    # HAN-FUN Lib
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/attributes.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/common.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/devices.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/profiles.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/protocol.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/uids.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/units.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/attribute_reporting.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/attribute_reporting_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/attribute_reporting_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/bind_management.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/bind_management_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/bind_management_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/device_information.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/device_management.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/device_management_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/device_management_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/session_management_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/core/session_management_server.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/alert.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/alert_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/alert_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/level_control.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/level_control_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/level_control_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/on_off.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/on_off_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/on_off_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/simple_humidity_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/simple_humidity_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/simple_power_meter.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/simple_power_meter_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/simple_power_meter_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/simple_temperature_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/interfaces/simple_temperature_server.cpp"
)

file(GLOB ${PROJECT_NAME}_SOURCES_DEBUG
    # HAN-FUN Lib
    "${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/src/debug.cpp"
)

execute_process (
    COMMAND git apply --directory=src/hanfun_lib ${CMAKE_CURRENT_SOURCE_DIR}/hanfun.patch
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE outVar
    ERROR_VARIABLE errVar
)
message(STATUS "Git applay: ${outVar}")

if( BOARD STREQUAL DspgDectNucleo OR BOARD STREQUAL DialogMmiNucleo )
    add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
else()
    add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_SOURCES_DEBUG})
endif()

#---------------------------------------------------------------------------------------
# Include needed header files
#---------------------------------------------------------------------------------------

if(NOT BOARD STREQUAL DspgDectNucleo)

    target_include_directories(${PROJECT_NAME} PUBLIC
        # HAN-FUN Lib
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib
        ${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/apps
    )

else()

    target_include_directories(${PROJECT_NAME} PUBLIC
        # HAN-FUN Lib
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib
        ${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib/inc
    )

endif()

#---------------------------------------------------------------------------------------
# Set macros
#---------------------------------------------------------------------------------------
if( BOARD STREQUAL DspgDectNucleo OR BOARD STREQUAL DialogMmiNucleo )
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DNDEBUG
    )
endif()
