#  ___ _____ _   ___ _  _____ ___  ___  ___ ___
# / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
# \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
# |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
# embedded.connectivity.solutions.==============
#
# @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
# @author     Patrick Weber
# @author     Heiko Berger
# @brief      openD unified API
#
#
# This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
# For further details, please refer to the project home: https://github.com/opend-connect/openD
#
# SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only

#---------------------------------------------------------------------------------------
# Options
#---------------------------------------------------------------------------------------
option(BUILD_DOC "Create and install the HTML based API documentation" OFF)

#---------------------------------------------------------------------------------------
# Doxygen documentation generation
#---------------------------------------------------------------------------------------

list(APPEND OPEND_DOXYGEN_INPUT
    ${CMAKE_SOURCE_DIR}/src/opend " "
)

if(BUILD_DOC)

    # Variables for use by generic doxygen configuration file.
    set(DOXYGEN_PRODUCT_NAME "openD unified API")
    set(DOXYGEN_PROJECT_NUMBER "1.0.0")
    set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/doc)
    set(DOXYGEN_CUSTOM_RESOURCES_DIR ${PROJECT_SOURCE_DIR}/doc)
    set(DOWNLOADED_MODUELES_DIR ${PROJECT_SOURCE_DIR}/cmake/modules)

    string(APPEND DOXYGEN_INPUT ${DOXYGEN_CUSTOM_RESOURCES_DIR}/doxygen/mainpage.dox " ")
    string(APPEND DOXYGEN_INPUT ${DOXYGEN_CUSTOM_RESOURCES_DIR}/doxygen/architecture.dox " ")
    string(APPEND DOXYGEN_INPUT ${DOXYGEN_CUSTOM_RESOURCES_DIR}/doxygen/audio.dox " ")

    string(APPEND DOXYGEN_INPUT ${OPEND_DOXYGEN_INPUT} " ")
    string(APPEND DOXYGEN_INPUT ${PROJECT_BINARY_DIR})

    string(APPEND DOXYGEN_IMAGE_PATH ${PROJECT_SOURCE_DIR}/doc/doxygen " ")


    message(STATUS "doxyfile input: ${DOXYGEN_INPUT}")

    # Include cmake modules.
    list(APPEND CMAKE_MODULE_PATH ${DOWNLOADED_MODUELES_DIR})
    include(DoxygenRequiredVersion)

    configure_file(${DOXYGEN_CUSTOM_RESOURCES_DIR}/doxygen/Doxyfile.in
        ${PROJECT_BINARY_DIR}/Doxyfile @ONLY
    )

    file(APPEND ${PROJECT_BINARY_DIR}/Doxyfile
      EXTRACT_ALL            = YES\n
      # Disable the usage of graphviz.
      HAVE_DOT             = NO\n
    )

    # Set the readme file as mainpage.
    file(APPEND ${PROJECT_BINARY_DIR}/Doxyfile
        "USE_MDFILE_AS_MAINPAGE = README.md\n"
        "FILE_PATTERNS = *.h"
    )

    add_custom_target(doc ALL
        ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        SOURCES ${PROJECT_BINARY_DIR}/Doxyfile
    )

    install(DIRECTORY ${PROJECT_BINARY_DIR}/doc/html DESTINATION ${CMAKE_INSTALL_DATADIR}/doc/${PROJECT_NAME})
endif()
