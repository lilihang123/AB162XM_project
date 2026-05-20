	.file	"hal_clock.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_clock.c"
	.section	.text.clock_physical_cg_ctrl,"ax",@progbits
	.align	1
	.globl	clock_physical_cg_ctrl
	.hidden	clock_physical_cg_ctrl
	.type	clock_physical_cg_ctrl, @function
clock_physical_cg_ctrl:
.LFB3:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_clock.c"
	.loc 1 82 1
	.cfi_startproc
.LVL0:
	.loc 1 83 5
	.loc 1 84 5
	.loc 1 87 7 is_stmt 0
	li	a5,17
	.loc 1 82 1
	mv	a2,a0
	.loc 1 84 14
	andi	t1,a0,31
.LVL1:
	.loc 1 87 5 is_stmt 1
	.loc 1 87 7 is_stmt 0
	beq	a0,a5,.L8
	.loc 1 92 10 is_stmt 1
	.loc 1 92 50 is_stmt 0
	addi	a5,a0,-32
	.loc 1 92 12
	li	a4,30
	bleu	a5,a4,.L9
	.loc 1 97 10 is_stmt 1
	.loc 1 97 51 is_stmt 0
	addi	a5,a0,-64
	.loc 1 97 12
	li	a4,15
	bleu	a5,a4,.L10
	.loc 1 102 10 is_stmt 1
	.loc 1 102 48 is_stmt 0
	addi	a5,a0,-96
	.loc 1 102 12
	li	a3,26
	bleu	a5,a3,.L11
	.loc 1 107 10 is_stmt 1
	.loc 1 107 50 is_stmt 0
	addi	a5,a0,-144
	.loc 1 107 12
	bleu	a5,a4,.L12
	.loc 1 112 10 is_stmt 1
	.loc 1 112 52 is_stmt 0
	addi	a5,a0,-160
	.loc 1 112 12
	li	a4,24
	bleu	a5,a4,.L13
	.loc 1 117 10 is_stmt 1
	.loc 1 117 12 is_stmt 0
	li	a5,208
	.loc 1 123 16
	li	a0,-2
.LVL2:
	.loc 1 117 12
	bne	a2,a5,.L1
	.loc 1 120 18
	li	a4,1110245376
	.loc 1 119 18
	li	a5,1110245376
	.loc 1 118 18
	li	a3,1110245376
	.loc 1 120 18
	addi	a4,a4,896
	.loc 1 119 18
	addi	a5,a5,880
	.loc 1 118 18
	addi	a3,a3,40
.L2:
.LVL3:
	.loc 1 126 5 is_stmt 1
	.loc 1 126 7 is_stmt 0
	bne	a1,zero,.L4
	.loc 1 127 9 is_stmt 1
	.loc 1 127 18 is_stmt 0
	lw	a0,0(a3)
	.loc 1 127 28
	srl	a0,a0,t1
	.loc 1 127 40
	andi	a0,a0,1
	ret
.LVL4:
.L8:
	.loc 1 90 18
	li	a4,1107562496
	.loc 1 89 18
	li	a5,1107562496
	.loc 1 90 18
	addi	a4,a4,-1248
	.loc 1 89 18
	addi	a5,a5,-1264
	.loc 1 88 18
	li	a3,1107558400
	j	.L2
.L9:
	.loc 1 95 18
	li	a4,1107562496
	.loc 1 94 18
	li	a5,1107562496
	.loc 1 93 18
	li	a3,1107558400
	.loc 1 95 18
	addi	a4,a4,-1200
	.loc 1 94 18
	addi	a5,a5,-1216
	.loc 1 93 18
	addi	a3,a3,4
	j	.L2
.L10:
	.loc 1 100 18
	li	a4,1107562496
	.loc 1 99 18
	li	a5,1107562496
	.loc 1 98 18
	li	a3,1107558400
	.loc 1 100 18
	addi	a4,a4,-1196
	.loc 1 99 18
	addi	a5,a5,-1212
	.loc 1 98 18
	addi	a3,a3,8
	j	.L2
.L11:
	.loc 1 105 18
	li	a4,1107562496
	.loc 1 104 18
	li	a5,1107562496
	.loc 1 103 18
	li	a3,1107558400
	.loc 1 105 18
	addi	a4,a4,-1152
	.loc 1 104 18
	addi	a5,a5,-1168
	.loc 1 103 18
	addi	a3,a3,12
	j	.L2
.L12:
	.loc 1 110 18
	li	a4,1107562496
	.loc 1 109 18
	li	a5,1107562496
	.loc 1 108 18
	li	a3,1107558400
	.loc 1 110 18
	addi	a4,a4,-1104
	.loc 1 109 18
	addi	a5,a5,-1120
	.loc 1 108 18
	addi	a3,a3,16
	j	.L2
.L13:
	.loc 1 115 18
	li	a4,1110245376
	.loc 1 114 18
	li	a5,1110245376
	.loc 1 113 18
	li	a3,1110245376
	.loc 1 115 18
	addi	a4,a4,800
	.loc 1 114 18
	addi	a5,a5,784
	.loc 1 113 18
	addi	a3,a3,32
	j	.L2
