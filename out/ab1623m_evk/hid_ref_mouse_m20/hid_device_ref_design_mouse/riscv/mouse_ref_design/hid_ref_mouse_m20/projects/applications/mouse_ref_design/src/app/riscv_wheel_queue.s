	.file	"riscv_wheel_queue.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_wheel_queue.c"
	.section	.text.riscv_wheel_queue_init_q_ctrl,"ax",@progbits
	.align	1
	.globl	riscv_wheel_queue_init_q_ctrl
	.hidden	riscv_wheel_queue_init_q_ctrl
	.type	riscv_wheel_queue_init_q_ctrl, @function
riscv_wheel_queue_init_q_ctrl:
.LFB6:
	.file 1 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_wheel_queue.c"
	.loc 1 61 1
	.cfi_startproc
	.loc 1 62 5
	.loc 1 62 27 is_stmt 0
	lla	a5,wheel_q_Ctrl
	sw	zero,16(a5)
	.loc 1 63 5 is_stmt 1
	.loc 1 63 27 is_stmt 0
	sw	zero,20(a5)
	.loc 1 64 1
	ret
	.cfi_endproc
.LFE6:
	.size	riscv_wheel_queue_init_q_ctrl, .-riscv_wheel_queue_init_q_ctrl
	.section	.text.riscv_wheel_queue_is_full,"ax",@progbits
	.align	1
	.globl	riscv_wheel_queue_is_full
	.hidden	riscv_wheel_queue_is_full
	.type	riscv_wheel_queue_is_full, @function
riscv_wheel_queue_is_full:
.LFB7:
	.loc 1 67 1 is_stmt 1
	.cfi_startproc
	.loc 1 68 5
	.loc 1 68 26 is_stmt 0
	lla	a5,wheel_q_Ctrl
	.loc 1 68 36
	lw	a0,16(a5)
	.loc 1 68 57
	lw	a5,20(a5)
	.loc 1 68 36
	addi	a0,a0,1
	.loc 1 68 41
	andi	a0,a0,7
	.loc 1 68 57
	sub	a0,a0,a5
	.loc 1 69 1
	seqz	a0,a0
	ret
	.cfi_endproc
.LFE7:
	.size	riscv_wheel_queue_is_full, .-riscv_wheel_queue_is_full
	.section	.text.riscv_wheel_queue_is_empty,"ax",@progbits
	.align	1
	.globl	riscv_wheel_queue_is_empty
	.hidden	riscv_wheel_queue_is_empty
	.type	riscv_wheel_queue_is_empty, @function
riscv_wheel_queue_is_empty:
.LFB8:
	.loc 1 72 1 is_stmt 1
	.cfi_startproc
	.loc 1 73 5
	.loc 1 73 24 is_stmt 0
	lla	a5,wheel_q_Ctrl
	.loc 1 73 34
	lw	a0,16(a5)
	lw	a5,20(a5)
	sub	a0,a0,a5
	.loc 1 74 1
	seqz	a0,a0
	ret
	.cfi_endproc
.LFE8:
	.size	riscv_wheel_queue_is_empty, .-riscv_wheel_queue_is_empty
	.section	.text.riscv_wheel_queue_push,"ax",@progbits
	.align	1
	.globl	riscv_wheel_queue_push
	.hidden	riscv_wheel_queue_push
	.type	riscv_wheel_queue_push, @function
riscv_wheel_queue_push:
.LFB9:
	.loc 1 77 1 is_stmt 1
	.cfi_startproc
.LVL0:
	.loc 1 78 5
	.loc 1 77 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 77 1
	mv	s0,a0
	.loc 1 78 9
	call	riscv_wheel_queue_is_full
.LVL1:
	.loc 1 78 8 discriminator 1
	beq	a0,zero,.L5
	.loc 1 79 9 is_stmt 1
.LBB2:
	.loc 1 79 14
	.loc 1 79 69
	.loc 1 79 229
.LBE2:
	.loc 1 88 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
.LVL2:
	lw	ra,8(sp)
	.cfi_restore 1
.LBB3:
	.loc 1 79 229
	li	a3,0
.LBE3:
	.loc 1 88 1
.LBB4:
	.loc 1 79 229
	lla	a2,msg_id_string.0
	li	a1,1
	lla	a0,log_control_block_riscv_ps
.LBE4:
	.loc 1 88 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
.LBB5:
	.loc 1 79 229
	tail	print_module_msgid_log
.LVL3:
.L5:
	.cfi_restore_state
