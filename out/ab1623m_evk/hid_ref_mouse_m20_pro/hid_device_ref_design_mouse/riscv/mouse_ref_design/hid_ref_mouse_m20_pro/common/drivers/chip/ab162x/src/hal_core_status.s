	.file	"hal_core_status.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/drivers/chip/ab162x/src/hal_core_status.c"
	.section	.tcm_code."/workdir/airoha/common/drivers/chip/ab162x/src/hal_core_status.c".64,"ax",@progbits
	.align	1
	.globl	hal_core_status_read
	.hidden	hal_core_status_read
	.type	hal_core_status_read, @function
hal_core_status_read:
.LFB15:
	.file 1 "/workdir/airoha/common/drivers/chip/ab162x/src/hal_core_status.c"
	.loc 1 65 1
	.cfi_startproc
.LVL0:
	.loc 1 66 5
	.loc 1 66 8 is_stmt 0
	li	a5,1
	bgtu	a0,a5,.L3
	.loc 1 69 9 is_stmt 1
	.loc 1 69 16 is_stmt 0
	lla	a5,ccm_core_status
	slli	a0,a0,2
.LVL1:
	add	a0,a0,a5
	lw	a0,0(a0)
	ret
.LVL2:
.L3:
	.loc 1 67 16
	li	a0,-1
.LVL3:
	.loc 1 71 1
	ret
	.cfi_endproc
.LFE15:
	.size	hal_core_status_read, .-hal_core_status_read
	.section	.text.hal_core_status_write,"ax",@progbits
	.align	1
	.globl	hal_core_status_write
	.hidden	hal_core_status_write
	.type	hal_core_status_write, @function
hal_core_status_write:
.LFB16:
	.loc 1 75 1 is_stmt 1
	.cfi_startproc
