	.file	"riscv_hid_express_xy_queue.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_xy_queue.c"
	.section	.text.hid_express_generate_value_candidate,"ax",@progbits
	.align	1
	.globl	hid_express_generate_value_candidate
	.hidden	hid_express_generate_value_candidate
	.type	hid_express_generate_value_candidate, @function
hid_express_generate_value_candidate:
.LFB15:
	.file 1 "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_xy_queue.c"
	.loc 1 71 1
	.cfi_startproc
.LVL0:
	.loc 1 72 5
	.loc 1 73 37 is_stmt 0
	lw	a5,0(a0)
	.loc 1 76 38
	slli	a1,a1,2
.LVL1:
	.loc 1 72 25
	sw	a2,4(a0)
	.loc 1 73 5 is_stmt 1
	.loc 1 73 37 is_stmt 0
	add	a5,a5,a2
	.loc 1 73 25
	sw	a5,8(a0)
	.loc 1 76 5 is_stmt 1
	.loc 1 76 38 is_stmt 0
	add	a1,a0,a1
	.loc 1 76 20
	lw	a5,4(a1)
	sw	a5,0(a0)
	.loc 1 77 1
	ret
	.cfi_endproc
.LFE15:
	.size	hid_express_generate_value_candidate, .-hid_express_generate_value_candidate
	.section	.text.hid_express_generate_value_candidate_1R1T_concurrent,"ax",@progbits
	.align	1
	.globl	hid_express_generate_value_candidate_1R1T_concurrent
	.hidden	hid_express_generate_value_candidate_1R1T_concurrent
	.type	hid_express_generate_value_candidate_1R1T_concurrent, @function
hid_express_generate_value_candidate_1R1T_concurrent:
.LFB16:
	.loc 1 85 1 is_stmt 1
	.cfi_startproc
.LVL2:
	.loc 1 87 5
	.loc 1 87 38 is_stmt 0
	slli	a5,a1,2
	add	a5,a0,a5
	lw	a5,4(a5)
	.loc 1 87 20
	sw	a5,0(a0)
	.loc 1 89 5 is_stmt 1
	.loc 1 89 8 is_stmt 0
	beq	a1,zero,.L3
	.loc 1 90 9 is_stmt 1
	.loc 1 90 41 is_stmt 0
	lw	a4,4(a0)
	add	a2,a2,a4
.LVL3:
.L3:
	sw	a2,4(a0)
	.loc 1 96 5 is_stmt 1
	.loc 1 96 25 is_stmt 0
	sw	a5,8(a0)
	.loc 1 97 1
	ret
	.cfi_endproc
.LFE16:
	.size	hid_express_generate_value_candidate_1R1T_concurrent, .-hid_express_generate_value_candidate_1R1T_concurrent
	.section	.text.hid_express_x_y_buf_has_data,"ax",@progbits
	.align	1
	.globl	hid_express_x_y_buf_has_data
	.hidden	hid_express_x_y_buf_has_data
	.type	hid_express_x_y_buf_has_data, @function
hid_express_x_y_buf_has_data:
.LFB17:
	.loc 1 101 1 is_stmt 1
	.cfi_startproc
	.loc 1 102 5
	.loc 1 102 25 is_stmt 0
	lla	a5,vCtrl_x
	.loc 1 103 31 discriminator 1
	lw	a0,4(a5)
	lw	a5,8(a5)
	or	a0,a0,a5
	.loc 1 103 27
	lla	a5,vCtrl_y
	.loc 1 103 31 discriminator 1
	lw	a4,4(a5)
	lw	a5,8(a5)
	or	a0,a0,a4
	or	a0,a0,a5
	.loc 1 108 1
	snez	a0,a0
	ret
	.cfi_endproc
.LFE17:
	.size	hid_express_x_y_buf_has_data, .-hid_express_x_y_buf_has_data
	.section	.text.hid_express_x_y_buf_init,"ax",@progbits
	.align	1
	.globl	hid_express_x_y_buf_init
	.hidden	hid_express_x_y_buf_init
	.type	hid_express_x_y_buf_init, @function
hid_express_x_y_buf_init:
.LFB18:
	.loc 1 111 1 is_stmt 1
	.cfi_startproc
