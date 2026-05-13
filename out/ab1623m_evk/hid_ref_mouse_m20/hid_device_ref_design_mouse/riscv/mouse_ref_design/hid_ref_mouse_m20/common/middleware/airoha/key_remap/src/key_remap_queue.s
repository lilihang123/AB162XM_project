	.file	"key_remap_queue.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/key_remap/src/key_remap_queue.c"
	.section	.text.key_remap_queue_init,"ax",@progbits
	.align	1
	.globl	key_remap_queue_init
	.hidden	key_remap_queue_init
	.type	key_remap_queue_init, @function
key_remap_queue_init:
.LFB8:
	.file 1 "/workdir/airoha/common/middleware/airoha/key_remap/src/key_remap_queue.c"
	.loc 1 86 1
	.cfi_startproc
.LVL0:
	.loc 1 87 5
	.loc 1 86 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 87 5
	li	a2,104
	li	a1,0
	.loc 1 86 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 87 5
	call	memset
.LVL1:
	.loc 1 89 5 is_stmt 1
	.loc 1 91 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 89 5
	li	a2,20
	.loc 1 91 1
	.loc 1 89 5
	li	a1,0
	lla	a0,Kr_xy_buf
	.loc 1 91 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	.loc 1 89 5
	tail	memset
.LVL2:
	.cfi_endproc
.LFE8:
	.size	key_remap_queue_init, .-key_remap_queue_init
	.section	.text.key_remap_xy_push,"ax",@progbits
	.align	1
	.globl	key_remap_xy_push
	.hidden	key_remap_xy_push
	.type	key_remap_xy_push, @function
key_remap_xy_push:
.LFB9:
	.loc 1 95 1 is_stmt 1
	.cfi_startproc
.LVL3:
	.loc 1 96 5
	.loc 1 97 5
	.loc 1 96 14 is_stmt 0
	lla	a3,Kr_xy_buf
	.loc 1 97 19
	lw	a5,16(a3)
	seqz	a5,a5
	.loc 1 97 30
	slli	a4,a5,3
	add	a4,a3,a4
	sw	a0,0(a4)
	.loc 1 98 5 is_stmt 1
	.loc 1 98 30 is_stmt 0
	sw	a1,4(a4)
	.loc 1 99 5 is_stmt 1
	.loc 1 99 24 is_stmt 0
	sw	a5,16(a3)
.LVL4:
	.loc 1 100 1
	ret
	.cfi_endproc
.LFE9:
	.size	key_remap_xy_push, .-key_remap_xy_push
	.section	.text.key_remap_xy_pop,"ax",@progbits
	.align	1
	.globl	key_remap_xy_pop
	.hidden	key_remap_xy_pop
	.type	key_remap_xy_pop, @function
key_remap_xy_pop:
.LFB10:
	.loc 1 103 1 is_stmt 1
	.cfi_startproc
.LVL5:
	.loc 1 104 5
	.loc 1 104 31 is_stmt 0
	lla	a5,Kr_xy_buf
	lw	a4,16(a5)
	.loc 1 104 39
	slli	a4,a4,3
	add	a5,a5,a4
	lw	a2,0(a5)
	.loc 1 104 76 discriminator 1
	lw	a3,4(a5)
	.loc 1 104 42 discriminator 1
	or	a4,a2,a3
	beq	a4,zero,.L4
	.loc 1 106 9 is_stmt 1
	.loc 1 106 26 is_stmt 0
	lw	a4,8(a0)
	add	a4,a4,a2
	sw	a4,8(a0)
	.loc 1 107 9 is_stmt 1
	.loc 1 107 26 is_stmt 0
	lw	a4,12(a0)
	add	a4,a4,a3
	sw	a4,12(a0)
	.loc 1 108 9 is_stmt 1
	.loc 1 108 43 is_stmt 0
	sw	zero,0(a5)
	.loc 1 109 9 is_stmt 1
	.loc 1 109 43 is_stmt 0
	sw	zero,4(a5)
	.loc 1 110 9 is_stmt 1
	.loc 1 110 34 is_stmt 0
	lw	a5,32(a0)
	li	a4,-2147483648
	or	a5,a5,a4
	sw	a5,32(a0)
