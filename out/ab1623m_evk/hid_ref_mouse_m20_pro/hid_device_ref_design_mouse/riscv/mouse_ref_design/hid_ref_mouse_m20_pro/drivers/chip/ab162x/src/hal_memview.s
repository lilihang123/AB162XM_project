	.file	"hal_memview.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_memview.c"
	.section	.text.check_infra_address,"ax",@progbits
	.align	1
	.type	check_infra_address, @function
check_infra_address:
.LFB3:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_memview.c"
	.loc 1 64 1
	.cfi_startproc
.LVL0:
	.loc 1 65 5
	.loc 1 65 7 is_stmt 0
	li	a4,-67108864
	add	a4,a0,a4
	li	a3,409600
	.loc 1 64 1
	mv	a5,a0
	.loc 1 65 7
	bltu	a4,a3,.L3
	.loc 1 66 34
	li	a4,-134217728
	add	a4,a0,a4
	.loc 1 66 9
	li	a3,1048576
	.loc 1 70 16
	li	a0,0
.LVL1:
	.loc 1 66 9
	bltu	a4,a3,.L1
	.loc 1 68 34
	li	a4,2079965184
	.loc 1 68 9
	li	a0,24576
	.loc 1 68 34
	add	a5,a5,a4
.LVL2:
	.loc 1 68 9
	addi	a0,a0,-1
	sgtu	a0,a5,a0
	ret
.LVL3:
.L3:
	.loc 1 70 16
	li	a0,0
.LVL4:
.L1:
	.loc 1 73 1
	ret
	.cfi_endproc
.LFE3:
	.size	check_infra_address, .-check_infra_address
	.section	.text.hal_memview_riscv_to_infrasys,"ax",@progbits
	.align	1
	.globl	hal_memview_riscv_to_infrasys
	.hidden	hal_memview_riscv_to_infrasys
	.type	hal_memview_riscv_to_infrasys, @function
hal_memview_riscv_to_infrasys:
.LFB5:
	.loc 1 104 1 is_stmt 1
	.cfi_startproc
.LVL5:
	.loc 1 105 5
	.loc 1 106 5
	.loc 1 107 5
	.loc 1 107 47 discriminator 1
	.loc 1 108 5
.LBB5:
.LBB6:
	.loc 1 94 5
.LBE6:
.LBE5:
	.loc 1 104 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
.LBB10:
.LBB7:
	.loc 1 95 31
	li	a5,-67108864
.LBE7:
.LBE10:
	.loc 1 104 1
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
.LBB11:
.LBB8:
	.loc 1 95 31
	add	a5,a0,a5
	.loc 1 94 8
	li	a4,393216
.LBE8:
.LBE11:
	.loc 1 104 1
	mv	s0,a0
.LBB12:
.LBB9:
	.loc 1 94 8
	bltu	a5,a4,.L6
	.loc 1 96 31
	li	a5,-134217728
	add	a5,a0,a5
	.loc 1 95 55
	li	a4,1048576
	bltu	a5,a4,.L6
.LVL6:
.LBE9:
.LBE12:
	.loc 1 111 5 is_stmt 1
.LBB13:
	.loc 1 112 7
	.loc 1 112 22 is_stmt 0
	call	check_infra_address
.LVL7:
	.loc 1 112 61 is_stmt 1 discriminator 1
	.loc 1 112 63 is_stmt 0 discriminator 1
	beq	a0,zero,.L6
	.loc 1 112 75 is_stmt 1 discriminator 1
	li	a0,0
.LVL8:
	call	air_assert
.LVL9:
.L6:
.LBE13:
	.loc 1 114 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	mv	a0,s0
	lw	s0,4(sp)
	.cfi_restore 8
.LVL10:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE5:
	.size	hal_memview_riscv_to_infrasys, .-hal_memview_riscv_to_infrasys
	.section	.text.hal_memview_infrasys_to_riscv,"ax",@progbits
	.align	1
	.globl	hal_memview_infrasys_to_riscv
	.hidden	hal_memview_infrasys_to_riscv
	.type	hal_memview_infrasys_to_riscv, @function
