	.file	"riscv_mouse_key_ir_ctrl.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_mouse_key_ir_ctrl.c"
	.section	.text.riscv_mkey_ir_ctrl_delay,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl_delay
	.hidden	riscv_mkey_ir_ctrl_delay
	.type	riscv_mkey_ir_ctrl_delay, @function
riscv_mkey_ir_ctrl_delay:
.LFB6:
	.file 1 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_mouse_key_ir_ctrl.c"
	.loc 1 115 1
	.cfi_startproc
.LVL0:
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s1,8(sp)
	.cfi_offset 9, -12
	.loc 1 121 29 is_stmt 0
	li	s1,1108672512
	.loc 1 115 1
	sw	s0,12(sp)
	sw	ra,16(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 115 1
	mv	s0,a0
	.loc 1 121 29
	addi	s1,s1,512
.LVL1:
.L2:
	.loc 1 116 5 is_stmt 1
	.loc 1 117 5
	.loc 1 119 5
	.loc 1 121 9
	.loc 1 121 29 is_stmt 0
	lw	a1,24(s1)
.LVL2:
	.loc 1 122 9 is_stmt 1
	addi	a2,sp,4
	lw	a0,irpt
	sw	a1,0(sp)
	call	hal_gpt_get_duration_count
.LVL3:
	.loc 1 124 28 discriminator 1
	lw	a5,4(sp)
	lw	a1,0(sp)
	bltu	a5,s0,.L2
	.loc 1 126 5
	.loc 1 127 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
.LVL4:
	lw	s1,8(sp)
	.cfi_restore 9
	mv	a0,a1
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
.LVL5:
	jr	ra
	.cfi_endproc
.LFE6:
	.size	riscv_mkey_ir_ctrl_delay, .-riscv_mkey_ir_ctrl_delay
	.section	.text.riscv_mkey_ir_ctrl_on,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl_on
	.hidden	riscv_mkey_ir_ctrl_on
	.type	riscv_mkey_ir_ctrl_on, @function
riscv_mkey_ir_ctrl_on:
.LFB7:
	.loc 1 130 1 is_stmt 1
	.cfi_startproc
	.loc 1 131 5
	.loc 1 130 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 131 43
	lla	s0,irpt
	.loc 1 131 5
	lw	a1,8(s0)
	lw	a0,4(s0)
	.loc 1 130 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 131 5
	seqz	a1,a1
	call	hal_gpio_set_output
.LVL6:
	.loc 1 131 57 is_stmt 1 discriminator 1
	.loc 1 131 73 is_stmt 0 discriminator 1
	li	a5,1
	sb	a5,IR_LED_status_on,a4
	.loc 1 131 5 is_stmt 1 discriminator 1
	.loc 1 133 5
	.loc 1 133 75 is_stmt 0
	li	a5,1108672512
	addi	a5,a5,512
	lw	a5,24(a5)
	.loc 1 134 1
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 133 32
	sw	a5,0(s0)
	.loc 1 134 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE7:
	.size	riscv_mkey_ir_ctrl_on, .-riscv_mkey_ir_ctrl_on
	.section	.text.riscv_mkey_ir_ctrl_off,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl_off
	.hidden	riscv_mkey_ir_ctrl_off
	.type	riscv_mkey_ir_ctrl_off, @function
riscv_mkey_ir_ctrl_off:
.LFB8:
	.loc 1 137 1 is_stmt 1
	.cfi_startproc
	.loc 1 138 5
	.loc 1 138 42 is_stmt 0
	lla	a5,irpt
	.loc 1 138 5
	lw	a1,8(a5)
	lw	a0,4(a5)
	.loc 1 137 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 138 5
	call	hal_gpio_set_output
.LVL7:
	.loc 1 138 56 is_stmt 1 discriminator 1
	.loc 1 139 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 138 72 discriminator 1
	sb	zero,IR_LED_status_on,a5
	.loc 1 138 5 is_stmt 1 discriminator 1
	.loc 1 139 1 is_stmt 0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE8:
	.size	riscv_mkey_ir_ctrl_off, .-riscv_mkey_ir_ctrl_off
	.section	.text.riscv_mkey_ir_ctrl_idle_state_scan,"ax",@progbits
	.align	1
	.type	riscv_mkey_ir_ctrl_idle_state_scan, @function
riscv_mkey_ir_ctrl_idle_state_scan:
.LFB11:
	.loc 1 170 1 is_stmt 1
	.cfi_startproc
.LVL8:
	.loc 1 171 5
	.loc 1 172 5
	.loc 1 173 5
	.loc 1 170 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 173 5
	call	riscv_mkey_ir_ctrl_on
.LVL9:
	.loc 1 174 5 is_stmt 1
	lla	s0,irpt
	lw	a0,12(s0)
	call	hal_gpt_sw_stop_timer_us
.LVL10:
	.loc 1 175 5
	.loc 1 175 75 is_stmt 0
	lw	a4,riscv_app+16
	.loc 1 175 5
	li	a5,6
	lw	a0,12(s0)
	.loc 1 175 5 discriminator 2
	li	a1,125
	.loc 1 175 5
	bgtu	a4,a5,.L10
	.loc 1 175 132 discriminator 1
	sub	a5,a5,a4
	.loc 1 175 60 discriminator 1
	sll	a1,a1,a5
.L10:
	.loc 1 175 5 discriminator 4
	li	a3,0
	lla	a2,riscv_mkey_ir_ctrl_idle_state_scan
	call	hal_gpt_sw_start_timer_us
.LVL11:
	.loc 1 176 5 is_stmt 1
	.loc 1 176 21 is_stmt 0
	li	a5,1108672512
	addi	a5,a5,512
	lw	a1,24(a5)
.LVL12:
	.loc 1 177 5 is_stmt 1
	lw	a0,0(s0)
	mv	a2,sp
	call	hal_gpt_get_duration_count
.LVL13:
	.loc 1 178 5
	.loc 1 178 19 is_stmt 0
	lw	a5,0(sp)
	.loc 1 178 7
	li	a4,19
	bgtu	a5,a4,.L11
	.loc 1 180 9 is_stmt 1
	li	a0,20
	sub	a0,a0,a5
	call	hal_gpt_delay_us
.LVL14:
.L11:
	.loc 1 183 5
	.loc 1 183 27 is_stmt 0
	call	riscv_mouse_key_polling_all_key_status
.LVL15:
	.loc 1 186 5 is_stmt 1
	call	riscv_mouse_key__notify_cm33_key_status
.LVL16:
	.loc 1 187 5
	call	riscv_mkey_ir_ctrl_off
.LVL17:
	.loc 1 188 5
	.loc 1 189 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	riscv_mkey_ir_ctrl_idle_state_scan, .-riscv_mkey_ir_ctrl_idle_state_scan
	.section	.text.riscv_mkey_ir_ctrl_init,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl_init
	.hidden	riscv_mkey_ir_ctrl_init
	.type	riscv_mkey_ir_ctrl_init, @function
riscv_mkey_ir_ctrl_init:
.LFB9:
	.loc 1 142 1 is_stmt 1
	.cfi_startproc
	.loc 1 144 5
	.loc 1 142 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 144 13
	lla	s0,irpt
	.loc 1 144 8
	lw	a5,12(s0)
	.loc 1 142 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 144 8
	bne	a5,zero,.L15
	.loc 1 145 9 is_stmt 1
	lla	a0,irpt+12
	call	hal_gpt_sw_get_timer
.LVL18:
.L15:
	.loc 1 149 5
.LBB2:
	.loc 1 149 10
	.loc 1 149 65
	.loc 1 149 255
	lw	a4,4(s0)
	li	a3,1
	lla	a2,msg_id_string.1
	li	a1,1
	lla	a0,log_control_block_riscv_ps
	call	print_module_msgid_log
.LVL19:
.LBE2:
	.loc 1 149 8 discriminator 1
	.loc 1 150 5
	.loc 1 150 29 is_stmt 0
	lw	a5,hid_common
	.loc 1 150 44
	lbu	a4,20(a5)
	.loc 1 151 54
	lbu	a5,21(a5)
	.loc 1 152 1
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 150 44
	sw	a4,4(s0)
	.loc 1 151 5 is_stmt 1
	.loc 1 151 54 is_stmt 0
	andi	a5,a5,1
	sw	a5,8(s0)
	.loc 1 152 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE9:
	.size	riscv_mkey_ir_ctrl_init, .-riscv_mkey_ir_ctrl_init
	.section	.text.riscv_mkey_ir_ctrl_deinit,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl_deinit
	.hidden	riscv_mkey_ir_ctrl_deinit
	.type	riscv_mkey_ir_ctrl_deinit, @function
riscv_mkey_ir_ctrl_deinit:
.LFB10:
	.loc 1 155 1 is_stmt 1
	.cfi_startproc
	.loc 1 156 5
.LBB3:
	.loc 1 156 10
	.loc 1 156 65
	.loc 1 156 258
.LBE3:
	.loc 1 155 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
.LBB4:
	.loc 1 156 258
	lla	a0,log_control_block_riscv_ps
	li	a3,0
	lla	a2,msg_id_string.0
	li	a1,1
.LBE4:
	.loc 1 155 1
	sw	ra,8(sp)
	sw	s0,4(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
.LBB5:
	.loc 1 156 258
	call	print_module_msgid_log
.LVL20:
.LBE5:
	.loc 1 156 8 is_stmt 1 discriminator 1
	.loc 1 157 5
	.loc 1 160 13 is_stmt 0
	lla	s0,irpt
	.loc 1 157 5
	call	riscv_mkey_ir_ctrl_off
.LVL21:
	.loc 1 160 5 is_stmt 1
	.loc 1 160 13 is_stmt 0
	lw	a0,12(s0)
	.loc 1 160 8
	beq	a0,zero,.L17
	.loc 1 161 9 is_stmt 1
	call	hal_gpt_sw_stop_timer_us
.LVL22:
	.loc 1 162 9
	lw	a0,12(s0)
	call	hal_gpt_sw_free_timer
.LVL23:
	.loc 1 163 9
	.loc 1 163 32 is_stmt 0
	sw	zero,irpt+12,a5
.L17:
	.loc 1 166 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE10:
	.size	riscv_mkey_ir_ctrl_deinit, .-riscv_mkey_ir_ctrl_deinit
	.section	.text.riscv_mkey_ir_ctrl__reset_cnt,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl__reset_cnt
	.hidden	riscv_mkey_ir_ctrl__reset_cnt
	.type	riscv_mkey_ir_ctrl__reset_cnt, @function
riscv_mkey_ir_ctrl__reset_cnt:
.LFB13:
	.loc 1 198 1 is_stmt 1
	.cfi_startproc
	.loc 1 199 5
	.loc 1 199 18 is_stmt 0
	lla	a4,riscv_app
	.loc 1 199 8
	lw	a2,20(a4)
	li	a3,18
	.loc 1 200 26
	li	a5,3
	.loc 1 199 8
	beq	a2,a3,.L24
.LBB8:
.LBB9:
	.loc 1 203 9 is_stmt 1
	.loc 1 203 56 is_stmt 0
	lw	a4,16(a4)
	lla	a5,protect_cnt_non_bt_mode_tbl
	add	a5,a5,a4
	lbu	a5,0(a5)
.L24:
	sw	a5,irpt+16,a4
.LBE9:
.LBE8:
	.loc 1 205 1
	ret
	.cfi_endproc
.LFE13:
	.size	riscv_mkey_ir_ctrl__reset_cnt, .-riscv_mkey_ir_ctrl__reset_cnt
	.section	.text.riscv_mkey_ir_ctrl__ir_key_check,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl__ir_key_check
	.hidden	riscv_mkey_ir_ctrl__ir_key_check
	.type	riscv_mkey_ir_ctrl__ir_key_check, @function
riscv_mkey_ir_ctrl__ir_key_check:
.LFB14:
	.loc 1 208 1 is_stmt 1
	.cfi_startproc
.LVL24:
	.loc 1 209 5
	.loc 1 208 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 208 1
	mv	s0,a1
	mv	s1,a2
	.loc 1 209 8
	bne	a0,zero,.L27
	.loc 1 212 9 is_stmt 1
	.loc 1 212 20 is_stmt 0
	andi	s0,a1,-4
.LVL25:
	.loc 1 213 9 is_stmt 1
	.loc 1 213 39 is_stmt 0
	andi	a5,a2,3
	.loc 1 213 20
	or	s0,a5,s0
.LVL26:
.L27:
	.loc 1 216 5 is_stmt 1
	.loc 1 216 9 is_stmt 0
	call	mouse_sensor_is_lifted
.LVL27:
	lla	a5,irpt
	.loc 1 217 12
	lw	a4,16(a5)
	.loc 1 216 8 discriminator 1
	beq	a0,zero,.L28
	.loc 1 217 9 is_stmt 1
	.loc 1 217 12 is_stmt 0
	bne	a4,zero,.L29
	.loc 1 218 13 is_stmt 1
	call	riscv_mkey_ir_ctrl__reset_cnt
.LVL28:
	lla	a5,irpt
.L29:
	.loc 1 222 9
	.loc 1 222 32 is_stmt 0
	xor	a4,s0,s1
	andi	a4,a4,3
	.loc 1 222 12
	beq	a4,zero,.L30
	.loc 1 223 13 is_stmt 1
	.loc 1 223 29 is_stmt 0
	lw	a4,16(a5)
	addi	a4,a4,-1
	sw	a4,16(a5)
	.loc 1 225 13 is_stmt 1
	.loc 1 225 16 is_stmt 0
	bgt	a4,zero,.L31
.L30:
	.loc 1 235 13 is_stmt 1
	call	riscv_mkey_ir_ctrl__reset_cnt
.LVL29:
	.loc 1 236 13
.L33:
	.loc 1 249 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	mv	a0,s0
	lw	s0,4(sp)
	.cfi_restore 8
	lw	s1,0(sp)
	.cfi_restore 9
.LVL30:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL31:
.L28:
	.cfi_restore_state
	.loc 1 240 9 is_stmt 1
	.loc 1 240 12 is_stmt 0
	ble	a4,zero,.L33
	.loc 1 242 13 is_stmt 1
	.loc 1 242 29 is_stmt 0
	addi	a4,a4,-1
	sw	a4,16(a5)
	.loc 1 243 13 is_stmt 1
.L31:
	.loc 1 226 24 is_stmt 0
	mv	s0,s1
.LVL32:
	j	.L33
	.cfi_endproc
.LFE14:
	.size	riscv_mkey_ir_ctrl__ir_key_check, .-riscv_mkey_ir_ctrl__ir_key_check
	.section	.text.riscv_mkey_ir_ctrl_post_process,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl_post_process
	.hidden	riscv_mkey_ir_ctrl_post_process
	.type	riscv_mkey_ir_ctrl_post_process, @function
riscv_mkey_ir_ctrl_post_process:
.LFB15:
	.loc 1 252 1 is_stmt 1
	.cfi_startproc
.LVL33:
	.loc 1 253 1
	ret
	.cfi_endproc
.LFE15:
	.size	riscv_mkey_ir_ctrl_post_process, .-riscv_mkey_ir_ctrl_post_process
	.section	.text.riscv_mkey_ir_ctrl__app_state_update,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl__app_state_update
	.hidden	riscv_mkey_ir_ctrl__app_state_update
	.type	riscv_mkey_ir_ctrl__app_state_update, @function
riscv_mkey_ir_ctrl__app_state_update:
.LFB16:
	.loc 1 256 2
	.cfi_startproc
.LVL34:
	.loc 1 257 5
	li	a5,19
	bgtu	a0,a5,.L37
	li	a5,15
	bgtu	a0,a5,.L38
	li	a5,3
	beq	a0,a5,.L39
	li	a5,10
	beq	a0,a5,.L40
	ret
.L37:
	li	a5,75
	beq	a0,a5,.L38
	bgtu	a0,a5,.L42
	li	a5,33
	bgtu	a0,a5,.L43
	li	a5,31
	bgtu	a0,a5,.L44
	ret
.L43:
	addi	a0,a0,-64
.LVL35:
	li	a5,1
	bleu	a0,a5,.L44
	ret
.LVL36:
.L42:
	li	a5,129
	bgtu	a0,a5,.L45
	li	a5,127
	bgtu	a0,a5,.L44
	ret
.L45:
	li	a5,139
	beq	a0,a5,.L38
	ret
.L40:
	.loc 1 262 13
	tail	riscv_mkey_ir_ctrl_init
.LVL37:
.L39:
	.loc 1 269 13
	tail	riscv_mkey_ir_ctrl_deinit
.LVL38:
.L38:
	.loc 1 279 13
	li	a0,0
.LVL39:
	tail	riscv_mkey_ir_ctrl_idle_state_scan
.LVL40:
.L44:
	.loc 1 301 13
.LBB12:
.LBB13:
	.loc 1 193 5
	lw	a0,irpt+12
	tail	hal_gpt_sw_stop_timer_us
.LVL41:
.LBE13:
.LBE12:
	.cfi_endproc
.LFE16:
	.size	riscv_mkey_ir_ctrl__app_state_update, .-riscv_mkey_ir_ctrl__app_state_update
	.section	.text.riscv_mkey_ir_ctrl_debug_print,"ax",@progbits
	.align	1
	.globl	riscv_mkey_ir_ctrl_debug_print
	.hidden	riscv_mkey_ir_ctrl_debug_print
	.type	riscv_mkey_ir_ctrl_debug_print, @function
riscv_mkey_ir_ctrl_debug_print:
.LFB17:
	.loc 1 312 1
	.cfi_startproc
	.loc 1 314 1
	ret
	.cfi_endproc
.LFE17:
	.size	riscv_mkey_ir_ctrl_debug_print, .-riscv_mkey_ir_ctrl_debug_print
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 100
msg_id_string.0:
	.string	"[M:riscv_ps C:info F: L: ]: riscv_mkey_ir_ctrl_deinit , stop and free timer(irpt.turn_on_timer_hdl)"
	.align	2
	.type	msg_id_string.1, @object
	.size	msg_id_string.1, 97
msg_id_string.1:
	.string	"[M:riscv_ps C:info F: L: ]: riscv_mkey_ir_ctrl_init , get timer (irpt.turn_on_timer_hdl) id = %d"
	.hidden	protect_cnt_non_bt_mode_tbl
	.globl	protect_cnt_non_bt_mode_tbl
	.section	.srodata.protect_cnt_non_bt_mode_tbl,"a"
	.align	2
	.type	protect_cnt_non_bt_mode_tbl, @object
	.size	protect_cnt_non_bt_mode_tbl, 7
protect_cnt_non_bt_mode_tbl:
	.ascii	"\002\004\b\020 @\200"
	.hidden	irpt
	.globl	irpt
	.section	.bss.irpt,"aw",@nobits
	.align	2
	.type	irpt, @object
	.size	irpt, 20
irpt:
	.zero	20
	.hidden	IR_LED_status_on
	.globl	IR_LED_status_on
	.section	.sbss.IR_LED_status_on,"aw",@nobits
	.type	IR_LED_status_on, @object
	.size	IR_LED_status_on, 1
IR_LED_status_on:
	.zero	1
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpt.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpio.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 8 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 9 "/workdir/airoha/common/applications/hid/inc/hid_common_hid_app_states.h"
	.file 10 "/workdir/airoha/common/applications/hid/inc/hid_common_key_remap.h"
	.file 11 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 12 "/workdir/airoha/common/applications/hid/inc/hid_common.h"
	.file 13 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_peripheral_sampling.h"
	.file 14 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 15 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_mouse_key_ir_ctrl.h"
	.file 16 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 17 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_mouse_key.h"
	.file 18 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/mouse_sensor.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x136d
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x29
	.4byte	.LASF325
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL10
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0xb
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0xb
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0xb
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0xb
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0xb
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0xb
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0xb
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0xb
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0xb
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x2a
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0xb
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x2b
	.byte	0x4
	.uleb128 0xb
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xe
	.4byte	0x75
	.uleb128 0xc
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
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x1b
	.4byte	0xaa
	.uleb128 0xe
	.4byte	0xb6
	.uleb128 0xe
	.4byte	0xaa
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x4
	.4byte	.LASF18
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x1b
	.4byte	0xd1
	.uleb128 0xe
	.4byte	0xdd
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.byte	0x3d
	.byte	0xe
	.4byte	0x10d
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF23
	.byte	0x3
	.byte	0x42
	.byte	0x3
	.4byte	0xe7
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.byte	0x45
	.byte	0xe
	.4byte	0x181
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF39
	.byte	0x3
	.byte	0x57
	.byte	0x3
	.4byte	0x119
	.uleb128 0x4
	.4byte	.LASF40
	.byte	0x3
	.byte	0x59
	.byte	0x10
	.4byte	0x199
	.uleb128 0xc
	.4byte	0x19e
	.uleb128 0x15
	.4byte	0x1be
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x10d
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x12
	.byte	0
	.uleb128 0x4
	.4byte	.LASF41
	.byte	0x3
	.byte	0x5a
	.byte	0x10
	.4byte	0x1ca
	.uleb128 0xc
	.4byte	0x1cf
	.uleb128 0x15
	.4byte	0x1f9
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x10d
	.uleb128 0x3
	.4byte	0x1f9
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x12
	.byte	0
	.uleb128 0xc
	.4byte	0x1fe
	.uleb128 0x2c
	.uleb128 0x4
	.4byte	.LASF42
	.byte	0x3
	.byte	0x5b
	.byte	0x10
	.4byte	0x20b
	.uleb128 0xc
	.4byte	0x210
	.uleb128 0x15
	.4byte	0x22b
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x10d
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xd1
	.uleb128 0x12
	.byte	0
	.uleb128 0x4
	.4byte	.LASF43
	.byte	0x3
	.byte	0x5c
	.byte	0x14
	.4byte	0x237
	.uleb128 0xc
	.4byte	0x23c
	.uleb128 0x2d
	.4byte	0xd1
	.4byte	0x25f
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x10d
	.uleb128 0x3
	.4byte	0x181
	.uleb128 0x3
	.4byte	0x25f
	.uleb128 0x3
	.4byte	0x264
	.byte	0
	.uleb128 0xc
	.4byte	0x1f9
	.uleb128 0xc
	.4byte	0xd1
	.uleb128 0x5
	.byte	0x1c
	.byte	0x3
	.byte	0x5e
	.4byte	0x2cd
	.uleb128 0x2
	.4byte	.LASF44
	.byte	0x3
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x2
	.4byte	.LASF45
	.byte	0x3
	.byte	0x60
	.byte	0xe
	.4byte	0xd1
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x3
	.byte	0x61
	.byte	0xe
	.4byte	0xd1
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x3
	.byte	0x62
	.byte	0xf
	.4byte	0x18d
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF48
	.byte	0x3
	.byte	0x63
	.byte	0x15
	.4byte	0x1be
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x3
	.byte	0x64
	.byte	0x12
	.4byte	0x22b
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF50
	.byte	0x3
	.byte	0x65
	.byte	0x10
	.4byte	0x1ff
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF51
	.byte	0x3
	.byte	0x66
	.byte	0x3
	.4byte	0x269
	.uleb128 0x8
	.4byte	0xbb
	.4byte	0x2e9
	.uleb128 0x9
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0xe
	.4byte	0x2d9
	.uleb128 0x1b
	.4byte	0x2e9
	.uleb128 0x5
	.byte	0x4
	.byte	0x4
	.byte	0x36
	.4byte	0x32f
	.uleb128 0x6
	.string	"EN"
	.byte	0x4
	.byte	0x37
	.byte	0x1e
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF52
	.byte	0x4
	.byte	0x38
	.byte	0x1e
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF53
	.byte	0x4
	.byte	0x39
	.byte	0x1e
	.4byte	0xb6
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF54
	.byte	0x4
	.byte	0x3a
	.byte	0x24
	.4byte	0x2ee
	.byte	0x3
	.byte	0
	.uleb128 0x1e
	.byte	0x4
	.byte	0x4
	.byte	0x35
	.4byte	0x350
	.uleb128 0x10
	.4byte	.LASF55
	.byte	0x4
	.byte	0x3b
	.byte	0xb
	.4byte	0x2f3
	.uleb128 0x10
	.4byte	.LASF56
	.byte	0x4
	.byte	0x3c
	.byte	0x1b
	.4byte	0xdd
	.byte	0
	.uleb128 0x5
	.byte	0x20
	.byte	0x4
	.byte	0x34
	.4byte	0x3c1
	.uleb128 0x2
	.4byte	.LASF57
	.byte	0x4
	.byte	0x3d
	.byte	0x7
	.4byte	0x32f
	.byte	0
	.uleb128 0x2
	.4byte	.LASF58
	.byte	0x4
	.byte	0x3e
	.byte	0x17
	.4byte	0xdd
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF59
	.byte	0x4
	.byte	0x3f
	.byte	0x17
	.4byte	0xdd
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF60
	.byte	0x4
	.byte	0x40
	.byte	0x17
	.4byte	0xdd
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF61
	.byte	0x4
	.byte	0x41
	.byte	0x1d
	.4byte	0xe2
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF62
	.byte	0x4
	.byte	0x42
	.byte	0x17
	.4byte	0xdd
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF63
	.byte	0x4
	.byte	0x43
	.byte	0x17
	.4byte	0xdd
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF64
	.byte	0x4
	.byte	0x44
	.byte	0x17
	.4byte	0xdd
	.byte	0x1c
	.byte	0
	.uleb128 0x4
	.4byte	.LASF65
	.byte	0x4
	.byte	0x45
	.byte	0x3
	.4byte	0x350
	.uleb128 0x8
	.4byte	0xaa
	.4byte	0x3dd
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x1f
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.2byte	0x1cd
	.4byte	0x511
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x30
	.byte	0
	.uleb128 0x16
	.4byte	.LASF115
	.byte	0x5
	.2byte	0x1ff
	.byte	0x3
	.4byte	0x3dd
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0xda
	.byte	0xe
	.4byte	0x538
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF118
	.byte	0x6
	.byte	0xdd
	.byte	0x3
	.4byte	0x51e
	.uleb128 0xf
	.byte	0x5
	.4byte	0x65
	.byte	0x6
	.byte	0xe1
	.byte	0xe
	.4byte	0x56a
	.uleb128 0xd
	.4byte	.LASF119
	.sleb128 -3
	.uleb128 0xd
	.4byte	.LASF120
	.sleb128 -2
	.uleb128 0xd
	.4byte	.LASF121
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF123
	.byte	0x6
	.byte	0xe6
	.byte	0x3
	.4byte	0x544
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x7
	.byte	0x50
	.byte	0xe
	.4byte	0x5ba
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.byte	0xa
	.byte	0x7
	.byte	0x5e
	.4byte	0x5dd
	.uleb128 0x2
	.4byte	.LASF133
	.byte	0x7
	.byte	0x60
	.byte	0xe
	.4byte	0xc5
	.byte	0
	.uleb128 0x6
	.string	"pin"
	.byte	0x7
	.byte	0x61
	.byte	0xd
	.4byte	0x5dd
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0xaa
	.4byte	0x5ed
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF134
	.byte	0x7
	.byte	0x62
	.byte	0x2
	.4byte	0x5ba
	.uleb128 0xb
	.byte	0x1
	.byte	0x2
	.4byte	.LASF135
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x31
	.byte	0x1
	.4byte	0x63e
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.byte	0x2
	.byte	0x8
	.byte	0x3f
	.4byte	0x661
	.uleb128 0x2
	.4byte	.LASF144
	.byte	0x8
	.byte	0x41
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF145
	.byte	0x8
	.byte	0x42
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF146
	.byte	0x8
	.byte	0x44
	.byte	0x2
	.4byte	0x63e
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x9
	.byte	0x32
	.byte	0x1
	.4byte	0x76b
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF157
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF159
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF162
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF163
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF164
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF165
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF166
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF167
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF168
	.byte	0x41
	.uleb128 0x1
	.4byte	.LASF169
	.byte	0x42
	.uleb128 0x1
	.4byte	.LASF170
	.byte	0x43
	.uleb128 0x1
	.4byte	.LASF171
	.byte	0x44
	.uleb128 0x1
	.4byte	.LASF172
	.byte	0x4a
	.uleb128 0x1
	.4byte	.LASF173
	.byte	0x4b
	.uleb128 0x1
	.4byte	.LASF174
	.byte	0x4c
	.uleb128 0x1
	.4byte	.LASF175
	.byte	0x4d
	.uleb128 0x1
	.4byte	.LASF176
	.byte	0x4e
	.uleb128 0x1
	.4byte	.LASF177
	.byte	0x80
	.uleb128 0x1
	.4byte	.LASF178
	.byte	0x81
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0x82
	.uleb128 0x1
	.4byte	.LASF180
	.byte	0x83
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0x84
	.uleb128 0x1
	.4byte	.LASF182
	.byte	0x8a
	.uleb128 0x1
	.4byte	.LASF183
	.byte	0x8b
	.uleb128 0x1
	.4byte	.LASF184
	.byte	0x8c
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0x8d
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0x8e
	.byte	0
	.uleb128 0x20
	.2byte	0x11c
	.2byte	0x109
	.byte	0xd
	.4byte	0x78f
	.uleb128 0x21
	.4byte	.LASF187
	.2byte	0x10a
	.byte	0x1a
	.4byte	0x78f
	.uleb128 0x2e
	.string	"x_y"
	.byte	0xa
	.2byte	0x10c
	.byte	0x1a
	.4byte	0x78f
	.byte	0
	.uleb128 0x8
	.4byte	0xd1
	.4byte	0x79f
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x46
	.byte	0
	.uleb128 0x22
	.2byte	0x23c
	.2byte	0x105
	.4byte	0x7d7
	.uleb128 0x17
	.4byte	.LASF188
	.2byte	0x106
	.byte	0x16
	.4byte	0xc5
	.byte	0
	.uleb128 0x17
	.4byte	.LASF189
	.2byte	0x107
	.byte	0x16
	.4byte	0xc5
	.byte	0x2
	.uleb128 0x17
	.4byte	.LASF190
	.2byte	0x108
	.byte	0x16
	.4byte	0x78f
	.byte	0x4
	.uleb128 0x2f
	.4byte	0x76b
	.2byte	0x120
	.byte	0
	.uleb128 0x20
	.2byte	0x23c
	.2byte	0x103
	.byte	0x5
	.4byte	0x7f3
	.uleb128 0x21
	.4byte	.LASF191
	.2byte	0x104
	.byte	0x12
	.4byte	0xd1
	.uleb128 0x30
	.4byte	0x79f
	.byte	0
	.uleb128 0x22
	.2byte	0x240
	.2byte	0x101
	.4byte	0x810
	.uleb128 0x17
	.4byte	.LASF192
	.2byte	0x102
	.byte	0xe
	.4byte	0xd1
	.byte	0
	.uleb128 0x23
	.4byte	0x7d7
	.byte	0x4
	.byte	0
	.uleb128 0x16
	.4byte	.LASF193
	.byte	0xa
	.2byte	0x111
	.byte	0x1e
	.4byte	0x7f3
	.uleb128 0x5
	.byte	0x8
	.byte	0xb
	.byte	0x50
	.4byte	0x86c
	.uleb128 0x2
	.4byte	.LASF194
	.byte	0xb
	.byte	0x51
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x6
	.string	"k"
	.byte	0xb
	.byte	0x52
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x6
	.string	"x"
	.byte	0xb
	.byte	0x53
	.byte	0xd
	.4byte	0x92
	.byte	0x2
	.uleb128 0x6
	.string	"y"
	.byte	0xb
	.byte	0x54
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x6
	.string	"z1"
	.byte	0xb
	.byte	0x55
	.byte	0xc
	.4byte	0x86
	.byte	0x6
	.uleb128 0x6
	.string	"z2"
	.byte	0xb
	.byte	0x56
	.byte	0xc
	.4byte	0x86
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF195
	.byte	0xb
	.byte	0x57
	.byte	0x1f
	.4byte	0x81d
	.uleb128 0x5
	.byte	0x8
	.byte	0xb
	.byte	0x88
	.4byte	0x8be
	.uleb128 0x2
	.4byte	.LASF194
	.byte	0xb
	.byte	0x89
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF196
	.byte	0xb
	.byte	0x8a
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF187
	.byte	0xb
	.byte	0x8b
	.byte	0xd
	.4byte	0x3cd
	.byte	0x2
	.uleb128 0x6
	.string	"x"
	.byte	0xb
	.byte	0x8c
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x6
	.string	"y"
	.byte	0xb
	.byte	0x8d
	.byte	0xd
	.4byte	0x92
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF197
	.byte	0xb
	.byte	0x8e
	.byte	0x1e
	.4byte	0x878
	.uleb128 0x5
	.byte	0x8
	.byte	0xb
	.byte	0x90
	.4byte	0x910
	.uleb128 0x2
	.4byte	.LASF194
	.byte	0xb
	.byte	0x91
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF198
	.byte	0xb
	.byte	0x92
	.byte	0xe
	.4byte	0xc5
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF199
	.byte	0xb
	.byte	0x93
	.byte	0xd
	.4byte	0xaa
	.byte	0x3
	.uleb128 0x6
	.string	"x"
	.byte	0xb
	.byte	0x94
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x6
	.string	"y"
	.byte	0xb
	.byte	0x95
	.byte	0xd
	.4byte	0x92
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF200
	.byte	0xb
	.byte	0x96
	.byte	0x1f
	.4byte	0x8ca
	.uleb128 0x8
	.4byte	0xaa
	.4byte	0x92c
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.byte	0xb
	.byte	0xa2
	.4byte	0x969
	.uleb128 0x2
	.4byte	.LASF194
	.byte	0xb
	.byte	0xa3
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF196
	.byte	0xb
	.byte	0xa4
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF187
	.byte	0xb
	.byte	0xa5
	.byte	0xd
	.4byte	0x91c
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF201
	.byte	0xb
	.byte	0xa6
	.byte	0xd
	.4byte	0xaa
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF202
	.byte	0xb
	.byte	0xa7
	.byte	0x1e
	.4byte	0x92c
	.uleb128 0x5
	.byte	0x8
	.byte	0xb
	.byte	0xa9
	.4byte	0x9b2
	.uleb128 0x2
	.4byte	.LASF194
	.byte	0xb
	.byte	0xaa
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF198
	.byte	0xb
	.byte	0xab
	.byte	0xd
	.4byte	0x9b2
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF199
	.byte	0xb
	.byte	0xac
	.byte	0xd
	.4byte	0xaa
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF201
	.byte	0xb
	.byte	0xad
	.byte	0xd
	.4byte	0x3cd
	.byte	0x6
	.byte	0
	.uleb128 0x8
	.4byte	0xaa
	.4byte	0x9c2
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF203
	.byte	0xb
	.byte	0xae
	.byte	0x1f
	.4byte	0x975
	.uleb128 0x8
	.4byte	0xaa
	.4byte	0x9de
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x5
	.byte	0x2
	.byte	0xc
	.byte	0x49
	.4byte	0xa00
	.uleb128 0x6
	.string	"id"
	.byte	0xc
	.byte	0x4b
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF204
	.byte	0xc
	.byte	0x4c
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF205
	.byte	0xc
	.byte	0x4d
	.byte	0x2
	.4byte	0x9de
	.uleb128 0x1e
	.byte	0x8
	.byte	0xc
	.byte	0x53
	.4byte	0xa51
	.uleb128 0x10
	.4byte	.LASF206
	.byte	0xc
	.byte	0x54
	.byte	0x25
	.4byte	0x86c
	.uleb128 0x10
	.4byte	.LASF207
	.byte	0xc
	.byte	0x56
	.byte	0x23
	.4byte	0x8be
	.uleb128 0x10
	.4byte	.LASF208
	.byte	0xc
	.byte	0x57
	.byte	0x28
	.4byte	0x910
	.uleb128 0x10
	.4byte	.LASF209
	.byte	0xc
	.byte	0x59
	.byte	0x20
	.4byte	0x969
	.uleb128 0x10
	.4byte	.LASF210
	.byte	0xc
	.byte	0x5a
	.byte	0x25
	.4byte	0x9c2
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.byte	0xc
	.byte	0x4f
	.4byte	0xa60
	.uleb128 0x23
	.4byte	0xa0c
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF211
	.byte	0xc
	.byte	0x5f
	.byte	0xa
	.4byte	0xa51
	.uleb128 0x5
	.byte	0x8
	.byte	0xc
	.byte	0x61
	.4byte	0xa8f
	.uleb128 0x2
	.4byte	.LASF212
	.byte	0xc
	.byte	0x62
	.byte	0xe
	.4byte	0xd1
	.byte	0
	.uleb128 0x2
	.4byte	.LASF213
	.byte	0xc
	.byte	0x63
	.byte	0xe
	.4byte	0xd1
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF214
	.byte	0xc
	.byte	0x67
	.byte	0x2
	.4byte	0xa6c
	.uleb128 0xe
	.4byte	0xa8f
	.uleb128 0x5
	.byte	0x3
	.byte	0xc
	.byte	0x69
	.4byte	0xad0
	.uleb128 0x2
	.4byte	.LASF215
	.byte	0xc
	.byte	0x6a
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF216
	.byte	0xc
	.byte	0x6b
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF217
	.byte	0xc
	.byte	0x6c
	.byte	0xd
	.4byte	0xaa
	.byte	0x2
	.byte	0
	.uleb128 0x4
	.4byte	.LASF218
	.byte	0xc
	.byte	0x6d
	.byte	0x3
	.4byte	0xaa0
	.uleb128 0x5
	.byte	0x18
	.byte	0xc
	.byte	0x7e
	.4byte	0xb33
	.uleb128 0x2
	.4byte	.LASF219
	.byte	0xc
	.byte	0x7f
	.byte	0xe
	.4byte	0xd1
	.byte	0
	.uleb128 0x2
	.4byte	.LASF220
	.byte	0xc
	.byte	0x80
	.byte	0xe
	.4byte	0xd1
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF221
	.byte	0xc
	.byte	0x81
	.byte	0xe
	.4byte	0xd1
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF222
	.byte	0xc
	.byte	0x82
	.byte	0xe
	.4byte	0xd1
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF223
	.byte	0xc
	.byte	0x83
	.byte	0x17
	.4byte	0xdd
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF224
	.byte	0xc
	.byte	0x84
	.byte	0xd
	.4byte	0xaa
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF225
	.byte	0xc
	.byte	0x94
	.byte	0x3
	.4byte	0xadc
	.uleb128 0x5
	.byte	0x40
	.byte	0xc
	.byte	0x96
	.4byte	0xbfd
	.uleb128 0x2
	.4byte	.LASF222
	.byte	0xc
	.byte	0x97
	.byte	0xe
	.4byte	0xd1
	.byte	0
	.uleb128 0x2
	.4byte	.LASF226
	.byte	0xc
	.byte	0x98
	.byte	0xe
	.4byte	0xd1
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF227
	.byte	0xc
	.byte	0x9b
	.byte	0x1e
	.4byte	0xbfd
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF228
	.byte	0xc
	.byte	0x9c
	.byte	0xe
	.4byte	0xd1
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF229
	.byte	0xc
	.byte	0x9d
	.byte	0xe
	.4byte	0xd1
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF230
	.byte	0xc
	.byte	0x9f
	.byte	0x1e
	.4byte	0xa00
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF231
	.byte	0xc
	.byte	0xa0
	.byte	0x1e
	.4byte	0xa00
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF232
	.byte	0xc
	.byte	0xa5
	.byte	0xe
	.4byte	0xd1
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF233
	.byte	0xc
	.byte	0xa6
	.byte	0xe
	.4byte	0xd1
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF234
	.byte	0xc
	.byte	0xae
	.byte	0xe
	.4byte	0xc02
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF235
	.byte	0xc
	.byte	0xb1
	.byte	0xd
	.4byte	0x9ce
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF236
	.byte	0xc
	.byte	0xb2
	.byte	0xd
	.4byte	0xaa
	.byte	0x38
	.uleb128 0x6
	.string	"rr"
	.byte	0xc
	.byte	0xbb
	.byte	0x1d
	.4byte	0x661
	.byte	0x39
	.uleb128 0x6
	.string	"deb"
	.byte	0xc
	.byte	0xbd
	.byte	0x17
	.4byte	0xad0
	.byte	0x3b
	.byte	0
	.uleb128 0xc
	.4byte	0xa9b
	.uleb128 0x8
	.4byte	0xc5
	.4byte	0xc12
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF237
	.byte	0xc
	.byte	0xbf
	.byte	0x3
	.4byte	0xb3f
	.uleb128 0x31
	.2byte	0x16ec
	.byte	0xc
	.byte	0xc1
	.byte	0x9
	.4byte	0xc6b
	.uleb128 0x6
	.string	"app"
	.byte	0xc
	.byte	0xc3
	.byte	0x1b
	.4byte	0xc12
	.byte	0
	.uleb128 0x6
	.string	"hid"
	.byte	0xc
	.byte	0xc4
	.byte	0x1b
	.4byte	0xb33
	.byte	0x40
	.uleb128 0x6
	.string	"dbg"
	.byte	0xc
	.byte	0xc5
	.byte	0x17
	.4byte	0x5ed
	.byte	0x58
	.uleb128 0x2
	.4byte	.LASF238
	.byte	0xc
	.byte	0xc7
	.byte	0x17
	.4byte	0xc6b
	.byte	0x62
	.uleb128 0x32
	.4byte	.LASF239
	.byte	0xc
	.byte	0xca
	.byte	0x1d
	.4byte	0xc7b
	.2byte	0x16e2
	.byte	0
	.uleb128 0x8
	.4byte	0x810
	.4byte	0xc7b
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x8
	.4byte	0xa60
	.4byte	0xc8b
	.uleb128 0x9
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF240
	.byte	0xc
	.byte	0xcc
	.byte	0x3
	.4byte	0xc1e
	.uleb128 0x14
	.4byte	.LASF246
	.byte	0xc
	.byte	0xd2
	.byte	0x19
	.4byte	0xca3
	.uleb128 0xc
	.4byte	0xc8b
	.uleb128 0xc
	.4byte	0xcad
	.uleb128 0x15
	.4byte	0xcb8
	.uleb128 0x3
	.4byte	0x73
	.byte	0
	.uleb128 0x5
	.byte	0x18
	.byte	0xd
	.byte	0x56
	.4byte	0xd0f
	.uleb128 0x2
	.4byte	.LASF241
	.byte	0xd
	.byte	0x57
	.byte	0xe
	.4byte	0xd1
	.byte	0
	.uleb128 0x2
	.4byte	.LASF242
	.byte	0xd
	.byte	0x58
	.byte	0xe
	.4byte	0xd1
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF145
	.byte	0xd
	.byte	0x59
	.byte	0xe
	.4byte	0xd1
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF144
	.byte	0xd
	.byte	0x5a
	.byte	0xe
	.4byte	0xd1
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF243
	.byte	0xd
	.byte	0x5b
	.byte	0xe
	.4byte	0xd1
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF244
	.byte	0xd
	.byte	0x5c
	.byte	0xe
	.4byte	0xd1
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF245
	.byte	0xd
	.byte	0x5f
	.byte	0x2
	.4byte	0xcb8
	.uleb128 0x14
	.4byte	.LASF247
	.byte	0xd
	.byte	0x63
	.byte	0x16
	.4byte	0xd0f
	.uleb128 0x16
	.4byte	.LASF248
	.byte	0xe
	.2byte	0x143
	.byte	0x10
	.4byte	0xca8
	.uleb128 0x1f
	.byte	0x5
	.4byte	0x65
	.byte	0xe
	.2byte	0x153
	.4byte	0xd72
	.uleb128 0xd
	.4byte	.LASF249
	.sleb128 -7
	.uleb128 0xd
	.4byte	.LASF250
	.sleb128 -6
	.uleb128 0xd
	.4byte	.LASF251
	.sleb128 -5
	.uleb128 0xd
	.4byte	.LASF252
	.sleb128 -4
	.uleb128 0xd
	.4byte	.LASF253
	.sleb128 -3
	.uleb128 0xd
	.4byte	.LASF254
	.sleb128 -2
	.uleb128 0xd
	.4byte	.LASF255
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF256
	.byte	0
	.byte	0
	.uleb128 0x16
	.4byte	.LASF257
	.byte	0xe
	.2byte	0x15c
	.byte	0x3
	.4byte	0xd34
	.uleb128 0x14
	.4byte	.LASF258
	.byte	0xf
	.byte	0x32
	.byte	0xc
	.4byte	0x5f9
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x10
	.byte	0x2a
	.byte	0xe
	.4byte	0xe35
	.uleb128 0x1
	.4byte	.LASF259
	.byte	0
	.uleb128 0x1
	.4byte	.LASF260
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF261
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF262
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF263
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF264
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF265
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF266
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF267
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF268
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF269
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF270
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF271
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF272
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF273
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF274
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF275
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF276
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF277
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF278
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF279
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF280
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF281
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF282
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF283
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF284
	.byte	0xff
	.byte	0
	.uleb128 0x33
	.4byte	0xd7f
	.byte	0x1
	.byte	0x42
	.byte	0x5
	.uleb128 0x5
	.byte	0x3
	.4byte	IR_LED_status_on
	.uleb128 0x5
	.byte	0x14
	.byte	0x1
	.byte	0x51
	.4byte	0xe8d
	.uleb128 0x2
	.4byte	.LASF285
	.byte	0x1
	.byte	0x53
	.byte	0xe
	.4byte	0xd1
	.byte	0
	.uleb128 0x2
	.4byte	.LASF286
	.byte	0x1
	.byte	0x54
	.byte	0xe
	.4byte	0xd1
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF287
	.byte	0x1
	.byte	0x55
	.byte	0xe
	.4byte	0xd1
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF288
	.byte	0x1
	.byte	0x56
	.byte	0xe
	.4byte	0xd1
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF289
	.byte	0x1
	.byte	0x57
	.byte	0xd
	.4byte	0x9e
	.byte	0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF290
	.byte	0x1
	.byte	0x58
	.byte	0x2
	.4byte	0xe43
	.uleb128 0x24
	.4byte	.LASF291
	.byte	0x5a
	.4byte	0xe8d
	.uleb128 0x5
	.byte	0x3
	.4byte	irpt
	.uleb128 0x8
	.4byte	0xc0
	.4byte	0xeb9
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0xe
	.4byte	0xea9
	.uleb128 0x24
	.4byte	.LASF292
	.byte	0x60
	.4byte	0xeb9
	.uleb128 0x5
	.byte	0x3
	.4byte	protect_cnt_non_bt_mode_tbl
	.uleb128 0x34
	.4byte	.LASF293
	.byte	0x11
	.byte	0x44
	.byte	0x6
	.4byte	0xee0
	.uleb128 0x3
	.4byte	0xd1
	.byte	0
	.uleb128 0x25
	.4byte	.LASF294
	.byte	0x11
	.byte	0x3a
	.byte	0xa
	.4byte	0xd1
	.4byte	0xef2
	.uleb128 0x12
	.byte	0
	.uleb128 0x11
	.4byte	.LASF295
	.byte	0xe
	.2byte	0x18d
	.byte	0x12
	.4byte	0xd72
	.4byte	0xf09
	.uleb128 0x3
	.4byte	0xd1
	.byte	0
	.uleb128 0x11
	.4byte	.LASF296
	.byte	0xe
	.2byte	0x1e5
	.byte	0x12
	.4byte	0xd72
	.4byte	0xf2f
	.uleb128 0x3
	.4byte	0xd1
	.uleb128 0x3
	.4byte	0xd1
	.uleb128 0x3
	.4byte	0xd27
	.uleb128 0x3
	.4byte	0x73
	.byte	0
	.uleb128 0x25
	.4byte	.LASF297
	.byte	0x12
	.byte	0x32
	.byte	0x5
	.4byte	0x65
	.4byte	0xf41
	.uleb128 0x12
	.byte	0
	.uleb128 0x11
	.4byte	.LASF298
	.byte	0xe
	.2byte	0x1ab
	.byte	0x12
	.4byte	0xd72
	.4byte	0xf58
	.uleb128 0x3
	.4byte	0xd1
	.byte	0
	.uleb128 0x11
	.4byte	.LASF299
	.byte	0xe
	.2byte	0x1ed
	.byte	0x12
	.4byte	0xd72
	.4byte	0xf6f
	.uleb128 0x3
	.4byte	0xd1
	.byte	0
	.uleb128 0x35
	.4byte	.LASF300
	.byte	0x3
	.2byte	0x129
	.byte	0xd
	.4byte	0xf92
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x10d
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xd1
	.uleb128 0x12
	.byte	0
	.uleb128 0x11
	.4byte	.LASF301
	.byte	0xe
	.2byte	0x1a2
	.byte	0x12
	.4byte	0xd72
	.4byte	0xfa9
	.uleb128 0x3
	.4byte	0x264
	.byte	0
	.uleb128 0x11
	.4byte	.LASF302
	.byte	0x6
	.2byte	0x13c
	.byte	0x13
	.4byte	0x56a
	.4byte	0xfc5
	.uleb128 0x3
	.4byte	0x511
	.uleb128 0x3
	.4byte	0x538
	.byte	0
	.uleb128 0x11
	.4byte	.LASF303
	.byte	0xe
	.2byte	0x199
	.byte	0x12
	.4byte	0xd72
	.4byte	0xfe6
	.uleb128 0x3
	.4byte	0xd1
	.uleb128 0x3
	.4byte	0xd1
	.uleb128 0x3
	.4byte	0x264
	.byte	0
	.uleb128 0x36
	.4byte	.LASF326
	.byte	0x1
	.2byte	0x137
	.byte	0x6
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x26
	.4byte	.LASF304
	.byte	0xff
	.byte	0x7
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x105e
	.uleb128 0x13
	.4byte	.LASF306
	.byte	0xff
	.byte	0x35
	.4byte	0xd1
	.4byte	.LLST9
	.uleb128 0x37
	.4byte	0x10ec
	.4byte	.LBB12
	.4byte	.LBE12-.LBB12
	.byte	0x1
	.2byte	0x12d
	.byte	0xd
	.4byte	0x103c
	.uleb128 0x1c
	.4byte	.LVL41
	.4byte	0xf58
	.byte	0
	.uleb128 0x1c
	.4byte	.LVL37
	.4byte	0x1234
	.uleb128 0x1c
	.4byte	.LVL38
	.4byte	0x11ab
	.uleb128 0x38
	.4byte	.LVL40
	.4byte	0x10f5
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	.LASF305
	.byte	0xfb
	.byte	0x6
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1082
	.uleb128 0x39
	.4byte	.LASF307
	.byte	0x1
	.byte	0xfb
	.byte	0x2f
	.4byte	0xd1
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x27
	.4byte	.LASF320
	.byte	0xcf
	.4byte	0xd1
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10e3
	.uleb128 0x13
	.4byte	.LASF308
	.byte	0xcf
	.byte	0x34
	.4byte	0xd1
	.4byte	.LLST6
	.uleb128 0x13
	.4byte	.LASF309
	.byte	0xcf
	.byte	0x48
	.4byte	0xd1
	.4byte	.LLST7
	.uleb128 0x13
	.4byte	.LASF310
	.byte	0xcf
	.byte	0x5d
	.4byte	0xd1
	.4byte	.LLST8
	.uleb128 0x7
	.4byte	.LVL27
	.4byte	0xf2f
	.uleb128 0x7
	.4byte	.LVL28
	.4byte	0x10e3
	.uleb128 0x7
	.4byte	.LVL29
	.4byte	0x10e3
	.byte	0
	.uleb128 0x3a
	.4byte	.LASF327
	.byte	0x1
	.byte	0xc5
	.byte	0x6
	.byte	0x1
	.uleb128 0x3b
	.4byte	.LASF328
	.byte	0x1
	.byte	0xbf
	.byte	0xd
	.byte	0x1
	.uleb128 0x3c
	.4byte	.LASF329
	.byte	0x1
	.byte	0xa9
	.byte	0xd
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x11ab
	.uleb128 0x13
	.4byte	.LASF311
	.byte	0xa9
	.byte	0x36
	.4byte	0x73
	.4byte	.LLST2
	.uleb128 0x1d
	.4byte	.LASF312
	.byte	0xab
	.4byte	0xd1
	.4byte	.LLST3
	.uleb128 0x18
	.4byte	.LASF313
	.byte	0xab
	.byte	0x1e
	.4byte	0xd1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1d
	.4byte	.LASF309
	.byte	0xb7
	.4byte	0xd1
	.4byte	.LLST4
	.uleb128 0x7
	.4byte	.LVL9
	.4byte	0x12d7
	.uleb128 0x7
	.4byte	.LVL10
	.4byte	0xf58
	.uleb128 0x28
	.4byte	.LVL11
	.4byte	0xf09
	.4byte	0x1172
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	riscv_mkey_ir_ctrl_idle_state_scan
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x28
	.4byte	.LVL13
	.4byte	0xfc5
	.4byte	0x1186
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL14
	.4byte	0xef2
	.uleb128 0x7
	.4byte	.LVL15
	.4byte	0xee0
	.uleb128 0x7
	.4byte	.LVL16
	.4byte	0xece
	.uleb128 0x7
	.4byte	.LVL17
	.4byte	0x12b9
	.byte	0
	.uleb128 0x19
	.4byte	.LASF316
	.byte	0x9a
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x121f
	.uleb128 0x3d
	.4byte	.LLRL5
	.4byte	0x1203
	.uleb128 0x14
	.4byte	.LASF314
	.byte	0x1
	.byte	0x9c
	.byte	0x25
	.4byte	0x2cd
	.uleb128 0x18
	.4byte	.LASF315
	.byte	0x9c
	.byte	0x80
	.4byte	0x122f
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x1a
	.4byte	.LVL20
	.4byte	0xf6f
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL21
	.4byte	0x12b9
	.uleb128 0x7
	.4byte	.LVL22
	.4byte	0xf58
	.uleb128 0x7
	.4byte	.LVL23
	.4byte	0xf41
	.byte	0
	.uleb128 0x8
	.4byte	0x7c
	.4byte	0x122f
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x63
	.byte	0
	.uleb128 0xe
	.4byte	0x121f
	.uleb128 0x19
	.4byte	.LASF317
	.byte	0x8d
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x12a4
	.uleb128 0x3e
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.4byte	0x1290
	.uleb128 0x14
	.4byte	.LASF314
	.byte	0x1
	.byte	0x95
	.byte	0x25
	.4byte	0x2cd
	.uleb128 0x18
	.4byte	.LASF315
	.byte	0x95
	.byte	0x80
	.4byte	0x12b4
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x1a
	.4byte	.LVL19
	.4byte	0xf6f
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x1a
	.4byte	.LVL18
	.4byte	0xf92
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	irpt+12
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x7c
	.4byte	0x12b4
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x60
	.byte	0
	.uleb128 0xe
	.4byte	0x12a4
	.uleb128 0x19
	.4byte	.LASF318
	.byte	0x88
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x12d7
	.uleb128 0x7
	.4byte	.LVL7
	.4byte	0xfa9
	.byte	0
	.uleb128 0x19
	.4byte	.LASF319
	.byte	0x81
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x12f5
	.uleb128 0x7
	.4byte	.LVL6
	.4byte	0xfa9
	.byte	0
	.uleb128 0x27
	.4byte	.LASF321
	.byte	0x72
	.4byte	0xd1
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1350
	.uleb128 0x13
	.4byte	.LASF322
	.byte	0x72
	.byte	0x2c
	.4byte	0xd1
	.4byte	.LLST0
	.uleb128 0x18
	.4byte	.LASF323
	.byte	0x74
	.byte	0xe
	.4byte	0xd1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1d
	.4byte	.LASF324
	.byte	0x75
	.4byte	0xd1
	.4byte	.LLST1
	.uleb128 0x1a
	.4byte	.LVL3
	.4byte	0xfc5
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.uleb128 0x3f
	.4byte	0x10e3
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x40
	.4byte	0x10e3
	.4byte	.LBB8
	.4byte	.LBE8-.LBB8
	.byte	0x1
	.byte	0xc5
	.byte	0x6
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
	.uleb128 0x6
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
	.uleb128 0x7
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x5
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
	.uleb128 0x12
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x17
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 10
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
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
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
	.uleb128 0x20
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 10
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
	.sleb128 10
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
	.sleb128 10
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
	.sleb128 15
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
	.uleb128 0x27
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
	.sleb128 10
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
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x2a
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
	.uleb128 0x2b
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2d
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
	.uleb128 0x2e
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
	.uleb128 0x2f
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
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
	.uleb128 0x32
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
	.uleb128 0x33
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
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
	.uleb128 0x37
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
	.uleb128 0x5
	.uleb128 0x57
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x38
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
	.uleb128 0x39
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3a
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
	.uleb128 0x3b
	.uleb128 0x2e
	.byte	0
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
	.uleb128 0x3c
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x3d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3e
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
	.uleb128 0x3f
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
	.uleb128 0x40
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
	.byte	0
	.section	.debug_loclists,"",@progbits
	.4byte	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.Ldebug_loc0:
.LLST9:
	.byte	0x6
	.4byte	.LVL34
	.byte	0x4
	.uleb128 .LVL34-.LVL34
	.uleb128 .LVL35-.LVL34
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL35-.LVL34
	.uleb128 .LVL36-.LVL34
	.uleb128 0x4
	.byte	0x7a
	.sleb128 64
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL36-.LVL34
	.uleb128 .LVL37-1-.LVL34
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL37-1-.LVL34
	.uleb128 .LVL37-.LVL34
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
	.uleb128 .LVL37-.LVL34
	.uleb128 .LVL38-1-.LVL34
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL38-1-.LVL34
	.uleb128 .LVL38-.LVL34
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
	.uleb128 .LVL38-.LVL34
	.uleb128 .LVL39-.LVL34
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL39-.LVL34
	.uleb128 .LFE16-.LVL34
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
	.4byte	.LVL24
	.byte	0x4
	.uleb128 .LVL24-.LVL24
	.uleb128 .LVL27-1-.LVL24
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL27-1-.LVL24
	.uleb128 .LFE14-.LVL24
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
	.4byte	.LVL24
	.byte	0x4
	.uleb128 .LVL24-.LVL24
	.uleb128 .LVL25-.LVL24
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL25-.LVL24
	.uleb128 .LVL29-.LVL24
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL31-.LVL24
	.uleb128 .LVL32-.LVL24
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST8:
	.byte	0x6
	.4byte	.LVL24
	.byte	0x4
	.uleb128 .LVL24-.LVL24
	.uleb128 .LVL27-1-.LVL24
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL27-1-.LVL24
	.uleb128 .LVL30-.LVL24
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL30-.LVL24
	.uleb128 .LVL31-.LVL24
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
	.byte	0x4
	.uleb128 .LVL31-.LVL24
	.uleb128 .LFE14-.LVL24
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL9-1-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL9-1-.LVL8
	.uleb128 .LFE11-.LVL8
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
.LLST3:
	.byte	0x8
	.4byte	.LVL12
	.uleb128 .LVL13-1-.LVL12
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST4:
	.byte	0x8
	.4byte	.LVL15
	.uleb128 .LVL16-1-.LVL15
	.uleb128 0x1
	.byte	0x5a
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
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL4-.LVL0
	.uleb128 .LFE6-.LVL0
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
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL3-1-.LVL2
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL3-1-.LVL2
	.uleb128 .LVL5-.LVL2
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL5-.LVL2
	.uleb128 .LFE6-.LVL2
	.uleb128 0x2
	.byte	0x72
	.sleb128 -20
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x6c
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
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
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
	.uleb128 .LBB4-.LBB3
	.uleb128 .LBE4-.LBB3
	.byte	0x4
	.uleb128 .LBB5-.LBB3
	.uleb128 .LBE5-.LBB3
	.byte	0
.LLRL10:
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
	.4byte	.LFB11
	.uleb128 .LFE11-.LFB11
	.byte	0x7
	.4byte	.LFB9
	.uleb128 .LFE9-.LFB9
	.byte	0x7
	.4byte	.LFB10
	.uleb128 .LFE10-.LFB10
	.byte	0x7
	.4byte	.LFB13
	.uleb128 .LFE13-.LFB13
	.byte	0x7
	.4byte	.LFB14
	.uleb128 .LFE14-.LFB14
	.byte	0x7
	.4byte	.LFB15
	.uleb128 .LFE15-.LFB15
	.byte	0x7
	.4byte	.LFB16
	.uleb128 .LFE16-.LFB16
	.byte	0x7
	.4byte	.LFB17
	.uleb128 .LFE17-.LFB17
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF223:
	.string	"outgoing_report_ready"
.LASF214:
	.string	"T_AIR_COMBO_KEY_S"
.LASF54:
	.string	"RESERVED"
.LASF302:
	.string	"hal_gpio_set_output"
.LASF265:
	.string	"SLEEP_LOCK_IRRX"
.LASF263:
	.string	"SLEEP_LOCK_DMA"
.LASF327:
	.string	"riscv_mkey_ir_ctrl__reset_cnt"
.LASF297:
	.string	"mouse_sensor_is_lifted"
.LASF326:
	.string	"riscv_mkey_ir_ctrl_debug_print"
.LASF282:
	.string	"SLEEP_LOCK_APP"
.LASF292:
	.string	"protect_cnt_non_bt_mode_tbl"
.LASF26:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF65:
	.string	"GPT_REGISTER_T"
.LASF221:
	.string	"flags"
.LASF152:
	.string	"APP_STATE_CONNECT_PREPARING"
.LASF242:
	.string	"read_key_timestamp"
.LASF37:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF287:
	.string	"idle_level"
.LASF19:
	.string	"PRINT_LEVEL_DEBUG"
.LASF232:
	.string	"key_remap_enable"
.LASF3:
	.string	"unsigned int"
.LASF225:
	.string	"hid_shared_parameters"
.LASF168:
	.string	"APP_STATE_BT_CONNECTED_ACTIVE"
.LASF142:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF262:
	.string	"SLEEP_LOCK_TRNG"
.LASF50:
	.string	"msg_id_handle"
.LASF295:
	.string	"hal_gpt_delay_us"
.LASF57:
	.string	"GPT_CON_UNION"
.LASF124:
	.string	"DBG_PIN_SPI_CB"
.LASF136:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF246:
	.string	"hid_common"
.LASF160:
	.string	"APP_STATE_CONNECT_CANCEL_CHECK"
.LASF39:
	.string	"log_type_t"
.LASF234:
	.string	"riscv_trigger_time"
.LASF325:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF133:
	.string	"enable_mask"
.LASF35:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF316:
	.string	"riscv_mkey_ir_ctrl_deinit"
.LASF129:
	.string	"DBG_PIN_USB_SOF"
.LASF240:
	.string	"hid_common_info"
.LASF139:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF305:
	.string	"riscv_mkey_ir_ctrl_post_process"
.LASF306:
	.string	"new_state"
.LASF298:
	.string	"hal_gpt_sw_free_timer"
.LASF264:
	.string	"SLEEP_LOCK_IRTX"
.LASF260:
	.string	"SLEEP_LOCK_AESOTF"
.LASF199:
	.string	"numeric_key_pad"
.LASF143:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF183:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1"
.LASF277:
	.string	"SLEEP_LOCK_USB"
.LASF166:
	.string	"APP_STATE_USB_DISCONNECTING"
.LASF322:
	.string	"duration"
.LASF155:
	.string	"APP_STATE_BT_RECONNECT"
.LASF140:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF55:
	.string	"GPT_CON_CELLS"
.LASF216:
	.string	"step_2_4g"
.LASF60:
	.string	"GPT_IRQ_EN"
.LASF93:
	.string	"HAL_GPIO_27"
.LASF22:
	.string	"PRINT_LEVEL_ERROR"
.LASF31:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF4:
	.string	"signed char"
.LASF177:
	.string	"APP_STATE_2_4G_CONNECTED"
.LASF18:
	.string	"uint32_t"
.LASF146:
	.string	"T_HID_REPORT_RATE_VAL_S"
.LASF128:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF294:
	.string	"riscv_mouse_key_polling_all_key_status"
.LASF76:
	.string	"HAL_GPIO_10"
.LASF77:
	.string	"HAL_GPIO_11"
.LASF78:
	.string	"HAL_GPIO_12"
.LASF79:
	.string	"HAL_GPIO_13"
.LASF80:
	.string	"HAL_GPIO_14"
.LASF81:
	.string	"HAL_GPIO_15"
.LASF82:
	.string	"HAL_GPIO_16"
.LASF83:
	.string	"HAL_GPIO_17"
.LASF84:
	.string	"HAL_GPIO_18"
.LASF85:
	.string	"HAL_GPIO_19"
.LASF25:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF148:
	.string	"APP_STATE_INITIALIZED"
.LASF42:
	.string	"f_msg_id_t"
.LASF188:
	.string	"play_mode"
.LASF204:
	.string	"para"
.LASF212:
	.string	"combo_bit_00_31"
.LASF215:
	.string	"step_wired"
.LASF2:
	.string	"long long unsigned int"
.LASF248:
	.string	"hal_gpt_callback_t"
.LASF138:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF178:
	.string	"APP_STATE_2_4G_CONNECTED_ACTIVE"
.LASF198:
	.string	"consumer"
.LASF43:
	.string	"f_tlv_dump_t"
.LASF196:
	.string	"combo"
.LASF239:
	.string	"outgoing_report"
.LASF86:
	.string	"HAL_GPIO_20"
.LASF87:
	.string	"HAL_GPIO_21"
.LASF88:
	.string	"HAL_GPIO_22"
.LASF89:
	.string	"HAL_GPIO_23"
.LASF90:
	.string	"HAL_GPIO_24"
.LASF91:
	.string	"HAL_GPIO_25"
.LASF92:
	.string	"HAL_GPIO_26"
.LASF32:
	.string	"LOG_TYPE_HCI_DATA"
.LASF94:
	.string	"HAL_GPIO_28"
.LASF95:
	.string	"HAL_GPIO_29"
.LASF318:
	.string	"riscv_mkey_ir_ctrl_off"
.LASF254:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF201:
	.string	"dummy"
.LASF313:
	.string	"delta_time"
.LASF38:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF281:
	.string	"SLEEP_LOCK_I2C0"
.LASF98:
	.string	"HAL_GPIO_32"
.LASF100:
	.string	"HAL_GPIO_34"
.LASF102:
	.string	"HAL_GPIO_36"
.LASF324:
	.string	"ir_check_timestamp"
.LASF103:
	.string	"HAL_GPIO_37"
.LASF62:
	.string	"GPT_IRQ_ACK"
.LASF300:
	.string	"print_module_msgid_log"
.LASF105:
	.string	"HAL_GPIO_39"
.LASF237:
	.string	"app_shared_parameters"
.LASF131:
	.string	"DBG_PIN_USB_TX"
.LASF34:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF272:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF284:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF258:
	.string	"IR_LED_status_on"
.LASF238:
	.string	"mapped_data"
.LASF96:
	.string	"HAL_GPIO_30"
.LASF97:
	.string	"HAL_GPIO_31"
.LASF135:
	.string	"_Bool"
.LASF99:
	.string	"HAL_GPIO_33"
.LASF241:
	.string	"hid_exp_features"
.LASF101:
	.string	"HAL_GPIO_35"
.LASF235:
	.string	"mouse_key_list"
.LASF114:
	.string	"HAL_GPIO_MAX"
.LASF104:
	.string	"HAL_GPIO_38"
.LASF274:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF193:
	.string	"T_HID_KEY_REMAP_S"
.LASF53:
	.string	"SW_CG"
.LASF28:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF207:
	.string	"kb_std2"
.LASF209:
	.string	"kb_std5"
.LASF130:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF230:
	.string	"irpt_ctrl"
.LASF202:
	.string	"T_HID_REPORT_KB_STD5_S"
.LASF309:
	.string	"key_status"
.LASF169:
	.string	"APP_STATE_BT_CONNECTED_IDLE_1"
.LASF170:
	.string	"APP_STATE_BT_CONNECTED_IDLE_2"
.LASF171:
	.string	"APP_STATE_BT_CONNECTED_IDLE_3"
.LASF250:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF236:
	.string	"mouse_key_num"
.LASF106:
	.string	"HAL_GPIO_40"
.LASF107:
	.string	"HAL_GPIO_41"
.LASF108:
	.string	"HAL_GPIO_42"
.LASF29:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF110:
	.string	"HAL_GPIO_44"
.LASF27:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF112:
	.string	"HAL_GPIO_46"
.LASF113:
	.string	"HAL_GPIO_47"
.LASF12:
	.string	"char"
.LASF33:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF16:
	.string	"uint8_t"
.LASF156:
	.string	"APP_STATE_2_4G_RECONNECT"
.LASF314:
	.string	"log_control_block_riscv_ps"
.LASF217:
	.string	"step_bt"
.LASF45:
	.string	"log_switch"
.LASF109:
	.string	"HAL_GPIO_43"
.LASF226:
	.string	"inActivity_timeout"
.LASF111:
	.string	"HAL_GPIO_45"
.LASF283:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF66:
	.string	"HAL_GPIO_0"
.LASF67:
	.string	"HAL_GPIO_1"
.LASF40:
	.string	"f_print_t"
.LASF69:
	.string	"HAL_GPIO_3"
.LASF70:
	.string	"HAL_GPIO_4"
.LASF71:
	.string	"HAL_GPIO_5"
.LASF72:
	.string	"HAL_GPIO_6"
.LASF73:
	.string	"HAL_GPIO_7"
.LASF74:
	.string	"HAL_GPIO_8"
.LASF75:
	.string	"HAL_GPIO_9"
.LASF192:
	.string	"status"
.LASF211:
	.string	"T_HID_CCNI_USB_REPORT_S"
.LASF261:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF141:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF253:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF311:
	.string	"user_data"
.LASF308:
	.string	"ir_status"
.LASF219:
	.string	"hid_scenario_type"
.LASF121:
	.string	"HAL_GPIO_STATUS_INVALID_PARAMETER"
.LASF10:
	.string	"long long int"
.LASF293:
	.string	"riscv_mouse_key__notify_cm33_key_status"
.LASF320:
	.string	"riscv_mkey_ir_ctrl__ir_key_check"
.LASF206:
	.string	"ms_s16_z8"
.LASF276:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF115:
	.string	"hal_gpio_pin_t"
.LASF41:
	.string	"f_dump_buffer_t"
.LASF165:
	.string	"APP_STATE_USB_ENTERING_ACTIVE"
.LASF157:
	.string	"APP_STATE_2_4G_QUICK_CONNECT"
.LASF213:
	.string	"combo_bit_32_63"
.LASF123:
	.string	"hal_gpio_status_t"
.LASF145:
	.string	"rr_idx_usb"
.LASF229:
	.string	"hold_timeout"
.LASF245:
	.string	"T_RISCV_APP_S"
.LASF20:
	.string	"PRINT_LEVEL_INFO"
.LASF127:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF61:
	.string	"GPT_IRQ_STA"
.LASF227:
	.string	"combo_key_list"
.LASF310:
	.string	"old_key_status"
.LASF273:
	.string	"SLEEP_LOCK_DCXO"
.LASF247:
	.string	"riscv_app"
.LASF68:
	.string	"HAL_GPIO_2"
.LASF290:
	.string	"T_IRPT_CTRL_S"
.LASF13:
	.string	"int8_t"
.LASF233:
	.string	"key_remap_fn_key"
.LASF266:
	.string	"SLEEP_LOCK_AIO"
.LASF151:
	.string	"APP_STATE_TEST"
.LASF315:
	.string	"msg_id_string"
.LASF303:
	.string	"hal_gpt_get_duration_count"
.LASF323:
	.string	"duration_count"
.LASF222:
	.string	"features"
.LASF117:
	.string	"HAL_GPIO_DATA_HIGH"
.LASF134:
	.string	"T_COMMON_LA_DBG_S"
.LASF231:
	.string	"scroll_ctrl"
.LASF252:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF208:
	.string	"kb_consumer1"
.LASF48:
	.string	"dump_handle"
.LASF158:
	.string	"APP_STATE_2_4G_RECONNECT_RESUME_WAIT"
.LASF11:
	.string	"long double"
.LASF17:
	.string	"uint16_t"
.LASF259:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF173:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_1"
.LASF174:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_2"
.LASF175:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_3"
.LASF249:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF185:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3"
.LASF49:
	.string	"tlv_dump_handle"
.LASF203:
	.string	"T_HID_REPORT_KB_CONSUMER2_S"
.LASF21:
	.string	"PRINT_LEVEL_WARNING"
.LASF162:
	.string	"APP_STATE_USB_ACTIVE"
.LASF289:
	.string	"protect_cnt"
.LASF299:
	.string	"hal_gpt_sw_stop_timer_us"
.LASF218:
	.string	"T_DEBOUNCE_PARA_S"
.LASF6:
	.string	"short int"
.LASF256:
	.string	"HAL_GPT_STATUS_OK"
.LASF8:
	.string	"long int"
.LASF210:
	.string	"kb_consumer2"
.LASF197:
	.string	"T_HID_REPORT_KB_STD2_XY_S"
.LASF119:
	.string	"HAL_GPIO_STATUS_ERROR"
.LASF275:
	.string	"SLEEP_LOCK_I3C1"
.LASF137:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF14:
	.string	"int16_t"
.LASF118:
	.string	"hal_gpio_data_t"
.LASF150:
	.string	"APP_STATE_DISCONNECTED"
.LASF255:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF159:
	.string	"APP_STATE_CONNECT_CANCEL"
.LASF125:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF301:
	.string	"hal_gpt_sw_get_timer"
.LASF172:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_ACTIVE"
.LASF59:
	.string	"GPT_CLK"
.LASF58:
	.string	"GPT_CLR"
.LASF47:
	.string	"print_handle"
.LASF251:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF317:
	.string	"riscv_mkey_ir_ctrl_init"
.LASF147:
	.string	"APP_STATE_NONE"
.LASF267:
	.string	"SLEEP_LOCK_FLASH"
.LASF328:
	.string	"riscv_mkey_ir_ctrl_idle_state_scan_stop"
.LASF288:
	.string	"turn_on_timer_hdl"
.LASF307:
	.string	"next_read_key_time"
.LASF120:
	.string	"HAL_GPIO_STATUS_ERROR_PIN"
.LASF176:
	.string	"APP_STATE_BT_DISCONNECTING"
.LASF51:
	.string	"log_control_block_t"
.LASF190:
	.string	"macro"
.LASF189:
	.string	"repeat_times"
.LASF184:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2"
.LASF9:
	.string	"long unsigned int"
.LASF186:
	.string	"APP_STATE_2_4G_DISCONNECTING"
.LASF224:
	.string	"delay_for_key_polling_ms"
.LASF122:
	.string	"HAL_GPIO_STATUS_OK"
.LASF15:
	.string	"int32_t"
.LASF36:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF268:
	.string	"SLEEP_LOCK_ESC"
.LASF257:
	.string	"hal_gpt_status_t"
.LASF291:
	.string	"irpt"
.LASF179:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_1"
.LASF180:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_2"
.LASF181:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_3"
.LASF5:
	.string	"unsigned char"
.LASF182:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE"
.LASF116:
	.string	"HAL_GPIO_DATA_LOW"
.LASF144:
	.string	"rr_idx_2_4g"
.LASF312:
	.string	"ir_timer_start"
.LASF24:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF286:
	.string	"pin_id"
.LASF44:
	.string	"module_name"
.LASF153:
	.string	"APP_STATE_BT_PAIRING"
.LASF52:
	.string	"MODE"
.LASF329:
	.string	"riscv_mkey_ir_ctrl_idle_state_scan"
.LASF244:
	.string	"state"
.LASF205:
	.string	"T_OUTPUT_CTRL_PIN_INFO_S"
.LASF321:
	.string	"riscv_mkey_ir_ctrl_delay"
.LASF30:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF163:
	.string	"APP_STATE_USB_SUSPEND"
.LASF243:
	.string	"rr_idx"
.LASF228:
	.string	"combo_key_list_size"
.LASF191:
	.string	"item"
.LASF46:
	.string	"print_level"
.LASF269:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF270:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF271:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF167:
	.string	"APP_STATE_BT_CONNECTED"
.LASF149:
	.string	"APP_STATE_STANDBY"
.LASF164:
	.string	"APP_STATE_USB_STOP"
.LASF7:
	.string	"short unsigned int"
.LASF126:
	.string	"DBG_PIN_NACK"
.LASF200:
	.string	"T_HID_REPORT_KB_CONSUMER1_XY_S"
.LASF132:
	.string	"DBG_PIN_MAX"
.LASF56:
	.string	"GPT_CON"
.LASF285:
	.string	"ir_turn_on_timestamp"
.LASF154:
	.string	"APP_STATE_2_4G_PAIRING"
.LASF296:
	.string	"hal_gpt_sw_start_timer_us"
.LASF64:
	.string	"GPT_COMPARE"
.LASF195:
	.string	"T_HID_REPORT_MS_K8_S16_Z8_S"
.LASF161:
	.string	"APP_STATE_USB_CONNECTED"
.LASF187:
	.string	"keycode"
.LASF319:
	.string	"riscv_mkey_ir_ctrl_on"
.LASF278:
	.string	"SLEEP_LOCK_UART0"
.LASF279:
	.string	"SLEEP_LOCK_UART1"
.LASF280:
	.string	"SLEEP_LOCK_UART2"
.LASF194:
	.string	"report_id"
.LASF304:
	.string	"riscv_mkey_ir_ctrl__app_state_update"
.LASF63:
	.string	"GPT_COUNT"
.LASF23:
	.string	"print_level_t"
.LASF220:
	.string	"dongle_scenario"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_mouse_key_ir_ctrl.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
