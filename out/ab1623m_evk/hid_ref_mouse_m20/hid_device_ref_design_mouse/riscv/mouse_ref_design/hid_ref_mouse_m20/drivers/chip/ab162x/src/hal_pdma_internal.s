	.file	"hal_pdma_internal.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.section	.text.internal_pdma_restore_default_value,"ax",@progbits
	.align	1
	.type	internal_pdma_restore_default_value, @function
internal_pdma_restore_default_value:
.LFB11:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.loc 1 313 1
	.cfi_startproc
.LVL0:
	.loc 1 314 5
	.loc 1 315 5
	.loc 1 317 5
	.loc 1 317 16 is_stmt 0
	slli	a0,a0,2
.LVL1:
	lla	a5,g_pdma_status_regbase_table
	add	a5,a5,a0
	lw	a4,0(a5)
.LVL2:
	.loc 1 318 5 is_stmt 1
	.loc 1 318 14 is_stmt 0
	lla	a5,g_pdma_cfg_regbase_table
	add	a5,a5,a0
	lw	a5,0(a5)
.LVL3:
	.loc 1 320 5 is_stmt 1
	.loc 1 327 39 is_stmt 0
	li	a3,32768
	.loc 1 320 31
	sw	zero,20(a5)
	.loc 1 321 5 is_stmt 1
	.loc 1 321 30 is_stmt 0
	sw	zero,0(a5)
	.loc 1 322 5 is_stmt 1
	.loc 1 322 30 is_stmt 0
	sw	zero,4(a5)
	.loc 1 323 5 is_stmt 1
	.loc 1 323 31 is_stmt 0
	sw	zero,8(a5)
	.loc 1 324 5 is_stmt 1
	.loc 1 324 29 is_stmt 0
	sw	zero,12(a5)
	.loc 1 325 5 is_stmt 1
	.loc 1 325 35 is_stmt 0
	sw	zero,12(a4)
	.loc 1 326 5 is_stmt 1
	.loc 1 326 33 is_stmt 0
	sw	zero,16(a5)
	.loc 1 327 5 is_stmt 1
	.loc 1 327 39 is_stmt 0
	lw	a5,4(a4)
.LVL4:
	or	a5,a5,a3
	sw	a5,4(a4)
	.loc 1 328 1
	ret
	.cfi_endproc
.LFE11:
	.size	internal_pdma_restore_default_value, .-internal_pdma_restore_default_value
	.section	.text.internal_vdma_restore_default_value,"ax",@progbits
	.align	1
	.type	internal_vdma_restore_default_value, @function
internal_vdma_restore_default_value:
.LFB24:
	.loc 1 673 1 is_stmt 1
	.cfi_startproc
.LVL5:
	.loc 1 674 5
	.loc 1 676 5
	.loc 1 676 10 is_stmt 0
	slli	a0,a0,2
.LVL6:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a0
	lw	a5,0(a5)
.LVL7:
	.loc 1 677 5 is_stmt 1
	.loc 1 685 23 is_stmt 0
	li	a4,32768
	.loc 1 677 22
	sw	zero,8(a5)
	.loc 1 678 5 is_stmt 1
	.loc 1 678 35 is_stmt 0
	sw	zero,4(a5)
	.loc 1 679 5 is_stmt 1
	.loc 1 679 22 is_stmt 0
	sw	zero,0(a5)
	.loc 1 680 5 is_stmt 1
	.loc 1 680 23 is_stmt 0
	sw	zero,12(a5)
	.loc 1 681 5 is_stmt 1
	.loc 1 681 24 is_stmt 0
	sw	zero,28(a5)
	.loc 1 682 5 is_stmt 1
	.loc 1 682 23 is_stmt 0
	sw	zero,48(a5)
	.loc 1 683 5 is_stmt 1
	.loc 1 683 23 is_stmt 0
	sw	zero,52(a5)
	.loc 1 684 5 is_stmt 1
	.loc 1 684 24 is_stmt 0
	sw	zero,24(a5)
	.loc 1 685 5 is_stmt 1
	.loc 1 685 23 is_stmt 0
	sw	a4,16(a5)
	.loc 1 686 1
	ret
	.cfi_endproc
.LFE24:
	.size	internal_vdma_restore_default_value, .-internal_vdma_restore_default_value
	.section	.text.internal_dma_check_idle_status,"ax",@progbits
	.align	1
	.type	internal_dma_check_idle_status, @function
internal_dma_check_idle_status:
.LFB9:
	.loc 1 217 1 is_stmt 1
	.cfi_startproc
.LVL8:
	.loc 1 218 5
	.loc 1 220 5
	.loc 1 217 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 220 8
	li	a5,9
	.loc 1 217 1
	mv	s0,a0
	.loc 1 220 8
	bgtu	a0,a5,.L4
	.loc 1 221 9 is_stmt 1
	.loc 1 221 23 is_stmt 0
	andi	a5,a0,1
.LVL9:
.L5:
	.loc 1 225 275 is_stmt 1 discriminator 3
	.loc 1 228 5
	.loc 1 230 65 is_stmt 0
	srli	a3,s0,1
	.loc 1 230 53
	slli	a3,a3,2
	lla	a4,g_dma_reg_table
	add	a4,a4,a3
	.loc 1 230 100
	slli	a5,a5,1
	.loc 1 230 94
	li	a3,1
	.loc 1 228 52
	addi	a0,s0,-6
	.loc 1 228 7
	li	a2,3
	.loc 1 230 53
	lw	a4,0(a4)
	.loc 1 230 94
	sll	a1,a3,a5
	.loc 1 228 7
	bgtu	a0,a2,.L6
	.loc 1 230 9 is_stmt 1
	.loc 1 230 82 is_stmt 0
	lw	a2,60(a4)
	.loc 1 232 19
	li	a0,0
	.loc 1 230 89
	and	a2,a2,a1
	.loc 1 230 12
	bne	a2,zero,.L7
	.loc 1 231 82
	lw	a4,60(a4)
	.loc 1 231 119
	addi	a0,a5,1
	.loc 1 231 95
	sll	a0,a3,a0
	.loc 1 231 89
	and	a0,a0,a4
	.loc 1 230 121 discriminator 1
	seqz	a0,a0
.L7:
	.loc 1 244 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL10:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL11:
.L4:
	.cfi_restore_state
	.loc 1 222 12 is_stmt 1
	.loc 1 225 9
.LBB3:
	.loc 1 225 26 discriminator 1
	.loc 1 225 102 discriminator 1
	.loc 1 225 244 discriminator 1
	li	a2,225
	lla	a1,file.10
	lla	a0,exp.11
	call	light_assert
.LVL12:
.LBE3:
	.loc 1 218 14 is_stmt 0
	li	a5,0
	j	.L5
.LVL13:
.L6:
	.loc 1 237 9 is_stmt 1
	.loc 1 237 45 is_stmt 0
	lw	a2,0(a4)
	.loc 1 232 19
	li	a0,0
	.loc 1 237 59
	and	a2,a2,a1
	.loc 1 237 12
	bne	a2,zero,.L7
	.loc 1 238 45
	lw	a2,0(a4)
	.loc 1 238 89
	addi	a4,a5,1
	.loc 1 238 65
	sll	a5,a3,a4
	.loc 1 238 59
	and	a5,a5,a2
	.loc 1 237 91 discriminator 1
	seqz	a0,a5
	j	.L7
	.cfi_endproc
.LFE9:
	.size	internal_dma_check_idle_status, .-internal_dma_check_idle_status
	.section	.text.internal_dma_disable_irq,"ax",@progbits
	.align	1
	.type	internal_dma_disable_irq, @function
internal_dma_disable_irq:
.LFB8:
	.loc 1 197 1 is_stmt 1
	.cfi_startproc
.LVL14:
	.loc 1 198 5
	.loc 1 200 5
	.loc 1 197 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 200 8
	li	a5,9
	.loc 1 197 1
	mv	s0,a0
	.loc 1 201 23
	andi	a3,a0,1
	.loc 1 200 8
	bleu	a0,a5,.L13
	.loc 1 202 12 is_stmt 1
	.loc 1 205 9
.LBB4:
	.loc 1 205 26 discriminator 1
	.loc 1 205 102 discriminator 1
	.loc 1 205 244 discriminator 1
	li	a2,205
	lla	a1,file.12
	lla	a0,exp.13
.LVL15:
	call	light_assert
.LVL16:
.LBE4:
	.loc 1 198 14 is_stmt 0
	li	a3,0
.L13:
.LVL17:
	.loc 1 205 275 is_stmt 1 discriminator 3
	.loc 1 208 5
	.loc 1 210 59 is_stmt 0
	srli	a4,s0,1
	.loc 1 210 47
	slli	a4,a4,2
	lla	a5,g_dma_reg_table
	add	a5,a5,a4
	lw	a4,0(a5)
	.loc 1 210 93
	li	a5,1
	sll	a5,a5,a3
	.loc 1 208 52
	addi	s0,s0,-6
.LVL18:
	.loc 1 208 7
	li	a3,3
	bgtu	s0,a3,.L14
	.loc 1 210 9 is_stmt 1
	.loc 1 210 88 is_stmt 0
	sw	a5,76(a4)
.L11:
	.loc 1 214 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL19:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.L14:
	.cfi_restore_state
	.loc 1 212 9 is_stmt 1
	.loc 1 212 61 is_stmt 0
	sw	a5,28(a4)
	.loc 1 214 1
	j	.L11
	.cfi_endproc
.LFE8:
	.size	internal_dma_disable_irq, .-internal_dma_disable_irq
	.section	.text.internal_dma_disable_clock,"ax",@progbits
	.align	1
	.type	internal_dma_disable_clock, @function
internal_dma_disable_clock:
.LFB6:
	.loc 1 157 1 is_stmt 1
	.cfi_startproc
.LVL20:
	.loc 1 158 5
	.loc 1 160 5
	.loc 1 157 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 160 8
	li	a5,9
	.loc 1 157 1
	mv	s0,a0
	.loc 1 161 23
	andi	a3,a0,1
	.loc 1 160 8
	bleu	a0,a5,.L19
	.loc 1 162 12 is_stmt 1
	.loc 1 165 9
.LBB5:
	.loc 1 165 26 discriminator 1
	.loc 1 165 102 discriminator 1
	.loc 1 165 244 discriminator 1
	li	a2,165
	lla	a1,file.16
	lla	a0,exp.17
.LVL21:
	call	light_assert
.LVL22:
.LBE5:
	.loc 1 158 14 is_stmt 0
	li	a3,0
.L19:
.LVL23:
	.loc 1 165 275 is_stmt 1 discriminator 3
	.loc 1 168 5
	.loc 1 170 59 is_stmt 0
	srli	a4,s0,1
	.loc 1 170 47
	slli	a4,a4,2
	lla	a5,g_dma_reg_table
	add	a5,a5,a4
	lw	a4,0(a5)
	.loc 1 170 92
	li	a5,1
	sll	a5,a5,a3
	.loc 1 168 52
	addi	s0,s0,-6
.LVL24:
	.loc 1 168 7
	li	a3,3
	bgtu	s0,a3,.L20
	.loc 1 170 9 is_stmt 1
	.loc 1 170 87 is_stmt 0
	sw	a5,104(a4)
.L17:
	.loc 1 174 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL25:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.L20:
	.cfi_restore_state
	.loc 1 172 9 is_stmt 1
	.loc 1 172 56 is_stmt 0
	sw	a5,120(a4)
	.loc 1 174 1
	j	.L17
	.cfi_endproc
.LFE6:
	.size	internal_dma_disable_clock, .-internal_dma_disable_clock
	.section	.text.i3c_dma_interrupt_hander,"ax",@progbits
	.align	1
	.type	i3c_dma_interrupt_hander, @function
i3c_dma_interrupt_hander:
.LFB52:
	.loc 1 1370 1 is_stmt 1
	.cfi_startproc
.LVL26:
	.loc 1 1371 5
	.loc 1 1372 5
	.loc 1 1373 5
	.loc 1 1374 5
	.loc 1 1375 5
	.loc 1 1377 5
	.loc 1 1370 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 1377 8
	li	a5,26
	lla	s0,g_pdma_init_status
	beq	a0,a5,.L24
	.loc 1 1378 9 is_stmt 1
.LBB6:
	.loc 1 1378 26 discriminator 1
	.loc 1 1378 102 discriminator 1
	.loc 1 1378 244 discriminator 1
	li	a2,1378
	lla	a1,file.0
	lla	a0,exp.1
.LVL27:
	call	light_assert
.LVL28:
.LBE6:
	.loc 1 1378 276 discriminator 3
	.loc 1 1381 5
	.loc 1 1398 56 discriminator 1
	.loc 1 1399 13
	.loc 1 1400 13
	.loc 1 1400 36 is_stmt 0
	lbu	a4,2(s0)
	.loc 1 1400 16
	li	a5,1
	bne	a4,a5,.L26
	.loc 1 1401 46
	li	a5,1074724864
	lw	a5,0(a5)
	.loc 1 1401 60
	andi	a5,a5,2
	.loc 1 1401 17
	beq	a5,zero,.L26
	.loc 1 1403 17 is_stmt 1
.LVL29:
	.loc 1 1404 17
	.loc 1 1404 51 is_stmt 0
	li	a5,1074724864
	addi	a5,a5,284
	lw	a4,4(a5)
	li	a3,32768
	or	a4,a4,a3
	sw	a4,4(a5)
	.loc 1 1406 17 is_stmt 1
	.loc 1 1406 31 is_stmt 0
	lla	a4,g_pdma_callback
	lw	a5,16(a4)
.LVL30:
	.loc 1 1407 17 is_stmt 1
	.loc 1 1407 26 is_stmt 0
	lw	a1,20(a4)
.LVL31:
	.loc 1 1408 17 is_stmt 1
	.loc 1 1408 20 is_stmt 0
	beq	a5,zero,.L26
	.loc 1 1409 21 is_stmt 1
	li	a0,0
	jalr	a5
.LVL32:
.L26:
	.loc 1 1398 90 discriminator 2
	.loc 1 1398 56 discriminator 1
	.loc 1 1399 13
	.loc 1 1400 13
	.loc 1 1400 36 is_stmt 0
	lbu	a4,3(s0)
	.loc 1 1400 16
	li	a5,1
	bne	a4,a5,.L23
	.loc 1 1401 46
	li	a5,1074724864
	lw	a5,0(a5)
	.loc 1 1401 60
	andi	a5,a5,8
	.loc 1 1401 17
	beq	a5,zero,.L23
	.loc 1 1403 17 is_stmt 1
.LVL33:
	.loc 1 1404 17
	.loc 1 1404 51 is_stmt 0
	li	a5,1074724864
	addi	a5,a5,540
	lw	a4,4(a5)
	li	a3,32768
	or	a4,a4,a3
	sw	a4,4(a5)
	.loc 1 1406 17 is_stmt 1
	.loc 1 1406 31 is_stmt 0
	lla	a4,g_pdma_callback
	lw	a5,24(a4)
.LVL34:
	.loc 1 1407 17 is_stmt 1
	.loc 1 1407 26 is_stmt 0
	lw	a1,28(a4)
	j	.L63
.LVL35:
.L24:
	.loc 1 1383 13 is_stmt 1
	.loc 1 1384 13
	.loc 1 1384 36 is_stmt 0
	lbu	a4,0(s0)
	.loc 1 1384 16
	li	a5,1
	bne	a4,a5,.L30
	.loc 1 1385 46
	li	a5,1109524480
	lw	a5,0(a5)
	.loc 1 1385 60
	andi	a5,a5,2
	.loc 1 1385 17
	beq	a5,zero,.L30
	.loc 1 1387 17 is_stmt 1
.LVL36:
	.loc 1 1388 17
	.loc 1 1388 51 is_stmt 0
	li	a5,1109524480
	addi	a5,a5,284
	lw	a4,4(a5)
	li	a3,32768
	or	a4,a4,a3
	sw	a4,4(a5)
	.loc 1 1390 17 is_stmt 1
	.loc 1 1390 31 is_stmt 0
	lla	a4,g_pdma_callback
	lw	a5,0(a4)
.LVL37:
	.loc 1 1391 17 is_stmt 1
	.loc 1 1391 26 is_stmt 0
	lw	a1,4(a4)
.LVL38:
	.loc 1 1392 17 is_stmt 1
	.loc 1 1392 20 is_stmt 0
	beq	a5,zero,.L30
	.loc 1 1393 21 is_stmt 1
	li	a0,0
.LVL39:
	jalr	a5
.LVL40:
.L30:
	.loc 1 1382 90 discriminator 2
	.loc 1 1382 56 discriminator 1
	.loc 1 1383 13
	.loc 1 1384 13
	.loc 1 1384 36 is_stmt 0
	lbu	a4,1(s0)
	.loc 1 1384 16
	li	a5,1
	bne	a4,a5,.L23
	.loc 1 1385 46
	li	a5,1109524480
	lw	a5,0(a5)
	.loc 1 1385 60
	andi	a5,a5,8
	.loc 1 1385 17
	beq	a5,zero,.L23
	.loc 1 1387 17 is_stmt 1
.LVL41:
	.loc 1 1388 17
	.loc 1 1388 51 is_stmt 0
	li	a5,1109524480
	addi	a5,a5,540
	lw	a4,4(a5)
	li	a3,32768
	or	a4,a4,a3
	sw	a4,4(a5)
	.loc 1 1390 17 is_stmt 1
	.loc 1 1390 31 is_stmt 0
	lla	a4,g_pdma_callback
	lw	a5,8(a4)
.LVL42:
	.loc 1 1391 17 is_stmt 1
	.loc 1 1391 26 is_stmt 0
	lw	a1,12(a4)
.LVL43:
	.loc 1 1392 17 is_stmt 1
.L63:
	.loc 1 1408 17
	.loc 1 1408 20 is_stmt 0
	beq	a5,zero,.L23
	.loc 1 1409 21 is_stmt 1
	.loc 1 1414 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 1409 21
	li	a0,0
	.loc 1 1414 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 1409 21
	jr	a5
.LVL44:
.L23:
	.cfi_restore_state
	.loc 1 1414 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE52:
	.size	i3c_dma_interrupt_hander, .-i3c_dma_interrupt_hander
	.section	.text.internal_dma_enable_irq,"ax",@progbits
	.align	1
	.type	internal_dma_enable_irq, @function
internal_dma_enable_irq:
.LFB7:
	.loc 1 177 1 is_stmt 1
	.cfi_startproc
.LVL45:
	.loc 1 178 5
	.loc 1 180 5
	.loc 1 177 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 180 8
	li	a5,9
	.loc 1 177 1
	mv	s0,a0
	.loc 1 181 23
	andi	a3,a0,1
	.loc 1 180 8
	bleu	a0,a5,.L66
	.loc 1 182 12 is_stmt 1
	.loc 1 185 9
.LBB7:
	.loc 1 185 26 discriminator 1
	.loc 1 185 102 discriminator 1
	.loc 1 185 244 discriminator 1
	li	a2,185
	lla	a1,file.14
	lla	a0,exp.15
.LVL46:
	call	light_assert
.LVL47:
.LBE7:
	.loc 1 178 14 is_stmt 0
	li	a3,0
.L66:
.LVL48:
	.loc 1 185 275 is_stmt 1 discriminator 3
	.loc 1 188 5
	.loc 1 190 59 is_stmt 0
	srli	a4,s0,1
	.loc 1 190 47
	slli	a4,a4,2
	lla	a5,g_dma_reg_table
	add	a5,a5,a4
	lw	a4,0(a5)
	.loc 1 190 93
	li	a5,1
	sll	a5,a5,a3
	.loc 1 188 52
	addi	s0,s0,-6
.LVL49:
	.loc 1 188 7
	li	a3,3
	bgtu	s0,a3,.L67
	.loc 1 190 9 is_stmt 1
	.loc 1 190 88 is_stmt 0
	sw	a5,72(a4)
.L64:
	.loc 1 194 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL50:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.L67:
	.cfi_restore_state
	.loc 1 192 9 is_stmt 1
	.loc 1 192 61 is_stmt 0
	sw	a5,24(a4)
	.loc 1 194 1
	j	.L64
	.cfi_endproc
.LFE7:
	.size	internal_dma_enable_irq, .-internal_dma_enable_irq
	.section	.text.internal_dma_enable_clock,"ax",@progbits
	.align	1
	.type	internal_dma_enable_clock, @function
internal_dma_enable_clock:
.LFB5:
	.loc 1 131 1 is_stmt 1
	.cfi_startproc
