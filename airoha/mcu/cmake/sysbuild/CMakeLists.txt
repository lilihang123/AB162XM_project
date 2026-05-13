#!/usr/bin/python3
# -*- coding: UTF-8 -*-
#
# * Copyright Statement:
# *
# * (C) 2024  Airoha Technology Corp. All rights reserved.
# *
# * This software/firmware and related documentation ("Airoha Software") are
# * protected under relevant copyright laws. The information contained herein
# * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
# * Without the prior written permission of Airoha and/or its licensors,
# * any reproduction, modification, use or disclosure of Airoha Software,
# * and information contained herein, in whole or in part, shall be strictly prohibited.
# * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
# * if you have agreed to and been bound by the applicable license agreement with
# * Airoha ("License Agreement") and been granted explicit permission to do so within
# * the License Agreement ("Permitted User").  If you are not a Permitted User,
# * please cease any access or use of Airoha Software immediately.
# * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
# * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
# * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
# * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
# * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
# * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
# * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
# *
# * Airoha restricted information */


# included by airoha/boards/arm/{BOARD}/sysbuild.cmake

string(TIMESTAMP SYSBUILD_START_TIME_IN_SEC "%s")
message(NOTICE "[Airoha][Build] SYSBUILD_START_TIME_IN_SEC: ${SYSBUILD_START_TIME_IN_SEC}")

# Need to define the AIR_ROOT_DIR variable in the system build environment
set(AIR_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../.. CACHE PATH "Airoha root directory")

set(COLLECT_FIRMWARES_SCRIPT            ${AIR_ROOT_DIR}/scripts/build/collect_firmwares.py)
set(SYSBUILD_CHECK_SCRIPT               ${AIR_ROOT_DIR}/scripts/build/sysbuild_check.py)
set(FLASH_PARTITION_CHECK_SCRIPT        ${AIR_ROOT_DIR}/scripts/build/flash_partition_check.py)

list(APPEND CALC_BUILD_TIME_DEPENDS "")

# In zephyr v3.7.0, the include order of this file is:
#   airoha/mcu/cmake/sysbuild/CMakeLists.txt
#   airoha/mcu/boards/airoha/ab1620_fpga/sysbuild.cmake
#   zephyr/share/sysbuild/images/boards/CMakeLists.txt
#   zephyr/share/sysbuild/cmake/modules/sysbuild_images.cmake
# In this dependency order, IMAGES has no value, and we use DEFAULT_IMAGE as a dependency file.
# Otherwise, the script file will have unexpected errors such as not finding the file due to
# in correct dependency order.

if(SB_CONFIG_AIR_COLLECT_FIRMWARE)

    # Compatibility code written for zephyr v3.7.0 upgrade.
    if(EXISTS ${AIR_ROOT_DIR}/soc/airoha)
        get_property(SYSBUILD_IMAGES GLOBAL PROPERTY sysbuild_images)
    endif()

    message(NOTICE "[Airoha] IMAGES: ${IMAGES}")
    message(NOTICE "[Airoha] DEFAULT_IMAGE: ${DEFAULT_IMAGE}")
    message(NOTICE "[Airoha] SYSBUILD_IMAGES: ${SYSBUILD_IMAGES}")

    add_custom_target(collect_firmwares ALL
        COMMAND ${PYTHON_EXECUTABLE} ${COLLECT_FIRMWARES_SCRIPT}
                -v ${ZEPHYR_BASE}/VERSION
                -f ${CMAKE_BINARY_DIR}/domains.yaml
        COMMENT "[Airoha] collect firmware and change firmware name in flash_download.cfg"
        DEPENDS
            ${IMAGES}
            ${SYSBUILD_IMAGES}
            ${ZEPHYR_BASE}/VERSION
            ${CMAKE_BINARY_DIR}/domains.yaml
            ${DEFAULT_IMAGE}
    )

    if(SB_CONFIG_AIR_SYSBUILD_CHECK_ENABLE)
        add_custom_target(sysbuild_check ALL
            COMMAND ${PYTHON_EXECUTABLE} ${SYSBUILD_CHECK_SCRIPT}
                    -f ${CMAKE_BINARY_DIR}/debug
            COMMENT "[Airoha] check sysbuild result, especially the address defined by the cross core variable"
            DEPENDS
                collect_firmwares
        )

        list(APPEND CALC_BUILD_TIME_DEPENDS sysbuild_check)
    endif()

    if(SB_CONFIG_AIR_FLASH_PARTITION_CHECK_ENABLE)
        add_custom_target(flash_partition_check ALL
            COMMAND ${PYTHON_EXECUTABLE} ${FLASH_PARTITION_CHECK_SCRIPT}
                    -f ${CMAKE_BINARY_DIR}/debug
            COMMENT "[Airoha] check the differences in the flash partition across different projects in sysbuild"
            DEPENDS
                collect_firmwares
        )

        list(APPEND CALC_BUILD_TIME_DEPENDS flash_partition_check)
    endif()

endif()


