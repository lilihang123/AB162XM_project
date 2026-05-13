	.file	"pka_share.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/pka_share/src/pka_share.c"
	.section	.text.pka_share_hw_semaphore_take,"ax",@progbits
	.align	1
	.globl	pka_share_hw_semaphore_take
	.hidden	pka_share_hw_semaphore_take
	.type	pka_share_hw_semaphore_take, @function
pka_share_hw_semaphore_take:
.LFB15:
	.file 1 "/workdir/airoha/common/middleware/airoha/pka_share/src/pka_share.c"
	.loc 1 124 1
	.cfi_startproc
.LVL0:
	.loc 1 125 5
	.loc 1 128 5
	.loc 1 134 279 discriminator 3
	.loc 1 128 12
	.loc 1 124 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	ra,12(sp)
	sw	s1,4(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 124 1
	sw	a0,0(sp)
	.loc 1 128 12
	li	s0,1
.LVL1:
.L5:
	.loc 1 129 9 is_stmt 1
	.loc 1 129 43 is_stmt 0
	lw	a0,0(sp)
	call	hal_hw_semaphore_take
.LVL2:
	.loc 1 129 12 discriminator 1
	beq	a0,zero,.L1
	.loc 1 133 9 is_stmt 1
	.loc 1 133 12 is_stmt 0
	li	a4,500
	addi	s1,s0,1
	bgtu	s0,a4,.L3
	.loc 1 134 279 is_stmt 1 discriminator 3
	.loc 1 128 12
.LVL3:
	mv	s0,s1
	j	.L5
.LVL4:
.L3:
	.loc 1 134 13
.LBB26:
	.loc 1 134 30 discriminator 1
	.loc 1 134 106 discriminator 1
	.loc 1 134 248 discriminator 1
	li	a2,134
	lla	a1,file.4
	lla	a0,exp.5
	call	light_assert
.LVL5:
.LBE26:
	.loc 1 134 279 discriminator 3
	.loc 1 128 12
	mv	s0,s1
	bne	s1,zero,.L5
.LVL6:
.L1:
	.loc 1 137 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
.LVL7:
	jr	ra
	.cfi_endproc
.LFE15:
	.size	pka_share_hw_semaphore_take, .-pka_share_hw_semaphore_take
	.section	.text.pka_share_hw_semaphore_give,"ax",@progbits
	.align	1
	.globl	pka_share_hw_semaphore_give
	.hidden	pka_share_hw_semaphore_give
	.type	pka_share_hw_semaphore_give, @function
pka_share_hw_semaphore_give:
.LFB16:
	.loc 1 140 1 is_stmt 1
	.cfi_startproc
.LVL8:
	.loc 1 141 5
	.loc 1 140 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 141 39
	call	hal_hw_semaphore_give
.LVL9:
	.loc 1 141 8 discriminator 1
	beq	a0,zero,.L13
	.loc 1 142 9 is_stmt 1
.LBB27:
	.loc 1 142 26 discriminator 1
	.loc 1 142 102 discriminator 1
	.loc 1 142 244 discriminator 1
.LBE27:
	.loc 1 144 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
.LBB28:
	.loc 1 142 244 discriminator 1
	li	a2,142
.LBE28:
	.loc 1 144 1
.LBB29:
	.loc 1 142 244 discriminator 1
	lla	a1,file.2
	lla	a0,exp.3
.LBE29:
	.loc 1 144 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
.LBB30:
	.loc 1 142 244 discriminator 1
	tail	light_assert
.LVL10:
.L13:
	.cfi_restore_state
.LBE30:
	.loc 1 144 1
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE16:
	.size	pka_share_hw_semaphore_give, .-pka_share_hw_semaphore_give
	.section	.text.pka_share_init,"ax",@progbits
	.align	1
	.globl	pka_share_init
	.hidden	pka_share_init
	.type	pka_share_init, @function
pka_share_init:
.LFB17:
	.loc 1 268 1 is_stmt 1
	.cfi_startproc
	.loc 1 269 5
	.loc 1 269 19 is_stmt 0
	lla	a5,ccm_pka_share
	sw	a5,pka_share_ptr,a4
	.loc 1 270 5 is_stmt 1
	.loc 1 270 38 is_stmt 0
	sw	zero,pka_share_tx_hid_ctl+52,a5
	.loc 1 271 1
	ret
	.cfi_endproc
.LFE17:
	.size	pka_share_init, .-pka_share_init
	.section	.text.pka_share_tx_init,"ax",@progbits
	.align	1
	.globl	pka_share_tx_init
	.hidden	pka_share_tx_init
	.type	pka_share_tx_init, @function
pka_share_tx_init:
.LFB18:
	.loc 1 275 1 is_stmt 1
	.cfi_startproc
.LVL11:
	.loc 1 276 5
	.loc 1 276 18 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 276 28
	sh	a0,60(a5)
	.loc 1 277 5 is_stmt 1
	.loc 1 277 44 is_stmt 0
	sh	a1,56(a5)
	.loc 1 278 5 is_stmt 1
	.loc 1 278 35 is_stmt 0
	sh	a2,58(a5)
	.loc 1 279 1
	ret
	.cfi_endproc
.LFE18:
	.size	pka_share_tx_init, .-pka_share_tx_init
	.globl	__mulsi3
	.section	.text.pka_share_tx_buf_get_by_idx,"ax",@progbits
	.align	1
	.globl	pka_share_tx_buf_get_by_idx
	.hidden	pka_share_tx_buf_get_by_idx
	.type	pka_share_tx_buf_get_by_idx, @function
pka_share_tx_buf_get_by_idx:
.LFB19:
	.loc 1 334 1 is_stmt 1
	.cfi_startproc
.LVL12:
	.loc 1 335 5
	.loc 1 334 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 335 40
	lw	s0,pka_share_ptr
.LVL13:
	.loc 1 336 5 is_stmt 1
	.loc 1 335 66 is_stmt 0
	lhu	a4,46(s0)
	lhu	a5,56(s0)
	.loc 1 334 1
	mv	a1,a0
	.loc 1 336 62
	li	a0,65536
.LVL14:
	.loc 1 335 66
	add	a5,a5,a4
	.loc 1 335 109
	addi	a5,a5,3
	.loc 1 336 62
	addi	a0,a0,-4
	and	a0,a5,a0
	.loc 1 334 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 336 62
	call	__mulsi3
.LVL15:
	.loc 1 336 49
	lw	a5,40(s0)
	.loc 1 337 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	add	a0,a5,a0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE19:
	.size	pka_share_tx_buf_get_by_idx, .-pka_share_tx_buf_get_by_idx
	.section	.text.pka_share_tx_buf_get_payload,"ax",@progbits
	.align	1
	.globl	pka_share_tx_buf_get_payload
	.hidden	pka_share_tx_buf_get_payload
	.type	pka_share_tx_buf_get_payload, @function
pka_share_tx_buf_get_payload:
.LFB20:
	.loc 1 340 1 is_stmt 1
	.cfi_startproc
.LVL16:
	.loc 1 341 5
	.loc 1 341 31 is_stmt 0
	lw	a5,pka_share_ptr
	lhu	a5,46(a5)
	.loc 1 342 1
	add	a0,a0,a5
.LVL17:
	ret
	.cfi_endproc
.LFE20:
	.size	pka_share_tx_buf_get_payload, .-pka_share_tx_buf_get_payload
	.section	.text.pka_share_tx_buf_init,"ax",@progbits
	.align	1
	.globl	pka_share_tx_buf_init
	.hidden	pka_share_tx_buf_init
	.type	pka_share_tx_buf_init, @function
pka_share_tx_buf_init:
.LFB21:
	.loc 1 345 1 is_stmt 1
	.cfi_startproc
.LVL18:
	.loc 1 346 5
	.loc 1 346 36 is_stmt 0
	lw	a4,pka_share_ptr
.LVL19:
	.loc 1 347 5 is_stmt 1
	.loc 1 346 14 is_stmt 0
	lhu	a5,44(a4)
	.loc 1 347 8
	srli	a5,a5,1
	slli	a5,a5,1
	.loc 1 347 17
	add	a0,a0,a5
.LVL20:
	li	a5,20
	sh	a5,0(a0)
.LVL21:
	.loc 1 348 5 is_stmt 1
	.loc 1 348 36 is_stmt 0
	lhu	a5,56(a4)
	.loc 1 348 21
	sh	a5,2(a0)
	.loc 1 349 5 is_stmt 1
	.loc 1 349 21 is_stmt 0
	sh	a5,14(a0)
	.loc 1 350 5 is_stmt 1
	.loc 1 350 21 is_stmt 0
	lhu	a5,60(a4)
	seqz	a5,a5
	slli	a5,a5,1
	.loc 1 350 21 discriminator 4
	sh	a5,12(a0)
	.loc 1 352 1
	ret
	.cfi_endproc
.LFE21:
	.size	pka_share_tx_buf_init, .-pka_share_tx_buf_init
	.section	.text.pka_tx_buf_set_active_state,"ax",@progbits
	.align	1
	.globl	pka_tx_buf_set_active_state
	.hidden	pka_tx_buf_set_active_state
	.type	pka_tx_buf_set_active_state, @function
pka_tx_buf_set_active_state:
.LFB23:
	.loc 1 360 1 is_stmt 1
	.cfi_startproc
.LVL22:
	.loc 1 361 5
.LBB33:
.LBB34:
	.loc 1 362 12 is_stmt 0
	lbu	a4,12(a0)
.LBE34:
.LBE33:
	.loc 1 364 18
	andi	a5,a4,223
	.loc 1 361 8
	beq	a1,zero,.L24
.LVL23:
.LBB36:
.LBB35:
	.loc 1 362 9 is_stmt 1
	.loc 1 362 18 is_stmt 0
	ori	a5,a4,32
.LVL24:
.L24:
	sb	a5,12(a0)
.LBE35:
.LBE36:
	.loc 1 366 1
	ret
	.cfi_endproc
.LFE23:
	.size	pka_tx_buf_set_active_state, .-pka_tx_buf_set_active_state
	.section	.text.pka_tx_buf_is_hid,"ax",@progbits
	.align	1
	.globl	pka_tx_buf_is_hid
	.hidden	pka_tx_buf_is_hid
	.type	pka_tx_buf_is_hid, @function
pka_tx_buf_is_hid:
.LFB32:
	.loc 1 410 1 is_stmt 1
	.cfi_startproc
.LVL25:
	.loc 1 412 5
	.loc 1 412 46 is_stmt 0
	lw	a5,pka_share_ptr
.LVL26:
	.loc 1 413 5 is_stmt 1
	.loc 1 413 11 is_stmt 0
	lw	a4,76(a5)
	.loc 1 414 47
	lw	a3,96(a5)
	.loc 1 414 47 discriminator 3
	li	a0,1
.LVL27:
	.loc 1 413 11
	lw	a4,0(a4)
.LVL28:
	.loc 1 414 5 is_stmt 1
	.loc 1 414 47 is_stmt 0
	beq	a3,a4,.L26
	.loc 1 414 47 discriminator 2
	lw	a0,100(a5)
	sub	a0,a0,a4
	seqz	a0,a0
.L26:
	.loc 1 421 1
	ret
	.cfi_endproc
.LFE32:
	.size	pka_tx_buf_is_hid, .-pka_tx_buf_is_hid
	.section	.text.pka_tx_buf_remain_length,"ax",@progbits
	.align	1
	.globl	pka_tx_buf_remain_length
	.hidden	pka_tx_buf_remain_length
	.type	pka_tx_buf_remain_length, @function
pka_tx_buf_remain_length:
.LFB33:
	.loc 1 425 1 is_stmt 1
	.cfi_startproc
.LVL29:
	.loc 1 426 5
.LBB37:
.LBB38:
	.loc 1 370 5
.LBE38:
.LBE37:
.LBB39:
.LBB40:
	.loc 1 380 5
.LBE40:
.LBE39:
	.loc 1 426 53 is_stmt 0 discriminator 2
	lhu	a5,2(a0)
	lhu	a4,14(a0)
	sub	a0,a5,a4
.LVL30:
	.loc 1 427 1
	slli	a0,a0,16
	srli	a0,a0,16
	ret
	.cfi_endproc
.LFE33:
	.size	pka_tx_buf_remain_length, .-pka_tx_buf_remain_length
	.section	.text.pka_tx_buf_is_empty,"ax",@progbits
	.align	1
	.globl	pka_tx_buf_is_empty
	.hidden	pka_tx_buf_is_empty
	.type	pka_tx_buf_is_empty, @function
pka_tx_buf_is_empty:
.LFB34:
	.loc 1 430 1 is_stmt 1
	.cfi_startproc
.LVL31:
	.loc 1 431 5
	.loc 1 431 8 is_stmt 0
	beq	a0,zero,.L31
.LVL32:
.LBB41:
.LBB42:
	.loc 1 370 5 is_stmt 1
.LBE42:
.LBE41:
	.loc 1 431 20 is_stmt 0 discriminator 1
	lhu	a0,2(a0)
.LVL33:
	seqz	a0,a0
	ret
.LVL34:
.L31:
	.loc 1 432 15
	li	a0,1
.LVL35:
	.loc 1 435 1
	ret
	.cfi_endproc
.LFE34:
	.size	pka_tx_buf_is_empty, .-pka_tx_buf_is_empty
	.section	.text.pka_flag_set_loading,"ax",@progbits
	.align	1
	.globl	pka_flag_set_loading
	.hidden	pka_flag_set_loading
	.type	pka_flag_set_loading, @function
pka_flag_set_loading:
.LFB35:
	.loc 1 438 1 is_stmt 1
	.cfi_startproc
.LVL36:
	.loc 1 439 5
	.loc 1 439 35 is_stmt 0
	lw	a5,pka_share_ptr
	lw	a4,64(a5)
	.loc 1 439 45
	lw	a5,0(a4)
	andi	a5,a5,-65
	.loc 1 440 5 is_stmt 1
	.loc 1 440 8 is_stmt 0
	beq	a0,zero,.L33
	.loc 1 441 9 is_stmt 1
	.loc 1 441 49 is_stmt 0
	ori	a5,a5,64
.L33:
	.loc 1 439 45
	sw	a5,0(a4)
	.loc 1 443 1
	ret
	.cfi_endproc
.LFE35:
	.size	pka_flag_set_loading, .-pka_flag_set_loading
	.section	.text.pka_active_state_match,"ax",@progbits
	.align	1
	.globl	pka_active_state_match
	.hidden	pka_active_state_match
	.type	pka_active_state_match, @function
pka_active_state_match:
.LFB36:
	.loc 1 446 1 is_stmt 1
	.cfi_startproc
.LVL37:
	.loc 1 447 5
	.loc 1 447 39 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 447 13
	lw	a5,132(a5)
	.loc 1 447 61
	lhu	a5,0(a5)
	sub	a0,a5,a0
.LVL38:
	.loc 1 448 1
	seqz	a0,a0
	ret
	.cfi_endproc
.LFE36:
	.size	pka_active_state_match, .-pka_active_state_match
	.section	.text.pka_active_state_set,"ax",@progbits
	.align	1
	.globl	pka_active_state_set
	.hidden	pka_active_state_set
	.type	pka_active_state_set, @function
pka_active_state_set:
.LFB37:
	.loc 1 461 1 is_stmt 1
	.cfi_startproc
.LVL39:
	.loc 1 462 5
	.loc 1 462 55 is_stmt 0
	lw	a5,pka_share_ptr
	lw	a5,132(a5)
.LVL40:
	.loc 1 463 5 is_stmt 1
	.loc 1 464 5
	.loc 1 461 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	s1,4(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 461 1
	mv	a1,a0
	.loc 1 464 53
	sb	a0,0(a5)
.LVL41:
	.loc 1 465 5 is_stmt 1
.LBB43:
	.loc 1 465 9
	.loc 1 465 17 is_stmt 0
	li	s0,0
	.loc 1 465 52 discriminator 1
	lla	s1,pka_share_tx_hid_ctl
.LVL42:
.L39:
	.loc 1 465 30 is_stmt 1 discriminator 1
	lbu	a5,49(s1)
	bgtu	a5,s0,.L40
.LBE43:
	.loc 1 468 5
	.loc 1 469 1 is_stmt 0
	lw	s0,8(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL43:
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s1,4(sp)
	.cfi_restore 9
	.loc 1 468 5
	lw	a0,g_pEmptyPktPtr
	.loc 1 469 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	.loc 1 468 5
	tail	pka_tx_buf_set_active_state
.LVL44:
.L40:
	.cfi_restore_state
.LBB44:
	.loc 1 466 9 is_stmt 1
	.loc 1 466 71 is_stmt 0
	slli	a5,s0,1
	add	a5,a5,s0
	slli	a5,a5,2
	add	a5,s1,a5
	.loc 1 466 9
	lw	a0,0(a5)
	sw	a1,0(sp)
	.loc 1 465 69 discriminator 3
	addi	s0,s0,1
.LVL45:
	.loc 1 466 9
	call	pka_tx_buf_set_active_state
.LVL46:
	.loc 1 465 69 is_stmt 1 discriminator 3
	lw	a1,0(sp)
	andi	s0,s0,0xff
.LVL47:
	j	.L39
.LBE44:
	.cfi_endproc
.LFE37:
	.size	pka_active_state_set, .-pka_active_state_set
	.section	.text.pka_share_tx_ctrl_init,"ax",@progbits
	.align	1
	.globl	pka_share_tx_ctrl_init
	.hidden	pka_share_tx_ctrl_init
	.type	pka_share_tx_ctrl_init, @function
pka_share_tx_ctrl_init:
.LFB38:
	.loc 1 482 1
	.cfi_startproc
	.loc 1 483 5
	.loc 1 482 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 483 22
	lla	s0,pka_share_ptr
	lw	a2,0(s0)
	.loc 1 482 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 483 8
	lbu	a5,62(a2)
	beq	a5,zero,.L42
	.loc 1 484 9 is_stmt 1
	.loc 1 484 36 is_stmt 0
	lhu	a5,60(a2)
	.loc 1 484 21
	sh	a5,pka_cb_type,a4
	.loc 1 485 9 is_stmt 1
	.loc 1 485 12 is_stmt 0
	li	a4,1
	bne	a5,a4,.L44
	.loc 1 487 13 is_stmt 1
	.loc 1 487 46 is_stmt 0
	lbu	a5,136(a2)
	lla	a1,pka_share_tx_hid_ctl
.LBB45:
	.loc 1 488 25
	li	a4,0
.LBE45:
	.loc 1 487 46
	sb	a5,49(a1)
	.loc 1 488 13 is_stmt 1
.LBB58:
	.loc 1 488 17
.LVL48:
.LBB46:
.LBB47:
	.loc 1 375 12 is_stmt 0
	li	a0,7
.LBE47:
.LBE46:
	.loc 1 493 58
	li	t1,1
.LVL49:
.L45:
	.loc 1 488 38 is_stmt 1 discriminator 1
	.loc 1 488 60 is_stmt 0 discriminator 1
	lbu	a5,49(a1)
	.loc 1 488 38 discriminator 1
	bgtu	a5,a4,.L46
.LBE58:
	.loc 1 496 13 is_stmt 1
	.loc 1 496 46 is_stmt 0
	sb	zero,pka_share_tx_hid_ctl+48,a4
.LVL50:
	.loc 1 497 13 is_stmt 1
	.loc 1 497 50 is_stmt 0
	sb	zero,pka_share_tx_hid_ctl+50,a4
	.loc 1 498 13 is_stmt 1
	.loc 1 498 16 is_stmt 0
	li	a4,4
	bleu	a5,a4,.L47
	.loc 1 499 17 is_stmt 1
.LBB59:
	.loc 1 499 34 discriminator 1
	.loc 1 499 110 discriminator 1
	.loc 1 499 252 discriminator 1
	li	a2,499
	lla	a1,file.0
	lla	a0,exp.1
	call	light_assert
.LVL51:
.L47:
.LBE59:
	.loc 1 499 283 discriminator 3
	.loc 1 503 13
	.loc 1 503 43 is_stmt 0
	lw	a5,0(s0)
	.loc 1 503 28
	lw	a4,112(a5)
	.loc 1 504 28
	addi	a5,a5,64
	.loc 1 503 28
	sw	a4,g_pEmptyPktPtr,a3
	.loc 1 504 13 is_stmt 1
	.loc 1 504 26 is_stmt 0
	sw	a5,g_pPkaRtInfo,a4
.LVL52:
.L44:
	.loc 1 506 9 is_stmt 1
	.loc 1 506 41 is_stmt 0
	lw	a5,0(s0)
	sb	zero,62(a5)
.L42:
	.loc 1 508 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL53:
.L46:
	.cfi_restore_state
.LBB60:
	.loc 1 489 17 is_stmt 1
	.loc 1 489 96 is_stmt 0
	addi	a5,a4,24
	slli	a5,a5,2
	add	a5,a2,a5
	lw	a3,0(a5)
	.loc 1 489 57
	slli	a5,a4,1
	add	a5,a5,a4
	slli	a5,a5,2
	add	a5,a1,a5
	sw	a3,0(a5)
	.loc 1 490 17 is_stmt 1
.LVL54:
.LBB50:
.LBB48:
	.loc 1 375 5
.LBE48:
.LBE50:
.LBB51:
.LBB52:
	.loc 1 400 12 is_stmt 0
	lbu	t0,9(a3)
.LBE52:
.LBE51:
.LBB54:
.LBB49:
	.loc 1 375 12
	sh	a0,2(a3)
.LVL55:
.LBE49:
.LBE54:
	.loc 1 491 17 is_stmt 1
.LBB55:
.LBB56:
	.loc 1 385 5
	.loc 1 385 12 is_stmt 0
	sh	a0,14(a3)
.LVL56:
.LBE56:
.LBE55:
	.loc 1 492 17 is_stmt 1
.LBB57:
.LBB53:
	.loc 1 400 5
	.loc 1 400 12 is_stmt 0
	andi	t0,t0,127
	sb	t0,9(a3)
.LVL57:
.LBE53:
.LBE57:
	.loc 1 493 17 is_stmt 1
	.loc 1 488 77 is_stmt 0 discriminator 3
	addi	a4,a4,1
.LVL58:
	.loc 1 493 58
	sb	t1,4(a5)
	.loc 1 494 17 is_stmt 1
	.loc 1 494 58 is_stmt 0
	sw	zero,8(a5)
	.loc 1 488 77 is_stmt 1 discriminator 3
	andi	a4,a4,0xff
.LVL59:
	j	.L45
.LBE60:
	.cfi_endproc
.LFE38:
	.size	pka_share_tx_ctrl_init, .-pka_share_tx_ctrl_init
	.section	.text.pka_share_updt_hid_tx_ptr,"ax",@progbits
	.align	1
	.globl	pka_share_updt_hid_tx_ptr
	.hidden	pka_share_updt_hid_tx_ptr
	.type	pka_share_updt_hid_tx_ptr, @function
pka_share_updt_hid_tx_ptr:
.LFB39:
	.loc 1 609 1
	.cfi_startproc
	.loc 1 610 5
	.loc 1 610 8 is_stmt 0
	lhu	a4,pka_cb_type
	li	a5,1
	beq	a4,a5,.L63
.L52:
	.loc 1 624 1
	ret
.L63:
.LVL60:
.LBB61:
.LBB62:
	.loc 1 614 34 is_stmt 1 discriminator 1
	.loc 1 614 56 is_stmt 0 discriminator 1
	lla	a1,pka_share_tx_hid_ctl
	lbu	a5,49(a1)
	.loc 1 614 34 discriminator 1
	beq	a5,zero,.L52
	slli	a3,a5,1
	add	a3,a3,a5
	slli	a3,a3,2
	add	a3,a1,a3
.LBE62:
	.loc 1 611 32
	mv	a5,a1
.LBB67:
	.loc 1 615 16
	li	a2,2
	j	.L57
.LVL61:
.L55:
	.loc 1 614 83 discriminator 2
	addi	a5,a5,12
.LVL62:
	.loc 1 614 34 is_stmt 1 discriminator 1
	beq	a3,a5,.L52
.LVL63:
.L57:
	.loc 1 615 13
	.loc 1 614 75 discriminator 2
	.loc 1 615 16 is_stmt 0
	lw	a4,8(a5)
	bne	a4,a2,.L55
	.loc 1 616 17 is_stmt 1
.LVL64:
.LBB63:
.LBB64:
	.loc 1 390 5
.LBE64:
.LBE63:
	.loc 1 618 21
.LBB66:
.LBB65:
	.loc 1 390 16 is_stmt 0
	lw	a4,0(a5)
	lb	a4,9(a4)
.LBE65:
.LBE66:
	.loc 1 616 33 discriminator 1
	srli	a0,a4,31
	.loc 1 616 31 discriminator 1
	sb	a0,4(a5)
	.loc 1 617 17 is_stmt 1
	.loc 1 617 20 is_stmt 0
	bge	a4,zero,.L55
	.loc 1 618 35
	sw	zero,8(a5)
	.loc 1 619 21 is_stmt 1
	.loc 1 619 57 is_stmt 0
	lbu	a4,50(a1)
	addi	a4,a4,-1
	sb	a4,50(a1)
	j	.L55
.LBE67:
.LBE61:
	.cfi_endproc
.LFE39:
	.size	pka_share_updt_hid_tx_ptr, .-pka_share_updt_hid_tx_ptr
	.globl	__umodsi3
	.globl	__modsi3
	.section	.text.pka_share_get_hid_tx_ptr,"ax",@progbits
	.align	1
	.globl	pka_share_get_hid_tx_ptr
	.hidden	pka_share_get_hid_tx_ptr
	.type	pka_share_get_hid_tx_ptr, @function
pka_share_get_hid_tx_ptr:
.LFB40:
	.loc 1 637 1 is_stmt 1
	.cfi_startproc
	.loc 1 638 5
	.loc 1 638 8 is_stmt 0
	lhu	a4,pka_cb_type
	li	a5,1
	bne	a4,a5,.L68
	.loc 1 639 9 is_stmt 1
	.loc 1 637 1 is_stmt 0
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	sw	s0,16(sp)
	sw	ra,20(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 639 33
	lla	s0,pka_share_tx_hid_ctl
	lbu	a4,50(s0)
	.loc 1 639 72
	lbu	a5,49(s0)
	.loc 1 639 33
	sw	a4,8(sp)
	.loc 1 639 72
	sw	a5,0(sp)
	.loc 1 639 12
	bgeu	a4,a5,.L69
	sw	s1,12(sp)
	.cfi_offset 9, -12
.LBB68:
	.loc 1 640 13 is_stmt 1
.LVL65:
	.loc 1 641 13
	.loc 1 642 13
	.loc 1 643 13
	.loc 1 646 13
	.loc 1 646 45 discriminator 1
	lbu	s1,48(s0)
	add	a5,a5,s1
.LVL66:
	sw	a5,4(sp)
	j	.L67
.LVL67:
.L66:
	lw	a5,4(sp)
	beq	a5,s1,.L76
.LVL68:
.L67:
	.loc 1 647 17
	.loc 1 647 87 is_stmt 0
	lw	a1,0(sp)
	mv	a0,s1
	.loc 1 646 45 discriminator 1
	addi	s1,s1,1
	.loc 1 647 87
	call	__modsi3
.LVL69:
	.loc 1 646 69 is_stmt 1 discriminator 2
	.loc 1 646 45 discriminator 1
	.loc 1 648 17
	.loc 1 648 27 is_stmt 0
	slli	a5,a0,1
	add	a5,a5,a0
	slli	a5,a5,2
	add	a5,s0,a5
	.loc 1 648 20
	lw	a3,8(a5)
	bne	a3,zero,.L66
	.loc 1 649 21 is_stmt 1
	.loc 1 650 55 is_stmt 0
	lw	a4,8(sp)
	.loc 1 652 34
	lw	a0,0(a5)
.LVL70:
	.loc 1 649 35
	li	a3,1
	.loc 1 650 55
	addi	a4,a4,1
	sb	a4,50(s0)
	.loc 1 649 35
	sw	a3,8(a5)
	.loc 1 650 21 is_stmt 1
	.loc 1 651 21
	.loc 1 651 37 is_stmt 0
	sw	a5,g_pLastGetHidTx,a4
	.loc 1 652 21 is_stmt 1
.L75:
.LBE68:
	.loc 1 658 1 is_stmt 0
	lw	ra,20(sp)
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
.LBB69:
	lw	s1,12(sp)
	.cfi_restore 9
.LBE69:
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
.LVL71:
	jr	ra
.LVL72:
.L68:
	.loc 1 657 11
	li	a0,0
	.loc 1 658 1
	ret
.L69:
	.cfi_def_cfa_offset 24
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	lw	ra,20(sp)
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	.loc 1 657 11
	li	a0,0
	.loc 1 658 1
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
	jr	ra
.LVL73:
.L76:
	.cfi_def_cfa_offset 24
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 657 11
	li	a0,0
.LVL74:
	j	.L75
	.cfi_endproc
.LFE40:
	.size	pka_share_get_hid_tx_ptr, .-pka_share_get_hid_tx_ptr
	.section	.text.pka_share_push_hid_tx_ptr,"ax",@progbits
	.align	1
	.globl	pka_share_push_hid_tx_ptr
	.hidden	pka_share_push_hid_tx_ptr
	.type	pka_share_push_hid_tx_ptr, @function
pka_share_push_hid_tx_ptr:
.LFB41:
	.loc 1 671 1 is_stmt 1
	.cfi_startproc
.LVL75:
	.loc 1 672 5
	.loc 1 672 8 is_stmt 0
	lhu	a5,pka_cb_type
	li	a4,1
	beq	a5,a4,.L79
.L77:
	.loc 1 680 1
	ret
.L79:
	.loc 1 673 9 is_stmt 1
	.loc 1 673 29 is_stmt 0
	lw	a4,g_pLastGetHidTx
	.loc 1 673 12
	lw	a3,0(a4)
	bne	a3,a0,.L77
	.loc 1 673 47 discriminator 1
	lw	a3,8(a4)
	bne	a3,a5,.L77
	.loc 1 674 13 is_stmt 1
	.loc 1 674 36 is_stmt 0
	sw	zero,8(a4)
	.loc 1 675 13 is_stmt 1
	.loc 1 675 49 is_stmt 0
	lla	a4,pka_share_tx_hid_ctl
	lbu	a5,50(a4)
	addi	a5,a5,-1
	sb	a5,50(a4)
	.loc 1 679 5 is_stmt 1
	.loc 1 680 1 is_stmt 0
	ret
	.cfi_endproc
.LFE41:
	.size	pka_share_push_hid_tx_ptr, .-pka_share_push_hid_tx_ptr
	.section	.text.pka_share_advanced_tx_prepare_rt,"ax",@progbits
	.align	1
	.globl	pka_share_advanced_tx_prepare_rt
	.hidden	pka_share_advanced_tx_prepare_rt
	.type	pka_share_advanced_tx_prepare_rt, @function
pka_share_advanced_tx_prepare_rt:
.LFB42:
	.loc 1 693 1 is_stmt 1
	.cfi_startproc
	.loc 1 695 5
.LVL76:
	.loc 1 696 5
	.loc 1 697 5
	.loc 1 698 5
	.loc 1 699 5
	.loc 1 700 5
	.loc 1 693 1 is_stmt 0
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	s0,24(sp)
	sw	ra,28(sp)
	sw	s1,20(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 700 83
	lla	s0,pka_share_tx_hid_ctl
	lbu	a2,48(s0)
	.loc 1 704 5
	addi	a0,sp,16
	.loc 1 700 83
	sw	a2,0(sp)
.LVL77:
	.loc 1 701 5 is_stmt 1
	.loc 1 704 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL78:
	.loc 1 706 5
	.loc 1 706 8 is_stmt 0
	lbu	a5,g_riscv_ccni_irq_occur
	bne	a5,zero,.L100
	.loc 1 708 9 is_stmt 1
	.loc 1 710 37 is_stmt 0
	lw	a2,0(sp)
	.loc 1 710 83
	li	a4,1
	.loc 1 708 30
	lw	a3,52(s0)
.LVL79:
	.loc 1 710 9 is_stmt 1
	.loc 1 710 37 is_stmt 0
	slli	t2,a2,1
	add	a5,t2,a2
	slli	a5,a5,2
	add	a5,s0,a5
	.loc 1 710 83
	lw	a1,8(a5)
	beq	a1,a4,.L115
	.loc 1 710 83 discriminator 2
	li	a4,0
.L82:
	.loc 1 715 41
	lla	s1,g_pPkaRtInfo
	lw	t1,0(s1)
	.loc 1 716 30
	lla	t0,g_pEmptyPktPtr
	lw	a1,0(t0)
	.loc 1 715 53
	lw	ra,20(t1)
	.loc 1 700 28
	add	a5,t2,a2
	slli	a5,a5,2
	.loc 1 715 28
	lw	a0,0(ra)
	.loc 1 700 28
	add	a5,s0,a5
.LVL80:
	.loc 1 715 9 is_stmt 1
	.loc 1 716 9
	.loc 1 716 12 is_stmt 0
	beq	a0,a1,.L116
	.loc 1 762 9 is_stmt 1
.LVL81:
	.loc 1 763 9
	.loc 1 763 53 is_stmt 0
	lw	ra,28(t1)
	.loc 1 763 28
	lw	a2,0(ra)
.LVL82:
	.loc 1 765 9 is_stmt 1
	.loc 1 765 12 is_stmt 0
	beq	a1,a2,.L117
.LVL83:
.L100:
	li	s1,0
.LVL84:
.L81:
	.loc 1 825 5 is_stmt 1
	.loc 1 825 8 is_stmt 0
	lw	a5,52(s0)
	beq	a5,zero,.L118
.L98:
	.loc 1 831 5 is_stmt 1
	lw	a0,16(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL85:
	.loc 1 833 5
	.loc 1 834 5
	.loc 1 835 1 is_stmt 0
	lw	ra,28(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,24(sp)
	.cfi_restore 8
	mv	a0,s1
	lw	s1,20(sp)
	.cfi_restore 9
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
.LVL86:
.L115:
	.cfi_restore_state
	.loc 1 710 83 discriminator 1
	lw	a4,0(a5)
	j	.L82
.LVL87:
.L117:
	.loc 1 762 28
	lw	t1,24(t1)
.LVL88:
	lw	t1,0(t1)
	.loc 1 766 13 is_stmt 1
	.loc 1 766 16 is_stmt 0
	beq	a3,zero,.L105
	.loc 1 767 46
	sw	a3,0(ra)
.LVL89:
	sw	a5,12(sp)
	sw	t1,8(sp)
	sw	a0,4(sp)
	.loc 1 767 17 is_stmt 1
	.loc 1 767 46 is_stmt 0
	sw	a3,0(sp)
.LVL90:
	.loc 1 768 17 is_stmt 1
	.loc 1 770 17
	.loc 1 770 48 is_stmt 0
	sw	zero,pka_share_tx_hid_ctl+52,a4
.LVL91:
	.loc 1 771 17 is_stmt 1
	call	hid_express_dbg_inc_pka_acl_cnt
.LVL92:
	.loc 1 768 34 is_stmt 0
	lw	a3,0(sp)
	lw	a0,4(sp)
	.loc 1 814 31
	lla	t0,g_pEmptyPktPtr
	lw	a2,0(t0)
	lw	t1,8(sp)
	lw	a5,12(sp)
	.loc 1 768 34
	mv	t2,a3
	li	s1,0
	mv	a3,a0
.LVL93:
.L91:
	.loc 1 810 13 is_stmt 1
.LBB70:
.LBB71:
	.loc 1 400 5
	.loc 1 400 12 is_stmt 0
	lbu	a4,9(t2)
	andi	a4,a4,127
	sb	a4,9(t2)
.LVL94:
.L89:
.LBE71:
.LBE70:
	.loc 1 814 9 is_stmt 1
	.loc 1 814 12 is_stmt 0
	bne	t1,a2,.L81
	.loc 1 814 50 discriminator 1
	bne	a3,t1,.L81
	.loc 1 815 50
	bne	t2,a3,.L81
	.loc 1 816 50
	lw	a3,8(a5)
	li	a4,2
	bne	a3,a4,.L81
	.loc 1 818 13 is_stmt 1
	.loc 1 818 40 is_stmt 0
	lw	a4,0(a5)
.LVL95:
.LBB72:
.LBB73:
	.loc 1 395 5 is_stmt 1
	.loc 1 395 12 is_stmt 0
	lbu	a5,9(a4)
.LVL96:
	ori	a5,a5,-128
	sb	a5,9(a4)
.LVL97:
.LBE73:
.LBE72:
	.loc 1 819 13 is_stmt 1
	call	hid_express_dbg_inc_pka_hid_drop_cnt
.LVL98:
	j	.L81
.LVL99:
.L118:
	.loc 1 826 9
	li	a0,4
	call	share_buffer_hw_semaphore_take
.LVL100:
	.loc 1 827 9
	.loc 1 827 55 is_stmt 0
	lw	a5,g_pPkaRtInfo
	lw	a5,16(a5)
	.loc 1 829 9
	li	a0,4
	.loc 1 827 42
	lw	a4,0(a5)
	.loc 1 827 40
	sw	a4,52(s0)
	.loc 1 828 9 is_stmt 1
	.loc 1 828 34 is_stmt 0
	sw	zero,0(a5)
	.loc 1 829 9 is_stmt 1
	call	share_buffer_hw_semaphore_give
.LVL101:
	j	.L98
.LVL102:
.L116:
	.loc 1 717 13
	.loc 1 717 16 is_stmt 0
	beq	a3,zero,.L84
	.loc 1 718 46
	sw	a3,0(ra)
	sw	a4,8(sp)
	sw	a5,4(sp)
	.loc 1 718 17 is_stmt 1
	.loc 1 718 46 is_stmt 0
	sw	a3,0(sp)
.LVL103:
	.loc 1 719 17 is_stmt 1
	.loc 1 721 17
	.loc 1 721 71 is_stmt 0
	sw	zero,pka_share_tx_hid_ctl+52,a2
.LVL104:
	.loc 1 722 17 is_stmt 1
	call	hid_express_dbg_inc_pka_acl_cnt
.LVL105:
.LBB74:
.LBB75:
	.loc 1 400 12 is_stmt 0
	lw	a3,0(sp)
.LBE75:
.LBE74:
	.loc 1 762 41
	lw	a0,0(s1)
	.loc 1 765 30
	lla	t0,g_pEmptyPktPtr
.LBB80:
.LBB76:
	.loc 1 400 12
	lbu	a1,9(a3)
.LBE76:
.LBE80:
	.loc 1 765 30
	lw	a2,0(t0)
.LVL106:
	.loc 1 758 13 is_stmt 1
.LBB81:
.LBB77:
	.loc 1 400 5
.LBE77:
.LBE81:
	.loc 1 765 12 is_stmt 0
	lw	a5,4(sp)
.LBB82:
.LBB78:
	.loc 1 400 12
	andi	a1,a1,127
	sb	a1,9(a3)
.LVL107:
.LBE78:
.LBE82:
	.loc 1 762 9 is_stmt 1
	.loc 1 763 53 is_stmt 0
	lw	ra,28(a0)
	.loc 1 762 28
	lw	a1,24(a0)
	.loc 1 765 12
	lw	a4,8(sp)
	.loc 1 763 28
	lw	t2,0(ra)
	.loc 1 762 28
	lw	t1,0(a1)
.LVL108:
	.loc 1 763 9 is_stmt 1
	.loc 1 765 9
	.loc 1 765 12 is_stmt 0
	beq	t2,a2,.L102
	li	a0,7
.LVL109:
.L86:
	.loc 1 834 36
	addi	s1,a0,-7
	j	.L89
.LVL110:
.L84:
	.loc 1 724 17 is_stmt 1
	.loc 1 724 20 is_stmt 0
	beq	a4,zero,.L103
.LVL111:
.L88:
	.loc 1 725 21 is_stmt 1
	.loc 1 726 25
	.loc 1 726 54 is_stmt 0
	sw	a4,0(ra)
	.loc 1 728 58 is_stmt 1 discriminator 1
	.loc 1 728 54 is_stmt 0 discriminator 1
	lw	a3,0(s1)
	lw	ra,20(a3)
	.loc 1 728 58 discriminator 1
	lw	a3,0(ra)
	bne	a3,a4,.L88
	.loc 1 743 21 is_stmt 1
.LVL112:
	.loc 1 744 21
	.loc 1 747 21
	.loc 1 750 51 is_stmt 0
	lbu	a0,48(s0)
	.loc 1 747 35
	add	a3,t2,a2
	.loc 1 751 52
	lbu	a1,49(s0)
	.loc 1 747 35
	slli	a3,a3,2
	li	a2,2
	add	a3,s0,a3
	.loc 1 750 51
	addi	a0,a0,1
	.loc 1 747 35
	sw	a2,8(a3)
	.loc 1 750 21 is_stmt 1
	.loc 1 751 21
	.loc 1 751 52 is_stmt 0
	andi	a0,a0,0xff
	sw	a4,8(sp)
.LVL113:
	sw	a5,4(sp)
	call	__umodsi3
.LVL114:
	.loc 1 754 46
	li	a3,1108672512
	.loc 1 751 52
	sb	a0,48(s0)
	.loc 1 754 21 is_stmt 1
	.loc 1 754 46 is_stmt 0
	lw	a0,536(a3)
.LVL115:
	sw	a0,0(sp)
.LVL116:
	.loc 1 755 21 is_stmt 1
	call	hid_express_dbg_inc_pka_hid_cnt
.LVL117:
	.loc 1 743 38 is_stmt 0
	lw	a4,8(sp)
	.loc 1 765 30
	lla	t0,g_pEmptyPktPtr
	.loc 1 762 41
	lw	t1,0(s1)
	.loc 1 765 30
	lw	a2,0(t0)
	lw	a0,0(sp)
	lw	a5,4(sp)
	.loc 1 743 38
	mv	a3,a4
.LVL118:
.L87:
	.loc 1 758 13 is_stmt 1
.LBB83:
.LBB79:
	.loc 1 400 5
	.loc 1 400 12 is_stmt 0
	lbu	a4,9(a3)
	andi	a4,a4,127
	sb	a4,9(a3)
.LVL119:
.LBE79:
.LBE83:
	.loc 1 762 9 is_stmt 1
	.loc 1 763 53 is_stmt 0
	lw	ra,28(t1)
	.loc 1 762 28
	lw	a4,24(t1)
	.loc 1 763 28
	lw	t2,0(ra)
	.loc 1 762 28
	lw	t1,0(a4)
.LVL120:
	.loc 1 763 9 is_stmt 1
	.loc 1 765 9
	.loc 1 765 12 is_stmt 0
	bne	a2,t2,.L86
	mv	a1,a2
.LVL121:
.L99:
	.loc 1 775 21 is_stmt 1
	.loc 1 775 76 is_stmt 0
	lbu	t2,48(s0)
	.loc 1 776 24
	li	a4,1
	.loc 1 775 28
	slli	a5,t2,1
	add	a5,a5,t2
	slli	a5,a5,2
	add	a5,s0,a5
.LVL122:
	.loc 1 776 21 is_stmt 1
	.loc 1 776 24 is_stmt 0
	lw	t2,8(a5)
	beq	t2,a4,.L93
.LVL123:
.L114:
	.loc 1 763 26
	mv	t2,a2
	.loc 1 834 36
	addi	s1,a0,-7
	mv	a2,a1
	j	.L91
.LVL124:
.L103:
	mv	a3,a0
.LVL125:
	.loc 1 715 26
	mv	a2,a0
	.loc 1 695 14
	li	a0,7
.LVL126:
	j	.L87
.LVL127:
.L105:
	mv	a3,a0
.LVL128:
.L85:
	.loc 1 774 17 is_stmt 1
	li	a0,7
	.loc 1 774 20 is_stmt 0
	beq	a4,zero,.L99
.LVL129:
.L92:
	.loc 1 781 49 discriminator 1
	beq	a3,a4,.L114
	.loc 1 782 62
	beq	t1,a4,.L114
.L95:
	.loc 1 784 21 is_stmt 1
	.loc 1 785 25
	.loc 1 785 54 is_stmt 0
	sw	a4,0(ra)
	.loc 1 787 59 is_stmt 1 discriminator 1
	.loc 1 787 55 is_stmt 0 discriminator 1
	lw	a2,0(s1)
	lw	ra,28(a2)
	.loc 1 787 59 discriminator 1
	lw	a2,0(ra)
	bne	a2,a4,.L95
	.loc 1 789 21 is_stmt 1
.LVL130:
	.loc 1 790 21
	.loc 1 790 47 is_stmt 0
	lw	a2,pka_share_ptr
	lw	a1,128(a2)
	.loc 1 790 65
	li	a2,2
	sw	a4,12(sp)
.LVL131:
	sb	a2,0(a1)
	.loc 1 799 21 is_stmt 1
	.loc 1 799 35 is_stmt 0
	sw	a2,8(a5)
	.loc 1 802 51
	lbu	a0,48(s0)
	.loc 1 803 52
	lbu	a1,49(s0)
	sw	a3,8(sp)
	.loc 1 802 51
	addi	a0,a0,1
	.loc 1 803 52
	andi	a0,a0,0xff
	sw	t1,4(sp)
	.loc 1 799 35
	sw	a5,0(sp)
	.loc 1 802 21 is_stmt 1
	.loc 1 803 21
	.loc 1 803 52 is_stmt 0
	call	__umodsi3
.LVL132:
	.loc 1 806 46
	li	a2,1108672512
	.loc 1 803 52
	sb	a0,48(s0)
	.loc 1 806 21 is_stmt 1
	.loc 1 806 46 is_stmt 0
	lw	s1,536(a2)
.LVL133:
	.loc 1 807 21 is_stmt 1
	call	hid_express_dbg_inc_pka_hid_cnt
.LVL134:
	.loc 1 789 38 is_stmt 0
	lw	a4,12(sp)
	.loc 1 814 31
	lla	t0,g_pEmptyPktPtr
	lw	a2,0(t0)
	.loc 1 789 38
	lw	a3,8(sp)
	lw	t1,4(sp)
	lw	a5,0(sp)
	.loc 1 834 36
	addi	s1,s1,-7
.LVL135:
	.loc 1 789 38
	mv	t2,a4
	j	.L91
.LVL136:
.L102:
	.loc 1 765 12
	mv	a1,a2
	j	.L85
.LVL137:
.L93:
	.loc 1 777 25 is_stmt 1
	.loc 1 777 44 is_stmt 0
	lw	a4,0(a5)
.LVL138:
	.loc 1 781 17 is_stmt 1
	.loc 1 781 20 is_stmt 0
	bne	a4,zero,.L92
	j	.L114
	.cfi_endproc
.LFE42:
	.size	pka_share_advanced_tx_prepare_rt, .-pka_share_advanced_tx_prepare_rt
	.section	.text.pka_share_tx_forward_prepare_rtt0,"ax",@progbits
	.align	1
	.globl	pka_share_tx_forward_prepare_rtt0
	.hidden	pka_share_tx_forward_prepare_rtt0
	.type	pka_share_tx_forward_prepare_rtt0, @function
pka_share_tx_forward_prepare_rtt0:
.LFB43:
	.loc 1 961 1 is_stmt 1
	.cfi_startproc
	.loc 1 963 5
	.loc 1 961 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 963 62
	lla	s0,pka_share_ptr
	lw	a5,0(s0)
	.loc 1 961 1
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 963 43
	lw	a4,84(a5)
	.loc 1 963 87
	lw	a5,100(a5)
	.loc 1 963 47
	sw	a5,0(a4)
	.loc 1 964 5 is_stmt 1
	.loc 1 964 62 is_stmt 0
	lw	a5,0(s0)
	.loc 1 964 43
	lw	a4,92(a5)
	.loc 1 964 87
	lw	a5,108(a5)
	.loc 1 964 47
	sw	a5,0(a4)
	.loc 1 965 5 is_stmt 1
	.loc 1 965 41 is_stmt 0
	lw	s1,0(s0)
	.loc 1 965 9
	lw	a5,76(s1)
	lw	a0,0(a5)
	call	pka_tx_buf_is_hid
.LVL139:
	lw	a5,80(s1)
	.loc 1 965 8 discriminator 1
	beq	a0,zero,.L120
	.loc 1 966 9 is_stmt 1
	.loc 1 966 91 is_stmt 0
	lw	a4,96(s1)
	.loc 1 966 51
	sw	a4,0(a5)
	.loc 1 967 9 is_stmt 1
	.loc 1 967 66 is_stmt 0
	lw	a5,0(s0)
	.loc 1 967 47
	lw	a4,88(a5)
	.loc 1 967 91
	lw	a5,104(a5)
.L123:
	.loc 1 985 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	.loc 1 970 51
	sw	a5,0(a4)
	.loc 1 985 1
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.L120:
	.cfi_restore_state
	.loc 1 969 9 is_stmt 1
	.loc 1 969 91 is_stmt 0
	lw	a4,100(s1)
	.loc 1 969 51
	sw	a4,0(a5)
	.loc 1 970 9 is_stmt 1
	.loc 1 970 66 is_stmt 0
	lw	a5,0(s0)
	.loc 1 970 47
	lw	a4,88(a5)
	.loc 1 970 91
	lw	a5,108(a5)
	j	.L123
	.cfi_endproc
.LFE43:
	.size	pka_share_tx_forward_prepare_rtt0, .-pka_share_tx_forward_prepare_rtt0
	.section	.text.pka_share_get_current_report_rate,"ax",@progbits
	.align	1
	.globl	pka_share_get_current_report_rate
	.hidden	pka_share_get_current_report_rate
	.type	pka_share_get_current_report_rate, @function
pka_share_get_current_report_rate:
.LFB44:
	.loc 1 987 1 is_stmt 1
	.cfi_startproc
	.loc 1 993 5
	.loc 1 993 52 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 993 13
	lbu	a0,138(a5)
	.loc 1 994 8
	li	a5,6
	.loc 1 993 13
	addi	a0,a0,-1
	andi	a0,a0,0xff
.LVL140:
	.loc 1 994 5 is_stmt 1
	.loc 1 994 8 is_stmt 0
	bleu	a0,a5,.L125
	.loc 1 995 21
	li	a0,15
.LVL141:
.L125:
	.loc 1 997 5 is_stmt 1
	.loc 1 998 1 is_stmt 0
	ret
	.cfi_endproc
.LFE44:
	.size	pka_share_get_current_report_rate, .-pka_share_get_current_report_rate
	.section	.text.pka_share_get_current_max_pdu_len,"ax",@progbits
	.align	1
	.globl	pka_share_get_current_max_pdu_len
	.hidden	pka_share_get_current_max_pdu_len
	.type	pka_share_get_current_max_pdu_len, @function
pka_share_get_current_max_pdu_len:
.LFB45:
	.loc 1 1001 1 is_stmt 1
	.cfi_startproc
	.loc 1 1003 5
	.loc 1 1003 23 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 1008 12
	li	a0,0
	.loc 1 1003 8
	beq	a5,zero,.L128
	.loc 1 1004 9 is_stmt 1
	.loc 1 1004 38 is_stmt 0
	lw	a5,144(a5)
	.loc 1 1004 12
	beq	a5,zero,.L128
	.loc 1 1005 13 is_stmt 1
	.loc 1 1005 20 is_stmt 0
	lbu	a0,0(a5)
.L128:
	.loc 1 1009 1
	ret
	.cfi_endproc
.LFE45:
	.size	pka_share_get_current_max_pdu_len, .-pka_share_get_current_max_pdu_len
	.hidden	g_pLastGetHidTx
	.globl	g_pLastGetHidTx
	.section	.sbss.g_pLastGetHidTx,"aw",@nobits
	.align	2
	.type	g_pLastGetHidTx, @object
	.size	g_pLastGetHidTx, 4
g_pLastGetHidTx:
	.zero	4
	.section	.log_string,"a"
	.align	2
	.type	file.0, @object
	.size	file.0, 67
file.0:
	.string	"/workdir/airoha/common/middleware/airoha/pka_share/src/pka_share.c"
	.align	2
	.type	exp.1, @object
	.size	exp.1, 2
exp.1:
	.string	"0"
	.align	2
	.type	file.2, @object
	.size	file.2, 67
file.2:
	.string	"/workdir/airoha/common/middleware/airoha/pka_share/src/pka_share.c"
	.align	2
	.type	exp.3, @object
	.size	exp.3, 2
exp.3:
	.string	"0"
	.align	2
	.type	file.4, @object
	.size	file.4, 67
file.4:
	.string	"/workdir/airoha/common/middleware/airoha/pka_share/src/pka_share.c"
	.align	2
	.type	exp.5, @object
	.size	exp.5, 2
exp.5:
	.string	"0"
	.hidden	g_pEmptyPktPtr
	.globl	g_pEmptyPktPtr
	.section	.sbss.g_pEmptyPktPtr,"aw",@nobits
	.align	2
	.type	g_pEmptyPktPtr, @object
	.size	g_pEmptyPktPtr, 4
g_pEmptyPktPtr:
	.zero	4
	.hidden	pka_cb_type
	.globl	pka_cb_type
	.section	.sbss.pka_cb_type,"aw",@nobits
	.align	1
	.type	pka_cb_type, @object
	.size	pka_cb_type, 2
pka_cb_type:
	.zero	2
	.hidden	g_pPkaRtInfo
	.globl	g_pPkaRtInfo
	.section	.sbss.g_pPkaRtInfo,"aw",@nobits
	.align	2
	.type	g_pPkaRtInfo, @object
	.size	g_pPkaRtInfo, 4
g_pPkaRtInfo:
	.zero	4
	.hidden	pka_share_tx_hid_ctl
	.globl	pka_share_tx_hid_ctl
	.section	.bss.pka_share_tx_hid_ctl,"aw",@nobits
	.align	2
	.type	pka_share_tx_hid_ctl, @object
	.size	pka_share_tx_hid_ctl, 56
pka_share_tx_hid_ctl:
	.zero	56
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpt.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 5 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_hw_semaphore.h"
	.file 6 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.file 7 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_eint_internal.h"
	.file 8 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_cross_core_config.h"
	.file 9 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 10 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 11 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 12 "/workdir/airoha/risc-v/kernel/service/exception_handler/inc/exception_handler.h"
	.file 13 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x148b
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x3b
	.4byte	.LASF319
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL46
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
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x6
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x6
	.byte	0x1
	.byte	0x6
	.4byte	.LASF6
	.uleb128 0x6
	.byte	0x2
	.byte	0x5
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
	.uleb128 0x3c
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x6
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x3d
	.byte	0x4
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x12
	.4byte	0x75
	.uleb128 0x8
	.4byte	0x7c
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x34
	.uleb128 0x17
	.4byte	0x86
	.uleb128 0x12
	.4byte	0x92
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x3b
	.uleb128 0x3
	.4byte	.LASF15
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x17
	.4byte	0xa8
	.uleb128 0x12
	.4byte	0xb4
	.uleb128 0x3e
	.4byte	.LASF320
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0xd
	.2byte	0x128
	.byte	0x11
	.4byte	0x144
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x1f
	.byte	0
	.uleb128 0x9
	.4byte	0x97
	.4byte	0x154
	.uleb128 0xa
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x12
	.4byte	0x144
	.uleb128 0x17
	.4byte	0x154
	.uleb128 0xb
	.byte	0x4
	.byte	0x3
	.byte	0x36
	.4byte	0x19a
	.uleb128 0x2b
	.string	"EN"
	.byte	0x3
	.byte	0x37
	.byte	0x1e
	.4byte	0x92
	.byte	0
	.uleb128 0x2
	.4byte	.LASF35
	.byte	0x3
	.byte	0x38
	.byte	0x1e
	.4byte	0x92
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0x3
	.byte	0x39
	.byte	0x1e
	.4byte	0x92
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF37
	.byte	0x3
	.byte	0x3a
	.byte	0x24
	.4byte	0x159
	.byte	0x3
	.byte	0
	.uleb128 0x2c
	.byte	0x4
	.byte	0x3
	.byte	0x35
	.byte	0x5
	.4byte	0x1bc
	.uleb128 0x1a
	.4byte	.LASF38
	.byte	0x3
	.byte	0x3b
	.byte	0xb
	.4byte	0x15e
	.uleb128 0x1a
	.4byte	.LASF39
	.byte	0x3
	.byte	0x3c
	.byte	0x1b
	.4byte	0xb4
	.byte	0
	.uleb128 0xb
	.byte	0x20
	.byte	0x3
	.byte	0x34
	.4byte	0x22d
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x3
	.byte	0x3d
	.byte	0x7
	.4byte	0x19a
	.byte	0
	.uleb128 0x2
	.4byte	.LASF41
	.byte	0x3
	.byte	0x3e
	.byte	0x17
	.4byte	0xb4
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF42
	.byte	0x3
	.byte	0x3f
	.byte	0x17
	.4byte	0xb4
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF43
	.byte	0x3
	.byte	0x40
	.byte	0x17
	.4byte	0xb4
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF44
	.byte	0x3
	.byte	0x41
	.byte	0x1d
	.4byte	0xb9
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF45
	.byte	0x3
	.byte	0x42
	.byte	0x17
	.4byte	0xb4
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x3
	.byte	0x43
	.byte	0x17
	.4byte	0xb4
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x3
	.byte	0x44
	.byte	0x17
	.4byte	0xb4
	.byte	0x1c
	.byte	0
	.uleb128 0x3
	.4byte	.LASF48
	.byte	0x3
	.byte	0x45
	.byte	0x3
	.4byte	0x1bc
	.uleb128 0x3f
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x4
	.2byte	0x407
	.byte	0xe
	.4byte	0x39f
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x38
	.byte	0
	.uleb128 0xe
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0xb6
	.byte	0xe
	.4byte	0x473
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x20
	.byte	0
	.uleb128 0x3
	.4byte	.LASF139
	.byte	0x5
	.byte	0xfa
	.byte	0x3
	.4byte	0x39f
	.uleb128 0xe
	.byte	0x5
	.4byte	0x65
	.byte	0x5
	.byte	0xfe
	.byte	0xe
	.4byte	0x4a5
	.uleb128 0x1b
	.4byte	.LASF140
	.sleb128 -3
	.uleb128 0x1b
	.4byte	.LASF141
	.sleb128 -2
	.uleb128 0x1b
	.4byte	.LASF142
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF144
	.byte	0x5
	.byte	0x3
	.4byte	0x47f
	.uleb128 0xe
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0x6e
	.byte	0xe
	.4byte	0x4d6
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
	.byte	0
	.uleb128 0x3
	.4byte	.LASF149
	.byte	0x6
	.byte	0x74
	.byte	0x3
	.4byte	0x4b0
	.uleb128 0xe
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0x76
	.byte	0xe
	.4byte	0x4fc
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF152
	.byte	0x6
	.byte	0x79
	.byte	0x3
	.4byte	0x4e2
	.uleb128 0xe
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0x85
	.byte	0xe
	.4byte	0x528
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF156
	.byte	0x6
	.byte	0x89
	.byte	0x3
	.4byte	0x508
	.uleb128 0x2d
	.4byte	.LASF161
	.byte	0x8
	.byte	0x8b
	.4byte	0x55a
	.uleb128 0x2
	.4byte	.LASF157
	.byte	0x6
	.byte	0x8c
	.byte	0x22
	.4byte	0x55a
	.byte	0
	.uleb128 0x2
	.4byte	.LASF158
	.byte	0x6
	.byte	0x8d
	.byte	0x22
	.4byte	0x55a
	.byte	0x4
	.byte	0
	.uleb128 0x8
	.4byte	0x534
	.uleb128 0x3
	.4byte	.LASF159
	.byte	0x6
	.byte	0x8f
	.byte	0x3
	.4byte	0x534
	.uleb128 0x3
	.4byte	.LASF160
	.byte	0x6
	.byte	0x90
	.byte	0x1e
	.4byte	0x55f
	.uleb128 0x2d
	.4byte	.LASF162
	.byte	0xc
	.byte	0x94
	.4byte	0x59d
	.uleb128 0x2
	.4byte	.LASF163
	.byte	0x6
	.byte	0x96
	.byte	0x1a
	.4byte	0x56b
	.byte	0
	.uleb128 0x2b
	.string	"noB"
	.byte	0x6
	.byte	0x98
	.byte	0xe
	.4byte	0xa8
	.byte	0x8
	.byte	0
	.uleb128 0x3
	.4byte	.LASF164
	.byte	0x6
	.byte	0x99
	.byte	0x3
	.4byte	0x577
	.uleb128 0xb
	.byte	0xc
	.byte	0x6
	.byte	0x9b
	.4byte	0x5d9
	.uleb128 0x2
	.4byte	.LASF165
	.byte	0x6
	.byte	0x9c
	.byte	0xf
	.4byte	0x5d9
	.byte	0
	.uleb128 0x2
	.4byte	.LASF166
	.byte	0x6
	.byte	0x9d
	.byte	0xf
	.4byte	0x5d9
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF167
	.byte	0x6
	.byte	0x9e
	.byte	0xf
	.4byte	0x5de
	.byte	0x8
	.byte	0
	.uleb128 0x8
	.4byte	0xa8
	.uleb128 0x8
	.4byte	0x9c
	.uleb128 0x3
	.4byte	.LASF168
	.byte	0x6
	.byte	0x9f
	.byte	0x3
	.4byte	0x5a9
	.uleb128 0xb
	.byte	0x18
	.byte	0x6
	.byte	0xa1
	.4byte	0x62c
	.uleb128 0x2
	.4byte	.LASF169
	.byte	0x6
	.byte	0xa2
	.byte	0x1e
	.4byte	0x5e3
	.byte	0
	.uleb128 0x2
	.4byte	.LASF170
	.byte	0x6
	.byte	0xa3
	.byte	0xc
	.4byte	0x62c
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF171
	.byte	0x6
	.byte	0xa4
	.byte	0xc
	.4byte	0x62c
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF172
	.byte	0x6
	.byte	0xa5
	.byte	0xe
	.4byte	0x631
	.byte	0x14
	.byte	0
	.uleb128 0x8
	.4byte	0x73
	.uleb128 0x8
	.4byte	0x86
	.uleb128 0x3
	.4byte	.LASF173
	.byte	0x6
	.byte	0xa8
	.byte	0x3
	.4byte	0x5ef
	.uleb128 0xb
	.byte	0x54
	.byte	0x6
	.byte	0xaa
	.4byte	0x71b
	.uleb128 0x2
	.4byte	.LASF169
	.byte	0x6
	.byte	0xab
	.byte	0x1e
	.4byte	0x5e3
	.byte	0
	.uleb128 0x2
	.4byte	.LASF174
	.byte	0x6
	.byte	0xac
	.byte	0xc
	.4byte	0x62c
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF175
	.byte	0x6
	.byte	0xad
	.byte	0xc
	.4byte	0x62c
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF176
	.byte	0x6
	.byte	0xae
	.byte	0xc
	.4byte	0x71b
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF177
	.byte	0x6
	.byte	0xaf
	.byte	0xb
	.4byte	0x72b
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF178
	.byte	0x6
	.byte	0xb0
	.byte	0xb
	.4byte	0x73
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF179
	.byte	0x6
	.byte	0xb1
	.byte	0xe
	.4byte	0x631
	.byte	0x34
	.uleb128 0x2
	.4byte	.LASF180
	.byte	0x6
	.byte	0xb2
	.byte	0xf
	.4byte	0x5d9
	.byte	0x38
	.uleb128 0x2
	.4byte	.LASF181
	.byte	0x6
	.byte	0xb3
	.byte	0xf
	.4byte	0x5de
	.byte	0x3c
	.uleb128 0x2
	.4byte	.LASF182
	.byte	0x6
	.byte	0xb4
	.byte	0xe
	.4byte	0x631
	.byte	0x40
	.uleb128 0x2
	.4byte	.LASF183
	.byte	0x6
	.byte	0xb5
	.byte	0xf
	.4byte	0x5de
	.byte	0x44
	.uleb128 0x2
	.4byte	.LASF184
	.byte	0x6
	.byte	0xb6
	.byte	0xd
	.4byte	0x86
	.byte	0x48
	.uleb128 0x2
	.4byte	.LASF185
	.byte	0x6
	.byte	0xb7
	.byte	0xd
	.4byte	0x86
	.byte	0x49
	.uleb128 0x2
	.4byte	.LASF186
	.byte	0x6
	.byte	0xb8
	.byte	0xd
	.4byte	0x86
	.byte	0x4a
	.uleb128 0x2
	.4byte	.LASF187
	.byte	0x6
	.byte	0xb9
	.byte	0xe
	.4byte	0x9c
	.byte	0x4c
	.uleb128 0x2
	.4byte	.LASF188
	.byte	0x6
	.byte	0xba
	.byte	0xe
	.4byte	0x631
	.byte	0x50
	.byte	0
	.uleb128 0x9
	.4byte	0x62c
	.4byte	0x72b
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x9
	.4byte	0x73
	.4byte	0x73b
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF189
	.byte	0x6
	.byte	0xbb
	.byte	0x3
	.4byte	0x642
	.uleb128 0x3
	.4byte	.LASF190
	.byte	0x6
	.byte	0xbb
	.byte	0x1a
	.4byte	0x753
	.uleb128 0x8
	.4byte	0x642
	.uleb128 0xb
	.byte	0x34
	.byte	0x6
	.byte	0xbd
	.4byte	0x795
	.uleb128 0x2
	.4byte	.LASF169
	.byte	0x6
	.byte	0xbe
	.byte	0x1e
	.4byte	0x5e3
	.byte	0
	.uleb128 0x2
	.4byte	.LASF174
	.byte	0x6
	.byte	0xbf
	.byte	0xc
	.4byte	0x62c
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF176
	.byte	0x6
	.byte	0xc0
	.byte	0xc
	.4byte	0x795
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF177
	.byte	0x6
	.byte	0xc1
	.byte	0xb
	.4byte	0x7a5
	.byte	0x20
	.byte	0
	.uleb128 0x9
	.4byte	0x62c
	.4byte	0x7a5
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x9
	.4byte	0x73
	.4byte	0x7b5
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF191
	.byte	0x6
	.byte	0xc2
	.byte	0x3
	.4byte	0x758
	.uleb128 0x2c
	.byte	0x54
	.byte	0x6
	.byte	0xc4
	.byte	0x9
	.4byte	0x7f6
	.uleb128 0x1d
	.string	"le"
	.byte	0xc5
	.byte	0x1a
	.4byte	0x636
	.uleb128 0x1d
	.string	"rt"
	.byte	0xc6
	.byte	0x1a
	.4byte	0x73b
	.uleb128 0x1d
	.string	"rtt"
	.byte	0xc7
	.byte	0x1b
	.4byte	0x7b5
	.uleb128 0x1a
	.4byte	.LASF169
	.byte	0x6
	.byte	0xc8
	.byte	0x1e
	.4byte	0x5e3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF192
	.byte	0x6
	.byte	0xc9
	.byte	0x3
	.4byte	0x7c1
	.uleb128 0xb
	.byte	0x94
	.byte	0x6
	.byte	0xcb
	.4byte	0x8c1
	.uleb128 0x2
	.4byte	.LASF193
	.byte	0x6
	.byte	0xcc
	.byte	0x18
	.4byte	0x4fc
	.byte	0
	.uleb128 0x2
	.4byte	.LASF194
	.byte	0x6
	.byte	0xcf
	.byte	0x14
	.4byte	0x59d
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF195
	.byte	0x6
	.byte	0xd0
	.byte	0x14
	.4byte	0x59d
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF196
	.byte	0x6
	.byte	0xd1
	.byte	0x14
	.4byte	0x59d
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF197
	.byte	0x6
	.byte	0xd2
	.byte	0xe
	.4byte	0x631
	.byte	0x28
	.uleb128 0x2
	.4byte	.LASF198
	.byte	0x6
	.byte	0xd3
	.byte	0xe
	.4byte	0x9c
	.byte	0x2c
	.uleb128 0x2
	.4byte	.LASF199
	.byte	0x6
	.byte	0xd4
	.byte	0xe
	.4byte	0x9c
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF200
	.byte	0x6
	.byte	0xd7
	.byte	0xe
	.4byte	0x631
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF201
	.byte	0x6
	.byte	0xd8
	.byte	0xe
	.4byte	0x631
	.byte	0x34
	.uleb128 0x2
	.4byte	.LASF202
	.byte	0x6
	.byte	0xd9
	.byte	0xe
	.4byte	0x9c
	.byte	0x38
	.uleb128 0x2
	.4byte	.LASF203
	.byte	0x6
	.byte	0xda
	.byte	0xe
	.4byte	0x9c
	.byte	0x3a
	.uleb128 0x2
	.4byte	.LASF204
	.byte	0x6
	.byte	0xdb
	.byte	0xe
	.4byte	0x9c
	.byte	0x3c
	.uleb128 0x2
	.4byte	.LASF205
	.byte	0x6
	.byte	0xdc
	.byte	0xd
	.4byte	0x86
	.byte	0x3e
	.uleb128 0x2
	.4byte	.LASF206
	.byte	0x6
	.byte	0xdf
	.byte	0x17
	.4byte	0x7f6
	.byte	0x40
	.byte	0
	.uleb128 0x3
	.4byte	.LASF207
	.byte	0x6
	.byte	0xe0
	.byte	0x3
	.4byte	0x802
	.uleb128 0xb
	.byte	0xc
	.byte	0x6
	.byte	0xf6
	.4byte	0x8fd
	.uleb128 0x2
	.4byte	.LASF208
	.byte	0x6
	.byte	0xf8
	.byte	0xc
	.4byte	0x73
	.byte	0
	.uleb128 0x2
	.4byte	.LASF209
	.byte	0x6
	.byte	0xf9
	.byte	0xb
	.4byte	0x8fd
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF210
	.byte	0x6
	.byte	0xfa
	.byte	0x25
	.4byte	0x528
	.byte	0x8
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.byte	0x2
	.4byte	.LASF211
	.uleb128 0x3
	.4byte	.LASF212
	.byte	0x6
	.byte	0xfb
	.byte	0x3
	.4byte	0x8cd
	.uleb128 0x3
	.4byte	.LASF213
	.byte	0x6
	.byte	0xfb
	.byte	0x18
	.4byte	0x91c
	.uleb128 0x8
	.4byte	0x8cd
	.uleb128 0xb
	.byte	0x38
	.byte	0x6
	.byte	0xfd
	.4byte	0x96b
	.uleb128 0x2
	.4byte	.LASF214
	.byte	0x6
	.byte	0xfe
	.byte	0x18
	.4byte	0x96b
	.byte	0
	.uleb128 0x2
	.4byte	.LASF215
	.byte	0x6
	.byte	0xff
	.byte	0xd
	.4byte	0x86
	.byte	0x30
	.uleb128 0x1e
	.4byte	.LASF216
	.2byte	0x100
	.byte	0xd
	.4byte	0x86
	.byte	0x31
	.uleb128 0x1e
	.4byte	.LASF217
	.2byte	0x101
	.byte	0xd
	.4byte	0x86
	.byte	0x32
	.uleb128 0x1e
	.4byte	.LASF218
	.2byte	0x102
	.byte	0xb
	.4byte	0x73
	.byte	0x34
	.byte	0
	.uleb128 0x9
	.4byte	0x904
	.4byte	0x97b
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF219
	.byte	0x6
	.byte	0x3
	.4byte	0x921
	.uleb128 0x1c
	.4byte	.LASF220
	.byte	0x6
	.byte	0x20
	.4byte	0x991
	.uleb128 0x8
	.4byte	0x921
	.uleb128 0x2e
	.4byte	.LASF221
	.2byte	0x107
	.byte	0x18
	.4byte	0x9a2
	.uleb128 0x8
	.4byte	0x8c1
	.uleb128 0x2e
	.4byte	.LASF222
	.2byte	0x108
	.byte	0x23
	.4byte	0x97b
	.uleb128 0xe
	.byte	0x7
	.4byte	0x2d
	.byte	0x7
	.byte	0x4b
	.byte	0xe
	.4byte	0xa03
	.uleb128 0x1
	.4byte	.LASF223
	.byte	0
	.uleb128 0x1
	.4byte	.LASF224
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF225
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF226
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF227
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF228
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF229
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF230
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF231
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF232
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF233
	.byte	0xa
	.byte	0
	.uleb128 0x9
	.4byte	0x92
	.4byte	0xa13
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x93
	.byte	0
	.uleb128 0x17
	.4byte	0xa03
	.uleb128 0x2f
	.4byte	.LASF234
	.byte	0x8
	.byte	0x97
	.byte	0x19
	.4byte	0xa13
	.uleb128 0xe
	.byte	0x7
	.4byte	0x2d
	.byte	0x9
	.byte	0x50
	.byte	0xe
	.4byte	0xa68
	.uleb128 0x1
	.4byte	.LASF235
	.byte	0
	.uleb128 0x1
	.4byte	.LASF236
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF237
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF238
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF239
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF240
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF241
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF242
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF243
	.byte	0x8
	.byte	0
	.uleb128 0xe
	.byte	0x7
	.4byte	0x2d
	.byte	0xa
	.byte	0x31
	.byte	0x1
	.4byte	0xaa6
	.uleb128 0x1
	.4byte	.LASF244
	.byte	0
	.uleb128 0x1
	.4byte	.LASF245
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF246
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF247
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF248
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF249
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF250
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF251
	.byte	0x7
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF252
	.byte	0x1
	.byte	0x74
	.byte	0xc
	.4byte	0x8fd
	.uleb128 0x40
	.4byte	0x9a7
	.byte	0x1
	.byte	0x75
	.byte	0x1c
	.uleb128 0x5
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.uleb128 0x1f
	.4byte	.LASF253
	.byte	0x76
	.byte	0x1a
	.4byte	0x747
	.uleb128 0x5
	.byte	0x3
	.4byte	g_pPkaRtInfo
	.uleb128 0x1f
	.4byte	.LASF254
	.byte	0x77
	.byte	0xa
	.4byte	0x9c
	.uleb128 0x5
	.byte	0x3
	.4byte	pka_cb_type
	.uleb128 0x1f
	.4byte	.LASF255
	.byte	0x78
	.byte	0x7
	.4byte	0x73
	.uleb128 0x5
	.byte	0x3
	.4byte	g_pEmptyPktPtr
	.uleb128 0x41
	.4byte	.LASF256
	.byte	0x1
	.2byte	0x254
	.byte	0x18
	.4byte	0x910
	.uleb128 0x5
	.byte	0x3
	.4byte	g_pLastGetHidTx
	.uleb128 0x20
	.4byte	.LASF257
	.byte	0xb
	.byte	0x3f
	.4byte	0xb17
	.uleb128 0xc
	.4byte	0xa8
	.byte	0
	.uleb128 0x30
	.4byte	.LASF258
	.2byte	0x10b
	.byte	0x6
	.4byte	0xb29
	.uleb128 0xc
	.4byte	0x473
	.byte	0
	.uleb128 0x30
	.4byte	.LASF259
	.2byte	0x10a
	.byte	0xd
	.4byte	0xb3b
	.uleb128 0xc
	.4byte	0x473
	.byte	0
	.uleb128 0x21
	.4byte	.LASF260
	.byte	0x43
	.4byte	0xb47
	.uleb128 0x22
	.byte	0
	.uleb128 0x21
	.4byte	.LASF261
	.byte	0x41
	.4byte	0xb53
	.uleb128 0x22
	.byte	0
	.uleb128 0x21
	.4byte	.LASF262
	.byte	0x42
	.4byte	0xb5f
	.uleb128 0x22
	.byte	0
	.uleb128 0x20
	.4byte	.LASF263
	.byte	0xb
	.byte	0x3e
	.4byte	0xb70
	.uleb128 0xc
	.4byte	0x5d9
	.byte	0
	.uleb128 0x31
	.4byte	.LASF265
	.2byte	0x127
	.4byte	0x4a5
	.4byte	0xb85
	.uleb128 0xc
	.4byte	0x473
	.byte	0
	.uleb128 0x20
	.4byte	.LASF264
	.byte	0xc
	.byte	0x44
	.4byte	0xba0
	.uleb128 0xc
	.4byte	0x81
	.uleb128 0xc
	.4byte	0x81
	.uleb128 0xc
	.4byte	0x65
	.byte	0
	.uleb128 0x31
	.4byte	.LASF266
	.2byte	0x11d
	.4byte	0x4a5
	.4byte	0xbb5
	.uleb128 0xc
	.4byte	0x473
	.byte	0
	.uleb128 0x42
	.4byte	.LASF321
	.byte	0x1
	.2byte	0x3e8
	.byte	0x9
	.4byte	0x86
	.4byte	.LFB45
	.4byte	.LFE45-.LFB45
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xd
	.4byte	.LASF267
	.2byte	0x3da
	.byte	0x9
	.4byte	0x86
	.4byte	.LFB44
	.4byte	.LFE44-.LFB44
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbf5
	.uleb128 0x13
	.4byte	.LASF269
	.2byte	0x3e1
	.byte	0xd
	.4byte	0x86
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0xf
	.4byte	.LASF277
	.2byte	0x3c0
	.byte	0x6
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc15
	.uleb128 0x7
	.4byte	.LVL139
	.4byte	0x10e5
	.byte	0
	.uleb128 0xd
	.4byte	.LASF268
	.2byte	0x2b4
	.byte	0x2a
	.4byte	0xa8
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd7e
	.uleb128 0x5
	.4byte	.LASF270
	.2byte	0x2b7
	.byte	0xe
	.4byte	0xa8
	.4byte	.LLST37
	.uleb128 0x5
	.4byte	.LASF271
	.2byte	0x2b8
	.byte	0xb
	.4byte	0x73
	.4byte	.LLST38
	.uleb128 0x5
	.4byte	.LASF272
	.2byte	0x2b9
	.byte	0xb
	.4byte	0x73
	.4byte	.LLST39
	.uleb128 0x5
	.4byte	.LASF273
	.2byte	0x2ba
	.byte	0xb
	.4byte	0xd7e
	.4byte	.LLST40
	.uleb128 0x13
	.4byte	.LASF274
	.2byte	0x2bb
	.byte	0x24
	.4byte	0x986
	.uleb128 0x6
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x9f
	.uleb128 0x5
	.4byte	.LASF275
	.2byte	0x2bc
	.byte	0x1c
	.4byte	0x910
	.4byte	.LLST41
	.uleb128 0x13
	.4byte	.LASF276
	.2byte	0x2bd
	.byte	0xe
	.4byte	0xa8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x23
	.4byte	0x112f
	.4byte	.LBB70
	.4byte	.LBE70-.LBB70
	.2byte	0x32a
	.byte	0xd
	.4byte	0xcbf
	.uleb128 0x10
	.4byte	0x113c
	.4byte	.LLST42
	.byte	0
	.uleb128 0x23
	.4byte	0x1149
	.4byte	.LBB72
	.4byte	.LBE72-.LBB72
	.2byte	0x332
	.byte	0xd
	.4byte	0xcdd
	.uleb128 0x10
	.4byte	0x1156
	.4byte	.LLST43
	.byte	0
	.uleb128 0x24
	.4byte	0x112f
	.4byte	.LBB74
	.4byte	.LLRL44
	.2byte	0x2f6
	.byte	0xd
	.4byte	0xcfb
	.uleb128 0x10
	.4byte	0x113c
	.4byte	.LLST45
	.byte	0
	.uleb128 0x25
	.4byte	.LVL78
	.4byte	0xb5f
	.4byte	0xd0f
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x7
	.4byte	.LVL85
	.4byte	0xb06
	.uleb128 0x7
	.4byte	.LVL92
	.4byte	0xb53
	.uleb128 0x7
	.4byte	.LVL98
	.4byte	0xb3b
	.uleb128 0x25
	.4byte	.LVL100
	.4byte	0xb29
	.4byte	0xd3d
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.uleb128 0x25
	.4byte	.LVL101
	.4byte	0xb17
	.4byte	0xd50
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.uleb128 0x7
	.4byte	.LVL105
	.4byte	0xb53
	.uleb128 0x7
	.4byte	.LVL114
	.4byte	0x1473
	.uleb128 0x7
	.4byte	.LVL117
	.4byte	0xb47
	.uleb128 0x7
	.4byte	.LVL132
	.4byte	0x1473
	.uleb128 0x7
	.4byte	.LVL134
	.4byte	0xb47
	.byte	0
	.uleb128 0x9
	.4byte	0x73
	.4byte	0xd8e
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0xf
	.4byte	.LASF278
	.2byte	0x29e
	.byte	0x26
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xdb3
	.uleb128 0x18
	.4byte	.LASF287
	.2byte	0x29e
	.byte	0x46
	.4byte	0x73
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0xd
	.4byte	.LASF279
	.2byte	0x27c
	.byte	0x27
	.4byte	0x73
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe2d
	.uleb128 0x32
	.4byte	.LLRL31
	.uleb128 0x5
	.4byte	.LASF275
	.2byte	0x280
	.byte	0x24
	.4byte	0x910
	.4byte	.LLST32
	.uleb128 0x5
	.4byte	.LASF274
	.2byte	0x281
	.byte	0x2c
	.4byte	0x986
	.4byte	.LLST33
	.uleb128 0x5
	.4byte	.LASF280
	.2byte	0x282
	.byte	0x15
	.4byte	0x86
	.4byte	.LLST34
	.uleb128 0x5
	.4byte	.LASF281
	.2byte	0x283
	.byte	0x15
	.4byte	0x86
	.4byte	.LLST35
	.uleb128 0x5
	.4byte	.LASF282
	.2byte	0x283
	.byte	0x48
	.4byte	0x86
	.4byte	.LLST36
	.uleb128 0x7
	.4byte	.LVL69
	.4byte	0x147c
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	.LASF283
	.2byte	0x260
	.byte	0x26
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe8a
	.uleb128 0x33
	.4byte	.LBB61
	.4byte	.LBE61-.LBB61
	.uleb128 0x5
	.4byte	.LASF275
	.2byte	0x263
	.byte	0x20
	.4byte	0x910
	.4byte	.LLST27
	.uleb128 0x32
	.4byte	.LLRL28
	.uleb128 0x26
	.string	"idx"
	.2byte	0x266
	.byte	0x15
	.4byte	0x86
	.4byte	.LLST29
	.uleb128 0x34
	.4byte	0x1163
	.4byte	.LBB63
	.4byte	.LLRL30
	.2byte	0x268
	.byte	0x21
	.uleb128 0x19
	.4byte	0x1173
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	.LASF284
	.2byte	0x1e1
	.byte	0x6
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf63
	.uleb128 0x27
	.4byte	.LLRL20
	.4byte	0xf10
	.uleb128 0x26
	.string	"idx"
	.2byte	0x1e8
	.byte	0x19
	.4byte	0x86
	.4byte	.LLST21
	.uleb128 0x24
	.4byte	0x11b7
	.4byte	.LBB46
	.4byte	.LLRL22
	.2byte	0x1ea
	.byte	0x11
	.4byte	0xed7
	.uleb128 0x10
	.4byte	0x11c4
	.4byte	.LLST23
	.byte	0
	.uleb128 0x24
	.4byte	0x112f
	.4byte	.LBB51
	.4byte	.LLRL24
	.2byte	0x1ec
	.byte	0x11
	.4byte	0xef5
	.uleb128 0x10
	.4byte	0x113c
	.4byte	.LLST25
	.byte	0
	.uleb128 0x28
	.4byte	0x1180
	.4byte	.LBB55
	.4byte	.LBE55-.LBB55
	.2byte	0x1eb
	.byte	0x11
	.uleb128 0x10
	.4byte	0x118d
	.4byte	.LLST26
	.byte	0
	.byte	0
	.uleb128 0x33
	.4byte	.LBB59
	.4byte	.LBE59-.LBB59
	.uleb128 0x43
	.string	"exp"
	.byte	0x1
	.2byte	0x1f3
	.byte	0x61
	.4byte	0xf73
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x13
	.4byte	.LASF285
	.2byte	0x1f3
	.byte	0xad
	.4byte	0xf88
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0x15
	.4byte	.LVL51
	.4byte	0xb85
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x1f3
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0x7c
	.4byte	0xf73
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.4byte	0xf63
	.uleb128 0x9
	.4byte	0x7c
	.4byte	0xf88
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x42
	.byte	0
	.uleb128 0x12
	.4byte	0xf78
	.uleb128 0xf
	.4byte	.LASF286
	.2byte	0x1cc
	.byte	0x6
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xff9
	.uleb128 0x35
	.4byte	.LASF210
	.2byte	0x1cc
	.byte	0x23
	.4byte	0x86
	.4byte	.LLST16
	.uleb128 0x5
	.4byte	.LASF288
	.2byte	0x1ce
	.byte	0xe
	.4byte	0x9c
	.4byte	.LLST17
	.uleb128 0x27
	.4byte	.LLRL18
	.4byte	0xfef
	.uleb128 0x26
	.string	"idx"
	.2byte	0x1d1
	.byte	0x11
	.4byte	0x86
	.4byte	.LLST19
	.uleb128 0x15
	.4byte	.LVL46
	.4byte	0x11ee
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x4
	.byte	0x72
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x44
	.4byte	.LVL44
	.4byte	0x11ee
	.byte	0
	.uleb128 0xd
	.4byte	.LASF289
	.2byte	0x1bd
	.byte	0x5
	.4byte	0x8fd
	.4byte	.LFB36
	.4byte	.LFE36-.LFB36
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1024
	.uleb128 0x35
	.4byte	.LASF210
	.2byte	0x1bd
	.byte	0x25
	.4byte	0x9c
	.4byte	.LLST15
	.byte	0
	.uleb128 0xf
	.4byte	.LASF290
	.2byte	0x1b5
	.byte	0x6
	.4byte	.LFB35
	.4byte	.LFE35-.LFB35
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1049
	.uleb128 0x18
	.4byte	.LASF291
	.2byte	0x1b5
	.byte	0x23
	.4byte	0x86
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0xd
	.4byte	.LASF292
	.2byte	0x1ad
	.byte	0x5
	.4byte	0x8fd
	.4byte	.LFB34
	.4byte	.LFE34-.LFB34
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x108a
	.uleb128 0x14
	.string	"ptr"
	.2byte	0x1ad
	.byte	0x22
	.4byte	0x631
	.4byte	.LLST14
	.uleb128 0x28
	.4byte	0x11d1
	.4byte	.LBB41
	.4byte	.LBE41-.LBB41
	.2byte	0x1af
	.byte	0x17
	.uleb128 0x19
	.4byte	0x11e1
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF293
	.2byte	0x1a8
	.byte	0xa
	.4byte	0x9c
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10e5
	.uleb128 0x14
	.string	"ptr"
	.2byte	0x1a8
	.byte	0x2c
	.4byte	0x631
	.4byte	.LLST13
	.uleb128 0x23
	.4byte	0x11d1
	.4byte	.LBB37
	.4byte	.LBE37-.LBB37
	.2byte	0x1aa
	.byte	0xc
	.4byte	0x10ce
	.uleb128 0x19
	.4byte	0x11e1
	.byte	0
	.uleb128 0x28
	.4byte	0x119a
	.4byte	.LBB39
	.4byte	.LBE39-.LBB39
	.2byte	0x1aa
	.byte	0x37
	.uleb128 0x19
	.4byte	0x11aa
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF294
	.2byte	0x199
	.byte	0x5
	.4byte	0x8fd
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x112f
	.uleb128 0x14
	.string	"ptr"
	.2byte	0x199
	.byte	0x20
	.4byte	0x631
	.4byte	.LLST12
	.uleb128 0x13
	.4byte	.LASF295
	.2byte	0x19c
	.byte	0xc
	.4byte	0x62c
	.uleb128 0x4
	.byte	0x7f
	.sleb128 96
	.byte	0x9f
	.uleb128 0x13
	.4byte	.LASF174
	.2byte	0x19d
	.byte	0xb
	.4byte	0x73
	.uleb128 0x1
	.byte	0x5e
	.byte	0
	.uleb128 0x16
	.4byte	.LASF296
	.2byte	0x18e
	.byte	0xd
	.byte	0x3
	.4byte	0x1149
	.uleb128 0x11
	.string	"ptr"
	.2byte	0x18e
	.byte	0x31
	.4byte	0x631
	.byte	0
	.uleb128 0x16
	.4byte	.LASF297
	.2byte	0x189
	.byte	0xd
	.byte	0x3
	.4byte	0x1163
	.uleb128 0x11
	.string	"ptr"
	.2byte	0x189
	.byte	0x2b
	.4byte	0x631
	.byte	0
	.uleb128 0x29
	.4byte	.LASF298
	.2byte	0x184
	.byte	0x10
	.4byte	0x86
	.4byte	0x1180
	.uleb128 0x11
	.string	"ptr"
	.2byte	0x184
	.byte	0x2d
	.4byte	0x631
	.byte	0
	.uleb128 0x16
	.4byte	.LASF299
	.2byte	0x17f
	.byte	0xd
	.byte	0x3
	.4byte	0x119a
	.uleb128 0x11
	.string	"ptr"
	.2byte	0x17f
	.byte	0x32
	.4byte	0x5de
	.byte	0
	.uleb128 0x29
	.4byte	.LASF300
	.2byte	0x17a
	.byte	0x11
	.4byte	0x9c
	.4byte	0x11b7
	.uleb128 0x11
	.string	"ptr"
	.2byte	0x17a
	.byte	0x32
	.4byte	0x5de
	.byte	0
	.uleb128 0x16
	.4byte	.LASF301
	.2byte	0x175
	.byte	0xd
	.byte	0x3
	.4byte	0x11d1
	.uleb128 0x11
	.string	"ptr"
	.2byte	0x175
	.byte	0x33
	.4byte	0x5de
	.byte	0
	.uleb128 0x29
	.4byte	.LASF302
	.2byte	0x170
	.byte	0x11
	.4byte	0x9c
	.4byte	0x11ee
	.uleb128 0x11
	.string	"ptr"
	.2byte	0x170
	.byte	0x33
	.4byte	0x5de
	.byte	0
	.uleb128 0x16
	.4byte	.LASF303
	.2byte	0x167
	.byte	0x6
	.byte	0x1
	.4byte	0x1215
	.uleb128 0x11
	.string	"ptr"
	.2byte	0x167
	.byte	0x2b
	.4byte	0x631
	.uleb128 0x45
	.4byte	.LASF210
	.byte	0x1
	.2byte	0x167
	.byte	0x38
	.4byte	0x86
	.byte	0
	.uleb128 0xf
	.4byte	.LASF304
	.2byte	0x158
	.byte	0x6
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x124c
	.uleb128 0x14
	.string	"ptr"
	.2byte	0x158
	.byte	0x26
	.4byte	0x5de
	.4byte	.LLST7
	.uleb128 0x5
	.4byte	.LASF305
	.2byte	0x15a
	.byte	0xe
	.4byte	0x9c
	.4byte	.LLST8
	.byte	0
	.uleb128 0xd
	.4byte	.LASF306
	.2byte	0x153
	.byte	0xa
	.4byte	0x631
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1277
	.uleb128 0x14
	.string	"ptr"
	.2byte	0x153
	.byte	0x30
	.4byte	0x631
	.4byte	.LLST6
	.byte	0
	.uleb128 0xd
	.4byte	.LASF307
	.2byte	0x14d
	.byte	0xb
	.4byte	0x631
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x12bb
	.uleb128 0x14
	.string	"idx"
	.2byte	0x14d
	.byte	0x2f
	.4byte	0x86
	.4byte	.LLST4
	.uleb128 0x5
	.4byte	.LASF308
	.2byte	0x14f
	.byte	0xe
	.4byte	0x9c
	.4byte	.LLST5
	.uleb128 0x7
	.4byte	.LVL15
	.4byte	0x1485
	.byte	0
	.uleb128 0xf
	.4byte	.LASF309
	.2byte	0x112
	.byte	0x6
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x12fd
	.uleb128 0x18
	.4byte	.LASF310
	.2byte	0x112
	.byte	0x32
	.4byte	0x4d6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x18
	.4byte	.LASF311
	.2byte	0x112
	.byte	0x41
	.4byte	0x9c
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x46
	.string	"num"
	.byte	0x1
	.2byte	0x112
	.byte	0x50
	.4byte	0x9c
	.uleb128 0x1
	.byte	0x5c
	.byte	0
	.uleb128 0x47
	.4byte	.LASF322
	.byte	0x1
	.2byte	0x10b
	.byte	0x6
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x36
	.4byte	.LASF312
	.byte	0x8b
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1398
	.uleb128 0x37
	.4byte	.LASF313
	.byte	0x8b
	.4byte	0x473
	.4byte	.LLST2
	.uleb128 0x27
	.4byte	.LLRL3
	.4byte	0x1380
	.uleb128 0x38
	.string	"exp"
	.byte	0x8e
	.byte	0x59
	.4byte	0xf73
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.3
	.uleb128 0x39
	.4byte	.LASF285
	.byte	0x8e
	.byte	0xa5
	.4byte	0xf88
	.uleb128 0x5
	.byte	0x3
	.4byte	file.2
	.uleb128 0x48
	.4byte	.LVL10
	.4byte	0xb85
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.3
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.2
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x8e
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LVL9
	.4byte	0xb70
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
	.uleb128 0x36
	.4byte	.LASF314
	.byte	0x7b
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x142e
	.uleb128 0x37
	.4byte	.LASF313
	.byte	0x7b
	.4byte	0x473
	.4byte	.LLST0
	.uleb128 0x49
	.4byte	.LASF315
	.byte	0x1
	.byte	0x7d
	.byte	0xe
	.4byte	0xa8
	.4byte	.LLST1
	.uleb128 0x4a
	.4byte	.LBB26
	.4byte	.LBE26-.LBB26
	.4byte	0x141c
	.uleb128 0x38
	.string	"exp"
	.byte	0x86
	.byte	0x5d
	.4byte	0xf73
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.5
	.uleb128 0x39
	.4byte	.LASF285
	.byte	0x86
	.byte	0xa9
	.4byte	0xf88
	.uleb128 0x5
	.byte	0x3
	.4byte	file.4
	.uleb128 0x15
	.4byte	.LVL5
	.4byte	0xb85
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.5
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.4
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x86
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LVL2
	.4byte	0xba0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x4b
	.4byte	0x11ee
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1473
	.uleb128 0x3a
	.4byte	0x11fb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3a
	.4byte	0x1207
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x34
	.4byte	0x11ee
	.4byte	.LBB33
	.4byte	.LLRL9
	.2byte	0x167
	.byte	0x6
	.uleb128 0x10
	.4byte	0x1207
	.4byte	.LLST10
	.uleb128 0x10
	.4byte	0x11fb
	.4byte	.LLST11
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	.LASF316
	.4byte	.LASF316
	.uleb128 0x2a
	.4byte	.LASF317
	.4byte	.LASF317
	.uleb128 0x2a
	.4byte	.LASF318
	.4byte	.LASF318
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
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x10
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x14
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
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
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0x1b
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 259
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.sleb128 13
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
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
	.sleb128 13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x23
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
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x26
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
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
	.sleb128 6
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
	.uleb128 0x2f
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
	.uleb128 0x30
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
	.uleb128 0x31
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 27
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
	.uleb128 0x32
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x34
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
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x36
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
	.uleb128 0x37
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
	.uleb128 0x21
	.sleb128 56
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x38
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x39
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
	.uleb128 0x3a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3b
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
	.uleb128 0x3c
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
	.uleb128 0x3d
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3e
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
	.uleb128 0x3f
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
	.uleb128 0x40
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
	.uleb128 0x41
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x42
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
	.uleb128 0x43
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
	.uleb128 0x44
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
	.uleb128 0x45
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
	.byte	0
	.byte	0
	.uleb128 0x46
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x47
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
	.uleb128 0x48
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
	.uleb128 0x49
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x4a
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
	.uleb128 0x4b
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
	.byte	0
	.section	.debug_loclists,"",@progbits
	.4byte	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.Ldebug_loc0:
.LLST37:
	.byte	0x6
	.4byte	.LVL76
	.byte	0x4
	.uleb128 .LVL76-.LVL76
	.uleb128 .LVL84-.LVL76
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL86-.LVL76
	.uleb128 .LVL93-.LVL76
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL102-.LVL76
	.uleb128 .LVL109-.LVL76
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL110-.LVL76
	.uleb128 .LVL115-.LVL76
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL116-.LVL76
	.uleb128 .LVL117-1-.LVL76
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL117-1-.LVL76
	.uleb128 .LVL118-.LVL76
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL118-.LVL76
	.uleb128 .LVL121-.LVL76
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL124-.LVL76
	.uleb128 .LVL129-.LVL76
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL133-.LVL76
	.uleb128 .LVL135-.LVL76
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL135-.LVL76
	.uleb128 .LVL136-.LVL76
	.uleb128 0x3
	.byte	0x79
	.sleb128 7
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL136-.LVL76
	.uleb128 .LVL137-.LVL76
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0
.LLST38:
	.byte	0x6
	.4byte	.LVL79
	.byte	0x4
	.uleb128 .LVL79-.LVL79
	.uleb128 .LVL83-.LVL79
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL86-.LVL79
	.uleb128 .LVL92-1-.LVL79
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL92-1-.LVL79
	.uleb128 .LVL93-.LVL79
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL102-.LVL79
	.uleb128 .LVL104-.LVL79
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL104-.LVL79
	.uleb128 .LVL110-.LVL79
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL110-.LVL79
	.uleb128 .LVL111-.LVL79
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL118-.LVL79
	.uleb128 .LVL121-.LVL79
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL124-.LVL79
	.uleb128 .LVL125-.LVL79
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL125-.LVL79
	.uleb128 .LVL127-.LVL79
	.uleb128 0x5
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl+52
	.byte	0x4
	.uleb128 .LVL127-.LVL79
	.uleb128 .LVL128-.LVL79
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL136-.LVL79
	.uleb128 .LVL137-.LVL79
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST39:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL83-.LVL80
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL87-.LVL80
	.uleb128 .LVL91-.LVL80
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL102-.LVL80
	.uleb128 .LVL105-1-.LVL80
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL105-1-.LVL80
	.uleb128 .LVL109-.LVL80
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL110-.LVL80
	.uleb128 .LVL112-.LVL80
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL112-.LVL80
	.uleb128 .LVL121-.LVL80
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL124-.LVL80
	.uleb128 .LVL129-.LVL80
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL136-.LVL80
	.uleb128 .LVL137-.LVL80
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL138-.LVL80
	.uleb128 .LFE42-.LVL80
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST40:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL81-.LVL80
	.uleb128 0x5
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL81-.LVL80
	.uleb128 .LVL82-.LVL80
	.uleb128 0xa
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x76
	.sleb128 24
	.byte	0x6
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL82-.LVL80
	.uleb128 .LVL83-.LVL80
	.uleb128 0xb
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x76
	.sleb128 24
	.byte	0x6
	.byte	0x93
	.uleb128 0x4
	.byte	0x5c
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL87-.LVL80
	.uleb128 .LVL88-.LVL80
	.uleb128 0xb
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x76
	.sleb128 24
	.byte	0x6
	.byte	0x93
	.uleb128 0x4
	.byte	0x5c
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL88-.LVL80
	.uleb128 .LVL89-.LVL80
	.uleb128 0x11
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x3
	.4byte	g_pPkaRtInfo
	.byte	0x6
	.byte	0x23
	.uleb128 0x18
	.byte	0x6
	.byte	0x93
	.uleb128 0x4
	.byte	0x5c
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL89-.LVL80
	.uleb128 .LVL90-.LVL80
	.uleb128 0x8
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x5c
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL90-.LVL80
	.uleb128 .LVL92-1-.LVL80
	.uleb128 0x9
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x72
	.sleb128 0
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL92-1-.LVL80
	.uleb128 .LVL93-.LVL80
	.uleb128 0xa
	.byte	0x91
	.sleb128 -28
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x72
	.sleb128 0
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL93-.LVL80
	.uleb128 .LVL98-1-.LVL80
	.uleb128 0x5
	.byte	0x93
	.uleb128 0x8
	.byte	0x57
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL102-.LVL80
	.uleb128 .LVL103-.LVL80
	.uleb128 0x5
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL103-.LVL80
	.uleb128 .LVL106-.LVL80
	.uleb128 0x6
	.byte	0x72
	.sleb128 0
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL106-.LVL80
	.uleb128 .LVL108-.LVL80
	.uleb128 0x5
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL108-.LVL80
	.uleb128 .LVL110-.LVL80
	.uleb128 0x9
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x56
	.byte	0x93
	.uleb128 0x4
	.byte	0x57
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL110-.LVL80
	.uleb128 .LVL112-.LVL80
	.uleb128 0x5
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL112-.LVL80
	.uleb128 .LVL113-.LVL80
	.uleb128 0x6
	.byte	0x91
	.sleb128 -24
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL118-.LVL80
	.uleb128 .LVL120-.LVL80
	.uleb128 0x5
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL120-.LVL80
	.uleb128 .LVL121-.LVL80
	.uleb128 0x9
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x56
	.byte	0x93
	.uleb128 0x4
	.byte	0x57
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL121-.LVL80
	.uleb128 .LVL124-.LVL80
	.uleb128 0x5
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL124-.LVL80
	.uleb128 .LVL126-.LVL80
	.uleb128 0x5
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL126-.LVL80
	.uleb128 .LVL127-.LVL80
	.uleb128 0x6
	.byte	0x71
	.sleb128 0
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL127-.LVL80
	.uleb128 .LVL128-.LVL80
	.uleb128 0x11
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x3
	.4byte	g_pPkaRtInfo
	.byte	0x6
	.byte	0x23
	.uleb128 0x18
	.byte	0x6
	.byte	0x93
	.uleb128 0x4
	.byte	0x5c
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL128-.LVL80
	.uleb128 .LVL130-.LVL80
	.uleb128 0x5
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL130-.LVL80
	.uleb128 .LVL131-.LVL80
	.uleb128 0x9
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x91
	.sleb128 -20
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL131-.LVL80
	.uleb128 .LVL132-1-.LVL80
	.uleb128 0x5
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL132-1-.LVL80
	.uleb128 .LVL136-.LVL80
	.uleb128 0x6
	.byte	0x91
	.sleb128 -24
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL136-.LVL80
	.uleb128 .LVL137-.LVL80
	.uleb128 0x9
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x56
	.byte	0x93
	.uleb128 0x4
	.byte	0x57
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL137-.LVL80
	.uleb128 .LFE42-.LVL80
	.uleb128 0x5
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x8
	.byte	0
.LLST41:
	.byte	0x6
	.4byte	.LVL77
	.byte	0x4
	.uleb128 .LVL77-.LVL77
	.uleb128 .LVL84-.LVL77
	.uleb128 0x10
	.byte	0x72
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x3c
	.byte	0x1e
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL86-.LVL77
	.uleb128 .LVL90-.LVL77
	.uleb128 0x10
	.byte	0x72
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x3c
	.byte	0x1e
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL93-.LVL77
	.uleb128 .LVL96-.LVL77
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL102-.LVL77
	.uleb128 .LVL103-.LVL77
	.uleb128 0x10
	.byte	0x72
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x3c
	.byte	0x1e
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL110-.LVL77
	.uleb128 .LVL116-.LVL77
	.uleb128 0x10
	.byte	0x72
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x3c
	.byte	0x1e
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL122-.LVL77
	.uleb128 .LVL123-.LVL77
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL124-.LVL77
	.uleb128 .LVL128-.LVL77
	.uleb128 0x10
	.byte	0x72
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x3c
	.byte	0x1e
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL137-.LVL77
	.uleb128 .LFE42-.LVL77
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST42:
	.byte	0x8
	.4byte	.LVL93
	.uleb128 .LVL94-.LVL93
	.uleb128 0x1
	.byte	0x57
	.byte	0
.LLST43:
	.byte	0x8
	.4byte	.LVL95
	.uleb128 .LVL97-.LVL95
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST45:
	.byte	0x6
	.4byte	.LVL106
	.byte	0x4
	.uleb128 .LVL106-.LVL106
	.uleb128 .LVL107-.LVL106
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL118-.LVL106
	.uleb128 .LVL119-.LVL106
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST32:
	.byte	0x6
	.4byte	.LVL65
	.byte	0x4
	.uleb128 .LVL65-.LVL65
	.uleb128 .LVL67-.LVL65
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL67-.LVL65
	.uleb128 .LVL68-.LVL65
	.uleb128 0xb
	.byte	0x7a
	.sleb128 0
	.byte	0x3c
	.byte	0x1e
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL69-.LVL65
	.uleb128 .LVL70-.LVL65
	.uleb128 0xb
	.byte	0x7a
	.sleb128 0
	.byte	0x3c
	.byte	0x1e
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL73-.LVL65
	.uleb128 .LVL74-.LVL65
	.uleb128 0xb
	.byte	0x7a
	.sleb128 0
	.byte	0x3c
	.byte	0x1e
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x22
	.byte	0x9f
	.byte	0
.LLST33:
	.byte	0x6
	.4byte	.LVL65
	.byte	0x4
	.uleb128 .LVL65-.LVL65
	.uleb128 .LVL72-.LVL65
	.uleb128 0x6
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL73-.LVL65
	.uleb128 .LFE40-.LVL65
	.uleb128 0x6
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x9f
	.byte	0
.LLST34:
	.byte	0x6
	.4byte	.LVL65
	.byte	0x4
	.uleb128 .LVL65-.LVL65
	.uleb128 .LVL66-.LVL65
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL66-.LVL65
	.uleb128 .LVL71-.LVL65
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL71-.LVL65
	.uleb128 .LVL72-.LVL65
	.uleb128 0x2
	.byte	0x72
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL73-.LVL65
	.uleb128 .LFE40-.LVL65
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST35:
	.byte	0x8
	.4byte	.LVL65
	.uleb128 .LVL67-.LVL65
	.uleb128 0x5
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl+48
	.byte	0
.LLST36:
	.byte	0x8
	.4byte	.LVL65
	.uleb128 .LVL67-.LVL65
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST27:
	.byte	0x6
	.4byte	.LVL60
	.byte	0x4
	.uleb128 .LVL60-.LVL60
	.uleb128 .LVL61-.LVL60
	.uleb128 0x6
	.byte	0x3
	.4byte	pka_share_tx_hid_ctl
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL61-.LVL60
	.uleb128 .LFE39-.LVL60
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST29:
	.byte	0x8
	.4byte	.LVL60
	.uleb128 .LVL61-.LVL60
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST21:
	.byte	0x6
	.4byte	.LVL48
	.byte	0x4
	.uleb128 .LVL48-.LVL48
	.uleb128 .LVL49-.LVL48
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL49-.LVL48
	.uleb128 .LVL50-.LVL48
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL53-.LVL48
	.uleb128 .LVL58-.LVL48
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL59-.LVL48
	.uleb128 .LFE38-.LVL48
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST23:
	.byte	0x8
	.4byte	.LVL54
	.uleb128 .LVL55-.LVL54
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST25:
	.byte	0x8
	.4byte	.LVL56
	.uleb128 .LVL57-.LVL56
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST26:
	.byte	0x8
	.4byte	.LVL55
	.uleb128 .LVL56-.LVL55
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST16:
	.byte	0x6
	.4byte	.LVL39
	.byte	0x4
	.uleb128 .LVL39-.LVL39
	.uleb128 .LVL42-.LVL39
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL42-.LVL39
	.uleb128 .LFE37-.LVL39
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
.LLST17:
	.byte	0x8
	.4byte	.LVL40
	.uleb128 .LVL41-.LVL40
	.uleb128 0xf
	.byte	0x7f
	.sleb128 0
	.byte	0x94
	.byte	0x2
	.byte	0xb
	.2byte	0xff00
	.byte	0x1a
	.byte	0x7a
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL41
	.byte	0x4
	.uleb128 .LVL41-.LVL41
	.uleb128 .LVL42-.LVL41
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL42-.LVL41
	.uleb128 .LVL43-.LVL41
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL44-.LVL41
	.uleb128 .LVL45-.LVL41
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL47-.LVL41
	.uleb128 .LFE37-.LVL41
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL37
	.byte	0x4
	.uleb128 .LVL37-.LVL37
	.uleb128 .LVL38-.LVL37
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL38-.LVL37
	.uleb128 .LFE36-.LVL37
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x3b
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST14:
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
	.uleb128 .LFE34-.LVL31
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
	.4byte	.LVL29
	.byte	0x4
	.uleb128 .LVL29-.LVL29
	.uleb128 .LVL30-.LVL29
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL30-.LVL29
	.uleb128 .LFE33-.LVL29
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
.LLST12:
	.byte	0x6
	.4byte	.LVL25
	.byte	0x4
	.uleb128 .LVL25-.LVL25
	.uleb128 .LVL27-.LVL25
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL27-.LVL25
	.uleb128 .LFE32-.LVL25
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
	.4byte	.LVL18
	.byte	0x4
	.uleb128 .LVL18-.LVL18
	.uleb128 .LVL20-.LVL18
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL20-.LVL18
	.uleb128 .LFE21-.LVL18
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
	.byte	0x8
	.4byte	.LVL19
	.uleb128 .LVL21-.LVL19
	.uleb128 0x7
	.byte	0x7e
	.sleb128 44
	.byte	0x94
	.byte	0x2
	.byte	0x31
	.byte	0x25
	.byte	0x9f
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL16
	.byte	0x4
	.uleb128 .LVL16-.LVL16
	.uleb128 .LVL17-.LVL16
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL17-.LVL16
	.uleb128 .LFE20-.LVL16
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
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL14-.LVL12
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL14-.LVL12
	.uleb128 .LVL15-1-.LVL12
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL15-1-.LVL12
	.uleb128 .LFE19-.LVL12
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
.LLST5:
	.byte	0x8
	.4byte	.LVL13
	.uleb128 .LVL15-1-.LVL13
	.uleb128 0xf
	.byte	0x78
	.sleb128 56
	.byte	0x94
	.byte	0x2
	.byte	0x78
	.sleb128 46
	.byte	0x94
	.byte	0x2
	.byte	0x22
	.byte	0x23
	.uleb128 0x3
	.byte	0x9
	.byte	0xfc
	.byte	0x1a
	.byte	0x9f
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
	.uleb128 .LFE16-.LVL8
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
	.uleb128 .LVL1-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL1-.LVL0
	.uleb128 .LVL7-.LVL0
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL7-.LVL0
	.uleb128 .LFE15-.LVL0
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL1-.LVL0
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL5-.LVL0
	.uleb128 .LVL6-.LVL0
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST10:
	.byte	0x8
	.4byte	.LVL23
	.uleb128 .LVL24-.LVL23
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
.LLST11:
	.byte	0x8
	.4byte	.LVL23
	.uleb128 .LVL24-.LVL23
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0xc4
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
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.4byte	.LFB34
	.4byte	.LFE34-.LFB34
	.4byte	.LFB35
	.4byte	.LFE35-.LFB35
	.4byte	.LFB36
	.4byte	.LFE36-.LFB36
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.4byte	.LFB44
	.4byte	.LFE44-.LFB44
	.4byte	.LFB45
	.4byte	.LFE45-.LFB45
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
.LLRL3:
	.byte	0x5
	.4byte	.LBB27
	.byte	0x4
	.uleb128 .LBB27-.LBB27
	.uleb128 .LBE27-.LBB27
	.byte	0x4
	.uleb128 .LBB28-.LBB27
	.uleb128 .LBE28-.LBB27
	.byte	0x4
	.uleb128 .LBB29-.LBB27
	.uleb128 .LBE29-.LBB27
	.byte	0x4
	.uleb128 .LBB30-.LBB27
	.uleb128 .LBE30-.LBB27
	.byte	0
.LLRL9:
	.byte	0x5
	.4byte	.LBB33
	.byte	0x4
	.uleb128 .LBB33-.LBB33
	.uleb128 .LBE33-.LBB33
	.byte	0x4
	.uleb128 .LBB36-.LBB33
	.uleb128 .LBE36-.LBB33
	.byte	0
.LLRL18:
	.byte	0x5
	.4byte	.LBB43
	.byte	0x4
	.uleb128 .LBB43-.LBB43
	.uleb128 .LBE43-.LBB43
	.byte	0x4
	.uleb128 .LBB44-.LBB43
	.uleb128 .LBE44-.LBB43
	.byte	0
.LLRL20:
	.byte	0x5
	.4byte	.LBB45
	.byte	0x4
	.uleb128 .LBB45-.LBB45
	.uleb128 .LBE45-.LBB45
	.byte	0x4
	.uleb128 .LBB58-.LBB45
	.uleb128 .LBE58-.LBB45
	.byte	0x4
	.uleb128 .LBB60-.LBB45
	.uleb128 .LBE60-.LBB45
	.byte	0
.LLRL22:
	.byte	0x5
	.4byte	.LBB46
	.byte	0x4
	.uleb128 .LBB46-.LBB46
	.uleb128 .LBE46-.LBB46
	.byte	0x4
	.uleb128 .LBB50-.LBB46
	.uleb128 .LBE50-.LBB46
	.byte	0x4
	.uleb128 .LBB54-.LBB46
	.uleb128 .LBE54-.LBB46
	.byte	0
.LLRL24:
	.byte	0x5
	.4byte	.LBB51
	.byte	0x4
	.uleb128 .LBB51-.LBB51
	.uleb128 .LBE51-.LBB51
	.byte	0x4
	.uleb128 .LBB57-.LBB51
	.uleb128 .LBE57-.LBB51
	.byte	0
.LLRL28:
	.byte	0x5
	.4byte	.LBB62
	.byte	0x4
	.uleb128 .LBB62-.LBB62
	.uleb128 .LBE62-.LBB62
	.byte	0x4
	.uleb128 .LBB67-.LBB62
	.uleb128 .LBE67-.LBB62
	.byte	0
.LLRL30:
	.byte	0x5
	.4byte	.LBB63
	.byte	0x4
	.uleb128 .LBB63-.LBB63
	.uleb128 .LBE63-.LBB63
	.byte	0x4
	.uleb128 .LBB66-.LBB63
	.uleb128 .LBE66-.LBB63
	.byte	0
.LLRL31:
	.byte	0x5
	.4byte	.LBB68
	.byte	0x4
	.uleb128 .LBB68-.LBB68
	.uleb128 .LBE68-.LBB68
	.byte	0x4
	.uleb128 .LBB69-.LBB68
	.uleb128 .LBE69-.LBB68
	.byte	0
.LLRL44:
	.byte	0x5
	.4byte	.LBB74
	.byte	0x4
	.uleb128 .LBB74-.LBB74
	.uleb128 .LBE74-.LBB74
	.byte	0x4
	.uleb128 .LBB80-.LBB74
	.uleb128 .LBE80-.LBB74
	.byte	0x4
	.uleb128 .LBB81-.LBB74
	.uleb128 .LBE81-.LBB74
	.byte	0x4
	.uleb128 .LBB82-.LBB74
	.uleb128 .LBE82-.LBB74
	.byte	0x4
	.uleb128 .LBB83-.LBB74
	.uleb128 .LBE83-.LBB74
	.byte	0
.LLRL46:
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
	.4byte	.LFB23
	.uleb128 .LFE23-.LFB23
	.byte	0x7
	.4byte	.LFB32
	.uleb128 .LFE32-.LFB32
	.byte	0x7
	.4byte	.LFB33
	.uleb128 .LFE33-.LFB33
	.byte	0x7
	.4byte	.LFB34
	.uleb128 .LFE34-.LFB34
	.byte	0x7
	.4byte	.LFB35
	.uleb128 .LFE35-.LFB35
	.byte	0x7
	.4byte	.LFB36
	.uleb128 .LFE36-.LFB36
	.byte	0x7
	.4byte	.LFB37
	.uleb128 .LFE37-.LFB37
	.byte	0x7
	.4byte	.LFB38
	.uleb128 .LFE38-.LFB38
	.byte	0x7
	.4byte	.LFB39
	.uleb128 .LFE39-.LFB39
	.byte	0x7
	.4byte	.LFB40
	.uleb128 .LFE40-.LFB40
	.byte	0x7
	.4byte	.LFB41
	.uleb128 .LFE41-.LFB41
	.byte	0x7
	.4byte	.LFB42
	.uleb128 .LFE42-.LFB42
	.byte	0x7
	.4byte	.LFB43
	.uleb128 .LFE43-.LFB43
	.byte	0x7
	.4byte	.LFB44
	.uleb128 .LFE44-.LFB44
	.byte	0x7
	.4byte	.LFB45
	.uleb128 .LFE45-.LFB45
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF37:
	.string	"RESERVED"
.LASF215:
	.string	"HidTxBufIdx"
.LASF202:
	.string	"hid_tx_buf_payload_size"
.LASF322:
	.string	"pka_share_init"
.LASF25:
	.string	"PMU_IRQn"
.LASF280:
	.string	"max_tx_num"
.LASF69:
	.string	"HAL_EINT_NUMBER_20"
.LASF70:
	.string	"HAL_EINT_NUMBER_21"
.LASF71:
	.string	"HAL_EINT_NUMBER_22"
.LASF297:
	.string	"pka_tx_buf_set_valid"
.LASF73:
	.string	"HAL_EINT_NUMBER_24"
.LASF74:
	.string	"HAL_EINT_NUMBER_25"
.LASF26:
	.string	"MCU_DMA_IRQn"
.LASF76:
	.string	"HAL_EINT_NUMBER_27"
.LASF77:
	.string	"HAL_EINT_NUMBER_28"
.LASF78:
	.string	"HAL_EINT_NUMBER_29"
.LASF99:
	.string	"HAL_EINT_UART_2_RX"
.LASF261:
	.string	"hid_express_dbg_inc_pka_hid_cnt"
.LASF48:
	.string	"GPT_REGISTER_T"
.LASF303:
	.string	"pka_tx_buf_set_active_state"
.LASF180:
	.string	"hwmt_last_anchor_ptr"
.LASF269:
	.string	"report_rate"
.LASF286:
	.string	"pka_active_state_set"
.LASF105:
	.string	"HAL_EINT_NUMBER_MAX"
.LASF236:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF100:
	.string	"HAL_EINT_USB0"
.LASF101:
	.string	"HAL_EINT_USB1"
.LASF102:
	.string	"HAL_EINT_USB2"
.LASF3:
	.string	"unsigned int"
.LASF158:
	.string	"next"
.LASF250:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF255:
	.string	"g_pEmptyPktPtr"
.LASF218:
	.string	"pLeAclTxPtr"
.LASF276:
	.string	"mask"
.LASF163:
	.string	"head"
.LASF40:
	.string	"GPT_CON_UNION"
.LASF79:
	.string	"HAL_EINT_NUMBER_30"
.LASF80:
	.string	"HAL_EINT_NUMBER_31"
.LASF244:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF82:
	.string	"HAL_EINT_NUMBER_33"
.LASF294:
	.string	"pka_tx_buf_is_hid"
.LASF268:
	.string	"pka_share_advanced_tx_prepare_rt"
.LASF216:
	.string	"HidTxBufNum"
.LASF86:
	.string	"HAL_EINT_NUMBER_37"
.LASF87:
	.string	"HAL_EINT_NUMBER_38"
.LASF88:
	.string	"HAL_EINT_NUMBER_39"
.LASF256:
	.string	"g_pLastGetHidTx"
.LASF197:
	.string	"hid_tx_buf_start_ptr"
.LASF194:
	.string	"hid_tx_buf_queue"
.LASF21:
	.string	"SPI_MST1_IRQn"
.LASF240:
	.string	"DBG_PIN_USB_SOF"
.LASF145:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF167:
	.string	"hwmt_pico_offset_phase_ptr"
.LASF33:
	.string	"BT_IRQn"
.LASF157:
	.string	"prev"
.LASF144:
	.string	"hal_hw_semaphore_status_t"
.LASF321:
	.string	"pka_share_get_current_max_pdu_len"
.LASF251:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF34:
	.string	"IRQ_NUMBER_MAX"
.LASF89:
	.string	"HAL_EINT_NUMBER_40"
.LASF90:
	.string	"HAL_EINT_NUMBER_41"
.LASF91:
	.string	"HAL_EINT_NUMBER_42"
.LASF92:
	.string	"HAL_EINT_NUMBER_43"
.LASF93:
	.string	"HAL_EINT_NUMBER_44"
.LASF94:
	.string	"HAL_EINT_NUMBER_45"
.LASF95:
	.string	"HAL_EINT_NUMBER_46"
.LASF96:
	.string	"HAL_EINT_NUMBER_47"
.LASF143:
	.string	"HAL_HW_SEMAPHORE_STATUS_OK"
.LASF248:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF43:
	.string	"GPT_IRQ_EN"
.LASF141:
	.string	"HAL_HW_SEMAPHORE_STATUS_GIVE_ERROR"
.LASF304:
	.string	"pka_share_tx_buf_init"
.LASF116:
	.string	"HAL_HW_SEMAPHORE_ID_10"
.LASF292:
	.string	"pka_tx_buf_is_empty"
.LASF15:
	.string	"uint32_t"
.LASF239:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF199:
	.string	"hid_tx_buf_payload_offset"
.LASF186:
	.string	"CurrentReportRate"
.LASF275:
	.string	"pHidTx"
.LASF253:
	.string	"g_pPkaRtInfo"
.LASF24:
	.string	"UART_DMA_IRQn"
.LASF220:
	.string	"t_pka_share_tx_hid_buf_ctl_ptr"
.LASF243:
	.string	"DBG_PIN_MAX"
.LASF159:
	.string	"pka_share_DLIST_STRU"
.LASF252:
	.string	"g_riscv_ccni_irq_occur"
.LASF2:
	.string	"long long unsigned int"
.LASF285:
	.string	"file"
.LASF161:
	.string	"pka_share_dlist_stru"
.LASF246:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF169:
	.string	"common"
.LASF204:
	.string	"cb_type"
.LASF309:
	.string	"pka_share_tx_init"
.LASF172:
	.string	"POFlow_ptr"
.LASF234:
	.string	"ccm_pka_share"
.LASF151:
	.string	"PKA_SHARE_ENABLE"
.LASF200:
	.string	"hid_tx_status_ptr"
.LASF155:
	.string	"BUFFER_PUSH_TO_HWMAC"
.LASF140:
	.string	"HAL_HW_SEMAPHORE_STATUS_INVALID_PARAMETER"
.LASF193:
	.string	"enable"
.LASF19:
	.string	"KEYSCAN_IRQn"
.LASF281:
	.string	"search_start_idx"
.LASF49:
	.string	"HAL_EINT_NUMBER_0"
.LASF279:
	.string	"pka_share_get_hid_tx_ptr"
.LASF51:
	.string	"HAL_EINT_NUMBER_2"
.LASF52:
	.string	"HAL_EINT_NUMBER_3"
.LASF53:
	.string	"HAL_EINT_NUMBER_4"
.LASF54:
	.string	"HAL_EINT_NUMBER_5"
.LASF55:
	.string	"HAL_EINT_NUMBER_6"
.LASF56:
	.string	"HAL_EINT_NUMBER_7"
.LASF57:
	.string	"HAL_EINT_NUMBER_8"
.LASF58:
	.string	"HAL_EINT_NUMBER_9"
.LASF206:
	.string	"bt_info"
.LASF45:
	.string	"GPT_IRQ_ACK"
.LASF126:
	.string	"HAL_HW_SEMAPHORE_ID_20"
.LASF152:
	.string	"pka_share_enable_t"
.LASF242:
	.string	"DBG_PIN_USB_TX"
.LASF301:
	.string	"pka_tx_buf_set_hid_data_len"
.LASF129:
	.string	"HAL_HW_SEMAPHORE_ID_23"
.LASF263:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF305:
	.string	"offset"
.LASF134:
	.string	"HAL_HW_SEMAPHORE_ID_28"
.LASF181:
	.string	"hwmt_last_anchor_phase_ptr"
.LASF211:
	.string	"_Bool"
.LASF187:
	.string	"mp_version"
.LASF319:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF302:
	.string	"pka_tx_buf_get_data_len"
.LASF296:
	.string	"pka_tx_buf_clear_buf_valid"
.LASF36:
	.string	"SW_CG"
.LASF224:
	.string	"EINT_COUNTER_NUMBER_1"
.LASF226:
	.string	"EINT_COUNTER_NUMBER_3"
.LASF227:
	.string	"EINT_COUNTER_NUMBER_4"
.LASF190:
	.string	"pka_share_bt_info_rt_ptr"
.LASF198:
	.string	"hid_tx_buf_queue_header_size"
.LASF282:
	.string	"search_cnt"
.LASF241:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF235:
	.string	"DBG_PIN_SPI_CB"
.LASF315:
	.string	"take_times"
.LASF12:
	.string	"char"
.LASF278:
	.string	"pka_share_push_hid_tx_ptr"
.LASF13:
	.string	"uint8_t"
.LASF272:
	.string	"pHidTxPtrCandidate"
.LASF288:
	.string	"active_state"
.LASF39:
	.string	"GPT_CON"
.LASF164:
	.string	"pka_share_OSMQ"
.LASF16:
	.string	"SW_IRQn"
.LASF136:
	.string	"HAL_HW_SEMAPHORE_ID_30"
.LASF185:
	.string	"TxRxDataRate"
.LASF284:
	.string	"pka_share_tx_ctrl_init"
.LASF166:
	.string	"hwmt_pico_offset_ptr"
.LASF75:
	.string	"HAL_EINT_NUMBER_26"
.LASF219:
	.string	"t_pka_share_tx_hid_buf_ctl"
.LASF98:
	.string	"HAL_EINT_UART_1_RX"
.LASF317:
	.string	"__modsi3"
.LASF249:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF165:
	.string	"flag_ptr"
.LASF266:
	.string	"hal_hw_semaphore_take"
.LASF314:
	.string	"pka_share_hw_semaphore_take"
.LASF10:
	.string	"long long int"
.LASF117:
	.string	"HAL_HW_SEMAPHORE_ID_11"
.LASF118:
	.string	"HAL_HW_SEMAPHORE_ID_12"
.LASF119:
	.string	"HAL_HW_SEMAPHORE_ID_13"
.LASF120:
	.string	"HAL_HW_SEMAPHORE_ID_14"
.LASF121:
	.string	"HAL_HW_SEMAPHORE_ID_15"
.LASF122:
	.string	"HAL_HW_SEMAPHORE_ID_16"
.LASF123:
	.string	"HAL_HW_SEMAPHORE_ID_17"
.LASF124:
	.string	"HAL_HW_SEMAPHORE_ID_18"
.LASF125:
	.string	"HAL_HW_SEMAPHORE_ID_19"
.LASF209:
	.string	"valid"
.LASF29:
	.string	"I3C0_DMA_IRQn"
.LASF183:
	.string	"acl_active_state_ptr"
.LASF247:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF295:
	.string	"pka_hid_tx_pkt_p"
.LASF174:
	.string	"CurTxPtr"
.LASF299:
	.string	"pka_tx_buf_set_hid_pdu_len"
.LASF146:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF173:
	.string	"pka_share_bt_info_le"
.LASF259:
	.string	"share_buffer_hw_semaphore_take"
.LASF179:
	.string	"hwmt_cur_idx_ptr"
.LASF31:
	.string	"IRQ_GEN_IRQn"
.LASF20:
	.string	"UART_IRQn"
.LASF139:
	.string	"hal_hw_semaphore_id_t"
.LASF238:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF44:
	.string	"GPT_IRQ_STA"
.LASF311:
	.string	"size"
.LASF127:
	.string	"HAL_HW_SEMAPHORE_ID_21"
.LASF128:
	.string	"HAL_HW_SEMAPHORE_ID_22"
.LASF192:
	.string	"pka_share_bt_info"
.LASF130:
	.string	"HAL_HW_SEMAPHORE_ID_24"
.LASF131:
	.string	"HAL_HW_SEMAPHORE_ID_25"
.LASF132:
	.string	"HAL_HW_SEMAPHORE_ID_26"
.LASF133:
	.string	"HAL_HW_SEMAPHORE_ID_27"
.LASF150:
	.string	"PKA_SHARE_DISABLE"
.LASF135:
	.string	"HAL_HW_SEMAPHORE_ID_29"
.LASF106:
	.string	"HAL_HW_SEMAPHORE_ID_0"
.LASF107:
	.string	"HAL_HW_SEMAPHORE_ID_1"
.LASF108:
	.string	"HAL_HW_SEMAPHORE_ID_2"
.LASF109:
	.string	"HAL_HW_SEMAPHORE_ID_3"
.LASF110:
	.string	"HAL_HW_SEMAPHORE_ID_4"
.LASF111:
	.string	"HAL_HW_SEMAPHORE_ID_5"
.LASF112:
	.string	"HAL_HW_SEMAPHORE_ID_6"
.LASF113:
	.string	"HAL_HW_SEMAPHORE_ID_7"
.LASF114:
	.string	"HAL_HW_SEMAPHORE_ID_8"
.LASF115:
	.string	"HAL_HW_SEMAPHORE_ID_9"
.LASF81:
	.string	"HAL_EINT_NUMBER_32"
.LASF32:
	.string	"USB_IRQn"
.LASF83:
	.string	"HAL_EINT_NUMBER_34"
.LASF84:
	.string	"HAL_EINT_NUMBER_35"
.LASF85:
	.string	"HAL_EINT_NUMBER_36"
.LASF308:
	.string	"unit_size"
.LASF153:
	.string	"BUFFER_FREE"
.LASF156:
	.string	"pka_share_tx_hud_buffer_state_t"
.LASF221:
	.string	"pka_share_ptr"
.LASF316:
	.string	"__umodsi3"
.LASF214:
	.string	"HidTxBuf"
.LASF168:
	.string	"pka_share_bt_info_common"
.LASF11:
	.string	"long double"
.LASF137:
	.string	"HAL_HW_SEMAPHORE_ID_31"
.LASF138:
	.string	"HAL_HW_SEMAPHORE_ID_MAX"
.LASF14:
	.string	"uint16_t"
.LASF320:
	.string	"IRQn"
.LASF208:
	.string	"pPtr"
.LASF176:
	.string	"CandiTxPtr"
.LASF203:
	.string	"hid_tx_buf_num"
.LASF22:
	.string	"RTC_IRQn"
.LASF300:
	.string	"pka_tx_buf_get_pdu_len"
.LASF7:
	.string	"short int"
.LASF201:
	.string	"hid_forced_nack_status_ptr"
.LASF148:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF175:
	.string	"NextTxPtr"
.LASF8:
	.string	"long int"
.LASF262:
	.string	"hid_express_dbg_inc_pka_acl_cnt"
.LASF17:
	.string	"LED_IRQn"
.LASF267:
	.string	"pka_share_get_current_report_rate"
.LASF245:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF290:
	.string	"pka_flag_set_loading"
.LASF50:
	.string	"HAL_EINT_NUMBER_1"
.LASF27:
	.string	"EINT_IRQn"
.LASF30:
	.string	"SPI_MST0_IRQn"
.LASF23:
	.string	"GPT_IRQn"
.LASF195:
	.string	"hid_tx_buf_sending_queue"
.LASF196:
	.string	"hid_tx_buf_ack_pending_queue"
.LASF287:
	.string	"pTxPtr"
.LASF42:
	.string	"GPT_CLK"
.LASF257:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF205:
	.string	"req_rscv_ctl_int"
.LASF41:
	.string	"GPT_CLR"
.LASF104:
	.string	"HAL_EINT_RESERVED"
.LASF212:
	.string	"t_pka_share_tx_hid"
.LASF149:
	.string	"pka_share_callback_type_t"
.LASF170:
	.string	"NextTxPtr0"
.LASF171:
	.string	"NextTxPtr1"
.LASF277:
	.string	"pka_share_tx_forward_prepare_rtt0"
.LASF307:
	.string	"pka_share_tx_buf_get_by_idx"
.LASF38:
	.string	"GPT_CON_CELLS"
.LASF188:
	.string	"max_pdu_len_ptr"
.LASF9:
	.string	"long unsigned int"
.LASF270:
	.string	"timestamp_key_submitted"
.LASF289:
	.string	"pka_active_state_match"
.LASF271:
	.string	"pLeAclTxPtrCandidate"
.LASF160:
	.string	"pka_share_DLIST_HEAD"
.LASF207:
	.string	"pka_share_info"
.LASF274:
	.string	"pPkaShareTxHidCtl"
.LASF310:
	.string	"type"
.LASF4:
	.string	"unsigned char"
.LASF254:
	.string	"pka_cb_type"
.LASF35:
	.string	"MODE"
.LASF233:
	.string	"EINT_COUNTER_NUMBER_MUX"
.LASF72:
	.string	"HAL_EINT_NUMBER_23"
.LASF210:
	.string	"state"
.LASF293:
	.string	"pka_tx_buf_remain_length"
.LASF213:
	.string	"t_pka_share_tx_hid_ptr"
.LASF265:
	.string	"hal_hw_semaphore_give"
.LASF260:
	.string	"hid_express_dbg_inc_pka_hid_drop_cnt"
.LASF182:
	.string	"hwmt_tpollgo_ptr"
.LASF184:
	.string	"MaxHidTxPktByRR"
.LASF28:
	.string	"I3C0_IRQn"
.LASF97:
	.string	"HAL_EINT_UART_0_RX"
.LASF264:
	.string	"light_assert"
.LASF312:
	.string	"pka_share_hw_semaphore_give"
.LASF298:
	.string	"pka_tx_buf_is_valid"
.LASF147:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF154:
	.string	"BUFFER_ALLC_BY_APP"
.LASF306:
	.string	"pka_share_tx_buf_get_payload"
.LASF6:
	.string	"signed char"
.LASF177:
	.string	"HidTxPktPtr"
.LASF5:
	.string	"short unsigned int"
.LASF223:
	.string	"EINT_COUNTER_NUMBER_0"
.LASF237:
	.string	"DBG_PIN_NACK"
.LASF225:
	.string	"EINT_COUNTER_NUMBER_2"
.LASF142:
	.string	"HAL_HW_SEMAPHORE_STATUS_TAKE_ERROR"
.LASF222:
	.string	"pka_share_tx_hid_ctl"
.LASF228:
	.string	"EINT_COUNTER_NUMBER_5"
.LASF229:
	.string	"EINT_COUNTER_NUMBER_6"
.LASF230:
	.string	"EINT_COUNTER_NUMBER_7"
.LASF231:
	.string	"EINT_COUNTER_NUMBER_8"
.LASF232:
	.string	"EINT_COUNTER_NUMBER_9"
.LASF162:
	.string	"pka_share_osmq_stru"
.LASF103:
	.string	"HAL_EINT_LPCOMP"
.LASF258:
	.string	"share_buffer_hw_semaphore_give"
.LASF178:
	.string	"EmptyPktPtr"
.LASF47:
	.string	"GPT_COMPARE"
.LASF189:
	.string	"pka_share_bt_info_rt"
.LASF283:
	.string	"pka_share_updt_hid_tx_ptr"
.LASF59:
	.string	"HAL_EINT_NUMBER_10"
.LASF60:
	.string	"HAL_EINT_NUMBER_11"
.LASF61:
	.string	"HAL_EINT_NUMBER_12"
.LASF62:
	.string	"HAL_EINT_NUMBER_13"
.LASF63:
	.string	"HAL_EINT_NUMBER_14"
.LASF64:
	.string	"HAL_EINT_NUMBER_15"
.LASF65:
	.string	"HAL_EINT_NUMBER_16"
.LASF66:
	.string	"HAL_EINT_NUMBER_17"
.LASF67:
	.string	"HAL_EINT_NUMBER_18"
.LASF68:
	.string	"HAL_EINT_NUMBER_19"
.LASF18:
	.string	"QDEC_IRQn"
.LASF46:
	.string	"GPT_COUNT"
.LASF191:
	.string	"pka_share_bt_info_rtt"
.LASF291:
	.string	"value"
.LASF273:
	.string	"pPkaCandTxPtr"
.LASF313:
	.string	"hw_sem_id"
.LASF217:
	.string	"HidTxBufAllcNum"
.LASF318:
	.string	"__mulsi3"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/pka_share/src/pka_share.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
