	.file	"hal_gpio_internal.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_gpio_internal.c"
	.section	.text.gpio_get_state,"ax",@progbits
	.align	1
	.globl	gpio_get_state
	.hidden	gpio_get_state
	.type	gpio_get_state, @function
gpio_get_state:
.LFB0:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_gpio_internal.c"
	.loc 1 112 1
	.cfi_startproc
.LVL0:
	.loc 1 113 5
	.loc 1 114 5
	.loc 1 115 5
	.loc 1 116 5
	.loc 1 117 5
	.loc 1 118 5
	.loc 1 122 5
	.loc 1 123 5
	.loc 1 124 5
	.loc 1 126 5
	.loc 1 127 5
	.loc 1 128 5
	.loc 1 129 5
	.loc 1 130 5
	.loc 1 131 5
	.loc 1 133 15 is_stmt 0
	srli	a5,a0,3
	.loc 1 135 33
	addi	a5,a5,12
	.loc 1 135 22
	lw	a4,gpio_base
	.loc 1 135 33
	slli	a5,a5,2
	add	a5,a4,a5
	lw	t1,0(a5)
	.loc 1 134 27
	andi	a5,a0,7
	.loc 1 134 15
	slli	a5,a5,2
	.loc 1 135 45
	srl	t1,t1,a5
	.loc 1 137 15
	srli	a5,a0,5
	slli	a5,a5,2
	add	a5,a4,a5
	.loc 1 112 1
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	.loc 1 139 31
	lw	a2,0(a5)
	.loc 1 112 1
	sw	s1,20(sp)
	.loc 1 140 31
	lw	a3,32(a5)
	.cfi_offset 9, -12
	.loc 1 141 33
	lw	s1,16(a5)
	.loc 1 112 1
	sw	s0,24(sp)
	.cfi_offset 8, -8
	mv	s0,a1
	.loc 1 138 15
	andi	a1,a0,31
.LVL1:
	.loc 1 139 43
	srl	a2,a2,a1
	.loc 1 140 43
	srl	a3,a3,a1
	.loc 1 141 45
	srl	s1,s1,a1
	.loc 1 112 1
	sw	ra,28(sp)
	.cfi_offset 1, -4
	.loc 1 131 32
	sw	zero,16(sp)
	.loc 1 133 5 is_stmt 1
	.loc 1 134 5
.LVL2:
	.loc 1 135 5
	.loc 1 152 49 is_stmt 0
	li	a5,22
	.loc 1 135 10
	andi	t1,t1,15
.LVL3:
	.loc 1 137 5 is_stmt 1
	.loc 1 138 5
	.loc 1 139 5
	.loc 1 139 9 is_stmt 0
	andi	a2,a2,1
.LVL4:
	.loc 1 140 5 is_stmt 1
	.loc 1 140 9 is_stmt 0
	andi	a3,a3,1
.LVL5:
	.loc 1 141 5 is_stmt 1
	.loc 1 141 10 is_stmt 0
	andi	s1,s1,1
.LVL6:
	.loc 1 143 5 is_stmt 1
	.loc 1 144 5
	.loc 1 149 5
	.loc 1 150 5
	.loc 1 152 5
	.loc 1 153 11 is_stmt 0 discriminator 2
	andi	a1,a0,0xff
.LVL7:
	li	a4,1108082688
	.loc 1 152 49
	bleu	a0,a5,.L2
.LVL8:
	.loc 1 153 5 is_stmt 1
	.loc 1 153 11 is_stmt 0 discriminator 1
	addi	a1,a1,-23
	andi	a1,a1,0xff
	.loc 1 152 49 discriminator 2
	li	a4,1108148224
.LVL9:
.L2:
	.loc 1 155 5 is_stmt 1
	.loc 1 155 12 is_stmt 0
	lw	a5,112(a4)
.LVL10:
	.loc 1 156 5 is_stmt 1
	.loc 1 156 12 is_stmt 0
	lw	t0,80(a4)
.LVL11:
	.loc 1 158 5 is_stmt 1
	.loc 1 155 57 is_stmt 0
	srl	a5,a5,a1
.LVL12:
	.loc 1 156 57
	srl	t0,t0,a1
.LVL13:
	.loc 1 158 16
	slli	a5,a5,4
	.loc 1 156 8
	andi	t0,t0,1
	.loc 1 158 16
	andi	a5,a5,16
	.loc 1 158 10
	or	a5,a5,t0
.LVL14:
	.loc 1 159 5 is_stmt 1
	.loc 1 159 24 is_stmt 0
	addi	a1,a0,-4
.LVL15:
	.loc 1 159 7
	li	t0,1
	bleu	a1,t0,.L3
	.loc 1 159 43 discriminator 1
	li	a1,38
	beq	a0,a1,.L10
	.loc 1 159 63 discriminator 2
	li	a1,39
	bne	a0,a1,.L5
	.loc 1 160 15 discriminator 4
	li	a1,2
	j	.L4
