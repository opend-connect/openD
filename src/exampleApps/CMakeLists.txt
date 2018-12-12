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

if(APPLICATION STREQUAL UDP_Client_Hanfun)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_hanfun_client)

elseif(APPLICATION STREQUAL UDP_Client_Legacy)

   add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_legacy_client)

elseif(APPLICATION STREQUAL HANFUN_SimpleSwitch_FP)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_hanfun_server_rpi)

elseif(APPLICATION STREQUAL HANFUN_SimpleLight_PP)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pp_hanfun_nucleo)

elseif(APPLICATION STREQUAL LEGACY_FP)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_legacy)

elseif(APPLICATION STREQUAL LEGACY_FP_SERVER)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fp_legacy_server_rpi)

elseif(APPLICATION STREQUAL LEGACY_PP)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pp_legacy_nucleo)

elseif(APPLICATION STREQUAL LEGACY_PP_INTERCOM)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pp_legacy_nucleo_intercom)

endif()
