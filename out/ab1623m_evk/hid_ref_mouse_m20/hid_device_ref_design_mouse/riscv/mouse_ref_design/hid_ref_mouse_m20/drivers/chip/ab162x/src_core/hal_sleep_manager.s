	.file	"hal_sleep_manager.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager.c"
	.section	.text.hal_sleep_manager_set_sleep_handle,"ax",@progbits
	.align	1
	.globl	hal_sleep_manager_set_sleep_handle
	.hidden	hal_sleep_manager_set_sleep_handle
	.type	hal_sleep_manager_set_sleep_handle, @function
hal_sleep_manager_set_sleep_handle:
.LFB4:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager.c"
	.loc 1 91 1
	.cfi_startproc
.LVL0:
	.loc 1 96 5
	.loc 1 98 5
	.loc 1 99 1 is_stmt 0
	li	a0,0
.LVL1:
	ret
	.cfi_endproc
.LFE4:
	.size	hal_sleep_manager_set_sleep_handle, .-hal_sleep_manager_set_sleep_handle
	.section	.text.hal_sleep_manager_lock_sleep,"ax",@progbits
	.align	1
	.globl	hal_sleep_manager_lock_sleep
	.hidden	hal_sleep_manager_lock_sleep
	.type	hal_sleep_manager_lock_sleep, @function
hal_sleep_manager_lock_sleep:
.LFB5:
	.loc 1 102 1 is_stmt 1
	.cfi_startproc
.LVL2:
	.loc 1 106 5
	.loc 1 107 1 is_stmt 0
	li	a0,0
.LVL3:
	ret
	.cfi_endproc
.LFE5:
	.size	hal_sleep_manager_lock_sleep, .-hal_sleep_manager_lock_sleep
	.section	.text.hal_sleep_manager_unlock_sleep,"ax",@progbits
	.align	1
	.globl	hal_sleep_manager_unlock_sleep
	.hidden	hal_sleep_manager_unlock_sleep
	.type	hal_sleep_manager_unlock_sleep, @function
hal_sleep_manager_unlock_sleep:
.LFB14:
	.cfi_startproc
	.loc 1 109 28 is_stmt 1
	li	a0,0
	ret
	.cfi_endproc
.LFE14:
	.size	hal_sleep_manager_unlock_sleep, .-hal_sleep_manager_unlock_sleep
	.section	.text.hal_sleep_manager_release_sleep_handle,"ax",@progbits
	.align	1
	.globl	hal_sleep_manager_release_sleep_handle
	.hidden	hal_sleep_manager_release_sleep_handle
	.type	hal_sleep_manager_release_sleep_handle, @function
hal_sleep_manager_release_sleep_handle:
.LFB16:
	.cfi_startproc
	.loc 1 117 28
	li	a0,0
	ret
	.cfi_endproc
.LFE16:
	.size	hal_sleep_manager_release_sleep_handle, .-hal_sleep_manager_release_sleep_handle
	.section	.text.hal_sleep_manager_get_lock_status,"ax",@progbits
	.align	1
	.globl	hal_sleep_manager_get_lock_status
	.hidden	hal_sleep_manager_get_lock_status
	.type	hal_sleep_manager_get_lock_status, @function
hal_sleep_manager_get_lock_status:
.LFB8:
	.loc 1 130 1
	.cfi_startproc
	.loc 1 134 5
	.loc 1 136 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE8:
	.size	hal_sleep_manager_get_lock_status, .-hal_sleep_manager_get_lock_status
	.section	.text.hal_sleep_manager_is_sleep_locked,"ax",@progbits
	.align	1
	.globl	hal_sleep_manager_is_sleep_locked
	.hidden	hal_sleep_manager_is_sleep_locked
	.type	hal_sleep_manager_is_sleep_locked, @function