.L3:
	.loc 1 160 9 is_stmt 1
	.loc 1 160 15 is_stmt 0
	snez	a1,a1
	slli	a1,a1,1
.LVL16:
.L4:
	.loc 1 161 9 is_stmt 1
	.loc 1 161 53 is_stmt 0
	addi	a4,a4,128
	.loc 1 161 18
	lw	a4,0(a4)
	.loc 1 161 63
	srl	a4,a4,a1
	.loc 1 161 14
	andi	a4,a4,3
.LVL17:
	.loc 1 162 9 is_stmt 1
	.loc 1 162 31 is_stmt 0
	slli	a1,a4,8
.LVL18:
	.loc 1 162 45
	srli	a4,a4,1
.LVL19:
	.loc 1 162 31
	andi	a1,a1,256
	.loc 1 162 58
	slli	a4,a4,12
	.loc 1 162 36
	or	a4,a1,a4
	.loc 1 162 14
	or	a5,a5,a4
.LVL20:
.L5:
	.loc 1 165 5 is_stmt 1
	.loc 1 165 19 discriminator 1
	lla	a1,pull_map
	.loc 1 160 15 is_stmt 0 discriminator 3
	li	a4,0
	mv	t2,a1
	.loc 1 165 19 discriminator 1
	li	t0,10
.LVL21:
.L8:
	.loc 1 166 9 is_stmt 1
	.loc 1 166 32 is_stmt 0
	lhu	ra,0(a1)
	.loc 1 166 12
	bne	ra,a5,.L6
	.loc 1 167 13 is_stmt 1
	.loc 1 167 23 is_stmt 0
	slli	a4,a4,3
.LVL22:
	add	a4,t2,a4
	lw	a5,4(a4)
.LVL23:
	.loc 1 168 13 is_stmt 1
.L7:
	.loc 1 172 5 is_stmt 0
	addi	a1,sp,16
	sw	a3,12(sp)
	sw	a2,8(sp)
	sw	t1,4(sp)
	sw	a5,0(sp)
.LVL24:
	.loc 1 172 5 is_stmt 1
	call	hal_gpio_get_driving_current
.LVL25:
	.loc 1 174 5
	.loc 1 178 27 is_stmt 0
	lw	a5,0(sp)
	.loc 1 174 22
	lw	t1,4(sp)
	.loc 1 175 21
	lw	a2,8(sp)
	.loc 1 176 21
	lw	a3,12(sp)
	.loc 1 178 27
	sw	a5,12(s0)
	.loc 1 179 30
	lbu	a5,16(sp)
	.loc 1 174 22
	sb	t1,0(s0)
	.loc 1 175 5 is_stmt 1
	.loc 1 175 21 is_stmt 0
	sb	a2,1(s0)
	.loc 1 176 5 is_stmt 1
	.loc 1 177 22 is_stmt 0
	sw	s1,8(s0)
	.loc 1 182 1
	lw	ra,28(sp)
	.cfi_remember_state
	.cfi_restore 1
	.loc 1 176 21
	sw	a3,4(s0)
	.loc 1 177 5 is_stmt 1
	.loc 1 178 5
	.loc 1 179 5
	.loc 1 179 30 is_stmt 0
	sw	a5,16(s0)
	.loc 1 182 1
	lw	s0,24(sp)
	.cfi_restore 8
.LVL26:
	lw	s1,20(sp)
	.cfi_restore 9
.LVL27:
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
.LVL28:
	jr	ra
.LVL29:
.L10:
	.cfi_restore_state
	.loc 1 160 15 discriminator 3
	li	a1,0
	j	.L4
.LVL30:
.L6:
	.loc 1 165 26 is_stmt 1 discriminator 2
	.loc 1 165 19 discriminator 1
	addi	a4,a4,1
.LVL31:
	addi	a1,a1,8
	bne	a4,t0,.L8
	.loc 1 150 15 is_stmt 0
	li	a5,7
.LVL32:
	j	.L7
	.cfi_endproc
.LFE0:
	.size	gpio_get_state, .-gpio_get_state
	.section	.rodata.pull_map,"a"
	.align	2
	.type	pull_map, @object
	.size	pull_map, 80
pull_map:
	.half	0
	.zero	2
	.word	0
	.half	16
	.zero	2
	.word	1
	.half	1
	.zero	2
	.word	2
	.half	257
	.zero	2
	.word	4
	.half	4097
	.zero	2
	.word	9
	.half	4353
	.zero	2
	.word	6
	.half	272
	.zero	2
	.word	3
	.half	4112
	.zero	2
	.word	8
	.half	4368
	.zero	2
	.word	5
	.half	17
	.zero	2
	.word	7
	.hidden	gpio_cfg_table
	.globl	gpio_cfg_table
	.section	.rodata.gpio_cfg_table,"a"
	.align	2
	.type	gpio_cfg_table, @object
	.size	gpio_cfg_table, 240
