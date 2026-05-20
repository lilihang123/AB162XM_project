	.file	"hal_spm.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_spm.c"
	.section	.text.spm_mask_wakeup_source,"ax",@progbits
	.align	1
	.globl	spm_mask_wakeup_source
	.hidden	spm_mask_wakeup_source
	.type	spm_mask_wakeup_source, @function
spm_mask_wakeup_source:
.LFB5:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_spm.c"
	.loc 1 69 1
	.cfi_startproc
.LVL0:
	.loc 1 70 5
	.loc 1 71 5
	.loc 1 69 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	.loc 1 71 5
	mv	a0,sp
.LVL1:
	.loc 1 69 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 71 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL2:
	.loc 1 73 5 is_stmt 1
	li	a5,1108541440
	.loc 1 73 8 is_stmt 0
	li	a4,32
	addi	a5,a5,8
	bne	s0,a4,.L2
	.loc 1 74 9 is_stmt 1
	.loc 1 74 57 is_stmt 0
	li	a4,-1
	sw	a4,0(a5)
.L3:
	.loc 1 79 5 is_stmt 1
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL3:
	.loc 1 80 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL4:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL5:
.L2:
	.cfi_restore_state
	.loc 1 76 9 is_stmt 1
	lw	a4,0(a5)
	.loc 1 76 65 is_stmt 0
	li	a0,1
	sll	a0,a0,s0
	.loc 1 76 57
	or	a0,a0,a4
	sw	a0,0(a5)
	j	.L3
	.cfi_endproc
.LFE5:
	.size	spm_mask_wakeup_source, .-spm_mask_wakeup_source
	.section	.text.spm_unmask_wakeup_source,"ax",@progbits
	.align	1
	.globl	spm_unmask_wakeup_source
	.hidden	spm_unmask_wakeup_source
	.type	spm_unmask_wakeup_source, @function
spm_unmask_wakeup_source:
.LFB6:
	.loc 1 83 1 is_stmt 1
	.cfi_startproc
.LVL6:
	.loc 1 84 5
	.loc 1 85 5
	.loc 1 83 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	.cfi_offset 8, -8
	mv	s0,a0
	.loc 1 85 5
	mv	a0,sp
.LVL7:
	.loc 1 83 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 85 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL8:
	.loc 1 87 5 is_stmt 1
	li	a4,1108541440
	.loc 1 87 8 is_stmt 0
	li	a5,32
	addi	a4,a4,8
	bne	s0,a5,.L6
	.loc 1 88 9 is_stmt 1
	.loc 1 88 57 is_stmt 0
	sw	zero,0(a4)
.L7:
	.loc 1 93 5 is_stmt 1
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL9:
	.loc 1 94 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL10:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL11:
.L6:
	.cfi_restore_state
	.loc 1 90 9 is_stmt 1
	lw	a3,0(a4)
	.loc 1 90 66 is_stmt 0
	li	a5,1
	sll	a5,a5,s0
	.loc 1 90 60
	not	a5,a5
	.loc 1 90 57
	and	a5,a5,a3
	sw	a5,0(a4)
	j	.L7
	.cfi_endproc
.LFE6:
	.size	spm_unmask_wakeup_source, .-spm_unmask_wakeup_source
	.section	.text.spm_init,"ax",@progbits
	.align	1
	.globl	spm_init
	.hidden	spm_init
	.type	spm_init, @function
spm_init:
.LFB4:
	.loc 1 53 1 is_stmt 1
	.cfi_startproc
	.loc 1 54 5
.LVL12:
	.loc 1 56 5
	.loc 1 53 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 56 5
	li	a0,32
	.loc 1 53 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 56 5
	call	spm_unmask_wakeup_source
.LVL13:
	.loc 1 57 5 is_stmt 1
	li	a0,1
	call	spm_mask_wakeup_source
.LVL14:
	.loc 1 58 5
	li	a0,3
	call	spm_mask_wakeup_source
.LVL15:
	.loc 1 59 5
	li	a0,4
	call	spm_mask_wakeup_source