.LBE5:
	.loc 1 83 5 is_stmt 1
	.loc 1 83 7 is_stmt 0
	beq	s0,zero,.L4
	.loc 1 85 9 is_stmt 1
	.loc 1 85 41 is_stmt 0
	lla	a4,wheel_q_Ctrl
	lw	a5,16(a4)
	.loc 1 85 52
	slli	a3,a5,1
	.loc 1 86 56
	addi	a5,a5,1
	.loc 1 85 52
	add	a3,a4,a3
	.loc 1 86 61
	andi	a5,a5,7
	.loc 1 85 52
	sh	s0,0(a3)
	.loc 1 86 9 is_stmt 1
	.loc 1 86 31 is_stmt 0
	sw	a5,16(a4)
.L4:
	.loc 1 88 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE9:
	.size	riscv_wheel_queue_push, .-riscv_wheel_queue_push
	.section	.text.riscv_wheel_queue_pop,"ax",@progbits
	.align	1
	.globl	riscv_wheel_queue_pop
	.hidden	riscv_wheel_queue_pop
	.type	riscv_wheel_queue_pop, @function
riscv_wheel_queue_pop:
.LFB10:
	.loc 1 91 1 is_stmt 1
	.cfi_startproc
.LVL4:
	.loc 1 92 5
	.loc 1 91 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 91 1
	mv	s0,a0
	.loc 1 92 9
	call	riscv_wheel_queue_is_empty
.LVL5:
	.loc 1 92 7 discriminator 1
	bne	a0,zero,.L12
	.loc 1 94 9 is_stmt 1
	.loc 1 94 48 is_stmt 0
	lla	a4,wheel_q_Ctrl
	lw	a5,20(a4)
	.loc 1 94 35
	slli	a3,a5,1
	add	a3,a4,a3
	lh	a3,0(a3)
	.loc 1 95 56
	addi	a5,a5,1
	.loc 1 95 61
	andi	a5,a5,7
	.loc 1 94 14
	sh	a3,0(s0)
	.loc 1 95 9 is_stmt 1
	.loc 1 95 31 is_stmt 0
	sw	a5,20(a4)
.L11:
	.loc 1 100 1
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL6:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.LVL7:
.L12:
	.cfi_restore_state
	.loc 1 98 9 is_stmt 1
	.loc 1 98 14 is_stmt 0
	sh	zero,0(s0)
	.loc 1 100 1
	j	.L11
	.cfi_endproc
.LFE10:
	.size	riscv_wheel_queue_pop, .-riscv_wheel_queue_pop
	.section	.text.riscv_wheel_queue_pop_temp,"ax",@progbits
	.align	1
	.globl	riscv_wheel_queue_pop_temp
	.hidden	riscv_wheel_queue_pop_temp
	.type	riscv_wheel_queue_pop_temp, @function
riscv_wheel_queue_pop_temp:
.LFB11:
	.loc 1 103 1 is_stmt 1
	.cfi_startproc
.LVL8:
	.loc 1 104 5
	.loc 1 103 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 103 1
	mv	s0,a0
	.loc 1 104 9
	call	riscv_wheel_queue_is_empty
.LVL9:
	li	a5,0
	.loc 1 104 7 discriminator 1
	bne	a0,zero,.L16
	.loc 1 106 9 is_stmt 1
	.loc 1 106 35 is_stmt 0
	lla	a5,wheel_q_Ctrl
	lw	a4,20(a5)
	slli	a4,a4,1
	add	a5,a5,a4
	lh	a5,0(a5)
.L16:
	.loc 1 111 1
	lw	ra,8(sp)
	.cfi_restore 1
	sh	a5,0(s0)
	lw	s0,4(sp)
	.cfi_restore 8
.LVL10:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	riscv_wheel_queue_pop_temp, .-riscv_wheel_queue_pop_temp
	.section	.text.riscv_wheel_queue_pop_confirm,"ax",@progbits
	.align	1
	.globl	riscv_wheel_queue_pop_confirm
	.hidden	riscv_wheel_queue_pop_confirm
	.type	riscv_wheel_queue_pop_confirm, @function
riscv_wheel_queue_pop_confirm:
.LFB12:
	.loc 1 114 1 is_stmt 1
	.cfi_startproc
	.loc 1 115 5
	.loc 1 115 27 is_stmt 0
	lla	a4,wheel_q_Ctrl
	.loc 1 115 52
	lw	a5,20(a4)
	addi	a5,a5,1
	.loc 1 115 57
	andi	a5,a5,7
	.loc 1 115 27
	sw	a5,20(a4)
	.loc 1 116 1
	ret
	.cfi_endproc
