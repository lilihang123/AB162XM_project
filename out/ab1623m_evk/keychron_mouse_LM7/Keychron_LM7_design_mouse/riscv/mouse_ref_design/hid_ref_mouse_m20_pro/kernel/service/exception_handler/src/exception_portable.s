	.file	"exception_portable.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/kernel/service/exception_handler/src/exception_portable.c"
	.section	.text.hal_ccni_event_callback16,"ax",@progbits
	.align	1
	.globl	hal_ccni_event_callback16
	.hidden	hal_ccni_event_callback16
	.type	hal_ccni_event_callback16, @function
hal_ccni_event_callback16:
.LFB3:
	.file 1 "/workdir/airoha/risc-v/kernel/service/exception_handler/src/exception_portable.c"
	.loc 1 69 1
	.cfi_startproc
.LVL0:
	.loc 1 70 5
	.loc 1 71 5
	.loc 1 72 5
	.loc 1 73 5
	.loc 1 69 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 73 5
	li	a2,73
	lla	a1,file.1
.LVL1:
	lla	a0,exp.2
.LVL2:
	.loc 1 69 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 73 5
	call	light_assert
.LVL3:
	.loc 1 74 5 is_stmt 1
	.loc 1 75 5
	.loc 1 76 5
	.loc 1 77 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 76 5
	lbu	a5,exception_triggered_flag.0
	.loc 1 77 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE3:
	.size	hal_ccni_event_callback16, .-hal_ccni_event_callback16
	.section	.text.exc_port_alert_other_cores,"ax",@progbits
	.align	1
	.globl	exc_port_alert_other_cores
	.hidden	exc_port_alert_other_cores
	.type	exc_port_alert_other_cores, @function
exc_port_alert_other_cores:
.LFB4:
	.loc 1 92 1 is_stmt 1
	.cfi_startproc
	.loc 1 94 5
	li	a0,33619968
	li	a1,0
	addi	a0,a0,16
	tail	hal_ccni_set_event
.LVL4:
	.cfi_endproc
.LFE4:
	.size	exc_port_alert_other_cores, .-exc_port_alert_other_cores
	.section	.text.exc_port_gpt_get_free_run_1M_count,"ax",@progbits
	.align	1
	.globl	exc_port_gpt_get_free_run_1M_count
	.hidden	exc_port_gpt_get_free_run_1M_count
	.type	exc_port_gpt_get_free_run_1M_count, @function
exc_port_gpt_get_free_run_1M_count:
.LFB5:
	.loc 1 106 1
	.cfi_startproc
.LVL5:
	.loc 1 107 5
	.loc 1 106 1 is_stmt 0
	mv	a1,a0
	.loc 1 107 5
	li	a0,1
.LVL6:
	tail	hal_gpt_get_free_run_count
.LVL7:
	.cfi_endproc
.LFE5:
	.size	exc_port_gpt_get_free_run_1M_count, .-exc_port_gpt_get_free_run_1M_count
	.section	.text.exc_port_gpt_get_free_run_32K_count,"ax",@progbits
	.align	1
	.globl	exc_port_gpt_get_free_run_32K_count
	.hidden	exc_port_gpt_get_free_run_32K_count
	.type	exc_port_gpt_get_free_run_32K_count, @function
exc_port_gpt_get_free_run_32K_count:
.LFB6:
	.loc 1 119 1 is_stmt 1
	.cfi_startproc
.LVL8:
	.loc 1 120 5
	.loc 1 119 1 is_stmt 0
	mv	a1,a0
	.loc 1 120 5
	li	a0,0
.LVL9:
	tail	hal_gpt_get_free_run_count
.LVL10:
	.cfi_endproc
.LFE6:
	.size	exc_port_gpt_get_free_run_32K_count, .-exc_port_gpt_get_free_run_32K_count
	.section	.text.exc_port_core_status_update,"ax",@progbits
	.align	1
	.globl	exc_port_core_status_update
	.hidden	exc_port_core_status_update
	.type	exc_port_core_status_update, @function
exc_port_core_status_update:
.LFB7:
	.loc 1 132 1 is_stmt 1
	.cfi_startproc
	.loc 1 133 5
	.loc 1 134 1 is_stmt 0
	ret
	.cfi_endproc
