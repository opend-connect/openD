# =============================================================================
#
#   @file cmake/package.cmake
#
#   HAN-FUN Library package export helpers.
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

# ... for build folder

get_property(_include_dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)

foreach(_include_dir ${_include_dirs})
    file(RELATIVE_PATH _rel_include_dir "${PROJECT_BINARY_DIR}" "${_include_dir}")
    list(APPEND CONF_INCLUDE_DIRS "\${HANFUN_CMAKE_DIR}/${_rel_include_dir}")
endforeach()

configure_file("cmake/config.cmake.in" "${PROJECT_BINARY_DIR}/${PACKAGE_NAME}-config.cmake" @ONLY)

# ... for install folder

file(RELATIVE_PATH _include_dirs "${CMAKE_INSTALL_PREFIX}/${INSTALL_CMAKE_DIR}"
                                 "${CMAKE_INSTALL_PREFIX}/${INSTALL_INCLUDE_DIR}")

set(CONF_INCLUDE_DIRS "\${HANFUN_CMAKE_DIR}/${_include_dirs}")

configure_file("cmake/config.cmake.in" "${PROJECT_BINARY_DIR}/cmake/${PACKAGE_NAME}-config.cmake" @ONLY)

# Create version file for both build and install folder.

configure_file("cmake/config-version.cmake.in"
               "${PROJECT_BINARY_DIR}/${PACKAGE_NAME}-config-version.cmake" @ONLY)

# Install the hanfun-config.cmake and hanfun-config-version.cmake
install(FILES "${PROJECT_BINARY_DIR}/cmake/${PACKAGE_NAME}-config.cmake"
              "${PROJECT_BINARY_DIR}/${PACKAGE_NAME}-config-version.cmake"
              DESTINATION "${INSTALL_CMAKE_DIR}")

# Install package headers
install(DIRECTORY "inc/" DESTINATION ${INSTALL_INCLUDE_DIR} PATTERN ".git*" EXCLUDE)

install(DIRECTORY "${PROJECT_BINARY_DIR}/hanfun" DESTINATION ${INSTALL_INCLUDE_DIR}
        PATTERN ".git*" EXCLUDE)

# Add all targets to the build-tree export set
export(TARGETS ${HF_TARGETS} FILE "${PROJECT_BINARY_DIR}/${PACKAGE_NAME}-targets.cmake")

# Install the export set for use with the install-tree
install(EXPORT ${PACKAGE_NAME}-targets DESTINATION "${INSTALL_CMAKE_DIR}")
