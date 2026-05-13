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

if(DEFINED CONFIG_AIR_NVKEY_ENABLE)

    zephyr_compile_definitions(AIR_NVKEY_ENABLE)

    zephyr_library()
    include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)
    zephyr_include_directories(inc)
    zephyr_include_directories(${AIR_PREBUILT_LIB_ROOT}/middleware/airoha/nvkey/${SOC_SERIES}/inc)

    aux_source_directory(src SRC)
    zephyr_library_sources(${SRC})

    # add default nvkey xml files
    airoha_nvkey_append_xml(${AIR_ROOT_DIR}/soc/${SOC_FAMILY}/${SOC_SERIES}/nvkey.xml)
    airoha_nvkey_append_xml(${AIR_ROOT_DIR}/boards/airoha/${BOARD}/nvkey.xml)
    # nvkey data file of app level should be appended in project level
    # airoha_nvkey_append_xml(${APPLICATION_SOURCE_DIR}/${CONFIG_AIR_NVKEY_APP_LEVEL_FILE})
    # add default nvkey xml files

    message(NOTICE "[Airoha] CONFIG_SETTINGS_NVS_SECTOR_COUNT is ${CONFIG_SETTINGS_NVS_SECTOR_COUNT}")
    message(NOTICE "[Airoha] CONFIG_STORAGE_PARTITION_SIZE is ${CONFIG_STORAGE_PARTITION_SIZE}")
    message(NOTICE "[Airoha] NVKEY_FILE_LIST is ${NVKEY_FILE_LIST}")
    message(NOTICE "[Airoha] GEN_DEFAULT_NVS_BIN is ${CONFIG_GEN_DEFAULT_NVS_BIN}")
endif() # DEFINED CONFIG_AIR_NVKEY_ENABLE