.LVL5:
.L4:
	.loc 1 129 10 is_stmt 1
	.loc 1 129 12 is_stmt 0
	li	a3,1
.LVL6:
	bne	a1,a3,.L5
	.loc 1 130 9 is_stmt 1
	.loc 1 130 24 is_stmt 0
	sll	a1,a1,t1
.LVL7:
	.loc 1 130 19
	sw	a1,0(a4)
.LVL8:
.L6:
	.loc 1 147 12
	li	a0,0
	ret
.LVL9:
.L5:
	.loc 1 132 10 is_stmt 1
	.loc 1 132 12 is_stmt 0
	li	a4,2
.LVL10:
	.loc 1 123 16
	li	a0,-2
	.loc 1 132 12
	bne	a1,a4,.L1
.LBB2:
	.loc 1 133 17
	li	a4,0
	.loc 1 136 48
	lla	a1,clk_always_on_cg_tbl
.LVL11:
	.loc 1 140 43
	li	a0,214
.L7:
.LVL12:
	.loc 1 135 9 is_stmt 1
	.loc 1 136 13
	.loc 1 136 48 is_stmt 0
	slli	a3,a4,2
	add	a3,a1,a3
	.loc 1 136 15
	lw	a3,0(a3)
	beq	a3,a2,.L16
	.loc 1 140 43 is_stmt 1
	addi	a4,a4,1
.LVL13:
	andi	a4,a4,0xff
.LVL14:
	.loc 1 140 35 is_stmt 0
	slli	a3,a4,2
	add	a3,a1,a3
	.loc 1 140 43
	lw	a3,0(a3)
	bne	a3,a0,.L7
	.loc 1 142 9 is_stmt 1
	.loc 1 142 24 is_stmt 0
	li	a4,1
.LVL15:
	sll	a4,a4,t1
	.loc 1 142 19
	sw	a4,0(a5)
.LBE2:
	j	.L6
.LVL16:
.L16:
.LBB3:
	.loc 1 137 24
	li	a0,-1
.LVL17:
.L1:
.LBE3:
	.loc 1 148 1
	ret
	.cfi_endproc
.LFE3:
	.size	clock_physical_cg_ctrl, .-clock_physical_cg_ctrl
	.section	.text.hal_clock_enable,"ax",@progbits
	.align	1
	.globl	hal_clock_enable
	.hidden	hal_clock_enable
	.type	hal_clock_enable, @function
hal_clock_enable:
.LFB4:
	.loc 1 151 1 is_stmt 1
	.cfi_startproc
.LVL18:
	.loc 1 155 5
	.loc 1 155 48 is_stmt 0
	addi	a4,a0,-209
	.loc 1 155 7
	li	a3,4
	bgtu	a4,a3,.L19
	.loc 1 156 9 is_stmt 1
	.loc 1 156 59 is_stmt 0
	slli	a4,a4,2
	lla	a5,pseudo_cg_tbl
	add	a5,a5,a4
	sw	zero,0(a5)
.L20:
	.loc 1 169 1
	li	a0,0
.LVL19:
	ret
.LVL20:
.L19:
	.loc 1 158 10 is_stmt 1
	.loc 1 158 12 is_stmt 0
	slli	a4,a0,16
	bge	a4,zero,.L21
	.loc 1 159 9 is_stmt 1
	.loc 1 159 54 is_stmt 0
	li	a4,1107562496
	.loc 1 159 65
	andi	a5,a0,31
	.loc 1 159 54
	addi	a4,a4,-1200
	sw	a5,0(a4)
	j	.L20
.L21:
.LBB4:
	.loc 1 162 9 is_stmt 1
	.loc 1 162 37 is_stmt 0
	li	a1,1
	tail	clock_physical_cg_ctrl
.LVL21:
.LBE4:
	.cfi_endproc
.LFE4:
	.size	hal_clock_enable, .-hal_clock_enable
	.section	.text.hal_clock_disable,"ax",@progbits
	.align	1
	.globl	hal_clock_disable
	.hidden	hal_clock_disable
	.type	hal_clock_disable, @function
hal_clock_disable:
.LFB5:
	.loc 1 172 1 is_stmt 1
	.cfi_startproc
.LVL22:
	.loc 1 176 5
	.loc 1 176 48 is_stmt 0
	addi	a4,a0,-209
	.loc 1 176 7
	li	a3,4
	bgtu	a4,a3,.L24
	.loc 1 177 9 is_stmt 1
	.loc 1 177 59 is_stmt 0
	slli	a4,a4,2
	lla	a5,pseudo_cg_tbl
	add	a5,a5,a4
	li	a4,1
	sw	a4,0(a5)
.L25:
	.loc 1 190 1
	li	a0,0
.LVL23:
	ret
.LVL24:
.L24:
	.loc 1 179 10 is_stmt 1
	.loc 1 179 12 is_stmt 0
	slli	a4,a0,16
	bge	a4,zero,.L26
	.loc 1 180 9 is_stmt 1
	.loc 1 180 54 is_stmt 0
	li	a4,1107562496
	.loc 1 180 65
	andi	a5,a0,31
	.loc 1 180 54
	addi	a4,a4,-1216
	sw	a5,0(a4)
	j	.L25
