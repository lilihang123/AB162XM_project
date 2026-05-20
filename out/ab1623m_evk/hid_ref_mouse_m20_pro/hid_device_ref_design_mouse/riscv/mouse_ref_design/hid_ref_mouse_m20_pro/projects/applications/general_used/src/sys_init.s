	.file	"sys_init.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/../general_used/src/sys_init.c"
	.section	.text.system_init,"ax",@progbits
	.align	1
	.globl	system_init
	.hidden	system_init
	.type	system_init, @function
system_init:
.LFB4:
	.file 1 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/../general_used/src/sys_init.c"
	.loc 1 63 1
	.cfi_startproc
	.loc 1 64 5
	.loc 1 63 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 64 5
	call	hal_ccni_init
.LVL0:
	.loc 1 65 5 is_stmt 1
	li	a1,1
	li	a0,1
	call	hal_core_status_write
.LVL1:
	.loc 1 67 5
	call	log_init
.LVL2:
	.loc 1 73 5
	call	hal_sleep_manager_init
.LVL3:
	.loc 1 81 5
	li	a1,2
	li	a0,1
	call	hal_core_status_write
.LVL4:
	.loc 1 83 5
 #APP
# 83 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/../general_used/src/sys_init.c" 1
	csrrsi x0, mstatus, 0x8

# 0 "" 2
	.loc 1 84 1 is_stmt 0
 #NO_APP
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE4:
	.size	system_init, .-system_init
	.text
.Letext0:
	.file 2 "/workdir/airoha/common/drivers/chip/ab162x/../inc/hal_ccni.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_core_status.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager.h"
	.file 5 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1f0
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0xb
	.4byte	.LASF39
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x1
	.byte	0x1
	.byte	0x6
	.4byte	.LASF2
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.uleb128 0x1
	.byte	0x2
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x1
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x1
	.byte	0x4
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x1
	.byte	0x8
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x1
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0xc
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x1
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xd
	.byte	0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x2
	.2byte	0x120
	.byte	0xe
	.4byte	0xa8
	.uleb128 0x3
	.4byte	.LASF13
	.sleb128 -4
	.uleb128 0x3
	.4byte	.LASF14
	.sleb128 -3
	.uleb128 0x3
	.4byte	.LASF15
	.sleb128 -2
	.uleb128 0x3
	.4byte	.LASF16
	.sleb128 -1
	.uleb128 0x2
	.4byte	.LASF17
	.byte	0
	.byte	0
	.uleb128 0xe
	.4byte	.LASF22
	.byte	0x2
	.2byte	0x126
	.byte	0x3
	.4byte	0x7a
	.uleb128 0x5
	.byte	0x7
	.4byte	0x65
	.byte	0x3
	.byte	0x2d
	.4byte	0xdd
	.uleb128 0x2
	.4byte	.LASF18
	.byte	0
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x2
	.uleb128 0x8
	.4byte	.LASF21
	.4byte	0xffffffff
	.byte	0
	.uleb128 0x6
	.4byte	.LASF23
	.byte	0x3
	.byte	0x32
	.4byte	0xb5
	.uleb128 0x5
	.byte	0x5
	.4byte	0x5e
	.byte	0x3
	.byte	0x35
	.4byte	0x122
	.uleb128 0x3
	.4byte	.LASF24
	.sleb128 -1
	.uleb128 0x2
	.4byte	.LASF25
	.byte	0
	.uleb128 0x2
	.4byte	.LASF26
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF27
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF28
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF29
	.byte	0x4
	.uleb128 0x8
	.4byte	.LASF30
	.4byte	0x7fffffff
	.byte	0
	.uleb128 0x6
	.4byte	.LASF31
	.byte	0x3
	.byte	0x3d
	.4byte	0xe8
	.uleb128 0x5
	.byte	0x5
	.4byte	0x5e
	.byte	0x4
	.byte	0x2d
	.4byte	0x146
	.uleb128 0x3
	.4byte	.LASF32
	.sleb128 -1
	.uleb128 0x2
	.4byte	.LASF33
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	.LASF34
	.byte	0x4
	.byte	0x30
	.4byte	0x12d
	.uleb128 0x1
	.byte	0x1
	.byte	0x2
	.4byte	.LASF35
	.uleb128 0xf
	.4byte	.LASF36
	.byte	0x4
	.byte	0x3c
	.byte	0x1c
	.4byte	0x146
	.uleb128 0x9
	.4byte	.LASF37
	.byte	0x5
	.2byte	0x134
	.byte	0xc
	.4byte	0x5e
	.uleb128 0x10
	.4byte	.LASF40
	.byte	0x3
	.byte	0x43
	.byte	0x13
	.4byte	0x122
	.4byte	0x18c
	.uleb128 0xa
	.4byte	0xdd
	.uleb128 0xa
	.4byte	0x122
	.byte	0
	.uleb128 0x9
	.4byte	.LASF38
	.byte	0x2
	.2byte	0x194
	.byte	0x13
	.4byte	0xa8
	.uleb128 0x11
	.4byte	.LASF41
	.byte	0x1
	.byte	0x3e
	.byte	0x6
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x7
	.4byte	.LVL0
	.4byte	0x18c
	.uleb128 0x12
	.4byte	.LVL1
	.4byte	0x171
	.4byte	0x1cc
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x7
	.4byte	.LVL2
	.4byte	0x164
	.uleb128 0x7
	.4byte	.LVL3
	.4byte	0x158
	.uleb128 0x13
	.4byte	.LVL4
	.4byte	0x171
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x32
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x5
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
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
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
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0
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
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
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
.LLRL0:
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF17:
	.string	"HAL_CCNI_STATUS_OK"
