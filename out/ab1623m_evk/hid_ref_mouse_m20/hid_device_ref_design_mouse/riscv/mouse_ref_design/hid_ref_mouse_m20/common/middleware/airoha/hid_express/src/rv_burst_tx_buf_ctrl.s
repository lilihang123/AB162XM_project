	.file	"rv_burst_tx_buf_ctrl.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/hid_express/src/rv_burst_tx_buf_ctrl.c"
	.section	.text.rv_bt_burst_tx_num_ctrl,"ax",@progbits
	.align	1
	.globl	rv_bt_burst_tx_num_ctrl
	.hidden	rv_bt_burst_tx_num_ctrl
	.type	rv_bt_burst_tx_num_ctrl, @function
rv_bt_burst_tx_num_ctrl:
.LFB15:
	.file 1 "/workdir/airoha/common/middleware/airoha/hid_express/src/rv_burst_tx_buf_ctrl.c"
	.loc 1 70 1
	.cfi_startproc
.LVL0:
	.loc 1 71 5
	.loc 1 72 27 is_stmt 0
	lla	t1,LC_burst_tx_number
	lw	t0,0(t1)
	lla	a2,outgoing_buffer_avail
	.loc 1 71 14
	li	a3,10
	.loc 1 72 27
	sw	t0,0(a2)
	.loc 1 70 1
	mv	a4,a0
	.loc 1 71 14
	sub	a5,a3,a1
.LVL1:
	.loc 1 72 5 is_stmt 1
	.loc 1 74 5
	.loc 1 74 7 is_stmt 0
	beq	a3,a1,.L2
	.loc 1 81 16
	li	a0,0
.LVL2:
	.loc 1 74 29 discriminator 1
	beq	a5,a3,.L1
	.loc 1 76 9 is_stmt 1
	.loc 1 76 29 is_stmt 0
	li	a5,9
.LVL3:
	sub	a5,a5,a1
.LVL4:
	.loc 1 95 5 is_stmt 1
	.loc 1 95 7 is_stmt 0
	li	a3,1
	bleu	a5,a3,.L2
	.loc 1 97 9 is_stmt 1
	.loc 1 97 22 is_stmt 0
	lla	a0,LC_ReTx_times
	lw	a3,0(a0)
	addi	a3,a3,1
	sw	a3,0(a0)
.L2:
.LVL5:
	.loc 1 100 5 is_stmt 1
	.loc 1 104 43 is_stmt 0
	lbu	a3,8(a4)
	lbu	a0,7(a4)
	slli	a3,a3,8
	or	a3,a3,a0
	lla	a0,last_ms_key
	.loc 1 100 8
	bgtu	t0,a5,.L6
	.loc 1 104 9 is_stmt 1
	.loc 1 104 12 is_stmt 0
	lbu	t0,0(a0)
	bne	t0,a3,.L7
	.loc 1 104 47 discriminator 1
	lb	t0,13(a4)
	bne	t0,zero,.L7
	.loc 1 104 90 discriminator 2
	lbu	t0,5(a4)
	lbu	a4,6(a4)
.LVL6:
	slli	a4,a4,8
	or	a4,a4,t0
	.loc 1 104 75 discriminator 2
	lw	t0,attr_handle
	bne	a4,t0,.L7
	.loc 1 106 13 is_stmt 1
	.loc 1 106 35 is_stmt 0
	sw	zero,outgoing_buffer_avail,a4
.L6:
	.loc 1 116 5 is_stmt 1
	.loc 1 116 33 is_stmt 0
	lla	a1,LC_traffic_statistic_counter
.LVL7:
	lw	a4,0(a1)
	addi	a4,a4,1
	sw	a4,0(a1)
	.loc 1 117 5 is_stmt 1
	.loc 1 117 7 is_stmt 0
	li	a1,132
	bleu	a4,a1,.L8
	.loc 1 119 9 is_stmt 1
	.loc 1 119 12 is_stmt 0
	lw	a1,LC_ReTx_times
	li	a4,9
	bleu	a1,a4,.L9
	.loc 1 122 13 is_stmt 1
	.loc 1 122 32 is_stmt 0
	li	a4,10
	.loc 1 123 43
	lla	a1,bt_debug
	.loc 1 122 32
	sw	a4,0(t1)
	.loc 1 123 13 is_stmt 1
	.loc 1 123 43 is_stmt 0
	lbu	a4,3(a1)
	addi	a4,a4,1
	sb	a4,3(a1)
