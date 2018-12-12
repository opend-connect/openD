# =============================================================================
#
#   @file doc/CMakeLists.txt
#
#   HAN-FUN Library documentation CMakeList
#
#   @author  Filipe Alves <filipe.alves@bithium.com>
#
#   @version 1.3.0
#
#   Copyright (c) 2012 Bithium S.A.
#
# =============================================================================

# add a target to generate API documentation with Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/API.doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/API.doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/API.doxyfile
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                      COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
