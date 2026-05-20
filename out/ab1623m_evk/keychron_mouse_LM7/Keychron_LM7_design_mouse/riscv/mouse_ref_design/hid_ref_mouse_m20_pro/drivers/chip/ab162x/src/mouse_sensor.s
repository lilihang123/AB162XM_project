	.file	"mouse_sensor.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/mouse_sensor.c"
	.section	.text.mouse_sensor_burst_read,"ax",@progbits
	.align	1
	.globl	mouse_sensor_burst_read
	.hidden	mouse_sensor_burst_read
	.type	mouse_sensor_burst_read, @function
mouse_sensor_burst_read:
.LFB15:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/mouse_sensor.c"
	.loc 1 49 48
	.cfi_startproc
.LVL0:
	.loc 1 54 5
	.loc 1 54 7 is_stmt 0
	lbu	a5,ccm_spi_sensor+8
	.loc 1 55 16
	li	a0,-8
.LVL1:
	.loc 1 54 7
	beq	a5,zero,.L6
	lla	a2,ccm_spi_sensor
	.loc 1 57 5 is_stmt 1
	.loc 1 57 7 is_stmt 0
	lbu	a5,7(a2)
	.loc 1 58 16
	li	a0,-10
	.loc 1 57 7
	beq	a5,zero,.L6
	.loc 1 60 5 is_stmt 1
	.loc 1 49 48 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	.loc 1 60 5
	lla	a1,burst_reg
	li	a0,0
	.loc 1 49 48
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 60 5
	call	hal_spi_master_restore_address_advanced
.LVL2:
	.loc 1 61 5 is_stmt 1
	li	a1,1
	li	a0,0
	call	hal_spi_master_trigger_start
.LVL3:
	.loc 1 82 5
	.loc 1 83 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 82 12
	li	a0,0
	.loc 1 83 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
.L6:
	ret
	.cfi_endproc
.LFE15:
	.size	mouse_sensor_burst_read, .-mouse_sensor_burst_read
	.section	.text.hal_ccni_event_callback20,"ax",@progbits
	.align	1
	.globl	hal_ccni_event_callback20
	.hidden	hal_ccni_event_callback20
	.type	hal_ccni_event_callback20, @function
hal_ccni_event_callback20:
.LFB16:
	.loc 1 86 1 is_stmt 1
	.cfi_startproc
.LVL4:
	.loc 1 87 5
	.loc 1 88 5
	.loc 1 86 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 88 5
	mv	a0,sp
.LVL5:
	.loc 1 86 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 88 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL6:
	.loc 1 89 5 is_stmt 1
	.loc 1 90 5 is_stmt 0
	lw	a0,0(sp)
	.loc 1 89 20
	sb	zero,workround_flag,a5
	.loc 1 90 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL7:
	.loc 1 91 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE16:
	.size	hal_ccni_event_callback20, .-hal_ccni_event_callback20
	.section	.text.mouse_sensor_send_report_to_CM33,"ax",@progbits
	.align	1
	.globl	mouse_sensor_send_report_to_CM33
	.hidden	mouse_sensor_send_report_to_CM33
	.type	mouse_sensor_send_report_to_CM33, @function
mouse_sensor_send_report_to_CM33:
.LFB17:
	.loc 1 93 1 is_stmt 1
	.cfi_startproc
.LVL8:
	.loc 1 94 5
	li	a0,33619968
.LVL9:
	li	a1,0
	addi	a0,a0,15
	tail	hal_ccni_set_event
.LVL10:
	.cfi_endproc
.LFE17:
	.size	mouse_sensor_send_report_to_CM33, .-mouse_sensor_send_report_to_CM33
	.section	.text.mouse_sensor_get_data,"ax",@progbits
	.align	1
	.globl	mouse_sensor_get_data
	.hidden	mouse_sensor_get_data
	.type	mouse_sensor_get_data, @function
mouse_sensor_get_data:
.LFB18:
	.loc 1 97 59
	.cfi_startproc
.LVL11:
	.loc 1 98 5
	.loc 1 99 5
	.loc 1 99 7 is_stmt 0
	lbu	a4,ccm_spi_sensor+8
	beq	a4,zero,.L16
	lla	a5,ccm_spi_sensor
	.loc 1 103 5 is_stmt 1
	.loc 1 103 47 is_stmt 0
	lbu	a4,1(a5)
	andi	a4,a4,8
	sw	a4,is_lifted,a3
	.loc 1 105 5 is_stmt 1
	.loc 1 105 7 is_stmt 0
	lbu	a4,2(a5)
	li	a3,183
	andi	a4,a4,247
	beq	a4,a3,.L14
	.loc 1 106 9 is_stmt 1
	.loc 1 97 59 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 106 27
	lla	s0,workround_flag
	.loc 1 106 11
	lbu	a5,0(s0)
	bne	a5,zero,.L15
	.loc 1 107 13 is_stmt 1
	mv	a0,sp
.LVL12:
	call	hal_nvic_save_and_set_interrupt_mask
.LVL13:
	.loc 1 108 13
	.loc 1 109 13 is_stmt 0
	lw	a0,0(sp)
	.loc 1 108 28
	li	a5,1
	sb	a5,0(s0)
	.loc 1 109 13 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL14:
	.loc 1 110 13
	li	a0,0
	call	mouse_sensor_send_report_to_CM33
