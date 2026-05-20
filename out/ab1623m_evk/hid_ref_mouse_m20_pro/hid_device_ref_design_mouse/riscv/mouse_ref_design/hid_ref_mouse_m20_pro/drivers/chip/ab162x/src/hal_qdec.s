	.file	"hal_qdec.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_qdec.c"
	.section	.text.hw_qdec_Isr_zephyr,"ax",@progbits
	.align	1
	.type	hw_qdec_Isr_zephyr, @function
hw_qdec_Isr_zephyr:
.LFB5:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_qdec.c"
	.loc 1 74 1
	.cfi_startproc
	.loc 1 75 3
.LBB16:
.LBB17:
	.loc 1 58 3
	.loc 1 58 70 is_stmt 0
	li	a5,1108348928
	lw	a5,76(a5)
.LBE17:
.LBE16:
	.loc 1 74 1
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	.cfi_offset 1, -4
.LBB19:
.LBB18:
	.loc 1 58 21
	sw	a5,0(sp)
	.loc 1 59 3 is_stmt 1
	.loc 1 59 18 is_stmt 0
	lw	a4,0(sp)
	li	a5,4
	andi	a4,a4,1
	.loc 1 59 6
	bne	a4,zero,.L2
	.loc 1 63 8 is_stmt 1
	.loc 1 63 23 is_stmt 0
	lw	a5,0(sp)
	andi	a5,a5,256
	.loc 1 65 12
	snez	a5,a5
	addi	a5,a5,1
.L2:
.LVL0:
.LBE18:
.LBE19:
	.loc 1 76 3 is_stmt 1
	.loc 1 76 16 is_stmt 0
	andi	a3,a5,2
	.loc 1 78 23
	lw	a4,qdec_callback
	.loc 1 76 6
	beq	a3,zero,.L3
	.loc 1 78 5 is_stmt 1
	.loc 1 78 8 is_stmt 0
	beq	a4,zero,.L4
	.loc 1 80 7 is_stmt 1
	li	a0,2
	jalr	a4
.LVL1:
.L4:
	.loc 1 83 5
	.loc 1 83 79 is_stmt 0
	li	a4,2
	li	a5,1108348928
	sb	a4,44(a5)
	.loc 1 84 5 is_stmt 1
	.loc 1 84 78 is_stmt 0
	li	a4,4
.L22:
	.loc 1 96 5 is_stmt 1
	.loc 1 96 78 is_stmt 0
	sb	a4,45(a5)
	.loc 1 97 5 is_stmt 1
	.loc 1 97 72 is_stmt 0
	sb	zero,20(a5)
	.loc 1 98 5 is_stmt 1
	.loc 1 98 24 is_stmt 0
	sw	zero,g_qdec_mode_status,a5
.L1:
	.loc 1 109 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.L3:
	.cfi_restore_state
	.loc 1 88 8 is_stmt 1
	.loc 1 88 22 is_stmt 0
	andi	a5,a5,4
	.loc 1 88 11
	beq	a5,zero,.L6
	.loc 1 90 5 is_stmt 1
	.loc 1 90 8 is_stmt 0
	beq	a4,zero,.L7
	.loc 1 92 7 is_stmt 1
	li	a0,4
	jalr	a4
.LVL2:
.L7:
	.loc 1 95 5
	.loc 1 95 79 is_stmt 0
	li	a5,1108348928
	li	a4,1
	sb	a4,44(a5)
	j	.L22
.L6:
	.loc 1 100 8 is_stmt 1
	.loc 1 102 5
	.loc 1 102 8 is_stmt 0
	beq	a4,zero,.L8
	.loc 1 104 7 is_stmt 1
	li	a0,1
	jalr	a4
.LVL3:
.L8:
	.loc 1 107 5
	.loc 1 107 75 is_stmt 0
	li	a5,1108348928
	li	a4,1
	sb	a4,46(a5)
	.loc 1 109 1
	j	.L1
	.cfi_endproc
.LFE5:
	.size	hw_qdec_Isr_zephyr, .-hw_qdec_Isr_zephyr
	.section	.text.qdec_group_config_para_check,"ax",@progbits
	.align	1
	.type	qdec_group_config_para_check, @function
qdec_group_config_para_check:
.LFB6:
	.loc 1 112 1 is_stmt 1
	.cfi_startproc
	.loc 1 113 3
	.loc 1 112 1 is_stmt 0
	mv	a4,a0
	.loc 1 113 12
	slli	a4,a4,16
	srli	a4,a4,16
.LVL4:
	.loc 1 114 3 is_stmt 1
	.loc 1 115 3
	.loc 1 116 3
	.loc 1 116 6 is_stmt 0
	li	a2,511
	.loc 1 112 1
	addi	sp,sp,-4
	.cfi_def_cfa_offset 4
	.loc 1 116 6
	bgtu	a4,a2,.L25
	srli	a3,a0,16
	andi	a3,a3,0xff
	.loc 1 116 28 discriminator 1
	li	a2,15
	mv	a5,a0
	.loc 1 119 12
	li	a0,-1
.LVL5:
	.loc 1 116 28 discriminator 1
	bgtu	a3,a2,.L23
	.loc 1 116 50 discriminator 2
	bgtu	a3,a4,.L23
	srli	a5,a5,24
.LVL6:
	.loc 1 116 79 discriminator 3
	li	a4,31
.LVL7:
	bgtu	a5,a4,.L23
	.loc 1 117 26
	addi	a5,a5,-1
	seqz	a5,a5
	neg	a0,a5
.L23:
	.loc 1 122 1
	addi	sp,sp,4
	.cfi_remember_state
	.cfi_def_cfa_offset 0
	jr	ra
.LVL8:
.L25:
	.cfi_restore_state
	.loc 1 119 12
	li	a0,-1
.LVL9:
	j	.L23
	.cfi_endproc
.LFE6:
	.size	qdec_group_config_para_check, .-qdec_group_config_para_check
	.section	.text.hal_qdec_init,"ax",@progbits
	.align	1
	.globl	hal_qdec_init
	.hidden	hal_qdec_init
	.type	hal_qdec_init, @function
hal_qdec_init:
.LFB8:
	.loc 1 177 1 is_stmt 1
	.cfi_startproc
.LVL10:
	.loc 1 184 3
.LBB22:
.LBB23:
	.loc 1 127 3
.LBE23:
.LBE22:
	.loc 1 177 1 is_stmt 0
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	sw	s1,12(sp)
	.cfi_offset 9, -12
.LBB27:
.LBB24:
	.loc 1 127 12
	lhu	s1,12(a0)
.LVL11:
	.loc 1 128 3 is_stmt 1
