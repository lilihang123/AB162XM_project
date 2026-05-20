	.file	"riscv_hid_express.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express.c"
	.section	.text.hid_express_get_hid_flag,"ax",@progbits
	.align	1
	.globl	hid_express_get_hid_flag
	.hidden	hid_express_get_hid_flag
	.type	hid_express_get_hid_flag, @function
hid_express_get_hid_flag:
.LFB16:
	.file 1 "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express.c"
	.loc 1 174 1
	.cfi_startproc
	.loc 1 175 5
	.loc 1 176 1 is_stmt 0
	lw	a0,hid_flags
	ret
	.cfi_endproc
.LFE16:
	.size	hid_express_get_hid_flag, .-hid_express_get_hid_flag
	.section	.text.hid_express_get_outgoing_data,"ax",@progbits
	.align	1
	.globl	hid_express_get_outgoing_data
	.hidden	hid_express_get_outgoing_data
	.type	hid_express_get_outgoing_data, @function
hid_express_get_outgoing_data:
.LFB17:
	.loc 1 179 1 is_stmt 1
	.cfi_startproc
	.loc 1 180 5
	.loc 1 181 1 is_stmt 0
	lla	a0,outgoing_data
	ret
	.cfi_endproc
.LFE17:
	.size	hid_express_get_outgoing_data, .-hid_express_get_outgoing_data
	.section	.text.hid_express_get_get_tx_result,"ax",@progbits
	.align	1
	.globl	hid_express_get_get_tx_result
	.hidden	hid_express_get_get_tx_result
	.type	hid_express_get_get_tx_result, @function
hid_express_get_get_tx_result:
.LFB18:
	.loc 1 184 1 is_stmt 1
	.cfi_startproc
	.loc 1 185 5
	.loc 1 186 1 is_stmt 0
	lw	a0,last_tx_result
	ret
	.cfi_endproc
.LFE18:
	.size	hid_express_get_get_tx_result, .-hid_express_get_get_tx_result
	.section	.text.hid_express_get_previous_tx_result,"ax",@progbits
	.align	1
	.globl	hid_express_get_previous_tx_result
	.hidden	hid_express_get_previous_tx_result
	.type	hid_express_get_previous_tx_result, @function
hid_express_get_previous_tx_result:
.LFB19:
	.loc 1 189 1 is_stmt 1
	.cfi_startproc
	.loc 1 190 5
	.loc 1 191 1 is_stmt 0
	lw	a0,previous_tx_result
	ret
	.cfi_endproc
.LFE19:
	.size	hid_express_get_previous_tx_result, .-hid_express_get_previous_tx_result
	.section	.text.hid_express_get_outgpoig_report_result,"ax",@progbits
	.align	1
	.globl	hid_express_get_outgpoig_report_result
	.hidden	hid_express_get_outgpoig_report_result
	.type	hid_express_get_outgpoig_report_result, @function
hid_express_get_outgpoig_report_result:
.LFB21:
	.loc 1 519 1 is_stmt 1
	.cfi_startproc
	.loc 1 520 5
	.loc 1 521 1 is_stmt 0
	lw	a0,report_send_result
	ret
	.cfi_endproc
.LFE21:
	.size	hid_express_get_outgpoig_report_result, .-hid_express_get_outgpoig_report_result
	.section	.text.hid_express_report_go_update,"ax",@progbits
	.align	1
	.globl	hid_express_report_go_update
	.hidden	hid_express_report_go_update
	.type	hid_express_report_go_update, @function
hid_express_report_go_update:
.LFB22:
	.loc 1 524 1 is_stmt 1
	.cfi_startproc
.LVL0:
	.loc 1 525 5
	.loc 1 525 15 is_stmt 0
	sw	a0,report_go,a5
	.loc 1 526 1
	ret
	.cfi_endproc
.LFE22:
	.size	hid_express_report_go_update, .-hid_express_report_go_update
	.section	.text.hid_express_prepare_X_Y,"ax",@progbits
	.align	1
	.globl	hid_express_prepare_X_Y
	.hidden	hid_express_prepare_X_Y
	.type	hid_express_prepare_X_Y, @function
hid_express_prepare_X_Y:
.LFB23:
	.loc 1 530 1 is_stmt 1
	.cfi_startproc