.LVL4:
	.loc 1 76 5
	.loc 1 75 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s1,0(sp)
	sw	ra,8(sp)
	sw	s0,4(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 76 8
	li	a5,1
	.loc 1 77 16
	li	s1,-1
	.loc 1 76 8
	bgtu	a0,a5,.L5
	mv	s0,a0
	mv	s1,a1
	.loc 1 85 5 is_stmt 1
	.loc 1 85 8 is_stmt 0
	beq	a0,a5,.L6
	.loc 1 86 9 is_stmt 1
.LBB2:
	.loc 1 86 14
	.loc 1 86 67
	.loc 1 86 217
	mv	a5,a1
	li	a4,0
	li	a3,2
	lla	a2,msg_id_string.0
	li	a1,2
.LVL5:
	lla	a0,log_control_block_common
.LVL6:
	call	print_module_msgid_log
.LVL7:
.L6:
.LBE2:
	.loc 1 86 12 discriminator 1
	.loc 1 92 5
	.loc 1 92 51 is_stmt 0
	slli	s0,s0,2
.LVL8:
	lla	a5,ccm_core_status
	add	s0,s0,a5
	sw	s1,0(s0)
	.loc 1 93 5 is_stmt 1
.LVL9:
.L5:
	.loc 1 95 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	mv	a0,s1
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE16:
	.size	hal_core_status_write, .-hal_core_status_write
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 57
msg_id_string.0:
	.string	"[M:common C:info F: L: ]: cross core operation: %d => %d"
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_core_status.h"
	.file 4 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 5 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_cross_core_config.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x412
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x12
	.4byte	.LASF65
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL3
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x4
	.4byte	.LASF10
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x61
	.uleb128 0xb
	.4byte	0x50
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF8
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x4
	.4byte	.LASF11
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x7b
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF12
	.uleb128 0x13
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x8
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.byte	0x2d
	.4byte	0xb1
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0x2
	.uleb128 0xc
	.4byte	.LASF16
	.4byte	0xffffffff
	.byte	0
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x3
	.byte	0x32
	.byte	0x3
	.4byte	0x89
	.uleb128 0x8
	.byte	0x5
	.4byte	0x82
	.byte	0x3
	.byte	0x35
	.4byte	0xf7
	.uleb128 0x14
	.4byte	.LASF18
	.sleb128 -1
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
	.uleb128 0xc
	.4byte	.LASF24
	.4byte	0x7fffffff
	.byte	0
	.uleb128 0x4
	.4byte	.LASF25
	.byte	0x3
	.byte	0x3d
	.byte	0x3
	.4byte	0xbd
	.uleb128 0x3
	.byte	0x10
	.byte	0x4
	.4byte	.LASF26
	.uleb128 0x15
	.byte	0x4
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF27
	.uleb128 0xd
	.4byte	0x10c
	.uleb128 0x5
	.4byte	0x113
	.uleb128 0x8
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x3d
	.4byte	0x142
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF32
	.byte	0x4
	.byte	0x42
	.byte	0x3
	.4byte	0x11d
	.uleb128 0x8
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x45
	.4byte	0x1b5
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF48
	.byte	0x4
	.byte	0x57
	.byte	0x3
	.4byte	0x14e
	.uleb128 0x4
	.4byte	.LASF49
	.byte	0x4
	.byte	0x59
	.byte	0x10
	.4byte	0x1cd
	.uleb128 0x5
	.4byte	0x1d2
	.uleb128 0xa
	.4byte	0x1f2
	.uleb128 0x2
	.4byte	0x10a
	.uleb128 0x2
	.4byte	0x118
	.uleb128 0x2
	.4byte	0x82
	.uleb128 0x2
	.4byte	0x142
	.uleb128 0x2
	.4byte	0x118
	.uleb128 0x9
	.byte	0
	.uleb128 0x4
	.4byte	.LASF50
	.byte	0x4
	.byte	0x5a
	.byte	0x10
	.4byte	0x1fe
	.uleb128 0x5
	.4byte	0x203
	.uleb128 0xa
	.4byte	0x22d
	.uleb128 0x2
	.4byte	0x10a
	.uleb128 0x2
	.4byte	0x118
	.uleb128 0x2
	.4byte	0x82
	.uleb128 0x2
	.4byte	0x142
	.uleb128 0x2
	.4byte	0x22d
	.uleb128 0x2
	.4byte	0x82
	.uleb128 0x2
	.4byte	0x118
	.uleb128 0x9
	.byte	0
	.uleb128 0x5
	.4byte	0x232
	.uleb128 0x16
	.uleb128 0x4
	.4byte	.LASF51
	.byte	0x4
	.byte	0x5b
	.byte	0x10
	.4byte	0x23f
	.uleb128 0x5
	.4byte	0x244
	.uleb128 0xa
	.4byte	0x25f
	.uleb128 0x2
	.4byte	0x10a
	.uleb128 0x2
	.4byte	0x142
	.uleb128 0x2
	.4byte	0x118
	.uleb128 0x2
	.4byte	0x6f
	.uleb128 0x9
	.byte	0
	.uleb128 0x4
	.4byte	.LASF52
	.byte	0x4
	.byte	0x5c
	.byte	0x14
	.4byte	0x26b
	.uleb128 0x5
	.4byte	0x270
	.uleb128 0x17
	.4byte	0x6f
	.4byte	0x293
	.uleb128 0x2
	.4byte	0x10a
	.uleb128 0x2
	.4byte	0x142
	.uleb128 0x2
	.4byte	0x1b5
	.uleb128 0x2
	.4byte	0x293
	.uleb128 0x2
	.4byte	0x298
	.byte	0
	.uleb128 0x5
	.4byte	0x22d
	.uleb128 0x5
	.4byte	0x6f
	.uleb128 0x18
	.byte	0x1c
	.byte	0x4
	.byte	0x5e
	.byte	0x9
	.4byte	0x2fb
	.uleb128 0x6
	.4byte	.LASF53
	.byte	0x5f
	.byte	0x11
	.4byte	0x118
	.byte	0
	.uleb128 0x6
	.4byte	.LASF54
	.byte	0x60
	.byte	0xe
	.4byte	0x6f
	.byte	0x4
	.uleb128 0x6
	.4byte	.LASF55
	.byte	0x61
	.byte	0xe
	.4byte	0x6f
	.byte	0x8
	.uleb128 0x6
	.4byte	.LASF56
	.byte	0x62
	.byte	0xf
	.4byte	0x1c1
	.byte	0xc
	.uleb128 0x6
	.4byte	.LASF57
	.byte	0x63
	.byte	0x15
	.4byte	0x1f2
	.byte	0x10
	.uleb128 0x6
	.4byte	.LASF58
	.byte	0x64
	.byte	0x12
	.4byte	0x25f
	.byte	0x14
	.uleb128 0x6
	.4byte	.LASF59
	.byte	0x65
	.byte	0x10
	.4byte	0x233
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF60
	.byte	0x4
	.byte	0x66
	.byte	0x3
	.4byte	0x29d
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF61
	.uleb128 0xe
	.4byte	0x5c
	.4byte	0x31e
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0xb
	.4byte	0x30e
	.uleb128 0x10
	.4byte	.LASF63
	.byte	0x5
	.byte	0x85
	.byte	0x19
	.4byte	0x31e
	.uleb128 0x19
	.4byte	.LASF66
	.byte	0x4
	.2byte	0x129
	.byte	0xd
	.4byte	0x352
	.uleb128 0x2
	.4byte	0x10a
	.uleb128 0x2
	.4byte	0x142
	.uleb128 0x2
	.4byte	0x118
	.uleb128 0x2
	.4byte	0x6f
	.uleb128 0x9
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF67
	.byte	0x1
	.byte	0x4a
	.byte	0x13
	.4byte	0xf7
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x3db
	.uleb128 0x11
	.string	"id"
	.byte	0x4a
	.byte	0x37
	.4byte	0xb1
	.4byte	.LLST1
	.uleb128 0x1b
	.4byte	.LASF62
	.byte	0x1
	.byte	0x4a
	.byte	0x4d
	.4byte	0xf7
	.4byte	.LLST2
	.uleb128 0x1c
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.uleb128 0x10
	.4byte	.LASF64
	.byte	0x1
	.byte	0x56
	.byte	0x29
	.4byte	0x2fb
	.uleb128 0x1d
	.4byte	.LASF68
	.byte	0x1
	.byte	0x56
	.byte	0x82
	.4byte	0x3eb
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x1e
	.4byte	.LVL7
	.4byte	0x32f
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x5f
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xe
	.4byte	0x113
	.4byte	0x3eb
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x38
	.byte	0
	.uleb128 0xd
	.4byte	0x3db
	.uleb128 0x1f
	.4byte	.LASF69
	.byte	0x1
	.byte	0x40
	.byte	0xa8
	.4byte	0xf7
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x11
	.string	"id"
	.byte	0x40
	.byte	0xcb
	.4byte	0xb1
	.4byte	.LLST0
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
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
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
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1d
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
.LLST1:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL6-.LVL4
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL6-.LVL4
	.uleb128 .LVL8-.LVL4
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL8-.LVL4
	.uleb128 .LFE16-.LVL4
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
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL5-.LVL4
	.uleb128 .LVL9-.LVL4
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL9-.LVL4
	.uleb128 .LFE16-.LVL4
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
	.uleb128 .LVL2-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL3-.LVL0
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
	.4byte	0x24
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
	.byte	0x7
	.4byte	.LFB15
	.uleb128 .LFE15-.LFB15
	.byte	0x7
	.4byte	.LFB16
	.uleb128 .LFE16-.LFB16
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF53:
	.string	"module_name"
.LASF59:
	.string	"msg_id_handle"
.LASF20:
	.string	"HAL_CORE_INIT"
.LASF47:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF50:
	.string	"f_dump_buffer_t"
.LASF34:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF17:
	.string	"hal_core_id_t"
.LASF31:
	.string	"PRINT_LEVEL_ERROR"
.LASF16:
	.string	"HAL_CORE_ID_NOT_EXIST"
.LASF45:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF52:
	.string	"f_tlv_dump_t"
.LASF42:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF25:
	.string	"hal_core_status_t"
.LASF14:
	.string	"HAL_CORE_RISCV"
.LASF56:
	.string	"print_handle"
.LASF44:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF5:
	.string	"short int"
.LASF38:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF69:
	.string	"hal_core_status_read"
.LASF29:
	.string	"PRINT_LEVEL_INFO"
.LASF64:
	.string	"log_control_block_common"
.LASF36:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF7:
	.string	"long long int"
.LASF63:
	.string	"ccm_core_status"
.LASF13:
	.string	"HAL_CORE_MCU"
.LASF51:
	.string	"f_msg_id_t"
.LASF57:
	.string	"dump_handle"
.LASF41:
	.string	"LOG_TYPE_HCI_DATA"
.LASF67:
	.string	"hal_core_status_write"
.LASF26:
	.string	"long double"
.LASF65:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF39:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF18:
	.string	"HAL_CORE_ERROR"
.LASF8:
	.string	"unsigned char"
.LASF4:
	.string	"signed char"
.LASF2:
	.string	"long long unsigned int"
.LASF11:
	.string	"uint32_t"
.LASF3:
	.string	"unsigned int"
.LASF32:
	.string	"print_level_t"
.LASF19:
	.string	"HAL_CORE_OFF"
.LASF33:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF55:
	.string	"print_level"
.LASF68:
	.string	"msg_id_string"
.LASF62:
	.string	"status"
.LASF9:
	.string	"short unsigned int"
.LASF58:
	.string	"tlv_dump_handle"
.LASF23:
	.string	"HAL_CORE_EXCEPTION"
.LASF27:
	.string	"char"
.LASF61:
	.string	"_Bool"
.LASF49:
	.string	"f_print_t"
.LASF22:
	.string	"HAL_CORE_SLEEP"
.LASF30:
	.string	"PRINT_LEVEL_WARNING"
.LASF40:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF60:
	.string	"log_control_block_t"
.LASF12:
	.string	"long unsigned int"
.LASF21:
	.string	"HAL_CORE_ACTIVE"
.LASF24:
	.string	"HAL_CORE_STATUS_MAX"
.LASF28:
	.string	"PRINT_LEVEL_DEBUG"
.LASF35:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF48:
	.string	"log_type_t"
.LASF10:
	.string	"uint8_t"
.LASF15:
	.string	"HAL_CORE_MAX"
.LASF37:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF46:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF6:
	.string	"long int"
.LASF43:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF66:
	.string	"print_module_msgid_log"
.LASF54:
	.string	"log_switch"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/drivers/chip/ab162x/src/hal_core_status.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
