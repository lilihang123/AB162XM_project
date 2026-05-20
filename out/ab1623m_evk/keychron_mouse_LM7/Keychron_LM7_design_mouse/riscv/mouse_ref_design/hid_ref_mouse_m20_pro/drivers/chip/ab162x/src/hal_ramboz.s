	.file	"hal_ramboz.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_ramboz.c"
	.section	.text.hw_ramboz_Isr_zephyr,"ax",@progbits
	.align	1
	.type	hw_ramboz_Isr_zephyr, @function
hw_ramboz_Isr_zephyr:
.LFB3:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_ramboz.c"
	.loc 1 50 1
	.cfi_startproc
	.loc 1 51 5
	.loc 1 51 51 is_stmt 0
	li	a5,1108353024
	lw	a5,72(a5)
	.loc 1 50 1
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 51 23
	sw	a5,0(sp)
	.loc 1 52 5 is_stmt 1
	.loc 1 52 21 is_stmt 0
	lw	a5,0(sp)
	andi	a5,a5,2
	.loc 1 52 8
	beq	a5,zero,.L2
	.loc 1 54 9 is_stmt 1
	.loc 1 54 28 is_stmt 0
	lw	a5,ramboz_callback
	.loc 1 54 12
	beq	a5,zero,.L3
	.loc 1 56 13 is_stmt 1
	li	a0,0
	jalr	a5
.LVL0:
.L3:
	.loc 1 59 9
	.loc 1 59 83 is_stmt 0
	li	a5,1108353024
	li	a3,2
	sb	a3,36(a5)
	.loc 1 60 9 is_stmt 1
	.loc 1 60 62 is_stmt 0
	li	a4,512
.L21:
	.loc 1 72 62
	sw	a4,36(a5)
	.loc 1 73 9 is_stmt 1
	.loc 1 73 86 is_stmt 0
	sb	a3,44(a5)
	.loc 1 74 9 is_stmt 1
	.loc 1 74 64 is_stmt 0
	sw	a4,44(a5)
.L1:
	.loc 1 85 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.L2:
	.cfi_restore_state
	.loc 1 64 10 is_stmt 1
	.loc 1 64 24 is_stmt 0
	lw	a5,0(sp)
	andi	a5,a5,1
	.loc 1 64 12
	beq	a5,zero,.L5
	.loc 1 66 9 is_stmt 1
	.loc 1 66 28 is_stmt 0
	lw	a5,ramboz_callback
	.loc 1 66 12
	beq	a5,zero,.L6
	.loc 1 68 13 is_stmt 1
	li	a0,1
	jalr	a5
.LVL1:
.L6:
	.loc 1 71 9
	.loc 1 71 83 is_stmt 0
	li	a5,1108353024
	li	a3,1
	sb	a3,36(a5)
	.loc 1 72 9 is_stmt 1
	.loc 1 72 62 is_stmt 0
	li	a4,256
	j	.L21
.L5:
	.loc 1 75 11 is_stmt 1
	.loc 1 75 25 is_stmt 0
	lw	a5,0(sp)
	andi	a5,a5,4
	.loc 1 75 13
	beq	a5,zero,.L1
	.loc 1 77 9 is_stmt 1
	.loc 1 77 28 is_stmt 0
	lw	a5,ramboz_callback
	.loc 1 77 12
	beq	a5,zero,.L7
	.loc 1 79 13 is_stmt 1
	li	a0,2
	jalr	a5
.LVL2:
.L7:
	.loc 1 82 9
	.loc 1 82 83 is_stmt 0
	li	a5,1108353024
	li	a4,4
	sb	a4,36(a5)
	.loc 1 83 9 is_stmt 1
	.loc 1 83 62 is_stmt 0
	li	a4,1024
	sw	a4,36(a5)
	.loc 1 85 1
	j	.L1
	.cfi_endproc
.LFE3:
	.size	hw_ramboz_Isr_zephyr, .-hw_ramboz_Isr_zephyr
	.section	.text.hal_ramboz_enable_irq,"ax",@progbits
	.align	1
	.globl	hal_ramboz_enable_irq
	.hidden	hal_ramboz_enable_irq
	.type	hal_ramboz_enable_irq, @function
hal_ramboz_enable_irq:
.LFB7:
	.loc 1 183 1 is_stmt 1
	.cfi_startproc
.LVL3:
	.loc 1 184 5
	.loc 1 184 8 is_stmt 0
	li	a4,2
	.loc 1 183 1
	mv	a5,a0
	.loc 1 184 8
	bne	a0,a4,.L23
	.loc 1 186 9 is_stmt 1
	.loc 1 186 59 is_stmt 0
	li	a5,1108353024
	lbu	a4,2(a5)
	.loc 1 186 71
	ori	a4,a4,4
	sb	a4,2(a5)
	.loc 1 187 9 is_stmt 1
	.loc 1 187 24 is_stmt 0
	lw	a4,32(a5)
	.loc 1 187 42
	ori	a4,a4,4
.LVL4:
.L28:
	sw	a4,32(a5)
	.loc 1 203 12
	li	a0,0
	ret
.LVL5:
.L23:
	.loc 1 189 10 is_stmt 1
	.loc 1 189 13 is_stmt 0
	bne	a0,zero,.L25
	.loc 1 191 9 is_stmt 1
	.loc 1 191 59 is_stmt 0
	li	a5,1108353024
	lbu	a4,2(a5)
	.loc 1 191 71
	ori	a4,a4,2
	sb	a4,2(a5)
	.loc 1 192 9 is_stmt 1
	.loc 1 192 24 is_stmt 0
	lw	a4,32(a5)
	.loc 1 192 42
	ori	a4,a4,2
	j	.L28
.L25:
	.loc 1 194 10 is_stmt 1
	.loc 1 194 13 is_stmt 0
	li	a4,1
	.loc 1 201 16
	li	a0,-1
.LVL6:
	.loc 1 194 13
	bne	a5,a4,.L22
	.loc 1 196 9 is_stmt 1
	.loc 1 196 59 is_stmt 0
	li	a5,1108353024
.LVL7:
	lbu	a4,2(a5)
	.loc 1 196 71
	ori	a4,a4,1
	sb	a4,2(a5)
	.loc 1 197 9 is_stmt 1
	.loc 1 197 24 is_stmt 0
	lw	a4,32(a5)
	.loc 1 197 42
	ori	a4,a4,1
	j	.L28
.LVL8:
.L22:
	.loc 1 204 1
	ret
	.cfi_endproc
.LFE7:
	.size	hal_ramboz_enable_irq, .-hal_ramboz_enable_irq
	.section	.text.hal_ramboz_disable_irq,"ax",@progbits
	.align	1
	.globl	hal_ramboz_disable_irq
	.hidden	hal_ramboz_disable_irq
	.type	hal_ramboz_disable_irq, @function
hal_ramboz_disable_irq:
.LFB8:
	.loc 1 207 1 is_stmt 1
	.cfi_startproc
.LVL9:
	.loc 1 208 5
	.loc 1 208 8 is_stmt 0
	li	a4,2
	.loc 1 207 1
	mv	a5,a0
	.loc 1 208 8
	bne	a0,a4,.L30
	.loc 1 210 9 is_stmt 1
	.loc 1 210 59 is_stmt 0
	li	a5,1108353024
	lbu	a4,2(a5)
	.loc 1 210 71
	andi	a4,a4,251
	sb	a4,2(a5)
	.loc 1 211 9 is_stmt 1
	.loc 1 211 24 is_stmt 0
	lw	a4,32(a5)
	.loc 1 211 42
	andi	a4,a4,-5
.LVL10:
.L35:
	sw	a4,32(a5)
	.loc 1 227 12
	li	a0,0
	ret
.LVL11:
.L30:
	.loc 1 213 10 is_stmt 1
	.loc 1 213 13 is_stmt 0
	bne	a0,zero,.L32
	.loc 1 215 9 is_stmt 1
	.loc 1 215 59 is_stmt 0
	li	a5,1108353024
	lbu	a4,2(a5)
	.loc 1 215 71
	andi	a4,a4,253
	sb	a4,2(a5)
	.loc 1 216 9 is_stmt 1
	.loc 1 216 24 is_stmt 0
	lw	a4,32(a5)
	.loc 1 216 42
	andi	a4,a4,-3
	j	.L35
.L32:
	.loc 1 218 10 is_stmt 1
	.loc 1 218 13 is_stmt 0
	li	a4,1
	.loc 1 225 16
	li	a0,-1
.LVL12:
	.loc 1 218 13
	bne	a5,a4,.L29
	.loc 1 220 9 is_stmt 1
	.loc 1 220 59 is_stmt 0
	li	a5,1108353024
