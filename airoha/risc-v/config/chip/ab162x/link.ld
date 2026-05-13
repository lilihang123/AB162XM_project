/* Copyright lowRISC contributors.
   Licensed under the Apache License, Version 2.0, see LICENSE for details.
   SPDX-License-Identifier: Apache-2.0 */

OUTPUT_ARCH(riscv)

MEMORY
{
/* Change this if you'd like different sizes. Arty A7-100(35) has a maximum of 607.5KB(225KB)
   BRAM space. Configuration below is for maximum BRAM capacity with Artya A7-35 while letting
   CoreMark run (.vmem of 152.8KB).
*/
    /* 30KB code + 1KB for threa stack + 1KB for ISR stack */
    ram(RWX)            : ORIGIN = 0x84064000, LENGTH = 0x7A00
    stack(RW)           : ORIGIN = 0x8406BA00, LENGTH = 0x200
    system_stack(RW)    : ORIGIN = 0x8406BC00, LENGTH = 0x400

    /* 28KB code + 2KB for threa stack + 2KB for ISR stack */
/*  ram(RWX)            : ORIGIN = 0x84064000, LENGTH = 0x7000
    stack(RW)           : ORIGIN = 0x8406B000, LENGTH = 0x800
    system_stack(RW)    : ORIGIN = 0x8406B800, LENGTH = 0x800 */

    ccm(RW)             : ORIGIN = _cross_core_mem_zi_data_start, LENGTH = _cross_core_mem_size
    ROM_LOG_STRING (RX) : ORIGIN = 0x06000000, LENGTH = 0x02000000
}

ram_start_addr = ORIGIN(ram);
ram_length = LENGTH(ram);

/* Stack information variables */
_min_stack      = 0;   /* 8K - minimum stack space to reserve */

_stack_len     = LENGTH(stack);
_stack_start   = ORIGIN(stack) + LENGTH(stack);
_thread_stack_begin = ORIGIN(stack);
_thread_stack_end = _stack_start;

_system_stack_len     = LENGTH(system_stack);
_system_stack_start   = ORIGIN(system_stack) + LENGTH(system_stack);
_isr_stack_begin = ORIGIN(system_stack);
_isr_stack_end = _system_stack_start;

_entry_point = _vectors_start + 0x80;
ENTRY(_entry_point)

/* The tohost address is used by Spike for a magic "stop me now" message. This
   is set to equal SIM_CTRL_CTRL (see simple_system_regs.h), which has that
   effect in simple_system simulations. Note that it must be 8-byte aligned.

   We don't read data back from Spike, so fromhost is set to some dummy value:
   we place it just above the top of the stack.
 */
/* tohost   = 0x20008; */
fromhost = _stack_start + 0x10;

SECTIONS
{
    .vectors :
    {
        . = ALIGN(4);
        _vectors_start = .;
        KEEP(*(.vectors))
        _vectors_end = .;
    } > ram

    .text : ALIGN(4)
    {
        . = ALIGN(4);
        _text_start = .;
        *(.text)
        *(.text.*)
        *(.tcm_code.*)
        _text_end = .;
    }  > ram

    .rodata : {
        . = ALIGN(4);
        _rodata_start = .;
        /* Small RO data before large RO data */
        *(.srodata)
        *(.srodata.*)
        *(.rodata);
        *(.rodata.*)

        . = ALIGN(4);
        _log_filter_start = .;
        KEEP(*(SORT_BY_NAME(.log_filter.*)))
        _log_filter_end = .;

        _rodata_end = .;
    } > ram

    .data : {
        . = ALIGN(4);
        _data_start = .;
        /* Small data before large data */
        *(.sdata)
        *(.sdata.*)
        *(.data);
        *(.data.*)
        _data_end = .;
    } > ram

    .bss (NOLOAD):
    {
        . = ALIGN(4);
        _bss_start = .;
        /* Small BSS before large BSS */
        *(.sbss)
        *(.sbss.*)
        *(.bss)
        *(.bss.*)
        *(COMMON)
        _bss_end = .;
    } > ram

    /* ensure there is enough room for stack */
    .stack (NOLOAD):
    {
        . = ALIGN(4);
        . = . + _min_stack ;
        . = ALIGN(4);
        stack = . ;
        _stack = . ;
    } > stack

    /* ensure there is enough room for stack */
    .system_stack (NOLOAD):
    {
        . = ALIGN(4);
        system_stack = . ;
        _system_stack = . ;
    } > system_stack

    .cross_core_zi_data (NOLOAD) :ALIGN(4)
    {
        _cross_core_mem_start = .;
        KEEP(*(SORT_BY_NAME(SORT_BY_ALIGNMENT(.share_zidata*))))
        _cross_core_mem_end = .;
    }> ccm

    /* log string */
    .log_str :
    {
        __log_strings_start = .;
        KEEP(*(.log_version))
        KEEP(*(.log_timestamp))
        KEEP(*(SORT_BY_NAME(.log_filter_mirror*)))
        KEEP(*(.log_filter_end))
        KEEP(*(.log_chip_option))
        *(.log_string)
        *(.assert_string*)
        __log_strings_end = .;
    } > ROM_LOG_STRING


    /* Add some symbols to facilitate the calculation of
     * the amount and remaining amount of various memory.
     */
    __fp_pattern_ram_total = LENGTH(ram);
    __fp_pattern_ram_used = _bss_end - ram_start_addr;
    __fp_pattern_ram_free = __fp_pattern_ram_total - __fp_pattern_ram_used;
    __fp_pattern_ram_free_begin = ram_start_addr + __fp_pattern_ram_used;
    __fp_pattern_ram_free_end = ram_start_addr + ram_length;
}
