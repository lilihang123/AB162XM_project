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
)