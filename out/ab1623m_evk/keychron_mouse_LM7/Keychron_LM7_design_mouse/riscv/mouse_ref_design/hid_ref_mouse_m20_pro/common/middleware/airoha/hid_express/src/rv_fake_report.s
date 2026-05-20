	.file	"rv_fake_report.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/hid_express/src/rv_fake_report.c"
	.section	.text.rv_fake_report_config,"ax",@progbits
	.align	1
	.globl	rv_fake_report_config
	.hidden	rv_fake_report_config
	.type	rv_fake_report_config, @function
rv_fake_report_config:
.LFB6:
	.file 1 "/workdir/airoha/common/middleware/airoha/hid_express/src/rv_fake_report.c"
	.loc 1 55 1
	.cfi_startproc
.LVL0:
	.loc 1 56 5
.LBB2:
	.loc 1 56 10
	.loc 1 56 63
	.loc 1 56 245
.LBE2:
	.loc 1 55 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
.LBB3:
	.loc 1 56 245
	mv	a4,a0
.LBE3:
	.loc 1 55 1
	sw	s0,12(sp)
	sw	s1,8(sp)
.LBB4:
	.loc 1 56 245
	sw	a2,0(sp)
	sw	a2,4(sp)
	mv	a5,a1
	.cfi_offset 8, -8
	.cfi_offset 9, -12
.LBE4:
	.loc 1 55 1
	mv	s1,a0
	mv	s0,a1
.LBB5:
	.loc 1 56 245
	li	a3,3
	lla	a2,msg_id_string.0
.LVL1:
	li	a1,1
.LVL2:
	lla	a0,log_control_block_rv_exp
.LVL3:
.LBE5:
	.loc 1 55 1
	sw	ra,16(sp)
	.cfi_offset 1, -4
.LBB6:
	.loc 1 56 245
	call	print_module_msgid_log
.LVL4:
.LBE6:
	.loc 1 56 8 is_stmt 1 discriminator 1
	.loc 1 63 5
	lla	a4,fake_report_rounds
	.loc 1 63 8 is_stmt 0
	beq	s1,zero,.L2
	.loc 1 65 9 is_stmt 1
	.loc 1 65 29 is_stmt 0
	sw	s0,fake_report_pattern,a5
	.loc 1 67 9 is_stmt 1
	.loc 1 67 12 is_stmt 0
	lw	t1,4(sp)
	.loc 1 71 30
	li	a5,100
	.loc 1 67 12
	bne	s0,zero,.L3
	.loc 1 68 30
	li	a5,1000
.L3:
	sw	a5,fake_report_size,a3
	.loc 1 74 9 is_stmt 1
	.loc 1 74 28 is_stmt 0
	sw	t1,0(a4)
	.loc 1 76 9 is_stmt 1
	.loc 1 76 25 is_stmt 0
	sw	zero,fake_report_idx,a5
	.loc 1 77 9 is_stmt 1
	.loc 1 77 36 is_stmt 0
	sw	zero,fake_report_rounds_counter,a5
	.loc 1 78 9 is_stmt 1
	.loc 1 78 32 is_stmt 0
	sw	zero,fake_report_offset_cnt,a5
.L4:
	.loc 1 85 5 is_stmt 1
	.loc 1 86 5
	.loc 1 89 1 is_stmt 0
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
.LVL5:
	.loc 1 85 24
	sh	zero,curr_data,a5
	.loc 1 88 5 is_stmt 1
	.loc 1 89 1 is_stmt 0
	lw	s1,8(sp)
	.cfi_restore 9
.LVL6:
	li	a0,0
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
.LVL7:
	jr	ra
.LVL8:
.L2:
	.cfi_restore_state
	.loc 1 82 9 is_stmt 1
	.loc 1 82 28 is_stmt 0
	li	a5,-1
	sw	a5,0(a4)
	.loc 1 83 9 is_stmt 1
	.loc 1 83 36 is_stmt 0
	sw	a5,fake_report_rounds_counter,a4
	j	.L4
	.cfi_endproc
