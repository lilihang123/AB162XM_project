	.file	"hal_comparator.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_comparator.c"
	.section	.text.hal_comparator_analog_power_on,"ax",@progbits
	.align	1
	.globl	hal_comparator_analog_power_on
	.hidden	hal_comparator_analog_power_on
	.type	hal_comparator_analog_power_on, @function
hal_comparator_analog_power_on:
.LFB4:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_comparator.c"
	.loc 1 103 1
	.cfi_startproc
	.loc 1 105 5
	.loc 1 105 42 is_stmt 0
	li	a4,17960960
	li	a5,1108377600
	addi	a4,a4,-1709
	sw	a4,8(a5)
	.loc 1 106 1
	ret
	.cfi_endproc
.LFE4:
	.size	hal_comparator_analog_power_on, .-hal_comparator_analog_power_on
	.section	.text.hal_comparator_analog_power_off,"ax",@progbits
	.align	1
	.globl	hal_comparator_analog_power_off
	.hidden	hal_comparator_analog_power_off
	.type	hal_comparator_analog_power_off, @function
hal_comparator_analog_power_off:
.LFB5:
	.loc 1 109 1 is_stmt 1
	.cfi_startproc
	.loc 1 111 5
	.loc 1 111 42 is_stmt 0
	li	a5,1108377600
	li	a4,17956864
	sw	a4,8(a5)
	.loc 1 112 1
	ret
	.cfi_endproc
.LFE5:
	.size	hal_comparator_analog_power_off, .-hal_comparator_analog_power_off
	.section	.text.hal_comparator_analog_reset,"ax",@progbits
	.align	1
	.globl	hal_comparator_analog_reset
	.hidden	hal_comparator_analog_reset
	.type	hal_comparator_analog_reset, @function
hal_comparator_analog_reset:
.LFB6:
	.loc 1 115 1 is_stmt 1
	.cfi_startproc
	.loc 1 117 5
	.loc 1 117 42 is_stmt 0
	li	a5,1108377600
	li	a4,18022400
	sw	a4,8(a5)
	.loc 1 119 5 is_stmt 1
	.loc 1 119 42 is_stmt 0
	li	a4,18153472
	sw	a4,8(a5)
	.loc 1 121 5 is_stmt 1
	.loc 1 121 42 is_stmt 0
	li	a4,18219008
	sw	a4,8(a5)
	.loc 1 123 5 is_stmt 1
	.loc 1 123 42 is_stmt 0
	li	a4,18284544
	sw	a4,8(a5)
	.loc 1 125 5 is_stmt 1
	.loc 1 125 42 is_stmt 0
	li	a4,18350080
	sw	a4,8(a5)
	.loc 1 128 5 is_stmt 1
	.loc 1 128 42 is_stmt 0
	li	a5,1107820544
	sw	zero,96(a5)
	.loc 1 130 5 is_stmt 1
	.loc 1 130 49 is_stmt 0
	li	a5,1107820544
	sw	zero,100(a5)
	.loc 1 132 5 is_stmt 1
	.loc 1 132 49 is_stmt 0
	li	a5,1107820544
	sw	zero,104(a5)
	.loc 1 134 5 is_stmt 1
	.loc 1 134 49 is_stmt 0
	li	a5,1107820544
	sw	zero,108(a5)
	.loc 1 135 1
	ret
	.cfi_endproc
.LFE6:
	.size	hal_comparator_analog_reset, .-hal_comparator_analog_reset
	.section	.text.hal_comparator_analog_int_ref_on,"ax",@progbits
	.align	1
	.globl	hal_comparator_analog_int_ref_on
	.hidden	hal_comparator_analog_int_ref_on
	.type	hal_comparator_analog_int_ref_on, @function
hal_comparator_analog_int_ref_on:
.LFB7:
	.loc 1 138 1 is_stmt 1
	.cfi_startproc
.LVL0:
	.loc 1 140 5
	.loc 1 140 14 is_stmt 0
	slli	a0,a0,2
.LVL1:
	lla	a5,internal_ref_cfg_value
	add	a5,a5,a0
	lw	a4,0(a5)
.LVL2:
	.loc 1 141 5 is_stmt 1
	.loc 1 141 42 is_stmt 0
	li	a5,1108377600
	sw	a4,8(a5)
	.loc 1 142 1
	ret
	.cfi_endproc
.LFE7:
	.size	hal_comparator_analog_int_ref_on, .-hal_comparator_analog_int_ref_on
	.section	.text.hal_comparator_analog_comp1_init,"ax",@progbits
	.align	1
	.globl	hal_comparator_analog_comp1_init
	.hidden	hal_comparator_analog_comp1_init
	.type	hal_comparator_analog_comp1_init, @function
hal_comparator_analog_comp1_init:
.LFB8:
	.loc 1 146 1 is_stmt 1
	.cfi_startproc
.LVL3:
	.loc 1 148 5
	.loc 1 148 63 is_stmt 0
	lw	a2,4(a0)
	.loc 1 148 14
	lla	a5,comp_1_mode_cfg_value
.LBB8:
	.loc 1 165 60
	li	a1,18350080
.LBE8:
	.loc 1 148 14
	slli	a4,a2,2
	add	a5,a5,a4
	lw	a5,0(a5)
.LVL4:
	.loc 1 149 5 is_stmt 1
	.loc 1 149 42 is_stmt 0
	li	a4,1108377600
	addi	a4,a4,8
	sw	a5,0(a4)
	.loc 1 150 5 is_stmt 1
	.loc 1 150 28 is_stmt 0
	sw	a5,g_comp1_mode_reg_value,a3
	.loc 1 152 5 is_stmt 1
.LVL5:
	.loc 1 153 5
	.loc 1 154 5
	.loc 1 155 5
	.loc 1 158 5
	.loc 1 154 14 is_stmt 0
	lw	a3,20(a0)
	.loc 1 152 14
	lw	a5,8(a0)
.LVL6:
	.loc 1 154 14
	slli	a3,a3,12
	.loc 1 152 14
	slli	a5,a5,8
.LBB9:
	.loc 1 160 91
	or	a5,a5,a3
	lw	a3,12(a0)
	or	a5,a5,a3
.LBE9:
	.loc 1 155 14
	lw	a3,24(a0)
	slli	a3,a3,14
.LBB10:
	.loc 1 160 91
	or	a5,a5,a3
	.loc 1 165 79
	lbu	a3,28(a0)
	.loc 1 165 60
	or	a3,a3,a1
.LBE10:
	.loc 1 158 7
	li	a1,5
	bleu	a2,a1,.L6
.LBB11:
	.loc 1 160 9 is_stmt 1
	.loc 1 160 18 is_stmt 0
	li	a2,18219008
.LVL7:
	addi	a2,a2,112
	or	a5,a5,a2
.LVL8:
	.loc 1 161 9 is_stmt 1
	.loc 1 161 46 is_stmt 0
	sw	a5,0(a4)
	.loc 1 163 9 is_stmt 1
.LVL9:
	.loc 1 164 9
	.loc 1 164 46 is_stmt 0
	li	a5,18284544
.LVL10:
.L8:
.LBE11:
.LBB12:
	.loc 1 173 46
	sw	a5,0(a4)
	.loc 1 174 9 is_stmt 1
	.loc 1 174 46 is_stmt 0
	sw	a3,0(a4)
.LBE12:
	.loc 1 176 1
	ret
.LVL11:
.L6:
.LBB13:
	.loc 1 168 9 is_stmt 1
	.loc 1 168 18 is_stmt 0
	li	a2,18219008
.LVL12:
	or	a5,a5,a2
.LVL13:
	.loc 1 169 9 is_stmt 1
	.loc 1 169 46 is_stmt 0
	sw	a5,0(a4)
	.loc 1 171 9 is_stmt 1
.LVL14:
	.loc 1 172 9
	.loc 1 173 9
	.loc 1 173 86 is_stmt 0
	lbu	a5,29(a0)
.LVL15:
	.loc 1 173 63
	li	a2,18284544
	.loc 1 173 86
	slli	a5,a5,8
	.loc 1 173 63
	or	a5,a5,a2
	j	.L8
.LBE13:
	.cfi_endproc
