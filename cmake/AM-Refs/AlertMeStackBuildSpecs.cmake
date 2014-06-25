#####################################################################
#
# ISOP config-specific compiler options
#
#####################################################################
if(ARCH_PC)
  if(MINOR_REVISION)
    math(EXPR MINOR_REVISION ${MINOR_REVISION}+100)
  else(MINOR_REVISION)
    set(MINOR_REVISION 100)
  endif(MINOR_REVISION)
endif(ARCH_PC)

add_definitions(-DHUBAPP_MAJOR_VERSION=${MAJOR_REVISION})
add_definitions(-DHUBAPP_MINOR_VERSION=${MINOR_REVISION})
add_definitions(-DHUBAPP_RELEASE_VERSION=${BUILD_REVISION})

add_definitions(-DPICO_MAJOR_VERSION=0)
add_definitions(-DPICO_MINOR_VERSION=19)

if(NOT ARCH_PC)
  # ZigBee controller configuration
  add_definitions(-DENABLE_ZIGBEE_CONTROLLER)
  # ZigBee channel bitmask
  add_definitions(-DDEFAULT_CHANLIST=0x03fff800)  # 11-25
  # ZigBee message queue timeout, 0 to disable
  add_definitions(-DZC_QUEUE_TIMEOUT=TIMER_SEC\(27\))
  # Ember EZSP configuration
  set(EZSPDEVICE EM260)
  add_definitions(-DEZSP_SPI)
  # add_definitions(-DEZSP_UART)
endif(NOT ARCH_PC)

set(EMBERZNET_VERSION EmberZNet4.6.4-GA)

# Use libc malloc instead of ax_malloc
add_definitions(-DAX_USE_LIBC_MALLOC)

# Maximum number of devices in devtbl
if(NOT ARCH_PC)
  add_definitions(-DDEVTBL_MAX_DEVICES=64)
else(NOT ARCH_PC)
  add_definitions(-DDEVTBL_MAX_DEVICES=32)
endif(NOT ARCH_PC)

# Maximum number of virtual devices
if(NOT ARCH_PC)
  add_definitions(-DVIRTUAL_MAX_DEVICES=4)
else(NOT ARCH_PC)
  add_definitions(-DVIRTUAL_MAX_DEVICES=32)
endif(NOT ARCH_PC)

# Maximum number of inflight transport messages
if(NOT ARCH_PC)
  add_definitions(-DMAX_IN_FLIGHT_DEVICE_TRANSPORT_MESSAGES=50)
else(NOT ARCH_PC)
  add_definitions(-DMAX_IN_FLIGHT_DEVICE_TRANSPORT_MESSAGES=10)
endif(NOT ARCH_PC)

add_definitions(-DMAX_TLS_CONNECTIONS=2)
set(HOME_AUTOMATION_SUPPORT 1)
add_definitions(-DENABLE_HOME_AUTOMATION_SUPPORT)
set(NATIVE_CLUSTER_SUPPORT 1)
add_definitions(-DENABLE_NATIVE_CLUSTER_SUPPORT)

if(NOT ARCH_PC)
  add_definitions(-DENABLE_ZWAVE_SUPPORT)
  add_definitions(-DMOD_CLIMATE_SCHEDULE)
  add_definitions(-DENABLE_CAMERA_SUPPORT)
  add_definitions(-DMAX_CAMERAS=10)
  add_definitions(-DCAMERA_NOTIFY_PORT=80)
  add_definitions(-DCAMERA_USE_IGNORE=0)
endif(NOT ARCH_PC)

add_definitions(-DENABLE_CONFIG_CACHING)
add_definitions(-DRSA_SIG_ENABLED)
add_definitions(-DENABLE_VIRTUAL_DEVICES)
add_definitions(-DVPOWCLAMP)
add_definitions(-DVPOWMON)
add_definitions(-DVPOWCON)

if(ARCH_PC)
  add_definitions(-DENABLE_VCMD_INTERFACE)
  add_definitions(-DVIAS)
  add_definitions(-DVKFB)
  add_definitions(-DVCLIMATE)
  add_definitions(-DVDOORLOCK)
endif(ARCH_PC)

#
# PC build only
#
if(PC)
  add_definitions(-DPC_PICOHUB)
endif(PC)