gpio_cfg_table:
	.byte	0
	.byte	0
	.half	240
	.byte	0
	.byte	0
	.byte	2
	.2byte	240
	.byte	2
	.byte	0
	.byte	4
	.half	255
	.byte	-1
	.byte	0
	.byte	6
	.2byte	255
	.byte	-1
	.byte	0
	.byte	8
	.half	240
	.byte	8
	.byte	0
	.byte	10
	.2byte	240
	.byte	10
	.byte	0
	.byte	12
	.half	240
	.byte	12
	.byte	0
	.byte	14
	.2byte	240
	.byte	14
	.byte	0
	.byte	16
	.half	240
	.byte	16
	.byte	0
	.byte	18
	.2byte	255
	.byte	-1
	.byte	0
	.byte	20
	.half	255
	.byte	-1
	.byte	0
	.byte	22
	.2byte	255
	.byte	-1
	.byte	0
	.byte	24
	.half	255
	.byte	-1
	.byte	0
	.byte	26
	.2byte	255
	.byte	-1
	.byte	0
	.byte	28
	.half	255
	.byte	-1
	.byte	0
	.byte	30
	.2byte	255
	.byte	-1
	.byte	16
	.byte	0
	.half	255
	.byte	-1
	.byte	16
	.byte	2
	.2byte	256
	.byte	2
	.byte	16
	.byte	4
	.half	256
	.byte	4
	.byte	16
	.byte	6
	.2byte	256
	.byte	6
	.byte	16
	.byte	8
	.half	256
	.byte	8
	.byte	16
	.byte	10
	.2byte	256
	.byte	10
	.byte	16
	.byte	12
	.half	256
	.byte	12
	.byte	0
	.byte	0
	.2byte	256
	.byte	0
	.byte	0
	.byte	2
	.half	256
	.byte	2
	.byte	0
	.byte	4
	.2byte	256
	.byte	4
	.byte	0
	.byte	6
	.half	256
	.byte	6
	.byte	0
	.byte	8
	.2byte	256
	.byte	8
	.byte	0
	.byte	10
	.half	256
	.byte	10
	.byte	0
	.byte	12
	.2byte	256
	.byte	12
	.byte	0
	.byte	14
	.half	256
	.byte	14
	.byte	0
	.byte	16
	.2byte	256
	.byte	16
	.byte	0
	.byte	18
	.half	256
	.byte	18
	.byte	0
	.byte	20
	.2byte	256
	.byte	20
	.byte	0
	.byte	22
	.half	256
	.byte	22
	.byte	0
	.byte	24
	.2byte	256
	.byte	24
	.byte	0
	.byte	26
	.half	256
	.byte	26
	.byte	0
	.byte	28
	.2byte	256
	.byte	28
	.byte	0
	.byte	30
	.half	256
	.byte	30
	.byte	16
	.byte	0
	.2byte	272
	.byte	0
	.byte	16
	.byte	2
	.half	255
	.byte	-1
	.byte	16
	.byte	4
	.2byte	255
	.byte	-1
	.byte	16
	.byte	6
	.half	255
	.byte	-1
	.byte	16
	.byte	8
	.2byte	255
	.byte	-1
	.byte	16
	.byte	10
	.half	272
	.byte	10
	.byte	16
	.byte	12
	.2byte	272
	.byte	12
	.byte	16
	.byte	14
	.half	272
	.byte	14
	.byte	16
	.byte	16
	.2byte	272
	.byte	16
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpio.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpio.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpio_internal.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x6d7
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x17
	.4byte	.LASF135
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL16
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
	.uleb128 0x4
	.4byte	.LASF9
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x5c
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF8
	.uleb128 0x4
	.4byte	.LASF10
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x6f
	.uleb128 0x5
	.byte	0x2
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x4
	.4byte	.LASF12
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x87
	.uleb128 0x9
	.4byte	0x76
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x18
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x7
	.4byte	0x82
	.4byte	0xa5
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x9
	.4byte	0x95
	.uleb128 0x7
	.4byte	0x82
	.4byte	0xba
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x5
	.byte	0
	.uleb128 0x9
	.4byte	0xaa
	.uleb128 0x19
	.2byte	0x318
	.byte	0x3
	.byte	0x2b
	.byte	0x9
	.4byte	0x1d0
	.uleb128 0x2
	.4byte	.LASF14
	.byte	0x3
	.byte	0x2d
	.byte	0x17
	.4byte	0xa5
	.byte	0
	.uleb128 0x2
	.4byte	.LASF15
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0xa5
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF16
	.byte	0x3
	.byte	0x2f
	.byte	0x17
	.4byte	0xa5
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF17
	.byte	0x3
	.byte	0x30
	.byte	0x17
	.4byte	0xa5
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0x3
	.byte	0x31
	.byte	0x17
	.4byte	0xa5
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x3
	.byte	0x32
	.byte	0x17
	.4byte	0xa5
	.byte	0x28
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x3
	.byte	0x33
	.byte	0x17
	.4byte	0xba
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF21
	.byte	0x3
	.byte	0x34
	.byte	0x17
	.4byte	0xa5
	.byte	0x48
	.uleb128 0x2
	.4byte	.LASF22
	.byte	0x3
	.byte	0x35
	.byte	0x17
	.4byte	0x82
	.byte	0x50
	.uleb128 0x2
	.4byte	.LASF23
	.byte	0x3
	.byte	0x36
	.byte	0x17
	.4byte	0x1e0
	.byte	0x54
	.uleb128 0x3
	.4byte	.LASF24
	.byte	0x38
	.4byte	0xa5
	.2byte	0x110
	.uleb128 0x3
	.4byte	.LASF25
	.byte	0x39
	.4byte	0xa5
	.2byte	0x118
	.uleb128 0x3
	.4byte	.LASF26
	.byte	0x3a
	.4byte	0xa5
	.2byte	0x120
	.uleb128 0x3
	.4byte	.LASF27
	.byte	0x3b
	.4byte	0xba
	.2byte	0x128
	.uleb128 0x3
	.4byte	.LASF28
	.byte	0x3c
	.4byte	0xa5
	.2byte	0x140
	.uleb128 0x3
	.4byte	.LASF29
	.byte	0x3d
	.4byte	0xa5
	.2byte	0x148
	.uleb128 0x3
	.4byte	.LASF30
	.byte	0x3e
	.4byte	0xa5
	.2byte	0x150
	.uleb128 0x3
	.4byte	.LASF31
	.byte	0x3f
	.4byte	0x1f5
	.2byte	0x158
	.uleb128 0x3
	.4byte	.LASF32
	.byte	0x41
	.4byte	0xba
	.2byte	0x200
	.uleb128 0x3
	.4byte	.LASF33
	.byte	0x42
	.4byte	0x20a
	.2byte	0x218
	.uleb128 0x3
	.4byte	.LASF34
	.byte	0x44
	.4byte	0xba
	.2byte	0x300
	.byte	0
	.uleb128 0x7
	.4byte	0x82
	.4byte	0x1e0
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x2e
	.byte	0
	.uleb128 0x9
	.4byte	0x1d0
	.uleb128 0x7
	.4byte	0x82
	.4byte	0x1f5
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x29
	.byte	0
	.uleb128 0x9
	.4byte	0x1e5
	.uleb128 0x7
	.4byte	0x82
	.4byte	0x20a
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x39
	.byte	0
	.uleb128 0x9
	.4byte	0x1fa
	.uleb128 0x4
	.4byte	.LASF35
	.byte	0x3
	.byte	0x45
	.byte	0x3
	.4byte	0xbf
	.uleb128 0x10
	.4byte	0x2d
	.2byte	0x1cd
	.4byte	0x34d
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x30
	.byte	0
	.uleb128 0x11
	.4byte	.LASF85
	.2byte	0x1ff
	.4byte	0x21b
	.uleb128 0x10
	.4byte	0x2d
	.2byte	0x23d
	.4byte	0x382
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x4
	.byte	0
	.uleb128 0x11
	.4byte	.LASF91
	.2byte	0x243
	.4byte	0x358
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0xda
	.4byte	0x3a6
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF94
	.byte	0x5
	.byte	0xdd
	.byte	0x3
	.4byte	0x38d
	.uleb128 0xc
	.byte	0x5
	.4byte	0x8e
	.byte	0x5
	.byte	0xe1
	.4byte	0x3d7
	.uleb128 0xd
	.4byte	.LASF95
	.sleb128 -3
	.uleb128 0xd
	.4byte	.LASF96
	.sleb128 -2
	.uleb128 0xd
	.4byte	.LASF97
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF99
	.byte	0x5
	.byte	0xe6
	.byte	0x3
	.4byte	0x3b2
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0x68
	.4byte	0x42c
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x9
	.byte	0
	.uleb128 0x4
	.4byte	.LASF110
	.byte	0x6
	.byte	0x73
	.byte	0x3
	.4byte	0x3e3
	.uleb128 0xe
	.byte	0x5
	.byte	0x6
	.byte	0x79
	.4byte	0x475
	.uleb128 0x2
	.4byte	.LASF111
	.byte	0x6
	.byte	0x7a
	.byte	0xd
	.4byte	0x50
	.byte	0
	.uleb128 0x2
	.4byte	.LASF112
	.byte	0x6
	.byte	0x7b
	.byte	0xd
	.4byte	0x50
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF113
	.byte	0x6
	.byte	0x7c
	.byte	0xe
	.4byte	0x63
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF114
	.byte	0x6
	.byte	0x7d
	.byte	0xd
	.4byte	0x50
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF115
	.byte	0x6
	.byte	0x7e
	.byte	0x1b
	.4byte	0x438
	.uleb128 0xa
	.4byte	0x475
	.uleb128 0xe
	.byte	0x14
	.byte	0x6
	.byte	0x80
	.4byte	0x4db
	.uleb128 0x2
	.4byte	.LASF116
	.byte	0x6
	.byte	0x81
	.byte	0xd
	.4byte	0x50
	.byte	0
	.uleb128 0x12
	.string	"dir"
	.byte	0x82
	.byte	0xd
	.4byte	0x50
	.byte	0x1
	.uleb128 0x12
	.string	"din"
	.byte	0x83
	.byte	0x15
	.4byte	0x3a6
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF117
	.byte	0x6
	.byte	0x84
	.byte	0x15
	.4byte	0x3a6
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF118
	.byte	0x6
	.byte	0x85
	.byte	0x16
	.4byte	0x42c
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF119
	.byte	0x6
	.byte	0x86
	.byte	0x20
	.4byte	0x382
	.byte	0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF120
	.byte	0x6
	.byte	0x87
	.byte	0x3
	.4byte	0x486
	.uleb128 0x13
	.4byte	.LASF121
	.byte	0x8e
	.byte	0x1e
	.4byte	0x4f2
	.uleb128 0xf
	.4byte	0x20f
	.uleb128 0x7
	.4byte	0x481
	.4byte	0x502
	.uleb128 0x1a
	.byte	0
	.uleb128 0xa
	.4byte	0x4f7
	.uleb128 0x13
	.4byte	.LASF122
	.byte	0x91
	.byte	0x21
	.4byte	0x502
	.uleb128 0x7
	.4byte	0x481
	.4byte	0x522
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x2f
	.byte	0
	.uleb128 0xa
	.4byte	0x512
	.uleb128 0x1b
	.4byte	0x507
	.byte	0x1
	.byte	0x29
	.byte	0x1a
	.4byte	0x522
	.uleb128 0x5
	.byte	0x3
	.4byte	gpio_cfg_table
	.uleb128 0xe
	.byte	0x8
	.byte	0x1
	.byte	0x5d
	.4byte	0x55c
	.uleb128 0x2
	.4byte	.LASF123
	.byte	0x1
	.byte	0x5e
	.byte	0xe
	.4byte	0x63
	.byte	0
	.uleb128 0x2
	.4byte	.LASF124
	.byte	0x1
	.byte	0x5f
	.byte	0x16
	.4byte	0x42c
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF125
	.byte	0x1
	.byte	0x60
	.byte	0x3
	.4byte	0x539
	.uleb128 0xa
	.4byte	0x55c
	.uleb128 0x7
	.4byte	0x568
	.4byte	0x57d
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0xa
	.4byte	0x56d
	.uleb128 0x14
	.4byte	.LASF128
	.byte	0x62
	.byte	0x19
	.4byte	0x57d
	.uleb128 0x5
	.byte	0x3
	.4byte	pull_map
	.uleb128 0x1c
	.4byte	.LASF136
	.byte	0x5
	.2byte	0x295
	.byte	0x13
	.4byte	0x3d7
	.4byte	0x5af
	.uleb128 0x15
	.4byte	0x34d
	.uleb128 0x15
	.4byte	0x5af
	.byte	0
	.uleb128 0xf
	.4byte	0x382
	.uleb128 0x1d
	.4byte	.LASF137
	.byte	0x1
	.byte	0x6f
	.byte	0x6
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x6d5
	.uleb128 0x16
	.4byte	.LASF126
	.byte	0x6f
	.byte	0x24
	.4byte	0x34d
	.4byte	.LLST0
	.uleb128 0x16
	.4byte	.LASF127
	.byte	0x6f
	.byte	0x3c
	.4byte	0x6d5
	.4byte	.LLST1
	.uleb128 0x6
	.4byte	.LASF116
	.byte	0x71
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST2
	.uleb128 0xb
	.string	"dir"
	.byte	0x72
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST3
	.uleb128 0xb
	.string	"din"
	.byte	0x73
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST4
	.uleb128 0x6
	.4byte	.LASF117
	.byte	0x74
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST5
	.uleb128 0xb
	.string	"pu"
	.byte	0x75
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST6
	.uleb128 0xb
	.string	"pd"
	.byte	0x76
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST7
	.uleb128 0x6
	.4byte	.LASF129
	.byte	0x7a
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST8
	.uleb128 0x6
	.4byte	.LASF130
	.byte	0x7b
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST9
	.uleb128 0xb
	.string	"j"
	.byte	0x7c
	.byte	0xd
	.4byte	0x50
	.4byte	.LLST10
	.uleb128 0x6
	.4byte	.LASF118
	.byte	0x7e
	.byte	0x16
	.4byte	0x42c
	.4byte	.LLST11
	.uleb128 0x6
	.4byte	.LASF123
	.byte	0x7f
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST12
	.uleb128 0x6
	.4byte	.LASF131
	.byte	0x80
	.byte	0xd
	.4byte	0x50
	.4byte	.LLST13
	.uleb128 0x6
	.4byte	.LASF132
	.byte	0x81
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST14
	.uleb128 0x6
	.4byte	.LASF133
	.byte	0x82
	.byte	0xe
	.4byte	0x76
	.4byte	.LLST15
	.uleb128 0x14
	.4byte	.LASF134
	.byte	0x83
	.byte	0x20
	.4byte	0x382
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x1e
	.4byte	.LVL25
	.4byte	0x593
	.uleb128 0x1f
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	0x4db
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 23
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
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
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xd
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xf
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
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
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x1d
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
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
.LLST0:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL25-1-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL25-1-.LVL0
	.uleb128 .LVL29-.LVL0
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
	.uleb128 .LVL29-.LVL0
	.uleb128 .LFE0-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL1-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL1-.LVL0
	.uleb128 .LVL26-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL26-.LVL0
	.uleb128 .LVL29-.LVL0
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
	.uleb128 .LVL29-.LVL0
	.uleb128 .LFE0-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL25-1-.LVL3
	.uleb128 0x1
	.byte	0x56
	.byte	0x4
	.uleb128 .LVL25-1-.LVL3
	.uleb128 .LVL28-.LVL3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0x4
	.uleb128 .LVL28-.LVL3
	.uleb128 .LVL29-.LVL3
	.uleb128 0x2
	.byte	0x72
	.sleb128 -28
	.byte	0x4
	.uleb128 .LVL29-.LVL3
	.uleb128 .LFE0-.LVL3
	.uleb128 0x1
	.byte	0x56
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL25-1-.LVL4
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL25-1-.LVL4
	.uleb128 .LVL28-.LVL4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL28-.LVL4
	.uleb128 .LVL29-.LVL4
	.uleb128 0x2
	.byte	0x72
	.sleb128 -24
	.byte	0x4
	.uleb128 .LVL29-.LVL4
	.uleb128 .LFE0-.LVL4
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL25-1-.LVL5
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL25-1-.LVL5
	.uleb128 .LVL28-.LVL5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL28-.LVL5
	.uleb128 .LVL29-.LVL5
	.uleb128 0x2
	.byte	0x72
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL29-.LVL5
	.uleb128 .LFE0-.LVL5
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL6
	.byte	0x4
	.uleb128 .LVL6-.LVL6
	.uleb128 .LVL27-.LVL6
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL27-.LVL6
	.uleb128 .LVL29-.LVL6
	.uleb128 0xb
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
	.uleb128 0x8
	.byte	0x4
	.uleb128 .LVL29-.LVL6
	.uleb128 .LFE0-.LVL6
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL6
	.byte	0x4
	.uleb128 .LVL6-.LVL6
	.uleb128 .LVL10-.LVL6
	.uleb128 0x2
	.byte	0x3f
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL10-.LVL6
	.uleb128 .LVL12-.LVL6
	.uleb128 0x8
	.byte	0x7f
	.sleb128 0
	.byte	0x7b
	.sleb128 0
	.byte	0x25
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL6
	.byte	0x4
	.uleb128 .LVL6-.LVL6
	.uleb128 .LVL11-.LVL6
	.uleb128 0x2
	.byte	0x3f
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL11-.LVL6
	.uleb128 .LVL13-.LVL6
	.uleb128 0x8
	.byte	0x75
	.sleb128 0
	.byte	0x7b
	.sleb128 0
	.byte	0x25
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST8:
	.byte	0x8
	.4byte	.LVL17
	.uleb128 .LVL19-.LVL17
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST9:
	.byte	0x8
	.4byte	.LVL8
	.uleb128 .LVL9-.LVL8
	.uleb128 0x6
	.byte	0xc
	.4byte	0x420d0000
	.byte	0x9f
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL20
	.byte	0x4
	.uleb128 .LVL20-.LVL20
	.uleb128 .LVL21-.LVL20
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL21-.LVL20
	.uleb128 .LVL22-.LVL20
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL30-.LVL20
	.uleb128 .LVL31-.LVL20
	.uleb128 0x3
	.byte	0x7e
	.sleb128 1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL31-.LVL20
	.uleb128 .LFE0-.LVL20
	.uleb128 0x3
	.byte	0x7e
	.sleb128 0
	.byte	0x9f
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL6
	.byte	0x4
	.uleb128 .LVL6-.LVL6
	.uleb128 .LVL23-.LVL6
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL24-.LVL6
	.uleb128 .LVL25-1-.LVL6
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL25-1-.LVL6
	.uleb128 .LVL28-.LVL6
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL28-.LVL6
	.uleb128 .LVL29-.LVL6
	.uleb128 0x2
	.byte	0x72
	.sleb128 -32
	.byte	0x4
	.uleb128 .LVL29-.LVL6
	.uleb128 .LFE0-.LVL6
	.uleb128 0x2
	.byte	0x37
	.byte	0x9f
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL14
	.byte	0x4
	.uleb128 .LVL14-.LVL14
	.uleb128 .LVL23-.LVL14
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL29-.LVL14
	.uleb128 .LVL32-.LVL14
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL6
	.byte	0x4
	.uleb128 .LVL6-.LVL6
	.uleb128 .LVL9-.LVL6
	.uleb128 0x3
	.byte	0x9
	.byte	0xff
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL9-.LVL6
	.uleb128 .LVL15-.LVL6
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL16-.LVL6
	.uleb128 .LVL18-.LVL6
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL25-1-.LVL3
	.uleb128 0x5
	.byte	0x7a
	.sleb128 0
	.byte	0x35
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL25-1-.LVL3
	.uleb128 .LVL29-.LVL3
	.uleb128 0xc
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x35
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL29-.LVL3
	.uleb128 .LFE0-.LVL3
	.uleb128 0x5
	.byte	0x7a
	.sleb128 0
	.byte	0x35
	.byte	0x25
	.byte	0x9f
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL3-.LVL2
	.uleb128 0x7
	.byte	0x7a
	.sleb128 0
	.byte	0x37
	.byte	0x1a
	.byte	0x32
	.byte	0x24
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.LVL2
	.uleb128 .LVL7-.LVL2
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL7-.LVL2
	.uleb128 .LVL25-1-.LVL2
	.uleb128 0x5
	.byte	0x7a
	.sleb128 0
	.byte	0x4f
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL25-1-.LVL2
	.uleb128 .LVL29-.LVL2
	.uleb128 0xc
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x4f
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL29-.LVL2
	.uleb128 .LFE0-.LVL2
	.uleb128 0x5
	.byte	0x7a
	.sleb128 0
	.byte	0x4f
	.byte	0x1a
	.byte	0x9f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
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
.LLRL16:
	.byte	0x7
	.4byte	.LFB0
	.uleb128 .LFE0-.LFB0
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF22:
	.string	"GPIO_BACKUP"