.LFE7:
	.size	exc_port_core_status_update, .-exc_port_core_status_update
	.section	.text.exc_port_ccni_clear_event,"ax",@progbits
	.align	1
	.globl	exc_port_ccni_clear_event
	.hidden	exc_port_ccni_clear_event
	.type	exc_port_ccni_clear_event, @function
exc_port_ccni_clear_event:
.LFB8:
	.loc 1 145 1 is_stmt 1
	.cfi_startproc
	.loc 1 146 5
	.loc 1 146 12 is_stmt 0
	li	a0,16908288
	addi	a0,a0,16
	tail	hal_ccni_clear_event
.LVL11:
	.cfi_endproc
.LFE8:
	.size	exc_port_ccni_clear_event, .-exc_port_ccni_clear_event
	.section	.text.exc_port_ccni_query_event_status,"ax",@progbits
	.align	1
	.globl	exc_port_ccni_query_event_status
	.hidden	exc_port_ccni_query_event_status
	.type	exc_port_ccni_query_event_status, @function
exc_port_ccni_query_event_status:
.LFB9:
	.loc 1 158 1 is_stmt 1
	.cfi_startproc
	.loc 1 159 5
	.loc 1 158 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 159 14
	sw	zero,0(sp)
	.loc 1 160 5 is_stmt 1
.L9:
	.loc 1 160 26
	lw	a4,0(sp)
	li	a5,1
	bne	a4,a5,.L10
	.loc 1 163 5
	.loc 1 165 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.L10:
	.cfi_restore_state
	.loc 1 161 9 is_stmt 1
	li	a0,16908288
	mv	a1,sp
	addi	a0,a0,16
	call	hal_ccni_query_event_status
.LVL12:
	j	.L9
	.cfi_endproc
.LFE9:
	.size	exc_port_ccni_query_event_status, .-exc_port_ccni_query_event_status
	.section	.sdata.exception_triggered_flag.0,"aw"
	.type	exception_triggered_flag.0, @object
	.size	exception_triggered_flag.0, 1
exception_triggered_flag.0:
	.byte	1
	.section	.log_string,"a"
	.align	2
	.type	file.1, @object
	.size	file.1, 81
file.1:
	.string	"/workdir/airoha/risc-v/kernel/service/exception_handler/src/exception_portable.c"
	.align	2
	.type	exp.2, @object
	.size	exp.2, 10
