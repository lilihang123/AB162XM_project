	.file	"key_remap_frontend.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/key_remap/src/key_remap_frontend.c"
	.section	.text.key_remap_frontend_process_xy,"ax",@progbits
	.align	1
	.globl	key_remap_frontend_process_xy
	.hidden	key_remap_frontend_process_xy
	.type	key_remap_frontend_process_xy, @function
key_remap_frontend_process_xy:
.LFB6:
	.file 1 "/workdir/airoha/common/middleware/airoha/key_remap/src/key_remap_frontend.c"
	.loc 1 97 1
	.cfi_startproc
.LVL0:
	.loc 1 98 5
	tail	key_remap_xy_pop
.LVL1:
	.cfi_endproc
.LFE6:
	.size	key_remap_frontend_process_xy, .-key_remap_frontend_process_xy
	.section	.text.key_remap_frontend_process,"ax",@progbits
	.align	1
	.globl	key_remap_frontend_process
	.hidden	key_remap_frontend_process
	.type	key_remap_frontend_process, @function
key_remap_frontend_process:
.LFB7:
	.loc 1 102 1
	.cfi_startproc
.LVL2:
	.loc 1 103 5
	.loc 1 103 14 is_stmt 0
	lw	a2,4(a0)
.LVL3:
	.loc 1 104 5 is_stmt 1
	.loc 1 104 34 is_stmt 0
	lw	a4,kr_ctrl
	.loc 1 104 66
	ori	a5,a4,224
	.loc 1 104 14
	and	a5,a5,a2
.LVL4:
	.loc 1 109 5 is_stmt 1
	.loc 1 109 9 is_stmt 0
	lw	a3,16(a0)
.LVL5:
	.loc 1 113 5 is_stmt 1
	.loc 1 102 1 is_stmt 0
	mv	a1,a0
	.loc 1 113 7
	beq	a5,zero,.L3
	.loc 1 115 9 is_stmt 1
	.loc 1 115 24 is_stmt 0
	not	a5,a5
.LVL6:
	.loc 1 115 21
	and	a5,a5,a2
.LVL7:
	sw	a5,4(a0)
.L3:
	.loc 1 125 5 is_stmt 1
	.loc 1 125 7 is_stmt 0
	slli	a5,a4,1
	bge	a5,zero,.L4
	.loc 1 125 56 discriminator 1
	bgt	a3,zero,.L5
.L4:
	.loc 1 125 72 discriminator 3
	bge	a4,zero,.L6
	.loc 1 126 53
	bge	a3,zero,.L6
.L5:
	.loc 1 129 9 is_stmt 1
	.loc 1 129 22 is_stmt 0
	sw	zero,16(a1)
.L6:
	.loc 1 134 5 is_stmt 1
	lla	a0,Kr_q_Ctrl
.LVL8:
	tail	key_remap_queue_pop
.LVL9:
	.cfi_endproc
.LFE7:
	.size	key_remap_frontend_process, .-key_remap_frontend_process
	.section	.text.key_remap_frontend_setting_update,"ax",@progbits
	.align	1
	.globl	key_remap_frontend_setting_update
	.hidden	key_remap_frontend_setting_update
	.type	key_remap_frontend_setting_update, @function
