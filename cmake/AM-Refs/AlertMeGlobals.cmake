#
# This generate lots of screen noise.
# Use only in extremis as it gives
# a verbose make output during the build and
# should not be defined in normal circumstances.
#
set(CMAKE_VERBOSE_MAKEFILE ON)
#

#
# For debugging the cmake process
# when in cmake debug mode
#
# e.g. DebugMessage("Hello World")
#
macro(DebugMessage COMMENT)
  if(CMAKE_ZOO_DEBUG_MODE)
    message(STATUS "${COMMENT}")
  endif(CMAKE_ZOO_DEBUG_MODE)
endmacro()
#
# A shorthand way of getting cmake flag values out
# when in cmake debug mode
#
# e.g. DebugFlag(PROJECT_BINARY_DIR)
#
macro(DebugFlag FLAG)
  if(CMAKE_ZOO_DEBUG_MODE)
    message(STATUS "${FLAG} : ${${FLAG}}")
  endif(CMAKE_ZOO_DEBUG_MODE)
endmacro()

#
# Helper macros for those cunning shared modules that
# aren't libXXXX.so
#
macro(append_map_link_flags target)
  set(new_link_flags "-Wl,--no-whole-archive -Wl,-Map,${LIBRARY_OUTPUT_PATH}/${target}.map")
  get_target_property(existing_link_flags ${target} LINK_FLAGS)
  if(existing_link_flags)
    set(new_link_flags "${existing_link_flags} ${new_link_flags}")
  endif(existing_link_flags)
  DebugFlag(new_link_flags)
  set_target_properties(${target} PROPERTIES LINK_FLAGS "${new_link_flags}")
endmacro(append_map_link_flags)

macro(add_shared_module target src)
  add_library(${target} SHARED ${src} ${ARGN})
  set_target_properties(${target}
    PROPERTIES PREFIX "")
  append_map_link_flags(${target})
endmacro(add_shared_module)

#macro(add_shared_module_package target deps libs opts)
# add_custom_target($(target) ALL
#  COMMAND ${CMAKE_C_COMPILER} -shared -o ${LIBRARY_OUTPUT_PATH}/${target} ${libs} ${opts}
# DEPENDS ${deps})
#endmacro(add_shared_module_package)
#
# Need to find some packages to ensure the requested build configuration is sane
#
include(FindPackageHandleStandardArgs)

macro(FindCppcheck)
  find_program(CPPCHECK_EXECUTABLE cppcheck DOC "path to the cppcheck executable")
  mark_as_advanced(CPPCHECK_EXECUTABLE)
  if(CPPCHECK_EXECUTABLE)
    execute_process(COMMAND ${CPPCHECK_EXECUTABLE} --version
      OUTPUT_VARIABLE CPPCHECK_version_output
      ERROR_VARIABLE CPPCHECK_version_error
      RESULT_VARIABLE CPPCHECK_version_result
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REPLACE "Cppcheck " "" CPPCHECK_VERSION "${CPPCHECK_version_output}")
    #    set(CPPCHECK_VERSION ${CPPCHECK_version_output})
  endif(CPPCHECK_EXECUTABLE)
  find_package_handle_standard_args(cppcheck REQUIRED_VARS CPPCHECK_EXECUTABLE VERSION_VAR CPPCHECK_VERSION)
endmacro(FindCppcheck)


FindCppcheck()

macro(FindLcov)
  find_program(LCOV_EXECUTABLE lcov DOC "path to the lcov executable")
  mark_as_advanced(LCOV_EXECUTABLE)
  if(LCOV_EXECUTABLE)
    execute_process(COMMAND ${LCOV_EXECUTABLE} --version
      OUTPUT_VARIABLE LCOV_version_output
      ERROR_VARIABLE LCOV_version_error
      RESULT_VARIABLE LCOV_version_result
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REPLACE "lcov: LCOV version " "" LCOV_VERSION "${LCOV_version_output}")
    #    set(LCOV_VERSION ${LCOV_version_output})
  endif(LCOV_EXECUTABLE)
  find_package_handle_standard_args(lcov REQUIRED_VARS LCOV_EXECUTABLE VERSION_VAR LCOV_VERSION)
endmacro(FindLcov)

FindLcov()

macro(FindGcov)
  find_program(GCOV_EXECUTABLE gcov DOC "path to the gcov executable")
  mark_as_advanced(GCOV_EXECUTABLE)
  if(GCOV_EXECUTABLE)
    execute_process(COMMAND ${GCOV_EXECUTABLE} --version
      OUTPUT_VARIABLE GCOV_version_output
      ERROR_VARIABLE GCOV_version_error
      RESULT_VARIABLE GCOV_version_result
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    #string(REPLACE "gcov (*) " "" GCOV_VERSION "${GCOV_version_output}")
    set(GCOV_VERSION ${GCOV_version_output})
  endif(GCOV_EXECUTABLE)
  find_package_handle_standard_args(gcov REQUIRED_VARS GCOV_EXECUTABLE VERSION_VAR GCOV_VERSION)
endmacro(FindGcov)

FindGcov()