exp.2:
	.string	"Triggered"
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/../inc/hal_ccni.h"
	.file 5 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_ccni_config.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 7 "/workdir/airoha/risc-v/kernel/service/exception_handler/inc/exception_handler.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x53f
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x16
	.4byte	.LASF92
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
	.uleb128 0x17
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x18
	.byte	0x4
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xb
	.4byte	0x75
	.uleb128 0xc
	.4byte	0x7c
	.uleb128 0x19
	.4byte	.LASF15
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0xc
	.4byte	0x86
	.uleb128 0xd
	.4byte	0x86
	.4byte	0xa7
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.2byte	0x466
	.4byte	0xc1
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x1
	.byte	0
	.uleb128 0x6
	.4byte	.LASF16
	.byte	0x3
	.2byte	0x469
	.byte	0x3
	.4byte	0xa7
	.uleb128 0x7
	.byte	0x5
	.4byte	0x65
	.byte	0x4
	.2byte	0x120
	.4byte	0xfa
	.uleb128 0x4
	.4byte	.LASF17
	.sleb128 -4
	.uleb128 0x4
	.4byte	.LASF18
	.sleb128 -3
	.uleb128 0x4
	.4byte	.LASF19
	.sleb128 -2
	.uleb128 0x4
	.4byte	.LASF20
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	.LASF22
	.byte	0x4
	.2byte	0x126
	.byte	0x3
	.4byte	0xce
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.2byte	0x129
	.4byte	0x121
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x1
	.byte	0
	.uleb128 0x6
	.4byte	.LASF25
	.byte	0x4
	.2byte	0x137
	.byte	0x12
	.4byte	0x86
	.uleb128 0x1a
	.byte	0x8
	.byte	0x4
	.2byte	0x13d
	.byte	0x5
	.4byte	0x153
	.uleb128 0x11
	.string	"ptr"
	.2byte	0x13e
	.byte	0xf
	.4byte	0x73
	.byte	0
	.uleb128 0x11
	.string	"len"
	.2byte	0x13f
	.byte	0x12
	.4byte	0x86
	.byte	0x4
	.byte	0
	.uleb128 0x1b
	.byte	0x8
	.byte	0x4
	.2byte	0x13c
	.byte	0x9
	.4byte	0x176
	.uleb128 0x12
	.4byte	.LASF26
	.2byte	0x140
	.byte	0x7
	.4byte	0x12e
	.uleb128 0x12
	.4byte	.LASF27
	.2byte	0x141
	.byte	0xe
	.4byte	0x97
	.byte	0
	.uleb128 0x6
	.4byte	.LASF28
	.byte	0x4
	.2byte	0x142
	.byte	0x3
	.4byte	0x153
	.uleb128 0xc
	.4byte	0x176
	.uleb128 0x13
	.4byte	0x2d
	.byte	0x35
	.4byte	0x1b4
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x3
	.uleb128 0x1c
	.4byte	.LASF33
	.4byte	0xffffffff
	.byte	0
	.uleb128 0x13
	.4byte	0x2d
	.byte	0x3d
	.4byte	0x285
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
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x20
	.byte	0
	.uleb128 0x7
	.byte	0x5
	.4byte	0x65
	.byte	0x6
	.2byte	0x153
	.4byte	0x2c3
	.uleb128 0x4
	.4byte	.LASF67
	.sleb128 -7
	.uleb128 0x4
	.4byte	.LASF68
	.sleb128 -6
	.uleb128 0x4
	.4byte	.LASF69
	.sleb128 -5
	.uleb128 0x4
	.4byte	.LASF70
	.sleb128 -4
	.uleb128 0x4
	.4byte	.LASF71
	.sleb128 -3
	.uleb128 0x4
	.4byte	.LASF72
	.sleb128 -2
	.uleb128 0x4
	.4byte	.LASF73
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	.LASF75
	.byte	0x6
	.2byte	0x15c
	.byte	0x3
	.4byte	0x285
	.uleb128 0x8
	.4byte	.LASF76
	.byte	0x4
	.2byte	0x177
	.byte	0x13
	.4byte	0xfa
	.4byte	0x2ec
	.uleb128 0x5
	.4byte	0x121
	.uleb128 0x5
	.4byte	0x92
	.byte	0
	.uleb128 0x8
	.4byte	.LASF77
	.byte	0x4
	.2byte	0x169
	.byte	0x13
	.4byte	0xfa
	.4byte	0x303
	.uleb128 0x5
	.4byte	0x121
	.byte	0
	.uleb128 0x8
	.4byte	.LASF78
	.byte	0x6
	.2byte	0x17b
	.byte	0x12
	.4byte	0x2c3
	.4byte	0x31f
	.uleb128 0x5
	.4byte	0xc1
	.uleb128 0x5
	.4byte	0x92
	.byte	0
	.uleb128 0x8
	.4byte	.LASF79
	.byte	0x4
	.2byte	0x15f
	.byte	0x13
	.4byte	0xfa
	.4byte	0x33b
	.uleb128 0x5
	.4byte	0x121
	.uleb128 0x5
	.4byte	0x183
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF93
	.byte	0x7
	.byte	0x44
	.byte	0xd
	.4byte	0x357
	.uleb128 0x5
	.4byte	0x81
	.uleb128 0x5
	.4byte	0x81
	.uleb128 0x5
	.4byte	0x65
	.byte	0
	.uleb128 0x14
	.4byte	.LASF80
	.byte	0x9d
	.4byte	0x65
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x397
	.uleb128 0xf
	.4byte	.LASF88
	.byte	0x9f
	.byte	0xe
	.4byte	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x15
	.4byte	.LVL12
	.4byte	0x2d0
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x1020010
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x14
	.4byte	.LASF81
	.byte	0x90
	.4byte	0x65
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x3c3
	.uleb128 0x9
	.4byte	.LVL11
	.4byte	0x2ec
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x1020010
	.byte	0
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF94
	.byte	0x1
	.byte	0x83
	.byte	0x6
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xa
	.4byte	.LASF82
	.byte	0x76
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x415
	.uleb128 0x10
	.4byte	.LASF84
	.byte	0x76
	.byte	0x34
	.4byte	0x92
	.4byte	.LLST3
	.uleb128 0x9
	.4byte	.LVL10
	.4byte	0x303
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
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
	.uleb128 0xa
	.4byte	.LASF83
	.byte	0x69
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x455
	.uleb128 0x10
	.4byte	.LASF84
	.byte	0x69
	.byte	0x33
	.4byte	0x92
	.4byte	.LLST2
	.uleb128 0x9
	.4byte	.LVL7
	.4byte	0x303
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
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
	.uleb128 0xa
	.4byte	.LASF85
	.byte	0x5b
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x482
	.uleb128 0x9
	.4byte	.LVL4
	.4byte	0x31f
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x2010010
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0xa
	.4byte	.LASF86
	.byte	0x44
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x50c
	.uleb128 0x10
	.4byte	.LASF87
	.byte	0x44
	.byte	0x31
	.4byte	0x121
	.4byte	.LLST0
	.uleb128 0x1f
	.string	"msg"
	.byte	0x1
	.byte	0x44
	.byte	0x4c
	.4byte	0x183
	.4byte	.LLST1
	.uleb128 0xf
	.4byte	.LASF89
	.byte	0x46
	.byte	0x19
	.4byte	0x513
	.uleb128 0x5
	.byte	0x3
	.4byte	exception_triggered_flag.0
	.uleb128 0x20
	.string	"exp"
	.byte	0x1
	.byte	0x47
	.byte	0x44
	.4byte	0x528
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.2
	.uleb128 0xf
	.4byte	.LASF90
	.byte	0x48
	.byte	0x44
	.4byte	0x53d
	.uleb128 0x5
	.byte	0x3
	.4byte	file.1
	.uleb128 0x15
	.4byte	.LVL3
	.4byte	0x33b
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.2
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.1
	.uleb128 0x3
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x49
	.byte	0
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF91
	.uleb128 0x21
	.4byte	0x50c
	.uleb128 0xd
	.4byte	0x7c
	.4byte	0x528
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x9
	.byte	0
	.uleb128 0xb
	.4byte	0x518
	.uleb128 0xd
	.4byte	0x7c
	.4byte	0x53d
	.uleb128 0xe
	.4byte	0x2d
	.byte	0x50
	.byte	0
	.uleb128 0xb
	.4byte	0x52d
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x5
	.byte	0
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
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
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
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
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
	.sleb128 5
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
	.uleb128 0x15
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0x1c
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x35
	.byte	0
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
.LLST3:
	.byte	0x6
	.4byte	.LVL8
	.byte	0x4
	.uleb128 .LVL8-.LVL8
	.uleb128 .LVL9-.LVL8
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL9-.LVL8
	.uleb128 .LVL10-1-.LVL8
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL10-1-.LVL8
	.uleb128 .LFE6-.LVL8
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
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL6-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL6-.LVL5
	.uleb128 .LVL7-1-.LVL5
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL7-1-.LVL5
	.uleb128 .LFE5-.LVL5
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
	.uleb128 .LFE3-.LVL0
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
	.uleb128 .LVL1-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL1-.LVL0
	.uleb128 .LFE3-.LVL0
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
	.4byte	0x4c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
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
.LLRL4:
	.byte	0x7
	.4byte	.LFB3
	.uleb128 .LFE3-.LFB3
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
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
.LASF18:
	.string	"HAL_CCNI_STATUS_BUSY"
