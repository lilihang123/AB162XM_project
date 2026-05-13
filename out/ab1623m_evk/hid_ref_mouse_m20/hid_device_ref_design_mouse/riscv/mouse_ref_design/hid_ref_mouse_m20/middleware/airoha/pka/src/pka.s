	.file	"pka.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/middleware/airoha/pka/src/pka.c"
	.section	.text.riscv_pka_rtt_tx_post_prepare_callback,"ax",@progbits
	.align	1
	.globl	riscv_pka_rtt_tx_post_prepare_callback
	.hidden	riscv_pka_rtt_tx_post_prepare_callback
	.type	riscv_pka_rtt_tx_post_prepare_callback, @function
riscv_pka_rtt_tx_post_prepare_callback:
.LFB37:
	.file 1 "/workdir/airoha/risc-v/middleware/airoha/pka/src/pka.c"
	.loc 1 410 1
	.cfi_startproc
.LVL0:
	.loc 1 436 5
	.loc 1 436 8 is_stmt 0
	bne	a0,zero,.L4
.LVL1:
.LBB45:
.LBB46:
	.loc 1 438 9 is_stmt 1
.LBE46:
.LBE45:
	.loc 1 410 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
.LBB50:
.LBB47:
	.loc 1 438 9
	call	pka_share_tx_forward_prepare_rtt0
.LVL2:
	.loc 1 440 9 is_stmt 1
.LBE47:
.LBE50:
	.loc 1 446 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
.LBB51:
.LBB48:
	li	a5,1
	.loc 1 440 21
	sb	a5,rtt_counter,a4
.LBE48:
.LBE51:
	.loc 1 446 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL3:
.L4:
	li	a5,0
.LBB52:
.LBB49:
	.loc 1 440 21
	sb	a5,rtt_counter,a4
	ret
.LBE49:
.LBE52:
	.cfi_endproc
.LFE37:
	.size	riscv_pka_rtt_tx_post_prepare_callback, .-riscv_pka_rtt_tx_post_prepare_callback
	.section	.text.pka_share_OS_dlist_getfront,"ax",@progbits
	.align	1
	.globl	pka_share_OS_dlist_getfront
	.hidden	pka_share_OS_dlist_getfront
	.type	pka_share_OS_dlist_getfront, @function
pka_share_OS_dlist_getfront:
.LFB21:
	.loc 1 165 1 is_stmt 1
	.cfi_startproc
.LVL4:
	.loc 1 166 5
.LBB60:
.LBB61:
	.loc 1 131 5
.LBE61:
.LBE60:
	.loc 1 165 1 is_stmt 0
	mv	a5,a0
.LBB63:
.LBB62:
	.loc 1 131 27
	lw	a0,4(a0)
.LVL5:
.LBE62:
.LBE63:
	.loc 1 166 8 discriminator 1
	beq	a5,a0,.L11
.LBB64:
	.loc 1 167 9 is_stmt 1
.LVL6:
	.loc 1 168 9
.LBB65:
.LBB66:
	.loc 1 136 5
	.loc 1 136 9 is_stmt 0
	lw	a4,0(a0)
	.loc 1 136 28
	lw	a5,4(a0)
.LVL7:
	.loc 1 136 22
	sw	a5,4(a4)
	.loc 1 137 5 is_stmt 1
	.loc 1 137 22 is_stmt 0
	sw	a4,0(a5)
	.loc 1 138 5 is_stmt 1
.LVL8:
.LBB67:
.LBB68:
	.loc 1 126 5
	.loc 1 126 31 is_stmt 0
	sw	a0,0(a0)
	.loc 1 126 17
	sw	a0,4(a0)
.LVL9:
.LBE68:
.LBE67:
.LBE66:
.LBE65:
	.loc 1 170 9 is_stmt 1
.LBB70:
.LBB69:
	.loc 1 139 1 is_stmt 0
	ret
.LVL10:
.L11:
.LBE69:
.LBE70:
.LBE64:
	.loc 1 172 15
	li	a0,0
	.loc 1 174 1
	ret
	.cfi_endproc
.LFE21:
	.size	pka_share_OS_dlist_getfront, .-pka_share_OS_dlist_getfront
	.section	.text.__pka_share_OSMQ_Get,"ax",@progbits
	.align	1
	.globl	__pka_share_OSMQ_Get
	.hidden	__pka_share_OSMQ_Get
	.type	__pka_share_OSMQ_Get, @function
__pka_share_OSMQ_Get:
.LFB22:
	.loc 1 177 1 is_stmt 1
	.cfi_startproc
.LVL11:
	.loc 1 178 5
	.loc 1 182 5
	.loc 1 177 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 177 1
	mv	s0,a0
	.loc 1 182 7
	bne	a0,zero,.L13
.LBB71:
	.loc 1 182 15 is_stmt 1 discriminator 1
	.loc 1 182 104 discriminator 1
	.loc 1 182 234 discriminator 1
	li	a2,182
	lla	a1,file.11
	lla	a0,exp.12
.LVL12:
	call	light_assert
.LVL13:
.L13:
.LBE71:
	.loc 1 182 265 discriminator 3
	.loc 1 184 5
	.loc 1 184 15 is_stmt 0
	lw	a5,8(s0)
	.loc 1 184 8
	beq	a5,zero,.L14
	.loc 1 185 9 is_stmt 1
	.loc 1 185 20 is_stmt 0
	addi	a5,a5,-1
	sw	a5,8(s0)
	.loc 1 187 9 is_stmt 1
	.loc 1 187 20 is_stmt 0
	mv	a0,s0
	.loc 1 200 1
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL14:
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 187 20
	tail	pka_share_OS_dlist_getfront
.LVL15:
.L14:
	.cfi_restore_state
	.loc 1 200 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL16:
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE22:
	.size	__pka_share_OSMQ_Get, .-__pka_share_OSMQ_Get
	.section	.text.pka_share_OSMQ_Peak,"ax",@progbits
	.align	1
	.globl	pka_share_OSMQ_Peak
	.hidden	pka_share_OSMQ_Peak
	.type	pka_share_OSMQ_Peak, @function
pka_share_OSMQ_Peak:
.LFB23:
	.loc 1 203 1 is_stmt 1
	.cfi_startproc
.LVL17:
	.loc 1 204 5
	.loc 1 205 1 is_stmt 0
	lw	a0,4(a0)
.LVL18:
	ret
	.cfi_endproc
.LFE23:
	.size	pka_share_OSMQ_Peak, .-pka_share_OSMQ_Peak
	.section	.text.pka_share_OSMQ_Get,"ax",@progbits
	.align	1
	.globl	pka_share_OSMQ_Get
	.hidden	pka_share_OSMQ_Get
	.type	pka_share_OSMQ_Get, @function
pka_share_OSMQ_Get:
.LFB24:
	.loc 1 208 1 is_stmt 1
	.cfi_startproc
.LVL19:
	.loc 1 209 5
	.loc 1 210 5
	.loc 1 210 12 is_stmt 0
	tail	__pka_share_OSMQ_Get
.LVL20:
	.cfi_endproc
.LFE24:
	.size	pka_share_OSMQ_Get, .-pka_share_OSMQ_Get
	.section	.text.pka_share_OSMQ_Put,"ax",@progbits
	.align	1
	.globl	pka_share_OSMQ_Put
	.hidden	pka_share_OSMQ_Put
	.type	pka_share_OSMQ_Put, @function
pka_share_OSMQ_Put:
.LFB25:
	.loc 1 216 1 is_stmt 1
	.cfi_startproc
.LVL21:
	.loc 1 217 5
	.loc 1 219 5
	.loc 1 216 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 216 1
	mv	s0,a0
	mv	s1,a1
	.loc 1 219 7
	bne	a0,zero,.L19
.LBB72:
	.loc 1 219 15 is_stmt 1 discriminator 1
	.loc 1 219 104 discriminator 1
	.loc 1 219 234 discriminator 1
	li	a2,219
	lla	a1,file.9
.LVL22:
	lla	a0,exp.10
.LVL23:
	call	light_assert
.LVL24:
.L19:
.LBE72:
	.loc 1 219 265 discriminator 3
	.loc 1 220 5
	.loc 1 220 7 is_stmt 0
	bne	s1,zero,.L20
.LBB73:
	.loc 1 220 15 is_stmt 1 discriminator 1
	.loc 1 220 101 discriminator 1
	.loc 1 220 231 discriminator 1
	li	a2,220
	lla	a1,file.7
	lla	a0,exp.8
	call	light_assert
.LVL25:
.L20:
.LBE73:
	.loc 1 220 262 discriminator 3
	.loc 1 223 5
.LBB74:
.LBB75:
	.loc 1 154 5
	lw	a5,0(s0)
.LVL26:
.LBB76:
.LBB77:
	.loc 1 145 5
	.loc 1 146 16 is_stmt 0
	sw	s0,4(s1)
.LBE77:
.LBE76:
.LBE75:
.LBE74:
	.loc 1 228 1
	lw	ra,8(sp)
	.cfi_restore 1
.LBB84:
.LBB82:
.LBB80:
.LBB78:
	.loc 1 145 16
	sw	a5,0(s1)
	.loc 1 146 5 is_stmt 1
	.loc 1 147 5
	.loc 1 147 21 is_stmt 0
	sw	s1,4(a5)
	.loc 1 148 5 is_stmt 1
.LBE78:
.LBE80:
.LBE82:
.LBE84:
	.loc 1 225 16 is_stmt 0
	lw	a5,8(s0)
.LVL27:
.LBB85:
.LBB83:
.LBB81:
.LBB79:
	.loc 1 148 21
	sw	s1,0(s0)
.LVL28:
.LBE79:
.LBE81:
.LBE83:
.LBE85:
	.loc 1 225 5 is_stmt 1
	.loc 1 228 1 is_stmt 0
	lw	s1,0(sp)
	.cfi_restore 9
.LVL29:
	.loc 1 225 16
	addi	a5,a5,1
	sw	a5,8(s0)
	.loc 1 227 5 is_stmt 1
	.loc 1 228 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
.LVL30:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE25:
	.size	pka_share_OSMQ_Put, .-pka_share_OSMQ_Put
	.section	.text.pka_share_OSMQ_PutFront,"ax",@progbits
	.align	1
	.globl	pka_share_OSMQ_PutFront
	.hidden	pka_share_OSMQ_PutFront
	.type	pka_share_OSMQ_PutFront, @function
pka_share_OSMQ_PutFront:
.LFB26:
	.loc 1 231 1 is_stmt 1
	.cfi_startproc
.LVL31:
	.loc 1 232 5
	.loc 1 234 5
	.loc 1 231 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 231 1
	mv	s0,a0
	mv	s1,a1
	.loc 1 234 7
	bne	a0,zero,.L23
.LBB86:
	.loc 1 234 15 is_stmt 1 discriminator 1
	.loc 1 234 104 discriminator 1
	.loc 1 234 234 discriminator 1
	li	a2,234
	lla	a1,file.5
.LVL32:
	lla	a0,exp.6
.LVL33:
	call	light_assert
.LVL34:
.L23:
.LBE86:
	.loc 1 234 265 discriminator 3
	.loc 1 235 5
	.loc 1 235 7 is_stmt 0
	bne	s1,zero,.L24
.LBB87:
	.loc 1 235 15 is_stmt 1 discriminator 1
	.loc 1 235 101 discriminator 1
	.loc 1 235 231 discriminator 1
	li	a2,235
	lla	a1,file.3
	lla	a0,exp.4
	call	light_assert
.LVL35:
.L24:
.LBE87:
	.loc 1 235 262 discriminator 3
	.loc 1 238 5
.LBB88:
.LBB89:
	.loc 1 160 5
	lw	a5,4(s0)
.LVL36:
.LBB90:
.LBB91:
	.loc 1 145 5
	.loc 1 145 16 is_stmt 0
	sw	s0,0(s1)
	.loc 1 146 5 is_stmt 1
.LBE91:
.LBE90:
.LBE89:
.LBE88:
	.loc 1 243 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
.LBB95:
.LBB94:
.LBB93:
.LBB92:
	.loc 1 146 16
	sw	a5,4(s1)
	.loc 1 147 5 is_stmt 1
	.loc 1 147 21 is_stmt 0
	sw	s1,4(s0)
	.loc 1 148 5 is_stmt 1
	.loc 1 148 21 is_stmt 0
	sw	s1,0(a5)
.LVL37:
.LBE92:
.LBE93:
.LBE94:
.LBE95:
	.loc 1 240 5 is_stmt 1
	.loc 1 240 16 is_stmt 0
	lw	a5,8(s0)
	.loc 1 243 1
	lw	s1,0(sp)
	.cfi_restore 9
.LVL38:
	.loc 1 240 16
	addi	a5,a5,1
	sw	a5,8(s0)
	.loc 1 242 5 is_stmt 1
	.loc 1 243 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
.LVL39:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE26:
	.size	pka_share_OSMQ_PutFront, .-pka_share_OSMQ_PutFront
	.section	.text.pka_share_OSMQ_PrintList,"ax",@progbits
	.align	1
	.globl	pka_share_OSMQ_PrintList
	.hidden	pka_share_OSMQ_PrintList
	.type	pka_share_OSMQ_PrintList, @function
pka_share_OSMQ_PrintList:
.LFB27:
	.loc 1 245 58 is_stmt 1
	.cfi_startproc
.LVL40:
	.loc 1 246 5
	.loc 1 247 5
	.loc 1 245 58 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 245 58
	mv	s0,a0
	.loc 1 246 30
	mv	s1,a0
.LVL41:
.L27:
	.loc 1 247 23 is_stmt 1
	.loc 1 247 16 is_stmt 0
	lw	s1,4(s1)
.LVL42:
	.loc 1 247 23
	bne	s1,s0,.L28
	.loc 1 254 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL43:
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL44:
.L28:
	.cfi_restore_state
.LBB96:
	.loc 1 248 9 is_stmt 1
	.loc 1 249 9
	.loc 1 250 9
	.loc 1 250 28 is_stmt 0
	mv	a0,s1
	call	pka_share_tx_buf_get_payload
.LVL45:
	.loc 1 251 9 is_stmt 1
.LBB97:
	.loc 1 251 14
	.loc 1 251 70
	.loc 1 251 230
	lbu	a4,14(a0)
	li	a3,1
	lla	a2,msg_id_string.2
	li	a1,1
	lla	a0,log_control_block_riscv_pka
.LVL46:
	call	print_module_msgid_log
.LVL47:
.LBE97:
	.loc 1 251 12 discriminator 1
	.loc 1 252 9
	j	.L27
.LBE96:
	.cfi_endproc
.LFE27:
	.size	pka_share_OSMQ_PrintList, .-pka_share_OSMQ_PrintList
	.section	.text.pka_share_OSMQ_PrintQueue,"ax",@progbits
	.align	1
	.globl	pka_share_OSMQ_PrintQueue
	.hidden	pka_share_OSMQ_PrintQueue
	.type	pka_share_OSMQ_PrintQueue, @function
pka_share_OSMQ_PrintQueue:
.LFB28:
	.loc 1 256 59
	.cfi_startproc