.LASF84:
	.string	"HAL_GPIO_MAX"
.LASF117:
	.string	"dout"
.LASF66:
	.string	"HAL_GPIO_30"
.LASF67:
	.string	"HAL_GPIO_31"
.LASF68:
	.string	"HAL_GPIO_32"
.LASF69:
	.string	"HAL_GPIO_33"
.LASF70:
	.string	"HAL_GPIO_34"
.LASF71:
	.string	"HAL_GPIO_35"
.LASF72:
	.string	"HAL_GPIO_36"
.LASF73:
	.string	"HAL_GPIO_37"
.LASF74:
	.string	"HAL_GPIO_38"
.LASF75:
	.string	"HAL_GPIO_39"
.LASF30:
	.string	"GPIO_DOUT_CLR"
.LASF105:
	.string	"GPIO_PU_R0_R1"
.LASF26:
	.string	"GPIO_DIR_CLR"
.LASF2:
	.string	"long long unsigned int"
.LASF132:
	.string	"reg_index"
.LASF100:
	.string	"GPIO_NO_PULL"
.LASF88:
	.string	"HAL_GPIO_DRIVING_CURRENT_12MA"
.LASF120:
	.string	"gpio_state_t"
.LASF93:
	.string	"HAL_GPIO_DATA_HIGH"
