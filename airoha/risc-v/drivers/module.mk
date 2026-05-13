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

# Copyright lowRISC contributors.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
DRIVERS_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

C_SRCS += $(wildcard $(DRIVERS_DIR)/chip/ab162x/src/hal_*.c)
C_SRCS += $(wildcard $(DRIVERS_DIR)/chip/ab162x/src/mouse_sensor.c)
C_SRCS += $(wildcard $(DRIVERS_DIR)/chip/ab162x/src_core/hal_*.c)
# C_SRCS += $(DRIVERS_DIR)/chip/ab162x/src_core/hal_sleep_manager_internal.c

CFLAGS += -DCORE_RISCV
CFLAGS += -DHAL_SPI_MASTER_MODULE_ENABLED
CFLAGS += -DHAL_RTC_MODULE_ENABLED
CFLAGS += -DAIR_BTD_IC_PREMIUM_G1
CFLAGS += -DAIR_SHARE_BUFFER_ENABLE
CFLAGS += -DHAL_SW_DMA_MODULE_ENABLED
CFLAGS += -DHAL_HW_SEMAPHORE_MODULE_ENABLED
CFLAGS += -DHAL_CCNI_MODULE_ENABLED
CFLAGS += -DHAL_GPIO_MODULE_ENABLED
CFLAGS += -DHAL_EINT_MODULE_ENABLED
CFLAGS += -DHAL_UART_MODULE_ENABLED
CFLAGS += -DHAL_QDEC_MODULE_ENABLED
CFLAGS += -DHAL_RAMBOZ_MODULE_ENABLED
CFLAGS += -DHAL_SLEEP_MANAGER_ENABLED
CFLAGS += -DHAL_CLOCK_MODULE_ENABLED
CFLAGS += -DHAL_GPT_MODULE_ENABLED
CFLAGS += -DHAL_COMPARATOR_MODULE_ENABLED
CFLAGS += -DHAL_SARADC_MODULE_ENABLED
CFLAGS += -DHAL_HW_KEYSCAN_MODULE_ENABLED

INCS += -I$(DRIVERS_DIR)/chip/ab162x/inc