.LVL4:
	.loc 1 112 5
	.loc 1 111 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 112 14
	lla	a5,vCtrl_x
	sw	a5,0(a0)
	.loc 1 113 5 is_stmt 1
	.loc 1 113 14 is_stmt 0
	lla	s0,vCtrl_y
	sw	s0,0(a1)
	.loc 1 114 5 is_stmt 1
	li	a2,16
	li	a1,0
.LVL5:
	mv	a0,a5
.LVL6:
	call	memset
.LVL7:
	.loc 1 115 5
	mv	a0,s0
	.loc 1 116 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 115 5
	li	a2,16
	.loc 1 116 1
	.loc 1 115 5
	li	a1,0
	.loc 1 116 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 115 5
	tail	memset
.LVL8:
	.cfi_endproc
.LFE18:
	.size	hid_express_x_y_buf_init, .-hid_express_x_y_buf_init
	.hidden	vCtrl_y
	.globl	vCtrl_y
	.section	.bss.vCtrl_y,"aw",@nobits
	.align	2
	.type	vCtrl_y, @object
	.size	vCtrl_y, 16
vCtrl_y:
	.zero	16
	.hidden	vCtrl_x
	.globl	vCtrl_x
	.section	.bss.vCtrl_x,"aw",@nobits
	.align	2
	.type	vCtrl_x, @object
	.size	vCtrl_x, 16
vCtrl_x:
	.zero	16
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 6 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_xy_queue.h"
	.file 7 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.file 8 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x2eb
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0xf
	.4byte	.LASF51
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL4
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
	.uleb128 0x10
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0x2
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x11
	.byte	0x4
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x3
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x50
	.byte	0xe
	.4byte	0xe3
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
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF25
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x31
	.byte	0x1
	.4byte	0x127
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
	.uleb128 0x12
	.byte	0x10
	.byte	0x6
	.byte	0x37
	.byte	0x9
	.4byte	0x152
	.uleb128 0x8
	.4byte	.LASF34
	.byte	0x38
	.4byte	0x152
	.byte	0
	.uleb128 0x8
	.4byte	.LASF35
	.byte	0x39
	.4byte	0x162
	.byte	0x4
	.uleb128 0x8
	.4byte	.LASF36
	.byte	0x3a
	.4byte	0x88
	.byte	0xc
	.byte	0
	.uleb128 0xa
	.4byte	0x88
	.4byte	0x162
	.uleb128 0xb
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0xa
	.4byte	0x88
	.4byte	0x172
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF37
	.byte	0x6
	.byte	0x3c
	.byte	0x2
	.4byte	0x127
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x7
	.byte	0x6e
	.byte	0xe
	.4byte	0x1a3
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x3
	.byte	0
	.uleb128 0xc
	.4byte	.LASF42
	.byte	0x35
	.4byte	0x172
	.uleb128 0x5
	.byte	0x3
	.4byte	vCtrl_x
	.uleb128 0xc
	.4byte	.LASF43
	.byte	0x36
	.4byte	0x172
	.uleb128 0x5
	.byte	0x3
	.4byte	vCtrl_y
	.uleb128 0x13
	.4byte	.LASF52
	.byte	0x8
	.byte	0x21
	.byte	0x8
	.4byte	0x7f
	.4byte	0x1e3
	.uleb128 0x9
	.4byte	0x7f
	.uleb128 0x9
	.4byte	0x65
	.uleb128 0x9
	.4byte	0x6c
	.byte	0
	.uleb128 0xd
	.4byte	.LASF46
	.byte	0x6e
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x254
	.uleb128 0x5
	.4byte	.LASF44
	.byte	0x6e
	.byte	0x37
	.4byte	0x254
	.4byte	.LLST2
	.uleb128 0x5
	.4byte	.LASF45
	.byte	0x6e
	.byte	0x58
	.4byte	0x254
	.4byte	.LLST3
	.uleb128 0x14
	.4byte	.LVL7
	.4byte	0x1c3
	.4byte	0x236
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	vCtrl_x
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x40
	.byte	0
	.uleb128 0x15
	.4byte	.LVL8
	.4byte	0x1c3
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	vCtrl_y
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x40
	.byte	0
	.byte	0
	.uleb128 0xe
	.4byte	0x259
	.uleb128 0xe
	.4byte	0x172
	.uleb128 0x16
	.4byte	.LASF53
	.byte	0x1
	.byte	0x64
	.byte	0xa
	.4byte	0x94
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xd
	.4byte	.LASF47
	.byte	0x54
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2b2
	.uleb128 0x6
	.4byte	.LASF48
	.byte	0x54
	.byte	0x53
	.4byte	0x259
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x6
	.4byte	.LASF49
	.byte	0x54
	.byte	0x63
	.4byte	0x94
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.4byte	.LASF50
	.byte	0x54
	.byte	0x76
	.4byte	0x88
	.4byte	.LLST1
	.byte	0
	.uleb128 0x17
	.4byte	.LASF54
	.byte	0x1
	.byte	0x46
	.byte	0x6
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x6
	.4byte	.LASF48
	.byte	0x46
	.byte	0x43
	.4byte	0x259
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.4byte	.LASF49
	.byte	0x46
	.byte	0x53
	.4byte	0x94
	.4byte	.LLST0
	.uleb128 0x6
	.4byte	.LASF50
	.byte	0x46
	.byte	0x66
	.4byte	0x88
	.uleb128 0x1
	.byte	0x5c
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x21
	.sleb128 13
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
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
	.uleb128 0x21
	.sleb128 23
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x11
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x17
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
.LLST2:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL6-.LVL4
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL6-.LVL4
	.uleb128 .LFE18-.LVL4
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
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL5-.LVL4
	.uleb128 .LFE18-.LVL4
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
.LLST1:
	.byte	0x6
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL3-.LVL2
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL3-.LVL2
	.uleb128 .LFE16-.LVL2
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
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL1-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL1-.LVL0
	.uleb128 .LFE15-.LVL0
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
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x34
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
.LLRL4:
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
.LASF12:
	.string	"char"
