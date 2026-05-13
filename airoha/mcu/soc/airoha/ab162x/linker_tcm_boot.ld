/* Copyright Statement:
 *
 * (C) 2025  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("AIROHA SOFTWARE")
 * RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES ARE PROVIDED
 * TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

/* SPDX-License-Identifier: Apache-2.0 */

/**
 * @file
 * @brief Linker command/script file
 *
 * Linker script for the Cortex-M platforms.
 */

#include <zephyr/linker/sections.h>
#include <zephyr/devicetree.h>

#include <zephyr/linker/devicetree_regions.h>
#include <zephyr/linker/linker-defs.h>
#include <zephyr/linker/linker-tool.h>

/* physical address of RAM */
#define ROMABLE_REGION SRAM
#define RAMABLE_REGION SRAM
#define RAM_SIZE (CONFIG_SRAM_SIZE * 1K)
#define RAM_ADDR CONFIG_SRAM_BASE_ADDRESS

#if defined(CONFIG_CUSTOM_SECTION_ALIGN)
_region_min_align = CONFIG_CUSTOM_SECTION_MIN_ALIGN_SIZE;
#else
/* Set alignment to CONFIG_ARM_MPU_REGION_MIN_ALIGN_AND_SIZE
 * to make linker section alignment comply with MPU granularity.
 */
#if defined(CONFIG_ARM_MPU_REGION_MIN_ALIGN_AND_SIZE)
_region_min_align = CONFIG_ARM_MPU_REGION_MIN_ALIGN_AND_SIZE;
#else
/* If building without MPU support, use default 4-byte alignment. */
_region_min_align = 4;
#endif
#endif

#if !defined(CONFIG_CUSTOM_SECTION_ALIGN) && defined(CONFIG_MPU_REQUIRES_POWER_OF_TWO_ALIGNMENT)
#define MPU_ALIGN(region_size) \
    . = ALIGN(_region_min_align); \
    . = ALIGN( 1 << LOG2CEIL(region_size))
#else
#define MPU_ALIGN(region_size) \
    . = ALIGN(_region_min_align)
#endif

#if CONFIG_AIR_PADDING_AROUND_RAM_TEXT_ENABLE
    #if CONFIG_AIR_PADDING_AROUND_RAM_TEXT_ALIGNMENT_16K
        #define PADDING_AROUND_RAM_TEXT 16*1024
    #elif CONFIG_AIR_PADDING_AROUND_RAM_TEXT_ALIGNMENT_32K
        #define PADDING_AROUND_RAM_TEXT 32*1024
    #elif CONFIG_AIR_PADDING_AROUND_RAM_TEXT_ALIGNMENT_64K
        #define PADDING_AROUND_RAM_TEXT 64*1024
    #else
        #error "unkown choice"
    #endif
#else
    #define PADDING_AROUND_RAM_TEXT 4
#endif

#define SYSRAM_BT_BASE        (DT_REG_ADDR_BY_IDX(DT_NODELABEL(ram_bt), 0))
#define SYSRAM_BT_LENGTH      (DT_REG_SIZE_BY_IDX(DT_NODELABEL(ram_bt), 0))

#define TCM_BASE              (DT_REG_ADDR_BY_IDX(DT_NODELABEL(tcm), 0))
/* For ab1620, cache memory is not include in TCM */
#define TCM_LENGTH            (DT_REG_SIZE_BY_IDX(DT_NODELABEL(tcm), 0))

/* For the ab1620 series chip, all RAM is TCM, but for the zephyr's link script template,
 * TCM does not have a separately defined name, it is collectively called SRAM.
 */
#define TCM SRAM

MEMORY
{
    SRAM  (rwx)     : ORIGIN = TCM_BASE,                LENGTH = TCM_LENGTH
    SRAM_BT (rwx)   : ORIGIN = SYSRAM_BT_BASE,          LENGTH = SYSRAM_BT_LENGTH
    ROM_LOG_STRING (rw) : ORIGIN = 0x06000000,          LENGTH = 0x02000000

    LINKER_DT_REGIONS()
    /* Used by and documented in include/linker/intlist.ld */
    IDT_LIST (wx) : ORIGIN = 0xFFFFF7FF, LENGTH = 2K
}

