	.file	"riscv_hid_express_2_4G_mode.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_2_4G_mode.c"
	.section	.text.hid_express_gaming_get_tx_status,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_get_tx_status
	.hidden	hid_express_gaming_get_tx_status
	.type	hid_express_gaming_get_tx_status, @function
hid_express_gaming_get_tx_status:
.LFB16:
	.file 1 "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_2_4G_mode.c"
	.loc 1 140 1
	.cfi_startproc
	.loc 1 141 5
	.loc 1 140 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 141 23
	call	pka_share_get_hid_tx_ptr
.LVL0:
	.loc 1 147 1
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 141 21 discriminator 1
	sw	a0,reliable_tx_ptr,a5
	.loc 1 143 5 is_stmt 1
	.loc 1 147 1 is_stmt 0
	seqz	a0,a0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE16:
	.size	hid_express_gaming_get_tx_status, .-hid_express_gaming_get_tx_status
	.section	.text.hid_express_gaming_axis_data_update,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_axis_data_update
	.hidden	hid_express_gaming_axis_data_update
	.type	hid_express_gaming_axis_data_update, @function
hid_express_gaming_axis_data_update:
.LFB17:
	.loc 1 153 1 is_stmt 1
	.cfi_startproc
.LVL1:
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 155 8 is_stmt 0
	li	a5,2047
	.loc 1 153 1
	mv	s0,a0
	.loc 1 154 5 is_stmt 1
.LVL2:
	.loc 1 155 5
	.loc 1 153 1 is_stmt 0
	mv	a0,a2
.LVL3:
	.loc 1 155 8
	bgt	a1,a5,.L10
	.loc 1 160 10 is_stmt 1
	.loc 1 160 13 is_stmt 0
	li	a5,-2048
	blt	a1,a5,.L11
	.loc 1 166 5 is_stmt 1
	.loc 1 172 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	.loc 1 166 13
	sw	a1,0(s0)
	.loc 1 168 5 is_stmt 1
	.loc 1 172 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
.LVL4:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL5:
.L11:
	.cfi_restore_state
	.loc 1 161 9 is_stmt 1
	.loc 1 162 9
	.loc 1 163 9
	li	a2,4096
.LVL6:
	addi	a2,a2,-2048
	li	a1,1
.LVL7:
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL8:
	.loc 1 166 5
	.loc 1 168 5
	.loc 1 163 9 is_stmt 0
	li	a5,-2048
.LVL9:
.L6:
	.loc 1 166 13
	sw	a5,0(s0)
	.loc 1 170 9 is_stmt 1
	.loc 1 172 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL10:
	.loc 1 170 29
	li	a5,1
	sw	a5,last_xy_over_12bits,a4
	.loc 1 172 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL11:
.L10:
	.cfi_restore_state
	.loc 1 156 9 is_stmt 1
	.loc 1 157 9
	.loc 1 158 9
	li	a2,-2047
	li	a1,1
.LVL12:
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL13:
	.loc 1 166 5
	.loc 1 168 5
	.loc 1 158 9 is_stmt 0
	li	a5,2047
	j	.L6
	.cfi_endproc
.LFE17:
	.size	hid_express_gaming_axis_data_update, .-hid_express_gaming_axis_data_update
	.section	.text.hid_express_gaming_buffer_full_update_report,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_buffer_full_update_report
	.hidden	hid_express_gaming_buffer_full_update_report
	.type	hid_express_gaming_buffer_full_update_report, @function
hid_express_gaming_buffer_full_update_report:
.LFB18:
	.loc 1 176 1 is_stmt 1
	.cfi_startproc
	.loc 1 177 5
	.loc 1 176 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 177 71
	lla	s0,outgoing_report
	lbu	a4,8(s0)
	.loc 1 176 1
	sw	ra,8(sp)
	.loc 1 179 5
	li	a3,5
	.loc 1 177 13
	andi	a5,a4,63
.LVL14:
	.loc 1 179 5 is_stmt 1
	.cfi_offset 1, -4
	beq	a5,a3,.L23
	li	a3,11
	beq	a5,a3,.L14
	li	a4,1
	beq	a5,a4,.L23
	.loc 1 288 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.L14:
	.cfi_restore_state
	.loc 1 184 13 is_stmt 1
.LBB28:
	.loc 1 184 18
	.loc 1 184 147 is_stmt 0
	lw	a5,g_vCtrl_x
.LVL15:
	lw	a3,4(a5)
.LVL16:
	.loc 1 184 258 is_stmt 1
	.loc 1 184 60 is_stmt 0
	lbu	a0,1(s0)
.LBE28:
.LBB29:
	.loc 1 191 63
	lw	a5,g_vCtrl_y
	.loc 1 191 95
	lhu	a2,4(a5)
.LBE29:
.LBB30:
	.loc 1 184 179
	li	a1,16711680
	slli	a5,a3,16
	.loc 1 184 216
	srai	a3,a3,8
.LVL17:
	.loc 1 184 179
	and	a5,a5,a1
	.loc 1 184 250
	slli	a3,a3,24
.LBE30:
.LBB31:
	.loc 1 191 206
	lbu	a1,sn_num
.LBE31:
.LBB32:
	.loc 1 184 186
	or	a5,a5,a3
	.loc 1 184 60
	slli	a0,a0,8
.LBE32:
.LBB33:
	.loc 1 191 206
	slli	a3,a1,16
.LBE33:
.LBB34:
	.loc 1 184 186
	or	a5,a5,a0
.LVL18:
.LBE34:
.LBB35:
	.loc 1 191 213
	or	a3,a2,a3
.LBE35:
.LBB36:
	.loc 1 184 315
	sw	a5,0(s0)
.LBE36:
	.loc 1 184 16 is_stmt 1
	.loc 1 191 13
.LBB37:
	.loc 1 191 18
.LVL19:
	.loc 1 191 243
	.loc 1 191 294 is_stmt 0
	sw	a3,4(s0)
.LBE37:
	.loc 1 191 16 is_stmt 1
	.loc 1 197 13
	.loc 1 197 49 is_stmt 0
	ori	a4,a4,-128
.LVL20:
	.loc 1 288 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	.loc 1 197 49
	sb	a4,8(s0)
.LVL21:
	.loc 1 214 9 is_stmt 1
	.loc 1 288 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL22:
.L23:
	.cfi_restore_state
	sw	s1,0(sp)
	.cfi_offset 9, -12
	.loc 1 220 13 is_stmt 1
	.loc 1 220 16 is_stmt 0
	lla	s1,last_xy_over_12bits
	.loc 1 220 15
	lw	a5,0(s1)
.LVL23:
	beq	a5,zero,.L26
	lw	s1,0(sp)
	.cfi_restore 9
.LVL24:
.L31:
	.loc 1 288 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL25:
.L26:
	.cfi_def_cfa_offset 12
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
.LBB38:
.LBB39:
.LBB40:
	.loc 1 222 17 is_stmt 1
	.loc 1 223 17
	.loc 1 223 68 is_stmt 0
	lla	a5,g_vCtrl_x
	lw	a0,0(a5)
.LBB41:
.LBB42:
	.loc 1 155 8
	li	a3,2047
.LBE42:
.LBE41:
	.loc 1 223 17
	lw	a4,4(a0)
.LVL26:
.LBB46:
.LBB43:
	.loc 1 154 5 is_stmt 1
	.loc 1 155 5
	.loc 1 155 8 is_stmt 0
	bgt	a4,a3,.L27
	.loc 1 160 10 is_stmt 1
	.loc 1 160 13 is_stmt 0
	li	a3,-2048
	blt	a4,a3,.L28
.LVL27:
.L18:
.LBE43:
.LBE46:
	.loc 1 224 17 is_stmt 1
	.loc 1 224 68 is_stmt 0
	lla	a4,g_vCtrl_y
	lw	a0,0(a4)
.LBB47:
.LBB48:
	.loc 1 155 8
	li	a2,2047
.LBE48:
.LBE47:
	.loc 1 224 17
	lw	a3,4(a0)
.LVL28:
.LBB53:
.LBB49:
	.loc 1 154 5 is_stmt 1
	.loc 1 155 5
	.loc 1 155 8 is_stmt 0
	bgt	a3,a2,.L29
	.loc 1 160 10 is_stmt 1
	.loc 1 160 13 is_stmt 0
	li	a2,-2048
	blt	a3,a2,.L30
.LVL29:
.L21:
.LBE49:
.LBE53:
	.loc 1 227 17 is_stmt 1
.LBB54:
	.loc 1 227 22
	.loc 1 227 264
.LBE54:
.LBB55:
	.loc 1 234 72 is_stmt 0
	lw	a5,0(a5)
.LBE55:
.LBB56:
	.loc 1 227 119
	lbu	a4,1(s0)
.LVL30:
	.loc 1 227 180
	lbu	t0,2(s0)
.LVL31:
.LBE56:
.LBB57:
	.loc 1 234 72
	lw	a2,4(a5)
	.loc 1 234 199
	slli	t1,a3,4
.LBE57:
.LBB58:
	.loc 1 227 242
	lbu	a0,3(s0)
.LBE58:
.LBB59:
	.loc 1 234 137
	srai	a5,a2,8
	.loc 1 234 199
	andi	t1,t1,255
	.loc 1 234 143
	andi	a5,a5,15
.LBE59:
.LBB60:
	.loc 1 227 194
	slli	t0,t0,16
.LVL32:
.LBE60:
.LBB61:
	.loc 1 234 157
	or	a5,a5,t1
.LBE61:
.LBB62:
	.loc 1 227 133
	slli	a4,a4,8
.LVL33:
.LBE62:
.LBB63:
	.loc 1 234 290
	slli	a3,a3,12
	li	t1,16711680
.LBE63:
	.loc 1 240 51
	lbu	a1,8(s0)
.LBB64:
	.loc 1 227 139
	or	a4,a4,t0
.LBE64:
.LBB65:
	.loc 1 234 290
	and	a3,a3,t1
.LBE65:
.LBB66:
	.loc 1 227 69
	lbu	t0,sn_num
.LBE66:
.LBB67:
	.loc 1 234 92
	andi	a2,a2,255
	.loc 1 234 297
	or	a3,a3,a2
.LBE67:
.LBB68:
	.loc 1 227 139
	or	a4,a4,t0
	.loc 1 227 256
	slli	a0,a0,24
.LBE68:
.LBB69:
	.loc 1 234 220
	slli	a5,a5,8
	.loc 1 234 297
	or	a5,a5,a3
.LBE69:
.LBB70:
	.loc 1 227 201
	or	a4,a4,a0
.LBE70:
	.loc 1 240 51
	ori	a3,a1,-128
.LBB71:
	.loc 1 227 319
	sw	a4,0(s0)
.LVL34:
.LBE71:
	.loc 1 227 20 is_stmt 1
	.loc 1 234 17
.LBB72:
	.loc 1 234 22
	.loc 1 234 330
	.loc 1 234 384 is_stmt 0
	sw	a5,4(s0)
.LBE72:
	.loc 1 234 20 is_stmt 1
	.loc 1 240 17
	lw	s1,0(sp)
	.cfi_remember_state
	.cfi_restore 9
	.loc 1 240 51 is_stmt 0
	sb	a3,8(s0)
.LVL35:
	j	.L31
.LVL36:
.L30:
	.cfi_restore_state
.LBB73:
.LBB50:
	.loc 1 161 9 is_stmt 1
	.loc 1 162 9
	.loc 1 163 9
	li	a2,4096
	addi	a2,a2,-2048
	li	a1,1
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL37:
	lla	a4,g_vCtrl_y
	lla	a5,g_vCtrl_x
	.loc 1 166 5
.LVL38:
	.loc 1 168 5
.L20:
	.loc 1 170 9
.LBE50:
.LBE73:
.LBB74:
	.loc 1 234 181 is_stmt 0
	lw	a4,0(a4)
.LBE74:
.LBB75:
.LBB51:
	.loc 1 170 29
	li	a3,1
	sw	a3,0(s1)
.LBE51:
.LBE75:
.LBB76:
	.loc 1 234 181
	lw	a3,4(a4)
	j	.L21
.LVL39:
.L28:
.LBE76:
.LBB77:
.LBB44:
	.loc 1 161 9 is_stmt 1
	.loc 1 162 9
	.loc 1 163 9
	li	a2,4096
	addi	a2,a2,-2048
.LVL40:
.L25:
	li	a1,1
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL41:
	.loc 1 170 29 is_stmt 0
	li	a4,1
	.loc 1 163 9
	lla	a5,g_vCtrl_x
.LVL42:
	.loc 1 166 5 is_stmt 1
	.loc 1 168 5
	.loc 1 170 9
	.loc 1 170 29 is_stmt 0
	sw	a4,0(s1)
	j	.L18
.LVL43:
.L29:
.LBE44:
.LBE77:
.LBB78:
.LBB52:
	.loc 1 156 9 is_stmt 1
	.loc 1 157 9
	.loc 1 158 9
	li	a2,-2047
	li	a1,1
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL44:
	.loc 1 166 5
	.loc 1 168 5
	lla	a5,g_vCtrl_x
	lla	a4,g_vCtrl_y
	j	.L20
.LVL45:
.L27:
.LBE52:
.LBE78:
.LBB79:
.LBB45:
	.loc 1 156 9
	.loc 1 157 9
	.loc 1 158 9
	li	a2,-2047
	j	.L25
.LBE45:
.LBE79:
.LBE40:
.LBE39:
.LBE38:
	.cfi_endproc
.LFE18:
	.size	hid_express_gaming_buffer_full_update_report, .-hid_express_gaming_buffer_full_update_report
	.section	.text.hid_express_gaming_generate_reports_1R1T_12bits,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_generate_reports_1R1T_12bits
	.hidden	hid_express_gaming_generate_reports_1R1T_12bits
	.type	hid_express_gaming_generate_reports_1R1T_12bits, @function
hid_express_gaming_generate_reports_1R1T_12bits:
.LFB19:
	.loc 1 291 1
	.cfi_startproc
.LVL46:
	.loc 1 292 5
	.loc 1 292 7 is_stmt 0
	lw	a5,reliable_tx_ptr
	beq	a5,zero,.L33
	.loc 1 294 9 is_stmt 1
.LBB80:
	.loc 1 298 85 is_stmt 0
	lw	a5,16(a0)
	.loc 1 298 166
	lw	a4,g_vCtrl_x
	.loc 1 298 91
	lw	t1,4(a0)
	.loc 1 298 166
	lw	a4,4(a4)
.LBE80:
	.loc 1 294 15
	lla	a2,sn_num
	lw	a1,0(a2)
.LBB81:
	.loc 1 305 59
	lw	a3,g_vCtrl_y
.LBE81:
.LBB82:
	.loc 1 298 85
	slli	a5,a5,5
.LBE82:
.LBB83:
	.loc 1 305 91
	lw	a3,4(a3)
.LBE83:
.LBB84:
	.loc 1 298 198
	li	a0,16711680
.LVL47:
	.loc 1 298 91
	or	a5,a5,t1
	.loc 1 298 56
	li	t0,65536
	.loc 1 298 198
	slli	t1,a4,16
	.loc 1 298 235
	srai	a4,a4,8
.LBE84:
	.loc 1 294 15
	addi	a1,a1,1
.LBB85:
	.loc 1 298 56
	addi	t0,t0,-1
	.loc 1 298 269
	slli	a4,a4,24
	.loc 1 298 135
	slli	a5,a5,8
	.loc 1 298 198
	and	t1,t1,a0
	.loc 1 298 30
	or	t1,t1,a4
.LBE85:
.LBB86:
	.loc 1 305 202
	slli	t2,a1,16
.LBE86:
.LBB87:
	.loc 1 298 56
	and	a5,a5,t0
.LBE87:
.LBB88:
	.loc 1 305 91
	and	a4,a3,t0
.LBE88:
.LBB89:
	.loc 1 298 30
	or	a5,a5,t1
	.loc 1 298 334
	lla	a3,outgoing_report
.LBE89:
.LBB90:
	.loc 1 305 202
	and	t2,t2,a0
	.loc 1 305 209
	or	a4,a4,t2
.LBE90:
.LBB91:
	.loc 1 298 334
	sw	a5,0(a3)
.LBE91:
	.loc 1 311 45
	li	a5,11
	.loc 1 294 15
	sw	a1,0(a2)
	.loc 1 298 9 is_stmt 1
.LBB92:
	.loc 1 298 14
.LVL48:
	.loc 1 298 277
.LBE92:
	.loc 1 298 12
	.loc 1 305 9
.LBB93:
	.loc 1 305 14
	.loc 1 305 242
	.loc 1 305 293 is_stmt 0
	sw	a4,4(a3)
.LBE93:
	.loc 1 305 12 is_stmt 1
	.loc 1 311 9
	.loc 1 311 45 is_stmt 0
	sb	a5,8(a3)
	.loc 1 333 1
	ret
