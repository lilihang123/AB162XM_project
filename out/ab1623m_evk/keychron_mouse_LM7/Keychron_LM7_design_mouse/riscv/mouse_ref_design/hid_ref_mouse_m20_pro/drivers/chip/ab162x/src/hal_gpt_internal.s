	.file	"hal_gpt_internal.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_gpt_internal.c"
	.section	.text.gpt_get_context_index,"ax",@progbits
	.align	1
	.globl	gpt_get_context_index
	.hidden	gpt_get_context_index
	.type	gpt_get_context_index, @function
gpt_get_context_index:
.LFB4:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_gpt_internal.c"
	.loc 1 56 1
	.cfi_startproc
.LVL0:
	.loc 1 57 5
	.loc 1 59 5
	.loc 1 59 19 discriminator 1
	.loc 1 60 9
	.loc 1 60 12 is_stmt 0
	li	a4,5
	.loc 1 56 1
	mv	a5,a0
	.loc 1 60 12
	beq	a0,a4,.L3
	.loc 1 59 25 is_stmt 1 discriminator 2
.LVL1:
	.loc 1 59 19 discriminator 1
	.loc 1 60 9
	.loc 1 60 12 is_stmt 0
	li	a4,6
	.loc 1 64 12
	li	a0,255
.LVL2:
	.loc 1 60 12
	bne	a5,a4,.L1
	.loc 1 59 25 discriminator 2
	li	a0,1
	ret
.LVL3:
.L3:
	.loc 1 59 12
	li	a0,0
.LVL4:
.L1:
	.loc 1 65 1
	ret
	.cfi_endproc
.LFE4:
	.size	gpt_get_context_index, .-gpt_get_context_index
	.section	.text.gpt_interrupt_handler,"ax",@progbits
	.align	1
	.globl	gpt_interrupt_handler
	.hidden	gpt_interrupt_handler
	.type	gpt_interrupt_handler, @function
gpt_interrupt_handler:
.LFB13:
	.loc 1 153 1 is_stmt 1
	.cfi_startproc
.LVL5:
	.loc 1 154 5
	.loc 1 156 5
	.loc 1 157 5
	.loc 1 159 5
	.loc 1 161 5
	.loc 1 161 19 discriminator 1
	.loc 1 153 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 161 12
	li	s1,0
	.loc 1 182 54
	lla	s0,g_gpt_context
.LVL6:
.L9:
	.loc 1 162 9 is_stmt 1
	.loc 1 162 17 is_stmt 0
	mv	a0,s1
	call	gpt_get_context_index
.LVL7:
	.loc 1 163 9 is_stmt 1
	.loc 1 163 12 is_stmt 0
	li	a3,1
	bgtu	a0,a3,.L7
	.loc 1 168 9 is_stmt 1
	.loc 1 168 18 is_stmt 0
	li	a4,1108672512
	slli	a5,s1,8
	add	a5,a5,a4
	.loc 1 168 62
	lw	a4,16(a5)
	.loc 1 168 15
	sw	a4,0(sp)
	.loc 1 169 9 is_stmt 1
	.loc 1 169 63 is_stmt 0
	lw	a4,12(a5)
	.loc 1 169 16
	sw	a4,4(sp)
	.loc 1 173 9 is_stmt 1
	.loc 1 173 20 is_stmt 0
	lw	a4,0(sp)
	andi	a4,a4,1
	.loc 1 173 12
	beq	a4,zero,.L7
	.loc 1 173 38 discriminator 1
	lw	a4,4(sp)
	andi	a4,a4,1
	.loc 1 173 27 discriminator 1
	beq	a4,zero,.L7
	.loc 1 175 13 is_stmt 1
	.loc 1 182 54 is_stmt 0
	slli	a0,a0,4
.LVL8:
	add	a0,s0,a0
	.loc 1 175 72
	sw	a3,20(a5)
	.loc 1 182 13 is_stmt 1
	.loc 1 182 54 is_stmt 0
	lw	a5,4(a0)
	.loc 1 182 16
	beq	a5,zero,.L7
	.loc 1 183 17 is_stmt 1
	lw	a0,8(a0)
	jalr	a5
.LVL9:
.L7:
	.loc 1 161 40 discriminator 2
	addi	s1,s1,1
.LVL10:
	.loc 1 161 19 discriminator 1
	li	a5,7
	bne	s1,a5,.L9
	.loc 1 190 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
.LVL11:
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE13:
	.size	gpt_interrupt_handler, .-gpt_interrupt_handler
	.section	.text.gpt_current_count,"ax",@progbits
	.align	1
	.globl	gpt_current_count
	.hidden	gpt_current_count
	.type	gpt_current_count, @function
gpt_current_count:
.LFB5:
	.loc 1 68 1 is_stmt 1
	.cfi_startproc
.LVL12:
	.loc 1 69 5
	.loc 1 69 15 is_stmt 0
	lw	a0,24(a0)
.LVL13:
	.loc 1 71 1
	ret
	.cfi_endproc
.LFE5:
	.size	gpt_current_count, .-gpt_current_count
	.globl	__udivsi3
	.section	.text.gpt_convert_ms_to_32k_count,"ax",@progbits
	.align	1
	.globl	gpt_convert_ms_to_32k_count
	.hidden	gpt_convert_ms_to_32k_count
	.type	gpt_convert_ms_to_32k_count, @function
gpt_convert_ms_to_32k_count:
.LFB6:
	.loc 1 74 1 is_stmt 1
	.cfi_startproc
.LVL14:
	.loc 1 75 5
	.loc 1 74 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 75 37
	slli	a5,a0,3
	.loc 1 74 1
	sw	s0,8(sp)
	.loc 1 75 43
	li	a1,10
	.cfi_offset 8, -8
	.loc 1 74 1
	mv	s0,a0
	.loc 1 75 43
	sub	a0,a5,a0
.LVL15:
	.loc 1 74 1
	sw	ra,12(sp)
	sw	s1,4(sp)
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 75 43
	sw	a5,0(sp)
	call	__udivsi3
.LVL16:
	mv	s1,a0
	.loc 1 75 53
	slli	a0,s0,1
	add	a0,a0,s0
	.loc 1 75 59
	li	a1,100
	slli	a0,a0,1
	call	__udivsi3
.LVL17:
	.loc 1 75 76
	lw	a5,0(sp)
	.loc 1 75 48
	add	s1,s1,a0
	.loc 1 75 27
	slli	s0,s0,5
.LVL18:
	.loc 1 75 76
	li	a1,1000
	mv	a0,a5
	call	__udivsi3
.LVL19:
	.loc 1 75 48
	add	s0,s1,s0
	.loc 1 76 1
	lw	ra,12(sp)
	.cfi_restore 1
	add	a0,s0,a0
	lw	s0,8(sp)
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE6:
	.size	gpt_convert_ms_to_32k_count, .-gpt_convert_ms_to_32k_count
	.section	.text.gpt_open_clock_source,"ax",@progbits
	.align	1
	.globl	gpt_open_clock_source
	.hidden	gpt_open_clock_source
	.type	gpt_open_clock_source, @function
gpt_open_clock_source:
.LFB7:
	.loc 1 80 1 is_stmt 1
	.cfi_startproc
	.loc 1 86 1
	ret
	.cfi_endproc
.LFE7:
	.size	gpt_open_clock_source, .-gpt_open_clock_source
	.section	.text.gpt_start_free_run_timer,"ax",@progbits
	.align	1
	.globl	gpt_start_free_run_timer
	.hidden	gpt_start_free_run_timer
	.type	gpt_start_free_run_timer, @function
gpt_start_free_run_timer:
.LFB8:
	.loc 1 90 1
	.cfi_startproc
.LVL20:
	.loc 1 91 5
	.loc 1 93 5
	.loc 1 93 33 is_stmt 0
	or	a1,a1,a2
.LVL21:
	.loc 1 93 18
	sw	a1,8(a0)
	.loc 1 96 5 is_stmt 1
	.loc 1 96 32 is_stmt 0
	li	a5,769
	sw	a5,0(a0)
	.loc 1 98 1
	ret
	.cfi_endproc
.LFE8:
	.size	gpt_start_free_run_timer, .-gpt_start_free_run_timer
	.section	.text.gpt_delay_time,"ax",@progbits
	.align	1
	.globl	gpt_delay_time
	.hidden	gpt_delay_time
	.type	gpt_delay_time, @function
gpt_delay_time:
.LFB9:
	.loc 1 101 1 is_stmt 1
	.cfi_startproc
.LVL22:
	.loc 1 102 5
	.loc 1 103 5
	.loc 1 104 5
	.loc 1 105 5
.LBB10:
.LBB11:
	.loc 1 69 5
	.loc 1 69 15 is_stmt 0
	lw	a4,24(a0)
.LVL23:
.LBE11:
.LBE10:
	.loc 1 107 5 is_stmt 1
	.loc 1 107 18
.L27:
	.loc 1 108 9
.LBB12:
.LBB13:
	.loc 1 69 5
	.loc 1 69 15 is_stmt 0
	lw	a5,24(a0)
.LVL24:
.LBE13:
.LBE12:
	.loc 1 110 9 is_stmt 1
	.loc 1 113 13
	.loc 1 107 18
	.loc 1 113 19 is_stmt 0
	sub	a5,a5,a4
.LVL25:
	.loc 1 107 18
	bgeu	a1,a5,.L27
	.loc 1 116 1
	ret
	.cfi_endproc
.LFE9:
	.size	gpt_delay_time, .-gpt_delay_time
	.section	.text.gpt_reset_default_timer,"ax",@progbits
	.align	1
	.globl	gpt_reset_default_timer
	.hidden	gpt_reset_default_timer
	.type	gpt_reset_default_timer, @function
gpt_reset_default_timer:
.LFB10:
	.loc 1 121 1 is_stmt 1
	.cfi_startproc
.LVL26:
	.loc 1 122 5
	.loc 1 122 37 is_stmt 0
	li	a5,4329472
	addi	a5,a5,1280
	add	a5,a0,a5
	slli	a5,a5,8
	.loc 1 122 70
	sw	zero,12(a5)
	.loc 1 123 5 is_stmt 1
	.loc 1 124 67 is_stmt 0
	li	a4,1
	.loc 1 123 81
	sw	zero,0(a5)
	.loc 1 124 5 is_stmt 1
	.loc 1 126 60 is_stmt 0 discriminator 1
	li	a2,1108676608
	.loc 1 124 67
	sw	a4,4(a5)
	.loc 1 126 5 is_stmt 1
	.loc 1 126 60 is_stmt 0 discriminator 1
	addi	a2,a2,-1024
	.loc 1 126 78 discriminator 1
	sll	a4,a4,a0
.L30:
	.loc 1 126 12 is_stmt 1 discriminator 1
	.loc 1 126 60 is_stmt 0 discriminator 1
	lw	a3,20(a2)
	.loc 1 126 73 discriminator 1
	and	a3,a3,a4
	.loc 1 126 12 discriminator 1
	bne	a3,zero,.L30
	.loc 1 127 5 is_stmt 1
	.loc 1 127 67 is_stmt 0
	li	a4,16
	sw	a4,8(a5)
	.loc 1 128 5 is_stmt 1
	.loc 1 128 71 is_stmt 0
	li	a4,1
	sw	a4,20(a5)
	.loc 1 129 5 is_stmt 1
	.loc 1 129 71 is_stmt 0
	li	a4,-1
	sw	a4,28(a5)
	.loc 1 131 1
	ret
	.cfi_endproc
.LFE10:
	.size	gpt_reset_default_timer, .-gpt_reset_default_timer
	.section	.text.gpt_save_and_mask_interrupt,"ax",@progbits
	.align	1
	.globl	gpt_save_and_mask_interrupt
	.hidden	gpt_save_and_mask_interrupt
	.type	gpt_save_and_mask_interrupt, @function
gpt_save_and_mask_interrupt:
.LFB11:
	.loc 1 136 1 is_stmt 1
	.cfi_startproc
.LVL27:
	.loc 1 137 5
	.loc 1 139 5
	.loc 1 139 15 is_stmt 0
	lw	a5,12(a0)
	.loc 1 136 1
	addi	sp,sp,-4
	.cfi_def_cfa_offset 4
	.loc 1 139 10
	sw	a5,0(sp)
	.loc 1 141 5 is_stmt 1
	.loc 1 141 8 is_stmt 0
	lw	a5,12(a0)
	.loc 1 141 21
	andi	a5,a5,-2
	sw	a5,12(a0)
	.loc 1 143 5 is_stmt 1
	.loc 1 143 12 is_stmt 0
	lw	a0,0(sp)
.LVL28:
	.loc 1 144 1
	addi	sp,sp,4
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	gpt_save_and_mask_interrupt, .-gpt_save_and_mask_interrupt
	.section	.text.gpt_restore_interrupt,"ax",@progbits
	.align	1
	.globl	gpt_restore_interrupt
	.hidden	gpt_restore_interrupt
	.type	gpt_restore_interrupt, @function
gpt_restore_interrupt:
.LFB12:
	.loc 1 147 1 is_stmt 1
	.cfi_startproc
.LVL29:
	.loc 1 148 5
	.loc 1 148 21 is_stmt 0
	sw	a1,12(a0)
	.loc 1 149 1
	ret
	.cfi_endproc
.LFE12:
	.size	gpt_restore_interrupt, .-gpt_restore_interrupt
	.section	.text.gpt_nvic_register,"ax",@progbits
	.align	1
	.globl	gpt_nvic_register
	.hidden	gpt_nvic_register
	.type	gpt_nvic_register, @function
gpt_nvic_register:
.LFB14:
	.loc 1 195 1 is_stmt 1
	.cfi_startproc
	.loc 1 196 5
	.loc 1 198 5
	.loc 1 195 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 198 17
	lla	s0,is_init.0
	.loc 1 198 8
	lbu	a5,0(s0)
	.loc 1 195 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 198 8
	bne	a5,zero,.L35
	.loc 1 199 9 is_stmt 1
	li	a0,20
	call	hal_nvic_disable_irq
.LVL30:
	.loc 1 200 9
	lla	a1,gpt_interrupt_handler
	li	a0,20
	call	hal_nvic_register_isr_handler
.LVL31:
	.loc 1 201 9
	li	a0,20
	call	hal_nvic_enable_irq
.LVL32:
	.loc 1 202 9
	.loc 1 202 17 is_stmt 0
	li	a5,1
	sb	a5,0(s0)
.L35:
	.loc 1 205 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE14:
	.size	gpt_nvic_register, .-gpt_nvic_register
	.section	.text.sw_gpt_find_the_next_expire_time,"ax",@progbits
	.align	1
	.globl	sw_gpt_find_the_next_expire_time
	.hidden	sw_gpt_find_the_next_expire_time
	.type	sw_gpt_find_the_next_expire_time, @function