.LFE6:
	.size	rv_fake_report_config, .-rv_fake_report_config
	.section	.text.rv_fake_report_fake_report,"ax",@progbits
	.align	1
	.globl	rv_fake_report_fake_report
	.hidden	rv_fake_report_fake_report
	.type	rv_fake_report_fake_report, @function
rv_fake_report_fake_report:
.LFB7:
	.loc 1 93 1 is_stmt 1
	.cfi_startproc
.LVL9:
	.loc 1 94 5
	.loc 1 94 28 is_stmt 0
	lla	a3,fake_report_rounds_counter
	lw	a5,0(a3)
	lw	a4,fake_report_rounds
	.loc 1 94 8
	bgtu	a4,a5,.L8
	.loc 1 94 57 discriminator 1
	bne	a4,zero,.L7
.L8:
	.loc 1 96 9 is_stmt 1
	.loc 1 96 32 is_stmt 0
	lla	a4,curr_data
	lb	a2,0(a4)
	.loc 1 97 32
	lb	a4,1(a4)
	.loc 1 96 32
	sw	a2,8(a0)
	.loc 1 97 9 is_stmt 1
	.loc 1 103 24 is_stmt 0
	lla	a2,fake_report_idx
	.loc 1 97 32
	sw	a4,12(a0)
	.loc 1 103 9 is_stmt 1
	.loc 1 103 24 is_stmt 0
	lw	a4,0(a2)
	addi	a4,a4,1
	sw	a4,0(a2)
	.loc 1 105 9 is_stmt 1
	.loc 1 105 12 is_stmt 0
	lw	a2,fake_report_size
	bltu	a4,a2,.L7
	.loc 1 107 13 is_stmt 1
	.loc 1 108 39 is_stmt 0
	addi	a5,a5,1
	.loc 1 107 28
	sw	zero,fake_report_idx,a4
	.loc 1 108 13 is_stmt 1
	.loc 1 108 39 is_stmt 0
	sw	a5,0(a3)
.L7:
	.loc 1 111 1
	ret
	.cfi_endproc
.LFE7:
	.size	rv_fake_report_fake_report, .-rv_fake_report_fake_report
	.section	.text.rv_fake_report_post_process,"ax",@progbits
	.align	1
	.globl	rv_fake_report_post_process
	.hidden	rv_fake_report_post_process
	.type	rv_fake_report_post_process, @function
rv_fake_report_post_process:
.LFB8:
	.loc 1 114 1 is_stmt 1
	.cfi_startproc
	.loc 1 115 5
	.loc 1 115 28 is_stmt 0
	lw	a5,fake_report_rounds
	.loc 1 115 8
	lw	a4,fake_report_rounds_counter
	bgtu	a5,a4,.L15
	.loc 1 115 57 discriminator 1
	bne	a5,zero,.L14
.L15:
	.loc 1 116 9 is_stmt 1
	.loc 1 116 46 is_stmt 0
	lw	a4,fake_report_idx
	slli	a4,a4,1
	lw	a5,fake_report_data
	add	a5,a5,a4
	.loc 1 116 63
	lb	a3,0(a5)
	.loc 1 117 63
	lb	a5,1(a5)
	.loc 1 116 28
	lla	a4,curr_data
	sb	a3,0(a4)
	.loc 1 117 9 is_stmt 1
	.loc 1 117 28 is_stmt 0
	sb	a5,1(a4)
.L14:
	.loc 1 119 1
	ret
	.cfi_endproc
.LFE8:
	.size	rv_fake_report_post_process, .-rv_fake_report_post_process
	.section	.text.rv_fake_report_set,"ax",@progbits
	.align	1
	.globl	rv_fake_report_set
	.hidden	rv_fake_report_set
	.type	rv_fake_report_set, @function
rv_fake_report_set:
.LFB9:
	.loc 1 122 1 is_stmt 1
	.cfi_startproc
.LVL10:
	.loc 1 123 5
	.loc 1 123 22 is_stmt 0
	sw	a0,fake_report_data,a5
	.loc 1 124 1
	ret
	.cfi_endproc
