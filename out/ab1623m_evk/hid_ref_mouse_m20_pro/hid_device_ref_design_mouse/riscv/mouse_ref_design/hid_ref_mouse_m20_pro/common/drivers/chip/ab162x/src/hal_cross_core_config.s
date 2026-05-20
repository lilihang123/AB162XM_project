	.file	"hal_cross_core_config.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c"
	.hidden	ccm_disable_all_log
	.globl	ccm_disable_all_log
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".102,"aw"
	.align	2
	.type	ccm_disable_all_log, @object
	.size	ccm_disable_all_log, 1
ccm_disable_all_log:
	.zero	1
	.hidden	ccm_mux
	.globl	ccm_mux
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".98,"aw"
	.align	2
	.type	ccm_mux, @object
	.size	ccm_mux, 512
ccm_mux:
	.zero	512
	.hidden	ccm_hid_common_para
	.globl	ccm_hid_common_para
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".90,"aw"
	.align	2
	.type	ccm_hid_common_para, @object
	.size	ccm_hid_common_para, 5868
ccm_hid_common_para:
	.zero	5868
	.hidden	ccm_pka_share
	.globl	ccm_pka_share
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".86,"aw"
	.align	2
	.type	ccm_pka_share, @object
	.size	ccm_pka_share, 148
ccm_pka_share:
	.zero	148
	.hidden	ccm_exception_risc_v_0
	.globl	ccm_exception_risc_v_0
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".81,"aw"
	.align	2
	.type	ccm_exception_risc_v_0, @object
	.size	ccm_exception_risc_v_0, 396
ccm_exception_risc_v_0:
	.zero	396
	.hidden	log_control_block_mirror_common
	.globl	log_control_block_mirror_common
	.section	.log_filter_mirror.common,"a"
	.align	2
	.type	log_control_block_mirror_common, @object
	.size	log_control_block_mirror_common, 7
log_control_block_mirror_common:
	.string	"common"
	.hidden	log_control_block_common
	.globl	log_control_block_common
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"common"
	.section	.log_filter.common,"aw"
	.align	2
	.type	log_control_block_common, @object
	.size	log_control_block_common, 28
log_control_block_common:
	.word	.LC0
	.word	0
	.word	1
	.word	0
	.word	0
	.word	0
	.word	print_module_msgid_log
	.hidden	ccm_build_date_time_str
	.globl	ccm_build_date_time_str
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".72,"aw"
	.align	2
	.type	ccm_build_date_time_str, @object
	.size	ccm_build_date_time_str, 144
ccm_build_date_time_str:
	.zero	144
	.hidden	ccm_sw_verno_str
	.globl	ccm_sw_verno_str
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".71,"aw"
	.align	2
	.type	ccm_sw_verno_str, @object
	.size	ccm_sw_verno_str, 144
ccm_sw_verno_str:
	.zero	144
	.hidden	ccm_syslog
	.globl	ccm_syslog
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".70,"aw"
	.align	2
	.type	ccm_syslog, @object
	.size	ccm_syslog, 360
ccm_syslog:
	.zero	360
	.hidden	ccm_eint_count
	.globl	ccm_eint_count
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".62,"aw"
	.align	2
	.type	ccm_eint_count, @object
	.size	ccm_eint_count, 40
ccm_eint_count:
	.zero	40
	.hidden	ccm_syslog_uart_para
	.globl	ccm_syslog_uart_para
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".60,"aw"
	.align	2
	.type	ccm_syslog_uart_para, @object
	.size	ccm_syslog_uart_para, 120
ccm_syslog_uart_para:
	.zero	120
	.hidden	ccm_spi_sensor
	.globl	ccm_spi_sensor
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".55,"aw"
	.align	4
	.type	ccm_spi_sensor, @object
	.size	ccm_spi_sensor, 16
ccm_spi_sensor:
	.zero	16
	.hidden	ccm_core_status
	.globl	ccm_core_status
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".53,"aw"
	.align	2
	.type	ccm_core_status, @object
	.size	ccm_core_status, 8
ccm_core_status:
	.zero	8
	.hidden	ccm_ccni
	.globl	ccm_ccni
	.section	.share_zidata."/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c".51,"aw"
	.align	2
	.type	ccm_ccni, @object
	.size	ccm_ccni, 256
ccm_ccni:
	.zero	256
	.text