hal_sleep_manager_is_sleep_locked:
.LFB9:
	.loc 1 139 1 is_stmt 1
	.cfi_startproc
	.loc 1 143 5
	.loc 1 145 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE9:
	.size	hal_sleep_manager_is_sleep_locked, .-hal_sleep_manager_is_sleep_locked
	.section	.text.hal_sleep_manager_is_sleep_handle_alive,"ax",@progbits
	.align	1
	.globl	hal_sleep_manager_is_sleep_handle_alive
	.hidden	hal_sleep_manager_is_sleep_handle_alive
	.type	hal_sleep_manager_is_sleep_handle_alive, @function
hal_sleep_manager_is_sleep_handle_alive:
.LFB10:
	.loc 1 148 1 is_stmt 1
	.cfi_startproc
.LVL4:
	.loc 1 152 5
	.loc 1 154 1 is_stmt 0
	li	a0,0
.LVL5:
	ret
	.cfi_endproc
.LFE10:
	.size	hal_sleep_manager_is_sleep_handle_alive, .-hal_sleep_manager_is_sleep_handle_alive
	.section	.text.hal_sleep_manager_riscv_sleep_routine,"ax",@progbits
	.align	1
	.globl	hal_sleep_manager_riscv_sleep_routine
	.hidden	hal_sleep_manager_riscv_sleep_routine
	.type	hal_sleep_manager_riscv_sleep_routine, @function
hal_sleep_manager_riscv_sleep_routine:
.LFB11:
	.loc 1 156 49 is_stmt 1
	.cfi_startproc
	.loc 1 165 5
	tail	sleep_management_enter_sleep
.LVL6:
	.cfi_endproc
.LFE11:
	.size	hal_sleep_manager_riscv_sleep_routine, .-hal_sleep_manager_riscv_sleep_routine
	.section	.text.hal_sleep_manager_init,"ax",@progbits
	.align	1
	.globl	hal_sleep_manager_init
	.hidden	hal_sleep_manager_init
	.type	hal_sleep_manager_init, @function
hal_sleep_manager_init:
.LFB12:
	.loc 1 171 1
	.cfi_startproc
	.loc 1 172 5
	.loc 1 171 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 172 5
	call	spm_init
.LVL7:
	.loc 1 174 5 is_stmt 1
	.loc 1 189 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 174 26 discriminator 1
	sb	zero,sleep_manager_handle,a5
	.loc 1 188 5 is_stmt 1
	.loc 1 189 1 is_stmt 0
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE12:
	.size	hal_sleep_manager_init, .-hal_sleep_manager_init
	.hidden	sleep_manager_handle
	.globl	sleep_manager_handle
	.section	.sbss.sleep_manager_handle,"aw",@nobits
	.type	sleep_manager_handle, @object
	.size	sleep_manager_handle, 1
