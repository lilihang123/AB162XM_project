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

cmake_minimum_required(VERSION 3.20.0)

# Refer to the zephyr/cmake/modules/configuration_files.cmake file
# to set environment variables to allow dts overlay.
# set(APPLICATION_CONFIG_DIR "config/\${BOARD}")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hid_dongle)

if(DEFINED CONFIG_AIR_PURE_GAMING_FAST_PAIR_ENABLE)
zephyr_compile_definitions(AIR_PURE_GAMING_FAST_PAIR_ENABLE)
endif()

include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)
include(${AIR_ROOT_DIR}/cmake/common/download_cfg.cmake)

zephyr_compile_definitions_ifdef(CONFIG_AIR_DONGLE_OF_KEYBOARD_M607 AIR_DONGLE_OF_KEYBOARD_M607)

zephyr_include_directories(./inc)
zephyr_include_directories(./inc/app)
zephyr_include_directories(./inc/app/app_events)
zephyr_include_directories(./inc/app/app_bt_conn)
zephyr_include_directories(./inc/app/app_race)
zephyr_include_directories(./inc/app/app_state)
zephyr_include_directories(./inc/app/app_usb)
zephyr_include_directories(./inc/app/app_scenario)
zephyr_include_directories(./inc/app/app_custom_protocol)
zephyr_include_directories(./inc/app/app_fast_pair)
zephyr_include_directories(./inc/app/app_led)
zephyr_include_directories(./app_framework/inc)

aux_source_directory(./src app_src)
aux_source_directory(./src/app app_src)
aux_source_directory(./src/app/app_events app_src)
aux_source_directory(./src/app/app_bt_conn app_src)
aux_source_directory(./src/app/app_race app_src)
aux_source_directory(./src/app/app_state app_src)
aux_source_directory(./src/app/app_usb app_src)
aux_source_directory(./src/app/app_scenario app_src)
aux_source_directory(./src/app/app_custom_protocol app_src)
aux_source_directory(./src/app/app_fast_pair app_src)
aux_source_directory(./src/app/app_led app_src)
aux_source_directory(./app_framework/src app_src)
aux_source_directory(./middle app_src)

# APP Dongle new folder for LE HOGP Office Dongle
if(DEFINED CONFIG_AIR_HOGP_DONGLE_ENABLE)
zephyr_compile_definitions(AIR_HOGP_DONGLE_ENABLE)

zephyr_include_directories(./inc/app/app_dongle)
zephyr_include_directories(./inc/app/app_dongle/app_bt_service)
zephyr_include_directories(./inc/app/app_dongle/app_dongle_cm)
zephyr_include_directories(./inc/app/app_dongle/app_event)
zephyr_include_directories(./inc/app/app_dongle/app_hogp_client)
zephyr_include_directories(./inc/app/app_dongle/app_usb_mgr)
aux_source_directory(./src/app/app_dongle app_src)
aux_source_directory(./src/app/app_dongle/app_bt_service app_src)
aux_source_directory(./src/app/app_dongle/app_dongle_cm app_src)
aux_source_directory(./src/app/app_dongle/app_event app_src)
aux_source_directory(./src/app/app_dongle/app_hogp_client app_src)
aux_source_directory(./src/app/app_dongle/app_usb_mgr app_src)
endif()

target_sources(app PRIVATE ${app_src})

# specify special nvkey source file and then generate non-volatile storage binary file
airoha_nvkey_append_xml(${APPLICATION_SOURCE_DIR}/${CONFIG_AIR_NVKEY_APP_LEVEL_FILE})
include(${AIR_ROOT_DIR}/cmake/common/gen_nvs.cmake)