	.file	"riscv_peripheral_sampling.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_peripheral_sampling.c"
	.section	.text.peripheral_sampling_inactivity_timeout,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_inactivity_timeout
	.hidden	peripheral_sampling_inactivity_timeout
	.type	peripheral_sampling_inactivity_timeout, @function
peripheral_sampling_inactivity_timeout:
.LFB18:
	.file 1 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_peripheral_sampling.c"
	.loc 1 133 1
	.cfi_startproc
.LVL0:
	.loc 1 134 5
	.loc 1 135 5
	.loc 1 133 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 135 12
	li	a5,-127
	.loc 1 138 5
	mv	a0,sp
.LVL1:
	li	a1,2
	.loc 1 133 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 135 12
	sb	a5,0(sp)
	.loc 1 138 5 is_stmt 1
	call	riscv_app_ccin_send
.LVL2:
	.loc 1 139 5
	.loc 1 140 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	.loc 1 139 20
	li	a5,2
	sw	a5,sampling_state,a4
	.loc 1 140 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE18:
	.size	peripheral_sampling_inactivity_timeout, .-peripheral_sampling_inactivity_timeout
	.section	.text.riscv_fake_report_check,"ax",@progbits
	.align	1
	.globl	riscv_fake_report_check
	.hidden	riscv_fake_report_check
	.type	riscv_fake_report_check, @function
riscv_fake_report_check:
.LFB15:
	.loc 1 105 1 is_stmt 1
	.cfi_startproc
	.loc 1 106 5
	.loc 1 105 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 106 34
	call	rv_fake_report__get_state
.LVL3:
	mv	s0,a0
.LVL4:
	.loc 1 107 5 is_stmt 1
	.loc 1 107 28 is_stmt 0
	call	riscv_mouse_keys_is_new_key_pressed
.LVL5:
	.loc 1 109 5 is_stmt 1
	.loc 1 109 8 is_stmt 0
	beq	a0,zero,.L4
	.loc 1 110 9 is_stmt 1
	.loc 1 110 12 is_stmt 0
	beq	s0,zero,.L3
.L6:
	.loc 1 111 13 is_stmt 1
	li	a2,0
	li	a1,0
	li	a0,0
.LVL6:
	call	rv_fake_report_config
.LVL7:
	.loc 1 112 13
	.loc 1 119 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL8:
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 112 13
	tail	riscv_app_ccin_fake_data_disable
.LVL9:
.L4:
	.cfi_restore_state
	.loc 1 115 10 is_stmt 1
	.loc 1 115 13 is_stmt 0
	li	a5,2
	beq	s0,a5,.L6
.L3:
	.loc 1 119 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL10:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE15:
	.size	riscv_fake_report_check, .-riscv_fake_report_check
	.section	.text.peripheral_sampling_state_change_active,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_state_change_active
	.hidden	peripheral_sampling_state_change_active
	.type	peripheral_sampling_state_change_active, @function
peripheral_sampling_state_change_active:
.LFB16:
	.loc 1 123 1 is_stmt 1
	.cfi_startproc
	.loc 1 124 5
	.loc 1 124 20 is_stmt 0
	sw	zero,sampling_state,a5
	.loc 1 125 1
	ret
	.cfi_endproc
.LFE16:
	.size	peripheral_sampling_state_change_active, .-peripheral_sampling_state_change_active
	.section	.text.peripheral_sampling_set_inActivity_timeout,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_set_inActivity_timeout
	.hidden	peripheral_sampling_set_inActivity_timeout
	.type	peripheral_sampling_set_inActivity_timeout, @function
peripheral_sampling_set_inActivity_timeout:
.LFB17:
	.loc 1 128 1 is_stmt 1
	.cfi_startproc
	.loc 1 129 5
	.loc 1 129 38 is_stmt 0
	lw	a5,hid_common
	.loc 1 129 21
	lw	a5,4(a5)
	sw	a5,inActivity_time,a4
	.loc 1 130 1
	ret
	.cfi_endproc
.LFE17:
	.size	peripheral_sampling_set_inActivity_timeout, .-peripheral_sampling_set_inActivity_timeout
	.section	.text.peripheral_sampling_pairing_state_change,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_pairing_state_change
	.hidden	peripheral_sampling_pairing_state_change
	.type	peripheral_sampling_pairing_state_change, @function
peripheral_sampling_pairing_state_change:
.LFB19:
	.loc 1 143 1 is_stmt 1
	.cfi_startproc
	.loc 1 144 5
	.loc 1 144 19 is_stmt 0
	sw	zero,pairing_state,a5
	.loc 1 145 1
	ret
	.cfi_endproc
.LFE19:
	.size	peripheral_sampling_pairing_state_change, .-peripheral_sampling_pairing_state_change
	.section	.text.peripheral_sampling_all_key_release_ccni_send,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_all_key_release_ccni_send
	.hidden	peripheral_sampling_all_key_release_ccni_send
	.type	peripheral_sampling_all_key_release_ccni_send, @function
peripheral_sampling_all_key_release_ccni_send:
.LFB20:
	.loc 1 148 1 is_stmt 1
	.cfi_startproc
	.loc 1 149 5
	.loc 1 150 5
	.loc 1 148 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 150 12
	li	a5,-126
	.loc 1 152 5
	mv	a0,sp
	li	a1,2
	.loc 1 148 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 150 12
	sb	a5,0(sp)
	.loc 1 152 5 is_stmt 1
	call	riscv_app_ccin_send
.LVL11:
	.loc 1 153 5
	.loc 1 156 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	.loc 1 153 19
	li	a5,2
	sw	a5,pairing_state,a4
	.loc 1 156 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE20:
	.size	peripheral_sampling_all_key_release_ccni_send, .-peripheral_sampling_all_key_release_ccni_send
	.section	.text.peripheral_sampling_pairing_check,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_pairing_check
	.hidden	peripheral_sampling_pairing_check
	.type	peripheral_sampling_pairing_check, @function
peripheral_sampling_pairing_check:
.LFB21:
	.loc 1 159 1 is_stmt 1
	.cfi_startproc
	.loc 1 161 5
	.loc 1 159 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 163 5
	lla	s0,pairing_state
	.loc 1 161 21
	call	hid_express_get_hid_flag
.LVL12:
	.loc 1 163 5 is_stmt 1
	lw	a5,0(s0)
	beq	a5,zero,.L17
	li	a4,1
	beq	a5,a4,.L18
.LVL13:
.L16:
	.loc 1 199 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL14:
.L17:
	.cfi_restore_state
	.loc 1 167 13 is_stmt 1
	.loc 1 167 27 is_stmt 0
	li	a5,1
.LVL15:
.L27:
	.loc 1 177 35
	sw	a5,0(s0)
	j	.L16
.LVL16:
.L18:
	.loc 1 173 13 is_stmt 1
	.loc 1 173 24 is_stmt 0
	andi	a5,a0,92
	.loc 1 173 16
	li	a4,92
	bne	a5,a4,.L20
	.loc 1 174 17 is_stmt 1
.LBB17:
.LBB18:
	.file 2 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.loc 2 270 5
	.loc 2 270 43 is_stmt 0
	lw	a5,pka_share_ptr
.LBE18:
.LBE17:
	.loc 1 174 19 discriminator 1
	lhu	a4,12(a5)
	li	a5,10
	bne	a4,a5,.L16
.LVL17:
.L21:
	.loc 1 176 21 is_stmt 1
	call	peripheral_sampling_all_key_release_ccni_send
.LVL18:
	.loc 1 177 21
	.loc 1 177 35 is_stmt 0
	li	a5,2
	j	.L27
.LVL19:
.L20:
	.loc 1 180 18 is_stmt 1
	.loc 1 180 29 is_stmt 0
	andi	a0,a0,144
.LVL20:
	.loc 1 180 21
	li	a5,144
	bne	a0,a5,.L16
.LBB19:
.LBB20:
	.loc 1 181 17 is_stmt 1
	.loc 1 181 21 is_stmt 0
	call	hid_express_get_get_tx_result
.LVL21:
	.loc 1 181 19 discriminator 1
	bne	a0,zero,.L16
	j	.L21
.LBE20:
.LBE19:
	.cfi_endproc
.LFE21:
	.size	peripheral_sampling_pairing_check, .-peripheral_sampling_pairing_check
	.section	.text.peripheral_sampling_idle_check,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_idle_check
	.hidden	peripheral_sampling_idle_check
	.type	peripheral_sampling_idle_check, @function
peripheral_sampling_idle_check:
.LFB22:
	.loc 1 202 1 is_stmt 1
	.cfi_startproc
