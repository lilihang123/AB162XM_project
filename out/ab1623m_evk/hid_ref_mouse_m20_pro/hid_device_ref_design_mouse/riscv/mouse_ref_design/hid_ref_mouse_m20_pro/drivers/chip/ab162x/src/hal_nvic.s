	.file	"hal_nvic.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_nvic.c"
	.section	.text.isrC_main,"ax",@progbits
	.align	1
	.globl	isrC_main
	.hidden	isrC_main
	.type	isrC_main, @function
isrC_main:
.LFB3:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_nvic.c"
	.loc 1 79 1
	.cfi_startproc
	.loc 1 80 5
	.loc 1 81 5
	.loc 1 87 5
 #APP
# 87 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_nvic.c" 1
	csrr a5,mcause
# 0 "" 2
.LVL0:
	.loc 1 88 5
	.loc 1 89 5
	.loc 1 92 5
	.loc 1 92 8 is_stmt 0
 #NO_APP
	bge	a5,zero,.L1
	.loc 1 89 13
	slli	a5,a5,1
.LVL1:
	srli	a0,a5,1
	.loc 1 100 9 is_stmt 1
	.loc 1 100 41 is_stmt 0
	lla	a4,nvic_function_table
	slli	a5,a5,1
	add	a5,a4,a5
	lw	a5,0(a5)
	.loc 1 100 12
	beq	a5,zero,.L1
	.loc 1 102 13 is_stmt 1
	jr	a5
.LVL2:
.L1:
	.loc 1 115 1 is_stmt 0
	ret
	.cfi_endproc
.LFE3:
	.size	isrC_main, .-isrC_main
	.section	.text.hal_nvic_register_isr_handler,"ax",@progbits
	.align	1
	.globl	hal_nvic_register_isr_handler
	.hidden	hal_nvic_register_isr_handler
	.type	hal_nvic_register_isr_handler, @function
hal_nvic_register_isr_handler:
.LFB4:
	.loc 1 119 1 is_stmt 1
	.cfi_startproc
.LVL3:
	.loc 1 120 5
	.loc 1 120 51 is_stmt 0
	slli	a0,a0,2
.LVL4:
	lla	a5,nvic_function_table
	add	a5,a5,a0
	sw	a1,0(a5)
	.loc 1 121 1
	ret
	.cfi_endproc
.LFE4:
	.size	hal_nvic_register_isr_handler, .-hal_nvic_register_isr_handler
	.section	.text.hal_nvic_enable_irq,"ax",@progbits
	.align	1
	.globl	hal_nvic_enable_irq
	.hidden	hal_nvic_enable_irq
	.type	hal_nvic_enable_irq, @function
hal_nvic_enable_irq:
.LFB5:
	.loc 1 124 1 is_stmt 1
	.cfi_startproc
.LVL5:
	.loc 1 125 5
	.loc 1 127 5
	.loc 1 125 30 is_stmt 0
	li	a5,1
	sll	a5,a5,a0
	.loc 1 127 5
 #APP
# 127 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_nvic.c" 1
	csrrs x0, mie, a5
# 0 "" 2
	.loc 1 128 1
 #NO_APP
	ret
	.cfi_endproc
.LFE5:
	.size	hal_nvic_enable_irq, .-hal_nvic_enable_irq
	.section	.text.hal_nvic_disable_irq,"ax",@progbits
	.align	1
	.globl	hal_nvic_disable_irq
	.hidden	hal_nvic_disable_irq
	.type	hal_nvic_disable_irq, @function
hal_nvic_disable_irq:
.LFB6:
	.loc 1 131 1 is_stmt 1
	.cfi_startproc
.LVL6:
	.loc 1 132 5
	.loc 1 134 5
	.loc 1 132 30 is_stmt 0
	li	a5,1
	sll	a5,a5,a0
	.loc 1 134 5
 #APP
# 134 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_nvic.c" 1
	csrrc x0, mie, a5
