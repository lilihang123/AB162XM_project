	.file	"hal_hw_semaphore.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/drivers/chip/ab162x/src/hal_hw_semaphore.c"
	.section	.text.hal_hw_semaphore_query_channel,"ax",@progbits
	.align	1
	.globl	hal_hw_semaphore_query_channel
	.hidden	hal_hw_semaphore_query_channel
	.type	hal_hw_semaphore_query_channel, @function
hal_hw_semaphore_query_channel:
.LFB6:
	.file 1 "/workdir/airoha/common/drivers/chip/ab162x/src/hal_hw_semaphore.c"
	.loc 1 97 1
	.cfi_startproc
.LVL0:
	.loc 1 98 5
	.loc 1 98 8 is_stmt 0
	li	a5,31
	bgtu	a0,a5,.L4
	.loc 1 102 5 is_stmt 1
	.loc 1 102 53 is_stmt 0
	li	a4,1110048768
	lw	a3,16(a4)
	.loc 1 102 74
	li	a5,1
	sll	a5,a5,a0
	.loc 1 102 69
	and	a3,a3,a5
	.loc 1 103 16
	li	a0,255
.LVL1:
	.loc 1 102 8
	beq	a3,zero,.L1
.LVL2:
.LBB2:
	.loc 1 107 13 is_stmt 1
	.loc 1 107 71 is_stmt 0
	lw	a3,0(a4)
	.loc 1 106 17
	li	a0,0
	.loc 1 107 76
	and	a3,a5,a3
	.loc 1 107 16
	bne	a3,zero,.L1
	.loc 1 106 86 is_stmt 1 discriminator 2
.LVL3:
	.loc 1 106 52 discriminator 1
	.loc 1 107 13
	.loc 1 107 71 is_stmt 0
	lw	a3,4(a4)
	.loc 1 106 86 discriminator 2
	li	a0,1
	.loc 1 107 76
	and	a3,a5,a3
	.loc 1 107 16
	bne	a3,zero,.L1
	.loc 1 106 86 is_stmt 1 discriminator 2
.LVL4:
	.loc 1 106 52 discriminator 1
	.loc 1 107 13
	.loc 1 107 71 is_stmt 0
	lw	a4,8(a4)
.LBE2:
	.loc 1 103 16
	li	a0,255
.LBB3:
	.loc 1 107 76
	and	a5,a5,a4
	.loc 1 107 16
	beq	a5,zero,.L1
	li	a0,2
	ret
.LVL5:
.L4:
.LBE3:
	.loc 1 99 16
	li	a0,-3
.LVL6:
.L1:
	.loc 1 113 1
	ret
	.cfi_endproc
.LFE6:
	.size	hal_hw_semaphore_query_channel, .-hal_hw_semaphore_query_channel
	.section	.text.hw_semaphore_take,"ax",@progbits
	.align	1
	.globl	hw_semaphore_take
	.hidden	hw_semaphore_take
	.type	hw_semaphore_take, @function
hw_semaphore_take:
.LFB7:
	.loc 1 116 1 is_stmt 1
	.cfi_startproc
.LVL7:
	.loc 1 117 5
	.loc 1 118 5
	.loc 1 116 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	a0,0(sp)
	.loc 1 118 5
	addi	a0,sp,4
.LVL8:
	.loc 1 116 1
	sw	s0,12(sp)
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 118 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL9:
	.loc 1 120 5 is_stmt 1
	.loc 1 120 73 is_stmt 0
	lw	a4,0(sp)
	.loc 1 120 64
	li	s1,1110048768
	lw	a5,4(s1)
	.loc 1 120 73
	li	s0,1
	sll	s0,s0,a4
	.loc 1 120 68
	and	a5,a5,s0
	.loc 1 120 8
	beq	a5,zero,.L11
	.loc 1 121 9 is_stmt 1
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL10:
	.loc 1 122 9
	.loc 1 122 16 is_stmt 0
	li	a0,-1
.L10:
	.loc 1 127 1
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
.LVL11:
	jr	ra
