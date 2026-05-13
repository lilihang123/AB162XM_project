	.file	"riscv_main.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_main.c"
	.section	.text.startup.main,"ax",@progbits
	.align	1
	.globl	main
	.hidden	main
	.type	main, @function
main:
.LFB15:
	.file 1 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_main.c"
	.loc 1 88 1
	.cfi_startproc
.LVL0:
	.loc 1 89 5
	.loc 1 88 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 89 5
	call	system_init
.LVL1:
	.loc 1 90 5 is_stmt 1
.LBB2:
	.loc 1 90 10
	.loc 1 90 65
	.loc 1 90 230
	li	a3,0
	lla	a2,msg_id_string.0
	li	a1,1
	lla	a0,log_control_block_riscv_ps
	call	print_module_msgid_log
.LVL2:
.LBE2:
	.loc 1 90 8 discriminator 1
	.loc 1 93 5
	call	peripheral_sampling_init
.LVL3:
	.loc 1 94 5
	call	riscv_app_ccin_init
.LVL4:
	.loc 1 102 5
	.loc 1 103 5
	li	a0,1
	call	rv_sleep_lock_request
.LVL5:
.LBB3:
	.loc 1 114 24 is_stmt 0
	lla	s0,hid_flags
.L3:
.LBE3:
	.loc 1 105 5 is_stmt 1
.LBB4:
	.loc 1 107 9
	.loc 1 110 9
	call	key_remap_backend_postprocess
.LVL6:
	.loc 1 114 9
	.loc 1 114 24 is_stmt 0
	lw	a5,0(s0)
	andi	a5,a5,32
	.loc 1 114 11
	bne	a5,zero,.L2
	.loc 1 115 13 is_stmt 1
	call	riscv_mouse_key_pairing_key_check
.LVL7:
.L2:
	.loc 1 120 9
	call	peripheral_sampling_debug_print
.LVL8:
	.loc 1 121 9
	call	hid_express_debug_print
.LVL9:
	.loc 1 126 9
	mv	a0,sp
	call	hal_nvic_save_and_set_interrupt_mask
.LVL10:
	.loc 1 127 9
	.loc 1 128 9
	call	hal_sleep_manager_riscv_sleep_routine
.LVL11:
	.loc 1 129 9
	.loc 1 130 9
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL12:
.LBE4:
	.loc 1 105 11
	.loc 1 106 5 is_stmt 0
	j	.L3
	.cfi_endproc
.LFE15:
	.size	main, .-main
	.section	.log_string,"a"
	.align	2
	.type	msg_id_string.0, @object
	.size	msg_id_string.0, 72
msg_id_string.0:
	.string	"[M:riscv_ps C:info F: L: ]: ================ iBEX Main =============== "
	.hidden	ccni_test
	.globl	ccni_test
	.section	.sbss.ccni_test,"aw",@nobits
	.align	2
	.type	ccni_test, @object
	.size	ccni_test, 8
ccni_test:
	.zero	8
	.hidden	timeout_counter
	.globl	timeout_counter
	.section	.sbss.timeout_counter,"aw",@nobits
	.align	2
	.type	timeout_counter, @object
	.size	timeout_counter, 4