.LASF78:
	.string	"hal_gpt_get_free_run_count"
.LASF93:
	.string	"light_assert"
.LASF30:
	.string	"HAL_CCNI_CORE_MCU"
.LASF27:
	.string	"data"
.LASF25:
	.string	"hal_ccni_event_t"
.LASF20:
	.string	"HAL_CCNI_STATUS_NO_INIT"
.LASF6:
	.string	"short int"
.LASF21:
	.string	"HAL_CCNI_STATUS_OK"
.LASF14:
	.string	"HAL_GPT_CLOCK_SOURCE_1M"
.LASF28:
	.string	"hal_ccni_message_t"
.LASF74:
	.string	"HAL_GPT_STATUS_OK"
.LASF79:
	.string	"hal_ccni_set_event"
.LASF82:
	.string	"exc_port_gpt_get_free_run_32K_count"
.LASF87:
	.string	"event"
.LASF44:
	.string	"HAL_CCNI_EVENT10"
.LASF45:
	.string	"HAL_CCNI_EVENT11"
.LASF46:
	.string	"HAL_CCNI_EVENT12"
.LASF47:
	.string	"HAL_CCNI_EVENT13"
.LASF48:
	.string	"HAL_CCNI_EVENT14"
.LASF49:
	.string	"HAL_CCNI_EVENT15"