# 0 "" 2
	.loc 1 135 1
 #NO_APP
	ret
	.cfi_endproc
.LFE6:
	.size	hal_nvic_disable_irq, .-hal_nvic_disable_irq
	.section	.text.hal_nvic_save_and_set_interrupt_mask,"ax",@progbits
	.align	1
	.globl	hal_nvic_save_and_set_interrupt_mask
	.hidden	hal_nvic_save_and_set_interrupt_mask
	.type	hal_nvic_save_and_set_interrupt_mask, @function
hal_nvic_save_and_set_interrupt_mask:
.LFB7:
	.loc 1 138 1 is_stmt 1
	.cfi_startproc
.LVL7:
	.loc 1 139 5
	.loc 1 141 5
 #APP
# 141 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_nvic.c" 1
	csrrci a5, mstatus, 0x8
# 0 "" 2
.LVL8:
	.loc 1 142 5
	.loc 1 142 11 is_stmt 0
 #NO_APP
	sw	a5,0(a0)
	.loc 1 143 1
	ret
	.cfi_endproc
.LFE7:
	.size	hal_nvic_save_and_set_interrupt_mask, .-hal_nvic_save_and_set_interrupt_mask
	.section	.text.hal_nvic_restore_interrupt_mask,"ax",@progbits
	.align	1
	.globl	hal_nvic_restore_interrupt_mask
	.hidden	hal_nvic_restore_interrupt_mask
	.type	hal_nvic_restore_interrupt_mask, @function
hal_nvic_restore_interrupt_mask:
.LFB8:
	.loc 1 146 1 is_stmt 1
	.cfi_startproc
.LVL9:
	.loc 1 147 5
	.loc 1 148 5
	.loc 1 147 10 is_stmt 0
	andi	a0,a0,8
.LVL10:
	.loc 1 148 5
 #APP
# 148 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_nvic.c" 1
	csrrs x0, mstatus, a0
# 0 "" 2
	.loc 1 149 1
 #NO_APP
	ret
	.cfi_endproc
.LFE8:
	.size	hal_nvic_restore_interrupt_mask, .-hal_nvic_restore_interrupt_mask
	.section	.text.hal_nvic_query_exception_number,"ax",@progbits
	.align	1
	.globl	hal_nvic_query_exception_number
	.hidden	hal_nvic_query_exception_number
	.type	hal_nvic_query_exception_number, @function
hal_nvic_query_exception_number:
.LFB9:
	.loc 1 158 1 is_stmt 1
	.cfi_startproc
	.loc 1 159 5
	.loc 1 159 46 is_stmt 0
	lw	a0,exception_interrupt_nesting_flag
	.loc 1 160 1
	snez	a0,a0
	ret
	.cfi_endproc
.LFE9:
	.size	hal_nvic_query_exception_number, .-hal_nvic_query_exception_number
	.hidden	irq_nest_count
	.globl	irq_nest_count
	.section	.sbss.irq_nest_count,"aw",@nobits
	.align	2
	.type	irq_nest_count, @object
	.size	irq_nest_count, 4
irq_nest_count:
	.zero	4
	.hidden	nvic_function_table
	.globl	nvic_function_table
	.section	.bss.nvic_function_table,"aw",@nobits
	.align	2
	.type	nvic_function_table, @object
	.size	nvic_function_table, 128
nvic_function_table:
	.zero	128
	.hidden	irq_info
	.globl	irq_info
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"SW_IRQn"
	.align	2
.LC1:
	.string	"LED"
	.align	2
.LC2:
	.string	"QDEC"
	.align	2
.LC3:
	.string	"KEYSCAN"
	.align	2
.LC4:
	.string	"UART"
	.align	2
.LC5:
	.string	"SPI_MST1"
	.align	2
.LC6:
	.string	"RTC"
	.align	2
.LC7:
	.string	"GPT"
	.align	2
.LC8:
	.string	"UART_DMA"
	.align	2
.LC9:
	.string	"PMU"
	.align	2
.LC10:
	.string	"MCU_DMA"
	.align	2
