#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
# @author     Patrick Weber
# @brief      openD Dialog legacy FP.
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

project(legacy_api)

cmake_minimum_required(VERSION 3.6)

enable_language(ASM)

#---------------------------------------------------------------------------------------
# Options
#---------------------------------------------------------------------------------------
set(CMAKE_C_FLAGS "-std=c99")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#---------------------------------------------------------------------------------------
# Headers and sources
#---------------------------------------------------------------------------------------
list(APPEND ${PROJECT_NAME}_SOURCES

    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/opend_state_call.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/opend_state_init.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/opend_state_standby.c"

    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/helper.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/ApiHelper.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/CallCtrl.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/LasHelper.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/LineCtrl.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/task.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/MmiCtrl.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/Util.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/LedCtrl/LedCtrl.c"

    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/iwu/CvmConOptions.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/iwu/DynTim.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/iwu/HdlcHost.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/iwu/HostUtil.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/iwu/LinkList.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/iwu/primitive_debug.c"

    "${CMAKE_CURRENT_SOURCE_DIR}/opend.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/opend_sub.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/opend_audio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/opend_call.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/opend_mgmt.c"
)

add_library(libCvmFpPhoenixRpiLinux SHARED IMPORTED)

set_property(TARGET libCvmFpPhoenixRpiLinux PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/lib/libCvmFpPhoenixRpiLinux.a")

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<TARGET_PROPERTY:opendApi,INTERFACE_INCLUDE_DIRECTORIES>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<TARGET_PROPERTY:opendApiPrv,INTERFACE_INCLUDE_DIRECTORIES>
    ${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/Stack/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/iwu
    ${CMAKE_CURRENT_SOURCE_DIR}/pp2fp/fpConf/Include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    libCvmFpPhoenixRpiLinux
    pthread
    rt
    dialog-hdlc-cvmdect
    dialog-board-rpi
    utils
)

add_definitions(
    -D__linux__

    -DRS_RTOS_ID=1
    -DRC_HEAP_IMPLEMENTATION=0
    -DRC_INLINE_HEAP_FUNCTIONS=1
    -DRS_OVERRIDE_AUTO_TOOLID
    -DRS_TOOL_ID=7
    -DRS_TARGET_FAMILY=6
    -DNATALIE_V11
    -DREGS_GCC_MODE=2
    -DREG_SIM_TYPE=1
    -D__forceinline=inline
    -D_DEBUG
    -DWIN32_CTU_TEST
    -DWIN32_NSC_VOICE
    -DWIN32_RSSI_AS_ADC
    -DWIN32_CS_INTERPRETATION
    -D_PP_
    -D_FP_
    -DPP_MMI_HOST_UTIL
    -D_MBCS
    -D_UNICODE
    -DUNICODE
    -DSC14441
    -DRSX
    -DPCCOMPILE
    -DDISREGARD_NON_STANDARD_RTXDEF_EXTENSIONS
    -DNDEBUG
    -DLOG_DDUOS_SIGNALS
    -DWIN32
    -DWIN32_SIM
    -DREPSCLIENT_DLL
    -D_CRT_SECURE_NO_DEPRECATE
    -DRTXDEF_INCLUDE
)