.LASF13:
	.string	"size_t"
.LASF51:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF54:
	.string	"hid_express_generate_value_candidate"
.LASF26:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF23:
	.string	"DBG_PIN_USB_TX"
.LASF41:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF7:
	.string	"short unsigned int"
.LASF16:
	.string	"DBG_PIN_SPI_CB"
.LASF18:
	.string	"DBG_PIN_NACK"
.LASF32:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF31:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF37:
	.string	"T_ASSEMBLE_VAL_CTRL_S"
.LASF36:
	.string	"untransmitted_value"
.LASF4:
	.string	"signed char"
.LASF5:
	.string	"unsigned char"
.LASF19:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF20:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF9:
	.string	"long unsigned int"
.LASF53:
	.string	"hid_express_x_y_buf_has_data"
.LASF52:
	.string	"memset"
.LASF33:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF29:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF17:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF40:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF34:
	.string	"tx_n"
.LASF3:
	.string	"unsigned int"
.LASF2:
	.string	"long long unsigned int"
.LASF38:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF14:
	.string	"int32_t"
.LASF22:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF28:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF30:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF10:
	.string	"long long int"
.LASF24:
	.string	"DBG_PIN_MAX"
.LASF45:
	.string	"vctrl_y"
.LASF48:
	.string	"vctrl"
.LASF6:
	.string	"short int"
.LASF47:
	.string	"hid_express_generate_value_candidate_1R1T_concurrent"
.LASF50:
	.string	"value_new"
.LASF42:
	.string	"vCtrl_x"
.LASF46:
	.string	"hid_express_x_y_buf_init"
.LASF15:
	.string	"uint32_t"
.LASF8:
	.string	"long int"
.LASF21:
	.string	"DBG_PIN_USB_SOF"
.LASF11:
	.string	"long double"
.LASF44:
	.string	"vctrl_x"
.LASF35:
	.string	"predict_n"
.LASF39:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF25:
	.string	"_Bool"
.LASF43:
	.string	"vCtrl_y"
.LASF27:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF49:
	.string	"tx_result"
	.section	.debug_line_str,"MS",@progbits,1
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_express_xy_queue.c"
.LASF1:
	.string	"/workdir/airoha/risc-v"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
