#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger (STACKFORCE)
# brief      openD fp dspg hanfun api
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(hanfun_api)

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Build target
#---------------------------------------------------------------------------------------

file(GLOB ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/opend_hanfun_fp.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/opend_hanfun.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/opend.c"
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

#---------------------------------------------------------------------------------------
# Include
#---------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PUBLIC
    $<TARGET_PROPERTY:opendApi,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:opendApiHan,INTERFACE_INCLUDE_DIRECTORIES>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<TARGET_PROPERTY:opendApiPrv,INTERFACE_INCLUDE_DIRECTORIES>
)

#---------------------------------------------------------------------------------------
# Link
#---------------------------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
    hanfunLib
    iwu
)

#---------------------------------------------------------------------------------------
# Set macros
#---------------------------------------------------------------------------------------

target_compile_definitions(${PROJECT_NAME} PRIVATE
    -DHF_APP_EXT_REG
)