.LVL48:
	.loc 1 257 5
	.loc 1 258 5
	.loc 1 256 59 is_stmt 0
	addi	sp,sp,-36
	.cfi_def_cfa_offset 36
	sw	s0,28(sp)
	sw	s1,24(sp)
	sw	ra,32(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 256 59
	mv	s1,a0
	.loc 1 257 30
	mv	s0,a0
.LVL49:
.L31:
	.loc 1 258 23 is_stmt 1
	.loc 1 258 16 is_stmt 0
	lw	s0,4(s0)
.LVL50:
	.loc 1 258 23
	bne	s0,s1,.L32
	.loc 1 266 1
	lw	ra,32(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,28(sp)
	.cfi_restore 8
	lw	s1,24(sp)
	.cfi_restore 9
.LVL51:
	addi	sp,sp,36
	.cfi_def_cfa_offset 0
	jr	ra
.LVL52:
.L32:
	.cfi_restore_state
.LBB98:
	.loc 1 259 9 is_stmt 1
	.loc 1 260 9
	.loc 1 261 9
	.loc 1 261 28 is_stmt 0
	mv	a0,s0
	call	pka_share_tx_buf_get_payload
.LVL53:
	.loc 1 262 9 is_stmt 1
.LBB99:
	.loc 1 262 14
	.loc 1 262 70
	.loc 1 262 289
	lbu	a4,14(a0)
	lbu	a5,17(s0)
	li	a3,8
	sw	a4,20(sp)
	lbu	a4,13(a0)
	andi	a5,a5,128
	lla	a2,msg_id_string.1
	sw	a4,16(sp)
	lbu	a4,12(a0)
	li	a1,1
	sw	a4,12(sp)
	lbu	a4,11(a0)
	sw	a4,8(sp)
	lbu	a4,10(a0)
	sw	a4,4(sp)
	lbu	a4,9(a0)
	lla	a0,log_control_block_riscv_pka
.LVL54:
	sw	a4,0(sp)
	mv	a4,s0
	call	print_module_msgid_log
.LVL55:
.LBE99:
	.loc 1 262 12 discriminator 1
	.loc 1 264 9
	j	.L31
.LBE98:
	.cfi_endproc
.LFE28:
	.size	pka_share_OSMQ_PrintQueue, .-pka_share_OSMQ_PrintQueue
	.section	.text.pka_share_tx_buf_apply_to_HWMT,"ax",@progbits
	.align	1
	.globl	pka_share_tx_buf_apply_to_HWMT
	.hidden	pka_share_tx_buf_apply_to_HWMT
	.type	pka_share_tx_buf_apply_to_HWMT, @function
pka_share_tx_buf_apply_to_HWMT:
.LFB29:
	.loc 1 269 1
	.cfi_startproc
	.loc 1 276 5
.LVL56:
.LBB100:
.LBB101:
	.loc 1 209 5
	.loc 1 210 5
.LBE101:
.LBE100:
	.loc 1 269 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	.cfi_offset 8, -8
	.loc 1 276 53
	lla	s0,pka_share_ptr
.LVL57:
	.loc 1 276 39
	lw	a0,0(s0)
	.loc 1 269 1
	sw	ra,16(sp)
	.cfi_offset 1, -4
.LBB103:
.LBB102:
	.loc 1 210 12
	addi	a0,a0,16
.LVL58:
	call	__pka_share_OSMQ_Get
.LVL59:
	.loc 1 211 5 is_stmt 1
	.loc 1 212 5
.LBE102:
.LBE103:
	.loc 1 279 5
	.loc 1 279 8 is_stmt 0
	sw	a0,0(sp)
	beq	a0,zero,.L34
	.loc 1 284 5 is_stmt 1
	.loc 1 285 5
	.loc 1 285 10
	addi	a0,sp,4
.LVL60:
	call	hal_nvic_save_and_set_interrupt_mask
.LVL61:
	.loc 1 285 55 discriminator 1
	li	a0,4
	call	share_buffer_hw_semaphore_take
.LVL62:
	.loc 1 285 8 discriminator 2
	.loc 1 288 5
	.loc 1 288 42 is_stmt 0
	lw	a5,0(s0)
	.loc 1 289 8
	lw	a1,0(sp)
	.loc 1 289 9
	lw	a2,84(a5)
	.loc 1 288 54
	lw	a4,76(a5)
	.loc 1 289 8
	lbu	a0,0(a2)
	li	a2,1
	.loc 1 288 14
	lw	a3,0(a4)
.LVL63:
	.loc 1 289 5 is_stmt 1
	.loc 1 289 8 is_stmt 0
	bne	a0,a2,.L36
	.loc 1 289 52 discriminator 1
	bne	a3,zero,.L36
	.loc 1 291 9 is_stmt 1
	.loc 1 291 68 is_stmt 0
	lhu	a5,44(a5)
	.loc 1 291 53
	add	a5,a1,a5
	.loc 1 291 47
	sw	a5,0(a4)
	.loc 1 292 9 is_stmt 1
	.loc 1 292 28 is_stmt 0
	lw	a0,0(s0)
	.loc 1 292 9
	addi	a0,a0,28
	call	pka_share_OSMQ_Put
.LVL64:
	.loc 1 296 9 is_stmt 1
.LBB104:
.LBB105:
	.loc 1 209 5
	.loc 1 210 5
.LBE105:
.LBE104:
	.loc 1 296 34 is_stmt 0
	lw	a0,0(s0)
.LBB107:
.LBB106:
	.loc 1 210 12
	addi	a0,a0,16
.LVL65:
	call	__pka_share_OSMQ_Get
.LVL66:
	mv	a1,a0
.LVL67:
	.loc 1 211 5 is_stmt 1
	.loc 1 212 5
.LBE106:
.LBE107:
	.loc 1 299 9
	.loc 1 299 12 is_stmt 0
	bne	a0,zero,.L36
.LVL68:
.L38:
	.loc 1 325 5 is_stmt 1
	.loc 1 325 10
	li	a0,4
	call	share_buffer_hw_semaphore_give
.LVL69:
	.loc 1 325 45 discriminator 1
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL70:
	.loc 1 325 8 discriminator 2
.L34:
	.loc 1 326 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL71:
.L36:
	.cfi_restore_state
	.loc 1 308 5 is_stmt 1
	.loc 1 308 42 is_stmt 0
	lw	a0,0(s0)
	.loc 1 309 9
	lw	a3,84(a0)
	.loc 1 308 54
	lw	a4,80(a0)
	.loc 1 309 8
	lbu	a2,0(a3)
	li	a3,1
	.loc 1 308 14
	lw	a5,0(a4)
.LVL72:
	.loc 1 309 5 is_stmt 1
	.loc 1 309 8 is_stmt 0
	bne	a2,a3,.L37
	.loc 1 309 52 discriminator 1
	bne	a5,zero,.L37
	.loc 1 311 9 is_stmt 1
	.loc 1 311 68 is_stmt 0
	lhu	a5,44(a0)
.LVL73:
	.loc 1 311 53
	add	a5,a1,a5
	.loc 1 311 47
	sw	a5,0(a4)
.LVL74:
	.loc 1 312 9 is_stmt 1
	.loc 1 312 28 is_stmt 0
	lw	a0,0(s0)
	.loc 1 312 9
	addi	a0,a0,28
	call	pka_share_OSMQ_Put
.LVL75:
	j	.L38
.LVL76:
.L37:
	.loc 1 318 9 is_stmt 1
	addi	a0,a0,16
	call	pka_share_OSMQ_PutFront
.LVL77:
	j	.L38
	.cfi_endproc
.LFE29:
	.size	pka_share_tx_buf_apply_to_HWMT, .-pka_share_tx_buf_apply_to_HWMT
	.section	.text.riscv_pka_le_tx_post_prepare_callback,"ax",@progbits
	.align	1
	.globl	riscv_pka_le_tx_post_prepare_callback
	.hidden	riscv_pka_le_tx_post_prepare_callback
	.type	riscv_pka_le_tx_post_prepare_callback, @function
riscv_pka_le_tx_post_prepare_callback:
.LFB36:
	.loc 1 385 1
	.cfi_startproc
.LVL78:
	.loc 1 394 5
	tail	pka_share_tx_buf_apply_to_HWMT
.LVL79:
	.cfi_endproc
.LFE36:
	.size	riscv_pka_le_tx_post_prepare_callback, .-riscv_pka_le_tx_post_prepare_callback
	.section	.text.pka_share_tx_buf_ack_pending_check,"ax",@progbits
	.align	1
	.globl	pka_share_tx_buf_ack_pending_check
	.hidden	pka_share_tx_buf_ack_pending_check
	.type	pka_share_tx_buf_ack_pending_check, @function
pka_share_tx_buf_ack_pending_check:
.LFB30:
	.loc 1 329 1
	.cfi_startproc
	.loc 1 332 5
	.loc 1 333 5
	.loc 1 335 5
	.loc 1 329 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s1,4(sp)
	.cfi_offset 9, -12
	.loc 1 335 56
	lla	s1,pka_share_ptr
	lw	a5,0(s1)
	.loc 1 329 1
	sw	s0,8(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 335 11
	lb	s0,36(a5)
.LVL80:
.L46:
	.loc 1 335 64 is_stmt 1 discriminator 1
	bgt	s0,zero,.L49
	.loc 1 350 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL81:
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL82:
.L49:
	.cfi_restore_state
	.loc 1 336 9 is_stmt 1
.LBB108:
.LBB109:
	.loc 1 209 5
	.loc 1 210 5
.LBE109:
.LBE108:
	.loc 1 336 34 is_stmt 0
	lw	a0,0(s1)
.LBB111:
.LBB110:
	.loc 1 210 12
	addi	a0,a0,28
.LVL83:
	call	__pka_share_OSMQ_Get
.LVL84:
	mv	a1,a0
.LVL85:
	.loc 1 211 5 is_stmt 1
	.loc 1 212 5
.LBE110:
.LBE111:
	.loc 1 337 9
	.loc 1 337 12 is_stmt 0
	beq	a0,zero,.L47
	.loc 1 338 13 is_stmt 1
.LVL86:
.LBB112:
.LBB113:
	.file 2 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.loc 2 281 5
.LBE113:
.LBE112:
	.loc 1 338 16 is_stmt 0 discriminator 1
	lb	a5,17(a1)
	.loc 1 340 50
	lw	a0,0(s1)
.LVL87:
	.loc 1 338 16 discriminator 1
	bge	a5,zero,.L48
	.loc 1 340 17 is_stmt 1
	addi	a0,a0,4
	sw	a1,0(sp)
	call	pka_share_OSMQ_Put
.LVL88:
	.loc 1 341 17
.LBB114:
.LBB115:
	.loc 2 286 5
	.loc 2 286 25 is_stmt 0
	lw	a1,0(sp)
	lbu	a5,17(a1)
	andi	a5,a5,127
	sb	a5,17(a1)
.LVL89:
.L47:
.LBE115:
.LBE114:
	.loc 1 335 70 is_stmt 1 discriminator 2
	addi	s0,s0,-1
.LVL90:
	slli	s0,s0,24
	srai	s0,s0,24
.LVL91:
	j	.L46
.LVL92:
.L48:
	.loc 1 346 17
	addi	a0,a0,28
	call	pka_share_OSMQ_Put
.LVL93:
	j	.L47
	.cfi_endproc
.LFE30:
	.size	pka_share_tx_buf_ack_pending_check, .-pka_share_tx_buf_ack_pending_check
	.globl	__umodsi3
	.globl	__modsi3
	.section	.text.record_riscV_info,"ax",@progbits
	.align	1
	.globl	record_riscV_info
	.hidden	record_riscV_info
	.type	record_riscV_info, @function
record_riscV_info:
.LFB31:
	.loc 1 353 1
	.cfi_startproc
.LVL94:
	.loc 1 354 5
	.loc 1 353 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	sw	ra,16(sp)
	sw	s1,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 354 40
	lla	a3,RiscVHidIdx
	.loc 1 353 1
	sw	a0,4(sp)
	.loc 1 354 40
	lbu	a0,0(a3)
.LVL95:
	lla	s0,RiscVHID
	.loc 1 353 1
	sw	a2,0(sp)
	.loc 1 354 40
	slli	a5,a0,1
	add	a5,a5,a0
	slli	a5,a5,2
	add	a5,s0,a5
	.loc 1 354 8
	lhu	a5,4(a5)
	beq	a5,a1,.L54
	mv	s1,a1
	.loc 1 355 5 is_stmt 1
	.loc 1 355 37 is_stmt 0
	addi	a0,a0,1
	li	a1,10
.LVL96:
	call	__modsi3
.LVL97:
	.loc 1 356 44
	slli	a5,a0,1
	lw	a4,4(sp)
	.loc 1 358 34
	lw	a2,0(sp)
	.loc 1 356 44
	add	a5,a5,a0
	slli	a5,a5,2
	add	a5,s0,a5
	.loc 1 355 17
	lla	a3,RiscVHidIdx
	sb	a0,0(a3)
	.loc 1 356 5 is_stmt 1
	.loc 1 356 44 is_stmt 0
	sw	a4,0(a5)
	.loc 1 357 5 is_stmt 1
	.loc 1 357 43 is_stmt 0
	sh	s1,4(a5)
	.loc 1 358 5 is_stmt 1
	.loc 1 358 34 is_stmt 0
	sw	a2,8(a5)
.LVL98:
.L54:
	.loc 1 359 1
	lw	ra,16(sp)
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
.LVL99:
	jr	ra
	.cfi_endproc
.LFE31:
	.size	record_riscV_info, .-record_riscV_info
	.section	.text.pka_share_tx_buf_set_pkt_len,"ax",@progbits
	.align	1
	.globl	pka_share_tx_buf_set_pkt_len
	.hidden	pka_share_tx_buf_set_pkt_len
	.type	pka_share_tx_buf_set_pkt_len, @function
pka_share_tx_buf_set_pkt_len:
.LFB32:
	.loc 1 363 1 is_stmt 1
	.cfi_startproc
.LVL100:
	.loc 1 364 5
	.loc 1 364 16 is_stmt 0
	sh	a1,10(a0)
	.loc 1 365 5 is_stmt 1
	.loc 1 365 16 is_stmt 0
	sh	a1,22(a0)
	.loc 1 366 1
	ret
	.cfi_endproc
.LFE32:
	.size	pka_share_tx_buf_set_pkt_len, .-pka_share_tx_buf_set_pkt_len
	.section	.text.pka_share_hid_need_accmulate,"ax",@progbits
	.align	1
	.globl	pka_share_hid_need_accmulate
	.hidden	pka_share_hid_need_accmulate
	.type	pka_share_hid_need_accmulate, @function
pka_share_hid_need_accmulate:
.LFB33:
	.loc 1 369 1 is_stmt 1
	.cfi_startproc
	.loc 1 370 5
	.loc 1 370 28 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 370 14
	lw	a4,48(a5)
	.loc 1 370 54
	lbu	a4,0(a4)
	beq	a4,zero,.L62
	.loc 1 370 58 discriminator 2
	lw	a5,76(a5)
	.loc 1 369 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 370 58 discriminator 2
	lw	a0,0(a5)
	call	pka_tx_buf_is_hid
.LVL101:
	.loc 1 371 1
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 370 54 discriminator 1
	xori	a0,a0,1
	andi	a0,a0,0xff
	.loc 1 371 1
	andi	a0,a0,1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.L62:
	li	a0,1
	andi	a0,a0,1
	ret
	.cfi_endproc
.LFE33:
	.size	pka_share_hid_need_accmulate, .-pka_share_hid_need_accmulate
	.section	.text.pka_share_get_tx_status,"ax",@progbits
	.align	1
	.globl	pka_share_get_tx_status
	.hidden	pka_share_get_tx_status
	.type	pka_share_get_tx_status, @function
pka_share_get_tx_status:
.LFB34:
	.loc 1 374 1 is_stmt 1
	.cfi_startproc
	.loc 1 376 5
	.loc 1 376 28 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 376 14
	lw	a4,48(a5)
	.loc 1 376 54 discriminator 3
	li	a0,1
	.loc 1 376 54
	lbu	a4,0(a4)
	beq	a4,a0,.L71
	.loc 1 376 58 discriminator 2
	lw	a5,76(a5)
	.loc 1 374 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 376 58 discriminator 2
	lw	a0,0(a5)
	call	pka_tx_buf_is_hid
.LVL102:
	.loc 1 377 1
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 376 54 discriminator 1
	xori	a0,a0,1
	andi	a0,a0,0xff
	.loc 1 377 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.L71:
	ret
	.cfi_endproc
.LFE34:
	.size	pka_share_get_tx_status, .-pka_share_get_tx_status
	.section	.text.pka_share_get_force_nack_ptr,"ax",@progbits
	.align	1
	.globl	pka_share_get_force_nack_ptr
	.hidden	pka_share_get_force_nack_ptr
	.type	pka_share_get_force_nack_ptr, @function
pka_share_get_force_nack_ptr:
.LFB35:
	.loc 1 380 1 is_stmt 1
	.cfi_startproc
	.loc 1 381 5
	.loc 1 381 25 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 382 1
	lw	a0,52(a5)
	ret
	.cfi_endproc
.LFE35:
	.size	pka_share_get_force_nack_ptr, .-pka_share_get_force_nack_ptr
	.section	.text.pka_share_hwmt_get_rxhdr,"ax",@progbits
	.align	1
	.globl	pka_share_hwmt_get_rxhdr
	.hidden	pka_share_hwmt_get_rxhdr
	.type	pka_share_hwmt_get_rxhdr, @function
pka_share_hwmt_get_rxhdr:
.LFB38:
	.loc 1 465 1 is_stmt 1
	.cfi_startproc
	.loc 1 466 5
	.loc 1 466 39 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 466 12
	lw	a5,128(a5)
	.loc 1 467 1
	lbu	a0,-4(a5)
	ret
	.cfi_endproc
.LFE38:
	.size	pka_share_hwmt_get_rxhdr, .-pka_share_hwmt_get_rxhdr
	.section	.text.pka_share_hwmt_get_curidx,"ax",@progbits
	.align	1
	.globl	pka_share_hwmt_get_curidx
	.hidden	pka_share_hwmt_get_curidx
	.type	pka_share_hwmt_get_curidx, @function
pka_share_hwmt_get_curidx:
.LFB39:
	.loc 1 470 1 is_stmt 1
	.cfi_startproc
	.loc 1 471 5
	.loc 1 471 38 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 471 12
	lw	a5,116(a5)
	.loc 1 472 1
	lbu	a0,0(a5)
	ret
	.cfi_endproc
.LFE39:
	.size	pka_share_hwmt_get_curidx, .-pka_share_hwmt_get_curidx
	.section	.text.pka_share_get_hwmt_last_anchor,"ax",@progbits
	.align	1
	.globl	pka_share_get_hwmt_last_anchor
	.hidden	pka_share_get_hwmt_last_anchor
	.type	pka_share_get_hwmt_last_anchor, @function
pka_share_get_hwmt_last_anchor:
.LFB40:
	.loc 1 475 1 is_stmt 1
	.cfi_startproc
.LVL103:
	.loc 1 476 5
	.loc 1 476 41 is_stmt 0
	lw	a5,pka_share_ptr
	.loc 1 476 27
	lw	a4,120(a5)
	.loc 1 477 26
	lw	a5,124(a5)
	.loc 1 476 27
	lw	a4,0(a4)
	.loc 1 477 26
	lhu	a5,0(a5)
	.loc 1 476 25
	sw	a4,0(a0)
	.loc 1 477 5 is_stmt 1
	.loc 1 477 24 is_stmt 0
	sh	a5,4(a0)
	.loc 1 478 1
	ret
	.cfi_endproc
.LFE40:
	.size	pka_share_get_hwmt_last_anchor, .-pka_share_get_hwmt_last_anchor
	.section	.text.pka_share_get_hwmt_pico_offset,"ax",@progbits
	.align	1
	.globl	pka_share_get_hwmt_pico_offset
	.hidden	pka_share_get_hwmt_pico_offset
	.type	pka_share_get_hwmt_pico_offset, @function
pka_share_get_hwmt_pico_offset:
.LFB41:
	.loc 1 481 1 is_stmt 1
	.cfi_startproc
.LVL104:
	.loc 1 482 5
	.loc 1 482 41 is_stmt 0
	lw	a4,pka_share_ptr
	.loc 1 482 27
	lw	a5,68(a4)
	.loc 1 482 79
	lw	a5,0(a5)
	slli	a5,a5,6
	srli	a5,a5,6
	.loc 1 482 25
	sw	a5,0(a0)
	.loc 1 483 5 is_stmt 1
	.loc 1 483 26 is_stmt 0
	lw	a5,72(a4)
	.loc 1 483 84
	lhu	a5,0(a5)
	slli	a5,a5,20
	srli	a5,a5,20
	.loc 1 483 24
	sh	a5,4(a0)
	.loc 1 484 1
	ret
	.cfi_endproc
.LFE41:
	.size	pka_share_get_hwmt_pico_offset, .-pka_share_get_hwmt_pico_offset
	.section	.text.pka_share_get_sync_clk,"ax",@progbits
	.align	1
	.globl	pka_share_get_sync_clk
	.hidden	pka_share_get_sync_clk
	.type	pka_share_get_sync_clk, @function
pka_share_get_sync_clk:
.LFB42:
	.loc 1 487 1 is_stmt 1
	.cfi_startproc
.LVL105:
	.loc 1 488 5
	.loc 1 488 26 is_stmt 0
	li	a5,-1610547200
	addi	a5,a5,1040
	lw	a5,0(a5)
	.loc 1 488 59
	srli	a5,a5,2
	.loc 1 488 23
	sw	a5,0(a0)
	.loc 1 489 5 is_stmt 1
	.loc 1 489 24 is_stmt 0
	li	a5,-1610547200
	addi	a5,a5,1044
	lw	a5,0(a5)
	.loc 1 489 22
	sh	a5,4(a0)
	.loc 1 490 1
	ret
	.cfi_endproc
.LFE42:
	.size	pka_share_get_sync_clk, .-pka_share_get_sync_clk
	.globl	__mulsi3
	.section	.text.riscv_pka_rt_tx_post_prepare_callback,"ax",@progbits
	.align	1
	.globl	riscv_pka_rt_tx_post_prepare_callback
	.hidden	riscv_pka_rt_tx_post_prepare_callback
	.type	riscv_pka_rt_tx_post_prepare_callback, @function
riscv_pka_rt_tx_post_prepare_callback:
.LFB44:
	.loc 1 518 1 is_stmt 1
	.cfi_startproc
.LVL106:
	.loc 1 544 5
	.loc 1 518 1 is_stmt 0
	addi	sp,sp,-112
	.cfi_def_cfa_offset 112
	sw	ra,108(sp)
	sw	s0,104(sp)
	sw	s1,100(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 544 9
	call	pka_share_hwmt_get_curidx
.LVL107:
	.loc 1 544 8 discriminator 1
	bne	a0,zero,.L80
.LVL108:
.LBB122:
.LBB123:
	.loc 1 545 9 is_stmt 1
	.loc 1 546 9
	.loc 1 547 8
	.loc 1 547 34 is_stmt 0
	li	a5,1108369408
	lw	a4,16(a5)
.LVL109:
	.loc 1 548 9 is_stmt 1
	.loc 1 548 18 is_stmt 0
	li	a5,1107558400
	addi	a5,a5,12
	lw	a5,0(a5)
.LVL110:
	.loc 1 551 9 is_stmt 1
	.loc 1 551 71 is_stmt 0 discriminator 1
	andi	a5,a5,64
.LVL111:
	.loc 1 551 50 discriminator 1
	or	a5,a5,a4
	bne	a5,zero,.L80
	.loc 1 556 9 is_stmt 1
	addi	a0,sp,12
	call	pka_share_get_hwmt_last_anchor
.LVL112:
	.loc 1 558 9
	addi	a0,sp,20
	call	pka_share_get_hwmt_pico_offset
.LVL113:
	.loc 1 560 9
	.loc 1 560 65 is_stmt 0
	lw	a5,20(sp)
	.loc 1 562 26
	lhu	a3,16(sp)
	.loc 1 562 47
	lhu	s0,24(sp)
	.loc 1 560 65
	sw	a5,8(sp)
	.loc 1 560 52
	lw	a4,8(sp)
	lw	a5,12(sp)
	sub	a5,a5,a4
	.loc 1 560 74
	slli	a5,a5,6
	srli	a5,a5,6
.LVL114:
	.loc 1 562 9 is_stmt 1
	.loc 1 562 12 is_stmt 0
	bltu	a3,s0,.L83
	.loc 1 563 13 is_stmt 1
	.loc 1 563 53 is_stmt 0
	sub	a3,a3,s0
	slli	s1,a3,16
	srli	s1,s1,16
.LVL115:
.L84:
	.loc 1 569 3
	addi	a0,sp,28
	sw	a5,4(sp)
.LVL116:
	.loc 1 569 3 is_stmt 1
	call	pka_share_get_sync_clk
.LVL117:
	.loc 1 571 9
	.loc 1 571 22 is_stmt 0
	lw	a5,28(sp)
	sw	a5,0(sp)
	.loc 1 571 12
	mv	a4,a5
	lw	a5,4(sp)
	bne	a4,zero,.L85
	.loc 1 572 13 is_stmt 1
.LBB124:
	.loc 1 572 18
	.loc 1 572 74
	.loc 1 572 229
.LBE124:
.LBE123:
.LBE122:
	.loc 1 869 1 is_stmt 0
	lw	s0,104(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,108(sp)
	.cfi_restore 1
	lw	s1,100(sp)
	.cfi_restore 9
.LVL118:
.LBB137:
.LBB130:
.LBB125:
	.loc 1 572 229
	li	a3,0
.LBE125:
.LBE130:
.LBE137:
	.loc 1 869 1
.LBB138:
.LBB131:
.LBB126:
	.loc 1 572 229
	lla	a2,msg_id_string.0
	li	a1,1
	lla	a0,log_control_block_riscv_pka
.LBE126:
.LBE131:
.LBE138:
	.loc 1 869 1
	addi	sp,sp,112
	.cfi_def_cfa_offset 0
.LVL119:
.LBB139:
.LBB132:
.LBB127:
	.loc 1 572 229
	tail	print_module_msgid_log
.LVL120:
.L83:
	.cfi_restore_state
.LBE127:
	.loc 1 565 13 is_stmt 1
	.loc 1 565 60 is_stmt 0
	li	a2,4096
	addi	a2,a2,-1596
	add	a3,a3,a2
	sub	a3,a3,s0
	slli	s1,a3,16
	srli	s1,s1,16
.LVL121:
	.loc 1 566 13 is_stmt 1
	.loc 1 566 32 is_stmt 0
	addi	a5,a5,-1
.LVL122:
	j	.L84
.LVL123:
.L85:
	.loc 1 580 9 is_stmt 1
	.loc 1 582 9
	.loc 1 583 72 is_stmt 0
	lhu	a4,32(sp)
	sw	a4,4(sp)
.LVL124:
	.loc 1 582 12
	lw	a4,0(sp)
	bgtu	a4,a5,.L86
	.loc 1 582 53 discriminator 1
	bne	a4,a5,.L87
	.loc 1 583 59
	lw	a4,4(sp)
	bgeu	s1,a4,.L87
.L86:
	.loc 1 584 13 is_stmt 1
	.loc 1 584 20 is_stmt 0
	lw	a5,4(sp)
	.loc 1 584 27
	addi	a3,s1,2000
	.loc 1 584 20
	sub	s1,a3,a5
.LVL125:
	.loc 1 585 13 is_stmt 1
	.loc 1 585 16 is_stmt 0
	li	a3,4096
	addi	a3,a3,-1596
	ble	s1,a3,.L88
	.loc 1 586 17 is_stmt 1
	.loc 1 586 24 is_stmt 0
	sub	s1,s1,a3
.LVL126:
.L88:
	.loc 1 599 9 is_stmt 1
	.loc 1 599 18 is_stmt 0
	li	a2,32
	lla	a1,.LANCHOR0
	addi	a0,sp,36
	call	memcpy
.LVL127:
	.loc 1 609 9 is_stmt 1
	.loc 1 609 18 is_stmt 0
	addi	t1,sp,68
	li	a2,32
	lla	a1,.LANCHOR0+32
	mv	a0,t1
	call	memcpy
.LVL128:
	.loc 1 651 44
	lla	a2,pka_share_ptr
	lw	a1,0(a2)
	.loc 1 609 18
	mv	t1,a0
	.loc 1 650 9 is_stmt 1
.LVL129:
	.loc 1 651 9
	.loc 1 653 12 is_stmt 0
	li	a3,2
	.loc 1 651 17
	lbu	a0,138(a1)
	.loc 1 653 12
	lbu	t0,137(a1)
	.loc 1 651 17
	addi	a0,a0,-1
	andi	a0,a0,0xff
.LVL130:
	.loc 1 653 9 is_stmt 1
	.loc 1 653 12 is_stmt 0
	bne	t0,a3,.L91
	.loc 1 654 13 is_stmt 1
	.loc 1 654 54 is_stmt 0
	li	a3,5
	bne	a0,a3,.L126
	.loc 1 654 24 discriminator 4
	li	a3,-260
	j	.L92
.LVL131:
.L87:
	.loc 1 590 13 is_stmt 1
	.loc 1 591 13
	.loc 1 590 62 is_stmt 0
	lw	a4,0(sp)
	li	a1,4096
	addi	a1,a1,-1596
	sub	a0,a5,a4
	call	__mulsi3
.LVL132:
	.loc 1 591 20
	lw	a4,4(sp)
	.loc 1 591 29
	add	a5,a0,s1
	.loc 1 593 27
	li	a3,2000
	.loc 1 591 20
	sub	s1,a5,a4
.LVL133:
	.loc 1 593 13 is_stmt 1
.L89:
	.loc 1 593 27
	ble	s1,a3,.L88
	.loc 1 594 17
	.loc 1 594 24 is_stmt 0
	addi	s1,s1,-2000
.LVL134:
	j	.L89
.LVL135:
.L91:
	.loc 1 656 13 is_stmt 1
	.loc 1 656 16 is_stmt 0
	li	a3,6
	beq	a0,a3,.L119
	.loc 1 659 17 is_stmt 1
	.loc 1 660 28 is_stmt 0
	lhu	a3,140(a1)
	beq	a3,zero,.L120
	.loc 1 660 28 discriminator 2
	li	a3,-240
.LVL136:
.L94:
	mv	a0,t1
	.loc 1 687 43
	li	t1,-229
.L95:
	.loc 1 687 43 is_stmt 1
	blt	s1,t1,.L97
	.loc 1 687 43 is_stmt 0 discriminator 1
	addi	a5,sp,100
	beq	a0,a5,.L117
	.loc 1 688 17 is_stmt 1
	.loc 1 688 24 is_stmt 0
	lw	t0,0(a0)
	addi	a0,a0,4
	sub	s1,s1,t0
.LVL137:
	.loc 1 689 17 is_stmt 1
	j	.L95
.LVL138:
.L126:
	.loc 1 663 9
	.loc 1 665 9
	.loc 1 665 12 is_stmt 0
	li	t0,6
	li	a3,-348
	beq	a0,t0,.L92
.LVL139:
	.loc 1 666 83 discriminator 1
	lhu	a0,140(a1)
.LVL140:
	bne	a0,zero,.L94
.L92:
	addi	a0,sp,36
	.loc 1 674 43
	li	t0,-127
	j	.L96
.L98:
	.loc 1 675 17 is_stmt 1
	.loc 1 675 24 is_stmt 0
	lw	t2,0(a0)
	addi	a0,a0,4
	sub	s1,s1,t2
.LVL141:
	.loc 1 676 17 is_stmt 1
.L96:
	.loc 1 674 43
	blt	s1,t0,.L97
	.loc 1 674 43 is_stmt 0 discriminator 1
	bne	t1,a0,.L98
.L117:
	.loc 1 702 13 is_stmt 1
	.loc 1 702 39 is_stmt 0
	addi	a0,a3,-10
	.loc 1 702 15
	blt	s1,a0,.L101
	.loc 1 703 36
	addi	a0,a3,10
	.loc 1 702 48 discriminator 1
	bgt	s1,a0,.L101
	.loc 1 704 17 is_stmt 1
	.loc 1 704 29 is_stmt 0
	addi	a0,a3,-3
	.loc 1 704 19
	blt	s1,a0,.L104
	.loc 1 704 63 discriminator 1
	addi	a0,a3,3
	.loc 1 704 52 discriminator 1
	ble	s1,a0,.L105
.L104:
	.loc 1 705 21 is_stmt 1
	.loc 1 705 40 is_stmt 0
	lla	t1,correction_idx
	lbu	t0,0(t1)
	.loc 1 705 24
	li	a0,255
	bne	t0,a0,.L106
.L129:
	.loc 1 711 29 is_stmt 1
	lw	a1,4(sp)
.LVL142:
	lw	a0,0(sp)
	mv	a2,s1
.LVL143:
	call	record_riscV_info
.LVL144:
	.loc 1 712 29
	.loc 1 712 44 is_stmt 0
	lbu	a5,RiscVHidIdx
	lla	t1,correction_idx
	sb	a5,0(t1)
	.loc 1 713 29 is_stmt 1
.LVL145:
.L80:
.LBE132:
.LBE139:
	.loc 1 869 1 is_stmt 0
	lw	ra,108(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,104(sp)
	.cfi_restore 8
	lw	s1,100(sp)
	.cfi_restore 9
	addi	sp,sp,112
	.cfi_def_cfa_offset 0
	jr	ra
.LVL146:
.L119:
	.cfi_restore_state
.LBB140:
.LBB133:
	.loc 1 657 28
	li	a3,-138
	j	.L92
.L120:
	.loc 1 660 28 discriminator 1
	li	a3,-268
	j	.L92
.LVL147:
.L97:
	.loc 1 700 9 is_stmt 1
	.loc 1 700 12 is_stmt 0
	bne	s1,a3,.L117
.L101:
	.loc 1 750 9 is_stmt 1
	.loc 1 750 30 is_stmt 0
	li	a4,1108369408
	lw	a3,16(a4)
.LVL148:
	.loc 1 751 9 is_stmt 1
	.loc 1 751 26 is_stmt 0
	li	a4,1107558400
	addi	a4,a4,12
	lw	a4,0(a4)
.LVL149:
	.loc 1 752 9 is_stmt 1
	.loc 1 752 71 is_stmt 0 discriminator 1
	andi	a4,a4,64
.LVL150:
	.loc 1 752 50 discriminator 1
	or	a4,a4,a3
	bne	a4,zero,.L80
	.loc 1 757 9 is_stmt 1
	.loc 1 757 39 is_stmt 0
	lla	a3,riscv_pka_info
.LVL151:
	lhu	a0,16(a3)
	.loc 1 757 12
	li	a4,65536
	addi	a4,a4,-1
	beq	a0,a4,.L113
	.loc 1 759 13 is_stmt 1
	.loc 1 759 53 is_stmt 0
	lw	a4,72(a1)
	.loc 1 759 16
	lhu	a1,0(a4)
.LVL152:
	li	a4,4
	bne	a1,a0,.L114
	.loc 1 760 17 is_stmt 1
	.loc 1 760 50 is_stmt 0
	li	a5,-1
	sh	a5,16(a3)
.LVL153:
.L113:
	.loc 1 787 9 is_stmt 1
	.loc 1 787 25 is_stmt 0
	call	pka_share_hwmt_get_rxhdr
.LVL154:
	.loc 1 788 9 is_stmt 1
.LBE133:
.LBE140:
	.loc 1 869 1 is_stmt 0
	lw	s0,104(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,108(sp)
	.cfi_restore 1
	lw	s1,100(sp)
	.cfi_restore 9
.LVL155:
.LBB141:
.LBB134:
	.loc 1 788 43
	srli	a0,a0,5
.LVL156:
.LBE134:
.LBE141:
	.loc 1 869 1
.LBB142:
.LBB135:
	.loc 1 788 9
	andi	a0,a0,1
.LBE135:
.LBE142:
	.loc 1 869 1
	addi	sp,sp,112
	.cfi_def_cfa_offset 0
.LBB143:
.LBB136:
	.loc 1 788 9
	tail	pka_active_state_set
.LVL157:
.L106:
	.cfi_restore_state
	.loc 1 710 25 is_stmt 1
	.loc 1 710 63 is_stmt 0
	slli	a0,t0,1
	add	a0,a0,t0
	slli	a0,a0,2
	lla	t0,RiscVHID
	add	a0,t0,a0
	.loc 1 710 28
	lw	a0,8(a0)
	bne	s1,a0,.L129
.L105:
	.loc 1 717 17 is_stmt 1
	.loc 1 717 20 is_stmt 0
	ble	s1,a3,.L108
	.loc 1 719 21 is_stmt 1
	.loc 1 719 39 is_stmt 0
	add	a4,s0,s1
	sub	a4,a4,a3
	slli	a4,a4,16
	.loc 1 721 24
	li	a3,4096
	.loc 1 719 39
	srli	a4,a4,16
	.loc 1 721 21 is_stmt 1
	.loc 1 721 24 is_stmt 0
	addi	a3,a3,-1597
	bgtu	a4,a3,.L109
	.loc 1 719 39
	sh	a4,24(sp)
.L110:
	.loc 1 745 17 is_stmt 1
	.loc 1 745 50 is_stmt 0
	lhu	a3,24(sp)
	lla	a4,riscv_pka_info
	sh	a3,16(a4)
	.loc 1 746 17 is_stmt 1
	.loc 1 746 51 is_stmt 0
	lw	a3,20(sp)
	sw	a3,12(a4)
	j	.L101
.L109:
	.loc 1 722 25 is_stmt 1
	.loc 1 725 43 is_stmt 0
	lw	a5,8(sp)
	.loc 1 722 43
	li	a3,-4096
	addi	a3,a3,1596
	add	a4,a4,a3
	sh	a4,24(sp)
	.loc 1 725 25 is_stmt 1
	.loc 1 726 25
	.loc 1 725 43 is_stmt 0
	addi	a4,a5,1
	.loc 1 726 44
	slli	a4,a4,6
	srli	a4,a4,6
.L128:
.LBB128:
	.loc 1 741 47
	sw	a4,20(sp)
	j	.L110
.L108:
	.loc 1 730 21 is_stmt 1
.LVL158:
	.loc 1 732 21
	.loc 1 730 29 is_stmt 0
	sub	a3,a3,s1
.LVL159:
	.loc 1 732 43
	andi	a3,a3,0xff
	.loc 1 732 24
	bltu	s0,a3,.L111
	.loc 1 733 25 is_stmt 1
	.loc 1 733 43 is_stmt 0
	sub	a3,s0,a3
	sh	a3,24(sp)
	j	.L110
.L111:
	.loc 1 735 25 is_stmt 1
	.loc 1 735 43 is_stmt 0
	li	a0,4096
	addi	a0,a0,-1596
	add	a4,s0,a0
	.loc 1 738 28
	lw	a5,8(sp)
	.loc 1 735 43
	sub	a4,a4,a3
	sh	a4,24(sp)
	.loc 1 738 25 is_stmt 1
	.loc 1 738 28 is_stmt 0
	bne	a5,zero,.L112
	.loc 1 739 29 is_stmt 1
	.loc 1 739 48 is_stmt 0
	li	a4,67108864
	addi	a4,a4,-1
	j	.L128
.L112:
	.loc 1 741 29 is_stmt 1
	.loc 1 741 47 is_stmt 0
	lw	a5,8(sp)
	addi	a4,a5,-1
	j	.L128
.LVL160:
.L114:
.LBE128:
.LBB129:
	.loc 1 763 32 is_stmt 1
	addi	a4,a4,-1
.LVL161:
	beq	a4,zero,.L115
	.loc 1 764 55 is_stmt 0
	li	a0,4
	sw	a4,8(sp)
.LVL162:
	.loc 1 764 21 is_stmt 1
	.loc 1 764 55 is_stmt 0
	call	hal_hw_semaphore_take
.LVL163:
	.loc 1 764 24 discriminator 1
	lw	a4,8(sp)
	lla	a2,pka_share_ptr
	lla	a3,riscv_pka_info
	bne	a0,zero,.L114
	.loc 1 765 25 is_stmt 1
	.loc 1 765 39 is_stmt 0
	lw	a4,0(a2)
	.loc 1 765 111
	lhu	a1,16(a3)
	.loc 1 767 25
	li	a0,4
	.loc 1 765 55
	lw	a2,72(a4)
	.loc 1 765 83
	sh	a1,0(a2)
	.loc 1 766 25 is_stmt 1
	.loc 1 766 77 is_stmt 0
	lw	a2,68(a4)
	.loc 1 766 114
	lw	a4,12(a3)
	li	a3,268435456
	or	a4,a4,a3
	.loc 1 766 77
	sw	a4,0(a2)
	.loc 1 767 25 is_stmt 1
	call	share_buffer_hw_semaphore_give
.LVL164:
	.loc 1 768 25
.L115:
	.loc 1 771 17
	.loc 1 772 17 is_stmt 0
	lw	a1,4(sp)
	lw	a0,0(sp)
	.loc 1 771 32
	li	a4,-1
	.loc 1 772 17
	mv	a2,s1
	.loc 1 771 32
	sb	a4,correction_idx,a3
	.loc 1 772 17 is_stmt 1
	call	record_riscV_info
.LVL165:
	j	.L113
.LBE129:
.LBE136:
.LBE143:
	.cfi_endproc
.LFE44:
	.size	riscv_pka_rt_tx_post_prepare_callback, .-riscv_pka_rt_tx_post_prepare_callback
	.section	.text.pka_share_get_cur_pico_clk,"ax",@progbits
	.align	1
	.globl	pka_share_get_cur_pico_clk
	.hidden	pka_share_get_cur_pico_clk
	.type	pka_share_get_cur_pico_clk, @function
pka_share_get_cur_pico_clk:
.LFB43:
	.loc 1 493 1
	.cfi_startproc
.LVL166:
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	.loc 1 497 29 is_stmt 0
	li	a3,-1610547200
	.loc 1 498 28
	li	a2,-1610547200
	.loc 1 493 1
	sw	ra,20(sp)
	sw	s0,16(sp)
	sw	s1,12(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 493 1
	mv	a4,a0
	.loc 1 497 29
	addi	a3,a3,8
	.loc 1 498 28
	addi	a2,a2,12
.L131:
	.loc 1 494 5 is_stmt 1
	.loc 1 496 5
	.loc 1 497 9
	.loc 1 497 29 is_stmt 0
	lw	s0,0(a3)
.LVL167:
	.loc 1 498 9 is_stmt 1
	.loc 1 498 28 is_stmt 0
	lhu	s1,0(a2)
	.loc 1 499 35 discriminator 1
	lw	a5,0(a3)
	.loc 1 498 28
	slli	s1,s1,16
	srli	s1,s1,16
.LVL168:
	.loc 1 499 32 is_stmt 1 discriminator 1
	bne	s0,a5,.L131
	.loc 1 504 5 is_stmt 0
	addi	a0,sp,4
.LVL169:
	sw	a4,0(sp)
	.loc 1 501 5 is_stmt 1
.LVL170:
	.loc 1 504 5
	call	pka_share_get_hwmt_pico_offset
.LVL171:
	.loc 1 505 5
	.loc 1 501 23 is_stmt 0
	li	a5,268435456
	addi	a5,a5,-4
	and	s0,s0,a5
.LVL172:
	.loc 1 505 20
	lw	a5,4(sp)
	.loc 1 508 8
	li	a3,4096
	addi	a3,a3,-1597
	.loc 1 505 20
	add	s0,s0,a5
	.loc 1 506 19
	lhu	a5,8(sp)
	.loc 1 505 20
	sw	s0,4(sp)
	.loc 1 506 5 is_stmt 1
	.loc 1 508 8 is_stmt 0
	lw	a4,0(sp)
	.loc 1 506 19
	add	a5,s1,a5
	slli	a5,a5,16
	srli	a5,a5,16
	.loc 1 508 5 is_stmt 1
	.loc 1 508 8 is_stmt 0
	bgtu	a5,a3,.L132
	.loc 1 506 19
	sh	a5,8(sp)
.L133:
	.loc 1 513 5 is_stmt 1
	.loc 1 513 22 is_stmt 0
	lw	a5,4(sp)
	.loc 1 515 1
	lw	ra,20(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	.loc 1 513 22
	sw	a5,0(a4)
	.loc 1 514 5 is_stmt 1
	.loc 1 514 21 is_stmt 0
	lhu	a5,8(sp)
	.loc 1 515 1
	lw	s1,12(sp)
	.cfi_restore 9
.LVL173:
	.loc 1 514 21
	sh	a5,4(a4)
	.loc 1 515 1
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
.LVL174:
	jr	ra
.LVL175:
.L132:
	.cfi_restore_state
	.loc 1 509 9 is_stmt 1
	.loc 1 509 23 is_stmt 0
	li	a3,-4096
	addi	a3,a3,1596
	add	a5,a5,a3
	.loc 1 510 24
	addi	s0,s0,4
	.loc 1 509 23
	sh	a5,8(sp)
	.loc 1 510 9 is_stmt 1
	.loc 1 510 24 is_stmt 0
	sw	s0,4(sp)
	j	.L133
	.cfi_endproc
.LFE43:
	.size	pka_share_get_cur_pico_clk, .-pka_share_get_cur_pico_clk
	.section	.text.pka_spi_callback_pre_process,"ax",@progbits
	.align	1
	.globl	pka_spi_callback_pre_process
	.hidden	pka_spi_callback_pre_process
	.type	pka_spi_callback_pre_process, @function
pka_spi_callback_pre_process:
.LFB45:
	.loc 1 872 1 is_stmt 1
	.cfi_startproc
.LVL176:
	.loc 1 875 5
	.loc 1 875 26 is_stmt 0
	lw	a5,pka_share_ptr
	lhu	a4,60(a5)
	sw	a4,0(a0)
	.loc 1 876 5 is_stmt 1
	.loc 1 878 8 is_stmt 0 discriminator 1
	lw	a5,0(a5)
	.loc 1 876 12
	lbu	a4,rtt_counter
	sw	a4,0(a1)
	.loc 1 878 5 is_stmt 1
.LBB144:
.LBB145:
	.loc 2 275 5
.LBE145:
.LBE144:
	.loc 1 878 8 is_stmt 0 discriminator 1
	beq	a5,zero,.L138
	.loc 1 881 5 is_stmt 1
	.loc 1 872 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 881 5
	call	pka_share_tx_ctrl_init
.LVL177:
	.loc 1 883 5 is_stmt 1
	call	pka_share_updt_hid_tx_ptr
.LVL178:
	.loc 1 885 5
	call	pka_share_tx_buf_ack_pending_check
.LVL179:
	.loc 1 887 5
	.loc 1 888 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 887 12
	li	a0,0
	.loc 1 888 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL180:
.L138:
	.loc 1 879 16
	li	a0,1
.LVL181:
	.loc 1 888 1
	ret
	.cfi_endproc
.LFE45:
	.size	pka_spi_callback_pre_process, .-pka_spi_callback_pre_process
	.section	.text.pka_spi_callback_post_process,"ax",@progbits
	.align	1
	.globl	pka_spi_callback_post_process
	.hidden	pka_spi_callback_post_process
	.type	pka_spi_callback_post_process, @function
pka_spi_callback_post_process:
.LFB46:
	.loc 1 891 1 is_stmt 1
	.cfi_startproc
	.loc 1 894 5
	.loc 1 894 14 is_stmt 0
	lw	a5,pka_share_ptr
	lhu	a5,60(a5)
.LVL182:
	.loc 1 895 5 is_stmt 1
	.loc 1 896 5
	.loc 1 891 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	sw	s0,4(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 896 8
	li	a4,1
	bne	a5,a4,.L144
	.loc 1 897 9 is_stmt 1
	.loc 1 897 25 is_stmt 0
	call	pka_share_advanced_tx_prepare_rt
.LVL183:
	mv	s0,a0
.LVL184:
	.loc 1 898 9 is_stmt 1
	li	a0,0
	call	riscv_pka_rt_tx_post_prepare_callback
.LVL185:
.L143:
	.loc 1 906 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	mv	a0,s0
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL186:
.L144:
	.cfi_restore_state
	.loc 1 899 12 is_stmt 1
	.loc 1 899 15 is_stmt 0
	bne	a5,zero,.L146
	.loc 1 900 9 is_stmt 1
.LVL187:
.LBB146:
.LBB147:
	.loc 1 394 5
	call	pka_share_tx_buf_apply_to_HWMT
.LVL188:
	.loc 1 398 79
	.loc 1 404 79
.L147:
.LBE147:
.LBE146:
	.loc 1 895 14 is_stmt 0
	li	s0,0
	j	.L143
.LVL189:
.L146:
	.loc 1 901 12 is_stmt 1
	.loc 1 901 15 is_stmt 0
	li	a4,2
	bne	a5,a4,.L147
	.loc 1 902 9 is_stmt 1
	lbu	a0,rtt_counter
	call	riscv_pka_rtt_tx_post_prepare_callback
.LVL190:
	j	.L147
	.cfi_endproc
.LFE46:
	.size	pka_spi_callback_post_process, .-pka_spi_callback_post_process
	.section	.text.riscv_pka_init,"ax",@progbits
	.align	1
	.globl	riscv_pka_init
	.hidden	riscv_pka_init
	.type	riscv_pka_init, @function
riscv_pka_init:
.LFB47:
	.loc 1 918 1
	.cfi_startproc
	.loc 1 925 5
	tail	pka_share_init
.LVL191:
	.cfi_endproc
.LFE47:
	.size	riscv_pka_init, .-riscv_pka_init
	.section	.text.pka_share_tx_buf_send,"ax",@progbits
	.align	1
	.globl	pka_share_tx_buf_send
	.hidden	pka_share_tx_buf_send
	.type	pka_share_tx_buf_send, @function
pka_share_tx_buf_send:
.LFB48:
	.loc 1 929 1
	.cfi_startproc
.LVL192:
	.loc 1 930 5
	.loc 1 929 1 is_stmt 0
	mv	a1,a0
	.loc 1 930 24
	lw	a0,pka_share_ptr
.LVL193:
	.loc 1 930 5
	addi	a0,a0,16
	tail	pka_share_OSMQ_Put
.LVL194:
	.cfi_endproc
.LFE48:
	.size	pka_share_tx_buf_send, .-pka_share_tx_buf_send
	.section	.text.pka_share_tx_buf_get_from_q,"ax",@progbits
	.align	1
	.globl	pka_share_tx_buf_get_from_q
	.hidden	pka_share_tx_buf_get_from_q
	.type	pka_share_tx_buf_get_from_q, @function
pka_share_tx_buf_get_from_q:
.LFB49:
	.loc 1 934 1 is_stmt 1
	.cfi_startproc
	.loc 1 935 5
.LVL195:
.LBB148:
.LBB149:
	.loc 1 209 5
	.loc 1 210 5
.LBE149:
.LBE148:
	.loc 1 935 31 is_stmt 0
	lw	a0,pka_share_ptr
.LBB151:
.LBB150:
	.loc 1 210 12
	addi	a0,a0,4
.LVL196:
	tail	__pka_share_OSMQ_Get
.LVL197:
.LBE150:
.LBE151:
	.cfi_endproc
.LFE49:
	.size	pka_share_tx_buf_get_from_q, .-pka_share_tx_buf_get_from_q
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 62
msg_id_string.0:
	.string	"[M:riscv_pka C:info F: L: ]: [RISCV][HWM_SYNC] sync time null"
	.hidden	rtt_counter
	.globl	rtt_counter
	.section	.sbss.rtt_counter,"aw",@nobits
	.type	rtt_counter, @object
	.size	rtt_counter, 1
rtt_counter:
	.zero	1
	.section	.log_string
	.align	2
	.type	msg_id_string.1, @object
	.size	msg_id_string.1, 126
msg_id_string.1:
	.string	"[M:riscv_pka C:info F: L: ]: pka_share_OSMQ_PrintQueue, ptr = %02x, valid = %d, payload[9~14] = %02x %02x %02x %02x %02x %02x"
	.align	2
	.type	msg_id_string.2, @object
	.size	msg_id_string.2, 67
msg_id_string.2:
	.string	"[M:riscv_pka C:info F: L: ]: pka_share_OSMQ_PrintList, seqn = %02x"
	.align	2
	.type	file.3, @object
	.size	file.3, 55
file.3:
	.string	"/workdir/airoha/risc-v/middleware/airoha/pka/src/pka.c"
	.align	2
	.type	exp.4, @object
	.size	exp.4, 12
exp.4:
	.string	"ptr != NULL"
	.align	2
	.type	file.5, @object
	.size	file.5, 55
file.5:
	.string	"/workdir/airoha/risc-v/middleware/airoha/pka/src/pka.c"
	.align	2
	.type	exp.6, @object
	.size	exp.6, 15
exp.6:
	.string	"mq_ptr != NULL"
	.align	2
	.type	file.7, @object
	.size	file.7, 55
file.7:
	.string	"/workdir/airoha/risc-v/middleware/airoha/pka/src/pka.c"
	.align	2
	.type	exp.8, @object
	.size	exp.8, 12
exp.8:
	.string	"ptr != NULL"
	.align	2
	.type	file.9, @object
	.size	file.9, 55
file.9:
	.string	"/workdir/airoha/risc-v/middleware/airoha/pka/src/pka.c"
	.align	2
	.type	exp.10, @object
	.size	exp.10, 15
exp.10:
	.string	"mq_ptr != NULL"
	.align	2
	.type	file.11, @object
	.size	file.11, 55
file.11:
	.string	"/workdir/airoha/risc-v/middleware/airoha/pka/src/pka.c"
	.align	2
	.type	exp.12, @object
	.size	exp.12, 15
exp.12:
	.string	"mq_ptr != NULL"
	.section	.sdata.correction_idx,"aw"
	.type	correction_idx, @object
	.size	correction_idx, 1
correction_idx:
	.byte	-1
	.section	.sbss.RiscVHidIdx,"aw",@nobits
	.type	RiscVHidIdx, @object
	.size	RiscVHidIdx, 1
RiscVHidIdx:
	.zero	1
	.hidden	RiscVHID
	.globl	RiscVHID
	.section	.bss.RiscVHID,"aw",@nobits
	.align	2
	.type	RiscVHID, @object
	.size	RiscVHID, 120
RiscVHID:
	.zero	120
	.hidden	pka_share_ptr
	.globl	pka_share_ptr
	.section	.sbss.pka_share_ptr,"aw",@nobits
	.align	2
	.type	pka_share_ptr, @object
	.size	pka_share_ptr, 4
pka_share_ptr:
	.zero	4
	.hidden	riscv_pka_info
	.globl	riscv_pka_info
	.section	.data.riscv_pka_info,"aw"
	.align	2
	.type	riscv_pka_info, @object
	.size	riscv_pka_info, 20
riscv_pka_info:
	.word	riscv_pka_le_tx_post_prepare_callback
	.word	riscv_pka_rt_tx_post_prepare_callback
	.word	riscv_pka_rtt_tx_post_prepare_callback
	.word	0
	.half	-1
	.zero	2
	.hidden	log_control_block_mirror_riscv_pka
	.globl	log_control_block_mirror_riscv_pka
	.section	.log_filter_mirror.riscv_pka,"a"
	.align	2
	.type	log_control_block_mirror_riscv_pka, @object
	.size	log_control_block_mirror_riscv_pka, 10
log_control_block_mirror_riscv_pka:
	.string	"riscv_pka"
	.hidden	log_control_block_riscv_pka
	.globl	log_control_block_riscv_pka
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC2:
	.string	"riscv_pka"
	.section	.log_filter.riscv_pka,"aw"
	.align	2
	.type	log_control_block_riscv_pka, @object
	.size	log_control_block_riscv_pka, 28
log_control_block_riscv_pka:
	.word	.LC2
	.word	0
	.word	1
	.word	0
	.word	0
	.word	0
	.word	print_module_msgid_log
	.section	.rodata
	.align	2
	.set	.LANCHOR0,. + 0
.LC0:
	.word	256
	.word	240
	.word	240
	.word	272
	.word	240
	.word	240
	.word	240
	.word	272
.LC1:
	.word	240
	.word	260
	.word	240
	.word	260
	.word	240
	.word	260
	.word	240
	.word	260
	.text
.Letext0:
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 7 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_eint_internal.h"
	.file 8 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_hw_semaphore.h"
	.file 9 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 10 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 11 "/workdir/airoha/risc-v/middleware/airoha/pka/inc/pka.h"
	.file 12 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 13 "/workdir/airoha/risc-v/kernel/service/exception_handler/inc/exception_handler.h"
	.file 14 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.file 15 "<built-in>"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1e4f
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x46
	.4byte	.LASF393
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL80
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
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0xe
	.byte	0x1
	.byte	0x6
	.4byte	.LASF6
	.uleb128 0xe
	.byte	0x2
	.byte	0x5
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
	.uleb128 0x47
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0xe
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x48
	.byte	0x4
	.uleb128 0xe
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x13
	.4byte	0x75
	.uleb128 0x8
	.4byte	0x7c
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x3
	.byte	0x22
	.byte	0x15
	.4byte	0x42
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x3
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x34
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x3
	.byte	0x31
	.byte	0x1c
	.4byte	0x3b
	.uleb128 0x5
	.4byte	.LASF17
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x37
	.byte	0xe
	.4byte	0xdc
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1
	.byte	0
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x3d
	.byte	0xe
	.4byte	0x102
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF24
	.byte	0x4
	.byte	0x42
	.byte	0x3
	.4byte	0xdc
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x45
	.byte	0xe
	.4byte	0x176
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x3f
	.byte	0
	.uleb128 0x5
	.4byte	.LASF40
	.byte	0x4
	.byte	0x57
	.byte	0x3
	.4byte	0x10e
	.uleb128 0x5
	.4byte	.LASF41
	.byte	0x4
	.byte	0x59
	.byte	0x10
	.4byte	0x18e
	.uleb128 0x8
	.4byte	0x193
	.uleb128 0x1f
	.4byte	0x1b3
	.uleb128 0x4
	.4byte	0x73
	.uleb128 0x4
	.4byte	0x81
	.uleb128 0x4
	.4byte	0x65
	.uleb128 0x4
	.4byte	0x102
	.uleb128 0x4
	.4byte	0x81
	.uleb128 0x20
	.byte	0
	.uleb128 0x5
	.4byte	.LASF42
	.byte	0x4
	.byte	0x5a
	.byte	0x10
	.4byte	0x1bf
	.uleb128 0x8
	.4byte	0x1c4
	.uleb128 0x1f
	.4byte	0x1ee
	.uleb128 0x4
	.4byte	0x73
	.uleb128 0x4
	.4byte	0x81
	.uleb128 0x4
	.4byte	0x65
	.uleb128 0x4
	.4byte	0x102
	.uleb128 0x4
	.4byte	0x1ee
	.uleb128 0x4
	.4byte	0x65
	.uleb128 0x4
	.4byte	0x81
	.uleb128 0x20
	.byte	0
	.uleb128 0x8
	.4byte	0x1f3
	.uleb128 0x49
	.uleb128 0x5
	.4byte	.LASF43
	.byte	0x4
	.byte	0x5b
	.byte	0x10
	.4byte	0x200
	.uleb128 0x8
	.4byte	0x205
	.uleb128 0x1f
	.4byte	0x220
	.uleb128 0x4
	.4byte	0x73
	.uleb128 0x4
	.4byte	0x102
	.uleb128 0x4
	.4byte	0x81
	.uleb128 0x4
	.4byte	0xb6
	.uleb128 0x20
	.byte	0
	.uleb128 0x5
	.4byte	.LASF44
	.byte	0x4
	.byte	0x5c
	.byte	0x14
	.4byte	0x22c
	.uleb128 0x8
	.4byte	0x231
	.uleb128 0x4a
	.4byte	0xb6
	.4byte	0x254
	.uleb128 0x4
	.4byte	0x73
	.uleb128 0x4
	.4byte	0x102
	.uleb128 0x4
	.4byte	0x176
	.uleb128 0x4
	.4byte	0x254
	.uleb128 0x4
	.4byte	0x259
	.byte	0
	.uleb128 0x8
	.4byte	0x1ee
	.uleb128 0x8
	.4byte	0xb6
	.uleb128 0x16
	.byte	0x1c
	.byte	0x4
	.byte	0x5e
	.4byte	0x2c2
	.uleb128 0x2
	.4byte	.LASF45
	.byte	0x4
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x4
	.byte	0x60
	.byte	0xe
	.4byte	0xb6
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x4
	.byte	0x61
	.byte	0xe
	.4byte	0xb6
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF48
	.byte	0x4
	.byte	0x62
	.byte	0xf
	.4byte	0x182
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x4
	.byte	0x63
	.byte	0x15
	.4byte	0x1b3
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF50
	.byte	0x4
	.byte	0x64
	.byte	0x12
	.4byte	0x220
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF51
	.byte	0x4
	.byte	0x65
	.byte	0x10
	.4byte	0x1f4
	.byte	0x18
	.byte	0
	.uleb128 0x5
	.4byte	.LASF52
	.byte	0x4
	.byte	0x66
	.byte	0x3
	.4byte	0x25e
	.uleb128 0x4b
	.4byte	.LASF394
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0xe
	.2byte	0x128
	.byte	0x12
	.4byte	0x354
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x1f
	.byte	0
	.uleb128 0x4c
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x5
	.2byte	0x407
	.byte	0xe
	.4byte	0x4ba
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x38
	.byte	0
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0x2a
	.byte	0xe
	.4byte	0x564
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0xff
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.byte	0x2
	.4byte	.LASF155
	.uleb128 0x8
	.4byte	0x9e
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x7
	.byte	0x4b
	.byte	0xe
	.4byte	0x5c0
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0
	.uleb128 0x1
	.4byte	.LASF157
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF159
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF162
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF163
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF164
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF165
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF166
	.byte	0xa
	.byte	0
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0xb6
	.byte	0xe
	.4byte	0x694
	.uleb128 0x1
	.4byte	.LASF167
	.byte	0
	.uleb128 0x1
	.4byte	.LASF168
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF169
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF170
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF171
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF172
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF173
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF174
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF175
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF176
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF177
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF178
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF180
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF182
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF183
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF184
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF188
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF189
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF190
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF191
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF192
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF193
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF194
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF195
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF196
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF197
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF198
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF199
	.byte	0x20
	.byte	0
	.uleb128 0x5
	.4byte	.LASF200
	.byte	0x8
	.byte	0xfa
	.byte	0x3
	.4byte	0x5c0
	.uleb128 0xf
	.byte	0x5
	.4byte	0x65
	.byte	0x8
	.byte	0xfe
	.byte	0xe
	.4byte	0x6c6
	.uleb128 0x2b
	.4byte	.LASF201
	.sleb128 -3
	.uleb128 0x2b
	.4byte	.LASF202
	.sleb128 -2
	.uleb128 0x2b
	.4byte	.LASF203
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF204
	.byte	0
	.byte	0
	.uleb128 0x4d
	.4byte	.LASF205
	.byte	0x8
	.2byte	0x103
	.byte	0x3
	.4byte	0x6a0
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x2
	.byte	0x6e
	.byte	0xe
	.4byte	0x6f9
	.uleb128 0x1
	.4byte	.LASF206
	.byte	0
	.uleb128 0x1
	.4byte	.LASF207
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF208
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF209
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF210
	.byte	0x2
	.byte	0x74
	.byte	0x3
	.4byte	0x6d3
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x2
	.byte	0x76
	.byte	0xe
	.4byte	0x71f
	.uleb128 0x1
	.4byte	.LASF211
	.byte	0
	.uleb128 0x1
	.4byte	.LASF212
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF213
	.byte	0x2
	.byte	0x79
	.byte	0x3
	.4byte	0x705
	.uleb128 0x21
	.4byte	.LASF220
	.byte	0x8
	.byte	0x2
	.byte	0x8b
	.4byte	0x752
	.uleb128 0x2
	.4byte	.LASF214
	.byte	0x2
	.byte	0x8c
	.byte	0x22
	.4byte	0x752
	.byte	0
	.uleb128 0x2
	.4byte	.LASF215
	.byte	0x2
	.byte	0x8d
	.byte	0x22
	.4byte	0x752
	.byte	0x4
	.byte	0
	.uleb128 0x8
	.4byte	0x72b
	.uleb128 0x5
	.4byte	.LASF216
	.byte	0x2
	.byte	0x8f
	.byte	0x3
	.4byte	0x72b
	.uleb128 0x5
	.4byte	.LASF217
	.byte	0x2
	.byte	0x8f
	.byte	0x1a
	.4byte	0x752
	.uleb128 0x5
	.4byte	.LASF218
	.byte	0x2
	.byte	0x90
	.byte	0x1e
	.4byte	0x757
	.uleb128 0x5
	.4byte	.LASF219
	.byte	0x2
	.byte	0x91
	.byte	0x22
	.4byte	0x763
	.uleb128 0x21
	.4byte	.LASF221
	.byte	0xc
	.byte	0x2
	.byte	0x94
	.4byte	0x7ae
	.uleb128 0x2
	.4byte	.LASF222
	.byte	0x2
	.byte	0x96
	.byte	0x1a
	.4byte	0x76f
	.byte	0
	.uleb128 0x4e
	.string	"noB"
	.byte	0x2
	.byte	0x98
	.byte	0xe
	.4byte	0xb6
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF223
	.byte	0x2
	.byte	0x99
	.byte	0x3
	.4byte	0x787
	.uleb128 0x5
	.4byte	.LASF224
	.byte	0x2
	.byte	0x99
	.byte	0x14
	.4byte	0x7c6
	.uleb128 0x8
	.4byte	0x787
	.uleb128 0x16
	.byte	0xc
	.byte	0x2
	.byte	0x9b
	.4byte	0x7fb
	.uleb128 0x2
	.4byte	.LASF225
	.byte	0x2
	.byte	0x9c
	.byte	0xf
	.4byte	0x259
	.byte	0
	.uleb128 0x2
	.4byte	.LASF226
	.byte	0x2
	.byte	0x9d
	.byte	0xf
	.4byte	0x259
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF227
	.byte	0x2
	.byte	0x9e
	.byte	0xf
	.4byte	0x7fb
	.byte	0x8
	.byte	0
	.uleb128 0x8
	.4byte	0xaa
	.uleb128 0x5
	.4byte	.LASF228
	.byte	0x2
	.byte	0x9f
	.byte	0x3
	.4byte	0x7cb
	.uleb128 0x16
	.byte	0x18
	.byte	0x2
	.byte	0xa1
	.4byte	0x849
	.uleb128 0x2
	.4byte	.LASF229
	.byte	0x2
	.byte	0xa2
	.byte	0x1e
	.4byte	0x800
	.byte	0
	.uleb128 0x2
	.4byte	.LASF230
	.byte	0x2
	.byte	0xa3
	.byte	0xc
	.4byte	0x849
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF231
	.byte	0x2
	.byte	0xa4
	.byte	0xc
	.4byte	0x849
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF232
	.byte	0x2
	.byte	0xa5
	.byte	0xe
	.4byte	0x56b
	.byte	0x14
	.byte	0
	.uleb128 0x8
	.4byte	0x73
	.uleb128 0x5
	.4byte	.LASF233
	.byte	0x2
	.byte	0xa8
	.byte	0x3
	.4byte	0x80c
	.uleb128 0x16
	.byte	0x54
	.byte	0x2
	.byte	0xaa
	.4byte	0x933
	.uleb128 0x2
	.4byte	.LASF229
	.byte	0x2
	.byte	0xab
	.byte	0x1e
	.4byte	0x800
	.byte	0
	.uleb128 0x2
	.4byte	.LASF234
	.byte	0x2
	.byte	0xac
	.byte	0xc
	.4byte	0x849
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF235
	.byte	0x2
	.byte	0xad
	.byte	0xc
	.4byte	0x849
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF236
	.byte	0x2
	.byte	0xae
	.byte	0xc
	.4byte	0x933
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF237
	.byte	0x2
	.byte	0xaf
	.byte	0xb
	.4byte	0x943
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF238
	.byte	0x2
	.byte	0xb0
	.byte	0xb
	.4byte	0x73
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF239
	.byte	0x2
	.byte	0xb1
	.byte	0xe
	.4byte	0x56b
	.byte	0x34
	.uleb128 0x2
	.4byte	.LASF240
	.byte	0x2
	.byte	0xb2
	.byte	0xf
	.4byte	0x259
	.byte	0x38
	.uleb128 0x2
	.4byte	.LASF241
	.byte	0x2
	.byte	0xb3
	.byte	0xf
	.4byte	0x7fb
	.byte	0x3c
	.uleb128 0x2
	.4byte	.LASF242
	.byte	0x2
	.byte	0xb4
	.byte	0xe
	.4byte	0x56b
	.byte	0x40
	.uleb128 0x2
	.4byte	.LASF243
	.byte	0x2
	.byte	0xb5
	.byte	0xf
	.4byte	0x7fb
	.byte	0x44
	.uleb128 0x2
	.4byte	.LASF244
	.byte	0x2
	.byte	0xb6
	.byte	0xd
	.4byte	0x9e
	.byte	0x48
	.uleb128 0x2
	.4byte	.LASF245
	.byte	0x2
	.byte	0xb7
	.byte	0xd
	.4byte	0x9e
	.byte	0x49
	.uleb128 0x2
	.4byte	.LASF246
	.byte	0x2
	.byte	0xb8
	.byte	0xd
	.4byte	0x9e
	.byte	0x4a
	.uleb128 0x2
	.4byte	.LASF247
	.byte	0x2
	.byte	0xb9
	.byte	0xe
	.4byte	0xaa
	.byte	0x4c
	.uleb128 0x2
	.4byte	.LASF248
	.byte	0x2
	.byte	0xba
	.byte	0xe
	.4byte	0x56b
	.byte	0x50
	.byte	0
	.uleb128 0x9
	.4byte	0x849
	.4byte	0x943
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x9
	.4byte	0x73
	.4byte	0x953
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF249
	.byte	0x2
	.byte	0xbb
	.byte	0x3
	.4byte	0x85a
	.uleb128 0x16
	.byte	0x34
	.byte	0x2
	.byte	0xbd
	.4byte	0x99c
	.uleb128 0x2
	.4byte	.LASF229
	.byte	0x2
	.byte	0xbe
	.byte	0x1e
	.4byte	0x800
	.byte	0
	.uleb128 0x2
	.4byte	.LASF234
	.byte	0x2
	.byte	0xbf
	.byte	0xc
	.4byte	0x849
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF236
	.byte	0x2
	.byte	0xc0
	.byte	0xc
	.4byte	0x99c
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF237
	.byte	0x2
	.byte	0xc1
	.byte	0xb
	.4byte	0x9ac
	.byte	0x20
	.byte	0
	.uleb128 0x9
	.4byte	0x849
	.4byte	0x9ac
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x9
	.4byte	0x73
	.4byte	0x9bc
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x5
	.4byte	.LASF250
	.byte	0x2
	.byte	0xc2
	.byte	0x3
	.4byte	0x95f
	.uleb128 0x4f
	.byte	0x54
	.byte	0x2
	.byte	0xc4
	.byte	0x9
	.4byte	0x9fd
	.uleb128 0x2c
	.string	"le"
	.byte	0xc5
	.byte	0x1a
	.4byte	0x84e
	.uleb128 0x2c
	.string	"rt"
	.byte	0xc6
	.byte	0x1a
	.4byte	0x953
	.uleb128 0x2c
	.string	"rtt"
	.byte	0xc7
	.byte	0x1b
	.4byte	0x9bc
	.uleb128 0x50
	.4byte	.LASF229
	.byte	0x2
	.byte	0xc8
	.byte	0x1e
	.4byte	0x800
	.byte	0
	.uleb128 0x5
	.4byte	.LASF251
	.byte	0x2
	.byte	0xc9
	.byte	0x3
	.4byte	0x9c8
	.uleb128 0x16
	.byte	0x94
	.byte	0x2
	.byte	0xcb
	.4byte	0xac8
	.uleb128 0x2
	.4byte	.LASF252
	.byte	0x2
	.byte	0xcc
	.byte	0x18
	.4byte	0x71f
	.byte	0
	.uleb128 0x2
	.4byte	.LASF253
	.byte	0x2
	.byte	0xcf
	.byte	0x14
	.4byte	0x7ae
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF254
	.byte	0x2
	.byte	0xd0
	.byte	0x14
	.4byte	0x7ae
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF255
	.byte	0x2
	.byte	0xd1
	.byte	0x14
	.4byte	0x7ae
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF256
	.byte	0x2
	.byte	0xd2
	.byte	0xe
	.4byte	0x56b
	.byte	0x28
	.uleb128 0x2
	.4byte	.LASF257
	.byte	0x2
	.byte	0xd3
	.byte	0xe
	.4byte	0xaa
	.byte	0x2c
	.uleb128 0x2
	.4byte	.LASF258
	.byte	0x2
	.byte	0xd4
	.byte	0xe
	.4byte	0xaa
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF259
	.byte	0x2
	.byte	0xd7
	.byte	0xe
	.4byte	0x56b
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF260
	.byte	0x2
	.byte	0xd8
	.byte	0xe
	.4byte	0x56b
	.byte	0x34
	.uleb128 0x2
	.4byte	.LASF261
	.byte	0x2
	.byte	0xd9
	.byte	0xe
	.4byte	0xaa
	.byte	0x38
	.uleb128 0x2
	.4byte	.LASF262
	.byte	0x2
	.byte	0xda
	.byte	0xe
	.4byte	0xaa
	.byte	0x3a
	.uleb128 0x2
	.4byte	.LASF263
	.byte	0x2
	.byte	0xdb
	.byte	0xe
	.4byte	0xaa
	.byte	0x3c
	.uleb128 0x2
	.4byte	.LASF264
	.byte	0x2
	.byte	0xdc
	.byte	0xd
	.4byte	0x9e
	.byte	0x3e
	.uleb128 0x2
	.4byte	.LASF265
	.byte	0x2
	.byte	0xdf
	.byte	0x17
	.4byte	0x9fd
	.byte	0x40
	.byte	0
	.uleb128 0x5
	.4byte	.LASF266
	.byte	0x2
	.byte	0xe0
	.byte	0x3
	.4byte	0xa09
	.uleb128 0x2d
	.4byte	.LASF293
	.byte	0x2
	.2byte	0x107
	.byte	0x18
	.4byte	0xae1
	.uleb128 0x8
	.4byte	0xac8
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0x9
	.byte	0x50
	.byte	0xe
	.4byte	0xb2a
	.uleb128 0x1
	.4byte	.LASF267
	.byte	0
	.uleb128 0x1
	.4byte	.LASF268
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF269
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF270
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF271
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF272
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF273
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF274
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF275
	.byte	0x8
	.byte	0
	.uleb128 0xf
	.byte	0x7
	.4byte	0x2d
	.byte	0xa
	.byte	0x31
	.byte	0x1
	.4byte	0xb68
	.uleb128 0x1
	.4byte	.LASF276
	.byte	0
	.uleb128 0x1
	.4byte	.LASF277
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF278
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF279
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF280
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF281
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF282
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF283
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.4byte	.LASF284
	.byte	0xb
	.byte	0x32
	.byte	0x10
	.4byte	0xb74
	.uleb128 0x8
	.4byte	0xb79
	.uleb128 0x1f
	.4byte	0xb84
	.uleb128 0x4
	.4byte	0x9e
	.byte	0
	.uleb128 0x21
	.4byte	.LASF285
	.byte	0x8
	.byte	0xb
	.byte	0x34
	.4byte	0xbab
	.uleb128 0x2
	.4byte	.LASF286
	.byte	0xb
	.byte	0x35
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x2
	.4byte	.LASF287
	.byte	0xb
	.byte	0x36
	.byte	0xe
	.4byte	0xaa
	.byte	0x4
	.byte	0
	.uleb128 0x5
	.4byte	.LASF288
	.byte	0xb
	.byte	0x37
	.byte	0x3
	.4byte	0xb84
	.uleb128 0x5
	.4byte	.LASF289
	.byte	0xb
	.byte	0x37
	.byte	0x11
	.4byte	0xbc3
	.uleb128 0x8
	.4byte	0xb84
	.uleb128 0x16
	.byte	0x14
	.byte	0xb
	.byte	0x39
	.4byte	0xbeb
	.uleb128 0x2
	.4byte	.LASF290
	.byte	0xb
	.byte	0x3c
	.byte	0x2a
	.4byte	0xbeb
	.byte	0
	.uleb128 0x2
	.4byte	.LASF291
	.byte	0xb
	.byte	0x3d
	.byte	0x11
	.4byte	0xbab
	.byte	0xc
	.byte	0
	.uleb128 0x9
	.4byte	0xb68
	.4byte	0xbfb
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.4byte	.LASF292
	.byte	0xb
	.byte	0x3e
	.byte	0x3
	.4byte	0xbc8
	.uleb128 0x22
	.4byte	.LASF294
	.byte	0x53
	.byte	0x4f
	.4byte	0x2c2
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_riscv_pka
	.uleb128 0x9
	.4byte	0x7c
	.4byte	0xc28
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x13
	.4byte	0xc18
	.uleb128 0x22
	.4byte	.LASF295
	.byte	0x53
	.byte	0x7f
	.4byte	0xc28
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_mirror_riscv_pka
	.uleb128 0x22
	.4byte	.LASF296
	.byte	0x5a
	.byte	0x12
	.4byte	0xbfb
	.uleb128 0x5
	.byte	0x3
	.4byte	riscv_pka_info
	.uleb128 0x51
	.4byte	0xad4
	.byte	0x1
	.byte	0x64
	.byte	0x11
	.uleb128 0x5
	.byte	0x3
	.4byte	pka_share_ptr
	.uleb128 0x21
	.4byte	.LASF297
	.byte	0xc
	.byte	0x1
	.byte	0x66
	.4byte	0xc84
	.uleb128 0x2
	.4byte	.LASF298
	.byte	0x1
	.byte	0x67
	.byte	0x11
	.4byte	0xbab
	.byte	0
	.uleb128 0x2
	.4byte	.LASF299
	.byte	0x1
	.byte	0x68
	.byte	0xd
	.4byte	0x92
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF300
	.byte	0x1
	.byte	0x69
	.byte	0x3
	.4byte	0xc5d
	.uleb128 0x9
	.4byte	0xc84
	.4byte	0xca0
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x22
	.4byte	.LASF301
	.byte	0x6b
	.byte	0xa
	.4byte	0xc90
	.uleb128 0x5
	.byte	0x3
	.4byte	RiscVHID
	.uleb128 0x12
	.4byte	.LASF302
	.byte	0x6c
	.byte	0x10
	.4byte	0x9e
	.uleb128 0x5
	.byte	0x3
	.4byte	RiscVHidIdx
	.uleb128 0x12
	.4byte	.LASF303
	.byte	0x6d
	.byte	0x10
	.4byte	0x9e
	.uleb128 0x5
	.byte	0x3
	.4byte	correction_idx
	.uleb128 0x52
	.4byte	.LASF304
	.byte	0x1
	.2byte	0x198
	.byte	0x9
	.4byte	0x9e
	.uleb128 0x5
	.byte	0x3
	.4byte	rtt_counter
	.uleb128 0x23
	.4byte	.LASF305
	.2byte	0x153
	.uleb128 0x53
	.4byte	.LASF389
	.byte	0x2
	.2byte	0x149
	.byte	0xa
	.4byte	0xb6
	.uleb128 0x23
	.4byte	.LASF306
	.2byte	0x142
	.uleb128 0x23
	.4byte	.LASF307
	.2byte	0x145
	.uleb128 0x24
	.4byte	.LASF311
	.byte	0x2
	.2byte	0x14c
	.byte	0x6
	.4byte	0xd1b
	.uleb128 0x4
	.4byte	0x9e
	.byte	0
	.uleb128 0x2e
	.4byte	.LASF309
	.byte	0x8
	.2byte	0x11d
	.byte	0x1b
	.4byte	0x6c6
	.4byte	0xd32
	.uleb128 0x4
	.4byte	0x694
	.byte	0
	.uleb128 0x23
	.4byte	.LASF308
	.2byte	0x14a
	.uleb128 0x2e
	.4byte	.LASF310
	.byte	0x2
	.2byte	0x13f
	.byte	0x5
	.4byte	0x564
	.4byte	0xd50
	.uleb128 0x4
	.4byte	0x56b
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF312
	.byte	0xc
	.byte	0x3f
	.4byte	0xd61
	.uleb128 0x4
	.4byte	0xb6
	.byte	0
	.uleb128 0x24
	.4byte	.LASF313
	.byte	0x2
	.2byte	0x10b
	.byte	0x6
	.4byte	0xd74
	.uleb128 0x4
	.4byte	0x694
	.byte	0
	.uleb128 0x24
	.4byte	.LASF314
	.byte	0x2
	.2byte	0x10a
	.byte	0xd
	.4byte	0xd87
	.uleb128 0x4
	.4byte	0x694
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF315
	.byte	0xc
	.byte	0x3e
	.4byte	0xd98
	.uleb128 0x4
	.4byte	0x259
	.byte	0
	.uleb128 0x2e
	.4byte	.LASF316
	.byte	0x2
	.2byte	0x13d
	.byte	0xa
	.4byte	0x56b
	.4byte	0xdaf
	.uleb128 0x4
	.4byte	0x56b
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF317
	.byte	0xd
	.byte	0x44
	.4byte	0xdca
	.uleb128 0x4
	.4byte	0x81
	.uleb128 0x4
	.4byte	0x81
	.uleb128 0x4
	.4byte	0x65
	.byte	0
	.uleb128 0x24
	.4byte	.LASF318
	.byte	0x4
	.2byte	0x129
	.byte	0xd
	.4byte	0xded
	.uleb128 0x4
	.4byte	0x73
	.uleb128 0x4
	.4byte	0x102
	.uleb128 0x4
	.4byte	0x81
	.uleb128 0x4
	.4byte	0xb6
	.uleb128 0x20
	.byte	0
	.uleb128 0x39
	.4byte	.LASF319
	.2byte	0x3a5
	.4byte	0x56b
	.4byte	.LFB49
	.4byte	.LFE49-.LFB49
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe35
	.uleb128 0x3a
	.4byte	0x18dd
	.4byte	.LBB148
	.4byte	.LLRL78
	.2byte	0x3a7
	.byte	0xc
	.uleb128 0x6
	.4byte	0x18ee
	.4byte	.LLST79
	.uleb128 0x25
	.4byte	.LLRL78
	.uleb128 0x3b
	.4byte	0x18f9
	.uleb128 0x26
	.4byte	.LVL197
	.4byte	0x192e
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x14
	.4byte	.LASF320
	.2byte	0x3a0
	.4byte	.LFB48
	.4byte	.LFE48-.LFB48
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe73
	.uleb128 0x54
	.string	"ptr"
	.byte	0x1
	.2byte	0x3a0
	.byte	0x25
	.4byte	0x56b
	.4byte	.LLST77
	.uleb128 0x27
	.4byte	.LVL194
	.4byte	0x17b9
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
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
	.uleb128 0x30
	.4byte	.LASF358
	.2byte	0x395
	.4byte	.LFB47
	.4byte	.LFE47-.LFB47
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe92
	.uleb128 0x26
	.4byte	.LVL191
	.4byte	0xce6
	.byte	0
	.uleb128 0x39
	.4byte	.LASF321
	.2byte	0x37a
	.4byte	0xb6
	.4byte	.LFB46
	.4byte	.LFE46-.LFB46
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf18
	.uleb128 0x17
	.4byte	.LASF263
	.2byte	0x37e
	.byte	0xe
	.4byte	0xaa
	.4byte	.LLST74
	.uleb128 0x17
	.4byte	.LASF322
	.2byte	0x37f
	.byte	0xe
	.4byte	0xb6
	.4byte	.LLST75
	.uleb128 0x31
	.4byte	0x11ab
	.4byte	.LBB146
	.4byte	.LBE146-.LBB146
	.2byte	0x384
	.byte	0x9
	.4byte	0xef2
	.uleb128 0x6
	.4byte	0x11b6
	.4byte	.LLST76
	.uleb128 0x7
	.4byte	.LVL188
	.4byte	0x1364
	.byte	0
	.uleb128 0x7
	.4byte	.LVL183
	.4byte	0xced
	.uleb128 0xb
	.4byte	.LVL185
	.4byte	0xf84
	.4byte	0xf0e
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x7
	.4byte	.LVL190
	.4byte	0x1193
	.byte	0
	.uleb128 0x32
	.4byte	.LASF350
	.2byte	0x367
	.byte	0xa
	.4byte	0xb6
	.4byte	.LFB45
	.4byte	.LFE45-.LFB45
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf7f
	.uleb128 0x18
	.4byte	.LASF323
	.2byte	0x367
	.byte	0x42
	.4byte	0xf7f
	.4byte	.LLST72
	.uleb128 0x18
	.4byte	.LASF324
	.2byte	0x367
	.byte	0x52
	.4byte	0x259
	.4byte	.LLST73
	.uleb128 0x55
	.4byte	0x1b4c
	.4byte	.LBB144
	.4byte	.LBE144-.LBB144
	.byte	0x1
	.2byte	0x36e
	.byte	0x9
	.uleb128 0x7
	.4byte	.LVL177
	.4byte	0xd01
	.uleb128 0x7
	.4byte	.LVL178
	.4byte	0xcfa
	.uleb128 0x7
	.4byte	.LVL179
	.4byte	0x12a4
	.byte	0
	.uleb128 0x8
	.4byte	0x6f9
	.uleb128 0x33
	.4byte	.LASF325
	.2byte	0x205
	.4byte	0x107e
	.uleb128 0x34
	.4byte	.LASF348
	.2byte	0x205
	.byte	0x34
	.4byte	0x9e
	.uleb128 0x3c
	.uleb128 0xc
	.4byte	.LASF326
	.2byte	0x221
	.byte	0x15
	.4byte	0xbab
	.uleb128 0xc
	.4byte	.LASF327
	.2byte	0x221
	.byte	0x22
	.4byte	0xbab
	.uleb128 0xc
	.4byte	.LASF291
	.2byte	0x221
	.byte	0x31
	.4byte	0xbab
	.uleb128 0xc
	.4byte	.LASF298
	.2byte	0x222
	.byte	0x15
	.4byte	0xbab
	.uleb128 0xc
	.4byte	.LASF328
	.2byte	0x223
	.byte	0xd
	.4byte	0x564
	.uleb128 0xc
	.4byte	.LASF329
	.2byte	0x224
	.byte	0x12
	.4byte	0xb6
	.uleb128 0xc
	.4byte	.LASF299
	.2byte	0x244
	.byte	0x11
	.4byte	0x92
	.uleb128 0xc
	.4byte	.LASF330
	.2byte	0x257
	.byte	0x12
	.4byte	0x107e
	.uleb128 0xc
	.4byte	.LASF331
	.2byte	0x261
	.byte	0x12
	.4byte	0x107e
	.uleb128 0xc
	.4byte	.LASF332
	.2byte	0x28a
	.byte	0x11
	.4byte	0x92
	.uleb128 0xc
	.4byte	.LASF333
	.2byte	0x28b
	.byte	0x11
	.4byte	0x9e
	.uleb128 0x56
	.string	"i"
	.byte	0x1
	.2byte	0x297
	.byte	0x12
	.4byte	0xb6
	.uleb128 0xc
	.4byte	.LASF334
	.2byte	0x313
	.byte	0x11
	.4byte	0x9e
	.uleb128 0x3d
	.4byte	0x105c
	.uleb128 0x2d
	.4byte	.LASF294
	.byte	0x1
	.2byte	0x23c
	.byte	0x2d
	.4byte	0x2c2
	.uleb128 0x1c
	.4byte	.LASF335
	.2byte	0x23c
	.byte	0x89
	.4byte	0x109e
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.byte	0
	.uleb128 0x3d
	.4byte	0x106e
	.uleb128 0xc
	.4byte	.LASF336
	.2byte	0x2da
	.byte	0x1d
	.4byte	0x9e
	.byte	0
	.uleb128 0x3c
	.uleb128 0xc
	.4byte	.LASF337
	.2byte	0x2fa
	.byte	0x1a
	.4byte	0xb6
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0xb6
	.4byte	0x108e
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x9
	.4byte	0x7c
	.4byte	0x109e
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3d
	.byte	0
	.uleb128 0x13
	.4byte	0x108e
	.uleb128 0x14
	.4byte	.LASF338
	.2byte	0x1ec
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10f8
	.uleb128 0x18
	.4byte	.LASF339
	.2byte	0x1ec
	.byte	0x31
	.4byte	0xbb7
	.4byte	.LLST70
	.uleb128 0x1c
	.4byte	.LASF340
	.2byte	0x1ee
	.byte	0x11
	.4byte	0xbab
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x17
	.4byte	.LASF341
	.2byte	0x1ee
	.byte	0x1a
	.4byte	0xbab
	.4byte	.LLST71
	.uleb128 0x10
	.4byte	.LVL171
	.4byte	0x1121
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x14
	.4byte	.LASF342
	.2byte	0x1e6
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x111c
	.uleb128 0x28
	.4byte	.LASF298
	.2byte	0x1e6
	.byte	0x2a
	.4byte	0x111c
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x8
	.4byte	0xbab
	.uleb128 0x14
	.4byte	.LASF343
	.2byte	0x1e0
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1145
	.uleb128 0x28
	.4byte	.LASF291
	.2byte	0x1e0
	.byte	0x32
	.4byte	0x111c
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x14
	.4byte	.LASF344
	.2byte	0x1da
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1169
	.uleb128 0x28
	.4byte	.LASF326
	.2byte	0x1da
	.byte	0x32
	.4byte	0x111c
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x3e
	.4byte	.LASF345
	.2byte	0x1d5
	.4byte	0x9e
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x3e
	.4byte	.LASF346
	.2byte	0x1d0
	.4byte	0x9e
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x33
	.4byte	.LASF347
	.2byte	0x199
	.4byte	0x11ab
	.uleb128 0x34
	.4byte	.LASF348
	.2byte	0x199
	.byte	0x35
	.4byte	0x9e
	.byte	0
	.uleb128 0x33
	.4byte	.LASF349
	.2byte	0x180
	.4byte	0x11c3
	.uleb128 0x34
	.4byte	.LASF348
	.2byte	0x180
	.byte	0x34
	.4byte	0x9e
	.byte	0
	.uleb128 0x57
	.4byte	.LASF395
	.byte	0x1
	.2byte	0x17b
	.byte	0xb
	.4byte	0x56b
	.4byte	.LFB35
	.4byte	.LFE35-.LFB35
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x32
	.4byte	.LASF351
	.2byte	0x175
	.byte	0x9
	.4byte	0x9e
	.4byte	.LFB34
	.4byte	.LFE34-.LFB34
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x11fe
	.uleb128 0x7
	.4byte	.LVL102
	.4byte	0xd39
	.byte	0
	.uleb128 0x32
	.4byte	.LASF352
	.2byte	0x170
	.byte	0x5
	.4byte	0x564
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1222
	.uleb128 0x7
	.4byte	.LVL101
	.4byte	0xd39
	.byte	0
	.uleb128 0x14
	.4byte	.LASF353
	.2byte	0x16a
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1255
	.uleb128 0x58
	.string	"ptr"
	.byte	0x1
	.2byte	0x16a
	.byte	0x2d
	.4byte	0x7fb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x28
	.4byte	.LASF354
	.2byte	0x16a
	.byte	0x3b
	.4byte	0xaa
	.uleb128 0x1
	.byte	0x5b
	.byte	0
	.uleb128 0x14
	.4byte	.LASF355
	.2byte	0x160
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x12a4
	.uleb128 0x18
	.4byte	.LASF356
	.2byte	0x160
	.byte	0x21
	.4byte	0xb6
	.4byte	.LLST53
	.uleb128 0x18
	.4byte	.LASF357
	.2byte	0x160
	.byte	0x3c
	.4byte	0xaa
	.4byte	.LLST54
	.uleb128 0x18
	.4byte	.LASF299
	.2byte	0x160
	.byte	0x55
	.4byte	0x92
	.4byte	.LLST55
	.uleb128 0x7
	.4byte	.LVL97
	.4byte	0x1e35
	.byte	0
	.uleb128 0x30
	.4byte	.LASF359
	.2byte	0x148
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1364
	.uleb128 0x35
	.string	"ptr"
	.2byte	0x14c
	.byte	0xe
	.4byte	0x56b
	.4byte	.LLST47
	.uleb128 0x35
	.string	"i"
	.2byte	0x14d
	.byte	0xc
	.4byte	0x86
	.4byte	.LLST48
	.uleb128 0x29
	.4byte	0x18dd
	.4byte	.LBB108
	.4byte	.LLRL49
	.2byte	0x150
	.byte	0xf
	.4byte	0x130d
	.uleb128 0x6
	.4byte	0x18ee
	.4byte	.LLST50
	.uleb128 0x25
	.4byte	.LLRL49
	.uleb128 0xd
	.4byte	0x18f9
	.4byte	.LLST51
	.uleb128 0x7
	.4byte	.LVL84
	.4byte	0x192e
	.byte	0
	.byte	0
	.uleb128 0x31
	.4byte	0x1b30
	.4byte	.LBB112
	.4byte	.LBE112-.LBB112
	.2byte	0x152
	.byte	0x11
	.4byte	0x1327
	.uleb128 0x59
	.4byte	0x1b3f
	.byte	0
	.uleb128 0x31
	.4byte	0x1b14
	.4byte	.LBB114
	.4byte	.LBE114-.LBB114
	.2byte	0x155
	.byte	0x11
	.4byte	0x1345
	.uleb128 0x6
	.4byte	0x1b23
	.4byte	.LLST52
	.byte	0
	.uleb128 0xb
	.4byte	.LVL88
	.4byte	0x17b9
	.4byte	0x135a
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x7
	.4byte	.LVL93
	.4byte	0x17b9
	.byte	0
	.uleb128 0x30
	.4byte	.LASF360
	.2byte	0x10c
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x148f
	.uleb128 0x35
	.string	"ptr"
	.2byte	0x114
	.byte	0xe
	.4byte	0x56b
	.4byte	.LLST37
	.uleb128 0x1c
	.4byte	.LASF361
	.2byte	0x11c
	.byte	0xe
	.4byte	0xb6
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x17
	.4byte	.LASF362
	.2byte	0x120
	.byte	0xe
	.4byte	0x56b
	.4byte	.LLST38
	.uleb128 0x17
	.4byte	.LASF363
	.2byte	0x134
	.byte	0xe
	.4byte	0x56b
	.4byte	.LLST39
	.uleb128 0x29
	.4byte	0x18dd
	.4byte	.LBB100
	.4byte	.LLRL40
	.2byte	0x114
	.byte	0x14
	.4byte	0x13ee
	.uleb128 0x6
	.4byte	0x18ee
	.4byte	.LLST41
	.uleb128 0x25
	.4byte	.LLRL40
	.uleb128 0xd
	.4byte	0x18f9
	.4byte	.LLST42
	.uleb128 0x7
	.4byte	.LVL59
	.4byte	0x192e
	.byte	0
	.byte	0
	.uleb128 0x29
	.4byte	0x18dd
	.4byte	.LBB104
	.4byte	.LLRL43
	.2byte	0x128
	.byte	0xf
	.4byte	0x1424
	.uleb128 0x6
	.4byte	0x18ee
	.4byte	.LLST44
	.uleb128 0x25
	.4byte	.LLRL43
	.uleb128 0xd
	.4byte	0x18f9
	.4byte	.LLST45
	.uleb128 0x7
	.4byte	.LVL66
	.4byte	0x192e
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL61
	.4byte	0xd87
	.4byte	0x1438
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xb
	.4byte	.LVL62
	.4byte	0xd74
	.4byte	0x144b
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.uleb128 0xb
	.4byte	.LVL64
	.4byte	0x17b9
	.4byte	0x1460
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xb
	.4byte	.LVL69
	.4byte	0xd61
	.4byte	0x1473
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.uleb128 0x7
	.4byte	.LVL70
	.4byte	0xd50
	.uleb128 0x7
	.4byte	.LVL75
	.4byte	0x17b9
	.uleb128 0x7
	.4byte	.LVL77
	.4byte	0x1656
	.byte	0
	.uleb128 0x14
	.4byte	.LASF364
	.2byte	0x100
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1565
	.uleb128 0x18
	.4byte	.LASF365
	.2byte	0x100
	.byte	0x33
	.4byte	0x7ba
	.4byte	.LLST34
	.uleb128 0x17
	.4byte	.LASF222
	.2byte	0x101
	.byte	0x1e
	.4byte	0x77b
	.4byte	.LLST35
	.uleb128 0x3f
	.4byte	.LBB98
	.4byte	.LBE98-.LBB98
	.uleb128 0x1c
	.4byte	.LASF366
	.2byte	0x103
	.byte	0x22
	.4byte	0x763
	.uleb128 0x1
	.byte	0x58
	.uleb128 0x5a
	.string	"ptr"
	.byte	0x1
	.2byte	0x104
	.byte	0x12
	.4byte	0x56b
	.uleb128 0x1
	.byte	0x58
	.uleb128 0x17
	.4byte	.LASF367
	.2byte	0x105
	.byte	0x12
	.4byte	0x56b
	.4byte	.LLST36
	.uleb128 0x15
	.4byte	.LBB99
	.4byte	.LBE99-.LBB99
	.4byte	0x1553
	.uleb128 0x2d
	.4byte	.LASF294
	.byte	0x1
	.2byte	0x106
	.byte	0x29
	.4byte	0x2c2
	.uleb128 0x1c
	.4byte	.LASF335
	.2byte	0x106
	.byte	0x85
	.4byte	0x1575
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x10
	.4byte	.LVL55
	.4byte	0xdca
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_riscv_pka
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x38
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LVL53
	.4byte	0xd98
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0x7c
	.4byte	0x1575
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x7d
	.byte	0
	.uleb128 0x13
	.4byte	0x1565
	.uleb128 0x36
	.4byte	.LASF368
	.byte	0xf5
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1641
	.uleb128 0x19
	.4byte	.LASF365
	.byte	0xf5
	.byte	0x32
	.4byte	0x7ba
	.4byte	.LLST31
	.uleb128 0x37
	.4byte	.LASF222
	.byte	0xf6
	.byte	0x1e
	.4byte	0x77b
	.4byte	.LLST32
	.uleb128 0x3f
	.4byte	.LBB96
	.4byte	.LBE96-.LBB96
	.uleb128 0x12
	.4byte	.LASF366
	.byte	0xf8
	.byte	0x22
	.4byte	0x763
	.uleb128 0x1
	.byte	0x59
	.uleb128 0x1a
	.string	"ptr"
	.byte	0xf9
	.byte	0x12
	.4byte	0x56b
	.uleb128 0x1
	.byte	0x59
	.uleb128 0x37
	.4byte	.LASF367
	.byte	0xfa
	.byte	0x12
	.4byte	0x56b
	.4byte	.LLST33
	.uleb128 0x15
	.4byte	.LBB97
	.4byte	.LBE97-.LBB97
	.4byte	0x162f
	.uleb128 0x5b
	.4byte	.LASF294
	.byte	0x1
	.byte	0xfb
	.byte	0x29
	.4byte	0x2c2
	.uleb128 0x12
	.4byte	.LASF335
	.byte	0xfb
	.byte	0x85
	.4byte	0x1651
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.2
	.uleb128 0x10
	.4byte	.LVL47
	.4byte	0xdca
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_riscv_pka
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.2
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LVL45
	.4byte	0xd98
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0x7c
	.4byte	0x1651
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x42
	.byte	0
	.uleb128 0x13
	.4byte	0x1641
	.uleb128 0x36
	.4byte	.LASF369
	.byte	0xe6
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x177a
	.uleb128 0x19
	.4byte	.LASF365
	.byte	0xe6
	.byte	0x31
	.4byte	0x7ba
	.4byte	.LLST22
	.uleb128 0x40
	.string	"ptr"
	.byte	0xe6
	.byte	0x3f
	.4byte	0x73
	.4byte	.LLST23
	.uleb128 0x15
	.4byte	.LBB86
	.4byte	.LBE86-.LBB86
	.4byte	0x16da
	.uleb128 0x1a
	.string	"exp"
	.byte	0xea
	.byte	0x4e
	.4byte	0x178a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.6
	.uleb128 0x12
	.4byte	.LASF370
	.byte	0xea
	.byte	0xa7
	.4byte	0x179f
	.uleb128 0x5
	.byte	0x3
	.4byte	file.5
	.uleb128 0x10
	.4byte	.LVL34
	.4byte	0xdaf
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.6
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.5
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xea
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LBB87
	.4byte	.LBE87-.LBB87
	.4byte	0x172c
	.uleb128 0x1a
	.string	"exp"
	.byte	0xeb
	.byte	0x4e
	.4byte	0x17b4
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.4
	.uleb128 0x12
	.4byte	.LASF370
	.byte	0xeb
	.byte	0xa4
	.4byte	0x179f
	.uleb128 0x5
	.byte	0x3
	.4byte	file.3
	.uleb128 0x10
	.4byte	.LVL35
	.4byte	0xdaf
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.4
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.3
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xeb
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	0x1a5d
	.4byte	.LBB88
	.4byte	.LLRL24
	.byte	0xee
	.byte	0x5
	.uleb128 0x6
	.4byte	0x1a72
	.4byte	.LLST25
	.uleb128 0x6
	.4byte	0x1a67
	.4byte	.LLST26
	.uleb128 0x1b
	.4byte	0x1a9f
	.4byte	.LBB90
	.4byte	.LLRL27
	.byte	0xa0
	.byte	0x5
	.uleb128 0x6
	.4byte	0x1abf
	.4byte	.LLST28
	.uleb128 0x6
	.4byte	0x1ab4
	.4byte	.LLST29
	.uleb128 0x6
	.4byte	0x1aa9
	.4byte	.LLST30
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0x7c
	.4byte	0x178a
	.uleb128 0xa
	.4byte	0x2d
	.byte	0xe
	.byte	0
	.uleb128 0x13
	.4byte	0x177a
	.uleb128 0x9
	.4byte	0x7c
	.4byte	0x179f
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x36
	.byte	0
	.uleb128 0x13
	.4byte	0x178f
	.uleb128 0x9
	.4byte	0x7c
	.4byte	0x17b4
	.uleb128 0xa
	.4byte	0x2d
	.byte	0xb
	.byte	0
	.uleb128 0x13
	.4byte	0x17a4
	.uleb128 0x36
	.4byte	.LASF371
	.byte	0xd7
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x18dd
	.uleb128 0x19
	.4byte	.LASF365
	.byte	0xd7
	.byte	0x2c
	.4byte	0x7ba
	.4byte	.LLST13
	.uleb128 0x40
	.string	"ptr"
	.byte	0xd7
	.byte	0x3a
	.4byte	0x73
	.4byte	.LLST14
	.uleb128 0x15
	.4byte	.LBB72
	.4byte	.LBE72-.LBB72
	.4byte	0x183d
	.uleb128 0x1a
	.string	"exp"
	.byte	0xdb
	.byte	0x4e
	.4byte	0x178a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.10
	.uleb128 0x12
	.4byte	.LASF370
	.byte	0xdb
	.byte	0xa7
	.4byte	0x179f
	.uleb128 0x5
	.byte	0x3
	.4byte	file.9
	.uleb128 0x10
	.4byte	.LVL24
	.4byte	0xdaf
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.10
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.9
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xdb
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LBB73
	.4byte	.LBE73-.LBB73
	.4byte	0x188f
	.uleb128 0x1a
	.string	"exp"
	.byte	0xdc
	.byte	0x4e
	.4byte	0x17b4
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.8
	.uleb128 0x12
	.4byte	.LASF370
	.byte	0xdc
	.byte	0xa4
	.4byte	0x179f
	.uleb128 0x5
	.byte	0x3
	.4byte	file.7
	.uleb128 0x10
	.4byte	.LVL25
	.4byte	0xdaf
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.8
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.7
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xdc
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	0x1a7e
	.4byte	.LBB74
	.4byte	.LLRL15
	.byte	0xdf
	.byte	0x5
	.uleb128 0x6
	.4byte	0x1a93
	.4byte	.LLST16
	.uleb128 0x6
	.4byte	0x1a88
	.4byte	.LLST17
	.uleb128 0x1b
	.4byte	0x1a9f
	.4byte	.LBB76
	.4byte	.LLRL18
	.byte	0x9a
	.byte	0x5
	.uleb128 0x6
	.4byte	0x1abf
	.4byte	.LLST19
	.uleb128 0x6
	.4byte	0x1ab4
	.4byte	.LLST20
	.uleb128 0x6
	.4byte	0x1aa9
	.4byte	.LLST21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x5c
	.4byte	.LASF372
	.byte	0x1
	.byte	0xcf
	.byte	0x7
	.4byte	0x73
	.byte	0x1
	.4byte	0x1905
	.uleb128 0x11
	.4byte	.LASF365
	.byte	0xcf
	.byte	0x2d
	.4byte	0x7ba
	.uleb128 0x41
	.4byte	.LASF373
	.byte	0xd1
	.byte	0xb
	.4byte	0x73
	.byte	0
	.uleb128 0x38
	.4byte	.LASF374
	.byte	0xca
	.byte	0x7
	.4byte	0x73
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x192e
	.uleb128 0x19
	.4byte	.LASF365
	.byte	0xca
	.byte	0x2e
	.4byte	0x7ba
	.4byte	.LLST11
	.byte	0
	.uleb128 0x38
	.4byte	.LASF375
	.byte	0xaf
	.byte	0x7
	.4byte	0x73
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x19cb
	.uleb128 0x19
	.4byte	.LASF365
	.byte	0xb0
	.byte	0x18
	.4byte	0x7ba
	.4byte	.LLST10
	.uleb128 0x41
	.4byte	.LASF376
	.byte	0xb2
	.byte	0x1e
	.4byte	0x763
	.uleb128 0x15
	.4byte	.LBB71
	.4byte	.LBE71-.LBB71
	.4byte	0x19b3
	.uleb128 0x1a
	.string	"exp"
	.byte	0xb6
	.byte	0x4e
	.4byte	0x178a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.12
	.uleb128 0x12
	.4byte	.LASF370
	.byte	0xb6
	.byte	0xa7
	.4byte	0x179f
	.uleb128 0x5
	.byte	0x3
	.4byte	file.11
	.uleb128 0x10
	.4byte	.LVL13
	.4byte	0xdaf
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.12
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.11
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xb6
	.byte	0
	.byte	0
	.uleb128 0x27
	.4byte	.LVL15
	.4byte	0x19cb
	.uleb128 0x3
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
	.uleb128 0x38
	.4byte	.LASF377
	.byte	0xa3
	.byte	0x1a
	.4byte	0x763
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1a5d
	.uleb128 0x19
	.4byte	.LASF222
	.byte	0xa4
	.byte	0x1e
	.4byte	0x77b
	.4byte	.LLST3
	.uleb128 0x15
	.4byte	.LBB64
	.4byte	.LBE64-.LBB64
	.4byte	0x1a43
	.uleb128 0x37
	.4byte	.LASF366
	.byte	0xa7
	.byte	0x22
	.4byte	0x763
	.4byte	.LLST6
	.uleb128 0x1b
	.4byte	0x1acb
	.4byte	.LBB65
	.4byte	.LLRL7
	.byte	0xa8
	.byte	0x9
	.uleb128 0x6
	.4byte	0x1ad5
	.4byte	.LLST8
	.uleb128 0x5d
	.4byte	0x1afe
	.4byte	.LBB67
	.4byte	.LBE67-.LBB67
	.byte	0x1
	.byte	0x8a
	.byte	0x5
	.uleb128 0x6
	.4byte	0x1b08
	.4byte	.LLST9
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	0x1ae1
	.4byte	.LBB60
	.4byte	.LLRL4
	.byte	0xa6
	.byte	0xa
	.uleb128 0x6
	.4byte	0x1af2
	.4byte	.LLST5
	.byte	0
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF379
	.byte	0x9c
	.4byte	0x1a7e
	.uleb128 0x11
	.4byte	.LASF378
	.byte	0x9d
	.byte	0x1e
	.4byte	0x763
	.uleb128 0x11
	.4byte	.LASF222
	.byte	0x9e
	.byte	0x1e
	.4byte	0x77b
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF380
	.byte	0x96
	.4byte	0x1a9f
	.uleb128 0x11
	.4byte	.LASF378
	.byte	0x97
	.byte	0x1e
	.4byte	0x763
	.uleb128 0x11
	.4byte	.LASF222
	.byte	0x98
	.byte	0x1e
	.4byte	0x77b
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF381
	.byte	0x8c
	.4byte	0x1acb
	.uleb128 0x11
	.4byte	.LASF366
	.byte	0x8d
	.byte	0x1e
	.4byte	0x763
	.uleb128 0x11
	.4byte	.LASF382
	.byte	0x8e
	.byte	0x1e
	.4byte	0x763
	.uleb128 0x11
	.4byte	.LASF383
	.byte	0x8f
	.byte	0x1e
	.4byte	0x763
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF384
	.byte	0x85
	.4byte	0x1ae1
	.uleb128 0x11
	.4byte	.LASF366
	.byte	0x86
	.byte	0x1e
	.4byte	0x763
	.byte	0
	.uleb128 0x5e
	.4byte	.LASF396
	.byte	0x1
	.byte	0x80
	.byte	0x13
	.4byte	0x564
	.byte	0x3
	.4byte	0x1afe
	.uleb128 0x11
	.4byte	.LASF385
	.byte	0x81
	.byte	0x1e
	.4byte	0x763
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF386
	.byte	0x7b
	.4byte	0x1b14
	.uleb128 0x11
	.4byte	.LASF385
	.byte	0x7c
	.byte	0x1e
	.4byte	0x763
	.byte	0
	.uleb128 0x42
	.4byte	.LASF387
	.2byte	0x11c
	.4byte	0x9e
	.4byte	0x1b30
	.uleb128 0x43
	.string	"ptr"
	.2byte	0x11c
	.byte	0x36
	.4byte	0x56b
	.byte	0
	.uleb128 0x42
	.4byte	.LASF388
	.2byte	0x116
	.4byte	0x9e
	.4byte	0x1b4c
	.uleb128 0x43
	.string	"ptr"
	.2byte	0x116
	.byte	0x33
	.4byte	0x56b
	.byte	0
	.uleb128 0x5f
	.4byte	.LASF390
	.byte	0x2
	.2byte	0x111
	.byte	0x1b
	.4byte	0x71f
	.byte	0x3
	.uleb128 0x2a
	.4byte	0x1193
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1b9a
	.uleb128 0x6
	.4byte	0x119e
	.4byte	.LLST0
	.uleb128 0x3a
	.4byte	0x1193
	.4byte	.LBB45
	.4byte	.LLRL1
	.2byte	0x199
	.byte	0x6
	.uleb128 0x6
	.4byte	0x119e
	.4byte	.LLST2
	.uleb128 0x7
	.4byte	.LVL2
	.4byte	0xd32
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x18dd
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1bd3
	.uleb128 0x6
	.4byte	0x18ee
	.4byte	.LLST12
	.uleb128 0x3b
	.4byte	0x18f9
	.uleb128 0x27
	.4byte	.LVL20
	.4byte	0x192e
	.uleb128 0x3
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
	.uleb128 0x2a
	.4byte	0x11ab
	.4byte	.LFB36
	.4byte	.LFE36-.LFB36
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1bf9
	.uleb128 0x6
	.4byte	0x11b6
	.4byte	.LLST46
	.uleb128 0x26
	.4byte	.LVL79
	.4byte	0x1364
	.byte	0
	.uleb128 0x2a
	.4byte	0xf84
	.4byte	.LFB44
	.4byte	.LFE44-.LFB44
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1e35
	.uleb128 0x6
	.4byte	0xf8f
	.4byte	.LLST56
	.uleb128 0x29
	.4byte	0xf84
	.4byte	.LBB122
	.4byte	.LLRL57
	.2byte	0x205
	.byte	0x6
	.4byte	0x1e2b
	.uleb128 0x6
	.4byte	0xf8f
	.4byte	.LLST58
	.uleb128 0x60
	.4byte	0xf9b
	.4byte	.LLRL57
	.uleb128 0xd
	.4byte	0xf9c
	.4byte	.LLST59
	.uleb128 0x1e
	.4byte	0xfa8
	.uleb128 0x3
	.byte	0x91
	.sleb128 -100
	.uleb128 0x1e
	.4byte	0xfb4
	.uleb128 0x3
	.byte	0x91
	.sleb128 -92
	.uleb128 0x1e
	.4byte	0xfc0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0xd
	.4byte	0xfcc
	.4byte	.LLST60
	.uleb128 0xd
	.4byte	0xfd8
	.4byte	.LLST61
	.uleb128 0xd
	.4byte	0xfe4
	.4byte	.LLST62
	.uleb128 0x1e
	.4byte	0xff0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x1e
	.4byte	0xffc
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0xd
	.4byte	0x1008
	.4byte	.LLST63
	.uleb128 0xd
	.4byte	0x1014
	.4byte	.LLST64
	.uleb128 0xd
	.4byte	0x1020
	.4byte	.LLST65
	.uleb128 0xd
	.4byte	0x102b
	.4byte	.LLST66
	.uleb128 0x61
	.4byte	0x1037
	.4byte	.LLRL67
	.4byte	0x1ce8
	.uleb128 0x62
	.4byte	0x103c
	.uleb128 0x27
	.4byte	.LVL120
	.4byte	0xdca
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_riscv_pka
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x44
	.4byte	0x105c
	.4byte	.LBB128
	.4byte	.LBE128-.LBB128
	.4byte	0x1d03
	.uleb128 0xd
	.4byte	0x1061
	.4byte	.LLST68
	.byte	0
	.uleb128 0x44
	.4byte	0x106e
	.4byte	.LBB129
	.4byte	.LBE129-.LBB129
	.4byte	0x1d64
	.uleb128 0xd
	.4byte	0x106f
	.4byte	.LLST69
	.uleb128 0xb
	.4byte	.LVL163
	.4byte	0xd1b
	.4byte	0x1d30
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.uleb128 0xb
	.4byte	.LVL164
	.4byte	0xd61
	.4byte	0x1d43
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.uleb128 0x10
	.4byte	.LVL165
	.4byte	0x1255
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x91
	.sleb128 -108
	.byte	0x94
	.byte	0x2
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL112
	.4byte	0x1145
	.4byte	0x1d79
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -100
	.byte	0
	.uleb128 0xb
	.4byte	.LVL113
	.4byte	0x1121
	.4byte	0x1d8e
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -92
	.byte	0
	.uleb128 0xb
	.4byte	.LVL117
	.4byte	0x10f8
	.4byte	0x1da3
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -84
	.byte	0
	.uleb128 0xb
	.4byte	.LVL127
	.4byte	0x1e3e
	.4byte	0x1dc7
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	.LANCHOR0
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x20
	.byte	0
	.uleb128 0xb
	.4byte	.LVL128
	.4byte	0x1e3e
	.4byte	0x1dea
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	.LANCHOR0+32
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x20
	.byte	0
	.uleb128 0x7
	.4byte	.LVL132
	.4byte	0x1e49
	.uleb128 0xb
	.4byte	.LVL144
	.4byte	0x1255
	.4byte	0x1e17
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x91
	.sleb128 -108
	.byte	0x94
	.byte	0x2
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL154
	.4byte	0x117e
	.uleb128 0x26
	.4byte	.LVL157
	.4byte	0xd08
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL107
	.4byte	0x1169
	.byte	0
	.uleb128 0x45
	.4byte	.LASF391
	.4byte	.LASF391
	.uleb128 0x63
	.4byte	.LASF397
	.4byte	.LASF398
	.byte	0xf
	.byte	0
	.uleb128 0x45
	.4byte	.LASF392
	.4byte	.LASF392
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
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
	.uleb128 0x31
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
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
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
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0xb
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
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.sleb128 20
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 16
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
	.uleb128 0x2
	.uleb128 0x18
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
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 0x25
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x2a
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
	.uleb128 0x2b
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
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
	.uleb128 0x2e
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
	.uleb128 0x2f
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
	.uleb128 0x30
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
	.uleb128 0x31
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
	.uleb128 0x32
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
	.uleb128 0x33
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
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
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
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x38
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
	.uleb128 0x39
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3a
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
	.uleb128 0x3b
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x21
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x3d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x1
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
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
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
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x40
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
	.uleb128 0x41
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
	.uleb128 0x42
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x43
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x44
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x45
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
	.uleb128 0x46
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
	.uleb128 0x47
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
	.uleb128 0x48
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x49
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4a
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
	.uleb128 0x4b
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
	.uleb128 0x4c
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
	.uleb128 0x4d
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
	.uleb128 0x4e
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
	.uleb128 0x4f
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
	.uleb128 0x50
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
	.uleb128 0x51
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
	.uleb128 0x52
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
	.uleb128 0x53
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
	.uleb128 0x54
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
	.uleb128 0x55
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
	.uleb128 0x5
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x56
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
	.byte	0
	.byte	0
	.uleb128 0x57
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
	.uleb128 0x58
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
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5a
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
	.uleb128 0x5b
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
	.uleb128 0x5c
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
	.uleb128 0x5d
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
	.uleb128 0x5e
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5f
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
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x60
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x61
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
	.uleb128 0x62
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x63
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
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
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
.LLST79:
	.byte	0x6
	.4byte	.LVL195
	.byte	0x4
	.uleb128 .LVL195-.LVL195
	.uleb128 .LVL196-.LVL195
	.uleb128 0x9
	.byte	0x3
	.4byte	pka_share_ptr
	.byte	0x6
	.byte	0x23
	.uleb128 0x4
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL196-.LVL195
	.uleb128 .LVL197-1-.LVL195
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST77:
	.byte	0x6
	.4byte	.LVL192
	.byte	0x4
	.uleb128 .LVL192-.LVL192
	.uleb128 .LVL193-.LVL192
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL193-.LVL192
	.uleb128 .LVL194-1-.LVL192
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL194-1-.LVL192
	.uleb128 .LFE48-.LVL192
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
.LLST74:
	.byte	0x6
	.4byte	.LVL182
	.byte	0x4
	.uleb128 .LVL182-.LVL182
	.uleb128 .LVL183-1-.LVL182
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL186-.LVL182
	.uleb128 .LVL188-1-.LVL182
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL189-.LVL182
	.uleb128 .LVL190-1-.LVL182
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST75:
	.byte	0x6
	.4byte	.LVL182
	.byte	0x4
	.uleb128 .LVL182-.LVL182
	.uleb128 .LVL184-.LVL182
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL184-.LVL182
	.uleb128 .LVL185-.LVL182
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL186-.LVL182
	.uleb128 .LFE46-.LVL182
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST76:
	.byte	0x8
	.4byte	.LVL187
	.uleb128 .LVL188-.LVL187
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST72:
	.byte	0x6
	.4byte	.LVL176
	.byte	0x4
	.uleb128 .LVL176-.LVL176
	.uleb128 .LVL177-1-.LVL176
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL177-1-.LVL176
	.uleb128 .LVL180-.LVL176
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
	.uleb128 .LVL180-.LVL176
	.uleb128 .LVL181-.LVL176
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL181-.LVL176
	.uleb128 .LFE45-.LVL176
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
.LLST73:
	.byte	0x6
	.4byte	.LVL176
	.byte	0x4
	.uleb128 .LVL176-.LVL176
	.uleb128 .LVL177-1-.LVL176
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL177-1-.LVL176
	.uleb128 .LVL180-.LVL176
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
	.uleb128 .LVL180-.LVL176
	.uleb128 .LFE45-.LVL176
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST70:
	.byte	0x6
	.4byte	.LVL166
	.byte	0x4
	.uleb128 .LVL166-.LVL166
	.uleb128 .LVL169-.LVL166
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL169-.LVL166
	.uleb128 .LVL171-1-.LVL166
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL171-1-.LVL166
	.uleb128 .LVL174-.LVL166
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL174-.LVL166
	.uleb128 .LVL175-.LVL166
	.uleb128 0x2
	.byte	0x72
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL175-.LVL166
	.uleb128 .LFE43-.LVL166
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST71:
	.byte	0x6
	.4byte	.LVL167
	.byte	0x4
	.uleb128 .LVL167-.LVL167
	.uleb128 .LVL168-.LVL167
	.uleb128 0x5
	.byte	0x58
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL168-.LVL167
	.uleb128 .LVL170-.LVL167
	.uleb128 0x8
	.byte	0x58
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL170-.LVL167
	.uleb128 .LVL172-.LVL167
	.uleb128 0x10
	.byte	0x78
	.sleb128 0
	.byte	0xc
	.4byte	0xffffffc
	.byte	0x1a
	.byte	0x9f
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL172-.LVL167
	.uleb128 .LVL173-.LVL167
	.uleb128 0x7
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL175-.LVL167
	.uleb128 .LFE43-.LVL167
	.uleb128 0x7
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0
.LLST53:
	.byte	0x6
	.4byte	.LVL94
	.byte	0x4
	.uleb128 .LVL94-.LVL94
	.uleb128 .LVL95-.LVL94
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL95-.LVL94
	.uleb128 .LVL99-.LVL94
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL99-.LVL94
	.uleb128 .LFE31-.LVL94
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0
.LLST54:
	.byte	0x6
	.4byte	.LVL94
	.byte	0x4
	.uleb128 .LVL94-.LVL94
	.uleb128 .LVL96-.LVL94
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL96-.LVL94
	.uleb128 .LVL98-.LVL94
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL98-.LVL94
	.uleb128 .LFE31-.LVL94
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x3b
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST55:
	.byte	0x6
	.4byte	.LVL94
	.byte	0x4
	.uleb128 .LVL94-.LVL94
	.uleb128 .LVL97-1-.LVL94
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL97-1-.LVL94
	.uleb128 .LVL98-.LVL94
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL98-.LVL94
	.uleb128 .LFE31-.LVL94
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST47:
	.byte	0x6
	.4byte	.LVL85
	.byte	0x4
	.uleb128 .LVL85-.LVL85
	.uleb128 .LVL87-.LVL85
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL87-.LVL85
	.uleb128 .LVL88-1-.LVL85
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL88-1-.LVL85
	.uleb128 .LVL89-.LVL85
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL92-.LVL85
	.uleb128 .LVL93-1-.LVL85
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST48:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL81-.LVL80
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL82-.LVL80
	.uleb128 .LVL90-.LVL80
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL91-.LVL80
	.uleb128 .LFE30-.LVL80
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST50:
	.byte	0x6
	.4byte	.LVL82
	.byte	0x4
	.uleb128 .LVL82-.LVL82
	.uleb128 .LVL83-.LVL82
	.uleb128 0x9
	.byte	0x3
	.4byte	pka_share_ptr
	.byte	0x6
	.byte	0x23
	.uleb128 0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL83-.LVL82
	.uleb128 .LVL84-1-.LVL82
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST51:
	.byte	0x8
	.4byte	.LVL82
	.uleb128 .LVL85-.LVL82
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST52:
	.byte	0x8
	.4byte	.LVL88
	.uleb128 .LVL89-.LVL88
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST37:
	.byte	0x6
	.4byte	.LVL59
	.byte	0x4
	.uleb128 .LVL59-.LVL59
	.uleb128 .LVL60-.LVL59
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL60-.LVL59
	.uleb128 .LVL67-.LVL59
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL67-.LVL59
	.uleb128 .LVL68-.LVL59
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL71-.LVL59
	.uleb128 .LVL75-1-.LVL59
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL76-.LVL59
	.uleb128 .LVL77-1-.LVL59
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST38:
	.byte	0x8
	.4byte	.LVL63
	.uleb128 .LVL64-1-.LVL63
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST39:
	.byte	0x6
	.4byte	.LVL72
	.byte	0x4
	.uleb128 .LVL72-.LVL72
	.uleb128 .LVL73-.LVL72
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL73-.LVL72
	.uleb128 .LVL74-.LVL72
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL76-.LVL72
	.uleb128 .LVL77-1-.LVL72
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST41:
	.byte	0x6
	.4byte	.LVL56
	.byte	0x4
	.uleb128 .LVL56-.LVL56
	.uleb128 .LVL57-.LVL56
	.uleb128 0x9
	.byte	0x3
	.4byte	pka_share_ptr
	.byte	0x6
	.byte	0x23
	.uleb128 0x10
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL57-.LVL56
	.uleb128 .LVL58-.LVL56
	.uleb128 0x9
	.byte	0x3
	.4byte	pka_share_ptr
	.byte	0x6
	.byte	0x23
	.uleb128 0x10
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL58-.LVL56
	.uleb128 .LVL59-1-.LVL56
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST42:
	.byte	0x8
	.4byte	.LVL56
	.uleb128 .LVL59-.LVL56
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST44:
	.byte	0x6
	.4byte	.LVL64
	.byte	0x4
	.uleb128 .LVL64-.LVL64
	.uleb128 .LVL65-.LVL64
	.uleb128 0x9
	.byte	0x3
	.4byte	pka_share_ptr
	.byte	0x6
	.byte	0x23
	.uleb128 0x10
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL65-.LVL64
	.uleb128 .LVL66-1-.LVL64
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST45:
	.byte	0x8
	.4byte	.LVL64
	.uleb128 .LVL67-.LVL64
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST34:
	.byte	0x6
	.4byte	.LVL48
	.byte	0x4
	.uleb128 .LVL48-.LVL48
	.uleb128 .LVL49-.LVL48
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL49-.LVL48
	.uleb128 .LVL51-.LVL48
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL51-.LVL48
	.uleb128 .LVL52-.LVL48
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
	.uleb128 .LVL52-.LVL48
	.uleb128 .LFE28-.LVL48
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST35:
	.byte	0x6
	.4byte	.LVL48
	.byte	0x4
	.uleb128 .LVL48-.LVL48
	.uleb128 .LVL49-.LVL48
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL49-.LVL48
	.uleb128 .LVL50-.LVL48
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL55-.LVL48
	.uleb128 .LFE28-.LVL48
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST36:
	.byte	0x8
	.4byte	.LVL53
	.uleb128 .LVL54-.LVL53
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST31:
	.byte	0x6
	.4byte	.LVL40
	.byte	0x4
	.uleb128 .LVL40-.LVL40
	.uleb128 .LVL41-.LVL40
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL41-.LVL40
	.uleb128 .LVL43-.LVL40
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL43-.LVL40
	.uleb128 .LVL44-.LVL40
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
	.uleb128 .LVL44-.LVL40
	.uleb128 .LFE27-.LVL40
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST32:
	.byte	0x6
	.4byte	.LVL40
	.byte	0x4
	.uleb128 .LVL40-.LVL40
	.uleb128 .LVL41-.LVL40
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL41-.LVL40
	.uleb128 .LVL42-.LVL40
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL47-.LVL40
	.uleb128 .LFE27-.LVL40
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST33:
	.byte	0x8
	.4byte	.LVL45
	.uleb128 .LVL46-.LVL45
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST22:
	.byte	0x6
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL33-.LVL31
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL33-.LVL31
	.uleb128 .LVL39-.LVL31
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL39-.LVL31
	.uleb128 .LFE26-.LVL31
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
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL32-.LVL31
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL32-.LVL31
	.uleb128 .LVL38-.LVL31
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL38-.LVL31
	.uleb128 .LVL39-.LVL31
	.uleb128 0x2
	.byte	0x78
	.sleb128 4
	.byte	0x4
	.uleb128 .LVL39-.LVL31
	.uleb128 .LFE26-.LVL31
	.uleb128 0xb
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
	.byte	0
.LLST25:
	.byte	0x8
	.4byte	.LVL35
	.uleb128 .LVL37-.LVL35
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST26:
	.byte	0x8
	.4byte	.LVL35
	.uleb128 .LVL37-.LVL35
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST28:
	.byte	0x8
	.4byte	.LVL36
	.uleb128 .LVL37-.LVL36
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST29:
	.byte	0x8
	.4byte	.LVL36
	.uleb128 .LVL37-.LVL36
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST30:
	.byte	0x8
	.4byte	.LVL36
	.uleb128 .LVL37-.LVL36
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL21
	.byte	0x4
	.uleb128 .LVL21-.LVL21
	.uleb128 .LVL23-.LVL21
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL23-.LVL21
	.uleb128 .LVL30-.LVL21
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL30-.LVL21
	.uleb128 .LFE25-.LVL21
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
.LLST14:
	.byte	0x6
	.4byte	.LVL21
	.byte	0x4
	.uleb128 .LVL21-.LVL21
	.uleb128 .LVL22-.LVL21
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL22-.LVL21
	.uleb128 .LVL29-.LVL21
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL29-.LVL21
	.uleb128 .LVL30-.LVL21
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL30-.LVL21
	.uleb128 .LFE25-.LVL21
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
.LLST16:
	.byte	0x8
	.4byte	.LVL25
	.uleb128 .LVL28-.LVL25
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST17:
	.byte	0x8
	.4byte	.LVL25
	.uleb128 .LVL28-.LVL25
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST19:
	.byte	0x8
	.4byte	.LVL26
	.uleb128 .LVL28-.LVL26
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST20:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL27-.LVL26
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL27-.LVL26
	.uleb128 .LVL28-.LVL26
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
.LLST21:
	.byte	0x8
	.4byte	.LVL26
	.uleb128 .LVL28-.LVL26
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL17
	.byte	0x4
	.uleb128 .LVL17-.LVL17
	.uleb128 .LVL18-.LVL17
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL18-.LVL17
	.uleb128 .LFE23-.LVL17
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
.LLST10:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL12-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL12-.LVL11
	.uleb128 .LVL14-.LVL11
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL14-.LVL11
	.uleb128 .LVL15-1-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL15-1-.LVL11
	.uleb128 .LVL15-.LVL11
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
	.uleb128 .LVL15-.LVL11
	.uleb128 .LVL16-.LVL11
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL16-.LVL11
	.uleb128 .LFE22-.LVL11
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
	.uleb128 .LVL7-.LVL4
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL7-.LVL4
	.uleb128 .LVL10-.LVL4
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
	.uleb128 .LVL10-.LVL4
	.uleb128 .LFE21-.LVL4
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST6:
	.byte	0x8
	.4byte	.LVL6
	.uleb128 .LVL10-.LVL6
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST8:
	.byte	0x8
	.4byte	.LVL6
	.uleb128 .LVL9-.LVL6
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST9:
	.byte	0x8
	.4byte	.LVL8
	.uleb128 .LVL9-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST5:
	.byte	0x8
	.4byte	.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL2-1-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL2-1-.LVL0
	.uleb128 .LVL3-.LVL0
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
	.uleb128 .LVL3-.LVL0
	.uleb128 .LFE37-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST2:
	.byte	0x8
	.4byte	.LVL1
	.uleb128 .LVL2-.LVL1
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL19
	.byte	0x4
	.uleb128 .LVL19-.LVL19
	.uleb128 .LVL20-1-.LVL19
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL20-1-.LVL19
	.uleb128 .LFE24-.LVL19
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
	.4byte	.LVL78
	.byte	0x4
	.uleb128 .LVL78-.LVL78
	.uleb128 .LVL79-1-.LVL78
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL79-1-.LVL78
	.uleb128 .LFE36-.LVL78
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
.LLST56:
	.byte	0x6
	.4byte	.LVL106
	.byte	0x4
	.uleb128 .LVL106-.LVL106
	.uleb128 .LVL107-1-.LVL106
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL107-1-.LVL106
	.uleb128 .LFE44-.LVL106
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
.LLST58:
	.byte	0x6
	.4byte	.LVL108
	.byte	0x4
	.uleb128 .LVL108-.LVL108
	.uleb128 .LVL145-.LVL108
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
	.uleb128 .LVL146-.LVL108
	.uleb128 .LFE44-.LVL108
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
.LLST59:
	.byte	0x6
	.4byte	.LVL114
	.byte	0x4
	.uleb128 .LVL114-.LVL114
	.uleb128 .LVL115-.LVL114
	.uleb128 0x5
	.byte	0x5f
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL115-.LVL114
	.uleb128 .LVL116-.LVL114
	.uleb128 0x8
	.byte	0x5f
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL116-.LVL114
	.uleb128 .LVL118-.LVL114
	.uleb128 0xa
	.byte	0x91
	.sleb128 -108
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL118-.LVL114
	.uleb128 .LVL119-.LVL114
	.uleb128 0x7
	.byte	0x91
	.sleb128 -108
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL119-.LVL114
	.uleb128 .LVL120-.LVL114
	.uleb128 0x7
	.byte	0x72
	.sleb128 -108
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL120-.LVL114
	.uleb128 .LVL121-.LVL114
	.uleb128 0x5
	.byte	0x5f
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL121-.LVL114
	.uleb128 .LVL122-.LVL114
	.uleb128 0x8
	.byte	0x5f
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL122-.LVL114
	.uleb128 .LVL123-.LVL114
	.uleb128 0x8
	.byte	0x5f
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL123-.LVL114
	.uleb128 .LVL124-.LVL114
	.uleb128 0xa
	.byte	0x91
	.sleb128 -108
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL124-.LVL114
	.uleb128 .LVL125-.LVL114
	.uleb128 0x7
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL131-.LVL114
	.uleb128 .LVL133-.LVL114
	.uleb128 0x7
	.byte	0x93
	.uleb128 0x4
	.byte	0x59
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0
.LLST60:
	.byte	0x6
	.4byte	.LVL109
	.byte	0x4
	.uleb128 .LVL109-.LVL109
	.uleb128 .LVL112-1-.LVL109
	.uleb128 0x5
	.byte	0x7e
	.sleb128 0
	.byte	0x30
	.byte	0x2e
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL148-.LVL109
	.uleb128 .LVL151-.LVL109
	.uleb128 0x5
	.byte	0x7d
	.sleb128 0
	.byte	0x30
	.byte	0x2e
	.byte	0x9f
	.byte	0
.LLST61:
	.byte	0x6
	.4byte	.LVL110
	.byte	0x4
	.uleb128 .LVL110-.LVL110
	.uleb128 .LVL111-.LVL110
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL149-.LVL110
	.uleb128 .LVL150-.LVL110
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST62:
	.byte	0x6
	.4byte	.LVL123
	.byte	0x4
	.uleb128 .LVL123-.LVL123
	.uleb128 .LVL125-.LVL123
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL125-.LVL123
	.uleb128 .LVL131-.LVL123
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL131-.LVL123
	.uleb128 .LVL132-1-.LVL123
	.uleb128 0xb
	.byte	0x7f
	.sleb128 0
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0x1c
	.byte	0xa
	.2byte	0x9c4
	.byte	0x1e
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL133-.LVL123
	.uleb128 .LVL145-.LVL123
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL146-.LVL123
	.uleb128 .LVL155-.LVL123
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL157-.LVL123
	.uleb128 .LFE44-.LVL123
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST63:
	.byte	0x6
	.4byte	.LVL129
	.byte	0x4
	.uleb128 .LVL129-.LVL129
	.uleb128 .LVL131-.LVL129
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL135-.LVL129
	.uleb128 .LVL136-.LVL129
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL138-.LVL129
	.uleb128 .LVL139-.LVL129
	.uleb128 0x4
	.byte	0xb
	.2byte	0xfea4
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL146-.LVL129
	.uleb128 .LVL147-.LVL129
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST64:
	.byte	0x6
	.4byte	.LVL130
	.byte	0x4
	.uleb128 .LVL130-.LVL130
	.uleb128 .LVL131-.LVL130
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL135-.LVL130
	.uleb128 .LVL136-.LVL130
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL136-.LVL130
	.uleb128 .LVL138-.LVL130
	.uleb128 0xb
	.byte	0x7b
	.sleb128 138
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL138-.LVL130
	.uleb128 .LVL140-.LVL130
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL140-.LVL130
	.uleb128 .LVL142-.LVL130
	.uleb128 0xb
	.byte	0x7b
	.sleb128 138
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL142-.LVL130
	.uleb128 .LVL143-.LVL130
	.uleb128 0x11
	.byte	0x3
	.4byte	pka_share_ptr
	.byte	0x6
	.byte	0x23
	.uleb128 0x8a
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL143-.LVL130
	.uleb128 .LVL144-1-.LVL130
	.uleb128 0x11
	.byte	0x3
	.4byte	pka_share_ptr
	.byte	0x6
	.byte	0x23
	.uleb128 0x8a
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL146-.LVL130
	.uleb128 .LVL147-.LVL130
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL147-.LVL130
	.uleb128 .LVL152-.LVL130
	.uleb128 0xb
	.byte	0x7b
	.sleb128 138
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL152-.LVL130
	.uleb128 .LVL153-.LVL130
	.uleb128 0x11
	.byte	0x3
	.4byte	pka_share_ptr
	.byte	0x6
	.byte	0x23
	.uleb128 0x8a
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL157-.LVL130
	.uleb128 .LVL160-.LVL130
	.uleb128 0xb
	.byte	0x7b
	.sleb128 138
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.byte	0
.LLST65:
	.byte	0x8
	.4byte	.LVL138
	.uleb128 .LVL139-.LVL138
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST66:
	.byte	0x8
	.4byte	.LVL154
	.uleb128 .LVL156-.LVL154
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST68:
	.byte	0x8
	.4byte	.LVL158
	.uleb128 .LVL159-.LVL158
	.uleb128 0x6
	.byte	0x7d
	.sleb128 0
	.byte	0x79
	.sleb128 0
	.byte	0x1c
	.byte	0x9f
	.byte	0
.LLST69:
	.byte	0x6
	.4byte	.LVL160
	.byte	0x4
	.uleb128 .LVL160-.LVL160
	.uleb128 .LVL161-.LVL160
	.uleb128 0x3
	.byte	0x7e
	.sleb128 -2
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL161-.LVL160
	.uleb128 .LVL162-.LVL160
	.uleb128 0x3
	.byte	0x7e
	.sleb128 -1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL162-.LVL160
	.uleb128 .LVL163-1-.LVL160
	.uleb128 0x3
	.byte	0x7e
	.sleb128 -2
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL163-1-.LVL160
	.uleb128 .LVL164-.LVL160
	.uleb128 0x7
	.byte	0x91
	.sleb128 -104
	.byte	0x6
	.byte	0x32
	.byte	0x1c
	.byte	0x9f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0xfc
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
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
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.4byte	.LFB36
	.4byte	.LFE36-.LFB36
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
	.4byte	.LFB44
	.4byte	.LFE44-.LFB44
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.4byte	.LFB45
	.4byte	.LFE45-.LFB45
	.4byte	.LFB46
	.4byte	.LFE46-.LFB46
	.4byte	.LFB47
	.4byte	.LFE47-.LFB47
	.4byte	.LFB48
	.4byte	.LFE48-.LFB48
	.4byte	.LFB49
	.4byte	.LFE49-.LFB49
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
.LLRL1:
	.byte	0x5
	.4byte	.LBB45
	.byte	0x4
	.uleb128 .LBB45-.LBB45
	.uleb128 .LBE45-.LBB45
	.byte	0x4
	.uleb128 .LBB50-.LBB45
	.uleb128 .LBE50-.LBB45
	.byte	0x4
	.uleb128 .LBB51-.LBB45
	.uleb128 .LBE51-.LBB45
	.byte	0x4
	.uleb128 .LBB52-.LBB45
	.uleb128 .LBE52-.LBB45
	.byte	0
.LLRL4:
	.byte	0x5
	.4byte	.LBB60
	.byte	0x4
	.uleb128 .LBB60-.LBB60
	.uleb128 .LBE60-.LBB60
	.byte	0x4
	.uleb128 .LBB63-.LBB60
	.uleb128 .LBE63-.LBB60
	.byte	0
.LLRL7:
	.byte	0x5
	.4byte	.LBB65
	.byte	0x4
	.uleb128 .LBB65-.LBB65
	.uleb128 .LBE65-.LBB65
	.byte	0x4
	.uleb128 .LBB70-.LBB65
	.uleb128 .LBE70-.LBB65
	.byte	0
.LLRL15:
	.byte	0x5
	.4byte	.LBB74
	.byte	0x4
	.uleb128 .LBB74-.LBB74
	.uleb128 .LBE74-.LBB74
	.byte	0x4
	.uleb128 .LBB84-.LBB74
	.uleb128 .LBE84-.LBB74
	.byte	0x4
	.uleb128 .LBB85-.LBB74
	.uleb128 .LBE85-.LBB74
	.byte	0
.LLRL18:
	.byte	0x5
	.4byte	.LBB76
	.byte	0x4
	.uleb128 .LBB76-.LBB76
	.uleb128 .LBE76-.LBB76
	.byte	0x4
	.uleb128 .LBB80-.LBB76
	.uleb128 .LBE80-.LBB76
	.byte	0x4
	.uleb128 .LBB81-.LBB76
	.uleb128 .LBE81-.LBB76
	.byte	0
.LLRL24:
	.byte	0x5
	.4byte	.LBB88
	.byte	0x4
	.uleb128 .LBB88-.LBB88
	.uleb128 .LBE88-.LBB88
	.byte	0x4
	.uleb128 .LBB95-.LBB88
	.uleb128 .LBE95-.LBB88
	.byte	0
.LLRL27:
	.byte	0x5
	.4byte	.LBB90
	.byte	0x4
	.uleb128 .LBB90-.LBB90
	.uleb128 .LBE90-.LBB90
	.byte	0x4
	.uleb128 .LBB93-.LBB90
	.uleb128 .LBE93-.LBB90
	.byte	0
.LLRL40:
	.byte	0x5
	.4byte	.LBB100
	.byte	0x4
	.uleb128 .LBB100-.LBB100
	.uleb128 .LBE100-.LBB100
	.byte	0x4
	.uleb128 .LBB103-.LBB100
	.uleb128 .LBE103-.LBB100
	.byte	0
.LLRL43:
	.byte	0x5
	.4byte	.LBB104
	.byte	0x4
	.uleb128 .LBB104-.LBB104
	.uleb128 .LBE104-.LBB104
	.byte	0x4
	.uleb128 .LBB107-.LBB104
	.uleb128 .LBE107-.LBB104
	.byte	0
.LLRL49:
	.byte	0x5
	.4byte	.LBB108
	.byte	0x4
	.uleb128 .LBB108-.LBB108
	.uleb128 .LBE108-.LBB108
	.byte	0x4
	.uleb128 .LBB111-.LBB108
	.uleb128 .LBE111-.LBB108
	.byte	0
.LLRL57:
	.byte	0x5
	.4byte	.LBB122
	.byte	0x4
	.uleb128 .LBB122-.LBB122
	.uleb128 .LBE122-.LBB122
	.byte	0x4
	.uleb128 .LBB137-.LBB122
	.uleb128 .LBE137-.LBB122
	.byte	0x4
	.uleb128 .LBB138-.LBB122
	.uleb128 .LBE138-.LBB122
	.byte	0x4
	.uleb128 .LBB139-.LBB122
	.uleb128 .LBE139-.LBB122
	.byte	0x4
	.uleb128 .LBB140-.LBB122
	.uleb128 .LBE140-.LBB122
	.byte	0x4
	.uleb128 .LBB141-.LBB122
	.uleb128 .LBE141-.LBB122
	.byte	0x4
	.uleb128 .LBB142-.LBB122
	.uleb128 .LBE142-.LBB122
	.byte	0x4
	.uleb128 .LBB143-.LBB122
	.uleb128 .LBE143-.LBB122
	.byte	0
.LLRL67:
	.byte	0x5
	.4byte	.LBB124
	.byte	0x4
	.uleb128 .LBB124-.LBB124
	.uleb128 .LBE124-.LBB124
	.byte	0x4
	.uleb128 .LBB125-.LBB124
	.uleb128 .LBE125-.LBB124
	.byte	0x4
	.uleb128 .LBB126-.LBB124
	.uleb128 .LBE126-.LBB124
	.byte	0x4
	.uleb128 .LBB127-.LBB124
	.uleb128 .LBE127-.LBB124
	.byte	0
.LLRL78:
	.byte	0x5
	.4byte	.LBB148
	.byte	0x4
	.uleb128 .LBB148-.LBB148
	.uleb128 .LBE148-.LBB148
	.byte	0x4
	.uleb128 .LBB151-.LBB148
	.uleb128 .LBE151-.LBB148
	.byte	0
.LLRL80:
	.byte	0x7
	.4byte	.LFB37
	.uleb128 .LFE37-.LFB37
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
	.byte	0x7
	.4byte	.LFB29
	.uleb128 .LFE29-.LFB29
	.byte	0x7
	.4byte	.LFB36
	.uleb128 .LFE36-.LFB36
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
	.4byte	.LFB44
	.uleb128 .LFE44-.LFB44
	.byte	0x7
	.4byte	.LFB43
	.uleb128 .LFE43-.LFB43
	.byte	0x7
	.4byte	.LFB45
	.uleb128 .LFE45-.LFB45
	.byte	0x7
	.4byte	.LFB46
	.uleb128 .LFE46-.LFB46
	.byte	0x7
	.4byte	.LFB47
	.uleb128 .LFE47-.LFB47
	.byte	0x7
	.4byte	.LFB48
	.uleb128 .LFE48-.LFB48
	.byte	0x7
	.4byte	.LFB49
	.uleb128 .LFE49-.LFB49
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF309:
	.string	"hal_hw_semaphore_take"
.LASF305:
	.string	"pka_share_init"
.LASF135:
	.string	"SLEEP_LOCK_IRRX"
.LASF62:
	.string	"PMU_IRQn"
.LASF51:
	.string	"msg_id_handle"
.LASF253:
	.string	"hid_tx_buf_queue"
.LASF92:
	.string	"HAL_EINT_NUMBER_20"
.LASF93:
	.string	"HAL_EINT_NUMBER_21"
.LASF338:
	.string	"pka_share_get_cur_pico_clk"
.LASF95:
	.string	"HAL_EINT_NUMBER_23"
.LASF96:
	.string	"HAL_EINT_NUMBER_24"
.LASF97:
	.string	"HAL_EINT_NUMBER_25"
.LASF63:
	.string	"MCU_DMA_IRQn"
.LASF99:
	.string	"HAL_EINT_NUMBER_27"
.LASF100:
	.string	"HAL_EINT_NUMBER_28"
.LASF101:
	.string	"HAL_EINT_NUMBER_29"
.LASF122:
	.string	"HAL_EINT_UART_2_RX"
.LASF152:
	.string	"SLEEP_LOCK_APP"
.LASF295:
	.string	"log_control_block_mirror_riscv_pka"
.LASF27:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF240:
	.string	"hwmt_last_anchor_ptr"
.LASF214:
	.string	"prev"
.LASF238:
	.string	"EmptyPktPtr"
.LASF311:
	.string	"pka_active_state_set"
.LASF38:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF300:
	.string	"RiscVHid"
.LASF20:
	.string	"PRINT_LEVEL_DEBUG"
.LASF123:
	.string	"HAL_EINT_USB0"
.LASF124:
	.string	"HAL_EINT_USB1"
.LASF125:
	.string	"HAL_EINT_USB2"
.LASF340:
	.string	"cur_clk"
.LASF365:
	.string	"mq_ptr"
.LASF189:
	.string	"HAL_HW_SEMAPHORE_ID_22"
.LASF322:
	.string	"complete_time"
.LASF215:
	.string	"next"
.LASF190:
	.string	"HAL_HW_SEMAPHORE_ID_23"
.LASF282:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF132:
	.string	"SLEEP_LOCK_TRNG"
.LASF359:
	.string	"pka_share_tx_buf_ack_pending_check"
.LASF373:
	.string	"pGet"
.LASF193:
	.string	"HAL_HW_SEMAPHORE_ID_26"
.LASF361:
	.string	"mask"
.LASF222:
	.string	"head"
.LASF220:
	.string	"pka_share_dlist_stru"
.LASF102:
	.string	"HAL_EINT_NUMBER_30"
.LASF103:
	.string	"HAL_EINT_NUMBER_31"
.LASF276:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF105:
	.string	"HAL_EINT_NUMBER_33"
.LASF310:
	.string	"pka_tx_buf_is_hid"
.LASF108:
	.string	"HAL_EINT_NUMBER_36"
.LASF142:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF369:
	.string	"pka_share_OSMQ_PutFront"
.LASF111:
	.string	"HAL_EINT_NUMBER_39"
.LASF393:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF364:
	.string	"pka_share_OSMQ_PrintQueue"
.LASF256:
	.string	"hid_tx_buf_start_ptr"
.LASF36:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF58:
	.string	"SPI_MST1_IRQn"
.LASF272:
	.string	"DBG_PIN_USB_SOF"
.LASF206:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF319:
	.string	"pka_share_tx_buf_get_from_q"
.LASF227:
	.string	"hwmt_pico_offset_phase_ptr"
.LASF70:
	.string	"BT_IRQn"
.LASF134:
	.string	"SLEEP_LOCK_IRTX"
.LASF205:
	.string	"hal_hw_semaphore_status_t"
.LASF372:
	.string	"pka_share_OSMQ_Get"
.LASF398:
	.string	"__builtin_memcpy"
.LASF130:
	.string	"SLEEP_LOCK_AESOTF"
.LASF283:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF346:
	.string	"pka_share_hwmt_get_rxhdr"
.LASF71:
	.string	"IRQ_NUMBER_MAX"
.LASF327:
	.string	"native_anchor"
.LASF112:
	.string	"HAL_EINT_NUMBER_40"
.LASF113:
	.string	"HAL_EINT_NUMBER_41"
.LASF147:
	.string	"SLEEP_LOCK_USB"
.LASF115:
	.string	"HAL_EINT_NUMBER_43"
.LASF116:
	.string	"HAL_EINT_NUMBER_44"
.LASF19:
	.string	"DEBUG_LOG_OFF"
.LASF118:
	.string	"HAL_EINT_NUMBER_46"
.LASF119:
	.string	"HAL_EINT_NUMBER_47"
.LASF151:
	.string	"SLEEP_LOCK_I2C0"
.LASF204:
	.string	"HAL_HW_SEMAPHORE_STATUS_OK"
.LASF280:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF304:
	.string	"rtt_counter"
.LASF328:
	.string	"connsys_clk_domain"
.LASF202:
	.string	"HAL_HW_SEMAPHORE_STATUS_GIVE_ERROR"
.LASF23:
	.string	"PRINT_LEVEL_ERROR"
.LASF366:
	.string	"list"
.LASF177:
	.string	"HAL_HW_SEMAPHORE_ID_10"
.LASF32:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF6:
	.string	"signed char"
.LASF353:
	.string	"pka_share_tx_buf_set_pkt_len"
.LASF396:
	.string	"pka_share_OS_dlist_is_empty"
.LASF17:
	.string	"uint32_t"
.LASF13:
	.string	"int8_t"
.LASF332:
	.string	"ref_offset"
.LASF258:
	.string	"hid_tx_buf_payload_offset"
.LASF246:
	.string	"CurrentReportRate"
.LASF395:
	.string	"pka_share_get_force_nack_ptr"
.LASF285:
	.string	"stru_bttime"
.LASF43:
	.string	"f_msg_id_t"
.LASF61:
	.string	"UART_DMA_IRQn"
.LASF343:
	.string	"pka_share_get_hwmt_pico_offset"
.LASF275:
	.string	"DBG_PIN_MAX"
.LASF289:
	.string	"bttime_stru_ptr"
.LASF216:
	.string	"pka_share_DLIST_STRU"
.LASF2:
	.string	"long long unsigned int"
.LASF370:
	.string	"file"
.LASF299:
	.string	"offset"
.LASF278:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF148:
	.string	"SLEEP_LOCK_UART0"
.LASF149:
	.string	"SLEEP_LOCK_UART1"
.LASF150:
	.string	"SLEEP_LOCK_UART2"
.LASF229:
	.string	"common"
.LASF44:
	.string	"f_tlv_dump_t"
.LASF263:
	.string	"cb_type"
.LASF232:
	.string	"POFlow_ptr"
.LASF334:
	.string	"rxhdr"
.LASF212:
	.string	"PKA_SHARE_ENABLE"
.LASF259:
	.string	"hid_tx_status_ptr"
.LASF33:
	.string	"LOG_TYPE_HCI_DATA"
.LASF201:
	.string	"HAL_HW_SEMAPHORE_STATUS_INVALID_PARAMETER"
.LASF252:
	.string	"enable"
.LASF290:
	.string	"tx_post_prepare_handler"
.LASF56:
	.string	"KEYSCAN_IRQn"
.LASF39:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF72:
	.string	"HAL_EINT_NUMBER_0"
.LASF73:
	.string	"HAL_EINT_NUMBER_1"
.LASF74:
	.string	"HAL_EINT_NUMBER_2"
.LASF75:
	.string	"HAL_EINT_NUMBER_3"
.LASF76:
	.string	"HAL_EINT_NUMBER_4"
.LASF77:
	.string	"HAL_EINT_NUMBER_5"
.LASF78:
	.string	"HAL_EINT_NUMBER_6"
.LASF79:
	.string	"HAL_EINT_NUMBER_7"
.LASF80:
	.string	"HAL_EINT_NUMBER_8"
.LASF81:
	.string	"HAL_EINT_NUMBER_9"
.LASF265:
	.string	"bt_info"
.LASF318:
	.string	"print_module_msgid_log"
.LASF83:
	.string	"HAL_EINT_NUMBER_11"
.LASF213:
	.string	"pka_share_enable_t"
.LASF274:
	.string	"DBG_PIN_USB_TX"
.LASF210:
	.string	"pka_share_callback_type_t"
.LASF245:
	.string	"TxRxDataRate"
.LASF35:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF315:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF330:
	.string	"expslot_1"
.LASF331:
	.string	"expslot_2"
.LASF154:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF194:
	.string	"HAL_HW_SEMAPHORE_ID_27"
.LASF345:
	.string	"pka_share_hwmt_get_curidx"
.LASF241:
	.string	"hwmt_last_anchor_phase_ptr"
.LASF375:
	.string	"__pka_share_OSMQ_Get"
.LASF341:
	.string	"native_clk"
.LASF247:
	.string	"mp_version"
.LASF348:
	.string	"tx_cnt"
.LASF144:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF128:
	.string	"HAL_EINT_NUMBER_MAX"
.LASF376:
	.string	"list_ptr"
.LASF157:
	.string	"EINT_COUNTER_NUMBER_1"
.LASF397:
	.string	"memcpy"
.LASF29:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF159:
	.string	"EINT_COUNTER_NUMBER_3"
.LASF18:
	.string	"DEBUG_LOG_ON"
.LASF326:
	.string	"last_anchor"
.LASF37:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF273:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF267:
	.string	"DBG_PIN_SPI_CB"
.LASF30:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF28:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF342:
	.string	"pka_share_get_sync_clk"
.LASF217:
	.string	"pka_share_DLIST_STRU_PTR"
.LASF34:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF344:
	.string	"pka_share_get_hwmt_last_anchor"
.LASF40:
	.string	"log_type_t"
.LASF15:
	.string	"uint8_t"
.LASF46:
	.string	"log_switch"
.LASF223:
	.string	"pka_share_OSMQ"
.LASF53:
	.string	"SW_IRQn"
.LASF384:
	.string	"pka_share_OS_dlist_remove"
.LASF153:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF197:
	.string	"HAL_HW_SEMAPHORE_ID_30"
.LASF41:
	.string	"f_print_t"
.LASF307:
	.string	"pka_share_tx_ctrl_init"
.LASF226:
	.string	"hwmt_pico_offset_ptr"
.LASF98:
	.string	"HAL_EINT_NUMBER_26"
.LASF254:
	.string	"hid_tx_buf_sending_queue"
.LASF368:
	.string	"pka_share_OSMQ_PrintList"
.LASF121:
	.string	"HAL_EINT_UART_1_RX"
.LASF391:
	.string	"__modsi3"
.LASF131:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF281:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF355:
	.string	"record_riscV_info"
.LASF225:
	.string	"flag_ptr"
.LASF389:
	.string	"pka_share_advanced_tx_prepare_rt"
.LASF288:
	.string	"bttime_stru"
.LASF386:
	.string	"pka_share_OS_dlist_init"
.LASF10:
	.string	"long long int"
.LASF178:
	.string	"HAL_HW_SEMAPHORE_ID_11"
.LASF179:
	.string	"HAL_HW_SEMAPHORE_ID_12"
.LASF180:
	.string	"HAL_HW_SEMAPHORE_ID_13"
.LASF181:
	.string	"HAL_HW_SEMAPHORE_ID_14"
.LASF182:
	.string	"HAL_HW_SEMAPHORE_ID_15"
.LASF183:
	.string	"HAL_HW_SEMAPHORE_ID_16"
.LASF184:
	.string	"HAL_HW_SEMAPHORE_ID_17"
.LASF185:
	.string	"HAL_HW_SEMAPHORE_ID_18"
.LASF186:
	.string	"HAL_HW_SEMAPHORE_ID_19"
.LASF66:
	.string	"I3C0_DMA_IRQn"
.LASF146:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF380:
	.string	"pka_share_OS_dlist_append"
.LASF243:
	.string	"acl_active_state_ptr"
.LASF257:
	.string	"hid_tx_buf_queue_header_size"
.LASF42:
	.string	"f_dump_buffer_t"
.LASF279:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF26:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF385:
	.string	"plist"
.LASF234:
	.string	"CurTxPtr"
.LASF207:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF233:
	.string	"pka_share_bt_info_le"
.LASF314:
	.string	"share_buffer_hw_semaphore_take"
.LASF239:
	.string	"hwmt_cur_idx_ptr"
.LASF68:
	.string	"IRQ_GEN_IRQn"
.LASF57:
	.string	"UART_IRQn"
.LASF200:
	.string	"hal_hw_semaphore_id_t"
.LASF21:
	.string	"PRINT_LEVEL_INFO"
.LASF270:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF271:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF187:
	.string	"HAL_HW_SEMAPHORE_ID_20"
.LASF188:
	.string	"HAL_HW_SEMAPHORE_ID_21"
.LASF349:
	.string	"riscv_pka_le_tx_post_prepare_callback"
.LASF251:
	.string	"pka_share_bt_info"
.LASF191:
	.string	"HAL_HW_SEMAPHORE_ID_24"
.LASF192:
	.string	"HAL_HW_SEMAPHORE_ID_25"
.LASF379:
	.string	"pka_share_OS_dlist_prepend"
.LASF143:
	.string	"SLEEP_LOCK_DCXO"
.LASF211:
	.string	"PKA_SHARE_DISABLE"
.LASF196:
	.string	"HAL_HW_SEMAPHORE_ID_29"
.LASF167:
	.string	"HAL_HW_SEMAPHORE_ID_0"
.LASF168:
	.string	"HAL_HW_SEMAPHORE_ID_1"
.LASF169:
	.string	"HAL_HW_SEMAPHORE_ID_2"
.LASF170:
	.string	"HAL_HW_SEMAPHORE_ID_3"
.LASF171:
	.string	"HAL_HW_SEMAPHORE_ID_4"
.LASF172:
	.string	"HAL_HW_SEMAPHORE_ID_5"
.LASF173:
	.string	"HAL_HW_SEMAPHORE_ID_6"
.LASF174:
	.string	"HAL_HW_SEMAPHORE_ID_7"
.LASF175:
	.string	"HAL_HW_SEMAPHORE_ID_8"
.LASF296:
	.string	"riscv_pka_info"
.LASF104:
	.string	"HAL_EINT_NUMBER_32"
.LASF69:
	.string	"USB_IRQn"
.LASF106:
	.string	"HAL_EINT_NUMBER_34"
.LASF136:
	.string	"SLEEP_LOCK_AIO"
.LASF107:
	.string	"HAL_EINT_NUMBER_35"
.LASF109:
	.string	"HAL_EINT_NUMBER_37"
.LASF110:
	.string	"HAL_EINT_NUMBER_38"
.LASF335:
	.string	"msg_id_string"
.LASF155:
	.string	"_Bool"
.LASF293:
	.string	"pka_share_ptr"
.LASF387:
	.string	"pka_share_tx_buf_clear_valid"
.LASF354:
	.string	"pkt_len"
.LASF195:
	.string	"HAL_HW_SEMAPHORE_ID_28"
.LASF49:
	.string	"dump_handle"
.LASF228:
	.string	"pka_share_bt_info_common"
.LASF11:
	.string	"long double"
.LASF198:
	.string	"HAL_HW_SEMAPHORE_ID_31"
.LASF199:
	.string	"HAL_HW_SEMAPHORE_ID_MAX"
.LASF16:
	.string	"uint16_t"
.LASF394:
	.string	"IRQn"
.LASF129:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF378:
	.string	"newptr"
.LASF236:
	.string	"CandiTxPtr"
.LASF262:
	.string	"hid_tx_buf_num"
.LASF50:
	.string	"tlv_dump_handle"
.LASF12:
	.string	"char"
.LASF59:
	.string	"RTC_IRQn"
.LASF22:
	.string	"PRINT_LEVEL_WARNING"
.LASF303:
	.string	"correction_idx"
.LASF7:
	.string	"short int"
.LASF260:
	.string	"hid_forced_nack_status_ptr"
.LASF209:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF374:
	.string	"pka_share_OSMQ_Peak"
.LASF235:
	.string	"NextTxPtr"
.LASF8:
	.string	"long int"
.LASF350:
	.string	"pka_spi_callback_pre_process"
.LASF54:
	.string	"LED_IRQn"
.LASF261:
	.string	"hid_tx_buf_payload_size"
.LASF320:
	.string	"pka_share_tx_buf_send"
.LASF145:
	.string	"SLEEP_LOCK_I3C1"
.LASF277:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF333:
	.string	"report_rate"
.LASF64:
	.string	"EINT_IRQn"
.LASF67:
	.string	"SPI_MST0_IRQn"
.LASF60:
	.string	"GPT_IRQn"
.LASF268:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF114:
	.string	"HAL_EINT_NUMBER_42"
.LASF117:
	.string	"HAL_EINT_NUMBER_45"
.LASF284:
	.string	"riscv_pka_tx_post_prepare_callback_t"
.LASF329:
	.string	"xo_pdn_top_cond0"
.LASF287:
	.string	"phase"
.LASF255:
	.string	"hid_tx_buf_ack_pending_queue"
.LASF298:
	.string	"sync_time"
.LASF264:
	.string	"req_rscv_ctl_int"
.LASF388:
	.string	"pka_share_tx_buf_is_valid"
.LASF219:
	.string	"pka_share_DLIST_HEAD_PTR"
.LASF352:
	.string	"pka_share_hid_need_accmulate"
.LASF48:
	.string	"print_handle"
.LASF127:
	.string	"HAL_EINT_RESERVED"
.LASF321:
	.string	"pka_spi_callback_post_process"
.LASF230:
	.string	"NextTxPtr0"
.LASF231:
	.string	"NextTxPtr1"
.LASF137:
	.string	"SLEEP_LOCK_FLASH"
.LASF308:
	.string	"pka_share_tx_forward_prepare_rtt0"
.LASF3:
	.string	"unsigned int"
.LASF371:
	.string	"pka_share_OSMQ_Put"
.LASF52:
	.string	"log_control_block_t"
.LASF347:
	.string	"riscv_pka_rtt_tx_post_prepare_callback"
.LASF358:
	.string	"riscv_pka_init"
.LASF248:
	.string	"max_pdu_len_ptr"
.LASF9:
	.string	"long unsigned int"
.LASF302:
	.string	"RiscVHidIdx"
.LASF356:
	.string	"sync_time_period"
.LASF14:
	.string	"int32_t"
.LASF390:
	.string	"pka_share_enabled"
.LASF336:
	.string	"update_value"
.LASF218:
	.string	"pka_share_DLIST_HEAD"
.LASF297:
	.string	"RiscVCtl"
.LASF266:
	.string	"pka_share_info"
.LASF325:
	.string	"riscv_pka_rt_tx_post_prepare_callback"
.LASF138:
	.string	"SLEEP_LOCK_ESC"
.LASF292:
	.string	"riscv_pka_info_t"
.LASF323:
	.string	"type"
.LASF4:
	.string	"unsigned char"
.LASF291:
	.string	"pico_offset"
.LASF357:
	.string	"sync_time_phase"
.LASF133:
	.string	"SLEEP_LOCK_DMA"
.LASF381:
	.string	"pka_share_OS_dlist_insert"
.LASF25:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF45:
	.string	"module_name"
.LASF166:
	.string	"EINT_COUNTER_NUMBER_MUX"
.LASF382:
	.string	"prev_list"
.LASF94:
	.string	"HAL_EINT_NUMBER_22"
.LASF339:
	.string	"time_ptr"
.LASF377:
	.string	"pka_share_OS_dlist_getfront"
.LASF242:
	.string	"hwmt_tpollgo_ptr"
.LASF31:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF244:
	.string	"MaxHidTxPktByRR"
.LASF65:
	.string	"I3C0_IRQn"
.LASF120:
	.string	"HAL_EINT_UART_0_RX"
.LASF317:
	.string	"light_assert"
.LASF362:
	.string	"pNextTxPtr0"
.LASF363:
	.string	"pNextTxPtr1"
.LASF47:
	.string	"print_level"
.LASF139:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF140:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF141:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF208:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF316:
	.string	"pka_share_tx_buf_get_payload"
.LASF176:
	.string	"HAL_HW_SEMAPHORE_ID_9"
.LASF286:
	.string	"period"
.LASF237:
	.string	"HidTxPktPtr"
.LASF224:
	.string	"pka_share_OSMQ_PTR"
.LASF5:
	.string	"short unsigned int"
.LASF156:
	.string	"EINT_COUNTER_NUMBER_0"
.LASF269:
	.string	"DBG_PIN_NACK"
.LASF158:
	.string	"EINT_COUNTER_NUMBER_2"
.LASF203:
	.string	"HAL_HW_SEMAPHORE_STATUS_TAKE_ERROR"
.LASF160:
	.string	"EINT_COUNTER_NUMBER_4"
.LASF161:
	.string	"EINT_COUNTER_NUMBER_5"
.LASF162:
	.string	"EINT_COUNTER_NUMBER_6"
.LASF163:
	.string	"EINT_COUNTER_NUMBER_7"
.LASF164:
	.string	"EINT_COUNTER_NUMBER_8"
.LASF165:
	.string	"EINT_COUNTER_NUMBER_9"
.LASF221:
	.string	"pka_share_osmq_stru"
.LASF324:
	.string	"tx_cn"
.LASF301:
	.string	"RiscVHID"
.LASF126:
	.string	"HAL_EINT_LPCOMP"
.LASF367:
	.string	"payload"
.LASF313:
	.string	"share_buffer_hw_semaphore_give"
.LASF360:
	.string	"pka_share_tx_buf_apply_to_HWMT"
.LASF294:
	.string	"log_control_block_riscv_pka"
.LASF249:
	.string	"pka_share_bt_info_rt"
.LASF306:
	.string	"pka_share_updt_hid_tx_ptr"
.LASF383:
	.string	"next_list"
.LASF82:
	.string	"HAL_EINT_NUMBER_10"
.LASF312:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF84:
	.string	"HAL_EINT_NUMBER_12"
.LASF85:
	.string	"HAL_EINT_NUMBER_13"
.LASF86:
	.string	"HAL_EINT_NUMBER_14"
.LASF87:
	.string	"HAL_EINT_NUMBER_15"
.LASF88:
	.string	"HAL_EINT_NUMBER_16"
.LASF89:
	.string	"HAL_EINT_NUMBER_17"
.LASF90:
	.string	"HAL_EINT_NUMBER_18"
.LASF91:
	.string	"HAL_EINT_NUMBER_19"
.LASF55:
	.string	"QDEC_IRQn"
.LASF250:
	.string	"pka_share_bt_info_rtt"
.LASF337:
	.string	"retru"
.LASF351:
	.string	"pka_share_get_tx_status"
.LASF24:
	.string	"print_level_t"
.LASF392:
	.string	"__mulsi3"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/middleware/airoha/pka/src/pka.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
