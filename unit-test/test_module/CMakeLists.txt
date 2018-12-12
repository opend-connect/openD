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
## Environment
##
list(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-modules)
find_package(sfgtest)
find_package(sfgtest-toolchain)

include(CTest)
enable_testing()

##
## Set paths
##
SET(MOCK_DIR ../mocks)
SET(MOCKED_MODULES_SOURCE_DIR ../../src)

##
## Libraries
##
add_library(libApp ../test_app/test.cpp)
target_link_libraries(libApp libgmock pthread)

add_library(libMockDspgIwuHanfun ${MOCK_DIR}/iwu_dspg_pp_hanfun/mock_iwu.cpp)
target_link_libraries(libMockDspgIwuHanfun libgmock pthread)
target_include_directories(libMockDspgIwuHanfun PUBLIC ${MOCK_DIR}/iwu_dspg_pp_hanfun ${CMAKE_SOURCE_DIR}/../src/opend/dspg/pp_hanfun/iwu)
target_compile_definitions(libMockDspgIwuHanfun PUBLIC -DSTM32L4)

add_library(mockDspgTransportLegacyPp ${MOCK_DIR}/transport_dspg_pp_legacy/mock_transport.cpp)
target_link_libraries(mockDspgTransportLegacyPp libgmock pthread)
target_include_directories(mockDspgTransportLegacyPp PUBLIC ${MOCK_DIR}/transport_dspg_pp_legacy ${CMAKE_SOURCE_DIR}/../src/opend/dspg/pp_legacy/iwu)

add_library(mockDspgTransportLegacyFp ${MOCK_DIR}/transport_dspg_fp_legacy/mock_transport.cpp)
target_link_libraries(mockDspgTransportLegacyFp libgmock pthread)
target_include_directories(mockDspgTransportLegacyFp PUBLIC ${MOCK_DIR}/transport_dspg_fp_legacy ${CMAKE_SOURCE_DIR}/../src/opend/dspg/fp_legacy/iwu)

add_library(libMockDialogIwu ${MOCK_DIR}/iwu_dialog_pp_hanfun/mock_iwu.cpp)
target_link_libraries(libMockDialogIwu libgmock pthread)
target_include_directories(libMockDialogIwu PUBLIC ${MOCK_DIR}/iwu_dialog_pp_hanfun ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_hanfun/iwu
                                                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_hanfun/include
                                                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_hanfun/include/Stack/Include)

add_library(libMockDspgCmndLib ${MOCK_DIR}/cmndlib_dspg_pp_hanfun/mock_cmndlib.cpp)
target_link_libraries(libMockDspgCmndLib libgmock pthread)
target_include_directories(libMockDspgCmndLib PUBLIC ${MOCK_DIR}/cmndlib_dspg_pp_hanfun ${CMAKE_SOURCE_DIR}/../src/opend/dspg/pp_hanfun/iwu/CmndLib
                                                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dspg/pp_hanfun/iwu/CmndLib/include)

add_library(libMockDspgTestLib ${MOCK_DIR}/testlib_dspg_fp_hanfun/mock_testlib.cpp)
target_link_libraries(libMockDspgTestLib libgmock pthread)
target_include_directories(libMockDspgTestLib PUBLIC ${MOCK_DIR}/testlib_dspg_fp_hanfun ${CMAKE_SOURCE_DIR}/../src/opend/dspg/cmbs/test/appcmbs
                                                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dspg/cmbs
                                                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dspg/cmbs/cmbs/
                                                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dspg/cmbs/frame
                                                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dspg/cmbs/include)
target_compile_definitions(libMockDspgTestLib PUBLIC -DCMBS_BUF_SIZE=2560)

add_library(mockLowLevelApi ${MOCK_DIR}/low_level_api/mock_lowLevel.cpp
                               ${MOCK_DIR}/low_level_api/mock_lowLevelGpio.cpp
                               ${MOCK_DIR}/low_level_api/mock_lowLevelSerial.cpp)
target_link_libraries(mockLowLevelApi libgmock pthread)
target_include_directories(mockLowLevelApi PUBLIC ${MOCK_DIR}/low_level_api ${CMAKE_SOURCE_DIR}/../src/hardware/low-level-api)

add_library(mockmsManager ${MOCK_DIR}/msmanager/mock_msManager.cpp)
target_link_libraries(mockmsManager libgmock pthread)
target_include_directories(mockmsManager PUBLIC ${MOCK_DIR}/msmanager ${CMAKE_SOURCE_DIR}/../src/utils)

set(MOCK_DSPG_APP_MSG_PARSER_DIR ${MOCK_DIR}/appmsgparser_dspg)
add_library(mockDspgAppMsgParser ${MOCK_DSPG_APP_MSG_PARSER_DIR}/mock_appmsgparser.cpp)
target_link_libraries(mockDspgAppMsgParser libgmock pthread)
target_include_directories(mockDspgAppMsgParser PUBLIC ${MOCK_DSPG_APP_MSG_PARSER_DIR}
                                                       ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/cmbs/
                                                       ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/test/appcmbs)
target_compile_definitions(mockDspgAppMsgParser PUBLIC -DCMBS_BUF_SIZE=2560)

set(MOCK_DSPG_APP_APP_CALL_DIR ${MOCK_DIR}/appcall_dspg)
add_library(mockDspgAppCall ${MOCK_DSPG_APP_APP_CALL_DIR}/mock_AppCall.cpp)
target_link_libraries(mockDspgAppCall libgmock pthread)
target_include_directories(mockDspgAppCall PUBLIC ${MOCK_DSPG_APP_APP_CALL_DIR}
                                                       ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/cmbs/
                                                       ${MOCKED_MODULES_SOURCE_DIR}/opend/dspg/cmbs/test/appcmbs)
