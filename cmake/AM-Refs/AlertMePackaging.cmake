if(NOT ARCH_PC)

  if(NOT HUB_VERSION)
    set(HUB_VERSION 0.0.1)
  endif(NOT HUB_VERSION)
  DebugFlag(HUB_VERSION)

  if(NOT MULTIPLEXOR_VERSION)
    set(MULTIPLEXOR_VERSION 0.0.1)
  endif(NOT MULTIPLEXOR_VERSION)
  DebugFlag(MULTIPLEXOR_VERSION)

  set(DEVICE_ABSTRACTION_VERSION ${MULTIPLEXOR_VERSION})

  if(ARCH_ARM_NANO1)
    set(ARCHITECTURE armv4)
  else(ARCH_ARM_NANO1)
    set(ARCHITECTURE alertmehub)
  endif(ARCH_ARM_NANO1)
  #
  # Opkg tools
  #
  set(OPKG_UTILS ${CMAKE_SOURCE_DIR}/tools/opkg-utils)
  set(OPKG_OWNER root)
  set(OPKG_GROUP root)
  set(OPKG_BUILD ${OPKG_UTILS}/opkg-build)
  set(OPKG_MAKE_INDEX ${OPKG_UTILS}/opkg-make-index)
  set(OPKG_CONTROL ${CMAKE_SOURCE_DIR}/cmake/opkg-consed)
  #
  # Helper scripts that avoid us putting error-pron
  # sed manipulations directly into COMMAND instructions
  #
  set(SED_VERSION ${CMAKE_SOURCE_DIR}/cmake/sed_version)
  set(SED_ARCH ${CMAKE_SOURCE_DIR}/cmake/sed_architecture)
  set(SED_MUX ${CMAKE_SOURCE_DIR}/cmake/sed_multiplexor)
  set(SED_DA ${CMAKE_SOURCE_DIR}/cmake/sed_da_version)
  set(SED_PKG ${CMAKE_SOURCE_DIR}/cmake/sed_package)
  set(SED_DESC ${CMAKE_SOURCE_DIR}/cmake/sed_descript)
  set(SEDP_EXCHANGE ${CMAKE_SOURCE_DIR}/cmake/sedp_exchange)
  set(SEDP_HWVERSION ${CMAKE_SOURCE_DIR}/cmake/sedp_hwversion)
  set(SEDP_HWVERSION2 ${CMAKE_SOURCE_DIR}/cmake/sedp_hwversion2)
  set(SEDP_KEY ${CMAKE_SOURCE_DIR}/cmake/sedp_key)
  set(SEDP_PROTOCOL ${CMAKE_SOURCE_DIR}/cmake/sedp_protocol)
  set(SEDP_MANUFACTURER ${CMAKE_SOURCE_DIR}/cmake/sedp_manufacturer)
  set(SEDP_MODEL ${CMAKE_SOURCE_DIR}/cmake/sedp_model)
  set(SEDP_SWVERSION ${CMAKE_SOURCE_DIR}/cmake/sedp_swversion)
  set(SEDP_URL ${CMAKE_SOURCE_DIR}/cmake/sedp_url)
  #
  # Delivering the different types of package artefact
  #
  set(PACKAGES_OUTPUT_PATH ${PROJECT_BINARY_DIR}/hub_packages)
  if(NOT EXISTS ${PACKAGES_OUTPUT_PATH})
    file(MAKE_DIRECTORY ${PACKAGES_OUTPUT_PATH})
  endif(NOT EXISTS ${PACKAGES_OUTPUT_PATH})

  set(FWPACKAGES_OUTPUT_PATH ${PROJECT_BINARY_DIR}/firmware_packages)
  if(NOT EXISTS ${FWPACKAGES_OUTPUT_PATH})
    file(MAKE_DIRECTORY ${FWPACKAGES_OUTPUT_PATH})
  endif(NOT EXISTS ${FWPACKAGES_OUTPUT_PATH})
  #
  # Making sure destination directories are available
  # for file operations
  #
  macro(set_pack_target tvariable tpath)
    if(NOT EXISTS ${tpath})
      file(MAKE_DIRECTORY ${tpath})
    endif()
    set(${tvariable} ${tpath})
  endmacro()

  #
  # Helpers for firmware packaging
  #
  macro(get_firmware url version file)
    add_custom_target(${file} ALL
      COMMAND wget ${url}/${version}/${file})
  endmacro(get_firmware)

  macro(build_fw_package package model version firmware-file desc)
    set(FILE_URL FILE:///opt/alertme/devices/${PROTOCOL}/${MANUFACTURER}/${firmware-file})
    set(PACKVER ${package}-${version})
    set(GLOBFWDEPS ${GLOBFWDEPS} ${package}-${firmware-file})
    add_custom_target(${package}-${firmware-file} ALL
      COMMAND rm -fr ${PKG_DIR}
      COMMAND mkdir -p ${PKG_CONTROL_DIR}
      COMMAND mkdir -p ${PKG_DEV_DIR}
      COMMAND cp ${CONTROL} ${PKG_CONTROL_DIR}
      COMMAND cp ${POSTINST} ${PKG_CONTROL_DIR}
      COMMAND cp ${firmware-file} ${PKG_DEV_DIR}
      COMMAND ${SED_PKG} -a ${PACKVER} -o ${PKG_CONTROL_DIR}/control
      COMMAND ${SED_VERSION} -a ${version} -o ${PKG_CONTROL_DIR}/control
      COMMAND ${SED_DESC} -a ${desc} -o ${PKG_CONTROL_DIR}/control
      COMMAND ${SEDP_EXCHANGE} -a ${EXCHANGE} -o ${PKG_CONTROL_DIR}/postinst
      COMMAND ${SEDP_KEY} -a ${KEY} -o ${PKG_CONTROL_DIR}/postinst
      COMMAND ${SEDP_PROTOCOL} -a ${PROTOCOL} -o ${PKG_CONTROL_DIR}/postinst
      COMMAND ${SEDP_MANUFACTURER} -a ${MANUFACTURER} -o ${PKG_CONTROL_DIR}/postinst
      COMMAND ${SEDP_MODEL} -a ${model} -o ${PKG_CONTROL_DIR}/postinst
      COMMAND ${SEDP_SWVERSION} -a ${SWVERSION} -o ${PKG_CONTROL_DIR}/postinst
      COMMAND ${SEDP_HWVERSION} -a ${HWVERSION} -o ${PKG_CONTROL_DIR}/postinst
      COMMAND ${SEDP_HWVERSION2} -a ${HWVERSION} -o ${PKG_CONTROL_DIR}/postinst
      COMMAND ${SEDP_URL} -a ${FILE_URL} -o ${PKG_CONTROL_DIR}/postinst
      COMMAND ${OPKG_BUILD} -o ${OPKG_OWNER} -g ${OPKG_GROUP} ${PKG_DIR} ${FWPACKAGES_OUTPUT_PATH}
      DEPENDS ${firmware-file})
  endmacro(build_fw_package)

  macro(build_batch_component_package package version firmware-file batch desc)
    set(PACKVER ${package}-${version})
    set(GLOBFWDEPS ${GLOBFWDEPS} ${package}-${version})
    add_custom_target(${package}-${version} ALL
      COMMAND rm -fr ${PKG_DIR}
      COMMAND mkdir -p ${PKG_CONTROL_DIR}
      COMMAND mkdir -p ${PKG_DIR}/${PKG_DEV_COMPONENT_DIR}
      COMMAND cp ${CONTROL} ${PKG_CONTROL_DIR}
      COMMAND cp ${batch} ${PKG_DIR}/${PKG_DEV_COMPONENT_DIR}
      COMMAND ${SED_PKG} -a ${PACKVER} -o ${PKG_CONTROL_DIR}/control
      COMMAND ${SED_VERSION} -a ${version} -o ${PKG_CONTROL_DIR}/control
      COMMAND ${SED_DESC} -a ${desc} -o ${PKG_CONTROL_DIR}/control
      COMMAND ${OPKG_BUILD} -o ${OPKG_OWNER} -g ${OPKG_GROUP} ${PKG_DIR} ${FWPACKAGES_OUTPUT_PATH}
      DEPENDS ${batch})
  endmacro(build_batch_component_package package version firmware-file batch desc)

  macro(build_component_package package version firmware-file target-file desc)
    set(PACKVER ${package}-${version})
    set(GLOBFWDEPS ${GLOBFWDEPS} ${package}-${firmware-file})
    add_custom_target(${package}-${firmware-file} ALL
      COMMAND rm -fr ${PKG_DIR}
      COMMAND mkdir -p ${PKG_CONTROL_DIR}
      COMMAND mkdir -p ${PKG_DIR}/${PKG_DEV_COMPONENT_DIR}
      COMMAND cp ${CONTROL} ${PKG_CONTROL_DIR}
      COMMAND cp ${firmware-file} ${PKG_DIR}/${PKG_DEV_COMPONENT_DIR}/${target-file}
      COMMAND ${SED_PKG} -a ${PACKVER} -o ${PKG_CONTROL_DIR}/control
      COMMAND ${SED_VERSION} -a ${version} -o ${PKG_CONTROL_DIR}/control
      COMMAND ${SED_DESC} -a ${desc} -o ${PKG_CONTROL_DIR}/control
      COMMAND ${OPKG_BUILD} -o ${OPKG_OWNER} -g ${OPKG_GROUP} ${PKG_DIR} ${FWPACKAGES_OUTPUT_PATH}
      DEPENDS ${firmware-file})
  endmacro(build_component_package)


  #
  # For pushing a list of config files into a destination directory
  #
  macro(prepare_package_configs confdir configlist)
    foreach(confile ${configlist})
      if(EXISTS ${confile})
        configure_file(${confile}
          ${confdir}
          @ONLY IMMEDIATE)
        # message(STATUS "Copied ${confile} into ${confdir}")
      else(EXISTS ${confile})
        message(FATAL_ERROR "Can't see ${confile}")
      endif(EXISTS ${confile})
    endforeach(confile ${conlist})
  endmacro(prepare_package_configs)
  #
  # For pushing a list of bins/libs into a destination directory
  #
  # Manages dependencies for each binary target in the list
  #
  # NOTE
  #     Side-effects are extension of GLOBAL_DEPS variable contents and
  #     increments GLOBAL_LCTR to manage unique target names.
  #
  macro(prepare_package_bins pname bindir dependency binaries)
    unset(PPTP_PKG)
    unset(PPTP_BIN)
    set(PPTP_PKG ${pname}-package)
    set(PPTP_BIN ${PPTP_PKG}-binary)
    set(GLOBAL_DEPS ${GLOBAL_DEPS} ${dependency})
    foreach(binfile ${binaries})
      DebugFlag(binfile)
      math(EXPR GLOBAL_LCTR ${GLOBAL_LCTR}+1) # This is how CMake does global_lctr++
      set(NDEP ${PPTP_BIN}-${GLOBAL_LCTR}) # Create a dummy unique dependency value
      # Set up a custom target dependency on each of our binaries,
      # so that we only attempt to copy it whenever it gets re/built
      add_custom_target(${NDEP} ALL
        COMMAND cp ${binfile} ${bindir}
        DEPENDS ${dependency})
      # Keep track of all the dummy dependencies we have generated
      set(GLOBAL_DEPS ${GLOBAL_DEPS} ${NDEP})
    endforeach(binfile ${binaries})
  endmacro(prepare_package_bins)
  #
  # Set the build-specific values in the package control file
  #
  macro(update_package_control pname tpath)
    unset(TPCON_PKG)
    set(TPCON_PKG ${pname}-package-control)
    # Ensure we run some custom commands before we execute our 'link' dependency
    add_custom_target(${TPCON_PKG} ALL
      COMMAND cat ${tpath}
      COMMAND ${SED_ARCH} -a ${ARCHITECTURE} -o ${tpath}
      COMMAND ${SED_MUX} -a ${MULTIPLEXOR_VERSION} -o ${tpath}
      COMMAND ${SED_DA} -a ${DEVICE_ABSTRACTION_VERSION} -o ${tpath}
      COMMAND ${SED_VERSION} -a ${HUB_VERSION} -o ${tpath}
      COMMAND cat ${tpath})
    set(GLOBAL_DEPS ${TPCON_PKG})
  endmacro(update_package_control)

  #
  # Package index preparation macro
  #
  macro(prepare_package_index dep directory)
    add_custom_target(${dep} ALL
      COMMAND ${OPKG_MAKE_INDEX} ${directory} > Packages
      COMMAND cp Packages ${directory}
      COMMAND mv Packages.stamps ${directory}
      COMMAND gzip -9 Packages
      COMMAND mv Packages.gz ${directory}
      )
  endmacro(prepare_package_index directory)

  #
  # Deploy built firmware packages to repository and firmware feed
  #
  macro(deploy_firmware deps)
    add_custom_target( ${deps} ALL
      COMMAND ${CMAKE_SOURCE_DIR}/zoo.hub.packages/deploy-scripts/deploy-staging-firmware.sh ${CMAKE_SOURCE_DIR} )
  endmacro(deploy_firmware)

  #
  # Deploy appropriate hub packages to repository and firmware feed
  #
  macro(deploy_packages deps)
    set(DEPLOY_SCRIPT_PATH ${CMAKE_SOURCE_DIR}/zoo.hub.packages/deploy-scripts)
    if(ARCH_ARM_NANO1)
      add_custom_target( ${deps} ALL
        COMMAND ${DEPLOY_SCRIPT_PATH}/deploy-staging-nano1.sh ${CMAKE_SOURCE_DIR} )
    endif(ARCH_ARM_NANO1)
    if(ARCH_ARM_NANO2)
      add_custom_target( ${deps} ALL
        COMMAND ${DEPLOY_SCRIPT_PATH}/deploy-staging-nano2.sh ${CMAKE_SOURCE_DIR} )
    endif(ARCH_ARM_NANO2)
  endmacro(deploy_packages)


endif(NOT ARCH_PC)