sleep_manager_handle:
	.zero	1
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_platform.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_spm.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_sleep_manager_internal.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x2df
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0xb
	.4byte	.LASF55
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL3
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
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
	.uleb128 0xc
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0xd
	.4byte	0x73
	.uleb128 0xe
	.byte	0x4
	.4byte	0x7a
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x2d
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x5
	.byte	0x5
	.4byte	0x65
	.byte	0x3
	.byte	0x2d
	.4byte	0xb6
	.uleb128 0xf
	.4byte	.LASF15
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x3
	.byte	0x30
	.byte	0x3
	.4byte	0x9d
	.uleb128 0x5
	.byte	0x7
	.4byte	0x34
	.byte	0x4
	.byte	0x2a
	.4byte	0x16b
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
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0xff
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF44
	.uleb128 0x10
	.4byte	.LASF56
	.byte	0x1
	.byte	0xa9
	.byte	0x9
	.4byte	0x85
	.uleb128 0x5
	.byte	0x3
	.4byte	sleep_manager_handle
	.uleb128 0x11
	.4byte	.LASF57
	.byte	0x5
	.2byte	0x13a
	.byte	0x5
	.4byte	0x65
	.uleb128 0x12
	.4byte	.LASF58
	.byte	0x6
	.byte	0x5e
	.byte	0x6
	.uleb128 0x6
	.4byte	.LASF45
	.byte	0xaa
	.byte	0x1c
	.4byte	0xb6
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1bc
	.uleb128 0x13
	.4byte	.LVL7
	.4byte	0x184
	.byte	0
	.uleb128 0x14
	.4byte	.LASF59
	.byte	0x1
	.byte	0x9c
	.byte	0x6
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1dc
	.uleb128 0x15
	.4byte	.LVL6
	.4byte	0x191
	.byte	0
	.uleb128 0x6
	.4byte	.LASF46
	.byte	0x93
	.byte	0x5
	.4byte	0x16b
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x206
	.uleb128 0x16
	.4byte	.LASF51
	.byte	0x1
	.byte	0x93
	.byte	0x35
	.4byte	0x85
	.4byte	.LLST2
	.byte	0
	.uleb128 0x7
	.4byte	.LASF47
	.byte	0x8a
	.byte	0x5
	.4byte	0x16b
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x7
	.4byte	.LASF48
	.byte	0x81
	.byte	0xa
	.4byte	0x91
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x8
	.4byte	.LASF49
	.byte	0x75
	.4byte	0xb6
	.4byte	0x24a
	.uleb128 0x3
	.4byte	.LASF51
	.byte	0x75
	.byte	0x4b
	.4byte	0x85
	.byte	0
	.uleb128 0x8
	.4byte	.LASF50
	.byte	0x6d
	.4byte	0xb6
	.4byte	0x264
	.uleb128 0x3
	.4byte	.LASF51
	.byte	0x6d
	.byte	0x43
	.4byte	0x85
	.byte	0
	.uleb128 0x9
	.4byte	.LASF52
	.byte	0x65
	.byte	0x1c
	.4byte	0xb6
	.4byte	0x27f
	.uleb128 0x3
	.4byte	.LASF51
	.byte	0x65
	.byte	0x41
	.4byte	0x85
	.byte	0
	.uleb128 0x9
	.4byte	.LASF53
	.byte	0x5a
	.byte	0x9
	.4byte	0x85
	.4byte	0x2a6
	.uleb128 0x3
	.4byte	.LASF54
	.byte	0x5a
	.byte	0x38
	.4byte	0x7f
	.uleb128 0x17
	.4byte	.LASF60
	.byte	0x1
	.byte	0x60
	.byte	0xd
	.4byte	0x85
	.byte	0
	.uleb128 0x18
	.4byte	0x27f
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2c9
	.uleb128 0xa
	.4byte	0x28e
	.4byte	.LLST0
	.uleb128 0x19
	.4byte	0x299
	.byte	0
	.byte	0
	.uleb128 0x1a
	.4byte	0x264
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xa
	.4byte	0x273
	.4byte	.LLST1
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.sleb128 28
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
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
.LLST2:
	.byte	0x6
	.4byte	.LVL4
	.byte	0x4
	.uleb128 .LVL4-.LVL4
	.uleb128 .LVL5-.LVL4
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL5-.LVL4
	.uleb128 .LFE10-.LVL4
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
	.uleb128 .LVL1-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL1-.LVL0
	.uleb128 .LFE4-.LVL0
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
.LLST1:
	.byte	0x6
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL3-.LVL2
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL3-.LVL2
	.uleb128 .LFE5-.LVL2
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
	.4byte	0x5c
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
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
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
.LLRL3:
	.byte	0x7
	.4byte	.LFB4
	.uleb128 .LFE4-.LFB4
	.byte	0x7
	.4byte	.LFB5
	.uleb128 .LFE5-.LFB5
	.byte	0x7
	.4byte	.LFB14
	.uleb128 .LFE14-.LFB14
	.byte	0x7
	.4byte	.LFB16
	.uleb128 .LFE16-.LFB16
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
.LASF40:
	.string	"SLEEP_LOCK_I2C0"