sw_gpt_find_the_next_expire_time:
.LFB15:
	.loc 1 213 1 is_stmt 1
	.cfi_startproc
.LVL33:
	.loc 1 214 5
	.loc 1 215 5
	.loc 1 216 5
	.loc 1 216 19 discriminator 1
	.loc 1 213 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 219 16
	li	t0,-2147483648
	.loc 1 213 1
	sw	s0,8(sp)
	sw	s1,4(sp)
	.cfi_offset 8, -4
	.cfi_offset 9, -8
	.loc 1 213 1
	sw	a2,0(sp)
	lla	a4,g_sw_gpt_notes
	.loc 1 215 46
	li	t2,10
	.loc 1 215 14
	li	t1,-1
	.loc 1 216 12
	li	a5,0
	.loc 1 217 12
	li	s1,2
	.loc 1 219 16
	addi	t0,t0,-2
	.loc 1 216 19 discriminator 1
	li	s0,10
.LVL34:
.L41:
	.loc 1 217 9 is_stmt 1
	.loc 1 217 12 is_stmt 0
	lw	a2,4(a4)
	bne	a2,s1,.L39
	.loc 1 217 85 discriminator 1
	lw	a2,8(a4)
	bne	a2,a3,.L39
	.loc 1 218 13 is_stmt 1
	.loc 1 218 24 is_stmt 0
	lw	a2,0(a4)
	sub	a2,a2,a0
.LVL35:
	.loc 1 219 13 is_stmt 1
	.loc 1 219 16 is_stmt 0
	bgtu	a2,t0,.L42
	.loc 1 220 17 is_stmt 1
	.loc 1 220 20 is_stmt 0
	bgeu	a2,t1,.L39
	.loc 1 222 38
	mv	t2,a5
.LVL36:
	.loc 1 221 39
	mv	t1,a2
.LVL37:
.L39:
	.loc 1 216 26 is_stmt 1 discriminator 2
	addi	a5,a5,1
.LVL38:
	.loc 1 216 19 discriminator 1
	addi	a4,a4,20
	bne	a5,s0,.L41
	mv	a5,t2
.LVL39:
.L40:
	.loc 1 231 5
	.loc 1 231 14 is_stmt 0
	sw	a5,0(a1)
	.loc 1 232 5 is_stmt 1
	.loc 1 232 21 is_stmt 0
	lw	a5,0(sp)