.LFE9:
	.size	rv_fake_report_set, .-rv_fake_report_set
	.section	.text.rv_fake_report_get_report_status,"ax",@progbits
	.align	1
	.globl	rv_fake_report_get_report_status
	.hidden	rv_fake_report_get_report_status
	.type	rv_fake_report_get_report_status, @function
rv_fake_report_get_report_status:
.LFB10:
	.loc 1 127 1 is_stmt 1
	.cfi_startproc
	.loc 1 128 5
	.loc 1 128 7 is_stmt 0
	lw	a0,fake_report_rounds
	addi	a0,a0,1
	.loc 1 132 1
	snez	a0,a0
	ret
	.cfi_endproc
.LFE10:
	.size	rv_fake_report_get_report_status, .-rv_fake_report_get_report_status
	.section	.text.rv_fake_report__get_state,"ax",@progbits
	.align	1
	.globl	rv_fake_report__get_state
	.hidden	rv_fake_report__get_state
	.type	rv_fake_report__get_state, @function
rv_fake_report__get_state:
.LFB11:
	.loc 1 135 1 is_stmt 1
	.cfi_startproc
	.loc 1 136 5
	.loc 1 136 27 is_stmt 0
	lw	a5,fake_report_rounds
	.loc 1 136 7
	li	a4,-1
	.loc 1 137 16
	li	a0,0
	.loc 1 136 7
	beq	a5,a4,.L19
	.loc 1 139 10 is_stmt 1
	.loc 1 139 13 is_stmt 0
	lw	a4,fake_report_rounds_counter
	.loc 1 144 12
	li	a0,1
	.loc 1 139 13
	bgtu	a5,a4,.L19
	.loc 1 144 12
	snez	a0,a5
	addi	a0,a0,1
.L19:
	.loc 1 145 1
	ret
	.cfi_endproc
.LFE11:
	.size	rv_fake_report__get_state, .-rv_fake_report__get_state
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 89
msg_id_string.0:
	.string	"[M:rv_exp C:info F: L: ]: rv_fake_report_config  enable =%d, pattern = %d,   rounds = %d"
	.hidden	curr_data
	.globl	curr_data
	.section	.sbss.curr_data,"aw",@nobits
	.align	2
	.type	curr_data, @object
	.size	curr_data, 2
curr_data:
	.zero	2
	.hidden	fake_report_data
	.globl	fake_report_data
	.section	.sbss.fake_report_data,"aw",@nobits
	.align	2
	.type	fake_report_data, @object
	.size	fake_report_data, 4
fake_report_data:
	.zero	4
	.hidden	fake_report_size
	.globl	fake_report_size
	.section	.sbss.fake_report_size,"aw",@nobits
	.align	2
	.type	fake_report_size, @object
	.size	fake_report_size, 4
fake_report_size:
	.zero	4
	.hidden	fake_report_pattern
	.globl	fake_report_pattern
	.section	.sbss.fake_report_pattern,"aw",@nobits
	.align	2
	.type	fake_report_pattern, @object
	.size	fake_report_pattern, 4
fake_report_pattern:
	.zero	4
	.hidden	fake_report_offset_cnt
	.globl	fake_report_offset_cnt
	.section	.sbss.fake_report_offset_cnt,"aw",@nobits
	.align	2
	.type	fake_report_offset_cnt, @object
	.size	fake_report_offset_cnt, 4
fake_report_offset_cnt:
	.zero	4
	.hidden	fake_report_rounds_counter
	.globl	fake_report_rounds_counter
	.section	.sdata.fake_report_rounds_counter,"aw"
	.align	2
	.type	fake_report_rounds_counter, @object
	.size	fake_report_rounds_counter, 4
fake_report_rounds_counter:
	.word	-1
	.hidden	fake_report_rounds
	.globl	fake_report_rounds
	.section	.sdata.fake_report_rounds,"aw"
	.align	2
	.type	fake_report_rounds, @object
	.size	fake_report_rounds, 4
fake_report_rounds:
	.word	-1
	.hidden	fake_report_idx
	.globl	fake_report_idx
	.section	.sbss.fake_report_idx,"aw",@nobits
	.align	2
	.type	fake_report_idx, @object
	.size	fake_report_idx, 4