.L4:
	.loc 1 112 1
	ret
	.cfi_endproc
.LFE10:
	.size	key_remap_xy_pop, .-key_remap_xy_pop
	.section	.text.key_remap_queue_pop,"ax",@progbits
	.align	1
	.globl	key_remap_queue_pop
	.hidden	key_remap_queue_pop
	.type	key_remap_queue_pop, @function
key_remap_queue_pop:
.LFB11:
	.loc 1 116 1 is_stmt 1
	.cfi_startproc
.LVL6:
	.loc 1 117 5
	.loc 1 119 5
.LBB5:
.LBB6:
	.loc 1 81 5
	.loc 1 81 44 is_stmt 0
	lw	a3,100(a0)
.LVL7:
.LBE6:
.LBE5:
	.loc 1 119 7 discriminator 1
	lw	a5,96(a0)
	beq	a5,a3,.L9
.LBB7:
	.loc 1 121 9 is_stmt 1
	.loc 1 121 86 is_stmt 0
	addi	a3,a3,1
	.loc 1 121 91
	andi	a3,a3,3
.LVL8:
	.loc 1 122 9 is_stmt 1
	.loc 1 124 9
	.loc 1 124 26 is_stmt 0
	slli	a4,a3,1
	add	a5,a4,a3
	slli	a5,a5,3
	add	a5,a0,a5
	.loc 1 124 11
	lw	a2,20(a5)
	beq	a2,zero,.L9
	.loc 1 140 13 is_stmt 1
	.loc 1 140 33 is_stmt 0
	lw	a2,8(a5)
	.loc 1 143 25
	lw	t1,0(a5)
	.loc 1 140 33
	sw	a2,28(a1)
	.loc 1 143 13 is_stmt 1
	.loc 1 143 25 is_stmt 0
	lw	a2,4(a1)
	or	a2,a2,t1
	sw	a2,4(a1)
	.loc 1 144 13 is_stmt 1
	.loc 1 144 33 is_stmt 0
	lw	t1,12(a5)
	lw	a2,32(a1)
	or	a2,a2,t1
	.loc 1 146 33
	lw	t1,4(a5)
	.loc 1 144 33
	sw	a2,32(a1)
	.loc 1 146 13 is_stmt 1
	.loc 1 146 15 is_stmt 0
	beq	t1,zero,.L11
	.loc 1 148 17 is_stmt 1
	.loc 1 148 30 is_stmt 0
	lw	a2,16(a1)
	add	a2,a2,t1
	sw	a2,16(a1)
	.loc 1 149 17 is_stmt 1
	.loc 1 149 42 is_stmt 0
	sw	zero,4(a5)
.L11:
	.loc 1 157 13 is_stmt 1
	.loc 1 157 54 is_stmt 0
	add	a5,a4,a3
	slli	a5,a5,3
	add	a5,a0,a5
	.loc 1 157 35
	lw	a4,16(a5)
	sw	a4,36(a1)
	.loc 1 159 13 is_stmt 1
	.loc 1 159 33 is_stmt 0
	sw	a3,100(a0)
	.loc 1 160 13 is_stmt 1
	.loc 1 160 35 is_stmt 0
	sw	zero,20(a5)
.LVL9:
.L9:
.LBE7:
	.loc 1 163 1
	ret
	.cfi_endproc
.LFE11:
	.size	key_remap_queue_pop, .-key_remap_queue_pop
	.section	.text.key_remap_queue_push,"ax",@progbits
	.align	1
	.globl	key_remap_queue_push
	.hidden	key_remap_queue_push
	.type	key_remap_queue_push, @function
key_remap_queue_push:
.LFB12:
	.loc 1 171 1 is_stmt 1
	.cfi_startproc
.LVL10:
	.loc 1 172 5
.LBB10:
.LBB11:
	.loc 1 74 5
	.loc 1 74 34 is_stmt 0
	lw	a5,96(a0)
.LBE11:
.LBE10:
	.loc 1 172 8 discriminator 1
	lw	a4,100(a0)
