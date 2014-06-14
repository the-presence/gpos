#
# For debugging the cmake process and getting flag values
# out when in cmake debug mode
#
include(DebugMessage)
#
# Generate lots of screen noise.
# Use only in extremis
#
# set(CMAKE_VERBOSE_MAKEFILE ON)

#####################################################################
#
# PC build configuration
#    incorporates configurations for
#    'check' 'memcheck' and 'coverage' builds
#    which are pc-only build configurations
#
#####################################################################
if(PC)
  set(ARCH_PC 1)
  set(PROJECT_BINARY_DIR ${BDIR}/x86-linux-gnu)
  add_definitions(-DARCH_PC)
  # Ensure previous build artefacts don't interfere
  unset(PC CACHE)
  # If we are doing coverage, check or memcheck builds
  # we need to be able to add and run unit tests
  if(CHECK_BUILD)
    # We do unit tests here
    include(CTest)
    enable_testing()
    set(BUILDTESTS 1)
    message(STATUS "Testing enabled")
  endif(CHECK_BUILD)
  if(COVERAGE_BUILD)
    include(CTest)
    enable_testing()
    set(BUILDTESTS 1)
    message(STATUS "Testing enabled")
    include(CodeCoverage)
    message(STATUS "Code coverage enabled")
  endif(COVERAGE_BUILD)
  if(MEMCHECK_BUILD)
    set(CMAKE_MEMORYCHECK_COMMAND valgrind)
    set(CMAKE_MEMORYCHECK_COMMAND_OPTIONS " ")
    set(BUILDTESTS 1)
    include(CTest)
    enable_testing()
    message(STATUS "Testing enabled")
    include(MemCheck)
    message(STATUS "Memory checks enabled")
  endif(MEMCHECK_BUILD)
  #
  # If we are building the test code, there is a
  # helper function, add_alertme_test
  # to keep this concise in the cmake files
  #
  if(BUILDTESTS)
    include(GlobalTestConfiguration)
  endif(BUILDTESTS)
endif(PC)

message(STATUS "Creating ${CMAKE_BUILD_TYPE} build")

#####################################################################
#
# Setting up some paths
#
#####################################################################
#
# Where are the build artefacts going?
#
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)
#
# Naturally we'll want to look into the output library directory
# for the libraries against which we want to link
#
link_directories(${LIBRARY_OUTPUT_PATH})
#
# Headers are spread out all over the source tree
#
# However:
#      Don't add any via include_directories() at this level,
#      otherwise they will break the rabbitmq build.
#
#set(INCLUDE_COMMON_INCLUDE ${CMAKE_SOURCE_DIR}/zoo.hub.common/include)
#set(INCLUDE_COMMON_SRC ${CMAKE_SOURCE_DIR}/zoo.hub.common/src)
#set(INCLUDE_AMQP ${CMAKE_SOURCE_DIR}/zoo.hub.amqp/src)
#set(INCLUDE_JSON ${CMAKE_SOURCE_DIR}/zoo.hub.json/src)
#set(INCLUDE_DAEMON ${CMAKE_SOURCE_DIR}/zoo.hub.daemon/src)

#####################################################################
#
# Project-specific compiler options
#
#####################################################################
add_definitions(-pipe)
#add_definitions(-std=c99)
add_definitions(-MD)
add_definitions(-Wall)
#add_definitions(-ggdb)
add_definitions(-fPIC)
add_definitions(-D_POSIX_SOURCE=200112L)
add_definitions(-D_GNU_SOURCE)
#add_definitions(-DHUBAPP)
#add_definitions(-DPLATFORM_POSIX)
#add_definitions(-DLINUX)
# add_definitions(-Wextra)
# Turn all warnings into errors - PC picohub is not (yet) warning free
# add_definitions(-Werror)
# Additional warnings and error checking
add_definitions(-Wstrict-overflow=1)
add_definitions(-Wlogical-op)
add_definitions(-Wvla)

#
# PC build specifics
#
if(PC)
endif(PC)
#####################################################################