	.file	"rv_hid_exp_delay_printf.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/middleware/airoha/hid_express/src/rv_hid_exp_delay_printf.c"
	.section	.text.hid_express_dbg_inc_pka_hid_cnt,"ax",@progbits
	.align	1
	.globl	hid_express_dbg_inc_pka_hid_cnt
	.hidden	hid_express_dbg_inc_pka_hid_cnt
	.type	hid_express_dbg_inc_pka_hid_cnt, @function
hid_express_dbg_inc_pka_hid_cnt:
.LFB7:
	.file 1 "/workdir/airoha/common/middleware/airoha/hid_express/src/rv_hid_exp_delay_printf.c"
	.loc 1 55 1
	.cfi_startproc
	.loc 1 56 5
	.loc 1 56 20 is_stmt 0
	lla	a4,dbg
	lw	a5,36(a4)
	addi	a5,a5,1
	sw	a5,36(a4)
	.loc 1 57 1
	ret
	.cfi_endproc
.LFE7:
	.size	hid_express_dbg_inc_pka_hid_cnt, .-hid_express_dbg_inc_pka_hid_cnt
	.section	.text.hid_express_dbg_inc_pka_acl_cnt,"ax",@progbits
	.align	1
	.globl	hid_express_dbg_inc_pka_acl_cnt
	.hidden	hid_express_dbg_inc_pka_acl_cnt
	.type	hid_express_dbg_inc_pka_acl_cnt, @function
hid_express_dbg_inc_pka_acl_cnt:
.LFB8:
	.loc 1 60 1 is_stmt 1
	.cfi_startproc
	.loc 1 61 5
	.loc 1 61 20 is_stmt 0
	lla	a4,dbg
	lw	a5,40(a4)
	addi	a5,a5,1
	sw	a5,40(a4)
	.loc 1 62 1
	ret
	.cfi_endproc
.LFE8:
	.size	hid_express_dbg_inc_pka_acl_cnt, .-hid_express_dbg_inc_pka_acl_cnt
	.section	.text.hid_express_dbg_inc_pka_hid_drop_cnt,"ax",@progbits
	.align	1
	.globl	hid_express_dbg_inc_pka_hid_drop_cnt
	.hidden	hid_express_dbg_inc_pka_hid_drop_cnt
	.type	hid_express_dbg_inc_pka_hid_drop_cnt, @function
hid_express_dbg_inc_pka_hid_drop_cnt:
.LFB9:
	.loc 1 65 1 is_stmt 1
	.cfi_startproc
	.loc 1 66 5
	.loc 1 66 25 is_stmt 0
	lla	a4,dbg
	lw	a5,32(a4)
	addi	a5,a5,1
	sw	a5,32(a4)
	.loc 1 67 1
	ret
	.cfi_endproc
.LFE9:
	.size	hid_express_dbg_inc_pka_hid_drop_cnt, .-hid_express_dbg_inc_pka_hid_drop_cnt
	.section	.text.hid_express_dbg_check,"ax",@progbits
	.align	1
	.globl	hid_express_dbg_check
	.hidden	hid_express_dbg_check
	.type	hid_express_dbg_check, @function
hid_express_dbg_check:
.LFB10:
	.loc 1 70 1 is_stmt 1
	.cfi_startproc
	.loc 1 71 5
	.loc 1 70 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	.cfi_offset 8, -8
	.loc 1 71 18
	lla	s0,dbg
	lw	a5,8(s0)
	.loc 1 70 1
	sw	s1,4(sp)
	sw	ra,12(sp)
	.cfi_offset 9, -12
	.cfi_offset 1, -4
	.loc 1 71 18
	addi	a5,a5,1
	sw	a5,8(s0)
	.loc 1 73 5 is_stmt 1
	.loc 1 74 5
	.loc 1 75 5
	.loc 1 75 29 is_stmt 0
	li	a5,1108672512
	addi	a5,a5,512
	lw	s1,24(a5)
.LVL0:
	.loc 1 76 5 is_stmt 1
	lw	a0,16(s0)
	mv	a2,sp
	mv	a1,s1
	call	hal_gpt_get_duration_count