.LBB13:
.LBB12:
	.loc 1 74 34
	addi	a5,a5,1
	.loc 1 74 39
	andi	a5,a5,3
.LVL11:
.LBE12:
.LBE13:
	.loc 1 172 8 discriminator 1
	beq	a5,a4,.L18
	.loc 1 177 5 is_stmt 1
	slli	a4,a5,1
	.loc 1 187 41 is_stmt 0
	lw	a3,0(a1)
	.loc 1 177 25
	sw	a5,96(a0)
	.loc 1 178 5 is_stmt 1
.LVL12:
	.loc 1 179 5
	.loc 1 187 5
	add	a5,a4,a5
.LVL13:
	slli	a5,a5,3
	add	a0,a0,a5
.LVL14:
	.loc 1 187 26 is_stmt 0
	sw	a3,0(a0)
.LVL15:
	.loc 1 188 5 is_stmt 1
	.loc 1 188 42 is_stmt 0
	lw	a5,4(a1)
	.loc 1 188 27
	sw	a5,4(a0)
	.loc 1 191 5 is_stmt 1
	.loc 1 191 54 is_stmt 0
	lw	a5,8(a1)
	.loc 1 191 31
	sw	a5,8(a0)
	.loc 1 192 5 is_stmt 1
	.loc 1 192 54 is_stmt 0
	lw	a5,12(a1)
	.loc 1 192 31
	sw	a5,12(a0)
	.loc 1 195 5 is_stmt 1
	.loc 1 195 48 is_stmt 0
	lw	a5,16(a1)
	.loc 1 195 33
	sw	a5,16(a0)
	.loc 1 196 5 is_stmt 1
	.loc 1 196 27 is_stmt 0
	li	a5,1
	sw	a5,20(a0)
.LVL16:
.L18:
	.loc 1 197 1
	ret
	.cfi_endproc
.LFE12:
	.size	key_remap_queue_push, .-key_remap_queue_push
	.hidden	Kr_xy_buf
	.globl	Kr_xy_buf
	.section	.bss.Kr_xy_buf,"aw",@nobits
	.align	2
	.type	Kr_xy_buf, @object
	.size	Kr_xy_buf, 20
Kr_xy_buf:
	.zero	20
	.hidden	log_control_block_mirror_kr_q
	.globl	log_control_block_mirror_kr_q
	.section	.log_filter_mirror.kr_q,"a"
	.align	2
	.type	log_control_block_mirror_kr_q, @object
	.size	log_control_block_mirror_kr_q, 5
log_control_block_mirror_kr_q:
	.string	"kr_q"
	.hidden	log_control_block_kr_q
	.globl	log_control_block_kr_q
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"kr_q"
	.section	.log_filter.kr_q,"aw"
	.align	2
	.type	log_control_block_kr_q, @object
	.size	log_control_block_kr_q, 28