.L26:
.LBB5:
	.loc 1 183 9 is_stmt 1
	.loc 1 183 37 is_stmt 0
	li	a1,2
	tail	clock_physical_cg_ctrl
.LVL25:
.LBE5:
	.cfi_endproc
.LFE5:
	.size	hal_clock_disable, .-hal_clock_disable
	.section	.text.hal_clock_is_enabled,"ax",@progbits
	.align	1
	.globl	hal_clock_is_enabled
	.hidden	hal_clock_is_enabled
	.type	hal_clock_is_enabled, @function
hal_clock_is_enabled:
.LFB6:
	.loc 1 193 1 is_stmt 1
	.cfi_startproc
.LVL26:
	.loc 1 197 5
	.loc 1 197 48 is_stmt 0
	addi	a5,a0,-209
	.loc 1 197 7
	li	a4,4
	bgtu	a5,a4,.L29
	.loc 1 198 9 is_stmt 1
	.loc 1 198 29 is_stmt 0
	lla	a4,pseudo_cg_tbl
	slli	a5,a5,2
	add	a5,a4,a5
	lw	a0,0(a5)
.LVL27:
	snez	a0,a0
	.loc 1 207 1
	ret
.LVL28:
.L29:
	.loc 1 201 9 is_stmt 1
	.loc 1 193 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 201 12
	li	a1,0
	.loc 1 193 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 201 12
	call	clock_physical_cg_ctrl
.LVL29:
	.loc 1 207 1
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 201 11 discriminator 1
	seqz	a0,a0
	.loc 1 207 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE6:
	.size	hal_clock_is_enabled, .-hal_clock_is_enabled
	.section	.text.hal_clock_mux_cur_sel,"ax",@progbits
	.align	1
	.globl	hal_clock_mux_cur_sel
	.hidden	hal_clock_mux_cur_sel
	.type	hal_clock_mux_cur_sel, @function
hal_clock_mux_cur_sel:
.LFB7:
	.loc 1 210 1 is_stmt 1
	.cfi_startproc
.LVL30:
	.loc 1 211 5
	.loc 1 214 5
	beq	a0,zero,.L35
	li	a5,1
	beq	a0,a5,.L36
	li	a0,0
.LVL31:
	ret
.LVL32:
.L35:
	.loc 1 216 13
	.loc 1 216 21 is_stmt 0
	li	a5,1108373504
	lbu	a0,22(a5)
.LVL33:
.L38:
	.loc 1 219 21
	andi	a0,a0,0xff
.LVL34:
	.loc 1 224 5 is_stmt 1
	.loc 1 225 1 is_stmt 0
	ret
.LVL35:
.L36:
	.loc 1 219 13 is_stmt 1
	.loc 1 219 21 is_stmt 0
	li	a5,1107492864
	lbu	a0,35(a5)
.LVL36:
	j	.L38
	.cfi_endproc
.LFE7:
	.size	hal_clock_mux_cur_sel, .-hal_clock_mux_cur_sel
	.section	.text.hal_clock_mux_sel,"ax",@progbits
	.align	1
	.globl	hal_clock_mux_sel
	.hidden	hal_clock_mux_sel
	.type	hal_clock_mux_sel, @function
hal_clock_mux_sel:
.LFB8:
	.loc 1 228 1 is_stmt 1
	.cfi_startproc
.LVL37:
	.loc 1 230 5
	li	a5,1
	bne	a0,a5,.L43
	.loc 1 232 13
	.loc 1 232 57 is_stmt 0
	li	a5,1107492864
	sb	a0,71(a5)
	.loc 1 233 13 is_stmt 1
	.loc 1 233 57 is_stmt 0
	andi	a1,a1,0xff
.LVL38:
	li	a5,1107492864
	sb	a1,35(a5)
	.loc 1 234 13 is_stmt 1
	.loc 1 234 57 is_stmt 0
	li	a5,1107492864
	addi	a5,a5,55
	sb	a0,0(a5)
	.loc 1 235 13 is_stmt 1
.L41:
	.loc 1 235 19 discriminator 1
	lbu	a4,0(a5)
	bne	a4,zero,.L41
	.loc 1 236 19 is_stmt 0 discriminator 1
	li	a5,1107492864
	addi	a5,a5,611
.L42:
	.loc 1 236 19 is_stmt 1 discriminator 1
	lbu	a4,0(a5)
	bne	a4,zero,.L42
	.loc 1 237 13
	.loc 1 237 57 is_stmt 0
	li	a5,1107492864
	sb	zero,71(a5)
	.loc 1 238 13 is_stmt 1
	.loc 1 238 20 is_stmt 0
	li	a0,0
.LVL39:
	ret
.LVL40:
.L43:
	.loc 1 240 20
	li	a0,-2
.LVL41:
	.loc 1 244 1
	ret
	.cfi_endproc