.Letext0:
	.file 1 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 2 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 3 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_eint_internal.h"
	.file 5 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_cross_core_config.h"
	.file 6 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 8 "/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c"
	.file 9 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x7c9
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x13
	.4byte	.LASF170
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.Ldebug_line0
	.uleb128 0x5
	.byte	0x1
	.byte	0x6
	.4byte	.LASF2
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.uleb128 0x5
	.byte	0x2
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x5
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x5
	.byte	0x8
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x5
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x14
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x5
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x15
	.byte	0x4
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x11
	.4byte	0x6d
	.uleb128 0xa
	.4byte	0x74
	.uleb128 0x8
	.4byte	.LASF13
	.byte	0x1
	.byte	0x2e
	.byte	0x17
	.4byte	0x25
	.uleb128 0x3
	.4byte	0x7e
	.uleb128 0x8
	.4byte	.LASF14
	.byte	0x1
	.byte	0x34
	.byte	0x1b
	.4byte	0x41
	.uleb128 0xc
	.4byte	0x5d
	.byte	0x2
	.byte	0x37
	.byte	0xe
	.4byte	0xb4
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x1
	.byte	0
	.uleb128 0xc
	.4byte	0x5d
	.byte	0x2
	.byte	0x3d
	.byte	0xe
	.4byte	0xd9
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x3
	.byte	0
	.uleb128 0x8
	.4byte	.LASF21
	.byte	0x2
	.byte	0x42
	.byte	0x3
	.4byte	0xb4
	.uleb128 0xc
	.4byte	0x5d
	.byte	0x2
	.byte	0x45
	.byte	0xe
	.4byte	0x14c
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x3f
	.byte	0
	.uleb128 0x8
	.4byte	.LASF37
	.byte	0x2
	.byte	0x57
	.byte	0x3
	.4byte	0xe5
	.uleb128 0x8
	.4byte	.LASF38
	.byte	0x2
	.byte	0x59
	.byte	0x10
	.4byte	0x164
	.uleb128 0xa
	.4byte	0x169
	.uleb128 0xf
	.4byte	0x189
	.uleb128 0x2
	.4byte	0x6b
	.uleb128 0x2
	.4byte	0x79
	.uleb128 0x2
	.4byte	0x56
	.uleb128 0x2
	.4byte	0xd9
	.uleb128 0x2
	.4byte	0x79
	.uleb128 0xd
	.byte	0
	.uleb128 0x8
	.4byte	.LASF39
	.byte	0x2
	.byte	0x5a
	.byte	0x10
	.4byte	0x195
	.uleb128 0xa
	.4byte	0x19a
	.uleb128 0xf
	.4byte	0x1c4
	.uleb128 0x2
	.4byte	0x6b
	.uleb128 0x2
	.4byte	0x79
	.uleb128 0x2
	.4byte	0x56
	.uleb128 0x2
	.4byte	0xd9
	.uleb128 0x2
	.4byte	0x1c4
	.uleb128 0x2
	.4byte	0x56
	.uleb128 0x2
	.4byte	0x79
	.uleb128 0xd
	.byte	0
	.uleb128 0xa
	.4byte	0x1c9
	.uleb128 0x16
	.uleb128 0x8
	.4byte	.LASF40
	.byte	0x2
	.byte	0x5b
	.byte	0x10
	.4byte	0x1d6
	.uleb128 0xa
	.4byte	0x1db
	.uleb128 0xf
	.4byte	0x1f6
	.uleb128 0x2
	.4byte	0x6b
	.uleb128 0x2
	.4byte	0xd9
	.uleb128 0x2
	.4byte	0x79
	.uleb128 0x2
	.4byte	0x8f
	.uleb128 0xd
	.byte	0
	.uleb128 0x8
	.4byte	.LASF41
	.byte	0x2
	.byte	0x5c
	.byte	0x14
	.4byte	0x202
	.uleb128 0xa
	.4byte	0x207
	.uleb128 0x17
	.4byte	0x8f
	.4byte	0x22a
	.uleb128 0x2
	.4byte	0x6b
	.uleb128 0x2
	.4byte	0xd9
	.uleb128 0x2
	.4byte	0x14c
	.uleb128 0x2
	.4byte	0x22a
	.uleb128 0x2
	.4byte	0x22f
	.byte	0
	.uleb128 0xa
	.4byte	0x1c4
	.uleb128 0xa
	.4byte	0x8f
	.uleb128 0x18
	.byte	0x1c
	.byte	0x2
	.byte	0x5e
	.byte	0x9
	.4byte	0x292
	.uleb128 0xb
	.4byte	.LASF42
	.byte	0x5f
	.byte	0x11
	.4byte	0x79
	.byte	0
	.uleb128 0xb
	.4byte	.LASF43
	.byte	0x60
	.byte	0xe
	.4byte	0x8f
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF44
	.byte	0x61
	.byte	0xe
	.4byte	0x8f
	.byte	0x8
	.uleb128 0xb
	.4byte	.LASF45
	.byte	0x62
	.byte	0xf
	.4byte	0x158
	.byte	0xc
	.uleb128 0xb
	.4byte	.LASF46
	.byte	0x63
	.byte	0x15
	.4byte	0x189
	.byte	0x10
	.uleb128 0xb
	.4byte	.LASF47
	.byte	0x64
	.byte	0x12
	.4byte	0x1f6
	.byte	0x14
	.uleb128 0xb
	.4byte	.LASF48
	.byte	0x65
	.byte	0x10
	.4byte	0x1ca
	.byte	0x18
	.byte	0
	.uleb128 0x8
	.4byte	.LASF49
	.byte	0x2
	.byte	0x66
	.byte	0x3
	.4byte	0x234
	.uleb128 0x19
	.4byte	.LASF171
	.byte	0x7
	.byte	0x4
	.4byte	0x5d
	.byte	0x9
	.2byte	0x128
	.byte	0x12
	.4byte	0x324
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0xb
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
	.byte	0
	.uleb128 0x1a
	.byte	0x7
	.byte	0x4
	.4byte	0x5d
	.byte	0x3
	.2byte	0x407
	.byte	0xe
	.4byte	0x48a
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x38
	.byte	0
	.uleb128 0xc
	.4byte	0x5d
	.byte	0x4
	.byte	0x4b
	.byte	0xe
	.4byte	0x4d9
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0xa
	.byte	0
	.uleb128 0x5
	.byte	0x1
	.byte	0x2
	.4byte	.LASF137
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x4f0
	.uleb128 0x9
	.4byte	0x5d
	.byte	0xff
	.byte	0
	.uleb128 0x3
	.4byte	0x4e0
	.uleb128 0x6
	.4byte	.LASF138
	.byte	0x83
	.4byte	0x4f0
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x50f
	.uleb128 0x9
	.4byte	0x5d
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.4byte	0x4ff
	.uleb128 0x6
	.4byte	.LASF139
	.byte	0x85
	.4byte	0x50f
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x52e
	.uleb128 0x9
	.4byte	0x5d
	.byte	0xf
	.byte	0
	.uleb128 0x3
	.4byte	0x51e
	.uleb128 0x6
	.4byte	.LASF140
	.byte	0x87
	.4byte	0x52e
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x54d
	.uleb128 0x9
	.4byte	0x5d
	.byte	0x77
	.byte	0
	.uleb128 0x3
	.4byte	0x53d
	.uleb128 0x6
	.4byte	.LASF141
	.byte	0x8c
	.4byte	0x54d
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x56c
	.uleb128 0x9
	.4byte	0x5d
	.byte	0x27
	.byte	0
	.uleb128 0x3
	.4byte	0x55c
	.uleb128 0x6
	.4byte	.LASF142
	.byte	0x8e
	.4byte	0x56c
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x58b
	.uleb128 0x9
	.4byte	0x5d
	.byte	0x93
	.byte	0
	.uleb128 0x3
	.4byte	0x57b
	.uleb128 0x6
	.4byte	.LASF143
	.byte	0x97
	.4byte	0x58b
	.uleb128 0xc
	.4byte	0x5d
	.byte	0x6
	.byte	0x50
	.byte	0xe
	.4byte	0x5dd
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.4byte	0x5d
	.byte	0x7
	.byte	0x31
	.byte	0x1
	.4byte	0x61a
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
	.byte	0
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x62b
	.uleb128 0xe
	.4byte	0x5d
	.2byte	0x16eb
	.byte	0
	.uleb128 0x3
	.4byte	0x61a
	.uleb128 0x6
	.4byte	.LASF161
	.byte	0x9c
	.4byte	0x62b
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x64b
	.uleb128 0xe
	.4byte	0x5d
	.2byte	0x1ff
	.byte	0
	.uleb128 0x3
	.4byte	0x63a
	.uleb128 0x6
	.4byte	.LASF162
	.byte	0xa5
	.4byte	0x64b
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x66b
	.uleb128 0xe
	.4byte	0x5d
	.2byte	0x18b
	.byte	0
	.uleb128 0x3
	.4byte	0x65a
	.uleb128 0x6
	.4byte	.LASF163
	.byte	0xaa
	.4byte	0x66b
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x68a
	.uleb128 0x9
	.4byte	0x5d
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	0x67a
	.uleb128 0x6
	.4byte	.LASF164
	.byte	0xae
	.4byte	0x68a
	.uleb128 0x7
	.4byte	0x4f5
	.byte	0x33
	.byte	0xb7
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_ccni
	.uleb128 0x7
	.4byte	0x514
	.byte	0x35
	.byte	0xb7
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_core_status
	.uleb128 0x7
	.4byte	0x533
	.byte	0x37
	.byte	0xd9
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_spi_sensor
	.uleb128 0x7
	.4byte	0x552
	.byte	0x3c
	.byte	0xb7
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_syslog_uart_para
	.uleb128 0x7
	.4byte	0x571
	.byte	0x3e
	.byte	0xb7
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_eint_count
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x6eb
	.uleb128 0xe
	.4byte	0x5d
	.2byte	0x167
	.byte	0
	.uleb128 0x3
	.4byte	0x6da
	.uleb128 0x10
	.4byte	.LASF165
	.byte	0x46
	.4byte	0x6eb
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_syslog
	.uleb128 0x4
	.4byte	0x8a
	.4byte	0x710
	.uleb128 0x9
	.4byte	0x5d
	.byte	0x8f
	.byte	0
	.uleb128 0x3
	.4byte	0x700
	.uleb128 0x10
	.4byte	.LASF166
	.byte	0x47
	.4byte	0x710
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_sw_verno_str
	.uleb128 0x10
	.4byte	.LASF167
	.byte	0x48
	.4byte	0x710
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_build_date_time_str
	.uleb128 0x12
	.4byte	.LASF168
	.byte	0x4c
	.byte	0x4c
	.4byte	0x292
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_common
	.uleb128 0x4
	.4byte	0x74
	.4byte	0x756
	.uleb128 0x9
	.4byte	0x5d
	.byte	0x6
	.byte	0
	.uleb128 0x11
	.4byte	0x746
	.uleb128 0x12
	.4byte	.LASF169
	.byte	0x4c
	.byte	0x7c
	.4byte	0x756
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_mirror_common
	.uleb128 0x7
	.4byte	0x670
	.byte	0x51
	.byte	0xd8
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_exception_risc_v_0
	.uleb128 0x7
	.4byte	0x590
	.byte	0x56
	.byte	0xb7
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_pka_share
	.uleb128 0x7
	.4byte	0x630
	.byte	0x5a
	.byte	0xb7
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_hid_common_para
	.uleb128 0x7
	.4byte	0x650
	.byte	0x62
	.byte	0xb7
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_mux
	.uleb128 0x7
	.4byte	0x68f
	.byte	0x66
	.byte	0xb8
	.uleb128 0x5
	.byte	0x3
	.4byte	ccm_disable_all_log
	.uleb128 0x1b
	.4byte	.LASF172
	.byte	0x2
	.2byte	0x129
	.byte	0xd
	.uleb128 0x2
	.4byte	0x6b
	.uleb128 0x2
	.4byte	0xd9
	.uleb128 0x2
	.4byte	0x79
	.uleb128 0x2
	.4byte	0x8f
	.uleb128 0xd
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
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
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
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 25
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
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
	.uleb128 0xc
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
	.uleb128 0xd
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
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
	.sleb128 8
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 183
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x88
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0x34
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x14
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF162:
	.string	"ccm_mux"