log_control_block_kr_q:
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
	.file 7 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 8 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 9 "/workdir/airoha/common/middleware/airoha/key_remap/inc/key_remap_queue.h"
	.file 10 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x786
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x18
	.4byte	.LASF102
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL10
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
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x5
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x5
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x5
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x19
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0x5
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x1a
	.byte	0x4
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x13
	.4byte	0x81
	.uleb128 0x6
	.4byte	0x88
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
	.uleb128 0xe
	.4byte	0x9e
	.4byte	0xba
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x4
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
	.uleb128 0x5
	.byte	0x1
	.byte	0x2
	.4byte	.LASF25
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x5
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
	.uleb128 0x8
	.byte	0x14
	.byte	0x6
	.byte	0xf5
	.4byte	0x17e
	.uleb128 0x3
	.4byte	.LASF34
	.byte	0x6
	.byte	0xf6
	.byte	0xe
	.4byte	0x9e
	.byte	0
	.uleb128 0x3
	.4byte	.LASF35
	.byte	0x6
	.byte	0xf7
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF36
	.byte	0x6
	.byte	0xf8
	.byte	0xe
	.4byte	0xaa
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF37
	.byte	0x6
	.byte	0xf9
	.byte	0xe
	.4byte	0x9e
	.byte	0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF38
	.byte	0x6
	.byte	0xff
	.byte	0x2
	.4byte	0x141
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x7
	.byte	0x37
	.byte	0xe
	.4byte	0x1a3
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x1
	.byte	0
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x7
	.byte	0x3d
	.byte	0xe
	.4byte	0x1c8
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF45
	.byte	0x7
	.byte	0x42
	.byte	0x3
	.4byte	0x1a3
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x7
	.byte	0x45
	.byte	0xe
	.4byte	0x23b
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF61
	.byte	0x7
	.byte	0x57
	.byte	0x3
	.4byte	0x1d4
	.uleb128 0x4
	.4byte	.LASF62
	.byte	0x7
	.byte	0x59
	.byte	0x10
	.4byte	0x253
	.uleb128 0x6
	.4byte	0x258
	.uleb128 0x11
	.4byte	0x278
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0x8d
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x1c8
	.uleb128 0x2
	.4byte	0x8d
	.uleb128 0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF63
	.byte	0x7
	.byte	0x5a
	.byte	0x10
	.4byte	0x284
	.uleb128 0x6
	.4byte	0x289
	.uleb128 0x11
	.4byte	0x2b3
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0x8d
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x1c8
	.uleb128 0x2
	.4byte	0x2b3
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x8d
	.uleb128 0x10
	.byte	0
	.uleb128 0x6
	.4byte	0x2b8
	.uleb128 0x1b
	.uleb128 0x4
	.4byte	.LASF64
	.byte	0x7
	.byte	0x5b
	.byte	0x10
	.4byte	0x2c5
	.uleb128 0x6
	.4byte	0x2ca
	.uleb128 0x11
	.4byte	0x2e5
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0x1c8
	.uleb128 0x2
	.4byte	0x8d
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF65
	.byte	0x7
	.byte	0x5c
	.byte	0x14
	.4byte	0x2f1
	.uleb128 0x6
	.4byte	0x2f6
	.uleb128 0x1c
	.4byte	0x9e
	.4byte	0x319
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0x1c8
	.uleb128 0x2
	.4byte	0x23b
	.uleb128 0x2
	.4byte	0x319
	.uleb128 0x2
	.4byte	0x31e
	.byte	0
	.uleb128 0x6
	.4byte	0x2b3
	.uleb128 0x6
	.4byte	0x9e
	.uleb128 0x8
	.byte	0x1c
	.byte	0x7
	.byte	0x5e
	.4byte	0x387
	.uleb128 0x3
	.4byte	.LASF66
	.byte	0x7
	.byte	0x5f
	.byte	0x11
	.4byte	0x8d
	.byte	0
	.uleb128 0x3
	.4byte	.LASF67
	.byte	0x7
	.byte	0x60
	.byte	0xe
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF68
	.byte	0x7
	.byte	0x61
	.byte	0xe
	.4byte	0x9e
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF69
	.byte	0x7
	.byte	0x62
	.byte	0xf
	.4byte	0x247
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF70
	.byte	0x7
	.byte	0x63
	.byte	0x15
	.4byte	0x278
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF71
	.byte	0x7
	.byte	0x64
	.byte	0x12
	.4byte	0x2e5
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF72
	.byte	0x7
	.byte	0x65
	.byte	0x10
	.4byte	0x2b9
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF73
	.byte	0x7
	.byte	0x66
	.byte	0x3
	.4byte	0x323
	.uleb128 0x8
	.byte	0x28
	.byte	0x8
	.byte	0x8d
	.4byte	0x409
	.uleb128 0x3
	.4byte	.LASF74
	.byte	0x8
	.byte	0x8e
	.byte	0xe
	.4byte	0x9e
	.byte	0
	.uleb128 0x7
	.string	"k"
	.byte	0x8
	.byte	0x8f
	.byte	0xe
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x7
	.string	"x"
	.byte	0x8
	.byte	0x90
	.byte	0xd
	.4byte	0x92
	.byte	0x8
	.uleb128 0x7
	.string	"y"
	.byte	0x8
	.byte	0x91
	.byte	0xd
	.4byte	0x92
	.byte	0xc
	.uleb128 0x7
	.string	"z1"
	.byte	0x8
	.byte	0x92
	.byte	0xd
	.4byte	0x92
	.byte	0x10
	.uleb128 0x7
	.string	"z2"
	.byte	0x8
	.byte	0x93
	.byte	0xd
	.4byte	0x92
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF75
	.byte	0x8
	.byte	0x94
	.byte	0xe
	.4byte	0x9e
	.byte	0x18
	.uleb128 0x3
	.4byte	.LASF36
	.byte	0x8
	.byte	0x95
	.byte	0xe
	.4byte	0xaa
	.byte	0x1c
	.uleb128 0x3
	.4byte	.LASF37
	.byte	0x8
	.byte	0x96
	.byte	0xe
	.4byte	0x9e
	.byte	0x24
	.byte	0
	.uleb128 0x4
	.4byte	.LASF76
	.byte	0x8
	.byte	0x9c
	.byte	0x2
	.4byte	0x393
	.uleb128 0x6
	.4byte	0x409
	.uleb128 0x8
	.byte	0x18
	.byte	0x9
	.byte	0x53
	.4byte	0x43d
	.uleb128 0x3
	.4byte	.LASF77
	.byte	0x9
	.byte	0x56
	.byte	0x16
	.4byte	0x17e
	.byte	0
	.uleb128 0x3
	.4byte	.LASF78
	.byte	0x9
	.byte	0x57
	.byte	0xe
	.4byte	0x9e
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF79
	.byte	0x9
	.byte	0x58
	.byte	0x2
	.4byte	0x41a
	.uleb128 0x8
	.byte	0x68
	.byte	0x9
	.byte	0x5a
	.4byte	0x479
	.uleb128 0x3
	.4byte	.LASF80
	.byte	0x9
	.byte	0x5b
	.byte	0x18
	.4byte	0x479
	.byte	0
	.uleb128 0x3
	.4byte	.LASF81
	.byte	0x9
	.byte	0x5c
	.byte	0xe
	.4byte	0x9e
	.byte	0x60
	.uleb128 0x3
	.4byte	.LASF82
	.byte	0x9
	.byte	0x5d
	.byte	0xe
	.4byte	0x9e
	.byte	0x64
	.byte	0
	.uleb128 0xe
	.4byte	0x43d
	.4byte	0x489
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF83
	.byte	0x9
	.byte	0x5e
	.byte	0x2
	.4byte	0x449
	.uleb128 0x6
	.4byte	0x489
	.uleb128 0x12
	.4byte	.LASF84
	.byte	0x2f
	.byte	0x4a
	.4byte	0x387
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_kr_q
	.uleb128 0xe
	.4byte	0x88
	.4byte	0x4bb
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x13
	.4byte	0x4ab
	.uleb128 0x12
	.4byte	.LASF85
	.byte	0x2f
	.byte	0x7a
	.4byte	0x4bb
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_mirror_kr_q
	.uleb128 0x8
	.byte	0x8
	.byte	0x1
	.byte	0x37
	.4byte	0x4f0
	.uleb128 0x7
	.string	"x"
	.byte	0x1
	.byte	0x38
	.byte	0xe
	.4byte	0x9e
	.byte	0
	.uleb128 0x7
	.string	"y"
	.byte	0x1
	.byte	0x39
	.byte	0xe
	.4byte	0x9e
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF86
	.byte	0x1
	.byte	0x3a
	.byte	0x2
	.4byte	0x4d1
	.uleb128 0x8
	.byte	0x14
	.byte	0x1
	.byte	0x3c
	.4byte	0x51f
	.uleb128 0x7
	.string	"val"
	.byte	0x1
	.byte	0x3d
	.byte	0x17
	.4byte	0x51f
	.byte	0
	.uleb128 0x3
	.4byte	.LASF87
	.byte	0x1
	.byte	0x3e
	.byte	0xe
	.4byte	0x9e
	.byte	0x10
	.byte	0
	.uleb128 0xe
	.4byte	0x4f0
	.4byte	0x52f
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF88
	.byte	0x1
	.byte	0x3f
	.byte	0x2
	.4byte	0x4fc
	.uleb128 0x12
	.4byte	.LASF89
	.byte	0x41
	.byte	0x12
	.4byte	0x52f
	.uleb128 0x5
	.byte	0x3
	.4byte	Kr_xy_buf
	.uleb128 0x1d
	.4byte	.LASF103
	.byte	0xa
	.byte	0x21
	.byte	0x8
	.4byte	0x7f
	.4byte	0x56c
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x6c
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF104
	.byte	0x7
	.2byte	0x129
	.byte	0xd
	.4byte	0x58f
	.uleb128 0x2
	.4byte	0x7f
	.uleb128 0x2
	.4byte	0x1c8
	.uleb128 0x2
	.4byte	0x8d
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0x10
	.byte	0
	.uleb128 0xb
	.4byte	.LASF95
	.byte	0xaa
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x604
	.uleb128 0x14
	.4byte	.LASF90
	.byte	0xaa
	.4byte	0x495
	.4byte	.LLST5
	.uleb128 0xc
	.4byte	.LASF91
	.byte	0xaa
	.byte	0x4e
	.4byte	0x604
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0xc
	.4byte	.LASF92
	.byte	0xaa
	.byte	0x66
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0xd
	.4byte	.LASF93
	.byte	0xb2
	.byte	0x19
	.4byte	0x609
	.4byte	.LLST6
	.uleb128 0xd
	.4byte	.LASF94
	.byte	0xb3
	.byte	0x17
	.4byte	0x604
	.4byte	.LLST7
	.uleb128 0x1f
	.4byte	0x770
	.4byte	.LBB10
	.4byte	.LLRL8
	.byte	0x1
	.byte	0xac
	.byte	0x9
	.uleb128 0x15
	.4byte	0x77d
	.4byte	.LLST9
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	0x17e
	.uleb128 0x6
	.4byte	0x43d
	.uleb128 0xb
	.4byte	.LASF96
	.byte	0x73
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x691
	.uleb128 0xc
	.4byte	.LASF90
	.byte	0x73
	.byte	0x30
	.4byte	0x495
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0xc
	.4byte	.LASF91
	.byte	0x73
	.byte	0x41
	.4byte	0x7f
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x20
	.4byte	.LASF97
	.byte	0x1
	.byte	0x75
	.byte	0x1b
	.4byte	0x415
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x21
	.4byte	.LBB7
	.4byte	.LBE7-.LBB7
	.4byte	0x676
	.uleb128 0xd
	.4byte	.LASF93
	.byte	0x79
	.byte	0x1d
	.4byte	0x609
	.4byte	.LLST3
	.uleb128 0xd
	.4byte	.LASF98
	.byte	0x7a
	.byte	0x1b
	.4byte	0x604
	.4byte	.LLST3
	.byte	0
	.uleb128 0x22
	.4byte	0x753
	.4byte	.LBB5
	.4byte	.LBE5-.LBB5
	.byte	0x1
	.byte	0x77
	.byte	0x9
	.uleb128 0x15
	.4byte	0x764
	.4byte	.LLST2
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF99
	.byte	0x66
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x6b3
	.uleb128 0xc
	.4byte	.LASF91
	.byte	0x66
	.byte	0x2c
	.4byte	0x415
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0xb
	.4byte	.LASF100
	.byte	0x5e
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x6ed
	.uleb128 0x16
	.string	"x"
	.byte	0x5e
	.byte	0x21
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x16
	.string	"y"
	.byte	0x5e
	.byte	0x2d
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0xd
	.4byte	.LASF87
	.byte	0x60
	.byte	0xe
	.4byte	0x9e
	.4byte	.LLST1
	.byte	0
	.uleb128 0xb
	.4byte	.LASF101
	.byte	0x55
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x753
	.uleb128 0x14
	.4byte	.LASF90
	.byte	0x55
	.4byte	0x495
	.4byte	.LLST0
	.uleb128 0x23
	.4byte	.LVL1
	.4byte	0x54c
	.4byte	0x735
	.uleb128 0x9
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
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x68
	.byte	0
	.uleb128 0x24
	.4byte	.LVL2
	.4byte	0x54c
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	Kr_xy_buf
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x44
	.byte	0
	.byte	0
	.uleb128 0x25
	.4byte	.LASF105
	.byte	0x1
	.byte	0x4f
	.byte	0xc
	.4byte	0xfd
	.byte	0x1
	.4byte	0x770
	.uleb128 0x17
	.4byte	.LASF90
	.byte	0x4f
	.byte	0x3b
	.4byte	0x495
	.byte	0
	.uleb128 0x26
	.4byte	.LASF106
	.byte	0x1
	.byte	0x48
	.byte	0xc
	.4byte	0xfd
	.byte	0x1
	.uleb128 0x17
	.4byte	.LASF90
	.byte	0x48
	.byte	0x3a
	.4byte	0x495
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
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
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
	.uleb128 0xb
	.uleb128 0x1
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
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
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
	.uleb128 0x21
	.sleb128 49
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1c
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x22
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x26
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
	.uleb128 .LVL14-.LVL10
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL14-.LVL10
	.uleb128 .LFE12-.LVL10
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
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x8
	.byte	0x7f
	.sleb128 0
	.byte	0x48
	.byte	0x1e
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL13-.LVL12
	.uleb128 .LVL14-.LVL12
	.uleb128 0xa
	.byte	0x7a
	.sleb128 96
	.byte	0x6
	.byte	0x48
	.byte	0x1e
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL14-.LVL12
	.uleb128 .LVL15-.LVL12
	.uleb128 0x19
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x23
	.uleb128 0x60
	.byte	0x6
	.byte	0x48
	.byte	0x1e
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x8
	.byte	0x7f
	.sleb128 0
	.byte	0x48
	.byte	0x1e
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL13-.LVL12
	.uleb128 .LVL14-.LVL12
	.uleb128 0xa
	.byte	0x7a
	.sleb128 96
	.byte	0x6
	.byte	0x48
	.byte	0x1e
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL14-.LVL12
	.uleb128 .LVL15-.LVL12
	.uleb128 0x19
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x23
	.uleb128 0x60
	.byte	0x6
	.byte	0x48
	.byte	0x1e
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0
.LLST9:
	.byte	0x8
	.4byte	.LVL10
	.uleb128 .LVL11-.LVL10
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST3:
	.byte	0x8
	.4byte	.LVL8
	.uleb128 .LVL9-.LVL8
	.uleb128 0x8
	.byte	0x7d
	.sleb128 0
	.byte	0x48
	.byte	0x1e
	.byte	0x7a
	.sleb128 0
	.byte	0x22
	.byte	0x9f
	.byte	0
