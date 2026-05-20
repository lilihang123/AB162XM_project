	.file	"riscv_motion_sensor.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_motion_sensor.c"
	.section	.text.riscv_motion_sensor_data_get,"ax",@progbits
	.align	1
	.globl	riscv_motion_sensor_data_get
	.hidden	riscv_motion_sensor_data_get
	.type	riscv_motion_sensor_data_get, @function
riscv_motion_sensor_data_get:
.LFB15:
	.file 1 "/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_motion_sensor.c"
	.loc 1 74 1
	.cfi_startproc
.LVL0:
	.loc 1 75 5
	.loc 1 74 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	s1,4(sp)
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	mv	s0,a1
	mv	s1,a0
	.loc 1 76 15
	addi	a1,sp,2
.LVL1:
	mv	a0,sp
.LVL2:
	.loc 1 74 1
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 75 13
	sh	zero,0(sp)
	.loc 1 75 20
	sh	zero,2(sp)
	.loc 1 76 5 is_stmt 1
	.loc 1 76 15 is_stmt 0
	call	mouse_sensor_get_data
.LVL3:
	.loc 1 78 5 is_stmt 1
	.loc 1 78 17 is_stmt 0
	sw	zero,0(s1)
	.loc 1 79 5 is_stmt 1
	.loc 1 79 17 is_stmt 0
	sw	zero,0(s0)
	.loc 1 81 5 is_stmt 1
	.loc 1 81 8 is_stmt 0
	bne	a0,zero,.L1
	.loc 1 85 10 is_stmt 1
	.loc 1 85 14 is_stmt 0
	lh	a4,0(sp)
	.loc 1 85 16 discriminator 1
	lh	a5,2(sp)
	or	a3,a4,a5
	beq	a3,zero,.L1
	.loc 1 87 9 is_stmt 1
	.loc 1 87 21 is_stmt 0
	sw	a4,0(s1)
	.loc 1 88 9 is_stmt 1
	.loc 1 88 21 is_stmt 0
	sw	a5,0(s0)
	.loc 1 91 5 is_stmt 1
.L1:
	.loc 1 92 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL4:
	lw	s1,4(sp)
	.cfi_restore 9
.LVL5:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE15:
	.size	riscv_motion_sensor_data_get, .-riscv_motion_sensor_data_get
	.section	.text.riscv_motion_sensor_init,"ax",@progbits
	.align	1
	.globl	riscv_motion_sensor_init
	.hidden	riscv_motion_sensor_init
	.type	riscv_motion_sensor_init, @function
riscv_motion_sensor_init:
.LFB16:
	.loc 1 95 1 is_stmt 1
	.cfi_startproc
	.loc 1 97 5
	.loc 1 98 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE16:
	.size	riscv_motion_sensor_init, .-riscv_motion_sensor_init
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/mouse_sensor.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x143
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x8
	.4byte	.LASF18
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL2
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x1
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x1
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x1
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x1
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x1
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x1
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x9
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x1
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x25
	.byte	0x13
	.4byte	0x42
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x28
	.byte	0x12
	.4byte	0x50
	.uleb128 0x1
	.byte	0x1
	.byte	0x2
	.4byte	.LASF15
	.uleb128 0xa
	.4byte	.LASF19
	.byte	0x3
	.byte	0x30
	.byte	0x5
	.4byte	0x65
	.4byte	0xb2
	.uleb128 0x4
	.4byte	0xb2
	.uleb128 0x4
	.4byte	0xb2
	.byte	0
	.uleb128 0x5
	.4byte	0x7a
	.uleb128 0xb
	.4byte	.LASF20
	.byte	0x1
	.byte	0x5e
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xc
	.4byte	.LASF21
	.byte	0x1
	.byte	0x49
	.byte	0x5
	.4byte	0x65
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x141
	.uleb128 0x6
	.4byte	.LASF16
	.byte	0x49
	.byte	0x2c
	.4byte	0x141
	.4byte	.LLST0
	.uleb128 0x6
	.4byte	.LASF17
	.byte	0x49
	.byte	0x42
	.4byte	0x141
	.4byte	.LLST1
	.uleb128 0x2
	.string	"x"
	.byte	0x4b
	.byte	0xd
	.4byte	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x2
	.string	"y"
	.byte	0x4b
	.byte	0x14
	.4byte	0x7a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -14
	.uleb128 0x2
	.string	"ret"
	.byte	0x4c
	.byte	0x9
	.4byte	0x65
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0xd
	.4byte	.LVL3
	.4byte	0x97
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -14
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	0x85
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
	.uleb128 0x34
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
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
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xd
	.uleb128 0x48
	.byte	0x1
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
	.uleb128 .LVL5-.LVL0
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL5-.LVL0
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
	.uleb128 .LVL1-.LVL0
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL1-.LVL0
	.uleb128 .LVL4-.LVL0
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL4-.LVL0
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
	.4byte	0x24
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
	.byte	0x7
	.4byte	.LFB15
	.uleb128 .LFE15-.LFB15
	.byte	0x7
	.4byte	.LFB16
	.uleb128 .LFE16-.LFB16
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF10:
	.string	"long long int"
.LASF3:
	.string	"unsigned int"
.LASF5:
	.string	"unsigned char"
.LASF13:
	.string	"int16_t"
.LASF9:
	.string	"long unsigned int"
.LASF19:
	.string	"mouse_sensor_get_data"
.LASF20:
	.string	"riscv_motion_sensor_init"
.LASF2:
	.string	"long long unsigned int"
.LASF12:
	.string	"char"
.LASF21:
	.string	"riscv_motion_sensor_data_get"
.LASF8:
	.string	"long int"
.LASF16:
	.string	"outgoing_x"
.LASF17:
	.string	"outgoing_y"
.LASF15:
	.string	"_Bool"
.LASF7:
	.string	"short unsigned int"
.LASF4:
	.string	"signed char"
.LASF11:
	.string	"long double"
.LASF6:
	.string	"short int"
.LASF14:
	.string	"int32_t"
.LASF18:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/projects/applications/mouse_ref_design/src/app/riscv_motion_sensor.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
