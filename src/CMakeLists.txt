#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger (STACKFORCE)
# brief      Choose different options
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Options
#---------------------------------------------------------------------------------------

# Allow switching of targets
set(BOARD_LIST DialogMmiRpi DialogMmiNucleo DspgDectNucleo DspgDectRpi None)
set(BOARD DialogMmiRpi CACHE STRING "Default target platform is DialogMmiRpi")
set_property(CACHE BOARD PROPERTY STRINGS ${BOARD_LIST})

# Allow switching of applications
set(APPLICATION_LIST FP_HANFUN_CLIENT FP_HANFUN_SERVER PP_HANFUN FP_LEGACY_CLIENT FP_LEGACY_SERVER PP_LEGACY_BASICCALL PP_LEGACY_INTERCOM)
set(APPLICATION FP_LEGACY_CLIENT CACHE STRING "Default application is FP_LEGACY_CLIENT")
set_property(CACHE APPLICATION PROPERTY STRINGS ${APPLICATION_LIST})

#---------------------------------------------------------------------------------------
# Add subdirectories
#---------------------------------------------------------------------------------------

if(APPLICATION STREQUAL FP_HANFUN_CLIENT OR APPLICATION STREQUAL FP_LEGACY_CLIENT)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/exampleApps)

else()

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/opend)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/exampleApps)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/hardware)

    if(APPLICATION STREQUAL FP_HANFUN_SERVER OR APPLICATION STREQUAL PP_HANFUN)

        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/hanfun_lib)

    else()

        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)

    endif()

endif()
