	.file	"riscv_hid_express_usb_mode.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_usb_mode.c"
	.section	.text.hid_express_usb_mode_send_report_to_CM33,"ax",@progbits
	.align	1
	.globl	hid_express_usb_mode_send_report_to_CM33
	.hidden	hid_express_usb_mode_send_report_to_CM33
	.type	hid_express_usb_mode_send_report_to_CM33, @function
hid_express_usb_mode_send_report_to_CM33:
.LFB15:
	.file 1 "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_usb_mode.c"
	.loc 1 85 1
	.cfi_startproc
.LVL0:
	.loc 1 88 5
	li	a1,0
	li	a0,33619968
.LVL1:
	tail	hal_ccni_set_event
.LVL2:
	.cfi_endproc
.LFE15:
	.size	hid_express_usb_mode_send_report_to_CM33, .-hid_express_usb_mode_send_report_to_CM33
	.section	.text.hid_express_usb_mode_generate_kb_consumer_reports,"ax",@progbits
	.align	1
	.globl	hid_express_usb_mode_generate_kb_consumer_reports
	.hidden	hid_express_usb_mode_generate_kb_consumer_reports
	.type	hid_express_usb_mode_generate_kb_consumer_reports, @function
hid_express_usb_mode_generate_kb_consumer_reports:
.LFB16:
	.loc 1 97 1
	.cfi_startproc
.LVL3:
	.loc 1 98 5
	.loc 1 100 5
.LBB2:
	.loc 1 100 10
	.loc 1 100 66 is_stmt 0
	lw	a4,36(a0)
.LVL4:
	.loc 1 100 254 is_stmt 1
	.loc 1 100 331 is_stmt 0
	li	a5,4096
	.loc 1 100 286
	lw	a3,hid_common
	.loc 1 100 108
	li	a2,65536
	.loc 1 100 331
	add	a3,a3,a5
	.loc 1 100 108
	addi	a2,a2,-256
	slli	a5,a4,8
.LVL5:
	and	a5,a5,a2
.LVL6:
	.loc 1 100 211
	srli	a2,a4,16
	.loc 1 100 246
	slli	a2,a2,24
	.loc 1 100 183
	or	a5,a5,a2
	.loc 1 100 176
	slli	a4,a4,8
.LVL7:
	li	a2,16711680
	and	a4,a4,a2
.LVL8:
	.loc 1 100 183
	or	a5,a5,a4
	.loc 1 100 26
	ori	a5,a5,10
	.loc 1 100 331
	sw	a5,1762(a3)
.LVL9:
.LBE2:
	.loc 1 100 8 is_stmt 1
	.loc 1 106 5
.LBB3:
	.loc 1 106 10
	.loc 1 106 189
	.loc 1 106 26 is_stmt 0
	lbu	a5,39(a0)
	.loc 1 106 268
	sw	a5,1766(a3)
.LVL10:
.LBE3:
	.loc 1 106 8 is_stmt 1
	.loc 1 126 1 is_stmt 0
	ret
	.cfi_endproc
.LFE16:
	.size	hid_express_usb_mode_generate_kb_consumer_reports, .-hid_express_usb_mode_generate_kb_consumer_reports
	.section	.text.hid_express_usb_mode_generate_kb_std_reports,"ax",@progbits
	.align	1
	.globl	hid_express_usb_mode_generate_kb_std_reports
	.hidden	hid_express_usb_mode_generate_kb_std_reports
	.type	hid_express_usb_mode_generate_kb_std_reports, @function
hid_express_usb_mode_generate_kb_std_reports:
.LFB17:
	.loc 1 131 1 is_stmt 1
	.cfi_startproc
.LVL11:
	.loc 1 132 5
	.loc 1 134 5
.LBB4:
	.loc 1 134 10
	.loc 1 134 73 is_stmt 0
	lw	a4,28(a0)
.LVL12:
	.loc 1 134 247 is_stmt 1
	.loc 1 134 319 is_stmt 0
	li	a5,4096
	.loc 1 134 279
	lw	a3,hid_common
	.loc 1 134 105
	li	a2,65536
	.loc 1 134 319
	add	a3,a3,a5
	.loc 1 134 105
	addi	a2,a2,-1
	slli	a5,a4,8
.LVL13:
	.loc 1 134 204
	srli	a1,a4,16
.LVL14:
	.loc 1 134 105
	and	a5,a5,a2
.LVL15:
	.loc 1 134 239
	slli	a1,a1,24
	.loc 1 134 178
	or	a5,a5,a1
	.loc 1 134 171
	slli	a4,a4,8
.LVL16:
	li	a1,16711680
	and	a4,a4,a1
.LVL17:
	.loc 1 134 178
	or	a5,a5,a4
	.loc 1 134 26
	ori	a5,a5,9
	.loc 1 134 319
	sw	a5,1762(a3)
.LVL18:
.LBE4:
	.loc 1 134 8 is_stmt 1
	.loc 1 140 5
.LBB5:
	.loc 1 140 10
	.loc 1 140 112 is_stmt 0
	lw	a5,32(a0)
.LVL19:
	.loc 1 140 247 is_stmt 1
	.loc 1 140 56 is_stmt 0
	lbu	a4,31(a0)
	.loc 1 140 144
	slli	a0,a5,8
.LVL20:
	and	a2,a0,a2
	.loc 1 140 91
	or	a4,a4,a2
	.loc 1 140 210
	and	a5,a0,a1
.LVL21:
	.loc 1 140 26
	or	a5,a4,a5
	.loc 1 140 320
	sw	a5,1766(a3)
.LVL22:
.LBE5:
	.loc 1 140 8 is_stmt 1
	.loc 1 160 1 is_stmt 0
	ret
	.cfi_endproc
.LFE17:
	.size	hid_express_usb_mode_generate_kb_std_reports, .-hid_express_usb_mode_generate_kb_std_reports
	.section	.text.hid_express_usb_mode_generate_12bits_reports,"ax",@progbits
	.align	1
	.globl	hid_express_usb_mode_generate_12bits_reports
	.hidden	hid_express_usb_mode_generate_12bits_reports
	.type	hid_express_usb_mode_generate_12bits_reports, @function
hid_express_usb_mode_generate_12bits_reports:
.LFB18:
	.loc 1 227 1 is_stmt 1
	.cfi_startproc
.LVL23:
	.loc 1 228 5
	.loc 1 228 15 is_stmt 0
	andi	a4,a1,1
.LVL24:
	.loc 1 231 5 is_stmt 1
.LBB6:
	.loc 1 231 10
	.loc 1 231 118 is_stmt 0
	slli	a4,a4,2
.LVL25:
	lw	a5,usb_vCtrl_x
	add	a5,a5,a4
	lw	a2,4(a5)
.LVL26:
	.loc 1 231 250 is_stmt 1
	.loc 1 231 282 is_stmt 0
	lw	a3,hid_common
	.loc 1 231 324
	li	a5,4096
	.loc 1 231 84
	lw	t1,4(a0)
	.loc 1 231 324
	add	a3,a3,a5
	.loc 1 231 159
	li	a1,16711680
.LVL27:
	slli	a5,a2,16
.LVL28:
	.loc 1 231 207
	srai	a2,a2,8
.LVL29:
	.loc 1 231 159
	and	a5,a5,a1
.LVL30:
	.loc 1 231 242
	slli	a2,a2,24
	.loc 1 231 166
	or	a5,a5,a2
	.loc 1 231 84
	li	a2,65536
	addi	a2,a2,-1
	slli	t1,t1,8
.LVL31:
	and	t1,t1,a2
.LVL32:
	.loc 1 231 166
	or	a5,a5,t1
	.loc 1 231 26
	ori	a5,a5,2
	.loc 1 231 324
	sw	a5,1762(a3)
.LVL33:
.LBE6:
	.loc 1 231 8 is_stmt 1
	.loc 1 237 5
.LBB7:
	.loc 1 237 10
	.loc 1 237 262
	.loc 1 237 214 is_stmt 0
	lw	a5,16(a0)
	slli	a5,a5,16
	and	a5,a5,a1
	.loc 1 237 254
	lw	a1,20(a0)
	slli	a1,a1,24
	.loc 1 237 221
	or	a5,a5,a1
	.loc 1 237 58
	lw	a1,usb_vCtrl_y
	add	a4,a1,a4
	.loc 1 237 99
	lw	a4,4(a4)
	and	a4,a4,a2
	.loc 1 237 221
	or	a5,a5,a4
	.loc 1 237 328
	sw	a5,1766(a3)
.LVL34:
.LBE7:
	.loc 1 237 8 is_stmt 1
	.loc 1 257 1 is_stmt 0
	ret
	.cfi_endproc
.LFE18:
	.size	hid_express_usb_mode_generate_12bits_reports, .-hid_express_usb_mode_generate_12bits_reports
	.section	.text.hid_express_usb_mode_generate_kb_std_xy_reports,"ax",@progbits
	.align	1
	.globl	hid_express_usb_mode_generate_kb_std_xy_reports
	.hidden	hid_express_usb_mode_generate_kb_std_xy_reports
	.type	hid_express_usb_mode_generate_kb_std_xy_reports, @function
hid_express_usb_mode_generate_kb_std_xy_reports:
.LFB19:
	.loc 1 261 1 is_stmt 1
	.cfi_startproc
.LVL35:
	.loc 1 262 5
.LBB8:
	.loc 1 265 73 is_stmt 0
	lw	a4,28(a0)
	.loc 1 265 319
	li	a5,4096
	.loc 1 265 279
	lw	a3,hid_common
	.loc 1 265 105
	li	a2,65536
	.loc 1 265 319
	add	a3,a3,a5
	.loc 1 265 105
	addi	a2,a2,-1
	slli	a5,a4,8
	.loc 1 265 204
	srli	a0,a4,16
.LVL36:
	.loc 1 265 239
	slli	a0,a0,24
	.loc 1 265 105
	and	a5,a5,a2
	.loc 1 265 178
	or	a5,a5,a0
	.loc 1 265 171
	slli	a4,a4,8
	li	a0,16711680
	and	a4,a4,a0
	.loc 1 265 178
	or	a5,a5,a4
	.loc 1 265 26
	ori	a5,a5,1
