	.file	"hal_hw_keyscan.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_hw_keyscan.c"
	.section	.text.hw_keyscan_dummy_Isr,"ax",@progbits
	.align	1
	.type	hw_keyscan_dummy_Isr, @function
hw_keyscan_dummy_Isr:
.LFB3:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_hw_keyscan.c"
	.loc 1 77 1
	.cfi_startproc
	.loc 1 78 5
	.loc 1 78 37 is_stmt 0
	li	a5,1109262336
	li	a4,1
	sw	a4,260(a5)
	.loc 1 79 5 is_stmt 1
	.loc 1 79 10 is_stmt 0
	li	a5,0
	.loc 1 79 68
	li	a4,1109262336
.L2:
	.loc 1 79 11 is_stmt 1
	.loc 1 79 68 is_stmt 0
	lbu	a2,153(a4)
	.loc 1 79 11
	beq	a2,zero,.L3
	beq	a5,zero,.L4
	sw	a3,key_data,a5
.L4:
	.loc 1 82 5 is_stmt 1
	.loc 1 82 9 is_stmt 0
	lw	a5,key_transaction
	.loc 1 82 8
	beq	a5,zero,.L1
	.loc 1 83 9 is_stmt 1
	lbu	a3,is_ghost
	lbu	a2,total_key_num
	lbu	a1,one_packet_valid_num
	lla	a0,key_data
	jr	a5
.LVL0:
.L3:
	.loc 1 80 9
	.loc 1 80 36 is_stmt 0
	lw	a3,148(a4)
	li	a5,1
	j	.L2
.L1:
	.loc 1 85 1
	ret
	.cfi_endproc
.LFE3:
	.size	hw_keyscan_dummy_Isr, .-hw_keyscan_dummy_Isr
	.globl	__mulsi3
	.section	.text.hal_hw_keyscan_init,"ax",@progbits
	.align	1
	.globl	hal_hw_keyscan_init
	.hidden	hal_hw_keyscan_init
	.type	hal_hw_keyscan_init, @function
hal_hw_keyscan_init:
.LFB10:
	.loc 1 274 1 is_stmt 1
	.cfi_startproc