.LASF24:
	.string	"SLEEP_LOCK_IRRX"
.LASF36:
	.string	"SLEEP_LOCK_USB"
.LASF57:
	.string	"spm_init"
.LASF29:
	.string	"SLEEP_LOCK_SPI_MST1"
.LASF44:
	.string	"_Bool"
.LASF15:
	.string	"HAL_SLEEP_MANAGER_ERROR"
.LASF46:
	.string	"hal_sleep_manager_is_sleep_handle_alive"
.LASF8:
	.string	"long int"
.LASF52:
	.string	"hal_sleep_manager_lock_sleep"
.LASF50:
	.string	"hal_sleep_manager_unlock_sleep"
.LASF32:
	.string	"SLEEP_LOCK_DCXO"
.LASF47:
	.string	"hal_sleep_manager_is_sleep_locked"
.LASF59:
	.string	"hal_sleep_manager_riscv_sleep_routine"
.LASF28:
	.string	"SLEEP_LOCK_SPI_MST0"
.LASF3:
	.string	"unsigned char"
.LASF30:
	.string	"SLEEP_LOCK_SPI_MST2"
.LASF18:
	.string	"SLEEP_LOCK_SECURITY_PD"
.LASF9:
	.string	"long unsigned int"
.LASF7:
	.string	"short unsigned int"
.LASF38:
	.string	"SLEEP_LOCK_UART1"
.LASF39:
	.string	"SLEEP_LOCK_UART2"
.LASF34:
	.string	"SLEEP_LOCK_I3C1"
.LASF54:
	.string	"handle_name"
.LASF23:
	.string	"SLEEP_LOCK_IRTX"
.LASF49:
	.string	"hal_sleep_manager_release_sleep_handle"
.LASF53:
	.string	"hal_sleep_manager_set_sleep_handle"
.LASF21:
	.string	"SLEEP_LOCK_TRNG"
.LASF6:
	.string	"short int"
.LASF58:
	.string	"sleep_management_enter_sleep"
.LASF27:
	.string	"SLEEP_LOCK_ESC"
.LASF42:
	.string	"SLEEP_LOCK_USER_START_ID"
.LASF4:
	.string	"unsigned int"
.LASF48:
	.string	"hal_sleep_manager_get_lock_status"
.LASF2:
	.string	"long long unsigned int"
.LASF13:
	.string	"uint8_t"
.LASF17:
	.string	"hal_sleep_manager_status_t"
.LASF37:
	.string	"SLEEP_LOCK_UART0"
.LASF41:
	.string	"SLEEP_LOCK_APP"
.LASF33:
	.string	"SLEEP_LOCK_SAR_ADC"
.LASF19:
	.string	"SLEEP_LOCK_AESOTF"
.LASF10:
	.string	"long long int"
.LASF12:
	.string	"char"
.LASF60:
	.string	"index"
.LASF51:
	.string	"handle_index"
.LASF20:
	.string	"SLEEP_LOCK_ESC_AESOTF"
.LASF26:
	.string	"SLEEP_LOCK_FLASH"
.LASF16:
	.string	"HAL_SLEEP_MANAGER_OK"
.LASF56:
	.string	"sleep_manager_handle"
.LASF14:
	.string	"uint32_t"
.LASF43:
	.string	"SLEEP_LOCK_INVALID_ID"
.LASF55:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF11:
	.string	"long double"
.LASF31:
	.string	"SLEEP_LOCK_SPI_SLV"
.LASF5:
	.string	"signed char"
.LASF35:
	.string	"SLEEP_LOCK_I3C1_DMA"
.LASF25:
	.string	"SLEEP_LOCK_AIO"
.LASF45:
	.string	"hal_sleep_manager_init"
.LASF22:
	.string	"SLEEP_LOCK_DMA"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src_core/hal_sleep_manager.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