.LBE8:
	.loc 1 262 15
	andi	a1,a1,1
.LVL37:
	.loc 1 265 5 is_stmt 1
.LBB9:
	.loc 1 265 10
	.loc 1 265 247
	.loc 1 265 319 is_stmt 0
	sw	a5,1762(a3)
.LBE9:
	.loc 1 265 8 is_stmt 1
	.loc 1 271 5
.LBB10:
	.loc 1 271 10
	.loc 1 271 209 is_stmt 0
	slli	a1,a1,2
.LVL38:
	lw	a5,usb_vCtrl_y
	add	a5,a5,a1
	lw	a4,4(a5)
.LVL39:
	.loc 1 271 341 is_stmt 1
	.loc 1 271 250 is_stmt 0
	slli	a5,a4,16
	.loc 1 271 298
	srai	a4,a4,8
.LVL40:
	.loc 1 271 333
	slli	a4,a4,24
	.loc 1 271 250
	and	a5,a5,a0
	.loc 1 271 257
	or	a5,a5,a4
	.loc 1 271 58
	lw	a4,usb_vCtrl_x
	add	a1,a4,a1
.LVL41:
	.loc 1 271 99
	lw	a4,4(a1)
	and	a4,a4,a2
	.loc 1 271 257
	or	a5,a5,a4
	.loc 1 271 405
	sw	a5,1766(a3)
.LVL42:
.LBE10:
	.loc 1 271 8 is_stmt 1
	.loc 1 291 1 is_stmt 0
	ret
	.cfi_endproc
.LFE19:
	.size	hid_express_usb_mode_generate_kb_std_xy_reports, .-hid_express_usb_mode_generate_kb_std_xy_reports
	.section	.text.hid_express_usb_mode_generate_kb_consumer_xy_reports,"ax",@progbits
	.align	1
	.globl	hid_express_usb_mode_generate_kb_consumer_xy_reports
	.hidden	hid_express_usb_mode_generate_kb_consumer_xy_reports
	.type	hid_express_usb_mode_generate_kb_consumer_xy_reports, @function
hid_express_usb_mode_generate_kb_consumer_xy_reports:
.LFB20:
	.loc 1 294 1 is_stmt 1
	.cfi_startproc
.LVL43:
	.loc 1 295 5
.LBB11:
	.loc 1 298 65 is_stmt 0
	lw	a4,36(a0)
	.loc 1 298 292
	li	a5,4096
	.loc 1 298 247
	lw	a3,hid_common
	.loc 1 298 107
	li	a2,65536
	.loc 1 298 292
	add	a3,a3,a5
	.loc 1 298 175
	li	a0,16711680
.LVL44:
	slli	a5,a4,8
	.loc 1 298 107
	addi	a2,a2,-1
	slli	a4,a4,8
	and	a4,a4,a2
	.loc 1 298 175
	and	a5,a5,a0
	.loc 1 298 113
	or	a5,a5,a4
	.loc 1 298 26
	ori	a5,a5,5
.LBE11:
	.loc 1 295 15
	andi	a1,a1,1
.LVL45:
	.loc 1 298 5 is_stmt 1
.LBB12:
	.loc 1 298 10
	.loc 1 298 215
	.loc 1 298 292 is_stmt 0
	sw	a5,1762(a3)
.LBE12:
	.loc 1 298 8 is_stmt 1
	.loc 1 304 5
.LBB13:
	.loc 1 304 10
	.loc 1 304 209 is_stmt 0
	slli	a1,a1,2
.LVL46:
	lw	a5,usb_vCtrl_y
	add	a5,a5,a1
	lw	a4,4(a5)
.LVL47:
	.loc 1 304 341 is_stmt 1
	.loc 1 304 250 is_stmt 0
	slli	a5,a4,16
	.loc 1 304 298
	srai	a4,a4,8
.LVL48:
	.loc 1 304 333
	slli	a4,a4,24
	.loc 1 304 250
	and	a5,a5,a0
	.loc 1 304 257
	or	a5,a5,a4
	.loc 1 304 58
	lw	a4,usb_vCtrl_x
	add	a4,a4,a1
	.loc 1 304 99
	lw	a4,4(a4)
	and	a4,a4,a2
	.loc 1 304 257
	or	a5,a5,a4
	.loc 1 304 410
	sw	a5,1766(a3)
.LVL49:
.LBE13:
	.loc 1 304 8 is_stmt 1
	.loc 1 324 1 is_stmt 0
	ret
	.cfi_endproc
.LFE20:
	.size	hid_express_usb_mode_generate_kb_consumer_xy_reports, .-hid_express_usb_mode_generate_kb_consumer_xy_reports
	.section	.text.hid_express_usb_last_report_is_kb,"ax",@progbits
	.align	1
	.globl	hid_express_usb_last_report_is_kb
	.hidden	hid_express_usb_last_report_is_kb
	.type	hid_express_usb_last_report_is_kb, @function
hid_express_usb_last_report_is_kb:
.LFB21:
	.loc 1 327 1 is_stmt 1
	.cfi_startproc
	.loc 1 329 5
	.loc 1 329 30 is_stmt 0
	lw	a0,last_report_id
	addi	a0,a0,-9
	.loc 1 334 1
	sltiu	a0,a0,2
	ret
	.cfi_endproc
.LFE21:
	.size	hid_express_usb_last_report_is_kb, .-hid_express_usb_last_report_is_kb
	.section	.text.hid_express_usb_x_y_data_prepare,"ax",@progbits
	.align	1
	.globl	hid_express_usb_x_y_data_prepare
	.hidden	hid_express_usb_x_y_data_prepare
	.type	hid_express_usb_x_y_data_prepare, @function
hid_express_usb_x_y_data_prepare:
.LFB22:
	.loc 1 338 1 is_stmt 1
	.cfi_startproc
.LVL50:
	.loc 1 340 5
	.loc 1 338 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 338 1
	mv	s1,a0
	mv	s0,a1
	.loc 1 340 8
	call	hid_express_usb_last_report_is_kb
.LVL51:
	.loc 1 340 7 discriminator 1
	beq	a0,zero,.L9
	.loc 1 342 19
	li	s0,1
.LVL52:
.L9:
	.loc 1 345 5 is_stmt 1
	lw	a2,8(s1)
	mv	a1,s0
	lw	a0,usb_vCtrl_x
	call	hid_express_generate_value_candidate
.LVL53:
	.loc 1 346 5
	lw	a2,12(s1)
	mv	a1,s0
	lw	a0,usb_vCtrl_y
	call	hid_express_generate_value_candidate
.LVL54:
	.loc 1 347 5
	.loc 1 348 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL55:
	lw	s1,0(sp)
	.cfi_restore 9
.LVL56:
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE22:
	.size	hid_express_usb_x_y_data_prepare, .-hid_express_usb_x_y_data_prepare
	.section	.text.hid_express_usb_delay_for_latency,"ax",@progbits
	.align	1
	.globl	hid_express_usb_delay_for_latency
	.hidden	hid_express_usb_delay_for_latency
	.type	hid_express_usb_delay_for_latency, @function
hid_express_usb_delay_for_latency:
.LFB23:
	.loc 1 352 1 is_stmt 1
	.cfi_startproc
	.loc 1 354 5
.LVL57:
	.loc 1 355 5
	.loc 1 352 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 355 13
	lla	s0,hid_common
	lw	a5,0(s0)
	.loc 1 352 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 356 7
	li	a4,30
	.loc 1 355 13
	lbu	a5,84(a5)
.LVL58:
	.loc 1 356 5 is_stmt 1
	.loc 1 356 7 is_stmt 0
	bgtu	a5,a4,.L13
	.loc 1 357 9 is_stmt 1
	.loc 1 357 18 is_stmt 0
	li	a0,30
	sub	a0,a0,a5
	andi	a0,a0,0xff
.LVL59:
	.loc 1 360 5 is_stmt 1
	.loc 1 360 7 is_stmt 0
	beq	a0,zero,.L13
	.loc 1 362 9 is_stmt 1
	call	hal_gpt_delay_us
.LVL60:
.L13:
	.loc 1 366 5
	.loc 1 366 15 is_stmt 0
	lw	a5,0(s0)
	.loc 1 368 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	.loc 1 366 43
	sw	zero,80(a5)
	.loc 1 368 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE23:
	.size	hid_express_usb_delay_for_latency, .-hid_express_usb_delay_for_latency
	.section	.text.hid_express_usb_wakeup_cm33_handler,"ax",@progbits
	.align	1
	.globl	hid_express_usb_wakeup_cm33_handler
	.hidden	hid_express_usb_wakeup_cm33_handler
	.type	hid_express_usb_wakeup_cm33_handler, @function
hid_express_usb_wakeup_cm33_handler:
.LFB24:
	.loc 1 372 1 is_stmt 1
	.cfi_startproc
	.loc 1 374 5
	.loc 1 374 15 is_stmt 0
	lw	a0,hid_common
	.loc 1 374 43
	sw	zero,80(a0)
	.loc 1 376 5 is_stmt 1
	.loc 1 376 24 is_stmt 0
	lw	a5,80(a0)
	.loc 1 376 7
	bne	a5,zero,.L18
	.loc 1 377 9 is_stmt 1
	.loc 1 377 71 is_stmt 0
	li	a5,4096
	addi	a5,a5,1762
	.loc 1 377 9
	add	a0,a0,a5
	tail	hid_express_usb_mode_send_report_to_CM33
.LVL61:
.L18:
	.loc 1 380 1
	ret
	.cfi_endproc
.LFE24:
	.size	hid_express_usb_wakeup_cm33_handler, .-hid_express_usb_wakeup_cm33_handler
	.section	.text.hid_express_usb_data_set_report_ready,"ax",@progbits
	.align	1
	.globl	hid_express_usb_data_set_report_ready
	.hidden	hid_express_usb_data_set_report_ready
	.type	hid_express_usb_data_set_report_ready, @function
hid_express_usb_data_set_report_ready:
.LFB25:
	.loc 1 383 45 is_stmt 1
	.cfi_startproc
	.loc 1 385 5
	.loc 1 385 15 is_stmt 0
	lw	a5,hid_common
	.loc 1 385 43
	li	a4,1
	sw	a4,80(a5)
	.loc 1 387 1
	ret
	.cfi_endproc