.L10:
	.loc 1 131 9 is_stmt 1
	.loc 1 131 38 is_stmt 0
	sw	zero,LC_traffic_statistic_counter,a4
	.loc 1 132 9 is_stmt 1
	.loc 1 132 23 is_stmt 0
	sw	zero,LC_ReTx_times,a4
.L8:
	.loc 1 135 5 is_stmt 1
	.loc 1 135 27 is_stmt 0
	lw	a4,0(t1)
	.loc 1 135 7
	bleu	a4,a5,.L11
	.loc 1 135 50 discriminator 1
	lw	a1,0(a2)
	beq	a1,zero,.L11
	.loc 1 137 9 is_stmt 1
	.loc 1 137 11 is_stmt 0
	li	a1,10
	bne	a4,a1,.L12
	.loc 1 137 39 discriminator 1
	li	a1,8
	bne	a5,a1,.L12
	.loc 1 140 33
	li	a5,9
.L12:
.LVL8:
	.loc 1 142 9 is_stmt 1
	.loc 1 142 52 is_stmt 0
	sub	a4,a4,a5
	.loc 1 142 31
	sw	a4,0(a2)
.LVL9:
.L11:
	.loc 1 147 5 is_stmt 1
	.loc 1 147 17 is_stmt 0
	sb	a3,0(a0)
	.loc 1 150 5 is_stmt 1
	.loc 1 150 12 is_stmt 0
	lw	a0,0(a2)
.L1:
	.loc 1 151 1
	ret
.LVL10:
.L7:
	.loc 1 111 13 is_stmt 1
	.loc 1 111 35 is_stmt 0
	sw	a1,0(a2)
	j	.L6
.LVL11:
.L9:
	.loc 1 127 13 is_stmt 1
	.loc 1 127 32 is_stmt 0
	li	a4,2
	sw	a4,0(t1)
	j	.L10
	.cfi_endproc
.LFE15:
	.size	rv_bt_burst_tx_num_ctrl, .-rv_bt_burst_tx_num_ctrl
	.hidden	outgoing_buffer_avail
	.globl	outgoing_buffer_avail
	.section	.sdata.outgoing_buffer_avail,"aw"
	.align	2
	.type	outgoing_buffer_avail, @object
	.size	outgoing_buffer_avail, 4
outgoing_buffer_avail:
	.word	2
	.hidden	LC_burst_tx_number
	.globl	LC_burst_tx_number
	.section	.sdata.LC_burst_tx_number,"aw"
	.align	2
	.type	LC_burst_tx_number, @object
	.size	LC_burst_tx_number, 4
LC_burst_tx_number:
	.word	2
	.section	.sbss.last_ms_key,"aw",@nobits
	.type	last_ms_key, @object
	.size	last_ms_key, 1
last_ms_key:
	.zero	1
	.section	.sbss.LC_traffic_statistic_counter,"aw",@nobits
	.align	2
	.type	LC_traffic_statistic_counter, @object
	.size	LC_traffic_statistic_counter, 4
LC_traffic_statistic_counter:
	.zero	4
	.section	.sbss.LC_ReTx_times,"aw",@nobits
	.align	2
	.type	LC_ReTx_times, @object
	.size	LC_ReTx_times, 4