.LASF50:
	.string	"HAL_CCNI_EVENT16"
.LASF51:
	.string	"HAL_CCNI_EVENT17"
.LASF52:
	.string	"HAL_CCNI_EVENT18"
.LASF53:
	.string	"HAL_CCNI_EVENT19"
.LASF19:
	.string	"HAL_CCNI_STATUS_ERROR"
.LASF34:
	.string	"HAL_CCNI_EVENT0"
.LASF35:
	.string	"HAL_CCNI_EVENT1"
.LASF36:
	.string	"HAL_CCNI_EVENT2"
.LASF37:
	.string	"HAL_CCNI_EVENT3"
.LASF38:
	.string	"HAL_CCNI_EVENT4"
.LASF39:
	.string	"HAL_CCNI_EVENT5"
.LASF40:
	.string	"HAL_CCNI_EVENT6"
.LASF41:
	.string	"HAL_CCNI_EVENT7"
.LASF42:
	.string	"HAL_CCNI_EVENT8"
.LASF43:
	.string	"HAL_CCNI_EVENT9"
.LASF69:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF85:
	.string	"exc_port_alert_other_cores"
.LASF73:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF26:
	.string	"variable_len_msg"
.LASF11:
	.string	"long double"
.LASF17:
	.string	"HAL_CCNI_STATUS_INVALID_PARAMETER"
.LASF10:
	.string	"long long int"
.LASF75:
	.string	"hal_gpt_status_t"
.LASF76:
	.string	"hal_ccni_query_event_status"
.LASF70:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF8:
	.string	"long int"
.LASF13:
	.string	"HAL_GPT_CLOCK_SOURCE_32K"
.LASF31:
	.string	"HAL_CCNI_CORE_RISCV"
.LASF54:
	.string	"HAL_CCNI_EVENT20"
.LASF55:
	.string	"HAL_CCNI_EVENT21"
.LASF56:
	.string	"HAL_CCNI_EVENT22"
.LASF57:
	.string	"HAL_CCNI_EVENT23"
.LASF58:
	.string	"HAL_CCNI_EVENT24"
.LASF59:
	.string	"HAL_CCNI_EVENT25"
.LASF60:
	.string	"HAL_CCNI_EVENT26"
.LASF61:
	.string	"HAL_CCNI_EVENT27"
.LASF62:
	.string	"HAL_CCNI_EVENT28"
.LASF63:
	.string	"HAL_CCNI_EVENT29"
.LASF5:
	.string	"unsigned char"
.LASF90:
	.string	"file"
.LASF4:
	.string	"signed char"
.LASF72:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF2:
	.string	"long long unsigned int"
.LASF22:
	.string	"hal_ccni_status_t"
.LASF15:
	.string	"uint32_t"
.LASF23:
	.string	"HAL_CCNI_EVENT_STATUS_IDLE"
.LASF3:
	.string	"unsigned int"
.LASF16:
	.string	"hal_gpt_clock_source_t"
.LASF33:
	.string	"HAL_CCNI_CORE_RESERVED"
.LASF7:
	.string	"short unsigned int"
.LASF67:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF12:
	.string	"char"
.LASF88:
	.string	"master_status"
.LASF80:
	.string	"exc_port_ccni_query_event_status"
.LASF92:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF91:
	.string	"_Bool"
.LASF94:
	.string	"exc_port_core_status_update"
.LASF64:
	.string	"HAL_CCNI_EVENT30"
.LASF65:
	.string	"HAL_CCNI_EVENT31"
.LASF71:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF9:
	.string	"long unsigned int"
.LASF86:
	.string	"hal_ccni_event_callback16"
.LASF84:
	.string	"count"
.LASF32:
	.string	"HAL_CCNI_CORE_END"
.LASF66:
	.string	"HAL_CCNI_EVENT_MAX"
.LASF68:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF24:
	.string	"HAL_CCNI_EVENT_STATUS_BUSY"
.LASF29:
	.string	"HAL_CCNI_CORE_START"
.LASF81:
	.string	"exc_port_ccni_clear_event"
.LASF77:
	.string	"hal_ccni_clear_event"
.LASF89:
	.string	"exception_triggered_flag"
.LASF83:
	.string	"exc_port_gpt_get_free_run_1M_count"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/kernel/service/exception_handler/src/exception_portable.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