.LFE25:
	.size	hid_express_usb_data_set_report_ready, .-hid_express_usb_data_set_report_ready
	.section	.text.hid_express_usb_data_send,"ax",@progbits
	.align	1
	.globl	hid_express_usb_data_send
	.hidden	hid_express_usb_data_send
	.type	hid_express_usb_data_send, @function
hid_express_usb_data_send:
.LFB26:
	.loc 1 390 1 is_stmt 1
	.cfi_startproc
.LVL62:
	.loc 1 391 5
	.loc 1 390 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	a1,4(sp)
	sw	a3,0(sp)
	sw	ra,16(sp)
	sw	s0,12(sp)
	sw	s1,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 390 1
	mv	s1,a0
	.loc 1 391 26
	call	riscv_hid_report_id_select
.LVL63:
	mv	s0,a0
.LVL64:
	.loc 1 394 5 is_stmt 1
	.loc 1 394 8 is_stmt 0
	call	hid_express_usb_last_report_is_kb
.LVL65:
	.loc 1 394 7 discriminator 1
	lw	a3,0(sp)
	lw	a1,4(sp)
	beq	a0,zero,.L22
	.loc 1 396 19
	li	a1,1
.L22:
.LVL66:
	.loc 1 398 5 is_stmt 1
	.loc 1 398 20 is_stmt 0
	sw	s0,last_report_id,a5
	.loc 1 401 5 is_stmt 1
	li	a5,9
	addi	s0,s0,-1
.LVL67:
	bgtu	s0,a5,.L23
	lla	a4,.L25
	slli	s0,s0,2
	add	s0,s0,a4
	lw	a5,0(s0)
	add	a5,a5,a4
	jr	a5
	.section	.rodata.hid_express_usb_data_send,"a",@progbits
	.align	2
	.align	2
.L25:
	.word	.L29-.L25
	.word	.L28-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L27-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L23-.L25
	.word	.L26-.L25
	.word	.L24-.L25
	.section	.text.hid_express_usb_data_send
.L29:
	.loc 1 413 13
	mv	a0,s1
	call	hid_express_usb_mode_generate_kb_std_xy_reports
.LVL68:
	.loc 1 414 13
.L30:
	.loc 1 444 5
	.loc 1 444 15 is_stmt 0
	lw	a5,hid_common
	.loc 1 444 43
	li	a4,2
	sw	a4,80(a5)
	.loc 1 476 5 is_stmt 1
.L23:
	.loc 1 477 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
.LVL69:
	li	a0,0
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
.LVL70:
	jr	ra
.LVL71:
.L27:
	.cfi_restore_state
	.loc 1 416 13 is_stmt 1
	mv	a0,s1
	call	hid_express_usb_mode_generate_kb_consumer_xy_reports
.LVL72:
	.loc 1 417 13
	j	.L30
.LVL73:
.L24:
	.loc 1 421 13
	mv	a0,s1
	call	hid_express_usb_mode_generate_kb_consumer_reports
.LVL74:
	.loc 1 422 13
	j	.L30
.LVL75:
.L26:
	.loc 1 426 13
	mv	a0,s1
	call	hid_express_usb_mode_generate_kb_std_reports
.LVL76:
	.loc 1 427 13
	j	.L30
.LVL77:
.L28:
	.loc 1 431 13
	.loc 1 433 13
	.loc 1 433 15 is_stmt 0
	beq	a3,zero,.L30
	.loc 1 434 17 is_stmt 1
	mv	a0,s1
	call	hid_express_usb_mode_generate_12bits_reports
.LVL78:
	j	.L30
	.cfi_endproc
.LFE26:
	.size	hid_express_usb_data_send, .-hid_express_usb_data_send
	.section	.text.hid_express_usb_mode_init,"ax",@progbits
	.align	1
	.globl	hid_express_usb_mode_init
	.hidden	hid_express_usb_mode_init
	.type	hid_express_usb_mode_init, @function
hid_express_usb_mode_init:
.LFB27:
	.loc 1 480 1
	.cfi_startproc
	.loc 1 482 5
	.loc 1 482 15 is_stmt 0
	lw	a5,hid_common
	.loc 1 482 43
	sw	zero,80(a5)
	.loc 1 486 5 is_stmt 1
	lla	a1,usb_vCtrl_y
	lla	a0,usb_vCtrl_x
	tail	hid_express_x_y_buf_init
.LVL79:
	.cfi_endproc
.LFE27:
	.size	hid_express_usb_mode_init, .-hid_express_usb_mode_init
	.hidden	usb_vCtrl_y
	.globl	usb_vCtrl_y
	.section	.sbss.usb_vCtrl_y,"aw",@nobits
	.align	2
	.type	usb_vCtrl_y, @object
	.size	usb_vCtrl_y, 4
usb_vCtrl_y:
	.zero	4
	.hidden	usb_vCtrl_x
	.globl	usb_vCtrl_x
	.section	.sbss.usb_vCtrl_x,"aw",@nobits
	.align	2
	.type	usb_vCtrl_x, @object
	.size	usb_vCtrl_x, 4
usb_vCtrl_x:
	.zero	4
	.section	.sdata.last_report_id,"aw"
	.align	2
	.type	last_report_id, @object
	.size	last_report_id, 4
last_report_id:
	.word	2
	.hidden	ccni_evt_status
	.globl	ccni_evt_status
	.section	.sbss.ccni_evt_status,"aw",@nobits
	.align	2
	.type	ccni_evt_status, @object
	.size	ccni_evt_status, 4