LC_ReTx_times:
	.zero	4
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 4 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 6 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.file 7 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_bt_mode.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x470
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x10
	.4byte	.LASF81
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
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x11
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0x22
	.byte	0x15
	.4byte	0x34
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x2
	.byte	0x25
	.byte	0x13
	.4byte	0x42
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x3
	.byte	0x50
	.byte	0xe
	.4byte	0xf9
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x8
	.byte	0
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF27
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x31
	.byte	0x1
	.4byte	0x13d
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
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x7
	.byte	0
	.uleb128 0xa
	.4byte	0x92
	.4byte	0x14d
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x6
	.byte	0x6
	.byte	0x5
	.byte	0xf8
	.4byte	0x170
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0x5
	.byte	0xf9
	.byte	0xd
	.4byte	0x92
	.byte	0
	.uleb128 0x2
	.4byte	.LASF37
	.byte	0x5
	.byte	0xfa
	.byte	0xd
	.4byte	0x13d
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF38
	.byte	0x5
	.byte	0xfb
	.byte	0x1e
	.4byte	0x14d
	.uleb128 0x12
	.byte	0x5
	.byte	0x5
	.2byte	0x102
	.byte	0x9
	.4byte	0x1a1
	.uleb128 0xc
	.4byte	.LASF39
	.2byte	0x103
	.byte	0xe
	.4byte	0x1a1
	.byte	0
	.uleb128 0xc
	.4byte	.LASF40
	.2byte	0x104
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.byte	0
	.uleb128 0xa
	.4byte	0x9e
	.4byte	0x1b1
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.4byte	.LASF41
	.byte	0x5
	.2byte	0x105
	.byte	0x1f
	.4byte	0x17c
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0x6e
	.byte	0xe
	.4byte	0x1e3
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.byte	0x14
	.byte	0x7
	.byte	0x39
	.4byte	0x22b
	.uleb128 0x5
	.string	"ms"
	.byte	0x3a
	.byte	0xe
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x7
	.byte	0x3b
	.byte	0xe
	.4byte	0xaa
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x7
	.byte	0x3c
	.byte	0xe
	.4byte	0xaa
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF48
	.byte	0x7
	.byte	0x3d
	.byte	0xe
	.4byte	0xaa
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x7
	.byte	0x3e
	.byte	0xe
	.4byte	0xaa
	.byte	0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF50
	.byte	0x7
	.byte	0x3f
	.byte	0x2
	.4byte	0x1e3
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.byte	0x41
	.4byte	0x259
	.uleb128 0x5
	.string	"LEN"
	.byte	0x42
	.byte	0xe
	.4byte	0x9e
	.byte	0
	.uleb128 0x2
	.4byte	.LASF51
	.byte	0x7
	.byte	0x43
	.byte	0xe
	.4byte	0x9e
	.byte	0x2
	.byte	0
	.uleb128 0x4
	.4byte	.LASF52
	.byte	0x7
	.byte	0x44
	.byte	0x2
	.4byte	0x237
	.uleb128 0x6
	.byte	0x3
	.byte	0x7
	.byte	0x46
	.4byte	0x288
	.uleb128 0x2
	.4byte	.LASF53
	.byte	0x7
	.byte	0x47
	.byte	0xd
	.4byte	0x92
	.byte	0
	.uleb128 0x2
	.4byte	.LASF54
	.byte	0x7
	.byte	0x48
	.byte	0xe
	.4byte	0x9e
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF55
	.byte	0x7
	.byte	0x49
	.byte	0xa
	.4byte	0x265
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.byte	0x4b
	.4byte	0x2d1
	.uleb128 0x5
	.string	"k"
	.byte	0x4c
	.byte	0xe
	.4byte	0x9e
	.byte	0
	.uleb128 0x5
	.string	"x"
	.byte	0x4d
	.byte	0xd
	.4byte	0x86
	.byte	0x2
	.uleb128 0x5
	.string	"y"
	.byte	0x4e
	.byte	0xd
	.4byte	0x86
	.byte	0x4
	.uleb128 0x5
	.string	"z1"
	.byte	0x4f
	.byte	0xc
	.4byte	0x7a
	.byte	0x6
	.uleb128 0x5
	.string	"z2"
	.byte	0x50
	.byte	0xc
	.4byte	0x7a
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF56
	.byte	0x7
	.byte	0x51
	.byte	0xa
	.4byte	0x294
	.uleb128 0x14
	.byte	0x8
	.byte	0x7
	.byte	0x67
	.byte	0x5
	.4byte	0x308
	.uleb128 0x8
	.4byte	.LASF57
	.byte	0x68
	.byte	0x22
	.4byte	0x2d1
	.uleb128 0x8
	.4byte	.LASF58
	.byte	0x69
	.byte	0x24
	.4byte	0x170
	.uleb128 0x8
	.4byte	.LASF59
	.byte	0x6a
	.byte	0x29
	.4byte	0x1b1
	.byte	0
	.uleb128 0x6
	.byte	0xf
	.byte	0x7
	.byte	0x64
	.4byte	0x330
	.uleb128 0x2
	.4byte	.LASF60
	.byte	0x7
	.byte	0x65
	.byte	0x16
	.4byte	0x259
	.byte	0
	.uleb128 0x5
	.string	"att"
	.byte	0x66
	.byte	0x14
	.4byte	0x288
	.byte	0x4
	.uleb128 0x15
	.4byte	0x2dd
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF61
	.byte	0x7
	.byte	0x75
	.byte	0xa
	.4byte	0x308
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.byte	0x7d
	.4byte	0x3ad
	.uleb128 0x2
	.4byte	.LASF62
	.byte	0x7
	.byte	0x7e
	.byte	0xd
	.4byte	0x92
	.byte	0
	.uleb128 0x2
	.4byte	.LASF63
	.byte	0x7
	.byte	0x7f
	.byte	0xd
	.4byte	0x92
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF64
	.byte	0x7
	.byte	0x80
	.byte	0xd
	.4byte	0x92
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF65
	.byte	0x7
	.byte	0x81
	.byte	0xd
	.4byte	0x92
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF66
	.byte	0x7
	.byte	0x82
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF67
	.byte	0x7
	.byte	0x83
	.byte	0xd
	.4byte	0x92
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF68
	.byte	0x7
	.byte	0x84
	.byte	0xd
	.4byte	0x92
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF69
	.byte	0x7
	.byte	0x85
	.byte	0xd
	.4byte	0x92
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF70
	.byte	0x7
	.byte	0x86
	.byte	0x3
	.4byte	0x33c
	.uleb128 0xd
	.4byte	.LASF74
	.byte	0x7
	.byte	0x88
	.byte	0x15
	.4byte	0x3ad
	.uleb128 0x9
	.4byte	.LASF71
	.byte	0x32
	.byte	0x11
	.4byte	0xaa
	.uleb128 0x5
	.byte	0x3
	.4byte	LC_ReTx_times
	.uleb128 0x9
	.4byte	.LASF72
	.byte	0x33
	.byte	0x11
	.4byte	0xaa
	.uleb128 0x5
	.byte	0x3
	.4byte	LC_traffic_statistic_counter
	.uleb128 0x9
	.4byte	.LASF73
	.byte	0x35
	.byte	0x10
	.4byte	0x92
	.uleb128 0x5
	.byte	0x3
	.4byte	last_ms_key
	.uleb128 0xe
	.4byte	.LASF75
	.byte	0x38
	.4byte	0xaa
	.uleb128 0x5
	.byte	0x3
	.4byte	LC_burst_tx_number
	.uleb128 0xe
	.4byte	.LASF76
	.byte	0x39
	.4byte	0xaa
	.uleb128 0x5
	.byte	0x3
	.4byte	outgoing_buffer_avail
	.uleb128 0xd
	.4byte	.LASF77
	.byte	0x1
	.byte	0x3b
	.byte	0x21
	.4byte	0x22b
	.uleb128 0x16
	.4byte	.LASF82
	.byte	0x1
	.byte	0x45
	.byte	0xa
	.4byte	0xaa
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x46d
	.uleb128 0xf
	.4byte	.LASF78
	.byte	0x45
	.byte	0x35
	.4byte	0x46d
	.4byte	.LLST0
	.uleb128 0xf
	.4byte	.LASF79
	.byte	0x45
	.byte	0x46
	.4byte	0xaa
	.4byte	.LLST1
	.uleb128 0x17
	.4byte	.LASF80
	.byte	0x1
	.byte	0x47
	.byte	0xe
	.4byte	0xaa
	.4byte	.LLST2
	.byte	0
	.uleb128 0x18
	.byte	0x4
	.4byte	0x330
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
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
	.uleb128 0x6
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
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
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
	.uleb128 0xe
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
	.sleb128 10
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0x17
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
	.uleb128 0x15
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 .LVL6-.LVL0
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL6-.LVL0
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
	.uleb128 .LVL10-.LVL0
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
	.uleb128 .LVL10-.LVL0
	.uleb128 .LVL11-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL11-.LVL0
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
.LLST2:
	.byte	0x6
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL3-.LVL1
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL3-.LVL1
	.uleb128 .LVL4-.LVL1
	.uleb128 0x6
	.byte	0x7d
	.sleb128 0
	.byte	0x7b
	.sleb128 0
	.byte	0x1c
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL4-.LVL1
	.uleb128 .LVL5-.LVL1
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL8-.LVL1
	.uleb128 .LVL9-.LVL1
	.uleb128 0x1
	.byte	0x5f
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
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF57:
	.string	"ms_hid"
