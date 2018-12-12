# =============================================================================
#
#   @file apps/CMakeLists.txt
#
#   HAN-FUN Library Examples CMakeList
#
#   @version    1.3.0
#
#   @copyright  Copyright (c) 2014  ULE Alliance
#
#   For licensing information, please see the file 'LICENSE' in the root folder.
#
#   Initial development by Bithium S.A. [http://www.bithium.com]
#
# =============================================================================

# =============================================================================
# Libuv
# =============================================================================

if (HF_BASE_APP OR HF_NODE_APP)
    include(ExternalProject)

    set (LIBUV_PREFIX      "${CMAKE_CURRENT_BINARY_DIR}/libuv")
    set (LIBUV_INSTALL_DIR "${LIBUV_PREFIX}/src/libuv")

    find_program(MAKE_BIN "make")

    ExternalProject_Add(libuv
        PREFIX ${LIBUV_PREFIX}
        URL "http://dist.libuv.org/dist/v0.10.27/libuv-v0.10.27.tar.gz"
        URL_HASH MD5=8bc14dc254363092bd36919ea05cc9ab
        CONFIGURE_COMMAND ""
        BUILD_COMMAND CC=${CMAKE_C_COMPILER} ${MAKE_BIN}
        BUILD_IN_SOURCE 1
        INSTALL_COMMAND ""
    )

    set (LIBUV_LIBRARY "${LIBUV_PREFIX}/src/libuv/libuv.a")
    set (LIBUV_LIBRARIES ${LIBUV_LIBRARY} -lrt -ldl -lm -pthread)

    include_directories( ${LIBUV_INSTALL_DIR}/include )
endif()

if (HF_APP_EXT_REG)
    add_definitions( -DHF_APP_EXT_REG )
endif()

if (HF_BASE_LIB OR HF_NODE_LIB)
    configure_file("application.h" "${CMAKE_BINARY_DIR}/hanfun/application.h" COPYONLY)
endif()

# =============================================================================
# Base Application Example
# =============================================================================

if (HF_BASE_LIB)
    message (STATUS "Build Base example application library.")

    set(BASE_APP_SRCS   "base.h" "common.cpp" "base.cpp" "base_app.cpp" "jsoncpp.cpp")

    add_definitions(-DJSON_USE_EXCEPTION=0)

    add_library(hf_base_app ${BASE_APP_SRCS})
    target_link_libraries(hf_base_app hanfun)

    install(TARGETS hf_base_app EXPORT ${PACKAGE_NAME}-targets
            ARCHIVE DESTINATION "${INSTALL_LIB_DIR}")

    set (HF_TARGETS ${HF_TARGETS} hf_base_app)
endif()

if (HF_BASE_APP)
    message (STATUS "Build Base example application.")

    add_executable(hf_base "main.cpp" "transport.cpp")
    add_dependencies(hf_base libuv)
    set_target_properties(hf_base PROPERTIES COMPILE_DEFINITIONS "HF_BASE_APP")
    target_link_libraries(hf_base hf_base_app hanfun  ${LIBUV_LIBRARIES} )
    install(TARGETS hf_base EXPORT ${PACKAGE_NAME}-targets RUNTIME DESTINATION "${INSTALL_BIN_DIR}")
endif()

# =============================================================================
# Node Applications Example
# =============================================================================

if (HF_NODE_LIB)
    message (STATUS "Build Node example application library.")

    set(NODE_APP_SRCS   "node.h" "common.cpp" "node.cpp" "node_app.cpp")

    add_library( hf_node_app ${NODE_APP_SRCS})
    target_link_libraries(hf_node_app hanfun)

    install(TARGETS hf_node_app EXPORT ${PACKAGE_NAME}-targets
            ARCHIVE DESTINATION "${INSTALL_LIB_DIR}")

    set (HF_TARGETS ${HF_TARGETS} hf_node_app)
endif()

if (HF_NODE_APP)
    message (STATUS "Build Node example application.")

    add_executable(hf_node "main.cpp" "transport.cpp")
    add_dependencies(hf_node libuv)
    set_target_properties(hf_node PROPERTIES COMPILE_DEFINITIONS "HF_NODE_APP")
    target_link_libraries(hf_node hf_node_app hanfun ${LIBUV_LIBRARIES})

    install(TARGETS hf_node EXPORT ${PACKAGE_NAME}-targets RUNTIME DESTINATION "${INSTALL_BIN_DIR}")
endif()

set (HF_TARGETS ${HF_TARGETS} PARENT_SCOPE)

# ==============================================================================
# Examples
# ==============================================================================

## Registration examples
add_executable(example_01 EXCLUDE_FROM_ALL example_01.cpp)
target_link_libraries(example_01 hanfun)

add_executable(example_02 EXCLUDE_FROM_ALL example_02.cpp)
target_link_libraries(example_02 hanfun)

## Alert interface example
add_executable(example_03 EXCLUDE_FROM_ALL example_03.cpp)
target_link_libraries(example_03 hanfun)

## On-Off interface example
add_executable(example_04 EXCLUDE_FROM_ALL example_04.cpp)
target_link_libraries(example_04 hanfun)

## Level Control interface example
add_executable(example_05 EXCLUDE_FROM_ALL example_05.cpp)
target_link_libraries(example_05 hanfun)

## Device Information service example
add_executable(example_06 EXCLUDE_FROM_ALL example_06.cpp)
target_link_libraries(example_06 hanfun)

## Attribute reporting service example
add_executable(example_07 EXCLUDE_FROM_ALL example_07.cpp)
target_link_libraries(example_07 hanfun)

## Bind service example
add_executable(example_08 EXCLUDE_FROM_ALL example_08.cpp)
target_link_libraries(example_08 hanfun)

## Build all examples
add_custom_target(examples DEPENDS example_01 example_02 example_03
                                   example_04 example_05 example_06
                                   example_07 example_08)