.LVL16:
	.loc 1 60 5
	li	a0,11
	call	spm_mask_wakeup_source
.LVL17:
	.loc 1 61 5
	li	a0,7
	call	spm_mask_wakeup_source
.LVL18:
	.loc 1 62 5
	li	a0,6
	call	spm_mask_wakeup_source
.LVL19:
	.loc 1 63 5
.LBB2:
	.loc 1 63 10
	.loc 1 63 63
	.loc 1 63 240
	li	a4,1108541440
	lw	a5,8(a4)
	addi	a4,a4,8
	lla	a0,log_control_block_common
	li	a3,2
	lla	a2,msg_id_string.0
	li	a1,1
	call	print_module_msgid_log
.LVL20:
.LBE2:
	.loc 1 63 8 discriminator 1
	.loc 1 65 5
	.loc 1 66 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE4:
	.size	spm_init, .-spm_init
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 82
msg_id_string.0:
	.string	"[M:common C:info F: L: ]: [SLP] *SPM_CFG_IBEX_WAKEUP_SOURCE_MASK(0x%08x)=0x%08x\r\n"
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x4d5
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x13
	.4byte	.LASF72
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL2
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x4
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x4
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x4
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x4
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x14
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x15
	.byte	0x4
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xd
	.4byte	0x75
	.uleb128 0x5
	.4byte	0x7c
	.uleb128 0x6
	.4byte	.LASF17
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3
	.byte	0x3d
	.4byte	0xb6
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.4byte	.LASF18
	.byte	0x3
	.byte	0x42
	.byte	0x3
	.4byte	0x92
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3
	.byte	0x45
	.4byte	0x128
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x3f
	.byte	0
	.uleb128 0x6
	.4byte	.LASF34
	.byte	0x3
	.byte	0x57
	.byte	0x3
	.4byte	0xc2
	.uleb128 0x6
	.4byte	.LASF35
	.byte	0x3
	.byte	0x59
	.byte	0x10
	.4byte	0x140
	.uleb128 0x5
	.4byte	0x145
	.uleb128 0xb
	.4byte	0x165
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xb6
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x9
	.byte	0
	.uleb128 0x6
	.4byte	.LASF36
	.byte	0x3
	.byte	0x5a
	.byte	0x10
	.4byte	0x171
	.uleb128 0x5
	.4byte	0x176
	.uleb128 0xb
	.4byte	0x1a0
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xb6
	.uleb128 0x2
	.4byte	0x1a0
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x9
	.byte	0
	.uleb128 0x5
	.4byte	0x1a5
	.uleb128 0x16
	.uleb128 0x6
	.4byte	.LASF37
	.byte	0x3
	.byte	0x5b
	.byte	0x10
	.4byte	0x1b2
	.uleb128 0x5
	.4byte	0x1b7
	.uleb128 0xb
	.4byte	0x1d2
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xb6
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x86
	.uleb128 0x9
	.byte	0
	.uleb128 0x6
	.4byte	.LASF38
	.byte	0x3
	.byte	0x5c
	.byte	0x14
	.4byte	0x1de
	.uleb128 0x5
	.4byte	0x1e3
	.uleb128 0x17
	.4byte	0x86
	.4byte	0x206
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xb6
	.uleb128 0x2
	.4byte	0x128
	.uleb128 0x2
	.4byte	0x206
	.uleb128 0x2
	.4byte	0x20b
	.byte	0
	.uleb128 0x5
	.4byte	0x1a0
	.uleb128 0x5
	.4byte	0x86
	.uleb128 0x18
	.byte	0x1c
	.byte	0x3
	.byte	0x5e
	.byte	0x9
	.4byte	0x26e
	.uleb128 0x8
	.4byte	.LASF39
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x8
	.4byte	.LASF40
	.byte	0x60
	.byte	0xe
	.4byte	0x86
	.byte	0x4
	.uleb128 0x8
	.4byte	.LASF41
	.byte	0x61
	.byte	0xe
	.4byte	0x86
	.byte	0x8
	.uleb128 0x8
	.4byte	.LASF42
	.byte	0x62
	.byte	0xf
	.4byte	0x134
	.byte	0xc
	.uleb128 0x8
	.4byte	.LASF43
	.byte	0x63
	.byte	0x15
	.4byte	0x165
	.byte	0x10
	.uleb128 0x8
	.4byte	.LASF44
	.byte	0x64
	.byte	0x12
	.4byte	0x1d2
	.byte	0x14
	.uleb128 0x8
	.4byte	.LASF45
	.byte	0x65
	.byte	0x10
	.4byte	0x1a6
	.byte	0x18
	.byte	0
	.uleb128 0x6
	.4byte	.LASF46
	.byte	0x3
	.byte	0x66
	.byte	0x3
	.4byte	0x210
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x4
	.byte	0xd0
	.4byte	0x2e0
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x20
	.byte	0
	.uleb128 0x4
	.byte	0x1
	.byte	0x2
	.4byte	.LASF62
	.uleb128 0xe
	.4byte	.LASF63
	.byte	0x3f
	.4byte	0x2f7
	.uleb128 0x2
	.4byte	0x86
	.byte	0
	.uleb128 0xe
	.4byte	.LASF64
	.byte	0x3e
	.4byte	0x307
	.uleb128 0x2
	.4byte	0x20b
	.byte	0
	.uleb128 0x19
	.4byte	.LASF65
	.byte	0x3
	.2byte	0x129
	.byte	0xd
	.4byte	0x32a
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xb6
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x86
	.uleb128 0x9
	.byte	0
	.uleb128 0xf
	.4byte	.LASF66
	.byte	0x52
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x379
	.uleb128 0x10
	.4byte	.LASF68
	.byte	0x52
	.byte	0x28
	.4byte	0x86
	.4byte	.LLST1
	.uleb128 0xc
	.4byte	.LASF69
	.byte	0x54
	.byte	0xe
	.4byte	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x7
	.4byte	.LVL8
	.4byte	0x2f7
	.4byte	0x36f
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x11
	.4byte	.LVL9
	.4byte	0x2e7
	.byte	0
	.uleb128 0xf
	.4byte	.LASF67
	.byte	0x44
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x3c8
	.uleb128 0x10
	.4byte	.LASF68
	.byte	0x44
	.byte	0x26
	.4byte	0x86
	.4byte	.LLST0
	.uleb128 0xc
	.4byte	.LASF69
	.byte	0x46
	.byte	0xe
	.4byte	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x7
	.4byte	.LVL2
	.4byte	0x2f7
	.4byte	0x3be
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x11
	.4byte	.LVL3
	.4byte	0x2e7
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF73
	.byte	0x1
	.byte	0x34
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x4c3
	.uleb128 0x1b
	.4byte	.LASF70
	.byte	0x1
	.byte	0x36
	.byte	0x9
	.4byte	0x65
	.byte	0
	.uleb128 0x1c
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.4byte	0x440
	.uleb128 0x1d
	.4byte	.LASF74
	.byte	0x1
	.byte	0x3f
	.byte	0x25
	.4byte	0x26e
	.uleb128 0xc
	.4byte	.LASF71
	.byte	0x3f
	.byte	0x7e
	.4byte	0x4d3
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x12
	.4byte	.LVL20
	.4byte	0x307
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
	.byte	0x32
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x5
	.byte	0xc
	.4byte	0x42130008
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	.LVL13
	.4byte	0x32a
	.4byte	0x454
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x20
	.byte	0
	.uleb128 0x7
	.4byte	.LVL14
	.4byte	0x379
	.4byte	0x467
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x7
	.4byte	.LVL15
	.4byte	0x379
	.4byte	0x47a
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x33
	.byte	0
	.uleb128 0x7
	.4byte	.LVL16
	.4byte	0x379
	.4byte	0x48d
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.uleb128 0x7
	.4byte	.LVL17
	.4byte	0x379
	.4byte	0x4a0
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x3b
	.byte	0
	.uleb128 0x7
	.4byte	.LVL18
	.4byte	0x379
	.4byte	0x4b3
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x37
	.byte	0
	.uleb128 0x12
	.4byte	.LVL19
	.4byte	0x379
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x36
	.byte	0
	.byte	0
	.uleb128 0x1e
	.4byte	0x7c
	.4byte	0x4d3
	.uleb128 0x1f
	.4byte	0x2d
	.byte	0x51
	.byte	0
	.uleb128 0xd
	.4byte	0x4c3
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x4
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
	.uleb128 0x8
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x18
	.byte	0
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
	.uleb128 0xb
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x11
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1c
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
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
.LLST1:
	.byte	0x6
	.4byte	.LVL6
	.byte	0x4
	.uleb128 .LVL6-.LVL6
	.uleb128 .LVL7-.LVL6
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL7-.LVL6
	.uleb128 .LVL10-.LVL6
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL10-.LVL6
	.uleb128 .LVL11-.LVL6
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
	.uleb128 .LVL11-.LVL6
	.uleb128 .LFE6-.LVL6
	.uleb128 0x1
	.byte	0x58
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
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL4-.LVL0
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
	.uleb128 .LFE5-.LVL0
	.uleb128 0x1
	.byte	0x58
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
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
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
.LLRL2:
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF73:
	.string	"spm_init"