ENTRY(CONFIG_KERNEL_ENTRY)

SECTIONS
{
#ifdef CONFIG_AIR_LOGGING_ENABLE
    #include "../common/log_string.ld"
#endif

#include <zephyr/linker/rel-sections.ld>

    /*
     * .plt and .iplt are here according to 'arm-zephyr-elf-ld --verbose',
     * before text section.
     */
    /DISCARD/ :
    {
        *(.plt)
    }

    /DISCARD/ :
    {
        *(.iplt)
    }


    /* no special meaning */
    GROUP_START(ROMABLE_REGION)

    __rom_region_start = RAM_ADDR;

    /* in z_arm_configure_static_mpu_regions, mpu will protected this region as no access */
    _nocache_ram_start = ORIGIN(SRAM);
    /* _nocache_ram_size = ORIGIN(SRAM); */
    _nocache_ram_size = LENGTH(SRAM);

#ifdef CONFIG_BOOTLOADER_MCUBOOT
    #include "../common/signature.ld"
#endif /* CONFIG_BOOTLOADER_MCUBOOT */

    /* zephyr/include/zephyr/linker/linker-tool-gcc.h
     * Define the section name, options and align settings
     * according to the syntax of the linker script.
     */
    SECTION_PROLOGUE(rom_start,,)
    {

#if 0
/* Located in generated directory. This file is populated by calling
 * zephyr_linker_sources(ROM_START ...). This typically contains the vector
 * table and debug information.
 */
#include <snippets-rom-start.ld>
    /* <BUILD_ROOT>/zephyr/include/generated/snippets-rom-start.ld
     *     zephyr/arch/common/rom_start_offset.ld( CONFIG_ROM_START_OFFSET <=> 0 )
     *     zephyr/arch/arm/core/aarch32/vector_table.ld
     */
#else

        #ifdef CONFIG_AIR_STD_ARM_BOOT_METHOD_ENABLE
        /* follow the default jump method of mcuboot/arm */
        LONG(_stack_end);
        LONG(Reset_Handler|0x1);
        #endif

        /* Set the MSP in the reset handler and place the reset-related code
         * at the beginning of the image. This is Airoha's special booting flow. */
        KEEP(*(.reset_handler*))
#if CONFIG_MCUBOOT
        KEEP(*(.rom_parameter*))
#endif

#endif
    } GROUP_LINK_IN(ROMABLE_REGION)


    GROUP_START(RAMABLE_REGION)

    . = RAM_ADDR;
    /* Align the start of image SRAM with the
     * minimum granularity required by MPU.
     */
    . = ALIGN(_region_min_align);
    _image_ram_start = .;

/* Located in generated directory. This file is populated by the
 * zephyr_linker_sources() Cmake function.
 * It can realize the noncache function and the placement of some ram functions.
 * zephyr/arch/common/nocache.ld
 */
#if 0
    #include <snippets-ram-sections.ld>
#else
    #include "../arch/common/ramfunc.ld"
#endif

    GROUP_START(DATA_REGION)

    SECTION_DATA_PROLOGUE(_DATA_SECTION_NAME,,)
    {
        __data_region_start = .;
        __data_start = .;

        *(.data)
        *(".data.*")
        *(".kernel.*")
        *(.cached_sysram_rwdata*)
#if CONFIG_TCM_BOOTING
    #include "../common/tcm_rw.ld"
#endif

/* Located in generated directory. This file is populated by the
 * zephyr_linker_sources() Cmake function.
 */
#include <snippets-rwdata.ld>

#ifdef CONFIG_CODE_DATA_RELOCATION
#include <linker_sram_data_relocate.ld>
#endif
        __data_end = .;

    } GROUP_DATA_LINK_IN(RAMABLE_REGION, ROMABLE_REGION)
    __data_size = __data_end - __data_start;
    __data_load_start = LOADADDR(_DATA_SECTION_NAME);

    __data_region_load_start = LOADADDR(_DATA_SECTION_NAME);

#include <zephyr/linker/common-ram.ld>
#include <zephyr/linker/kobject-data.ld>

#include <zephyr/linker/cplusplus-ram.ld>

/* Located in generated directory. This file is populated by the
 * zephyr_linker_sources() Cmake function.
 */
#include <snippets-data-sections.ld>

    __data_region_end = .;


    SECTION_DATA_PROLOGUE(_BSS_SECTION_NAME,(NOLOAD),)
    {
        /*
         * For performance, BSS section is assumed to be 4 byte aligned and
         * a multiple of 4 bytes
         */
        . = ALIGN(4);
        __bss_start = .;
        __kernel_ram_start = .;

        *(.bss)
        *(".bss.*")
        *(COMMON)
        *(".kernel_bss.*")
        *(.cached_sysram_zidata*)
#if CONFIG_TCM_BOOTING
    #include "../common/tcm_zi.ld"
#endif

#ifdef CONFIG_CODE_DATA_RELOCATION
#include <linker_sram_bss_relocate.ld>
#endif

        /*
         * As memory is cleared in words only, it is simpler to ensure the BSS
         * section ends on a 4 byte boundary. This wastes a maximum of 3 bytes.
         */
        __bss_end = ALIGN(4);
    } GROUP_DATA_LINK_IN(RAMABLE_REGION, RAMABLE_REGION)
    /* In theory, AT should not be used to specify Load Memory,
     * but there is no side effect in practice.
     */

#ifdef CONFIG_AIR_SOC_CROSS_CORE_MEMORY_ENABLE
    #include "cross_core_mem.ld"
#endif

    SECTION_PROLOGUE(_NOINIT_SECTION_NAME,(NOLOAD),)
    {
        __no_init_start = .;
        /*
         * This section is used for non-initialized objects that
         * will not be cleared during the boot process.
         */
        *(.noinit)
        *(".noinit.*")
        *(".kernel_noinit.*")

/* Located in generated directory. This file is populated by the
 * zephyr_linker_sources() Cmake function.
 */
#include <snippets-noinit.ld>

        __no_init_end = .;
    } GROUP_LINK_IN(RAMABLE_REGION)

    /* Define linker symbols */
    _image_ram_end = .;
    _end = .;

#include "../common/sram_bt.ld"

    __kernel_ram_end = RAM_ADDR + RAM_SIZE;
    __kernel_ram_size = __kernel_ram_end - __kernel_ram_start;

    GROUP_END(RAMABLE_REGION)

    .padding_after_data (NOLOAD):
    {
        /* linker symbols for footprint */
        __padding_after_retention_text_start = .;
        __padding_before_tcm_text_start = .;
        . = ALIGN(PADDING_AROUND_RAM_TEXT);
        __padding_after_retention_text_end = .;
        __padding_before_tcm_text_end = .;
        _tcm_rw_data_non_retention_start = .;
        _tcm_rw_data_non_retention_end = .;
        _tcm_zi_data_non_retention_start = .;
        _tcm_zi_data_non_retention_end = .;
    } GROUP_LINK_IN(RAMABLE_REGION)


    /* GROUP_LINK_IN
     * Specify the position of the section according to the linker syntax,
     * including execution view and load view.
     * Under the condition of GROUP_LINK_IN, the two views are equal.
     */

    _stack_start = z_main_stack;
    _stack_end = z_main_stack + CONFIG_MAIN_STACK_SIZE;

#ifdef CONFIG_CODE_DATA_RELOCATION

#include <linker_relocate.ld>

#endif /* CONFIG_CODE_DATA_RELOCATION */

    SECTION_PROLOGUE(_TEXT_SECTION_NAME,,)
    {
        __text_region_start = .;

#include <zephyr/linker/kobject-text.ld>

       *(EXCLUDE_FILE(
            *swap_helper.S.obj
            *libkernel.a
            ).text*)

        *(".TEXT.*")

        KEEP(*(SORT_BY_NAME(._af_evt_type*)))
        KEEP(*(SORT_BY_NAME(_app_evt_dispatcher_*)))

        *(.gnu.linkonce.t.*)
#if CONFIG_TCM_BOOTING
    #include "../common/tcm_ro.ld"
#endif

        /*
        * These are here according to 'arm-zephyr-elf-ld --verbose',
        * after .gnu.linkonce.t.*
        */
        *(.glue_7t) *(.glue_7) *(.vfp11_veneer) *(.v4_bx)
        . = ALIGN(4);

        __text_region_end = .;
    } GROUP_LINK_IN(ROMABLE_REGION)

#if defined(CONFIG_CPLUSPLUS) || defined(CONFIG_CPP)
    SECTION_PROLOGUE(.ARM.extab,,)
    {
    /*
     * .ARM.extab section containing exception unwinding information.
     */
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    } GROUP_LINK_IN(ROMABLE_REGION)
#endif

    SECTION_PROLOGUE(.ARM.exidx,,)
    {
        /*
        * This section, related to stack and exception unwinding, is placed
        * explicitly to prevent it from being shared between multiple regions.
        * It  must be defined for gcc to support 64-bit math and avoid
        * section overlap.
        */
        __exidx_start = .;
#if defined (__GCC_LINKER_CMD__)
        *(.ARM.exidx* gnu.linkonce.armexidx.*)
#endif
        __exidx_end = .;
    } GROUP_LINK_IN(ROMABLE_REGION)

    __rodata_region_start = .;

#include <zephyr/linker/common-rom.ld>
#include <zephyr/linker/thread-local-storage.ld>

    SECTION_PROLOGUE(_RODATA_SECTION_NAME,,)
    {
        *(.rodata)
        *(".rodata.*")

        . = ALIGN(4);
        __riscv_firmware_scenario_start = .;
        KEEP(*(SORT_BY_NAME(.riscv_scenario.[0-9].*)))
        . = ALIGN(4);
        __riscv_firmware_scenario_end = .;

#ifdef CONFIG_AIR_LOGGING_ENABLE
        #include "../common/log_filter.ld"
#endif

        *(.gnu.linkonce.r.*)

/* Located in generated directory. This file is populated by the
 * zephyr_linker_sources() Cmake function.
 */
#include <snippets-rodata.ld>

#include <zephyr/linker/kobject-rom.ld>

        /*
        * For XIP images, in order to avoid the situation when __data_rom_start
        * is 32-bit aligned, but the actual data is placed right after rodata
        * section, which may not end exactly at 32-bit border, pad rodata
        * section, so __data_rom_start points at data and it is 32-bit aligned.
        *
        * On non-XIP images this may enlarge image size up to 3 bytes. This
        * generally is not an issue, since modern ROM and FLASH memory is
        * usually 4k aligned.
        */
        . = ALIGN(4);
    } GROUP_LINK_IN(ROMABLE_REGION)

    __riscv_firmware_scenario_num = (__riscv_firmware_scenario_end - __riscv_firmware_scenario_start)/8;

#include <zephyr/linker/cplusplus-rom.ld>

    __rodata_region_end = .;
    MPU_ALIGN(__rodata_region_end -__rom_region_start);
    __rom_region_end = .;

    GROUP_END(ROMABLE_REGION)

    /*
     * These are here according to 'arm-zephyr-elf-ld --verbose',
     * before data section.
     */
    /DISCARD/ : {
        *(.got.plt)
        *(.igot.plt)
        *(.got)
        *(.igot)
    }



/* Located in generated directory. This file is populated by the
 * zephyr_linker_sources() Cmake function.
 */
#include <snippets-sections.ld>

#include <zephyr/linker/debug-sections.ld>

    /DISCARD/ : { *(.note.GNU-stack) }

    SECTION_PROLOGUE(.ARM.attributes, 0,)
    {
        KEEP(*(.ARM.attributes))
        KEEP(*(.gnu.attributes))
    }

    /* Sections generated from 'zephyr,memory-region' nodes */
    LINKER_DT_SECTIONS()

#ifndef CONFIG_TCM_BOOTING
    /* Must be last in romable region */
SECTION_PROLOGUE(.last_section,,)
    {
#ifdef CONFIG_LINKER_LAST_SECTION_ID
  /* Fill last section with a word to ensure location counter and actual rom
   * region data usage match. */
  LONG(CONFIG_LINKER_LAST_SECTION_ID_PATTERN)
#endif
    } GROUP_LINK_IN(ROMABLE_REGION)

    /* To provide the image size as a const expression,
    * calculate this value here. */
_flash_used = LOADADDR(.last_section) + SIZEOF(.last_section) - __rom_region_start;
#endif
}