timeout_counter:
	.zero	4
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 4 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 7 "/workdir/airoha/common/middleware/airoha/pka_share/inc/pka_share.h"
	.file 8 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 9 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 10 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_peripheral_sampling.h"
	.file 11 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_mouse_key.h"
	.file 12 "/workdir/airoha/common/middleware/airoha/key_remap/inc/key_remap_backend.h"
	.file 13 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/inc/app/riscv_ccni.h"
	.file 14 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager.h"
	.file 15 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/../general_used/inc/sys_init.h"
	.file 16 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x68e
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x17
	.4byte	.LASF134
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
	.uleb128 0x18
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x19
	.byte	0x4
	.uleb128 0x4
	.4byte	0x7a
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xe
	.4byte	0x7a
	.uleb128 0x4
	.4byte	0x81
	.uleb128 0x7
	.4byte	.LASF17
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x3
	.byte	0x3d
	.byte	0xe
	.4byte	0xbc
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x3
	.byte	0
	.uleb128 0x7
	.4byte	.LASF18
	.byte	0x3
	.byte	0x42
	.byte	0x3
	.4byte	0x97
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x3
	.byte	0x45
	.byte	0xe
	.4byte	0x12f
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x3f
	.byte	0
	.uleb128 0x7
	.4byte	.LASF34
	.byte	0x3
	.byte	0x57
	.byte	0x3
	.4byte	0xc8
	.uleb128 0x7
	.4byte	.LASF35
	.byte	0x3
	.byte	0x59
	.byte	0x10
	.4byte	0x147
	.uleb128 0x4
	.4byte	0x14c
	.uleb128 0xd
	.4byte	0x16c
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x86
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xbc
	.uleb128 0x2
	.4byte	0x86
	.uleb128 0x5
	.byte	0
	.uleb128 0x7
	.4byte	.LASF36
	.byte	0x3
	.byte	0x5a
	.byte	0x10
	.4byte	0x178
	.uleb128 0x4
	.4byte	0x17d
	.uleb128 0xd
	.4byte	0x1a7
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0x86
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0xbc
	.uleb128 0x2
	.4byte	0x1a7
	.uleb128 0x2
	.4byte	0x65
	.uleb128 0x2
	.4byte	0x86
	.uleb128 0x5
	.byte	0
	.uleb128 0x4
	.4byte	0x1ac
	.uleb128 0x1a
	.uleb128 0x7
	.4byte	.LASF37
	.byte	0x3
	.byte	0x5b
	.byte	0x10
	.4byte	0x1b9
	.uleb128 0x4
	.4byte	0x1be
	.uleb128 0xd
	.4byte	0x1d9
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xbc
	.uleb128 0x2
	.4byte	0x86
	.uleb128 0x2
	.4byte	0x8b
	.uleb128 0x5
	.byte	0
	.uleb128 0x7
	.4byte	.LASF38
	.byte	0x3
	.byte	0x5c
	.byte	0x14
	.4byte	0x1e5
	.uleb128 0x4
	.4byte	0x1ea
	.uleb128 0x1b
	.4byte	0x8b
	.4byte	0x20d
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xbc
	.uleb128 0x2
	.4byte	0x12f
	.uleb128 0x2
	.4byte	0x20d
	.uleb128 0x2
	.4byte	0x212
	.byte	0
	.uleb128 0x4
	.4byte	0x1a7
	.uleb128 0x4
	.4byte	0x8b
	.uleb128 0x1c
	.byte	0x1c
	.byte	0x3
	.byte	0x5e
	.byte	0x9
	.4byte	0x275
	.uleb128 0x8
	.4byte	.LASF39
	.byte	0x5f
	.byte	0x11
	.4byte	0x86
	.byte	0
	.uleb128 0x8
	.4byte	.LASF40
	.byte	0x60
	.byte	0xe
	.4byte	0x8b
	.byte	0x4
	.uleb128 0x8
	.4byte	.LASF41
	.byte	0x61
	.byte	0xe
	.4byte	0x8b
	.byte	0x8
	.uleb128 0x8
	.4byte	.LASF42
	.byte	0x62
	.byte	0xf
	.4byte	0x13b
	.byte	0xc
	.uleb128 0x8
	.4byte	.LASF43
	.byte	0x63
	.byte	0x15
	.4byte	0x16c
	.byte	0x10
	.uleb128 0x8
	.4byte	.LASF44
	.byte	0x64
	.byte	0x12
	.4byte	0x1d9
	.byte	0x14
	.uleb128 0x8
	.4byte	.LASF45
	.byte	0x65
	.byte	0x10
	.4byte	0x1ad
	.byte	0x18
	.byte	0
	.uleb128 0x7
	.4byte	.LASF46
	.byte	0x3
	.byte	0x66
	.byte	0x3
	.4byte	0x217
	.uleb128 0x1d
	.4byte	.LASF135
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x10
	.2byte	0x128
	.byte	0x12
	.4byte	0x307
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0xb
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
	.byte	0
	.uleb128 0xf
	.4byte	0x8b
	.4byte	0x317
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x4
	.byte	0x50
	.byte	0xe
	.4byte	0x35a
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x8
	.byte	0
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF75
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x5
	.byte	0x31
	.byte	0x1
	.4byte	0x39e
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x7
	.byte	0
	.uleb128 0x11
	.4byte	.LASF114
	.byte	0x8
	.byte	0xda
	.byte	0x11
	.4byte	0x8b
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x6
	.byte	0x2a
	.byte	0xe
	.4byte	0x453
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0xff
	.byte	0
	.uleb128 0x9
	.4byte	0x2d
	.byte	0x7
	.byte	0x6e
	.byte	0xe
	.4byte	0x478
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x3
	.byte	0
	.uleb128 0x12
	.4byte	.LASF115
	.byte	0x4c
	.byte	0x5
	.4byte	0x65
	.uleb128 0x5
	.byte	0x3
	.4byte	timeout_counter
	.uleb128 0x12
	.4byte	.LASF116
	.byte	0x54
	.byte	0xa
	.4byte	0x307
	.uleb128 0x5
	.byte	0x3
	.4byte	ccni_test
	.uleb128 0xb
	.4byte	.LASF117
	.byte	0x9
	.byte	0x3f
	.byte	0xd
	.4byte	0x4ac
	.uleb128 0x2
	.4byte	0x8b
	.byte	0
	.uleb128 0x13
	.4byte	.LASF127
	.byte	0xe
	.byte	0x3b
	.byte	0x6
	.uleb128 0xb
	.4byte	.LASF118
	.byte	0x9
	.byte	0x3e
	.byte	0xd
	.4byte	0x4c6
	.uleb128 0x2
	.4byte	0x212
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF119
	.byte	0x8
	.2byte	0x109
	.byte	0x6
	.4byte	0x4d5
	.uleb128 0x5
	.byte	0
	.uleb128 0xc
	.4byte	.LASF120
	.byte	0xa
	.byte	0x6c
	.4byte	0x4e2
	.uleb128 0x5
	.byte	0
	.uleb128 0xc
	.4byte	.LASF121
	.byte	0xb
	.byte	0x33
	.4byte	0x4ef
	.uleb128 0x5
	.byte	0
	.uleb128 0xc
	.4byte	.LASF122
	.byte	0xc
	.byte	0x4b
	.4byte	0x4fc
	.uleb128 0x5
	.byte	0
	.uleb128 0xb
	.4byte	.LASF123
	.byte	0x1
	.byte	0x66
	.byte	0x11
	.4byte	0x50e
	.uleb128 0x2
	.4byte	0x8b
	.byte	0
	.uleb128 0xc
	.4byte	.LASF124
	.byte	0xd
	.byte	0x31
	.4byte	0x51b
	.uleb128 0x5
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF125
	.byte	0xa
	.byte	0x66
	.byte	0x5
	.4byte	0x65
	.4byte	0x52d
	.uleb128 0x5
	.byte	0
	.uleb128 0x20
	.4byte	.LASF126
	.byte	0x3
	.2byte	0x129
	.byte	0xd
	.4byte	0x550
	.uleb128 0x2
	.4byte	0x73
	.uleb128 0x2
	.4byte	0xbc
	.uleb128 0x2
	.4byte	0x86
	.uleb128 0x2
	.4byte	0x8b
	.uleb128 0x5
	.byte	0
	.uleb128 0x13
	.4byte	.LASF128
	.byte	0xf
	.byte	0x2e
	.byte	0xd
	.uleb128 0x21
	.4byte	.LASF136
	.byte	0x1
	.byte	0x57
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x677
	.uleb128 0x14
	.4byte	.LASF129
	.byte	0x57
	.byte	0xe
	.4byte	0x65
	.4byte	.LLST0
	.uleb128 0x14
	.4byte	.LASF130
	.byte	0x57
	.byte	0x1b
	.4byte	0x677
	.4byte	.LLST1
	.uleb128 0xb
	.4byte	.LASF123
	.byte	0x1
	.byte	0x66
	.byte	0x11
	.4byte	0x5a2
	.uleb128 0x2
	.4byte	0x8b
	.byte	0
	.uleb128 0x22
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.4byte	0x5ea
	.uleb128 0x11
	.4byte	.LASF131
	.byte	0x1
	.byte	0x5a
	.byte	0x25
	.4byte	0x275
	.uleb128 0x15
	.4byte	.LASF132
	.byte	0x5a
	.byte	0x80
	.4byte	0x68c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0x16
	.4byte	.LVL2
	.4byte	0x52d
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	.LLRL2
	.4byte	0x64c
	.uleb128 0x15
	.4byte	.LASF133
	.byte	0x6b
	.byte	0x12
	.4byte	0x8b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x6
	.4byte	.LVL6
	.4byte	0x4ef
	.uleb128 0x6
	.4byte	.LVL7
	.4byte	0x4e2
	.uleb128 0x6
	.4byte	.LVL8
	.4byte	0x4d5
	.uleb128 0x6
	.4byte	.LVL9
	.4byte	0x4c6
	.uleb128 0x24
	.4byte	.LVL10
	.4byte	0x4b4
	.4byte	0x639
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x6
	.4byte	.LVL11
	.4byte	0x4ac
	.uleb128 0x6
	.4byte	.LVL12
	.4byte	0x49a
	.byte	0
	.uleb128 0x6
	.4byte	.LVL1
	.4byte	0x550
	.uleb128 0x6
	.4byte	.LVL3
	.4byte	0x51b
	.uleb128 0x6
	.4byte	.LVL4
	.4byte	0x50e
	.uleb128 0x16
	.4byte	.LVL5
	.4byte	0x4fc
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	0x75
	.uleb128 0xf
	.4byte	0x81
	.4byte	0x68c
	.uleb128 0x10
	.4byte	0x2d
	.byte	0x47
	.byte	0
	.uleb128 0xe
	.4byte	0x67c
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
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
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x21
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
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 .LVL1-1-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL1-1-.LVL0
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
	.uleb128 .LVL1-1-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL1-1-.LVL0
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
.LLRL2:
	.byte	0x5
	.4byte	.LBB3
	.byte	0x4
	.uleb128 .LBB3-.LBB3
	.uleb128 .LBE3-.LBB3
	.byte	0x4
	.uleb128 .LBB4-.LBB3
	.uleb128 .LBE4-.LBB3
	.byte	0