.LVL22:
	.loc 1 203 5
	.loc 1 202 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	sw	s0,4(sp)
	sw	s1,0(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 203 8
	bne	a0,zero,.L29
	.loc 1 204 9 is_stmt 1
	.loc 1 204 11 is_stmt 0
	lw	a4,sampling_state
	li	a5,1
	bne	a4,a5,.L30
	.loc 1 206 13 is_stmt 1
	lw	a0,inActivity_gpt_hdl
.LVL23:
	call	hal_gpt_sw_stop_timer_ms
.LVL24:
.L30:
	.loc 1 208 9
	.loc 1 208 28 is_stmt 0
	sw	zero,inactivity_counter,a5
	.loc 1 209 9 is_stmt 1
	.loc 1 209 24 is_stmt 0
	sw	zero,sampling_state,a5
.L28:
	.loc 1 227 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL25:
.L29:
	.cfi_restore_state
	.loc 1 212 9 is_stmt 1
	.loc 1 212 32 is_stmt 0
	lla	a4,inactivity_counter
	lw	a5,0(a4)
	.loc 1 212 12
	li	a3,79
	bgtu	a5,a3,.L32
	.loc 1 213 13 is_stmt 1
	.loc 1 213 31 is_stmt 0
	addi	a5,a5,1
	sw	a5,0(a4)
	j	.L28
.L32:
	.loc 1 215 14 is_stmt 1
	.loc 1 215 33 is_stmt 0
	lla	a5,sampling_state
	.loc 1 215 17
	lw	a4,0(a5)
	bne	a4,zero,.L28
	.loc 1 215 38 discriminator 1
	lla	s1,inActivity_time
	lw	a4,0(s1)
	beq	a4,zero,.L28
.LVL26:
.LBB23:
.LBB24:
	.loc 1 217 13 is_stmt 1
	.loc 1 220 13 is_stmt 0
	lla	s0,inActivity_gpt_hdl
	lw	a0,0(s0)
.LVL27:
	.loc 1 217 28
	li	a4,1
	sw	a4,0(a5)
	.loc 1 220 13 is_stmt 1
	call	hal_gpt_sw_stop_timer_ms
.LVL28:
	.loc 1 221 13
	lw	a0,0(s0)
.LBE24:
.LBE23:
	.loc 1 227 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
.LBB29:
.LBB25:
	.loc 1 221 13
	lw	a1,0(s1)
.LBE25:
.LBE29:
	.loc 1 227 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
.LBB30:
.LBB26:
	.loc 1 221 13
	li	a3,0
.LBE26:
.LBE30:
	.loc 1 227 1
.LBB31:
.LBB27:
	.loc 1 221 13
	lla	a2,peripheral_sampling_inactivity_timeout
.LBE27:
.LBE31:
	.loc 1 227 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
.LBB32:
.LBB28:
	.loc 1 221 13
	tail	hal_gpt_sw_start_timer_ms
.LVL29:
.LBE28:
.LBE32:
	.cfi_endproc
.LFE22:
	.size	peripheral_sampling_idle_check, .-peripheral_sampling_idle_check
	.section	.text.peripheral_sampling__need_early_key_handle_in_wireless_mode,"ax",@progbits
	.align	1
	.globl	peripheral_sampling__need_early_key_handle_in_wireless_mode
	.hidden	peripheral_sampling__need_early_key_handle_in_wireless_mode
	.type	peripheral_sampling__need_early_key_handle_in_wireless_mode, @function
peripheral_sampling__need_early_key_handle_in_wireless_mode:
.LFB23:
	.loc 1 230 1 is_stmt 1
	.cfi_startproc
	.loc 1 231 5
	.loc 1 231 20 is_stmt 0
	lw	a5,riscv_app+20
	.loc 1 231 8
	andi	a3,a5,-65
	li	a4,10
	.loc 1 241 15
	li	a0,1
	.loc 1 231 8
	beq	a3,a4,.L38
	.loc 1 232 29
	andi	a4,a5,16
	.loc 1 232 9
	bne	a4,zero,.L38
	.loc 1 233 9
	addi	a4,a5,-64
	andi	a4,a4,-66
	beq	a4,zero,.L38
	.loc 1 235 9
	addi	a5,a5,-138
	seqz	a0,a5
.L38:
	.loc 1 245 1
	ret
	.cfi_endproc
.LFE23:
	.size	peripheral_sampling__need_early_key_handle_in_wireless_mode, .-peripheral_sampling__need_early_key_handle_in_wireless_mode
	.section	.text.peripheral_sampling_last_handler,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_last_handler
	.hidden	peripheral_sampling_last_handler
	.type	peripheral_sampling_last_handler, @function
peripheral_sampling_last_handler:
.LFB25:
	.loc 1 319 1 is_stmt 1
	.cfi_startproc
	.loc 1 320 5
	.loc 1 319 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 320 5
	call	riscv_wheel_post_process
.LVL30:
	.loc 1 322 5 is_stmt 1
	call	hid_express_get_outgpoig_report_result
.LVL31:
	.loc 1 322 5 is_stmt 0 discriminator 1
	call	peripheral_sampling_idle_check
.LVL32:
	.loc 1 324 5 is_stmt 1
	call	riscv_fake_report_check
.LVL33:
	.loc 1 327 5
	.loc 1 327 23 is_stmt 0
	call	key_remap_get_process_status
.LVL34:
	.loc 1 328 5 is_stmt 1
	.loc 1 329 5
	li	a5,3
	beq	a0,a5,.L43
	bgtu	a0,a5,.L44
	li	a5,1
	beq	a0,a5,.L45
	li	a5,2
	beq	a0,a5,.L46
.LVL35:
.L47:
	.loc 1 352 5
	.loc 1 352 8 is_stmt 0
	mv	a0,sp
	call	key_remap_get_key_status
.LVL36:
	.loc 1 352 7 discriminator 1
	beq	a0,zero,.L49
	.loc 1 354 9 is_stmt 1
	lw	a0,0(sp)
	call	riscv_mouse_key__ccni_send_status
.LVL37:
.L49:
	.loc 1 358 5
	call	riscv_mouse_key_post_process
.LVL38:
	.loc 1 359 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL39:
.L44:
	.cfi_restore_state
	.loc 1 329 5
	li	a5,7
	bne	a0,a5,.L47
	.loc 1 347 13 is_stmt 1
	li	a1,0
	li	a0,10
.LVL40:
	j	.L54
.LVL41:
.L45:
	.loc 1 332 13
	li	a1,0
	li	a0,6
.LVL42:
.L54:
	.loc 1 347 13 is_stmt 0
	call	riscv_app_ccni_key_remap_send
.LVL43:
	.loc 1 348 13 is_stmt 1
	call	key_remap_state_reset
.LVL44:
	.loc 1 349 13
	j	.L47
.LVL45:
.L46:
	.loc 1 337 13
	call	key_remap_get_dpi_attr
.LVL46:
	mv	a1,a0
.L55:
	.loc 1 342 13 is_stmt 0
	li	a0,7
	j	.L54
.LVL47:
.L43:
	.loc 1 342 13 is_stmt 1
	li	a1,2
	j	.L55
	.cfi_endproc
.LFE25:
	.size	peripheral_sampling_last_handler, .-peripheral_sampling_last_handler
	.section	.text.peripheral_sampling_handler,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_handler
	.hidden	peripheral_sampling_handler
	.type	peripheral_sampling_handler, @function
peripheral_sampling_handler:
.LFB24:
	.loc 1 248 1
	.cfi_startproc
.LVL48:
	.loc 1 249 5
	.loc 1 248 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 249 5
	li	a5,2
	.loc 1 248 1
	mv	s0,a1
	.loc 1 249 5
	beq	a0,a5,.L57
	bgtu	a0,a5,.L58
	bne	a0,zero,.L74
	.loc 1 253 13 is_stmt 1
	.loc 1 253 18 is_stmt 0
	call	peripheral_sampling__need_early_key_handle_in_wireless_mode
.LVL49:
	lla	a5,riscv_app
	.loc 1 253 16 discriminator 1
	beq	a0,zero,.L63
	.loc 1 253 80 discriminator 1
	lw	a3,16(a5)
	li	a4,6
	beq	a3,a4,.L64
.L63:
	.loc 1 254 13
	lw	a4,20(a5)
	li	a5,33
	bne	a4,a5,.L56
.L64:
	.loc 1 256 17 is_stmt 1
	.loc 1 316 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL50:
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 256 17
	tail	riscv_mouse_key_early_handle
.LVL51:
.L58:
	.cfi_restore_state
	.loc 1 249 5
	li	a5,3
	beq	a0,a5,.L61
.LVL52:
.L56:
	.loc 1 316 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL53:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL54:
.L74:
	.cfi_restore_state
	.loc 1 264 13 is_stmt 1
	.loc 1 264 27 is_stmt 0
	lw	a5,hid_flags
	andi	a5,a5,512
	.loc 1 264 15
	beq	a5,zero,.L65
	.loc 1 266 17 is_stmt 1
	.loc 1 316 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL55:
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 266 17
	tail	peripheral_sampling_pairing_check
.LVL56:
.L65:
	.cfi_restore_state
	.loc 1 270 17 is_stmt 1
	addi	a1,a1,12
	addi	a0,s0,8
.LVL57:
	call	riscv_motion_sensor_data_get
.LVL58:
	.loc 1 272 17
	.loc 1 272 20 is_stmt 0
	call	peripheral_sampling__need_early_key_handle_in_wireless_mode
.LVL59:
	.loc 1 272 19 discriminator 1
	beq	a0,zero,.L66
	.loc 1 272 82 discriminator 1
	lw	a4,riscv_app+16
	li	a5,6
	beq	a4,a5,.L66
	.loc 1 274 21 is_stmt 1
	call	riscv_mouse_key_early_handle
.LVL60:
.L66:
	.loc 1 278 17
	addi	a0,s0,16
	call	riscv_wheel_get_data
.LVL61:
	.loc 1 280 17
	.loc 1 316 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL62:
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 280 17
	tail	riscv_wheel_trigger_read_process
.LVL63:
.L57:
	.cfi_restore_state
	.loc 1 289 13 is_stmt 1
	.loc 1 289 33 is_stmt 0
	li	a5,1
	sw	a5,0(a1)
	.loc 1 291 13 is_stmt 1
	.loc 1 291 27 is_stmt 0
	lw	a5,hid_flags
	andi	a5,a5,512
	.loc 1 291 15
	bne	a5,zero,.L56
	.loc 1 297 17 is_stmt 1
	.loc 1 316 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL64:
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 297 17
	addi	a0,a1,4
.LVL65:
	.loc 1 316 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 297 17
	tail	riscv_mouse_key_get_key_status
.LVL66:
.L61:
	.cfi_restore_state
	.loc 1 305 13 is_stmt 1
	.loc 1 316 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
.LVL67:
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 305 13
	tail	peripheral_sampling_last_handler
.LVL68:
	.cfi_endproc
.LFE24:
	.size	peripheral_sampling_handler, .-peripheral_sampling_handler
	.section	.text.peripheral_sampling_deinit,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_deinit
	.hidden	peripheral_sampling_deinit
	.type	peripheral_sampling_deinit, @function
peripheral_sampling_deinit:
.LFB27:
	.loc 1 382 1 is_stmt 1
	.cfi_startproc
	.loc 1 384 5
	.loc 1 382 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 384 5
	lla	s0,inActivity_gpt_hdl
	lw	a0,0(s0)
	.loc 1 382 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 384 5
	call	hal_gpt_sw_stop_timer_ms
.LVL69:
	.loc 1 385 5 is_stmt 1
	lw	a0,0(s0)
	call	hal_gpt_sw_free_timer
.LVL70:
	.loc 1 386 5
	.loc 1 387 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 386 5
	tail	hid_express_deinit
.LVL71:
	.cfi_endproc
.LFE27:
	.size	peripheral_sampling_deinit, .-peripheral_sampling_deinit
	.section	.text.peripheral_sampling_debug_print,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_debug_print
	.hidden	peripheral_sampling_debug_print
	.type	peripheral_sampling_debug_print, @function
peripheral_sampling_debug_print:
.LFB29:
	.loc 1 440 1 is_stmt 1
	.cfi_startproc
	.loc 1 441 5
	.loc 1 440 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 441 5
	call	riscv_mouse_key_debug_print
.LVL72:
	.loc 1 442 5 is_stmt 1
	.loc 1 443 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 442 5
	tail	riscv_wheel_debug_print
.LVL73:
	.cfi_endproc
.LFE29:
	.size	peripheral_sampling_debug_print, .-peripheral_sampling_debug_print
	.section	.text.peripheral_sampling_common_para_update,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_common_para_update
	.hidden	peripheral_sampling_common_para_update
	.type	peripheral_sampling_common_para_update, @function
peripheral_sampling_common_para_update:
.LFB30:
	.loc 1 446 1 is_stmt 1
	.cfi_startproc
	.loc 1 448 5
	.loc 1 446 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 448 26
	lla	s0,riscv_app
	.loc 1 448 38
	lw	a4,hid_common
	.loc 1 449 47
	lbu	a3,57(a4)
	.loc 1 448 46
	lbu	a5,58(a4)
	.loc 1 452 19
	lw	a4,20(s0)
	.loc 1 449 27
	sw	a3,12(s0)
	.loc 1 448 26
	sw	a5,8(s0)
	.loc 1 449 5 is_stmt 1
	.loc 1 450 5
	.loc 1 450 22 is_stmt 0
	sw	a3,16(s0)
	.loc 1 452 5 is_stmt 1
	.loc 1 452 26 is_stmt 0
	andi	a2,a4,32
	.loc 1 452 8
	beq	a2,zero,.L81
	.loc 1 453 9 is_stmt 1
	.loc 1 453 26 is_stmt 0
	sw	a5,16(s0)
.L82:
	.loc 1 462 5 is_stmt 1
.LBB33:
	.loc 1 462 10
	.loc 1 462 65
	.loc 1 462 274
	sw	a3,0(sp)
	lw	a4,16(s0)
	li	a3,3
	lla	a2,msg_id_string.0
	li	a1,1
	lla	a0,log_control_block_riscv_ps
	call	print_module_msgid_log
.LVL74:
.LBE33:
	.loc 1 462 8 discriminator 1
	.loc 1 469 5
	lw	a0,16(s0)
	call	hid_express_set_report_rate_idx
.LVL75:
	.loc 1 470 5
	.loc 1 472 1 is_stmt 0
	lw	s0,8(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,12(sp)
	.cfi_restore 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	.loc 1 470 5
	tail	riscv_mouse_key_common_para_update
.LVL76:
.L81:
	.cfi_restore_state
	.loc 1 455 10 is_stmt 1
	.loc 1 455 30 is_stmt 0
	andi	a2,a4,128
	.loc 1 455 12
	bne	a2,zero,.L82
	.loc 1 458 10 is_stmt 1
	.loc 1 458 30 is_stmt 0
	andi	a4,a4,64
	.loc 1 458 12
	beq	a4,zero,.L82
	.loc 1 459 9 is_stmt 1
	.loc 1 459 26 is_stmt 0
	sw	zero,riscv_app+16,a4
	j	.L82
	.cfi_endproc
.LFE30:
	.size	peripheral_sampling_common_para_update, .-peripheral_sampling_common_para_update
	.section	.text.peripheral_sampling_init,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_init
	.hidden	peripheral_sampling_init
	.type	peripheral_sampling_init, @function
peripheral_sampling_init:
.LFB26:
	.loc 1 362 1 is_stmt 1
	.cfi_startproc
	.loc 1 363 5
	.loc 1 362 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 363 5
	lla	a0,riscv_app
	.loc 1 362 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 363 5
	call	hid_common_get_hid_exp_features
.LVL77:
	.loc 1 365 5 is_stmt 1
	call	riscv_wheel_init
.LVL78:
	.loc 1 366 5
	call	riscv_motion_sensor_init
.LVL79:
	.loc 1 367 5
	call	riscv_mouse_key_init
.LVL80:
	.loc 1 369 5
	call	peripheral_sampling_common_para_update
.LVL81:
	.loc 1 371 5
	lw	a0,riscv_app
	call	hid_express_set_features
.LVL82:
	.loc 1 373 5
	call	peripheral_sampling_set_inActivity_timeout
.LVL83:
	.loc 1 374 5
	lla	a0,inActivity_gpt_hdl
	call	hal_gpt_sw_get_timer
.LVL84:
	.loc 1 376 5
	lla	a0,peripheral_sampling_handler
	call	hid_express_init
.LVL85:
	.loc 1 378 5
	.loc 1 379 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE26:
	.size	peripheral_sampling_init, .-peripheral_sampling_init
	.section	.text.peripheral_sampling_app_state_update,"ax",@progbits
	.align	1
	.globl	peripheral_sampling_app_state_update
	.hidden	peripheral_sampling_app_state_update
	.type	peripheral_sampling_app_state_update, @function
peripheral_sampling_app_state_update:
.LFB28:
	.loc 1 390 1 is_stmt 1
	.cfi_startproc
.LVL86:
	.loc 1 391 5
	.loc 1 392 5
.LBB34:
	.loc 1 392 10
	.loc 1 392 65
	.loc 1 392 247
.LBE34:
	.loc 1 390 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s1,0(sp)
	.cfi_offset 9, -12
.LBB35:
	.loc 1 392 247
	lla	s1,riscv_app
	lw	a4,20(s1)
.LBE35:
	.loc 1 390 1
	sw	s0,4(sp)
.LBB36:
	.loc 1 392 247
	li	a3,1
	.cfi_offset 8, -8
.LBE36:
	.loc 1 390 1
	mv	s0,a0
.LBB37:
	.loc 1 392 247
	lla	a2,msg_id_string.1
	li	a1,1
	lla	a0,log_control_block_riscv_ps
.LVL87:
.LBE37:
	.loc 1 390 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
.LBB38:
	.loc 1 392 247
	call	print_module_msgid_log
.LVL88:
.LBE38:
	.loc 1 392 8 is_stmt 1 discriminator 1
	.loc 1 393 5
	.loc 1 395 5 is_stmt 0
	li	a5,32
	.loc 1 393 21
	sw	s0,20(s1)
	.loc 1 395 5 is_stmt 1
	beq	s0,a5,.L90
	bgtu	s0,a5,.L91
	li	a5,3
	beq	s0,a5,.L92
	li	a5,10
	beq	s0,a5,.L90
.L93:
	.loc 1 433 5
	mv	a0,s0
	call	riscv_mouse_key__app_state_update
.LVL89:
	.loc 1 434 5
	mv	a0,s0
	.loc 1 437 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL90:
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 434 5
	tail	riscv_wheel__app_state_update
.LVL91:
.L91:
	.cfi_restore_state
	.loc 1 395 5
	addi	a5,s0,-64
	andi	a5,a5,-65
	bne	a5,zero,.L93
.L90:
	.loc 1 398 13 is_stmt 1
	call	peripheral_sampling_common_para_update
.LVL92:
	.loc 1 399 9
	j	.L93
.L92:
	.loc 1 403 13
.LBB39:
.LBB40:
	.loc 1 144 5
	.loc 1 144 19 is_stmt 0
	sw	zero,pairing_state,a5
.LBE40:
.LBE39:
	.loc 1 404 13 is_stmt 1
	call	peripheral_sampling_deinit
.LVL93:
	.loc 1 406 9
	j	.L93
	.cfi_endproc
.LFE28:
	.size	peripheral_sampling_app_state_update, .-peripheral_sampling_app_state_update
	.section	.text.peripheral_sampling__check_condiction,"ax",@progbits
	.align	1
	.globl	peripheral_sampling__check_condiction
	.hidden	peripheral_sampling__check_condiction
	.type	peripheral_sampling__check_condiction, @function
peripheral_sampling__check_condiction:
.LFB31:
	.loc 1 475 1
	.cfi_startproc
.LVL94:
	.loc 1 476 5
	li	a5,3
	beq	a0,a5,.L96
	bgtu	a0,a5,.L97
	li	a5,1
	beq	a0,a5,.L98
	li	a5,2
	beq	a0,a5,.L99
.L109:
	.loc 1 518 11 is_stmt 0
	li	a0,0
.LVL95:
	ret
.LVL96:
.L97:
	.loc 1 476 5
	li	a5,4
	bne	a0,a5,.L109
	.loc 1 508 13 is_stmt 1
	.loc 1 508 16 is_stmt 0
	lw	a0,riscv_app+20
.LVL97:
	srli	a0,a0,5
	andi	a0,a0,1
.L100:
	.loc 1 519 1
	ret
.LVL98:
.L98:
	.loc 1 480 13 is_stmt 1
	.loc 1 480 27 is_stmt 0
	lla	a5,riscv_app
	.loc 1 480 16
	lw	a3,16(a5)
	li	a4,6
	.loc 1 518 11
	li	a0,0
.LVL99:
	.loc 1 480 16
	bne	a3,a4,.L100
	.loc 1 480 74 discriminator 1
	lw	a5,20(a5)
	.loc 1 480 81 discriminator 1
	andi	a4,a5,224
	.loc 1 480 61 discriminator 1
	beq	a4,zero,.L100
	.loc 1 480 162 discriminator 2
	srli	a5,a5,6
	xori	a5,a5,1
	andi	a0,a5,1
	ret
.LVL100:
.L99:
	.loc 1 488 13 is_stmt 1
	.loc 1 488 27 is_stmt 0
	lw	a5,riscv_app+20
	.loc 1 488 34
	andi	a4,a5,224
	.loc 1 518 11
	li	a0,0
.LVL101:
	.loc 1 488 16
	beq	a4,zero,.L100
	.loc 1 489 17 is_stmt 1
	.loc 1 489 39 is_stmt 0
	andi	a5,a5,15
	.loc 1 489 20
	addi	a5,a5,-1
	snez	a0,a5
	ret
.LVL102:
.L96:
	.loc 1 498 13 is_stmt 1
	.loc 1 498 27 is_stmt 0
	lw	a5,riscv_app+20
	.loc 1 498 34
	andi	a4,a5,224
	.loc 1 518 11
	li	a0,0
.LVL103:
	.loc 1 498 16
	beq	a4,zero,.L100
	.loc 1 499 17 is_stmt 1
	.loc 1 499 39 is_stmt 0
	andi	a5,a5,15
	.loc 1 499 20
	addi	a5,a5,-1
	seqz	a0,a5
	ret
	.cfi_endproc
.LFE31:
	.size	peripheral_sampling__check_condiction, .-peripheral_sampling__check_condiction
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 116
msg_id_string.0:
	.string	"[M:riscv_ps C:info F: L: ]: peripheral_sampling_common_para_update, rr_idx = %d, rr_idx_usb = %d, rr_idx_2_4g = %d "
	.align	2
	.type	msg_id_string.1, @object
	.size	msg_id_string.1, 89
msg_id_string.1:
	.string	"[M:riscv_ps C:info F: L: ]: peripheral_sampling_app_state_update, riscv_app.state = 0x%x"
	.hidden	riscv_app
	.globl	riscv_app
	.section	.bss.riscv_app,"aw",@nobits
	.align	2
	.type	riscv_app, @object
	.size	riscv_app, 24
riscv_app:
	.zero	24
	.hidden	inActivity_time
	.globl	inActivity_time
	.section	.sdata.inActivity_time,"aw"
	.align	2
	.type	inActivity_time, @object
	.size	inActivity_time, 4
inActivity_time:
	.word	10000
	.hidden	pairing_state
	.globl	pairing_state
	.section	.sbss.pairing_state,"aw",@nobits
	.align	2
	.type	pairing_state, @object
	.size	pairing_state, 4
pairing_state:
	.zero	4
	.section	.sbss.sampling_state,"aw",@nobits
	.align	2
	.type	sampling_state, @object
	.size	sampling_state, 4
sampling_state:
	.zero	4
	.hidden	inactivity_counter
	.globl	inactivity_counter
	.section	.sbss.inactivity_counter,"aw",@nobits
	.align	2
	.type	inactivity_counter, @object
	.size	inactivity_counter, 4
inactivity_counter:
	.zero	4
	.section	.sbss.inActivity_gpt_hdl,"aw",@nobits
	.align	2
	.type	inActivity_gpt_hdl, @object
	.size	inActivity_gpt_hdl, 4
inActivity_gpt_hdl:
	.zero	4
	.hidden	log_control_block_mirror_riscv_ps
	.globl	log_control_block_mirror_riscv_ps
	.section	.log_filter_mirror.riscv_ps,"a"
	.align	2
	.type	log_control_block_mirror_riscv_ps, @object
	.size	log_control_block_mirror_riscv_ps, 9
log_control_block_mirror_riscv_ps:
	.string	"riscv_ps"
	.hidden	log_control_block_riscv_ps
	.globl	log_control_block_riscv_ps
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"riscv_ps"
	.section	.log_filter.riscv_ps,"aw"
	.align	2
	.type	log_control_block_riscv_ps, @object
	.size	log_control_block_riscv_ps, 28
log_control_block_riscv_ps:
	.word	.LC0
	.word	0
	.word	1
	.word	0
	.word	0
	.word	0
	.word	print_module_msgid_log
	.text
.Letext0:
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 6 "/workdir/airoha/common/applications/hid/inc/hid_common_ccni_msg.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 8 "/workdir/airoha/common/applications/hid/inc/hid_common_hid_app_states.h"
	.file 9 "/workdir/airoha/common/applications/hid/inc/hid_common_key_remap.h"
	.file 10 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 11 "/workdir/airoha/common/applications/hid/inc/hid_common.h"
	.file 12 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 13 "/workdir/airoha/common/drivers/chip/ab162x/../inc/hal_ccni.h"
	.file 14 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_peripheral_sampling.h"
	.file 15 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 16 "/workdir/airoha/common/middleware/airoha/hid_express/inc/rv_fake_report.h"
	.file 17 "/workdir/airoha/common/middleware/airoha/key_remap/inc/key_remap_backend.h"
	.file 18 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_mouse_key.h"
	.file 19 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_wheel.h"
	.file 20 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_motion_sensor.h"
	.file 21 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_ccni.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1b63
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x38
	.4byte	.LASF389
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL13
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0xe
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0xe
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0xe
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0xe
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0xe
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0xe
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0xe
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0xe
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0xe
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x39
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0xe
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x3a
	.byte	0x4
	.uleb128 0xe
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x16
	.4byte	0x75
	.uleb128 0xa
	.4byte	0x7c
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x3
	.byte	0x22
	.byte	0x15
	.4byte	0x34
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x3
	.byte	0x25
	.byte	0x13
	.4byte	0x42
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x3
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x3
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x4
	.4byte	.LASF18
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x3b
	.4byte	0xc2
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x4
	.byte	0x37
	.byte	0xe
	.4byte	0xec
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x1
	.byte	0
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x4
	.byte	0x3d
	.byte	0xe
	.4byte	0x111
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF25
	.byte	0x4
	.byte	0x42
	.byte	0x3
	.4byte	0xec
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x4
	.byte	0x45
	.byte	0xe
	.4byte	0x184
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF41
	.byte	0x4
	.byte	0x57
	.byte	0x3
	.4byte	0x11d
	.uleb128 0x4
	.4byte	.LASF42
	.byte	0x4
	.byte	0x59
	.byte	0x10
	.4byte	0x19c
	.uleb128 0xa
	.4byte	0x1a1
	.uleb128 0x17
	.4byte	0x1c1
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x111
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF43
	.byte	0x4
	.byte	0x5a
	.byte	0x10
	.4byte	0x1cd
	.uleb128 0xa
	.4byte	0x1d2
	.uleb128 0x17
	.4byte	0x1fc
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x111
	.uleb128 0x3
	.4byte	0x1fc
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x7
	.byte	0
	.uleb128 0xa
	.4byte	0x201
	.uleb128 0x3c
	.uleb128 0x4
	.4byte	.LASF44
	.byte	0x4
	.byte	0x5b
	.byte	0x10
	.4byte	0x20e
	.uleb128 0xa
	.4byte	0x213
	.uleb128 0x17
	.4byte	0x22e
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x111
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xc2
	.uleb128 0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF45
	.byte	0x4
	.byte	0x5c
	.byte	0x14
	.4byte	0x23a
	.uleb128 0xa
	.4byte	0x23f
	.uleb128 0x3d
	.4byte	0xc2
	.4byte	0x262
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x111
	.uleb128 0x3
	.4byte	0x184
	.uleb128 0x3
	.4byte	0x262
	.uleb128 0x3
	.4byte	0x267
	.byte	0
	.uleb128 0xa
	.4byte	0x1fc
	.uleb128 0xa
	.4byte	0xc2
	.uleb128 0x9
	.byte	0x1c
	.byte	0x4
	.byte	0x5e
	.4byte	0x2d0
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x4
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x4
	.byte	0x60
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF48
	.byte	0x4
	.byte	0x61
	.byte	0xe
	.4byte	0xc2
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x4
	.byte	0x62
	.byte	0xf
	.4byte	0x190
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF50
	.byte	0x4
	.byte	0x63
	.byte	0x15
	.4byte	0x1c1
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF51
	.byte	0x4
	.byte	0x64
	.byte	0x12
	.4byte	0x22e
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF52
	.byte	0x4
	.byte	0x65
	.byte	0x10
	.4byte	0x202
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF53
	.byte	0x4
	.byte	0x66
	.byte	0x3
	.4byte	0x26c
	.uleb128 0xb
	.4byte	0xaa
	.4byte	0x2ec
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xb
	.4byte	0xc2
	.4byte	0x2fc
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x5
	.byte	0x50
	.byte	0xe
	.4byte	0x33f
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x8
	.byte	0
	.uleb128 0x9
	.byte	0xa
	.byte	0x5
	.byte	0x5e
	.4byte	0x362
	.uleb128 0x2
	.4byte	.LASF63
	.byte	0x5
	.byte	0x60
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x8
	.string	"pin"
	.byte	0x5
	.byte	0x61
	.byte	0xd
	.4byte	0x362
	.byte	0x2
	.byte	0
	.uleb128 0xb
	.4byte	0xaa
	.4byte	0x372
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF64
	.byte	0x5
	.byte	0x62
	.byte	0x2
	.4byte	0x33f
	.uleb128 0xe
	.byte	0x1
	.byte	0x2
	.4byte	.LASF65
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x6
	.byte	0x33
	.byte	0x1
	.4byte	0x40a
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x81
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x82
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x83
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x84
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x85
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x86
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x87
	.byte	0
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x7
	.byte	0x31
	.byte	0x1
	.4byte	0x447
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x7
	.byte	0
	.uleb128 0x9
	.byte	0x2
	.byte	0x7
	.byte	0x3f
	.4byte	0x46a
	.uleb128 0x2
	.4byte	.LASF94
	.byte	0x7
	.byte	0x41
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF95
	.byte	0x7
	.byte	0x42
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF96
	.byte	0x7
	.byte	0x44
	.byte	0x2
	.4byte	0x447
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x8
	.byte	0x32
	.byte	0x1
	.4byte	0x573
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x41
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x42
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x43
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x44
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x4a
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x4b
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x4c
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x4d
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x4e
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x80
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x81
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x82
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x83
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x84
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x8a
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x8b
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x8c
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x8d
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x8e
	.byte	0
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x9
	.byte	0x81
	.byte	0xd
	.4byte	0x5c2
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0xa
	.byte	0
	.uleb128 0x28
	.2byte	0x11c
	.2byte	0x109
	.byte	0xd
	.4byte	0x5e6
	.uleb128 0x29
	.4byte	.LASF148
	.2byte	0x10a
	.byte	0x1a
	.4byte	0x5e6
	.uleb128 0x3e
	.string	"x_y"
	.byte	0x9
	.2byte	0x10c
	.byte	0x1a
	.4byte	0x5e6
	.byte	0
	.uleb128 0xb
	.4byte	0xc2
	.4byte	0x5f6
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x46
	.byte	0
	.uleb128 0x2a
	.2byte	0x23c
	.2byte	0x105
	.4byte	0x62e
	.uleb128 0x1a
	.4byte	.LASF149
	.2byte	0x106
	.byte	0x16
	.4byte	0xb6
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF150
	.2byte	0x107
	.byte	0x16
	.4byte	0xb6
	.byte	0x2
	.uleb128 0x1a
	.4byte	.LASF151
	.2byte	0x108
	.byte	0x16
	.4byte	0x5e6
	.byte	0x4
	.uleb128 0x3f
	.4byte	0x5c2
	.2byte	0x120
	.byte	0
	.uleb128 0x28
	.2byte	0x23c
	.2byte	0x103
	.byte	0x5
	.4byte	0x64a
	.uleb128 0x29
	.4byte	.LASF152
	.2byte	0x104
	.byte	0x12
	.4byte	0xc2
	.uleb128 0x40
	.4byte	0x5f6
	.byte	0
	.uleb128 0x2a
	.2byte	0x240
	.2byte	0x101
	.4byte	0x667
	.uleb128 0x1a
	.4byte	.LASF153
	.2byte	0x102
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2b
	.4byte	0x62e
	.byte	0x4
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF154
	.byte	0x9
	.2byte	0x111
	.byte	0x1e
	.4byte	0x64a
	.uleb128 0x9
	.byte	0x8
	.byte	0xa
	.byte	0x50
	.4byte	0x6c3
	.uleb128 0x2
	.4byte	.LASF155
	.byte	0xa
	.byte	0x51
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x8
	.string	"k"
	.byte	0xa
	.byte	0x52
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x8
	.string	"x"
	.byte	0xa
	.byte	0x53
	.byte	0xd
	.4byte	0x92
	.byte	0x2
	.uleb128 0x8
	.string	"y"
	.byte	0xa
	.byte	0x54
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x8
	.string	"z1"
	.byte	0xa
	.byte	0x55
	.byte	0xc
	.4byte	0x86
	.byte	0x6
	.uleb128 0x8
	.string	"z2"
	.byte	0xa
	.byte	0x56
	.byte	0xc
	.4byte	0x86
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF156
	.byte	0xa
	.byte	0x57
	.byte	0x1f
	.4byte	0x674
	.uleb128 0x9
	.byte	0x8
	.byte	0xa
	.byte	0x88
	.4byte	0x715
	.uleb128 0x2
	.4byte	.LASF155
	.byte	0xa
	.byte	0x89
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF157
	.byte	0xa
	.byte	0x8a
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF148
	.byte	0xa
	.byte	0x8b
	.byte	0xd
	.4byte	0x2dc
	.byte	0x2
	.uleb128 0x8
	.string	"x"
	.byte	0xa
	.byte	0x8c
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x8
	.string	"y"
	.byte	0xa
	.byte	0x8d
	.byte	0xd
	.4byte	0x92
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF158
	.byte	0xa
	.byte	0x8e
	.byte	0x1e
	.4byte	0x6cf
	.uleb128 0x9
	.byte	0x8
	.byte	0xa
	.byte	0x90
	.4byte	0x767
	.uleb128 0x2
	.4byte	.LASF155
	.byte	0xa
	.byte	0x91
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF159
	.byte	0xa
	.byte	0x92
	.byte	0xe
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF160
	.byte	0xa
	.byte	0x93
	.byte	0xd
	.4byte	0xaa
	.byte	0x3
	.uleb128 0x8
	.string	"x"
	.byte	0xa
	.byte	0x94
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x8
	.string	"y"
	.byte	0xa
	.byte	0x95
	.byte	0xd
	.4byte	0x92
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF161
	.byte	0xa
	.byte	0x96
	.byte	0x1f
	.4byte	0x721
	.uleb128 0xb
	.4byte	0xaa
	.4byte	0x783
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.byte	0xa
	.byte	0xa2
	.4byte	0x7c0
	.uleb128 0x2
	.4byte	.LASF155
	.byte	0xa
	.byte	0xa3
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF157
	.byte	0xa
	.byte	0xa4
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF148
	.byte	0xa
	.byte	0xa5
	.byte	0xd
	.4byte	0x773
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF162
	.byte	0xa
	.byte	0xa6
	.byte	0xd
	.4byte	0xaa
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF163
	.byte	0xa
	.byte	0xa7
	.byte	0x1e
	.4byte	0x783
	.uleb128 0x9
	.byte	0x8
	.byte	0xa
	.byte	0xa9
	.4byte	0x809
	.uleb128 0x2
	.4byte	.LASF155
	.byte	0xa
	.byte	0xaa
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF159
	.byte	0xa
	.byte	0xab
	.byte	0xd
	.4byte	0x809
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF160
	.byte	0xa
	.byte	0xac
	.byte	0xd
	.4byte	0xaa
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF162
	.byte	0xa
	.byte	0xad
	.byte	0xd
	.4byte	0x2dc
	.byte	0x6
	.byte	0
	.uleb128 0xb
	.4byte	0xaa
	.4byte	0x819
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF164
	.byte	0xa
	.byte	0xae
	.byte	0x1f
	.4byte	0x7cc
	.uleb128 0xb
	.4byte	0xaa
	.4byte	0x835
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x9
	.byte	0x2
	.byte	0xb
	.byte	0x49
	.4byte	0x857
	.uleb128 0x8
	.string	"id"
	.byte	0xb
	.byte	0x4b
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF165
	.byte	0xb
	.byte	0x4c
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF166
	.byte	0xb
	.byte	0x4d
	.byte	0x2
	.4byte	0x835
	.uleb128 0x2c
	.byte	0x8
	.byte	0xb
	.byte	0x53
	.byte	0x5
	.4byte	0x8a9
	.uleb128 0x15
	.4byte	.LASF167
	.byte	0xb
	.byte	0x54
	.byte	0x25
	.4byte	0x6c3
	.uleb128 0x15
	.4byte	.LASF168
	.byte	0xb
	.byte	0x56
	.byte	0x23
	.4byte	0x715
	.uleb128 0x15
	.4byte	.LASF169
	.byte	0xb
	.byte	0x57
	.byte	0x28
	.4byte	0x767
	.uleb128 0x15
	.4byte	.LASF170
	.byte	0xb
	.byte	0x59
	.byte	0x20
	.4byte	0x7c0
	.uleb128 0x15
	.4byte	.LASF171
	.byte	0xb
	.byte	0x5a
	.byte	0x25
	.4byte	0x819
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.byte	0xb
	.byte	0x4f
	.4byte	0x8b8
	.uleb128 0x2b
	.4byte	0x863
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF172
	.byte	0xb
	.byte	0x5f
	.byte	0xa
	.4byte	0x8a9
	.uleb128 0x9
	.byte	0x8
	.byte	0xb
	.byte	0x61
	.4byte	0x8e7
	.uleb128 0x2
	.4byte	.LASF173
	.byte	0xb
	.byte	0x62
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF174
	.byte	0xb
	.byte	0x63
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF175
	.byte	0xb
	.byte	0x67
	.byte	0x2
	.4byte	0x8c4
	.uleb128 0x16
	.4byte	0x8e7
	.uleb128 0x9
	.byte	0x3
	.byte	0xb
	.byte	0x69
	.4byte	0x928
	.uleb128 0x2
	.4byte	.LASF176
	.byte	0xb
	.byte	0x6a
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF177
	.byte	0xb
	.byte	0x6b
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF178
	.byte	0xb
	.byte	0x6c
	.byte	0xd
	.4byte	0xaa
	.byte	0x2
	.byte	0
	.uleb128 0x4
	.4byte	.LASF179
	.byte	0xb
	.byte	0x6d
	.byte	0x3
	.4byte	0x8f8
	.uleb128 0x9
	.byte	0x18
	.byte	0xb
	.byte	0x7e
	.4byte	0x98b
	.uleb128 0x2
	.4byte	.LASF180
	.byte	0xb
	.byte	0x7f
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF181
	.byte	0xb
	.byte	0x80
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF182
	.byte	0xb
	.byte	0x81
	.byte	0xe
	.4byte	0xc2
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF183
	.byte	0xb
	.byte	0x82
	.byte	0xe
	.4byte	0xc2
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF184
	.byte	0xb
	.byte	0x83
	.byte	0x17
	.4byte	0xce
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF185
	.byte	0xb
	.byte	0x84
	.byte	0xd
	.4byte	0xaa
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF186
	.byte	0xb
	.byte	0x94
	.byte	0x3
	.4byte	0x934
	.uleb128 0x9
	.byte	0x40
	.byte	0xb
	.byte	0x96
	.4byte	0xa55
	.uleb128 0x2
	.4byte	.LASF183
	.byte	0xb
	.byte	0x97
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF187
	.byte	0xb
	.byte	0x98
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF188
	.byte	0xb
	.byte	0x9b
	.byte	0x1e
	.4byte	0xa55
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF189
	.byte	0xb
	.byte	0x9c
	.byte	0xe
	.4byte	0xc2
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF190
	.byte	0xb
	.byte	0x9d
	.byte	0xe
	.4byte	0xc2
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF191
	.byte	0xb
	.byte	0x9f
	.byte	0x1e
	.4byte	0x857
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF192
	.byte	0xb
	.byte	0xa0
	.byte	0x1e
	.4byte	0x857
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF193
	.byte	0xb
	.byte	0xa5
	.byte	0xe
	.4byte	0xc2
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF194
	.byte	0xb
	.byte	0xa6
	.byte	0xe
	.4byte	0xc2
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF195
	.byte	0xb
	.byte	0xae
	.byte	0xe
	.4byte	0xa5a
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF196
	.byte	0xb
	.byte	0xb1
	.byte	0xd
	.4byte	0x825
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF197
	.byte	0xb
	.byte	0xb2
	.byte	0xd
	.4byte	0xaa
	.byte	0x38
	.uleb128 0x8
	.string	"rr"
	.byte	0xb
	.byte	0xbb
	.byte	0x1d
	.4byte	0x46a
	.byte	0x39
	.uleb128 0x8
	.string	"deb"
	.byte	0xb
	.byte	0xbd
	.byte	0x17
	.4byte	0x928
	.byte	0x3b
	.byte	0
	.uleb128 0xa
	.4byte	0x8f3
	.uleb128 0xb
	.4byte	0xb6
	.4byte	0xa6a
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF198
	.byte	0xb
	.byte	0xbf
	.byte	0x3
	.4byte	0x997
	.uleb128 0x41
	.2byte	0x16ec
	.byte	0xb
	.byte	0xc1
	.byte	0x9
	.4byte	0xac3
	.uleb128 0x8
	.string	"app"
	.byte	0xb
	.byte	0xc3
	.byte	0x1b
	.4byte	0xa6a
	.byte	0
	.uleb128 0x8
	.string	"hid"
	.byte	0xb
	.byte	0xc4
	.byte	0x1b
	.4byte	0x98b
	.byte	0x40
	.uleb128 0x8
	.string	"dbg"
	.byte	0xb
	.byte	0xc5
	.byte	0x17
	.4byte	0x372
	.byte	0x58
	.uleb128 0x2
	.4byte	.LASF199
	.byte	0xb
	.byte	0xc7
	.byte	0x17
	.4byte	0xac3
	.byte	0x62
	.uleb128 0x42
	.4byte	.LASF200
	.byte	0xb
	.byte	0xca
	.byte	0x1d
	.4byte	0xad3
	.2byte	0x16e2
	.byte	0
	.uleb128 0xb
	.4byte	0x667
	.4byte	0xad3
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0xb
	.4byte	0x8b8
	.4byte	0xae3
	.uleb128 0xc
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF201
	.byte	0xb
	.byte	0xcc
	.byte	0x3
	.4byte	0xa76
	.uleb128 0x20
	.4byte	.LASF211
	.byte	0xb
	.byte	0xd2
	.byte	0x19
	.4byte	0xafb
	.uleb128 0xa
	.4byte	0xae3
	.uleb128 0x21
	.byte	0x7
	.4byte	0x2d
	.byte	0xb
	.2byte	0x12a
	.byte	0xd
	.4byte	0xb27
	.uleb128 0x1
	.4byte	.LASF202
	.byte	0
	.uleb128 0x1
	.4byte	.LASF203
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF204
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF205
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.4byte	0xaa
	.uleb128 0xa
	.4byte	0xb31
	.uleb128 0x17
	.4byte	0xb3c
	.uleb128 0x3
	.4byte	0x73
	.byte	0
	.uleb128 0x9
	.byte	0x28
	.byte	0xc
	.byte	0x8d
	.4byte	0xbb2
	.uleb128 0x2
	.4byte	.LASF206
	.byte	0xc
	.byte	0x8e
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x8
	.string	"k"
	.byte	0xc
	.byte	0x8f
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x8
	.string	"x"
	.byte	0xc
	.byte	0x90
	.byte	0xd
	.4byte	0x9e
	.byte	0x8
	.uleb128 0x8
	.string	"y"
	.byte	0xc
	.byte	0x91
	.byte	0xd
	.4byte	0x9e
	.byte	0xc
	.uleb128 0x8
	.string	"z1"
	.byte	0xc
	.byte	0x92
	.byte	0xd
	.4byte	0x9e
	.byte	0x10
	.uleb128 0x8
	.string	"z2"
	.byte	0xc
	.byte	0x93
	.byte	0xd
	.4byte	0x9e
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF207
	.byte	0xc
	.byte	0x94
	.byte	0xe
	.4byte	0xc2
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF208
	.byte	0xc
	.byte	0x95
	.byte	0xe
	.4byte	0x2ec
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF209
	.byte	0xc
	.byte	0x96
	.byte	0xe
	.4byte	0xc2
	.byte	0x24
	.byte	0
	.uleb128 0x4
	.4byte	.LASF210
	.byte	0xc
	.byte	0x9c
	.byte	0x2
	.4byte	0xb3c
	.uleb128 0x20
	.4byte	.LASF212
	.byte	0xc
	.byte	0xda
	.byte	0x11
	.4byte	0xc2
	.uleb128 0xd
	.4byte	0x2d
	.byte	0xc
	.byte	0xef
	.byte	0xe
	.4byte	0xbf5
	.uleb128 0x1
	.4byte	.LASF213
	.byte	0
	.uleb128 0x1
	.4byte	.LASF214
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF215
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF216
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF217
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF218
	.byte	0xc
	.byte	0xf5
	.byte	0x3
	.4byte	0xbca
	.uleb128 0x4
	.4byte	.LASF219
	.byte	0xc
	.byte	0xf7
	.byte	0x10
	.4byte	0xc0d
	.uleb128 0xa
	.4byte	0xc12
	.uleb128 0x17
	.4byte	0xc22
	.uleb128 0x3
	.4byte	0xbf5
	.uleb128 0x3
	.4byte	0xc22
	.byte	0
	.uleb128 0xa
	.4byte	0xbb2
	.uleb128 0x21
	.byte	0x5
	.4byte	0x65
	.byte	0xd
	.2byte	0x120
	.byte	0xe
	.4byte	0xc54
	.uleb128 0xf
	.4byte	.LASF220
	.sleb128 -4
	.uleb128 0xf
	.4byte	.LASF221
	.sleb128 -3
	.uleb128 0xf
	.4byte	.LASF222
	.sleb128 -2
	.uleb128 0xf
	.4byte	.LASF223
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF224
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF225
	.byte	0xd
	.2byte	0x126
	.byte	0x3
	.4byte	0xc27
	.uleb128 0xd
	.4byte	0x2d
	.byte	0xe
	.byte	0x46
	.byte	0xe
	.4byte	0xc80
	.uleb128 0x1
	.4byte	.LASF226
	.byte	0
	.uleb128 0x1
	.4byte	.LASF227
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF228
	.byte	0x2
	.byte	0
	.uleb128 0xd
	.4byte	0x2d
	.byte	0xe
	.byte	0x4c
	.byte	0xe
	.4byte	0xcab
	.uleb128 0x1
	.4byte	.LASF229
	.byte	0
	.uleb128 0x1
	.4byte	.LASF230
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF231
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF232
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF233
	.byte	0x4
	.byte	0
	.uleb128 0x9
	.byte	0x18
	.byte	0xe
	.byte	0x56
	.4byte	0xd02
	.uleb128 0x2
	.4byte	.LASF234
	.byte	0xe
	.byte	0x57
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF235
	.byte	0xe
	.byte	0x58
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF95
	.byte	0xe
	.byte	0x59
	.byte	0xe
	.4byte	0xc2
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF94
	.byte	0xe
	.byte	0x5a
	.byte	0xe
	.4byte	0xc2
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF236
	.byte	0xe
	.byte	0x5b
	.byte	0xe
	.4byte	0xc2
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF237
	.byte	0xe
	.byte	0x5c
	.byte	0xe
	.4byte	0xc2
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF238
	.byte	0xe
	.byte	0x5f
	.byte	0x2
	.4byte	0xcab
	.uleb128 0x20
	.4byte	.LASF239
	.byte	0xe
	.byte	0x63
	.byte	0x16
	.4byte	0xd02
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x2
	.byte	0x6e
	.byte	0xe
	.4byte	0xd3f
	.uleb128 0x1
	.4byte	.LASF240
	.byte	0
	.uleb128 0x1
	.4byte	.LASF241
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF242
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF243
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x2
	.byte	0x76
	.byte	0xe
	.4byte	0xd58
	.uleb128 0x1
	.4byte	.LASF244
	.byte	0
	.uleb128 0x1
	.4byte	.LASF245
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF246
	.byte	0x2
	.byte	0x79
	.byte	0x3
	.4byte	0xd3f
	.uleb128 0x2d
	.4byte	.LASF251
	.byte	0x8
	.byte	0x8b
	.4byte	0xd8a
	.uleb128 0x2
	.4byte	.LASF247
	.byte	0x2
	.byte	0x8c
	.byte	0x22
	.4byte	0xd8a
	.byte	0
	.uleb128 0x2
	.4byte	.LASF248
	.byte	0x2
	.byte	0x8d
	.byte	0x22
	.4byte	0xd8a
	.byte	0x4
	.byte	0
	.uleb128 0xa
	.4byte	0xd64
	.uleb128 0x4
	.4byte	.LASF249
	.byte	0x2
	.byte	0x8f
	.byte	0x3
	.4byte	0xd64
	.uleb128 0x4
	.4byte	.LASF250
	.byte	0x2
	.byte	0x90
	.byte	0x1e
	.4byte	0xd8f
	.uleb128 0x2d
	.4byte	.LASF252
	.byte	0xc
	.byte	0x94
	.4byte	0xdcd
	.uleb128 0x2
	.4byte	.LASF253
	.byte	0x2
	.byte	0x96
	.byte	0x1a
	.4byte	0xd9b
	.byte	0
	.uleb128 0x8
	.string	"noB"
	.byte	0x2
	.byte	0x98
	.byte	0xe
	.4byte	0xc2
	.byte	0x8
	.byte	0
	.uleb128 0x4
	.4byte	.LASF254
	.byte	0x2
	.byte	0x99
	.byte	0x3
	.4byte	0xda7
	.uleb128 0x9
	.byte	0xc
	.byte	0x2
	.byte	0x9b
	.4byte	0xe09
	.uleb128 0x2
	.4byte	.LASF255
	.byte	0x2
	.byte	0x9c
	.byte	0xf
	.4byte	0x267
	.byte	0
	.uleb128 0x2
	.4byte	.LASF256
	.byte	0x2
	.byte	0x9d
	.byte	0xf
	.4byte	0x267
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF257
	.byte	0x2
	.byte	0x9e
	.byte	0xf
	.4byte	0xe09
	.byte	0x8
	.byte	0
	.uleb128 0xa
	.4byte	0xb6
	.uleb128 0x4
	.4byte	.LASF258
	.byte	0x2
	.byte	0x9f
	.byte	0x3
	.4byte	0xdd9
	.uleb128 0x9
	.byte	0x18
	.byte	0x2
	.byte	0xa1
	.4byte	0xe57
	.uleb128 0x2
	.4byte	.LASF259
	.byte	0x2
	.byte	0xa2
	.byte	0x1e
	.4byte	0xe0e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF260
	.byte	0x2
	.byte	0xa3
	.byte	0xc
	.4byte	0xe57
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF261
	.byte	0x2
	.byte	0xa4
	.byte	0xc
	.4byte	0xe57
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF262
	.byte	0x2
	.byte	0xa5
	.byte	0xe
	.4byte	0xb27
	.byte	0x14
	.byte	0
	.uleb128 0xa
	.4byte	0x73
	.uleb128 0x4
	.4byte	.LASF263
	.byte	0x2
	.byte	0xa8
	.byte	0x3
	.4byte	0xe1a
	.uleb128 0x9
	.byte	0x54
	.byte	0x2
	.byte	0xaa
	.4byte	0xf41
	.uleb128 0x2
	.4byte	.LASF259
	.byte	0x2
	.byte	0xab
	.byte	0x1e
	.4byte	0xe0e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF264
	.byte	0x2
	.byte	0xac
	.byte	0xc
	.4byte	0xe57
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF265
	.byte	0x2
	.byte	0xad
	.byte	0xc
	.4byte	0xe57
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF266
	.byte	0x2
	.byte	0xae
	.byte	0xc
	.4byte	0xf41
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF267
	.byte	0x2
	.byte	0xaf
	.byte	0xb
	.4byte	0xf51
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF268
	.byte	0x2
	.byte	0xb0
	.byte	0xb
	.4byte	0x73
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF269
	.byte	0x2
	.byte	0xb1
	.byte	0xe
	.4byte	0xb27
	.byte	0x34
	.uleb128 0x2
	.4byte	.LASF270
	.byte	0x2
	.byte	0xb2
	.byte	0xf
	.4byte	0x267
	.byte	0x38
	.uleb128 0x2
	.4byte	.LASF271
	.byte	0x2
	.byte	0xb3
	.byte	0xf
	.4byte	0xe09
	.byte	0x3c
	.uleb128 0x2
	.4byte	.LASF272
	.byte	0x2
	.byte	0xb4
	.byte	0xe
	.4byte	0xb27
	.byte	0x40
	.uleb128 0x2
	.4byte	.LASF273
	.byte	0x2
	.byte	0xb5
	.byte	0xf
	.4byte	0xe09
	.byte	0x44
	.uleb128 0x2
	.4byte	.LASF274
	.byte	0x2
	.byte	0xb6
	.byte	0xd
	.4byte	0xaa
	.byte	0x48
	.uleb128 0x2
	.4byte	.LASF275
	.byte	0x2
	.byte	0xb7
	.byte	0xd
	.4byte	0xaa
	.byte	0x49
	.uleb128 0x2
	.4byte	.LASF276
	.byte	0x2
	.byte	0xb8
	.byte	0xd
	.4byte	0xaa
	.byte	0x4a
	.uleb128 0x2
	.4byte	.LASF277
	.byte	0x2
	.byte	0xb9
	.byte	0xe
	.4byte	0xb6
	.byte	0x4c
	.uleb128 0x2
	.4byte	.LASF278
	.byte	0x2
	.byte	0xba
	.byte	0xe
	.4byte	0xb27
	.byte	0x50
	.byte	0
	.uleb128 0xb
	.4byte	0xe57
	.4byte	0xf51
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0xb
	.4byte	0x73
	.4byte	0xf61
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF279
	.byte	0x2
	.byte	0xbb
	.byte	0x3
	.4byte	0xe68
	.uleb128 0x9
	.byte	0x34
	.byte	0x2
	.byte	0xbd
	.4byte	0xfaa
	.uleb128 0x2
	.4byte	.LASF259
	.byte	0x2
	.byte	0xbe
	.byte	0x1e
	.4byte	0xe0e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF264
	.byte	0x2
	.byte	0xbf
	.byte	0xc
	.4byte	0xe57
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF266
	.byte	0x2
	.byte	0xc0
	.byte	0xc
	.4byte	0xfaa
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF267
	.byte	0x2
	.byte	0xc1
	.byte	0xb
	.4byte	0xfba
	.byte	0x20
	.byte	0
	.uleb128 0xb
	.4byte	0xe57
	.4byte	0xfba
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0xb
	.4byte	0x73
	.4byte	0xfca
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF280
	.byte	0x2
	.byte	0xc2
	.byte	0x3
	.4byte	0xf6d
	.uleb128 0x2c
	.byte	0x54
	.byte	0x2
	.byte	0xc4
	.byte	0x9
	.4byte	0x100b
	.uleb128 0x22
	.string	"le"
	.byte	0xc5
	.byte	0x1a
	.4byte	0xe5c
	.uleb128 0x22
	.string	"rt"
	.byte	0xc6
	.byte	0x1a
	.4byte	0xf61
	.uleb128 0x22
	.string	"rtt"
	.byte	0xc7
	.byte	0x1b
	.4byte	0xfca
	.uleb128 0x15
	.4byte	.LASF259
	.byte	0x2
	.byte	0xc8
	.byte	0x1e
	.4byte	0xe0e
	.byte	0
	.uleb128 0x4
	.4byte	.LASF281
	.byte	0x2
	.byte	0xc9
	.byte	0x3
	.4byte	0xfd6
	.uleb128 0x9
	.byte	0x94
	.byte	0x2
	.byte	0xcb
	.4byte	0x10d6
	.uleb128 0x2
	.4byte	.LASF282
	.byte	0x2
	.byte	0xcc
	.byte	0x18
	.4byte	0xd58
	.byte	0
	.uleb128 0x2
	.4byte	.LASF283
	.byte	0x2
	.byte	0xcf
	.byte	0x14
	.4byte	0xdcd
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF284
	.byte	0x2
	.byte	0xd0
	.byte	0x14
	.4byte	0xdcd
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF285
	.byte	0x2
	.byte	0xd1
	.byte	0x14
	.4byte	0xdcd
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF286
	.byte	0x2
	.byte	0xd2
	.byte	0xe
	.4byte	0xb27
	.byte	0x28
	.uleb128 0x2
	.4byte	.LASF287
	.byte	0x2
	.byte	0xd3
	.byte	0xe
	.4byte	0xb6
	.byte	0x2c
	.uleb128 0x2
	.4byte	.LASF288
	.byte	0x2
	.byte	0xd4
	.byte	0xe
	.4byte	0xb6
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF289
	.byte	0x2
	.byte	0xd7
	.byte	0xe
	.4byte	0xb27
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF290
	.byte	0x2
	.byte	0xd8
	.byte	0xe
	.4byte	0xb27
	.byte	0x34
	.uleb128 0x2
	.4byte	.LASF291
	.byte	0x2
	.byte	0xd9
	.byte	0xe
	.4byte	0xb6
	.byte	0x38
	.uleb128 0x2
	.4byte	.LASF292
	.byte	0x2
	.byte	0xda
	.byte	0xe
	.4byte	0xb6
	.byte	0x3a
	.uleb128 0x2
	.4byte	.LASF293
	.byte	0x2
	.byte	0xdb
	.byte	0xe
	.4byte	0xb6
	.byte	0x3c
	.uleb128 0x2
	.4byte	.LASF294
	.byte	0x2
	.byte	0xdc
	.byte	0xd
	.4byte	0xaa
	.byte	0x3e
	.uleb128 0x2
	.4byte	.LASF295
	.byte	0x2
	.byte	0xdf
	.byte	0x17
	.4byte	0x100b
	.byte	0x40
	.byte	0
	.uleb128 0x4
	.4byte	.LASF296
	.byte	0x2
	.byte	0xe0
	.byte	0x3
	.4byte	0x1017
	.uleb128 0x23
	.4byte	.LASF297
	.byte	0x2
	.2byte	0x107
	.byte	0x18
	.4byte	0x10ef
	.uleb128 0xa
	.4byte	0x10d6
	.uleb128 0x1b
	.4byte	.LASF298
	.byte	0xf
	.2byte	0x143
	.byte	0x10
	.4byte	0xb2c
	.uleb128 0x21
	.byte	0x5
	.4byte	0x65
	.byte	0xf
	.2byte	0x153
	.byte	0xe
	.4byte	0x1140
	.uleb128 0xf
	.4byte	.LASF299
	.sleb128 -7
	.uleb128 0xf
	.4byte	.LASF300
	.sleb128 -6
	.uleb128 0xf
	.4byte	.LASF301
	.sleb128 -5
	.uleb128 0xf
	.4byte	.LASF302
	.sleb128 -4
	.uleb128 0xf
	.4byte	.LASF303
	.sleb128 -3
	.uleb128 0xf
	.4byte	.LASF304
	.sleb128 -2
	.uleb128 0xf
	.4byte	.LASF305
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF306
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF307
	.byte	0xf
	.2byte	0x15c
	.byte	0x3
	.4byte	0x1101
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x10
	.byte	0x2d
	.byte	0xe
	.4byte	0x116c
	.uleb128 0x1
	.4byte	.LASF308
	.byte	0
	.uleb128 0x1
	.4byte	.LASF309
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF310
	.byte	0x2
	.byte	0
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x11
	.byte	0x34
	.byte	0xe
	.4byte	0x11a9
	.uleb128 0x1
	.4byte	.LASF311
	.byte	0
	.uleb128 0x1
	.4byte	.LASF312
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF313
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF314
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF315
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF316
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF317
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF318
	.byte	0x7
	.byte	0
	.uleb128 0x18
	.4byte	.LASF319
	.byte	0x58
	.byte	0x4e
	.4byte	0x2d0
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_riscv_ps
	.uleb128 0xb
	.4byte	0x7c
	.4byte	0x11ca
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x8
	.byte	0
	.uleb128 0x16
	.4byte	0x11ba
	.uleb128 0x18
	.4byte	.LASF320
	.byte	0x58
	.byte	0x7e
	.4byte	0x11ca
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_mirror_riscv_ps
	.uleb128 0x2e
	.4byte	.LASF322
	.byte	0x5b
	.4byte	0xc2
	.uleb128 0x5
	.byte	0x3
	.4byte	inActivity_gpt_hdl
	.uleb128 0x18
	.4byte	.LASF321
	.byte	0x5c
	.byte	0xa
	.4byte	0xc2
	.uleb128 0x5
	.byte	0x3
	.4byte	inactivity_counter
	.uleb128 0x2e
	.4byte	.LASF323
	.byte	0x5d
	.4byte	0xc2
	.uleb128 0x5
	.byte	0x3
	.4byte	sampling_state
	.uleb128 0x18
	.4byte	.LASF324
	.byte	0x5e
	.byte	0xa
	.4byte	0xc2
	.uleb128 0x5
	.byte	0x3
	.4byte	pairing_state
	.uleb128 0x18
	.4byte	.LASF325
	.byte	0x5f
	.byte	0xa
	.4byte	0xc2
	.uleb128 0x5
	.byte	0x3
	.4byte	inActivity_time
	.uleb128 0x43
	.4byte	0xd0e
	.byte	0x1
	.byte	0x60
	.byte	0xf
	.uleb128 0x5
	.byte	0x3
	.4byte	riscv_app
	.uleb128 0x11
	.4byte	.LASF326
	.byte	0x12
	.byte	0x41
	.4byte	0x124e
	.uleb128 0x7
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF329
	.byte	0xc
	.2byte	0x11d
	.byte	0x6
	.4byte	0x1261
	.uleb128 0x3
	.4byte	0xc2
	.byte	0
	.uleb128 0x11
	.4byte	.LASF327
	.byte	0x13
	.byte	0x36
	.4byte	0x126e
	.uleb128 0x7
	.byte	0
	.uleb128 0x11
	.4byte	.LASF328
	.byte	0x12
	.byte	0x35
	.4byte	0x127b
	.uleb128 0x7
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF330
	.byte	0x13
	.byte	0x34
	.4byte	0x128c
	.uleb128 0x3
	.4byte	0xc2
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF331
	.byte	0x12
	.byte	0x40
	.4byte	0x129d
	.uleb128 0x3
	.4byte	0xc2
	.byte	0
	.uleb128 0x44
	.4byte	.LASF332
	.byte	0xc
	.2byte	0x11c
	.byte	0x6
	.4byte	0x12ac
	.uleb128 0x7
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF333
	.2byte	0x1ab
	.4byte	0x1140
	.4byte	0x12c1
	.uleb128 0x3
	.4byte	0xc2
	.byte	0
	.uleb128 0x13
	.4byte	.LASF334
	.byte	0xc
	.byte	0xf9
	.byte	0x5
	.4byte	0x65
	.4byte	0x12d7
	.uleb128 0x3
	.4byte	0xc01
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF335
	.2byte	0x1a2
	.4byte	0x1140
	.4byte	0x12ec
	.uleb128 0x3
	.4byte	0x267
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF336
	.byte	0xc
	.2byte	0x116
	.byte	0x6
	.4byte	0x12ff
	.uleb128 0x3
	.4byte	0xc2
	.byte	0
	.uleb128 0x10
	.4byte	.LASF337
	.byte	0x12
	.byte	0x2f
	.byte	0x5
	.4byte	0x65
	.4byte	0x1311
	.uleb128 0x7
	.byte	0
	.uleb128 0x10
	.4byte	.LASF338
	.byte	0x14
	.byte	0x2e
	.byte	0x5
	.4byte	0x65
	.4byte	0x1323
	.uleb128 0x7
	.byte	0
	.uleb128 0x10
	.4byte	.LASF339
	.byte	0x13
	.byte	0x2e
	.byte	0x5
	.4byte	0x65
	.4byte	0x1335
	.uleb128 0x7
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF340
	.byte	0xb
	.2byte	0x128
	.byte	0x6
	.4byte	0x1348
	.uleb128 0x3
	.4byte	0x267
	.byte	0
	.uleb128 0x11
	.4byte	.LASF341
	.byte	0x12
	.byte	0x36
	.4byte	0x1355
	.uleb128 0x7
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF342
	.byte	0x12
	.byte	0x3d
	.4byte	0x1366
	.uleb128 0x3
	.4byte	0xc2
	.byte	0
	.uleb128 0x13
	.4byte	.LASF343
	.byte	0x11
	.byte	0x52
	.byte	0xa
	.4byte	0xc2
	.4byte	0x137c
	.uleb128 0x3
	.4byte	0x267
	.byte	0
	.uleb128 0x10
	.4byte	.LASF344
	.byte	0x11
	.byte	0x48
	.byte	0xa
	.4byte	0xc2
	.4byte	0x138e
	.uleb128 0x7
	.byte	0
	.uleb128 0x11
	.4byte	.LASF345
	.byte	0x11
	.byte	0x49
	.4byte	0x139b
	.uleb128 0x7
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF346
	.byte	0xe
	.byte	0x68
	.4byte	0x13b1
	.uleb128 0x3
	.4byte	0xc2
	.uleb128 0x3
	.4byte	0xc2
	.byte	0
	.uleb128 0x10
	.4byte	.LASF347
	.byte	0x11
	.byte	0x47
	.byte	0xa
	.4byte	0xc2
	.4byte	0x13c3
	.uleb128 0x7
	.byte	0
	.uleb128 0x10
	.4byte	.LASF348
	.byte	0xc
	.byte	0xfa
	.byte	0xa
	.4byte	0xc2
	.4byte	0x13d5
	.uleb128 0x7
	.byte	0
	.uleb128 0x11
	.4byte	.LASF349
	.byte	0x13
	.byte	0x33
	.4byte	0x13e2
	.uleb128 0x7
	.byte	0
	.uleb128 0x13
	.4byte	.LASF350
	.byte	0x12
	.byte	0x30
	.byte	0x5
	.4byte	0x65
	.4byte	0x13f8
	.uleb128 0x3
	.4byte	0x267
	.byte	0
	.uleb128 0x10
	.4byte	.LASF351
	.byte	0x13
	.byte	0x30
	.byte	0x5
	.4byte	0x65
	.4byte	0x140a
	.uleb128 0x7
	.byte	0
	.uleb128 0x13
	.4byte	.LASF352
	.byte	0x13
	.byte	0x31
	.byte	0x5
	.4byte	0x65
	.4byte	0x1420
	.uleb128 0x3
	.4byte	0x1420
	.byte	0
	.uleb128 0xa
	.4byte	0x9e
	.uleb128 0x13
	.4byte	.LASF353
	.byte	0x14
	.byte	0x31
	.byte	0x5
	.4byte	0x65
	.4byte	0x1440
	.uleb128 0x3
	.4byte	0x1420
	.uleb128 0x3
	.4byte	0x1420
	.byte	0
	.uleb128 0x11
	.4byte	.LASF354
	.byte	0x12
	.byte	0x34
	.4byte	0x144d
	.uleb128 0x7
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF355
	.2byte	0x1b8
	.4byte	0x1140
	.4byte	0x1471
	.uleb128 0x3
	.4byte	0xc2
	.uleb128 0x3
	.4byte	0xc2
	.uleb128 0x3
	.4byte	0x10f4
	.uleb128 0x3
	.4byte	0x73
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF356
	.2byte	0x1c1
	.4byte	0x1140
	.4byte	0x1486
	.uleb128 0x3
	.4byte	0xc2
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF357
	.2byte	0x107
	.4byte	0xc2
	.4byte	0x1497
	.uleb128 0x7
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF358
	.2byte	0x105
	.4byte	0xc2
	.4byte	0x14a8
	.uleb128 0x7
	.byte	0
	.uleb128 0x13
	.4byte	.LASF359
	.byte	0xe
	.byte	0x67
	.byte	0x13
	.4byte	0xc54
	.4byte	0x14c3
	.uleb128 0x3
	.4byte	0xb27
	.uleb128 0x3
	.4byte	0xaa
	.byte	0
	.uleb128 0x11
	.4byte	.LASF360
	.byte	0x15
	.byte	0x33
	.4byte	0x14d0
	.uleb128 0x7
	.byte	0
	.uleb128 0x13
	.4byte	.LASF361
	.byte	0x10
	.byte	0x34
	.byte	0x5
	.4byte	0x65
	.4byte	0x14f0
	.uleb128 0x3
	.4byte	0xc2
	.uleb128 0x3
	.4byte	0xc2
	.uleb128 0x3
	.4byte	0xc2
	.byte	0
	.uleb128 0x10
	.4byte	.LASF362
	.byte	0x12
	.byte	0x3b
	.byte	0xa
	.4byte	0xc2
	.4byte	0x1502
	.uleb128 0x7
	.byte	0
	.uleb128 0x10
	.4byte	.LASF363
	.byte	0x10
	.byte	0x39
	.byte	0xa
	.4byte	0xc2
	.4byte	0x1514
	.uleb128 0x7
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF364
	.byte	0x4
	.2byte	0x129
	.byte	0xd
	.4byte	0x1537
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x111
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xc2
	.uleb128 0x7
	.byte	0
	.uleb128 0x45
	.4byte	.LASF390
	.byte	0x1
	.2byte	0x1da
	.byte	0x5
	.4byte	0x37e
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1562
	.uleb128 0x30
	.4byte	.LASF368
	.2byte	0x1da
	.4byte	0xc2
	.4byte	.LLST12
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF366
	.2byte	0x1bd
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x15dd
	.uleb128 0x46
	.4byte	.LBB33
	.4byte	.LBE33-.LBB33
	.4byte	0x15ca
	.uleb128 0x23
	.4byte	.LASF319
	.byte	0x1
	.2byte	0x1ce
	.byte	0x25
	.4byte	0x2d0
	.uleb128 0x24
	.4byte	.LASF365
	.2byte	0x1ce
	.byte	0x80
	.4byte	0x15ed
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x19
	.4byte	.LVL74
	.4byte	0x1514
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_riscv_ps
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x33
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL75
	.4byte	0x124e
	.uleb128 0x12
	.4byte	.LVL76
	.4byte	0x1241
	.byte	0
	.uleb128 0xb
	.4byte	0x7c
	.4byte	0x15ed
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x73
	.byte	0
	.uleb128 0x16
	.4byte	0x15dd
	.uleb128 0x1f
	.4byte	.LASF367
	.2byte	0x1b7
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x161a
	.uleb128 0x5
	.4byte	.LVL72
	.4byte	0x126e
	.uleb128 0x12
	.4byte	.LVL73
	.4byte	0x1261
	.byte	0
	.uleb128 0x47
	.4byte	.LASF371
	.byte	0x1
	.2byte	0x185
	.byte	0x6
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x16e2
	.uleb128 0x30
	.4byte	.LASF369
	.2byte	0x185
	.4byte	0xc2
	.4byte	.LLST10
	.uleb128 0x48
	.4byte	.LLRL11
	.4byte	0x168f
	.uleb128 0x23
	.4byte	.LASF319
	.byte	0x1
	.2byte	0x188
	.byte	0x25
	.4byte	0x2d0
	.uleb128 0x24
	.4byte	.LASF365
	.2byte	0x188
	.byte	0x80
	.4byte	0x16f2
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x19
	.4byte	.LVL88
	.4byte	0x1514
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_riscv_ps
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x49
	.4byte	0x199a
	.4byte	.LBB39
	.4byte	.LBE39-.LBB39
	.byte	0x1
	.2byte	0x193
	.byte	0xd
	.uleb128 0x14
	.4byte	.LVL89
	.4byte	0x128c
	.4byte	0x16b4
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x31
	.4byte	.LVL91
	.4byte	0x127b
	.4byte	0x16cf
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL92
	.4byte	0x1562
	.uleb128 0x5
	.4byte	.LVL93
	.4byte	0x16f7
	.byte	0
	.uleb128 0xb
	.4byte	0x7c
	.4byte	0x16f2
	.uleb128 0xc
	.4byte	0x2d
	.byte	0x58
	.byte	0
	.uleb128 0x16
	.4byte	0x16e2
	.uleb128 0x1f
	.4byte	.LASF370
	.2byte	0x17d
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1728
	.uleb128 0x5
	.4byte	.LVL69
	.4byte	0x1471
	.uleb128 0x5
	.4byte	.LVL70
	.4byte	0x12ac
	.uleb128 0x12
	.4byte	.LVL71
	.4byte	0x129d
	.byte	0
	.uleb128 0x4a
	.4byte	.LASF372
	.byte	0x1
	.2byte	0x169
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x17bb
	.uleb128 0x14
	.4byte	.LVL77
	.4byte	0x1335
	.4byte	0x175a
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	riscv_app
	.byte	0
	.uleb128 0x5
	.4byte	.LVL78
	.4byte	0x1323
	.uleb128 0x5
	.4byte	.LVL79
	.4byte	0x1311
	.uleb128 0x5
	.4byte	.LVL80
	.4byte	0x12ff
	.uleb128 0x5
	.4byte	.LVL81
	.4byte	0x1562
	.uleb128 0x5
	.4byte	.LVL82
	.4byte	0x12ec
	.uleb128 0x5
	.4byte	.LVL83
	.4byte	0x19e9
	.uleb128 0x14
	.4byte	.LVL84
	.4byte	0x12d7
	.4byte	0x17a7
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	inActivity_gpt_hdl
	.byte	0
	.uleb128 0x19
	.4byte	.LVL85
	.4byte	0x12c1
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	peripheral_sampling_handler
	.byte	0
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF373
	.2byte	0x13e
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x185f
	.uleb128 0x4b
	.4byte	.LASF153
	.byte	0x1
	.2byte	0x147
	.byte	0xe
	.4byte	0xc2
	.4byte	.LLST7
	.uleb128 0x24
	.4byte	.LASF374
	.2byte	0x148
	.byte	0xe
	.4byte	0xc2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x5
	.4byte	.LVL30
	.4byte	0x13d5
	.uleb128 0x5
	.4byte	.LVL31
	.4byte	0x13c3
	.uleb128 0x5
	.4byte	.LVL32
	.4byte	0x1932
	.uleb128 0x5
	.4byte	.LVL33
	.4byte	0x1a09
	.uleb128 0x5
	.4byte	.LVL34
	.4byte	0x13b1
	.uleb128 0x14
	.4byte	.LVL36
	.4byte	0x1366
	.4byte	0x1831
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL37
	.4byte	0x1355
	.uleb128 0x5
	.4byte	.LVL38
	.4byte	0x1348
	.uleb128 0x5
	.4byte	.LVL43
	.4byte	0x139b
	.uleb128 0x5
	.4byte	.LVL44
	.4byte	0x138e
	.uleb128 0x5
	.4byte	.LVL46
	.4byte	0x137c
	.byte	0
	.uleb128 0x32
	.4byte	.LASF375
	.byte	0xf7
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x191c
	.uleb128 0x25
	.4byte	.LASF376
	.byte	0xf7
	.byte	0x31
	.4byte	0xbf5
	.4byte	.LLST8
	.uleb128 0x25
	.4byte	.LASF377
	.byte	0xf7
	.byte	0x52
	.4byte	0xc22
	.4byte	.LLST9
	.uleb128 0x5
	.4byte	.LVL49
	.4byte	0x191c
	.uleb128 0x12
	.4byte	.LVL51
	.4byte	0x1440
	.uleb128 0x12
	.4byte	.LVL56
	.4byte	0x194c
	.uleb128 0x14
	.4byte	.LVL58
	.4byte	0x1425
	.4byte	0x18c6
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 8
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x78
	.sleb128 12
	.byte	0
	.uleb128 0x5
	.4byte	.LVL59
	.4byte	0x191c
	.uleb128 0x5
	.4byte	.LVL60
	.4byte	0x1440
	.uleb128 0x14
	.4byte	.LVL61
	.4byte	0x140a
	.4byte	0x18ec
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 16
	.byte	0
	.uleb128 0x12
	.4byte	.LVL63
	.4byte	0x13f8
	.uleb128 0x31
	.4byte	.LVL66
	.4byte	0x13e2
	.4byte	0x1912
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0xb
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x12
	.4byte	.LVL68
	.4byte	0x17bb
	.byte	0
	.uleb128 0x4c
	.4byte	.LASF391
	.byte	0x1
	.byte	0xe5
	.byte	0x5
	.4byte	0x37e
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x4d
	.4byte	.LASF378
	.byte	0x1
	.byte	0xc9
	.byte	0x6
	.byte	0x1
	.4byte	0x194c
	.uleb128 0x4e
	.4byte	.LASF392
	.byte	0x1
	.byte	0xc9
	.byte	0x2e
	.4byte	0xc2
	.byte	0
	.uleb128 0x33
	.4byte	.LASF379
	.byte	0x9e
	.4byte	0x1961
	.uleb128 0x26
	.4byte	.LASF386
	.byte	0xa1
	.4byte	0xc2
	.byte	0
	.uleb128 0x4f
	.4byte	.LASF380
	.byte	0x1
	.byte	0x93
	.byte	0x6
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x199a
	.uleb128 0x34
	.string	"msg"
	.byte	0x95
	.4byte	0x2dc
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x19
	.4byte	.LVL11
	.4byte	0x14a8
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.byte	0
	.uleb128 0x50
	.4byte	.LASF393
	.byte	0x1
	.byte	0x8e
	.byte	0x6
	.byte	0x1
	.uleb128 0x32
	.4byte	.LASF381
	.byte	0x84
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x19e9
	.uleb128 0x25
	.4byte	.LASF382
	.byte	0x84
	.byte	0x33
	.4byte	0x73
	.4byte	.LLST0
	.uleb128 0x34
	.string	"msg"
	.byte	0x86
	.4byte	0x2dc
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x19
	.4byte	.LVL2
	.4byte	0x14a8
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.byte	0
	.uleb128 0x35
	.4byte	.LASF383
	.byte	0x7f
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x35
	.4byte	.LASF384
	.byte	0x7a
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x33
	.4byte	.LASF385
	.byte	0x68
	.4byte	0x1a28
	.uleb128 0x26
	.4byte	.LASF387
	.byte	0x6a
	.4byte	0xc2
	.uleb128 0x26
	.4byte	.LASF388
	.byte	0x6b
	.4byte	0xc2
	.byte	0
	.uleb128 0x51
	.4byte	.LASF394
	.byte	0x2
	.2byte	0x10c
	.byte	0x11
	.4byte	0xb6
	.byte	0x3
	.uleb128 0x36
	.4byte	0x1a09
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1a94
	.uleb128 0x27
	.4byte	0x1a13
	.4byte	.LLST1
	.uleb128 0x27
	.4byte	0x1a1d
	.4byte	.LLST2
	.uleb128 0x5
	.4byte	.LVL3
	.4byte	0x1502
	.uleb128 0x5
	.4byte	.LVL5
	.4byte	0x14f0
	.uleb128 0x14
	.4byte	.LVL7
	.4byte	0x14d0
	.4byte	0x1a8a
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x12
	.4byte	.LVL9
	.4byte	0x14c3
	.byte	0
	.uleb128 0x52
	.4byte	0x199a
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x36
	.4byte	0x194c
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1b05
	.uleb128 0x27
	.4byte	0x1956
	.4byte	.LLST3
	.uleb128 0x53
	.4byte	0x1a28
	.4byte	.LBB17
	.4byte	.LBE17-.LBB17
	.byte	0x1
	.byte	0xae
	.byte	0x15
	.uleb128 0x54
	.4byte	0x194c
	.4byte	.LBB19
	.4byte	.LBE19-.LBB19
	.byte	0x1
	.byte	0x9e
	.byte	0x6
	.4byte	0x1af2
	.uleb128 0x55
	.4byte	0x1956
	.uleb128 0x5
	.4byte	.LVL21
	.4byte	0x1486
	.byte	0
	.uleb128 0x5
	.4byte	.LVL12
	.4byte	0x1497
	.uleb128 0x5
	.4byte	.LVL18
	.4byte	0x1961
	.byte	0
	.uleb128 0x56
	.4byte	0x1932
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x37
	.4byte	0x193f
	.4byte	.LLST4
	.uleb128 0x57
	.4byte	0x1932
	.4byte	.LBB23
	.4byte	.LLRL5
	.byte	0x1
	.byte	0xc9
	.byte	0x6
	.4byte	0x1b5c
	.uleb128 0x37
	.4byte	0x193f
	.4byte	.LLST6
	.uleb128 0x5
	.4byte	.LVL28
	.4byte	0x1471
	.uleb128 0x58
	.4byte	.LVL29
	.4byte	0x144d
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	peripheral_sampling_inactivity_timeout
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL24
	.4byte	0x1471
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3e
	.uleb128 0x21
	.sleb128 7
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x82
	.uleb128 0x19
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 15
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 18
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 16
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 17
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 12
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 10
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 52
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x82
	.uleb128 0x19
	.uleb128 0x7f
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 13
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x3d
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x40
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x41
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x42
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x43
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x44
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x45
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x46
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x47
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x48
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x49
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x4a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x4c
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x4d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4e
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x50
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x51
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x52
	.uleb128 0x2e
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x53
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x54
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x55
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x56
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x57
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x58
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x82
	.uleb128 0x19
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loclists,"",@progbits
	.4byte	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.Ldebug_loc0:
.LLST12:
	.byte	0x6
	.4byte	.LVL94
	.byte	0x4
	.uleb128 .LVL94-.LVL94
	.uleb128 .LVL95-.LVL94
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL95-.LVL94
	.uleb128 .LVL96-.LVL94
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL96-.LVL94
	.uleb128 .LVL97-.LVL94
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL97-.LVL94
	.uleb128 .LVL98-.LVL94
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL98-.LVL94
	.uleb128 .LVL99-.LVL94
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL99-.LVL94
	.uleb128 .LVL100-.LVL94
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL100-.LVL94
	.uleb128 .LVL101-.LVL94
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL101-.LVL94
	.uleb128 .LVL102-.LVL94
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL102-.LVL94
	.uleb128 .LVL103-.LVL94
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL103-.LVL94
	.uleb128 .LFE31-.LVL94
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL86
	.byte	0x4
	.uleb128 .LVL86-.LVL86
	.uleb128 .LVL87-.LVL86
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL87-.LVL86
	.uleb128 .LVL90-.LVL86
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL90-.LVL86
	.uleb128 .LVL91-1-.LVL86
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL91-1-.LVL86
	.uleb128 .LVL91-.LVL86
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL91-.LVL86
	.uleb128 .LFE28-.LVL86
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL34
	.byte	0x4
	.uleb128 .LVL34-.LVL34
	.uleb128 .LVL35-.LVL34
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL39-.LVL34
	.uleb128 .LVL40-.LVL34
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL41-.LVL34
	.uleb128 .LVL42-.LVL34
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL45-.LVL34
	.uleb128 .LVL46-1-.LVL34
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL47-.LVL34
	.uleb128 .LFE25-.LVL34
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST8:
	.byte	0x6
	.4byte	.LVL48
	.byte	0x4
	.uleb128 .LVL48-.LVL48
	.uleb128 .LVL49-1-.LVL48
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL49-1-.LVL48
	.uleb128 .LVL51-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL51-.LVL48
	.uleb128 .LVL52-.LVL48
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL52-.LVL48
	.uleb128 .LVL54-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL54-.LVL48
	.uleb128 .LVL56-1-.LVL48
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL56-1-.LVL48
	.uleb128 .LVL56-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL56-.LVL48
	.uleb128 .LVL57-.LVL48
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL57-.LVL48
	.uleb128 .LVL63-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL63-.LVL48
	.uleb128 .LVL65-.LVL48
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL65-.LVL48
	.uleb128 .LVL66-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL66-.LVL48
	.uleb128 .LVL68-1-.LVL48
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL68-1-.LVL48
	.uleb128 .LFE24-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL48
	.byte	0x4
	.uleb128 .LVL48-.LVL48
	.uleb128 .LVL49-1-.LVL48
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL49-1-.LVL48
	.uleb128 .LVL50-.LVL48
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL50-.LVL48
	.uleb128 .LVL51-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL51-.LVL48
	.uleb128 .LVL53-.LVL48
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL53-.LVL48
	.uleb128 .LVL54-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL54-.LVL48
	.uleb128 .LVL55-.LVL48
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL55-.LVL48
	.uleb128 .LVL56-1-.LVL48
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL56-1-.LVL48
	.uleb128 .LVL56-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL56-.LVL48
	.uleb128 .LVL62-.LVL48
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL62-.LVL48
	.uleb128 .LVL63-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL63-.LVL48
	.uleb128 .LVL64-.LVL48
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL64-.LVL48
	.uleb128 .LVL66-1-.LVL48
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL66-1-.LVL48
	.uleb128 .LVL66-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL66-.LVL48
	.uleb128 .LVL67-.LVL48
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL67-.LVL48
	.uleb128 .LVL68-1-.LVL48
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL68-1-.LVL48
	.uleb128 .LFE24-.LVL48
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL1-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL1-.LVL0
	.uleb128 .LFE18-.LVL0
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL8-.LVL4
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL9-.LVL4
	.uleb128 .LVL10-.LVL4
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL6-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL9-.LVL5
	.uleb128 .LFE15-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL14-.LVL12
	.uleb128 .LVL15-.LVL12
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL16-.LVL12
	.uleb128 .LVL17-.LVL12
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL19-.LVL12
	.uleb128 .LVL20-.LVL12
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL23-.LVL22
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL23-.LVL22
	.uleb128 .LVL25-.LVL22
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL25-.LVL22
	.uleb128 .LVL27-.LVL22
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL27-.LVL22
	.uleb128 .LFE22-.LVL22
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL27-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL27-.LVL26
	.uleb128 .LFE22-.LVL26
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x9c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.4byte	0
	.4byte	0
	.section	.debug_rnglists,"",@progbits
.Ldebug_ranges0:
	.4byte	.Ldebug_ranges3-.Ldebug_ranges2
.Ldebug_ranges2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.LLRL5:
	.byte	0x5
	.4byte	.LBB23
	.byte	0x4
	.uleb128 .LBB23-.LBB23
	.uleb128 .LBE23-.LBB23
	.byte	0x4
	.uleb128 .LBB29-.LBB23
	.uleb128 .LBE29-.LBB23
	.byte	0x4
	.uleb128 .LBB30-.LBB23
	.uleb128 .LBE30-.LBB23
	.byte	0x4
	.uleb128 .LBB31-.LBB23
	.uleb128 .LBE31-.LBB23
	.byte	0x4
	.uleb128 .LBB32-.LBB23
	.uleb128 .LBE32-.LBB23
	.byte	0
.LLRL11:
	.byte	0x5
	.4byte	.LBB34
	.byte	0x4
	.uleb128 .LBB34-.LBB34
	.uleb128 .LBE34-.LBB34
	.byte	0x4
	.uleb128 .LBB35-.LBB34
	.uleb128 .LBE35-.LBB34
	.byte	0x4
	.uleb128 .LBB36-.LBB34
	.uleb128 .LBE36-.LBB34
	.byte	0x4
	.uleb128 .LBB37-.LBB34
	.uleb128 .LBE37-.LBB34
	.byte	0x4
	.uleb128 .LBB38-.LBB34
	.uleb128 .LBE38-.LBB34
	.byte	0
.LLRL13:
	.byte	0x7
	.4byte	.LFB18
	.uleb128 .LFE18-.LFB18
	.byte	0x7
	.4byte	.LFB15
	.uleb128 .LFE15-.LFB15
	.byte	0x7
	.4byte	.LFB16
	.uleb128 .LFE16-.LFB16
	.byte	0x7
	.4byte	.LFB17
	.uleb128 .LFE17-.LFB17
	.byte	0x7
	.4byte	.LFB19
	.uleb128 .LFE19-.LFB19
	.byte	0x7
	.4byte	.LFB20
	.uleb128 .LFE20-.LFB20
	.byte	0x7
	.4byte	.LFB21
	.uleb128 .LFE21-.LFB21
	.byte	0x7
	.4byte	.LFB22
	.uleb128 .LFE22-.LFB22
	.byte	0x7
	.4byte	.LFB23
	.uleb128 .LFE23-.LFB23
	.byte	0x7
	.4byte	.LFB25
	.uleb128 .LFE25-.LFB25
	.byte	0x7
	.4byte	.LFB24
	.uleb128 .LFE24-.LFB24
	.byte	0x7
	.4byte	.LFB27
	.uleb128 .LFE27-.LFB27
	.byte	0x7
	.4byte	.LFB29
	.uleb128 .LFE29-.LFB29
	.byte	0x7
	.4byte	.LFB30
	.uleb128 .LFE30-.LFB30
	.byte	0x7
	.4byte	.LFB26
	.uleb128 .LFE26-.LFB26
	.byte	0x7
	.4byte	.LFB28
	.uleb128 .LFE28-.LFB28
	.byte	0x7
	.4byte	.LFB31
	.uleb128 .LFE31-.LFB31
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF373:
	.string	"peripheral_sampling_last_handler"
.LASF184:
	.string	"outgoing_report_ready"
.LASF175:
	.string	"T_AIR_COMBO_KEY_S"
.LASF385:
	.string	"riscv_fake_report_check"
.LASF352:
	.string	"riscv_wheel_get_data"
.LASF291:
	.string	"hid_tx_buf_payload_size"
.LASF77:
	.string	"HID_CCNI_MSG_USB_PLUG_OUT"
.LASF128:
	.string	"APP_STATE_2_4G_CONNECTED_ACTIVE"
.LASF133:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1"
.LASF146:
	.string	"REMAP_TO_SCROLL_DOWN"
.LASF283:
	.string	"hid_tx_buf_queue"
.LASF172:
	.string	"T_HID_CCNI_USB_REPORT_S"
.LASF28:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF377:
	.string	"outgoing_data"
.LASF270:
	.string	"hwmt_last_anchor_ptr"
.LASF247:
	.string	"prev"
.LASF182:
	.string	"flags"
.LASF102:
	.string	"APP_STATE_CONNECT_PREPARING"
.LASF326:
	.string	"riscv_mouse_key_common_para_update"
.LASF235:
	.string	"read_key_timestamp"
.LASF39:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF309:
	.string	"FAKE_REPORT_RUNNING"
.LASF21:
	.string	"PRINT_LEVEL_DEBUG"
.LASF186:
	.string	"hid_shared_parameters"
.LASF344:
	.string	"key_remap_get_dpi_attr"
.LASF193:
	.string	"key_remap_enable"
.LASF261:
	.string	"NextTxPtr1"
.LASF36:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF384:
	.string	"peripheral_sampling_state_change_active"
.LASF248:
	.string	"next"
.LASF118:
	.string	"APP_STATE_BT_CONNECTED_ACTIVE"
.LASF92:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF349:
	.string	"riscv_wheel_post_process"
.LASF390:
	.string	"peripheral_sampling__check_condiction"
.LASF52:
	.string	"msg_id_handle"
.LASF253:
	.string	"head"
.LASF251:
	.string	"pka_share_dlist_stru"
.LASF54:
	.string	"DBG_PIN_SPI_CB"
.LASF86:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF211:
	.string	"hid_common"
.LASF110:
	.string	"APP_STATE_CONNECT_CANCEL_CHECK"
.LASF41:
	.string	"log_type_t"
.LASF150:
	.string	"repeat_times"
.LASF195:
	.string	"riscv_trigger_time"
.LASF389:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF79:
	.string	"HID_CCNI_MSG_INACTIVITY_TIMEOUT"
.LASF315:
	.string	"FN_KEY_DPI_SWITCH"
.LASF286:
	.string	"hid_tx_buf_start_ptr"
.LASF63:
	.string	"enable_mask"
.LASF37:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF59:
	.string	"DBG_PIN_USB_SOF"
.LASF201:
	.string	"hid_common_info"
.LASF357:
	.string	"hid_express_get_get_tx_result"
.LASF81:
	.string	"HID_CCNI_MSG_KEY_REMAP_TRIGGER"
.LASF204:
	.string	"DPI_STAGE_LOCK"
.LASF89:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF70:
	.string	"HID_CCNI_MSG_FEATURE_CONFIG"
.LASF369:
	.string	"new_state"
.LASF333:
	.string	"hal_gpt_sw_free_timer"
.LASF356:
	.string	"hal_gpt_sw_stop_timer_ms"
.LASF160:
	.string	"numeric_key_pad"
.LASF97:
	.string	"APP_STATE_NONE"
.LASF223:
	.string	"HAL_CCNI_STATUS_NO_INIT"
.LASF20:
	.string	"DEBUG_LOG_OFF"
.LASF310:
	.string	"FAKE_REPORT_COMPLETED"
.LASF116:
	.string	"APP_STATE_USB_DISCONNECTING"
.LASF135:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3"
.LASF105:
	.string	"APP_STATE_BT_RECONNECT"
.LASF90:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF177:
	.string	"step_2_4g"
.LASF24:
	.string	"PRINT_LEVEL_ERROR"
.LASF33:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF4:
	.string	"signed char"
.LASF224:
	.string	"HAL_CCNI_STATUS_OK"
.LASF127:
	.string	"APP_STATE_2_4G_CONNECTED"
.LASF367:
	.string	"peripheral_sampling_debug_print"
.LASF18:
	.string	"uint32_t"
.LASF332:
	.string	"hid_express_deinit"
.LASF96:
	.string	"T_HID_REPORT_RATE_VAL_S"
.LASF354:
	.string	"riscv_mouse_key_early_handle"
.LASF288:
	.string	"hid_tx_buf_payload_offset"
.LASF208:
	.string	"kb_std"
.LASF276:
	.string	"CurrentReportRate"
.LASF325:
	.string	"inActivity_time"
.LASF170:
	.string	"kb_std5"
.LASF27:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF98:
	.string	"APP_STATE_INITIALIZED"
.LASF394:
	.string	"pka_share_tx_buf_avail_num"
.LASF149:
	.string	"play_mode"
.LASF165:
	.string	"para"
.LASF173:
	.string	"combo_bit_00_31"
.LASF249:
	.string	"pka_share_DLIST_STRU"
.LASF232:
	.string	"APP_CHECK_CONNECTED_ACTIVE"
.LASF2:
	.string	"long long unsigned int"
.LASF372:
	.string	"peripheral_sampling_init"
.LASF88:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF334:
	.string	"hid_express_init"
.LASF259:
	.string	"common"
.LASF159:
	.string	"consumer"
.LASF45:
	.string	"f_tlv_dump_t"
.LASF157:
	.string	"combo"
.LASF67:
	.string	"HID_CCNI_MSG_FAKE_REPORT_ENABLE"
.LASF262:
	.string	"POFlow_ptr"
.LASF327:
	.string	"riscv_wheel_debug_print"
.LASF289:
	.string	"hid_tx_status_ptr"
.LASF34:
	.string	"LOG_TYPE_HCI_DATA"
.LASF210:
	.string	"T_OUTGOING_VALUES_S"
.LASF346:
	.string	"riscv_app_ccni_key_remap_send"
.LASF282:
	.string	"enable"
.LASF304:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF162:
	.string	"dummy"
.LASF144:
	.string	"REMAP_TO_DPI"
.LASF219:
	.string	"riscv_ps_callback_t"
.LASF40:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF71:
	.string	"HID_CCNI_MSG_HOGP_ATTR_HANDLE"
.LASF295:
	.string	"bt_info"
.LASF364:
	.string	"print_module_msgid_log"
.LASF229:
	.string	"APP_CHECK_NONE"
.LASF147:
	.string	"REMAP_TO_PAIRING"
.LASF198:
	.string	"app_shared_parameters"
.LASF246:
	.string	"pka_share_enable_t"
.LASF61:
	.string	"DBG_PIN_USB_TX"
.LASF275:
	.string	"TxRxDataRate"
.LASF312:
	.string	"SWITCH_RR"
.LASF64:
	.string	"T_COMMON_LA_DBG_S"
.LASF388:
	.string	"btn_pressed"
.LASF271:
	.string	"hwmt_last_anchor_phase_ptr"
.LASF143:
	.string	"REMAP_TO_RR"
.LASF199:
	.string	"mapped_data"
.LASF65:
	.string	"_Bool"
.LASF234:
	.string	"hid_exp_features"
.LASF277:
	.string	"mp_version"
.LASF345:
	.string	"key_remap_state_reset"
.LASF323:
	.string	"sampling_state"
.LASF154:
	.string	"T_HID_KEY_REMAP_S"
.LASF343:
	.string	"key_remap_get_key_status"
.LASF363:
	.string	"rv_fake_report__get_state"
.LASF228:
	.string	"PAIRING_STATE_CCNI_SEND"
.LASF30:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF19:
	.string	"DEBUG_LOG_ON"
.LASF168:
	.string	"kb_std2"
.LASF287:
	.string	"hid_tx_buf_queue_header_size"
.LASF84:
	.string	"HID_CCNI_MSG_POLLING_KEY_STATUS"
.LASF60:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF212:
	.string	"hid_flags"
.LASF191:
	.string	"irpt_ctrl"
.LASF163:
	.string	"T_HID_REPORT_KB_STD5_S"
.LASF374:
	.string	"key_status"
.LASF119:
	.string	"APP_STATE_BT_CONNECTED_IDLE_1"
.LASF120:
	.string	"APP_STATE_BT_CONNECTED_IDLE_2"
.LASF121:
	.string	"APP_STATE_BT_CONNECTED_IDLE_3"
.LASF93:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF300:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF197:
	.string	"mouse_key_num"
.LASF134:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2"
.LASF31:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF29:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF12:
	.string	"char"
.LASF35:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF355:
	.string	"hal_gpt_sw_start_timer_ms"
.LASF220:
	.string	"HAL_CCNI_STATUS_INVALID_PARAMETER"
.LASF359:
	.string	"riscv_app_ccin_send"
.LASF104:
	.string	"APP_STATE_2_4G_PAIRING"
.LASF16:
	.string	"uint8_t"
.LASF106:
	.string	"APP_STATE_2_4G_RECONNECT"
.LASF140:
	.string	"REMAP_KB_CONSUMER"
.LASF178:
	.string	"step_bt"
.LASF75:
	.string	"HID_CCNI_MSG_COMMON_PARA_UPDATE"
.LASF319:
	.string	"log_control_block_riscv_ps"
.LASF254:
	.string	"pka_share_OSMQ"
.LASF245:
	.string	"PKA_SHARE_ENABLE"
.LASF187:
	.string	"inActivity_timeout"
.LASF202:
	.string	"DPI_STAGE_PLUS"
.LASF342:
	.string	"riscv_mouse_key__ccni_send_status"
.LASF222:
	.string	"HAL_CCNI_STATUS_ERROR"
.LASF298:
	.string	"hal_gpt_callback_t"
.LASF330:
	.string	"riscv_wheel__app_state_update"
.LASF42:
	.string	"f_print_t"
.LASF256:
	.string	"hwmt_pico_offset_ptr"
.LASF153:
	.string	"status"
.LASF339:
	.string	"riscv_wheel_init"
.LASF338:
	.string	"riscv_motion_sensor_init"
.LASF231:
	.string	"APP_CHECK_CONNECTED_IDLE"
.LASF82:
	.string	"HID_CCNI_MSG_FAKE_REPORT_TERMINATE"
.LASF392:
	.string	"send_result"
.LASF91:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF255:
	.string	"flag_ptr"
.LASF142:
	.string	"MACRO_CONTINUE"
.LASF329:
	.string	"hid_express_set_report_rate_idx"
.LASF180:
	.string	"hid_scenario_type"
.LASF176:
	.string	"step_wired"
.LASF85:
	.string	"HID_CCNI_MSG_POLLING_WHEEL_STATUS"
.LASF10:
	.string	"long long int"
.LASF360:
	.string	"riscv_app_ccin_fake_data_disable"
.LASF200:
	.string	"outgoing_report"
.LASF358:
	.string	"hid_express_get_hid_flag"
.LASF350:
	.string	"riscv_mouse_key_get_key_status"
.LASF370:
	.string	"peripheral_sampling_deinit"
.LASF167:
	.string	"ms_s16_z8"
.LASF273:
	.string	"acl_active_state_ptr"
.LASF269:
	.string	"hwmt_cur_idx_ptr"
.LASF43:
	.string	"f_dump_buffer_t"
.LASF115:
	.string	"APP_STATE_USB_ENTERING_ACTIVE"
.LASF376:
	.string	"ps_cb_type"
.LASF368:
	.string	"check_type"
.LASF264:
	.string	"CurTxPtr"
.LASF137:
	.string	"NO_REMAP"
.LASF241:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF107:
	.string	"APP_STATE_2_4G_QUICK_CONNECT"
.LASF263:
	.string	"pka_share_bt_info_le"
.LASF174:
	.string	"combo_bit_32_63"
.LASF95:
	.string	"rr_idx_usb"
.LASF348:
	.string	"hid_express_get_outgpoig_report_result"
.LASF190:
	.string	"hold_timeout"
.LASF381:
	.string	"peripheral_sampling_inactivity_timeout"
.LASF238:
	.string	"T_RISCV_APP_S"
.LASF22:
	.string	"PRINT_LEVEL_INFO"
.LASF57:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF58:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF188:
	.string	"combo_key_list"
.LASF227:
	.string	"PAIRING_STATE_CHECK_BUFFER"
.LASF322:
	.string	"inActivity_gpt_hdl"
.LASF293:
	.string	"cb_type"
.LASF281:
	.string	"pka_share_bt_info"
.LASF196:
	.string	"mouse_key_list"
.LASF244:
	.string	"PKA_SHARE_DISABLE"
.LASF239:
	.string	"riscv_app"
.LASF347:
	.string	"key_remap_get_process_status"
.LASF13:
	.string	"int8_t"
.LASF194:
	.string	"key_remap_fn_key"
.LASF221:
	.string	"HAL_CCNI_STATUS_BUSY"
.LASF101:
	.string	"APP_STATE_TEST"
.LASF393:
	.string	"peripheral_sampling_pairing_state_change"
.LASF365:
	.string	"msg_id_string"
.LASF361:
	.string	"rv_fake_report_config"
.LASF80:
	.string	"HID_CCNI_MSG_FORCE_ALL_KEY_RELEASED"
.LASF297:
	.string	"pka_share_ptr"
.LASF183:
	.string	"features"
.LASF145:
	.string	"REMAP_TO_SCROLL_UP"
.LASF215:
	.string	"HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL"
.LASF324:
	.string	"pairing_state"
.LASF192:
	.string	"scroll_ctrl"
.LASF302:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF311:
	.string	"STATUS_NONE"
.LASF50:
	.string	"dump_handle"
.LASF108:
	.string	"APP_STATE_2_4G_RECONNECT_RESUME_WAIT"
.LASF258:
	.string	"pka_share_bt_info_common"
.LASF11:
	.string	"long double"
.LASF321:
	.string	"inactivity_counter"
.LASF17:
	.string	"uint16_t"
.LASF68:
	.string	"HID_CCNI_MSG_FAKE_REPORT_CONFIG"
.LASF379:
	.string	"peripheral_sampling_pairing_check"
.LASF209:
	.string	"kb_consumer"
.LASF141:
	.string	"MACRO_REMAP"
.LASF123:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_1"
.LASF124:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_2"
.LASF125:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_3"
.LASF299:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF266:
	.string	"CandiTxPtr"
.LASF292:
	.string	"hid_tx_buf_num"
.LASF51:
	.string	"tlv_dump_handle"
.LASF351:
	.string	"riscv_wheel_trigger_read_process"
.LASF378:
	.string	"peripheral_sampling_idle_check"
.LASF164:
	.string	"T_HID_REPORT_KB_CONSUMER2_S"
.LASF23:
	.string	"PRINT_LEVEL_WARNING"
.LASF112:
	.string	"APP_STATE_USB_ACTIVE"
.LASF318:
	.string	"WHEEL_PAIRING_KEY"
.LASF47:
	.string	"log_switch"
.LASF179:
	.string	"T_DEBOUNCE_PARA_S"
.LASF6:
	.string	"short int"
.LASF290:
	.string	"hid_forced_nack_status_ptr"
.LASF69:
	.string	"HID_CCNI_MSG_KEY_REMAP_CONFIG"
.LASF243:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF207:
	.string	"k_old"
.LASF306:
	.string	"HAL_GPT_STATUS_OK"
.LASF265:
	.string	"NextTxPtr"
.LASF8:
	.string	"long int"
.LASF169:
	.string	"kb_consumer1"
.LASF171:
	.string	"kb_consumer2"
.LASF158:
	.string	"T_HID_REPORT_KB_STD2_XY_S"
.LASF387:
	.string	"fake_report_state"
.LASF226:
	.string	"PAIRING_STATE_SEND_REPORT"
.LASF87:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF14:
	.string	"int16_t"
.LASF214:
	.string	"HID_EXP_2ND_CB"
.LASF100:
	.string	"APP_STATE_DISCONNECTED"
.LASF305:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF308:
	.string	"FAKE_REPORT_DISABLED"
.LASF55:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF335:
	.string	"hal_gpt_sw_get_timer"
.LASF386:
	.string	"flag"
.LASF284:
	.string	"hid_tx_buf_sending_queue"
.LASF285:
	.string	"hid_tx_buf_ack_pending_queue"
.LASF122:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_ACTIVE"
.LASF303:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF139:
	.string	"REMAP_KB_STD"
.LASF294:
	.string	"req_rscv_ctl_int"
.LASF72:
	.string	"HID_CCNI_MSG_SET_DBG_PIN"
.LASF49:
	.string	"print_handle"
.LASF301:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF217:
	.string	"HID_EXP_NO_REPORT_PROCESS"
.LASF314:
	.string	"SWITCH_DPI_STOP"
.LASF260:
	.string	"NextTxPtr0"
.LASF203:
	.string	"DPI_STAGE_MINUS"
.LASF185:
	.string	"delay_for_key_polling_ms"
.LASF74:
	.string	"HID_CCNI_MSG_SET_FEATURE"
.LASF225:
	.string	"hal_ccni_status_t"
.LASF3:
	.string	"unsigned int"
.LASF66:
	.string	"HID_CCNI_MSG_APP_STATE"
.LASF380:
	.string	"peripheral_sampling_all_key_release_ccni_send"
.LASF73:
	.string	"HID_CCNI_MSG_SET_OUTPUT_CTRL_PIN"
.LASF382:
	.string	"user_data"
.LASF126:
	.string	"APP_STATE_BT_DISCONNECTING"
.LASF320:
	.string	"log_control_block_mirror_riscv_ps"
.LASF353:
	.string	"riscv_motion_sensor_data_get"
.LASF53:
	.string	"log_control_block_t"
.LASF151:
	.string	"macro"
.LASF278:
	.string	"max_pdu_len_ptr"
.LASF9:
	.string	"long unsigned int"
.LASF371:
	.string	"peripheral_sampling_app_state_update"
.LASF136:
	.string	"APP_STATE_2_4G_DISCONNECTING"
.LASF76:
	.string	"HID_CCNI_MSG_WAKEUP_KEY"
.LASF15:
	.string	"int32_t"
.LASF375:
	.string	"peripheral_sampling_handler"
.LASF250:
	.string	"pka_share_DLIST_HEAD"
.LASF38:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF296:
	.string	"pka_share_info"
.LASF307:
	.string	"hal_gpt_status_t"
.LASF340:
	.string	"hid_common_get_hid_exp_features"
.LASF206:
	.string	"type"
.LASF129:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_1"
.LASF130:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_2"
.LASF328:
	.string	"riscv_mouse_key_debug_print"
.LASF5:
	.string	"unsigned char"
.LASF132:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE"
.LASF94:
	.string	"rr_idx_2_4g"
.LASF138:
	.string	"REMAP_MS_KEY"
.LASF366:
	.string	"peripheral_sampling_common_para_update"
.LASF26:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF313:
	.string	"SWITCH_DPI"
.LASF46:
	.string	"module_name"
.LASF103:
	.string	"APP_STATE_BT_PAIRING"
.LASF391:
	.string	"peripheral_sampling__need_early_key_handle_in_wireless_mode"
.LASF156:
	.string	"T_HID_REPORT_MS_K8_S16_Z8_S"
.LASF240:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF237:
	.string	"state"
.LASF218:
	.string	"T_PS_CB_TYPE_E"
.LASF166:
	.string	"T_OUTPUT_CTRL_PIN_INFO_S"
.LASF78:
	.string	"HID_CCNI_MSG_KEY"
.LASF272:
	.string	"hwmt_tpollgo_ptr"
.LASF32:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF274:
	.string	"MaxHidTxPktByRR"
.LASF113:
	.string	"APP_STATE_USB_SUSPEND"
.LASF236:
	.string	"rr_idx"
.LASF189:
	.string	"combo_key_list_size"
.LASF152:
	.string	"item"
.LASF316:
	.string	"PRESS_PAIRING_KEY"
.LASF233:
	.string	"APP_CHECK_USB_MODE"
.LASF213:
	.string	"HID_EXP_1ST_CB"
.LASF48:
	.string	"print_level"
.LASF83:
	.string	"HID_CCNI_MSG_PRINT_HID_REPORT_REQ"
.LASF117:
	.string	"APP_STATE_BT_CONNECTED"
.LASF242:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF44:
	.string	"f_msg_id_t"
.LASF99:
	.string	"APP_STATE_STANDBY"
.LASF114:
	.string	"APP_STATE_USB_STOP"
.LASF267:
	.string	"HidTxPktPtr"
.LASF7:
	.string	"short unsigned int"
.LASF341:
	.string	"riscv_mouse_key_post_process"
.LASF56:
	.string	"DBG_PIN_NACK"
.LASF161:
	.string	"T_HID_REPORT_KB_CONSUMER1_XY_S"
.LASF62:
	.string	"DBG_PIN_MAX"
.LASF205:
	.string	"DPI_STAGE_LOOP"
.LASF252:
	.string	"pka_share_osmq_stru"
.LASF230:
	.string	"APP_CHECK_8K_CONNECTED"
.LASF336:
	.string	"hid_express_set_features"
.LASF268:
	.string	"EmptyPktPtr"
.LASF216:
	.string	"HID_EXP_4TH_CB_POST_PROCESS"
.LASF111:
	.string	"APP_STATE_USB_CONNECTED"
.LASF331:
	.string	"riscv_mouse_key__app_state_update"
.LASF279:
	.string	"pka_share_bt_info_rt"
.LASF383:
	.string	"peripheral_sampling_set_inActivity_timeout"
.LASF148:
	.string	"keycode"
.LASF109:
	.string	"APP_STATE_CONNECT_CANCEL"
.LASF155:
	.string	"report_id"
.LASF337:
	.string	"riscv_mouse_key_init"
.LASF317:
	.string	"UPDATE_PAIRING_KEY"
.LASF280:
	.string	"pka_share_bt_info_rtt"
.LASF362:
	.string	"riscv_mouse_keys_is_new_key_pressed"
.LASF25:
	.string	"print_level_t"
.LASF131:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_3"
.LASF257:
	.string	"hwmt_pico_offset_phase_ptr"
.LASF181:
	.string	"dongle_scenario"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_peripheral_sampling.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