.LASF143:
	.string	"ccm_pka_share"
.LASF120:
	.string	"HAL_EINT_USB0"
.LASF144:
	.string	"DBG_PIN_SPI_CB"
.LASF142:
	.string	"ccm_eint_count"
.LASF28:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF118:
	.string	"HAL_EINT_UART_1_RX"
.LASF170:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF30:
	.string	"LOG_TYPE_HCI_DATA"
.LASF47:
	.string	"tlv_dump_handle"
.LASF160:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF52:
	.string	"QDEC_IRQn"
.LASF163:
	.string	"ccm_exception_risc_v_0"
.LASF22:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF108:
	.string	"HAL_EINT_NUMBER_39"
.LASF168:
	.string	"log_control_block_common"
.LASF140:
	.string	"ccm_spi_sensor"
.LASF27:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF8:
	.string	"long long int"
.LASF121:
	.string	"HAL_EINT_USB1"
.LASF122:
	.string	"HAL_EINT_USB2"
.LASF167:
	.string	"ccm_build_date_time_str"
.LASF9:
	.string	"long long unsigned int"
.LASF164:
	.string	"ccm_disable_all_log"
.LASF58:
	.string	"UART_DMA_IRQn"
.LASF117:
	.string	"HAL_EINT_UART_0_RX"
