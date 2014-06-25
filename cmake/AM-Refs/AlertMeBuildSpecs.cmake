#####################################################################
#
# Project-specific compiler options
#
#####################################################################
add_definitions(-pipe)
add_definitions(-std=c99)
add_definitions(-MD)
add_definitions(-Wall)
IF ((CMAKE_BUILD_TYPE STREQUAL "Debug") OR
    (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo"))
  add_definitions(-ggdb)
ENDIF()
add_definitions(-fPIC)
add_definitions(-D_POSIX_C_SOURCE=200112L)
add_definitions(-D_GNU_SOURCE)
add_definitions(-DHUBAPP)
add_definitions(-DPLATFORM_POSIX)
add_definitions(-DLINUX)
# add_definitions(-Wextra)
# Turn all warnings into errors - PC picohub is not (yet) warning free
#add_definitions(-Werror)
# Additional warnings and error checking
add_definitions(-Wstrict-overflow=1)
add_definitions(-Wlogical-op)
# NB.JAS: variable-length arrays are used in the ZeroMQ code and
# in cilClusterMgr_ProcessSimpleDescriptor() in the ZigBee stack.
# Leave this disabled unless the code is rewritten to eliminate them.
# add_definitions(-Wvla)

#
# PC build only
#
if(PC)
  add_definitions(-DPC_PICOHUB)
endif(PC)
