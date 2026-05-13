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

COMMON_DIR := $(abspath ../common)
RISCV_ROOT_DIR := $(abspath .)
RISCV_FIRMWARE_OUT_DIR ?= $(RISCV_ROOT_DIR)/output

ARCH ?= rv32ec_zicsr_zifencei

SRCS = $(PROGRAM_C) $(EXTRA_SRCS)

C_SRCS = $(filter %.c, $(SRCS))
ASM_SRCS = $(filter %.S, $(SRCS))

AIR_SOC_CROSS_CORE_MEMORY_ENABLE ?= y
AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE ?= y

ifeq ($(AIR_SOC_CROSS_CORE_MEMORY_ENABLE),y)
CFLAGS += -DAIR_SOC_CROSS_CORE_MEMORY_ENABLE
endif


include $(COMMON_DIR)/middleware/airoha/share_buffer/module.mk

ifeq ($(AIR_PKA_SHARE_ENABLE),y)
include $(COMMON_DIR)/middleware/airoha/pka_share/module.mk
endif

ifeq ($(AIR_ADC_KEYSCAN_ENABLE),y)
include $(COMMON_DIR)/middleware/airoha/adc_keyscan/module.mk
endif


include $(COMMON_DIR)/drivers/chip/ab162x/module.mk

ifeq ($(AIR_HID_COMMON_SERVICE),y)
include $(COMMON_DIR)/applications/hid/module.mk
endif

ifeq ($(AIR_HID_EXPRESS_SERVICE),y)
include $(COMMON_DIR)/middleware/airoha/hid_express/module.mk
endif

ifeq ($(AIR_HID_DEVICE_SCENARIO_SERVICE_KEY_REMAP),y)
include $(COMMON_DIR)/middleware/airoha/key_remap/module.mk
endif

include $(CURDIR)/drivers/module.mk
include $(CURDIR)/kernel/service/exception_handler/module.mk
include $(CURDIR)/kernel/service/syslog/module.mk
include $(CURDIR)/kernel/service/swla/module.mk
include $(CURDIR)/kernel/service/system_online_dump/module.mk

LINKER_SCRIPT_OPTION ?=

ifneq ($(CROSS_BUILD_PARAMS_FILE),)
include $(RISCV_FIRMWARE_OUT_DIR)/$(CROSS_BUILD_PARAMS_FILE)
endif

ifeq ($(AIR_FPGA_ENV_ENABLE),y)
CFLAGS += -DFPGA_ENV
endif

ifeq ($(AIR_ONLINE_SWLA_ENABLE),y)
CFLAGS += -DAIR_SWLA_ENABLE
CFLAGS += -DAIR_ONLINE_SWLA_ENABLE
endif

ifeq ($(AIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE), y)
CFLAGS += -DAIR_SLEEP_MANAGER_LIGHT_MODE_ENABLE
endif

ifeq ($(AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE),y)
CFLAGS += -DAIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE
endif

TOOLCHAIN_DIR=$(CURDIR)/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/bin
TOOLCHAIN_BRIEF_PREFIX=riscv-none-elf-

CC 						= $(TOOLCHAIN_DIR)/$(TOOLCHAIN_BRIEF_PREFIX)gcc
NM 						= $(TOOLCHAIN_DIR)/$(TOOLCHAIN_BRIEF_PREFIX)nm
OBJCOPY 				= $(TOOLCHAIN_DIR)/$(TOOLCHAIN_BRIEF_PREFIX)objcopy
OBJDUMP 				= $(TOOLCHAIN_DIR)/$(TOOLCHAIN_BRIEF_PREFIX)objdump

LINKER_SCRIPT_TEMPLATE ?= $(CURDIR)/config/chip/ab162x/link.ld
LINKER_SCRIPT = $(RISCV_FIRMWARE_OUT_DIR)/link.ld
CRT ?= $(CURDIR)/config/chip/ab162x/startup.S

