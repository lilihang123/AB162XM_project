	.file	"system_online_dump.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/kernel/service/system_online_dump/src/system_online_dump.c"
	.section	.text.ccni_dump_sysinfo,"ax",@progbits
	.align	1
	.globl	ccni_dump_sysinfo
	.hidden	ccni_dump_sysinfo
	.type	ccni_dump_sysinfo, @function
ccni_dump_sysinfo:
.LFB4:
	.file 1 "/workdir/airoha/risc-v/kernel/service/system_online_dump/src/system_online_dump.c"
	.loc 1 193 1
	.cfi_startproc
.LVL0:
	.loc 1 194 5
.LBB2:
	.loc 1 194 10
	.loc 1 194 74
	.loc 1 194 271
.LBE2:
	.loc 1 193 1 is_stmt 0
	mv	a4,a0
.LBB3:
	.loc 1 194 271
	li	a3,1
	lla	a2,msg_id_string.1
	li	a1,2
	lla	a0,log_control_block_system_online_dsp
.LVL1:
	tail	print_module_msgid_log
.LVL2:
.LBE3:
	.cfi_endproc
.LFE4:
	.size	ccni_dump_sysinfo, .-ccni_dump_sysinfo
	.section	.text.hal_ccni_event_callback15,"ax",@progbits
	.align	1
	.globl	hal_ccni_event_callback15
	.hidden	hal_ccni_event_callback15
	.type	hal_ccni_event_callback15, @function
hal_ccni_event_callback15:
.LFB5:
	.loc 1 200 1 is_stmt 1
	.cfi_startproc
.LVL3:
	.loc 1 201 5
	.loc 1 202 5
	.loc 1 204 5
	.loc 1 205 5
	.loc 1 207 5
	.loc 1 207 8 is_stmt 0
	beq	a1,zero,.L7
	.loc 1 200 1
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s1,4(sp)
	.cfi_offset 9, -12
	.loc 1 208 16
	lw	s1,0(a1)
	.loc 1 200 1
	sw	s0,8(sp)
.LBB4:
	.loc 1 209 267
	li	a3,3
	sw	s1,0(sp)
	lw	a5,4(a1)
	.cfi_offset 8, -8
	mv	s0,a1
.LBE4:
	.loc 1 208 9 is_stmt 1
.LVL4:
	.loc 1 209 9
.LBB5:
	.loc 1 209 14
	.loc 1 209 78
	.loc 1 209 267
	mv	a4,s1
	lla	a2,msg_id_string.0
	li	a1,1
.LVL5:
	lla	a0,log_control_block_system_online_dsp
.LVL6:
.LBE5:
	.loc 1 200 1 is_stmt 0
	sw	ra,12(sp)
	.cfi_offset 1, -4
.LBB6:
	.loc 1 209 267
	call	print_module_msgid_log
.LVL7:
.LBE6:
	.loc 1 209 12 is_stmt 1 discriminator 1
	.loc 1 213 9
	li	a5,1
	bne	s1,a5,.L2
.LBB7:
	.loc 1 218 17
.LVL8:
	.loc 1 219 17
	lw	a0,4(s0)