.LASF44:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF42:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF6:
	.string	"short int"
.LASF67:
	.string	"controller_full_print"
.LASF39:
	.string	"consumer"
.LASF32:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF48:
	.string	"game_controller"
.LASF21:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF22:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF37:
	.string	"keycode"
.LASF34:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF63:
	.string	"controller_full"
.LASF15:
	.string	"uint8_t"
.LASF18:
	.string	"DBG_PIN_SPI_CB"
.LASF47:
	.string	"kb_csm"
.LASF41:
	.string	"T_REPORT_KB_CONSUMER2_PAYLOAD_S"
.LASF13:
	.string	"int8_t"
.LASF11:
	.string	"long double"
.LASF10:
	.string	"long long int"
.LASF38:
	.string	"T_REPORT_KB_STD5_PAYLOAD_S"
.LASF12:
	.string	"char"
.LASF68:
	.string	"drop_data_print"
.LASF31:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF24:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF69:
	.string	"LC_burst_tx_number_10_print"
.LASF40:
	.string	"numeric_key_pad"
.LASF61:
	.string	"T_BT_HID_REPORT_S"
.LASF72:
	.string	"LC_traffic_statistic_counter"
.LASF73:
	.string	"last_ms_key"
.LASF66:
	.string	"tx_buffer_full_print"
