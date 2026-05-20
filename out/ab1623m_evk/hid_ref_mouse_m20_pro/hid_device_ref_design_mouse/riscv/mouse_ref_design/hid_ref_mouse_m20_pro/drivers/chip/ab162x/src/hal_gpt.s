	.file	"hal_gpt.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_gpt.c"
	.section	.text.hal_gpt_init,"ax",@progbits
	.align	1
	.globl	hal_gpt_init
	.hidden	hal_gpt_init
	.type	hal_gpt_init, @function
hal_gpt_init:
.LFB5:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_gpt.c"
	.loc 1 60 1
	.cfi_startproc
.LVL0:
	.loc 1 61 5
	.loc 1 63 5
	.loc 1 60 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	sw	ra,8(sp)
	sw	s1,0(sp)
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 63 13
	call	gpt_get_context_index
.LVL1:
	.loc 1 65 5 is_stmt 1
.LBB14:
.LBB15:
	.loc 1 53 5
	.loc 1 53 8 is_stmt 0
	bne	s0,zero,.L3
	mv	a5,a0
	.loc 1 54 9 is_stmt 1
.LVL2:
.LBE15:
.LBE14:
	.loc 1 65 68 is_stmt 0 discriminator 2
	li	s1,1
	.loc 1 66 16
	li	a0,-2
.LVL3:
	.loc 1 65 68 discriminator 2
	bgtu	a5,s1,.L1
	.loc 1 69 5 is_stmt 1
	.loc 1 69 30 is_stmt 0
	slli	a5,a5,4
.LVL4:
	lla	s0,g_gpt_context
.LVL5:
	add	s0,s0,a5
	.loc 1 69 8
	lw	a5,0(s0)
	.loc 1 70 16
	li	a0,-3
	.loc 1 69 8
	beq	a5,s1,.L1
	.loc 1 69 66 discriminator 1
	lbu	a5,12(s0)
	bne	a5,zero,.L1
	.loc 1 74 5 is_stmt 1
	li	a2,16
	li	a1,0
	mv	a0,s0
	call	memset
.LVL6:
	.loc 1 78 5
	call	gpt_open_clock_source
.LVL7:
	.loc 1 80 5
	.loc 1 80 72 is_stmt 0
	li	a4,1108672512
	lw	a5,0(a4)
	.loc 1 80 81
	li	a3,-65536
	addi	a3,a3,-1
	and	a5,a5,a3
	sw	a5,0(a4)
	.loc 1 82 5 is_stmt 1
	.loc 1 82 53 is_stmt 0
	li	a5,1108676608
	addi	a5,a5,-1024
	lw	a3,8(a5)
	.loc 1 88 43
	lw	a0,gpt_lock_sleep_name
	.loc 1 82 67
	andi	a3,a3,-2
	sw	a3,8(a5)
	.loc 1 83 5 is_stmt 1
	.loc 1 83 53 is_stmt 0
	lw	a3,16(a5)
	.loc 1 83 70
	andi	a3,a3,-2
	sw	a3,16(a5)
	.loc 1 86 5 is_stmt 1
	.loc 1 86 57 is_stmt 0
	lw	a5,12(a4)
	.loc 1 86 70
	andi	a5,a5,-2
	sw	a5,12(a4)
	.loc 1 88 5 is_stmt 1
	.loc 1 88 9
	.loc 1 88 43 is_stmt 0
	call	hal_sleep_manager_set_sleep_handle
.LVL8:
	.loc 1 88 41 discriminator 1
	sb	a0,gpt_lock_sleep_handle,a5
	.loc 1 88 7 is_stmt 1 discriminator 1
	.loc 1 94 5
	.loc 1 94 41 is_stmt 0
	sb	s1,12(s0)
	.loc 1 96 5 is_stmt 1
	.loc 1 96 12 is_stmt 0
	li	a0,0
.L1:
	.loc 1 97 1
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
.LVL9:
.L3:
	.cfi_restore_state
	.loc 1 66 16
	li	a0,-2
.LVL10:
	j	.L1
	.cfi_endproc
.LFE5:
	.size	hal_gpt_init, .-hal_gpt_init
	.section	.text.hal_gpt_deinit,"ax",@progbits
	.align	1
	.globl	hal_gpt_deinit
	.hidden	hal_gpt_deinit
	.type	hal_gpt_deinit, @function
hal_gpt_deinit:
.LFB6:
	.loc 1 100 1 is_stmt 1
	.cfi_startproc
.LVL11:
	.loc 1 101 5
	.loc 1 103 5
	.loc 1 100 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 103 13
	call	gpt_get_context_index
.LVL12:
	.loc 1 105 5 is_stmt 1
.LBB16:
.LBB17:
	.loc 1 53 5
	.loc 1 53 8 is_stmt 0
	bne	s0,zero,.L10
	mv	a5,a0
	.loc 1 54 9 is_stmt 1
.LVL13:
.LBE17:
.LBE16:
	.loc 1 105 68 is_stmt 0 discriminator 2
	li	a4,1
	.loc 1 106 16
	li	a0,-2
.LVL14:
	.loc 1 105 68 discriminator 2
	bgtu	a5,a4,.L8
	.loc 1 109 5 is_stmt 1
	.loc 1 109 29 is_stmt 0
	slli	a5,a5,4
.LVL15:
	lla	s0,g_gpt_context
.LVL16:
	add	s0,s0,a5
	.loc 1 109 8
	lw	a5,0(s0)
	.loc 1 111 16
	li	a0,-3
	.loc 1 109 8
	beq	a5,a4,.L8
	.loc 1 115 5 is_stmt 1
	li	a2,16
	li	a1,0
	mv	a0,s0
	call	memset
.LVL17:
	.loc 1 118 5
	.loc 1 120 53 is_stmt 0
	li	a5,1108676608
	addi	a5,a5,-1024
	lw	a4,4(a5)
	.loc 1 118 41
	sb	zero,12(s0)
	.loc 1 120 5 is_stmt 1
	.loc 1 122 5 is_stmt 0
	li	a0,0
	.loc 1 120 67
	ori	a4,a4,1
	sw	a4,4(a5)
	.loc 1 122 5 is_stmt 1
	call	gpt_reset_default_timer
.LVL18:
	.loc 1 124 5
	.loc 1 124 9
	lbu	a0,gpt_lock_sleep_handle
	call	hal_sleep_manager_release_sleep_handle
.LVL19:
	.loc 1 124 7 discriminator 1
	.loc 1 129 5
	.loc 1 129 12 is_stmt 0
	li	a0,0
.L8:
	.loc 1 130 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL20:
.L10:
	.cfi_restore_state
	.loc 1 106 16
	li	a0,-2
.LVL21:
	j	.L8
	.cfi_endproc
.LFE6:
	.size	hal_gpt_deinit, .-hal_gpt_deinit
	.section	.text.hal_gpt_get_free_run_count,"ax",@progbits
	.align	1
	.globl	hal_gpt_get_free_run_count
	.hidden	hal_gpt_get_free_run_count
	.type	hal_gpt_get_free_run_count, @function
hal_gpt_get_free_run_count:
.LFB7:
	.loc 1 134 1 is_stmt 1
	.cfi_startproc
