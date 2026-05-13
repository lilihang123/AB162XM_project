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

# -> zephyr/soc/CMakeLists.txt( add_subdirectory(${${series_setting_dir}} soc/${SOC_SERIES}) )
# -> zephyr/CMakeLists.txt( add_subdirectory(soc) )

message(NOTICE "[Airoha] soc/airoha/ab162x/CMakeLists.txt was included!")

if(NOT DEFINED AIR_ROOT_DIR)
    set(AIR_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../..)
endif()

zephyr_include_directories(.)

zephyr_library()

include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)


aux_source_directory(. SRC)

zephyr_library_sources(
    ${SRC}
    startup.S
)

zephyr_compile_definitions_ifdef(CONFIG_AIR_FPGA_ENV_ENABLE FPGA_ENV)

set(SOC_LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/linker.ld CACHE PATH "linker script SoC template")
message(NOTICE "[Airoha] variable SOC_LINKER_SCRIPT is ${SOC_LINKER_SCRIPT}")


# set(AIR_INIT_KCONFIG_GENERATOR ${AIR_ROOT_DIR}/scripts/build/gen_init_macro.py)
# set(AIR_INIT_CFG_FILE ${CMAKE_CURRENT_LIST_DIR}/init_cfg.yaml)
# add_custom_target(gen_init_level_macro ALL
#     COMMAND ${PYTHON_EXECUTABLE} ${AIR_INIT_KCONFIG_GENERATOR} -f ${AIR_INIT_CFG_FILE} -o ${PROJECT_BINARY_DIR}/include/generated/zephyr
#     COMMENT "[Airoha] Generating initialize level macro in C header file and initialize priority macro in Kconfig file by the specified configuration file"
#     DEPENDS ${AIR_INIT_CFG_FILE}
# )

zephyr_compile_definitions_ifdef(CONFIG_AIR_SOC_CROSS_CORE_MEMORY_ENABLE AIR_SOC_CROSS_CORE_MEMORY_ENABLE)


if(CONFIG_AIR_LOGGING_ENABLE)
    include(../../../cmake/common/logging.cmake)
endif()


add_subdirectory_ifdef(CONFIG_AIR_MEMORY_MONITOR_ENABLE memory_monitor)