.LLRL3:
	.byte	0x7
	.4byte	.LFB15
	.uleb128 .LFE15-.LFB15
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF84:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF117:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF25:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF134:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF87:
	.string	"SLEEP_LOCK_TRNG"
.LASF27:
	.string	"LOG_TYPE_HCI_DATA"
.LASF44:
	.string	"tlv_dump_handle"
.LASF83:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF120:
	.string	"peripheral_sampling_debug_print"
.LASF49:
	.string	"QDEC_IRQn"
.LASF128:
	.string	"system_init"
.LASF89:
	.string	"SLEEP_LOCK_IRTX"
.LASF19:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF131:
	.string	"log_control_block_riscv_ps"
.LASF109:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF86:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF24:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF10:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF127:
	.string	"hal_sleep_manager_riscv_sleep_routine"
.LASF111:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RT"
.LASF2:
	.string	"long long unsigned int"
.LASF55:
	.string	"UART_DMA_IRQn"
.LASF51:
	.string	"UART_IRQn"
.LASF77:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF41:
	.string	"print_level"
.LASF53:
	.string	"RTC_IRQn"
.LASF50:
	.string	"KEYSCAN_IRQn"
.LASF8:
	.string	"long int"
.LASF35:
	.string	"f_print_t"
.LASF124:
	.string	"riscv_app_ccin_init"