.LVL12:
.L11:
	.cfi_restore_state
	.loc 1 124 5 is_stmt 1
	.loc 1 124 70 is_stmt 0
	sw	s0,512(s1)
	.loc 1 125 5 is_stmt 1
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL13:
	.loc 1 126 5
	.loc 1 126 68 is_stmt 0
	lw	a5,4(s1)
	.loc 1 126 72
	and	a0,s0,a5
	.loc 1 126 128
	seqz	a0,a0
	neg	a0,a0
	j	.L10
	.cfi_endproc
.LFE7:
	.size	hw_semaphore_take, .-hw_semaphore_take
	.section	.text.hal_hw_semaphore_take,"ax",@progbits
	.align	1
	.globl	hal_hw_semaphore_take
	.hidden	hal_hw_semaphore_take
	.type	hal_hw_semaphore_take, @function
hal_hw_semaphore_take:
.LFB4:
	.loc 1 66 1 is_stmt 1
	.cfi_startproc
.LVL14:
	.loc 1 77 5
	.loc 1 78 5
	.loc 1 78 8 is_stmt 0
	li	a5,31
	bgtu	a0,a5,.L15
	.loc 1 81 5 is_stmt 1
	.loc 1 81 16 is_stmt 0
	tail	hw_semaphore_take
.LVL15:
.L15:
	.loc 1 83 1
	li	a0,-3
.LVL16:
	ret
	.cfi_endproc
.LFE4:
	.size	hal_hw_semaphore_take, .-hal_hw_semaphore_take
	.section	.text.hw_semaphore_take_special,"ax",@progbits
	.align	1
	.globl	hw_semaphore_take_special
	.hidden	hw_semaphore_take_special
	.type	hw_semaphore_take_special, @function
hw_semaphore_take_special:
.LFB8:
	.loc 1 130 1 is_stmt 1
	.cfi_startproc
.LVL17:
	.loc 1 131 5
	.loc 1 131 64 is_stmt 0
	li	a4,1110048768
	lw	a3,4(a4)
	.loc 1 131 73
	li	a5,1
	sll	a0,a5,a0
.LVL18:
	.loc 1 131 68
	and	a3,a3,a0
	.loc 1 131 8
	bne	a3,zero,.L18
	.loc 1 134 5 is_stmt 1
	.loc 1 134 70 is_stmt 0
	sw	a0,512(a4)
	.loc 1 135 5 is_stmt 1
	.loc 1 135 68 is_stmt 0
	lw	a5,4(a4)
	.loc 1 135 72
	and	a0,a0,a5
	.loc 1 135 128
	seqz	a0,a0
	neg	a0,a0
	ret
.L18:
	.loc 1 132 16
	li	a0,-1
	.loc 1 136 1
	ret
	.cfi_endproc
.LFE8:
	.size	hw_semaphore_take_special, .-hw_semaphore_take_special
	.section	.text.hw_semaphore_give,"ax",@progbits
	.align	1
	.globl	hw_semaphore_give
	.hidden	hw_semaphore_give
	.type	hw_semaphore_give, @function
hw_semaphore_give:
.LFB9:
	.loc 1 139 1 is_stmt 1
	.cfi_startproc
.LVL19:
	.loc 1 140 5
	.loc 1 141 5
	.loc 1 139 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	a0,0(sp)
	.loc 1 141 5
	addi	a0,sp,4
.LVL20:
	.loc 1 139 1
	sw	s0,12(sp)
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 141 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL21:
	.loc 1 142 5 is_stmt 1
	.loc 1 142 73 is_stmt 0
	lw	a4,0(sp)
	.loc 1 142 64
	li	s1,1110048768
	lw	a5,4(s1)
	.loc 1 142 73
	li	s0,1
	sll	s0,s0,a4
	.loc 1 142 68
	and	a5,a5,s0
	.loc 1 142 8
	bne	a5,zero,.L20
	.loc 1 143 9 is_stmt 1
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL22:
	.loc 1 144 9
