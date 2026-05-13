	.file	"riscv_mouse_key.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_mouse_key.c"
	.section	.text.riscv_mouse_key_polling_all_key_status,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_polling_all_key_status
	.hidden	riscv_mouse_key_polling_all_key_status
	.type	riscv_mouse_key_polling_all_key_status, @function
riscv_mouse_key_polling_all_key_status:
.LFB15:
	.file 1 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_mouse_key.c"
	.loc 1 98 1
	.cfi_startproc
	.loc 1 99 5
	.loc 1 101 5
	.loc 1 98 1 is_stmt 0
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	.loc 1 105 5
	addi	a1,sp,8
	addi	a0,sp,4
	.loc 1 98 1
	sw	s0,16(sp)
	sw	s1,12(sp)
	.loc 1 101 16
	sw	zero,mouse_5key,a5
	.loc 1 102 5 is_stmt 1
	.loc 1 104 5
	.loc 1 105 5
	.loc 1 98 1 is_stmt 0
	sw	ra,20(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 105 5
	call	hal_eint_get_debounce_out_value_by_mask
.LVL0:
	.loc 1 121 5 is_stmt 1
	.loc 1 121 14 is_stmt 0
	lw	a0,4(sp)
	.loc 1 122 14
	lw	t1,8(sp)
	.loc 1 101 16
	lla	s0,mouse_5key
	lw	a4,0(s0)
	.loc 1 124 24 discriminator 1
	lw	a5,rv_key_num
	.loc 1 121 14
	not	a0,a0
.LVL1:
	.loc 1 122 5 is_stmt 1
	.loc 1 122 14 is_stmt 0
	not	t1,t1
.LVL2:
	.loc 1 124 5 is_stmt 1
	.loc 1 124 24 is_stmt 0 discriminator 1
	sw	a5,0(sp)
	lla	t0,rv_key_ids
	.loc 1 124 5
	li	a1,0
	.loc 1 124 14
	li	a3,0
	.loc 1 126 12
	li	t2,31
	.loc 1 132 17
	li	s1,47
	.loc 1 133 41
	li	a2,1
.LVL3:
.L2:
	.loc 1 124 24 is_stmt 1 discriminator 1
	lw	a5,0(sp)
	bne	a5,a3,.L5
	beq	a1,zero,.L6
	sw	a4,0(s0)
.L6:
	.loc 1 144 5
	.loc 1 145 1 is_stmt 0
	lw	a0,0(s0)
.LVL4:
	lw	ra,20(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	lw	s1,12(sp)
	.cfi_restore 9
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
.LVL5:
	jr	ra
.LVL6:
.L5:
	.cfi_restore_state
	.loc 1 126 9 is_stmt 1
	.loc 1 126 23 is_stmt 0
	lw	a5,0(t0)
	.loc 1 126 12
	bgtu	a5,t2,.L3
	.loc 1 127 13 is_stmt 1
	.loc 1 127 41 is_stmt 0
	sll	a5,a2,a5
	.loc 1 127 36
	and	a5,a5,a0
.L19:
	.loc 1 133 16
	beq	a5,zero,.L4
	.loc 1 135 17 is_stmt 1
	.loc 1 135 34 is_stmt 0
	sll	a5,a2,a3
	.loc 1 135 28
	or	a4,a4,a5
	li	a1,1
.L4:
	.loc 1 124 42 is_stmt 1 discriminator 2
	addi	a3,a3,1
.LVL7:
	addi	t0,t0,4
	j	.L2
.L3:
	.loc 1 132 14
	.loc 1 132 17 is_stmt 0
	bgtu	a5,s1,.L4
	.loc 1 133 13 is_stmt 1
	.loc 1 133 60 is_stmt 0
	addi	a5,a5,-32
	.loc 1 133 41
	sll	a5,a2,a5
	.loc 1 133 36
	and	a5,a5,t1
	j	.L19
	.cfi_endproc
.LFE15:
	.size	riscv_mouse_key_polling_all_key_status, .-riscv_mouse_key_polling_all_key_status
	.section	.text.update_key_status,"ax",@progbits
	.align	1
	.globl	update_key_status
	.hidden	update_key_status
	.type	update_key_status, @function
update_key_status:
.LFB16:
	.loc 1 148 1 is_stmt 1
	.cfi_startproc
.LVL8:
	.loc 1 149 5
	.loc 1 149 40 is_stmt 0
	slli	a2,a2,2
.LVL9:
	lla	a5,rv_key_ids
	add	a5,a5,a2
	lw	a4,0(a5)
	.loc 1 149 96
	li	a5,31
	bgtu	a4,a5,.L21
	.loc 1 149 68 discriminator 1
	li	a5,1
	sll	a5,a5,a4
.LVL10:
	.loc 1 151 5 is_stmt 1
	.loc 1 152 9
	.loc 1 153 13 is_stmt 0
	lw	a4,0(a0)
	.loc 1 152 12
	bne	a3,zero,.L22
	.loc 1 155 13 is_stmt 1
	.loc 1 155 35 is_stmt 0
	not	a5,a5
.LVL11:
	.loc 1 155 32
	and	a5,a5,a4
.LVL12:
	j	.L29
.LVL13:
.L21:
	.loc 1 149 130 discriminator 2
	addi	a4,a4,-32
	.loc 1 149 103 discriminator 2
	li	a5,1
	sll	a5,a5,a4
.LVL14:
	.loc 1 151 5 is_stmt 1
	.loc 1 158 9
	.loc 1 159 13 is_stmt 0
	lw	a4,0(a1)
	.loc 1 158 12
	bne	a3,zero,.L24
	.loc 1 161 13 is_stmt 1
	.loc 1 161 35 is_stmt 0
	not	a5,a5
.LVL15:
	.loc 1 161 32
	and	a5,a5,a4
.LVL16:
	j	.L30
.LVL17:
.L22:
	.loc 1 153 13 is_stmt 1
	.loc 1 153 32 is_stmt 0
	or	a5,a5,a4
.LVL18:
.L29:
	.loc 1 155 32
	sw	a5,0(a0)
.LVL19:
	ret
.LVL20:
.L24:
	.loc 1 159 13 is_stmt 1
	.loc 1 159 32 is_stmt 0
	or	a5,a5,a4
.LVL21:
.L30:
	.loc 1 161 32
	sw	a5,0(a1)
.LVL22:
	.loc 1 164 1
	ret
	.cfi_endproc
.LFE16:
	.size	update_key_status, .-update_key_status
	.section	.text.riscv_mouse_key_combo_key_check,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_combo_key_check
	.hidden	riscv_mouse_key_combo_key_check
	.type	riscv_mouse_key_combo_key_check, @function
riscv_mouse_key_combo_key_check:
.LFB17:
	.loc 1 167 1 is_stmt 1
	.cfi_startproc
	.loc 1 168 5
.LVL23:
	.loc 1 169 5
	.loc 1 170 5
	.loc 1 171 5
	.loc 1 174 5
	.loc 1 167 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	.loc 1 174 5
	addi	a1,sp,4
	mv	a0,sp
	.loc 1 167 1
	sw	ra,16(sp)
	.cfi_offset 1, -4
	.loc 1 174 5
	call	hal_eint_get_debounce_out_value_by_mask
.LVL24:
	.loc 1 178 5 is_stmt 1
	.loc 1 190 46 is_stmt 0 discriminator 1
	lla	a5,combo_cfg
	.loc 1 178 57
	lw	a1,0(sp)
.LVL25:
	.loc 1 179 5 is_stmt 1
	.loc 1 179 57 is_stmt 0
	lw	t1,4(sp)
.LVL26:
	.loc 1 190 5 is_stmt 1
	.loc 1 190 46 is_stmt 0 discriminator 1
	lw	a2,4(a5)
	lw	a4,0(a5)
	.loc 1 190 20
	li	a0,0
.LVL27:
.L32:
	.loc 1 190 35 is_stmt 1 discriminator 1
	bne	a2,a0,.L34
	.loc 1 168 14 is_stmt 0
	li	a0,255
.LVL28:
	.loc 1 201 5 is_stmt 1
.L31:
	.loc 1 202 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL29:
.L34:
	.cfi_restore_state
	.loc 1 192 9 is_stmt 1
	mv	a3,a4
.LVL30:
	.loc 1 193 9
	.loc 1 195 9
	.loc 1 195 63 is_stmt 0 discriminator 1
	lw	a5,0(a3)
	lw	a3,4(a3)
.LVL31:
	addi	a4,a4,8
	and	a5,a1,a5
.LVL32:
	and	a3,t1,a3
.LVL33:
	or	a5,a5,a3
	beq	a5,zero,.L31
	.loc 1 190 77 is_stmt 1 discriminator 2
	addi	a0,a0,1
.LVL34:
	j	.L32
	.cfi_endproc
.LFE17:
	.size	riscv_mouse_key_combo_key_check, .-riscv_mouse_key_combo_key_check
	.section	.text.riscv_mouse_key_deinit,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_deinit
	.hidden	riscv_mouse_key_deinit
	.type	riscv_mouse_key_deinit, @function
riscv_mouse_key_deinit:
.LFB33:
	.cfi_startproc
	.loc 1 233 6
	ret
	.cfi_endproc
.LFE33:
	.size	riscv_mouse_key_deinit, .-riscv_mouse_key_deinit
	.section	.text.riscv_mouse_key_early_handle,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_early_handle
	.hidden	riscv_mouse_key_early_handle
	.type	riscv_mouse_key_early_handle, @function
riscv_mouse_key_early_handle:
.LFB20:
	.loc 1 239 1
	.cfi_startproc
	.loc 1 240 5
	lla	a1,riscv_app+4
	li	a0,1
	tail	hal_gpt_get_free_run_count
.LVL35:
	.cfi_endproc
.LFE20:
	.size	riscv_mouse_key_early_handle, .-riscv_mouse_key_early_handle
	.section	.text.riscv_mouse_key_get_key_status,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_get_key_status
	.hidden	riscv_mouse_key_get_key_status
	.type	riscv_mouse_key_get_key_status, @function
riscv_mouse_key_get_key_status:
.LFB21:
	.loc 1 252 1
	.cfi_startproc
.LVL36:
	.loc 1 253 5
	.loc 1 258 5
	.loc 1 252 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.loc 1 258 5
	lla	a1,riscv_app+4
	.cfi_offset 8, -8
	.loc 1 252 1
	mv	s0,a0
	.loc 1 258 5
	li	a0,1
.LVL37:
	.loc 1 252 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 258 5
	call	hal_gpt_get_free_run_count
.LVL38:
	.loc 1 270 9 is_stmt 1
	.loc 1 270 27 is_stmt 0
	call	riscv_mouse_key_polling_all_key_status
.LVL39:
	.loc 1 271 9 is_stmt 1
	.loc 1 271 24 is_stmt 0
	sw	a0,0(s0)
	.loc 1 284 5 is_stmt 1
	.loc 1 285 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL40:
	li	a0,0
.LVL41:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE21:
	.size	riscv_mouse_key_get_key_status, .-riscv_mouse_key_get_key_status
	.section	.text.riscv_mouse_key_post_process,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_post_process
	.hidden	riscv_mouse_key_post_process
	.type	riscv_mouse_key_post_process, @function
riscv_mouse_key_post_process:
.LFB22:
	.loc 1 288 1 is_stmt 1
	.cfi_startproc
	.loc 1 304 5
	.loc 1 304 28 is_stmt 0
	lw	a5,mouse_5key
	sw	a5,new_keys_status_record,a4
	.loc 1 306 1
	ret
	.cfi_endproc
.LFE22:
	.size	riscv_mouse_key_post_process, .-riscv_mouse_key_post_process
	.section	.text.riscv_mouse_key_get_combo_key,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_get_combo_key
	.hidden	riscv_mouse_key_get_combo_key
	.type	riscv_mouse_key_get_combo_key, @function
riscv_mouse_key_get_combo_key:
.LFB23:
	.loc 1 309 1 is_stmt 1
	.cfi_startproc
	.loc 1 310 5
	lla	a2,combo_cfg+8
	lla	a1,combo_cfg+4
	lla	a0,combo_cfg
	tail	hid_common_get_combo_key_list
.LVL42:
	.cfi_endproc
.LFE23:
	.size	riscv_mouse_key_get_combo_key, .-riscv_mouse_key_get_combo_key
	.section	.text.riscv_mouse_key_init,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_init
	.hidden	riscv_mouse_key_init
	.type	riscv_mouse_key_init, @function
riscv_mouse_key_init:
.LFB18:
	.loc 1 206 1
	.cfi_startproc
	.loc 1 207 5
	.loc 1 209 5
	.loc 1 206 1 is_stmt 0
	addi	sp,sp,-40
	.cfi_def_cfa_offset 40
	sw	s0,32(sp)
	sw	s1,28(sp)
	sw	ra,36(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 209 28
	lw	a2,hid_common
	.loc 1 209 33
	lbu	a3,56(a2)
	.loc 1 209 16
	lla	s1,rv_key_num
	lla	a4,rv_key_ids
	sw	a3,0(s1)
	.loc 1 210 5 is_stmt 1
.LVL43:
	.loc 1 210 14 is_stmt 0
	li	a5,0
	mv	s0,a4
.LVL44:
.L46:
	.loc 1 210 23 is_stmt 1 discriminator 1
	bgtu	a3,a5,.L47
	.loc 1 215 5
	call	riscv_mouse_key_get_combo_key
.LVL45:
	.loc 1 217 5
.LBB4:
	.loc 1 217 10
	.loc 1 217 65
	.loc 1 217 266
	lw	a5,28(s0)
	lla	a0,log_control_block_riscv_ps
	li	a3,10
	sw	a5,24(sp)
	lw	a5,24(s0)
	lla	a2,msg_id_string.1
	li	a1,1
	sw	a5,20(sp)
	lw	a5,20(s0)
	sw	a5,16(sp)
	lw	a5,16(s0)
	sw	a5,12(sp)
	lw	a5,12(s0)
	sw	a5,8(sp)
	lw	a5,8(s0)
	sw	a5,4(sp)
	lw	a5,4(s0)
	sw	a5,0(sp)
	lw	a5,0(s0)
	lw	a4,0(s1)
	call	print_module_msgid_log
.LVL46:
.LBE4:
	.loc 1 217 8 discriminator 1
	.loc 1 230 5
	.loc 1 231 1 is_stmt 0
	lw	ra,36(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,32(sp)
	.cfi_restore 8
	lw	s1,28(sp)
	.cfi_restore 9
	li	a0,0
	addi	sp,sp,40
	.cfi_def_cfa_offset 0
	jr	ra
.LVL47:
.L47:
	.cfi_restore_state
	.loc 1 212 9 is_stmt 1
	.loc 1 212 57 is_stmt 0
	add	a1,a2,a5
	lbu	a1,46(a1)
	.loc 1 210 40 discriminator 3
	addi	a5,a5,1
.LVL48:
	.loc 1 212 57
	sw	a1,0(a4)
	.loc 1 210 40 is_stmt 1 discriminator 3
.LVL49:
	addi	a4,a4,4
	j	.L46
	.cfi_endproc
.LFE18:
	.size	riscv_mouse_key_init, .-riscv_mouse_key_init
	.section	.text.riscv_mouse_key_change_state,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_change_state
	.hidden	riscv_mouse_key_change_state
	.type	riscv_mouse_key_change_state, @function
riscv_mouse_key_change_state:
.LFB24:
	.loc 1 314 1
	.cfi_startproc
.LVL50:
	.loc 1 315 5
	.loc 1 315 25 is_stmt 0
	sw	a0,combo_cfg+12,a5
	.loc 1 316 1
	ret
	.cfi_endproc
.LFE24:
	.size	riscv_mouse_key_change_state, .-riscv_mouse_key_change_state
	.section	.text.riscv_mouse_keys_is_new_key_pressed,"ax",@progbits
	.align	1
	.globl	riscv_mouse_keys_is_new_key_pressed
	.hidden	riscv_mouse_keys_is_new_key_pressed
	.type	riscv_mouse_keys_is_new_key_pressed, @function
riscv_mouse_keys_is_new_key_pressed:
.LFB25:
	.loc 1 320 1 is_stmt 1
	.cfi_startproc
	.loc 1 321 5
	.loc 1 321 12 is_stmt 0
	lw	a5,mouse_5key
	.loc 1 321 23 discriminator 4
	li	a0,0
	.loc 1 321 23
	beq	a5,zero,.L51
	.loc 1 321 23 discriminator 1
	lw	a0,new_keys_status_record
	sub	a0,a0,a5
	snez	a0,a0
.L51:
	.loc 1 322 1
	ret
	.cfi_endproc
.LFE25:
	.size	riscv_mouse_keys_is_new_key_pressed, .-riscv_mouse_keys_is_new_key_pressed
	.section	.text.riscv_mouse_key_pairing_key_check,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_pairing_key_check
	.hidden	riscv_mouse_key_pairing_key_check
	.type	riscv_mouse_key_pairing_key_check, @function
riscv_mouse_key_pairing_key_check:
.LFB26:
	.loc 1 326 1 is_stmt 1
	.cfi_startproc
	.loc 1 327 5
	.loc 1 326 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	.cfi_offset 8, -8
	.loc 1 327 18
	lla	s0,combo_cfg
	lw	a5,12(s0)
	.loc 1 326 1
	sw	ra,16(sp)
	sw	s1,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 327 29
	andi	a4,a5,224
	.loc 1 327 7
	beq	a4,zero,.L54
	.loc 1 327 134 discriminator 1
	andi	a5,a5,1
	.loc 1 327 110 discriminator 1
	beq	a5,zero,.L54
.LBB5:
	.loc 1 329 9 is_stmt 1
	.loc 1 329 18 is_stmt 0
	sw	zero,0(sp)
	.loc 1 330 9 is_stmt 1
	.loc 1 330 18 is_stmt 0
	sw	zero,4(sp)
	.loc 1 331 9 is_stmt 1
	.loc 1 331 28 is_stmt 0
	call	riscv_mouse_key_combo_key_check
.LVL51:
	.loc 1 331 26 discriminator 1
	sw	a0,combo_key_result,a4
	.loc 1 332 9 is_stmt 1
	.loc 1 332 34 is_stmt 0
	lla	s1,start_gpt_free_count
	.loc 1 332 11
	lw	a4,0(s1)
	beq	a4,zero,.L56
	.loc 1 332 40 discriminator 1
	bne	a0,zero,.L57
	.loc 1 334 13 is_stmt 1
	mv	a1,sp
	call	hal_gpt_get_free_run_count
.LVL52:
	.loc 1 335 13
	lw	a1,0(sp)
	lw	a0,0(s1)
	addi	a2,sp,4
	call	hal_gpt_get_duration_count
.LVL53:
	.loc 1 336 13
	.loc 1 336 58 is_stmt 0
	lw	a5,8(s0)
	.loc 1 336 15
	lw	a4,4(sp)
	.loc 1 336 58
	slli	a5,a5,15
	.loc 1 336 15
	bgtu	a5,a4,.L54
	.loc 1 338 17 is_stmt 1
	li	a0,9
	call	hid_common_set_hid_exp_flag
.LVL54:
	.loc 1 339 17
.L57:
	.loc 1 348 13
	.loc 1 348 34 is_stmt 0
	sw	zero,start_gpt_free_count,a5
.LBE5:
	.loc 1 351 1
	j	.L54
.L56:
.LBB6:
	.loc 1 342 14 is_stmt 1
	.loc 1 342 16 is_stmt 0
	bne	a0,zero,.L57
	.loc 1 344 13 is_stmt 1
	mv	a1,s1
	call	hal_gpt_get_free_run_count
.LVL55:
.L54:
.LBE6:
	.loc 1 351 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE26:
	.size	riscv_mouse_key_pairing_key_check, .-riscv_mouse_key_pairing_key_check
	.section	.text.riscv_mouse_key__app_state_update,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key__app_state_update
	.hidden	riscv_mouse_key__app_state_update
	.type	riscv_mouse_key__app_state_update, @function
riscv_mouse_key__app_state_update:
.LFB27:
	.loc 1 354 1 is_stmt 1
	.cfi_startproc
.LVL56:
	.loc 1 355 5
	.loc 1 365 5
	.loc 1 391 13
	.loc 1 393 9
	.loc 1 399 5
	.loc 1 400 1 is_stmt 0
	ret
	.cfi_endproc
.LFE27:
	.size	riscv_mouse_key__app_state_update, .-riscv_mouse_key__app_state_update
	.section	.text.riscv_mouse_key_common_para_update,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_common_para_update
	.hidden	riscv_mouse_key_common_para_update
	.type	riscv_mouse_key_common_para_update, @function
riscv_mouse_key_common_para_update:
.LFB28:
	.loc 1 403 1 is_stmt 1
	.cfi_startproc
	.loc 1 407 1
	ret
	.cfi_endproc
.LFE28:
	.size	riscv_mouse_key_common_para_update, .-riscv_mouse_key_common_para_update
	.section	.text.riscv_mouse_key_debug_print,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_debug_print
	.hidden	riscv_mouse_key_debug_print
	.type	riscv_mouse_key_debug_print, @function
riscv_mouse_key_debug_print:
.LFB29:
	.loc 1 410 1
	.cfi_startproc
	.loc 1 419 5
	.loc 1 410 1 is_stmt 0
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,24(sp)
	sw	s1,20(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 419 28
	lla	s0,mouse_5key_printed
	lla	s1,mouse_5key
	lw	a4,0(s0)
	lw	a5,0(s1)
	.loc 1 410 1
	sw	ra,28(sp)
	.cfi_offset 1, -4
	.loc 1 419 8
	beq	a4,a5,.L68
	.loc 1 420 9 is_stmt 1
.LBB7:
	.loc 1 420 14
	.loc 1 420 69
	.loc 1 420 315
	lw	a1,hid_common
	lw	a1,72(a1)
	.loc 1 420 452 is_stmt 0
	lla	a2,combo_cfg
	lw	a3,0(a2)
	.loc 1 420 315
	sw	a1,16(sp)
	lw	a1,combo_key_result
	sw	a1,12(sp)
	lw	a2,4(a2)
	li	a1,1
	lla	a0,log_control_block_riscv_ps
	sw	a2,8(sp)
	lw	a2,4(a3)
	sw	a2,4(sp)
	lw	a3,0(a3)
	lla	a2,msg_id_string.0
	sw	a3,0(sp)
	li	a3,7
	call	print_module_msgid_log
.LVL57:
.LBE7:
	.loc 1 420 12 is_stmt 1 discriminator 1
	.loc 1 431 9
	.loc 1 431 28 is_stmt 0
	lw	a5,0(s1)
	sw	a5,0(s0)
.L68:
	.loc 1 433 1
	lw	ra,28(sp)
	.cfi_restore 1
	lw	s0,24(sp)
	.cfi_restore 8
	lw	s1,20(sp)
	.cfi_restore 9
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE29:
	.size	riscv_mouse_key_debug_print, .-riscv_mouse_key_debug_print
	.section	.text.riscv_mouse_key__ccni_send_status,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key__ccni_send_status
	.hidden	riscv_mouse_key__ccni_send_status
	.type	riscv_mouse_key__ccni_send_status, @function
riscv_mouse_key__ccni_send_status:
.LFB30:
	.loc 1 436 1 is_stmt 1
	.cfi_startproc
.LVL58:
	.loc 1 437 5
	.loc 1 438 5
	.loc 1 436 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	.loc 1 438 12
	li	a5,-122
	sb	a5,0(sp)
	.loc 1 439 5 is_stmt 1
	.loc 1 439 25 is_stmt 0
	srli	a5,a0,8
	sb	a0,1(sp)
	sb	a5,2(sp)
	srli	a5,a0,16
	srli	a0,a0,24
.LVL59:
	sb	a0,4(sp)
	.loc 1 441 5 is_stmt 1
	li	a1,5
	mv	a0,sp
	.loc 1 436 1 is_stmt 0
	sw	ra,16(sp)
	.cfi_offset 1, -4
	.loc 1 439 25
	sb	a5,3(sp)
	.loc 1 441 5
	call	riscv_app_ccin_send
.LVL60:
	.loc 1 442 1
	lw	ra,16(sp)
	.cfi_restore 1
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE30:
	.size	riscv_mouse_key__ccni_send_status, .-riscv_mouse_key__ccni_send_status
	.section	.text.riscv_mouse_key_id_to_key_status,"ax",@progbits
	.align	1
	.globl	riscv_mouse_key_id_to_key_status
	.hidden	riscv_mouse_key_id_to_key_status
	.type	riscv_mouse_key_id_to_key_status, @function
riscv_mouse_key_id_to_key_status:
.LFB31:
	.loc 1 461 1 is_stmt 1
	.cfi_startproc
.LVL61:
	.loc 1 462 5
	.loc 1 463 5
.LBB8:
	.loc 1 463 10
	lla	a4,rv_key_ids
	lw	a3,rv_key_num
	.loc 1 463 14 is_stmt 0
	li	a5,0
.LVL62:
.L74:
	.loc 1 463 27 is_stmt 1 discriminator 1
	bne	a5,a3,.L76
.LBE8:
	.loc 1 473 16 is_stmt 0
	li	a0,0
.LVL63:
	ret
.LVL64:
.L76:
.LBB9:
	.loc 1 464 9 is_stmt 1
	.loc 1 464 12 is_stmt 0
	lw	a2,0(a4)
	addi	a4,a4,4
	beq	a2,a0,.L75
	.loc 1 463 44 is_stmt 1 discriminator 2
	addi	a5,a5,1
.LVL65:
	j	.L74
.L75:
.LVL66:
.LBE9:
	.loc 1 470 5
	.loc 1 471 9
	.loc 1 471 19 is_stmt 0
	li	a0,1
.LVL67:
	sll	a0,a0,a5
	.loc 1 475 1
	ret
	.cfi_endproc
.LFE31:
	.size	riscv_mouse_key_id_to_key_status, .-riscv_mouse_key_id_to_key_status
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 153
msg_id_string.0:
	.string	"[M:riscv_ps C:info F: L: ]: mouse_5key = 0x%x --> 0x%x,  combo_key_list = 0x%08X-%08X, combo_key_list_size = 0x%x, combo_key_result = 0x%x, flags = 0x%x"
	.align	2
	.type	msg_id_string.1, @object
	.size	msg_id_string.1, 108
msg_id_string.1:
	.string	"[M:riscv_ps C:info F: L: ]: riscv_mouse_key_init, key_num = %d, rv_key_ids = %d, %d, %d, %d, %d, %d, %d, %d"
	.hidden	new_keys_status_record
	.globl	new_keys_status_record
	.section	.sbss.new_keys_status_record,"aw",@nobits
	.align	2
	.type	new_keys_status_record, @object
	.size	new_keys_status_record, 4
new_keys_status_record:
	.zero	4
	.section	.sdata.combo_key_result,"aw"
	.align	2
	.type	combo_key_result, @object
	.size	combo_key_result, 4
combo_key_result:
	.word	255
	.section	.sbss.mouse_5key_printed,"aw",@nobits
	.align	2
	.type	mouse_5key_printed, @object
	.size	mouse_5key_printed, 4
mouse_5key_printed:
	.zero	4
	.section	.sbss.mouse_5key,"aw",@nobits
	.align	2
	.type	mouse_5key, @object
	.size	mouse_5key, 4
mouse_5key:
	.zero	4
	.hidden	rv_key_ids
	.globl	rv_key_ids
	.section	.bss.rv_key_ids,"aw",@nobits
	.align	2
	.type	rv_key_ids, @object
	.size	rv_key_ids, 40
rv_key_ids:
	.zero	40
	.section	.sbss.rv_key_num,"aw",@nobits
	.align	2
	.type	rv_key_num, @object
	.size	rv_key_num, 4
rv_key_num:
	.zero	4
	.section	.bss.combo_cfg,"aw",@nobits
	.align	2
	.type	combo_cfg, @object
	.size	combo_cfg, 16
combo_cfg:
	.zero	16
	.section	.sbss.start_gpt_free_count,"aw",@nobits
	.align	2
	.type	start_gpt_free_count, @object
	.size	start_gpt_free_count, 4
start_gpt_free_count:
	.zero	4
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 6 "/workdir/airoha/common/applications/hid/inc/hid_common_ccni_msg.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 8 "/workdir/airoha/common/applications/hid/inc/hid_common_hid_app_states.h"
	.file 9 "/workdir/airoha/common/applications/hid/inc/hid_common_key_remap.h"
	.file 10 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 11 "/workdir/airoha/common/applications/hid/inc/hid_common.h"
	.file 12 "/workdir/airoha/common/drivers/chip/ab162x/../inc/hal_ccni.h"
	.file 13 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_peripheral_sampling.h"
	.file 14 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.file 15 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpio_internal.h"
	.file 16 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 17 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_eint_internal.h"
	.file 18 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1478
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x2e
	.4byte	.LASF355
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL16
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x9
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x9
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x9
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x9
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x9
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x9
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x9
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x9
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x9
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x2f
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x9
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x30
	.byte	0x4
	.uleb128 0x9
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x12
	.4byte	0x75
	.uleb128 0x8
	.4byte	0x7c
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0x22
	.byte	0x15
	.4byte	0x34
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x2
	.byte	0x25
	.byte	0x13
	.4byte	0x42
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x31
	.4byte	0xb6
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x3
	.byte	0x3d
	.byte	0xe
	.4byte	0xec
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF22
	.byte	0x3
	.byte	0x42
	.byte	0x3
	.4byte	0xc7
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x3
	.byte	0x45
	.byte	0xe
	.4byte	0x15f
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF38
	.byte	0x3
	.byte	0x57
	.byte	0x3
	.4byte	0xf8
	.uleb128 0x4
	.4byte	.LASF39
	.byte	0x3
	.byte	0x59
	.byte	0x10
	.4byte	0x177
	.uleb128 0x8
	.4byte	0x17c
	.uleb128 0x18
	.4byte	0x19c
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0xec
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x13
	.byte	0
	.uleb128 0x4
	.4byte	.LASF40
	.byte	0x3
	.byte	0x5a
	.byte	0x10
	.4byte	0x1a8
	.uleb128 0x8
	.4byte	0x1ad
	.uleb128 0x18
	.4byte	0x1d7
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0xec
	.uleb128 0x3
	.4byte	0x1d7
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x13
	.byte	0
	.uleb128 0x8
	.4byte	0x1dc
	.uleb128 0x32
	.uleb128 0x4
	.4byte	.LASF41
	.byte	0x3
	.byte	0x5b
	.byte	0x10
	.4byte	0x1e9
	.uleb128 0x8
	.4byte	0x1ee
	.uleb128 0x18
	.4byte	0x209
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0xec
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xb6
	.uleb128 0x13
	.byte	0
	.uleb128 0x4
	.4byte	.LASF42
	.byte	0x3
	.byte	0x5c
	.byte	0x14
	.4byte	0x215
	.uleb128 0x8
	.4byte	0x21a
	.uleb128 0x33
	.4byte	0xb6
	.4byte	0x23d
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0xec
	.uleb128 0x3
	.4byte	0x15f
	.uleb128 0x3
	.4byte	0x23d
	.uleb128 0x3
	.4byte	0x242
	.byte	0
	.uleb128 0x8
	.4byte	0x1d7
	.uleb128 0x8
	.4byte	0xb6
	.uleb128 0x6
	.byte	0x1c
	.byte	0x3
	.byte	0x5e
	.4byte	0x2ab
	.uleb128 0x2
	.4byte	.LASF43
	.byte	0x3
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x2
	.4byte	.LASF44
	.byte	0x3
	.byte	0x60
	.byte	0xe
	.4byte	0xb6
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF45
	.byte	0x3
	.byte	0x61
	.byte	0xe
	.4byte	0xb6
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x3
	.byte	0x62
	.byte	0xf
	.4byte	0x16b
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x3
	.byte	0x63
	.byte	0x15
	.4byte	0x19c
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF48
	.byte	0x3
	.byte	0x64
	.byte	0x12
	.4byte	0x209
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x3
	.byte	0x65
	.byte	0x10
	.4byte	0x1dd
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF50
	.byte	0x3
	.byte	0x66
	.byte	0x3
	.4byte	0x247
	.uleb128 0x34
	.4byte	.LASF356
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x12
	.2byte	0x128
	.byte	0x11
	.4byte	0x33d
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x1f
	.byte	0
	.uleb128 0xa
	.4byte	0x9e
	.4byte	0x34d
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x14
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.2byte	0x407
	.4byte	0x4b1
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x1d
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
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x38
	.byte	0
	.uleb128 0x14
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.2byte	0x466
	.4byte	0x4cb
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x1
	.byte	0
	.uleb128 0x15
	.4byte	.LASF129
	.byte	0x4
	.2byte	0x469
	.byte	0x3
	.4byte	0x4b1
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x5
	.byte	0x50
	.byte	0xe
	.4byte	0x51b
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x8
	.byte	0
	.uleb128 0x6
	.byte	0xa
	.byte	0x5
	.byte	0x5e
	.4byte	0x53e
	.uleb128 0x2
	.4byte	.LASF139
	.byte	0x5
	.byte	0x60
	.byte	0xe
	.4byte	0xaa
	.byte	0
	.uleb128 0x7
	.string	"pin"
	.byte	0x5
	.byte	0x61
	.byte	0xd
	.4byte	0x53e
	.byte	0x2
	.byte	0
	.uleb128 0xa
	.4byte	0x9e
	.4byte	0x54e
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF140
	.byte	0x5
	.byte	0x62
	.byte	0x2
	.4byte	0x51b
	.uleb128 0x9
	.byte	0x1
	.byte	0x2
	.4byte	.LASF141
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x6
	.byte	0x33
	.byte	0x1
	.4byte	0x5e6
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0x81
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0x82
	.uleb128 0x1
	.4byte	.LASF157
	.byte	0x83
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0x84
	.uleb128 0x1
	.4byte	.LASF159
	.byte	0x85
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0x86
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x87
	.byte	0
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x7
	.byte	0x31
	.byte	0x1
	.4byte	0x623
	.uleb128 0x1
	.4byte	.LASF162
	.byte	0
	.uleb128 0x1
	.4byte	.LASF163
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF164
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF165
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF166
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF167
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF168
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF169
	.byte	0x7
	.byte	0
	.uleb128 0x6
	.byte	0x2
	.byte	0x7
	.byte	0x3f
	.4byte	0x646
	.uleb128 0x2
	.4byte	.LASF170
	.byte	0x7
	.byte	0x41
	.byte	0xd
	.4byte	0x9e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF171
	.byte	0x7
	.byte	0x42
	.byte	0xd
	.4byte	0x9e
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF172
	.byte	0x7
	.byte	0x44
	.byte	0x2
	.4byte	0x623
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x8
	.byte	0x32
	.byte	0x1
	.4byte	0x74f
	.uleb128 0x1
	.4byte	.LASF173
	.byte	0
	.uleb128 0x1
	.4byte	.LASF174
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF175
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF176
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF177
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF178
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF180
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF182
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF183
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF184
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF188
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF189
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF190
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF191
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF192
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF193
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF194
	.byte	0x41
	.uleb128 0x1
	.4byte	.LASF195
	.byte	0x42
	.uleb128 0x1
	.4byte	.LASF196
	.byte	0x43
	.uleb128 0x1
	.4byte	.LASF197
	.byte	0x44
	.uleb128 0x1
	.4byte	.LASF198
	.byte	0x4a
	.uleb128 0x1
	.4byte	.LASF199
	.byte	0x4b
	.uleb128 0x1
	.4byte	.LASF200
	.byte	0x4c
	.uleb128 0x1
	.4byte	.LASF201
	.byte	0x4d
	.uleb128 0x1
	.4byte	.LASF202
	.byte	0x4e
	.uleb128 0x1
	.4byte	.LASF203
	.byte	0x80
	.uleb128 0x1
	.4byte	.LASF204
	.byte	0x81
	.uleb128 0x1
	.4byte	.LASF205
	.byte	0x82
	.uleb128 0x1
	.4byte	.LASF206
	.byte	0x83
	.uleb128 0x1
	.4byte	.LASF207
	.byte	0x84
	.uleb128 0x1
	.4byte	.LASF208
	.byte	0x8a
	.uleb128 0x1
	.4byte	.LASF209
	.byte	0x8b
	.uleb128 0x1
	.4byte	.LASF210
	.byte	0x8c
	.uleb128 0x1
	.4byte	.LASF211
	.byte	0x8d
	.uleb128 0x1
	.4byte	.LASF212
	.byte	0x8e
	.byte	0
	.uleb128 0x20
	.2byte	0x11c
	.2byte	0x109
	.byte	0xd
	.4byte	0x773
	.uleb128 0x21
	.4byte	.LASF213
	.2byte	0x10a
	.byte	0x1a
	.4byte	0x773
	.uleb128 0x35
	.string	"x_y"
	.byte	0x9
	.2byte	0x10c
	.byte	0x1a
	.4byte	0x773
	.byte	0
	.uleb128 0xa
	.4byte	0xb6
	.4byte	0x783
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x46
	.byte	0
	.uleb128 0x22
	.2byte	0x23c
	.2byte	0x105
	.4byte	0x7bb
	.uleb128 0x16
	.4byte	.LASF214
	.2byte	0x106
	.byte	0x16
	.4byte	0xaa
	.byte	0
	.uleb128 0x16
	.4byte	.LASF215
	.2byte	0x107
	.byte	0x16
	.4byte	0xaa
	.byte	0x2
	.uleb128 0x16
	.4byte	.LASF216
	.2byte	0x108
	.byte	0x16
	.4byte	0x773
	.byte	0x4
	.uleb128 0x36
	.4byte	0x74f
	.2byte	0x120
	.byte	0
	.uleb128 0x20
	.2byte	0x23c
	.2byte	0x103
	.byte	0x5
	.4byte	0x7d7
	.uleb128 0x21
	.4byte	.LASF217
	.2byte	0x104
	.byte	0x12
	.4byte	0xb6
	.uleb128 0x37
	.4byte	0x783
	.byte	0
	.uleb128 0x22
	.2byte	0x240
	.2byte	0x101
	.4byte	0x7f4
	.uleb128 0x16
	.4byte	.LASF218
	.2byte	0x102
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x23
	.4byte	0x7bb
	.byte	0x4
	.byte	0
	.uleb128 0x15
	.4byte	.LASF219
	.byte	0x9
	.2byte	0x111
	.byte	0x1e
	.4byte	0x7d7
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0x50
	.4byte	0x850
	.uleb128 0x2
	.4byte	.LASF220
	.byte	0xa
	.byte	0x51
	.byte	0xd
	.4byte	0x9e
	.byte	0
	.uleb128 0x7
	.string	"k"
	.byte	0xa
	.byte	0x52
	.byte	0xd
	.4byte	0x9e
	.byte	0x1
	.uleb128 0x7
	.string	"x"
	.byte	0xa
	.byte	0x53
	.byte	0xd
	.4byte	0x92
	.byte	0x2
	.uleb128 0x7
	.string	"y"
	.byte	0xa
	.byte	0x54
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x7
	.string	"z1"
	.byte	0xa
	.byte	0x55
	.byte	0xc
	.4byte	0x86
	.byte	0x6
	.uleb128 0x7
	.string	"z2"
	.byte	0xa
	.byte	0x56
	.byte	0xc
	.4byte	0x86
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF221
	.byte	0xa
	.byte	0x57
	.byte	0x1f
	.4byte	0x801
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0x88
	.4byte	0x8a2
	.uleb128 0x2
	.4byte	.LASF220
	.byte	0xa
	.byte	0x89
	.byte	0xd
	.4byte	0x9e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF222
	.byte	0xa
	.byte	0x8a
	.byte	0xd
	.4byte	0x9e
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF213
	.byte	0xa
	.byte	0x8b
	.byte	0xd
	.4byte	0x33d
	.byte	0x2
	.uleb128 0x7
	.string	"x"
	.byte	0xa
	.byte	0x8c
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x7
	.string	"y"
	.byte	0xa
	.byte	0x8d
	.byte	0xd
	.4byte	0x92
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF223
	.byte	0xa
	.byte	0x8e
	.byte	0x1e
	.4byte	0x85c
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0x90
	.4byte	0x8f4
	.uleb128 0x2
	.4byte	.LASF220
	.byte	0xa
	.byte	0x91
	.byte	0xd
	.4byte	0x9e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF224
	.byte	0xa
	.byte	0x92
	.byte	0xe
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF225
	.byte	0xa
	.byte	0x93
	.byte	0xd
	.4byte	0x9e
	.byte	0x3
	.uleb128 0x7
	.string	"x"
	.byte	0xa
	.byte	0x94
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x7
	.string	"y"
	.byte	0xa
	.byte	0x95
	.byte	0xd
	.4byte	0x92
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF226
	.byte	0xa
	.byte	0x96
	.byte	0x1f
	.4byte	0x8ae
	.uleb128 0xa
	.4byte	0x9e
	.4byte	0x910
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0xa2
	.4byte	0x94d
	.uleb128 0x2
	.4byte	.LASF220
	.byte	0xa
	.byte	0xa3
	.byte	0xd
	.4byte	0x9e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF222
	.byte	0xa
	.byte	0xa4
	.byte	0xd
	.4byte	0x9e
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF213
	.byte	0xa
	.byte	0xa5
	.byte	0xd
	.4byte	0x900
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF227
	.byte	0xa
	.byte	0xa6
	.byte	0xd
	.4byte	0x9e
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF228
	.byte	0xa
	.byte	0xa7
	.byte	0x1e
	.4byte	0x910
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0xa9
	.4byte	0x996
	.uleb128 0x2
	.4byte	.LASF220
	.byte	0xa
	.byte	0xaa
	.byte	0xd
	.4byte	0x9e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF224
	.byte	0xa
	.byte	0xab
	.byte	0xd
	.4byte	0x996
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF225
	.byte	0xa
	.byte	0xac
	.byte	0xd
	.4byte	0x9e
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF227
	.byte	0xa
	.byte	0xad
	.byte	0xd
	.4byte	0x33d
	.byte	0x6
	.byte	0
	.uleb128 0xa
	.4byte	0x9e
	.4byte	0x9a6
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF229
	.byte	0xa
	.byte	0xae
	.byte	0x1f
	.4byte	0x959
	.uleb128 0xa
	.4byte	0x9e
	.4byte	0x9c2
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x6
	.byte	0x2
	.byte	0xb
	.byte	0x49
	.4byte	0x9e4
	.uleb128 0x7
	.string	"id"
	.byte	0xb
	.byte	0x4b
	.byte	0xd
	.4byte	0x9e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF230
	.byte	0xb
	.byte	0x4c
	.byte	0xd
	.4byte	0x9e
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF231
	.byte	0xb
	.byte	0x4d
	.byte	0x2
	.4byte	0x9c2
	.uleb128 0x38
	.byte	0x8
	.byte	0xb
	.byte	0x53
	.byte	0x5
	.4byte	0xa31
	.uleb128 0x11
	.4byte	.LASF232
	.byte	0x54
	.byte	0x25
	.4byte	0x850
	.uleb128 0x11
	.4byte	.LASF233
	.byte	0x56
	.byte	0x23
	.4byte	0x8a2
	.uleb128 0x11
	.4byte	.LASF234
	.byte	0x57
	.byte	0x28
	.4byte	0x8f4
	.uleb128 0x11
	.4byte	.LASF235
	.byte	0x59
	.byte	0x20
	.4byte	0x94d
	.uleb128 0x11
	.4byte	.LASF236
	.byte	0x5a
	.byte	0x25
	.4byte	0x9a6
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.byte	0xb
	.byte	0x4f
	.4byte	0xa40
	.uleb128 0x23
	.4byte	0x9f0
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF237
	.byte	0xb
	.byte	0x5f
	.byte	0xa
	.4byte	0xa31
	.uleb128 0x6
	.byte	0x8
	.byte	0xb
	.byte	0x61
	.4byte	0xa6f
	.uleb128 0x2
	.4byte	.LASF238
	.byte	0xb
	.byte	0x62
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF239
	.byte	0xb
	.byte	0x63
	.byte	0xe
	.4byte	0xb6
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF240
	.byte	0xb
	.byte	0x67
	.byte	0x2
	.4byte	0xa4c
	.uleb128 0x12
	.4byte	0xa6f
	.uleb128 0x6
	.byte	0x3
	.byte	0xb
	.byte	0x69
	.4byte	0xab0
	.uleb128 0x2
	.4byte	.LASF241
	.byte	0xb
	.byte	0x6a
	.byte	0xd
	.4byte	0x9e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF242
	.byte	0xb
	.byte	0x6b
	.byte	0xd
	.4byte	0x9e
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF243
	.byte	0xb
	.byte	0x6c
	.byte	0xd
	.4byte	0x9e
	.byte	0x2
	.byte	0
	.uleb128 0x4
	.4byte	.LASF244
	.byte	0xb
	.byte	0x6d
	.byte	0x3
	.4byte	0xa80
	.uleb128 0x6
	.byte	0x18
	.byte	0xb
	.byte	0x7e
	.4byte	0xb13
	.uleb128 0x2
	.4byte	.LASF245
	.byte	0xb
	.byte	0x7f
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF246
	.byte	0xb
	.byte	0x80
	.byte	0xe
	.4byte	0xb6
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF247
	.byte	0xb
	.byte	0x81
	.byte	0xe
	.4byte	0xb6
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF248
	.byte	0xb
	.byte	0x82
	.byte	0xe
	.4byte	0xb6
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF249
	.byte	0xb
	.byte	0x83
	.byte	0x17
	.4byte	0xc2
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF250
	.byte	0xb
	.byte	0x84
	.byte	0xd
	.4byte	0x9e
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF251
	.byte	0xb
	.byte	0x94
	.byte	0x3
	.4byte	0xabc
	.uleb128 0x6
	.byte	0x40
	.byte	0xb
	.byte	0x96
	.4byte	0xbdd
	.uleb128 0x2
	.4byte	.LASF248
	.byte	0xb
	.byte	0x97
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF252
	.byte	0xb
	.byte	0x98
	.byte	0xe
	.4byte	0xb6
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF253
	.byte	0xb
	.byte	0x9b
	.byte	0x1e
	.4byte	0xbdd
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF254
	.byte	0xb
	.byte	0x9c
	.byte	0xe
	.4byte	0xb6
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF255
	.byte	0xb
	.byte	0x9d
	.byte	0xe
	.4byte	0xb6
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF256
	.byte	0xb
	.byte	0x9f
	.byte	0x1e
	.4byte	0x9e4
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF257
	.byte	0xb
	.byte	0xa0
	.byte	0x1e
	.4byte	0x9e4
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF258
	.byte	0xb
	.byte	0xa5
	.byte	0xe
	.4byte	0xb6
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF259
	.byte	0xb
	.byte	0xa6
	.byte	0xe
	.4byte	0xb6
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF260
	.byte	0xb
	.byte	0xae
	.byte	0xe
	.4byte	0xbe2
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF261
	.byte	0xb
	.byte	0xb1
	.byte	0xd
	.4byte	0x9b2
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF262
	.byte	0xb
	.byte	0xb2
	.byte	0xd
	.4byte	0x9e
	.byte	0x38
	.uleb128 0x7
	.string	"rr"
	.byte	0xb
	.byte	0xbb
	.byte	0x1d
	.4byte	0x646
	.byte	0x39
	.uleb128 0x7
	.string	"deb"
	.byte	0xb
	.byte	0xbd
	.byte	0x17
	.4byte	0xab0
	.byte	0x3b
	.byte	0
	.uleb128 0x8
	.4byte	0xa7b
	.uleb128 0xa
	.4byte	0xaa
	.4byte	0xbf2
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF263
	.byte	0xb
	.byte	0xbf
	.byte	0x3
	.4byte	0xb1f
	.uleb128 0x39
	.2byte	0x16ec
	.byte	0xb
	.byte	0xc1
	.byte	0x9
	.4byte	0xc4b
	.uleb128 0x7
	.string	"app"
	.byte	0xb
	.byte	0xc3
	.byte	0x1b
	.4byte	0xbf2
	.byte	0
	.uleb128 0x7
	.string	"hid"
	.byte	0xb
	.byte	0xc4
	.byte	0x1b
	.4byte	0xb13
	.byte	0x40
	.uleb128 0x7
	.string	"dbg"
	.byte	0xb
	.byte	0xc5
	.byte	0x17
	.4byte	0x54e
	.byte	0x58
	.uleb128 0x2
	.4byte	.LASF264
	.byte	0xb
	.byte	0xc7
	.byte	0x17
	.4byte	0xc4b
	.byte	0x62
	.uleb128 0x3a
	.4byte	.LASF265
	.byte	0xb
	.byte	0xca
	.byte	0x1d
	.4byte	0xc5b
	.2byte	0x16e2
	.byte	0
	.uleb128 0xa
	.4byte	0x7f4
	.4byte	0xc5b
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0xa
	.4byte	0xa40
	.4byte	0xc6b
	.uleb128 0xb
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF266
	.byte	0xb
	.byte	0xcc
	.byte	0x3
	.4byte	0xbfe
	.uleb128 0x19
	.4byte	.LASF287
	.byte	0xb
	.byte	0xd2
	.byte	0x19
	.4byte	0xc83
	.uleb128 0x8
	.4byte	0xc6b
	.uleb128 0x14
	.byte	0x5
	.4byte	0x65
	.byte	0xc
	.2byte	0x120
	.4byte	0xcb4
	.uleb128 0xd
	.4byte	.LASF267
	.sleb128 -4
	.uleb128 0xd
	.4byte	.LASF268
	.sleb128 -3
	.uleb128 0xd
	.4byte	.LASF269
	.sleb128 -2
	.uleb128 0xd
	.4byte	.LASF270
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF271
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LASF272
	.byte	0xc
	.2byte	0x126
	.byte	0x3
	.4byte	0xc88
	.uleb128 0x8
	.4byte	0x9e
	.uleb128 0xe
	.4byte	0x2d
	.byte	0xd
	.byte	0x2d
	.byte	0xe
	.4byte	0xd09
	.uleb128 0x1
	.4byte	.LASF273
	.byte	0
	.uleb128 0x1
	.4byte	.LASF274
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF275
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF276
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF277
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF278
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF279
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF280
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF281
	.byte	0x8
	.byte	0
	.uleb128 0x6
	.byte	0x18
	.byte	0xd
	.byte	0x56
	.4byte	0xd60
	.uleb128 0x2
	.4byte	.LASF282
	.byte	0xd
	.byte	0x57
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF283
	.byte	0xd
	.byte	0x58
	.byte	0xe
	.4byte	0xb6
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF171
	.byte	0xd
	.byte	0x59
	.byte	0xe
	.4byte	0xb6
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF170
	.byte	0xd
	.byte	0x5a
	.byte	0xe
	.4byte	0xb6
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF284
	.byte	0xd
	.byte	0x5b
	.byte	0xe
	.4byte	0xb6
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF285
	.byte	0xd
	.byte	0x5c
	.byte	0xe
	.4byte	0xb6
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF286
	.byte	0xd
	.byte	0x5f
	.byte	0x2
	.4byte	0xd09
	.uleb128 0x19
	.4byte	.LASF288
	.byte	0xd
	.byte	0x63
	.byte	0x16
	.4byte	0xd60
	.uleb128 0xe
	.4byte	0x2d
	.byte	0xe
	.byte	0x6e
	.byte	0xe
	.4byte	0xd9d
	.uleb128 0x1
	.4byte	.LASF289
	.byte	0
	.uleb128 0x1
	.4byte	.LASF290
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF291
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF292
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.byte	0xf
	.byte	0x89
	.4byte	0xdc0
	.uleb128 0x2
	.4byte	.LASF293
	.byte	0xf
	.byte	0x8a
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF294
	.byte	0xf
	.byte	0x8b
	.byte	0xe
	.4byte	0xb6
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF295
	.byte	0xf
	.byte	0x8c
	.byte	0x3
	.4byte	0xd9d
	.uleb128 0x14
	.byte	0x5
	.4byte	0x65
	.byte	0x10
	.2byte	0x153
	.4byte	0xe0a
	.uleb128 0xd
	.4byte	.LASF296
	.sleb128 -7
	.uleb128 0xd
	.4byte	.LASF297
	.sleb128 -6
	.uleb128 0xd
	.4byte	.LASF298
	.sleb128 -5
	.uleb128 0xd
	.4byte	.LASF299
	.sleb128 -4
	.uleb128 0xd
	.4byte	.LASF300
	.sleb128 -3
	.uleb128 0xd
	.4byte	.LASF301
	.sleb128 -2
	.uleb128 0xd
	.4byte	.LASF302
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF303
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LASF304
	.byte	0x10
	.2byte	0x15c
	.byte	0x3
	.4byte	0xdcc
	.uleb128 0x6
	.byte	0x10
	.byte	0x1
	.byte	0x3f
	.4byte	0xe54
	.uleb128 0x2
	.4byte	.LASF253
	.byte	0x1
	.byte	0x40
	.byte	0x18
	.4byte	0xe54
	.byte	0
	.uleb128 0x2
	.4byte	.LASF254
	.byte	0x1
	.byte	0x41
	.byte	0xe
	.4byte	0xb6
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF255
	.byte	0x1
	.byte	0x42
	.byte	0xe
	.4byte	0xb6
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF305
	.byte	0x1
	.byte	0x43
	.byte	0xe
	.4byte	0xb6
	.byte	0xc
	.byte	0
	.uleb128 0x8
	.4byte	0xa6f
	.uleb128 0x4
	.4byte	.LASF306
	.byte	0x1
	.byte	0x44
	.byte	0x2
	.4byte	0xe17
	.uleb128 0xc
	.4byte	.LASF307
	.byte	0x4f
	.byte	0x11
	.4byte	0xb6
	.uleb128 0x5
	.byte	0x3
	.4byte	start_gpt_free_count
	.uleb128 0xc
	.4byte	.LASF308
	.byte	0x50
	.byte	0x1a
	.4byte	0xe59
	.uleb128 0x5
	.byte	0x3
	.4byte	combo_cfg
	.uleb128 0xc
	.4byte	.LASF309
	.byte	0x52
	.byte	0x11
	.4byte	0xb6
	.uleb128 0x5
	.byte	0x3
	.4byte	rv_key_num
	.uleb128 0xa
	.4byte	0xb6
	.4byte	0xea8
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x24
	.4byte	.LASF310
	.byte	0x53
	.4byte	0xe98
	.uleb128 0x5
	.byte	0x3
	.4byte	rv_key_ids
	.uleb128 0xc
	.4byte	.LASF311
	.byte	0x55
	.byte	0x11
	.4byte	0xb6
	.uleb128 0x5
	.byte	0x3
	.4byte	mouse_5key
	.uleb128 0xc
	.4byte	.LASF312
	.byte	0x56
	.byte	0x11
	.4byte	0xb6
	.uleb128 0x5
	.byte	0x3
	.4byte	mouse_5key_printed
	.uleb128 0xc
	.4byte	.LASF313
	.byte	0x57
	.byte	0x11
	.4byte	0xb6
	.uleb128 0x5
	.byte	0x3
	.4byte	combo_key_result
	.uleb128 0x24
	.4byte	.LASF314
	.byte	0x5a
	.4byte	0xb6
	.uleb128 0x5
	.byte	0x3
	.4byte	new_keys_status_record
	.uleb128 0x3b
	.4byte	.LASF315
	.byte	0xd
	.byte	0x67
	.byte	0x13
	.4byte	0xcb4
	.4byte	0xf16
	.uleb128 0x3
	.4byte	0xcc1
	.uleb128 0x3
	.4byte	0x9e
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF317
	.byte	0xb
	.byte	0xe7
	.4byte	0xf27
	.uleb128 0x3
	.4byte	0x9e
	.byte	0
	.uleb128 0x25
	.4byte	.LASF316
	.2byte	0x199
	.4byte	0xe0a
	.4byte	0xf46
	.uleb128 0x3
	.4byte	0xb6
	.uleb128 0x3
	.4byte	0xb6
	.uleb128 0x3
	.4byte	0x242
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF318
	.byte	0xb
	.byte	0xef
	.4byte	0xf61
	.uleb128 0x3
	.4byte	0xf61
	.uleb128 0x3
	.4byte	0x242
	.uleb128 0x3
	.4byte	0x242
	.byte	0
	.uleb128 0x8
	.4byte	0xe54
	.uleb128 0x25
	.4byte	.LASF319
	.2byte	0x17b
	.4byte	0xe0a
	.4byte	0xf80
	.uleb128 0x3
	.4byte	0x4cb
	.uleb128 0x3
	.4byte	0x242
	.byte	0
	.uleb128 0x3c
	.4byte	.LASF320
	.byte	0x3
	.2byte	0x129
	.byte	0xd
	.4byte	0xfa3
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0xec
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xb6
	.uleb128 0x13
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF321
	.byte	0x11
	.byte	0x9a
	.4byte	0xfb9
	.uleb128 0x3
	.4byte	0x242
	.uleb128 0x3
	.4byte	0x242
	.byte	0
	.uleb128 0x3d
	.4byte	.LASF338
	.byte	0x1
	.2byte	0x1cc
	.byte	0xa
	.4byte	0xb6
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x100d
	.uleb128 0x26
	.4byte	.LASF323
	.2byte	0x1cc
	.byte	0x34
	.4byte	0xb6
	.4byte	.LLST12
	.uleb128 0x3e
	.4byte	.LASF322
	.byte	0x1
	.2byte	0x1ce
	.byte	0x9
	.4byte	0x65
	.4byte	.LLST13
	.uleb128 0x27
	.4byte	.LLRL14
	.uleb128 0x3f
	.string	"idx"
	.byte	0x1
	.2byte	0x1cf
	.byte	0xe
	.4byte	0x65
	.4byte	.LLST15
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF327
	.2byte	0x1b3
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1058
	.uleb128 0x26
	.4byte	.LASF324
	.2byte	0x1b3
	.byte	0x31
	.4byte	0xb6
	.4byte	.LLST11
	.uleb128 0x40
	.string	"msg"
	.byte	0x1
	.2byte	0x1b5
	.byte	0xd
	.4byte	0x900
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xf
	.4byte	.LVL60
	.4byte	0xefb
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x35
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF330
	.2byte	0x199
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10b4
	.uleb128 0x41
	.4byte	.LBB7
	.4byte	.LBE7-.LBB7
	.uleb128 0x42
	.4byte	.LASF325
	.byte	0x1
	.2byte	0x1a4
	.byte	0x29
	.4byte	0x2ab
	.uleb128 0x1d
	.4byte	.LASF326
	.2byte	0x1a4
	.byte	0x84
	.4byte	0x10c4
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0xf
	.4byte	.LVL57
	.4byte	0xf80
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x37
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xa
	.4byte	0x7c
	.4byte	0x10c4
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x98
	.byte	0
	.uleb128 0x12
	.4byte	0x10b4
	.uleb128 0x28
	.4byte	.LASF336
	.2byte	0x192
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1b
	.4byte	.LASF328
	.2byte	0x161
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10fe
	.uleb128 0x29
	.4byte	.LASF329
	.2byte	0x161
	.byte	0x31
	.4byte	0xb6
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF331
	.2byte	0x145
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x118c
	.uleb128 0x27
	.4byte	.LLRL10
	.uleb128 0x1d
	.4byte	.LASF332
	.2byte	0x149
	.byte	0x12
	.4byte	0xb6
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1d
	.4byte	.LASF333
	.2byte	0x14a
	.byte	0x12
	.4byte	0xb6
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1e
	.4byte	.LVL51
	.4byte	0x1325
	.uleb128 0x17
	.4byte	.LVL52
	.4byte	0xf66
	.4byte	0x1153
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x17
	.4byte	.LVL53
	.4byte	0xf27
	.4byte	0x1167
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x17
	.4byte	.LVL54
	.4byte	0xf16
	.4byte	0x117a
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x39
	.byte	0
	.uleb128 0xf
	.4byte	.LVL55
	.4byte	0xf66
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x43
	.4byte	.LASF357
	.byte	0x1
	.2byte	0x13f
	.byte	0xa
	.4byte	0xb6
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1b
	.4byte	.LASF334
	.2byte	0x139
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x11c7
	.uleb128 0x29
	.4byte	.LASF285
	.2byte	0x139
	.byte	0x2c
	.4byte	0xb6
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF335
	.2byte	0x134
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1202
	.uleb128 0x2a
	.4byte	.LVL42
	.4byte	0xf46
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	combo_cfg
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	combo_cfg+4
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	combo_cfg+8
	.byte	0
	.byte	0
	.uleb128 0x28
	.4byte	.LASF337
	.2byte	0x11f
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x44
	.4byte	.LASF339
	.byte	0x1
	.byte	0xfb
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1268
	.uleb128 0x2b
	.4byte	.LASF340
	.byte	0xfb
	.byte	0x2f
	.4byte	0x242
	.4byte	.LLST7
	.uleb128 0x10
	.4byte	.LASF324
	.byte	0xfd
	.byte	0xe
	.4byte	0xb6
	.4byte	.LLST8
	.uleb128 0x17
	.4byte	.LVL38
	.4byte	0xf66
	.4byte	0x125e
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x1e
	.4byte	.LVL39
	.4byte	0x1416
	.byte	0
	.uleb128 0x45
	.4byte	.LASF341
	.byte	0x1
	.byte	0xee
	.byte	0x6
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x128e
	.uleb128 0x2a
	.4byte	.LVL35
	.4byte	0xf66
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x46
	.4byte	.LASF358
	.byte	0x1
	.byte	0xe9
	.byte	0x6
	.byte	0x1
	.uleb128 0x2c
	.4byte	.LASF342
	.byte	0xcd
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1310
	.uleb128 0x2d
	.string	"idx"
	.byte	0xcf
	.4byte	0xb6
	.4byte	.LLST9
	.uleb128 0x47
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.4byte	0x1306
	.uleb128 0x19
	.4byte	.LASF325
	.byte	0x1
	.byte	0xd9
	.byte	0x25
	.4byte	0x2ab
	.uleb128 0xc
	.4byte	.LASF326
	.byte	0xd9
	.byte	0x80
	.4byte	0x1320
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0xf
	.4byte	.LVL46
	.4byte	0xf80
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.byte	0
	.uleb128 0x1e
	.4byte	.LVL45
	.4byte	0x11c7
	.byte	0
	.uleb128 0xa
	.4byte	0x7c
	.4byte	0x1320
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x6b
	.byte	0
	.uleb128 0x12
	.4byte	0x1310
	.uleb128 0x2c
	.4byte	.LASF343
	.byte	0xa6
	.byte	0xa
	.4byte	0xb6
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x13bd
	.uleb128 0x48
	.string	"ret"
	.byte	0x1
	.byte	0xa8
	.byte	0xe
	.4byte	0xb6
	.byte	0xff
	.uleb128 0x10
	.4byte	.LASF344
	.byte	0xa9
	.byte	0xe
	.4byte	0xb6
	.4byte	.LLST4
	.uleb128 0x10
	.4byte	.LASF345
	.byte	0xa9
	.byte	0x1b
	.4byte	0xb6
	.4byte	.LLST5
	.uleb128 0x10
	.4byte	.LASF346
	.byte	0xaa
	.byte	0xe
	.4byte	0xb6
	.4byte	.LLST6
	.uleb128 0xc
	.4byte	.LASF347
	.byte	0xab
	.byte	0x19
	.4byte	0xdc0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xc
	.4byte	.LASF348
	.byte	0xb2
	.byte	0xe
	.4byte	0xb6
	.uleb128 0x4
	.byte	0x7b
	.sleb128 0
	.byte	0x20
	.byte	0x9f
	.uleb128 0xc
	.4byte	.LASF349
	.byte	0xb3
	.byte	0xe
	.4byte	0xb6
	.uleb128 0x4
	.byte	0x76
	.sleb128 0
	.byte	0x20
	.byte	0x9f
	.uleb128 0xf
	.4byte	.LVL24
	.4byte	0xfa3
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.uleb128 0x49
	.4byte	.LASF350
	.byte	0x1
	.byte	0x93
	.byte	0x6
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1416
	.uleb128 0x1f
	.4byte	.LASF348
	.byte	0x22
	.4byte	0x242
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1f
	.4byte	.LASF349
	.byte	0x3f
	.4byte	0x242
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2b
	.4byte	.LASF351
	.byte	0x93
	.byte	0x5b
	.4byte	0xb6
	.4byte	.LLST2
	.uleb128 0x1f
	.4byte	.LASF352
	.byte	0x6d
	.4byte	0x55a
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x10
	.4byte	.LASF353
	.byte	0x95
	.byte	0xe
	.4byte	0xb6
	.4byte	.LLST3
	.byte	0
	.uleb128 0x4a
	.4byte	.LASF354
	.byte	0x1
	.byte	0x61
	.byte	0xa
	.4byte	0xb6
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x2d
	.string	"idx"
	.byte	0x63
	.4byte	0xb6
	.4byte	.LLST0
	.uleb128 0xc
	.4byte	.LASF347
	.byte	0x66
	.byte	0x19
	.4byte	0xdc0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x10
	.4byte	.LASF348
	.byte	0x79
	.byte	0xe
	.4byte	0xb6
	.4byte	.LLST1
	.uleb128 0xc
	.4byte	.LASF349
	.byte	0x7a
	.byte	0xe
	.4byte	0xb6
	.uleb128 0x1
	.byte	0x56
	.uleb128 0xf
	.4byte	.LVL0
	.4byte	0xfa3
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xf
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 11
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x14
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
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x1e
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 147
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 10
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
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
	.sleb128 16
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
	.uleb128 0x26
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
	.uleb128 0x27
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0x2c
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
	.uleb128 0x2d
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
	.sleb128 14
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2e
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
	.uleb128 0x2f
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
	.uleb128 0x30
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x33
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
	.uleb128 0x34
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x35
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
	.uleb128 0x36
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x38
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
	.uleb128 0x39
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
	.uleb128 0x3a
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
	.uleb128 0x3b
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
	.uleb128 0x3c
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
	.uleb128 0x3d
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
	.uleb128 0x3e
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
	.uleb128 0x3f
	.uleb128 0x34
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
	.uleb128 0x40
	.uleb128 0x34
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x41
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x42
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
	.uleb128 0x43
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
	.uleb128 0xb
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
	.uleb128 0x46
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
	.uleb128 0x47
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
	.uleb128 0x48
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
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x49
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
	.4byte	.LVL61
	.byte	0x4
	.uleb128 .LVL61-.LVL61
	.uleb128 .LVL63-.LVL61
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL63-.LVL61
	.uleb128 .LVL64-.LVL61
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
	.uleb128 .LVL64-.LVL61
	.uleb128 .LVL67-.LVL61
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL67-.LVL61
	.uleb128 .LFE31-.LVL61
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
.LLST13:
	.byte	0x6
	.4byte	.LVL61
	.byte	0x4
	.uleb128 .LVL61-.LVL61
	.uleb128 .LVL63-.LVL61
	.uleb128 0x3
	.byte	0x9
	.byte	0xff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL64-.LVL61
	.uleb128 .LVL66-.LVL61
	.uleb128 0x3
	.byte	0x9
	.byte	0xff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL66-.LVL61
	.uleb128 .LFE31-.LVL61
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL61
	.byte	0x4
	.uleb128 .LVL61-.LVL61
	.uleb128 .LVL62-.LVL61
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL62-.LVL61
	.uleb128 .LFE31-.LVL61
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL58
	.byte	0x4
	.uleb128 .LVL58-.LVL58
	.uleb128 .LVL59-.LVL58
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL59-.LVL58
	.uleb128 .LFE30-.LVL58
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
.LLST7:
	.byte	0x6
	.4byte	.LVL36
	.byte	0x4
	.uleb128 .LVL36-.LVL36
	.uleb128 .LVL37-.LVL36
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL37-.LVL36
	.uleb128 .LVL40-.LVL36
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL40-.LVL36
	.uleb128 .LFE21-.LVL36
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
.LLST8:
	.byte	0x6
	.4byte	.LVL36
	.byte	0x4
	.uleb128 .LVL36-.LVL36
	.uleb128 .LVL39-.LVL36
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL39-.LVL36
	.uleb128 .LVL41-.LVL36
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL41-.LVL36
	.uleb128 .LFE21-.LVL36
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
.LLST9:
	.byte	0x6
	.4byte	.LVL43
	.byte	0x4
	.uleb128 .LVL43-.LVL43
	.uleb128 .LVL44-.LVL43
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL44-.LVL43
	.uleb128 .LVL45-1-.LVL43
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL47-.LVL43
	.uleb128 .LVL48-.LVL43
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL48-.LVL43
	.uleb128 .LVL49-.LVL43
	.uleb128 0x3
	.byte	0x7f
	.sleb128 -1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL49-.LVL43
	.uleb128 .LFE18-.LVL43
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL31-.LVL30
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL31-.LVL30
	.uleb128 .LVL32-.LVL30
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL32-.LVL30
	.uleb128 .LFE17-.LVL30
	.uleb128 0x2
	.byte	0x7e
	.sleb128 -8
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL31-.LVL30
	.uleb128 0x2
	.byte	0x7d
	.sleb128 4
	.byte	0x4
	.uleb128 .LVL31-.LVL30
	.uleb128 .LVL33-.LVL30
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL33-.LVL30
	.uleb128 .LFE17-.LVL30
	.uleb128 0x2
	.byte	0x7e
	.sleb128 -4
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL27-.LVL26
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL27-.LVL26
	.uleb128 .LVL28-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL29-.LVL26
	.uleb128 .LFE17-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL9-.LVL8
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL9-.LVL8
	.uleb128 .LFE16-.LVL8
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xc
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL10
	.byte	0x4
	.uleb128 .LVL10-.LVL10
	.uleb128 .LVL11-.LVL10
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL11-.LVL10
	.uleb128 .LVL12-.LVL10
	.uleb128 0x4
	.byte	0x7f
	.sleb128 0
	.byte	0x20
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL12-.LVL10
	.uleb128 .LVL13-.LVL10
	.uleb128 0x10
	.byte	0x31
	.byte	0x7c
	.sleb128 0
	.byte	0x3
	.4byte	rv_key_ids
	.byte	0x22
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x24
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL14-.LVL10
	.uleb128 .LVL15-.LVL10
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL15-.LVL10
	.uleb128 .LVL16-.LVL10
	.uleb128 0x4
	.byte	0x7f
	.sleb128 0
	.byte	0x20
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL16-.LVL10
	.uleb128 .LVL17-.LVL10
	.uleb128 0x12
	.byte	0x31
	.byte	0x7c
	.sleb128 0
	.byte	0x3
	.4byte	rv_key_ids
	.byte	0x22
	.byte	0x6
	.byte	0x8
	.byte	0x20
	.byte	0x1c
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x24
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL17-.LVL10
	.uleb128 .LVL18-.LVL10
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL18-.LVL10
	.uleb128 .LVL19-.LVL10
	.uleb128 0x10
	.byte	0x31
	.byte	0x7c
	.sleb128 0
	.byte	0x3
	.4byte	rv_key_ids
	.byte	0x22
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x24
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL20-.LVL10
	.uleb128 .LVL21-.LVL10
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL21-.LVL10
	.uleb128 .LVL22-.LVL10
	.uleb128 0x12
	.byte	0x31
	.byte	0x7c
	.sleb128 0
	.byte	0x3
	.4byte	rv_key_ids
	.byte	0x22
	.byte	0x6
	.byte	0x8
	.byte	0x20
	.byte	0x1c
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x24
	.byte	0x9f
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL3-.LVL2
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.LVL2
	.uleb128 .LFE15-.LVL2
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL4-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL4-.LVL1
	.uleb128 .LVL5-.LVL1
	.uleb128 0x5
	.byte	0x91
	.sleb128 -20
	.byte	0x6
	.byte	0x20
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.LVL1
	.uleb128 .LVL6-.LVL1
	.uleb128 0x5
	.byte	0x72
	.sleb128 -20
	.byte	0x6
	.byte	0x20
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL6-.LVL1
	.uleb128 .LFE15-.LVL1
	.uleb128 0x1
	.byte	0x5a
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
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
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
.LLRL10:
	.byte	0x5
	.4byte	.LBB5
	.byte	0x4
	.uleb128 .LBB5-.LBB5
	.uleb128 .LBE5-.LBB5
	.byte	0x4
	.uleb128 .LBB6-.LBB5
	.uleb128 .LBE6-.LBB5
	.byte	0
.LLRL14:
	.byte	0x5
	.4byte	.LBB8
	.byte	0x4
	.uleb128 .LBB8-.LBB8
	.uleb128 .LBE8-.LBB8
	.byte	0x4
	.uleb128 .LBB9-.LBB8
	.uleb128 .LBE9-.LBB8
	.byte	0
.LLRL16:
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
	.4byte	.LFB33
	.uleb128 .LFE33-.LFB33
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
	.4byte	.LFB18
	.uleb128 .LFE18-.LFB18
	.byte	0x7
	.4byte	.LFB24
	.uleb128 .LFE24-.LFB24
	.byte	0x7
	.4byte	.LFB25
	.uleb128 .LFE25-.LFB25
	.byte	0x7
	.4byte	.LFB26
	.uleb128 .LFE26-.LFB26
	.byte	0x7
	.4byte	.LFB27
	.uleb128 .LFE27-.LFB27
	.byte	0x7
	.4byte	.LFB28
	.uleb128 .LFE28-.LFB28
	.byte	0x7
	.4byte	.LFB29
	.uleb128 .LFE29-.LFB29
	.byte	0x7
	.4byte	.LFB30
	.uleb128 .LFE30-.LFB30
	.byte	0x7
	.4byte	.LFB31
	.uleb128 .LFE31-.LFB31
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF249:
	.string	"outgoing_report_ready"
.LASF240:
	.string	"T_AIR_COMBO_KEY_S"
.LASF57:
	.string	"RTC_IRQn"
.LASF118:
	.string	"HAL_EINT_UART_0_RX"
.LASF153:
	.string	"HID_CCNI_MSG_USB_PLUG_OUT"
.LASF204:
	.string	"APP_STATE_2_4G_CONNECTED_ACTIVE"
.LASF340:
	.string	"outgoing_keys"
.LASF209:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1"
.LASF210:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2"
.LASF90:
	.string	"HAL_EINT_NUMBER_20"
.LASF91:
	.string	"HAL_EINT_NUMBER_21"
.LASF92:
	.string	"HAL_EINT_NUMBER_22"
.LASF93:
	.string	"HAL_EINT_NUMBER_23"
.LASF94:
	.string	"HAL_EINT_NUMBER_24"
.LASF95:
	.string	"HAL_EINT_NUMBER_25"
.LASF61:
	.string	"MCU_DMA_IRQn"
.LASF97:
	.string	"HAL_EINT_NUMBER_27"
.LASF98:
	.string	"HAL_EINT_NUMBER_28"
.LASF99:
	.string	"HAL_EINT_NUMBER_29"
.LASF120:
	.string	"HAL_EINT_UART_2_RX"
.LASF280:
	.string	"ERROR_NOTHING_CHANGED"
.LASF25:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF317:
	.string	"hid_common_set_hid_exp_flag"
.LASF343:
	.string	"riscv_mouse_key_combo_key_check"
.LASF247:
	.string	"flags"
.LASF178:
	.string	"APP_STATE_CONNECT_PREPARING"
.LASF336:
	.string	"riscv_mouse_key_common_para_update"
.LASF283:
	.string	"read_key_timestamp"
.LASF308:
	.string	"combo_cfg"
.LASF36:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF18:
	.string	"PRINT_LEVEL_DEBUG"
.LASF121:
	.string	"HAL_EINT_USB0"
.LASF123:
	.string	"HAL_EINT_USB2"
.LASF258:
	.string	"key_remap_enable"
.LASF276:
	.string	"ERROR_INSUFFICIENT_MEMORY"
.LASF3:
	.string	"unsigned int"
.LASF251:
	.string	"hid_shared_parameters"
.LASF168:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF49:
	.string	"msg_id_handle"
.LASF100:
	.string	"HAL_EINT_NUMBER_30"
.LASF101:
	.string	"HAL_EINT_NUMBER_31"
.LASF162:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF103:
	.string	"HAL_EINT_NUMBER_33"
.LASF287:
	.string	"hid_common"
.LASF70:
	.string	"HAL_EINT_NUMBER_0"
.LASF186:
	.string	"APP_STATE_CONNECT_CANCEL_CHECK"
.LASF38:
	.string	"log_type_t"
.LASF109:
	.string	"HAL_EINT_NUMBER_39"
.LASF260:
	.string	"riscv_trigger_time"
.LASF355:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF335:
	.string	"riscv_mouse_key_get_combo_key"
.LASF313:
	.string	"combo_key_result"
.LASF139:
	.string	"enable_mask"
.LASF34:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF56:
	.string	"SPI_MST1_IRQn"
.LASF314:
	.string	"new_keys_status_record"
.LASF135:
	.string	"DBG_PIN_USB_SOF"
.LASF266:
	.string	"hid_common_info"
.LASF157:
	.string	"HID_CCNI_MSG_KEY_REMAP_TRIGGER"
.LASF165:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF146:
	.string	"HID_CCNI_MSG_FEATURE_CONFIG"
.LASF329:
	.string	"new_state"
.LASF68:
	.string	"BT_IRQn"
.LASF225:
	.string	"numeric_key_pad"
.LASF169:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF270:
	.string	"HAL_CCNI_STATUS_NO_INIT"
.LASF69:
	.string	"IRQ_NUMBER_MAX"
.LASF110:
	.string	"HAL_EINT_NUMBER_40"
.LASF111:
	.string	"HAL_EINT_NUMBER_41"
.LASF112:
	.string	"HAL_EINT_NUMBER_42"
.LASF113:
	.string	"HAL_EINT_NUMBER_43"
.LASF219:
	.string	"T_HID_KEY_REMAP_S"
.LASF115:
	.string	"HAL_EINT_NUMBER_45"
.LASF116:
	.string	"HAL_EINT_NUMBER_46"
.LASF117:
	.string	"HAL_EINT_NUMBER_47"
.LASF192:
	.string	"APP_STATE_USB_DISCONNECTING"
.LASF354:
	.string	"riscv_mouse_key_polling_all_key_status"
.LASF181:
	.string	"APP_STATE_BT_RECONNECT"
.LASF166:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF242:
	.string	"step_2_4g"
.LASF21:
	.string	"PRINT_LEVEL_ERROR"
.LASF30:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF306:
	.string	"T_COMBO_KEY_CFG_S"
.LASF271:
	.string	"HAL_CCNI_STATUS_OK"
.LASF203:
	.string	"APP_STATE_2_4G_CONNECTED"
.LASF332:
	.string	"end_gpt_free_count"
.LASF307:
	.string	"start_gpt_free_count"
.LASF17:
	.string	"uint32_t"
.LASF172:
	.string	"T_HID_REPORT_RATE_VAL_S"
.LASF341:
	.string	"riscv_mouse_key_early_handle"
.LASF235:
	.string	"kb_std5"
.LASF24:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF174:
	.string	"APP_STATE_INITIALIZED"
.LASF41:
	.string	"f_msg_id_t"
.LASF59:
	.string	"UART_DMA_IRQn"
.LASF214:
	.string	"play_mode"
.LASF230:
	.string	"para"
.LASF238:
	.string	"combo_bit_00_31"
.LASF128:
	.string	"HAL_GPT_CLOCK_SOURCE_1M"
.LASF2:
	.string	"long long unsigned int"
.LASF164:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF274:
	.string	"ERROR_INVALID_PARAMETER"
.LASF224:
	.string	"consumer"
.LASF42:
	.string	"f_tlv_dump_t"
.LASF222:
	.string	"combo"
.LASF143:
	.string	"HID_CCNI_MSG_FAKE_REPORT_ENABLE"
.LASF338:
	.string	"riscv_mouse_key_id_to_key_status"
.LASF265:
	.string	"outgoing_report"
.LASF352:
	.string	"is_pressed"
.LASF347:
	.string	"gpio_data_in_mask_temp"
.LASF31:
	.string	"LOG_TYPE_HCI_DATA"
.LASF301:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF227:
	.string	"dummy"
.LASF54:
	.string	"KEYSCAN_IRQn"
.LASF278:
	.string	"ERROR_QUEUE_FULL"
.LASF37:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF147:
	.string	"HID_CCNI_MSG_HOGP_ATTR_HANDLE"
.LASF71:
	.string	"HAL_EINT_NUMBER_1"
.LASF72:
	.string	"HAL_EINT_NUMBER_2"
.LASF73:
	.string	"HAL_EINT_NUMBER_3"
.LASF74:
	.string	"HAL_EINT_NUMBER_4"
.LASF75:
	.string	"HAL_EINT_NUMBER_5"
.LASF76:
	.string	"HAL_EINT_NUMBER_6"
.LASF77:
	.string	"HAL_EINT_NUMBER_7"
.LASF78:
	.string	"HAL_EINT_NUMBER_8"
.LASF79:
	.string	"HAL_EINT_NUMBER_9"
.LASF320:
	.string	"print_module_msgid_log"
.LASF263:
	.string	"app_shared_parameters"
.LASF137:
	.string	"DBG_PIN_USB_TX"
.LASF33:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF140:
	.string	"T_COMMON_LA_DBG_S"
.LASF346:
	.string	"combo_idx"
.LASF207:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_3"
.LASF264:
	.string	"mapped_data"
.LASF141:
	.string	"_Bool"
.LASF220:
	.string	"report_id"
.LASF282:
	.string	"hid_exp_features"
.LASF339:
	.string	"riscv_mouse_key_get_key_status"
.LASF348:
	.string	"all_gpio_status_1"
.LASF349:
	.string	"all_gpio_status_2"
.LASF126:
	.string	"HAL_EINT_NUMBER_MAX"
.LASF27:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF233:
	.string	"kb_std2"
.LASF353:
	.string	"shift_value"
.LASF160:
	.string	"HID_CCNI_MSG_POLLING_KEY_STATUS"
.LASF136:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF130:
	.string	"DBG_PIN_SPI_CB"
.LASF228:
	.string	"T_HID_REPORT_KB_STD5_S"
.LASF311:
	.string	"mouse_5key"
.LASF195:
	.string	"APP_STATE_BT_CONNECTED_IDLE_1"
.LASF196:
	.string	"APP_STATE_BT_CONNECTED_IDLE_2"
.LASF197:
	.string	"APP_STATE_BT_CONNECTED_IDLE_3"
.LASF297:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF262:
	.string	"mouse_key_num"
.LASF310:
	.string	"rv_key_ids"
.LASF28:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF26:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF273:
	.string	"SUCCESS"
.LASF12:
	.string	"char"
.LASF295:
	.string	"gpio_data_in_mask_t"
.LASF267:
	.string	"HAL_CCNI_STATUS_INVALID_PARAMETER"
.LASF315:
	.string	"riscv_app_ccin_send"
.LASF182:
	.string	"APP_STATE_2_4G_RECONNECT"
.LASF325:
	.string	"log_control_block_riscv_ps"
.LASF243:
	.string	"step_bt"
.LASF151:
	.string	"HID_CCNI_MSG_COMMON_PARA_UPDATE"
.LASF44:
	.string	"log_switch"
.LASF155:
	.string	"HID_CCNI_MSG_INACTIVITY_TIMEOUT"
.LASF51:
	.string	"SW_IRQn"
.LASF327:
	.string	"riscv_mouse_key__ccni_send_status"
.LASF269:
	.string	"HAL_CCNI_STATUS_ERROR"
.LASF39:
	.string	"f_print_t"
.LASF15:
	.string	"uint8_t"
.LASF218:
	.string	"status"
.LASF4:
	.string	"signed char"
.LASF119:
	.string	"HAL_EINT_UART_1_RX"
.LASF237:
	.string	"T_HID_CCNI_USB_REPORT_S"
.LASF158:
	.string	"HID_CCNI_MSG_FAKE_REPORT_TERMINATE"
.LASF167:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF300:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF305:
	.string	"app_state"
.LASF286:
	.string	"T_RISCV_APP_S"
.LASF245:
	.string	"hid_scenario_type"
.LASF241:
	.string	"step_wired"
.LASF345:
	.string	"combo_key_2"
.LASF10:
	.string	"long long int"
.LASF309:
	.string	"rv_key_num"
.LASF189:
	.string	"APP_STATE_USB_SUSPEND"
.LASF323:
	.string	"key_id"
.LASF232:
	.string	"ms_s16_z8"
.LASF64:
	.string	"I3C0_DMA_IRQn"
.LASF331:
	.string	"riscv_mouse_key_pairing_key_check"
.LASF40:
	.string	"f_dump_buffer_t"
.LASF191:
	.string	"APP_STATE_USB_ENTERING_ACTIVE"
.LASF290:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF183:
	.string	"APP_STATE_2_4G_QUICK_CONNECT"
.LASF239:
	.string	"combo_bit_32_63"
.LASF171:
	.string	"rr_idx_usb"
.LASF255:
	.string	"hold_timeout"
.LASF66:
	.string	"IRQ_GEN_IRQn"
.LASF55:
	.string	"UART_IRQn"
.LASF281:
	.string	"ERROR_UNKNOWN"
.LASF19:
	.string	"PRINT_LEVEL_INFO"
.LASF133:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF134:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF253:
	.string	"combo_key_list"
.LASF261:
	.string	"mouse_key_list"
.LASF277:
	.string	"ERROR_QUEUE_EMPTY"
.LASF288:
	.string	"riscv_app"
.LASF194:
	.string	"APP_STATE_BT_CONNECTED_ACTIVE"
.LASF102:
	.string	"HAL_EINT_NUMBER_32"
.LASF259:
	.string	"key_remap_fn_key"
.LASF67:
	.string	"USB_IRQn"
.LASF104:
	.string	"HAL_EINT_NUMBER_34"
.LASF268:
	.string	"HAL_CCNI_STATUS_BUSY"
.LASF105:
	.string	"HAL_EINT_NUMBER_35"
.LASF106:
	.string	"HAL_EINT_NUMBER_36"
.LASF177:
	.string	"APP_STATE_TEST"
.LASF107:
	.string	"HAL_EINT_NUMBER_37"
.LASF108:
	.string	"HAL_EINT_NUMBER_38"
.LASF358:
	.string	"riscv_mouse_key_deinit"
.LASF326:
	.string	"msg_id_string"
.LASF156:
	.string	"HID_CCNI_MSG_FORCE_ALL_KEY_RELEASED"
.LASF316:
	.string	"hal_gpt_get_duration_count"
.LASF333:
	.string	"duration_count"
.LASF248:
	.string	"features"
.LASF344:
	.string	"combo_key_1"
.LASF257:
	.string	"scroll_ctrl"
.LASF299:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF234:
	.string	"kb_consumer1"
.LASF47:
	.string	"dump_handle"
.LASF184:
	.string	"APP_STATE_2_4G_RECONNECT_RESUME_WAIT"
.LASF11:
	.string	"long double"
.LASF16:
	.string	"uint16_t"
.LASF356:
	.string	"IRQn"
.LASF144:
	.string	"HID_CCNI_MSG_FAKE_REPORT_CONFIG"
.LASF199:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_1"
.LASF200:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_2"
.LASF201:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_3"
.LASF296:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF211:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3"
.LASF48:
	.string	"tlv_dump_handle"
.LASF350:
	.string	"update_key_status"
.LASF321:
	.string	"hal_eint_get_debounce_out_value_by_mask"
.LASF122:
	.string	"HAL_EINT_USB1"
.LASF229:
	.string	"T_HID_REPORT_KB_CONSUMER2_S"
.LASF20:
	.string	"PRINT_LEVEL_WARNING"
.LASF188:
	.string	"APP_STATE_USB_ACTIVE"
.LASF322:
	.string	"found_idx"
.LASF244:
	.string	"T_DEBOUNCE_PARA_S"
.LASF6:
	.string	"short int"
.LASF145:
	.string	"HID_CCNI_MSG_KEY_REMAP_CONFIG"
.LASF324:
	.string	"new_keys_status"
.LASF292:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF303:
	.string	"HAL_GPT_STATUS_OK"
.LASF8:
	.string	"long int"
.LASF236:
	.string	"kb_consumer2"
.LASF223:
	.string	"T_HID_REPORT_KB_STD2_XY_S"
.LASF52:
	.string	"LED_IRQn"
.LASF163:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF14:
	.string	"int16_t"
.LASF62:
	.string	"EINT_IRQn"
.LASF176:
	.string	"APP_STATE_DISCONNECTED"
.LASF302:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF185:
	.string	"APP_STATE_CONNECT_CANCEL"
.LASF65:
	.string	"SPI_MST0_IRQn"
.LASF58:
	.string	"GPT_IRQn"
.LASF131:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF114:
	.string	"HAL_EINT_NUMBER_44"
.LASF32:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF198:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_ACTIVE"
.LASF319:
	.string	"hal_gpt_get_free_run_count"
.LASF161:
	.string	"HID_CCNI_MSG_POLLING_WHEEL_STATUS"
.LASF148:
	.string	"HID_CCNI_MSG_SET_DBG_PIN"
.LASF46:
	.string	"print_handle"
.LASF125:
	.string	"HAL_EINT_RESERVED"
.LASF298:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF173:
	.string	"APP_STATE_NONE"
.LASF250:
	.string	"delay_for_key_polling_ms"
.LASF150:
	.string	"HID_CCNI_MSG_SET_FEATURE"
.LASF318:
	.string	"hid_common_get_combo_key_list"
.LASF142:
	.string	"HID_CCNI_MSG_APP_STATE"
.LASF149:
	.string	"HID_CCNI_MSG_SET_OUTPUT_CTRL_PIN"
.LASF202:
	.string	"APP_STATE_BT_DISCONNECTING"
.LASF13:
	.string	"int8_t"
.LASF50:
	.string	"log_control_block_t"
.LASF334:
	.string	"riscv_mouse_key_change_state"
.LASF272:
	.string	"hal_ccni_status_t"
.LASF216:
	.string	"macro"
.LASF215:
	.string	"repeat_times"
.LASF9:
	.string	"long unsigned int"
.LASF212:
	.string	"APP_STATE_2_4G_DISCONNECTING"
.LASF152:
	.string	"HID_CCNI_MSG_WAKEUP_KEY"
.LASF35:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF304:
	.string	"hal_gpt_status_t"
.LASF351:
	.string	"key_id_index"
.LASF205:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_1"
.LASF206:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_2"
.LASF330:
	.string	"riscv_mouse_key_debug_print"
.LASF5:
	.string	"unsigned char"
.LASF208:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE"
.LASF275:
	.string	"ERROR_BUSY"
.LASF170:
	.string	"rr_idx_2_4g"
.LASF293:
	.string	"register0"
.LASF294:
	.string	"register1"
.LASF23:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF252:
	.string	"inActivity_timeout"
.LASF43:
	.string	"module_name"
.LASF179:
	.string	"APP_STATE_BT_PAIRING"
.LASF154:
	.string	"HID_CCNI_MSG_KEY"
.LASF289:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF285:
	.string	"state"
.LASF231:
	.string	"T_OUTPUT_CTRL_PIN_INFO_S"
.LASF96:
	.string	"HAL_EINT_NUMBER_26"
.LASF256:
	.string	"irpt_ctrl"
.LASF29:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF63:
	.string	"I3C0_IRQn"
.LASF279:
	.string	"ERROR_TIMEOUT"
.LASF284:
	.string	"rr_idx"
.LASF254:
	.string	"combo_key_list_size"
.LASF217:
	.string	"item"
.LASF127:
	.string	"HAL_GPT_CLOCK_SOURCE_32K"
.LASF45:
	.string	"print_level"
.LASF159:
	.string	"HID_CCNI_MSG_PRINT_HID_REPORT_REQ"
.LASF193:
	.string	"APP_STATE_BT_CONNECTED"
.LASF291:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF175:
	.string	"APP_STATE_STANDBY"
.LASF190:
	.string	"APP_STATE_USB_STOP"
.LASF7:
	.string	"short unsigned int"
.LASF337:
	.string	"riscv_mouse_key_post_process"
.LASF132:
	.string	"DBG_PIN_NACK"
.LASF226:
	.string	"T_HID_REPORT_KB_CONSUMER1_XY_S"
.LASF138:
	.string	"DBG_PIN_MAX"
.LASF60:
	.string	"PMU_IRQn"
.LASF124:
	.string	"HAL_EINT_LPCOMP"
.LASF180:
	.string	"APP_STATE_2_4G_PAIRING"
.LASF221:
	.string	"T_HID_REPORT_MS_K8_S16_Z8_S"
.LASF187:
	.string	"APP_STATE_USB_CONNECTED"
.LASF328:
	.string	"riscv_mouse_key__app_state_update"
.LASF213:
	.string	"keycode"
.LASF80:
	.string	"HAL_EINT_NUMBER_10"
.LASF81:
	.string	"HAL_EINT_NUMBER_11"
.LASF82:
	.string	"HAL_EINT_NUMBER_12"
.LASF83:
	.string	"HAL_EINT_NUMBER_13"
.LASF84:
	.string	"HAL_EINT_NUMBER_14"
.LASF85:
	.string	"HAL_EINT_NUMBER_15"
.LASF86:
	.string	"HAL_EINT_NUMBER_16"
.LASF87:
	.string	"HAL_EINT_NUMBER_17"
.LASF88:
	.string	"HAL_EINT_NUMBER_18"
.LASF89:
	.string	"HAL_EINT_NUMBER_19"
.LASF53:
	.string	"QDEC_IRQn"
.LASF129:
	.string	"hal_gpt_clock_source_t"
.LASF342:
	.string	"riscv_mouse_key_init"
.LASF357:
	.string	"riscv_mouse_keys_is_new_key_pressed"
.LASF22:
	.string	"print_level_t"
.LASF312:
	.string	"mouse_5key_printed"
.LASF246:
	.string	"dongle_scenario"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_mouse_key.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
