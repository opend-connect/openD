#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
# author     Heiko Berger (STACKFORCE), Patrick Weber (STACKFORCE)
# brief
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

cmake_minimum_required(VERSION 2.8)


##
## PROJECT
##
project(dialog_fp)

##
## Subdirectories
##
add_subdirectory(hanfun)
add_subdirectory(hanfun_api)
add_subdirectory(hanfun_api_fp)
add_subdirectory(hanfun_opend_api)
add_subdirectory(legacy_opend_api)
add_subdirectory(audio)
add_subdirectory(audio_api)
add_subdirectory(call)
add_subdirectory(call_api)
add_subdirectory(mgmt)
add_subdirectory(mgmt_api)
add_subdirectory(sub)
add_subdirectory(sub_api)