.LVL51:
	.loc 1 132 5
	.loc 1 134 5
	.loc 1 131 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	s1,4(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 137 53
	srli	s1,a0,1
	.loc 1 134 8
	li	a5,5
	.loc 1 131 1
	mv	s0,a0
	slli	s1,s1,2
	.loc 1 134 8
	bgtu	a0,a5,.L71
.L77:
	.loc 1 140 9 is_stmt 1
	.loc 1 142 9 is_stmt 0
	lla	a5,g_dma_clk_table
	add	a5,a5,s1
	lw	a0,0(a5)
.LVL52:
	.loc 1 140 23
	andi	a4,s0,1
	sw	a4,0(sp)
.LVL53:
	.loc 1 142 9 is_stmt 1
	call	hal_clock_enable
.LVL54:
	lw	a4,0(sp)
.LVL55:
.L72:
	.loc 1 145 275 discriminator 3
	.loc 1 148 5
	.loc 1 150 47 is_stmt 0
	lla	a5,g_dma_reg_table
	add	a5,a5,s1
	lw	a3,0(a5)
	.loc 1 150 92
	li	a5,1
	sll	a5,a5,a4
	.loc 1 148 52
	addi	s0,s0,-6
.LVL56:
	.loc 1 148 7
	li	a4,3
	bgtu	s0,a4,.L74
	.loc 1 150 9 is_stmt 1
	.loc 1 150 87 is_stmt 0
	sw	a5,100(a3)
.L70:
	.loc 1 154 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL57:
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL58:
.L71:
	.cfi_restore_state
	.loc 1 139 12 is_stmt 1
	.loc 1 139 15 is_stmt 0
	li	a5,9
	bleu	a0,a5,.L77
	.loc 1 145 9 is_stmt 1
.LBB8:
	.loc 1 145 26 discriminator 1
	.loc 1 145 102 discriminator 1
	.loc 1 145 244 discriminator 1
	li	a2,145
	lla	a1,file.18
	lla	a0,exp.19
	call	light_assert
.LVL59:
.LBE8:
	.loc 1 132 14 is_stmt 0
	li	a4,0
	j	.L72
.LVL60:
.L74:
	.loc 1 152 9 is_stmt 1
	.loc 1 152 56 is_stmt 0
	sw	a5,116(a3)
	.loc 1 154 1
	j	.L70
	.cfi_endproc
.LFE5:
	.size	internal_dma_enable_clock, .-internal_dma_enable_clock
	.section	.text.internal_dma_register_irq_callback,"ax",@progbits
	.align	1
	.type	internal_dma_register_irq_callback, @function
internal_dma_register_irq_callback:
.LFB4:
	.loc 1 115 1 is_stmt 1
	.cfi_startproc
.LVL61:
	.loc 1 116 5
	.loc 1 115 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	a0,0(sp)
	.loc 1 118 5
	addi	a0,sp,4
.LVL62:
	.loc 1 115 1
	sw	s0,12(sp)
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 116 14
	sw	zero,4(sp)
	.loc 1 118 5 is_stmt 1
	call	hal_nvic_save_and_set_interrupt_mask
.LVL63:
	.loc 1 119 5
	.loc 1 120 66 is_stmt 0
	lw	a5,0(sp)
	.loc 1 119 8
	li	a4,5
	lla	s0,g_dma_irq_table
	.loc 1 120 66
	srli	s1,a5,1
	slli	s1,s1,2
	.loc 1 119 8
	bgtu	a5,a4,.L79
	.loc 1 120 9 is_stmt 1
	add	a5,s0,s1
	lla	a1,uart_dma_interrupt_hander
.L83:
	.loc 1 122 9 is_stmt 0
	lw	a0,0(a5)
	call	hal_nvic_register_isr_handler
.LVL64:
.L80:
	.loc 1 124 275 is_stmt 1 discriminator 3
	.loc 1 126 5
	add	s0,s0,s1
	lw	a0,0(s0)
	call	hal_nvic_enable_irq
.LVL65:
	.loc 1 127 5
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL66:
	.loc 1 128 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
.LVL67:
	jr	ra
.LVL68:
.L79:
	.cfi_restore_state
	.loc 1 121 12 is_stmt 1
	.loc 1 121 15 is_stmt 0
	li	a4,9
	bgtu	a5,a4,.L81
	.loc 1 122 9 is_stmt 1
	add	a5,s0,s1
	lla	a1,i3c_dma_interrupt_hander
	j	.L83
.L81:
	.loc 1 124 9
.LBB9:
	.loc 1 124 26 discriminator 1
	.loc 1 124 102 discriminator 1
	.loc 1 124 244 discriminator 1
	li	a2,124
	lla	a1,file.20
	lla	a0,exp.21
	call	light_assert
.LVL69:
	j	.L80
.LBE9:
	.cfi_endproc
.LFE4:
	.size	internal_dma_register_irq_callback, .-internal_dma_register_irq_callback
	.section	.text.uart_dma_interrupt_hander,"ax",@progbits
	.align	1
	.type	uart_dma_interrupt_hander, @function
uart_dma_interrupt_hander:
.LFB51:
	.loc 1 1287 1
	.cfi_startproc
.LVL70:
	.loc 1 1288 5
	.loc 1 1289 5
	.loc 1 1290 5
	.loc 1 1291 5
	.loc 1 1292 5
	.loc 1 1294 5
	.loc 1 1294 8 is_stmt 0
	li	a5,21
	beq	a0,a5,.L85
	.loc 1 1295 9 is_stmt 1
.LBB14:
	.loc 1 1295 26 discriminator 1
	.loc 1 1295 102 discriminator 1
	.loc 1 1295 244 discriminator 1
	li	a2,1295
	lla	a1,file.2
	lla	a0,exp.3
.LVL71:
	tail	light_assert
.LVL72:
.L85:
.LBE14:
.LBB15:
.LBB16:
	.loc 1 1300 13
	.loc 1 1301 13
	.loc 1 1301 36 is_stmt 0
	lbu	a4,g_vdma_init_status
	.loc 1 1301 16
	li	a5,1
	bne	a4,a5,.L104
	.loc 1 1302 47
	li	a5,1109852160
	lw	a5,0(a5)
	.loc 1 1302 61
	andi	a5,a5,2
	.loc 1 1302 17
	beq	a5,zero,.L104
	.loc 1 1304 17 is_stmt 1
	.loc 1 1304 22 is_stmt 0
	lw	a5,g_vdma_regbase_table
.LVL73:
	.loc 1 1305 17 is_stmt 1
	.loc 1 1305 35 is_stmt 0
	li	a4,32768
	sw	a4,16(a5)
	.loc 1 1307 17 is_stmt 1
	.loc 1 1307 31 is_stmt 0
	lla	a4,g_vdma_callback
	lw	a5,0(a4)
.LVL74:
	.loc 1 1308 17 is_stmt 1
	.loc 1 1308 26 is_stmt 0
	lw	a1,4(a4)
.LVL75:
	.loc 1 1309 17 is_stmt 1
	.loc 1 1309 20 is_stmt 0
	beq	a5,zero,.L104
	.loc 1 1310 21 is_stmt 1
.LBE16:
.LBE15:
	.loc 1 1287 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
.LBB21:
.LBB17:
	.loc 1 1310 21
	li	a0,0
.LVL76:
	jalr	a5
.LVL77:
	.loc 1 1299 94 is_stmt 1 discriminator 2
	.loc 1 1299 58 discriminator 1
	.loc 1 1300 13
	.loc 1 1301 13
	.loc 1 1301 36 is_stmt 0
	lbu	a4,g_vdma_init_status+1
	.loc 1 1301 16
	li	a5,1
	bne	a4,a5,.L84
	.loc 1 1302 47
	li	a5,1109852160
	lw	a5,0(a5)
	.loc 1 1302 61
	andi	a5,a5,8
	.loc 1 1302 17
	beq	a5,zero,.L84
	.loc 1 1304 17 is_stmt 1
	.loc 1 1304 22 is_stmt 0
	lw	a5,g_vdma_regbase_table+4
.LVL78:
	.loc 1 1305 17 is_stmt 1
	.loc 1 1305 35 is_stmt 0
	li	a4,32768
	sw	a4,16(a5)
	.loc 1 1307 17 is_stmt 1
	.loc 1 1307 31 is_stmt 0
	lla	a4,g_vdma_callback
	lw	a5,8(a4)
.LVL79:
	.loc 1 1308 17 is_stmt 1
	.loc 1 1308 26 is_stmt 0
	lw	a1,12(a4)
.LVL80:
	.loc 1 1309 17 is_stmt 1
	.loc 1 1309 20 is_stmt 0
	beq	a5,zero,.L84
	.loc 1 1310 21 is_stmt 1
.LBE17:
.LBE21:
	.loc 1 1347 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
.LBB22:
.LBB18:
	.loc 1 1310 21
	li	a0,0
.LBE18:
.LBE22:
	.loc 1 1347 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
.L111:
.LBB23:
.LBB19:
	.loc 1 1310 21
	jr	a5
.LVL81:
.L84:
	.cfi_def_cfa_offset 12
	.cfi_offset 1, -4
.LBE19:
.LBE23:
	.loc 1 1347 1
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL82:
.L104:
.LBB24:
.LBB20:
	.loc 1 1299 94 is_stmt 1 discriminator 2
	.loc 1 1299 58 discriminator 1
	.loc 1 1300 13
	.loc 1 1301 13
	.loc 1 1301 36 is_stmt 0
	lbu	a4,g_vdma_init_status+1
	.loc 1 1301 16
	li	a5,1
	bne	a4,a5,.L106
	.loc 1 1302 47
	li	a5,1109852160
	lw	a5,0(a5)
	.loc 1 1302 61
	andi	a5,a5,8
	.loc 1 1302 17
	beq	a5,zero,.L106
	.loc 1 1304 17 is_stmt 1
	.loc 1 1304 22 is_stmt 0
	lw	a5,g_vdma_regbase_table+4
.LVL83:
	.loc 1 1305 17 is_stmt 1
	.loc 1 1305 35 is_stmt 0
	li	a4,32768
	sw	a4,16(a5)
	.loc 1 1307 17 is_stmt 1
	.loc 1 1307 31 is_stmt 0
	lla	a4,g_vdma_callback
	lw	a5,8(a4)
.LVL84:
	.loc 1 1308 17 is_stmt 1
	.loc 1 1308 26 is_stmt 0
	lw	a1,12(a4)
.LVL85:
	.loc 1 1309 17 is_stmt 1
	.loc 1 1309 20 is_stmt 0
	beq	a5,zero,.L106
	.loc 1 1310 21 is_stmt 1
	li	a0,0
.LVL86:
	j	.L111
.LVL87:
.L106:
	ret
.LBE20:
.LBE24:
	.cfi_endproc
.LFE51:
	.size	uart_dma_interrupt_hander, .-uart_dma_interrupt_hander
	.section	.text.pdma_init,"ax",@progbits
	.align	1
	.globl	pdma_init
	.hidden	pdma_init
	.type	pdma_init, @function
pdma_init:
.LFB12:
	.loc 1 331 1
	.cfi_startproc
.LVL88:
	.loc 1 332 5
	.loc 1 334 5
	.loc 1 334 8 is_stmt 0
	li	a5,3
	bgtu	a0,a5,.L117
	.loc 1 331 1
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	.loc 1 338 5 is_stmt 1
	mv	a0,sp
.LVL89:
	.loc 1 331 1 is_stmt 0
	sw	ra,12(sp)
	sw	s1,4(sp)
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 338 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL90:
	.loc 1 339 5 is_stmt 1
	.loc 1 339 27 is_stmt 0
	lla	a5,g_pdma_init_status
	add	a5,a5,s0
	lbu	a3,0(a5)
	.loc 1 339 8
	li	a4,1
	lw	a0,0(sp)
	bne	a3,a4,.L114
	.loc 1 340 9 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL91:
	.loc 1 341 9
.L115:
	.loc 1 341 16 is_stmt 0
	li	a0,-3
.L112:
	.loc 1 354 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL92:
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL93:
.L114:
	.cfi_restore_state
	.loc 1 343 5 is_stmt 1
	.loc 1 343 33 is_stmt 0
	sb	a4,0(a5)
	.loc 1 344 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL94:
	.loc 1 346 5
	.loc 1 346 9 is_stmt 0
	slli	a4,s0,2
	lla	a5,g_pdma_channel_map_table
	add	a5,a5,a4
	lw	s1,0(a5)
	mv	a0,s1
	call	internal_dma_check_idle_status
.LVL95:
	.loc 1 346 8 discriminator 1
	beq	a0,zero,.L115
	.loc 1 350 5 is_stmt 1
	mv	a0,s1
	call	internal_dma_enable_clock
.LVL96:
	.loc 1 351 5
	mv	a0,s0
	call	internal_pdma_restore_default_value
.LVL97:
	.loc 1 353 5
	.loc 1 353 12 is_stmt 0
	li	a0,0
	j	.L112
.LVL98:
.L117:
	.cfi_def_cfa_offset 0
	.cfi_restore 1
	.cfi_restore 8
	.cfi_restore 9
	.loc 1 335 16
	li	a0,-2
.LVL99:
	.loc 1 354 1
	ret
	.cfi_endproc
.LFE12:
	.size	pdma_init, .-pdma_init
	.section	.text.pdma_deinit,"ax",@progbits
	.align	1
	.globl	pdma_deinit
	.hidden	pdma_deinit
	.type	pdma_deinit, @function
pdma_deinit:
.LFB13:
	.loc 1 357 1 is_stmt 1
	.cfi_startproc
.LVL100:
	.loc 1 358 5
	.loc 1 360 5
	.loc 1 360 8 is_stmt 0
	li	a4,3
	bgtu	a0,a4,.L127
	.loc 1 357 1
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	sw	s1,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 365 27
	lla	s0,g_pdma_init_status
	mv	s1,a0
	.loc 1 364 5 is_stmt 1
	addi	a0,sp,4
.LVL101:
	.loc 1 357 1 is_stmt 0
	sw	ra,16(sp)
	.cfi_offset 1, -4
	.loc 1 365 27
	add	s0,s0,s1
	.loc 1 364 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL102:
	.loc 1 365 5 is_stmt 1
	.loc 1 365 27 is_stmt 0
	lbu	a4,0(s0)
	.loc 1 365 8
	bne	a4,zero,.L124
	.loc 1 366 9 is_stmt 1
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL103:
	.loc 1 367 9
.L125:
	.loc 1 367 16 is_stmt 0
	li	a0,-3
.L122:
	.loc 1 382 1
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
.LVL104:
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL105:
.L124:
	.cfi_restore_state
	.loc 1 370 5 is_stmt 1
	.loc 1 370 9 is_stmt 0
	slli	a3,s1,2
	lla	a4,g_pdma_channel_map_table
	add	a4,a4,a3
	lw	a5,0(a4)
	mv	a0,a5
	sw	a5,0(sp)
	call	internal_dma_check_idle_status
.LVL106:
	.loc 1 370 8 discriminator 1
	beq	a0,zero,.L125
	.loc 1 374 5 is_stmt 1
	mv	a0,s1
	call	internal_pdma_restore_default_value
.LVL107:
	.loc 1 375 5
	lw	a0,0(sp)
	call	internal_dma_disable_irq
.LVL108:
	.loc 1 376 5
	lw	a0,0(sp)
	call	internal_dma_disable_clock
.LVL109:
	.loc 1 378 5
	.loc 1 379 5 is_stmt 0
	lw	a0,4(sp)
	.loc 1 378 33
	sb	zero,0(s0)
	.loc 1 379 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL110:
	.loc 1 381 5
	.loc 1 381 12 is_stmt 0
	li	a0,0
	j	.L122
.LVL111:
.L127:
	.cfi_def_cfa_offset 0
	.cfi_restore 1
	.cfi_restore 8
	.cfi_restore 9
	.loc 1 361 16
	li	a0,-2
.LVL112:
	.loc 1 382 1
	ret
	.cfi_endproc
.LFE13:
	.size	pdma_deinit, .-pdma_deinit
	.section	.text.pdma_set_ring_buffer,"ax",@progbits
	.align	1
	.globl	pdma_set_ring_buffer
	.hidden	pdma_set_ring_buffer
	.type	pdma_set_ring_buffer, @function
pdma_set_ring_buffer:
.LFB14:
	.loc 1 385 1 is_stmt 1
	.cfi_startproc
.LVL113:
	.loc 1 386 5
	.loc 1 388 5
	.loc 1 388 8 is_stmt 0
	li	a4,3
	.loc 1 385 1
	mv	a5,a0
	.loc 1 388 8
	bgtu	a0,a4,.L134
	.loc 1 391 5 is_stmt 1
	.loc 1 391 8 is_stmt 0
	li	a4,65536
	.loc 1 392 16
	li	a0,-1
.LVL114:
	.loc 1 391 8
	bgeu	a1,a4,.L132
	.loc 1 395 5 is_stmt 1
	.loc 1 395 14 is_stmt 0
	lla	a4,g_pdma_cfg_regbase_table
	slli	a5,a5,2
.LVL115:
	add	a5,a4,a5
	lw	a5,0(a5)
.LVL116:
	.loc 1 396 5 is_stmt 1
	.loc 1 399 12 is_stmt 0
	li	a0,0
	.loc 1 396 30
	sw	a1,0(a5)
	.loc 1 397 5 is_stmt 1
	.loc 1 397 30 is_stmt 0
	sw	a2,4(a5)
	.loc 1 399 5 is_stmt 1
	.loc 1 399 12 is_stmt 0
	ret
.LVL117:
.L134:
	.loc 1 389 16
	li	a0,-2
.LVL118:
.L132:
	.loc 1 400 1
	ret
	.cfi_endproc
.LFE14:
	.size	pdma_set_ring_buffer, .-pdma_set_ring_buffer
	.section	.text.pdma_configure,"ax",@progbits
	.align	1
	.globl	pdma_configure
	.hidden	pdma_configure
	.type	pdma_configure, @function
pdma_configure:
.LFB15:
	.loc 1 403 1 is_stmt 1
	.cfi_startproc
.LVL119:
	.loc 1 404 5
	.loc 1 405 5
	.loc 1 407 5
	.loc 1 407 8 is_stmt 0
	li	a3,3
	bgtu	a0,a3,.L145
	mv	a5,a0
	.loc 1 410 5 is_stmt 1
	.loc 1 413 16 is_stmt 0
	li	a0,-1
.LVL120:
	.loc 1 410 8
	beq	a1,zero,.L153
	.loc 1 411 21
	lw	a4,12(a1)
	.loc 1 410 30 discriminator 1
	bgtu	a4,a3,.L153
	.loc 1 412 21
	lw	a3,4(a1)
	.loc 1 411 55
	li	a2,2
	bgtu	a3,a2,.L153
	.loc 1 416 5 is_stmt 1
	.loc 1 417 20 is_stmt 0
	lbu	a0,0(a1)
	.loc 1 403 1
	addi	sp,sp,-4
	.cfi_def_cfa_offset 4
	.loc 1 416 22
	sw	zero,0(sp)
	.loc 1 417 5 is_stmt 1
	.loc 1 417 8 is_stmt 0
	beq	a0,zero,.L138
	.loc 1 418 9 is_stmt 1
	.loc 1 418 26 is_stmt 0
	li	a2,524288
	sw	a2,0(sp)
.L139:
	.loc 1 422 5 is_stmt 1
	li	a2,2
	beq	a4,a2,.L140
	li	a2,3
	beq	a4,a2,.L141
	li	a2,1
	beq	a4,a2,.L142
	.loc 1 424 13
	.loc 1 424 24 is_stmt 0
	lw	a4,0(sp)
	.loc 1 424 30
	ori	a4,a4,1
	sw	a4,0(sp)
	.loc 1 425 13 is_stmt 1
.L143:
	.loc 1 443 5
	.loc 1 443 28 is_stmt 0
	lw	a4,0(sp)
	andi	a2,a3,3
	slli	a2,a2,8
	andi	a4,a4,-769
	or	a4,a4,a2
	sw	a4,0(sp)
	.loc 1 444 5 is_stmt 1
	.loc 1 444 8 is_stmt 0
	beq	a0,zero,.L144
	.loc 1 444 42 discriminator 1
	bne	a3,zero,.L144
	.loc 1 445 9 is_stmt 1
	.loc 1 445 20 is_stmt 0
	lw	a4,0(sp)
	.loc 1 445 26
	li	a3,131072
	or	a4,a4,a3
	sw	a4,0(sp)
.L144:
	.loc 1 447 5 is_stmt 1
	.loc 1 447 16 is_stmt 0
	lw	a4,0(sp)
	.loc 1 447 22
	li	a3,65536
	.loc 1 449 14
	slli	a5,a5,2
.LVL121:
	.loc 1 447 22
	or	a4,a4,a3
	sw	a4,0(sp)
	.loc 1 449 5 is_stmt 1
	.loc 1 449 14 is_stmt 0
	lla	a4,g_pdma_cfg_regbase_table
	add	a5,a4,a5
	lw	a5,0(a5)
.LVL122:
	.loc 1 451 5 is_stmt 1
	.loc 1 451 36 is_stmt 0
	li	a3,-32768
	addi	a3,a3,-1
	lw	a4,20(a5)
	.loc 1 455 12
	li	a0,0
	.loc 1 451 36
	and	a4,a4,a3
	sw	a4,20(a5)
	.loc 1 452 5 is_stmt 1
	.loc 1 452 42 is_stmt 0
	lw	a4,0(sp)
	.loc 1 452 29
	sw	a4,12(a5)
	.loc 1 453 5 is_stmt 1
	.loc 1 453 44 is_stmt 0
	lw	a4,8(a1)
	.loc 1 453 31
	sw	a4,8(a5)
	.loc 1 455 5 is_stmt 1
	.loc 1 456 1 is_stmt 0
	addi	sp,sp,4
	.cfi_remember_state
	.cfi_def_cfa_offset 0
	jr	ra
.LVL123:
.L138:
	.cfi_restore_state
	.loc 1 420 9 is_stmt 1
	.loc 1 420 26 is_stmt 0
	sw	zero,0(sp)
	j	.L139
.L142:
	.loc 1 427 13 is_stmt 1
	.loc 1 427 24 is_stmt 0
	lw	a4,0(sp)
	.loc 1 427 30
	ori	a4,a4,16
	sw	a4,0(sp)
	.loc 1 428 13 is_stmt 1
	.loc 1 428 24 is_stmt 0
	lw	a4,0(sp)
	.loc 1 428 30
	ori	a4,a4,2
.L156:
	.loc 1 438 30
	sw	a4,0(sp)
	.loc 1 439 13 is_stmt 1
	j	.L143
.L140:
	.loc 1 431 13
	.loc 1 431 24 is_stmt 0
	lw	a4,0(sp)
	.loc 1 431 30
	ori	a4,a4,1
.L157:
	.loc 1 437 30
	sw	a4,0(sp)
	.loc 1 438 13 is_stmt 1
	.loc 1 438 24 is_stmt 0
	lw	a4,0(sp)
	.loc 1 438 30
	ori	a4,a4,8
	j	.L156
.L141:
	.loc 1 435 13 is_stmt 1
	.loc 1 435 24 is_stmt 0
	lw	a4,0(sp)
	.loc 1 435 30
	ori	a4,a4,16
	sw	a4,0(sp)
	.loc 1 436 13 is_stmt 1
	.loc 1 436 24 is_stmt 0
	lw	a4,0(sp)
	.loc 1 436 30
	ori	a4,a4,1
	sw	a4,0(sp)
	.loc 1 437 13 is_stmt 1
	.loc 1 437 24 is_stmt 0
	lw	a4,0(sp)
	.loc 1 437 30
	ori	a4,a4,4
	j	.L157
.LVL124:
.L145:
	.cfi_def_cfa_offset 0
	.loc 1 408 16
	li	a0,-2
.LVL125:
	ret
.LVL126:
.L153:
	.loc 1 456 1
	ret
	.cfi_endproc
.LFE15:
	.size	pdma_configure, .-pdma_configure
	.section	.text.pdma_start_interrupt,"ax",@progbits
	.align	1
	.globl	pdma_start_interrupt
	.hidden	pdma_start_interrupt
	.type	pdma_start_interrupt, @function
pdma_start_interrupt:
.LFB17:
	.loc 1 489 1 is_stmt 1
	.cfi_startproc
.LVL127:
	.loc 1 490 5
	.loc 1 492 5
	.loc 1 492 8 is_stmt 0
	li	a4,3
	bgtu	a0,a4,.L160
	.loc 1 495 18
	andi	a4,a1,3
	mv	a5,a0
	.loc 1 495 5 is_stmt 1
	.loc 1 496 16 is_stmt 0
	li	a0,-1
.LVL128:
	.loc 1 495 8
	bne	a4,zero,.L163
	.loc 1 504 5 is_stmt 1
	.loc 1 504 14 is_stmt 0
	lla	a4,g_pdma_cfg_regbase_table
	slli	a5,a5,2
.LVL129:
	.loc 1 489 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 504 14
	add	a5,a4,a5
	.loc 1 489 1
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 504 14
	lw	s0,0(a5)
.LVL130:
	.loc 1 505 5 is_stmt 1
	.loc 1 505 35 is_stmt 0
	mv	a0,a1
	.loc 1 489 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 505 35
	call	hal_memview_riscv_to_infrasys
.LVL131:
	.loc 1 505 33 discriminator 1
	sw	a0,16(s0)
	.loc 1 506 5 is_stmt 1
	.loc 1 506 35 is_stmt 0
	lw	a5,12(s0)
	li	a4,16777216
	.loc 1 509 12
	li	a0,0
	.loc 1 506 35
	or	a5,a5,a4
	sw	a5,12(s0)
	.loc 1 507 5 is_stmt 1
	.loc 1 507 36 is_stmt 0
	lw	a5,20(s0)
	li	a4,32768
	or	a5,a5,a4
	sw	a5,20(s0)
	.loc 1 509 5 is_stmt 1
	.loc 1 510 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL132:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL133:
.L160:
	.loc 1 493 16
	li	a0,-2
.LVL134:
	ret
.LVL135:
.L163:
	.loc 1 510 1
	ret
	.cfi_endproc
.LFE17:
	.size	pdma_start_interrupt, .-pdma_start_interrupt
	.section	.text.pdma_stop,"ax",@progbits
	.align	1
	.globl	pdma_stop
	.hidden	pdma_stop
	.type	pdma_stop, @function
pdma_stop:
.LFB18:
	.loc 1 513 1 is_stmt 1
	.cfi_startproc
.LVL136:
	.loc 1 514 5
	.loc 1 515 5
	.loc 1 517 5
	.loc 1 517 8 is_stmt 0
	li	a5,3
	bgtu	a0,a5,.L168
	.loc 1 521 5 is_stmt 1
	.loc 1 521 16 is_stmt 0
	slli	a0,a0,2
.LVL137:
	lla	a5,g_pdma_status_regbase_table
	add	a5,a5,a0
	lw	a3,0(a5)
.LVL138:
	.loc 1 522 5 is_stmt 1
	.loc 1 522 14 is_stmt 0
	lla	a5,g_pdma_cfg_regbase_table
	add	a5,a5,a0
	lw	a2,0(a5)
.LVL139:
	.loc 1 523 5 is_stmt 1
	.loc 1 523 36 is_stmt 0
	li	a4,-32768
	addi	a4,a4,-1
	lw	a5,20(a2)
	.loc 1 526 12
	li	a0,0
	.loc 1 523 36
	and	a5,a5,a4
	sw	a5,20(a2)
	.loc 1 524 5 is_stmt 1
	.loc 1 524 39 is_stmt 0
	lw	a5,4(a3)
	li	a4,32768
	or	a5,a5,a4
	sw	a5,4(a3)
	.loc 1 526 5 is_stmt 1
	.loc 1 526 12 is_stmt 0
	ret
.LVL140:
.L168:
	.loc 1 518 16
	li	a0,-2
.LVL141:
	.loc 1 527 1
	ret
	.cfi_endproc
.LFE18:
	.size	pdma_stop, .-pdma_stop
	.section	.text.pdma_register_callback,"ax",@progbits
	.align	1
	.globl	pdma_register_callback
	.hidden	pdma_register_callback
	.type	pdma_register_callback, @function
pdma_register_callback:
.LFB19:
	.loc 1 530 1 is_stmt 1
	.cfi_startproc
.LVL142:
	.loc 1 531 5
	.loc 1 531 8 is_stmt 0
	li	a4,3
	bgtu	a0,a4,.L171
	mv	a5,a0
	.loc 1 534 5 is_stmt 1
	.loc 1 535 16 is_stmt 0
	li	a0,-1
.LVL143:
	.loc 1 534 8
	beq	a1,zero,.L174
	.loc 1 538 5 is_stmt 1
	.loc 1 530 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 538 35
	slli	a3,a5,3
	lla	a4,g_pdma_callback
	.loc 1 530 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 538 35
	add	a4,a4,a3
	sw	a1,0(a4)
	.loc 1 539 5 is_stmt 1
	.loc 1 539 39 is_stmt 0
	sw	a2,4(a4)
	.loc 1 541 5 is_stmt 1
	slli	a5,a5,2
.LVL144:
	lla	a4,g_pdma_channel_map_table
	add	a5,a4,a5
	lw	a0,0(a5)
	sw	a0,0(sp)
	call	internal_dma_register_irq_callback
.LVL145:
	.loc 1 542 5
	lw	a0,0(sp)
	call	internal_dma_enable_irq
.LVL146:
	.loc 1 544 5
	.loc 1 545 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	.loc 1 544 12
	li	a0,0
	.loc 1 545 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL147:
.L171:
	.loc 1 532 16
	li	a0,-2
.LVL148:
	ret
.LVL149:
.L174:
	.loc 1 545 1
	ret
	.cfi_endproc
.LFE19:
	.size	pdma_register_callback, .-pdma_register_callback
	.section	.text.pdma_get_running_status,"ax",@progbits
	.align	1
	.globl	pdma_get_running_status
	.hidden	pdma_get_running_status
	.type	pdma_get_running_status, @function
pdma_get_running_status:
.LFB20:
	.loc 1 548 1 is_stmt 1
	.cfi_startproc
.LVL150:
	.loc 1 549 5
	.loc 1 549 8 is_stmt 0
	li	a4,3
	bgtu	a0,a4,.L186
	.loc 1 548 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s1,0(sp)
	sw	ra,8(sp)
	sw	s0,4(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	mv	a5,a0
	mv	s1,a1
	.loc 1 552 5 is_stmt 1
	.loc 1 553 16 is_stmt 0
	li	a0,-1
.LVL151:
	.loc 1 552 8
	beq	a1,zero,.L177
	.loc 1 556 5 is_stmt 1
	.loc 1 556 9 is_stmt 0
	slli	a5,a5,2
.LVL152:
	lla	a4,g_pdma_channel_map_table
	add	a5,a4,a5
	lw	s0,0(a5)
.LVL153:
.LBB28:
.LBB29:
	.loc 1 248 5 is_stmt 1
	.loc 1 250 5
	.loc 1 250 8 is_stmt 0
	li	a5,5
	bgtu	s0,a5,.L179
.L195:
	.loc 1 253 9 is_stmt 1
	.loc 1 253 23 is_stmt 0
	andi	a5,s0,1
.LVL154:
.L180:
	.loc 1 255 275 is_stmt 1 discriminator 3
	.loc 1 258 5
	.loc 1 260 65 is_stmt 0
	srli	a3,s0,1
	.loc 1 260 53
	slli	a3,a3,2
	lla	a4,g_dma_reg_table
	add	a4,a4,a3
	lw	a3,0(a4)
	.loc 1 260 100
	slli	a5,a5,1
	.loc 1 260 94
	li	a4,1
	sll	a5,a4,a5
	.loc 1 258 52
	addi	s0,s0,-6
.LVL155:
	.loc 1 258 7
	li	a4,3
	bgtu	s0,a4,.L182
	.loc 1 260 9 is_stmt 1
	.loc 1 260 82 is_stmt 0
	lw	a4,60(a3)
.L196:
	.loc 1 265 58
	and	a5,a4,a5
	.loc 1 265 12
	beq	a5,zero,.L184
.LVL156:
.LBE29:
.LBE28:
	.loc 1 557 9 is_stmt 1
	.loc 1 557 25 is_stmt 0
	li	a5,1
	sw	a5,0(s1)
.L185:
	.loc 1 562 12
	li	a0,0
.L177:
	.loc 1 563 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	lw	s1,0(sp)
	.cfi_restore 9
.LVL157:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL158:
.L179:
	.cfi_restore_state
.LBB32:
.LBB31:
	.loc 1 252 12 is_stmt 1
	.loc 1 252 15 is_stmt 0
	li	a5,9
	bleu	s0,a5,.L195
	.loc 1 255 9 is_stmt 1
.LBB30:
	.loc 1 255 26 discriminator 1
	.loc 1 255 102 discriminator 1
	.loc 1 255 244 discriminator 1
	li	a2,255
	lla	a1,file.8
	lla	a0,exp.9
	call	light_assert
.LVL159:
.LBE30:
	.loc 1 248 14 is_stmt 0
	li	a5,0
	j	.L180
.LVL160:
.L182:
	.loc 1 265 9 is_stmt 1
	.loc 1 265 44 is_stmt 0
	lw	a4,0(a3)
	j	.L196
.L184:
.LVL161:
.LBE31:
.LBE32:
	.loc 1 559 9 is_stmt 1
	.loc 1 559 25 is_stmt 0
	sw	zero,0(s1)
	j	.L185
.LVL162:
.L186:
	.cfi_def_cfa_offset 0
	.cfi_restore 1
	.cfi_restore 8
	.cfi_restore 9
	.loc 1 550 16
	li	a0,-2
.LVL163:
	.loc 1 563 1
	ret
	.cfi_endproc
.LFE20:
	.size	pdma_get_running_status, .-pdma_get_running_status
	.section	.text.pdma_start_polling,"ax",@progbits
	.align	1
	.globl	pdma_start_polling
	.hidden	pdma_start_polling
	.type	pdma_start_polling, @function
pdma_start_polling:
.LFB16:
	.loc 1 459 1 is_stmt 1
	.cfi_startproc
.LVL164:
	.loc 1 460 5
	.loc 1 461 5
	.loc 1 463 5
	.loc 1 463 8 is_stmt 0
	li	a5,3
	bgtu	a0,a5,.L200
	.loc 1 459 1
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	ra,12(sp)
	sw	s1,4(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 466 18
	andi	a5,a1,3
	mv	s0,a0
	.loc 1 466 5 is_stmt 1
	.loc 1 467 16 is_stmt 0
	li	a0,-1
.LVL165:
	.loc 1 466 8
	bne	a5,zero,.L197
	.loc 1 475 5 is_stmt 1
	.loc 1 475 14 is_stmt 0
	slli	a4,s0,2
	lla	a5,g_pdma_cfg_regbase_table
	add	a5,a5,a4
	lw	s1,0(a5)
.LVL166:
	.loc 1 476 5 is_stmt 1
	.loc 1 476 35 is_stmt 0
	mv	a0,a1
	call	hal_memview_riscv_to_infrasys
.LVL167:
	.loc 1 476 33 discriminator 1
	sw	a0,16(s1)
	.loc 1 477 5 is_stmt 1
	.loc 1 477 35 is_stmt 0
	lw	a5,12(s1)
	li	a4,-16777216
	addi	a4,a4,-1
	and	a5,a5,a4
	sw	a5,12(s1)
	.loc 1 478 5 is_stmt 1
	.loc 1 478 36 is_stmt 0
	lw	a5,20(s1)
	li	a4,32768
	or	a5,a5,a4
	sw	a5,20(s1)
.L199:
	.loc 1 480 5 is_stmt 1
	.loc 1 481 9
	mv	a1,sp
	mv	a0,s0
	call	pdma_get_running_status
.LVL168:
	.loc 1 482 14 discriminator 1
	lw	a5,0(sp)
	bne	a5,zero,.L199
	.loc 1 483 5
	mv	a0,s0
	call	pdma_stop
.LVL169:
	.loc 1 485 5
	.loc 1 485 12 is_stmt 0
	li	a0,0
.LVL170:
.L197:
	.loc 1 486 1
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL171:
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL172:
.L200:
	.loc 1 464 16
	li	a0,-2
.LVL173:
	.loc 1 486 1
	ret
	.cfi_endproc
.LFE16:
	.size	pdma_start_polling, .-pdma_start_polling
	.section	.text.pdma_dump_reg_list,"ax",@progbits
	.align	1
	.globl	pdma_dump_reg_list
	.hidden	pdma_dump_reg_list
	.type	pdma_dump_reg_list, @function
pdma_dump_reg_list:
.LFB21:
	.loc 1 566 1 is_stmt 1
	.cfi_startproc
.LVL174:
	.loc 1 567 5
	.loc 1 568 5
	.loc 1 570 5
	.loc 1 570 8 is_stmt 0
	li	a5,3
	bleu	a0,a5,.L209
	.loc 1 571 16
	li	a0,-2
.LVL175:
	ret
.LVL176:
.L209:
	.loc 1 589 12
	li	a0,0
.LVL177:
	.loc 1 590 1
	ret
	.cfi_endproc
.LFE21:
	.size	pdma_dump_reg_list, .-pdma_dump_reg_list
	.section	.text.internal_vdma_clock_control,"ax",@progbits
	.align	1
	.globl	internal_vdma_clock_control
	.hidden	internal_vdma_clock_control
	.type	internal_vdma_clock_control, @function
internal_vdma_clock_control:
.LFB22:
	.loc 1 642 1 is_stmt 1
	.cfi_startproc
.LVL178:
	.loc 1 643 5
	.loc 1 642 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 643 8
	li	a5,5
	.loc 1 642 1
	mv	s0,a0
	mv	s1,a1
	.loc 1 643 8
	bleu	a0,a5,.L211
	.loc 1 644 9 is_stmt 1
.LBB33:
	.loc 1 644 26 discriminator 1
	.loc 1 644 102 discriminator 1
	.loc 1 644 244 discriminator 1
	li	a2,644
	lla	a1,file.6
.LVL179:
	lla	a0,exp.7
.LVL180:
	call	light_assert
.LVL181:
.L211:
.LBE33:
	.loc 1 644 275 discriminator 3
	.loc 1 647 5
	.loc 1 648 9 is_stmt 0
	slli	s0,s0,2
.LVL182:
	lla	a5,g_vdma_channel_map_table
	add	a5,a5,s0
	lw	a0,0(a5)
	.loc 1 647 8
	beq	s1,zero,.L212
	.loc 1 648 9 is_stmt 1
	.loc 1 652 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
.LVL183:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 648 9
	tail	internal_dma_enable_clock
.LVL184:
.L212:
	.cfi_restore_state
	.loc 1 650 9 is_stmt 1
	.loc 1 652 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 650 9
	tail	internal_dma_disable_clock
.LVL185:
	.cfi_endproc
.LFE22:
	.size	internal_vdma_clock_control, .-internal_vdma_clock_control
	.section	.text.internal_vdma_irq_control,"ax",@progbits
	.align	1
	.globl	internal_vdma_irq_control
	.hidden	internal_vdma_irq_control
	.type	internal_vdma_irq_control, @function
internal_vdma_irq_control:
.LFB23:
	.loc 1 660 1 is_stmt 1
	.cfi_startproc
.LVL186:
	.loc 1 661 5
	.loc 1 660 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 661 8
	li	a5,5
	.loc 1 660 1
	mv	s0,a0
	mv	s1,a1
	.loc 1 661 8
	bleu	a0,a5,.L215
	.loc 1 662 9 is_stmt 1
.LBB34:
	.loc 1 662 26 discriminator 1
	.loc 1 662 102 discriminator 1
	.loc 1 662 244 discriminator 1
	li	a2,662
	lla	a1,file.4
.LVL187:
	lla	a0,exp.5
.LVL188:
	call	light_assert
.LVL189:
.L215:
.LBE34:
	.loc 1 662 275 discriminator 3
	.loc 1 665 5
	.loc 1 666 9 is_stmt 0
	slli	s0,s0,2
.LVL190:
	lla	a5,g_vdma_channel_map_table
	add	a5,a5,s0
	lw	a0,0(a5)
	.loc 1 665 8
	beq	s1,zero,.L216
	.loc 1 666 9 is_stmt 1
	.loc 1 670 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
.LVL191:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 666 9
	tail	internal_dma_enable_irq
.LVL192:
.L216:
	.cfi_restore_state
	.loc 1 668 9 is_stmt 1
	.loc 1 670 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 668 9
	tail	internal_dma_disable_irq
.LVL193:
	.cfi_endproc
.LFE23:
	.size	internal_vdma_irq_control, .-internal_vdma_irq_control
	.section	.text.vdma_init,"ax",@progbits
	.align	1
	.globl	vdma_init
	.hidden	vdma_init
	.type	vdma_init, @function
vdma_init:
.LFB25:
	.loc 1 689 1 is_stmt 1
	.cfi_startproc
.LVL194:
	.loc 1 690 5
	.loc 1 691 5
	.loc 1 693 5
	.loc 1 693 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L223
	.loc 1 689 1
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	.loc 1 697 5 is_stmt 1
	addi	a0,sp,4
.LVL195:
	.loc 1 689 1 is_stmt 0
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 697 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL196:
	.loc 1 698 5 is_stmt 1
	.loc 1 698 27 is_stmt 0
	lla	a5,g_vdma_init_status
	add	a5,a5,s0
	lbu	a4,0(a5)
	.loc 1 698 8
	li	s1,1
	lw	a0,4(sp)
	bne	a4,s1,.L220
	.loc 1 699 9 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL197:
	.loc 1 700 9
	.loc 1 700 16 is_stmt 0
	li	a0,-3
.L218:
	.loc 1 729 1
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
.LVL198:
	lw	s1,8(sp)
	.cfi_restore 9
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL199:
.L220:
	.cfi_restore_state
	.loc 1 702 5 is_stmt 1
	.loc 1 702 33 is_stmt 0
	sb	s1,0(a5)
	.loc 1 703 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL200:
	.loc 1 705 5
	slli	a4,s0,2
	lla	a5,g_vdma_channel_map_table
	add	a5,a5,a4
	lw	a0,0(a5)
	sw	a4,0(sp)
	call	internal_dma_enable_clock
.LVL201:
	.loc 1 707 5
	mv	a0,s0
	call	internal_vdma_restore_default_value
.LVL202:
	.loc 1 709 5
	.loc 1 709 10 is_stmt 0
	lw	a4,0(sp)
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a4
	.loc 1 710 5
	li	a4,42
	srl	a4,a4,s0
	andi	a4,a4,1
	.loc 1 709 10
	lw	a5,0(a5)
.LVL203:
	.loc 1 710 5 is_stmt 1
	bne	a4,zero,.L221
.L228:
	.loc 1 714 13
	.loc 1 714 62 is_stmt 0
	sb	s1,6(a5)
	.loc 1 715 13 is_stmt 1
	.loc 1 715 59 is_stmt 0
	sb	zero,5(a5)
	.loc 1 716 13 is_stmt 1
	.loc 1 728 12 is_stmt 0
	li	a0,0
	j	.L218
.L221:
	.loc 1 720 13 is_stmt 1
	.loc 1 720 64 is_stmt 0
	li	a4,16
	sb	a4,4(a5)
	.loc 1 721 13 is_stmt 1
	j	.L228
.LVL204:
.L223:
	.cfi_def_cfa_offset 0
	.cfi_restore 1
	.cfi_restore 8
	.cfi_restore 9
	.loc 1 694 16 is_stmt 0
	li	a0,-2
.LVL205:
	.loc 1 729 1
	ret
	.cfi_endproc
.LFE25:
	.size	vdma_init, .-vdma_init
	.section	.text.vdma_deinit,"ax",@progbits
	.align	1
	.globl	vdma_deinit
	.hidden	vdma_deinit
	.type	vdma_deinit, @function
vdma_deinit:
.LFB26:
	.loc 1 732 1 is_stmt 1
	.cfi_startproc
.LVL206:
	.loc 1 733 5
	.loc 1 735 5
	.loc 1 735 8 is_stmt 0
	li	a4,5
	bgtu	a0,a4,.L234
	.loc 1 732 1
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	sw	s1,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 740 27
	lla	s0,g_vdma_init_status
	mv	s1,a0
	.loc 1 739 5 is_stmt 1
	addi	a0,sp,4
.LVL207:
	.loc 1 732 1 is_stmt 0
	sw	ra,16(sp)
	.cfi_offset 1, -4
	.loc 1 740 27
	add	s0,s0,s1
	.loc 1 739 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL208:
	.loc 1 740 5 is_stmt 1
	.loc 1 740 27 is_stmt 0
	lbu	a4,0(s0)
	.loc 1 740 8
	bne	a4,zero,.L231
	.loc 1 741 9 is_stmt 1
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL209:
	.loc 1 742 9
.L232:
	.loc 1 742 16 is_stmt 0
	li	a0,-3
.L229:
	.loc 1 757 1
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
.LVL210:
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL211:
.L231:
	.cfi_restore_state
	.loc 1 745 5 is_stmt 1
	.loc 1 745 9 is_stmt 0
	slli	a3,s1,2
	lla	a4,g_vdma_channel_map_table
	add	a4,a4,a3
	lw	a5,0(a4)
	mv	a0,a5
	sw	a5,0(sp)
	call	internal_dma_check_idle_status
.LVL212:
	.loc 1 745 8 discriminator 1
	beq	a0,zero,.L232
	.loc 1 749 5 is_stmt 1
	mv	a0,s1
	call	internal_vdma_restore_default_value
.LVL213:
	.loc 1 750 5
	lw	a0,0(sp)
	call	internal_dma_disable_irq
.LVL214:
	.loc 1 751 5
	lw	a0,0(sp)
	call	internal_dma_disable_clock
.LVL215:
	.loc 1 753 5
	.loc 1 754 5 is_stmt 0
	lw	a0,4(sp)
	.loc 1 753 33
	sb	zero,0(s0)
	.loc 1 754 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL216:
	.loc 1 756 5
	.loc 1 756 12 is_stmt 0
	li	a0,0
	j	.L229
.LVL217:
.L234:
	.cfi_def_cfa_offset 0
	.cfi_restore 1
	.cfi_restore 8
	.cfi_restore 9
	.loc 1 736 16
	li	a0,-2
.LVL218:
	.loc 1 757 1
	ret
	.cfi_endproc
.LFE26:
	.size	vdma_deinit, .-vdma_deinit
	.section	.text.vdma_start,"ax",@progbits
	.align	1
	.globl	vdma_start
	.hidden	vdma_start
	.type	vdma_start, @function
vdma_start:
.LFB27:
	.loc 1 760 1 is_stmt 1
	.cfi_startproc
.LVL219:
	.loc 1 761 5
	.loc 1 763 5
	.loc 1 763 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L241
	.loc 1 767 5 is_stmt 1
	.loc 1 760 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.loc 1 767 5
	lla	a5,g_vdma_channel_map_table
	.cfi_offset 8, -8
	slli	s0,a0,2
	add	a5,a5,s0
	lw	a0,0(a5)
.LVL220:
	.loc 1 760 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 767 5
	call	internal_dma_check_idle_status
.LVL221:
	.loc 1 769 5 is_stmt 1
	.loc 1 769 10 is_stmt 0
	lla	a5,g_vdma_regbase_table
	add	a5,a5,s0
	lw	a5,0(a5)
.LVL222:
	.loc 1 770 5 is_stmt 1
	.loc 1 773 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	.loc 1 770 22
	li	a4,32768
	sw	a4,8(a5)
	.loc 1 772 5 is_stmt 1
	.loc 1 772 12 is_stmt 0
	li	a0,0
	.loc 1 773 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL223:
.L241:
	.loc 1 764 16
	li	a0,-2
.LVL224:
	.loc 1 773 1
	ret
	.cfi_endproc
.LFE27:
	.size	vdma_start, .-vdma_start
	.section	.text.vdma_stop,"ax",@progbits
	.align	1
	.globl	vdma_stop
	.hidden	vdma_stop
	.type	vdma_stop, @function
vdma_stop:
.LFB28:
	.loc 1 776 1 is_stmt 1
	.cfi_startproc
.LVL225:
	.loc 1 777 5
	.loc 1 779 5
	.loc 1 779 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L248
	.loc 1 783 5 is_stmt 1
	.loc 1 783 10 is_stmt 0
	slli	a0,a0,2
.LVL226:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a0
	lw	a5,0(a5)
.LVL227:
	.loc 1 784 5 is_stmt 1
	.loc 1 787 12 is_stmt 0
	li	a0,0
	.loc 1 784 22
	sw	zero,8(a5)
	.loc 1 785 5 is_stmt 1
	.loc 1 785 33 is_stmt 0
	lw	a4,40(a5)
	.loc 1 785 84
	lbu	a3,5(a5)
	.loc 1 785 46
	sll	a4,a4,a3
	.loc 1 785 27
	sw	a4,80(a5)
	.loc 1 787 5 is_stmt 1
	.loc 1 787 12 is_stmt 0
	ret
.LVL228:
.L248:
	.loc 1 780 16
	li	a0,-2
.LVL229:
	.loc 1 788 1
	ret
	.cfi_endproc
.LFE28:
	.size	vdma_stop, .-vdma_stop
	.section	.text.vdma_configure,"ax",@progbits
	.align	1
	.globl	vdma_configure
	.hidden	vdma_configure
	.type	vdma_configure, @function
vdma_configure:
.LFB29:
	.loc 1 791 1 is_stmt 1
	.cfi_startproc
.LVL230:
	.loc 1 792 5
	.loc 1 793 5
	.loc 1 795 5
	.loc 1 795 8 is_stmt 0
	beq	a1,zero,.L251
	.loc 1 799 8
	li	a3,5
	mv	a5,a0
	.loc 1 799 5 is_stmt 1
	.loc 1 800 16 is_stmt 0
	li	a4,-2
	.loc 1 799 8
	bgtu	a0,a3,.L255
	.loc 1 803 5 is_stmt 1
	.loc 1 803 18 is_stmt 0
	lw	a0,0(a1)
.LVL231:
	.loc 1 804 5 is_stmt 1
	.loc 1 796 16 is_stmt 0
	li	a4,-1
	.loc 1 804 23
	andi	a3,a0,3
	.loc 1 804 8
	bne	a3,zero,.L255
	.loc 1 814 5 is_stmt 1
	.loc 1 814 10 is_stmt 0
	lla	a4,g_vdma_regbase_table
	slli	a5,a5,2
.LVL232:
	.loc 1 791 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 814 10
	add	a5,a4,a5
	.loc 1 791 1
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 814 10
	lw	s0,0(a5)
.LVL233:
	.loc 1 815 5 is_stmt 1
	.loc 1 815 36 is_stmt 0
	lw	a5,4(a1)
	.loc 1 791 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 815 23
	sw	a5,52(s0)
	.loc 1 816 5 is_stmt 1
	.loc 1 816 26 is_stmt 0
	call	hal_memview_riscv_to_infrasys
.LVL234:
	.loc 1 816 24 discriminator 1
	sw	a0,28(s0)
	.loc 1 818 5 is_stmt 1
	.loc 1 819 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL235:
	.loc 1 818 12
	li	a4,0
	.loc 1 819 1
	mv	a0,a4
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL236:
.L251:
	.loc 1 796 16
	li	a4,-1
.LVL237:
.L255:
	.loc 1 819 1
	mv	a0,a4
	ret
	.cfi_endproc
.LFE29:
	.size	vdma_configure, .-vdma_configure
	.section	.text.vdma_enable_interrupt,"ax",@progbits
	.align	1
	.globl	vdma_enable_interrupt
	.hidden	vdma_enable_interrupt
	.type	vdma_enable_interrupt, @function
vdma_enable_interrupt:
.LFB30:
	.loc 1 822 1 is_stmt 1
	.cfi_startproc
.LVL238:
	.loc 1 823 5
	.loc 1 825 5
	.loc 1 825 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L260
	.loc 1 829 5 is_stmt 1
	.loc 1 829 10 is_stmt 0
	slli	a0,a0,2
.LVL239:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a0
	lw	a5,0(a5)
.LVL240:
	.loc 1 830 5 is_stmt 1
	.loc 1 830 51 is_stmt 0
	li	a4,1
	.loc 1 832 12
	li	a0,0
	.loc 1 830 51
	sb	a4,7(a5)
	.loc 1 832 5 is_stmt 1
	.loc 1 832 12 is_stmt 0
	ret
.LVL241:
.L260:
	.loc 1 826 16
	li	a0,-2
.LVL242:
	.loc 1 833 1
	ret
	.cfi_endproc
.LFE30:
	.size	vdma_enable_interrupt, .-vdma_enable_interrupt
	.section	.text.vdma_disable_interrupt,"ax",@progbits
	.align	1
	.globl	vdma_disable_interrupt
	.hidden	vdma_disable_interrupt
	.type	vdma_disable_interrupt, @function
vdma_disable_interrupt:
.LFB31:
	.loc 1 836 1 is_stmt 1
	.cfi_startproc
.LVL243:
	.loc 1 837 5
	.loc 1 839 5
	.loc 1 839 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L263
	.loc 1 843 5 is_stmt 1
	.loc 1 843 10 is_stmt 0
	slli	a0,a0,2
.LVL244:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a0
	lw	a5,0(a5)
.LVL245:
	.loc 1 844 5 is_stmt 1
	.loc 1 846 12 is_stmt 0
	li	a0,0
	.loc 1 844 51
	sb	zero,7(a5)
	.loc 1 846 5 is_stmt 1
	.loc 1 846 12 is_stmt 0
	ret
.LVL246:
.L263:
	.loc 1 840 16
	li	a0,-2
.LVL247:
	.loc 1 847 1
	ret
	.cfi_endproc
.LFE31:
	.size	vdma_disable_interrupt, .-vdma_disable_interrupt
	.section	.text.vdma_get_interrupt_status,"ax",@progbits
	.align	1
	.globl	vdma_get_interrupt_status
	.hidden	vdma_get_interrupt_status
	.type	vdma_get_interrupt_status, @function
vdma_get_interrupt_status:
.LFB32:
	.loc 1 850 1 is_stmt 1
	.cfi_startproc
.LVL248:
	.loc 1 851 5
	.loc 1 853 5
	.loc 1 853 8 is_stmt 0
	li	a4,5
	.loc 1 850 1
	mv	a5,a0
	.loc 1 853 8
	bgtu	a0,a4,.L266
	.loc 1 856 5 is_stmt 1
	.loc 1 857 16 is_stmt 0
	li	a0,-1
.LVL249:
	.loc 1 856 8
	beq	a1,zero,.L264
	.loc 1 860 5 is_stmt 1
	.loc 1 860 10 is_stmt 0
	lla	a4,g_vdma_regbase_table
	slli	a5,a5,2
.LVL250:
	add	a5,a4,a5
	lw	a5,0(a5)
.LVL251:
	.loc 1 861 5 is_stmt 1
	.loc 1 863 12 is_stmt 0
	li	a0,0
	.loc 1 861 54
	lbu	a5,7(a5)
.LVL252:
	.loc 1 861 65
	andi	a5,a5,1
	.loc 1 861 17
	sb	a5,0(a1)
.LVL253:
	.loc 1 863 5 is_stmt 1
	.loc 1 863 12 is_stmt 0
	ret
.LVL254:
.L266:
	.loc 1 854 16
	li	a0,-2
.LVL255:
.L264:
	.loc 1 864 1
	ret
	.cfi_endproc
.LFE32:
	.size	vdma_get_interrupt_status, .-vdma_get_interrupt_status
	.section	.text.vdma_set_threshold,"ax",@progbits
	.align	1
	.globl	vdma_set_threshold
	.hidden	vdma_set_threshold
	.type	vdma_set_threshold, @function
vdma_set_threshold:
.LFB33:
	.loc 1 867 1 is_stmt 1
	.cfi_startproc
.LVL256:
	.loc 1 868 5
	.loc 1 869 5
	.loc 1 871 5
	.loc 1 871 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L270
	.loc 1 875 5 is_stmt 1
	.loc 1 875 10 is_stmt 0
	slli	a0,a0,2
.LVL257:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a0
	lw	a5,0(a5)
.LVL258:
	.loc 1 876 5 is_stmt 1
	.loc 1 879 16 is_stmt 0
	li	a0,-1
	.loc 1 876 12
	lbu	a4,5(a5)
.LVL259:
	.loc 1 877 5 is_stmt 1
	.loc 1 877 15 is_stmt 0
	srl	a1,a1,a4
.LVL260:
	.loc 1 878 5 is_stmt 1
	.loc 1 878 8 is_stmt 0
	li	a4,65536
.LVL261:
	bgeu	a1,a4,.L268
	.loc 1 881 5 is_stmt 1
	.loc 1 881 22 is_stmt 0
	sw	a1,0(a5)
	.loc 1 883 5 is_stmt 1
	.loc 1 883 12 is_stmt 0
	li	a0,0
	ret
.LVL262:
.L270:
	.loc 1 872 16
	li	a0,-2
.LVL263:
.L268:
	.loc 1 884 1
	ret
	.cfi_endproc
.LFE33:
	.size	vdma_set_threshold, .-vdma_set_threshold
	.section	.text.vdma_set_alert_length,"ax",@progbits
	.align	1
	.globl	vdma_set_alert_length
	.hidden	vdma_set_alert_length
	.type	vdma_set_alert_length, @function
vdma_set_alert_length:
.LFB34:
	.loc 1 887 1 is_stmt 1
	.cfi_startproc
.LVL264:
	.loc 1 888 5
	.loc 1 889 5
	.loc 1 891 5
	.loc 1 891 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L274
	.loc 1 895 5 is_stmt 1
	.loc 1 895 10 is_stmt 0
	slli	a0,a0,2
.LVL265:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a0
	lw	a5,0(a5)
.LVL266:
	.loc 1 896 5 is_stmt 1
	.loc 1 899 16 is_stmt 0
	li	a0,-1
	.loc 1 896 12
	lbu	a4,5(a5)
.LVL267:
	.loc 1 897 5 is_stmt 1
	.loc 1 897 18 is_stmt 0
	srl	a1,a1,a4
.LVL268:
	.loc 1 898 5 is_stmt 1
	.loc 1 898 8 is_stmt 0
	li	a4,63
.LVL269:
	bgtu	a1,a4,.L272
	.loc 1 901 5 is_stmt 1
	.loc 1 901 23 is_stmt 0
	sw	a1,48(a5)
	.loc 1 903 5 is_stmt 1
	.loc 1 903 12 is_stmt 0
	li	a0,0
	ret
.LVL270:
.L274:
	.loc 1 892 16
	li	a0,-2
.LVL271:
.L272:
	.loc 1 904 1
	ret
	.cfi_endproc
.LFE34:
	.size	vdma_set_alert_length, .-vdma_set_alert_length
	.section	.text.vdma_get_available_receive_bytes,"ax",@progbits
	.align	1
	.globl	vdma_get_available_receive_bytes
	.hidden	vdma_get_available_receive_bytes
	.type	vdma_get_available_receive_bytes, @function
vdma_get_available_receive_bytes:
.LFB41:
	.loc 1 1062 1 is_stmt 1
	.cfi_startproc
.LVL272:
	.loc 1 1063 5
	.loc 1 1064 5
	.loc 1 1066 5
	.loc 1 1066 8 is_stmt 0
	li	a4,5
	.loc 1 1062 1
	mv	a5,a0
	.loc 1 1066 8
	bgtu	a0,a4,.L278
	.loc 1 1069 5 is_stmt 1
	.loc 1 1070 16 is_stmt 0
	li	a0,-1
.LVL273:
	.loc 1 1069 8
	beq	a1,zero,.L276
	.loc 1 1073 5 is_stmt 1
	.loc 1 1073 10 is_stmt 0
	lla	a4,g_vdma_regbase_table
	slli	a5,a5,2
.LVL274:
	add	a5,a4,a5
	lw	a5,0(a5)
.LVL275:
	.loc 1 1074 5 is_stmt 1
	.loc 1 1077 12 is_stmt 0
	li	a0,0
	.loc 1 1074 12
	lbu	a4,5(a5)
.LVL276:
	.loc 1 1075 5 is_stmt 1
	.loc 1 1075 27 is_stmt 0
	lw	a5,40(a5)
.LVL277:
	.loc 1 1075 40
	sll	a5,a5,a4
	.loc 1 1075 20
	sw	a5,0(a1)
	.loc 1 1077 5 is_stmt 1
	.loc 1 1077 12 is_stmt 0
	ret
.LVL278:
.L278:
	.loc 1 1067 16
	li	a0,-2
.LVL279:
.L276:
	.loc 1 1078 1
	ret
	.cfi_endproc
.LFE41:
	.size	vdma_get_available_receive_bytes, .-vdma_get_available_receive_bytes
	.section	.text.vdma_get_available_send_space,"ax",@progbits
	.align	1
	.globl	vdma_get_available_send_space
	.hidden	vdma_get_available_send_space
	.type	vdma_get_available_send_space, @function
vdma_get_available_send_space:
.LFB42:
	.loc 1 1081 1 is_stmt 1
	.cfi_startproc
.LVL280:
	.loc 1 1082 5
	.loc 1 1084 5
	.loc 1 1084 8 is_stmt 0
	li	a4,5
	.loc 1 1081 1
	mv	a5,a0
	.loc 1 1084 8
	bgtu	a0,a4,.L282
	.loc 1 1087 5 is_stmt 1
	.loc 1 1088 16 is_stmt 0
	li	a0,-1
.LVL281:
	.loc 1 1087 8
	beq	a1,zero,.L280
	.loc 1 1091 5 is_stmt 1
	.loc 1 1091 10 is_stmt 0
	lla	a4,g_vdma_regbase_table
	slli	a5,a5,2
.LVL282:
	add	a5,a4,a5
	lw	a5,0(a5)
.LVL283:
	.loc 1 1092 5 is_stmt 1
	.loc 1 1094 12 is_stmt 0
	li	a0,0
	.loc 1 1092 28
	lw	a5,92(a5)
.LVL284:
	.loc 1 1092 22
	sw	a5,0(a1)
	.loc 1 1094 5 is_stmt 1
	.loc 1 1094 12 is_stmt 0
	ret
.LVL285:
.L282:
	.loc 1 1085 16
	li	a0,-2
.LVL286:
.L280:
	.loc 1 1095 1
	ret
	.cfi_endproc
.LFE42:
	.size	vdma_get_available_send_space, .-vdma_get_available_send_space
	.section	.tcm_code."/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c".1097,"ax",@progbits
	.align	1
	.globl	vdma_get_hw_read_point
	.hidden	vdma_get_hw_read_point
	.type	vdma_get_hw_read_point, @function
vdma_get_hw_read_point:
.LFB43:
	.loc 1 1098 1 is_stmt 1
	.cfi_startproc
.LVL287:
	.loc 1 1099 5
	.loc 1 1101 5
	.loc 1 1101 8 is_stmt 0
	li	a4,5
	.loc 1 1098 1
	mv	a5,a0
	.loc 1 1101 8
	bgtu	a0,a4,.L286
	.loc 1 1104 5 is_stmt 1
	.loc 1 1105 16 is_stmt 0
	li	a0,-1
.LVL288:
	.loc 1 1104 8
	beq	a1,zero,.L284
	.loc 1 1108 5 is_stmt 1
	.loc 1 1108 10 is_stmt 0
	lla	a4,g_vdma_regbase_table
	slli	a5,a5,2
.LVL289:
	add	a5,a4,a5
	lw	a5,0(a5)
.LVL290:
	.loc 1 1109 5 is_stmt 1
	.loc 1 1111 12 is_stmt 0
	li	a0,0
	.loc 1 1109 23
	lw	a5,36(a5)
.LVL291:
	.loc 1 1109 17
	sw	a5,0(a1)
	.loc 1 1111 5 is_stmt 1
	.loc 1 1111 12 is_stmt 0
	ret
.LVL292:
.L286:
	.loc 1 1102 16
	li	a0,-2
.LVL293:
.L284:
	.loc 1 1112 1
	ret
	.cfi_endproc
.LFE43:
	.size	vdma_get_hw_read_point, .-vdma_get_hw_read_point
	.section	.tcm_code."/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c".1115,"ax",@progbits
	.align	1
	.globl	vdma_get_hw_read_offset
	.hidden	vdma_get_hw_read_offset
	.type	vdma_get_hw_read_offset, @function
vdma_get_hw_read_offset:
.LFB44:
	.loc 1 1116 1 is_stmt 1
	.cfi_startproc
.LVL294:
	.loc 1 1117 5
	.loc 1 1119 5
	.loc 1 1119 8 is_stmt 0
	li	a4,5
	.loc 1 1116 1
	mv	a5,a0
	.loc 1 1119 8
	bgtu	a0,a4,.L290
	.loc 1 1123 5 is_stmt 1
	.loc 1 1124 16 is_stmt 0
	li	a0,-1
.LVL295:
	.loc 1 1123 8
	beq	a1,zero,.L288
	.loc 1 1127 5 is_stmt 1
	.loc 1 1127 10 is_stmt 0
	lla	a4,g_vdma_regbase_table
	slli	a5,a5,2
.LVL296:
	add	a5,a4,a5
	lw	a4,0(a5)
.LVL297:
	.loc 1 1128 5 is_stmt 1
	.loc 1 1130 12 is_stmt 0
	li	a0,0
	.loc 1 1128 24
	lw	a5,36(a4)
	.loc 1 1128 43
	lw	a4,28(a4)
.LVL298:
	.loc 1 1128 37
	sub	a5,a5,a4
	.loc 1 1128 18
	sw	a5,0(a1)
	.loc 1 1130 5 is_stmt 1
	.loc 1 1130 12 is_stmt 0
	ret
.LVL299:
.L290:
	.loc 1 1120 16
	li	a0,-2
.LVL300:
.L288:
	.loc 1 1131 1
	ret
	.cfi_endproc
.LFE44:
	.size	vdma_get_hw_read_offset, .-vdma_get_hw_read_offset
	.section	.text.vdma_set_sw_move_byte,"ax",@progbits
	.align	1
	.globl	vdma_set_sw_move_byte
	.hidden	vdma_set_sw_move_byte
	.type	vdma_set_sw_move_byte, @function
vdma_set_sw_move_byte:
.LFB45:
	.loc 1 1134 1 is_stmt 1
	.cfi_startproc
.LVL301:
	.loc 1 1135 5
	.loc 1 1136 5
	.loc 1 1138 5
	.loc 1 1138 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L295
	.loc 1 1142 5 is_stmt 1
	.loc 1 1142 10 is_stmt 0
	slli	a0,a0,2
.LVL302:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a0
	lw	a4,0(a5)
.LVL303:
	.loc 1 1143 5 is_stmt 1
	.loc 1 1144 5 is_stmt 0
	li	a2,2
	.loc 1 1143 12
	lbu	a5,5(a4)
	andi	a3,a5,0xff
.LVL304:
	.loc 1 1144 5 is_stmt 1
	bne	a5,a2,.L294
	.loc 1 1146 13
	.loc 1 1146 16 is_stmt 0
	andi	a5,a1,3
	.loc 1 1147 24
	li	a0,-1
	.loc 1 1146 16
	bne	a5,zero,.L292
.L294:
	.loc 1 1154 5 is_stmt 1
	.loc 1 1154 43 is_stmt 0
	sra	a1,a1,a3
.LVL305:
	.loc 1 1154 27
	sw	a1,80(a4)
	.loc 1 1156 5 is_stmt 1
	.loc 1 1156 12 is_stmt 0
	li	a0,0
	ret
.LVL306:
.L295:
	.loc 1 1139 16
	li	a0,-2
.LVL307:
.L292:
	.loc 1 1157 1
	ret
	.cfi_endproc
.LFE45:
	.size	vdma_set_sw_move_byte, .-vdma_set_sw_move_byte
	.section	.text.vdma_push_data,"ax",@progbits
	.align	1
	.globl	vdma_push_data
	.hidden	vdma_push_data
	.type	vdma_push_data, @function
vdma_push_data:
.LFB35:
	.loc 1 907 1 is_stmt 1
	.cfi_startproc
.LVL308:
	.loc 1 908 5
	.loc 1 909 5
	.loc 1 911 5
	.loc 1 911 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L299
	.loc 1 915 10
	slli	a4,a0,2
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a4
	lw	a5,0(a5)
	.loc 1 907 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	.loc 1 916 36
	lw	a0,32(a5)
.LVL309:
	.loc 1 907 1
	sw	ra,8(sp)
	sw	s1,0(sp)
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	mv	s1,a1
	.loc 1 915 5 is_stmt 1
.LVL310:
	.loc 1 916 5
	.loc 1 917 5
	.loc 1 917 32 is_stmt 0
	call	hal_memview_infrasys_to_riscv
.LVL311:
	.loc 1 918 5 is_stmt 1
	.loc 1 918 20 is_stmt 0
	sb	s1,0(a0)
	.loc 1 920 5 is_stmt 1
	li	a1,1
	mv	a0,s0
.LVL312:
	call	vdma_set_sw_move_byte
.LVL313:
	.loc 1 922 5
	.loc 1 923 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL314:
	lw	s1,0(sp)
	.cfi_restore 9
.LVL315:
	.loc 1 922 12
	li	a0,0
	.loc 1 923 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL316:
.L299:
	.loc 1 912 16
	li	a0,-2
.LVL317:
	.loc 1 923 1
	ret
	.cfi_endproc
.LFE35:
	.size	vdma_push_data, .-vdma_push_data
	.section	.text.vdma_push_data_4bytes,"ax",@progbits
	.align	1
	.globl	vdma_push_data_4bytes
	.hidden	vdma_push_data_4bytes
	.type	vdma_push_data_4bytes, @function
vdma_push_data_4bytes:
.LFB36:
	.loc 1 926 1 is_stmt 1
	.cfi_startproc
.LVL318:
	.loc 1 927 5
	.loc 1 928 5
	.loc 1 930 5
	.loc 1 930 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L306
	.loc 1 934 10
	slli	a4,a0,2
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a4
	lw	a5,0(a5)
	.loc 1 926 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	.loc 1 935 37
	lw	a0,32(a5)
.LVL319:
	.loc 1 926 1
	sw	ra,8(sp)
	sw	s1,0(sp)
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	mv	s1,a1
	.loc 1 934 5 is_stmt 1
.LVL320:
	.loc 1 935 5
	.loc 1 936 5
	.loc 1 936 33 is_stmt 0
	call	hal_memview_infrasys_to_riscv
.LVL321:
	.loc 1 937 5 is_stmt 1
	.loc 1 937 20 is_stmt 0
	sw	s1,0(a0)
	.loc 1 939 5 is_stmt 1
	li	a1,4
	mv	a0,s0
.LVL322:
	call	vdma_set_sw_move_byte
.LVL323:
	.loc 1 941 5
	.loc 1 942 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL324:
	lw	s1,0(sp)
	.cfi_restore 9
.LVL325:
	.loc 1 941 12
	li	a0,0
	.loc 1 942 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL326:
.L306:
	.loc 1 931 16
	li	a0,-2
.LVL327:
	.loc 1 942 1
	ret
	.cfi_endproc
.LFE36:
	.size	vdma_push_data_4bytes, .-vdma_push_data_4bytes
	.section	.text.vdma_push_data_multi_bytes,"ax",@progbits
	.align	1
	.globl	vdma_push_data_multi_bytes
	.hidden	vdma_push_data_multi_bytes
	.type	vdma_push_data_multi_bytes, @function
vdma_push_data_multi_bytes:
.LFB37:
	.loc 1 945 1 is_stmt 1
	.cfi_startproc
.LVL328:
	.loc 1 946 5
	.loc 1 947 5
	.loc 1 948 5
	.loc 1 949 5
	.loc 1 951 5
	.loc 1 945 1 is_stmt 0
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	sw	ra,20(sp)
	sw	s0,16(sp)
	sw	s1,12(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 945 1
	sw	a0,0(sp)
	.loc 1 951 8
	li	a5,5
	bgtu	a0,a5,.L315
	.loc 1 954 8
	sw	a1,4(sp)
	mv	a4,a0
	.loc 1 954 5 is_stmt 1
	.loc 1 955 16 is_stmt 0
	li	a0,-1
.LVL329:
	.loc 1 954 8
	beq	a1,zero,.L311
	.loc 1 957 10
	slli	a4,a4,2
.LVL330:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a4
	lw	s1,0(a5)
	mv	s0,a2
	.loc 1 957 5 is_stmt 1
.LVL331:
	.loc 1 958 5
	.loc 1 958 16 is_stmt 0
	lw	a5,92(s1)
.LVL332:
	.loc 1 959 5 is_stmt 1
	.loc 1 959 8 is_stmt 0
	bltu	a5,a2,.L311
	.loc 1 963 5 is_stmt 1
	.loc 1 963 36 is_stmt 0
	lw	a0,32(s1)
.LVL333:
	.loc 1 964 5 is_stmt 1
	.loc 1 964 32 is_stmt 0
	call	hal_memview_infrasys_to_riscv
.LVL334:
	.loc 1 965 5 is_stmt 1
	.loc 1 965 19 is_stmt 0
	lw	a5,88(s1)
.LVL335:
	.loc 1 966 5 is_stmt 1
	.loc 1 966 8 is_stmt 0
	lw	a1,4(sp)
	.loc 1 972 9
	mv	a2,s0
	.loc 1 966 8
	bleu	s0,a5,.L319
	.loc 1 967 9 is_stmt 1
	mv	a2,a5
	sw	a5,8(sp)
	call	memcpy
.LVL336:
	.loc 1 968 9
	.loc 1 968 40 is_stmt 0
	lw	a0,28(s1)
.LVL337:
	.loc 1 969 9 is_stmt 1
	.loc 1 969 36 is_stmt 0
	call	hal_memview_infrasys_to_riscv
.LVL338:
	.loc 1 970 9 is_stmt 1
	lw	a5,8(sp)
	lw	a1,4(sp)
	sub	a2,s0,a5
	add	a1,a1,a5
.LVL339:
.L319:
	.loc 1 972 9 is_stmt 0
	call	memcpy
.LVL340:
	.loc 1 974 5 is_stmt 1
	lw	a0,0(sp)
	slli	a1,s0,16
	srli	a1,a1,16
	call	vdma_set_sw_move_byte
.LVL341:
	.loc 1 976 5
	.loc 1 976 12 is_stmt 0
	li	a0,0
.LVL342:
.L311:
	.loc 1 977 1
	lw	ra,20(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	lw	s1,12(sp)
	.cfi_restore 9
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
.LVL343:
	jr	ra
.LVL344:
.L315:
	.cfi_restore_state
	.loc 1 952 16
	li	a0,-2
.LVL345:
	j	.L311
	.cfi_endproc
.LFE37:
	.size	vdma_push_data_multi_bytes, .-vdma_push_data_multi_bytes
	.section	.text.vdma_pop_data,"ax",@progbits
	.align	1
	.globl	vdma_pop_data
	.hidden	vdma_pop_data
	.type	vdma_pop_data, @function
vdma_pop_data:
.LFB38:
	.loc 1 980 1 is_stmt 1
	.cfi_startproc
.LVL346:
	.loc 1 981 5
	.loc 1 982 5
	.loc 1 984 5
	.loc 1 984 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L322
	.loc 1 980 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	mv	s0,a0
	mv	s1,a1
	.loc 1 987 5 is_stmt 1
	.loc 1 988 16 is_stmt 0
	li	a0,-1
.LVL347:
	.loc 1 987 8
	beq	a1,zero,.L320
	.loc 1 991 5 is_stmt 1
	.loc 1 991 10 is_stmt 0
	slli	a4,s0,2
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a4
	lw	a5,0(a5)
.LVL348:
	.loc 1 992 5 is_stmt 1
	.loc 1 992 35 is_stmt 0
	lw	a0,36(a5)
.LVL349:
	.loc 1 993 5 is_stmt 1
	.loc 1 993 31 is_stmt 0
	call	hal_memview_infrasys_to_riscv
.LVL350:
	.loc 1 994 5 is_stmt 1
	.loc 1 994 13 is_stmt 0
	lbu	a5,0(a0)
	.loc 1 996 5
	li	a1,1
	mv	a0,s0
.LVL351:
	.loc 1 994 11
	sb	a5,0(s1)
	.loc 1 996 5 is_stmt 1
	call	vdma_set_sw_move_byte
.LVL352:
	.loc 1 998 5
	.loc 1 998 12 is_stmt 0
	li	a0,0
.LVL353:
.L320:
	.loc 1 999 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL354:
	lw	s1,0(sp)
	.cfi_restore 9
.LVL355:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL356:
.L322:
	.loc 1 985 16
	li	a0,-2
.LVL357:
	.loc 1 999 1
	ret
	.cfi_endproc
.LFE38:
	.size	vdma_pop_data, .-vdma_pop_data
	.section	.text.vdma_pop_data_4bytes,"ax",@progbits
	.align	1
	.globl	vdma_pop_data_4bytes
	.hidden	vdma_pop_data_4bytes
	.type	vdma_pop_data_4bytes, @function
vdma_pop_data_4bytes:
.LFB39:
	.loc 1 1002 1 is_stmt 1
	.cfi_startproc
.LVL358:
	.loc 1 1003 5
	.loc 1 1004 5
	.loc 1 1006 5
	.loc 1 1006 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L330
	.loc 1 1002 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	mv	s0,a0
	mv	s1,a1
	.loc 1 1009 5 is_stmt 1
	.loc 1 1010 16 is_stmt 0
	li	a0,-1
.LVL359:
	.loc 1 1009 8
	beq	a1,zero,.L328
	.loc 1 1013 5 is_stmt 1
	.loc 1 1013 10 is_stmt 0
	slli	a4,s0,2
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a4
	lw	a5,0(a5)
.LVL360:
	.loc 1 1014 5 is_stmt 1
	.loc 1 1014 36 is_stmt 0
	lw	a0,36(a5)
.LVL361:
	.loc 1 1015 5 is_stmt 1
	.loc 1 1015 32 is_stmt 0
	call	hal_memview_infrasys_to_riscv
.LVL362:
	.loc 1 1016 5 is_stmt 1
	.loc 1 1016 13 is_stmt 0
	lw	a5,0(a0)
	.loc 1 1018 5
	li	a1,4
	mv	a0,s0
.LVL363:
	.loc 1 1016 11
	sw	a5,0(s1)
	.loc 1 1018 5 is_stmt 1
	call	vdma_set_sw_move_byte
.LVL364:
	.loc 1 1020 5
	.loc 1 1020 12 is_stmt 0
	li	a0,0
.LVL365:
.L328:
	.loc 1 1021 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL366:
	lw	s1,0(sp)
	.cfi_restore 9
.LVL367:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL368:
.L330:
	.loc 1 1007 16
	li	a0,-2
.LVL369:
	.loc 1 1021 1
	ret
	.cfi_endproc
.LFE39:
	.size	vdma_pop_data_4bytes, .-vdma_pop_data_4bytes
	.section	.text.vdma_pop_data_multi_bytes,"ax",@progbits
	.align	1
	.globl	vdma_pop_data_multi_bytes
	.hidden	vdma_pop_data_multi_bytes
	.type	vdma_pop_data_multi_bytes, @function
vdma_pop_data_multi_bytes:
.LFB40:
	.loc 1 1024 1 is_stmt 1
	.cfi_startproc
.LVL370:
	.loc 1 1025 5
	.loc 1 1026 5
	.loc 1 1027 5
	.loc 1 1028 5
	.loc 1 1029 5
	.loc 1 1031 5
	.loc 1 1024 1 is_stmt 0
	addi	sp,sp,-24
	.cfi_def_cfa_offset 24
	sw	ra,20(sp)
	sw	s0,16(sp)
	sw	s1,12(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 1024 1
	sw	a0,4(sp)
	sw	a1,0(sp)
	.loc 1 1031 8
	li	a5,5
	bgtu	a0,a5,.L340
	mv	a4,a0
	.loc 1 1034 5 is_stmt 1
	.loc 1 1035 16 is_stmt 0
	li	a0,-1
.LVL371:
	.loc 1 1034 8
	beq	a1,zero,.L336
	.loc 1 1037 10
	slli	a4,a4,2
.LVL372:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a4
	lw	a5,0(a5)
	mv	s0,a2
	.loc 1 1037 5 is_stmt 1
.LVL373:
	.loc 1 1038 5
	.loc 1 1038 12 is_stmt 0
	lbu	a3,5(a5)
.LVL374:
	.loc 1 1039 5 is_stmt 1
	.loc 1 1039 27 is_stmt 0
	lw	a4,40(a5)
.LVL375:
	.loc 1 1040 5 is_stmt 1
	.loc 1 1039 20 is_stmt 0
	sll	a4,a4,a3
.LVL376:
	.loc 1 1040 8
	bltu	a4,a2,.L336
	.loc 1 1044 5 is_stmt 1
	.loc 1 1044 19 is_stmt 0
	lw	s1,88(a5)
.LVL377:
	.loc 1 1045 5 is_stmt 1
	.loc 1 1045 35 is_stmt 0
	lw	a0,36(a5)
	sw	a5,8(sp)
.LVL378:
	.loc 1 1046 5 is_stmt 1
	.loc 1 1046 31 is_stmt 0
	call	hal_memview_infrasys_to_riscv
.LVL379:
	mv	a1,a0
.LVL380:
	.loc 1 1047 5 is_stmt 1
	.loc 1 1047 8 is_stmt 0
	bleu	s0,s1,.L338
	.loc 1 1048 9 is_stmt 1
	lw	a0,0(sp)
.LVL381:
	mv	a2,s1
	call	memcpy
.LVL382:
	.loc 1 1049 9
	.loc 1 1049 39 is_stmt 0
	lw	a5,8(sp)
	lw	a0,28(a5)
.LVL383:
	.loc 1 1050 9 is_stmt 1
	.loc 1 1050 35 is_stmt 0
	call	hal_memview_infrasys_to_riscv
.LVL384:
	.loc 1 1051 9
	lw	a5,0(sp)
	.loc 1 1050 35
	mv	a1,a0
.LVL385:
	.loc 1 1051 9 is_stmt 1
	sub	a2,s0,s1
	add	a0,a5,s1
.LVL386:
.L344:
	.loc 1 1053 9 is_stmt 0
	call	memcpy
.LVL387:
	.loc 1 1056 5 is_stmt 1
	lw	a0,4(sp)
	slli	a1,s0,16
	srli	a1,a1,16
	call	vdma_set_sw_move_byte
.LVL388:
	.loc 1 1058 5
	.loc 1 1058 12 is_stmt 0
	li	a0,0
.LVL389:
.L336:
	.loc 1 1059 1
	lw	ra,20(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,16(sp)
	.cfi_restore 8
	lw	s1,12(sp)
	.cfi_restore 9
	addi	sp,sp,24
	.cfi_def_cfa_offset 0
.LVL390:
	jr	ra
.LVL391:
.L338:
	.cfi_restore_state
	.loc 1 1053 9 is_stmt 1
	lw	a0,0(sp)
.LVL392:
	mv	a2,s0
	j	.L344
.LVL393:
.L340:
	.loc 1 1032 16 is_stmt 0
	li	a0,-2
.LVL394:
	j	.L336
	.cfi_endproc
.LFE40:
	.size	vdma_pop_data_multi_bytes, .-vdma_pop_data_multi_bytes
	.section	.tcm_code."/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c".1159,"ax",@progbits
	.align	1
	.globl	vdma_get_hw_write_point
	.hidden	vdma_get_hw_write_point
	.type	vdma_get_hw_write_point, @function
vdma_get_hw_write_point:
.LFB46:
	.loc 1 1160 1 is_stmt 1
	.cfi_startproc
.LVL395:
	.loc 1 1161 5
	.loc 1 1163 5
	.loc 1 1163 8 is_stmt 0
	li	a4,5
	.loc 1 1160 1
	mv	a5,a0
	.loc 1 1163 8
	bgtu	a0,a4,.L347
	.loc 1 1166 5 is_stmt 1
	.loc 1 1167 16 is_stmt 0
	li	a0,-1
.LVL396:
	.loc 1 1166 8
	beq	a1,zero,.L345
	.loc 1 1170 5 is_stmt 1
	.loc 1 1170 10 is_stmt 0
	lla	a4,g_vdma_regbase_table
	slli	a5,a5,2
.LVL397:
	add	a5,a4,a5
	lw	a5,0(a5)
.LVL398:
	.loc 1 1171 5 is_stmt 1
	.loc 1 1173 12 is_stmt 0
	li	a0,0
	.loc 1 1171 24
	lw	a5,32(a5)
.LVL399:
	.loc 1 1171 18
	sw	a5,0(a1)
	.loc 1 1173 5 is_stmt 1
	.loc 1 1173 12 is_stmt 0
	ret
.LVL400:
.L347:
	.loc 1 1164 16
	li	a0,-2
.LVL401:
.L345:
	.loc 1 1174 1
	ret
	.cfi_endproc
.LFE46:
	.size	vdma_get_hw_write_point, .-vdma_get_hw_write_point
	.section	.tcm_code."/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c".1176,"ax",@progbits
	.align	1
	.globl	vdma_get_hw_write_offset
	.hidden	vdma_get_hw_write_offset
	.type	vdma_get_hw_write_offset, @function
vdma_get_hw_write_offset:
.LFB47:
	.loc 1 1177 1 is_stmt 1
	.cfi_startproc
.LVL402:
	.loc 1 1178 5
	.loc 1 1180 5
	.loc 1 1180 8 is_stmt 0
	li	a4,5
	.loc 1 1177 1
	mv	a5,a0
	.loc 1 1180 8
	bgtu	a0,a4,.L351
	.loc 1 1184 5 is_stmt 1
	.loc 1 1185 16 is_stmt 0
	li	a0,-1
.LVL403:
	.loc 1 1184 8
	beq	a1,zero,.L349
	.loc 1 1188 5 is_stmt 1
	.loc 1 1188 10 is_stmt 0
	lla	a4,g_vdma_regbase_table
	slli	a5,a5,2
.LVL404:
	add	a5,a4,a5
	lw	a4,0(a5)
.LVL405:
	.loc 1 1189 5 is_stmt 1
	.loc 1 1191 12 is_stmt 0
	li	a0,0
	.loc 1 1189 25
	lw	a5,32(a4)
	.loc 1 1189 44
	lw	a4,28(a4)
.LVL406:
	.loc 1 1189 38
	sub	a5,a5,a4
	.loc 1 1189 19
	sw	a5,0(a1)
	.loc 1 1191 5 is_stmt 1
	.loc 1 1191 12 is_stmt 0
	ret
.LVL407:
.L351:
	.loc 1 1181 16
	li	a0,-2
.LVL408:
.L349:
	.loc 1 1192 1
	ret
	.cfi_endproc
.LFE47:
	.size	vdma_get_hw_write_offset, .-vdma_get_hw_write_offset
	.section	.text.vdma_register_callback,"ax",@progbits
	.align	1
	.globl	vdma_register_callback
	.hidden	vdma_register_callback
	.type	vdma_register_callback, @function
vdma_register_callback:
.LFB48:
	.loc 1 1195 1 is_stmt 1
	.cfi_startproc
.LVL409:
	.loc 1 1196 5
	.loc 1 1196 8 is_stmt 0
	li	a4,5
	bgtu	a0,a4,.L355
	mv	a5,a0
	.loc 1 1199 5 is_stmt 1
	.loc 1 1200 16 is_stmt 0
	li	a0,-1
.LVL410:
	.loc 1 1199 8
	beq	a1,zero,.L358
	.loc 1 1203 5 is_stmt 1
	.loc 1 1195 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 1203 35
	slli	a3,a5,3
	lla	a4,g_vdma_callback
	.loc 1 1195 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 1203 35
	add	a4,a4,a3
	sw	a1,0(a4)
	.loc 1 1204 5 is_stmt 1
	.loc 1 1204 39 is_stmt 0
	sw	a2,4(a4)
	.loc 1 1206 5 is_stmt 1
	slli	a5,a5,2
.LVL411:
	lla	a4,g_vdma_channel_map_table
	add	a5,a4,a5
	lw	a0,0(a5)
	sw	a0,0(sp)
	call	internal_dma_register_irq_callback
.LVL412:
	.loc 1 1207 5
	lw	a0,0(sp)
	call	internal_dma_enable_irq
.LVL413:
	.loc 1 1209 5
	.loc 1 1210 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	.loc 1 1209 12
	li	a0,0
	.loc 1 1210 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL414:
.L355:
	.loc 1 1197 16
	li	a0,-2
.LVL415:
	ret
.LVL416:
.L358:
	.loc 1 1210 1
	ret
	.cfi_endproc
.LFE48:
	.size	vdma_register_callback, .-vdma_register_callback
	.section	.text.vdma_buffer_is_empty,"ax",@progbits
	.align	1
	.globl	vdma_buffer_is_empty
	.hidden	vdma_buffer_is_empty
	.type	vdma_buffer_is_empty, @function
vdma_buffer_is_empty:
.LFB49:
	.loc 1 1213 1 is_stmt 1
	.cfi_startproc
.LVL417:
	.loc 1 1214 5
	.loc 1 1216 5
	.loc 1 1216 8 is_stmt 0
	li	a5,5
	bgtu	a0,a5,.L363
	.loc 1 1220 5 is_stmt 1
	.loc 1 1220 10 is_stmt 0
	slli	a0,a0,2
.LVL418:
	lla	a5,g_vdma_regbase_table
	add	a5,a5,a0
	lw	a5,0(a5)
.LVL419:
	.loc 1 1221 5 is_stmt 1
	.loc 1 1221 13 is_stmt 0
	lw	a0,36(a5)
	.loc 1 1221 33
	lw	a5,32(a5)
.LVL420:
	.loc 1 1221 8
	sub	a0,a0,a5
	seqz	a0,a0
	ret
.LVL421:
.L363:
	.loc 1 1217 15
	li	a0,0
.LVL422:
	.loc 1 1226 1
	ret
	.cfi_endproc
.LFE49:
	.size	vdma_buffer_is_empty, .-vdma_buffer_is_empty
	.section	.text.vdma_dump_reg_list,"ax",@progbits
	.align	1
	.globl	vdma_dump_reg_list
	.hidden	vdma_dump_reg_list
	.type	vdma_dump_reg_list, @function
vdma_dump_reg_list:
.LFB50:
	.loc 1 1229 1 is_stmt 1
	.cfi_startproc
.LVL423:
	.loc 1 1230 5
	.loc 1 1232 5
	.loc 1 1232 8 is_stmt 0
	li	a5,5
	bleu	a0,a5,.L366
	.loc 1 1233 16
	li	a0,-2
.LVL424:
	ret
.LVL425:
.L366:
	.loc 1 1254 12
	li	a0,0
.LVL426:
	.loc 1 1255 1
	ret
	.cfi_endproc
.LFE50:
	.size	vdma_dump_reg_list, .-vdma_dump_reg_list
	.section	.log_string,"a"
	.align	2
	.type	file.0, @object
	.size	file.0, 67
file.0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.1, @object
	.size	exp.1, 2
exp.1:
	.string	"0"
	.align	2
	.type	file.2, @object
	.size	file.2, 67
file.2:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.3, @object
	.size	exp.3, 2
exp.3:
	.string	"0"
	.align	2
	.type	file.4, @object
	.size	file.4, 67
file.4:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.5, @object
	.size	exp.5, 2
exp.5:
	.string	"0"
	.align	2
	.type	file.6, @object
	.size	file.6, 67
file.6:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.7, @object
	.size	exp.7, 2
exp.7:
	.string	"0"
	.section	.sbss.g_vdma_init_status,"aw",@nobits
	.align	2
	.type	g_vdma_init_status, @object
	.size	g_vdma_init_status, 6
g_vdma_init_status:
	.zero	6
	.section	.bss.g_vdma_callback,"aw",@nobits
	.align	2
	.type	g_vdma_callback, @object
	.size	g_vdma_callback, 48
g_vdma_callback:
	.zero	48
	.hidden	g_vdma_regbase_table
	.globl	g_vdma_regbase_table
	.section	.data.g_vdma_regbase_table,"aw"
	.align	2
	.type	g_vdma_regbase_table, @object
	.size	g_vdma_regbase_table, 24
g_vdma_regbase_table:
	.word	1109852432
	.word	1109852688
	.word	1109917968
	.word	1109918224
	.word	1109983504
	.word	1109983760
	.section	.rodata.g_vdma_channel_map_table,"a"
	.align	2
	.type	g_vdma_channel_map_table, @object
	.size	g_vdma_channel_map_table, 24
g_vdma_channel_map_table:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.section	.sbss.g_pdma_init_status,"aw",@nobits
	.align	2
	.type	g_pdma_init_status, @object
	.size	g_pdma_init_status, 4
g_pdma_init_status:
	.zero	4
	.section	.bss.g_pdma_callback,"aw",@nobits
	.align	2
	.type	g_pdma_callback, @object
	.size	g_pdma_callback, 32
g_pdma_callback:
	.zero	32
	.section	.rodata.g_pdma_cfg_regbase_table,"a"
	.align	2
	.type	g_pdma_cfg_regbase_table, @object
	.size	g_pdma_cfg_regbase_table, 16
g_pdma_cfg_regbase_table:
	.word	1109524492
	.word	1109524516
	.word	1074724876
	.word	1074724900
	.section	.rodata.g_pdma_status_regbase_table,"a"
	.align	2
	.type	g_pdma_status_regbase_table, @object
	.size	g_pdma_status_regbase_table, 16
g_pdma_status_regbase_table:
	.word	1109524764
	.word	1109525020
	.word	1074725148
	.word	1074725404
	.section	.rodata.g_pdma_channel_map_table,"a"
	.align	2
	.type	g_pdma_channel_map_table, @object
	.size	g_pdma_channel_map_table, 16
g_pdma_channel_map_table:
	.word	6
	.word	7
	.word	8
	.word	9
	.section	.log_string
	.align	2
	.type	file.8, @object
	.size	file.8, 67
file.8:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.9, @object
	.size	exp.9, 2
exp.9:
	.string	"0"
	.align	2
	.type	file.10, @object
	.size	file.10, 67
file.10:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.11, @object
	.size	exp.11, 2
exp.11:
	.string	"0"
	.align	2
	.type	file.12, @object
	.size	file.12, 67
file.12:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.13, @object
	.size	exp.13, 2
exp.13:
	.string	"0"
	.align	2
	.type	file.14, @object
	.size	file.14, 67
file.14:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.15, @object
	.size	exp.15, 2
exp.15:
	.string	"0"
	.align	2
	.type	file.16, @object
	.size	file.16, 67
file.16:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.17, @object
	.size	exp.17, 2
exp.17:
	.string	"0"
	.align	2
	.type	file.18, @object
	.size	file.18, 67
file.18:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.19, @object
	.size	exp.19, 2
exp.19:
	.string	"0"
	.align	2
	.type	file.20, @object
	.size	file.20, 67
file.20:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.align	2
	.type	exp.21, @object
	.size	exp.21, 2
exp.21:
	.string	"0"
	.section	.rodata.g_dma_reg_table,"a"
	.align	2
	.type	g_dma_reg_table, @object
	.size	g_dma_reg_table, 20
g_dma_reg_table:
	.word	1109852160
	.word	1109917696
	.word	1109983232
	.word	1109524480
	.word	1074724864
	.section	.rodata.g_dma_clk_table,"a"
	.align	2
	.type	g_dma_clk_table, @object
	.size	g_dma_clk_table, 20
g_dma_clk_table:
	.word	41
	.word	42
	.word	43
	.word	45
	.word	166
	.section	.rodata.g_dma_irq_table,"a"
	.align	2
	.type	g_dma_irq_table, @object
	.size	g_dma_irq_table, 20
g_dma_irq_table:
	.word	21
	.word	21
	.word	21
	.word	26
	.word	26
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_pdma_internal.h"
	.file 5 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.file 6 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
	.file 7 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 8 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 9 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_clock.h"
	.file 10 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.file 11 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_memview.h"
	.file 12 "/workdir/airoha/risc-v/kernel/service/exception_handler/inc/exception_handler.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x3016
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x3b
	.4byte	.LASF474
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL134
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x17
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x17
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x17
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x17
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x3c
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x10
	.4byte	.LASF13
	.byte	0x2
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0x17
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x17
	.byte	0x10
	.byte	0x4
	.4byte	.LASF7
	.uleb128 0x17
	.byte	0x1
	.byte	0x6
	.4byte	.LASF8
	.uleb128 0x17
	.byte	0x2
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x17
	.byte	0x4
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x17
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x3d
	.byte	0x4
	.uleb128 0x31
	.4byte	0x7f
	.uleb128 0x17
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x28
	.4byte	0x86
	.uleb128 0x15
	.4byte	0x8d
	.uleb128 0x10
	.4byte	.LASF14
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x34
	.uleb128 0x1d
	.4byte	0x97
	.uleb128 0x10
	.4byte	.LASF15
	.byte	0x3
	.byte	0x31
	.byte	0x1c
	.4byte	0x3b
	.uleb128 0x10
	.4byte	.LASF16
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x78
	.uleb128 0x1d
	.4byte	0xb4
	.uleb128 0x28
	.4byte	0xc0
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x38
	.4byte	0xfb
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x4
	.byte	0
	.uleb128 0x10
	.4byte	.LASF23
	.byte	0x4
	.byte	0x3f
	.byte	0x3
	.4byte	0xca
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x42
	.4byte	0x126
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x2
	.byte	0
	.uleb128 0x10
	.4byte	.LASF27
	.byte	0x4
	.byte	0x46
	.byte	0x3
	.4byte	0x107
	.uleb128 0x1b
	.byte	0x5
	.4byte	0x42
	.byte	0x4
	.byte	0x49
	.4byte	0x14b
	.uleb128 0x19
	.4byte	.LASF28
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF30
	.byte	0x4
	.byte	0x4c
	.byte	0x3
	.4byte	0x132
	.uleb128 0x1b
	.byte	0x5
	.4byte	0x42
	.byte	0x4
	.byte	0x4f
	.4byte	0x17c
	.uleb128 0x19
	.4byte	.LASF31
	.sleb128 -3
	.uleb128 0x19
	.4byte	.LASF32
	.sleb128 -2
	.uleb128 0x19
	.4byte	.LASF33
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF35
	.byte	0x4
	.byte	0x54
	.byte	0x3
	.4byte	0x157
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x57
	.4byte	0x1a1
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.4byte	.LASF38
	.byte	0x4
	.byte	0x5a
	.byte	0x3
	.4byte	0x188
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x5d
	.4byte	0x1d2
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x3
	.byte	0
	.uleb128 0x10
	.4byte	.LASF43
	.byte	0x4
	.byte	0x62
	.byte	0x3
	.4byte	0x1ad
	.uleb128 0x1f
	.byte	0x10
	.byte	0x4
	.byte	0x65
	.byte	0x9
	.4byte	0x21c
	.uleb128 0xa
	.4byte	.LASF44
	.byte	0x4
	.byte	0x66
	.byte	0x25
	.4byte	0x21c
	.byte	0
	.uleb128 0xa
	.4byte	.LASF45
	.byte	0x4
	.byte	0x67
	.byte	0x21
	.4byte	0x126
	.byte	0x4
	.uleb128 0xa
	.4byte	.LASF46
	.byte	0x4
	.byte	0x68
	.byte	0xe
	.4byte	0xb4
	.byte	0x8
	.uleb128 0xa
	.4byte	.LASF47
	.byte	0x4
	.byte	0x69
	.byte	0x18
	.4byte	0x1d2
	.byte	0xc
	.byte	0
	.uleb128 0x17
	.byte	0x1
	.byte	0x2
	.4byte	.LASF48
	.uleb128 0x10
	.4byte	.LASF49
	.byte	0x4
	.byte	0x6a
	.byte	0x3
	.4byte	0x1de
	.uleb128 0x10
	.4byte	.LASF50
	.byte	0x4
	.byte	0x6d
	.byte	0x10
	.4byte	0x23b
	.uleb128 0x15
	.4byte	0x240
	.uleb128 0x2f
	.4byte	0x250
	.uleb128 0x14
	.4byte	0x14b
	.uleb128 0x14
	.4byte	0x7f
	.byte	0
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0xf0
	.4byte	0x28d
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x6
	.byte	0
	.uleb128 0x10
	.4byte	.LASF59
	.byte	0x4
	.byte	0xf9
	.byte	0x3
	.4byte	0x250
	.uleb128 0x1b
	.byte	0x5
	.4byte	0x42
	.byte	0x4
	.byte	0xfc
	.4byte	0x2be
	.uleb128 0x19
	.4byte	.LASF60
	.sleb128 -3
	.uleb128 0x19
	.4byte	.LASF61
	.sleb128 -2
	.uleb128 0x19
	.4byte	.LASF62
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF64
	.byte	0x4
	.2byte	0x101
	.byte	0x3
	.4byte	0x299
	.uleb128 0x29
	.byte	0x5
	.4byte	0x42
	.byte	0x4
	.2byte	0x10a
	.4byte	0x2e5
	.uleb128 0x19
	.4byte	.LASF65
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF67
	.byte	0x4
	.2byte	0x10d
	.byte	0x3
	.4byte	0x2cb
	.uleb128 0xb
	.byte	0x8
	.byte	0x4
	.2byte	0x110
	.byte	0x9
	.4byte	0x319
	.uleb128 0x4
	.4byte	.LASF68
	.byte	0x4
	.2byte	0x111
	.byte	0xe
	.4byte	0xb4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF45
	.byte	0x4
	.2byte	0x112
	.byte	0xe
	.4byte	0xb4
	.byte	0x4
	.byte	0
	.uleb128 0x8
	.4byte	.LASF69
	.byte	0x4
	.2byte	0x113
	.byte	0x3
	.4byte	0x2f2
	.uleb128 0x8
	.4byte	.LASF70
	.byte	0x4
	.2byte	0x116
	.byte	0x10
	.4byte	0x333
	.uleb128 0x15
	.4byte	0x338
	.uleb128 0x2f
	.4byte	0x348
	.uleb128 0x14
	.4byte	0x2e5
	.uleb128 0x14
	.4byte	0x7f
	.byte	0
	.uleb128 0x3e
	.4byte	.LASF475
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x5
	.2byte	0x128
	.byte	0x12
	.4byte	0x3ce
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x1f
	.byte	0
	.uleb128 0x8
	.4byte	.LASF90
	.byte	0x5
	.2byte	0x13c
	.byte	0x7
	.4byte	0x348
	.uleb128 0x8
	.4byte	.LASF91
	.byte	0x5
	.2byte	0x13e
	.byte	0x17
	.4byte	0x3ce
	.uleb128 0xc
	.4byte	0xb4
	.4byte	0x3f8
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x3b
	.byte	0
	.uleb128 0xc
	.4byte	0xc0
	.4byte	0x408
	.uleb128 0xd
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x1d
	.4byte	0x3f8
	.uleb128 0xc
	.4byte	0xc0
	.4byte	0x41d
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x1d
	.4byte	0x40d
	.uleb128 0xc
	.4byte	0xc0
	.4byte	0x432
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x1d
	.4byte	0x422
	.uleb128 0x1f
	.byte	0x7c
	.byte	0x6
	.byte	0x43
	.byte	0x9
	.4byte	0x593
	.uleb128 0xa
	.4byte	.LASF92
	.byte	0x6
	.byte	0x44
	.byte	0x1d
	.4byte	0xc5
	.byte	0
	.uleb128 0xa
	.4byte	.LASF93
	.byte	0x6
	.byte	0x45
	.byte	0x17
	.4byte	0x408
	.byte	0x4
	.uleb128 0xa
	.4byte	.LASF94
	.byte	0x6
	.byte	0x46
	.byte	0x1d
	.4byte	0xc5
	.byte	0x8
	.uleb128 0xa
	.4byte	.LASF95
	.byte	0x6
	.byte	0x47
	.byte	0x17
	.4byte	0xc0
	.byte	0xc
	.uleb128 0xa
	.4byte	.LASF96
	.byte	0x6
	.byte	0x48
	.byte	0x17
	.4byte	0xc0
	.byte	0x10
	.uleb128 0xa
	.4byte	.LASF97
	.byte	0x6
	.byte	0x49
	.byte	0x1d
	.4byte	0xc5
	.byte	0x14
	.uleb128 0xa
	.4byte	.LASF98
	.byte	0x6
	.byte	0x4a
	.byte	0x17
	.4byte	0xc0
	.byte	0x18
	.uleb128 0xa
	.4byte	.LASF99
	.byte	0x6
	.byte	0x4b
	.byte	0x17
	.4byte	0xc0
	.byte	0x1c
	.uleb128 0xa
	.4byte	.LASF100
	.byte	0x6
	.byte	0x4c
	.byte	0x1d
	.4byte	0xc5
	.byte	0x20
	.uleb128 0xa
	.4byte	.LASF101
	.byte	0x6
	.byte	0x4d
	.byte	0x17
	.4byte	0x408
	.byte	0x24
	.uleb128 0xa
	.4byte	.LASF102
	.byte	0x6
	.byte	0x4e
	.byte	0x1d
	.4byte	0xc5
	.byte	0x28
	.uleb128 0xa
	.4byte	.LASF103
	.byte	0x6
	.byte	0x4f
	.byte	0x17
	.4byte	0x41d
	.byte	0x2c
	.uleb128 0xa
	.4byte	.LASF104
	.byte	0x6
	.byte	0x50
	.byte	0x1d
	.4byte	0xc5
	.byte	0x40
	.uleb128 0xa
	.4byte	.LASF105
	.byte	0x6
	.byte	0x51
	.byte	0x1d
	.4byte	0xc5
	.byte	0x44
	.uleb128 0xa
	.4byte	.LASF106
	.byte	0x6
	.byte	0x52
	.byte	0x17
	.4byte	0x432
	.byte	0x48
	.uleb128 0xa
	.4byte	.LASF107
	.byte	0x6
	.byte	0x53
	.byte	0x1d
	.4byte	0xc5
	.byte	0x50
	.uleb128 0xa
	.4byte	.LASF108
	.byte	0x6
	.byte	0x54
	.byte	0x17
	.4byte	0xc0
	.byte	0x54
	.uleb128 0xa
	.4byte	.LASF109
	.byte	0x6
	.byte	0x55
	.byte	0x17
	.4byte	0xc0
	.byte	0x58
	.uleb128 0xa
	.4byte	.LASF110
	.byte	0x6
	.byte	0x56
	.byte	0x17
	.4byte	0x408
	.byte	0x5c
	.uleb128 0xa
	.4byte	.LASF111
	.byte	0x6
	.byte	0x57
	.byte	0x1d
	.4byte	0xc5
	.byte	0x60
	.uleb128 0xa
	.4byte	.LASF112
	.byte	0x6
	.byte	0x58
	.byte	0x17
	.4byte	0xc0
	.byte	0x64
	.uleb128 0xa
	.4byte	.LASF113
	.byte	0x6
	.byte	0x59
	.byte	0x17
	.4byte	0xc0
	.byte	0x68
	.uleb128 0xa
	.4byte	.LASF114
	.byte	0x6
	.byte	0x5a
	.byte	0x17
	.4byte	0x408
	.byte	0x6c
	.uleb128 0xa
	.4byte	.LASF115
	.byte	0x6
	.byte	0x5b
	.byte	0x1d
	.4byte	0xc5
	.byte	0x70
	.uleb128 0xa
	.4byte	.LASF116
	.byte	0x6
	.byte	0x5c
	.byte	0x17
	.4byte	0xc0
	.byte	0x74
	.uleb128 0xa
	.4byte	.LASF117
	.byte	0x6
	.byte	0x5d
	.byte	0x17
	.4byte	0xc0
	.byte	0x78
	.byte	0
	.uleb128 0x10
	.4byte	.LASF118
	.byte	0x6
	.byte	0x5e
	.byte	0x3
	.4byte	0x437
	.uleb128 0x1f
	.byte	0x4
	.byte	0x6
	.byte	0xaa
	.byte	0x5
	.4byte	0x5d0
	.uleb128 0x16
	.4byte	.LASF119
	.byte	0xab
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0
	.uleb128 0x16
	.4byte	.LASF120
	.byte	0xac
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.4byte	.LASF121
	.byte	0xad
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x23
	.byte	0xa9
	.4byte	0x5ed
	.uleb128 0x1e
	.4byte	.LASF122
	.byte	0xae
	.byte	0x7
	.4byte	0x59f
	.uleb128 0x1e
	.4byte	.LASF123
	.byte	0xaf
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF124
	.byte	0x6
	.byte	0xb0
	.byte	0x3
	.4byte	0x5d0
	.uleb128 0x1f
	.byte	0x4
	.byte	0x6
	.byte	0xba
	.byte	0x5
	.4byte	0x62a
	.uleb128 0x16
	.4byte	.LASF125
	.byte	0xbb
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0
	.uleb128 0x16
	.4byte	.LASF126
	.byte	0xbc
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.4byte	.LASF121
	.byte	0xbd
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x23
	.byte	0xb9
	.4byte	0x647
	.uleb128 0x1e
	.4byte	.LASF122
	.byte	0xbe
	.byte	0x7
	.4byte	0x5f9
	.uleb128 0x1e
	.4byte	.LASF123
	.byte	0xbf
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF127
	.byte	0x6
	.byte	0xc0
	.byte	0x3
	.4byte	0x62a
	.uleb128 0x1f
	.byte	0x4
	.byte	0x6
	.byte	0xca
	.byte	0x5
	.4byte	0x684
	.uleb128 0x16
	.4byte	.LASF128
	.byte	0xcb
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0
	.uleb128 0x16
	.4byte	.LASF129
	.byte	0xcc
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.4byte	.LASF121
	.byte	0xcd
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x23
	.byte	0xc9
	.4byte	0x6a1
	.uleb128 0x1e
	.4byte	.LASF122
	.byte	0xce
	.byte	0x7
	.4byte	0x653
	.uleb128 0x1e
	.4byte	.LASF123
	.byte	0xcf
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF130
	.byte	0x6
	.byte	0xd0
	.byte	0x3
	.4byte	0x684
	.uleb128 0x1f
	.byte	0x4
	.byte	0x6
	.byte	0xda
	.byte	0x5
	.4byte	0x6d1
	.uleb128 0x16
	.4byte	.LASF131
	.byte	0xdb
	.byte	0x1b
	.4byte	0xc0
	.byte	0x10
	.byte	0
	.uleb128 0x16
	.4byte	.LASF121
	.byte	0xdc
	.byte	0x21
	.4byte	0xc5
	.byte	0x10
	.byte	0x10
	.byte	0
	.uleb128 0x23
	.byte	0xd9
	.4byte	0x6ee
	.uleb128 0x1e
	.4byte	.LASF122
	.byte	0xdd
	.byte	0x7
	.4byte	0x6ad
	.uleb128 0x1e
	.4byte	.LASF123
	.byte	0xde
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF132
	.byte	0x6
	.byte	0xdf
	.byte	0x3
	.4byte	0x6d1
	.uleb128 0x1f
	.byte	0x4
	.byte	0x6
	.byte	0xe7
	.byte	0x5
	.4byte	0x771
	.uleb128 0x16
	.4byte	.LASF133
	.byte	0xf9
	.byte	0x1b
	.4byte	0xc0
	.byte	0x5
	.byte	0
	.uleb128 0x16
	.4byte	.LASF121
	.byte	0xfa
	.byte	0x21
	.4byte	0xc5
	.byte	0x3
	.byte	0x5
	.uleb128 0x16
	.4byte	.LASF134
	.byte	0xff
	.byte	0x1b
	.4byte	0xc0
	.byte	0x2
	.byte	0x8
	.uleb128 0x5
	.4byte	.LASF135
	.2byte	0x100
	.byte	0x21
	.4byte	0xc5
	.byte	0x6
	.byte	0xa
	.uleb128 0x5
	.4byte	.LASF136
	.2byte	0x10d
	.byte	0x1b
	.4byte	0xc0
	.byte	0x4
	.byte	0x10
	.uleb128 0x5
	.4byte	.LASF137
	.2byte	0x10e
	.byte	0x21
	.4byte	0xc5
	.byte	0x4
	.byte	0x14
	.uleb128 0x5
	.4byte	.LASF138
	.2byte	0x10f
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0x18
	.uleb128 0x5
	.4byte	.LASF139
	.2byte	0x110
	.byte	0x21
	.4byte	0xc5
	.byte	0x7
	.byte	0x19
	.byte	0
	.uleb128 0x23
	.byte	0xe6
	.4byte	0x790
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x111
	.byte	0x7
	.4byte	0x6fa
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x112
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF140
	.byte	0x6
	.2byte	0x113
	.byte	0x3
	.4byte	0x771
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x13d
	.byte	0x5
	.4byte	0x7b6
	.uleb128 0x5
	.4byte	.LASF141
	.2byte	0x13e
	.byte	0x1b
	.4byte	0xc0
	.byte	0x20
	.byte	0
	.byte	0
	.uleb128 0x11
	.2byte	0x13c
	.byte	0x9
	.4byte	0x7d7
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x13f
	.byte	0x7
	.4byte	0x79d
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x140
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF142
	.byte	0x6
	.2byte	0x141
	.byte	0x3
	.4byte	0x7b6
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x149
	.byte	0x5
	.4byte	0x819
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x14a
	.byte	0x21
	.4byte	0xc5
	.byte	0xf
	.byte	0
	.uleb128 0x2a
	.string	"STR"
	.2byte	0x14b
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0xf
	.uleb128 0x5
	.4byte	.LASF135
	.2byte	0x14c
	.byte	0x21
	.4byte	0xc5
	.byte	0x10
	.byte	0x10
	.byte	0
	.uleb128 0x11
	.2byte	0x148
	.byte	0x9
	.4byte	0x83a
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x14d
	.byte	0x7
	.4byte	0x7e4
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x14e
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF143
	.byte	0x6
	.2byte	0x14f
	.byte	0x3
	.4byte	0x819
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x157
	.byte	0x5
	.4byte	0x898
	.uleb128 0x5
	.4byte	.LASF144
	.2byte	0x158
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF145
	.2byte	0x159
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF146
	.2byte	0x15a
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0x2
	.uleb128 0x5
	.4byte	.LASF147
	.2byte	0x15b
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0x3
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x15c
	.byte	0x21
	.4byte	0xc5
	.byte	0x1c
	.byte	0x4
	.byte	0
	.uleb128 0x11
	.2byte	0x156
	.byte	0x9
	.4byte	0x8b9
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x15d
	.byte	0x7
	.4byte	0x847
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x15e
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF148
	.byte	0x6
	.2byte	0x15f
	.byte	0x3
	.4byte	0x898
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x16d
	.byte	0x5
	.4byte	0x8fb
	.uleb128 0x5
	.4byte	.LASF149
	.2byte	0x16e
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF150
	.2byte	0x16f
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x170
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.2byte	0x16c
	.byte	0x9
	.4byte	0x91c
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x171
	.byte	0x7
	.4byte	0x8c6
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x172
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF151
	.byte	0x6
	.2byte	0x173
	.byte	0x3
	.4byte	0x8fb
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x17d
	.byte	0x5
	.4byte	0x95e
	.uleb128 0x5
	.4byte	.LASF152
	.2byte	0x17e
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF153
	.2byte	0x17f
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x180
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.2byte	0x17c
	.byte	0x9
	.4byte	0x97f
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x181
	.byte	0x7
	.4byte	0x929
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x182
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF154
	.byte	0x6
	.2byte	0x183
	.byte	0x3
	.4byte	0x95e
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x18d
	.byte	0x5
	.4byte	0x9c1
	.uleb128 0x5
	.4byte	.LASF155
	.2byte	0x18e
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF156
	.2byte	0x18f
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x190
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.2byte	0x18c
	.byte	0x9
	.4byte	0x9e2
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x191
	.byte	0x7
	.4byte	0x98c
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x192
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF157
	.byte	0x6
	.2byte	0x193
	.byte	0x3
	.4byte	0x9c1
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x19d
	.byte	0x5
	.4byte	0xa24
	.uleb128 0x5
	.4byte	.LASF158
	.2byte	0x19e
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF159
	.2byte	0x19f
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x1a0
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.2byte	0x19c
	.byte	0x9
	.4byte	0xa45
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x1a1
	.byte	0x7
	.4byte	0x9ef
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x1a2
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF160
	.byte	0x6
	.2byte	0x1a3
	.byte	0x3
	.4byte	0xa24
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x1ad
	.byte	0x5
	.4byte	0xa79
	.uleb128 0x5
	.4byte	.LASF161
	.2byte	0x1ae
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x1af
	.byte	0x21
	.4byte	0xc5
	.byte	0x1f
	.byte	0x1
	.byte	0
	.uleb128 0x11
	.2byte	0x1ac
	.byte	0x9
	.4byte	0xa9a
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x1b0
	.byte	0x7
	.4byte	0xa52
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x1b1
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF162
	.byte	0x6
	.2byte	0x1b2
	.byte	0x3
	.4byte	0xa79
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x1ba
	.byte	0x5
	.4byte	0xace
	.uleb128 0x5
	.4byte	.LASF163
	.2byte	0x1bb
	.byte	0x1b
	.4byte	0xc0
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x1bc
	.byte	0x21
	.4byte	0xc5
	.byte	0x18
	.byte	0x8
	.byte	0
	.uleb128 0x11
	.2byte	0x1b9
	.byte	0x9
	.4byte	0xaef
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x1bd
	.byte	0x7
	.4byte	0xaa7
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x1be
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF164
	.byte	0x6
	.2byte	0x1bf
	.byte	0x3
	.4byte	0xace
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x1c7
	.byte	0x5
	.4byte	0xb14
	.uleb128 0x2a
	.string	"CC"
	.2byte	0x1c8
	.byte	0x21
	.4byte	0xc5
	.byte	0x20
	.byte	0
	.byte	0
	.uleb128 0x11
	.2byte	0x1c6
	.byte	0x9
	.4byte	0xb35
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x1c9
	.byte	0x7
	.4byte	0xafc
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x1ca
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF165
	.byte	0x6
	.2byte	0x1cb
	.byte	0x3
	.4byte	0xb14
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x1d3
	.byte	0x5
	.4byte	0xb77
	.uleb128 0x5
	.4byte	.LASF144
	.2byte	0x1d4
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF146
	.2byte	0x1d5
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x1d6
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.2byte	0x1d2
	.byte	0x9
	.4byte	0xb98
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x1d7
	.byte	0x7
	.4byte	0xb42
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x1d8
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF166
	.byte	0x6
	.2byte	0x1d9
	.byte	0x3
	.4byte	0xb77
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x1e3
	.byte	0x5
	.4byte	0xbda
	.uleb128 0x5
	.4byte	.LASF145
	.2byte	0x1e4
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF147
	.2byte	0x1e5
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x1e6
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.2byte	0x1e2
	.byte	0x9
	.4byte	0xbfb
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x1e7
	.byte	0x7
	.4byte	0xba5
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x1e8
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF167
	.byte	0x6
	.2byte	0x1e9
	.byte	0x3
	.4byte	0xbda
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x1f3
	.byte	0x5
	.4byte	0xc3d
	.uleb128 0x5
	.4byte	.LASF168
	.2byte	0x1f4
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF169
	.2byte	0x1f5
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x1f6
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.2byte	0x1f2
	.byte	0x9
	.4byte	0xc5e
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x1f7
	.byte	0x7
	.4byte	0xc08
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x1f8
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF170
	.byte	0x6
	.2byte	0x1f9
	.byte	0x3
	.4byte	0xc3d
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x203
	.byte	0x5
	.4byte	0xca0
	.uleb128 0x5
	.4byte	.LASF171
	.2byte	0x204
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF172
	.2byte	0x205
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x206
	.byte	0x21
	.4byte	0xc5
	.byte	0x1e
	.byte	0x2
	.byte	0
	.uleb128 0x11
	.2byte	0x202
	.byte	0x9
	.4byte	0xcc1
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x207
	.byte	0x7
	.4byte	0xc6b
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x208
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF173
	.byte	0x6
	.2byte	0x209
	.byte	0x3
	.4byte	0xca0
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x212
	.byte	0x5
	.4byte	0xcf5
	.uleb128 0x5
	.4byte	.LASF174
	.2byte	0x213
	.byte	0x1b
	.4byte	0xc0
	.byte	0x10
	.byte	0
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x214
	.byte	0x21
	.4byte	0xc5
	.byte	0x10
	.byte	0x10
	.byte	0
	.uleb128 0x11
	.2byte	0x211
	.byte	0x9
	.4byte	0xd16
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x215
	.byte	0x7
	.4byte	0xcce
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x216
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF175
	.byte	0x6
	.2byte	0x217
	.byte	0x3
	.4byte	0xcf5
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x21f
	.byte	0x5
	.4byte	0xd3c
	.uleb128 0x5
	.4byte	.LASF176
	.2byte	0x220
	.byte	0x1b
	.4byte	0xc0
	.byte	0x20
	.byte	0
	.byte	0
	.uleb128 0x11
	.2byte	0x21e
	.byte	0x9
	.4byte	0xd5d
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x221
	.byte	0x7
	.4byte	0xd23
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x222
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF177
	.byte	0x6
	.2byte	0x223
	.byte	0x3
	.4byte	0xd3c
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x22b
	.byte	0x5
	.4byte	0xd9f
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x22c
	.byte	0x21
	.4byte	0xc5
	.byte	0xf
	.byte	0
	.uleb128 0x2a
	.string	"INT"
	.2byte	0x22d
	.byte	0x21
	.4byte	0xc5
	.byte	0x1
	.byte	0xf
	.uleb128 0x5
	.4byte	.LASF135
	.2byte	0x22e
	.byte	0x21
	.4byte	0xc5
	.byte	0x10
	.byte	0x10
	.byte	0
	.uleb128 0x11
	.2byte	0x22a
	.byte	0x9
	.4byte	0xdc0
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x22f
	.byte	0x7
	.4byte	0xd6a
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x230
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF178
	.byte	0x6
	.2byte	0x231
	.byte	0x3
	.4byte	0xd9f
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x239
	.byte	0x5
	.4byte	0xe02
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x23a
	.byte	0x21
	.4byte	0xc5
	.byte	0xf
	.byte	0
	.uleb128 0x2a
	.string	"ACK"
	.2byte	0x23b
	.byte	0x1b
	.4byte	0xc0
	.byte	0x1
	.byte	0xf
	.uleb128 0x5
	.4byte	.LASF135
	.2byte	0x23c
	.byte	0x21
	.4byte	0xc5
	.byte	0x10
	.byte	0x10
	.byte	0
	.uleb128 0x11
	.2byte	0x238
	.byte	0x9
	.4byte	0xe23
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x23d
	.byte	0x7
	.4byte	0xdcd
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x23e
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF179
	.byte	0x6
	.2byte	0x23f
	.byte	0x3
	.4byte	0xe02
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x247
	.byte	0x5
	.4byte	0xe57
	.uleb128 0x5
	.4byte	.LASF180
	.2byte	0x248
	.byte	0x21
	.4byte	0xc5
	.byte	0x10
	.byte	0
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x249
	.byte	0x21
	.4byte	0xc5
	.byte	0x10
	.byte	0x10
	.byte	0
	.uleb128 0x11
	.2byte	0x246
	.byte	0x9
	.4byte	0xe78
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x24a
	.byte	0x7
	.4byte	0xe30
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x24b
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF181
	.byte	0x6
	.2byte	0x24c
	.byte	0x3
	.4byte	0xe57
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x254
	.byte	0x5
	.4byte	0xeac
	.uleb128 0x5
	.4byte	.LASF163
	.2byte	0x255
	.byte	0x1b
	.4byte	0xc0
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF121
	.2byte	0x256
	.byte	0x21
	.4byte	0xc5
	.byte	0x18
	.byte	0x8
	.byte	0
	.uleb128 0x11
	.2byte	0x253
	.byte	0x9
	.4byte	0xecd
	.uleb128 0x7
	.4byte	.LASF122
	.2byte	0x257
	.byte	0x7
	.4byte	0xe85
	.uleb128 0x7
	.4byte	.LASF123
	.2byte	0x258
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x8
	.4byte	.LASF182
	.byte	0x6
	.2byte	0x259
	.byte	0x3
	.4byte	0xeac
	.uleb128 0xb
	.byte	0x18
	.byte	0x6
	.2byte	0x25f
	.byte	0x9
	.4byte	0xf39
	.uleb128 0x4
	.4byte	.LASF183
	.byte	0x6
	.2byte	0x260
	.byte	0x11
	.4byte	0xd16
	.byte	0
	.uleb128 0x4
	.4byte	.LASF184
	.byte	0x6
	.2byte	0x261
	.byte	0x11
	.4byte	0xd5d
	.byte	0x4
	.uleb128 0x4
	.4byte	.LASF185
	.byte	0x6
	.2byte	0x262
	.byte	0x12
	.4byte	0x6ee
	.byte	0x8
	.uleb128 0x4
	.4byte	.LASF186
	.byte	0x6
	.2byte	0x263
	.byte	0x10
	.4byte	0x790
	.byte	0xc
	.uleb128 0x4
	.4byte	.LASF187
	.byte	0x6
	.2byte	0x264
	.byte	0x14
	.4byte	0x7d7
	.byte	0x10
	.uleb128 0x4
	.4byte	.LASF188
	.byte	0x6
	.2byte	0x265
	.byte	0x12
	.4byte	0x83a
	.byte	0x14
	.byte	0
	.uleb128 0x8
	.4byte	.LASF189
	.byte	0x6
	.2byte	0x266
	.byte	0x3
	.4byte	0xeda
	.uleb128 0x32
	.2byte	0x100
	.2byte	0x268
	.4byte	0xf96
	.uleb128 0x4
	.4byte	.LASF190
	.byte	0x6
	.2byte	0x269
	.byte	0x13
	.4byte	0xdc0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF191
	.byte	0x6
	.2byte	0x26a
	.byte	0x13
	.4byte	0xe23
	.byte	0x4
	.uleb128 0x4
	.4byte	.LASF192
	.byte	0x6
	.2byte	0x26b
	.byte	0x11
	.4byte	0xe78
	.byte	0x8
	.uleb128 0x4
	.4byte	.LASF193
	.byte	0x6
	.2byte	0x26c
	.byte	0x14
	.4byte	0xecd
	.byte	0xc
	.uleb128 0x4
	.4byte	.LASF121
	.byte	0x6
	.2byte	0x26d
	.byte	0xe
	.4byte	0x3e8
	.byte	0x10
	.byte	0
	.uleb128 0x8
	.4byte	.LASF194
	.byte	0x6
	.2byte	0x26e
	.byte	0x3
	.4byte	0xf46
	.uleb128 0x32
	.2byte	0x31c
	.2byte	0x270
	.4byte	0x10aa
	.uleb128 0x4
	.4byte	.LASF195
	.byte	0x6
	.2byte	0x271
	.byte	0x18
	.4byte	0x5ed
	.byte	0
	.uleb128 0x4
	.4byte	.LASF196
	.byte	0x6
	.2byte	0x272
	.byte	0x18
	.4byte	0x647
	.byte	0x4
	.uleb128 0x4
	.4byte	.LASF197
	.byte	0x6
	.2byte	0x273
	.byte	0x17
	.4byte	0x6a1
	.byte	0x8
	.uleb128 0x4
	.4byte	.LASF198
	.byte	0x6
	.2byte	0x275
	.byte	0x19
	.4byte	0x10aa
	.byte	0xc
	.uleb128 0x4
	.4byte	.LASF199
	.byte	0x6
	.2byte	0x277
	.byte	0x12
	.4byte	0x8b9
	.byte	0x3c
	.uleb128 0x4
	.4byte	.LASF200
	.byte	0x6
	.2byte	0x278
	.byte	0x18
	.4byte	0x91c
	.byte	0x40
	.uleb128 0x4
	.4byte	.LASF201
	.byte	0x6
	.2byte	0x279
	.byte	0x18
	.4byte	0x97f
	.byte	0x44
	.uleb128 0x4
	.4byte	.LASF202
	.byte	0x6
	.2byte	0x27a
	.byte	0x18
	.4byte	0x9e2
	.byte	0x48
	.uleb128 0x4
	.4byte	.LASF203
	.byte	0x6
	.2byte	0x27b
	.byte	0x18
	.4byte	0xa45
	.byte	0x4c
	.uleb128 0x4
	.4byte	.LASF204
	.byte	0x6
	.2byte	0x27c
	.byte	0x15
	.4byte	0xa9a
	.byte	0x50
	.uleb128 0x4
	.4byte	.LASF205
	.byte	0x6
	.2byte	0x27d
	.byte	0x16
	.4byte	0xaef
	.byte	0x54
	.uleb128 0x4
	.4byte	.LASF206
	.byte	0x6
	.2byte	0x27e
	.byte	0x13
	.4byte	0xb35
	.byte	0x58
	.uleb128 0x4
	.4byte	.LASF207
	.byte	0x6
	.2byte	0x27f
	.byte	0x14
	.4byte	0xb98
	.byte	0x5c
	.uleb128 0x4
	.4byte	.LASF208
	.byte	0x6
	.2byte	0x280
	.byte	0x14
	.4byte	0xbfb
	.byte	0x60
	.uleb128 0x4
	.4byte	.LASF209
	.byte	0x6
	.2byte	0x281
	.byte	0x17
	.4byte	0xc5e
	.byte	0x64
	.uleb128 0x4
	.4byte	.LASF210
	.byte	0x6
	.2byte	0x282
	.byte	0x17
	.4byte	0xcc1
	.byte	0x68
	.uleb128 0x4
	.4byte	.LASF121
	.byte	0x6
	.2byte	0x283
	.byte	0xe
	.4byte	0x10ba
	.byte	0x6c
	.uleb128 0x3f
	.4byte	.LASF211
	.byte	0x6
	.2byte	0x285
	.byte	0x19
	.4byte	0x10ca
	.2byte	0x11c
	.byte	0
	.uleb128 0xc
	.4byte	0xf39
	.4byte	0x10ba
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xc
	.4byte	0xb4
	.4byte	0x10ca
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x2b
	.byte	0
	.uleb128 0xc
	.4byte	0xf96
	.4byte	0x10da
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x8
	.4byte	.LASF212
	.byte	0x6
	.2byte	0x286
	.byte	0x3
	.4byte	0xfa3
	.uleb128 0xb
	.byte	0x4
	.byte	0x6
	.2byte	0x28d
	.byte	0x9
	.4byte	0x112a
	.uleb128 0x4
	.4byte	.LASF213
	.byte	0x6
	.2byte	0x28e
	.byte	0x1e
	.4byte	0xa3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF214
	.byte	0x6
	.2byte	0x28f
	.byte	0x1e
	.4byte	0xa3
	.byte	0x1
	.uleb128 0x4
	.4byte	.LASF215
	.byte	0x6
	.2byte	0x290
	.byte	0x1e
	.4byte	0xa3
	.byte	0x2
	.uleb128 0x4
	.4byte	.LASF216
	.byte	0x6
	.2byte	0x291
	.byte	0x1e
	.4byte	0xa3
	.byte	0x3
	.byte	0
	.uleb128 0x11
	.2byte	0x28c
	.byte	0x5
	.4byte	0x114b
	.uleb128 0x7
	.4byte	.LASF217
	.2byte	0x292
	.byte	0xb
	.4byte	0x10e7
	.uleb128 0x7
	.4byte	.LASF218
	.2byte	0x293
	.byte	0x1b
	.4byte	0xc0
	.byte	0
	.uleb128 0xb
	.byte	0x60
	.byte	0x6
	.2byte	0x28a
	.byte	0x9
	.4byte	0x1260
	.uleb128 0x4
	.4byte	.LASF219
	.byte	0x6
	.2byte	0x28b
	.byte	0x17
	.4byte	0xc0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF220
	.byte	0x6
	.2byte	0x294
	.byte	0x7
	.4byte	0x112a
	.byte	0x4
	.uleb128 0x4
	.4byte	.LASF221
	.byte	0x6
	.2byte	0x295
	.byte	0x17
	.4byte	0xc0
	.byte	0x8
	.uleb128 0x4
	.4byte	.LASF222
	.byte	0x6
	.2byte	0x296
	.byte	0x17
	.4byte	0xc0
	.byte	0xc
	.uleb128 0x4
	.4byte	.LASF223
	.byte	0x6
	.2byte	0x297
	.byte	0x17
	.4byte	0xc0
	.byte	0x10
	.uleb128 0x4
	.4byte	.LASF224
	.byte	0x6
	.2byte	0x298
	.byte	0x17
	.4byte	0x408
	.byte	0x14
	.uleb128 0x4
	.4byte	.LASF225
	.byte	0x6
	.2byte	0x299
	.byte	0x17
	.4byte	0xc0
	.byte	0x18
	.uleb128 0x4
	.4byte	.LASF226
	.byte	0x6
	.2byte	0x29a
	.byte	0x17
	.4byte	0xc0
	.byte	0x1c
	.uleb128 0x4
	.4byte	.LASF227
	.byte	0x6
	.2byte	0x29b
	.byte	0x1d
	.4byte	0xc5
	.byte	0x20
	.uleb128 0x4
	.4byte	.LASF228
	.byte	0x6
	.2byte	0x29c
	.byte	0x1d
	.4byte	0xc5
	.byte	0x24
	.uleb128 0x4
	.4byte	.LASF229
	.byte	0x6
	.2byte	0x29d
	.byte	0x1d
	.4byte	0xc5
	.byte	0x28
	.uleb128 0x4
	.4byte	.LASF230
	.byte	0x6
	.2byte	0x29e
	.byte	0x1d
	.4byte	0xc5
	.byte	0x2c
	.uleb128 0x4
	.4byte	.LASF231
	.byte	0x6
	.2byte	0x29f
	.byte	0x17
	.4byte	0xc0
	.byte	0x30
	.uleb128 0x4
	.4byte	.LASF232
	.byte	0x6
	.2byte	0x2a0
	.byte	0x17
	.4byte	0xc0
	.byte	0x34
	.uleb128 0x4
	.4byte	.LASF233
	.byte	0x6
	.2byte	0x2a1
	.byte	0x17
	.4byte	0x1270
	.byte	0x38
	.uleb128 0x4
	.4byte	.LASF234
	.byte	0x6
	.2byte	0x2a2
	.byte	0x17
	.4byte	0xc0
	.byte	0x50
	.uleb128 0x4
	.4byte	.LASF235
	.byte	0x6
	.2byte	0x2a3
	.byte	0x17
	.4byte	0xc0
	.byte	0x54
	.uleb128 0x4
	.4byte	.LASF236
	.byte	0x6
	.2byte	0x2a4
	.byte	0x17
	.4byte	0xc0
	.byte	0x58
	.uleb128 0x4
	.4byte	.LASF237
	.byte	0x6
	.2byte	0x2a5
	.byte	0x17
	.4byte	0xc0
	.byte	0x5c
	.byte	0
	.uleb128 0xc
	.4byte	0xc0
	.4byte	0x1270
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x5
	.byte	0
	.uleb128 0x1d
	.4byte	0x1260
	.uleb128 0x8
	.4byte	.LASF238
	.byte	0x6
	.2byte	0x2a6
	.byte	0x3
	.4byte	0x114b
	.uleb128 0xc
	.4byte	0xb4
	.4byte	0x1292
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x29
	.byte	0x7
	.4byte	0x2d
	.byte	0x7
	.2byte	0x74b
	.4byte	0x14a5
	.uleb128 0x1
	.4byte	.LASF239
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF240
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF241
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF242
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF243
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF244
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF245
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF246
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF247
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF248
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF249
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF250
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF251
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF252
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF253
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF254
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF255
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF256
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF257
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF258
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF259
	.byte	0x38
	.uleb128 0x1
	.4byte	.LASF260
	.byte	0x39
	.uleb128 0x1
	.4byte	.LASF261
	.byte	0x3a
	.uleb128 0x1
	.4byte	.LASF262
	.byte	0x3b
	.uleb128 0x1
	.4byte	.LASF263
	.byte	0x3c
	.uleb128 0x1
	.4byte	.LASF264
	.byte	0x3d
	.uleb128 0x1
	.4byte	.LASF265
	.byte	0x3e
	.uleb128 0x1
	.4byte	.LASF266
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF267
	.byte	0x41
	.uleb128 0x1
	.4byte	.LASF268
	.byte	0x42
	.uleb128 0x1
	.4byte	.LASF269
	.byte	0x4e
	.uleb128 0x1
	.4byte	.LASF270
	.byte	0x4f
	.uleb128 0x1
	.4byte	.LASF271
	.byte	0x60
	.uleb128 0x1
	.4byte	.LASF272
	.byte	0x61
	.uleb128 0x1
	.4byte	.LASF273
	.byte	0x62
	.uleb128 0x1
	.4byte	.LASF274
	.byte	0x64
	.uleb128 0x1
	.4byte	.LASF275
	.byte	0x65
	.uleb128 0x1
	.4byte	.LASF276
	.byte	0x66
	.uleb128 0x1
	.4byte	.LASF277
	.byte	0x6a
	.uleb128 0x1
	.4byte	.LASF278
	.byte	0x6c
	.uleb128 0x1
	.4byte	.LASF279
	.byte	0x6d
	.uleb128 0x1
	.4byte	.LASF280
	.byte	0x6e
	.uleb128 0x1
	.4byte	.LASF281
	.byte	0x6f
	.uleb128 0x1
	.4byte	.LASF282
	.byte	0x71
	.uleb128 0x1
	.4byte	.LASF283
	.byte	0x72
	.uleb128 0x1
	.4byte	.LASF284
	.byte	0x73
	.uleb128 0x1
	.4byte	.LASF285
	.byte	0x74
	.uleb128 0x1
	.4byte	.LASF286
	.byte	0x75
	.uleb128 0x1
	.4byte	.LASF287
	.byte	0x76
	.uleb128 0x1
	.4byte	.LASF288
	.byte	0x77
	.uleb128 0x1
	.4byte	.LASF289
	.byte	0x79
	.uleb128 0x1
	.4byte	.LASF290
	.byte	0x7a
	.uleb128 0x1
	.4byte	.LASF291
	.byte	0x90
	.uleb128 0x1
	.4byte	.LASF292
	.byte	0x91
	.uleb128 0x1
	.4byte	.LASF293
	.byte	0x92
	.uleb128 0x1
	.4byte	.LASF294
	.byte	0x98
	.uleb128 0x1
	.4byte	.LASF295
	.byte	0x9d
	.uleb128 0x1
	.4byte	.LASF296
	.byte	0x9e
	.uleb128 0x1
	.4byte	.LASF297
	.byte	0x9f
	.uleb128 0x1
	.4byte	.LASF298
	.byte	0xa0
	.uleb128 0x1
	.4byte	.LASF299
	.byte	0xa1
	.uleb128 0x1
	.4byte	.LASF300
	.byte	0xa4
	.uleb128 0x1
	.4byte	.LASF301
	.byte	0xa5
	.uleb128 0x1
	.4byte	.LASF302
	.byte	0xa6
	.uleb128 0x1
	.4byte	.LASF303
	.byte	0xa9
	.uleb128 0x1
	.4byte	.LASF304
	.byte	0xaa
	.uleb128 0x1
	.4byte	.LASF305
	.byte	0xab
	.uleb128 0x1
	.4byte	.LASF306
	.byte	0xac
	.uleb128 0x1
	.4byte	.LASF307
	.byte	0xad
	.uleb128 0x1
	.4byte	.LASF308
	.byte	0xae
	.uleb128 0x1
	.4byte	.LASF309
	.byte	0xaf
	.uleb128 0x1
	.4byte	.LASF310
	.byte	0xb2
	.uleb128 0x1
	.4byte	.LASF311
	.byte	0xb3
	.uleb128 0x1
	.4byte	.LASF312
	.byte	0xb4
	.uleb128 0x1
	.4byte	.LASF313
	.byte	0xb7
	.uleb128 0x1
	.4byte	.LASF314
	.byte	0xb8
	.uleb128 0x1
	.4byte	.LASF315
	.byte	0xd0
	.uleb128 0x1
	.4byte	.LASF316
	.byte	0xd1
	.uleb128 0x1
	.4byte	.LASF317
	.byte	0xd1
	.uleb128 0x1
	.4byte	.LASF318
	.byte	0xd2
	.uleb128 0x1
	.4byte	.LASF319
	.byte	0xd3
	.uleb128 0x1
	.4byte	.LASF320
	.byte	0xd4
	.uleb128 0x1
	.4byte	.LASF321
	.byte	0xd5
	.uleb128 0x1
	.4byte	.LASF322
	.byte	0xd5
	.uleb128 0x1
	.4byte	.LASF323
	.byte	0xd6
	.uleb128 0x40
	.4byte	.LASF324
	.2byte	0x8000
	.byte	0
	.uleb128 0x8
	.4byte	.LASF325
	.byte	0x7
	.2byte	0x7d9
	.byte	0x3
	.4byte	0x1292
	.uleb128 0x10
	.4byte	.LASF326
	.byte	0x8
	.byte	0x2e
	.byte	0x10
	.4byte	0x14be
	.uleb128 0x15
	.4byte	0x14c3
	.uleb128 0x2f
	.4byte	0x14ce
	.uleb128 0x14
	.4byte	0x3db
	.byte	0
	.uleb128 0x1b
	.byte	0x5
	.4byte	0x42
	.byte	0x9
	.byte	0x5e
	.4byte	0x14f3
	.uleb128 0x19
	.4byte	.LASF327
	.sleb128 -3
	.uleb128 0x19
	.4byte	.LASF328
	.sleb128 -2
	.uleb128 0x19
	.4byte	.LASF329
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF330
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF331
	.byte	0x9
	.byte	0x63
	.byte	0x3
	.4byte	0x14ce
	.uleb128 0x15
	.4byte	0x1509
	.uleb128 0x31
	.4byte	0x14ff
	.uleb128 0x41
	.uleb128 0x15
	.4byte	0xb4
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x1
	.byte	0x45
	.4byte	0x1570
	.uleb128 0x1
	.4byte	.LASF332
	.byte	0
	.uleb128 0x1
	.4byte	.LASF333
	.byte	0
	.uleb128 0x1
	.4byte	.LASF334
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF335
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF336
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF337
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF338
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF339
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF340
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF341
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF342
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF343
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF344
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF345
	.byte	0x9
	.byte	0
	.uleb128 0x10
	.4byte	.LASF346
	.byte	0x1
	.byte	0x56
	.byte	0x3
	.4byte	0x150f
	.uleb128 0xc
	.4byte	0x3db
	.4byte	0x158c
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF347
	.byte	0x58
	.byte	0x17
	.4byte	0x157c
	.uleb128 0x5
	.byte	0x3
	.4byte	g_dma_irq_table
	.uleb128 0xc
	.4byte	0x14a5
	.4byte	0x15ad
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF348
	.byte	0x61
	.byte	0x18
	.4byte	0x159d
	.uleb128 0x5
	.byte	0x3
	.4byte	g_dma_clk_table
	.uleb128 0xc
	.4byte	0x15ce
	.4byte	0x15ce
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x15
	.4byte	0x593
	.uleb128 0x1a
	.4byte	.LASF349
	.byte	0x6a
	.byte	0x1f
	.4byte	0x15be
	.uleb128 0x5
	.byte	0x3
	.4byte	g_dma_reg_table
	.uleb128 0xc
	.4byte	0x1570
	.4byte	0x15f4
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x13
	.4byte	.LASF350
	.2byte	0x11a
	.byte	0x16
	.4byte	0x15e4
	.uleb128 0x5
	.byte	0x3
	.4byte	g_pdma_channel_map_table
	.uleb128 0xc
	.4byte	0x1616
	.4byte	0x1616
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x15
	.4byte	0xf96
	.uleb128 0x13
	.4byte	.LASF351
	.2byte	0x122
	.byte	0x1d
	.4byte	0x1606
	.uleb128 0x5
	.byte	0x3
	.4byte	g_pdma_status_regbase_table
	.uleb128 0xc
	.4byte	0x163d
	.4byte	0x163d
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x15
	.4byte	0xf39
	.uleb128 0x13
	.4byte	.LASF352
	.2byte	0x129
	.byte	0x1d
	.4byte	0x162d
	.uleb128 0x5
	.byte	0x3
	.4byte	g_pdma_cfg_regbase_table
	.uleb128 0xb
	.byte	0x8
	.byte	0x1
	.2byte	0x130
	.byte	0x9
	.4byte	0x167b
	.uleb128 0x4
	.4byte	.LASF353
	.byte	0x1
	.2byte	0x131
	.byte	0x15
	.4byte	0x22f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF354
	.byte	0x1
	.2byte	0x132
	.byte	0xb
	.4byte	0x7f
	.byte	0x4
	.byte	0
	.uleb128 0x8
	.4byte	.LASF355
	.byte	0x1
	.2byte	0x133
	.byte	0x3
	.4byte	0x1654
	.uleb128 0xc
	.4byte	0x167b
	.4byte	0x1698
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x13
	.4byte	.LASF356
	.2byte	0x135
	.byte	0x1d
	.4byte	0x1688
	.uleb128 0x5
	.byte	0x3
	.4byte	g_pdma_callback
	.uleb128 0xc
	.4byte	0xa3
	.4byte	0x16ba
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x1d
	.4byte	0x16aa
	.uleb128 0x13
	.4byte	.LASF357
	.2byte	0x136
	.byte	0x19
	.4byte	0x16ba
	.uleb128 0x5
	.byte	0x3
	.4byte	g_pdma_init_status
	.uleb128 0xc
	.4byte	0x1570
	.4byte	0x16e1
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x5
	.byte	0
	.uleb128 0x13
	.4byte	.LASF358
	.2byte	0x261
	.byte	0x16
	.4byte	0x16d1
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vdma_channel_map_table
	.uleb128 0xc
	.4byte	0x1703
	.4byte	0x1703
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x5
	.byte	0
	.uleb128 0x15
	.4byte	0x1275
	.uleb128 0x42
	.4byte	.LASF476
	.byte	0x1
	.2byte	0x26b
	.byte	0x12
	.4byte	0x16f3
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vdma_regbase_table
	.uleb128 0xb
	.byte	0x8
	.byte	0x1
	.2byte	0x274
	.byte	0x9
	.4byte	0x1742
	.uleb128 0x4
	.4byte	.LASF353
	.byte	0x1
	.2byte	0x275
	.byte	0x15
	.4byte	0x326
	.byte	0
	.uleb128 0x4
	.4byte	.LASF354
	.byte	0x1
	.2byte	0x276
	.byte	0xb
	.4byte	0x7f
	.byte	0x4
	.byte	0
	.uleb128 0x8
	.4byte	.LASF359
	.byte	0x1
	.2byte	0x277
	.byte	0x3
	.4byte	0x171b
	.uleb128 0xc
	.4byte	0x1742
	.4byte	0x175f
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x5
	.byte	0
	.uleb128 0x13
	.4byte	.LASF360
	.2byte	0x279
	.byte	0x1d
	.4byte	0x174f
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vdma_callback
	.uleb128 0xc
	.4byte	0xa3
	.4byte	0x1781
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x5
	.byte	0
	.uleb128 0x1d
	.4byte	0x1771
	.uleb128 0x13
	.4byte	.LASF361
	.2byte	0x27a
	.byte	0x19
	.4byte	0x1781
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vdma_init_status
	.uleb128 0xc
	.4byte	0xb4
	.4byte	0x17a8
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x5
	.byte	0
	.uleb128 0x18
	.4byte	.LASF369
	.2byte	0x4ee
	.byte	0x11
	.4byte	0x1798
	.uleb128 0x29
	.byte	0x7
	.4byte	0x2d
	.byte	0x1
	.2byte	0x4f7
	.4byte	0x17e6
	.uleb128 0x1
	.4byte	.LASF362
	.byte	0
	.uleb128 0x1
	.4byte	.LASF363
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF364
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF365
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF366
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF367
	.byte	0x5
	.byte	0
	.uleb128 0x8
	.4byte	.LASF368
	.byte	0x1
	.2byte	0x4fe
	.byte	0x3
	.4byte	0x17b4
	.uleb128 0xc
	.4byte	0x15ce
	.4byte	0x1803
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x18
	.4byte	.LASF370
	.2byte	0x500
	.byte	0x1f
	.4byte	0x17f3
	.uleb128 0x18
	.4byte	.LASF371
	.2byte	0x546
	.byte	0x11
	.4byte	0x1282
	.uleb128 0x29
	.byte	0x7
	.4byte	0x2d
	.byte	0x1
	.2byte	0x54d
	.4byte	0x1841
	.uleb128 0x1
	.4byte	.LASF372
	.byte	0
	.uleb128 0x1
	.4byte	.LASF373
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF374
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF375
	.byte	0x3
	.byte	0
	.uleb128 0x8
	.4byte	.LASF376
	.byte	0x1
	.2byte	0x552
	.byte	0x3
	.4byte	0x181b
	.uleb128 0xc
	.4byte	0x15ce
	.4byte	0x185e
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x18
	.4byte	.LASF377
	.2byte	0x554
	.byte	0x1f
	.4byte	0x184e
	.uleb128 0x2b
	.4byte	.LASF378
	.byte	0xa
	.byte	0x1f
	.byte	0x8
	.4byte	0x7f
	.4byte	0x188a
	.uleb128 0x14
	.4byte	0x81
	.uleb128 0x14
	.4byte	0x1504
	.uleb128 0x14
	.4byte	0x49
	.byte	0
	.uleb128 0x2b
	.4byte	.LASF379
	.byte	0xb
	.byte	0x2a
	.byte	0xa
	.4byte	0xb4
	.4byte	0x18a0
	.uleb128 0x14
	.4byte	0xb4
	.byte	0
	.uleb128 0x24
	.4byte	.LASF380
	.byte	0x8
	.byte	0x3c
	.4byte	0x18b1
	.uleb128 0x14
	.4byte	0x3db
	.byte	0
	.uleb128 0x24
	.4byte	.LASF381
	.byte	0x8
	.byte	0x3b
	.4byte	0x18c7
	.uleb128 0x14
	.4byte	0x3db
	.uleb128 0x14
	.4byte	0x14b2
	.byte	0
	.uleb128 0x2b
	.4byte	.LASF382
	.byte	0xb
	.byte	0x29
	.byte	0xa
	.4byte	0xb4
	.4byte	0x18dd
	.uleb128 0x14
	.4byte	0xb4
	.byte	0
	.uleb128 0x2b
	.4byte	.LASF383
	.byte	0x9
	.byte	0x7d
	.byte	0x14
	.4byte	0x14f3
	.4byte	0x18f3
	.uleb128 0x14
	.4byte	0x14a5
	.byte	0
	.uleb128 0x24
	.4byte	.LASF384
	.byte	0xc
	.byte	0x44
	.4byte	0x190e
	.uleb128 0x14
	.4byte	0x92
	.uleb128 0x14
	.4byte	0x92
	.uleb128 0x14
	.4byte	0x42
	.byte	0
	.uleb128 0x24
	.4byte	.LASF385
	.byte	0x8
	.byte	0x3f
	.4byte	0x191f
	.uleb128 0x14
	.4byte	0xb4
	.byte	0
	.uleb128 0x24
	.4byte	.LASF386
	.byte	0x8
	.byte	0x3e
	.4byte	0x1930
	.uleb128 0x14
	.4byte	0x150a
	.byte	0
	.uleb128 0x30
	.4byte	.LASF443
	.2byte	0x559
	.byte	0x6
	.4byte	.LFB52
	.4byte	.LFE52-.LFB52
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1a24
	.uleb128 0x3
	.4byte	.LASF395
	.2byte	0x559
	.byte	0x2e
	.4byte	0x3db
	.4byte	.LLST9
	.uleb128 0x6
	.4byte	.LASF387
	.2byte	0x55b
	.byte	0xe
	.4byte	0xb4
	.4byte	.LLST10
	.uleb128 0x6
	.4byte	.LASF354
	.2byte	0x55c
	.byte	0xb
	.4byte	0x7f
	.4byte	.LLST11
	.uleb128 0x6
	.4byte	.LASF388
	.2byte	0x55d
	.byte	0x1a
	.4byte	0x1616
	.4byte	.LLST12
	.uleb128 0x6
	.4byte	.LASF389
	.2byte	0x55e
	.byte	0x15
	.4byte	0x22f
	.4byte	.LLST13
	.uleb128 0x6
	.4byte	.LASF390
	.2byte	0x55f
	.byte	0x1e
	.4byte	0x1841
	.4byte	.LLST14
	.uleb128 0x25
	.4byte	.LBB6
	.4byte	.LBE6-.LBB6
	.4byte	0x19fa
	.uleb128 0x2c
	.string	"exp"
	.2byte	0x562
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x13
	.4byte	.LASF391
	.2byte	0x562
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0xe
	.4byte	.LVL28
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x562
	.byte	0
	.byte	0
	.uleb128 0x33
	.4byte	.LVL32
	.4byte	0x1a09
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x33
	.4byte	.LVL40
	.4byte	0x1a18
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x43
	.4byte	.LVL44
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xc
	.4byte	0x8d
	.4byte	0x1a34
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x28
	.4byte	0x1a24
	.uleb128 0xc
	.4byte	0x8d
	.4byte	0x1a49
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x42
	.byte	0
	.uleb128 0x28
	.4byte	0x1a39
	.uleb128 0x44
	.4byte	.LASF477
	.byte	0x1
	.2byte	0x506
	.byte	0x6
	.byte	0x1
	.4byte	0x1aee
	.uleb128 0x45
	.4byte	.LASF395
	.byte	0x1
	.2byte	0x506
	.byte	0x2f
	.4byte	0x3db
	.uleb128 0x18
	.4byte	.LASF392
	.2byte	0x508
	.byte	0xe
	.4byte	0xb4
	.uleb128 0x18
	.4byte	.LASF354
	.2byte	0x509
	.byte	0xb
	.4byte	0x7f
	.uleb128 0x18
	.4byte	.LASF393
	.2byte	0x50a
	.byte	0x16
	.4byte	0x1703
	.uleb128 0x18
	.4byte	.LASF394
	.2byte	0x50b
	.byte	0x15
	.4byte	0x326
	.uleb128 0x18
	.4byte	.LASF390
	.2byte	0x50c
	.byte	0x1f
	.4byte	0x17e6
	.uleb128 0x34
	.uleb128 0x2c
	.string	"exp"
	.2byte	0x50f
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.3
	.uleb128 0x13
	.4byte	.LASF391
	.2byte	0x50f
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.2
	.uleb128 0x46
	.4byte	.LVL72
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.2
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x50f
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF396
	.2byte	0x4cc
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB50
	.4byte	.LFE50-.LFB50
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1b25
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x4cc
	.byte	0x31
	.4byte	0x28d
	.4byte	.LLST133
	.uleb128 0x18
	.4byte	.LASF393
	.2byte	0x4ce
	.byte	0x16
	.4byte	0x1703
	.byte	0
	.uleb128 0x9
	.4byte	.LASF397
	.2byte	0x4bc
	.byte	0x5
	.4byte	0x21c
	.4byte	.LFB49
	.4byte	.LFE49-.LFB49
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1b60
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x4bc
	.byte	0x29
	.4byte	0x28d
	.4byte	.LLST131
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x4be
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST132
	.byte	0
	.uleb128 0x9
	.4byte	.LASF398
	.2byte	0x4aa
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB48
	.4byte	.LFE48-.LFB48
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1bd1
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x4aa
	.byte	0x35
	.4byte	0x28d
	.4byte	.LLST128
	.uleb128 0x3
	.4byte	.LASF399
	.2byte	0x4aa
	.byte	0x4e
	.4byte	0x326
	.4byte	.LLST129
	.uleb128 0x3
	.4byte	.LASF400
	.2byte	0x4aa
	.byte	0x5e
	.4byte	0x7f
	.4byte	.LLST130
	.uleb128 0xf
	.4byte	.LVL412
	.4byte	0x2ec7
	.4byte	0x1bbf
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xe
	.4byte	.LVL413
	.4byte	0x2d2f
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF401
	.2byte	0x498
	.byte	0xa8
	.4byte	0x2be
	.4byte	.LFB47
	.4byte	.LFE47-.LFB47
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1c1a
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x498
	.byte	0xd0
	.4byte	0x28d
	.4byte	.LLST126
	.uleb128 0x1c
	.4byte	.LASF402
	.2byte	0x498
	.byte	0xe3
	.4byte	0x150a
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x49a
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST127
	.byte	0
	.uleb128 0x9
	.4byte	.LASF403
	.2byte	0x487
	.byte	0xa8
	.4byte	0x2be
	.4byte	.LFB46
	.4byte	.LFE46-.LFB46
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1c63
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x487
	.byte	0xcf
	.4byte	0x28d
	.4byte	.LLST124
	.uleb128 0x1c
	.4byte	.LASF404
	.2byte	0x487
	.byte	0xe2
	.4byte	0x150a
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x489
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST125
	.byte	0
	.uleb128 0x9
	.4byte	.LASF405
	.2byte	0x46d
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB45
	.4byte	.LFE45-.LFB45
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1cbe
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x46d
	.byte	0x34
	.4byte	0x28d
	.4byte	.LLST89
	.uleb128 0x3
	.4byte	.LASF406
	.2byte	0x46d
	.byte	0x46
	.4byte	0xa8
	.4byte	.LLST90
	.uleb128 0x6
	.4byte	.LASF407
	.2byte	0x46f
	.byte	0xd
	.4byte	0x97
	.4byte	.LLST91
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x470
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST92
	.byte	0
	.uleb128 0x9
	.4byte	.LASF408
	.2byte	0x45b
	.byte	0xa8
	.4byte	0x2be
	.4byte	.LFB44
	.4byte	.LFE44-.LFB44
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1d07
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x45b
	.byte	0xcf
	.4byte	0x28d
	.4byte	.LLST87
	.uleb128 0x1c
	.4byte	.LASF409
	.2byte	0x45b
	.byte	0xe2
	.4byte	0x150a
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x45d
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST88
	.byte	0
	.uleb128 0x9
	.4byte	.LASF410
	.2byte	0x449
	.byte	0xa8
	.4byte	0x2be
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1d50
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x449
	.byte	0xce
	.4byte	0x28d
	.4byte	.LLST85
	.uleb128 0x1c
	.4byte	.LASF411
	.2byte	0x449
	.byte	0xe1
	.4byte	0x150a
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x44b
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST86
	.byte	0
	.uleb128 0x9
	.4byte	.LASF412
	.2byte	0x438
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1d99
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x438
	.byte	0x3c
	.4byte	0x28d
	.4byte	.LLST83
	.uleb128 0x1c
	.4byte	.LASF413
	.2byte	0x438
	.byte	0x4f
	.4byte	0x150a
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x43a
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST84
	.byte	0
	.uleb128 0x9
	.4byte	.LASF414
	.2byte	0x425
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1df2
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x425
	.byte	0x3f
	.4byte	0x28d
	.4byte	.LLST80
	.uleb128 0x1c
	.4byte	.LASF415
	.2byte	0x425
	.byte	0x52
	.4byte	0x150a
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x6
	.4byte	.LASF407
	.2byte	0x427
	.byte	0xd
	.4byte	0x97
	.4byte	.LLST81
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x428
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST82
	.byte	0
	.uleb128 0x9
	.4byte	.LASF416
	.2byte	0x3ff
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1ede
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x3ff
	.byte	0x38
	.4byte	0x28d
	.4byte	.LLST116
	.uleb128 0x3
	.4byte	.LASF417
	.2byte	0x3ff
	.byte	0x4a
	.4byte	0x1ede
	.4byte	.LLST117
	.uleb128 0x3
	.4byte	.LASF45
	.2byte	0x3ff
	.byte	0x59
	.4byte	0xb4
	.4byte	.LLST118
	.uleb128 0x6
	.4byte	.LASF407
	.2byte	0x401
	.byte	0xd
	.4byte	0x97
	.4byte	.LLST119
	.uleb128 0x6
	.4byte	.LASF418
	.2byte	0x402
	.byte	0xe
	.4byte	0x1ede
	.4byte	.LLST120
	.uleb128 0x6
	.4byte	.LASF419
	.2byte	0x403
	.byte	0xe
	.4byte	0xb4
	.4byte	.LLST121
	.uleb128 0x6
	.4byte	.LASF420
	.2byte	0x404
	.byte	0xe
	.4byte	0xb4
	.4byte	.LLST122
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x405
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST123
	.uleb128 0x12
	.4byte	.LVL379
	.4byte	0x188a
	.uleb128 0xf
	.4byte	.LVL382
	.4byte	0x186a
	.4byte	0x1eb0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0x12
	.4byte	.LVL384
	.4byte	0x188a
	.uleb128 0x12
	.4byte	.LVL387
	.4byte	0x186a
	.uleb128 0xe
	.4byte	.LVL388
	.4byte	0x1c63
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -20
	.byte	0x6
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x6
	.byte	0x78
	.sleb128 0
	.byte	0x40
	.byte	0x24
	.byte	0x40
	.byte	0x25
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	0x97
	.uleb128 0x9
	.4byte	.LASF421
	.2byte	0x3e9
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1f5c
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x3e9
	.byte	0x33
	.4byte	0x28d
	.4byte	.LLST112
	.uleb128 0x3
	.4byte	.LASF417
	.2byte	0x3e9
	.byte	0x46
	.4byte	0x150a
	.4byte	.LLST113
	.uleb128 0x6
	.4byte	.LASF418
	.2byte	0x3eb
	.byte	0xf
	.4byte	0x150a
	.4byte	.LLST114
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x3ec
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST115
	.uleb128 0x12
	.4byte	.LVL362
	.4byte	0x188a
	.uleb128 0xe
	.4byte	.LVL364
	.4byte	0x1c63
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF422
	.2byte	0x3d3
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1fd5
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x3d3
	.byte	0x2c
	.4byte	0x28d
	.4byte	.LLST108
	.uleb128 0x3
	.4byte	.LASF417
	.2byte	0x3d3
	.byte	0x3e
	.4byte	0x1ede
	.4byte	.LLST109
	.uleb128 0x6
	.4byte	.LASF418
	.2byte	0x3d5
	.byte	0xe
	.4byte	0x1ede
	.4byte	.LLST110
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x3d6
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST111
	.uleb128 0x12
	.4byte	.LVL350
	.4byte	0x188a
	.uleb128 0xe
	.4byte	.LVL352
	.4byte	0x1c63
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF423
	.2byte	0x3b0
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x20b2
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x3b0
	.byte	0x39
	.4byte	0x28d
	.4byte	.LLST101
	.uleb128 0x3
	.4byte	.LASF417
	.2byte	0x3b0
	.byte	0x4b
	.4byte	0x1ede
	.4byte	.LLST102
	.uleb128 0x3
	.4byte	.LASF45
	.2byte	0x3b0
	.byte	0x5a
	.4byte	0xb4
	.4byte	.LLST103
	.uleb128 0x6
	.4byte	.LASF424
	.2byte	0x3b2
	.byte	0xe
	.4byte	0x1ede
	.4byte	.LLST104
	.uleb128 0x6
	.4byte	.LASF420
	.2byte	0x3b3
	.byte	0xe
	.4byte	0xb4
	.4byte	.LLST105
	.uleb128 0x6
	.4byte	.LASF425
	.2byte	0x3b4
	.byte	0xe
	.4byte	0xb4
	.4byte	.LLST106
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x3b5
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST107
	.uleb128 0x12
	.4byte	.LVL334
	.4byte	0x188a
	.uleb128 0xf
	.4byte	.LVL336
	.4byte	0x186a
	.4byte	0x2084
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -20
	.byte	0x6
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0x91
	.sleb128 -16
	.byte	0x6
	.byte	0
	.uleb128 0x12
	.4byte	.LVL338
	.4byte	0x188a
	.uleb128 0x12
	.4byte	.LVL340
	.4byte	0x186a
	.uleb128 0xe
	.4byte	.LVL341
	.4byte	0x1c63
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x6
	.byte	0x78
	.sleb128 0
	.byte	0x40
	.byte	0x24
	.byte	0x40
	.byte	0x25
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF426
	.2byte	0x39d
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB36
	.4byte	.LFE36-.LFB36
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x212b
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x39d
	.byte	0x34
	.4byte	0x28d
	.4byte	.LLST97
	.uleb128 0x3
	.4byte	.LASF417
	.2byte	0x39d
	.byte	0x46
	.4byte	0xb4
	.4byte	.LLST98
	.uleb128 0x6
	.4byte	.LASF424
	.2byte	0x39f
	.byte	0xf
	.4byte	0x150a
	.4byte	.LLST99
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x3a0
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST100
	.uleb128 0x12
	.4byte	.LVL321
	.4byte	0x188a
	.uleb128 0xe
	.4byte	.LVL323
	.4byte	0x1c63
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF427
	.2byte	0x38a
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB35
	.4byte	.LFE35-.LFB35
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x21a4
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x38a
	.byte	0x2d
	.4byte	0x28d
	.4byte	.LLST93
	.uleb128 0x3
	.4byte	.LASF417
	.2byte	0x38a
	.byte	0x3e
	.4byte	0x97
	.4byte	.LLST94
	.uleb128 0x6
	.4byte	.LASF424
	.2byte	0x38c
	.byte	0xe
	.4byte	0x1ede
	.4byte	.LLST95
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x38d
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST96
	.uleb128 0x12
	.4byte	.LVL311
	.4byte	0x188a
	.uleb128 0xe
	.4byte	.LVL313
	.4byte	0x1c63
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF428
	.2byte	0x376
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB34
	.4byte	.LFE34-.LFB34
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x21ff
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x376
	.byte	0x34
	.4byte	0x28d
	.4byte	.LLST76
	.uleb128 0x3
	.4byte	.LASF429
	.2byte	0x376
	.byte	0x46
	.4byte	0xb4
	.4byte	.LLST77
	.uleb128 0x6
	.4byte	.LASF407
	.2byte	0x378
	.byte	0xd
	.4byte	0x97
	.4byte	.LLST78
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x379
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST79
	.byte	0
	.uleb128 0x9
	.4byte	.LASF430
	.2byte	0x362
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB33
	.4byte	.LFE33-.LFB33
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x225a
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x362
	.byte	0x31
	.4byte	0x28d
	.4byte	.LLST72
	.uleb128 0x3
	.4byte	.LASF431
	.2byte	0x362
	.byte	0x43
	.4byte	0xb4
	.4byte	.LLST73
	.uleb128 0x6
	.4byte	.LASF407
	.2byte	0x364
	.byte	0xd
	.4byte	0x97
	.4byte	.LLST74
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x365
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST75
	.byte	0
	.uleb128 0x9
	.4byte	.LASF432
	.2byte	0x351
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x22a3
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x351
	.byte	0x38
	.4byte	0x28d
	.4byte	.LLST70
	.uleb128 0x1c
	.4byte	.LASF433
	.2byte	0x351
	.byte	0x4a
	.4byte	0x1ede
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x353
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST71
	.byte	0
	.uleb128 0x9
	.4byte	.LASF434
	.2byte	0x343
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x22de
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x343
	.byte	0x35
	.4byte	0x28d
	.4byte	.LLST68
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x345
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST69
	.byte	0
	.uleb128 0x9
	.4byte	.LASF435
	.2byte	0x335
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2319
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x335
	.byte	0x34
	.4byte	0x28d
	.4byte	.LLST66
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x337
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST67
	.byte	0
	.uleb128 0x9
	.4byte	.LASF436
	.2byte	0x316
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x237d
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x316
	.byte	0x2d
	.4byte	0x28d
	.4byte	.LLST62
	.uleb128 0x3
	.4byte	.LASF437
	.2byte	0x316
	.byte	0x45
	.4byte	0x237d
	.4byte	.LLST63
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x318
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST64
	.uleb128 0x6
	.4byte	.LASF68
	.2byte	0x319
	.byte	0xe
	.4byte	0xb4
	.4byte	.LLST65
	.uleb128 0x12
	.4byte	.LVL234
	.4byte	0x18c7
	.byte	0
	.uleb128 0x15
	.4byte	0x319
	.uleb128 0x9
	.4byte	.LASF438
	.2byte	0x307
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x23bd
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x307
	.byte	0x28
	.4byte	0x28d
	.4byte	.LLST60
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x309
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST61
	.byte	0
	.uleb128 0x9
	.4byte	.LASF439
	.2byte	0x2f7
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x240f
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x2f7
	.byte	0x29
	.4byte	0x28d
	.4byte	.LLST58
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x2f9
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST59
	.uleb128 0xe
	.4byte	.LVL221
	.4byte	0x2c2b
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.byte	0x78
	.sleb128 0
	.byte	0x3
	.4byte	g_vdma_channel_map_table
	.byte	0x22
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF440
	.2byte	0x2db
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x24c2
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x2db
	.byte	0x2a
	.4byte	0x28d
	.4byte	.LLST57
	.uleb128 0x13
	.4byte	.LASF441
	.2byte	0x2dd
	.byte	0xe
	.4byte	0xb4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xf
	.4byte	.LVL208
	.4byte	0x191f
	.4byte	0x245c
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x12
	.4byte	.LVL209
	.4byte	0x190e
	.uleb128 0xf
	.4byte	.LVL212
	.4byte	0x2c2b
	.4byte	0x247a
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xf
	.4byte	.LVL213
	.4byte	0x255e
	.4byte	0x248e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0xf
	.4byte	.LVL214
	.4byte	0x2cb0
	.4byte	0x24a3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xf
	.4byte	.LVL215
	.4byte	0x2dae
	.4byte	0x24b8
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x12
	.4byte	.LVL216
	.4byte	0x190e
	.byte	0
	.uleb128 0x9
	.4byte	.LASF442
	.2byte	0x2b0
	.byte	0xf
	.4byte	0x2be
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x255e
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x2b0
	.byte	0x28
	.4byte	0x28d
	.4byte	.LLST55
	.uleb128 0x13
	.4byte	.LASF441
	.2byte	0x2b2
	.byte	0xe
	.4byte	0xb4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x6
	.4byte	.LASF393
	.2byte	0x2b3
	.byte	0x16
	.4byte	0x1703
	.4byte	.LLST56
	.uleb128 0xf
	.4byte	.LVL196
	.4byte	0x191f
	.4byte	0x251f
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x12
	.4byte	.LVL197
	.4byte	0x190e
	.uleb128 0x12
	.4byte	.LVL200
	.4byte	0x190e
	.uleb128 0xf
	.4byte	.LVL201
	.4byte	0x2e2d
	.4byte	0x254d
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0xa
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0x3
	.4byte	g_vdma_channel_map_table
	.byte	0x22
	.byte	0x6
	.byte	0
	.uleb128 0xe
	.4byte	.LVL202
	.4byte	0x255e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x30
	.4byte	.LASF444
	.2byte	0x2a0
	.byte	0xd
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2593
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x2a0
	.byte	0x40
	.4byte	0x28d
	.4byte	.LLST2
	.uleb128 0x13
	.4byte	.LASF393
	.2byte	0x2a2
	.byte	0x16
	.4byte	0x1703
	.uleb128 0x1
	.byte	0x5f
	.byte	0
	.uleb128 0x35
	.4byte	.LASF446
	.2byte	0x293
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x264a
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x293
	.byte	0x2f
	.4byte	0x28d
	.4byte	.LLST53
	.uleb128 0x3
	.4byte	.LASF445
	.2byte	0x293
	.byte	0x3c
	.4byte	0x21c
	.4byte	.LLST54
	.uleb128 0x25
	.4byte	.LBB34
	.4byte	.LBE34-.LBB34
	.4byte	0x261c
	.uleb128 0x2c
	.string	"exp"
	.2byte	0x296
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.5
	.uleb128 0x13
	.4byte	.LASF391
	.2byte	0x296
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.4
	.uleb128 0xe
	.4byte	.LVL189
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.5
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.4
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x296
	.byte	0
	.byte	0
	.uleb128 0x36
	.4byte	.LVL192
	.4byte	0x2d2f
	.4byte	0x2640
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x12
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	g_vdma_channel_map_table
	.byte	0x22
	.byte	0x6
	.byte	0
	.uleb128 0x37
	.4byte	.LVL193
	.4byte	0x2cb0
	.byte	0
	.uleb128 0x35
	.4byte	.LASF447
	.2byte	0x281
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2701
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x281
	.byte	0x31
	.4byte	0x28d
	.4byte	.LLST51
	.uleb128 0x3
	.4byte	.LASF445
	.2byte	0x281
	.byte	0x3e
	.4byte	0x21c
	.4byte	.LLST52
	.uleb128 0x25
	.4byte	.LBB33
	.4byte	.LBE33-.LBB33
	.4byte	0x26d3
	.uleb128 0x2c
	.string	"exp"
	.2byte	0x284
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.7
	.uleb128 0x13
	.4byte	.LASF391
	.2byte	0x284
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.6
	.uleb128 0xe
	.4byte	.LVL181
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.7
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.6
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x284
	.byte	0
	.byte	0
	.uleb128 0x36
	.4byte	.LVL184
	.4byte	0x2e2d
	.4byte	0x26f7
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x12
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	g_vdma_channel_map_table
	.byte	0x22
	.byte	0x6
	.byte	0
	.uleb128 0x37
	.4byte	.LVL185
	.4byte	0x2dae
	.byte	0
	.uleb128 0x9
	.4byte	.LASF448
	.2byte	0x235
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2744
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x235
	.byte	0x31
	.4byte	0xfb
	.4byte	.LLST50
	.uleb128 0x18
	.4byte	.LASF388
	.2byte	0x237
	.byte	0x1a
	.4byte	0x1616
	.uleb128 0x18
	.4byte	.LASF449
	.2byte	0x238
	.byte	0x1a
	.4byte	0x163d
	.byte	0
	.uleb128 0x9
	.4byte	.LASF450
	.2byte	0x223
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x27d8
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x223
	.byte	0x36
	.4byte	0xfb
	.4byte	.LLST42
	.uleb128 0x3
	.4byte	.LASF451
	.2byte	0x223
	.byte	0x56
	.4byte	0x27d8
	.4byte	.LLST43
	.uleb128 0x38
	.4byte	0x2bde
	.4byte	.LBB28
	.4byte	.LLRL44
	.2byte	0x22c
	.byte	0x9
	.uleb128 0x39
	.4byte	0x2bef
	.4byte	.LLST45
	.uleb128 0x3a
	.4byte	.LLRL44
	.uleb128 0x21
	.4byte	0x2bfb
	.4byte	.LLST46
	.uleb128 0x47
	.4byte	0x2c07
	.4byte	.LBB30
	.4byte	.LBE30-.LBB30
	.uleb128 0xe
	.4byte	.LVL159
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.9
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.8
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xff
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	0x1a1
	.uleb128 0x9
	.4byte	.LASF452
	.2byte	0x211
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x284e
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x211
	.byte	0x35
	.4byte	0xfb
	.4byte	.LLST39
	.uleb128 0x3
	.4byte	.LASF399
	.2byte	0x211
	.byte	0x4e
	.4byte	0x22f
	.4byte	.LLST40
	.uleb128 0x3
	.4byte	.LASF400
	.2byte	0x211
	.byte	0x5e
	.4byte	0x7f
	.4byte	.LLST41
	.uleb128 0xf
	.4byte	.LVL145
	.4byte	0x2ec7
	.4byte	0x283c
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xe
	.4byte	.LVL146
	.4byte	0x2d2f
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF453
	.2byte	0x200
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2899
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x200
	.byte	0x28
	.4byte	0xfb
	.4byte	.LLST36
	.uleb128 0x6
	.4byte	.LASF388
	.2byte	0x202
	.byte	0x1a
	.4byte	0x1616
	.4byte	.LLST37
	.uleb128 0x6
	.4byte	.LASF449
	.2byte	0x203
	.byte	0x1a
	.4byte	0x163d
	.4byte	.LLST38
	.byte	0
	.uleb128 0x9
	.4byte	.LASF454
	.2byte	0x1e8
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x28fb
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x1e8
	.byte	0x33
	.4byte	0xfb
	.4byte	.LLST33
	.uleb128 0x3
	.4byte	.LASF455
	.2byte	0x1e8
	.byte	0x45
	.4byte	0xb4
	.4byte	.LLST34
	.uleb128 0x6
	.4byte	.LASF449
	.2byte	0x1ea
	.byte	0x1a
	.4byte	0x163d
	.4byte	.LLST35
	.uleb128 0xe
	.4byte	.LVL131
	.4byte	0x18c7
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
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
	.uleb128 0x9
	.4byte	.LASF456
	.2byte	0x1ca
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x299a
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x1ca
	.byte	0x31
	.4byte	0xfb
	.4byte	.LLST47
	.uleb128 0x3
	.4byte	.LASF455
	.2byte	0x1ca
	.byte	0x43
	.4byte	0xb4
	.4byte	.LLST48
	.uleb128 0x6
	.4byte	.LASF449
	.2byte	0x1cc
	.byte	0x1a
	.4byte	0x163d
	.4byte	.LLST49
	.uleb128 0x13
	.4byte	.LASF451
	.2byte	0x1cd
	.byte	0x1b
	.4byte	0x1a1
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xf
	.4byte	.LVL167
	.4byte	0x18c7
	.4byte	0x296f
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
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
	.uleb128 0xf
	.4byte	.LVL168
	.4byte	0x2744
	.4byte	0x2989
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0xe
	.4byte	.LVL169
	.4byte	0x284e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	.LASF457
	.2byte	0x192
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x29f2
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x192
	.byte	0x2d
	.4byte	0xfb
	.4byte	.LLST31
	.uleb128 0x1c
	.4byte	.LASF458
	.2byte	0x192
	.byte	0x45
	.4byte	0x29f2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x13
	.4byte	.LASF459
	.2byte	0x194
	.byte	0x10
	.4byte	0x790
	.uleb128 0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x6
	.4byte	.LASF449
	.2byte	0x195
	.byte	0x1a
	.4byte	0x163d
	.4byte	.LLST32
	.byte	0
	.uleb128 0x15
	.4byte	0x223
	.uleb128 0x9
	.4byte	.LASF460
	.2byte	0x180
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2a4e
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x180
	.byte	0x33
	.4byte	0xfb
	.4byte	.LLST29
	.uleb128 0x1c
	.4byte	.LASF461
	.2byte	0x180
	.byte	0x45
	.4byte	0xb4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1c
	.4byte	.LASF462
	.2byte	0x180
	.byte	0x54
	.4byte	0xb4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x6
	.4byte	.LASF449
	.2byte	0x182
	.byte	0x1a
	.4byte	0x163d
	.4byte	.LLST30
	.byte	0
	.uleb128 0x9
	.4byte	.LASF463
	.2byte	0x164
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2b01
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x164
	.byte	0x2a
	.4byte	0xfb
	.4byte	.LLST28
	.uleb128 0x13
	.4byte	.LASF441
	.2byte	0x166
	.byte	0xe
	.4byte	0xb4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xf
	.4byte	.LVL102
	.4byte	0x191f
	.4byte	0x2a9b
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x12
	.4byte	.LVL103
	.4byte	0x190e
	.uleb128 0xf
	.4byte	.LVL106
	.4byte	0x2c2b
	.4byte	0x2ab9
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xf
	.4byte	.LVL107
	.4byte	0x2b99
	.4byte	0x2acd
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0xf
	.4byte	.LVL108
	.4byte	0x2cb0
	.4byte	0x2ae2
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0xf
	.4byte	.LVL109
	.4byte	0x2dae
	.4byte	0x2af7
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x12
	.4byte	.LVL110
	.4byte	0x190e
	.byte	0
	.uleb128 0x9
	.4byte	.LASF464
	.2byte	0x14a
	.byte	0xf
	.4byte	0x17c
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2b99
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x14a
	.byte	0x28
	.4byte	0xfb
	.4byte	.LLST27
	.uleb128 0x13
	.4byte	.LASF441
	.2byte	0x14c
	.byte	0xe
	.4byte	0xb4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0xf
	.4byte	.LVL90
	.4byte	0x191f
	.4byte	0x2b4e
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x12
	.4byte	.LVL91
	.4byte	0x190e
	.uleb128 0x12
	.4byte	.LVL94
	.4byte	0x190e
	.uleb128 0xf
	.4byte	.LVL95
	.4byte	0x2c2b
	.4byte	0x2b74
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0xf
	.4byte	.LVL96
	.4byte	0x2e2d
	.4byte	0x2b88
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0xe
	.4byte	.LVL97
	.4byte	0x2b99
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x30
	.4byte	.LASF465
	.2byte	0x138
	.byte	0xd
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2bde
	.uleb128 0x3
	.4byte	.LASF390
	.2byte	0x138
	.byte	0x40
	.4byte	0xfb
	.4byte	.LLST0
	.uleb128 0x13
	.4byte	.LASF388
	.2byte	0x13a
	.byte	0x1a
	.4byte	0x1616
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x6
	.4byte	.LASF449
	.2byte	0x13b
	.byte	0x1a
	.4byte	0x163d
	.4byte	.LLST1
	.byte	0
	.uleb128 0x48
	.4byte	.LASF478
	.byte	0x1
	.byte	0xf6
	.byte	0xc
	.4byte	0x21c
	.byte	0x1
	.4byte	0x2c2b
	.uleb128 0x49
	.4byte	.LASF466
	.byte	0x1
	.byte	0xf6
	.byte	0x3c
	.4byte	0x1570
	.uleb128 0x4a
	.4byte	.LASF467
	.byte	0x1
	.byte	0xf8
	.byte	0xe
	.4byte	0xb4
	.uleb128 0x34
	.uleb128 0x20
	.string	"exp"
	.byte	0xff
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.9
	.uleb128 0x1a
	.4byte	.LASF391
	.byte	0xff
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.8
	.byte	0
	.byte	0
	.uleb128 0x4b
	.4byte	.LASF479
	.byte	0x1
	.byte	0xd8
	.byte	0xc
	.4byte	0x21c
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2cb0
	.uleb128 0x22
	.4byte	.LASF466
	.byte	0xd8
	.byte	0x39
	.4byte	0x1570
	.4byte	.LLST3
	.uleb128 0x26
	.4byte	.LASF467
	.byte	0xda
	.4byte	0xb4
	.4byte	.LLST4
	.uleb128 0x2d
	.4byte	.LBB3
	.4byte	.LBE3-.LBB3
	.uleb128 0x20
	.string	"exp"
	.byte	0xe1
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.11
	.uleb128 0x1a
	.4byte	.LASF391
	.byte	0xe1
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.10
	.uleb128 0xe
	.4byte	.LVL12
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.11
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.10
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xe1
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x27
	.4byte	.LASF468
	.byte	0xc4
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2d2f
	.uleb128 0x22
	.4byte	.LASF466
	.byte	0xc4
	.byte	0x34
	.4byte	0x1570
	.4byte	.LLST5
	.uleb128 0x26
	.4byte	.LASF467
	.byte	0xc6
	.4byte	0xb4
	.4byte	.LLST6
	.uleb128 0x2d
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.uleb128 0x20
	.string	"exp"
	.byte	0xcd
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.13
	.uleb128 0x1a
	.4byte	.LASF391
	.byte	0xcd
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.12
	.uleb128 0xe
	.4byte	.LVL16
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.13
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.12
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xcd
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x27
	.4byte	.LASF469
	.byte	0xb0
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2dae
	.uleb128 0x22
	.4byte	.LASF466
	.byte	0xb0
	.byte	0x33
	.4byte	0x1570
	.4byte	.LLST15
	.uleb128 0x26
	.4byte	.LASF467
	.byte	0xb2
	.4byte	0xb4
	.4byte	.LLST16
	.uleb128 0x2d
	.4byte	.LBB7
	.4byte	.LBE7-.LBB7
	.uleb128 0x20
	.string	"exp"
	.byte	0xb9
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.15
	.uleb128 0x1a
	.4byte	.LASF391
	.byte	0xb9
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.14
	.uleb128 0xe
	.4byte	.LVL47
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.15
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.14
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xb9
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x27
	.4byte	.LASF470
	.byte	0x9c
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2e2d
	.uleb128 0x22
	.4byte	.LASF466
	.byte	0x9c
	.byte	0x36
	.4byte	0x1570
	.4byte	.LLST7
	.uleb128 0x26
	.4byte	.LASF467
	.byte	0x9e
	.4byte	0xb4
	.4byte	.LLST8
	.uleb128 0x2d
	.4byte	.LBB5
	.4byte	.LBE5-.LBB5
	.uleb128 0x20
	.string	"exp"
	.byte	0xa5
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.17
	.uleb128 0x1a
	.4byte	.LASF391
	.byte	0xa5
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.16
	.uleb128 0xe
	.4byte	.LVL22
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.17
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.16
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0xa5
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x27
	.4byte	.LASF471
	.byte	0x82
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2ec7
	.uleb128 0x22
	.4byte	.LASF466
	.byte	0x82
	.byte	0x35
	.4byte	0x1570
	.4byte	.LLST17
	.uleb128 0x26
	.4byte	.LASF467
	.byte	0x84
	.4byte	0xb4
	.4byte	.LLST18
	.uleb128 0x25
	.4byte	.LBB8
	.4byte	.LBE8-.LBB8
	.4byte	0x2eaf
	.uleb128 0x20
	.string	"exp"
	.byte	0x91
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.19
	.uleb128 0x1a
	.4byte	.LASF391
	.byte	0x91
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.18
	.uleb128 0xe
	.4byte	.LVL59
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.19
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.18
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x91
	.byte	0
	.byte	0
	.uleb128 0xe
	.4byte	.LVL54
	.4byte	0x18dd
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.byte	0x79
	.sleb128 0
	.byte	0x3
	.4byte	g_dma_clk_table
	.byte	0x22
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x27
	.4byte	.LASF472
	.byte	0x72
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2f85
	.uleb128 0x22
	.4byte	.LASF466
	.byte	0x72
	.byte	0x3e
	.4byte	0x1570
	.4byte	.LLST19
	.uleb128 0x1a
	.4byte	.LASF473
	.byte	0x74
	.byte	0xe
	.4byte	0xb4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x25
	.4byte	.LBB9
	.4byte	.LBE9-.LBB9
	.4byte	0x2f49
	.uleb128 0x20
	.string	"exp"
	.byte	0x7c
	.4byte	0x1a34
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.21
	.uleb128 0x1a
	.4byte	.LASF391
	.byte	0x7c
	.byte	0xa5
	.4byte	0x1a49
	.uleb128 0x5
	.byte	0x3
	.4byte	file.20
	.uleb128 0xe
	.4byte	.LVL69
	.4byte	0x18f3
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.21
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.20
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x7c
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	.LVL63
	.4byte	0x191f
	.4byte	0x2f5d
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x12
	.4byte	.LVL64
	.4byte	0x18b1
	.uleb128 0xf
	.4byte	.LVL65
	.4byte	0x18a0
	.4byte	0x2f7b
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x78
	.sleb128 0
	.byte	0x6
	.byte	0
	.uleb128 0x12
	.4byte	.LVL66
	.4byte	0x190e
	.byte	0
	.uleb128 0x4c
	.4byte	0x1a4e
	.4byte	.LFB51
	.4byte	.LFE51-.LFB51
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x39
	.4byte	0x1a5c
	.4byte	.LLST20
	.uleb128 0x2e
	.4byte	0x1a69
	.uleb128 0x2e
	.4byte	0x1a75
	.uleb128 0x2e
	.4byte	0x1a81
	.uleb128 0x2e
	.4byte	0x1a8d
	.uleb128 0x4d
	.4byte	0x1a99
	.byte	0
	.uleb128 0x4e
	.4byte	0x1aa5
	.4byte	.LBB14
	.4byte	.LBE14-.LBB14
	.uleb128 0x38
	.4byte	0x1a4e
	.4byte	.LBB15
	.4byte	.LLRL21
	.2byte	0x506
	.byte	0x6
	.uleb128 0x4f
	.4byte	0x1a5c
	.uleb128 0x3a
	.4byte	.LLRL21
	.uleb128 0x21
	.4byte	0x1a69
	.4byte	.LLST22
	.uleb128 0x21
	.4byte	0x1a75
	.4byte	.LLST23
	.uleb128 0x21
	.4byte	0x1a81
	.4byte	.LLST24
	.uleb128 0x21
	.4byte	0x1a8d
	.4byte	.LLST25
	.uleb128 0x21
	.4byte	0x1a99
	.4byte	.LLST22
	.uleb128 0x50
	.4byte	.LVL77
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
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
	.uleb128 0x4
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
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x5
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
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0x6b
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
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
	.uleb128 0x11
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0x6b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
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
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
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
	.uleb128 0x35
	.byte	0
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.sleb128 89
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x25
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
	.uleb128 0x26
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
	.sleb128 14
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.sleb128 13
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x2a
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0x6b
	.uleb128 0xb
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
	.uleb128 0x2c
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
	.sleb128 89
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x31
	.uleb128 0x37
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x36
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x82
	.uleb128 0x19
	.uleb128 0x7f
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x37
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
	.uleb128 0x38
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
	.uleb128 0x39
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
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
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x40
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x41
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x42
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
	.uleb128 0x43
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x82
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x44
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
	.uleb128 0x47
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
	.uleb128 0x48
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
	.uleb128 0x49
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
	.uleb128 0x4a
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
	.byte	0
	.byte	0
	.uleb128 0x4b
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
	.uleb128 0x4c
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
	.byte	0
	.byte	0
	.uleb128 0x4d
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x4e
	.uleb128 0xb
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x4f
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x50
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
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
.LLST9:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL27-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL27-.LVL26
	.uleb128 .LVL35-.LVL26
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
	.uleb128 .LVL35-.LVL26
	.uleb128 .LVL39-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL39-.LVL26
	.uleb128 .LFE52-.LVL26
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
	.4byte	.LVL28
	.byte	0x4
	.uleb128 .LVL28-.LVL28
	.uleb128 .LVL32-.LVL28
	.uleb128 0x2
	.byte	0x32
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL32-.LVL28
	.uleb128 .LVL35-.LVL28
	.uleb128 0x2
	.byte	0x33
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL35-.LVL28
	.uleb128 .LVL40-.LVL28
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL40-.LVL28
	.uleb128 .LVL43-.LVL28
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL32-1-.LVL31
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL38-.LVL31
	.uleb128 .LVL40-1-.LVL31
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL43-.LVL31
	.uleb128 .LVL44-1-.LVL31
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL29
	.byte	0x4
	.uleb128 .LVL29-.LVL29
	.uleb128 .LVL32-.LVL29
	.uleb128 0x6
	.byte	0xc
	.4byte	0x400f011c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL33-.LVL29
	.uleb128 .LVL35-.LVL29
	.uleb128 0x6
	.byte	0xc
	.4byte	0x400f021c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL36-.LVL29
	.uleb128 .LVL40-.LVL29
	.uleb128 0x6
	.byte	0xc
	.4byte	0x4222011c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL41-.LVL29
	.uleb128 .LVL43-.LVL29
	.uleb128 0x6
	.byte	0xc
	.4byte	0x4222021c
	.byte	0x9f
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL32-1-.LVL30
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL34-.LVL30
	.uleb128 .LVL35-.LVL30
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL37-.LVL30
	.uleb128 .LVL40-1-.LVL30
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL42-.LVL30
	.uleb128 .LVL44-1-.LVL30
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL28-.LVL26
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL28-.LVL26
	.uleb128 .LVL32-.LVL26
	.uleb128 0x2
	.byte	0x32
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL32-.LVL26
	.uleb128 .LVL35-.LVL26
	.uleb128 0x2
	.byte	0x33
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL35-.LVL26
	.uleb128 .LVL40-.LVL26
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL40-.LVL26
	.uleb128 .LVL43-.LVL26
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0
.LLST133:
	.byte	0x6
	.4byte	.LVL423
	.byte	0x4
	.uleb128 .LVL423-.LVL423
	.uleb128 .LVL424-.LVL423
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL424-.LVL423
	.uleb128 .LVL425-.LVL423
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
	.uleb128 .LVL425-.LVL423
	.uleb128 .LVL426-.LVL423
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL426-.LVL423
	.uleb128 .LFE50-.LVL423
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
.LLST131:
	.byte	0x6
	.4byte	.LVL417
	.byte	0x4
	.uleb128 .LVL417-.LVL417
	.uleb128 .LVL418-.LVL417
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL418-.LVL417
	.uleb128 .LVL421-.LVL417
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
	.uleb128 .LVL421-.LVL417
	.uleb128 .LVL422-.LVL417
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL422-.LVL417
	.uleb128 .LFE49-.LVL417
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
.LLST132:
	.byte	0x6
	.4byte	.LVL419
	.byte	0x4
	.uleb128 .LVL419-.LVL419
	.uleb128 .LVL420-.LVL419
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL420-.LVL419
	.uleb128 .LVL421-.LVL419
	.uleb128 0x11
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	g_vdma_regbase_table
	.byte	0x22
	.byte	0
.LLST128:
	.byte	0x6
	.4byte	.LVL409
	.byte	0x4
	.uleb128 .LVL409-.LVL409
	.uleb128 .LVL410-.LVL409
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL410-.LVL409
	.uleb128 .LVL411-.LVL409
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL411-.LVL409
	.uleb128 .LVL414-.LVL409
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
	.uleb128 .LVL414-.LVL409
	.uleb128 .LVL415-.LVL409
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL415-.LVL409
	.uleb128 .LVL416-.LVL409
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
	.uleb128 .LVL416-.LVL409
	.uleb128 .LFE48-.LVL409
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST129:
	.byte	0x6
	.4byte	.LVL409
	.byte	0x4
	.uleb128 .LVL409-.LVL409
	.uleb128 .LVL412-1-.LVL409
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL412-1-.LVL409
	.uleb128 .LVL414-.LVL409
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
	.uleb128 .LVL414-.LVL409
	.uleb128 .LFE48-.LVL409
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST130:
	.byte	0x6
	.4byte	.LVL409
	.byte	0x4
	.uleb128 .LVL409-.LVL409
	.uleb128 .LVL412-1-.LVL409
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL412-1-.LVL409
	.uleb128 .LVL414-.LVL409
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
	.uleb128 .LVL414-.LVL409
	.uleb128 .LFE48-.LVL409
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST126:
	.byte	0x6
	.4byte	.LVL402
	.byte	0x4
	.uleb128 .LVL402-.LVL402
	.uleb128 .LVL403-.LVL402
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL403-.LVL402
	.uleb128 .LVL404-.LVL402
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL404-.LVL402
	.uleb128 .LVL407-.LVL402
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
	.uleb128 .LVL407-.LVL402
	.uleb128 .LVL408-.LVL402
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL408-.LVL402
	.uleb128 .LFE47-.LVL402
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST127:
	.byte	0x6
	.4byte	.LVL405
	.byte	0x4
	.uleb128 .LVL405-.LVL405
	.uleb128 .LVL406-.LVL405
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL406-.LVL405
	.uleb128 .LVL407-.LVL405
	.uleb128 0x11
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	g_vdma_regbase_table
	.byte	0x22
	.byte	0
.LLST124:
	.byte	0x6
	.4byte	.LVL395
	.byte	0x4
	.uleb128 .LVL395-.LVL395
	.uleb128 .LVL396-.LVL395
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL396-.LVL395
	.uleb128 .LVL397-.LVL395
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL397-.LVL395
	.uleb128 .LVL400-.LVL395
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
	.uleb128 .LVL400-.LVL395
	.uleb128 .LVL401-.LVL395
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL401-.LVL395
	.uleb128 .LFE46-.LVL395
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST125:
	.byte	0x6
	.4byte	.LVL398
	.byte	0x4
	.uleb128 .LVL398-.LVL398
	.uleb128 .LVL399-.LVL398
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL399-.LVL398
	.uleb128 .LVL400-.LVL398
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
	.byte	0x32
	.byte	0x24
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0
.LLST89:
	.byte	0x6
	.4byte	.LVL301
	.byte	0x4
	.uleb128 .LVL301-.LVL301
	.uleb128 .LVL302-.LVL301
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL302-.LVL301
	.uleb128 .LVL306-.LVL301
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
	.uleb128 .LVL306-.LVL301
	.uleb128 .LVL307-.LVL301
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL307-.LVL301
	.uleb128 .LFE45-.LVL301
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
.LLST90:
	.byte	0x6
	.4byte	.LVL301
	.byte	0x4
	.uleb128 .LVL301-.LVL301
	.uleb128 .LVL305-.LVL301
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL305-.LVL301
	.uleb128 .LVL306-.LVL301
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
	.byte	0x4
	.uleb128 .LVL306-.LVL301
	.uleb128 .LFE45-.LVL301
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST91:
	.byte	0x6
	.4byte	.LVL301
	.byte	0x4
	.uleb128 .LVL301-.LVL301
	.uleb128 .LVL304-.LVL301
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL304-.LVL301
	.uleb128 .LVL306-.LVL301
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL306-.LVL301
	.uleb128 .LVL307-.LVL301
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST92:
	.byte	0x8
	.4byte	.LVL303
	.uleb128 .LVL306-.LVL303
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST87:
	.byte	0x6
	.4byte	.LVL294
	.byte	0x4
	.uleb128 .LVL294-.LVL294
	.uleb128 .LVL295-.LVL294
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL295-.LVL294
	.uleb128 .LVL296-.LVL294
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL296-.LVL294
	.uleb128 .LVL299-.LVL294
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
	.uleb128 .LVL299-.LVL294
	.uleb128 .LVL300-.LVL294
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL300-.LVL294
	.uleb128 .LFE44-.LVL294
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST88:
	.byte	0x6
	.4byte	.LVL297
	.byte	0x4
	.uleb128 .LVL297-.LVL297
	.uleb128 .LVL298-.LVL297
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL298-.LVL297
	.uleb128 .LVL299-.LVL297
	.uleb128 0x11
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	g_vdma_regbase_table
	.byte	0x22
	.byte	0
.LLST85:
	.byte	0x6
	.4byte	.LVL287
	.byte	0x4
	.uleb128 .LVL287-.LVL287
	.uleb128 .LVL288-.LVL287
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL288-.LVL287
	.uleb128 .LVL289-.LVL287
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL289-.LVL287
	.uleb128 .LVL292-.LVL287
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
	.uleb128 .LVL292-.LVL287
	.uleb128 .LVL293-.LVL287
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL293-.LVL287
	.uleb128 .LFE43-.LVL287
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST86:
	.byte	0x6
	.4byte	.LVL290
	.byte	0x4
	.uleb128 .LVL290-.LVL290
	.uleb128 .LVL291-.LVL290
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL291-.LVL290
	.uleb128 .LVL292-.LVL290
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
	.byte	0x32
	.byte	0x24
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0
.LLST83:
	.byte	0x6
	.4byte	.LVL280
	.byte	0x4
	.uleb128 .LVL280-.LVL280
	.uleb128 .LVL281-.LVL280
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL281-.LVL280
	.uleb128 .LVL282-.LVL280
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL282-.LVL280
	.uleb128 .LVL285-.LVL280
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
	.uleb128 .LVL285-.LVL280
	.uleb128 .LVL286-.LVL280
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL286-.LVL280
	.uleb128 .LFE42-.LVL280
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST84:
	.byte	0x6
	.4byte	.LVL283
	.byte	0x4
	.uleb128 .LVL283-.LVL283
	.uleb128 .LVL284-.LVL283
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL284-.LVL283
	.uleb128 .LVL285-.LVL283
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
	.byte	0x32
	.byte	0x24
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0
.LLST80:
	.byte	0x6
	.4byte	.LVL272
	.byte	0x4
	.uleb128 .LVL272-.LVL272
	.uleb128 .LVL273-.LVL272
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL273-.LVL272
	.uleb128 .LVL274-.LVL272
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL274-.LVL272
	.uleb128 .LVL278-.LVL272
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
	.uleb128 .LVL278-.LVL272
	.uleb128 .LVL279-.LVL272
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL279-.LVL272
	.uleb128 .LFE41-.LVL272
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST81:
	.byte	0x8
	.4byte	.LVL276
	.uleb128 .LVL278-.LVL276
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST82:
	.byte	0x6
	.4byte	.LVL275
	.byte	0x4
	.uleb128 .LVL275-.LVL275
	.uleb128 .LVL277-.LVL275
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL277-.LVL275
	.uleb128 .LVL278-.LVL275
	.uleb128 0x11
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	g_vdma_regbase_table
	.byte	0x22
	.byte	0
.LLST116:
	.byte	0x6
	.4byte	.LVL370
	.byte	0x4
	.uleb128 .LVL370-.LVL370
	.uleb128 .LVL371-.LVL370
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL371-.LVL370
	.uleb128 .LVL372-.LVL370
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL372-.LVL370
	.uleb128 .LVL390-.LVL370
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL390-.LVL370
	.uleb128 .LVL391-.LVL370
	.uleb128 0x2
	.byte	0x72
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL391-.LVL370
	.uleb128 .LVL393-.LVL370
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL393-.LVL370
	.uleb128 .LVL394-.LVL370
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL394-.LVL370
	.uleb128 .LFE40-.LVL370
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
.LLST117:
	.byte	0x6
	.4byte	.LVL370
	.byte	0x4
	.uleb128 .LVL370-.LVL370
	.uleb128 .LVL379-1-.LVL370
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL379-1-.LVL370
	.uleb128 .LVL390-.LVL370
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL390-.LVL370
	.uleb128 .LVL391-.LVL370
	.uleb128 0x2
	.byte	0x72
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL391-.LVL370
	.uleb128 .LVL393-.LVL370
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL393-.LVL370
	.uleb128 .LFE40-.LVL370
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST118:
	.byte	0x6
	.4byte	.LVL370
	.byte	0x4
	.uleb128 .LVL370-.LVL370
	.uleb128 .LVL379-1-.LVL370
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL379-1-.LVL370
	.uleb128 .LVL389-.LVL370
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL389-.LVL370
	.uleb128 .LVL391-.LVL370
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
	.uleb128 .LVL391-.LVL370
	.uleb128 .LVL393-.LVL370
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL393-.LVL370
	.uleb128 .LFE40-.LVL370
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST119:
	.byte	0x8
	.4byte	.LVL374
	.uleb128 .LVL379-1-.LVL374
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST120:
	.byte	0x6
	.4byte	.LVL378
	.byte	0x4
	.uleb128 .LVL378-.LVL378
	.uleb128 .LVL379-1-.LVL378
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL380-.LVL378
	.uleb128 .LVL381-.LVL378
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL381-.LVL378
	.uleb128 .LVL382-1-.LVL378
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL383-.LVL378
	.uleb128 .LVL384-1-.LVL378
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL385-.LVL378
	.uleb128 .LVL386-.LVL378
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL386-.LVL378
	.uleb128 .LVL387-1-.LVL378
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL391-.LVL378
	.uleb128 .LVL392-.LVL378
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL392-.LVL378
	.uleb128 .LVL393-.LVL378
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST121:
	.byte	0x8
	.4byte	.LVL375
	.uleb128 .LVL376-.LVL375
	.uleb128 0x6
	.byte	0x7e
	.sleb128 0
	.byte	0x7d
	.sleb128 0
	.byte	0x24
	.byte	0x9f
	.byte	0
.LLST122:
	.byte	0x6
	.4byte	.LVL377
	.byte	0x4
	.uleb128 .LVL377-.LVL377
	.uleb128 .LVL389-.LVL377
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL391-.LVL377
	.uleb128 .LVL393-.LVL377
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST123:
	.byte	0x6
	.4byte	.LVL373
	.byte	0x4
	.uleb128 .LVL373-.LVL373
	.uleb128 .LVL379-1-.LVL373
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL379-1-.LVL373
	.uleb128 .LVL389-.LVL373
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL391-.LVL373
	.uleb128 .LVL393-.LVL373
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
.LLST112:
	.byte	0x6
	.4byte	.LVL358
	.byte	0x4
	.uleb128 .LVL358-.LVL358
	.uleb128 .LVL359-.LVL358
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL359-.LVL358
	.uleb128 .LVL366-.LVL358
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL366-.LVL358
	.uleb128 .LVL368-.LVL358
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
	.uleb128 .LVL368-.LVL358
	.uleb128 .LVL369-.LVL358
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL369-.LVL358
	.uleb128 .LFE39-.LVL358
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
.LLST113:
	.byte	0x6
	.4byte	.LVL358
	.byte	0x4
	.uleb128 .LVL358-.LVL358
	.uleb128 .LVL362-1-.LVL358
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL362-1-.LVL358
	.uleb128 .LVL367-.LVL358
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL367-.LVL358
	.uleb128 .LVL368-.LVL358
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
	.uleb128 .LVL368-.LVL358
	.uleb128 .LFE39-.LVL358
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST114:
	.byte	0x6
	.4byte	.LVL361
	.byte	0x4
	.uleb128 .LVL361-.LVL361
	.uleb128 .LVL362-1-.LVL361
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL362-.LVL361
	.uleb128 .LVL363-.LVL361
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST115:
	.byte	0x8
	.4byte	.LVL360
	.uleb128 .LVL362-1-.LVL360
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST108:
	.byte	0x6
	.4byte	.LVL346
	.byte	0x4
	.uleb128 .LVL346-.LVL346
	.uleb128 .LVL347-.LVL346
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL347-.LVL346
	.uleb128 .LVL354-.LVL346
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL354-.LVL346
	.uleb128 .LVL356-.LVL346
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
	.uleb128 .LVL356-.LVL346
	.uleb128 .LVL357-.LVL346
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL357-.LVL346
	.uleb128 .LFE38-.LVL346
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
.LLST109:
	.byte	0x6
	.4byte	.LVL346
	.byte	0x4
	.uleb128 .LVL346-.LVL346
	.uleb128 .LVL350-1-.LVL346
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL350-1-.LVL346
	.uleb128 .LVL355-.LVL346
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL355-.LVL346
	.uleb128 .LVL356-.LVL346
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
	.uleb128 .LVL356-.LVL346
	.uleb128 .LFE38-.LVL346
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST110:
	.byte	0x6
	.4byte	.LVL349
	.byte	0x4
	.uleb128 .LVL349-.LVL349
	.uleb128 .LVL350-1-.LVL349
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL350-.LVL349
	.uleb128 .LVL351-.LVL349
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST111:
	.byte	0x8
	.4byte	.LVL348
	.uleb128 .LVL350-1-.LVL348
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST101:
	.byte	0x6
	.4byte	.LVL328
	.byte	0x4
	.uleb128 .LVL328-.LVL328
	.uleb128 .LVL329-.LVL328
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL329-.LVL328
	.uleb128 .LVL330-.LVL328
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL330-.LVL328
	.uleb128 .LVL343-.LVL328
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL343-.LVL328
	.uleb128 .LVL344-.LVL328
	.uleb128 0x2
	.byte	0x72
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL344-.LVL328
	.uleb128 .LVL345-.LVL328
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL345-.LVL328
	.uleb128 .LFE37-.LVL328
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST102:
	.byte	0x6
	.4byte	.LVL328
	.byte	0x4
	.uleb128 .LVL328-.LVL328
	.uleb128 .LVL334-1-.LVL328
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL334-1-.LVL328
	.uleb128 .LVL342-.LVL328
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL342-.LVL328
	.uleb128 .LVL344-.LVL328
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
	.uleb128 .LVL344-.LVL328
	.uleb128 .LFE37-.LVL328
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST103:
	.byte	0x6
	.4byte	.LVL328
	.byte	0x4
	.uleb128 .LVL328-.LVL328
	.uleb128 .LVL334-1-.LVL328
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL334-1-.LVL328
	.uleb128 .LVL342-.LVL328
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL342-.LVL328
	.uleb128 .LVL344-.LVL328
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
	.uleb128 .LVL344-.LVL328
	.uleb128 .LFE37-.LVL328
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST104:
	.byte	0x6
	.4byte	.LVL333
	.byte	0x4
	.uleb128 .LVL333-.LVL333
	.uleb128 .LVL334-1-.LVL333
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL334-.LVL333
	.uleb128 .LVL336-1-.LVL333
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL337-.LVL333
	.uleb128 .LVL338-1-.LVL333
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL338-.LVL333
	.uleb128 .LVL339-.LVL333
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST105:
	.byte	0x6
	.4byte	.LVL335
	.byte	0x4
	.uleb128 .LVL335-.LVL335
	.uleb128 .LVL336-1-.LVL335
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL336-1-.LVL335
	.uleb128 .LVL339-.LVL335
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
.LLST106:
	.byte	0x8
	.4byte	.LVL332
	.uleb128 .LVL334-1-.LVL332
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST107:
	.byte	0x8
	.4byte	.LVL331
	.uleb128 .LVL342-.LVL331
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST97:
	.byte	0x6
	.4byte	.LVL318
	.byte	0x4
	.uleb128 .LVL318-.LVL318
	.uleb128 .LVL319-.LVL318
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL319-.LVL318
	.uleb128 .LVL324-.LVL318
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL324-.LVL318
	.uleb128 .LVL326-.LVL318
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
	.uleb128 .LVL326-.LVL318
	.uleb128 .LVL327-.LVL318
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL327-.LVL318
	.uleb128 .LFE36-.LVL318
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
.LLST98:
	.byte	0x6
	.4byte	.LVL318
	.byte	0x4
	.uleb128 .LVL318-.LVL318
	.uleb128 .LVL321-1-.LVL318
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL321-1-.LVL318
	.uleb128 .LVL325-.LVL318
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL325-.LVL318
	.uleb128 .LVL326-.LVL318
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
	.uleb128 .LVL326-.LVL318
	.uleb128 .LFE36-.LVL318
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST99:
	.byte	0x6
	.4byte	.LVL320
	.byte	0x4
	.uleb128 .LVL320-.LVL320
	.uleb128 .LVL321-1-.LVL320
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL321-.LVL320
	.uleb128 .LVL322-.LVL320
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST100:
	.byte	0x8
	.4byte	.LVL320
	.uleb128 .LVL321-1-.LVL320
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST93:
	.byte	0x6
	.4byte	.LVL308
	.byte	0x4
	.uleb128 .LVL308-.LVL308
	.uleb128 .LVL309-.LVL308
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL309-.LVL308
	.uleb128 .LVL314-.LVL308
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL314-.LVL308
	.uleb128 .LVL316-.LVL308
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
	.uleb128 .LVL316-.LVL308
	.uleb128 .LVL317-.LVL308
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL317-.LVL308
	.uleb128 .LFE35-.LVL308
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
.LLST94:
	.byte	0x6
	.4byte	.LVL308
	.byte	0x4
	.uleb128 .LVL308-.LVL308
	.uleb128 .LVL311-1-.LVL308
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL311-1-.LVL308
	.uleb128 .LVL315-.LVL308
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL315-.LVL308
	.uleb128 .LVL316-.LVL308
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
	.uleb128 .LVL316-.LVL308
	.uleb128 .LFE35-.LVL308
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST95:
	.byte	0x6
	.4byte	.LVL310
	.byte	0x4
	.uleb128 .LVL310-.LVL310
	.uleb128 .LVL311-1-.LVL310
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL311-.LVL310
	.uleb128 .LVL312-.LVL310
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST96:
	.byte	0x8
	.4byte	.LVL310
	.uleb128 .LVL311-1-.LVL310
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST76:
	.byte	0x6
	.4byte	.LVL264
	.byte	0x4
	.uleb128 .LVL264-.LVL264
	.uleb128 .LVL265-.LVL264
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL265-.LVL264
	.uleb128 .LVL270-.LVL264
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
	.uleb128 .LVL270-.LVL264
	.uleb128 .LVL271-.LVL264
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL271-.LVL264
	.uleb128 .LFE34-.LVL264
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
.LLST77:
	.byte	0x6
	.4byte	.LVL264
	.byte	0x4
	.uleb128 .LVL264-.LVL264
	.uleb128 .LVL268-.LVL264
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL268-.LVL264
	.uleb128 .LFE34-.LVL264
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST78:
	.byte	0x6
	.4byte	.LVL264
	.byte	0x4
	.uleb128 .LVL264-.LVL264
	.uleb128 .LVL267-.LVL264
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL267-.LVL264
	.uleb128 .LVL269-.LVL264
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL270-.LVL264
	.uleb128 .LVL271-.LVL264
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST79:
	.byte	0x8
	.4byte	.LVL266
	.uleb128 .LVL270-.LVL266
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST72:
	.byte	0x6
	.4byte	.LVL256
	.byte	0x4
	.uleb128 .LVL256-.LVL256
	.uleb128 .LVL257-.LVL256
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL257-.LVL256
	.uleb128 .LVL262-.LVL256
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
	.uleb128 .LVL262-.LVL256
	.uleb128 .LVL263-.LVL256
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL263-.LVL256
	.uleb128 .LFE33-.LVL256
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
	.4byte	.LVL256
	.byte	0x4
	.uleb128 .LVL256-.LVL256
	.uleb128 .LVL260-.LVL256
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL260-.LVL256
	.uleb128 .LFE33-.LVL256
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST74:
	.byte	0x6
	.4byte	.LVL256
	.byte	0x4
	.uleb128 .LVL256-.LVL256
	.uleb128 .LVL259-.LVL256
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL259-.LVL256
	.uleb128 .LVL261-.LVL256
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL262-.LVL256
	.uleb128 .LVL263-.LVL256
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST75:
	.byte	0x8
	.4byte	.LVL258
	.uleb128 .LVL262-.LVL258
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST70:
	.byte	0x6
	.4byte	.LVL248
	.byte	0x4
	.uleb128 .LVL248-.LVL248
	.uleb128 .LVL249-.LVL248
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL249-.LVL248
	.uleb128 .LVL250-.LVL248
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL250-.LVL248
	.uleb128 .LVL254-.LVL248
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
	.uleb128 .LVL254-.LVL248
	.uleb128 .LVL255-.LVL248
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL255-.LVL248
	.uleb128 .LFE32-.LVL248
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST71:
	.byte	0x6
	.4byte	.LVL251
	.byte	0x4
	.uleb128 .LVL251-.LVL251
	.uleb128 .LVL252-.LVL251
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL252-.LVL251
	.uleb128 .LVL253-.LVL251
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
	.byte	0x32
	.byte	0x24
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0
.LLST68:
	.byte	0x6
	.4byte	.LVL243
	.byte	0x4
	.uleb128 .LVL243-.LVL243
	.uleb128 .LVL244-.LVL243
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL244-.LVL243
	.uleb128 .LVL246-.LVL243
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
	.uleb128 .LVL246-.LVL243
	.uleb128 .LVL247-.LVL243
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL247-.LVL243
	.uleb128 .LFE31-.LVL243
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
.LLST69:
	.byte	0x8
	.4byte	.LVL245
	.uleb128 .LVL246-.LVL245
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST66:
	.byte	0x6
	.4byte	.LVL238
	.byte	0x4
	.uleb128 .LVL238-.LVL238
	.uleb128 .LVL239-.LVL238
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL239-.LVL238
	.uleb128 .LVL241-.LVL238
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
	.uleb128 .LVL241-.LVL238
	.uleb128 .LVL242-.LVL238
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL242-.LVL238
	.uleb128 .LFE30-.LVL238
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
.LLST67:
	.byte	0x8
	.4byte	.LVL240
	.uleb128 .LVL241-.LVL240
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST62:
	.byte	0x6
	.4byte	.LVL230
	.byte	0x4
	.uleb128 .LVL230-.LVL230
	.uleb128 .LVL231-.LVL230
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL231-.LVL230
	.uleb128 .LVL232-.LVL230
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL232-.LVL230
	.uleb128 .LVL236-.LVL230
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
	.uleb128 .LVL236-.LVL230
	.uleb128 .LVL237-.LVL230
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL237-.LVL230
	.uleb128 .LFE29-.LVL230
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
.LLST63:
	.byte	0x6
	.4byte	.LVL230
	.byte	0x4
	.uleb128 .LVL230-.LVL230
	.uleb128 .LVL234-1-.LVL230
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL234-1-.LVL230
	.uleb128 .LVL236-.LVL230
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
	.uleb128 .LVL236-.LVL230
	.uleb128 .LFE29-.LVL230
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST64:
	.byte	0x8
	.4byte	.LVL233
	.uleb128 .LVL235-.LVL233
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST65:
	.byte	0x8
	.4byte	.LVL231
	.uleb128 .LVL234-1-.LVL231
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST60:
	.byte	0x6
	.4byte	.LVL225
	.byte	0x4
	.uleb128 .LVL225-.LVL225
	.uleb128 .LVL226-.LVL225
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL226-.LVL225
	.uleb128 .LVL228-.LVL225
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
	.uleb128 .LVL228-.LVL225
	.uleb128 .LVL229-.LVL225
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL229-.LVL225
	.uleb128 .LFE28-.LVL225
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
.LLST61:
	.byte	0x8
	.4byte	.LVL227
	.uleb128 .LVL228-.LVL227
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST58:
	.byte	0x6
	.4byte	.LVL219
	.byte	0x4
	.uleb128 .LVL219-.LVL219
	.uleb128 .LVL220-.LVL219
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL220-.LVL219
	.uleb128 .LVL223-.LVL219
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
	.uleb128 .LVL223-.LVL219
	.uleb128 .LVL224-.LVL219
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL224-.LVL219
	.uleb128 .LFE27-.LVL219
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
.LLST59:
	.byte	0x8
	.4byte	.LVL222
	.uleb128 .LVL223-.LVL222
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST57:
	.byte	0x6
	.4byte	.LVL206
	.byte	0x4
	.uleb128 .LVL206-.LVL206
	.uleb128 .LVL207-.LVL206
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL207-.LVL206
	.uleb128 .LVL210-.LVL206
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL210-.LVL206
	.uleb128 .LVL211-.LVL206
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
	.uleb128 .LVL211-.LVL206
	.uleb128 .LVL217-.LVL206
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL217-.LVL206
	.uleb128 .LVL218-.LVL206
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL218-.LVL206
	.uleb128 .LFE26-.LVL206
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
.LLST55:
	.byte	0x6
	.4byte	.LVL194
	.byte	0x4
	.uleb128 .LVL194-.LVL194
	.uleb128 .LVL195-.LVL194
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL195-.LVL194
	.uleb128 .LVL198-.LVL194
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL198-.LVL194
	.uleb128 .LVL199-.LVL194
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
	.uleb128 .LVL199-.LVL194
	.uleb128 .LVL204-.LVL194
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL204-.LVL194
	.uleb128 .LVL205-.LVL194
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL205-.LVL194
	.uleb128 .LFE25-.LVL194
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
.LLST56:
	.byte	0x8
	.4byte	.LVL203
	.uleb128 .LVL204-.LVL203
	.uleb128 0x1
	.byte	0x5f
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
	.uleb128 .LFE24-.LVL5
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
.LLST53:
	.byte	0x6
	.4byte	.LVL186
	.byte	0x4
	.uleb128 .LVL186-.LVL186
	.uleb128 .LVL188-.LVL186
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL188-.LVL186
	.uleb128 .LVL190-.LVL186
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL190-.LVL186
	.uleb128 .LFE23-.LVL186
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
.LLST54:
	.byte	0x6
	.4byte	.LVL186
	.byte	0x4
	.uleb128 .LVL186-.LVL186
	.uleb128 .LVL187-.LVL186
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL187-.LVL186
	.uleb128 .LVL191-.LVL186
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL191-.LVL186
	.uleb128 .LFE23-.LVL186
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
.LLST51:
	.byte	0x6
	.4byte	.LVL178
	.byte	0x4
	.uleb128 .LVL178-.LVL178
	.uleb128 .LVL180-.LVL178
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL180-.LVL178
	.uleb128 .LVL182-.LVL178
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL182-.LVL178
	.uleb128 .LFE22-.LVL178
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
.LLST52:
	.byte	0x6
	.4byte	.LVL178
	.byte	0x4
	.uleb128 .LVL178-.LVL178
	.uleb128 .LVL179-.LVL178
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL179-.LVL178
	.uleb128 .LVL183-.LVL178
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL183-.LVL178
	.uleb128 .LFE22-.LVL178
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
.LLST50:
	.byte	0x6
	.4byte	.LVL174
	.byte	0x4
	.uleb128 .LVL174-.LVL174
	.uleb128 .LVL175-.LVL174
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL175-.LVL174
	.uleb128 .LVL176-.LVL174
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
	.uleb128 .LVL176-.LVL174
	.uleb128 .LVL177-.LVL174
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL177-.LVL174
	.uleb128 .LFE21-.LVL174
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
.LLST42:
	.byte	0x6
	.4byte	.LVL150
	.byte	0x4
	.uleb128 .LVL150-.LVL150
	.uleb128 .LVL151-.LVL150
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL151-.LVL150
	.uleb128 .LVL152-.LVL150
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL152-.LVL150
	.uleb128 .LVL162-.LVL150
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
	.uleb128 .LVL162-.LVL150
	.uleb128 .LVL163-.LVL150
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL163-.LVL150
	.uleb128 .LFE20-.LVL150
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
	.4byte	.LVL150
	.byte	0x4
	.uleb128 .LVL150-.LVL150
	.uleb128 .LVL154-.LVL150
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL154-.LVL150
	.uleb128 .LVL157-.LVL150
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL157-.LVL150
	.uleb128 .LVL158-.LVL150
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
	.uleb128 .LVL158-.LVL150
	.uleb128 .LVL162-.LVL150
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL162-.LVL150
	.uleb128 .LFE20-.LVL150
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST45:
	.byte	0x6
	.4byte	.LVL153
	.byte	0x4
	.uleb128 .LVL153-.LVL153
	.uleb128 .LVL155-.LVL153
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL155-.LVL153
	.uleb128 .LVL156-.LVL153
	.uleb128 0x3
	.byte	0x78
	.sleb128 6
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL158-.LVL153
	.uleb128 .LVL160-.LVL153
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL160-.LVL153
	.uleb128 .LVL161-.LVL153
	.uleb128 0x3
	.byte	0x78
	.sleb128 6
	.byte	0x9f
	.byte	0
.LLST46:
	.byte	0x6
	.4byte	.LVL153
	.byte	0x4
	.uleb128 .LVL153-.LVL153
	.uleb128 .LVL154-.LVL153
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL158-.LVL153
	.uleb128 .LVL160-.LVL153
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST39:
	.byte	0x6
	.4byte	.LVL142
	.byte	0x4
	.uleb128 .LVL142-.LVL142
	.uleb128 .LVL143-.LVL142
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL143-.LVL142
	.uleb128 .LVL144-.LVL142
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL144-.LVL142
	.uleb128 .LVL147-.LVL142
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
	.uleb128 .LVL147-.LVL142
	.uleb128 .LVL148-.LVL142
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL148-.LVL142
	.uleb128 .LVL149-.LVL142
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
	.uleb128 .LVL149-.LVL142
	.uleb128 .LFE19-.LVL142
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST40:
	.byte	0x6
	.4byte	.LVL142
	.byte	0x4
	.uleb128 .LVL142-.LVL142
	.uleb128 .LVL145-1-.LVL142
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL145-1-.LVL142
	.uleb128 .LVL147-.LVL142
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
	.uleb128 .LVL147-.LVL142
	.uleb128 .LFE19-.LVL142
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST41:
	.byte	0x6
	.4byte	.LVL142
	.byte	0x4
	.uleb128 .LVL142-.LVL142
	.uleb128 .LVL145-1-.LVL142
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL145-1-.LVL142
	.uleb128 .LVL147-.LVL142
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
	.uleb128 .LVL147-.LVL142
	.uleb128 .LFE19-.LVL142
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST36:
	.byte	0x6
	.4byte	.LVL136
	.byte	0x4
	.uleb128 .LVL136-.LVL136
	.uleb128 .LVL137-.LVL136
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL137-.LVL136
	.uleb128 .LVL140-.LVL136
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
	.uleb128 .LVL140-.LVL136
	.uleb128 .LVL141-.LVL136
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL141-.LVL136
	.uleb128 .LFE18-.LVL136
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
.LLST37:
	.byte	0x8
	.4byte	.LVL138
	.uleb128 .LVL140-.LVL138
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST38:
	.byte	0x8
	.4byte	.LVL139
	.uleb128 .LVL140-.LVL139
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST33:
	.byte	0x6
	.4byte	.LVL127
	.byte	0x4
	.uleb128 .LVL127-.LVL127
	.uleb128 .LVL128-.LVL127
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL128-.LVL127
	.uleb128 .LVL129-.LVL127
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL129-.LVL127
	.uleb128 .LVL133-.LVL127
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
	.uleb128 .LVL133-.LVL127
	.uleb128 .LVL134-.LVL127
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL134-.LVL127
	.uleb128 .LVL135-.LVL127
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
	.uleb128 .LVL135-.LVL127
	.uleb128 .LFE17-.LVL127
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST34:
	.byte	0x6
	.4byte	.LVL127
	.byte	0x4
	.uleb128 .LVL127-.LVL127
	.uleb128 .LVL131-1-.LVL127
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL131-1-.LVL127
	.uleb128 .LVL133-.LVL127
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
	.uleb128 .LVL133-.LVL127
	.uleb128 .LFE17-.LVL127
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST35:
	.byte	0x6
	.4byte	.LVL130
	.byte	0x4
	.uleb128 .LVL130-.LVL130
	.uleb128 .LVL132-.LVL130
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL132-.LVL130
	.uleb128 .LVL133-.LVL130
	.uleb128 0x11
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	g_pdma_cfg_regbase_table
	.byte	0x22
	.byte	0
.LLST47:
	.byte	0x6
	.4byte	.LVL164
	.byte	0x4
	.uleb128 .LVL164-.LVL164
	.uleb128 .LVL165-.LVL164
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL165-.LVL164
	.uleb128 .LVL171-.LVL164
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL171-.LVL164
	.uleb128 .LVL172-.LVL164
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
	.uleb128 .LVL172-.LVL164
	.uleb128 .LVL173-.LVL164
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL173-.LVL164
	.uleb128 .LFE16-.LVL164
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
	.4byte	.LVL164
	.byte	0x4
	.uleb128 .LVL164-.LVL164
	.uleb128 .LVL167-1-.LVL164
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL167-1-.LVL164
	.uleb128 .LVL172-.LVL164
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
	.uleb128 .LVL172-.LVL164
	.uleb128 .LFE16-.LVL164
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST49:
	.byte	0x8
	.4byte	.LVL166
	.uleb128 .LVL170-.LVL166
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST31:
	.byte	0x6
	.4byte	.LVL119
	.byte	0x4
	.uleb128 .LVL119-.LVL119
	.uleb128 .LVL120-.LVL119
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL120-.LVL119
	.uleb128 .LVL121-.LVL119
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL121-.LVL119
	.uleb128 .LVL123-.LVL119
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
	.uleb128 .LVL123-.LVL119
	.uleb128 .LVL124-.LVL119
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL124-.LVL119
	.uleb128 .LVL125-.LVL119
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL125-.LVL119
	.uleb128 .LVL126-.LVL119
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
	.uleb128 .LVL126-.LVL119
	.uleb128 .LFE15-.LVL119
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST32:
	.byte	0x8
	.4byte	.LVL122
	.uleb128 .LVL123-.LVL122
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST29:
	.byte	0x6
	.4byte	.LVL113
	.byte	0x4
	.uleb128 .LVL113-.LVL113
	.uleb128 .LVL114-.LVL113
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL114-.LVL113
	.uleb128 .LVL115-.LVL113
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL115-.LVL113
	.uleb128 .LVL117-.LVL113
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
	.uleb128 .LVL117-.LVL113
	.uleb128 .LVL118-.LVL113
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL118-.LVL113
	.uleb128 .LFE14-.LVL113
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST30:
	.byte	0x8
	.4byte	.LVL116
	.uleb128 .LVL117-.LVL116
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST28:
	.byte	0x6
	.4byte	.LVL100
	.byte	0x4
	.uleb128 .LVL100-.LVL100
	.uleb128 .LVL101-.LVL100
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL101-.LVL100
	.uleb128 .LVL104-.LVL100
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL104-.LVL100
	.uleb128 .LVL105-.LVL100
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
	.uleb128 .LVL105-.LVL100
	.uleb128 .LVL111-.LVL100
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL111-.LVL100
	.uleb128 .LVL112-.LVL100
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL112-.LVL100
	.uleb128 .LFE13-.LVL100
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
	.4byte	.LVL88
	.byte	0x4
	.uleb128 .LVL88-.LVL88
	.uleb128 .LVL89-.LVL88
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL89-.LVL88
	.uleb128 .LVL92-.LVL88
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL92-.LVL88
	.uleb128 .LVL93-.LVL88
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
	.uleb128 .LVL93-.LVL88
	.uleb128 .LVL98-.LVL88
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL98-.LVL88
	.uleb128 .LVL99-.LVL88
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL99-.LVL88
	.uleb128 .LFE12-.LVL88
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
	.uleb128 .LFE11-.LVL0
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
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL4-.LVL3
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL4-.LVL3
	.uleb128 .LFE11-.LVL3
	.uleb128 0x8
	.byte	0x7a
	.sleb128 0
	.byte	0x3
	.4byte	g_pdma_cfg_regbase_table
	.byte	0x22
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL9-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL9-.LVL8
	.uleb128 .LVL10-.LVL8
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL10-.LVL8
	.uleb128 .LVL11-.LVL8
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
	.uleb128 .LVL11-.LVL8
	.uleb128 .LFE9-.LVL8
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL9-.LVL8
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL11-.LVL8
	.uleb128 .LVL13-.LVL8
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST5:
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
	.uleb128 .LVL19-.LVL14
	.uleb128 0x3
	.byte	0x78
	.sleb128 6
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL19-.LVL14
	.uleb128 .LFE8-.LVL14
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
	.byte	0x8
	.4byte	.LVL14
	.uleb128 .LVL17-.LVL14
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL45
	.byte	0x4
	.uleb128 .LVL45-.LVL45
	.uleb128 .LVL46-.LVL45
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL46-.LVL45
	.uleb128 .LVL49-.LVL45
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL49-.LVL45
	.uleb128 .LVL50-.LVL45
	.uleb128 0x3
	.byte	0x78
	.sleb128 6
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL50-.LVL45
	.uleb128 .LFE7-.LVL45
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
	.byte	0x8
	.4byte	.LVL45
	.uleb128 .LVL48-.LVL45
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL20
	.byte	0x4
	.uleb128 .LVL20-.LVL20
	.uleb128 .LVL21-.LVL20
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL21-.LVL20
	.uleb128 .LVL24-.LVL20
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL24-.LVL20
	.uleb128 .LVL25-.LVL20
	.uleb128 0x3
	.byte	0x78
	.sleb128 6
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL25-.LVL20
	.uleb128 .LFE6-.LVL20
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
	.4byte	.LVL20
	.uleb128 .LVL23-.LVL20
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST17:
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
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL56-.LVL51
	.uleb128 .LVL57-.LVL51
	.uleb128 0x3
	.byte	0x78
	.sleb128 6
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL57-.LVL51
	.uleb128 .LVL58-.LVL51
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
	.uleb128 .LVL58-.LVL51
	.uleb128 .LVL60-.LVL51
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL60-.LVL51
	.uleb128 .LFE5-.LVL51
	.uleb128 0x3
	.byte	0x78
	.sleb128 6
	.byte	0x9f
	.byte	0
.LLST18:
	.byte	0x6
	.4byte	.LVL51
	.byte	0x4
	.uleb128 .LVL51-.LVL51
	.uleb128 .LVL53-.LVL51
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL53-.LVL51
	.uleb128 .LVL54-1-.LVL51
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL54-1-.LVL51
	.uleb128 .LVL55-.LVL51
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL58-.LVL51
	.uleb128 .LVL60-.LVL51
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL61
	.byte	0x4
	.uleb128 .LVL61-.LVL61
	.uleb128 .LVL62-.LVL61
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL62-.LVL61
	.uleb128 .LVL67-.LVL61
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL67-.LVL61
	.uleb128 .LVL68-.LVL61
	.uleb128 0x2
	.byte	0x72
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL68-.LVL61
	.uleb128 .LFE4-.LVL61
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST20:
	.byte	0x6
	.4byte	.LVL70
	.byte	0x4
	.uleb128 .LVL70-.LVL70
	.uleb128 .LVL71-.LVL70
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL71-.LVL70
	.uleb128 .LVL72-.LVL70
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
	.uleb128 .LVL72-.LVL70
	.uleb128 .LVL76-.LVL70
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL76-.LVL70
	.uleb128 .LVL82-.LVL70
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
	.uleb128 .LVL82-.LVL70
	.uleb128 .LVL86-.LVL70
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL86-.LVL70
	.uleb128 .LVL87-.LVL70
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
	.uleb128 .LVL87-.LVL70
	.uleb128 .LFE51-.LVL70
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST22:
	.byte	0x6
	.4byte	.LVL72
	.byte	0x4
	.uleb128 .LVL72-.LVL72
	.uleb128 .LVL77-.LVL72
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL77-.LVL72
	.uleb128 .LFE51-.LVL72
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0
.LLST23:
	.byte	0x6
	.4byte	.LVL75
	.byte	0x4
	.uleb128 .LVL75-.LVL75
	.uleb128 .LVL77-1-.LVL75
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL80-.LVL75
	.uleb128 .LVL81-1-.LVL75
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL85-.LVL75
	.uleb128 .LVL87-.LVL75
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST24:
	.byte	0x6
	.4byte	.LVL73
	.byte	0x4
	.uleb128 .LVL73-.LVL73
	.uleb128 .LVL74-.LVL73
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL74-.LVL73
	.uleb128 .LVL77-1-.LVL73
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vdma_regbase_table
	.byte	0x4
	.uleb128 .LVL78-.LVL73
	.uleb128 .LVL79-.LVL73
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL79-.LVL73
	.uleb128 .LVL81-1-.LVL73
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vdma_regbase_table+4
	.byte	0x4
	.uleb128 .LVL83-.LVL73
	.uleb128 .LVL84-.LVL73
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL84-.LVL73
	.uleb128 .LVL87-.LVL73
	.uleb128 0x5
	.byte	0x3
	.4byte	g_vdma_regbase_table+4
	.byte	0
.LLST25:
	.byte	0x6
	.4byte	.LVL74
	.byte	0x4
	.uleb128 .LVL74-.LVL74
	.uleb128 .LVL77-1-.LVL74
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL79-.LVL74
	.uleb128 .LVL81-1-.LVL74
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL84-.LVL74
	.uleb128 .LVL87-.LVL74
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x194
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.4byte	.LFB52
	.4byte	.LFE52-.LFB52
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB51
	.4byte	.LFE51-.LFB51
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
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
	.4byte	.LFB46
	.4byte	.LFE46-.LFB46
	.4byte	.LFB47
	.4byte	.LFE47-.LFB47
	.4byte	.LFB48
	.4byte	.LFE48-.LFB48
	.4byte	.LFB49
	.4byte	.LFE49-.LFB49
	.4byte	.LFB50
	.4byte	.LFE50-.LFB50
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
.LLRL21:
	.byte	0x5
	.4byte	.LBB15
	.byte	0x4
	.uleb128 .LBB15-.LBB15
	.uleb128 .LBE15-.LBB15
	.byte	0x4
	.uleb128 .LBB21-.LBB15
	.uleb128 .LBE21-.LBB15
	.byte	0x4
	.uleb128 .LBB22-.LBB15
	.uleb128 .LBE22-.LBB15
	.byte	0x4
	.uleb128 .LBB23-.LBB15
	.uleb128 .LBE23-.LBB15
	.byte	0x4
	.uleb128 .LBB24-.LBB15
	.uleb128 .LBE24-.LBB15
	.byte	0
.LLRL44:
	.byte	0x5
	.4byte	.LBB28
	.byte	0x4
	.uleb128 .LBB28-.LBB28
	.uleb128 .LBE28-.LBB28
	.byte	0x4
	.uleb128 .LBB32-.LBB28
	.uleb128 .LBE32-.LBB28
	.byte	0
.LLRL134:
	.byte	0x7
	.4byte	.LFB11
	.uleb128 .LFE11-.LFB11
	.byte	0x7
	.4byte	.LFB24
	.uleb128 .LFE24-.LFB24
	.byte	0x7
	.4byte	.LFB9
	.uleb128 .LFE9-.LFB9
	.byte	0x7
	.4byte	.LFB8
	.uleb128 .LFE8-.LFB8
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
	.byte	0x7
	.4byte	.LFB52
	.uleb128 .LFE52-.LFB52
	.byte	0x7
	.4byte	.LFB7
	.uleb128 .LFE7-.LFB7
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
	.byte	0x7
	.4byte	.LFB51
	.uleb128 .LFE51-.LFB51
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
	.4byte	.LFB16
	.uleb128 .LFE16-.LFB16
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
	.byte	0x7
	.4byte	.LFB50
	.uleb128 .LFE50-.LFB50
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF36:
	.string	"PDMA_IDLE"
.LASF461:
	.string	"wppt"
.LASF10:
	.string	"long int"
.LASF271:
	.string	"HAL_CLOCK_CG_SPIMST0"
.LASF272:
	.string	"HAL_CLOCK_CG_SPIMST1"
.LASF273:
	.string	"HAL_CLOCK_CG_SPIMST2"
.LASF289:
	.string	"HAL_CLOCK_CG_EFUSE"
.LASF364:
	.string	"UART_DMA_DOMAIN_UART1_TX"
.LASF372:
	.string	"I3C_DMA_DOMAIN_I3C0_TX"
.LASF166:
	.string	"DMA_GLB_BUSY_T"
.LASF203:
	.string	"dma_glb_cpu1_clr"
.LASF124:
	.string	"DMA_GLB_CPU0_CFG_T"
.LASF151:
	.string	"DMA_GLB_CPU0_SET_T"
.LASF265:
	.string	"HAL_CLOCK_CG_PMU_1M"
.LASF234:
	.string	"VDMA_SW_MV_BYTE"
.LASF432:
	.string	"vdma_get_interrupt_status"
.LASF43:
	.string	"pdma_master_type_t"
.LASF219:
	.string	"VDMA_COUNT"
.LASF19:
	.string	"PDMA_I3C0_RX"
.LASF422:
	.string	"vdma_pop_data"
.LASF345:
	.string	"PDMA_DMA_CHANNEL_I3C_END"
.LASF477:
	.string	"uart_dma_interrupt_hander"
.LASF469:
	.string	"internal_dma_enable_irq"
.LASF169:
	.string	"CLK_SET_RX"
.LASF354:
	.string	"argument"
.LASF464:
	.string	"pdma_init"
.LASF379:
	.string	"hal_memview_infrasys_to_riscv"
.LASF199:
	.string	"dma_glbsta"
.LASF192:
	.string	"pdma_rlct"
.LASF315:
	.string	"HAL_CLOCK_CG_CMSYS_ROM"
.LASF269:
	.string	"HAL_CLOCK_CG_BUS_ERR_AO"
.LASF370:
	.string	"uart_dma_glb_reg_table"
.LASF285:
	.string	"HAL_CLOCK_CG_USB"
.LASF262:
	.string	"HAL_CLOCK_CG_KEY_SCAN_BCLK"
.LASF162:
	.string	"DMA_GLB_SWRST_T"
.LASF406:
	.string	"sw_move_byte"
.LASF376:
	.string	"i3c_dma_domain_channel_t"
.LASF3:
	.string	"unsigned int"
.LASF380:
	.string	"hal_nvic_enable_irq"
.LASF212:
	.string	"I3C_DMA_REGISTER_T"
.LASF176:
	.string	"WPTO"
.LASF281:
	.string	"HAL_CLOCK_CG_CKSYS_DEBUG_DIS"
.LASF258:
	.string	"HAL_CLOCK_CG_OSTIMER"
.LASF419:
	.string	"ready_for_read"
.LASF205:
	.string	"dma_glblimiter"
.LASF412:
	.string	"vdma_get_available_send_space"
.LASF132:
	.string	"PDMA_COUNT_T"
.LASF361:
	.string	"g_vdma_init_status"
.LASF344:
	.string	"PDMA_DMA_CHANNEL_I3C1_RX"
.LASF416:
	.string	"vdma_pop_data_multi_bytes"
.LASF377:
	.string	"i3c_dma_glb_reg_table"
.LASF131:
	.string	"COUNT"
.LASF267:
	.string	"HAL_CLOCK_CG_SPIMST0_BUS"
.LASF474:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF207:
	.string	"dma_glb_busy"
.LASF194:
	.string	"PDMA_STA_REGISTER_T"
.LASF291:
	.string	"HAL_CLOCK_CG_CMSYS_BUS"
.LASF56:
	.string	"VDMA_UART2TX"
.LASF339:
	.string	"MCU_DMA_CHANNEL_UART_END"
.LASF418:
	.string	"read_address"
.LASF76:
	.string	"SPI_MST1_IRQn"
.LASF286:
	.string	"HAL_CLOCK_CG_AUD_INTBUS"
.LASF93:
	.string	"RESERVE1"
.LASF313:
	.string	"HAL_CLOCK_CG_USB_BUS"
.LASF334:
	.string	"MCU_DMA_CHANNEL_UART0_RX"
.LASF114:
	.string	"RESERVE6"
.LASF415:
	.string	"receive_bytes"
.LASF236:
	.string	"VDMA_BYTE_TO_BNDRY"
.LASF353:
	.string	"func"
.LASF336:
	.string	"MCU_DMA_CHANNEL_UART1_RX"
.LASF204:
	.string	"dma_glb_swrst"
.LASF88:
	.string	"BT_IRQn"
.LASF239:
	.string	"HAL_CLOCK_CG_AUXADC"
.LASF427:
	.string	"vdma_push_data"
.LASF352:
	.string	"g_pdma_cfg_regbase_table"
.LASF112:
	.string	"RG_GLB_CPU3_INT_SET"
.LASF104:
	.string	"RG_GLB_BUSY"
.LASF89:
	.string	"IRQ_NUMBER_MAX"
.LASF276:
	.string	"HAL_CLOCK_CG_BT_MAC_CONN"
.LASF32:
	.string	"PDMA_ERROR_CHANNEL"
.LASF18:
	.string	"PDMA_I3C0_TX"
.LASF253:
	.string	"HAL_CLOCK_CG_GLB_CON_DEBUG_DIS"
.LASF395:
	.string	"irq_number"
.LASF403:
	.string	"vdma_get_hw_write_point"
.LASF63:
	.string	"VDMA_OK"
.LASF463:
	.string	"pdma_deinit"
.LASF37:
	.string	"PDMA_BUSY"
.LASF8:
	.string	"signed char"
.LASF53:
	.string	"VDMA_UART0RX"
.LASF251:
	.string	"HAL_CLOCK_CG_I3C0"
.LASF330:
	.string	"HAL_CLOCK_STATUS_OK"
.LASF227:
	.string	"VDMA_WRPTR"
.LASF16:
	.string	"uint32_t"
.LASF243:
	.string	"HAL_CLOCK_CG_PWM_3"
.LASF116:
	.string	"RG_GLB_CLK_SET"
.LASF309:
	.string	"HAL_CLOCK_CG_SEC_MON"
.LASF274:
	.string	"HAL_CLOCK_CG_I3C"
.LASF154:
	.string	"DMA_GLB_CPU0_CLR_T"
.LASF226:
	.string	"VDMA_PGMADDR"
.LASF450:
	.string	"pdma_get_running_status"
.LASF340:
	.string	"PDMA_DMA_CHANNEL_I3C_BEGIN"
.LASF147:
	.string	"IT_RX"
.LASF117:
	.string	"RG_GLB_CLK_CLR"
.LASF156:
	.string	"CPU1_SET_RX"
.LASF79:
	.string	"UART_DMA_IRQn"
.LASF343:
	.string	"PDMA_DMA_CHANNEL_I3C1_TX"
.LASF46:
	.string	"count"
.LASF348:
	.string	"g_dma_clk_table"
.LASF424:
	.string	"write_address"
.LASF324:
	.string	"HAL_CLOCK_CG_PWM_MULTI_CTRL"
.LASF277:
	.string	"HAL_CLOCK_CG_IRTX"
.LASF405:
	.string	"vdma_set_sw_move_byte"
.LASF278:
	.string	"HAL_CLOCK_CG_AUD_TEST"
.LASF209:
	.string	"dma_glb_clk_set"
.LASF39:
	.string	"PDMA_TX"
.LASF218:
	.string	"VDMA_CON"
.LASF2:
	.string	"long long unsigned int"
.LASF391:
	.string	"file"
.LASF252:
	.string	"HAL_CLOCK_CG_I3C_DMA0"
.LASF302:
	.string	"HAL_CLOCK_CG_I3C_DMA1"
.LASF283:
	.string	"HAL_CLOCK_CG_ESC"
.LASF200:
	.string	"dma_glb_cpu0_set"
.LASF305:
	.string	"HAL_CLOCK_CG_IRRX"
.LASF148:
	.string	"DMA_GLBSTA_T"
.LASF44:
	.string	"burst_mode"
.LASF347:
	.string	"g_dma_irq_table"
.LASF462:
	.string	"wpto"
.LASF101:
	.string	"RESERVE2"
.LASF106:
	.string	"RESERVE4"
.LASF335:
	.string	"MCU_DMA_CHANNEL_UART1_TX"
.LASF350:
	.string	"g_pdma_channel_map_table"
.LASF142:
	.string	"PDMA_PGMADDR_T"
.LASF102:
	.string	"RG_GLB_LIMITER"
.LASF270:
	.string	"HAL_CLOCK_CG_SEC_MON_AO"
.LASF97:
	.string	"RG_GLB_CPU1_INT_CFG"
.LASF141:
	.string	"PGMADDR"
.LASF396:
	.string	"vdma_dump_reg_list"
.LASF445:
	.string	"enable"
.LASF50:
	.string	"pdma_callback_t"
.LASF459:
	.string	"dma_control"
.LASF323:
	.string	"HAL_CLOCK_CG_DUMMY_END"
.LASF143:
	.string	"PDMA_START_T"
.LASF454:
	.string	"pdma_start_interrupt"
.LASF363:
	.string	"UART_DMA_DOMAIN_UART0_RX"
.LASF404:
	.string	"write_point"
.LASF220:
	.string	"VDMA_CON_UNION"
.LASF90:
	.string	"IRQn_Type"
.LASF279:
	.string	"HAL_CLOCK_CG_SEC_MON_TOP"
.LASF438:
	.string	"vdma_stop"
.LASF381:
	.string	"hal_nvic_register_isr_handler"
.LASF52:
	.string	"VDMA_UART0TX"
.LASF13:
	.string	"size_t"
.LASF386:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF436:
	.string	"vdma_configure"
.LASF223:
	.string	"VDMA_ACKINT"
.LASF181:
	.string	"PDMA_RLCT_T"
.LASF400:
	.string	"user_data"
.LASF260:
	.string	"HAL_CLOCK_CG_GPTIMER_SEC"
.LASF48:
	.string	"_Bool"
.LASF64:
	.string	"vdma_status_t"
.LASF456:
	.string	"pdma_start_polling"
.LASF235:
	.string	"VDMA_BNDRY_ADDR"
.LASF210:
	.string	"dma_glb_clk_clr"
.LASF392:
	.string	"vdma_index"
.LASF382:
	.string	"hal_memview_riscv_to_infrasys"
.LASF257:
	.string	"HAL_CLOCK_CG_SPM_SYS"
.LASF288:
	.string	"HAL_CLOCK_CG_SEJ"
.LASF256:
	.string	"HAL_CLOCK_CG_SPM_DIV"
.LASF77:
	.string	"RTC_IRQn"
.LASF201:
	.string	"dma_glb_cpu0_clr"
.LASF292:
	.string	"HAL_CLOCK_CG_MEM_BUS"
.LASF295:
	.string	"HAL_CLOCK_CG_OSC_LS_D2"
.LASF351:
	.string	"g_pdma_status_regbase_table"
.LASF42:
	.string	"PDMA_RX_RINGBUFF"
.LASF230:
	.string	"VDMA_FFSTA"
.LASF35:
	.string	"pdma_status_t"
.LASF314:
	.string	"HAL_CLOCK_CG_USB_DMA"
.LASF134:
	.string	"SIZE"
.LASF183:
	.string	"pdma_wppt"
.LASF66:
	.string	"VDMA_EVENT_TRANSACTION_SUCCESS"
.LASF360:
	.string	"g_vdma_callback"
.LASF217:
	.string	"VDMA_CON_CELLS"
.LASF237:
	.string	"VDMA_BYTE_AVAIL"
.LASF214:
	.string	"VDMA_SIZE"
.LASF206:
	.string	"dma_glb_dbg"
.LASF328:
	.string	"HAL_CLOCK_STATUS_INVALID_PARAMETER"
.LASF264:
	.string	"HAL_CLOCK_CG_UART0"
.LASF246:
	.string	"HAL_CLOCK_CG_UART1"
.LASF247:
	.string	"HAL_CLOCK_CG_UART2"
.LASF238:
	.string	"VDMA_REGISTER_T"
.LASF161:
	.string	"SW_RESET"
.LASF407:
	.string	"h_size"
.LASF160:
	.string	"DMA_GLB_CPU1_CLR_T"
.LASF187:
	.string	"pdma_pgmaddr"
.LASF12:
	.string	"char"
.LASF346:
	.string	"dma_channel_t"
.LASF282:
	.string	"HAL_CLOCK_CG_SFC"
.LASF356:
	.string	"g_pdma_callback"
.LASF216:
	.string	"VDMA_ITEN"
.LASF65:
	.string	"VDMA_EVENT_TRANSACTION_ERROR"
.LASF208:
	.string	"dma_glb_intr"
.LASF38:
	.string	"pdma_running_status_t"
.LASF362:
	.string	"UART_DMA_DOMAIN_UART0_TX"
.LASF133:
	.string	"DIRECTION"
.LASF71:
	.string	"SW_IRQn"
.LASF119:
	.string	"CPU0_CFG_TX"
.LASF383:
	.string	"hal_clock_enable"
.LASF29:
	.string	"PDMA_EVENT_TRANSACTION_SUCCESS"
.LASF310:
	.string	"HAL_CLOCK_CG_AESOTF"
.LASF22:
	.string	"PDMA_END_CHANNEL"
.LASF215:
	.string	"VDMA_SETTING"
.LASF448:
	.string	"pdma_dump_reg_list"
.LASF393:
	.string	"vdma"
.LASF420:
	.string	"byte_to_bndry"
.LASF429:
	.string	"alert_length"
.LASF14:
	.string	"uint8_t"
.LASF367:
	.string	"UART_DMA_DOMAIN_UART2_RX"
.LASF375:
	.string	"I3C_DMA_DOMAIN_I3C1_RX"
.LASF95:
	.string	"RG_GLB_CPU0_INT_SET"
.LASF27:
	.string	"pdma_transfer_size_format_t"
.LASF304:
	.string	"HAL_CLOCK_CG_SPISLV_BUS"
.LASF92:
	.string	"RG_GLB_STA"
.LASF322:
	.string	"HAL_CLOCK_CG_PSEUDO_END"
.LASF338:
	.string	"MCU_DMA_CHANNEL_UART2_RX"
.LASF189:
	.string	"PDMA_CFG_REGISTER_T"
.LASF105:
	.string	"RG_GLB_INTR"
.LASF164:
	.string	"DMA_GLBLIMITER_T"
.LASF113:
	.string	"RG_GLB_CPU3_INT_CLR"
.LASF145:
	.string	"IT_TX"
.LASF85:
	.string	"SPI_MST0_IRQn"
.LASF300:
	.string	"HAL_CLOCK_CG_SPIMST2_BUS"
.LASF394:
	.string	"vdma_callback"
.LASF186:
	.string	"pdma_con"
.LASF307:
	.string	"HAL_CLOCK_CG_AIO"
.LASF6:
	.string	"long long int"
.LASF398:
	.string	"vdma_register_callback"
.LASF180:
	.string	"RLCT"
.LASF293:
	.string	"HAL_CLOCK_CG_CONN_BUS"
.LASF129:
	.string	"CLK_CFG_RX"
.LASF84:
	.string	"I3C0_DMA_IRQn"
.LASF167:
	.string	"DMA_GLB_INTR_T"
.LASF168:
	.string	"CLK_SET_TX"
.LASF389:
	.string	"pdma_callback"
.LASF342:
	.string	"PDMA_DMA_CHANNEL_I3C0_RX"
.LASF197:
	.string	"dma_glb_clk_cfg"
.LASF446:
	.string	"internal_vdma_irq_control"
.LASF191:
	.string	"pdma_ackint"
.LASF349:
	.string	"g_dma_reg_table"
.LASF298:
	.string	"HAL_CLOCK_CG_AUXADC_SRAM"
.LASF452:
	.string	"pdma_register_callback"
.LASF443:
	.string	"i3c_dma_interrupt_hander"
.LASF408:
	.string	"vdma_get_hw_read_offset"
.LASF96:
	.string	"RG_GLB_CPU0_INT_CLR"
.LASF430:
	.string	"vdma_set_threshold"
.LASF426:
	.string	"vdma_push_data_4bytes"
.LASF476:
	.string	"g_vdma_regbase_table"
.LASF86:
	.string	"IRQ_GEN_IRQn"
.LASF75:
	.string	"UART_IRQn"
.LASF421:
	.string	"vdma_pop_data_4bytes"
.LASF45:
	.string	"size"
.LASF165:
	.string	"DMA_GLB_DBG_T"
.LASF153:
	.string	"CPU0_CLR_RX"
.LASF317:
	.string	"HAL_CLOCK_CG_PSUEDO_OSC_26M"
.LASF98:
	.string	"RG_GLB_CPU1_INT_SET"
.LASF140:
	.string	"PDMA_CON_T"
.LASF40:
	.string	"PDMA_RX"
.LASF107:
	.string	"RG_GLB_CPU2_INT_CFG"
.LASF31:
	.string	"PDMA_ERROR"
.LASF242:
	.string	"HAL_CLOCK_CG_PWM_2"
.LASF280:
	.string	"HAL_CLOCK_CG_BUS_ERR_TOP"
.LASF244:
	.string	"HAL_CLOCK_CG_PWM_4"
.LASF245:
	.string	"HAL_CLOCK_CG_ARGB_BCLK"
.LASF87:
	.string	"USB_IRQn"
.LASF294:
	.string	"HAL_CLOCK_CG_AUD_ENGINE"
.LASF157:
	.string	"DMA_GLB_CPU1_SET_T"
.LASF55:
	.string	"VDMA_UART1RX"
.LASF366:
	.string	"UART_DMA_DOMAIN_UART2_TX"
.LASF374:
	.string	"I3C_DMA_DOMAIN_I3C1_TX"
.LASF414:
	.string	"vdma_get_available_receive_bytes"
.LASF453:
	.string	"pdma_stop"
.LASF248:
	.string	"HAL_CLOCK_CG_UART_DMA0"
.LASF249:
	.string	"HAL_CLOCK_CG_UART_DMA1"
.LASF250:
	.string	"HAL_CLOCK_CG_UART_DMA2"
.LASF254:
	.string	"HAL_CLOCK_CG_SPM_PCLK"
.LASF138:
	.string	"ITEN"
.LASF303:
	.string	"HAL_CLOCK_CG_TRNG"
.LASF21:
	.string	"PDMA_I3C1_RX"
.LASF196:
	.string	"dma_glb_cpu1_cfg"
.LASF401:
	.string	"vdma_get_hw_write_offset"
.LASF81:
	.string	"MCU_DMA_IRQn"
.LASF449:
	.string	"pdma_cfg"
.LASF444:
	.string	"internal_vdma_restore_default_value"
.LASF428:
	.string	"vdma_set_alert_length"
.LASF188:
	.string	"pdma_start"
.LASF457:
	.string	"pdma_configure"
.LASF7:
	.string	"long double"
.LASF15:
	.string	"uint16_t"
.LASF475:
	.string	"IRQn"
.LASF163:
	.string	"LIMITER"
.LASF146:
	.string	"RUN_RX"
.LASF263:
	.string	"HAL_CLOCK_CG_KEY_SCAN_F2M"
.LASF437:
	.string	"vdma_config"
.LASF128:
	.string	"CLK_CFG_TX"
.LASF423:
	.string	"vdma_push_data_multi_bytes"
.LASF390:
	.string	"channel"
.LASF371:
	.string	"i3c_pdma_domain_channel_index"
.LASF74:
	.string	"KEYSCAN_IRQn"
.LASF341:
	.string	"PDMA_DMA_CHANNEL_I3C0_TX"
.LASF232:
	.string	"VDMA_FFSIZE"
.LASF118:
	.string	"DMA_REGISTER_GLOABL_T"
.LASF229:
	.string	"VDMA_FFCNT"
.LASF355:
	.string	"pdma_user_callback_t"
.LASF410:
	.string	"vdma_get_hw_read_point"
.LASF388:
	.string	"pda_status"
.LASF221:
	.string	"VDMA_START"
.LASF182:
	.string	"PDMA_LIMITER_T"
.LASF296:
	.string	"HAL_CLOCK_CG_OSC_HS_D2"
.LASF319:
	.string	"HAL_CLOCK_CG_PSEUDO_DCXO_DIG_MACRO"
.LASF297:
	.string	"HAL_CLOCK_CG_OSC_HS_D4"
.LASF59:
	.string	"vdma_channel_t"
.LASF178:
	.string	"PDMA_INTSTA_T"
.LASF9:
	.string	"short int"
.LASF431:
	.string	"threshold"
.LASF275:
	.string	"HAL_CLOCK_CG_BT_HOP"
.LASF327:
	.string	"HAL_CLOCK_STATUS_UNINITIALIZED"
.LASF306:
	.string	"HAL_CLOCK_CG_IRRX_BUS"
.LASF126:
	.string	"CPU1_CFG_RX"
.LASF213:
	.string	"VDMA_DIRECTION"
.LASF99:
	.string	"RG_GLB_CPU1_INT_CLR"
.LASF28:
	.string	"PDMA_EVENT_TRANSACTION_ERROR"
.LASF72:
	.string	"LED_IRQn"
.LASF333:
	.string	"MCU_DMA_CHANNEL_UART0_TX"
.LASF152:
	.string	"CPU0_CLR_TX"
.LASF198:
	.string	"dma_config_ch"
.LASF255:
	.string	"HAL_CLOCK_CG_SPM_BCLK_CM33"
.LASF82:
	.string	"EINT_IRQn"
.LASF47:
	.string	"master_type"
.LASF78:
	.string	"GPT_IRQn"
.LASF478:
	.string	"internal_dma_check_running_status"
.LASF54:
	.string	"VDMA_UART1TX"
.LASF100:
	.string	"RG_GLB_SWRST"
.LASF471:
	.string	"internal_dma_enable_clock"
.LASF123:
	.string	"word"
.LASF290:
	.string	"HAL_CLOCK_CG_BT_MAC"
.LASF411:
	.string	"read_point"
.LASF25:
	.string	"PDMA_HALF_WORD"
.LASF20:
	.string	"PDMA_I3C1_TX"
.LASF177:
	.string	"PDMA_WPTO_T"
.LASF318:
	.string	"HAL_CLOCK_CG_PSEUDO_DCXO_PWR_CTRL"
.LASF127:
	.string	"DMA_GLB_CPU1_CFG_T"
.LASF458:
	.string	"pdma_config"
.LASF261:
	.string	"HAL_CLOCK_CG_SECURITY_AO"
.LASF172:
	.string	"CLK_CLR_RX"
.LASF122:
	.string	"field"
.LASF144:
	.string	"RUN_TX"
.LASF467:
	.string	"domain_offset"
.LASF473:
	.string	"irq_status"
.LASF413:
	.string	"available_space"
.LASF442:
	.string	"vdma_init"
.LASF369:
	.string	"uart_vdma_domain_channel_index"
.LASF224:
	.string	"DUMMY1_OFFSET"
.LASF417:
	.string	"data"
.LASF175:
	.string	"PDMA_WPPT_T"
.LASF11:
	.string	"long unsigned int"
.LASF23:
	.string	"pdma_channel_t"
.LASF455:
	.string	"address"
.LASF68:
	.string	"base_address"
.LASF240:
	.string	"HAL_CLOCK_CG_PWM_DMA_0"
.LASF185:
	.string	"pdma_count"
.LASF468:
	.string	"internal_dma_disable_irq"
.LASF359:
	.string	"vdma_user_callback_t"
.LASF173:
	.string	"DMA_GLB_CLK_CLR_T"
.LASF332:
	.string	"MCU_DMA_CHANNEL_UART_BEGIN"
.LASF320:
	.string	"HAL_CLOCK_CG_PSEUDO_RGU_32K"
.LASF69:
	.string	"vdma_config_t"
.LASF179:
	.string	"PDMA_ACKINT_T"
.LASF115:
	.string	"RG_GLB_CLK_CFG"
.LASF125:
	.string	"CPU1_CFG_TX"
.LASF222:
	.string	"VDMA_INTSTA"
.LASF24:
	.string	"PDMA_BYTE"
.LASF397:
	.string	"vdma_buffer_is_empty"
.LASF174:
	.string	"WPPT"
.LASF225:
	.string	"VDMA_LIMITER"
.LASF268:
	.string	"HAL_CLOCK_CG_SPIMST1_BUS"
.LASF4:
	.string	"unsigned char"
.LASF26:
	.string	"PDMA_WORD"
.LASF51:
	.string	"VDMA_START_CHANNEL"
.LASF158:
	.string	"CPU1_CLR_TX"
.LASF30:
	.string	"pdma_event_t"
.LASF460:
	.string	"pdma_set_ring_buffer"
.LASF49:
	.string	"pdma_config_t"
.LASF233:
	.string	"DUMMY2_OFFSET"
.LASF357:
	.string	"g_pdma_init_status"
.LASF150:
	.string	"CPU0_SET_RX"
.LASF337:
	.string	"MCU_DMA_CHANNEL_UART2_TX"
.LASF136:
	.string	"SETTING"
.LASF120:
	.string	"CPU0_CFG_RX"
.LASF155:
	.string	"CPU1_SET_TX"
.LASF308:
	.string	"HAL_CLOCK_CG_BUS_ERR"
.LASF67:
	.string	"vdma_event_t"
.LASF111:
	.string	"RG_GLB_CPU3_INT_CFG"
.LASF466:
	.string	"dma_channel"
.LASF358:
	.string	"g_vdma_channel_map_table"
.LASF228:
	.string	"VDMA_RDPTR"
.LASF108:
	.string	"RG_GLB_CPU2_INT_SET"
.LASF425:
	.string	"byte_avail"
.LASF402:
	.string	"write_offset"
.LASF259:
	.string	"HAL_CLOCK_CG_GPTIMER"
.LASF231:
	.string	"VDMA_ALTLEN"
.LASF325:
	.string	"hal_clock_cg_id"
.LASF433:
	.string	"is_enabled"
.LASF184:
	.string	"pdma_wpto"
.LASF399:
	.string	"callback"
.LASF365:
	.string	"UART_DMA_DOMAIN_UART1_RX"
.LASF373:
	.string	"I3C_DMA_DOMAIN_I3C0_RX"
.LASF284:
	.string	"HAL_CLOCK_CG_SPISLV"
.LASF479:
	.string	"internal_dma_check_idle_status"
.LASF83:
	.string	"I3C0_IRQn"
.LASF384:
	.string	"light_assert"
.LASF171:
	.string	"CLK_CLR_TX"
.LASF34:
	.string	"PDMA_OK"
.LASF472:
	.string	"internal_dma_register_irq_callback"
.LASF202:
	.string	"dma_glb_cpu1_set"
.LASF311:
	.string	"HAL_CLOCK_CG_AESOTF_ESC"
.LASF435:
	.string	"vdma_enable_interrupt"
.LASF316:
	.string	"HAL_CLOCK_CG_PSEUDO_BEGIN"
.LASF434:
	.string	"vdma_disable_interrupt"
.LASF312:
	.string	"HAL_CLOCK_CG_CRYPTO"
.LASF5:
	.string	"short unsigned int"
.LASF193:
	.string	"pdma_limiter"
.LASF299:
	.string	"HAL_CLOCK_CG_FAST_DMA_0"
.LASF266:
	.string	"HAL_CLOCK_CG_FAST_DMA_1"
.LASF378:
	.string	"memcpy"
.LASF80:
	.string	"PMU_IRQn"
.LASF33:
	.string	"PDMA_INVALID_PARAMETER"
.LASF121:
	.string	"__reserved_00"
.LASF135:
	.string	"__reserved_01"
.LASF137:
	.string	"__reserved_02"
.LASF139:
	.string	"__reserved_03"
.LASF451:
	.string	"running_status"
.LASF301:
	.string	"HAL_CLOCK_CG_I3C1"
.LASF60:
	.string	"VDMA_ERROR"
.LASF159:
	.string	"CPU1_CLR_RX"
.LASF470:
	.string	"internal_dma_disable_clock"
.LASF287:
	.string	"HAL_CLOCK_CG_IBEX"
.LASF409:
	.string	"read_offset"
.LASF441:
	.string	"saved_mask"
.LASF190:
	.string	"pdma_intsta"
.LASF62:
	.string	"VDMA_INVALID_PARAMETER"
.LASF465:
	.string	"internal_pdma_restore_default_value"
.LASF70:
	.string	"vdma_callback_t"
.LASF195:
	.string	"dma_glb_cpu0_cfg"
.LASF440:
	.string	"vdma_deinit"
.LASF241:
	.string	"HAL_CLOCK_CG_PWM_DMA_1"
.LASF385:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF326:
	.string	"hal_nvic_isr_t"
.LASF58:
	.string	"VDMA_END_CHANNEL"
.LASF329:
	.string	"HAL_CLOCK_STATUS_ERROR"
.LASF331:
	.string	"hal_clock_status_t"
.LASF73:
	.string	"QDEC_IRQn"
.LASF109:
	.string	"RG_GLB_CPU2_INT_CLR"
.LASF130:
	.string	"DMA_GLB_CLK_CFG_T"
.LASF170:
	.string	"DMA_GLB_CLK_SET_T"
.LASF149:
	.string	"CPU0_SET_TX"
.LASF57:
	.string	"VDMA_UART2RX"
.LASF211:
	.string	"dma_status_ch"
.LASF447:
	.string	"internal_vdma_clock_control"
.LASF41:
	.string	"PDMA_TX_RINGBUFF"
.LASF439:
	.string	"vdma_start"
.LASF321:
	.string	"HAL_CLOCK_CG_PSEUDO_SLOW_BUS"
.LASF387:
	.string	"pdma_index"
.LASF103:
	.string	"RESERVE3"
.LASF91:
	.string	"hal_nvic_irq_t"
.LASF110:
	.string	"RESERVE5"
.LASF368:
	.string	"uart_dma_domain_channel_t"
.LASF94:
	.string	"RG_GLB_CPU0_INT_CFG"
.LASF17:
	.string	"PDMA_START_CHANNEL"
.LASF61:
	.string	"VDMA_ERROR_CHANNEL"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_pdma_internal.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
