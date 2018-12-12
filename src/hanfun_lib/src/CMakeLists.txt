# =============================================================================
#
#   @file src/CMakeLists.txt
#
#   HAN-FUN Library CMakeList.
#
#   @version 1.3.0
#
#   @copyright  Copyright (c) 2014  ULE Alliance
#
#   For licensing information, please see the file 'LICENSE' in the root folder.
#
#   Initial development by Bithium S.A. [http://www.bithium.com]
#
# =============================================================================

# ==============================================================================
# Configuration
# ==============================================================================

# ==============================================================================
# Build
# ==============================================================================

set(HF_COMMON_SRCS common.cpp attributes.cpp devices.cpp profiles.cpp uids.cpp debug.cpp)

set(HF_PROTOCOL_SRCS protocol.cpp)
set(HF_INTERFACES_SRCS interfaces.cpp
                       interfaces/alert.cpp
                       interfaces/alert_server.cpp
                       interfaces/alert_client.cpp
                       interfaces/on_off.cpp
                       interfaces/on_off_server.cpp
                       interfaces/on_off_client.cpp
                       interfaces/level_control.cpp
                       interfaces/level_control_server.cpp
                       interfaces/level_control_client.cpp
                       interfaces/simple_power_meter.cpp
                       interfaces/simple_power_meter_server.cpp
                       interfaces/simple_power_meter_client.cpp
                       interfaces/simple_temperature_client.cpp
                       interfaces/simple_temperature_server.cpp
                       interfaces/simple_humidity_client.cpp
                       interfaces/simple_humidity_server.cpp )

set(HF_CORE_SRCS       core/device_management.cpp
                       core/device_management_client.cpp
                       core/device_management_server.cpp
                       core/bind_management.cpp
                       core/bind_management_client.cpp
                       core/bind_management_server.cpp
                       core/device_information.cpp
                       core/attribute_reporting.cpp
                       core/attribute_reporting_server.cpp
                       core/attribute_reporting_client.cpp
                       core/session_management_server.cpp
                       core/session_management_client.cpp)

set(HF_UNITS_SRCS units.cpp)

add_library( hanfun  ${HF_COMMON_SRCS} ${HF_PROTOCOL_SRCS}
                     ${HF_INTERFACES_SRCS} ${HF_CORE_SRCS}
                     ${HF_UNITS_SRCS} )

install(TARGETS hanfun EXPORT ${PACKAGE_NAME}-targets
        ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)

set (HF_TARGETS ${HF_TARGETS} hanfun PARENT_SCOPE)