.LVL49:
.L33:
	.loc 1 331 9 is_stmt 1
	tail	hid_express_gaming_buffer_full_update_report
.LVL50:
	.cfi_endproc
.LFE19:
	.size	hid_express_gaming_generate_reports_1R1T_12bits, .-hid_express_gaming_generate_reports_1R1T_12bits
	.section	.text.hid_express_gaming_generate_kb_std_xy_reports_1R1T,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_generate_kb_std_xy_reports_1R1T
	.hidden	hid_express_gaming_generate_kb_std_xy_reports_1R1T
	.type	hid_express_gaming_generate_kb_std_xy_reports_1R1T, @function
hid_express_gaming_generate_kb_std_xy_reports_1R1T:
.LFB20:
	.loc 1 370 1
	.cfi_startproc
.LVL51:
	.loc 1 371 5
	.loc 1 371 7 is_stmt 0
	lw	a4,reliable_tx_ptr
	beq	a4,zero,.L37
.LBB101:
	.loc 1 373 9 is_stmt 1
	.loc 1 373 15 is_stmt 0
	lla	t1,sn_num
	lw	a4,0(t1)
.LBE101:
	.loc 1 370 1
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	mv	a5,a0
.LBB134:
	.loc 1 376 60
	lw	a0,g_vCtrl_x
.LVL52:
	.loc 1 373 15
	addi	a4,a4,1
.LBE134:
	.loc 1 370 1
	sw	s1,4(sp)
	.cfi_offset 9, -12
.LBB135:
	.loc 1 376 9
	lw	s1,4(a0)
	.loc 1 373 15
	sw	a4,0(t1)
	.loc 1 374 9 is_stmt 1
	.loc 1 375 9
	.loc 1 375 29 is_stmt 0
	sw	zero,last_xy_over_12bits,a4
	.loc 1 376 9 is_stmt 1
.LVL53:
.LBB102:
.LBB103:
	.loc 1 154 5
	.loc 1 155 5
.LBE103:
.LBE102:
.LBE135:
	.loc 1 370 1 is_stmt 0
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
.LBB136:
.LBB107:
.LBB104:
	.loc 1 155 8
	li	a4,2047
	bgt	s1,a4,.L51
	.loc 1 160 10 is_stmt 1
	.loc 1 160 13 is_stmt 0
	li	a4,-2048
	blt	s1,a4,.L40
.LVL54:
.LBE104:
.LBE107:
	.loc 1 377 9 is_stmt 1
	.loc 1 377 60 is_stmt 0
	lw	a0,g_vCtrl_y
	.loc 1 377 9
	lw	a3,4(a0)
.LVL55:
.LBB108:
.LBB109:
	.loc 1 154 5 is_stmt 1
	.loc 1 155 5
.LBE109:
.LBE108:
.LBB115:
	.loc 1 388 83 is_stmt 0
	srai	s0,s1,8
.LBE115:
.LBB116:
.LBB110:
	.loc 1 155 8
	li	a4,2047
.LBE110:
.LBE116:
.LBB117:
	.loc 1 388 57
	andi	s1,s1,255
	.loc 1 388 89
	andi	s0,s0,15
.LBE117:
.LBB118:
.LBB111:
	.loc 1 155 8
	bgt	a3,a4,.L52
.LVL56:
.L42:
	.loc 1 160 10 is_stmt 1
	.loc 1 160 13 is_stmt 0
	li	a4,-2048
	blt	a3,a4,.L44
.LBE111:
.LBE118:
.LBB119:
	.loc 1 388 124
	slli	a4,a3,4
	andi	a4,a4,255
	.loc 1 388 195
	slli	a3,a3,12
.LVL57:
	.loc 1 388 103
	or	s0,s0,a4
	.loc 1 388 195
	li	a4,16711680
	and	a3,a3,a4
.LVL58:
.L45:
.LBE119:
	.loc 1 381 9 is_stmt 1
.LBB120:
	.loc 1 381 14
	.loc 1 381 96 is_stmt 0
	lw	a4,28(a5)
.LVL59:
	.loc 1 381 270 is_stmt 1
	.loc 1 381 128 is_stmt 0
	li	a0,65536
	.loc 1 381 61
	lbu	a1,0(t1)
	.loc 1 381 128
	slli	a5,a4,8
.LVL60:
	.loc 1 381 227
	srli	a2,a4,16
	.loc 1 381 128
	addi	a0,a0,-256
	.loc 1 381 262
	slli	a2,a2,24
	.loc 1 381 128
	and	a5,a5,a0
.LVL61:
	.loc 1 381 30
	or	a5,a5,a2
	.loc 1 381 194
	slli	a4,a4,8
.LVL62:
	li	a2,16711680
.LBE120:
.LBB121:
	.loc 1 388 202
	or	s1,s1,a3
.LBE121:
.LBB122:
	.loc 1 381 30
	or	a5,a5,a1
	.loc 1 381 194
	and	a4,a4,a2
.LBE122:
.LBB123:
	.loc 1 388 145
	slli	s0,s0,8
.LBE123:
.LBB124:
	.loc 1 381 325
	lla	a3,outgoing_report
.LBE124:
.LBB125:
	.loc 1 388 202
	or	s0,s0,s1
.LBE125:
.LBB126:
	.loc 1 381 30
	or	a5,a5,a4
	.loc 1 381 325
	sw	a5,0(a3)
.LBE126:
	.loc 1 381 12 is_stmt 1
	.loc 1 388 9
.LBB127:
	.loc 1 388 14
.LVL63:
	.loc 1 388 235
	.loc 1 388 289 is_stmt 0
	sw	s0,4(a3)
.LBE127:
	.loc 1 388 12 is_stmt 1
	.loc 1 394 9
.LBE136:
	.loc 1 416 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LBB137:
	.loc 1 394 43
	li	a5,1
	sb	a5,8(a3)
.LBE137:
	.loc 1 416 1
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL64:
.L51:
	.cfi_restore_state
.LBB138:
.LBB128:
.LBB105:
	.loc 1 158 9
	li	a2,-2047
	li	a1,1
	sw	a5,0(sp)
	.loc 1 156 9 is_stmt 1
.LVL65:
	.loc 1 157 9
	.loc 1 158 9
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL66:
	.loc 1 166 5
	.loc 1 168 5
	lw	a5,0(sp)
	.loc 1 158 9 is_stmt 0
	li	s0,7
	li	s1,255
.LVL67:
	lla	t1,sn_num
.LVL68:
.L39:
	.loc 1 170 9 is_stmt 1
	.loc 1 170 29 is_stmt 0
	li	a4,1
	sw	a4,last_xy_over_12bits,a3
.LVL69:
.LBE105:
.LBE128:
	.loc 1 377 9 is_stmt 1
	.loc 1 377 60 is_stmt 0
	lw	a0,g_vCtrl_y
	.loc 1 377 9
	lw	a3,4(a0)
.LVL70:
.LBB129:
.LBB112:
	.loc 1 154 5 is_stmt 1
	.loc 1 155 5
	.loc 1 155 8 is_stmt 0
	li	a4,2047
	ble	a3,a4,.L42
.LVL71:
.L52:
	.loc 1 158 9
	li	a2,-2047
	li	a1,1
	sw	a5,0(sp)
	.loc 1 156 9 is_stmt 1
.LVL72:
	.loc 1 157 9
	.loc 1 158 9
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL73:
	.loc 1 166 5
	.loc 1 168 5
	lw	a5,0(sp)
.LBE112:
.LBE129:
.LBB130:
	.loc 1 388 103 is_stmt 0
	ori	s0,s0,240
	li	a3,8323072
	lla	t1,sn_num
.LVL74:
.L43:
.LBE130:
.LBB131:
.LBB113:
	.loc 1 170 9 is_stmt 1
	.loc 1 170 29 is_stmt 0
	li	a4,1
	sw	a4,last_xy_over_12bits,a2
	j	.L45
.LVL75:
.L37:
	.cfi_def_cfa_offset 0
	.cfi_restore 1
	.cfi_restore 8
	.cfi_restore 9
.LBE113:
.LBE131:
.LBE138:
	.loc 1 414 9 is_stmt 1
	tail	hid_express_gaming_buffer_full_update_report
.LVL76:
.L40:
	.cfi_def_cfa_offset 16
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
.LBB139:
.LBB132:
.LBB106:
	.loc 1 163 9 is_stmt 0
	li	a2,4096
	addi	a2,a2,-2048
	li	a1,1
	sw	a5,0(sp)
	.loc 1 161 9 is_stmt 1
.LVL77:
	.loc 1 162 9
	.loc 1 163 9
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL78:
	.loc 1 166 5
	.loc 1 168 5
	.loc 1 163 9 is_stmt 0
	lw	a5,0(sp)
	li	s0,8
	li	s1,0
.LVL79:
	lla	t1,sn_num
	j	.L39
.LVL80:
.L44:
.LBE106:
.LBE132:
.LBB133:
.LBB114:
	li	a2,4096
	addi	a2,a2,-2048
	li	a1,1
	sw	a5,0(sp)
	.loc 1 161 9 is_stmt 1
.LVL81:
	.loc 1 162 9
	.loc 1 163 9
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL82:
	.loc 1 166 5
	.loc 1 168 5
	.loc 1 163 9 is_stmt 0
	lw	a5,0(sp)
	li	a3,8388608
	lla	t1,sn_num
	j	.L43
.LBE114:
.LBE133:
.LBE139:
	.cfi_endproc
.LFE20:
	.size	hid_express_gaming_generate_kb_std_xy_reports_1R1T, .-hid_express_gaming_generate_kb_std_xy_reports_1R1T
	.section	.text.hid_express_gaming_generate_kb_consumer_xy_reports_1R1T,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_generate_kb_consumer_xy_reports_1R1T
	.hidden	hid_express_gaming_generate_kb_consumer_xy_reports_1R1T
	.type	hid_express_gaming_generate_kb_consumer_xy_reports_1R1T, @function
hid_express_gaming_generate_kb_consumer_xy_reports_1R1T:
.LFB21:
	.loc 1 419 1 is_stmt 1
	.cfi_startproc
.LVL83:
	.loc 1 420 5
	.loc 1 420 7 is_stmt 0
	lw	a4,reliable_tx_ptr
	beq	a4,zero,.L54
.LBB147:
	.loc 1 422 9 is_stmt 1
	.loc 1 422 15 is_stmt 0
	lla	t1,sn_num
	lw	a4,0(t1)
.LBE147:
	.loc 1 419 1
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	mv	a5,a0
.LBB182:
	.loc 1 425 60
	lw	a0,g_vCtrl_x
.LVL84:
	.loc 1 422 15
	addi	a4,a4,1
.LBE182:
	.loc 1 419 1
	sw	s1,4(sp)
	.cfi_offset 9, -12
.LBB183:
	.loc 1 425 9
	lw	s1,4(a0)
	.loc 1 422 15
	sw	a4,0(t1)
	.loc 1 423 9 is_stmt 1
	.loc 1 424 9
	.loc 1 424 29 is_stmt 0
	sw	zero,last_xy_over_12bits,a4
	.loc 1 425 9 is_stmt 1
.LVL85:
.LBB148:
.LBB149:
	.loc 1 154 5
	.loc 1 155 5
.LBE149:
.LBE148:
.LBE183:
	.loc 1 419 1 is_stmt 0
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
.LBB184:
.LBB154:
.LBB150:
	.loc 1 155 8
	li	a4,2047
	bgt	s1,a4,.L68
	.loc 1 160 10 is_stmt 1
	.loc 1 160 13 is_stmt 0
	li	a4,-2048
	blt	s1,a4,.L57
.LVL86:
.LBE150:
.LBE154:
	.loc 1 426 9 is_stmt 1
	.loc 1 426 60 is_stmt 0
	lw	a0,g_vCtrl_y
	.loc 1 426 9
	lw	a4,4(a0)
.LVL87:
.LBB155:
.LBB156:
	.loc 1 154 5 is_stmt 1
	.loc 1 155 5
.LBE156:
.LBE155:
.LBB162:
	.loc 1 436 89 is_stmt 0
	srai	s0,s1,8
.LBE162:
.LBB163:
.LBB157:
	.loc 1 155 8
	li	a3,2047
.LBE157:
.LBE163:
.LBB164:
	.loc 1 436 64
	andi	s1,s1,255
	.loc 1 436 95
	andi	s0,s0,15
.LBE164:
.LBB165:
.LBB158:
	.loc 1 155 8
	bgt	a4,a3,.L69
.LVL88:
.L59:
	.loc 1 160 10 is_stmt 1
	.loc 1 160 13 is_stmt 0
	li	a3,-2048
	blt	a4,a3,.L61
.LBE158:
.LBE165:
.LBB166:
	.loc 1 436 131
	slli	a3,a4,4
	andi	a3,a3,255
	.loc 1 436 202
	slli	a4,a4,12
.LVL89:
	.loc 1 436 109
	or	s0,s0,a3
	.loc 1 436 202
	li	a3,16711680
	and	a3,a4,a3
.LVL90:
.L62:
.LBE166:
	.loc 1 429 9 is_stmt 1
.LBB167:
	.loc 1 429 14
	.loc 1 429 88 is_stmt 0
	lw	a4,36(a5)
.LVL91:
	.loc 1 429 238 is_stmt 1
	.loc 1 429 61 is_stmt 0
	lbu	a1,0(t1)
	.loc 1 429 130
	li	a2,65536
	slli	a5,a4,8
	addi	a2,a2,-256
	and	a5,a5,a2
	.loc 1 429 198
	slli	a4,a4,8
.LVL92:
	li	a2,16711680
.LBE167:
.LBB168:
	.loc 1 436 209
	or	s1,s1,a3
.LBE168:
.LBB169:
	.loc 1 429 75
	or	a5,a5,a1
	.loc 1 429 198
	and	a4,a4,a2
.LBE169:
.LBB170:
	.loc 1 436 152
	slli	s0,s0,8
.LBE170:
.LBB171:
	.loc 1 429 298
	lla	a3,outgoing_report
.LBE171:
.LBB172:
	.loc 1 436 209
	or	s0,s0,s1
.LBE172:
.LBB173:
	.loc 1 429 30
	or	a5,a5,a4
	.loc 1 429 298
	sw	a5,0(a3)
.LBE173:
	.loc 1 429 12 is_stmt 1
	.loc 1 436 9
.LBB174:
	.loc 1 436 14
.LVL93:
	.loc 1 436 242
	.loc 1 436 301 is_stmt 0
	sw	s0,4(a3)
.LBE174:
	.loc 1 436 12 is_stmt 1
	.loc 1 442 9
.LBE184:
	.loc 1 464 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LBB185:
	.loc 1 442 48
	li	a5,5
	sb	a5,8(a3)
.LBE185:
	.loc 1 464 1
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL94:
.L68:
	.cfi_restore_state
.LBB186:
.LBB175:
.LBB151:
	.loc 1 158 9
	li	a2,-2047
	li	a1,1
	sw	a5,0(sp)
	.loc 1 156 9 is_stmt 1
.LVL95:
	.loc 1 157 9
	.loc 1 158 9
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL96:
	.loc 1 166 5
	.loc 1 168 5
	lw	a5,0(sp)
	.loc 1 158 9 is_stmt 0
	li	s0,7
	li	s1,255
.LVL97:
	lla	t1,sn_num
.LVL98:
.L56:
	.loc 1 170 9 is_stmt 1
	.loc 1 170 29 is_stmt 0
	li	a4,1
.LBE151:
.LBE175:
	.loc 1 426 60
	lw	a0,g_vCtrl_y
.LBB176:
.LBB152:
	.loc 1 170 29
	sw	a4,last_xy_over_12bits,a3
.LVL99:
.LBE152:
.LBE176:
	.loc 1 426 9 is_stmt 1
	lw	a4,4(a0)
.LVL100:
.LBB177:
.LBB159:
	.loc 1 154 5
	.loc 1 155 5
	.loc 1 155 8 is_stmt 0
	li	a3,2047
	ble	a4,a3,.L59
.LVL101:
.L69:
	.loc 1 158 9
	li	a2,-2047
	li	a1,1
	sw	a5,0(sp)
	.loc 1 156 9 is_stmt 1
.LVL102:
	.loc 1 157 9
	.loc 1 158 9
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL103:
	.loc 1 166 5
	.loc 1 168 5
	lw	a5,0(sp)
.LBE159:
.LBE177:
.LBB178:
	.loc 1 436 109 is_stmt 0
	ori	s0,s0,240
	li	a3,8323072
	lla	t1,sn_num
.LVL104:
.L60:
.LBE178:
.LBB179:
.LBB160:
	.loc 1 170 9 is_stmt 1
	.loc 1 170 29 is_stmt 0
	li	a4,1
	sw	a4,last_xy_over_12bits,a2
	j	.L62
.LVL105:
.L54:
	.cfi_def_cfa_offset 0
	.cfi_restore 1
	.cfi_restore 8
	.cfi_restore 9
