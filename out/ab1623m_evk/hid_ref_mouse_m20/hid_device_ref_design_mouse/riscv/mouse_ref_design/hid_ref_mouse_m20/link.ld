OUTPUT_ARCH(riscv)
MEMORY
{
    ram(RWX) : ORIGIN = 0x84064000, LENGTH = 0x7A00
    stack(RW) : ORIGIN = 0x8406BA00, LENGTH = 0x200
    system_stack(RW) : ORIGIN = 0x8406BC00, LENGTH = 0x400
    ccm(RW) : ORIGIN = 0x000000000400e540, LENGTH = 0x0000000000001f54
    ROM_LOG_STRING (RX) : ORIGIN = 0x06000000, LENGTH = 0x02000000
}
ram_start_addr = ORIGIN(ram);
ram_length = LENGTH(ram);
_min_stack = 0;
_stack_len = LENGTH(stack);
_stack_start = ORIGIN(stack) + LENGTH(stack);
_thread_stack_begin = ORIGIN(stack);
_thread_stack_end = _stack_start;
_system_stack_len = LENGTH(system_stack);
_system_stack_start = ORIGIN(system_stack) + LENGTH(system_stack);
_isr_stack_begin = ORIGIN(system_stack);
_isr_stack_end = _system_stack_start;
_entry_point = _vectors_start + 0x80;
ENTRY(_entry_point)
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
    } > ram
    .rodata : {
        . = ALIGN(4);
        _rodata_start = .;
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
        *(.sbss)
        *(.sbss.*)
        *(.bss)
        *(.bss.*)
        *(COMMON)
        _bss_end = .;
    } > ram
    .stack (NOLOAD):
    {
        . = ALIGN(4);
        . = . + _min_stack ;
        . = ALIGN(4);
        stack = . ;
        _stack = . ;
    } > stack
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
    __fp_pattern_ram_total = LENGTH(ram);
    __fp_pattern_ram_used = _bss_end - ram_start_addr;
    __fp_pattern_ram_free = __fp_pattern_ram_total - __fp_pattern_ram_used;
    __fp_pattern_ram_free_begin = ram_start_addr + __fp_pattern_ram_used;
    __fp_pattern_ram_free_end = ram_start_addr + ram_length;
}