.LASF7:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF87:
	.string	"HAL_GPIO_DRIVING_CURRENT_8MA"
.LASF76:
	.string	"HAL_GPIO_40"
.LASF77:
	.string	"HAL_GPIO_41"
.LASF78:
	.string	"HAL_GPIO_42"
.LASF79:
	.string	"HAL_GPIO_43"
.LASF80:
	.string	"HAL_GPIO_44"
.LASF81:
	.string	"HAL_GPIO_45"
.LASF82:
	.string	"HAL_GPIO_46"
.LASF83:
	.string	"HAL_GPIO_47"
.LASF137:
	.string	"gpio_get_state"
.LASF6:
	.string	"long int"
.LASF18:
	.string	"GPIO_DIN"
.LASF14:
	.string	"GPIO_DIR"
.LASF10:
	.string	"uint16_t"
.LASF28:
	.string	"GPIO_DOUT_SET"
.LASF131:
	.string	"shift"
.LASF24:
	.string	"GPIO_DIR_SET"
.LASF125:
	.string	"pull_map_t"
.LASF130:
	.string	"io_cfg_base"
.LASF121:
	.string	"gpio_base"
.LASF123:
	.string	"temp"
.LASF20:
	.string	"GPIO_MODE"
.LASF116:
	.string	"mode"
