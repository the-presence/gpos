#
# Which version of rabbitmq-c are we using?
#
set(RABBIT_VERSION_0p3 1)
#set(RABBIT_VERSION_0p5 1)
#
# Which version of zeromq are we using?
#
set(ZEROMQ zeromq-3.2.3)
#set(ZEROMQ zeromq-4.0.4)
#
# Building the Ember stack
#
set(EMBERSTACK 1)
set(EMBERZNET_VERSION EmberZNet4.6.4-GA)

if(PACK)
  set(PACKAGE 1)
endif(PACK)

if(DEP)
  set(DEPLOY 1)
endif(DEP)

if(CPPCHECK)
  set(STATIC_ANALYSIS 1)
endif()

#####################################################################
#
# PC build configuration
#
#####################################################################
if(PC)
  set(ARCH_PC 1)
  set(PROJECT_BINARY_DIR ${BDIR}/x86-linux-gnu)
  # Support conditional compilation sections that may (do) exist in the code
  add_definitions(-DARCH_PC)
  # Ensure previous build artefacts don't interfere
  unset(PC CACHE)
  unset(ARCH_ARM CACHE)
  unset(ARCH_ARM_NANO1 CACHE)
  unset(ARCH_ARM_NANO2 CACHE)
  # We might be building some tests
  if(COVERAGE_BUILD)
    set(BUILDTESTS 1)
  endif(COVERAGE_BUILD)
  if(CHECK_BUILD)
    set(BUILDTESTS 1)
  endif(CHECK_BUILD)
  if(MEMCHECK_BUILD)
    set(BUILDTESTS 1)
  endif(MEMCHECK_BUILD)
  if(BUILDTESTS)
    include(CTest)
    include(Dart)
    enable_testing()
    include(AlertMeUnitTesting)
    message(STATUS "Testing enabled")
    if(COVERAGE_BUILD)
      include(AlertMeCodeCoverage)
      message(STATUS "Code coverage enabled")
    endif(COVERAGE_BUILD)
  endif(BUILDTESTS)
endif(PC)

#####################################################################
#
# nano1 build configuration
#
#####################################################################
if(NANO1)
  set(ARCH_ARM 1)
  set(ARCH_ARM_NANO1 1)
  set(PROJECT_BINARY_DIR ${BDIR}/nano1-arm-linux-gnu)
  # Support conditional compilation sections that may (do) exist in the code
  add_definitions(-DARCH_ARM_NANO1)
  add_definitions(-DARCH_ARM)
  # Conditional code for watchdog device type in watchdog_server.c
  add_definitions(-DSW_WATCHDOG)
  # Ensure previous build artefacts don't interfere
  unset(NANO1 CACHE)
  unset(ARCH_PC CACHE)
  unset(ARCH_ARM_NANO2 CACHE)
endif(NANO1)

#####################################################################
#
# nano2 build configuration
#
#####################################################################
if(NANO2)
  set(ARCH_ARM 1)
  set(ARCH_ARM_NANO2 1)
  set(PROJECT_BINARY_DIR ${BDIR}/nano2-arm-linux-gnu)
  # Support conditional compilation sections that may (do) exist in the code
  add_definitions(-DARCH_ARM_NANO2)
  add_definitions(-DARCH_ARM)
  # Ensure previous build artefacts don't interfere
  unset(NANO2 CACHE)
  unset(ARCH_PC CACHE)
  unset(ARCH_ARM_NANO1 CACHE)
endif(NANO2)

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
# and adding them at the architecture-level interferes with
# third-party software builds, so they are specified
# later, and further down the source tree.
#
#####################################################################

#
# We will be wanting to make packages for cross-compiled binaries
#
if(NOT ARCH_PC)
  include(AlertMePackaging)
endif(NOT ARCH_PC)
#####################################################################
#
# Setting up documentation target
#
#####################################################################
#
find_package(Doxygen)
if(NOT DOXYGEN_FOUND)
  message(WARNING "Doxygen is needed to build the documentation!")
else(NOT DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/AlertMeDoxyFile.in
    ${PROJECT_BINARY_DIR}/Doxyfile
    @ONLY IMMEDIATE)
  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
    SOURCES ${PROJECT_BINARY_DIR}/Doxyfile)
endif(NOT DOXYGEN_FOUND)

