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
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/acpica/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/adi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/altera/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_ambiq/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/atmel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_espressif/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_ethos_u/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_gigadevice/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_infineon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_intel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/microchip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/nuvoton/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_nxp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/openisa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/quicklogic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_renesas/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_rpi_pico/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_silabs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/stm32/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_telink/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/ti/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/xtensa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/trusted-firmware-a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/modules/airoha/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workdir/out/ab1620dm_evk/Keychron_LM7_dongle/Keychron_LM7_dongle_design/zephyr/cmake/reports/cmake_install.cmake")
endif()