.LC11:
	.string	"EINT"
	.align	2
.LC12:
	.string	"I3C0"
	.align	2
.LC13:
	.string	"I3C0_DMA"
	.align	2
.LC14:
	.string	"SPI_MST0"
	.align	2
.LC15:
	.string	"IRQ_GEN"
	.align	2
.LC16:
	.string	"USB"
	.align	2
.LC17:
	.string	"BT"
	.section	.rodata.irq_info,"a"
	.align	2
	.type	irq_info, @object
	.size	irq_info, 186
irq_info:
	.zero	18
	.byte	3
	.byte	3
	.4byte	.LC0
	.zero	18
	.byte	7
	.byte	7
	.4byte	.LC1
	.zero	18
	.byte	11
	.byte	11
	.4byte	.LC2
	.zero	24
	.byte	16
	.byte	16
	.4byte	.LC3
	.byte	17
	.byte	17
	.4byte	.LC4
	.byte	18
	.byte	18
	.4byte	.LC5
	.byte	19
	.byte	19
	.4byte	.LC6
	.byte	20
	.byte	20
	.4byte	.LC7
	.byte	21
	.byte	21
	.4byte	.LC8
	.byte	22
	.byte	22
	.4byte	.LC9
	.byte	23
	.byte	23
	.4byte	.LC10
	.byte	24
	.byte	24
	.4byte	.LC11
	.byte	25
	.byte	25
	.4byte	.LC12
	.byte	26
	.byte	26
	.4byte	.LC13
	.byte	27
	.byte	27
	.4byte	.LC14
	.byte	28
	.byte	28
	.4byte	.LC15
	.byte	29
	.byte	29
	.4byte	.LC16
	.byte	30
	.byte	30
	.4byte	.LC17
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x362
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x12
	.4byte	.LASF60
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
	.uleb128 0x13
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
	.uleb128 0x8
	.4byte	0x7a
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x2
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x3b
	.uleb128 0x3
	.4byte	.LASF15
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x14
	.4byte	.LASF61
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x3
	.2byte	0x128
	.byte	0x11
	.4byte	0x12e
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x1f
	.byte	0
	.uleb128 0xa
	.4byte	.LASF35
	.2byte	0x13c
	.byte	0x7
	.4byte	0xa8
	.uleb128 0xa
	.4byte	.LASF36
	.2byte	0x13e
	.byte	0x17
	.4byte	0x12e
	.uleb128 0x3
	.4byte	.LASF37
	.byte	0x4
	.byte	0x2e
	.byte	0x10
	.4byte	0x152
	.uleb128 0x8
	.4byte	0x157
	.uleb128 0x15
	.4byte	0x162
	.uleb128 0x16
	.4byte	0x13a
	.byte	0
	.uleb128 0xb
	.byte	0x6
	.byte	0x4
	.byte	0x30
	.4byte	0x192
	.uleb128 0x5
	.4byte	.LASF38
	.byte	0x4
	.byte	0x31
	.byte	0xd
	.4byte	0x90
	.byte	0
	.uleb128 0x5
	.4byte	.LASF39
	.byte	0x4
	.byte	0x32
	.byte	0xd
	.4byte	0x90
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF40
	.byte	0x4
	.byte	0x33
	.byte	0x11
	.4byte	0x7f
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF41
	.byte	0x4
	.byte	0x34
	.byte	0x1b
	.4byte	0x162
	.uleb128 0x7
	.4byte	0x192
	.uleb128 0xc
	.4byte	0x19e
	.4byte	0x1b3
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x1e
	.byte	0
	.uleb128 0x7
	.4byte	0x1a3
	.uleb128 0xe
	.4byte	.LASF44
	.byte	0x4
	.byte	0x36
	.byte	0x19
	.4byte	0x1b3
	.uleb128 0x17
	.4byte	0x1b8
	.byte	0x1
	.byte	0x2d
	.byte	0x12
	.uleb128 0x5
	.byte	0x3
	.4byte	irq_info
	.uleb128 0xb
	.byte	0x4
	.byte	0x1
	.byte	0x43
	.4byte	0x1e8
	.uleb128 0x5
	.4byte	.LASF42
	.byte	0x1
	.byte	0x44
	.byte	0xc
	.4byte	0x152
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF43
	.byte	0x1
	.byte	0x45
	.byte	0x3
	.4byte	0x1d2
	.uleb128 0xc
	.4byte	0x1e8
	.4byte	0x204
	.uleb128 0xd
	.4byte	0x2d
	.byte	0x1f
	.byte	0
	.uleb128 0xf
	.4byte	.LASF45
	.byte	0x49
	.byte	0x11
	.4byte	0x1f4
	.uleb128 0x5
	.byte	0x3
	.4byte	nvic_function_table
	.uleb128 0xf
	.4byte	.LASF46
	.byte	0x4a
	.byte	0xa
	.4byte	0x9c
	.uleb128 0x5
	.byte	0x3
	.4byte	irq_nest_count
	.uleb128 0xe
	.4byte	.LASF47
	.byte	0x1
	.byte	0x4b
	.byte	0x11
	.4byte	0x9c
	.uleb128 0x18
	.4byte	.LASF62
	.byte	0x1
	.byte	0x9d
	.byte	0x9
	.4byte	0x84
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x4
	.4byte	.LASF48
	.byte	0x91
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x26c
	.uleb128 0x10
	.4byte	.LASF50
	.byte	0x91
	.byte	0x2f
	.4byte	0x9c
	.4byte	.LLST3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF49
	.byte	0x89
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x29a
	.uleb128 0x6
	.4byte	.LASF50
	.byte	0x89
	.byte	0x35
	.4byte	0x29a
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.4byte	.LASF53
	.byte	0x8b
	.4byte	0x9c
	.uleb128 0x1
	.byte	0x5f
	.byte	0
	.uleb128 0x8
	.4byte	0x9c
	.uleb128 0x4
	.4byte	.LASF51
	.byte	0x82
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2d1
	.uleb128 0x6
	.4byte	.LASF52
	.byte	0x82
	.byte	0x2a
	.4byte	0x13a
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.4byte	.LASF54
	.byte	0x84
	.4byte	0x9c
	.uleb128 0x5
	.byte	0x31
	.byte	0x7a
	.sleb128 0
	.byte	0x24
	.byte	0x9f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF55
	.byte	0x7b
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x303
	.uleb128 0x6
	.4byte	.LASF52
	.byte	0x7b
	.byte	0x29
	.4byte	0x13a
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.4byte	.LASF54
	.byte	0x7d
	.4byte	0x9c
	.uleb128 0x5
	.byte	0x31
	.byte	0x7a
	.sleb128 0
	.byte	0x24
	.byte	0x9f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF56
	.byte	0x76
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x334
	.uleb128 0x10
	.4byte	.LASF52
	.byte	0x76
	.byte	0x33
	.4byte	0x13a
	.4byte	.LLST2
	.uleb128 0x6
	.4byte	.LASF57
	.byte	0x76
	.byte	0x4e
	.4byte	0x146
	.uleb128 0x1
	.byte	0x5b
	.byte	0
	.uleb128 0x19
	.4byte	.LASF63
	.byte	0x1
	.byte	0x4e
	.byte	0x6
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x11
	.4byte	.LASF58
	.byte	0x50
	.byte	0x14
	.4byte	0x13a
	.4byte	.LLST0
	.uleb128 0x11
	.4byte	.LASF59
	.byte	0x51
	.byte	0xe
	.4byte	0x9c
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
	.uleb128 0x18
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0x3f
	.uleb128 0x19
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
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.4byte	.LVL9
	.byte	0x4
	.uleb128 .LVL9-.LVL9
	.uleb128 .LVL9-.LVL9
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL9-.LVL9
	.uleb128 .LVL10-.LVL9
	.uleb128 0x5
	.byte	0x7a
	.sleb128 0
	.byte	0x38
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL10-.LVL9
	.uleb128 .LFE8-.LVL9
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL4-.LVL3
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL4-.LVL3
	.uleb128 .LFE4-.LVL3
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
	.byte	0x8
	.4byte	.LVL0
	.uleb128 .LVL1-.LVL0
	.uleb128 0x9
	.byte	0x7f
	.sleb128 0
	.byte	0xc
	.4byte	0x7fffffff
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST1:
	.byte	0x8
	.4byte	.LVL0
	.uleb128 .LVL1-.LVL0
	.uleb128 0x8
	.byte	0x7f
	.sleb128 0
	.byte	0x40
	.byte	0x4b
	.byte	0x24
	.byte	0x1f
	.byte	0x1a
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
.LASF60:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF30:
	.string	"SPI_MST0_IRQn"
