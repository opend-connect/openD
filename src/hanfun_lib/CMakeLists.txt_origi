# =============================================================================
#
#   @file CMakeLists.txt
#
#   HAN-FUN Library Top CMakeList
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

cmake_minimum_required (VERSION 2.8)

project (HAN-FUN)

# ==============================================================================
# Default project setup.

## Standard project paths.
set( PROJECT_INCLUDE_DIR  "${PROJECT_SOURCE_DIR}/inc" )

# setup default include-directories
include_directories(
  ${PROJECT_BINARY_DIR}
  ${PROJECT_INCLUDE_DIR}
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# ==============================================================================
# Configuration
# ==============================================================================

include("cmake/compiler.cmake")

# The version number.
set(HF_MAJOR_VERSION 1)
set(HF_MINOR_VERSION 3)
set(HF_PATCH_VERSION 0)
set(HF_OTHER_VERSION "")

set(HF_VERSION "${HF_MAJOR_VERSION}.${HF_MINOR_VERSION}.${HF_PATCH_VERSION}${HF_OTHER_VERSION}")

configure_file( ${CMAKE_SOURCE_DIR}/version.h.in
                ${CMAKE_BINARY_DIR}/hanfun/version.h )

include("cmake/options.cmake")

configure_file( ${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/hanfun/config.h )

# ==============================================================================
# Library
# ==============================================================================

add_subdirectory(src)

# ==============================================================================
# Example Applications
# ==============================================================================

add_subdirectory(apps)

# ==============================================================================
# Tests
# ==============================================================================

if(HF_BUILD_TESTS)
    add_subdirectory(tests)
endif(HF_BUILD_TESTS)

# ==============================================================================
# Documentation
# ==============================================================================

add_subdirectory(doc EXCLUDE_FROM_ALL)

# ==============================================================================
# Package
# ==============================================================================

include("cmake/package.cmake")

# ==============================================================================
# Release
# ==============================================================================

add_custom_target(dist scripts/make_release.sh DEPENDS doc
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  COMMENT "Create distribution tarballs ...")
