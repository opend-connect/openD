#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger, Patrick Weber
# brief      openD pp hanfun dialog iwu
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(iwu)

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Build target
#---------------------------------------------------------------------------------------

file(GLOB ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/fws.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/mmi.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/log.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/UserTaskWsm.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/transport.cpp"
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

#---------------------------------------------------------------------------------------
# Include
#---------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<TARGET_PROPERTY:pp_hanfun,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:opendApi,INTERFACE_INCLUDE_DIRECTORIES>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<TARGET_PROPERTY:opendApiPrv,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:opend-low-level-api,INTERFACE_INCLUDE_DIRECTORIES>
)

#---------------------------------------------------------------------------------------
# Link libraries
#---------------------------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
    hanfunLib
    dialog-hdlc-wsmdata
    UleSdkWsmPpPhoenixCM4
)

#---------------------------------------------------------------------------------------
# Set macros
#---------------------------------------------------------------------------------------

target_compile_definitions(${PROJECT_NAME} PRIVATE
    -D__baremetal_arm__
    -DHF_SIMPLE_LIGHT
)