.L21:
	.loc 1 144 16 is_stmt 0
	li	a0,-2
	j	.L19
.L20:
	.loc 1 146 5 is_stmt 1
	.loc 1 146 73 is_stmt 0
	sw	s0,516(s1)
	.loc 1 147 5 is_stmt 1
	lw	a0,4(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL23:
	.loc 1 148 5
	.loc 1 148 68 is_stmt 0
	lw	a5,4(s1)
	.loc 1 148 120 discriminator 1
	li	a0,0
	.loc 1 148 72
	and	s0,s0,a5
	.loc 1 148 120
	bne	s0,zero,.L21
.L19:
	.loc 1 149 1
	lw	ra,16(sp)
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
.LVL24:
	jr	ra
	.cfi_endproc
.LFE9:
	.size	hw_semaphore_give, .-hw_semaphore_give
	.section	.text.hal_hw_semaphore_give,"ax",@progbits
	.align	1
	.globl	hal_hw_semaphore_give
	.hidden	hal_hw_semaphore_give
	.type	hal_hw_semaphore_give, @function
hal_hw_semaphore_give:
.LFB5:
	.loc 1 86 1 is_stmt 1
	.cfi_startproc
.LVL25:
	.loc 1 87 5
	.loc 1 88 5
	.loc 1 88 8 is_stmt 0
	li	a5,31
	bgtu	a0,a5,.L27
	.loc 1 91 5 is_stmt 1
	.loc 1 91 16 is_stmt 0
	tail	hw_semaphore_give
.LVL26:
.L27:
	.loc 1 94 1
	li	a0,-3
.LVL27:
	ret
	.cfi_endproc
.LFE5:
	.size	hal_hw_semaphore_give, .-hal_hw_semaphore_give
	.section	.text.hw_semaphore_give_special,"ax",@progbits
	.align	1
	.globl	hw_semaphore_give_special
	.hidden	hw_semaphore_give_special
	.type	hw_semaphore_give_special, @function
hw_semaphore_give_special:
.LFB10:
	.loc 1 152 1 is_stmt 1
	.cfi_startproc
.LVL28:
	.loc 1 153 5
	.loc 1 153 64 is_stmt 0
	li	a4,1110048768
	lw	a3,4(a4)
	.loc 1 153 73
	li	a5,1
	sll	a0,a5,a0
.LVL29:
	.loc 1 153 68
	and	a3,a3,a0
	.loc 1 153 8
	bne	a3,zero,.L29
.L31:
	.loc 1 154 16
	li	a0,-2
	ret
.L29:
	.loc 1 156 5 is_stmt 1
	.loc 1 156 73 is_stmt 0
	sw	a0,516(a4)
	.loc 1 157 5 is_stmt 1
	.loc 1 157 68 is_stmt 0
	lw	a5,4(a4)
	.loc 1 157 72
	and	a0,a0,a5
	.loc 1 157 120
	bne	a0,zero,.L31
	.loc 1 158 1
	ret
	.cfi_endproc
.LFE10:
	.size	hw_semaphore_give_special, .-hw_semaphore_give_special
	.text
.Letext0:
	.file 2 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_smph.h"
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_hw_semaphore.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x4d5
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x16
	.4byte	.LASF79
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL9
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
	.byte	0x2
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x6
	.4byte	.LASF14
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x74
	.uleb128 0x7
	.4byte	0x5e
	.uleb128 0x8
	.4byte	0x6a
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x17
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0xf
	.2byte	0x100
	.byte	0x28
	.4byte	0xaf
	.uleb128 0x3
	.4byte	.LASF11
	.byte	0x29
	.byte	0x17
	.4byte	0x6a
	.byte	0
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x2a
	.byte	0x17
	.4byte	0x6a
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x2b
	.byte	0x1d
	.4byte	0xc4
	.byte	0x8
	.byte	0
	.uleb128 0x9
	.4byte	0x6f
	.4byte	0xbf
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3d
	.byte	0
	.uleb128 0x8
	.4byte	0xaf
	.uleb128 0x7
	.4byte	0xbf
	.uleb128 0x6
	.4byte	.LASF15
	.byte	0x2
	.byte	0x2c
	.byte	0x3
	.4byte	0x82
	.uleb128 0xf
	.2byte	0x400
	.byte	0x2e
	.4byte	0x11c
	.uleb128 0x3
	.4byte	.LASF16
	.byte	0x2f
	.byte	0x1d
	.4byte	0x131
	.byte	0
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x30
	.byte	0x1d
	.4byte	0x14b
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF17
	.byte	0x31
	.byte	0x1d
	.4byte	0x6f
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF18
	.byte	0x32
	.byte	0x1d
	.4byte	0x165
	.byte	0x14
	.uleb128 0x18
	.4byte	.LASF19
	.byte	0x2
	.byte	0x33
	.byte	0x14
	.4byte	0x16a
	.2byte	0x100
	.byte	0
	.uleb128 0x9
	.4byte	0x6f
	.4byte	0x12c
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0x11c
	.uleb128 0x7
	.4byte	0x12c
	.uleb128 0x9
	.4byte	0x6f
	.4byte	0x146
	.uleb128 0xa
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x136
	.uleb128 0x7
	.4byte	0x146
	.uleb128 0x9
	.4byte	0x6f
	.4byte	0x160
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3a
	.byte	0
	.uleb128 0x8
	.4byte	0x150
	.uleb128 0x7
	.4byte	0x160
	.uleb128 0x9
	.4byte	0xc9
	.4byte	0x17a
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x6
	.4byte	.LASF20
	.byte	0x2
	.byte	0x34
	.byte	0x3
	.4byte	0xd5
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xa3
	.4byte	0x1b0
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0xff
	.byte	0
	.uleb128 0x6
	.4byte	.LASF26
	.byte	0x4
	.byte	0xab
	.byte	0x3
	.4byte	0x186
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xb6
	.4byte	0x28e
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x20
	.byte	0
	.uleb128 0x6
	.4byte	.LASF60
	.byte	0x4
	.byte	0xfa
	.byte	0x3
	.4byte	0x1bc
	.uleb128 0xd
	.byte	0x5
	.4byte	0x7b
	.byte	0xfe
	.4byte	0x2be
	.uleb128 0xe
	.4byte	.LASF61
	.sleb128 -3
	.uleb128 0xe
	.4byte	.LASF62
	.sleb128 -2
	.uleb128 0xe
	.4byte	.LASF63
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0
	.byte	0
	.uleb128 0x19
	.4byte	.LASF65
	.byte	0x4
	.2byte	0x103
	.byte	0x3
	.4byte	0x29a
	.uleb128 0x2
	.byte	0x10
	.byte	0x4
	.4byte	.LASF66
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF67
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF68
	.uleb128 0x10
	.4byte	.LASF69
	.byte	0x3f
	.4byte	0x2f0
	.uleb128 0x11
	.4byte	0x5e
	.byte	0
	.uleb128 0x10
	.4byte	.LASF70
	.byte	0x3e
	.4byte	0x300
	.uleb128 0x11
	.4byte	0x300
	.byte	0
	.uleb128 0x1a
	.byte	0x4
	.4byte	0x5e
	.uleb128 0x5
	.4byte	.LASF71
	.byte	0x97
	.byte	0x1c
	.4byte	0x2be
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x32e
	.uleb128 0x4
	.string	"id"
	.byte	0x97
	.byte	0x4c
	.4byte	0x28e
	.4byte	.LLST8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF72
	.byte	0x8a
	.byte	0x1c
	.4byte	0x2be
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x389
	.uleb128 0x4
	.string	"id"
	.byte	0x8a
	.byte	0x44
	.4byte	0x28e
	.4byte	.LLST6
	.uleb128 0x12
	.4byte	.LASF75
	.byte	0x8c
	.4byte	0x5e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x13
	.4byte	.LVL21
	.4byte	0x2f0
	.4byte	0x376
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xc
	.4byte	.LVL22
	.4byte	0x2e0
	.uleb128 0xc
	.4byte	.LVL23
	.4byte	0x2e0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF73
	.byte	0x81
	.byte	0x1c
	.4byte	0x2be
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x3b1
	.uleb128 0x4
	.string	"id"
	.byte	0x81
	.byte	0x4c
	.4byte	0x28e
	.4byte	.LLST5
	.byte	0
	.uleb128 0x5
	.4byte	.LASF74
	.byte	0x73
	.byte	0x1c
	.4byte	0x2be
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x40c
	.uleb128 0x4
	.string	"id"
	.byte	0x73
	.byte	0x44
	.4byte	0x28e
	.4byte	.LLST3
	.uleb128 0x12
	.4byte	.LASF75
	.byte	0x75
	.4byte	0x5e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x13
	.4byte	.LVL9
	.4byte	0x2f0
	.4byte	0x3f9
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xc
	.4byte	.LVL10
	.4byte	0x2e0
	.uleb128 0xc
	.4byte	.LVL13
	.4byte	0x2e0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF76
	.byte	0x60
	.byte	0x1d
	.4byte	0x1b0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x449
	.uleb128 0x4
	.string	"id"
	.byte	0x60
	.byte	0x52
	.4byte	0x28e
	.4byte	.LLST0
	.uleb128 0x1b
	.4byte	.LLRL1
	.uleb128 0x1c
	.string	"ch"
	.byte	0x1
	.byte	0x69
	.byte	0x24
	.4byte	0x1b0
	.4byte	.LLST2
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF77
	.byte	0x55
	.byte	0x1c
	.4byte	0x2be
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x492
	.uleb128 0x4
	.string	"id"
	.byte	0x55
	.byte	0x48
	.4byte	0x28e
	.4byte	.LLST7
	.uleb128 0x14
	.4byte	.LASF78
	.byte	0x57
	.4byte	0x2be
	.uleb128 0x15
	.4byte	.LVL26
	.4byte	0x32e
	.uleb128 0xb
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
	.uleb128 0x1d
	.4byte	.LASF80
	.byte	0x1
	.byte	0x41
	.byte	0x1c
	.4byte	0x2be
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x4
	.string	"id"
	.byte	0x41
	.byte	0x48
	.4byte	0x28e
	.4byte	.LLST4
	.uleb128 0x14
	.4byte	.LASF78
	.byte	0x4d
	.4byte	0x2be
	.uleb128 0x15
	.4byte	.LVL15
	.4byte	0x3b1
	.uleb128 0xb
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
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
	.uleb128 0x4
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
	.uleb128 0x7
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x26
	.byte	0
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x21
	.sleb128 5
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
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
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
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x21
	.sleb128 31
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1c
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
	.byte	0
	.section	.debug_loclists,"",@progbits
	.4byte	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.Ldebug_loc0:
.LLST8:
	.byte	0x6
	.4byte	.LVL28
	.byte	0x4
	.uleb128 .LVL28-.LVL28
	.uleb128 .LVL29-.LVL28
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL29-.LVL28
	.uleb128 .LFE10-.LVL28
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
	.4byte	.LVL19
	.byte	0x4
	.uleb128 .LVL19-.LVL19
	.uleb128 .LVL20-.LVL19
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL20-.LVL19
	.uleb128 .LVL24-.LVL19
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL24-.LVL19
	.uleb128 .LFE9-.LVL19
	.uleb128 0x2
	.byte	0x72
	.sleb128 -20
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL17
	.byte	0x4
	.uleb128 .LVL17-.LVL17
	.uleb128 .LVL18-.LVL17
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL18-.LVL17
	.uleb128 .LFE8-.LVL17
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
	.4byte	.LVL7
	.byte	0x4
	.uleb128 .LVL7-.LVL7
	.uleb128 .LVL8-.LVL7
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL8-.LVL7
	.uleb128 .LVL11-.LVL7
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL11-.LVL7
	.uleb128 .LVL12-.LVL7
	.uleb128 0x2
	.byte	0x72
	.sleb128 -20
	.byte	0x4
	.uleb128 .LVL12-.LVL7
	.uleb128 .LFE7-.LVL7
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
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
	.uleb128 .LVL5-.LVL0
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
	.uleb128 .LVL5-.LVL0
	.uleb128 .LVL6-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL6-.LVL0
	.uleb128 .LFE6-.LVL0
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
.LLST2:
	.byte	0x6
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL3-.LVL2
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.LVL2
	.uleb128 .LVL4-.LVL2
	.uleb128 0x2
	.byte	0x31
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL4-.LVL2
	.uleb128 .LVL5-.LVL2
	.uleb128 0x2
	.byte	0x32
	.byte	0x9f
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL25
	.byte	0x4
	.uleb128 .LVL25-.LVL25
	.uleb128 .LVL26-1-.LVL25
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL26-1-.LVL25
	.uleb128 .LVL26-.LVL25
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
	.uleb128 .LVL26-.LVL25
	.uleb128 .LVL27-.LVL25
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL27-.LVL25
	.uleb128 .LFE5-.LVL25
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
	.4byte	.LVL14
	.byte	0x4
	.uleb128 .LVL14-.LVL14
	.uleb128 .LVL15-1-.LVL14
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL15-1-.LVL14
	.uleb128 .LVL15-.LVL14
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
	.uleb128 .LVL15-.LVL14
	.uleb128 .LVL16-.LVL14
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL16-.LVL14
	.uleb128 .LFE4-.LVL14
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
	.4byte	0x4c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
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
	.4byte	.LBB2
	.byte	0x4
	.uleb128 .LBB2-.LBB2
	.uleb128 .LBE2-.LBB2
	.byte	0x4
	.uleb128 .LBB3-.LBB2
	.uleb128 .LBE3-.LBB2
	.byte	0
.LLRL9:
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
	.byte	0x7
	.4byte	.LFB7
	.uleb128 .LFE7-.LFB7
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
	.byte	0x7
	.4byte	.LFB8
	.uleb128 .LFE8-.LFB8
	.byte	0x7
	.4byte	.LFB9
	.uleb128 .LFE9-.LFB9
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
	.byte	0x7
	.4byte	.LFB10
	.uleb128 .LFE10-.LFB10
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF53:
	.string	"HAL_HW_SEMAPHORE_ID_26"
.LASF37:
	.string	"HAL_HW_SEMAPHORE_ID_10"
.LASF38:
	.string	"HAL_HW_SEMAPHORE_ID_11"
.LASF15:
	.string	"SMPH_CH_T"
.LASF40:
	.string	"HAL_HW_SEMAPHORE_ID_13"
.LASF41:
	.string	"HAL_HW_SEMAPHORE_ID_14"
.LASF42:
	.string	"HAL_HW_SEMAPHORE_ID_15"
.LASF43:
	.string	"HAL_HW_SEMAPHORE_ID_16"
.LASF44:
	.string	"HAL_HW_SEMAPHORE_ID_17"
.LASF45:
	.string	"HAL_HW_SEMAPHORE_ID_18"
.LASF46:
	.string	"HAL_HW_SEMAPHORE_ID_19"
.LASF27:
	.string	"HAL_HW_SEMAPHORE_ID_0"
.LASF28:
	.string	"HAL_HW_SEMAPHORE_ID_1"
.LASF29:
	.string	"HAL_HW_SEMAPHORE_ID_2"
.LASF64:
	.string	"HAL_HW_SEMAPHORE_STATUS_OK"
.LASF31:
	.string	"HAL_HW_SEMAPHORE_ID_4"
.LASF32:
	.string	"HAL_HW_SEMAPHORE_ID_5"
.LASF33:
	.string	"HAL_HW_SEMAPHORE_ID_6"
.LASF34:
	.string	"HAL_HW_SEMAPHORE_ID_7"
.LASF35:
	.string	"HAL_HW_SEMAPHORE_ID_8"
.LASF36:
	.string	"HAL_HW_SEMAPHORE_ID_9"
.LASF5:
	.string	"short int"
.LASF61:
	.string	"HAL_HW_SEMAPHORE_STATUS_INVALID_PARAMETER"
.LASF26:
	.string	"hal_hw_semaphore_channel_t"
.LASF59:
	.string	"HAL_HW_SEMAPHORE_ID_MAX"
.LASF65:
	.string	"hal_hw_semaphore_status_t"
.LASF16:
	.string	"ch_status"
.LASF47:
	.string	"HAL_HW_SEMAPHORE_ID_20"
.LASF48:
	.string	"HAL_HW_SEMAPHORE_ID_21"
.LASF49:
	.string	"HAL_HW_SEMAPHORE_ID_22"
.LASF30:
	.string	"HAL_HW_SEMAPHORE_ID_3"
.LASF51:
	.string	"HAL_HW_SEMAPHORE_ID_24"
.LASF52:
	.string	"HAL_HW_SEMAPHORE_ID_25"
.LASF80:
	.string	"hal_hw_semaphore_take"
.LASF54:
	.string	"HAL_HW_SEMAPHORE_ID_27"
.LASF55:
	.string	"HAL_HW_SEMAPHORE_ID_28"
.LASF56:
	.string	"HAL_HW_SEMAPHORE_ID_29"
.LASF7:
	.string	"long long int"
.LASF74:
	.string	"hw_semaphore_take"
.LASF67:
	.string	"char"
.LASF21:
	.string	"HAL_HW_SEMAPHORE_CHANNEL_MCU"
.LASF6:
	.string	"long int"
.LASF57:
	.string	"HAL_HW_SEMAPHORE_ID_30"
.LASF17:
	.string	"global_status"
.LASF22:
	.string	"HAL_HW_SEMAPHORE_CHANNEL_RISCV"
.LASF78:
	.string	"g_status"
.LASF39:
	.string	"HAL_HW_SEMAPHORE_ID_12"
.LASF12:
	.string	"ch_release"
.LASF66:
	.string	"long double"
.LASF79:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF8:
	.string	"unsigned char"
.LASF69:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF13:
	.string	"__reserved_00"
.LASF18:
	.string	"__reserved_01"
.LASF2:
	.string	"long long unsigned int"
.LASF14:
	.string	"uint32_t"
.LASF58:
	.string	"HAL_HW_SEMAPHORE_ID_31"
.LASF70:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF3:
	.string	"unsigned int"
.LASF25:
	.string	"HAL_HW_SEMAPHORE_CHANNEL_NOT_EXIST"
.LASF75:
	.string	"int_mask"
.LASF9:
	.string	"short unsigned int"
.LASF4:
	.string	"signed char"
.LASF23:
	.string	"HAL_HW_SEMAPHORE_CHANNEL_HWMAC"
.LASF19:
	.string	"channels"
.LASF68:
	.string	"_Bool"
.LASF71:
	.string	"hw_semaphore_give_special"
.LASF10:
	.string	"long unsigned int"
.LASF62:
	.string	"HAL_HW_SEMAPHORE_STATUS_GIVE_ERROR"
.LASF20:
	.string	"SMPH_REGISTER_T"
.LASF11:
	.string	"ch_lock"
.LASF24:
	.string	"HAL_HW_SEMAPHORE_CHANNEL_MAX"
.LASF73:
	.string	"hw_semaphore_take_special"
.LASF76:
	.string	"hal_hw_semaphore_query_channel"
.LASF63:
	.string	"HAL_HW_SEMAPHORE_STATUS_TAKE_ERROR"
.LASF77:
	.string	"hal_hw_semaphore_give"
.LASF60:
	.string	"hal_hw_semaphore_id_t"
.LASF50:
	.string	"HAL_HW_SEMAPHORE_ID_23"
.LASF72:
	.string	"hw_semaphore_give"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/drivers/chip/ab162x/src/hal_hw_semaphore.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