ccni_evt_status:
	.zero	4
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 4 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_key_remap.h"
	.file 6 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common.h"
	.file 8 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 9 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.file 10 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 11 "/workdir/airoha/common/drivers/chip/ab162x/../inc/hal_ccni.h"
	.file 12 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_ccni_config.h"
	.file 13 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_xy_queue.h"
	.file 14 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_report_id_selector.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xf2a
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x2b
	.4byte	.LASF196
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL29
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
	.uleb128 0x2c
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x6
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x2d
	.byte	0x4
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x2
	.byte	0x22
	.byte	0x15
	.4byte	0x34
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x2
	.byte	0x25
	.byte	0x13
	.4byte	0x42
	.uleb128 0x3
	.4byte	.LASF15
	.byte	0x2
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x3
	.4byte	.LASF16
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x3
	.4byte	.LASF17
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x3
	.4byte	.LASF18
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x2e
	.4byte	0xb8
	.uleb128 0x7
	.4byte	0xa0
	.4byte	0xd9
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x7
	.4byte	0xb8
	.4byte	0xe9
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x3
	.byte	0x50
	.byte	0xe
	.4byte	0x12c
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
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.byte	0xa
	.byte	0x3
	.byte	0x5e
	.4byte	0x14f
	.uleb128 0x2
	.4byte	.LASF28
	.byte	0x3
	.byte	0x60
	.byte	0xe
	.4byte	0xac
	.byte	0
	.uleb128 0x4
	.string	"pin"
	.byte	0x3
	.byte	0x61
	.byte	0xd
	.4byte	0x14f
	.byte	0x2
	.byte	0
	.uleb128 0x7
	.4byte	0xa0
	.4byte	0x15f
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.4byte	.LASF29
	.byte	0x3
	.byte	0x62
	.byte	0x2
	.4byte	0x12c
	.uleb128 0x6
	.byte	0x1
	.byte	0x2
	.4byte	.LASF30
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x4
	.byte	0x31
	.byte	0x1
	.4byte	0x1af
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.byte	0x2
	.byte	0x4
	.byte	0x3f
	.4byte	0x1d2
	.uleb128 0x2
	.4byte	.LASF39
	.byte	0x4
	.byte	0x41
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x4
	.byte	0x42
	.byte	0xd
	.4byte	0xa0
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF41
	.byte	0x4
	.byte	0x44
	.byte	0x2
	.4byte	0x1af
	.uleb128 0x1d
	.2byte	0x11c
	.2byte	0x109
	.byte	0xd
	.4byte	0x203
	.uleb128 0x16
	.4byte	.LASF42
	.byte	0x5
	.2byte	0x10a
	.byte	0x1a
	.4byte	0x203
	.uleb128 0x2f
	.string	"x_y"
	.byte	0x5
	.2byte	0x10c
	.byte	0x1a
	.4byte	0x203
	.byte	0
	.uleb128 0x7
	.4byte	0xb8
	.4byte	0x213
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x46
	.byte	0
	.uleb128 0x1e
	.2byte	0x23c
	.2byte	0x105
	.4byte	0x24b
	.uleb128 0x17
	.4byte	.LASF43
	.2byte	0x106
	.byte	0x16
	.4byte	0xac
	.byte	0
	.uleb128 0x17
	.4byte	.LASF44
	.2byte	0x107
	.byte	0x16
	.4byte	0xac
	.byte	0x2
	.uleb128 0x17
	.4byte	.LASF45
	.2byte	0x108
	.byte	0x16
	.4byte	0x203
	.byte	0x4
	.uleb128 0x30
	.4byte	0x1de
	.2byte	0x120
	.byte	0
	.uleb128 0x1d
	.2byte	0x23c
	.2byte	0x103
	.byte	0x5
	.4byte	0x268
	.uleb128 0x16
	.4byte	.LASF46
	.byte	0x5
	.2byte	0x104
	.byte	0x12
	.4byte	0xb8
	.uleb128 0x31
	.4byte	0x213
	.byte	0
	.uleb128 0x1e
	.2byte	0x240
	.2byte	0x101
	.4byte	0x285
	.uleb128 0x17
	.4byte	.LASF47
	.2byte	0x102
	.byte	0xe
	.4byte	0xb8
	.byte	0
	.uleb128 0x1f
	.4byte	0x24b
	.byte	0x4
	.byte	0
	.uleb128 0x11
	.4byte	.LASF48
	.byte	0x5
	.2byte	0x111
	.byte	0x1e
	.4byte	0x268
	.uleb128 0x5
	.byte	0x8
	.byte	0x6
	.byte	0x50
	.4byte	0x2e1
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x6
	.byte	0x51
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x4
	.string	"k"
	.byte	0x6
	.byte	0x52
	.byte	0xd
	.4byte	0xa0
	.byte	0x1
	.uleb128 0x4
	.string	"x"
	.byte	0x6
	.byte	0x53
	.byte	0xd
	.4byte	0x88
	.byte	0x2
	.uleb128 0x4
	.string	"y"
	.byte	0x6
	.byte	0x54
	.byte	0xd
	.4byte	0x88
	.byte	0x4
	.uleb128 0x4
	.string	"z1"
	.byte	0x6
	.byte	0x55
	.byte	0xc
	.4byte	0x7c
	.byte	0x6
	.uleb128 0x4
	.string	"z2"
	.byte	0x6
	.byte	0x56
	.byte	0xc
	.4byte	0x7c
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.4byte	.LASF50
	.byte	0x6
	.byte	0x57
	.byte	0x1f
	.4byte	0x292
	.uleb128 0x5
	.byte	0x8
	.byte	0x6
	.byte	0x88
	.4byte	0x333
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x6
	.byte	0x89
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF51
	.byte	0x6
	.byte	0x8a
	.byte	0xd
	.4byte	0xa0
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF42
	.byte	0x6
	.byte	0x8b
	.byte	0xd
	.4byte	0xc9
	.byte	0x2
	.uleb128 0x4
	.string	"x"
	.byte	0x6
	.byte	0x8c
	.byte	0xd
	.4byte	0x88
	.byte	0x4
	.uleb128 0x4
	.string	"y"
	.byte	0x6
	.byte	0x8d
	.byte	0xd
	.4byte	0x88
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.4byte	.LASF52
	.byte	0x6
	.byte	0x8e
	.byte	0x1e
	.4byte	0x2ed
	.uleb128 0x5
	.byte	0x8
	.byte	0x6
	.byte	0x90
	.4byte	0x385
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x6
	.byte	0x91
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF53
	.byte	0x6
	.byte	0x92
	.byte	0xe
	.4byte	0xac
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF54
	.byte	0x6
	.byte	0x93
	.byte	0xd
	.4byte	0xa0
	.byte	0x3
	.uleb128 0x4
	.string	"x"
	.byte	0x6
	.byte	0x94
	.byte	0xd
	.4byte	0x88
	.byte	0x4
	.uleb128 0x4
	.string	"y"
	.byte	0x6
	.byte	0x95
	.byte	0xd
	.4byte	0x88
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.4byte	.LASF55
	.byte	0x6
	.byte	0x96
	.byte	0x1f
	.4byte	0x33f
	.uleb128 0x7
	.4byte	0xa0
	.4byte	0x3a1
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.byte	0x6
	.byte	0xa2
	.4byte	0x3de
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x6
	.byte	0xa3
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF51
	.byte	0x6
	.byte	0xa4
	.byte	0xd
	.4byte	0xa0
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF42
	.byte	0x6
	.byte	0xa5
	.byte	0xd
	.4byte	0x391
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF56
	.byte	0x6
	.byte	0xa6
	.byte	0xd
	.4byte	0xa0
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.4byte	.LASF57
	.byte	0x6
	.byte	0xa7
	.byte	0x1e
	.4byte	0x3a1
	.uleb128 0x5
	.byte	0x8
	.byte	0x6
	.byte	0xa9
	.4byte	0x427
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x6
	.byte	0xaa
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF53
	.byte	0x6
	.byte	0xab
	.byte	0xd
	.4byte	0x427
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF54
	.byte	0x6
	.byte	0xac
	.byte	0xd
	.4byte	0xa0
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF56
	.byte	0x6
	.byte	0xad
	.byte	0xd
	.4byte	0xc9
	.byte	0x6
	.byte	0
	.uleb128 0x7
	.4byte	0xa0
	.4byte	0x437
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF58
	.byte	0x6
	.byte	0xae
	.byte	0x1f
	.4byte	0x3ea
	.uleb128 0x7
	.4byte	0xa0
	.4byte	0x453
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x5
	.byte	0x2
	.byte	0x7
	.byte	0x49
	.4byte	0x475
	.uleb128 0x4
	.string	"id"
	.byte	0x7
	.byte	0x4b
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF59
	.byte	0x7
	.byte	0x4c
	.byte	0xd
	.4byte	0xa0
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF60
	.byte	0x7
	.byte	0x4d
	.byte	0x2
	.4byte	0x453
	.uleb128 0x32
	.byte	0x8
	.byte	0x7
	.byte	0x53
	.byte	0x5
	.4byte	0x4c2
	.uleb128 0x12
	.4byte	.LASF61
	.byte	0x54
	.byte	0x25
	.4byte	0x2e1
	.uleb128 0x12
	.4byte	.LASF62
	.byte	0x56
	.byte	0x23
	.4byte	0x333
	.uleb128 0x12
	.4byte	.LASF63
	.byte	0x57
	.byte	0x28
	.4byte	0x385
	.uleb128 0x12
	.4byte	.LASF64
	.byte	0x59
	.byte	0x20
	.4byte	0x3de
	.uleb128 0x12
	.4byte	.LASF65
	.byte	0x5a
	.byte	0x25
	.4byte	0x437
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.byte	0x7
	.byte	0x4f
	.4byte	0x4d1
	.uleb128 0x1f
	.4byte	0x481
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF66
	.byte	0x7
	.byte	0x5f
	.byte	0xa
	.4byte	0x4c2
	.uleb128 0x5
	.byte	0x8
	.byte	0x7
	.byte	0x61
	.4byte	0x500
	.uleb128 0x2
	.4byte	.LASF67
	.byte	0x7
	.byte	0x62
	.byte	0xe
	.4byte	0xb8
	.byte	0
	.uleb128 0x2
	.4byte	.LASF68
	.byte	0x7
	.byte	0x63
	.byte	0xe
	.4byte	0xb8
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF69
	.byte	0x7
	.byte	0x67
	.byte	0x2
	.4byte	0x4dd
	.uleb128 0x33
	.4byte	0x500
	.uleb128 0x5
	.byte	0x3
	.byte	0x7
	.byte	0x69
	.4byte	0x541
	.uleb128 0x2
	.4byte	.LASF70
	.byte	0x7
	.byte	0x6a
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF71
	.byte	0x7
	.byte	0x6b
	.byte	0xd
	.4byte	0xa0
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF72
	.byte	0x7
	.byte	0x6c
	.byte	0xd
	.4byte	0xa0
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF73
	.byte	0x7
	.byte	0x6d
	.byte	0x3
	.4byte	0x511
	.uleb128 0x5
	.byte	0x18
	.byte	0x7
	.byte	0x7e
	.4byte	0x5a4
	.uleb128 0x2
	.4byte	.LASF74
	.byte	0x7
	.byte	0x7f
	.byte	0xe
	.4byte	0xb8
	.byte	0
	.uleb128 0x2
	.4byte	.LASF75
	.byte	0x7
	.byte	0x80
	.byte	0xe
	.4byte	0xb8
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF76
	.byte	0x7
	.byte	0x81
	.byte	0xe
	.4byte	0xb8
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF77
	.byte	0x7
	.byte	0x82
	.byte	0xe
	.4byte	0xb8
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF78
	.byte	0x7
	.byte	0x83
	.byte	0x17
	.4byte	0xc4
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF79
	.byte	0x7
	.byte	0x84
	.byte	0xd
	.4byte	0xa0
	.byte	0x14
	.byte	0
	.uleb128 0x3
	.4byte	.LASF80
	.byte	0x7
	.byte	0x94
	.byte	0x3
	.4byte	0x54d
	.uleb128 0x5
	.byte	0x40
	.byte	0x7
	.byte	0x96
	.4byte	0x66e
	.uleb128 0x2
	.4byte	.LASF77
	.byte	0x7
	.byte	0x97
	.byte	0xe
	.4byte	0xb8
	.byte	0
	.uleb128 0x2
	.4byte	.LASF81
	.byte	0x7
	.byte	0x98
	.byte	0xe
	.4byte	0xb8
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF82
	.byte	0x7
	.byte	0x9b
	.byte	0x1e
	.4byte	0x66e
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF83
	.byte	0x7
	.byte	0x9c
	.byte	0xe
	.4byte	0xb8
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF84
	.byte	0x7
	.byte	0x9d
	.byte	0xe
	.4byte	0xb8
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF85
	.byte	0x7
	.byte	0x9f
	.byte	0x1e
	.4byte	0x475
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF86
	.byte	0x7
	.byte	0xa0
	.byte	0x1e
	.4byte	0x475
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF87
	.byte	0x7
	.byte	0xa5
	.byte	0xe
	.4byte	0xb8
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF88
	.byte	0x7
	.byte	0xa6
	.byte	0xe
	.4byte	0xb8
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF89
	.byte	0x7
	.byte	0xae
	.byte	0xe
	.4byte	0x673
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF90
	.byte	0x7
	.byte	0xb1
	.byte	0xd
	.4byte	0x443
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF91
	.byte	0x7
	.byte	0xb2
	.byte	0xd
	.4byte	0xa0
	.byte	0x38
	.uleb128 0x4
	.string	"rr"
	.byte	0x7
	.byte	0xbb
	.byte	0x1d
	.4byte	0x1d2
	.byte	0x39
	.uleb128 0x4
	.string	"deb"
	.byte	0x7
	.byte	0xbd
	.byte	0x17
	.4byte	0x541
	.byte	0x3b
	.byte	0
	.uleb128 0xd
	.4byte	0x50c
	.uleb128 0x7
	.4byte	0xac
	.4byte	0x683
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.4byte	.LASF92
	.byte	0x7
	.byte	0xbf
	.byte	0x3
	.4byte	0x5b0
	.uleb128 0x34
	.2byte	0x16ec
	.byte	0x7
	.byte	0xc1
	.byte	0x9
	.4byte	0x6dc
	.uleb128 0x4
	.string	"app"
	.byte	0x7
	.byte	0xc3
	.byte	0x1b
	.4byte	0x683
	.byte	0
	.uleb128 0x4
	.string	"hid"
	.byte	0x7
	.byte	0xc4
	.byte	0x1b
	.4byte	0x5a4
	.byte	0x40
	.uleb128 0x4
	.string	"dbg"
	.byte	0x7
	.byte	0xc5
	.byte	0x17
	.4byte	0x15f
	.byte	0x58
	.uleb128 0x2
	.4byte	.LASF93
	.byte	0x7
	.byte	0xc7
	.byte	0x17
	.4byte	0x6dc
	.byte	0x62
	.uleb128 0x35
	.4byte	.LASF94
	.byte	0x7
	.byte	0xca
	.byte	0x1d
	.4byte	0x6ec
	.2byte	0x16e2
	.byte	0
	.uleb128 0x7
	.4byte	0x285
	.4byte	0x6ec
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x7
	.4byte	0x4d1
	.4byte	0x6fc
	.uleb128 0x8
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF95
	.byte	0x7
	.byte	0xcc
	.byte	0x3
	.4byte	0x68f
	.uleb128 0x36
	.4byte	.LASF167
	.byte	0x7
	.byte	0xd2
	.byte	0x19
	.4byte	0x714
	.uleb128 0xd
	.4byte	0x6fc
	.uleb128 0x5
	.byte	0x28
	.byte	0x8
	.byte	0x8d
	.4byte	0x78f
	.uleb128 0x2
	.4byte	.LASF96
	.byte	0x8
	.byte	0x8e
	.byte	0xe
	.4byte	0xb8
	.byte	0
	.uleb128 0x4
	.string	"k"
	.byte	0x8
	.byte	0x8f
	.byte	0xe
	.4byte	0xb8
	.byte	0x4
	.uleb128 0x4
	.string	"x"
	.byte	0x8
	.byte	0x90
	.byte	0xd
	.4byte	0x94
	.byte	0x8
	.uleb128 0x4
	.string	"y"
	.byte	0x8
	.byte	0x91
	.byte	0xd
	.4byte	0x94
	.byte	0xc
	.uleb128 0x4
	.string	"z1"
	.byte	0x8
	.byte	0x92
	.byte	0xd
	.4byte	0x94
	.byte	0x10
	.uleb128 0x4
	.string	"z2"
	.byte	0x8
	.byte	0x93
	.byte	0xd
	.4byte	0x94
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF97
	.byte	0x8
	.byte	0x94
	.byte	0xe
	.4byte	0xb8
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF98
	.byte	0x8
	.byte	0x95
	.byte	0xe
	.4byte	0xd9
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF99
	.byte	0x8
	.byte	0x96
	.byte	0xe
	.4byte	0xb8
	.byte	0x24
	.byte	0
	.uleb128 0x3
	.4byte	.LASF100
	.byte	0x8
	.byte	0x9c
	.byte	0x2
	.4byte	0x719
	.uleb128 0x3
	.4byte	.LASF101
	.byte	0x8
	.byte	0xc9
	.byte	0x2d
	.4byte	0x57
	.uleb128 0xd
	.4byte	0x78f
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x9
	.byte	0x6e
	.byte	0xe
	.4byte	0x7d1
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x3
	.byte	0
	.uleb128 0x20
	.4byte	0x65
	.byte	0xa
	.2byte	0x153
	.4byte	0x80e
	.uleb128 0xa
	.4byte	.LASF106
	.sleb128 -7
	.uleb128 0xa
	.4byte	.LASF107
	.sleb128 -6
	.uleb128 0xa
	.4byte	.LASF108
	.sleb128 -5
	.uleb128 0xa
	.4byte	.LASF109
	.sleb128 -4
	.uleb128 0xa
	.4byte	.LASF110
	.sleb128 -3
	.uleb128 0xa
	.4byte	.LASF111
	.sleb128 -2
	.uleb128 0xa
	.4byte	.LASF112
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	.LASF114
	.byte	0xa
	.2byte	0x15c
	.byte	0x3
	.4byte	0x7d1
	.uleb128 0x20
	.4byte	0x65
	.byte	0xb
	.2byte	0x120
	.4byte	0x846
	.uleb128 0xa
	.4byte	.LASF115
	.sleb128 -4
	.uleb128 0xa
	.4byte	.LASF116
	.sleb128 -3
	.uleb128 0xa
	.4byte	.LASF117
	.sleb128 -2
	.uleb128 0xa
	.4byte	.LASF118
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	.LASF120
	.byte	0xb
	.2byte	0x126
	.byte	0x3
	.4byte	0x81b
	.uleb128 0x11
	.4byte	.LASF121
	.byte	0xb
	.2byte	0x137
	.byte	0x12
	.4byte	0xb8
	.uleb128 0x37
	.byte	0x8
	.byte	0xb
	.2byte	0x13d
	.byte	0x5
	.4byte	0x885
	.uleb128 0x21
	.string	"ptr"
	.2byte	0x13e
	.byte	0xf
	.4byte	0x73
	.byte	0
	.uleb128 0x21
	.string	"len"
	.2byte	0x13f
	.byte	0x12
	.4byte	0xb8
	.byte	0x4
	.byte	0
	.uleb128 0x38
	.byte	0x8
	.byte	0xb
	.2byte	0x13c
	.byte	0x9
	.4byte	0x8aa
	.uleb128 0x16
	.4byte	.LASF122
	.byte	0xb
	.2byte	0x140
	.byte	0x7
	.4byte	0x860
	.uleb128 0x16
	.4byte	.LASF123
	.byte	0xb
	.2byte	0x141
	.byte	0xe
	.4byte	0xd9
	.byte	0
	.uleb128 0x11
	.4byte	.LASF124
	.byte	0xb
	.2byte	0x142
	.byte	0x3
	.4byte	0x885
	.uleb128 0xd
	.4byte	0x8aa
	.uleb128 0x10
	.4byte	0x2d
	.byte	0xc
	.byte	0x35
	.byte	0xe
	.4byte	0x8ea
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x3
	.uleb128 0x39
	.4byte	.LASF129
	.4byte	0xffffffff
	.byte	0
	.uleb128 0x10
	.4byte	0x2d
	.byte	0xc
	.byte	0x3d
	.byte	0xe
	.4byte	0x9bd
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
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF157
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF159
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF162
	.byte	0x20
	.byte	0
	.uleb128 0x5
	.byte	0x10
	.byte	0xd
	.byte	0x37
	.4byte	0x9ed
	.uleb128 0x2
	.4byte	.LASF163
	.byte	0xd
	.byte	0x38
	.byte	0xd
	.4byte	0x9ed
	.byte	0
	.uleb128 0x2
	.4byte	.LASF164
	.byte	0xd
	.byte	0x39
	.byte	0xd
	.4byte	0x9fd
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF165
	.byte	0xd
	.byte	0x3a
	.byte	0xd
	.4byte	0x94
	.byte	0xc
	.byte	0
	.uleb128 0x7
	.4byte	0x94
	.4byte	0x9fd
	.uleb128 0x8
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	0x94
	.4byte	0xa0d
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF166
	.byte	0xd
	.byte	0x3c
	.byte	0x2
	.4byte	0x9bd
	.uleb128 0x18
	.4byte	.LASF168
	.byte	0x42
	.byte	0xa
	.4byte	0xb8
	.uleb128 0x5
	.byte	0x3
	.4byte	ccni_evt_status
	.uleb128 0x3a
	.4byte	.LASF180
	.byte	0x1
	.byte	0x45
	.byte	0x11
	.4byte	0xb8
	.uleb128 0x5
	.byte	0x3
	.4byte	last_report_id
	.uleb128 0x18
	.4byte	.LASF169
	.byte	0x47
	.byte	0x18
	.4byte	0xa4d
	.uleb128 0x5
	.byte	0x3
	.4byte	usb_vCtrl_x
	.uleb128 0xd
	.4byte	0xa0d
	.uleb128 0x18
	.4byte	.LASF170
	.byte	0x48
	.byte	0x18
	.4byte	0xa4d
	.uleb128 0x5
	.byte	0x3
	.4byte	usb_vCtrl_y
	.uleb128 0x22
	.4byte	.LASF173
	.byte	0x3e
	.4byte	0xa78
	.uleb128 0xc
	.4byte	0xa78
	.uleb128 0xc
	.4byte	0xa78
	.byte	0
	.uleb128 0xd
	.4byte	0xa4d
	.uleb128 0x3b
	.4byte	.LASF171
	.byte	0xe
	.byte	0x27
	.byte	0xa
	.4byte	0xb8
	.4byte	0xa93
	.uleb128 0xc
	.4byte	0x7a7
	.byte	0
	.uleb128 0x23
	.4byte	.LASF172
	.byte	0xa
	.2byte	0x18d
	.byte	0x12
	.4byte	0x80e
	.4byte	0xaaa
	.uleb128 0xc
	.4byte	0xb8
	.byte	0
	.uleb128 0x22
	.4byte	.LASF174
	.byte	0x40
	.4byte	0xac4
	.uleb128 0xc
	.4byte	0xa4d
	.uleb128 0xc
	.4byte	0xb8
	.uleb128 0xc
	.4byte	0x94
	.byte	0
	.uleb128 0x23
	.4byte	.LASF175
	.byte	0xb
	.2byte	0x15f
	.byte	0x13
	.4byte	0x846
	.4byte	0xae0
	.uleb128 0xc
	.4byte	0x853
	.uleb128 0xc
	.4byte	0x8b7
	.byte	0
	.uleb128 0x19
	.4byte	.LASF181
	.2byte	0x1df
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb12
	.uleb128 0x24
	.4byte	.LVL79
	.4byte	0xa63
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	usb_vCtrl_x
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	usb_vCtrl_y
	.byte	0
	.byte	0
	.uleb128 0x25
	.4byte	.LASF186
	.2byte	0x185
	.4byte	0x65
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbf9
	.uleb128 0xb
	.4byte	.LASF176
	.2byte	0x185
	.byte	0x34
	.4byte	0x7a7
	.4byte	.LLST24
	.uleb128 0xb
	.4byte	.LASF177
	.2byte	0x185
	.byte	0x47
	.4byte	0xb8
	.4byte	.LLST25
	.uleb128 0xb
	.4byte	.LASF178
	.2byte	0x185
	.byte	0x5b
	.4byte	0xb8
	.4byte	.LLST26
	.uleb128 0xb
	.4byte	.LASF179
	.2byte	0x185
	.byte	0x67
	.4byte	0x16b
	.4byte	.LLST27
	.uleb128 0x13
	.4byte	.LASF49
	.2byte	0x187
	.byte	0xe
	.4byte	0xb8
	.4byte	.LLST28
	.uleb128 0xe
	.4byte	.LVL63
	.4byte	0xa7d
	.4byte	0xb8f
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0x1a
	.4byte	.LVL65
	.4byte	0xce1
	.uleb128 0xe
	.4byte	.LVL68
	.4byte	0xd5d
	.4byte	0xbac
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0xe
	.4byte	.LVL72
	.4byte	0xcf8
	.4byte	0xbc0
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0xe
	.4byte	.LVL74
	.4byte	0xe8e
	.4byte	0xbd4
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0xe
	.4byte	.LVL76
	.4byte	0xe27
	.4byte	0xbe8
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0x26
	.4byte	.LVL78
	.4byte	0xdc2
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x3c
	.4byte	.LASF197
	.byte	0x1
	.2byte	0x17f
	.byte	0x6
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x19
	.4byte	.LASF182
	.2byte	0x173
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc2b
	.uleb128 0x3d
	.4byte	.LVL61
	.4byte	0xef3
	.byte	0
	.uleb128 0x19
	.4byte	.LASF183
	.2byte	0x15f
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc6a
	.uleb128 0x13
	.4byte	.LASF184
	.2byte	0x162
	.byte	0xd
	.4byte	0xa0
	.4byte	.LLST22
	.uleb128 0x13
	.4byte	.LASF185
	.2byte	0x163
	.byte	0xd
	.4byte	0xa0
	.4byte	.LLST23
	.uleb128 0x1a
	.4byte	.LVL60
	.4byte	0xa93
	.byte	0
	.uleb128 0x25
	.4byte	.LASF187
	.2byte	0x151
	.4byte	0x65
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xce1
	.uleb128 0xb
	.4byte	.LASF176
	.2byte	0x151
	.byte	0x3b
	.4byte	0x7a7
	.4byte	.LLST19
	.uleb128 0xb
	.4byte	.LASF177
	.2byte	0x151
	.byte	0x4e
	.4byte	0xb8
	.4byte	.LLST20
	.uleb128 0xb
	.4byte	.LASF178
	.2byte	0x151
	.byte	0x62
	.4byte	0xb8
	.4byte	.LLST21
	.uleb128 0x1a
	.4byte	.LVL51
	.4byte	0xce1
	.uleb128 0xe
	.4byte	.LVL53
	.4byte	0xaaa
	.4byte	0xcd0
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x26
	.4byte	.LVL54
	.4byte	0xaaa
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x3e
	.4byte	.LASF198
	.byte	0x1
	.2byte	0x146
	.byte	0xa
	.4byte	0xb8
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x27
	.4byte	.LASF189
	.2byte	0x125
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd5d
	.uleb128 0xb
	.4byte	.LASF176
	.2byte	0x125
	.byte	0x50
	.4byte	0x7a7
	.4byte	.LLST15
	.uleb128 0xb
	.4byte	.LASF177
	.2byte	0x125
	.byte	0x63
	.4byte	0xb8
	.4byte	.LLST16
	.uleb128 0x28
	.4byte	.LLRL17
	.4byte	0xd42
	.uleb128 0x29
	.4byte	.LASF188
	.2byte	0x12a
	.4byte	0x79b
	.byte	0
	.uleb128 0x14
	.4byte	.LBB13
	.4byte	.LBE13-.LBB13
	.uleb128 0x13
	.4byte	.LASF188
	.2byte	0x130
	.byte	0x1a
	.4byte	0x79b
	.4byte	.LLST18
	.byte	0
	.byte	0
	.uleb128 0x27
	.4byte	.LASF190
	.2byte	0x104
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xdc2
	.uleb128 0xb
	.4byte	.LASF176
	.2byte	0x104
	.byte	0x4b
	.4byte	0x7a7
	.4byte	.LLST11
	.uleb128 0xb
	.4byte	.LASF177
	.2byte	0x104
	.byte	0x5e
	.4byte	0xb8
	.4byte	.LLST12
	.uleb128 0x28
	.4byte	.LLRL13
	.4byte	0xda7
	.uleb128 0x29
	.4byte	.LASF188
	.2byte	0x109
	.4byte	0x79b
	.byte	0
	.uleb128 0x14
	.4byte	.LBB10
	.4byte	.LBE10-.LBB10
	.uleb128 0x13
	.4byte	.LASF188
	.2byte	0x10f
	.byte	0x1a
	.4byte	0x79b
	.4byte	.LLST14
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF191
	.byte	0xe2
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe27
	.uleb128 0x2a
	.4byte	.LASF176
	.byte	0xe2
	.byte	0x48
	.4byte	0x7a7
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x15
	.4byte	.LASF177
	.byte	0xe2
	.byte	0x5b
	.4byte	0xb8
	.4byte	.LLST8
	.uleb128 0x1c
	.4byte	.LBB6
	.4byte	.LBE6-.LBB6
	.4byte	0xe0e
	.uleb128 0xf
	.4byte	.LASF188
	.byte	0xe7
	.4byte	0x79b
	.4byte	.LLST9
	.byte	0
	.uleb128 0x14
	.4byte	.LBB7
	.4byte	.LBE7-.LBB7
	.uleb128 0xf
	.4byte	.LASF188
	.byte	0xed
	.4byte	0x79b
	.4byte	.LLST10
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF192
	.byte	0x82
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe8e
	.uleb128 0x15
	.4byte	.LASF176
	.byte	0x82
	.byte	0x48
	.4byte	0x7a7
	.4byte	.LLST4
	.uleb128 0x15
	.4byte	.LASF177
	.byte	0x82
	.byte	0x5b
	.4byte	0xb8
	.4byte	.LLST5
	.uleb128 0x1c
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.4byte	0xe75
	.uleb128 0xf
	.4byte	.LASF188
	.byte	0x86
	.4byte	0x79b
	.4byte	.LLST6
	.byte	0
	.uleb128 0x14
	.4byte	.LBB5
	.4byte	.LBE5-.LBB5
	.uleb128 0xf
	.4byte	.LASF188
	.byte	0x8c
	.4byte	0x79b
	.4byte	.LLST7
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF193
	.byte	0x60
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xef3
	.uleb128 0x2a
	.4byte	.LASF176
	.byte	0x60
	.byte	0x4d
	.4byte	0x7a7
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x15
	.4byte	.LASF177
	.byte	0x60
	.byte	0x60
	.4byte	0xb8
	.4byte	.LLST1
	.uleb128 0x1c
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.4byte	0xeda
	.uleb128 0xf
	.4byte	.LASF188
	.byte	0x64
	.4byte	0x79b
	.4byte	.LLST2
	.byte	0
	.uleb128 0x14
	.4byte	.LBB3
	.4byte	.LBE3-.LBB3
	.uleb128 0xf
	.4byte	.LASF188
	.byte	0x6a
	.4byte	0x79b
	.4byte	.LLST3
	.byte	0
	.byte	0
	.uleb128 0x3f
	.4byte	.LASF194
	.byte	0x1
	.byte	0x54
	.byte	0x6
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x15
	.4byte	.LASF195
	.byte	0x54
	.byte	0x43
	.4byte	0x8b7
	.4byte	.LLST0
	.uleb128 0x24
	.4byte	.LVL2
	.4byte	0xac4
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x2010000
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
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
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xf
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
	.sleb128 26
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0xd
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
	.sleb128 5
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
	.uleb128 0x3f
	.uleb128 0x19
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
	.uleb128 0x1a
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0x1c
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
	.uleb128 0x1d
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3e
	.uleb128 0x21
	.sleb128 5
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 11
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
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 13
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
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x26
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0x28
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 26
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2f
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
	.uleb128 0x30
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
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
	.uleb128 0x33
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
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
	.uleb128 0x35
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
	.uleb128 0x36
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
	.uleb128 0x37
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
	.uleb128 0x38
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
	.uleb128 0x39
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x3a
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
	.uleb128 0x3d
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
	.uleb128 0x3e
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
	.uleb128 0x3f
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
.LLST24:
	.byte	0x6
	.4byte	.LVL62
	.byte	0x4
	.uleb128 .LVL62-.LVL62
	.uleb128 .LVL63-1-.LVL62
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL63-1-.LVL62
	.uleb128 .LVL69-.LVL62
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL69-.LVL62
	.uleb128 .LVL71-.LVL62
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
	.uleb128 .LVL71-.LVL62
	.uleb128 .LFE26-.LVL62
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST25:
	.byte	0x6
	.4byte	.LVL62
	.byte	0x4
	.uleb128 .LVL62-.LVL62
	.uleb128 .LVL63-1-.LVL62
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL63-1-.LVL62
	.uleb128 .LVL66-.LVL62
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL66-.LVL62
	.uleb128 .LVL68-1-.LVL62
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL71-.LVL62
	.uleb128 .LVL72-1-.LVL62
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL73-.LVL62
	.uleb128 .LVL74-1-.LVL62
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL75-.LVL62
	.uleb128 .LVL76-1-.LVL62
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL77-.LVL62
	.uleb128 .LVL78-1-.LVL62
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST26:
	.byte	0x6
	.4byte	.LVL62
	.byte	0x4
	.uleb128 .LVL62-.LVL62
	.uleb128 .LVL63-1-.LVL62
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL63-1-.LVL62
	.uleb128 .LFE26-.LVL62
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
.LLST27:
	.byte	0x6
	.4byte	.LVL62
	.byte	0x4
	.uleb128 .LVL62-.LVL62
	.uleb128 .LVL63-1-.LVL62
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL63-1-.LVL62
	.uleb128 .LVL70-.LVL62
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL70-.LVL62
	.uleb128 .LVL71-.LVL62
	.uleb128 0x2
	.byte	0x72
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL71-.LVL62
	.uleb128 .LFE26-.LVL62
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST28:
	.byte	0x6
	.4byte	.LVL64
	.byte	0x4
	.uleb128 .LVL64-.LVL64
	.uleb128 .LVL67-.LVL64
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL67-.LVL64
	.uleb128 .LVL68-1-.LVL64
	.uleb128 0x5
	.byte	0x3
	.4byte	last_report_id
	.byte	0x4
	.uleb128 .LVL71-.LVL64
	.uleb128 .LVL72-1-.LVL64
	.uleb128 0x5
	.byte	0x3
	.4byte	last_report_id
	.byte	0x4
	.uleb128 .LVL73-.LVL64
	.uleb128 .LVL74-1-.LVL64
	.uleb128 0x5
	.byte	0x3
	.4byte	last_report_id
	.byte	0x4
	.uleb128 .LVL75-.LVL64
	.uleb128 .LVL76-1-.LVL64
	.uleb128 0x5
	.byte	0x3
	.4byte	last_report_id
	.byte	0x4
	.uleb128 .LVL77-.LVL64
	.uleb128 .LVL78-1-.LVL64
	.uleb128 0x5
	.byte	0x3
	.4byte	last_report_id
	.byte	0