.LVL22:
	.loc 1 136 5
	.loc 1 134 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s1,0(sp)
	sw	ra,8(sp)
	sw	s0,4(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 134 1
	mv	s1,a1
	.loc 1 136 8
	bne	a0,zero,.L15
	.loc 1 137 9 is_stmt 1
	.loc 1 137 30 is_stmt 0
	lla	s0,gpt_running_state
	.loc 1 137 12
	lw	a4,0(s0)
	li	a5,1
	beq	a4,a5,.L16
	.loc 1 143 13 is_stmt 1
	li	a0,1108672512
.LVL23:
	li	a2,0
	li	a1,16
.LVL24:
	addi	a0,a0,256
	call	gpt_start_free_run_timer
.LVL25:
	.loc 1 146 13
	.loc 1 146 34 is_stmt 0
	li	a5,1
	sw	a5,0(s0)
.L16:
	.loc 1 152 9 is_stmt 1
	.loc 1 152 18 is_stmt 0
	li	a0,1108672512
	addi	a0,a0,256
.L22:
	call	gpt_current_count
.LVL26:
	.loc 1 152 16 discriminator 1
	sw	a0,0(s1)
	.loc 1 170 12
	li	a0,0
.L14:
	.loc 1 171 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	lw	s1,0(sp)
	.cfi_restore 9
.LVL27:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL28:
.L15:
	.cfi_restore_state
	mv	s0,a0
	.loc 1 156 10 is_stmt 1
	.loc 1 156 13 is_stmt 0
	li	a5,1
	.loc 1 167 16
	li	a0,-1
.LVL29:
	.loc 1 156 13
	bne	s0,a5,.L14
	.loc 1 157 9 is_stmt 1
	.loc 1 157 30 is_stmt 0
	lla	a5,gpt_running_state
	.loc 1 157 12
	lw	a4,4(a5)
	beq	a4,s0,.L18
	.loc 1 160 13 is_stmt 1
	li	a0,1108672512
	li	a2,13
	li	a1,0
	addi	a0,a0,512
	call	gpt_start_free_run_timer
.LVL30:
	.loc 1 162 13
	.loc 1 162 34 is_stmt 0
	lla	a5,gpt_running_state
	sw	s0,4(a5)
.L18:
	.loc 1 165 9 is_stmt 1
	.loc 1 165 18 is_stmt 0
	li	a0,1108672512
	addi	a0,a0,512
	j	.L22
	.cfi_endproc
.LFE7:
	.size	hal_gpt_get_free_run_count, .-hal_gpt_get_free_run_count
	.section	.text.hal_gpt_get_duration_count,"ax",@progbits
	.align	1
	.globl	hal_gpt_get_duration_count
	.hidden	hal_gpt_get_duration_count
	.type	hal_gpt_get_duration_count, @function
hal_gpt_get_duration_count:
.LFB8:
	.loc 1 174 1 is_stmt 1
	.cfi_startproc
.LVL31:
	.loc 1 175 5
	.loc 1 175 8 is_stmt 0
	beq	a2,zero,.L25
	.loc 1 179 5 is_stmt 1
	.loc 1 182 9
	.loc 1 180 37 is_stmt 0
	sub	a1,a1,a0
.LVL32:
	.loc 1 182 25
	sw	a1,0(a2)
	.loc 1 184 12
	li	a0,0
.LVL33:
	ret
.LVL34:
.L25:
	.loc 1 176 16
	li	a0,-1
.LVL35:
	.loc 1 185 1
	ret
	.cfi_endproc
.LFE8:
	.size	hal_gpt_get_duration_count, .-hal_gpt_get_duration_count
	.section	.text.hal_gpt_get_running_status,"ax",@progbits
	.align	1
	.globl	hal_gpt_get_running_status
	.hidden	hal_gpt_get_running_status
	.type	hal_gpt_get_running_status, @function
hal_gpt_get_running_status:
.LFB9:
	.loc 1 188 1 is_stmt 1
	.cfi_startproc
.LVL36:
	.loc 1 189 5
	.loc 1 191 5
	.loc 1 188 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 188 1
	mv	s1,a0
	mv	s0,a1
	.loc 1 191 13
	call	gpt_get_context_index
.LVL37:
	.loc 1 193 5 is_stmt 1
	.loc 1 193 8 is_stmt 0
	li	a5,1
	bgtu	a0,a5,.L27
	.loc 1 194 9 is_stmt 1
	.loc 1 194 47 is_stmt 0
	slli	a0,a0,4
.LVL38:
	lla	a5,g_gpt_context
	add	a5,a5,a0
	lw	a5,0(a5)
.L33:
	.loc 1 199 25
	sw	a5,0(s0)
	.loc 1 200 9 is_stmt 1
	.loc 1 195 16 is_stmt 0
	li	a0,0
.L26:
	.loc 1 210 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL39:
	lw	s1,0(sp)
	.cfi_restore 9
.LVL40:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL41:
.L27:
	.cfi_restore_state
	.loc 1 198 5 is_stmt 1
	.loc 1 198 8 is_stmt 0
	bne	s1,a5,.L29
	.loc 1 199 9 is_stmt 1
	.loc 1 199 44 is_stmt 0
	lw	a5,gpt_running_state
	j	.L33
.L29:
	.loc 1 203 5 is_stmt 1
	.loc 1 203 8 is_stmt 0
	li	a5,2
	.loc 1 208 12
	li	a0,-2
.LVL42:
	.loc 1 203 8
	bne	s1,a5,.L26
	.loc 1 204 9 is_stmt 1
	.loc 1 204 44 is_stmt 0
	lw	a5,gpt_running_state+4
	j	.L33
	.cfi_endproc
.LFE9:
	.size	hal_gpt_get_running_status, .-hal_gpt_get_running_status
	.section	.text.hal_gpt_register_callback,"ax",@progbits
	.align	1
	.globl	hal_gpt_register_callback
	.hidden	hal_gpt_register_callback
	.type	hal_gpt_register_callback, @function
hal_gpt_register_callback:
.LFB10:
	.loc 1 215 1 is_stmt 1
	.cfi_startproc
.LVL43:
	.loc 1 217 5
	.loc 1 219 5
	.loc 1 215 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	s1,4(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 215 1
	sw	a0,0(sp)
	mv	s0,a1
	mv	s1,a2
	.loc 1 219 13
	call	gpt_get_context_index
.LVL44:
	.loc 1 221 5 is_stmt 1
.LBB18:
.LBB19:
	.loc 1 53 5
	.loc 1 53 8 is_stmt 0
	lw	a4,0(sp)
	bne	a4,zero,.L36
	mv	a5,a0
	.loc 1 54 9 is_stmt 1
.LVL45:
.LBE19:
.LBE18:
	.loc 1 221 68 is_stmt 0 discriminator 2
	li	a4,1
	.loc 1 222 16
	li	a0,-2
.LVL46:
	.loc 1 221 68 discriminator 2
	bgtu	a5,a4,.L34
	.loc 1 225 5 is_stmt 1
	.loc 1 225 30 is_stmt 0
	slli	a0,a5,4
	lla	a5,g_gpt_context
.LVL47:
	add	a5,a5,a0
	.loc 1 225 8
	lw	a3,0(a5)
	.loc 1 228 16
	li	a0,-3
	.loc 1 225 8
	beq	a3,a4,.L34
	.loc 1 225 66 discriminator 1
	lbu	a4,12(a5)
	beq	a4,zero,.L34
	.loc 1 231 5 is_stmt 1
	.loc 1 232 16 is_stmt 0
	li	a0,-1
	.loc 1 231 8
	beq	s0,zero,.L34
	.loc 1 238 5 is_stmt 1
	.loc 1 238 52 is_stmt 0
	sw	s0,4(a5)
	.loc 1 239 5 is_stmt 1
	.loc 1 239 53 is_stmt 0
	sw	s1,8(a5)
	.loc 1 241 5 is_stmt 1
	call	gpt_nvic_register
.LVL48:
	.loc 1 243 5
	.loc 1 243 12 is_stmt 0
	li	a0,0
.L34:
	.loc 1 244 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL49:
	lw	s1,4(sp)
	.cfi_restore 9
.LVL50:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
.LVL51:
	jr	ra
.LVL52:
.L36:
	.cfi_restore_state
	.loc 1 222 16
	li	a0,-2
.LVL53:
	j	.L34
	.cfi_endproc
.LFE10:
	.size	hal_gpt_register_callback, .-hal_gpt_register_callback
	.section	.text.hal_gpt_start_timer_ms,"ax",@progbits
	.align	1
	.globl	hal_gpt_start_timer_ms
	.hidden	hal_gpt_start_timer_ms
	.type	hal_gpt_start_timer_ms, @function
hal_gpt_start_timer_ms:
.LFB11:
	.loc 1 247 1 is_stmt 1
	.cfi_startproc
.LVL54:
	.loc 1 249 5
	.loc 1 250 5
	.loc 1 252 5
	.loc 1 247 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 247 1
	sw	a0,0(sp)
	mv	s0,a1
	mv	s1,a2
	.loc 1 252 13
	call	gpt_get_context_index
.LVL55:
	.loc 1 254 5 is_stmt 1
.LBB20:
.LBB21:
	.loc 1 53 5
	.loc 1 53 8 is_stmt 0
	lw	a4,0(sp)
	bne	a4,zero,.L48
	mv	a5,a0
	.loc 1 54 9 is_stmt 1
.LVL56:
.LBE21:
.LBE20:
	.loc 1 254 68 is_stmt 0 discriminator 2
	li	a2,1
	.loc 1 255 16
	li	a0,-2
.LVL57:
	.loc 1 254 68 discriminator 2
	bgtu	a5,a2,.L42
	.loc 1 258 5 is_stmt 1
	.loc 1 258 30 is_stmt 0
	slli	a5,a5,4
.LVL58:
	lla	a3,g_gpt_context
	add	a4,a3,a5
	.loc 1 258 8
	lw	a1,0(a4)
	.loc 1 258 30
	sw	a5,0(sp)
.LVL59:
	.loc 1 261 16
	li	a0,-4
	.loc 1 258 8
	beq	a1,a2,.L42
	.loc 1 259 9
	lbu	a4,12(a4)
	beq	a4,zero,.L42
	.loc 1 264 5 is_stmt 1
	.loc 1 264 8 is_stmt 0
	li	a4,130150400
	addi	a4,a4,123
	.loc 1 265 16
	li	a0,-1
	.loc 1 264 8
	bgtu	s0,a4,.L42
	.loc 1 273 5 is_stmt 1
	addi	a0,sp,4
	call	hal_nvic_save_and_set_interrupt_mask
.LVL60:
	.loc 1 275 5
	.loc 1 275 70 is_stmt 0
	li	a4,1108672512
	sw	zero,12(a4)
	.loc 1 276 5 is_stmt 1
	.loc 1 276 86 is_stmt 0
	lbu	a2,0(a4)
	.loc 1 288 73
	mv	a0,s0
	.loc 1 276 90
	andi	a2,a2,254
	sb	a2,0(a4)
	.loc 1 287 5 is_stmt 1
	.loc 1 288 5
	.loc 1 287 67 is_stmt 0
	sw	zero,8(a4)
	.loc 1 288 73
	call	gpt_convert_ms_to_32k_count
.LVL61:
	.loc 1 289 60 discriminator 1
	lw	a5,0(sp)
	.loc 1 288 71 discriminator 1
	li	a4,1108672512
	.loc 1 289 60 discriminator 1
	li	a2,1108676608
	.loc 1 288 71 discriminator 1
	sw	a0,28(a4)
	.loc 1 289 5 is_stmt 1
	.loc 1 289 60 is_stmt 0 discriminator 1
	addi	a2,a2,-1024
	lla	a3,g_gpt_context
.L44:
	.loc 1 289 12 is_stmt 1 discriminator 1
	.loc 1 289 60 is_stmt 0 discriminator 1
	lw	a4,24(a2)
	.loc 1 289 75 discriminator 1
	andi	a4,a4,1
	.loc 1 289 12 discriminator 1
	bne	a4,zero,.L44
	.loc 1 291 5 is_stmt 1
	.loc 1 291 71 is_stmt 0
	li	a2,1
	li	a4,1108672512
	sw	a2,20(a4)
	.loc 1 292 5 is_stmt 1
	.loc 1 292 67 is_stmt 0
	sw	a2,4(a4)
	.loc 1 293 5 is_stmt 1
	.loc 1 293 60 is_stmt 0 discriminator 1
	li	a2,1108676608
	addi	a2,a2,-1024
.L45:
	.loc 1 293 12 is_stmt 1 discriminator 1
	.loc 1 293 60 is_stmt 0 discriminator 1
	lw	a4,20(a2)
	.loc 1 293 73 discriminator 1
	andi	a4,a4,1
	.loc 1 293 12 discriminator 1
	bne	a4,zero,.L45
	.loc 1 296 5 is_stmt 1
	.loc 1 296 67 is_stmt 0
	li	a4,1108672512
	li	a2,16
	sw	a2,8(a4)
	.loc 1 298 5 is_stmt 1
	.loc 1 298 81 is_stmt 0
	sw	zero,0(a4)
	.loc 1 301 5 is_stmt 1
	.loc 1 302 76 is_stmt 0
	lw	a2,0(a4)
	.loc 1 301 8
	beq	s1,zero,.L46
	.loc 1 302 9 is_stmt 1
	.loc 1 302 85 is_stmt 0
	ori	a2,a2,257
.L56:
	.loc 1 304 85
	sw	a2,0(a4)
	.loc 1 307 5 is_stmt 1
	.loc 1 307 70 is_stmt 0
	li	a4,1
	li	a2,1108672512
	sw	a4,12(a2)
	.loc 1 308 5 is_stmt 1
	.loc 1 309 5 is_stmt 0
	lw	a0,4(sp)
	.loc 1 308 41
	add	a5,a3,a5
	sw	a4,0(a5)
	.loc 1 309 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL62:
	.loc 1 312 5
	.loc 1 312 12 is_stmt 0
	li	a0,0
.L42:
	.loc 1 313 1
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
.LVL63:
	lw	s1,8(sp)
	.cfi_restore 9
.LVL64:
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL65:
.L46:
	.cfi_restore_state
	.loc 1 304 9 is_stmt 1
	.loc 1 304 85 is_stmt 0
	ori	a2,a2,1
	j	.L56
.LVL66:
.L48:
	.loc 1 255 16
	li	a0,-2
.LVL67:
	j	.L42
	.cfi_endproc
.LFE11:
	.size	hal_gpt_start_timer_ms, .-hal_gpt_start_timer_ms
	.section	.text.hal_gpt_delay_ms,"ax",@progbits
	.align	1
	.globl	hal_gpt_delay_ms
	.hidden	hal_gpt_delay_ms
	.type	hal_gpt_delay_ms, @function
hal_gpt_delay_ms:
.LFB12:
	.loc 1 317 1 is_stmt 1
	.cfi_startproc
.LVL68:
	.loc 1 322 5
	.loc 1 317 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s1,4(sp)
	.cfi_offset 9, -12
	.loc 1 322 26
	lla	s1,gpt_running_state
	.loc 1 322 8
	lw	a4,0(s1)
	.loc 1 317 1
	sw	s0,8(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 317 1
	sw	a0,0(sp)
	.loc 1 322 8
	li	s0,1
	beq	a4,s0,.L58
	.loc 1 325 9 is_stmt 1
	li	a0,1108672512
.LVL69:
	li	a2,0
	li	a1,16
	addi	a0,a0,256
	call	gpt_start_free_run_timer
.LVL70:
	.loc 1 326 9
	.loc 1 326 30 is_stmt 0
	sw	s0,0(s1)
.L58:
	.loc 1 328 5 is_stmt 1
	lw	a0,0(sp)
	call	gpt_convert_ms_to_32k_count
.LVL71:
	mv	a1,a0
	.loc 1 328 5 is_stmt 0 discriminator 1
	li	a0,1108672512
	addi	a0,a0,256
	call	gpt_delay_time
.LVL72:
	.loc 1 331 5 is_stmt 1
	.loc 1 332 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
.LVL73:
	jr	ra
	.cfi_endproc
.LFE12:
	.size	hal_gpt_delay_ms, .-hal_gpt_delay_ms
	.section	.text.hal_gpt_start_timer_us,"ax",@progbits
	.align	1
	.globl	hal_gpt_start_timer_us
	.hidden	hal_gpt_start_timer_us
	.type	hal_gpt_start_timer_us, @function
hal_gpt_start_timer_us:
.LFB13:
	.loc 1 337 1 is_stmt 1
	.cfi_startproc
.LVL74:
	.loc 1 338 5
	.loc 1 339 5
	.loc 1 341 5
	.loc 1 337 1 is_stmt 0
	addi	sp,sp,-28
	.cfi_def_cfa_offset 28
	sw	s0,20(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	sw	s1,16(sp)
	sw	ra,24(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 337 1
	mv	s1,a1
	sw	a2,0(sp)
	.loc 1 341 13
	call	gpt_get_context_index
.LVL75:
	.loc 1 343 5 is_stmt 1
.LBB22:
.LBB23:
	.loc 1 53 5
	.loc 1 53 8 is_stmt 0
	bne	s0,zero,.L65
	mv	a5,a0
	.loc 1 54 9 is_stmt 1
.LVL76:
.LBE23:
.LBE22:
	.loc 1 343 68 is_stmt 0 discriminator 2
	li	s0,1
.LVL77:
	.loc 1 345 16
	li	a0,-2
.LVL78:
	.loc 1 343 68 discriminator 2
	bgtu	a5,s0,.L60
	.loc 1 348 5 is_stmt 1
	.loc 1 348 30 is_stmt 0
	slli	a5,a5,4
.LVL79:
	lla	a2,g_gpt_context
	add	a4,a2,a5
	.loc 1 348 8
	lw	a1,0(a4)
	.loc 1 348 30
	sw	a5,8(sp)
	.loc 1 351 16
	li	a0,-4
	.loc 1 348 8
	beq	a1,s0,.L60
	.loc 1 349 9
	lbu	a1,12(a4)
	sw	a4,4(sp)
	beq	a1,zero,.L60
	.loc 1 360 5 is_stmt 1
	.loc 1 360 9
	lbu	a0,gpt_lock_sleep_handle
	call	hal_sleep_manager_lock_sleep
.LVL80:
	.loc 1 360 7 discriminator 1
	.loc 1 361 5
	.loc 1 361 46 is_stmt 0
	lw	a4,4(sp)
	.loc 1 363 5
	addi	a0,sp,12
	.loc 1 361 46
	sb	s0,13(a4)
	.loc 1 363 5 is_stmt 1
	call	hal_nvic_save_and_set_interrupt_mask
.LVL81:
	.loc 1 365 5
	.loc 1 365 70 is_stmt 0
	li	a4,1108672512
	sw	zero,12(a4)
	.loc 1 366 5 is_stmt 1
	.loc 1 366 86 is_stmt 0
	lbu	a1,0(a4)
	.loc 1 373 60 discriminator 1
	lw	a5,8(sp)
	li	a3,1108676608
	.loc 1 366 90
	andi	a1,a1,254
	sb	a1,0(a4)
	.loc 1 369 5 is_stmt 1
	.loc 1 369 67 is_stmt 0
	li	a1,13
	sw	a1,8(a4)
	.loc 1 370 5 is_stmt 1
	.loc 1 370 71 is_stmt 0
	sw	s1,28(a4)
	.loc 1 371 5 is_stmt 1
	.loc 1 371 71 is_stmt 0
	sw	s0,20(a4)
	.loc 1 372 5 is_stmt 1
	.loc 1 372 67 is_stmt 0
	sw	s0,4(a4)
	.loc 1 373 5 is_stmt 1
	.loc 1 373 60 is_stmt 0 discriminator 1
	addi	a3,a3,-1024
	lla	a2,g_gpt_context
.L62:
	.loc 1 373 12 is_stmt 1 discriminator 1
	.loc 1 373 60 is_stmt 0 discriminator 1
	lw	a4,20(a3)
	.loc 1 373 73 discriminator 1
	andi	a4,a4,1
	.loc 1 373 12 discriminator 1
	bne	a4,zero,.L62
	.loc 1 375 5 is_stmt 1
	.loc 1 377 8 is_stmt 0
	lw	a3,0(sp)
	.loc 1 375 81
	li	a4,1108672512
	sw	zero,0(a4)
	.loc 1 377 5 is_stmt 1
	.loc 1 377 8 is_stmt 0
	beq	a3,zero,.L63
	.loc 1 378 9 is_stmt 1
	.loc 1 378 76 is_stmt 0
	lw	a3,0(a4)
	.loc 1 378 85
	ori	a3,a3,257
.L71:
	.loc 1 380 85
	sw	a3,0(a4)
	.loc 1 383 5 is_stmt 1
	.loc 1 383 70 is_stmt 0
	li	a4,1
	li	a3,1108672512
	sw	a4,12(a3)
	.loc 1 384 5 is_stmt 1
	.loc 1 386 5 is_stmt 0
	lw	a0,12(sp)
	.loc 1 384 41
	add	a5,a2,a5
	sw	a4,0(a5)
	.loc 1 386 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL82:
	.loc 1 388 5
	.loc 1 388 12 is_stmt 0
	li	a0,0
.L60:
	.loc 1 389 1
	lw	ra,24(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,20(sp)
	.cfi_restore 8
	lw	s1,16(sp)
	.cfi_restore 9
.LVL83:
	addi	sp,sp,28
	.cfi_def_cfa_offset 0
.LVL84:
	jr	ra
.LVL85:
.L63:
	.cfi_restore_state
	.loc 1 380 9 is_stmt 1
	.loc 1 380 76 is_stmt 0
	lw	a3,0(a4)
	.loc 1 380 85
	ori	a3,a3,1
	j	.L71
.LVL86:
.L65:
	.loc 1 345 16
	li	a0,-2
.LVL87:
	j	.L60
	.cfi_endproc
.LFE13:
	.size	hal_gpt_start_timer_us, .-hal_gpt_start_timer_us
	.section	.text.hal_gpt_delay_us,"ax",@progbits
	.align	1
	.globl	hal_gpt_delay_us
	.hidden	hal_gpt_delay_us
	.type	hal_gpt_delay_us, @function
hal_gpt_delay_us:
.LFB14:
	.loc 1 394 1 is_stmt 1
	.cfi_startproc
.LVL88:
	.loc 1 396 5
	.loc 1 394 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s1,4(sp)
	.cfi_offset 9, -12
	.loc 1 396 26
	lla	s1,gpt_running_state
	.loc 1 396 8
	lw	a4,4(s1)
	.loc 1 394 1
	sw	s0,8(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 394 1
	sw	a0,0(sp)
	.loc 1 396 8
	li	s0,1
	beq	a4,s0,.L73
	.loc 1 399 9 is_stmt 1
	li	a0,1108672512
.LVL89:
	li	a2,13
	li	a1,0
	addi	a0,a0,512
	call	gpt_start_free_run_timer
.LVL90:
	.loc 1 401 9
	.loc 1 401 30 is_stmt 0
	sw	s0,4(s1)
.L73:
	.loc 1 403 5 is_stmt 1
	lw	a1,0(sp)
	li	a0,1108672512
	addi	a0,a0,512
	call	gpt_delay_time
.LVL91:
	.loc 1 405 5
	.loc 1 406 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
.LVL92:
	jr	ra
	.cfi_endproc
.LFE14:
	.size	hal_gpt_delay_us, .-hal_gpt_delay_us
	.section	.text.hal_gpt_stop_timer,"ax",@progbits
	.align	1
	.globl	hal_gpt_stop_timer
	.hidden	hal_gpt_stop_timer
	.type	hal_gpt_stop_timer, @function
hal_gpt_stop_timer:
.LFB15:
	.loc 1 411 1 is_stmt 1
	.cfi_startproc
.LVL93:
	.loc 1 412 5
	.loc 1 413 5
	.loc 1 415 5
	.loc 1 411 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s1,4(sp)
	.cfi_offset 9, -12
	mv	s1,a0
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 415 13
	call	gpt_get_context_index
.LVL94:
	.loc 1 417 5 is_stmt 1
.LBB24:
.LBB25:
	.loc 1 53 5
	.loc 1 53 8 is_stmt 0
	bne	s1,zero,.L78
	mv	s0,a0
	.loc 1 54 9 is_stmt 1
.LVL95:
.LBE25:
.LBE24:
	.loc 1 417 68 is_stmt 0 discriminator 2
	li	s1,1
.LVL96:
	.loc 1 418 16
	li	a0,-2
.LVL97:
	.loc 1 417 68 discriminator 2
	bgtu	s0,s1,.L75
	.loc 1 427 5 is_stmt 1
	mv	a0,sp
	call	hal_nvic_save_and_set_interrupt_mask
.LVL98:
	.loc 1 430 5
	.loc 1 430 57 is_stmt 0
	li	a5,1108672512
	lw	a4,12(a5)
	.loc 1 436 41
	slli	s0,s0,4
.LVL99:
	.loc 1 430 70
	andi	a4,a4,-2
	sw	a4,12(a5)
	.loc 1 433 5 is_stmt 1
	.loc 1 433 86 is_stmt 0
	lbu	a4,0(a5)
	.loc 1 433 90
	andi	a4,a4,254
	sb	a4,0(a5)
	.loc 1 434 5 is_stmt 1
	.loc 1 434 71 is_stmt 0
	sw	s1,20(a5)
	.loc 1 436 5 is_stmt 1
	.loc 1 437 5 is_stmt 0
	lw	a0,0(sp)
	.loc 1 436 41
	lla	a5,g_gpt_context
	add	s0,a5,s0
	sw	zero,0(s0)
	.loc 1 437 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL100:
	.loc 1 439 5
	.loc 1 439 8 is_stmt 0
	lbu	a5,13(s0)
	beq	a5,zero,.L77
	.loc 1 440 9 is_stmt 1
	.loc 1 440 13
	lbu	a0,gpt_lock_sleep_handle
	call	hal_sleep_manager_unlock_sleep
.LVL101:
	.loc 1 440 11 discriminator 1
	.loc 1 441 9
	.loc 1 441 50 is_stmt 0
	sb	zero,13(s0)
.L77:
	.loc 1 443 12
	li	a0,0
.L75:
	.loc 1 444 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL102:
.L78:
	.cfi_restore_state
	.loc 1 418 16
	li	a0,-2
.LVL103:
	j	.L75
	.cfi_endproc
.LFE15:
	.size	hal_gpt_stop_timer, .-hal_gpt_stop_timer
	.section	.text.hal_gpt_sw_get_timer,"ax",@progbits
	.align	1
	.globl	hal_gpt_sw_get_timer
	.hidden	hal_gpt_sw_get_timer
	.type	hal_gpt_sw_get_timer, @function
hal_gpt_sw_get_timer:
.LFB16:
	.loc 1 454 1 is_stmt 1
	.cfi_startproc
.LVL104:
	.loc 1 455 5
	.loc 1 456 5
	.loc 1 457 5
	.loc 1 458 5
	.loc 1 454 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 458 21
	sw	zero,sw_type_port.0,a5
	.loc 1 459 5 is_stmt 1
	.loc 1 454 1 is_stmt 0
	sw	s0,8(sp)
	sw	ra,12(sp)
	sw	s1,4(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 458 21
	lla	s0,sw_type_port.0
	.loc 1 459 21
	li	a5,1
	sw	a5,4(s0)
	.loc 1 460 5 is_stmt 1
	.loc 1 460 8 is_stmt 0
	beq	a0,zero,.L92
	mv	s1,a0
	.loc 1 463 5 is_stmt 1
	mv	a0,sp
.LVL105:
	call	hal_nvic_save_and_set_interrupt_mask
.LVL106:
	.loc 1 464 5
	.loc 1 464 23 is_stmt 0
	lbu	a1,g_sw_gpt_notes+200
	.loc 1 464 8
	li	a5,9
	.loc 1 464 23
	lla	a3,g_sw_gpt_notes
	.loc 1 468 12
	li	a4,0
	.loc 1 468 19 discriminator 1
	li	a2,10
	.loc 1 464 8
	bleu	a1,a5,.L86
	.loc 1 465 9 is_stmt 1
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL107:
	.loc 1 466 9
	.loc 1 466 16 is_stmt 0
	li	a0,-5
.LVL108:
.L84:
	.loc 1 504 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL109:
.L87:
	.cfi_restore_state
	.loc 1 468 26 is_stmt 1 discriminator 2
	addi	a4,a4,1
.LVL110:
	.loc 1 468 19 discriminator 1
	beq	a4,a2,.L88
.LVL111:
.L86:
	.loc 1 469 9
	.loc 1 469 43 is_stmt 0
	slli	a5,a4,2
	add	a5,a5,a4
	slli	a5,a5,2
	add	a5,a3,a5
	lw	a1,4(a5)
	.loc 1 469 12
	bne	a1,zero,.L87
	.loc 1 470 13 is_stmt 1
	.loc 1 470 25 is_stmt 0
	li	a2,-1431699456
	or	a4,a4,a2
.LVL112:
	.loc 1 470 21
	sw	a4,0(s1)
	.loc 1 471 13 is_stmt 1
	.loc 1 471 51 is_stmt 0
	li	a4,1
	sw	a4,4(a5)
	.loc 1 472 13 is_stmt 1
	.loc 1 472 57 is_stmt 0
	sw	zero,0(a5)
	.loc 1 473 13 is_stmt 1
	.loc 1 473 53 is_stmt 0
	sw	zero,12(a5)
	.loc 1 474 13 is_stmt 1
	.loc 1 474 54 is_stmt 0
	sw	zero,16(a5)
	.loc 1 475 13 is_stmt 1
.LVL113:
.L88:
	.loc 1 478 5
	.loc 1 478 19 is_stmt 0
	lbu	a5,200(a3)
	.loc 1 479 5
	lw	a0,0(sp)
	.loc 1 480 28
	lla	s1,sw_gpt_first_start
.LVL114:
	.loc 1 478 36
	addi	a5,a5,1
	andi	a5,a5,0xff
	sb	a5,200(a3)
	.loc 1 479 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL115:
	.loc 1 480 5
	.loc 1 480 28 is_stmt 0
	lbu	a5,sw_gpt_first_start
	.loc 1 480 8
	bne	a5,zero,.L89
	.loc 1 481 9 is_stmt 1
	.loc 1 481 13
	.loc 1 481 48 is_stmt 0
	lw	a0,gpt_lock_sleep_name+24
	call	hal_sleep_manager_set_sleep_handle
.LVL116:
	.loc 1 481 46 discriminator 1
	sb	a0,gpt_lock_sleep_handle+6,a5
.L89:
	.loc 1 481 11 is_stmt 1 discriminator 1
	.loc 1 483 5
	mv	a0,sp
	call	hal_nvic_save_and_set_interrupt_mask
.LVL117:
	.loc 1 486 5
	.loc 1 486 28 is_stmt 0
	lbu	a5,0(s1)
	.loc 1 486 8
	bne	a5,zero,.L90
	.loc 1 487 9 is_stmt 1
	.loc 1 488 9
	.loc 1 487 28 is_stmt 0
	li	a5,1
	.loc 1 488 24
	li	a0,5
	.loc 1 487 28
	sb	a5,0(s1)
	.loc 1 488 24
	call	gpt_get_context_index
.LVL118:
	mv	s1,a0
.LVL119:
	.loc 1 489 9 is_stmt 1
	.loc 1 489 24 is_stmt 0
	li	a0,6
	call	gpt_get_context_index
.LVL120:
	.loc 1 490 9 is_stmt 1
	.loc 1 490 32 is_stmt 0 discriminator 1
	or	a4,s1,a0
	li	a5,1
	bleu	a4,a5,.L91
	.loc 1 492 12 is_stmt 1
	lw	a0,0(sp)
.LVL121:
	call	hal_nvic_restore_interrupt_mask
.LVL122:
	.loc 1 493 12
	.loc 1 493 19 is_stmt 0
	li	a0,-2
	j	.L84
.LVL123:
.L91:
	.loc 1 495 9 is_stmt 1
	.loc 1 495 63 is_stmt 0
	lla	a5,g_gpt_context
	slli	s1,s1,4
.LVL124:
	add	s1,a5,s1
	lla	a4,sw_gpt_callback
	.loc 1 497 63
	slli	a0,a0,4
.LVL125:
	.loc 1 495 63
	sw	a4,4(s1)
	.loc 1 496 9 is_stmt 1
	.loc 1 497 63 is_stmt 0
	add	a5,a5,a0
	.loc 1 496 64
	sw	s0,8(s1)
	.loc 1 497 9 is_stmt 1
	.loc 1 497 63 is_stmt 0
	sw	a4,4(a5)
	.loc 1 498 9 is_stmt 1
	.loc 1 498 64 is_stmt 0
	lla	a4,sw_type_port.0+4
	sw	a4,8(a5)
	.loc 1 499 9 is_stmt 1
	call	gpt_nvic_register
.LVL126:
.L90:
	.loc 1 501 5
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL127:
	.loc 1 503 5
	.loc 1 503 12 is_stmt 0
	li	a0,0
	j	.L84
.LVL128:
.L92:
	.loc 1 461 16
	li	a0,-1
.LVL129:
	j	.L84
	.cfi_endproc
.LFE16:
	.size	hal_gpt_sw_get_timer, .-hal_gpt_sw_get_timer
	.section	.text.hal_gpt_sw_free_timer,"ax",@progbits
	.align	1
	.globl	hal_gpt_sw_free_timer
	.hidden	hal_gpt_sw_free_timer
	.type	hal_gpt_sw_free_timer, @function
hal_gpt_sw_free_timer:
.LFB17:
	.loc 1 507 1 is_stmt 1
	.cfi_startproc
.LVL130:
	.loc 1 508 5
	.loc 1 509 5
	.loc 1 510 5
	.loc 1 510 17 is_stmt 0
	li	a5,-1431699456
	and	a4,a0,a5
	.loc 1 510 8
	bne	a4,a5,.L99
	.loc 1 513 5 is_stmt 1
	.loc 1 513 11 is_stmt 0
	slli	a5,a0,16
	srli	a5,a5,16
.LVL131:
	.loc 1 514 5 is_stmt 1
	.loc 1 514 8 is_stmt 0
	li	a4,9
	.loc 1 511 16
	li	a0,-1
.LVL132:
	.loc 1 514 8
	bgtu	a5,a4,.L103
	.loc 1 517 5 is_stmt 1
	.loc 1 507 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	.cfi_offset 8, -8
	.loc 1 517 43
	slli	s0,a5,2
	add	s0,s0,a5
	.loc 1 507 1
	sw	s1,4(sp)
	.loc 1 517 43
	slli	s0,s0,2
	.cfi_offset 9, -12
	lla	s1,g_sw_gpt_notes
	add	s0,s1,s0
	lw	a4,4(s0)
	.loc 1 507 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 517 8
	li	a5,1
.LVL133:
	.loc 1 518 16
	li	a0,-3
	.loc 1 517 8
	bne	a4,a5,.L97
	.loc 1 520 5 is_stmt 1
	mv	a0,sp
	call	hal_nvic_save_and_set_interrupt_mask
.LVL134:
	.loc 1 521 5
	.loc 1 521 47 is_stmt 0
	sw	zero,4(s0)
	.loc 1 522 5 is_stmt 1
	.loc 1 522 19 is_stmt 0
	lbu	a5,200(s1)
	.loc 1 523 5
	lw	a0,0(sp)
	.loc 1 522 36
	addi	a5,a5,-1
	andi	a5,a5,0xff
	sb	a5,200(s1)
	.loc 1 523 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL135:
	.loc 1 524 5
	.loc 1 524 12 is_stmt 0
	li	a0,0
.L97:
	.loc 1 525 1
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL136:
.L99:
	.loc 1 511 16
	li	a0,-1
.LVL137:
	ret
.LVL138:
.L103:
	.loc 1 525 1
	ret
	.cfi_endproc
.LFE17:
	.size	hal_gpt_sw_free_timer, .-hal_gpt_sw_free_timer
	.section	.text.hal_gpt_sw_start_timer_ms,"ax",@progbits
	.align	1
	.globl	hal_gpt_sw_start_timer_ms
	.hidden	hal_gpt_sw_start_timer_ms
	.type	hal_gpt_sw_start_timer_ms, @function
hal_gpt_sw_start_timer_ms:
.LFB18:
	.loc 1 528 1 is_stmt 1
	.cfi_startproc
.LVL139:
	.loc 1 529 5
	.loc 1 529 12 is_stmt 0
	li	a4,0
	tail	sw_gpt_timer_start
.LVL140:
	.cfi_endproc
.LFE18:
	.size	hal_gpt_sw_start_timer_ms, .-hal_gpt_sw_start_timer_ms
	.section	.text.hal_gpt_sw_stop_timer_ms,"ax",@progbits
	.align	1
	.globl	hal_gpt_sw_stop_timer_ms
	.hidden	hal_gpt_sw_stop_timer_ms
	.type	hal_gpt_sw_stop_timer_ms, @function
hal_gpt_sw_stop_timer_ms:
.LFB19:
	.loc 1 533 1 is_stmt 1
	.cfi_startproc
.LVL141:
	.loc 1 534 5
	.loc 1 534 12 is_stmt 0
	li	a1,0
	tail	sw_gpt_timer_stop
.LVL142:
	.cfi_endproc
.LFE19:
	.size	hal_gpt_sw_stop_timer_ms, .-hal_gpt_sw_stop_timer_ms
	.section	.text.hal_gpt_sw_get_remaining_time_ms,"ax",@progbits
	.align	1
	.globl	hal_gpt_sw_get_remaining_time_ms
	.hidden	hal_gpt_sw_get_remaining_time_ms
	.type	hal_gpt_sw_get_remaining_time_ms, @function
hal_gpt_sw_get_remaining_time_ms:
.LFB20:
	.loc 1 538 1 is_stmt 1
	.cfi_startproc
.LVL143:
	.loc 1 539 5
	.loc 1 539 12 is_stmt 0
	li	a2,0
	tail	sw_gpt_get_remaining_time
.LVL144:
	.cfi_endproc
.LFE20:
	.size	hal_gpt_sw_get_remaining_time_ms, .-hal_gpt_sw_get_remaining_time_ms
	.section	.text.hal_gpt_sw_start_timer_us,"ax",@progbits
	.align	1
	.globl	hal_gpt_sw_start_timer_us
	.hidden	hal_gpt_sw_start_timer_us
	.type	hal_gpt_sw_start_timer_us, @function
hal_gpt_sw_start_timer_us:
.LFB21:
	.loc 1 544 1 is_stmt 1
	.cfi_startproc
.LVL145:
	.loc 1 545 5
	.loc 1 545 12 is_stmt 0
	li	a4,1
	tail	sw_gpt_timer_start
.LVL146:
	.cfi_endproc
.LFE21:
	.size	hal_gpt_sw_start_timer_us, .-hal_gpt_sw_start_timer_us
	.section	.text.hal_gpt_sw_stop_timer_us,"ax",@progbits
	.align	1
	.globl	hal_gpt_sw_stop_timer_us
	.hidden	hal_gpt_sw_stop_timer_us
	.type	hal_gpt_sw_stop_timer_us, @function
hal_gpt_sw_stop_timer_us:
.LFB22:
	.loc 1 550 1 is_stmt 1
	.cfi_startproc
.LVL147:
	.loc 1 551 5
	.loc 1 551 12 is_stmt 0
	li	a1,1
	tail	sw_gpt_timer_stop
.LVL148:
	.cfi_endproc
.LFE22:
	.size	hal_gpt_sw_stop_timer_us, .-hal_gpt_sw_stop_timer_us
	.section	.text.hal_gpt_sw_get_remaining_time_us,"ax",@progbits
	.align	1
	.globl	hal_gpt_sw_get_remaining_time_us
	.hidden	hal_gpt_sw_get_remaining_time_us
	.type	hal_gpt_sw_get_remaining_time_us, @function
hal_gpt_sw_get_remaining_time_us:
.LFB23:
	.loc 1 555 1 is_stmt 1
	.cfi_startproc
.LVL149:
	.loc 1 556 5
	.loc 1 556 12 is_stmt 0
	li	a2,1
	tail	sw_gpt_get_remaining_time
.LVL150:
	.cfi_endproc
.LFE23:
	.size	hal_gpt_sw_get_remaining_time_us, .-hal_gpt_sw_get_remaining_time_us
	.section	.sbss.sw_type_port.0,"aw",@nobits
	.align	2
	.type	sw_type_port.0, @object
	.size	sw_type_port.0, 8
sw_type_port.0:
	.zero	8
	.hidden	sw_gpt_first_start
	.globl	sw_gpt_first_start
	.section	.sbss.sw_gpt_first_start,"aw",@nobits
	.type	sw_gpt_first_start, @object
	.size	sw_gpt_first_start, 1
sw_gpt_first_start:
	.zero	1
	.hidden	g_sw_gpt_running_note
	.globl	g_sw_gpt_running_note
	.section	.sdata.g_sw_gpt_running_note,"aw"
	.align	2
	.type	g_sw_gpt_running_note, @object
	.size	g_sw_gpt_running_note, 2
g_sw_gpt_running_note:
	.ascii	"\n\n"
	.hidden	g_sw_gpt_notes
	.globl	g_sw_gpt_notes
	.section	.bss.g_sw_gpt_notes,"aw",@nobits
	.align	2
	.type	g_sw_gpt_notes, @object
	.size	g_sw_gpt_notes, 204
g_sw_gpt_notes:
	.zero	204
	.hidden	gpt_lock_sleep_handle
	.globl	gpt_lock_sleep_handle
	.section	.sbss.gpt_lock_sleep_handle,"aw",@nobits
	.align	2
	.type	gpt_lock_sleep_handle, @object
	.size	gpt_lock_sleep_handle, 7
gpt_lock_sleep_handle:
	.zero	7
	.hidden	gpt_lock_sleep_name
	.globl	gpt_lock_sleep_name
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"GPT0"
	.align	2
.LC1:
	.string	"GPT1"
	.align	2
.LC2:
	.string	"GPT2"
	.align	2
.LC3:
	.string	"GPT3"
	.align	2
.LC4:
	.string	"GPT4"
	.align	2
.LC5:
	.string	"GPT5"
	.align	2
.LC6:
	.string	"GPT6"
	.section	.data.gpt_lock_sleep_name,"aw"
	.align	2
	.type	gpt_lock_sleep_name, @object
	.size	gpt_lock_sleep_name, 28
gpt_lock_sleep_name:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpt.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 6 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 7 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager.h"
	.file 8 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt_internal.h"
	.file 9 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 10 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 11 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.file 12 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1333
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x28
	.4byte	.LASF222
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL53
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
	.uleb128 0x29
	.4byte	.LASF223
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0xc
	.2byte	0x128
	.byte	0x12
	.4byte	0xba
	.uleb128 0x1
	.4byte	.LASF4
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF5
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF6
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF7
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF8
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF9
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF10
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF11
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF12
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x1f
	.byte	0
	.uleb128 0x9
	.byte	0x1
	.byte	0x6
	.4byte	.LASF23
	.uleb128 0x9
	.byte	0x2
	.byte	0x5
	.4byte	.LASF24
	.uleb128 0x9
	.byte	0x4
	.byte	0x5
	.4byte	.LASF25
	.uleb128 0x9
	.byte	0x8
	.byte	0x5
	.4byte	.LASF26
	.uleb128 0xa
	.4byte	.LASF29
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0xec
	.uleb128 0x18
	.4byte	0xd6
	.uleb128 0x1d
	.4byte	0xe2
	.uleb128 0x9
	.byte	0x1
	.byte	0x8
	.4byte	.LASF27
	.uleb128 0x9
	.byte	0x2
	.byte	0x7
	.4byte	.LASF28
	.uleb128 0xa
	.4byte	.LASF30
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x110
	.uleb128 0x18
	.4byte	0xfa
	.uleb128 0x1d
	.4byte	0x106
	.uleb128 0x9
	.byte	0x4
	.byte	0x7
	.4byte	.LASF31
	.uleb128 0x2a
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0xd
	.4byte	0xe7
	.4byte	0x12e
	.uleb128 0xe
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x1d
	.4byte	0x11e
	.uleb128 0x18
	.4byte	0x12e
	.uleb128 0x10
	.byte	0x1c
	.byte	0x3
	.byte	0x2a
	.4byte	0x19c
	.uleb128 0x3
	.4byte	.LASF32
	.byte	0x3
	.byte	0x2b
	.byte	0x1d
	.4byte	0x10b
	.byte	0
	.uleb128 0x3
	.4byte	.LASF33
	.byte	0x3
	.byte	0x2c
	.byte	0x17
	.4byte	0x106
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF34
	.byte	0x3
	.byte	0x2d
	.byte	0x17
	.4byte	0x106
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF35
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x106
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF36
	.byte	0x3
	.byte	0x2f
	.byte	0x17
	.4byte	0x106
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF37
	.byte	0x3
	.byte	0x30
	.byte	0x1d
	.4byte	0x10b
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF38
	.byte	0x3
	.byte	0x31
	.byte	0x1d
	.4byte	0x10b
	.byte	0x18
	.byte	0
	.uleb128 0xa
	.4byte	.LASF39
	.byte	0x3
	.byte	0x32
	.byte	0x3
	.4byte	0x138
	.uleb128 0x10
	.byte	0x4
	.byte	0x3
	.byte	0x36
	.4byte	0x1e4
	.uleb128 0x2b
	.string	"EN"
	.byte	0x3
	.byte	0x37
	.byte	0x1e
	.4byte	0xe2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF40
	.byte	0x3
	.byte	0x38
	.byte	0x1e
	.4byte	0xe2
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF41
	.byte	0x3
	.byte	0x39
	.byte	0x1e
	.4byte	0xe2
	.byte	0x2
	.uleb128 0x3
	.4byte	.LASF42
	.byte	0x3
	.byte	0x3a
	.byte	0x24
	.4byte	0x133
	.byte	0x3
	.byte	0
	.uleb128 0x2c
	.byte	0x4
	.byte	0x3
	.byte	0x35
	.byte	0x5
	.4byte	0x204
	.uleb128 0x22
	.4byte	.LASF43
	.byte	0x3b
	.byte	0xb
	.4byte	0x1a8
	.uleb128 0x22
	.4byte	.LASF44
	.byte	0x3c
	.byte	0x1b
	.4byte	0x106
	.byte	0
	.uleb128 0x10
	.byte	0x20
	.byte	0x3
	.byte	0x34
	.4byte	0x275
	.uleb128 0x3
	.4byte	.LASF45
	.byte	0x3
	.byte	0x3d
	.byte	0x7
	.4byte	0x1e4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF46
	.byte	0x3
	.byte	0x3e
	.byte	0x17
	.4byte	0x106
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF47
	.byte	0x3
	.byte	0x3f
	.byte	0x17
	.4byte	0x106
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF48
	.byte	0x3
	.byte	0x40
	.byte	0x17
	.4byte	0x106
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF49
	.byte	0x3
	.byte	0x41
	.byte	0x1d
	.4byte	0x10b
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF50
	.byte	0x3
	.byte	0x42
	.byte	0x17
	.4byte	0x106
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF51
	.byte	0x3
	.byte	0x43
	.byte	0x17
	.4byte	0x106
	.byte	0x18
	.uleb128 0x3
	.4byte	.LASF52
	.byte	0x3
	.byte	0x44
	.byte	0x17
	.4byte	0x106
	.byte	0x1c
	.byte	0
	.uleb128 0xa
	.4byte	.LASF53
	.byte	0x3
	.byte	0x45
	.byte	0x3
	.4byte	0x204
	.uleb128 0xd
	.4byte	0xd6
	.4byte	0x291
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x19
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.2byte	0x459
	.4byte	0x2d5
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
	.byte	0x7
	.byte	0
	.uleb128 0x13
	.4byte	.LASF63
	.byte	0x4
	.2byte	0x463
	.byte	0x3
	.4byte	0x291
	.uleb128 0x19
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.2byte	0x466
	.4byte	0x2fc
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.4byte	.LASF66
	.byte	0x4
	.2byte	0x469
	.byte	0x3
	.4byte	0x2e2
	.uleb128 0x13
	.4byte	.LASF67
	.byte	0x5
	.2byte	0x143
	.byte	0x10
	.4byte	0x316
	.uleb128 0x14
	.4byte	0x31b
	.uleb128 0x2d
	.4byte	0x326
	.uleb128 0x4
	.4byte	0x326
	.byte	0
	.uleb128 0x2e
	.byte	0x4
	.uleb128 0x19
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.2byte	0x14c
	.4byte	0x342
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.4byte	.LASF70
	.byte	0x5
	.2byte	0x14f
	.byte	0x3
	.4byte	0x328
	.uleb128 0x19
	.byte	0x5
	.4byte	0x117
	.byte	0x5
	.2byte	0x153
	.4byte	0x38d
	.uleb128 0xf
	.4byte	.LASF71
	.sleb128 -7
	.uleb128 0xf
	.4byte	.LASF72
	.sleb128 -6
	.uleb128 0xf
	.4byte	.LASF73
	.sleb128 -5
	.uleb128 0xf
	.4byte	.LASF74
	.sleb128 -4
	.uleb128 0xf
	.4byte	.LASF75
	.sleb128 -3
	.uleb128 0xf
	.4byte	.LASF76
	.sleb128 -2
	.uleb128 0xf
	.4byte	.LASF77
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0
	.byte	0
	.uleb128 0x13
	.4byte	.LASF79
	.byte	0x5
	.2byte	0x15c
	.byte	0x3
	.4byte	0x34f
	.uleb128 0x19
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.2byte	0x160
	.4byte	0x3b4
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.4byte	.LASF82
	.byte	0x5
	.2byte	0x163
	.byte	0x3
	.4byte	0x39a
	.uleb128 0xa
	.4byte	.LASF83
	.byte	0x6
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0x9
	.byte	0x10
	.byte	0x4
	.4byte	.LASF84
	.uleb128 0x9
	.byte	0x1
	.byte	0x8
	.4byte	.LASF85
	.uleb128 0x1d
	.4byte	0x3d4
	.uleb128 0x14
	.4byte	0x3db
	.uleb128 0x11
	.byte	0x5
	.4byte	0x117
	.byte	0x7
	.byte	0x2d
	.byte	0xe
	.4byte	0x3ff
	.uleb128 0xf
	.4byte	.LASF86
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0
	.byte	0
	.uleb128 0xa
	.4byte	.LASF88
	.byte	0x7
	.byte	0x30
	.byte	0x3
	.4byte	0x3e5
	.uleb128 0x11
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x53
	.byte	0xe
	.4byte	0x42b
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x2
	.byte	0
	.uleb128 0xa
	.4byte	.LASF92
	.byte	0x8
	.byte	0x57
	.byte	0x3
	.4byte	0x40b
	.uleb128 0x11
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x71
	.byte	0xe
	.4byte	0x460
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0
	.uleb128 0x20
	.4byte	.LASF94
	.2byte	0x100
	.uleb128 0x20
	.4byte	.LASF95
	.2byte	0x200
	.uleb128 0x20
	.4byte	.LASF96
	.2byte	0x300
	.byte	0
	.uleb128 0x11
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x78
	.byte	0xe
	.4byte	0x47d
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF98
	.4byte	0x10000
	.byte	0
	.uleb128 0x11
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x7d
	.byte	0xe
	.4byte	0x4eb
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0xf
	.byte	0
	.uleb128 0x10
	.byte	0x8
	.byte	0x8
	.byte	0x90
	.4byte	0x50e
	.uleb128 0x3
	.4byte	.LASF115
	.byte	0x8
	.byte	0x91
	.byte	0x18
	.4byte	0x309
	.byte	0
	.uleb128 0x3
	.4byte	.LASF116
	.byte	0x8
	.byte	0x92
	.byte	0xb
	.4byte	0x326
	.byte	0x4
	.byte	0
	.uleb128 0xa
	.4byte	.LASF117
	.byte	0x8
	.byte	0x93
	.byte	0x3
	.4byte	0x4eb
	.uleb128 0x10
	.byte	0x10
	.byte	0x8
	.byte	0x95
	.4byte	0x557
	.uleb128 0x3
	.4byte	.LASF118
	.byte	0x8
	.byte	0x96
	.byte	0x1e
	.4byte	0x3b4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF119
	.byte	0x8
	.byte	0x97
	.byte	0x1c
	.4byte	0x50e
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF120
	.byte	0x8
	.byte	0x98
	.byte	0x1d
	.4byte	0x557
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF121
	.byte	0x8
	.byte	0x99
	.byte	0x1d
	.4byte	0x557
	.byte	0xd
	.byte	0
	.uleb128 0x9
	.byte	0x1
	.byte	0x2
	.4byte	.LASF122
	.uleb128 0x18
	.4byte	0x557
	.uleb128 0xa
	.4byte	.LASF123
	.byte	0x8
	.byte	0x9a
	.byte	0x3
	.4byte	0x51a
	.uleb128 0x11
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0xbe
	.byte	0xd
	.4byte	0x58f
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x2
	.byte	0
	.uleb128 0xa
	.4byte	.LASF127
	.byte	0x8
	.byte	0xc2
	.byte	0x2
	.4byte	0x56f
	.uleb128 0x10
	.byte	0x14
	.byte	0x8
	.byte	0xc4
	.4byte	0x5e5
	.uleb128 0x3
	.4byte	.LASF128
	.byte	0x8
	.byte	0xc5
	.byte	0xe
	.4byte	0xfa
	.byte	0
	.uleb128 0x3
	.4byte	.LASF129
	.byte	0x8
	.byte	0xc6
	.byte	0x1a
	.4byte	0x58f
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF130
	.byte	0x8
	.byte	0xc7
	.byte	0x13
	.4byte	0x42b
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF115
	.byte	0x8
	.byte	0xc8
	.byte	0x18
	.4byte	0x309
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF116
	.byte	0x8
	.byte	0xc9
	.byte	0xb
	.4byte	0x326
	.byte	0x10
	.byte	0
	.uleb128 0xa
	.4byte	.LASF131
	.byte	0x8
	.byte	0xca
	.byte	0x2
	.4byte	0x59b
	.uleb128 0x10
	.byte	0xcc
	.byte	0x8
	.byte	0xcc
	.4byte	0x614
	.uleb128 0x3
	.4byte	.LASF132
	.byte	0x8
	.byte	0xcd
	.byte	0xf
	.4byte	0x614
	.byte	0
	.uleb128 0x3
	.4byte	.LASF133
	.byte	0x8
	.byte	0xce
	.byte	0x9
	.4byte	0xd6
	.byte	0xc8
	.byte	0
	.uleb128 0xd
	.4byte	0x5e5
	.4byte	0x624
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0xa
	.4byte	.LASF134
	.byte	0x8
	.byte	0xcf
	.byte	0x2
	.4byte	0x5f1
	.uleb128 0x18
	.4byte	0x624
	.uleb128 0xd
	.4byte	0x563
	.4byte	0x645
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x23
	.4byte	.LASF135
	.byte	0xd2
	.byte	0x16
	.4byte	0x635
	.uleb128 0xd
	.4byte	0x3b4
	.4byte	0x660
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x23
	.4byte	.LASF136
	.byte	0xd3
	.byte	0x21
	.4byte	0x650
	.uleb128 0x11
	.byte	0x7
	.4byte	0x2d
	.byte	0x9
	.byte	0x2a
	.byte	0xe
	.4byte	0x715
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
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0xf
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
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF162
	.byte	0xff
	.byte	0
	.uleb128 0xd
	.4byte	0x3e0
	.4byte	0x725
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x24
	.4byte	.LASF163
	.byte	0x30
	.byte	0xd
	.4byte	0x715
	.uleb128 0x5
	.byte	0x3
	.4byte	gpt_lock_sleep_name
	.uleb128 0xd
	.4byte	0xd6
	.4byte	0x746
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x24
	.4byte	.LASF164
	.byte	0x31
	.byte	0x9
	.4byte	0x736
	.uleb128 0x5
	.byte	0x3
	.4byte	gpt_lock_sleep_handle
	.uleb128 0x21
	.4byte	.LASF165
	.2byte	0x1bf
	.byte	0x1c
	.4byte	0x630
	.uleb128 0x5
	.byte	0x3
	.4byte	g_sw_gpt_notes
	.uleb128 0x21
	.4byte	.LASF166
	.2byte	0x1c0
	.byte	0x9
	.4byte	0x281
	.uleb128 0x5
	.byte	0x3
	.4byte	g_sw_gpt_running_note
	.uleb128 0x21
	.4byte	.LASF167
	.2byte	0x1c1
	.byte	0xe
	.4byte	0x55e
	.uleb128 0x5
	.byte	0x3
	.4byte	sw_gpt_first_start
	.uleb128 0xc
	.4byte	.LASF168
	.byte	0x8
	.byte	0xec
	.byte	0x12
	.4byte	0x38d
	.4byte	0x7ad
	.uleb128 0x4
	.4byte	0xfa
	.uleb128 0x4
	.4byte	0x7ad
	.uleb128 0x4
	.4byte	0x42b
	.byte	0
	.uleb128 0x14
	.4byte	0xfa
	.uleb128 0xc
	.4byte	.LASF169
	.byte	0x8
	.byte	0xeb
	.byte	0x12
	.4byte	0x38d
	.4byte	0x7cd
	.uleb128 0x4
	.4byte	0xfa
	.uleb128 0x4
	.4byte	0x42b
	.byte	0
	.uleb128 0xc
	.4byte	.LASF170
	.byte	0x8
	.byte	0xea
	.byte	0x12
	.4byte	0x38d
	.4byte	0x7f7
	.uleb128 0x4
	.4byte	0xfa
	.uleb128 0x4
	.4byte	0xfa
	.uleb128 0x4
	.4byte	0x309
	.uleb128 0x4
	.4byte	0x326
	.uleb128 0x4
	.4byte	0x42b
	.byte	0
	.uleb128 0x15
	.4byte	.LASF173
	.byte	0x8
	.byte	0xe9
	.byte	0x6
	.4byte	0x809
	.uleb128 0x4
	.4byte	0x809
	.byte	0
	.uleb128 0x14
	.4byte	0x42b
	.uleb128 0xc
	.4byte	.LASF171
	.byte	0x7
	.byte	0x36
	.byte	0x1c
	.4byte	0x3ff
	.4byte	0x824
	.uleb128 0x4
	.4byte	0xd6
	.byte	0
	.uleb128 0xc
	.4byte	.LASF172
	.byte	0x7
	.byte	0x35
	.byte	0x1c
	.4byte	0x3ff
	.4byte	0x83a
	.uleb128 0x4
	.4byte	0xd6
	.byte	0
	.uleb128 0x15
	.4byte	.LASF174
	.byte	0x8
	.byte	0xd9
	.byte	0x6
	.4byte	0x851
	.uleb128 0x4
	.4byte	0x851
	.uleb128 0x4
	.4byte	0xfa
	.byte	0
	.uleb128 0x14
	.4byte	0x275
	.uleb128 0x15
	.4byte	.LASF175
	.byte	0xa
	.byte	0x3f
	.byte	0xd
	.4byte	0x868
	.uleb128 0x4
	.4byte	0xfa
	.byte	0
	.uleb128 0xc
	.4byte	.LASF176
	.byte	0x8
	.byte	0xdb
	.byte	0xa
	.4byte	0xfa
	.4byte	0x87e
	.uleb128 0x4
	.4byte	0xfa
	.byte	0
	.uleb128 0x15
	.4byte	.LASF177
	.byte	0xa
	.byte	0x3e
	.byte	0xd
	.4byte	0x890
	.uleb128 0x4
	.4byte	0x7ad
	.byte	0
	.uleb128 0x25
	.4byte	.LASF183
	.byte	0xd8
	.uleb128 0xc
	.4byte	.LASF178
	.byte	0x8
	.byte	0xdc
	.byte	0xa
	.4byte	0xfa
	.4byte	0x8ac
	.uleb128 0x4
	.4byte	0x851
	.byte	0
	.uleb128 0x15
	.4byte	.LASF179
	.byte	0x8
	.byte	0xda
	.byte	0x6
	.4byte	0x8c8
	.uleb128 0x4
	.4byte	0x851
	.uleb128 0x4
	.4byte	0xfa
	.uleb128 0x4
	.4byte	0xfa
	.byte	0
	.uleb128 0xc
	.4byte	.LASF180
	.byte	0x7
	.byte	0x37
	.byte	0x1c
	.4byte	0x3ff
	.4byte	0x8de
	.uleb128 0x4
	.4byte	0xd6
	.byte	0
	.uleb128 0x15
	.4byte	.LASF181
	.byte	0x8
	.byte	0xd7
	.byte	0x6
	.4byte	0x8f0
	.uleb128 0x4
	.4byte	0xfa
	.byte	0
	.uleb128 0xc
	.4byte	.LASF182
	.byte	0x7
	.byte	0x34
	.byte	0x9
	.4byte	0xd6
	.4byte	0x906
	.uleb128 0x4
	.4byte	0x3e0
	.byte	0
	.uleb128 0x25
	.4byte	.LASF184
	.byte	0xdd
	.uleb128 0xc
	.4byte	.LASF185
	.byte	0xb
	.byte	0x21
	.byte	0x8
	.4byte	0x326
	.4byte	0x92c
	.uleb128 0x4
	.4byte	0x326
	.uleb128 0x4
	.4byte	0x117
	.uleb128 0x4
	.4byte	0x3c1
	.byte	0
	.uleb128 0xc
	.4byte	.LASF186
	.byte	0x8
	.byte	0xe4
	.byte	0xa
	.4byte	0xfa
	.4byte	0x942
	.uleb128 0x4
	.4byte	0x2d5
	.byte	0
	.uleb128 0xb
	.4byte	.LASF189
	.2byte	0x22a
	.4byte	0x38d
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9a5
	.uleb128 0x6
	.4byte	.LASF187
	.2byte	0x22a
	.byte	0x3c
	.4byte	0xfa
	.4byte	.LLST51
	.uleb128 0x6
	.4byte	.LASF188
	.2byte	0x22a
	.byte	0x4e
	.4byte	0x7ad
	.4byte	.LLST52
	.uleb128 0x16
	.4byte	.LVL150
	.4byte	0x78d
	.uleb128 0x2
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF190
	.2byte	0x225
	.4byte	0x38d
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9eb
	.uleb128 0x6
	.4byte	.LASF187
	.2byte	0x225
	.byte	0x34
	.4byte	0xfa
	.4byte	.LLST50
	.uleb128 0x16
	.4byte	.LVL148
	.4byte	0x7b2
	.uleb128 0x2
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF191
	.2byte	0x21f
	.4byte	0x38d
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa88
	.uleb128 0x6
	.4byte	.LASF187
	.2byte	0x21f
	.byte	0x35
	.4byte	0xfa
	.4byte	.LLST46
	.uleb128 0x6
	.4byte	.LASF192
	.2byte	0x21f
	.byte	0x46
	.4byte	0xfa
	.4byte	.LLST47
	.uleb128 0x6
	.4byte	.LASF115
	.2byte	0x21f
	.byte	0x6a
	.4byte	0x309
	.4byte	.LLST48
	.uleb128 0x6
	.4byte	.LASF116
	.2byte	0x21f
	.byte	0x7a
	.4byte	0x326
	.4byte	.LLST49
	.uleb128 0x16
	.4byte	.LVL146
	.4byte	0x7cd
	.uleb128 0x2
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xc
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xd
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF193
	.2byte	0x219
	.4byte	0x38d
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xaeb
	.uleb128 0x6
	.4byte	.LASF187
	.2byte	0x219
	.byte	0x3c
	.4byte	0xfa
	.4byte	.LLST44
	.uleb128 0x6
	.4byte	.LASF188
	.2byte	0x219
	.byte	0x4e
	.4byte	0x7ad
	.4byte	.LLST45
	.uleb128 0x16
	.4byte	.LVL144
	.4byte	0x78d
	.uleb128 0x2
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF194
	.2byte	0x214
	.4byte	0x38d
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb31
	.uleb128 0x6
	.4byte	.LASF187
	.2byte	0x214
	.byte	0x34
	.4byte	0xfa
	.4byte	.LLST43
	.uleb128 0x16
	.4byte	.LVL142
	.4byte	0x7b2
	.uleb128 0x2
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF195
	.2byte	0x20f
	.4byte	0x38d
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbce
	.uleb128 0x6
	.4byte	.LASF187
	.2byte	0x20f
	.byte	0x35
	.4byte	0xfa
	.4byte	.LLST39
	.uleb128 0x6
	.4byte	.LASF196
	.2byte	0x20f
	.byte	0x46
	.4byte	0xfa
	.4byte	.LLST40
	.uleb128 0x6
	.4byte	.LASF115
	.2byte	0x20f
	.byte	0x6a
	.4byte	0x309
	.4byte	.LLST41
	.uleb128 0x6
	.4byte	.LASF116
	.2byte	0x20f
	.byte	0x7a
	.4byte	0x326
	.4byte	.LLST42
	.uleb128 0x16
	.4byte	.LVL140
	.4byte	0x7cd
	.uleb128 0x2
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
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
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xc
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xd
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF197
	.2byte	0x1fa
	.4byte	0x38d
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc34
	.uleb128 0x6
	.4byte	.LASF187
	.2byte	0x1fa
	.byte	0x31
	.4byte	0xfa
	.4byte	.LLST37
	.uleb128 0x1a
	.4byte	.LASF198
	.2byte	0x1fc
	.byte	0xe
	.4byte	0xfa
	.4byte	.LLST38
	.uleb128 0x1b
	.4byte	.LASF199
	.2byte	0x1fd
	.byte	0xe
	.4byte	0xfa
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x5
	.4byte	.LVL134
	.4byte	0x87e
	.4byte	0xc2a
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL135
	.4byte	0x856
	.byte	0
	.uleb128 0xb
	.4byte	.LASF200
	.2byte	0x1c5
	.4byte	0x38d
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd32
	.uleb128 0x6
	.4byte	.LASF187
	.2byte	0x1c5
	.byte	0x31
	.4byte	0x7ad
	.4byte	.LLST33
	.uleb128 0x30
	.string	"i"
	.byte	0x1
	.2byte	0x1c7
	.byte	0xe
	.4byte	0xfa
	.4byte	.LLST34
	.uleb128 0x1b
	.4byte	.LASF199
	.2byte	0x1c7
	.byte	0x11
	.4byte	0xfa
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1a
	.4byte	.LASF201
	.2byte	0x1c8
	.byte	0xe
	.4byte	0xfa
	.4byte	.LLST35
	.uleb128 0x1a
	.4byte	.LASF202
	.2byte	0x1c8
	.byte	0x1c
	.4byte	0xfa
	.4byte	.LLST36
	.uleb128 0x1b
	.4byte	.LASF203
	.2byte	0x1c9
	.byte	0x1a
	.4byte	0xd32
	.uleb128 0x5
	.byte	0x3
	.4byte	sw_type_port.0
	.uleb128 0x5
	.4byte	.LVL106
	.4byte	0x87e
	.4byte	0xcc1
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL107
	.4byte	0x856
	.uleb128 0x7
	.4byte	.LVL115
	.4byte	0x856
	.uleb128 0x7
	.4byte	.LVL116
	.4byte	0x8f0
	.uleb128 0x5
	.4byte	.LVL117
	.4byte	0x87e
	.4byte	0xcf0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL118
	.4byte	0x92c
	.4byte	0xd03
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x35
	.byte	0
	.uleb128 0x5
	.4byte	.LVL120
	.4byte	0x92c
	.4byte	0xd16
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x36
	.byte	0
	.uleb128 0x7
	.4byte	.LVL122
	.4byte	0x856
	.uleb128 0x7
	.4byte	.LVL126
	.4byte	0x890
	.uleb128 0x7
	.4byte	.LVL127
	.4byte	0x856
	.byte	0
	.uleb128 0xd
	.4byte	0x42b
	.4byte	0xd42
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xb
	.4byte	.LASF204
	.2byte	0x19a
	.4byte	0x38d
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xde2
	.uleb128 0x6
	.4byte	.LASF205
	.2byte	0x19a
	.byte	0x34
	.4byte	0x2d5
	.4byte	.LLST30
	.uleb128 0x1b
	.4byte	.LASF199
	.2byte	0x19c
	.byte	0xe
	.4byte	0xfa
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1a
	.4byte	.LASF198
	.2byte	0x19d
	.byte	0xe
	.4byte	0xfa
	.4byte	.LLST31
	.uleb128 0x26
	.4byte	0x131c
	.4byte	.LBB24
	.4byte	.LBE24-.LBB24
	.2byte	0x1a1
	.4byte	0xda7
	.uleb128 0x17
	.4byte	0x1329
	.4byte	.LLST32
	.byte	0
	.uleb128 0x5
	.4byte	.LVL94
	.4byte	0x92c
	.4byte	0xdbb
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL98
	.4byte	0x87e
	.4byte	0xdcf
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL100
	.4byte	0x856
	.uleb128 0x7
	.4byte	.LVL101
	.4byte	0x80e
	.byte	0
	.uleb128 0xb
	.4byte	.LASF206
	.2byte	0x189
	.4byte	0x38d
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe45
	.uleb128 0x27
	.string	"us"
	.2byte	0x189
	.4byte	0xfa
	.4byte	.LLST29
	.uleb128 0x5
	.4byte	.LVL90
	.4byte	0x8ac
	.4byte	0xe2a
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x42150200
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x3d
	.byte	0
	.uleb128 0x1e
	.4byte	.LVL91
	.4byte	0x83a
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x42150200
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF207
	.2byte	0x150
	.4byte	0x38d
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf05
	.uleb128 0x6
	.4byte	.LASF205
	.2byte	0x150
	.byte	0x38
	.4byte	0x2d5
	.4byte	.LLST24
	.uleb128 0x6
	.4byte	.LASF192
	.2byte	0x150
	.byte	0x4b
	.4byte	0xfa
	.4byte	.LLST25
	.uleb128 0x6
	.4byte	.LASF208
	.2byte	0x150
	.byte	0x71
	.4byte	0x342
	.4byte	.LLST26
	.uleb128 0x1b
	.4byte	.LASF199
	.2byte	0x152
	.byte	0xe
	.4byte	0xfa
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1a
	.4byte	.LASF198
	.2byte	0x153
	.byte	0xe
	.4byte	0xfa
	.4byte	.LLST27
	.uleb128 0x26
	.4byte	0x131c
	.4byte	.LBB22
	.4byte	.LBE22-.LBB22
	.2byte	0x157
	.4byte	0xeca
	.uleb128 0x17
	.4byte	0x1329
	.4byte	.LLST28
	.byte	0
	.uleb128 0x5
	.4byte	.LVL75
	.4byte	0x92c
	.4byte	0xede
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL80
	.4byte	0x824
	.uleb128 0x5
	.4byte	.LVL81
	.4byte	0x87e
	.4byte	0xefb
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x7
	.4byte	.LVL82
	.4byte	0x856
	.byte	0
	.uleb128 0xb
	.4byte	.LASF209
	.2byte	0x13c
	.4byte	0x38d
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf76
	.uleb128 0x27
	.string	"ms"
	.2byte	0x13c
	.4byte	0xfa
	.4byte	.LLST23
	.uleb128 0x5
	.4byte	.LVL70
	.4byte	0x8ac
	.4byte	0xf4d
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x42150100
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x40
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x5
	.4byte	.LVL71
	.4byte	0x868
	.4byte	0xf62
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x1e
	.4byte	.LVL72
	.4byte	0x83a
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x42150100
	.byte	0
	.byte	0
	.uleb128 0x12
	.4byte	.LASF210
	.byte	0xf6
	.4byte	0x38d
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x103b
	.uleb128 0x8
	.4byte	.LASF205
	.byte	0xf6
	.byte	0x38
	.4byte	0x2d5
	.4byte	.LLST18
	.uleb128 0x8
	.4byte	.LASF196
	.byte	0xf6
	.byte	0x4b
	.4byte	0xfa
	.4byte	.LLST19
	.uleb128 0x8
	.4byte	.LASF208
	.byte	0xf6
	.byte	0x71
	.4byte	0x342
	.4byte	.LLST20
	.uleb128 0x31
	.4byte	.LASF199
	.byte	0x1
	.byte	0xf9
	.byte	0xe
	.4byte	0xfa
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1c
	.4byte	.LASF198
	.byte	0xfa
	.4byte	0xfa
	.4byte	.LLST21
	.uleb128 0x1f
	.4byte	0x131c
	.4byte	.LBB20
	.4byte	.LBE20-.LBB20
	.byte	0xfe
	.4byte	0xff4
	.uleb128 0x17
	.4byte	0x1329
	.4byte	.LLST22
	.byte	0
	.uleb128 0x5
	.4byte	.LVL55
	.4byte	0x92c
	.4byte	0x1009
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x5
	.4byte	.LVL60
	.4byte	0x87e
	.4byte	0x101d
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x5
	.4byte	.LVL61
	.4byte	0x868
	.4byte	0x1031
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL62
	.4byte	0x856
	.byte	0
	.uleb128 0x12
	.4byte	.LASF211
	.byte	0xd4
	.4byte	0x38d
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10c9
	.uleb128 0x8
	.4byte	.LASF205
	.byte	0xd4
	.byte	0x3b
	.4byte	0x2d5
	.4byte	.LLST13
	.uleb128 0x8
	.4byte	.LASF115
	.byte	0xd5
	.byte	0x3f
	.4byte	0x309
	.4byte	.LLST14
	.uleb128 0x8
	.4byte	.LASF116
	.byte	0xd6
	.byte	0x32
	.4byte	0x326
	.4byte	.LLST15
	.uleb128 0x1c
	.4byte	.LASF198
	.byte	0xd9
	.4byte	0xfa
	.4byte	.LLST16
	.uleb128 0x1f
	.4byte	0x131c
	.4byte	.LBB18
	.4byte	.LBE18-.LBB18
	.byte	0xdd
	.4byte	0x10aa
	.uleb128 0x17
	.4byte	0x1329
	.4byte	.LLST17
	.byte	0
	.uleb128 0x5
	.4byte	.LVL44
	.4byte	0x92c
	.4byte	0x10bf
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x7
	.4byte	.LVL48
	.4byte	0x890
	.byte	0
	.uleb128 0x12
	.4byte	.LASF212
	.byte	0xbb
	.4byte	0x38d
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x111e
	.uleb128 0x8
	.4byte	.LASF205
	.byte	0xbb
	.byte	0x3c
	.4byte	0x2d5
	.4byte	.LLST10
	.uleb128 0x8
	.4byte	.LASF118
	.byte	0xbb
	.byte	0x60
	.4byte	0x111e
	.4byte	.LLST11
	.uleb128 0x1c
	.4byte	.LASF198
	.byte	0xbd
	.4byte	0xfa
	.4byte	.LLST12
	.uleb128 0x1e
	.4byte	.LVL37
	.4byte	0x92c
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x14
	.4byte	0x3b4
	.uleb128 0x12
	.4byte	.LASF213
	.byte	0xad
	.4byte	0x38d
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1168
	.uleb128 0x8
	.4byte	.LASF214
	.byte	0xad
	.byte	0x36
	.4byte	0xfa
	.4byte	.LLST8
	.uleb128 0x8
	.4byte	.LASF215
	.byte	0xad
	.byte	0x4c
	.4byte	0xfa
	.4byte	.LLST9
	.uleb128 0x32
	.4byte	.LASF216
	.byte	0x1
	.byte	0xad
	.byte	0x61
	.4byte	0x7ad
	.uleb128 0x1
	.byte	0x5c
	.byte	0
	.uleb128 0x12
	.4byte	.LASF217
	.byte	0x85
	.4byte	0x38d
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x11e6
	.uleb128 0x8
	.4byte	.LASF218
	.byte	0x85
	.byte	0x44
	.4byte	0x2fc
	.4byte	.LLST6
	.uleb128 0x8
	.4byte	.LASF219
	.byte	0x85
	.byte	0x5c
	.4byte	0x7ad
	.4byte	.LLST7
	.uleb128 0x5
	.4byte	.LVL25
	.4byte	0x8ac
	.4byte	0x11bf
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x42150100
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x40
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x7
	.4byte	.LVL26
	.4byte	0x896
	.uleb128 0x1e
	.4byte	.LVL30
	.4byte	0x8ac
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x42150200
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x3d
	.byte	0
	.byte	0
	.uleb128 0x12
	.4byte	.LASF220
	.byte	0x63
	.4byte	0x38d
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1286
	.uleb128 0x8
	.4byte	.LASF205
	.byte	0x63
	.byte	0x30
	.4byte	0x2d5
	.4byte	.LLST3
	.uleb128 0x1c
	.4byte	.LASF198
	.byte	0x65
	.4byte	0xfa
	.4byte	.LLST4
	.uleb128 0x1f
	.4byte	0x131c
	.4byte	.LBB16
	.4byte	.LBE16-.LBB16
	.byte	0x69
	.4byte	0x1237
	.uleb128 0x17
	.4byte	0x1329
	.4byte	.LLST5
	.byte	0
	.uleb128 0x5
	.4byte	.LVL12
	.4byte	0x92c
	.4byte	0x124b
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL17
	.4byte	0x90c
	.4byte	0x1269
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x40
	.byte	0
	.uleb128 0x5
	.4byte	.LVL18
	.4byte	0x8de
	.4byte	0x127c
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x7
	.4byte	.LVL19
	.4byte	0x8c8
	.byte	0
	.uleb128 0x12
	.4byte	.LASF221
	.byte	0x3b
	.4byte	0x38d
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x131c
	.uleb128 0x8
	.4byte	.LASF205
	.byte	0x3b
	.byte	0x2e
	.4byte	0x2d5
	.4byte	.LLST0
	.uleb128 0x1c
	.4byte	.LASF198
	.byte	0x3d
	.4byte	0xfa
	.4byte	.LLST1
	.uleb128 0x1f
	.4byte	0x131c
	.4byte	.LBB14
	.4byte	.LBE14-.LBB14
	.byte	0x41
	.4byte	0x12d7
	.uleb128 0x17
	.4byte	0x1329
	.4byte	.LLST2
	.byte	0
	.uleb128 0x5
	.4byte	.LVL1
	.4byte	0x92c
	.4byte	0x12eb
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL6
	.4byte	0x90c
	.4byte	0x1309
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x40
	.byte	0
	.uleb128 0x7
	.4byte	.LVL7
	.4byte	0x906
	.uleb128 0x7
	.4byte	.LVL8
	.4byte	0x8f0
	.byte	0
	.uleb128 0x33
	.4byte	.LASF224
	.byte	0x1
	.byte	0x32
	.byte	0xc
	.4byte	0x557
	.byte	0x1
	.uleb128 0x34
	.4byte	.LASF205
	.byte	0x1
	.byte	0x32
	.byte	0x31
	.4byte	0x2d5
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3
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
	.uleb128 0x4
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0xb
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
	.sleb128 18
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
	.uleb128 0xc
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
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
	.sleb128 18
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
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0x21
	.sleb128 10
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x21
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
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
	.uleb128 0x21
	.sleb128 8
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
	.uleb128 0xb
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
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x57
	.uleb128 0x21
	.sleb128 10
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 44
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x30
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
	.uleb128 0x31
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x32
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
	.uleb128 0x33
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x34
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
	.byte	0
	.section	.debug_loclists,"",@progbits
	.4byte	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.Ldebug_loc0:
.LLST51:
	.byte	0x6
	.4byte	.LVL149
	.byte	0x4
	.uleb128 .LVL149-.LVL149
	.uleb128 .LVL150-1-.LVL149
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL150-1-.LVL149
	.uleb128 .LFE23-.LVL149
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
.LLST52:
	.byte	0x6
	.4byte	.LVL149
	.byte	0x4
	.uleb128 .LVL149-.LVL149
	.uleb128 .LVL150-1-.LVL149
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL150-1-.LVL149
	.uleb128 .LFE23-.LVL149
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
.LLST50:
	.byte	0x6
	.4byte	.LVL147
	.byte	0x4
	.uleb128 .LVL147-.LVL147
	.uleb128 .LVL148-1-.LVL147
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL148-1-.LVL147
	.uleb128 .LFE22-.LVL147
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
.LLST46:
	.byte	0x6
	.4byte	.LVL145
	.byte	0x4
	.uleb128 .LVL145-.LVL145
	.uleb128 .LVL146-1-.LVL145
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL146-1-.LVL145
	.uleb128 .LFE21-.LVL145
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
.LLST47:
	.byte	0x6
	.4byte	.LVL145
	.byte	0x4
	.uleb128 .LVL145-.LVL145
	.uleb128 .LVL146-1-.LVL145
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL146-1-.LVL145
	.uleb128 .LFE21-.LVL145
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
.LLST48:
	.byte	0x6
	.4byte	.LVL145
	.byte	0x4
	.uleb128 .LVL145-.LVL145
	.uleb128 .LVL146-1-.LVL145
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL146-1-.LVL145
	.uleb128 .LFE21-.LVL145
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
.LLST49:
	.byte	0x6
	.4byte	.LVL145
	.byte	0x4
	.uleb128 .LVL145-.LVL145
	.uleb128 .LVL146-1-.LVL145
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL146-1-.LVL145
	.uleb128 .LFE21-.LVL145
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xd
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST44:
	.byte	0x6
	.4byte	.LVL143
	.byte	0x4
	.uleb128 .LVL143-.LVL143
	.uleb128 .LVL144-1-.LVL143
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL144-1-.LVL143
	.uleb128 .LFE20-.LVL143
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
.LLST45:
	.byte	0x6
	.4byte	.LVL143
	.byte	0x4
	.uleb128 .LVL143-.LVL143
	.uleb128 .LVL144-1-.LVL143
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL144-1-.LVL143
	.uleb128 .LFE20-.LVL143
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
.LLST43:
	.byte	0x6
	.4byte	.LVL141
	.byte	0x4
	.uleb128 .LVL141-.LVL141
	.uleb128 .LVL142-1-.LVL141
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL142-1-.LVL141
	.uleb128 .LFE19-.LVL141
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
.LLST39:
	.byte	0x6
	.4byte	.LVL139
	.byte	0x4
	.uleb128 .LVL139-.LVL139
	.uleb128 .LVL140-1-.LVL139
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL140-1-.LVL139
	.uleb128 .LFE18-.LVL139
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
.LLST40:
	.byte	0x6
	.4byte	.LVL139
	.byte	0x4
	.uleb128 .LVL139-.LVL139
	.uleb128 .LVL140-1-.LVL139
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL140-1-.LVL139
	.uleb128 .LFE18-.LVL139
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
.LLST41:
	.byte	0x6
	.4byte	.LVL139
	.byte	0x4
	.uleb128 .LVL139-.LVL139
	.uleb128 .LVL140-1-.LVL139
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL140-1-.LVL139
	.uleb128 .LFE18-.LVL139
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
.LLST42:
	.byte	0x6
	.4byte	.LVL139
	.byte	0x4
	.uleb128 .LVL139-.LVL139
	.uleb128 .LVL140-1-.LVL139
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL140-1-.LVL139
	.uleb128 .LFE18-.LVL139
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xd
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST37:
	.byte	0x6
	.4byte	.LVL130
	.byte	0x4
	.uleb128 .LVL130-.LVL130
	.uleb128 .LVL132-.LVL130
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL132-.LVL130
	.uleb128 .LVL136-.LVL130
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
	.uleb128 .LVL136-.LVL130
	.uleb128 .LVL137-.LVL130
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL137-.LVL130
	.uleb128 .LFE17-.LVL130
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
.LLST38:
	.byte	0x6
	.4byte	.LVL131
	.byte	0x4
	.uleb128 .LVL131-.LVL131
	.uleb128 .LVL133-.LVL131
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL133-.LVL131
	.uleb128 .LVL136-.LVL131
	.uleb128 0xe
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x40
	.byte	0x24
	.byte	0x40
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL138-.LVL131
	.uleb128 .LFE17-.LVL131
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST33:
	.byte	0x6
	.4byte	.LVL104
	.byte	0x4
	.uleb128 .LVL104-.LVL104
	.uleb128 .LVL105-.LVL104
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL105-.LVL104
	.uleb128 .LVL108-.LVL104
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL108-.LVL104
	.uleb128 .LVL109-.LVL104
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
	.uleb128 .LVL109-.LVL104
	.uleb128 .LVL114-.LVL104
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL114-.LVL104
	.uleb128 .LVL128-.LVL104
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
	.uleb128 .LVL128-.LVL104
	.uleb128 .LVL129-.LVL104
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL129-.LVL104
	.uleb128 .LFE16-.LVL104
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
.LLST34:
	.byte	0x8
	.4byte	.LVL109
	.uleb128 .LVL112-.LVL109
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST35:
	.byte	0x8
	.4byte	.LVL119
	.uleb128 .LVL124-.LVL119
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST36:
	.byte	0x6
	.4byte	.LVL120
	.byte	0x4
	.uleb128 .LVL120-.LVL120
	.uleb128 .LVL121-.LVL120
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL123-.LVL120
	.uleb128 .LVL125-.LVL120
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST30:
	.byte	0x6
	.4byte	.LVL93
	.byte	0x4
	.uleb128 .LVL93-.LVL93
	.uleb128 .LVL94-1-.LVL93
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL94-1-.LVL93
	.uleb128 .LVL96-.LVL93
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL96-.LVL93
	.uleb128 .LVL102-.LVL93
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
	.uleb128 .LVL102-.LVL93
	.uleb128 .LFE15-.LVL93
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST31:
	.byte	0x6
	.4byte	.LVL94
	.byte	0x4
	.uleb128 .LVL94-.LVL94
	.uleb128 .LVL97-.LVL94
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL97-.LVL94
	.uleb128 .LVL99-.LVL94
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL102-.LVL94
	.uleb128 .LVL103-.LVL94
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST32:
	.byte	0x6
	.4byte	.LVL94
	.byte	0x4
	.uleb128 .LVL94-.LVL94
	.uleb128 .LVL95-.LVL94
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL102-.LVL94
	.uleb128 .LFE15-.LVL94
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST29:
	.byte	0x6
	.4byte	.LVL88
	.byte	0x4
	.uleb128 .LVL88-.LVL88
	.uleb128 .LVL89-.LVL88
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL89-.LVL88
	.uleb128 .LVL92-.LVL88
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL92-.LVL88
	.uleb128 .LFE14-.LVL88
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0
.LLST24:
	.byte	0x6
	.4byte	.LVL74
	.byte	0x4
	.uleb128 .LVL74-.LVL74
	.uleb128 .LVL75-1-.LVL74
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL75-1-.LVL74
	.uleb128 .LVL77-.LVL74
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL77-.LVL74
	.uleb128 .LVL86-.LVL74
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
	.uleb128 .LVL86-.LVL74
	.uleb128 .LFE13-.LVL74
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST25:
	.byte	0x6
	.4byte	.LVL74
	.byte	0x4
	.uleb128 .LVL74-.LVL74
	.uleb128 .LVL75-1-.LVL74
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL75-1-.LVL74
	.uleb128 .LVL83-.LVL74
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL83-.LVL74
	.uleb128 .LVL85-.LVL74
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
	.uleb128 .LVL85-.LVL74
	.uleb128 .LFE13-.LVL74
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST26:
	.byte	0x6
	.4byte	.LVL74
	.byte	0x4
	.uleb128 .LVL74-.LVL74
	.uleb128 .LVL75-1-.LVL74
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL75-1-.LVL74
	.uleb128 .LVL84-.LVL74
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL84-.LVL74
	.uleb128 .LVL85-.LVL74
	.uleb128 0x2
	.byte	0x72
	.sleb128 -28
	.byte	0x4
	.uleb128 .LVL85-.LVL74
	.uleb128 .LFE13-.LVL74
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST27:
	.byte	0x6
	.4byte	.LVL75
	.byte	0x4
	.uleb128 .LVL75-.LVL75
	.uleb128 .LVL78-.LVL75
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL78-.LVL75
	.uleb128 .LVL79-.LVL75
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL86-.LVL75
	.uleb128 .LVL87-.LVL75
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST28:
	.byte	0x6
	.4byte	.LVL75
	.byte	0x4
	.uleb128 .LVL75-.LVL75
	.uleb128 .LVL76-.LVL75
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL86-.LVL75
	.uleb128 .LFE13-.LVL75
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST23:
	.byte	0x6
	.4byte	.LVL68
	.byte	0x4
	.uleb128 .LVL68-.LVL68
	.uleb128 .LVL69-.LVL68
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL69-.LVL68
	.uleb128 .LVL73-.LVL68
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL73-.LVL68
	.uleb128 .LFE12-.LVL68
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0
.LLST18:
	.byte	0x6
	.4byte	.LVL54
	.byte	0x4
	.uleb128 .LVL54-.LVL54
	.uleb128 .LVL55-1-.LVL54
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL55-1-.LVL54
	.uleb128 .LVL59-.LVL54
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL59-.LVL54
	.uleb128 .LVL66-.LVL54
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
	.uleb128 .LVL66-.LVL54
	.uleb128 .LFE11-.LVL54
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL54
	.byte	0x4
	.uleb128 .LVL54-.LVL54
	.uleb128 .LVL55-1-.LVL54
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL55-1-.LVL54
	.uleb128 .LVL63-.LVL54
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL63-.LVL54
	.uleb128 .LVL65-.LVL54
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
	.uleb128 .LVL65-.LVL54
	.uleb128 .LFE11-.LVL54
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST20:
	.byte	0x6
	.4byte	.LVL54
	.byte	0x4
	.uleb128 .LVL54-.LVL54
	.uleb128 .LVL55-1-.LVL54
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL55-1-.LVL54
	.uleb128 .LVL64-.LVL54
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL64-.LVL54
	.uleb128 .LVL65-.LVL54
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
	.uleb128 .LVL65-.LVL54
	.uleb128 .LFE11-.LVL54
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST21:
	.byte	0x6
	.4byte	.LVL55
	.byte	0x4
	.uleb128 .LVL55-.LVL55
	.uleb128 .LVL57-.LVL55
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL57-.LVL55
	.uleb128 .LVL58-.LVL55
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL66-.LVL55
	.uleb128 .LVL67-.LVL55
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST22:
	.byte	0x6
	.4byte	.LVL55
	.byte	0x4
	.uleb128 .LVL55-.LVL55
	.uleb128 .LVL56-.LVL55
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL66-.LVL55
	.uleb128 .LFE11-.LVL55
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL43
	.byte	0x4
	.uleb128 .LVL43-.LVL43
	.uleb128 .LVL44-1-.LVL43
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL44-1-.LVL43
	.uleb128 .LVL51-.LVL43
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL51-.LVL43
	.uleb128 .LVL52-.LVL43
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL52-.LVL43
	.uleb128 .LFE10-.LVL43
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL43
	.byte	0x4
	.uleb128 .LVL43-.LVL43
	.uleb128 .LVL44-1-.LVL43
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL44-1-.LVL43
	.uleb128 .LVL49-.LVL43
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL49-.LVL43
	.uleb128 .LVL52-.LVL43
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
	.uleb128 .LVL52-.LVL43
	.uleb128 .LFE10-.LVL43
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL43
	.byte	0x4
	.uleb128 .LVL43-.LVL43
	.uleb128 .LVL44-1-.LVL43
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL44-1-.LVL43
	.uleb128 .LVL50-.LVL43
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL50-.LVL43
	.uleb128 .LVL52-.LVL43
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
	.uleb128 .LVL52-.LVL43
	.uleb128 .LFE10-.LVL43
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST16:
	.byte	0x6
	.4byte	.LVL44
	.byte	0x4
	.uleb128 .LVL44-.LVL44
	.uleb128 .LVL46-.LVL44
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL46-.LVL44
	.uleb128 .LVL47-.LVL44
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL52-.LVL44
	.uleb128 .LVL53-.LVL44
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST17:
	.byte	0x6
	.4byte	.LVL44
	.byte	0x4
	.uleb128 .LVL44-.LVL44
	.uleb128 .LVL45-.LVL44
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL52-.LVL44
	.uleb128 .LFE10-.LVL44
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL36
	.byte	0x4
	.uleb128 .LVL36-.LVL36
	.uleb128 .LVL37-1-.LVL36
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL37-1-.LVL36
	.uleb128 .LVL40-.LVL36
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL40-.LVL36
	.uleb128 .LVL41-.LVL36
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
	.uleb128 .LVL41-.LVL36
	.uleb128 .LFE9-.LVL36
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL36
	.byte	0x4
	.uleb128 .LVL36-.LVL36
	.uleb128 .LVL37-1-.LVL36
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL37-1-.LVL36
	.uleb128 .LVL39-.LVL36
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL39-.LVL36
	.uleb128 .LVL41-.LVL36
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
	.uleb128 .LVL41-.LVL36
	.uleb128 .LFE9-.LVL36
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL37
	.byte	0x4
	.uleb128 .LVL37-.LVL37
	.uleb128 .LVL38-.LVL37
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL41-.LVL37
	.uleb128 .LVL42-.LVL37
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST8:
	.byte	0x6
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL33-.LVL31
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL33-.LVL31
	.uleb128 .LVL34-.LVL31
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
	.uleb128 .LVL34-.LVL31
	.uleb128 .LVL35-.LVL31
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL35-.LVL31
	.uleb128 .LFE8-.LVL31
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
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL32-.LVL31
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL32-.LVL31
	.uleb128 .LVL34-.LVL31
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
	.uleb128 .LVL34-.LVL31
	.uleb128 .LFE8-.LVL31
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL23-.LVL22
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL23-.LVL22
	.uleb128 .LVL28-.LVL22
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
	.uleb128 .LVL28-.LVL22
	.uleb128 .LVL29-.LVL22
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL29-.LVL22
	.uleb128 .LFE7-.LVL22
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL24-.LVL22
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL24-.LVL22
	.uleb128 .LVL27-.LVL22
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL27-.LVL22
	.uleb128 .LVL28-.LVL22
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
	.uleb128 .LVL28-.LVL22
	.uleb128 .LFE7-.LVL22
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL12-1-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL12-1-.LVL11
	.uleb128 .LVL16-.LVL11
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL16-.LVL11
	.uleb128 .LVL20-.LVL11
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
	.uleb128 .LVL20-.LVL11
	.uleb128 .LFE6-.LVL11
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL14-.LVL12
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL14-.LVL12
	.uleb128 .LVL15-.LVL12
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL20-.LVL12
	.uleb128 .LVL21-.LVL12
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL20-.LVL12
	.uleb128 .LFE6-.LVL12
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL1-1-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL1-1-.LVL0
	.uleb128 .LVL5-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL5-.LVL0
	.uleb128 .LVL9-.LVL0
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
	.uleb128 .LVL9-.LVL0
	.uleb128 .LFE5-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL3-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL3-.LVL1
	.uleb128 .LVL4-.LVL1
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL9-.LVL1
	.uleb128 .LVL10-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL2-.LVL1
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL9-.LVL1
	.uleb128 .LFE5-.LVL1
	.uleb128 0x1
	.byte	0x58
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0xac
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
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
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
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
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
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
.LLRL53:
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
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
	.byte	0x7
	.4byte	.LFB12
	.uleb128 .LFE12-.LFB12
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
	.byte	0x7
	.4byte	.LFB18
	.uleb128 .LFE18-.LFB18
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF211:
	.string	"hal_gpt_register_callback"
.LASF191:
	.string	"hal_gpt_sw_start_timer_us"
.LASF219:
	.string	"count"
.LASF189:
	.string	"hal_gpt_sw_get_remaining_time_us"
.LASF137:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF9:
	.string	"SPI_MST1_IRQn"
.LASF98:
	.string	"GPT_CLOCK_GATE"
.LASF74:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF113:
	.string	"GPT_DIVIDE_32"
.LASF18:
	.string	"SPI_MST0_IRQn"
.LASF83:
	.string	"size_t"
.LASF175:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF108:
	.string	"GPT_DIVIDE_10"
.LASF63:
	.string	"hal_gpt_port_t"
.LASF111:
	.string	"GPT_DIVIDE_13"
.LASF214:
	.string	"start_count"
.LASF222:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF183:
	.string	"gpt_nvic_register"
.LASF174:
	.string	"gpt_delay_time"
.LASF95:
	.string	"GPT_MODE_KEEP_GO"
.LASF188:
	.string	"remaing_time"
.LASF140:
	.string	"SLEEP_LOCK_TRNG"
.LASF97:
	.string	"GPT_CLOCK_UNGATE"
.LASF170:
	.string	"sw_gpt_timer_start"
.LASF2:
	.string	"long long unsigned int"
.LASF89:
	.string	"SW_GPT_MS_TYPE"
.LASF124:
	.string	"SW_GPT_NOTE_STATUS_OF_FREE"
.LASF6:
	.string	"QDEC_IRQn"
.LASF210:
	.string	"hal_gpt_start_timer_ms"
.LASF142:
	.string	"SLEEP_LOCK_IRTX"
.LASF5:
	.string	"LED_IRQn"
.LASF208:
	.string	"timer_type"
.LASF162:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF93:
	.string	"GPT_MODE_ONE_SHOT"
.LASF139:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF91:
	.string	"SW_GPT_MAX_TYPE"
.LASF35:
	.string	"GPT_WAKEUPMSK0"
.LASF36:
	.string	"GPT_WAKEUPMSK1"
.LASF26:
	.string	"long long int"
.LASF23:
	.string	"signed char"
.LASF116:
	.string	"user_data"
.LASF121:
	.string	"is_gpt_locked_sleep"
.LASF45:
	.string	"GPT_CON_UNION"
.LASF207:
	.string	"hal_gpt_start_timer_us"
.LASF120:
	.string	"has_initilized"
.LASF8:
	.string	"UART_IRQn"
.LASF51:
	.string	"GPT_COUNT"
.LASF25:
	.string	"long int"
.LASF145:
	.string	"SLEEP_LOCK_FLASH"
.LASF82:
	.string	"hal_gpt_running_status_t"
.LASF90:
	.string	"SW_GPT_US_TYPE"
.LASF3:
	.string	"unsigned int"
.LASF138:
	.string	"SLEEP_LOCK_AESOTF"
.LASF99:
	.string	"GPT_DIVIDE_1"
.LASF100:
	.string	"GPT_DIVIDE_2"
.LASF101:
	.string	"GPT_DIVIDE_3"
.LASF102:
	.string	"GPT_DIVIDE_4"
.LASF103:
	.string	"GPT_DIVIDE_5"
.LASF104:
	.string	"GPT_DIVIDE_6"
.LASF105:
	.string	"GPT_DIVIDE_7"
.LASF106:
	.string	"GPT_DIVIDE_8"
.LASF107:
	.string	"GPT_DIVIDE_9"
.LASF47:
	.string	"GPT_CLK"
.LASF123:
	.string	"gpt_context_t"
.LASF118:
	.string	"running_status"
.LASF46:
	.string	"GPT_CLR"
.LASF69:
	.string	"HAL_GPT_TIMER_TYPE_REPEAT"
.LASF39:
	.string	"GPT_REGISTER_GLOABL_T"
.LASF16:
	.string	"I3C0_IRQn"
.LASF133:
	.string	"used_timer_count"
.LASF201:
	.string	"gpt_ms_index"
.LASF212:
	.string	"hal_gpt_get_running_status"
.LASF52:
	.string	"GPT_COMPARE"
.LASF178:
	.string	"gpt_current_count"
.LASF15:
	.string	"EINT_IRQn"
.LASF17:
	.string	"I3C0_DMA_IRQn"
.LASF73:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF71:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF81:
	.string	"HAL_GPT_RUNNING"
.LASF31:
	.string	"long unsigned int"
.LASF62:
	.string	"HAL_GPT_MAX"
.LASF86:
	.string	"HAL_SLEEP_MANAGER_ERROR"
.LASF80:
	.string	"HAL_GPT_STOPPED"
.LASF182:
	.string	"hal_sleep_manager_set_sleep_handle"
.LASF33:
	.string	"GPT_IRQMSK0"
.LASF34:
	.string	"GPT_IRQMSK1"
.LASF28:
	.string	"short unsigned int"
.LASF141:
	.string	"SLEEP_LOCK_DMA"
.LASF153:
	.string	"SLEEP_LOCK_I3C1"
.LASF215:
	.string	"end_count"
.LASF115:
	.string	"callback"
.LASF114:
	.string	"GPT_DIVIDE_64"
.LASF176:
	.string	"gpt_convert_ms_to_32k_count"
.LASF186:
	.string	"gpt_get_context_index"
.LASF76:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF217:
	.string	"hal_gpt_get_free_run_count"
.LASF224:
	.string	"hal_gpt_is_port_valid"
.LASF117:
	.string	"gpt_callback_context_t"
.LASF152:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF202:
	.string	"gpt_us_index"
.LASF67:
	.string	"hal_gpt_callback_t"
.LASF220:
	.string	"hal_gpt_deinit"
.LASF223:
	.string	"IRQn"
.LASF72:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF179:
	.string	"gpt_start_free_run_timer"
.LASF197:
	.string	"hal_gpt_sw_free_timer"
.LASF119:
	.string	"callback_context"
.LASF78:
	.string	"HAL_GPT_STATUS_OK"
.LASF132:
	.string	"sw_gpt_timer"
.LASF11:
	.string	"GPT_IRQn"
.LASF209:
	.string	"hal_gpt_delay_ms"
.LASF4:
	.string	"SW_IRQn"
.LASF204:
	.string	"hal_gpt_stop_timer"
.LASF20:
	.string	"USB_IRQn"
.LASF146:
	.string	"SLEEP_LOCK_ESC"
.LASF94:
	.string	"GPT_MODE_REPEAT"
.LASF221:
	.string	"hal_gpt_init"
.LASF166:
	.string	"g_sw_gpt_running_note"
.LASF159:
	.string	"SLEEP_LOCK_I2C0"
.LASF206:
	.string	"hal_gpt_delay_us"
.LASF128:
	.string	"expire_count"
.LASF177:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF218:
	.string	"clock_source"
.LASF154:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF126:
	.string	"SW_GPT_NOTE_STATUS_OF_RUNING"
.LASF161:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF49:
	.string	"GPT_IRQ_STA"
.LASF12:
	.string	"UART_DMA_IRQn"
.LASF130:
	.string	"timer_port_type"
.LASF156:
	.string	"SLEEP_LOCK_UART0"
.LASF37:
	.string	"GPT_CLRSTA"
.LASF158:
	.string	"SLEEP_LOCK_UART2"
.LASF122:
	.string	"_Bool"
.LASF44:
	.string	"GPT_CON"
.LASF50:
	.string	"GPT_IRQ_ACK"
.LASF155:
	.string	"SLEEP_LOCK_USB"
.LASF24:
	.string	"short int"
.LASF135:
	.string	"g_gpt_context"
.LASF13:
	.string	"PMU_IRQn"
.LASF150:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF14:
	.string	"MCU_DMA_IRQn"
.LASF165:
	.string	"g_sw_gpt_notes"
.LASF131:
	.string	"sw_gpt_note_t"
.LASF203:
	.string	"sw_type_port"
.LASF171:
	.string	"hal_sleep_manager_unlock_sleep"
.LASF75:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF43:
	.string	"GPT_CON_CELLS"
.LASF53:
	.string	"GPT_REGISTER_T"
.LASF127:
	.string	"sw_gpt_note_status_t"
.LASF134:
	.string	"sw_gpt_add_note_t"
.LASF64:
	.string	"HAL_GPT_CLOCK_SOURCE_32K"
.LASF48:
	.string	"GPT_IRQ_EN"
.LASF30:
	.string	"uint32_t"
.LASF173:
	.string	"sw_gpt_callback"
.LASF216:
	.string	"duration_count"
.LASF84:
	.string	"long double"
.LASF85:
	.string	"char"
.LASF92:
	.string	"sw_gpt_type_t"
.LASF109:
	.string	"GPT_DIVIDE_11"
.LASF110:
	.string	"GPT_DIVIDE_12"
.LASF181:
	.string	"gpt_reset_default_timer"
.LASF169:
	.string	"sw_gpt_timer_stop"
.LASF112:
	.string	"GPT_DIVIDE_16"
.LASF19:
	.string	"IRQ_GEN_IRQn"
.LASF172:
	.string	"hal_sleep_manager_lock_sleep"
.LASF164:
	.string	"gpt_lock_sleep_handle"
.LASF198:
	.string	"index"
.LASF38:
	.string	"GPT_WCOMPSTA"
.LASF42:
	.string	"RESERVED"
.LASF40:
	.string	"MODE"
.LASF29:
	.string	"uint8_t"
.LASF213:
	.string	"hal_gpt_get_duration_count"
.LASF125:
	.string	"SW_GPT_NOTE_STATUS_OF_ALLOC"
.LASF65:
	.string	"HAL_GPT_CLOCK_SOURCE_1M"
.LASF21:
	.string	"BT_IRQn"
.LASF41:
	.string	"SW_CG"
.LASF68:
	.string	"HAL_GPT_TIMER_TYPE_ONE_SHOT"
.LASF88:
	.string	"hal_sleep_manager_status_t"
.LASF61:
	.string	"HAL_GPT_MAX_PORT"
.LASF149:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF27:
	.string	"unsigned char"
.LASF87:
	.string	"HAL_SLEEP_MANAGER_OK"
.LASF163:
	.string	"gpt_lock_sleep_name"
.LASF194:
	.string	"hal_gpt_sw_stop_timer_ms"
.LASF143:
	.string	"SLEEP_LOCK_IRRX"
.LASF77:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF32:
	.string	"GPT_IRQSTA"
.LASF196:
	.string	"timeout_time_ms"
.LASF157:
	.string	"SLEEP_LOCK_UART1"
.LASF168:
	.string	"sw_gpt_get_remaining_time"
.LASF184:
	.string	"gpt_open_clock_source"
.LASF205:
	.string	"gpt_port"
.LASF185:
	.string	"memset"
.LASF199:
	.string	"mask"
.LASF129:
	.string	"status"
.LASF151:
	.string	"SLEEP_LOCK_DCXO"
.LASF54:
	.string	"HAL_GPT_0"
.LASF55:
	.string	"HAL_GPT_1"
.LASF160:
	.string	"SLEEP_LOCK_APP"
.LASF57:
	.string	"HAL_GPT_3"
.LASF58:
	.string	"HAL_GPT_4"
.LASF59:
	.string	"HAL_GPT_5"
.LASF192:
	.string	"timeout_time_us"
.LASF96:
	.string	"GPT_MODE_FREE_RUN"
.LASF147:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF148:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF167:
	.string	"sw_gpt_first_start"
.LASF187:
	.string	"handle"
.LASF60:
	.string	"HAL_GPT_6"
.LASF56:
	.string	"HAL_GPT_2"
.LASF195:
	.string	"hal_gpt_sw_start_timer_ms"
.LASF190:
	.string	"hal_gpt_sw_stop_timer_us"
.LASF193:
	.string	"hal_gpt_sw_get_remaining_time_ms"
.LASF10:
	.string	"RTC_IRQn"
.LASF144:
	.string	"SLEEP_LOCK_AIO"
.LASF200:
	.string	"hal_gpt_sw_get_timer"
.LASF70:
	.string	"hal_gpt_timer_type_t"
.LASF7:
	.string	"KEYSCAN_IRQn"
.LASF180:
	.string	"hal_sleep_manager_release_sleep_handle"
.LASF136:
	.string	"gpt_running_state"
.LASF66:
	.string	"hal_gpt_clock_source_t"
.LASF79:
	.string	"hal_gpt_status_t"
.LASF22:
	.string	"IRQ_NUMBER_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_gpt.c"
.LASF1:
	.string	"/workdir/airoha/risc-v"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