.LFE8:
	.size	hal_comparator_analog_comp1_init, .-hal_comparator_analog_comp1_init
	.section	.text.comparator_para_check,"ax",@progbits
	.align	1
	.globl	comparator_para_check
	.hidden	comparator_para_check
	.type	comparator_para_check, @function
comparator_para_check:
.LFB9:
	.loc 1 179 1 is_stmt 1
	.cfi_startproc
.LVL16:
	.loc 1 180 5
	.loc 1 180 7 is_stmt 0
	lw	a3,0(a0)
	li	a4,2
	.loc 1 179 1
	mv	a5,a0
	.loc 1 180 7
	bgtu	a3,a4,.L11
	.loc 1 180 46 discriminator 1
	lw	a3,4(a0)
	li	a4,12
	.loc 1 185 16
	li	a0,-2
.LVL17:
	.loc 1 180 46 discriminator 1
	bgtu	a3,a4,.L9
	.loc 1 181 46
	lw	a3,8(a5)
	li	a4,11
	bgtu	a3,a4,.L9
	.loc 1 182 51
	lw	a3,16(a5)
	li	a4,16
	bgtu	a3,a4,.L9
	.loc 1 188 5 is_stmt 1
	.loc 1 188 7 is_stmt 0
	lbu	a3,28(a5)
	li	a4,63
	bgtu	a3,a4,.L9
	.loc 1 188 46 discriminator 1
	lbu	a5,29(a5)
.LVL18:
	bgtu	a5,a4,.L9
	.loc 1 193 12
	li	a0,0
	ret
.LVL19:
.L11:
	.loc 1 185 16
	li	a0,-2
.LVL20:
.L9:
	.loc 1 194 1
	ret
	.cfi_endproc
.LFE9:
	.size	comparator_para_check, .-comparator_para_check
	.section	.text.hal_comparator_analog_comp2_init,"ax",@progbits
	.align	1
	.globl	hal_comparator_analog_comp2_init
	.hidden	hal_comparator_analog_comp2_init
	.type	hal_comparator_analog_comp2_init, @function
hal_comparator_analog_comp2_init:
.LFB10:
	.loc 1 197 1 is_stmt 1
	.cfi_startproc
.LVL21:
	.loc 1 199 5
	.loc 1 199 63 is_stmt 0
	lw	t2,4(a0)
	.loc 1 199 14
	lla	a5,comp_2_mode_cfg_value
	.loc 1 206 42
	li	a3,1107820544
	.loc 1 199 14
	slli	a4,t2,2
	add	a5,a5,a4
	lw	a2,0(a5)
.LVL22:
	.loc 1 200 5 is_stmt 1
	.loc 1 200 72 is_stmt 0
	lw	a4,12(a0)
	.loc 1 203 14
	lw	t0,24(a0)
	.loc 1 201 14
	lw	a1,8(a0)
	.loc 1 202 39
	lw	a5,20(a0)
	.loc 1 206 42
	sw	a2,96(a3)
	.loc 1 207 28
	sw	a2,g_comp2_mode_reg_value,a3
	.loc 1 209 7
	li	a3,5
	li	a2,1107820544
.LVL23:
.LBB14:
	.loc 1 215 40
	lbu	t1,28(a0)
.LBE14:
	.loc 1 200 72
	slli	a4,a4,4
.LVL24:
	.loc 1 201 5 is_stmt 1
	.loc 1 202 5
	.loc 1 203 5
	.loc 1 203 14 is_stmt 0
	slli	t0,t0,8
.LVL25:
	.loc 1 204 5 is_stmt 1
	.loc 1 206 5
	.loc 1 207 5
	.loc 1 209 5
	addi	a2,a2,100
	.loc 1 209 7 is_stmt 0
	bleu	t2,a3,.L18
.LBB15:
	.loc 1 211 9 is_stmt 1
.LBE15:
	.loc 1 200 14 is_stmt 0
	li	a3,12288
	addi	a3,a3,256
	.loc 1 202 14
	slli	a5,a5,4
.LVL26:
	.loc 1 200 14
	or	a3,a4,a3
	.loc 1 204 14
	or	a5,a5,t0
.LVL27:
.LBB16:
	.loc 1 211 54
	sw	a3,0(a2)
	.loc 1 213 9 is_stmt 1
.LBE16:
	.loc 1 204 14 is_stmt 0
	or	a5,a5,a1
.LBB17:
	.loc 1 213 54
	li	a4,1107820544
.LVL28:
	sw	a5,104(a4)
	.loc 1 215 9 is_stmt 1
.LVL29:
	.loc 1 216 9
	.loc 1 215 18 is_stmt 0
	slli	t1,t1,8
	.loc 1 216 54
	li	a5,1107820544
	sw	t1,108(a5)
.LVL30:
.LBE17:
	ret
.LVL31:
.L18:
.LBB18:
	.loc 1 219 9 is_stmt 1
	.loc 1 219 26 is_stmt 0
	ori	a4,a4,1
.LVL32:
	.loc 1 220 9 is_stmt 1
	.loc 1 220 54 is_stmt 0
	sw	a4,0(a2)
	.loc 1 222 9 is_stmt 1
.LVL33:
	.loc 1 223 9
	.loc 1 223 18 is_stmt 0
	or	a5,a1,t0
.LVL34:
	.loc 1 224 9 is_stmt 1
	.loc 1 224 54 is_stmt 0
	li	a4,1107820544
.LVL35:
	sw	a5,104(a4)
.LVL36:
	.loc 1 227 9 is_stmt 1
	lhu	a4,28(a0)
	slli	a5,a4,8
.LVL37:
	srli	a4,a4,8
	or	a5,a5,a4
	slli	a5,a5,16
	srli	a5,a5,16
.LVL38:
	.loc 1 228 9
	.loc 1 229 9
	.loc 1 229 54 is_stmt 0
	li	a4,1107820544
.LVL39:
	sw	a5,108(a4)
.LVL40:
.LBE18:
	.loc 1 231 1
	ret
	.cfi_endproc
.LFE10:
	.size	hal_comparator_analog_comp2_init, .-hal_comparator_analog_comp2_init
	.section	.text.hal_comparator_comp2_init,"ax",@progbits
	.align	1
	.globl	hal_comparator_comp2_init
	.hidden	hal_comparator_comp2_init
	.type	hal_comparator_comp2_init, @function
hal_comparator_comp2_init:
.LFB11:
	.loc 1 234 1 is_stmt 1
	.cfi_startproc
.LVL41:
	.loc 1 235 5
.LBB19:
.LBB20:
	.loc 1 105 5
.LBE20:
.LBE19:
	.loc 1 234 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
.LBB23:
.LBB21:
	.loc 1 105 42
	li	a4,17960960
	.cfi_offset 8, -8
.LBE21:
.LBE23:
	.loc 1 234 1
	mv	s0,a0
	.loc 1 236 5
	lw	a0,16(a0)
.LVL42:
	.loc 1 234 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
.LBB24:
.LBB22:
	.loc 1 105 42
	li	a5,1108377600
	addi	a4,a4,-1709
	sw	a4,8(a5)
.LBE22:
.LBE24:
	.loc 1 236 5 is_stmt 1
	call	hal_comparator_analog_int_ref_on
.LVL43:
	.loc 1 237 5
	mv	a0,s0
	call	hal_comparator_analog_comp2_init
.LVL44:
	.loc 1 238 5
	.loc 1 239 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL45:
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE11:
	.size	hal_comparator_comp2_init, .-hal_comparator_comp2_init
	.section	.text.hal_comparator_comp1_init,"ax",@progbits
	.align	1
	.globl	hal_comparator_comp1_init
	.hidden	hal_comparator_comp1_init
	.type	hal_comparator_comp1_init, @function
hal_comparator_comp1_init:
.LFB12:
	.loc 1 242 1 is_stmt 1
	.cfi_startproc
.LVL46:
	.loc 1 243 5
.LBB25:
.LBB26:
	.loc 1 105 5
.LBE26:
.LBE25:
	.loc 1 242 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
.LBB29:
.LBB27:
	.loc 1 105 42
	li	a4,17960960
	.cfi_offset 8, -8
.LBE27:
.LBE29:
	.loc 1 242 1
	mv	s0,a0
	.loc 1 244 5
	lw	a0,16(a0)