.LFE12:
	.size	riscv_wheel_queue_pop_confirm, .-riscv_wheel_queue_pop_confirm
	.section	.text.riscv_wheel_queue_update,"ax",@progbits
	.align	1
	.globl	riscv_wheel_queue_update
	.hidden	riscv_wheel_queue_update
	.type	riscv_wheel_queue_update, @function
riscv_wheel_queue_update:
.LFB13:
	.loc 1 119 1 is_stmt 1
	.cfi_startproc
.LVL11:
	.loc 1 120 5
	.loc 1 120 37 is_stmt 0
	lla	a5,wheel_q_Ctrl
	lw	a4,20(a5)
	.loc 1 120 48
	slli	a4,a4,1
	add	a5,a5,a4
	lhu	a4,0(a5)
	add	a4,a4,a0
	sh	a4,0(a5)
	.loc 1 121 1
	ret
	.cfi_endproc
.LFE13:
	.size	riscv_wheel_queue_update, .-riscv_wheel_queue_update
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 67
msg_id_string.0:
	.string	"[M:riscv_ps C:info F: L: ]: riscv_wheel_queue_push - Queue is full"
	.hidden	wheel_q_Ctrl
	.globl	wheel_q_Ctrl
	.section	.bss.wheel_q_Ctrl,"aw",@nobits
	.align	2
	.type	wheel_q_Ctrl, @object
	.size	wheel_q_Ctrl, 24
