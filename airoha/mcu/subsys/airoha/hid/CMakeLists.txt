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

if(DEFINED CONFIG_AIR_HID_SCENARIO_SERVICE)

zephyr_compile_definitions(AIR_HID_SCENARIO_SERVICE)

if(DEFINED CONFIG_AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)
zephyr_compile_definitions(AIR_PURE_GAMING_CUSTOM_PROTOCOL_ENABLE)

if(DEFINED CONFIG_AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
zephyr_compile_definitions(AIR_PURE_GAMING_CUSTOM_PROTOCOL_HID_MIXING_ENABLE)
endif()

endif()

if(DEFINED CONFIG_AIR_PURE_GAMING_DONGLE_ENABLE)

zephyr_compile_definitions(AIR_PURE_GAMING_DONGLE_ENABLE)

if(DEFINED CONFIG_AIR_PURE_GAMING_DONGLE_MS_ENABLE)
zephyr_compile_definitions(AIR_PURE_GAMING_DONGLE_MS_ENABLE)
endif()

if(DEFINED CONFIG_AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
zephyr_compile_definitions(AIR_PURE_GAMING_DONGLE_GAMEPAD_ENABLE)
endif()

if(DEFINED CONFIG_AIR_PURE_GAMING_DONGLE_KB_ENABLE)
zephyr_compile_definitions(AIR_PURE_GAMING_DONGLE_KB_ENABLE)
endif()

if(DEFINED CONFIG_AIR_HID_DUMMY_REPORT_RATE)
zephyr_compile_definitions(AIR_HID_DUMMY_REPORT_RATE)
endif()

if(DEFINED CONFIG_AIR_EXTERNAL_BUCK_GPIO_MODE)
zephyr_compile_definitions(AIR_EXTERNAL_BUCK_GPIO_MODE)
endif()

zephyr_library()
include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)
zephyr_include_directories(hid_dongle_scenario_service/inc)
zephyr_include_directories(hid_critical_path/gaming_dongle/inc)
zephyr_include_directories(hid_plc_common/inc)
zephyr_include_directories(la_debug/inc)
zephyr_include_directories(custom_protocol/inc)
zephyr_include_directories(hid_power_manager/inc)
zephyr_include_directories(hid_scenario_service/inc)
zephyr_include_directories(hid_vendor_cmd/inc)
if(DEFINED CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
zephyr_include_directories(auto_switch_service/inc)
endif()

aux_source_directory(hid_dongle_scenario_service/src SRC)
aux_source_directory(hid_critical_path/gaming_dongle/src SRC)
aux_source_directory(hid_plc_common/src SRC)
aux_source_directory(la_debug/src SRC)
aux_source_directory(custom_protocol/src SRC)
aux_source_directory(hid_power_manager/src SRC)
aux_source_directory(hid_power_manager/src SRC)
aux_source_directory(hid_vendor_cmd/src SRC)
if(DEFINED CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
aux_source_directory(auto_switch_service/src SRC)
endif()
if(DEFINED CONFIG_AIR_HID_AUTO_SWITCH_TX_POWER)
    airoha_nvkey_append_xml(${AIR_ROOT_DIR}/subsys/airoha/hid/auto_switch_service/nvkey.xml)
endif()
zephyr_library_sources(${SRC})

else()# DEFINED CONFIG_AIR_PURE_GAMING_DONGLE_ENABLE

if(DEFINED CONFIG_AIR_PRODUCT_TYPE_MOUSE)
zephyr_compile_definitions(AIR_PRODUCT_TYPE_MOUSE)
endif()

if(DEFINED CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
zephyr_compile_definitions(AIR_PRODUCT_TYPE_GAME_CONTROLLER)
endif()

if(DEFINED CONFIG_AIR_GAME_CONTROLLER_9B_DATA)
zephyr_compile_definitions(AIR_GAME_CONTROLLER_9B_DATA)
endif()

if(DEFINED CONFIG_AIR_GAME_CONTROLLER_12BIT_ADC)
zephyr_compile_definitions(AIR_GAME_CONTROLLER_12BIT_ADC)
endif()

zephyr_library()
include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)
zephyr_include_directories(hid_scenario_service/inc)
zephyr_include_directories(key_remap/inc)
zephyr_include_directories(user_profiles/inc)

if(DEFINED CONFIG_AIR_PRODUCT_TYPE_MOUSE)
zephyr_include_directories(sensor_manager/inc)
endif()
zephyr_include_directories(hid_race_cmd/inc)
zephyr_include_directories(la_debug/inc)
zephyr_include_directories(custom_protocol/inc)
zephyr_include_directories(labtest_service/inc)
if(DEFINED CONFIG_AIR_PRODUCT_TYPE_MOUSE)
zephyr_include_directories(math/inc)
endif()
zephyr_include_directories(hid_power_manager/inc)
zephyr_include_directories(hid_vendor_cmd/inc)

if(DEFINED CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
zephyr_include_directories(hid_critical_path/game_controller/inc)
endif()

aux_source_directory(hid_scenario_service/src SRC)
aux_source_directory(key_remap/src SRC)
aux_source_directory(user_profiles/src SRC)
if(DEFINED CONFIG_AIR_PRODUCT_TYPE_MOUSE)
aux_source_directory(sensor_manager/src SRC)
endif()
aux_source_directory(hid_race_cmd/src SRC)
aux_source_directory(la_debug/src SRC)
aux_source_directory(custom_protocol/src SRC)
aux_source_directory(labtest_service/src SRC)
if(DEFINED CONFIG_AIR_PRODUCT_TYPE_MOUSE)
aux_source_directory(math/src SRC)
endif()

aux_source_directory(hid_power_manager/src SRC)
aux_source_directory(hid_vendor_cmd/src SRC)

if(DEFINED CONFIG_AIR_PRODUCT_TYPE_GAME_CONTROLLER)
aux_source_directory(hid_critical_path/game_controller/src SRC)
endif()
zephyr_library_sources(${SRC})

endif() # DEFINED CONFIG_AIR_PURE_GAMING_DONGLE_ENABLE
endif() # DEFINED CONFIG_AIR_HID_SCENARIO_SERVICE