fake_report_idx:
	.zero	4
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 4 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 5 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 6 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 7 "/workdir/airoha/common/middleware/airoha/hid_express/inc/rv_fake_report.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x5e2
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x15
	.4byte	.LASF96
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL4
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
	.uleb128 0x16
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x17
	.byte	0x4
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xc
	.4byte	0x75
	.uleb128 0x6
	.4byte	0x7c
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x2
	.byte	0x22
	.byte	0x15
	.4byte	0x34
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x2
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x10
	.4byte	0x9e
	.4byte	0xba
	.uleb128 0x11
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x3
	.byte	0x50
	.byte	0xe
	.4byte	0xfd
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x8
	.byte	0
	.uleb128 0x4
	.byte	0x1
	.byte	0x2
	.4byte	.LASF25
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x4
	.byte	0x31
	.byte	0x1
	.4byte	0x141
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x7
	.byte	0
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x5
	.byte	0x3d
	.byte	0xe
	.4byte	0x166
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF38
	.byte	0x5
	.byte	0x42
	.byte	0x3
	.4byte	0x141
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x5
	.byte	0x45
	.byte	0xe
	.4byte	0x1d9
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x3f
	.byte	0
	.uleb128 0x5
	.4byte	.LASF54
	.byte	0x5
	.byte	0x57
	.byte	0x3
	.4byte	0x172
	.uleb128 0x5
	.4byte	.LASF55
	.byte	0x5
	.byte	0x59
	.byte	0x10
	.4byte	0x1f1
	.uleb128 0x6
	.4byte	0x1f6
	.uleb128 0xd
	.4byte	0x216
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x166
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0xb
	.byte	0
	.uleb128 0x5
	.4byte	.LASF56
	.byte	0x5
	.byte	0x5a
	.byte	0x10
	.4byte	0x222
	.uleb128 0x6
	.4byte	0x227
	.uleb128 0xd
	.4byte	0x251
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x166
	.uleb128 0x2
	.4byte	0x251
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0xb
	.byte	0
	.uleb128 0x6
	.4byte	0x256
	.uleb128 0x18
	.uleb128 0x5
	.4byte	.LASF57
	.byte	0x5
	.byte	0x5b
	.byte	0x10
	.4byte	0x263
	.uleb128 0x6
	.4byte	0x268
	.uleb128 0xd
	.4byte	0x283
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x166
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0xb
	.byte	0
	.uleb128 0x5
	.4byte	.LASF58
	.byte	0x5
	.byte	0x5c
	.byte	0x14
	.4byte	0x28f
	.uleb128 0x6
	.4byte	0x294
	.uleb128 0x19
	.4byte	0x9e
	.4byte	0x2b7
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x166
	.uleb128 0x2
	.4byte	0x1d9
	.uleb128 0x2
	.4byte	0x2b7
	.uleb128 0x2
	.4byte	0x2bc
	.byte	0
	.uleb128 0x6
	.4byte	0x251
	.uleb128 0x6
	.4byte	0x9e
	.uleb128 0xe
	.byte	0x1c
	.byte	0x5
	.byte	0x5e
	.4byte	0x325
	.uleb128 0x3
	.4byte	.LASF59
	.byte	0x5
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x3
	.4byte	.LASF60
	.byte	0x5
	.byte	0x60
	.byte	0xe
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF61
	.byte	0x5
	.byte	0x61
	.byte	0xe
	.4byte	0x9e
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF62
	.byte	0x5
	.byte	0x62
	.byte	0xf
	.4byte	0x1e5
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF63
	.byte	0x5
	.byte	0x63
	.byte	0x15
	.4byte	0x216
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF64
	.byte	0x5
	.byte	0x64
	.byte	0x12
	.4byte	0x283
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF65
	.byte	0x5
	.byte	0x65
	.byte	0x10
	.4byte	0x257
	.byte	0x18
	.byte	0
	.uleb128 0x5
	.4byte	.LASF66
	.byte	0x5
	.byte	0x66
	.byte	0x3
	.4byte	0x2c1
	.uleb128 0xe
	.byte	0x28
	.byte	0x6
	.byte	0x8d
	.4byte	0x3a2
	.uleb128 0x3
	.4byte	.LASF67
	.byte	0x6
	.byte	0x8e
	.byte	0xe
	.4byte	0x9e
	.byte	0
	.uleb128 0xa
	.string	"k"
	.byte	0x8f
	.byte	0xe
	.4byte	0x9e
	.byte	0x4
	.uleb128 0xa
	.string	"x"
	.byte	0x90
	.byte	0xd
	.4byte	0x92
	.byte	0x8
	.uleb128 0xa
	.string	"y"
	.byte	0x91
	.byte	0xd
	.4byte	0x92
	.byte	0xc
	.uleb128 0xa
	.string	"z1"
	.byte	0x92
	.byte	0xd
	.4byte	0x92
	.byte	0x10
	.uleb128 0xa
	.string	"z2"
	.byte	0x93
	.byte	0xd
	.4byte	0x92
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF68
	.byte	0x6
	.byte	0x94
	.byte	0xe
	.4byte	0x9e
	.byte	0x18
	.uleb128 0x3
	.4byte	.LASF69
	.byte	0x6
	.byte	0x95
	.byte	0xe
	.4byte	0xaa
	.byte	0x1c
	.uleb128 0x3
	.4byte	.LASF70
	.byte	0x6
	.byte	0x96
	.byte	0xe
	.4byte	0x9e
	.byte	0x24
	.byte	0
	.uleb128 0x5
	.4byte	.LASF71
	.byte	0x6
	.byte	0x9c
	.byte	0x2
	.4byte	0x331
	.uleb128 0x6
	.4byte	0x3a2
	.uleb128 0xe
	.byte	0x2
	.byte	0x7
	.byte	0x27
	.4byte	0x3d6
	.uleb128 0x3
	.4byte	.LASF72
	.byte	0x7
	.byte	0x28
	.byte	0xc
	.4byte	0x86
	.byte	0
	.uleb128 0x3
	.4byte	.LASF73
	.byte	0x7
	.byte	0x29
	.byte	0xc
	.4byte	0x86
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF74
	.byte	0x7
	.byte	0x2a
	.byte	0x2
	.4byte	0x3b3
	.uleb128 0xc
	.4byte	0x3d6
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x7
	.byte	0x2d
	.byte	0xe
	.4byte	0x406
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x2
	.byte	0
	.uleb128 0x7
	.4byte	.LASF78
	.byte	0x2c
	.byte	0xa
	.4byte	0x9e
	.uleb128 0x5
	.byte	0x3
	.4byte	fake_report_idx
	.uleb128 0x7
	.4byte	.LASF79
	.byte	0x2d
	.byte	0xa
	.4byte	0x9e
	.uleb128 0x5
	.byte	0x3
	.4byte	fake_report_rounds
	.uleb128 0x7
	.4byte	.LASF80
	.byte	0x2e
	.byte	0xa
	.4byte	0x9e
	.uleb128 0x5
	.byte	0x3
	.4byte	fake_report_rounds_counter
	.uleb128 0x7
	.4byte	.LASF81
	.byte	0x2f
	.byte	0xa
	.4byte	0x9e
	.uleb128 0x5
	.byte	0x3
	.4byte	fake_report_offset_cnt
	.uleb128 0x7
	.4byte	.LASF82
	.byte	0x30
	.byte	0xa
	.4byte	0x9e
	.uleb128 0x5
	.byte	0x3
	.4byte	fake_report_pattern
	.uleb128 0x7
	.4byte	.LASF83
	.byte	0x31
	.byte	0xa
	.4byte	0x9e
	.uleb128 0x5
	.byte	0x3
	.4byte	fake_report_size
	.uleb128 0x7
	.4byte	.LASF84
	.byte	0x32
	.byte	0x1f
	.4byte	0x47d
	.uleb128 0x5
	.byte	0x3
	.4byte	fake_report_data
	.uleb128 0x6
	.4byte	0x3e2
	.uleb128 0x7
	.4byte	.LASF85
	.byte	0x33
	.byte	0x17
	.4byte	0x3d6
	.uleb128 0x5
	.byte	0x3
	.4byte	curr_data
	.uleb128 0x1a
	.4byte	.LASF97
	.byte	0x5
	.2byte	0x129
	.byte	0xd
	.4byte	0x4b6
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x166
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0xb
	.byte	0
	.uleb128 0x12
	.4byte	.LASF86
	.byte	0x86
	.byte	0xa
	.4byte	0x9e
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x12
	.4byte	.LASF87
	.byte	0x7e
	.byte	0x5
	.4byte	0xfd
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x13
	.4byte	.LASF88
	.byte	0x79
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x502
	.uleb128 0x14
	.4byte	.LASF90
	.byte	0x79
	.byte	0x23
	.4byte	0x2bc
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF98
	.byte	0x1
	.byte	0x71
	.byte	0x6
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x13
	.4byte	.LASF89
	.byte	0x5c
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x536
	.uleb128 0x14
	.4byte	.LASF91
	.byte	0x5c
	.byte	0x37
	.4byte	0x3ae
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF99
	.byte	0x1
	.byte	0x36
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5d0
	.uleb128 0xf
	.4byte	.LASF92
	.byte	0x24
	.4byte	0x9e
	.4byte	.LLST0
	.uleb128 0xf
	.4byte	.LASF93
	.byte	0x35
	.4byte	0x9e
	.4byte	.LLST1
	.uleb128 0xf
	.4byte	.LASF94
	.byte	0x47
	.4byte	0x9e
	.4byte	.LLST2
	.uleb128 0x1d
	.4byte	.LLRL3
	.uleb128 0x1e
	.4byte	.LASF95
	.byte	0x1
	.byte	0x38
	.byte	0x25
	.4byte	0x325
	.uleb128 0x1f
	.4byte	.LASF100
	.byte	0x1
	.byte	0x38
	.byte	0x7e
	.4byte	0x5e0
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x20
	.4byte	.LVL4
	.4byte	0x493
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x5f
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x8
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -16
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	0x7c
	.4byte	0x5e0
	.uleb128 0x11
	.4byte	0x2d
	.byte	0x58
	.byte	0
	.uleb128 0xc
	.4byte	0x5d0
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0x18
	.byte	0
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
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 54
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x14
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1b
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
	.uleb128 0x1d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