.LBE24:
.LBE27:
	.loc 1 177 1 is_stmt 0
	sw	ra,20(sp)
	sw	s0,16(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
.LBB28:
.LBB25:
	.loc 1 128 6
	li	a5,511
	bleu	s1,a5,.L31
.LVL12:
.L33:
.LBE25:
.LBE28:
	.loc 1 186 12
	li	t1,-1
.L30:
	.loc 1 217 1
	lw	ra,20(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	lw	s1,12(sp)
	.cfi_restore 9
	mv	a0,t1
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
	jr	ra
.LVL13:
.L31:
	.cfi_restore_state
.LBB29:
.LBB26:
	.loc 1 135 27
	lhu	a5,14(a0)
	mv	s0,a0
	.loc 1 134 3 is_stmt 1
	.loc 1 135 3
	.loc 1 135 27 is_stmt 0
	sh	a5,4(sp)
	lhu	a5,16(a0)
	sh	a5,6(sp)
	.loc 1 136 3 is_stmt 1
	.loc 1 136 9 is_stmt 0
	lw	a0,4(sp)
.LVL14:
	call	qdec_group_config_para_check
.LVL15:
	.loc 1 137 3 is_stmt 1
	.loc 1 137 6 is_stmt 0
	bne	a0,zero,.L33
	.loc 1 142 3 is_stmt 1
	.loc 1 142 27 is_stmt 0
	lhu	a5,18(s0)
	sh	a5,8(sp)
	lhu	a5,20(s0)
	sh	a5,10(sp)
	.loc 1 143 3 is_stmt 1
	.loc 1 143 9 is_stmt 0
	lw	a0,8(sp)
.LVL16:
	call	qdec_group_config_para_check
.LVL17:
	.loc 1 144 3 is_stmt 1
	.loc 1 144 6 is_stmt 0
	sw	a0,0(sp)
	bne	a0,zero,.L33
	.loc 1 150 3 is_stmt 1
	.loc 1 150 11 is_stmt 0
	lbu	t0,0(s0)
.LVL18:
	.loc 1 151 3 is_stmt 1
	.loc 1 153 6 is_stmt 0
	li	a5,48
	.loc 1 151 11
	lbu	a3,1(s0)
.LVL19:
	.loc 1 152 3 is_stmt 1
	.loc 1 152 11 is_stmt 0
	lbu	a4,2(s0)
.LVL20:
	.loc 1 153 3 is_stmt 1
	.loc 1 153 6 is_stmt 0
	bgtu	t0,a5,.L33
	.loc 1 153 33 discriminator 1
	bgtu	a3,a5,.L33
	.loc 1 153 62 discriminator 2
	bgtu	a4,a5,.L33
	.loc 1 159 3 is_stmt 1
	.loc 1 159 16 is_stmt 0
	lw	a0,4(s0)
.LVL21:
	.loc 1 159 6
	li	a2,1
	bgtu	a0,a2,.L33
	.loc 1 159 70 discriminator 1
	lw	a1,8(s0)
	.loc 1 159 58 discriminator 1
	bgtu	a1,a2,.L33
	.loc 1 165 3 is_stmt 1
	.loc 1 165 23 is_stmt 0
	lla	a5,g_qdec_cfg
	.loc 1 171 26
	lhu	t2,4(sp)
	.loc 1 165 23
	sb	t0,0(a5)
	.loc 1 166 3 is_stmt 1
	.loc 1 166 23 is_stmt 0
	sb	a3,1(a5)
	.loc 1 167 3 is_stmt 1
	.loc 1 172 26 is_stmt 0
	lhu	t0,8(sp)
.LVL22:
	.loc 1 171 26
	lhu	a3,6(sp)
.LVL23:
	.loc 1 167 22
	sb	a4,2(a5)
	.loc 1 168 3 is_stmt 1
	.loc 1 172 26 is_stmt 0
	lhu	a4,10(sp)
.LVL24:
	.loc 1 169 32
	sw	a1,8(a5)
	.loc 1 171 26
	sh	t2,14(a5)
	.loc 1 168 28
	sw	a0,4(a5)
	.loc 1 169 3 is_stmt 1
	.loc 1 170 3
	.loc 1 171 26 is_stmt 0
	sh	a3,16(a5)
	.loc 1 172 26
	sh	t0,18(a5)
	sh	a4,20(a5)
	.loc 1 170 24
	sh	s1,12(a5)
	.loc 1 171 3 is_stmt 1
	.loc 1 172 3
	.loc 1 173 3
.LVL25:
.LBE26:
.LBE29:
	.loc 1 189 3
	.loc 1 189 56 is_stmt 0
	li	a5,1108348928
	sb	zero,19(a5)
	.loc 1 191 3 is_stmt 1
	.loc 1 191 70 is_stmt 0
	andi	a0,a0,0xff
	sb	a0,1(a5)
	.loc 1 192 3 is_stmt 1
	.loc 1 192 64 is_stmt 0
	andi	a1,a1,0xff
	sb	a1,0(a5)
	.loc 1 193 3 is_stmt 1
	.loc 1 193 72 is_stmt 0
	sh	s1,4(a5)
	.loc 1 194 3 is_stmt 1
	.loc 1 194 79 is_stmt 0
	sh	t2,8(a5)
	.loc 1 195 3 is_stmt 1
	.loc 1 195 103 is_stmt 0
	andi	a1,a3,0xff
	.loc 1 195 79
	sb	a1,10(a5)
	.loc 1 196 3 is_stmt 1
	.loc 1 196 102 is_stmt 0
	srli	a3,a3,8
	.loc 1 196 78
	sb	a3,11(a5)
	.loc 1 197 3 is_stmt 1
	.loc 1 197 79 is_stmt 0
	sh	t0,12(a5)
	.loc 1 198 3 is_stmt 1
	.loc 1 198 103 is_stmt 0
	andi	a3,a4,0xff
	.loc 1 198 79
	sb	a3,14(a5)
	.loc 1 199 3 is_stmt 1
	.loc 1 199 102 is_stmt 0
	srli	a4,a4,8
	.loc 1 199 78
	sb	a4,15(a5)
	.loc 1 202 3 is_stmt 1
	.loc 1 202 73 is_stmt 0
	sb	zero,22(a5)
	.loc 1 204 3 is_stmt 1
	.loc 1 204 70 is_stmt 0
	sb	zero,20(a5)
	.loc 1 206 3 is_stmt 1
	.loc 1 209 3
	.loc 1 206 58 is_stmt 0
	sb	a2,16(a5)
	.loc 1 209 3
	lla	a1,hw_qdec_Isr_zephyr
	li	a0,11
	call	hal_nvic_register_isr_handler
.LVL26:
	.loc 1 214 3 is_stmt 1
	li	a0,11
	call	hal_nvic_enable_irq
.LVL27:
	.loc 1 215 3
	.loc 1 215 15 is_stmt 0
	li	a2,1
	lw	t1,0(sp)
	.loc 1 216 3 is_stmt 1
	.loc 1 215 15 is_stmt 0
	sw	a2,qdec_status,a5
	.loc 1 216 10
	j	.L30
	.cfi_endproc
.LFE8:
	.size	hal_qdec_init, .-hal_qdec_init
	.section	.text.hal_qdec_deinit,"ax",@progbits
	.align	1
	.globl	hal_qdec_deinit
	.hidden	hal_qdec_deinit
	.type	hal_qdec_deinit, @function
hal_qdec_deinit:
.LFB9:
	.loc 1 220 1 is_stmt 1
	.cfi_startproc
	.loc 1 225 3
	.loc 1 220 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 225 3
	li	a2,24
	li	a1,0
	lla	a0,g_qdec_cfg
	.loc 1 220 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 225 3
	call	memset
.LVL28:
	.loc 1 227 3 is_stmt 1
	.loc 1 227 21 is_stmt 0
	sb	zero,g_first_data_flag,a5
	.loc 1 228 3 is_stmt 1
	.loc 1 231 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 228 56
	li	a5,1108348928
	sb	zero,19(a5)
	.loc 1 229 3 is_stmt 1
	.loc 1 229 15 is_stmt 0
	sw	zero,qdec_status,a5
	.loc 1 230 3 is_stmt 1
	.loc 1 231 1 is_stmt 0
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE9:
	.size	hal_qdec_deinit, .-hal_qdec_deinit
	.section	.text.hal_qdec_enable,"ax",@progbits
	.align	1
	.globl	hal_qdec_enable
	.hidden	hal_qdec_enable
	.type	hal_qdec_enable, @function
hal_qdec_enable:
.LFB10:
	.loc 1 234 1 is_stmt 1
	.cfi_startproc
	.loc 1 263 3
	.loc 1 263 21 is_stmt 0
	li	a5,1
	sb	a5,g_first_data_flag,a4
	.loc 1 264 3 is_stmt 1
	.loc 1 264 60 is_stmt 0
	li	a4,1108348928
	sb	a5,17(a4)
	.loc 1 265 3 is_stmt 1
	.loc 1 265 15 is_stmt 0
	li	a5,2
	sw	a5,qdec_status,a4
	.loc 1 266 3 is_stmt 1
	.loc 1 267 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE10:
	.size	hal_qdec_enable, .-hal_qdec_enable
	.section	.text.hal_qdec_disable,"ax",@progbits
	.align	1
	.globl	hal_qdec_disable
	.hidden	hal_qdec_disable
	.type	hal_qdec_disable, @function
hal_qdec_disable:
.LFB11:
	.loc 1 270 1 is_stmt 1
	.cfi_startproc
	.loc 1 276 3
	.loc 1 276 60 is_stmt 0
	li	a5,1108348928
	sb	zero,17(a5)
	.loc 1 278 3 is_stmt 1
	.loc 1 278 21 is_stmt 0
	sb	zero,g_first_data_flag,a5
	.loc 1 279 3 is_stmt 1
	.loc 1 279 15 is_stmt 0
	li	a5,1
	sw	a5,qdec_status,a4
	.loc 1 280 3 is_stmt 1
	.loc 1 281 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE11:
	.size	hal_qdec_disable, .-hal_qdec_disable
	.section	.text.hal_qdec_register_callback,"ax",@progbits
	.align	1
	.globl	hal_qdec_register_callback
	.hidden	hal_qdec_register_callback
	.type	hal_qdec_register_callback, @function
hal_qdec_register_callback:
.LFB12:
	.loc 1 284 1 is_stmt 1
	.cfi_startproc
.LVL29:
	.loc 1 285 3
	.loc 1 285 6 is_stmt 0
	beq	a0,zero,.L41
	.loc 1 290 3 is_stmt 1
	.loc 1 290 17 is_stmt 0
	sw	a0,qdec_callback,a5
	.loc 1 291 3 is_stmt 1
	.loc 1 291 10 is_stmt 0
	li	a0,0
.LVL30:
	ret
.LVL31:
.L41:
	.loc 1 287 12
	li	a0,-1
.LVL32:
	.loc 1 292 1
	ret
	.cfi_endproc
.LFE12:
	.size	hal_qdec_register_callback, .-hal_qdec_register_callback
	.section	.text.hal_qdec_zcnt_mode_set,"ax",@progbits
	.align	1
	.globl	hal_qdec_zcnt_mode_set
	.hidden	hal_qdec_zcnt_mode_set
	.type	hal_qdec_zcnt_mode_set, @function
hal_qdec_zcnt_mode_set:
.LFB13:
	.loc 1 295 1 is_stmt 1
	.cfi_startproc
.LVL33:
	.loc 1 301 3
	.loc 1 301 6 is_stmt 0
	li	a5,255
	bgtu	a1,a5,.L44
	.loc 1 305 3 is_stmt 1
	.loc 1 305 74 is_stmt 0
	li	a5,1108348928
	andi	a1,a1,0xff
.LVL34:
	sb	a1,6(a5)
	.loc 1 306 3 is_stmt 1
	.loc 1 306 68 is_stmt 0
	andi	a0,a0,0xff
.LVL35:
	sb	a0,7(a5)
	.loc 1 307 3 is_stmt 1
	.loc 1 307 13 is_stmt 0
	li	a5,1
	sw	a5,qdec_mode,a4
	.loc 1 308 3 is_stmt 1
	.loc 1 308 10 is_stmt 0
	li	a0,0
	ret
.LVL36:
.L44:
	.loc 1 303 12
	li	a0,-1
.LVL37:
	.loc 1 309 1
	ret
	.cfi_endproc
.LFE13:
	.size	hal_qdec_zcnt_mode_set, .-hal_qdec_zcnt_mode_set
	.section	.text.hal_qdec_set_latch_clear,"ax",@progbits
	.align	1
	.globl	hal_qdec_set_latch_clear
	.hidden	hal_qdec_set_latch_clear
	.type	hal_qdec_set_latch_clear, @function
hal_qdec_set_latch_clear:
.LFB14:
	.loc 1 312 1 is_stmt 1
	.cfi_startproc
	.loc 1 315 5
	.loc 1 315 29 is_stmt 0
	lbu	a5,qdec_available_data
	.loc 1 322 10
	li	a0,-2
	.loc 1 315 8
	bne	a5,zero,.L45
	.loc 1 317 7 is_stmt 1
	.loc 1 317 80 is_stmt 0
	li	a5,1
	li	a4,1108348928
	sb	a5,40(a4)
	.loc 1 318 7 is_stmt 1
	.loc 1 318 27 is_stmt 0
	sb	a5,qdec_available_data,a4
	.loc 1 319 7 is_stmt 1
	.loc 1 319 14 is_stmt 0
	li	a0,0
.L45:
	.loc 1 323 1
	ret
	.cfi_endproc
.LFE14:
	.size	hal_qdec_set_latch_clear, .-hal_qdec_set_latch_clear
	.section	.text.hal_qdec_get_data,"ax",@progbits
	.align	1
	.globl	hal_qdec_get_data
	.hidden	hal_qdec_get_data
	.type	hal_qdec_get_data, @function
hal_qdec_get_data:
.LFB16:
	.loc 1 339 1 is_stmt 1
	.cfi_startproc
.LVL38:
	.loc 1 340 3
	.loc 1 341 3
	.loc 1 341 27 is_stmt 0
	lbu	a5,qdec_available_data
	.loc 1 341 6
	beq	a5,zero,.L57
	.loc 1 346 3 is_stmt 1
	.loc 1 346 17 is_stmt 0
	lw	a5,qdec_mode
	.loc 1 339 1
	addi	sp,sp,-4
	.cfi_def_cfa_offset 4
.LBB34:
	.loc 1 350 9
	lbu	a4,g_first_data_flag
.LBE34:
	.loc 1 346 6
	bne	a5,zero,.L50
.LBB35:
	.loc 1 348 5 is_stmt 1
	.loc 1 348 85 is_stmt 0
	li	a5,1108348928
	lhu	a5,52(a5)
	slli	a5,a5,16
	srli	a5,a5,16
	.loc 1 348 23
	sh	a5,0(sp)
	.loc 1 349 5 is_stmt 1
	.loc 1 349 25 is_stmt 0
	sb	zero,qdec_available_data,a5
	.loc 1 350 5 is_stmt 1
	.loc 1 350 8 is_stmt 0
	beq	a4,zero,.L51
	.loc 1 352 7 is_stmt 1
	.loc 1 352 17 is_stmt 0
	sh	zero,0(sp)
	.loc 1 353 7 is_stmt 1
	.loc 1 353 25 is_stmt 0
	sb	zero,g_first_data_flag,a5
.L51:
	.loc 1 356 5 is_stmt 1
	.loc 1 356 9 is_stmt 0
	lhu	a5,0(sp)
	.loc 1 356 8
	andi	a5,a5,512
	beq	a5,zero,.L52
	.loc 1 358 7 is_stmt 1
	.loc 1 358 19 is_stmt 0
	lhu	a5,0(sp)
.L68:
.LBE35:
.LBB36:
	.loc 1 376 19
	ori	a5,a5,-1024
	.loc 1 376 17
	slli	a5,a5,16
	srai	a5,a5,16
.LVL39:
.L53:
.LBE36:
	.loc 1 383 3 is_stmt 1
.LBB37:
.LBB38:
	.loc 1 328 3
	.loc 1 328 11 is_stmt 0
	lla	a3,dat_Sum
	lhu	a4,0(a3)
	add	a5,a4,a5
.LVL40:
	slli	a4,a5,16
	srai	a4,a4,16
	sh	a4,0(a3)
	.loc 1 329 3 is_stmt 1
	.loc 1 329 6 is_stmt 0
	andi	a5,a5,1
	bne	a5,zero,.L56
	.loc 1 331 5 is_stmt 1
	.loc 1 331 18 is_stmt 0
	srai	a4,a4,1
	sh	a4,0(a0)
	.loc 1 332 5 is_stmt 1
	.loc 1 332 13 is_stmt 0
	sh	zero,dat_Sum,a5
	.loc 1 333 5 is_stmt 1
.L56:
.LBE38:
.LBE37:
	.loc 1 384 10 is_stmt 0
	li	a0,0
.LVL41:
	.loc 1 385 1
	addi	sp,sp,4
	.cfi_remember_state
	.cfi_def_cfa_offset 0
	jr	ra
.LVL42:
.L52:
	.cfi_restore_state
.LBB39:
	.loc 1 362 7 is_stmt 1
	.loc 1 362 19 is_stmt 0
	lhu	a5,0(sp)
.L69:
.LBE39:
.LBB40:
	.loc 1 380 17
	andi	a5,a5,1023
.LVL43:
	j	.L53
.LVL44:
.L50:
	.loc 1 367 5 is_stmt 1
	.loc 1 367 85 is_stmt 0
	li	a5,1108348928
	lhu	a5,54(a5)
	slli	a5,a5,16
	srli	a5,a5,16
	.loc 1 367 23
	sh	a5,2(sp)
	.loc 1 368 5 is_stmt 1
	.loc 1 368 25 is_stmt 0
	sb	zero,qdec_available_data,a5
	.loc 1 369 5 is_stmt 1
	.loc 1 369 8 is_stmt 0
	beq	a4,zero,.L54
	.loc 1 371 7 is_stmt 1
	.loc 1 371 17 is_stmt 0
	sh	zero,2(sp)
	.loc 1 372 7 is_stmt 1
	.loc 1 372 25 is_stmt 0
	sb	zero,g_first_data_flag,a5
.L54:
	.loc 1 374 5 is_stmt 1
	.loc 1 374 9 is_stmt 0
	lhu	a5,2(sp)
	.loc 1 374 8
	andi	a5,a5,256
	beq	a5,zero,.L55
	.loc 1 376 7 is_stmt 1
	.loc 1 376 19 is_stmt 0
	lhu	a5,2(sp)
	j	.L68
.L55:
	.loc 1 380 7 is_stmt 1
	.loc 1 380 19 is_stmt 0
	lhu	a5,2(sp)
	j	.L69
.L57:
	.cfi_def_cfa_offset 0
.LBE40:
	.loc 1 343 12
	li	a0,-2
.LVL45:
	.loc 1 385 1
	ret
	.cfi_endproc
.LFE16:
	.size	hal_qdec_get_data, .-hal_qdec_get_data
	.section	.text.hal_qdec_enable_hw_sel,"ax",@progbits
	.align	1
	.globl	hal_qdec_enable_hw_sel
	.hidden	hal_qdec_enable_hw_sel
	.type	hal_qdec_enable_hw_sel, @function
hal_qdec_enable_hw_sel:
.LFB17:
	.loc 1 388 1 is_stmt 1
	.cfi_startproc
.LVL46:
	.loc 1 389 3
	.loc 1 389 5 is_stmt 0
	li	a4,1
	bgtu	a0,a4,.L72
	.loc 1 394 3 is_stmt 1
	.loc 1 394 73 is_stmt 0
	li	a5,1108348928
	andi	a0,a0,0xff
.LVL47:
	sb	a0,22(a5)
	.loc 1 395 3 is_stmt 1
	.loc 1 395 70 is_stmt 0
	sb	a4,21(a5)
	.loc 1 397 3 is_stmt 1
	.loc 1 397 58 is_stmt 0
	sb	a4,16(a5)
	.loc 1 398 3 is_stmt 1
	.loc 1 398 10 is_stmt 0
	li	a0,0
	ret
.LVL48:
.L72:
	.loc 1 391 12
	li	a0,-1
.LVL49:
	.loc 1 399 1
	ret
	.cfi_endproc
.LFE17:
	.size	hal_qdec_enable_hw_sel, .-hal_qdec_enable_hw_sel
	.section	.text.hal_qdec_disable_hw_sel,"ax",@progbits
	.align	1
	.globl	hal_qdec_disable_hw_sel
	.hidden	hal_qdec_disable_hw_sel
	.type	hal_qdec_disable_hw_sel, @function
hal_qdec_disable_hw_sel:
.LFB18:
	.loc 1 402 1 is_stmt 1
	.cfi_startproc
	.loc 1 403 3
	.loc 1 403 70 is_stmt 0
	li	a5,1108348928
	sb	zero,21(a5)
	.loc 1 405 3 is_stmt 1
	.loc 1 405 58 is_stmt 0
	li	a4,1
	sb	a4,16(a5)
	.loc 1 406 3 is_stmt 1
	.loc 1 407 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE18:
	.size	hal_qdec_disable_hw_sel, .-hal_qdec_disable_hw_sel
	.section	.text.hal_qdec_sw_sel_group,"ax",@progbits
	.align	1
	.globl	hal_qdec_sw_sel_group
	.hidden	hal_qdec_sw_sel_group
	.type	hal_qdec_sw_sel_group, @function
hal_qdec_sw_sel_group:
.LFB19:
	.loc 1 410 1 is_stmt 1
	.cfi_startproc
.LVL50:
	.loc 1 411 3
	.loc 1 411 5 is_stmt 0
	li	a4,1
	bgtu	a0,a4,.L76
	.loc 1 415 3 is_stmt 1
	.loc 1 415 70 is_stmt 0
	li	a5,1108348928
	andi	a0,a0,0xff
.LVL51:
	sb	a0,20(a5)
	.loc 1 417 3 is_stmt 1
	.loc 1 417 58 is_stmt 0
	sb	a4,16(a5)
	.loc 1 418 3 is_stmt 1
	.loc 1 418 10 is_stmt 0
	li	a0,0
	ret
.LVL52:
.L76:
	.loc 1 413 12
	li	a0,-1
.LVL53:
	.loc 1 419 1
	ret
	.cfi_endproc
.LFE19:
	.size	hal_qdec_sw_sel_group, .-hal_qdec_sw_sel_group
	.section	.text.hal_qdec_select_to_group_a,"ax",@progbits
	.align	1
	.globl	hal_qdec_select_to_group_a
	.hidden	hal_qdec_select_to_group_a
	.type	hal_qdec_select_to_group_a, @function
hal_qdec_select_to_group_a:
.LFB20:
	.loc 1 422 1 is_stmt 1
	.cfi_startproc
	.loc 1 423 3
	.loc 1 424 3
.LBB41:
.LBB42:
	.loc 1 403 3
	.loc 1 403 70 is_stmt 0
	li	a5,1108348928
	sb	zero,21(a5)
	.loc 1 405 3 is_stmt 1
	.loc 1 405 58 is_stmt 0
	li	a4,1
	sb	a4,16(a5)
	.loc 1 406 3 is_stmt 1
.LVL54:
.LBE42:
.LBE41:
	.loc 1 425 3
	.loc 1 430 3
.LBB43:
.LBB44:
	.loc 1 411 3
	.loc 1 415 3
	.loc 1 415 70 is_stmt 0
	sb	zero,20(a5)
	.loc 1 417 3 is_stmt 1
	.loc 1 417 58 is_stmt 0
	sb	a4,16(a5)
	.loc 1 418 3 is_stmt 1
.LVL55:
.LBE44:
.LBE43:
	.loc 1 431 3
	.loc 1 436 3
	.loc 1 436 17 is_stmt 0
	lw	a4,qdec_mode
	.loc 1 436 6
	bne	a4,zero,.L78
	.loc 1 438 5 is_stmt 1
	.loc 1 438 81 is_stmt 0
	sb	zero,32(a5)
	.loc 1 439 5 is_stmt 1
	.loc 1 439 84 is_stmt 0
	sb	zero,36(a5)
.L79:
	.loc 1 446 3 is_stmt 1
	.loc 1 447 1 is_stmt 0
	li	a0,0
	ret
.L78:
	.loc 1 443 5 is_stmt 1
	.loc 1 443 81 is_stmt 0
	sb	zero,33(a5)
	.loc 1 444 5 is_stmt 1
	.loc 1 444 84 is_stmt 0
	sb	zero,37(a5)
	j	.L79
	.cfi_endproc
.LFE20:
	.size	hal_qdec_select_to_group_a, .-hal_qdec_select_to_group_a
	.section	.text.hal_qdec_select_to_group_b,"ax",@progbits
	.align	1
	.globl	hal_qdec_select_to_group_b
	.hidden	hal_qdec_select_to_group_b
	.type	hal_qdec_select_to_group_b, @function
hal_qdec_select_to_group_b:
.LFB21:
	.loc 1 450 1 is_stmt 1
	.cfi_startproc
	.loc 1 451 3
	.loc 1 452 3
.LVL56:
.LBB45:
.LBB46:
	.loc 1 389 3
	.loc 1 394 3
	.loc 1 394 73 is_stmt 0
	li	a5,1108348928
	sb	zero,22(a5)
	.loc 1 395 3 is_stmt 1
	.loc 1 395 70 is_stmt 0
	li	a4,1
	sb	a4,21(a5)
	.loc 1 397 3 is_stmt 1
	.loc 1 397 58 is_stmt 0
	sb	a4,16(a5)
	.loc 1 398 3 is_stmt 1
.LVL57:
.LBE46:
.LBE45:
	.loc 1 453 3
	.loc 1 458 3
.LBB47:
.LBB48:
	.loc 1 411 3
	.loc 1 415 3
	.loc 1 415 70 is_stmt 0
	sb	a4,20(a5)
	.loc 1 417 3 is_stmt 1
	.loc 1 417 58 is_stmt 0
	sb	a4,16(a5)
	.loc 1 418 3 is_stmt 1
.LVL58:
.LBE48:
.LBE47:
	.loc 1 459 3
	.loc 1 464 3
	.loc 1 464 17 is_stmt 0
	lw	a3,qdec_mode
	.loc 1 464 6
	bne	a3,zero,.L81
	.loc 1 466 5 is_stmt 1
	.loc 1 466 81 is_stmt 0
	sb	a4,32(a5)
	.loc 1 467 5 is_stmt 1
	.loc 1 467 84 is_stmt 0
	sb	a4,36(a5)
.L82:
	.loc 1 474 3 is_stmt 1
	.loc 1 475 1 is_stmt 0
	li	a0,0
	ret
.L81:
	.loc 1 471 5 is_stmt 1
	.loc 1 471 81 is_stmt 0
	sb	a4,33(a5)
	.loc 1 472 5 is_stmt 1
	.loc 1 472 84 is_stmt 0
	sb	a4,37(a5)
	j	.L82
	.cfi_endproc
.LFE21:
	.size	hal_qdec_select_to_group_b, .-hal_qdec_select_to_group_b
	.section	.text.hal_qdec_select_to_idle_status,"ax",@progbits
	.align	1
	.globl	hal_qdec_select_to_idle_status
	.hidden	hal_qdec_select_to_idle_status
	.type	hal_qdec_select_to_idle_status, @function
hal_qdec_select_to_idle_status:
.LFB22:
	.loc 1 478 1 is_stmt 1
	.cfi_startproc
	.loc 1 483 3
	.loc 1 484 3
	.loc 1 478 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 484 9
	call	hal_qdec_select_to_group_b
.LVL59:
	.loc 1 485 3 is_stmt 1
	.loc 1 485 6 is_stmt 0
	bne	a0,zero,.L85
	.loc 1 489 3 is_stmt 1
	.loc 1 489 22 is_stmt 0
	li	a5,1
	sw	a5,g_qdec_mode_status,a4
	.loc 1 490 3 is_stmt 1
.LVL60:
.L83:
	.loc 1 491 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL61:
.L85:
	.cfi_restore_state
	.loc 1 487 12
	li	a0,-2
.LVL62:
	j	.L83
	.cfi_endproc
.LFE22:
	.size	hal_qdec_select_to_idle_status, .-hal_qdec_select_to_idle_status
	.section	.text.hal_qdec_select_to_active_status,"ax",@progbits
	.align	1
	.globl	hal_qdec_select_to_active_status
	.hidden	hal_qdec_select_to_active_status
	.type	hal_qdec_select_to_active_status, @function
hal_qdec_select_to_active_status:
.LFB23:
	.loc 1 494 1 is_stmt 1
	.cfi_startproc
	.loc 1 500 3
	.loc 1 501 3
	.loc 1 494 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 501 9
	call	hal_qdec_select_to_group_a
.LVL63:
	.loc 1 502 3 is_stmt 1
	.loc 1 502 6 is_stmt 0
	bne	a0,zero,.L89
	.loc 1 506 3 is_stmt 1
	.loc 1 506 22 is_stmt 0
	sw	zero,g_qdec_mode_status,a5
	.loc 1 507 3 is_stmt 1
.LVL64:
.L87:
	.loc 1 508 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL65:
.L89:
	.cfi_restore_state
	.loc 1 504 12
	li	a0,-2
.LVL66:
	j	.L87
	.cfi_endproc
.LFE23:
	.size	hal_qdec_select_to_active_status, .-hal_qdec_select_to_active_status
	.section	.text.hal_qdec_enable_irq,"ax",@progbits
	.align	1
	.globl	hal_qdec_enable_irq
	.hidden	hal_qdec_enable_irq
	.type	hal_qdec_enable_irq, @function
hal_qdec_enable_irq:
.LFB24:
	.loc 1 511 1 is_stmt 1
	.cfi_startproc
.LVL67:
	.loc 1 512 3
	.loc 1 512 6 is_stmt 0
	li	a4,4
	.loc 1 511 1
	mv	a5,a0
	.loc 1 512 6
	bne	a0,a4,.L92
	.loc 1 514 5 is_stmt 1
	.loc 1 514 81 is_stmt 0
	li	a5,1108348928
	li	a4,1
	sb	a4,32(a5)
	.loc 1 515 5 is_stmt 1
	.loc 1 515 84 is_stmt 0
	sb	a4,36(a5)
.LVL68:
.L95:
	.loc 1 530 10
	li	a0,0
	ret
.LVL69:
.L92:
	.loc 1 517 8 is_stmt 1
	.loc 1 517 11 is_stmt 0
	li	a4,2
	bne	a0,a4,.L94
	.loc 1 519 5 is_stmt 1
	.loc 1 519 81 is_stmt 0
	li	a5,1108348928
	li	a4,1
	sb	a4,33(a5)
	.loc 1 520 5 is_stmt 1
	.loc 1 520 84 is_stmt 0
	sb	a4,37(a5)
	j	.L95
.L94:
	.loc 1 522 8 is_stmt 1
	.loc 1 522 11 is_stmt 0
	li	a4,1
	.loc 1 528 12
	li	a0,-1
.LVL70:
	.loc 1 522 11
	bne	a5,a4,.L91
	.loc 1 524 5 is_stmt 1
	.loc 1 524 84 is_stmt 0
	li	a4,1108348928
	sb	a5,34(a4)
	j	.L95
.L91:
	.loc 1 531 1
	ret
	.cfi_endproc
.LFE24:
	.size	hal_qdec_enable_irq, .-hal_qdec_enable_irq
	.section	.text.hal_qdec_disable_irq,"ax",@progbits
	.align	1
	.globl	hal_qdec_disable_irq
	.hidden	hal_qdec_disable_irq
	.type	hal_qdec_disable_irq, @function
hal_qdec_disable_irq:
.LFB25:
	.loc 1 534 1 is_stmt 1
	.cfi_startproc
.LVL71:
	.loc 1 535 3
	.loc 1 535 6 is_stmt 0
	li	a4,4
	.loc 1 534 1
	mv	a5,a0
	.loc 1 535 6
	bne	a0,a4,.L98
	.loc 1 537 5 is_stmt 1
	.loc 1 537 81 is_stmt 0
	li	a5,1108348928
	sb	zero,32(a5)
	.loc 1 538 5 is_stmt 1
	.loc 1 538 84 is_stmt 0
	sb	zero,36(a5)
.LVL72:
.L101:
	.loc 1 553 10
	li	a0,0
	ret
.LVL73:
.L98:
	.loc 1 540 8 is_stmt 1
	.loc 1 540 11 is_stmt 0
	li	a4,2
	bne	a0,a4,.L100
	.loc 1 542 5 is_stmt 1
	.loc 1 542 81 is_stmt 0
	li	a5,1108348928
	sb	zero,33(a5)
	.loc 1 543 5 is_stmt 1
	.loc 1 543 84 is_stmt 0
	sb	zero,37(a5)
	j	.L101
.L100:
	.loc 1 545 8 is_stmt 1
	.loc 1 545 11 is_stmt 0
	li	a4,1
	.loc 1 551 12
	li	a0,-1
.LVL74:
	.loc 1 545 11
	bne	a5,a4,.L97
	.loc 1 547 5 is_stmt 1
	.loc 1 547 84 is_stmt 0
	li	a5,1108348928
.LVL75:
	sb	zero,34(a5)
	j	.L101
.LVL76:
.L97:
	.loc 1 554 1
	ret
	.cfi_endproc
.LFE25:
	.size	hal_qdec_disable_irq, .-hal_qdec_disable_irq
	.section	.text.hal_qdec_latch_status_is_busy,"ax",@progbits
	.align	1
	.globl	hal_qdec_latch_status_is_busy
	.hidden	hal_qdec_latch_status_is_busy
	.type	hal_qdec_latch_status_is_busy, @function
hal_qdec_latch_status_is_busy:
.LFB26:
	.loc 1 557 1 is_stmt 1
	.cfi_startproc
.LVL77:
	.loc 1 558 3
	.loc 1 559 3
	.loc 1 559 102 is_stmt 0
	li	a4,1108348928
	lbu	a5,34(a4)
	.loc 1 557 1
	addi	sp,sp,-4
	.cfi_def_cfa_offset 4
	.loc 1 559 102
	andi	a5,a5,0xff
	.loc 1 559 20
	sb	a5,3(sp)
	.loc 1 560 3 is_stmt 1
	.loc 1 560 28 is_stmt 0
	lbu	a3,3(sp)
	.loc 1 560 5
	li	a5,1
	beq	a3,a5,.L107
	.loc 1 565 3 is_stmt 1
	.loc 1 565 16 is_stmt 0
	lbu	a4,41(a4)
.LVL78:
	.loc 1 566 3 is_stmt 1
	.loc 1 566 6 is_stmt 0
	bne	a4,a5,.L105
	.loc 1 568 5 is_stmt 1
	.loc 1 568 21 is_stmt 0
	sb	zero,0(a0)
.L106:
	.loc 1 574 10
	li	a0,0
.LVL79:
.L103:
	.loc 1 575 1
	addi	sp,sp,4
	.cfi_remember_state
	.cfi_def_cfa_offset 0
	jr	ra
.LVL80:
.L105:
	.cfi_restore_state
	.loc 1 572 5 is_stmt 1
	.loc 1 572 21 is_stmt 0
	sb	a5,0(a0)
	j	.L106
.LVL81:
.L107:
	.loc 1 562 12
	li	a0,-2
.LVL82:
	j	.L103
	.cfi_endproc
.LFE26:
	.size	hal_qdec_latch_status_is_busy, .-hal_qdec_latch_status_is_busy
	.section	.text.hal_qdec_runnig_config_group_para,"ax",@progbits
	.align	1
	.globl	hal_qdec_runnig_config_group_para
	.hidden	hal_qdec_runnig_config_group_para
	.type	hal_qdec_runnig_config_group_para, @function
hal_qdec_runnig_config_group_para:
.LFB27:
	.loc 1 578 1 is_stmt 1
	.cfi_startproc
.LVL83:
	slli	a3,a1,16
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	srli	a3,a3,16
	sw	ra,20(sp)
	sw	s0,16(sp)
	sw	s1,12(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	sw	a3,4(sp)
.LVL84:
	.loc 1 579 3
	.loc 1 579 6 is_stmt 0
	li	a5,1
	sw	a0,0(sp)
	bgtu	a0,a5,.L114
	.loc 1 585 9
	mv	a0,a1
.LVL85:
	srli	s0,a1,16
	srli	s1,a1,24
	.loc 1 584 3 is_stmt 1
	.loc 1 585 3
	.loc 1 585 9 is_stmt 0
	call	qdec_group_config_para_check
.LVL86:
	.loc 1 586 3 is_stmt 1
	.loc 1 586 6 is_stmt 0
	bne	a0,zero,.L114
	.loc 1 591 5
	lw	a4,0(sp)
	lw	a3,4(sp)
	andi	s0,s0,0xff
	.loc 1 591 3 is_stmt 1
	lla	a5,g_qdec_cfg
	.loc 1 591 5 is_stmt 0
	bne	a4,zero,.L111
	.loc 1 593 5 is_stmt 1
	.loc 1 593 81 is_stmt 0
	li	a4,1108348928
	sh	a3,8(a4)
	.loc 1 594 5 is_stmt 1
	.loc 1 594 81 is_stmt 0
	sb	s0,10(a4)
	.loc 1 595 5 is_stmt 1
	.loc 1 595 80 is_stmt 0
	sb	s1,11(a4)
	.loc 1 596 5 is_stmt 1
	.loc 1 596 28 is_stmt 0
	sh	a3,14(a5)
	sb	s0,16(a5)
	sb	s1,17(a5)
.L112:
	.loc 1 604 3 is_stmt 1
	.loc 1 604 58 is_stmt 0
	li	a5,1108348928
	li	a4,1
	sb	a4,16(a5)
	.loc 1 606 3 is_stmt 1
.LVL87:
.L109:
	.loc 1 607 1 is_stmt 0
	lw	ra,20(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	lw	s1,12(sp)
	.cfi_restore 9
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
.LVL88:
	jr	ra
.LVL89:
.L111:
	.cfi_restore_state
	.loc 1 598 5 is_stmt 1
	.loc 1 598 81 is_stmt 0
	li	a4,1108348928
.LVL90:
	sh	a3,12(a4)
	.loc 1 599 5 is_stmt 1
	.loc 1 599 81 is_stmt 0
	sb	s0,14(a4)
	.loc 1 600 5 is_stmt 1
	.loc 1 600 80 is_stmt 0
	sb	s1,15(a4)
	.loc 1 601 5 is_stmt 1
	.loc 1 601 28 is_stmt 0
	sh	a3,18(a5)
	sb	s0,20(a5)
	sb	s1,21(a5)
	j	.L112
.LVL91:
.L114:
	.loc 1 581 12
	li	a0,-1
	j	.L109
	.cfi_endproc
.LFE27:
	.size	hal_qdec_runnig_config_group_para, .-hal_qdec_runnig_config_group_para
	.section	.text.hal_qdec_data_getting_type_set,"ax",@progbits
	.align	1
	.globl	hal_qdec_data_getting_type_set
	.hidden	hal_qdec_data_getting_type_set
	.type	hal_qdec_data_getting_type_set, @function
hal_qdec_data_getting_type_set:
.LFB28:
	.loc 1 610 1 is_stmt 1
	.cfi_startproc
.LVL92:
	.loc 1 611 3
	.loc 1 612 3
	.loc 1 610 1 is_stmt 0
	mv	a5,a0
	.loc 1 612 6
	bne	a0,zero,.L117
	.loc 1 614 5 is_stmt 1
.LVL93:
.LBB49:
.LBB50:
	.loc 1 512 3
	.loc 1 517 8
	.loc 1 522 8
	.loc 1 524 5
	.loc 1 524 84 is_stmt 0
	li	a5,1108348928
	li	a4,1
	sb	a4,34(a5)
.LVL94:
.LBE50:
.LBE49:
	.loc 1 615 5 is_stmt 1
.L119:
	.loc 1 632 10 is_stmt 0
	li	a0,0
	ret
.LVL95:
.L117:
	.loc 1 620 8 is_stmt 1
	.loc 1 620 11 is_stmt 0
	li	a4,1
	.loc 1 630 12
	li	a0,-1
.LVL96:
	.loc 1 620 11
	bne	a5,a4,.L116
	.loc 1 622 5 is_stmt 1
.LVL97:
.LBB51:
.LBB52:
	.loc 1 535 3
	.loc 1 540 8
	.loc 1 545 8
	.loc 1 547 5
	.loc 1 547 84 is_stmt 0
	li	a5,1108348928
.LVL98:
	sb	zero,34(a5)
.LVL99:
.LBE52:
.LBE51:
	.loc 1 623 5 is_stmt 1
	j	.L119
.LVL100:
.L116:
	.loc 1 633 1 is_stmt 0
	ret
	.cfi_endproc
.LFE28:
	.size	hal_qdec_data_getting_type_set, .-hal_qdec_data_getting_type_set
	.section	.text.hal_qdec_get_config_group_para,"ax",@progbits
	.align	1
	.globl	hal_qdec_get_config_group_para
	.hidden	hal_qdec_get_config_group_para
	.type	hal_qdec_get_config_group_para, @function
hal_qdec_get_config_group_para:
.LFB29:
	.loc 1 636 1 is_stmt 1
	.cfi_startproc
.LVL101:
	.loc 1 637 3
	.loc 1 637 6 is_stmt 0
	li	a5,1
	bgtu	a0,a5,.L125
	.loc 1 642 3 is_stmt 1
	lla	a5,g_qdec_cfg
	.loc 1 642 5 is_stmt 0
	bne	a0,zero,.L123
	.loc 1 644 5 is_stmt 1
	.loc 1 644 19 is_stmt 0
	lhu	a4,14(a5)
	sh	a4,0(a1)
	lhu	a5,16(a5)
.L126:
	sh	a5,2(a1)
	.loc 1 648 10
	li	a0,0
.LVL102:
	ret
.LVL103:
.L123:
	.loc 1 646 5 is_stmt 1
	.loc 1 646 19 is_stmt 0
	lhu	a4,18(a5)
	sh	a4,0(a1)
	lhu	a5,20(a5)
	j	.L126
.L125:
	.loc 1 639 12
	li	a0,-1
.LVL104:
	.loc 1 649 1
	ret
	.cfi_endproc
.LFE29:
	.size	hal_qdec_get_config_group_para, .-hal_qdec_get_config_group_para
	.section	.text.hal_qdec_get_mode_status,"ax",@progbits
	.align	1
	.globl	hal_qdec_get_mode_status
	.hidden	hal_qdec_get_mode_status
	.type	hal_qdec_get_mode_status, @function
hal_qdec_get_mode_status:
.LFB30:
	.loc 1 652 1 is_stmt 1
	.cfi_startproc
	.loc 1 653 3
	.loc 1 654 1 is_stmt 0
	lw	a0,g_qdec_mode_status
	ret
	.cfi_endproc
.LFE30:
	.size	hal_qdec_get_mode_status, .-hal_qdec_get_mode_status
	.section	.text.hal_qdec_get_irq_status,"ax",@progbits
	.align	1
	.globl	hal_qdec_get_irq_status
	.hidden	hal_qdec_get_irq_status
	.type	hal_qdec_get_irq_status, @function
hal_qdec_get_irq_status:
.LFB31:
	.loc 1 657 1 is_stmt 1
	.cfi_startproc
.LVL105:
	.loc 1 658 3
	.loc 1 658 6 is_stmt 0
	li	a4,4
	.loc 1 657 1
	mv	a5,a0
	.loc 1 658 6
	bne	a0,a4,.L129
	.loc 1 660 5 is_stmt 1
	.loc 1 660 77 is_stmt 0
	li	a5,1108348928
	lbu	a5,32(a5)
.LVL106:
.L134:
	sw	a5,0(a1)
	.loc 1 673 10
	li	a0,0
	ret
.LVL107:
.L129:
	.loc 1 662 8 is_stmt 1
	.loc 1 662 11 is_stmt 0
	li	a4,2
	bne	a0,a4,.L131
	.loc 1 664 5 is_stmt 1
	.loc 1 664 77 is_stmt 0
	li	a5,1108348928
	lbu	a5,33(a5)
	j	.L134
.L131:
	.loc 1 666 8 is_stmt 1
	.loc 1 666 11 is_stmt 0
	li	a4,1
	.loc 1 671 12
	li	a0,-1
.LVL108:
	.loc 1 666 11
	bne	a5,a4,.L128
	.loc 1 668 5 is_stmt 1
	.loc 1 668 77 is_stmt 0
	li	a5,1108348928
.LVL109:
	lbu	a5,34(a5)
	j	.L134
.LVL110:
.L128:
	.loc 1 674 1
	ret
	.cfi_endproc
.LFE31:
	.size	hal_qdec_get_irq_status, .-hal_qdec_get_irq_status
	.section	.text.hal_qdec_set_z_sum_threshold,"ax",@progbits
	.align	1
	.globl	hal_qdec_set_z_sum_threshold
	.hidden	hal_qdec_set_z_sum_threshold
	.type	hal_qdec_set_z_sum_threshold, @function
hal_qdec_set_z_sum_threshold:
.LFB32:
	.loc 1 677 1 is_stmt 1
	.cfi_startproc
.LVL111:
	.loc 1 678 3
	.loc 1 678 6 is_stmt 0
	li	a5,511
	bgtu	a0,a5,.L137
	.loc 1 682 3 is_stmt 1
	.loc 1 682 24 is_stmt 0
	sh	a0,g_qdec_cfg+12,a5
	.loc 1 683 3 is_stmt 1
	.loc 1 683 72 is_stmt 0
	li	a5,1108348928
	sh	a0,4(a5)
	.loc 1 685 3 is_stmt 1
	.loc 1 685 58 is_stmt 0
	li	a4,1
	sb	a4,16(a5)
	.loc 1 686 3 is_stmt 1
	.loc 1 686 10 is_stmt 0
	li	a0,0
.LVL112:
	ret
.LVL113:
.L137:
	.loc 1 680 12
	li	a0,-1
.LVL114:
	.loc 1 687 1
	ret
	.cfi_endproc
.LFE32:
	.size	hal_qdec_set_z_sum_threshold, .-hal_qdec_set_z_sum_threshold
	.section	.text.hal_qdec_get_z_sum_threshold,"ax",@progbits
	.align	1
	.globl	hal_qdec_get_z_sum_threshold
	.hidden	hal_qdec_get_z_sum_threshold
	.type	hal_qdec_get_z_sum_threshold, @function
hal_qdec_get_z_sum_threshold:
.LFB33:
	.loc 1 690 1 is_stmt 1
	.cfi_startproc
.LVL115:
	.loc 1 691 3
	.loc 1 692 3
	.loc 1 690 1 is_stmt 0
	mv	a5,a0
	.loc 1 692 6
	beq	a0,zero,.L140
	.loc 1 697 3 is_stmt 1
	.loc 1 697 73 is_stmt 0
	li	a4,1108348928
	lhu	a3,4(a4)
.LVL116:
	.loc 1 698 3 is_stmt 1
	.loc 1 698 5 is_stmt 0
	lhu	a4,g_qdec_cfg+12
	.loc 1 701 12
	li	a0,-2
.LVL117:
	.loc 1 698 5
	bne	a4,a3,.L138
	.loc 1 703 3 is_stmt 1
	.loc 1 703 14 is_stmt 0
	sh	a4,0(a5)
	.loc 1 704 3 is_stmt 1
	.loc 1 704 10 is_stmt 0
	li	a0,0
	ret
.LVL118:
.L140:
	.loc 1 694 12
	li	a0,-1
.LVL119:
.L138:
	.loc 1 705 1
	ret
	.cfi_endproc
.LFE33:
	.size	hal_qdec_get_z_sum_threshold, .-hal_qdec_get_z_sum_threshold
	.section	.text.hal_qdec_get_hw_sel_cfg,"ax",@progbits
	.align	1
	.globl	hal_qdec_get_hw_sel_cfg
	.hidden	hal_qdec_get_hw_sel_cfg
	.type	hal_qdec_get_hw_sel_cfg, @function
hal_qdec_get_hw_sel_cfg:
.LFB34:
	.loc 1 708 1 is_stmt 1
	.cfi_startproc
.LVL120:
	.loc 1 709 3
	.loc 1 708 1 is_stmt 0
	mv	a5,a0
	.loc 1 711 12
	li	a0,-1
.LVL121:
	.loc 1 709 5
	beq	a5,zero,.L142
	.loc 1 709 28 discriminator 1
	beq	a1,zero,.L142
	.loc 1 713 3 is_stmt 1
	.loc 1 713 11 is_stmt 0
	li	a3,1108348928
	lbu	a4,21(a3)
.LVL122:
	.loc 1 714 3 is_stmt 1
	.loc 1 714 5 is_stmt 0
	snez	a4,a4
.LVL123:
	sw	a4,0(a5)
	.loc 1 720 3 is_stmt 1
	.loc 1 720 11 is_stmt 0
	lbu	a5,22(a3)
.LVL124:
	.loc 1 721 3 is_stmt 1
	.loc 1 721 5 is_stmt 0
	bne	a5,zero,.L144
	.loc 1 723 5 is_stmt 1
	.loc 1 723 12 is_stmt 0
	sw	zero,0(a1)
.LVL125:
.L145:
	.loc 1 727 10
	li	a0,0
	ret
.LVL126:
.L144:
	.loc 1 725 5 is_stmt 1
	.loc 1 725 12 is_stmt 0
	li	a5,1
.LVL127:
	sw	a5,0(a1)
	j	.L145
.LVL128:
.L142:
	.loc 1 728 1
	ret
	.cfi_endproc
.LFE34:
	.size	hal_qdec_get_hw_sel_cfg, .-hal_qdec_get_hw_sel_cfg
	.section	.sbss.dat_Sum,"aw",@nobits
	.align	1
	.type	dat_Sum, @object
	.size	dat_Sum, 2
dat_Sum:
	.zero	2
	.hidden	qdec_callback
	.globl	qdec_callback
	.section	.sbss.qdec_callback,"aw",@nobits
	.align	2
	.type	qdec_callback, @object
	.size	qdec_callback, 4
qdec_callback:
	.zero	4
	.hidden	g_qdec_mode_status
	.globl	g_qdec_mode_status
	.section	.sbss.g_qdec_mode_status,"aw",@nobits
	.align	2
	.type	g_qdec_mode_status, @object
	.size	g_qdec_mode_status, 4
g_qdec_mode_status:
	.zero	4
	.section	.sbss.qdec_available_data,"aw",@nobits
	.type	qdec_available_data, @object
	.size	qdec_available_data, 1
qdec_available_data:
	.zero	1
	.section	.sbss.g_first_data_flag,"aw",@nobits
	.type	g_first_data_flag, @object
	.size	g_first_data_flag, 1
g_first_data_flag:
	.zero	1
	.section	.bss.g_qdec_cfg,"aw",@nobits
	.align	2
	.type	g_qdec_cfg, @object
	.size	g_qdec_cfg, 24
g_qdec_cfg:
	.zero	24
	.section	.sbss.qdec_mode,"aw",@nobits
	.align	2
	.type	qdec_mode, @object
	.size	qdec_mode, 4
qdec_mode:
	.zero	4
	.section	.sbss.qdec_status,"aw",@nobits
	.align	2
	.type	qdec_status, @object
	.size	qdec_status, 4
qdec_status:
	.zero	4
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_qdec.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_qdec.h"
	.file 6 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 7 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 8 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 9 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1618
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x31
	.4byte	.LASF310
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL47
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0xa
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0xa
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0xa
	.byte	0x2
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0xa
	.byte	0x1
	.byte	0x6
	.4byte	.LASF5
	.uleb128 0x5
	.4byte	.LASF9
	.byte	0x2
	.byte	0x25
	.byte	0x13
	.4byte	0x4e
	.uleb128 0xa
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0xa
	.byte	0x4
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0xa
	.byte	0x8
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x5
	.4byte	.LASF10
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x79
	.uleb128 0x7
	.4byte	0x63
	.uleb128 0x11
	.4byte	0x6f
	.uleb128 0xa
	.byte	0x1
	.byte	0x8
	.4byte	.LASF11
	.uleb128 0x5
	.4byte	.LASF12
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x34
	.uleb128 0x7
	.4byte	0x80
	.uleb128 0x11
	.4byte	0x8c
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0xac
	.uleb128 0x7
	.4byte	0x96
	.uleb128 0x11
	.4byte	0xa2
	.uleb128 0xa
	.byte	0x4
	.byte	0x7
	.4byte	.LASF14
	.uleb128 0x32
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x33
	.4byte	.LASF311
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x3
	.2byte	0x128
	.byte	0x11
	.4byte	0x140
	.uleb128 0x2
	.4byte	.LASF15
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF16
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF17
	.byte	0xb
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x11
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x12
	.uleb128 0x2
	.4byte	.LASF21
	.byte	0x13
	.uleb128 0x2
	.4byte	.LASF22
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF23
	.byte	0x15
	.uleb128 0x2
	.4byte	.LASF24
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF25
	.byte	0x17
	.uleb128 0x2
	.4byte	.LASF26
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF27
	.byte	0x19
	.uleb128 0x2
	.4byte	.LASF28
	.byte	0x1a
	.uleb128 0x2
	.4byte	.LASF29
	.byte	0x1b
	.uleb128 0x2
	.4byte	.LASF30
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF31
	.byte	0x1d
	.uleb128 0x2
	.4byte	.LASF32
	.byte	0x1e
	.uleb128 0x2
	.4byte	.LASF33
	.byte	0x1f
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF34
	.byte	0x3
	.2byte	0x13c
	.byte	0x7
	.4byte	0xba
	.uleb128 0x1b
	.4byte	.LASF35
	.byte	0x3
	.2byte	0x13e
	.byte	0x17
	.4byte	0x140
	.uleb128 0x1c
	.4byte	0x74
	.4byte	0x16a
	.uleb128 0x1d
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x11
	.4byte	0x15a
	.uleb128 0x7
	.4byte	0x16a
	.uleb128 0x7
	.4byte	0x16a
	.uleb128 0x7
	.4byte	0x16a
	.uleb128 0x7
	.4byte	0x16a
	.uleb128 0x7
	.4byte	0x16a
	.uleb128 0x7
	.4byte	0x16a
	.uleb128 0x7
	.4byte	0x16a
	.uleb128 0x7
	.4byte	0x16a
	.uleb128 0x7
	.4byte	0x16a
	.uleb128 0x1c
	.4byte	0x74
	.4byte	0x1ac
	.uleb128 0x1d
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	0x19c
	.uleb128 0x7
	.4byte	0x1ac
	.uleb128 0x1c
	.4byte	0xa2
	.4byte	0x1c6
	.uleb128 0x1d
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x7
	.4byte	0x1b6
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x28
	.byte	0x5
	.4byte	0x1fc
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x4
	.byte	0x2a
	.byte	0x18
	.4byte	0x6f
	.byte	0
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x4
	.byte	0x2b
	.byte	0x18
	.4byte	0x6f
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0x2c
	.byte	0x1e
	.4byte	0x16f
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0x26
	.4byte	0x219
	.uleb128 0x3
	.4byte	.LASF39
	.byte	0x2d
	.byte	0x7
	.4byte	0x1cb
	.uleb128 0x3
	.4byte	.LASF40
	.byte	0x2e
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x33
	.byte	0x5
	.4byte	0x24a
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x4
	.byte	0x35
	.byte	0x19
	.4byte	0x8c
	.byte	0
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x4
	.byte	0x36
	.byte	0x18
	.4byte	0x6f
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x4
	.byte	0x37
	.byte	0x18
	.4byte	0x6f
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0x31
	.4byte	0x267
	.uleb128 0x3
	.4byte	.LASF44
	.byte	0x38
	.byte	0x7
	.4byte	0x219
	.uleb128 0x3
	.4byte	.LASF45
	.byte	0x39
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x3e
	.byte	0x5
	.4byte	0x298
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x4
	.byte	0x40
	.byte	0x19
	.4byte	0x8c
	.byte	0
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0x4
	.byte	0x41
	.byte	0x18
	.4byte	0x6f
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x4
	.byte	0x42
	.byte	0x18
	.4byte	0x6f
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0x3c
	.4byte	0x2b5
	.uleb128 0x3
	.4byte	.LASF49
	.byte	0x43
	.byte	0x7
	.4byte	0x267
	.uleb128 0x3
	.4byte	.LASF50
	.byte	0x44
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x49
	.byte	0x5
	.4byte	0x2e6
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x4
	.byte	0x4b
	.byte	0x19
	.4byte	0x8c
	.byte	0
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x4
	.byte	0x4c
	.byte	0x18
	.4byte	0x6f
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x4
	.byte	0x4d
	.byte	0x18
	.4byte	0x6f
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0x47
	.4byte	0x303
	.uleb128 0x3
	.4byte	.LASF54
	.byte	0x4e
	.byte	0x7
	.4byte	0x2b5
	.uleb128 0x3
	.4byte	.LASF55
	.byte	0x4f
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x54
	.byte	0x5
	.4byte	0x341
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x4
	.byte	0x56
	.byte	0x18
	.4byte	0x6f
	.byte	0
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x4
	.byte	0x57
	.byte	0x18
	.4byte	0x6f
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0x58
	.byte	0x1e
	.4byte	0x74
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x4
	.byte	0x59
	.byte	0x18
	.4byte	0x6f
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0x52
	.4byte	0x35e
	.uleb128 0x3
	.4byte	.LASF59
	.byte	0x5a
	.byte	0x7
	.4byte	0x303
	.uleb128 0x3
	.4byte	.LASF60
	.byte	0x5b
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x60
	.byte	0x5
	.4byte	0x39c
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x4
	.byte	0x62
	.byte	0x18
	.4byte	0x6f
	.byte	0
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x4
	.byte	0x63
	.byte	0x18
	.4byte	0x6f
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x4
	.byte	0x64
	.byte	0x18
	.4byte	0x6f
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0x65
	.byte	0x1e
	.4byte	0x74
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0x5e
	.4byte	0x3b9
	.uleb128 0x3
	.4byte	.LASF64
	.byte	0x66
	.byte	0x7
	.4byte	0x35e
	.uleb128 0x3
	.4byte	.LASF65
	.byte	0x67
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x6e
	.byte	0x5
	.4byte	0x3f7
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x4
	.byte	0x70
	.byte	0x18
	.4byte	0x6f
	.byte	0
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x4
	.byte	0x71
	.byte	0x18
	.4byte	0x6f
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x4
	.byte	0x72
	.byte	0x18
	.4byte	0x6f
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0x73
	.byte	0x1e
	.4byte	0x74
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0x6c
	.4byte	0x414
	.uleb128 0x3
	.4byte	.LASF69
	.byte	0x74
	.byte	0x7
	.4byte	0x3b9
	.uleb128 0x3
	.4byte	.LASF70
	.byte	0x75
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x7a
	.byte	0x5
	.4byte	0x445
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x4
	.byte	0x7c
	.byte	0x18
	.4byte	0x6f
	.byte	0
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x4
	.byte	0x7d
	.byte	0x18
	.4byte	0x6f
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0x7e
	.byte	0x1e
	.4byte	0x174
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0x78
	.4byte	0x462
	.uleb128 0x3
	.4byte	.LASF73
	.byte	0x7f
	.byte	0x7
	.4byte	0x414
	.uleb128 0x3
	.4byte	.LASF74
	.byte	0x80
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x85
	.byte	0x5
	.4byte	0x493
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x4
	.byte	0x87
	.byte	0x18
	.4byte	0x6f
	.byte	0
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x4
	.byte	0x88
	.byte	0x1e
	.4byte	0x74
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0x89
	.byte	0x1e
	.4byte	0x179
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0x83
	.4byte	0x4b0
	.uleb128 0x3
	.4byte	.LASF77
	.byte	0x8a
	.byte	0x7
	.4byte	0x462
	.uleb128 0x3
	.4byte	.LASF78
	.byte	0x8b
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x90
	.byte	0x5
	.4byte	0x4ee
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x4
	.byte	0x92
	.byte	0x18
	.4byte	0x6f
	.byte	0
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x4
	.byte	0x93
	.byte	0x18
	.4byte	0x6f
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x4
	.byte	0x94
	.byte	0x18
	.4byte	0x6f
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0x95
	.byte	0x1e
	.4byte	0x74
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0x8e
	.4byte	0x50b
	.uleb128 0x3
	.4byte	.LASF82
	.byte	0x96
	.byte	0x7
	.4byte	0x4b0
	.uleb128 0x3
	.4byte	.LASF83
	.byte	0x97
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x9c
	.byte	0x5
	.4byte	0x53c
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x4
	.byte	0x9e
	.byte	0x18
	.4byte	0x6f
	.byte	0
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x4
	.byte	0x9f
	.byte	0x18
	.4byte	0x6f
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0xa0
	.byte	0x1e
	.4byte	0x17e
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0x9a
	.4byte	0x559
	.uleb128 0x3
	.4byte	.LASF86
	.byte	0xa1
	.byte	0x7
	.4byte	0x50b
	.uleb128 0x3
	.4byte	.LASF87
	.byte	0xa2
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0xa7
	.byte	0x5
	.4byte	0x57d
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x4
	.byte	0xa9
	.byte	0x1f
	.4byte	0x91
	.byte	0
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x4
	.byte	0xaa
	.byte	0x1f
	.4byte	0x91
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0xa5
	.4byte	0x59a
	.uleb128 0x3
	.4byte	.LASF90
	.byte	0xab
	.byte	0x7
	.4byte	0x559
	.uleb128 0x3
	.4byte	.LASF91
	.byte	0xac
	.byte	0x1d
	.4byte	0xa7
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0xb1
	.byte	0x5
	.4byte	0x5be
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x4
	.byte	0xb3
	.byte	0x1f
	.4byte	0x91
	.byte	0
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x4
	.byte	0xb4
	.byte	0x1f
	.4byte	0x91
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0xaf
	.4byte	0x5db
	.uleb128 0x3
	.4byte	.LASF94
	.byte	0xb5
	.byte	0x7
	.4byte	0x59a
	.uleb128 0x3
	.4byte	.LASF95
	.byte	0xb6
	.byte	0x1d
	.4byte	0xa7
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0xbd
	.byte	0x5
	.4byte	0x60c
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x4
	.byte	0xbf
	.byte	0x18
	.4byte	0x6f
	.byte	0
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x4
	.byte	0xc0
	.byte	0x1e
	.4byte	0x74
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0xc1
	.byte	0x1e
	.4byte	0x183
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0xbb
	.4byte	0x629
	.uleb128 0x3
	.4byte	.LASF98
	.byte	0xc2
	.byte	0x7
	.4byte	0x5db
	.uleb128 0x3
	.4byte	.LASF99
	.byte	0xc3
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0xc8
	.byte	0x5
	.4byte	0x65a
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x4
	.byte	0xca
	.byte	0x1e
	.4byte	0x74
	.byte	0
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x4
	.byte	0xcb
	.byte	0x1e
	.4byte	0x74
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0xcc
	.byte	0x1e
	.4byte	0x188
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0xc6
	.4byte	0x677
	.uleb128 0x3
	.4byte	.LASF101
	.byte	0xcd
	.byte	0x7
	.4byte	0x629
	.uleb128 0x3
	.4byte	.LASF102
	.byte	0xce
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0xd3
	.byte	0x5
	.4byte	0x6b5
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x4
	.byte	0xd5
	.byte	0x1e
	.4byte	0x74
	.byte	0
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x4
	.byte	0xd6
	.byte	0x1e
	.4byte	0x74
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x4
	.byte	0xd7
	.byte	0x1e
	.4byte	0x74
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0xd8
	.byte	0x1e
	.4byte	0x1b1
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0xd1
	.4byte	0x6d2
	.uleb128 0x3
	.4byte	.LASF106
	.byte	0xd9
	.byte	0x7
	.4byte	0x677
	.uleb128 0x3
	.4byte	.LASF107
	.byte	0xda
	.byte	0x1d
	.4byte	0xa7
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0xdf
	.byte	0x5
	.4byte	0x703
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x4
	.byte	0xe1
	.byte	0x1e
	.4byte	0x74
	.byte	0
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x4
	.byte	0xe2
	.byte	0x1e
	.4byte	0x74
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0xe3
	.byte	0x1e
	.4byte	0x18d
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0xdd
	.4byte	0x720
	.uleb128 0x3
	.4byte	.LASF110
	.byte	0xe4
	.byte	0x7
	.4byte	0x6d2
	.uleb128 0x3
	.4byte	.LASF111
	.byte	0xe5
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0xea
	.byte	0x5
	.4byte	0x751
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x4
	.byte	0xec
	.byte	0x1e
	.4byte	0x74
	.byte	0
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x4
	.byte	0xed
	.byte	0x1e
	.4byte	0x74
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0xee
	.byte	0x1e
	.4byte	0x192
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0xe8
	.4byte	0x76e
	.uleb128 0x3
	.4byte	.LASF114
	.byte	0xef
	.byte	0x7
	.4byte	0x720
	.uleb128 0x3
	.4byte	.LASF115
	.byte	0xf0
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0xf5
	.byte	0x5
	.4byte	0x79f
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x4
	.byte	0xf7
	.byte	0x1e
	.4byte	0x74
	.byte	0
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x4
	.byte	0xf8
	.byte	0x1e
	.4byte	0x74
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0xf9
	.byte	0x1e
	.4byte	0x197
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.byte	0xf3
	.4byte	0x7bc
	.uleb128 0x3
	.4byte	.LASF118
	.byte	0xfa
	.byte	0x7
	.4byte	0x76e
	.uleb128 0x3
	.4byte	.LASF119
	.byte	0xfb
	.byte	0x17
	.4byte	0xa2
	.byte	0
	.uleb128 0x4
	.byte	0x68
	.byte	0x4
	.byte	0x24
	.byte	0x9
	.4byte	0x8fe
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x4
	.byte	0x2f
	.byte	0x5
	.4byte	0x1fc
	.byte	0
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x4
	.byte	0x3a
	.byte	0x5
	.4byte	0x24a
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x4
	.byte	0x45
	.byte	0x5
	.4byte	0x298
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x4
	.byte	0x50
	.byte	0x5
	.4byte	0x2e6
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x4
	.byte	0x5c
	.byte	0x5
	.4byte	0x341
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x4
	.byte	0x68
	.byte	0x5
	.4byte	0x39c
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x4
	.byte	0x6a
	.byte	0x15
	.4byte	0x1c6
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x4
	.byte	0x76
	.byte	0x5
	.4byte	0x3f7
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x4
	.byte	0x81
	.byte	0x5
	.4byte	0x445
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x4
	.byte	0x8c
	.byte	0x5
	.4byte	0x493
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x4
	.byte	0x98
	.byte	0x5
	.4byte	0x4ee
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x4
	.byte	0xa3
	.byte	0x5
	.4byte	0x53c
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x4
	.byte	0xad
	.byte	0x5
	.4byte	0x57d
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x4
	.byte	0xb7
	.byte	0x5
	.4byte	0x5be
	.byte	0x38
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x4
	.byte	0xb9
	.byte	0x15
	.4byte	0x1c6
	.byte	0x3c
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x4
	.byte	0xc4
	.byte	0x5
	.4byte	0x60c
	.byte	0x44
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x4
	.byte	0xcf
	.byte	0x5
	.4byte	0x65a
	.byte	0x48
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x4
	.byte	0xdb
	.byte	0x5
	.4byte	0x6b5
	.byte	0x4c
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x4
	.byte	0xe6
	.byte	0x5
	.4byte	0x703
	.byte	0x50
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0x4
	.byte	0xf1
	.byte	0x5
	.4byte	0x751
	.byte	0x54
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0x4
	.byte	0xfc
	.byte	0x5
	.4byte	0x79f
	.byte	0x58
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0x4
	.byte	0xfe
	.byte	0x15
	.4byte	0xa2
	.byte	0x5c
	.uleb128 0x22
	.4byte	.LASF142
	.2byte	0x100
	.byte	0x15
	.4byte	0xa2
	.byte	0x60
	.uleb128 0x22
	.4byte	.LASF143
	.2byte	0x101
	.byte	0x1b
	.4byte	0xa7
	.byte	0x64
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF144
	.byte	0x4
	.2byte	0x103
	.byte	0x3
	.4byte	0x7bc
	.uleb128 0x7
	.4byte	0x8fe
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x31
	.byte	0x1
	.4byte	0x929
	.uleb128 0x2
	.4byte	.LASF145
	.byte	0
	.uleb128 0x2
	.4byte	.LASF146
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF147
	.byte	0x5
	.byte	0x34
	.byte	0x3
	.4byte	0x910
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x37
	.byte	0x1
	.4byte	0x94e
	.uleb128 0x2
	.4byte	.LASF148
	.byte	0
	.uleb128 0x2
	.4byte	.LASF149
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF150
	.byte	0x5
	.byte	0x3a
	.byte	0x3
	.4byte	0x935
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x3d
	.byte	0x1
	.4byte	0x973
	.uleb128 0x2
	.4byte	.LASF151
	.byte	0
	.uleb128 0x2
	.4byte	.LASF152
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF153
	.byte	0x5
	.byte	0x40
	.byte	0x3
	.4byte	0x95a
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x43
	.byte	0x1
	.4byte	0x998
	.uleb128 0x2
	.4byte	.LASF154
	.byte	0
	.uleb128 0x2
	.4byte	.LASF155
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF156
	.byte	0x5
	.byte	0x46
	.byte	0x3
	.4byte	0x97f
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x49
	.byte	0x1
	.4byte	0x9bd
	.uleb128 0x2
	.4byte	.LASF157
	.byte	0
	.uleb128 0x2
	.4byte	.LASF158
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF159
	.byte	0x5
	.byte	0x4c
	.byte	0x3
	.4byte	0x9a4
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x4f
	.byte	0x1
	.4byte	0x9e2
	.uleb128 0x2
	.4byte	.LASF160
	.byte	0
	.uleb128 0x2
	.4byte	.LASF161
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF162
	.byte	0x5
	.byte	0x52
	.byte	0x3
	.4byte	0x9c9
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x55
	.byte	0x1
	.4byte	0xa07
	.uleb128 0x2
	.4byte	.LASF163
	.byte	0
	.uleb128 0x2
	.4byte	.LASF164
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF165
	.byte	0x5
	.byte	0x58
	.byte	0x3
	.4byte	0x9ee
	.uleb128 0x7
	.4byte	0xa07
	.uleb128 0xc
	.byte	0x5
	.4byte	0xb3
	.byte	0x5c
	.byte	0x1
	.4byte	0xa37
	.uleb128 0x23
	.4byte	.LASF166
	.sleb128 -2
	.uleb128 0x23
	.4byte	.LASF167
	.sleb128 -1
	.uleb128 0x2
	.4byte	.LASF168
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF169
	.byte	0x5
	.byte	0x60
	.byte	0x3
	.4byte	0xa18
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x62
	.byte	0xe
	.4byte	0xa62
	.uleb128 0x2
	.4byte	.LASF170
	.byte	0
	.uleb128 0x2
	.4byte	.LASF171
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF172
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.4byte	.LASF173
	.byte	0x5
	.byte	0x66
	.byte	0x3
	.4byte	0xa43
	.uleb128 0x7
	.4byte	0xa62
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x68
	.byte	0xe
	.4byte	0xa92
	.uleb128 0x2
	.4byte	.LASF174
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF175
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF176
	.byte	0x4
	.byte	0
	.uleb128 0x5
	.4byte	.LASF177
	.byte	0x5
	.byte	0x6c
	.byte	0x3
	.4byte	0xa73
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x6e
	.byte	0xe
	.4byte	0xab7
	.uleb128 0x2
	.4byte	.LASF178
	.byte	0
	.uleb128 0x2
	.4byte	.LASF179
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF180
	.byte	0x5
	.byte	0x71
	.byte	0x3
	.4byte	0xa9e
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.byte	0x73
	.byte	0x9
	.4byte	0xaf4
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0x5
	.byte	0x75
	.byte	0xc
	.4byte	0x80
	.byte	0
	.uleb128 0x1
	.4byte	.LASF182
	.byte	0x5
	.byte	0x76
	.byte	0xb
	.4byte	0x63
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF183
	.byte	0x5
	.byte	0x77
	.byte	0xb
	.4byte	0x63
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF184
	.byte	0x5
	.byte	0x78
	.byte	0x3
	.4byte	0xac3
	.uleb128 0x4
	.byte	0x18
	.byte	0x5
	.byte	0x7a
	.byte	0x9
	.4byte	0xb72
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0x5
	.byte	0x7c
	.byte	0xb
	.4byte	0x63
	.byte	0
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0x5
	.byte	0x7d
	.byte	0xb
	.4byte	0x63
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0x5
	.byte	0x7e
	.byte	0xb
	.4byte	0x63
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF188
	.byte	0x5
	.byte	0x7f
	.byte	0x1a
	.4byte	0x9bd
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF189
	.byte	0x5
	.byte	0x80
	.byte	0x27
	.4byte	0x94e
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF190
	.byte	0x5
	.byte	0x81
	.byte	0xc
	.4byte	0x80
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF191
	.byte	0x5
	.byte	0x82
	.byte	0x1b
	.4byte	0xaf4
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF192
	.byte	0x5
	.byte	0x83
	.byte	0x1b
	.4byte	0xaf4
	.byte	0x12
	.byte	0
	.uleb128 0x5
	.4byte	.LASF193
	.byte	0x5
	.byte	0x84
	.byte	0x3
	.4byte	0xb00
	.uleb128 0x5
	.4byte	.LASF194
	.byte	0x5
	.byte	0x87
	.byte	0x10
	.4byte	0xb8a
	.uleb128 0xd
	.4byte	0xb8f
	.uleb128 0x24
	.4byte	0xb9a
	.uleb128 0xf
	.4byte	0x63
	.byte	0
	.uleb128 0x5
	.4byte	.LASF195
	.byte	0x6
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0xa
	.byte	0x10
	.byte	0x4
	.4byte	.LASF196
	.uleb128 0x34
	.byte	0x4
	.uleb128 0xa
	.byte	0x1
	.byte	0x8
	.4byte	.LASF197
	.uleb128 0x5
	.4byte	.LASF198
	.byte	0x7
	.byte	0x2e
	.byte	0x10
	.4byte	0xbc2
	.uleb128 0xd
	.4byte	0xbc7
	.uleb128 0x24
	.4byte	0xbd2
	.uleb128 0xf
	.4byte	0x14d
	.byte	0
	.uleb128 0x35
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x8
	.2byte	0x1cd
	.byte	0xe
	.4byte	0xd08
	.uleb128 0x2
	.4byte	.LASF199
	.byte	0
	.uleb128 0x2
	.4byte	.LASF200
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF201
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF202
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF203
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF204
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF205
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF206
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF207
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF208
	.byte	0x9
	.uleb128 0x2
	.4byte	.LASF209
	.byte	0xa
	.uleb128 0x2
	.4byte	.LASF210
	.byte	0xb
	.uleb128 0x2
	.4byte	.LASF211
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF212
	.byte	0xd
	.uleb128 0x2
	.4byte	.LASF213
	.byte	0xe
	.uleb128 0x2
	.4byte	.LASF214
	.byte	0xf
	.uleb128 0x2
	.4byte	.LASF215
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF216
	.byte	0x11
	.uleb128 0x2
	.4byte	.LASF217
	.byte	0x12
	.uleb128 0x2
	.4byte	.LASF218
	.byte	0x13
	.uleb128 0x2
	.4byte	.LASF219
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF220
	.byte	0x15
	.uleb128 0x2
	.4byte	.LASF221
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF222
	.byte	0x17
	.uleb128 0x2
	.4byte	.LASF223
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF224
	.byte	0x19
	.uleb128 0x2
	.4byte	.LASF225
	.byte	0x1a
	.uleb128 0x2
	.4byte	.LASF226
	.byte	0x1b
	.uleb128 0x2
	.4byte	.LASF227
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF228
	.byte	0x1d
	.uleb128 0x2
	.4byte	.LASF229
	.byte	0x1e
	.uleb128 0x2
	.4byte	.LASF230
	.byte	0x1f
	.uleb128 0x2
	.4byte	.LASF231
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF232
	.byte	0x21
	.uleb128 0x2
	.4byte	.LASF233
	.byte	0x22
	.uleb128 0x2
	.4byte	.LASF234
	.byte	0x23
	.uleb128 0x2
	.4byte	.LASF235
	.byte	0x24
	.uleb128 0x2
	.4byte	.LASF236
	.byte	0x25
	.uleb128 0x2
	.4byte	.LASF237
	.byte	0x26
	.uleb128 0x2
	.4byte	.LASF238
	.byte	0x27
	.uleb128 0x2
	.4byte	.LASF239
	.byte	0x28
	.uleb128 0x2
	.4byte	.LASF240
	.byte	0x29
	.uleb128 0x2
	.4byte	.LASF241
	.byte	0x2a
	.uleb128 0x2
	.4byte	.LASF242
	.byte	0x2b
	.uleb128 0x2
	.4byte	.LASF243
	.byte	0x2c
	.uleb128 0x2
	.4byte	.LASF244
	.byte	0x2d
	.uleb128 0x2
	.4byte	.LASF245
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF246
	.byte	0x2f
	.uleb128 0x2
	.4byte	.LASF247
	.byte	0x30
	.byte	0
	.uleb128 0x36
	.4byte	.LASF248
	.byte	0x1
	.byte	0x2d
	.byte	0x2b
	.4byte	0xd1d
	.4byte	0x42101000
	.uleb128 0xd
	.4byte	0x90b
	.uleb128 0x11
	.4byte	0xd18
	.uleb128 0x13
	.4byte	.LASF249
	.byte	0x2e
	.byte	0x26
	.4byte	0xa6e
	.uleb128 0x5
	.byte	0x3
	.4byte	qdec_status
	.uleb128 0x13
	.4byte	.LASF250
	.byte	0x2f
	.byte	0x21
	.4byte	0xa13
	.uleb128 0x5
	.byte	0x3
	.4byte	qdec_mode
	.uleb128 0x13
	.4byte	.LASF251
	.byte	0x30
	.byte	0x1a
	.4byte	0xb72
	.uleb128 0x5
	.byte	0x3
	.4byte	g_qdec_cfg
	.uleb128 0x13
	.4byte	.LASF252
	.byte	0x32
	.byte	0xc
	.4byte	0xd66
	.uleb128 0x5
	.byte	0x3
	.4byte	g_first_data_flag
	.uleb128 0xa
	.byte	0x1
	.byte	0x2
	.4byte	.LASF253
	.uleb128 0x7
	.4byte	0xd66
	.uleb128 0x13
	.4byte	.LASF254
	.byte	0x33
	.byte	0x15
	.4byte	0xd6d
	.uleb128 0x5
	.byte	0x3
	.4byte	qdec_available_data
	.uleb128 0x25
	.4byte	.LASF255
	.byte	0x34
	.byte	0x18
	.4byte	0x929
	.uleb128 0x5
	.byte	0x3
	.4byte	g_qdec_mode_status
	.uleb128 0x25
	.4byte	.LASF256
	.byte	0x36
	.byte	0x8
	.4byte	0xb8a
	.uleb128 0x5
	.byte	0x3
	.4byte	qdec_callback
	.uleb128 0x17
	.4byte	.LASF257
	.2byte	0x145
	.byte	0x10
	.4byte	0x42
	.uleb128 0x5
	.byte	0x3
	.4byte	dat_Sum
	.uleb128 0x37
	.4byte	.LASF281
	.byte	0x9
	.byte	0x21
	.byte	0x8
	.4byte	0xbad
	.4byte	0xdd7
	.uleb128 0xf
	.4byte	0xbad
	.uleb128 0xf
	.4byte	0xb3
	.uleb128 0xf
	.4byte	0xb9a
	.byte	0
	.uleb128 0x26
	.4byte	.LASF258
	.byte	0x3c
	.4byte	0xde7
	.uleb128 0xf
	.4byte	0x14d
	.byte	0
	.uleb128 0x26
	.4byte	.LASF259
	.byte	0x3b
	.4byte	0xdfc
	.uleb128 0xf
	.4byte	0x14d
	.uleb128 0xf
	.4byte	0xbb6
	.byte	0
	.uleb128 0x8
	.4byte	.LASF264
	.2byte	0x2c3
	.4byte	0xa37
	.4byte	.LFB34
	.4byte	.LFE34-.LFB34
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe54
	.uleb128 0x9
	.4byte	.LASF260
	.2byte	0x2c3
	.byte	0x42
	.4byte	0xe54
	.4byte	.LLST44
	.uleb128 0x1e
	.4byte	.LASF261
	.2byte	0x2c3
	.byte	0x6f
	.4byte	0xe59
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x14
	.4byte	.LASF262
	.2byte	0x2c9
	.byte	0xb
	.4byte	0x63
	.4byte	.LLST45
	.uleb128 0x14
	.4byte	.LASF263
	.2byte	0x2d0
	.byte	0xb
	.4byte	0x63
	.4byte	.LLST46
	.byte	0
	.uleb128 0xd
	.4byte	0xab7
	.uleb128 0xd
	.4byte	0x998
	.uleb128 0x8
	.4byte	.LASF265
	.2byte	0x2b1
	.4byte	0xa37
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe98
	.uleb128 0x9
	.4byte	.LASF266
	.2byte	0x2b1
	.byte	0x3a
	.4byte	0xe98
	.4byte	.LLST42
	.uleb128 0x14
	.4byte	.LASF190
	.2byte	0x2b3
	.byte	0xc
	.4byte	0x96
	.4byte	.LLST43
	.byte	0
	.uleb128 0xd
	.4byte	0x80
	.uleb128 0x8
	.4byte	.LASF267
	.2byte	0x2a4
	.4byte	0xa37
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xec7
	.uleb128 0x9
	.4byte	.LASF266
	.2byte	0x2a4
	.byte	0x39
	.4byte	0x80
	.4byte	.LLST41
	.byte	0
	.uleb128 0x8
	.4byte	.LASF268
	.2byte	0x290
	.4byte	0xa37
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xeff
	.uleb128 0x9
	.4byte	.LASF269
	.2byte	0x290
	.byte	0x3f
	.4byte	0xa92
	.4byte	.LLST40
	.uleb128 0x1e
	.4byte	.LASF270
	.2byte	0x290
	.byte	0x61
	.4byte	0xe54
	.uleb128 0x1
	.byte	0x5b
	.byte	0
	.uleb128 0x38
	.4byte	.LASF312
	.byte	0x1
	.2byte	0x28b
	.byte	0x18
	.4byte	0x929
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x8
	.4byte	.LASF271
	.2byte	0x27b
	.4byte	0xa37
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf4e
	.uleb128 0x9
	.4byte	.LASF272
	.2byte	0x27b
	.byte	0x4f
	.4byte	0x998
	.4byte	.LLST39
	.uleb128 0x1e
	.4byte	.LASF273
	.2byte	0x27b
	.byte	0x72
	.4byte	0xf4e
	.uleb128 0x1
	.byte	0x5b
	.byte	0
	.uleb128 0xd
	.4byte	0xaf4
	.uleb128 0x8
	.4byte	.LASF274
	.2byte	0x261
	.4byte	0xa37
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xfc4
	.uleb128 0x9
	.4byte	.LASF275
	.2byte	0x261
	.byte	0x4f
	.4byte	0x9e2
	.4byte	.LLST35
	.uleb128 0x18
	.string	"ret"
	.2byte	0x263
	.4byte	0xa37
	.4byte	.LLST36
	.uleb128 0x27
	.4byte	0x1080
	.4byte	.LBB49
	.4byte	.LBE49-.LBB49
	.2byte	0x266
	.byte	0xb
	.4byte	0xfa9
	.uleb128 0xb
	.4byte	0x108f
	.4byte	.LLST37
	.byte	0
	.uleb128 0x19
	.4byte	0x1064
	.4byte	.LBB51
	.4byte	.LBE51-.LBB51
	.2byte	0x26e
	.byte	0xb
	.uleb128 0xb
	.4byte	0x1073
	.4byte	.LLST38
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF276
	.2byte	0x241
	.4byte	0xa37
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1016
	.uleb128 0x9
	.4byte	.LASF272
	.2byte	0x241
	.byte	0x52
	.4byte	0x998
	.4byte	.LLST32
	.uleb128 0x9
	.4byte	.LASF273
	.2byte	0x241
	.byte	0x74
	.4byte	0xaf4
	.4byte	.LLST33
	.uleb128 0x18
	.string	"ret"
	.2byte	0x248
	.4byte	0xa37
	.4byte	.LLST34
	.uleb128 0x15
	.4byte	.LVL86
	.4byte	0x14bd
	.byte	0
	.uleb128 0x8
	.4byte	.LASF277
	.2byte	0x22c
	.4byte	0xa37
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x105f
	.uleb128 0x9
	.4byte	.LASF278
	.2byte	0x22c
	.byte	0x36
	.4byte	0x105f
	.4byte	.LLST30
	.uleb128 0x14
	.4byte	.LASF279
	.2byte	0x22e
	.byte	0xb
	.4byte	0x63
	.4byte	.LLST31
	.uleb128 0x17
	.4byte	.LASF280
	.2byte	0x22f
	.byte	0x14
	.4byte	0x6f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0xd
	.4byte	0xd66
	.uleb128 0x1a
	.4byte	.LASF282
	.2byte	0x215
	.4byte	0xa37
	.4byte	0x1080
	.uleb128 0x12
	.4byte	.LASF269
	.2byte	0x215
	.byte	0x3c
	.4byte	0xa92
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF283
	.2byte	0x1fe
	.4byte	0xa37
	.4byte	0x109c
	.uleb128 0x12
	.4byte	.LASF269
	.2byte	0x1fe
	.byte	0x3b
	.4byte	0xa92
	.byte	0
	.uleb128 0x8
	.4byte	.LASF284
	.2byte	0x1ed
	.4byte	0xa37
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10ce
	.uleb128 0x18
	.string	"ret"
	.2byte	0x1f4
	.4byte	0xa37
	.4byte	.LLST27
	.uleb128 0x15
	.4byte	.LVL63
	.4byte	0x115d
	.byte	0
	.uleb128 0x8
	.4byte	.LASF285
	.2byte	0x1dd
	.4byte	0xa37
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1100
	.uleb128 0x18
	.string	"ret"
	.2byte	0x1e3
	.4byte	0xa37
	.4byte	.LLST26
	.uleb128 0x15
	.4byte	.LVL59
	.4byte	0x1100
	.byte	0
	.uleb128 0x8
	.4byte	.LASF286
	.2byte	0x1c1
	.4byte	0xa37
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x115d
	.uleb128 0x28
	.string	"ret"
	.2byte	0x1c3
	.4byte	0xa37
	.uleb128 0x27
	.4byte	0x11d7
	.4byte	.LBB45
	.4byte	.LBE45-.LBB45
	.2byte	0x1c4
	.byte	0x9
	.4byte	0x1142
	.uleb128 0xb
	.4byte	0x11e6
	.4byte	.LLST24
	.byte	0
	.uleb128 0x19
	.4byte	0x11ad
	.4byte	.LBB47
	.4byte	.LBE47-.LBB47
	.2byte	0x1ca
	.byte	0x9
	.uleb128 0xb
	.4byte	0x11bc
	.4byte	.LLST25
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF287
	.2byte	0x1a5
	.4byte	0xa37
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x11ad
	.uleb128 0x28
	.string	"ret"
	.2byte	0x1a7
	.4byte	0xa37
	.uleb128 0x39
	.4byte	0x11c9
	.4byte	.LBB41
	.4byte	.LBE41-.LBB41
	.byte	0x1
	.2byte	0x1a8
	.byte	0x9
	.uleb128 0x19
	.4byte	0x11ad
	.4byte	.LBB43
	.4byte	.LBE43-.LBB43
	.2byte	0x1ae
	.byte	0x9
	.uleb128 0xb
	.4byte	0x11bc
	.4byte	.LLST23
	.byte	0
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF288
	.2byte	0x199
	.4byte	0xa37
	.4byte	0x11c9
	.uleb128 0x12
	.4byte	.LASF261
	.2byte	0x199
	.byte	0x46
	.4byte	0x998
	.byte	0
	.uleb128 0x3a
	.4byte	.LASF313
	.byte	0x1
	.2byte	0x191
	.byte	0x13
	.4byte	0xa37
	.byte	0x1
	.uleb128 0x1a
	.4byte	.LASF289
	.2byte	0x183
	.4byte	0xa37
	.4byte	0x11f3
	.uleb128 0x12
	.4byte	.LASF261
	.2byte	0x183
	.byte	0x47
	.4byte	0x998
	.byte	0
	.uleb128 0x8
	.4byte	.LASF290
	.2byte	0x152
	.4byte	0xa37
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1282
	.uleb128 0x9
	.4byte	.LASF291
	.2byte	0x152
	.byte	0x2e
	.4byte	0x1282
	.4byte	.LLST15
	.uleb128 0x14
	.4byte	.LASF292
	.2byte	0x154
	.byte	0xb
	.4byte	0x42
	.4byte	.LLST16
	.uleb128 0x29
	.4byte	.LLRL17
	.4byte	0x1245
	.uleb128 0x17
	.4byte	.LASF293
	.2byte	0x15c
	.byte	0x17
	.4byte	0x8c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x29
	.4byte	.LLRL18
	.4byte	0x125e
	.uleb128 0x17
	.4byte	.LASF293
	.2byte	0x16f
	.byte	0x17
	.4byte	0x8c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -2
	.byte	0
	.uleb128 0x19
	.4byte	0x1287
	.4byte	.LBB37
	.4byte	.LBE37-.LBB37
	.2byte	0x17f
	.byte	0x3
	.uleb128 0xb
	.4byte	0x12a1
	.4byte	.LLST19
	.uleb128 0xb
	.4byte	0x1295
	.4byte	.LLST20
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	0x42
	.uleb128 0x3b
	.4byte	.LASF314
	.byte	0x1
	.2byte	0x146
	.byte	0xd
	.byte	0x1
	.4byte	0x12ae
	.uleb128 0x12
	.4byte	.LASF294
	.2byte	0x146
	.byte	0x27
	.4byte	0x42
	.uleb128 0x12
	.4byte	.LASF295
	.2byte	0x146
	.byte	0x3a
	.4byte	0x1282
	.byte	0
	.uleb128 0x2a
	.4byte	.LASF301
	.2byte	0x137
	.4byte	0xa37
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x8
	.4byte	.LASF296
	.2byte	0x126
	.4byte	0xa37
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x12fd
	.uleb128 0x9
	.4byte	.LASF297
	.2byte	0x126
	.byte	0x43
	.4byte	0x973
	.4byte	.LLST13
	.uleb128 0x9
	.4byte	.LASF298
	.2byte	0x126
	.byte	0x53
	.4byte	0x80
	.4byte	.LLST14
	.byte	0
	.uleb128 0x8
	.4byte	.LASF299
	.2byte	0x11b
	.4byte	0xa37
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1327
	.uleb128 0x9
	.4byte	.LASF300
	.2byte	0x11b
	.byte	0x42
	.4byte	0xb7e
	.4byte	.LLST12
	.byte	0
	.uleb128 0x2a
	.4byte	.LASF302
	.2byte	0x10d
	.4byte	0xa37
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x3c
	.4byte	.LASF303
	.byte	0x1
	.byte	0xe9
	.byte	0x13
	.4byte	0xa37
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x2b
	.4byte	.LASF304
	.byte	0xdb
	.4byte	0xa37
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1388
	.uleb128 0x2c
	.4byte	.LVL28
	.4byte	0xdb7
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	g_qdec_cfg
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x48
	.byte	0
	.byte	0
	.uleb128 0x2b
	.4byte	.LASF305
	.byte	0xb0
	.4byte	0xa37
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x144e
	.uleb128 0x3d
	.4byte	.LASF306
	.byte	0x1
	.byte	0xb0
	.byte	0x34
	.4byte	0x144e
	.4byte	.LLST4
	.uleb128 0x2d
	.4byte	0x1453
	.4byte	.LBB22
	.4byte	.LLRL5
	.byte	0xb8
	.byte	0x7
	.4byte	0x1422
	.uleb128 0xb
	.4byte	0x1462
	.4byte	.LLST6
	.uleb128 0x2e
	.4byte	.LLRL5
	.uleb128 0x16
	.4byte	0x146e
	.4byte	.LLST7
	.uleb128 0x16
	.4byte	0x1479
	.4byte	.LLST8
	.uleb128 0x1f
	.4byte	0x1485
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1f
	.4byte	0x1490
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x16
	.4byte	0x149b
	.4byte	.LLST9
	.uleb128 0x16
	.4byte	0x14a6
	.4byte	.LLST10
	.uleb128 0x16
	.4byte	0x14b1
	.4byte	.LLST11
	.uleb128 0x15
	.4byte	.LVL15
	.4byte	0x14bd
	.uleb128 0x15
	.4byte	.LVL17
	.4byte	0x14bd
	.byte	0
	.byte	0
	.uleb128 0x3e
	.4byte	.LVL26
	.4byte	0xde7
	.4byte	0x143e
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x3b
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	hw_qdec_Isr_zephyr
	.byte	0
	.uleb128 0x2c
	.4byte	.LVL27
	.4byte	0xdd7
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x3b
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	0xb72
	.uleb128 0x2f
	.4byte	.LASF308
	.byte	0x7c
	.byte	0x1a
	.4byte	0xa37
	.4byte	0x14bd
	.uleb128 0x3f
	.4byte	.LASF306
	.byte	0x1
	.byte	0x7c
	.byte	0x4c
	.4byte	0x144e
	.uleb128 0x10
	.4byte	.LASF190
	.byte	0x7f
	.byte	0xc
	.4byte	0x80
	.uleb128 0x40
	.string	"ret"
	.byte	0x1
	.byte	0x86
	.byte	0x15
	.4byte	0xa37
	.uleb128 0x10
	.4byte	.LASF191
	.byte	0x87
	.byte	0x1b
	.4byte	0xaf4
	.uleb128 0x10
	.4byte	.LASF192
	.byte	0x8e
	.byte	0x1b
	.4byte	0xaf4
	.uleb128 0x10
	.4byte	.LASF185
	.byte	0x96
	.byte	0xb
	.4byte	0x63
	.uleb128 0x10
	.4byte	.LASF186
	.byte	0x97
	.byte	0xb
	.4byte	0x63
	.uleb128 0x10
	.4byte	.LASF187
	.byte	0x98
	.byte	0xb
	.4byte	0x63
	.byte	0
	.uleb128 0x41
	.4byte	.LASF315
	.byte	0x1
	.byte	0x6f
	.byte	0x1a
	.4byte	0xa37
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1514
	.uleb128 0x42
	.4byte	.LASF307
	.byte	0x1
	.byte	0x6f
	.byte	0x4f
	.4byte	0xaf4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x20
	.4byte	.LASF181
	.byte	0x71
	.byte	0xc
	.4byte	0x80
	.4byte	.LLST1
	.uleb128 0x20
	.4byte	.LASF182
	.byte	0x72
	.byte	0xb
	.4byte	0x63
	.4byte	.LLST2
	.uleb128 0x20
	.4byte	.LASF183
	.byte	0x73
	.byte	0xb
	.4byte	0x63
	.4byte	.LLST3
	.byte	0
	.uleb128 0x43
	.4byte	.LASF316
	.byte	0x1
	.byte	0x49
	.byte	0xd
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1581
	.uleb128 0x10
	.4byte	.LASF269
	.byte	0x4b
	.byte	0x17
	.4byte	0xa92
	.uleb128 0x2d
	.4byte	0x1581
	.4byte	.LBB16
	.4byte	.LLRL0
	.byte	0x4b
	.byte	0x22
	.4byte	0x1557
	.uleb128 0x2e
	.4byte	.LLRL0
	.uleb128 0x1f
	.4byte	0x1590
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.uleb128 0x30
	.4byte	.LVL1
	.4byte	0x1566
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.uleb128 0x30
	.4byte	.LVL2
	.4byte	0x1575
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.uleb128 0x44
	.4byte	.LVL3
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF309
	.byte	0x38
	.byte	0x1c
	.4byte	0xa92
	.4byte	0x159c
	.uleb128 0x10
	.4byte	.LASF270
	.byte	0x3a
	.byte	0x15
	.4byte	0xa2
	.byte	0
	.uleb128 0x21
	.4byte	0x11d7
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x15b9
	.uleb128 0xb
	.4byte	0x11e6
	.4byte	.LLST21
	.byte	0
	.uleb128 0x45
	.4byte	0x11c9
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x21
	.4byte	0x11ad
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x15e5
	.uleb128 0xb
	.4byte	0x11bc
	.4byte	.LLST22
	.byte	0
	.uleb128 0x21
	.4byte	0x1080
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1602
	.uleb128 0xb
	.4byte	0x108f
	.4byte	.LLST28
	.byte	0
	.uleb128 0x46
	.4byte	0x1064
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xb
	.4byte	0x1073
	.4byte	.LLST29
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
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
	.uleb128 0x2
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3
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
	.uleb128 0x4
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
	.uleb128 0x7
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.sleb128 19
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
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x21
	.sleb128 21
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.sleb128 19
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
	.uleb128 0x1b
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
	.uleb128 0x1c
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x22
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
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
	.uleb128 0x23
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
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
	.sleb128 7
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
	.uleb128 0x28
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
	.uleb128 0x1c
	.uleb128 0x21
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.sleb128 19
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
	.uleb128 0x2b
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
	.sleb128 19
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
	.uleb128 0x2c
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2f
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
	.uleb128 0xb
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
	.uleb128 0x30
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
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
	.uleb128 0x32
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
	.uleb128 0x33
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
	.uleb128 0x34
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x1c
	.uleb128 0x6
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
	.uleb128 0x38
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
	.uleb128 0x39
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
	.uleb128 0x3a
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
	.uleb128 0x3b
	.uleb128 0x2e
	.byte	0x1
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
	.byte	0
	.byte	0
	.uleb128 0x3d
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x3e
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
	.uleb128 0x3f
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
	.uleb128 0x40
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
	.byte	0
	.byte	0
	.uleb128 0x41
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
	.uleb128 0x42
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
	.uleb128 0x43
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
	.uleb128 0x44
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x45
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
	.uleb128 0x46
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
	.byte	0
	.section	.debug_loclists,"",@progbits
	.4byte	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.Ldebug_loc0:
.LLST44:
	.byte	0x6
	.4byte	.LVL120
	.byte	0x4
	.uleb128 .LVL120-.LVL120
	.uleb128 .LVL121-.LVL120
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL121-.LVL120
	.uleb128 .LVL124-.LVL120
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL124-.LVL120
	.uleb128 .LVL128-.LVL120
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
	.uleb128 .LVL128-.LVL120
	.uleb128 .LFE34-.LVL120
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST45:
	.byte	0x8
	.4byte	.LVL122
	.uleb128 .LVL123-.LVL122
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST46:
	.byte	0x6
	.4byte	.LVL124
	.byte	0x4
	.uleb128 .LVL124-.LVL124
	.uleb128 .LVL125-.LVL124
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL126-.LVL124
	.uleb128 .LVL127-.LVL124
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST42:
	.byte	0x6
	.4byte	.LVL115
	.byte	0x4
	.uleb128 .LVL115-.LVL115
	.uleb128 .LVL117-.LVL115
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL117-.LVL115
	.uleb128 .LVL118-.LVL115
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL118-.LVL115
	.uleb128 .LVL119-.LVL115
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL119-.LVL115
	.uleb128 .LFE33-.LVL115
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST43:
	.byte	0x8
	.4byte	.LVL116
	.uleb128 .LVL118-.LVL116
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST41:
	.byte	0x6
	.4byte	.LVL111
	.byte	0x4
	.uleb128 .LVL111-.LVL111
	.uleb128 .LVL112-.LVL111
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL112-.LVL111
	.uleb128 .LVL113-.LVL111
	.uleb128 0x5
	.byte	0x3
	.4byte	g_qdec_cfg+12
	.byte	0x4
	.uleb128 .LVL113-.LVL111
	.uleb128 .LVL114-.LVL111
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL114-.LVL111
	.uleb128 .LFE32-.LVL111
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
.LLST40:
	.byte	0x6
	.4byte	.LVL105
	.byte	0x4
	.uleb128 .LVL105-.LVL105
	.uleb128 .LVL106-.LVL105
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL106-.LVL105
	.uleb128 .LVL107-.LVL105
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
	.uleb128 .LVL107-.LVL105
	.uleb128 .LVL108-.LVL105
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL108-.LVL105
	.uleb128 .LVL109-.LVL105
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL109-.LVL105
	.uleb128 .LVL110-.LVL105
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
	.uleb128 .LVL110-.LVL105
	.uleb128 .LFE31-.LVL105
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST39:
	.byte	0x6
	.4byte	.LVL101
	.byte	0x4
	.uleb128 .LVL101-.LVL101
	.uleb128 .LVL102-.LVL101
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL102-.LVL101
	.uleb128 .LVL103-.LVL101
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
	.uleb128 .LVL103-.LVL101
	.uleb128 .LVL104-.LVL101
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL104-.LVL101
	.uleb128 .LFE29-.LVL101
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
.LLST35:
	.byte	0x6
	.4byte	.LVL92
	.byte	0x4
	.uleb128 .LVL92-.LVL92
	.uleb128 .LVL94-.LVL92
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL94-.LVL92
	.uleb128 .LVL95-.LVL92
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
	.uleb128 .LVL95-.LVL92
	.uleb128 .LVL96-.LVL92
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL96-.LVL92
	.uleb128 .LVL98-.LVL92
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL98-.LVL92
	.uleb128 .LVL100-.LVL92
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
	.uleb128 .LVL100-.LVL92
	.uleb128 .LFE28-.LVL92
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST36:
	.byte	0x6
	.4byte	.LVL94
	.byte	0x4
	.uleb128 .LVL94-.LVL94
	.uleb128 .LVL95-.LVL94
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL99-.LVL94
	.uleb128 .LVL100-.LVL94
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST37:
	.byte	0x8
	.4byte	.LVL93
	.uleb128 .LVL94-.LVL93
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0
.LLST38:
	.byte	0x8
	.4byte	.LVL97
	.uleb128 .LVL99-.LVL97
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0
.LLST32:
	.byte	0x6
	.4byte	.LVL83
	.byte	0x4
	.uleb128 .LVL83-.LVL83
	.uleb128 .LVL85-.LVL83
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL85-.LVL83
	.uleb128 .LVL88-.LVL83
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL88-.LVL83
	.uleb128 .LVL89-.LVL83
	.uleb128 0x2
	.byte	0x72
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL89-.LVL83
	.uleb128 .LVL90-.LVL83
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL90-.LVL83
	.uleb128 .LFE27-.LVL83
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST33:
	.byte	0x6
	.4byte	.LVL84
	.byte	0x4
	.uleb128 .LVL84-.LVL84
	.uleb128 .LVL86-1-.LVL84
	.uleb128 0x12
	.byte	0x91
	.sleb128 -20
	.byte	0x93
	.uleb128 0x2
	.byte	0x7b
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x9f
	.byte	0x93
	.uleb128 0x1
	.byte	0x7b
	.sleb128 0
	.byte	0x48
	.byte	0x25
	.byte	0x9f
	.byte	0x93
	.uleb128 0x1
	.byte	0x4
	.uleb128 .LVL86-1-.LVL84
	.uleb128 .LVL88-.LVL84
	.uleb128 0x6
	.byte	0x91
	.sleb128 -20
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL88-.LVL84
	.uleb128 .LVL89-.LVL84
	.uleb128 0x6
	.byte	0x72
	.sleb128 -20
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0x4
	.uleb128 .LVL89-.LVL84
	.uleb128 .LFE27-.LVL84
	.uleb128 0x6
	.byte	0x91
	.sleb128 -20
	.byte	0x93
	.uleb128 0x2
	.byte	0x93
	.uleb128 0x2
	.byte	0
.LLST34:
	.byte	0x6
	.4byte	.LVL86
	.byte	0x4
	.uleb128 .LVL86-.LVL86
	.uleb128 .LVL87-.LVL86
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL89-.LVL86
	.uleb128 .LVL91-.LVL86
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST30:
	.byte	0x6
	.4byte	.LVL77
	.byte	0x4
	.uleb128 .LVL77-.LVL77
	.uleb128 .LVL79-.LVL77
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL79-.LVL77
	.uleb128 .LVL80-.LVL77
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
	.uleb128 .LVL80-.LVL77
	.uleb128 .LVL82-.LVL77
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL82-.LVL77
	.uleb128 .LFE26-.LVL77
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
	.4byte	.LVL78
	.byte	0x4
	.uleb128 .LVL78-.LVL78
	.uleb128 .LVL79-.LVL78
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL80-.LVL78
	.uleb128 .LVL81-.LVL78
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST27:
	.byte	0x6
	.4byte	.LVL63
	.byte	0x4
	.uleb128 .LVL63-.LVL63
	.uleb128 .LVL64-.LVL63
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL65-.LVL63
	.uleb128 .LVL66-.LVL63
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST26:
	.byte	0x6
	.4byte	.LVL59
	.byte	0x4
	.uleb128 .LVL59-.LVL59
	.uleb128 .LVL60-.LVL59
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL61-.LVL59
	.uleb128 .LVL62-.LVL59
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST24:
	.byte	0x8
	.4byte	.LVL56
	.uleb128 .LVL57-.LVL56
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST25:
	.byte	0x8
	.4byte	.LVL57
	.uleb128 .LVL58-.LVL57
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0
.LLST23:
	.byte	0x8
	.4byte	.LVL54
	.uleb128 .LVL55-.LVL54
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL38
	.byte	0x4
	.uleb128 .LVL38-.LVL38
	.uleb128 .LVL41-.LVL38
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL41-.LVL38
	.uleb128 .LVL42-.LVL38
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
	.uleb128 .LVL42-.LVL38
	.uleb128 .LVL45-.LVL38
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL45-.LVL38
	.uleb128 .LFE16-.LVL38
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
	.4byte	.LVL39
	.byte	0x4
	.uleb128 .LVL39-.LVL39
	.uleb128 .LVL40-.LVL39
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL43-.LVL39
	.uleb128 .LVL44-.LVL39
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL39
	.byte	0x4
	.uleb128 .LVL39-.LVL39
	.uleb128 .LVL41-.LVL39
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL41-.LVL39
	.uleb128 .LVL42-.LVL39
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
	.byte	0x8
	.4byte	.LVL39
	.uleb128 .LVL40-.LVL39
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL35-.LVL33
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL35-.LVL33
	.uleb128 .LVL36-.LVL33
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
	.uleb128 .LVL36-.LVL33
	.uleb128 .LVL37-.LVL33
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL37-.LVL33
	.uleb128 .LFE13-.LVL33
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
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LVL36-.LVL33
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
	.uleb128 .LVL36-.LVL33
	.uleb128 .LFE13-.LVL33
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL29
	.byte	0x4
	.uleb128 .LVL29-.LVL29
	.uleb128 .LVL30-.LVL29
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL30-.LVL29
	.uleb128 .LVL31-.LVL29
	.uleb128 0x5
	.byte	0x3
	.4byte	qdec_callback
	.byte	0x4
	.uleb128 .LVL31-.LVL29
	.uleb128 .LVL32-.LVL29
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL32-.LVL29
	.uleb128 .LFE12-.LVL29
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
	.4byte	.LVL10
	.byte	0x4
	.uleb128 .LVL10-.LVL10
	.uleb128 .LVL12-.LVL10
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL12-.LVL10
	.uleb128 .LVL13-.LVL10
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
	.uleb128 .LVL13-.LVL10
	.uleb128 .LVL14-.LVL10
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL14-.LVL10
	.uleb128 .LFE8-.LVL10
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL10
	.byte	0x4
	.uleb128 .LVL10-.LVL10
	.uleb128 .LVL12-.LVL10
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL13-.LVL10
	.uleb128 .LVL14-.LVL10
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL14-.LVL10
	.uleb128 .LVL25-.LVL10
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL12-.LVL11
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL13-.LVL11
	.uleb128 .LVL25-.LVL11
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST8:
	.byte	0x6
	.4byte	.LVL15
	.byte	0x4
	.uleb128 .LVL15-.LVL15
	.uleb128 .LVL16-.LVL15
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL17-.LVL15
	.uleb128 .LVL21-.LVL15
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL21-.LVL15
	.uleb128 .LVL25-.LVL15
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL18
	.byte	0x4
	.uleb128 .LVL18-.LVL18
	.uleb128 .LVL22-.LVL18
	.uleb128 0x1
	.byte	0x55
	.byte	0x4
	.uleb128 .LVL22-.LVL18
	.uleb128 .LVL25-.LVL18
	.uleb128 0x5
	.byte	0x3
	.4byte	g_qdec_cfg
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL19
	.byte	0x4
	.uleb128 .LVL19-.LVL19
	.uleb128 .LVL23-.LVL19
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL23-.LVL19
	.uleb128 .LVL25-.LVL19
	.uleb128 0x5
	.byte	0x3
	.4byte	g_qdec_cfg+1
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL20
	.byte	0x4
	.uleb128 .LVL20-.LVL20
	.uleb128 .LVL24-.LVL20
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL24-.LVL20
	.uleb128 .LVL25-.LVL20
	.uleb128 0x5
	.byte	0x3
	.4byte	g_qdec_cfg+2
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL7-.LVL4
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL8-.LVL4
	.uleb128 .LFE6-.LVL4
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x5
	.byte	0x7a
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.LVL4
	.uleb128 .LVL6-.LVL4
	.uleb128 0x5
	.byte	0x7f
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL8-.LVL4
	.uleb128 .LVL9-.LVL4
	.uleb128 0x5
	.byte	0x7a
	.sleb128 0
	.byte	0x40
	.byte	0x25
	.byte	0x9f
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x5
	.byte	0x7a
	.sleb128 0
	.byte	0x48
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.LVL4
	.uleb128 .LVL6-.LVL4
	.uleb128 0x5
	.byte	0x7f
	.sleb128 0
	.byte	0x48
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL8-.LVL4
	.uleb128 .LVL9-.LVL4
	.uleb128 0x5
	.byte	0x7a
	.sleb128 0
	.byte	0x48
	.byte	0x25
	.byte	0x9f
	.byte	0
.LLST21:
	.byte	0x6
	.4byte	.LVL46
	.byte	0x4
	.uleb128 .LVL46-.LVL46
	.uleb128 .LVL47-.LVL46
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL47-.LVL46
	.uleb128 .LVL48-.LVL46
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
	.uleb128 .LVL48-.LVL46
	.uleb128 .LVL49-.LVL46
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL49-.LVL46
	.uleb128 .LFE17-.LVL46
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
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL51-.LVL50
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL51-.LVL50
	.uleb128 .LVL52-.LVL50
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
	.uleb128 .LVL52-.LVL50
	.uleb128 .LVL53-.LVL50
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL53-.LVL50
	.uleb128 .LFE19-.LVL50
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
	.4byte	.LVL67
	.byte	0x4
	.uleb128 .LVL67-.LVL67
	.uleb128 .LVL68-.LVL67
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL68-.LVL67
	.uleb128 .LVL69-.LVL67
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
	.uleb128 .LVL69-.LVL67
	.uleb128 .LVL70-.LVL67
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL70-.LVL67
	.uleb128 .LFE24-.LVL67
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST29:
	.byte	0x6
	.4byte	.LVL71
	.byte	0x4
	.uleb128 .LVL71-.LVL71
	.uleb128 .LVL72-.LVL71
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL72-.LVL71
	.uleb128 .LVL73-.LVL71
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
	.uleb128 .LVL73-.LVL71
	.uleb128 .LVL74-.LVL71
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL74-.LVL71
	.uleb128 .LVL75-.LVL71
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL75-.LVL71
	.uleb128 .LVL76-.LVL71
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
	.uleb128 .LVL76-.LVL71
	.uleb128 .LFE25-.LVL71
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0xf4
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
.LLRL0:
	.byte	0x5
	.4byte	.LBB16
	.byte	0x4
	.uleb128 .LBB16-.LBB16
	.uleb128 .LBE16-.LBB16
	.byte	0x4
	.uleb128 .LBB19-.LBB16
	.uleb128 .LBE19-.LBB16
	.byte	0
.LLRL5:
	.byte	0x5
	.4byte	.LBB22
	.byte	0x4
	.uleb128 .LBB22-.LBB22
	.uleb128 .LBE22-.LBB22
	.byte	0x4
	.uleb128 .LBB27-.LBB22
	.uleb128 .LBE27-.LBB22
	.byte	0x4
	.uleb128 .LBB28-.LBB22
	.uleb128 .LBE28-.LBB22
	.byte	0x4
	.uleb128 .LBB29-.LBB22
	.uleb128 .LBE29-.LBB22
	.byte	0
.LLRL17:
	.byte	0x5
	.4byte	.LBB34
	.byte	0x4
	.uleb128 .LBB34-.LBB34
	.uleb128 .LBE34-.LBB34
	.byte	0x4
	.uleb128 .LBB35-.LBB34
	.uleb128 .LBE35-.LBB34
	.byte	0x4
	.uleb128 .LBB39-.LBB34
	.uleb128 .LBE39-.LBB34
	.byte	0
.LLRL18:
	.byte	0x5
	.4byte	.LBB36
	.byte	0x4
	.uleb128 .LBB36-.LBB36
	.uleb128 .LBE36-.LBB36
	.byte	0x4
	.uleb128 .LBB40-.LBB36
	.uleb128 .LBE40-.LBB36
	.byte	0
.LLRL47:
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF142:
	.string	"QDEC_DEBUG_SEL"
.LASF87:
	.string	"QDEC_WKUP_LCR"
.LASF38:
	.string	"RESERVED"
.LASF315:
	.string	"qdec_group_config_para_check"
.LASF257:
	.string	"dat_Sum"
.LASF262:
	.string	"hw_sel_en_reg"
.LASF192:
	.string	"group_b_cfg"
.LASF98:
	.string	"QDEC_SW_RELOAD_CLR_CELLS"
.LASF97:
	.string	"SW_RELOAD_STATUS"
.LASF25:
	.string	"MCU_DMA_IRQn"
.LASF254:
	.string	"qdec_available_data"
.LASF255:
	.string	"g_qdec_mode_status"
.LASF111:
	.string	"QDEC_WKUP_STATUS"
.LASF65:
	.string	"QDEC_SEL_GROUP"
.LASF153:
	.string	"hal_qdec_z_div_setting_t"
.LASF156:
	.string	"hal_qdec_sel_group_setting_t"
.LASF248:
	.string	"qdec_register"
.LASF82:
	.string	"QDEC_IRQ_LCR_CELLS"
.LASF114:
	.string	"QDEC_IRQ_EVENT_STATUS_CELLS"
.LASF81:
	.string	"IRQ_CLR_DATA_RDY"
.LASF78:
	.string	"QDEC_LATCH_N_CLR"
.LASF118:
	.string	"QDEC_WKUP_EVENT_STATUS_CELLS"
.LASF79:
	.string	"IRQ_CLR_Z_THR_NOTIFY"
.LASF258:
	.string	"hal_nvic_enable_irq"
.LASF161:
	.string	"HAL_QDEC_READ_DATA_BY_NEXT_CYCLE"
.LASF307:
	.string	"qdec_group_cfg"
.LASF125:
	.string	"QDEC_SEL_GROUP_UNION"
.LASF169:
	.string	"hal_qdec_status_t"
.LASF272:
	.string	"group_id"
.LASF310:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF157:
	.string	"HAL_QDEC_LED_NO_EFFECT"
.LASF176:
	.string	"QDEC_IRQ_Z_SUM"
.LASF92:
	.string	"SMP_CNT"
.LASF20:
	.string	"SPI_MST1_IRQn"
.LASF259:
	.string	"hal_nvic_register_isr_handler"
.LASF6:
	.string	"short int"
.LASF180:
	.string	"hal_qdec_irq_status_t"
.LASF147:
	.string	"hal_qdec_mode_status_t"
.LASF32:
	.string	"BT_IRQn"
.LASF115:
	.string	"QDEC_IRQ_EVENT_STATUS"
.LASF264:
	.string	"hal_qdec_get_hw_sel_cfg"
.LASF33:
	.string	"IRQ_NUMBER_MAX"
.LASF90:
	.string	"QDEC_Z_INFO_CELLS"
.LASF41:
	.string	"Z_SUM_THR"
.LASF129:
	.string	"QDEC_LATCH_N_CLR_UNION"
.LASF219:
	.string	"HAL_GPIO_20"
.LASF283:
	.string	"hal_qdec_enable_irq"
.LASF64:
	.string	"QDEC_SEL_GROUP_CELLS"
.LASF89:
	.string	"Z_CNT"
.LASF223:
	.string	"HAL_GPIO_24"
.LASF94:
	.string	"QDEC_SAMPLE_INFO_CELLS"
.LASF58:
	.string	"SW_RSTB"
.LASF288:
	.string	"hal_qdec_sw_sel_group"
.LASF13:
	.string	"uint32_t"
.LASF251:
	.string	"g_qdec_cfg"
.LASF209:
	.string	"HAL_GPIO_10"
.LASF210:
	.string	"HAL_GPIO_11"
.LASF211:
	.string	"HAL_GPIO_12"
.LASF212:
	.string	"HAL_GPIO_13"
.LASF213:
	.string	"HAL_GPIO_14"
.LASF214:
	.string	"HAL_GPIO_15"
.LASF215:
	.string	"HAL_GPIO_16"
.LASF216:
	.string	"HAL_GPIO_17"
.LASF217:
	.string	"HAL_GPIO_18"
.LASF218:
	.string	"HAL_GPIO_19"
.LASF177:
	.string	"hal_qdec_irq_type_t"
.LASF23:
	.string	"UART_DMA_IRQn"
.LASF158:
	.string	"HAL_QDEC_LED_FORCE_OFF"
.LASF299:
	.string	"hal_qdec_register_callback"
.LASF132:
	.string	"QDEC_Z_INFO_UNION"
.LASF9:
	.string	"int16_t"
.LASF193:
	.string	"hal_qdec_config_t"
.LASF43:
	.string	"Z_DIV"
.LASF2:
	.string	"long long unsigned int"
.LASF77:
	.string	"QDEC_LATCH_N_CLR_CELLS"
.LASF165:
	.string	"hal_qdec_mode_t"
.LASF49:
	.string	"QDEC_SAMPLE_CON_A_CELLS"
.LASF124:
	.string	"QDEC_CON_UNION"
.LASF187:
	.string	"led_pin"
.LASF313:
	.string	"hal_qdec_disable_hw_sel"
.LASF220:
	.string	"HAL_GPIO_21"
.LASF221:
	.string	"HAL_GPIO_22"
.LASF222:
	.string	"HAL_GPIO_23"
.LASF63:
	.string	"HW_SEL_GROUP"
.LASF224:
	.string	"HAL_GPIO_25"
.LASF225:
	.string	"HAL_GPIO_26"
.LASF226:
	.string	"HAL_GPIO_27"
.LASF227:
	.string	"HAL_GPIO_28"
.LASF228:
	.string	"HAL_GPIO_29"
.LASF273:
	.string	"group_config"
.LASF293:
	.string	"fifo_data"
.LASF18:
	.string	"KEYSCAN_IRQn"
.LASF231:
	.string	"HAL_GPIO_32"
.LASF34:
	.string	"IRQn_Type"
.LASF236:
	.string	"HAL_GPIO_37"
.LASF143:
	.string	"QDEC_DEBUG_ADDR"
.LASF175:
	.string	"QDEC_IRQ_Z_CNT"
.LASF195:
	.string	"size_t"
.LASF7:
	.string	"long int"
.LASF186:
	.string	"pinb_pin"
.LASF112:
	.string	"IRQ_EVENT_STATUS_Z_SUM"
.LASF263:
	.string	"hw_sel_goup_reg"
.LASF229:
	.string	"HAL_GPIO_30"
.LASF230:
	.string	"HAL_GPIO_31"
.LASF253:
	.string	"_Bool"
.LASF232:
	.string	"HAL_GPIO_33"
.LASF233:
	.string	"HAL_GPIO_34"
.LASF234:
	.string	"HAL_GPIO_35"
.LASF235:
	.string	"HAL_GPIO_36"
.LASF247:
	.string	"HAL_GPIO_MAX"
.LASF237:
	.string	"HAL_GPIO_38"
.LASF238:
	.string	"HAL_GPIO_39"
.LASF178:
	.string	"IRQ_DISABLE"
.LASF140:
	.string	"QDEC_WKUP_EVENT_STATUS_UNION"
.LASF191:
	.string	"group_a_cfg"
.LASF312:
	.string	"hal_qdec_get_mode_status"
.LASF95:
	.string	"QDEC_SAMPLE_INFO"
.LASF151:
	.string	"HAL_QDEC_DIV_OF_Z_COUNT_1_2"
.LASF152:
	.string	"HAL_QDEC_DIV_OF_Z_COUNT_1_4"
.LASF76:
	.string	"LATCH_STATUS"
.LASF75:
	.string	"LATCH_N_CLR"
.LASF84:
	.string	"WKUP_LCR_Z_THR_NOTIFY"
.LASF292:
	.string	"temp_data"
.LASF168:
	.string	"HAL_QDEC_STATUS_OK"
.LASF160:
	.string	"HAL_QDEC_READ_DATA_BY_IRQ"
.LASF61:
	.string	"SEL_GROUP"
.LASF240:
	.string	"HAL_GPIO_41"
.LASF241:
	.string	"HAL_GPIO_42"
.LASF242:
	.string	"HAL_GPIO_43"
.LASF243:
	.string	"HAL_GPIO_44"
.LASF57:
	.string	"QDEC_ENABLE"
.LASF245:
	.string	"HAL_GPIO_46"
.LASF246:
	.string	"HAL_GPIO_47"
.LASF197:
	.string	"char"
.LASF40:
	.string	"QDEC_LEED_CON"
.LASF304:
	.string	"hal_qdec_deinit"
.LASF71:
	.string	"WKUP_ENABLE_Z_SUM"
.LASF91:
	.string	"QDEC_Z_INFO"
.LASF239:
	.string	"HAL_GPIO_40"
.LASF170:
	.string	"QDEC_STATUS_UNINITIALIZED"
.LASF15:
	.string	"SW_IRQn"
.LASF244:
	.string	"HAL_GPIO_45"
.LASF301:
	.string	"hal_qdec_set_latch_clear"
.LASF3:
	.string	"unsigned int"
.LASF119:
	.string	"QDEC_WKUP_EVENT_STATUS"
.LASF200:
	.string	"HAL_GPIO_1"
.LASF201:
	.string	"HAL_GPIO_2"
.LASF202:
	.string	"HAL_GPIO_3"
.LASF260:
	.string	"hw_sel_status"
.LASF204:
	.string	"HAL_GPIO_5"
.LASF205:
	.string	"HAL_GPIO_6"
.LASF206:
	.string	"HAL_GPIO_7"
.LASF10:
	.string	"uint8_t"
.LASF208:
	.string	"HAL_GPIO_9"
.LASF171:
	.string	"QDEC_STATUS_INITIALIZED"
.LASF278:
	.string	"hw_latch_status"
.LASF295:
	.string	"output_data"
.LASF164:
	.string	"HAL_QDEC_ZCNT_MODE"
.LASF250:
	.string	"qdec_mode"
.LASF174:
	.string	"QDEC_IRQ_DATA_READY"
.LASF29:
	.string	"SPI_MST0_IRQn"
.LASF289:
	.string	"hal_qdec_enable_hw_sel"
.LASF69:
	.string	"QDEC_IRQ_ENABLE_CELLS"
.LASF8:
	.string	"long long int"
.LASF121:
	.string	"QDEC_SAMPLE_THR_UNION"
.LASF136:
	.string	"QDEC_INFO_UNION"
.LASF101:
	.string	"QDEC_INFO_CELLS"
.LASF137:
	.string	"QDEC_IRQ_STATUS_UNION"
.LASF28:
	.string	"I3C0_DMA_IRQn"
.LASF80:
	.string	"IRQ_CLR_Z_THR_EVENT"
.LASF182:
	.string	"led_period"
.LASF108:
	.string	"WKUP_STATUS_Z_SUM"
.LASF172:
	.string	"QDEC_STATUS_RUNNING"
.LASF93:
	.string	"INVALID_CNT"
.LASF113:
	.string	"IRQ_EVENT_STATUS_Z_CNT"
.LASF270:
	.string	"irq_status"
.LASF281:
	.string	"memset"
.LASF133:
	.string	"QDEC_SAMPLE_INFO_UNION"
.LASF294:
	.string	"new_data"
.LASF30:
	.string	"IRQ_GEN_IRQn"
.LASF19:
	.string	"UART_IRQn"
.LASF302:
	.string	"hal_qdec_disable"
.LASF83:
	.string	"QDEC_IRQ_LCR"
.LASF287:
	.string	"hal_qdec_select_to_group_a"
.LASF286:
	.string	"hal_qdec_select_to_group_b"
.LASF300:
	.string	"callback"
.LASF199:
	.string	"HAL_GPIO_0"
.LASF128:
	.string	"QDEC_WKUP_ENABLE_UNION"
.LASF203:
	.string	"HAL_GPIO_4"
.LASF31:
	.string	"USB_IRQn"
.LASF44:
	.string	"QDEC_SAMPLE_THR_CELLS"
.LASF66:
	.string	"IRQ_ENABLE_Z_SUM"
.LASF149:
	.string	"HAL_QDEC_LED_HIGH_ACTIVE"
.LASF106:
	.string	"QDEC_IRQ_STATUS_CELLS"
.LASF207:
	.string	"HAL_GPIO_8"
.LASF56:
	.string	"SW_RELOAD"
.LASF271:
	.string	"hal_qdec_get_config_group_para"
.LASF144:
	.string	"HW_QDEC_REGISTER_T"
.LASF62:
	.string	"HW_SEL_EN"
.LASF298:
	.string	"z_cnt_thr"
.LASF280:
	.string	"data_ready_irq_status"
.LASF303:
	.string	"hal_qdec_enable"
.LASF72:
	.string	"WKUP_ENABLE_Z_CNT"
.LASF275:
	.string	"qdec_data_getting_type"
.LASF196:
	.string	"long double"
.LASF123:
	.string	"QDEC_SAMPLE_CON_B_UNION"
.LASF12:
	.string	"uint16_t"
.LASF311:
	.string	"IRQn"
.LASF102:
	.string	"QDEC_INFO"
.LASF261:
	.string	"group"
.LASF277:
	.string	"hal_qdec_latch_status_is_busy"
.LASF48:
	.string	"DBC_COUNT_A"
.LASF53:
	.string	"DBC_COUNT_B"
.LASF274:
	.string	"hal_qdec_data_getting_type_set"
.LASF249:
	.string	"qdec_status"
.LASF139:
	.string	"QDEC_IRQ_EVENT_STATUS_UNION"
.LASF145:
	.string	"HAL_QDEC_LED_ACTIVE_MDOE"
.LASF21:
	.string	"RTC_IRQn"
.LASF183:
	.string	"dbc_count"
.LASF126:
	.string	"RESERVED1"
.LASF134:
	.string	"RESERVED2"
.LASF141:
	.string	"RESERVED3"
.LASF252:
	.string	"g_first_data_flag"
.LASF99:
	.string	"QDEC_SW_RELOAD_CLR"
.LASF103:
	.string	"IRQ_STATUS_Z_SUM"
.LASF120:
	.string	"QDEC_LED_CON_UNION"
.LASF290:
	.string	"hal_qdec_get_data"
.LASF305:
	.string	"hal_qdec_init"
.LASF131:
	.string	"QDEC_WKUP_LCR_UNION"
.LASF16:
	.string	"LED_IRQn"
.LASF265:
	.string	"hal_qdec_get_z_sum_threshold"
.LASF22:
	.string	"GPT_IRQn"
.LASF70:
	.string	"QDEC_IRQ_ENABLE"
.LASF127:
	.string	"QDEC_IRQ_ENABLE_UNION"
.LASF109:
	.string	"WKUP_STATUS_Z_CNT"
.LASF194:
	.string	"hal_qdec_callback_t"
.LASF189:
	.string	"led_active_output"
.LASF146:
	.string	"HAL_QDEC_LED_IDLE_MDOE"
.LASF184:
	.string	"hal_qdec_group_config_t"
.LASF309:
	.string	"hw_qdec_irq_type_query"
.LASF306:
	.string	"qdec_cfg"
.LASF85:
	.string	"WKUP_LCR_Z_THR_EVENT"
.LASF166:
	.string	"HAL_QDEC_STATUS_ERROR"
.LASF39:
	.string	"QDEC_LED_CON_CELLS"
.LASF86:
	.string	"QDEC_WKUP_LCR_CELLS"
.LASF269:
	.string	"irq_type"
.LASF107:
	.string	"QDEC_IRQ_STATUS"
.LASF36:
	.string	"LED_POL"
.LASF67:
	.string	"IRQ_ENABLE_Z_CNT"
.LASF291:
	.string	"data"
.LASF14:
	.string	"long unsigned int"
.LASF73:
	.string	"QDEC_WKUP_ENABLE_CELLS"
.LASF181:
	.string	"smp_period"
.LASF314:
	.string	"qdec_data_handler"
.LASF68:
	.string	"IRQ_ENABLE_DATA_RDY"
.LASF297:
	.string	"z_div"
.LASF138:
	.string	"QDEC_WKUP_STATUS_UNION"
.LASF46:
	.string	"SMP_PERIOD_A"
.LASF51:
	.string	"SMP_PERIOD_B"
.LASF173:
	.string	"hal_qdec_hw_status_t"
.LASF54:
	.string	"QDEC_SAMPLE_CON_B_CELLS"
.LASF50:
	.string	"QDEC_SAMPLE_CON_A"
.LASF55:
	.string	"QDEC_SAMPLE_CON_B"
.LASF74:
	.string	"QDEC_WKUP_ENABLE"
.LASF11:
	.string	"unsigned char"
.LASF282:
	.string	"hal_qdec_disable_irq"
.LASF116:
	.string	"WKUP_EVENT_STATUS_Z_SUM"
.LASF279:
	.string	"latch_status"
.LASF96:
	.string	"SW_RELOAD_CLR"
.LASF37:
	.string	"LED_FORCE_OFF"
.LASF179:
	.string	"IRQ_ENABLE"
.LASF162:
	.string	"hal_qdec_data_getting_type_t"
.LASF285:
	.string	"hal_qdec_select_to_idle_status"
.LASF276:
	.string	"hal_qdec_runnig_config_group_para"
.LASF26:
	.string	"EINT_IRQn"
.LASF60:
	.string	"QDEC_CON"
.LASF188:
	.string	"led_force_off"
.LASF100:
	.string	"QDEC_STATE"
.LASF104:
	.string	"IRQ_STATUS_Z_CNT"
.LASF27:
	.string	"I3C0_IRQn"
.LASF284:
	.string	"hal_qdec_select_to_active_status"
.LASF110:
	.string	"QDEC_WKUP_STATUS_CELLS"
.LASF266:
	.string	"threshold"
.LASF296:
	.string	"hal_qdec_zcnt_mode_set"
.LASF47:
	.string	"LED_PERIOD_A"
.LASF52:
	.string	"LED_PERIOD_B"
.LASF5:
	.string	"signed char"
.LASF150:
	.string	"hal_qdec_led_active_value_setting_t"
.LASF105:
	.string	"IRQ_STATUS_DATA_RDY"
.LASF4:
	.string	"short unsigned int"
.LASF24:
	.string	"PMU_IRQn"
.LASF163:
	.string	"HAL_QDEC_ZSUM_MODE"
.LASF117:
	.string	"WKUP_EVENT_STATUS_Z_CNT"
.LASF268:
	.string	"hal_qdec_get_irq_status"
.LASF190:
	.string	"z_sum_thr"
.LASF308:
	.string	"hw_qdec_init_config_para_check"
.LASF135:
	.string	"QDEC_SW_RELOAD_CLR_UNION"
.LASF122:
	.string	"QDEC_SAMPLE_CON_A_UNION"
.LASF256:
	.string	"qdec_callback"
.LASF148:
	.string	"HAL_QDEC_LED_LOW_ACTIVE"
.LASF45:
	.string	"QDEC_SAMPLE_THR"
.LASF59:
	.string	"QDEC_CON_CELLS"
.LASF316:
	.string	"hw_qdec_Isr_zephyr"
.LASF167:
	.string	"HAL_QDEC_INVALID_PARAMETER"
.LASF198:
	.string	"hal_nvic_isr_t"
.LASF88:
	.string	"Z_SUM"
.LASF17:
	.string	"QDEC_IRQn"
.LASF154:
	.string	"HAL_QDEC_SELECT_GROUP_A"
.LASF155:
	.string	"HAL_QDEC_SELECT_GROUP_B"
.LASF130:
	.string	"QDEC_IRQ_LCR_UNION"
.LASF159:
	.string	"hal_qdec_led_setting_t"
.LASF267:
	.string	"hal_qdec_set_z_sum_threshold"
.LASF42:
	.string	"Z_COUNT_THR"
.LASF35:
	.string	"hal_nvic_irq_t"
.LASF185:
	.string	"pina_pin"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_qdec.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