.LASF61:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL"
.LASF70:
	.string	"result"
.LASF36:
	.string	"f_dump_buffer_t"
.LASF20:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF4:
	.string	"signed char"
.LASF16:
	.string	"PRINT_LEVEL_ERROR"
.LASF6:
	.string	"short int"
.LASF31:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF38:
	.string	"f_tlv_dump_t"
.LASF28:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF30:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF54:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_QDEC"
.LASF24:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF56:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_LED_CON"
.LASF14:
	.string	"PRINT_LEVEL_INFO"
.LASF74:
	.string	"log_control_block_common"
.LASF45:
	.string	"msg_id_handle"
.LASF52:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_KEY_SCAN"
.LASF22:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF10:
	.string	"long long int"
.LASF40:
	.string	"log_switch"
.LASF8:
	.string	"long int"
.LASF37:
	.string	"f_msg_id_t"
.LASF43:
	.string	"dump_handle"
.LASF27:
	.string	"LOG_TYPE_HCI_DATA"
.LASF47:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_GPT"
.LASF11:
	.string	"long double"
.LASF72:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF50:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_I3C0"
.LASF5:
	.string	"unsigned char"
.LASF63:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF66:
	.string	"spm_unmask_wakeup_source"
.LASF51:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_USB_32K_RES"
.LASF2:
	.string	"long long unsigned int"