.LVL47:
	.loc 1 242 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
.LBB30:
.LBB28:
	.loc 1 105 42
	li	a5,1108377600
	addi	a4,a4,-1709
	sw	a4,8(a5)
.LBE28:
.LBE30:
	.loc 1 244 5 is_stmt 1
	call	hal_comparator_analog_int_ref_on
.LVL48:
	.loc 1 245 5
	mv	a0,s0
	call	hal_comparator_analog_comp1_init
.LVL49:
	.loc 1 246 5
	.loc 1 247 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
.LVL50:
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE12:
	.size	hal_comparator_comp1_init, .-hal_comparator_comp1_init
	.section	.text.hal_comparator_deinit,"ax",@progbits
	.align	1
	.globl	hal_comparator_deinit
	.hidden	hal_comparator_deinit
	.type	hal_comparator_deinit, @function
hal_comparator_deinit:
.LFB13:
	.loc 1 250 1 is_stmt 1
	.cfi_startproc
	.loc 1 251 5
	.loc 1 250 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 251 5
	call	hal_comparator_analog_reset
.LVL51:
	.loc 1 252 5 is_stmt 1
.LBB31:
.LBB32:
	.loc 1 111 5
.LBE32:
.LBE31:
	.loc 1 253 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
.LBB34:
.LBB33:
	.loc 1 111 42
	li	a5,1108377600
	li	a4,17956864
	sw	a4,8(a5)
.LBE33:
.LBE34:
	.loc 1 253 1
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE13:
	.size	hal_comparator_deinit, .-hal_comparator_deinit
	.section	.text.hal_comp1_enable,"ax",@progbits
	.align	1
	.globl	hal_comp1_enable
	.hidden	hal_comp1_enable
	.type	hal_comp1_enable, @function
hal_comp1_enable:
.LFB14:
	.loc 1 256 1 is_stmt 1
	.cfi_startproc
	.loc 1 257 5
	.loc 1 257 14 is_stmt 0
	lw	a4,g_comp1_mode_reg_value
	ori	a4,a4,1
.LVL52:
	.loc 1 258 5 is_stmt 1
	.loc 1 258 42 is_stmt 0
	li	a5,1108377600
	sw	a4,8(a5)
	.loc 1 259 1
	ret
	.cfi_endproc
.LFE14:
	.size	hal_comp1_enable, .-hal_comp1_enable
	.section	.text.hal_comp1_disable,"ax",@progbits
	.align	1
	.globl	hal_comp1_disable
	.hidden	hal_comp1_disable
	.type	hal_comp1_disable, @function
hal_comp1_disable:
.LFB15:
	.loc 1 262 1 is_stmt 1
	.cfi_startproc
	.loc 1 263 5
	.loc 1 263 14 is_stmt 0
	lw	a4,g_comp1_mode_reg_value
	andi	a4,a4,-2
.LVL53:
	.loc 1 264 5 is_stmt 1
	.loc 1 264 42 is_stmt 0
	li	a5,1108377600
	sw	a4,8(a5)
	.loc 1 265 1
	ret
	.cfi_endproc
.LFE15:
	.size	hal_comp1_disable, .-hal_comp1_disable
	.section	.text.hal_comp2_enable,"ax",@progbits
	.align	1
	.globl	hal_comp2_enable
	.hidden	hal_comp2_enable
	.type	hal_comp2_enable, @function
hal_comp2_enable:
.LFB16:
	.loc 1 268 1 is_stmt 1
	.cfi_startproc
	.loc 1 269 5
	.loc 1 269 14 is_stmt 0
	lw	a4,g_comp2_mode_reg_value
	ori	a4,a4,1
.LVL54:
	.loc 1 270 5 is_stmt 1
	.loc 1 270 42 is_stmt 0
	li	a5,1107820544
	sw	a4,96(a5)
	.loc 1 271 1
	ret
	.cfi_endproc
.LFE16:
	.size	hal_comp2_enable, .-hal_comp2_enable
	.section	.text.hal_comp2_disable,"ax",@progbits
	.align	1
	.globl	hal_comp2_disable
	.hidden	hal_comp2_disable
	.type	hal_comp2_disable, @function
hal_comp2_disable:
.LFB17:
	.loc 1 274 1 is_stmt 1
	.cfi_startproc
	.loc 1 275 5
	.loc 1 275 14 is_stmt 0
	lw	a4,g_comp2_mode_reg_value
	andi	a4,a4,-2
.LVL55:
	.loc 1 276 5 is_stmt 1
	.loc 1 276 42 is_stmt 0
	li	a5,1107820544
	sw	a4,96(a5)
	.loc 1 277 1
	ret
	.cfi_endproc
.LFE17:
	.size	hal_comp2_disable, .-hal_comp2_disable
	.hidden	g_comp2_mode_reg_value
	.globl	g_comp2_mode_reg_value
	.section	.sbss.g_comp2_mode_reg_value,"aw",@nobits
	.align	2
	.type	g_comp2_mode_reg_value, @object
	.size	g_comp2_mode_reg_value, 4
g_comp2_mode_reg_value:
	.zero	4
	.hidden	g_comp1_mode_reg_value
	.globl	g_comp1_mode_reg_value
	.section	.sbss.g_comp1_mode_reg_value,"aw",@nobits
	.align	2
	.type	g_comp1_mode_reg_value, @object
	.size	g_comp1_mode_reg_value, 4
g_comp1_mode_reg_value:
	.zero	4
	.hidden	g_comp_lp_callabck
	.globl	g_comp_lp_callabck
	.section	.sbss.g_comp_lp_callabck,"aw",@nobits
	.align	2
	.type	g_comp_lp_callabck, @object
	.size	g_comp_lp_callabck, 4
g_comp_lp_callabck:
	.zero	4
	.hidden	g_comp2_callabck
	.globl	g_comp2_callabck
	.section	.sbss.g_comp2_callabck,"aw",@nobits
	.align	2
	.type	g_comp2_callabck, @object
	.size	g_comp2_callabck, 4
g_comp2_callabck:
	.zero	4
	.hidden	g_comp1_callabck
	.globl	g_comp1_callabck
	.section	.sbss.g_comp1_callabck,"aw",@nobits
	.align	2
	.type	g_comp1_callabck, @object
	.size	g_comp1_callabck, 4
g_comp1_callabck:
	.zero	4
	.section	.rodata.comp_2_mode_cfg_value,"a"
	.align	2
	.type	comp_2_mode_cfg_value, @object
	.size	comp_2_mode_cfg_value, 48
comp_2_mode_cfg_value:
	.word	4099
	.word	4611
	.word	5635
	.word	4097
	.word	4609
	.word	5633
	.word	4099
	.word	4611
	.word	5635
	.word	4097
	.word	4609
	.word	5633
	.section	.rodata.comp_1_mode_cfg_value,"a"
	.align	2
	.type	comp_1_mode_cfg_value, @object
	.size	comp_1_mode_cfg_value, 48
comp_1_mode_cfg_value:
	.word	18165763
	.word	18166275
	.word	18167299
	.word	18165761
	.word	18166273
	.word	18167297
	.word	18157571
	.word	18158083
	.word	18159107
	.word	18157569
	.word	18158081
	.word	18159105
	.section	.rodata.internal_ref_cfg_value,"a"
	.align	2
	.type	internal_ref_cfg_value, @object
	.size	internal_ref_cfg_value, 64
