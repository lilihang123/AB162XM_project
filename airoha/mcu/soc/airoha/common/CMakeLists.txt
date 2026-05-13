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

zephyr_include_directories(.)

zephyr_library()

if(DEFINED AIR_ROOT_DIR)
    include(${AIR_ROOT_DIR}/cmake/common/air_chip.cmake)
else()
    include(../../../cmake/common/air_chip.cmake)
endif()

zephyr_library_sources_ifdef(CONFIG_ARM_MPU air_mpu_init.c)
zephyr_library_sources_ifdef(CONFIG_AIR_CACHE air_cache_init.c)
zephyr_library_sources_ifdef(CONFIG_BOOT_TIME_MEASUREMENT boot_time_measure.c)
zephyr_library_sources_ifdef(CONFIG_WRAP_PRINTK air_printk.c)
zephyr_library_sources_ifdef(CONFIG_AIR_MEMCPY_MEMSET_OPTIMIZE air_string_opt.s)
zephyr_library_sources_ifdef(CONFIG_TRACING_USER air_tracing.c)
zephyr_library_sources_ifdef(CONFIG_AIR_C_LIB_ALLOCATION_API_WRAP_ENABLE air_allocation_c_lib.c)
zephyr_library_sources_ifdef(CONFIG_AIR_Z_ALLOCATION_DEBUG_ENABLE air_allocation_zephyr.c)

zephyr_library_sources(air_uart_pre_init.c)

set(soc_common_addition_ld_opt "")
if(CONFIG_WRAP_PRINTK)
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=printk")
endif()

if(CONFIG_AIR_MEMCPY_MEMSET_OPTIMIZE)
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=memcpy -Wl,-wrap=memset")
endif()

if(CONFIG_AIR_C_LIB_ALLOCATION_API_WRAP_ENABLE)
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=malloc")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=aligned_alloc")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=memalign")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=realloc")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=free")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=calloc")
endif()


if(CONFIG_AIR_Z_ALLOCATION_DEBUG_ENABLE)
    # wrap memory allocation functions with prefix 'k_' in zephyr/kernel/mempool.c
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=k_free")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=k_aligned_alloc")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=k_malloc")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=k_calloc")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=k_realloc")
    # for include some apis in heap.h
    zephyr_library_include_directories(${ZEPHYR_BASE}/lib/heap)
endif()


if(CONFIG_AIR_STACK_PROTECT_ALL_ENABLE)
    zephyr_compile_options(-fstack-protector-all)
endif()

if(CONFIG_AIR_STACK_PROTECT_STRONG_ENABLE)
    zephyr_compile_options(-fstack-protector-strong)
endif()

if(CONFIG_AIR_STACK_PROTECT_ENABLE)
    zephyr_compile_options(-fstack-protector)
endif()

if(CONFIG_AIR_STACK_CHECK_FAIL_HOOK_WRAP_ENABLE)
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=__stack_chk_fail")
    zephyr_library_sources(stack_check_fail_hook.c)
endif()

# For non-cacheable intervals, zephyr native code always adds the execute never attribute, which is not as expected.
# For airoha's ab162x series, all RAMs are TCMs, which are non-cacheable and can run code.
if(CONFIG_ARM_MPU)
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=z_arm_configure_static_mpu_regions")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=z_arm_mpu_init")
endif()

if(CONFIG_AIR_PARTITION_ENABLE)
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=flash_area_foreach")
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=flash_area_open")
endif()

if(CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE)
    list(APPEND soc_common_addition_ld_opt "-Wl,-wrap=z_impl_device_get_binding")
endif()

if(CONFIG_AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE)
    zephyr_compile_definitions(AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE)
endif()

zephyr_ld_options(
    ${soc_common_addition_ld_opt}
)


add_subdirectory_ifdef(CONFIG_AIR_DAEMON_WORKQUEUE_ENABLE daemon_work_q/)
if (DEFINED CONFIG_SOC_SERIES_AB162X)
add_subdirectory_ifdef(CONFIG_AIR_LOGGING_ENABLE syslog_portable/)
add_subdirectory_ifdef(CONFIG_AIR_SWLA_ENABLE swla/)
add_subdirectory_ifdef(CONFIG_AIR_ONLINE_DUMP_ENABLE system_online_dump/)
add_subdirectory_ifdef(CONFIG_AIR_OFFLINE_DUMP_ENABLE offline_dump/)
endif() # CONFIG_SOC_SERIES_AB162X

if (DEFINED CONFIG_SOC_SERIES_AB161X)
add_subdirectory_ifdef(CONFIG_AIR_LOGGING_ENABLE syslog_portable/)
add_subdirectory_ifdef(CONFIG_AIR_SWLA_ENABLE swla/)
add_subdirectory_ifdef(CONFIG_AIR_ONLINE_DUMP_ENABLE system_online_dump/)
endif() # CONFIG_SOC_SERIES_AB162X

add_subdirectory_ifdef(CONFIG_AIR_EXCEPTION_HANDLER_ENABLE exception_handler/)

add_subdirectory_ifdef(CONFIG_AIR_BSP_FLASH_ENABLE bsp_flash/)
add_subdirectory_ifdef(CONFIG_AIR_BDM_ENABLE bdm/)
