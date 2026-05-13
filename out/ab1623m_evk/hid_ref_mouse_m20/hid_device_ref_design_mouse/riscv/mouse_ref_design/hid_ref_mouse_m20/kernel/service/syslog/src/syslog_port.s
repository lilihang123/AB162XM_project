	.file	"syslog_port.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/kernel/service/syslog/src/syslog_port.c"
	.section	.text.syslog_port_check_in_isr_handler,"ax",@progbits
	.align	1
	.globl	syslog_port_check_in_isr_handler
	.hidden	syslog_port_check_in_isr_handler
	.type	syslog_port_check_in_isr_handler, @function
syslog_port_check_in_isr_handler:
.LFB15:
	.file 1 "/workdir/airoha/risc-v/kernel/service/syslog/src/syslog_port.c"
	.loc 1 49 43
	.cfi_startproc
	.loc 1 51 5
	.loc 1 49 43 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 51 8
	call	hal_nvic_query_exception_number
.LVL0:
	.loc 1 60 1
	lw	ra,8(sp)
	.cfi_restore 1
	snez	a0,a0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE15:
	.size	syslog_port_check_in_isr_handler, .-syslog_port_check_in_isr_handler
	.section	.text.log_hw_semaphore_take,"ax",@progbits
	.align	1
	.globl	log_hw_semaphore_take
	.hidden	log_hw_semaphore_take
	.type	log_hw_semaphore_take, @function
log_hw_semaphore_take:
.LFB16:
	.loc 1 63 1 is_stmt 1
	.cfi_startproc
.LVL1:
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	sw	ra,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	mv	s0,a0
.LVL2:
.L4:
	.loc 1 66 5
	.loc 1 70 9
	.loc 1 70 13 is_stmt 0
	mv	a0,s0
	call	hw_semaphore_take_special
.LVL3:
	.loc 1 70 12 discriminator 1
	bne	a0,zero,.L4
	.loc 1 78 1
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL4:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE16:
	.size	log_hw_semaphore_take, .-log_hw_semaphore_take
	.section	.text.log_hw_semaphore_give,"ax",@progbits
	.align	1
	.globl	log_hw_semaphore_give
	.hidden	log_hw_semaphore_give
	.type	log_hw_semaphore_give, @function
log_hw_semaphore_give:
.LFB17:
	.loc 1 81 1 is_stmt 1
	.cfi_startproc
.LVL5:
	.loc 1 82 5
	.loc 1 81 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 82 39
	call	hw_semaphore_give_special
.LVL6:
	.loc 1 82 8 discriminator 1
	beq	a0,zero,.L7
	.loc 1 83 9 is_stmt 1
.LBB2:
	.loc 1 83 26 discriminator 1
	.loc 1 83 102 discriminator 1
	.loc 1 83 240 discriminator 1
.LBE2:
	.loc 1 89 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_remember_state
	.cfi_restore 1
.LBB3:
	.loc 1 83 240 discriminator 1
	li	a2,83
.LBE3:
	.loc 1 89 1
.LBB4:
	.loc 1 83 240 discriminator 1
	lla	a1,file.0
	lla	a0,exp.1
.LBE4:
	.loc 1 89 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
.LBB5:
	.loc 1 83 240 discriminator 1
	tail	light_assert
.LVL7:
.L7:
	.cfi_restore_state
.LBE5:
	.loc 1 89 1
	lw	ra,8(sp)
	.cfi_restore 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE17:
	.size	log_hw_semaphore_give, .-log_hw_semaphore_give
	.section	.tcm_code."/workdir/airoha/risc-v/kernel/service/syslog/src/syslog_port.c".95,"ax",@progbits
	.align	1
	.globl	exception_get_disable_all_log_flag
	.hidden	exception_get_disable_all_log_flag
	.type	exception_get_disable_all_log_flag, @function
exception_get_disable_all_log_flag:
.LFB18:
	.loc 1 96 1 is_stmt 1
	.cfi_startproc
	.loc 1 97 5
	.loc 1 98 1 is_stmt 0
	lbu	a0,ccm_disable_all_log
	ret
	.cfi_endproc
.LFE18:
	.size	exception_get_disable_all_log_flag, .-exception_get_disable_all_log_flag
	.section	.log_string,"a"
	.align	2
	.type	file.0, @object
	.size	file.0, 63
file.0:
	.string	"/workdir/airoha/risc-v/kernel/service/syslog/src/syslog_port.c"
	.align	2
	.type	exp.1, @object
	.size	exp.1, 2