.LLST0:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL6-.LVL0
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL6-.LVL0
	.uleb128 .LVL8-.LVL0
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
	.uleb128 .LVL8-.LVL0
	.uleb128 .LFE6-.LVL0
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL2-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL2-.LVL0
	.uleb128 .LVL5-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL5-.LVL0
	.uleb128 .LVL8-.LVL0
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
	.uleb128 .LVL8-.LVL0
	.uleb128 .LFE6-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL1-.LVL0
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL1-.LVL0
	.uleb128 .LVL4-1-.LVL0
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL4-1-.LVL0
	.uleb128 .LVL7-.LVL0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL7-.LVL0
	.uleb128 .LVL8-.LVL0
	.uleb128 0x2
	.byte	0x72
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL8-.LVL0
	.uleb128 .LFE6-.LVL0
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
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
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
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
	.4byte	.LBB2
	.byte	0x4
	.uleb128 .LBB2-.LBB2
	.uleb128 .LBE2-.LBB2
	.byte	0x4
	.uleb128 .LBB3-.LBB2
	.uleb128 .LBE3-.LBB2
	.byte	0x4
	.uleb128 .LBB4-.LBB2
	.uleb128 .LBE4-.LBB2
	.byte	0x4
	.uleb128 .LBB5-.LBB2
	.uleb128 .LBE5-.LBB2
	.byte	0x4
	.uleb128 .LBB6-.LBB2
	.uleb128 .LBE6-.LBB2
	.byte	0