.LBE160:
.LBE179:
.LBE186:
	.loc 1 462 9 is_stmt 1
	tail	hid_express_gaming_buffer_full_update_report
.LVL106:
.L57:
	.cfi_def_cfa_offset 16
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
.LBB187:
.LBB180:
.LBB153:
	.loc 1 163 9 is_stmt 0
	li	a2,4096
	addi	a2,a2,-2048
	li	a1,1
	sw	a5,0(sp)
	.loc 1 161 9 is_stmt 1
.LVL107:
	.loc 1 162 9
	.loc 1 163 9
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL108:
	.loc 1 166 5
	.loc 1 168 5
	.loc 1 163 9 is_stmt 0
	lw	a5,0(sp)
	li	s0,8
	li	s1,0
.LVL109:
	lla	t1,sn_num
	j	.L56
.LVL110:
.L61:
.LBE153:
.LBE180:
.LBB181:
.LBB161:
	li	a2,4096
	addi	a2,a2,-2048
	li	a1,1
	sw	a5,0(sp)
	.loc 1 161 9 is_stmt 1
.LVL111:
	.loc 1 162 9
	.loc 1 163 9
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL112:
	.loc 1 166 5
	.loc 1 168 5
	.loc 1 163 9 is_stmt 0
	lw	a5,0(sp)
	li	a3,8388608
	lla	t1,sn_num
	j	.L60
.LBE161:
.LBE181:
.LBE187:
	.cfi_endproc
.LFE21:
	.size	hid_express_gaming_generate_kb_consumer_xy_reports_1R1T, .-hid_express_gaming_generate_kb_consumer_xy_reports_1R1T
	.section	.text.hid_express_2_4G_x_y_data_prepare,"ax",@progbits
	.align	1
	.globl	hid_express_2_4G_x_y_data_prepare
	.hidden	hid_express_2_4G_x_y_data_prepare
	.type	hid_express_2_4G_x_y_data_prepare, @function
hid_express_2_4G_x_y_data_prepare:
.LFB22:
	.loc 1 468 1 is_stmt 1
	.cfi_startproc