hal_memview_infrasys_to_riscv:
.LFB6:
	.loc 1 119 1 is_stmt 1
	.cfi_startproc
.LVL11:
	.loc 1 120 5
	.loc 1 121 5
	.loc 1 122 5
	.loc 1 122 47 discriminator 1
.LBB14:
	.loc 1 124 7
.LBE14:
	.loc 1 119 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 119 1
	mv	s0,a0
.LBB15:
	.loc 1 124 22
	call	check_infra_address
.LVL12:
	.loc 1 124 61 is_stmt 1 discriminator 1
	.loc 1 124 63 is_stmt 0 discriminator 1
	beq	a0,zero,.L12
	.loc 1 124 75 is_stmt 1 discriminator 1
	li	a0,0
.LVL13:
	call	air_assert
.LVL14:
.L12:
.LBE15:
	.loc 1 124 9 discriminator 3
	.loc 1 125 5
	.loc 1 127 5
	.loc 1 128 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	mv	a0,s0
	lw	s0,4(sp)
	.cfi_restore 8
.LVL15:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE6:
	.size	hal_memview_infrasys_to_riscv, .-hal_memview_infrasys_to_riscv
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/kernel/service/exception_handler/inc/exception_handler.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1e7
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0xa
	.4byte	.LASF18
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL10
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x1
	.byte	0x1
	.byte	0x6
	.4byte	.LASF2
	.uleb128 0x1
	.byte	0x2
	.byte	0x5
	.4byte	.LASF3
	.uleb128 0x1
	.byte	0x4
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x1
	.byte	0x8
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.4byte	.LASF6
	.uleb128 0x1
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0xb
	.4byte	.LASF19
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x5c
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x1
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0xc
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x1
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xd
	.4byte	.LASF20
	.byte	0x3
	.byte	0x43
	.byte	0xd
	.4byte	0x98
	.uleb128 0xe
	.4byte	0x6a
	.byte	0
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x76
	.4byte	0x50
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10e
	.uleb128 0x3
	.4byte	.LASF16
	.byte	0x76
	.byte	0x31
	.4byte	0x50
	.4byte	.LLST6
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x78
	.4byte	0x50
	.4byte	.LLST7
	.uleb128 0x6
	.string	"lr"
	.byte	0x79
	.4byte	0x50
	.uleb128 0xf
	.4byte	.LLRL8
	.uleb128 0x7
	.string	"res"
	.byte	0x7c
	.4byte	0x50
	.4byte	.LLST9
	.uleb128 0x8
	.4byte	.LVL12
	.4byte	0x1c4
	.4byte	0xfd
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x9
	.4byte	.LVL14
	.4byte	0x86
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x67
	.4byte	0x50
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1a6
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x67
	.byte	0x31
	.4byte	0x50
	.4byte	.LLST1
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x69
	.4byte	0x50
	.4byte	.LLST2
	.uleb128 0x6
	.string	"lr"
	.byte	0x6a
	.4byte	0x50
	.uleb128 0x10
	.4byte	.LBB13
	.4byte	.LBE13-.LBB13
	.4byte	0x18b
	.uleb128 0x7
	.string	"res"
	.byte	0x70
	.4byte	0x50
	.4byte	.LLST5
	.uleb128 0x8
	.4byte	.LVL7
	.4byte	0x1c4
	.4byte	0x17b
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x9
	.4byte	.LVL9
	.4byte	0x86
	.uleb128 0x2
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	0x1a6
	.4byte	.LBB5
	.4byte	.LLRL3
	.byte	0x1
	.byte	0x6c
	.byte	0x9
	.uleb128 0x12
	.4byte	0x1b7
	.4byte	.LLST4
	.byte	0
	.byte	0
	.uleb128 0x13
	.4byte	.LASF21
	.byte	0x1
	.byte	0x5c
	.byte	0x11
	.4byte	0x50
	.byte	0x1
	.4byte	0x1c4
	.uleb128 0x14
	.4byte	.LASF17
	.byte	0x1
	.byte	0x5c
	.byte	0x2e
	.4byte	0x50
	.byte	0
	.uleb128 0x15
	.4byte	.LASF22
	.byte	0x1
	.byte	0x3f
	.byte	0x11
	.4byte	0x50
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x3
	.4byte	.LASF17
	.byte	0x3f
	.byte	0x2e
	.4byte	0x50
	.4byte	.LLST0
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
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
	.sleb128 10
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
	.uleb128 0x5
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
	.uleb128 0x6
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
	.sleb128 14
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.sleb128 16
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
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
.LLST6:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL12-1-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL12-1-.LVL11
	.uleb128 .LVL15-.LVL11
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL15-.LVL11
	.uleb128 .LFE6-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL14-.LVL11
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL14-.LVL11
	.uleb128 .LVL15-.LVL11
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL15-.LVL11
	.uleb128 .LFE6-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST9:
	.byte	0x8
	.4byte	.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL7-1-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL7-1-.LVL5
	.uleb128 .LVL10-.LVL5
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL10-.LVL5
	.uleb128 .LFE5-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL6-.LVL5
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL6-.LVL5
	.uleb128 .LVL7-1-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL7-1-.LVL5
	.uleb128 .LVL9-.LVL5
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST5:
	.byte	0x8
	.4byte	.LVL7
	.uleb128 .LVL8-.LVL7
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST4:
	.byte	0x8
	.4byte	.LVL5
	.uleb128 .LVL6-.LVL5
	.uleb128 0x1
	.byte	0x5a
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
	.uleb128 .LVL2-.LVL0
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL2-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x7
	.byte	0x7f
	.sleb128 -2079965184
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL4-.LVL0
	.uleb128 .LFE3-.LVL0
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
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
	.4byte	.LBB5
	.byte	0x4
	.uleb128 .LBB5-.LBB5
	.uleb128 .LBE5-.LBB5
	.byte	0x4
	.uleb128 .LBB10-.LBB5
	.uleb128 .LBE10-.LBB5
	.byte	0x4
	.uleb128 .LBB11-.LBB5
	.uleb128 .LBE11-.LBB5
	.byte	0x4
	.uleb128 .LBB12-.LBB5
	.uleb128 .LBE12-.LBB5
	.byte	0
