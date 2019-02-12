#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger (STACKFORCE)
# brief      openD example applications
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(exampleApps)

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Add subdirectories
#---------------------------------------------------------------------------------------

if(APPLICATION STREQUAL FP_HANFUN_CLIENT)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_hanfun_client_rpi)

elseif(APPLICATION STREQUAL FP_LEGACY_CLIENT)

   add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_legacy_client_rpi)

elseif(APPLICATION STREQUAL FP_HANFUN_SERVER AND (BOARD STREQUAL DialogMmiRpi OR BOARD STREQUAL DspgDectRpi))

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_hanfun_server_rpi)

elseif(APPLICATION STREQUAL PP_HANFUN AND (BOARD STREQUAL DialogMmiNucleo OR BOARD STREQUAL DspgDectNucleo))

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pp_hanfun_nucleo)

elseif(APPLICATION STREQUAL FP_LEGACY_SERVER AND (BOARD STREQUAL DialogMmiRpi OR BOARD STREQUAL DspgDectRpi))

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_legacy_server_rpi)

elseif(APPLICATION STREQUAL PP_LEGACY_BASICCALL AND (BOARD STREQUAL DialogMmiNucleo OR BOARD STREQUAL DspgDectNucleo))

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pp_legacy_basiccall_nucleo)

elseif(APPLICATION STREQUAL PP_LEGACY_INTERCOM AND (BOARD STREQUAL DialogMmiNucleo OR BOARD STREQUAL DspgDectNucleo))

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pp_legacy_intercom_nucleo)

else()

    message(FATAL_ERROR "The application, board or the combination of both is not supported!")

endif()