.LFE8:
	.size	hal_clock_mux_sel, .-hal_clock_mux_sel
	.hidden	clk_always_on_cg_tbl
	.globl	clk_always_on_cg_tbl
	.section	.rodata.clk_always_on_cg_tbl,"a"
	.align	2
	.type	clk_always_on_cg_tbl, @object
	.size	clk_always_on_cg_tbl, 28
clk_always_on_cg_tbl:
	.word	144
	.word	118
	.word	55
	.word	113
	.word	49
	.word	51
	.word	214
	.hidden	pseudo_cg_tbl
	.globl	pseudo_cg_tbl
	.section	.bss.pseudo_cg_tbl,"aw",@nobits
	.align	2
	.type	pseudo_cg_tbl, @object
	.size	pseudo_cg_tbl, 20
pseudo_cg_tbl:
	.zero	20
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_clock.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_clock_internal.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x685
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x13
	.4byte	.LASF176
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL14
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x14
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x15
	.4byte	0x92
	.uleb128 0xa
	.4byte	0x2d
	.2byte	0x74b
	.4byte	0x2b4
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x38
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x39
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x3a
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x3b
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x3c
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x3d
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x3e
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x41
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x42
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x4e
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0x4f
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x60
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x61
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x62
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x64
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x65
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x66
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x6a
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x6c
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x6d
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x6e
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x6f
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x71
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x72
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x73
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x74
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x75
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x76
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x77
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x79
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x7a
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x90
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x91
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x92
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x98
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x9d
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x9e
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x9f
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0xa0
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0xa1
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0xa4
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0xa5
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0xa6
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0xa9
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0xaa
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0xab
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0xac
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0xad
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0xae
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0xaf
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0xb2
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0xb3
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0xb4
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0xb7
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0xb8
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0xd0
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0xd1
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0xd1
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0xd2
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0xd3
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0xd4
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0xd5
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0xd5
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0xd6
	.uleb128 0x16
	.4byte	.LASF101
	.2byte	0x8000
	.byte	0
	.uleb128 0xb
	.4byte	.LASF102
	.2byte	0x7d9
	.4byte	0xa3
	.uleb128 0xc
	.4byte	0x2b4
	.uleb128 0xa
	.4byte	0x2d
	.2byte	0x80b
	.4byte	0x3a2
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x20
	.byte	0
	.uleb128 0xb
	.4byte	.LASF138
	.2byte	0x835
	.4byte	0x2c4
	.uleb128 0x6
	.byte	0x5
	.4byte	0x65
	.byte	0x4
	.byte	0x5e
	.4byte	0x3d2
	.uleb128 0x8
	.4byte	.LASF139
	.sleb128 -3
	.uleb128 0x8
	.4byte	.LASF140
	.sleb128 -2
	.uleb128 0x8
	.4byte	.LASF141
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF143
	.byte	0x4
	.byte	0x63
	.byte	0x3
	.4byte	0x3ad
	.uleb128 0x6
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x37
	.4byte	0x403
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF148
	.byte	0x5
	.byte	0x3d
	.byte	0x3
	.4byte	0x3de
	.uleb128 0x6
	.byte	0x7
	.4byte	0x2d
	.byte	0x1
	.byte	0x2f
	.4byte	0x43a
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x2
	.byte	0
	.uleb128 0x4
	.4byte	.LASF154
	.byte	0x1
	.byte	0x36
	.byte	0x3
	.4byte	0x40f
	.uleb128 0x6
	.byte	0x7
	.4byte	0x2d
	.byte	0x1
	.byte	0x38
	.4byte	0x45f
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF157
	.byte	0x1
	.byte	0x3b
	.byte	0x3
	.4byte	0x446
	.uleb128 0xd
	.4byte	0x45f
	.4byte	0x47b
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0xf
	.4byte	.LASF158
	.byte	0x3d
	.byte	0xc
	.4byte	0x46b
	.uleb128 0x5
	.byte	0x3
	.4byte	pseudo_cg_tbl
	.uleb128 0xd
	.4byte	0x2bf
	.4byte	0x49c
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0xc
	.4byte	0x48c
	.uleb128 0xf
	.4byte	.LASF159
	.byte	0x3f
	.byte	0x17
	.4byte	0x49c
	.uleb128 0x5
	.byte	0x3
	.4byte	clk_always_on_cg_tbl
	.uleb128 0x5
	.4byte	.LASF162
	.byte	0xe3
	.byte	0x14
	.4byte	0x3d2
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x4ea
	.uleb128 0x3
	.4byte	.LASF160
	.byte	0xe3
	.byte	0x37
	.4byte	0x3a2
	.4byte	.LLST12
	.uleb128 0x3
	.4byte	.LASF161
	.byte	0xe3
	.byte	0x51
	.4byte	0x403
	.4byte	.LLST13
	.byte	0
	.uleb128 0x5
	.4byte	.LASF163
	.byte	0xd1
	.byte	0x9
	.4byte	0x86
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x522
	.uleb128 0x3
	.4byte	.LASF160
	.byte	0xd1
	.byte	0x30
	.4byte	0x3a2
	.4byte	.LLST10
	.uleb128 0x7
	.4byte	.LASF161
	.byte	0xd3
	.byte	0xd
	.4byte	0x86
	.4byte	.LLST11
	.byte	0
	.uleb128 0x5
	.4byte	.LASF164
	.byte	0xc0
	.byte	0x5
	.4byte	0x55a
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x55a
	.uleb128 0x3
	.4byte	.LASF165
	.byte	0xc0
	.byte	0x2a
	.4byte	0x2b4
	.4byte	.LLST9
	.uleb128 0x17
	.4byte	.LVL29
	.4byte	0x5f9
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF166
	.uleb128 0x5
	.4byte	.LASF167
	.byte	0xab
	.byte	0x14
	.4byte	0x3d2
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5ad
	.uleb128 0x3
	.4byte	.LASF165
	.byte	0xab
	.byte	0x36
	.4byte	0x2b4
	.4byte	.LLST8
	.uleb128 0x10
	.4byte	.LBB5
	.4byte	.LBE5-.LBB5
	.uleb128 0x11
	.4byte	.LASF169
	.byte	0xb7
	.4byte	0x3d2
	.uleb128 0x12
	.4byte	.LVL25
	.4byte	0x5f9
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF168
	.byte	0x96
	.byte	0x14
	.4byte	0x3d2
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5f9
	.uleb128 0x3
	.4byte	.LASF165
	.byte	0x96
	.byte	0x35
	.4byte	0x2b4
	.4byte	.LLST7
	.uleb128 0x10
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.uleb128 0x11
	.4byte	.LASF169
	.byte	0xa2
	.4byte	0x3d2
	.uleb128 0x12
	.4byte	.LVL21
	.4byte	0x5f9
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF170
	.byte	0x51
	.byte	0x9
	.4byte	0x7a
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x682
	.uleb128 0x3
	.4byte	.LASF165
	.byte	0x51
	.byte	0x30
	.4byte	0x2b4
	.4byte	.LLST0
	.uleb128 0x3
	.4byte	.LASF171
	.byte	0x51
	.byte	0x47
	.4byte	0x43a
	.4byte	.LLST1
	.uleb128 0x7
	.4byte	.LASF172
	.byte	0x53
	.byte	0x18
	.4byte	0x682
	.4byte	.LLST2
	.uleb128 0x7
	.4byte	.LASF173
	.byte	0x53
	.byte	0x29
	.4byte	0x682
	.4byte	.LLST3
	.uleb128 0x7
	.4byte	.LASF174
	.byte	0x53
	.byte	0x3b
	.4byte	0x682
	.4byte	.LLST4
	.uleb128 0x18
	.4byte	.LASF175
	.byte	0x1
	.byte	0x54
	.byte	0xe
	.4byte	0x92
	.uleb128 0x1
	.byte	0x56
	.uleb128 0x19
	.4byte	.LLRL5
	.uleb128 0x1a
	.string	"idx"
	.byte	0x1
	.byte	0x85
	.byte	0x11
	.4byte	0x86
	.4byte	.LLST6
	.byte	0
	.byte	0
	.uleb128 0x1b
	.byte	0x4
	.4byte	0x9e
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
	.uleb128 0x3
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
	.uleb128 0x4
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
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
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
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
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
	.uleb128 0x10
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.sleb128 28
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x5
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
	.uleb128 0x19
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
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
.LLST12:
	.byte	0x6
	.4byte	.LVL37
	.byte	0x4
	.uleb128 .LVL37-.LVL37
	.uleb128 .LVL39-.LVL37
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL39-.LVL37
	.uleb128 .LVL40-.LVL37
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
	.uleb128 .LVL40-.LVL37
	.uleb128 .LVL41-.LVL37
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL41-.LVL37
	.uleb128 .LFE8-.LVL37
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
	.4byte	.LVL37
	.byte	0x4
	.uleb128 .LVL37-.LVL37
	.uleb128 .LVL38-.LVL37
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL38-.LVL37
	.uleb128 .LVL40-.LVL37
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
	.uleb128 .LVL40-.LVL37
	.uleb128 .LFE8-.LVL37
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL31-.LVL30
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL31-.LVL30
	.uleb128 .LVL32-.LVL30
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
	.uleb128 .LVL32-.LVL30
	.uleb128 .LVL33-.LVL30
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL33-.LVL30
	.uleb128 .LVL35-.LVL30
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
	.uleb128 .LVL35-.LVL30
	.uleb128 .LVL36-.LVL30
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL36-.LVL30
	.uleb128 .LFE7-.LVL30
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
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL34-.LVL30
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL34-.LVL30
	.uleb128 .LVL35-.LVL30
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL35-.LVL30
	.uleb128 .LFE7-.LVL30
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
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
	.uleb128 .LVL28-.LVL26
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
	.uleb128 .LVL28-.LVL26
	.uleb128 .LVL29-1-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL29-1-.LVL26
	.uleb128 .LFE6-.LVL26
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
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL23-.LVL22
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL23-.LVL22
	.uleb128 .LVL24-.LVL22
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
	.uleb128 .LVL24-.LVL22
	.uleb128 .LVL25-1-.LVL22
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL25-1-.LVL22
	.uleb128 .LFE5-.LVL22
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
	.uleb128 .LVL19-.LVL18
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL19-.LVL18
	.uleb128 .LVL20-.LVL18
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
	.uleb128 .LVL20-.LVL18
	.uleb128 .LVL21-1-.LVL18
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL21-1-.LVL18
	.uleb128 .LFE4-.LVL18
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
	.uleb128 .LVL2-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL2-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL4-.LVL0
	.uleb128 .LVL5-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL5-.LVL0
	.uleb128 .LFE3-.LVL0
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL7-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL7-.LVL0
	.uleb128 .LVL9-.LVL0
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
	.uleb128 .LVL9-.LVL0
	.uleb128 .LVL11-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL11-.LVL0
	.uleb128 .LFE3-.LVL0
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
.LLST2:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL4-.LVL0
	.uleb128 .LVL5-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.LVL0
	.uleb128 .LVL6-.LVL0
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL4-.LVL0
	.uleb128 .LVL5-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.LVL0
	.uleb128 .LVL17-.LVL0
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL4-.LVL0
	.uleb128 .LVL5-.LVL0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.LVL0
	.uleb128 .LVL8-.LVL0
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL9-.LVL0
	.uleb128 .LVL10-.LVL0
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL13-.LVL12
	.uleb128 .LVL14-.LVL12
	.uleb128 0x3
	.byte	0x7e
	.sleb128 -1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL14-.LVL12
	.uleb128 .LVL15-.LVL12
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL16-.LVL12
	.uleb128 .LVL17-.LVL12
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x44
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
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
	.4byte	.LBB2
	.byte	0x4
	.uleb128 .LBB2-.LBB2
	.uleb128 .LBE2-.LBB2
	.byte	0x4
	.uleb128 .LBB3-.LBB2
	.uleb128 .LBE3-.LBB2
	.byte	0
