# Install script for directory: /workdir/airoha/mcu

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/toolchains/zephyr-sdk-0.16.9/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/cmake/ab162x/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/nvkey/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/modules/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/bluetooth/controller/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/pka/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/bluetooth/services/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/ull_hid_le/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/bluetooth/host/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/prebuilt/system/ab162x/offline_dump/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/partition/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/bt_air/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/race/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/argb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/version/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/third_party/lzma_decoder/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/prebuilt/system/ab162x/logging/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/prebuilt/system/ab162x/exception_handler/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/usb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/led/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/rgb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/fota/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/ram_blocks_control/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/pd_domain_control/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/gesture/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/hid/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/io_expander/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/app_framework/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/mux/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/soundmaker/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/hw_keyscan/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/bootreason_check/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/subsys/airoha/battery_management/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/upper_level/cmake_install.cmake")
endif()