.LVL15:
.L15:
	.loc 1 122 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	.loc 1 112 16
	li	a0,-9
	.loc 1 122 1
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL16:
.L14:
	.loc 1 115 5 is_stmt 1
	lbu	a3,3(a5)
	lbu	a4,4(a5)
	slli	a4,a4,8
	or	a4,a4,a3
	.loc 1 116 5
	.loc 1 116 13 is_stmt 0
	sh	a4,0(a0)
	.loc 1 118 5 is_stmt 1
	lbu	a4,5(a5)
	lbu	a5,6(a5)
	.loc 1 121 12 is_stmt 0
	li	a0,0
.LVL17:
	slli	a5,a5,8
	or	a5,a5,a4
	.loc 1 119 5 is_stmt 1
	.loc 1 119 13 is_stmt 0
	sh	a5,0(a1)
	.loc 1 121 5 is_stmt 1
	.loc 1 121 12 is_stmt 0
	ret
.LVL18:
.L16:
	.loc 1 100 16
	li	a0,-8
.LVL19:
	.loc 1 122 1
	ret
	.cfi_endproc
.LFE18:
	.size	mouse_sensor_get_data, .-mouse_sensor_get_data
	.section	.text.mouse_sensor_register_callback,"ax",@progbits
	.align	1
	.globl	mouse_sensor_register_callback
	.hidden	mouse_sensor_register_callback
	.type	mouse_sensor_register_callback, @function
mouse_sensor_register_callback:
.LFB19:
	.loc 1 124 87 is_stmt 1
	.cfi_startproc
.LVL20:
	.loc 1 125 5
	.loc 1 124 87 is_stmt 0
	mv	a2,a1
	.loc 1 125 12
	mv	a1,a0
.LVL21:
	li	a0,0
.LVL22:
	tail	hal_spi_master_register_callback
.LVL23:
	.cfi_endproc
.LFE19:
	.size	mouse_sensor_register_callback, .-mouse_sensor_register_callback
	.section	.text.mouse_sensor_is_lifted,"ax",@progbits
	.align	1
	.globl	mouse_sensor_is_lifted
	.hidden	mouse_sensor_is_lifted
	.type	mouse_sensor_is_lifted, @function
mouse_sensor_is_lifted:
.LFB20:
	.loc 1 129 1 is_stmt 1
	.cfi_startproc
	.loc 1 130 5
	.loc 1 131 1 is_stmt 0
	lw	a0,is_lifted
	ret
	.cfi_endproc
.LFE20:
	.size	mouse_sensor_is_lifted, .-mouse_sensor_is_lifted
	.hidden	burst_reg
	.globl	burst_reg
	.section	.sdata.burst_reg,"aw"
	.align	4
	.type	burst_reg, @object
	.size	burst_reg, 1
burst_reg:
	.byte	22
	.hidden	is_lifted
	.globl	is_lifted
	.section	.sbss.is_lifted,"aw",@nobits
	.align	2
	.type	is_lifted, @object
	.size	is_lifted, 4
is_lifted:
	.zero	4
	.hidden	workround_flag
	.globl	workround_flag
	.section	.sbss.workround_flag,"aw",@nobits
	.type	workround_flag, @object
	.size	workround_flag, 1