.LLST2:
	.byte	0x8
	.4byte	.LVL6
	.uleb128 .LVL7-.LVL6
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST1:
	.byte	0x8
	.4byte	.LVL3
	.uleb128 .LVL4-.LVL3
	.uleb128 0x5
	.byte	0x3
	.4byte	Kr_xy_buf+16
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
	.uleb128 .LFE8-.LVL0
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
	.4byte	0x3c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
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
.LLRL8:
	.byte	0x5
	.4byte	.LBB10
	.byte	0x4
	.uleb128 .LBB10-.LBB10
	.uleb128 .LBE10-.LBB10
	.byte	0x4
	.uleb128 .LBB13-.LBB10
	.uleb128 .LBE13-.LBB10
	.byte	0
.LLRL10:
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
	.byte	0x7
	.4byte	.LFB12
	.uleb128 .LFE12-.LFB12
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF81:
	.string	"buf_head"
.LASF66:
	.string	"module_name"
.LASF99:
	.string	"key_remap_xy_pop"
.LASF72:
	.string	"msg_id_handle"
.LASF85:
	.string	"log_control_block_mirror_kr_q"
.LASF97:
	.string	"outgoing"
.LASF57:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF47:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF89:
	.string	"Kr_xy_buf"
.LASF12:
	.string	"char"
