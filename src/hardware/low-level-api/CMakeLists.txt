##
## Author: Patrick Weber
##
cmake_minimum_required(VERSION 3.6)

project(opend-low-level-api)
#---------------------------------------------------------------------------------------
# Target
#---------------------------------------------------------------------------------------
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