internal_ref_cfg_value:
	.word	18022407
	.word	18022423
	.word	18022439
	.word	18022455
	.word	18022471
	.word	18022487
	.word	18022503
	.word	18022519
	.word	18022535
	.word	18022551
	.word	18022567
	.word	18022583
	.word	18022599
	.word	18022615
	.word	18022631
	.word	18022647
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_comparator.h"
	.file 5 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x981
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x1b
	.4byte	.LASF206
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL24
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
	.uleb128 0x1c
	.4byte	.LASF207
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x5
	.2byte	0x128
	.byte	0x12
	.4byte	0xba
	.uleb128 0x1
	.4byte	.LASF4
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF5
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF6
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF7
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF8
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF9
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF10
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF11
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF12
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x1f
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF23
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF24
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF25
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF26
	.uleb128 0x5
	.4byte	.LASF29
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0xe2
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF27
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF28
	.uleb128 0x5
	.4byte	.LASF30
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x101
	.uleb128 0xc
	.4byte	0xf0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF31
	.uleb128 0x1d
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x1e
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x3
	.2byte	0x407
	.byte	0xe
	.4byte	0x275
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x38
	.byte	0
	.uleb128 0x2
	.byte	0x10
	.byte	0x4
	.4byte	.LASF89
	.uleb128 0x11
	.4byte	0x281
	.uleb128 0x1f
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF90
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF91
	.uleb128 0x7
	.byte	0x5
	.4byte	0x108
	.byte	0x4c
	.4byte	0x2ae
	.uleb128 0x12
	.4byte	.LASF92
	.sleb128 -2
	.uleb128 0x12
	.4byte	.LASF93
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF95
	.byte	0x4
	.byte	0x50
	.byte	0x3
	.4byte	0x290
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x53
	.4byte	0x32c
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
	.byte	0
	.uleb128 0x5
	.4byte	.LASF113
	.byte	0x4
	.byte	0x65
	.byte	0x3
	.4byte	0x2ba
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x68
	.4byte	0x398
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0xc
	.byte	0
	.uleb128 0x5
	.4byte	.LASF128
	.byte	0x4
	.byte	0x78
	.byte	0x3
	.4byte	0x338
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x7b
	.4byte	0x3f8
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0xb
	.byte	0
	.uleb128 0x5
	.4byte	.LASF141
	.byte	0x4
	.byte	0x88
	.byte	0x2
	.4byte	0x3a4
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x8b
	.4byte	0x428
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF146
	.byte	0x4
	.byte	0x90
	.byte	0x2
	.4byte	0x404
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x93
	.4byte	0x458
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF151
	.byte	0x4
	.byte	0x98
	.byte	0x2
	.4byte	0x434
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x9b
	.4byte	0x488
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.4byte	.LASF156
	.byte	0x4
	.byte	0xa0
	.byte	0x2
	.4byte	0x464
	.uleb128 0x20
	.byte	0x20
	.byte	0x4
	.byte	0xa2
	.byte	0x9
	.4byte	0x50a
	.uleb128 0x6
	.4byte	.LASF157
	.byte	0xa4
	.byte	0x15
	.4byte	0x488
	.byte	0
	.uleb128 0x6
	.4byte	.LASF158
	.byte	0xa5
	.byte	0x19
	.4byte	0x398
	.byte	0x4
	.uleb128 0x6
	.4byte	.LASF159
	.byte	0xa6
	.byte	0x19
	.4byte	0x3f8
	.byte	0x8
	.uleb128 0x6
	.4byte	.LASF160
	.byte	0xa7
	.byte	0x19
	.4byte	0x3f8
	.byte	0xc
	.uleb128 0x6
	.4byte	.LASF161
	.byte	0xa8
	.byte	0x24
	.4byte	0x32c
	.byte	0x10
	.uleb128 0x6
	.4byte	.LASF162
	.byte	0xa9
	.byte	0x1b
	.4byte	0x428
	.byte	0x14
	.uleb128 0x6
	.4byte	.LASF163
	.byte	0xaa
	.byte	0x22
	.4byte	0x458
	.byte	0x18
	.uleb128 0x6
	.4byte	.LASF164
	.byte	0xab
	.byte	0xd
	.4byte	0xd6
	.byte	0x1c
	.uleb128 0x6
	.4byte	.LASF165
	.byte	0xac
	.byte	0xd
	.4byte	0xd6
	.byte	0x1d
	.byte	0
	.uleb128 0x5
	.4byte	.LASF166
	.byte	0x4
	.byte	0xad
	.byte	0x3
	.4byte	0x494
	.uleb128 0x5
	.4byte	.LASF167
	.byte	0x4
	.byte	0xaf
	.byte	0x10
	.4byte	0x27c
	.uleb128 0x13
	.4byte	0xfc
	.4byte	0x532
	.uleb128 0x14
	.4byte	0x2d
	.byte	0xf
	.byte	0
	.uleb128 0xc
	.4byte	0x522
	.uleb128 0x3
	.4byte	.LASF168
	.byte	0x2f
	.byte	0x17
	.4byte	0x532
	.uleb128 0x5
	.byte	0x3
	.4byte	internal_ref_cfg_value
	.uleb128 0x13
	.4byte	0xfc
	.4byte	0x558
	.uleb128 0x14
	.4byte	0x2d
	.byte	0xb
	.byte	0
	.uleb128 0xc
	.4byte	0x548
	.uleb128 0x3
	.4byte	.LASF169
	.byte	0x42
	.byte	0x17
	.4byte	0x558
	.uleb128 0x5
	.byte	0x3
	.4byte	comp_1_mode_cfg_value
	.uleb128 0x3
	.4byte	.LASF170
	.byte	0x51
	.byte	0x17
	.4byte	0x558
	.uleb128 0x5
	.byte	0x3
	.4byte	comp_2_mode_cfg_value
	.uleb128 0x9
	.4byte	.LASF171
	.byte	0x61
	.byte	0x1b
	.4byte	0x516
	.uleb128 0x5
	.byte	0x3
	.4byte	g_comp1_callabck
	.uleb128 0x9
	.4byte	.LASF172
	.byte	0x62
	.byte	0x1b
	.4byte	0x516
	.uleb128 0x5
	.byte	0x3
	.4byte	g_comp2_callabck
	.uleb128 0x9
	.4byte	.LASF173
	.byte	0x63
	.byte	0x1b
	.4byte	0x516
	.uleb128 0x5
	.byte	0x3
	.4byte	g_comp_lp_callabck
	.uleb128 0x9
	.4byte	.LASF174
	.byte	0x90
	.byte	0xa
	.4byte	0xf0
	.uleb128 0x5
	.byte	0x3
	.4byte	g_comp1_mode_reg_value
	.uleb128 0x9
	.4byte	.LASF175
	.byte	0xc3
	.byte	0xa
	.4byte	0xf0
	.uleb128 0x5
	.byte	0x3
	.4byte	g_comp2_mode_reg_value
	.uleb128 0xd
	.4byte	.LASF177
	.2byte	0x111
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5f7
	.uleb128 0xa
	.4byte	.LASF176
	.2byte	0x113
	.4byte	0xf0
	.uleb128 0x1
	.byte	0x5e
	.byte	0
	.uleb128 0xd
	.4byte	.LASF178
	.2byte	0x10b
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x61a
	.uleb128 0xa
	.4byte	.LASF179
	.2byte	0x10d
	.4byte	0xf0
	.uleb128 0x1
	.byte	0x5e
	.byte	0
	.uleb128 0xd
	.4byte	.LASF180
	.2byte	0x105
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x63d
	.uleb128 0xa
	.4byte	.LASF176
	.2byte	0x107
	.4byte	0xf0
	.uleb128 0x1
	.byte	0x5e
	.byte	0
	.uleb128 0xb
	.4byte	.LASF181
	.byte	0xff
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x65f
	.uleb128 0xa
	.4byte	.LASF179
	.2byte	0x101
	.4byte	0xf0
	.uleb128 0x1
	.byte	0x5e
	.byte	0
	.uleb128 0x21
	.4byte	.LASF208
	.byte	0x1
	.byte	0xf9
	.byte	0x6
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x68d
	.uleb128 0xe
	.4byte	0x95a
	.4byte	.LBB31
	.4byte	.LLRL23
	.byte	0xfc
	.uleb128 0xf
	.4byte	.LVL51
	.4byte	0x948
	.byte	0
	.uleb128 0x10
	.4byte	.LASF184
	.byte	0xf1
	.4byte	0x2ae
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x6eb
	.uleb128 0x8
	.4byte	.LASF182
	.byte	0xf1
	.byte	0x49
	.4byte	0x6eb
	.4byte	.LLST20
	.uleb128 0x8
	.4byte	.LASF183
	.byte	0xf1
	.byte	0x6d
	.4byte	0x516
	.4byte	.LLST21
	.uleb128 0xe
	.4byte	0x960
	.4byte	.LBB25
	.4byte	.LLRL22
	.byte	0xf3
	.uleb128 0xf
	.4byte	.LVL48
	.4byte	0x917
	.uleb128 0x15
	.4byte	.LVL49
	.4byte	0x84a
	.uleb128 0x16
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	0x50a
	.uleb128 0x10
	.4byte	.LASF185
	.byte	0xe9
	.4byte	0x2ae
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x74e
	.uleb128 0x8
	.4byte	.LASF182
	.byte	0xe9
	.byte	0x49
	.4byte	0x6eb
	.4byte	.LLST17
	.uleb128 0x8
	.4byte	.LASF186
	.byte	0xe9
	.byte	0x6d
	.4byte	0x516
	.4byte	.LLST18
	.uleb128 0xe
	.4byte	0x960
	.4byte	.LBB19
	.4byte	.LLRL19
	.byte	0xeb
	.uleb128 0xf
	.4byte	.LVL43
	.4byte	0x917
	.uleb128 0x15
	.4byte	.LVL44
	.4byte	0x74e
	.uleb128 0x16
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF187
	.byte	0xc4
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x822
	.uleb128 0x17
	.4byte	.LASF182
	.byte	0xc4
	.4byte	0x6eb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x4
	.4byte	.LASF188
	.byte	0xc7
	.byte	0xe
	.4byte	0xf0
	.4byte	.LLST8
	.uleb128 0x4
	.4byte	.LASF189
	.byte	0xc8
	.byte	0xe
	.4byte	0xf0
	.4byte	.LLST9
	.uleb128 0x3
	.4byte	.LASF190
	.byte	0xc9
	.byte	0xe
	.4byte	0xf0
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x4
	.4byte	.LASF191
	.byte	0xca
	.byte	0xe
	.4byte	0xf0
	.4byte	.LLST10
	.uleb128 0x3
	.4byte	.LASF192
	.byte	0xcb
	.byte	0xe
	.4byte	0xf0
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x4
	.4byte	.LASF193
	.byte	0xcc
	.byte	0xe
	.4byte	0xf0
	.4byte	.LLST11
	.uleb128 0x18
	.4byte	.LLRL12
	.4byte	0x7dd
	.uleb128 0x4
	.4byte	.LASF194
	.byte	0xd7
	.byte	0x12
	.4byte	0xf0
	.4byte	.LLST13
	.byte	0
	.uleb128 0x22
	.4byte	.LBB18
	.4byte	.LBE18-.LBB18
	.uleb128 0x23
	.4byte	.LASF191
	.byte	0x1
	.byte	0xde
	.byte	0x12
	.4byte	0xf0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF193
	.byte	0xdf
	.byte	0x12
	.4byte	0xf0
	.4byte	.LLST14
	.uleb128 0x4
	.4byte	.LASF194
	.byte	0xe3
	.byte	0x12
	.4byte	0xf0
	.4byte	.LLST15
	.uleb128 0x4
	.4byte	.LASF195
	.byte	0xe4
	.byte	0x12
	.4byte	0xf0
	.4byte	.LLST16
	.byte	0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF196
	.byte	0xb2
	.4byte	0x2ae
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x84a
	.uleb128 0x8
	.4byte	.LASF182
	.byte	0xb2
	.byte	0x45
	.4byte	0x6eb
	.4byte	.LLST7
	.byte	0
	.uleb128 0xb
	.4byte	.LASF197
	.byte	0x91
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x917
	.uleb128 0x17
	.4byte	.LASF182
	.byte	0x91
	.4byte	0x6eb
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x4
	.4byte	.LASF198
	.byte	0x94
	.byte	0xe
	.4byte	0xf0
	.4byte	.LLST1
	.uleb128 0x3
	.4byte	.LASF190
	.byte	0x98
	.byte	0xe
	.4byte	0xf0
	.uleb128 0x6
	.byte	0x7a
	.sleb128 8
	.byte	0x6
	.byte	0x38
	.byte	0x24
	.byte	0x9f
	.uleb128 0x3
	.4byte	.LASF189
	.byte	0x99
	.byte	0xe
	.4byte	0xf0
	.uleb128 0x2
	.byte	0x7a
	.sleb128 12
	.uleb128 0x3
	.4byte	.LASF191
	.byte	0x9a
	.byte	0xe
	.4byte	0xf0
	.uleb128 0x6
	.byte	0x7a
	.sleb128 20
	.byte	0x6
	.byte	0x3c
	.byte	0x24
	.byte	0x9f
	.uleb128 0x3
	.4byte	.LASF192
	.byte	0x9b
	.byte	0xe
	.4byte	0xf0
	.uleb128 0x6
	.byte	0x7a
	.sleb128 24
	.byte	0x6
	.byte	0x3e
	.byte	0x24
	.byte	0x9f
	.uleb128 0x18
	.4byte	.LLRL2
	.4byte	0x8e5
	.uleb128 0x4
	.4byte	.LASF193
	.byte	0xa0
	.byte	0x12
	.4byte	0xf0
	.4byte	.LLST3
	.uleb128 0x4
	.4byte	.LASF199
	.byte	0xa3
	.byte	0x11
	.4byte	0xd6
	.4byte	.LLST4
	.byte	0
	.uleb128 0x24
	.4byte	.LLRL5
	.uleb128 0x4
	.4byte	.LASF193
	.byte	0xa8
	.byte	0x12
	.4byte	0xf0
	.4byte	.LLST6
	.uleb128 0x3
	.4byte	.LASF200
	.byte	0xab
	.byte	0x11
	.4byte	0xd6
	.uleb128 0x2
	.byte	0x7a
	.sleb128 28
	.uleb128 0x3
	.4byte	.LASF201
	.byte	0xac
	.byte	0x11
	.4byte	0xd6
	.uleb128 0x2
	.byte	0x7a
	.sleb128 29
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF202
	.byte	0x89
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x948
	.uleb128 0x8
	.4byte	.LASF161
	.byte	0x89
	.byte	0x46
	.4byte	0x32c
	.4byte	.LLST0
	.uleb128 0x3
	.4byte	.LASF203
	.byte	0x8c
	.byte	0xe
	.4byte	0xf0
	.uleb128 0x1
	.byte	0x5e
	.byte	0
	.uleb128 0x25
	.4byte	.LASF209
	.byte	0x1
	.byte	0x72
	.byte	0x6
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x19
	.4byte	.LASF204
	.byte	0x6c
	.uleb128 0x19
	.4byte	.LASF205
	.byte	0x66
	.uleb128 0x1a
	.4byte	0x960
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1a
	.4byte	0x95a
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
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
	.uleb128 0x4
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
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
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
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
	.uleb128 0xc
	.uleb128 0x26
	.byte	0
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
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0xe
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0x21
	.sleb128 5
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
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
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 25
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
	.uleb128 0x11
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x21
	.sleb128 61
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 1
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0
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
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.uleb128 0x1f
	.uleb128 0x15
	.byte	0
	.uleb128 0x27
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.byte	0
	.byte	0
	.uleb128 0x23
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
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.byte	0
	.section	.debug_loclists,"",@progbits
	.4byte	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.2byte	0x5
	.byte	0x4
	.byte	0
	.4byte	0