.LLRL14:
	.byte	0x7
	.4byte	.LFB3
	.uleb128 .LFE3-.LFB3
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
	.byte	0x7
	.4byte	.LFB7
	.uleb128 .LFE7-.LFB7
	.byte	0x7
	.4byte	.LFB8
	.uleb128 .LFE8-.LFB8
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF127:
	.string	"CLK_OSC_26M_SEL"
.LASF34:
	.string	"HAL_CLOCK_CG_SPM_SYS"
.LASF83:
	.string	"HAL_CLOCK_CG_IRRX_BUS"
.LASF39:
	.string	"HAL_CLOCK_CG_KEY_SCAN_BCLK"
.LASF31:
	.string	"HAL_CLOCK_CG_SPM_PCLK"
.LASF153:
	.string	"CLK_REQ_DISABLE"
.LASF42:
	.string	"HAL_CLOCK_CG_PMU_1M"
.LASF124:
	.string	"CLK_DCXO_DIG_MACRO_SEL"
.LASF162:
	.string	"hal_clock_mux_sel"
.LASF167:
	.string	"hal_clock_disable"
.LASF30:
	.string	"HAL_CLOCK_CG_GLB_CON_DEBUG_DIS"
.LASF97:
	.string	"HAL_CLOCK_CG_PSEUDO_RGU_32K"