.LASF101:
	.string	"key_remap_queue_init"
.LASF84:
	.string	"log_control_block_kr_q"
.LASF44:
	.string	"PRINT_LEVEL_ERROR"
.LASF74:
	.string	"type"
.LASF13:
	.string	"size_t"
.LASF65:
	.string	"f_tlv_dump_t"
.LASF55:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF30:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF94:
	.string	"key_info_write"
.LASF19:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF20:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF87:
	.string	"active"
.LASF6:
	.string	"short int"
.LASF98:
	.string	"outgoing_key_info"
.LASF63:
	.string	"f_dump_buffer_t"
.LASF32:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF51:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF16:
	.string	"DBG_PIN_SPI_CB"
.LASF88:
	.string	"T_REMAP_XY_BUF_S"
.LASF92:
	.string	"key_status"
.LASF42:
	.string	"PRINT_LEVEL_INFO"
.LASF11:
	.string	"long double"
.LASF91:
	.string	"outgoing_data"
.LASF49:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF10:
	.string	"long long int"
.LASF83:
	.string	"T_REMAP_QUEUE_CTRL_S"
.LASF103:
	.string	"memset"
.LASF8:
	.string	"long int"
.LASF71:
	.string	"tlv_dump_handle"
.LASF64:
	.string	"f_msg_id_t"
