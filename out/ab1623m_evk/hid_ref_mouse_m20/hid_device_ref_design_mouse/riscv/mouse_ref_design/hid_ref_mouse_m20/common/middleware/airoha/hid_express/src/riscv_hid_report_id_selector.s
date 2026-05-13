	.file	"riscv_hid_report_id_selector.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_report_id_selector.c"
	.section	.text.riscv_hid_report_id_select,"ax",@progbits
	.align	1
	.globl	riscv_hid_report_id_select
	.hidden	riscv_hid_report_id_select
	.type	riscv_hid_report_id_select, @function
riscv_hid_report_id_select:
.LFB6:
	.file 1 "/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_report_id_selector.c"
	.loc 1 60 1
	.cfi_startproc
.LVL0:
	.loc 1 62 5
	.loc 1 60 1 is_stmt 0
	mv	a5,a0
	.loc 1 62 17
	lw	a0,0(a0)
.LVL1:
	.loc 1 62 8
	li	a4,9
	bne	a0,a4,.L2
	.loc 1 73 9 is_stmt 1
	.loc 1 73 33 is_stmt 0
	lbu	a5,31(a5)
.LVL2:
	.loc 1 73 11
	beq	a5,zero,.L4
	ret
.LVL3:
.L2:
	.loc 1 82 10 is_stmt 1
	.loc 1 82 13 is_stmt 0
	li	a4,10
	bne	a0,a4,.L1
	.loc 1 91 9 is_stmt 1
	.loc 1 91 34 is_stmt 0
	lhu	a5,38(a5)
.LVL4:
	.loc 1 91 11
	beq	a5,zero,.L5
	ret
.L4:
	.loc 1 79 20
	li	a0,1
	ret
.L5:
	.loc 1 97 20
	li	a0,5
.L1:
	.loc 1 103 1
	ret
	.cfi_endproc
.LFE6:
	.size	riscv_hid_report_id_select, .-riscv_hid_report_id_select
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x149
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x5
	.4byte	.LASF21
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL1
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x1
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x1
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x1
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x1
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x1
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x1
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x1
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x1
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
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x7
	.4byte	0x86
	.4byte	0xa2
	.uleb128 0x8
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x1
	.byte	0x1
	.byte	0x2
	.4byte	.LASF15
	.uleb128 0x9
	.byte	0x28
	.byte	0x3
	.byte	0x8d
	.byte	0x9
	.4byte	0x113
	.uleb128 0x3
	.4byte	.LASF16
	.byte	0x8e
	.4byte	0x86
	.byte	0
	.uleb128 0x2
	.string	"k"
	.byte	0x8f
	.byte	0xe
	.4byte	0x86
	.byte	0x4
	.uleb128 0x2
	.string	"x"
	.byte	0x90
	.byte	0xd
	.4byte	0x7a
	.byte	0x8
	.uleb128 0x2
	.string	"y"
	.byte	0x91
	.byte	0xd
	.4byte	0x7a
	.byte	0xc
	.uleb128 0x2
	.string	"z1"
	.byte	0x92
	.byte	0xd
	.4byte	0x7a
	.byte	0x10
	.uleb128 0x2
	.string	"z2"
	.byte	0x93
	.byte	0xd
	.4byte	0x7a
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF17
	.byte	0x94
	.4byte	0x86
	.byte	0x18
	.uleb128 0x3
	.4byte	.LASF18
	.byte	0x95
	.4byte	0x92
	.byte	0x1c
	.uleb128 0x3
	.4byte	.LASF19
	.byte	0x96
	.4byte	0x86
	.byte	0x24
	.byte	0
	.uleb128 0x4
	.4byte	.LASF20
	.byte	0x3
	.byte	0x9c
	.byte	0x2
	.4byte	0xa9
	.uleb128 0xa
	.byte	0x4
	.4byte	0x113
	.uleb128 0xb
	.4byte	.LASF22
	.byte	0x1
	.byte	0x3b
	.byte	0xa
	.4byte	0x86
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xc
	.4byte	.LASF23
	.byte	0x1
	.byte	0x3b
	.byte	0x3a
	.4byte	0x11f
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.sleb128 14
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
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
	.uleb128 0x6
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
	.uleb128 0xa
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL4-.LVL0
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
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
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
.LLRL1:
	.byte	0x7
	.4byte	.LFB6
	.uleb128 .LFE6-.LFB6
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF10:
	.string	"long long int"
.LASF20:
	.string	"T_OUTGOING_VALUES_S"
.LASF18:
	.string	"kb_std"
.LASF22:
	.string	"riscv_hid_report_id_select"
.LASF13:
	.string	"int32_t"
.LASF9:
	.string	"long unsigned int"
.LASF2:
	.string	"long long unsigned int"
.LASF23:
	.string	"outgoing"
.LASF16:
	.string	"type"
.LASF5:
	.string	"unsigned char"
.LASF12:
	.string	"char"
.LASF14:
	.string	"uint32_t"
.LASF8:
	.string	"long int"
.LASF15:
	.string	"_Bool"
.LASF7:
	.string	"short unsigned int"
.LASF4:
	.string	"signed char"
.LASF3:
	.string	"unsigned int"
.LASF11:
	.string	"long double"
.LASF6:
	.string	"short int"
.LASF19:
	.string	"kb_consumer"
.LASF17:
	.string	"k_old"
.LASF21:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/riscv_hid_report_id_selector.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
