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

zephyr_library_compile_options(-Werror)

# Use macro to avoid not modifying NVKEY_FILE_LIST global variables
# due to function scope limitations.
macro(airoha_nvkey_append_xml input_file)
    if(EXISTS ${input_file})
        list(APPEND NVKEY_FILE_LIST ${input_file})
        # update NVKEY_FILE_LIST manually
        set(NVKEY_FILE_LIST ${NVKEY_FILE_LIST} CACHE STRING "nvkey file list" FORCE)
    else()
        message(WARNING "[Airoha][nvkey] ${input_file} not exist.")
    endif()
endmacro()


macro (airoha_show_archieve_size input_archieve)
    # When executing this command, cmake will automatically switch to the library's
    # generation directory, so there is no need to obtain its generation directory.
    add_custom_target(airoha_show_archieve_size${input_archieve} ALL
        COMMAND ${CROSS_COMPILE}size -t lib${input_archieve}.a
        COMMENT "[Airoha] show file: ${input_archieve} footprint information by toolchain"
        DEPENDS ${input_archieve}
    )
endmacro()


macro(airoha_copy_file_with_lock named_prebuild_lib output_dir prebuild_dir)
    if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
        add_custom_target(
            AIR_PREBUILT_LIB_INSTALL_SPECIAL_PATTERN_${ZEPHYR_CURRENT_LIBRARY}
            ALL
            DEPENDS ${ZEPHYR_CURRENT_LIBRARY}
            COMMAND ${CMAKE_COMMAND} -E copy ${output_dir}/${named_prebuild_lib} ${prebuild_dir}/${named_prebuild_lib}
        )
    elseif((${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux") OR (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin") OR (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Generic") )
        add_custom_target(
            AIR_PREBUILT_LIB_INSTALL_SPECIAL_PATTERN_${ZEPHYR_CURRENT_LIBRARY}
            ALL
            DEPENDS ${ZEPHYR_CURRENT_LIBRARY}
            COMMAND ${PYTHON_EXECUTABLE} ${AIR_ROOT_DIR}/scripts/build/copy_with_lock.py ${named_prebuild_lib} ${output_dir} ${prebuild_dir} ${named_prebuild_lib}
        )
    else()
        message(FATAL_ERROR "Unkown Operating System ${CMAKE_HOST_SYSTEM_NAME}")
    endif()
endmacro()


macro(airoha_copy_file_with_lock_and_rename named_prebuild_lib output_dir prebuild_dir renamed_prebuild_lib)
    if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
        add_custom_target(
            AIR_PREBUILT_LIB_INSTALL_SPECIAL_PATTERN_${ZEPHYR_CURRENT_LIBRARY}
            ALL
            DEPENDS ${ZEPHYR_CURRENT_LIBRARY}
            COMMAND ${CMAKE_COMMAND} -E copy ${output_dir}/${named_prebuild_lib} ${prebuild_dir}/${renamed_prebuild_lib}
        )
    elseif((${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux") OR (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin") OR (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Generic") )
        add_custom_target(
            AIR_PREBUILT_LIB_INSTALL_SPECIAL_PATTERN_${ZEPHYR_CURRENT_LIBRARY}
            ALL
            DEPENDS ${ZEPHYR_CURRENT_LIBRARY}
            COMMAND ${PYTHON_EXECUTABLE} ${AIR_ROOT_DIR}/scripts/build/copy_with_lock.py ${named_prebuild_lib} ${output_dir} ${prebuild_dir} ${renamed_prebuild_lib}
        )
    else()
        message(FATAL_ERROR "Unkown Operating System ${CMAKE_HOST_SYSTEM_NAME}")
    endif()
endmacro()