.LLRL8:
	.byte	0x5
	.4byte	.LBB14
	.byte	0x4
	.uleb128 .LBB14-.LBB14
	.uleb128 .LBE14-.LBB14
	.byte	0x4
	.uleb128 .LBB15-.LBB14
	.uleb128 .LBE15-.LBB14
	.byte	0
.LLRL10:
	.byte	0x7
	.4byte	.LFB3
	.uleb128 .LFE3-.LFB3
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF5:
	.string	"long long int"
.LASF7:
	.string	"short unsigned int"
.LASF10:
	.string	"unsigned int"
.LASF16:
	.string	"infrasys_address"
.LASF6:
	.string	"unsigned char"
.LASF22:
	.string	"check_infra_address"
.LASF8:
	.string	"long unsigned int"
.LASF9:
	.string	"long long unsigned int"
.LASF17:
	.string	"addr"
.LASF14:
	.string	"hal_memview_infrasys_to_riscv"
.LASF13:
	.string	"mcu_address"
.LASF15:
	.string	"hal_memview_riscv_to_infrasys"
.LASF12:
	.string	"char"
.LASF19:
	.string	"uint32_t"
.LASF4:
	.string	"long int"
.LASF20:
	.string	"air_assert"
.LASF2:
	.string	"signed char"
.LASF11:
	.string	"long double"
.LASF3:
	.string	"short int"
.LASF18:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF21:
	.string	"allow_convert_check"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_memview.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