wheel_q_Ctrl:
	.zero	24
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 4 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x4e9
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x13
	.4byte	.LASF80
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL4
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
	.byte	0x2
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF5
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF6
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
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
	.uleb128 0x14
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x15
	.byte	0x4
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xd
	.4byte	0x75
	.uleb128 0x6
	.4byte	0x7c
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0x25
	.byte	0x13
	.4byte	0x49
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x3
	.byte	0x3d
	.byte	0xe
	.4byte	0xc3
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF19
	.byte	0x3
	.byte	0x42
	.byte	0x3
	.4byte	0x9e
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x3
	.byte	0x45
	.byte	0xe
	.4byte	0x136
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF35
	.byte	0x3
	.byte	0x57
	.byte	0x3
	.4byte	0xcf
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0x3
	.byte	0x59
	.byte	0x10
	.4byte	0x14e
	.uleb128 0x6
	.4byte	0x153
	.uleb128 0xa
	.4byte	0x173
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xc3
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x8
	.byte	0
	.uleb128 0x4
	.4byte	.LASF37
	.byte	0x3
	.byte	0x5a
	.byte	0x10
	.4byte	0x17f
	.uleb128 0x6
	.4byte	0x184
	.uleb128 0xa
	.4byte	0x1ae
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xc3
	.uleb128 0x2
	.4byte	0x1ae
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x8
	.byte	0
	.uleb128 0x6
	.4byte	0x1b3
	.uleb128 0x16
	.uleb128 0x4
	.4byte	.LASF38
	.byte	0x3
	.byte	0x5b
	.byte	0x10
	.4byte	0x1c0
	.uleb128 0x6
	.4byte	0x1c5
	.uleb128 0xa
	.4byte	0x1e0
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xc3
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x8
	.byte	0
	.uleb128 0x4
	.4byte	.LASF39
	.byte	0x3
	.byte	0x5c
	.byte	0x14
	.4byte	0x1ec
	.uleb128 0x6
	.4byte	0x1f1
	.uleb128 0x17
	.4byte	0x92
	.4byte	0x214
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xc3
	.uleb128 0x2
	.4byte	0x136
	.uleb128 0x2
	.4byte	0x214
	.uleb128 0x2
	.4byte	0x219
	.byte	0
	.uleb128 0x6
	.4byte	0x1ae
	.uleb128 0x6
	.4byte	0x92
	.uleb128 0xe
	.byte	0x1c
	.byte	0x3
	.byte	0x5e
	.4byte	0x282
	.uleb128 0x5
	.4byte	.LASF40
	.byte	0x3
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x5
	.4byte	.LASF41
	.byte	0x3
	.byte	0x60
	.byte	0xe
	.4byte	0x92
	.byte	0x4
	.uleb128 0x5
	.4byte	.LASF42
	.byte	0x3
	.byte	0x61
	.byte	0xe
	.4byte	0x92
	.byte	0x8
	.uleb128 0x5
	.4byte	.LASF43
	.byte	0x3
	.byte	0x62
	.byte	0xf
	.4byte	0x142
	.byte	0xc
	.uleb128 0x5
	.4byte	.LASF44
	.byte	0x3
	.byte	0x63
	.byte	0x15
	.4byte	0x173
	.byte	0x10
	.uleb128 0x5
	.4byte	.LASF45
	.byte	0x3
	.byte	0x64
	.byte	0x12
	.4byte	0x1e0
	.byte	0x14
	.uleb128 0x5
	.4byte	.LASF46
	.byte	0x3
	.byte	0x65
	.byte	0x10
	.4byte	0x1b4
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF47
	.byte	0x3
	.byte	0x66
	.byte	0x3
	.4byte	0x21e
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x50
	.byte	0xe
	.4byte	0x2d1
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x8
	.byte	0
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF57
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0x31
	.byte	0x1
	.4byte	0x315
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x7
	.byte	0
	.uleb128 0xe
	.byte	0x18
	.byte	0x1
	.byte	0x2e
	.4byte	0x345
	.uleb128 0x5
	.4byte	.LASF66
	.byte	0x1
	.byte	0x2f
	.byte	0xd
	.4byte	0x345
	.byte	0
	.uleb128 0x5
	.4byte	.LASF67
	.byte	0x1
	.byte	0x30
	.byte	0xe
	.4byte	0x92
	.byte	0x10
	.uleb128 0x5
	.4byte	.LASF68
	.byte	0x1
	.byte	0x31
	.byte	0xe
	.4byte	0x92
	.byte	0x14
	.byte	0
	.uleb128 0xf
	.4byte	0x86
	.4byte	0x355
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF69
	.byte	0x1
	.byte	0x32
	.byte	0x2
	.4byte	0x315
	.uleb128 0x18
	.4byte	.LASF75
	.byte	0x1
	.byte	0x38
	.byte	0x16
	.4byte	0x355
	.uleb128 0x5
	.byte	0x3
	.4byte	wheel_q_Ctrl
	.uleb128 0x19
	.4byte	.LASF81
	.byte	0x3
	.2byte	0x129
	.byte	0xd
	.4byte	0x396
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xc3
	.uleb128 0x2
	.4byte	0x81
	.uleb128 0x2
	.4byte	0x92
	.uleb128 0x8
	.byte	0
	.uleb128 0x9
	.4byte	.LASF70
	.byte	0x76
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x3b9
	.uleb128 0x1a
	.string	"num"
	.byte	0x1
	.byte	0x76
	.byte	0x27
	.4byte	0x86
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF82
	.byte	0x1
	.byte	0x71
	.byte	0x6
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x9
	.4byte	.LASF71
	.byte	0x66
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x3f8
	.uleb128 0x11
	.string	"num"
	.byte	0x66
	.byte	0x2a
	.4byte	0x3f8
	.4byte	.LLST3
	.uleb128 0xb
	.4byte	.LVL9
	.4byte	0x4b2
	.byte	0
	.uleb128 0x6
	.4byte	0x86
	.uleb128 0x9
	.4byte	.LASF72
	.byte	0x5a
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x42a
	.uleb128 0x11
	.string	"num"
	.byte	0x5a
	.byte	0x25
	.4byte	0x3f8
	.4byte	.LLST2
	.uleb128 0xb
	.4byte	.LVL5
	.4byte	0x4b2
	.byte	0
	.uleb128 0x9
	.4byte	.LASF73
	.byte	0x4c
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x49d
	.uleb128 0x1c
	.4byte	.LASF74
	.byte	0x1
	.byte	0x4c
	.byte	0x25
	.4byte	0x86
	.4byte	.LLST0
	.uleb128 0x1d
	.4byte	.LLRL1
	.4byte	0x493
	.uleb128 0x1e
	.4byte	.LASF76
	.byte	0x1
	.byte	0x4f
	.byte	0x29
	.4byte	0x282
	.uleb128 0x1f
	.4byte	.LASF83
	.byte	0x1
	.byte	0x4f
	.byte	0x84
	.4byte	0x4ad
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x20
	.4byte	.LVL3
	.4byte	0x373
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL1
	.4byte	0x4c6
	.byte	0
	.uleb128 0xf
	.4byte	0x7c
	.4byte	0x4ad
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x42
	.byte	0
	.uleb128 0xd
	.4byte	0x49d
	.uleb128 0x12
	.4byte	.LASF77
	.byte	0x47
	.4byte	0x2d1
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x12
	.4byte	.LASF78
	.byte	0x42
	.4byte	0x2d1
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x21
	.4byte	.LASF79
	.byte	0x1
	.byte	0x3c
	.byte	0x6
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
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
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
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
	.uleb128 0x21
	.sleb128 5
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
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0x18
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
	.uleb128 0x1d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x82
	.uleb128 0x19
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
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
.LLST3:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL9-1-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL9-1-.LVL8
	.uleb128 .LVL10-.LVL8
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL10-.LVL8
	.uleb128 .LFE11-.LVL8
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
	.uleb128 .LVL5-1-.LVL4
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL5-1-.LVL4
	.uleb128 .LVL6-.LVL4
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL6-.LVL4
	.uleb128 .LVL7-.LVL4
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
	.uleb128 .LVL7-.LVL4
	.uleb128 .LFE10-.LVL4
	.uleb128 0x1
	.byte	0x58
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
	.uleb128 .LVL2-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL2-.LVL0
	.uleb128 .LFE9-.LVL0
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x54
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
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
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
	.byte	0x4
	.uleb128 .LBB4-.LBB2
	.uleb128 .LBE4-.LBB2
	.byte	0x4
	.uleb128 .LBB5-.LBB2
	.uleb128 .LBE5-.LBB2
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
	.byte	0x7
	.4byte	.LFB12
	.uleb128 .LFE12-.LFB12
	.byte	0x7
	.4byte	.LFB13
	.uleb128 .LFE13-.LFB13
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF67:
	.string	"buf_head"
