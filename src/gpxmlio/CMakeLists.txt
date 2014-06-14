file(GLOB SOURCES Gp*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_library(gpxmlio STATIC ${SOURCES})