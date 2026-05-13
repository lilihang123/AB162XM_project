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


zephyr_library()

set(PKA_TARGET_BOARD ab1620)
set(PKA_TARGET_LIB_POST_STR "")
if(CONFIG_BT_PKA_LIB_COSIM)
    set(PKA_TARGET_LIB zephyrcosim)
elseif(CONFIG_BT_PKA_LIB_MULTI_PROTOCOL)
    if(CONFIG_NET_L2_CUSTOM_IEEE802154)
        set(PKA_TARGET_LIB zephyrmultipro_dualpan)
    else()
        set(PKA_TARGET_LIB zephyrmultipro)
    endif()
elseif(CONFIG_BT_PKA_LIB_LE_SUPPORT_RANGING)
    set(PKA_TARGET_LIB zephyrleranging)
else()
    set(PKA_TARGET_LIB zephyrle)
    if(CONFIG_AIR_FPGA_ENV_ENABLE)
        set(PKA_TARGET_LIB_POST_STR "${PKA_TARGET_LIB_POST_STR}_fpga")
        if(CONFIG_FLASH_BOOTING)
            set(PKA_TARGET_LIB_POST_STR "${PKA_TARGET_LIB_POST_STR}_fb")
        else()
            set(PKA_TARGET_LIB_POST_STR "${PKA_TARGET_LIB_POST_STR}_rb")
        endif()
    else()
        set(PKA_TARGET_LIB_POST_STR "${PKA_TARGET_LIB_POST_STR}_asic")
    endif()
endif()

zephyr_include_directories(inc)
zephyr_include_directories(hci_log)

if(CONFIG_AIR_AVM)
zephyr_include_directories(avm/inc)
zephyr_include_directories(relay_mode/${SOC_SERIES}/inc)
zephyr_library_sources(
    avm/src/bt_driver_misc.c
    avm/src/bt_driver.c
    avm/src/bt_common.c
    avm/src/bt_linknode.c
    avm/src/bt_memory.c
    relay_mode/${SOC_SERIES}/src/bt_driver_relay_mode.c
    relay_mode/${SOC_SERIES}/src/relay_client.c
)
endif()

zephyr_include_directories(${AIR_SUBSYS_PKA_ROOT}/inc)
zephyr_include_directories(${AIR_PREBUILT_LIB_ROOT}/middleware/airoha/nvkey/ab162x/inc/)
include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)
zephyr_library_sources(
    src/avm_external.c
    src/hci/hci_driver_airoha.c
    hci_log/bt_hci_log.c
    hci_log/hci_log.c
)


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../pka_protected")
    message("build pka lib...")
    add_subdirectory(pka)
else()
    message("${CMAKE_CURRENT_SOURCE_DIR}/pka_protected is empty. Prebuilt libpka_${PKA_TARGET_LIB}${PKA_TARGET_LIB_POST_STR}.a is used")
    zephyr_library_link_libraries(${AIR_PREBUILT_LIB_ROOT}/middleware/airoha/bluetooth/${SOC_SERIES}/controller/libpka_${PKA_TARGET_LIB}${PKA_TARGET_LIB_POST_STR}.a)
endif()

if(CONFIG_AIR_BT_SMP_SC_ENABLE)
zephyr_compile_definitions(AIR_BT_SMP_SC_ENABLE)
endif()