.LASF3:
	.string	"unsigned int"
.LASF13:
	.string	"long unsigned int"
.LASF135:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF127:
	.string	"gpio_state"
.LASF11:
	.string	"short unsigned int"
.LASF89:
	.string	"HAL_GPIO_DRIVING_CURRENT_16MA"
.LASF104:
	.string	"GPIO_PD_R0"
.LASF124:
	.string	"pull"
.LASF85:
	.string	"hal_gpio_pin_t"
.LASF111:
	.string	"drv_reg"
.LASF101:
	.string	"GPIO_PU_R"
.LASF96:
	.string	"HAL_GPIO_STATUS_ERROR_PIN"
.LASF133:
	.string	"bit_index"
.LASF35:
	.string	"GPIO_BASE_REGISTER_T"
.LASF114:
	.string	"rtc_gpio_mode_reg_shift"
.LASF109:
	.string	"GPIO_PD_R1"
.LASF102:
	.string	"GPIO_PD_R"
.LASF126:
	.string	"gpio_pin"
.LASF107:
	.string	"GPIO_PUPD_ERR"
.LASF112:
	.string	"drv_shift"
.LASF128:
	.string	"pull_map"
.LASF118:
	.string	"pull_type"
.LASF15:
	.string	"RESERVED0"
.LASF17:
	.string	"RESERVED1"