.LASF17:
	.string	"uint32_t"
.LASF64:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF3:
	.string	"unsigned int"
.LASF18:
	.string	"print_level_t"
.LASF25:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF19:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF33:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF71:
	.string	"msg_id_string"
.LASF67:
	.string	"spm_mask_wakeup_source"
.LASF42:
	.string	"print_handle"
.LASF7:
	.string	"short unsigned int"
.LASF44:
	.string	"tlv_dump_handle"
.LASF12:
	.string	"char"
.LASF62:
	.string	"_Bool"
.LASF35:
	.string	"f_print_t"
.LASF15:
	.string	"PRINT_LEVEL_WARNING"
.LASF26:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF46:
	.string	"log_control_block_t"
.LASF39:
	.string	"module_name"
.LASF55:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_RTC_TIMER"
.LASF49:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_IRQGEN"
.LASF9:
	.string	"long unsigned int"
.LASF41:
	.string	"print_level"
.LASF68:
	.string	"wakeup_source"
.LASF13:
	.string	"PRINT_LEVEL_DEBUG"
.LASF21:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF69:
	.string	"mask"
.LASF34:
	.string	"log_type_t"
.LASF58:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_TIMER"
.LASF59:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_IRQ"
.LASF23:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF60:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_SPM_SW_WAKEUP"
.LASF32:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF57:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_PMU"
.LASF29:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF65:
	.string	"print_module_msgid_log"
.LASF48:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_EINT"
.LASF53:
	.string	"HAL_SLEEP_MANAGER_WAKEUP_SOURCE_RAMBOZ"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_spm.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
