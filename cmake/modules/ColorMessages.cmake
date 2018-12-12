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
## @author     STACKFORCE
## @author     Adrian Antonana <adrian.antonana@stackforce.de>
## @brief      Extra cmake messages
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

# colorized output
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")

function(colormessage)
    list(GET ARGV 0 MessageType)
  if(MessageType STREQUAL FATAL_ERROR OR MessageType STREQUAL SEND_ERROR)
    list(REMOVE_AT ARGV 0)
    message(${MessageType} "${BoldRed}>> ${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL WARNING)
    list(REMOVE_AT ARGV 0)
    message(${MessageType} "${BoldYellow}>> ${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL AUTHOR_WARNING)
    list(REMOVE_AT ARGV 0)
    message(${MessageType} "${BoldCyan}>> ${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL STATUS)
    list(REMOVE_AT ARGV 0)
    message(${MessageType} "${Green}>> ${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL INFO)
    list(REMOVE_AT ARGV 0)
    message("-- ${BoldBlue}>> ${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL NOTICE)
    list(REMOVE_AT ARGV 0)
    message("-- ${Blue}>> ${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL IMPORTANT)
    list(REMOVE_AT ARGV 0)
    message("-- ${Yellow}>> ${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL MORE_IMPORTANT)
    list(REMOVE_AT ARGV 0)
    message("-- ${BoldYellow}>> ${ARGV}${ColourReset}")
  else()
    message(">> ${ARGV}")
  endif()
endfunction()
