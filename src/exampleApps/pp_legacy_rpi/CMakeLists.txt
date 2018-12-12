#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
# @author     Patrick Weber
# @brief      openD unified API
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(opend_app_pp2fpConf_ppRpi)
cmake_minimum_required(VERSION 3.6)

enable_language(ASM)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)


set(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall -fmessage-length=0 -fpack-struct=1" CACHE INTERNAL "C Compiler options for debug build type")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -fmessage-length=0 -fpack-struct=1" CACHE INTERNAL "C++ Compiler options for debug build type")
set(CMAKE_ASM_FLAGS_DEBUG "-g" CACHE INTERNAL "ASM Compiler options for debug build type")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE INTERNAL "Linker options for debug build type")


file(GLOB SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/opend_app_pp2fpConf_pp.c"
)


add_executable(${PROJECT_NAME} ${SOURCE})


target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    opend_utils
    opend_dialog_pp_legacy
)
