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

if(DEFINED CONFIG_AIR_FOTA_ENABLE)

zephyr_compile_definitions(AIR_FOTA_ENABLE)

zephyr_library_named(fota)
include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)
zephyr_include_directories(inc)

aux_source_directory(src fota_middleware)
zephyr_library_sources(${fota_middleware})

if(DEFINED CONFIG_AIR_DUAL_BANK_FOTA_ENABLE)

zephyr_compile_definitions(AIR_DUAL_BANK_FOTA_ENABLE)

endif() # DEFINED AIR_DUAL_BANK_FOTA_ENABLE

if(DEFINED CONFIG_AIR_FOTA_ECDSA_ENABLE)

zephyr_compile_definitions(AIR_FOTA_ECDSA_ENABLE)

message(STATUS "Adding mbedtls include directories...")
zephyr_library_include_directories(../../../../../modules/crypto/mbedtls/include)
zephyr_library_include_directories(../../../../../modules/crypto/mbedtls/library)
zephyr_library_include_directories(../../../../../modules/crypto/mbedtls/include/mbedtls)

message(STATUS "Adding mbedtls config file include directories...")
zephyr_library_include_directories(../../../mcu/applications/light_bulb/inc/mbedtls_cfg_file)

message(STATUS "Setting MBEDTLS_USER_CONFIG_FILE for fota target...")
target_compile_definitions(fota PRIVATE MBEDTLS_USER_CONFIG_FILE="config-tls-generic.h")
message(STATUS "Set MBEDTLS_USER_CONFIG_FILE to: config-tls-generic.h")

endif() # DEFINED AIR_FOTA_ECDSA_ENABLE

endif() # DEFINED CONFIG_AIR_FOTA_ENABLE