.LVL13:
	lbu	a4,2(a5)
	.loc 1 220 71
	andi	a4,a4,254
	sb	a4,2(a5)
	.loc 1 221 9 is_stmt 1
	.loc 1 221 24 is_stmt 0
	lw	a4,32(a5)
	.loc 1 221 42
	andi	a4,a4,-2
	j	.L35
.LVL14:
.L29:
	.loc 1 228 1
	ret
	.cfi_endproc
.LFE8:
	.size	hal_ramboz_disable_irq, .-hal_ramboz_disable_irq
	.section	.text.hal_ramboz_init,"ax",@progbits
	.align	1
	.globl	hal_ramboz_init
	.hidden	hal_ramboz_init
	.type	hal_ramboz_init, @function
hal_ramboz_init:
.LFB6:
	.loc 1 142 1 is_stmt 1
	.cfi_startproc
.LVL15:
	.loc 1 143 5
	.loc 1 145 5
	.loc 1 142 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s1,0(sp)
	.cfi_offset 9, -12
	.loc 1 145 23
	lla	s1,ramboz_status
	.loc 1 145 8
	lw	a4,0(s1)
	.loc 1 142 1
	sw	ra,8(sp)
	sw	s0,4(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 145 8
	bne	a4,zero,.L38
.LBB6:
.LBB7:
	.loc 1 89 28
	lw	a3,0(a0)
	.loc 1 90 8
	li	s0,1
	mv	a5,a0
.LBE7:
.LBE6:
	.loc 1 150 5 is_stmt 1
.LVL16:
.LBB10:
.LBB8:
	.loc 1 89 5
	.loc 1 90 5
.LBE8:
.LBE10:
	.loc 1 152 16 is_stmt 0
	li	a0,-1
.LVL17:
.LBB11:
.LBB9:
	.loc 1 90 8
	bgtu	a3,s0,.L36
	.loc 1 94 5 is_stmt 1
	.loc 1 94 23 is_stmt 0
	lw	a4,4(a5)
.LVL18:
	.loc 1 95 5 is_stmt 1
	.loc 1 95 8 is_stmt 0
	bgtu	a4,s0,.L36
	.loc 1 99 5 is_stmt 1
	.loc 1 99 13 is_stmt 0
	lbu	t1,8(a5)
.LVL19:
	.loc 1 100 5 is_stmt 1
	.loc 1 100 14 is_stmt 0
	lhu	a1,10(a5)
.LVL20:
	.loc 1 101 5 is_stmt 1
	.loc 1 101 14 is_stmt 0
	lhu	a2,12(a5)
.LVL21:
	.loc 1 102 5 is_stmt 1
	.loc 1 102 14 is_stmt 0
	lhu	t0,14(a5)
.LVL22:
	.loc 1 104 5 is_stmt 1
	.loc 1 104 8 is_stmt 0
	li	a5,15
.LVL23:
	bgtu	t1,a5,.L36
	.loc 1 104 94 discriminator 3
	or	a5,a1,a2
	or	a5,t0,a5
	li	t2,4096
	bgeu	a5,t2,.L36
.LVL24:
.LBE9:
.LBE11:
	.loc 1 156 5 is_stmt 1
	.loc 1 156 73 is_stmt 0
	li	a5,1108353024
	andi	a3,a3,0xff
	sb	a3,0(a5)
	.loc 1 157 5 is_stmt 1
	.loc 1 157 73 is_stmt 0
	andi	a4,a4,0xff
	sb	a4,1(a5)
	.loc 1 158 5 is_stmt 1
	.loc 1 158 36 is_stmt 0
	sw	t1,4(a5)
	.loc 1 159 5 is_stmt 1
	.loc 1 159 41 is_stmt 0
	sw	a1,8(a5)
	.loc 1 160 5 is_stmt 1
	.loc 1 160 41 is_stmt 0
	sw	a2,12(a5)
	.loc 1 161 5 is_stmt 1
	.loc 1 161 39 is_stmt 0
	sw	t0,16(a5)
	.loc 1 163 5 is_stmt 1
	.loc 1 163 93 is_stmt 0
	sb	s0,22(a5)
	.loc 1 164 5 is_stmt 1
	.loc 1 164 95 is_stmt 0
	sb	s0,20(a5)
	.loc 1 166 5 is_stmt 1
	li	a0,0
	call	hal_ramboz_disable_irq
.LVL25:
	.loc 1 167 5
	li	a0,1
	call	hal_ramboz_disable_irq
.LVL26:
	.loc 1 168 5
	li	a0,2
	call	hal_ramboz_disable_irq
.LVL27:
	.loc 1 172 5
	lla	a1,hw_ramboz_Isr_zephyr
	li	a0,11
	call	hal_nvic_register_isr_handler
.LVL28:
	.loc 1 177 5
	li	a0,11
	call	hal_nvic_enable_irq
.LVL29:
	.loc 1 178 5
	.loc 1 179 12 is_stmt 0
	li	a0,0
	.loc 1 178 19
	sw	s0,0(s1)
	.loc 1 179 5 is_stmt 1
.L36:
	.loc 1 180 1 is_stmt 0
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
.LVL30:
.L38:
	.cfi_restore_state
	.loc 1 147 16
	li	a0,-2
.LVL31:
	j	.L36
	.cfi_endproc
.LFE6:
	.size	hal_ramboz_init, .-hal_ramboz_init
	.section	.text.hal_ramboz_enable,"ax",@progbits
	.align	1
	.globl	hal_ramboz_enable
	.hidden	hal_ramboz_enable
	.type	hal_ramboz_enable, @function
hal_ramboz_enable:
.LFB9:
	.loc 1 231 1 is_stmt 1
	.cfi_startproc
	.loc 1 232 5
	.loc 1 232 23 is_stmt 0
	lla	a5,ramboz_status
	.loc 1 232 8
	lw	a4,0(a5)
	li	a3,1
	.loc 1 234 16
	li	a0,-2
	.loc 1 232 8
	bne	a4,a3,.L44
	.loc 1 236 5 is_stmt 1
	.loc 1 236 36 is_stmt 0
	li	a3,1108353024
	sw	a4,48(a3)
	.loc 1 237 5 is_stmt 1
	.loc 1 237 19 is_stmt 0
	li	a4,2
	sw	a4,0(a5)
	.loc 1 238 5 is_stmt 1
	.loc 1 238 12 is_stmt 0
	li	a0,0
.L44:
	.loc 1 239 1
	ret
	.cfi_endproc
.LFE9:
	.size	hal_ramboz_enable, .-hal_ramboz_enable
	.section	.text.hal_ramboz_disable,"ax",@progbits
	.align	1
	.globl	hal_ramboz_disable
	.hidden	hal_ramboz_disable
	.type	hal_ramboz_disable, @function
hal_ramboz_disable:
.LFB10:
	.loc 1 242 1 is_stmt 1
	.cfi_startproc
	.loc 1 243 5
	.loc 1 243 23 is_stmt 0
	lla	a5,ramboz_status
	.loc 1 243 8
	lw	a3,0(a5)
	li	a4,2
	.loc 1 245 16
	li	a0,-2
	.loc 1 243 8
	bne	a3,a4,.L47
	.loc 1 247 5 is_stmt 1
	.loc 1 247 36 is_stmt 0
	li	a3,1108353024
	sw	zero,48(a3)
	.loc 1 248 5 is_stmt 1
	.loc 1 248 78 is_stmt 0
	li	a4,1
	sb	a4,70(a3)
	.loc 1 249 5 is_stmt 1
	.loc 1 249 19 is_stmt 0
	sw	a4,0(a5)
	.loc 1 250 5 is_stmt 1
	.loc 1 250 12 is_stmt 0
	li	a0,0
.L47:
	.loc 1 251 1
	ret
	.cfi_endproc
.LFE10:
	.size	hal_ramboz_disable, .-hal_ramboz_disable
	.section	.text.hal_ramboz_deinit,"ax",@progbits
	.align	1
	.globl	hal_ramboz_deinit
	.hidden	hal_ramboz_deinit
	.type	hal_ramboz_deinit, @function
hal_ramboz_deinit:
.LFB11:
	.loc 1 254 1 is_stmt 1
	.cfi_startproc
	.loc 1 255 5
	.loc 1 254 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 255 5
	call	hal_ramboz_disable
.LVL32:
	.loc 1 256 5 is_stmt 1
	.loc 1 258 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 256 19
	sw	zero,ramboz_status,a5
	.loc 1 257 5 is_stmt 1
	.loc 1 258 1 is_stmt 0
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	hal_ramboz_deinit, .-hal_ramboz_deinit
	.section	.text.hal_ramboz_register_callback,"ax",@progbits
	.align	1
	.globl	hal_ramboz_register_callback
	.hidden	hal_ramboz_register_callback
	.type	hal_ramboz_register_callback, @function
hal_ramboz_register_callback:
.LFB12:
	.loc 1 261 1 is_stmt 1
	.cfi_startproc
.LVL33:
	.loc 1 262 5
	.loc 1 262 8 is_stmt 0
	beq	a0,zero,.L54
	.loc 1 267 5 is_stmt 1
	.loc 1 267 21 is_stmt 0
	sw	a0,ramboz_callback,a5
	.loc 1 271 5 is_stmt 1
	.loc 1 271 12 is_stmt 0
	li	a0,0
.LVL34:
	ret
.LVL35:
.L54:
	.loc 1 265 16
	li	a0,-1
.LVL36:
	.loc 1 272 1
	ret
	.cfi_endproc
.LFE12:
	.size	hal_ramboz_register_callback, .-hal_ramboz_register_callback
	.section	.text.hal_ramboz_set_latch_clear,"ax",@progbits
	.align	1
	.globl	hal_ramboz_set_latch_clear
	.hidden	hal_ramboz_set_latch_clear
	.type	hal_ramboz_set_latch_clear, @function
hal_ramboz_set_latch_clear:
.LFB13:
	.loc 1 276 1 is_stmt 1
	.cfi_startproc
	.loc 1 279 9
	.loc 1 279 82 is_stmt 0
	li	a5,1108353024
	li	a4,1
	sb	a4,70(a5)
	.loc 1 280 9 is_stmt 1
	.loc 1 281 9
	.loc 1 284 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE13:
	.size	hal_ramboz_set_latch_clear, .-hal_ramboz_set_latch_clear
	.section	.text.hal_ramboz_get_data,"ax",@progbits
	.align	1
	.globl	hal_ramboz_get_data
	.hidden	hal_ramboz_get_data
	.type	hal_ramboz_get_data, @function
hal_ramboz_get_data:
.LFB14:
	.loc 1 287 1 is_stmt 1
	.cfi_startproc
.LVL37:
	.loc 1 293 5
	.loc 1 293 87 is_stmt 0
	li	a5,1108353024
	lbu	a5,68(a5)
	.loc 1 287 1
	addi	sp,sp,-4
	.cfi_def_cfa_offset 4
	.loc 1 293 87
	slli	a5,a5,24
	srai	a5,a5,24
	.loc 1 293 21
	sb	a5,3(sp)
	.loc 1 294 5 is_stmt 1
	.loc 1 299 5
	.loc 1 299 11 is_stmt 0
	lbu	a5,3(sp)
	slli	a5,a5,24
	srai	a5,a5,24
	sh	a5,0(a0)
	.loc 1 300 5 is_stmt 1
	.loc 1 301 1 is_stmt 0
	li	a0,0
.LVL38:
	addi	sp,sp,4
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE14:
	.size	hal_ramboz_get_data, .-hal_ramboz_get_data
	.section	.text.hw_ramboz_data_getting_type_set,"ax",@progbits
	.align	1
	.globl	hw_ramboz_data_getting_type_set
	.hidden	hw_ramboz_data_getting_type_set
	.type	hw_ramboz_data_getting_type_set, @function
hw_ramboz_data_getting_type_set:
.LFB15:
	.loc 1 304 1 is_stmt 1
	.cfi_startproc
.LVL39:
	.loc 1 305 5
	.loc 1 304 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 305 8
	bne	a0,zero,.L59
	.loc 1 307 9 is_stmt 1
	li	a0,2
.LVL40:
	call	hal_ramboz_enable_irq
.LVL41:
.L61:
	.loc 1 317 12 is_stmt 0
	li	a0,0
.L58:
	.loc 1 318 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL42:
.L59:
	.cfi_restore_state
	mv	a5,a0
	.loc 1 309 10 is_stmt 1
	.loc 1 309 13 is_stmt 0
	li	a4,1
	.loc 1 315 16
	li	a0,-1
.LVL43:
	.loc 1 309 13
	bne	a5,a4,.L58
	.loc 1 311 9 is_stmt 1
	li	a0,2
	call	hal_ramboz_disable_irq
.LVL44:
	j	.L61
	.cfi_endproc
.LFE15:
	.size	hw_ramboz_data_getting_type_set, .-hw_ramboz_data_getting_type_set
	.section	.text.hw_ramboz_data_sample_mode_set,"ax",@progbits
	.align	1
	.globl	hw_ramboz_data_sample_mode_set
	.hidden	hw_ramboz_data_sample_mode_set
	.type	hw_ramboz_data_sample_mode_set, @function
hw_ramboz_data_sample_mode_set:
.LFB16:
	.loc 1 321 1
	.cfi_startproc
.LVL45:
	.loc 1 322 5
	.loc 1 321 1 is_stmt 0
	mv	a5,a0
	.loc 1 322 8
	bne	a0,zero,.L65
	.loc 1 324 9 is_stmt 1
	.loc 1 324 99 is_stmt 0
	li	a5,1108353024
	li	a4,1
	sb	a4,20(a5)
.LVL46:
.L67:
	.loc 1 334 12
	li	a0,0
	ret
.LVL47:
.L65:
	.loc 1 326 10 is_stmt 1
	.loc 1 326 13 is_stmt 0
	li	a4,1
	.loc 1 332 16
	li	a0,-1
.LVL48:
	.loc 1 326 13
	bne	a5,a4,.L64
	.loc 1 328 9 is_stmt 1
	.loc 1 328 99 is_stmt 0
	li	a4,1108353024
	sb	a5,21(a4)
	j	.L67
.L64:
	.loc 1 335 1
	ret
	.cfi_endproc
.LFE16:
	.size	hw_ramboz_data_sample_mode_set, .-hw_ramboz_data_sample_mode_set
	.section	.text.hal_ramboz_enable_wakeup_event,"ax",@progbits
	.align	1
	.globl	hal_ramboz_enable_wakeup_event
	.hidden	hal_ramboz_enable_wakeup_event
	.type	hal_ramboz_enable_wakeup_event, @function
hal_ramboz_enable_wakeup_event:
.LFB17:
	.loc 1 338 1 is_stmt 1
	.cfi_startproc
.LVL49:
	.loc 1 339 5
	.loc 1 338 1 is_stmt 0
	mv	a5,a0
	.loc 1 339 8
	bne	a0,zero,.L70
	.loc 1 341 9 is_stmt 1
	.loc 1 341 59 is_stmt 0
	li	a5,1108353024
	lbu	a4,3(a5)
	.loc 1 341 72
	ori	a4,a4,2
	sb	a4,3(a5)
	.loc 1 342 9 is_stmt 1
	.loc 1 342 24 is_stmt 0
	lw	a4,40(a5)
	.loc 1 342 43
	ori	a4,a4,2
.LVL50:
.L74:
	sw	a4,40(a5)
	.loc 1 353 12
	li	a0,0
	ret
.LVL51:
.L70:
	.loc 1 344 10 is_stmt 1
	.loc 1 344 13 is_stmt 0
	li	a4,1
	.loc 1 351 16
	li	a0,-1
.LVL52:
	.loc 1 344 13
	bne	a5,a4,.L69
	.loc 1 346 9 is_stmt 1
	.loc 1 346 59 is_stmt 0
	li	a5,1108353024
.LVL53:
	lbu	a4,3(a5)
	.loc 1 346 72
	ori	a4,a4,1
	sb	a4,3(a5)
	.loc 1 347 9 is_stmt 1
	.loc 1 347 24 is_stmt 0
	lw	a4,40(a5)
	.loc 1 347 43
	ori	a4,a4,1
	j	.L74
.LVL54:
.L69:
	.loc 1 354 1
	ret
	.cfi_endproc
.LFE17:
	.size	hal_ramboz_enable_wakeup_event, .-hal_ramboz_enable_wakeup_event
	.section	.text.hal_ramboz_disable_wakeup_event,"ax",@progbits
	.align	1
	.globl	hal_ramboz_disable_wakeup_event
	.hidden	hal_ramboz_disable_wakeup_event
	.type	hal_ramboz_disable_wakeup_event, @function
hal_ramboz_disable_wakeup_event:
.LFB18:
	.loc 1 357 1 is_stmt 1
	.cfi_startproc
.LVL55:
	.loc 1 358 5
	.loc 1 357 1 is_stmt 0
	mv	a5,a0
	.loc 1 358 8
	bne	a0,zero,.L76
	.loc 1 360 9 is_stmt 1
	.loc 1 360 59 is_stmt 0
	li	a5,1108353024
	lbu	a4,3(a5)
	.loc 1 360 72
	andi	a4,a4,253
	sb	a4,3(a5)
	.loc 1 361 9 is_stmt 1
	.loc 1 361 24 is_stmt 0
	lw	a4,40(a5)
	.loc 1 361 43
	andi	a4,a4,-3
.LVL56:
.L80:
	sw	a4,40(a5)
	.loc 1 372 12
	li	a0,0
	ret
.LVL57:
.L76:
	.loc 1 363 10 is_stmt 1
	.loc 1 363 13 is_stmt 0
	li	a4,1
	.loc 1 370 16
	li	a0,-1
.LVL58:
	.loc 1 363 13
	bne	a5,a4,.L75
	.loc 1 365 9 is_stmt 1
	.loc 1 365 59 is_stmt 0
	li	a5,1108353024
.LVL59:
	lbu	a4,3(a5)
	.loc 1 365 72
	andi	a4,a4,254
	sb	a4,3(a5)
	.loc 1 366 9 is_stmt 1
	.loc 1 366 24 is_stmt 0
	lw	a4,40(a5)
	.loc 1 366 43
	andi	a4,a4,-2
	j	.L80
.LVL60:
.L75:
	.loc 1 373 1
	ret
	.cfi_endproc
.LFE18:
	.size	hal_ramboz_disable_wakeup_event, .-hal_ramboz_disable_wakeup_event
	.section	.sbss.ramboz_status,"aw",@nobits
	.align	2
	.type	ramboz_status, @object
	.size	ramboz_status, 4
ramboz_status:
	.zero	4
	.hidden	ramboz_callback
	.globl	ramboz_callback
	.section	.sbss.ramboz_callback,"aw",@nobits
	.align	2
	.type	ramboz_callback, @object
	.size	ramboz_callback, 4
ramboz_callback:
	.zero	4
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_ramboz.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_ramboz.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xb66
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x1f
	.4byte	.LASF163
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL17
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
	.uleb128 0x3
	.4byte	.LASF5
	.byte	0x2
	.byte	0x22
	.byte	0x15
	.4byte	0x45
	.uleb128 0x8
	.4byte	0x34
	.uleb128 0x5
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x3
	.4byte	.LASF6
	.byte	0x2
	.byte	0x25
	.byte	0x13
	.4byte	0x58
	.uleb128 0x5
	.byte	0x2
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x5
	.byte	0x8
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x83
	.uleb128 0x8
	.4byte	0x6d
	.uleb128 0xb
	.4byte	0x79
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF11
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0xa0
	.uleb128 0x8
	.4byte	0x8a
	.uleb128 0xb
	.4byte	0x96
	.uleb128 0x5
	.byte	0x2
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0xbd
	.uleb128 0x8
	.4byte	0xa7
	.uleb128 0xb
	.4byte	0xb3
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF15
	.uleb128 0x20
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x21
	.4byte	.LASF164
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x3
	.2byte	0x128
	.byte	0x11
	.4byte	0x151
	.uleb128 0x2
	.4byte	.LASF16
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF17
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0xb
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x11
	.uleb128 0x2
	.4byte	.LASF21
	.byte	0x12
	.uleb128 0x2
	.4byte	.LASF22
	.byte	0x13
	.uleb128 0x2
	.4byte	.LASF23
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF24
	.byte	0x15
	.uleb128 0x2
	.4byte	.LASF25
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF26
	.byte	0x17
	.uleb128 0x2
	.4byte	.LASF27
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF28
	.byte	0x19
	.uleb128 0x2
	.4byte	.LASF29
	.byte	0x1a
	.uleb128 0x2
	.4byte	.LASF30
	.byte	0x1b
	.uleb128 0x2
	.4byte	.LASF31
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF32
	.byte	0x1d
	.uleb128 0x2
	.4byte	.LASF33
	.byte	0x1e
	.uleb128 0x2
	.4byte	.LASF34
	.byte	0x1f
	.byte	0
	.uleb128 0x17
	.4byte	.LASF35
	.2byte	0x13c
	.byte	0x7
	.4byte	0xcb
	.uleb128 0x17
	.4byte	.LASF36
	.2byte	0x13e
	.byte	0x17
	.4byte	0x151
	.uleb128 0x14
	.4byte	0xb8
	.4byte	0x179
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0xb
	.4byte	0x169
	.uleb128 0x8
	.4byte	0x179
	.uleb128 0x14
	.4byte	0x7e
	.4byte	0x193
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xb
	.4byte	0x183
	.uleb128 0x8
	.4byte	0x193
	.uleb128 0x8
	.4byte	0x193
	.uleb128 0x14
	.4byte	0xb8
	.4byte	0x1b2
	.uleb128 0x15
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xb
	.4byte	0x1a2
	.uleb128 0x8
	.4byte	0x1b2
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.byte	0x28
	.byte	0x5
	.4byte	0x1fa
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x4
	.byte	0x2a
	.byte	0x18
	.4byte	0x79
	.byte	0
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.byte	0x2b
	.byte	0x18
	.4byte	0x79
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x4
	.byte	0x2c
	.byte	0x18
	.4byte	0x79
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x4
	.byte	0x2d
	.byte	0x18
	.4byte	0x79
	.byte	0x3
	.byte	0
	.uleb128 0x9
	.byte	0x26
	.4byte	0x217
	.uleb128 0x4
	.4byte	.LASF41
	.byte	0x2e
	.byte	0x7
	.4byte	0x1bc
	.uleb128 0x4
	.4byte	.LASF42
	.byte	0x2f
	.byte	0x17
	.4byte	0xb3
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.byte	0x39
	.byte	0x5
	.4byte	0x255
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x4
	.byte	0x3b
	.byte	0x18
	.4byte	0x79
	.byte	0
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x4
	.byte	0x3c
	.byte	0x18
	.4byte	0x79
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x4
	.byte	0x3d
	.byte	0x18
	.4byte	0x79
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x4
	.byte	0x3e
	.byte	0x1e
	.4byte	0x7e
	.byte	0x3
	.byte	0
	.uleb128 0x9
	.byte	0x37
	.4byte	0x272
	.uleb128 0x4
	.4byte	.LASF47
	.byte	0x3f
	.byte	0x7
	.4byte	0x217
	.uleb128 0x4
	.4byte	.LASF48
	.byte	0x40
	.byte	0x17
	.4byte	0xb3
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.byte	0x49
	.byte	0x5
	.4byte	0x2a3
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x4
	.byte	0x4b
	.byte	0x18
	.4byte	0x79
	.byte	0
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x4
	.byte	0x4c
	.byte	0x18
	.4byte	0x79
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x4
	.byte	0x4d
	.byte	0x1e
	.4byte	0x198
	.byte	0x2
	.byte	0
	.uleb128 0x9
	.byte	0x47
	.4byte	0x2c0
	.uleb128 0x4
	.4byte	.LASF51
	.byte	0x4e
	.byte	0x7
	.4byte	0x272
	.uleb128 0x4
	.4byte	.LASF52
	.byte	0x4f
	.byte	0x17
	.4byte	0xb3
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.byte	0x56
	.byte	0x5
	.4byte	0x2f1
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x4
	.byte	0x58
	.byte	0x18
	.4byte	0x79
	.byte	0
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x4
	.byte	0x59
	.byte	0x18
	.4byte	0x79
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x4
	.byte	0x5a
	.byte	0x1e
	.4byte	0x19d
	.byte	0x2
	.byte	0
	.uleb128 0x9
	.byte	0x54
	.4byte	0x30e
	.uleb128 0x4
	.4byte	.LASF55
	.byte	0x5b
	.byte	0x7
	.4byte	0x2c0
	.uleb128 0x4
	.4byte	.LASF56
	.byte	0x5c
	.byte	0x17
	.4byte	0xb3
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.byte	0x66
	.byte	0x5
	.4byte	0x34c
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x4
	.byte	0x68
	.byte	0x1e
	.4byte	0x7e
	.byte	0
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x4
	.byte	0x69
	.byte	0x1e
	.4byte	0x7e
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x4
	.byte	0x6a
	.byte	0x18
	.4byte	0x79
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x4
	.byte	0x6b
	.byte	0x1e
	.4byte	0x7e
	.byte	0x3
	.byte	0
	.uleb128 0x9
	.byte	0x64
	.4byte	0x369
	.uleb128 0x4
	.4byte	.LASF61
	.byte	0x6c
	.byte	0x7
	.4byte	0x30e
	.uleb128 0x4
	.4byte	.LASF62
	.byte	0x6d
	.byte	0x17
	.4byte	0xb3
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.byte	0x76
	.byte	0x5
	.4byte	0x3a7
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x4
	.byte	0x78
	.byte	0x1e
	.4byte	0x7e
	.byte	0
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x4
	.byte	0x79
	.byte	0x1e
	.4byte	0x7e
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x4
	.byte	0x7a
	.byte	0x18
	.4byte	0x79
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x4
	.byte	0x7b
	.byte	0x1e
	.4byte	0x7e
	.byte	0x3
	.byte	0
	.uleb128 0x9
	.byte	0x74
	.4byte	0x3c4
	.uleb128 0x4
	.4byte	.LASF65
	.byte	0x7c
	.byte	0x7
	.4byte	0x369
	.uleb128 0x4
	.4byte	.LASF66
	.byte	0x7d
	.byte	0x17
	.4byte	0xb3
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.byte	0x82
	.byte	0x5
	.4byte	0x3f5
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x4
	.byte	0x84
	.byte	0x1e
	.4byte	0x7e
	.byte	0
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x4
	.byte	0x85
	.byte	0x1e
	.4byte	0x7e
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x4
	.byte	0x86
	.byte	0x1f
	.4byte	0x9b
	.byte	0x2
	.byte	0
	.uleb128 0x9
	.byte	0x80
	.4byte	0x412
	.uleb128 0x4
	.4byte	.LASF70
	.byte	0x87
	.byte	0x7
	.4byte	0x3c4
	.uleb128 0x4
	.4byte	.LASF71
	.byte	0x88
	.byte	0x1d
	.4byte	0xb8
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.byte	0x4
	.byte	0x8d
	.byte	0x5
	.4byte	0x450
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x4
	.byte	0x8f
	.byte	0x1e
	.4byte	0x7e
	.byte	0
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x4
	.byte	0x90
	.byte	0x1e
	.4byte	0x7e
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x4
	.byte	0x91
	.byte	0x1e
	.4byte	0x7e
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x4
	.byte	0x92
	.byte	0x1e
	.4byte	0x7e
	.byte	0x3
	.byte	0
	.uleb128 0x9
	.byte	0x8b
	.4byte	0x46d
	.uleb128 0x4
	.4byte	.LASF76
	.byte	0x93
	.byte	0x7
	.4byte	0x412
	.uleb128 0x4
	.4byte	.LASF77
	.byte	0x94
	.byte	0x1d
	.4byte	0xb8
	.byte	0
	.uleb128 0x7
	.byte	0x5c
	.byte	0x4
	.byte	0x24
	.byte	0x9
	.4byte	0x57b
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x4
	.byte	0x30
	.byte	0x5
	.4byte	0x1fa
	.byte	0
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x4
	.byte	0x32
	.byte	0x15
	.4byte	0xb3
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x4
	.byte	0x33
	.byte	0x15
	.4byte	0xb3
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x4
	.byte	0x34
	.byte	0x15
	.4byte	0xb3
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x4
	.byte	0x35
	.byte	0x15
	.4byte	0xb3
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x4
	.byte	0x41
	.byte	0x5
	.4byte	0x255
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x4
	.byte	0x43
	.byte	0x1b
	.4byte	0x1b7
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x4
	.byte	0x45
	.byte	0x15
	.4byte	0xb3
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x4
	.byte	0x50
	.byte	0x5
	.4byte	0x2a3
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x4
	.byte	0x52
	.byte	0x15
	.4byte	0xb3
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x4
	.byte	0x5d
	.byte	0x5
	.4byte	0x2f1
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x4
	.byte	0x5f
	.byte	0x15
	.4byte	0xb3
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x4
	.byte	0x60
	.byte	0x1b
	.4byte	0x17e
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x4
	.byte	0x62
	.byte	0x15
	.4byte	0xb3
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x4
	.byte	0x6e
	.byte	0x5
	.4byte	0x34c
	.byte	0x44
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x4
	.byte	0x70
	.byte	0x1b
	.4byte	0xb8
	.byte	0x48
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x4
	.byte	0x72
	.byte	0x1b
	.4byte	0xb8
	.byte	0x4c
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x4
	.byte	0x7e
	.byte	0x5
	.4byte	0x3a7
	.byte	0x50
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x4
	.byte	0x89
	.byte	0x5
	.4byte	0x3f5
	.byte	0x54
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x4
	.byte	0x95
	.byte	0x5
	.4byte	0x450
	.byte	0x58
	.byte	0
	.uleb128 0x3
	.4byte	.LASF96
	.byte	0x4
	.byte	0x97
	.byte	0x3
	.4byte	0x46d
	.uleb128 0x8
	.4byte	0x57b
	.uleb128 0xa
	.byte	0x7
	.4byte	0x2d
	.byte	0x2f
	.byte	0x1
	.4byte	0x5a5
	.uleb128 0x2
	.4byte	.LASF97
	.byte	0
	.uleb128 0x2
	.4byte	.LASF98
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF99
	.byte	0x5
	.byte	0x32
	.byte	0x3
	.4byte	0x58c
	.uleb128 0xa
	.byte	0x7
	.4byte	0x2d
	.byte	0x35
	.byte	0x1
	.4byte	0x5ca
	.uleb128 0x2
	.4byte	.LASF100
	.byte	0
	.uleb128 0x2
	.4byte	.LASF101
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF102
	.byte	0x5
	.byte	0x38
	.byte	0x3
	.4byte	0x5b1
	.uleb128 0xa
	.byte	0x7
	.4byte	0x2d
	.byte	0x3b
	.byte	0x1
	.4byte	0x5ef
	.uleb128 0x2
	.4byte	.LASF103
	.byte	0
	.uleb128 0x2
	.4byte	.LASF104
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF105
	.byte	0x5
	.byte	0x3e
	.byte	0x3
	.4byte	0x5d6
	.uleb128 0xa
	.byte	0x7
	.4byte	0x2d
	.byte	0x41
	.byte	0x1
	.4byte	0x614
	.uleb128 0x2
	.4byte	.LASF106
	.byte	0
	.uleb128 0x2
	.4byte	.LASF107
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF108
	.byte	0x5
	.byte	0x44
	.byte	0x3
	.4byte	0x5fb
	.uleb128 0x7
	.byte	0x10
	.byte	0x5
	.byte	0x46
	.byte	0x9
	.4byte	0x678
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x5
	.byte	0x48
	.byte	0x1a
	.4byte	0x5a5
	.byte	0
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x5
	.byte	0x49
	.byte	0x15
	.4byte	0x5ca
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x5
	.byte	0x4a
	.byte	0xb
	.4byte	0x6d
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x5
	.byte	0x4b
	.byte	0xc
	.4byte	0x8a
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x5
	.byte	0x4c
	.byte	0xc
	.4byte	0x8a
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x5
	.byte	0x4d
	.byte	0xc
	.4byte	0x8a
	.byte	0xe
	.byte	0
	.uleb128 0x3
	.4byte	.LASF115
	.byte	0x5
	.byte	0x4e
	.byte	0x3
	.4byte	0x620
	.uleb128 0xa
	.byte	0x5
	.4byte	0xc4
	.byte	0x51
	.byte	0x1
	.4byte	0x6a3
	.uleb128 0x18
	.4byte	.LASF116
	.sleb128 -2
	.uleb128 0x18
	.4byte	.LASF117
	.sleb128 -1
	.uleb128 0x2
	.4byte	.LASF118
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF119
	.byte	0x5
	.byte	0x55
	.byte	0x3
	.4byte	0x684
	.uleb128 0xa
	.byte	0x7
	.4byte	0x2d
	.byte	0x57
	.byte	0xe
	.4byte	0x6ce
	.uleb128 0x2
	.4byte	.LASF120
	.byte	0
	.uleb128 0x2
	.4byte	.LASF121
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF122
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF123
	.byte	0x5
	.byte	0x5b
	.byte	0x3
	.4byte	0x6af
	.uleb128 0xa
	.byte	0x7
	.4byte	0x2d
	.byte	0x5e
	.byte	0x1
	.4byte	0x6f9
	.uleb128 0x2
	.4byte	.LASF124
	.byte	0
	.uleb128 0x2
	.4byte	.LASF125
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF126
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF127
	.byte	0x5
	.byte	0x62
	.byte	0x3
	.4byte	0x6da
	.uleb128 0xa
	.byte	0x7
	.4byte	0x2d
	.byte	0x65
	.byte	0x1
	.4byte	0x71e
	.uleb128 0x2
	.4byte	.LASF128
	.byte	0
	.uleb128 0x2
	.4byte	.LASF129
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF130
	.byte	0x5
	.byte	0x68
	.byte	0x3
	.4byte	0x705
	.uleb128 0x3
	.4byte	.LASF131
	.byte	0x5
	.byte	0x6b
	.byte	0x10
	.4byte	0x736
	.uleb128 0x10
	.4byte	0x73b
	.uleb128 0x19
	.4byte	0x746
	.uleb128 0x11
	.4byte	0x6d
	.byte	0
	.uleb128 0x5
	.byte	0x10
	.byte	0x4
	.4byte	.LASF132
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF133
	.uleb128 0x3
	.4byte	.LASF134
	.byte	0x6
	.byte	0x2e
	.byte	0x10
	.4byte	0x760
	.uleb128 0x10
	.4byte	0x765
	.uleb128 0x19
	.4byte	0x770
	.uleb128 0x11
	.4byte	0x15d
	.byte	0
	.uleb128 0x22
	.4byte	.LASF135
	.byte	0x1
	.byte	0x2c
	.byte	0x2c
	.4byte	0x785
	.4byte	0x42102000
	.uleb128 0x10
	.4byte	0x587
	.uleb128 0xb
	.4byte	0x780
	.uleb128 0x23
	.4byte	.LASF165
	.byte	0x1
	.byte	0x2e
	.byte	0x8
	.4byte	0x736
	.uleb128 0x5
	.byte	0x3
	.4byte	ramboz_callback
	.uleb128 0x1a
	.4byte	.LASF136
	.byte	0x2f
	.byte	0x1f
	.4byte	0x6ce
	.uleb128 0x5
	.byte	0x3
	.4byte	ramboz_status
	.uleb128 0x24
	.4byte	.LASF160
	.byte	0x1
	.2byte	0x112
	.byte	0xc
	.4byte	0x7ba
	.uleb128 0x5
	.byte	0x1
	.byte	0x2
	.4byte	.LASF137
	.uleb128 0x1b
	.4byte	.LASF138
	.byte	0x3c
	.4byte	0x7d1
	.uleb128 0x11
	.4byte	0x15d
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF139
	.byte	0x3b
	.4byte	0x7e6
	.uleb128 0x11
	.4byte	0x15d
	.uleb128 0x11
	.4byte	0x754
	.byte	0
	.uleb128 0xc
	.4byte	.LASF140
	.2byte	0x164
	.4byte	0x6a3
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x810
	.uleb128 0xd
	.4byte	.LASF142
	.2byte	0x164
	.byte	0x54
	.4byte	0x71e
	.4byte	.LLST16
	.byte	0
	.uleb128 0xc
	.4byte	.LASF141
	.2byte	0x151
	.4byte	0x6a3
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x83a
	.uleb128 0xd
	.4byte	.LASF142
	.2byte	0x151
	.byte	0x53
	.4byte	0x71e
	.4byte	.LLST15
	.byte	0
	.uleb128 0xc
	.4byte	.LASF143
	.2byte	0x140
	.4byte	0x6a3
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x864
	.uleb128 0xd
	.4byte	.LASF144
	.2byte	0x140
	.byte	0x4d
	.4byte	0x5ef
	.4byte	.LLST14
	.byte	0
	.uleb128 0xc
	.4byte	.LASF145
	.2byte	0x12f
	.4byte	0x6a3
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x8b0
	.uleb128 0xd
	.4byte	.LASF146
	.2byte	0x12f
	.byte	0x54
	.4byte	0x614
	.4byte	.LLST13
	.uleb128 0x12
	.4byte	.LVL41
	.4byte	0x9a2
	.4byte	0x8a0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.uleb128 0x1c
	.4byte	.LVL44
	.4byte	0x97a
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.byte	0
	.uleb128 0xc
	.4byte	.LASF147
	.2byte	0x11e
	.4byte	0x6a3
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x8ea
	.uleb128 0xd
	.4byte	.LASF148
	.2byte	0x11e
	.byte	0x32
	.4byte	0x8ea
	.4byte	.LLST12
	.uleb128 0x25
	.4byte	.LASF149
	.byte	0x1
	.2byte	0x125
	.byte	0x15
	.4byte	0x40
	.uleb128 0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0x10
	.4byte	0x4c
	.uleb128 0x26
	.4byte	.LASF166
	.byte	0x1
	.2byte	0x113
	.byte	0x15
	.4byte	0x6a3
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xc
	.4byte	.LASF150
	.2byte	0x104
	.4byte	0x6a3
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x930
	.uleb128 0xd
	.4byte	.LASF151
	.2byte	0x104
	.byte	0x48
	.4byte	0x72a
	.4byte	.LLST11
	.byte	0
	.uleb128 0x13
	.4byte	.LASF152
	.byte	0xfd
	.4byte	0x6a3
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x952
	.uleb128 0x27
	.4byte	.LVL32
	.4byte	0x952
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF153
	.byte	0xf1
	.4byte	0x6a3
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1d
	.4byte	.LASF154
	.byte	0xe6
	.4byte	0x6a3
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x13
	.4byte	.LASF155
	.byte	0xce
	.4byte	0x6a3
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9a2
	.uleb128 0x16
	.4byte	.LASF156
	.byte	0xce
	.byte	0x42
	.4byte	0x6f9
	.4byte	.LLST1
	.byte	0
	.uleb128 0x13
	.4byte	.LASF157
	.byte	0xb6
	.4byte	0x6a3
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9ca
	.uleb128 0x16
	.4byte	.LASF156
	.byte	0xb6
	.byte	0x41
	.4byte	0x6f9
	.4byte	.LLST0
	.byte	0
	.uleb128 0x13
	.4byte	.LASF158
	.byte	0x8d
	.4byte	0x6a3
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xab1
	.uleb128 0x16
	.4byte	.LASF159
	.byte	0x8d
	.byte	0x3a
	.4byte	0xab1
	.4byte	.LLST2
	.uleb128 0x28
	.4byte	0xabf
	.4byte	.LBB6
	.4byte	.LLRL3
	.byte	0x1
	.byte	0x96
	.byte	0x9
	.4byte	0xa4b
	.uleb128 0x29
	.4byte	0xad0
	.4byte	.LLST4
	.uleb128 0x2a
	.4byte	.LLRL3
	.uleb128 0xe
	.4byte	0xadc
	.4byte	.LLST5
	.uleb128 0xe
	.4byte	0xae7
	.4byte	.LLST6
	.uleb128 0xe
	.4byte	0xaf2
	.4byte	.LLST7
	.uleb128 0xe
	.4byte	0xafd
	.4byte	.LLST8
	.uleb128 0xe
	.4byte	0xb08
	.4byte	.LLST9
	.uleb128 0xe
	.4byte	0xb13
	.4byte	.LLST10
	.byte	0
	.byte	0
	.uleb128 0x12
	.4byte	.LVL25
	.4byte	0x97a
	.4byte	0xa5e
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x12
	.4byte	.LVL26
	.4byte	0x97a
	.4byte	0xa72
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x12
	.4byte	.LVL27
	.4byte	0x97a
	.4byte	0xa85
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.uleb128 0x12
	.4byte	.LVL28
	.4byte	0x7d1
	.4byte	0xaa1
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x3b
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	hw_ramboz_Isr_zephyr
	.byte	0
	.uleb128 0x1c
	.4byte	.LVL29
	.4byte	0x7c1
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x3b
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	0x678
	.uleb128 0x2b
	.4byte	.LASF167
	.byte	0x1
	.byte	0x70
	.byte	0xd
	.byte	0x1
	.uleb128 0x2c
	.4byte	.LASF168
	.byte	0x1
	.byte	0x57
	.byte	0x1c
	.4byte	0x6a3
	.byte	0x1
	.4byte	0xb1f
	.uleb128 0x2d
	.4byte	.LASF159
	.byte	0x1
	.byte	0x57
	.byte	0x4c
	.4byte	0xab1
	.uleb128 0xf
	.4byte	.LASF109
	.byte	0x59
	.byte	0x1c
	.4byte	0x5a5
	.uleb128 0xf
	.4byte	.LASF110
	.byte	0x5e
	.byte	0x17
	.4byte	0x5ca
	.uleb128 0xf
	.4byte	.LASF111
	.byte	0x63
	.byte	0xd
	.4byte	0x6d
	.uleb128 0xf
	.4byte	.LASF112
	.byte	0x64
	.byte	0xe
	.4byte	0x8a
	.uleb128 0xf
	.4byte	.LASF161
	.byte	0x65
	.byte	0xe
	.4byte	0x8a
	.uleb128 0xf
	.4byte	.LASF114
	.byte	0x66
	.byte	0xe
	.4byte	0x8a
	.byte	0
	.uleb128 0x2e
	.4byte	.LASF169
	.byte	0x1
	.byte	0x31
	.byte	0xd
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1a
	.4byte	.LASF162
	.byte	0x33
	.byte	0x17
	.4byte	0xb3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1e
	.4byte	.LVL0
	.4byte	0xb4e
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x1e
	.4byte	.LVL1
	.4byte	0xb5d
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x2f
	.4byte	.LVL2
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x32
	.byte	0
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.sleb128 21
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
	.uleb128 0xd
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
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 21
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
	.uleb128 0x17
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
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
	.uleb128 0x1c
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.uleb128 0x21
	.sleb128 21
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
	.uleb128 0x22
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
	.uleb128 0x23
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x26
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
	.uleb128 0x27
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x2e
	.byte	0
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
	.byte	0
	.byte	0
	.uleb128 0x2c
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
	.uleb128 0x2d
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
	.uleb128 0x2e
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
	.byte	0
	.byte	0
	.uleb128 0x2f
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
.LLST16:
	.byte	0x6
	.4byte	.LVL55
	.byte	0x4
	.uleb128 .LVL55-.LVL55
	.uleb128 .LVL56-.LVL55
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL56-.LVL55
	.uleb128 .LVL57-.LVL55
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
	.uleb128 .LVL57-.LVL55
	.uleb128 .LVL58-.LVL55
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL58-.LVL55
	.uleb128 .LVL59-.LVL55
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL59-.LVL55
	.uleb128 .LVL60-.LVL55
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
	.uleb128 .LVL60-.LVL55
	.uleb128 .LFE18-.LVL55
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL49
	.byte	0x4
	.uleb128 .LVL49-.LVL49
	.uleb128 .LVL50-.LVL49
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL50-.LVL49
	.uleb128 .LVL51-.LVL49
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
	.uleb128 .LVL51-.LVL49
	.uleb128 .LVL52-.LVL49
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL52-.LVL49
	.uleb128 .LVL53-.LVL49
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL53-.LVL49
	.uleb128 .LVL54-.LVL49
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
	.uleb128 .LVL54-.LVL49
	.uleb128 .LFE17-.LVL49
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL45
	.byte	0x4
	.uleb128 .LVL45-.LVL45
	.uleb128 .LVL46-.LVL45
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL46-.LVL45
	.uleb128 .LVL47-.LVL45
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
	.uleb128 .LVL47-.LVL45
	.uleb128 .LVL48-.LVL45
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL48-.LVL45
	.uleb128 .LFE16-.LVL45
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL39
	.byte	0x4
	.uleb128 .LVL39-.LVL39
	.uleb128 .LVL40-.LVL39
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL40-.LVL39
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
	.byte	0x4
	.uleb128 .LVL42-.LVL39
	.uleb128 .LVL43-.LVL39
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL43-.LVL39
	.uleb128 .LVL44-1-.LVL39
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL44-1-.LVL39
	.uleb128 .LFE15-.LVL39
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
	.4byte	.LVL37
	.byte	0x4
	.uleb128 .LVL37-.LVL37
	.uleb128 .LVL38-.LVL37
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL38-.LVL37
	.uleb128 .LFE14-.LVL37
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
.LLST11:
	.byte	0x6
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LVL35-.LVL33
	.uleb128 0x5
	.byte	0x3
	.4byte	ramboz_callback
	.byte	0x4
	.uleb128 .LVL35-.LVL33
	.uleb128 .LVL36-.LVL33
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL36-.LVL33
	.uleb128 .LFE12-.LVL33
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
	.4byte	.LVL9
	.byte	0x4
	.uleb128 .LVL9-.LVL9
	.uleb128 .LVL10-.LVL9
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL10-.LVL9
	.uleb128 .LVL11-.LVL9
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
	.uleb128 .LVL11-.LVL9
	.uleb128 .LVL12-.LVL9
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL12-.LVL9
	.uleb128 .LVL13-.LVL9
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL13-.LVL9
	.uleb128 .LVL14-.LVL9
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
	.uleb128 .LVL14-.LVL9
	.uleb128 .LFE8-.LVL9
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL4-.LVL3
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL4-.LVL3
	.uleb128 .LVL5-.LVL3
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
	.uleb128 .LVL5-.LVL3
	.uleb128 .LVL6-.LVL3
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL6-.LVL3
	.uleb128 .LVL7-.LVL3
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL7-.LVL3
	.uleb128 .LVL8-.LVL3
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
	.uleb128 .LVL8-.LVL3
	.uleb128 .LFE7-.LVL3
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL15
	.byte	0x4
	.uleb128 .LVL15-.LVL15
	.uleb128 .LVL17-.LVL15
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL17-.LVL15
	.uleb128 .LVL23-.LVL15
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL23-.LVL15
	.uleb128 .LVL30-.LVL15
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
	.uleb128 .LVL30-.LVL15
	.uleb128 .LVL31-.LVL15
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL31-.LVL15
	.uleb128 .LFE6-.LVL15
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
	.4byte	.LVL16
	.byte	0x4
	.uleb128 .LVL16-.LVL16
	.uleb128 .LVL17-.LVL16
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL17-.LVL16
	.uleb128 .LVL23-.LVL16
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL23-.LVL16
	.uleb128 .LVL24-.LVL16
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
	.byte	0x8
	.4byte	.LVL16
	.uleb128 .LVL24-.LVL16
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST6:
	.byte	0x8
	.4byte	.LVL18
	.uleb128 .LVL24-.LVL18
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST7:
	.byte	0x8
	.4byte	.LVL19
	.uleb128 .LVL24-.LVL19
	.uleb128 0x1
	.byte	0x56
	.byte	0
.LLST8:
	.byte	0x8
	.4byte	.LVL20
	.uleb128 .LVL24-.LVL20
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST9:
	.byte	0x8
	.4byte	.LVL21
	.uleb128 .LVL24-.LVL21
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST10:
	.byte	0x8
	.4byte	.LVL22
	.uleb128 .LVL24-.LVL22
	.uleb128 0x1
	.byte	0x55
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x84
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
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
	.4byte	.LBB6
	.byte	0x4
	.uleb128 .LBB6-.LBB6
	.uleb128 .LBE6-.LBB6
	.byte	0x4
	.uleb128 .LBB10-.LBB6
	.uleb128 .LBE10-.LBB6
	.byte	0x4
	.uleb128 .LBB11-.LBB6
	.uleb128 .LBE11-.LBB6
	.byte	0
.LLRL17:
	.byte	0x7
	.4byte	.LFB3
	.uleb128 .LFE3-.LFB3
	.byte	0x7
	.4byte	.LFB7
	.uleb128 .LFE7-.LFB7
	.byte	0x7
	.4byte	.LFB8
	.uleb128 .LFE8-.LFB8
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF97:
	.string	"HAL_RAMBOZ_DIRECTION_0"
.LASF107:
	.string	"HAL_RAMBOZ_READ_DATA_BY_NEXT_CYCLE"
.LASF81:
	.string	"SLOW_SAMPLE_PERIOD"
.LASF100:
	.string	"HAL_RAMBOZ_MODE_8CNT"
.LASF135:
	.string	"ramboz_register"
.LASF121:
	.string	"RAMBOZ_STATUS_INITIALIZED"
.LASF68:
	.string	"SLEEP_STATE"
.LASF163:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF109:
	.string	"direction"
.LASF44:
	.string	"SW_FORCE_SLOW_SAMPLE"
.LASF43:
	.string	"SW_FORCE_FAST_SAMPLE"
.LASF53:
	.string	"WKUP_NOTIFY_CLR"
.LASF63:
	.string	"DEBUG_MON"
.LASF2:
	.string	"long long unsigned int"
.LASF71:
	.string	"RAMBOZ_DEBUG_INFO_0"
.LASF77:
	.string	"RAMBOZ_DEBUG_INFO_1"
.LASF18:
	.string	"QDEC_IRQn"
.LASF150:
	.string	"hal_ramboz_register_callback"
.LASF108:
	.string	"hal_ramboz_data_getting_type_t"
.LASF141:
	.string	"hal_ramboz_enable_wakeup_event"
.LASF130:
	.string	"hal_ramboz_wakeup_event_type_t"
.LASF6:
	.string	"int16_t"
.LASF9:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF91:
	.string	"RAMBOZ_IRQ_STATE"
.LASF126:
	.string	"HAL_RAMBOZ_IRQ_DATA_READY"
.LASF61:
	.string	"RAMBOZ_Z_CNT_CELLS"
.LASF24:
	.string	"UART_DMA_IRQn"
.LASF85:
	.string	"RAMBOZ_IRQ_CLR_UNION"
.LASF20:
	.string	"UART_IRQn"
.LASF19:
	.string	"KEYSCAN_IRQn"
.LASF8:
	.string	"long int"
.LASF73:
	.string	"WKUP_CLR_LEVEL_32K"
.LASF12:
	.string	"uint16_t"
.LASF86:
	.string	"RAMBOZ_WKUP_MASK"
.LASF129:
	.string	"HAL_RAMBOZ_WAKEUP_EVENT_RAMBO_CNT"
.LASF39:
	.string	"IRQ_ENABLE"
.LASF48:
	.string	"SAMPLE_RATE_CONTROL"
.LASF74:
	.string	"FORCE_FAST_LEVEL_32K"
.LASF105:
	.string	"hal_ramboz_sample_mode_t"
.LASF168:
	.string	"hal_ramboz_init_para_check"
.LASF139:
	.string	"hal_nvic_register_isr_handler"
.LASF28:
	.string	"I3C0_IRQn"
.LASF56:
	.string	"RAMBOZ_WKUP_CLR"
.LASF52:
	.string	"RAMBOZ_IRQ_CLR"
.LASF62:
	.string	"RAMBOZ_Z_CNT"
.LASF67:
	.string	"LED_STATE"
.LASF70:
	.string	"RAMBOZ_DEBUG_INFO_0_CELLS"
.LASF155:
	.string	"hal_ramboz_disable_irq"
.LASF125:
	.string	"HAL_RAMBOZ_IRQ_RAMBO_CNT"
.LASF106:
	.string	"HAL_RAMBOZ_READ_DATA_BY_IRQ"
.LASF27:
	.string	"EINT_IRQn"
.LASF29:
	.string	"I3C0_DMA_IRQn"
.LASF114:
	.string	"fast_roll_period"
.LASF3:
	.string	"unsigned int"
.LASF111:
	.string	"filter_period"
.LASF149:
	.string	"fifo_data"
.LASF101:
	.string	"HAL_RAMBOZ_MODE_5CNT"
.LASF123:
	.string	"hal_ramboz_hw_status_t"
.LASF115:
	.string	"hal_ramboz_config_t"
.LASF142:
	.string	"wakeup_event_type"
.LASF95:
	.string	"RAMBOZ_DEBUG_INFO_1_UNION"
.LASF88:
	.string	"RAMBOZ_ENABLE"
.LASF79:
	.string	"FILTER_PERIOD"
.LASF148:
	.string	"data"
.LASF156:
	.string	"irq_type"
.LASF13:
	.string	"short unsigned int"
.LASF65:
	.string	"RAMBOZ_DEBUG_MON_CELLS"
.LASF117:
	.string	"HAL_RAMBOZ_INVALID_PARAMETER"
.LASF128:
	.string	"HAL_RAMBOZ_WAKEUP_EVENT_Z_CNT"
.LASF160:
	.string	"ramboz_available_data"
.LASF144:
	.string	"ramboz_sample_mode"
.LASF136:
	.string	"ramboz_status"
.LASF116:
	.string	"HAL_RAMBOZ_STATUS_ERROR"
.LASF72:
	.string	"IRQ_CLR_LEVEL_32K"
.LASF90:
	.string	"RAMBOZ_Z_CNT_UNION"
.LASF151:
	.string	"callback"
.LASF82:
	.string	"FAST_ROLL_PERIOD"
.LASF80:
	.string	"FAST_SAMPLE_PERIOD"
.LASF30:
	.string	"SPI_MST0_IRQn"
.LASF166:
	.string	"hal_ramboz_set_latch_clear"
.LASF55:
	.string	"RAMBOZ_WKUP_CLR_CELLS"
.LASF153:
	.string	"hal_ramboz_disable"
.LASF164:
	.string	"IRQn"
.LASF145:
	.string	"hw_ramboz_data_getting_type_set"
.LASF5:
	.string	"int8_t"
.LASF64:
	.string	"DEBUG_SEL"
.LASF31:
	.string	"IRQ_GEN_IRQn"
.LASF132:
	.string	"long double"
.LASF23:
	.string	"GPT_IRQn"
.LASF96:
	.string	"HW_RAMBZ_REGISTER_T"
.LASF42:
	.string	"RAMBOZ_CFG"
.LASF158:
	.string	"hal_ramboz_init"
.LASF16:
	.string	"SW_IRQn"
.LASF127:
	.string	"hal_ramboz_irq_type_t"
.LASF113:
	.string	"slow_sample_period"
.LASF54:
	.string	"WKUP_EVENT_CLR"
.LASF32:
	.string	"USB_IRQn"
.LASF94:
	.string	"RAMBOZ_DEBUG_INFO_0_UNION"
.LASF165:
	.string	"ramboz_callback"
.LASF21:
	.string	"SPI_MST1_IRQn"
.LASF37:
	.string	"RAMBOZ_DIRECTION"
.LASF112:
	.string	"fast_sample_period"
.LASF152:
	.string	"hal_ramboz_deinit"
.LASF89:
	.string	"RAMBOZ_CNT"
.LASF167:
	.string	"ramboz_reg_adr_check"
.LASF122:
	.string	"RAMBOZ_STATUS_RUNNING"
.LASF131:
	.string	"hal_ramboz_callback_t"
.LASF137:
	.string	"_Bool"
.LASF11:
	.string	"unsigned char"
.LASF93:
	.string	"RAMBOZ_DEBUG_MON_UNION"
.LASF134:
	.string	"hal_nvic_isr_t"
.LASF159:
	.string	"ramboz_cfg"
.LASF7:
	.string	"short int"
.LASF25:
	.string	"PMU_IRQn"
.LASF41:
	.string	"RAMBOZ_CFG_CELLS"
.LASF26:
	.string	"MCU_DMA_IRQn"
.LASF51:
	.string	"RAMBOZ_IRQ_CLR_CELLS"
.LASF99:
	.string	"hal_ramboz_direction_t"
.LASF140:
	.string	"hal_ramboz_disable_wakeup_event"
.LASF138:
	.string	"hal_nvic_enable_irq"
.LASF84:
	.string	"RAMBOZ_IRQ_MASK"
.LASF58:
	.string	"RESERVE1"
.LASF59:
	.string	"Z_CNT_LATCH_N_CLR"
.LASF87:
	.string	"RAMBOZ_WKUP_CLR_UNION"
.LASF35:
	.string	"IRQn_Type"
.LASF162:
	.string	"irq_status"
.LASF147:
	.string	"hal_ramboz_get_data"
.LASF14:
	.string	"uint32_t"
.LASF102:
	.string	"hal_ramboz_mode_t"
.LASF15:
	.string	"long unsigned int"
.LASF133:
	.string	"char"
.LASF110:
	.string	"mode"
.LASF120:
	.string	"RAMBOZ_STATUS_UNINITIALIZED"
.LASF103:
	.string	"HAL_RAMBOZ_FAST_SAMPLE"
.LASF143:
	.string	"hw_ramboz_data_sample_mode_set"
.LASF75:
	.string	"FORCE_SLOW_LEVEL_32K"
.LASF46:
	.string	"RESERVE"
.LASF154:
	.string	"hal_ramboz_enable"
.LASF60:
	.string	"RESERVE2"
.LASF33:
	.string	"BT_IRQn"
.LASF76:
	.string	"RAMBOZ_DEBUG_INFO_1_CELLS"
.LASF92:
	.string	"RAMBOZ_WKUP_STATE"
.LASF47:
	.string	"SAMPLE_RATE_CONTROL_CELLS"
.LASF98:
	.string	"HAL_RAMBOZ_DIRECTION_1"
.LASF45:
	.string	"SAMPLE_RATE_CHANGE"
.LASF69:
	.string	"LEDOFF_PERIOD_MUX"
.LASF57:
	.string	"Z_CNT"
.LASF17:
	.string	"LED_IRQn"
.LASF146:
	.string	"ramboz_data_getting_type"
.LASF50:
	.string	"IRQ_EVENT_CLR"
.LASF10:
	.string	"uint8_t"
.LASF83:
	.string	"SAMPLE_RATE_CONTROL_UNION"
.LASF161:
	.string	"low_sample_period"
.LASF104:
	.string	"HAL_RAMBOZ_SLOW_SAMPLE"
.LASF78:
	.string	"RAMBOZ_CFG_UNION"
.LASF40:
	.string	"WKUP_ENABLE"
.LASF36:
	.string	"hal_nvic_irq_t"
.LASF38:
	.string	"RAMBOZ_5CNT_MODE"
.LASF119:
	.string	"hal_ramboz_status_t"
.LASF169:
	.string	"hw_ramboz_Isr_zephyr"
.LASF124:
	.string	"HAL_RAMBOZ_IRQ_Z_CNT"
.LASF49:
	.string	"IRQ_NOTIFY_CLR"
.LASF22:
	.string	"RTC_IRQn"
.LASF157:
	.string	"hal_ramboz_enable_irq"
.LASF66:
	.string	"RAMBOZ_DEBUG_MON"
.LASF118:
	.string	"HAL_RAMBOZ_STATUS_OK"
.LASF34:
	.string	"IRQ_NUMBER_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_ramboz.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
