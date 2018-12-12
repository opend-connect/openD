#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
# author     Patrick Weber
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

cmake_minimum_required(VERSION 3.6)

# Sets the corresponding platform.
if(BOARD STREQUAL DialogMmiNucleo)

  add_subdirectory(dialogNucleo)
  set(PLATFORM Nucleol476 PARENT_SCOPE)

elseif(BOARD STREQUAL DialogMmiRpi)

  add_subdirectory(dialogRpi)
  set(PLATFORM RaspberryPi PARENT_SCOPE)

elseif(BOARD STREQUAL DspgDectNucleo)

  add_subdirectory(dspgNucleo)
  set(PLATFORM Nucleol476 PARENT_SCOPE)

endif()
