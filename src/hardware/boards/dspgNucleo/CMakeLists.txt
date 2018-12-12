##
## Authors:  Patrick Weber
##
project(dspg-board-nucleol476 VERSION 1.0.0)
set(PROJECT_SEMVER_VERSION_SUFFIX "beta.1")

cmake_minimum_required(VERSION 3.6)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/config)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)

#---------------------------------------------------------------------------------------
# Product info
#---------------------------------------------------------------------------------------
set(PROJECT_PRODUCT_COMPANY "STACKFORCE" CACHE STRING "company")
set(PROJECT_PRODUCT_NAME    "openD connect - Platform driver for NucleoL476x" CACHE STRING "product")

# Project version
if(PROJECT_SEMVER_VERSION_SUFFIX)
set(PROJECT_SEMVER_VERSION ${PROJECT_VERSION}-${PROJECT_SEMVER_VERSION_SUFFIX})
else()
set(PROJECT_SEMVER_VERSION ${PROJECT_VERSION})
endif()

#---------------------------------------------------------------------------------------
# Options
#---------------------------------------------------------------------------------------
enable_language(ASM)

#---------------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------------
file(GLOB ${PROJECT_NAME}_SOURCES

    "${CMAKE_CURRENT_LIST_DIR}/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/utils/*.c"

    # Configuration
    "${CMAKE_CURRENT_SOURCE_DIR}/config/gcc/startup_stm32l476xx.s"
    "${CMAKE_CURRENT_SOURCE_DIR}/config/system_stm32l4xx.c"

    "${CMAKE_CURRENT_LIST_DIR}/dspg_ll.c"
    "${CMAKE_CURRENT_LIST_DIR}/dspg_ll_serial.c"
    "${CMAKE_CURRENT_LIST_DIR}/dspg_ll_serial.c"
)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:opend-low-level-api,INTERFACE_INCLUDE_DIRECTORIES>>
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

# PRIVATE because the access may only be allowed over the HAL!
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:platform-config,INTERFACE_INCLUDE_DIRECTORIES>>
)

target_link_libraries( ${PROJECT_NAME}
                            # testApp
                            stm32l4xx
                            stm32l4
                            #dialog-wsmHdlc
                            # utils
)


#---------------------------------------------------------------------------------------
# Configure toolchain
#---------------------------------------------------------------------------------------
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/config/gcc/stm32l476xx_flash.ld)

if(NOT DEFINED LINKER_SCRIPT)
message(FATAL_ERROR "Linker script file path variable LINKER_SCRIPT is not set!")
endif()
# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections --specs=nano.specs --specs=nosys.specs -mthumb -g2 -mcpu=cortex-m4 -mabi=aapcs -T${LINKER_SCRIPT} -Wl,-Map=${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker options")

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