.LBE7:
	.loc 1 226 1 is_stmt 0
	lw	s0,8(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL9:
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s1,4(sp)
	.cfi_restore 9
.LVL10:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
.LBB8:
	.loc 1 219 17
	tail	ccni_dump_sysinfo
.LVL11:
.L2:
	.cfi_restore_state
.LBE8:
	.loc 1 226 1
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL12:
	lw	s1,4(sp)
	.cfi_restore 9
.LVL13:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL14:
.L7:
	ret
	.cfi_endproc
.LFE5:
	.size	hal_ccni_event_callback15, .-hal_ccni_event_callback15
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 96
msg_id_string.0:
	.string	"[M:system_online_dsp C:info F: L: ]: dsp_system_event_handler msg[0]:0x%x msg[1]:0x%x sub_id:%d"
	.align	2
	.type	msg_id_string.1, @object
	.size	msg_id_string.1, 104
msg_id_string.1:
	.string	"[M:system_online_dsp C:info F: L: ]: Please enable RISC-V AIR_ONLINE_SWLA_ENABLE first. function_id:%d "
	.hidden	sys_task_info
	.globl	sys_task_info
	.section	.data.sys_task_info,"aw"
	.align	2
	.type	sys_task_info, @object
	.size	sys_task_info, 18
sys_task_info:
	.byte	0
	.byte	0
	.string	"main"
	.zero	11
	.hidden	log_control_block_mirror_system_online_dsp
	.globl	log_control_block_mirror_system_online_dsp
	.section	.log_filter_mirror.system_online_dsp,"a"
	.align	2
	.type	log_control_block_mirror_system_online_dsp, @object
	.size	log_control_block_mirror_system_online_dsp, 18
log_control_block_mirror_system_online_dsp:
	.string	"system_online_dsp"
	.hidden	log_control_block_system_online_dsp
	.globl	log_control_block_system_online_dsp
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"system_online_dsp"
	.section	.log_filter.system_online_dsp,"aw"
	.align	2
	.type	log_control_block_system_online_dsp, @object
	.size	log_control_block_system_online_dsp, 28
log_control_block_system_online_dsp:
	.word	.LC0
	.word	0
	.word	1
	.word	0
	.word	0
	.word	0
	.word	print_module_msgid_log
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 4 "/workdir/airoha/risc-v/kernel/service/system_online_dump/inc/system_online_dump.h"
	.file 5 "/workdir/airoha/common/drivers/chip/ab162x/../inc/hal_ccni.h"
	.file 6 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x63f
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x1a
	.4byte	.LASF97
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL8
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
	.uleb128 0x1b
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.byte	0x8
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x4
	.byte	0x10
	.byte	0x4
	.4byte	.LASF5
	.uleb128 0x4
	.byte	0x1
	.byte	0x6
	.4byte	.LASF6
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF7
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x4
	.byte	0x2
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x1c
	.byte	0x4
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xa
	.4byte	0x75
	.uleb128 0x7
	.4byte	0x7c
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x2
	.byte	0x22
	.byte	0x15
	.4byte	0x49
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x50
	.uleb128 0x3
	.4byte	.LASF15
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x6c
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x3
	.byte	0x37
	.4byte	0xc2
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x1
	.byte	0
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x3
	.byte	0x3d
	.4byte	0xe6
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
	.byte	0
	.uleb128 0x3
	.4byte	.LASF22
	.byte	0x3
	.byte	0x42
	.byte	0x3
	.4byte	0xc2
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x3
	.byte	0x45
	.4byte	0x158
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x3f
	.byte	0
	.uleb128 0x3
	.4byte	.LASF38
	.byte	0x3
	.byte	0x57
	.byte	0x3
	.4byte	0xf2
	.uleb128 0x3
	.4byte	.LASF39
	.byte	0x3
	.byte	0x59
	.byte	0x10
	.4byte	0x170
	.uleb128 0x7
	.4byte	0x175
	.uleb128 0xe
	.4byte	0x195
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x34
	.uleb128 0x2
	.4byte	0xe6
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0xc
	.byte	0
	.uleb128 0x3
	.4byte	.LASF40
	.byte	0x3
	.byte	0x5a
	.byte	0x10
	.4byte	0x1a1
	.uleb128 0x7
	.4byte	0x1a6
	.uleb128 0xe
	.4byte	0x1d0
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x34
	.uleb128 0x2
	.4byte	0xe6
	.uleb128 0x2
	.4byte	0x1d0
	.uleb128 0x2
	.4byte	0x34
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0xc
	.byte	0
	.uleb128 0x7
	.4byte	0x1d5
	.uleb128 0x1d
	.uleb128 0x3
	.4byte	.LASF41
	.byte	0x3
	.byte	0x5b
	.byte	0x10
	.4byte	0x1e2
	.uleb128 0x7
	.4byte	0x1e7
	.uleb128 0xe
	.4byte	0x202
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xe6
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0xc
	.byte	0
	.uleb128 0x3
	.4byte	.LASF42
	.byte	0x3
	.byte	0x5c
	.byte	0x14
	.4byte	0x20e
	.uleb128 0x7
	.4byte	0x213
	.uleb128 0x1e
	.4byte	0x9e
	.4byte	0x236
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xe6
	.uleb128 0x2
	.4byte	0x158
	.uleb128 0x2
	.4byte	0x236
	.uleb128 0x2
	.4byte	0x23b
	.byte	0
	.uleb128 0x7
	.4byte	0x1d0
	.uleb128 0x7
	.4byte	0x9e
	.uleb128 0x11
	.byte	0x1c
	.byte	0x3
	.byte	0x5e
	.4byte	0x2a4
	.uleb128 0x6
	.4byte	.LASF43
	.byte	0x3
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x6
	.4byte	.LASF44
	.byte	0x3
	.byte	0x60
	.byte	0xe
	.4byte	0x9e
	.byte	0x4
	.uleb128 0x6
	.4byte	.LASF45
	.byte	0x3
	.byte	0x61
	.byte	0xe
	.4byte	0x9e
	.byte	0x8
	.uleb128 0x6
	.4byte	.LASF46
	.byte	0x3
	.byte	0x62
	.byte	0xf
	.4byte	0x164
	.byte	0xc
	.uleb128 0x6
	.4byte	.LASF47
	.byte	0x3
	.byte	0x63
	.byte	0x15
	.4byte	0x195
	.byte	0x10
	.uleb128 0x6
	.4byte	.LASF48
	.byte	0x3
	.byte	0x64
	.byte	0x12
	.4byte	0x202
	.byte	0x14
	.uleb128 0x6
	.4byte	.LASF49
	.byte	0x3
	.byte	0x65
	.byte	0x10
	.4byte	0x1d6
	.byte	0x18
	.byte	0
	.uleb128 0x3
	.4byte	.LASF50
	.byte	0x3
	.byte	0x66
	.byte	0x3
	.4byte	0x240
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x4
	.byte	0x42
	.4byte	0x2d1
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x1
	.uleb128 0x1f
	.4byte	.LASF53
	.4byte	0xffffffff
	.byte	0
	.uleb128 0x3
	.4byte	.LASF54
	.byte	0x4
	.byte	0x46
	.byte	0x3
	.4byte	0x2b0
	.uleb128 0x11
	.byte	0x12
	.byte	0x4
	.byte	0x48
	.4byte	0x30d
	.uleb128 0x6
	.4byte	.LASF55
	.byte	0x4
	.byte	0x49
	.byte	0xd
	.4byte	0x92
	.byte	0
	.uleb128 0x6
	.4byte	.LASF56
	.byte	0x4
	.byte	0x4a
	.byte	0xc
	.4byte	0x86
	.byte	0x1
	.uleb128 0x6
	.4byte	.LASF57
	.byte	0x4
	.byte	0x4b
	.byte	0xa
	.4byte	0x30d
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.4byte	0x75
	.4byte	0x31d
	.uleb128 0x9
	.4byte	0x2d
	.byte	0xf
	.byte	0
	.uleb128 0x3
	.4byte	.LASF58
	.byte	0x4
	.byte	0x4c
	.byte	0x1b
	.4byte	0x2dd
	.uleb128 0x20
	.4byte	.LASF98
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x6
	.2byte	0x128
	.byte	0x12
	.4byte	0x3af
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x1f
	.byte	0
	.uleb128 0x8
	.4byte	0x9e
	.4byte	0x3bf
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x21
	.byte	0x5
	.byte	0x4
	.4byte	0x34
	.byte	0x5
	.2byte	0x120
	.byte	0xe
	.4byte	0x3ed
	.uleb128 0xd
	.4byte	.LASF78
	.sleb128 -4
	.uleb128 0xd
	.4byte	.LASF79
	.sleb128 -3
	.uleb128 0xd
	.4byte	.LASF80
	.sleb128 -2
	.uleb128 0xd
	.4byte	.LASF81
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	.LASF83
	.2byte	0x126
	.byte	0x3
	.4byte	0x3bf
	.uleb128 0xf
	.4byte	.LASF84
	.2byte	0x137
	.byte	0x12
	.4byte	0x9e
	.uleb128 0x22
	.byte	0x8
	.byte	0x5
	.2byte	0x13d
	.byte	0x5
	.4byte	0x42a
	.uleb128 0x12
	.string	"ptr"
	.2byte	0x13e
	.byte	0xf
	.4byte	0x73
	.byte	0
	.uleb128 0x12
	.string	"len"
	.2byte	0x13f
	.byte	0x12
	.4byte	0x9e
	.byte	0x4
	.byte	0
	.uleb128 0x23
	.byte	0x8
	.byte	0x5
	.2byte	0x13c
	.byte	0x9
	.4byte	0x44d
	.uleb128 0x13
	.4byte	.LASF85
	.2byte	0x140
	.byte	0x7
	.4byte	0x405
	.uleb128 0x13
	.4byte	.LASF86
	.2byte	0x141
	.byte	0xe
	.4byte	0x3af
	.byte	0
	.uleb128 0xf
	.4byte	.LASF87
	.2byte	0x142
	.byte	0x3
	.4byte	0x42a
	.uleb128 0x7
	.4byte	0x44d
	.uleb128 0x10
	.4byte	.LASF88
	.byte	0x33
	.byte	0x57
	.4byte	0x2a4
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_system_online_dsp
	.uleb128 0x8
	.4byte	0x7c
	.4byte	0x47f
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x11
	.byte	0
	.uleb128 0xa
	.4byte	0x46f
	.uleb128 0x10
	.4byte	.LASF89
	.byte	0x33
	.byte	0x87
	.4byte	0x47f
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_mirror_system_online_dsp
	.uleb128 0x8
	.4byte	0x31d
	.4byte	0x4a5
	.uleb128 0x9
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF90
	.byte	0x3c
	.byte	0x11
	.4byte	0x495
	.uleb128 0x5
	.byte	0x3
	.4byte	sys_task_info
	.uleb128 0x24
	.4byte	.LASF99
	.byte	0x3
	.2byte	0x129
	.byte	0xd
	.4byte	0x4d9
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xe6
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x9e
	.uleb128 0xc
	.byte	0
	.uleb128 0x14
	.4byte	.LASF95
	.byte	0xc7
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x59f
	.uleb128 0x15
	.4byte	.LASF91
	.byte	0xc7
	.byte	0x31
	.4byte	0x3f9
	.4byte	.LLST2
	.uleb128 0x25
	.string	"msg"
	.byte	0x1
	.byte	0xc7
	.byte	0x4c
	.4byte	0x459
	.4byte	.LLST3
	.uleb128 0x16
	.4byte	.LASF92
	.byte	0xc9
	.byte	0x20
	.4byte	0x2d1
	.4byte	.LLST4
	.uleb128 0x26
	.4byte	.LASF100
	.byte	0x1
	.byte	0xca
	.byte	0x17
	.4byte	0x3ed
	.uleb128 0x27
	.4byte	.LLRL5
	.4byte	0x580
	.uleb128 0x17
	.4byte	.LASF88
	.byte	0xd1
	.byte	0x29
	.4byte	0x2a4
	.uleb128 0x18
	.4byte	.LASF93
	.byte	0xd1
	.byte	0x8d
	.4byte	0x5af
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x28
	.4byte	.LVL7
	.4byte	0x4b6
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_system_online_dsp
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x33
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.uleb128 0x5
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x19
	.4byte	.LLRL6
	.uleb128 0x16
	.4byte	.LASF94
	.byte	0xda
	.byte	0x1a
	.4byte	0x9e
	.4byte	.LLST7
	.uleb128 0x29
	.4byte	.LVL11
	.4byte	0x5b4
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0x7c
	.4byte	0x5af
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x5f
	.byte	0
	.uleb128 0xa
	.4byte	0x59f
	.uleb128 0x14
	.4byte	.LASF96
	.byte	0xc0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x62d
	.uleb128 0x15
	.4byte	.LASF94
	.byte	0xc0
	.byte	0x21
	.4byte	0x9e
	.4byte	.LLST0
	.uleb128 0x19
	.4byte	.LLRL1
	.uleb128 0x17
	.4byte	.LASF88
	.byte	0xc2
	.byte	0x25
	.4byte	0x2a4
	.uleb128 0x18
	.4byte	.LASF93
	.byte	0xc2
	.byte	0x89
	.4byte	0x63d
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x2a
	.4byte	.LVL2
	.4byte	0x4b6
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_system_online_dsp
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5e
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
	.uleb128 0x8
	.4byte	0x7c
	.4byte	0x63d
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x67
	.byte	0
	.uleb128 0xa
	.4byte	0x62d
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x6
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x16
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
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x13
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
	.byte	0
	.byte	0
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0x1c
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.uleb128 0x1f
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x21
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0x17
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
	.uleb128 0x24
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
	.uleb128 0x25
	.uleb128 0x5
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
	.uleb128 0x26
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
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x2a
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
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL6-.LVL3
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL6-.LVL3
	.uleb128 .LVL14-.LVL3
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
	.uleb128 .LVL14-.LVL3
	.uleb128 .LFE5-.LVL3
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL5-.LVL3
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL5-.LVL3
	.uleb128 .LVL9-.LVL3
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL9-.LVL3
	.uleb128 .LVL11-.LVL3
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
	.uleb128 .LVL11-.LVL3
	.uleb128 .LVL12-.LVL3
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL12-.LVL3
	.uleb128 .LVL14-.LVL3
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
	.uleb128 .LVL14-.LVL3
	.uleb128 .LFE5-.LVL3
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL10-.LVL4
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL11-.LVL4
	.uleb128 .LVL13-.LVL4
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL9-.LVL8
	.uleb128 0x2
	.byte	0x78
	.sleb128 4
	.byte	0x4
	.uleb128 .LVL9-.LVL8
	.uleb128 .LVL11-1-.LVL8
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
	.uleb128 .LVL2-1-.LVL0
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL2-1-.LVL0
	.uleb128 .LFE4-.LVL0
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
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
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
.LLRL5:
	.byte	0x5
	.4byte	.LBB4
	.byte	0x4
	.uleb128 .LBB4-.LBB4
	.uleb128 .LBE4-.LBB4
	.byte	0x4
	.uleb128 .LBB5-.LBB4
	.uleb128 .LBE5-.LBB4
	.byte	0x4
	.uleb128 .LBB6-.LBB4
	.uleb128 .LBE6-.LBB4
	.byte	0
.LLRL6:
	.byte	0x5
	.4byte	.LBB7
	.byte	0x4
	.uleb128 .LBB7-.LBB7
	.uleb128 .LBE7-.LBB7
	.byte	0x4
	.uleb128 .LBB8-.LBB7
	.uleb128 .LBE8-.LBB7
	.byte	0
.LLRL8:
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF79:
	.string	"HAL_CCNI_STATUS_BUSY"
.LASF69:
	.string	"MCU_DMA_IRQn"
.LASF84:
	.string	"hal_ccni_event_t"
.LASF40:
	.string	"f_dump_buffer_t"
.LASF62:
	.string	"KEYSCAN_IRQn"
.LASF76:
	.string	"BT_IRQn"
.LASF56:
	.string	"priority"
.LASF13:
	.string	"int8_t"
.LASF81:
	.string	"HAL_CCNI_STATUS_NO_INIT"
.LASF21:
	.string	"PRINT_LEVEL_ERROR"
.LASF71:
	.string	"I3C0_IRQn"
.LASF35:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF42:
	.string	"f_tlv_dump_t"
.LASF32:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF70:
	.string	"EINT_IRQn"
.LASF59:
	.string	"SW_IRQn"
.LASF87:
	.string	"hal_ccni_message_t"
.LASF98:
	.string	"IRQn"
.LASF34:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF91:
	.string	"event"
.LASF51:
	.string	"SYSTEM_CCNI_SUB_EVENT_SWLA"
.LASF8:
	.string	"short int"
.LASF66:
	.string	"GPT_IRQn"
.LASF83:
	.string	"hal_ccni_status_t"
.LASF94:
	.string	"func_id"
.LASF80:
	.string	"HAL_CCNI_STATUS_ERROR"
.LASF63:
	.string	"UART_IRQn"
.LASF28:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF18:
	.string	"PRINT_LEVEL_DEBUG"
.LASF19:
	.string	"PRINT_LEVEL_INFO"
.LASF82:
	.string	"HAL_CCNI_STATUS_OK"
.LASF29:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF55:
	.string	"number"
.LASF78:
	.string	"HAL_CCNI_STATUS_INVALID_PARAMETER"
.LASF26:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF4:
	.string	"long long int"
.LASF65:
	.string	"RTC_IRQn"
.LASF44:
	.string	"log_switch"
.LASF10:
	.string	"long int"
.LASF53:
	.string	"SYSTEM_CCNI_SUB_EVENT_MAX"
.LASF41:
	.string	"f_msg_id_t"
.LASF92:
	.string	"sub_id"
.LASF47:
	.string	"dump_handle"
.LASF31:
	.string	"LOG_TYPE_HCI_DATA"
.LASF24:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF57:
	.string	"name"
.LASF5:
	.string	"long double"
.LASF97:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF64:
	.string	"SPI_MST1_IRQn"
.LASF7:
	.string	"unsigned char"
.LASF89:
	.string	"log_control_block_mirror_system_online_dsp"
.LASF52:
	.string	"SYSTEM_CCNI_SUB_EVENT_SYSINFO"
.LASF6:
	.string	"signed char"
.LASF2:
	.string	"long long unsigned int"
.LASF15:
	.string	"uint32_t"
.LASF3:
	.string	"unsigned int"
.LASF22:
	.string	"print_level_t"
.LASF60:
	.string	"LED_IRQn"
.LASF88:
	.string	"log_control_block_system_online_dsp"
.LASF23:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF37:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF93:
	.string	"msg_id_string"
.LASF49:
	.string	"msg_id_handle"
.LASF100:
	.string	"status"
.LASF9:
	.string	"short unsigned int"
.LASF72:
	.string	"I3C0_DMA_IRQn"
.LASF48:
	.string	"tlv_dump_handle"
.LASF96:
	.string	"ccni_dump_sysinfo"
.LASF90:
	.string	"sys_task_info"
.LASF12:
	.string	"char"
.LASF39:
	.string	"f_print_t"
.LASF17:
	.string	"DEBUG_LOG_OFF"
.LASF61:
	.string	"QDEC_IRQn"
.LASF20:
	.string	"PRINT_LEVEL_WARNING"
.LASF46:
	.string	"print_handle"
.LASF30:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF50:
	.string	"log_control_block_t"
.LASF86:
	.string	"data"
.LASF43:
	.string	"module_name"
.LASF11:
	.string	"long unsigned int"
.LASF45:
	.string	"print_level"
.LASF75:
	.string	"USB_IRQn"
.LASF95:
	.string	"hal_ccni_event_callback15"
.LASF77:
	.string	"IRQ_NUMBER_MAX"
.LASF67:
	.string	"UART_DMA_IRQn"
.LASF54:
	.string	"system_ccni_sub_event_id_t"
.LASF25:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF38:
	.string	"log_type_t"
.LASF14:
	.string	"uint8_t"
.LASF27:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF58:
	.string	"sys_task_info_t"
.LASF68:
	.string	"PMU_IRQn"
.LASF36:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF74:
	.string	"IRQ_GEN_IRQn"
.LASF16:
	.string	"DEBUG_LOG_ON"
.LASF33:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF99:
	.string	"print_module_msgid_log"
.LASF85:
	.string	"variable_len_msg"
.LASF73:
	.string	"SPI_MST0_IRQn"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/kernel/service/system_online_dump/src/system_online_dump.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