if((DEFINED CONFIG_AIR_RISCV_PROJ_PATH) AND (NOT CONFIG_AIR_RISCV_PROJ_PATH STREQUAL ""))
    message(STATUS "")
    message(STATUS "[Airoha] AIR_ROOT_DIR at ${AIR_ROOT_DIR}")
    message(STATUS "[Airoha] CONFIG_AIR_RISCV_ROOT_PATH is ${CONFIG_AIR_RISCV_ROOT_PATH}")
    message(STATUS "[Airoha] CONFIG_AIR_RISCV_FEATURE is ${CONFIG_AIR_RISCV_FEATURE}")
    message(STATUS "[Airoha] CONFIG_AIR_RISCV_PROJ_PATH is ${CONFIG_AIR_RISCV_PROJ_PATH}")

    list(LENGTH CONFIG_AIR_RISCV_PROJ_PATH RISCV_PROJ_LEN)
    list(LENGTH CONFIG_AIR_RISCV_FEATURE RISCV_FEATURE_LEN)

    if (NOT RISCV_PROJ_LEN EQUAL RISCV_FEATURE_LEN)
        message(STATUS "[Airoha] RISCV_PROJ_LEN is ${RISCV_PROJ_LEN}")
        message(STATUS "[Airoha] RISCV_FEATURE_LEN is ${RISCV_FEATURE_LEN}")
        message(FATAL_ERROR "[Airoha] configuration relate to risc-v projects check error")
    endif()

    set(RISCV_BUILD_BYPASS 0)
    if(NOT EXISTS "${AIR_ROOT_DIR}/${CONFIG_AIR_RISCV_ROOT_PATH}")
        message(STATUS "[Airoha] No RISCV_ROOT")
        set(RISCV_BUILD_BYPASS 1)
    endif()


    set(RISCV_FIRMWARE_LIST "")
    set(RISCV_PROJ_IDX 0)

    if(NOT RISCV_BUILD_BYPASS)
        foreach(RISCV_PROJ_PATH RISCV_FEATURE IN ZIP_LISTS CONFIG_AIR_RISCV_PROJ_PATH CONFIG_AIR_RISCV_FEATURE)
            message(STATUS "[Airoha] RISCV_PROJ_PATH is ${RISCV_PROJ_PATH}")
            message(STATUS "[Airoha] RISCV_FEATURE is ${RISCV_FEATURE}")

            get_filename_component(RISCV_PROJ_ABBR ${RISCV_PROJ_PATH} NAME)
            get_filename_component(RISCV_FEATURE_ABBR ${RISCV_FEATURE} NAME_WE)
            message(STATUS "[Airoha] RISCV_PROJ_ABBR is ${RISCV_PROJ_ABBR}")
            message(STATUS "[Airoha] RISCV_FEATURE_ABBR is ${RISCV_FEATURE_ABBR}")

            set(RISCV_FIRMWARE_OUT_DIR ${APPLICATION_BINARY_DIR}/riscv/${RISCV_PROJ_ABBR}/${RISCV_FEATURE_ABBR})

            if(NOT EXISTS "${RISCV_FIRMWARE_OUT_DIR}")
                message(NOTICE "[Airoha] Create directory ${RISCV_FIRMWARE_OUT_DIR}")
                file(MAKE_DIRECTORY ${RISCV_FIRMWARE_OUT_DIR})
            endif()

            message(STATUS "[Airoha] riscv output: ${RISCV_FIRMWARE_OUT_DIR}/riscv.bin")
            message(STATUS "[Airoha] riscv output: ${RISCV_FIRMWARE_OUT_DIR}/riscv.c")

            add_custom_command(
                OUTPUT
                    ${RISCV_FIRMWARE_OUT_DIR}/${RISCV_PROJ_ABBR}.bin
                    ${RISCV_FIRMWARE_OUT_DIR}/${RISCV_PROJ_ABBR}.c
                COMMAND
                    cd ${AIR_ROOT_DIR}/${CONFIG_AIR_RISCV_ROOT_PATH}
                    &&
                    ${PYTHON_EXECUTABLE}
                        ${CMAKE_CURRENT_LIST_DIR}/prepare_cross_core_params.py
                        -m ${PROJECT_BINARY_DIR}/${ZEPHYR_LINK_STAGE_EXECUTABLE}.map
                        -c ${AUTOCONF_H}
                        -o ${RISCV_FIRMWARE_OUT_DIR}/cross_core_params.mk
                    &&
                    make -f ${RISCV_PROJ_PATH}/Makefile
                        RISCV_FIRMWARE_OUT_DIR=${RISCV_FIRMWARE_OUT_DIR}
                        CROSS_BUILD_PARAMS_FILE=cross_core_params.mk
                        FEATURE=${RISCV_FEATURE}
                    &&
                    cd ${RISCV_FIRMWARE_OUT_DIR}
                    &&
                    ${PYTHON_EXECUTABLE}
                        ${CMAKE_CURRENT_LIST_DIR}/riscv_c_code_format.py
                        ${RISCV_PROJ_ABBR}
                        ${RISCV_FEATURE_ABBR}
                        ${RISCV_PROJ_IDX}
                DEPENDS
                    ${AUTOCONF_H}
                    ${PROJECT_BINARY_DIR}/${ZEPHYR_LINK_STAGE_EXECUTABLE}.map
                COMMENT
                    "[Airoha] generating riscv firmware to ${RISCV_FIRMWARE_OUT_DIR}..."
            )

            # add generated file to GKSF so that zephyr will link twice
            set_property(GLOBAL APPEND PROPERTY GENERATED_KERNEL_SOURCE_FILES ${RISCV_FIRMWARE_OUT_DIR}/${RISCV_PROJ_ABBR}.c)

            list(APPEND RISCV_FIRMWARE_LIST ${RISCV_FIRMWARE_OUT_DIR}/${RISCV_PROJ_ABBR}.c ${RISCV_FIRMWARE_OUT_DIR}/${RISCV_PROJ_ABBR}.bin)

            math(EXPR RISCV_PROJ_IDX "${RISCV_PROJ_IDX} + 1")
        endforeach()

        # create a custom target that will build during project build proccssing
        add_custom_target(build_riscv_firmware
            DEPENDS
                ${RISCV_FIRMWARE_LIST}
        )
    endif()

endif()