.LASF176:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF170:
	.string	"clock_physical_cg_ctrl"
.LASF67:
	.string	"HAL_CLOCK_CG_BT_MAC"
.LASF98:
	.string	"HAL_CLOCK_CG_PSEUDO_SLOW_BUS"
.LASF52:
	.string	"HAL_CLOCK_CG_BT_HOP"
.LASF29:
	.string	"HAL_CLOCK_CG_I3C_DMA0"
.LASF79:
	.string	"HAL_CLOCK_CG_I3C_DMA1"
.LASF38:
	.string	"HAL_CLOCK_CG_SECURITY_AO"
.LASF10:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF65:
	.string	"HAL_CLOCK_CG_SEJ"
.LASF63:
	.string	"HAL_CLOCK_CG_AUD_INTBUS"
.LASF132:
	.string	"CLK_PWM1_SEL"
.LASF161:
	.string	"mux_sel"
.LASF2:
	.string	"long long unsigned int"
.LASF150:
	.string	"CG_REQUEST_CLEAR"
.LASF110:
	.string	"CLK_SPISLV_SEL"
.LASF45:
	.string	"HAL_CLOCK_CG_SPIMST1_BUS"
.LASF115:
	.string	"CLK_BT_HOP_SEL"
.LASF105:
	.string	"CLK_SFC_SEL"
.LASF108:
	.string	"CLK_SPIMST1_SEL"
.LASF8:
	.string	"long int"
.LASF142:
	.string	"HAL_CLOCK_STATUS_OK"
.LASF154:
	.string	"cg_request_t"
.LASF32:
	.string	"HAL_CLOCK_CG_SPM_BCLK_CM33"
.LASF85:
	.string	"HAL_CLOCK_CG_BUS_ERR"
.LASF123:
	.string	"CLK_DCXO_PWR_CTRL_SEL"
