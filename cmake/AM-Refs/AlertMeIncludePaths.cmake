#
# Headers are spread out all over the source tree
#
#

set(EMBERZNET_TOP ${CMAKE_SOURCE_DIR}/external_src/${EMBERZNET_VERSION})

set(SRCTOP ${CMAKE_SOURCE_DIR}/src)
set(INCTOP ${CMAKE_SOURCE_DIR}/include)

set(COMMON_INC ${INCTOP}/common)
set(JSON_INC ${INCTOP}/json)

set(AMQP_INC ${INCTOP}/amqp)
set(AMQP_SRC ${SRCTOP}/amqp)

set(DAEMON_INC ${INCTOP}/daemon)
set(DAEMON_SRC ${SRCTOP}/daemon)

set(ZIGBEE_INC ${INCTOP}/zigbee)
set(ZIGBEE_SRC ${SRCTOP}/zigbee)

set(HDM_INC ${INCTOP}/hdm)
set(HDM_SRC ${SRCTOP}/hdm)

set(DAL_INC ${INCTOP}/dal)
set(DAL_SRC ${SRCTOP}/dal)

set(DSTR_INC ${INCTOP}/datastore)
set(DSTR_SRC ${SRCTOP}/datastore)
set(DSTRCLI_SRC ${SRCTOP}/datastore_client)

set(DSTRCLI ${DSTRCLI_SRC}/datastoreclient.c)
set(DSTRFNS ${DSTRCLI_SRC}/datastorefns.c)
set(DSTRTAG ${DSTRCLI_SRC}/datastoretags.c)
set(DSTRSRCS ${DSTRCLI} ${DSTRFNS} ${DSTRTAG})

set(HUBMGR_INC ${INCTOP}/hubmanager)
set(HUBMGR_SRC ${SRCTOP}/hubmanager)

set(ZBDEV_SRC ${SRCTOP}/zigbee_zbdal_devices)

set(THIRDPARTYDIR
  ${CMAKE_SOURCE_DIR}/external_src)
set(ZEROMQDIR
  ${THIRDPARTYDIR}/zeromq-3.2.3)
set(RABBITMQCDIR
  ${THIRDPARTYDIR}/rabbitmq-c-rabbitmq-c-v0.3.0)
set(RABBIT_INC ${RABBITMQCDIR}/librabbitmq)

set(COMMON_TESTS ${SRCTOP}/common_tests)

set(CHECK_SRC ${SRCTOP}/check)
set(CHECK_INC ${INCTOP}/check)

set(CHECKTOOLS ${CHECK_SRC}/checktools.c)
set(CHECKDAEMON ${CHECK_SRC}/check_daemon_stubs.c)
set(CHECKJSON ${CHECK_SRC}/check_json_template.c)
#
set(ST_INC
  ${COMMON_INC}
  ${JSON_INC}
  ${AMQP_INC}
  ${DAEMON_INC}
  ${ZIGBEE_INC}
  ${HDM_INC}
  ${DAL_INC}
  ${DSTR_INC}
  ${HUBMGR_INC}
  ${CHECK_INC}
  )
# This is a massive stringified list used for static analysis
# Not recommended for normal build purposes
set(STAT_INC
  ${COMMON_INC}
  ${JSON_INC}
  ${AMQP_INC}
  ${DAEMON_INC}
  ${ZIGBEE_INC}
  ${HDM_INC}
  ${DAL_INC}
  ${DSTR_INC}
  ${HUBMGR_INC}
  ${CHECK_INC}
  ${RABBIT_INC}
  ${ZEROMQDIR}/include
  ${EMBERZNET_TOP}
  ${EMBERZNET_TOP}/stack
  )
foreach(fileName ${STAT_INC})
  #MESSAGE(STATUS "Process path: ${fileName}")
  # Generate output path include directive
  string(REGEX REPLACE "^/" "-I/" outfile "${fileName}")
  #message(STATUS "Output path: ${outfile}")
  # Finally remember the output
  SET(STAT_INC_FLAGS ${STAT_INC_FLAGS} "${outfile}")
endforeach(fileName)
DebugFlag(STAT_INC_FLAGS)