exp.1:
	.string	"0"
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_hw_semaphore.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_cross_core_config.h"
	.file 5 "/workdir/airoha/risc-v/kernel/service/exception_handler/inc/exception_handler.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x373
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x11
	.4byte	.LASF64
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL5
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
	.uleb128 0x12
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
	.uleb128 0x7
	.4byte	0x73
	.uleb128 0xb
	.4byte	0x7a
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x2
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0xc
	.4byte	0x90
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0xb
	.4byte	0xa1
	.uleb128 0xd
	.byte	0x7
	.4byte	0x2d
	.byte	0xb6
	.4byte	0x184
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
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x20
	.byte	0
	.uleb128 0x5
	.4byte	.LASF49
	.byte	0x3
	.byte	0xfa
	.byte	0x3
	.4byte	0xb2
	.uleb128 0xd
	.byte	0x5
	.4byte	0x65
	.byte	0xfe
	.4byte	0x1b4
	.uleb128 0x8
	.4byte	.LASF50
	.sleb128 -3
	.uleb128 0x8
	.4byte	.LASF51
	.sleb128 -2
	.uleb128 0x8
	.4byte	.LASF52
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0
	.byte	0
	.uleb128 0x13
	.4byte	.LASF54
	.byte	0x3
	.2byte	0x103
	.byte	0x3
	.4byte	0x190
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF55
	.uleb128 0x9
	.4byte	0x9c
	.4byte	0x1d8
	.uleb128 0xa
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0xc
	.4byte	0x1c8
	.uleb128 0x14
	.4byte	.LASF65
	.byte	0x4
	.byte	0xae
	.byte	0x19
	.4byte	0x1d8
	.uleb128 0x15
	.4byte	.LASF66
	.byte	0x5
	.byte	0x44
	.byte	0xd
	.4byte	0x205
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x7f
	.uleb128 0x3
	.4byte	0x65
	.byte	0
	.uleb128 0xe
	.4byte	.LASF56
	.byte	0x30
	.4byte	0x1b4
	.4byte	0x219
	.uleb128 0x3
	.4byte	0x184
	.byte	0
	.uleb128 0xe
	.4byte	.LASF57
	.byte	0x2f
	.4byte	0x1b4
	.4byte	0x22d
	.uleb128 0x3
	.4byte	0x184
	.byte	0
	.uleb128 0x16
	.4byte	.LASF67
	.byte	0x1
	.byte	0x2e
	.byte	0x10
	.4byte	0x84
	.uleb128 0x17
	.4byte	.LASF68
	.byte	0x1
	.byte	0x5f
	.byte	0x98
	.4byte	0x65
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xf
	.4byte	.LASF61
	.byte	0x50
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2e9
	.uleb128 0x6
	.4byte	.LASF58
	.byte	0x50
	.byte	0x32
	.4byte	0x184
	.4byte	.LLST2
	.uleb128 0x6
	.4byte	.LASF59
	.byte	0x50
	.byte	0x45
	.4byte	0xa1
	.4byte	.LLST3
	.uleb128 0x18
	.4byte	.LLRL4
	.4byte	0x2d1
	.uleb128 0x19
	.string	"exp"
	.byte	0x1
	.byte	0x53
	.byte	0x59
	.4byte	0x2f9
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x1a
	.4byte	.LASF60
	.byte	0x1
	.byte	0x53
	.byte	0xa5
	.4byte	0x30e
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0x1b
	.4byte	.LVL7
	.4byte	0x1e9
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x53
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LVL6
	.4byte	0x205
	.uleb128 0x4
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
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0x7a
	.4byte	0x2f9
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x7
	.4byte	0x2e9
	.uleb128 0x9
	.4byte	0x7a
	.4byte	0x30e
	.uleb128 0xa
	.4byte	0x2d
	.byte	0x3e
	.byte	0
	.uleb128 0x7
	.4byte	0x2fe
	.uleb128 0xf
	.4byte	.LASF62
	.byte	0x3e
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x356
	.uleb128 0x6
	.4byte	.LASF58
	.byte	0x3e
	.byte	0x32
	.4byte	0x184
	.4byte	.LLST0
	.uleb128 0x6
	.4byte	.LASF59
	.byte	0x3e
	.byte	0x46
	.4byte	0xad
	.4byte	.LLST1
	.uleb128 0x10
	.4byte	.LVL3
	.4byte	0x219
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF63
	.byte	0x1
	.byte	0x31
	.byte	0x5
	.4byte	0x1c1
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1d
	.4byte	.LVL0
	.4byte	0x22d
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
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x6
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
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
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
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.sleb128 34
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
	.uleb128 0xf
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
	.uleb128 0x10
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
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
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL6-1-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL6-1-.LVL5
	.uleb128 .LFE17-.LVL5
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
.LLST3:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL6-1-.LVL5
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL6-1-.LVL5
	.uleb128 .LFE17-.LVL5
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
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL2-.LVL1
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL2-.LVL1
	.uleb128 .LVL4-.LVL1
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL4-.LVL1
	.uleb128 .LFE16-.LVL1
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
	.4byte	.LVL1
	.byte	0x4
	.uleb128 .LVL1-.LVL1
	.uleb128 .LVL2-.LVL1
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL2-.LVL1
	.uleb128 .LFE16-.LVL1
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
	.4byte	0x34
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
.LLRL5:
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF26:
	.string	"HAL_HW_SEMAPHORE_ID_10"