.LLST22:
	.byte	0x6
	.4byte	.LVL57
	.byte	0x4
	.uleb128 .LVL57-.LVL57
	.uleb128 .LVL59-.LVL57
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL59-.LVL57
	.uleb128 .LVL60-1-.LVL57
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST23:
	.byte	0x8
	.4byte	.LVL58
	.uleb128 .LVL60-1-.LVL58
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL51-1-.LVL50
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL51-1-.LVL50
	.uleb128 .LVL56-.LVL50
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL56-.LVL50
	.uleb128 .LFE22-.LVL50
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
.LLST20:
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL51-1-.LVL50
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL51-1-.LVL50
	.uleb128 .LVL55-.LVL50
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST21:
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL51-1-.LVL50
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL51-1-.LVL50
	.uleb128 .LFE22-.LVL50
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
.LLST15:
	.byte	0x6
	.4byte	.LVL43
	.byte	0x4
	.uleb128 .LVL43-.LVL43
	.uleb128 .LVL44-.LVL43
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL44-.LVL43
	.uleb128 .LFE20-.LVL43
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
.LLST16:
	.byte	0x6
	.4byte	.LVL43
	.byte	0x4
	.uleb128 .LVL43-.LVL43
	.uleb128 .LVL45-.LVL43
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL45-.LVL43
	.uleb128 .LVL46-.LVL43
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL46-.LVL43
	.uleb128 .LFE20-.LVL43
	.uleb128 0xc
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST18:
	.byte	0x6
	.4byte	.LVL47
	.byte	0x4
	.uleb128 .LVL47-.LVL47
	.uleb128 .LVL48-.LVL47
	.uleb128 0x2d
	.byte	0x7e
	.sleb128 0
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL48-.LVL47
	.uleb128 .LVL49-.LVL47
	.uleb128 0x41
	.byte	0x3
	.4byte	usb_vCtrl_y
	.byte	0x6
	.byte	0x7b
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x3
	.4byte	usb_vCtrl_y
	.byte	0x6
	.byte	0x7b
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL35
	.byte	0x4
	.uleb128 .LVL35-.LVL35
	.uleb128 .LVL36-.LVL35
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL36-.LVL35
	.uleb128 .LFE19-.LVL35
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
	.4byte	.LVL35
	.byte	0x4
	.uleb128 .LVL35-.LVL35
	.uleb128 .LVL37-.LVL35
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL37-.LVL35
	.uleb128 .LVL38-.LVL35
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL38-.LVL35
	.uleb128 .LFE19-.LVL35
	.uleb128 0xc
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL39
	.byte	0x4
	.uleb128 .LVL39-.LVL39
	.uleb128 .LVL40-.LVL39
	.uleb128 0x2d
	.byte	0x7e
	.sleb128 0
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL40-.LVL39
	.uleb128 .LVL41-.LVL39
	.uleb128 0x41
	.byte	0x3
	.4byte	usb_vCtrl_y
	.byte	0x6
	.byte	0x7b
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x3
	.4byte	usb_vCtrl_y
	.byte	0x6
	.byte	0x7b
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL41-.LVL39
	.uleb128 .LVL42-.LVL39
	.uleb128 0x57
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	usb_vCtrl_y
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	usb_vCtrl_y
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST8:
	.byte	0x6
	.4byte	.LVL23
	.byte	0x4
	.uleb128 .LVL23-.LVL23
	.uleb128 .LVL24-.LVL23
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL24-.LVL23
	.uleb128 .LVL25-.LVL23
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL25-.LVL23
	.uleb128 .LVL27-.LVL23
	.uleb128 0x5
	.byte	0x7b
	.sleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL27-.LVL23
	.uleb128 .LFE18-.LVL23
	.uleb128 0xc
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL28-.LVL26
	.uleb128 0x1d
	.byte	0x7c
	.sleb128 0
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x7a
	.sleb128 4
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x7c
	.sleb128 0
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x32
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL28-.LVL26
	.uleb128 .LVL29-.LVL26
	.uleb128 0x1b
	.byte	0x7f
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x7a
	.sleb128 4
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x7c
	.sleb128 0
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x32
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL29-.LVL26
	.uleb128 .LVL30-.LVL26
	.uleb128 0x25
	.byte	0x7f
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x7a
	.sleb128 4
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x32
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL30-.LVL26
	.uleb128 .LVL31-.LVL26
	.uleb128 0x31
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x7a
	.sleb128 4
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x32
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL31-.LVL26
	.uleb128 .LVL32-.LVL26
	.uleb128 0x2e
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x76
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x32
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL32-.LVL26
	.uleb128 .LVL33-.LVL26
	.uleb128 0x31
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x7a
	.sleb128 4
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x3
	.4byte	usb_vCtrl_x
	.byte	0x6
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x32
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST10:
	.byte	0x8
	.4byte	.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x2d
	.byte	0x7a
	.sleb128 16
	.byte	0x6
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	usb_vCtrl_y
	.byte	0x6
	.byte	0x22
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x7a
	.sleb128 20
	.byte	0x6
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL20-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL20-.LVL11
	.uleb128 .LFE17-.LVL11
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
.LLST5:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL11-.LVL11
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL14-.LVL11
	.uleb128 0x5
	.byte	0x7b
	.sleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL14-.LVL11
	.uleb128 .LFE17-.LVL11
	.uleb128 0xc
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x1e
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7e
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x39
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL13-.LVL12
	.uleb128 .LVL15-.LVL12
	.uleb128 0x1c
	.byte	0x7f
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7e
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x39
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL15-.LVL12
	.uleb128 .LVL16-.LVL12
	.uleb128 0x1e
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7e
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x39
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL16-.LVL12
	.uleb128 .LVL17-.LVL12
	.uleb128 0x1e
	.byte	0x7e
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7a
	.sleb128 28
	.byte	0x6
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7a
	.sleb128 28
	.byte	0x6
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x39
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL17-.LVL12
	.uleb128 .LVL18-.LVL12
	.uleb128 0x21
	.byte	0x7a
	.sleb128 28
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7a
	.sleb128 28
	.byte	0x6
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7a
	.sleb128 28
	.byte	0x6
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x39
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL19
	.byte	0x4
	.uleb128 .LVL19-.LVL19
	.uleb128 .LVL20-.LVL19
	.uleb128 0x1b
	.byte	0x7f
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7f
	.sleb128 0
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7a
	.sleb128 28
	.byte	0x6
	.byte	0x48
	.byte	0x25
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL20-.LVL19
	.uleb128 .LVL21-.LVL19
	.uleb128 0x24
	.byte	0x7f
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7f
	.sleb128 0
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x23
	.uleb128 0x1c
	.byte	0x6
	.byte	0x48
	.byte	0x25
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL21-.LVL19
	.uleb128 .LVL22-.LVL19
	.uleb128 0x38
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x23
	.uleb128 0x20
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x23
	.uleb128 0x20
	.byte	0x6
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x23
	.uleb128 0x1c
	.byte	0x6
	.byte	0x48
	.byte	0x25
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL3-.LVL3
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LFE16-.LVL3
	.uleb128 0x5
	.byte	0x7b
	.sleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x1e
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7e
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.LVL4
	.uleb128 .LVL6-.LVL4
	.uleb128 0x1c
	.byte	0x7f
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7e
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL6-.LVL4
	.uleb128 .LVL7-.LVL4
	.uleb128 0x1e
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7e
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL7-.LVL4
	.uleb128 .LVL8-.LVL4
	.uleb128 0x1e
	.byte	0x7e
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7a
	.sleb128 36
	.byte	0x6
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7a
	.sleb128 36
	.byte	0x6
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL8-.LVL4
	.uleb128 .LVL9-.LVL4
	.uleb128 0x21
	.byte	0x7a
	.sleb128 36
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7a
	.sleb128 36
	.byte	0x6
	.byte	0x38
	.byte	0x25
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x7a
	.sleb128 36
	.byte	0x6
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3a
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST3:
	.byte	0x8
	.4byte	.LVL9
	.uleb128 .LVL10-.LVL9
	.uleb128 0x6
	.byte	0x7a
	.sleb128 36
	.byte	0x6
	.byte	0x48
	.byte	0x25
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
	.uleb128 .LFE15-.LVL0
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
	.4byte	0x7c
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
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
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
	.4byte	.LBB8
	.byte	0x4
	.uleb128 .LBB8-.LBB8
	.uleb128 .LBE8-.LBB8
	.byte	0x4
	.uleb128 .LBB9-.LBB8
	.uleb128 .LBE9-.LBB8
	.byte	0
