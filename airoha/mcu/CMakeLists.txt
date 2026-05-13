# Copyright Statement:
#
# (C) 2025  Airoha Technology Corp. All rights reserved.
#
# This software/firmware and related documentation ("Airoha Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
# Without the prior written permission of Airoha and/or its licensors,
# any reproduction, modification, use or disclosure of Airoha Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.
# You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
# if you have agreed to and been bound by the applicable license agreement with
# Airoha ("License Agreement") and been granted explicit permission to do so within
# the License Agreement ("Permitted User").  If you are not a Permitted User,
# please cease any access or use of Airoha Software immediately.
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
# ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
# WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
# CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
# AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.


if(DEFINED CONFIG_SOC_FAMILY_AIROHA)

    message(STATUS "ZEPHYR_VERSION_CODE: ${ZEPHYR_VERSION_CODE}")
    message(STATUS "KERNELVERSION: ${KERNELVERSION}")
    message(STATUS "KERNEL_VERSION_NUMBER: ${KERNEL_VERSION_NUMBER}")

    # from https://docs.zephyrproject.org/latest/develop/languages/c/index.html
    # In summary, it is recommended to use a compiler toolchain that supports
    # *** at least the C11 standard *** for developing with Zephyr.
    # It is, however, important to note that some optional Zephyr components
    # and external modules may make use of the C language features that
    # have been introduced in *** more recent versions of the standards ***,
    # in which case it will be necessary to use a more up-to-date compiler toolchain
    # that supports such standards.
    # Note: we can choose STD_C17 in zephyr v3.7.0
    if(KERNELVERSION STREQUAL "0x3030000")
        set_property(GLOBAL PROPERTY CSTD c17)
    endif()

    # In fact, the extraction of footprint information is still based on the map file,
    # and the symbols in the ELF file is incomplete.( ex. section str1.1 ... )
    # extract symbol information from ELF, including symbol size/attribute, etc
    # set_property(TARGET bintools PROPERTY symbols_flag "-Sa")

    # extract debug information from ELF(dwarf) to get information such as compilation unit and symbol
    # set_property(TARGET bintools PROPERTY readelf_flag "--debug-dump=info")

    # override the default flag so that C code and assembly code are not mixed
    set_property(TARGET bintools PROPERTY disassembly_flag_inline_source "")

    set(AIR_PREBUILT_LIB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt CACHE PATH "Airoha prebuilt library directory")
    set(AIR_MODULE_OUT_PATH ${APPLICATION_BINARY_DIR}/modules/airoha CACHE PATH "Airoha modules output directory")
    # Point to Airoha root directory, so that CMakeLists.txt in project can use AIR_ROOT_DIR
    set(AIR_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "Airoha root directory")

    set(AIR_SUBSYS_PKA_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/subsys/pka)
    set(AIR_SUBSYS_802154_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/ieee802154)

    message(NOTICE "[Airoha] AIR_PREBUILT_LIB_ROOT: ${AIR_PREBUILT_LIB_ROOT}")
    message(NOTICE "[Airoha] AIR_MODULE_OUT_PATH: ${AIR_MODULE_OUT_PATH}")
    message(NOTICE "[Airoha] APPLICATION_BINARY_DIR: ${APPLICATION_BINARY_DIR}")
    message(NOTICE "[Airoha] AIR_ROOT_DIR: ${AIR_ROOT_DIR}")
    message(NOTICE "[Airoha] AIR_COMMON_ROOT_DIR: ${AIR_COMMON_ROOT_DIR}")

    # We need to cache the build type so that it is not out of sync when CONF_FILE is cached.
    set(CONF_FILE_BUILD_TYPE ${CONF_FILE_BUILD_TYPE} CACHE INTERNAL "The build type")

    set(NVKEY_FILE_LIST "" CACHE STRING "nvkey file list" FORCE)

    add_subdirectory(cmake/${SOC_SERIES})
    if(KERNELVERSION STREQUAL "0x3030000")
        add_subdirectory(soc/${ARCH}/${SOC_FAMILY})
    endif()
    add_subdirectory(subsys/airoha/nvkey)
    add_subdirectory(modules)

    add_subdirectory(drivers)
    if(NOT CONFIG_BT_CTLR AND NOT CONFIG_BT_LL_SW_SPLIT)
    add_subdirectory_ifdef(CONFIG_BT subsys/airoha/bluetooth/controller/)
    add_subdirectory_ifdef(CONFIG_BT subsys/airoha/pka)
    endif()
    add_subdirectory_ifdef(CONFIG_BT subsys/airoha/bluetooth/services/)
    if(CONFIG_BT_ULL_HID_LE)
    add_subdirectory(subsys/airoha/ull_hid_le)
    endif()
    add_subdirectory_ifdef(CONFIG_OPENTHREAD_IPERF subsys/airoha/iperf)
    add_subdirectory_ifdef(CONFIG_BT subsys/airoha/bluetooth/host/)
    if(CONFIG_BT_LL_SW_SPLIT)
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/air_zephyr_le_controller_protected)
            add_subdirectory(subsys/airoha/air_zephyr_le_controller_protected)
        else()
            if(CONFIG_BT_DEVICE_NAME)
                string(REPLACE " " "_" AIR_CTRL_TYPE ${CONFIG_BT_DEVICE_NAME})
            else()
                set(AIR_CTRL_TYPE "hci_relay")
            endif()
            zephyr_library_import(libair_zephyr_le_controller_relay.a ${AIR_PREBUILT_LIB_ROOT}/middleware/airoha/bluetooth/${SOC_SERIES}/controller/libair_zephyr_le_controller_${AIR_CTRL_TYPE}.a)
        endif()
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/swla)
        add_subdirectory(subsys/airoha/swla)
    else()
        if(DEFINED CONFIG_AIR_SWLA_ENABLE)
            add_subdirectory(${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/swla)
            zephyr_library_import(lib_swla.a ${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/swla/lib_swla.a)
        endif()
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/system_online_dump)
        add_subdirectory(subsys/airoha/system_online_dump)
    else()
        if(DEFINED CONFIG_AIR_ONLINE_DUMP_ENABLE)
            add_subdirectory(${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/system_online_dump)
            zephyr_library_import(lib_system_online_dump.a ${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/system_online_dump/lib_system_online_dump.a)
        endif()
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/offline_dump)
        add_subdirectory(subsys/airoha/offline_dump)
    else()
        if(DEFINED CONFIG_AIR_OFFLINE_DUMP_ENABLE)
            add_subdirectory(${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/offline_dump)
            zephyr_library_import(lib_offline_dump.a ${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/offline_dump/lib_offline_dump.a)
        endif()
    endif()
    add_subdirectory(subsys/airoha/partition)
    add_subdirectory(subsys/airoha/bt_air)
    add_subdirectory(subsys/airoha/race)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/argb)
        add_subdirectory(subsys/airoha/argb)
    endif()
    add_subdirectory(subsys/airoha/version)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/third_party/lzma_decoder)
        add_subdirectory(subsys/third_party/lzma_decoder)
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/ieee802154)
        add_subdirectory(subsys/airoha/ieee802154)
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/logging)
        add_subdirectory(subsys/airoha/logging)
    else()
        if(DEFINED CONFIG_AIR_LOGGING_ENABLE)
            add_subdirectory(${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/logging)
            zephyr_library_import(lib_logging.a ${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/logging/lib_logging.a)
        endif()
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/exception_handler)
        add_subdirectory(subsys/airoha/exception_handler)
    else()
        if(DEFINED CONFIG_AIR_EXCEPTION_HANDLER_ENABLE)
            add_subdirectory(${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/exception_handler)
            zephyr_library_import(lib_exception_handler.a ${AIR_PREBUILT_LIB_ROOT}/system/${SOC_SERIES}/exception_handler/lib_exception_handler.a)
        endif()
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/usb)
        add_subdirectory(subsys/airoha/usb)
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/led)
        add_subdirectory(subsys/airoha/led)
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/rgb)
        add_subdirectory(subsys/airoha/rgb)
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/bt_fast_pair_protected)
        add_subdirectory(subsys/airoha/bt_fast_pair_protected)
    else()
        if(DEFINED CONFIG_AIR_SPOT_ENABLE)
            zephyr_link_libraries(${AIR_PREBUILT_LIB_ROOT}/bt_fast_pair_protected/${SOC_SERIES}/libbt_fast_pair_protected.a)
        endif()
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/find_my_protected)
        add_subdirectory(subsys/airoha/find_my_protected)
    else()
        if(DEFINED CONFIG_AIR_APPLE_FIND_MY_ENABLE)
            zephyr_link_libraries(${AIR_PREBUILT_LIB_ROOT}/find_my/${SOC_SERIES}/libfind_my_protected.a)
        endif()
    endif()
    add_subdirectory(subsys/airoha/fota)
    add_subdirectory_ifndef(CONFIG_SOC_SERIES_AB161X subsys/airoha/ram_blocks_control)
    add_subdirectory_ifndef(CONFIG_SOC_SERIES_AB161X subsys/airoha/pd_domain_control)

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/gesture)
        add_subdirectory(subsys/airoha/gesture)
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/hid_plc_protected)
        add_subdirectory(subsys/airoha/hid_plc_protected)
    else()
        if(DEFINED CONFIG_AIR_HID_PLC_CALCULATE)
            add_subdirectory(${AIR_PREBUILT_LIB_ROOT}/middleware/airoha/hid_plc)
            zephyr_library_import(libhid_plc.a ${AIR_PREBUILT_LIB_ROOT}/middleware/airoha/hid_plc/libhid_plc.a)
        endif()
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/hid)
        add_subdirectory(subsys/airoha/hid)
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/io_expander)
        add_subdirectory(subsys/airoha/io_expander)
    endif()
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/app_framework)
        add_subdirectory(subsys/airoha/app_framework)
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/mux)
        add_subdirectory(subsys/airoha/mux)
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/soundmaker)
    add_subdirectory(subsys/airoha/soundmaker)
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/hw_keyscan)
    add_subdirectory(subsys/airoha/hw_keyscan)
    endif()
    
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/usbda)
        add_subdirectory(subsys/airoha/usbda)
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/bootreason_check)
        add_subdirectory(subsys/airoha/bootreason_check)
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/battery_management)
        add_subdirectory(subsys/airoha/battery_management)
    endif()

    if(DEFINED CONFIG_AIR_GM10P_ENABLE)
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/battery_management_protected)
            add_subdirectory(subsys/airoha/battery_management_protected)
        else()
            zephyr_library_import(lib_gm10p.a ${AIR_PREBUILT_LIB_ROOT}/middleware/airoha/battery_management/lib_gm10p.a)
        endif()
    endif()

    #Openthread third_party libraries
    if(DEFINED CONFIG_NET_L2_OPENTHREAD)
        add_subdirectory(subsys/airoha/openthread)
        if(DEFINED CONFIG_OPENTHREAD_LIBRARY)
            if (DEFINED CONFIG_AIR_OPENTHREAD_LIBRARY_MASTER)
                zephyr_library_import(libopenthread-cli-ftd.a ${AIR_PREBUILT_LIB_ROOT}/openthread/lib/v1.3.1/master/libopenthread-cli-ftd.a)
                zephyr_library_import(libopenthread-ftd.a ${AIR_PREBUILT_LIB_ROOT}/openthread/lib/v1.3.1/master/libopenthread-ftd.a)
                zephyr_library_import(libtcplp-ftd.a ${AIR_PREBUILT_LIB_ROOT}/openthread/lib/v1.3.1/master/libtcplp-ftd.a)
            elseif(DEFINED CONFIG_AIR_OPENTHREAD_LIBRARY_FTD)
                zephyr_library_import(libopenthread-cli-ftd.a ${AIR_PREBUILT_LIB_ROOT}/openthread/lib/v1.3.1/ftd/libopenthread-cli-ftd.a)
                zephyr_library_import(libopenthread-ftd.a ${AIR_PREBUILT_LIB_ROOT}/openthread/lib/v1.3.1/ftd/libopenthread-ftd.a)
            elseif(DEFINED CONFIG_AIR_OPENTHREAD_LIBRARY_MTD)
                zephyr_library_import(libopenthread-cli-mtd.a ${AIR_PREBUILT_LIB_ROOT}/openthread/lib/v1.3.1/mtd/libopenthread-cli-mtd.a)
                zephyr_library_import(libopenthread-mtd.a ${AIR_PREBUILT_LIB_ROOT}/openthread/lib/v1.3.1/mtd/libopenthread-mtd.a)
            endif()
        endif()
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tools/da_security)
        add_subdirectory(tools/da_security)
    endif()

    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../common upper_level)

    if (CONFIG_ZIGBEE)
        add_subdirectory(subsys/airoha/zigbee/zboss_porting)
        if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/zigbee/zboss_porting/platform)
            add_subdirectory(subsys/airoha/zigbee/zboss_porting/platform)
        endif()
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/subsys/airoha/race_protected)
        add_subdirectory(subsys/airoha/race_protected)
    endif()

    # add more CMakeLists.txt by using add_subdirectory
    # include more *.cmake by using include
endif()
