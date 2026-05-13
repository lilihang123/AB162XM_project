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
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_sof_routine)
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

    *lib*usb.a:air_usb_hid.c.obj(.text.air_usb_hid_register_set_report_cb)
    *lib*usb.a:air_usb_hid.c.obj(.text.air_usb_hid_register_get_report_cb)
    *lib*usb.a:air_usb_hid.c.obj(.text.register_cb*)
    *lib*mux.a:mux_usb.c.obj(.text.mux_usb_evt_cb)
    *lib*race.a:race_port_usb.c.obj(.text.race_mux_usb_callback)

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
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_read)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_write)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_read_wait)
    *lib*.a:usb_dc_airoha.c.obj(.text.usb_dc_ep_read_continue)
    *lib*.a:usb_dc_airoha.c.obj(.text.get_ep_ctx)

    *libkernel.a:sched.c.obj(.text.z_impl_k_yield)
    *libkernel.a:sched.c.obj(.text.z_impl_k_usleep)
    *libkernel.a:thread.c.obj(.text.k_is_in_isr)


    *lib*.a:air_daemon_work_q.c.obj(.text.air_daemon_wq_work_submit)
    *libkernel.a:work.c.obj(.text.k_work_submit_to_queue)
    *libkernel.a:work.c.obj(.text.z_work_submit_to_queue)
    *libkernel.a:work.c.obj(.text.submit_to_queue_locked)
    *libkernel.a:work.c.obj(.text.notify_queue_locked*)
    *libkernel.a:work.c.obj(.text.k_work_submit*) /*hcla*/
    *libkernel.a:sched.c.obj(.text.z_sched_wake)

    *lib*usb.a:air_usb_hid.c.obj(.text.air_usb_hid_evt_cb)
    *lib*usb.a:air_usb_hid.c.obj(.rodata.airoha_usb_hid_ops)

    *lib*hid.a:core.c.obj(.text.hid_int_in)
    *lib*hid.a:core.c.obj(.text.hid_int_out)
    *lib*hid.a:core.c.obj(.text.hid_int_ep_read)
    *libzephyr.a:usb_device.c.obj(.text.usb_read)
    *lib*hid.a:custom_protocol.c.obj(.text.epio_usb_hid_rx_cb) /*hid_int_ep_read*/

    *libzephyr*.a:usb_descriptor.c.obj(.text.usb_get_dev_data_by_ep) /*hid_int_in*/
    *lib*hid.a:hid_scenario_USB_mode.c.obj(.text.usb_tx_done) /*air_usb_hid_int_in_ready_callback*/
    *lib*hid.a:hid_scenario_USB_mode.c.obj(.text.usb_tx_free) /*air_usb_hid_int_in_ready_callback*/

    /* mouse senser */
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

    /* CCNI flash code & data */
    *lib*.a:hal_ccni.c.obj(.text.ccni_irq_handler)
    *lib*.a:hal_ccni.c.obj(.text.hal_ccni_mask_event)
    *lib*.a:hal_ccni.c.obj(.text.hal_ccni_unmask_event)
    *lib*.a:hal_ccni.c.obj(.text.hal_ccni_clear_event)
    *lib*.a:hal_ccni.c.obj(.text.ccni_write_register)
    *lib*.a:hal_ccni_config.c.obj(.rodata.ccni_callback)
    *libarch*.a:exc_exit.c.obj(.text._HandlerModeExit)
    *lib*common.a:air_mpu_init.c.obj(.rodata)
    *lib*hid.a:hid_common.c.obj(.text.hid_common_clear_hid_exp_flag) /*ccni_irq_handler*/
    *lib*hid.a:hid_common.c.obj(.text.hid_common_set_hid_exp_flag) /*ccni_irq_handler*/
    *lib*hid.a:hid_common.c.obj(.text.hid_common_set_app_para)

    *libzephyr.a:tracing_user.c.obj(.text.sys_trace_thread_sched_ready)
    *libkernel.a:sched.c.obj(.text.z_reset_time_slice)
#if 0
    /* sqrt func in math.h*/
    *lib*cortex_m.a:__aeabi_read_tp.S.obj(.TEXT.__aeabi_read_tp)
    *lib*newlib.a:libc-hooks.c.obj(.text.__errno)
    *lib*libgcc.a:_arm_addsubdf3.o(.text)
    *lib*libgcc.a:_arm_fixdfsi.o(.text)
    *lib*libgcc.a:_arm_muldivdf3.o(.text)
    *lib*libgcc.a:_arm_cmpdf2.o(.text)
    *lib*libm_nano.a:lib_a-w_sqrt.o(.text.sqrt)
    *lib*libm_nano.a:lib_a-e_sqrt.o(.text.__ieee754_sqrt)
    *lib*libgcc.a:_arm_unorddf2.o(.text)
    /*double convert to unsigned int*/
    *lib*libgcc.a:_arm_fixunsdfsi.o(.text)
#endif

#ifdef CONFIG_AIR_BYPASS_SYSLOG_WITH_LOG_FLOW_ENABLE
    /*The following symbol for disable all log but run log flow feature*/
    *lib*exception_handler.a:exception_port.c.obj(.text.exception_get_disable_all_log_flag)
    *lib*mux.a:mux_port_device.c.obj(.text.mux_common_device_get_hw_rptr)
    *lib*mux.a:mux_port_device.c.obj(.text.mux_common_device_get_hw_wptr)
    *lib*mux.a:mux_port_device.c.obj(.text.mux_common_device_set_rx_hw_rptr)
    *lib*mux.a:mux_port_device.c.obj(.text.mux_common_device_set_tx_hw_wptr)
    *lib*mux.a:mux_port_device.c.obj(.text.mux_common_device_set_tx_hw_rptr_internal_use)
    *lib*mux.a:mux_port_device.c.obj(.text.mux_common_device_r_w_point_init)
    *lib*mux.a:mux_port_device.c.obj(.text.mux_common_device_buf_clear)
    *lib*mux.a:mux_port_device.c.obj(.text.mux_common_device_buf_is_empty)
#endif

#ifdef CONFIG_AIR_HID_DEBUG_PIN
    *lib*ab162x.a:hal_gpio.c.obj(.text.hal_gpio_set_output)
#endif

#endif