.LLRL4:
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
	.byte	0x7
	.4byte	.LFB7
	.uleb128 .LFE7-.LFB7
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF59:
	.string	"module_name"
.LASF65:
	.string	"msg_id_handle"
.LASF91:
	.string	"outgoing"
.LASF44:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF50:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF81:
	.string	"fake_report_offset_cnt"
.LASF40:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF13:
	.string	"int8_t"
.LASF89:
	.string	"rv_fake_report_fake_report"
.LASF29:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF37:
	.string	"PRINT_LEVEL_ERROR"
.LASF67:
	.string	"type"
.LASF51:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF58:
	.string	"f_tlv_dump_t"
.LASF48:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF30:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF19:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF20:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF6:
	.string	"short int"
.LASF8:
	.string	"long int"
.LASF93:
	.string	"pattern"
.LASF32:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF92:
	.string	"enable"
.LASF16:
	.string	"DBG_PIN_SPI_CB"
.LASF35:
	.string	"PRINT_LEVEL_INFO"
.LASF88:
	.string	"rv_fake_report_set"
.LASF11:
	.string	"long double"
.LASF42:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF10:
	.string	"long long int"
.LASF82:
	.string	"fake_report_pattern"
.LASF76:
	.string	"FAKE_REPORT_RUNNING"
