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
## @brief      openD unified API
##

cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Project version
#---------------------------------------------------------------------------------------
project(openDUnifiedAPI VERSION 1.0.0)
set(PROJECT_SEMVER_VERSION_SUFFIX "alpha.7")

if(PROJECT_SEMVER_VERSION_SUFFIX)
  set(PROJECT_SEMVER_VERSION ${PROJECT_VERSION}-${PROJECT_SEMVER_VERSION_SUFFIX})
else()
  set(PROJECT_SEMVER_VERSION ${PROJECT_VERSION})
endif()

add_subdirectory(src)
add_subdirectory(doc)
