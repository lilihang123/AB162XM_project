	.file	"riscv_ccni.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_ccni.c"
	.section	.text.rv_sleep_lock_request,"ax",@progbits
	.align	1
	.globl	rv_sleep_lock_request
	.hidden	rv_sleep_lock_request
	.type	rv_sleep_lock_request, @function
rv_sleep_lock_request:
.LFB6:
	.file 1 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_ccni.c"
	.loc 1 87 1
	.cfi_startproc
.LVL0:
	.loc 1 88 5
	.loc 1 90 5
	.loc 1 87 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	s1,4(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 90 45 discriminator 1
	lla	s1,risv_app_sleep_lock_status
	lbu	a5,0(s1)
	.loc 1 87 1
	mv	s0,a0
	.loc 1 90 8
	beq	a0,zero,.L2
	.loc 1 88 32
	li	a0,0
.LVL1:
	.loc 1 90 14 discriminator 1
	bne	a5,zero,.L3
	.loc 1 91 9 is_stmt 1
	.loc 1 92 15 is_stmt 0
	li	a0,23
	.loc 1 91 36
	sb	s0,0(s1)
	.loc 1 92 9 is_stmt 1
	.loc 1 92 15 is_stmt 0
	call	hal_sleep_manager_lock_sleep
.LVL2:
.L3:
	.loc 1 99 5 is_stmt 1
.LBB2:
	.loc 1 99 10
	.loc 1 99 65
	.loc 1 99 266
	sw	a0,0(sp)
	lbu	a5,0(s1)
	mv	a4,s0
	li	a3,3
	lla	a2,msg_id_string.3
	li	a1,1
	lla	a0,log_control_block_riscv_ps
.LVL3:
	call	print_module_msgid_log
.LVL4:
.LBE2:
	.loc 1 99 8 discriminator 1
	.loc 1 105 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL5:
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL6:
.L2:
	.cfi_restore_state
	.loc 1 88 32
	li	a0,0
	.loc 1 94 29 discriminator 1
	beq	a5,zero,.L3
	.loc 1 95 9 is_stmt 1
	.loc 1 96 15 is_stmt 0
	li	a0,23
	.loc 1 95 36
	sb	zero,risv_app_sleep_lock_status,a5
	.loc 1 96 9 is_stmt 1
	.loc 1 96 15 is_stmt 0
	call	hal_sleep_manager_unlock_sleep
.LVL7:
	j	.L3
	.cfi_endproc
.LFE6:
	.size	rv_sleep_lock_request, .-rv_sleep_lock_request
	.section	.text.hal_ccni_event_callback3,"ax",@progbits
	.align	1
	.globl	hal_ccni_event_callback3
	.hidden	hal_ccni_event_callback3
	.type	hal_ccni_event_callback3, @function
hal_ccni_event_callback3:
.LFB7:
	.loc 1 109 1 is_stmt 1
	.cfi_startproc
.LVL8:
	.loc 1 110 5
	.loc 1 110 28 is_stmt 0
	li	a4,1
	sb	a4,g_riscv_ccni_irq_occur,a3
	.loc 1 111 5 is_stmt 1
.LVL9:
	.loc 1 113 5
	lbu	a4,0(a1)
	li	a3,12
	addi	a4,a4,-16
	andi	a4,a4,0xff
	bgtu	a4,a3,.L37
	lla	a3,.L11
	slli	a4,a4,2
	add	a4,a4,a3
	lw	a4,0(a4)
	.loc 1 109 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.loc 1 113 5
	add	a4,a4,a3
	.loc 1 109 1
	sw	s0,4(sp)
	sw	s1,0(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	mv	a5,a1
	.loc 1 113 5
	jr	a4
	.section	.rodata.hal_ccni_event_callback3,"a",@progbits
	.align	2
	.align	2
.L11:
	.word	.L19-.L11
	.word	.L18-.L11
	.word	.L17-.L11
	.word	.L16-.L11
	.word	.L8-.L11
	.word	.L15-.L11
	.word	.L8-.L11
	.word	.L8-.L11
	.word	.L8-.L11
	.word	.L14-.L11
	.word	.L13-.L11
	.word	.L12-.L11
	.word	.L10-.L11
	.section	.text.hal_ccni_event_callback3
.L19:
.LBB3:
	.loc 1 117 13 is_stmt 1
	.loc 1 117 48 is_stmt 0
	lw	s1,0(a1)
.LBB4:
	.loc 1 118 220
	li	a3,1
	lla	a2,msg_id_string.2
.LBE4:
	.loc 1 117 48
	srli	s1,s1,8
	.loc 1 117 22
	andi	s0,s1,255
.LVL10:
	.loc 1 118 13 is_stmt 1
.LBB5:
	.loc 1 118 18
	.loc 1 118 73
	.loc 1 118 220
	mv	a4,s0
	li	a1,1
.LVL11:
	lla	a0,log_control_block_riscv_ps
.LVL12:
	call	print_module_msgid_log
.LVL13:
.LBE5:
	.loc 1 118 16 discriminator 1
	.loc 1 119 13
	mv	a0,s0
	call	riscv_mouse_key_change_state
.LVL14:
	.loc 1 120 13
	li	a5,34
	beq	s0,a5,.L42
	bgtu	s0,a5,.L21
	li	a5,19
	bgtu	s0,a5,.L22
	andi	s1,s1,254
	beq	s1,zero,.L23
	addi	a5,s0,-2
	li	a4,17
	bgtu	a5,a4,.L23
	lla	a4,.L25
	slli	a5,a5,2
	add	a5,a5,a4
	lw	a5,0(a5)
	add	a5,a5,a4
	jr	a5
	.section	.rodata.hal_ccni_event_callback3
	.align	2
	.align	2
.L25:
	.word	.L28-.L25
	.word	.L27-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L26-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L42-.L25
	.word	.L42-.L25
	.word	.L42-.L25
	.word	.L24-.L25
	.section	.text.hal_ccni_event_callback3
.L22:
	li	a5,33
	beq	s0,a5,.L29
.L23:
	.loc 1 262 13
	mv	a0,s0
	call	peripheral_sampling_app_state_update
.LVL15:
	.loc 1 263 13
	.loc 1 263 28 is_stmt 0
	sw	s0,last_app_state,a5
.LBE3:
	.loc 1 265 9 is_stmt 1
.LVL16:
.L8:
	.loc 1 339 1 is_stmt 0
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
.LVL17:
.L21:
	.cfi_restore_state
.LBB6:
	li	a5,128
	beq	s0,a5,.L42
	bgtu	s0,a5,.L30
	li	a5,65
	beq	s0,a5,.L31
	andi	s1,s1,253
	li	a5,64
	bne	s1,a5,.L23
.L42:
	.loc 1 134 21 is_stmt 1
	li	a0,1
	j	.L40
.L30:
	li	a5,129
	beq	s0,a5,.L31
	li	a5,131
	beq	s0,a5,.L42
	j	.L23
.L28:
	.loc 1 124 21
	li	a0,0
.L40:
	.loc 1 134 21 is_stmt 0
	call	rv_sleep_lock_request
.LVL18:
	.loc 1 136 17 is_stmt 1
	j	.L23
.L27:
	.loc 1 130 21
	li	a0,9
	call	hid_common_clear_hid_exp_flag
.LVL19:
	.loc 1 132 21
	call	hid_experss_bt_clear_queue
.LVL20:
	j	.L42
.L26:
	.loc 1 140 21
	call	peripheral_sampling_init
.LVL21:
	.loc 1 145 17
	j	.L23
.L24:
	.loc 1 157 21
	li	a0,1
	call	rv_sleep_lock_request
.LVL22:
	.loc 1 158 21
	call	hid_common_get_dongle_scenario
.LVL23:
	.loc 1 158 21 is_stmt 0 discriminator 1
	call	hid_express_dongle_scenario_update
.LVL24:
	.loc 1 160 17 is_stmt 1
	j	.L23
.L29:
	.loc 1 174 21
	li	a0,1
	call	rv_sleep_lock_request
.LVL25:
	.loc 1 175 21
	call	hid_express_clear_key_pushed
.LVL26:
	.loc 1 176 21
.L41:
	.loc 1 196 21
	call	peripheral_sampling_state_change_active
.LVL27:
	.loc 1 198 17
	j	.L23
.L31:
	.loc 1 195 21
	li	a0,1
	call	rv_sleep_lock_request
.LVL28:
	j	.L41
.LVL29:
.L18:
.LBE6:
	.loc 1 270 13
	.loc 1 339 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	.loc 1 270 13
	lw	a2,3(a1)
	.loc 1 339 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
	.loc 1 270 13
	lbu	a1,2(a1)
.LVL30:
	lbu	a0,1(a5)
.LVL31:
	.loc 1 339 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 270 13
	tail	rv_fake_report_config
.LVL32:
.L16:
	.cfi_restore_state
	.loc 1 278 13 is_stmt 1
	call	key_remap_frontend_setting_update
.LVL33:
	.loc 1 279 13
	.loc 1 339 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 279 13
	tail	key_remap_backend_setting
.LVL34:
.L17:
	.cfi_restore_state
.LBB7:
	.loc 1 287 13 is_stmt 1
	.loc 1 288 13
	.loc 1 289 13
.LBE7:
	.loc 1 339 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
.LBB8:
	.loc 1 289 13
	lw	a0,1(a1)
.LVL35:
.LBE8:
	.loc 1 339 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
.LBB9:
	.loc 1 289 13
	tail	rv_fake_report_set
.LVL36:
.L15:
	.cfi_restore_state
.LBE9:
	.loc 1 297 13 is_stmt 1
	.loc 1 339 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	.loc 1 297 13
	lbu	a2,3(a1)
	.loc 1 339 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
	.loc 1 297 13
	lbu	a1,2(a1)
.LVL37:
	lbu	a0,1(a5)
.LVL38:
	.loc 1 339 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 297 13
	tail	hid_experss_bt_set_attr_handle
.LVL39:
.L14:
	.cfi_restore_state
	.loc 1 304 13 is_stmt 1
	.loc 1 339 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 304 13
	tail	peripheral_sampling_common_para_update
.LVL40:
.L13:
	.cfi_restore_state
	.loc 1 310 13 is_stmt 1
	.loc 1 310 15 is_stmt 0
	lbu	a4,2(a1)
	.loc 1 313 17
	li	a1,0
.LVL41:
	.loc 1 310 15
	beq	a4,zero,.L43
	.loc 1 318 17 is_stmt 1
	lbu	a0,1(a5)
.LVL42:
	call	riscv_mouse_key_id_to_key_status
.LVL43:
	mv	a1,a0
.L43:
	.loc 1 318 17 is_stmt 0 discriminator 1
	li	a0,0
.L44:
	.loc 1 339 1
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 318 17 discriminator 1
	tail	hid_express__push_to_key_queue
.LVL44:
.L10:
	.cfi_restore_state
	.loc 1 326 13 is_stmt 1
	lw	a1,2(a1)
.LVL45:
	lbu	a0,1(a5)
.LVL46:
	j	.L44
.LVL47:
.L12:
	.loc 1 332 13
	.loc 1 339 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 332 13
	tail	peripheral_sampling_state_change_active
.LVL48:
.L37:
	ret
	.cfi_endproc
.LFE7:
	.size	hal_ccni_event_callback3, .-hal_ccni_event_callback3
	.section	.text.riscv_app_ccin_init,"ax",@progbits
	.align	1
	.globl	riscv_app_ccin_init
	.hidden	riscv_app_ccin_init
	.type	riscv_app_ccin_init, @function
riscv_app_ccin_init:
.LFB8:
	.loc 1 342 1 is_stmt 1
	.cfi_startproc
	.loc 1 343 5
	li	a0,16908288
	addi	a0,a0,3
	tail	hal_ccni_unmask_event
.LVL49:
	.cfi_endproc
.LFE8:
	.size	riscv_app_ccin_init, .-riscv_app_ccin_init
	.section	.text.riscv_app_ccin_send,"ax",@progbits
	.align	1
	.globl	riscv_app_ccin_send
	.hidden	riscv_app_ccin_send
	.type	riscv_app_ccin_send, @function
riscv_app_ccin_send:
.LFB9:
	.loc 1 347 1
	.cfi_startproc
.LVL50:
	.loc 1 348 5
	.loc 1 349 5
	.loc 1 351 5
	.loc 1 351 8 is_stmt 0
	li	a4,8
	bgtu	a1,a4,.L53
	mv	a5,a0
	.loc 1 352 16
	li	a0,-4
.LVL51:
	.loc 1 351 19 discriminator 1
	beq	a5,zero,.L56
	.loc 1 347 1
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	mv	a2,a1
	.loc 1 355 5 is_stmt 1
	addi	a0,sp,4
	mv	a1,a5
.LVL52:
	.loc 1 347 1 is_stmt 0
	sw	ra,20(sp)
	sw	s0,16(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 355 5
	call	memcpy
.LVL53:
	.loc 1 357 5 is_stmt 1
	.loc 1 357 14 is_stmt 0
	li	a0,33619968
	addi	a1,sp,4
	addi	a0,a0,3
	call	hal_ccni_set_event
.LVL54:
	.loc 1 359 5 is_stmt 1
	.loc 1 359 7 is_stmt 0
	li	a5,-3
	bne	a0,a5,.L46
.LBB10:
	.loc 1 361 9 is_stmt 1
.LVL55:
	.loc 1 362 9
	.loc 1 362 18 is_stmt 0
	li	a5,1
	sw	a5,0(sp)
	.loc 1 363 9 is_stmt 1
	.loc 1 361 18 is_stmt 0
	li	s0,0
.LVL56:
.L48:
	.loc 1 363 52 is_stmt 1
	lw	a4,0(sp)
	li	a5,1
	bne	a4,a5,.L49
	.loc 1 363 52 is_stmt 0 discriminator 1
	li	a5,1000
	bne	s0,a5,.L50
.L51:
.LBB11:
	.loc 1 367 81 is_stmt 1 discriminator 1
	.loc 1 367 235 discriminator 1
	.loc 1 367 393 discriminator 1
	li	a2,367
	lla	a1,file.0
	lla	a0,exp.1
	call	light_assert
.LVL57:
	j	.L52
.L50:
.LBE11:
	.loc 1 364 13
	.loc 1 364 22 is_stmt 0
	addi	s0,s0,1
.LVL58:
	.loc 1 365 13
	li	a0,33619968
	.loc 1 364 22
	slli	s0,s0,16
.LVL59:
	.loc 1 365 13
	mv	a1,sp
	addi	a0,a0,3
	.loc 1 364 22
	srli	s0,s0,16
.LVL60:
	.loc 1 365 13 is_stmt 1
	call	hal_ccni_query_event_status
.LVL61:
	j	.L48
.L49:
	.loc 1 367 9
	.loc 1 367 11 is_stmt 0
	li	a5,1000
	beq	s0,a5,.L51
.L52:
	.loc 1 367 424 is_stmt 1 discriminator 3
	.loc 1 369 9
	.loc 1 369 18 is_stmt 0
	li	a0,33619968
	addi	a1,sp,4
	addi	a0,a0,3
	call	hal_ccni_set_event
.LVL62:
.L46:
.LBE10:
	.loc 1 373 1
	lw	ra,20(sp)
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
	jr	ra
.LVL63:
.L53:
	.loc 1 352 16
	li	a0,-4
.LVL64:
	ret
.LVL65:
.L56:
	.loc 1 373 1
	ret
	.cfi_endproc
.LFE9:
	.size	riscv_app_ccin_send, .-riscv_app_ccin_send
	.section	.text.riscv_app_ccin_fake_data_disable,"ax",@progbits
	.align	1
	.globl	riscv_app_ccin_fake_data_disable
	.hidden	riscv_app_ccin_fake_data_disable
	.type	riscv_app_ccin_fake_data_disable, @function
riscv_app_ccin_fake_data_disable:
.LFB10:
	.loc 1 376 1 is_stmt 1
	.cfi_startproc
	.loc 1 377 5
	.loc 1 378 5
	.loc 1 376 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 378 12
	li	a5,-124
	.loc 1 380 5
	mv	a0,sp
	li	a1,1
	.loc 1 376 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 378 12
	sb	a5,0(sp)
	.loc 1 380 5 is_stmt 1
	call	riscv_app_ccin_send
.LVL66:
	.loc 1 381 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE10:
	.size	riscv_app_ccin_fake_data_disable, .-riscv_app_ccin_fake_data_disable
	.section	.text.riscv_app_ccni_key_remap_send,"ax",@progbits
	.align	1
	.globl	riscv_app_ccni_key_remap_send
	.hidden	riscv_app_ccni_key_remap_send
	.type	riscv_app_ccni_key_remap_send, @function
riscv_app_ccni_key_remap_send:
.LFB11:
	.loc 1 401 1 is_stmt 1
	.cfi_startproc
.LVL67:
	.loc 1 402 5
	.loc 1 403 5
	.loc 1 401 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	.loc 1 405 12
	sh	a1,2(sp)
	.loc 1 407 24
	srli	a1,a1,16
.LVL68:
	.loc 1 404 12
	sb	a0,1(sp)
	.loc 1 407 12
	sb	a1,4(sp)
	.loc 1 403 12
	li	a5,-125
	.loc 1 409 5
	mv	a0,sp
.LVL69:
	li	a1,5
	.loc 1 401 1
	sw	ra,16(sp)
	.cfi_offset 1, -4
	.loc 1 403 12
	sb	a5,0(sp)
	.loc 1 404 5 is_stmt 1
	.loc 1 405 5
	.loc 1 406 5
	.loc 1 407 5
	.loc 1 409 5
	call	riscv_app_ccin_send
.LVL70:
	.loc 1 411 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_restore 1
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	riscv_app_ccni_key_remap_send, .-riscv_app_ccni_key_remap_send
	.section	.log_string,"a"
	.align	2
	.type	file.0, @object
	.size	file.0, 83
file.0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_ccni.c"
	.align	2
	.type	exp.1, @object
	.size	exp.1, 78
exp.1:
	.string	"(retry_cnt < MAX_CCNI_STATUS_RETRY_CNT) && \"Error : RISC-V busy for too long\""
	.align	2
	.type	msg_id_string.2, @object
	.size	msg_id_string.2, 54
msg_id_string.2:
	.string	"[M:riscv_ps C:info F: L: ]: ======== app_state = 0x%x"
	.align	2
	.type	msg_id_string.3, @object
	.size	msg_id_string.3, 108
msg_id_string.3:
	.string	"[M:riscv_ps C:info F: L: ]: rv_sleep_lock_request, lock req = %d, risv_app_sleep_lock_status = %d, ret = %d"
	.hidden	risv_app_sleep_lock_status
	.globl	risv_app_sleep_lock_status
	.section	.sbss.risv_app_sleep_lock_status,"aw",@nobits
	.type	risv_app_sleep_lock_status, @object
	.size	risv_app_sleep_lock_status, 1
risv_app_sleep_lock_status:
	.zero	1
	.hidden	last_app_state
	.globl	last_app_state
	.section	.sbss.last_app_state,"aw",@nobits
	.align	2
	.type	last_app_state, @object
	.size	last_app_state, 4
last_app_state:
	.zero	4
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 6 "/workdir/airoha/common/applications/hid/inc/hid_common_ccni_msg.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 8 "/workdir/airoha/common/applications/hid/inc/hid_common_hid_app_states.h"
	.file 9 "/workdir/airoha/common/drivers/chip/ab162x/../inc/hal_ccni.h"
	.file 10 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_ccni_config.h"
	.file 11 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_key_queue_mouse.h"
	.file 12 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager.h"
	.file 13 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 14 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.file 15 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_mouse_key.h"
	.file 16 "/workdir/airoha/risc-v/kernel/service/exception_handler/inc/exception_handler.h"
	.file 17 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 18 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_bt_mode.h"
	.file 19 "/workdir/airoha/common/middleware/airoha/hid_express/inc/rv_fake_report.h"
	.file 20 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_peripheral_sampling.h"
	.file 21 "/workdir/airoha/common/middleware/airoha/key_remap/inc/key_remap_backend.h"
	.file 22 "/workdir/airoha/common/middleware/airoha/key_remap/inc/key_remap_frontend.h"
	.file 23 "/workdir/airoha/common/applications/hid/inc/hid_common.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xea0
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x2a
	.4byte	.LASF255
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL16
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x4
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x4
	.byte	0x1
	.byte	0x6
	.4byte	.LASF5
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x4
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x4
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x2b
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x2
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0x4
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x2c
	.byte	0x4
	.uleb128 0x1f
	.4byte	0x7f
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x11
	.4byte	0x86
	.uleb128 0x8
	.4byte	0x8d
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x34
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x3
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x3d
	.byte	0xe
	.4byte	0xe1
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF21
	.byte	0x4
	.byte	0x42
	.byte	0x3
	.4byte	0xbb
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x45
	.byte	0xe
	.4byte	0x155
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x3f
	.byte	0
	.uleb128 0x5
	.4byte	.LASF37
	.byte	0x4
	.byte	0x57
	.byte	0x3
	.4byte	0xed
	.uleb128 0x5
	.4byte	.LASF38
	.byte	0x4
	.byte	0x59
	.byte	0x10
	.4byte	0x16d
	.uleb128 0x8
	.4byte	0x172
	.uleb128 0x16
	.4byte	0x192
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xe1
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x6
	.byte	0
	.uleb128 0x5
	.4byte	.LASF39
	.byte	0x4
	.byte	0x5a
	.byte	0x10
	.4byte	0x19e
	.uleb128 0x8
	.4byte	0x1a3
	.uleb128 0x16
	.4byte	0x1cd
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xe1
	.uleb128 0x2
	.4byte	0x1cd
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x6
	.byte	0
	.uleb128 0x8
	.4byte	0x1d7
	.uleb128 0x1f
	.4byte	0x1cd
	.uleb128 0x2d
	.uleb128 0x5
	.4byte	.LASF40
	.byte	0x4
	.byte	0x5b
	.byte	0x10
	.4byte	0x1e4
	.uleb128 0x8
	.4byte	0x1e9
	.uleb128 0x16
	.4byte	0x204
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0xe1
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x2
	.4byte	0xaf
	.uleb128 0x6
	.byte	0
	.uleb128 0x5
	.4byte	.LASF41
	.byte	0x4
	.byte	0x5c
	.byte	0x14
	.4byte	0x210
	.uleb128 0x8
	.4byte	0x215
	.uleb128 0x2e
	.4byte	0xaf
	.4byte	0x238
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0xe1
	.uleb128 0x2
	.4byte	0x155
	.uleb128 0x2
	.4byte	0x238
	.uleb128 0x2
	.4byte	0x23d
	.byte	0
	.uleb128 0x8
	.4byte	0x1cd
	.uleb128 0x8
	.4byte	0xaf
	.uleb128 0x2f
	.byte	0x1c
	.byte	0x4
	.byte	0x5e
	.byte	0x9
	.4byte	0x2a0
	.uleb128 0xc
	.4byte	.LASF42
	.byte	0x5f
	.byte	0x11
	.4byte	0x92
	.byte	0
	.uleb128 0xc
	.4byte	.LASF43
	.byte	0x60
	.byte	0xe
	.4byte	0xaf
	.byte	0x4
	.uleb128 0xc
	.4byte	.LASF44
	.byte	0x61
	.byte	0xe
	.4byte	0xaf
	.byte	0x8
	.uleb128 0xc
	.4byte	.LASF45
	.byte	0x62
	.byte	0xf
	.4byte	0x161
	.byte	0xc
	.uleb128 0xc
	.4byte	.LASF46
	.byte	0x63
	.byte	0x15
	.4byte	0x192
	.byte	0x10
	.uleb128 0xc
	.4byte	.LASF47
	.byte	0x64
	.byte	0x12
	.4byte	0x204
	.byte	0x14
	.uleb128 0xc
	.4byte	.LASF48
	.byte	0x65
	.byte	0x10
	.4byte	0x1d8
	.byte	0x18
	.byte	0
	.uleb128 0x5
	.4byte	.LASF49
	.byte	0x4
	.byte	0x66
	.byte	0x3
	.4byte	0x242
	.uleb128 0xd
	.4byte	0xaf
	.4byte	0x2bc
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x50
	.byte	0xe
	.4byte	0x300
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x8
	.byte	0
	.uleb128 0x4
	.byte	0x1
	.byte	0x2
	.4byte	.LASF59
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0x33
	.byte	0x1
	.4byte	0x38d
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x81
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x82
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x83
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x84
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x85
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x86
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x87
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x7
	.byte	0x31
	.byte	0x1
	.4byte	0x3cb
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x7
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x32
	.byte	0x1
	.4byte	0x4c9
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x41
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x42
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x43
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x44
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x4a
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x4b
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x4c
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x4d
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x4e
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x80
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x81
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x82
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x83
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x84
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x8a
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x8b
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x8c
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x8d
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x8e
	.byte	0
	.uleb128 0xd
	.4byte	0x97
	.4byte	0x4d9
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x20
	.byte	0x5
	.4byte	0x65
	.2byte	0x120
	.4byte	0x504
	.uleb128 0x12
	.4byte	.LASF128
	.sleb128 -4
	.uleb128 0x12
	.4byte	.LASF129
	.sleb128 -3
	.uleb128 0x12
	.4byte	.LASF130
	.sleb128 -2
	.uleb128 0x12
	.4byte	.LASF131
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0
	.byte	0
	.uleb128 0x17
	.4byte	.LASF133
	.2byte	0x126
	.byte	0x3
	.4byte	0x4d9
	.uleb128 0x20
	.byte	0x7
	.4byte	0x2d
	.2byte	0x129
	.4byte	0x529
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x1
	.byte	0
	.uleb128 0x17
	.4byte	.LASF136
	.2byte	0x137
	.byte	0x12
	.4byte	0xaf
	.uleb128 0x30
	.byte	0x8
	.byte	0x9
	.2byte	0x13d
	.byte	0x5
	.4byte	0x55a
	.uleb128 0x21
	.string	"ptr"
	.2byte	0x13e
	.byte	0xf
	.4byte	0x7f
	.byte	0
	.uleb128 0x21
	.string	"len"
	.2byte	0x13f
	.byte	0x12
	.4byte	0xaf
	.byte	0x4
	.byte	0
	.uleb128 0x31
	.byte	0x8
	.byte	0x9
	.2byte	0x13c
	.byte	0x9
	.4byte	0x57d
	.uleb128 0x22
	.4byte	.LASF137
	.2byte	0x140
	.byte	0x7
	.4byte	0x535
	.uleb128 0x22
	.4byte	.LASF138
	.2byte	0x141
	.byte	0xe
	.4byte	0x2ac
	.byte	0
	.uleb128 0x17
	.4byte	.LASF139
	.2byte	0x142
	.byte	0x3
	.4byte	0x55a
	.uleb128 0x8
	.4byte	0x57d
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0xa
	.byte	0x35
	.byte	0xe
	.4byte	0x5bd
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0x3
	.uleb128 0x32
	.4byte	.LASF144
	.4byte	0xffffffff
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0xa
	.byte	0x3d
	.byte	0xe
	.4byte	0x691
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF157
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF159
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF162
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF163
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF164
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF165
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF166
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF167
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF168
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF169
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF170
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF171
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF172
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF173
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF174
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF175
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF176
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF177
	.byte	0x20
	.byte	0
	.uleb128 0x8
	.4byte	0x97
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0xb
	.byte	0x3d
	.byte	0xe
	.4byte	0x6b6
	.uleb128 0x1
	.4byte	.LASF178
	.byte	0
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF180
	.byte	0x2
	.byte	0
	.uleb128 0x7
	.byte	0x5
	.4byte	0x65
	.byte	0xc
	.byte	0x2d
	.byte	0xe
	.4byte	0x6d0
	.uleb128 0x12
	.4byte	.LASF181
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF182
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF183
	.byte	0xc
	.byte	0x30
	.byte	0x3
	.4byte	0x6b6
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0xd
	.byte	0x2a
	.byte	0xe
	.4byte	0x786
	.uleb128 0x1
	.4byte	.LASF184
	.byte	0
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF188
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF189
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF190
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF191
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF192
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF193
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF194
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF195
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF196
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF197
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF198
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF199
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF200
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF201
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF202
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF203
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF204
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF205
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF206
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF207
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF208
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF209
	.byte	0xff
	.byte	0
	.uleb128 0x23
	.4byte	.LASF210
	.byte	0x4c
	.byte	0xa
	.4byte	0xaf
	.uleb128 0x5
	.byte	0x3
	.4byte	last_app_state
	.uleb128 0x18
	.4byte	.LASF211
	.byte	0x4e
	.byte	0xc
	.4byte	0x300
	.uleb128 0x23
	.4byte	.LASF212
	.byte	0x54
	.byte	0x9
	.4byte	0x97
	.uleb128 0x5
	.byte	0x3
	.4byte	risv_app_sleep_lock_status
	.uleb128 0x10
	.4byte	.LASF218
	.byte	0x10
	.byte	0x44
	.byte	0xd
	.4byte	0x7cf
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x2
	.4byte	0x65
	.byte	0
	.uleb128 0x19
	.4byte	.LASF213
	.2byte	0x177
	.4byte	0x504
	.4byte	0x7e9
	.uleb128 0x2
	.4byte	0x529
	.uleb128 0x2
	.4byte	0x23d
	.byte	0
	.uleb128 0x19
	.4byte	.LASF214
	.2byte	0x15f
	.4byte	0x504
	.4byte	0x803
	.uleb128 0x2
	.4byte	0x529
	.uleb128 0x2
	.4byte	0x589
	.byte	0
	.uleb128 0x13
	.4byte	.LASF215
	.byte	0xe
	.byte	0x1f
	.byte	0x8
	.4byte	0x7f
	.4byte	0x823
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x1d2
	.uleb128 0x2
	.4byte	0x6c
	.byte	0
	.uleb128 0x19
	.4byte	.LASF216
	.2byte	0x18b
	.4byte	0x504
	.4byte	0x838
	.uleb128 0x2
	.4byte	0x529
	.byte	0
	.uleb128 0x13
	.4byte	.LASF217
	.byte	0xf
	.byte	0x3c
	.byte	0xa
	.4byte	0xaf
	.4byte	0x84e
	.uleb128 0x2
	.4byte	0xaf
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF219
	.byte	0x11
	.2byte	0x11e
	.byte	0x6
	.4byte	0x866
	.uleb128 0x2
	.4byte	0xaf
	.uleb128 0x2
	.4byte	0xaf
	.byte	0
	.uleb128 0x14
	.4byte	.LASF222
	.byte	0x14
	.byte	0x70
	.4byte	0x873
	.uleb128 0x6
	.byte	0
	.uleb128 0x10
	.4byte	.LASF220
	.byte	0x12
	.byte	0x95
	.byte	0x6
	.4byte	0x88f
	.uleb128 0x2
	.4byte	0xaf
	.uleb128 0x2
	.4byte	0xaf
	.uleb128 0x2
	.4byte	0xaf
	.byte	0
	.uleb128 0x10
	.4byte	.LASF221
	.byte	0x13
	.byte	0x37
	.byte	0x6
	.4byte	0x8a1
	.uleb128 0x2
	.4byte	0x23d
	.byte	0
	.uleb128 0x14
	.4byte	.LASF223
	.byte	0x15
	.byte	0x45
	.4byte	0x8ae
	.uleb128 0x6
	.byte	0
	.uleb128 0x14
	.4byte	.LASF224
	.byte	0x16
	.byte	0x2d
	.4byte	0x8bb
	.uleb128 0x6
	.byte	0
	.uleb128 0x13
	.4byte	.LASF225
	.byte	0x13
	.byte	0x34
	.byte	0x5
	.4byte	0x65
	.4byte	0x8db
	.uleb128 0x2
	.4byte	0xaf
	.uleb128 0x2
	.4byte	0xaf
	.uleb128 0x2
	.4byte	0xaf
	.byte	0
	.uleb128 0x10
	.4byte	.LASF226
	.byte	0x14
	.byte	0x6f
	.byte	0x6
	.4byte	0x8ed
	.uleb128 0x2
	.4byte	0xaf
	.byte	0
	.uleb128 0x14
	.4byte	.LASF227
	.byte	0x14
	.byte	0x69
	.4byte	0x8fa
	.uleb128 0x6
	.byte	0
	.uleb128 0x33
	.4byte	.LASF228
	.byte	0x11
	.2byte	0x10a
	.byte	0x6
	.4byte	0x909
	.uleb128 0x6
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF229
	.byte	0x11
	.2byte	0x108
	.byte	0x6
	.4byte	0x91c
	.uleb128 0x2
	.4byte	0xaf
	.byte	0
	.uleb128 0x24
	.4byte	.LASF230
	.byte	0x17
	.byte	0xeb
	.byte	0xa
	.4byte	0xaf
	.4byte	0x92e
	.uleb128 0x6
	.byte	0
	.uleb128 0x24
	.4byte	.LASF231
	.byte	0x14
	.byte	0x66
	.byte	0x5
	.4byte	0x65
	.4byte	0x940
	.uleb128 0x6
	.byte	0
	.uleb128 0x14
	.4byte	.LASF232
	.byte	0x12
	.byte	0x97
	.4byte	0x94d
	.uleb128 0x6
	.byte	0
	.uleb128 0x10
	.4byte	.LASF233
	.byte	0x17
	.byte	0xe8
	.byte	0x6
	.4byte	0x95f
	.uleb128 0x2
	.4byte	0x97
	.byte	0
	.uleb128 0x10
	.4byte	.LASF234
	.byte	0xf
	.byte	0x31
	.byte	0x6
	.4byte	0x971
	.uleb128 0x2
	.4byte	0xaf
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF235
	.byte	0x4
	.2byte	0x129
	.byte	0xd
	.4byte	0x994
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0xe1
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x2
	.4byte	0xaf
	.uleb128 0x6
	.byte	0
	.uleb128 0x13
	.4byte	.LASF236
	.byte	0xc
	.byte	0x36
	.byte	0x1c
	.4byte	0x6d0
	.4byte	0x9aa
	.uleb128 0x2
	.4byte	0x97
	.byte	0
	.uleb128 0x13
	.4byte	.LASF237
	.byte	0xc
	.byte	0x35
	.byte	0x1c
	.4byte	0x6d0
	.4byte	0x9c0
	.uleb128 0x2
	.4byte	0x97
	.byte	0
	.uleb128 0x34
	.4byte	.LASF245
	.byte	0x1
	.2byte	0x190
	.byte	0x6
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa1c
	.uleb128 0x1b
	.4byte	.LASF238
	.2byte	0x190
	.byte	0x2d
	.4byte	0xaf
	.4byte	.LLST14
	.uleb128 0x1b
	.4byte	.LASF239
	.2byte	0x190
	.byte	0x3e
	.4byte	0xaf
	.4byte	.LLST15
	.uleb128 0x15
	.string	"msg"
	.2byte	0x192
	.byte	0xd
	.4byte	0x4c9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x9
	.4byte	.LVL70
	.4byte	0xa66
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x35
	.byte	0
	.byte	0
	.uleb128 0x25
	.4byte	.LASF243
	.2byte	0x177
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa56
	.uleb128 0x15
	.string	"msg"
	.2byte	0x179
	.byte	0xd
	.4byte	0xa56
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x9
	.4byte	.LVL66
	.4byte	0xa66
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	0x97
	.4byte	0xa66
	.uleb128 0xe
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x35
	.4byte	.LASF256
	.byte	0x1
	.2byte	0x15a
	.byte	0x13
	.4byte	0x504
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbc4
	.uleb128 0x1b
	.4byte	.LASF240
	.2byte	0x15a
	.byte	0x30
	.4byte	0x691
	.4byte	.LLST10
	.uleb128 0x36
	.string	"len"
	.byte	0x1
	.2byte	0x15a
	.byte	0x41
	.4byte	0x97
	.4byte	.LLST11
	.uleb128 0x15
	.string	"msg"
	.2byte	0x15c
	.byte	0x18
	.4byte	0x57d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1c
	.4byte	.LASF238
	.2byte	0x15d
	.byte	0x17
	.4byte	0x504
	.4byte	.LLST12
	.uleb128 0x1d
	.4byte	.LBB10
	.4byte	.LBE10-.LBB10
	.4byte	0xb7c
	.uleb128 0x1c
	.4byte	.LASF241
	.2byte	0x169
	.byte	0x12
	.4byte	0xa3
	.4byte	.LLST13
	.uleb128 0x37
	.4byte	.LASF138
	.byte	0x1
	.2byte	0x16a
	.byte	0x12
	.4byte	0xaf
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1d
	.4byte	.LBB11
	.4byte	.LBE11-.LBB11
	.4byte	0xb45
	.uleb128 0x15
	.string	"exp"
	.2byte	0x16f
	.byte	0x90
	.4byte	0xbd4
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x38
	.4byte	.LASF242
	.byte	0x1
	.2byte	0x16f
	.2byte	0x12a
	.4byte	0xbe9
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0x9
	.4byte	.LVL57
	.4byte	0x7b3
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x16f
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL61
	.4byte	0x7cf
	.4byte	0xb62
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x2010003
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x9
	.4byte	.LVL62
	.4byte	0x7e9
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x2010003
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL53
	.4byte	0x803
	.4byte	0xbaa
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
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
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0
	.uleb128 0x9
	.4byte	.LVL54
	.4byte	0x7e9
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x2010003
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	0x8d
	.4byte	0xbd4
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x4d
	.byte	0
	.uleb128 0x11
	.4byte	0xbc4
	.uleb128 0xd
	.4byte	0x8d
	.4byte	0xbe9
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x52
	.byte	0
	.uleb128 0x11
	.4byte	0xbd9
	.uleb128 0x25
	.4byte	.LASF244
	.2byte	0x155
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc17
	.uleb128 0x39
	.4byte	.LVL49
	.4byte	0x823
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x1020003
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	.LASF246
	.byte	0x6c
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xdd6
	.uleb128 0x27
	.4byte	.LASF247
	.byte	0x6c
	.byte	0x30
	.4byte	0x529
	.4byte	.LLST2
	.uleb128 0x3a
	.string	"msg"
	.byte	0x1
	.byte	0x6c
	.byte	0x4b
	.4byte	0x589
	.4byte	.LLST3
	.uleb128 0x28
	.4byte	.LASF248
	.byte	0x6f
	.byte	0xf
	.4byte	0x691
	.4byte	.LLST4
	.uleb128 0x1e
	.4byte	.LLRL5
	.4byte	0xd6a
	.uleb128 0x28
	.4byte	.LASF249
	.byte	0x75
	.byte	0x16
	.4byte	0xaf
	.4byte	.LLST6
	.uleb128 0x1e
	.4byte	.LLRL7
	.4byte	0xcba
	.uleb128 0x18
	.4byte	.LASF250
	.byte	0x76
	.byte	0x2d
	.4byte	0x2a0
	.uleb128 0x29
	.4byte	.LASF251
	.byte	0x76
	.byte	0x88
	.4byte	0xde6
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.2
	.uleb128 0x9
	.4byte	.LVL13
	.4byte	0x971
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.2
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL14
	.4byte	0x95f
	.4byte	0xcce
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL15
	.4byte	0x8db
	.4byte	0xce2
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0xa
	.4byte	.LVL18
	.4byte	0xdeb
	.uleb128 0xb
	.4byte	.LVL19
	.4byte	0x94d
	.4byte	0xcfe
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x39
	.byte	0
	.uleb128 0xa
	.4byte	.LVL20
	.4byte	0x940
	.uleb128 0xa
	.4byte	.LVL21
	.4byte	0x92e
	.uleb128 0xb
	.4byte	.LVL22
	.4byte	0xdeb
	.4byte	0xd23
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0xa
	.4byte	.LVL23
	.4byte	0x91c
	.uleb128 0xa
	.4byte	.LVL24
	.4byte	0x909
	.uleb128 0xb
	.4byte	.LVL25
	.4byte	0xdeb
	.4byte	0xd48
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0xa
	.4byte	.LVL26
	.4byte	0x8fa
	.uleb128 0xa
	.4byte	.LVL27
	.4byte	0x8ed
	.uleb128 0x9
	.4byte	.LVL28
	.4byte	0xdeb
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x1e
	.4byte	.LLRL8
	.4byte	0xd8d
	.uleb128 0x1c
	.4byte	.LASF252
	.2byte	0x11f
	.byte	0x16
	.4byte	0xaf
	.4byte	.LLST9
	.uleb128 0xf
	.4byte	.LVL36
	.4byte	0x88f
	.byte	0
	.uleb128 0xf
	.4byte	.LVL32
	.4byte	0x8bb
	.uleb128 0xa
	.4byte	.LVL33
	.4byte	0x8ae
	.uleb128 0xf
	.4byte	.LVL34
	.4byte	0x8a1
	.uleb128 0xf
	.4byte	.LVL39
	.4byte	0x873
	.uleb128 0xf
	.4byte	.LVL40
	.4byte	0x866
	.uleb128 0xa
	.4byte	.LVL43
	.4byte	0x838
	.uleb128 0xf
	.4byte	.LVL44
	.4byte	0x84e
	.uleb128 0xf
	.4byte	.LVL48
	.4byte	0x8ed
	.byte	0
	.uleb128 0xd
	.4byte	0x8d
	.4byte	0xde6
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x35
	.byte	0
	.uleb128 0x11
	.4byte	0xdd6
	.uleb128 0x26
	.4byte	.LASF253
	.byte	0x56
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe8e
	.uleb128 0x27
	.4byte	.LASF254
	.byte	0x56
	.byte	0x25
	.4byte	0xaf
	.4byte	.LLST0
	.uleb128 0x3b
	.string	"ret"
	.byte	0x1
	.byte	0x58
	.byte	0x20
	.4byte	0x6d0
	.4byte	.LLST1
	.uleb128 0x1d
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.4byte	0xe6b
	.uleb128 0x18
	.4byte	.LASF250
	.byte	0x63
	.byte	0x25
	.4byte	0x2a0
	.uleb128 0x29
	.4byte	.LASF251
	.byte	0x63
	.byte	0x80
	.4byte	0xe9e
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.3
	.uleb128 0x9
	.4byte	.LVL4
	.4byte	0x971
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.3
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL2
	.4byte	0x9aa
	.4byte	0xe7e
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x47
	.byte	0
	.uleb128 0x9
	.4byte	.LVL7
	.4byte	0x994
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x47
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	0x8d
	.4byte	0xe9e
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x6b
	.byte	0
	.uleb128 0x11
	.4byte	0xe8e
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
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x4
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
	.uleb128 0x5
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
	.uleb128 0x6
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
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
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
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
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x16
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x16
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
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1c
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.uleb128 0x1e
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x37
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x22
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
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0x2c
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2e
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
	.uleb128 0x2f
	.uleb128 0x13
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
	.uleb128 0x30
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x31
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x32
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
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
	.uleb128 0x34
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
	.uleb128 0x35
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
	.uleb128 0x36
	.uleb128 0x5
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
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x37
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x39
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
	.uleb128 0x3a
	.uleb128 0x5
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
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x34
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
	.uleb128 0x2
	.uleb128 0x17
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
.LLST14:
	.byte	0x6
	.4byte	.LVL67
	.byte	0x4
	.uleb128 .LVL67-.LVL67
	.uleb128 .LVL69-.LVL67
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL69-.LVL67
	.uleb128 .LFE11-.LVL67
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
.LLST15:
	.byte	0x6
	.4byte	.LVL67
	.byte	0x4
	.uleb128 .LVL67-.LVL67
	.uleb128 .LVL68-.LVL67
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL68-.LVL67
	.uleb128 .LFE11-.LVL67
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
.LLST10:
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL51-.LVL50
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL51-.LVL50
	.uleb128 .LVL53-1-.LVL50
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL53-1-.LVL50
	.uleb128 .LVL63-.LVL50
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
	.uleb128 .LVL63-.LVL50
	.uleb128 .LVL64-.LVL50
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL64-.LVL50
	.uleb128 .LVL65-.LVL50
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
	.uleb128 .LVL65-.LVL50
	.uleb128 .LFE9-.LVL50
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL52-.LVL50
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL52-.LVL50
	.uleb128 .LVL53-1-.LVL50
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL53-1-.LVL50
	.uleb128 .LVL63-.LVL50
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL63-.LVL50
	.uleb128 .LFE9-.LVL50
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL54
	.byte	0x4
	.uleb128 .LVL54-.LVL54
	.uleb128 .LVL56-.LVL54
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL62-.LVL54
	.uleb128 .LVL63-.LVL54
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL55
	.byte	0x4
	.uleb128 .LVL55-.LVL55
	.uleb128 .LVL56-.LVL55
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL56-.LVL55
	.uleb128 .LVL58-.LVL55
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL58-.LVL55
	.uleb128 .LVL59-.LVL55
	.uleb128 0x3
	.byte	0x78
	.sleb128 -1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL60-.LVL55
	.uleb128 .LVL62-.LVL55
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL12-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL12-.LVL8
	.uleb128 .LVL29-.LVL8
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
	.uleb128 .LVL29-.LVL8
	.uleb128 .LVL31-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL31-.LVL8
	.uleb128 .LVL32-.LVL8
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
	.uleb128 .LVL32-.LVL8
	.uleb128 .LVL33-1-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL33-1-.LVL8
	.uleb128 .LVL34-.LVL8
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
	.uleb128 .LVL34-.LVL8
	.uleb128 .LVL35-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL35-.LVL8
	.uleb128 .LVL36-.LVL8
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
	.uleb128 .LVL36-.LVL8
	.uleb128 .LVL38-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL38-.LVL8
	.uleb128 .LVL39-.LVL8
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
	.uleb128 .LVL39-.LVL8
	.uleb128 .LVL40-1-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL40-1-.LVL8
	.uleb128 .LVL40-.LVL8
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
	.uleb128 .LVL40-.LVL8
	.uleb128 .LVL42-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL42-.LVL8
	.uleb128 .LVL44-.LVL8
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
	.uleb128 .LVL44-.LVL8
	.uleb128 .LVL46-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL46-.LVL8
	.uleb128 .LVL47-.LVL8
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
	.uleb128 .LVL47-.LVL8
	.uleb128 .LVL48-1-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL48-1-.LVL8
	.uleb128 .LVL48-.LVL8
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
	.uleb128 .LVL48-.LVL8
	.uleb128 .LFE7-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL11-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL11-.LVL8
	.uleb128 .LVL13-1-.LVL8
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL13-1-.LVL8
	.uleb128 .LVL29-.LVL8
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
	.uleb128 .LVL29-.LVL8
	.uleb128 .LVL30-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL30-.LVL8
	.uleb128 .LVL32-1-.LVL8
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL32-1-.LVL8
	.uleb128 .LVL32-.LVL8
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
	.uleb128 .LVL32-.LVL8
	.uleb128 .LVL33-1-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL33-1-.LVL8
	.uleb128 .LVL34-.LVL8
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
	.uleb128 .LVL34-.LVL8
	.uleb128 .LVL36-1-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL36-1-.LVL8
	.uleb128 .LVL36-.LVL8
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
	.uleb128 .LVL36-.LVL8
	.uleb128 .LVL37-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL37-.LVL8
	.uleb128 .LVL39-1-.LVL8
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL39-1-.LVL8
	.uleb128 .LVL39-.LVL8
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
	.uleb128 .LVL39-.LVL8
	.uleb128 .LVL40-1-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL40-1-.LVL8
	.uleb128 .LVL40-.LVL8
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
	.uleb128 .LVL40-.LVL8
	.uleb128 .LVL41-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL41-.LVL8
	.uleb128 .LVL43-1-.LVL8
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL43-1-.LVL8
	.uleb128 .LVL44-.LVL8
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
	.uleb128 .LVL44-.LVL8
	.uleb128 .LVL45-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL45-.LVL8
	.uleb128 .LVL47-.LVL8
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL47-.LVL8
	.uleb128 .LVL48-1-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL48-1-.LVL8
	.uleb128 .LVL48-.LVL8
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
	.uleb128 .LVL48-.LVL8
	.uleb128 .LFE7-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL9
	.byte	0x4
	.uleb128 .LVL9-.LVL9
	.uleb128 .LVL11-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL11-.LVL9
	.uleb128 .LVL13-1-.LVL9
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL13-1-.LVL9
	.uleb128 .LVL29-.LVL9
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
	.uleb128 .LVL29-.LVL9
	.uleb128 .LVL30-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL30-.LVL9
	.uleb128 .LVL32-1-.LVL9
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL32-1-.LVL9
	.uleb128 .LVL32-.LVL9
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
	.uleb128 .LVL32-.LVL9
	.uleb128 .LVL33-1-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL33-1-.LVL9
	.uleb128 .LVL34-.LVL9
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
	.uleb128 .LVL34-.LVL9
	.uleb128 .LVL36-1-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL36-1-.LVL9
	.uleb128 .LVL36-.LVL9
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
	.uleb128 .LVL36-.LVL9
	.uleb128 .LVL37-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL37-.LVL9
	.uleb128 .LVL39-1-.LVL9
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL39-1-.LVL9
	.uleb128 .LVL39-.LVL9
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
	.uleb128 .LVL39-.LVL9
	.uleb128 .LVL40-1-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL40-1-.LVL9
	.uleb128 .LVL40-.LVL9
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
	.uleb128 .LVL40-.LVL9
	.uleb128 .LVL41-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL41-.LVL9
	.uleb128 .LVL43-1-.LVL9
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL43-1-.LVL9
	.uleb128 .LVL44-.LVL9
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
	.uleb128 .LVL44-.LVL9
	.uleb128 .LVL45-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL45-.LVL9
	.uleb128 .LVL47-.LVL9
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL47-.LVL9
	.uleb128 .LVL48-1-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL48-1-.LVL9
	.uleb128 .LVL48-.LVL9
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
	.uleb128 .LVL48-.LVL9
	.uleb128 .LFE7-.LVL9
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL10
	.byte	0x4
	.uleb128 .LVL10-.LVL10
	.uleb128 .LVL16-.LVL10
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL17-.LVL10
	.uleb128 .LVL29-.LVL10
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST9:
	.byte	0x8
	.4byte	.LVL34
	.uleb128 .LVL36-1-.LVL34
	.uleb128 0x2
	.byte	0x7b
	.sleb128 1
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
	.uleb128 .LVL5-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL5-.LVL0
	.uleb128 .LVL6-.LVL0
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
	.uleb128 .LVL6-.LVL0
	.uleb128 .LFE6-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL2-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL2-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-1-.LVL0
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL6-.LVL0
	.uleb128 .LVL7-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL7-.LVL0
	.uleb128 .LFE6-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x44
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
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
	.4byte	.LBB3
	.byte	0x4
	.uleb128 .LBB3-.LBB3
	.uleb128 .LBE3-.LBB3
	.byte	0x4
	.uleb128 .LBB6-.LBB3
	.uleb128 .LBE6-.LBB3
	.byte	0
.LLRL7:
	.byte	0x5
	.4byte	.LBB4
	.byte	0x4
	.uleb128 .LBB4-.LBB4
	.uleb128 .LBE4-.LBB4
	.byte	0x4
	.uleb128 .LBB5-.LBB4
	.uleb128 .LBE5-.LBB4
	.byte	0
.LLRL8:
	.byte	0x5
	.4byte	.LBB7
	.byte	0x4
	.uleb128 .LBB7-.LBB7
	.uleb128 .LBE7-.LBB7
	.byte	0x4
	.uleb128 .LBB8-.LBB7
	.uleb128 .LBE8-.LBB7
	.byte	0x4
	.uleb128 .LBB9-.LBB7
	.uleb128 .LBE9-.LBB7
	.byte	0
.LLRL16:
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
	.byte	0x7
	.4byte	.LFB7
	.uleb128 .LFE7-.LFB7
	.byte	0x7
	.4byte	.LFB8
	.uleb128 .LFE8-.LFB8
	.byte	0x7
	.4byte	.LFB9
	.uleb128 .LFE9-.LFB9
	.byte	0x7
	.4byte	.LFB10
	.uleb128 .LFE10-.LFB10
	.byte	0x7
	.4byte	.LFB11
	.uleb128 .LFE11-.LFB11
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF8:
	.string	"long int"
.LASF79:
	.string	"HID_CCNI_MSG_POLLING_WHEEL_STATUS"
.LASF71:
	.string	"HID_CCNI_MSG_USB_PLUG_OUT"
.LASF190:
	.string	"SLEEP_LOCK_IRRX"
.LASF188:
	.string	"SLEEP_LOCK_DMA"
.LASF248:
	.string	"raw_msg"
.LASF12:
	.string	"char"
.LASF144:
	.string	"HAL_CCNI_CORE_RESERVED"
.LASF207:
	.string	"SLEEP_LOCK_APP"
.LASF24:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF93:
	.string	"APP_STATE_CONNECT_PREPARING"
.LASF35:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF17:
	.string	"PRINT_LEVEL_DEBUG"
.LASF140:
	.string	"HAL_CCNI_CORE_START"
.LASF3:
	.string	"unsigned int"
.LASF227:
	.string	"peripheral_sampling_state_change_active"
.LASF109:
	.string	"APP_STATE_BT_CONNECTED_ACTIVE"
.LASF86:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF187:
	.string	"SLEEP_LOCK_TRNG"
.LASF48:
	.string	"msg_id_handle"
.LASF50:
	.string	"DBG_PIN_SPI_CB"
.LASF80:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF219:
	.string	"hid_express__push_to_key_queue"
.LASF101:
	.string	"APP_STATE_CONNECT_CANCEL_CHECK"
.LASF37:
	.string	"log_type_t"
.LASF255:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF246:
	.string	"hal_ccni_event_callback3"
.LASF33:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF221:
	.string	"rv_fake_report_set"
.LASF6:
	.string	"short int"
.LASF55:
	.string	"DBG_PIN_USB_SOF"
.LASF75:
	.string	"HID_CCNI_MSG_KEY_REMAP_TRIGGER"
.LASF83:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF64:
	.string	"HID_CCNI_MSG_FEATURE_CONFIG"
.LASF189:
	.string	"SLEEP_LOCK_IRTX"
.LASF185:
	.string	"SLEEP_LOCK_AESOTF"
.LASF87:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF131:
	.string	"HAL_CCNI_STATUS_NO_INIT"
.LASF124:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1"
.LASF202:
	.string	"SLEEP_LOCK_USB"
.LASF107:
	.string	"APP_STATE_USB_DISCONNECTING"
.LASF96:
	.string	"APP_STATE_BT_RECONNECT"
.LASF84:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF181:
	.string	"HAL_SLEEP_MANAGER_ERROR"
.LASF20:
	.string	"PRINT_LEVEL_ERROR"
.LASF29:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF5:
	.string	"signed char"
.LASF132:
	.string	"HAL_CCNI_STATUS_OK"
.LASF118:
	.string	"APP_STATE_2_4G_CONNECTED"
.LASF16:
	.string	"uint32_t"
.LASF137:
	.string	"variable_len_msg"
.LASF214:
	.string	"hal_ccni_set_event"
.LASF89:
	.string	"APP_STATE_INITIALIZED"
.LASF247:
	.string	"event"
.LASF228:
	.string	"hid_express_clear_key_pushed"
.LASF211:
	.string	"g_riscv_ccni_irq_occur"
.LASF2:
	.string	"long long unsigned int"
.LASF242:
	.string	"file"
.LASF231:
	.string	"peripheral_sampling_init"
.LASF82:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF119:
	.string	"APP_STATE_2_4G_CONNECTED_ACTIVE"
.LASF41:
	.string	"f_tlv_dump_t"
.LASF61:
	.string	"HID_CCNI_MSG_FAKE_REPORT_ENABLE"
.LASF30:
	.string	"LOG_TYPE_HCI_DATA"
.LASF245:
	.string	"riscv_app_ccni_key_remap_send"
.LASF36:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF65:
	.string	"HID_CCNI_MSG_HOGP_ATTR_HANDLE"
.LASF206:
	.string	"SLEEP_LOCK_I2C0"
.LASF216:
	.string	"hal_ccni_unmask_event"
.LASF241:
	.string	"retry_cnt"
.LASF235:
	.string	"print_module_msgid_log"
.LASF57:
	.string	"DBG_PIN_USB_TX"
.LASF13:
	.string	"size_t"
.LASF32:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF197:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF209:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF179:
	.string	"K_TYPE_Z1"
.LASF180:
	.string	"K_TYPE_Z2"
.LASF59:
	.string	"_Bool"
.LASF253:
	.string	"rv_sleep_lock_request"
.LASF199:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF46:
	.string	"dump_handle"
.LASF26:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF78:
	.string	"HID_CCNI_MSG_POLLING_KEY_STATUS"
.LASF34:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF56:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF237:
	.string	"hal_sleep_manager_lock_sleep"
.LASF110:
	.string	"APP_STATE_BT_CONNECTED_IDLE_1"
.LASF111:
	.string	"APP_STATE_BT_CONNECTED_IDLE_2"
.LASF112:
	.string	"APP_STATE_BT_CONNECTED_IDLE_3"
.LASF236:
	.string	"hal_sleep_manager_unlock_sleep"
.LASF233:
	.string	"hid_common_clear_hid_exp_flag"
.LASF141:
	.string	"HAL_CCNI_CORE_MCU"
.LASF27:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF25:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF230:
	.string	"hid_common_get_dongle_scenario"
.LASF31:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF128:
	.string	"HAL_CCNI_STATUS_INVALID_PARAMETER"
.LASF256:
	.string	"riscv_app_ccin_send"
.LASF97:
	.string	"APP_STATE_2_4G_RECONNECT"
.LASF250:
	.string	"log_control_block_riscv_ps"
.LASF69:
	.string	"HID_CCNI_MSG_COMMON_PARA_UPDATE"
.LASF43:
	.string	"log_switch"
.LASF73:
	.string	"HID_CCNI_MSG_INACTIVITY_TIMEOUT"
.LASF77:
	.string	"HID_CCNI_MSG_PRINT_HID_REPORT_REQ"
.LASF138:
	.string	"data"
.LASF130:
	.string	"HAL_CCNI_STATUS_ERROR"
.LASF208:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF38:
	.string	"f_print_t"
.LASF142:
	.string	"HAL_CCNI_CORE_RISCV"
.LASF14:
	.string	"uint8_t"
.LASF238:
	.string	"status"
.LASF224:
	.string	"key_remap_frontend_setting_update"
.LASF76:
	.string	"HID_CCNI_MSG_FAKE_REPORT_TERMINATE"
.LASF186:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF85:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF249:
	.string	"app_state"
.LASF10:
	.string	"long long int"
.LASF243:
	.string	"riscv_app_ccin_fake_data_disable"
.LASF254:
	.string	"lock"
.LASF66:
	.string	"HID_CCNI_MSG_SET_DBG_PIN"
.LASF201:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF39:
	.string	"f_dump_buffer_t"
.LASF106:
	.string	"APP_STATE_USB_ENTERING_ACTIVE"
.LASF23:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF182:
	.string	"HAL_SLEEP_MANAGER_OK"
.LASF98:
	.string	"APP_STATE_2_4G_QUICK_CONNECT"
.LASF183:
	.string	"hal_sleep_manager_status_t"
.LASF252:
	.string	"ptr_val"
.LASF18:
	.string	"PRINT_LEVEL_INFO"
.LASF53:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF54:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF198:
	.string	"SLEEP_LOCK_DCXO"
.LASF99:
	.string	"APP_STATE_2_4G_RECONNECT_RESUME_WAIT"
.LASF58:
	.string	"DBG_PIN_MAX"
.LASF129:
	.string	"HAL_CCNI_STATUS_BUSY"
.LASF92:
	.string	"APP_STATE_TEST"
.LASF251:
	.string	"msg_id_string"
.LASF225:
	.string	"rv_fake_report_config"
.LASF74:
	.string	"HID_CCNI_MSG_FORCE_ALL_KEY_RELEASED"
.LASF212:
	.string	"risv_app_sleep_lock_status"
.LASF155:
	.string	"HAL_CCNI_EVENT10"
.LASF156:
	.string	"HAL_CCNI_EVENT11"
.LASF157:
	.string	"HAL_CCNI_EVENT12"
.LASF158:
	.string	"HAL_CCNI_EVENT13"
.LASF159:
	.string	"HAL_CCNI_EVENT14"
.LASF160:
	.string	"HAL_CCNI_EVENT15"
.LASF161:
	.string	"HAL_CCNI_EVENT16"
.LASF162:
	.string	"HAL_CCNI_EVENT17"
.LASF163:
	.string	"HAL_CCNI_EVENT18"
.LASF164:
	.string	"HAL_CCNI_EVENT19"
.LASF11:
	.string	"long double"
.LASF15:
	.string	"uint16_t"
.LASF62:
	.string	"HID_CCNI_MSG_FAKE_REPORT_CONFIG"
.LASF178:
	.string	"K_TYPE_K"
.LASF114:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_1"
.LASF115:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_2"
.LASF116:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_3"
.LASF125:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2"
.LASF126:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3"
.LASF47:
	.string	"tlv_dump_handle"
.LASF49:
	.string	"log_control_block_t"
.LASF210:
	.string	"last_app_state"
.LASF19:
	.string	"PRINT_LEVEL_WARNING"
.LASF103:
	.string	"APP_STATE_USB_ACTIVE"
.LASF145:
	.string	"HAL_CCNI_EVENT0"
.LASF146:
	.string	"HAL_CCNI_EVENT1"
.LASF147:
	.string	"HAL_CCNI_EVENT2"
.LASF148:
	.string	"HAL_CCNI_EVENT3"
.LASF149:
	.string	"HAL_CCNI_EVENT4"
.LASF150:
	.string	"HAL_CCNI_EVENT5"
.LASF151:
	.string	"HAL_CCNI_EVENT6"
.LASF152:
	.string	"HAL_CCNI_EVENT7"
.LASF153:
	.string	"HAL_CCNI_EVENT8"
.LASF154:
	.string	"HAL_CCNI_EVENT9"
.LASF63:
	.string	"HID_CCNI_MSG_KEY_REMAP_CONFIG"
.LASF165:
	.string	"HAL_CCNI_EVENT20"
.LASF166:
	.string	"HAL_CCNI_EVENT21"
.LASF167:
	.string	"HAL_CCNI_EVENT22"
.LASF168:
	.string	"HAL_CCNI_EVENT23"
.LASF169:
	.string	"HAL_CCNI_EVENT24"
.LASF170:
	.string	"HAL_CCNI_EVENT25"
.LASF171:
	.string	"HAL_CCNI_EVENT26"
.LASF172:
	.string	"HAL_CCNI_EVENT27"
.LASF173:
	.string	"HAL_CCNI_EVENT28"
.LASF174:
	.string	"HAL_CCNI_EVENT29"
.LASF200:
	.string	"SLEEP_LOCK_I3C1"
.LASF81:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF229:
	.string	"hid_express_dongle_scenario_update"
.LASF91:
	.string	"APP_STATE_DISCONNECTED"
.LASF100:
	.string	"APP_STATE_CONNECT_CANCEL"
.LASF51:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF113:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_ACTIVE"
.LASF139:
	.string	"hal_ccni_message_t"
.LASF45:
	.string	"print_handle"
.LASF175:
	.string	"HAL_CCNI_EVENT30"
.LASF176:
	.string	"HAL_CCNI_EVENT31"
.LASF88:
	.string	"APP_STATE_NONE"
.LASF192:
	.string	"SLEEP_LOCK_FLASH"
.LASF68:
	.string	"HID_CCNI_MSG_SET_FEATURE"
.LASF133:
	.string	"hal_ccni_status_t"
.LASF60:
	.string	"HID_CCNI_MSG_APP_STATE"
.LASF67:
	.string	"HID_CCNI_MSG_SET_OUTPUT_CTRL_PIN"
.LASF117:
	.string	"APP_STATE_BT_DISCONNECTING"
.LASF136:
	.string	"hal_ccni_event_t"
.LASF239:
	.string	"attribute"
.LASF234:
	.string	"riscv_mouse_key_change_state"
.LASF177:
	.string	"HAL_CCNI_EVENT_MAX"
.LASF9:
	.string	"long unsigned int"
.LASF226:
	.string	"peripheral_sampling_app_state_update"
.LASF127:
	.string	"APP_STATE_2_4G_DISCONNECTING"
.LASF70:
	.string	"HID_CCNI_MSG_WAKEUP_KEY"
.LASF134:
	.string	"HAL_CCNI_EVENT_STATUS_IDLE"
.LASF193:
	.string	"SLEEP_LOCK_ESC"
.LASF223:
	.string	"key_remap_backend_setting"
.LASF120:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_1"
.LASF121:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_2"
.LASF122:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_3"
.LASF4:
	.string	"unsigned char"
.LASF123:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE"
.LASF222:
	.string	"peripheral_sampling_common_para_update"
.LASF22:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF42:
	.string	"module_name"
.LASF184:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF94:
	.string	"APP_STATE_BT_PAIRING"
.LASF220:
	.string	"hid_experss_bt_set_attr_handle"
.LASF232:
	.string	"hid_experss_bt_clear_queue"
.LASF213:
	.string	"hal_ccni_query_event_status"
.LASF72:
	.string	"HID_CCNI_MSG_KEY"
.LASF28:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF104:
	.string	"APP_STATE_USB_SUSPEND"
.LASF218:
	.string	"light_assert"
.LASF217:
	.string	"riscv_mouse_key_id_to_key_status"
.LASF44:
	.string	"print_level"
.LASF194:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF195:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF196:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF108:
	.string	"APP_STATE_BT_CONNECTED"
.LASF40:
	.string	"f_msg_id_t"
.LASF90:
	.string	"APP_STATE_STANDBY"
.LASF105:
	.string	"APP_STATE_USB_STOP"
.LASF7:
	.string	"short unsigned int"
.LASF52:
	.string	"DBG_PIN_NACK"
.LASF215:
	.string	"memcpy"
.LASF143:
	.string	"HAL_CCNI_CORE_END"
.LASF240:
	.string	"payload"
.LASF95:
	.string	"APP_STATE_2_4G_PAIRING"
.LASF191:
	.string	"SLEEP_LOCK_AIO"
.LASF102:
	.string	"APP_STATE_USB_CONNECTED"
.LASF244:
	.string	"riscv_app_ccin_init"
.LASF203:
	.string	"SLEEP_LOCK_UART0"
.LASF204:
	.string	"SLEEP_LOCK_UART1"
.LASF205:
	.string	"SLEEP_LOCK_UART2"
.LASF135:
	.string	"HAL_CCNI_EVENT_STATUS_BUSY"
.LASF21:
	.string	"print_level_t"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_ccni.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