workround_flag:
	.zero	1
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_spi_master.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/mouse_sensor.h"
	.file 7 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_spi_sensor.h"
	.file 8 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_eint_internal.h"
	.file 9 "/workdir/airoha/common/drivers/chip/ab162x/../inc/hal_ccni.h"
	.file 10 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_ccni_config.h"
	.file 11 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 12 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 13 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_cross_core_config.h"
	.file 14 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 15 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xa42
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x1d
	.4byte	.LASF250
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
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x1e
	.4byte	.LASF251
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0xf
	.2byte	0x128
	.byte	0x12
	.4byte	0xc1
	.uleb128 0x1
	.4byte	.LASF5
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF6
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF7
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF8
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF9
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF10
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF11
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF12
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x1f
	.byte	0
	.uleb128 0x4
	.byte	0x1
	.byte	0x6
	.4byte	.LASF24
	.uleb128 0xc
	.4byte	.LASF28
	.byte	0x2
	.byte	0x25
	.byte	0x13
	.4byte	0xd4
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.4byte	.LASF25
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.4byte	.LASF26
	.uleb128 0x4
	.byte	0x8
	.byte	0x5
	.4byte	.LASF27
	.uleb128 0xc
	.4byte	.LASF29
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x34
	.uleb128 0x11
	.4byte	0xe9
	.uleb128 0x4
	.byte	0x2
	.byte	0x7
	.4byte	.LASF30
	.uleb128 0xc
	.4byte	.LASF31
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x10d
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.4byte	.LASF32
	.uleb128 0x1f
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0xe
	.4byte	0x101
	.4byte	0x12b
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0xb
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.2byte	0x373
	.4byte	0x14b
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x2
	.byte	0
	.uleb128 0x7
	.4byte	.LASF36
	.byte	0x3
	.2byte	0x377
	.byte	0x3
	.4byte	0x12b
	.uleb128 0xb
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.2byte	0x407
	.4byte	0x2bc
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x38
	.byte	0
	.uleb128 0x4
	.byte	0x10
	.byte	0x4
	.4byte	.LASF94
	.uleb128 0x20
	.byte	0x4
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF95
	.uleb128 0x8
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x2a
	.byte	0xe
	.4byte	0x376
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0xff
	.byte	0
	.uleb128 0x4
	.byte	0x1
	.byte	0x2
	.4byte	.LASF122
	.uleb128 0xb
	.byte	0x7
	.4byte	0x2d
	.byte	0x5
	.2byte	0x2a5
	.4byte	0x39d
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x2
	.byte	0
	.uleb128 0x7
	.4byte	.LASF126
	.byte	0x5
	.2byte	0x2a9
	.byte	0x3
	.4byte	0x37d
	.uleb128 0xb
	.byte	0x5
	.4byte	0x114
	.byte	0x5
	.2byte	0x2ad
	.4byte	0x3e8
	.uleb128 0x2
	.4byte	.LASF127
	.sleb128 -7
	.uleb128 0x2
	.4byte	.LASF128
	.sleb128 -6
	.uleb128 0x2
	.4byte	.LASF129
	.sleb128 -5
	.uleb128 0x2
	.4byte	.LASF130
	.sleb128 -4
	.uleb128 0x2
	.4byte	.LASF131
	.sleb128 -3
	.uleb128 0x2
	.4byte	.LASF132
	.sleb128 -2
	.uleb128 0x2
	.4byte	.LASF133
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	.LASF135
	.byte	0x5
	.2byte	0x2b6
	.byte	0x3
	.4byte	0x3aa
	.uleb128 0x7
	.4byte	.LASF136
	.byte	0x5
	.2byte	0x2d2
	.byte	0x10
	.4byte	0x402
	.uleb128 0x9
	.4byte	0x407
	.uleb128 0x21
	.4byte	0x417
	.uleb128 0x3
	.4byte	0x39d
	.uleb128 0x3
	.4byte	0x2c3
	.byte	0
	.uleb128 0x9
	.4byte	0xe9
	.uleb128 0x8
	.byte	0x5
	.4byte	0x114
	.byte	0x6
	.byte	0x27
	.byte	0xe
	.4byte	0x442
	.uleb128 0x2
	.4byte	.LASF137
	.sleb128 -10
	.uleb128 0x2
	.4byte	.LASF138
	.sleb128 -9
	.uleb128 0x2
	.4byte	.LASF139
	.sleb128 -8
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0
	.byte	0
	.uleb128 0x22
	.4byte	.LASF252
	.byte	0x10
	.byte	0x7
	.byte	0x2f
	.byte	0x10
	.4byte	0x4d4
	.uleb128 0x6
	.4byte	.LASF141
	.byte	0x30
	.byte	0xd
	.4byte	0xe9
	.byte	0
	.uleb128 0x6
	.4byte	.LASF142
	.byte	0x31
	.byte	0xa
	.4byte	0xe9
	.byte	0x1
	.uleb128 0x6
	.4byte	.LASF143
	.byte	0x32
	.byte	0xd
	.4byte	0xe9
	.byte	0x2
	.uleb128 0x6
	.4byte	.LASF144
	.byte	0x33
	.byte	0xd
	.4byte	0xe9
	.byte	0x3
	.uleb128 0x6
	.4byte	.LASF145
	.byte	0x34
	.byte	0xd
	.4byte	0xe9
	.byte	0x4
	.uleb128 0x6
	.4byte	.LASF146
	.byte	0x35
	.byte	0xd
	.4byte	0xe9
	.byte	0x5
	.uleb128 0x6
	.4byte	.LASF147
	.byte	0x36
	.byte	0xd
	.4byte	0xe9
	.byte	0x6
	.uleb128 0x6
	.4byte	.LASF148
	.byte	0x37
	.byte	0x9
	.4byte	0x376
	.byte	0x7
	.uleb128 0x6
	.4byte	.LASF149
	.byte	0x38
	.byte	0x9
	.4byte	0x376
	.byte	0x8
	.uleb128 0x6
	.4byte	.LASF150
	.byte	0x39
	.byte	0xd
	.4byte	0x4d4
	.byte	0x9
	.uleb128 0x6
	.4byte	.LASF151
	.byte	0x3d
	.byte	0xe
	.4byte	0x101
	.byte	0xc
	.byte	0
	.uleb128 0xe
	.4byte	0xe9
	.4byte	0x4e4
	.uleb128 0xf
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0xc
	.4byte	.LASF152
	.byte	0x7
	.byte	0x41
	.byte	0x2
	.4byte	0x442
	.uleb128 0x9
	.4byte	0x101
	.uleb128 0x8
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x4b
	.byte	0xe
	.4byte	0x545
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF157
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF159
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF162
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF163
	.byte	0xa
	.byte	0
	.uleb128 0xb
	.byte	0x5
	.4byte	0x114
	.byte	0x9
	.2byte	0x120
	.4byte	0x571
	.uleb128 0x2
	.4byte	.LASF164
	.sleb128 -4
	.uleb128 0x2
	.4byte	.LASF165
	.sleb128 -3
	.uleb128 0x2
	.4byte	.LASF166
	.sleb128 -2
	.uleb128 0x2
	.4byte	.LASF167
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF168
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	.LASF169
	.byte	0x9
	.2byte	0x126
	.byte	0x3
	.4byte	0x545
	.uleb128 0x7
	.4byte	.LASF170
	.byte	0x9
	.2byte	0x137
	.byte	0x12
	.4byte	0x101
	.uleb128 0x23
	.byte	0x8
	.byte	0x9
	.2byte	0x13d
	.byte	0x5
	.4byte	0x5b0
	.uleb128 0x12
	.string	"ptr"
	.2byte	0x13e
	.byte	0xf
	.4byte	0x2c3
	.byte	0
	.uleb128 0x12
	.string	"len"
	.2byte	0x13f
	.byte	0x12
	.4byte	0x101
	.byte	0x4
	.byte	0
	.uleb128 0x24
	.byte	0x8
	.byte	0x9
	.2byte	0x13c
	.byte	0x9
	.4byte	0x5d3
	.uleb128 0x13
	.4byte	.LASF171
	.2byte	0x140
	.byte	0x7
	.4byte	0x58b
	.uleb128 0x13
	.4byte	.LASF172
	.2byte	0x141
	.byte	0xe
	.4byte	0x11b
	.byte	0
	.uleb128 0x7
	.4byte	.LASF173
	.byte	0x9
	.2byte	0x142
	.byte	0x3
	.4byte	0x5b0
	.uleb128 0x9
	.4byte	0x5d3
	.uleb128 0x8
	.byte	0x7
	.4byte	0x2d
	.byte	0xa
	.byte	0x35
	.byte	0xe
	.4byte	0x614
	.uleb128 0x1
	.4byte	.LASF174
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF175
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF176
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF177
	.byte	0x3
	.uleb128 0x25
	.4byte	.LASF178
	.4byte	0xffffffff
	.byte	0
	.uleb128 0x8
	.byte	0x7
	.4byte	0x2d
	.byte	0xa
	.byte	0x3d
	.byte	0xe
	.4byte	0x6e8
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0
	.uleb128 0x1
	.4byte	.LASF180
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF182
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF183
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF184
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF188
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF189
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF190
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF191
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF192
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF193
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF194
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF195
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF196
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF197
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF198
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF199
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF200
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF201
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF202
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF203
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF204
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF205
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF206
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF207
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF208
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF209
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF210
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF211
	.byte	0x20
	.byte	0
	.uleb128 0xe
	.4byte	0xf5
	.4byte	0x6f8
	.uleb128 0xf
	.4byte	0x2d
	.byte	0xf
	.byte	0
	.uleb128 0x11
	.4byte	0x6e8
	.uleb128 0x26
	.4byte	.LASF229
	.byte	0xd
	.byte	0x87
	.byte	0x19
	.4byte	0x6f8
	.uleb128 0x8
	.byte	0x7
	.4byte	0x2d
	.byte	0xb
	.byte	0x50
	.byte	0xe
	.4byte	0x74d
	.uleb128 0x1
	.4byte	.LASF212
	.byte	0
	.uleb128 0x1
	.4byte	.LASF213
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF214
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF215
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF216
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF217
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF218
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF219
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF220
	.byte	0x8
	.byte	0
	.uleb128 0x8
	.byte	0x7
	.4byte	0x2d
	.byte	0xc
	.byte	0x31
	.byte	0x1
	.4byte	0x78b
	.uleb128 0x1
	.4byte	.LASF221
	.byte	0
	.uleb128 0x1
	.4byte	.LASF222
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF223
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF224
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF225
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF226
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF227
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF228
	.byte	0x7
	.byte	0
	.uleb128 0x14
	.4byte	.LASF230
	.byte	0x2b
	.byte	0x9
	.4byte	0xe9
	.uleb128 0x5
	.byte	0x3
	.4byte	workround_flag
	.uleb128 0x14
	.4byte	.LASF231
	.byte	0x2c
	.byte	0xa
	.4byte	0x101
	.uleb128 0x5
	.byte	0x3
	.4byte	is_lifted
	.uleb128 0x27
	.4byte	.LASF253
	.byte	0x1
	.byte	0x2f
	.byte	0x2b
	.4byte	0xe9
	.byte	0x10
	.uleb128 0x5
	.byte	0x3
	.4byte	burst_reg
	.uleb128 0x28
	.4byte	.LASF252
	.byte	0x1
	.byte	0x30
	.byte	0x1d
	.4byte	0x7cc
	.uleb128 0x9
	.4byte	0x4e4
	.uleb128 0xd
	.4byte	.LASF232
	.byte	0x5
	.2byte	0x4bc
	.byte	0x19
	.4byte	0x3e8
	.4byte	0x7f2
	.uleb128 0x3
	.4byte	0x14b
	.uleb128 0x3
	.4byte	0x3f5
	.uleb128 0x3
	.4byte	0x2c3
	.byte	0
	.uleb128 0xd
	.4byte	.LASF233
	.byte	0x9
	.2byte	0x15f
	.byte	0x13
	.4byte	0x571
	.4byte	0x80e
	.uleb128 0x3
	.4byte	0x57e
	.uleb128 0x3
	.4byte	0x5e0
	.byte	0
	.uleb128 0x15
	.4byte	.LASF234
	.byte	0x3f
	.4byte	0x81e
	.uleb128 0x3
	.4byte	0x101
	.byte	0
	.uleb128 0x15
	.4byte	.LASF235
	.byte	0x3e
	.4byte	0x82e
	.uleb128 0x3
	.4byte	0x4f0
	.byte	0
	.uleb128 0xd
	.4byte	.LASF236
	.byte	0x5
	.2byte	0x466
	.byte	0x19
	.4byte	0x3e8
	.4byte	0x84a
	.uleb128 0x3
	.4byte	0x14b
	.uleb128 0x3
	.4byte	0x376
	.byte	0
	.uleb128 0xd
	.4byte	.LASF237
	.byte	0x5
	.2byte	0x408
	.byte	0x19
	.4byte	0x3e8
	.4byte	0x86b
	.uleb128 0x3
	.4byte	0x14b
	.uleb128 0x3
	.4byte	0x417
	.uleb128 0x3
	.4byte	0x417
	.byte	0
	.uleb128 0x29
	.4byte	.LASF254
	.byte	0x1
	.byte	0x80
	.byte	0x5
	.4byte	0x114
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x16
	.4byte	.LASF240
	.byte	0x7c
	.4byte	0x114
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x8e1
	.uleb128 0xa
	.4byte	.LASF238
	.byte	0x7c
	.byte	0x3e
	.4byte	0x3f5
	.4byte	.LLST6
	.uleb128 0xa
	.4byte	.LASF239
	.byte	0x7c
	.byte	0x4d
	.4byte	0x2c3
	.4byte	.LLST7
	.uleb128 0x17
	.4byte	.LVL23
	.4byte	0x7d1
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x5
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
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0
	.byte	0
	.uleb128 0x16
	.4byte	.LASF241
	.byte	0x61
	.4byte	0x114
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x951
	.uleb128 0xa
	.4byte	.LASF242
	.byte	0x61
	.byte	0x24
	.4byte	0x951
	.4byte	.LLST4
	.uleb128 0xa
	.4byte	.LASF243
	.byte	0x61
	.byte	0x34
	.4byte	0x951
	.4byte	.LLST5
	.uleb128 0x18
	.4byte	.LASF247
	.byte	0x62
	.4byte	0x101
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x10
	.4byte	.LVL13
	.4byte	0x81e
	.4byte	0x938
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL14
	.4byte	0x80e
	.uleb128 0x1a
	.4byte	.LVL15
	.4byte	0x956
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0xc8
	.uleb128 0x1b
	.4byte	.LASF244
	.byte	0x5c
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x992
	.uleb128 0x1c
	.string	"msg"
	.byte	0x5c
	.byte	0x3b
	.4byte	0x5e0
	.4byte	.LLST3
	.uleb128 0x17
	.4byte	.LVL10
	.4byte	0x7f2
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0xc
	.4byte	0x201000f
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF245
	.byte	0x55
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9ef
	.uleb128 0xa
	.4byte	.LASF246
	.byte	0x55
	.byte	0x31
	.4byte	0x57e
	.4byte	.LLST1
	.uleb128 0x1c
	.string	"msg"
	.byte	0x55
	.byte	0x4c
	.4byte	0x5e0
	.4byte	.LLST2
	.uleb128 0x18
	.4byte	.LASF247
	.byte	0x57
	.4byte	0x101
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x10
	.4byte	.LVL6
	.4byte	0x81e
	.4byte	0x9e5
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL7
	.4byte	0x80e
	.byte	0
	.uleb128 0x2a
	.4byte	.LASF248
	.byte	0x1
	.byte	0x31
	.byte	0x5
	.4byte	0x114
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xa
	.4byte	.LASF249
	.byte	0x31
	.byte	0x25
	.4byte	0xe9
	.4byte	.LLST0
	.uleb128 0x10
	.4byte	.LVL2
	.4byte	0x84a
	.4byte	0xa30
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	burst_reg
	.byte	0
	.uleb128 0x1a
	.4byte	.LVL3
	.4byte	0x82e
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
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
	.uleb128 0x14
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
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 13
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x17
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
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x88
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x2a
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
	.byte	0
	.section	.debug_loclists,"",@progbits
	.4byte	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.Ldebug_loc0:
.LLST6:
	.byte	0x6
	.4byte	.LVL20
	.byte	0x4
	.uleb128 .LVL20-.LVL20
	.uleb128 .LVL22-.LVL20
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL22-.LVL20
	.uleb128 .LVL23-1-.LVL20
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL23-1-.LVL20
	.uleb128 .LFE19-.LVL20
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
.LLST7:
	.byte	0x6
	.4byte	.LVL20
	.byte	0x4
	.uleb128 .LVL20-.LVL20
	.uleb128 .LVL21-.LVL20
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL21-.LVL20
	.uleb128 .LVL23-1-.LVL20
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL23-1-.LVL20
	.uleb128 .LFE19-.LVL20
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
.LLST4:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL12-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL12-.LVL11
	.uleb128 .LVL16-.LVL11
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
	.uleb128 .LVL16-.LVL11
	.uleb128 .LVL17-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL17-.LVL11
	.uleb128 .LVL18-.LVL11
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
	.uleb128 .LVL18-.LVL11
	.uleb128 .LVL19-.LVL11
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL19-.LVL11
	.uleb128 .LFE18-.LVL11
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
.LLST5:
	.byte	0x6
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL13-1-.LVL11
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL13-1-.LVL11
	.uleb128 .LVL16-.LVL11
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
	.uleb128 .LVL16-.LVL11
	.uleb128 .LFE18-.LVL11
	.uleb128 0x1
	.byte	0x5b
	.byte	0
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
	.uleb128 .LFE17-.LVL8
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
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL5-.LVL4
	.uleb128 .LFE16-.LVL4
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
	.uleb128 .LVL6-1-.LVL4
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL6-1-.LVL4
	.uleb128 .LFE16-.LVL4
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
	.uleb128 .LFE15-.LVL0
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
	.4byte	0x44
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
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
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
	.byte	0x7
	.4byte	.LFB19
	.uleb128 .LFE19-.LFB19
	.byte	0x7
	.4byte	.LFB20
	.uleb128 .LFE20-.LFB20
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF26:
	.string	"long int"