CFLAGS += -march=$(ARCH) -mabi=ilp32e -static -mcmodel=medany -Wall -g -Os\
	-fvisibility=hidden -nostartfiles -ffreestanding $(PROGRAM_CFLAGS)
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -save-temps=obj
CFLAGS += -Wall -Werror
CFLAGS += -Wl,-Map=$(RISCV_FIRMWARE_OUT_DIR)/$(PROGRAM).map
LDFLAGS ?= -Wl,--gc-sections -march=$(ARCH) -mabi=ilp32e -Wl,--print-memory-usage

OBJS := ${C_SRCS:.c=.o} ${ASM_SRCS:.S=.o} ${CRT:.S=.o}
OBJS := $(patsubst $(RISCV_ROOT_DIR)/%.o,$(RISCV_FIRMWARE_OUT_DIR)/%.o,$(OBJS))
OBJS := $(patsubst $(COMMON_DIR)/%.o,$(RISCV_FIRMWARE_OUT_DIR)/common/%.o,$(OBJS))
DEPS = $(OBJS:%.o=%.d)

OBJ_OUT_DIRS := $(sort $(dir $(OBJS)))

ifdef PROGRAM
OUTFILES := $(RISCV_FIRMWARE_OUT_DIR)/$(PROGRAM).elf $(RISCV_FIRMWARE_OUT_DIR)/$(PROGRAM).dis $(RISCV_FIRMWARE_OUT_DIR)/$(PROGRAM).bin
else
OUTFILES := $(OBJS)
endif

COMPILE_CMDS=$(RISCV_FIRMWARE_OUT_DIR)/compile_commands.json

all: print_vars create_dirs $(OUTFILES)


create_dirs:
	@$(foreach dir, $(OBJ_OUT_DIRS), mkdir -p $(dir);)
	@echo -n "" > $(COMPILE_CMDS)
	@echo "[" >> $(COMPILE_CMDS)


ldscript_preprocess: $(LINKER_SCRIPT_TEMPLATE)
	@echo "[Airoha][RISC-V] generate linker script $(LINKER_SCRIPT)..."
	@echo $(CC) -E -x assembler-with-cpp $(LINKER_SCRIPT_OPTION) $(LINKER_SCRIPT_TEMPLATE) -P -o $(LINKER_SCRIPT)
	$(CC) -E -x assembler-with-cpp $(LINKER_SCRIPT_OPTION) $(LINKER_SCRIPT_TEMPLATE) -P -o $(LINKER_SCRIPT)


print_vars:
	@$(foreach input, $(SRCS), echo "[Airoha][RISC-V] source file: $(subst $(RISCV_ROOT_DIR)/,,$(input))";)
	@$(foreach input, $(OBJS), echo "[Airoha][RISC-V] object file: $(subst $(RISCV_ROOT_DIR)/,,$(input))";)
	@$(foreach input, $(DEPS), echo "[Airoha][RISC-V] dependency file: $(subst $(RISCV_ROOT_DIR)/,,$(input))";)
	@$(foreach input, $(LIBS), echo "[Airoha][RISC-V] libray file: $(subst $(RISCV_ROOT_DIR)/,,$(input))";)
	@echo "[Airoha][RISC-V] RISCV_FIRMWARE_OUT_DIR is $(RISCV_FIRMWARE_OUT_DIR)"
	@echo "[Airoha][RISC-V] RISCV_ROOT_DIR is $(RISCV_ROOT_DIR)"
	@echo "[Airoha][RISC-V] COMMON_DIR is $(COMMON_DIR)"
	@echo "[Airoha][RISC-V] OUTFILES is $(OUTFILES)"
	@echo "[Airoha][RISC-V] CRT is $(CRT)"