.LASF92:
	.string	"SLEEP_LOCK_FLASH"
.LASF26:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF85:
	.string	"SLEEP_LOCK_AESOTF"
.LASF36:
	.string	"f_dump_buffer_t"
.LASF126:
	.string	"print_module_msgid_log"
.LASF82:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF122:
	.string	"key_remap_backend_postprocess"
.LASF30:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF59:
	.string	"I3C0_IRQn"
.LASF113:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_MAX"
.LASF58:
	.string	"EINT_IRQn"
.LASF60:
	.string	"I3C0_DMA_IRQn"
.LASF76:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF3:
	.string	"unsigned int"
.LASF115:
	.string	"timeout_counter"
.LASF40:
	.string	"log_switch"
.LASF23:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF29:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF9:
	.string	"long unsigned int"
.LASF42:
	.string	"print_handle"
.LASF7:
	.string	"short unsigned int"
.LASF16:
	.string	"PRINT_LEVEL_ERROR"
.LASF110:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_LE"
.LASF100:
	.string	"SLEEP_LOCK_I3C1"
.LASF28:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF63:
	.string	"USB_IRQn"
.LASF119:
	.string	"hid_express_debug_print"
.LASF15:
	.string	"PRINT_LEVEL_WARNING"
.LASF61:
	.string	"SPI_MST0_IRQn"