.LASF128:
	.string	"HAL_SPI_STATUS_ERROR_USED_BY_NORMAL_USER"
.LASF125:
	.string	"HAL_SPI_MASTER_NO_BUSY_FUNCTION_ERROR"
.LASF102:
	.string	"SLEEP_LOCK_IRRX"
.LASF243:
	.string	"data_y"
.LASF134:
	.string	"HAL_SPI_MASTER_STATUS_OK"
.LASF14:
	.string	"PMU_IRQn"
.LASF254:
	.string	"mouse_sensor_is_lifted"
.LASF58:
	.string	"HAL_EINT_NUMBER_21"
.LASF59:
	.string	"HAL_EINT_NUMBER_22"
.LASF60:
	.string	"HAL_EINT_NUMBER_23"
.LASF61:
	.string	"HAL_EINT_NUMBER_24"
.LASF62:
	.string	"HAL_EINT_NUMBER_25"
.LASF15:
	.string	"MCU_DMA_IRQn"
.LASF64:
	.string	"HAL_EINT_NUMBER_27"
.LASF65:
	.string	"HAL_EINT_NUMBER_28"
.LASF66:
	.string	"HAL_EINT_NUMBER_29"
.LASF87:
	.string	"HAL_EINT_UART_2_RX"
.LASF119:
	.string	"SLEEP_LOCK_APP"