.Ldebug_loc0:
.LLST20:
	.byte	0x6
	.4byte	.LVL46
	.byte	0x4
	.uleb128 .LVL46-.LVL46
	.uleb128 .LVL47-.LVL46
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL47-.LVL46
	.uleb128 .LVL50-.LVL46
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL50-.LVL46
	.uleb128 .LFE12-.LVL46
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
.LLST21:
	.byte	0x6
	.4byte	.LVL46
	.byte	0x4
	.uleb128 .LVL46-.LVL46
	.uleb128 .LVL48-1-.LVL46
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL48-1-.LVL46
	.uleb128 .LFE12-.LVL46
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
.LLST17:
	.byte	0x6
	.4byte	.LVL41
	.byte	0x4
	.uleb128 .LVL41-.LVL41
	.uleb128 .LVL42-.LVL41
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL42-.LVL41
	.uleb128 .LVL45-.LVL41
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL45-.LVL41
	.uleb128 .LFE11-.LVL41
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
.LLST18:
	.byte	0x6
	.4byte	.LVL41
	.byte	0x4
	.uleb128 .LVL41-.LVL41
	.uleb128 .LVL43-1-.LVL41
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL43-1-.LVL41
	.uleb128 .LFE11-.LVL41
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
.LLST8:
	.byte	0x6
	.4byte	.LVL22
	.byte	0x4
	.uleb128 .LVL22-.LVL22
	.uleb128 .LVL23-.LVL22
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL23-.LVL22
	.uleb128 .LFE10-.LVL22
	.uleb128 0xa
	.byte	0x77
	.sleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	comp_2_mode_cfg_value
	.byte	0x22
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL24
	.byte	0x4
	.uleb128 .LVL24-.LVL24
	.uleb128 .LVL28-.LVL24
	.uleb128 0x7
	.byte	0x7e
	.sleb128 0
	.byte	0xa
	.2byte	0x3100
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL28-.LVL24
	.uleb128 .LVL31-.LVL24
	.uleb128 0xa
	.byte	0x7a
	.sleb128 12
	.byte	0x6
	.byte	0x34
	.byte	0x24
	.byte	0xa
	.2byte	0x3100
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL31-.LVL24
	.uleb128 .LVL32-.LVL24
	.uleb128 0x7
	.byte	0x7e
	.sleb128 0
	.byte	0xa
	.2byte	0x3100
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL32-.LVL24
	.uleb128 .LVL35-.LVL24
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL35-.LVL24
	.uleb128 .LVL36-.LVL24
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL36-.LVL24
	.uleb128 .LFE10-.LVL24
	.uleb128 0x8
	.byte	0x7a
	.sleb128 12
	.byte	0x6
	.byte	0x34
	.byte	0x24
	.byte	0x31
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL24
	.byte	0x4
	.uleb128 .LVL24-.LVL24
	.uleb128 .LVL26-.LVL24
	.uleb128 0x5
	.byte	0x7f
	.sleb128 0
	.byte	0x34
	.byte	0x24
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL26-.LVL24
	.uleb128 .LVL27-.LVL24
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL27-.LVL24
	.uleb128 .LVL31-.LVL24
	.uleb128 0x6
	.byte	0x7a
	.sleb128 20
	.byte	0x6
	.byte	0x34
	.byte	0x24
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL31-.LVL24
	.uleb128 .LVL34-.LVL24
	.uleb128 0x5
	.byte	0x7f
	.sleb128 0
	.byte	0x34
	.byte	0x24
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL34-.LVL24
	.uleb128 .LFE10-.LVL24
	.uleb128 0x6
	.byte	0x7a
	.sleb128 20
	.byte	0x6
	.byte	0x34
	.byte	0x24
	.byte	0x9f
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL25
	.byte	0x4
	.uleb128 .LVL25-.LVL25
	.uleb128 .LVL26-.LVL25
	.uleb128 0xb
	.byte	0x7f
	.sleb128 0
	.byte	0x34
	.byte	0x24
	.byte	0x75
	.sleb128 0
	.byte	0x21
	.byte	0x7b
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL26-.LVL25
	.uleb128 .LVL27-.LVL25
	.uleb128 0x9
	.byte	0x7f
	.sleb128 0
	.byte	0x75
	.sleb128 0
	.byte	0x21
	.byte	0x7b
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL27-.LVL25
	.uleb128 .LVL31-.LVL25
	.uleb128 0xc
	.byte	0x7a
	.sleb128 20
	.byte	0x6
	.byte	0x34
	.byte	0x24
	.byte	0x75
	.sleb128 0
	.byte	0x21
	.byte	0x7b
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL31-.LVL25
	.uleb128 .LVL34-.LVL25
	.uleb128 0xb
	.byte	0x7f
	.sleb128 0
	.byte	0x34
	.byte	0x24
	.byte	0x75
	.sleb128 0
	.byte	0x21
	.byte	0x7b
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL34-.LVL25
	.uleb128 .LFE10-.LVL25
	.uleb128 0xc
	.byte	0x7a
	.sleb128 20
	.byte	0x6
	.byte	0x34
	.byte	0x24
	.byte	0x75
	.sleb128 0
	.byte	0x21
	.byte	0x7b
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST13:
	.byte	0x8
	.4byte	.LVL29
	.uleb128 .LVL30-.LVL29
	.uleb128 0xa
	.byte	0x7a
	.sleb128 28
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x38
	.byte	0x24
	.byte	0x9f
	.byte	0