.LASF34:
	.string	"log_type_t"
.LASF68:
	.string	"DBG_PIN_NACK"
.LASF99:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF125:
	.string	"peripheral_sampling_init"
.LASF80:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF135:
	.string	"IRQn"
.LASF62:
	.string	"IRQ_GEN_IRQn"
.LASF54:
	.string	"GPT_IRQn"
.LASF73:
	.string	"DBG_PIN_USB_TX"
.LASF47:
	.string	"SW_IRQn"
.LASF93:
	.string	"SLEEP_LOCK_ESC"
.LASF31:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF52:
	.string	"SPI_MST1_IRQn"
.LASF20:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF106:
	.string	"SLEEP_LOCK_I2C0"
.LASF118:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF132:
	.string	"msg_id_string"
.LASF101:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF14:
	.string	"PRINT_LEVEL_INFO"
.LASF46:
	.string	"log_control_block_t"
.LASF108:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF75:
	.string	"_Bool"
.LASF5:
	.string	"unsigned char"
.LASF102:
	.string	"SLEEP_LOCK_USB"
.LASF18:
	.string	"print_level_t"
.LASF6:
	.string	"short int"
.LASF56:
	.string	"PMU_IRQn"
.LASF97:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF57:
	.string	"MCU_DMA_IRQn"
.LASF32:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF78:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF33:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF17:
	.string	"uint32_t"
.LASF67:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF43:
	.string	"dump_handle"
.LASF11:
	.string	"long double"
.LASF12:
	.string	"char"
.LASF70:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF45:
	.string	"msg_id_handle"
.LASF123:
	.string	"rv_sleep_lock_request"
.LASF129:
	.string	"argc"
.LASF39:
	.string	"module_name"
.LASF64:
	.string	"BT_IRQn"
.LASF94:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF95:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF96:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF90:
	.string	"SLEEP_LOCK_IRRX"
.LASF79:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF13:
	.string	"PRINT_LEVEL_DEBUG"
.LASF103:
	.string	"SLEEP_LOCK_UART0"
.LASF104:
	.string	"SLEEP_LOCK_UART1"
.LASF105:
	.string	"SLEEP_LOCK_UART2"
.LASF130:
	.string	"argv"
.LASF38:
	.string	"f_tlv_dump_t"
.LASF48:
	.string	"LED_IRQn"
.LASF98:
	.string	"SLEEP_LOCK_DCXO"
.LASF112:
	.string	"PKA_SHARE_TX_PREPARE_CB_TYPE_RTT"
.LASF133:
	.string	"irq_mask"
.LASF107:
	.string	"SLEEP_LOCK_APP"
.LASF69:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF116:
	.string	"ccni_test"
.LASF121:
	.string	"riscv_mouse_key_pairing_key_check"
.LASF74:
	.string	"DBG_PIN_MAX"
.LASF21:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF37:
	.string	"f_msg_id_t"
.LASF88:
	.string	"SLEEP_LOCK_DMA"
.LASF72:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF81:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF22:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF66:
	.string	"DBG_PIN_SPI_CB"
.LASF71:
	.string	"DBG_PIN_USB_SOF"
.LASF136:
	.string	"main"
.LASF91:
	.string	"SLEEP_LOCK_AIO"
.LASF114:
	.string	"hid_flags"
.LASF65:
	.string	"IRQ_NUMBER_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_main.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
