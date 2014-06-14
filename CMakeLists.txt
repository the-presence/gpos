cmake_minimum_required(VERSION 2.8)

project(gpos)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(DebugMessage)
include(GlobalConfiguration)
DebugFlag(PROJECT_BINARY_DIR)
DebugFlag(CMAKE_CURRENT_BINARY_DIR)

add_subdirectory(external_src)
add_subdirectory(src)

DebugMessage("All done debug message!")