.LASF40:
	.string	"hal_core_status_write"
.LASF14:
	.string	"HAL_CCNI_STATUS_BUSY"
.LASF39:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF23:
	.string	"hal_core_id_t"
.LASF24:
	.string	"HAL_CORE_ERROR"
.LASF32:
	.string	"HAL_SLEEP_MANAGER_ERROR"
.LASF10:
	.string	"unsigned int"
.LASF20:
	.string	"HAL_CORE_MAX"
.LASF18:
	.string	"HAL_CORE_MCU"
.LASF19:
	.string	"HAL_CORE_RISCV"
.LASF37:
	.string	"log_init"
.LASF15:
	.string	"HAL_CCNI_STATUS_ERROR"
.LASF16:
	.string	"HAL_CCNI_STATUS_NO_INIT"
.LASF7:
	.string	"long unsigned int"
.LASF5:
	.string	"short unsigned int"
.LASF25:
	.string	"HAL_CORE_OFF"
.LASF31:
	.string	"hal_core_status_t"
.LASF28:
	.string	"HAL_CORE_SLEEP"
.LASF3:
	.string	"unsigned char"
.LASF21:
	.string	"HAL_CORE_ID_NOT_EXIST"
.LASF26:
	.string	"HAL_CORE_INIT"
.LASF30:
	.string	"HAL_CORE_STATUS_MAX"
.LASF9:
	.string	"long long unsigned int"
.LASF38:
	.string	"hal_ccni_init"
.LASF34:
	.string	"hal_sleep_manager_status_t"
.LASF13:
	.string	"HAL_CCNI_STATUS_INVALID_PARAMETER"
.LASF27:
	.string	"HAL_CORE_ACTIVE"
.LASF8:
	.string	"long long int"
.LASF22:
	.string	"hal_ccni_status_t"
.LASF12:
	.string	"char"
.LASF4:
	.string	"short int"
.LASF33:
	.string	"HAL_SLEEP_MANAGER_OK"
.LASF29:
	.string	"HAL_CORE_EXCEPTION"
.LASF6:
	.string	"long int"
.LASF41:
	.string	"system_init"
.LASF11:
	.string	"long double"
.LASF2:
	.string	"signed char"
.LASF35:
	.string	"_Bool"
.LASF36:
	.string	"hal_sleep_manager_init"
	.section	.debug_line_str,"MS",@progbits,1
.LASF0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/../general_used/src/sys_init.c"
.LASF1:
	.string	"/workdir/airoha/risc-v"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