.LVL40:
	.loc 1 234 1
	lw	s0,8(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
	.loc 1 232 21
	sw	t1,0(a5)
.LVL41:
	.loc 1 233 5 is_stmt 1
	.loc 1 234 1 is_stmt 0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
.LVL42:
	jr	ra
.LVL43:
.L42:
	.cfi_restore_state
	.loc 1 225 35
	li	t1,0
.LVL44:
	j	.L40
	.cfi_endproc
.LFE15:
	.size	sw_gpt_find_the_next_expire_time, .-sw_gpt_find_the_next_expire_time
	.section	.text.clear_gpt_and_restart_hw_gpt,"ax",@progbits
	.align	1
	.globl	clear_gpt_and_restart_hw_gpt
	.hidden	clear_gpt_and_restart_hw_gpt
	.type	clear_gpt_and_restart_hw_gpt, @function
clear_gpt_and_restart_hw_gpt:
.LFB17:
	.loc 1 300 1 is_stmt 1
	.cfi_startproc
.LVL45:
	.loc 1 301 5
	.loc 1 303 5
	.loc 1 300 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s1,4(sp)
	.cfi_offset 9, -12
	mv	s1,a0
	.loc 1 303 5
	mv	a0,sp
.LVL46:
	.loc 1 300 1
	sw	s0,8(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 300 1
	mv	s0,a1
	.loc 1 303 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL47:
	.loc 1 304 5 is_stmt 1
	.loc 1 306 5
	.loc 1 306 53 is_stmt 0
	li	a5,4329472
	addi	a5,a5,1280
	add	a5,s0,a5
	slli	a5,a5,8
	.loc 1 306 68
	lw	a4,0(a5)
	.loc 1 306 77
	li	a3,-65536
	addi	a3,a3,-1
	and	a4,a4,a3
	sw	a4,0(a5)
	.loc 1 307 5 is_stmt 1
	.loc 1 307 66 is_stmt 0
	sw	zero,12(a5)
	.loc 1 308 5 is_stmt 1
	.loc 1 308 82 is_stmt 0
	lbu	a4,0(a5)
	.loc 1 314 60 discriminator 1
	li	a2,1108676608
	addi	a2,a2,-1024
	.loc 1 308 86
	andi	a4,a4,254
	sb	a4,0(a5)
	.loc 1 312 5 is_stmt 1
	.loc 1 312 63 is_stmt 0
	sw	zero,8(a5)
	.loc 1 313 5 is_stmt 1
	.loc 1 314 80 is_stmt 0 discriminator 1
	li	a4,1
	.loc 1 313 67
	sw	s1,28(a5)
	.loc 1 314 5 is_stmt 1
	.loc 1 314 80 is_stmt 0 discriminator 1
	sll	a4,a4,s0
.L47:
	.loc 1 314 12 is_stmt 1 discriminator 1
	.loc 1 314 60 is_stmt 0 discriminator 1
	lw	a3,24(a2)
	.loc 1 314 75 discriminator 1
	and	a3,a3,a4
	.loc 1 314 12 discriminator 1
	bne	a3,zero,.L47
	.loc 1 315 5 is_stmt 1
	.loc 1 315 67 is_stmt 0
	li	a3,1
	sw	a3,20(a5)
	.loc 1 316 5 is_stmt 1
	.loc 1 317 60 is_stmt 0 discriminator 1
	li	a2,1108676608
	.loc 1 316 63
	sw	a3,4(a5)
	.loc 1 317 5 is_stmt 1
	.loc 1 317 60 is_stmt 0 discriminator 1
	addi	a2,a2,-1024
.L48:
	.loc 1 317 12 is_stmt 1 discriminator 1
	.loc 1 317 60 is_stmt 0 discriminator 1
	lw	a3,20(a2)
	.loc 1 317 73 discriminator 1
	and	a3,a4,a3
	.loc 1 317 12 discriminator 1
	bne	a3,zero,.L48
	.loc 1 320 5 is_stmt 1
	.loc 1 320 8 is_stmt 0
	li	a3,5
	bne	s0,a3,.L49
	.loc 1 321 9 is_stmt 1
	.loc 1 321 67 is_stmt 0
	li	a3,1108672512
	addi	a3,a3,1280
	li	a2,16
.L54:
	.loc 1 324 67
	sw	a2,8(a3)
.L50:
	.loc 1 327 5 is_stmt 1
	.loc 1 327 68 is_stmt 0
	lw	a3,0(a5)
	.loc 1 329 70
	not	a4,a4
	.loc 1 327 77
	andi	a3,a3,-769
	sw	a3,0(a5)
	.loc 1 328 5 is_stmt 1
	.loc 1 328 82 is_stmt 0
	lbu	a3,0(a5)
	.loc 1 328 86
	ori	a3,a3,1
	sb	a3,0(a5)
	.loc 1 329 5 is_stmt 1
	.loc 1 329 53 is_stmt 0
	li	a3,1108676608
	addi	a3,a3,-1024
	lw	a2,8(a3)
	.loc 1 329 67
	and	a2,a2,a4
	sw	a2,8(a3)
	.loc 1 330 5 is_stmt 1
	.loc 1 330 53 is_stmt 0
	lw	a2,16(a3)
	.loc 1 330 70
	and	a4,a4,a2
	sw	a4,16(a3)
	.loc 1 331 5 is_stmt 1
	.loc 1 335 5 is_stmt 0
	lw	a0,0(sp)
	.loc 1 331 66
	li	a4,1
	sw	a4,12(a5)
	.loc 1 335 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL48:
	.loc 1 336 5
	.loc 1 337 1 is_stmt 0
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
	jr	ra
.LVL51:
.L49:
	.cfi_restore_state
	.loc 1 323 5 is_stmt 1
	.loc 1 323 8 is_stmt 0
	li	a3,6
	bne	s0,a3,.L50
	.loc 1 324 9 is_stmt 1
	.loc 1 324 67 is_stmt 0
	li	a3,1108672512
	addi	a3,a3,1536
	li	a2,13
	j	.L54
	.cfi_endproc
.LFE17:
	.size	clear_gpt_and_restart_hw_gpt, .-clear_gpt_and_restart_hw_gpt
	.section	.text.sw_gpt_callback,"ax",@progbits
	.align	1
	.globl	sw_gpt_callback
	.hidden	sw_gpt_callback
	.type	sw_gpt_callback, @function
sw_gpt_callback:
.LFB16:
	.loc 1 237 1 is_stmt 1
	.cfi_startproc
.LVL52:
	.loc 1 238 5
	.loc 1 237 1 is_stmt 0
	addi	sp,sp,-44
	.cfi_def_cfa_offset 44
	sw	s0,36(sp)
	.cfi_offset 8, -8
	.loc 1 243 19
	lw	s0,0(a0)
	.loc 1 237 1
	sw	ra,40(sp)
	sw	s1,32(sp)
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 244 40
	slli	a5,s0,2
	sw	a5,8(sp)
	slli	a4,s0,2
	lla	a5,g_sw_gpt_running_note
	add	a5,a5,a4
	.loc 1 238 23
	sw	zero,20(sp)
	.loc 1 239 5 is_stmt 1
	.loc 1 240 5
	.loc 1 241 5
	.loc 1 242 5
.LVL53:
	.loc 1 243 5
	.loc 1 244 5
	.loc 1 244 40 is_stmt 0
	li	a4,10
	sw	a4,0(a5)
	.loc 1 242 20
	li	a5,7
	sw	a5,0(sp)
.LVL54:
.L56:
	.loc 1 245 5 is_stmt 1
	.loc 1 247 5
	.loc 1 247 8 is_stmt 0
	bne	s0,zero,.L57
	.loc 1 248 9 is_stmt 1
.LVL55:
	.loc 1 249 9
	addi	a1,sp,20
	li	a0,0
	call	hal_gpt_get_free_run_count
.LVL56:
	.loc 1 251 5
	.loc 1 248 18 is_stmt 0
	li	a5,5
.LVL57:
.L72:
	.loc 1 252 18
	sw	a5,0(sp)
.L58:
.LVL58:
	.loc 1 255 5 is_stmt 1
	.loc 1 256 5
	.loc 1 256 19 discriminator 1
	lla	s1,g_sw_gpt_notes
	.loc 1 255 18 is_stmt 0
	sw	zero,4(sp)
.LVL59:
.L61:
	.loc 1 260 9 is_stmt 1
	addi	a0,sp,16
	call	hal_nvic_save_and_set_interrupt_mask
.LVL60:
	.loc 1 261 9
	.loc 1 261 12 is_stmt 0
	lw	a3,4(s1)
	li	a4,2
	lw	a0,16(sp)
	bne	a3,a4,.L59
	.loc 1 261 85 discriminator 1
	lw	a4,8(s1)
	bne	a4,s0,.L59
	.loc 1 263 28
	lw	a4,0(s1)
	lw	a3,20(sp)
	sub	a3,a3,a4
	.loc 1 262 77
	li	a4,-2147483648
	addi	a4,a4,-2
	bgtu	a3,a4,.L59
	.loc 1 264 13 is_stmt 1
	.loc 1 264 51 is_stmt 0
	li	a5,1
	.loc 1 265 27
	lw	a4,12(s1)
	.loc 1 264 51
	sw	a5,4(s1)
	.loc 1 265 13 is_stmt 1
	.loc 1 266 28 is_stmt 0
	lw	a5,16(s1)
	.loc 1 265 27
	sw	a4,12(sp)
.LVL61:
	.loc 1 266 13 is_stmt 1
	.loc 1 266 28 is_stmt 0
	sw	a5,4(sp)
.LVL62:
	.loc 1 267 13 is_stmt 1
	.loc 1 268 13
	call	hal_nvic_restore_interrupt_mask
.LVL63:
	.loc 1 270 13
	lw	a0,4(sp)
	lw	a4,12(sp)
	jalr	a4
.LVL64:
	.loc 1 267 26 is_stmt 0
	li	a5,1
	sw	a5,4(sp)
.LVL65:
.L60:
	.loc 1 256 26 is_stmt 1 discriminator 2
	.loc 1 256 19 discriminator 1
	addi	s1,s1,20
	lla	a5,g_sw_gpt_notes+200
	bne	s1,a5,.L61
	.loc 1 275 5
	.loc 1 275 8 is_stmt 0
	lw	a5,4(sp)
	li	a4,1
	beq	a5,a4,.L56
	.loc 1 278 5 is_stmt 1
	addi	a0,sp,16
	call	hal_nvic_save_and_set_interrupt_mask
.LVL66:
	.loc 1 281 5
	.loc 1 281 30 is_stmt 0
	lw	a4,8(sp)
	lla	a5,g_sw_gpt_running_note
	add	a5,a5,a4
	.loc 1 281 8
	lw	t1,0(a5)
	li	a4,10
	bne	t1,a4,.L62
	.loc 1 282 9
	lw	a0,20(sp)
	mv	a3,s0
	addi	a2,sp,28
	addi	a1,sp,24
	sw	t1,8(sp)
	sw	a5,4(sp)
.LVL67:
	.loc 1 282 9 is_stmt 1
	call	sw_gpt_find_the_next_expire_time
.LVL68:
	.loc 1 283 9
	.loc 1 283 24 is_stmt 0
	lw	a4,24(sp)
	.loc 1 283 12
	lw	t1,8(sp)
	lw	a5,4(sp)
	bne	a4,t1,.L63
	.loc 1 284 13 is_stmt 1
	.loc 1 284 45 is_stmt 0
	lw	a4,0(sp)
	li	a5,4329472
	addi	a5,a5,1280
	add	a5,a4,a5
	slli	a5,a5,8
	.loc 1 284 98
	sb	zero,0(a5)
	.loc 1 285 13 is_stmt 1
	.loc 1 285 16 is_stmt 0
	li	a5,1
	bne	s0,a5,.L62
	.loc 1 285 48 discriminator 1
	lbu	a5,sw_gpt_us_locksleep_status
	beq	a5,zero,.L62
	.loc 1 286 17 is_stmt 1
	.loc 1 286 44 is_stmt 0
	sb	zero,sw_gpt_us_locksleep_status,a5
	.loc 1 287 17 is_stmt 1
	.loc 1 287 21
	lla	a5,gpt_lock_sleep_handle
	add	a5,a5,a4
	lbu	a0,0(a5)
	call	hal_sleep_manager_unlock_sleep
.LVL69:
	.loc 1 287 19 discriminator 1
	.loc 1 289 13
.L62:
	.loc 1 295 5
	lw	a0,16(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL70:
	.loc 1 296 1 is_stmt 0
	lw	ra,40(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,36(sp)
	.cfi_restore 8
.LVL71:
	lw	s1,32(sp)
	.cfi_restore 9
	addi	sp,sp,44
	.cfi_def_cfa_offset 0
.LVL72:
	jr	ra
.LVL73:
.L57:
	.cfi_restore_state
	.loc 1 251 5 is_stmt 1
	.loc 1 251 8 is_stmt 0
	li	a5,1
	bne	s0,a5,.L58
	.loc 1 252 9 is_stmt 1
.LVL74:
	.loc 1 253 9
	addi	a1,sp,20
	li	a0,1
	call	hal_gpt_get_free_run_count
.LVL75:
	.loc 1 252 18 is_stmt 0
	li	a5,6
	j	.L72
.LVL76:
.L59:
	.loc 1 272 13 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL77:
	j	.L60
.LVL78:
.L63:
	.loc 1 292 9
	.loc 1 292 44 is_stmt 0
	sw	a4,0(a5)
	.loc 1 293 9 is_stmt 1
	lw	a1,0(sp)
	lw	a0,28(sp)
	call	clear_gpt_and_restart_hw_gpt
.LVL79:
	j	.L62
	.cfi_endproc
.LFE16:
	.size	sw_gpt_callback, .-sw_gpt_callback
	.section	.text.sw_gpt_timer_start,"ax",@progbits
	.align	1
	.globl	sw_gpt_timer_start
	.hidden	sw_gpt_timer_start
	.type	sw_gpt_timer_start, @function
sw_gpt_timer_start:
.LFB18:
	.loc 1 344 1
	.cfi_startproc
.LVL80:
	.loc 1 345 5
	.loc 1 345 14 is_stmt 0
	slli	a5,a0,16
	.loc 1 344 1
	addi	sp,sp,-44
	.cfi_def_cfa_offset 44
	.loc 1 345 14
	srli	a5,a5,16
	.loc 1 344 1
	sw	ra,40(sp)
	sw	s0,36(sp)
	sw	s1,32(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 344 1
	sw	a2,4(sp)
	sw	a3,8(sp)
	.loc 1 345 14
	sw	a5,0(sp)
.LVL81:
	.loc 1 346 5 is_stmt 1
	.loc 1 346 14 is_stmt 0
	sw	zero,16(sp)
.LVL82:
	.loc 1 347 5 is_stmt 1
	.loc 1 348 5
	.loc 1 349 5
	.loc 1 349 8 is_stmt 0
	beq	a2,zero,.L86
	.loc 1 352 5 is_stmt 1
	.loc 1 352 17 is_stmt 0
	li	a5,-1431699456
.LVL83:
	and	a0,a0,a5
.LVL84:
	.loc 1 352 8
	bne	a0,a5,.L86
	mv	s0,a4
	.loc 1 355 5 is_stmt 1
	.loc 1 355 8 is_stmt 0
	lw	a4,0(sp)
.LVL85:
	li	a5,9
	bgtu	a4,a5,.L86
	.loc 1 360 8
	li	a5,65536000
	mv	s1,a1
	.loc 1 360 5 is_stmt 1
	.loc 1 360 8 is_stmt 0
	bltu	a1,a5,.L75
	.loc 1 360 33 discriminator 1
	beq	s0,zero,.L88
	.loc 1 363 5 is_stmt 1
	.loc 1 363 8 is_stmt 0
	bge	a1,zero,.L76
	.loc 1 363 35 discriminator 1
	li	a5,1
	beq	s0,a5,.L88
.L89:
	li	t1,7
	li	s1,0
	j	.L78
.LVL86:
.L75:
	.loc 1 368 5 is_stmt 1
	.loc 1 368 8 is_stmt 0
	bne	s0,zero,.L76
	.loc 1 369 9 is_stmt 1
.LVL87:
	.loc 1 370 9
	addi	a1,sp,16
	li	a0,0
	call	hal_gpt_get_free_run_count
.LVL88:
	.loc 1 371 9
	.loc 1 371 24 is_stmt 0
	mv	a0,s1
	call	gpt_convert_ms_to_32k_count
.LVL89:
	mv	s1,a0
.LVL90:
	.loc 1 369 18
	li	t1,5
.LVL91:
.L78:
	.loc 1 384 18
	lw	a5,16(sp)
	.loc 1 387 5
	addi	a0,sp,20
	sw	t1,12(sp)
.LVL92:
	.loc 1 384 5 is_stmt 1
	.loc 1 384 18 is_stmt 0
	add	s1,s1,a5
.LVL93:
	.loc 1 387 5 is_stmt 1
	call	hal_nvic_save_and_set_interrupt_mask
.LVL94:
	.loc 1 388 5
	.loc 1 388 43 is_stmt 0
	lw	a5,0(sp)
	.loc 1 388 8
	lw	t1,12(sp)
	.loc 1 388 43
	slli	a4,a5,2
	add	a4,a4,a5
	slli	a4,a4,2
	lla	a5,g_sw_gpt_notes
	add	a5,a5,a4
	.loc 1 388 8
	lw	a3,4(a5)
	li	a4,1
	beq	a3,a4,.L80
	.loc 1 389 9 is_stmt 1
	lw	a0,20(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL95:
	.loc 1 390 9
	.loc 1 390 16 is_stmt 0
	li	a0,-7
.LVL96:
.L73:
	.loc 1 411 1
	lw	ra,40(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,36(sp)
	.cfi_restore 8
	lw	s1,32(sp)
	.cfi_restore 9
	addi	sp,sp,44
	.cfi_def_cfa_offset 0
.LVL97:
	jr	ra
.LVL98:
.L76:
	.cfi_restore_state
	.loc 1 373 5 is_stmt 1
	.loc 1 373 8 is_stmt 0
	li	a5,1
	bne	s0,a5,.L89
	.loc 1 374 9 is_stmt 1
.LVL99:
	.loc 1 375 9
	addi	a0,sp,20
	call	hal_nvic_save_and_set_interrupt_mask
.LVL100:
	.loc 1 376 9
	.loc 1 376 40 is_stmt 0
	lla	a5,sw_gpt_us_locksleep_status
	.loc 1 376 12
	lbu	a4,0(a5)
	bne	a4,zero,.L79
	.loc 1 377 13 is_stmt 1
	.loc 1 377 17
	lbu	a0,gpt_lock_sleep_handle+6
	call	hal_sleep_manager_lock_sleep
.LVL101:
	.loc 1 377 15 discriminator 1
	.loc 1 378 13
	.loc 1 378 40 is_stmt 0
	lla	a5,sw_gpt_us_locksleep_status
	sb	s0,0(a5)
.L79:
	.loc 1 380 9 is_stmt 1
	lw	a0,20(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL102:
	.loc 1 381 9
	addi	a1,sp,16
	li	a0,1
	call	hal_gpt_get_free_run_count
.LVL103:
	.loc 1 382 9
	.loc 1 374 18 is_stmt 0
	li	t1,6
	j	.L78
.LVL104:
.L80:
	.loc 1 393 47
	li	a4,2
	sw	a4,4(a5)
	.loc 1 395 49
	lw	a4,4(sp)
	.loc 1 399 5
	lw	a0,16(sp)
	mv	a3,s0
	.loc 1 395 49
	sw	a4,12(a5)
	.loc 1 396 50
	lw	a4,8(sp)
	.loc 1 399 5
	addi	a2,sp,28
	addi	a1,sp,24
	.loc 1 396 50
	sw	a4,16(a5)
	sw	t1,0(sp)
.LVL105:
	.loc 1 393 5 is_stmt 1
	.loc 1 394 5
	.loc 1 394 53 is_stmt 0
	sw	s1,0(a5)
	.loc 1 395 5 is_stmt 1
	.loc 1 396 5
	.loc 1 397 5
	.loc 1 397 56 is_stmt 0
	sw	s0,8(a5)
	.loc 1 399 5 is_stmt 1
	call	sw_gpt_find_the_next_expire_time
.LVL106:
	.loc 1 400 5
	.loc 1 400 20 is_stmt 0
	lw	a4,24(sp)
	.loc 1 400 8
	li	a5,10
	lw	t1,0(sp)
	bne	a4,a5,.L81
.L82:
	.loc 1 401 9 is_stmt 1
	.loc 1 401 14
	j	.L82
.L81:
	.loc 1 405 5
	.loc 1 405 44 is_stmt 0
	slli	s0,s0,2
.LVL107:
	lla	a5,g_sw_gpt_running_note
	add	a5,a5,s0
	.loc 1 405 8
	lw	a3,0(a5)
	beq	a4,a3,.L83
	.loc 1 406 9 is_stmt 1
	.loc 1 406 40 is_stmt 0
	sw	a4,0(a5)
	.loc 1 407 9 is_stmt 1
	lw	a0,28(sp)
	mv	a1,t1
	call	clear_gpt_and_restart_hw_gpt
.LVL108:
.L83:
	.loc 1 409 5
	lw	a0,20(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL109:
	.loc 1 410 5
	.loc 1 410 12 is_stmt 0
	li	a0,0
	j	.L73
.LVL110:
.L86:
	.loc 1 350 16
	li	a0,-1
	j	.L73
.LVL111:
.L88:
	.loc 1 361 16
	li	a0,-6
	j	.L73
	.cfi_endproc
.LFE18:
	.size	sw_gpt_timer_start, .-sw_gpt_timer_start
	.section	.text.sw_gpt_timer_stop,"ax",@progbits
	.align	1
	.globl	sw_gpt_timer_stop
	.hidden	sw_gpt_timer_stop
	.type	sw_gpt_timer_stop, @function
sw_gpt_timer_stop:
.LFB19:
	.loc 1 414 1 is_stmt 1
	.cfi_startproc
.LVL112:
	.loc 1 415 5
	.loc 1 414 1 is_stmt 0
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	.loc 1 421 17
	li	a5,-1431699456
	.loc 1 414 1
	sw	s1,20(sp)
	sw	ra,28(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 415 14
	slli	s1,a0,16
.LVL113:
	.loc 1 416 5 is_stmt 1
	.loc 1 417 5
	.loc 1 414 1 is_stmt 0
	sw	s0,24(sp)
	.cfi_offset 8, -8
	.loc 1 417 14
	sw	zero,8(sp)
	.loc 1 418 5 is_stmt 1
	.loc 1 419 5
.LVL114:
	.loc 1 421 5
	.loc 1 421 17 is_stmt 0
	and	a0,a0,a5
.LVL115:
	.loc 1 421 8
	bne	a0,a5,.L100
	srli	s1,s1,16
.LVL116:
	.loc 1 424 5 is_stmt 1
	.loc 1 424 8 is_stmt 0
	li	a5,9
	.loc 1 422 16
	li	a0,-1
	.loc 1 424 8
	bgtu	s1,a5,.L91
	mv	s0,a1
	.loc 1 427 5 is_stmt 1
	.loc 1 427 8 is_stmt 0
	bne	a1,zero,.L93
	.loc 1 428 9 is_stmt 1
.LVL117:
	.loc 1 429 9
	addi	a1,sp,8
.LVL118:
	li	a0,0
	call	hal_gpt_get_free_run_count
.LVL119:
	.loc 1 431 5
	.loc 1 428 18 is_stmt 0
	li	a4,5
.LVL120:
.L94:
	.loc 1 435 5
	addi	a0,sp,4
	sw	a4,0(sp)
.LVL121:
	.loc 1 435 5 is_stmt 1
	call	hal_nvic_save_and_set_interrupt_mask
.LVL122:
	.loc 1 436 5
	.loc 1 436 43 is_stmt 0
	slli	a5,s1,2
	add	a5,a5,s1
	lla	a3,g_sw_gpt_notes
	slli	a5,a5,2
	add	a5,a3,a5
	.loc 1 436 8
	lw	a2,4(a5)
	li	a3,2
	bne	a2,a3,.L95
	.loc 1 437 9 is_stmt 1
	.loc 1 440 9
	lw	a0,8(sp)
	.loc 1 437 51 is_stmt 0
	li	t1,1
	.loc 1 440 9
	mv	a3,s0
	addi	a2,sp,16
	addi	a1,sp,12
	.loc 1 437 51
	sw	t1,4(a5)
	.loc 1 440 9
	call	sw_gpt_find_the_next_expire_time
.LVL123:
	.loc 1 441 9 is_stmt 1
	.loc 1 441 24 is_stmt 0
	lw	a5,12(sp)
	.loc 1 441 12
	li	a2,10
	lw	a4,0(sp)
	lla	s1,g_sw_gpt_running_note
.LVL124:
	slli	a3,s0,2
	li	t1,1
	bne	a5,a2,.L96
	.loc 1 442 13 is_stmt 1
	.loc 1 442 45 is_stmt 0
	li	a5,4329472
	addi	a5,a5,1280
	add	a5,a4,a5
	slli	a5,a5,8
	.loc 1 442 98
	sb	zero,0(a5)
	.loc 1 443 13 is_stmt 1
	.loc 1 443 16 is_stmt 0
	bne	s0,t1,.L97
	.loc 1 443 44 discriminator 1
	lbu	a5,sw_gpt_us_locksleep_status
	beq	a5,zero,.L97
	.loc 1 444 44
	sb	zero,sw_gpt_us_locksleep_status,a5
	.loc 1 445 21
	lla	a5,gpt_lock_sleep_handle
	add	a5,a5,a4
	lbu	a0,0(a5)
	sw	a3,0(sp)
.LVL125:
	.loc 1 444 17 is_stmt 1
	.loc 1 445 17
	.loc 1 445 21
	call	hal_sleep_manager_unlock_sleep
.LVL126:
	lw	a3,0(sp)
.L97:
	.loc 1 445 19 discriminator 1
	.loc 1 447 13
	.loc 1 447 44 is_stmt 0
	add	a3,s1,a3
	li	a5,10
	sw	a5,0(a3)
.L107:
	.loc 1 448 13 is_stmt 1
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL127:
	.loc 1 449 13
	.loc 1 449 20 is_stmt 0
	li	a0,0
.LVL128:
.L91:
	.loc 1 463 1
	lw	ra,28(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,24(sp)
	.cfi_restore 8
	lw	s1,20(sp)
	.cfi_restore 9
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
.LVL129:
.L93:
	.cfi_restore_state
	.loc 1 431 5 is_stmt 1
	.loc 1 431 8 is_stmt 0
	li	a5,1
	li	a4,7
	bne	a1,a5,.L94
	.loc 1 432 9 is_stmt 1
.LVL130:
	.loc 1 433 9
	addi	a1,sp,8
	li	a0,1
	call	hal_gpt_get_free_run_count
.LVL131:
	.loc 1 432 18 is_stmt 0
	li	a4,6
	j	.L94
.LVL132:
.L96:
	.loc 1 451 9 is_stmt 1
	.loc 1 451 34 is_stmt 0
	add	s1,s1,a3
	.loc 1 451 12
	lw	a3,0(s1)
	sw	a5,0(sp)
.LVL133:
	beq	a5,a3,.L107
	.loc 1 453 13 is_stmt 1
	lw	a0,16(sp)
	mv	a1,a4
	call	clear_gpt_and_restart_hw_gpt
.LVL134:
	.loc 1 454 13
	.loc 1 454 44 is_stmt 0
	lw	a5,0(sp)
	sw	a5,0(s1)
	.loc 1 456 9 is_stmt 1
.LVL135:
	.loc 1 457 9
	j	.L107
.LVL136:
.L95:
	.loc 1 459 9
	.loc 1 460 9
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL137:
	.loc 1 459 20 is_stmt 0
	li	a0,-3
	j	.L91
.LVL138:
.L100:
	.loc 1 422 16
	li	a0,-1
	j	.L91
	.cfi_endproc
.LFE19:
	.size	sw_gpt_timer_stop, .-sw_gpt_timer_stop
	.section	.text.sw_gpt_get_remaining_time,"ax",@progbits
	.align	1
	.globl	sw_gpt_get_remaining_time
	.hidden	sw_gpt_get_remaining_time
	.type	sw_gpt_get_remaining_time, @function
sw_gpt_get_remaining_time:
.LFB20:
	.loc 1 466 1 is_stmt 1
	.cfi_startproc
.LVL139:
	.loc 1 467 5
	.loc 1 467 14 is_stmt 0
	slli	a4,a0,16
	.loc 1 466 1
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	.loc 1 467 14
	srli	a4,a4,16
.LVL140:
	.loc 1 468 5 is_stmt 1
	.loc 1 469 5
	.loc 1 466 1 is_stmt 0
	sw	ra,20(sp)
	sw	s0,16(sp)
	sw	s1,12(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 469 14
	sw	zero,8(sp)
	.loc 1 470 5 is_stmt 1
	.loc 1 472 5
	.loc 1 472 8 is_stmt 0
	li	a5,9
	sw	a4,0(sp)
	.loc 1 473 16
	li	a0,-1
.LVL141:
	.loc 1 472 8
	bgtu	a4,a5,.L108
	.loc 1 475 5
	addi	a0,sp,4
	mv	s0,a1
	mv	s1,a2
	.loc 1 475 5 is_stmt 1
	call	hal_nvic_save_and_set_interrupt_mask
.LVL142:
	.loc 1 476 5
	.loc 1 476 43 is_stmt 0
	lw	a4,0(sp)
	lw	a0,4(sp)
	slli	a5,a4,2
	add	a5,a5,a4
	slli	a5,a5,2
	lla	a4,g_sw_gpt_notes
	add	a5,a4,a5
	.loc 1 476 8
	lw	a3,4(a5)
	li	a4,2
	beq	a3,a4,.L110
	.loc 1 477 9 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL143:
	.loc 1 478 9
	.loc 1 478 16 is_stmt 0
	li	a0,-3
.LVL144:
.L108:
	.loc 1 507 1
	lw	ra,20(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	lw	s1,12(sp)
	.cfi_restore 9
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
	jr	ra
.LVL145:
.L110:
	.cfi_restore_state
	.loc 1 480 5 is_stmt 1
	.loc 1 480 18 is_stmt 0
	lw	a5,0(a5)
	sw	a5,0(sp)
.LVL146:
	.loc 1 481 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL147:
	.loc 1 483 5
	.loc 1 483 8 is_stmt 0
	bne	s1,zero,.L111
	.loc 1 484 9 is_stmt 1
	addi	a1,sp,8
	li	a0,0
	call	hal_gpt_get_free_run_count
.LVL148:
	.loc 1 485 9
	.loc 1 485 22 is_stmt 0
	lw	a5,0(sp)
	lw	a3,8(sp)
	sub	a3,a5,a3
.LVL149:
	.loc 1 487 9 is_stmt 1
	.loc 1 487 12 is_stmt 0
	li	a5,-2147483648
	addi	a5,a5,-2
	bgtu	a3,a5,.L112
	.loc 1 488 13 is_stmt 1
.LVL150:
	.loc 1 489 13
	.loc 1 490 13
	.loc 1 491 13
	.loc 1 489 38 is_stmt 0
	slli	a5,a3,17
	srli	a4,a5,17
	.loc 1 489 47
	srli	a5,a5,12
	sub	a5,a5,a4
	slli	a5,a5,2
	add	a5,a5,a4
	.loc 1 488 20
	srli	a3,a3,15
.LVL151:
	.loc 1 489 54
	li	a4,16384
	.loc 1 489 47
	slli	a5,a5,3
	.loc 1 489 54
	add	a5,a5,a4
	.loc 1 490 37
	slli	a4,a3,5
	sub	a4,a4,a3
	slli	a4,a4,2
	add	a4,a4,a3
	.loc 1 489 21
	srli	a5,a5,15
	.loc 1 490 37
	slli	a4,a4,3
	.loc 1 490 28
	add	a5,a5,a4
.LVL152:
.L116:
	.loc 1 500 13 is_stmt 1
	.loc 1 501 13
	.loc 1 501 26 is_stmt 0
	sw	a5,0(s0)
	.loc 1 502 13 is_stmt 1
.LVL153:
.L113:
	.loc 1 492 20 is_stmt 0
	li	a0,0
	j	.L108
.L111:
	.loc 1 495 5 is_stmt 1
	.loc 1 495 8 is_stmt 0
	li	a5,1
	bne	s1,a5,.L112
	.loc 1 496 9 is_stmt 1
	addi	a1,sp,8
	li	a0,1
	call	hal_gpt_get_free_run_count
.LVL154:
	.loc 1 497 9
	.loc 1 497 22 is_stmt 0
	lw	a4,0(sp)
	lw	a5,8(sp)
	sub	a5,a4,a5
.LVL155:
	.loc 1 499 9 is_stmt 1
	.loc 1 499 12 is_stmt 0
	li	a4,-2147483648
	addi	a4,a4,-2
	bleu	a5,a4,.L116
.LVL156:
.L112:
	.loc 1 505 5 is_stmt 1
	.loc 1 505 18 is_stmt 0
	sw	zero,0(s0)
	.loc 1 506 5 is_stmt 1
	.loc 1 506 12 is_stmt 0
	j	.L113
	.cfi_endproc
.LFE20:
	.size	sw_gpt_get_remaining_time, .-sw_gpt_get_remaining_time
	.section	.sbss.is_init.0,"aw",@nobits
	.type	is_init.0, @object
	.size	is_init.0, 1
is_init.0:
	.zero	1
	.hidden	sw_gpt_us_locksleep_status
	.globl	sw_gpt_us_locksleep_status
	.section	.sbss.sw_gpt_us_locksleep_status,"aw",@nobits
	.type	sw_gpt_us_locksleep_status, @object
	.size	sw_gpt_us_locksleep_status, 1
sw_gpt_us_locksleep_status:
	.zero	1
	.hidden	gpt_context_mapping
	.globl	gpt_context_mapping
	.section	.srodata.gpt_context_mapping,"a"
	.align	2
	.type	gpt_context_mapping, @object
	.size	gpt_context_mapping, 8
gpt_context_mapping:
	.word	5
	.word	6
	.hidden	gpt_running_state
	.globl	gpt_running_state
	.section	.sbss.gpt_running_state,"aw",@nobits
	.align	2
	.type	gpt_running_state, @object
	.size	gpt_running_state, 8
gpt_running_state:
	.zero	8
	.hidden	g_gpt_context
	.globl	g_gpt_context
	.section	.bss.g_gpt_context,"aw",@nobits
	.align	2
	.type	g_gpt_context, @object
	.size	g_gpt_context, 32
g_gpt_context:
	.zero	32
	.text
.Letext0:
	.file 2 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpt.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 7 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager.h"
	.file 8 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt_internal.h"
	.file 9 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x10fb
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x2a
	.4byte	.LASF204
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL52
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x7
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x7
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2b
	.4byte	.LASF205
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x2
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
	.uleb128 0xf
	.4byte	.LASF23
	.byte	0x2
	.2byte	0x13c
	.byte	0x7
	.4byte	0x34
	.uleb128 0xf
	.4byte	.LASF24
	.byte	0x2
	.2byte	0x13e
	.byte	0x17
	.4byte	0xba
	.uleb128 0x7
	.byte	0x1
	.byte	0x6
	.4byte	.LASF25
	.uleb128 0x7
	.byte	0x2
	.byte	0x5
	.4byte	.LASF26
	.uleb128 0x7
	.byte	0x4
	.byte	0x5
	.4byte	.LASF27
	.uleb128 0x7
	.byte	0x8
	.byte	0x5
	.4byte	.LASF28
	.uleb128 0x8
	.4byte	.LASF29
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x106
	.uleb128 0x1e
	.4byte	0xf0
	.uleb128 0x14
	.4byte	0xfc
	.uleb128 0x7
	.byte	0x1
	.byte	0x8
	.4byte	.LASF30
	.uleb128 0x7
	.byte	0x2
	.byte	0x7
	.4byte	.LASF31
	.uleb128 0x8
	.4byte	.LASF32
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x12f
	.uleb128 0x1e
	.4byte	0x114
	.uleb128 0x14
	.4byte	0x120
	.uleb128 0x14
	.4byte	0x114
	.uleb128 0x7
	.byte	0x4
	.byte	0x7
	.4byte	.LASF33
	.uleb128 0x2c
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x10
	.4byte	0x101
	.4byte	0x14d
	.uleb128 0x15
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x14
	.4byte	0x13d
	.uleb128 0x1e
	.4byte	0x14d
	.uleb128 0x11
	.byte	0x1c
	.byte	0x4
	.byte	0x2a
	.4byte	0x1bb
	.uleb128 0x3
	.4byte	.LASF34
	.byte	0x4
	.byte	0x2b
	.byte	0x1d
	.4byte	0x125
	.byte	0
	.uleb128 0x3
	.4byte	.LASF35
	.byte	0x4
	.byte	0x2c
	.byte	0x17
	.4byte	0x120
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF36
	.byte	0x4
	.byte	0x2d
	.byte	0x17
	.4byte	0x120
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF37
	.byte	0x4
	.byte	0x2e
	.byte	0x17
	.4byte	0x120
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF38
	.byte	0x4
	.byte	0x2f
	.byte	0x17
	.4byte	0x120
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF39
	.byte	0x4
	.byte	0x30
	.byte	0x1d
	.4byte	0x125
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF40
	.byte	0x4
	.byte	0x31
	.byte	0x1d
	.4byte	0x125
	.byte	0x18
	.byte	0
	.uleb128 0x8
	.4byte	.LASF41
	.byte	0x4
	.byte	0x32
	.byte	0x3
	.4byte	0x157
	.uleb128 0x11
	.byte	0x4
	.byte	0x4
	.byte	0x36
	.4byte	0x203
	.uleb128 0x2d
	.string	"EN"
	.byte	0x4
	.byte	0x37
	.byte	0x1e
	.4byte	0xfc
	.byte	0
	.uleb128 0x3
	.4byte	.LASF42
	.byte	0x4
	.byte	0x38
	.byte	0x1e
	.4byte	0xfc
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF43
	.byte	0x4
	.byte	0x39
	.byte	0x1e
	.4byte	0xfc
	.byte	0x2
	.uleb128 0x3
	.4byte	.LASF44
	.byte	0x4
	.byte	0x3a
	.byte	0x24
	.4byte	0x152
	.byte	0x3
	.byte	0
	.uleb128 0x2e
	.byte	0x4
	.byte	0x4
	.byte	0x35
	.byte	0x5
	.4byte	0x223
	.uleb128 0x24
	.4byte	.LASF45
	.byte	0x3b
	.byte	0xb
	.4byte	0x1c7
	.uleb128 0x24
	.4byte	.LASF46
	.byte	0x3c
	.byte	0x1b
	.4byte	0x120
	.byte	0
	.uleb128 0x11
	.byte	0x20
	.byte	0x4
	.byte	0x34
	.4byte	0x294
	.uleb128 0x3
	.4byte	.LASF47
	.byte	0x4
	.byte	0x3d
	.byte	0x7
	.4byte	0x203
	.byte	0
	.uleb128 0x3
	.4byte	.LASF48
	.byte	0x4
	.byte	0x3e
	.byte	0x17
	.4byte	0x120
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF49
	.byte	0x4
	.byte	0x3f
	.byte	0x17
	.4byte	0x120
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF50
	.byte	0x4
	.byte	0x40
	.byte	0x17
	.4byte	0x120
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF51
	.byte	0x4
	.byte	0x41
	.byte	0x1d
	.4byte	0x125
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF52
	.byte	0x4
	.byte	0x42
	.byte	0x17
	.4byte	0x120
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF53
	.byte	0x4
	.byte	0x43
	.byte	0x17
	.4byte	0x120
	.byte	0x18
	.uleb128 0x3
	.4byte	.LASF54
	.byte	0x4
	.byte	0x44
	.byte	0x17
	.4byte	0x120
	.byte	0x1c
	.byte	0
	.uleb128 0x8
	.4byte	.LASF55
	.byte	0x4
	.byte	0x45
	.byte	0x3
	.4byte	0x223
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.2byte	0x459
	.4byte	0x2e4
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x7
	.byte	0
	.uleb128 0xf
	.4byte	.LASF65
	.byte	0x5
	.2byte	0x463
	.byte	0x3
	.4byte	0x2a0
	.uleb128 0x14
	.4byte	0x2e4
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.2byte	0x466
	.4byte	0x310
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1
	.byte	0
	.uleb128 0xf
	.4byte	.LASF68
	.byte	0x5
	.2byte	0x469
	.byte	0x3
	.4byte	0x2f6
	.uleb128 0xf
	.4byte	.LASF69
	.byte	0x6
	.2byte	0x143
	.byte	0x10
	.4byte	0x32a
	.uleb128 0x17
	.4byte	0x32f
	.uleb128 0x25
	.4byte	0x33a
	.uleb128 0x9
	.4byte	0x33a
	.byte	0
	.uleb128 0x2f
	.byte	0x4
	.uleb128 0x1b
	.byte	0x5
	.4byte	0x136
	.byte	0x6
	.2byte	0x153
	.4byte	0x37a
	.uleb128 0xd
	.4byte	.LASF70
	.sleb128 -7
	.uleb128 0xd
	.4byte	.LASF71
	.sleb128 -6
	.uleb128 0xd
	.4byte	.LASF72
	.sleb128 -5
	.uleb128 0xd
	.4byte	.LASF73
	.sleb128 -4
	.uleb128 0xd
	.4byte	.LASF74
	.sleb128 -3
	.uleb128 0xd
	.4byte	.LASF75
	.sleb128 -2
	.uleb128 0xd
	.4byte	.LASF76
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	.LASF78
	.byte	0x6
	.2byte	0x15c
	.byte	0x3
	.4byte	0x33c
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.2byte	0x160
	.4byte	0x3a1
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x1
	.byte	0
	.uleb128 0xf
	.4byte	.LASF81
	.byte	0x6
	.2byte	0x163
	.byte	0x3
	.4byte	0x387
	.uleb128 0x7
	.byte	0x10
	.byte	0x4
	.4byte	.LASF82
	.uleb128 0x7
	.byte	0x1
	.byte	0x8
	.4byte	.LASF83
	.uleb128 0x16
	.byte	0x5
	.4byte	0x136
	.byte	0x7
	.byte	0x2d
	.byte	0xe
	.4byte	0x3d6
	.uleb128 0xd
	.4byte	.LASF84
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF86
	.byte	0x7
	.byte	0x30
	.byte	0x3
	.4byte	0x3bc
	.uleb128 0x16
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x53
	.byte	0xe
	.4byte	0x402
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	.LASF90
	.byte	0x8
	.byte	0x57
	.byte	0x3
	.4byte	0x3e2
	.uleb128 0x16
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x71
	.byte	0xe
	.4byte	0x437
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF92
	.2byte	0x100
	.uleb128 0x1f
	.4byte	.LASF93
	.2byte	0x200
	.uleb128 0x1f
	.4byte	.LASF94
	.2byte	0x300
	.byte	0
	.uleb128 0x16
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x78
	.byte	0xe
	.4byte	0x454
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0
	.uleb128 0x30
	.4byte	.LASF96
	.4byte	0x10000
	.byte	0
	.uleb128 0x16
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x7d
	.byte	0xe
	.4byte	0x4c2
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
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0xf
	.byte	0
	.uleb128 0x11
	.byte	0x8
	.byte	0x8
	.byte	0x90
	.4byte	0x4e5
	.uleb128 0x3
	.4byte	.LASF113
	.byte	0x8
	.byte	0x91
	.byte	0x18
	.4byte	0x31d
	.byte	0
	.uleb128 0x3
	.4byte	.LASF114
	.byte	0x8
	.byte	0x92
	.byte	0xb
	.4byte	0x33a
	.byte	0x4
	.byte	0
	.uleb128 0x8
	.4byte	.LASF115
	.byte	0x8
	.byte	0x93
	.byte	0x3
	.4byte	0x4c2
	.uleb128 0x11
	.byte	0x10
	.byte	0x8
	.byte	0x95
	.4byte	0x52e
	.uleb128 0x3
	.4byte	.LASF116
	.byte	0x8
	.byte	0x96
	.byte	0x1e
	.4byte	0x3a1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF117
	.byte	0x8
	.byte	0x97
	.byte	0x1c
	.4byte	0x4e5
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF118
	.byte	0x8
	.byte	0x98
	.byte	0x1d
	.4byte	0x52e
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF119
	.byte	0x8
	.byte	0x99
	.byte	0x1d
	.4byte	0x52e
	.byte	0xd
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.byte	0x2
	.4byte	.LASF120
	.uleb128 0x8
	.4byte	.LASF121
	.byte	0x8
	.byte	0x9a
	.byte	0x3
	.4byte	0x4f1
	.uleb128 0x16
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0xbe
	.byte	0xd
	.4byte	0x561
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	.LASF125
	.byte	0x8
	.byte	0xc2
	.byte	0x2
	.4byte	0x541
	.uleb128 0x11
	.byte	0x14
	.byte	0x8
	.byte	0xc4
	.4byte	0x5b7
	.uleb128 0x3
	.4byte	.LASF126
	.byte	0x8
	.byte	0xc5
	.byte	0xe
	.4byte	0x114
	.byte	0
	.uleb128 0x3
	.4byte	.LASF127
	.byte	0x8
	.byte	0xc6
	.byte	0x1a
	.4byte	0x561
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF128
	.byte	0x8
	.byte	0xc7
	.byte	0x13
	.4byte	0x402
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF113
	.byte	0x8
	.byte	0xc8
	.byte	0x18
	.4byte	0x31d
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF114
	.byte	0x8
	.byte	0xc9
	.byte	0xb
	.4byte	0x33a
	.byte	0x10
	.byte	0
	.uleb128 0x8
	.4byte	.LASF129
	.byte	0x8
	.byte	0xca
	.byte	0x2
	.4byte	0x56d
	.uleb128 0x11
	.byte	0xcc
	.byte	0x8
	.byte	0xcc
	.4byte	0x5e6
	.uleb128 0x3
	.4byte	.LASF130
	.byte	0x8
	.byte	0xcd
	.byte	0xf
	.4byte	0x5e6
	.byte	0
	.uleb128 0x3
	.4byte	.LASF131
	.byte	0x8
	.byte	0xce
	.byte	0x9
	.4byte	0xf0
	.byte	0xc8
	.byte	0
	.uleb128 0x10
	.4byte	0x5b7
	.4byte	0x5f6
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x8
	.4byte	.LASF132
	.byte	0x8
	.byte	0xcf
	.byte	0x2
	.4byte	0x5c3
	.uleb128 0x10
	.4byte	0x535
	.4byte	0x612
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x18
	.4byte	.LASF133
	.byte	0x8
	.byte	0xd2
	.byte	0x16
	.4byte	0x602
	.uleb128 0x10
	.4byte	0x3a1
	.4byte	0x62e
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x18
	.4byte	.LASF134
	.byte	0x8
	.byte	0xd3
	.byte	0x21
	.4byte	0x61e
	.uleb128 0x8
	.4byte	.LASF135
	.byte	0x9
	.byte	0x2e
	.byte	0x10
	.4byte	0x646
	.uleb128 0x17
	.4byte	0x64b
	.uleb128 0x25
	.4byte	0x656
	.uleb128 0x9
	.4byte	0xc7
	.byte	0
	.uleb128 0x26
	.4byte	0x612
	.byte	0x31
	.byte	0xf
	.uleb128 0x5
	.byte	0x3
	.4byte	g_gpt_context
	.uleb128 0x26
	.4byte	0x62e
	.byte	0x33
	.byte	0x1a
	.uleb128 0x5
	.byte	0x3
	.4byte	gpt_running_state
	.uleb128 0x10
	.4byte	0x2f1
	.4byte	0x680
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x14
	.4byte	0x670
	.uleb128 0x27
	.4byte	.LASF136
	.byte	0x34
	.byte	0x16
	.4byte	0x680
	.uleb128 0x5
	.byte	0x3
	.4byte	gpt_context_mapping
	.uleb128 0x10
	.4byte	0xf0
	.4byte	0x6a6
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x18
	.4byte	.LASF137
	.byte	0x1
	.byte	0x36
	.byte	0x10
	.4byte	0x696
	.uleb128 0x18
	.4byte	.LASF138
	.byte	0x1
	.byte	0xd0
	.byte	0x1a
	.4byte	0x5f6
	.uleb128 0x10
	.4byte	0x114
	.4byte	0x6c9
	.uleb128 0x31
	.byte	0
	.uleb128 0x18
	.4byte	.LASF139
	.byte	0x1
	.byte	0xd1
	.byte	0x11
	.4byte	0x6be
	.uleb128 0x27
	.4byte	.LASF140
	.byte	0xd2
	.byte	0x5
	.4byte	0x52e
	.uleb128 0x5
	.byte	0x3
	.4byte	sw_gpt_us_locksleep_status
	.uleb128 0x28
	.4byte	.LASF141
	.byte	0x35
	.4byte	0x3d6
	.4byte	0x6fa
	.uleb128 0x9
	.4byte	0xf0
	.byte	0
	.uleb128 0x28
	.4byte	.LASF142
	.byte	0x36
	.4byte	0x3d6
	.4byte	0x70e
	.uleb128 0x9
	.4byte	0xf0
	.byte	0
	.uleb128 0x19
	.4byte	.LASF143
	.byte	0x3f
	.4byte	0x71e
	.uleb128 0x9
	.4byte	0x114
	.byte	0
	.uleb128 0x19
	.4byte	.LASF144
	.byte	0x3e
	.4byte	0x72e
	.uleb128 0x9
	.4byte	0x72e
	.byte	0
	.uleb128 0x17
	.4byte	0x114
	.uleb128 0x32
	.4byte	.LASF145
	.byte	0x6
	.2byte	0x17b
	.byte	0x12
	.4byte	0x37a
	.4byte	0x74f
	.uleb128 0x9
	.4byte	0x310
	.uleb128 0x9
	.4byte	0x72e
	.byte	0
	.uleb128 0x19
	.4byte	.LASF146
	.byte	0x3c
	.4byte	0x75f
	.uleb128 0x9
	.4byte	0xc7
	.byte	0
	.uleb128 0x19
	.4byte	.LASF147
	.byte	0x3b
	.4byte	0x774
	.uleb128 0x9
	.4byte	0xc7
	.uleb128 0x9
	.4byte	0x63a
	.byte	0
	.uleb128 0x19
	.4byte	.LASF148
	.byte	0x3d
	.4byte	0x784
	.uleb128 0x9
	.4byte	0xc7
	.byte	0
	.uleb128 0x20
	.4byte	.LASF160
	.2byte	0x1d1
	.4byte	0x37a
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x8b0
	.uleb128 0xa
	.4byte	.LASF149
	.2byte	0x1d1
	.byte	0x35
	.4byte	0x114
	.4byte	.LLST42
	.uleb128 0xa
	.4byte	.LASF150
	.2byte	0x1d1
	.byte	0x47
	.4byte	0x72e
	.4byte	.LLST43
	.uleb128 0xa
	.4byte	.LASF151
	.2byte	0x1d1
	.byte	0x62
	.4byte	0x402
	.4byte	.LLST44
	.uleb128 0x6
	.4byte	.LASF152
	.2byte	0x1d3
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST45
	.uleb128 0xc
	.4byte	.LASF153
	.2byte	0x1d4
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xc
	.4byte	.LASF154
	.2byte	0x1d5
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x6
	.4byte	.LASF155
	.2byte	0x1d6
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST46
	.uleb128 0x6
	.4byte	.LASF156
	.2byte	0x1d6
	.byte	0x1c
	.4byte	0x114
	.4byte	.LLST47
	.uleb128 0x6
	.4byte	.LASF157
	.2byte	0x1d6
	.byte	0x24
	.4byte	0x114
	.4byte	.LLST48
	.uleb128 0x6
	.4byte	.LASF158
	.2byte	0x1d6
	.byte	0x2d
	.4byte	0x114
	.4byte	.LLST49
	.uleb128 0x6
	.4byte	.LASF159
	.2byte	0x1d6
	.byte	0x3d
	.4byte	0x114
	.4byte	.LLST50
	.uleb128 0x6
	.4byte	.LASF126
	.2byte	0x1d6
	.byte	0x4d
	.4byte	0x114
	.4byte	.LLST51
	.uleb128 0x4
	.4byte	.LVL142
	.4byte	0x71e
	.4byte	0x86f
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x5
	.4byte	.LVL143
	.4byte	0x70e
	.uleb128 0x5
	.4byte	.LVL147
	.4byte	0x70e
	.uleb128 0x4
	.4byte	.LVL148
	.4byte	0x733
	.4byte	0x89a
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x1c
	.4byte	.LVL154
	.4byte	0x733
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.uleb128 0x20
	.4byte	.LASF161
	.2byte	0x19d
	.4byte	0x37a
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9e0
	.uleb128 0xa
	.4byte	.LASF149
	.2byte	0x19d
	.byte	0x2d
	.4byte	0x114
	.4byte	.LLST37
	.uleb128 0xa
	.4byte	.LASF151
	.2byte	0x19d
	.byte	0x43
	.4byte	0x402
	.4byte	.LLST38
	.uleb128 0x6
	.4byte	.LASF152
	.2byte	0x19f
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST39
	.uleb128 0xc
	.4byte	.LASF153
	.2byte	0x1a0
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xc
	.4byte	.LASF154
	.2byte	0x1a1
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xc
	.4byte	.LASF162
	.2byte	0x1a1
	.byte	0x21
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xc
	.4byte	.LASF163
	.2byte	0x1a1
	.byte	0x2d
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x6
	.4byte	.LASF164
	.2byte	0x1a2
	.byte	0x16
	.4byte	0x37a
	.4byte	.LLST40
	.uleb128 0x6
	.4byte	.LASF165
	.2byte	0x1a3
	.byte	0x14
	.4byte	0x2e4
	.4byte	.LLST41
	.uleb128 0x4
	.4byte	.LVL119
	.4byte	0x733
	.4byte	0x96e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x4
	.4byte	.LVL122
	.4byte	0x71e
	.4byte	0x982
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x4
	.4byte	.LVL123
	.4byte	0xd79
	.4byte	0x9a2
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL126
	.4byte	0x6fa
	.uleb128 0x5
	.4byte	.LVL127
	.4byte	0x70e
	.uleb128 0x4
	.4byte	.LVL131
	.4byte	0x733
	.4byte	0x9cd
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x5
	.4byte	.LVL134
	.4byte	0xb8d
	.uleb128 0x5
	.4byte	.LVL137
	.4byte	0x70e
	.byte	0
	.uleb128 0x20
	.4byte	.LASF166
	.2byte	0x157
	.4byte	0x37a
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb8d
	.uleb128 0xa
	.4byte	.LASF149
	.2byte	0x157
	.byte	0x2e
	.4byte	0x114
	.4byte	.LLST28
	.uleb128 0xa
	.4byte	.LASF167
	.2byte	0x157
	.byte	0x3f
	.4byte	0x114
	.4byte	.LLST29
	.uleb128 0xa
	.4byte	.LASF113
	.2byte	0x157
	.byte	0x60
	.4byte	0x31d
	.4byte	.LLST30
	.uleb128 0xa
	.4byte	.LASF114
	.2byte	0x157
	.byte	0x70
	.4byte	0x33a
	.4byte	.LLST31
	.uleb128 0xa
	.4byte	.LASF151
	.2byte	0x157
	.byte	0x89
	.4byte	0x402
	.4byte	.LLST32
	.uleb128 0x6
	.4byte	.LASF152
	.2byte	0x159
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST33
	.uleb128 0xc
	.4byte	.LASF154
	.2byte	0x15a
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x6
	.4byte	.LASF126
	.2byte	0x15a
	.byte	0x21
	.4byte	0x114
	.4byte	.LLST34
	.uleb128 0x6
	.4byte	.LASF168
	.2byte	0x15a
	.byte	0x2f
	.4byte	0x114
	.4byte	.LLST35
	.uleb128 0xc
	.4byte	.LASF153
	.2byte	0x15a
	.byte	0x41
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xc
	.4byte	.LASF162
	.2byte	0x15b
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xc
	.4byte	.LASF163
	.2byte	0x15b
	.byte	0x1a
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x6
	.4byte	.LASF165
	.2byte	0x15c
	.byte	0x14
	.4byte	0x2e4
	.4byte	.LLST36
	.uleb128 0x4
	.4byte	.LVL88
	.4byte	0x733
	.4byte	0xade
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x4
	.4byte	.LVL89
	.4byte	0x1035
	.4byte	0xaf2
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0x4
	.4byte	.LVL94
	.4byte	0x71e
	.4byte	0xb06
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x5
	.4byte	.LVL95
	.4byte	0x70e
	.uleb128 0x4
	.4byte	.LVL100
	.4byte	0x71e
	.4byte	0xb23
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x5
	.4byte	.LVL101
	.4byte	0x6e6
	.uleb128 0x5
	.4byte	.LVL102
	.4byte	0x70e
	.uleb128 0x4
	.4byte	.LVL103
	.4byte	0x733
	.4byte	0xb4e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x4
	.4byte	.LVL106
	.4byte	0xd79
	.4byte	0xb6e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x4
	.4byte	.LVL108
	.4byte	0xb8d
	.4byte	0xb83
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x5
	.4byte	.LVL109
	.4byte	0x70e
	.byte	0
	.uleb128 0x33
	.4byte	.LASF171
	.byte	0x1
	.2byte	0x12b
	.byte	0x6
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbf1
	.uleb128 0xa
	.4byte	.LASF169
	.2byte	0x12b
	.byte	0x2c
	.4byte	0x114
	.4byte	.LLST19
	.uleb128 0xa
	.4byte	.LASF170
	.2byte	0x12b
	.byte	0x4f
	.4byte	0x2e4
	.4byte	.LLST20
	.uleb128 0xc
	.4byte	.LASF153
	.2byte	0x12d
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x4
	.4byte	.LVL47
	.4byte	0x71e
	.4byte	0xbe7
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL48
	.4byte	0x70e
	.byte	0
	.uleb128 0x12
	.4byte	.LASF172
	.byte	0xec
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd74
	.uleb128 0x1a
	.4byte	.LASF173
	.byte	0xec
	.byte	0x25
	.4byte	0xd74
	.4byte	.LLST21
	.uleb128 0x1d
	.string	"i"
	.byte	0xee
	.4byte	0x114
	.4byte	.LLST22
	.uleb128 0xe
	.4byte	.LASF153
	.byte	0xee
	.byte	0x11
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xe
	.4byte	.LASF154
	.byte	0xee
	.byte	0x17
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xe
	.4byte	.LASF162
	.byte	0xef
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xe
	.4byte	.LASF163
	.byte	0xef
	.byte	0x1a
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xb
	.4byte	.LASF174
	.byte	0xf0
	.byte	0x18
	.4byte	0x31d
	.4byte	.LLST23
	.uleb128 0xb
	.4byte	.LASF175
	.byte	0xf1
	.byte	0xb
	.4byte	0x33a
	.4byte	.LLST24
	.uleb128 0xb
	.4byte	.LASF165
	.byte	0xf2
	.byte	0x14
	.4byte	0x2e4
	.4byte	.LLST25
	.uleb128 0xb
	.4byte	.LASF176
	.byte	0xf3
	.byte	0x13
	.4byte	0x402
	.4byte	.LLST26
	.uleb128 0xb
	.4byte	.LASF177
	.byte	0xf5
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST27
	.uleb128 0x34
	.4byte	.LASF206
	.byte	0x1
	.byte	0xf6
	.byte	0x1
	.4byte	.L56
	.uleb128 0x4
	.4byte	.LVL56
	.4byte	0x733
	.4byte	0xcc8
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x4
	.4byte	.LVL60
	.4byte	0x71e
	.4byte	0xcdc
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x5
	.4byte	.LVL63
	.4byte	0x70e
	.uleb128 0x35
	.4byte	.LVL64
	.uleb128 0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x6
	.4byte	0xcfa
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -40
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LVL66
	.4byte	0x71e
	.4byte	0xd0e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x4
	.4byte	.LVL68
	.4byte	0xd79
	.4byte	0xd2e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x5
	.4byte	.LVL69
	.4byte	0x6fa
	.uleb128 0x5
	.4byte	.LVL70
	.4byte	0x70e
	.uleb128 0x4
	.4byte	.LVL75
	.4byte	0x733
	.4byte	0xd59
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x5
	.4byte	.LVL77
	.4byte	0x70e
	.uleb128 0x1c
	.4byte	.LVL79
	.4byte	0xb8d
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x17
	.4byte	0x402
	.uleb128 0x12
	.4byte	.LASF178
	.byte	0xd4
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xdfd
	.uleb128 0x13
	.4byte	.LASF154
	.byte	0xd4
	.byte	0x30
	.4byte	0x114
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x13
	.4byte	.LASF179
	.byte	0xd4
	.byte	0x49
	.4byte	0x72e
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1a
	.4byte	.LASF180
	.byte	0xd4
	.byte	0x5c
	.4byte	0x72e
	.4byte	.LLST14
	.uleb128 0x13
	.4byte	.LASF151
	.byte	0xd4
	.byte	0x7a
	.4byte	0x402
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1d
	.string	"i"
	.byte	0xd6
	.4byte	0x114
	.4byte	.LLST15
	.uleb128 0xb
	.4byte	.LASF181
	.byte	0xd6
	.byte	0x11
	.4byte	0x114
	.4byte	.LLST16
	.uleb128 0xb
	.4byte	.LASF182
	.byte	0xd7
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST17
	.uleb128 0xb
	.4byte	.LASF183
	.byte	0xd7
	.byte	0x2e
	.4byte	0x114
	.4byte	.LLST18
	.byte	0
	.uleb128 0x12
	.4byte	.LASF184
	.byte	0xc2
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe61
	.uleb128 0xe
	.4byte	.LASF185
	.byte	0xc4
	.byte	0x10
	.4byte	0x52e
	.uleb128 0x5
	.byte	0x3
	.4byte	is_init.0
	.uleb128 0x4
	.4byte	.LVL30
	.4byte	0x774
	.4byte	0xe35
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x44
	.byte	0
	.uleb128 0x4
	.4byte	.LVL31
	.4byte	0x75f
	.4byte	0xe51
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x44
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	gpt_interrupt_handler
	.byte	0
	.uleb128 0x1c
	.4byte	.LVL32
	.4byte	0x74f
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x44
	.byte	0
	.byte	0
	.uleb128 0x36
	.4byte	.LASF186
	.byte	0x1
	.byte	0x98
	.byte	0x6
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xece
	.uleb128 0x1a
	.4byte	.LASF187
	.byte	0x98
	.byte	0x2b
	.4byte	0xc7
	.4byte	.LLST2
	.uleb128 0x1d
	.string	"i"
	.byte	0x9a
	.4byte	0x114
	.4byte	.LLST3
	.uleb128 0xb
	.4byte	.LASF152
	.byte	0x9a
	.byte	0x11
	.4byte	0x114
	.4byte	.LLST4
	.uleb128 0xe
	.4byte	.LASF188
	.byte	0x9c
	.byte	0x17
	.4byte	0x120
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xe
	.4byte	.LASF189
	.byte	0x9d
	.byte	0x17
	.4byte	0x120
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1c
	.4byte	.LVL7
	.4byte	0x1095
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x12
	.4byte	.LASF190
	.byte	0x92
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xefd
	.uleb128 0x21
	.string	"gpt"
	.byte	0x92
	.byte	0x2c
	.4byte	0xefd
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x13
	.4byte	.LASF153
	.byte	0x92
	.byte	0x3a
	.4byte	0x114
	.uleb128 0x1
	.byte	0x5b
	.byte	0
	.uleb128 0x17
	.4byte	0x294
	.uleb128 0x22
	.4byte	.LASF191
	.byte	0x87
	.4byte	0x114
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf38
	.uleb128 0x29
	.string	"gpt"
	.byte	0x87
	.byte	0x36
	.4byte	0xefd
	.4byte	.LLST13
	.uleb128 0xe
	.4byte	.LASF153
	.byte	0x89
	.byte	0x17
	.4byte	0x120
	.uleb128 0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x12
	.4byte	.LASF192
	.byte	0x78
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf5a
	.uleb128 0x13
	.4byte	.LASF165
	.byte	0x78
	.byte	0x27
	.4byte	0x114
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x12
	.4byte	.LASF193
	.byte	0x64
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xfee
	.uleb128 0x21
	.string	"gpt"
	.byte	0x64
	.byte	0x25
	.4byte	0xefd
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x13
	.4byte	.LASF194
	.byte	0x64
	.byte	0x39
	.4byte	0x12a
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0xb
	.4byte	.LASF195
	.byte	0x66
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST8
	.uleb128 0xb
	.4byte	.LASF196
	.byte	0x67
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST9
	.uleb128 0xb
	.4byte	.LASF197
	.byte	0x68
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST10
	.uleb128 0x37
	.4byte	0x1077
	.4byte	.LBB10
	.4byte	.LBE10-.LBB10
	.byte	0x1
	.byte	0x69
	.byte	0xf
	.4byte	0xfd3
	.uleb128 0x23
	.4byte	0x1088
	.4byte	.LLST11
	.byte	0
	.uleb128 0x38
	.4byte	0x1077
	.4byte	.LBB12
	.4byte	.LBE12-.LBB12
	.byte	0x1
	.byte	0x6c
	.byte	0x11
	.uleb128 0x23
	.4byte	0x1088
	.4byte	.LLST12
	.byte	0
	.byte	0
	.uleb128 0x12
	.4byte	.LASF198
	.byte	0x59
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x102c
	.uleb128 0x21
	.string	"gpt"
	.byte	0x59
	.byte	0x2f
	.4byte	0xefd
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1a
	.4byte	.LASF199
	.byte	0x59
	.byte	0x3d
	.4byte	0x114
	.4byte	.LLST7
	.uleb128 0x13
	.4byte	.LASF200
	.byte	0x59
	.byte	0x54
	.4byte	0x114
	.uleb128 0x1
	.byte	0x5c
	.byte	0
	.uleb128 0x39
	.4byte	.LASF207
	.byte	0x1
	.byte	0x4f
	.byte	0x6
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF201
	.byte	0x49
	.4byte	0x114
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1077
	.uleb128 0x29
	.string	"ms"
	.byte	0x49
	.byte	0x2f
	.4byte	0x114
	.4byte	.LLST6
	.uleb128 0x5
	.4byte	.LVL16
	.4byte	0x10f5
	.uleb128 0x5
	.4byte	.LVL17
	.4byte	0x10f5
	.uleb128 0x5
	.4byte	.LVL19
	.4byte	0x10f5
	.byte	0
	.uleb128 0x3a
	.4byte	.LASF202
	.byte	0x1
	.byte	0x43
	.byte	0xa
	.4byte	0x114
	.byte	0x1
	.4byte	0x1095
	.uleb128 0x3b
	.string	"gpt"
	.byte	0x1
	.byte	0x43
	.byte	0x2c
	.4byte	0xefd
	.byte	0
	.uleb128 0x22
	.4byte	.LASF203
	.byte	0x37
	.4byte	0x114
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10c9
	.uleb128 0x1a
	.4byte	.LASF165
	.byte	0x37
	.byte	0x2f
	.4byte	0x2e4
	.4byte	.LLST0
	.uleb128 0x1d
	.string	"i"
	.byte	0x39
	.4byte	0x114
	.4byte	.LLST1
	.byte	0
	.uleb128 0x3c
	.4byte	0x1077
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10e6
	.uleb128 0x23
	.4byte	0x1088
	.4byte	.LLST5
	.byte	0
	.uleb128 0x3d
	.4byte	0x102c
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x3e
	.4byte	.LASF208
	.4byte	.LASF208
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xf
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
	.uleb128 0x10
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x17
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 13
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0x1c
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.uleb128 0x1e
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x28
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 28
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
	.uleb128 0x29
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x2c
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
	.uleb128 0x2d
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
	.uleb128 0x2e
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
	.uleb128 0x2f
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x21
	.byte	0
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
	.uleb128 0x34
	.uleb128 0xa
	.byte	0
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
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x83
	.uleb128 0x18
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
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
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x38
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
	.byte	0
	.byte	0
	.uleb128 0x39
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
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3a
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3b
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
	.byte	0
	.byte	0
	.uleb128 0x3c
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
	.uleb128 0x3d
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
	.uleb128 0x3e
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
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
.LLST42:
	.byte	0x6
	.4byte	.LVL139
	.byte	0x4
	.uleb128 .LVL139-.LVL139
	.uleb128 .LVL141-.LVL139
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL141-.LVL139
	.uleb128 .LFE20-.LVL139
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
.LLST43:
	.byte	0x6
	.4byte	.LVL139
	.byte	0x4
	.uleb128 .LVL139-.LVL139
	.uleb128 .LVL142-1-.LVL139
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL142-1-.LVL139
	.uleb128 .LVL144-.LVL139
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL144-.LVL139
	.uleb128 .LVL145-.LVL139
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
	.uleb128 .LVL145-.LVL139
	.uleb128 .LFE20-.LVL139
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST44:
	.byte	0x6
	.4byte	.LVL139
	.byte	0x4
	.uleb128 .LVL139-.LVL139
	.uleb128 .LVL142-1-.LVL139
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL142-1-.LVL139
	.uleb128 .LVL144-.LVL139
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL144-.LVL139
	.uleb128 .LVL145-.LVL139
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
	.uleb128 .LVL145-.LVL139
	.uleb128 .LFE20-.LVL139
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST45:
	.byte	0x6
	.4byte	.LVL140
	.byte	0x4
	.uleb128 .LVL140-.LVL140
	.uleb128 .LVL142-1-.LVL140
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL142-1-.LVL140
	.uleb128 .LVL144-.LVL140
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL144-.LVL140
	.uleb128 .LVL145-.LVL140
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
	.uleb128 .LVL145-.LVL140
	.uleb128 .LVL146-.LVL140
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL146-.LVL140
	.uleb128 .LFE20-.LVL140
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
	.byte	0
.LLST46:
	.byte	0x6
	.4byte	.LVL149
	.byte	0x4
	.uleb128 .LVL149-.LVL149
	.uleb128 .LVL151-.LVL149
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL151-.LVL149
	.uleb128 .LVL152-.LVL149
	.uleb128 0x8
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0x91
	.sleb128 -16
	.byte	0x6
	.byte	0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL155-.LVL149
	.uleb128 .LVL156-.LVL149
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST47:
	.byte	0x6
	.4byte	.LVL150
	.byte	0x4
	.uleb128 .LVL150-.LVL150
	.uleb128 .LVL151-.LVL150
	.uleb128 0x5
	.byte	0x7d
	.sleb128 0
	.byte	0x3f
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL151-.LVL150
	.uleb128 .LVL152-.LVL150
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST48:
	.byte	0x6
	.4byte	.LVL150
	.byte	0x4
	.uleb128 .LVL150-.LVL150
	.uleb128 .LVL151-.LVL150
	.uleb128 0x11
	.byte	0x7d
	.sleb128 0
	.byte	0xa
	.2byte	0x7fff
	.byte	0x1a
	.byte	0xa
	.2byte	0x3e8
	.byte	0x1e
	.byte	0x23
	.uleb128 0x4000
	.byte	0x3f
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL151-.LVL150
	.uleb128 .LVL152-.LVL150
	.uleb128 0x16
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0x91
	.sleb128 -16
	.byte	0x6
	.byte	0x1c
	.byte	0xa
	.2byte	0x7fff
	.byte	0x1a
	.byte	0xa
	.2byte	0x3e8
	.byte	0x1e
	.byte	0x23
	.uleb128 0x4000
	.byte	0x3f
	.byte	0x25
	.byte	0x9f
	.byte	0
.LLST49:
	.byte	0x6
	.4byte	.LVL150
	.byte	0x4
	.uleb128 .LVL150-.LVL150
	.uleb128 .LVL151-.LVL150
	.uleb128 0x1a
	.byte	0x7d
	.sleb128 0
	.byte	0x3f
	.byte	0x25
	.byte	0xa
	.2byte	0x3e8
	.byte	0x1e
	.byte	0x7d
	.sleb128 0
	.byte	0xa
	.2byte	0x7fff
	.byte	0x1a
	.byte	0xa
	.2byte	0x3e8
	.byte	0x1e
	.byte	0x23
	.uleb128 0x4000
	.byte	0x3f
	.byte	0x25
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL151-.LVL150
	.uleb128 .LVL152-.LVL150
	.uleb128 0x24
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0x91
	.sleb128 -16
	.byte	0x6
	.byte	0x1c
	.byte	0x3f
	.byte	0x25
	.byte	0xa
	.2byte	0x3e8
	.byte	0x1e
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0x91
	.sleb128 -16
	.byte	0x6
	.byte	0x1c
	.byte	0xa
	.2byte	0x7fff
	.byte	0x1a
	.byte	0xa
	.2byte	0x3e8
	.byte	0x1e
	.byte	0x23
	.uleb128 0x4000
	.byte	0x3f
	.byte	0x25
	.byte	0x22
	.byte	0x9f
	.byte	0
.LLST50:
	.byte	0x8
	.4byte	.LVL152
	.uleb128 .LVL153-.LVL152
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST51:
	.byte	0x6
	.4byte	.LVL146
	.byte	0x4
	.uleb128 .LVL146-.LVL146
	.uleb128 .LVL147-1-.LVL146
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL147-1-.LVL146
	.uleb128 .LFE20-.LVL146
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST37:
	.byte	0x6
	.4byte	.LVL112
	.byte	0x4
	.uleb128 .LVL112-.LVL112
	.uleb128 .LVL115-.LVL112
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL115-.LVL112
	.uleb128 .LFE19-.LVL112
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
	.4byte	.LVL112
	.byte	0x4
	.uleb128 .LVL112-.LVL112
	.uleb128 .LVL118-.LVL112
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL118-.LVL112
	.uleb128 .LVL128-.LVL112
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL128-.LVL112
	.uleb128 .LVL129-.LVL112
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
	.uleb128 .LVL129-.LVL112
	.uleb128 .LVL138-.LVL112
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL138-.LVL112
	.uleb128 .LFE19-.LVL112
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST39:
	.byte	0x6
	.4byte	.LVL113
	.byte	0x4
	.uleb128 .LVL113-.LVL113
	.uleb128 .LVL116-.LVL113
	.uleb128 0x5
	.byte	0x79
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL116-.LVL113
	.uleb128 .LVL124-.LVL113
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL124-.LVL113
	.uleb128 .LVL129-.LVL113
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
	.uleb128 .LVL129-.LVL113
	.uleb128 .LVL132-.LVL113
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL132-.LVL113
	.uleb128 .LVL136-.LVL113
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
	.uleb128 .LVL136-.LVL113
	.uleb128 .LVL138-.LVL113
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL138-.LVL113
	.uleb128 .LFE19-.LVL113
	.uleb128 0x5
	.byte	0x79
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x9f
	.byte	0
.LLST40:
	.byte	0x6
	.4byte	.LVL135
	.byte	0x4
	.uleb128 .LVL135-.LVL135
	.uleb128 .LVL136-.LVL135
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL136-.LVL135
	.uleb128 .LVL138-.LVL135
	.uleb128 0x3
	.byte	0x9
	.byte	0xfd
	.byte	0x9f
	.byte	0
.LLST41:
	.byte	0x6
	.4byte	.LVL114
	.byte	0x4
	.uleb128 .LVL114-.LVL114
	.uleb128 .LVL117-.LVL114
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL117-.LVL114
	.uleb128 .LVL120-.LVL114
	.uleb128 0x2
	.byte	0x35
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL121-.LVL114
	.uleb128 .LVL122-1-.LVL114
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL122-1-.LVL114
	.uleb128 .LVL125-.LVL114
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL129-.LVL114
	.uleb128 .LVL130-.LVL114
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL130-.LVL114
	.uleb128 .LVL132-.LVL114
	.uleb128 0x2
	.byte	0x36
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL132-.LVL114
	.uleb128 .LVL133-.LVL114
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL136-.LVL114
	.uleb128 .LVL138-.LVL114
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL138-.LVL114
	.uleb128 .LFE19-.LVL114
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0
.LLST28:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL84-.LVL80
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL84-.LVL80
	.uleb128 .LFE18-.LVL80
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
.LLST29:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL86-.LVL80
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL86-.LVL80
	.uleb128 .LVL90-.LVL80
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL90-.LVL80
	.uleb128 .LVL98-.LVL80
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
	.uleb128 .LVL98-.LVL80
	.uleb128 .LVL104-.LVL80
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL104-.LVL80
	.uleb128 .LVL110-.LVL80
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
	.uleb128 .LVL110-.LVL80
	.uleb128 .LVL111-.LVL80
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL111-.LVL80
	.uleb128 .LFE18-.LVL80
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST30:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL88-1-.LVL80
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL88-1-.LVL80
	.uleb128 .LVL97-.LVL80
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0x4
	.uleb128 .LVL97-.LVL80
	.uleb128 .LVL98-.LVL80
	.uleb128 0x2
	.byte	0x72
	.sleb128 -40
	.byte	0x4
	.uleb128 .LVL98-.LVL80
	.uleb128 .LVL100-1-.LVL80
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL100-1-.LVL80
	.uleb128 .LVL110-.LVL80
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0x4
	.uleb128 .LVL110-.LVL80
	.uleb128 .LFE18-.LVL80
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST31:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL88-1-.LVL80
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL88-1-.LVL80
	.uleb128 .LVL97-.LVL80
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0x4
	.uleb128 .LVL97-.LVL80
	.uleb128 .LVL98-.LVL80
	.uleb128 0x2
	.byte	0x72
	.sleb128 -36
	.byte	0x4
	.uleb128 .LVL98-.LVL80
	.uleb128 .LVL100-1-.LVL80
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL100-1-.LVL80
	.uleb128 .LVL110-.LVL80
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0x4
	.uleb128 .LVL110-.LVL80
	.uleb128 .LFE18-.LVL80
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST32:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL85-.LVL80
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL85-.LVL80
	.uleb128 .LVL96-.LVL80
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL96-.LVL80
	.uleb128 .LVL98-.LVL80
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xe
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL98-.LVL80
	.uleb128 .LVL107-.LVL80
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL107-.LVL80
	.uleb128 .LVL111-.LVL80
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xe
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL111-.LVL80
	.uleb128 .LFE18-.LVL80
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST33:
	.byte	0x6
	.4byte	.LVL81
	.byte	0x4
	.uleb128 .LVL81-.LVL81
	.uleb128 .LVL83-.LVL81
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL83-.LVL81
	.uleb128 .LVL96-.LVL81
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL96-.LVL81
	.uleb128 .LVL98-.LVL81
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
	.uleb128 .LVL98-.LVL81
	.uleb128 .LVL100-1-.LVL81
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL100-1-.LVL81
	.uleb128 .LVL105-.LVL81
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL105-.LVL81
	.uleb128 .LVL110-.LVL81
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
	.uleb128 .LVL110-.LVL81
	.uleb128 .LVL111-.LVL81
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL111-.LVL81
	.uleb128 .LFE18-.LVL81
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST34:
	.byte	0x6
	.4byte	.LVL93
	.byte	0x4
	.uleb128 .LVL93-.LVL93
	.uleb128 .LVL96-.LVL93
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL104-.LVL93
	.uleb128 .LVL110-.LVL93
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST35:
	.byte	0x6
	.4byte	.LVL82
	.byte	0x4
	.uleb128 .LVL82-.LVL82
	.uleb128 .LVL90-.LVL82
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL90-.LVL82
	.uleb128 .LVL91-.LVL82
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL92-.LVL82
	.uleb128 .LVL93-.LVL82
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL98-.LVL82
	.uleb128 .LVL103-.LVL82
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL103-.LVL82
	.uleb128 .LVL104-.LVL82
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL110-.LVL82
	.uleb128 .LFE18-.LVL82
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST36:
	.byte	0x6
	.4byte	.LVL82
	.byte	0x4
	.uleb128 .LVL82-.LVL82
	.uleb128 .LVL87-.LVL82
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL87-.LVL82
	.uleb128 .LVL91-.LVL82
	.uleb128 0x2
	.byte	0x35
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL92-.LVL82
	.uleb128 .LVL94-1-.LVL82
	.uleb128 0x1
	.byte	0x56
	.byte	0x4
	.uleb128 .LVL94-1-.LVL82
	.uleb128 .LVL96-.LVL82
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x4
	.uleb128 .LVL98-.LVL82
	.uleb128 .LVL99-.LVL82
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL99-.LVL82
	.uleb128 .LVL104-.LVL82
	.uleb128 0x2
	.byte	0x36
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL104-.LVL82
	.uleb128 .LVL110-.LVL82
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x4
	.uleb128 .LVL110-.LVL82
	.uleb128 .LFE18-.LVL82
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL45
	.byte	0x4
	.uleb128 .LVL45-.LVL45
	.uleb128 .LVL46-.LVL45
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL46-.LVL45
	.uleb128 .LVL50-.LVL45
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL50-.LVL45
	.uleb128 .LVL51-.LVL45
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
	.uleb128 .LVL51-.LVL45
	.uleb128 .LFE17-.LVL45
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST20:
	.byte	0x6
	.4byte	.LVL45
	.byte	0x4
	.uleb128 .LVL45-.LVL45
	.uleb128 .LVL47-1-.LVL45
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL47-1-.LVL45
	.uleb128 .LVL49-.LVL45
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL49-.LVL45
	.uleb128 .LVL51-.LVL45
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
	.uleb128 .LVL51-.LVL45
	.uleb128 .LFE17-.LVL45
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST21:
	.byte	0x6
	.4byte	.LVL52
	.byte	0x4
	.uleb128 .LVL52-.LVL52
	.uleb128 .LVL54-.LVL52
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL54-.LVL52
	.uleb128 .LFE16-.LVL52
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
.LLST22:
	.byte	0x8
	.4byte	.LVL58
	.uleb128 .LVL59-.LVL58
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST23:
	.byte	0x6
	.4byte	.LVL61
	.byte	0x4
	.uleb128 .LVL61-.LVL61
	.uleb128 .LVL63-1-.LVL61
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL63-1-.LVL61
	.uleb128 .LVL65-.LVL61
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
.LLST24:
	.byte	0x6
	.4byte	.LVL62
	.byte	0x4
	.uleb128 .LVL62-.LVL62
	.uleb128 .LVL63-1-.LVL62
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL63-1-.LVL62
	.uleb128 .LVL65-.LVL62
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
.LLST25:
	.byte	0x6
	.4byte	.LVL53
	.byte	0x4
	.uleb128 .LVL53-.LVL53
	.uleb128 .LVL54-.LVL53
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL54-.LVL53
	.uleb128 .LVL55-.LVL53
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL55-.LVL53
	.uleb128 .LVL57-.LVL53
	.uleb128 0x2
	.byte	0x35
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL58-.LVL53
	.uleb128 .LVL72-.LVL53
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL72-.LVL53
	.uleb128 .LVL73-.LVL53
	.uleb128 0x2
	.byte	0x72
	.sleb128 -44
	.byte	0x4
	.uleb128 .LVL73-.LVL53
	.uleb128 .LVL74-.LVL53
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL74-.LVL53
	.uleb128 .LVL76-.LVL53
	.uleb128 0x2
	.byte	0x36
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL76-.LVL53
	.uleb128 .LFE16-.LVL53
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST26:
	.byte	0x6
	.4byte	.LVL53
	.byte	0x4
	.uleb128 .LVL53-.LVL53
	.uleb128 .LVL71-.LVL53
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL73-.LVL53
	.uleb128 .LFE16-.LVL53
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST27:
	.byte	0x6
	.4byte	.LVL58
	.byte	0x4
	.uleb128 .LVL58-.LVL58
	.uleb128 .LVL59-.LVL58
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL59-.LVL58
	.uleb128 .LVL62-.LVL58
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0x4
	.uleb128 .LVL62-.LVL58
	.uleb128 .LVL65-.LVL58
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL65-.LVL58
	.uleb128 .LVL67-.LVL58
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0x4
	.uleb128 .LVL76-.LVL58
	.uleb128 .LVL78-.LVL58
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LVL42-.LVL33
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL42-.LVL33
	.uleb128 .LVL43-.LVL33
	.uleb128 0x2
	.byte	0x72
	.sleb128 -12
	.byte	0x4
	.uleb128 .LVL43-.LVL33
	.uleb128 .LFE15-.LVL33
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LVL39-.LVL33
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL43-.LVL33
	.uleb128 .LFE15-.LVL33
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST16:
	.byte	0x6
	.4byte	.LVL35
	.byte	0x4
	.uleb128 .LVL35-.LVL35
	.uleb128 .LVL37-.LVL35
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL43-.LVL35
	.uleb128 .LFE15-.LVL35
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST17:
	.byte	0x6
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x3
	.byte	0x9
	.byte	0xff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LVL44-.LVL33
	.uleb128 0x1
	.byte	0x56
	.byte	0
.LLST18:
	.byte	0x6
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x2
	.byte	0x3a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LVL36-.LVL33
	.uleb128 0x1
	.byte	0x57
	.byte	0x4
	.uleb128 .LVL37-.LVL33
	.uleb128 .LVL39-.LVL33
	.uleb128 0x1
	.byte	0x57
	.byte	0x4
	.uleb128 .LVL39-.LVL33
	.uleb128 .LVL40-.LVL33
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL40-.LVL33
	.uleb128 .LVL41-.LVL33
	.uleb128 0x2
	.byte	0x7b
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL43-.LVL33
	.uleb128 .LFE15-.LVL33
	.uleb128 0x1
	.byte	0x57
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
	.uleb128 .LVL6-.LVL5
	.uleb128 .LFE13-.LVL5
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
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL6-.LVL5
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL6-.LVL5
	.uleb128 .LVL11-.LVL5
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST4:
	.byte	0x8
	.4byte	.LVL7
	.uleb128 .LVL8-.LVL7
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL27
	.byte	0x4
	.uleb128 .LVL27-.LVL27
	.uleb128 .LVL28-.LVL27
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL28-.LVL27
	.uleb128 .LFE11-.LVL27
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
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL23-.LVL22
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL23-.LVL22
	.uleb128 .LFE9-.LVL22
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL23-.LVL22
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL24-.LVL22
	.uleb128 .LVL25-.LVL22
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL24-.LVL22
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL24-.LVL22
	.uleb128 .LVL25-.LVL22
	.uleb128 0x6
	.byte	0x7f
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL25-.LVL22
	.uleb128 .LFE9-.LVL22
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST11:
	.byte	0x8
	.4byte	.LVL22
	.uleb128 .LVL23-.LVL22
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST12:
	.byte	0x8
	.4byte	.LVL23
	.uleb128 .LVL24-.LVL23
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL20
	.byte	0x4
	.uleb128 .LVL20-.LVL20
	.uleb128 .LVL21-.LVL20
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL21-.LVL20
	.uleb128 .LFE8-.LVL20
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
.LLST6:
	.byte	0x6
	.4byte	.LVL14
	.byte	0x4
	.uleb128 .LVL14-.LVL14
	.uleb128 .LVL15-.LVL14
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL15-.LVL14
	.uleb128 .LVL18-.LVL14
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL18-.LVL14
	.uleb128 .LFE6-.LVL14
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
.LLST0:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL2-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL2-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL4-.LVL0
	.uleb128 .LFE4-.LVL0
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL1-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL1-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL13-.LVL12
	.uleb128 .LFE5-.LVL12
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
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
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
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
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
.LLRL52:
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
	.byte	0x7
	.4byte	.LFB13
	.uleb128 .LFE13-.LFB13
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
	.4byte	.LFB14
	.uleb128 .LFE14-.LFB14
	.byte	0x7
	.4byte	.LFB15
	.uleb128 .LFE15-.LFB15
	.byte	0x7
	.4byte	.LFB17
	.uleb128 .LFE17-.LFB17
	.byte	0x7
	.4byte	.LFB16
	.uleb128 .LFE16-.LFB16
	.byte	0x7
	.4byte	.LFB18
	.uleb128 .LFE18-.LFB18
	.byte	0x7
	.4byte	.LFB19
	.uleb128 .LFE19-.LFB19
	.byte	0x7
	.4byte	.LFB20
	.uleb128 .LFE20-.LFB20
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF208:
	.string	"__udivsi3"
.LASF162:
	.string	"next_index"
.LASF194:
	.string	"count"
.LASF140:
	.string	"sw_gpt_us_locksleep_status"
.LASF9:
	.string	"SPI_MST1_IRQn"
.LASF96:
	.string	"GPT_CLOCK_GATE"
.LASF111:
	.string	"GPT_DIVIDE_32"
.LASF18:
	.string	"SPI_MST0_IRQn"
.LASF136:
	.string	"gpt_context_mapping"
.LASF182:
	.string	"the_minimum_count"
.LASF143:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF106:
	.string	"GPT_DIVIDE_10"
.LASF100:
	.string	"GPT_DIVIDE_4"
.LASF65:
	.string	"hal_gpt_port_t"
.LASF109:
	.string	"GPT_DIVIDE_13"
.LASF204:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF184:
	.string	"gpt_nvic_register"
.LASF193:
	.string	"gpt_delay_time"
.LASF93:
	.string	"GPT_MODE_KEEP_GO"
.LASF168:
	.string	"timeout_tick"
.LASF95:
	.string	"GPT_CLOCK_UNGATE"
.LASF166:
	.string	"sw_gpt_timer_start"
.LASF2:
	.string	"long long unsigned int"
.LASF87:
	.string	"SW_GPT_MS_TYPE"
.LASF122:
	.string	"SW_GPT_NOTE_STATUS_OF_FREE"
.LASF6:
	.string	"QDEC_IRQn"
.LASF186:
	.string	"gpt_interrupt_handler"
.LASF191:
	.string	"gpt_save_and_mask_interrupt"
.LASF200:
	.string	"divide"
.LASF91:
	.string	"GPT_MODE_ONE_SHOT"
.LASF89:
	.string	"SW_GPT_MAX_TYPE"
.LASF37:
	.string	"GPT_WAKEUPMSK0"
.LASF38:
	.string	"GPT_WAKEUPMSK1"
.LASF28:
	.string	"long long int"
.LASF25:
	.string	"signed char"
.LASF114:
	.string	"user_data"
.LASF119:
	.string	"is_gpt_locked_sleep"
.LASF47:
	.string	"GPT_CON_UNION"
.LASF118:
	.string	"has_initilized"
.LASF8:
	.string	"UART_IRQn"
.LASF53:
	.string	"GPT_COUNT"
.LASF185:
	.string	"is_init"
.LASF188:
	.string	"state"
.LASF7:
	.string	"KEYSCAN_IRQn"
.LASF27:
	.string	"long int"
.LASF157:
	.string	"time_ms"
.LASF174:
	.string	"temp_callback"
.LASF81:
	.string	"hal_gpt_running_status_t"
.LASF88:
	.string	"SW_GPT_US_TYPE"
.LASF3:
	.string	"unsigned int"
.LASF163:
	.string	"next_count"
.LASF97:
	.string	"GPT_DIVIDE_1"
.LASF98:
	.string	"GPT_DIVIDE_2"
.LASF99:
	.string	"GPT_DIVIDE_3"
.LASF189:
	.string	"enable"
.LASF101:
	.string	"GPT_DIVIDE_5"
.LASF102:
	.string	"GPT_DIVIDE_6"
.LASF103:
	.string	"GPT_DIVIDE_7"
.LASF104:
	.string	"GPT_DIVIDE_8"
.LASF105:
	.string	"GPT_DIVIDE_9"
.LASF49:
	.string	"GPT_CLK"
.LASF121:
	.string	"gpt_context_t"
.LASF155:
	.string	"remain_count"
.LASF116:
	.string	"running_status"
.LASF48:
	.string	"GPT_CLR"
.LASF147:
	.string	"hal_nvic_register_isr_handler"
.LASF41:
	.string	"GPT_REGISTER_GLOABL_T"
.LASF16:
	.string	"I3C0_IRQn"
.LASF131:
	.string	"used_timer_count"
.LASF148:
	.string	"hal_nvic_disable_irq"
.LASF170:
	.string	"port"
.LASF15:
	.string	"EINT_IRQn"
.LASF17:
	.string	"I3C0_DMA_IRQn"
.LASF72:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF117:
	.string	"callback_context"
.LASF70:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF80:
	.string	"HAL_GPT_RUNNING"
.LASF33:
	.string	"long unsigned int"
.LASF64:
	.string	"HAL_GPT_MAX"
.LASF173:
	.string	"sw_gpt_type_port"
.LASF84:
	.string	"HAL_SLEEP_MANAGER_ERROR"
.LASF79:
	.string	"HAL_GPT_STOPPED"
.LASF167:
	.string	"timeout_time"
.LASF36:
	.string	"GPT_IRQMSK1"
.LASF158:
	.string	"remain_time_ms"
.LASF31:
	.string	"short unsigned int"
.LASF20:
	.string	"USB_IRQn"
.LASF113:
	.string	"callback"
.LASF112:
	.string	"GPT_DIVIDE_64"
.LASF203:
	.string	"gpt_get_context_index"
.LASF159:
	.string	"remain_time_us"
.LASF75:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF145:
	.string	"hal_gpt_get_free_run_count"
.LASF67:
	.string	"HAL_GPT_CLOCK_SOURCE_1M"
.LASF115:
	.string	"gpt_callback_context_t"
.LASF180:
	.string	"p_expire_count"
.LASF206:
	.string	"Reget_current_count"
.LASF69:
	.string	"hal_gpt_callback_t"
.LASF205:
	.string	"IRQn"
.LASF71:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF198:
	.string	"gpt_start_free_run_timer"
.LASF5:
	.string	"LED_IRQn"
.LASF150:
	.string	"remain_time"
.LASF77:
	.string	"HAL_GPT_STATUS_OK"
.LASF130:
	.string	"sw_gpt_timer"
.LASF11:
	.string	"GPT_IRQn"
.LASF4:
	.string	"SW_IRQn"
.LASF201:
	.string	"gpt_convert_ms_to_32k_count"
.LASF55:
	.string	"GPT_REGISTER_T"
.LASF92:
	.string	"GPT_MODE_REPEAT"
.LASF176:
	.string	"sw_gpt_type"
.LASF179:
	.string	"p_index"
.LASF139:
	.string	"g_sw_gpt_running_note"
.LASF183:
	.string	"the_minimum_note"
.LASF156:
	.string	"time_s"
.LASF126:
	.string	"expire_count"
.LASF144:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF154:
	.string	"current_count"
.LASF199:
	.string	"clock_source"
.LASF146:
	.string	"hal_nvic_enable_irq"
.LASF124:
	.string	"SW_GPT_NOTE_STATUS_OF_RUNING"
.LASF164:
	.string	"ret_status"
.LASF51:
	.string	"GPT_IRQ_STA"
.LASF12:
	.string	"UART_DMA_IRQn"
.LASF128:
	.string	"timer_port_type"
.LASF39:
	.string	"GPT_CLRSTA"
.LASF178:
	.string	"sw_gpt_find_the_next_expire_time"
.LASF120:
	.string	"_Bool"
.LASF46:
	.string	"GPT_CON"
.LASF135:
	.string	"hal_nvic_isr_t"
.LASF52:
	.string	"GPT_IRQ_ACK"
.LASF26:
	.string	"short int"
.LASF133:
	.string	"g_gpt_context"
.LASF13:
	.string	"PMU_IRQn"
.LASF14:
	.string	"MCU_DMA_IRQn"
.LASF138:
	.string	"g_sw_gpt_notes"
.LASF175:
	.string	"temp_user_data"
.LASF54:
	.string	"GPT_COMPARE"
.LASF142:
	.string	"hal_sleep_manager_unlock_sleep"
.LASF171:
	.string	"clear_gpt_and_restart_hw_gpt"
.LASF35:
	.string	"GPT_IRQMSK0"
.LASF74:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF45:
	.string	"GPT_CON_CELLS"
.LASF195:
	.string	"current"
.LASF125:
	.string	"sw_gpt_note_status_t"
.LASF23:
	.string	"IRQn_Type"
.LASF66:
	.string	"HAL_GPT_CLOCK_SOURCE_32K"
.LASF50:
	.string	"GPT_IRQ_EN"
.LASF32:
	.string	"uint32_t"
.LASF196:
	.string	"temp0"
.LASF172:
	.string	"sw_gpt_callback"
.LASF82:
	.string	"long double"
.LASF83:
	.string	"char"
.LASF90:
	.string	"sw_gpt_type_t"
.LASF107:
	.string	"GPT_DIVIDE_11"
.LASF108:
	.string	"GPT_DIVIDE_12"
.LASF192:
	.string	"gpt_reset_default_timer"
.LASF161:
	.string	"sw_gpt_timer_stop"
.LASF110:
	.string	"GPT_DIVIDE_16"
.LASF190:
	.string	"gpt_restore_interrupt"
.LASF19:
	.string	"IRQ_GEN_IRQn"
.LASF141:
	.string	"hal_sleep_manager_lock_sleep"
.LASF137:
	.string	"gpt_lock_sleep_handle"
.LASF152:
	.string	"index"
.LASF40:
	.string	"GPT_WCOMPSTA"
.LASF44:
	.string	"RESERVED"
.LASF42:
	.string	"MODE"
.LASF29:
	.string	"uint8_t"
.LASF123:
	.string	"SW_GPT_NOTE_STATUS_OF_ALLOC"
.LASF21:
	.string	"BT_IRQn"
.LASF43:
	.string	"SW_CG"
.LASF151:
	.string	"sw_type"
.LASF86:
	.string	"hal_sleep_manager_status_t"
.LASF63:
	.string	"HAL_GPT_MAX_PORT"
.LASF30:
	.string	"unsigned char"
.LASF169:
	.string	"next_expired_count"
.LASF85:
	.string	"HAL_SLEEP_MANAGER_OK"
.LASF129:
	.string	"sw_gpt_note_t"
.LASF73:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF76:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF34:
	.string	"GPT_IRQSTA"
.LASF177:
	.string	"expired_flag"
.LASF160:
	.string	"sw_gpt_get_remaining_time"
.LASF207:
	.string	"gpt_open_clock_source"
.LASF165:
	.string	"gpt_port"
.LASF153:
	.string	"mask"
.LASF127:
	.string	"status"
.LASF56:
	.string	"HAL_GPT_0"
.LASF57:
	.string	"HAL_GPT_1"
.LASF58:
	.string	"HAL_GPT_2"
.LASF59:
	.string	"HAL_GPT_3"
.LASF60:
	.string	"HAL_GPT_4"
.LASF61:
	.string	"HAL_GPT_5"
.LASF62:
	.string	"HAL_GPT_6"
.LASF181:
	.string	"temp_count"
.LASF94:
	.string	"GPT_MODE_FREE_RUN"
.LASF202:
	.string	"gpt_current_count"
.LASF149:
	.string	"handle"
.LASF24:
	.string	"hal_nvic_irq_t"
.LASF132:
	.string	"sw_gpt_add_note_t"
.LASF10:
	.string	"RTC_IRQn"
.LASF187:
	.string	"irq_number"
.LASF197:
	.string	"temp1"
.LASF134:
	.string	"gpt_running_state"
.LASF68:
	.string	"hal_gpt_clock_source_t"
.LASF78:
	.string	"hal_gpt_status_t"
.LASF22:
	.string	"IRQ_NUMBER_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_gpt_internal.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