.LASF19:
	.string	"RESERVED2"
.LASF21:
	.string	"RESERVED3"
.LASF34:
	.string	"GPIO_MODE_CLR"
.LASF25:
	.string	"RESERVED5"
.LASF27:
	.string	"RESERVED6"
.LASF29:
	.string	"RESERVED7"
.LASF31:
	.string	"RESERVED8"
.LASF33:
	.string	"RESERVED9"
.LASF8:
	.string	"unsigned char"
.LASF99:
	.string	"hal_gpio_status_t"
.LASF5:
	.string	"short int"
.LASF103:
	.string	"GPIO_PU_R0"
.LASF108:
	.string	"GPIO_PU_R1"
.LASF16:
	.string	"GPIO_DOUT"
.LASF113:
	.string	"rtc_gpio_mode_reg"
.LASF110:
	.string	"gpio_pull_type_t"
.LASF23:
	.string	"RESERVED4"
.LASF134:
	.string	"driving_value"
.LASF12:
	.string	"uint32_t"
.LASF92:
	.string	"HAL_GPIO_DATA_LOW"
.LASF122:
	.string	"gpio_cfg_table"
.LASF94:
	.string	"hal_gpio_data_t"
.LASF46:
	.string	"HAL_GPIO_10"
.LASF47:
	.string	"HAL_GPIO_11"