.LASF40:
	.string	"module_name"
.LASF46:
	.string	"msg_id_handle"
.LASF37:
	.string	"f_dump_buffer_t"
.LASF31:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF21:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF18:
	.string	"PRINT_LEVEL_ERROR"
.LASF7:
	.string	"short int"
.LASF32:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF74:
	.string	"wheel_data"
.LASF39:
	.string	"f_tlv_dump_t"
.LASF29:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF62:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF82:
	.string	"riscv_wheel_queue_pop_confirm"
.LASF51:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF52:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF64:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF69:
	.string	"T_WHEEL_QUEUE_CTRL_S"
.LASF25:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF48:
	.string	"DBG_PIN_SPI_CB"
.LASF70:
	.string	"riscv_wheel_queue_update"
.LASF16:
	.string	"PRINT_LEVEL_INFO"
.LASF73:
	.string	"riscv_wheel_queue_push"
.LASF59:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF23:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF10:
	.string	"long long int"
.LASF71:
	.string	"riscv_wheel_queue_pop_temp"
.LASF12:
	.string	"char"
.LASF8:
	.string	"long int"
.LASF38:
	.string	"f_msg_id_t"
.LASF44:
	.string	"dump_handle"
.LASF54:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF28:
	.string	"LOG_TYPE_HCI_DATA"
.LASF79:
	.string	"riscv_wheel_queue_init_q_ctrl"
.LASF11:
	.string	"long double"
.LASF80:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF6:
	.string	"unsigned char"
.LASF75:
	.string	"wheel_q_Ctrl"
.LASF5:
	.string	"signed char"
.LASF2:
	.string	"long long unsigned int"
.LASF14:
	.string	"uint32_t"
.LASF49:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF3:
	.string	"unsigned int"
.LASF58:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF72:
	.string	"riscv_wheel_queue_pop"
.LASF26:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF20:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF34:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF55:
	.string	"DBG_PIN_USB_TX"
.LASF43:
	.string	"print_handle"
.LASF4:
	.string	"short unsigned int"
.LASF45:
	.string	"tlv_dump_handle"
.LASF19:
	.string	"print_level_t"
.LASF77:
	.string	"riscv_wheel_queue_is_empty"
.LASF57:
	.string	"_Bool"
.LASF36:
	.string	"f_print_t"
.LASF66:
	.string	"buffer"
.LASF13:
	.string	"int16_t"
.LASF17:
	.string	"PRINT_LEVEL_WARNING"
.LASF27:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF47:
	.string	"log_control_block_t"
.LASF60:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF68:
	.string	"buf_tail"
.LASF9:
	.string	"long unsigned int"
.LASF42:
	.string	"print_level"
.LASF61:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF15:
	.string	"PRINT_LEVEL_DEBUG"
.LASF78:
	.string	"riscv_wheel_queue_is_full"
.LASF22:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF63:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF53:
	.string	"DBG_PIN_USB_SOF"
.LASF35:
	.string	"log_type_t"
.LASF24:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF33:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF65:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF50:
	.string	"DBG_PIN_NACK"
.LASF76:
	.string	"log_control_block_riscv_ps"
.LASF83:
	.string	"msg_id_string"
.LASF56:
	.string	"DBG_PIN_MAX"
.LASF30:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF81:
	.string	"print_module_msgid_log"
.LASF41:
	.string	"log_switch"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_wheel_queue.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