.LLRL17:
	.byte	0x5
	.4byte	.LBB11
	.byte	0x4
	.uleb128 .LBB11-.LBB11
	.uleb128 .LBE11-.LBB11
	.byte	0x4
	.uleb128 .LBB12-.LBB11
	.uleb128 .LBE12-.LBB11
	.byte	0
.LLRL29:
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF159:
	.string	"HAL_CCNI_EVENT29"
.LASF171:
	.string	"riscv_hid_report_id_select"
.LASF87:
	.string	"key_remap_enable"
.LASF66:
	.string	"T_HID_CCNI_USB_REPORT_S"
.LASF163:
	.string	"tx_n"
.LASF82:
	.string	"combo_key_list"
.LASF120:
	.string	"hal_ccni_status_t"
.LASF29:
	.string	"T_COMMON_LA_DBG_S"
.LASF116:
	.string	"HAL_CCNI_STATUS_BUSY"
.LASF179:
	.string	"report_go"
.LASF61:
	.string	"ms_s16_z8"
.LASF196:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF189:
	.string	"hid_express_usb_mode_generate_kb_consumer_xy_reports"
.LASF96:
	.string	"type"
.LASF115:
	.string	"HAL_CCNI_STATUS_INVALID_PARAMETER"
.LASF38:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF68:
	.string	"combo_bit_32_63"