.LASF58:
	.string	"HAL_CLOCK_CG_CKSYS_DEBUG_DIS"
.LASF174:
	.string	"clr_addr"
.LASF59:
	.string	"HAL_CLOCK_CG_SFC"
.LASF71:
	.string	"HAL_CLOCK_CG_AUD_ENGINE"
.LASF160:
	.string	"mux_id"
.LASF168:
	.string	"hal_clock_enable"
.LASF172:
	.string	"con_addr"
.LASF139:
	.string	"HAL_CLOCK_STATUS_UNINITIALIZED"
.LASF101:
	.string	"HAL_CLOCK_CG_PWM_MULTI_CTRL"
.LASF175:
	.string	"bit_idx"
.LASF117:
	.string	"CLK_UART0_SEL"
.LASF90:
	.string	"HAL_CLOCK_CG_USB_BUS"
.LASF136:
	.string	"CLK_MUX_SEL_PSEUDO_END"
.LASF126:
	.string	"CLK_IRRX_BCLK_SEL"
.LASF9:
	.string	"long unsigned int"
.LASF73:
	.string	"HAL_CLOCK_CG_OSC_HS_D2"
.LASF74:
	.string	"HAL_CLOCK_CG_OSC_HS_D4"
.LASF57:
	.string	"HAL_CLOCK_CG_BUS_ERR_TOP"
.LASF103:
	.string	"CLK_SYS_SEL"
.LASF112:
	.string	"CLK_USB_SEL"
.LASF140:
	.string	"HAL_CLOCK_STATUS_INVALID_PARAMETER"
.LASF7:
	.string	"short unsigned int"
.LASF120:
	.string	"CLK_GPT_BCLK_SEL"
.LASF164:
	.string	"hal_clock_is_enabled"
.LASF134:
	.string	"CLK_PWM3_SEL"
.LASF68:
	.string	"HAL_CLOCK_CG_CMSYS_BUS"
.LASF107:
	.string	"CLK_SPIMST0_SEL"
.LASF82:
	.string	"HAL_CLOCK_CG_IRRX"
.LASF116:
	.string	"CLK_BT_MAC_SEL"
.LASF137:
	.string	"TOTAL_MUX_CNT"
.LASF88:
	.string	"HAL_CLOCK_CG_AESOTF_ESC"
.LASF151:
	.string	"CG_REQUEST_SET"
.LASF106:
	.string	"CLK_ESC_SEL"
.LASF146:
	.string	"MUX_IBEX_IDX_OSC_26M"
.LASF114:
	.string	"CLK_AUD_BUS_SEL"
.LASF60:
	.string	"HAL_CLOCK_CG_ESC"
.LASF129:
	.string	"CLK_SLOW_BUS_SEL"
.LASF131:
	.string	"CLK_PWM0_SEL"
.LASF25:
	.string	"HAL_CLOCK_CG_UART_DMA0"
.LASF26:
	.string	"HAL_CLOCK_CG_UART_DMA1"
.LASF27:
	.string	"HAL_CLOCK_CG_UART_DMA2"
.LASF94:
	.string	"HAL_CLOCK_CG_PSUEDO_OSC_26M"
.LASF165:
	.string	"clock_id"
.LASF44:
	.string	"HAL_CLOCK_CG_SPIMST0_BUS"
.LASF37:
	.string	"HAL_CLOCK_CG_GPTIMER_SEC"
.LASF28:
	.string	"HAL_CLOCK_CG_I3C0"
.LASF55:
	.string	"HAL_CLOCK_CG_AUD_TEST"
.LASF99:
	.string	"HAL_CLOCK_CG_PSEUDO_END"
.LASF51:
	.string	"HAL_CLOCK_CG_I3C"
.LASF141:
	.string	"HAL_CLOCK_STATUS_ERROR"
.LASF56:
	.string	"HAL_CLOCK_CG_SEC_MON_TOP"
.LASF89:
	.string	"HAL_CLOCK_CG_CRYPTO"
.LASF119:
	.string	"CLK_UART2_SEL"
.LASF66:
	.string	"HAL_CLOCK_CG_EFUSE"
.LASF156:
	.string	"CG_SET__CLK_OFF"
.LASF149:
	.string	"CG_REQUEST_STATUS"
.LASF122:
	.string	"CLK_SEC_GPT_BCLK_SEL"
.LASF111:
	.string	"CLK_I3C_SEL"
.LASF64:
	.string	"HAL_CLOCK_CG_IBEX"
.LASF62:
	.string	"HAL_CLOCK_CG_USB"
.LASF33:
	.string	"HAL_CLOCK_CG_SPM_DIV"
.LASF95:
	.string	"HAL_CLOCK_CG_PSEUDO_DCXO_PWR_CTRL"
.LASF20:
	.string	"HAL_CLOCK_CG_PWM_3"
.LASF21:
	.string	"HAL_CLOCK_CG_PWM_4"
.LASF93:
	.string	"HAL_CLOCK_CG_PSEUDO_BEGIN"
.LASF40:
	.string	"HAL_CLOCK_CG_KEY_SCAN_F2M"
.LASF166:
	.string	"_Bool"
