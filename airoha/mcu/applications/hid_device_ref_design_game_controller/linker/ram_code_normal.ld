/* according to the linker script format, place some code in RAM */
/*
    example:
        // place all the code sections in the OBJECT files
        // containing mem*.o in the LIBRARY files matching
        // libc*.a into RAM for execution
        *libc*.a:*mem*.c.o(.text*)

        // place all code sections in OBJECT files matching
        // swap_helper.S.obj into RAM for execution
        *swap_helper.S.obj(.text*)
 */

*lib..__airoha__mcu__subsys__airoha__usb.a:air_usb_hid.c.obj(
    .text.air_usb_hid_find_device
    .text.air_usb_hid_find_first_device_by_report
    .text.air_usb_hid_tx
    .text.air_usb_xinput_tx
    .text.find_cb_hdlr*
    .text.air_usb_hid_int_in_ready_callback
    .text.air_usb_hid_int_out_ready_callback
    .text.air_usb_hid_on_idle_callback
)

*lib..__airoha__mcu__drivers__ab162x__usb__device.a:usb_dc_airoha.c.obj(
    .text.usb_dc_ep_write
)

*lib..__airoha__mcu__modules__hal__airoha__ab162x.a:hal_usb.c.obj(
    .text.usb_ep_check
    .text.usb_ep_dma_running_check*
    .text.usb_hw_epfifowrite
    .text.hal_usb_set_endpoint_tx_ready_toggle
    .text.hal_usb_write_endpoint_fifo
)

*libzephyr.a:usb_device.c.obj(
    .text.usb_write
)

*libsubsys__usb__device__class__hid.a:core.c.obj(
    .text.hid_int_ep_write
    .text.hid_sof_handler
    .text.hid_clear_idle_ctx
)