.LASF77:
	.string	"FAKE_REPORT_COMPLETED"
.LASF12:
	.string	"char"
.LASF95:
	.string	"log_control_block_rv_exp"
.LASF90:
	.string	"fake_data"
.LASF56:
	.string	"f_dump_buffer_t"
.LASF57:
	.string	"f_msg_id_t"
.LASF14:
	.string	"int32_t"
.LASF63:
	.string	"dump_handle"
.LASF22:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF47:
	.string	"LOG_TYPE_HCI_DATA"
.LASF75:
	.string	"FAKE_REPORT_DISABLED"
.LASF86:
	.string	"rv_fake_report__get_state"
.LASF80:
	.string	"fake_report_rounds_counter"
.LASF79:
	.string	"fake_report_rounds"
.LASF96:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF5:
	.string	"unsigned char"
.LASF84:
	.string	"fake_report_data"
.LASF4:
	.string	"signed char"
.LASF70:
	.string	"kb_consumer"
.LASF2:
	.string	"long long unsigned int"
.LASF15:
	.string	"uint32_t"
.LASF17:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF3:
	.string	"unsigned int"
.LASF26:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF97:
	.string	"print_module_msgid_log"
.LASF68:
	.string	"k_old"
.LASF45:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF39:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF53:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF23:
	.string	"DBG_PIN_USB_TX"
.LASF71:
	.string	"T_OUTGOING_VALUES_S"
.LASF62:
	.string	"print_handle"
.LASF7:
	.string	"short unsigned int"
.LASF64:
	.string	"tlv_dump_handle"
.LASF99:
	.string	"rv_fake_report_config"
.LASF38:
	.string	"print_level_t"
.LASF69:
	.string	"kb_std"
.LASF25:
	.string	"_Bool"
.LASF55:
	.string	"f_print_t"
.LASF78:
	.string	"fake_report_idx"
.LASF36:
	.string	"PRINT_LEVEL_WARNING"
.LASF46:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF66:
	.string	"log_control_block_t"
.LASF98:
	.string	"rv_fake_report_post_process"
.LASF94:
	.string	"rounds"
.LASF28:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF9:
	.string	"long unsigned int"
.LASF61:
	.string	"print_level"
.LASF74:
	.string	"T_SENSOR_DATA_SMALL_S"
.LASF34:
	.string	"PRINT_LEVEL_DEBUG"
.LASF41:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF85:
	.string	"curr_data"
.LASF31:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF21:
	.string	"DBG_PIN_USB_SOF"
.LASF27:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF54:
	.string	"log_type_t"
.LASF83:
	.string	"fake_report_size"
.LASF43:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF52:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF33:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF18:
	.string	"DBG_PIN_NACK"
.LASF100:
	.string	"msg_id_string"
.LASF24:
	.string	"DBG_PIN_MAX"
.LASF49:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF87:
	.string	"rv_fake_report_get_report_status"
.LASF60:
	.string	"log_switch"
.LASF72:
	.string	"sensor_x"
.LASF73:
	.string	"sensor_y"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/rv_fake_report.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
