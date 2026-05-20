	.file	"riscv_wheel.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_wheel.c"
	.section	.text.riscv_wheel_trigger_read_process,"ax",@progbits
	.align	1
	.globl	riscv_wheel_trigger_read_process
	.hidden	riscv_wheel_trigger_read_process
	.type	riscv_wheel_trigger_read_process, @function
riscv_wheel_trigger_read_process:
.LFB7:
	.file 1 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_wheel.c"
	.loc 1 106 1
	.cfi_startproc
	.loc 1 110 5
	.loc 1 106 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 110 5
	call	hal_qdec_set_latch_clear
.LVL0:
	.loc 1 115 5 is_stmt 1
	.loc 1 116 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE7:
	.size	riscv_wheel_trigger_read_process, .-riscv_wheel_trigger_read_process
	.section	.text.riscv_wheel_get_data,"ax",@progbits
	.align	1
	.globl	riscv_wheel_get_data
	.hidden	riscv_wheel_get_data
	.type	riscv_wheel_get_data, @function
riscv_wheel_get_data:
.LFB8:
	.loc 1 119 1 is_stmt 1
	.cfi_startproc
.LVL1:
	.loc 1 120 5
	.loc 1 119 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	sw	s1,8(sp)
	sw	ra,16(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 122 17
	sw	zero,0(a0)
	.loc 1 119 1
	mv	s1,a0
	.loc 1 129 15
	addi	a0,sp,3
.LVL2:
	.loc 1 120 13
	sh	zero,4(sp)
	.loc 1 122 5 is_stmt 1
	.loc 1 127 8
	.loc 1 128 9
	.loc 1 129 9
	.loc 1 129 15 is_stmt 0
	call	hal_qdec_latch_status_is_busy
.LVL3:
	.loc 1 132 9 is_stmt 1
	.loc 1 134 20 is_stmt 0
	li	s0,-1
	.loc 1 132 12
	bne	a0,zero,.L3
	mv	s0,a0
	.loc 1 137 9 is_stmt 1
	addi	a0,sp,4
.LVL4:
	call	hal_qdec_get_data
.LVL5:
	.loc 1 140 5
.LBB4:
.LBB5:
	.loc 1 69 5
	.loc 1 71 5
	.loc 1 71 8 is_stmt 0
	lh	a5,4(sp)
	beq	a5,zero,.L5
	.loc 1 72 9 is_stmt 1
	addi	a0,sp,6
	call	riscv_wheel_queue_pop_temp
.LVL6:
	.loc 1 74 9
	.loc 1 74 14 is_stmt 0
	lh	a0,4(sp)
	.loc 1 74 12
	ble	a0,zero,.L6
	.loc 1 74 26 discriminator 1
	lh	a5,6(sp)
	bgt	a5,zero,.L7
.L8:
	.loc 1 78 13 is_stmt 1
	call	riscv_wheel_queue_push
.LVL7:
	j	.L5
.L6:
	.loc 1 74 44 is_stmt 0 discriminator 3
	beq	a0,zero,.L8
	.loc 1 74 60 discriminator 4
	lh	a5,6(sp)
	bge	a5,zero,.L8
.L7:
	.loc 1 75 13 is_stmt 1
	call	riscv_wheel_queue_update
.LVL8:
.L5:
	.loc 1 82 5
	addi	a0,sp,6
	call	riscv_wheel_queue_pop_temp
.LVL9:
	.loc 1 84 5
	.loc 1 84 19 is_stmt 0
	lh	a5,6(sp)
	.loc 1 84 8
	ble	a5,zero,.L9
	.loc 1 85 9 is_stmt 1
	.loc 1 85 18 is_stmt 0
	addi	a5,a5,-1
	.loc 1 86 9
	li	a0,-1
	.loc 1 85 18
	sh	a5,6(sp)
	.loc 1 86 9 is_stmt 1
	call	riscv_wheel_queue_update
.LVL10:
	.loc 1 87 9
	.loc 1 87 12 is_stmt 0
	lh	a5,6(sp)
	bne	a5,zero,.L10
	.loc 1 88 13 is_stmt 1
	call	riscv_wheel_queue_pop_confirm
.LVL11:
.L10:
	.loc 1 90 9
	.loc 1 90 17 is_stmt 0
	li	a5,1
.L26:
	.loc 1 98 17
	sh	a5,4(sp)
.L11:
.LVL12:
.LBE5:
.LBE4:
	.loc 1 142 5 is_stmt 1
	.loc 1 142 7 is_stmt 0
	lw	a4,qdec_reverse_enable
	.loc 1 144 24
	lh	a5,4(sp)
	.loc 1 142 7
	beq	a4,zero,.L13
	.loc 1 144 9 is_stmt 1
	.loc 1 144 23 is_stmt 0
	neg	a5,a5
.L13:
	.loc 1 148 9 is_stmt 1
	.loc 1 148 21 is_stmt 0
	sw	a5,0(s1)
.LVL13:
.L3:
	.loc 1 151 1
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	mv	a0,s0
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
.LVL14:
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL15:
.L9:
	.cfi_restore_state
.LBB7:
.LBB6:
	.loc 1 92 10 is_stmt 1
	.loc 1 92 13 is_stmt 0
	beq	a5,zero,.L11
	.loc 1 93 9 is_stmt 1
	.loc 1 93 18 is_stmt 0
	addi	a5,a5,1
	.loc 1 94 9
	li	a0,1
	.loc 1 93 18
	sh	a5,6(sp)
	.loc 1 94 9 is_stmt 1
	call	riscv_wheel_queue_update
.LVL16:
	.loc 1 95 9
	.loc 1 95 12 is_stmt 0
	lh	a5,6(sp)
	bne	a5,zero,.L12
	.loc 1 96 13 is_stmt 1
	call	riscv_wheel_queue_pop_confirm
.LVL17:
.L12:
	.loc 1 98 9
	.loc 1 98 17 is_stmt 0
	li	a5,-1
	j	.L26
.LBE6:
.LBE7:
	.cfi_endproc
.LFE8:
	.size	riscv_wheel_get_data, .-riscv_wheel_get_data
	.section	.text.riscv_wheel_post_process,"ax",@progbits
	.align	1
	.globl	riscv_wheel_post_process
	.hidden	riscv_wheel_post_process
	.type	riscv_wheel_post_process, @function
riscv_wheel_post_process:
.LFB9:
	.loc 1 156 1 is_stmt 1
	.cfi_startproc
	.loc 1 160 1
	ret
	.cfi_endproc
.LFE9:
	.size	riscv_wheel_post_process, .-riscv_wheel_post_process
	.section	.text.riscv_wheel_init,"ax",@progbits
	.align	1
	.globl	riscv_wheel_init
	.hidden	riscv_wheel_init
	.type	riscv_wheel_init, @function
riscv_wheel_init:
.LFB10:
	.loc 1 163 1
	.cfi_startproc
	.loc 1 164 5
	.loc 1 164 19 is_stmt 0
	lw	a4,hid_common
	.loc 1 164 34
	lw	a5,0(a4)
	.loc 1 163 1
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 164 34
	andi	a5,a5,2
	lla	a3,qdec_reverse_enable
	.loc 1 164 7
	beq	a5,zero,.L29
	.loc 1 166 9 is_stmt 1
	.loc 1 166 29 is_stmt 0
	li	a5,1
	sw	a5,0(a3)
.L29:
	.loc 1 169 5 is_stmt 1
	.loc 1 169 53 is_stmt 0
	lbu	a5,22(a4)
	.loc 1 170 60
	lbu	a4,23(a4)
.LBB8:
	.loc 1 171 280
	lla	a0,log_control_block_riscv_ps
.LBE8:
	.loc 1 169 24
	sb	a5,scroll_ctrl_pin_id,a2
	.loc 1 170 5 is_stmt 1
	.loc 1 170 60 is_stmt 0
	andi	a4,a4,1
.LBB9:
	.loc 1 171 280
	sw	a4,0(sp)
.LBE9:
	.loc 1 170 25
	sb	a4,scroll_active_level,a2
	.loc 1 171 5 is_stmt 1
.LBB10:
	.loc 1 171 10
	.loc 1 171 65
	.loc 1 171 280
	lw	a4,0(a3)
	lla	a2,msg_id_string.1
	li	a3,3
	li	a1,1
	call	print_module_msgid_log
.LVL18:
.LBE10:
	.loc 1 171 8 discriminator 1
	.loc 1 176 5
	call	riscv_wheel_queue_init_q_ctrl
.LVL19:
	.loc 1 177 5
	.loc 1 178 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE10:
	.size	riscv_wheel_init, .-riscv_wheel_init
	.section	.text.riscv_wheel_deinit,"ax",@progbits
	.align	1
	.globl	riscv_wheel_deinit
	.hidden	riscv_wheel_deinit
	.type	riscv_wheel_deinit, @function
riscv_wheel_deinit:
.LFB11:
	.loc 1 181 1 is_stmt 1
	.cfi_startproc
	.loc 1 182 5
.LBB11:
	.loc 1 182 10
	.loc 1 182 65
	.loc 1 182 205
	li	a3,0
	lla	a2,msg_id_string.0
	li	a1,1
	lla	a0,log_control_block_riscv_ps
	tail	print_module_msgid_log
.LVL20:
.LBE11:
	.cfi_endproc
.LFE11:
	.size	riscv_wheel_deinit, .-riscv_wheel_deinit
	.section	.text.riscv_wheel__app_state_update,"ax",@progbits
	.align	1
	.globl	riscv_wheel__app_state_update
	.hidden	riscv_wheel__app_state_update
	.type	riscv_wheel__app_state_update, @function
riscv_wheel__app_state_update:
.LFB12:
	.loc 1 192 1
	.cfi_startproc
.LVL21:
	.loc 1 197 5
	li	a5,3
	bne	a0,a5,.L35
	.loc 1 201 13
	tail	riscv_wheel_deinit
.LVL22:
.L35:
	.loc 1 216 1 is_stmt 0
	ret
	.cfi_endproc
.LFE12:
	.size	riscv_wheel__app_state_update, .-riscv_wheel__app_state_update
	.section	.text.riscv_wheel_debug_print,"ax",@progbits
	.align	1
	.globl	riscv_wheel_debug_print
	.hidden	riscv_wheel_debug_print
	.type	riscv_wheel_debug_print, @function
riscv_wheel_debug_print:
.LFB15:
	.cfi_startproc
	.loc 1 235 6 is_stmt 1
	ret
	.cfi_endproc
.LFE15:
	.size	riscv_wheel_debug_print, .-riscv_wheel_debug_print
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 47
msg_id_string.0:
	.string	"[M:riscv_ps C:info F: L: ]: riscv_wheel_deinit"
	.align	2
	.type	msg_id_string.1, @object
	.size	msg_id_string.1, 122
msg_id_string.1:
	.string	"[M:riscv_ps C:info F: L: ]: riscv_wheel_init, qdec_reverse_enable = %d, scroll_ctrl_pin_id = %d, scroll_active_level = %d"
	.hidden	qdec_reverse_enable
	.globl	qdec_reverse_enable
	.section	.sbss.qdec_reverse_enable,"aw",@nobits
	.align	2
	.type	qdec_reverse_enable, @object
	.size	qdec_reverse_enable, 4
qdec_reverse_enable:
	.zero	4
	.hidden	scroll_active_level
	.globl	scroll_active_level
	.section	.sbss.scroll_active_level,"aw",@nobits
	.type	scroll_active_level, @object
	.size	scroll_active_level, 1
scroll_active_level:
	.zero	1
	.hidden	scroll_ctrl_pin_id
	.globl	scroll_ctrl_pin_id
	.section	.sbss.scroll_ctrl_pin_id,"aw",@nobits
	.type	scroll_ctrl_pin_id, @object
	.size	scroll_ctrl_pin_id, 1
scroll_ctrl_pin_id:
	.zero	1
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_qdec.h"
	.file 6 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 8 "/workdir/airoha/common/applications/hid/inc/hid_common_hid_app_states.h"
	.file 9 "/workdir/airoha/common/applications/hid/inc/hid_common_key_remap.h"
	.file 10 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 11 "/workdir/airoha/common/applications/hid/inc/hid_common.h"
	.file 12 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_wheel_queue.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xe5a
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x22
	.4byte	.LASF220
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL6
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x8
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x8
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x8
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x8
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x8
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x8
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x23
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x8
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x24
	.byte	0x4
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x11
	.4byte	0x75
	.uleb128 0x7
	.4byte	0x7c
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
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x4
	.4byte	.LASF18
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x25
	.4byte	0xc2
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.byte	0x3d
	.byte	0xe
	.4byte	0xf9
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
	.byte	0
	.uleb128 0x4
	.4byte	.LASF23
	.byte	0x3
	.byte	0x42
	.byte	0x3
	.4byte	0xd3
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.byte	0x45
	.byte	0xe
	.4byte	0x16d
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF39
	.byte	0x3
	.byte	0x57
	.byte	0x3
	.4byte	0x105
	.uleb128 0x4
	.4byte	.LASF40
	.byte	0x3
	.byte	0x59
	.byte	0x10
	.4byte	0x185
	.uleb128 0x7
	.4byte	0x18a
	.uleb128 0x14
	.4byte	0x1aa
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0xf9
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0xe
	.byte	0
	.uleb128 0x4
	.4byte	.LASF41
	.byte	0x3
	.byte	0x5a
	.byte	0x10
	.4byte	0x1b6
	.uleb128 0x7
	.4byte	0x1bb
	.uleb128 0x14
	.4byte	0x1e5
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0xf9
	.uleb128 0x3
	.4byte	0x1e5
	.uleb128 0x3
	.4byte	0x65
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0xe
	.byte	0
	.uleb128 0x7
	.4byte	0x1ea
	.uleb128 0x26
	.uleb128 0x4
	.4byte	.LASF42
	.byte	0x3
	.byte	0x5b
	.byte	0x10
	.4byte	0x1f7
	.uleb128 0x7
	.4byte	0x1fc
	.uleb128 0x14
	.4byte	0x217
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0xf9
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xc2
	.uleb128 0xe
	.byte	0
	.uleb128 0x4
	.4byte	.LASF43
	.byte	0x3
	.byte	0x5c
	.byte	0x14
	.4byte	0x223
	.uleb128 0x7
	.4byte	0x228
	.uleb128 0x27
	.4byte	0xc2
	.4byte	0x24b
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0xf9
	.uleb128 0x3
	.4byte	0x16d
	.uleb128 0x3
	.4byte	0x24b
	.uleb128 0x3
	.4byte	0x250
	.byte	0
	.uleb128 0x7
	.4byte	0x1e5
	.uleb128 0x7
	.4byte	0xc2
	.uleb128 0x6
	.byte	0x1c
	.byte	0x3
	.byte	0x5e
	.4byte	0x2b9
	.uleb128 0x2
	.4byte	.LASF44
	.byte	0x3
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x2
	.4byte	.LASF45
	.byte	0x3
	.byte	0x60
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x3
	.byte	0x61
	.byte	0xe
	.4byte	0xc2
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x3
	.byte	0x62
	.byte	0xf
	.4byte	0x179
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF48
	.byte	0x3
	.byte	0x63
	.byte	0x15
	.4byte	0x1aa
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x3
	.byte	0x64
	.byte	0x12
	.4byte	0x217
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF50
	.byte	0x3
	.byte	0x65
	.byte	0x10
	.4byte	0x1eb
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF51
	.byte	0x3
	.byte	0x66
	.byte	0x3
	.4byte	0x255
	.uleb128 0xa
	.4byte	0xaa
	.4byte	0x2d5
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x2a
	.byte	0xe
	.4byte	0x37f
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0xff
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.byte	0x2
	.4byte	.LASF78
	.uleb128 0xc
	.byte	0x5
	.4byte	0x65
	.byte	0x5
	.byte	0x5c
	.byte	0x1
	.4byte	0x3a6
	.uleb128 0x18
	.4byte	.LASF79
	.sleb128 -2
	.uleb128 0x18
	.4byte	.LASF80
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF82
	.byte	0x5
	.byte	0x60
	.byte	0x3
	.4byte	0x386
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0x50
	.byte	0xe
	.4byte	0x3f6
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x8
	.byte	0
	.uleb128 0x6
	.byte	0xa
	.byte	0x6
	.byte	0x5e
	.4byte	0x419
	.uleb128 0x2
	.4byte	.LASF92
	.byte	0x6
	.byte	0x60
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x5
	.string	"pin"
	.byte	0x6
	.byte	0x61
	.byte	0xd
	.4byte	0x419
	.byte	0x2
	.byte	0
	.uleb128 0xa
	.4byte	0xaa
	.4byte	0x429
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF93
	.byte	0x6
	.byte	0x62
	.byte	0x2
	.4byte	0x3f6
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x7
	.byte	0x31
	.byte	0x1
	.4byte	0x473
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x7
	.byte	0
	.uleb128 0x6
	.byte	0x2
	.byte	0x7
	.byte	0x3f
	.4byte	0x496
	.uleb128 0x2
	.4byte	.LASF102
	.byte	0x7
	.byte	0x41
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF103
	.byte	0x7
	.byte	0x42
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF104
	.byte	0x7
	.byte	0x44
	.byte	0x2
	.4byte	0x473
	.uleb128 0xc
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x32
	.byte	0x1
	.4byte	0x5a0
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x41
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x42
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x43
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x44
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x4a
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x4b
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x4c
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x4d
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x4e
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x80
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x81
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x82
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x83
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0x84
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0x8a
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0x8b
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0x8c
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0x8d
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0x8e
	.byte	0
	.uleb128 0x19
	.2byte	0x11c
	.2byte	0x109
	.byte	0xd
	.4byte	0x5c4
	.uleb128 0x1a
	.4byte	.LASF145
	.2byte	0x10a
	.byte	0x1a
	.4byte	0x5c4
	.uleb128 0x28
	.string	"x_y"
	.byte	0x9
	.2byte	0x10c
	.byte	0x1a
	.4byte	0x5c4
	.byte	0
	.uleb128 0xa
	.4byte	0xc2
	.4byte	0x5d4
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x46
	.byte	0
	.uleb128 0x1b
	.2byte	0x23c
	.2byte	0x105
	.4byte	0x60c
	.uleb128 0x12
	.4byte	.LASF146
	.2byte	0x106
	.byte	0x16
	.4byte	0xb6
	.byte	0
	.uleb128 0x12
	.4byte	.LASF147
	.2byte	0x107
	.byte	0x16
	.4byte	0xb6
	.byte	0x2
	.uleb128 0x12
	.4byte	.LASF148
	.2byte	0x108
	.byte	0x16
	.4byte	0x5c4
	.byte	0x4
	.uleb128 0x29
	.4byte	0x5a0
	.2byte	0x120
	.byte	0
	.uleb128 0x19
	.2byte	0x23c
	.2byte	0x103
	.byte	0x5
	.4byte	0x628
	.uleb128 0x1a
	.4byte	.LASF149
	.2byte	0x104
	.byte	0x12
	.4byte	0xc2
	.uleb128 0x2a
	.4byte	0x5d4
	.byte	0
	.uleb128 0x1b
	.2byte	0x240
	.2byte	0x101
	.4byte	0x645
	.uleb128 0x12
	.4byte	.LASF150
	.2byte	0x102
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x1c
	.4byte	0x60c
	.byte	0x4
	.byte	0
	.uleb128 0x2b
	.4byte	.LASF151
	.byte	0x9
	.2byte	0x111
	.byte	0x1e
	.4byte	0x628
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0x50
	.4byte	0x6a1
	.uleb128 0x2
	.4byte	.LASF152
	.byte	0xa
	.byte	0x51
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x5
	.string	"k"
	.byte	0xa
	.byte	0x52
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x5
	.string	"x"
	.byte	0xa
	.byte	0x53
	.byte	0xd
	.4byte	0x92
	.byte	0x2
	.uleb128 0x5
	.string	"y"
	.byte	0xa
	.byte	0x54
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x5
	.string	"z1"
	.byte	0xa
	.byte	0x55
	.byte	0xc
	.4byte	0x86
	.byte	0x6
	.uleb128 0x5
	.string	"z2"
	.byte	0xa
	.byte	0x56
	.byte	0xc
	.4byte	0x86
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF153
	.byte	0xa
	.byte	0x57
	.byte	0x1f
	.4byte	0x652
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0x88
	.4byte	0x6f3
	.uleb128 0x2
	.4byte	.LASF152
	.byte	0xa
	.byte	0x89
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF154
	.byte	0xa
	.byte	0x8a
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF145
	.byte	0xa
	.byte	0x8b
	.byte	0xd
	.4byte	0x2c5
	.byte	0x2
	.uleb128 0x5
	.string	"x"
	.byte	0xa
	.byte	0x8c
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x5
	.string	"y"
	.byte	0xa
	.byte	0x8d
	.byte	0xd
	.4byte	0x92
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF155
	.byte	0xa
	.byte	0x8e
	.byte	0x1e
	.4byte	0x6ad
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0x90
	.4byte	0x745
	.uleb128 0x2
	.4byte	.LASF152
	.byte	0xa
	.byte	0x91
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF156
	.byte	0xa
	.byte	0x92
	.byte	0xe
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF157
	.byte	0xa
	.byte	0x93
	.byte	0xd
	.4byte	0xaa
	.byte	0x3
	.uleb128 0x5
	.string	"x"
	.byte	0xa
	.byte	0x94
	.byte	0xd
	.4byte	0x92
	.byte	0x4
	.uleb128 0x5
	.string	"y"
	.byte	0xa
	.byte	0x95
	.byte	0xd
	.4byte	0x92
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF158
	.byte	0xa
	.byte	0x96
	.byte	0x1f
	.4byte	0x6ff
	.uleb128 0xa
	.4byte	0xaa
	.4byte	0x761
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0xa2
	.4byte	0x79e
	.uleb128 0x2
	.4byte	.LASF152
	.byte	0xa
	.byte	0xa3
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF154
	.byte	0xa
	.byte	0xa4
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF145
	.byte	0xa
	.byte	0xa5
	.byte	0xd
	.4byte	0x751
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF159
	.byte	0xa
	.byte	0xa6
	.byte	0xd
	.4byte	0xaa
	.byte	0x7
	.byte	0
	.uleb128 0x4
	.4byte	.LASF160
	.byte	0xa
	.byte	0xa7
	.byte	0x1e
	.4byte	0x761
	.uleb128 0x6
	.byte	0x8
	.byte	0xa
	.byte	0xa9
	.4byte	0x7e7
	.uleb128 0x2
	.4byte	.LASF152
	.byte	0xa
	.byte	0xaa
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF156
	.byte	0xa
	.byte	0xab
	.byte	0xd
	.4byte	0x7e7
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF157
	.byte	0xa
	.byte	0xac
	.byte	0xd
	.4byte	0xaa
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF159
	.byte	0xa
	.byte	0xad
	.byte	0xd
	.4byte	0x2c5
	.byte	0x6
	.byte	0
	.uleb128 0xa
	.4byte	0xaa
	.4byte	0x7f7
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF161
	.byte	0xa
	.byte	0xae
	.byte	0x1f
	.4byte	0x7aa
	.uleb128 0xa
	.4byte	0xaa
	.4byte	0x813
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0x6
	.byte	0x2
	.byte	0xb
	.byte	0x49
	.4byte	0x835
	.uleb128 0x5
	.string	"id"
	.byte	0xb
	.byte	0x4b
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF162
	.byte	0xb
	.byte	0x4c
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF163
	.byte	0xb
	.byte	0x4d
	.byte	0x2
	.4byte	0x813
	.uleb128 0x2c
	.byte	0x8
	.byte	0xb
	.byte	0x53
	.byte	0x5
	.4byte	0x882
	.uleb128 0xf
	.4byte	.LASF164
	.byte	0x54
	.byte	0x25
	.4byte	0x6a1
	.uleb128 0xf
	.4byte	.LASF165
	.byte	0x56
	.byte	0x23
	.4byte	0x6f3
	.uleb128 0xf
	.4byte	.LASF166
	.byte	0x57
	.byte	0x28
	.4byte	0x745
	.uleb128 0xf
	.4byte	.LASF167
	.byte	0x59
	.byte	0x20
	.4byte	0x79e
	.uleb128 0xf
	.4byte	.LASF168
	.byte	0x5a
	.byte	0x25
	.4byte	0x7f7
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.byte	0xb
	.byte	0x4f
	.4byte	0x891
	.uleb128 0x1c
	.4byte	0x841
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF169
	.byte	0xb
	.byte	0x5f
	.byte	0xa
	.4byte	0x882
	.uleb128 0x6
	.byte	0x8
	.byte	0xb
	.byte	0x61
	.4byte	0x8c0
	.uleb128 0x2
	.4byte	.LASF170
	.byte	0xb
	.byte	0x62
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF171
	.byte	0xb
	.byte	0x63
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.byte	0
	.uleb128 0x4
	.4byte	.LASF172
	.byte	0xb
	.byte	0x67
	.byte	0x2
	.4byte	0x89d
	.uleb128 0x11
	.4byte	0x8c0
	.uleb128 0x6
	.byte	0x3
	.byte	0xb
	.byte	0x69
	.4byte	0x901
	.uleb128 0x2
	.4byte	.LASF173
	.byte	0xb
	.byte	0x6a
	.byte	0xd
	.4byte	0xaa
	.byte	0
	.uleb128 0x2
	.4byte	.LASF174
	.byte	0xb
	.byte	0x6b
	.byte	0xd
	.4byte	0xaa
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF175
	.byte	0xb
	.byte	0x6c
	.byte	0xd
	.4byte	0xaa
	.byte	0x2
	.byte	0
	.uleb128 0x4
	.4byte	.LASF176
	.byte	0xb
	.byte	0x6d
	.byte	0x3
	.4byte	0x8d1
	.uleb128 0x6
	.byte	0x18
	.byte	0xb
	.byte	0x7e
	.4byte	0x964
	.uleb128 0x2
	.4byte	.LASF177
	.byte	0xb
	.byte	0x7f
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF178
	.byte	0xb
	.byte	0x80
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF179
	.byte	0xb
	.byte	0x81
	.byte	0xe
	.4byte	0xc2
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF180
	.byte	0xb
	.byte	0x82
	.byte	0xe
	.4byte	0xc2
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF181
	.byte	0xb
	.byte	0x83
	.byte	0x17
	.4byte	0xce
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF182
	.byte	0xb
	.byte	0x84
	.byte	0xd
	.4byte	0xaa
	.byte	0x14
	.byte	0
	.uleb128 0x4
	.4byte	.LASF183
	.byte	0xb
	.byte	0x94
	.byte	0x3
	.4byte	0x90d
	.uleb128 0x6
	.byte	0x40
	.byte	0xb
	.byte	0x96
	.4byte	0xa2e
	.uleb128 0x2
	.4byte	.LASF180
	.byte	0xb
	.byte	0x97
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF184
	.byte	0xb
	.byte	0x98
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF185
	.byte	0xb
	.byte	0x9b
	.byte	0x1e
	.4byte	0xa2e
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF186
	.byte	0xb
	.byte	0x9c
	.byte	0xe
	.4byte	0xc2
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF187
	.byte	0xb
	.byte	0x9d
	.byte	0xe
	.4byte	0xc2
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF188
	.byte	0xb
	.byte	0x9f
	.byte	0x1e
	.4byte	0x835
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF189
	.byte	0xb
	.byte	0xa0
	.byte	0x1e
	.4byte	0x835
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF190
	.byte	0xb
	.byte	0xa5
	.byte	0xe
	.4byte	0xc2
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF191
	.byte	0xb
	.byte	0xa6
	.byte	0xe
	.4byte	0xc2
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF192
	.byte	0xb
	.byte	0xae
	.byte	0xe
	.4byte	0xa33
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF193
	.byte	0xb
	.byte	0xb1
	.byte	0xd
	.4byte	0x803
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF194
	.byte	0xb
	.byte	0xb2
	.byte	0xd
	.4byte	0xaa
	.byte	0x38
	.uleb128 0x5
	.string	"rr"
	.byte	0xb
	.byte	0xbb
	.byte	0x1d
	.4byte	0x496
	.byte	0x39
	.uleb128 0x5
	.string	"deb"
	.byte	0xb
	.byte	0xbd
	.byte	0x17
	.4byte	0x901
	.byte	0x3b
	.byte	0
	.uleb128 0x7
	.4byte	0x8cc
	.uleb128 0xa
	.4byte	0xb6
	.4byte	0xa43
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.4byte	.LASF195
	.byte	0xb
	.byte	0xbf
	.byte	0x3
	.4byte	0x970
	.uleb128 0x2d
	.2byte	0x16ec
	.byte	0xb
	.byte	0xc1
	.byte	0x9
	.4byte	0xa9c
	.uleb128 0x5
	.string	"app"
	.byte	0xb
	.byte	0xc3
	.byte	0x1b
	.4byte	0xa43
	.byte	0
	.uleb128 0x5
	.string	"hid"
	.byte	0xb
	.byte	0xc4
	.byte	0x1b
	.4byte	0x964
	.byte	0x40
	.uleb128 0x5
	.string	"dbg"
	.byte	0xb
	.byte	0xc5
	.byte	0x17
	.4byte	0x429
	.byte	0x58
	.uleb128 0x2
	.4byte	.LASF196
	.byte	0xb
	.byte	0xc7
	.byte	0x17
	.4byte	0xa9c
	.byte	0x62
	.uleb128 0x2e
	.4byte	.LASF197
	.byte	0xb
	.byte	0xca
	.byte	0x1d
	.4byte	0xaac
	.2byte	0x16e2
	.byte	0
	.uleb128 0xa
	.4byte	0x645
	.4byte	0xaac
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0xa
	.4byte	0x891
	.4byte	0xabc
	.uleb128 0xb
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF198
	.byte	0xb
	.byte	0xcc
	.byte	0x3
	.4byte	0xa4f
	.uleb128 0x15
	.4byte	.LASF199
	.byte	0xb
	.byte	0xd2
	.byte	0x19
	.4byte	0xad4
	.uleb128 0x7
	.4byte	0xabc
	.uleb128 0x16
	.4byte	.LASF200
	.byte	0x3c
	.byte	0x9
	.4byte	0xaa
	.uleb128 0x5
	.byte	0x3
	.4byte	scroll_ctrl_pin_id
	.uleb128 0x16
	.4byte	.LASF201
	.byte	0x3d
	.byte	0x9
	.4byte	0xaa
	.uleb128 0x5
	.byte	0x3
	.4byte	scroll_active_level
	.uleb128 0x16
	.4byte	.LASF202
	.byte	0x40
	.byte	0xa
	.4byte	0xc2
	.uleb128 0x5
	.byte	0x3
	.4byte	qdec_reverse_enable
	.uleb128 0x1d
	.4byte	.LASF218
	.byte	0x41
	.byte	0x11
	.4byte	0xc2
	.uleb128 0x2f
	.4byte	.LASF221
	.byte	0xc
	.byte	0x2e
	.byte	0x6
	.uleb128 0x30
	.4byte	.LASF203
	.byte	0x3
	.2byte	0x129
	.byte	0xd
	.4byte	0xb42
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0xf9
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xc2
	.uleb128 0xe
	.byte	0
	.uleb128 0x31
	.4byte	.LASF222
	.byte	0xc
	.byte	0x32
	.byte	0x6
	.4byte	0xb50
	.uleb128 0xe
	.byte	0
	.uleb128 0x17
	.4byte	.LASF204
	.byte	0x2f
	.4byte	0xb60
	.uleb128 0x3
	.4byte	0x92
	.byte	0
	.uleb128 0x17
	.4byte	.LASF205
	.byte	0x33
	.4byte	0xb70
	.uleb128 0x3
	.4byte	0x92
	.byte	0
	.uleb128 0x17
	.4byte	.LASF206
	.byte	0x31
	.4byte	0xb80
	.uleb128 0x3
	.4byte	0xb80
	.byte	0
	.uleb128 0x7
	.4byte	0x92
	.uleb128 0x1e
	.4byte	.LASF207
	.byte	0x99
	.4byte	0x3a6
	.4byte	0xb99
	.uleb128 0x3
	.4byte	0xb80
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF208
	.byte	0xa3
	.4byte	0x3a6
	.4byte	0xbad
	.uleb128 0x3
	.4byte	0xbad
	.byte	0
	.uleb128 0x7
	.4byte	0x37f
	.uleb128 0x32
	.4byte	.LASF223
	.byte	0x5
	.byte	0x98
	.byte	0x13
	.4byte	0x3a6
	.uleb128 0x33
	.4byte	.LASF224
	.byte	0x1
	.byte	0xeb
	.byte	0x6
	.uleb128 0x34
	.4byte	.LASF210
	.byte	0x1
	.byte	0xbf
	.byte	0x6
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbf5
	.uleb128 0x1f
	.4byte	.LASF213
	.byte	0xbf
	.byte	0x2d
	.4byte	0xc2
	.4byte	.LLST5
	.uleb128 0x35
	.4byte	.LVL22
	.4byte	0xbf5
	.byte	0
	.uleb128 0x36
	.4byte	.LASF225
	.byte	0x1
	.byte	0xb4
	.byte	0x6
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc50
	.uleb128 0x37
	.4byte	.LBB11
	.4byte	.LBE11-.LBB11
	.uleb128 0x15
	.4byte	.LASF209
	.byte	0x1
	.byte	0xb6
	.byte	0x25
	.4byte	0x2b9
	.uleb128 0x13
	.4byte	.LASF212
	.byte	0xb6
	.byte	0x80
	.4byte	0xc60
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x38
	.4byte	.LVL20
	.4byte	0xb1f
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xa
	.4byte	0x7c
	.4byte	0xc60
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x2e
	.byte	0
	.uleb128 0x11
	.4byte	0xc50
	.uleb128 0x20
	.4byte	.LASF211
	.byte	0xa2
	.4byte	0x65
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xccb
	.uleb128 0x39
	.4byte	.LLRL4
	.4byte	0xcc1
	.uleb128 0x15
	.4byte	.LASF209
	.byte	0x1
	.byte	0xab
	.byte	0x25
	.4byte	0x2b9
	.uleb128 0x13
	.4byte	.LASF212
	.byte	0xab
	.byte	0x80
	.4byte	0xcdb
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x21
	.4byte	.LVL18
	.4byte	0xb1f
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.1
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x33
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	.LVL19
	.4byte	0xb17
	.byte	0
	.uleb128 0xa
	.4byte	0x7c
	.4byte	0xcdb
	.uleb128 0xb
	.4byte	0x2d
	.byte	0x79
	.byte	0
	.uleb128 0x11
	.4byte	0xccb
	.uleb128 0x3a
	.4byte	.LASF226
	.byte	0x1
	.byte	0x9b
	.byte	0x6
	.byte	0x1
	.uleb128 0x3b
	.4byte	.LASF227
	.byte	0x1
	.byte	0x76
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe02
	.uleb128 0x1f
	.4byte	.LASF214
	.byte	0x76
	.byte	0x24
	.4byte	0xe02
	.4byte	.LLST0
	.uleb128 0x13
	.4byte	.LASF215
	.byte	0x78
	.byte	0xd
	.4byte	0x92
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x13
	.4byte	.LASF216
	.byte	0x7f
	.byte	0xd
	.4byte	0x37f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -17
	.uleb128 0x3c
	.string	"ret"
	.byte	0x1
	.byte	0x80
	.byte	0x1b
	.4byte	0x3a6
	.4byte	.LLST1
	.uleb128 0x3d
	.4byte	0xe29
	.4byte	.LBB4
	.4byte	.LLRL2
	.byte	0x1
	.byte	0x8c
	.byte	0x5
	.4byte	0xddd
	.uleb128 0x3e
	.4byte	0xe36
	.4byte	.LLST3
	.uleb128 0x3f
	.4byte	.LLRL2
	.uleb128 0x40
	.4byte	0xe42
	.uleb128 0x2
	.byte	0x91
	.sleb128 -14
	.uleb128 0x10
	.4byte	.LVL6
	.4byte	0xb70
	.4byte	0xd7c
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -14
	.byte	0
	.uleb128 0xd
	.4byte	.LVL7
	.4byte	0xb50
	.uleb128 0xd
	.4byte	.LVL8
	.4byte	0xb60
	.uleb128 0x10
	.4byte	.LVL9
	.4byte	0xb70
	.4byte	0xda2
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -14
	.byte	0
	.uleb128 0x10
	.4byte	.LVL10
	.4byte	0xb60
	.4byte	0xdb6
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x9
	.byte	0xff
	.byte	0
	.uleb128 0xd
	.4byte	.LVL11
	.4byte	0xb42
	.uleb128 0x10
	.4byte	.LVL16
	.4byte	0xb60
	.4byte	0xdd2
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0xd
	.4byte	.LVL17
	.4byte	0xb42
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LVL3
	.4byte	0xb99
	.4byte	0xdf1
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -17
	.byte	0
	.uleb128 0x21
	.4byte	.LVL5
	.4byte	0xb85
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	0x9e
	.uleb128 0x20
	.4byte	.LASF217
	.byte	0x69
	.4byte	0x65
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe29
	.uleb128 0xd
	.4byte	.LVL0
	.4byte	0xbb2
	.byte	0
	.uleb128 0x41
	.4byte	.LASF228
	.byte	0x1
	.byte	0x43
	.byte	0xd
	.byte	0x1
	.4byte	0xe4e
	.uleb128 0x42
	.4byte	.LASF215
	.byte	0x1
	.byte	0x43
	.byte	0x2a
	.4byte	0xb80
	.uleb128 0x1d
	.4byte	.LASF219
	.byte	0x45
	.byte	0xd
	.4byte	0x92
	.byte	0
	.uleb128 0x43
	.4byte	0xce0
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
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
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 11
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
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
	.uleb128 0x14
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0x21
	.sleb128 12
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
	.uleb128 0x18
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 19
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x23
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
	.uleb128 0x24
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x29
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
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
	.uleb128 0x2c
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
	.uleb128 0x2d
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
	.uleb128 0x2e
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
	.uleb128 0x2f
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
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x30
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
	.uleb128 0x31
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x33
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x36
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
	.uleb128 0x37
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x38
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
	.uleb128 0x39
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3a
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
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3b
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
	.uleb128 0x3c
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
	.uleb128 0x3d
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x40
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x41
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x42
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
	.byte	0
	.byte	0
	.uleb128 0x43
	.uleb128 0x2e
	.byte	0
	.uleb128 0x31
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
.LLST5:
	.byte	0x6
	.4byte	.LVL21
	.byte	0x4
	.uleb128 .LVL21-.LVL21
	.uleb128 .LVL22-1-.LVL21
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL22-1-.LVL21
	.uleb128 .LVL22-.LVL21
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
	.uleb128 .LVL22-.LVL21
	.uleb128 .LFE12-.LVL21
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST0:
	.byte	0x6
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL2-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL2-.LVL1
	.uleb128 .LVL14-.LVL1
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL14-.LVL1
	.uleb128 .LVL15-.LVL1
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
	.uleb128 .LVL15-.LVL1
	.uleb128 .LFE8-.LVL1
	.uleb128 0x1
	.byte	0x59
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL4-.LVL3
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL4-.LVL3
	.uleb128 .LVL13-.LVL3
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL15-.LVL3
	.uleb128 .LFE8-.LVL3
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL12-.LVL5
	.uleb128 0x3
	.byte	0x91
	.sleb128 -16
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL15-.LVL5
	.uleb128 .LFE8-.LVL5
	.uleb128 0x3
	.byte	0x91
	.sleb128 -16
	.byte	0x9f
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x4c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
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
.LLRL2:
	.byte	0x5
	.4byte	.LBB4
	.byte	0x4
	.uleb128 .LBB4-.LBB4
	.uleb128 .LBE4-.LBB4
	.byte	0x4
	.uleb128 .LBB7-.LBB4
	.uleb128 .LBE7-.LBB4
	.byte	0
.LLRL4:
	.byte	0x5
	.4byte	.LBB8
	.byte	0x4
	.uleb128 .LBB8-.LBB8
	.uleb128 .LBE8-.LBB8
	.byte	0x4
	.uleb128 .LBB9-.LBB8
	.uleb128 .LBE9-.LBB8
	.byte	0x4
	.uleb128 .LBB10-.LBB8
	.uleb128 .LBE10-.LBB8
	.byte	0
.LLRL6:
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
	.4byte	.LFB15
	.uleb128 .LFE15-.LFB15
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF219:
	.string	"queue_num"
.LASF152:
	.string	"report_id"
.LASF162:
	.string	"para"
.LASF211:
	.string	"riscv_wheel_init"
.LASF190:
	.string	"key_remap_enable"
.LASF169:
	.string	"T_HID_CCNI_USB_REPORT_S"
.LASF32:
	.string	"LOG_TYPE_HCI_DATA"
.LASF137:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_1"
.LASF185:
	.string	"combo_key_list"
.LASF139:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_3"
.LASF131:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_1"
.LASF133:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_3"
.LASF138:
	.string	"APP_STATE_2_4G_CONNECTED_IDLE_2"
.LASF164:
	.string	"ms_s16_z8"
.LASF220:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF124:
	.string	"APP_STATE_USB_DISCONNECTING"
.LASF204:
	.string	"riscv_wheel_queue_push"
.LASF55:
	.string	"SLEEP_LOCK_TRNG"
.LASF94:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF49:
	.string	"tlv_dump_handle"
.LASF101:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF171:
	.string	"combo_bit_32_63"
.LASF57:
	.string	"SLEEP_LOCK_IRTX"
.LASF24:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF178:
	.string	"dongle_scenario"
.LASF209:
	.string	"log_control_block_riscv_ps"
.LASF77:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF54:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF29:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF222:
	.string	"riscv_wheel_queue_pop_confirm"
.LASF14:
	.string	"int16_t"
.LASF10:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF213:
	.string	"new_state"
.LASF115:
	.string	"APP_STATE_2_4G_QUICK_CONNECT"
.LASF188:
	.string	"irpt_ctrl"
.LASF191:
	.string	"key_remap_fn_key"
.LASF79:
	.string	"HAL_QDEC_STATUS_ERROR"
.LASF102:
	.string	"rr_idx_2_4g"
.LASF153:
	.string	"T_HID_REPORT_MS_K8_S16_Z8_S"
.LASF118:
	.string	"APP_STATE_CONNECT_CANCEL_CHECK"
.LASF95:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF46:
	.string	"print_level"
.LASF8:
	.string	"long int"
.LASF130:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_ACTIVE"
.LASF40:
	.string	"f_print_t"
.LASF121:
	.string	"APP_STATE_USB_SUSPEND"
.LASF60:
	.string	"SLEEP_LOCK_FLASH"
.LASF184:
	.string	"inActivity_timeout"
.LASF31:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF114:
	.string	"APP_STATE_2_4G_RECONNECT"
.LASF53:
	.string	"SLEEP_LOCK_AESOTF"
.LASF17:
	.string	"uint16_t"
.LASF41:
	.string	"f_dump_buffer_t"
.LASF216:
	.string	"hw_latch_busy"
.LASF100:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF199:
	.string	"hid_common"
.LASF200:
	.string	"scroll_ctrl_pin_id"
.LASF155:
	.string	"T_HID_REPORT_KB_STD2_XY_S"
.LASF223:
	.string	"hal_qdec_set_latch_clear"
.LASF210:
	.string	"riscv_wheel__app_state_update"
.LASF52:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF35:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF159:
	.string	"dummy"
.LASF2:
	.string	"long long unsigned int"
.LASF91:
	.string	"DBG_PIN_MAX"
.LASF151:
	.string	"T_HID_KEY_REMAP_S"
.LASF135:
	.string	"APP_STATE_2_4G_CONNECTED"
.LASF3:
	.string	"unsigned int"
.LASF45:
	.string	"log_switch"
.LASF112:
	.string	"APP_STATE_2_4G_PAIRING"
.LASF147:
	.string	"repeat_times"
.LASF86:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF28:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF110:
	.string	"APP_STATE_CONNECT_PREPARING"
.LASF61:
	.string	"SLEEP_LOCK_ESC"
.LASF9:
	.string	"long unsigned int"
.LASF165:
	.string	"kb_std2"
.LASF125:
	.string	"APP_STATE_BT_CONNECTED"
.LASF167:
	.string	"kb_std5"
.LASF47:
	.string	"print_handle"
.LASF201:
	.string	"scroll_active_level"
.LASF186:
	.string	"combo_key_list_size"
.LASF192:
	.string	"riscv_trigger_time"
.LASF158:
	.string	"T_HID_REPORT_KB_CONSUMER1_XY_S"
.LASF123:
	.string	"APP_STATE_USB_ENTERING_ACTIVE"
.LASF7:
	.string	"short unsigned int"
.LASF22:
	.string	"PRINT_LEVEL_ERROR"
.LASF196:
	.string	"mapped_data"
.LASF68:
	.string	"SLEEP_LOCK_I3C1"
.LASF203:
	.string	"print_module_msgid_log"
.LASF33:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF111:
	.string	"APP_STATE_BT_PAIRING"
.LASF104:
	.string	"T_HID_REPORT_RATE_VAL_S"
.LASF215:
	.string	"number"
.LASF144:
	.string	"APP_STATE_2_4G_DISCONNECTING"
.LASF228:
	.string	"riscv_wheel_get_num"
.LASF21:
	.string	"PRINT_LEVEL_WARNING"
.LASF149:
	.string	"item"
.LASF39:
	.string	"log_type_t"
.LASF67:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF181:
	.string	"outgoing_report_ready"
.LASF180:
	.string	"features"
.LASF183:
	.string	"hid_shared_parameters"
.LASF98:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF205:
	.string	"riscv_wheel_queue_update"
.LASF202:
	.string	"qdec_reverse_enable"
.LASF207:
	.string	"hal_qdec_get_data"
.LASF132:
	.string	"APP_STATE_BT_CONNECTED_ENTERING_IDLE_2"
.LASF217:
	.string	"riscv_wheel_trigger_read_process"
.LASF126:
	.string	"APP_STATE_BT_CONNECTED_ACTIVE"
.LASF90:
	.string	"DBG_PIN_USB_TX"
.LASF194:
	.string	"mouse_key_num"
.LASF225:
	.string	"riscv_wheel_deinit"
.LASF38:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF176:
	.string	"T_DEBOUNCE_PARA_S"
.LASF175:
	.string	"step_bt"
.LASF107:
	.string	"APP_STATE_STANDBY"
.LASF36:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF134:
	.string	"APP_STATE_BT_DISCONNECTING"
.LASF25:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF177:
	.string	"hid_scenario_type"
.LASF74:
	.string	"SLEEP_LOCK_I2C0"
.LASF218:
	.string	"app_state"
.LASF141:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_1"
.LASF212:
	.string	"msg_id_string"
.LASF172:
	.string	"T_AIR_COMBO_KEY_S"
.LASF142:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_2"
.LASF69:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF20:
	.string	"PRINT_LEVEL_INFO"
.LASF148:
	.string	"macro"
.LASF108:
	.string	"APP_STATE_DISCONNECTED"
.LASF193:
	.string	"mouse_key_list"
.LASF174:
	.string	"step_2_4g"
.LASF76:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF34:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF109:
	.string	"APP_STATE_TEST"
.LASF72:
	.string	"SLEEP_LOCK_UART1"
.LASF73:
	.string	"SLEEP_LOCK_UART2"
.LASF78:
	.string	"_Bool"
.LASF15:
	.string	"int32_t"
.LASF5:
	.string	"unsigned char"
.LASF70:
	.string	"SLEEP_LOCK_USB"
.LASF106:
	.string	"APP_STATE_INITIALIZED"
.LASF187:
	.string	"hold_timeout"
.LASF6:
	.string	"short int"
.LASF170:
	.string	"combo_bit_00_31"
.LASF103:
	.string	"rr_idx_usb"
.LASF120:
	.string	"APP_STATE_USB_ACTIVE"
.LASF157:
	.string	"numeric_key_pad"
.LASF37:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF208:
	.string	"hal_qdec_latch_status_is_busy"
.LASF145:
	.string	"keycode"
.LASF65:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF224:
	.string	"riscv_wheel_debug_print"
.LASF96:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF81:
	.string	"HAL_QDEC_STATUS_OK"
.LASF82:
	.string	"hal_qdec_status_t"
.LASF18:
	.string	"uint32_t"
.LASF84:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF214:
	.string	"outgoing_z"
.LASF30:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF197:
	.string	"outgoing_report"
.LASF48:
	.string	"dump_handle"
.LASF11:
	.string	"long double"
.LASF166:
	.string	"kb_consumer1"
.LASF168:
	.string	"kb_consumer2"
.LASF12:
	.string	"char"
.LASF51:
	.string	"log_control_block_t"
.LASF136:
	.string	"APP_STATE_2_4G_CONNECTED_ACTIVE"
.LASF127:
	.string	"APP_STATE_BT_CONNECTED_IDLE_1"
.LASF128:
	.string	"APP_STATE_BT_CONNECTED_IDLE_2"
.LASF129:
	.string	"APP_STATE_BT_CONNECTED_IDLE_3"
.LASF50:
	.string	"msg_id_handle"
.LASF105:
	.string	"APP_STATE_NONE"
.LASF44:
	.string	"module_name"
.LASF140:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_ACTIVE"
.LASF113:
	.string	"APP_STATE_BT_RECONNECT"
.LASF80:
	.string	"HAL_QDEC_INVALID_PARAMETER"
.LASF85:
	.string	"DBG_PIN_NACK"
.LASF62:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF63:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF64:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF173:
	.string	"step_wired"
.LASF198:
	.string	"hid_common_info"
.LASF143:
	.string	"APP_STATE_2_4G_CONNECTED_ENTERING_IDLE_3"
.LASF13:
	.string	"int8_t"
.LASF122:
	.string	"APP_STATE_USB_STOP"
.LASF58:
	.string	"SLEEP_LOCK_IRRX"
.LASF97:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF146:
	.string	"play_mode"
.LASF19:
	.string	"PRINT_LEVEL_DEBUG"
.LASF71:
	.string	"SLEEP_LOCK_UART0"
.LASF163:
	.string	"T_OUTPUT_CTRL_PIN_INFO_S"
.LASF154:
	.string	"combo"
.LASF43:
	.string	"f_tlv_dump_t"
.LASF93:
	.string	"T_COMMON_LA_DBG_S"
.LASF150:
	.string	"status"
.LASF66:
	.string	"SLEEP_LOCK_DCXO"
.LASF161:
	.string	"T_HID_REPORT_KB_CONSUMER2_S"
.LASF156:
	.string	"consumer"
.LASF16:
	.string	"uint8_t"
.LASF75:
	.string	"SLEEP_LOCK_APP"
.LASF160:
	.string	"T_HID_REPORT_KB_STD5_S"
.LASF87:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF179:
	.string	"flags"
.LASF189:
	.string	"scroll_ctrl"
.LASF182:
	.string	"delay_for_key_polling_ms"
.LASF23:
	.string	"print_level_t"
.LASF227:
	.string	"riscv_wheel_get_data"
.LASF117:
	.string	"APP_STATE_CONNECT_CANCEL"
.LASF26:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF195:
	.string	"app_shared_parameters"
.LASF42:
	.string	"f_msg_id_t"
.LASF56:
	.string	"SLEEP_LOCK_DMA"
.LASF119:
	.string	"APP_STATE_USB_CONNECTED"
.LASF89:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF99:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF116:
	.string	"APP_STATE_2_4G_RECONNECT_RESUME_WAIT"
.LASF206:
	.string	"riscv_wheel_queue_pop_temp"
.LASF27:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF88:
	.string	"DBG_PIN_USB_SOF"
.LASF92:
	.string	"enable_mask"
.LASF59:
	.string	"SLEEP_LOCK_AIO"
.LASF226:
	.string	"riscv_wheel_post_process"
.LASF221:
	.string	"riscv_wheel_queue_init_q_ctrl"
.LASF83:
	.string	"DBG_PIN_SPI_CB"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_wheel.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