.LLST14:
	.byte	0x6
	.4byte	.LVL34
	.byte	0x4
	.uleb128 .LVL34-.LVL34
	.uleb128 .LVL37-.LVL34
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL37-.LVL34
	.uleb128 .LVL39-.LVL34
	.uleb128 0x5
	.byte	0xc
	.4byte	0x42080068
	.byte	0x4
	.uleb128 .LVL39-.LVL34
	.uleb128 .LVL40-.LVL34
	.uleb128 0x3
	.byte	0x7e
	.sleb128 104
	.byte	0x4
	.uleb128 .LVL40-.LVL34
	.uleb128 .LFE10-.LVL34
	.uleb128 0x6
	.byte	0x7b
	.sleb128 0
	.byte	0x75
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST15:
	.byte	0x8
	.4byte	.LVL38
	.uleb128 .LVL40-.LVL38
	.uleb128 0xa
	.byte	0x7a
	.sleb128 28
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x38
	.byte	0x24
	.byte	0x9f
	.byte	0
.LLST16:
	.byte	0x8
	.4byte	.LVL38
	.uleb128 .LVL40-.LVL38
	.uleb128 0x8
	.byte	0x7a
	.sleb128 29
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL16
	.byte	0x4
	.uleb128 .LVL16-.LVL16
	.uleb128 .LVL17-.LVL16
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL17-.LVL16
	.uleb128 .LVL18-.LVL16
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL18-.LVL16
	.uleb128 .LVL19-.LVL16
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
	.uleb128 .LVL19-.LVL16
	.uleb128 .LVL20-.LVL16
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL20-.LVL16
	.uleb128 .LFE9-.LVL16
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
	.uleb128 .LVL6-.LVL4
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL6-.LVL4
	.uleb128 .LVL7-.LVL4
	.uleb128 0xa
	.byte	0x7c
	.sleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	comp_1_mode_cfg_value
	.byte	0x22
	.byte	0x4
	.uleb128 .LVL7-.LVL4
	.uleb128 .LVL11-.LVL4
	.uleb128 0xb
	.byte	0x7a
	.sleb128 4
	.byte	0x6
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	comp_1_mode_cfg_value
	.byte	0x22
	.byte	0x4
	.uleb128 .LVL11-.LVL4
	.uleb128 .LVL12-.LVL4
	.uleb128 0xa
	.byte	0x7c
	.sleb128 0
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	comp_1_mode_cfg_value
	.byte	0x22
	.byte	0x4
	.uleb128 .LVL12-.LVL4
	.uleb128 .LFE8-.LVL4
	.uleb128 0xb
	.byte	0x7a
	.sleb128 4
	.byte	0x6
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	comp_1_mode_cfg_value
	.byte	0x22
	.byte	0
.LLST3:
	.byte	0x8
	.4byte	.LVL8
	.uleb128 .LVL10-.LVL8
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST4:
	.byte	0x8
	.4byte	.LVL9
	.uleb128 .LVL10-.LVL9
	.uleb128 0x2
	.byte	0x7a
	.sleb128 28
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL13
	.byte	0x4
	.uleb128 .LVL13-.LVL13
	.uleb128 .LVL15-.LVL13
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL15-.LVL13
	.uleb128 .LFE8-.LVL13
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
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
	.uleb128 .LFE7-.LVL0
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
	.4byte	0x84
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
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
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
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
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
	.4byte	.LBB8
	.byte	0x4
	.uleb128 .LBB8-.LBB8
	.uleb128 .LBE8-.LBB8
	.byte	0x4
	.uleb128 .LBB9-.LBB8
	.uleb128 .LBE9-.LBB8
	.byte	0x4
	.uleb128 .LBB10-.LBB8
	.uleb128 .LBE10-.LBB8
	.byte	0x4
	.uleb128 .LBB11-.LBB8
	.uleb128 .LBE11-.LBB8
	.byte	0