.LVL1:
	.loc 1 531 5
	.loc 1 534 5
	.loc 1 530 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	sw	s0,8(sp)
	sw	s1,4(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 530 1
	mv	s0,a0
	.loc 1 534 5
	call	rv_fake_report_fake_report
.LVL2:
	.loc 1 537 5 is_stmt 1
	.loc 1 540 5 is_stmt 0
	mv	a0,s0
	.loc 1 537 15
	sw	zero,report_go,a5
	.loc 1 540 5 is_stmt 1
	call	key_remap_frontend_process_xy
.LVL3:
	.loc 1 543 5
	.loc 1 543 7 is_stmt 0
	lw	a5,16(s0)
	beq	a5,zero,.L8
	.loc 1 544 9 is_stmt 1
	.loc 1 544 21 is_stmt 0
	lla	a4,dbg
	lw	a5,0(a4)
	addi	a5,a5,1
	sw	a5,0(a4)
.L8:
	.loc 1 547 5 is_stmt 1
	.loc 1 547 8 is_stmt 0
	lw	a5,8(s0)
	bne	a5,zero,.L9
	.loc 1 547 22 discriminator 1
	lw	a5,12(s0)
	beq	a5,zero,.L10
.L9:
	.loc 1 549 9 is_stmt 1
	.loc 1 549 22 is_stmt 0
	lla	a4,dbg
	lw	a5,4(a4)
	addi	a5,a5,1
	sw	a5,4(a4)
	.loc 1 550 9 is_stmt 1
.L13:
	.loc 1 530 1 is_stmt 0
	li	a0,1
.L11:
	.loc 1 550 19
	lla	s1,report_go
	sw	a0,0(s1)
	.loc 1 567 5 is_stmt 1
	mv	a1,sp
	li	a0,18
	call	hal_gpio_get_input
.LVL4:
	.loc 1 568 5
	.loc 1 568 7 is_stmt 0
	lw	a5,0(sp)
	bne	a5,zero,.L15
	.loc 1 570 9 is_stmt 1
	.loc 1 570 27 is_stmt 0
	lla	a4,dbg
	lw	a5,24(a4)
	addi	a5,a5,1
	sw	a5,24(a4)
.L15:
	.loc 1 574 5 is_stmt 1
	.loc 1 574 8 is_stmt 0
	lw	a5,0(s1)
	bne	a5,zero,.L16
	.loc 1 574 19 discriminator 1
	lw	a5,last_tx_result
	bne	a5,zero,.L17
	.loc 1 574 45 discriminator 2
	lw	a5,report_go_previous
	beq	a5,zero,.L17
.L16:
	.loc 1 576 9 is_stmt 1
	.loc 1 576 25 is_stmt 0
	lw	a5,hid_flags
	andi	a3,a5,144
	.loc 1 576 12
	li	a4,144
	bne	a3,a4,.L18
	.loc 1 577 13 is_stmt 1
	lw	a3,dongle_scenario
	lw	a2,this_tx_idx
	lw	a1,last_tx_result
	mv	a0,s0
	call	hid_express_2_4G_x_y_data_prepare
.LVL5:
.L17:
	.loc 1 590 5
	.loc 1 591 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL6:
	lw	s1,4(sp)
	.cfi_restore 9
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL7:
.L10:
	.cfi_restore_state
	.loc 1 555 9 is_stmt 1
	.loc 1 555 11 is_stmt 0
	lw	a5,last_tx_result
	beq	a5,zero,.L12
	.loc 1 555 28 discriminator 1
	lw	a5,report_go_previous
	bne	a5,zero,.L13
.L12:
	.loc 1 555 54 discriminator 3
	call	hid_express_x_y_buf_has_data
.LVL8:
	.loc 1 555 51 discriminator 1
	bne	a0,zero,.L13
	j	.L11
.L18:
	.loc 1 580 14 is_stmt 1
	.loc 1 580 30 is_stmt 0
	andi	a4,a5,92
	.loc 1 580 17
	li	a3,92
	bne	a4,a3,.L19
	.loc 1 581 13 is_stmt 1
	li	a3,1
	lw	a2,this_tx_idx
	lw	a1,last_tx_result
	mv	a0,s0
	call	hid_express_bt_x_y_data_prepare
.LVL9:
	j	.L17
.L19:
	.loc 1 584 14
	.loc 1 584 28 is_stmt 0
	andi	a5,a5,32
	.loc 1 584 17
	beq	a5,zero,.L17
	.loc 1 585 13 is_stmt 1
	lw	a2,this_tx_idx
	lw	a1,last_tx_result
	mv	a0,s0
	call	hid_express_usb_x_y_data_prepare
.LVL10:
	j	.L17
	.cfi_endproc
.LFE23:
	.size	hid_express_prepare_X_Y, .-hid_express_prepare_X_Y
	.section	.text.hid_express_send,"ax",@progbits
	.align	1
	.globl	hid_express_send
	.hidden	hid_express_send
	.type	hid_express_send, @function
hid_express_send:
.LFB24:
	.loc 1 648 1
	.cfi_startproc
.LVL11:
	.loc 1 649 5
	.loc 1 650 5
	.loc 1 648 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	a1,0(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	.loc 1 655 5
	lw	a1,16(a0)
.LVL12:
	lw	a0,4(a0)
.LVL13:
	.loc 1 650 27
	li	a5,8
	.loc 1 648 1
	sw	ra,12(sp)
	sw	s1,4(sp)
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 650 27
	lla	s1,key_queue_push_result
	sw	a5,0(s1)
	.loc 1 655 5 is_stmt 1
	call	key_remap_update_key_status
.LVL14:
	.loc 1 659 5
	mv	a0,s0
	call	key_remap_frontend_process
.LVL15:
	.loc 1 665 5
	.loc 1 665 9 is_stmt 0
	lla	a5,previous_key_status
	.loc 1 665 39
	lw	a4,4(s0)
	.loc 1 665 8
	lw	a3,0(a5)
	lw	a2,0(sp)
	beq	a4,a3,.L37
	.loc 1 666 9 is_stmt 1
	.loc 1 666 29 is_stmt 0
	sw	a4,0(a5)
	.loc 1 667 9 is_stmt 1
	.loc 1 667 26 is_stmt 0
	lla	a4,dbg
	lw	a5,28(a4)
	addi	a5,a5,1
	sw	a5,28(a4)
.L37:
	.loc 1 670 5 is_stmt 1
.LVL16:
	.loc 1 671 5
	.loc 1 671 29 is_stmt 0
	mv	a1,s0
	lla	a0,kCtrl_k
	sw	a2,0(sp)
.LVL17:
	call	riscv_key_push
.LVL18:
	.loc 1 673 33
	lw	a2,0(sp)
	.loc 1 671 27 discriminator 1
	sw	a0,0(s1)
	.loc 1 673 5 is_stmt 1
	.loc 1 673 33 is_stmt 0
	mv	a1,s0
	lla	a0,kCtrl_k
	call	riscv_key_pop_temperory
.LVL19:
	.loc 1 685 5 is_stmt 1
	.loc 1 685 8 is_stmt 0
	beq	a0,zero,.L38
	.loc 1 685 67 discriminator 2
	lw	a5,16(s0)
	bne	a5,zero,.L38
	.loc 1 685 83 discriminator 3
	lw	a5,20(s0)
	beq	a5,zero,.L39
.L38:
	.loc 1 690 9 is_stmt 1
	.loc 1 690 19 is_stmt 0
	li	a5,1
	lla	a4,report_go
	sw	a5,0(a4)
	.loc 1 691 9 is_stmt 1
	.loc 1 691 27 is_stmt 0
	sw	zero,report_repeat_cnt,a5
.L39:
	.loc 1 693 5 is_stmt 1
	.loc 1 693 9 is_stmt 0
	lla	a5,report_go
	lw	a3,0(a5)
	.loc 1 697 25
	lla	a5,hid_flags
	lw	a5,0(a5)
	lw	s1,pka_active_state_always
	or	s1,a3,s1
	andi	a4,a5,144
	.loc 1 693 19 discriminator 1
	beq	s1,zero,.L40
	.loc 1 695 9 is_stmt 1
	.loc 1 697 9
	.loc 1 697 12 is_stmt 0
	li	a2,144
	bne	a4,a2,.L41
	.loc 1 698 13 is_stmt 1
	lw	a3,dongle_scenario
	lw	a2,this_tx_idx
	lw	a1,last_tx_result
	mv	a0,s0
.LVL20:
	call	hid_express_gaming_data_send
.LVL21:
.L42:
	.loc 1 708 9
	.loc 1 710 9
	.loc 1 710 12 is_stmt 0
	lla	a5,report_go
	lw	s1,0(a5)
	seqz	s1,s1
.LVL22:
.L44:
	.loc 1 739 5 is_stmt 1
	.loc 1 740 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL23:
	mv	a0,s1
	lw	s1,4(sp)
	.cfi_restore 9
.LVL24:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL25:
.L41:
	.cfi_restore_state
	.loc 1 701 14 is_stmt 1
	.loc 1 701 30 is_stmt 0
	andi	a4,a5,92
	.loc 1 701 17
	li	a2,92
	bne	a4,a2,.L43
	.loc 1 702 13 is_stmt 1
	li	a3,1
	lw	a2,this_tx_idx
	lw	a1,last_tx_result
	mv	a0,s0
.LVL26:
	call	hid_express_bt_data_send
.LVL27:
	j	.L42
.LVL28:
.L43:
	.loc 1 705 14
	.loc 1 705 29 is_stmt 0
	andi	a5,a5,32
	.loc 1 705 17
	beq	a5,zero,.L42
	.loc 1 706 13 is_stmt 1
	snez	a3,a3
	lw	a2,this_tx_idx
	lw	a1,last_tx_result
	mv	a0,s0
.LVL29:
	call	hid_express_usb_data_send
.LVL30:
	j	.L42
.LVL31:
.L40:
	.loc 1 715 9
	.loc 1 715 12 is_stmt 0
	li	a3,144
	bne	a4,a3,.L45
	.loc 1 716 13 is_stmt 1
	lw	a0,reliable_tx_ptr
.LVL32:
	call	pka_share_push_hid_tx_ptr
.LVL33:
.L46:
	.loc 1 732 9
	.loc 1 732 24 is_stmt 0
	lla	a5,hid_flags
	lw	a5,0(a5)
	.loc 1 732 11
	li	a4,92
	.loc 1 732 24
	andi	a5,a5,92
	.loc 1 732 11
	beq	a5,a4,.L47
.L48:
	.loc 1 649 14
	li	s1,1
	j	.L44
.LVL34:
.L45:
	.loc 1 725 14 is_stmt 1
	.loc 1 725 29 is_stmt 0
	andi	a5,a5,32
	.loc 1 725 17
	beq	a5,zero,.L46
	.loc 1 726 13 is_stmt 1
	call	hid_express_usb_data_set_report_ready
.LVL35:
	j	.L46
.L47:
	.loc 1 732 136 is_stmt 0 discriminator 1
	call	is_bt_queue_empty
.LVL36:
	.loc 1 732 132 discriminator 1
	bne	a0,zero,.L48
	.loc 1 733 13 is_stmt 1
	li	a3,0
	lw	a2,this_tx_idx
	lw	a1,last_tx_result
	mv	a0,s0
	call	hid_express_bt_data_send
.LVL37:
	.loc 1 734 13
	j	.L44
	.cfi_endproc
.LFE24:
	.size	hid_express_send, .-hid_express_send
	.section	.text.hid_express_entrance,"ax",@progbits
	.align	1
	.globl	hid_express_entrance
	.hidden	hid_express_entrance
	.type	hid_express_entrance, @function
hid_express_entrance:
.LFB20:
	.loc 1 340 1
	.cfi_startproc
.LVL38:
	.loc 1 341 5
	.loc 1 343 5
	.loc 1 343 37 is_stmt 0
	lla	a3,timestamp_spi_cb_start
	lw	a5,0(a3)
	.loc 1 340 1
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	sw	s1,12(sp)
	.loc 1 343 37
	sw	a5,timestamp_spi_cb_start_previous,a4
	.loc 1 344 5 is_stmt 1
	.loc 1 344 72 is_stmt 0
	li	a5,1108672512
	addi	a5,a5,512
	lw	a5,24(a5)
	.loc 1 340 1
	sw	ra,20(sp)
	sw	s0,16(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 347 27
	lw	a4,hid_common
	.loc 1 344 29
	sw	a5,0(a3)
	.loc 1 345 5 is_stmt 1
	.loc 1 347 5
	.loc 1 347 32 is_stmt 0
	lw	a5,72(a4)
	.loc 1 348 37
	lbu	a4,57(a4)
	.loc 1 347 15
	lla	s1,hid_flags
	sw	a5,0(s1)
	.loc 1 348 5 is_stmt 1
	.loc 1 348 37 is_stmt 0
	sw	a4,rr_idx_2_4g,a3
	.loc 1 349 5 is_stmt 1
	.loc 1 352 14 is_stmt 0
	sw	zero,8(sp)
	.loc 1 349 29
	sw	zero,pka_active_state_always,a4
	.loc 1 351 5 is_stmt 1
	.loc 1 352 5
	.loc 1 353 5
.LVL39:
	.loc 1 361 5
	.loc 1 361 19 is_stmt 0
	andi	a5,a5,32
	.loc 1 361 7
	beq	a5,zero,.L63
	.loc 1 362 9 is_stmt 1
	call	hid_express_usb_delay_for_latency
.LVL40:
.L63:
	.loc 1 365 5
	.loc 1 365 9 is_stmt 0
	lla	a5,peripheral_sampling_cb_ptr
	lw	a5,0(a5)
	.loc 1 365 8
	beq	a5,zero,.L64
	.loc 1 366 9 is_stmt 1
	li	a1,0
	li	a0,0
	jalr	a5
.LVL41:
.L64:
	.loc 1 369 5
	.loc 1 369 19 is_stmt 0
	lw	a5,0(s1)
	andi	a5,a5,32
	.loc 1 369 7
	bne	a5,zero,.L65
	.loc 1 371 9 is_stmt 1
	addi	a1,sp,8
	addi	a0,sp,4
	call	pka_spi_callback_pre_process
.LVL42:
.L65:
	.loc 1 375 5
	.loc 1 375 17 is_stmt 0
	lw	a5,8(sp)
	.loc 1 380 24
	lw	a1,0(s1)
	.loc 1 376 20
	lla	s0,last_tx_result
	.loc 1 375 17
	sw	a5,this_tx_idx,a4
	.loc 1 376 5 is_stmt 1
	.loc 1 376 20 is_stmt 0
	sw	zero,last_tx_result,a5
	.loc 1 380 9 is_stmt 1
	.loc 1 380 24 is_stmt 0
	andi	a5,a1,32
	.loc 1 380 12
	beq	a5,zero,.L66
	.loc 1 381 13 is_stmt 1
	.loc 1 381 59 is_stmt 0
	srli	a1,a1,8
	andi	a1,a1,1
	.loc 1 381 28
	sw	a1,0(s0)
	.loc 1 382 13 is_stmt 1
	li	a2,0
.L108:
	.loc 1 387 13 is_stmt 0
	lla	a0,kCtrl_k
	call	rv_hid_exp_key_queue_pre_process
.LVL43:
.L67:
	.loc 1 413 9 is_stmt 1
	.loc 1 413 12 is_stmt 0
	lw	a5,0(s0)
	beq	a5,zero,.L72
	.loc 1 414 13 is_stmt 1
	.loc 1 414 27 is_stmt 0
	lla	a4,dbg
	lw	a5,20(a4)
	addi	a5,a5,1
	sw	a5,20(a4)
.L72:
	.loc 1 418 9 is_stmt 1
	.loc 1 420 13
	.loc 1 421 13
	.loc 1 424 9
	.loc 1 424 13 is_stmt 0
	lla	a5,peripheral_sampling_cb_ptr
	lw	a4,0(a5)
	.loc 1 424 12
	beq	a4,zero,.L73
	.loc 1 425 13 is_stmt 1
	.loc 1 425 29 is_stmt 0
	lla	a3,dbg
	lw	a5,12(a3)
	.loc 1 426 13
	li	a0,1
	lla	a1,outgoing_data
	.loc 1 425 29
	addi	a5,a5,1
	sw	a5,12(a3)
	.loc 1 426 13 is_stmt 1
	jalr	a4
.LVL44:
	.loc 1 428 13
	lla	a0,outgoing_data
	call	hid_express_prepare_X_Y
.LVL45:
.L73:
	.loc 1 439 9
	.loc 1 439 23 is_stmt 0
	lw	a5,0(s1)
	andi	a5,a5,32
	.loc 1 439 11
	beq	a5,zero,.L74
	.loc 1 441 13 is_stmt 1
	call	hid_express_usb_wakeup_cm33_handler
.LVL46:
.L74:
	.loc 1 445 9
	.loc 1 445 13 is_stmt 0
	lla	a5,peripheral_sampling_cb_ptr
	lw	a5,0(a5)
	.loc 1 445 12
	beq	a5,zero,.L75
	.loc 1 446 13 is_stmt 1
	.loc 1 447 13
	lla	a1,outgoing_data
	li	a0,2
	jalr	a5
.LVL47:
	.loc 1 450 13
	.loc 1 450 34 is_stmt 0
	lla	a5,timestamp_spi_cb_start
	lw	a1,0(a5)
	lla	a0,outgoing_data
	call	hid_express_send
.LVL48:
	.loc 1 450 32 discriminator 1
	sw	a0,report_send_result,a5
.L75:
	.loc 1 454 5 is_stmt 1
	.loc 1 454 19 is_stmt 0
	lw	a5,0(s1)
	.loc 1 353 14
	sw	zero,0(sp)
	.loc 1 454 19
	andi	a5,a5,32
	.loc 1 454 7
	bne	a5,zero,.L76
	.loc 1 457 9 is_stmt 1
	.loc 1 457 38 is_stmt 0
	call	pka_spi_callback_post_process
.LVL49:
	sw	a0,0(sp)
.LVL50:
.L76:
	.loc 1 459 9 is_stmt 1
	.loc 1 470 5
	call	key_remap_backend_process
.LVL51:
	.loc 1 487 5
	.loc 1 487 9 is_stmt 0
	lla	a5,peripheral_sampling_cb_ptr
	lw	a5,0(a5)
	.loc 1 487 8
	beq	a5,zero,.L77
	.loc 1 488 9 is_stmt 1
	lla	a1,outgoing_data
	li	a0,3
	jalr	a5
.LVL52:
	.loc 1 489 9
	li	a2,40
	li	a1,0
	lla	a0,outgoing_data
	call	memset
.LVL53:
.L77:
	.loc 1 492 5
	call	hid_express_dbg_check
.LVL54:
	.loc 1 494 5
	.loc 1 494 9 is_stmt 0
	lla	a4,report_go
	.loc 1 494 8
	lw	a5,0(a4)
	beq	a5,zero,.L78
	.loc 1 495 9 is_stmt 1
	.loc 1 495 25 is_stmt 0
	lw	a5,0(s1)
	.loc 1 495 12
	li	a3,144
	.loc 1 495 25
	andi	a5,a5,144
	.loc 1 495 12
	bne	a5,a3,.L78
	.loc 1 496 13 is_stmt 1
	lw	a0,0(s0)
	call	hid_express_2_4g_post_process
.LVL55:
.L78:
	.loc 1 500 5
	lla	a5,timestamp_spi_cb_start
	lw	a1,0(a5)
	lw	a5,0(sp)
	lla	a0,kCtrl_k
	sub	a1,a5,a1
	call	rv_hid_exp_key_queue_post_process
.LVL56:
	.loc 1 502 5
	call	rv_fake_report_post_process
.LVL57:
	.loc 1 505 5
	.loc 1 507 5
	.loc 1 507 24 is_stmt 0
	lla	a4,report_go
	lw	a5,0(a4)
	sw	a5,report_go_previous,a4
	.loc 1 508 5 is_stmt 1
	.loc 1 508 24 is_stmt 0
	lw	a5,0(s0)
	sw	a5,previous_tx_result,a4
	.loc 1 509 5 is_stmt 1
	.loc 1 509 22 is_stmt 0
	lw	a5,tx_buff_num
	sw	a5,last_tx_buff_num,a4
	.loc 1 510 5 is_stmt 1
	.loc 1 511 5
	.loc 1 512 5
	.loc 1 513 5
	j	.L71
.LVL58:
.L66:
	.loc 1 385 14
	.loc 1 385 30 is_stmt 0
	andi	a5,a1,92
	.loc 1 385 17
	li	a4,92
	bne	a5,a4,.L68
	.loc 1 386 13 is_stmt 1
	.loc 1 386 30 is_stmt 0
	call	hid_express_bt_get_tx_result
.LVL59:
	mv	a1,a0
	.loc 1 386 28 discriminator 1
	sw	a0,0(s0)
	.loc 1 387 13 is_stmt 1
	li	a2,2
	j	.L108
.L68:
	.loc 1 390 14
	.loc 1 390 30 is_stmt 0
	andi	a1,a1,144
	.loc 1 390 17
	li	a5,144
	bne	a1,a5,.L69
	.loc 1 394 13 is_stmt 1
	li	a2,1
	lw	a1,previous_tx_result
	lla	a0,kCtrl_k
	call	rv_hid_exp_key_queue_pre_process
.LVL60:
	.loc 1 395 13
	.loc 1 395 30 is_stmt 0
	call	hid_express_gaming_get_tx_status
.LVL61:
	.loc 1 395 28 discriminator 1
	sw	a0,0(s0)
	.loc 1 398 13 is_stmt 1
	.loc 1 398 40 is_stmt 0
	li	a0,1
	call	pka_active_state_match
.LVL62:
	.loc 1 398 94 discriminator 1
	xori	a0,a0,1
	andi	a0,a0,0xff
	sw	a0,pka_active_state_always,a5
	j	.L67
.L69:
	.loc 1 401 13 is_stmt 1
	call	pka_spi_callback_post_process
.LVL63:
	.loc 1 403 13
	.loc 1 403 17 is_stmt 0
	lla	a5,peripheral_sampling_cb_ptr
	lw	a5,0(a5)
	.loc 1 403 16
	beq	a5,zero,.L70
	.loc 1 404 13 is_stmt 1
	li	a1,0
	li	a0,4
	jalr	a5
.LVL64:
.L70:
	.loc 1 407 13
	call	hid_express_dbg_check
.LVL65:
	.loc 1 408 13
	.loc 1 409 13
	.loc 1 410 13
.L71:
	.loc 1 514 2 is_stmt 0
	lw	ra,20(sp)
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	.loc 1 510 28
	sb	zero,g_riscv_ccni_irq_occur,a5
	.loc 1 514 2
	lw	s1,12(sp)
	.cfi_restore 9
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE20:
	.size	hid_express_entrance, .-hid_express_entrance
	.section	.text.hid_express_init_gpio_timestamp_latch,"ax",@progbits
	.align	1
	.globl	hid_express_init_gpio_timestamp_latch
	.hidden	hid_express_init_gpio_timestamp_latch
	.type	hid_express_init_gpio_timestamp_latch, @function
hid_express_init_gpio_timestamp_latch:
.LFB25:
	.loc 1 744 1 is_stmt 1
	.cfi_startproc
	.loc 1 745 5
	.loc 1 744 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 745 5
	call	hal_eint_counter_enable
.LVL66:
	.loc 1 747 5 is_stmt 1
	li	a1,0
	li	a0,5
	call	hal_eint_set_counter_number
.LVL67:
	.loc 1 748 5
	li	a1,1
	li	a0,6
	call	hal_eint_set_counter_number
.LVL68:
	.loc 1 749 5
	li	a1,2
	li	a0,17
	call	hal_eint_set_counter_number
.LVL69:
	.loc 1 750 5
	li	a1,3
	li	a0,23
	call	hal_eint_set_counter_number
.LVL70:
	.loc 1 751 5
	.loc 1 752 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 751 5
	li	a1,4
	.loc 1 752 1
	.loc 1 751 5
	li	a0,24
	.loc 1 752 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 751 5
	tail	hal_eint_set_counter_number
.LVL71:
	.cfi_endproc
.LFE25:
	.size	hid_express_init_gpio_timestamp_latch, .-hid_express_init_gpio_timestamp_latch
	.section	.text.hid_express_init,"ax",@progbits
	.align	1
	.globl	hid_express_init
	.hidden	hid_express_init
	.type	hid_express_init, @function
hid_express_init:
.LFB26:
	.loc 1 755 1 is_stmt 1
	.cfi_startproc
.LVL72:
	.loc 1 758 5
	.loc 1 758 8 is_stmt 0
	beq	a0,zero,.L113
	.loc 1 759 9 is_stmt 1
	.loc 1 755 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 759 36
	sw	a0,peripheral_sampling_cb_ptr,a5
	.loc 1 766 5 is_stmt 1
	call	riscv_pka_init
.LVL73:
	.loc 1 768 5
	li	a2,0
	lla	a1,hid_express_entrance
	li	a0,0
	call	hal_spi_master_register_callback
.LVL74:
	.loc 1 769 5
	call	hid_express_init_gpio_timestamp_latch
.LVL75:
	.loc 1 790 5
	call	hid_express_usb_mode_init
.LVL76:
	.loc 1 791 5
	call	hid_express_gaming_init
.LVL77:
	.loc 1 793 5
	call	hid_express_bt_init
.LVL78:
	.loc 1 795 5
	lla	a0,kCtrl_k
	li	a1,0
	call	init_key_ctrl
.LVL79:
	.loc 1 798 5
	call	key_remap_frontend_init
.LVL80:
	.loc 1 800 5
	call	key_remap_backend_init
.LVL81:
	.loc 1 803 5
	.loc 1 811 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 803 21
	sw	zero,dongle_scenario,a5
	.loc 1 804 5 is_stmt 1
	.loc 1 804 21 is_stmt 0
	li	a5,6
	sb	a5,hid_ctrl,a4
	.loc 1 810 5 is_stmt 1
	.loc 1 810 12 is_stmt 0
	li	a0,0
	.loc 1 811 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL82:
.L113:
	.loc 1 763 16
	li	a0,1
.LVL83:
	.loc 1 811 1
	ret
	.cfi_endproc
.LFE26:
	.size	hid_express_init, .-hid_express_init
	.section	.text.hid_express_dongle_scenario_update,"ax",@progbits
	.align	1
	.globl	hid_express_dongle_scenario_update
	.hidden	hid_express_dongle_scenario_update
	.type	hid_express_dongle_scenario_update, @function
hid_express_dongle_scenario_update:
.LFB27:
	.loc 1 814 1 is_stmt 1
	.cfi_startproc
.LVL84:
	.loc 1 815 5
	.loc 1 815 21 is_stmt 0
	sw	a0,dongle_scenario,a5
	.loc 1 816 1
	ret
	.cfi_endproc
.LFE27:
	.size	hid_express_dongle_scenario_update, .-hid_express_dongle_scenario_update
	.section	.text.hid_express_set_features,"ax",@progbits
	.align	1
	.globl	hid_express_set_features
	.hidden	hid_express_set_features
	.type	hid_express_set_features, @function
hid_express_set_features:
.LFB28:
	.loc 1 819 1 is_stmt 1
	.cfi_startproc
.LVL85:
	.loc 1 820 5
	.loc 1 820 28 is_stmt 0
	sw	a0,hid_exp_feature_option,a5
	.loc 1 821 1
	ret
	.cfi_endproc
.LFE28:
	.size	hid_express_set_features, .-hid_express_set_features
	.section	.text.hid_express_debug_print,"ax",@progbits
	.align	1
	.globl	hid_express_debug_print
	.hidden	hid_express_debug_print
	.type	hid_express_debug_print, @function
hid_express_debug_print:
.LFB29:
	.loc 1 959 1 is_stmt 1
	.cfi_startproc
	.loc 1 960 5
.LVL86:
	.loc 1 962 5
	.loc 1 960 78 is_stmt 0
	lbu	a5,hid_ctrl
	.loc 1 960 69
	addi	a5,a5,16
.LVL87:
	lw	a4,hid_common
	slli	a5,a5,1
.LVL88:
	add	a5,a4,a5
	.loc 1 962 5
	lhu	a1,0(a5)
	.loc 1 959 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 962 5
	lla	a0,kCtrl_k
	.loc 1 959 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 962 5
	call	riscv_hid_express_key_queue_debug_print
.LVL89:
	.loc 1 963 5 is_stmt 1
	.loc 1 973 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 963 5
	tail	rv_hid_exp_delay_printf
.LVL90:
	.cfi_endproc
.LFE29:
	.size	hid_express_debug_print, .-hid_express_debug_print
	.section	.text.hid_express_set_report_rate_idx,"ax",@progbits
	.align	1
	.globl	hid_express_set_report_rate_idx
	.hidden	hid_express_set_report_rate_idx
	.type	hid_express_set_report_rate_idx, @function
hid_express_set_report_rate_idx:
.LFB30:
	.loc 1 976 1 is_stmt 1
	.cfi_startproc
.LVL91:
	.loc 1 977 5
	.loc 1 977 21 is_stmt 0
	andi	a5,a0,0xff
	sb	a5,hid_ctrl,a4
	.loc 1 978 5 is_stmt 1
	.loc 1 978 21 is_stmt 0
	sb	a5,report_rate_pka,a4
	.loc 1 979 5 is_stmt 1
.LBB2:
	.loc 1 979 10
	.loc 1 979 63
	.loc 1 979 223
	mv	a4,a5
	li	a3,1
	lla	a2,msg_id_string.0
	li	a1,1
	lla	a0,log_control_block_rv_exp
.LVL92:
	tail	print_module_msgid_log
.LVL93:
.LBE2:
	.cfi_endproc
.LFE30:
	.size	hid_express_set_report_rate_idx, .-hid_express_set_report_rate_idx
	.section	.text.hid_express_clear_key_pushed,"ax",@progbits
	.align	1
	.globl	hid_express_clear_key_pushed
	.hidden	hid_express_clear_key_pushed
	.type	hid_express_clear_key_pushed, @function
hid_express_clear_key_pushed:
.LFB31:
	.loc 1 983 1
	.cfi_startproc
	.loc 1 987 5
	lla	a0,kCtrl_k
	tail	riscv_key_clear_key_pushed
.LVL94:
	.cfi_endproc
.LFE31:
	.size	hid_express_clear_key_pushed, .-hid_express_clear_key_pushed
	.section	.text.hid_express__push_to_key_queue,"ax",@progbits
	.align	1
	.globl	hid_express__push_to_key_queue
	.hidden	hid_express__push_to_key_queue
	.type	hid_express__push_to_key_queue, @function
hid_express__push_to_key_queue:
.LFB32:
	.loc 1 993 1
	.cfi_startproc
.LVL95:
	.loc 1 995 5
	.loc 1 996 5
	.loc 1 996 26 is_stmt 0
	li	a5,1108672512
	addi	a5,a5,512
	lw	a5,24(a5)
	.loc 1 993 1
	addi	sp,sp,-56
	.cfi_def_cfa_offset 56
	sw	s0,48(sp)
	sw	s1,44(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	mv	s0,a1
	mv	s1,a0
	.loc 1 999 5
	li	a2,40
	li	a1,0
.LVL96:
	addi	a0,sp,4
.LVL97:
	.loc 1 993 1
	sw	ra,52(sp)
	.cfi_offset 1, -4
	.loc 1 996 26
	sw	a5,0(sp)
.LVL98:
	.loc 1 998 5 is_stmt 1
	.loc 1 999 5
	call	memset
.LVL99:
	.loc 1 1003 5
	.loc 1 1003 8 is_stmt 0
	lla	a0,kCtrl_k
	call	is_queue_num_2
.LVL100:
	.loc 1 1003 7 discriminator 1
	beq	a0,zero,.L125
	.loc 1 1004 9 is_stmt 1
	lla	a0,kCtrl_k
	call	riscv_key_pop_confirm
.LVL101:
.L125:
	.loc 1 1009 5
	beq	s1,zero,.L126
	li	a5,1
	beq	s1,a5,.L127
.L128:
	.loc 1 1041 5
	lw	a1,20(sp)
	lw	a0,8(sp)
	call	key_remap_update_key_status
.LVL102:
	.loc 1 1045 5
	call	key_remap_backend_process
.LVL103:
	.loc 1 1048 5
	addi	a0,sp,4
	call	key_remap_frontend_process
.LVL104:
	.loc 1 1049 5
	lw	a2,0(sp)
	addi	a1,sp,4
	lla	a0,kCtrl_k
	call	riscv_key_push
.LVL105:
	.loc 1 1077 1 is_stmt 0
	lw	ra,52(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,48(sp)
	.cfi_restore 8
.LVL106:
	lw	s1,44(sp)
	.cfi_restore 9
.LVL107:
	addi	sp,sp,56
	.cfi_def_cfa_offset 0
.LVL108:
	jr	ra
.LVL109:
.L126:
	.cfi_restore_state
	.loc 1 1020 13 is_stmt 1
	.loc 1 1020 29 is_stmt 0
	sw	s0,8(sp)
	.loc 1 1022 9 is_stmt 1
	j	.L128
.L127:
	.loc 1 1027 13
	.loc 1 1027 30 is_stmt 0
	sw	s0,20(sp)
	.loc 1 1029 9 is_stmt 1
	j	.L128
	.cfi_endproc
.LFE32:
	.size	hid_express__push_to_key_queue, .-hid_express__push_to_key_queue
	.section	.text.hid_express_deinit,"ax",@progbits
	.align	1
	.globl	hid_express_deinit
	.hidden	hid_express_deinit
	.type	hid_express_deinit, @function
hid_express_deinit:
.LFB33:
	.loc 1 1093 1
	.cfi_startproc
	.loc 1 1095 5
	tail	key_remap_backend_deinit
.LVL110:
	.cfi_endproc
.LFE33:
	.size	hid_express_deinit, .-hid_express_deinit
	.section	.text.hid_express_get_report_go_previous,"ax",@progbits
	.align	1
	.globl	hid_express_get_report_go_previous
	.hidden	hid_express_get_report_go_previous
	.type	hid_express_get_report_go_previous, @function
hid_express_get_report_go_previous:
.LFB34:
	.loc 1 1100 1
	.cfi_startproc
	.loc 1 1101 5
	.loc 1 1102 1 is_stmt 0
	lw	a0,report_go_previous
	ret
	.cfi_endproc
.LFE34:
	.size	hid_express_get_report_go_previous, .-hid_express_get_report_go_previous
	.section	.text.hid_express_get_last_report_go,"ax",@progbits
	.align	1
	.globl	hid_express_get_last_report_go
	.hidden	hid_express_get_last_report_go
	.type	hid_express_get_last_report_go, @function
hid_express_get_last_report_go:
.LFB35:
	.loc 1 1105 1 is_stmt 1
	.cfi_startproc
	.loc 1 1106 5
	.loc 1 1107 1 is_stmt 0
	lw	a0,last_report_go
	ret
	.cfi_endproc
.LFE35:
	.size	hid_express_get_last_report_go, .-hid_express_get_last_report_go
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 67
msg_id_string.0:
	.string	"[M:rv_exp C:info F: L: ]: hid_express_set_report_rate_idx rr = %d "
	.hidden	key_queue_push_result
	.globl	key_queue_push_result
	.section	.sdata.key_queue_push_result,"aw"
	.align	2
	.type	key_queue_push_result, @object
	.size	key_queue_push_result, 4
key_queue_push_result:
	.word	8
	.hidden	g_riscv_ccni_irq_occur
	.globl	g_riscv_ccni_irq_occur
	.section	.sbss.g_riscv_ccni_irq_occur,"aw",@nobits
	.type	g_riscv_ccni_irq_occur, @object
	.size	g_riscv_ccni_irq_occur, 1
g_riscv_ccni_irq_occur:
	.zero	1
	.hidden	pka_active_state_always
	.globl	pka_active_state_always
	.section	.sbss.pka_active_state_always,"aw",@nobits
	.align	2
	.type	pka_active_state_always, @object
	.size	pka_active_state_always, 4
pka_active_state_always:
	.zero	4
	.hidden	timestamp_spi_cb_start_previous
	.globl	timestamp_spi_cb_start_previous
	.section	.sbss.timestamp_spi_cb_start_previous,"aw",@nobits
	.align	2
	.type	timestamp_spi_cb_start_previous, @object
	.size	timestamp_spi_cb_start_previous, 4
timestamp_spi_cb_start_previous:
	.zero	4
	.hidden	timestamp_spi_cb_start
	.globl	timestamp_spi_cb_start
	.section	.sbss.timestamp_spi_cb_start,"aw",@nobits
	.align	2
	.type	timestamp_spi_cb_start, @object
	.size	timestamp_spi_cb_start, 4
timestamp_spi_cb_start:
	.zero	4
	.hidden	hid_ctrl
	.globl	hid_ctrl
	.section	.sbss.hid_ctrl,"aw",@nobits
	.align	2
	.type	hid_ctrl, @object
	.size	hid_ctrl, 1
hid_ctrl:
	.zero	1
	.hidden	report_rate_pka
	.globl	report_rate_pka
	.section	.sbss.report_rate_pka,"aw",@nobits
	.type	report_rate_pka, @object
	.size	report_rate_pka, 1
report_rate_pka:
	.zero	1
	.hidden	report_send_result
	.globl	report_send_result
	.section	.sbss.report_send_result,"aw",@nobits
	.align	2
	.type	report_send_result, @object
	.size	report_send_result, 4
report_send_result:
	.zero	4
	.hidden	outgoing_data
	.globl	outgoing_data
	.section	.bss.outgoing_data,"aw",@nobits
	.align	2
	.type	outgoing_data, @object
	.size	outgoing_data, 40
outgoing_data:
	.zero	40
	.hidden	report_repeat_cnt
	.globl	report_repeat_cnt
	.section	.sbss.report_repeat_cnt,"aw",@nobits
	.align	2
	.type	report_repeat_cnt, @object
	.size	report_repeat_cnt, 4
report_repeat_cnt:
	.zero	4
	.hidden	curr_tx_count
	.globl	curr_tx_count
	.section	.sbss.curr_tx_count,"aw",@nobits
	.align	2
	.type	curr_tx_count, @object
	.size	curr_tx_count, 4
curr_tx_count:
	.zero	4
	.hidden	report_go_previous
	.globl	report_go_previous
	.section	.sbss.report_go_previous,"aw",@nobits
	.align	2
	.type	report_go_previous, @object
	.size	report_go_previous, 4
report_go_previous:
	.zero	4
	.hidden	last_report_go
	.globl	last_report_go
	.section	.sbss.last_report_go,"aw",@nobits
	.align	2
	.type	last_report_go, @object
	.size	last_report_go, 4
last_report_go:
	.zero	4
	.hidden	report_go
	.globl	report_go
	.section	.sbss.report_go,"aw",@nobits
	.align	2
	.type	report_go, @object
	.size	report_go, 4
report_go:
	.zero	4
	.section	.sbss.peripheral_sampling_cb_ptr,"aw",@nobits
	.align	2
	.type	peripheral_sampling_cb_ptr, @object
	.size	peripheral_sampling_cb_ptr, 4
peripheral_sampling_cb_ptr:
	.zero	4
	.hidden	hid_exp_feature_option
	.globl	hid_exp_feature_option
	.section	.sbss.hid_exp_feature_option,"aw",@nobits
	.align	2
	.type	hid_exp_feature_option, @object
	.size	hid_exp_feature_option, 4
hid_exp_feature_option:
	.zero	4
	.hidden	rr_idx_2_4g
	.globl	rr_idx_2_4g
	.section	.sdata.rr_idx_2_4g,"aw"
	.align	2
	.type	rr_idx_2_4g, @object
	.size	rr_idx_2_4g, 4
rr_idx_2_4g:
	.word	7
	.hidden	previous_key_status
	.globl	previous_key_status
	.section	.sbss.previous_key_status,"aw",@nobits
	.align	2
	.type	previous_key_status, @object
	.size	previous_key_status, 4
previous_key_status:
	.zero	4
	.hidden	dongle_scenario
	.globl	dongle_scenario
	.section	.sbss.dongle_scenario,"aw",@nobits
	.align	2
	.type	dongle_scenario, @object
	.size	dongle_scenario, 4
dongle_scenario:
	.zero	4
	.hidden	this_tx_idx
	.globl	this_tx_idx
	.section	.sbss.this_tx_idx,"aw",@nobits
	.align	2
	.type	this_tx_idx, @object
	.size	this_tx_idx, 4
this_tx_idx:
	.zero	4
	.hidden	last_tx_buff_num
	.globl	last_tx_buff_num
	.section	.sbss.last_tx_buff_num,"aw",@nobits
	.align	2
	.type	last_tx_buff_num, @object
	.size	last_tx_buff_num, 4
last_tx_buff_num:
	.zero	4
	.hidden	tx_buff_num
	.globl	tx_buff_num
	.section	.sbss.tx_buff_num,"aw",@nobits
	.align	2
	.type	tx_buff_num, @object
	.size	tx_buff_num, 4
tx_buff_num:
	.zero	4
	.hidden	previous_tx_result
	.globl	previous_tx_result
	.section	.sbss.previous_tx_result,"aw",@nobits
	.align	2
	.type	previous_tx_result, @object
	.size	previous_tx_result, 4
previous_tx_result:
	.zero	4
	.hidden	last_tx_result
	.globl	last_tx_result
	.section	.sbss.last_tx_result,"aw",@nobits
	.align	2
	.type	last_tx_result, @object
	.size	last_tx_result, 4
last_tx_result:
	.zero	4
	.hidden	rv_fun_flags
	.globl	rv_fun_flags
	.section	.sbss.rv_fun_flags,"aw",@nobits
	.align	2
	.type	rv_fun_flags, @object
	.size	rv_fun_flags, 4
rv_fun_flags:
	.zero	4
	.hidden	hid_flags
	.globl	hid_flags
	.section	.sbss.hid_flags,"aw",@nobits
	.align	2
	.type	hid_flags, @object
	.size	hid_flags, 4
hid_flags:
	.zero	4
	.hidden	kCtrl_k
	.globl	kCtrl_k
	.section	.bss.kCtrl_k,"aw",@nobits
	.align	2
	.type	kCtrl_k, @object
	.size	kCtrl_k, 168
kCtrl_k:
	.zero	168
	.hidden	log_control_block_mirror_rv_exp
	.globl	log_control_block_mirror_rv_exp
	.section	.log_filter_mirror.rv_exp,"a"
	.align	2
	.type	log_control_block_mirror_rv_exp, @object
	.size	log_control_block_mirror_rv_exp, 7
log_control_block_mirror_rv_exp:
	.string	"rv_exp"
	.hidden	log_control_block_rv_exp
	.globl	log_control_block_rv_exp
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"rv_exp"
	.section	.log_filter.rv_exp,"aw"
	.align	2
	.type	log_control_block_rv_exp, @object
	.size	log_control_block_rv_exp, 28
log_control_block_rv_exp:
	.word	.LC0
	.word	0
	.word	1
	.word	0
	.word	0
	.word	0
	.word	print_module_msgid_log
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpt.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpio.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 8 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 9 "/workdir/airoha/common/applications/hid/inc/hid_common_key_remap.h"
	.file 10 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 11 "/workdir/airoha/common/applications/hid/inc/hid_common.h"
	.file 12 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 13 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 14 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_key_queue_mouse.h"
	.file 15 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 16 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_spi_master.h"
	.file 17 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.file 18 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_eint.h"
	.file 19 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_eint_internal.h"
	.file 20 "/workdir/airoha/common/middleware/airoha/hid_express/inc/rv_hid_exp_delay_printf.h"
	.file 21 "/workdir/airoha/common/middleware/airoha/key_remap/inc/key_remap_backend.h"
	.file 22 "/workdir/airoha/common/middleware/airoha/key_remap/inc/key_remap_frontend.h"
	.file 23 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_bt_mode.h"
	.file 24 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_2_4G_mode.h"
	.file 25 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_usb_mode.h"
	.file 26 "/workdir/airoha/risc-v/middleware/airoha/pka/inc/pka.h"
	.file 27 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_xy_queue.h"
	.file 28 "/workdir/airoha/common/middleware/airoha/hid_express/inc/rv_fake_report.h"
	.file 29 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.file 30 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x2252
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x33
	.4byte	.LASF528
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL13
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x13
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x13
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x13
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x13
	.byte	0x1
	.byte	0x6
	.4byte	.LASF5
	.uleb128 0x13
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x13
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x13
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x13
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x13
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x34
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x2
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0x13
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x35
	.byte	0x4
	.uleb128 0x13
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x16
	.4byte	0x81
	.uleb128 0xc
	.4byte	0x88
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x3
	.byte	0x22
	.byte	0x15
	.4byte	0x3b
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x3
	.byte	0x25
	.byte	0x13
	.4byte	0x42
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x3
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF17
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x34
	.uleb128 0x24
	.4byte	0xb6
	.uleb128 0x16
	.4byte	0xc2
	.uleb128 0x5
	.4byte	.LASF18
	.byte	0x3
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x5
	.4byte	.LASF19
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x24
	.4byte	0xd8
	.uleb128 0x16
	.4byte	0xe4
	.uleb128 0xe
	.4byte	0xb6
	.4byte	0xfe
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xc
	.4byte	0xb6
	.uleb128 0x36
	.4byte	.LASF529
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x1e
	.2byte	0x128
	.byte	0x11
	.4byte	0x189
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x1f
	.byte	0
	.uleb128 0xe
	.4byte	0xc7
	.4byte	0x199
	.uleb128 0xf
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x16
	.4byte	0x189
	.uleb128 0x24
	.4byte	0x199
	.uleb128 0xb
	.byte	0x4
	.byte	0x4
	.byte	0x36
	.4byte	0x1df
	.uleb128 0xa
	.string	"EN"
	.byte	0x4
	.byte	0x37
	.byte	0x1e
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF39
	.byte	0x4
	.byte	0x38
	.byte	0x1e
	.4byte	0xc2
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x4
	.byte	0x39
	.byte	0x1e
	.4byte	0xc2
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF41
	.byte	0x4
	.byte	0x3a
	.byte	0x24
	.4byte	0x19e
	.byte	0x3
	.byte	0
	.uleb128 0x2a
	.byte	0x4
	.byte	0x4
	.byte	0x35
	.4byte	0x200
	.uleb128 0x17
	.4byte	.LASF42
	.byte	0x4
	.byte	0x3b
	.byte	0xb
	.4byte	0x1a3
	.uleb128 0x17
	.4byte	.LASF43
	.byte	0x4
	.byte	0x3c
	.byte	0x1b
	.4byte	0xe4
	.byte	0
	.uleb128 0xb
	.byte	0x20
	.byte	0x4
	.byte	0x34
	.4byte	0x271
	.uleb128 0x2
	.4byte	.LASF44
	.byte	0x4
	.byte	0x3d
	.byte	0x7
	.4byte	0x1df
	.byte	0
	.uleb128 0x2
	.4byte	.LASF45
	.byte	0x4
	.byte	0x3e
	.byte	0x17
	.4byte	0xe4
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x4
	.byte	0x3f
	.byte	0x17
	.4byte	0xe4
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x4
	.byte	0x40
	.byte	0x17
	.4byte	0xe4
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF48
	.byte	0x4
	.byte	0x41
	.byte	0x1d
	.4byte	0xe9
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x4
	.byte	0x42
	.byte	0x17
	.4byte	0xe4
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF50
	.byte	0x4
	.byte	0x43
	.byte	0x17
	.4byte	0xe4
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF51
	.byte	0x4
	.byte	0x44
	.byte	0x17
	.4byte	0xe4
	.byte	0x1c
	.byte	0
	.uleb128 0x5
	.4byte	.LASF52
	.byte	0x4
	.byte	0x45
	.byte	0x3
	.4byte	0x200
	.uleb128 0xe
	.4byte	0xd8
	.4byte	0x28d
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x1a
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.2byte	0x1cd
	.4byte	0x3c1
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x30
	.byte	0
	.uleb128 0x18
	.4byte	.LASF102
	.byte	0x5
	.2byte	0x1ff
	.byte	0x3
	.4byte	0x28d
	.uleb128 0x1a
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.2byte	0x373
	.4byte	0x3ee
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x2
	.byte	0
	.uleb128 0x18
	.4byte	.LASF106
	.byte	0x5
	.2byte	0x377
	.byte	0x3
	.4byte	0x3ce
	.uleb128 0x1a
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.2byte	0x407
	.4byte	0x55f
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF157
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF159
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF162
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF163
	.byte	0x38
	.byte	0
	.uleb128 0x18
	.4byte	.LASF164
	.byte	0x5
	.2byte	0x441
	.byte	0x3
	.4byte	0x3fb
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0xda
	.byte	0xe
	.4byte	0x586
	.uleb128 0x1
	.4byte	.LASF165
	.byte	0
	.uleb128 0x1
	.4byte	.LASF166
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF167
	.byte	0x6
	.byte	0xdd
	.byte	0x3
	.4byte	0x56c
	.uleb128 0xd
	.byte	0x5
	.4byte	0x65
	.byte	0x6
	.byte	0xe1
	.byte	0xe
	.4byte	0x5b8
	.uleb128 0x11
	.4byte	.LASF168
	.sleb128 -3
	.uleb128 0x11
	.4byte	.LASF169
	.sleb128 -2
	.uleb128 0x11
	.4byte	.LASF170
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF171
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF172
	.byte	0x6
	.byte	0xe6
	.byte	0x3
	.4byte	0x592
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0x7
	.byte	0x50
	.byte	0xe
	.4byte	0x608
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
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF180
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0x8
	.byte	0
	.uleb128 0xb
	.byte	0xa
	.byte	0x7
	.byte	0x5e
	.4byte	0x62b
	.uleb128 0x2
	.4byte	.LASF182
	.byte	0x7
	.byte	0x60
	.byte	0xe
	.4byte	0xcc
	.byte	0
	.uleb128 0xa
	.string	"pin"
	.byte	0x7
	.byte	0x61
	.byte	0xd
	.4byte	0x62b
	.byte	0x2
	.byte	0
	.uleb128 0xe
	.4byte	0xb6
	.4byte	0x63b
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.4byte	.LASF183
	.byte	0x7
	.byte	0x62
	.byte	0x2
	.4byte	0x608
	.uleb128 0x13
	.byte	0x1
	.byte	0x2
	.4byte	.LASF184
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x31
	.byte	0x1
	.4byte	0x68c
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF188
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF189
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF190
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF191
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF192
	.byte	0x7
	.byte	0
	.uleb128 0xb
	.byte	0x2
	.byte	0x8
	.byte	0x3f
	.4byte	0x6af
	.uleb128 0x2
	.4byte	.LASF193
	.byte	0x8
	.byte	0x41
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF194
	.byte	0x8
	.byte	0x42
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF195
	.byte	0x8
	.byte	0x44
	.byte	0x2
	.4byte	0x68c
	.uleb128 0x2b
	.2byte	0x11c
	.2byte	0x109
	.byte	0xd
	.4byte	0x6df
	.uleb128 0x2c
	.4byte	.LASF196
	.2byte	0x10a
	.byte	0x1a
	.4byte	0x6df
	.uleb128 0x37
	.string	"x_y"
	.byte	0x9
	.2byte	0x10c
	.byte	0x1a
	.4byte	0x6df
	.byte	0
	.uleb128 0xe
	.4byte	0xd8
	.4byte	0x6ef
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x46
	.byte	0
	.uleb128 0x2d
	.2byte	0x23c
	.2byte	0x105
	.4byte	0x727
	.uleb128 0x1f
	.4byte	.LASF197
	.2byte	0x106
	.byte	0x16
	.4byte	0xcc
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF198
	.2byte	0x107
	.byte	0x16
	.4byte	0xcc
	.byte	0x2
	.uleb128 0x1f
	.4byte	.LASF199
	.2byte	0x108
	.byte	0x16
	.4byte	0x6df
	.byte	0x4
	.uleb128 0x38
	.4byte	0x6bb
	.2byte	0x120
	.byte	0
	.uleb128 0x2b
	.2byte	0x23c
	.2byte	0x103
	.byte	0x5
	.4byte	0x743
	.uleb128 0x2c
	.4byte	.LASF200
	.2byte	0x104
	.byte	0x12
	.4byte	0xd8
	.uleb128 0x39
	.4byte	0x6ef
	.byte	0
	.uleb128 0x2d
	.2byte	0x240
	.2byte	0x101
	.4byte	0x760
	.uleb128 0x1f
	.4byte	.LASF201
	.2byte	0x102
	.byte	0xe
	.4byte	0xd8
	.byte	0
	.uleb128 0x2e
	.4byte	0x727
	.byte	0x4
	.byte	0
	.uleb128 0x18
	.4byte	.LASF202
	.byte	0x9
	.2byte	0x111
	.byte	0x1e
	.4byte	0x743
	.uleb128 0xb
	.byte	0x8
	.byte	0xa
	.byte	0x50
	.4byte	0x7bc
	.uleb128 0x2
	.4byte	.LASF203
	.byte	0xa
	.byte	0x51
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0xa
	.string	"k"
	.byte	0xa
	.byte	0x52
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.uleb128 0xa
	.string	"x"
	.byte	0xa
	.byte	0x53
	.byte	0xd
	.4byte	0x9e
	.byte	0x2
	.uleb128 0xa
	.string	"y"
	.byte	0xa
	.byte	0x54
	.byte	0xd
	.4byte	0x9e
	.byte	0x4
	.uleb128 0xa
	.string	"z1"
	.byte	0xa
	.byte	0x55
	.byte	0xc
	.4byte	0x92
	.byte	0x6
	.uleb128 0xa
	.string	"z2"
	.byte	0xa
	.byte	0x56
	.byte	0xc
	.4byte	0x92
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.4byte	.LASF204
	.byte	0xa
	.byte	0x57
	.byte	0x1f
	.4byte	0x76d
	.uleb128 0xb
	.byte	0x8
	.byte	0xa
	.byte	0x88
	.4byte	0x80e
	.uleb128 0x2
	.4byte	.LASF203
	.byte	0xa
	.byte	0x89
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF205
	.byte	0xa
	.byte	0x8a
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF196
	.byte	0xa
	.byte	0x8b
	.byte	0xd
	.4byte	0xee
	.byte	0x2
	.uleb128 0xa
	.string	"x"
	.byte	0xa
	.byte	0x8c
	.byte	0xd
	.4byte	0x9e
	.byte	0x4
	.uleb128 0xa
	.string	"y"
	.byte	0xa
	.byte	0x8d
	.byte	0xd
	.4byte	0x9e
	.byte	0x6
	.byte	0
	.uleb128 0x5
	.4byte	.LASF206
	.byte	0xa
	.byte	0x8e
	.byte	0x1e
	.4byte	0x7c8
	.uleb128 0xb
	.byte	0x8
	.byte	0xa
	.byte	0x90
	.4byte	0x860
	.uleb128 0x2
	.4byte	.LASF203
	.byte	0xa
	.byte	0x91
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF207
	.byte	0xa
	.byte	0x92
	.byte	0xe
	.4byte	0xcc
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF208
	.byte	0xa
	.byte	0x93
	.byte	0xd
	.4byte	0xb6
	.byte	0x3
	.uleb128 0xa
	.string	"x"
	.byte	0xa
	.byte	0x94
	.byte	0xd
	.4byte	0x9e
	.byte	0x4
	.uleb128 0xa
	.string	"y"
	.byte	0xa
	.byte	0x95
	.byte	0xd
	.4byte	0x9e
	.byte	0x6
	.byte	0
	.uleb128 0x5
	.4byte	.LASF209
	.byte	0xa
	.byte	0x96
	.byte	0x1f
	.4byte	0x81a
	.uleb128 0xe
	.4byte	0xb6
	.4byte	0x87c
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0xb
	.byte	0x8
	.byte	0xa
	.byte	0xa2
	.4byte	0x8b9
	.uleb128 0x2
	.4byte	.LASF203
	.byte	0xa
	.byte	0xa3
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF205
	.byte	0xa
	.byte	0xa4
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF196
	.byte	0xa
	.byte	0xa5
	.byte	0xd
	.4byte	0x86c
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF210
	.byte	0xa
	.byte	0xa6
	.byte	0xd
	.4byte	0xb6
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.4byte	.LASF211
	.byte	0xa
	.byte	0xa7
	.byte	0x1e
	.4byte	0x87c
	.uleb128 0xb
	.byte	0x8
	.byte	0xa
	.byte	0xa9
	.4byte	0x902
	.uleb128 0x2
	.4byte	.LASF203
	.byte	0xa
	.byte	0xaa
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF207
	.byte	0xa
	.byte	0xab
	.byte	0xd
	.4byte	0x902
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF208
	.byte	0xa
	.byte	0xac
	.byte	0xd
	.4byte	0xb6
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF210
	.byte	0xa
	.byte	0xad
	.byte	0xd
	.4byte	0xee
	.byte	0x6
	.byte	0
	.uleb128 0xe
	.4byte	0xb6
	.4byte	0x912
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF212
	.byte	0xa
	.byte	0xae
	.byte	0x1f
	.4byte	0x8c5
	.uleb128 0xe
	.4byte	0xb6
	.4byte	0x92e
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0xb
	.byte	0x2
	.byte	0xb
	.byte	0x49
	.4byte	0x950
	.uleb128 0xa
	.string	"id"
	.byte	0xb
	.byte	0x4b
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF213
	.byte	0xb
	.byte	0x4c
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF214
	.byte	0xb
	.byte	0x4d
	.byte	0x2
	.4byte	0x92e
	.uleb128 0x2a
	.byte	0x8
	.byte	0xb
	.byte	0x53
	.4byte	0x9a1
	.uleb128 0x17
	.4byte	.LASF215
	.byte	0xb
	.byte	0x54
	.byte	0x25
	.4byte	0x7bc
	.uleb128 0x17
	.4byte	.LASF216
	.byte	0xb
	.byte	0x56
	.byte	0x23
	.4byte	0x80e
	.uleb128 0x17
	.4byte	.LASF217
	.byte	0xb
	.byte	0x57
	.byte	0x28
	.4byte	0x860
	.uleb128 0x17
	.4byte	.LASF218
	.byte	0xb
	.byte	0x59
	.byte	0x20
	.4byte	0x8b9
	.uleb128 0x17
	.4byte	.LASF219
	.byte	0xb
	.byte	0x5a
	.byte	0x25
	.4byte	0x912
	.byte	0
	.uleb128 0xb
	.byte	0x8
	.byte	0xb
	.byte	0x4f
	.4byte	0x9b0
	.uleb128 0x2e
	.4byte	0x95c
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF220
	.byte	0xb
	.byte	0x5f
	.byte	0xa
	.4byte	0x9a1
	.uleb128 0xb
	.byte	0x8
	.byte	0xb
	.byte	0x61
	.4byte	0x9df
	.uleb128 0x2
	.4byte	.LASF221
	.byte	0xb
	.byte	0x62
	.byte	0xe
	.4byte	0xd8
	.byte	0
	.uleb128 0x2
	.4byte	.LASF222
	.byte	0xb
	.byte	0x63
	.byte	0xe
	.4byte	0xd8
	.byte	0x4
	.byte	0
	.uleb128 0x5
	.4byte	.LASF223
	.byte	0xb
	.byte	0x67
	.byte	0x2
	.4byte	0x9bc
	.uleb128 0x16
	.4byte	0x9df
	.uleb128 0xb
	.byte	0x3
	.byte	0xb
	.byte	0x69
	.4byte	0xa20
	.uleb128 0x2
	.4byte	.LASF224
	.byte	0xb
	.byte	0x6a
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF225
	.byte	0xb
	.byte	0x6b
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF226
	.byte	0xb
	.byte	0x6c
	.byte	0xd
	.4byte	0xb6
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.4byte	.LASF227
	.byte	0xb
	.byte	0x6d
	.byte	0x3
	.4byte	0x9f0
	.uleb128 0xb
	.byte	0x18
	.byte	0xb
	.byte	0x7e
	.4byte	0xa83
	.uleb128 0x2
	.4byte	.LASF228
	.byte	0xb
	.byte	0x7f
	.byte	0xe
	.4byte	0xd8
	.byte	0
	.uleb128 0x2
	.4byte	.LASF229
	.byte	0xb
	.byte	0x80
	.byte	0xe
	.4byte	0xd8
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF230
	.byte	0xb
	.byte	0x81
	.byte	0xe
	.4byte	0xd8
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF231
	.byte	0xb
	.byte	0x82
	.byte	0xe
	.4byte	0xd8
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF232
	.byte	0xb
	.byte	0x83
	.byte	0x17
	.4byte	0xe4
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF233
	.byte	0xb
	.byte	0x84
	.byte	0xd
	.4byte	0xb6
	.byte	0x14
	.byte	0
	.uleb128 0x5
	.4byte	.LASF234
	.byte	0xb
	.byte	0x94
	.byte	0x3
	.4byte	0xa2c
	.uleb128 0xb
	.byte	0x40
	.byte	0xb
	.byte	0x96
	.4byte	0xb4d
	.uleb128 0x2
	.4byte	.LASF231
	.byte	0xb
	.byte	0x97
	.byte	0xe
	.4byte	0xd8
	.byte	0
	.uleb128 0x2
	.4byte	.LASF235
	.byte	0xb
	.byte	0x98
	.byte	0xe
	.4byte	0xd8
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF236
	.byte	0xb
	.byte	0x9b
	.byte	0x1e
	.4byte	0xb4d
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF237
	.byte	0xb
	.byte	0x9c
	.byte	0xe
	.4byte	0xd8
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF238
	.byte	0xb
	.byte	0x9d
	.byte	0xe
	.4byte	0xd8
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF239
	.byte	0xb
	.byte	0x9f
	.byte	0x1e
	.4byte	0x950
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF240
	.byte	0xb
	.byte	0xa0
	.byte	0x1e
	.4byte	0x950
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF241
	.byte	0xb
	.byte	0xa5
	.byte	0xe
	.4byte	0xd8
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF242
	.byte	0xb
	.byte	0xa6
	.byte	0xe
	.4byte	0xd8
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF243
	.byte	0xb
	.byte	0xae
	.byte	0xe
	.4byte	0xb52
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF244
	.byte	0xb
	.byte	0xb1
	.byte	0xd
	.4byte	0x91e
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF245
	.byte	0xb
	.byte	0xb2
	.byte	0xd
	.4byte	0xb6
	.byte	0x38
	.uleb128 0xa
	.string	"rr"
	.byte	0xb
	.byte	0xbb
	.byte	0x1d
	.4byte	0x6af
	.byte	0x39
	.uleb128 0xa
	.string	"deb"
	.byte	0xb
	.byte	0xbd
	.byte	0x17
	.4byte	0xa20
	.byte	0x3b
	.byte	0
	.uleb128 0xc
	.4byte	0x9eb
	.uleb128 0xe
	.4byte	0xcc
	.4byte	0xb62
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x5
	.4byte	.LASF246
	.byte	0xb
	.byte	0xbf
	.byte	0x3
	.4byte	0xa8f
	.uleb128 0x3a
	.2byte	0x16ec
	.byte	0xb
	.byte	0xc1
	.byte	0x9
	.4byte	0xbbb
	.uleb128 0xa
	.string	"app"
	.byte	0xb
	.byte	0xc3
	.byte	0x1b
	.4byte	0xb62
	.byte	0
	.uleb128 0xa
	.string	"hid"
	.byte	0xb
	.byte	0xc4
	.byte	0x1b
	.4byte	0xa83
	.byte	0x40
	.uleb128 0xa
	.string	"dbg"
	.byte	0xb
	.byte	0xc5
	.byte	0x17
	.4byte	0x63b
	.byte	0x58
	.uleb128 0x2
	.4byte	.LASF247
	.byte	0xb
	.byte	0xc7
	.byte	0x17
	.4byte	0xbbb
	.byte	0x62
	.uleb128 0x3b
	.4byte	.LASF248
	.byte	0xb
	.byte	0xca
	.byte	0x1d
	.4byte	0xbcb
	.2byte	0x16e2
	.byte	0
	.uleb128 0xe
	.4byte	0x760
	.4byte	0xbcb
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0xe
	.4byte	0x9b0
	.4byte	0xbdb
	.uleb128 0xf
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF249
	.byte	0xb
	.byte	0xcc
	.byte	0x3
	.4byte	0xb6e
	.uleb128 0x20
	.4byte	.LASF287
	.byte	0xb
	.byte	0xd2
	.byte	0x19
	.4byte	0xbf3
	.uleb128 0xc
	.4byte	0xbdb
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xc
	.byte	0x37
	.byte	0xe
	.4byte	0xc12
	.uleb128 0x1
	.4byte	.LASF250
	.byte	0
	.uleb128 0x1
	.4byte	.LASF251
	.byte	0x1
	.byte	0
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xc
	.byte	0x3d
	.byte	0xe
	.4byte	0xc38
	.uleb128 0x1
	.4byte	.LASF252
	.byte	0
	.uleb128 0x1
	.4byte	.LASF253
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF254
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF255
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF256
	.byte	0xc
	.byte	0x42
	.byte	0x3
	.4byte	0xc12
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xc
	.byte	0x45
	.byte	0xe
	.4byte	0xcac
	.uleb128 0x1
	.4byte	.LASF257
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF258
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF259
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF260
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF261
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF262
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF263
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF264
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF265
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF266
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF267
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF268
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF269
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF270
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF271
	.byte	0x3f
	.byte	0
	.uleb128 0x5
	.4byte	.LASF272
	.byte	0xc
	.byte	0x57
	.byte	0x3
	.4byte	0xc44
	.uleb128 0x5
	.4byte	.LASF273
	.byte	0xc
	.byte	0x59
	.byte	0x10
	.4byte	0xcc4
	.uleb128 0xc
	.4byte	0xcc9
	.uleb128 0x1b
	.4byte	0xce9
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0xc38
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x9
	.byte	0
	.uleb128 0x5
	.4byte	.LASF274
	.byte	0xc
	.byte	0x5a
	.byte	0x10
	.4byte	0xcf5
	.uleb128 0xc
	.4byte	0xcfa
	.uleb128 0x1b
	.4byte	0xd24
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0xc38
	.uleb128 0x3
	.4byte	0xd24
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x9
	.byte	0
	.uleb128 0xc
	.4byte	0xd29
	.uleb128 0x3c
	.uleb128 0x5
	.4byte	.LASF275
	.byte	0xc
	.byte	0x5b
	.byte	0x10
	.4byte	0xd36
	.uleb128 0xc
	.4byte	0xd3b
	.uleb128 0x1b
	.4byte	0xd56
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0xc38
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x9
	.byte	0
	.uleb128 0x5
	.4byte	.LASF276
	.byte	0xc
	.byte	0x5c
	.byte	0x14
	.4byte	0xd62
	.uleb128 0xc
	.4byte	0xd67
	.uleb128 0x3d
	.4byte	0xd8
	.4byte	0xd8a
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0xc38
	.uleb128 0x3
	.4byte	0xcac
	.uleb128 0x3
	.4byte	0xd8a
	.uleb128 0x3
	.4byte	0xd8f
	.byte	0
	.uleb128 0xc
	.4byte	0xd24
	.uleb128 0xc
	.4byte	0xd8
	.uleb128 0xb
	.byte	0x1c
	.byte	0xc
	.byte	0x5e
	.4byte	0xdf8
	.uleb128 0x2
	.4byte	.LASF277
	.byte	0xc
	.byte	0x5f
	.byte	0x11
	.4byte	0x8d
	.byte	0
	.uleb128 0x2
	.4byte	.LASF278
	.byte	0xc
	.byte	0x60
	.byte	0xe
	.4byte	0xd8
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF279
	.byte	0xc
	.byte	0x61
	.byte	0xe
	.4byte	0xd8
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF280
	.byte	0xc
	.byte	0x62
	.byte	0xf
	.4byte	0xcb8
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF281
	.byte	0xc
	.byte	0x63
	.byte	0x15
	.4byte	0xce9
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF282
	.byte	0xc
	.byte	0x64
	.byte	0x12
	.4byte	0xd56
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF283
	.byte	0xc
	.byte	0x65
	.byte	0x10
	.4byte	0xd2a
	.byte	0x18
	.byte	0
	.uleb128 0x5
	.4byte	.LASF284
	.byte	0xc
	.byte	0x66
	.byte	0x3
	.4byte	0xd94
	.uleb128 0xb
	.byte	0x1
	.byte	0xd
	.byte	0x6a
	.4byte	0xe1a
	.uleb128 0x2
	.4byte	.LASF285
	.byte	0xd
	.byte	0x6c
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF286
	.byte	0xd
	.byte	0x6d
	.byte	0x2
	.4byte	0xe04
	.uleb128 0x20
	.4byte	.LASF288
	.byte	0xd
	.byte	0x6f
	.byte	0x15
	.4byte	0xe1a
	.uleb128 0xb
	.byte	0x28
	.byte	0xd
	.byte	0x8d
	.4byte	0xea8
	.uleb128 0x2
	.4byte	.LASF289
	.byte	0xd
	.byte	0x8e
	.byte	0xe
	.4byte	0xd8
	.byte	0
	.uleb128 0xa
	.string	"k"
	.byte	0xd
	.byte	0x8f
	.byte	0xe
	.4byte	0xd8
	.byte	0x4
	.uleb128 0xa
	.string	"x"
	.byte	0xd
	.byte	0x90
	.byte	0xd
	.4byte	0xaa
	.byte	0x8
	.uleb128 0xa
	.string	"y"
	.byte	0xd
	.byte	0x91
	.byte	0xd
	.4byte	0xaa
	.byte	0xc
	.uleb128 0xa
	.string	"z1"
	.byte	0xd
	.byte	0x92
	.byte	0xd
	.4byte	0xaa
	.byte	0x10
	.uleb128 0xa
	.string	"z2"
	.byte	0xd
	.byte	0x93
	.byte	0xd
	.4byte	0xaa
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF290
	.byte	0xd
	.byte	0x94
	.byte	0xe
	.4byte	0xd8
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF291
	.byte	0xd
	.byte	0x95
	.byte	0xe
	.4byte	0x27d
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF292
	.byte	0xd
	.byte	0x96
	.byte	0xe
	.4byte	0xd8
	.byte	0x24
	.byte	0
	.uleb128 0x5
	.4byte	.LASF293
	.byte	0xd
	.byte	0x9c
	.byte	0x2
	.4byte	0xe32
	.uleb128 0x20
	.4byte	.LASF294
	.byte	0xd
	.byte	0xda
	.byte	0x11
	.4byte	0xd8
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xd
	.byte	0xef
	.byte	0xe
	.4byte	0xeec
	.uleb128 0x1
	.4byte	.LASF295
	.byte	0
	.uleb128 0x1
	.4byte	.LASF296
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF297
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF298
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF299
	.byte	0x4
	.byte	0
	.uleb128 0x5
	.4byte	.LASF300
	.byte	0xd
	.byte	0xf5
	.byte	0x3
	.4byte	0xec0
	.uleb128 0x5
	.4byte	.LASF301
	.byte	0xd
	.byte	0xf7
	.byte	0x10
	.4byte	0xf04
	.uleb128 0xc
	.4byte	0xf09
	.uleb128 0x1b
	.4byte	0xf19
	.uleb128 0x3
	.4byte	0xeec
	.uleb128 0x3
	.4byte	0xf19
	.byte	0
	.uleb128 0xc
	.4byte	0xea8
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xe
	.byte	0x29
	.byte	0xe
	.4byte	0xf62
	.uleb128 0x1
	.4byte	.LASF302
	.byte	0
	.uleb128 0x1
	.4byte	.LASF303
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF304
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF305
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF306
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF307
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF308
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF309
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF310
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF311
	.byte	0xe
	.byte	0x34
	.byte	0x3
	.4byte	0xf1e
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xe
	.byte	0x3d
	.byte	0xe
	.4byte	0xf8e
	.uleb128 0x1
	.4byte	.LASF312
	.byte	0
	.uleb128 0x1
	.4byte	.LASF313
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF314
	.byte	0x2
	.byte	0
	.uleb128 0xb
	.byte	0x10
	.byte	0xe
	.byte	0x4a
	.4byte	0xfd8
	.uleb128 0x2
	.4byte	.LASF315
	.byte	0xe
	.byte	0x4b
	.byte	0xe
	.4byte	0x27d
	.byte	0
	.uleb128 0x2
	.4byte	.LASF316
	.byte	0xe
	.byte	0x4c
	.byte	0xe
	.4byte	0xd8
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF317
	.byte	0xe
	.byte	0x4d
	.byte	0xd
	.4byte	0xb6
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF318
	.byte	0xe
	.byte	0x4e
	.byte	0xd
	.4byte	0xb6
	.byte	0xd
	.uleb128 0x2
	.4byte	.LASF289
	.byte	0xe
	.byte	0x4f
	.byte	0xd
	.4byte	0xb6
	.byte	0xe
	.byte	0
	.uleb128 0x5
	.4byte	.LASF319
	.byte	0xe
	.byte	0x50
	.byte	0x2
	.4byte	0xf8e
	.uleb128 0xb
	.byte	0xa8
	.byte	0xe
	.byte	0x52
	.4byte	0x106f
	.uleb128 0x2
	.4byte	.LASF320
	.byte	0xe
	.byte	0x53
	.byte	0x12
	.4byte	0x106f
	.byte	0
	.uleb128 0x2
	.4byte	.LASF321
	.byte	0xe
	.byte	0x54
	.byte	0xe
	.4byte	0xd8
	.byte	0x80
	.uleb128 0x2
	.4byte	.LASF322
	.byte	0xe
	.byte	0x55
	.byte	0xe
	.4byte	0xd8
	.byte	0x84
	.uleb128 0x2
	.4byte	.LASF323
	.byte	0xe
	.byte	0x56
	.byte	0xe
	.4byte	0xd8
	.byte	0x88
	.uleb128 0x2
	.4byte	.LASF324
	.byte	0xe
	.byte	0x57
	.byte	0xe
	.4byte	0xd8
	.byte	0x8c
	.uleb128 0x2
	.4byte	.LASF325
	.byte	0xe
	.byte	0x59
	.byte	0xe
	.4byte	0x27d
	.byte	0x90
	.uleb128 0x2
	.4byte	.LASF326
	.byte	0xe
	.byte	0x5a
	.byte	0xe
	.4byte	0xd8
	.byte	0x98
	.uleb128 0x2
	.4byte	.LASF327
	.byte	0xe
	.byte	0x5b
	.byte	0xe
	.4byte	0xd8
	.byte	0x9c
	.uleb128 0x2
	.4byte	.LASF328
	.byte	0xe
	.byte	0x5c
	.byte	0xe
	.4byte	0xd8
	.byte	0xa0
	.uleb128 0x2
	.4byte	.LASF329
	.byte	0xe
	.byte	0x5d
	.byte	0xe
	.4byte	0xd8
	.byte	0xa4
	.byte	0
	.uleb128 0xe
	.4byte	0xfd8
	.4byte	0x107f
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.4byte	.LASF330
	.byte	0xe
	.byte	0x5e
	.byte	0x2
	.4byte	0xfe4
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xf
	.byte	0x2a
	.byte	0xe
	.4byte	0x1135
	.uleb128 0x1
	.4byte	.LASF331
	.byte	0
	.uleb128 0x1
	.4byte	.LASF332
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF333
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF334
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF335
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF336
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF337
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF338
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF339
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF340
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF341
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF342
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF343
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF344
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF345
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF346
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF347
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF348
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF349
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF350
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF351
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF352
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF353
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF354
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF355
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF356
	.byte	0xff
	.byte	0
	.uleb128 0x1a
	.byte	0x7
	.4byte	0x2d
	.byte	0x10
	.2byte	0x2a5
	.4byte	0x1155
	.uleb128 0x1
	.4byte	.LASF357
	.byte	0
	.uleb128 0x1
	.4byte	.LASF358
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF359
	.byte	0x2
	.byte	0
	.uleb128 0x18
	.4byte	.LASF360
	.byte	0x10
	.2byte	0x2a9
	.byte	0x3
	.4byte	0x1135
	.uleb128 0x1a
	.byte	0x5
	.4byte	0x65
	.byte	0x10
	.2byte	0x2ad
	.4byte	0x11a0
	.uleb128 0x11
	.4byte	.LASF361
	.sleb128 -7
	.uleb128 0x11
	.4byte	.LASF362
	.sleb128 -6
	.uleb128 0x11
	.4byte	.LASF363
	.sleb128 -5
	.uleb128 0x11
	.4byte	.LASF364
	.sleb128 -4
	.uleb128 0x11
	.4byte	.LASF365
	.sleb128 -3
	.uleb128 0x11
	.4byte	.LASF366
	.sleb128 -2
	.uleb128 0x11
	.4byte	.LASF367
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF368
	.byte	0
	.byte	0
	.uleb128 0x18
	.4byte	.LASF369
	.byte	0x10
	.2byte	0x2b6
	.byte	0x3
	.4byte	0x1162
	.uleb128 0x18
	.4byte	.LASF370
	.byte	0x10
	.2byte	0x2d2
	.byte	0x10
	.4byte	0x11ba
	.uleb128 0xc
	.4byte	0x11bf
	.uleb128 0x1b
	.4byte	0x11cf
	.uleb128 0x3
	.4byte	0x1155
	.uleb128 0x3
	.4byte	0x7f
	.byte	0
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0x11
	.byte	0x6e
	.byte	0xe
	.4byte	0x11f5
	.uleb128 0x1
	.4byte	.LASF371
	.byte	0
	.uleb128 0x1
	.4byte	.LASF372
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF373
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF374
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF375
	.byte	0x11
	.byte	0x74
	.byte	0x3
	.4byte	0x11cf
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0x11
	.byte	0x80
	.byte	0xe
	.4byte	0x121b
	.uleb128 0x1
	.4byte	.LASF376
	.byte	0
	.uleb128 0x1
	.4byte	.LASF377
	.byte	0x1
	.byte	0
	.uleb128 0xd
	.byte	0x5
	.4byte	0x65
	.byte	0x12
	.byte	0xce
	.byte	0xe
	.4byte	0x1241
	.uleb128 0x11
	.4byte	.LASF378
	.sleb128 -3
	.uleb128 0x11
	.4byte	.LASF379
	.sleb128 -2
	.uleb128 0x11
	.4byte	.LASF380
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF381
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF382
	.byte	0x12
	.byte	0xd3
	.byte	0x3
	.4byte	0x121b
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0x13
	.byte	0x4b
	.byte	0xe
	.4byte	0x129d
	.uleb128 0x1
	.4byte	.LASF383
	.byte	0
	.uleb128 0x1
	.4byte	.LASF384
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF385
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF386
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF387
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF388
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF389
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF390
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF391
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF392
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF393
	.byte	0xa
	.byte	0
	.uleb128 0x5
	.4byte	.LASF394
	.byte	0x13
	.byte	0x57
	.byte	0x3
	.4byte	0x124d
	.uleb128 0xb
	.byte	0x48
	.byte	0x14
	.byte	0x2b
	.4byte	0x13dd
	.uleb128 0x2
	.4byte	.LASF395
	.byte	0x14
	.byte	0x2d
	.byte	0xe
	.4byte	0xd8
	.byte	0
	.uleb128 0x2
	.4byte	.LASF396
	.byte	0x14
	.byte	0x2e
	.byte	0xe
	.4byte	0xd8
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF397
	.byte	0x14
	.byte	0x2f
	.byte	0xe
	.4byte	0xd8
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF398
	.byte	0x14
	.byte	0x30
	.byte	0xe
	.4byte	0xd8
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF316
	.byte	0x14
	.byte	0x31
	.byte	0xe
	.4byte	0xd8
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF399
	.byte	0x14
	.byte	0x32
	.byte	0xe
	.4byte	0xd8
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF400
	.byte	0x14
	.byte	0x33
	.byte	0xe
	.4byte	0xd8
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF401
	.byte	0x14
	.byte	0x34
	.byte	0xe
	.4byte	0xd8
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF402
	.byte	0x14
	.byte	0x35
	.byte	0xe
	.4byte	0xd8
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF403
	.byte	0x14
	.byte	0x36
	.byte	0xe
	.4byte	0xd8
	.byte	0x24
	.uleb128 0x2
	.4byte	.LASF404
	.byte	0x14
	.byte	0x37
	.byte	0xe
	.4byte	0xd8
	.byte	0x28
	.uleb128 0x2
	.4byte	.LASF405
	.byte	0x14
	.byte	0x38
	.byte	0xe
	.4byte	0xd8
	.byte	0x2c
	.uleb128 0x2
	.4byte	.LASF406
	.byte	0x14
	.byte	0x3f
	.byte	0xe
	.4byte	0xcc
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF407
	.byte	0x14
	.byte	0x40
	.byte	0xe
	.4byte	0xcc
	.byte	0x32
	.uleb128 0x2
	.4byte	.LASF408
	.byte	0x14
	.byte	0x41
	.byte	0xe
	.4byte	0xcc
	.byte	0x34
	.uleb128 0x2
	.4byte	.LASF409
	.byte	0x14
	.byte	0x42
	.byte	0xe
	.4byte	0xcc
	.byte	0x36
	.uleb128 0x2
	.4byte	.LASF410
	.byte	0x14
	.byte	0x43
	.byte	0xe
	.4byte	0xcc
	.byte	0x38
	.uleb128 0x2
	.4byte	.LASF411
	.byte	0x14
	.byte	0x44
	.byte	0xe
	.4byte	0xcc
	.byte	0x3a
	.uleb128 0x2
	.4byte	.LASF412
	.byte	0x14
	.byte	0x45
	.byte	0xe
	.4byte	0xcc
	.byte	0x3c
	.uleb128 0x2
	.4byte	.LASF413
	.byte	0x14
	.byte	0x46
	.byte	0xe
	.4byte	0xcc
	.byte	0x3e
	.uleb128 0x2
	.4byte	.LASF414
	.byte	0x14
	.byte	0x47
	.byte	0xe
	.4byte	0xcc
	.byte	0x40
	.uleb128 0x2
	.4byte	.LASF415
	.byte	0x14
	.byte	0x48
	.byte	0xe
	.4byte	0xcc
	.byte	0x42
	.uleb128 0x2
	.4byte	.LASF416
	.byte	0x14
	.byte	0x49
	.byte	0xe
	.4byte	0xcc
	.byte	0x44
	.byte	0
	.uleb128 0x5
	.4byte	.LASF417
	.byte	0x14
	.byte	0x4a
	.byte	0x2
	.4byte	0x12a9
	.uleb128 0x3e
	.string	"dbg"
	.byte	0x14
	.byte	0x4c
	.byte	0x23
	.4byte	0x13dd
	.uleb128 0x7
	.4byte	.LASF418
	.byte	0x56
	.byte	0x4c
	.4byte	0xdf8
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_rv_exp
	.uleb128 0xe
	.4byte	0x88
	.4byte	0x1416
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x16
	.4byte	0x1406
	.uleb128 0x7
	.4byte	.LASF419
	.byte	0x56
	.byte	0x7c
	.4byte	0x1416
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_mirror_rv_exp
	.uleb128 0x7
	.4byte	.LASF420
	.byte	0x5c
	.byte	0x14
	.4byte	0x107f
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.uleb128 0x2f
	.4byte	0xeb4
	.byte	0x63
	.byte	0xa
	.uleb128 0x5
	.byte	0x3
	.4byte	hid_flags
	.uleb128 0x7
	.4byte	.LASF421
	.byte	0x64
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	rv_fun_flags
	.uleb128 0x7
	.4byte	.LASF422
	.byte	0x65
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	last_tx_result
	.uleb128 0x7
	.4byte	.LASF423
	.byte	0x66
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	previous_tx_result
	.uleb128 0x7
	.4byte	.LASF424
	.byte	0x67
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	tx_buff_num
	.uleb128 0x7
	.4byte	.LASF425
	.byte	0x68
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	last_tx_buff_num
	.uleb128 0x7
	.4byte	.LASF426
	.byte	0x69
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	this_tx_idx
	.uleb128 0x7
	.4byte	.LASF229
	.byte	0x6a
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	dongle_scenario
	.uleb128 0x7
	.4byte	.LASF427
	.byte	0x6b
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	previous_key_status
	.uleb128 0x7
	.4byte	.LASF193
	.byte	0x6c
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	rr_idx_2_4g
	.uleb128 0x7
	.4byte	.LASF428
	.byte	0x6e
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	hid_exp_feature_option
	.uleb128 0x3f
	.4byte	.LASF494
	.byte	0x1
	.byte	0x70
	.byte	0x1c
	.4byte	0xef8
	.uleb128 0x5
	.byte	0x3
	.4byte	peripheral_sampling_cb_ptr
	.uleb128 0x7
	.4byte	.LASF429
	.byte	0x73
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	report_go
	.uleb128 0x7
	.4byte	.LASF430
	.byte	0x74
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	last_report_go
	.uleb128 0x7
	.4byte	.LASF431
	.byte	0x75
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	report_go_previous
	.uleb128 0x7
	.4byte	.LASF432
	.byte	0x77
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	curr_tx_count
	.uleb128 0x7
	.4byte	.LASF433
	.byte	0x78
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	report_repeat_cnt
	.uleb128 0x7
	.4byte	.LASF434
	.byte	0x79
	.byte	0x15
	.4byte	0xea8
	.uleb128 0x5
	.byte	0x3
	.4byte	outgoing_data
	.uleb128 0x7
	.4byte	.LASF435
	.byte	0x7a
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	report_send_result
	.uleb128 0x7
	.4byte	.LASF436
	.byte	0x7b
	.byte	0x9
	.4byte	0xb6
	.uleb128 0x5
	.byte	0x3
	.4byte	report_rate_pka
	.uleb128 0x2f
	.4byte	0xe26
	.byte	0x7c
	.byte	0xe
	.uleb128 0x5
	.byte	0x3
	.4byte	hid_ctrl
	.uleb128 0x7
	.4byte	.LASF437
	.byte	0x80
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	timestamp_spi_cb_start
	.uleb128 0x7
	.4byte	.LASF438
	.byte	0x81
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	timestamp_spi_cb_start_previous
	.uleb128 0x7
	.4byte	.LASF439
	.byte	0x82
	.byte	0xa
	.4byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	pka_active_state_always
	.uleb128 0x20
	.4byte	.LASF440
	.byte	0x1
	.byte	0x8c
	.byte	0x11
	.4byte	0xfe
	.uleb128 0x7
	.4byte	.LASF441
	.byte	0x94
	.byte	0x5
	.4byte	0x647
	.uleb128 0x5
	.byte	0x3
	.4byte	g_riscv_ccni_irq_occur
	.uleb128 0x7
	.4byte	.LASF442
	.byte	0x96
	.byte	0x12
	.4byte	0xf62
	.uleb128 0x5
	.byte	0x3
	.4byte	key_queue_push_result
	.uleb128 0x10
	.4byte	.LASF445
	.byte	0x15
	.byte	0x51
	.4byte	0x1609
	.uleb128 0x9
	.byte	0
	.uleb128 0x12
	.4byte	.LASF443
	.byte	0xe
	.byte	0x6a
	.byte	0x12
	.4byte	0xf62
	.4byte	0x161f
	.uleb128 0x3
	.4byte	0x161f
	.byte	0
	.uleb128 0xc
	.4byte	0x107f
	.uleb128 0x12
	.4byte	.LASF444
	.byte	0xe
	.byte	0x6e
	.byte	0x5
	.4byte	0x647
	.4byte	0x163a
	.uleb128 0x3
	.4byte	0x161f
	.byte	0
	.uleb128 0x14
	.4byte	.LASF447
	.byte	0xe
	.byte	0x67
	.4byte	0x164b
	.uleb128 0x3
	.4byte	0x161f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF446
	.byte	0x14
	.byte	0x4f
	.4byte	0x1658
	.uleb128 0x9
	.byte	0
	.uleb128 0x14
	.4byte	.LASF448
	.byte	0xe
	.byte	0x6b
	.4byte	0x166e
	.uleb128 0x3
	.4byte	0x161f
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x10
	.4byte	.LASF449
	.byte	0x15
	.byte	0x4a
	.4byte	0x167b
	.uleb128 0x9
	.byte	0
	.uleb128 0x10
	.4byte	.LASF450
	.byte	0x16
	.byte	0x2c
	.4byte	0x1688
	.uleb128 0x9
	.byte	0
	.uleb128 0x14
	.4byte	.LASF451
	.byte	0xe
	.byte	0x66
	.4byte	0x169e
	.uleb128 0x3
	.4byte	0x161f
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x10
	.4byte	.LASF452
	.byte	0x17
	.byte	0x8d
	.4byte	0x16ab
	.uleb128 0x9
	.byte	0
	.uleb128 0x10
	.4byte	.LASF453
	.byte	0x18
	.byte	0x41
	.4byte	0x16b8
	.uleb128 0x9
	.byte	0
	.uleb128 0x10
	.4byte	.LASF454
	.byte	0x19
	.byte	0x28
	.4byte	0x16c5
	.uleb128 0x9
	.byte	0
	.uleb128 0x25
	.4byte	.LASF455
	.byte	0x10
	.2byte	0x4bc
	.byte	0x19
	.4byte	0x11a0
	.4byte	0x16e6
	.uleb128 0x3
	.4byte	0x3ee
	.uleb128 0x3
	.4byte	0x11ad
	.uleb128 0x3
	.4byte	0x7f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF456
	.byte	0x1a
	.byte	0x54
	.4byte	0x16f3
	.uleb128 0x9
	.byte	0
	.uleb128 0x12
	.4byte	.LASF457
	.byte	0x13
	.byte	0x90
	.byte	0x13
	.4byte	0x1241
	.4byte	0x170e
	.uleb128 0x3
	.4byte	0x55f
	.uleb128 0x3
	.4byte	0x129d
	.byte	0
	.uleb128 0x40
	.4byte	.LASF530
	.byte	0x13
	.byte	0x8d
	.byte	0x13
	.4byte	0x1241
	.uleb128 0x1c
	.4byte	.LASF458
	.byte	0x17
	.byte	0x8f
	.byte	0x5
	.4byte	0x647
	.4byte	0x172c
	.uleb128 0x9
	.byte	0
	.uleb128 0x10
	.4byte	.LASF459
	.byte	0x19
	.byte	0x2f
	.4byte	0x1739
	.uleb128 0x9
	.byte	0
	.uleb128 0x30
	.4byte	.LASF460
	.byte	0x11
	.2byte	0x144
	.byte	0x6
	.4byte	0x174c
	.uleb128 0x3
	.4byte	0x7f
	.byte	0
	.uleb128 0x12
	.4byte	.LASF461
	.byte	0x19
	.byte	0x29
	.byte	0x5
	.4byte	0x65
	.4byte	0x1771
	.uleb128 0x3
	.4byte	0xf19
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0x647
	.byte	0
	.uleb128 0x12
	.4byte	.LASF462
	.byte	0x17
	.byte	0x8a
	.byte	0x5
	.4byte	0x65
	.4byte	0x1796
	.uleb128 0x3
	.4byte	0xf19
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x12
	.4byte	.LASF463
	.byte	0x18
	.byte	0x44
	.byte	0x5
	.4byte	0x65
	.4byte	0x17bb
	.uleb128 0x3
	.4byte	0xf19
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x12
	.4byte	.LASF464
	.byte	0xe
	.byte	0x68
	.byte	0x12
	.4byte	0xf62
	.4byte	0x17db
	.uleb128 0x3
	.4byte	0x161f
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x12
	.4byte	.LASF465
	.byte	0xe
	.byte	0x69
	.byte	0x12
	.4byte	0xf62
	.4byte	0x17fb
	.uleb128 0x3
	.4byte	0x161f
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x14
	.4byte	.LASF466
	.byte	0x16
	.byte	0x2b
	.4byte	0x180c
	.uleb128 0x3
	.4byte	0xf19
	.byte	0
	.uleb128 0x14
	.4byte	.LASF467
	.byte	0x15
	.byte	0x4d
	.4byte	0x1822
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0x65
	.byte	0
	.uleb128 0x12
	.4byte	.LASF468
	.byte	0x19
	.byte	0x2a
	.byte	0x5
	.4byte	0x65
	.4byte	0x1842
	.uleb128 0x3
	.4byte	0xf19
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x12
	.4byte	.LASF469
	.byte	0x17
	.byte	0x8b
	.byte	0x5
	.4byte	0x65
	.4byte	0x1867
	.uleb128 0x3
	.4byte	0xf19
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x12
	.4byte	.LASF470
	.byte	0x18
	.byte	0x43
	.byte	0x5
	.4byte	0x65
	.4byte	0x188c
	.uleb128 0x3
	.4byte	0xf19
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x25
	.4byte	.LASF471
	.byte	0x6
	.2byte	0x12e
	.byte	0x13
	.4byte	0x5b8
	.4byte	0x18a8
	.uleb128 0x3
	.4byte	0x3c1
	.uleb128 0x3
	.4byte	0x18a8
	.byte	0
	.uleb128 0xc
	.4byte	0x586
	.uleb128 0x1c
	.4byte	.LASF472
	.byte	0x1b
	.byte	0x3f
	.byte	0xa
	.4byte	0xd8
	.4byte	0x18bf
	.uleb128 0x9
	.byte	0
	.uleb128 0x14
	.4byte	.LASF473
	.byte	0x16
	.byte	0x2e
	.4byte	0x18d0
	.uleb128 0x3
	.4byte	0xf19
	.byte	0
	.uleb128 0x14
	.4byte	.LASF474
	.byte	0x1c
	.byte	0x35
	.4byte	0x18e1
	.uleb128 0x3
	.4byte	0xf19
	.byte	0
	.uleb128 0x10
	.4byte	.LASF475
	.byte	0x1c
	.byte	0x36
	.4byte	0x18ee
	.uleb128 0x9
	.byte	0
	.uleb128 0x14
	.4byte	.LASF476
	.byte	0xe
	.byte	0x6c
	.4byte	0x1904
	.uleb128 0x3
	.4byte	0x161f
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x14
	.4byte	.LASF477
	.byte	0x18
	.byte	0x48
	.4byte	0x1915
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x12
	.4byte	.LASF478
	.byte	0x1d
	.byte	0x21
	.byte	0x8
	.4byte	0x7f
	.4byte	0x1935
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x6c
	.byte	0
	.uleb128 0x10
	.4byte	.LASF479
	.byte	0x15
	.byte	0x46
	.4byte	0x1942
	.uleb128 0x9
	.byte	0
	.uleb128 0x10
	.4byte	.LASF480
	.byte	0x19
	.byte	0x2d
	.4byte	0x194f
	.uleb128 0x9
	.byte	0
	.uleb128 0x10
	.4byte	.LASF481
	.byte	0x1
	.byte	0x7e
	.4byte	0x195c
	.uleb128 0x9
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF482
	.byte	0x1a
	.byte	0x59
	.byte	0xa
	.4byte	0xd8
	.4byte	0x196e
	.uleb128 0x9
	.byte	0
	.uleb128 0x25
	.4byte	.LASF483
	.byte	0x11
	.2byte	0x14b
	.byte	0x5
	.4byte	0x647
	.4byte	0x1985
	.uleb128 0x3
	.4byte	0xcc
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF484
	.byte	0x18
	.byte	0x4a
	.byte	0x5
	.4byte	0x65
	.4byte	0x1997
	.uleb128 0x9
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF485
	.byte	0x17
	.byte	0x8c
	.byte	0x5
	.4byte	0x65
	.4byte	0x19a9
	.uleb128 0x9
	.byte	0
	.uleb128 0x14
	.4byte	.LASF486
	.byte	0xe
	.byte	0x6d
	.4byte	0x19c4
	.uleb128 0x3
	.4byte	0x161f
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x3
	.4byte	0xd8
	.byte	0
	.uleb128 0x12
	.4byte	.LASF487
	.byte	0x1a
	.byte	0x58
	.byte	0xa
	.4byte	0xd8
	.4byte	0x19df
	.uleb128 0x3
	.4byte	0x19df
	.uleb128 0x3
	.4byte	0xd8f
	.byte	0
	.uleb128 0xc
	.4byte	0x11f5
	.uleb128 0x10
	.4byte	.LASF488
	.byte	0x19
	.byte	0x2b
	.4byte	0x19f1
	.uleb128 0x9
	.byte	0
	.uleb128 0x30
	.4byte	.LASF489
	.byte	0xc
	.2byte	0x129
	.byte	0xd
	.4byte	0x1a14
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0xc38
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x3
	.4byte	0xd8
	.uleb128 0x9
	.byte	0
	.uleb128 0x26
	.4byte	.LASF490
	.2byte	0x450
	.4byte	0xd8
	.4byte	.LFB35
	.4byte	.LFE35-.LFB35
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x26
	.4byte	.LASF491
	.2byte	0x44b
	.4byte	0xd8
	.4byte	.LFB34
	.4byte	.LFE34-.LFB34
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x21
	.4byte	.LASF497
	.2byte	0x444
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1a5d
	.uleb128 0x31
	.4byte	.LVL110
	.4byte	0x15fc
	.byte	0
	.uleb128 0x19
	.4byte	.LASF499
	.2byte	0x3e0
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1b45
	.uleb128 0x15
	.4byte	.LASF492
	.2byte	0x3e0
	.byte	0x2e
	.4byte	0xd8
	.4byte	.LLST10
	.uleb128 0x15
	.4byte	.LASF493
	.2byte	0x3e0
	.byte	0x43
	.4byte	0xd8
	.4byte	.LLST11
	.uleb128 0x22
	.4byte	.LASF495
	.2byte	0x3e3
	.byte	0xe
	.4byte	0xd8
	.4byte	.LLST12
	.uleb128 0x1d
	.4byte	.LASF496
	.2byte	0x3e6
	.byte	0x19
	.4byte	0xea8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x6
	.4byte	.LVL99
	.4byte	0x1915
	.4byte	0x1ad0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x28
	.byte	0
	.uleb128 0x6
	.4byte	.LVL100
	.4byte	0x1624
	.4byte	0x1ae7
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.byte	0
	.uleb128 0x6
	.4byte	.LVL101
	.4byte	0x1609
	.4byte	0x1afe
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.byte	0
	.uleb128 0x8
	.4byte	.LVL102
	.4byte	0x180c
	.uleb128 0x8
	.4byte	.LVL103
	.4byte	0x1935
	.uleb128 0x6
	.4byte	.LVL104
	.4byte	0x17fb
	.4byte	0x1b24
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0
	.uleb128 0x27
	.4byte	.LVL105
	.4byte	0x17db
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x21
	.4byte	.LASF498
	.2byte	0x3d6
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1b6e
	.uleb128 0x28
	.4byte	.LVL94
	.4byte	0x163a
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.byte	0
	.byte	0
	.uleb128 0x19
	.4byte	.LASF500
	.2byte	0x3cf
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1bf3
	.uleb128 0x41
	.string	"rr"
	.byte	0x1
	.2byte	0x3cf
	.byte	0x2f
	.4byte	0xd8
	.4byte	.LLST9
	.uleb128 0x42
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.uleb128 0x43
	.4byte	.LASF418
	.byte	0x1
	.2byte	0x3d3
	.byte	0x25
	.4byte	0xdf8
	.uleb128 0x1d
	.4byte	.LASF501
	.2byte	0x3d3
	.byte	0x7e
	.4byte	0x1c03
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x28
	.4byte	.LVL93
	.4byte	0x19f1
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_rv_exp
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
	.byte	0x31
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0xc
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xe
	.4byte	0x88
	.4byte	0x1c03
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x42
	.byte	0
	.uleb128 0x16
	.4byte	0x1bf3
	.uleb128 0x21
	.4byte	.LASF502
	.2byte	0x3be
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1c4b
	.uleb128 0x44
	.4byte	.LASF243
	.byte	0x1
	.2byte	0x3c0
	.byte	0xe
	.4byte	0xd8
	.uleb128 0x6
	.4byte	.LVL89
	.4byte	0x1658
	.4byte	0x1c41
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.byte	0
	.uleb128 0x31
	.4byte	.LVL90
	.4byte	0x164b
	.byte	0
	.uleb128 0x19
	.4byte	.LASF503
	.2byte	0x332
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1c6f
	.uleb128 0x32
	.4byte	.LASF504
	.2byte	0x332
	.byte	0x28
	.4byte	0xd8
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x19
	.4byte	.LASF505
	.2byte	0x32d
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1c93
	.uleb128 0x32
	.4byte	.LASF506
	.2byte	0x32d
	.byte	0x32
	.4byte	0xd8
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x29
	.4byte	.LASF509
	.2byte	0x2f2
	.4byte	0x65
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1d39
	.uleb128 0x15
	.4byte	.LASF507
	.2byte	0x2f2
	.byte	0x2a
	.4byte	0xef8
	.4byte	.LLST8
	.uleb128 0x8
	.4byte	.LVL73
	.4byte	0x16e6
	.uleb128 0x6
	.4byte	.LVL74
	.4byte	0x16c5
	.4byte	0x1ce6
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	hid_express_entrance
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x8
	.4byte	.LVL75
	.4byte	0x1d39
	.uleb128 0x8
	.4byte	.LVL76
	.4byte	0x16b8
	.uleb128 0x8
	.4byte	.LVL77
	.4byte	0x16ab
	.uleb128 0x8
	.4byte	.LVL78
	.4byte	0x169e
	.uleb128 0x6
	.4byte	.LVL79
	.4byte	0x1688
	.4byte	0x1d26
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x8
	.4byte	.LVL80
	.4byte	0x167b
	.uleb128 0x8
	.4byte	.LVL81
	.4byte	0x166e
	.byte	0
	.uleb128 0x21
	.4byte	.LASF508
	.2byte	0x2e7
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1dcc
	.uleb128 0x8
	.4byte	.LVL66
	.4byte	0x170e
	.uleb128 0x6
	.4byte	.LVL67
	.4byte	0x16f3
	.4byte	0x1d6f
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x35
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.4byte	.LVL68
	.4byte	0x16f3
	.4byte	0x1d87
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x36
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x6
	.4byte	.LVL69
	.4byte	0x16f3
	.4byte	0x1d9f
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x41
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.uleb128 0x6
	.4byte	.LVL70
	.4byte	0x16f3
	.4byte	0x1db7
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x47
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x33
	.byte	0
	.uleb128 0x28
	.4byte	.LVL71
	.4byte	0x16f3
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x48
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.byte	0
	.uleb128 0x29
	.4byte	.LASF510
	.2byte	0x287
	.4byte	0x65
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1f0a
	.uleb128 0x15
	.4byte	.LASF511
	.2byte	0x287
	.byte	0x2c
	.4byte	0xf19
	.4byte	.LLST1
	.uleb128 0x15
	.4byte	.LASF495
	.2byte	0x287
	.byte	0x3f
	.4byte	0xd8
	.4byte	.LLST2
	.uleb128 0x22
	.4byte	.LASF512
	.2byte	0x289
	.byte	0xe
	.4byte	0xd8
	.4byte	.LLST3
	.uleb128 0x45
	.4byte	.LASF513
	.byte	0x1
	.2byte	0x29e
	.byte	0x16
	.4byte	0xf62
	.byte	0x4
	.uleb128 0x22
	.4byte	.LASF514
	.2byte	0x2a1
	.byte	0x16
	.4byte	0xf62
	.4byte	.LLST4
	.uleb128 0x8
	.4byte	.LVL14
	.4byte	0x180c
	.uleb128 0x6
	.4byte	.LVL15
	.4byte	0x17fb
	.4byte	0x1e50
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x6
	.4byte	.LVL18
	.4byte	0x17db
	.4byte	0x1e74
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x6
	.4byte	.LVL19
	.4byte	0x17bb
	.4byte	0x1e98
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x6
	.4byte	.LVL21
	.4byte	0x1796
	.4byte	0x1eac
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x6
	.4byte	.LVL27
	.4byte	0x1771
	.4byte	0x1ec5
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x6
	.4byte	.LVL30
	.4byte	0x174c
	.4byte	0x1ed9
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x8
	.4byte	.LVL33
	.4byte	0x1739
	.uleb128 0x8
	.4byte	.LVL35
	.4byte	0x172c
	.uleb128 0x8
	.4byte	.LVL36
	.4byte	0x171a
	.uleb128 0x27
	.4byte	.LVL37
	.4byte	0x1771
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x29
	.4byte	.LASF515
	.2byte	0x211
	.4byte	0x65
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1fca
	.uleb128 0x15
	.4byte	.LASF511
	.2byte	0x211
	.byte	0x33
	.4byte	0xf19
	.4byte	.LLST0
	.uleb128 0x1d
	.4byte	.LASF516
	.2byte	0x213
	.byte	0x15
	.4byte	0x586
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x6
	.4byte	.LVL2
	.4byte	0x18d0
	.4byte	0x1f56
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x6
	.4byte	.LVL3
	.4byte	0x18bf
	.4byte	0x1f6a
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x6
	.4byte	.LVL4
	.4byte	0x188c
	.4byte	0x1f83
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x42
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x6
	.4byte	.LVL5
	.4byte	0x1867
	.4byte	0x1f97
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x8
	.4byte	.LVL8
	.4byte	0x18ad
	.uleb128 0x6
	.4byte	.LVL9
	.4byte	0x1842
	.4byte	0x1fb9
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x27
	.4byte	.LVL10
	.4byte	0x1822
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x19
	.4byte	.LASF517
	.2byte	0x20b
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1fee
	.uleb128 0x46
	.string	"go"
	.byte	0x1
	.2byte	0x20b
	.byte	0x27
	.4byte	0x647
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x26
	.4byte	.LASF518
	.2byte	0x206
	.4byte	0xd8
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x19
	.4byte	.LASF519
	.2byte	0x14c
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2201
	.uleb128 0x15
	.4byte	.LASF520
	.2byte	0x14c
	.byte	0x3b
	.4byte	0x1155
	.4byte	.LLST5
	.uleb128 0x15
	.4byte	.LASF521
	.2byte	0x14c
	.byte	0x48
	.4byte	0x7f
	.4byte	.LLST6
	.uleb128 0x1d
	.4byte	.LASF289
	.2byte	0x15f
	.byte	0x1f
	.4byte	0x11f5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1d
	.4byte	.LASF522
	.2byte	0x160
	.byte	0xe
	.4byte	0xd8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x22
	.4byte	.LASF523
	.2byte	0x161
	.byte	0xe
	.4byte	0xd8
	.4byte	.LLST7
	.uleb128 0x8
	.4byte	.LVL40
	.4byte	0x19e4
	.uleb128 0x1e
	.4byte	.LVL41
	.4byte	0x2083
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.4byte	.LVL42
	.4byte	0x19c4
	.4byte	0x209d
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x6
	.4byte	.LVL43
	.4byte	0x19a9
	.4byte	0x20b4
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.byte	0
	.uleb128 0x1e
	.4byte	.LVL44
	.4byte	0x20cc
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	outgoing_data
	.byte	0
	.uleb128 0x6
	.4byte	.LVL45
	.4byte	0x1f0a
	.4byte	0x20e3
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	outgoing_data
	.byte	0
	.uleb128 0x8
	.4byte	.LVL46
	.4byte	0x1942
	.uleb128 0x1e
	.4byte	.LVL47
	.4byte	0x2104
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	outgoing_data
	.byte	0
	.uleb128 0x6
	.4byte	.LVL48
	.4byte	0x1dcc
	.4byte	0x211b
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	outgoing_data
	.byte	0
	.uleb128 0x8
	.4byte	.LVL49
	.4byte	0x195c
	.uleb128 0x8
	.4byte	.LVL51
	.4byte	0x1935
	.uleb128 0x1e
	.4byte	.LVL52
	.4byte	0x2145
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	outgoing_data
	.byte	0
	.uleb128 0x6
	.4byte	.LVL53
	.4byte	0x1915
	.4byte	0x2167
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	outgoing_data
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x28
	.byte	0
	.uleb128 0x8
	.4byte	.LVL54
	.4byte	0x194f
	.uleb128 0x8
	.4byte	.LVL55
	.4byte	0x1904
	.uleb128 0x6
	.4byte	.LVL56
	.4byte	0x18ee
	.4byte	0x2190
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.byte	0
	.uleb128 0x8
	.4byte	.LVL57
	.4byte	0x18e1
	.uleb128 0x8
	.4byte	.LVL59
	.4byte	0x1997
	.uleb128 0x6
	.4byte	.LVL60
	.4byte	0x19a9
	.4byte	0x21be
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kCtrl_k
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x8
	.4byte	.LVL61
	.4byte	0x1985
	.uleb128 0x6
	.4byte	.LVL62
	.4byte	0x196e
	.4byte	0x21da
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x8
	.4byte	.LVL63
	.4byte	0x195c
	.uleb128 0x1e
	.4byte	.LVL64
	.4byte	0x21f7
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x34
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x8
	.4byte	.LVL65
	.4byte	0x194f
	.byte	0
	.uleb128 0x23
	.4byte	.LASF524
	.byte	0xbc
	.byte	0xa
	.4byte	0xd8
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x23
	.4byte	.LASF525
	.byte	0xb7
	.byte	0xa
	.4byte	0xd8
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x23
	.4byte	.LASF526
	.byte	0xb2
	.byte	0x16
	.4byte	0xf19
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x23
	.4byte	.LASF527
	.byte	0xad
	.byte	0xa
	.4byte	0xd8
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
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
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
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
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
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
	.uleb128 0x13
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
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
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
	.uleb128 0x16
	.uleb128 0x26
	.byte	0
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
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 0x1a
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
	.uleb128 0x1b
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
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
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
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
	.uleb128 0x22
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
	.uleb128 0x23
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
	.uleb128 0x24
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
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
	.uleb128 0x26
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
	.sleb128 10
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
	.uleb128 0x27
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0x21
	.sleb128 5
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
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0x2c
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
	.uleb128 0x2d
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
	.uleb128 0x2e
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2f
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
	.uleb128 0x32
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
	.uleb128 0x33
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
	.uleb128 0x34
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
	.uleb128 0x35
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x36
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
	.uleb128 0x37
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
	.uleb128 0x38
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3a
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
	.uleb128 0x3b
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x3f
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
	.uleb128 0x40
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x41
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
	.uleb128 0x42
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x43
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
	.uleb128 0x44
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
	.byte	0
	.byte	0
	.uleb128 0x45
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
	.uleb128 0xb
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
	.byte	0
	.section	.debug_loclists,"",@progbits
	.4byte	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.Ldebug_loc0:
.LLST10:
	.byte	0x6
	.4byte	.LVL95
	.byte	0x4
	.uleb128 .LVL95-.LVL95
	.uleb128 .LVL97-.LVL95
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL97-.LVL95
	.uleb128 .LVL107-.LVL95
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL107-.LVL95
	.uleb128 .LVL109-.LVL95
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
	.uleb128 .LVL109-.LVL95
	.uleb128 .LFE32-.LVL95
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL95
	.byte	0x4
	.uleb128 .LVL95-.LVL95
	.uleb128 .LVL96-.LVL95
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL96-.LVL95
	.uleb128 .LVL106-.LVL95
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL106-.LVL95
	.uleb128 .LVL109-.LVL95
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
	.uleb128 .LVL109-.LVL95
	.uleb128 .LFE32-.LVL95
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL98
	.byte	0x4
	.uleb128 .LVL98-.LVL98
	.uleb128 .LVL99-1-.LVL98
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL99-1-.LVL98
	.uleb128 .LVL108-.LVL98
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL108-.LVL98
	.uleb128 .LVL109-.LVL98
	.uleb128 0x2
	.byte	0x72
	.sleb128 -56
	.byte	0x4
	.uleb128 .LVL109-.LVL98
	.uleb128 .LFE32-.LVL98
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL91
	.byte	0x4
	.uleb128 .LVL91-.LVL91
	.uleb128 .LVL92-.LVL91
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL92-.LVL91
	.uleb128 .LFE30-.LVL91
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
	.4byte	.LVL72
	.byte	0x4
	.uleb128 .LVL72-.LVL72
	.uleb128 .LVL73-1-.LVL72
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL73-1-.LVL72
	.uleb128 .LVL82-.LVL72
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
	.uleb128 .LVL82-.LVL72
	.uleb128 .LVL83-.LVL72
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL83-.LVL72
	.uleb128 .LFE26-.LVL72
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
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL13-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL13-.LVL11
	.uleb128 .LVL23-.LVL11
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL23-.LVL11
	.uleb128 .LVL25-.LVL11
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
	.uleb128 .LVL25-.LVL11
	.uleb128 .LFE24-.LVL11
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL12-.LVL11
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL12-.LVL11
	.uleb128 .LVL17-.LVL11
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL17-.LVL11
	.uleb128 .LFE24-.LVL11
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
.LLST3:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL22-.LVL11
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL22-.LVL11
	.uleb128 .LVL24-.LVL11
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL24-.LVL11
	.uleb128 .LVL25-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL25-.LVL11
	.uleb128 .LVL37-.LVL11
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL37-.LVL11
	.uleb128 .LFE24-.LVL11
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL19
	.byte	0x4
	.uleb128 .LVL19-.LVL19
	.uleb128 .LVL20-.LVL19
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL25-.LVL19
	.uleb128 .LVL26-.LVL19
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL28-.LVL19
	.uleb128 .LVL29-.LVL19
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL31-.LVL19
	.uleb128 .LVL32-.LVL19
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL34-.LVL19
	.uleb128 .LVL35-1-.LVL19
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL2-1-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL2-1-.LVL1
	.uleb128 .LVL6-.LVL1
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL6-.LVL1
	.uleb128 .LVL7-.LVL1
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
	.uleb128 .LVL7-.LVL1
	.uleb128 .LFE23-.LVL1
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL38
	.byte	0x4
	.uleb128 .LVL38-.LVL38
	.uleb128 .LVL40-1-.LVL38
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL40-1-.LVL38
	.uleb128 .LFE20-.LVL38
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
	.4byte	.LVL38
	.byte	0x4
	.uleb128 .LVL38-.LVL38
	.uleb128 .LVL40-1-.LVL38
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL40-1-.LVL38
	.uleb128 .LFE20-.LVL38
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
.LLST7:
	.byte	0x6
	.4byte	.LVL39
	.byte	0x4
	.uleb128 .LVL39-.LVL39
	.uleb128 .LVL50-.LVL39
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL50-.LVL39
	.uleb128 .LVL58-.LVL39
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL58-.LVL39
	.uleb128 .LVL65-.LVL39
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0xb4
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
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
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.4byte	.LFB34
	.4byte	.LFE34-.LFB34
	.4byte	.LFB35
	.4byte	.LFE35-.LFB35
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
	.4byte	.LFB21
	.uleb128 .LFE21-.LFB21
	.byte	0x7
	.4byte	.LFB22
	.uleb128 .LFE22-.LFB22
	.byte	0x7
	.4byte	.LFB23
	.uleb128 .LFE23-.LFB23
	.byte	0x7
	.4byte	.LFB24
	.uleb128 .LFE24-.LFB24
	.byte	0x7
	.4byte	.LFB20
	.uleb128 .LFE20-.LFB20
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF89:
	.string	"HAL_GPIO_36"
.LASF90:
	.string	"HAL_GPIO_37"
.LASF91:
	.string	"HAL_GPIO_38"
.LASF92:
	.string	"HAL_GPIO_39"
.LASF77:
	.string	"HAL_GPIO_24"
.LASF78:
	.string	"HAL_GPIO_25"
.LASF14:
	.string	"int8_t"
.LASF81:
	.string	"HAL_GPIO_28"
.LASF13:
	.string	"size_t"
.LASF156:
	.string	"HAL_EINT_UART_1_RX"
.LASF528:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF249:
	.string	"hid_common_info"
.LASF280:
	.string	"print_handle"
.LASF255:
	.string	"PRINT_LEVEL_ERROR"
.LASF239:
	.string	"irpt_ctrl"
.LASF453:
	.string	"hid_express_gaming_init"
.LASF371:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF377:
	.string	"PKA_SHARE_ACTIVE_STATE_NORMAL"
.LASF93:
	.string	"HAL_GPIO_40"
.LASF454:
	.string	"hid_express_usb_mode_init"
.LASF151:
	.string	"HAL_EINT_NUMBER_44"
.LASF96:
	.string	"HAL_GPIO_43"
.LASF73:
	.string	"HAL_GPIO_20"
.LASF107:
	.string	"HAL_EINT_NUMBER_0"
.LASF108:
	.string	"HAL_EINT_NUMBER_1"
.LASF110:
	.string	"HAL_EINT_NUMBER_3"
.LASF111:
	.string	"HAL_EINT_NUMBER_4"
.LASF112:
	.string	"HAL_EINT_NUMBER_5"
.LASF113:
	.string	"HAL_EINT_NUMBER_6"
.LASF114:
	.string	"HAL_EINT_NUMBER_7"
.LASF115:
	.string	"HAL_EINT_NUMBER_8"
.LASF116:
	.string	"HAL_EINT_NUMBER_9"
.LASF164:
	.string	"hal_eint_number_t"
.LASF503:
	.string	"hid_express_set_features"
.LASF162:
	.string	"HAL_EINT_RESERVED"
.LASF441:
	.string	"g_riscv_ccni_irq_occur"
.LASF438:
	.string	"timestamp_spi_cb_start_previous"
.LASF530:
	.string	"hal_eint_counter_enable"
.LASF266:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF348:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF428:
	.string	"hid_exp_feature_option"
.LASF43:
	.string	"GPT_CON"
.LASF212:
	.string	"T_HID_REPORT_KB_CONSUMER2_S"
.LASF192:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF254:
	.string	"PRINT_LEVEL_WARNING"
.LASF518:
	.string	"hid_express_get_outgpoig_report_result"
.LASF271:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF342:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF443:
	.string	"riscv_key_pop_confirm"
.LASF85:
	.string	"HAL_GPIO_32"
.LASF277:
	.string	"module_name"
.LASF29:
	.string	"PMU_IRQn"
.LASF473:
	.string	"key_remap_frontend_process_xy"
.LASF508:
	.string	"hid_express_init_gpio_timestamp_latch"
.LASF363:
	.string	"HAL_SPI_STATUS_BUSY_BY_NON_BLOCKING_FUNCTION"
.LASF79:
	.string	"HAL_GPIO_26"
.LASF516:
	.string	"motion_val"
.LASF289:
	.string	"type"
.LASF376:
	.string	"PKA_SHARE_ACTIVE_STATE_ALWAYS"
.LASF384:
	.string	"EINT_COUNTER_NUMBER_1"
.LASF385:
	.string	"EINT_COUNTER_NUMBER_2"
.LASF386:
	.string	"EINT_COUNTER_NUMBER_3"
.LASF387:
	.string	"EINT_COUNTER_NUMBER_4"
.LASF388:
	.string	"EINT_COUNTER_NUMBER_5"
.LASF389:
	.string	"EINT_COUNTER_NUMBER_6"
.LASF390:
	.string	"EINT_COUNTER_NUMBER_7"
.LASF391:
	.string	"EINT_COUNTER_NUMBER_8"
.LASF392:
	.string	"EINT_COUNTER_NUMBER_9"
.LASF424:
	.string	"tx_buff_num"
.LASF305:
	.string	"STATUS_INSUFFICIENT_MEMORY"
.LASF344:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF444:
	.string	"is_queue_num_2"
.LASF167:
	.string	"hal_gpio_data_t"
.LASF421:
	.string	"rv_fun_flags"
.LASF464:
	.string	"riscv_key_pop_temperory"
.LASF299:
	.string	"HID_EXP_NO_REPORT_PROCESS"
.LASF179:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF195:
	.string	"T_HID_REPORT_RATE_VAL_S"
.LASF181:
	.string	"DBG_PIN_MAX"
.LASF41:
	.string	"RESERVED"
.LASF35:
	.string	"IRQ_GEN_IRQn"
.LASF337:
	.string	"SLEEP_LOCK_IRRX"
.LASF426:
	.string	"this_tx_idx"
.LASF512:
	.string	"result"
.LASF94:
	.string	"HAL_GPIO_41"
.LASF95:
	.string	"HAL_GPIO_42"
.LASF183:
	.string	"T_COMMON_LA_DBG_S"
.LASF97:
	.string	"HAL_GPIO_44"
.LASF240:
	.string	"scroll_ctrl"
.LASF405:
	.string	"all_buff_full_cnt"
.LASF210:
	.string	"dummy"
.LASF100:
	.string	"HAL_GPIO_47"
.LASF378:
	.string	"HAL_EINT_STATUS_ERROR_EINT_NUMBER"
.LASF39:
	.string	"MODE"
.LASF225:
	.string	"step_2_4g"
.LASF8:
	.string	"long int"
.LASF490:
	.string	"hid_express_get_last_report_go"
.LASF457:
	.string	"hal_eint_set_counter_number"
.LASF215:
	.string	"ms_s16_z8"
.LASF245:
	.string	"mouse_key_num"
.LASF335:
	.string	"SLEEP_LOCK_DMA"
.LASF234:
	.string	"hid_shared_parameters"
.LASF118:
	.string	"HAL_EINT_NUMBER_11"
.LASF119:
	.string	"HAL_EINT_NUMBER_12"
.LASF120:
	.string	"HAL_EINT_NUMBER_13"
.LASF121:
	.string	"HAL_EINT_NUMBER_14"
.LASF122:
	.string	"HAL_EINT_NUMBER_15"
.LASF123:
	.string	"HAL_EINT_NUMBER_16"
.LASF124:
	.string	"HAL_EINT_NUMBER_17"
.LASF125:
	.string	"HAL_EINT_NUMBER_18"
.LASF126:
	.string	"HAL_EINT_NUMBER_19"
.LASF51:
	.string	"GPT_COMPARE"
.LASF529:
	.string	"IRQn"
.LASF415:
	.string	"motion_pin_low_4print"
.LASF357:
	.string	"HAL_SPI_MASTER_EVENT_SEND_FINISHED"
.LASF432:
	.string	"curr_tx_count"
.LASF246:
	.string	"app_shared_parameters"
.LASF157:
	.string	"HAL_EINT_UART_2_RX"
.LASF470:
	.string	"hid_express_2_4G_x_y_data_prepare"
.LASF304:
	.string	"STATUS_BUSY"
.LASF499:
	.string	"hid_express__push_to_key_queue"
.LASF232:
	.string	"outgoing_report_ready"
.LASF336:
	.string	"SLEEP_LOCK_IRTX"
.LASF127:
	.string	"HAL_EINT_NUMBER_20"
.LASF128:
	.string	"HAL_EINT_NUMBER_21"
.LASF129:
	.string	"HAL_EINT_NUMBER_22"
.LASF130:
	.string	"HAL_EINT_NUMBER_23"
.LASF131:
	.string	"HAL_EINT_NUMBER_24"
.LASF132:
	.string	"HAL_EINT_NUMBER_25"
.LASF341:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF487:
	.string	"pka_spi_callback_pre_process"
.LASF343:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF136:
	.string	"HAL_EINT_NUMBER_29"
.LASF509:
	.string	"hid_express_init"
.LASF5:
	.string	"signed char"
.LASF17:
	.string	"uint8_t"
.LASF292:
	.string	"kb_consumer"
.LASF461:
	.string	"hid_express_usb_data_send"
.LASF168:
	.string	"HAL_GPIO_STATUS_ERROR"
.LASF316:
	.string	"timestamp"
.LASF253:
	.string	"PRINT_LEVEL_INFO"
.LASF410:
	.string	"pka_hid_drop_cnt_4print"
.LASF236:
	.string	"combo_key_list"
.LASF20:
	.string	"SW_IRQn"
.LASF494:
	.string	"peripheral_sampling_cb_ptr"
.LASF355:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF137:
	.string	"HAL_EINT_NUMBER_30"
.LASF138:
	.string	"HAL_EINT_NUMBER_31"
.LASF139:
	.string	"HAL_EINT_NUMBER_32"
.LASF294:
	.string	"hid_flags"
.LASF141:
	.string	"HAL_EINT_NUMBER_34"
.LASF4:
	.string	"unsigned char"
.LASF143:
	.string	"HAL_EINT_NUMBER_36"
.LASF144:
	.string	"HAL_EINT_NUMBER_37"
.LASF145:
	.string	"HAL_EINT_NUMBER_38"
.LASF146:
	.string	"HAL_EINT_NUMBER_39"
.LASF409:
	.string	"sampling_cnt_4print"
.LASF372:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF327:
	.string	"buf_head"
.LASF36:
	.string	"USB_IRQn"
.LASF99:
	.string	"HAL_GPIO_46"
.LASF379:
	.string	"HAL_EINT_STATUS_INVALID_PARAMETER"
.LASF184:
	.string	"_Bool"
.LASF147:
	.string	"HAL_EINT_NUMBER_40"
.LASF148:
	.string	"HAL_EINT_NUMBER_41"
.LASF149:
	.string	"HAL_EINT_NUMBER_42"
.LASF150:
	.string	"HAL_EINT_NUMBER_43"
.LASF456:
	.string	"riscv_pka_init"
.LASF152:
	.string	"HAL_EINT_NUMBER_45"
.LASF153:
	.string	"HAL_EINT_NUMBER_46"
.LASF154:
	.string	"HAL_EINT_NUMBER_47"
.LASF166:
	.string	"HAL_GPIO_DATA_HIGH"
.LASF238:
	.string	"hold_timeout"
.LASF434:
	.string	"outgoing_data"
.LASF12:
	.string	"char"
.LASF203:
	.string	"report_id"
.LASF413:
	.string	"total_cnt_4print"
.LASF346:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF525:
	.string	"hid_express_get_get_tx_result"
.LASF176:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF177:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF288:
	.string	"hid_ctrl"
.LASF21:
	.string	"LED_IRQn"
.LASF279:
	.string	"print_level"
.LASF333:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF350:
	.string	"SLEEP_LOCK_UART0"
.LASF351:
	.string	"SLEEP_LOCK_UART1"
.LASF352:
	.string	"SLEEP_LOCK_UART2"
.LASF190:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF229:
	.string	"dongle_scenario"
.LASF322:
	.string	"last_pushed_ms"
.LASF479:
	.string	"key_remap_backend_process"
.LASF103:
	.string	"HAL_SPI_MASTER_0"
.LASF382:
	.string	"hal_eint_status_t"
.LASF326:
	.string	"last_pushed_kb_consumer"
.LASF230:
	.string	"flags"
.LASF402:
	.string	"pka_hid_drop_cnt"
.LASF265:
	.string	"LOG_TYPE_HCI_DATA"
.LASF260:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF40:
	.string	"SW_CG"
.LASF47:
	.string	"GPT_IRQ_EN"
.LASF323:
	.string	"old_pushed_ms"
.LASF267:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF501:
	.string	"msg_id_string"
.LASF514:
	.string	"status_k"
.LASF284:
	.string	"log_control_block_t"
.LASF395:
	.string	"wheel_ok"
.LASF481:
	.string	"hid_express_dbg_check"
.LASF158:
	.string	"HAL_EINT_USB0"
.LASF159:
	.string	"HAL_EINT_USB1"
.LASF160:
	.string	"HAL_EINT_USB2"
.LASF298:
	.string	"HID_EXP_4TH_CB_POST_PROCESS"
.LASF285:
	.string	"rr_idx"
.LASF435:
	.string	"report_send_result"
.LASF206:
	.string	"T_HID_REPORT_KB_STD2_XY_S"
.LASF262:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF98:
	.string	"HAL_GPIO_45"
.LASF325:
	.string	"last_pushed_kb_std"
.LASF287:
	.string	"hid_common"
.LASF243:
	.string	"riscv_trigger_time"
.LASF366:
	.string	"HAL_SPI_MASTER_STATUS_ERROR_PORT"
.LASF44:
	.string	"GPT_CON_UNION"
.LASF433:
	.string	"report_repeat_cnt"
.LASF311:
	.string	"KEY_QUEUE_STATUS"
.LASF446:
	.string	"rv_hid_exp_delay_printf"
.LASF485:
	.string	"hid_express_bt_get_tx_result"
.LASF320:
	.string	"buffer"
.LASF463:
	.string	"hid_express_gaming_data_send"
.LASF425:
	.string	"last_tx_buff_num"
.LASF347:
	.string	"SLEEP_LOCK_I3C1"
.LASF345:
	.string	"SLEEP_LOCK_DCXO"
.LASF440:
	.string	"reliable_tx_ptr"
.LASF25:
	.string	"SPI_MST1_IRQn"
.LASF526:
	.string	"hid_express_get_outgoing_data"
.LASF286:
	.string	"T_hid_ctrl_S"
.LASF291:
	.string	"kb_std"
.LASF504:
	.string	"hid_exp_features"
.LASF306:
	.string	"STATUS_QUEUE_EMPTY"
.LASF321:
	.string	"valid_key_mask"
.LASF27:
	.string	"GPT_IRQn"
.LASF362:
	.string	"HAL_SPI_STATUS_ERROR_USED_BY_NORMAL_USER"
.LASF301:
	.string	"riscv_ps_callback_t"
.LASF106:
	.string	"hal_spi_master_port_t"
.LASF297:
	.string	"HID_EXP_3RD_CB_GET_KEY__TIMING_CRITICAL"
.LASF296:
	.string	"HID_EXP_2ND_CB"
.LASF227:
	.string	"T_DEBOUNCE_PARA_S"
.LASF396:
	.string	"sensor_ok"
.LASF242:
	.string	"key_remap_fn_key"
.LASF9:
	.string	"long unsigned int"
.LASF406:
	.string	"wheel_ok_4print"
.LASF283:
	.string	"msg_id_handle"
.LASF201:
	.string	"status"
.LASF49:
	.string	"GPT_IRQ_ACK"
.LASF178:
	.string	"DBG_PIN_USB_SOF"
.LASF199:
	.string	"macro"
.LASF338:
	.string	"SLEEP_LOCK_AIO"
.LASF513:
	.string	"status_z1"
.LASF460:
	.string	"pka_share_push_hid_tx_ptr"
.LASF182:
	.string	"enable_mask"
.LASF16:
	.string	"int32_t"
.LASF515:
	.string	"hid_express_prepare_X_Y"
.LASF169:
	.string	"HAL_GPIO_STATUS_ERROR_PIN"
.LASF50:
	.string	"GPT_COUNT"
.LASF492:
	.string	"value_type"
.LASF282:
	.string	"tlv_dump_handle"
.LASF33:
	.string	"I3C0_DMA_IRQn"
.LASF445:
	.string	"key_remap_backend_deinit"
.LASF251:
	.string	"DEBUG_LOG_OFF"
.LASF23:
	.string	"KEYSCAN_IRQn"
.LASF318:
	.string	"key_delivery_status"
.LASF250:
	.string	"DEBUG_LOG_ON"
.LASF216:
	.string	"kb_std2"
.LASF218:
	.string	"kb_std5"
.LASF439:
	.string	"pka_active_state_always"
.LASF248:
	.string	"outgoing_report"
.LASF109:
	.string	"HAL_EINT_NUMBER_2"
.LASF401:
	.string	"valid_key_cnt"
.LASF373:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF471:
	.string	"hal_gpio_get_input"
.LASF171:
	.string	"HAL_GPIO_STATUS_OK"
.LASF431:
	.string	"report_go_previous"
.LASF264:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF10:
	.string	"long long int"
.LASF244:
	.string	"mouse_key_list"
.LASF198:
	.string	"repeat_times"
.LASF412:
	.string	"pka_acl_cnt_4print"
.LASF469:
	.string	"hid_express_bt_x_y_data_prepare"
.LASF226:
	.string	"step_bt"
.LASF477:
	.string	"hid_express_2_4g_post_process"
.LASF155:
	.string	"HAL_EINT_UART_0_RX"
.LASF313:
	.string	"K_TYPE_Z1"
.LASF314:
	.string	"K_TYPE_Z2"
.LASF258:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF397:
	.string	"total_cnt"
.LASF500:
	.string	"hid_express_set_report_rate_idx"
.LASF208:
	.string	"numeric_key_pad"
.LASF101:
	.string	"HAL_GPIO_MAX"
.LASF498:
	.string	"hid_express_clear_key_pushed"
.LASF172:
	.string	"hal_gpio_status_t"
.LASF365:
	.string	"HAL_SPI_MASTER_STATUS_ERROR_BUSY"
.LASF398:
	.string	"sampling_cnt"
.LASF307:
	.string	"STATUS_QUEUE_FULL"
.LASF274:
	.string	"f_dump_buffer_t"
.LASF519:
	.string	"hid_express_entrance"
.LASF259:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF105:
	.string	"HAL_SPI_MASTER_MAX"
.LASF484:
	.string	"hid_express_gaming_get_tx_status"
.LASF42:
	.string	"GPT_CON_CELLS"
.LASF205:
	.string	"combo"
.LASF394:
	.string	"eint_counter_number_t"
.LASF334:
	.string	"SLEEP_LOCK_TRNG"
.LASF375:
	.string	"pka_share_callback_type_t"
.LASF173:
	.string	"DBG_PIN_SPI_CB"
.LASF196:
	.string	"keycode"
.LASF520:
	.string	"event"
.LASF222:
	.string	"combo_bit_32_63"
.LASF38:
	.string	"IRQ_NUMBER_MAX"
.LASF340:
	.string	"SLEEP_LOCK_ESC"
.LASF332:
	.string	"SLEEP_LOCK_AESOTF"
.LASF3:
	.string	"unsigned int"
.LASF475:
	.string	"rv_fake_report_post_process"
.LASF427:
	.string	"previous_key_status"
.LASF491:
	.string	"hid_express_get_report_go_previous"
.LASF408:
	.string	"sensor_ok_4print"
.LASF360:
	.string	"hal_spi_master_callback_event_t"
.LASF310:
	.string	"STATUS_UNKNOWN"
.LASF451:
	.string	"init_key_ctrl"
.LASF34:
	.string	"SPI_MST0_IRQn"
.LASF252:
	.string	"PRINT_LEVEL_DEBUG"
.LASF6:
	.string	"short int"
.LASF211:
	.string	"T_HID_REPORT_KB_STD5_S"
.LASF359:
	.string	"HAL_SPI_MASTER_NO_BUSY_FUNCTION_ERROR"
.LASF430:
	.string	"last_report_go"
.LASF510:
	.string	"hid_express_send"
.LASF467:
	.string	"key_remap_update_key_status"
.LASF474:
	.string	"rv_fake_report_fake_report"
.LASF300:
	.string	"T_PS_CB_TYPE_E"
.LASF511:
	.string	"outgoing"
.LASF194:
	.string	"rr_idx_usb"
.LASF48:
	.string	"GPT_IRQ_STA"
.LASF133:
	.string	"HAL_EINT_NUMBER_26"
.LASF134:
	.string	"HAL_EINT_NUMBER_27"
.LASF22:
	.string	"QDEC_IRQn"
.LASF135:
	.string	"HAL_EINT_NUMBER_28"
.LASF237:
	.string	"combo_key_list_size"
.LASF476:
	.string	"rv_hid_exp_key_queue_post_process"
.LASF486:
	.string	"rv_hid_exp_key_queue_pre_process"
.LASF418:
	.string	"log_control_block_rv_exp"
.LASF32:
	.string	"I3C0_IRQn"
.LASF24:
	.string	"UART_IRQn"
.LASF458:
	.string	"is_bt_queue_empty"
.LASF11:
	.string	"long double"
.LASF317:
	.string	"nack_cnt"
.LASF361:
	.string	"HAL_SPI_STATUS_FULL_BY_NON_BLOCKING_FUNCTION"
.LASF354:
	.string	"SLEEP_LOCK_APP"
.LASF197:
	.string	"play_mode"
.LASF459:
	.string	"hid_express_usb_data_set_report_ready"
.LASF482:
	.string	"pka_spi_callback_post_process"
.LASF331:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF228:
	.string	"hid_scenario_type"
.LASF368:
	.string	"HAL_SPI_MASTER_STATUS_OK"
.LASF180:
	.string	"DBG_PIN_USB_TX"
.LASF400:
	.string	"motion_pin_cnt"
.LASF214:
	.string	"T_OUTPUT_CTRL_PIN_INFO_S"
.LASF417:
	.string	"T_SENSOR_DATA_STATISTICS_S"
.LASF488:
	.string	"hid_express_usb_delay_for_latency"
.LASF191:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF209:
	.string	"T_HID_REPORT_KB_CONSUMER1_XY_S"
.LASF472:
	.string	"hid_express_x_y_buf_has_data"
.LASF207:
	.string	"consumer"
.LASF30:
	.string	"MCU_DMA_IRQn"
.LASF2:
	.string	"long long unsigned int"
.LASF174:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF18:
	.string	"uint16_t"
.LASF442:
	.string	"key_queue_push_result"
.LASF263:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF140:
	.string	"HAL_EINT_NUMBER_33"
.LASF28:
	.string	"UART_DMA_IRQn"
.LASF193:
	.string	"rr_idx_2_4g"
.LASF142:
	.string	"HAL_EINT_NUMBER_35"
.LASF502:
	.string	"hid_express_debug_print"
.LASF187:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF493:
	.string	"value"
.LASF480:
	.string	"hid_express_usb_wakeup_cm33_handler"
.LASF295:
	.string	"HID_EXP_1ST_CB"
.LASF364:
	.string	"HAL_SPI_MASTER_STATUS_ERROR"
.LASF339:
	.string	"SLEEP_LOCK_FLASH"
.LASF54:
	.string	"HAL_GPIO_1"
.LASF55:
	.string	"HAL_GPIO_2"
.LASF56:
	.string	"HAL_GPIO_3"
.LASF57:
	.string	"HAL_GPIO_4"
.LASF58:
	.string	"HAL_GPIO_5"
.LASF59:
	.string	"HAL_GPIO_6"
.LASF60:
	.string	"HAL_GPIO_7"
.LASF61:
	.string	"HAL_GPIO_8"
.LASF62:
	.string	"HAL_GPIO_9"
.LASF231:
	.string	"features"
.LASF170:
	.string	"HAL_GPIO_STATUS_INVALID_PARAMETER"
.LASF466:
	.string	"key_remap_frontend_process"
.LASF429:
	.string	"report_go"
.LASF523:
	.string	"timestamp_report_submitted"
.LASF478:
	.string	"memset"
.LASF522:
	.string	"tx_cnt"
.LASF381:
	.string	"HAL_EINT_STATUS_OK"
.LASF328:
	.string	"buf_tail"
.LASF188:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF233:
	.string	"delay_for_key_polling_ms"
.LASF161:
	.string	"HAL_EINT_LPCOMP"
.LASF186:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF358:
	.string	"HAL_SPI_MASTER_EVENT_RECEIVE_FINISHED"
.LASF465:
	.string	"riscv_key_push"
.LASF202:
	.string	"T_HID_KEY_REMAP_S"
.LASF449:
	.string	"key_remap_backend_init"
.LASF165:
	.string	"HAL_GPIO_DATA_LOW"
.LASF273:
	.string	"f_print_t"
.LASF204:
	.string	"T_HID_REPORT_MS_K8_S16_Z8_S"
.LASF367:
	.string	"HAL_SPI_MASTER_STATUS_INVALID_PARAMETER"
.LASF224:
	.string	"step_wired"
.LASF189:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF437:
	.string	"timestamp_spi_cb_start"
.LASF349:
	.string	"SLEEP_LOCK_USB"
.LASF312:
	.string	"K_TYPE_K"
.LASF507:
	.string	"ps_callback"
.LASF505:
	.string	"hid_express_dongle_scenario_update"
.LASF356:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF452:
	.string	"hid_express_bt_init"
.LASF53:
	.string	"HAL_GPIO_0"
.LASF163:
	.string	"HAL_EINT_NUMBER_MAX"
.LASF436:
	.string	"report_rate_pka"
.LASF527:
	.string	"hid_express_get_hid_flag"
.LASF403:
	.string	"pka_hid_cnt"
.LASF489:
	.string	"print_module_msgid_log"
.LASF185:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF419:
	.string	"log_control_block_mirror_rv_exp"
.LASF369:
	.string	"hal_spi_master_status_t"
.LASF383:
	.string	"EINT_COUNTER_NUMBER_0"
.LASF411:
	.string	"pka_hid_cnt_4print"
.LASF117:
	.string	"HAL_EINT_NUMBER_10"
.LASF15:
	.string	"int16_t"
.LASF104:
	.string	"HAL_SPI_MASTER_1"
.LASF450:
	.string	"key_remap_frontend_init"
.LASF353:
	.string	"SLEEP_LOCK_I2C0"
.LASF303:
	.string	"STATUS_INVALID_PARAMETER"
.LASF281:
	.string	"dump_handle"
.LASF200:
	.string	"item"
.LASF223:
	.string	"T_AIR_COMBO_KEY_S"
.LASF483:
	.string	"pka_active_state_match"
.LASF380:
	.string	"HAL_EINT_STATUS_ERROR"
.LASF455:
	.string	"hal_spi_master_register_callback"
.LASF268:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF374:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF416:
	.string	"valid_key_cnt_4print"
.LASF423:
	.string	"previous_tx_result"
.LASF404:
	.string	"pka_acl_cnt"
.LASF319:
	.string	"T_KEY_INFO_S"
.LASF447:
	.string	"riscv_key_clear_key_pushed"
.LASF448:
	.string	"riscv_hid_express_key_queue_debug_print"
.LASF52:
	.string	"GPT_REGISTER_T"
.LASF37:
	.string	"BT_IRQn"
.LASF495:
	.string	"timestamp_key_press"
.LASF422:
	.string	"last_tx_result"
.LASF468:
	.string	"hid_express_usb_x_y_data_prepare"
.LASF315:
	.string	"items"
.LASF241:
	.string	"key_remap_enable"
.LASF517:
	.string	"hid_express_report_go_update"
.LASF506:
	.string	"scenario"
.LASF370:
	.string	"hal_spi_master_callback_t"
.LASF330:
	.string	"T_KEY_QUEUE_CTRL_S"
.LASF19:
	.string	"uint32_t"
.LASF276:
	.string	"f_tlv_dump_t"
.LASF221:
	.string	"combo_bit_00_31"
.LASF257:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF393:
	.string	"EINT_COUNTER_NUMBER_MUX"
.LASF329:
	.string	"buf_tail_printed"
.LASF496:
	.string	"temp_outgoing"
.LASF407:
	.string	"waiting_4print"
.LASF261:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF7:
	.string	"short unsigned int"
.LASF63:
	.string	"HAL_GPIO_10"
.LASF64:
	.string	"HAL_GPIO_11"
.LASF220:
	.string	"T_HID_CCNI_USB_REPORT_S"
.LASF66:
	.string	"HAL_GPIO_13"
.LASF524:
	.string	"hid_express_get_previous_tx_result"
.LASF68:
	.string	"HAL_GPIO_15"
.LASF65:
	.string	"HAL_GPIO_12"
.LASF70:
	.string	"HAL_GPIO_17"
.LASF71:
	.string	"HAL_GPIO_18"
.LASF72:
	.string	"HAL_GPIO_19"
.LASF67:
	.string	"HAL_GPIO_14"
.LASF270:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF69:
	.string	"HAL_GPIO_16"
.LASF521:
	.string	"user_data"
.LASF290:
	.string	"k_old"
.LASF256:
	.string	"print_level_t"
.LASF102:
	.string	"hal_gpio_pin_t"
.LASF46:
	.string	"GPT_CLK"
.LASF278:
	.string	"log_switch"
.LASF45:
	.string	"GPT_CLR"
.LASF414:
	.string	"nack_count_4print"
.LASF293:
	.string	"T_OUTGOING_VALUES_S"
.LASF420:
	.string	"kCtrl_k"
.LASF302:
	.string	"STATUS_SUCCESS"
.LASF74:
	.string	"HAL_GPIO_21"
.LASF75:
	.string	"HAL_GPIO_22"
.LASF76:
	.string	"HAL_GPIO_23"
.LASF217:
	.string	"kb_consumer1"
.LASF219:
	.string	"kb_consumer2"
.LASF275:
	.string	"f_msg_id_t"
.LASF80:
	.string	"HAL_GPIO_27"
.LASF272:
	.string	"log_type_t"
.LASF82:
	.string	"HAL_GPIO_29"
.LASF309:
	.string	"STATUS_NOTHING_CHANGED"
.LASF213:
	.string	"para"
.LASF247:
	.string	"mapped_data"
.LASF324:
	.string	"outgoing_item_idx"
.LASF308:
	.string	"STATUS_TIMEOUT"
.LASF269:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF497:
	.string	"hid_express_deinit"
.LASF399:
	.string	"nack_count"
.LASF26:
	.string	"RTC_IRQn"
.LASF175:
	.string	"DBG_PIN_NACK"
.LASF462:
	.string	"hid_express_bt_data_send"
.LASF31:
	.string	"EINT_IRQn"
.LASF83:
	.string	"HAL_GPIO_30"
.LASF84:
	.string	"HAL_GPIO_31"
.LASF235:
	.string	"inActivity_timeout"
.LASF86:
	.string	"HAL_GPIO_33"
.LASF87:
	.string	"HAL_GPIO_34"
.LASF88:
	.string	"HAL_GPIO_35"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