.LASF45:
	.string	"nvic_function_table"
.LASF24:
	.string	"UART_DMA_IRQn"
.LASF43:
	.string	"nvic_function_t"
.LASF7:
	.string	"short unsigned int"
.LASF23:
	.string	"GPT_IRQn"
.LASF62:
	.string	"hal_nvic_query_exception_number"
.LASF40:
	.string	"name"
.LASF63:
	.string	"isrC_main"
.LASF42:
	.string	"nvic_callback"
.LASF56:
	.string	"hal_nvic_register_isr_handler"
.LASF55:
	.string	"hal_nvic_enable_irq"
.LASF28:
	.string	"I3C0_IRQn"
.LASF5:
	.string	"unsigned char"
.LASF35:
	.string	"IRQn_Type"
.LASF2:
	.string	"long long unsigned int"
.LASF18:
	.string	"QDEC_IRQn"
.LASF53:
	.string	"mstatus_temp"
.LASF29:
	.string	"I3C0_DMA_IRQn"
.LASF33:
	.string	"BT_IRQn"
.LASF57:
	.string	"callback"
.LASF15:
	.string	"uint32_t"
.LASF36:
	.string	"hal_nvic_irq_t"
.LASF39:
	.string	"priority"
.LASF22:
	.string	"RTC_IRQn"