.LASF54:
	.string	"UART_IRQn"
.LASF154:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF44:
	.string	"print_level"
.LASF56:
	.string	"RTC_IRQn"
.LASF53:
	.string	"KEYSCAN_IRQn"
.LASF6:
	.string	"long int"
.LASF38:
	.string	"f_print_t"
.LASF29:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF96:
	.string	"HAL_EINT_NUMBER_27"
.LASF39:
	.string	"f_dump_buffer_t"
.LASF172:
	.string	"print_module_msgid_log"
.LASF159:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF33:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF62:
	.string	"I3C0_IRQn"
.LASF84:
	.string	"HAL_EINT_NUMBER_15"
.LASF61:
	.string	"EINT_IRQn"
.LASF63:
	.string	"I3C0_DMA_IRQn"
.LASF153:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF10:
	.string	"unsigned int"
.LASF43:
	.string	"log_switch"
.LASF26:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF32:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF7:
	.string	"long unsigned int"
.LASF45:
	.string	"print_handle"
.LASF141:
	.string	"ccm_syslog_uart_para"
.LASF5:
	.string	"short unsigned int"
.LASF125:
	.string	"HAL_EINT_NUMBER_MAX"
.LASF31:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF69:
	.string	"HAL_EINT_NUMBER_0"
.LASF70:
	.string	"HAL_EINT_NUMBER_1"
