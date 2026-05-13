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
# THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
# RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
# TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
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
#

# SPDX-License-Identifier: Apache-2.0

zephyr_library()
include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)
zephyr_include_directories(inc)

zephyr_compile_definitions_ifdef(CONFIG_ARM_SECURE_FIRMWARE AIR_CPU_IN_SECURITY_MODE)

zephyr_compile_definitions_ifdef(CONFIG_TCM_BOOTING AIR_TCM_BOOTING)
zephyr_compile_definitions_ifdef(CONFIG_FLASH_BOOTING AIR_FLASH_BOOTING)
zephyr_compile_definitions_ifdef(CONFIG_ARM_MPU HAL_MPU_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_FLASH HAL_FLASH_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_CACHE HAL_CACHE_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_TRNG_ENABLE HAL_TRNG_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_HW_SEMAPHORE HAL_HW_SEMAPHORE_MODULE_ENABLED)
if((DEFINED CONFIG_AIR_ESC) AND (NOT DEFINED CONFIG_AIR_ESC_WITH_NONE))
    zephyr_compile_definitions(HAL_ESC_MODULE_ENABLED)
endif()
zephyr_compile_definitions_ifdef(CONFIG_AIR_ESC_WITH_FLASH ESC_FLASH_ENABLE)
zephyr_compile_definitions_ifdef(CONFIG_AIR_ESC_WITH_RAM ESC_PSRAM_ENABLE)
zephyr_compile_definitions_ifdef(CONFIG_AIR_DMA HAL_SW_DMA_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_WDT HAL_WDT_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_WDT_2ND HAL_WDT_FEATURE_SECOND_CHANNEL)
zephyr_compile_definitions(HAL_DWT_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_CCNI HAL_CCNI_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_IRRX HAL_IRRX_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_IRTX HAL_IRTX_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_INTC HAL_NVIC_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_EINT HAL_EINT_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_I2C HAL_I2C_MASTER_MODULE_ENABLED)
#zephyr_compile_definitions_ifdef(CONFIG_AIR_I3C HAL_I3C_MASTER_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_I2CAO HAL_I2C_MASTER_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_RTC HAL_RTC_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_ARGB HAL_ARGB_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_PWM  HAL_PWM_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_PWMDMA HAL_PWM_DMA_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_MIDDLE_LED HAL_PWM_LED_SUPPORTED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_MIDDLE_RGB HAL_PWM_RGB_SUPPORTED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_UART HAL_UART_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_UART_SLEEP UART_SLEEP_TRIGGER_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_SPIM HAL_SPI_MASTER_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_SPIS HAL_SPI_SLAVE_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_USB HAL_USB_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_GPIO HAL_GPIO_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_GPIO HAL_EINT_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_LED HAL_LED_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_QDEC HAL_QDEC_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_RAMBOZ HAL_RAMBOZ_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_CLOCK_CONTROL HAL_CLOCK_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_DCXO HAL_DCXO_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_DVFS HAL_DVFS_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_PMU HAL_PMU_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_BAT HAL_BAT_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_SARADC HAL_ADC_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_SLEEP_MANAGER HAL_SLEEP_MANAGER_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_SOUNDMAKER SOUNDMAKR_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_HW_KEYSCAN HAL_HW_KEYSCAN_MODULE_ENABLED)
zephyr_compile_definitions_ifdef(CONFIG_AIR_MIDDLE_ARGB HAL_MIDDLE_ARGB_SUPPORTED)

zephyr_compile_definitions_ifdef(CONFIG_AIR_RGB_REAL_TIME_FIFO RGB_REAL_TIME_FIFO)
zephyr_compile_definitions_ifdef(CONFIG_AIR_RGB_REAL_TIME_ACK RGB_REAL_TIME_ACK)

zephyr_compile_definitions(HAL_AIOADC_MODULE_ENABLED)
zephyr_compile_definitions(HAL_COMPARATOR_MODULE_ENABLED)
zephyr_compile_definitions(HAL_UART_MODULE_ENABLED)
zephyr_compile_definitions(HAL_EINT_MODULE_ENABLED)
#zephyr_compile_definitions(CONFIG_UART_ASYNC_API)
zephyr_compile_definitions(HAL_GPIO_MODULE_ENABLED)
zephyr_compile_definitions(HAL_GPT_MODULE_ENABLED)
zephyr_compile_definitions(HAL_IRRX_MODULE_ENABLED)
zephyr_compile_definitions(HAL_I3C_MASTER_MODULE_ENABLED)
zephyr_compile_definitions(HAL_RAMBOZ_MODULE_ENABLED)
# zephyr_compile_definitions(HAL_QDEC_MODULE_ENABLED)
zephyr_compile_definitions(HAL_AES_MODULE_ENABLED)
zephyr_compile_definitions(HAL_SHA_MODULE_ENABLED)
zephyr_compile_definitions(HAL_AESOTF_MODULE_ENABLED)
zephyr_compile_definitions(HAL_DEEP_SLEEP_MODULE_ENABLED)

aux_source_directory(src SRC)
zephyr_library_sources(${SRC})


if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src_core)
    add_subdirectory(src_core)
else()
    zephyr_library_import(libhalsrc_core.a ${AIR_PREBUILT_LIB_ROOT}/hal/${SOC_SERIES}/libhalsrc_core.a)
endif()


zephyr_include_directories(${AIR_PREBUILT_LIB_ROOT}/hal/${SOC_SERIES}/inc)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src_protected)
    add_subdirectory(src_protected)
else()
    zephyr_library_import(libhal_src_protected.a ${AIR_PREBUILT_LIB_ROOT}/hal/${SOC_SERIES}/lib/libhal_src_protected.a)
endif()