.LASF48:
	.string	"HAL_GPIO_12"
.LASF49:
	.string	"HAL_GPIO_13"
.LASF50:
	.string	"HAL_GPIO_14"
.LASF51:
	.string	"HAL_GPIO_15"
.LASF52:
	.string	"HAL_GPIO_16"
.LASF53:
	.string	"HAL_GPIO_17"
.LASF54:
	.string	"HAL_GPIO_18"
.LASF55:
	.string	"HAL_GPIO_19"
.LASF115:
	.string	"hal_gpio_cfg_reg_t"
.LASF98:
	.string	"HAL_GPIO_STATUS_OK"
.LASF9:
	.string	"uint8_t"
.LASF32:
	.string	"GPIO_MODE_SET"
.LASF90:
	.string	"HAL_GPIO_DRIVING_CURRENT_MAX"
.LASF106:
	.string	"GPIO_PD_R0_R1"
.LASF91:
	.string	"hal_gpio_driving_current_t"
.LASF86:
	.string	"HAL_GPIO_DRIVING_CURRENT_4MA"
.LASF136:
	.string	"hal_gpio_get_driving_current"
.LASF95:
	.string	"HAL_GPIO_STATUS_ERROR"
.LASF56:
	.string	"HAL_GPIO_20"
.LASF57:
	.string	"HAL_GPIO_21"
.LASF58:
	.string	"HAL_GPIO_22"
.LASF59:
	.string	"HAL_GPIO_23"
.LASF60:
	.string	"HAL_GPIO_24"
.LASF61:
	.string	"HAL_GPIO_25"
.LASF62:
	.string	"HAL_GPIO_26"
.LASF63:
	.string	"HAL_GPIO_27"
.LASF64:
	.string	"HAL_GPIO_28"
.LASF65:
	.string	"HAL_GPIO_29"
.LASF129:
	.string	"rsel"
.LASF119:
	.string	"current_type"
.LASF36:
	.string	"HAL_GPIO_0"
.LASF37:
	.string	"HAL_GPIO_1"
.LASF38:
	.string	"HAL_GPIO_2"
.LASF39:
	.string	"HAL_GPIO_3"
.LASF40:
	.string	"HAL_GPIO_4"
.LASF41:
	.string	"HAL_GPIO_5"
.LASF42:
	.string	"HAL_GPIO_6"
.LASF43:
	.string	"HAL_GPIO_7"
.LASF44:
	.string	"HAL_GPIO_8"
.LASF45:
	.string	"HAL_GPIO_9"
.LASF97:
	.string	"HAL_GPIO_STATUS_INVALID_PARAMETER"
	.section	.debug_line_str,"MS",@progbits,1
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_gpio_internal.c"
.LASF1:
	.string	"/workdir/airoha/risc-v"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