key_remap_frontend_setting_update:
.LFB8:
	.loc 1 172 1
	.cfi_startproc
	.loc 1 174 5
	.loc 1 174 47 is_stmt 0
	lw	a5,hid_common
	.loc 1 174 30
	lw	a5,24(a5)
	.loc 1 172 1
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	s1,0(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 174 30
	sw	a5,kr_ctrl,a4
	.loc 1 179 5 is_stmt 1
.LBB2:
	.loc 1 179 9
.LVL10:
	.loc 1 179 27 discriminator 1
	.loc 1 179 18 is_stmt 0
	li	s0,0
	.loc 1 181 9
	lla	s1,key_setting
.LVL11:
.L15:
	.loc 1 181 9 is_stmt 1
	slli	a0,s0,3
	andi	a1,s0,0xff
	add	a0,s1,a0
	call	hid_common_get_frontend_key_remap_data
.LVL12:
	.loc 1 179 34 discriminator 3
	addi	s0,s0,1
.LVL13:
	.loc 1 179 27 discriminator 1
	li	a5,10
	bne	s0,a5,.L15
.LBE2:
	.loc 1 183 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL14:
	lw	s1,0(sp)
	.cfi_restore 9
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE8:
	.size	key_remap_frontend_setting_update, .-key_remap_frontend_setting_update
	.section	.text.key_remap_frontend_init,"ax",@progbits
	.align	1
	.globl	key_remap_frontend_init
	.hidden	key_remap_frontend_init
	.type	key_remap_frontend_init, @function
key_remap_frontend_init:
.LFB9:
	.loc 1 186 1 is_stmt 1
	.cfi_startproc
	.loc 1 187 5
	.loc 1 186 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 187 5
	li	a2,4
	li	a1,0
	lla	a0,kr_ctrl
	.loc 1 186 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 187 5
	call	memset
.LVL15:
	.loc 1 188 5 is_stmt 1
	lla	a0,Kr_q_Ctrl
	call	key_remap_queue_init
.LVL16:
	.loc 1 191 5
	lla	a0,Kr_q_Ctrl
	call	key_remap_set_queue
.LVL17:
	.loc 1 200 5
	.loc 1 201 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 200 5
	tail	key_remap_frontend_setting_update
.LVL18:
	.cfi_endproc
.LFE9:
	.size	key_remap_frontend_init, .-key_remap_frontend_init
	.hidden	key_setting
	.globl	key_setting
	.section	.bss.key_setting,"aw",@nobits
	.align	2
	.type	key_setting, @object
	.size	key_setting, 80
key_setting:
	.zero	80
	.hidden	Kr_q_Ctrl
	.globl	Kr_q_Ctrl
	.section	.bss.Kr_q_Ctrl,"aw",@nobits
	.align	2
	.type	Kr_q_Ctrl, @object
	.size	Kr_q_Ctrl, 104
Kr_q_Ctrl:
	.zero	104
	.section	.sbss.kr_ctrl,"aw",@nobits
	.align	2
	.type	kr_ctrl, @object
	.size	kr_ctrl, 4
kr_ctrl:
	.zero	4
	.hidden	log_control_block_mirror_kr_frontend
	.globl	log_control_block_mirror_kr_frontend
	.section	.log_filter_mirror.kr_frontend,"a"
	.align	2
	.type	log_control_block_mirror_kr_frontend, @object
	.size	log_control_block_mirror_kr_frontend, 12
log_control_block_mirror_kr_frontend:
	.string	"kr_frontend"
	.hidden	log_control_block_kr_frontend
	.globl	log_control_block_kr_frontend
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"kr_frontend"
	.section	.log_filter.kr_frontend,"aw"
	.align	2
	.type	log_control_block_kr_frontend, @object
	.size	log_control_block_kr_frontend, 28
log_control_block_kr_frontend:
	.word	.LC0
	.word	0
	.word	1
	.word	0
	.word	0
	.word	0
	.word	print_module_msgid_log
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 6 "/workdir/airoha/common/applications/hid/inc/hid_common_key_remap.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 8 "/workdir/airoha/common/applications/hid/inc/hid_common.h"
	.file 9 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 10 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 11 "/workdir/airoha/common/middleware/airoha/key_remap/inc/key_remap_queue.h"
	.file 12 "/workdir/airoha/common/middleware/airoha/key_remap/inc/key_remap_backend.h"
	.file 13 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xd49
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x1e
	.4byte	.LASF168
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL6
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0xa
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0xa
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0xa
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0xa
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0xa
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0xa
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0xa
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0xa
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0xa
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x1f
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0xa
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x20
	.byte	0x4
	.uleb128 0xa
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x12
	.4byte	0x81
	.uleb128 0x7
	.4byte	0x88
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x3
	.byte	0x22
	.byte	0x15
	.4byte	0x34
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x3
	.byte	0x25
	.byte	0x13
	.4byte	0x42
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x3
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x4
	.4byte	.LASF18
	.byte	0x3
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x4
	.4byte	.LASF19
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x21
	.4byte	0xce
	.uleb128 0x8
	.4byte	0xb6
	.4byte	0xef
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x8
	.4byte	0xce
	.4byte	0xff
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x4
	.byte	0x50
	.byte	0xe
	.4byte	0x142
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0
	.uleb128 0x2
	.4byte	.LASF21
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF22
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF23
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF24
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF25
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF26
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF27
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF28
	.byte	0x8
	.byte	0
	.uleb128 0x6
	.byte	0xa
	.byte	0x4
	.byte	0x5e
	.4byte	0x165
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x4
	.byte	0x60
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x5
	.string	"pin"
	.byte	0x4
	.byte	0x61
	.byte	0xd
	.4byte	0x165
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0xb6
	.4byte	0x175
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF30
	.byte	0x4
	.byte	0x62
	.byte	0x2
	.4byte	0x142
	.uleb128 0xa
	.byte	0x1
	.byte	0x2
	.4byte	.LASF31
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x5
	.byte	0x31
	.byte	0x1
	.4byte	0x1c5
	.uleb128 0x2
	.4byte	.LASF32
	.byte	0
	.uleb128 0x2
	.4byte	.LASF33
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF34
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF35
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF37
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF38
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF39
	.byte	0x7
	.byte	0
	.uleb128 0x6
	.byte	0x2
	.byte	0x5
	.byte	0x3f
	.4byte	0x1e8
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x5
	.byte	0x41
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x5
	.byte	0x42
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF42
	.byte	0x5
	.byte	0x44
	.byte	0x2
	.4byte	0x1c5
	.uleb128 0x6
	.byte	0x14
	.byte	0x6
	.byte	0xf5
	.4byte	0x231
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x6
	.byte	0xf6
	.byte	0xe
	.4byte	0xce
	.byte	0
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x6
	.byte	0xf7
	.byte	0xd
	.4byte	0xaa
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x6
	.byte	0xf8
	.byte	0xe
	.4byte	0xef
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x6
	.byte	0xf9
	.byte	0xe
	.4byte	0xce
	.byte	0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF47
	.byte	0x6
	.byte	0xff
	.byte	0x2
	.4byte	0x1f4
	.uleb128 0x16
	.2byte	0x11c
	.2byte	0x109
	.byte	0xd
	.4byte	0x261
	.uleb128 0x17
	.4byte	.LASF48
	.2byte	0x10a
	.byte	0x1a
	.4byte	0x261
	.uleb128 0x22
	.string	"x_y"
	.byte	0x6
	.2byte	0x10c
	.byte	0x1a
	.4byte	0x261
	.byte	0
	.uleb128 0x8
	.4byte	0xce
	.4byte	0x271
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x46
	.byte	0
	.uleb128 0x18
	.2byte	0x23c
	.2byte	0x105
	.4byte	0x2a9
	.uleb128 0xc
	.4byte	.LASF49
	.2byte	0x106
	.byte	0x16
	.4byte	0xc2
	.byte	0
	.uleb128 0xc
	.4byte	.LASF50
	.2byte	0x107
	.byte	0x16
	.4byte	0xc2
	.byte	0x2
	.uleb128 0xc
	.4byte	.LASF51
	.2byte	0x108
	.byte	0x16
	.4byte	0x261
	.byte	0x4
	.uleb128 0x23
	.4byte	0x23d
	.2byte	0x120
	.byte	0
	.uleb128 0x16
	.2byte	0x23c
	.2byte	0x103
	.byte	0x5
	.4byte	0x2c5
	.uleb128 0x17
	.4byte	.LASF52
	.2byte	0x104
	.byte	0x12
	.4byte	0xce
	.uleb128 0x24
	.4byte	0x271
	.byte	0
	.uleb128 0x18
	.2byte	0x240
	.2byte	0x101
	.4byte	0x2e2
	.uleb128 0xc
	.4byte	.LASF53
	.2byte	0x102
	.byte	0xe
	.4byte	0xce
	.byte	0
	.uleb128 0x19
	.4byte	0x2a9
	.byte	0x4
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF54
	.2byte	0x111
	.4byte	0x2c5
	.uleb128 0x25
	.byte	0x8
	.byte	0x6
	.2byte	0x125
	.byte	0x9
	.4byte	0x312
	.uleb128 0xc
	.4byte	.LASF53
	.2byte	0x126
	.byte	0xe
	.4byte	0xce
	.byte	0
	.uleb128 0xc
	.4byte	.LASF52
	.2byte	0x127
	.byte	0xe
	.4byte	0xce
	.byte	0x4
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF55
	.2byte	0x128
	.4byte	0x2ed
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.byte	0x50
	.4byte	0x36c
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x7
	.byte	0x51
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x5
	.string	"k"
	.byte	0x7
	.byte	0x52
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x5
	.string	"x"
	.byte	0x7
	.byte	0x53
	.byte	0xd
	.4byte	0x9e
	.byte	0x2
	.uleb128 0x5
	.string	"y"
	.byte	0x7
	.byte	0x54
	.byte	0xd
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x5
	.string	"z1"
	.byte	0x7
	.byte	0x55
	.byte	0xc
	.4byte	0x92
	.byte	0x6
	.uleb128 0x5
	.string	"z2"
	.byte	0x7
	.byte	0x56
	.byte	0xc
	.4byte	0x92
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF57
	.byte	0x7
	.byte	0x57
	.byte	0x1f
	.4byte	0x31d
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.byte	0x88
	.4byte	0x3be
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x7
	.byte	0x89
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x7
	.byte	0x8a
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x7
	.byte	0x8b
	.byte	0xd
	.4byte	0xdf
	.byte	0x2
	.uleb128 0x5
	.string	"x"
	.byte	0x7
	.byte	0x8c
	.byte	0xd
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x5
	.string	"y"
	.byte	0x7
	.byte	0x8d
	.byte	0xd
	.4byte	0x9e
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF59
	.byte	0x7
	.byte	0x8e
	.byte	0x1e
	.4byte	0x378
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.byte	0x90
	.4byte	0x410
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x7
	.byte	0x91
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x7
	.byte	0x92
	.byte	0xe
	.4byte	0xc2
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x7
	.byte	0x93
	.byte	0xd
	.4byte	0xb6
	.byte	0x3
	.uleb128 0x5
	.string	"x"
	.byte	0x7
	.byte	0x94
	.byte	0xd
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x5
	.string	"y"
	.byte	0x7
	.byte	0x95
	.byte	0xd
	.4byte	0x9e
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF62
	.byte	0x7
	.byte	0x96
	.byte	0x1f
	.4byte	0x3ca
	.uleb128 0x8
	.4byte	0xb6
	.4byte	0x42c
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.byte	0xa2
	.4byte	0x469
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x7
	.byte	0xa3
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x7
	.byte	0xa4
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x7
	.byte	0xa5
	.byte	0xd
	.4byte	0x41c
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x7
	.byte	0xa6
	.byte	0xd
	.4byte	0xb6
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF64
	.byte	0x7
	.byte	0xa7
	.byte	0x1e
	.4byte	0x42c
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.byte	0xa9
	.4byte	0x4b2
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x7
	.byte	0xaa
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x7
	.byte	0xab
	.byte	0xd
	.4byte	0x4b2
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x7
	.byte	0xac
	.byte	0xd
	.4byte	0xb6
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x7
	.byte	0xad
	.byte	0xd
	.4byte	0xdf
	.byte	0x6
	.byte	0
	.uleb128 0x8
	.4byte	0xb6
	.4byte	0x4c2
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF65
	.byte	0x7
	.byte	0xae
	.byte	0x1f
	.4byte	0x475
	.uleb128 0x8
	.4byte	0xb6
	.4byte	0x4de
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x6
	.byte	0x2
	.byte	0x8
	.byte	0x49
	.4byte	0x500
	.uleb128 0x5
	.string	"id"
	.byte	0x8
	.byte	0x4b
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x8
	.byte	0x4c
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF67
	.byte	0x8
	.byte	0x4d
	.byte	0x2
	.4byte	0x4de
	.uleb128 0x26
	.byte	0x8
	.byte	0x8
	.byte	0x53
	.byte	0x5
	.4byte	0x54d
	.uleb128 0xe
	.4byte	.LASF68
	.byte	0x54
	.byte	0x25
	.4byte	0x36c
	.uleb128 0xe
	.4byte	.LASF69
	.byte	0x56
	.byte	0x23
	.4byte	0x3be
	.uleb128 0xe
	.4byte	.LASF70
	.byte	0x57
	.byte	0x28
	.4byte	0x410
	.uleb128 0xe
	.4byte	.LASF71
	.byte	0x59
	.byte	0x20
	.4byte	0x469
	.uleb128 0xe
	.4byte	.LASF72
	.byte	0x5a
	.byte	0x25
	.4byte	0x4c2
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.byte	0x8
	.byte	0x4f
	.4byte	0x55c
	.uleb128 0x19
	.4byte	0x50c
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF73
	.byte	0x8
	.byte	0x5f
	.byte	0xa
	.4byte	0x54d
	.uleb128 0x6
	.byte	0x8
	.byte	0x8
	.byte	0x61
	.4byte	0x58b
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x8
	.byte	0x62
	.byte	0xe
	.4byte	0xce
	.byte	0
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x8
	.byte	0x63
	.byte	0xe
	.4byte	0xce
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF76
	.byte	0x8
	.byte	0x67
	.byte	0x2
	.4byte	0x568
	.uleb128 0x12
	.4byte	0x58b
	.uleb128 0x6
	.byte	0x3
	.byte	0x8
	.byte	0x69
	.4byte	0x5cc
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x8
	.byte	0x6a
	.byte	0xd
	.4byte	0xb6
	.byte	0
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x8
	.byte	0x6b
	.byte	0xd
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x8
	.byte	0x6c
	.byte	0xd
	.4byte	0xb6
	.byte	0x2
	.byte	0
	.uleb128 0x4
	.4byte	.LASF80
	.byte	0x8
	.byte	0x6d
	.byte	0x3
	.4byte	0x59c
	.uleb128 0x6
	.byte	0x18
	.byte	0x8
	.byte	0x7e
	.4byte	0x62f
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x8
	.byte	0x7f
	.byte	0xe
	.4byte	0xce
	.byte	0
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x8
	.byte	0x80
	.byte	0xe
	.4byte	0xce
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x8
	.byte	0x81
	.byte	0xe
	.4byte	0xce
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x8
	.byte	0x82
	.byte	0xe
	.4byte	0xce
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x8
	.byte	0x83
	.byte	0x17
	.4byte	0xda
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x8
	.byte	0x84
	.byte	0xd
	.4byte	0xb6
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF87
	.byte	0x8
	.byte	0x94
	.byte	0x3
	.4byte	0x5d8
	.uleb128 0x6
	.byte	0x40
	.byte	0x8
	.byte	0x96
	.4byte	0x6f9
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x8
	.byte	0x97
	.byte	0xe
	.4byte	0xce
	.byte	0
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x8
	.byte	0x98
	.byte	0xe
	.4byte	0xce
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x8
	.byte	0x9b
	.byte	0x1e
	.4byte	0x6f9
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x8
	.byte	0x9c
	.byte	0xe
	.4byte	0xce
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x8
	.byte	0x9d
	.byte	0xe
	.4byte	0xce
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x8
	.byte	0x9f
	.byte	0x1e
	.4byte	0x500
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x8
	.byte	0xa0
	.byte	0x1e
	.4byte	0x500
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x8
	.byte	0xa5
	.byte	0xe
	.4byte	0xce
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x8
	.byte	0xa6
	.byte	0xe
	.4byte	0xce
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x8
	.byte	0xae
	.byte	0xe
	.4byte	0x6fe
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x8
	.byte	0xb1
	.byte	0xd
	.4byte	0x4ce
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x8
	.byte	0xb2
	.byte	0xd
	.4byte	0xb6
	.byte	0x38
	.uleb128 0x5
	.string	"rr"
	.byte	0x8
	.byte	0xbb
	.byte	0x1d
	.4byte	0x1e8
	.byte	0x39
	.uleb128 0x5
	.string	"deb"
	.byte	0x8
	.byte	0xbd
	.byte	0x17
	.4byte	0x5cc
	.byte	0x3b
	.byte	0
	.uleb128 0x7
	.4byte	0x597
	.uleb128 0x8
	.4byte	0xc2
	.4byte	0x70e
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF99
	.byte	0x8
	.byte	0xbf
	.byte	0x3
	.4byte	0x63b
	.uleb128 0x27
	.2byte	0x16ec
	.byte	0x8
	.byte	0xc1
	.byte	0x9
	.4byte	0x767
	.uleb128 0x5
	.string	"app"
	.byte	0x8
	.byte	0xc3
	.byte	0x1b
	.4byte	0x70e
	.byte	0
	.uleb128 0x5
	.string	"hid"
	.byte	0x8
	.byte	0xc4
	.byte	0x1b
	.4byte	0x62f
	.byte	0x40
	.uleb128 0x5
	.string	"dbg"
	.byte	0x8
	.byte	0xc5
	.byte	0x17
	.4byte	0x175
	.byte	0x58
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x8
	.byte	0xc7
	.byte	0x17
	.4byte	0x767
	.byte	0x62
	.uleb128 0x28
	.4byte	.LASF101
	.byte	0x8
	.byte	0xca
	.byte	0x1d
	.4byte	0x777
	.2byte	0x16e2
	.byte	0
	.uleb128 0x8
	.4byte	0x2e2
	.4byte	0x777
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x8
	.4byte	0x55c
	.4byte	0x787
	.uleb128 0x9
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF102
	.byte	0x8
	.byte	0xcc
	.byte	0x3
	.4byte	0x71a
	.uleb128 0x29
	.4byte	.LASF148
	.byte	0x8
	.byte	0xd2
	.byte	0x19
	.4byte	0x79f
	.uleb128 0x7
	.4byte	0x787
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x9
	.byte	0x37
	.byte	0xe
	.4byte	0x7bd
	.uleb128 0x2
	.4byte	.LASF103
	.byte	0
	.uleb128 0x2
	.4byte	.LASF104
	.byte	0x1
	.byte	0
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x9
	.byte	0x3d
	.byte	0xe
	.4byte	0x7e2
	.uleb128 0x2
	.4byte	.LASF105
	.byte	0
	.uleb128 0x2
	.4byte	.LASF106
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF107
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF108
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF109
	.byte	0x9
	.byte	0x42
	.byte	0x3
	.4byte	0x7bd
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x9
	.byte	0x45
	.byte	0xe
	.4byte	0x855
	.uleb128 0x2
	.4byte	.LASF110
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF111
	.byte	0xf
	.uleb128 0x2
	.4byte	.LASF112
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF113
	.byte	0x11
	.uleb128 0x2
	.4byte	.LASF114
	.byte	0x12
	.uleb128 0x2
	.4byte	.LASF115
	.byte	0x13
	.uleb128 0x2
	.4byte	.LASF116
	.byte	0x1a
	.uleb128 0x2
	.4byte	.LASF117
	.byte	0x2f
	.uleb128 0x2
	.4byte	.LASF118
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF119
	.byte	0x31
	.uleb128 0x2
	.4byte	.LASF120
	.byte	0x32
	.uleb128 0x2
	.4byte	.LASF121
	.byte	0x33
	.uleb128 0x2
	.4byte	.LASF122
	.byte	0x34
	.uleb128 0x2
	.4byte	.LASF123
	.byte	0x35
	.uleb128 0x2
	.4byte	.LASF124
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF125
	.byte	0x9
	.byte	0x57
	.byte	0x3
	.4byte	0x7ee
	.uleb128 0x4
	.4byte	.LASF126
	.byte	0x9
	.byte	0x59
	.byte	0x10
	.4byte	0x86d
	.uleb128 0x7
	.4byte	0x872
	.uleb128 0x13
	.4byte	0x892
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x7e2
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF127
	.byte	0x9
	.byte	0x5a
	.byte	0x10
	.4byte	0x89e
	.uleb128 0x7
	.4byte	0x8a3
	.uleb128 0x13
	.4byte	0x8cd
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x7e2
	.uleb128 0x3
	.4byte	0x8cd
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x10
	.byte	0
	.uleb128 0x7
	.4byte	0x8d2
	.uleb128 0x2a
	.uleb128 0x4
	.4byte	.LASF128
	.byte	0x9
	.byte	0x5b
	.byte	0x10
	.4byte	0x8df
	.uleb128 0x7
	.4byte	0x8e4
	.uleb128 0x13
	.4byte	0x8ff
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x7e2
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x3
	.4byte	0xce
	.uleb128 0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF129
	.byte	0x9
	.byte	0x5c
	.byte	0x14
	.4byte	0x90b
	.uleb128 0x7
	.4byte	0x910
	.uleb128 0x2b
	.4byte	0xce
	.4byte	0x933
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x7e2
	.uleb128 0x3
	.4byte	0x855
	.uleb128 0x3
	.4byte	0x933
	.uleb128 0x3
	.4byte	0x938
	.byte	0
	.uleb128 0x7
	.4byte	0x8cd
	.uleb128 0x7
	.4byte	0xce
	.uleb128 0x6
	.byte	0x1c
	.byte	0x9
	.byte	0x5e
	.4byte	0x9a1
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x9
	.byte	0x5f
	.byte	0x11
	.4byte	0x8d
	.byte	0
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x9
	.byte	0x60
	.byte	0xe
	.4byte	0xce
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x9
	.byte	0x61
	.byte	0xe
	.4byte	0xce
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x9
	.byte	0x62
	.byte	0xf
	.4byte	0x861
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x9
	.byte	0x63
	.byte	0x15
	.4byte	0x892
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x9
	.byte	0x64
	.byte	0x12
	.4byte	0x8ff
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x9
	.byte	0x65
	.byte	0x10
	.4byte	0x8d3
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF137
	.byte	0x9
	.byte	0x66
	.byte	0x3
	.4byte	0x93d
	.uleb128 0x6
	.byte	0x28
	.byte	0xa
	.byte	0x8d
	.4byte	0xa23
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0xa
	.byte	0x8e
	.byte	0xe
	.4byte	0xce
	.byte	0
	.uleb128 0x5
	.string	"k"
	.byte	0xa
	.byte	0x8f
	.byte	0xe
	.4byte	0xce
	.byte	0x4
	.uleb128 0x5
	.string	"x"
	.byte	0xa
	.byte	0x90
	.byte	0xd
	.4byte	0xaa
	.byte	0x8
	.uleb128 0x5
	.string	"y"
	.byte	0xa
	.byte	0x91
	.byte	0xd
	.4byte	0xaa
	.byte	0xc
	.uleb128 0x5
	.string	"z1"
	.byte	0xa
	.byte	0x92
	.byte	0xd
	.4byte	0xaa
	.byte	0x10
	.uleb128 0x5
	.string	"z2"
	.byte	0xa
	.byte	0x93
	.byte	0xd
	.4byte	0xaa
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0xa
	.byte	0x94
	.byte	0xe
	.4byte	0xce
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0xa
	.byte	0x95
	.byte	0xe
	.4byte	0xef
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0xa
	.byte	0x96
	.byte	0xe
	.4byte	0xce
	.byte	0x24
	.byte	0
	.uleb128 0x4
	.4byte	.LASF140
	.byte	0xa
	.byte	0x9c
	.byte	0x2
	.4byte	0x9ad
	.uleb128 0x7
	.4byte	0xa23
	.uleb128 0x6
	.byte	0x18
	.byte	0xb
	.byte	0x53
	.4byte	0xa57
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0xb
	.byte	0x56
	.byte	0x16
	.4byte	0x231
	.byte	0
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0xb
	.byte	0x57
	.byte	0xe
	.4byte	0xce
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF143
	.byte	0xb
	.byte	0x58
	.byte	0x2
	.4byte	0xa34
	.uleb128 0x6
	.byte	0x68
	.byte	0xb
	.byte	0x5a
	.4byte	0xa93
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0xb
	.byte	0x5b
	.byte	0x18
	.4byte	0xa93
	.byte	0
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0xb
	.byte	0x5c
	.byte	0xe
	.4byte	0xce
	.byte	0x60
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0xb
	.byte	0x5d
	.byte	0xe
	.4byte	0xce
	.byte	0x64
	.byte	0
	.uleb128 0x8
	.4byte	0xa57
	.4byte	0xaa3
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF147
	.byte	0xb
	.byte	0x5e
	.byte	0x2
	.4byte	0xa63
	.uleb128 0x7
	.4byte	0xaa3
	.uleb128 0x11
	.4byte	.LASF149
	.byte	0x35
	.byte	0x51
	.4byte	0x9a1
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_kr_frontend
	.uleb128 0x8
	.4byte	0x88
	.4byte	0xad5
	.uleb128 0x9
	.4byte	0x2d
	.byte	0xb
	.byte	0
	.uleb128 0x12
	.4byte	0xac5
	.uleb128 0x11
	.4byte	.LASF150
	.byte	0x35
	.byte	0x81
	.4byte	0xad5
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_mirror_kr_frontend
	.uleb128 0x6
	.byte	0x4
	.byte	0x1
	.byte	0x39
	.4byte	0xb01
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x1
	.byte	0x3e
	.byte	0xe
	.4byte	0xce
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF151
	.byte	0x1
	.byte	0x43
	.byte	0x2
	.4byte	0xaeb
	.uleb128 0x2c
	.4byte	.LASF162
	.byte	0x1
	.byte	0x45
	.byte	0x24
	.4byte	0xb01
	.uleb128 0x5
	.byte	0x3
	.4byte	kr_ctrl
	.uleb128 0x11
	.4byte	.LASF152
	.byte	0x46
	.byte	0x16
	.4byte	0xaa3
	.uleb128 0x5
	.byte	0x3
	.4byte	Kr_q_Ctrl
	.uleb128 0x8
	.4byte	0x312
	.4byte	0xb40
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x11
	.4byte	.LASF153
	.byte	0x47
	.byte	0x1c
	.4byte	0xb30
	.uleb128 0x5
	.byte	0x3
	.4byte	key_setting
	.uleb128 0xf
	.4byte	.LASF154
	.byte	0xc
	.byte	0x53
	.4byte	0xb62
	.uleb128 0x3
	.4byte	0xaaf
	.byte	0
	.uleb128 0xf
	.4byte	.LASF155
	.byte	0xb
	.byte	0x66
	.4byte	0xb73
	.uleb128 0x3
	.4byte	0xaaf
	.byte	0
	.uleb128 0x2d
	.4byte	.LASF169
	.byte	0xd
	.byte	0x21
	.byte	0x8
	.4byte	0x7f
	.4byte	0xb93
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x6c
	.byte	0
	.uleb128 0xf
	.4byte	.LASF156
	.byte	0x8
	.byte	0xf4
	.4byte	0xba9
	.uleb128 0x3
	.4byte	0xba9
	.uleb128 0x3
	.4byte	0xb6
	.byte	0
	.uleb128 0x7
	.4byte	0x312
	.uleb128 0xf
	.4byte	.LASF157
	.byte	0xb
	.byte	0x67
	.4byte	0xbc4
	.uleb128 0x3
	.4byte	0xaaf
	.uleb128 0x3
	.4byte	0x7f
	.byte	0
	.uleb128 0xf
	.4byte	.LASF158
	.byte	0xb
	.byte	0x70
	.4byte	0xbd5
	.uleb128 0x3
	.4byte	0xa2f
	.byte	0
	.uleb128 0x2e
	.4byte	.LASF159
	.byte	0x9
	.2byte	0x129
	.byte	0xd
	.4byte	0xbf8
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x7e2
	.uleb128 0x3
	.4byte	0x8d
	.uleb128 0x3
	.4byte	0xce
	.uleb128 0x10
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF160
	.byte	0xb9
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc65
	.uleb128 0x14
	.4byte	.LVL15
	.4byte	0xb73
	.4byte	0xc2d
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	kr_ctrl
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x34
	.byte	0
	.uleb128 0x14
	.4byte	.LVL16
	.4byte	0xb62
	.4byte	0xc44
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	Kr_q_Ctrl
	.byte	0
	.uleb128 0x14
	.4byte	.LVL17
	.4byte	0xb51
	.4byte	0xc5b
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	Kr_q_Ctrl
	.byte	0
	.uleb128 0x2f
	.4byte	.LVL18
	.4byte	0xc65
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF161
	.byte	0xab
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xcad
	.uleb128 0x30
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.uleb128 0x31
	.string	"i"
	.byte	0x1
	.byte	0xb3
	.byte	0x12
	.4byte	0xce
	.4byte	.LLST5
	.uleb128 0x32
	.4byte	.LVL12
	.4byte	0xb93
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x7
	.byte	0x78
	.sleb128 0
	.byte	0x33
	.byte	0x24
	.byte	0x79
	.sleb128 0
	.byte	0x22
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x33
	.4byte	.LASF170
	.byte	0x1
	.byte	0x65
	.byte	0x6
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd13
	.uleb128 0x1c
	.4byte	.LASF167
	.byte	0x65
	.byte	0x36
	.4byte	0xa2f
	.4byte	.LLST1
	.uleb128 0x15
	.4byte	.LASF163
	.byte	0x67
	.byte	0xe
	.4byte	0xce
	.4byte	.LLST2
	.uleb128 0x15
	.4byte	.LASF164
	.byte	0x68
	.byte	0xe
	.4byte	0xce
	.4byte	.LLST3
	.uleb128 0x15
	.4byte	.LASF165
	.byte	0x6d
	.byte	0x9
	.4byte	0x65
	.4byte	.LLST4
	.uleb128 0x1d
	.4byte	.LVL9
	.4byte	0xbae
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	Kr_q_Ctrl
	.byte	0
	.byte	0
	.uleb128 0x34
	.4byte	.LASF166
	.byte	0x1
	.byte	0x60
	.byte	0x6
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1c
	.4byte	.LASF167
	.byte	0x60
	.byte	0x39
	.4byte	0xa2f
	.4byte	.LLST0
	.uleb128 0x1d
	.4byte	.LVL1
	.4byte	0xbc4
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
	.uleb128 0x2
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
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
	.uleb128 0xe
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
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
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x18
	.byte	0
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
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
	.uleb128 0x16
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 30
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x23
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x2a
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2b
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
	.uleb128 0x2c
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
	.uleb128 0x2d
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
	.uleb128 0x2e
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
	.uleb128 0x2f
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x82
	.uleb128 0x19
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x31
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
	.uleb128 0x32
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
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
	.uleb128 0x34
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
.LLST5:
	.byte	0x6
	.4byte	.LVL10
	.byte	0x4
	.uleb128 .LVL10-.LVL10
	.uleb128 .LVL11-.LVL10
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL11-.LVL10
	.uleb128 .LVL14-.LVL10
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL8-.LVL2
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL8-.LVL2
	.uleb128 .LVL9-1-.LVL2
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL9-1-.LVL2
	.uleb128 .LFE7-.LVL2
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
	.byte	0x8
	.4byte	.LVL3
	.uleb128 .LVL9-1-.LVL3
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL6-.LVL4
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL6-.LVL4
	.uleb128 .LVL7-.LVL4
	.uleb128 0x4
	.byte	0x7f
	.sleb128 0
	.byte	0x20
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL7-.LVL4
	.uleb128 .LVL9-1-.LVL4
	.uleb128 0x9
	.byte	0x7e
	.sleb128 0
	.byte	0x8
	.byte	0xe0
	.byte	0x21
	.byte	0x7c
	.sleb128 0
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST4:
	.byte	0x8
	.4byte	.LVL5
	.uleb128 .LVL9-1-.LVL5
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL0
	.byte	0x4
	.uleb128 .LVL0-.LVL0
	.uleb128 .LVL1-1-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL1-1-.LVL0
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
	.4byte	0x34
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
.LLRL6:
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF94:
	.string	"key_remap_enable"
.LASF73:
	.string	"T_HID_CCNI_USB_REPORT_S"
.LASF13:
	.string	"size_t"
.LASF89:
	.string	"combo_key_list"
.LASF20:
	.string	"DBG_PIN_SPI_CB"
.LASF30:
	.string	"T_COMMON_LA_DBG_S"
.LASF4:
	.string	"signed char"
.LASF68:
	.string	"ms_s16_z8"
.LASF163:
	.string	"new_key"
.LASF168:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF138:
	.string	"type"
.LASF118:
	.string	"LOG_TYPE_HCI_DATA"
.LASF36:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF135:
	.string	"tlv_dump_handle"
.LASF39:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF75:
	.string	"combo_bit_32_63"
.LASF110:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF82:
	.string	"dongle_scenario"
.LASF115:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF15:
	.string	"int16_t"
.LASF10:
	.string	"long long int"
.LASF142:
	.string	"ready"
.LASF145:
	.string	"buf_head"
.LASF92:
	.string	"irpt_ctrl"
.LASF46:
	.string	"kb_consumer"
.LASF95:
	.string	"key_remap_fn_key"
.LASF2:
	.string	"long long unsigned int"
.LASF40:
	.string	"rr_idx_2_4g"
.LASF57:
	.string	"T_HID_REPORT_MS_K8_S16_Z8_S"
.LASF158:
	.string	"key_remap_xy_pop"
.LASF33:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF132:
	.string	"print_level"
.LASF8:
	.string	"long int"
.LASF126:
	.string	"f_print_t"
.LASF100:
	.string	"mapped_data"
.LASF88:
	.string	"inActivity_timeout"
.LASF55:
	.string	"T_HID_KEY_REMAP_FRONTEND_S"
.LASF117:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF45:
	.string	"kb_std"
.LASF6:
	.string	"short int"
.LASF18:
	.string	"uint16_t"
.LASF127:
	.string	"f_dump_buffer_t"
.LASF38:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF148:
	.string	"hid_common"
.LASF76:
	.string	"T_AIR_COMBO_KEY_S"
.LASF59:
	.string	"T_HID_REPORT_KB_STD2_XY_S"
.LASF121:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF44:
	.string	"ms_z1"
.LASF63:
	.string	"dummy"
.LASF42:
	.string	"T_HID_REPORT_RATE_VAL_S"
.LASF156:
	.string	"hid_common_get_frontend_key_remap_data"
.LASF47:
	.string	"T_REMAP_VALUES_S"
.LASF54:
	.string	"T_HID_KEY_REMAP_S"
.LASF32:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF154:
	.string	"key_remap_set_queue"
.LASF131:
	.string	"log_switch"
.LASF50:
	.string	"repeat_times"
.LASF23:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF114:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF140:
	.string	"T_OUTGOING_VALUES_S"
.LASF120:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF9:
	.string	"long unsigned int"
.LASF69:
	.string	"kb_std2"
.LASF48:
	.string	"keycode"
.LASF71:
	.string	"kb_std5"
.LASF133:
	.string	"print_handle"
.LASF90:
	.string	"combo_key_list_size"
.LASF96:
	.string	"riscv_trigger_time"
.LASF62:
	.string	"T_HID_REPORT_KB_CONSUMER1_XY_S"
.LASF141:
	.string	"data"
.LASF7:
	.string	"short unsigned int"
.LASF108:
	.string	"PRINT_LEVEL_ERROR"
.LASF43:
	.string	"ms_k"
.LASF159:
	.string	"print_module_msgid_log"
.LASF119:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF167:
	.string	"outgoing"
.LASF165:
	.string	"new_z1"
.LASF107:
	.string	"PRINT_LEVEL_WARNING"
.LASF155:
	.string	"key_remap_queue_init"
.LASF125:
	.string	"log_type_t"
.LASF85:
	.string	"outgoing_report_ready"
.LASF84:
	.string	"features"
.LASF87:
	.string	"hid_shared_parameters"
.LASF152:
	.string	"Kr_q_Ctrl"
.LASF147:
	.string	"T_REMAP_QUEUE_CTRL_S"
.LASF27:
	.string	"DBG_PIN_USB_TX"
.LASF98:
	.string	"mouse_key_num"
.LASF161:
	.string	"key_remap_frontend_setting_update"
.LASF162:
	.string	"kr_ctrl"
.LASF52:
	.string	"item"
.LASF80:
	.string	"T_DEBOUNCE_PARA_S"
.LASF79:
	.string	"step_bt"
.LASF111:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF81:
	.string	"hid_scenario_type"
.LASF139:
	.string	"k_old"
.LASF56:
	.string	"report_id"
.LASF106:
	.string	"PRINT_LEVEL_INFO"
.LASF51:
	.string	"macro"
.LASF137:
	.string	"log_control_block_t"
.LASF97:
	.string	"mouse_key_list"
.LASF78:
	.string	"step_2_4g"
.LASF103:
	.string	"DEBUG_LOG_ON"
.LASF146:
	.string	"buf_tail"
.LASF170:
	.string	"key_remap_frontend_process"
.LASF31:
	.string	"_Bool"
.LASF16:
	.string	"int32_t"
.LASF5:
	.string	"unsigned char"
.LASF91:
	.string	"hold_timeout"
.LASF150:
	.string	"log_control_block_mirror_kr_frontend"
.LASF160:
	.string	"key_remap_frontend_init"
.LASF74:
	.string	"combo_bit_00_31"
.LASF41:
	.string	"rr_idx_usb"
.LASF166:
	.string	"key_remap_frontend_process_xy"
.LASF61:
	.string	"numeric_key_pad"
.LASF123:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF34:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF164:
	.string	"erase_bit"
.LASF124:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF143:
	.string	"T_REMAP_KEY_INFO_S"
.LASF19:
	.string	"uint32_t"
.LASF21:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF101:
	.string	"outgoing_report"
.LASF134:
	.string	"dump_handle"
.LASF11:
	.string	"long double"
.LASF70:
	.string	"kb_consumer1"
.LASF72:
	.string	"kb_consumer2"
.LASF12:
	.string	"char"
.LASF151:
	.string	"T_KEY_REMAP_FRONTEND_CTRL_S"
.LASF3:
	.string	"unsigned int"
.LASF136:
	.string	"msg_id_handle"
.LASF144:
	.string	"buffer"
.LASF66:
	.string	"para"
.LASF22:
	.string	"DBG_PIN_NACK"
.LASF77:
	.string	"step_wired"
.LASF102:
	.string	"hid_common_info"
.LASF14:
	.string	"int8_t"
.LASF122:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF35:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF49:
	.string	"play_mode"
.LASF105:
	.string	"PRINT_LEVEL_DEBUG"
.LASF130:
	.string	"module_name"
.LASF67:
	.string	"T_OUTPUT_CTRL_PIN_INFO_S"
.LASF58:
	.string	"combo"
.LASF169:
	.string	"memset"
.LASF129:
	.string	"f_tlv_dump_t"
.LASF53:
	.string	"status"
.LASF65:
	.string	"T_HID_REPORT_KB_CONSUMER2_S"
.LASF149:
	.string	"log_control_block_kr_frontend"
.LASF60:
	.string	"consumer"
.LASF17:
	.string	"uint8_t"
.LASF64:
	.string	"T_HID_REPORT_KB_STD5_S"
.LASF24:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF83:
	.string	"flags"
.LASF93:
	.string	"scroll_ctrl"
.LASF86:
	.string	"delay_for_key_polling_ms"
.LASF109:
	.string	"print_level_t"
.LASF28:
	.string	"DBG_PIN_MAX"
.LASF112:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF99:
	.string	"app_shared_parameters"
.LASF128:
	.string	"f_msg_id_t"
.LASF26:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF153:
	.string	"key_setting"
.LASF37:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF113:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF157:
	.string	"key_remap_queue_pop"
.LASF25:
	.string	"DBG_PIN_USB_SOF"
.LASF29:
	.string	"enable_mask"
.LASF116:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF104:
	.string	"DEBUG_LOG_OFF"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/key_remap/src/key_remap_frontend.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
