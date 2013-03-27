#####
##
## Copyright (C) 2012 by the deal.II authors
##
## This file is part of the deal.II library.
##
## <TODO: Full License information>
## This file is dual licensed under QPL 1.0 and LGPL 2.1 or any later
## version of the LGPL license.
##
## Author: Matthias Maier <matthias.maier@iwr.uni-heidelberg.de>
##
#####

#
# Tests whether it is possible to compile and link a dummy program with a
# given flag.
# If so, add it to variable.
#
# Usage:
#     ENABLE_IF_LINKS(variable flag)
#

MACRO(ENABLE_IF_LINKS _variable _flag)
  STRING(STRIP "${_flag}" _flag_stripped)
  STRING(REGEX REPLACE "^-" "" _flag_name "${_flag_stripped}")
  STRING(REPLACE "," "" _flag_name "${_flag_name}")
  STRING(REPLACE "-" "_" _flag_name "${_flag_name}")

  IF(NOT "${_flag_stripped}" STREQUAL "")
    ADD_FLAGS(CMAKE_REQUIRED_FLAGS "${_flag_stripped}")
    CHECK_CXX_SOURCE_COMPILES(
    "
    int main() { return 0; }
    "
    DEAL_II_HAVE_FLAG_${_flag_name}
    )
    STRIP_FLAG(CMAKE_REQUIRED_FLAGS "${_flag_stripped}")
    IF(DEAL_II_HAVE_FLAG_${_flag_name})
      SET(${_variable} "${${_variable}} ${_flag_stripped}")
      STRING(STRIP "${${_variable}}" ${_variable})
    ENDIF()
  ENDIF()
ENDMACRO()