.LASF71:
	.string	"HAL_EINT_NUMBER_2"
.LASF72:
	.string	"HAL_EINT_NUMBER_3"
.LASF73:
	.string	"HAL_EINT_NUMBER_4"
.LASF74:
	.string	"HAL_EINT_NUMBER_5"
.LASF75:
	.string	"HAL_EINT_NUMBER_6"
.LASF76:
	.string	"HAL_EINT_NUMBER_7"
.LASF77:
	.string	"HAL_EINT_NUMBER_8"
.LASF78:
	.string	"HAL_EINT_NUMBER_9"
.LASF20:
	.string	"PRINT_LEVEL_ERROR"
.LASF19:
	.string	"PRINT_LEVEL_WARNING"
.LASF64:
	.string	"SPI_MST0_IRQn"
.LASF37:
	.string	"log_type_t"
.LASF146:
	.string	"DBG_PIN_NACK"
.LASF100:
	.string	"HAL_EINT_NUMBER_31"
.LASF165:
	.string	"ccm_syslog"
.LASF157:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF171:
	.string	"IRQn"
.LASF126:
	.string	"EINT_COUNTER_NUMBER_0"
.LASF127:
	.string	"EINT_COUNTER_NUMBER_1"
.LASF128:
	.string	"EINT_COUNTER_NUMBER_2"
.LASF129:
	.string	"EINT_COUNTER_NUMBER_3"
.LASF130:
	.string	"EINT_COUNTER_NUMBER_4"
.LASF131:
	.string	"EINT_COUNTER_NUMBER_5"
.LASF132:
	.string	"EINT_COUNTER_NUMBER_6"
.LASF133:
	.string	"EINT_COUNTER_NUMBER_7"
.LASF134:
	.string	"EINT_COUNTER_NUMBER_8"
.LASF135:
	.string	"EINT_COUNTER_NUMBER_9"
.LASF57:
	.string	"GPT_IRQn"
.LASF151:
	.string	"DBG_PIN_USB_TX"
.LASF136:
	.string	"EINT_COUNTER_NUMBER_MUX"
.LASF50:
	.string	"SW_IRQn"
.LASF66:
	.string	"USB_IRQn"
.LASF55:
	.string	"SPI_MST1_IRQn"
.LASF23:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF79:
	.string	"HAL_EINT_NUMBER_10"
.LASF80:
	.string	"HAL_EINT_NUMBER_11"
.LASF81:
	.string	"HAL_EINT_NUMBER_12"
