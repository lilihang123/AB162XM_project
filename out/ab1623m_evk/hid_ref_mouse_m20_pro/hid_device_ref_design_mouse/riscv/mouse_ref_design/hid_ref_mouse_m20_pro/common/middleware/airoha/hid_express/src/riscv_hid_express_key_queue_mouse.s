	.file	"riscv_hid_express_key_queue_mouse.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_key_queue_mouse.c"
	.section	.text.is_queue_full,"ax",@progbits
	.align	1
	.globl	is_queue_full
	.hidden	is_queue_full
	.type	is_queue_full, @function
is_queue_full:
.LFB7:
	.file 1 "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_key_queue_mouse.c"
	.loc 1 80 1
	.cfi_startproc
.LVL0:
	.loc 1 81 5
	.loc 1 81 31 is_stmt 0
	lw	a5,156(a0)
	.loc 1 81 52
	lw	a4,160(a0)
	.loc 1 81 31
	addi	a5,a5,1
	.loc 1 81 36
	andi	a5,a5,7
	.loc 1 81 52
	sub	a0,a5,a4
.LVL1:
	.loc 1 82 1
	seqz	a0,a0
	ret
	.cfi_endproc
.LFE7:
	.size	is_queue_full, .-is_queue_full
	.section	.text.is_key_expired,"ax",@progbits
	.align	1
	.globl	is_key_expired
	.hidden	is_key_expired
	.type	is_key_expired, @function
is_key_expired:
.LFB8:
	.loc 1 85 1 is_stmt 1
	.cfi_startproc
.LVL2:
	.loc 1 86 5
	.loc 1 85 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 87 5
	mv	a2,sp
	.loc 1 85 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 86 14
	sw	zero,0(sp)
	.loc 1 87 5 is_stmt 1
	call	hal_gpt_get_duration_count
.LVL3:
	.loc 1 89 5
	.loc 1 90 1 is_stmt 0
	lw	a0,0(sp)
	lw	ra,12(sp)
	.cfi_restore 1
	.loc 1 89 22
	li	a5,1998848
	addi	a5,a5,1152
	.loc 1 90 1
	sgtu	a0,a0,a5
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE8:
	.size	is_key_expired, .-is_key_expired
	.section	.text.is_queue_empty,"ax",@progbits
	.align	1
	.globl	is_queue_empty
	.hidden	is_queue_empty
	.type	is_queue_empty, @function
is_queue_empty:
.LFB9:
	.loc 1 94 1 is_stmt 1
	.cfi_startproc
.LVL4:
	.loc 1 95 5
	.loc 1 95 28 is_stmt 0
	lw	a5,156(a0)
	lw	a4,160(a0)
	sub	a0,a5,a4
.LVL5:
	.loc 1 96 1
	seqz	a0,a0
	ret
	.cfi_endproc
.LFE9:
	.size	is_queue_empty, .-is_queue_empty
	.section	.text.get_queue_count,"ax",@progbits
	.align	1
	.globl	get_queue_count
	.hidden	get_queue_count
	.type	get_queue_count, @function
get_queue_count:
.LFB10:
	.loc 1 100 1 is_stmt 1
	.cfi_startproc
.LVL6:
	.loc 1 101 5
	.loc 1 101 14 is_stmt 0
	lw	a5,160(a0)
	.loc 1 101 33
	lw	a0,156(a0)
.LVL7:
	.loc 1 101 8
	bltu	a5,a0,.L6
.L8:
	.loc 1 104 23
	sub	a0,a5,a0
	.loc 1 105 1
	ret
.L6:
	.loc 1 104 9 is_stmt 1
	.loc 1 104 23 is_stmt 0
	addi	a5,a5,8
	j	.L8
	.cfi_endproc
.LFE10:
	.size	get_queue_count, .-get_queue_count
	.section	.text.is_queue_num_2,"ax",@progbits
	.align	1
	.globl	is_queue_num_2
	.hidden	is_queue_num_2
	.type	is_queue_num_2, @function
is_queue_num_2:
.LFB11:
	.loc 1 109 1 is_stmt 1
	.cfi_startproc
.LVL8:
	.loc 1 110 5
	.loc 1 109 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 110 12
	call	get_queue_count
.LVL9:
	.loc 1 111 1
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 110 35 discriminator 1
	addi	a0,a0,-2
	.loc 1 111 1
	seqz	a0,a0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	is_queue_num_2, .-is_queue_num_2
	.section	.text.riscv_key_push_key_info,"ax",@progbits
	.align	1
	.globl	riscv_key_push_key_info
	.hidden	riscv_key_push_key_info
	.type	riscv_key_push_key_info, @function
riscv_key_push_key_info:
.LFB12:
	.loc 1 115 124 is_stmt 1
	.cfi_startproc
.LVL10:
	.loc 1 118 5
	.loc 1 118 40 is_stmt 0
	lw	a5,156(a0)
	addi	a5,a5,1
	.loc 1 118 45
	andi	a5,a5,7
	.loc 1 118 21
	sw	a5,156(a0)
	.loc 1 119 5 is_stmt 1
.LVL11:
	.loc 1 122 5
	slli	a5,a5,4
.LVL12:
	add	a0,a0,a5
.LVL13:
	.loc 1 125 5
	.loc 1 122 30 is_stmt 0
	li	a5,256
	sh	a5,12(a0)
	.loc 1 126 5 is_stmt 1
	.loc 1 126 30 is_stmt 0
	sw	a2,0(a0)
	.loc 1 127 5 is_stmt 1
	.loc 1 127 30 is_stmt 0
	sw	a3,4(a0)
	.loc 1 128 5 is_stmt 1
	.loc 1 128 26 is_stmt 0
	sb	a1,14(a0)
	.loc 1 129 5 is_stmt 1
	.loc 1 129 31 is_stmt 0
	sw	a4,8(a0)
	.loc 1 131 1
	ret
	.cfi_endproc
.LFE12:
	.size	riscv_key_push_key_info, .-riscv_key_push_key_info
	.section	.text.init_key_ctrl,"ax",@progbits
	.align	1
	.globl	init_key_ctrl
	.hidden	init_key_ctrl
	.type	init_key_ctrl, @function
init_key_ctrl:
.LFB13:
	.loc 1 136 1 is_stmt 1
	.cfi_startproc
.LVL14:
	.loc 1 137 5
	.loc 1 137 27 is_stmt 0
	li	a5,31
	sw	a5,128(a0)
	.loc 1 138 5 is_stmt 1
	.loc 1 138 21 is_stmt 0
	sw	zero,156(a0)
	.loc 1 139 5 is_stmt 1
	.loc 1 139 21 is_stmt 0
	sw	zero,160(a0)
	.loc 1 140 5 is_stmt 1
	.loc 1 140 27 is_stmt 0
	sw	a1,132(a0)
	.loc 1 141 1
	ret
	.cfi_endproc
.LFE13:
	.size	init_key_ctrl, .-init_key_ctrl
	.section	.text.riscv_key_clear_key_pushed,"ax",@progbits
	.align	1
	.globl	riscv_key_clear_key_pushed
	.hidden	riscv_key_clear_key_pushed
	.type	riscv_key_clear_key_pushed, @function
riscv_key_clear_key_pushed:
.LFB14:
	.loc 1 144 1 is_stmt 1
	.cfi_startproc
.LVL15:
	.loc 1 146 5
	.loc 1 146 27 is_stmt 0
	li	a5,31
	sw	a5,128(a0)
	.loc 1 147 5 is_stmt 1
	.loc 1 147 26 is_stmt 0
	sw	zero,136(a0)
	.loc 1 148 5 is_stmt 1
	.loc 1 148 27 is_stmt 0
	sw	zero,132(a0)
	.loc 1 149 1
	ret
	.cfi_endproc
.LFE14:
	.size	riscv_key_clear_key_pushed, .-riscv_key_clear_key_pushed
	.section	.text.riscv_key_push,"ax",@progbits
	.align	1
	.globl	riscv_key_push
	.hidden	riscv_key_push
	.type	riscv_key_push, @function