.LLRL5:
	.byte	0x5
	.4byte	.LBB12
	.byte	0x4
	.uleb128 .LBB12-.LBB12
	.uleb128 .LBE12-.LBB12
	.byte	0x4
	.uleb128 .LBB13-.LBB12
	.uleb128 .LBE13-.LBB12
	.byte	0
.LLRL12:
	.byte	0x5
	.4byte	.LBB14
	.byte	0x4
	.uleb128 .LBB14-.LBB14
	.uleb128 .LBE14-.LBB14
	.byte	0x4
	.uleb128 .LBB15-.LBB14
	.uleb128 .LBE15-.LBB14
	.byte	0x4
	.uleb128 .LBB16-.LBB14
	.uleb128 .LBE16-.LBB14
	.byte	0x4
	.uleb128 .LBB17-.LBB14
	.uleb128 .LBE17-.LBB14
	.byte	0
.LLRL19:
	.byte	0x5
	.4byte	.LBB19
	.byte	0x4
	.uleb128 .LBB19-.LBB19
	.uleb128 .LBE19-.LBB19
	.byte	0x4
	.uleb128 .LBB23-.LBB19
	.uleb128 .LBE23-.LBB19
	.byte	0x4
	.uleb128 .LBB24-.LBB19
	.uleb128 .LBE24-.LBB19
	.byte	0
.LLRL22:
	.byte	0x5
	.4byte	.LBB25
	.byte	0x4
	.uleb128 .LBB25-.LBB25
	.uleb128 .LBE25-.LBB25
	.byte	0x4
	.uleb128 .LBB29-.LBB25
	.uleb128 .LBE29-.LBB25
	.byte	0x4
	.uleb128 .LBB30-.LBB25
	.uleb128 .LBE30-.LBB25
	.byte	0
.LLRL23:
	.byte	0x5
	.4byte	.LBB31
	.byte	0x4
	.uleb128 .LBB31-.LBB31
	.uleb128 .LBE31-.LBB31
	.byte	0x4
	.uleb128 .LBB34-.LBB31
	.uleb128 .LBE34-.LBB31
	.byte	0
.LLRL24:
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
	.byte	0x7
	.4byte	.LFB10
	.uleb128 .LFE10-.LFB10
	.byte	0x7
	.4byte	.LFB11
	.uleb128 .LFE11-.LFB11
	.byte	0x7
	.4byte	.LFB12
	.uleb128 .LFE12-.LFB12
	.byte	0x7
	.4byte	.LFB13
	.uleb128 .LFE13-.LFB13
	.byte	0x7
	.4byte	.LFB14
	.uleb128 .LFE14-.LFB14
	.byte	0x7
	.4byte	.LFB15
	.uleb128 .LFE15-.LFB15
	.byte	0x7
	.4byte	.LFB16
	.uleb128 .LFE16-.LFB16
	.byte	0x7
	.4byte	.LFB17
	.uleb128 .LFE17-.LFB17
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF179:
	.string	"enable_value"
.LASF114:
	.string	"HAL_COMP_SE_MODE_REF_ON_LS_MODE"
.LASF130:
	.string	"HAL_GPIO_SEL_GPIO25"
.LASF131:
	.string	"HAL_GPIO_SEL_GPIO26"
.LASF132:
	.string	"HAL_GPIO_SEL_GPIO27"
.LASF133:
	.string	"HAL_GPIO_SEL_GPIO28"
.LASF134:
	.string	"HAL_GPIO_SEL_GPIO29"
.LASF84:
	.string	"HAL_EINT_USB1"
.LASF85:
	.string	"HAL_EINT_USB2"
.LASF137:
	.string	"HAL_GPIO_SEL_GPIO32"
.LASF180:
	.string	"hal_comp1_disable"
.LASF23:
	.string	"signed char"
.LASF99:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_1_2"
.LASF81:
	.string	"HAL_EINT_UART_1_RX"
.LASF206:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF144:
	.string	"HAL_REF_V_SEL_GPIO_IN"
.LASF146:
	.string	"hal_comp_ref_in_cfg_t"
.LASF193:
	.string	"ref_in_mask"
.LASF2:
	.string	"long long unsigned int"
.LASF195:
	.string	"vdn_mask"
.LASF6:
	.string	"QDEC_IRQn"
.LASF196:
	.string	"comparator_para_check"
.LASF160:
	.string	"ref_in_gpio"
.LASF128:
	.string	"hal_comp_mode_cfg_t"
.LASF121:
	.string	"HAL_COMP_DIFF_MODE_REF_ON_LS_MODE"
.LASF135:
	.string	"HAL_GPIO_SEL_GPIO30"
.LASF136:
	.string	"HAL_GPIO_SEL_GPIO31"
.LASF26:
	.string	"long long int"
.LASF138:
	.string	"HAL_GPIO_SEL_GPIO33"
.LASF139:
	.string	"HAL_GPIO_SEL_GPIO34"
.LASF150:
	.string	"HAL_LADDER_REF_V_SEL_VDD"
.LASF12:
	.string	"UART_DMA_IRQn"
.LASF80:
	.string	"HAL_EINT_UART_0_RX"
.LASF148:
	.string	"HAL_LADDER_REF_V_SEL_REF_ON_IN"
.LASF175:
	.string	"g_comp2_mode_reg_value"
.LASF8:
	.string	"UART_IRQn"
.LASF173:
	.string	"g_comp_lp_callabck"
.LASF177:
	.string	"hal_comp2_disable"
.LASF7:
	.string	"KEYSCAN_IRQn"
.LASF25:
	.string	"long int"
.LASF110:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_VDD"
.LASF59:
	.string	"HAL_EINT_NUMBER_27"
.LASF106:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_2_4"
.LASF187:
	.string	"hal_comparator_analog_comp2_init"
.LASF97:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_1_2"
.LASF147:
	.string	"HAL_LADDER_REF_V_SEL_AVSS"
.LASF16:
	.string	"I3C0_IRQn"
.LASF172:
	.string	"g_comp2_callabck"
.LASF116:
	.string	"HAL_COMP_SE_MODE_REF_ON_HS_MODE"
.LASF154:
	.string	"HAL_COMP_LP"
.LASF161:
	.string	"internal_ref_cfg"
.LASF181:
	.string	"hal_comp1_enable"
.LASF15:
	.string	"EINT_IRQn"
.LASF17:
	.string	"I3C0_DMA_IRQn"
.LASF151:
	.string	"hal_comp_ref_ladder_in_cfg_t"
.LASF191:
	.string	"ref_sel_mask"
.LASF201:
	.string	"rladder_value_vdn"
.LASF157:
	.string	"comp_port"
.LASF3:
	.string	"unsigned int"
.LASF117:
	.string	"HAL_COMP_SE_MODE_REF_OFF_LS_MODE"
.LASF94:
	.string	"HAL_COMPARATOR_STATUS_OK"
.LASF155:
	.string	"HAL_COMP_MAX"
.LASF31:
	.string	"long unsigned int"
.LASF109:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_VDD"
.LASF208:
	.string	"hal_comparator_deinit"
.LASF115:
	.string	"HAL_COMP_SE_MODE_REF_ON_NM_MODE"
.LASF202:
	.string	"hal_comparator_analog_int_ref_on"
.LASF105:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_2_4"
.LASF28:
	.string	"short unsigned int"
.LASF140:
	.string	"HAL_GPIO_SEL_MAX"
.LASF88:
	.string	"HAL_EINT_NUMBER_MAX"
.LASF164:
	.string	"vup_rladder_value"
.LASF32:
	.string	"HAL_EINT_NUMBER_0"
.LASF33:
	.string	"HAL_EINT_NUMBER_1"
.LASF34:
	.string	"HAL_EINT_NUMBER_2"
.LASF35:
	.string	"HAL_EINT_NUMBER_3"
.LASF36:
	.string	"HAL_EINT_NUMBER_4"
.LASF37:
	.string	"HAL_EINT_NUMBER_5"
.LASF38:
	.string	"HAL_EINT_NUMBER_6"
.LASF39:
	.string	"HAL_EINT_NUMBER_7"
.LASF40:
	.string	"HAL_EINT_NUMBER_8"