.LASF34:
	.string	"ms_k"
.LASF70:
	.string	"dump_handle"
.LASF22:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF54:
	.string	"LOG_TYPE_HCI_DATA"
.LASF102:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF5:
	.string	"unsigned char"
.LASF106:
	.string	"key_remap_queue_is_full"
.LASF50:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF4:
	.string	"signed char"
.LASF37:
	.string	"kb_consumer"
.LASF2:
	.string	"long long unsigned int"
.LASF15:
	.string	"uint32_t"
.LASF17:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF86:
	.string	"T_REMAP_XY_IFNO_S"
.LASF26:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF75:
	.string	"k_old"
.LASF52:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF46:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF105:
	.string	"key_remap_queue_is_empty"
.LASF60:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF23:
	.string	"DBG_PIN_USB_TX"
.LASF76:
	.string	"T_OUTGOING_VALUES_S"
.LASF69:
	.string	"print_handle"
.LASF7:
	.string	"short unsigned int"
.LASF100:
	.string	"key_remap_xy_push"
.LASF93:
	.string	"key_remap_info"
.LASF45:
	.string	"print_level_t"
.LASF36:
	.string	"kb_std"
.LASF25:
	.string	"_Bool"
.LASF62:
	.string	"f_print_t"
.LASF78:
	.string	"ready"
