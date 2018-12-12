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
    "${CMAKE_CURRENT_SOURCE_DIR}/src/attributes.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/common.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/debug.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/devices.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/dlg_extra.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/profiles.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/protocol.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/uids.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/units.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/attribute_reporting.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/attribute_reporting_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/attribute_reporting_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/bind_management.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/bind_management_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/bind_management_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/device_information.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/device_management.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/device_management_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/device_management_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/session_management_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/session_management_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/alert.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/alert_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/alert_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/level_control.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/level_control_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/level_control_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/on_off.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/on_off_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/on_off_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/simple_humidity_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/simple_humidity_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/simple_power_meter.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/simple_power_meter_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/simple_power_meter_server.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/simple_temperature_client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/interfaces/simple_temperature_server.cpp"
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

#---------------------------------------------------------------------------------------
# Include needed header files
#---------------------------------------------------------------------------------------

if(NOT BOARD STREQUAL DspgDectNucleo)

    target_include_directories(${PROJECT_NAME} PUBLIC
        # HAN-FUN Lib
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/apps
    )

else()

    target_include_directories(${PROJECT_NAME} PUBLIC
        # HAN-FUN Lib
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
    )

endif()

#---------------------------------------------------------------------------------------
# Set macros
#---------------------------------------------------------------------------------------

remove_definitions(
    -DNDEBUG
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    -DDLG_HF_NO_ASSERT
)