.LASF5:
	.string	"unsigned char"
.LASF58:
	.string	"kb_std5"
.LASF36:
	.string	"combo"
.LASF4:
	.string	"signed char"
.LASF2:
	.string	"long long unsigned int"
.LASF78:
	.string	"report"
.LASF17:
	.string	"uint32_t"
.LASF65:
	.string	"LC_burst_tx_number_10"
.LASF3:
	.string	"unsigned int"
.LASF28:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF16:
	.string	"uint16_t"
.LASF29:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF25:
	.string	"DBG_PIN_USB_TX"
.LASF45:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF7:
	.string	"short unsigned int"
.LASF19:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF71:
	.string	"LC_ReTx_times"
.LASF46:
	.string	"kb_std"
.LASF82:
	.string	"rv_bt_burst_tx_num_ctrl"
.LASF8:
	.string	"long int"
.LASF56:
	.string	"T_MOUSE_REPORT_PAYLOAD_S"
.LASF14:
	.string	"int16_t"
.LASF74:
	.string	"bt_debug"
.LASF27:
	.string	"_Bool"
.LASF54:
	.string	"ATTRIBUTE_HANDLE"
.LASF62:
	.string	"tx_buffer_full"
.LASF64:
	.string	"drop_data"
.LASF70:
	.string	"T_BT_DEBUG_S"
.LASF77:
	.string	"attr_handle"
.LASF30:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF43:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF9:
	.string	"long unsigned int"
.LASF55:
	.string	"T_ATT_HEADER_S"
.LASF60:
	.string	"l2cap"
.LASF49:
	.string	"kb_nkey"
.LASF75:
	.string	"LC_burst_tx_number"
.LASF50:
	.string	"T_ATT_ATTRIBUTE_HANDLE_S"
.LASF33:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF23:
	.string	"DBG_PIN_USB_SOF"
.LASF81:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF52:
	.string	"T_L2CAP_HEADER_S"
.LASF76:
	.string	"outgoing_buffer_avail"
.LASF35:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF20:
	.string	"DBG_PIN_NACK"
.LASF59:
	.string	"kb_consumer2"
.LASF80:
	.string	"LC_queued_tx_pkt_num"
.LASF51:
	.string	"CH_ID"
.LASF26:
	.string	"DBG_PIN_MAX"
.LASF79:
	.string	"buf_avail_num"
.LASF53:
	.string	"OPCODE"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/rv_burst_tx_buf_ctrl.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