.LVL1:
	.loc 1 78 5
	.loc 1 78 7 is_stmt 0
	lw	a4,0(sp)
	li	a5,999424
	addi	a5,a5,514
	bleu	a4,a5,.L4
	.loc 1 79 9 is_stmt 1
	.loc 1 79 28 is_stmt 0
	li	a5,1
	sh	a5,50(s0)
	.loc 1 80 9 is_stmt 1
	.loc 1 80 29 is_stmt 0
	lw	a5,0(s0)
	.loc 1 101 23
	sw	s1,16(s0)
	.loc 1 103 11
	li	a4,92
	.loc 1 80 29
	sh	a5,48(s0)
	.loc 1 81 9 is_stmt 1
	.loc 1 81 30 is_stmt 0
	lw	a5,8(s0)
	sh	a5,62(s0)
	.loc 1 82 9 is_stmt 1
	.loc 1 82 30 is_stmt 0
	lw	a5,4(s0)
	sh	a5,52(s0)
	.loc 1 83 9 is_stmt 1
	.loc 1 83 33 is_stmt 0
	lw	a5,12(s0)
	sh	a5,54(s0)
	.loc 1 84 9 is_stmt 1
	.loc 1 84 31 is_stmt 0
	lw	a5,20(s0)
	sh	a5,64(s0)
	.loc 1 85 9 is_stmt 1
	.loc 1 85 35 is_stmt 0
	lw	a5,24(s0)
	sh	a5,66(s0)
	.loc 1 86 9 is_stmt 1
	.loc 1 86 34 is_stmt 0
	lw	a5,28(s0)
	sh	a5,68(s0)
	.loc 1 87 9 is_stmt 1
	.loc 1 87 37 is_stmt 0
	lw	a5,32(s0)
	sh	a5,56(s0)
	.loc 1 88 9 is_stmt 1
	.loc 1 88 32 is_stmt 0
	lw	a5,36(s0)
	sh	a5,58(s0)
	.loc 1 89 9 is_stmt 1
	.loc 1 89 32 is_stmt 0
	lw	a5,40(s0)
	sh	a5,60(s0)
	.loc 1 91 9 is_stmt 1
	.loc 1 91 22 is_stmt 0
	sw	zero,dbg,a5
	.loc 1 92 9 is_stmt 1
	.loc 1 92 23 is_stmt 0
	sw	zero,dbg+8,a5
	.loc 1 93 9 is_stmt 1
	.loc 1 93 23 is_stmt 0
	sw	zero,dbg+4,a5
	.loc 1 94 9 is_stmt 1
	.loc 1 94 26 is_stmt 0
	sw	zero,dbg+12,a5
	.loc 1 95 9 is_stmt 1
	.loc 1 95 24 is_stmt 0
	sw	zero,dbg+20,a5
	.loc 1 96 9 is_stmt 1
	.loc 1 96 28 is_stmt 0
	sw	zero,dbg+24,a5
	.loc 1 97 9 is_stmt 1
	.loc 1 97 27 is_stmt 0
	sw	zero,dbg+28,a5
	.loc 1 98 9 is_stmt 1
	.loc 1 98 30 is_stmt 0
	sw	zero,dbg+32,a5
	.loc 1 99 9 is_stmt 1
	.loc 1 99 25 is_stmt 0
	sw	zero,dbg+36,a5
	.loc 1 100 9 is_stmt 1
	.loc 1 100 25 is_stmt 0
	sw	zero,dbg+40,a5
	.loc 1 101 9 is_stmt 1
	.loc 1 103 9
	.loc 1 103 24 is_stmt 0
	lw	a5,hid_flags
	andi	a5,a5,92
	.loc 1 103 11
	bne	a5,a4,.L4
	.loc 1 104 13 is_stmt 1
	call	hid_express_bt_debug_check
.LVL2:
.L4:
	.loc 1 108 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
.LVL3:
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE10:
	.size	hid_express_dbg_check, .-hid_express_dbg_check
	.section	.text.rv_hid_exp_delay_printf,"ax",@progbits
	.align	1
	.globl	rv_hid_exp_delay_printf
	.hidden	rv_hid_exp_delay_printf
	.type	rv_hid_exp_delay_printf, @function
rv_hid_exp_delay_printf:
.LFB11:
	.loc 1 111 1 is_stmt 1
	.cfi_startproc
	.loc 1 115 5
	.loc 1 111 1 is_stmt 0
	addi	sp,sp,-36
	.cfi_def_cfa_offset 36
	sw	s0,28(sp)
	.cfi_offset 8, -8
	.loc 1 115 11
	lla	s0,dbg
	.loc 1 115 7
	lhu	a5,50(s0)
	.loc 1 111 1
	sw	ra,32(sp)
	sw	s1,24(sp)
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 115 7
	beq	a5,zero,.L9
	.loc 1 117 9 is_stmt 1
.LBB2:
	.loc 1 117 14
	.loc 1 117 67
	.loc 1 117 362
	lbu	a5,hid_ctrl
	sw	a5,20(sp)
	lhu	a5,62(s0)
	li	a3,8
	lla	a2,msg_id_string.3
	sw	a5,16(sp)
	lhu	a5,54(s0)
	li	a1,1
	lla	a0,log_control_block_rv_exp
	sw	a5,12(sp)
	lhu	a5,66(s0)
.LBE2:
	.loc 1 136 24 is_stmt 0
	lla	s1,hid_flags