.LASF82:
	.string	"HAL_EINT_NUMBER_13"
.LASF83:
	.string	"HAL_EINT_NUMBER_14"
.LASF18:
	.string	"PRINT_LEVEL_INFO"
.LASF85:
	.string	"HAL_EINT_NUMBER_16"
.LASF86:
	.string	"HAL_EINT_NUMBER_17"
.LASF87:
	.string	"HAL_EINT_NUMBER_18"
.LASF88:
	.string	"HAL_EINT_NUMBER_19"
.LASF139:
	.string	"ccm_core_status"
.LASF15:
	.string	"DEBUG_LOG_ON"
.LASF137:
	.string	"_Bool"
.LASF3:
	.string	"unsigned char"
.LASF124:
	.string	"HAL_EINT_RESERVED"
.LASF21:
	.string	"print_level_t"
.LASF4:
	.string	"short int"
.LASF59:
	.string	"PMU_IRQn"
.LASF138:
	.string	"ccm_ccni"
.LASF60:
	.string	"MCU_DMA_IRQn"
.LASF49:
	.string	"log_control_block_t"
.LASF35:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF155:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF36:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF89:
	.string	"HAL_EINT_NUMBER_20"
.LASF90:
	.string	"HAL_EINT_NUMBER_21"
.LASF91:
	.string	"HAL_EINT_NUMBER_22"
.LASF92:
	.string	"HAL_EINT_NUMBER_23"
.LASF93:
	.string	"HAL_EINT_NUMBER_24"
.LASF94:
	.string	"HAL_EINT_NUMBER_25"
.LASF95:
	.string	"HAL_EINT_NUMBER_26"
.LASF14:
	.string	"uint32_t"
.LASF97:
	.string	"HAL_EINT_NUMBER_28"
.LASF98:
	.string	"HAL_EINT_NUMBER_29"
.LASF114:
	.string	"HAL_EINT_NUMBER_45"
.LASF145:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF116:
	.string	"HAL_EINT_NUMBER_47"
.LASF46:
	.string	"dump_handle"
.LASF11:
	.string	"long double"
.LASF169:
	.string	"log_control_block_mirror_common"
.LASF12:
	.string	"char"
.LASF2:
	.string	"signed char"
.LASF65:
	.string	"IRQ_GEN_IRQn"
.LASF166:
	.string	"ccm_sw_verno_str"
.LASF42:
	.string	"module_name"
.LASF67:
	.string	"BT_IRQn"
.LASF34:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF156:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF99:
	.string	"HAL_EINT_NUMBER_30"
.LASF17:
	.string	"PRINT_LEVEL_DEBUG"
.LASF101:
	.string	"HAL_EINT_NUMBER_32"
.LASF102:
	.string	"HAL_EINT_NUMBER_33"
.LASF103:
	.string	"HAL_EINT_NUMBER_34"
.LASF104:
	.string	"HAL_EINT_NUMBER_35"
.LASF105:
	.string	"HAL_EINT_NUMBER_36"
.LASF106:
	.string	"HAL_EINT_NUMBER_37"
.LASF107:
	.string	"HAL_EINT_NUMBER_38"
.LASF41:
	.string	"f_tlv_dump_t"
.LASF51:
	.string	"LED_IRQn"
.LASF13:
	.string	"uint8_t"
.LASF147:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF148:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF161:
	.string	"ccm_hid_common_para"
.LASF152:
	.string	"DBG_PIN_MAX"
.LASF24:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF40:
	.string	"f_msg_id_t"
.LASF150:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF123:
	.string	"HAL_EINT_LPCOMP"
.LASF48:
	.string	"msg_id_handle"
.LASF158:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF119:
	.string	"HAL_EINT_UART_2_RX"
.LASF25:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF149:
	.string	"DBG_PIN_USB_SOF"
.LASF109:
	.string	"HAL_EINT_NUMBER_40"
.LASF110:
	.string	"HAL_EINT_NUMBER_41"
.LASF111:
	.string	"HAL_EINT_NUMBER_42"
.LASF112:
	.string	"HAL_EINT_NUMBER_43"
.LASF113:
	.string	"HAL_EINT_NUMBER_44"
.LASF16:
	.string	"DEBUG_LOG_OFF"
.LASF115:
	.string	"HAL_EINT_NUMBER_46"
.LASF68:
	.string	"IRQ_NUMBER_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/drivers/chip/ab162x/src/hal_cross_core_config.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
