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
## @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
## @author     Patrick Weber
## @author     Adrian Antonana
## @brief      openD unified API
##

#---------------------------------------------------------------------------------------
# Include required modules
#---------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------
# Required dependencies versions
#---------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------
# Find required packages
#---------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------
# Options
#---------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------
# Product info
#---------------------------------------------------------------------------------------
set(PROJECT_PRODUCT_COMPANY "STACKFORCE & DECT Forum" CACHE STRING "company")
set(PROJECT_PRODUCT_NAME    "openD unified API" CACHE STRING "product")

#---------------------------------------------------------------------------------------
# Headers and sources
#---------------------------------------------------------------------------------------
set(OPEND_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/opend.c
    ${CMAKE_CURRENT_LIST_DIR}/opend_audio.c
    ${CMAKE_CURRENT_LIST_DIR}/opend_call.c
    ${CMAKE_CURRENT_LIST_DIR}/opend_hanfun.c
    ${CMAKE_CURRENT_LIST_DIR}/opend_mgmt.c
    ${CMAKE_CURRENT_LIST_DIR}/opend_sixlowpan.c
    ${CMAKE_CURRENT_LIST_DIR}/opend_sub.c
)

set(OPEND_DOXYGEN_INPUT
    ${CMAKE_CURRENT_LIST_DIR} " "
    ${CMAKE_CURRENT_LIST_DIR}/hanfun " "
    ${CMAKE_CURRENT_LIST_DIR}/hanfun/interfaces " "
    ${CMAKE_CURRENT_LIST_DIR}/hanfun/profiles " "
    PARENT_SCOPE
)

# configure version header
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/version.h.in
    ${PROJECT_BINARY_DIR}/version.h
)

#---------------------------------------------------------------------------------------
# Targets
#---------------------------------------------------------------------------------------
add_library( libOpenD ${OPEND_SOURCES} )

#---------------------------------------------------------------------------------------
# Install/export targets and files
#---------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------
# Create release packages
#---------------------------------------------------------------------------------------

