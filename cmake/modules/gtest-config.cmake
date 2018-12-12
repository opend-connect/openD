##
## @code
##  ___ _____ _   ___ _  _____ ___  ___  ___ ___
## / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
## \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
## |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
## embedded.connectivity.solutions.==============
## @endcode
##
## @file
## @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
## @author     Lars Moellendorf
## @author     Adrian Antonana
## @brief      STACKFORCE CMake Module for googeltest
##
## This file is part of the STACKFORCE CMake modules collection
## (below "sf cmake modules collection").
##
## sf cmake modules collection is free software: you can redistribute it
## and/or modify it under the terms of the GNU Affero General Public License
## as published by the Free Software Foundation, either version 3 of the
## License, or (at your option) any later version.
##
## sf cmake modules collection is distributed in the hope that it will be
## useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Affero General Public License for more details.
##
## You should have received a copy of the GNU Affero General Public License
## along with sf cmake modules collection.
## If not, see <http://www.gnu.org/licenses/>.
##

cmake_minimum_required(VERSION 3.2)

if(TARGET googletest)
    MESSAGE(STATUS "googletest already exists!")
else()
    MESSAGE(STATUS "Add googletest")
    find_package(Threads REQUIRED)

    # Enable ExternalProject CMake module
    include(ExternalProject)

    # Configure the project for testing
    include(CTest)

    set(GTEST_GIT_REPOSITORY https://github.com/google/googletest.git)
    set(GTEST_GIT_TAG release-1.8.1)
    set(GTEST_PATCH_COMMAND)

    ExternalProject_Add(googletest   # Name for custom target
        GIT_REPOSITORY ${GTEST_GIT_REPOSITORY}
        GIT_TAG ${GTEST_GIT_TAG}
        UPDATE_DISCONNECTED 1
        PATCH_COMMAND ${GTEST_PATCH_COMMAND}
        INSTALL_COMMAND ""
    )

    ExternalProject_Get_Property(googletest source_dir)
    MESSAGE(STATUS "google source_dir is:\n " ${source_dir} )

    add_library(libgmock IMPORTED STATIC GLOBAL)
    add_dependencies(libgmock googletest)

    add_library(libgmock_main IMPORTED STATIC GLOBAL)
    add_dependencies(libgmock_main googletest_main)


    set(GTEST_INCLUDE_GOOGLETEST "${source_dir}/googletest/include/")
    set(GTEST_INCLUDE_GOOGLEMOCK "${source_dir}/googlemock/include/")

    # Set gmock properties
    ExternalProject_Get_Property(googletest source_dir binary_dir)
    set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        # This does not work as intended
        #"INTERFACE_INCLUDE_DIRECTORIES" "${GTEST_INCLUDE_GOOGLETEST}"
        #"INTERFACE_INCLUDE_DIRECTORIES" "${GTEST_INCLUDE_GOOGLEMOCK}"
    )
    # Set gmock properties
    set_target_properties(libgmock_main PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock_main.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        # This does not work as intended
        #"INTERFACE_INCLUDE_DIRECTORIES" "${GTEST_INCLUDE_GOOGLETEST}"
        #"INTERFACE_INCLUDE_DIRECTORIES" "${GTEST_INCLUDE_GOOGLEMOCK}"
    )

    include_directories("${GTEST_INCLUDE_GOOGLETEST}")
    include_directories("${GTEST_INCLUDE_GOOGLEMOCK}")

    # CMake seems to demand that the directories referenced by the
    # INTERFACE_INCLUDE_DIRECTORIES property of an IMPORTED target can be
    # found at configure-time. This is quite unhelpful if those directories
    # are only generated as part of the build.
    # This is a Workaround proposed in
    # bug report:
    # http://public.kitware.com/Bug/bug_relationship_graph.php?bug_id=14495
    # See also:
    # http://public.kitware.com/Bug/view.php?id=15052&nbn=2
    file(MAKE_DIRECTORY "${GTEST_INCLUDE_GOOGLETEST}")
    file(MAKE_DIRECTORY "${GTEST_INCLUDE_GOOGLEMOCK}")
    # Let other cmake targets know where to find the header files.
    set_property(TARGET libgmock APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                "${GTEST_INCLUDE_GOOGLETEST}"
                "${GTEST_INCLUDE_GOOGLEMOCK}"
    )
    # Let other cmake targets know where to find the header files.
    set_property(TARGET libgmock_main APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                "${GTEST_INCLUDE_GOOGLETEST}"
                "${GTEST_INCLUDE_GOOGLEMOCK}"
    )

endif()
