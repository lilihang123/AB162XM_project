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



# Refer to the logic of CONFIG_BUILD_OUTPUT_BIN in zephyr/CMakeLists.txt and write these two special custom target.
# gen_zephyr_bin_wo_logging_section: Responsible for generating the final burned binary file that does not contain .log_strings_sections
# gen_log_str_bin: Responsible for generating the mcu_log_str.bin file used by the host Airoha logging tool.

# For MCUBOOT, the situation is more complicated.
# Because MCUBOOT needs to sign the application firmware, it can be seen in zephyr/cmake/mcuboot.cmake that
# its signature processing of the hex/bin file is followed by Zephyr's original HEX/BIN operation and
# stored in extra_post_build_commands variables, so we need to find a gap to allow Airoha's logging section
# to insert process, and the CMakelist.txt in simply SOC directory is better than mcuboot.cmake.

set_property(GLOBAL APPEND PROPERTY extra_post_build_commands
    COMMAND $<TARGET_PROPERTY:bintools,elfconvert_command>
    $<TARGET_PROPERTY:bintools,elfconvert_flag>
    $<TARGET_PROPERTY:bintools,elfconvert_flag_outtarget>binary
    $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>.comment
    $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>COMMON
    $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>.eh_frame
    $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>.log_strings_sections
    $<TARGET_PROPERTY:bintools,elfconvert_flag_infile>${KERNEL_ELF_NAME}
    $<TARGET_PROPERTY:bintools,elfconvert_flag_outfile>${KERNEL_BIN_NAME}
    $<TARGET_PROPERTY:bintools,elfconvert_flag_final>)

if(CONFIG_BUILD_OUTPUT_HEX)
    set_property(GLOBAL APPEND PROPERTY extra_post_build_commands
        COMMAND $<TARGET_PROPERTY:bintools,elfconvert_command>
        $<TARGET_PROPERTY:bintools,elfconvert_flag>
        $<TARGET_PROPERTY:bintools,elfconvert_flag_outtarget>ihex
        $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>.comment
        $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>COMMON
        $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>.eh_frame
        $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>.log_strings_sections
        $<TARGET_PROPERTY:bintools,elfconvert_flag_infile>${KERNEL_ELF_NAME}
        $<TARGET_PROPERTY:bintools,elfconvert_flag_outfile>${KERNEL_HEX_NAME}
        $<TARGET_PROPERTY:bintools,elfconvert_flag_final>)
endif()

set_property(GLOBAL APPEND PROPERTY extra_post_build_commands
    COMMAND $<TARGET_PROPERTY:bintools,elfconvert_command>
    $<TARGET_PROPERTY:bintools,elfconvert_flag>
    $<TARGET_PROPERTY:bintools,elfconvert_flag_outtarget>binary
    $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>.comment
    $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>COMMON
    $<TARGET_PROPERTY:bintools,elfconvert_flag_section_remove>.eh_frame
    $<TARGET_PROPERTY:bintools,elfconvert_flag_section_only>.log_strings_sections
    $<TARGET_PROPERTY:bintools,elfconvert_flag_infile>${KERNEL_ELF_NAME}
    $<TARGET_PROPERTY:bintools,elfconvert_flag_outfile>mcu_log_str.bin
    $<TARGET_PROPERTY:bintools,elfconvert_flag_final>)

