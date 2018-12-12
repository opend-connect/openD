#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger (STACKFORCE)
# brief      openD nucleo hanfun app
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(pp_hanfun_nucleo)

cmake_minimum_required(VERSION 3.6)


if(BOARD STREQUAL DialogMmiNucleo)

#---------------------------------------------------------------------------------------
# Build target
#---------------------------------------------------------------------------------------

  link_directories(
      ${CMAKE_SOURCE_DIR}/src/opend/dialog/pp_hanfun/lib/baremetal_arm
  )

  add_executable(${PROJECT_NAME} main_hanfun.cpp)

#---------------------------------------------------------------------------------------
# Link target
#---------------------------------------------------------------------------------------

  target_link_libraries(${PROJECT_NAME}
      iwu
      hanfunLib
      hanfun_api
  )

elseif(BOARD STREQUAL DspgDectNucleo)

#---------------------------------------------------------------------------------------
# Build target
#---------------------------------------------------------------------------------------

  add_executable(${PROJECT_NAME} main_hanfun.cpp)

#---------------------------------------------------------------------------------------
# Link target
#---------------------------------------------------------------------------------------

  target_link_libraries(${PROJECT_NAME}
      iwu
      stm32l4xx
      hanfun_api
  )

#---------------------------------------------------------------------------------------
# Set property
#---------------------------------------------------------------------------------------

  set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

endif()