.LVL113:
	.loc 1 470 5
	.loc 1 468 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 470 30
	lw	a5,last_report_id
	.loc 1 468 1
	sw	s0,8(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 470 30
	addi	a5,a5,-9
	.loc 1 470 7
	li	a4,1
	.loc 1 468 1
	mv	s0,a0
	.loc 1 470 7
	bleu	a5,a4,.L73
	.loc 1 470 56 discriminator 1
	lw	a5,last_xy_over_12bits
	bne	a5,zero,.L73
.LVL114:
.L71:
	.loc 1 475 5 is_stmt 1
	lw	a2,8(s0)
.LVL115:
	lw	a0,g_vCtrl_x
.LVL116:
	sw	a1,0(sp)
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL117:
	.loc 1 476 5
	lw	a2,12(s0)
	lw	a1,0(sp)
	lw	a0,g_vCtrl_y
	call	hid_express_generate_value_candidate_1R1T_concurrent
.LVL118:
	.loc 1 478 5
	.loc 1 479 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL119:
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
.LVL120:
	jr	ra
.LVL121:
.L73:
	.cfi_restore_state
	.loc 1 472 19
	li	a1,1
.LVL122:
	j	.L71
	.cfi_endproc
.LFE22:
	.size	hid_express_2_4G_x_y_data_prepare, .-hid_express_2_4G_x_y_data_prepare
	.section	.text.hid_express_gaming_submit_report_to_pka,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_submit_report_to_pka
	.hidden	hid_express_gaming_submit_report_to_pka
	.type	hid_express_gaming_submit_report_to_pka, @function
hid_express_gaming_submit_report_to_pka:
.LFB23:
	.loc 1 483 1 is_stmt 1
	.cfi_startproc
	.loc 1 542 5
	.loc 1 544 53 is_stmt 0
	lla	a4,outgoing_report
	.loc 1 542 24
	lw	a5,reliable_tx_ptr
	.loc 1 544 53
	lw	a1,0(a4)
	lw	a2,4(a4)
	.loc 1 547 50
	lbu	a3,8(a4)
	.loc 1 542 7
	beq	a5,zero,.L76
.LBB190:
.LBB191:
	.loc 1 558 9 is_stmt 1
	.loc 1 561 87 is_stmt 0 discriminator 1
	li	a4,9
	.loc 1 557 60
	sw	a1,20(a5)
	sw	a2,24(a5)
	.loc 1 560 9 is_stmt 1
	.loc 1 560 59 is_stmt 0
	sb	a3,28(a5)
	.loc 1 561 9 is_stmt 1
	.loc 1 561 87 is_stmt 0 discriminator 1
	sh	a4,2(a5)
	.loc 1 562 9 is_stmt 1
	.loc 1 562 86 is_stmt 0 discriminator 1
	sh	a4,14(a5)
.LBE191:
.LBE190:
	.loc 1 569 1
	ret
.L76:
.LBB193:
.LBB192:
	.loc 1 557 9 is_stmt 1
	.loc 1 557 55 is_stmt 0
	lw	a5,reliable_tx_ptr_previous
	.loc 1 558 9 is_stmt 1
	.loc 1 561 87 is_stmt 0 discriminator 1
	li	a4,9
	.loc 1 557 60
	sw	a1,20(a5)
	sw	a2,24(a5)
	.loc 1 560 9 is_stmt 1
	.loc 1 560 59 is_stmt 0
	sb	a3,28(a5)
	.loc 1 561 9 is_stmt 1
	.loc 1 561 87 is_stmt 0 discriminator 1
	sh	a4,2(a5)
	.loc 1 562 9 is_stmt 1
	.loc 1 562 86 is_stmt 0 discriminator 1
	sh	a4,14(a5)
.LBE192:
.LBE193:
	.loc 1 569 1
	ret
	.cfi_endproc
.LFE23:
	.size	hid_express_gaming_submit_report_to_pka, .-hid_express_gaming_submit_report_to_pka
	.section	.text.hid_express_gaming_generate_kb_consumer_reports_1R1T,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_generate_kb_consumer_reports_1R1T
	.hidden	hid_express_gaming_generate_kb_consumer_reports_1R1T
	.type	hid_express_gaming_generate_kb_consumer_reports_1R1T, @function
hid_express_gaming_generate_kb_consumer_reports_1R1T:
.LFB24:
	.loc 1 948 1 is_stmt 1
	.cfi_startproc
.LVL123:
	.loc 1 949 5
	.loc 1 949 7 is_stmt 0
	lw	a5,reliable_tx_ptr
	beq	a5,zero,.L79
	.loc 1 951 9 is_stmt 1
.LBB194:
	.loc 1 973 92 is_stmt 0
	lw	a4,36(a0)
.LBE194:
	.loc 1 951 15
	lla	a0,sn_num
.LVL124:
	lw	a3,0(a0)
.LBB195:
	.loc 1 973 134
	li	a1,65536
	slli	a5,a4,8
	addi	a1,a1,-256
	.loc 1 973 237
	srli	a2,a4,16
.LBE195:
	.loc 1 951 15
	addi	a3,a3,1
.LBB196:
	.loc 1 973 134
	and	a5,a5,a1
	.loc 1 973 272
	slli	a2,a2,24
	.loc 1 973 34
	or	a5,a5,a2
	andi	t1,a3,255
	.loc 1 973 202
	slli	a1,a4,8
	.loc 1 973 34
	or	a5,a5,t1
	.loc 1 973 202
	li	t1,16711680
	and	a1,a1,t1
	.loc 1 973 340
	lla	a2,outgoing_report
	.loc 1 973 34
	or	a5,a5,a1
.LBE196:
.LBB197:
	.loc 1 980 34
	srli	a4,a4,24
	.loc 1 980 261
	sw	a4,4(a2)
.LBE197:
.LBB198:
	.loc 1 973 340
	sw	a5,0(a2)
.LBE198:
	.loc 1 986 52
	li	a5,10
	.loc 1 951 15
	sw	a3,0(a0)
	.loc 1 973 13 is_stmt 1
.LBB199:
	.loc 1 973 18
.LVL125:
	.loc 1 973 280
.LBE199:
	.loc 1 973 16
	.loc 1 980 13
.LBB200:
	.loc 1 980 18
	.loc 1 980 197
.LBE200:
	.loc 1 980 16
	.loc 1 986 13
	.loc 1 986 52 is_stmt 0
	sb	a5,7(a2)
.LVL126:
.L79:
	.loc 1 1017 1
	ret
	.cfi_endproc
.LFE24:
	.size	hid_express_gaming_generate_kb_consumer_reports_1R1T, .-hid_express_gaming_generate_kb_consumer_reports_1R1T
	.section	.text.hid_express_gaming_generate_kb_std_reports_1R1T,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_generate_kb_std_reports_1R1T
	.hidden	hid_express_gaming_generate_kb_std_reports_1R1T
	.type	hid_express_gaming_generate_kb_std_reports_1R1T, @function
hid_express_gaming_generate_kb_std_reports_1R1T:
.LFB25:
	.loc 1 1022 1 is_stmt 1
	.cfi_startproc
.LVL127:
	.loc 1 1023 5
	.loc 1 1023 7 is_stmt 0
	lw	a5,reliable_tx_ptr
	beq	a5,zero,.L84
	.loc 1 1025 9 is_stmt 1
	.loc 1 1025 15 is_stmt 0
	lla	a4,sn_num
	lw	a5,0(a4)
	.loc 1 1028 12
	lw	a2,rr_idx_2_4g
	li	a3,6
	.loc 1 1025 15
	addi	a5,a5,1
	sw	a5,0(a4)
	.loc 1 1028 9 is_stmt 1
	.loc 1 1028 12 is_stmt 0
	beq	a2,a3,.L88
.L84:
	.loc 1 1099 1
	ret
.L88:
	.loc 1 1048 13 is_stmt 1
.LBB201:
	.loc 1 1048 18
	.loc 1 1048 100 is_stmt 0
	lw	a2,28(a0)
.LVL128:
	.loc 1 1048 274 is_stmt 1
.LBE201:
.LBB202:
	.loc 1 1055 120 is_stmt 0
	lw	a3,32(a0)
.LBE202:
.LBB203:
	.loc 1 1048 132
	li	t0,65536
	addi	t0,t0,-1
	slli	a1,a2,8
.LVL129:
	.loc 1 1048 231
	srli	t1,a2,16
	.loc 1 1048 266
	slli	t1,t1,24
.LBE203:
.LBB204:
	.loc 1 1055 152
	slli	a4,a3,8
.LBE204:
.LBB205:
	.loc 1 1048 132
	and	a1,a1,t0
.LVL130:
	.loc 1 1048 198
	li	a0,16711680
.LVL131:
	.loc 1 1048 34
	or	a1,a1,t1
	andi	a5,a5,255
.LVL132:
	.loc 1 1048 198
	slli	t1,a2,8
.LVL133:
.LBE205:
.LBB206:
	.loc 1 1055 152
	and	a4,a4,t0
	.loc 1 1055 64
	srli	a2,a2,24
.LVL134:
	.loc 1 1055 218
	slli	a3,a3,8
.LBE206:
.LBB207:
	.loc 1 1048 34
	or	a1,a1,a5
.LBE207:
.LBB208:
	.loc 1 1055 218
	and	a3,a3,a0
	.loc 1 1055 99
	or	a5,a4,a2
	.loc 1 1055 34
	or	a5,a5,a3
.LBE208:
.LBB209:
	.loc 1 1048 329
	lla	a2,outgoing_report
	.loc 1 1048 198
	and	t1,t1,a0
.LVL135:
	.loc 1 1048 34
	or	a4,a1,t1
.LBE209:
.LBB210:
	.loc 1 1055 316
	sw	a5,4(a2)
.LBE210:
	.loc 1 1061 47
	li	a5,9
.LBB211:
	.loc 1 1048 329
	sw	a4,0(a2)
.LBE211:
	.loc 1 1048 16 is_stmt 1
	.loc 1 1055 13
.LBB212:
	.loc 1 1055 18
.LVL136:
	.loc 1 1055 258
.LBE212:
	.loc 1 1055 16
	.loc 1 1061 13
	.loc 1 1061 47 is_stmt 0
	sb	a5,8(a2)
	.loc 1 1099 1
	ret
	.cfi_endproc
.LFE25:
	.size	hid_express_gaming_generate_kb_std_reports_1R1T, .-hid_express_gaming_generate_kb_std_reports_1R1T
	.section	.text.hid_express_gaming_data_send,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_data_send
	.hidden	hid_express_gaming_data_send
	.type	hid_express_gaming_data_send, @function
hid_express_gaming_data_send:
.LFB26:
	.loc 1 1103 1 is_stmt 1
	.cfi_startproc
.LVL137:
	.loc 1 1104 5
	.loc 1 1103 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	ra,12(sp)
	sw	s1,4(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 1103 1
	sw	a0,0(sp)
	mv	s0,a1
	.loc 1 1104 26
	call	riscv_hid_report_id_select
.LVL138:
	.loc 1 1106 5 is_stmt 1
	addi	a5,a0,-1
	li	a4,9
	bgtu	a5,a4,.L90
	lla	a4,.L92
	slli	a5,a5,2
	add	a5,a5,a4
	lw	a5,0(a5)
	mv	s1,a0
	add	a5,a5,a4
	jr	a5
	.section	.rodata.hid_express_gaming_data_send,"a",@progbits
	.align	2
	.align	2
.L92:
	.word	.L96-.L92
	.word	.L95-.L92
	.word	.L90-.L92
	.word	.L90-.L92
	.word	.L94-.L92
	.word	.L90-.L92
	.word	.L90-.L92
	.word	.L90-.L92
	.word	.L93-.L92
	.word	.L91-.L92
	.section	.text.hid_express_gaming_data_send
.L96:
	.loc 1 1121 13
	lw	a0,0(sp)
.LVL139:
	call	hid_express_gaming_generate_kb_std_xy_reports_1R1T
.LVL140:
	.loc 1 1122 13
.L97:
	.loc 1 1165 5
	call	hid_express_gaming_submit_report_to_pka
.LVL141:
	.loc 1 1167 5
	.loc 1 1167 24 is_stmt 0
	lw	a5,reliable_tx_ptr
	.loc 1 1167 7
	beq	a5,zero,.L98
	.loc 1 1169 9 is_stmt 1
	.loc 1 1169 34 is_stmt 0
	sw	a5,reliable_tx_ptr_previous,a4
.L98:
	.loc 1 1173 5 is_stmt 1
	.loc 1 1173 20 is_stmt 0
	lla	a5,last_report_id
	sw	s1,0(a5)
	.loc 1 1175 5 is_stmt 1
	.loc 1 1175 7 is_stmt 0
	lw	a4,last_xy_over_12bits
	beq	a4,zero,.L90
	.loc 1 1178 9 is_stmt 1
	.loc 1 1178 24 is_stmt 0
	li	a4,9
	sw	a4,0(a5)
	.loc 1 1179 9 is_stmt 1
	.loc 1 1179 11 is_stmt 0
	bne	s0,zero,.L90
	.loc 1 1181 13 is_stmt 1
	.loc 1 1181 33 is_stmt 0
	sw	zero,last_xy_over_12bits,a5
.LVL142:
.L90:
	.loc 1 1188 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL143:
	lw	s1,4(sp)
	.cfi_restore 9
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
.LVL144:
	jr	ra
.LVL145:
.L94:
	.cfi_restore_state
	.loc 1 1124 13 is_stmt 1
	lw	a0,0(sp)
	call	hid_express_gaming_generate_kb_consumer_xy_reports_1R1T
.LVL146:
	.loc 1 1125 13
	j	.L97
.L91:
	.loc 1 1129 13
	lw	a0,0(sp)
	call	hid_express_gaming_generate_kb_consumer_reports_1R1T
.LVL147:
	.loc 1 1130 13
	j	.L97
.L93:
	.loc 1 1134 13
	lw	a0,0(sp)
	call	hid_express_gaming_generate_kb_std_reports_1R1T
.LVL148:
	.loc 1 1135 13
	j	.L97
.L95:
	.loc 1 1139 13
	lw	a0,0(sp)
	call	hid_express_gaming_generate_reports_1R1T_12bits
.LVL149:
	.loc 1 1140 13
	j	.L97
	.cfi_endproc
.LFE26:
	.size	hid_express_gaming_data_send, .-hid_express_gaming_data_send
	.section	.text.hid_express_gaming_init,"ax",@progbits
	.align	1
	.globl	hid_express_gaming_init
	.hidden	hid_express_gaming_init
	.type	hid_express_gaming_init, @function
hid_express_gaming_init:
.LFB27:
	.loc 1 1191 1
	.cfi_startproc
	.loc 1 1193 5
	lla	a1,g_vCtrl_y
	lla	a0,g_vCtrl_x
	tail	hid_express_x_y_buf_init
.LVL150:
	.cfi_endproc
.LFE27:
	.size	hid_express_gaming_init, .-hid_express_gaming_init
	.section	.text.hid_express_2_4g_post_process,"ax",@progbits
	.align	1
	.globl	hid_express_2_4g_post_process
	.hidden	hid_express_2_4g_post_process
	.type	hid_express_2_4g_post_process, @function
hid_express_2_4g_post_process:
.LFB28:
	.loc 1 1202 1
	.cfi_startproc
.LVL151:
	.loc 1 1204 1
	ret
	.cfi_endproc
.LFE28:
	.size	hid_express_2_4g_post_process, .-hid_express_2_4g_post_process
	.section	.bss.outgoing_report,"aw",@nobits
	.align	2
	.type	outgoing_report, @object
	.size	outgoing_report, 9
outgoing_report:
	.zero	9
	.hidden	reliable_tx_ptr_previous
	.globl	reliable_tx_ptr_previous
	.section	.sbss.reliable_tx_ptr_previous,"aw",@nobits
	.align	2
	.type	reliable_tx_ptr_previous, @object
	.size	reliable_tx_ptr_previous, 4
reliable_tx_ptr_previous:
	.zero	4
	.hidden	reliable_tx_ptr
	.globl	reliable_tx_ptr
	.section	.sbss.reliable_tx_ptr,"aw",@nobits
	.align	2
	.type	reliable_tx_ptr, @object
	.size	reliable_tx_ptr, 4
reliable_tx_ptr:
	.zero	4
	.section	.sdata.last_report_id,"aw"
	.align	2
	.type	last_report_id, @object
	.size	last_report_id, 4
last_report_id:
	.word	2
	.section	.sbss.last_xy_over_12bits,"aw",@nobits
	.align	2
	.type	last_xy_over_12bits, @object
	.size	last_xy_over_12bits, 4
last_xy_over_12bits:
	.zero	4
	.hidden	g_vCtrl_y
	.globl	g_vCtrl_y
	.section	.sbss.g_vCtrl_y,"aw",@nobits
	.align	2
	.type	g_vCtrl_y, @object
	.size	g_vCtrl_y, 4
g_vCtrl_y:
	.zero	4
	.hidden	g_vCtrl_x
	.globl	g_vCtrl_x
	.section	.sbss.g_vCtrl_x,"aw",@nobits
	.align	2
	.type	g_vCtrl_x, @object
	.size	g_vCtrl_x, 4
g_vCtrl_x:
	.zero	4
	.hidden	sn_num
	.globl	sn_num
	.section	.sbss.sn_num,"aw",@nobits
	.align	2
	.type	sn_num, @object
	.size	sn_num, 4
sn_num:
	.zero	4
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 4 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_key_remap.h"
	.file 6 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 7 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 8 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.file 9 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_xy_queue.h"
	.file 10 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_report_id_selector.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xe7b
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x2b
	.4byte	.LASF104
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL82
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x8
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x8
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x8
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x8
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x8
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x8
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x2c
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x8
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x2d
	.byte	0x4
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x2
	.byte	0x22
	.byte	0x15
	.4byte	0x34
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x2
	.byte	0x25
	.byte	0x13
	.4byte	0x42
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x2
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x5
	.4byte	.LASF17
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x5
	.4byte	.LASF18
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0xf
	.4byte	0xa0
	.4byte	0xd4
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x15
	.4byte	0xa0
	.uleb128 0xf
	.4byte	0xb8
	.4byte	0xe9
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x19
	.4byte	0x2d
	.byte	0x3
	.byte	0x50
	.byte	0xe
	.4byte	0x12c
	.uleb128 0x3
	.4byte	.LASF19
	.byte	0
	.uleb128 0x3
	.4byte	.LASF20
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF21
	.byte	0x2
	.uleb128 0x3
	.4byte	.LASF22
	.byte	0x3
	.uleb128 0x3
	.4byte	.LASF23
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF24
	.byte	0x5
	.uleb128 0x3
	.4byte	.LASF25
	.byte	0x6
	.uleb128 0x3
	.4byte	.LASF26
	.byte	0x7
	.uleb128 0x3
	.4byte	.LASF27
	.byte	0x8
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.byte	0x2
	.4byte	.LASF28
	.uleb128 0x19
	.4byte	0x2d
	.byte	0x4
	.byte	0x31
	.byte	0x1
	.4byte	0x170
	.uleb128 0x3
	.4byte	.LASF29
	.byte	0
	.uleb128 0x3
	.4byte	.LASF30
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF31
	.byte	0x2
	.uleb128 0x3
	.4byte	.LASF32
	.byte	0x3
	.uleb128 0x3
	.4byte	.LASF33
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF34
	.byte	0x5
	.uleb128 0x3
	.4byte	.LASF35
	.byte	0x6
	.uleb128 0x3
	.4byte	.LASF36
	.byte	0x7
	.byte	0
	.uleb128 0x11
	.byte	0x9
	.byte	0x5
	.byte	0xcf
	.4byte	0x1c7
	.uleb128 0x2
	.4byte	.LASF37
	.byte	0x5
	.byte	0xd0
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF38
	.byte	0x5
	.byte	0xd1
	.byte	0xd
	.4byte	0xa0
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF39
	.byte	0x5
	.byte	0xd2
	.byte	0xd
	.4byte	0xc4
	.byte	0x2
	.uleb128 0xb
	.string	"x_y"
	.byte	0x5
	.byte	0xd3
	.byte	0xc
	.4byte	0x1c7
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x5
	.byte	0xd4
	.byte	0xd
	.4byte	0xa0
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF41
	.byte	0x5
	.byte	0xd5
	.byte	0xd
	.4byte	0xa0
	.byte	0x8
	.byte	0
	.uleb128 0xf
	.4byte	0x7c
	.4byte	0x1d7
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.4byte	.LASF42
	.byte	0x5
	.byte	0xd6
	.byte	0x1e
	.4byte	0x170
	.uleb128 0x11
	.byte	0x9
	.byte	0x5
	.byte	0xd8
	.4byte	0x23a
	.uleb128 0x2
	.4byte	.LASF37
	.byte	0x5
	.byte	0xd9
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF43
	.byte	0x5
	.byte	0xda
	.byte	0xe
	.4byte	0xac
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF44
	.byte	0x5
	.byte	0xdb
	.byte	0xd
	.4byte	0xa0
	.byte	0x3
	.uleb128 0xb
	.string	"x_y"
	.byte	0x5
	.byte	0xdc
	.byte	0xc
	.4byte	0x1c7
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x5
	.byte	0xdd
	.byte	0xd
	.4byte	0xa0
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF41
	.byte	0x5
	.byte	0xde
	.byte	0xd
	.4byte	0xa0
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF45
	.byte	0x5
	.byte	0xdf
	.byte	0x1f
	.4byte	0x1e3
	.uleb128 0x11
	.byte	0x9
	.byte	0x6
	.byte	0x74
	.4byte	0x2a6
	.uleb128 0x2
	.4byte	.LASF37
	.byte	0x6
	.byte	0x75
	.byte	0xc
	.4byte	0x7c
	.byte	0
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x6
	.byte	0x76
	.byte	0xd
	.4byte	0xa0
	.byte	0x1
	.uleb128 0xb
	.string	"x"
	.byte	0x6
	.byte	0x77
	.byte	0xd
	.4byte	0x88
	.byte	0x2
	.uleb128 0xb
	.string	"y"
	.byte	0x6
	.byte	0x78
	.byte	0xd
	.4byte	0x88
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x6
	.byte	0x79
	.byte	0xc
	.4byte	0x7c
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x6
	.byte	0x7a
	.byte	0xc
	.4byte	0x7c
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF41
	.byte	0x6
	.byte	0x7b
	.byte	0xd
	.4byte	0xa0
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF48
	.byte	0x6
	.byte	0x7c
	.byte	0x1f
	.4byte	0x246
	.uleb128 0xf
	.4byte	0xa0
	.4byte	0x2c2
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0xf
	.4byte	0xa0
	.4byte	0x2d2
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x11
	.byte	0x9
	.byte	0x6
	.byte	0xbf
	.4byte	0x31c
	.uleb128 0x2
	.4byte	.LASF37
	.byte	0x6
	.byte	0xc0
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF38
	.byte	0x6
	.byte	0xc1
	.byte	0xd
	.4byte	0xa0
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF39
	.byte	0x6
	.byte	0xc2
	.byte	0xd
	.4byte	0x2b2
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x6
	.byte	0xc3
	.byte	0xd
	.4byte	0xa0
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF41
	.byte	0x6
	.byte	0xc4
	.byte	0xd
	.4byte	0xa0
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF49
	.byte	0x6
	.byte	0xc5
	.byte	0x1e
	.4byte	0x2d2
	.uleb128 0x11
	.byte	0x8
	.byte	0x6
	.byte	0xc7
	.4byte	0x372
	.uleb128 0x2
	.4byte	.LASF37
	.byte	0x6
	.byte	0xc8
	.byte	0xd
	.4byte	0xa0
	.byte	0
	.uleb128 0x2
	.4byte	.LASF43
	.byte	0x6
	.byte	0xc9
	.byte	0xd
	.4byte	0x2c2
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF44
	.byte	0x6
	.byte	0xca
	.byte	0xd
	.4byte	0xa0
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0x6
	.byte	0xcb
	.byte	0xd
	.4byte	0xa0
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF41
	.byte	0x6
	.byte	0xcc
	.byte	0xd
	.4byte	0xa0
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.4byte	.LASF50
	.byte	0x6
	.byte	0xcd
	.byte	0x1f
	.4byte	0x328
	.uleb128 0x11
	.byte	0x28
	.byte	0x7
	.byte	0x8d
	.4byte	0x3f4
	.uleb128 0x2
	.4byte	.LASF51
	.byte	0x7
	.byte	0x8e
	.byte	0xe
	.4byte	0xb8
	.byte	0
	.uleb128 0xb
	.string	"k"
	.byte	0x7
	.byte	0x8f
	.byte	0xe
	.4byte	0xb8
	.byte	0x4
	.uleb128 0xb
	.string	"x"
	.byte	0x7
	.byte	0x90
	.byte	0xd
	.4byte	0x94
	.byte	0x8
	.uleb128 0xb
	.string	"y"
	.byte	0x7
	.byte	0x91
	.byte	0xd
	.4byte	0x94
	.byte	0xc
	.uleb128 0xb
	.string	"z1"
	.byte	0x7
	.byte	0x92
	.byte	0xd
	.4byte	0x94
	.byte	0x10
	.uleb128 0xb
	.string	"z2"
	.byte	0x7
	.byte	0x93
	.byte	0xd
	.4byte	0x94
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF52
	.byte	0x7
	.byte	0x94
	.byte	0xe
	.4byte	0xb8
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF53
	.byte	0x7
	.byte	0x95
	.byte	0xe
	.4byte	0xd9
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF54
	.byte	0x7
	.byte	0x96
	.byte	0xe
	.4byte	0xb8
	.byte	0x24
	.byte	0
	.uleb128 0x5
	.4byte	.LASF55
	.byte	0x7
	.byte	0x9c
	.byte	0x2
	.4byte	0x37e
	.uleb128 0x5
	.4byte	.LASF56
	.byte	0x7
	.byte	0xc9
	.byte	0x2d
	.4byte	0x57
	.uleb128 0x15
	.4byte	0x3f4
	.uleb128 0x19
	.4byte	0x2d
	.byte	0x8
	.byte	0x6e
	.byte	0xe
	.4byte	0x436
	.uleb128 0x3
	.4byte	.LASF57
	.byte	0
	.uleb128 0x3
	.4byte	.LASF58
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF59
	.byte	0x2
	.uleb128 0x3
	.4byte	.LASF60
	.byte	0x3
	.byte	0
	.uleb128 0x11
	.byte	0x10
	.byte	0x9
	.byte	0x37
	.4byte	0x466
	.uleb128 0x2
	.4byte	.LASF61
	.byte	0x9
	.byte	0x38
	.byte	0xd
	.4byte	0x466
	.byte	0
	.uleb128 0x2
	.4byte	.LASF62
	.byte	0x9
	.byte	0x39
	.byte	0xd
	.4byte	0x476
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF63
	.byte	0x9
	.byte	0x3a
	.byte	0xd
	.4byte	0x94
	.byte	0xc
	.byte	0
	.uleb128 0xf
	.4byte	0x94
	.4byte	0x476
	.uleb128 0x10
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	0x94
	.4byte	0x486
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF64
	.byte	0x9
	.byte	0x3c
	.byte	0x2
	.4byte	0x436
	.uleb128 0x2e
	.4byte	.LASF65
	.byte	0x1
	.byte	0x4b
	.byte	0x11
	.4byte	0xb8
	.uleb128 0x16
	.4byte	.LASF66
	.byte	0x4e
	.byte	0xa
	.4byte	0xb8
	.uleb128 0x5
	.byte	0x3
	.4byte	sn_num
	.uleb128 0x2f
	.byte	0x9
	.byte	0x1
	.byte	0x4f
	.byte	0x9
	.4byte	0x4f0
	.uleb128 0x17
	.4byte	.LASF67
	.byte	0x51
	.byte	0x27
	.4byte	0x2a6
	.uleb128 0x17
	.4byte	.LASF68
	.byte	0x57
	.byte	0x26
	.4byte	0x372
	.uleb128 0x17
	.4byte	.LASF69
	.byte	0x5a
	.byte	0x24
	.4byte	0x1d7
	.uleb128 0x17
	.4byte	.LASF70
	.byte	0x5b
	.byte	0x29
	.4byte	0x23a
	.uleb128 0x17
	.4byte	.LASF71
	.byte	0x5e
	.byte	0x21
	.4byte	0x31c
	.byte	0
	.uleb128 0x5
	.4byte	.LASF72
	.byte	0x1
	.byte	0x70
	.byte	0x1f
	.4byte	0x4af
	.uleb128 0x16
	.4byte	.LASF73
	.byte	0x73
	.byte	0x18
	.4byte	0x50d
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vCtrl_x
	.uleb128 0x15
	.4byte	0x486
	.uleb128 0x16
	.4byte	.LASF74
	.byte	0x74
	.byte	0x18
	.4byte	0x50d
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vCtrl_y
	.uleb128 0x1a
	.4byte	.LASF75
	.byte	0x76
	.byte	0x11
	.4byte	0xb8
	.uleb128 0x5
	.byte	0x3
	.4byte	last_xy_over_12bits
	.uleb128 0x1a
	.4byte	.LASF76
	.byte	0x7b
	.byte	0x11
	.4byte	0xb8
	.uleb128 0x5
	.byte	0x3
	.4byte	last_report_id
	.uleb128 0x16
	.4byte	.LASF77
	.byte	0x7f
	.byte	0xa
	.4byte	0xd4
	.uleb128 0x5
	.byte	0x3
	.4byte	reliable_tx_ptr
	.uleb128 0x16
	.4byte	.LASF78
	.byte	0x80
	.byte	0xa
	.4byte	0xd4
	.uleb128 0x5
	.byte	0x3
	.4byte	reliable_tx_ptr_previous
	.uleb128 0x1a
	.4byte	.LASF79
	.byte	0x83
	.byte	0x16
	.4byte	0x4f0
	.uleb128 0x5
	.byte	0x3
	.4byte	outgoing_report
	.uleb128 0x1e
	.4byte	.LASF80
	.byte	0x3e
	.4byte	0x58d
	.uleb128 0x12
	.4byte	0x58d
	.uleb128 0x12
	.4byte	0x58d
	.byte	0
	.uleb128 0x15
	.4byte	0x50d
	.uleb128 0x30
	.4byte	.LASF105
	.byte	0xa
	.byte	0x27
	.byte	0xa
	.4byte	0xb8
	.4byte	0x5a8
	.uleb128 0x12
	.4byte	0x40c
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF81
	.byte	0x41
	.4byte	0x5c2
	.uleb128 0x12
	.4byte	0x50d
	.uleb128 0x12
	.4byte	0xb8
	.uleb128 0x12
	.4byte	0x94
	.byte	0
	.uleb128 0x31
	.4byte	.LASF101
	.byte	0x8
	.2byte	0x143
	.byte	0x7
	.4byte	0x73
	.uleb128 0x13
	.4byte	.LASF86
	.2byte	0x4b1
	.byte	0x6
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5f5
	.uleb128 0x32
	.4byte	.LASF82
	.byte	0x1
	.2byte	0x4b1
	.byte	0x2d
	.4byte	0xb8
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x33
	.4byte	.LASF106
	.byte	0x1
	.2byte	0x4a6
	.byte	0x6
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x629
	.uleb128 0x34
	.4byte	.LVL150
	.4byte	0x578
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vCtrl_x
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vCtrl_y
	.byte	0
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF90
	.2byte	0x44e
	.4byte	0x65
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x716
	.uleb128 0x6
	.4byte	.LASF83
	.2byte	0x44e
	.byte	0x37
	.4byte	0x40c
	.4byte	.LLST77
	.uleb128 0x6
	.4byte	.LASF82
	.2byte	0x44e
	.byte	0x4a
	.4byte	0xb8
	.4byte	.LLST78
	.uleb128 0x6
	.4byte	.LASF84
	.2byte	0x44e
	.byte	0x5e
	.4byte	0xb8
	.4byte	.LLST79
	.uleb128 0x6
	.4byte	.LASF85
	.2byte	0x44e
	.byte	0x6f
	.4byte	0xb8
	.4byte	.LLST80
	.uleb128 0xd
	.4byte	.LASF41
	.2byte	0x450
	.byte	0xe
	.4byte	0xb8
	.4byte	.LLST81
	.uleb128 0x9
	.4byte	.LVL138
	.4byte	0x592
	.4byte	0x6a7
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x9
	.4byte	.LVL140
	.4byte	0x9e5
	.4byte	0x6bc
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x20
	.4byte	.LVL141
	.4byte	0x7fa
	.uleb128 0x9
	.4byte	.LVL146
	.4byte	0x884
	.4byte	0x6da
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x9
	.4byte	.LVL147
	.4byte	0x7a3
	.4byte	0x6ef
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x9
	.4byte	.LVL148
	.4byte	0x716
	.4byte	0x704
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xc
	.4byte	.LVL149
	.4byte	0xb46
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x13
	.4byte	.LASF87
	.2byte	0x3fd
	.byte	0x27
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x7a3
	.uleb128 0x6
	.4byte	.LASF83
	.2byte	0x3fd
	.byte	0x6c
	.4byte	0x40c
	.4byte	.LLST73
	.uleb128 0xa
	.4byte	.LLRL74
	.4byte	0x756
	.uleb128 0xd
	.4byte	.LASF88
	.2byte	0x418
	.byte	0x22
	.4byte	0x400
	.4byte	.LLST75
	.byte	0
	.uleb128 0xe
	.4byte	.LLRL76
	.uleb128 0x35
	.4byte	.LASF88
	.byte	0x1
	.2byte	0x41f
	.byte	0x22
	.4byte	0x400
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
	.byte	0
	.uleb128 0x13
	.4byte	.LASF89
	.2byte	0x3b3
	.byte	0x27
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x7fa
	.uleb128 0x6
	.4byte	.LASF83
	.2byte	0x3b3
	.byte	0x71
	.4byte	0x40c
	.4byte	.LLST68
	.uleb128 0xa
	.4byte	.LLRL69
	.4byte	0x7e3
	.uleb128 0xd
	.4byte	.LASF88
	.2byte	0x3cd
	.byte	0x22
	.4byte	0x400
	.4byte	.LLST70
	.byte	0
	.uleb128 0xe
	.4byte	.LLRL71
	.uleb128 0xd
	.4byte	.LASF88
	.2byte	0x3d4
	.byte	0x22
	.4byte	0x400
	.4byte	.LLST72
	.byte	0
	.byte	0
	.uleb128 0x36
	.4byte	.LASF107
	.byte	0x1
	.2byte	0x1e2
	.byte	0x27
	.byte	0x1
	.uleb128 0x1f
	.4byte	.LASF91
	.2byte	0x1d3
	.4byte	0x65
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x884
	.uleb128 0x6
	.4byte	.LASF83
	.2byte	0x1d3
	.byte	0x3c
	.4byte	0x40c
	.4byte	.LLST63
	.uleb128 0x6
	.4byte	.LASF82
	.2byte	0x1d3
	.byte	0x4f
	.4byte	0xb8
	.4byte	.LLST64
	.uleb128 0x6
	.4byte	.LASF84
	.2byte	0x1d3
	.byte	0x63
	.4byte	0xb8
	.4byte	.LLST65
	.uleb128 0x6
	.4byte	.LASF85
	.2byte	0x1d3
	.byte	0x74
	.4byte	0xb8
	.4byte	.LLST66
	.uleb128 0x9
	.4byte	.LVL117
	.4byte	0x5a8
	.4byte	0x872
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xc
	.4byte	.LVL118
	.4byte	0x5a8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x13
	.4byte	.LASF92
	.2byte	0x1a2
	.byte	0x27
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9e5
	.uleb128 0x6
	.4byte	.LASF83
	.2byte	0x1a2
	.byte	0x74
	.4byte	0x40c
	.4byte	.LLST46
	.uleb128 0xa
	.4byte	.LLRL47
	.4byte	0x9db
	.uleb128 0x18
	.string	"x12"
	.2byte	0x1a7
	.byte	0x11
	.4byte	0x94
	.4byte	.LLST48
	.uleb128 0x18
	.string	"y12"
	.2byte	0x1a7
	.byte	0x1a
	.4byte	0x94
	.4byte	.LLST49
	.uleb128 0xa
	.4byte	.LLRL61
	.4byte	0x8ed
	.uleb128 0xd
	.4byte	.LASF88
	.2byte	0x1ad
	.byte	0x1e
	.4byte	0x400
	.4byte	.LLST62
	.byte	0
	.uleb128 0xa
	.4byte	.LLRL60
	.4byte	0x902
	.uleb128 0x21
	.4byte	.LASF88
	.2byte	0x1b4
	.4byte	0x400
	.byte	0
	.uleb128 0x22
	.4byte	0xc1b
	.4byte	.LBB148
	.4byte	.LLRL50
	.2byte	0x1a9
	.4byte	0x970
	.uleb128 0x4
	.4byte	0xc3f
	.4byte	.LLST51
	.uleb128 0x4
	.4byte	0xc33
	.4byte	.LLST52
	.uleb128 0x4
	.4byte	0xc28
	.4byte	.LLST53
	.uleb128 0xe
	.4byte	.LLRL50
	.uleb128 0x7
	.4byte	0xc4a
	.4byte	.LLST54
	.uleb128 0x9
	.4byte	.LVL96
	.4byte	0x5a8
	.4byte	0x958
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xb
	.2byte	0xf801
	.byte	0
	.uleb128 0xc
	.4byte	.LVL108
	.4byte	0x5a8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x800
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	0xc1b
	.4byte	.LBB155
	.4byte	.LLRL55
	.2byte	0x1aa
	.uleb128 0x4
	.4byte	0xc3f
	.4byte	.LLST56
	.uleb128 0x4
	.4byte	0xc33
	.4byte	.LLST57
	.uleb128 0x4
	.4byte	0xc28
	.4byte	.LLST58
	.uleb128 0xe
	.4byte	.LLRL55
	.uleb128 0x7
	.4byte	0xc4a
	.4byte	.LLST59
	.uleb128 0x9
	.4byte	.LVL103
	.4byte	0x5a8
	.4byte	0x9c2
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xb
	.2byte	0xf801
	.byte	0
	.uleb128 0xc
	.4byte	.LVL112
	.4byte	0x5a8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x800
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL106
	.4byte	0xbaa
	.byte	0
	.uleb128 0x13
	.4byte	.LASF93
	.2byte	0x171
	.byte	0x27
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb46
	.uleb128 0x6
	.4byte	.LASF83
	.2byte	0x171
	.byte	0x6f
	.4byte	0x40c
	.4byte	.LLST29
	.uleb128 0xa
	.4byte	.LLRL30
	.4byte	0xb3c
	.uleb128 0x18
	.string	"x12"
	.2byte	0x176
	.byte	0x11
	.4byte	0x94
	.4byte	.LLST31
	.uleb128 0x18
	.string	"y12"
	.2byte	0x176
	.byte	0x1a
	.4byte	0x94
	.4byte	.LLST32
	.uleb128 0xa
	.4byte	.LLRL44
	.4byte	0xa4e
	.uleb128 0xd
	.4byte	.LASF88
	.2byte	0x17d
	.byte	0x1e
	.4byte	0x400
	.4byte	.LLST45
	.byte	0
	.uleb128 0xa
	.4byte	.LLRL43
	.4byte	0xa63
	.uleb128 0x21
	.4byte	.LASF88
	.2byte	0x184
	.4byte	0x400
	.byte	0
	.uleb128 0x22
	.4byte	0xc1b
	.4byte	.LBB102
	.4byte	.LLRL33
	.2byte	0x178
	.4byte	0xad1
	.uleb128 0x4
	.4byte	0xc3f
	.4byte	.LLST34
	.uleb128 0x4
	.4byte	0xc33
	.4byte	.LLST35
	.uleb128 0x4
	.4byte	0xc28
	.4byte	.LLST36
	.uleb128 0xe
	.4byte	.LLRL33
	.uleb128 0x7
	.4byte	0xc4a
	.4byte	.LLST37
	.uleb128 0x9
	.4byte	.LVL66
	.4byte	0x5a8
	.4byte	0xab9
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xb
	.2byte	0xf801
	.byte	0
	.uleb128 0xc
	.4byte	.LVL78
	.4byte	0x5a8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x800
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	0xc1b
	.4byte	.LBB108
	.4byte	.LLRL38
	.2byte	0x179
	.uleb128 0x4
	.4byte	0xc3f
	.4byte	.LLST39
	.uleb128 0x4
	.4byte	0xc33
	.4byte	.LLST40
	.uleb128 0x4
	.4byte	0xc28
	.4byte	.LLST41
	.uleb128 0xe
	.4byte	.LLRL38
	.uleb128 0x7
	.4byte	0xc4a
	.4byte	.LLST42
	.uleb128 0x9
	.4byte	.LVL73
	.4byte	0x5a8
	.4byte	0xb23
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xb
	.2byte	0xf801
	.byte	0
	.uleb128 0xc
	.4byte	.LVL82
	.4byte	0x5a8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x800
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL76
	.4byte	0xbaa
	.byte	0
	.uleb128 0x13
	.4byte	.LASF94
	.2byte	0x122
	.byte	0x27
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbaa
	.uleb128 0x6
	.4byte	.LASF83
	.2byte	0x122
	.byte	0x6c
	.4byte	0x40c
	.4byte	.LLST24
	.uleb128 0xa
	.4byte	.LLRL25
	.4byte	0xb86
	.uleb128 0xd
	.4byte	.LASF88
	.2byte	0x12a
	.byte	0x1e
	.4byte	0x400
	.4byte	.LLST26
	.byte	0
	.uleb128 0xa
	.4byte	.LLRL27
	.4byte	0xba0
	.uleb128 0xd
	.4byte	.LASF88
	.2byte	0x131
	.byte	0x1e
	.4byte	0x400
	.4byte	.LLST28
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL50
	.4byte	0xbaa
	.byte	0
	.uleb128 0x37
	.4byte	.LASF108
	.byte	0x1
	.byte	0xaf
	.byte	0x27
	.byte	0x1
	.4byte	0xc1b
	.uleb128 0x14
	.4byte	.LASF95
	.byte	0xb1
	.byte	0xd
	.4byte	0xa0
	.uleb128 0x1c
	.4byte	0xbd3
	.uleb128 0x14
	.4byte	.LASF88
	.byte	0xb8
	.byte	0x22
	.4byte	0x400
	.byte	0
	.uleb128 0x1c
	.4byte	0xbe4
	.uleb128 0x14
	.4byte	.LASF88
	.byte	0xbf
	.byte	0x22
	.4byte	0x400
	.byte	0
	.uleb128 0x24
	.uleb128 0x25
	.string	"x12"
	.byte	0xde
	.byte	0x19
	.4byte	0x94
	.uleb128 0x25
	.string	"y12"
	.byte	0xde
	.byte	0x22
	.4byte	0x94
	.uleb128 0x1c
	.4byte	0xc0c
	.uleb128 0x14
	.4byte	.LASF88
	.byte	0xe3
	.byte	0x26
	.4byte	0x400
	.byte	0
	.uleb128 0x24
	.uleb128 0x14
	.4byte	.LASF88
	.byte	0xea
	.byte	0x26
	.4byte	0x400
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x38
	.4byte	.LASF96
	.byte	0x1
	.byte	0x98
	.byte	0x27
	.byte	0x1
	.4byte	0xc56
	.uleb128 0x26
	.4byte	.LASF97
	.byte	0x98
	.byte	0x54
	.4byte	0xc56
	.uleb128 0x39
	.string	"raw"
	.byte	0x1
	.byte	0x98
	.byte	0x64
	.4byte	0x94
	.uleb128 0x26
	.4byte	.LASF98
	.byte	0x98
	.byte	0x6f
	.4byte	0x73
	.uleb128 0x14
	.4byte	.LASF99
	.byte	0x9a
	.byte	0xd
	.4byte	0x94
	.byte	0
	.uleb128 0x15
	.4byte	0x94
	.uleb128 0x3a
	.4byte	.LASF100
	.byte	0x1
	.byte	0x8b
	.byte	0x26
	.4byte	0x65
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc7f
	.uleb128 0x20
	.4byte	.LVL0
	.4byte	0x5c2
	.byte	0
	.uleb128 0x27
	.4byte	.LASF102
	.2byte	0x12b
	.4byte	0xa0
	.uleb128 0x27
	.4byte	.LASF103
	.2byte	0x126
	.4byte	0xa0
	.uleb128 0x28
	.4byte	0xc1b
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xcfd
	.uleb128 0x4
	.4byte	0xc28
	.4byte	.LLST0
	.uleb128 0x4
	.4byte	0xc33
	.4byte	.LLST1
	.uleb128 0x4
	.4byte	0xc3f
	.4byte	.LLST2
	.uleb128 0x7
	.4byte	0xc4a
	.4byte	.LLST3
	.uleb128 0x9
	.4byte	.LVL8
	.4byte	0x5a8
	.4byte	0xce6
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x800
	.byte	0
	.uleb128 0xc
	.4byte	.LVL13
	.4byte	0x5a8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xb
	.2byte	0xf801
	.byte	0
	.byte	0
	.uleb128 0x28
	.4byte	0xbaa
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe5d
	.uleb128 0x7
	.4byte	0xbb7
	.4byte	.LLST4
	.uleb128 0x1d
	.4byte	0xbc2
	.4byte	.LLRL5
	.4byte	0xd30
	.uleb128 0x7
	.4byte	0xbc7
	.4byte	.LLST6
	.byte	0
	.uleb128 0x1d
	.4byte	0xbd3
	.4byte	.LLRL7
	.4byte	0xd47
	.uleb128 0x7
	.4byte	0xbd8
	.4byte	.LLST8
	.byte	0
	.uleb128 0x3b
	.4byte	0xbaa
	.4byte	.LBB38
	.4byte	.LBE38-.LBB38
	.byte	0x1
	.byte	0xaf
	.byte	0x27
	.uleb128 0x29
	.4byte	0xbb7
	.uleb128 0x3c
	.4byte	0xbe4
	.4byte	.LBB40
	.4byte	.LBE40-.LBB40
	.uleb128 0x7
	.4byte	0xbe5
	.4byte	.LLST9
	.uleb128 0x7
	.4byte	0xbf0
	.4byte	.LLST10
	.uleb128 0x2a
	.4byte	0xc1b
	.4byte	.LBB41
	.4byte	.LLRL11
	.byte	0xdf
	.4byte	0xdc7
	.uleb128 0x4
	.4byte	0xc3f
	.4byte	.LLST12
	.uleb128 0x4
	.4byte	0xc33
	.4byte	.LLST13
	.uleb128 0x4
	.4byte	0xc28
	.4byte	.LLST14
	.uleb128 0xe
	.4byte	.LLRL11
	.uleb128 0x7
	.4byte	0xc4a
	.4byte	.LLST15
	.uleb128 0xc
	.4byte	.LVL41
	.4byte	0x5a8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0xc1b
	.4byte	.LBB47
	.4byte	.LLRL16
	.byte	0xe0
	.4byte	0xe34
	.uleb128 0x4
	.4byte	0xc3f
	.4byte	.LLST17
	.uleb128 0x4
	.4byte	0xc33
	.4byte	.LLST18
	.uleb128 0x4
	.4byte	0xc28
	.4byte	.LLST19
	.uleb128 0xe
	.4byte	.LLRL16
	.uleb128 0x7
	.4byte	0xc4a
	.4byte	.LLST20
	.uleb128 0x9
	.4byte	.LVL37
	.4byte	0x5a8
	.4byte	0xe1c
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x800
	.byte	0
	.uleb128 0xc
	.4byte	.LVL44
	.4byte	0x5a8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xb
	.2byte	0xf801
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1d
	.4byte	0xbfb
	.4byte	.LLRL21
	.4byte	0xe4b
	.uleb128 0x7
	.4byte	0xc00
	.4byte	.LLST22
	.byte	0
	.uleb128 0x3d
	.4byte	0xc0c
	.4byte	.LLRL23
	.uleb128 0x29
	.4byte	0xc0d
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x3e
	.4byte	0x7fa
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x3f
	.4byte	0x7fa
	.4byte	.LBB190
	.4byte	.LLRL67
	.byte	0x1
	.2byte	0x1e2
	.byte	0x27
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
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
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xe
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
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
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x14
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
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x17
	.uleb128 0xd
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
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
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
	.sleb128 9
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
	.uleb128 0x1f
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
	.uleb128 0x20
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 30
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
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
	.uleb128 0x21
	.sleb128 9
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 16
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 3
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0x29
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0x21
	.sleb128 17
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x2f
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
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
	.uleb128 0x3c
	.uleb128 0x19
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
	.uleb128 0x35
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
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x37
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x38
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x39
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
	.uleb128 0x3b
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
	.uleb128 0x3c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x3d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x3e
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
	.uleb128 0x3f
	.uleb128 0x1d
	.byte	0
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
.LLST77:
	.byte	0x6
	.4byte	.LVL137
	.byte	0x4
	.uleb128 .LVL137-.LVL137
	.uleb128 .LVL138-1-.LVL137
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL138-1-.LVL137
	.uleb128 .LVL144-.LVL137
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL144-.LVL137
	.uleb128 .LVL145-.LVL137
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL145-.LVL137
	.uleb128 .LFE26-.LVL137
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST78:
	.byte	0x6
	.4byte	.LVL137
	.byte	0x4
	.uleb128 .LVL137-.LVL137
	.uleb128 .LVL138-1-.LVL137
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL138-1-.LVL137
	.uleb128 .LVL143-.LVL137
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL143-.LVL137
	.uleb128 .LVL145-.LVL137
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
	.uleb128 .LVL145-.LVL137
	.uleb128 .LFE26-.LVL137
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST79:
	.byte	0x6
	.4byte	.LVL137
	.byte	0x4
	.uleb128 .LVL137-.LVL137
	.uleb128 .LVL138-1-.LVL137
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL138-1-.LVL137
	.uleb128 .LFE26-.LVL137
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
.LLST80:
	.byte	0x6
	.4byte	.LVL137
	.byte	0x4
	.uleb128 .LVL137-.LVL137
	.uleb128 .LVL138-1-.LVL137
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL138-1-.LVL137
	.uleb128 .LFE26-.LVL137
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
.LLST81:
	.byte	0x6
	.4byte	.LVL138
	.byte	0x4
	.uleb128 .LVL138-.LVL138
	.uleb128 .LVL139-.LVL138
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL139-.LVL138
	.uleb128 .LVL142-.LVL138
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL145-.LVL138
	.uleb128 .LFE26-.LVL138
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST73:
	.byte	0x6
	.4byte	.LVL127
	.byte	0x4
	.uleb128 .LVL127-.LVL127
	.uleb128 .LVL131-.LVL127
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL131-.LVL127
	.uleb128 .LFE25-.LVL127
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
.LLST75:
	.byte	0x6
	.4byte	.LVL128
	.byte	0x4
	.uleb128 .LVL128-.LVL128
	.uleb128 .LVL129-.LVL128
	.uleb128 0x22
	.byte	0x7c
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7f
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x7c
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
	.byte	0x7c
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL129-.LVL128
	.uleb128 .LVL130-.LVL128
	.uleb128 0x20
	.byte	0x7b
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7f
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x7c
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
	.byte	0x7c
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL130-.LVL128
	.uleb128 .LVL132-.LVL128
	.uleb128 0x22
	.byte	0x7c
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7f
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x7c
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
	.byte	0x7c
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL132-.LVL128
	.uleb128 .LVL133-.LVL128
	.uleb128 0x26
	.byte	0x7c
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x3
	.4byte	sn_num
	.byte	0x6
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x7c
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
	.byte	0x7c
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL133-.LVL128
	.uleb128 .LVL134-.LVL128
	.uleb128 0x24
	.byte	0x76
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x3
	.4byte	sn_num
	.byte	0x6
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x7c
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
	.byte	0x7c
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL134-.LVL128
	.uleb128 .LVL135-.LVL128
	.uleb128 0x38
	.byte	0x76
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x3
	.4byte	sn_num
	.byte	0x6
	.byte	0x8
	.byte	0xff
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
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL135-.LVL128
	.uleb128 .LFE25-.LVL128
	.uleb128 0x44
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
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x3
	.4byte	sn_num
	.byte	0x6
	.byte	0x8
	.byte	0xff
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
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST68:
	.byte	0x6
	.4byte	.LVL123
	.byte	0x4
	.uleb128 .LVL123-.LVL123
	.uleb128 .LVL124-.LVL123
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL124-.LVL123
	.uleb128 .LFE24-.LVL123
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
.LLST70:
	.byte	0x8
	.4byte	.LVL125
	.uleb128 .LVL126-.LVL125
	.uleb128 0x40
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
	.uleb128 0x24
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7d
	.sleb128 0
	.byte	0x8
	.byte	0xff
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
	.uleb128 0x24
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
	.uleb128 0x24
	.byte	0x6
	.byte	0x40
	.byte	0x25
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST72:
	.byte	0x8
	.4byte	.LVL125
	.uleb128 .LVL126-.LVL125
	.uleb128 0xf
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
	.uleb128 0x24
	.byte	0x6
	.byte	0x48
	.byte	0x25
	.byte	0x9f
	.byte	0
.LLST63:
	.byte	0x6
	.4byte	.LVL113
	.byte	0x4
	.uleb128 .LVL113-.LVL113
	.uleb128 .LVL116-.LVL113
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL116-.LVL113
	.uleb128 .LVL119-.LVL113
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL119-.LVL113
	.uleb128 .LVL121-.LVL113
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
	.uleb128 .LVL121-.LVL113
	.uleb128 .LFE22-.LVL113
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST64:
	.byte	0x6
	.4byte	.LVL113
	.byte	0x4
	.uleb128 .LVL113-.LVL113
	.uleb128 .LVL114-.LVL113
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL114-.LVL113
	.uleb128 .LVL117-1-.LVL113
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL117-1-.LVL113
	.uleb128 .LVL120-.LVL113
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL120-.LVL113
	.uleb128 .LVL121-.LVL113
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL121-.LVL113
	.uleb128 .LVL122-.LVL113
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL122-.LVL113
	.uleb128 .LFE22-.LVL113
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
.LLST65:
	.byte	0x6
	.4byte	.LVL113
	.byte	0x4
	.uleb128 .LVL113-.LVL113
	.uleb128 .LVL115-.LVL113
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL115-.LVL113
	.uleb128 .LVL121-.LVL113
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
	.uleb128 .LVL121-.LVL113
	.uleb128 .LFE22-.LVL113
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST66:
	.byte	0x6
	.4byte	.LVL113
	.byte	0x4
	.uleb128 .LVL113-.LVL113
	.uleb128 .LVL117-1-.LVL113
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL117-1-.LVL113
	.uleb128 .LVL121-.LVL113
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
	.byte	0x4
	.uleb128 .LVL121-.LVL113
	.uleb128 .LFE22-.LVL113
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST46:
	.byte	0x6
	.4byte	.LVL83
	.byte	0x4
	.uleb128 .LVL83-.LVL83
	.uleb128 .LVL84-.LVL83
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL84-.LVL83
	.uleb128 .LVL88-.LVL83
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL88-.LVL83
	.uleb128 .LVL94-.LVL83
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
	.uleb128 .LVL94-.LVL83
	.uleb128 .LVL96-1-.LVL83
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL96-1-.LVL83
	.uleb128 .LVL101-.LVL83
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL101-.LVL83
	.uleb128 .LVL105-.LVL83
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
	.uleb128 .LVL105-.LVL83
	.uleb128 .LVL106-1-.LVL83
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL106-1-.LVL83
	.uleb128 .LVL106-.LVL83
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
	.uleb128 .LVL106-.LVL83
	.uleb128 .LVL108-1-.LVL83
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL108-1-.LVL83
	.uleb128 .LVL110-.LVL83
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL110-.LVL83
	.uleb128 .LFE21-.LVL83
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
.LLST48:
	.byte	0x6
	.4byte	.LVL96
	.byte	0x4
	.uleb128 .LVL96-.LVL96
	.uleb128 .LVL98-.LVL96
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL108-.LVL96
	.uleb128 .LVL110-.LVL96
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0
.LLST49:
	.byte	0x6
	.4byte	.LVL103
	.byte	0x4
	.uleb128 .LVL103-.LVL103
	.uleb128 .LVL104-.LVL103
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL112-.LVL103
	.uleb128 .LFE21-.LVL103
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0
.LLST62:
	.byte	0x8
	.4byte	.LVL91
	.uleb128 .LVL92-.LVL91
	.uleb128 0x1d
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
	.byte	0x76
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST51:
	.byte	0x6
	.4byte	.LVL85
	.byte	0x4
	.uleb128 .LVL85-.LVL85
	.uleb128 .LVL86-.LVL85
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL94-.LVL85
	.uleb128 .LVL96-1-.LVL85
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL106-.LVL85
	.uleb128 .LVL108-1-.LVL85
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST52:
	.byte	0x6
	.4byte	.LVL85
	.byte	0x4
	.uleb128 .LVL85-.LVL85
	.uleb128 .LVL86-.LVL85
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL94-.LVL85
	.uleb128 .LVL95-.LVL85
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL95-.LVL85
	.uleb128 .LVL98-.LVL85
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL106-.LVL85
	.uleb128 .LVL107-.LVL85
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL107-.LVL85
	.uleb128 .LVL110-.LVL85
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0
.LLST53:
	.byte	0x6
	.4byte	.LVL85
	.byte	0x4
	.uleb128 .LVL85-.LVL85
	.uleb128 .LVL86-.LVL85
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2227
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL94-.LVL85
	.uleb128 .LVL99-.LVL85
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2227
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL106-.LVL85
	.uleb128 .LVL110-.LVL85
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2227
	.sleb128 0
	.byte	0
.LLST54:
	.byte	0x6
	.4byte	.LVL85
	.byte	0x4
	.uleb128 .LVL85-.LVL85
	.uleb128 .LVL86-.LVL85
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL94-.LVL85
	.uleb128 .LVL95-.LVL85
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL95-.LVL85
	.uleb128 .LVL97-.LVL85
	.uleb128 0x4
	.byte	0x79
	.sleb128 -2047
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL106-.LVL85
	.uleb128 .LVL107-.LVL85
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL107-.LVL85
	.uleb128 .LVL109-.LVL85
	.uleb128 0x4
	.byte	0x79
	.sleb128 2048
	.byte	0x9f
	.byte	0
.LLST56:
	.byte	0x6
	.4byte	.LVL87
	.byte	0x4
	.uleb128 .LVL87-.LVL87
	.uleb128 .LVL90-.LVL87
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL100-.LVL87
	.uleb128 .LVL103-1-.LVL87
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL110-.LVL87
	.uleb128 .LVL112-1-.LVL87
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST57:
	.byte	0x6
	.4byte	.LVL87
	.byte	0x4
	.uleb128 .LVL87-.LVL87
	.uleb128 .LVL89-.LVL87
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL100-.LVL87
	.uleb128 .LVL102-.LVL87
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL102-.LVL87
	.uleb128 .LVL104-.LVL87
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL110-.LVL87
	.uleb128 .LVL111-.LVL87
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL111-.LVL87
	.uleb128 .LFE21-.LVL87
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0
.LLST58:
	.byte	0x6
	.4byte	.LVL87
	.byte	0x4
	.uleb128 .LVL87-.LVL87
	.uleb128 .LVL90-.LVL87
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2243
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL100-.LVL87
	.uleb128 .LVL105-.LVL87
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2243
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL110-.LVL87
	.uleb128 .LFE21-.LVL87
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2243
	.sleb128 0
	.byte	0
.LLST59:
	.byte	0x6
	.4byte	.LVL87
	.byte	0x4
	.uleb128 .LVL87-.LVL87
	.uleb128 .LVL90-.LVL87
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL100-.LVL87
	.uleb128 .LVL102-.LVL87
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL102-.LVL87
	.uleb128 .LVL103-1-.LVL87
	.uleb128 0x4
	.byte	0x7e
	.sleb128 -2047
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL110-.LVL87
	.uleb128 .LVL111-.LVL87
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL111-.LVL87
	.uleb128 .LVL112-1-.LVL87
	.uleb128 0x4
	.byte	0x7e
	.sleb128 2048
	.byte	0x9f
	.byte	0
.LLST29:
	.byte	0x6
	.4byte	.LVL51
	.byte	0x4
	.uleb128 .LVL51-.LVL51
	.uleb128 .LVL52-.LVL51
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL52-.LVL51
	.uleb128 .LVL56-.LVL51
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL56-.LVL51
	.uleb128 .LVL64-.LVL51
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
	.uleb128 .LVL64-.LVL51
	.uleb128 .LVL66-1-.LVL51
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL66-1-.LVL51
	.uleb128 .LVL71-.LVL51
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL71-.LVL51
	.uleb128 .LVL75-.LVL51
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
	.uleb128 .LVL75-.LVL51
	.uleb128 .LVL76-1-.LVL51
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL76-1-.LVL51
	.uleb128 .LVL76-.LVL51
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
	.uleb128 .LVL76-.LVL51
	.uleb128 .LVL78-1-.LVL51
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL78-1-.LVL51
	.uleb128 .LVL80-.LVL51
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL80-.LVL51
	.uleb128 .LFE20-.LVL51
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
.LLST31:
	.byte	0x6
	.4byte	.LVL66
	.byte	0x4
	.uleb128 .LVL66-.LVL66
	.uleb128 .LVL68-.LVL66
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL78-.LVL66
	.uleb128 .LVL80-.LVL66
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0
.LLST32:
	.byte	0x6
	.4byte	.LVL73
	.byte	0x4
	.uleb128 .LVL73-.LVL73
	.uleb128 .LVL74-.LVL73
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL82-.LVL73
	.uleb128 .LFE20-.LVL73
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0
.LLST45:
	.byte	0x6
	.4byte	.LVL59
	.byte	0x4
	.uleb128 .LVL59-.LVL59
	.uleb128 .LVL60-.LVL59
	.uleb128 0x24
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
	.byte	0x76
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL60-.LVL59
	.uleb128 .LVL61-.LVL59
	.uleb128 0x22
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
	.byte	0x76
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL61-.LVL59
	.uleb128 .LVL62-.LVL59
	.uleb128 0x24
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
	.byte	0x76
	.sleb128 0
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST34:
	.byte	0x6
	.4byte	.LVL53
	.byte	0x4
	.uleb128 .LVL53-.LVL53
	.uleb128 .LVL54-.LVL53
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL64-.LVL53
	.uleb128 .LVL66-1-.LVL53
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL76-.LVL53
	.uleb128 .LVL78-1-.LVL53
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST35:
	.byte	0x6
	.4byte	.LVL53
	.byte	0x4
	.uleb128 .LVL53-.LVL53
	.uleb128 .LVL54-.LVL53
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL64-.LVL53
	.uleb128 .LVL65-.LVL53
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL65-.LVL53
	.uleb128 .LVL68-.LVL53
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL76-.LVL53
	.uleb128 .LVL77-.LVL53
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL77-.LVL53
	.uleb128 .LVL80-.LVL53
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0
.LLST36:
	.byte	0x6
	.4byte	.LVL53
	.byte	0x4
	.uleb128 .LVL53-.LVL53
	.uleb128 .LVL54-.LVL53
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2580
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL64-.LVL53
	.uleb128 .LVL69-.LVL53
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2580
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL76-.LVL53
	.uleb128 .LVL80-.LVL53
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2580
	.sleb128 0
	.byte	0
.LLST37:
	.byte	0x6
	.4byte	.LVL53
	.byte	0x4
	.uleb128 .LVL53-.LVL53
	.uleb128 .LVL54-.LVL53
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL64-.LVL53
	.uleb128 .LVL65-.LVL53
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL65-.LVL53
	.uleb128 .LVL67-.LVL53
	.uleb128 0x4
	.byte	0x79
	.sleb128 -2047
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL76-.LVL53
	.uleb128 .LVL77-.LVL53
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL77-.LVL53
	.uleb128 .LVL79-.LVL53
	.uleb128 0x4
	.byte	0x79
	.sleb128 2048
	.byte	0x9f
	.byte	0
.LLST39:
	.byte	0x6
	.4byte	.LVL55
	.byte	0x4
	.uleb128 .LVL55-.LVL55
	.uleb128 .LVL58-.LVL55
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL70-.LVL55
	.uleb128 .LVL73-1-.LVL55
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL80-.LVL55
	.uleb128 .LVL82-1-.LVL55
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST40:
	.byte	0x6
	.4byte	.LVL55
	.byte	0x4
	.uleb128 .LVL55-.LVL55
	.uleb128 .LVL57-.LVL55
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL70-.LVL55
	.uleb128 .LVL72-.LVL55
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL72-.LVL55
	.uleb128 .LVL74-.LVL55
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL80-.LVL55
	.uleb128 .LVL81-.LVL55
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL81-.LVL55
	.uleb128 .LFE20-.LVL55
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0
.LLST41:
	.byte	0x6
	.4byte	.LVL55
	.byte	0x4
	.uleb128 .LVL55-.LVL55
	.uleb128 .LVL58-.LVL55
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2596
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL70-.LVL55
	.uleb128 .LVL75-.LVL55
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2596
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL80-.LVL55
	.uleb128 .LFE20-.LVL55
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+2596
	.sleb128 0
	.byte	0
.LLST42:
	.byte	0x6
	.4byte	.LVL55
	.byte	0x4
	.uleb128 .LVL55-.LVL55
	.uleb128 .LVL58-.LVL55
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL70-.LVL55
	.uleb128 .LVL72-.LVL55
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL72-.LVL55
	.uleb128 .LVL73-1-.LVL55
	.uleb128 0x4
	.byte	0x7d
	.sleb128 -2047
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL80-.LVL55
	.uleb128 .LVL81-.LVL55
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL81-.LVL55
	.uleb128 .LVL82-1-.LVL55
	.uleb128 0x4
	.byte	0x7d
	.sleb128 2048
	.byte	0x9f
	.byte	0
.LLST24:
	.byte	0x6
	.4byte	.LVL46
	.byte	0x4
	.uleb128 .LVL46-.LVL46
	.uleb128 .LVL47-.LVL46
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL47-.LVL46
	.uleb128 .LVL49-.LVL46
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
	.uleb128 .LVL49-.LVL46
	.uleb128 .LVL50-1-.LVL46
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL50-1-.LVL46
	.uleb128 .LFE19-.LVL46
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
.LLST26:
	.byte	0x8
	.4byte	.LVL48
	.uleb128 .LVL49-.LVL48
	.uleb128 0x41
	.byte	0x3
	.4byte	g_vCtrl_x
	.byte	0x6
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
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x23
	.uleb128 0x10
	.byte	0x6
	.byte	0x35
	.byte	0x24
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
	.uleb128 0x4
	.byte	0x6
	.byte	0x21
	.byte	0x38
	.byte	0x24
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x21
	.byte	0x3
	.4byte	g_vCtrl_x
	.byte	0x6
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
.LLST28:
	.byte	0x8
	.4byte	.LVL48
	.uleb128 .LVL49-.LVL48
	.uleb128 0x18
	.byte	0x3
	.4byte	g_vCtrl_y
	.byte	0x6
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x7b
	.sleb128 0
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST0:
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
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL4-.LVL1
	.uleb128 .LVL5-.LVL1
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
	.uleb128 .LVL5-.LVL1
	.uleb128 .LVL10-.LVL1
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL10-.LVL1
	.uleb128 .LVL11-.LVL1
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
	.uleb128 .LVL11-.LVL1
	.uleb128 .LFE17-.LVL1
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL5-.LVL1
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL5-.LVL1
	.uleb128 .LVL9-.LVL1
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL11-.LVL1
	.uleb128 .LFE17-.LVL1
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL6-.LVL1
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL6-.LVL1
	.uleb128 .LVL8-1-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL8-1-.LVL1
	.uleb128 .LVL11-.LVL1
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
	.uleb128 .LVL11-.LVL1
	.uleb128 .LVL13-1-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL13-1-.LVL1
	.uleb128 .LFE17-.LVL1
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
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL5-.LVL2
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.LVL2
	.uleb128 .LVL7-.LVL2
	.uleb128 0x4
	.byte	0x7b
	.sleb128 2048
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL7-.LVL2
	.uleb128 .LVL9-.LVL2
	.uleb128 0xd
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x23
	.uleb128 0x800
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL11-.LVL2
	.uleb128 .LVL12-.LVL2
	.uleb128 0x4
	.byte	0x7b
	.sleb128 -2047
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL12-.LVL2
	.uleb128 .LFE17-.LVL2
	.uleb128 0xe
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0xa
	.2byte	0x7ff
	.byte	0x1c
	.byte	0x9f
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL14
	.byte	0x4
	.uleb128 .LVL14-.LVL14
	.uleb128 .LVL15-.LVL14
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL15-.LVL14
	.uleb128 .LVL20-.LVL14
	.uleb128 0x6
	.byte	0x7e
	.sleb128 0
	.byte	0x8
	.byte	0x3f
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL20-.LVL14
	.uleb128 .LVL21-.LVL14
	.uleb128 0xb
	.byte	0x3
	.4byte	outgoing_report+8
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0x3f
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL22-.LVL14
	.uleb128 .LVL23-.LVL14
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL23-.LVL14
	.uleb128 .LVL24-.LVL14
	.uleb128 0xb
	.byte	0x3
	.4byte	outgoing_report+8
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0x3f
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL25-.LVL14
	.uleb128 .LVL27-.LVL14
	.uleb128 0xb
	.byte	0x3
	.4byte	outgoing_report+8
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0x3f
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL39-.LVL14
	.uleb128 .LVL41-1-.LVL14
	.uleb128 0xb
	.byte	0x3
	.4byte	outgoing_report+8
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0x3f
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL45-.LVL14
	.uleb128 .LFE18-.LVL14
	.uleb128 0xb
	.byte	0x3
	.4byte	outgoing_report+8
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0x3f
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL16
	.byte	0x4
	.uleb128 .LVL16-.LVL16
	.uleb128 .LVL17-.LVL16
	.uleb128 0x1e
	.byte	0x7d
	.sleb128 0
	.byte	0x40
	.byte	0x24
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x7d
	.sleb128 0
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	outgoing_report+1
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x38
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL17-.LVL16
	.uleb128 .LVL18-.LVL16
	.uleb128 0x2c
	.byte	0x3
	.4byte	g_vCtrl_x
	.byte	0x6
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
	.byte	0x3
	.4byte	g_vCtrl_x
	.byte	0x6
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0x38
	.byte	0x26
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	outgoing_report+1
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x38
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL18-.LVL16
	.uleb128 .LVL22-.LVL16
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST8:
	.byte	0x8
	.4byte	.LVL19
	.uleb128 .LVL22-.LVL19
	.uleb128 0x1b
	.byte	0x3
	.4byte	g_vCtrl_y
	.byte	0x6
	.byte	0x23
	.uleb128 0x4
	.byte	0x6
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x3
	.4byte	sn_num
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x40
	.byte	0x24
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST9:
	.byte	0x8
	.4byte	.LVL42
	.uleb128 .LVL43-.LVL42
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0
.LLST10:
	.byte	0x8
	.4byte	.LVL44
	.uleb128 .LVL45-.LVL44
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL27-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL39-.LVL26
	.uleb128 .LVL41-1-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL45-.LVL26
	.uleb128 .LFE18-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL27-.LVL26
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL39-.LVL26
	.uleb128 .LVL40-.LVL26
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL42-.LVL26
	.uleb128 .LVL43-.LVL26
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL45-.LVL26
	.uleb128 .LFE18-.LVL26
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL27-.LVL26
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+3433
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL39-.LVL26
	.uleb128 .LVL43-.LVL26
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+3433
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL45-.LVL26
	.uleb128 .LFE18-.LVL26
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+3433
	.sleb128 0
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL27-.LVL26
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL39-.LVL26
	.uleb128 .LVL40-.LVL26
	.uleb128 0x4
	.byte	0x7e
	.sleb128 2048
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL45-.LVL26
	.uleb128 .LFE18-.LVL26
	.uleb128 0x4
	.byte	0x7e
	.sleb128 -2047
	.byte	0x9f
	.byte	0
.LLST17:
	.byte	0x6
	.4byte	.LVL28
	.byte	0x4
	.uleb128 .LVL28-.LVL28
	.uleb128 .LVL29-.LVL28
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL36-.LVL28
	.uleb128 .LVL37-1-.LVL28
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL43-.LVL28
	.uleb128 .LVL44-1-.LVL28
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST18:
	.byte	0x6
	.4byte	.LVL28
	.byte	0x4
	.uleb128 .LVL28-.LVL28
	.uleb128 .LVL29-.LVL28
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL36-.LVL28
	.uleb128 .LVL38-.LVL28
	.uleb128 0x4
	.byte	0xb
	.2byte	0xf800
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL43-.LVL28
	.uleb128 .LVL45-.LVL28
	.uleb128 0x4
	.byte	0xa
	.2byte	0x7ff
	.byte	0x9f
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL28
	.byte	0x4
	.uleb128 .LVL28-.LVL28
	.uleb128 .LVL29-.LVL28
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+3442
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL36-.LVL28
	.uleb128 .LVL39-.LVL28
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+3442
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL43-.LVL28
	.uleb128 .LVL45-.LVL28
	.uleb128 0x6
	.byte	0xa0
	.4byte	.Ldebug_info0+3442
	.sleb128 0
	.byte	0
.LLST20:
	.byte	0x6
	.4byte	.LVL28
	.byte	0x4
	.uleb128 .LVL28-.LVL28
	.uleb128 .LVL29-.LVL28
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL36-.LVL28
	.uleb128 .LVL37-1-.LVL28
	.uleb128 0x4
	.byte	0x7d
	.sleb128 2048
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL43-.LVL28
	.uleb128 .LVL44-1-.LVL28
	.uleb128 0x4
	.byte	0x7d
	.sleb128 -2047
	.byte	0x9f
	.byte	0
.LLST22:
	.byte	0x6
	.4byte	.LVL29
	.byte	0x4
	.uleb128 .LVL29-.LVL29
	.uleb128 .LVL30-.LVL29
	.uleb128 0x32
	.byte	0x3
	.4byte	outgoing_report+1
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x38
	.byte	0x24
	.byte	0x3
	.4byte	outgoing_report+2
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x40
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	outgoing_report+3
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	sn_num
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL30-.LVL29
	.uleb128 .LVL31-.LVL29
	.uleb128 0x2a
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0x3
	.4byte	outgoing_report+2
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x40
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	outgoing_report+3
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	sn_num
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL31-.LVL29
	.uleb128 .LVL32-.LVL29
	.uleb128 0x22
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0x75
	.sleb128 0
	.byte	0x40
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	outgoing_report+3
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	sn_num
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL32-.LVL29
	.uleb128 .LVL33-.LVL29
	.uleb128 0x2a
	.byte	0x7e
	.sleb128 0
	.byte	0x38
	.byte	0x24
	.byte	0x3
	.4byte	outgoing_report+2
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x40
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	outgoing_report+3
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	sn_num
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL33-.LVL29
	.uleb128 .LVL34-.LVL29
	.uleb128 0x32
	.byte	0x3
	.4byte	outgoing_report+1
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x38
	.byte	0x24
	.byte	0x3
	.4byte	outgoing_report+2
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x40
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	outgoing_report+3
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x48
	.byte	0x24
	.byte	0x21
	.byte	0x3
	.4byte	sn_num
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x21
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
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
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
	.4byte	.LBB28
	.byte	0x4
	.uleb128 .LBB28-.LBB28
	.uleb128 .LBE28-.LBB28
	.byte	0x4
	.uleb128 .LBB30-.LBB28
	.uleb128 .LBE30-.LBB28
	.byte	0x4
	.uleb128 .LBB32-.LBB28
	.uleb128 .LBE32-.LBB28
	.byte	0x4
	.uleb128 .LBB34-.LBB28
	.uleb128 .LBE34-.LBB28
	.byte	0x4
	.uleb128 .LBB36-.LBB28
	.uleb128 .LBE36-.LBB28
	.byte	0
.LLRL7:
	.byte	0x5
	.4byte	.LBB29
	.byte	0x4
	.uleb128 .LBB29-.LBB29
	.uleb128 .LBE29-.LBB29
	.byte	0x4
	.uleb128 .LBB31-.LBB29
	.uleb128 .LBE31-.LBB29
	.byte	0x4
	.uleb128 .LBB33-.LBB29
	.uleb128 .LBE33-.LBB29
	.byte	0x4
	.uleb128 .LBB35-.LBB29
	.uleb128 .LBE35-.LBB29
	.byte	0x4
	.uleb128 .LBB37-.LBB29
	.uleb128 .LBE37-.LBB29
	.byte	0
.LLRL11:
	.byte	0x5
	.4byte	.LBB41
	.byte	0x4
	.uleb128 .LBB41-.LBB41
	.uleb128 .LBE41-.LBB41
	.byte	0x4
	.uleb128 .LBB46-.LBB41
	.uleb128 .LBE46-.LBB41
	.byte	0x4
	.uleb128 .LBB77-.LBB41
	.uleb128 .LBE77-.LBB41
	.byte	0x4
	.uleb128 .LBB79-.LBB41
	.uleb128 .LBE79-.LBB41
	.byte	0
.LLRL16:
	.byte	0x5
	.4byte	.LBB47
	.byte	0x4
	.uleb128 .LBB47-.LBB47
	.uleb128 .LBE47-.LBB47
	.byte	0x4
	.uleb128 .LBB53-.LBB47
	.uleb128 .LBE53-.LBB47
	.byte	0x4
	.uleb128 .LBB73-.LBB47
	.uleb128 .LBE73-.LBB47
	.byte	0x4
	.uleb128 .LBB75-.LBB47
	.uleb128 .LBE75-.LBB47
	.byte	0x4
	.uleb128 .LBB78-.LBB47
	.uleb128 .LBE78-.LBB47
	.byte	0
.LLRL21:
	.byte	0x5
	.4byte	.LBB54
	.byte	0x4
	.uleb128 .LBB54-.LBB54
	.uleb128 .LBE54-.LBB54
	.byte	0x4
	.uleb128 .LBB56-.LBB54
	.uleb128 .LBE56-.LBB54
	.byte	0x4
	.uleb128 .LBB58-.LBB54
	.uleb128 .LBE58-.LBB54
	.byte	0x4
	.uleb128 .LBB60-.LBB54
	.uleb128 .LBE60-.LBB54
	.byte	0x4
	.uleb128 .LBB62-.LBB54
	.uleb128 .LBE62-.LBB54
	.byte	0x4
	.uleb128 .LBB64-.LBB54
	.uleb128 .LBE64-.LBB54
	.byte	0x4
	.uleb128 .LBB66-.LBB54
	.uleb128 .LBE66-.LBB54
	.byte	0x4
	.uleb128 .LBB68-.LBB54
	.uleb128 .LBE68-.LBB54
	.byte	0x4
	.uleb128 .LBB70-.LBB54
	.uleb128 .LBE70-.LBB54
	.byte	0x4
	.uleb128 .LBB71-.LBB54
	.uleb128 .LBE71-.LBB54
	.byte	0
.LLRL23:
	.byte	0x5
	.4byte	.LBB55
	.byte	0x4
	.uleb128 .LBB55-.LBB55
	.uleb128 .LBE55-.LBB55
	.byte	0x4
	.uleb128 .LBB57-.LBB55
	.uleb128 .LBE57-.LBB55
	.byte	0x4
	.uleb128 .LBB59-.LBB55
	.uleb128 .LBE59-.LBB55
	.byte	0x4
	.uleb128 .LBB61-.LBB55
	.uleb128 .LBE61-.LBB55
	.byte	0x4
	.uleb128 .LBB63-.LBB55
	.uleb128 .LBE63-.LBB55
	.byte	0x4
	.uleb128 .LBB65-.LBB55
	.uleb128 .LBE65-.LBB55
	.byte	0x4
	.uleb128 .LBB67-.LBB55
	.uleb128 .LBE67-.LBB55
	.byte	0x4
	.uleb128 .LBB69-.LBB55
	.uleb128 .LBE69-.LBB55
	.byte	0x4
	.uleb128 .LBB72-.LBB55
	.uleb128 .LBE72-.LBB55
	.byte	0x4
	.uleb128 .LBB74-.LBB55
	.uleb128 .LBE74-.LBB55
	.byte	0x4
	.uleb128 .LBB76-.LBB55
	.uleb128 .LBE76-.LBB55
	.byte	0
.LLRL25:
	.byte	0x5
	.4byte	.LBB80
	.byte	0x4
	.uleb128 .LBB80-.LBB80
	.uleb128 .LBE80-.LBB80
	.byte	0x4
	.uleb128 .LBB82-.LBB80
	.uleb128 .LBE82-.LBB80
	.byte	0x4
	.uleb128 .LBB84-.LBB80
	.uleb128 .LBE84-.LBB80
	.byte	0x4
	.uleb128 .LBB85-.LBB80
	.uleb128 .LBE85-.LBB80
	.byte	0x4
	.uleb128 .LBB87-.LBB80
	.uleb128 .LBE87-.LBB80
	.byte	0x4
	.uleb128 .LBB89-.LBB80
	.uleb128 .LBE89-.LBB80
	.byte	0x4
	.uleb128 .LBB91-.LBB80
	.uleb128 .LBE91-.LBB80
	.byte	0x4
	.uleb128 .LBB92-.LBB80
	.uleb128 .LBE92-.LBB80
	.byte	0
.LLRL27:
	.byte	0x5
	.4byte	.LBB81
	.byte	0x4
	.uleb128 .LBB81-.LBB81
	.uleb128 .LBE81-.LBB81
	.byte	0x4
	.uleb128 .LBB83-.LBB81
	.uleb128 .LBE83-.LBB81
	.byte	0x4
	.uleb128 .LBB86-.LBB81
	.uleb128 .LBE86-.LBB81
	.byte	0x4
	.uleb128 .LBB88-.LBB81
	.uleb128 .LBE88-.LBB81
	.byte	0x4
	.uleb128 .LBB90-.LBB81
	.uleb128 .LBE90-.LBB81
	.byte	0x4
	.uleb128 .LBB93-.LBB81
	.uleb128 .LBE93-.LBB81
	.byte	0
.LLRL30:
	.byte	0x5
	.4byte	.LBB101
	.byte	0x4
	.uleb128 .LBB101-.LBB101
	.uleb128 .LBE101-.LBB101
	.byte	0x4
	.uleb128 .LBB134-.LBB101
	.uleb128 .LBE134-.LBB101
	.byte	0x4
	.uleb128 .LBB135-.LBB101
	.uleb128 .LBE135-.LBB101
	.byte	0x4
	.uleb128 .LBB136-.LBB101
	.uleb128 .LBE136-.LBB101
	.byte	0x4
	.uleb128 .LBB137-.LBB101
	.uleb128 .LBE137-.LBB101
	.byte	0x4
	.uleb128 .LBB138-.LBB101
	.uleb128 .LBE138-.LBB101
	.byte	0x4
	.uleb128 .LBB139-.LBB101
	.uleb128 .LBE139-.LBB101
	.byte	0
.LLRL33:
	.byte	0x5
	.4byte	.LBB102
	.byte	0x4
	.uleb128 .LBB102-.LBB102
	.uleb128 .LBE102-.LBB102
	.byte	0x4
	.uleb128 .LBB107-.LBB102
	.uleb128 .LBE107-.LBB102
	.byte	0x4
	.uleb128 .LBB128-.LBB102
	.uleb128 .LBE128-.LBB102
	.byte	0x4
	.uleb128 .LBB132-.LBB102
	.uleb128 .LBE132-.LBB102
	.byte	0
.LLRL38:
	.byte	0x5
	.4byte	.LBB108
	.byte	0x4
	.uleb128 .LBB108-.LBB108
	.uleb128 .LBE108-.LBB108
	.byte	0x4
	.uleb128 .LBB116-.LBB108
	.uleb128 .LBE116-.LBB108
	.byte	0x4
	.uleb128 .LBB118-.LBB108
	.uleb128 .LBE118-.LBB108
	.byte	0x4
	.uleb128 .LBB129-.LBB108
	.uleb128 .LBE129-.LBB108
	.byte	0x4
	.uleb128 .LBB131-.LBB108
	.uleb128 .LBE131-.LBB108
	.byte	0x4
	.uleb128 .LBB133-.LBB108
	.uleb128 .LBE133-.LBB108
	.byte	0
.LLRL43:
	.byte	0x5
	.4byte	.LBB115
	.byte	0x4
	.uleb128 .LBB115-.LBB115
	.uleb128 .LBE115-.LBB115
	.byte	0x4
	.uleb128 .LBB117-.LBB115
	.uleb128 .LBE117-.LBB115
	.byte	0x4
	.uleb128 .LBB119-.LBB115
	.uleb128 .LBE119-.LBB115
	.byte	0x4
	.uleb128 .LBB121-.LBB115
	.uleb128 .LBE121-.LBB115
	.byte	0x4
	.uleb128 .LBB123-.LBB115
	.uleb128 .LBE123-.LBB115
	.byte	0x4
	.uleb128 .LBB125-.LBB115
	.uleb128 .LBE125-.LBB115
	.byte	0x4
	.uleb128 .LBB127-.LBB115
	.uleb128 .LBE127-.LBB115
	.byte	0x4
	.uleb128 .LBB130-.LBB115
	.uleb128 .LBE130-.LBB115
	.byte	0
.LLRL44:
	.byte	0x5
	.4byte	.LBB120
	.byte	0x4
	.uleb128 .LBB120-.LBB120
	.uleb128 .LBE120-.LBB120
	.byte	0x4
	.uleb128 .LBB122-.LBB120
	.uleb128 .LBE122-.LBB120
	.byte	0x4
	.uleb128 .LBB124-.LBB120
	.uleb128 .LBE124-.LBB120
	.byte	0x4
	.uleb128 .LBB126-.LBB120
	.uleb128 .LBE126-.LBB120
	.byte	0
.LLRL47:
	.byte	0x5
	.4byte	.LBB147
	.byte	0x4
	.uleb128 .LBB147-.LBB147
	.uleb128 .LBE147-.LBB147
	.byte	0x4
	.uleb128 .LBB182-.LBB147
	.uleb128 .LBE182-.LBB147
	.byte	0x4
	.uleb128 .LBB183-.LBB147
	.uleb128 .LBE183-.LBB147
	.byte	0x4
	.uleb128 .LBB184-.LBB147
	.uleb128 .LBE184-.LBB147
	.byte	0x4
	.uleb128 .LBB185-.LBB147
	.uleb128 .LBE185-.LBB147
	.byte	0x4
	.uleb128 .LBB186-.LBB147
	.uleb128 .LBE186-.LBB147
	.byte	0x4
	.uleb128 .LBB187-.LBB147
	.uleb128 .LBE187-.LBB147
	.byte	0
.LLRL50:
	.byte	0x5
	.4byte	.LBB148
	.byte	0x4
	.uleb128 .LBB148-.LBB148
	.uleb128 .LBE148-.LBB148
	.byte	0x4
	.uleb128 .LBB154-.LBB148
	.uleb128 .LBE154-.LBB148
	.byte	0x4
	.uleb128 .LBB175-.LBB148
	.uleb128 .LBE175-.LBB148
	.byte	0x4
	.uleb128 .LBB176-.LBB148
	.uleb128 .LBE176-.LBB148
	.byte	0x4
	.uleb128 .LBB180-.LBB148
	.uleb128 .LBE180-.LBB148
	.byte	0
.LLRL55:
	.byte	0x5
	.4byte	.LBB155
	.byte	0x4
	.uleb128 .LBB155-.LBB155
	.uleb128 .LBE155-.LBB155
	.byte	0x4
	.uleb128 .LBB163-.LBB155
	.uleb128 .LBE163-.LBB155
	.byte	0x4
	.uleb128 .LBB165-.LBB155
	.uleb128 .LBE165-.LBB155
	.byte	0x4
	.uleb128 .LBB177-.LBB155
	.uleb128 .LBE177-.LBB155
	.byte	0x4
	.uleb128 .LBB179-.LBB155
	.uleb128 .LBE179-.LBB155
	.byte	0x4
	.uleb128 .LBB181-.LBB155
	.uleb128 .LBE181-.LBB155
	.byte	0
.LLRL60:
	.byte	0x5
	.4byte	.LBB162
	.byte	0x4
	.uleb128 .LBB162-.LBB162
	.uleb128 .LBE162-.LBB162
	.byte	0x4
	.uleb128 .LBB164-.LBB162
	.uleb128 .LBE164-.LBB162
	.byte	0x4
	.uleb128 .LBB166-.LBB162
	.uleb128 .LBE166-.LBB162
	.byte	0x4
	.uleb128 .LBB168-.LBB162
	.uleb128 .LBE168-.LBB162
	.byte	0x4
	.uleb128 .LBB170-.LBB162
	.uleb128 .LBE170-.LBB162
	.byte	0x4
	.uleb128 .LBB172-.LBB162
	.uleb128 .LBE172-.LBB162
	.byte	0x4
	.uleb128 .LBB174-.LBB162
	.uleb128 .LBE174-.LBB162
	.byte	0x4
	.uleb128 .LBB178-.LBB162
	.uleb128 .LBE178-.LBB162
	.byte	0
.LLRL61:
	.byte	0x5
	.4byte	.LBB167
	.byte	0x4
	.uleb128 .LBB167-.LBB167
	.uleb128 .LBE167-.LBB167
	.byte	0x4
	.uleb128 .LBB169-.LBB167
	.uleb128 .LBE169-.LBB167
	.byte	0x4
	.uleb128 .LBB171-.LBB167
	.uleb128 .LBE171-.LBB167
	.byte	0x4
	.uleb128 .LBB173-.LBB167
	.uleb128 .LBE173-.LBB167
	.byte	0
.LLRL67:
	.byte	0x5
	.4byte	.LBB190
	.byte	0x4
	.uleb128 .LBB190-.LBB190
	.uleb128 .LBE190-.LBB190
	.byte	0x4
	.uleb128 .LBB193-.LBB190
	.uleb128 .LBE193-.LBB190
	.byte	0
.LLRL69:
	.byte	0x5
	.4byte	.LBB194
	.byte	0x4
	.uleb128 .LBB194-.LBB194
	.uleb128 .LBE194-.LBB194
	.byte	0x4
	.uleb128 .LBB195-.LBB194
	.uleb128 .LBE195-.LBB194
	.byte	0x4
	.uleb128 .LBB196-.LBB194
	.uleb128 .LBE196-.LBB194
	.byte	0x4
	.uleb128 .LBB198-.LBB194
	.uleb128 .LBE198-.LBB194
	.byte	0x4
	.uleb128 .LBB199-.LBB194
	.uleb128 .LBE199-.LBB194
	.byte	0
.LLRL71:
	.byte	0x5
	.4byte	.LBB197
	.byte	0x4
	.uleb128 .LBB197-.LBB197
	.uleb128 .LBE197-.LBB197
	.byte	0x4
	.uleb128 .LBB200-.LBB197
	.uleb128 .LBE200-.LBB197
	.byte	0
.LLRL74:
	.byte	0x5
	.4byte	.LBB201
	.byte	0x4
	.uleb128 .LBB201-.LBB201
	.uleb128 .LBE201-.LBB201
	.byte	0x4
	.uleb128 .LBB203-.LBB201
	.uleb128 .LBE203-.LBB201
	.byte	0x4
	.uleb128 .LBB205-.LBB201
	.uleb128 .LBE205-.LBB201
	.byte	0x4
	.uleb128 .LBB207-.LBB201
	.uleb128 .LBE207-.LBB201
	.byte	0x4
	.uleb128 .LBB209-.LBB201
	.uleb128 .LBE209-.LBB201
	.byte	0x4
	.uleb128 .LBB211-.LBB201
	.uleb128 .LBE211-.LBB201
	.byte	0
.LLRL76:
	.byte	0x5
	.4byte	.LBB202
	.byte	0x4
	.uleb128 .LBB202-.LBB202
	.uleb128 .LBE202-.LBB202
	.byte	0x4
	.uleb128 .LBB204-.LBB202
	.uleb128 .LBE204-.LBB202
	.byte	0x4
	.uleb128 .LBB206-.LBB202
	.uleb128 .LBE206-.LBB202
	.byte	0x4
	.uleb128 .LBB208-.LBB202
	.uleb128 .LBE208-.LBB202
	.byte	0x4
	.uleb128 .LBB210-.LBB202
	.uleb128 .LBE210-.LBB202
	.byte	0x4
	.uleb128 .LBB212-.LBB202
	.uleb128 .LBE212-.LBB202
	.byte	0
.LLRL82:
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
	.byte	0x7
	.4byte	.LFB28
	.uleb128 .LFE28-.LFB28
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF58:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF81:
	.string	"hid_express_generate_value_candidate_1R1T_concurrent"
.LASF83:
	.string	"outgoing"
.LASF50:
	.string	"T_HID_2_4G_REPORT_KB_CONSUMER2_S"
.LASF48:
	.string	"T_HID_MOUSE_2_4G_REPORT_K8_S16_Z8"
.LASF107:
	.string	"hid_express_gaming_submit_report_to_pka"
.LASF103:
	.string	"pka_share_get_tx_datalen_offset"
.LASF75:
	.string	"last_xy_over_12bits"
.LASF95:
	.string	"report_id_of_submitted_report"
.LASF79:
	.string	"outgoing_report"
.LASF85:
	.string	"dongle_scenario"
.LASF59:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF73:
	.string	"g_vCtrl_x"
.LASF74:
	.string	"g_vCtrl_y"
.LASF88:
	.string	"temp"
.LASF51:
	.string	"type"
.LASF91:
	.string	"hid_express_2_4G_x_y_data_prepare"
.LASF33:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF43:
	.string	"consumer"
.LASF61:
	.string	"tx_n"
.LASF100:
	.string	"hid_express_gaming_get_tx_status"
.LASF92:
	.string	"hid_express_gaming_generate_kb_consumer_xy_reports_1R1T"
.LASF45:
	.string	"T_HID_2_4G_REPORT_KB_CONSUMER1_XY_S"
.LASF22:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF23:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF6:
	.string	"short int"
.LASF39:
	.string	"keycode"
.LASF35:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF13:
	.string	"int8_t"
.LASF16:
	.string	"uint8_t"
.LASF19:
	.string	"DBG_PIN_SPI_CB"
.LASF57:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF82:
	.string	"tx_result"
.LASF62:
	.string	"predict_n"
.LASF96:
	.string	"hid_express_gaming_axis_data_update"
.LASF11:
	.string	"long double"
.LASF10:
	.string	"long long int"
.LASF12:
	.string	"char"
.LASF47:
	.string	"ac_pan"
.LASF8:
	.string	"long int"
.LASF32:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF25:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF80:
	.string	"hid_express_x_y_buf_init"
.LASF101:
	.string	"pka_share_get_hid_tx_ptr"
.LASF65:
	.string	"rr_idx_2_4g"
.LASF44:
	.string	"numeric_key_pad"
.LASF104:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF69:
	.string	"kb_std2"
.LASF90:
	.string	"hid_express_gaming_data_send"
.LASF5:
	.string	"unsigned char"
.LASF71:
	.string	"kb_std5"
.LASF40:
	.string	"dummy_1"
.LASF37:
	.string	"dummy_2"
.LASF78:
	.string	"reliable_tx_ptr_previous"
.LASF38:
	.string	"combo"
.LASF4:
	.string	"signed char"
.LASF54:
	.string	"kb_consumer"
.LASF2:
	.string	"long long unsigned int"
.LASF18:
	.string	"uint32_t"
.LASF3:
	.string	"unsigned int"
.LASF29:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF63:
	.string	"untransmitted_value"
.LASF89:
	.string	"hid_express_gaming_generate_kb_consumer_reports_1R1T"
.LASF52:
	.string	"k_old"
.LASF56:
	.string	"u32_may_alias_t"
.LASF97:
	.string	"axis12"
.LASF26:
	.string	"DBG_PIN_USB_TX"
.LASF55:
	.string	"T_OUTGOING_VALUES_S"
.LASF60:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF7:
	.string	"short unsigned int"
.LASF20:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF53:
	.string	"kb_std"
.LASF17:
	.string	"uint16_t"
.LASF15:
	.string	"int32_t"
.LASF66:
	.string	"sn_num"
.LASF99:
	.string	"overflow"
.LASF14:
	.string	"int16_t"
.LASF102:
	.string	"pka_share_get_tx_pdulen_offset"
.LASF28:
	.string	"_Bool"
.LASF49:
	.string	"T_HID_2_4G_REPORT_KB_STD5_S"
.LASF93:
	.string	"hid_express_gaming_generate_kb_std_xy_reports_1R1T"
.LASF42:
	.string	"T_HID_2_4G_REPORT_KB_STD2_XY_S"
.LASF31:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF84:
	.string	"tx_idx"
.LASF9:
	.string	"long unsigned int"
.LASF98:
	.string	"ctrl"
.LASF106:
	.string	"hid_express_gaming_init"
.LASF67:
	.string	"ms_s16_z8"
.LASF34:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF24:
	.string	"DBG_PIN_USB_SOF"
.LASF30:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF108:
	.string	"hid_express_gaming_buffer_full_update_report"
.LASF94:
	.string	"hid_express_gaming_generate_reports_1R1T_12bits"
.LASF87:
	.string	"hid_express_gaming_generate_kb_std_reports_1R1T"
.LASF41:
	.string	"report_id"
.LASF72:
	.string	"U_CCNI_REPORT"
.LASF77:
	.string	"reliable_tx_ptr"
.LASF76:
	.string	"last_report_id"
.LASF36:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF21:
	.string	"DBG_PIN_NACK"
.LASF70:
	.string	"kb_consumer1"
.LASF68:
	.string	"kb_consumer2"
.LASF46:
	.string	"wheel_key"
.LASF86:
	.string	"hid_express_2_4g_post_process"
.LASF64:
	.string	"T_ASSEMBLE_VAL_CTRL_S"
.LASF105:
	.string	"riscv_hid_report_id_select"
.LASF27:
	.string	"DBG_PIN_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_2_4G_mode.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