.LASF27:
	.string	"HAL_HW_SEMAPHORE_ID_11"
.LASF28:
	.string	"HAL_HW_SEMAPHORE_ID_12"
.LASF29:
	.string	"HAL_HW_SEMAPHORE_ID_13"
.LASF66:
	.string	"light_assert"
.LASF31:
	.string	"HAL_HW_SEMAPHORE_ID_15"
.LASF32:
	.string	"HAL_HW_SEMAPHORE_ID_16"
.LASF33:
	.string	"HAL_HW_SEMAPHORE_ID_17"
.LASF34:
	.string	"HAL_HW_SEMAPHORE_ID_18"
.LASF35:
	.string	"HAL_HW_SEMAPHORE_ID_19"
.LASF16:
	.string	"HAL_HW_SEMAPHORE_ID_0"
.LASF17:
	.string	"HAL_HW_SEMAPHORE_ID_1"
.LASF18:
	.string	"HAL_HW_SEMAPHORE_ID_2"
.LASF53:
	.string	"HAL_HW_SEMAPHORE_STATUS_OK"
.LASF20:
	.string	"HAL_HW_SEMAPHORE_ID_4"
.LASF21:
	.string	"HAL_HW_SEMAPHORE_ID_5"
.LASF22:
	.string	"HAL_HW_SEMAPHORE_ID_6"
.LASF23:
	.string	"HAL_HW_SEMAPHORE_ID_7"
.LASF24:
	.string	"HAL_HW_SEMAPHORE_ID_8"
.LASF25:
	.string	"HAL_HW_SEMAPHORE_ID_9"
.LASF6:
	.string	"short int"
.LASF50:
	.string	"HAL_HW_SEMAPHORE_STATUS_INVALID_PARAMETER"
.LASF63:
	.string	"syslog_port_check_in_isr_handler"
.LASF61:
	.string	"log_hw_semaphore_give"
.LASF60:
	.string	"file"
.LASF48:
	.string	"HAL_HW_SEMAPHORE_ID_MAX"
.LASF54:
	.string	"hal_hw_semaphore_status_t"
.LASF14:
	.string	"uint8_t"
.LASF36:
	.string	"HAL_HW_SEMAPHORE_ID_20"
.LASF37:
	.string	"HAL_HW_SEMAPHORE_ID_21"
.LASF38:
	.string	"HAL_HW_SEMAPHORE_ID_22"
.LASF19:
	.string	"HAL_HW_SEMAPHORE_ID_3"
.LASF40:
	.string	"HAL_HW_SEMAPHORE_ID_24"
.LASF41:
	.string	"HAL_HW_SEMAPHORE_ID_25"
.LASF42:
	.string	"HAL_HW_SEMAPHORE_ID_26"
.LASF43:
	.string	"HAL_HW_SEMAPHORE_ID_27"
.LASF44:
	.string	"HAL_HW_SEMAPHORE_ID_28"
.LASF45:
	.string	"HAL_HW_SEMAPHORE_ID_29"
.LASF68:
	.string	"exception_get_disable_all_log_flag"
.LASF10:
	.string	"long long int"
.LASF8:
	.string	"long int"
.LASF46:
	.string	"HAL_HW_SEMAPHORE_ID_30"
.LASF30:
	.string	"HAL_HW_SEMAPHORE_ID_14"
.LASF65:
	.string	"ccm_disable_all_log"
.LASF11:
	.string	"long double"
.LASF64:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF5:
	.string	"unsigned char"
.LASF62:
	.string	"log_hw_semaphore_take"
.LASF4:
	.string	"signed char"
.LASF2:
	.string	"long long unsigned int"
.LASF15:
	.string	"uint32_t"
.LASF47:
	.string	"HAL_HW_SEMAPHORE_ID_31"
.LASF3:
	.string	"unsigned int"
.LASF7:
	.string	"short unsigned int"
.LASF67:
	.string	"hal_nvic_query_exception_number"
.LASF12:
	.string	"char"
.LASF13:
	.string	"int32_t"
.LASF55:
	.string	"_Bool"
.LASF56:
	.string	"hw_semaphore_give_special"
.LASF58:
	.string	"hw_sem_id"
.LASF9:
	.string	"long unsigned int"
.LASF51:
	.string	"HAL_HW_SEMAPHORE_STATUS_GIVE_ERROR"
.LASF59:
	.string	"mask"
.LASF57:
	.string	"hw_semaphore_take_special"
.LASF52:
	.string	"HAL_HW_SEMAPHORE_STATUS_TAKE_ERROR"
.LASF49:
	.string	"hal_hw_semaphore_id_t"
.LASF39:
	.string	"HAL_HW_SEMAPHORE_ID_23"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/kernel/service/syslog/src/syslog_port.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
