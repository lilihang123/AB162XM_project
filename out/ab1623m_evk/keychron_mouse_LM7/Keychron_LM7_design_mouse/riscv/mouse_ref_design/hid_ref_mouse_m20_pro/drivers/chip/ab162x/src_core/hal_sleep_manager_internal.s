	.file	"hal_sleep_manager_internal.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c"
	.section	.text.sleep_management_enter_sleep,"ax",@progbits
	.align	1
	.globl	sleep_management_enter_sleep
	.hidden	sleep_management_enter_sleep
	.type	sleep_management_enter_sleep, @function
sleep_management_enter_sleep:
.LFB4:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c"
	.loc 1 163 1
	.cfi_startproc
	.loc 1 165 5
 #APP
# 165 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	wfi
nop

# 0 "" 2
	.loc 1 170 1 is_stmt 0
 #NO_APP
	ret
	.cfi_endproc
.LFE4:
	.size	sleep_management_enter_sleep, .-sleep_management_enter_sleep
	.section	.text.sleep_management_register_suspend_callback,"ax",@progbits
	.align	1
	.globl	sleep_management_register_suspend_callback
	.hidden	sleep_management_register_suspend_callback
	.type	sleep_management_register_suspend_callback, @function
sleep_management_register_suspend_callback:
.LFB6:
	.loc 1 230 1 is_stmt 1
	.cfi_startproc
.LVL0:
	.loc 1 231 5
	.loc 1 231 8 is_stmt 0
	li	a5,4
	bne	a0,a5,.L3
	.loc 1 232 9 is_stmt 1
	.loc 1 232 41 is_stmt 0
	lla	a0,suspend_user_register_count
.LVL1:
	lw	a5,0(a0)
	.loc 1 232 12
	li	a4,2
	bgtu	a5,a4,.L4
	.loc 1 233 13 is_stmt 1
	.loc 1 233 80 is_stmt 0
	slli	a3,a5,1
	add	a3,a3,a5
	slli	a3,a3,2
	lla	a4,suspend_user_callback_func_table
	add	a4,a4,a3
	.loc 1 236 40
	addi	a5,a5,1
	.loc 1 235 87
	li	a3,1
	.loc 1 233 80
	sw	a1,0(a4)
	.loc 1 234 13 is_stmt 1
	.loc 1 234 80 is_stmt 0
	sw	a2,4(a4)
	.loc 1 235 13 is_stmt 1
	.loc 1 235 87 is_stmt 0
	sb	a3,8(a4)
	.loc 1 236 13 is_stmt 1
	.loc 1 236 40 is_stmt 0
	sw	a5,0(a0)
	ret
.L4:
	.loc 1 238 13 is_stmt 1
.LBB2:
	.loc 1 238 18
	.loc 1 238 71
	.loc 1 238 238
	li	a3,0
	lla	a2,msg_id_string.17
.LVL2:
	li	a1,3
.LVL3:
	lla	a0,log_control_block_common
	tail	print_module_msgid_log
.LVL4:
.L3:
.LBE2:
	.loc 1 241 9
	.loc 1 241 50 is_stmt 0
	slli	a4,a0,1
	add	a4,a4,a0
	slli	a4,a4,2
	lla	a5,suspend_callback_func_table
	add	a5,a5,a4
	.loc 1 243 57
	li	a4,1
	.loc 1 241 50
	sw	a1,0(a5)
	.loc 1 242 9 is_stmt 1
	.loc 1 242 50 is_stmt 0
	sw	a2,4(a5)
	.loc 1 243 9 is_stmt 1
	.loc 1 243 57 is_stmt 0
	sb	a4,8(a5)
	.loc 1 245 1
	ret
	.cfi_endproc
.LFE6:
	.size	sleep_management_register_suspend_callback, .-sleep_management_register_suspend_callback
	.section	.text.sleep_management_register_resume_callback,"ax",@progbits
	.align	1
	.globl	sleep_management_register_resume_callback
	.hidden	sleep_management_register_resume_callback
	.type	sleep_management_register_resume_callback, @function
sleep_management_register_resume_callback:
.LFB7:
	.loc 1 248 1 is_stmt 1
	.cfi_startproc
.LVL5:
	.loc 1 249 5
	.loc 1 249 8 is_stmt 0
	li	a5,4
	bne	a0,a5,.L7
	.loc 1 250 9 is_stmt 1
	.loc 1 250 40 is_stmt 0
	lla	a0,resume_user_register_count
.LVL6:
	lw	a5,0(a0)
	.loc 1 250 12
	li	a4,2
	bgtu	a5,a4,.L8
	.loc 1 251 13 is_stmt 1
	.loc 1 251 78 is_stmt 0
	slli	a3,a5,1
	add	a3,a3,a5
	slli	a3,a3,2
	lla	a4,resume_user_callback_func_table
	add	a4,a4,a3
	.loc 1 254 39
	addi	a5,a5,1
	.loc 1 253 85
	li	a3,1
	.loc 1 251 78
	sw	a1,0(a4)
	.loc 1 252 13 is_stmt 1
	.loc 1 252 78 is_stmt 0
	sw	a2,4(a4)
	.loc 1 253 13 is_stmt 1
	.loc 1 253 85 is_stmt 0
	sb	a3,8(a4)
	.loc 1 254 13 is_stmt 1
	.loc 1 254 39 is_stmt 0
	sw	a5,0(a0)
	ret
.L8:
	.loc 1 256 13 is_stmt 1
.LBB3:
	.loc 1 256 18
	.loc 1 256 71
	.loc 1 256 237
	li	a3,0
	lla	a2,msg_id_string.16
.LVL7:
	li	a1,3
.LVL8:
	lla	a0,log_control_block_common
	tail	print_module_msgid_log
.LVL9:
.L7:
.LBE3:
	.loc 1 259 9
	.loc 1 259 49 is_stmt 0
	slli	a4,a0,1
	add	a4,a4,a0
	slli	a4,a4,2
	lla	a5,resume_callback_func_table
	add	a5,a5,a4
	.loc 1 261 56
	li	a4,1
	.loc 1 259 49
	sw	a1,0(a5)
	.loc 1 260 9 is_stmt 1
	.loc 1 260 49 is_stmt 0
	sw	a2,4(a5)
	.loc 1 261 9 is_stmt 1
	.loc 1 261 56 is_stmt 0
	sb	a4,8(a5)
	.loc 1 263 1
	ret
	.cfi_endproc
.LFE7:
	.size	sleep_management_register_resume_callback, .-sleep_management_register_resume_callback
	.section	.text.sleep_management_suspend_callback,"ax",@progbits
	.align	1
	.globl	sleep_management_suspend_callback
	.hidden	sleep_management_suspend_callback
	.type	sleep_management_suspend_callback, @function