.LASF13:
	.string	"int32_t"
.LASF5:
	.string	"unsigned char"
.LASF158:
	.string	"pseudo_cg_tbl"
.LASF80:
	.string	"HAL_CLOCK_CG_TRNG"
.LASF19:
	.string	"HAL_CLOCK_CG_PWM_2"
.LASF6:
	.string	"short int"
.LASF173:
	.string	"set_addr"
.LASF81:
	.string	"HAL_CLOCK_CG_SPISLV_BUS"
.LASF102:
	.string	"hal_clock_cg_id"
.LASF152:
	.string	"CLK_REQ_ENABLE"
.LASF75:
	.string	"HAL_CLOCK_CG_AUXADC_SRAM"
.LASF144:
	.string	"MUX_IBEX_IDX_XO"
.LASF54:
	.string	"HAL_CLOCK_CG_IRTX"
.LASF76:
	.string	"HAL_CLOCK_CG_FAST_DMA_0"
.LASF148:
	.string	"clk_mux_sel_idx_t"
.LASF157:
	.string	"cg_state_t"
.LASF92:
	.string	"HAL_CLOCK_CG_CMSYS_ROM"
.LASF47:
	.string	"HAL_CLOCK_CG_SEC_MON_AO"
.LASF15:
	.string	"uint32_t"
.LASF163:
	.string	"hal_clock_mux_cur_sel"
.LASF18:
	.string	"HAL_CLOCK_CG_PWM_DMA_1"
.LASF48:
	.string	"HAL_CLOCK_CG_SPIMST0"
.LASF49:
	.string	"HAL_CLOCK_CG_SPIMST1"
.LASF50:
	.string	"HAL_CLOCK_CG_SPIMST2"
.LASF11:
	.string	"long double"
.LASF128:
	.string	"CLK_RGU_32K_SEL"
.LASF12:
	.string	"char"
.LASF3:
	.string	"unsigned int"
.LASF159:
	.string	"clk_always_on_cg_tbl"
.LASF133:
	.string	"CLK_PWM2_SEL"
.LASF104:
	.string	"CLK_IBEX_SEL"
.LASF143:
	.string	"hal_clock_status_t"
.LASF36:
	.string	"HAL_CLOCK_CG_GPTIMER"
.LASF77:
	.string	"HAL_CLOCK_CG_SPIMST2_BUS"
.LASF109:
	.string	"CLK_SPIMST2_SEL"
.LASF96:
	.string	"HAL_CLOCK_CG_PSEUDO_DCXO_DIG_MACRO"
.LASF155:
	.string	"CG_CLR__CLK_ON"
.LASF41:
	.string	"HAL_CLOCK_CG_UART0"
.LASF23:
	.string	"HAL_CLOCK_CG_UART1"
.LASF24:
	.string	"HAL_CLOCK_CG_UART2"
.LASF171:
	.string	"request"
.LASF125:
	.string	"CLK_IRTX_SEL"
.LASF147:
	.string	"MUX_IBEX_IDX_OSC_LS"
.LASF17:
	.string	"HAL_CLOCK_CG_PWM_DMA_0"
.LASF22:
	.string	"HAL_CLOCK_CG_ARGB_BCLK"
.LASF72:
	.string	"HAL_CLOCK_CG_OSC_LS_D2"
.LASF169:
	.string	"status"
.LASF91:
	.string	"HAL_CLOCK_CG_USB_DMA"
.LASF35:
	.string	"HAL_CLOCK_CG_OSTIMER"
.LASF121:
	.string	"CLK_OSGPT_BCLK_SEL"
.LASF14:
	.string	"uint8_t"
.LASF70:
	.string	"HAL_CLOCK_CG_CONN_BUS"
.LASF145:
	.string	"MUX_IBEX_IDX_XO_DBL"
.LASF69:
	.string	"HAL_CLOCK_CG_MEM_BUS"
.LASF16:
	.string	"HAL_CLOCK_CG_AUXADC"
.LASF53:
	.string	"HAL_CLOCK_CG_BT_MAC_CONN"
.LASF135:
	.string	"CLK_PWM4_SEL"
.LASF86:
	.string	"HAL_CLOCK_CG_SEC_MON"
.LASF113:
	.string	"CLK_AUD_ENGINE_SEL"
.LASF84:
	.string	"HAL_CLOCK_CG_AIO"
.LASF130:
	.string	"CLK_MUX_SEL_PSEUDO_BEGIN"
.LASF118:
	.string	"CLK_UART1_SEL"
.LASF100:
	.string	"HAL_CLOCK_CG_DUMMY_END"
.LASF61:
	.string	"HAL_CLOCK_CG_SPISLV"
.LASF43:
	.string	"HAL_CLOCK_CG_FAST_DMA_1"
.LASF138:
	.string	"clock_mux_sel_id"
.LASF78:
	.string	"HAL_CLOCK_CG_I3C1"
.LASF46:
	.string	"HAL_CLOCK_CG_BUS_ERR_AO"
.LASF87:
	.string	"HAL_CLOCK_CG_AESOTF"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_clock.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