.LASF14:
	.string	"int32_t"
.LASF40:
	.string	"DEBUG_LOG_OFF"
.LASF80:
	.string	"buffer"
.LASF43:
	.string	"PRINT_LEVEL_WARNING"
.LASF53:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF95:
	.string	"key_remap_queue_push"
.LASF77:
	.string	"data"
.LASF28:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF79:
	.string	"T_REMAP_KEY_INFO_S"
.LASF82:
	.string	"buf_tail"
.LASF9:
	.string	"long unsigned int"
.LASF68:
	.string	"print_level"
.LASF29:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF41:
	.string	"PRINT_LEVEL_DEBUG"
.LASF48:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF31:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF21:
	.string	"DBG_PIN_USB_SOF"
.LASF27:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF35:
	.string	"ms_z1"
.LASF61:
	.string	"log_type_t"
.LASF38:
	.string	"T_REMAP_VALUES_S"
.LASF90:
	.string	"Kr_q_Ctrl"
.LASF58:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF59:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF33:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF18:
	.string	"DBG_PIN_NACK"
.LASF3:
	.string	"unsigned int"
.LASF39:
	.string	"DEBUG_LOG_ON"
.LASF24:
	.string	"DBG_PIN_MAX"
.LASF56:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF96:
	.string	"key_remap_queue_pop"
.LASF104:
	.string	"print_module_msgid_log"
.LASF67:
	.string	"log_switch"
.LASF73:
	.string	"log_control_block_t"
	.section	.debug_line_str,"MS",@progbits,1
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/key_remap/src/key_remap_queue.c"
.LASF1:
	.string	"/workdir/airoha/risc-v"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