if(SB_CONFIG_AIR_GEN_FOOTPRINT_DETAIL_ENABLE)
    set(FOOTPRINT_GENERATOR_DIR ${AIR_ROOT_DIR}/scripts/scripts_protected/memory_utility/footprint_v2)
    set(FOOTPRINT_GENERATOR_PATH ${FOOTPRINT_GENERATOR_DIR}/footprint.py)
    set(FOOTPRINT_GENERATOR_NAME footprint.py)

    if(EXISTS ${FOOTPRINT_GENERATOR_PATH})
        add_custom_target(gen_footprint_detail ALL
            COMMAND
                ${CMAKE_COMMAND} -E chdir ${FOOTPRINT_GENERATOR_DIR}
                ${PYTHON_EXECUTABLE} ${FOOTPRINT_GENERATOR_NAME}
                -o ${CMAKE_BINARY_DIR}
                # -r ${AIR_ROOT_DIR}
            COMMENT
                "[Airoha][Footprint] Generating fp_symbol.csv & fp_object.csv for footprint analysising..."
            DEPENDS
                collect_firmwares
        )

        list(APPEND CALC_BUILD_TIME_DEPENDS gen_footprint_detail)
    else()
        message(NOTICE "[Airoha][Footprint] script(${FOOTPRINT_GENERATOR_PATH}) not exist")
    endif()

endif() # AIR_GEN_FOOTPRINT_ENABLE


if(SB_CONFIG_AIR_GEN_FOOTPRINT_STATISTICS_ENABLE)
    set(FOOTPRINT_STATISTICS_DIR ${AIR_ROOT_DIR}/scripts/build)
    set(FOOTPRINT_STATISTICS_NAME footprint_statistics.py)
    set(FOOTPRINT_STATISTICS_PATH ${FOOTPRINT_STATISTICS_DIR}/${FOOTPRINT_STATISTICS_NAME})

    if(EXISTS ${FOOTPRINT_STATISTICS_PATH})
        add_custom_target(gen_footprint_statistics ALL
            COMMAND
                ${CMAKE_COMMAND} -E chdir ${FOOTPRINT_STATISTICS_DIR}
                ${PYTHON_EXECUTABLE} ${FOOTPRINT_STATISTICS_NAME}
                -o ${CMAKE_BINARY_DIR}
            COMMENT
                "[Airoha][Footprint] Generating statistics data for footprint analysising..."
            DEPENDS
                collect_firmwares
        )

        list(APPEND CALC_BUILD_TIME_DEPENDS gen_footprint_statistics)
    else()
        message(NOTICE "[Airoha][Footprint] script(${FOOTPRINT_STATISTICS_PATH}) not exist")
    endif()
endif() # SB_CONFIG_AIR_GEN_FOOTPRINT_STATISTICS_ENABLE

if(SB_CONFIG_AIR_GEN_RELEASE_RELATED_ENABLE)
    set(GEN_DL_RELEASE_MISC_DIR ${AIR_ROOT_DIR}/scripts/build)
    set(GEN_DL_RELEASE_MISC_NAME gen_release_misc.py)
    set(GEN_DL_RELEASE_MISC_PATH ${GEN_DL_RELEASE_MISC_DIR}/${GEN_DL_RELEASE_MISC_NAME})

    if(EXISTS ${GEN_DL_RELEASE_MISC_PATH})
        add_custom_target(gen_release_misc ALL
            COMMAND
                ${CMAKE_COMMAND} -E chdir ${GEN_DL_RELEASE_MISC_DIR}
                ${PYTHON_EXECUTABLE} ${GEN_DL_RELEASE_MISC_NAME}
                -o ${CMAKE_BINARY_DIR}/download
            COMMENT
                "[Airoha][Release] Generating release related files..."
            DEPENDS
                collect_firmwares
        )

        list(APPEND CALC_BUILD_TIME_DEPENDS gen_release_misc)
    endif()
endif() # SB_CONFIG_AIR_GEN_RELEASE_RELATED_ENABLE


file(WRITE ${CMAKE_BINARY_DIR}/calc_build_time.cmake "
string(TIMESTAMP SYSBUILD_FINISH_TIME_IN_SEC \"%s\")
math(EXPR REAL_BUILD_TIME_IN_SEC \"\${SYSBUILD_FINISH_TIME_IN_SEC} - ${SYSBUILD_START_TIME_IN_SEC}\")
math(EXPR REAL_BUILD_TIME_SEC_PART \"\${REAL_BUILD_TIME_IN_SEC} % 60\")
math(EXPR REAL_BUILD_TIME_MIN_PART \"\${REAL_BUILD_TIME_IN_SEC} / 60\")
message(NOTICE \"[Airoha][Build] Real Build Time: \${REAL_BUILD_TIME_MIN_PART} min \${REAL_BUILD_TIME_SEC_PART} s\")
")

add_custom_target(
    print_sysbuild_end_time ALL
    COMMAND
        ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/calc_build_time.cmake
        # ${CMAKE_COMMAND} -E echo "[Airoha][Build] sysbuild end time in seconds is $<TIMESTAMP:%s>"
    COMMENT
        "[Airoha][Build] print sysbuild time"
    DEPENDS
        ${CALC_BUILD_TIME_DEPENDS}
)