.LASF160:
	.string	"HAL_CCNI_EVENT30"
.LASF161:
	.string	"HAL_CCNI_EVENT31"
.LASF71:
	.string	"step_2_4g"
.LASF91:
	.string	"mouse_key_num"
.LASF14:
	.string	"int16_t"
.LASF10:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF85:
	.string	"irpt_ctrl"
.LASF99:
	.string	"kb_consumer"
.LASF88:
	.string	"key_remap_fn_key"
.LASF2:
	.string	"long long unsigned int"
.LASF39:
	.string	"rr_idx_2_4g"
.LASF50:
	.string	"T_HID_REPORT_MS_K8_S16_Z8_S"
.LASF32:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF124:
	.string	"hal_ccni_message_t"
.LASF8:
	.string	"long int"
.LASF3:
	.string	"unsigned int"
.LASF103:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF98:
	.string	"kb_std"
.LASF17:
	.string	"uint16_t"
.LASF166:
	.string	"T_ASSEMBLE_VAL_CTRL_S"
.LASF101:
	.string	"u32_may_alias_t"
.LASF37:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF167:
	.string	"hid_common"
.LASF69:
	.string	"T_AIR_COMBO_KEY_S"
.LASF52:
	.string	"T_HID_REPORT_KB_STD2_XY_S"