.LBB3:
	.loc 1 117 362
	sw	a5,8(sp)
	lhu	a5,52(s0)
	sw	a5,4(sp)
	lhu	a5,64(s0)
	sw	a5,0(sp)
	lhu	a5,48(s0)
	lhu	a4,68(s0)
	call	print_module_msgid_log
.LVL4:
.LBE3:
	.loc 1 117 12 is_stmt 1 discriminator 1
	.loc 1 129 8
.LBB4:
	.loc 1 129 13
	.loc 1 129 66
	.loc 1 129 257
	lhu	a5,60(s0)
	li	a3,3
	lla	a2,msg_id_string.2
	sw	a5,0(sp)
	lhu	a5,58(s0)
	lhu	a4,56(s0)
	li	a1,1
	lla	a0,log_control_block_rv_exp
	call	print_module_msgid_log
.LVL5:
.LBE4:
	.loc 1 129 11 discriminator 1
	.loc 1 136 9
	.loc 1 136 24 is_stmt 0
	lw	a5,0(s1)
	.loc 1 136 11
	li	a4,144
	.loc 1 136 24
	andi	a5,a5,144
	.loc 1 136 11
	bne	a5,a4,.L12
	.loc 1 137 13 is_stmt 1
	.loc 1 137 15 is_stmt 0
	lhu	a4,64(s0)
	lhu	a5,62(s0)
	bne	a4,a5,.L13
	.loc 1 138 17 is_stmt 1
	.loc 1 138 38 is_stmt 0
	lw	a5,44(s0)
	.loc 1 139 19
	li	a4,2
	.loc 1 138 38
	addi	a5,a5,1
	sw	a5,44(s0)
	.loc 1 139 17 is_stmt 1
	.loc 1 139 19 is_stmt 0
	bne	a5,a4,.L12
	.loc 1 141 21 is_stmt 1
.LBB5:
	.loc 1 141 79 discriminator 1
	.loc 1 141 198 discriminator 1
	.loc 1 141 356 discriminator 1
	li	a2,141
	lla	a1,file.0
	lla	a0,exp.1
	call	light_assert
.LVL6:
.L12:
.LBE5:
	.loc 1 150 9
	.loc 1 150 24 is_stmt 0
	lw	a5,0(s1)
	.loc 1 150 11
	li	a4,92
	.loc 1 150 24
	andi	a5,a5,92
	.loc 1 150 11
	bne	a5,a4,.L15
	.loc 1 151 13 is_stmt 1
	call	hid_express_bt_debug_print
.LVL7:
.L15:
	.loc 1 155 9
	.loc 1 155 28 is_stmt 0
	sh	zero,dbg+50,a5