.LASF41:
	.string	"HAL_EINT_NUMBER_9"
.LASF95:
	.string	"hal_comparator_status_t"
.LASF24:
	.string	"short int"
.LASF18:
	.string	"SPI_MST0_IRQn"
.LASF127:
	.string	"HAL_COMP_MODE_MAX"
.LASF159:
	.string	"input_gpio"
.LASF108:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_VDD"
.LASF125:
	.string	"HAL_COMP_DIFF_MODE_REF_OFF_NM_MODE"
.LASF124:
	.string	"HAL_COMP_DIFF_MODE_REF_OFF_LS_MODE"
.LASF156:
	.string	"hal_comp_port_t"
.LASF207:
	.string	"IRQn"
.LASF122:
	.string	"HAL_COMP_DIFF_MODE_REF_ON_NM_MODE"
.LASF104:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_2_4"
.LASF86:
	.string	"HAL_EINT_LPCOMP"
.LASF176:
	.string	"disable_value"
.LASF199:
	.string	"rladder_value"
.LASF112:
	.string	"HAL_COMPARATOR_INT_REFF_MAX"
.LASF171:
	.string	"g_comp1_callabck"
.LASF11:
	.string	"GPT_IRQn"
.LASF93:
	.string	"HAL_COMPARATOR_STATUS_ERROR"
.LASF4:
	.string	"SW_IRQn"
.LASF98:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_1_2"
.LASF20:
	.string	"USB_IRQn"
.LASF111:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_VDD"
.LASF118:
	.string	"HAL_COMP_SE_MODE_REF_OFF_NM_MODE"
.LASF102:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_1_8"
.LASF200:
	.string	"rladder_value_vup"
.LASF9:
	.string	"SPI_MST1_IRQn"
.LASF101:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_1_8"
.LASF42:
	.string	"HAL_EINT_NUMBER_10"
.LASF43:
	.string	"HAL_EINT_NUMBER_11"
.LASF44:
	.string	"HAL_EINT_NUMBER_12"
.LASF45:
	.string	"HAL_EINT_NUMBER_13"
.LASF46:
	.string	"HAL_EINT_NUMBER_14"
.LASF47:
	.string	"HAL_EINT_NUMBER_15"
.LASF48:
	.string	"HAL_EINT_NUMBER_16"
.LASF49:
	.string	"HAL_EINT_NUMBER_17"
.LASF50:
	.string	"HAL_EINT_NUMBER_18"
.LASF51:
	.string	"HAL_EINT_NUMBER_19"
.LASF163:
	.string	"ladder_ref_sel"
.LASF165:
	.string	"vdn_rladder_value"
.LASF149:
	.string	"HAL_LADDER_REF_V_SEL_GPIO_IN"
.LASF100:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_1_8"
.LASF91:
	.string	"_Bool"
.LASF183:
	.string	"comp1_callback"
.LASF186:
	.string	"comp2_callback"
.LASF143:
	.string	"HAL_REF_V_SEL_INTERNAL_REF_IN"
.LASF167:
	.string	"hal_comparator_callback_t"
.LASF141:
	.string	"hal_comp_gpio_cfg_t"
.LASF96:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_1_2"
.LASF168:
	.string	"internal_ref_cfg_value"
.LASF13:
	.string	"PMU_IRQn"
.LASF14:
	.string	"MCU_DMA_IRQn"
.LASF126:
	.string	"HAL_COMP_DIFF_MODE_REF_OFF_HS_MODE"
.LASF113:
	.string	"hal_comparator_inter_ref_cfg_t"
.LASF194:
	.string	"vup_mask"
.LASF189:
	.string	"ref_in_gpio_mask"
.LASF205:
	.string	"hal_comparator_analog_power_on"
.LASF129:
	.string	"HAL_GPIO_SEL_NO"
.LASF174:
	.string	"g_comp1_mode_reg_value"
.LASF103:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_1_8"
.LASF204:
	.string	"hal_comparator_analog_power_off"
.LASF52:
	.string	"HAL_EINT_NUMBER_20"
.LASF53:
	.string	"HAL_EINT_NUMBER_21"
.LASF54:
	.string	"HAL_EINT_NUMBER_22"
.LASF55:
	.string	"HAL_EINT_NUMBER_23"
.LASF56:
	.string	"HAL_EINT_NUMBER_24"
.LASF57:
	.string	"HAL_EINT_NUMBER_25"
.LASF58:
	.string	"HAL_EINT_NUMBER_26"
.LASF30:
	.string	"uint32_t"
.LASF60:
	.string	"HAL_EINT_NUMBER_28"
.LASF61:
	.string	"HAL_EINT_NUMBER_29"
.LASF77:
	.string	"HAL_EINT_NUMBER_45"
.LASF79:
	.string	"HAL_EINT_NUMBER_47"
.LASF170:
	.string	"comp_2_mode_cfg_value"
.LASF89:
	.string	"long double"
.LASF90:
	.string	"char"
.LASF198:
	.string	"comp1_mode_value"
.LASF158:
	.string	"mode"
.LASF19:
	.string	"IRQ_GEN_IRQn"
.LASF190:
	.string	"input_gpio_mask"
.LASF142:
	.string	"HAL_REF_V_SEL_RLADDER"
.LASF92:
	.string	"HAL_COMPARATOR_STATUS_INVALID_PARAMETER"
.LASF119:
	.string	"HAL_COMP_SE_MODE_REF_OFF_HS_MODE"
.LASF21:
	.string	"BT_IRQn"
.LASF197:
	.string	"hal_comparator_analog_comp1_init"
.LASF188:
	.string	"comp2_mode_value"
.LASF27:
	.string	"unsigned char"
.LASF123:
	.string	"HAL_COMP_DIFF_MODE_REF_ON_HS_MODE"
.LASF192:
	.string	"ladder_ref_sel_mask"
.LASF184:
	.string	"hal_comparator_comp1_init"
.LASF62:
	.string	"HAL_EINT_NUMBER_30"
.LASF63:
	.string	"HAL_EINT_NUMBER_31"
.LASF64:
	.string	"HAL_EINT_NUMBER_32"
.LASF65:
	.string	"HAL_EINT_NUMBER_33"
.LASF66:
	.string	"HAL_EINT_NUMBER_34"
.LASF67:
	.string	"HAL_EINT_NUMBER_35"
.LASF68:
	.string	"HAL_EINT_NUMBER_36"
.LASF69:
	.string	"HAL_EINT_NUMBER_37"
.LASF70:
	.string	"HAL_EINT_NUMBER_38"
.LASF71:
	.string	"HAL_EINT_NUMBER_39"
.LASF5:
	.string	"LED_IRQn"
.LASF107:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_2_4"
.LASF203:
	.string	"ref_val"
.LASF209:
	.string	"hal_comparator_analog_reset"
.LASF29:
	.string	"uint8_t"
.LASF145:
	.string	"HAL_REF_V_SEL_LP_RLADDER"
.LASF83:
	.string	"HAL_EINT_USB0"
.LASF152:
	.string	"HAL_COMP_1"
.LASF153:
	.string	"HAL_COMP_2"
.LASF87:
	.string	"HAL_EINT_RESERVED"
.LASF166:
	.string	"hal_comparator_cfg_t"
.LASF182:
	.string	"comp_cfg"
.LASF82:
	.string	"HAL_EINT_UART_2_RX"
.LASF162:
	.string	"ref_sel"
.LASF120:
	.string	"HAL_COMP_SE_MODE_MAX"
.LASF10:
	.string	"RTC_IRQn"
.LASF185:
	.string	"hal_comparator_comp2_init"
.LASF169:
	.string	"comp_1_mode_cfg_value"
.LASF72:
	.string	"HAL_EINT_NUMBER_40"
.LASF73:
	.string	"HAL_EINT_NUMBER_41"
.LASF74:
	.string	"HAL_EINT_NUMBER_42"
.LASF75:
	.string	"HAL_EINT_NUMBER_43"
.LASF76:
	.string	"HAL_EINT_NUMBER_44"
.LASF178:
	.string	"hal_comp2_enable"
.LASF78:
	.string	"HAL_EINT_NUMBER_46"
.LASF22:
	.string	"IRQ_NUMBER_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_comparator.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