ifdef PROGRAM
$(RISCV_FIRMWARE_OUT_DIR)/$(PROGRAM).elf: $(OBJS) ldscript_preprocess
	@echo "[Airoha][RISC-V] linking to generate $(subst $(RISCV_ROOT_DIR)/,,$@)..."

	@echo $(CC) $(CFLAGS) $(LDFLAGS) -T $(LINKER_SCRIPT) $(OBJS) -o $@ $(LIBS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -T $(LINKER_SCRIPT) $(OBJS) -o $@ $(LIBS)

	@echo $(OBJCOPY) -O binary --only-section=.log_str $@ $(RISCV_FIRMWARE_OUT_DIR)/risc_v_log_str.bin
	@$(OBJCOPY) -O binary --only-section=.log_str $@ $(RISCV_FIRMWARE_OUT_DIR)/risc_v_log_str.bin

	@echo $(NM) $@ > $(subst .elf,.symbols,$@)
	$(NM) $@ > $(subst .elf,.symbols,$@)

	@sed -i '$$ s/,$$//' "$(COMPILE_CMDS)"
	@echo "]" >> $(COMPILE_CMDS)

# .PHONY: disassemble
# disassemble: $(PROGRAM).dis
endif

$(RISCV_FIRMWARE_OUT_DIR)/%.dis: $(RISCV_FIRMWARE_OUT_DIR)/%.elf
	@echo "[Airoha][RISC-V] generate disassembly file for debugging..."
	@$(OBJDUMP) -fhd $^ > $@

# Note: this target requires the srecord package to be installed.
# XXX: This could be replaced by objcopy once
# https://sourceware.org/bugzilla/show_bug.cgi?id=19921
# is widely available.
# %.vmem: %.bin
# 	srec_cat $^ -binary -offset 0x0000 -byte-swap 4 -o $@ -vmem

$(RISCV_FIRMWARE_OUT_DIR)/%.bin: $(RISCV_FIRMWARE_OUT_DIR)/%.elf
	@echo "[Airoha][RISC-V] generate binary firmware..."
	@$(OBJCOPY) -O binary --remove-section=.debug_info --remove-section=.log_str $^ $@


$(RISCV_FIRMWARE_OUT_DIR)/%.o: $(RISCV_ROOT_DIR)/%.c
	@echo "[Airoha][RISC-V] compile $(subst $(RISCV_ROOT_DIR)/,,$<)..."
#@echo $(CC) $(CFLAGS) -MMD $(INCS) -o $@ -c $< >> $(COMPILE_CMDS)
	@echo "{" >> $(COMPILE_CMDS)
	@echo '  "directory":' \"$(RISCV_FIRMWARE_OUT_DIR)\", >> $(COMPILE_CMDS)
	@echo '  "command":' \"$(CC) $(CFLAGS) -MMD $(INCS) -o $@ -c $<\", >> $(COMPILE_CMDS)
	@echo '  "file":' \"$<\" >> $(COMPILE_CMDS)
	@echo "}," >> $(COMPILE_CMDS)
	@$(CC) $(CFLAGS) -MMD $(INCS) -o $@ -c $<


$(RISCV_FIRMWARE_OUT_DIR)/common/%.o: $(COMMON_DIR)/%.c
	@echo "[Airoha][RISC-V] compile common file $(subst $(COMMON_DIR)/,,$<)..."
#@echo $(CC) $(CFLAGS) -MMD $(INCS) -o $@ -c $< >> $(COMPILE_CMDS)
	@echo "{" >> $(COMPILE_CMDS)
	@echo '  "directory":' \"$(RISCV_FIRMWARE_OUT_DIR)\", >> $(COMPILE_CMDS)
	@echo '  "command":' \"$(CC) $(CFLAGS) -MMD $(INCS) -o $@ -c $<\", >> $(COMPILE_CMDS)
	@echo '  "file":' \"$<\" >> $(COMPILE_CMDS)
	@echo "}," >> $(COMPILE_CMDS)
	@$(CC) $(CFLAGS) -MMD $(INCS) -o $@ -c $<


$(RISCV_FIRMWARE_OUT_DIR)/%.o: $(RISCV_ROOT_DIR)/%.S
	@echo "[Airoha][RISC-V] assembly $(subst $(RISCV_ROOT_DIR)/,,$<)..."
	@$(CC) $(CFLAGS) -MMD $(INCS) -o $@ -c $<


clean:
	@echo "[Airoha][RISC-V] remove output directory $(RISCV_FIRMWARE_OUT_DIR)"
	@$(RM) -rf $(RISCV_FIRMWARE_OUT_DIR)


rebuild: clean all

.PHONY: all clean distclean create_dirs print_vars