.LVL1:
	.loc 1 275 5
	.loc 1 275 8 is_stmt 0
	lw	a4,hw_keyscan_status
	bne	a4,zero,.L75
	.loc 1 274 1
	addi	sp,sp,-60
	.cfi_def_cfa_offset 60
	sw	s1,48(sp)
	sw	ra,56(sp)
	sw	s0,52(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 280 13
	lbu	a5,15(a0)
	.loc 1 284 7
	li	a4,3
	mv	s1,a0
	.loc 1 280 5 is_stmt 1
	.loc 1 280 13 is_stmt 0
	sw	a5,4(sp)
.LVL2:
	.loc 1 281 5 is_stmt 1
	.loc 1 281 13 is_stmt 0
	lbu	a5,16(a0)
	sw	a5,8(sp)
.LVL3:
	.loc 1 282 5 is_stmt 1
	.loc 1 282 27 is_stmt 0
	lw	a5,0(a0)
	sw	a5,12(sp)
.LVL4:
	.loc 1 284 5 is_stmt 1
	.loc 1 284 7 is_stmt 0
	bne	a5,a4,.L11
	.loc 1 286 14
	li	a5,1
.LVL5:
	sw	a5,12(sp)
.L11:
.LVL6:
	.loc 1 289 5 is_stmt 1
	.loc 1 291 13 is_stmt 0
	lbu	a5,13(s1)
.LBB14:
.LBB15:
	.loc 1 155 33 discriminator 1
	li	a2,63
.LBE15:
.LBE14:
	.loc 1 289 37
	lw	s0,4(s1)
.LVL7:
	.loc 1 290 5 is_stmt 1
	.loc 1 291 13 is_stmt 0
	sw	a5,20(sp)
	.loc 1 292 13
	lbu	a5,14(s1)
	.loc 1 290 27
	lw	a4,8(s1)
.LVL8:
	.loc 1 291 5 is_stmt 1
	.loc 1 292 5
	.loc 1 299 16 is_stmt 0
	li	a0,-1
.LVL9:
	.loc 1 292 13
	sw	a5,24(sp)
.LVL10:
	.loc 1 293 4 is_stmt 1
	.loc 1 293 9 is_stmt 0
	lbu	a5,12(s1)
.LBB18:
.LBB16:
	.loc 1 155 33 discriminator 1
	lw	a3,24(sp)
.LBE16:
.LBE18:
	.loc 1 293 9
	sw	a5,36(sp)
.LVL11:
	.loc 1 294 5 is_stmt 1
	.loc 1 294 30 is_stmt 0
	lw	a5,44(s1)
	sw	a5,0(sp)
.LVL12:
	.loc 1 295 5 is_stmt 1
	.loc 1 295 33 is_stmt 0
	lbu	a5,48(s1)
.LVL13:
	sw	a5,40(sp)
.LVL14:
	.loc 1 297 5 is_stmt 1
.LBB19:
.LBB17:
	.loc 1 155 5
	.loc 1 155 33 is_stmt 0 discriminator 1
	lw	a5,20(sp)
.LVL15:
	or	a1,a5,a3
	bgtu	a1,a2,.L9
	.loc 1 161 9 is_stmt 1
.LVL16:
.LBE17:
.LBE19:
.LBB20:
.LBB21:
	.loc 1 167 5
	.loc 1 167 8 is_stmt 0
	lw	a5,4(sp)
	addi	a2,a5,-1
	andi	a5,a2,0xff
	sw	a5,28(sp)
	li	a2,7
	bgtu	a5,a2,.L9
	.loc 1 167 23 discriminator 1
	lw	a5,8(sp)
	addi	a1,a5,-1
	andi	a5,a1,0xff
	sw	a5,16(sp)
	li	a1,17
	bgtu	a5,a1,.L9
	.loc 1 173 9 is_stmt 1
.LVL17:
.LBE21:
.LBE20:
.LBB22:
.LBB23:
	.loc 1 179 5
	.loc 1 179 8 is_stmt 0
	lw	a5,0(sp)
	bne	a5,zero,.L13
	.loc 1 179 59 discriminator 1
	li	a2,3
	bleu	a4,a2,.L70
.LVL18:
.L9:
.LBE23:
.LBE22:
	.loc 1 381 1
	lw	ra,56(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,52(sp)
	.cfi_restore 8
	lw	s1,48(sp)
	.cfi_restore 9
	addi	sp,sp,60
	.cfi_def_cfa_offset 0
.LVL19:
	jr	ra
.LVL20:
.L13:
	.cfi_restore_state
.LBB28:
.LBB24:
	.loc 1 179 98 discriminator 3
	lw	a5,0(sp)
.LVL21:
	li	a1,1
	bne	a5,a1,.L15
.LBE24:
.LBE28:
	.loc 1 299 16
	li	a0,-1
.LBB29:
.LBB25:
	.loc 1 179 156 discriminator 4
	beq	a4,zero,.L9
	.loc 1 185 9 is_stmt 1
.LVL22:
.LBE25:
.LBE29:
.LBB30:
.LBB31:
	.loc 1 191 5
	.loc 1 202 10
	.loc 1 204 9
	.loc 1 204 12 is_stmt 0
	li	a2,2
	bne	a4,a2,.L81
.LBE31:
.LBE30:
	.loc 1 299 16
	li	a0,-1
.LBB35:
.LBB32:
	.loc 1 204 50 discriminator 1
	bgtu	s0,a4,.L9
.LVL23:
.L19:
.LBE32:
.LBE35:
.LBB36:
.LBB37:
	.loc 1 238 9
	li	a0,59
	sw	a4,44(sp)
.LVL24:
.LBE37:
.LBE36:
	.loc 1 302 5 is_stmt 1
.LBB40:
.LBB38:
	.loc 1 238 5
	.loc 1 238 9 is_stmt 0
	call	hal_clock_is_enabled
.LVL25:
	.loc 1 238 8 discriminator 1
	lw	a4,44(sp)
	beq	a0,zero,.L25
.LVL26:
.L28:
	.loc 1 244 9
	li	a0,60
	sw	a4,44(sp)
	.loc 1 244 5 is_stmt 1
	.loc 1 244 9 is_stmt 0
	call	hal_clock_is_enabled
.LVL27:
	.loc 1 244 8 discriminator 1
	lw	a4,44(sp)
	bne	a0,zero,.L26
	.loc 1 245 36
	li	a0,60
	sw	a4,44(sp)
	.loc 1 245 9 is_stmt 1
	.loc 1 245 36 is_stmt 0
	call	hal_clock_enable
.LVL28:
	.loc 1 245 12 discriminator 1
	lw	a4,44(sp)
	bne	a0,zero,.L10
.L26:
.LBE38:
.LBE40:
	.loc 1 306 5 is_stmt 1
	.loc 1 306 71 is_stmt 0
	lw	a5,28(sp)
	li	a2,1109262336
	.loc 1 317 7
	lw	a3,0(s1)
	.loc 1 306 71
	sb	a5,0(a2)
	.loc 1 307 5 is_stmt 1
	.loc 1 307 71 is_stmt 0
	lw	a5,16(sp)
	sb	a5,1(a2)
	.loc 1 308 5 is_stmt 1
	.loc 1 308 37 is_stmt 0
	lw	a5,12(sp)
	sw	a5,4(a2)
	.loc 1 309 5 is_stmt 1
	.loc 1 311 40 is_stmt 0
	lw	a5,20(sp)
	.loc 1 309 42
	sw	s0,8(a2)
	.loc 1 310 5 is_stmt 1
	.loc 1 310 48 is_stmt 0
	sw	a4,12(a2)
	.loc 1 311 5 is_stmt 1
	.loc 1 311 40 is_stmt 0
	sw	a5,20(a2)
	.loc 1 312 5 is_stmt 1
	.loc 1 312 40 is_stmt 0
	lw	a5,24(sp)
	.loc 1 314 35
	li	a4,1109262336
	addi	a4,a4,128
	.loc 1 312 40
	sw	a5,24(a2)
	.loc 1 313 5 is_stmt 1
	.loc 1 313 34 is_stmt 0
	lw	a5,36(sp)
	sw	a5,16(a2)
	.loc 1 314 5 is_stmt 1
	.loc 1 314 35 is_stmt 0
	lw	a5,0(sp)
	sw	a5,4(a4)
	.loc 1 315 5 is_stmt 1
	.loc 1 315 42 is_stmt 0
	lw	a5,40(sp)
	sw	a5,8(a4)
	.loc 1 317 5 is_stmt 1
	.loc 1 317 7 is_stmt 0
	li	a4,3
	bne	a3,a4,.L30
	.loc 1 320 9 is_stmt 1
	.loc 1 320 44 is_stmt 0
	li	a4,1107427328
	li	a3,1
	sw	a3,56(a4)
.L30:
	.loc 1 323 5 is_stmt 1
	.loc 1 323 30 is_stmt 0
	lw	a1,8(sp)
	lw	a0,4(sp)
	call	__mulsi3
.LVL29:
	andi	a0,a0,0xff
	.loc 1 323 19
	sb	a0,total_key_num,a4
	.loc 1 324 5 is_stmt 1
	.loc 1 326 30 is_stmt 0
	srli	a4,a0,5
	.loc 1 324 7
	andi	a0,a0,31
	beq	a0,zero,.L32
	.loc 1 329 9 is_stmt 1
	.loc 1 329 53 is_stmt 0
	addi	a4,a4,1
.L32:
	sb	a4,one_packet_valid_num,a3
	.loc 1 332 5 is_stmt 1
	.loc 1 333 5
.LVL30:
	.loc 1 333 12 is_stmt 0
	lw	a3,4(sp)
	.loc 1 333 25 discriminator 1
	li	a2,8
	.loc 1 335 42
	li	a1,1109262336
	li	a0,63
.LVL31:
.L33:
	.loc 1 333 25 is_stmt 1 discriminator 1
	bne	a3,a2,.L34
	.loc 1 338 5
.LVL32:
	.loc 1 338 12 is_stmt 0
	lw	a3,8(sp)
	.loc 1 338 25 discriminator 1
	li	a2,18
	.loc 1 340 42
	li	a1,1109262336
	li	a0,63
.LVL33:
.L35:
	.loc 1 338 25 is_stmt 1 discriminator 1
	bne	a3,a2,.L36
	.loc 1 343 12 is_stmt 0
	li	a4,0
	.loc 1 345 42
	li	a1,1109262336
.LVL34:
.L37:
	.loc 1 345 9 is_stmt 1
	.loc 1 345 63 is_stmt 0
	add	a3,s1,a4
	lbu	a2,17(a3)
	.loc 1 345 42
	addi	a3,a4,24
	slli	a3,a3,2
	.loc 1 343 19 discriminator 1
	lw	a5,4(sp)
	.loc 1 345 42
	add	a3,a1,a3
	sw	a2,4(a3)
	.loc 1 343 31 is_stmt 1 discriminator 3
	addi	a4,a4,1
.LVL35:
	.loc 1 343 19 discriminator 1
	bgt	a5,a4,.L37
	.loc 1 348 12 is_stmt 0
	li	a4,0
.LVL36:
	.loc 1 350 42
	li	s0,1109262336
.LVL37:
.L38:
	.loc 1 350 9 is_stmt 1
	.loc 1 350 63 is_stmt 0
	add	a3,s1,a4
	lbu	a2,25(a3)
	.loc 1 350 42
	addi	a3,a4,4
	slli	a3,a3,2
	.loc 1 348 19 discriminator 1
	lw	a5,8(sp)
	.loc 1 350 42
	add	a3,s0,a3
	sw	a2,12(a3)
	.loc 1 348 31 is_stmt 1 discriminator 3
	addi	a4,a4,1
.LVL38:
	.loc 1 348 19 discriminator 1
	bgt	a5,a4,.L38
	.loc 1 357 5
	lla	a1,hw_keyscan_dummy_Isr
	li	a0,16
	call	hal_nvic_register_isr_handler
.LVL39:
	.loc 1 369 5
	.loc 1 369 37 is_stmt 0
	li	a5,1
	sw	a5,260(s0)
	.loc 1 370 5 is_stmt 1
	.loc 1 370 68 is_stmt 0
	li	a4,1109262336
	.loc 1 370 10
	li	a5,0
.L39:
	.loc 1 370 11 is_stmt 1
	.loc 1 370 68 is_stmt 0
	lbu	a3,153(a4)
	.loc 1 370 11
	beq	a3,zero,.L40
	beq	a5,zero,.L41
	lw	a4,32(sp)
	sw	a4,key_data,a5
.L41:
	.loc 1 373 5 is_stmt 1
	.loc 1 373 37 is_stmt 0
	li	s0,1
	li	s1,1109262336
.LVL40:
	.loc 1 374 5
	li	a0,16
	.loc 1 373 37
	sw	s0,260(s1)
	.loc 1 374 5 is_stmt 1
	call	hal_nvic_enable_irq
.LVL41:
	.loc 1 375 5
	.loc 1 375 41 is_stmt 0
	sw	s0,140(s1)
	.loc 1 376 5 is_stmt 1
	.loc 1 376 23 is_stmt 0
	sw	s0,hw_keyscan_status,a5
	.loc 1 380 5 is_stmt 1
	.loc 1 380 12 is_stmt 0
	li	a0,0
	j	.L9
.LVL42:
.L15:
.LBB41:
.LBB26:
	.loc 1 179 196 discriminator 6
	lw	a5,0(sp)
	li	a1,2
.LBE26:
.LBE41:
	.loc 1 299 16
	li	a0,-1
.LBB42:
.LBB27:
	.loc 1 179 196 discriminator 6
	bne	a5,a1,.L9
	.loc 1 179 253 discriminator 7
	beq	a4,zero,.L9
	.loc 1 185 9 is_stmt 1
.LVL43:
.LBE27:
.LBE42:
.LBB43:
.LBB33:
	.loc 1 191 5
	.loc 1 215 9
	.loc 1 215 12 is_stmt 0
	lw	a5,0(sp)
	.loc 1 218 18
	li	a1,8
	.loc 1 215 12
	bne	a4,a5,.L80
.LVL44:
.L81:
	.loc 1 215 49 discriminator 1
	li	a2,3
	j	.L78
.LVL45:
.L70:
	.loc 1 193 9 is_stmt 1
	.loc 1 193 12 is_stmt 0
	bne	a4,zero,.L18
	.loc 1 193 50 discriminator 1
	li	a2,1
.LVL46:
.L78:
.LBE33:
.LBE43:
	.loc 1 299 16
	li	a0,-1
.LBB44:
.LBB34:
	.loc 1 221 92 discriminator 2
	bleu	s0,a2,.L19
	j	.L9
.LVL47:
.L18:
	.loc 1 193 112 discriminator 3
	li	a1,1
	bne	a4,a1,.L20
.LVL48:
.L24:
	.loc 1 221 15 is_stmt 1
	.loc 1 221 92 is_stmt 0 discriminator 2
	li	a2,4
	j	.L78
.LVL49:
.L20:
	.loc 1 193 214 discriminator 6
	li	a1,2
.LVL50:
.L80:
	.loc 1 218 18
	beq	a4,a1,.L78
	j	.L24
.LVL51:
.L25:
.LBE34:
.LBE44:
.LBB45:
.LBB39:
	.loc 1 239 36
	li	a0,59
	sw	a4,44(sp)
.LVL52:
	.loc 1 239 9 is_stmt 1
	.loc 1 239 36 is_stmt 0
	call	hal_clock_enable
.LVL53:
	.loc 1 239 12 discriminator 1
	lw	a4,44(sp)
	beq	a0,zero,.L28
.L10:
.LBE39:
.LBE45:
	.loc 1 277 16
	li	a0,-2
	j	.L9
.LVL54:
.L34:
	.loc 1 335 9 is_stmt 1
	.loc 1 335 42 is_stmt 0
	addi	a4,a3,24
	slli	a4,a4,2
	add	a4,a1,a4
	sw	a0,4(a4)
	.loc 1 333 31 is_stmt 1 discriminator 3
	addi	a3,a3,1
.LVL55:
	j	.L33
.L36:
	.loc 1 340 9
	.loc 1 340 42 is_stmt 0
	addi	a4,a3,4
	slli	a4,a4,2
	add	a4,a1,a4
	sw	a0,12(a4)
	.loc 1 338 32 is_stmt 1 discriminator 3
	addi	a3,a3,1
.LVL56:
	j	.L35
.LVL57:
.L40:
	.loc 1 371 9
	.loc 1 371 36 is_stmt 0
	lw	a5,148(a4)
	sw	a5,32(sp)
	li	a5,1
	j	.L39
.LVL58:
.L75:
	.cfi_def_cfa_offset 0
	.cfi_restore 1
	.cfi_restore 8
	.cfi_restore 9
	.loc 1 277 16
	li	a0,-2
.LVL59:
	.loc 1 381 1
	ret
	.cfi_endproc
.LFE10:
	.size	hal_hw_keyscan_init, .-hal_hw_keyscan_init
	.section	.text.hal_hw_keyscan_deinit,"ax",@progbits
	.align	1
	.globl	hal_hw_keyscan_deinit
	.hidden	hal_hw_keyscan_deinit
	.type	hal_hw_keyscan_deinit, @function
hal_hw_keyscan_deinit:
.LFB11:
	.loc 1 384 1 is_stmt 1
	.cfi_startproc
	.loc 1 385 5
	.loc 1 385 8 is_stmt 0
	lw	a4,hw_keyscan_status
	li	a5,1
	beq	a4,a5,.L83
	.loc 1 387 16
	li	a0,-2
	.loc 1 413 1
	ret
.L83:
	.loc 1 391 5 is_stmt 1
.LBB48:
.LBB49:
	.loc 1 256 5
.LBE49:
.LBE48:
	.loc 1 384 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
.LBB53:
.LBB50:
	.loc 1 256 9
	li	a0,59
.LBE50:
.LBE53:
	.loc 1 384 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
.LBB54:
.LBB51:
	.loc 1 256 9
	call	hal_clock_is_enabled
.LVL60:
	.loc 1 256 8 discriminator 1
	bne	a0,zero,.L85
.L89:
	.loc 1 262 5 is_stmt 1
	.loc 1 262 9 is_stmt 0
	li	a0,60
	call	hal_clock_is_enabled
.LVL61:
	.loc 1 262 8 discriminator 1
	beq	a0,zero,.L87
	.loc 1 263 9 is_stmt 1
	.loc 1 263 36 is_stmt 0
	li	a0,60
	call	hal_clock_enable
.LVL62:
	.loc 1 263 12 discriminator 1
	bne	a0,zero,.L88
.L87:
.LBE51:
.LBE54:
	.loc 1 395 5 is_stmt 1
	.loc 1 396 5
	.loc 1 396 38 is_stmt 0
	li	a5,1109262336
	sw	zero,144(a5)
	.loc 1 397 5 is_stmt 1
	.loc 1 397 41 is_stmt 0
	sw	zero,140(a5)
	.loc 1 398 5 is_stmt 1
.LVL63:
	.loc 1 398 19 discriminator 1
	.loc 1 400 9
	.loc 1 400 42 is_stmt 0
	li	a4,63
	sw	a4,100(a5)
	.loc 1 398 25 is_stmt 1 discriminator 3
.LVL64:
	.loc 1 398 19 discriminator 1
	.loc 1 400 9
	.loc 1 400 42 is_stmt 0
	sw	a4,104(a5)
	.loc 1 398 25 is_stmt 1 discriminator 3
.LVL65:
	.loc 1 398 19 discriminator 1
	.loc 1 400 9
	.loc 1 400 42 is_stmt 0
	sw	a4,108(a5)
	.loc 1 398 25 is_stmt 1 discriminator 3
.LVL66:
	.loc 1 398 19 discriminator 1
	.loc 1 400 9
	.loc 1 400 42 is_stmt 0
	sw	a4,112(a5)
	.loc 1 398 25 is_stmt 1 discriminator 3
.LVL67:
	.loc 1 398 19 discriminator 1
	.loc 1 400 9
	.loc 1 400 42 is_stmt 0
	sw	a4,116(a5)
	.loc 1 398 25 is_stmt 1 discriminator 3
.LVL68:
	.loc 1 398 19 discriminator 1
	.loc 1 400 9
	.loc 1 400 42 is_stmt 0
	sw	a4,120(a5)
	.loc 1 398 25 is_stmt 1 discriminator 3
.LVL69:
	.loc 1 398 19 discriminator 1
	.loc 1 400 9
	.loc 1 400 42 is_stmt 0
	sw	a4,124(a5)
	addi	a5,a5,4
	.loc 1 398 25 is_stmt 1 discriminator 3
.LVL70:
	.loc 1 398 19 discriminator 1
	.loc 1 400 9
	.loc 1 400 42 is_stmt 0
	sw	a4,124(a5)
	.loc 1 398 25 is_stmt 1 discriminator 3
.LVL71:
	.loc 1 398 19 discriminator 1
	.loc 1 405 42 is_stmt 0
	li	a3,1109262336
	.loc 1 403 12
	li	a4,0
	.loc 1 405 42
	li	a1,63
	.loc 1 403 19 discriminator 1
	li	a2,18
.LVL72:
.L90:
	.loc 1 405 9 is_stmt 1
	.loc 1 405 42 is_stmt 0
	addi	a5,a4,4
	slli	a5,a5,2
	add	a5,a3,a5
	sw	a1,12(a5)
	.loc 1 403 26 is_stmt 1 discriminator 3
	addi	a4,a4,1
.LVL73:
	.loc 1 403 19 discriminator 1
	bne	a4,a2,.L90
	.loc 1 407 5
	.loc 1 407 40 is_stmt 0
	li	a5,3
	sw	a5,20(a3)
	.loc 1 408 5 is_stmt 1
	.loc 1 408 40 is_stmt 0
	li	a5,1
	sw	a5,24(a3)
	.loc 1 409 5 is_stmt 1
	.loc 1 409 19 is_stmt 0
	sb	zero,total_key_num,a5
	.loc 1 410 5 is_stmt 1
	.loc 1 410 26 is_stmt 0
	sb	zero,one_packet_valid_num,a5
	.loc 1 411 5 is_stmt 1
	.loc 1 411 23 is_stmt 0
	sw	zero,hw_keyscan_status,a5
	.loc 1 412 5 is_stmt 1
	.loc 1 412 12 is_stmt 0
	li	a0,0
	j	.L82
.LVL74:
.L85:
.LBB55:
.LBB52:
	.loc 1 257 9 is_stmt 1
	.loc 1 257 36 is_stmt 0
	li	a0,59
	call	hal_clock_disable
.LVL75:
	.loc 1 257 12 discriminator 1
	beq	a0,zero,.L89
.L88:
.LBE52:
.LBE55:
	.loc 1 387 16
	li	a0,-2
.L82:
	.loc 1 413 1
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	hal_hw_keyscan_deinit, .-hal_hw_keyscan_deinit
	.section	.text.hal_hw_keyscan_enable,"ax",@progbits
	.align	1
	.globl	hal_hw_keyscan_enable
	.hidden	hal_hw_keyscan_enable
	.type	hal_hw_keyscan_enable, @function
hal_hw_keyscan_enable:
.LFB12:
	.loc 1 416 1 is_stmt 1
	.cfi_startproc
	.loc 1 417 5
	.loc 1 417 27 is_stmt 0
	lla	a5,hw_keyscan_status
	.loc 1 417 8
	lw	a4,0(a5)
	li	a3,1
	bne	a4,a3,.L98
	.loc 1 421 5 is_stmt 1
	.loc 1 416 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 421 38
	li	a3,1109262336
	sw	a4,144(a3)
	.loc 1 422 5 is_stmt 1
	.loc 1 426 5 is_stmt 0
	li	a0,5
	.loc 1 422 23
	li	a4,2
	sw	a4,0(a5)
	.loc 1 426 5 is_stmt 1
	call	hal_gpt_delay_us
.LVL76:
	.loc 1 427 5
	.loc 1 428 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 427 12
	li	a0,0
	.loc 1 428 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.L98:
	li	a0,-2
	ret
	.cfi_endproc
.LFE12:
	.size	hal_hw_keyscan_enable, .-hal_hw_keyscan_enable
	.section	.text.hal_hw_keyscan_disable,"ax",@progbits
	.align	1
	.globl	hal_hw_keyscan_disable
	.hidden	hal_hw_keyscan_disable
	.type	hal_hw_keyscan_disable, @function
hal_hw_keyscan_disable:
.LFB13:
	.loc 1 431 1 is_stmt 1
	.cfi_startproc
	.loc 1 432 5
	.loc 1 432 27 is_stmt 0
	lla	a5,hw_keyscan_status
	.loc 1 432 8
	lw	a3,0(a5)
	li	a4,2
	.loc 1 434 16
	li	a0,-2
	.loc 1 432 8
	bne	a3,a4,.L103
	.loc 1 436 5 is_stmt 1
	.loc 1 436 38 is_stmt 0
	li	a4,1109262336
	sw	zero,144(a4)
	.loc 1 437 5 is_stmt 1
	.loc 1 437 23 is_stmt 0
	li	a4,1
	sw	a4,0(a5)
	.loc 1 441 5 is_stmt 1
	.loc 1 441 12 is_stmt 0
	li	a0,0
.L103:
	.loc 1 442 1
	ret
	.cfi_endproc
.LFE13:
	.size	hal_hw_keyscan_disable, .-hal_hw_keyscan_disable
	.section	.text.hal_hw_keyscan_register_callback,"ax",@progbits
	.align	1
	.globl	hal_hw_keyscan_register_callback
	.hidden	hal_hw_keyscan_register_callback
	.type	hal_hw_keyscan_register_callback, @function
hal_hw_keyscan_register_callback:
.LFB14:
	.loc 1 445 1 is_stmt 1
	.cfi_startproc
.LVL77:
	.loc 1 446 5
	.loc 1 446 8 is_stmt 0
	beq	a0,zero,.L108
	.loc 1 451 5 is_stmt 1
	.loc 1 451 21 is_stmt 0
	sw	a0,key_transaction,a5
	.loc 1 455 5 is_stmt 1
	.loc 1 455 12 is_stmt 0
	li	a0,0
.LVL78:
	ret
.LVL79:
.L108:
	.loc 1 448 16
	li	a0,-1
.LVL80:
	.loc 1 456 1
	ret
	.cfi_endproc
.LFE14:
	.size	hal_hw_keyscan_register_callback, .-hal_hw_keyscan_register_callback
	.section	.text.hal_hw_keyscan_sw_trigger,"ax",@progbits
	.align	1
	.globl	hal_hw_keyscan_sw_trigger
	.hidden	hal_hw_keyscan_sw_trigger
	.type	hal_hw_keyscan_sw_trigger, @function
hal_hw_keyscan_sw_trigger:
.LFB15:
	.loc 1 459 1 is_stmt 1
	.cfi_startproc
	.loc 1 460 5
	.loc 1 460 40 is_stmt 0
	li	a5,1107427328
	li	a4,1
	sw	a4,60(a5)
	.loc 1 461 1
	ret
	.cfi_endproc
.LFE15:
	.size	hal_hw_keyscan_sw_trigger, .-hal_hw_keyscan_sw_trigger
	.section	.text.hal_hw_keyscan_align_bt_trigger_set_enable,"ax",@progbits
	.align	1
	.globl	hal_hw_keyscan_align_bt_trigger_set_enable
	.hidden	hal_hw_keyscan_align_bt_trigger_set_enable
	.type	hal_hw_keyscan_align_bt_trigger_set_enable, @function
hal_hw_keyscan_align_bt_trigger_set_enable:
.LFB16:
	.loc 1 464 1 is_stmt 1
	.cfi_startproc
.LVL81:
	.loc 1 465 5
	li	a5,1107427328
	addi	a5,a5,56
	.loc 1 465 7 is_stmt 0
	beq	a0,zero,.L111
	.loc 1 468 9 is_stmt 1
	.loc 1 468 44 is_stmt 0
	sw	zero,0(a5)
	ret
.L111:
	.loc 1 472 9 is_stmt 1
	.loc 1 472 44 is_stmt 0
	li	a4,1
	sw	a4,0(a5)
	.loc 1 474 1
	ret
	.cfi_endproc
.LFE16:
	.size	hal_hw_keyscan_align_bt_trigger_set_enable, .-hal_hw_keyscan_align_bt_trigger_set_enable
	.hidden	key_data
	.globl	key_data
	.section	.sbss.key_data,"aw",@nobits
	.align	2
	.type	key_data, @object
	.size	key_data, 4
key_data:
	.zero	4
	.hidden	key_transaction
	.globl	key_transaction
	.section	.sbss.key_transaction,"aw",@nobits
	.align	2
	.type	key_transaction, @object
	.size	key_transaction, 4
key_transaction:
	.zero	4
	.hidden	is_ghost
	.globl	is_ghost
	.section	.sbss.is_ghost,"aw",@nobits
	.type	is_ghost, @object
	.size	is_ghost, 1
is_ghost:
	.zero	1
	.section	.sbss.hw_keyscan_status,"aw",@nobits
	.align	2
	.type	hw_keyscan_status, @object
	.size	hw_keyscan_status, 4
hw_keyscan_status:
	.zero	4
	.section	.sbss.one_packet_valid_num,"aw",@nobits
	.type	one_packet_valid_num, @object
	.size	one_packet_valid_num, 1
one_packet_valid_num:
	.zero	1
	.section	.sbss.total_key_num,"aw",@nobits
	.type	total_key_num, @object
	.size	total_key_num, 1
total_key_num:
	.zero	1
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_hw_keyscan.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_hw_keyscan.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 7 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 8 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 9 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_clock.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xe3d
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x26
	.4byte	.LASF255
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL28
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x5
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x5
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x5
	.byte	0x2
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x5
	.byte	0x8
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x66
	.uleb128 0xb
	.4byte	0x50
	.uleb128 0x12
	.4byte	0x5c
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF8
	.uleb128 0x5
	.byte	0x2
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x3
	.4byte	.LASF11
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x85
	.uleb128 0xb
	.4byte	0x74
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF12
	.uleb128 0x27
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x28
	.4byte	.LASF256
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x3
	.2byte	0x128
	.byte	0x11
	.4byte	0x119
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x1f
	.byte	0
	.uleb128 0x13
	.4byte	.LASF32
	.byte	0x3
	.2byte	0x13c
	.byte	0x7
	.4byte	0x93
	.uleb128 0x13
	.4byte	.LASF33
	.byte	0x3
	.2byte	0x13e
	.byte	0x17
	.4byte	0x119
	.uleb128 0xd
	.4byte	0x61
	.4byte	0x143
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.4byte	0x133
	.uleb128 0xb
	.4byte	0x143
	.uleb128 0xd
	.4byte	0x80
	.4byte	0x15d
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0xb
	.4byte	0x14d
	.uleb128 0x14
	.byte	0x4
	.byte	0x4
	.byte	0x28
	.byte	0x5
	.4byte	0x193
	.uleb128 0x2
	.4byte	.LASF34
	.byte	0x4
	.byte	0x2a
	.byte	0x18
	.4byte	0x5c
	.byte	0
	.uleb128 0x2
	.4byte	.LASF35
	.byte	0x4
	.byte	0x2b
	.byte	0x18
	.4byte	0x5c
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0x4
	.byte	0x2c
	.byte	0x1e
	.4byte	0x148
	.byte	0x2
	.byte	0
	.uleb128 0x19
	.byte	0x26
	.4byte	0x1b0
	.uleb128 0x10
	.4byte	.LASF37
	.byte	0x2d
	.byte	0x7
	.4byte	0x162
	.uleb128 0x10
	.4byte	.LASF38
	.byte	0x2e
	.byte	0x17
	.4byte	0x80
	.byte	0
	.uleb128 0x14
	.byte	0x4
	.byte	0x4
	.byte	0x43
	.byte	0x5
	.4byte	0x1ee
	.uleb128 0x2
	.4byte	.LASF39
	.byte	0x4
	.byte	0x45
	.byte	0x18
	.4byte	0x5c
	.byte	0
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x4
	.byte	0x46
	.byte	0x18
	.4byte	0x5c
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF41
	.byte	0x4
	.byte	0x47
	.byte	0x18
	.4byte	0x5c
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF42
	.byte	0x4
	.byte	0x48
	.byte	0x18
	.4byte	0x5c
	.byte	0x3
	.byte	0
	.uleb128 0x19
	.byte	0x41
	.4byte	0x20b
	.uleb128 0x10
	.4byte	.LASF43
	.byte	0x49
	.byte	0x7
	.4byte	0x1b0
	.uleb128 0x10
	.4byte	.LASF44
	.byte	0x4a
	.byte	0x17
	.4byte	0x80
	.byte	0
	.uleb128 0x14
	.byte	0x4
	.byte	0x4
	.byte	0x54
	.byte	0x5
	.4byte	0x23c
	.uleb128 0x2
	.4byte	.LASF45
	.byte	0x4
	.byte	0x56
	.byte	0x18
	.4byte	0x5c
	.byte	0
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x4
	.byte	0x57
	.byte	0x18
	.4byte	0x5c
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0x4
	.byte	0x58
	.byte	0x18
	.4byte	0x24c
	.byte	0x2
	.byte	0
	.uleb128 0xd
	.4byte	0x5c
	.4byte	0x24c
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xb
	.4byte	0x23c
	.uleb128 0x19
	.byte	0x52
	.4byte	0x26e
	.uleb128 0x10
	.4byte	.LASF47
	.byte	0x59
	.byte	0x7
	.4byte	0x20b
	.uleb128 0x10
	.4byte	.LASF48
	.byte	0x5a
	.byte	0x17
	.4byte	0x80
	.byte	0
	.uleb128 0x29
	.2byte	0x110
	.byte	0x4
	.byte	0x24
	.byte	0x9
	.4byte	0x37d
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x4
	.byte	0x2f
	.byte	0x5
	.4byte	0x193
	.byte	0
	.uleb128 0x2
	.4byte	.LASF50
	.byte	0x4
	.byte	0x31
	.byte	0x15
	.4byte	0x80
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF51
	.byte	0x4
	.byte	0x32
	.byte	0x15
	.4byte	0x80
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF52
	.byte	0x4
	.byte	0x33
	.byte	0x15
	.4byte	0x80
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF53
	.byte	0x4
	.byte	0x34
	.byte	0x15
	.4byte	0x80
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF54
	.byte	0x4
	.byte	0x35
	.byte	0x15
	.4byte	0x80
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF55
	.byte	0x4
	.byte	0x36
	.byte	0x15
	.4byte	0x80
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF56
	.byte	0x4
	.byte	0x38
	.byte	0x15
	.4byte	0x38d
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF57
	.byte	0x4
	.byte	0x39
	.byte	0x15
	.4byte	0x15d
	.byte	0x64
	.uleb128 0x2
	.4byte	.LASF58
	.byte	0x4
	.byte	0x3b
	.byte	0x15
	.4byte	0x80
	.byte	0x84
	.uleb128 0x2
	.4byte	.LASF59
	.byte	0x4
	.byte	0x3c
	.byte	0x15
	.4byte	0x80
	.byte	0x88
	.uleb128 0x2
	.4byte	.LASF60
	.byte	0x4
	.byte	0x3d
	.byte	0x15
	.4byte	0x80
	.byte	0x8c
	.uleb128 0x2
	.4byte	.LASF61
	.byte	0x4
	.byte	0x3e
	.byte	0x15
	.4byte	0x80
	.byte	0x90
	.uleb128 0x2
	.4byte	.LASF62
	.byte	0x4
	.byte	0x3f
	.byte	0x15
	.4byte	0x80
	.byte	0x94
	.uleb128 0x2
	.4byte	.LASF63
	.byte	0x4
	.byte	0x4b
	.byte	0x5
	.4byte	0x1ee
	.byte	0x98
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0x4
	.byte	0x4d
	.byte	0x15
	.4byte	0x3a2
	.byte	0x9c
	.uleb128 0x15
	.4byte	.LASF64
	.byte	0x4e
	.byte	0x15
	.4byte	0x80
	.2byte	0x100
	.uleb128 0x15
	.4byte	.LASF65
	.byte	0x4f
	.byte	0x15
	.4byte	0x80
	.2byte	0x104
	.uleb128 0x15
	.4byte	.LASF66
	.byte	0x50
	.byte	0x15
	.4byte	0x80
	.2byte	0x108
	.uleb128 0x15
	.4byte	.LASF67
	.byte	0x5b
	.byte	0x5
	.4byte	0x251
	.2byte	0x10c
	.byte	0
	.uleb128 0xd
	.4byte	0x80
	.4byte	0x38d
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x11
	.byte	0
	.uleb128 0xb
	.4byte	0x37d
	.uleb128 0xd
	.4byte	0x80
	.4byte	0x3a2
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x18
	.byte	0
	.uleb128 0xb
	.4byte	0x392
	.uleb128 0x3
	.4byte	.LASF68
	.byte	0x4
	.byte	0x5c
	.byte	0x3
	.4byte	0x26e
	.uleb128 0xb
	.4byte	0x3a7
	.uleb128 0x5
	.byte	0x10
	.byte	0x4
	.4byte	.LASF69
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF70
	.uleb128 0x11
	.4byte	0x74
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x2b
	.byte	0x1
	.4byte	0x3f1
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF75
	.byte	0x5
	.byte	0x30
	.byte	0x3
	.4byte	0x3cb
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x34
	.byte	0x1
	.4byte	0x43b
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.4byte	.LASF84
	.byte	0x5
	.byte	0x3d
	.byte	0x3
	.4byte	0x3fd
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x41
	.byte	0x1
	.4byte	0x497
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x10
	.byte	0
	.uleb128 0x3
	.4byte	.LASF96
	.byte	0x5
	.byte	0x4d
	.byte	0x3
	.4byte	0x447
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x51
	.byte	0x1
	.4byte	0x4c3
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF100
	.byte	0x5
	.byte	0x55
	.byte	0x3
	.4byte	0x4a3
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x59
	.byte	0x1
	.4byte	0x4ef
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF104
	.byte	0x5
	.byte	0x5d
	.byte	0x3
	.4byte	0x4cf
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x61
	.byte	0x1
	.4byte	0x515
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF107
	.byte	0x5
	.byte	0x64
	.byte	0x3
	.4byte	0x4fb
	.uleb128 0x14
	.byte	0x34
	.byte	0x5
	.byte	0x67
	.byte	0x9
	.4byte	0x5c3
	.uleb128 0x2
	.4byte	.LASF108
	.byte	0x5
	.byte	0x69
	.byte	0x19
	.4byte	0x3f1
	.byte	0
	.uleb128 0x2
	.4byte	.LASF109
	.byte	0x5
	.byte	0x6a
	.byte	0x23
	.4byte	0x43b
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF110
	.byte	0x5
	.byte	0x6b
	.byte	0x19
	.4byte	0x497
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF111
	.byte	0x5
	.byte	0x6c
	.byte	0x7
	.4byte	0x5c3
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF112
	.byte	0x5
	.byte	0x6d
	.byte	0xb
	.4byte	0x50
	.byte	0xd
	.uleb128 0x2
	.4byte	.LASF113
	.byte	0x5
	.byte	0x6e
	.byte	0xb
	.4byte	0x50
	.byte	0xe
	.uleb128 0x2
	.4byte	.LASF114
	.byte	0x5
	.byte	0x6f
	.byte	0xb
	.4byte	0x50
	.byte	0xf
	.uleb128 0x2
	.4byte	.LASF115
	.byte	0x5
	.byte	0x70
	.byte	0xb
	.4byte	0x50
	.byte	0x10
	.uleb128 0x1e
	.string	"row"
	.byte	0x71
	.4byte	0x5ca
	.byte	0x11
	.uleb128 0x1e
	.string	"col"
	.byte	0x72
	.4byte	0x5da
	.byte	0x19
	.uleb128 0x2
	.4byte	.LASF116
	.byte	0x5
	.byte	0x73
	.byte	0x1c
	.4byte	0x4ef
	.byte	0x2c
	.uleb128 0x2
	.4byte	.LASF117
	.byte	0x5
	.byte	0x74
	.byte	0xb
	.4byte	0x50
	.byte	0x30
	.byte	0
	.uleb128 0x5
	.byte	0x1
	.byte	0x2
	.4byte	.LASF118
	.uleb128 0xd
	.4byte	0x50
	.4byte	0x5da
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0xd
	.4byte	0x50
	.4byte	0x5ea
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x11
	.byte	0
	.uleb128 0x3
	.4byte	.LASF119
	.byte	0x5
	.byte	0x75
	.byte	0x3
	.4byte	0x521
	.uleb128 0xc
	.byte	0x5
	.4byte	0x8c
	.byte	0x5
	.byte	0x79
	.byte	0x1
	.4byte	0x616
	.uleb128 0x6
	.4byte	.LASF120
	.sleb128 -2
	.uleb128 0x6
	.4byte	.LASF121
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF123
	.byte	0x5
	.byte	0x7d
	.byte	0x3
	.4byte	0x5f6
	.uleb128 0x3
	.4byte	.LASF124
	.byte	0x5
	.byte	0x7f
	.byte	0x10
	.4byte	0x62e
	.uleb128 0x11
	.4byte	0x633
	.uleb128 0x1f
	.4byte	0x64d
	.uleb128 0x7
	.4byte	0x3c6
	.uleb128 0x7
	.4byte	0x50
	.uleb128 0x7
	.4byte	0x50
	.uleb128 0x7
	.4byte	0x5c3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF125
	.byte	0x6
	.byte	0x2e
	.byte	0x10
	.4byte	0x659
	.uleb128 0x11
	.4byte	0x65e
	.uleb128 0x1f
	.4byte	0x669
	.uleb128 0x7
	.4byte	0x126
	.byte	0
	.uleb128 0x20
	.byte	0x7
	.4byte	0x2d
	.byte	0x7
	.2byte	0x74b
	.4byte	0x87c
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x38
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x39
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x3a
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x3b
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x3c
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x3d
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0x3e
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x41
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0x42
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0x4e
	.uleb128 0x1
	.4byte	.LASF157
	.byte	0x4f
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0x60
	.uleb128 0x1
	.4byte	.LASF159
	.byte	0x61
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0x62
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x64
	.uleb128 0x1
	.4byte	.LASF162
	.byte	0x65
	.uleb128 0x1
	.4byte	.LASF163
	.byte	0x66
	.uleb128 0x1
	.4byte	.LASF164
	.byte	0x6a
	.uleb128 0x1
	.4byte	.LASF165
	.byte	0x6c
	.uleb128 0x1
	.4byte	.LASF166
	.byte	0x6d
	.uleb128 0x1
	.4byte	.LASF167
	.byte	0x6e
	.uleb128 0x1
	.4byte	.LASF168
	.byte	0x6f
	.uleb128 0x1
	.4byte	.LASF169
	.byte	0x71
	.uleb128 0x1
	.4byte	.LASF170
	.byte	0x72
	.uleb128 0x1
	.4byte	.LASF171
	.byte	0x73
	.uleb128 0x1
	.4byte	.LASF172
	.byte	0x74
	.uleb128 0x1
	.4byte	.LASF173
	.byte	0x75
	.uleb128 0x1
	.4byte	.LASF174
	.byte	0x76
	.uleb128 0x1
	.4byte	.LASF175
	.byte	0x77
	.uleb128 0x1
	.4byte	.LASF176
	.byte	0x79
	.uleb128 0x1
	.4byte	.LASF177
	.byte	0x7a
	.uleb128 0x1
	.4byte	.LASF178
	.byte	0x90
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0x91
	.uleb128 0x1
	.4byte	.LASF180
	.byte	0x92
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0x98
	.uleb128 0x1
	.4byte	.LASF182
	.byte	0x9d
	.uleb128 0x1
	.4byte	.LASF183
	.byte	0x9e
	.uleb128 0x1
	.4byte	.LASF184
	.byte	0x9f
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0xa0
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0xa1
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0xa4
	.uleb128 0x1
	.4byte	.LASF188
	.byte	0xa5
	.uleb128 0x1
	.4byte	.LASF189
	.byte	0xa6
	.uleb128 0x1
	.4byte	.LASF190
	.byte	0xa9
	.uleb128 0x1
	.4byte	.LASF191
	.byte	0xaa
	.uleb128 0x1
	.4byte	.LASF192
	.byte	0xab
	.uleb128 0x1
	.4byte	.LASF193
	.byte	0xac
	.uleb128 0x1
	.4byte	.LASF194
	.byte	0xad
	.uleb128 0x1
	.4byte	.LASF195
	.byte	0xae
	.uleb128 0x1
	.4byte	.LASF196
	.byte	0xaf
	.uleb128 0x1
	.4byte	.LASF197
	.byte	0xb2
	.uleb128 0x1
	.4byte	.LASF198
	.byte	0xb3
	.uleb128 0x1
	.4byte	.LASF199
	.byte	0xb4
	.uleb128 0x1
	.4byte	.LASF200
	.byte	0xb7
	.uleb128 0x1
	.4byte	.LASF201
	.byte	0xb8
	.uleb128 0x1
	.4byte	.LASF202
	.byte	0xd0
	.uleb128 0x1
	.4byte	.LASF203
	.byte	0xd1
	.uleb128 0x1
	.4byte	.LASF204
	.byte	0xd1
	.uleb128 0x1
	.4byte	.LASF205
	.byte	0xd2
	.uleb128 0x1
	.4byte	.LASF206
	.byte	0xd3
	.uleb128 0x1
	.4byte	.LASF207
	.byte	0xd4
	.uleb128 0x1
	.4byte	.LASF208
	.byte	0xd5
	.uleb128 0x1
	.4byte	.LASF209
	.byte	0xd5
	.uleb128 0x1
	.4byte	.LASF210
	.byte	0xd6
	.uleb128 0x2a
	.4byte	.LASF211
	.2byte	0x8000
	.byte	0
	.uleb128 0x13
	.4byte	.LASF212
	.byte	0x7
	.2byte	0x7d9
	.byte	0x3
	.4byte	0x669
	.uleb128 0x12
	.4byte	0x87c
	.uleb128 0x20
	.byte	0x5
	.4byte	0x8c
	.byte	0x8
	.2byte	0x153
	.4byte	0x8cc
	.uleb128 0x6
	.4byte	.LASF213
	.sleb128 -7
	.uleb128 0x6
	.4byte	.LASF214
	.sleb128 -6
	.uleb128 0x6
	.4byte	.LASF215
	.sleb128 -5
	.uleb128 0x6
	.4byte	.LASF216
	.sleb128 -4
	.uleb128 0x6
	.4byte	.LASF217
	.sleb128 -3
	.uleb128 0x6
	.4byte	.LASF218
	.sleb128 -2
	.uleb128 0x6
	.4byte	.LASF219
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF220
	.byte	0
	.byte	0
	.uleb128 0x13
	.4byte	.LASF221
	.byte	0x8
	.2byte	0x15c
	.byte	0x3
	.4byte	0x88e
	.uleb128 0xc
	.byte	0x5
	.4byte	0x8c
	.byte	0x9
	.byte	0x5e
	.byte	0xe
	.4byte	0x8ff
	.uleb128 0x6
	.4byte	.LASF222
	.sleb128 -3
	.uleb128 0x6
	.4byte	.LASF223
	.sleb128 -2
	.uleb128 0x6
	.4byte	.LASF224
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF225
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF226
	.byte	0x9
	.byte	0x63
	.byte	0x3
	.4byte	0x8d9
	.uleb128 0x1a
	.4byte	.LASF227
	.byte	0x3e
	.byte	0x10
	.4byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	total_key_num
	.uleb128 0x1a
	.4byte	.LASF228
	.byte	0x3f
	.byte	0x10
	.4byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	one_packet_valid_num
	.uleb128 0x1a
	.4byte	.LASF229
	.byte	0x40
	.byte	0x1f
	.4byte	0x4c3
	.uleb128 0x5
	.byte	0x3
	.4byte	hw_keyscan_status
	.uleb128 0x21
	.4byte	.LASF230
	.byte	0x41
	.4byte	0x889
	.byte	0x3b
	.uleb128 0x21
	.4byte	.LASF231
	.byte	0x42
	.4byte	0x889
	.byte	0x3c
	.uleb128 0x1b
	.4byte	.LASF233
	.byte	0x45
	.byte	0x5
	.4byte	0x5c3
	.uleb128 0x5
	.byte	0x3
	.4byte	is_ghost
	.uleb128 0x2b
	.4byte	.LASF232
	.byte	0x1
	.byte	0x47
	.byte	0x2e
	.4byte	0x97a
	.4byte	0x421e0000
	.uleb128 0x11
	.4byte	0x3b3
	.uleb128 0x12
	.4byte	0x975
	.uleb128 0x1b
	.4byte	.LASF234
	.byte	0x48
	.byte	0x8
	.4byte	0x62e
	.uleb128 0x5
	.byte	0x3
	.4byte	key_transaction
	.uleb128 0x1b
	.4byte	.LASF235
	.byte	0x4a
	.byte	0xa
	.4byte	0x74
	.uleb128 0x5
	.byte	0x3
	.4byte	key_data
	.uleb128 0x2c
	.4byte	.LASF236
	.byte	0x8
	.2byte	0x18d
	.byte	0x12
	.4byte	0x8cc
	.4byte	0x9b8
	.uleb128 0x7
	.4byte	0x74
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF237
	.byte	0x87
	.byte	0x14
	.4byte	0x8ff
	.4byte	0x9cd
	.uleb128 0x7
	.4byte	0x87c
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF238
	.byte	0x7d
	.byte	0x14
	.4byte	0x8ff
	.4byte	0x9e2
	.uleb128 0x7
	.4byte	0x87c
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF239
	.byte	0x8f
	.byte	0x5
	.4byte	0x5c3
	.4byte	0x9f7
	.uleb128 0x7
	.4byte	0x87c
	.byte	0
	.uleb128 0x22
	.4byte	.LASF240
	.byte	0x3c
	.4byte	0xa07
	.uleb128 0x7
	.4byte	0x126
	.byte	0
	.uleb128 0x22
	.4byte	.LASF241
	.byte	0x3b
	.4byte	0xa1c
	.uleb128 0x7
	.4byte	0x126
	.uleb128 0x7
	.4byte	0x64d
	.byte	0
	.uleb128 0x2d
	.4byte	.LASF257
	.byte	0x1
	.2byte	0x1cf
	.byte	0x6
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa43
	.uleb128 0x2e
	.4byte	.LASF242
	.byte	0x1
	.2byte	0x1cf
	.byte	0x35
	.4byte	0x5c3
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF258
	.byte	0x1
	.2byte	0x1ca
	.byte	0x6
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x16
	.4byte	.LASF244
	.2byte	0x1bc
	.4byte	0x616
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa80
	.uleb128 0x23
	.4byte	.LASF243
	.2byte	0x1bc
	.byte	0x54
	.4byte	0x622
	.4byte	.LLST27
	.byte	0
	.uleb128 0x30
	.4byte	.LASF259
	.byte	0x1
	.2byte	0x1ae
	.byte	0x19
	.4byte	0x616
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x16
	.4byte	.LASF245
	.2byte	0x19f
	.4byte	0x616
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xac0
	.uleb128 0x17
	.4byte	.LVL76
	.4byte	0x9a1
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x35
	.byte	0
	.byte	0
	.uleb128 0x16
	.4byte	.LASF246
	.2byte	0x17f
	.4byte	0x616
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb45
	.uleb128 0x24
	.string	"i"
	.2byte	0x18b
	.4byte	0x8c
	.4byte	.LLST25
	.uleb128 0x31
	.4byte	0xd5e
	.4byte	.LBB48
	.4byte	.LLRL26
	.byte	0x1
	.2byte	0x187
	.byte	0x25
	.uleb128 0xf
	.4byte	.LVL60
	.4byte	0x9e2
	.4byte	0xb0b
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x3b
	.byte	0
	.uleb128 0xf
	.4byte	.LVL61
	.4byte	0x9e2
	.4byte	0xb1f
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x3c
	.byte	0
	.uleb128 0xf
	.4byte	.LVL62
	.4byte	0x9cd
	.4byte	0xb33
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x3c
	.byte	0
	.uleb128 0x17
	.4byte	.LVL75
	.4byte	0x9b8
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x3b
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x16
	.4byte	.LASF247
	.2byte	0x111
	.4byte	0x616
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd59
	.uleb128 0x23
	.4byte	.LASF248
	.2byte	0x111
	.byte	0x46
	.4byte	0xd59
	.4byte	.LLST0
	.uleb128 0x8
	.4byte	.LASF114
	.2byte	0x118
	.byte	0xd
	.4byte	0x50
	.4byte	.LLST1
	.uleb128 0x8
	.4byte	.LASF115
	.2byte	0x119
	.byte	0xd
	.4byte	0x50
	.4byte	.LLST2
	.uleb128 0x8
	.4byte	.LASF108
	.2byte	0x11a
	.byte	0x1b
	.4byte	0x3f1
	.4byte	.LLST3
	.uleb128 0x8
	.4byte	.LASF109
	.2byte	0x121
	.byte	0x25
	.4byte	0x43b
	.4byte	.LLST4
	.uleb128 0x8
	.4byte	.LASF110
	.2byte	0x122
	.byte	0x1b
	.4byte	0x497
	.4byte	.LLST5
	.uleb128 0x8
	.4byte	.LASF112
	.2byte	0x123
	.byte	0xd
	.4byte	0x50
	.4byte	.LLST6
	.uleb128 0x8
	.4byte	.LASF113
	.2byte	0x124
	.byte	0xd
	.4byte	0x50
	.4byte	.LLST7
	.uleb128 0x8
	.4byte	.LASF111
	.2byte	0x125
	.byte	0x9
	.4byte	0x5c3
	.4byte	.LLST8
	.uleb128 0x8
	.4byte	.LASF116
	.2byte	0x126
	.byte	0x1e
	.4byte	0x4ef
	.4byte	.LLST9
	.uleb128 0x8
	.4byte	.LASF117
	.2byte	0x127
	.byte	0x21
	.4byte	0x515
	.4byte	.LLST10
	.uleb128 0x24
	.string	"i"
	.2byte	0x14c
	.4byte	0x8c
	.4byte	.LLST11
	.uleb128 0x1d
	.4byte	0xdec
	.4byte	.LBB14
	.4byte	.LLRL12
	.2byte	0x129
	.byte	0xa
	.4byte	0xc42
	.uleb128 0x9
	.4byte	0xe05
	.4byte	.LLST13
	.uleb128 0x9
	.4byte	0xdfa
	.4byte	.LLST14
	.byte	0
	.uleb128 0x32
	.4byte	0xdc7
	.4byte	.LBB20
	.4byte	.LBE20-.LBB20
	.byte	0x1
	.2byte	0x129
	.byte	0x6a
	.4byte	0xc6a
	.uleb128 0x9
	.4byte	0xde0
	.4byte	.LLST15
	.uleb128 0x9
	.4byte	0xdd5
	.4byte	.LLST16
	.byte	0
	.uleb128 0x1d
	.4byte	0xda2
	.4byte	.LBB22
	.4byte	.LLRL17
	.2byte	0x129
	.byte	0xbd
	.4byte	0xc91
	.uleb128 0x9
	.4byte	0xdbb
	.4byte	.LLST18
	.uleb128 0x9
	.4byte	0xdb0
	.4byte	.LLST19
	.byte	0
	.uleb128 0x33
	.4byte	0xd72
	.4byte	.LBB30
	.4byte	.LLRL20
	.byte	0x1
	.2byte	0x129
	.2byte	0x111
	.4byte	0xcc3
	.uleb128 0x9
	.4byte	0xd96
	.4byte	.LLST21
	.uleb128 0x9
	.4byte	0xd8b
	.4byte	.LLST22
	.uleb128 0x9
	.4byte	0xd80
	.4byte	.LLST23
	.byte	0
	.uleb128 0x1d
	.4byte	0xd68
	.4byte	.LBB36
	.4byte	.LLRL24
	.2byte	0x12e
	.byte	0x25
	.4byte	0xd24
	.uleb128 0xf
	.4byte	.LVL25
	.4byte	0x9e2
	.4byte	0xceb
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x3b
	.byte	0
	.uleb128 0xf
	.4byte	.LVL27
	.4byte	0x9e2
	.4byte	0xcff
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x3c
	.byte	0
	.uleb128 0xf
	.4byte	.LVL28
	.4byte	0x9cd
	.4byte	0xd13
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x3c
	.byte	0
	.uleb128 0x17
	.4byte	.LVL53
	.4byte	0x9cd
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x3b
	.byte	0
	.byte	0
	.uleb128 0x34
	.4byte	.LVL29
	.4byte	0xe37
	.uleb128 0xf
	.4byte	.LVL39
	.4byte	0xa07
	.4byte	0xd49
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x40
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	hw_keyscan_dummy_Isr
	.byte	0
	.uleb128 0x17
	.4byte	.LVL41
	.4byte	0x9f7
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x40
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	0x5ea
	.uleb128 0x25
	.4byte	.LASF249
	.byte	0xfe
	.4byte	0x616
	.uleb128 0x25
	.4byte	.LASF250
	.byte	0xec
	.4byte	0x616
	.uleb128 0x18
	.4byte	.LASF251
	.byte	0xbd
	.4byte	0x616
	.4byte	0xda2
	.uleb128 0xa
	.4byte	.LASF116
	.byte	0xbd
	.byte	0x56
	.4byte	0x4ef
	.uleb128 0xa
	.4byte	.LASF110
	.byte	0xbd
	.byte	0x7b
	.4byte	0x497
	.uleb128 0xa
	.4byte	.LASF109
	.byte	0xbd
	.byte	0xa1
	.4byte	0x43b
	.byte	0
	.uleb128 0x18
	.4byte	.LASF252
	.byte	0xb1
	.4byte	0x616
	.4byte	0xdc7
	.uleb128 0xa
	.4byte	.LASF116
	.byte	0xb1
	.byte	0x57
	.4byte	0x4ef
	.uleb128 0xa
	.4byte	.LASF110
	.byte	0xb1
	.byte	0x7c
	.4byte	0x497
	.byte	0
	.uleb128 0x18
	.4byte	.LASF253
	.byte	0xa5
	.4byte	0x616
	.4byte	0xdec
	.uleb128 0xa
	.4byte	.LASF114
	.byte	0xa5
	.byte	0x48
	.4byte	0x50
	.uleb128 0xa
	.4byte	.LASF115
	.byte	0xa5
	.byte	0x59
	.4byte	0x50
	.byte	0
	.uleb128 0x18
	.4byte	.LASF254
	.byte	0x99
	.4byte	0x616
	.4byte	0xe11
	.uleb128 0xa
	.4byte	.LASF113
	.byte	0x99
	.byte	0x45
	.4byte	0x50
	.uleb128 0xa
	.4byte	.LASF112
	.byte	0x99
	.byte	0x5d
	.4byte	0x50
	.byte	0
	.uleb128 0x35
	.4byte	.LASF260
	.byte	0x1
	.byte	0x4c
	.byte	0xd
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe37
	.uleb128 0x36
	.4byte	.LVL0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	key_data
	.byte	0
	.byte	0
	.uleb128 0x37
	.4byte	.LASF261
	.4byte	.LASF261
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
	.uleb128 0x6
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0x11
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
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
	.uleb128 0x15
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
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.sleb128 25
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
	.uleb128 0x17
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 32
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 3
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0x1c
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
	.uleb128 0x1d
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x57
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 11
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
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
	.uleb128 0x21
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
	.sleb128 30
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
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
	.sleb128 6
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
	.uleb128 0x23
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
	.uleb128 0x24
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
	.sleb128 9
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x2e
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
	.sleb128 32
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 1
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x2a
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x5
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x6
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
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
	.uleb128 0x2e
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
	.uleb128 0x2f
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
	.uleb128 0x30
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
	.uleb128 0x31
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
	.uleb128 0x32
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
	.uleb128 0x33
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
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x36
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x82
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x37
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
.LLST27:
	.byte	0x6
	.4byte	.LVL77
	.byte	0x4
	.uleb128 .LVL77-.LVL77
	.uleb128 .LVL78-.LVL77
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL78-.LVL77
	.uleb128 .LVL79-.LVL77
	.uleb128 0x5
	.byte	0x3
	.4byte	key_transaction
	.byte	0x4
	.uleb128 .LVL79-.LVL77
	.uleb128 .LVL80-.LVL77
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL80-.LVL77
	.uleb128 .LFE14-.LVL77
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
.LLST25:
	.byte	0x6
	.4byte	.LVL63
	.byte	0x4
	.uleb128 .LVL63-.LVL63
	.uleb128 .LVL64-.LVL63
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL64-.LVL63
	.uleb128 .LVL65-.LVL63
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL65-.LVL63
	.uleb128 .LVL66-.LVL63
	.uleb128 0x2
	.byte	0x32
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL66-.LVL63
	.uleb128 .LVL67-.LVL63
	.uleb128 0x2
	.byte	0x33
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL67-.LVL63
	.uleb128 .LVL68-.LVL63
	.uleb128 0x2
	.byte	0x34
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL68-.LVL63
	.uleb128 .LVL69-.LVL63
	.uleb128 0x2
	.byte	0x35
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL69-.LVL63
	.uleb128 .LVL70-.LVL63
	.uleb128 0x2
	.byte	0x36
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL70-.LVL63
	.uleb128 .LVL71-.LVL63
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL71-.LVL63
	.uleb128 .LVL72-.LVL63
	.uleb128 0x2
	.byte	0x38
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL72-.LVL63
	.uleb128 .LVL74-.LVL63
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL9-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL9-.LVL1
	.uleb128 .LVL18-.LVL1
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL18-.LVL1
	.uleb128 .LVL20-.LVL1
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
	.uleb128 .LVL20-.LVL1
	.uleb128 .LVL40-.LVL1
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL40-.LVL1
	.uleb128 .LVL42-.LVL1
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
	.uleb128 .LVL42-.LVL1
	.uleb128 .LVL58-.LVL1
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL58-.LVL1
	.uleb128 .LVL59-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL59-.LVL1
	.uleb128 .LFE10-.LVL1
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
	.uleb128 .LVL19-.LVL2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0x4
	.uleb128 .LVL19-.LVL2
	.uleb128 .LVL20-.LVL2
	.uleb128 0x2
	.byte	0x72
	.sleb128 -56
	.byte	0x4
	.uleb128 .LVL20-.LVL2
	.uleb128 .LVL58-.LVL2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL19-.LVL3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0x4
	.uleb128 .LVL19-.LVL3
	.uleb128 .LVL20-.LVL3
	.uleb128 0x2
	.byte	0x72
	.sleb128 -52
	.byte	0x4
	.uleb128 .LVL20-.LVL3
	.uleb128 .LVL58-.LVL3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL5-.LVL4
	.uleb128 .LVL6-.LVL4
	.uleb128 0x2
	.byte	0x7a
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL6-.LVL4
	.uleb128 .LVL19-.LVL4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0x4
	.uleb128 .LVL19-.LVL4
	.uleb128 .LVL20-.LVL4
	.uleb128 0x2
	.byte	0x72
	.sleb128 -48
	.byte	0x4
	.uleb128 .LVL20-.LVL4
	.uleb128 .LVL58-.LVL4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL7
	.byte	0x4
	.uleb128 .LVL7-.LVL7
	.uleb128 .LVL18-.LVL7
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL20-.LVL7
	.uleb128 .LVL37-.LVL7
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL42-.LVL7
	.uleb128 .LVL57-.LVL7
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL18-.LVL8
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL20-.LVL8
	.uleb128 .LVL25-1-.LVL8
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL25-1-.LVL8
	.uleb128 .LVL26-.LVL8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL42-.LVL8
	.uleb128 .LVL51-.LVL8
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL51-.LVL8
	.uleb128 .LVL52-.LVL8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL19-.LVL8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0x4
	.uleb128 .LVL19-.LVL8
	.uleb128 .LVL20-.LVL8
	.uleb128 0x2
	.byte	0x72
	.sleb128 -40
	.byte	0x4
	.uleb128 .LVL20-.LVL8
	.uleb128 .LVL58-.LVL8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL10
	.byte	0x4
	.uleb128 .LVL10-.LVL10
	.uleb128 .LVL19-.LVL10
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0x4
	.uleb128 .LVL19-.LVL10
	.uleb128 .LVL20-.LVL10
	.uleb128 0x2
	.byte	0x72
	.sleb128 -36
	.byte	0x4
	.uleb128 .LVL20-.LVL10
	.uleb128 .LVL58-.LVL10
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
.LLST8:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL19-.LVL11
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL19-.LVL11
	.uleb128 .LVL20-.LVL11
	.uleb128 0x2
	.byte	0x72
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL20-.LVL11
	.uleb128 .LVL58-.LVL11
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL13-.LVL12
	.uleb128 .LVL19-.LVL12
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL19-.LVL12
	.uleb128 .LVL20-.LVL12
	.uleb128 0x2
	.byte	0x72
	.sleb128 -60
	.byte	0x4
	.uleb128 .LVL20-.LVL12
	.uleb128 .LVL21-.LVL12
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL21-.LVL12
	.uleb128 .LVL45-.LVL12
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL45-.LVL12
	.uleb128 .LVL46-.LVL12
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL46-.LVL12
	.uleb128 .LVL47-.LVL12
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL47-.LVL12
	.uleb128 .LVL48-.LVL12
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL48-.LVL12
	.uleb128 .LVL49-.LVL12
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL49-.LVL12
	.uleb128 .LVL50-.LVL12
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL50-.LVL12
	.uleb128 .LVL58-.LVL12
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL14
	.byte	0x4
	.uleb128 .LVL14-.LVL14
	.uleb128 .LVL15-.LVL14
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL15-.LVL14
	.uleb128 .LVL19-.LVL14
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL19-.LVL14
	.uleb128 .LVL20-.LVL14
	.uleb128 0x2
	.byte	0x72
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL20-.LVL14
	.uleb128 .LVL58-.LVL14
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL31-.LVL30
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0x4
	.uleb128 .LVL31-.LVL30
	.uleb128 .LVL32-.LVL30
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL32-.LVL30
	.uleb128 .LVL33-.LVL30
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0x4
	.uleb128 .LVL33-.LVL30
	.uleb128 .LVL34-.LVL30
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL34-.LVL30
	.uleb128 .LVL36-.LVL30
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL37-.LVL30
	.uleb128 .LVL39-1-.LVL30
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL54-.LVL30
	.uleb128 .LVL57-.LVL30
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST13:
	.byte	0x8
	.4byte	.LVL14
	.uleb128 .LVL16-.LVL14
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
.LLST14:
	.byte	0x8
	.4byte	.LVL14
	.uleb128 .LVL16-.LVL14
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
.LLST15:
	.byte	0x8
	.4byte	.LVL16
	.uleb128 .LVL17-.LVL16
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0
.LLST16:
	.byte	0x8
	.4byte	.LVL16
	.uleb128 .LVL17-.LVL16
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
.LLST18:
	.byte	0x6
	.4byte	.LVL17
	.byte	0x4
	.uleb128 .LVL17-.LVL17
	.uleb128 .LVL18-.LVL17
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL20-.LVL17
	.uleb128 .LVL22-.LVL17
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL42-.LVL17
	.uleb128 .LVL43-.LVL17
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL17
	.byte	0x4
	.uleb128 .LVL17-.LVL17
	.uleb128 .LVL18-.LVL17
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL20-.LVL17
	.uleb128 .LVL21-.LVL17
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL21-.LVL17
	.uleb128 .LVL22-.LVL17
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL42-.LVL17
	.uleb128 .LVL43-.LVL17
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST21:
	.byte	0x6
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL24-.LVL22
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL43-.LVL22
	.uleb128 .LVL51-.LVL22
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST22:
	.byte	0x6
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL24-.LVL22
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL43-.LVL22
	.uleb128 .LVL51-.LVL22
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST23:
	.byte	0x6
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL23-.LVL22
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL43-.LVL22
	.uleb128 .LVL44-.LVL22
	.uleb128 0x2
	.byte	0x32
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL45-.LVL22
	.uleb128 .LVL46-.LVL22
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL47-.LVL22
	.uleb128 .LVL48-.LVL22
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL49-.LVL22
	.uleb128 .LVL50-.LVL22
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x54
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
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
.LLRL12:
	.byte	0x5
	.4byte	.LBB14
	.byte	0x4
	.uleb128 .LBB14-.LBB14
	.uleb128 .LBE14-.LBB14
	.byte	0x4
	.uleb128 .LBB18-.LBB14
	.uleb128 .LBE18-.LBB14
	.byte	0x4
	.uleb128 .LBB19-.LBB14
	.uleb128 .LBE19-.LBB14
	.byte	0
.LLRL17:
	.byte	0x5
	.4byte	.LBB22
	.byte	0x4
	.uleb128 .LBB22-.LBB22
	.uleb128 .LBE22-.LBB22
	.byte	0x4
	.uleb128 .LBB28-.LBB22
	.uleb128 .LBE28-.LBB22
	.byte	0x4
	.uleb128 .LBB29-.LBB22
	.uleb128 .LBE29-.LBB22
	.byte	0x4
	.uleb128 .LBB41-.LBB22
	.uleb128 .LBE41-.LBB22
	.byte	0x4
	.uleb128 .LBB42-.LBB22
	.uleb128 .LBE42-.LBB22
	.byte	0
.LLRL20:
	.byte	0x5
	.4byte	.LBB30
	.byte	0x4
	.uleb128 .LBB30-.LBB30
	.uleb128 .LBE30-.LBB30
	.byte	0x4
	.uleb128 .LBB35-.LBB30
	.uleb128 .LBE35-.LBB30
	.byte	0x4
	.uleb128 .LBB43-.LBB30
	.uleb128 .LBE43-.LBB30
	.byte	0x4
	.uleb128 .LBB44-.LBB30
	.uleb128 .LBE44-.LBB30
	.byte	0
.LLRL24:
	.byte	0x5
	.4byte	.LBB36
	.byte	0x4
	.uleb128 .LBB36-.LBB36
	.uleb128 .LBE36-.LBB36
	.byte	0x4
	.uleb128 .LBB40-.LBB36
	.uleb128 .LBE40-.LBB36
	.byte	0x4
	.uleb128 .LBB45-.LBB36
	.uleb128 .LBE45-.LBB36
	.byte	0
.LLRL26:
	.byte	0x5
	.4byte	.LBB48
	.byte	0x4
	.uleb128 .LBB48-.LBB48
	.uleb128 .LBE48-.LBB48
	.byte	0x4
	.uleb128 .LBB53-.LBB48
	.uleb128 .LBE53-.LBB48
	.byte	0x4
	.uleb128 .LBB54-.LBB48
	.uleb128 .LBE54-.LBB48
	.byte	0x4
	.uleb128 .LBB55-.LBB48
	.uleb128 .LBE55-.LBB48
	.byte	0
.LLRL28:
	.byte	0x7
	.4byte	.LFB3
	.uleb128 .LFE3-.LFB3
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF105:
	.string	"HAL_HW_KEYSCAN_IO_SETING_LOW_ACTIVE"
.LASF158:
	.string	"HAL_CLOCK_CG_SPIMST0"
.LASF159:
	.string	"HAL_CLOCK_CG_SPIMST1"
.LASF160:
	.string	"HAL_CLOCK_CG_SPIMST2"
.LASF176:
	.string	"HAL_CLOCK_CG_EFUSE"
.LASF233:
	.string	"is_ghost"
.LASF152:
	.string	"HAL_CLOCK_CG_PMU_1M"
.LASF22:
	.string	"PMU_IRQn"
.LASF254:
	.string	"hw_keyscan_debounce_is_valid"
.LASF70:
	.string	"char"
.LASF23:
	.string	"MCU_DMA_IRQn"
.LASF225:
	.string	"HAL_CLOCK_STATUS_OK"
.LASF247:
	.string	"hal_hw_keyscan_init"
.LASF57:
	.string	"SFR_ROW_MAP"
.LASF174:
	.string	"HAL_CLOCK_CG_IBEX"
.LASF199:
	.string	"HAL_CLOCK_CG_CRYPTO"
.LASF54:
	.string	"SFR_RLS_DEB_TIME"
.LASF156:
	.string	"HAL_CLOCK_CG_BUS_ERR_AO"
.LASF172:
	.string	"HAL_CLOCK_CG_USB"
.LASF107:
	.string	"hal_hw_keyscan_io_setting_t"
.LASF250:
	.string	"hal_hw_keyscan_clock_enable"
.LASF3:
	.string	"unsigned int"
.LASF240:
	.string	"hal_nvic_enable_irq"
.LASF145:
	.string	"HAL_CLOCK_CG_OSTIMER"
.LASF236:
	.string	"hal_gpt_delay_us"
.LASF106:
	.string	"HAL_HW_KEYSCAN_IO_SETING_HIGH_ACTIVE"
.LASF255:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF82:
	.string	"HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_10T"
.LASF178:
	.string	"HAL_CLOCK_CG_CMSYS_BUS"
.LASF18:
	.string	"SPI_MST1_IRQn"
.LASF173:
	.string	"HAL_CLOCK_CG_AUD_INTBUS"
.LASF5:
	.string	"short int"
.LASF200:
	.string	"HAL_CLOCK_CG_USB_BUS"
.LASF226:
	.string	"hal_clock_status_t"
.LASF124:
	.string	"hal_hw_keyscan_callback_t"
.LASF230:
	.string	"keycan_cg_blck"
.LASF224:
	.string	"HAL_CLOCK_STATUS_ERROR"
.LASF102:
	.string	"HAL_HW_KEYSCAN_TYPE_GAMING_KB_MECH"
.LASF50:
	.string	"SFR_SCAN_MODE"
.LASF108:
	.string	"mode"
.LASF242:
	.string	"bt_trigger_enable"
.LASF30:
	.string	"BT_IRQn"
.LASF126:
	.string	"HAL_CLOCK_CG_AUXADC"
.LASF42:
	.string	"FIFO_STOP_FLAG"
.LASF45:
	.string	"DEB_DONE_SYNC"
.LASF31:
	.string	"IRQ_NUMBER_MAX"
.LASF36:
	.string	"RESERVED"
.LASF27:
	.string	"SPI_MST0_IRQn"
.LASF168:
	.string	"HAL_CLOCK_CG_CKSYS_DEBUG_DIS"
.LASF140:
	.string	"HAL_CLOCK_CG_GLB_CON_DEBUG_DIS"
.LASF87:
	.string	"HAL_HW_KEYSCAN_RATE_133RR"
.LASF154:
	.string	"HAL_CLOCK_CG_SPIMST0_BUS"
.LASF89:
	.string	"HAL_HW_KEYSCAN_RATE_500RR"
.LASF11:
	.string	"uint32_t"
.LASF196:
	.string	"HAL_CLOCK_CG_SEC_MON"
.LASF161:
	.string	"HAL_CLOCK_CG_I3C"
.LASF163:
	.string	"HAL_CLOCK_CG_BT_MAC_CONN"
.LASF21:
	.string	"UART_DMA_IRQn"
.LASF229:
	.string	"hw_keyscan_status"
.LASF211:
	.string	"HAL_CLOCK_CG_PWM_MULTI_CTRL"
.LASF61:
	.string	"SFR_KEYSCAN_EN"
.LASF165:
	.string	"HAL_CLOCK_CG_AUD_TEST"
.LASF35:
	.string	"SFR_COL_NUM"
.LASF248:
	.string	"keyscan_config"
.LASF2:
	.string	"long long unsigned int"
.LASF139:
	.string	"HAL_CLOCK_CG_I3C_DMA0"
.LASF189:
	.string	"HAL_CLOCK_CG_I3C_DMA1"
.LASF170:
	.string	"HAL_CLOCK_CG_ESC"
.LASF192:
	.string	"HAL_CLOCK_CG_IRRX"
.LASF99:
	.string	"KEYSCAN_HWSTATUS_RUNGING"
.LASF46:
	.string	"KEYSCAN_READ_SYNC"
.LASF71:
	.string	"HAL_HW_KEYSCAN_OFFICE_KB"
.LASF121:
	.string	"HAL_HW_KEYSCAN_INVALID_PARAMETER"
.LASF88:
	.string	"HAL_HW_KEYSCAN_RATE_250RR"
.LASF182:
	.string	"HAL_CLOCK_CG_OSC_LS_D2"
.LASF157:
	.string	"HAL_CLOCK_CG_SEC_MON_AO"
.LASF218:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF53:
	.string	"SFR_DEB_EN"
.LASF112:
	.string	"release_debounce"
.LASF210:
	.string	"HAL_CLOCK_CG_DUMMY_END"
.LASF32:
	.string	"IRQn_Type"
.LASF166:
	.string	"HAL_CLOCK_CG_SEC_MON_TOP"
.LASF241:
	.string	"hal_nvic_register_isr_handler"
.LASF49:
	.string	"MATRIX_SIZE_UNION"
.LASF190:
	.string	"HAL_CLOCK_CG_TRNG"
.LASF202:
	.string	"HAL_CLOCK_CG_CMSYS_ROM"
.LASF231:
	.string	"keycan_cg_2m"
.LASF62:
	.string	"AFIFO_DOUT"
.LASF222:
	.string	"HAL_CLOCK_STATUS_UNINITIALIZED"
.LASF116:
	.string	"keyboard_type"
.LASF147:
	.string	"HAL_CLOCK_CG_GPTIMER_SEC"
.LASF118:
	.string	"_Bool"
.LASF55:
	.string	"SFR_PRS_DEB_TIME"
.LASF104:
	.string	"hal_hw_keyscan_kb_type_t"
.LASF60:
	.string	"SFR_KEYSCAN_IO_EN"
.LASF144:
	.string	"HAL_CLOCK_CG_SPM_SYS"
.LASF175:
	.string	"HAL_CLOCK_CG_SEJ"
.LASF143:
	.string	"HAL_CLOCK_CG_SPM_DIV"
.LASF73:
	.string	"HAL_HW_KEYSCAN_GAMING_KB"
.LASF179:
	.string	"HAL_CLOCK_CG_MEM_BUS"
.LASF83:
	.string	"HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_14T"
.LASF201:
	.string	"HAL_CLOCK_CG_USB_DMA"
.LASF232:
	.string	"keyscan_register"
.LASF164:
	.string	"HAL_CLOCK_CG_IRTX"
.LASF214:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF37:
	.string	"MATRIX_SIZE_CELLS"
.LASF223:
	.string	"HAL_CLOCK_STATUS_INVALID_PARAMETER"
.LASF151:
	.string	"HAL_CLOCK_CG_UART0"
.LASF133:
	.string	"HAL_CLOCK_CG_UART1"
.LASF134:
	.string	"HAL_CLOCK_CG_UART2"
.LASF253:
	.string	"hw_keyscan_row_col_num_is_valid"
.LASF76:
	.string	"HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_2T"
.LASF44:
	.string	"AFIFO_STATUS"
.LASF122:
	.string	"HAL_HW_KEYSCAN_STATUS_OK"
.LASF110:
	.string	"rate"
.LASF169:
	.string	"HAL_CLOCK_CG_SFC"
.LASF119:
	.string	"hal_hw_keyscan_config_t"
.LASF41:
	.string	"AFIFO_FULL_SYNC"
.LASF13:
	.string	"SW_IRQn"
.LASF244:
	.string	"hal_hw_keyscan_register_callback"
.LASF197:
	.string	"HAL_CLOCK_CG_AESOTF"
.LASF10:
	.string	"uint8_t"
.LASF191:
	.string	"HAL_CLOCK_CG_SPISLV_BUS"
.LASF115:
	.string	"col_num"
.LASF217:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF187:
	.string	"HAL_CLOCK_CG_SPIMST2_BUS"
.LASF194:
	.string	"HAL_CLOCK_CG_AIO"
.LASF239:
	.string	"hal_clock_is_enabled"
.LASF7:
	.string	"long long int"
.LASF75:
	.string	"hal_hw_keyscan_mode_t"
.LASF26:
	.string	"I3C0_DMA_IRQn"
.LASF91:
	.string	"HAL_HW_KEYSCAN_RATE_2KRR"
.LASF56:
	.string	"SFR_COL_MAP"
.LASF185:
	.string	"HAL_CLOCK_CG_AUXADC_SRAM"
.LASF238:
	.string	"hal_clock_enable"
.LASF117:
	.string	"col_in_setting"
.LASF257:
	.string	"hal_hw_keyscan_align_bt_trigger_set_enable"
.LASF251:
	.string	"hw_keyscan_io_delay_is_valid"
.LASF17:
	.string	"UART_IRQn"
.LASF260:
	.string	"hw_keyscan_dummy_Isr"
.LASF84:
	.string	"hal_hw_keyscan_io_switch_time_t"
.LASF67:
	.string	"STATUS_UNION"
.LASF204:
	.string	"HAL_CLOCK_CG_PSUEDO_OSC_26M"
.LASF38:
	.string	"MATRIX_SIZE"
.LASF63:
	.string	"AFIFO_STATUS_UNION"
.LASF129:
	.string	"HAL_CLOCK_CG_PWM_2"
.LASF167:
	.string	"HAL_CLOCK_CG_BUS_ERR_TOP"
.LASF131:
	.string	"HAL_CLOCK_CG_PWM_4"
.LASF132:
	.string	"HAL_CLOCK_CG_ARGB_BCLK"
.LASF29:
	.string	"USB_IRQn"
.LASF181:
	.string	"HAL_CLOCK_CG_AUD_ENGINE"
.LASF85:
	.string	"HAL_HW_KEYSCAN_RATE_100RR"
.LASF135:
	.string	"HAL_CLOCK_CG_UART_DMA0"
.LASF136:
	.string	"HAL_CLOCK_CG_UART_DMA1"
.LASF137:
	.string	"HAL_CLOCK_CG_UART_DMA2"
.LASF96:
	.string	"hal_hw_keyscan_rate_t"
.LASF72:
	.string	"HAL_HW_KEYSCAN_GAMING_KB_ALIGN_BT"
.LASF216:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF109:
	.string	"swich_time"
.LASF101:
	.string	"HAL_HW_KEYSCAN_TYPE_OFFICE_KB"
.LASF69:
	.string	"long double"
.LASF59:
	.string	"SFR_COL_IN_SETTING"
.LASF256:
	.string	"IRQn"
.LASF209:
	.string	"HAL_CLOCK_CG_PSEUDO_END"
.LASF120:
	.string	"HAL_HW_KEYSCAN_STATUS_ERROR"
.LASF150:
	.string	"HAL_CLOCK_CG_KEY_SCAN_F2M"
.LASF213:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF47:
	.string	"STATUS_CELLS"
.LASF16:
	.string	"KEYSCAN_IRQn"
.LASF77:
	.string	"HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_3T"
.LASF43:
	.string	"AFIFO_STATUS_CELLS"
.LASF66:
	.string	"SOFT_RST"
.LASF19:
	.string	"RTC_IRQn"
.LASF51:
	.string	"SFR_IO_SW_TIME_SEL"
.LASF183:
	.string	"HAL_CLOCK_CG_OSC_HS_D2"
.LASF206:
	.string	"HAL_CLOCK_CG_PSEUDO_DCXO_DIG_MACRO"
.LASF184:
	.string	"HAL_CLOCK_CG_OSC_HS_D4"
.LASF92:
	.string	"HAL_HW_KEYSCAN_RATE_4KRR"
.LASF246:
	.string	"hal_hw_keyscan_deinit"
.LASF162:
	.string	"HAL_CLOCK_CG_BT_HOP"
.LASF220:
	.string	"HAL_GPT_STATUS_OK"
.LASF193:
	.string	"HAL_CLOCK_CG_IRRX_BUS"
.LASF6:
	.string	"long int"
.LASF14:
	.string	"LED_IRQn"
.LASF237:
	.string	"hal_clock_disable"
.LASF235:
	.string	"key_data"
.LASF24:
	.string	"EINT_IRQn"
.LASF219:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF113:
	.string	"press_debounce"
.LASF20:
	.string	"GPT_IRQn"
.LASF78:
	.string	"HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_4T"
.LASF100:
	.string	"hal_keyscan_hwstatus_t"
.LASF86:
	.string	"HAL_HW_KEYSCAN_RATE_125RR"
.LASF68:
	.string	"HW_KEYSCAN_REGISTER_T"
.LASF177:
	.string	"HAL_CLOCK_CG_BT_MAC"
.LASF215:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF205:
	.string	"HAL_CLOCK_CG_PSEUDO_DCXO_PWR_CTRL"
.LASF95:
	.string	"HAL_HW_KEYSCAN_RATE_32KRR"
.LASF148:
	.string	"HAL_CLOCK_CG_SECURITY_AO"
.LASF94:
	.string	"HAL_HW_KEYSCAN_RATE_16KRR"
.LASF34:
	.string	"SFR_ROW_NUM"
.LASF64:
	.string	"GHOST_KEY"
.LASF79:
	.string	"HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_5T"
.LASF12:
	.string	"long unsigned int"
.LASF228:
	.string	"one_packet_valid_num"
.LASF127:
	.string	"HAL_CLOCK_CG_PWM_DMA_0"
.LASF74:
	.string	"HAL_HW_KEYSCAN_SW_TRIGGER"
.LASF261:
	.string	"__mulsi3"
.LASF207:
	.string	"HAL_CLOCK_CG_PSEUDO_RGU_32K"
.LASF149:
	.string	"HAL_CLOCK_CG_KEY_SCAN_BCLK"
.LASF141:
	.string	"HAL_CLOCK_CG_SPM_PCLK"
.LASF221:
	.string	"hal_gpt_status_t"
.LASF58:
	.string	"SFR_KB_TYPE"
.LASF155:
	.string	"HAL_CLOCK_CG_SPIMST1_BUS"
.LASF8:
	.string	"unsigned char"
.LASF103:
	.string	"HAL_HW_KEYSCAN_TYPE_GAMING_KB_OPT"
.LASF111:
	.string	"debounce_en"
.LASF123:
	.string	"hal_hw_keyscan_status_t"
.LASF80:
	.string	"HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_6T"
.LASF227:
	.string	"total_key_num"
.LASF195:
	.string	"HAL_CLOCK_CG_BUS_ERR"
.LASF146:
	.string	"HAL_CLOCK_CG_GPTIMER"
.LASF212:
	.string	"hal_clock_cg_id"
.LASF28:
	.string	"IRQ_GEN_IRQn"
.LASF245:
	.string	"hal_hw_keyscan_enable"
.LASF243:
	.string	"callback"
.LASF171:
	.string	"HAL_CLOCK_CG_SPISLV"
.LASF180:
	.string	"HAL_CLOCK_CG_CONN_BUS"
.LASF25:
	.string	"I3C0_IRQn"
.LASF130:
	.string	"HAL_CLOCK_CG_PWM_3"
.LASF198:
	.string	"HAL_CLOCK_CG_AESOTF_ESC"
.LASF4:
	.string	"signed char"
.LASF203:
	.string	"HAL_CLOCK_CG_PSEUDO_BEGIN"
.LASF40:
	.string	"AFIFO_EMPTY"
.LASF9:
	.string	"short unsigned int"
.LASF52:
	.string	"SFR_KEYSCAN_RATE_DLY_SEL"
.LASF186:
	.string	"HAL_CLOCK_CG_FAST_DMA_0"
.LASF153:
	.string	"HAL_CLOCK_CG_FAST_DMA_1"
.LASF39:
	.string	"AFIFO_DNUM"
.LASF234:
	.string	"key_transaction"
.LASF252:
	.string	"hw_keyscan_scan_rate_is_valid"
.LASF138:
	.string	"HAL_CLOCK_CG_I3C0"
.LASF188:
	.string	"HAL_CLOCK_CG_I3C1"
.LASF90:
	.string	"HAL_HW_KEYSCAN_RATE_1KRR"
.LASF258:
	.string	"hal_hw_keyscan_sw_trigger"
.LASF97:
	.string	"KEYSCAN_HWSTATUS_UNINITIALIZED"
.LASF48:
	.string	"STATUS"
.LASF128:
	.string	"HAL_CLOCK_CG_PWM_DMA_1"
.LASF125:
	.string	"hal_nvic_isr_t"
.LASF65:
	.string	"SFR_IRQ_CLEAR"
.LASF15:
	.string	"QDEC_IRQn"
.LASF142:
	.string	"HAL_CLOCK_CG_SPM_BCLK_CM33"
.LASF81:
	.string	"HAL_HW_KEYSCAN_IO_SWITCH_TIME_SELECTION_8T"
.LASF93:
	.string	"HAL_HW_KEYSCAN_RATE_8KRR"
.LASF114:
	.string	"row_num"
.LASF208:
	.string	"HAL_CLOCK_CG_PSEUDO_SLOW_BUS"
.LASF259:
	.string	"hal_hw_keyscan_disable"
.LASF33:
	.string	"hal_nvic_irq_t"
.LASF98:
	.string	"KEYSCAN_HWSTATUS_INITIALIZED"
.LASF249:
	.string	"hal_hw_keyscan_clock_disable"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_hw_keyscan.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
