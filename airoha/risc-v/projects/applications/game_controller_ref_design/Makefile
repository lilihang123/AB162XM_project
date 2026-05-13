#  Copyright Statement:
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

FEATURE ?= feature.mk

# Name of the program $(PROGRAM).c will be added as a source file
PROGRAM_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
PROGRAM = $(shell basename $(PROGRAM_DIR))
# Any extra source files to include in the build. Use the upper case .S
# extension for assembly files
EXTRA_SRCS := ${PROGRAM_DIR}/src/app/riscv_main.c
EXTRA_SRCS += ${PROGRAM_DIR}/src/app/riscv_ccni.c
EXTRA_SRCS += ${PROGRAM_DIR}/src/app/riscv_peripheral_sampling.c
EXTRA_SRCS += ${PROGRAM_DIR}/src/app/riscv_game_controller_key.c
EXTRA_SRCS += ${PROGRAM_DIR}/src/app/riscv_joystick_and_trigger.c
EXTRA_SRCS += ${PROGRAM_DIR}/../general_used/src/sys_init.c

INCS := -I${PROGRAM_DIR}/inc/app
INCS += -I${PROGRAM_DIR}/../general_used/inc


include $(CURDIR)/middleware/airoha/pka/module.mk

include $(PROGRAM_DIR)/${FEATURE}
$(info FEATURE IN GCC = $(PROGRAM_DIR)/$(FEATURE))

include ${PROGRAM_DIR}/../../../config/chip/ab162x/common.mk

ifeq ($(AIR_BASIC_LA_DEBUG),y)
CFLAGS += -DAIR_BASIC_LA_DEBUG
endif


ifeq ($(AIR_REPORT_DATA_LOG),y)
CFLAGS += -DAIR_REPORT_DATA_LOG
endif

ifeq ($(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP),y)
CFLAGS += -DAIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP

ifeq ($(AIR_FN_KEY_ENABLE),y)
CFLAGS += -DAIR_FN_KEY_ENABLE
endif

ifeq ($(AIR_KEY_REMAP_FRONTEND_RISCV),y)
CFLAGS += -DAIR_KEY_REMAP_FRONTEND_RISCV
endif

ifeq ($(AIR_KEY_REMAP_BACKEND_RISCV),y)
CFLAGS += -DAIR_KEY_REMAP_BACKEND_RISCV
endif
endif

ifeq ($(AIR_HID_BT_MODE),y)
CFLAGS += -DAIR_HID_BT_MODE
endif

ifeq ($(AIR_BACKUP_RESTORE_LOG),y)
CFLAGS += -DAIR_BACKUP_RESTORE_LOG
endif

ifeq ($(AIR_REPORT_LOG_NACK_BIT),y)
CFLAGS += -DAIR_REPORT_LOG_NACK_BIT
endif

ifeq ($(AIR_DEBUG_POLLING_LOG),y)
CFLAGS += -DAIR_DEBUG_POLLING_LOG
endif

ifeq ($(AIR_2_4G_RELIABLE_RETRASMISSION),y)
CFLAGS += -DAIR_2_4G_RELIABLE_RETRASMISSION
endif

ifeq ($(AIR_FAKE_REPORT),y)
CFLAGS += -DAIR_FAKE_REPORT
endif

ifeq ($(AIR_USB_CCNI_WAKEUP_CM33),y)
CFLAGS += -DAIR_USB_CCNI_WAKEUP_CM33
endif

ifeq ($(AIR_PRODUCT_TYPE_GAME_CONTROLLER),y)
CFLAGS += -DAIR_PRODUCT_TYPE_GAME_CONTROLLER
endif

ifeq ($(AIR_GAME_CONTROLLER_9B_DATA),y)
CFLAGS += -DAIR_GAME_CONTROLLER_9B_DATA
endif

ifeq ($(AIR_GAME_CONTROLLER_12BIT_ADC),y)
CFLAGS += -DAIR_GAME_CONTROLLER_12BIT_ADC
endif

ifeq ($(AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE),y)
CFLAGS += -DAIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE
endif

ifeq ($(AIR_HW_KEYSCAN),y)
CFLAGS += -DAIR_HW_KEYSCAN
endif

ifeq ($(AIR_HID_DUMMY_REPORT_RATE),y)
CFLAGS += -DAIR_HID_DUMMY_REPORT_RATE
endif