.LASF240:
	.string	"mouse_sensor_register_callback"
.LASF213:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF88:
	.string	"HAL_EINT_USB0"
.LASF144:
	.string	"x_low"
.LASF90:
	.string	"HAL_EINT_USB2"
.LASF174:
	.string	"HAL_CCNI_CORE_START"
.LASF3:
	.string	"unsigned int"
.LASF227:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF99:
	.string	"SLEEP_LOCK_TRNG"
.LASF67:
	.string	"HAL_EINT_NUMBER_30"
.LASF68:
	.string	"HAL_EINT_NUMBER_31"
.LASF221:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF70:
	.string	"HAL_EINT_NUMBER_33"
.LASF71:
	.string	"HAL_EINT_NUMBER_34"
.LASF72:
	.string	"HAL_EINT_NUMBER_35"
.LASF73:
	.string	"HAL_EINT_NUMBER_36"
.LASF109:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF253:
	.string	"burst_reg"
.LASF76:
	.string	"HAL_EINT_NUMBER_39"
.LASF250:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF233:
	.string	"hal_ccni_set_event"
.LASF10:
	.string	"SPI_MST1_IRQn"
.LASF25:
	.string	"short int"
.LASF217:
	.string	"DBG_PIN_USB_SOF"
.LASF22:
	.string	"BT_IRQn"
.LASF147:
	.string	"y_high"
.LASF101:
	.string	"SLEEP_LOCK_IRTX"
.LASF97:
	.string	"SLEEP_LOCK_AESOTF"
.LASF228:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF167:
	.string	"HAL_CCNI_STATUS_NO_INIT"
.LASF23:
	.string	"IRQ_NUMBER_MAX"
.LASF36:
	.string	"hal_spi_master_port_t"
.LASF78:
	.string	"HAL_EINT_NUMBER_41"
.LASF114:
	.string	"SLEEP_LOCK_USB"
.LASF80:
	.string	"HAL_EINT_NUMBER_43"
.LASF81:
	.string	"HAL_EINT_NUMBER_44"
.LASF82:
	.string	"HAL_EINT_NUMBER_45"
.LASF83:
	.string	"HAL_EINT_NUMBER_46"
.LASF84:
	.string	"HAL_EINT_NUMBER_47"
.LASF150:
	.string	"reserved2"
.LASF118:
	.string	"SLEEP_LOCK_I2C0"
.LASF225:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF130:
	.string	"HAL_SPI_MASTER_STATUS_ERROR"
.LASF168:
	.string	"HAL_CCNI_STATUS_OK"
.LASF31:
	.string	"uint32_t"
.LASF171:
	.string	"variable_len_msg"
.LASF246:
	.string	"event"
.LASF13:
	.string	"UART_DMA_IRQn"
.LASF28:
	.string	"int16_t"
.LASF91:
	.string	"HAL_EINT_LPCOMP"
.LASF248:
	.string	"mouse_sensor_burst_read"
.LASF2:
	.string	"long long unsigned int"
.LASF223:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF115:
	.string	"SLEEP_LOCK_UART0"
.LASF116:
	.string	"SLEEP_LOCK_UART1"
.LASF117:
	.string	"SLEEP_LOCK_UART2"
.LASF231:
	.string	"is_lifted"
.LASF79:
	.string	"HAL_EINT_NUMBER_42"
.LASF8:
	.string	"KEYSCAN_IRQn"
.LASF37:
	.string	"HAL_EINT_NUMBER_0"
.LASF38:
	.string	"HAL_EINT_NUMBER_1"
.LASF39:
	.string	"HAL_EINT_NUMBER_2"
.LASF40:
	.string	"HAL_EINT_NUMBER_3"
