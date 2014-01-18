macro(DebugMessage COMMENT)
  if(CMAKE_ZOO_DEBUG_MODE)
    message(STATUS "${COMMENT}")
  endif(CMAKE_ZOO_DEBUG_MODE)
endmacro()

macro(DebugFlag FLAG)
  if(CMAKE_ZOO_DEBUG_MODE)
    message(STATUS "${FLAG} : ${${FLAG}}")
  endif(CMAKE_ZOO_DEBUG_MODE)
endmacro()

include(DumpFlags)