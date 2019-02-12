#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger, Patrick Weber
# brief      Root CMake file for udp client sido demo application
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(opend_dspg)

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Add subdirectories
#---------------------------------------------------------------------------------------

if(APPLICATION STREQUAL FP_LEGACY_SERVER)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmbs)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_legacy)

elseif(APPLICATION STREQUAL PP_LEGACY_BASICCALL OR APPLICATION STREQUAL PP_LEGACY_INTERCOM)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pp_legacy)

elseif(APPLICATION STREQUAL FP_HANFUN_SERVER)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmbs)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_hanfun)

elseif(APPLICATION STREQUAL PP_HANFUN)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pp_hanfun)

endif()