.LASF41:
	.string	"HAL_EINT_NUMBER_4"
.LASF42:
	.string	"HAL_EINT_NUMBER_5"
.LASF43:
	.string	"HAL_EINT_NUMBER_6"
.LASF44:
	.string	"HAL_EINT_NUMBER_7"
.LASF45:
	.string	"HAL_EINT_NUMBER_8"
.LASF46:
	.string	"HAL_EINT_NUMBER_9"
.LASF241:
	.string	"mouse_sensor_get_data"
.LASF34:
	.string	"HAL_SPI_MASTER_1"
.LASF219:
	.string	"DBG_PIN_USB_TX"
.LASF6:
	.string	"LED_IRQn"
.LASF252:
	.string	"mouse_burst_data"
.LASF235:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF121:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF122:
	.string	"_Bool"
.LASF132:
	.string	"HAL_SPI_MASTER_STATUS_ERROR_PORT"
.LASF111:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF142:
	.string	"Motion_data"
.LASF135:
	.string	"hal_spi_master_status_t"
.LASF93:
	.string	"HAL_EINT_NUMBER_MAX"
.LASF152:
	.string	"mouse_burst_data_t"
.LASF154:
	.string	"EINT_COUNTER_NUMBER_1"
.LASF127:
	.string	"HAL_SPI_STATUS_FULL_BY_NON_BLOCKING_FUNCTION"
.LASF176:
	.string	"HAL_CCNI_CORE_RISCV"
.LASF218:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF212:
	.string	"DBG_PIN_SPI_CB"
.LASF151:
	.string	"data_ready_handler"
.LASF175:
	.string	"HAL_CCNI_CORE_MCU"
.LASF95:
	.string	"char"
.LASF164:
	.string	"HAL_CCNI_STATUS_INVALID_PARAMETER"
.LASF35:
	.string	"HAL_SPI_MASTER_MAX"
.LASF126:
	.string	"hal_spi_master_callback_event_t"
.LASF5:
	.string	"SW_IRQn"
.LASF172:
	.string	"data"
.LASF166:
	.string	"HAL_CCNI_STATUS_ERROR"
.LASF120:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF29:
	.string	"uint8_t"
.LASF63:
	.string	"HAL_EINT_NUMBER_26"
.LASF86:
	.string	"HAL_EINT_UART_1_RX"
.LASF98:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF226:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF19:
	.string	"SPI_MST0_IRQn"
.LASF239:
	.string	"user_data"
.LASF27:
	.string	"long long int"
.LASF145:
	.string	"x_high"
.LASF18:
	.string	"I3C0_DMA_IRQn"
.LASF113:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF224:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF129:
	.string	"HAL_SPI_STATUS_BUSY_BY_NON_BLOCKING_FUNCTION"
.LASF133:
	.string	"HAL_SPI_MASTER_STATUS_INVALID_PARAMETER"
.LASF20:
	.string	"IRQ_GEN_IRQn"
.LASF9:
	.string	"UART_IRQn"
.LASF215:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF216:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF110:
	.string	"SLEEP_LOCK_DCXO"
.LASF242:
	.string	"data_x"
.LASF247:
	.string	"mask"
.LASF220:
	.string	"DBG_PIN_MAX"
.LASF69:
	.string	"HAL_EINT_NUMBER_32"
.LASF21:
	.string	"USB_IRQn"
.LASF165:
	.string	"HAL_CCNI_STATUS_BUSY"
.LASF74:
	.string	"HAL_EINT_NUMBER_37"
.LASF75:
	.string	"HAL_EINT_NUMBER_38"
.LASF189:
	.string	"HAL_CCNI_EVENT10"
.LASF190:
	.string	"HAL_CCNI_EVENT11"
.LASF191:
	.string	"HAL_CCNI_EVENT12"
.LASF192:
	.string	"HAL_CCNI_EVENT13"
.LASF193:
	.string	"HAL_CCNI_EVENT14"
.LASF194:
	.string	"HAL_CCNI_EVENT15"
.LASF195:
	.string	"HAL_CCNI_EVENT16"
.LASF196:
	.string	"HAL_CCNI_EVENT17"
.LASF197:
	.string	"HAL_CCNI_EVENT18"
.LASF198:
	.string	"HAL_CCNI_EVENT19"
.LASF94:
	.string	"long double"
.LASF251:
	.string	"IRQn"
.LASF96:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF89:
	.string	"HAL_EINT_USB1"
.LASF136:
	.string	"hal_spi_master_callback_t"
.LASF11:
	.string	"RTC_IRQn"
.LASF179:
	.string	"HAL_CCNI_EVENT0"
.LASF180:
	.string	"HAL_CCNI_EVENT1"
.LASF181:
	.string	"HAL_CCNI_EVENT2"
.LASF182:
	.string	"HAL_CCNI_EVENT3"
.LASF183:
	.string	"HAL_CCNI_EVENT4"
.LASF184:
	.string	"HAL_CCNI_EVENT5"
.LASF185:
	.string	"HAL_CCNI_EVENT6"
.LASF186:
	.string	"HAL_CCNI_EVENT7"
.LASF187:
	.string	"HAL_CCNI_EVENT8"
.LASF188:
	.string	"HAL_CCNI_EVENT9"
.LASF199:
	.string	"HAL_CCNI_EVENT20"
.LASF200:
	.string	"HAL_CCNI_EVENT21"
