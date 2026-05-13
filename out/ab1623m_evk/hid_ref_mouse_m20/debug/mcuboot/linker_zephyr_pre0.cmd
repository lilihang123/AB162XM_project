 OUTPUT_FORMAT("elf32-littlearm")
_region_min_align = 4;
MEMORY
{
    SRAM (rwx) : ORIGIN = (67108864), LENGTH = (393216)
    SRAM_BT (rwx) : ORIGIN = (67502080), LENGTH = (16384)
    ROM_LOG_STRING (rw) : ORIGIN = 0x06000000, LENGTH = 0x02000000
   
    IDT_LIST (wx) : ORIGIN = 0xFFFFF7FF, LENGTH = 2K
}
ENTRY("Reset_Handler")
SECTIONS
{
 .rel.plt :
 {
 *(.rel.plt)
 PROVIDE_HIDDEN (__rel_iplt_start = .);
 *(.rel.iplt)
 PROVIDE_HIDDEN (__rel_iplt_end = .);
 }
 .rela.plt :
 {
 *(.rela.plt)
 PROVIDE_HIDDEN (__rela_iplt_start = .);
 *(.rela.iplt)
 PROVIDE_HIDDEN (__rela_iplt_end = .);
 }
 .rel.dyn :
 {
 *(.rel.*)
 }
 .rela.dyn :
 {
 *(.rela.*)
 }
    /DISCARD/ :
    {
        *(.plt)
    }
    /DISCARD/ :
    {
        *(.iplt)
    }
   
    __rom_region_start = 0x4000000;
    _nocache_ram_start = ORIGIN(SRAM);
    _nocache_ram_size = LENGTH(SRAM);
    rom_start :
    {
        KEEP(*(.reset_handler*))
        KEEP(*(.rom_parameter*))
    } > SRAM
    _stack_start = z_main_stack;
    _stack_end = z_main_stack + 2048;
    text :
    {
        __text_region_start = .;
       *(EXCLUDE_FILE(
            *swap_helper.S.obj
            *libkernel.a
            ).text*)
        *(".TEXT.*")
        KEEP(*(SORT_BY_NAME(._af_evt_type*)))
        KEEP(*(SORT_BY_NAME(_app_evt_dispatcher_*)))
        *(.gnu.linkonce.t.*)
. = ALIGN(4);
_tcm_text_start = .;
. = ALIGN(128);
exception_num = 16 + 53;
. = ALIGN( 1 << LOG2CEIL(exception_num*4));
_vector_start = .;
KEEP(*(.isr_vector))
KEEP(*(.gnu.linkonce.irq_vector_table*))
KEEP(*(.vectors))
*(.exception_code*)
*swap_helper.S.obj(.text*)
*libkernel.a:*.c.obj(.text*)
*(.exception_rodata*)
*(.tcm_code_retention*)
*(.ram_code*)
*(.tcm_code*)
*(.sysram_code*)
*(.tcm_rodata*)
*(.ram_rodata*)
*(.sysram_rodata*)
. = ALIGN(4);
_tcm_text_end = .;
_vector_end = .;
        *(.glue_7t) *(.glue_7) *(.vfp11_veneer) *(.v4_bx)
        . = ALIGN(4);
        __text_region_end = .;
    } > SRAM
    .ARM.extab :
    {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > SRAM
    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx* gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > SRAM
    __rodata_region_start = .;
 initlevel :
 {
  __init_start = .;
  __init_EARLY_start = .; KEEP(*(SORT(.z_init_EARLY?_*))); KEEP(*(SORT(.z_init_EARLY??_*)));
  __init_PRE_KERNEL_1_start = .; KEEP(*(SORT(.z_init_PRE_KERNEL_1?_*))); KEEP(*(SORT(.z_init_PRE_KERNEL_1??_*)));
  __init_PRE_KERNEL_2_start = .; KEEP(*(SORT(.z_init_PRE_KERNEL_2?_*))); KEEP(*(SORT(.z_init_PRE_KERNEL_2??_*)));
  __init_POST_KERNEL_start = .; KEEP(*(SORT(.z_init_POST_KERNEL?_*))); KEEP(*(SORT(.z_init_POST_KERNEL??_*)));
  __init_APPLICATION_start = .; KEEP(*(SORT(.z_init_APPLICATION?_*))); KEEP(*(SORT(.z_init_APPLICATION??_*)));
  __init_SMP_start = .; KEEP(*(SORT(.z_init_SMP?_*))); KEEP(*(SORT(.z_init_SMP??_*)));
  __init_end = .;
  __deferred_init_list_start = .;
  KEEP(*(.z_deferred_init*))
  __deferred_init_list_end = .;
 } > SRAM
 device_area : SUBALIGN(4) { _device_list_start = .; KEEP(*(SORT(._device.static.*_?_*))); KEEP(*(SORT(._device.static.*_??_*))); _device_list_end = .; } > SRAM
 initlevel_error :
 {
  KEEP(*(SORT(.z_init_[_A-Z0-9]*)))
 }
 ASSERT(SIZEOF(initlevel_error) == 0, "Undefined initialization levels used.")
 app_shmem_regions :
 {
  __app_shmem_regions_start = .;
  KEEP(*(SORT(.app_regions.*)));
  __app_shmem_regions_end = .;
 } > SRAM
 k_p4wq_initparam_area : SUBALIGN(4) { _k_p4wq_initparam_list_start = .; KEEP(*(SORT_BY_NAME(._k_p4wq_initparam.static.*))); _k_p4wq_initparam_list_end = .; } > SRAM
 _static_thread_data_area : SUBALIGN(4) { __static_thread_data_list_start = .; KEEP(*(SORT_BY_NAME(.__static_thread_data.static.*))); __static_thread_data_list_end = .; } > SRAM
 device_deps :
 {
__device_deps_start = .;
KEEP(*(SORT(.__device_deps_pass2*)));
__device_deps_end = .;
 } > SRAM
ztest :
{
 _ztest_expected_result_entry_list_start = .; KEEP(*(SORT_BY_NAME(._ztest_expected_result_entry.static.*))); _ztest_expected_result_entry_list_end = .;
 _ztest_suite_node_list_start = .; KEEP(*(SORT_BY_NAME(._ztest_suite_node.static.*))); _ztest_suite_node_list_end = .;
 _ztest_unit_test_list_start = .; KEEP(*(SORT_BY_NAME(._ztest_unit_test.static.*))); _ztest_unit_test_list_end = .;
 _ztest_test_rule_list_start = .; KEEP(*(SORT_BY_NAME(._ztest_test_rule.static.*))); _ztest_test_rule_list_end = .;
} > SRAM
 ctors :
 {
  . = ALIGN(4);
  __ZEPHYR_CTOR_LIST__ = .;
  LONG((__ZEPHYR_CTOR_END__ - __ZEPHYR_CTOR_LIST__) / 4 - 2)
  KEEP(*(SORT_BY_NAME(".ctors*")))
  __CTOR_LIST__ = .;
  LONG(0)
  __ZEPHYR_CTOR_END__ = .;
  LONG(0)
  __CTOR_END__ = .;
 } > SRAM
 init_array :
 {
  . = ALIGN(4);
  __init_array_start = .;
  __init_array_end = .;
  __zephyr_init_array_start = .;
  KEEP(*(SORT_BY_NAME(".init_array*")))
  __zephyr_init_array_end = .;
 } > SRAM
 bt_l2cap_fixed_chan_area : SUBALIGN(4) { _bt_l2cap_fixed_chan_list_start = .; KEEP(*(SORT_BY_NAME(._bt_l2cap_fixed_chan.static.*))); _bt_l2cap_fixed_chan_list_end = .; } > SRAM
 bt_gatt_service_static_area : SUBALIGN(4) { _bt_gatt_service_static_list_start = .; KEEP(*(SORT_BY_NAME(._bt_gatt_service_static.static.*))); _bt_gatt_service_static_list_end = .; } > SRAM
 log_strings_area : SUBALIGN(4) { _log_strings_list_start = .; KEEP(*(SORT_BY_NAME(._log_strings.static.*))); _log_strings_list_end = .; } > SRAM
 log_const_area : SUBALIGN(4) { _log_const_list_start = .; KEEP(*(SORT_BY_NAME(._log_const.static.*))); _log_const_list_end = .; } > SRAM
 log_backend_area : SUBALIGN(4) { _log_backend_list_start = .; KEEP(*(SORT_BY_NAME(._log_backend.static.*))); _log_backend_list_end = .; } > SRAM
 log_link_area : SUBALIGN(4) { _log_link_list_start = .; KEEP(*(SORT_BY_NAME(._log_link.static.*))); _log_link_list_end = .; } > SRAM
 tracing_backend_area : SUBALIGN(4) { _tracing_backend_list_start = .; KEEP(*(SORT_BY_NAME(._tracing_backend.static.*))); _tracing_backend_list_end = .; } > SRAM
 zephyr_dbg_info :
 {
  KEEP(*(".dbg_thread_info"));
 } > SRAM
 intc_table_area : SUBALIGN(4) { _intc_table_list_start = .; KEEP(*(SORT_BY_NAME(._intc_table.static.*))); _intc_table_list_end = .; } > SRAM
 symbol_to_keep :
 {
  __symbol_to_keep_start = .;
  KEEP(*(SORT(.symbol_to_keep*)));
  __symbol_to_keep_end = .;
 } > SRAM
 shell_area : SUBALIGN(4) { _shell_list_start = .; KEEP(*(SORT_BY_NAME(._shell.static.*))); _shell_list_end = .; } > SRAM
 shell_root_cmds_area : SUBALIGN(4) { _shell_root_cmds_list_start = .; KEEP(*(SORT_BY_NAME(._shell_root_cmds.static.*))); _shell_root_cmds_list_end = .; } > SRAM
 shell_subcmds_area : SUBALIGN(4) { _shell_subcmds_list_start = .; KEEP(*(SORT_BY_NAME(._shell_subcmds.static.*))); _shell_subcmds_list_end = .; } > SRAM
 shell_dynamic_subcmds_area : SUBALIGN(4) { _shell_dynamic_subcmds_list_start = .; KEEP(*(SORT_BY_NAME(._shell_dynamic_subcmds.static.*))); _shell_dynamic_subcmds_list_end = .; } > SRAM
 cfb_font_area : SUBALIGN(4) { _cfb_font_list_start = .; KEEP(*(SORT_BY_NAME(._cfb_font.static.*))); _cfb_font_list_end = .; } > SRAM
 tdata :
 {
  *(.tdata .tdata.* .gnu.linkonce.td.*);
 } > SRAM
 tbss :
 {
  *(.tbss .tbss.* .gnu.linkonce.tb.* .tcommon);
 } > SRAM
 PROVIDE(__tdata_start = ADDR(tdata));
 PROVIDE(__tdata_align = ALIGNOF(tdata));
 PROVIDE(__tdata_size = (SIZEOF(tdata) + __tdata_align - 1) & ~(__tdata_align - 1));
 PROVIDE(__tdata_end = __tdata_start + __tdata_size);
 PROVIDE(__tbss_align = ALIGNOF(tbss));
 PROVIDE(__tbss_start = ADDR(tbss));
 PROVIDE(__tbss_size = (SIZEOF(tbss) + __tbss_align - 1) & ~(__tbss_align - 1));
 PROVIDE(__tbss_end = __tbss_start + __tbss_size);
 PROVIDE(__tls_start = __tdata_start);
 PROVIDE(__tls_end = __tbss_end);
 PROVIDE(__tls_size = __tbss_end - __tdata_start);
    rodata :
    {
        *(.rodata)
        *(".rodata.*")
        . = ALIGN(4);
        __riscv_firmware_scenario_start = .;
        KEEP(*(SORT_BY_NAME(.riscv_scenario.[0-9].*)))
        . = ALIGN(4);
        __riscv_firmware_scenario_end = .;
        *(.gnu.linkonce.r.*)
        . = ALIGN(4);
    } > SRAM
    __riscv_firmware_scenario_num = (__riscv_firmware_scenario_end - __riscv_firmware_scenario_start)/8;
 .gcc_except_table : ONLY_IF_RO
 {
 *(.gcc_except_table .gcc_except_table.*)
 } > SRAM
    __rodata_region_end = .;
    . = ALIGN(_region_min_align);
    __rom_region_end = .;
   
    /DISCARD/ : {
        *(.got.plt)
        *(.igot.plt)
        *(.got)
        *(.igot)
    }
   
    . = 0x4000000;
    . = ALIGN(_region_min_align);
    _image_ram_start = .;
.ramfunc :
{
 . = ALIGN(_region_min_align);
 __ramfunc_start = .;
 *(.ramfunc)
 *(".ramfunc.*")
 . = ALIGN(_region_min_align);
 __ramfunc_end = .;
} > SRAM
__ramfunc_size = __ramfunc_end - __ramfunc_start;
__ramfunc_load_start = LOADADDR(.ramfunc);
   
    datas :
    {
        __data_region_start = .;
        __data_start = .;
        *(.data)
        *(".data.*")
        *(".kernel.*")
        *(.cached_sysram_rwdata*)
. = ALIGN(4);
_tcm_rwdata_start = .;
*(.tcm_rwdata.*)
*(.tcm_rwdata_none_retention*)
. = ALIGN(4);
_tcm_rwdata_end = .;
        __data_end = .;
    } > SRAM
    __data_size = __data_end - __data_start;
    __data_load_start = LOADADDR(datas);
    __data_region_load_start = LOADADDR(datas);
        device_states :
        {
                __device_states_start = .;
  KEEP(*(".z_devstate"));
  KEEP(*(".z_devstate.*"));
                __device_states_end = .;
        } > SRAM
 log_mpsc_pbuf_area : SUBALIGN(4) { _log_mpsc_pbuf_list_start = .; *(SORT_BY_NAME(._log_mpsc_pbuf.static.*)); _log_mpsc_pbuf_list_end = .; } > SRAM
 log_msg_ptr_area : SUBALIGN(4) { _log_msg_ptr_list_start = .; KEEP(*(SORT_BY_NAME(._log_msg_ptr.static.*))); _log_msg_ptr_list_end = .; } > SRAM
 log_dynamic_area : SUBALIGN(4) { _log_dynamic_list_start = .; KEEP(*(SORT_BY_NAME(._log_dynamic.static.*))); _log_dynamic_list_end = .; } > SRAM
 k_timer_area : SUBALIGN(4) { _k_timer_list_start = .; *(SORT_BY_NAME(._k_timer.static.*)); _k_timer_list_end = .; } > SRAM
 k_mem_slab_area : SUBALIGN(4) { _k_mem_slab_list_start = .; *(SORT_BY_NAME(._k_mem_slab.static.*)); _k_mem_slab_list_end = .; } > SRAM
 k_heap_area : SUBALIGN(4) { _k_heap_list_start = .; *(SORT_BY_NAME(._k_heap.static.*)); _k_heap_list_end = .; } > SRAM
 k_mutex_area : SUBALIGN(4) { _k_mutex_list_start = .; *(SORT_BY_NAME(._k_mutex.static.*)); _k_mutex_list_end = .; } > SRAM
 k_stack_area : SUBALIGN(4) { _k_stack_list_start = .; *(SORT_BY_NAME(._k_stack.static.*)); _k_stack_list_end = .; } > SRAM
 k_msgq_area : SUBALIGN(4) { _k_msgq_list_start = .; *(SORT_BY_NAME(._k_msgq.static.*)); _k_msgq_list_end = .; } > SRAM
 k_mbox_area : SUBALIGN(4) { _k_mbox_list_start = .; *(SORT_BY_NAME(._k_mbox.static.*)); _k_mbox_list_end = .; } > SRAM
 k_pipe_area : SUBALIGN(4) { _k_pipe_list_start = .; *(SORT_BY_NAME(._k_pipe.static.*)); _k_pipe_list_end = .; } > SRAM
 k_sem_area : SUBALIGN(4) { _k_sem_list_start = .; *(SORT_BY_NAME(._k_sem.static.*)); _k_sem_list_end = .; } > SRAM
 k_event_area : SUBALIGN(4) { _k_event_list_start = .; *(SORT_BY_NAME(._k_event.static.*)); _k_event_list_end = .; } > SRAM
 k_queue_area : SUBALIGN(4) { _k_queue_list_start = .; *(SORT_BY_NAME(._k_queue.static.*)); _k_queue_list_end = .; } > SRAM
 k_fifo_area : SUBALIGN(4) { _k_fifo_list_start = .; *(SORT_BY_NAME(._k_fifo.static.*)); _k_fifo_list_end = .; } > SRAM
 k_lifo_area : SUBALIGN(4) { _k_lifo_list_start = .; *(SORT_BY_NAME(._k_lifo.static.*)); _k_lifo_list_end = .; } > SRAM
 k_condvar_area : SUBALIGN(4) { _k_condvar_list_start = .; *(SORT_BY_NAME(._k_condvar.static.*)); _k_condvar_list_end = .; } > SRAM
 sys_mem_blocks_ptr_area : SUBALIGN(4) { _sys_mem_blocks_ptr_list_start = .; *(SORT_BY_NAME(._sys_mem_blocks_ptr.static.*)); _sys_mem_blocks_ptr_list_end = .; } > SRAM
 net_buf_pool_area : SUBALIGN(4) { _net_buf_pool_list_start = .; KEEP(*(SORT_BY_NAME(._net_buf_pool.static.*))); _net_buf_pool_list_end = .; } > SRAM
 .gcc_except_table : ONLY_IF_RW
 {
 *(.gcc_except_table .gcc_except_table.*)
 } > SRAM
    __data_region_end = .;
    _FIRMWARE_SIZE = __data_region_end - __rom_region_start;
    ASSERT(0x18000 >= _FIRMWARE_SIZE, "Error: firmware size exceeds the expected CONFIG_FLASH_LOAD_SIZE")
    bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start = .;
        __kernel_ram_start = .;
        *(.bss)
        *(".bss.*")
        *(COMMON)
        *(".kernel_bss.*")
        *(.cached_sysram_zidata*)
. = ALIGN(4);
_tcm_zi_start = .;
*(.tcm_zidata.*)
*(.tcm_zidata_none_retention*)
. = ALIGN(4);
_tcm_zi_end = .;
        __bss_end = ALIGN(4);
    } > SRAM
    noinit (NOLOAD) :
    {
        __no_init_start = .;
        *(.noinit)
        *(".noinit.*")
        *(".kernel_noinit.*")
        __no_init_end = .;
    } > SRAM
    _image_ram_end = .;
    _end = .;
_bt_sysram_rw_data_load = LOADADDR(.bt_sysram_rw_data);
.bt_sysram_rw_data :ALIGN(4)
{
    . = ALIGN(4);
    _bt_sysram_rw_data_start = .;
    *(.share_rwbt*)
    . = ALIGN(4);
    _bt_sysram_rw_data_end = .;
}> SRAM_BT AT> SRAM
.bt_sysram_zi_data (NOLOAD) :ALIGN(4)
{
    . = ALIGN(4);
    _bt_sysram_zi_data_start = .;
    *(.share_zibt*)
    . = ALIGN(4);
    _bt_sysram_zi_data_end = .;
}> SRAM_BT
_bt_sysram_end = _bt_sysram_zi_data_end;
    __kernel_ram_end = 0x4000000 + (384 * 1K - 0 * 1K);
    __kernel_ram_size = __kernel_ram_end - __kernel_ram_start;
    __padding_after_retention_text_start = .;
    __padding_after_retention_text_end = .;
    __padding_before_tcm_text_start = .;
    __padding_before_tcm_text_end = .;
    _tcm_rw_data_non_retention_start = .;
    _tcm_rw_data_non_retention_end = .;
    _tcm_zi_data_non_retention_start = .;
    _tcm_zi_data_non_retention_end = .;
   
 .stab 0 : { *(.stab) }
 .stabstr 0 : { *(.stabstr) }
 .stab.excl 0 : { *(.stab.excl) }
 .stab.exclstr 0 : { *(.stab.exclstr) }
 .stab.index 0 : { *(.stab.index) }
 .stab.indexstr 0 : { *(.stab.indexstr) }
 .gnu.build.attributes 0 : { *(.gnu.build.attributes .gnu.build.attributes.*) }
 .comment 0 : { *(.comment) }
 .debug 0 : { *(.debug) }
 .line 0 : { *(.line) }
 .debug_srcinfo 0 : { *(.debug_srcinfo) }
 .debug_sfnames 0 : { *(.debug_sfnames) }
 .debug_aranges 0 : { *(.debug_aranges) }
 .debug_pubnames 0 : { *(.debug_pubnames) }
 .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
 .debug_abbrev 0 : { *(.debug_abbrev) }
 .debug_line 0 : { *(.debug_line .debug_line.* .debug_line_end ) }
 .debug_frame 0 : { *(.debug_frame) }
 .debug_str 0 : { *(.debug_str) }
 .debug_loc 0 : { *(.debug_loc) }
 .debug_macinfo 0 : { *(.debug_macinfo) }
 .debug_weaknames 0 : { *(.debug_weaknames) }
 .debug_funcnames 0 : { *(.debug_funcnames) }
 .debug_typenames 0 : { *(.debug_typenames) }
 .debug_varnames 0 : { *(.debug_varnames) }
 .debug_pubtypes 0 : { *(.debug_pubtypes) }
 .debug_ranges 0 : { *(.debug_ranges) }
 .debug_addr 0 : { *(.debug_addr) }
 .debug_line_str 0 : { *(.debug_line_str) }
 .debug_loclists 0 : { *(.debug_loclists) }
 .debug_macro 0 : { *(.debug_macro) }
 .debug_names 0 : { *(.debug_names) }
 .debug_rnglists 0 : { *(.debug_rnglists) }
 .debug_str_offsets 0 : { *(.debug_str_offsets) }
 .debug_sup 0 : { *(.debug_sup) }
    /DISCARD/ : { *(.note.GNU-stack) }
    .ARM.attributes 0 :
    {
        KEEP(*(.ARM.attributes))
        KEEP(*(.gnu.attributes))
    }
   
}