sleep_management_suspend_callback:
.LFB8:
	.loc 1 266 1 is_stmt 1
	.cfi_startproc
	.loc 1 267 5
	.loc 1 269 5
	.loc 1 266 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	sw	s1,0(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 269 5
	li	a5,0
	.loc 1 269 12
	lla	s0,i.1
.L11:
	sw	a5,0(s0)
	.loc 1 269 19 is_stmt 1 discriminator 1
	li	a4,2
	bleu	a5,a4,.L13
	li	a4,0
	.loc 1 285 48 is_stmt 0
	lla	s1,suspend_user_callback_func_table
.L14:
	.loc 1 284 12
	sw	a4,0(s0)
	.loc 1 284 19 is_stmt 1 discriminator 1
	li	a5,2
	bleu	a4,a5,.L16
	.loc 1 298 1 is_stmt 0
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
.L13:
	.cfi_restore_state
	.loc 1 270 9 is_stmt 1
	.loc 1 270 43 is_stmt 0
	slli	a4,a5,1
	add	a4,a4,a5
	slli	a4,a4,2
	lla	a5,suspend_callback_func_table
	add	a5,a5,a4
	.loc 1 270 12
	lbu	a4,8(a5)
	beq	a4,zero,.L12
	.loc 1 276 13 is_stmt 1
	lw	a4,0(a5)
	lw	a0,4(a5)
	jalr	a4
.LVL10:
.L12:
	.loc 1 269 55 discriminator 2
	lw	a5,0(s0)
	addi	a5,a5,1
	j	.L11
.L16:
	.loc 1 285 9
	.loc 1 285 48 is_stmt 0
	slli	a5,a4,1
	add	a5,a5,a4
	slli	a5,a5,2
	add	a5,s1,a5
	.loc 1 285 12
	lbu	a4,8(a5)
	beq	a4,zero,.L15
	.loc 1 291 13 is_stmt 1
	lw	a4,0(a5)
	lw	a0,4(a5)
	jalr	a4
.LVL11:
.L15:
	.loc 1 284 25 discriminator 2
	lw	a4,0(s0)
	addi	a4,a4,1
	j	.L14
	.cfi_endproc
.LFE8:
	.size	sleep_management_suspend_callback, .-sleep_management_suspend_callback
	.section	.text.sleep_management_resume_callback,"ax",@progbits
	.align	1
	.globl	sleep_management_resume_callback
	.hidden	sleep_management_resume_callback
	.type	sleep_management_resume_callback, @function
sleep_management_resume_callback:
.LFB9:
	.loc 1 301 1
	.cfi_startproc
	.loc 1 302 5
	.loc 1 304 5
	.loc 1 301 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	sw	s1,0(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 304 5
	li	a5,0
	.loc 1 304 12
	lla	s0,i.0
.L25:
	sw	a5,0(s0)
	.loc 1 304 19 is_stmt 1 discriminator 1
	li	a4,2
	bleu	a5,a4,.L27
	li	a4,0
	.loc 1 319 47 is_stmt 0
	lla	s1,resume_user_callback_func_table
.L28:
	.loc 1 318 12
	sw	a4,0(s0)
	.loc 1 318 19 is_stmt 1 discriminator 1
	li	a5,2
	bleu	a4,a5,.L30
	.loc 1 332 1 is_stmt 0
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
.L27:
	.cfi_restore_state
	.loc 1 305 9 is_stmt 1
	.loc 1 305 42 is_stmt 0
	slli	a4,a5,1
	add	a4,a4,a5
	slli	a4,a4,2
	lla	a5,resume_callback_func_table
	add	a5,a5,a4
	.loc 1 305 12
	lbu	a4,8(a5)
	beq	a4,zero,.L26
	.loc 1 310 13 is_stmt 1
	lw	a4,0(a5)
	lw	a0,4(a5)
	jalr	a4
.LVL12:
.L26:
	.loc 1 304 55 discriminator 2
	lw	a5,0(s0)
	addi	a5,a5,1
	j	.L25
.L30:
	.loc 1 319 9
	.loc 1 319 47 is_stmt 0
	slli	a5,a4,1
	add	a5,a5,a4
	slli	a5,a5,2
	add	a5,s1,a5
	.loc 1 319 12
	lbu	a4,8(a5)
	beq	a4,zero,.L29
	.loc 1 325 13 is_stmt 1
	lw	a4,0(a5)
	lw	a0,4(a5)
	jalr	a4
.LVL13:
.L29:
	.loc 1 318 25 discriminator 2
	lw	a4,0(s0)
	addi	a4,a4,1
	j	.L28
	.cfi_endproc
.LFE9:
	.size	sleep_management_resume_callback, .-sleep_management_resume_callback
	.section	.text.sleep_management_enter_deep_sleep,"ax",@progbits
	.align	1
	.globl	sleep_management_enter_deep_sleep
	.hidden	sleep_management_enter_deep_sleep
	.type	sleep_management_enter_deep_sleep, @function
sleep_management_enter_deep_sleep:
.LFB5:
	.loc 1 173 1
	.cfi_startproc
	.loc 1 174 5
	.loc 1 175 5
	.loc 1 178 5
	.loc 1 173 1 is_stmt 0
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	.loc 1 178 5
	lla	a0,sleep_management_mask
	.loc 1 173 1
	sw	ra,20(sp)
	sw	s0,16(sp)
	sw	s1,12(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 180 55
	li	s0,1108475904
	.loc 1 178 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL14:
	.loc 1 180 5 is_stmt 1
	.loc 1 180 55 is_stmt 0
	addi	s0,s0,388
	li	a5,145
	sw	a5,0(s0)
	.loc 1 181 5 is_stmt 1
	call	sleep_management_suspend_callback
.LVL15:
	.loc 1 182 5
	.loc 1 183 5 is_stmt 0
	li	a4,1110310912
	.loc 1 182 55
	li	a5,146
	sw	a5,0(s0)
	.loc 1 183 5 is_stmt 1
	lw	a5,24(a4)
	addi	a4,a4,24
	.loc 1 183 48 is_stmt 0
	ori	a5,a5,256
	sw	a5,0(a4)
	.loc 1 184 5 is_stmt 1
	.loc 1 184 55 is_stmt 0
	li	a5,147
	sw	a5,0(s0)
	.loc 1 186 7 is_stmt 1
 #APP
# 186 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	csrrw x0, mscratch, x10
la x10, sleep_management_context
sw x1, 0(x10)
sw x2, 4(x10)
sw x3, 8(x10)
sw x4, 12(x10)
sw x5, 16(x10)
sw x6, 20(x10)
sw x7, 24(x10)
sw x8, 28(x10)
sw x9, 32(x10)
sw x12, 44(x10)
sw x13, 48(x10)
sw x14, 52(x10)
sw x15, 56(x10)
sw x11, 40(x10)
csrrs x11, mtvec, x0
sw x11, 68(x10)
csrrs x11, mstatus, x0
sw x11, 60(x10)
csrrs x11, mie, x0
sw x11, 64(x10)
csrrs x11, mscratch, x0
sw x11, 36(x10)

# 0 "" 2
	.loc 1 186 542
	.loc 1 188 5
# 188 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	csrr a5, mie
# 0 "" 2
.LVL16:
	.loc 1 189 5
# 189 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	csrr a5, mip
# 0 "" 2
.LVL17:
	.loc 1 190 5
# 190 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	csrr a5, mstatus
# 0 "" 2
.LVL18:
	.loc 1 195 5
# 195 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	li x10, 1110310928
li x11, 0x3
sw x11, 4(x10)
la x11, 1f
sw x11, 0(x10)
fence.i
wfi
1:nop

# 0 "" 2
	.loc 1 211 5
# 211 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	csrr a5, mie
# 0 "" 2
.LVL19:
 #NO_APP
	sw	a5,8(sp)
.LVL20:
	.loc 1 212 5
 #APP
# 212 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	csrr s1, mip
# 0 "" 2
.LVL21:
	.loc 1 213 5
# 213 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	csrr a5, mstatus
# 0 "" 2
.LVL22:
 #NO_APP
	sw	a5,4(sp)
.LVL23:
	.loc 1 215 7
 #APP
# 215 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c" 1
	la x10, sleep_management_context
lw x1, 0(x10)
lw x2, 4(x10)
lw x3, 8(x10)
lw x4, 12(x10)
lw x5, 16(x10)
lw x6, 20(x10)
lw x7, 24(x10)
lw x8, 28(x10)
lw x9, 32(x10)
lw x11, 40(x10)
lw x12, 44(x10)
lw x13, 48(x10)
lw x14, 52(x10)
lw x15, 56(x10)
lw x11, 68(x10)
csrrw x0, mtvec, x11
lw x11, 60(x10)
csrrw x0, mstatus, x11
lw x11, 64(x10)
csrrw x0, mie, x11
lw x11, 40(x10)
lw x10, 36(x10)

# 0 "" 2
	.loc 1 215 506
	.loc 1 216 5
	.loc 1 216 55 is_stmt 0
 #NO_APP
	li	a3,148
	sw	a3,0(s0)
	.loc 1 217 5 is_stmt 1
	lw	a3,0(a4)
	.loc 1 217 48 is_stmt 0
	andi	a3,a3,-257
	sw	a3,0(a4)
	.loc 1 218 5 is_stmt 1
	call	sleep_management_resume_callback
.LVL24:
	.loc 1 219 5
	.loc 1 219 55 is_stmt 0
	li	a4,149
	sw	a4,0(s0)
	.loc 1 220 5 is_stmt 1
.LBB4:
	.loc 1 220 10
	.loc 1 220 63
	.loc 1 220 232
	li	a4,1108541440
	addi	a4,a4,372
	lw	a4,0(a4)
	li	a3,1
	lla	a2,msg_id_string.19
	li	a1,1
	lla	a0,log_control_block_common
	call	print_module_msgid_log
.LVL25:
.LBE4:
	.loc 1 220 8 discriminator 1
	.loc 1 221 5
.LBB5:
	.loc 1 221 10
	.loc 1 221 63
	.loc 1 221 243
	lw	a5,8(sp)
	lw	a4,4(sp)
	sw	s1,0(sp)
	li	a3,3
	lla	a2,msg_id_string.18
	li	a1,1
	lla	a0,log_control_block_common
	call	print_module_msgid_log
.LVL26:
.LBE5:
	.loc 1 221 8 discriminator 1
	.loc 1 225 5
	lw	a0,sleep_management_mask
	call	hal_nvic_restore_interrupt_mask
.LVL27:
	.loc 1 226 5
	.loc 1 226 55 is_stmt 0
	li	a5,150
	.loc 1 227 1
	lw	ra,20(sp)
	.cfi_restore 1
	.loc 1 226 55
	sw	a5,0(s0)
	.loc 1 227 1
	lw	s0,16(sp)
	.cfi_restore 8
	lw	s1,12(sp)
	.cfi_restore 9
.LVL28:
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
.LVL29:
	jr	ra
	.cfi_endproc
.LFE5:
	.size	sleep_management_enter_deep_sleep, .-sleep_management_enter_deep_sleep
	.section	.text.sleep_management_get_lock_handle,"ax",@progbits
	.align	1
	.globl	sleep_management_get_lock_handle
	.hidden	sleep_management_get_lock_handle
	.type	sleep_management_get_lock_handle, @function
sleep_management_get_lock_handle:
.LFB10:
	.loc 1 335 1 is_stmt 1
	.cfi_startproc
.LVL30:
	.loc 1 336 5
	.loc 1 337 5
	.loc 1 338 5
	.loc 1 340 5
	.loc 1 340 28 discriminator 1
	.loc 1 335 1 is_stmt 0
	addi	sp,sp,-36
	.cfi_def_cfa_offset 36
	sw	s0,28(sp)
	sw	ra,32(sp)
	sw	s1,24(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 335 1
	sw	a0,12(sp)
	li	s0,0
.LVL31:
.L48:
	.loc 1 341 9 is_stmt 1
	addi	a0,sp,20
	call	hal_nvic_save_and_set_interrupt_mask
.LVL32:
	.loc 1 343 9
	.loc 1 343 38 is_stmt 0
	lla	s1,sleep_management_handle
	lw	a4,8(s1)
	lw	a0,20(sp)
	.loc 1 343 59
	srl	a5,a4,s0
	.loc 1 343 69
	andi	a5,a5,1
	.loc 1 343 12
	bne	a5,zero,.L41
	.loc 1 345 13 is_stmt 1
	.loc 1 345 63 is_stmt 0
	li	a5,1
	sll	a5,a5,s0
	.loc 1 345 57
	or	a5,a5,a4
	sw	a5,8(s1)
	.loc 1 346 13 is_stmt 1
	.loc 1 346 54 is_stmt 0
	lbu	a5,12(s1)
	addi	a5,a5,1
	sb	a5,12(s1)
	.loc 1 348 13 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL33:
	.loc 1 350 13
	slli	a5,s0,1
	add	a5,a5,s0
	slli	a5,a5,2
	sub	a5,a5,s0
	sw	a5,8(sp)
	.loc 1 350 20 is_stmt 0
	addi	a5,a5,63
	add	a5,s1,a5
	.loc 1 350 13
	mv	a0,a5
	li	a2,11
	li	a1,0
	.loc 1 350 20
	sw	a5,4(sp)
	.loc 1 350 13
	call	memset
.LVL34:
	.loc 1 351 13 is_stmt 1
	.loc 1 351 24 is_stmt 0
	lw	a0,12(sp)
	call	strlen
.LVL35:
	.loc 1 353 16
	sw	a0,0(sp)
	li	a4,10
	.loc 1 351 24
	mv	a5,a0
.LVL36:
	.loc 1 353 13 is_stmt 1
	.loc 1 353 16 is_stmt 0
	bleu	a0,a4,.L42
	sw	a4,0(sp)
.L42:
	.loc 1 356 13
	lw	a2,0(sp)
	lw	a1,12(sp)
	lw	a0,4(sp)
.LVL37:
	sw	a5,16(sp)
.LVL38:
	.loc 1 356 13 is_stmt 1
	call	memcpy
.LVL39:
	.loc 1 359 13
	.loc 1 359 16 is_stmt 0
	lw	a5,16(sp)
	bne	a5,zero,.L43
	.loc 1 360 17 is_stmt 1
.LBB6:
	.loc 1 360 22
	.loc 1 360 75
	.loc 1 360 222
	li	a3,0
	lla	a2,msg_id_string.15
	li	a1,3
	lla	a0,log_control_block_common
	call	print_module_msgid_log
.LVL40:
.L43:
	lw	a5,8(sp)
	lbu	t1,0(sp)
	add	a4,s1,a5
.LBE6:
	.loc 1 335 1 is_stmt 0
	li	s1,0
.LVL41:
.L44:
	.loc 1 363 27 is_stmt 1 discriminator 1
	bne	s1,t1,.L46
	.loc 1 376 5
	.loc 1 382 5
	.loc 1 382 11 is_stmt 0
	addi	a0,s0,24
	andi	a0,a0,0xff
.LVL42:
	.loc 1 384 5 is_stmt 1
.L54:
	.loc 1 385 1 is_stmt 0
	lw	ra,32(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,28(sp)
	.cfi_restore 8
	lw	s1,24(sp)
	.cfi_restore 9
	addi	sp,sp,36
	.cfi_def_cfa_offset 0
.LVL43:
	jr	ra
.LVL44:
.L46:
	.cfi_restore_state
	.loc 1 364 17 is_stmt 1
	.loc 1 364 82 is_stmt 0
	lbu	a5,63(a4)
	.loc 1 364 20
	li	a3,92
	.loc 1 364 82
	addi	a5,a5,-33
	.loc 1 364 20
	andi	a5,a5,0xff
	bleu	a5,a3,.L45
.LBB7:
	.loc 1 365 226
	li	a3,0
	lla	a2,msg_id_string.14
	li	a1,3
	lla	a0,log_control_block_common
	sw	t1,4(sp)
	sw	a4,0(sp)
.LBE7:
	.loc 1 365 21 is_stmt 1
.LBB8:
	.loc 1 365 26
	.loc 1 365 79
	.loc 1 365 226
	call	print_module_msgid_log
.LVL45:
	lw	t1,4(sp)
	lw	a4,0(sp)
.L45:
.LBE8:
	.loc 1 365 24 discriminator 1
	.loc 1 363 40 discriminator 2
	addi	s1,s1,1
.LVL46:
	andi	s1,s1,0xff
.LVL47:
	addi	a4,a4,1
	j	.L44
.LVL48:
.L41:
	.loc 1 371 13
	call	hal_nvic_restore_interrupt_mask
.LVL49:
	.loc 1 340 67 discriminator 2
	.loc 1 340 28 discriminator 1
	addi	s0,s0,1
.LVL50:
	li	a5,26
	bne	s0,a5,.L48
	.loc 1 376 5
	.loc 1 377 9
.LBB9:
	.loc 1 377 14
	.loc 1 377 67
	.loc 1 377 214
	lla	a0,log_control_block_common
	li	a3,0
	lla	a2,msg_id_string.13
	li	a1,3
	call	print_module_msgid_log
.LVL51:
.LBE9:
	.loc 1 377 12 discriminator 1
	.loc 1 379 9
	.loc 1 379 16 is_stmt 0
	li	a0,255
	j	.L54
	.cfi_endproc
.LFE10:
	.size	sleep_management_get_lock_handle, .-sleep_management_get_lock_handle
	.section	.text.sleep_management_release_lock_handle,"ax",@progbits
	.align	1
	.globl	sleep_management_release_lock_handle
	.hidden	sleep_management_release_lock_handle
	.type	sleep_management_release_lock_handle, @function
sleep_management_release_lock_handle:
.LFB11:
	.loc 1 388 1 is_stmt 1
	.cfi_startproc
.LVL52:
	.loc 1 389 5
	.loc 1 391 5
	.loc 1 388 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	.cfi_offset 8, -8
	.loc 1 391 30
	addi	s0,a0,-24
	.loc 1 388 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 391 30
	andi	s0,s0,0xff
	.loc 1 391 8
	li	a5,25
	bleu	s0,a5,.L57
	.loc 1 392 9 is_stmt 1
.LBB10:
	.loc 1 392 14
	.loc 1 392 67
	.loc 1 392 215
.LBE10:
	.loc 1 409 1 is_stmt 0
	lw	s0,8(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,12(sp)
	.cfi_restore 1
.LBB11:
	.loc 1 392 215
	li	a3,0
.LBE11:
	.loc 1 409 1
.LBB12:
	.loc 1 392 215
	lla	a2,msg_id_string.12
	li	a1,3
	lla	a0,log_control_block_common
.LVL53:
.LBE12:
	.loc 1 409 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
.LBB13:
	.loc 1 392 215
	tail	print_module_msgid_log
.LVL54:
.L57:
	.cfi_restore_state
.LBE13:
	.loc 1 396 5 is_stmt 1
	.loc 1 398 5
	mv	a0,sp
	call	hal_nvic_save_and_set_interrupt_mask
.LVL55:
	.loc 1 399 5
	.loc 1 399 34 is_stmt 0
	lla	a0,sleep_management_handle
	lw	a4,8(a0)
	.loc 1 399 55
	srl	a5,a4,s0
	.loc 1 399 72
	andi	a5,a5,1
	.loc 1 399 8
	beq	a5,zero,.L58
	.loc 1 400 9 is_stmt 1
	.loc 1 400 50 is_stmt 0
	lbu	a5,12(a0)
	.loc 1 402 9
	li	a2,11
	li	a1,0
	.loc 1 400 50
	addi	a5,a5,-1
	sb	a5,12(a0)
	.loc 1 401 9 is_stmt 1
	.loc 1 401 60 is_stmt 0
	li	a5,1
	sll	a5,a5,s0
	.loc 1 401 56
	not	a5,a5
	.loc 1 401 53
	and	a5,a5,a4
	sw	a5,8(a0)
	.loc 1 402 9 is_stmt 1
	.loc 1 402 16 is_stmt 0
	slli	a5,s0,1
	add	a5,a5,s0
	slli	a5,a5,2
	sub	a5,a5,s0
	addi	a5,a5,63
	.loc 1 402 9
	add	a0,a0,a5
	call	memset
.LVL56:
.L59:
	.loc 1 404 12 is_stmt 1 discriminator 1
	.loc 1 406 5
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL57:
	.loc 1 408 5
	.loc 1 409 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL58:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL59:
.L58:
	.cfi_restore_state
	.loc 1 404 9 is_stmt 1
.LBB14:
	.loc 1 404 14
	.loc 1 404 67
	.loc 1 404 220
	li	a3,0
	lla	a2,msg_id_string.11
	li	a1,2
	lla	a0,log_control_block_common
	call	print_module_msgid_log
.LVL60:
	j	.L59
.LBE14:
	.cfi_endproc
.LFE11:
	.size	sleep_management_release_lock_handle, .-sleep_management_release_lock_handle
	.globl	__ashldi3
	.section	.text.sleep_management_lock_sleep,"ax",@progbits
	.align	1
	.globl	sleep_management_lock_sleep
	.hidden	sleep_management_lock_sleep
	.type	sleep_management_lock_sleep, @function
sleep_management_lock_sleep:
.LFB12:
	.loc 1 412 1
	.cfi_startproc
.LVL61:
	.loc 1 413 5
	.loc 1 414 5
	.loc 1 416 5
	.loc 1 416 8 is_stmt 0
	li	a5,49
	bleu	a1,a5,.L62
	.loc 1 417 9 is_stmt 1
.LBB15:
	.loc 1 417 14
	.loc 1 417 67
	.loc 1 417 215
	li	a3,0
	lla	a2,msg_id_string.10
	li	a1,3
.LVL62:
	lla	a0,log_control_block_common
.LVL63:
	tail	print_module_msgid_log
.LVL64:
.L62:
.LBE15:
	.loc 1 412 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 421 8
	li	a4,1
	mv	s0,a1
	.loc 1 421 5 is_stmt 1
	lla	s1,sleep_management_handle
	.loc 1 421 8 is_stmt 0
	bne	a0,a4,.L63
	.loc 1 423 9 is_stmt 1
	addi	a0,sp,4
.LVL65:
	call	hal_nvic_save_and_set_interrupt_mask
.LVL66:
	.loc 1 424 9
	.loc 1 424 61 is_stmt 0
	add	a3,s1,s0
	lbu	a4,13(a3)
	.loc 1 424 12
	li	a2,255
	beq	a4,a2,.L64
	.loc 1 425 13 is_stmt 1
	.loc 1 425 75 is_stmt 0
	addi	a4,a4,1
	sb	a4,13(a3)
	.loc 1 426 13 is_stmt 1
.LVL67:
	.loc 1 427 13
	.loc 1 426 19 is_stmt 0
	mv	a2,s0
	li	a0,1
	li	a1,0
	call	__ashldi3
.LVL68:
	.loc 1 427 56
	lw	a4,0(s1)
	or	a0,a4,a0
	lw	a4,4(s1)
	sw	a0,0(s1)
	or	a4,a4,a1
	sw	a4,4(s1)
.LVL69:
.L64:
	.loc 1 430 9 is_stmt 1
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL70:
	.loc 1 434 9
	.loc 1 434 61 is_stmt 0
	add	a4,s1,s0
	.loc 1 434 12
	lbu	a3,13(a4)
	li	a4,255
	bne	a3,a4,.L61
	.loc 1 435 13 is_stmt 1
.LBB16:
	.loc 1 435 18
	.loc 1 435 71
	.loc 1 435 233
	mv	a4,s0
	li	a3,1
	lla	a2,msg_id_string.9
	li	a1,2
	lla	a0,log_control_block_common
	call	print_module_msgid_log
.LVL71:
.LBE16:
	.loc 1 435 16 discriminator 1
	.loc 1 436 13
	.loc 1 436 16 is_stmt 0
	li	a4,23
	bleu	s0,a4,.L61
	.loc 1 437 17 is_stmt 1
.LBB17:
	.loc 1 437 22
	.loc 1 437 75
	.loc 1 437 214
	.loc 1 437 364 is_stmt 0
	addi	s0,s0,-24
	.loc 1 437 349
	slli	a4,s0,1
	add	a4,a4,s0
	slli	a4,a4,2
	sub	a4,a4,s0
	addi	a4,a4,63
	.loc 1 437 214
	add	a4,s1,a4
	li	a3,1
	lla	a2,msg_id_string.8
.L72:
.LBE17:
.LBB18:
	.loc 1 459 210
	li	a1,2
	lla	a0,log_control_block_common
	call	print_module_msgid_log
.LVL72:
	j	.L61
.LVL73:
.L63:
.LBE18:
	.loc 1 443 9 is_stmt 1
	addi	a0,sp,4
.LVL74:
	call	hal_nvic_save_and_set_interrupt_mask
.LVL75:
	.loc 1 444 9
	lw	a5,4(sp)
	.loc 1 444 61 is_stmt 0
	add	a3,s1,s0
	lbu	a4,13(a3)
	sw	a5,0(sp)
	.loc 1 444 12
	beq	a4,zero,.L68
	.loc 1 445 13 is_stmt 1
	.loc 1 445 75 is_stmt 0
	addi	a4,a4,-1
	andi	a4,a4,0xff
	sb	a4,13(a3)
	.loc 1 446 13 is_stmt 1
	.loc 1 446 16 is_stmt 0
	bne	a4,zero,.L69
	.loc 1 447 17 is_stmt 1
.LVL76:
	.loc 1 448 17
	.loc 1 447 23 is_stmt 0
	mv	a2,s0
	li	a0,1
	li	a1,0
	call	__ashldi3
.LVL77:
	.loc 1 448 60
	lw	a3,0(s1)
	lw	a4,4(s1)
	.loc 1 448 63
	not	a0,a0
	not	a1,a1
	.loc 1 448 60
	and	a3,a3,a0
	and	a4,a4,a1
	sw	a3,0(s1)
	sw	a4,4(s1)
.LVL78:
.L69:
	.loc 1 454 13 is_stmt 1
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL79:
.L61:
	.loc 1 466 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL80:
.L68:
	.cfi_restore_state
	.loc 1 456 13 is_stmt 1
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL81:
	.loc 1 457 13
.LBB19:
	.loc 1 457 18
	.loc 1 457 71
	.loc 1 457 243
	mv	a4,s0
	li	a3,1
	lla	a2,msg_id_string.7
	li	a1,2
	lla	a0,log_control_block_common
	call	print_module_msgid_log
.LVL82:
.LBE19:
	.loc 1 457 16 discriminator 1
	.loc 1 458 13
	.loc 1 458 16 is_stmt 0
	li	a4,23
	bleu	s0,a4,.L61
	.loc 1 459 17 is_stmt 1
.LBB20:
	.loc 1 459 22
	.loc 1 459 75
	.loc 1 459 210
	.loc 1 459 360 is_stmt 0
	addi	s0,s0,-24
	.loc 1 459 345
	slli	a4,s0,1
	add	a4,a4,s0
	slli	a4,a4,2
	sub	a4,a4,s0
	addi	a4,a4,63
	.loc 1 459 210
	add	a4,s1,a4
	li	a3,1
	lla	a2,msg_id_string.6
	j	.L72
.LBE20:
	.cfi_endproc
.LFE12:
	.size	sleep_management_lock_sleep, .-sleep_management_lock_sleep
	.section	.text.sleep_management_check_sleep_locks,"ax",@progbits
	.align	1
	.globl	sleep_management_check_sleep_locks
	.hidden	sleep_management_check_sleep_locks
	.type	sleep_management_check_sleep_locks, @function
sleep_management_check_sleep_locks:
.LFB13:
	.loc 1 469 1 is_stmt 1
	.cfi_startproc
	.loc 1 470 4
.LVL83:
	.loc 1 471 5
	.loc 1 472 5
	.loc 1 474 5
	.loc 1 475 5
	.loc 1 477 5
	.loc 1 469 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 477 5
	mv	a0,sp
	.loc 1 469 1
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 477 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL84:
	.loc 1 478 5 is_stmt 1
	.loc 1 478 33 is_stmt 0
	lla	a5,sleep_management_handle
	.loc 1 478 53
	lw	s0,0(a5)
	lw	a5,4(a5)
	.loc 1 483 5
	lw	a0,0(sp)
	.loc 1 478 53
	slli	a5,a5,15
	srli	a5,a5,15
	.loc 1 478 8
	or	s0,s0,a5
	snez	s0,s0
.LVL85:
	.loc 1 483 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL86:
	.loc 1 485 5
	.loc 1 486 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	mv	a0,s0
	lw	s0,8(sp)
	.cfi_restore 8
.LVL87:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE13:
	.size	sleep_management_check_sleep_locks, .-sleep_management_check_sleep_locks
	.globl	__lshrdi3
	.section	.text.sleep_management_check_handle_status,"ax",@progbits
	.align	1
	.globl	sleep_management_check_handle_status
	.hidden	sleep_management_check_handle_status
	.type	sleep_management_check_handle_status, @function
sleep_management_check_handle_status:
.LFB14:
	.loc 1 489 1 is_stmt 1
	.cfi_startproc
.LVL88:
	.loc 1 490 4
	.loc 1 493 5
	.loc 1 489 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 493 8
	li	a5,49
	bleu	a0,a5,.L76
	.loc 1 494 9 is_stmt 1
.LBB21:
	.loc 1 494 14
	.loc 1 494 67
	.loc 1 494 215
	lla	a0,log_control_block_common
.LVL89:
	li	a3,0
	lla	a2,msg_id_string.5
	li	a1,3
	call	print_module_msgid_log
.LVL90:
.LBE21:
	.loc 1 494 12 discriminator 1
	.loc 1 495 9
	.loc 1 495 15 is_stmt 0
	li	a0,0
.L77:
.LVL91:
	.loc 1 507 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL92:
.L76:
	.cfi_restore_state
	.loc 1 498 54
	lla	a5,sleep_management_handle
	mv	a2,a0
	.loc 1 498 5 is_stmt 1
	.loc 1 498 54 is_stmt 0
	lw	a1,4(a5)
	lw	a0,0(a5)
.LVL93:
	call	__lshrdi3
.LVL94:
	andi	a0,a0,1
	j	.L77
	.cfi_endproc
.LFE14:
	.size	sleep_management_check_handle_status, .-sleep_management_check_handle_status
	.section	.text.sleep_management_get_lock_sleep_request_info,"ax",@progbits
	.align	1
	.globl	sleep_management_get_lock_sleep_request_info
	.hidden	sleep_management_get_lock_sleep_request_info
	.type	sleep_management_get_lock_sleep_request_info, @function
sleep_management_get_lock_sleep_request_info:
.LFB15:
	.loc 1 510 1 is_stmt 1
	.cfi_startproc
	.loc 1 511 5
	.loc 1 512 1 is_stmt 0
	lla	a5,sleep_management_handle
	lw	a0,0(a5)
	lw	a1,4(a5)
	ret
	.cfi_endproc
.LFE15:
	.size	sleep_management_get_lock_sleep_request_info, .-sleep_management_get_lock_sleep_request_info
	.section	.text.sleep_management_get_lock_sleep_handle_list,"ax",@progbits
	.align	1
	.globl	sleep_management_get_lock_sleep_handle_list
	.hidden	sleep_management_get_lock_sleep_handle_list
	.type	sleep_management_get_lock_sleep_handle_list, @function
sleep_management_get_lock_sleep_handle_list:
.LFB16:
	.loc 1 515 1 is_stmt 1
	.cfi_startproc
	.loc 1 516 5
	.loc 1 517 5
	.loc 1 517 14 is_stmt 0
	lla	a5,sleep_management_handle
	lw	a4,0(a5)
	lw	a5,4(a5)
	.loc 1 515 1
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
.LBB22:
	.loc 1 520 212
	li	a3,0
	lla	a2,msg_id_string.4
	li	a1,1
	lla	a0,log_control_block_common
.LBE22:
	.loc 1 515 1
	sw	s0,12(sp)
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 517 14
	sw	a4,0(sp)
	sw	a5,4(sp)
.LVL95:
	.loc 1 518 5 is_stmt 1
	.loc 1 520 5
.LBB23:
	.loc 1 520 10
	.loc 1 520 63
	.loc 1 520 212
	lla	s1,sleep_management_handle-201
	call	print_module_msgid_log
.LVL96:
.LBE23:
	.loc 1 520 8 discriminator 1
	.loc 1 521 5
	.loc 1 521 19 discriminator 1
.LBB24:
	.loc 1 520 212 is_stmt 0
	li	s0,0
.LVL97:
.L84:
.LBE24:
	.loc 1 522 9 is_stmt 1
	.loc 1 522 40 is_stmt 0
	mv	a2,s0
	li	a0,1
	li	a1,0
	call	__ashldi3
.LVL98:
	.loc 1 522 32
	lw	a5,0(sp)
	and	a0,a0,a5
	lw	a5,4(sp)
	and	a1,a1,a5
	.loc 1 522 12
	or	a0,a0,a1
	beq	a0,zero,.L82
	.loc 1 523 13 is_stmt 1
.LBB25:
	.loc 1 523 18
	.loc 1 523 71
	.loc 1 523 221
	mv	a4,s0
	li	a3,1
	lla	a2,msg_id_string.3
	li	a1,1
	lla	a0,log_control_block_common
	call	print_module_msgid_log
.LVL99:
.LBE25:
	.loc 1 523 16 discriminator 1
	.loc 1 524 13
	.loc 1 524 16 is_stmt 0
	li	a5,23
	bleu	s0,a5,.L82
	.loc 1 525 17 is_stmt 1
.LBB26:
	.loc 1 525 22
	.loc 1 525 75
	.loc 1 525 216
	mv	a4,s1
	li	a3,1
	lla	a2,msg_id_string.2
	li	a1,1
	lla	a0,log_control_block_common
	call	print_module_msgid_log
.LVL100:
.L82:
.LBE26:
	.loc 1 525 20 discriminator 1
	.loc 1 521 26 discriminator 2
	.loc 1 521 19 discriminator 1
	addi	s0,s0,1
.LVL101:
	li	a5,50
	addi	s1,s1,11
	bne	s0,a5,.L84
	.loc 1 529 5
	.loc 1 530 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
.LVL102:
	lw	a0,0(sp)
	lw	a1,4(sp)
	lw	s1,8(sp)
	.cfi_restore 9
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
.LVL103:
	jr	ra
	.cfi_endproc
.LFE16:
	.size	sleep_management_get_lock_sleep_handle_list, .-sleep_management_get_lock_sleep_handle_list
	.section	.text.sleep_management_get_lock_extslp_handle,"ax",@progbits
	.align	1
	.globl	sleep_management_get_lock_extslp_handle
	.hidden	sleep_management_get_lock_extslp_handle
	.type	sleep_management_get_lock_extslp_handle, @function
sleep_management_get_lock_extslp_handle:
.LFB17:
	.loc 1 533 1 is_stmt 1
	.cfi_startproc
.LVL104:
	.loc 1 534 5
	.loc 1 586 5
	.loc 1 587 1 is_stmt 0
	li	a0,0
.LVL105:
	ret
	.cfi_endproc
.LFE17:
	.size	sleep_management_get_lock_extslp_handle, .-sleep_management_get_lock_extslp_handle
	.section	.text.sleep_management_release_lock_extslp_handle,"ax",@progbits
	.align	1
	.globl	sleep_management_release_lock_extslp_handle
	.hidden	sleep_management_release_lock_extslp_handle
	.type	sleep_management_release_lock_extslp_handle, @function
sleep_management_release_lock_extslp_handle:
.LFB18:
	.loc 1 590 1 is_stmt 1
	.cfi_startproc
.LVL106:
	.loc 1 611 5
	.loc 1 612 1 is_stmt 0
	ret
	.cfi_endproc
.LFE18:
	.size	sleep_management_release_lock_extslp_handle, .-sleep_management_release_lock_extslp_handle
	.section	.text.sleep_management_lock_extslp,"ax",@progbits
	.align	1
	.globl	sleep_management_lock_extslp
	.hidden	sleep_management_lock_extslp
	.type	sleep_management_lock_extslp, @function
sleep_management_lock_extslp:
.LFB19:
	.loc 1 615 1 is_stmt 1
	.cfi_startproc
.LVL107:
	.loc 1 673 5
	.loc 1 674 1 is_stmt 0
	ret
	.cfi_endproc
.LFE19:
	.size	sleep_management_lock_extslp, .-sleep_management_lock_extslp
	.section	.text.sleep_management_check_extslp_locks,"ax",@progbits
	.align	1
	.globl	sleep_management_check_extslp_locks
	.hidden	sleep_management_check_extslp_locks
	.type	sleep_management_check_extslp_locks, @function
sleep_management_check_extslp_locks:
.LFB20:
	.loc 1 677 1 is_stmt 1
	.cfi_startproc
	.loc 1 678 4
.LVL108:
	.loc 1 695 5
	.loc 1 696 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE20:
	.size	sleep_management_check_extslp_locks, .-sleep_management_check_extslp_locks
	.section	.text.sleep_management_check_request_extslp_status,"ax",@progbits
	.align	1
	.globl	sleep_management_check_request_extslp_status
	.hidden	sleep_management_check_request_extslp_status
	.type	sleep_management_check_request_extslp_status, @function
sleep_management_check_request_extslp_status:
.LFB21:
	.loc 1 699 1 is_stmt 1
	.cfi_startproc
	.loc 1 700 5
	.loc 1 702 5
	.loc 1 699 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 702 5
	mv	a0,sp
	.loc 1 699 1
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 702 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL109:
	.loc 1 703 4 is_stmt 1
	.loc 1 704 5 is_stmt 0
	lw	a0,0(sp)
	.loc 1 703 23
	li	a5,1108541440
	lw	s0,112(a5)
.LVL110:
	.loc 1 704 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL111:
	.loc 1 706 5
	.loc 1 707 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	andi	a0,s0,1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL112:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE21:
	.size	sleep_management_check_request_extslp_status, .-sleep_management_check_request_extslp_status
	.section	.sbss.i.0,"aw",@nobits
	.align	2
	.type	i.0, @object
	.size	i.0, 4
i.0:
	.zero	4
	.section	.sbss.i.1,"aw",@nobits
	.align	2
	.type	i.1, @object
	.size	i.1, 4
i.1:
	.zero	4
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.2, @object
	.size	msg_id_string.2, 46
msg_id_string.2:
	.string	"[M:common C:info F: L: ]: sleep handle = %s\r\n"
	.align	2
	.type	msg_id_string.3, @object
	.size	msg_id_string.3, 55
msg_id_string.3:
	.string	"[M:common C:info F: L: ]: index of sleep handle = %d\r\n"
	.align	2
	.type	msg_id_string.4, @object
	.size	msg_id_string.4, 54
msg_id_string.4:
	.string	"[M:common C:info F: L: ]: lock sleep handle list : \r\n"
	.align	2
	.type	msg_id_string.5, @object
	.size	msg_id_string.5, 53
msg_id_string.5:
	.string	"[M:common C:info F: L: ]: sleep handle index error\r\n"
	.align	2
	.type	msg_id_string.6, @object
	.size	msg_id_string.6, 42
msg_id_string.6:
	.string	"[M:common C:info F: L: ]: sleep handle=%s"
	.align	2
	.type	msg_id_string.7, @object
	.size	msg_id_string.7, 77
msg_id_string.7:
	.string	"[M:common C:info F: L: ]: sleep handle=%d,lock sleep has already released \r\n"
	.align	2
	.type	msg_id_string.8, @object
	.size	msg_id_string.8, 44
msg_id_string.8:
	.string	"[M:common C:info F: L: ]: sleep handle=%s\r\n"
	.align	2
	.type	msg_id_string.9, @object
	.size	msg_id_string.9, 67
msg_id_string.9:
	.string	"[M:common C:info F: L: ]: sleep handle=%d,lock sleep count full \r\n"
	.align	2
	.type	msg_id_string.10, @object
	.size	msg_id_string.10, 53
msg_id_string.10:
	.string	"[M:common C:info F: L: ]: sleep handle index error\r\n"
	.align	2
	.type	msg_id_string.11, @object
	.size	msg_id_string.11, 58
msg_id_string.11:
	.string	"[M:common C:info F: L: ]: sleep handle already release \r\n"
	.align	2
	.type	msg_id_string.12, @object
	.size	msg_id_string.12, 53
msg_id_string.12:
	.string	"[M:common C:info F: L: ]: sleep handle index error\r\n"
	.align	2
	.type	msg_id_string.13, @object
	.size	msg_id_string.13, 52
msg_id_string.13:
	.string	"[M:common C:info F: L: ]: cannot get sleep handle\r\n"
	.align	2
	.type	msg_id_string.14, @object
	.size	msg_id_string.14, 52
msg_id_string.14:
	.string	"[M:common C:info F: L: ]: sleep handle name error\r\n"
	.align	2
	.type	msg_id_string.15, @object
	.size	msg_id_string.15, 52
msg_id_string.15:
	.string	"[M:common C:info F: L: ]: sleep handle name error\r\n"
	.align	2
	.type	msg_id_string.16, @object
	.size	msg_id_string.16, 71
msg_id_string.16:
	.string	"[M:common C:info F: L: ]: register resume callback function overflow\r\n"
	.align	2
	.type	msg_id_string.17, @object
	.size	msg_id_string.17, 72
msg_id_string.17:
	.string	"[M:common C:info F: L: ]: register suspend callback function overflow\r\n"
	.align	2
	.type	msg_id_string.18, @object
	.size	msg_id_string.18, 87
msg_id_string.18:
	.string	"[M:common C:info F: L: ]: [SLP][wakeup] dsp mstatus = 0x%08x, mie = 0x%08x, mip=0x%08x"
	.align	2
	.type	msg_id_string.19, @object
	.size	msg_id_string.19, 76
msg_id_string.19:
	.string	"[M:common C:info F: L: ]: [SLP] dsp deep sleep exit, wakeup source = 0x%08x"
	.section	.sbss.resume_user_register_count,"aw",@nobits
	.align	2
	.type	resume_user_register_count, @object
	.size	resume_user_register_count, 4
resume_user_register_count:
	.zero	4
	.section	.sbss.suspend_user_register_count,"aw",@nobits
	.align	2
	.type	suspend_user_register_count, @object
	.size	suspend_user_register_count, 4
suspend_user_register_count:
	.zero	4
	.section	.bss.resume_user_callback_func_table,"aw",@nobits
	.align	2
	.type	resume_user_callback_func_table, @object
	.size	resume_user_callback_func_table, 36
resume_user_callback_func_table:
	.zero	36
	.section	.bss.suspend_user_callback_func_table,"aw",@nobits
	.align	2
	.type	suspend_user_callback_func_table, @object
	.size	suspend_user_callback_func_table, 36
suspend_user_callback_func_table:
	.zero	36
	.section	.bss.resume_callback_func_table,"aw",@nobits
	.align	2
	.type	resume_callback_func_table, @object
	.size	resume_callback_func_table, 36
resume_callback_func_table:
	.zero	36
	.section	.bss.suspend_callback_func_table,"aw",@nobits
	.align	2
	.type	suspend_callback_func_table, @object
	.size	suspend_callback_func_table, 36
suspend_callback_func_table:
	.zero	36
	.hidden	sleep_management_mask
	.globl	sleep_management_mask
	.section	.sbss.sleep_management_mask,"aw",@nobits
	.align	2
	.type	sleep_management_mask, @object
	.size	sleep_management_mask, 4
sleep_management_mask:
	.zero	4
	.hidden	sleep_management_context
	.globl	sleep_management_context
	.section	.bss.sleep_management_context,"aw",@nobits
	.align	2
	.type	sleep_management_context, @object
	.size	sleep_management_context, 72
sleep_management_context:
	.zero	72
	.section	.bss.sleep_management_handle,"aw",@nobits
	.align	3
	.type	sleep_management_handle, @object
	.size	sleep_management_handle, 352
sleep_management_handle:
	.zero	352
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_internal.h"
	.file 7 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.file 8 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 9 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x138a
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x2c
	.4byte	.LASF174
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL28
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
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0xe
	.byte	0x1
	.byte	0x6
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
	.uleb128 0x2d
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0xe
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x2e
	.byte	0x4
	.uleb128 0x24
	.4byte	0x7f
	.uleb128 0xe
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xa
	.4byte	0x86
	.uleb128 0x12
	.4byte	0x8d
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x34
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x3
	.byte	0x37
	.byte	0x20
	.4byte	0x26
	.uleb128 0x13
	.4byte	0x2d
	.byte	0x4
	.byte	0x3d
	.4byte	0xdf
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
	.uleb128 0x4
	.4byte	.LASF21
	.byte	0x4
	.byte	0x42
	.byte	0x3
	.4byte	0xbb
	.uleb128 0x13
	.4byte	0x2d
	.byte	0x4
	.byte	0x45
	.4byte	0x151
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
	.uleb128 0x4
	.4byte	.LASF37
	.byte	0x4
	.byte	0x57
	.byte	0x3
	.4byte	0xeb
	.uleb128 0x4
	.4byte	.LASF38
	.byte	0x4
	.byte	0x59
	.byte	0x10
	.4byte	0x169
	.uleb128 0x12
	.4byte	0x16e
	.uleb128 0x18
	.4byte	0x18e
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x92
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0xdf
	.uleb128 0x3
	.4byte	0x92
	.uleb128 0x19
	.byte	0
	.uleb128 0x4
	.4byte	.LASF39
	.byte	0x4
	.byte	0x5a
	.byte	0x10
	.4byte	0x19a
	.uleb128 0x12
	.4byte	0x19f
	.uleb128 0x18
	.4byte	0x1c9
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x92
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0xdf
	.uleb128 0x3
	.4byte	0x1c9
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x92
	.uleb128 0x19
	.byte	0
	.uleb128 0x12
	.4byte	0x1d3
	.uleb128 0x24
	.4byte	0x1c9
	.uleb128 0x2f
	.uleb128 0x4
	.4byte	.LASF40
	.byte	0x4
	.byte	0x5b
	.byte	0x10
	.4byte	0x1e0
	.uleb128 0x12
	.4byte	0x1e5
	.uleb128 0x18
	.4byte	0x200
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0xdf
	.uleb128 0x3
	.4byte	0x92
	.uleb128 0x3
	.4byte	0xa3
	.uleb128 0x19
	.byte	0
	.uleb128 0x4
	.4byte	.LASF41
	.byte	0x4
	.byte	0x5c
	.byte	0x14
	.4byte	0x20c
	.uleb128 0x12
	.4byte	0x211
	.uleb128 0x30
	.4byte	0xa3
	.4byte	0x234
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0xdf
	.uleb128 0x3
	.4byte	0x151
	.uleb128 0x3
	.4byte	0x234
	.uleb128 0x3
	.4byte	0x239
	.byte	0
	.uleb128 0x12
	.4byte	0x1c9
	.uleb128 0x12
	.4byte	0xa3
	.uleb128 0x1a
	.byte	0x1c
	.byte	0x4
	.byte	0x5e
	.4byte	0x2a2
	.uleb128 0x5
	.4byte	.LASF42
	.byte	0x4
	.byte	0x5f
	.byte	0x11
	.4byte	0x92
	.byte	0
	.uleb128 0x5
	.4byte	.LASF43
	.byte	0x4
	.byte	0x60
	.byte	0xe
	.4byte	0xa3
	.byte	0x4
	.uleb128 0x5
	.4byte	.LASF44
	.byte	0x4
	.byte	0x61
	.byte	0xe
	.4byte	0xa3
	.byte	0x8
	.uleb128 0x5
	.4byte	.LASF45
	.byte	0x4
	.byte	0x62
	.byte	0xf
	.4byte	0x15d
	.byte	0xc
	.uleb128 0x5
	.4byte	.LASF46
	.byte	0x4
	.byte	0x63
	.byte	0x15
	.4byte	0x18e
	.byte	0x10
	.uleb128 0x5
	.4byte	.LASF47
	.byte	0x4
	.byte	0x64
	.byte	0x12
	.4byte	0x200
	.byte	0x14
	.uleb128 0x5
	.4byte	.LASF48
	.byte	0x4
	.byte	0x65
	.byte	0x10
	.4byte	0x1d4
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF49
	.byte	0x4
	.byte	0x66
	.byte	0x3
	.4byte	0x23e
	.uleb128 0x31
	.4byte	.LASF175
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x9
	.2byte	0x128
	.byte	0x12
	.4byte	0x334
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x1f
	.byte	0
	.uleb128 0x13
	.4byte	0x2d
	.byte	0x5
	.byte	0x2a
	.4byte	0x3dc
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0xff
	.byte	0
	.uleb128 0x13
	.4byte	0x2d
	.byte	0x5
	.byte	0x5e
	.4byte	0x406
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF100
	.byte	0x5
	.byte	0x64
	.byte	0x3
	.4byte	0x3dc
	.uleb128 0x13
	.4byte	0x2d
	.byte	0x6
	.byte	0x2e
	.4byte	0x42a
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF103
	.byte	0x6
	.byte	0x31
	.byte	0x3
	.4byte	0x412
	.uleb128 0x13
	.4byte	0x2d
	.byte	0x6
	.byte	0x33
	.4byte	0x44e
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF106
	.byte	0x6
	.byte	0x36
	.byte	0x3
	.4byte	0x436
	.uleb128 0x13
	.4byte	0x2d
	.byte	0x6
	.byte	0x38
	.4byte	0x472
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x1
	.byte	0
	.uleb128 0x32
	.2byte	0x160
	.byte	0x6
	.byte	0x42
	.byte	0x9
	.4byte	0x4be
	.uleb128 0x5
	.4byte	.LASF109
	.byte	0x6
	.byte	0x43
	.byte	0xe
	.4byte	0xaf
	.byte	0
	.uleb128 0x5
	.4byte	.LASF110
	.byte	0x6
	.byte	0x44
	.byte	0xe
	.4byte	0xa3
	.byte	0x8
	.uleb128 0x5
	.4byte	.LASF111
	.byte	0x6
	.byte	0x45
	.byte	0xd
	.4byte	0x97
	.byte	0xc
	.uleb128 0x5
	.4byte	.LASF112
	.byte	0x6
	.byte	0x46
	.byte	0xd
	.4byte	0x4be
	.byte	0xd
	.uleb128 0x5
	.4byte	.LASF113
	.byte	0x6
	.byte	0x47
	.byte	0xd
	.4byte	0x4ce
	.byte	0x3f
	.byte	0
	.uleb128 0x8
	.4byte	0x97
	.4byte	0x4ce
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x31
	.byte	0
	.uleb128 0x8
	.4byte	0x97
	.4byte	0x4e4
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x19
	.uleb128 0x7
	.4byte	0x2d
	.byte	0xa
	.byte	0
	.uleb128 0x4
	.4byte	.LASF114
	.byte	0x6
	.byte	0x48
	.byte	0x3
	.4byte	0x472
	.uleb128 0x4
	.4byte	.LASF115
	.byte	0x6
	.byte	0x4a
	.byte	0x10
	.4byte	0x4fc
	.uleb128 0x12
	.4byte	0x501
	.uleb128 0x18
	.4byte	0x50c
	.uleb128 0x3
	.4byte	0x7f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF116
	.byte	0x6
	.byte	0x4b
	.byte	0x10
	.4byte	0x4fc
	.uleb128 0x1a
	.byte	0xc
	.byte	0x6
	.byte	0x4d
	.4byte	0x548
	.uleb128 0x5
	.4byte	.LASF117
	.byte	0x6
	.byte	0x4e
	.byte	0x29
	.4byte	0x4f0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF118
	.byte	0x6
	.byte	0x4f
	.byte	0xb
	.4byte	0x7f
	.byte	0x4
	.uleb128 0x5
	.4byte	.LASF119
	.byte	0x6
	.byte	0x50
	.byte	0x9
	.4byte	0x548
	.byte	0x8
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.byte	0x2
	.4byte	.LASF120
	.uleb128 0x4
	.4byte	.LASF121
	.byte	0x6
	.byte	0x51
	.byte	0x3
	.4byte	0x518
	.uleb128 0x1a
	.byte	0xc
	.byte	0x6
	.byte	0x53
	.4byte	0x58b
	.uleb128 0x5
	.4byte	.LASF117
	.byte	0x6
	.byte	0x54
	.byte	0x28
	.4byte	0x50c
	.byte	0
	.uleb128 0x5
	.4byte	.LASF118
	.byte	0x6
	.byte	0x55
	.byte	0xb
	.4byte	0x7f
	.byte	0x4
	.uleb128 0x5
	.4byte	.LASF119
	.byte	0x6
	.byte	0x56
	.byte	0x9
	.4byte	0x548
	.byte	0x8
	.byte	0
	.uleb128 0x4
	.4byte	.LASF122
	.byte	0x6
	.byte	0x57
	.byte	0x3
	.4byte	0x55b
	.uleb128 0x1a
	.byte	0x48
	.byte	0x1
	.byte	0x7b
	.4byte	0x661
	.uleb128 0x9
	.string	"x1"
	.byte	0x7c
	.4byte	0xa3
	.byte	0
	.uleb128 0x9
	.string	"x2"
	.byte	0x7d
	.4byte	0xa3
	.byte	0x4
	.uleb128 0x9
	.string	"x3"
	.byte	0x7e
	.4byte	0xa3
	.byte	0x8
	.uleb128 0x9
	.string	"x4"
	.byte	0x7f
	.4byte	0xa3
	.byte	0xc
	.uleb128 0x9
	.string	"x5"
	.byte	0x80
	.4byte	0xa3
	.byte	0x10
	.uleb128 0x9
	.string	"x6"
	.byte	0x81
	.4byte	0xa3
	.byte	0x14
	.uleb128 0x9
	.string	"x7"
	.byte	0x82
	.4byte	0xa3
	.byte	0x18
	.uleb128 0x9
	.string	"x8"
	.byte	0x83
	.4byte	0xa3
	.byte	0x1c
	.uleb128 0x9
	.string	"x9"
	.byte	0x84
	.4byte	0xa3
	.byte	0x20
	.uleb128 0x9
	.string	"x10"
	.byte	0x85
	.4byte	0xa3
	.byte	0x24
	.uleb128 0x9
	.string	"x11"
	.byte	0x86
	.4byte	0xa3
	.byte	0x28
	.uleb128 0x9
	.string	"x12"
	.byte	0x87
	.4byte	0xa3
	.byte	0x2c
	.uleb128 0x9
	.string	"x13"
	.byte	0x88
	.4byte	0xa3
	.byte	0x30
	.uleb128 0x9
	.string	"x14"
	.byte	0x89
	.4byte	0xa3
	.byte	0x34
	.uleb128 0x9
	.string	"x15"
	.byte	0x8a
	.4byte	0xa3
	.byte	0x38
	.uleb128 0x5
	.4byte	.LASF123
	.byte	0x1
	.byte	0x8b
	.byte	0xe
	.4byte	0xa3
	.byte	0x3c
	.uleb128 0x9
	.string	"mie"
	.byte	0x8c
	.4byte	0xa3
	.byte	0x40
	.uleb128 0x5
	.4byte	.LASF124
	.byte	0x1
	.byte	0x8d
	.byte	0xe
	.4byte	0xa3
	.byte	0x44
	.byte	0
	.uleb128 0x4
	.4byte	.LASF125
	.byte	0x1
	.byte	0x8e
	.byte	0x3
	.4byte	0x597
	.uleb128 0x11
	.4byte	.LASF128
	.byte	0x92
	.byte	0x22
	.4byte	0x4e4
	.uleb128 0x5
	.byte	0x3
	.4byte	sleep_management_handle
	.uleb128 0x25
	.4byte	.LASF126
	.byte	0x97
	.byte	0x11
	.4byte	0x661
	.uleb128 0x5
	.byte	0x3
	.4byte	sleep_management_context
	.uleb128 0x25
	.4byte	.LASF127
	.byte	0x98
	.byte	0xa
	.4byte	0xa3
	.uleb128 0x5
	.byte	0x3
	.4byte	sleep_management_mask
	.uleb128 0x8
	.4byte	0x54f
	.4byte	0x6b0
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.4byte	.LASF129
	.byte	0x99
	.byte	0x31
	.4byte	0x6a0
	.uleb128 0x5
	.byte	0x3
	.4byte	suspend_callback_func_table
	.uleb128 0x8
	.4byte	0x58b
	.4byte	0x6d1
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.4byte	.LASF130
	.byte	0x9a
	.byte	0x30
	.4byte	0x6c1
	.uleb128 0x5
	.byte	0x3
	.4byte	resume_callback_func_table
	.uleb128 0x11
	.4byte	.LASF131
	.byte	0x9b
	.byte	0x31
	.4byte	0x6a0
	.uleb128 0x5
	.byte	0x3
	.4byte	suspend_user_callback_func_table
	.uleb128 0x11
	.4byte	.LASF132
	.byte	0x9c
	.byte	0x30
	.4byte	0x6c1
	.uleb128 0x5
	.byte	0x3
	.4byte	resume_user_callback_func_table
	.uleb128 0x11
	.4byte	.LASF133
	.byte	0x9d
	.byte	0x11
	.4byte	0xa3
	.uleb128 0x5
	.byte	0x3
	.4byte	suspend_user_register_count
	.uleb128 0x11
	.4byte	.LASF134
	.byte	0x9d
	.byte	0x32
	.4byte	0xa3
	.uleb128 0x5
	.byte	0x3
	.4byte	resume_user_register_count
	.uleb128 0x1e
	.4byte	.LASF135
	.byte	0x1f
	.4byte	0x7f
	.4byte	0x744
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x1ce
	.uleb128 0x3
	.4byte	0x6c
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF136
	.byte	0x29
	.4byte	0x6c
	.4byte	0x758
	.uleb128 0x3
	.4byte	0x92
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF137
	.byte	0x21
	.4byte	0x7f
	.4byte	0x776
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x6c
	.byte	0
	.uleb128 0x26
	.4byte	.LASF138
	.byte	0x3f
	.4byte	0x786
	.uleb128 0x3
	.4byte	0xa3
	.byte	0
	.uleb128 0x33
	.4byte	.LASF139
	.byte	0x4
	.2byte	0x129
	.byte	0xd
	.4byte	0x7a9
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0xdf
	.uleb128 0x3
	.4byte	0x92
	.uleb128 0x3
	.4byte	0xa3
	.uleb128 0x19
	.byte	0
	.uleb128 0x26
	.4byte	.LASF140
	.byte	0x3e
	.4byte	0x7b9
	.uleb128 0x3
	.4byte	0x239
	.byte	0
	.uleb128 0x34
	.4byte	.LASF143
	.byte	0x1
	.2byte	0x2ba
	.byte	0x5
	.4byte	0x548
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x811
	.uleb128 0x6
	.4byte	.LASF141
	.2byte	0x2bc
	.byte	0xe
	.4byte	0xa3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x14
	.4byte	.LASF142
	.2byte	0x2bf
	.byte	0x9
	.4byte	0x548
	.4byte	.LLST27
	.uleb128 0xf
	.4byte	.LVL109
	.4byte	0x7a9
	.4byte	0x807
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0xd
	.4byte	.LVL111
	.4byte	0x776
	.byte	0
	.uleb128 0x15
	.4byte	.LASF147
	.2byte	0x2a4
	.byte	0x5
	.4byte	0x548
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x839
	.uleb128 0x1f
	.4byte	.LASF142
	.2byte	0x2a6
	.byte	0x9
	.4byte	0x548
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF144
	.2byte	0x266
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x86b
	.uleb128 0x20
	.4byte	.LASF142
	.2byte	0x266
	.byte	0x42
	.4byte	0x44e
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x20
	.4byte	.LASF145
	.2byte	0x266
	.byte	0x50
	.4byte	0x97
	.uleb128 0x1
	.byte	0x5b
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF146
	.2byte	0x24d
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x88f
	.uleb128 0x20
	.4byte	.LASF145
	.2byte	0x24d
	.byte	0x3a
	.4byte	0x97
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x15
	.4byte	.LASF148
	.2byte	0x214
	.byte	0x9
	.4byte	0x97
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x8c7
	.uleb128 0x16
	.4byte	.LASF149
	.2byte	0x214
	.byte	0x3d
	.4byte	0x92
	.4byte	.LLST26
	.uleb128 0x1f
	.4byte	.LASF150
	.2byte	0x216
	.byte	0xd
	.4byte	0x97
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LASF151
	.2byte	0x202
	.byte	0xa
	.4byte	0xaf
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9f8
	.uleb128 0x27
	.string	"i"
	.2byte	0x204
	.4byte	0x97
	.4byte	.LLST23
	.uleb128 0x14
	.4byte	.LASF109
	.2byte	0x205
	.byte	0xe
	.4byte	0xaf
	.4byte	.LLST24
	.uleb128 0x1f
	.4byte	.LASF141
	.2byte	0x206
	.byte	0xe
	.4byte	0xaf
	.byte	0x1
	.uleb128 0x1c
	.4byte	.LLRL25
	.4byte	0x950
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x208
	.byte	0x25
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x208
	.byte	0x7e
	.4byte	0xa08
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.4
	.uleb128 0xc
	.4byte	.LVL96
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.4
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LBB25
	.4byte	.LBE25-.LBB25
	.4byte	0x99f
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x20b
	.byte	0x2d
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x20b
	.byte	0x86
	.4byte	0xa1d
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.3
	.uleb128 0xc
	.4byte	.LVL99
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LBB26
	.4byte	.LBE26-.LBB26
	.4byte	0x9ee
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x20d
	.byte	0x31
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x20d
	.byte	0x8a
	.4byte	0xa32
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.2
	.uleb128 0xc
	.4byte	.LVL100
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.2
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LVL98
	.4byte	0x137b
	.byte	0
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0xa08
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x35
	.byte	0
	.uleb128 0xa
	.4byte	0x9f8
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0xa1d
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x36
	.byte	0
	.uleb128 0xa
	.4byte	0xa0d
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0xa32
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x2d
	.byte	0
	.uleb128 0xa
	.4byte	0xa22
	.uleb128 0x35
	.4byte	.LASF176
	.byte	0x1
	.2byte	0x1fd
	.byte	0xa
	.4byte	0xaf
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x15
	.4byte	.LASF154
	.2byte	0x1e8
	.byte	0x5
	.4byte	0x548
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xadb
	.uleb128 0x16
	.4byte	.LASF145
	.2byte	0x1e8
	.byte	0x32
	.4byte	0x97
	.4byte	.LLST21
	.uleb128 0x14
	.4byte	.LASF142
	.2byte	0x1ea
	.byte	0x9
	.4byte	0x548
	.4byte	.LLST22
	.uleb128 0x10
	.4byte	.LBB21
	.4byte	.LBE21-.LBB21
	.4byte	0xad1
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x1ee
	.byte	0x29
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x1ee
	.byte	0x82
	.4byte	0xaeb
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.5
	.uleb128 0xc
	.4byte	.LVL90
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.5
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LVL94
	.4byte	0x1384
	.byte	0
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0xaeb
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x34
	.byte	0
	.uleb128 0xa
	.4byte	0xadb
	.uleb128 0x15
	.4byte	.LASF155
	.2byte	0x1d4
	.byte	0x5
	.4byte	0x548
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb5c
	.uleb128 0x14
	.4byte	.LASF142
	.2byte	0x1d6
	.byte	0x9
	.4byte	0x548
	.4byte	.LLST20
	.uleb128 0x6
	.4byte	.LASF141
	.2byte	0x1d7
	.byte	0xe
	.4byte	0xa3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x36
	.4byte	.LASF156
	.byte	0x1
	.2byte	0x1d8
	.byte	0xe
	.4byte	0xaf
	.8byte	0x1ffffffffffff
	.uleb128 0xf
	.4byte	.LVL84
	.4byte	0x7a9
	.4byte	0xb52
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0xd
	.4byte	.LVL86
	.4byte	0x776
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF157
	.2byte	0x19b
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd64
	.uleb128 0x16
	.4byte	.LASF142
	.2byte	0x19b
	.byte	0x40
	.4byte	0x42a
	.4byte	.LLST16
	.uleb128 0x16
	.4byte	.LASF145
	.2byte	0x19b
	.byte	0x4e
	.4byte	0x97
	.4byte	.LLST17
	.uleb128 0x6
	.4byte	.LASF141
	.2byte	0x19d
	.byte	0xe
	.4byte	0xa3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x14
	.4byte	.LASF158
	.2byte	0x19e
	.byte	0xe
	.4byte	0xaf
	.4byte	.LLST18
	.uleb128 0x10
	.4byte	.LBB15
	.4byte	.LBE15-.LBB15
	.4byte	0xbf9
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x1a1
	.byte	0x29
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x1a1
	.byte	0x82
	.4byte	0xaeb
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.10
	.uleb128 0x1d
	.4byte	.LVL64
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.10
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LBB16
	.4byte	.LBE16-.LBB16
	.4byte	0xc48
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x1b3
	.byte	0x2d
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x1b3
	.byte	0x86
	.4byte	0xd74
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.9
	.uleb128 0xc
	.4byte	.LVL71
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.9
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LBB17
	.4byte	.LBE17-.LBB17
	.4byte	0xc74
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x1b5
	.byte	0x31
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x1b5
	.byte	0x8a
	.4byte	0xd89
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.8
	.byte	0
	.uleb128 0x10
	.4byte	.LBB19
	.4byte	.LBE19-.LBB19
	.4byte	0xcc3
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x1c9
	.byte	0x2d
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x1c9
	.byte	0x86
	.4byte	0xd9e
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.7
	.uleb128 0xc
	.4byte	.LVL82
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.7
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	.LLRL19
	.4byte	0xcfa
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x1cb
	.byte	0x31
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x1cb
	.byte	0x8a
	.4byte	0xdb3
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.6
	.uleb128 0xc
	.4byte	.LVL72
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	.LVL66
	.4byte	0x7a9
	.4byte	0xd0e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xd
	.4byte	.LVL68
	.4byte	0x137b
	.uleb128 0xd
	.4byte	.LVL70
	.4byte	0x776
	.uleb128 0xf
	.4byte	.LVL75
	.4byte	0x7a9
	.4byte	0xd34
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xd
	.4byte	.LVL77
	.4byte	0x137b
	.uleb128 0xf
	.4byte	.LVL79
	.4byte	0x776
	.4byte	0xd52
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xc
	.4byte	.LVL81
	.4byte	0x776
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0xd74
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x42
	.byte	0
	.uleb128 0xa
	.4byte	0xd64
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0xd89
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x2b
	.byte	0
	.uleb128 0xa
	.4byte	0xd79
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0xd9e
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x4c
	.byte	0
	.uleb128 0xa
	.4byte	0xd8e
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0xdb3
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x29
	.byte	0
	.uleb128 0xa
	.4byte	0xda3
	.uleb128 0x1b
	.4byte	.LASF159
	.2byte	0x183
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xec6
	.uleb128 0x16
	.4byte	.LASF145
	.2byte	0x183
	.byte	0x33
	.4byte	0x97
	.4byte	.LLST14
	.uleb128 0x6
	.4byte	.LASF141
	.2byte	0x185
	.byte	0xe
	.4byte	0xa3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1c
	.4byte	.LLRL15
	.4byte	0xe31
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x188
	.byte	0x29
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x188
	.byte	0x82
	.4byte	0xaeb
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.12
	.uleb128 0x1d
	.4byte	.LVL54
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.12
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LBB14
	.4byte	.LBE14-.LBB14
	.4byte	0xe7a
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x194
	.byte	0x29
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x194
	.byte	0x82
	.4byte	0xed6
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.11
	.uleb128 0xc
	.4byte	.LVL60
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.11
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	.LVL55
	.4byte	0x7a9
	.4byte	0xe8e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0xf
	.4byte	.LVL56
	.4byte	0x758
	.4byte	0xebc
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x12
	.byte	0x78
	.sleb128 0
	.byte	0x31
	.byte	0x24
	.byte	0x78
	.sleb128 0
	.byte	0x22
	.byte	0x32
	.byte	0x24
	.byte	0x78
	.sleb128 0
	.byte	0x1c
	.byte	0x3
	.4byte	sleep_management_handle+63
	.byte	0x22
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x3b
	.byte	0
	.uleb128 0xd
	.4byte	.LVL57
	.4byte	0x776
	.byte	0
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0xed6
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x39
	.byte	0
	.uleb128 0xa
	.4byte	0xec6
	.uleb128 0x15
	.4byte	.LASF160
	.2byte	0x14e
	.byte	0x9
	.4byte	0x97
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1096
	.uleb128 0x16
	.4byte	.LASF149
	.2byte	0x14e
	.byte	0x36
	.4byte	0x92
	.4byte	.LLST9
	.uleb128 0x14
	.4byte	.LASF150
	.2byte	0x150
	.byte	0xd
	.4byte	0x97
	.4byte	.LLST10
	.uleb128 0x27
	.string	"i"
	.2byte	0x151
	.4byte	0x97
	.4byte	.LLST11
	.uleb128 0x6
	.4byte	.LASF141
	.2byte	0x152
	.byte	0xe
	.4byte	0xa3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x14
	.4byte	.LASF161
	.2byte	0x152
	.byte	0x14
	.4byte	0xa3
	.4byte	.LLST12
	.uleb128 0x10
	.4byte	.LBB6
	.4byte	.LBE6-.LBB6
	.4byte	0xf8a
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x168
	.byte	0x31
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x168
	.byte	0x8a
	.4byte	0x10a6
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.15
	.uleb128 0xc
	.4byte	.LVL40
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.15
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	.LLRL13
	.4byte	0xfcf
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x16d
	.byte	0x35
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x16d
	.byte	0x8e
	.4byte	0x10a6
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.14
	.uleb128 0xc
	.4byte	.LVL45
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.14
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LBB9
	.4byte	.LBE9-.LBB9
	.4byte	0x1018
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x179
	.byte	0x29
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x179
	.byte	0x82
	.4byte	0x10a6
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.13
	.uleb128 0xc
	.4byte	.LVL51
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.13
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	.LVL32
	.4byte	0x7a9
	.4byte	0x102c
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xd
	.4byte	.LVL33
	.4byte	0x776
	.uleb128 0xf
	.4byte	.LVL34
	.4byte	0x758
	.4byte	0x1054
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x6
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x3b
	.byte	0
	.uleb128 0xf
	.4byte	.LVL35
	.4byte	0x744
	.4byte	0x1069
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -24
	.byte	0x6
	.byte	0
	.uleb128 0xf
	.4byte	.LVL39
	.4byte	0x726
	.4byte	0x108c
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x6
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -24
	.byte	0x6
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xd
	.4byte	.LVL49
	.4byte	0x776
	.byte	0
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0x10a6
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x33
	.byte	0
	.uleb128 0xa
	.4byte	0x1096
	.uleb128 0x28
	.4byte	.LASF162
	.2byte	0x12c
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10d0
	.uleb128 0x29
	.string	"i"
	.2byte	0x12e
	.4byte	0xa3
	.uleb128 0x5
	.byte	0x3
	.4byte	i.0
	.byte	0
	.uleb128 0x28
	.4byte	.LASF163
	.2byte	0x109
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10f5
	.uleb128 0x29
	.string	"i"
	.2byte	0x10b
	.4byte	0xa3
	.uleb128 0x5
	.byte	0x3
	.4byte	i.1
	.byte	0
	.uleb128 0x21
	.4byte	.LASF164
	.byte	0xf7
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x117c
	.uleb128 0x17
	.4byte	.LASF165
	.byte	0xf7
	.byte	0x59
	.4byte	0x406
	.4byte	.LLST3
	.uleb128 0x17
	.4byte	.LASF166
	.byte	0xf7
	.byte	0x84
	.4byte	0x50c
	.4byte	.LLST4
	.uleb128 0x17
	.4byte	.LASF118
	.byte	0xf7
	.byte	0x94
	.4byte	0x7f
	.4byte	.LLST5
	.uleb128 0x2a
	.4byte	.LBB3
	.4byte	.LBE3-.LBB3
	.uleb128 0xb
	.4byte	.LASF152
	.2byte	0x100
	.byte	0x2d
	.4byte	0x2a2
	.uleb128 0x6
	.4byte	.LASF153
	.2byte	0x100
	.byte	0x86
	.4byte	0x118c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.16
	.uleb128 0x1d
	.4byte	.LVL9
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.16
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0x118c
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x46
	.byte	0
	.uleb128 0xa
	.4byte	0x117c
	.uleb128 0x21
	.4byte	.LASF167
	.byte	0xe5
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1216
	.uleb128 0x17
	.4byte	.LASF165
	.byte	0xe5
	.byte	0x5a
	.4byte	0x406
	.4byte	.LLST0
	.uleb128 0x17
	.4byte	.LASF166
	.byte	0xe5
	.byte	0x86
	.4byte	0x4f0
	.4byte	.LLST1
	.uleb128 0x17
	.4byte	.LASF118
	.byte	0xe5
	.byte	0x96
	.4byte	0x7f
	.4byte	.LLST2
	.uleb128 0x2a
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.uleb128 0x22
	.4byte	.LASF152
	.byte	0xee
	.byte	0x2d
	.4byte	0x2a2
	.uleb128 0x11
	.4byte	.LASF153
	.byte	0xee
	.byte	0x86
	.4byte	0x1226
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.17
	.uleb128 0x1d
	.4byte	.LVL4
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.17
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0x1226
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x47
	.byte	0
	.uleb128 0xa
	.4byte	0x1216
	.uleb128 0x21
	.4byte	.LASF168
	.byte	0xac
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x133f
	.uleb128 0x23
	.4byte	.LASF169
	.byte	0xe
	.4byte	0xa3
	.4byte	.LLST6
	.uleb128 0x23
	.4byte	.LASF170
	.byte	0x19
	.4byte	0xa3
	.4byte	.LLST7
	.uleb128 0x23
	.4byte	.LASF171
	.byte	0x24
	.4byte	0xa3
	.4byte	.LLST8
	.uleb128 0x10
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.4byte	0x12b0
	.uleb128 0x22
	.4byte	.LASF152
	.byte	0xdc
	.byte	0x25
	.4byte	0x2a2
	.uleb128 0x11
	.4byte	.LASF153
	.byte	0xdc
	.byte	0x7e
	.4byte	0x134f
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.19
	.uleb128 0xc
	.4byte	.LVL25
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.19
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LBB5
	.4byte	.LBE5-.LBB5
	.4byte	0x130c
	.uleb128 0x22
	.4byte	.LASF152
	.byte	0xdd
	.byte	0x25
	.4byte	0x2a2
	.uleb128 0x11
	.4byte	.LASF153
	.byte	0xdd
	.byte	0x7e
	.4byte	0x1364
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.18
	.uleb128 0xc
	.4byte	.LVL26
	.4byte	0x786
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.18
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -20
	.byte	0x6
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5f
	.uleb128 0x3
	.byte	0x91
	.sleb128 -16
	.byte	0x6
	.uleb128 0x2
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	.LVL14
	.4byte	0x7a9
	.4byte	0x1323
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	sleep_management_mask
	.byte	0
	.uleb128 0xd
	.4byte	.LVL15
	.4byte	0x10d0
	.uleb128 0xd
	.4byte	.LVL24
	.4byte	0x10ab
	.uleb128 0xd
	.4byte	.LVL27
	.4byte	0x776
	.byte	0
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0x134f
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x4b
	.byte	0
	.uleb128 0xa
	.4byte	0x133f
	.uleb128 0x8
	.4byte	0x8d
	.4byte	0x1364
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x56
	.byte	0
	.uleb128 0xa
	.4byte	0x1354
	.uleb128 0x37
	.4byte	.LASF177
	.byte	0x1
	.byte	0xa2
	.byte	0x6
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x2b
	.4byte	.LASF172
	.4byte	.LASF172
	.uleb128 0x2b
	.4byte	.LASF173
	.4byte	.LASF173
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
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
	.uleb128 0xd
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
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0xc
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.sleb128 8
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
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 175
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x37
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.uleb128 0x26
	.uleb128 0x2e
	.byte	0x1
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
	.sleb128 13
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x21
	.sleb128 13
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
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
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x21
	.sleb128 21
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2b
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
	.uleb128 0x2c
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
	.uleb128 0x2d
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
	.uleb128 0x2e
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x30
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
	.uleb128 0x31
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
	.uleb128 0x32
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
	.uleb128 0x35
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
	.uleb128 0x1c
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x37
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
.LLST27:
	.byte	0x8
	.4byte	.LVL110
	.uleb128 .LVL112-.LVL110
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST26:
	.byte	0x6
	.4byte	.LVL104
	.byte	0x4
	.uleb128 .LVL104-.LVL104
	.uleb128 .LVL105-.LVL104
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL105-.LVL104
	.uleb128 .LFE17-.LVL104
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
.LLST23:
	.byte	0x6
	.4byte	.LVL96
	.byte	0x4
	.uleb128 .LVL96-.LVL96
	.uleb128 .LVL97-.LVL96
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL97-.LVL96
	.uleb128 .LVL100-.LVL96
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL100-.LVL96
	.uleb128 .LVL101-.LVL96
	.uleb128 0x3
	.byte	0x78
	.sleb128 1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL101-.LVL96
	.uleb128 .LVL102-.LVL96
	.uleb128 0x3
	.byte	0x78
	.sleb128 0
	.byte	0x9f
	.byte	0
.LLST24:
	.byte	0x6
	.4byte	.LVL95
	.byte	0x4
	.uleb128 .LVL95-.LVL95
	.uleb128 .LVL96-1-.LVL95
	.uleb128 0x6
	.byte	0x5e
	.byte	0x93
	.uleb128 0x4
	.byte	0x5f
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL96-1-.LVL95
	.uleb128 .LVL103-.LVL95
	.uleb128 0x8
	.byte	0x72
	.sleb128 0
	.byte	0x93
	.uleb128 0x4
	.byte	0x91
	.sleb128 -16
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL103-.LVL95
	.uleb128 .LFE16-.LVL95
	.uleb128 0x8
	.byte	0x72
	.sleb128 -20
	.byte	0x93
	.uleb128 0x4
	.byte	0x72
	.sleb128 -16
	.byte	0x93
	.uleb128 0x4
	.byte	0
.LLST21:
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
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL92-.LVL88
	.uleb128 .LVL93-.LVL88
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL93-.LVL88
	.uleb128 .LFE14-.LVL88
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST22:
	.byte	0x6
	.4byte	.LVL88
	.byte	0x4
	.uleb128 .LVL88-.LVL88
	.uleb128 .LVL91-.LVL88
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL92-.LVL88
	.uleb128 .LFE14-.LVL88
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST20:
	.byte	0x6
	.4byte	.LVL83
	.byte	0x4
	.uleb128 .LVL83-.LVL83
	.uleb128 .LVL85-.LVL83
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL85-.LVL83
	.uleb128 .LVL87-.LVL83
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL87-.LVL83
	.uleb128 .LFE13-.LVL83
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST16:
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
	.uleb128 .LVL65-.LVL61
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL65-.LVL61
	.uleb128 .LVL73-.LVL61
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
	.uleb128 .LVL73-.LVL61
	.uleb128 .LVL74-.LVL61
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL74-.LVL61
	.uleb128 .LFE12-.LVL61
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
.LLST17:
	.byte	0x6
	.4byte	.LVL61
	.byte	0x4
	.uleb128 .LVL61-.LVL61
	.uleb128 .LVL62-.LVL61
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL62-.LVL61
	.uleb128 .LVL64-.LVL61
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
	.uleb128 .LVL64-.LVL61
	.uleb128 .LVL66-1-.LVL61
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL66-1-.LVL61
	.uleb128 .LVL73-.LVL61
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
	.uleb128 .LVL73-.LVL61
	.uleb128 .LVL75-1-.LVL61
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL75-1-.LVL61
	.uleb128 .LFE12-.LVL61
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
	.byte	0
.LLST18:
	.byte	0x6
	.4byte	.LVL61
	.byte	0x4
	.uleb128 .LVL61-.LVL61
	.uleb128 .LVL67-.LVL61
	.uleb128 0xa
	.byte	0x9e
	.uleb128 0x8
	.8byte	0x1
	.byte	0x4
	.uleb128 .LVL67-.LVL61
	.uleb128 .LVL69-.LVL61
	.uleb128 0xb
	.byte	0x31
	.byte	0xa8
	.uleb128 0x26
	.byte	0x78
	.sleb128 0
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0x26
	.byte	0x24
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL73-.LVL61
	.uleb128 .LVL76-.LVL61
	.uleb128 0xa
	.byte	0x9e
	.uleb128 0x8
	.8byte	0x1
	.byte	0x4
	.uleb128 .LVL76-.LVL61
	.uleb128 .LVL78-.LVL61
	.uleb128 0xb
	.byte	0x31
	.byte	0xa8
	.uleb128 0x26
	.byte	0x78
	.sleb128 0
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0x26
	.byte	0x24
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL80-.LVL61
	.uleb128 .LFE12-.LVL61
	.uleb128 0xa
	.byte	0x9e
	.uleb128 0x8
	.8byte	0x1
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL52
	.byte	0x4
	.uleb128 .LVL52-.LVL52
	.uleb128 .LVL53-.LVL52
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL53-.LVL52
	.uleb128 .LVL54-.LVL52
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL54-.LVL52
	.uleb128 .LVL58-.LVL52
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL59-.LVL52
	.uleb128 .LFE11-.LVL52
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL31-.LVL30
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL31-.LVL30
	.uleb128 .LVL43-.LVL30
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL43-.LVL30
	.uleb128 .LVL44-.LVL30
	.uleb128 0x2
	.byte	0x72
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL44-.LVL30
	.uleb128 .LFE10-.LVL30
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL31-.LVL30
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL31-.LVL30
	.uleb128 .LVL42-.LVL30
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL44-.LVL30
	.uleb128 .LVL49-.LVL30
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL49-.LVL30
	.uleb128 .LVL50-.LVL30
	.uleb128 0x3
	.byte	0x78
	.sleb128 1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL50-.LVL30
	.uleb128 .LFE10-.LVL30
	.uleb128 0x3
	.byte	0x78
	.sleb128 0
	.byte	0x9f
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL41
	.byte	0x4
	.uleb128 .LVL41-.LVL41
	.uleb128 .LVL42-.LVL41
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL44-.LVL41
	.uleb128 .LVL46-.LVL41
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL47-.LVL41
	.uleb128 .LVL48-.LVL41
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL36
	.byte	0x4
	.uleb128 .LVL36-.LVL36
	.uleb128 .LVL37-.LVL36
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL37-.LVL36
	.uleb128 .LVL38-.LVL36
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL38-.LVL36
	.uleb128 .LVL39-1-.LVL36
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL39-1-.LVL36
	.uleb128 .LVL41-.LVL36
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL6-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL6-.LVL5
	.uleb128 .LVL9-.LVL5
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
	.uleb128 .LVL9-.LVL5
	.uleb128 .LFE7-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL8-.LVL5
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL8-.LVL5
	.uleb128 .LVL9-.LVL5
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
	.uleb128 .LVL9-.LVL5
	.uleb128 .LFE7-.LVL5
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL7-.LVL5
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL7-.LVL5
	.uleb128 .LVL9-.LVL5
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
	.uleb128 .LVL9-.LVL5
	.uleb128 .LFE7-.LVL5
	.uleb128 0x1
	.byte	0x5c
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
	.uleb128 .LVL4-.LVL0
	.uleb128 .LFE6-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
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
	.uleb128 .LVL4-.LVL0
	.uleb128 .LFE6-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL2-.LVL0
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL2-.LVL0
	.uleb128 .LVL4-.LVL0
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
	.uleb128 .LVL4-.LVL0
	.uleb128 .LFE6-.LVL0
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL20
	.byte	0x4
	.uleb128 .LVL20-.LVL20
	.uleb128 .LVL22-.LVL20
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL22-.LVL20
	.uleb128 .LVL29-.LVL20
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL29-.LVL20
	.uleb128 .LFE5-.LVL20
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0
.LLST7:
	.byte	0x8
	.4byte	.LVL21
	.uleb128 .LVL28-.LVL21
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST8:
	.byte	0x6
	.4byte	.LVL23
	.byte	0x4
	.uleb128 .LVL23-.LVL23
	.uleb128 .LVL24-1-.LVL23
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL24-1-.LVL23
	.uleb128 .LVL29-.LVL23
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL29-.LVL23
	.uleb128 .LFE5-.LVL23
	.uleb128 0x2
	.byte	0x72
	.sleb128 -20
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0xa4
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
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
.LLRL13:
	.byte	0x5
	.4byte	.LBB7
	.byte	0x4
	.uleb128 .LBB7-.LBB7
	.uleb128 .LBE7-.LBB7
	.byte	0x4
	.uleb128 .LBB8-.LBB7
	.uleb128 .LBE8-.LBB7
	.byte	0
.LLRL15:
	.byte	0x5
	.4byte	.LBB10
	.byte	0x4
	.uleb128 .LBB10-.LBB10
	.uleb128 .LBE10-.LBB10
	.byte	0x4
	.uleb128 .LBB11-.LBB10
	.uleb128 .LBE11-.LBB10
	.byte	0x4
	.uleb128 .LBB12-.LBB10
	.uleb128 .LBE12-.LBB10
	.byte	0x4
	.uleb128 .LBB13-.LBB10
	.uleb128 .LBE13-.LBB10
	.byte	0
.LLRL19:
	.byte	0x5
	.4byte	.LBB18
	.byte	0x4
	.uleb128 .LBB18-.LBB18
	.uleb128 .LBE18-.LBB18
	.byte	0x4
	.uleb128 .LBB20-.LBB18
	.uleb128 .LBE20-.LBB18
	.byte	0
.LLRL25:
	.byte	0x5
	.4byte	.LBB22
	.byte	0x4
	.uleb128 .LBB22-.LBB22
	.uleb128 .LBE22-.LBB22
	.byte	0x4
	.uleb128 .LBB23-.LBB22
	.uleb128 .LBE23-.LBB22
	.byte	0x4
	.uleb128 .LBB24-.LBB22
	.uleb128 .LBE24-.LBB22
	.byte	0
.LLRL28:
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
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
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF119:
	.string	"init_status"
.LASF69:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF97:
	.string	"SLEEP_BACKUP_RESTORE_UART"
.LASF146:
	.string	"sleep_management_release_lock_extslp_handle"
.LASF13:
	.string	"size_t"
.LASF161:
	.string	"name_len"
.LASF138:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF16:
	.string	"uint64_t"
.LASF99:
	.string	"SLEEP_BACKUP_RESTORE_USER"
.LASF28:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF174:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF149:
	.string	"handle_name"
.LASF8:
	.string	"long int"
.LASF72:
	.string	"SLEEP_LOCK_TRNG"
.LASF30:
	.string	"LOG_TYPE_HCI_DATA"
.LASF47:
	.string	"tlv_dump_handle"
.LASF52:
	.string	"QDEC_IRQn"
.LASF106:
	.string	"sleep_management_lock_extslp_t"
.LASF74:
	.string	"SLEEP_LOCK_IRTX"
.LASF22:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF94:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF71:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF27:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF10:
	.string	"long long int"
.LASF5:
	.string	"signed char"
.LASF104:
	.string	"UNLOCK_EXTSLP"
.LASF109:
	.string	"lock_sleep_request"
.LASF58:
	.string	"UART_DMA_IRQn"
.LASF95:
	.string	"SLEEP_BACKUP_RESTORE_SPI_MST0"
.LASF105:
	.string	"LOCK_EXTSLP"
.LASF44:
	.string	"print_level"
.LASF126:
	.string	"sleep_management_context"
.LASF38:
	.string	"f_print_t"
.LASF77:
	.string	"SLEEP_LOCK_FLASH"
.LASF122:
	.string	"sleep_management_resume_callback_func_t"
.LASF29:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF135:
	.string	"memcpy"
.LASF70:
	.string	"SLEEP_LOCK_AESOTF"
.LASF152:
	.string	"log_control_block_common"
.LASF167:
	.string	"sleep_management_register_suspend_callback"
.LASF156:
	.string	"sleep_handle_mask"
.LASF130:
	.string	"resume_callback_func_table"
.LASF39:
	.string	"f_dump_buffer_t"
.LASF139:
	.string	"print_module_msgid_log"
.LASF158:
	.string	"shift"
.LASF33:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF141:
	.string	"mask"
.LASF128:
	.string	"sleep_management_handle"
.LASF112:
	.string	"lock_sleep_request_count"
.LASF127:
	.string	"sleep_management_mask"
.LASF170:
	.string	"mip_value"
.LASF61:
	.string	"EINT_IRQn"
.LASF129:
	.string	"suspend_callback_func_table"
.LASF63:
	.string	"I3C0_DMA_IRQn"
.LASF3:
	.string	"unsigned int"
.LASF43:
	.string	"log_switch"
.LASF111:
	.string	"user_handle_count"
.LASF136:
	.string	"strlen"
.LASF124:
	.string	"mtvec"
.LASF169:
	.string	"mie_value"
.LASF32:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF9:
	.string	"long unsigned int"
.LASF45:
	.string	"print_handle"
.LASF98:
	.string	"SLEEP_BACKUP_RESTORE_MODULE_MAX"
.LASF2:
	.string	"long long unsigned int"
.LASF118:
	.string	"data"
.LASF154:
	.string	"sleep_management_check_handle_status"
.LASF7:
	.string	"short unsigned int"
.LASF20:
	.string	"PRINT_LEVEL_ERROR"
.LASF85:
	.string	"SLEEP_LOCK_I3C1"
.LASF62:
	.string	"I3C0_IRQn"
.LASF113:
	.string	"user_handle_name"
.LASF31:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF147:
	.string	"sleep_management_check_extslp_locks"
.LASF66:
	.string	"USB_IRQn"
.LASF166:
	.string	"callback"
.LASF155:
	.string	"sleep_management_check_sleep_locks"
.LASF19:
	.string	"PRINT_LEVEL_WARNING"
.LASF64:
	.string	"SPI_MST0_IRQn"
.LASF37:
	.string	"log_type_t"
.LASF84:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF107:
	.string	"SLEEP_MANAGEMENT_UNINITIALIZED"
.LASF175:
	.string	"IRQn"
.LASF162:
	.string	"sleep_management_resume_callback"
.LASF100:
	.string	"sleep_management_backup_restore_module_t"
.LASF101:
	.string	"UNLOCK_SLEEP"
.LASF65:
	.string	"IRQ_GEN_IRQn"
.LASF57:
	.string	"GPT_IRQn"
.LASF143:
	.string	"sleep_management_check_request_extslp_status"
.LASF50:
	.string	"SW_IRQn"
.LASF108:
	.string	"SLEEP_MANAGEMENT_INITIALIZED"
.LASF36:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF78:
	.string	"SLEEP_LOCK_ESC"
.LASF144:
	.string	"sleep_management_lock_extslp"
.LASF34:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF55:
	.string	"SPI_MST1_IRQn"
.LASF23:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF160:
	.string	"sleep_management_get_lock_handle"
.LASF91:
	.string	"SLEEP_LOCK_I2C0"
.LASF140:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF153:
	.string	"msg_id_string"
.LASF86:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF18:
	.string	"PRINT_LEVEL_INFO"
.LASF114:
	.string	"sleep_management_handle_t"
.LASF67:
	.string	"BT_IRQn"
.LASF164:
	.string	"sleep_management_register_resume_callback"
.LASF42:
	.string	"module_name"
.LASF93:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF133:
	.string	"suspend_user_register_count"
.LASF121:
	.string	"sleep_management_suspend_callback_func_t"
.LASF120:
	.string	"_Bool"
.LASF4:
	.string	"unsigned char"
.LASF96:
	.string	"SLEEP_BACKUP_RESTORE_SPI_MST1"
.LASF87:
	.string	"SLEEP_LOCK_USB"
.LASF21:
	.string	"print_level_t"
.LASF6:
	.string	"short int"
.LASF131:
	.string	"suspend_user_callback_func_table"
.LASF59:
	.string	"PMU_IRQn"
.LASF82:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF165:
	.string	"module"
.LASF60:
	.string	"MCU_DMA_IRQn"
.LASF134:
	.string	"resume_user_register_count"
.LASF35:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF132:
	.string	"resume_user_callback_func_table"
.LASF176:
	.string	"sleep_management_get_lock_sleep_request_info"
.LASF110:
	.string	"user_handle_resoure"
.LASF103:
	.string	"sleep_management_lock_sleep_t"
.LASF116:
	.string	"sleep_management_resume_callback_t"
.LASF148:
	.string	"sleep_management_get_lock_extslp_handle"
.LASF15:
	.string	"uint32_t"
.LASF163:
	.string	"sleep_management_suspend_callback"
.LASF46:
	.string	"dump_handle"
.LASF11:
	.string	"long double"
.LASF173:
	.string	"__lshrdi3"
.LASF12:
	.string	"char"
.LASF117:
	.string	"func"
.LASF49:
	.string	"log_control_block_t"
.LASF151:
	.string	"sleep_management_get_lock_sleep_handle_list"
.LASF54:
	.string	"UART_IRQn"
.LASF157:
	.string	"sleep_management_lock_sleep"
.LASF150:
	.string	"index"
.LASF48:
	.string	"msg_id_handle"
.LASF115:
	.string	"sleep_management_suspend_callback_t"
.LASF145:
	.string	"handle_index"
.LASF79:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF80:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF81:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF168:
	.string	"sleep_management_enter_deep_sleep"
.LASF123:
	.string	"mstatus"
.LASF75:
	.string	"SLEEP_LOCK_IRRX"
.LASF17:
	.string	"PRINT_LEVEL_DEBUG"
.LASF88:
	.string	"SLEEP_LOCK_UART0"
.LASF89:
	.string	"SLEEP_LOCK_UART1"
.LASF90:
	.string	"SLEEP_LOCK_UART2"
.LASF137:
	.string	"memset"
.LASF41:
	.string	"f_tlv_dump_t"
.LASF51:
	.string	"LED_IRQn"
.LASF83:
	.string	"SLEEP_LOCK_DCXO"
.LASF171:
	.string	"mstatus_value"
.LASF14:
	.string	"uint8_t"
.LASF92:
	.string	"SLEEP_LOCK_APP"
.LASF26:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF102:
	.string	"LOCK_SLEEP"
.LASF172:
	.string	"__ashldi3"
.LASF24:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF159:
	.string	"sleep_management_release_lock_handle"
.LASF40:
	.string	"f_msg_id_t"
.LASF73:
	.string	"SLEEP_LOCK_DMA"
.LASF177:
	.string	"sleep_management_enter_sleep"
.LASF25:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF56:
	.string	"RTC_IRQn"
.LASF142:
	.string	"lock"
.LASF76:
	.string	"SLEEP_LOCK_AIO"
.LASF125:
	.string	"sleep_context_t"
.LASF53:
	.string	"KEYSCAN_IRQn"
.LASF68:
	.string	"IRQ_NUMBER_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager_internal.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