riscv_key_push:
.LFB15:
	.loc 1 153 1 is_stmt 1
	.cfi_startproc
.LVL16:
	.loc 1 154 5
	.loc 1 153 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	s1,4(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 153 1
	mv	s0,a0
	mv	s1,a1
.LVL17:
	.loc 1 155 5 is_stmt 1
	.loc 1 156 5
	.loc 1 157 5
	.loc 1 153 1 is_stmt 0
	sw	a2,0(sp)
	.loc 1 157 9
	call	is_queue_full
.LVL18:
	.loc 1 157 8 discriminator 1
	bne	a0,zero,.L20
	.loc 1 164 5 is_stmt 1
	.loc 1 164 18 is_stmt 0
	lw	a3,132(s0)
	.loc 1 164 60
	lw	a2,4(s1)
	.loc 1 165 23
	lw	a4,16(s1)
	.loc 1 164 35
	andi	a0,a3,255
	.loc 1 166 23
	lw	a1,20(s1)
	.loc 1 164 8
	bne	a0,a2,.L16
	.loc 1 166 9
	or	t1,a4,a1
	.loc 1 156 14
	li	a0,7
	.loc 1 166 9
	beq	t1,zero,.L17
.L16:
	.loc 1 169 9 is_stmt 1
	.loc 1 169 122 is_stmt 0
	slli	a1,a1,24
	.loc 1 169 39
	andi	a2,a2,255
	.loc 1 169 24
	or	a2,a2,a1
	.loc 1 169 84
	slli	a4,a4,16
	li	a1,16711680
	and	a4,a4,a1
	.loc 1 169 24
	or	a2,a2,a4
.LVL19:
	.loc 1 170 9 is_stmt 1
	.loc 1 172 9 is_stmt 0
	lw	a4,0(sp)
	.loc 1 170 30
	sw	a3,136(s0)
	.loc 1 171 9 is_stmt 1
	.loc 1 172 9 is_stmt 0
	mv	a0,s0
	.loc 1 171 31
	sw	a2,132(s0)
	.loc 1 172 9 is_stmt 1
	li	a3,0
	li	a1,0
	call	riscv_key_push_key_info
.LVL20:
	.loc 1 173 9
	.loc 1 173 16 is_stmt 0
	li	a0,0
.LVL21:
.L17:
	.loc 1 178 5 is_stmt 1
	.loc 1 178 57 is_stmt 0
	lw	a2,28(s1)
	.loc 1 178 7
	lw	a4,144(s0)
	.loc 1 179 61
	lw	a3,32(s1)
	.loc 1 178 7
	bne	a4,a2,.L18
	.loc 1 179 9
	lw	a4,148(s0)
	beq	a4,a3,.L19
.L18:
	.loc 1 181 9 is_stmt 1
	.loc 1 183 9 is_stmt 0
	lw	a4,0(sp)
	mv	a0,s0
.LVL22:
	.loc 1 181 38
	sw	a2,144(s0)
	.loc 1 182 9 is_stmt 1
	.loc 1 182 38 is_stmt 0
	sw	a3,148(s0)
	.loc 1 183 9 is_stmt 1
	li	a1,1
	call	riscv_key_push_key_info
.LVL23:
	.loc 1 184 9
	.loc 1 184 16 is_stmt 0
	li	a0,0
.LVL24:
.L19:
	.loc 1 188 5 is_stmt 1
	.loc 1 188 50 is_stmt 0
	lw	a2,36(s1)
	.loc 1 188 7
	lw	a5,152(s0)
	beq	a5,a2,.L14
	.loc 1 190 9 is_stmt 1
	.loc 1 191 9 is_stmt 0
	lw	a4,0(sp)
	mv	a0,s0
.LVL25:
	.loc 1 190 40
	sw	a2,152(s0)
	.loc 1 191 9 is_stmt 1
	li	a3,0
	li	a1,2
	call	riscv_key_push_key_info
.LVL26:
	.loc 1 192 9
	.loc 1 192 16 is_stmt 0
	li	a0,0
.LVL27:
.L14:
	.loc 1 205 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL28:
	lw	s1,4(sp)
	.cfi_restore 9
.LVL29:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
.LVL30:
	jr	ra
.LVL31:
.L20:
	.cfi_restore_state
	.loc 1 160 16
	li	a0,5
.LVL32:
	j	.L14
	.cfi_endproc
.LFE15:
	.size	riscv_key_push, .-riscv_key_push
	.section	.text.riscv_key_pop_temperory,"ax",@progbits
	.align	1
	.globl	riscv_key_pop_temperory
	.hidden	riscv_key_pop_temperory
	.type	riscv_key_pop_temperory, @function
riscv_key_pop_temperory:
.LFB16:
	.loc 1 209 1 is_stmt 1
	.cfi_startproc
.LVL33:
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	mv	s1,a1
	sw	s0,12(sp)
	.cfi_offset 8, -8
	mv	a4,a0
	mv	a1,a2
.LVL34:
	.loc 1 210 5
	.loc 1 211 5
.L25:
	.loc 1 211 12
.LBB7:
.LBB8:
	.loc 1 95 5
	.loc 1 95 36 is_stmt 0
	lw	s0,160(a4)
.LVL35:
.LBE8:
.LBE7:
	.loc 1 211 12 discriminator 1
	lw	a3,156(a4)
	bne	a3,s0,.L31
	.loc 1 287 5 is_stmt 1
	.loc 1 287 20 is_stmt 0
	li	a4,2
	sw	a4,0(s1)
	.loc 1 288 5 is_stmt 1
	.loc 1 288 12 is_stmt 0
	li	a0,4
	j	.L24
.L31:
.LBB9:
	.loc 1 213 9 is_stmt 1
	.loc 1 213 53 is_stmt 0
	addi	s0,s0,1
	.loc 1 213 58
	andi	s0,s0,7
	.loc 1 213 34
	sw	s0,140(a4)
	.loc 1 215 9 is_stmt 1
.LVL36:
	.loc 1 218 9
	slli	s0,s0,4
.LVL37:
	add	s0,a4,s0
.LVL38:
	.loc 1 218 13 is_stmt 0
	lw	a0,8(s0)
	sw	a4,4(sp)
	sw	a1,0(sp)
	call	is_key_expired
.LVL39:
	.loc 1 218 12 discriminator 1
	beq	a0,zero,.L26
	.loc 1 221 13 is_stmt 1
	.loc 1 233 48 is_stmt 0
	lw	a4,4(sp)
	.loc 1 221 52
	li	a3,5
	sb	a3,13(s0)
	.loc 1 222 13 is_stmt 1
	.loc 1 233 13
	.loc 1 233 48 is_stmt 0
	lw	a3,160(a4)
	lw	a1,0(sp)
	addi	a3,a3,1
	.loc 1 233 53
	andi	a3,a3,7
	.loc 1 233 29
	sw	a3,160(a4)
	j	.L25
.L26:
	.loc 1 236 13 is_stmt 1
	.loc 1 236 37 is_stmt 0
	lbu	a4,14(s0)
	.loc 1 236 13
	li	a3,1
	beq	a4,a3,.L27
	li	a3,2
	beq	a4,a3,.L28
	bne	a4,zero,.L29
	.loc 1 240 21 is_stmt 1
	.loc 1 241 59 is_stmt 0
	lw	a4,0(s0)
	.loc 1 240 36
	sw	a3,0(s1)
	.loc 1 241 21 is_stmt 1
	.loc 1 241 63 is_stmt 0
	andi	a2,a4,255
	.loc 1 241 33
	sw	a2,4(s1)
	.loc 1 242 21 is_stmt 1
	.loc 1 242 65 is_stmt 0
	srli	a2,a4,16
	.loc 1 242 72
	andi	a2,a2,255
	.loc 1 243 65
	srli	a4,a4,24
	.loc 1 242 34
	sw	a2,16(s1)
	.loc 1 243 21 is_stmt 1
	.loc 1 243 34 is_stmt 0
	sw	a4,20(s1)
	.loc 1 244 21 is_stmt 1
	.loc 1 244 60 is_stmt 0
	sb	a3,13(s0)
	.loc 1 246 17 is_stmt 1
.L29:
	.loc 1 283 20 is_stmt 0
	li	a0,0
.LVL40:
.L24:
.LBE9:
	.loc 1 289 1
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
.LVL41:
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL42:
.L27:
	.cfi_restore_state
.LBB10:
	.loc 1 251 21 is_stmt 1
	.loc 1 251 36 is_stmt 0
	li	a4,9
	sw	a4,0(s1)
	.loc 1 252 21 is_stmt 1
	.loc 1 252 71 is_stmt 0
	lw	a4,0(s0)
	.loc 1 254 60
	li	a5,2
	.loc 1 252 71
	slli	a4,a4,1
	srli	a4,a4,1
	.loc 1 252 41
	sw	a4,28(s1)
	.loc 1 253 21 is_stmt 1
	.loc 1 253 41 is_stmt 0
	lw	a4,4(s0)
	sw	a4,32(s1)
	.loc 1 254 21 is_stmt 1
	.loc 1 254 60 is_stmt 0
	sb	a5,13(s0)
	.loc 1 256 17 is_stmt 1
	j	.L29
.L28:
	.loc 1 260 21
	.loc 1 260 36 is_stmt 0
	li	a3,10
	sw	a3,0(s1)
	.loc 1 261 21 is_stmt 1
	.loc 1 261 43 is_stmt 0
	lw	a3,0(s0)
	sw	a3,36(s1)
	.loc 1 262 21 is_stmt 1
	.loc 1 262 60 is_stmt 0
	sb	a4,13(s0)
	.loc 1 265 17 is_stmt 1
	j	.L29
.LBE10:
	.cfi_endproc
.LFE16:
	.size	riscv_key_pop_temperory, .-riscv_key_pop_temperory
	.section	.text.riscv_key_pop_confirm,"ax",@progbits
	.align	1
	.globl	riscv_key_pop_confirm
	.hidden	riscv_key_pop_confirm
	.type	riscv_key_pop_confirm, @function
riscv_key_pop_confirm:
.LFB17:
	.loc 1 293 1
	.cfi_startproc
.LVL43:
	.loc 1 294 5
.LBB11:
.LBB12:
	.loc 1 95 5
	.loc 1 95 36 is_stmt 0
	lw	a5,160(a0)
.LVL44:
.LBE12:
.LBE11:
	.loc 1 294 8 discriminator 1
	lw	a4,156(a0)
	beq	a4,a5,.L34
	.loc 1 295 13 is_stmt 1
	.loc 1 295 56 is_stmt 0
	lw	a4,140(a0)
	slli	a4,a4,4
	add	a4,a0,a4
	.loc 1 295 16
	lbu	a3,13(a4)
	li	a4,4
	bne	a3,a4,.L34
	.loc 1 296 17 is_stmt 1
	.loc 1 297 17
	.loc 1 297 52 is_stmt 0
	addi	a5,a5,1
	.loc 1 297 57
	andi	a5,a5,7
	.loc 1 297 33
	sw	a5,160(a0)
.L34:
	.loc 1 298 17 is_stmt 1
	.loc 1 301 5
	.loc 1 302 1 is_stmt 0
	li	a0,0
.LVL45:
	ret
	.cfi_endproc
.LFE17:
	.size	riscv_key_pop_confirm, .-riscv_key_pop_confirm
	.section	.text.riscv_hid_express_key_queue_debug_print,"ax",@progbits
	.align	1
	.globl	riscv_hid_express_key_queue_debug_print
	.hidden	riscv_hid_express_key_queue_debug_print
	.type	riscv_hid_express_key_queue_debug_print, @function
riscv_hid_express_key_queue_debug_print:
.LFB18:
	.loc 1 305 1 is_stmt 1
	.cfi_startproc
.LVL46:
	.loc 1 308 5
	.loc 1 308 15 is_stmt 0
	lw	a4,164(a0)
	.loc 1 308 8
	lw	a5,160(a0)
	beq	a4,a5,.L42
	.loc 1 305 1
	addi	sp,sp,-28
	.cfi_def_cfa_offset 28
	.loc 1 308 96 discriminator 1
	slli	a5,a4,4
	.loc 1 305 1
	sw	s0,20(sp)
	sw	ra,24(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 308 96 discriminator 1
	add	a5,a0,a5
	lbu	a5,13(a5)
	mv	s0,a0
	.loc 1 308 54 discriminator 1
	beq	a5,zero,.L37
	.loc 1 308 144 discriminator 2
	li	a3,5
	bne	a5,a3,.L35
.L37:
.LBB13:
	.loc 1 311 9 is_stmt 1
	.loc 1 311 83 is_stmt 0
	addi	a5,a4,1
	.loc 1 311 88
	andi	a5,a5,7
.LVL47:
	.loc 1 313 9 is_stmt 1
.LBB14:
	.loc 1 313 14
	.loc 1 313 67
	.loc 1 313 264
	slli	a5,a5,4
.LVL48:
	add	a5,s0,a5
.LVL49:
	lw	a3,8(a5)
	lla	a2,msg_id_string.0
	li	a1,1
.LVL50:
	sw	a3,12(sp)
	lbu	a3,12(a5)
	lla	a0,log_control_block_rv_exp
.LVL51:
	sw	a3,8(sp)
	lw	a3,0(a5)
	sw	a3,4(sp)
	lw	a3,4(a5)
	sw	a3,0(sp)
	lbu	a5,14(a5)
.LVL52:
	li	a3,9
	call	print_module_msgid_log
.LVL53:
.LBE14:
	.loc 1 313 12 discriminator 1
	.loc 1 323 9
	.loc 1 323 60 is_stmt 0
	lw	a5,164(s0)
	addi	a5,a5,1
	.loc 1 323 65
	andi	a5,a5,7
	.loc 1 323 33
	sw	a5,164(s0)
.LVL54:
.L35:
.LBE13:
	.loc 1 327 1
	lw	ra,24(sp)
	.cfi_restore 1
	lw	s0,20(sp)
	.cfi_restore 8
.LVL55:
	addi	sp,sp,28
	.cfi_def_cfa_offset 0
	jr	ra
.LVL56:
.L42:
	ret
	.cfi_endproc
.LFE18:
	.size	riscv_hid_express_key_queue_debug_print, .-riscv_hid_express_key_queue_debug_print
	.section	.text.rv_hid_exp_key_queue_post_process,"ax",@progbits
	.align	1
	.globl	rv_hid_exp_key_queue_post_process
	.hidden	rv_hid_exp_key_queue_post_process
	.type	rv_hid_exp_key_queue_post_process, @function
rv_hid_exp_key_queue_post_process:
.LFB19:
	.loc 1 332 1 is_stmt 1
	.cfi_startproc
.LVL57:
	.loc 1 333 5
	.loc 1 337 5
	lw	a5,140(a0)
	slli	a5,a5,4
	add	a0,a0,a5
.LVL58:
	lbu	a4,13(a0)
	li	a5,4
	bne	a4,a5,.L45
	.loc 1 351 13
	.loc 1 351 52 is_stmt 0
	sb	zero,13(a0)
	.loc 1 353 9 is_stmt 1
.L45:
	.loc 1 355 1 is_stmt 0
	ret
	.cfi_endproc
.LFE19:
	.size	rv_hid_exp_key_queue_post_process, .-rv_hid_exp_key_queue_post_process
	.section	.text.rv_hid_exp_key_queue_tx_result_handle,"ax",@progbits
	.align	1
	.globl	rv_hid_exp_key_queue_tx_result_handle
	.hidden	rv_hid_exp_key_queue_tx_result_handle
	.type	rv_hid_exp_key_queue_tx_result_handle, @function
rv_hid_exp_key_queue_tx_result_handle:
.LFB20:
	.loc 1 358 1 is_stmt 1
	.cfi_startproc
.LVL59:
	.loc 1 361 5
.LBB17:
.LBB18:
	.loc 1 362 28 is_stmt 0
	lw	a4,140(a0)
	slli	a4,a4,4
	.loc 1 362 69
	add	a5,a0,a4
.LBE18:
.LBE17:
	.loc 1 361 8
	bne	a1,zero,.L48
.LVL60:
.LBB20:
.LBB19:
	.loc 1 362 9 is_stmt 1
	.loc 1 362 69 is_stmt 0
	li	a4,4
	sb	a4,13(a5)
	.loc 1 363 9 is_stmt 1
	tail	riscv_key_pop_confirm
.LVL61:
.L48:
.LBE19:
.LBE20:
	.loc 1 366 9
	.loc 1 367 9
	.loc 1 367 57 is_stmt 0
	lbu	a4,12(a5)
	addi	a4,a4,1
	sb	a4,12(a5)
	.loc 1 368 9 is_stmt 1
	.loc 1 372 1 is_stmt 0
	ret
	.cfi_endproc
.LFE20:
	.size	rv_hid_exp_key_queue_tx_result_handle, .-rv_hid_exp_key_queue_tx_result_handle
	.section	.text.rv_hid_exp_key_queue_pre_process,"ax",@progbits
	.align	1
	.globl	rv_hid_exp_key_queue_pre_process
	.hidden	rv_hid_exp_key_queue_pre_process
	.type	rv_hid_exp_key_queue_pre_process, @function
rv_hid_exp_key_queue_pre_process:
.LFB21:
	.loc 1 377 1 is_stmt 1
	.cfi_startproc
.LVL62:
	.loc 1 378 5
	.loc 1 378 48 is_stmt 0
	lw	a4,140(a0)
	slli	a4,a4,4
	add	a5,a0,a4
	.loc 1 378 8
	lbu	a4,13(a5)
	li	a5,2
	bne	a4,a5,.L49
	.loc 1 379 9 is_stmt 1
	.loc 1 380 9
	tail	rv_hid_exp_key_queue_tx_result_handle
.LVL63:
.L49:
	.loc 1 383 1 is_stmt 0
	ret
	.cfi_endproc
.LFE21:
	.size	rv_hid_exp_key_queue_pre_process, .-rv_hid_exp_key_queue_pre_process
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 104
msg_id_string.0:
	.string	"[M:rv_exp C:info F: L: ]: Index[%d], type = %d, key = (%08X-%08X <--), retry cnt = %08X, timestamp = %d"
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 4 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 5 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_key_queue_mouse.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xb08
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x1f
	.4byte	.LASF135
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL36
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x6
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x6
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x6
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x6
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x20
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x6
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x21
	.byte	0x4
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x1a
	.4byte	0x75
	.uleb128 0x8
	.4byte	0x7c
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x2
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x14
	.4byte	0x9e
	.4byte	0xba
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.byte	0x2
	.4byte	.LASF16
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x3
	.byte	0x3d
	.4byte	0xe5
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
	.byte	0x3
	.byte	0x42
	.byte	0x3
	.4byte	0xc1
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x3
	.byte	0x45
	.4byte	0x157
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
	.byte	0x3
	.byte	0x57
	.byte	0x3
	.4byte	0xf1
	.uleb128 0x5
	.4byte	.LASF38
	.byte	0x3
	.byte	0x59
	.byte	0x10
	.4byte	0x16f
	.uleb128 0x8
	.4byte	0x174
	.uleb128 0x16
	.4byte	0x194
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xe5
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x12
	.byte	0
	.uleb128 0x5
	.4byte	.LASF39
	.byte	0x3
	.byte	0x5a
	.byte	0x10
	.4byte	0x1a0
	.uleb128 0x8
	.4byte	0x1a5
	.uleb128 0x16
	.4byte	0x1cf
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xe5
	.uleb128 0x2
	.4byte	0x1cf
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x12
	.byte	0
	.uleb128 0x8
	.4byte	0x1d4
	.uleb128 0x22
	.uleb128 0x5
	.4byte	.LASF40
	.byte	0x3
	.byte	0x5b
	.byte	0x10
	.4byte	0x1e1
	.uleb128 0x8
	.4byte	0x1e6
	.uleb128 0x16
	.4byte	0x201
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xe5
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0x12
	.byte	0
	.uleb128 0x5
	.4byte	.LASF41
	.byte	0x3
	.byte	0x5c
	.byte	0x14
	.4byte	0x20d
	.uleb128 0x8
	.4byte	0x212
	.uleb128 0x23
	.4byte	0x9e
	.4byte	0x235
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xe5
	.uleb128 0x2
	.4byte	0x157
	.uleb128 0x2
	.4byte	0x235
	.uleb128 0x2
	.4byte	0x23a
	.byte	0
	.uleb128 0x8
	.4byte	0x1cf
	.uleb128 0x8
	.4byte	0x9e
	.uleb128 0x13
	.byte	0x1c
	.byte	0x3
	.byte	0x5e
	.4byte	0x2a3
	.uleb128 0x3
	.4byte	.LASF42
	.byte	0x3
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x3
	.4byte	.LASF43
	.byte	0x3
	.byte	0x60
	.byte	0xe
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF44
	.byte	0x3
	.byte	0x61
	.byte	0xe
	.4byte	0x9e
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF45
	.byte	0x3
	.byte	0x62
	.byte	0xf
	.4byte	0x163
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF46
	.byte	0x3
	.byte	0x63
	.byte	0x15
	.4byte	0x194
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF47
	.byte	0x3
	.byte	0x64
	.byte	0x12
	.4byte	0x201
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF48
	.byte	0x3
	.byte	0x65
	.byte	0x10
	.4byte	0x1d5
	.byte	0x18
	.byte	0
	.uleb128 0x5
	.4byte	.LASF49
	.byte	0x3
	.byte	0x66
	.byte	0x3
	.4byte	0x23f
	.uleb128 0x13
	.byte	0x28
	.byte	0x4
	.byte	0x8d
	.4byte	0x320
	.uleb128 0x3
	.4byte	.LASF50
	.byte	0x4
	.byte	0x8e
	.byte	0xe
	.4byte	0x9e
	.byte	0
	.uleb128 0x10
	.string	"k"
	.byte	0x8f
	.byte	0xe
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x10
	.string	"x"
	.byte	0x90
	.byte	0xd
	.4byte	0x86
	.byte	0x8
	.uleb128 0x10
	.string	"y"
	.byte	0x91
	.byte	0xd
	.4byte	0x86
	.byte	0xc
	.uleb128 0x10
	.string	"z1"
	.byte	0x92
	.byte	0xd
	.4byte	0x86
	.byte	0x10
	.uleb128 0x10
	.string	"z2"
	.byte	0x93
	.byte	0xd
	.4byte	0x86
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF51
	.byte	0x4
	.byte	0x94
	.byte	0xe
	.4byte	0x9e
	.byte	0x18
	.uleb128 0x3
	.4byte	.LASF52
	.byte	0x4
	.byte	0x95
	.byte	0xe
	.4byte	0xaa
	.byte	0x1c
	.uleb128 0x3
	.4byte	.LASF53
	.byte	0x4
	.byte	0x96
	.byte	0xe
	.4byte	0x9e
	.byte	0x24
	.byte	0
	.uleb128 0x5
	.4byte	.LASF54
	.byte	0x4
	.byte	0x9c
	.byte	0x2
	.4byte	0x2af
	.uleb128 0x8
	.4byte	0x320
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x5
	.byte	0x29
	.4byte	0x373
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF64
	.byte	0x5
	.byte	0x34
	.byte	0x3
	.4byte	0x331
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x5
	.byte	0x36
	.4byte	0x3a3
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x3
	.byte	0
	.uleb128 0x13
	.byte	0x10
	.byte	0x5
	.byte	0x4a
	.4byte	0x3ed
	.uleb128 0x3
	.4byte	.LASF69
	.byte	0x5
	.byte	0x4b
	.byte	0xe
	.4byte	0xaa
	.byte	0
	.uleb128 0x3
	.4byte	.LASF70
	.byte	0x5
	.byte	0x4c
	.byte	0xe
	.4byte	0x9e
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF71
	.byte	0x5
	.byte	0x4d
	.byte	0xd
	.4byte	0x92
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF72
	.byte	0x5
	.byte	0x4e
	.byte	0xd
	.4byte	0x92
	.byte	0xd
	.uleb128 0x3
	.4byte	.LASF50
	.byte	0x5
	.byte	0x4f
	.byte	0xd
	.4byte	0x92
	.byte	0xe
	.byte	0
	.uleb128 0x5
	.4byte	.LASF73
	.byte	0x5
	.byte	0x50
	.byte	0x2
	.4byte	0x3a3
	.uleb128 0x13
	.byte	0xa8
	.byte	0x5
	.byte	0x52
	.4byte	0x484
	.uleb128 0x3
	.4byte	.LASF74
	.byte	0x5
	.byte	0x53
	.byte	0x12
	.4byte	0x484
	.byte	0
	.uleb128 0x3
	.4byte	.LASF75
	.byte	0x5
	.byte	0x54
	.byte	0xe
	.4byte	0x9e
	.byte	0x80
	.uleb128 0x3
	.4byte	.LASF76
	.byte	0x5
	.byte	0x55
	.byte	0xe
	.4byte	0x9e
	.byte	0x84
	.uleb128 0x3
	.4byte	.LASF77
	.byte	0x5
	.byte	0x56
	.byte	0xe
	.4byte	0x9e
	.byte	0x88
	.uleb128 0x3
	.4byte	.LASF78
	.byte	0x5
	.byte	0x57
	.byte	0xe
	.4byte	0x9e
	.byte	0x8c
	.uleb128 0x3
	.4byte	.LASF79
	.byte	0x5
	.byte	0x59
	.byte	0xe
	.4byte	0xaa
	.byte	0x90
	.uleb128 0x3
	.4byte	.LASF80
	.byte	0x5
	.byte	0x5a
	.byte	0xe
	.4byte	0x9e
	.byte	0x98
	.uleb128 0x3
	.4byte	.LASF81
	.byte	0x5
	.byte	0x5b
	.byte	0xe
	.4byte	0x9e
	.byte	0x9c
	.uleb128 0x3
	.4byte	.LASF82
	.byte	0x5
	.byte	0x5c
	.byte	0xe
	.4byte	0x9e
	.byte	0xa0
	.uleb128 0x3
	.4byte	.LASF83
	.byte	0x5
	.byte	0x5d
	.byte	0xe
	.4byte	0x9e
	.byte	0xa4
	.byte	0
	.uleb128 0x14
	.4byte	0x3ed
	.4byte	0x494
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.4byte	.LASF84
	.byte	0x5
	.byte	0x5e
	.byte	0x2
	.4byte	0x3f9
	.uleb128 0x24
	.byte	0x5
	.byte	0x4
	.4byte	0x65
	.byte	0x6
	.2byte	0x153
	.byte	0xe
	.4byte	0x4e0
	.uleb128 0x9
	.4byte	.LASF85
	.sleb128 -7
	.uleb128 0x9
	.4byte	.LASF86
	.sleb128 -6
	.uleb128 0x9
	.4byte	.LASF87
	.sleb128 -5
	.uleb128 0x9
	.4byte	.LASF88
	.sleb128 -4
	.uleb128 0x9
	.4byte	.LASF89
	.sleb128 -3
	.uleb128 0x9
	.4byte	.LASF90
	.sleb128 -2
	.uleb128 0x9
	.4byte	.LASF91
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0
	.byte	0
	.uleb128 0x25
	.4byte	.LASF93
	.byte	0x6
	.2byte	0x15c
	.byte	0x3
	.4byte	0x4a0
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x1
	.byte	0x34
	.4byte	0x51d
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x5
	.byte	0
	.uleb128 0x26
	.4byte	.LASF103
	.byte	0x3
	.2byte	0x129
	.byte	0xd
	.4byte	0x540
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xe5
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0x12
	.byte	0
	.uleb128 0x27
	.4byte	.LASF128
	.byte	0x6
	.2byte	0x199
	.byte	0x12
	.4byte	0x4e0
	.4byte	0x561
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0x2
	.4byte	0x23a
	.byte	0
	.uleb128 0x17
	.4byte	.LASF105
	.2byte	0x178
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5cb
	.uleb128 0xa
	.4byte	.LASF100
	.2byte	0x178
	.byte	0x3b
	.4byte	0x5cb
	.4byte	.LLST33
	.uleb128 0xa
	.4byte	.LASF101
	.2byte	0x178
	.byte	0x4b
	.4byte	0x9e
	.4byte	.LLST34
	.uleb128 0xa
	.4byte	.LASF102
	.2byte	0x178
	.byte	0x5f
	.4byte	0x9e
	.4byte	.LLST35
	.uleb128 0x1b
	.4byte	.LVL63
	.4byte	0x5d0
	.uleb128 0x4
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
	.uleb128 0x4
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
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x494
	.uleb128 0x28
	.4byte	.LASF104
	.byte	0x1
	.2byte	0x165
	.byte	0x6
	.byte	0x1
	.4byte	0x5f3
	.uleb128 0x1c
	.4byte	.LASF100
	.byte	0x40
	.4byte	0x5cb
	.uleb128 0x1c
	.4byte	.LASF101
	.byte	0x50
	.4byte	0x9e
	.byte	0
	.uleb128 0x17
	.4byte	.LASF106
	.2byte	0x14b
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x638
	.uleb128 0xa
	.4byte	.LASF100
	.2byte	0x14b
	.byte	0x3c
	.4byte	0x5cb
	.4byte	.LLST26
	.uleb128 0x29
	.4byte	.LASF107
	.byte	0x1
	.2byte	0x14b
	.byte	0x4c
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1d
	.4byte	.LASF110
	.2byte	0x14d
	.byte	0x13
	.4byte	0x638
	.4byte	.LLST27
	.byte	0
	.uleb128 0x8
	.4byte	0x3ed
	.uleb128 0x17
	.4byte	.LASF108
	.2byte	0x130
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x6d4
	.uleb128 0xa
	.4byte	.LASF100
	.2byte	0x130
	.byte	0x42
	.4byte	0x5cb
	.4byte	.LLST23
	.uleb128 0xa
	.4byte	.LASF109
	.2byte	0x130
	.byte	0x52
	.4byte	0x9e
	.4byte	.LLST24
	.uleb128 0x1e
	.4byte	.LBB13
	.4byte	.LBE13-.LBB13
	.uleb128 0x1d
	.4byte	.LASF110
	.2byte	0x137
	.byte	0x17
	.4byte	0x638
	.4byte	.LLST25
	.uleb128 0x1e
	.4byte	.LBB14
	.4byte	.LBE14-.LBB14
	.uleb128 0x2a
	.4byte	.LASF136
	.byte	0x1
	.2byte	0x139
	.byte	0x29
	.4byte	0x2a3
	.uleb128 0x2b
	.4byte	.LASF111
	.byte	0x1
	.2byte	0x139
	.byte	0x82
	.4byte	0x6e4
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x11
	.4byte	.LVL53
	.4byte	0x51d
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x39
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x14
	.4byte	0x7c
	.4byte	0x6e4
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x67
	.byte	0
	.uleb128 0x1a
	.4byte	0x6d4
	.uleb128 0x2c
	.4byte	.LASF112
	.byte	0x1
	.2byte	0x124
	.byte	0x12
	.4byte	0x373
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x730
	.uleb128 0xa
	.4byte	.LASF100
	.2byte	0x124
	.byte	0x3c
	.4byte	0x5cb
	.4byte	.LLST21
	.uleb128 0x2d
	.4byte	0x9d9
	.4byte	.LBB11
	.4byte	.LBE11-.LBB11
	.byte	0x1
	.2byte	0x126
	.byte	0xa
	.uleb128 0xb
	.4byte	0x9ea
	.4byte	.LLST22
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF113
	.byte	0xd0
	.byte	0x12
	.4byte	0x373
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x7ca
	.uleb128 0x7
	.4byte	.LASF100
	.byte	0xd0
	.byte	0x3e
	.4byte	0x5cb
	.4byte	.LLST14
	.uleb128 0x7
	.4byte	.LASF114
	.byte	0xd0
	.byte	0x4b
	.4byte	0x73
	.4byte	.LLST15
	.uleb128 0x7
	.4byte	.LASF70
	.byte	0xd0
	.byte	0x63
	.4byte	0x9e
	.4byte	.LLST16
	.uleb128 0xe
	.4byte	.LASF115
	.byte	0xd2
	.byte	0x1b
	.4byte	0x32c
	.4byte	.LLST17
	.uleb128 0x2e
	.4byte	.LLRL19
	.4byte	0x7af
	.uleb128 0xe
	.4byte	.LASF110
	.byte	0xd7
	.byte	0x17
	.4byte	0x638
	.4byte	.LLST20
	.uleb128 0x11
	.4byte	.LVL39
	.4byte	0x9f7
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x2f
	.4byte	0x9d9
	.4byte	.LBB7
	.4byte	.LBE7-.LBB7
	.byte	0x1
	.byte	0xd3
	.byte	0xd
	.uleb128 0xb
	.4byte	0x9ea
	.4byte	.LLST18
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF116
	.byte	0x98
	.byte	0x12
	.4byte	0x373
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x8b8
	.uleb128 0x7
	.4byte	.LASF100
	.byte	0x98
	.byte	0x35
	.4byte	0x5cb
	.4byte	.LLST8
	.uleb128 0x7
	.4byte	.LASF114
	.byte	0x98
	.byte	0x43
	.4byte	0x73
	.4byte	.LLST9
	.uleb128 0x7
	.4byte	.LASF70
	.byte	0x98
	.byte	0x5c
	.4byte	0x9e
	.4byte	.LLST10
	.uleb128 0xe
	.4byte	.LASF115
	.byte	0x9a
	.byte	0x1b
	.4byte	0x32c
	.4byte	.LLST11
	.uleb128 0xe
	.4byte	.LASF117
	.byte	0x9b
	.byte	0xe
	.4byte	0x9e
	.4byte	.LLST12
	.uleb128 0xe
	.4byte	.LASF118
	.byte	0x9c
	.byte	0xe
	.4byte	0x9e
	.4byte	.LLST13
	.uleb128 0x18
	.4byte	.LVL18
	.4byte	0xa68
	.4byte	0x851
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x18
	.4byte	.LVL20
	.4byte	0x909
	.4byte	0x876
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x18
	.4byte	.LVL23
	.4byte	0x909
	.4byte	0x896
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x11
	.4byte	.LVL26
	.4byte	0x909
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x19
	.4byte	.LASF119
	.byte	0x8f
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x8da
	.uleb128 0xc
	.4byte	.LASF100
	.byte	0x8f
	.byte	0x35
	.4byte	0x5cb
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x19
	.4byte	.LASF120
	.byte	0x87
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x909
	.uleb128 0xc
	.4byte	.LASF100
	.byte	0x87
	.byte	0x28
	.4byte	0x5cb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0xc
	.4byte	.LASF121
	.byte	0x87
	.byte	0x38
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x5b
	.byte	0
	.uleb128 0x19
	.4byte	.LASF122
	.byte	0x73
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x970
	.uleb128 0x7
	.4byte	.LASF100
	.byte	0x73
	.byte	0x32
	.4byte	0x5cb
	.4byte	.LLST6
	.uleb128 0xc
	.4byte	.LASF50
	.byte	0x73
	.byte	0x42
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0xc
	.4byte	.LASF123
	.byte	0x73
	.byte	0x51
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0xc
	.4byte	.LASF124
	.byte	0x73
	.byte	0x61
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0xc
	.4byte	.LASF70
	.byte	0x73
	.byte	0x71
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0xe
	.4byte	.LASF125
	.byte	0x77
	.byte	0x13
	.4byte	0x638
	.4byte	.LLST7
	.byte	0
	.uleb128 0xd
	.4byte	.LASF126
	.byte	0x6c
	.byte	0x5
	.4byte	0xba
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9b0
	.uleb128 0x7
	.4byte	.LASF100
	.byte	0x6c
	.byte	0x28
	.4byte	0x5cb
	.4byte	.LLST5
	.uleb128 0x11
	.4byte	.LVL9
	.4byte	0x9b0
	.uleb128 0x4
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
	.byte	0
	.uleb128 0xd
	.4byte	.LASF127
	.byte	0x63
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9d9
	.uleb128 0x7
	.4byte	.LASF100
	.byte	0x63
	.byte	0x29
	.4byte	0x5cb
	.4byte	.LLST4
	.byte	0
	.uleb128 0x30
	.4byte	.LASF129
	.byte	0x1
	.byte	0x5d
	.byte	0x5
	.4byte	0xba
	.byte	0x1
	.4byte	0x9f7
	.uleb128 0x31
	.4byte	.LASF100
	.byte	0x1
	.byte	0x5d
	.byte	0x28
	.4byte	0x5cb
	.byte	0
	.uleb128 0xd
	.4byte	.LASF130
	.byte	0x54
	.byte	0x5
	.4byte	0xba
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa68
	.uleb128 0x7
	.4byte	.LASF131
	.byte	0x54
	.byte	0x1d
	.4byte	0x9e
	.4byte	.LLST1
	.uleb128 0x7
	.4byte	.LASF132
	.byte	0x54
	.byte	0x30
	.4byte	0x9e
	.4byte	.LLST2
	.uleb128 0x32
	.4byte	.LASF133
	.byte	0x1
	.byte	0x56
	.byte	0xe
	.4byte	0x9e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x11
	.4byte	.LVL3
	.4byte	0x540
	.uleb128 0x4
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
	.uleb128 0x4
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
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF134
	.byte	0x4f
	.byte	0x5
	.4byte	0xba
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa91
	.uleb128 0x7
	.4byte	.LASF100
	.byte	0x4f
	.byte	0x27
	.4byte	0x5cb
	.4byte	.LLST0
	.byte	0
	.uleb128 0x33
	.4byte	0x9d9
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xaae
	.uleb128 0xb
	.4byte	0x9ea
	.4byte	.LLST3
	.byte	0
	.uleb128 0x34
	.4byte	0x5d0
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xb
	.4byte	0x5de
	.4byte	.LLST28
	.uleb128 0xb
	.4byte	0x5e8
	.4byte	.LLST29
	.uleb128 0x35
	.4byte	0x5d0
	.4byte	.LBB17
	.4byte	.LLRL30
	.byte	0x1
	.2byte	0x165
	.byte	0x6
	.uleb128 0xb
	.4byte	0x5e8
	.4byte	.LLST31
	.uleb128 0xb
	.4byte	0x5de
	.4byte	.LLST32
	.uleb128 0x1b
	.4byte	.LVL61
	.4byte	0x6e9
	.uleb128 0x4
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
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
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
	.uleb128 0x7
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
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
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x10
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x11
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
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
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x1a
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 357
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0x21
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x23
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
	.uleb128 0x24
	.uleb128 0x4
	.byte	0x1
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
	.uleb128 0x25
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
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x5
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
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0x2c
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
	.uleb128 0x2d
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
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2f
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
	.uleb128 0x30
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
	.uleb128 0x31
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
	.uleb128 0x32
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
	.uleb128 0x33
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
	.uleb128 0x34
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
	.uleb128 0x35
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
	.uleb128 0x5
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
.LLST33:
	.byte	0x6
	.4byte	.LVL62
	.byte	0x4
	.uleb128 .LVL62-.LVL62
	.uleb128 .LVL63-1-.LVL62
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL63-1-.LVL62
	.uleb128 .LVL63-.LVL62
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
	.uleb128 .LVL63-.LVL62
	.uleb128 .LFE21-.LVL62
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST34:
	.byte	0x6
	.4byte	.LVL62
	.byte	0x4
	.uleb128 .LVL62-.LVL62
	.uleb128 .LVL63-1-.LVL62
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL63-1-.LVL62
	.uleb128 .LVL63-.LVL62
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
	.uleb128 .LVL63-.LVL62
	.uleb128 .LFE21-.LVL62
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST35:
	.byte	0x6
	.4byte	.LVL62
	.byte	0x4
	.uleb128 .LVL62-.LVL62
	.uleb128 .LVL63-1-.LVL62
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL63-1-.LVL62
	.uleb128 .LVL63-.LVL62
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
	.uleb128 .LVL63-.LVL62
	.uleb128 .LFE21-.LVL62
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST26:
	.byte	0x6
	.4byte	.LVL57
	.byte	0x4
	.uleb128 .LVL57-.LVL57
	.uleb128 .LVL58-.LVL57
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL58-.LVL57
	.uleb128 .LFE19-.LVL57
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
.LLST27:
	.byte	0x6
	.4byte	.LVL57
	.byte	0x4
	.uleb128 .LVL57-.LVL57
	.uleb128 .LVL58-.LVL57
	.uleb128 0xa
	.byte	0x7a
	.sleb128 140
	.byte	0x6
	.byte	0x34
	.byte	0x24
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL58-.LVL57
	.uleb128 .LFE19-.LVL57
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST23:
	.byte	0x6
	.4byte	.LVL46
	.byte	0x4
	.uleb128 .LVL46-.LVL46
	.uleb128 .LVL51-.LVL46
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL51-.LVL46
	.uleb128 .LVL55-.LVL46
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL55-.LVL46
	.uleb128 .LVL56-.LVL46
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
	.uleb128 .LVL56-.LVL46
	.uleb128 .LFE18-.LVL46
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST24:
	.byte	0x6
	.4byte	.LVL46
	.byte	0x4
	.uleb128 .LVL46-.LVL46
	.uleb128 .LVL50-.LVL46
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL50-.LVL46
	.uleb128 .LVL56-.LVL46
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
	.uleb128 .LVL56-.LVL46
	.uleb128 .LFE18-.LVL46
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST25:
	.byte	0x6
	.4byte	.LVL47
	.byte	0x4
	.uleb128 .LVL47-.LVL47
	.uleb128 .LVL48-.LVL47
	.uleb128 0x8
	.byte	0x7f
	.sleb128 0
	.byte	0x34
	.byte	0x24
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL48-.LVL47
	.uleb128 .LVL49-.LVL47
	.uleb128 0xa
	.byte	0x7e
	.sleb128 1
	.byte	0x37
	.byte	0x1a
	.byte	0x34
	.byte	0x24
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL49-.LVL47
	.uleb128 .LVL52-.LVL47
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL52-.LVL47
	.uleb128 .LVL53-1-.LVL47
	.uleb128 0xa
	.byte	0x7e
	.sleb128 1
	.byte	0x37
	.byte	0x1a
	.byte	0x34
	.byte	0x24
	.byte	0x78
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0
.LLST21:
	.byte	0x6
	.4byte	.LVL43
	.byte	0x4
	.uleb128 .LVL43-.LVL43
	.uleb128 .LVL45-.LVL43
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL45-.LVL43
	.uleb128 .LFE17-.LVL43
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
	.4byte	.LVL43
	.uleb128 .LVL44-.LVL43
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LFE16-.LVL33
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
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LVL41-.LVL33
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL41-.LVL33
	.uleb128 .LVL42-.LVL33
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
	.uleb128 .LVL42-.LVL33
	.uleb128 .LFE16-.LVL33
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST16:
	.byte	0x6
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LFE16-.LVL33
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
.LLST17:
	.byte	0x6
	.4byte	.LVL34
	.byte	0x4
	.uleb128 .LVL34-.LVL34
	.uleb128 .LVL41-.LVL34
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL41-.LVL34
	.uleb128 .LVL42-.LVL34
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
	.uleb128 .LVL42-.LVL34
	.uleb128 .LFE16-.LVL34
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST20:
	.byte	0x6
	.4byte	.LVL36
	.byte	0x4
	.uleb128 .LVL36-.LVL36
	.uleb128 .LVL37-.LVL36
	.uleb128 0x8
	.byte	0x78
	.sleb128 0
	.byte	0x34
	.byte	0x24
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL37-.LVL36
	.uleb128 .LVL38-.LVL36
	.uleb128 0xa
	.byte	0x7e
	.sleb128 140
	.byte	0x6
	.byte	0x34
	.byte	0x24
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL38-.LVL36
	.uleb128 .LVL40-.LVL36
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL42-.LVL36
	.uleb128 .LFE16-.LVL36
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST18:
	.byte	0x8
	.4byte	.LVL34
	.uleb128 .LVL35-.LVL34
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST8:
	.byte	0x6
	.4byte	.LVL16
	.byte	0x4
	.uleb128 .LVL16-.LVL16
	.uleb128 .LVL18-1-.LVL16
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL18-1-.LVL16
	.uleb128 .LVL28-.LVL16
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL28-.LVL16
	.uleb128 .LVL31-.LVL16
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
	.uleb128 .LVL31-.LVL16
	.uleb128 .LFE15-.LVL16
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL16
	.byte	0x4
	.uleb128 .LVL16-.LVL16
	.uleb128 .LVL18-1-.LVL16
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL18-1-.LVL16
	.uleb128 .LVL29-.LVL16
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL29-.LVL16
	.uleb128 .LVL31-.LVL16
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
	.uleb128 .LVL31-.LVL16
	.uleb128 .LFE15-.LVL16
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL16
	.byte	0x4
	.uleb128 .LVL16-.LVL16
	.uleb128 .LVL18-1-.LVL16
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL18-1-.LVL16
	.uleb128 .LVL30-.LVL16
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL30-.LVL16
	.uleb128 .LVL31-.LVL16
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL31-.LVL16
	.uleb128 .LFE15-.LVL16
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL17
	.byte	0x4
	.uleb128 .LVL17-.LVL17
	.uleb128 .LVL18-1-.LVL17
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL18-1-.LVL17
	.uleb128 .LVL29-.LVL17
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL29-.LVL17
	.uleb128 .LVL31-.LVL17
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
	.uleb128 .LVL31-.LVL17
	.uleb128 .LFE15-.LVL17
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL17
	.byte	0x4
	.uleb128 .LVL17-.LVL17
	.uleb128 .LVL19-.LVL17
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL19-.LVL17
	.uleb128 .LVL20-1-.LVL17
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL31-.LVL17
	.uleb128 .LFE15-.LVL17
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL17
	.byte	0x4
	.uleb128 .LVL17-.LVL17
	.uleb128 .LVL20-.LVL17
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL20-.LVL17
	.uleb128 .LVL21-.LVL17
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL21-.LVL17
	.uleb128 .LVL22-.LVL17
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL23-.LVL17
	.uleb128 .LVL24-.LVL17
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL24-.LVL17
	.uleb128 .LVL25-.LVL17
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL26-.LVL17
	.uleb128 .LVL27-.LVL17
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL31-.LVL17
	.uleb128 .LVL32-.LVL17
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL10
	.byte	0x4
	.uleb128 .LVL10-.LVL10
	.uleb128 .LVL13-.LVL10
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL13-.LVL10
	.uleb128 .LFE12-.LVL10
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
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL12-.LVL11
	.uleb128 0x8
	.byte	0x7f
	.sleb128 0
	.byte	0x34
	.byte	0x24
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL12-.LVL11
	.uleb128 .LVL13-.LVL11
	.uleb128 0xa
	.byte	0x7a
	.sleb128 156
	.byte	0x6
	.byte	0x34
	.byte	0x24
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL13-.LVL11
	.uleb128 .LFE12-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST5:
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
.LLST4:
	.byte	0x6
	.4byte	.LVL6
	.byte	0x4
	.uleb128 .LVL6-.LVL6
	.uleb128 .LVL7-.LVL6
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL7-.LVL6
	.uleb128 .LFE10-.LVL6
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
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL3-1-.LVL2
	.uleb128 .LFE8-.LVL2
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
.LLST2:
	.byte	0x6
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL3-1-.LVL2
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL3-1-.LVL2
	.uleb128 .LFE8-.LVL2
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
	.uleb128 .LFE7-.LVL0
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
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL5-.LVL4
	.uleb128 .LFE9-.LVL4
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
.LLST28:
	.byte	0x6
	.4byte	.LVL59
	.byte	0x4
	.uleb128 .LVL59-.LVL59
	.uleb128 .LVL61-1-.LVL59
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL61-1-.LVL59
	.uleb128 .LVL61-.LVL59
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
	.uleb128 .LVL61-.LVL59
	.uleb128 .LFE20-.LVL59
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST29:
	.byte	0x6
	.4byte	.LVL59
	.byte	0x4
	.uleb128 .LVL59-.LVL59
	.uleb128 .LVL61-1-.LVL59
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL61-1-.LVL59
	.uleb128 .LVL61-.LVL59
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
	.uleb128 .LVL61-.LVL59
	.uleb128 .LFE20-.LVL59
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST31:
	.byte	0x8
	.4byte	.LVL60
	.uleb128 .LVL61-.LVL60
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST32:
	.byte	0x8
	.4byte	.LVL60
	.uleb128 .LVL61-1-.LVL60
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x8c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
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
.LLRL19:
	.byte	0x5
	.4byte	.LBB9
	.byte	0x4
	.uleb128 .LBB9-.LBB9
	.uleb128 .LBE9-.LBB9
	.byte	0x4
	.uleb128 .LBB10-.LBB9
	.uleb128 .LBE10-.LBB9
	.byte	0
.LLRL30:
	.byte	0x5
	.4byte	.LBB17
	.byte	0x4
	.uleb128 .LBB17-.LBB17
	.uleb128 .LBE17-.LBB17
	.byte	0x4
	.uleb128 .LBB20-.LBB17
	.uleb128 .LBE20-.LBB17
	.byte	0
.LLRL36:
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF80:
	.string	"last_pushed_kb_consumer"
.LASF121:
	.string	"default_key_status"
.LASF64:
	.string	"KEY_QUEUE_STATUS"
.LASF28:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF135:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF132:
	.string	"cur_time"
.LASF50:
	.string	"type"
.LASF112:
	.string	"riscv_key_pop_confirm"
.LASF30:
	.string	"LOG_TYPE_HCI_DATA"
.LASF67:
	.string	"KB_CONSUMBER"
.LASF47:
	.string	"tlv_dump_handle"
.LASF124:
	.string	"item2"
.LASF61:
	.string	"STATUS_TIMEOUT"
.LASF22:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF86:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF70:
	.string	"timestamp"
.LASF27:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF136:
	.string	"log_control_block_rv_exp"
.LASF10:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF81:
	.string	"buf_head"
.LASF53:
	.string	"kb_consumer"
.LASF99:
	.string	"KEY_DELIVERY_STATE_ABANDONED"
.LASF72:
	.string	"key_delivery_status"
.LASF116:
	.string	"riscv_key_push"
.LASF106:
	.string	"rv_hid_exp_key_queue_post_process"
.LASF59:
	.string	"STATUS_QUEUE_EMPTY"
.LASF54:
	.string	"T_OUTGOING_VALUES_S"
.LASF44:
	.string	"print_level"
.LASF8:
	.string	"long int"
.LASF38:
	.string	"f_print_t"
.LASF108:
	.string	"riscv_hid_express_key_queue_debug_print"
.LASF29:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF52:
	.string	"kb_std"
.LASF58:
	.string	"STATUS_INSUFFICIENT_MEMORY"
.LASF39:
	.string	"f_dump_buffer_t"
.LASF103:
	.string	"print_module_msgid_log"
.LASF57:
	.string	"STATUS_BUSY"
.LASF94:
	.string	"KEY_DELIVERY_STATE_IDLE"
.LASF33:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF60:
	.string	"STATUS_QUEUE_FULL"
.LASF133:
	.string	"duration"
.LASF2:
	.string	"long long unsigned int"
.LASF87:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF117:
	.string	"combined_value"
.LASF85:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF43:
	.string	"log_switch"
.LASF17:
	.string	"PRINT_LEVEL_DEBUG"
.LASF26:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF62:
	.string	"STATUS_NOTHING_CHANGED"
.LASF32:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF9:
	.string	"long unsigned int"
.LASF83:
	.string	"buf_tail_printed"
.LASF45:
	.string	"print_handle"
.LASF91:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF109:
	.string	"riscv_trigger_time"
.LASF98:
	.string	"KEY_DELIVERY_STATE_ACKED"
.LASF126:
	.string	"is_queue_num_2"
.LASF20:
	.string	"PRINT_LEVEL_ERROR"
.LASF130:
	.string	"is_key_expired"
.LASF31:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF89:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF55:
	.string	"STATUS_SUCCESS"
.LASF19:
	.string	"PRINT_LEVEL_WARNING"
.LASF90:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF37:
	.string	"log_type_t"
.LASF71:
	.string	"nack_cnt"
.LASF77:
	.string	"old_pushed_ms"
.LASF114:
	.string	"outgoing_data"
.LASF88:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF65:
	.string	"MS_KEY_Z"
.LASF119:
	.string	"riscv_key_clear_key_pushed"
.LASF56:
	.string	"STATUS_INVALID_PARAMETER"
.LASF63:
	.string	"STATUS_UNKNOWN"
.LASF76:
	.string	"last_pushed_ms"
.LASF100:
	.string	"kCtrl"
.LASF23:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF51:
	.string	"k_old"
.LASF111:
	.string	"msg_id_string"
.LASF18:
	.string	"PRINT_LEVEL_INFO"
.LASF49:
	.string	"log_control_block_t"
.LASF82:
	.string	"buf_tail"
.LASF92:
	.string	"HAL_GPT_STATUS_OK"
.LASF16:
	.string	"_Bool"
.LASF13:
	.string	"int32_t"
.LASF5:
	.string	"unsigned char"
.LASF21:
	.string	"print_level_t"
.LASF97:
	.string	"KEY_DELIVERY_STATE_SKIP_FIRST_RESULT"
.LASF6:
	.string	"short int"
.LASF113:
	.string	"riscv_key_pop_temperory"
.LASF122:
	.string	"riscv_key_push_key_info"
.LASF42:
	.string	"module_name"
.LASF35:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF95:
	.string	"KEY_DELIVERY_STATE_TRIGGERED"
.LASF36:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF104:
	.string	"rv_hid_exp_key_queue_tx_result_handle"
.LASF15:
	.string	"uint32_t"
.LASF101:
	.string	"tx_result"
.LASF46:
	.string	"dump_handle"
.LASF11:
	.string	"long double"
.LASF12:
	.string	"char"
.LASF102:
	.string	"mode"
.LASF3:
	.string	"unsigned int"
.LASF125:
	.string	"key_info_write"
.LASF127:
	.string	"get_queue_count"
.LASF134:
	.string	"is_queue_full"
.LASF48:
	.string	"msg_id_handle"
.LASF74:
	.string	"buffer"
.LASF78:
	.string	"outgoing_item_idx"
.LASF7:
	.string	"short unsigned int"
.LASF128:
	.string	"hal_gpt_get_duration_count"
.LASF34:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF123:
	.string	"item1"
.LASF79:
	.string	"last_pushed_kb_std"
.LASF131:
	.string	"key_time"
.LASF110:
	.string	"outgoing_key_info"
.LASF41:
	.string	"f_tlv_dump_t"
.LASF118:
	.string	"status"
.LASF75:
	.string	"valid_key_mask"
.LASF105:
	.string	"rv_hid_exp_key_queue_pre_process"
.LASF14:
	.string	"uint8_t"
.LASF96:
	.string	"KEY_DELIVERY_STATE_TRIGGERED_COMPLETED"
.LASF107:
	.string	"report_process_time"
.LASF24:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF40:
	.string	"f_msg_id_t"
.LASF68:
	.string	"ACL_RESPONSE"
.LASF73:
	.string	"T_KEY_INFO_S"
.LASF25:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF129:
	.string	"is_queue_empty"
.LASF84:
	.string	"T_KEY_QUEUE_CTRL_S"
.LASF69:
	.string	"items"
.LASF66:
	.string	"KB_STD"
.LASF115:
	.string	"outgoing"
.LASF93:
	.string	"hal_gpt_status_t"
.LASF120:
	.string	"init_key_ctrl"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_key_queue_mouse.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
