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

# generate pre-defined NVS/Settings data
set(NVS_COMBINE ${AIR_ROOT_DIR}/scripts/nvs/nvs_combine.py)

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(NVS_POSTBUILD ${AIR_ROOT_DIR}/tools/nvs_bin_generator/windows/nvs_post_build.exe)
elseif((${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux") OR (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Generic") )
    set(NVS_POSTBUILD ${AIR_ROOT_DIR}/tools/nvs_bin_generator/linux/nvs_post_build)
elseif((${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin"))
    set(NVS_POSTBUILD ${AIR_ROOT_DIR}/tools/nvs_bin_generator/macos/nvs_post_build)
else()
    message(FATAL_ERROR "Unkown Operating System ${CMAKE_HOST_SYSTEM_NAME}")
endif()

set(NVS_OUTPATH ${APPLICATION_BINARY_DIR}/download)
set(NVKEY_COMBINED_XML ${NVS_OUTPATH}/nvkey.xml)

if(CONFIG_GEN_DEFAULT_NVS_BIN)
    # Identify whether the output directory exists, and ensure that the nvs_post_build command succeeds.
    if(NOT EXISTS "${NVS_OUTPATH}")
        message(NOTICE "[Airoha][NVKey] Create NVS binary directory ${NVS_OUTPATH}")
        file(MAKE_DIRECTORY ${NVS_OUTPATH})
    endif()

    set(NVKEY_XML_NUM 1)
    foreach(NVKEY_XML_PATH IN LISTS NVKEY_FILE_LIST)
        string(REPLACE "${AIR_ROOT_DIR}" "airoha/mcu" NVKEY_XML_PATH "${NVKEY_XML_PATH}")
        message(STATUS "[Airoha][NVKey] NVKEY_FILE ${NVKEY_XML_NUM}: ${NVKEY_XML_PATH}")
        math(EXPR NVKEY_XML_NUM "${NVKEY_XML_NUM} + 1")
    endforeach()

    add_custom_target(nvs_pre_process ALL
        COMMAND
            ${PYTHON_EXECUTABLE} ${NVS_COMBINE} -f ${NVKEY_FILE_LIST} -o ${NVKEY_COMBINED_XML} -s ${CONFIG_GEN_DEFAULT_NVS_BIN_REPEAT_PROCESS_STRATEGY_STR}
        COMMENT
            "[Airoha][NVKey] Merge the input xml into one full nvkey.xml, and if there are dumplicate items, prompt or overwrite them according to project's policy."
    )

    add_custom_target(nvs_post_build ALL
        COMMAND
            ${NVS_POSTBUILD} -f nvs2bin -size ${CONFIG_STORAGE_PARTITION_SIZE} -o ${NVS_OUTPATH}/ -s ${NVKEY_COMBINED_XML} -mode 2 && mv ${NVS_OUTPATH}/nvs.bin ${NVS_OUTPATH}/storage.bin
        COMMENT
            "[Airoha][NVKey] Executing nvs_post_build target to generate storage binary data for downloading default NVS data"
    )
    # 1. generate combined nvkey.xml
    # 2. generate nvs.bin accoring to the combined nvkey.xml
    add_dependencies(nvs_post_build nvs_pre_process)

    if(CONFIG_GEN_DEFAULT_NVS_BIN_RELEASE)
        set(NVKEY_COMBINED_XML_RELEASE ${NVS_OUTPATH}/nvkey_release.xml)

        # update NVKEY_FILE_LIST_RELEASE manually
        set(NVKEY_FILE_LIST_RELEASE ${NVKEY_FILE_LIST} CACHE STRING "nvkey file list with release flag" FORCE)
        list(APPEND NVKEY_FILE_LIST_RELEASE ${AIR_ROOT_DIR}/soc/airoha/common/exception_handler/nvkey_release.xml)

        set(NVKEY_XML_NUM 1)
        foreach(NVKEY_XML_PATH IN LISTS NVKEY_FILE_LIST_RELEASE)
            string(REPLACE "${AIR_ROOT_DIR}" "airoha/mcu" NVKEY_XML_PATH "${NVKEY_XML_PATH}")
            message(STATUS "[Airoha][NVKey][MP] NVKEY_FILE ${NVKEY_XML_NUM}: ${NVKEY_XML_PATH}")
            math(EXPR NVKEY_XML_NUM "${NVKEY_XML_NUM} + 1")
        endforeach()

        add_custom_target(nvs_release_pre_process ALL
            COMMAND
                ${PYTHON_EXECUTABLE} ${NVS_COMBINE} -f ${NVKEY_FILE_LIST_RELEASE} -o ${NVKEY_COMBINED_XML_RELEASE} -s "USE_LAST"
            COMMENT
                "[Airoha][NVKey] Merge the input xml into one full nvkey_release.xml, and if there are dumplicate items, prompt or overwrite them according to project's policy."
        )

        add_custom_target(nvs_release_post_build ALL
            COMMAND
                ${NVS_POSTBUILD} -f nvs2bin -size ${CONFIG_STORAGE_PARTITION_SIZE} -o ${NVS_OUTPATH}/ -s ${NVKEY_COMBINED_XML_RELEASE} -mode 2 && mv ${NVS_OUTPATH}/nvs.bin ${NVS_OUTPATH}/storage_release.bin
            COMMENT
                "[Airoha][NVKey] Executing nvs_release_post_build target to generate storage_release.bin for downloading default NVS data with MP flag"
        )
        add_dependencies(nvs_release_post_build nvs_release_pre_process)

        add_dependencies(nvs_release_pre_process nvs_post_build)
    endif() # CONFIG_GEN_DEFAULT_NVS_BIN_RELEASE

    if(EXISTS ${AIR_ROOT_DIR}/scripts/scripts_protected/nvkey_id_list)
        set(NVKEY_ID_LIST_GENERATOR ${AIR_ROOT_DIR}/scripts/scripts_protected/nvkey_id_list/gen_nvkey_id.py)
        set(NVKEY_ID_LIST_FILE ${AIR_ROOT_DIR}/prebuilt/middleware/airoha/nvkey/${SOC_SERIES}/inc/nvkey_id_def.h)

        add_custom_target(gen_nvkey_id_list_def
            COMMAND
                ${PYTHON_EXECUTABLE} ${NVKEY_ID_LIST_GENERATOR} -o ${NVKEY_ID_LIST_FILE}
            COMMENT
                "[Airoha][NVKey] manually generate ${NVKEY_ID_LIST_FILE} if you have added a new nvkey"
        )
    endif()

endif() # CONFIG_GEN_DEFAULT_NVS_BIN