target_compile_definitions(mockDspgAppCall PUBLIC -DCMBS_BUF_SIZE=2560)

add_library(mockDialogHdlc ${MOCK_DIR}/hdlc_dialog/mock_hdlc.cpp
                           ${MOCK_DIR}/hdlc_dialog/mock_hdlcHost.cpp)
target_link_libraries(mockDialogHdlc libgmock pthread)
target_include_directories(mockDialogHdlc PUBLIC ${MOCK_DIR}/hdlc_dialog
                                                 ${CMAKE_SOURCE_DIR}/../src/opend/dialog/dect-hdlc/src/hdlc
                                                 ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/iwu)

add_library(mockDialogHostUtil ${MOCK_DIR}/hostutil_dialog/mock_hostUtil.cpp)
target_link_libraries(mockDialogHostUtil libgmock pthread)
target_include_directories(mockDialogHostUtil PUBLIC ${MOCK_DIR}/hostutil_dialog
                                                     ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/iwu
                                                     ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/PpConf/Include
                                                     ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/Stack/Include)

add_library(mockDialogRosMail ${MOCK_DIR}/rosmail_dialog/mock_rosMail.cpp)
target_link_libraries(mockDialogRosMail libgmock pthread)
target_include_directories(mockDialogRosMail PUBLIC ${MOCK_DIR}/rosmail_dialog
                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/iwu
                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/Stack/Include
                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/Stack/Include/Core/Ros
                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/PpConf/Include
                                                    ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/Stack/Include)
target_compile_definitions(mockDialogRosMail PUBLIC -D__linux__ -DRS_RTOS_ID=1 -DRC_HEAP_IMPLEMENTATION=0 -DRC_INLINE_HEAP_FUNCTIONS=1 -DRS_OVERRIDE_AUTO_TOOLID
-DRS_TOOL_ID=7 -DRS_TARGET_FAMILY=6 -DNATALIE_V11 -DREGS_GCC_MODE=2 -DREG_SIM_TYPE=1 -D__forceinline=inline -D_DEBUG -DWIN32_CTU_TEST -DWIN32_NSC_VOICE
-DWIN32_RSSI_AS_ADC -DWIN32_CS_INTERPRETATION -D_PP_ -DPP_MMI_HOST_UTIL -D_MBCS -D_UNICODE -DUNICODE -DSC14441 -DRSX -DPCCOMPILE -DDISREGARD_NON_STANDARD_RTXDEF_EXTENSIONS
-DNDEBUG -DLOG_DDUOS_SIGNALS -DWIN32 -DWIN32_SIM -DREPSCLIENT_DLL -D_CRT_SECURE_NO_DEPRECATE -DRTXDEF_INCLUDE)

add_library(mockDialogUtil ${MOCK_DIR}/util_dialog/mock_util.cpp)
target_link_libraries(mockDialogUtil libgmock pthread)
target_include_directories(mockDialogUtil PUBLIC ${MOCK_DIR}/util_dialog
                                                 ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/iwu
                                                 ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/FpConf/Include
                                                 ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/Stack/Include
                                                 ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/iwu
                                                 ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/Stack/Include/Core/
                                                 ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/Stack/Include/Core/Ros)

add_library(mockDialogOpendStates ${MOCK_DIR}/opendstates_dialog/mock_opendStates.cpp)
target_link_libraries(mockDialogOpendStates libgmock pthread)
target_include_directories(mockDialogOpendStates PUBLIC ${MOCK_DIR}/opendstates_dialog
                                                     ${CMAKE_SOURCE_DIR}/../src/opend/dialog/pp_legacy/pp2fp/FpConf/Include)

add_library(mockOpend ${MOCK_DIR}/opend/mock_opend.cpp)
target_link_libraries(mockOpend libgmock pthread)
target_include_directories(mockOpend PUBLIC ${MOCK_DIR}/opend
                                            ${CMAKE_SOURCE_DIR}/../src/opend/
                                            ${CMAKE_SOURCE_DIR}/../src/opend/prv)

file(GLOB HAN_FUN_SOURES
    # HAN-FUN Lib
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/attributes.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/common.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/debug.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/devices.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/dlg_extra.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/profiles.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/protocol.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/uids.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/units.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/attribute_reporting.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/attribute_reporting_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/attribute_reporting_server.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/bind_management.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/bind_management_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/bind_management_server.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/device_information.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/device_management.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/device_management_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/device_management_server.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/session_management_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/core/session_management_server.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/alert.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/alert_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/alert_server.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/level_control.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/level_control_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/level_control_server.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/on_off.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/on_off_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/on_off_server.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/simple_humidity_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/simple_humidity_server.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/simple_power_meter.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/simple_power_meter_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/simple_power_meter_server.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/simple_temperature_client.cpp"
    "${CMAKE_SOURCE_DIR}/../src/hanfun_lib/src/interfaces/simple_temperature_server.cpp"
)

add_library(libTestHanFun ${HAN_FUN_SOURES})

target_include_directories(libTestHanFun PUBLIC
    # HAN-FUN Lib
    ${CMAKE_SOURCE_DIR}/../src/hanfun_lib
    ${CMAKE_SOURCE_DIR}/../src/hanfun_lib/inc
)

##
## Tests
##
add_subdirectory(modules)