#ifdef CONFIG_AIR_BYPASS_FLASH_RETURN_READY_ENABLE
    *libc_nano.a:*.o(.text*)
    /* *libpka*.a:LC_*.obj(.text.*)
    *libpka*.a:bt_os_manager*.obj(.text.*)
    *libpka*.a:bt_memory*.obj(.text.*)
    *libpka_zephyrle_asic.a:LC_LE_CS_Pkt.c.obj(.rodata.NAP_CFG_TAB)
    *libpka_zephyrle_asic.a:LC_LE_CS_DcocCal.c.obj(.rodata.g_CsDcocCalTab)
    *libpka*.a:bt_pka_memory*.obj(.text.pka_heap_monitor_by_source)
    *lib*pka.a:pka_porting_layer*.obj(.text.pka_hal_gpt_delay_us) */
    *libkernel.a:thread*.obj(.text.k_thread_name_get)
    *libkernel.a:timer*.obj(.text.k_timer_init)
    *:hal_usb.c.obj(.text.*)
    *:hal_usb_phy.c.obj(.text.*)
    *lib*.a:exception_handler.c.obj(.text.platform_assert)
    *lib*.a:exception_port.c.obj(.text.exception_core_status_read)
    *lib*.a:mux.c.obj(.text.mux_query_user_name)
    *lib*.a:relay_client.c.obj(.rodata.bt_relay_mux_init*)
    *lib*.a:race_xport.c.obj(.rodata.race_init.*)
    *lib*.a:air_logging.c.obj(.rodata*)
    *lib*.a:mux_port.c.obj(.rodata.g_mux_device_ops_array)
    *lib*.a:hal_uart.c.obj(.rodata.uart_port_to_dma_map)
    *lib*.a:hal_pdma_internal.c.obj(.rodata.g_vdma_regbase_table)
    *lib*.a:hal_pdma_internal.c.obj(.text.vdma_set_sw_move_byte)
    *lib*.a:hal_clock.c.obj(.text.hal_clock_is_enabled*)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_suspend_routine)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_reset_routine)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_resume_routine)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_sof_routine)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_ep0_routine)
    *lib*.a:usb_dc_airoha.c.obj(.text.epi_cb)
    *lib*.a:usb_dc_airoha.c.obj(.text.epi_*_cb)
    *lib*.a:usb_dc_airoha.c.obj(.text.epo_cb)
    *lib*.a:usb_dc_airoha.c.obj(.text.epo_*_cb)
    *lib*.a:usb_device.c.obj(.text.forward_status_cb)
    *lib*.a:syslog_port.c.obj(.text.syslog_query_thread_id)
    *lib*.a:air_tracing.c.obj(.text.sys_trace_query_thread_id)
    *lib*hid.a:core.c.obj(.text.hid_status_cb)
    *lib*.a:usb_descriptor.c.obj(.text.usb_get_dev_data_by_cfg)
    _ram_device_list_start = .;
    *lib*hid.a:core.c.obj(._device*)
    _ram_device_list_end = .;
    *lib*usb.a:air_usb.c.obj(.text.air_usb_dc_status_cb)
    *lib*usb.a:air_usb.c.obj(.text.air_usb_execute_cb)
    *lib*usb.a:air_usb.c.obj(.text.air_usb_get_user_name)
    *lib*usb.a:air_usb.c.obj(.text.air_usb_check_user_id)
    *lib*usb.a:air_usb.c.obj(.text.air_usb_dc_pulg_in_cb)
    *lib*usb.a:air_usb.c.obj(.text.air_usb_dc_pulg_out_cb)
    *lib*usb.a:air_usb_hid.c.obj(.text.air_usb_hid_register_set_report_cb)
    *lib*usb.a:air_usb_hid.c.obj(.text.air_usb_hid_register_get_report_cb)
    *lib*usb.a:air_usb_hid.c.obj(.text.register_cb*)
    *lib*mux.a:mux_usb.c.obj(.text.mux_usb_evt_cb)
    *lib*race.a:race_port_usb.c.obj(.text.race_mux_usb_callback)
    *lib*hid.a:hid_scenario_USB_mode.c.obj(.text.hid_usb_evt_cb)
    *libkernel.a:timer*.obj(.text.z_impl_k_timer_start) /*hid_usb_evt_cb*/
    *libkernel.a:timer*.obj(.text.z_impl_k_timer_stop) /*hid_usb_evt_cb*/
    *libkernel.a:timeout*.obj(.text.z_timeout_remaining) /*hid_usb_evt_cb*/
    *libkernel.a:timeout*.obj(.text.elapsed) /*z_timeout_remaining*/
    *libkernel.a:timeout*.obj(.text.z_abort_timeout) /*z_impl_k_timer_start*/
    *libkernel.a:timeout*.obj(.text.remove_timeout) /*z_abort_timeout*/
    *libkernel.a:timeout*.obj(.text.z_add_timeout) /*z_impl_k_timer_start*/
    *libkernel.a:timeout*.obj(.text.timeout_rem) /*z_timeout_remaining*/
    *libkernel.a:timeout*.obj(.text.next_timeout)
    *lib*.a:ost_airoha*.obj(.text.sys_clock_set_timeout) /*z_add_timeout*/
    *lib*.a:hal_sleep_manager.c.obj(.text.hal_sleep_manager_is_enter_tickless_sleep) /* sys_clock_set_timeout */
    *lib*.a:hal_rtc.c.obj(.text.hal_rtc_set_alarm_ms) /* sys_clock_set_timeout */
    *lib*.a:hal_os_timer.c.obj(.text.hal_os_timer_stop) /* sys_clock_set_timeout */
    *lib*.a:hal_os_timer.c.obj(.text.hal_os_timer_start) /*sys_clock_set_timeout*/
    *lib*.a:hal_nvic.c.obj(.text.hal_nvic_clear_pending_irq) /* hal_os_timer_stop */
    *lib*.a:hal_nvic.c.obj(.text.hal_nvic_set_pending_irq) /* usb_hisr */
    *lib*.a:ost_airoha.c.obj(.text.sys_clock_elapsed) /* elapsed */
    *lib*.a:hal_sleep_manager_internal.c.obj(.text.sleep_management_check_handle_status) /* hal_usb_unlock_sleep */
    *libkernel.a:spinlock_validate*.obj(.text.z_spin_lock_valid)
    *libkernel.a:spinlock_validate*.obj(.text.z_spin_lock_set_owner)
    *libkernel.a:spinlock_validate*.obj(.text.z_spin_unlock_valid)
    *libkernel.a:sched*.obj(.text.z_impl_k_sched_current_thread_query)
    *libkernel.a:sched*.obj(.text.z_unpend1_no_timeout) /*z_impl_k_timer_stop*/
    *libkernel.a:sched*.obj(.text.unpend_thread_no_timeout) /*z_unpend1_no_timeout*/
    *libkernel.a:sched*.obj(.text.z_ready_thread) /*z_impl_k_timer_stop*/
    *libkernel.a:sched*.obj(.text.ready_thread) /*z_impl_k_timer_stop*/
    *libzephyr*.a:tracing_user*.obj(.text.sys_trace_thread_sched_ready_user) /*ready_thread*/
    *libkernel.a:sched*.obj(.text.z_reschedule_irqlock) /*z_impl_k_timer_stop*/
    *libarch*.a:swap*.obj(.text.arch_swap) /*z_reschedule_irqlock*/

    *libapp.a:app_usb_port.c.obj(.text.app_usb_port__hid_event_handler) /*air_usb_execute_cb*/
    *libapp.a:app_usb_port.c.obj(.text.app_usb_port__start_timer) /*app_usb_port__hid_event_handler*/
    *libapp.a:app_usb_port.c.obj(.text.app_usb_port__check_usb_configured_status) /*app_usb_port__hid_event_handler*/
    *libapp.a:app_usb_port.c.obj(.text.hid_scenario_usb_for_applaciton) /*app_usb_port__hid_event_handler*/
    *libapp.a:app_usb_port.c.obj(.text.app_usb_port__change_plugged_status)
    *libapp.a:app_usb_port.c.obj(.text.create_evt_usb_status)
    *lib*usb.a:air_usb.c.obj(.text.air_usb_is_vbus_ready) /*hid_scenario_usb_for_applaciton*/
    *lib*hid.a:hid_scenario_service.c.obj(.text.hid_scenario_send_state_update_notification) /*hid_scenario_usb_for_applaciton*/
    *lib*hid.a:hid_scenario_service.c.obj(.text.hid_scenario_send_notification) /*hid_scenario_usb_for_applaciton*/
    *lib*hid.a:hid_scenario_report_rate.c.obj(.text.hid_scenario_read_report_rate) /*hid_scenario_usb_for_applaciton*/
    *lib*usb.a:air_usb.c.obj(.text.air_usb_enable) /*hid_scenario_usb_for_applaciton*/
    *lib*usb.a:air_usb.c.obj(.text.air_usb_disable) /*hid_scenario_usb_for_applaciton*/
    *libzephyr*.a:usb_device*.obj(.text.usb_disable) /*air_usb_disable*/
    *libzephyr*.a:usb_device*.obj(.text.usb_enable) /*air_usb_enable*/
    *libkernel.a:mutex*.obj(.text.z_impl_k_mutex_lock) /*usb_enable*/
    *libkernel.a:mutex*.obj(.text.z_impl_k_mutex_unlock) /*usb_enable*/
    *libkernel.a:mutex*.obj(.text.adjust_owner_prio)
    *libkernel.a:sched*.obj(.text.z_thread_prio_set)
    *libzephyr*.a:tracing_user*.obj(.text.sys_trace_thread_sched_priority_set) /*z_thread_prio_set*/
    *libkernel.a:sched*.obj(.text.sys_dlist_remove)
    *libkernel.a:sched*.obj(.text.update_cache)
    *libkernel.a:timeslicing.c.obj(.text.z_reset_time_slice) /*update_cache*/
    *libkernel.a:timeslicing.c.obj(.text.thread_is_sliceable) /*z_reset_time_slice*/
    *libkernel.a:sched*.obj(.text.z_pend_curr)
    *libkernel.a:sched*.obj(.text.add_to_waitq_locked)
    *libzephyr*.a:tracing_user*.obj(.text.sys_trace_thread_pend)
    *libzephyr*.a:tracing_user*.obj(.text.sys_trace_thread_pend_user)
    *libkernel.a:sched*.obj(.text.unready_thread)
    *libkernel.a:sched*.obj(.text.z_reschedule)
    *libzephyr*.a:usb_device*.obj(.text.usb_handle_*)
    *libzephyr*.a:usb_device*.obj(.text.class_handler)
    *libzephyr*.a:usb_device*.obj(.text.vendor_handler)
    *libzephyr*.a:usb_device*.obj(.text.custom_handler)
    *libzephyr*.a:usb_device*.obj(.text.usb_dc_ep_set_stall)
    *libzephyr*.a:usb_device*.obj(.text.usb_data_to_host)
    *libzephyr*.a:usb_device*.obj(.text.usb_reset_alt_setting)
    *libzephyr*.a:usb_device*.obj(.text.set_endpoint)
    *libzephyr*.a:usb_device*.obj(.text.reset_endpoint*)
    *libzephyr*.a:usb_device*.obj(.text.is_ep_valid)
    *libzephyr*.a:usb_device*.obj(.text.usb_halt_endpoint_req*)
    *libzephyr*.a:usb_device*.obj(.text.get_ep_bm_from_addr)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_read)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_write)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_read_wait)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_read_continue)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_set_address)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_is_stalled)
    *lib*.a:usb_dc_airoha.c.obj(.text.get_ep_ctx)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_configure)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_enable)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_disable)

    *lib*hid.a:core.c.obj(.text.hid_custom_handle_req) /*hid_scenario_usb_for_applaciton*/
    *libzephyr*.a:usb_descriptor.c.obj(.text.usb_get_dev_data_by_iface)
    *libkernel.a:sched.c.obj(.text.z_impl_k_yield)
    *libkernel.a:sched.c.obj(.text.z_impl_k_usleep)
    *libkernel.a:thread.c.obj(.text.k_is_in_isr)
    *libapp.a:app_state.c.obj(.text.app_state_current_state) /*app_usb_port__hid_event_handler*/
    *libapp.a:app_usb_port.c.obj(.text.k_uptime_get_32) /*app_usb_port__hid_event_handler*/
    *libkernel.a:timeout*.obj(.text.sys_clock_tick_get)
    *libkernel.a:timeout*.obj(.text.z_impl_k_uptime_ticks)
    *libkernel.a:timeout*.obj(.text.sys_timepoint_calc)
    *libkernel.a:timeout*.obj(.text.sys_timepoint_timeout)

    *lib*.a:air_allocation_zephyr.c.obj(.text.__wrap_k_malloc)
    *lib*.a:air_allocation_zephyr.c.obj(.text.calc_heap_info_by_buffer_ptr)
    *lib*.a:air_allocation_zephyr.c.obj(.text.application_alloc_failed_hook)
    *libkernel.a:mempool.c.obj(.text.k_malloc)
    *libkernel.a:mempool.c.obj(.text.k_aligned_alloc)
    *libkernel.a:mempool.c.obj(.text.z_heap_aligned_alloc)
    *libkernel.a:kheap.c.obj(.text.k_heap_aligned_alloc)
    *libzephyr*.a:heap.c.obj(.text.__wrap_k_malloc)
    *libzephyr*.a:heap.c.obj(.text.sys_heap_aligned_alloc)
    *libzephyr*.a:heap.c.obj(.text.sys_heap_alloc)
    *libzephyr*.a:heap.c.obj(.text.bytes_to_chunksz*)
    *libzephyr*.a:heap.c.obj(.text.alloc_chunk)
    *libzephyr*.a:heap.c.obj(.text.bucket_idx*)
    *libzephyr*.a:heap.c.obj(.text.chunk_size)
    *libzephyr*.a:heap.c.obj(.text.free_list_remove_bidx)
    *libzephyr*.a:heap.c.obj(.text.chunk_field)
    *libzephyr*.a:heap.c.obj(.text.split_chunks)
    *libzephyr*.a:heap.c.obj(.text.free_list_add)
    *libzephyr*.a:heap.c.obj(.text.set_chunk_used)
    *libzephyr*.a:heap.c.obj(.text.mem_to_chunkid)
    *libzephyr*.a:heap.c.obj(.text.set_chunk_size)
    *libzephyr*.a:heap.c.obj(.text.chunk_set)
    *libzephyr*.a:heap.c.obj(.text.merge_chunks)
    *libzephyr*.a:heap.c.obj(.text.free_list_remove)
    *libzephyr*.a:heap.c.obj(.text.free_chunk)

    *libapp.a:app_usb_port.c.obj(.text.app_usb_port__usb_enable_handler) /*app_usb_port__check_usb_port_status*/
    *libapp.a:app_usb_port.c.obj(.text.app_usb_port__get_vbus_ready) /*app_usb_port__check_usb_port_status*/
    *lib*.a:af_framework.c.obj(.text.af_evt_submit)
    *lib*.a:af_framework.c.obj(.text.af_evt_manager_alloc)
    *libapp.a:app_state.c.obj(.text.app_state_check) /*app_usb_port__usb_enable_handler*/

    *lib*hid.a:hid_scenario_USB_mode.c.obj(.text.hid_scenario_usb_for_applaciton) /*app_usb_port__get_vbus_ready*/
    *lib*.a:air_daemon_work_q.c.obj(.text.air_daemon_wq_work_submit)
    *libkernel.a:work.c.obj(.text.k_work_submit_to_queue)
    *libkernel.a:work.c.obj(.text.z_work_submit_to_queue)
    *libkernel.a:work.c.obj(.text.submit_to_queue_locked)
    *libkernel.a:work.c.obj(.text.notify_queue_locked*)
    *libkernel.a:work.c.obj(.text.k_work_submit*) /*hcla*/
    *libkernel.a:sched.c.obj(.text.z_sched_wake)

    *libapp.a:app_battery.c.obj(.text.app_battery__get_battery_power) /*app_usb_port__change_plugged_status*/

    *lib*usb.a:air_usb_hid.c.obj(.text.air_usb_hid_evt_cb)
    *lib*usb.a:air_usb_hid.c.obj(.rodata.airoha_usb_hid_ops)

    *lib*hid.a:core.c.obj(.text.hid_int_in)
    *lib*hid.a:core.c.obj(.text.hid_int_out)
    *lib*hid.a:core.c.obj(.text.hid_int_ep_read)

    *libzephyr*.a:usb_descriptor.c.obj(.text.usb_get_dev_data_by_ep) /*hid_int_in*/
    *lib*hid.a:hid_scenario_USB_mode.c.obj(.text.usb_tx_done) /*air_usb_hid_int_in_ready_callback*/
    *lib*hid.a:hid_scenario_USB_mode.c.obj(.text.usb_tx_free) /*air_usb_hid_int_in_ready_callback*/
    *lib*mouse_sensor.a:paw*_pixart.c.obj(.rodata.mouse_sensor_driver_api)
    *lib*mouse_sensor.a:paw*_pixart.c.obj(.rodata.paw*_config)
    *lib*mouse_sensor.a:paw*_pixart.c.obj(.text.spi_delay_config)
    *lib*mouse_sensor.a:paw*_pixart.c.obj(._device*)
    *lib*ab162x.a:hal_spi_master.c.obj(.text.hal_spi_master_set_delay_cnt) /*spi_delay_config*/
    *lib*ab162x.a:hal_spi_master.c.obj(.text.hal_spi_master_trigger_start)
    *lib*ab162x.a:hal_spi_master.c.obj(.text.hal_spi_master_send_and_receive_dma_advanced)
    *lib*ab162x.a:hal_spi_master.c.obj(.text.spi_master_config_dma)
    *lib*ab162x.a:hal_spi_master.c.obj(.text.hal_spi_master_restore_address_advanced)
    *lib*ab162x.a:hal_spi_master_internal.c.obj(.text.spi_master_config_transfer)
    *lib*ab162x.a:hal_spi_master_internal.c.obj(.text.spi_master_config_fifo)
    *lib*ab162x.a:hal_spi_master_internal.c.obj(.text.spi_master_set_delay_cnt) /*hal_spi_master_set_delay_cnt*/
    *lib*ab162x.a:hal_spi_master_internal.c.obj(.text.spi_master_ioctl)
    *lib*ab162x.a:hal_spi_master_internal.c.obj(.text.spi_master_set_rwaddr)
    *lib*ab162x.a:hal_spi_master_internal.c.obj(.rodata.g_spi_master_register)
    *lib*ab162x.a:hal_memview.c.obj(.text.hal_memview_mcu_to_infrasys)
    *lib*ab162x.a:hal_memview.c.obj(.text.check_infra_address)

    *libzephyr.a:usb_device.c.obj(.text.usb_read)
    *lib*hid.a:custom_protocol.c.obj(.text.epio_usb_hid_rx_cb) /*hid_int_ep_read*/

    /* CCNI flash code & data */
    *libzephyr.a:hal_ccni.c.obj(.text.ccni_irq_handler)
    *libzephyr.a:hal_ccni.c.obj(.text.hal_ccni_mask_event)
    *libzephyr.a:hal_ccni.c.obj(.text.hal_ccni_unmask_event)
    *libzephyr.a:hal_ccni.c.obj(.text.hal_ccni_clear_event)
    *libzephyr.a:hal_ccni.c.obj(.text.ccni_write_register)
    *libzephyr.a:hal_ccni_config.c.obj(.rodata.ccni_callback)
    *libarch*.a:exc_exit.c.obj(.text._HandlerModeExit)
    *lib*common.a:air_mpu_init.c.obj(.rodata)
    *lib*hid.a:hid_common.c.obj(.text.hid_common_clear_hid_exp_flag) /*ccni_irq_handler*/
    *lib*hid.a:hid_common.c.obj(.text.hid_common_set_hid_exp_flag) /*ccni_irq_handler*/
    *lib*hid.a:hid_common.c.obj(.text.hid_common_set_app_para)

    *libzephyr.a:tracing_user.c.obj(.text.sys_trace_thread_sched_ready)
    *libkernel.a:sched.c.obj(.text.z_reset_time_slice)
#endif
