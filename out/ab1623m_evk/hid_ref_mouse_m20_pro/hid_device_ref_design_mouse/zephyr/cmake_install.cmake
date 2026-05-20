# Install script for directory: /workdir/zephyr

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
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/acpica/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/adi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/altera/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_ambiq/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/atmel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_espressif/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_ethos_u/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_gigadevice/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_infineon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_intel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/microchip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/nuvoton/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_nxp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/openisa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/quicklogic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_renesas/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_rpi_pico/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_silabs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/stm32/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_telink/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/ti/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/xtensa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/trusted-firmware-a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/modules/airoha/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1623m_evk/hid_ref_mouse_m20_pro/hid_device_ref_design_mouse/zephyr/cmake/reports/cmake_install.cmake")
endif()