.LASF51:
	.string	"hal_nvic_disable_irq"
.LASF19:
	.string	"KEYSCAN_IRQn"
.LASF34:
	.string	"IRQ_NUMBER_MAX"
.LASF32:
	.string	"USB_IRQn"
.LASF48:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF17:
	.string	"LED_IRQn"
.LASF47:
	.string	"exception_interrupt_nesting_flag"
.LASF9:
	.string	"long unsigned int"
.LASF54:
	.string	"temp_value"
.LASF12:
	.string	"char"
.LASF14:
	.string	"uint8_t"
.LASF49:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF21:
	.string	"SPI_MST1_IRQn"
.LASF41:
	.string	"IRQ_INFO_t"
.LASF44:
	.string	"irq_info"
.LASF58:
	.string	"irq_num"
.LASF52:
	.string	"irq_number"
.LASF13:
	.string	"int32_t"
.LASF10:
	.string	"long long int"
.LASF50:
	.string	"mask"
.LASF59:
	.string	"is_interrupt"
.LASF38:
	.string	"index"
.LASF3:
	.string	"unsigned int"
.LASF16:
	.string	"SW_IRQn"
.LASF6:
	.string	"short int"
.LASF25:
	.string	"PMU_IRQn"
.LASF8:
	.string	"long int"
.LASF31:
	.string	"IRQ_GEN_IRQn"
.LASF11:
	.string	"long double"
.LASF26:
	.string	"MCU_DMA_IRQn"
.LASF4:
	.string	"signed char"
.LASF20:
	.string	"UART_IRQn"
.LASF46:
	.string	"irq_nest_count"
.LASF37:
	.string	"hal_nvic_isr_t"
.LASF27:
	.string	"EINT_IRQn"
.LASF61:
	.string	"IRQn"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_nvic.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