.L9:
	.loc 1 158 1
	lw	ra,32(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,28(sp)
	.cfi_restore 8
	lw	s1,24(sp)
	.cfi_restore 9
	addi	sp,sp,36
	.cfi_def_cfa_offset 0
	jr	ra
.L13:
	.cfi_restore_state
	.loc 1 145 17 is_stmt 1
	.loc 1 145 39 is_stmt 0
	sw	zero,dbg+44,a5
	j	.L12
	.cfi_endproc
.LFE11:
	.size	rv_hid_exp_delay_printf, .-rv_hid_exp_delay_printf
	.section	.log_string,"a"
	.align	2
	.type	file.0, @object
	.size	file.0, 83
file.0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/rv_hid_exp_delay_printf.c"
	.align	2
	.type	exp.1, @object
	.size	exp.1, 43
exp.1:
	.string	"0 && \"Always buffer full within 2 seconds\""
	.align	2
	.type	msg_id_string.2, @object
	.size	msg_id_string.2, 98
msg_id_string.2:
	.string	"[M:rv_exp C:info F: L: ]: Common HID PKA Status Report: PkaHidDrop = %d, PkaHid = %d, PkaAcl = %d"
	.align	2
	.type	msg_id_string.3, @object
	.size	msg_id_string.3, 202
msg_id_string.3:
	.string	"[M:rv_exp C:info F: L: ]: Common HID Exp Status Report: Key = %d,  Wheel = %d, Nack = %d, Motion Count = %d, Motion Pin Low = %d, Sampling Count = %d, SPI CB in 1s = %d, RR_idx = %d (0=125, 3=1K, 6=8k)"
	.hidden	dbg
	.globl	dbg
	.section	.bss.dbg,"aw",@nobits
	.align	2
	.type	dbg, @object
	.size	dbg, 72
dbg:
	.zero	72
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpt.h"
	.file 4 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 6 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 7 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express.h"
	.file 8 "/workdir/airoha/common/middleware/airoha/hid_express/inc/rv_hid_exp_delay_printf.h"
	.file 9 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 10 "/workdir/airoha/risc-v/kernel/service/exception_handler/inc/exception_handler.h"
	.file 11 "/workdir/airoha/common/middleware/airoha/hid_express/inc/riscv_hid_express_bt_mode.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x857
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x1a
	.4byte	.LASF132
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL2
	.4byte	0
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
	.uleb128 0x1b
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
	.uleb128 0x1c
	.byte	0x4
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x7
	.4byte	0x75
	.uleb128 0x8
	.4byte	0x7c
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x2d
	.uleb128 0x10
	.4byte	0x86
	.uleb128 0x7
	.4byte	0x92
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x3b
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x49
	.uleb128 0x10
	.4byte	0xa8
	.uleb128 0x7
	.4byte	0xb4
	.uleb128 0xb
	.4byte	0x97
	.4byte	0xce
	.uleb128 0xc
	.4byte	0x65
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	0xbe
	.uleb128 0x10
	.4byte	0xce
	.uleb128 0xd
	.byte	0x4
	.byte	0x3
	.byte	0x36
	.4byte	0x114
	.uleb128 0x1d
	.string	"EN"
	.byte	0x3
	.byte	0x37
	.byte	0x1e
	.4byte	0x92
	.byte	0
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x3
	.byte	0x38
	.byte	0x1e
	.4byte	0x92
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x3
	.byte	0x39
	.byte	0x1e
	.4byte	0x92
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x3
	.byte	0x3a
	.byte	0x24
	.4byte	0xd3
	.byte	0x3
	.byte	0
	.uleb128 0x1e
	.byte	0x4
	.byte	0x3
	.byte	0x35
	.byte	0x5
	.4byte	0x134
	.uleb128 0x15
	.4byte	.LASF19
	.byte	0x3b
	.byte	0xb
	.4byte	0xd8
	.uleb128 0x15
	.4byte	.LASF20
	.byte	0x3c
	.byte	0x1b
	.4byte	0xb4
	.byte	0
	.uleb128 0xd
	.byte	0x20
	.byte	0x3
	.byte	0x34
	.4byte	0x1a5
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x3
	.byte	0x3d
	.byte	0x7
	.4byte	0x114
	.byte	0
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x3
	.byte	0x3e
	.byte	0x17
	.4byte	0xb4
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x3
	.byte	0x3f
	.byte	0x17
	.4byte	0xb4
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x3
	.byte	0x40
	.byte	0x17
	.4byte	0xb4
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x3
	.byte	0x41
	.byte	0x1d
	.4byte	0xb9
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x3
	.byte	0x42
	.byte	0x17
	.4byte	0xb4
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x3
	.byte	0x43
	.byte	0x17
	.4byte	0xb4
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x3
	.byte	0x44
	.byte	0x17
	.4byte	0xb4
	.byte	0x1c
	.byte	0
	.uleb128 0x4
	.4byte	.LASF29
	.byte	0x3
	.byte	0x45
	.byte	0x3
	.4byte	0x134
	.uleb128 0xe
	.4byte	0x65
	.byte	0x4
	.byte	0x50
	.byte	0xe
	.4byte	0x1f4
	.uleb128 0x2
	.4byte	.LASF30
	.byte	0
	.uleb128 0x2
	.4byte	.LASF31
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF32
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF33
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF34
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF35
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF36
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF37
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF38
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.byte	0x1
	.byte	0x2
	.4byte	.LASF39
	.uleb128 0xe
	.4byte	0x65
	.byte	0x5
	.byte	0x31
	.byte	0x1
	.4byte	0x238
	.uleb128 0x2
	.4byte	.LASF40
	.byte	0
	.uleb128 0x2
	.4byte	.LASF41
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF42
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF43
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF44
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF45
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF46
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF47
	.byte	0x7
	.byte	0
	.uleb128 0xe
	.4byte	0x65
	.byte	0x6
	.byte	0x3d
	.byte	0xe
	.4byte	0x25d
	.uleb128 0x2
	.4byte	.LASF48
	.byte	0
	.uleb128 0x2
	.4byte	.LASF49
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF50
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF51
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF52
	.byte	0x6
	.byte	0x42
	.byte	0x3
	.4byte	0x238
	.uleb128 0xe
	.4byte	0x65
	.byte	0x6
	.byte	0x45
	.byte	0xe
	.4byte	0x2d0
	.uleb128 0x2
	.4byte	.LASF53
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF54
	.byte	0xf
	.uleb128 0x2
	.4byte	.LASF55
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF56
	.byte	0x11
	.uleb128 0x2
	.4byte	.LASF57
	.byte	0x12
	.uleb128 0x2
	.4byte	.LASF58
	.byte	0x13
	.uleb128 0x2
	.4byte	.LASF59
	.byte	0x1a
	.uleb128 0x2
	.4byte	.LASF60
	.byte	0x2f
	.uleb128 0x2
	.4byte	.LASF61
	.byte	0x30
	.uleb128 0x2
	.4byte	.LASF62
	.byte	0x31
	.uleb128 0x2
	.4byte	.LASF63
	.byte	0x32
	.uleb128 0x2
	.4byte	.LASF64
	.byte	0x33
	.uleb128 0x2
	.4byte	.LASF65
	.byte	0x34
	.uleb128 0x2
	.4byte	.LASF66
	.byte	0x35
	.uleb128 0x2
	.4byte	.LASF67
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF68
	.byte	0x6
	.byte	0x57
	.byte	0x3
	.4byte	0x269
	.uleb128 0x4
	.4byte	.LASF69
	.byte	0x6
	.byte	0x59
	.byte	0x10
	.4byte	0x2e8
	.uleb128 0x8
	.4byte	0x2ed
	.uleb128 0x11
	.4byte	0x30d
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x5e
	.uleb128 0x3
	.4byte	0x25d
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0xa
	.byte	0
	.uleb128 0x4
	.4byte	.LASF70
	.byte	0x6
	.byte	0x5a
	.byte	0x10
	.4byte	0x319
	.uleb128 0x8
	.4byte	0x31e
	.uleb128 0x11
	.4byte	0x348
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x5e
	.uleb128 0x3
	.4byte	0x25d
	.uleb128 0x3
	.4byte	0x348
	.uleb128 0x3
	.4byte	0x5e
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0xa
	.byte	0
	.uleb128 0x8
	.4byte	0x34d
	.uleb128 0x1f
	.uleb128 0x4
	.4byte	.LASF71
	.byte	0x6
	.byte	0x5b
	.byte	0x10
	.4byte	0x35a
	.uleb128 0x8
	.4byte	0x35f
	.uleb128 0x11
	.4byte	0x37a
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x25d
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xa8
	.uleb128 0xa
	.byte	0
	.uleb128 0x4
	.4byte	.LASF72
	.byte	0x6
	.byte	0x5c
	.byte	0x14
	.4byte	0x386
	.uleb128 0x8
	.4byte	0x38b
	.uleb128 0x20
	.4byte	0xa8
	.4byte	0x3ae
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x25d
	.uleb128 0x3
	.4byte	0x2d0
	.uleb128 0x3
	.4byte	0x3ae
	.uleb128 0x3
	.4byte	0x3b3
	.byte	0
	.uleb128 0x8
	.4byte	0x348
	.uleb128 0x8
	.4byte	0xa8
	.uleb128 0xd
	.byte	0x1c
	.byte	0x6
	.byte	0x5e
	.4byte	0x41c
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x6
	.byte	0x5f
	.byte	0x11
	.4byte	0x81
	.byte	0
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x6
	.byte	0x60
	.byte	0xe
	.4byte	0xa8
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x6
	.byte	0x61
	.byte	0xe
	.4byte	0xa8
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x6
	.byte	0x62
	.byte	0xf
	.4byte	0x2dc
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x6
	.byte	0x63
	.byte	0x15
	.4byte	0x30d
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x6
	.byte	0x64
	.byte	0x12
	.4byte	0x37a
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x6
	.byte	0x65
	.byte	0x10
	.4byte	0x34e
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF80
	.byte	0x6
	.byte	0x66
	.byte	0x3
	.4byte	0x3b8
	.uleb128 0xd
	.byte	0x1
	.byte	0x7
	.byte	0x6a
	.4byte	0x43e
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x7
	.byte	0x6c
	.byte	0xd
	.4byte	0x86
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF82
	.byte	0x7
	.byte	0x6d
	.byte	0x2
	.4byte	0x428
	.uleb128 0xf
	.4byte	.LASF83
	.byte	0x7
	.byte	0x6f
	.byte	0x15
	.4byte	0x43e
	.uleb128 0xf
	.4byte	.LASF84
	.byte	0x7
	.byte	0xda
	.byte	0x11
	.4byte	0xa8
	.uleb128 0xd
	.byte	0x48
	.byte	0x8
	.byte	0x2b
	.4byte	0x596
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x8
	.byte	0x2d
	.byte	0xe
	.4byte	0xa8
	.byte	0
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x8
	.byte	0x2e
	.byte	0xe
	.4byte	0xa8
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x8
	.byte	0x2f
	.byte	0xe
	.4byte	0xa8
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x8
	.byte	0x30
	.byte	0xe
	.4byte	0xa8
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x8
	.byte	0x31
	.byte	0xe
	.4byte	0xa8
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x8
	.byte	0x32
	.byte	0xe
	.4byte	0xa8
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x8
	.byte	0x33
	.byte	0xe
	.4byte	0xa8
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x8
	.byte	0x34
	.byte	0xe
	.4byte	0xa8
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x8
	.byte	0x35
	.byte	0xe
	.4byte	0xa8
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x8
	.byte	0x36
	.byte	0xe
	.4byte	0xa8
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x8
	.byte	0x37
	.byte	0xe
	.4byte	0xa8
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x8
	.byte	0x38
	.byte	0xe
	.4byte	0xa8
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x8
	.byte	0x3f
	.byte	0xe
	.4byte	0x9c
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x8
	.byte	0x40
	.byte	0xe
	.4byte	0x9c
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x8
	.byte	0x41
	.byte	0xe
	.4byte	0x9c
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x8
	.byte	0x42
	.byte	0xe
	.4byte	0x9c
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x8
	.byte	0x43
	.byte	0xe
	.4byte	0x9c
	.byte	0x38
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x8
	.byte	0x44
	.byte	0xe
	.4byte	0x9c
	.byte	0x3a
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x8
	.byte	0x45
	.byte	0xe
	.4byte	0x9c
	.byte	0x3c
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x8
	.byte	0x46
	.byte	0xe
	.4byte	0x9c
	.byte	0x3e
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x8
	.byte	0x47
	.byte	0xe
	.4byte	0x9c
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x8
	.byte	0x48
	.byte	0xe
	.4byte	0x9c
	.byte	0x42
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x8
	.byte	0x49
	.byte	0xe
	.4byte	0x9c
	.byte	0x44
	.byte	0
	.uleb128 0x4
	.4byte	.LASF108
	.byte	0x8
	.byte	0x4a
	.byte	0x2
	.4byte	0x462
	.uleb128 0x21
	.string	"dbg"
	.byte	0x8
	.byte	0x4c
	.byte	0x23
	.4byte	0x596
	.uleb128 0x22
	.byte	0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x9
	.2byte	0x153
	.byte	0xe
	.4byte	0x5ee
	.uleb128 0x9
	.4byte	.LASF109
	.sleb128 -7
	.uleb128 0x9
	.4byte	.LASF110
	.sleb128 -6
	.uleb128 0x9
	.4byte	.LASF111
	.sleb128 -5
	.uleb128 0x9
	.4byte	.LASF112
	.sleb128 -4
	.uleb128 0x9
	.4byte	.LASF113
	.sleb128 -3
	.uleb128 0x9
	.4byte	.LASF114
	.sleb128 -2
	.uleb128 0x9
	.4byte	.LASF115
	.sleb128 -1
	.uleb128 0x2
	.4byte	.LASF116
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	.LASF117
	.byte	0x9
	.2byte	0x15c
	.byte	0x3
	.4byte	0x5ae
	.uleb128 0x24
	.4byte	0x5a2
	.byte	0x1
	.byte	0x32
	.byte	0x1c
	.uleb128 0x5
	.byte	0x3
	.4byte	dbg
	.uleb128 0x16
	.4byte	.LASF120
	.byte	0x99
	.4byte	0x615
	.uleb128 0xa
	.byte	0
	.uleb128 0x25
	.4byte	.LASF118
	.byte	0xa
	.byte	0x44
	.byte	0xd
	.4byte	0x631
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0x5e
	.byte	0
	.uleb128 0x26
	.4byte	.LASF119
	.byte	0x6
	.2byte	0x129
	.byte	0xd
	.4byte	0x654
	.uleb128 0x3
	.4byte	0x73
	.uleb128 0x3
	.4byte	0x25d
	.uleb128 0x3
	.4byte	0x81
	.uleb128 0x3
	.4byte	0xa8
	.uleb128 0xa
	.byte	0
	.uleb128 0x16
	.4byte	.LASF121
	.byte	0x98
	.4byte	0x660
	.uleb128 0xa
	.byte	0
	.uleb128 0x27
	.4byte	.LASF133
	.byte	0x9
	.2byte	0x199
	.byte	0x12
	.4byte	0x5ee
	.4byte	0x681
	.uleb128 0x3
	.4byte	0xa8
	.uleb128 0x3
	.4byte	0xa8
	.uleb128 0x3
	.4byte	0x3b3
	.byte	0
	.uleb128 0x17
	.4byte	.LASF125
	.byte	0x6e
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x780
	.uleb128 0x28
	.4byte	.LLRL1
	.4byte	0x6d9
	.uleb128 0xf
	.4byte	.LASF122
	.byte	0x1
	.byte	0x75
	.byte	0x29
	.4byte	0x41c
	.uleb128 0x12
	.4byte	.LASF123
	.byte	0x75
	.byte	0x82
	.4byte	0x790
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.3
	.uleb128 0x13
	.4byte	.LVL4
	.4byte	0x631
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.3
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x38
	.byte	0
	.byte	0
	.uleb128 0x18
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.4byte	0x721
	.uleb128 0xf
	.4byte	.LASF122
	.byte	0x1
	.byte	0x81
	.byte	0x28
	.4byte	0x41c
	.uleb128 0x12
	.4byte	.LASF123
	.byte	0x81
	.byte	0x81
	.4byte	0x7a5
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.2
	.uleb128 0x13
	.4byte	.LVL5
	.4byte	0x631
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x5
	.byte	0x3
	.4byte	msg_id_string.2
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x1
	.byte	0x33
	.byte	0
	.byte	0
	.uleb128 0x18
	.4byte	.LBB5
	.4byte	.LBE5-.LBB5
	.4byte	0x776
	.uleb128 0x29
	.string	"exp"
	.byte	0x1
	.byte	0x8d
	.byte	0x8e
	.4byte	0x7ba
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x2a
	.4byte	.LASF124
	.byte	0x1
	.byte	0x8d
	.2byte	0x105
	.4byte	0x7cf
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0x13
	.4byte	.LVL6
	.4byte	0x615
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	exp.1
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.byte	0x3
	.4byte	file.0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x8
	.byte	0x8d
	.byte	0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL7
	.4byte	0x609
	.byte	0
	.uleb128 0xb
	.4byte	0x7c
	.4byte	0x790
	.uleb128 0xc
	.4byte	0x65
	.byte	0xc9
	.byte	0
	.uleb128 0x7
	.4byte	0x780
	.uleb128 0xb
	.4byte	0x7c
	.4byte	0x7a5
	.uleb128 0xc
	.4byte	0x65
	.byte	0x61
	.byte	0
	.uleb128 0x7
	.4byte	0x795
	.uleb128 0xb
	.4byte	0x7c
	.4byte	0x7ba
	.uleb128 0xc
	.4byte	0x65
	.byte	0x2a
	.byte	0
	.uleb128 0x7
	.4byte	0x7aa
	.uleb128 0xb
	.4byte	0x7c
	.4byte	0x7cf
	.uleb128 0xc
	.4byte	0x65
	.byte	0x52
	.byte	0
	.uleb128 0x7
	.4byte	0x7bf
	.uleb128 0x17
	.4byte	.LASF126
	.byte	0x45
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x82a
	.uleb128 0x2b
	.4byte	.LASF127
	.byte	0x1
	.byte	0x49
	.byte	0xe
	.4byte	0xa8
	.4byte	.LLST0
	.uleb128 0x12
	.4byte	.LASF128
	.byte	0x4a
	.byte	0xe
	.4byte	0xa8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x2c
	.4byte	.LVL1
	.4byte	0x660
	.4byte	0x820
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL2
	.4byte	0x654
	.byte	0
	.uleb128 0x14
	.4byte	.LASF129
	.byte	0x40
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x14
	.4byte	.LASF130
	.byte	0x3b
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x14
	.4byte	.LASF131
	.byte	0x36
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x10
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
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
	.uleb128 0x13
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
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
	.uleb128 0x21
	.sleb128 6
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
	.uleb128 0x15
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
	.sleb128 11
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
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x1b
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
	.uleb128 0x1c
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.uleb128 0x1f
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x28
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x2a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2b
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2c
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
	.byte	0x8
	.4byte	.LVL0
	.uleb128 .LVL3-.LVL0
	.uleb128 0x1
	.byte	0x59
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x3c
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
.LLRL1:
	.byte	0x5
	.4byte	.LBB2
	.byte	0x4
	.uleb128 .LBB2-.LBB2
	.uleb128 .LBE2-.LBB2
	.byte	0x4
	.uleb128 .LBB3-.LBB2
	.uleb128 .LBE3-.LBB2
	.byte	0
.LLRL2:
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF83:
	.string	"hid_ctrl"
.LASF30:
	.string	"DBG_PIN_SPI_CB"
.LASF59:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF99:
	.string	"sensor_ok_4print"
.LASF104:
	.string	"total_cnt_4print"
.LASF61:
	.string	"LOG_TYPE_HCI_DATA"
.LASF97:
	.string	"wheel_ok_4print"
.LASF78:
	.string	"tlv_dump_handle"
.LASF47:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF94:
	.string	"pka_hid_cnt"
.LASF89:
	.string	"timestamp"
.LASF58:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF122:
	.string	"log_control_block_rv_exp"
.LASF8:
	.string	"long long int"
.LASF2:
	.string	"signed char"
.LASF126:
	.string	"hid_express_dbg_check"
.LASF21:
	.string	"GPT_CON_UNION"
.LASF9:
	.string	"long long unsigned int"
.LASF27:
	.string	"GPT_COUNT"
.LASF41:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF75:
	.string	"print_level"
.LASF6:
	.string	"long int"
.LASF69:
	.string	"f_print_t"
.LASF95:
	.string	"pka_acl_cnt"
.LASF93:
	.string	"pka_hid_drop_cnt"
.LASF60:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF14:
	.string	"uint16_t"
.LASF70:
	.string	"f_dump_buffer_t"
.LASF125:
	.string	"rv_hid_exp_delay_printf"
.LASF23:
	.string	"GPT_CLK"
.LASF119:
	.string	"print_module_msgid_log"
.LASF46:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF22:
	.string	"GPT_CLR"
.LASF64:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF88:
	.string	"sampling_cnt"
.LASF118:
	.string	"light_assert"
.LASF111:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF92:
	.string	"valid_key_cnt"
.LASF40:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF109:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF74:
	.string	"log_switch"
.LASF103:
	.string	"pka_acl_cnt_4print"
.LASF57:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF63:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF7:
	.string	"long unsigned int"
.LASF76:
	.string	"print_handle"
.LASF131:
	.string	"hid_express_dbg_inc_pka_hid_cnt"
.LASF115:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF132:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF5:
	.string	"short unsigned int"
.LASF51:
	.string	"PRINT_LEVEL_ERROR"
.LASF62:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF98:
	.string	"waiting_4print"
.LASF100:
	.string	"sampling_cnt_4print"
.LASF96:
	.string	"all_buff_full_cnt"
.LASF101:
	.string	"pka_hid_drop_cnt_4print"
.LASF113:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF105:
	.string	"nack_count_4print"
.LASF102:
	.string	"pka_hid_cnt_4print"
.LASF90:
	.string	"nack_count"
.LASF50:
	.string	"PRINT_LEVEL_WARNING"
.LASF114:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF68:
	.string	"log_type_t"
.LASF32:
	.string	"DBG_PIN_NACK"
.LASF130:
	.string	"hid_express_dbg_inc_pka_acl_cnt"
.LASF44:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF81:
	.string	"rr_idx"
.LASF110:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF112:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF82:
	.string	"T_hid_ctrl_S"
.LASF37:
	.string	"DBG_PIN_USB_TX"
.LASF106:
	.string	"motion_pin_low_4print"
.LASF128:
	.string	"time_delta"
.LASF54:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF123:
	.string	"msg_id_string"
.LASF49:
	.string	"PRINT_LEVEL_INFO"
.LASF80:
	.string	"log_control_block_t"
.LASF25:
	.string	"GPT_IRQ_STA"
.LASF116:
	.string	"HAL_GPT_STATUS_OK"
.LASF108:
	.string	"T_SENSOR_DATA_STATISTICS_S"
.LASF107:
	.string	"valid_key_cnt_4print"
.LASF39:
	.string	"_Bool"
.LASF20:
	.string	"GPT_CON"
.LASF120:
	.string	"hid_express_bt_debug_print"
.LASF26:
	.string	"GPT_IRQ_ACK"
.LASF52:
	.string	"print_level_t"
.LASF4:
	.string	"short int"
.LASF124:
	.string	"file"
.LASF127:
	.string	"current_gpt_free_count"
.LASF18:
	.string	"RESERVED"
.LASF66:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF28:
	.string	"GPT_COMPARE"
.LASF42:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF67:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF29:
	.string	"GPT_REGISTER_T"
.LASF24:
	.string	"GPT_IRQ_EN"
.LASF15:
	.string	"uint32_t"
.LASF31:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF77:
	.string	"dump_handle"
.LASF11:
	.string	"long double"
.LASF12:
	.string	"char"
.LASF10:
	.string	"unsigned int"
.LASF79:
	.string	"msg_id_handle"
.LASF16:
	.string	"MODE"
.LASF133:
	.string	"hal_gpt_get_duration_count"
.LASF87:
	.string	"total_cnt"
.LASF17:
	.string	"SW_CG"
.LASF3:
	.string	"unsigned char"
.LASF121:
	.string	"hid_express_bt_debug_check"
.LASF129:
	.string	"hid_express_dbg_inc_pka_hid_drop_cnt"
.LASF65:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF43:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF48:
	.string	"PRINT_LEVEL_DEBUG"
.LASF73:
	.string	"module_name"
.LASF85:
	.string	"wheel_ok"
.LASF72:
	.string	"f_tlv_dump_t"
.LASF53:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF13:
	.string	"uint8_t"
.LASF19:
	.string	"GPT_CON_CELLS"
.LASF33:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF34:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF38:
	.string	"DBG_PIN_MAX"
.LASF55:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF71:
	.string	"f_msg_id_t"
.LASF36:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF91:
	.string	"motion_pin_cnt"
.LASF45:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF56:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF35:
	.string	"DBG_PIN_USB_SOF"
.LASF86:
	.string	"sensor_ok"
.LASF84:
	.string	"hid_flags"
.LASF117:
	.string	"hal_gpt_status_t"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/middleware/airoha/hid_express/src/rv_hid_exp_delay_printf.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