.LASF201:
	.string	"HAL_CCNI_EVENT22"
.LASF202:
	.string	"HAL_CCNI_EVENT23"
.LASF203:
	.string	"HAL_CCNI_EVENT24"
.LASF204:
	.string	"HAL_CCNI_EVENT25"
.LASF205:
	.string	"HAL_CCNI_EVENT26"
.LASF206:
	.string	"HAL_CCNI_EVENT27"
.LASF207:
	.string	"HAL_CCNI_EVENT28"
.LASF208:
	.string	"HAL_CCNI_EVENT29"
.LASF112:
	.string	"SLEEP_LOCK_I3C1"
.LASF222:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF16:
	.string	"EINT_IRQn"
.LASF77:
	.string	"HAL_EINT_NUMBER_40"
.LASF12:
	.string	"GPT_IRQn"
.LASF140:
	.string	"MOUSE_SENSOR_STATUS_OK"
.LASF33:
	.string	"HAL_SPI_MASTER_0"
.LASF237:
	.string	"hal_spi_master_restore_address_advanced"
.LASF146:
	.string	"y_low"
.LASF131:
	.string	"HAL_SPI_MASTER_STATUS_ERROR_BUSY"
.LASF173:
	.string	"hal_ccni_message_t"
.LASF234:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF123:
	.string	"HAL_SPI_MASTER_EVENT_SEND_FINISHED"
.LASF139:
	.string	"MOUSE_SENSOR_STATUS_NOT_INIT"
.LASF92:
	.string	"HAL_EINT_RESERVED"
.LASF209:
	.string	"HAL_CCNI_EVENT30"
.LASF210:
	.string	"HAL_CCNI_EVENT31"
.LASF104:
	.string	"SLEEP_LOCK_FLASH"
.LASF169:
	.string	"hal_ccni_status_t"
.LASF170:
	.string	"hal_ccni_event_t"
.LASF244:
	.string	"mouse_sensor_send_report_to_CM33"
.LASF211:
	.string	"HAL_CCNI_EVENT_MAX"
.LASF249:
	.string	"burst_size"
.LASF230:
	.string	"workround_flag"
.LASF32:
	.string	"long unsigned int"
.LASF105:
	.string	"SLEEP_LOCK_ESC"
.LASF4:
	.string	"unsigned char"
.LASF148:
	.string	"burst_flag"
.LASF100:
	.string	"SLEEP_LOCK_DMA"
.LASF138:
	.string	"MOUSE_SENSOR_STATUS_READ_DATA_FAILED"
.LASF163:
	.string	"EINT_COUNTER_NUMBER_MUX"
.LASF57:
	.string	"HAL_EINT_NUMBER_20"
.LASF143:
	.string	"observation_data"
.LASF149:
	.string	"init_flag"
.LASF238:
	.string	"callback"
.LASF124:
	.string	"HAL_SPI_MASTER_EVENT_RECEIVE_FINISHED"
.LASF17:
	.string	"I3C0_IRQn"
.LASF85:
	.string	"HAL_EINT_UART_0_RX"
.LASF106:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF107:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF108:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF24:
	.string	"signed char"
.LASF232:
	.string	"hal_spi_master_register_callback"
.LASF30:
	.string	"short unsigned int"
.LASF153:
	.string	"EINT_COUNTER_NUMBER_0"
.LASF214:
	.string	"DBG_PIN_NACK"
.LASF155:
	.string	"EINT_COUNTER_NUMBER_2"
.LASF156:
	.string	"EINT_COUNTER_NUMBER_3"
.LASF157:
	.string	"EINT_COUNTER_NUMBER_4"
.LASF158:
	.string	"EINT_COUNTER_NUMBER_5"
.LASF159:
	.string	"EINT_COUNTER_NUMBER_6"
.LASF160:
	.string	"EINT_COUNTER_NUMBER_7"
.LASF161:
	.string	"EINT_COUNTER_NUMBER_8"
.LASF162:
	.string	"EINT_COUNTER_NUMBER_9"
.LASF141:
	.string	"reserved"
.LASF177:
	.string	"HAL_CCNI_CORE_END"
.LASF103:
	.string	"SLEEP_LOCK_AIO"
.LASF47:
	.string	"HAL_EINT_NUMBER_10"
.LASF48:
	.string	"HAL_EINT_NUMBER_11"
.LASF49:
	.string	"HAL_EINT_NUMBER_12"
.LASF50:
	.string	"HAL_EINT_NUMBER_13"
.LASF51:
	.string	"HAL_EINT_NUMBER_14"
.LASF52:
	.string	"HAL_EINT_NUMBER_15"
.LASF53:
	.string	"HAL_EINT_NUMBER_16"
.LASF54:
	.string	"HAL_EINT_NUMBER_17"
.LASF55:
	.string	"HAL_EINT_NUMBER_18"
.LASF56:
	.string	"HAL_EINT_NUMBER_19"
.LASF178:
	.string	"HAL_CCNI_CORE_RESERVED"
.LASF7:
	.string	"QDEC_IRQn"
.LASF137:
	.string	"MOUSE_SENSOR_STATUS_NOT_SET_BURST"
.LASF229:
	.string	"ccm_spi_sensor"
.LASF245:
	.string	"hal_ccni_event_callback20"
.LASF236:
	.string	"hal_spi_master_trigger_start"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/mouse_sensor.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