.LASF185:
	.string	"reduce_us"
.LASF176:
	.string	"outgoing"
.LASF183:
	.string	"hid_express_usb_delay_for_latency"
.LASF56:
	.string	"dummy"
.LASF105:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF188:
	.string	"temp"
.LASF128:
	.string	"HAL_CCNI_CORE_END"
.LASF108:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF48:
	.string	"T_HID_KEY_REMAP_S"
.LASF31:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF106:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF195:
	.string	"outgoing_rep"
.LASF125:
	.string	"HAL_CCNI_CORE_START"
.LASF44:
	.string	"repeat_times"
.LASF22:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF100:
	.string	"T_OUTGOING_VALUES_S"
.LASF9:
	.string	"long unsigned int"
.LASF62:
	.string	"kb_std2"
.LASF42:
	.string	"keycode"
.LASF64:
	.string	"kb_std5"
.LASF95:
	.string	"hid_common_info"
.LASF83:
	.string	"combo_key_list_size"
.LASF89:
	.string	"riscv_trigger_time"
.LASF55:
	.string	"T_HID_REPORT_KB_CONSUMER1_XY_S"
.LASF123:
	.string	"data"
.LASF7:
	.string	"short unsigned int"
.LASF93:
	.string	"mapped_data"
.LASF192:
	.string	"hid_express_usb_mode_generate_kb_std_reports"
.LASF41:
	.string	"T_HID_REPORT_RATE_VAL_S"
.LASF110:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF177:
	.string	"tx_result"
.LASF168:
	.string	"ccni_evt_status"
.LASF111:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF126:
	.string	"HAL_CCNI_CORE_MCU"
.LASF169:
	.string	"usb_vCtrl_x"
.LASF170:
	.string	"usb_vCtrl_y"
.LASF78:
	.string	"outgoing_report_ready"
.LASF77:
	.string	"features"
.LASF80:
	.string	"hid_shared_parameters"
.LASF35:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF190:
	.string	"hid_express_usb_mode_generate_kb_std_xy_reports"
.LASF107:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF114:
	.string	"hal_gpt_status_t"
.LASF178:
	.string	"tx_idx"
.LASF119:
	.string	"HAL_CCNI_STATUS_OK"
.LASF15:
	.string	"int32_t"
.LASF26:
	.string	"DBG_PIN_USB_TX"
.LASF60:
	.string	"T_OUTPUT_CTRL_PIN_INFO_S"
.LASF51:
	.string	"combo"
.LASF121:
	.string	"hal_ccni_event_t"
.LASF187:
	.string	"hid_express_usb_x_y_data_prepare"
.LASF191:
	.string	"hid_express_usb_mode_generate_12bits_reports"
.LASF46:
	.string	"item"
.LASF73:
	.string	"T_DEBOUNCE_PARA_S"
.LASF72:
	.string	"step_bt"
.LASF102:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF74:
	.string	"hid_scenario_type"
.LASF172:
	.string	"hal_gpt_delay_us"
.LASF109:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF97:
	.string	"k_old"
.LASF49:
	.string	"report_id"
.LASF129:
	.string	"HAL_CCNI_CORE_RESERVED"
.LASF198:
	.string	"hid_express_usb_last_report_is_kb"
.LASF45:
	.string	"macro"
.LASF90:
	.string	"mouse_key_list"
.LASF112:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF193:
	.string	"hid_express_usb_mode_generate_kb_consumer_reports"
.LASF113:
	.string	"HAL_GPT_STATUS_OK"
.LASF174:
	.string	"hid_express_generate_value_candidate"
.LASF30:
	.string	"_Bool"
.LASF75:
	.string	"dongle_scenario"
.LASF5:
	.string	"unsigned char"
.LASF84:
	.string	"hold_timeout"
.LASF6:
	.string	"short int"
.LASF67:
	.string	"combo_bit_00_31"
.LASF182:
	.string	"hid_express_usb_wakeup_cm33_handler"
.LASF117:
	.string	"HAL_CCNI_STATUS_ERROR"
.LASF181:
	.string	"hid_express_usb_mode_init"
.LASF94:
	.string	"outgoing_report"
.LASF54:
	.string	"numeric_key_pad"
.LASF127:
	.string	"HAL_CCNI_CORE_RISCV"
.LASF162:
	.string	"HAL_CCNI_EVENT_MAX"
.LASF43:
	.string	"play_mode"
.LASF33:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF118:
	.string	"HAL_CCNI_STATUS_NO_INIT"
.LASF130:
	.string	"HAL_CCNI_EVENT0"
.LASF18:
	.string	"uint32_t"
.LASF132:
	.string	"HAL_CCNI_EVENT2"
.LASF133:
	.string	"HAL_CCNI_EVENT3"
.LASF134:
	.string	"HAL_CCNI_EVENT4"
.LASF135:
	.string	"HAL_CCNI_EVENT5"
.LASF136:
	.string	"HAL_CCNI_EVENT6"
.LASF137:
	.string	"HAL_CCNI_EVENT7"
.LASF138:
	.string	"HAL_CCNI_EVENT8"
.LASF139:
	.string	"HAL_CCNI_EVENT9"
.LASF11:
	.string	"long double"
.LASF63:
	.string	"kb_consumer1"
.LASF65:
	.string	"kb_consumer2"
.LASF12:
	.string	"char"
.LASF165:
	.string	"untransmitted_value"
.LASF184:
	.string	"delay_us"
.LASF81:
	.string	"inActivity_timeout"
.LASF180:
	.string	"last_report_id"
.LASF13:
	.string	"int8_t"
.LASF59:
	.string	"para"
.LASF175:
	.string	"hal_ccni_set_event"
.LASF21:
	.string	"DBG_PIN_NACK"
.LASF70:
	.string	"step_wired"
.LASF122:
	.string	"variable_len_msg"
.LASF40:
	.string	"rr_idx_usb"
.LASF186:
	.string	"hid_express_usb_data_send"
.LASF164:
	.string	"predict_n"
.LASF20:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF173:
	.string	"hid_express_x_y_buf_init"
.LASF34:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF140:
	.string	"HAL_CCNI_EVENT10"
.LASF141:
	.string	"HAL_CCNI_EVENT11"
.LASF142:
	.string	"HAL_CCNI_EVENT12"
.LASF143:
	.string	"HAL_CCNI_EVENT13"
.LASF144:
	.string	"HAL_CCNI_EVENT14"
.LASF145:
	.string	"HAL_CCNI_EVENT15"
.LASF146:
	.string	"HAL_CCNI_EVENT16"
.LASF147:
	.string	"HAL_CCNI_EVENT17"
.LASF148:
	.string	"HAL_CCNI_EVENT18"
.LASF149:
	.string	"HAL_CCNI_EVENT19"
.LASF47:
	.string	"status"
.LASF58:
	.string	"T_HID_REPORT_KB_CONSUMER2_S"
.LASF104:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF53:
	.string	"consumer"
.LASF16:
	.string	"uint8_t"
.LASF197:
	.string	"hid_express_usb_data_set_report_ready"
.LASF57:
	.string	"T_HID_REPORT_KB_STD5_S"
.LASF23:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF76:
	.string	"flags"
.LASF86:
	.string	"scroll_ctrl"
.LASF79:
	.string	"delay_for_key_polling_ms"
.LASF27:
	.string	"DBG_PIN_MAX"
.LASF19:
	.string	"DBG_PIN_SPI_CB"
.LASF92:
	.string	"app_shared_parameters"
.LASF25:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF36:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF131:
	.string	"HAL_CCNI_EVENT1"
.LASF24:
	.string	"DBG_PIN_USB_SOF"
.LASF28:
	.string	"enable_mask"
.LASF194:
	.string	"hid_express_usb_mode_send_report_to_CM33"
.LASF150:
	.string	"HAL_CCNI_EVENT20"
.LASF151:
	.string	"HAL_CCNI_EVENT21"
.LASF152:
	.string	"HAL_CCNI_EVENT22"
.LASF153:
	.string	"HAL_CCNI_EVENT23"
.LASF154:
	.string	"HAL_CCNI_EVENT24"
.LASF155:
	.string	"HAL_CCNI_EVENT25"
.LASF156:
	.string	"HAL_CCNI_EVENT26"
.LASF157:
	.string	"HAL_CCNI_EVENT27"
.LASF158:
	.string	"HAL_CCNI_EVENT28"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_usb_mode.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
