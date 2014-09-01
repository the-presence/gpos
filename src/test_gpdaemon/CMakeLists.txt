file(GLOB SOURCES *.cpp)

add_executable(test_gpdaemon ${SOURCES})
target_link_libraries(test_gpdaemon gpdaemon)
#set(TDATA ${EXECUTABLE_OUTPUT_PATH}/testdata)
#add_custom_target(test_gpxmlio_data ALL
#  COMMAND mkdir -p ${TDATA}
#  COMMAND cp ${CMAKE_SOURCE_DIR}/testdata/gpxmlio/parserTest.xml ${TDATA}
#  DEPENDS test_gpxmlio)