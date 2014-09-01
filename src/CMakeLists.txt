include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(/usr/local/include)
add_subdirectory(gpxmlio)
add_subdirectory(gpdaemon)

add_subdirectory(test_gpxmlio)
add_subdirectory(test_gpdaemon)