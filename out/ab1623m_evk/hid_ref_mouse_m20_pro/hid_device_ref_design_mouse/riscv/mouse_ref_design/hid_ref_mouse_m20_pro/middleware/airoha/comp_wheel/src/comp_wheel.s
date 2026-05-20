	.file	"comp_wheel.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/middleware/airoha/comp_wheel/src/comp_wheel.c"
	.section	.text.comp_set_pmu_strup_rg,"ax",@progbits
	.align	1
	.globl	comp_set_pmu_strup_rg
	.hidden	comp_set_pmu_strup_rg
	.type	comp_set_pmu_strup_rg, @function
comp_set_pmu_strup_rg:
.LFB8:
	.file 1 "/workdir/airoha/risc-v/middleware/airoha/comp_wheel/src/comp_wheel.c"
	.loc 1 143 1
	.cfi_startproc
.LVL0:
	.loc 1 144 5
	.loc 1 144 73 is_stmt 0
	slli	a0,a0,16
.LVL1:
	.loc 1 144 66
	li	a5,16777216
	or	a0,a0,a1
	or	a0,a0,a5
	.loc 1 144 46
	li	a5,1108377600
	sw	a0,8(a5)
	.loc 1 145 1
	ret
	.cfi_endproc
.LFE8:
	.size	comp_set_pmu_strup_rg, .-comp_set_pmu_strup_rg
	.section	.text.comp_get_pmu_strup_rg,"ax",@progbits
	.align	1
	.globl	comp_get_pmu_strup_rg
	.hidden	comp_get_pmu_strup_rg
	.type	comp_get_pmu_strup_rg, @function
comp_get_pmu_strup_rg:
.LFB9:
	.loc 1 148 1 is_stmt 1
	.cfi_startproc
.LVL2:
	.loc 1 149 5
	.loc 1 150 5
	.loc 1 150 59 is_stmt 0
	slli	a0,a0,16
.LVL3:
	.loc 1 150 46
	li	a5,1108377600
	sw	a0,8(a5)
	.loc 1 151 5 is_stmt 1
	.loc 1 151 10 is_stmt 0
	li	a5,1108377600
	lhu	a0,12(a5)
.LVL4:
	.loc 1 152 5 is_stmt 1
	.loc 1 153 1 is_stmt 0
	ret
	.cfi_endproc
.LFE9:
	.size	comp_get_pmu_strup_rg, .-comp_get_pmu_strup_rg
	.section	.text.comp_wheel_scan_once,"ax",@progbits
	.align	1
	.globl	comp_wheel_scan_once
	.hidden	comp_wheel_scan_once
	.type	comp_wheel_scan_once, @function
comp_wheel_scan_once:
.LFB15:
	.loc 1 239 1 is_stmt 1
	.cfi_startproc
.LVL5:
	.loc 1 240 5
	.loc 1 239 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 240 43
	lla	s0,comp_wheel_encoder
	.loc 1 239 1
	sw	s1,0(sp)
	.cfi_offset 9, -12
	mv	s1,a0
	.loc 1 240 43
	lw	a0,4(s0)
.LVL6:
	.loc 1 240 5
	li	a1,1
	.loc 1 239 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 240 5
	call	hal_gpio_set_output
.LVL7:
	.loc 1 241 5 is_stmt 1
.LBB24:
.LBB25:
	.loc 1 222 5
	call	hal_comp1_enable
.LVL8:
	.loc 1 223 5
	call	hal_comp2_enable
.LVL9:
.LBE25:
.LBE24:
	.loc 1 242 5
	mv	a0,s1
	call	hal_gpt_delay_us
.LVL10:
	.loc 1 243 5
.LBB26:
.LBB27:
	.loc 1 169 5
	.loc 1 170 5
.LBB28:
.LBB29:
	.loc 1 149 5
	.loc 1 150 5
	.loc 1 150 46 is_stmt 0
	li	a3,1108377600
	li	a5,3866624
	sw	a5,8(a3)
	.loc 1 151 5 is_stmt 1
	.loc 1 151 10 is_stmt 0
	li	a5,1108377600
	addi	a5,a5,12
	lhu	a5,0(a5)
.LVL11:
	.loc 1 152 5 is_stmt 1
.LBE29:
.LBE28:
	.loc 1 173 19 is_stmt 0
	lla	a2,g_last_pina_state
	.loc 1 173 7
	lbu	a4,0(a2)
	.loc 1 170 66 discriminator 1
	srli	a5,a5,10
	.loc 1 170 16 discriminator 1
	andi	a5,a5,1
.LVL12:
	.loc 1 171 5 is_stmt 1
	.loc 1 171 35 is_stmt 0
	sw	a5,16(s0)
	.loc 1 173 5 is_stmt 1
.LBB31:
.LBB30:
	.loc 1 150 46 is_stmt 0
	addi	a3,a3,8
.LBE30:
.LBE31:
	.loc 1 173 7
	beq	a4,a5,.L4
	.loc 1 175 9 is_stmt 1
	.loc 1 175 11 is_stmt 0
	bne	a5,zero,.L5
	.loc 1 177 13 is_stmt 1
	.loc 1 177 98 is_stmt 0
	lbu	a4,g_comp1_vup_rladder_value
.L24:
	.loc 1 180 98
	slli	a4,a4,8
	.loc 1 180 67
	li	a1,18284544
	or	a4,a4,a1
	.loc 1 180 50
	sw	a4,0(a3)
.L4:
	.loc 1 183 5 is_stmt 1
	.loc 1 183 23 is_stmt 0
	sb	a5,0(a2)
	.loc 1 186 5 is_stmt 1
	.loc 1 187 5
	.loc 1 187 29 is_stmt 0
	li	a5,1108606976
.LVL13:
	addi	a5,a5,788
	lw	a5,0(a5)
	.loc 1 187 63
	srli	a5,a5,22
	.loc 1 187 16
	andi	a5,a5,1
.LVL14:
	.loc 1 188 5 is_stmt 1
	.loc 1 188 7 is_stmt 0
	beq	a5,zero,.L6
	.loc 1 190 9 is_stmt 1
	.loc 1 190 39 is_stmt 0
	sw	zero,comp_wheel_encoder+20,a4
.L7:
	.loc 1 195 5 is_stmt 1
	.loc 1 195 19 is_stmt 0
	lla	a2,g_last_pinb_state
	.loc 1 195 7
	lbu	a4,0(a2)
	beq	a4,a5,.L8
.LBB32:
	.loc 1 197 9 is_stmt 1
	.loc 1 198 9
	.loc 1 199 9
	.loc 1 199 49 is_stmt 0
	lbu	a4,g_comp2_vup_rladder_value
	.loc 1 199 18
	slli	a3,a4,8
.LVL15:
	.loc 1 200 9 is_stmt 1
	.loc 1 200 11 is_stmt 0
	bne	a5,zero,.L9
	.loc 1 202 13 is_stmt 1
	.loc 1 202 22 is_stmt 0
	lbu	a4,g_comp2_vdn_rladder_value
.LVL16:
.L9:
	.loc 1 208 9 is_stmt 1
	.loc 1 208 66 is_stmt 0
	or	a3,a3,a4
.LVL17:
	.loc 1 208 52
	li	a4,1107820544
.LVL18:
	sw	a3,108(a4)
.LVL19:
.L8:
.LBE32:
	.loc 1 210 5 is_stmt 1
	.loc 1 210 23 is_stmt 0
	sb	a5,0(a2)
	.loc 1 211 5 is_stmt 1
	.loc 1 211 42 is_stmt 0
	lw	a5,20(s0)
.LVL20:
	.loc 1 211 80
	lw	a4,16(s0)
	.loc 1 212 22
	lla	a3,last_current_state
	.loc 1 211 54
	slli	a5,a5,1
	.loc 1 211 60
	or	a5,a5,a4
	andi	a5,a5,0xff
	.loc 1 211 19
	sb	a5,current_state,a4
	.loc 1 212 5 is_stmt 1
	.loc 1 212 7 is_stmt 0
	lbu	a4,0(a3)
	beq	a4,a5,.L10
	.loc 1 214 9 is_stmt 1
.LVL21:
.LBB33:
.LBB34:
	.loc 1 89 5
	.loc 1 89 23 is_stmt 0
	lbu	a4,28(s0)
	andi	a2,a5,3
	.loc 1 93 5
	li	a1,14
	.loc 1 89 33
	slli	a4,a4,2
	andi	a4,a4,0xff
	sb	a4,28(s0)
	.loc 1 90 5 is_stmt 1
	.loc 1 90 23 is_stmt 0
	lbu	a4,28(s0)
	or	a4,a4,a2
	.loc 1 90 33
	sb	a4,28(s0)
	.loc 1 91 5 is_stmt 1
	.loc 1 91 23 is_stmt 0
	lbu	a4,28(s0)
	.loc 1 91 33
	andi	a4,a4,15
	sb	a4,28(s0)
	.loc 1 93 5 is_stmt 1
	.loc 1 93 31 is_stmt 0
	lbu	a4,28(s0)
	andi	a2,a4,0xff
	.loc 1 93 5
	bgtu	a4,a1,.L10
	li	a4,28672
	addi	a4,a4,-1642
	srl	a4,a4,a2
	andi	a4,a4,1
	beq	a4,zero,.L10
	.loc 1 104 9 is_stmt 1
	.loc 1 104 27 is_stmt 0
	lbu	a4,29(s0)
	.loc 1 104 38
	slli	a4,a4,4
	andi	a4,a4,0xff
	sb	a4,29(s0)
	.loc 1 105 9 is_stmt 1
	.loc 1 105 60 is_stmt 0
	lbu	a2,28(s0)
	.loc 1 105 27
	lbu	a4,29(s0)
	andi	a2,a2,15
	or	a4,a4,a2
	.loc 1 105 38
	sb	a4,29(s0)
	.loc 1 106 9 is_stmt 1
	.loc 1 106 27 is_stmt 0
	lbu	a4,29(s0)
	li	a2,212
	andi	a4,a4,0xff
	.loc 1 106 38
	sb	a4,29(s0)
	.loc 1 108 9 is_stmt 1
	.loc 1 108 35 is_stmt 0
	lbu	a1,29(s0)
	andi	a4,a1,0xff
	beq	a1,a2,.L13
	bgtu	a4,a2,.L14
	li	a2,23
	beq	a4,a2,.L15
	li	a2,43
	beq	a4,a2,.L13
.LVL22:
.L10:
.LBE34:
.LBE33:
	.loc 1 216 5 is_stmt 1
.LBE27:
.LBE26:
	.loc 1 244 43 is_stmt 0
	lw	a0,4(s0)
	.loc 1 244 5
	li	a1,0
.LBB39:
.LBB37:
	.loc 1 216 24
	sb	a5,0(a3)
.LVL23:
.LBE37:
.LBE39:
	.loc 1 244 5 is_stmt 1
	call	hal_gpio_set_output
.LVL24:
	.loc 1 245 5
.LBB40:
	.loc 1 235 5
.LBB41:
.LBB42:
	.loc 1 130 5
	.loc 1 130 26 is_stmt 0
	lw	a5,24(s0)
	.loc 1 130 7
	beq	a5,zero,.L16
	.loc 1 135 5 is_stmt 1
	.loc 1 135 26 is_stmt 0
	lw	a5,32(s0)
	.loc 1 135 7
	beq	a5,zero,.L16
	.loc 1 137 9 is_stmt 1
	.loc 1 137 27 is_stmt 0
	lw	a5,32(s0)
	.loc 1 137 55
	lw	a0,24(s0)
	.loc 1 137 9
	slli	a0,a0,16
	srai	a0,a0,16
	jalr	a5
.LVL25:
	.loc 1 138 9 is_stmt 1
	.loc 1 138 46 is_stmt 0
	sw	zero,comp_wheel_encoder+24,a5
.L16:
.LBE42:
.LBE41:
.LBE40:
	.loc 1 246 5 is_stmt 1
.LBB43:
.LBB44:
	.loc 1 229 5
	call	hal_comp1_disable
.LVL26:
	.loc 1 230 5
.LBE44:
.LBE43:
	.loc 1 247 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s1,0(sp)
	.cfi_restore 9
.LVL27:
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
.LBB46:
.LBB45:
	.loc 1 230 5
	tail	hal_comp2_disable
.LVL28:
.L5:
	.cfi_restore_state
.LBE45:
.LBE46:
.LBB47:
.LBB38:
	.loc 1 180 13 is_stmt 1
	.loc 1 180 98 is_stmt 0
	lbu	a4,g_comp1_vdn_rladder_value
	j	.L24
.LVL29:
.L6:
	.loc 1 192 9 is_stmt 1
	.loc 1 192 39 is_stmt 0
	li	a4,1
	sw	a4,20(s0)
	j	.L7
.LVL30:
.L14:
.LBB36:
.LBB35:
	li	a2,232
	bne	a4,a2,.L10
.L15:
	.loc 1 112 17 is_stmt 1
	.loc 1 112 35 is_stmt 0
	lw	a4,24(s0)
	.loc 1 112 53
	addi	a4,a4,1
.L25:
	.loc 1 116 53
	sw	a4,24(s0)
	.loc 1 117 13 is_stmt 1
	j	.L10
.L13:
	.loc 1 116 17
	.loc 1 116 35 is_stmt 0
	lw	a4,24(s0)
	.loc 1 116 53
	addi	a4,a4,-1
	j	.L25
.LBE35:
.LBE36:
.LBE38:
.LBE47:
	.cfi_endproc
.LFE15:
	.size	comp_wheel_scan_once, .-comp_wheel_scan_once
	.section	.text.comp_wheel_init,"ax",@progbits
	.align	1
	.globl	comp_wheel_init
	.hidden	comp_wheel_init
	.type	comp_wheel_init, @function
comp_wheel_init:
.LFB16:
	.loc 1 250 1 is_stmt 1
	.cfi_startproc
.LVL31:
	.loc 1 251 5
	.loc 1 251 15 is_stmt 0
	lw	t1,0(a0)
	.loc 1 251 7
	li	a4,48
	bgtu	t1,a4,.L28
	.loc 1 256 15
	lw	a2,4(a0)
	.loc 1 256 7
	li	t0,11
	mv	a5,a0
	.loc 1 256 5 is_stmt 1
	.loc 1 253 16 is_stmt 0
	li	a0,-2
.LVL32:
	.loc 1 256 7
	bgtu	a2,t0,.L32
	.loc 1 261 5 is_stmt 1
	.loc 1 261 15 is_stmt 0
	lw	a3,8(a5)
	.loc 1 261 7
	bgtu	a3,t0,.L32
	.loc 1 266 5 is_stmt 1
	.loc 1 250 1 is_stmt 0
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sw	ra,44(sp)
	sw	s0,40(sp)
	sw	s1,36(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 266 32
	lla	a5,comp_wheel_encoder
.LVL33:
	sw	t1,4(a5)
	.loc 1 267 5 is_stmt 1
	.loc 1 267 29 is_stmt 0
	sw	a2,8(a5)
	.loc 1 268 5 is_stmt 1
	.loc 1 268 29 is_stmt 0
	sw	a3,12(a5)
	.loc 1 269 5 is_stmt 1
	.loc 1 269 33 is_stmt 0
	sw	a1,32(a5)
	.loc 1 271 5 is_stmt 1
	.loc 1 271 43 is_stmt 0
	lw	s1,8(a5)
	.loc 1 271 67
	lw	a2,12(a5)
.LBB56:
.LBB57:
.LBB58:
.LBB59:
	.loc 1 53 26
	li	s0,1
.LBE59:
.LBE58:
.LBE57:
.LBE56:
	.loc 1 271 67
	sw	a2,0(sp)
.LVL34:
.LBB70:
.LBB68:
	.loc 1 157 5 is_stmt 1
	call	hal_comparator_analog_power_on
.LVL35:
	.loc 1 158 5
	li	a0,15
	call	hal_comparator_analog_int_ref_on
.LVL36:
	.loc 1 159 5
.LBB61:
.LBB60:
	.loc 1 53 5
	.loc 1 64 31 is_stmt 0
	li	a4,48
	.loc 1 53 26
	sw	s1,12(sp)
	.loc 1 64 31
	sb	a4,g_comp1_vup_rladder_value,a5
	.loc 1 53 26
	li	s1,4096
.LVL37:
	li	a3,15
	addi	s1,s1,48
	.loc 1 65 31
	li	a5,16
	.loc 1 66 5
	addi	a0,sp,4
	.loc 1 53 26
	sw	s0,8(sp)
	sw	a3,20(sp)
	sw	s0,28(sp)
	sh	s1,32(sp)
	.loc 1 64 5 is_stmt 1
	.loc 1 65 5
	.loc 1 66 5
	.loc 1 53 26 is_stmt 0
	sw	zero,4(sp)
	sw	zero,16(sp)
	sw	zero,24(sp)
	.loc 1 65 31
	sb	a5,g_comp1_vdn_rladder_value,a1
	.loc 1 66 5
	call	hal_comparator_analog_comp1_init
.LVL38:
.LBE60:
.LBE61:
	.loc 1 160 5 is_stmt 1
.LBB62:
.LBB63:
	.loc 1 71 5
	.loc 1 71 26 is_stmt 0
	lw	a2,0(sp)
	.loc 1 82 31
	li	a4,48
	.loc 1 71 26
	li	a3,15
	.loc 1 83 31
	li	a5,16
	.loc 1 84 5
	addi	a0,sp,4
	.loc 1 71 26
	sw	s0,4(sp)
	sw	s0,8(sp)
	sw	a3,20(sp)
	sw	s0,28(sp)
	sh	s1,32(sp)
	.loc 1 82 5 is_stmt 1
	.loc 1 82 31 is_stmt 0
	sb	a4,g_comp2_vup_rladder_value,a3
	.loc 1 83 5 is_stmt 1
	.loc 1 71 26 is_stmt 0
	sw	a2,12(sp)
	.loc 1 83 31
	sb	a5,g_comp2_vdn_rladder_value,a4
	.loc 1 84 5 is_stmt 1
	.loc 1 71 26 is_stmt 0
	sw	zero,16(sp)
	sw	zero,24(sp)
	.loc 1 84 5
	call	hal_comparator_analog_comp2_init
.LVL39:
.LBE63:
.LBE62:
	.loc 1 163 5 is_stmt 1
.LBB64:
.LBB65:
	.loc 1 144 5
.LBE65:
.LBE64:
.LBE68:
.LBE70:
	.loc 1 273 1 is_stmt 0
	lw	ra,44(sp)
	.cfi_restore 1
	lw	s0,40(sp)
	.cfi_restore 8
.LBB71:
.LBB69:
.LBB67:
.LBB66:
	.loc 1 144 46
	li	a4,18939904
	li	a5,1108377600
	addi	a4,a4,3
	sw	a4,8(a5)
.LVL40:
.LBE66:
.LBE67:
.LBE69:
.LBE71:
	.loc 1 272 5 is_stmt 1
	.loc 1 273 1 is_stmt 0
	lw	s1,36(sp)
	.cfi_restore 9
	.loc 1 272 12
	li	a0,0
	.loc 1 273 1
	addi	sp,sp,48
	.cfi_def_cfa_offset 0
	jr	ra
.LVL41:
.L28:
	.loc 1 253 16
	li	a0,-2
.LVL42:
	ret
.LVL43:
.L32:
	.loc 1 273 1
	ret
	.cfi_endproc
.LFE16:
	.size	comp_wheel_init, .-comp_wheel_init
	.section	.text.comp_wheel_deinit,"ax",@progbits
	.align	1
	.globl	comp_wheel_deinit
	.hidden	comp_wheel_deinit
	.type	comp_wheel_deinit, @function
comp_wheel_deinit:
.LFB17:
	.loc 1 276 1 is_stmt 1
	.cfi_startproc
	.loc 1 277 5
	tail	hal_comparator_deinit
.LVL44:
	.cfi_endproc
.LFE17:
	.size	comp_wheel_deinit, .-comp_wheel_deinit
	.section	.sbss.g_last_pinb_state,"aw",@nobits
	.type	g_last_pinb_state, @object
	.size	g_last_pinb_state, 1
g_last_pinb_state:
	.zero	1
	.section	.sbss.g_last_pina_state,"aw",@nobits
	.type	g_last_pina_state, @object
	.size	g_last_pina_state, 1
g_last_pina_state:
	.zero	1
	.section	.sbss.g_comp2_vdn_rladder_value,"aw",@nobits
	.type	g_comp2_vdn_rladder_value, @object
	.size	g_comp2_vdn_rladder_value, 1
g_comp2_vdn_rladder_value:
	.zero	1
	.section	.sbss.g_comp2_vup_rladder_value,"aw",@nobits
	.type	g_comp2_vup_rladder_value, @object
	.size	g_comp2_vup_rladder_value, 1
g_comp2_vup_rladder_value:
	.zero	1
	.section	.sbss.g_comp1_vdn_rladder_value,"aw",@nobits
	.type	g_comp1_vdn_rladder_value, @object
	.size	g_comp1_vdn_rladder_value, 1
g_comp1_vdn_rladder_value:
	.zero	1
	.section	.sbss.g_comp1_vup_rladder_value,"aw",@nobits
	.type	g_comp1_vup_rladder_value, @object
	.size	g_comp1_vup_rladder_value, 1
g_comp1_vup_rladder_value:
	.zero	1
	.section	.sbss.last_current_state,"aw",@nobits
	.type	last_current_state, @object
	.size	last_current_state, 1
last_current_state:
	.zero	1
	.section	.sbss.current_state,"aw",@nobits
	.type	current_state, @object
	.size	current_state, 1
current_state:
	.zero	1
	.section	.bss.comp_wheel_encoder,"aw",@nobits
	.align	2
	.type	comp_wheel_encoder, @object
	.size	comp_wheel_encoder, 36
comp_wheel_encoder:
	.zero	36
	.hidden	log_control_block_mirror_comp_wheel
	.globl	log_control_block_mirror_comp_wheel
	.section	.log_filter_mirror.comp_wheel,"a"
	.align	2
	.type	log_control_block_mirror_comp_wheel, @object
	.size	log_control_block_mirror_comp_wheel, 11
log_control_block_mirror_comp_wheel:
	.string	"comp_wheel"
	.hidden	log_control_block_comp_wheel
	.globl	log_control_block_comp_wheel
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"comp_wheel"
	.section	.log_filter.comp_wheel,"aw"
	.align	2
	.type	log_control_block_comp_wheel, @object
	.size	log_control_block_comp_wheel, 28
log_control_block_comp_wheel:
	.word	.LC0
	.word	0
	.word	1
	.word	0
	.word	0
	.word	0
	.word	print_module_msgid_log
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_comparator.h"
	.file 5 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpio.h"
	.file 7 "/workdir/airoha/risc-v/middleware/airoha/comp_wheel/inc/comp_wheel.h"
	.file 8 "/workdir/airoha/risc-v/kernel/service/syslog/inc/syslog.h"
	.file 9 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xff9
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x26
	.4byte	.LASF328
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL30
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x6
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x27
	.4byte	.LASF329
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0x9
	.2byte	0x128
	.byte	0x12
	.4byte	0xc8
	.uleb128 0x1
	.4byte	.LASF6
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF7
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF8
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF9
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF10
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF11
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF12
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF13
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF14
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x1f
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.byte	0x6
	.4byte	.LASF25
	.uleb128 0x4
	.4byte	.LASF27
	.byte	0x2
	.byte	0x25
	.byte	0x13
	.4byte	0xdb
	.uleb128 0x6
	.byte	0x2
	.byte	0x5
	.4byte	.LASF26
	.uleb128 0x4
	.4byte	.LASF28
	.byte	0x2
	.byte	0x28
	.byte	0x12
	.4byte	0xee
	.uleb128 0x6
	.byte	0x4
	.byte	0x5
	.4byte	.LASF29
	.uleb128 0x6
	.byte	0x8
	.byte	0x5
	.4byte	.LASF30
	.uleb128 0x4
	.4byte	.LASF31
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x34
	.uleb128 0x4
	.4byte	.LASF32
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x3b
	.uleb128 0x4
	.4byte	.LASF33
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x120
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.4byte	.LASF34
	.uleb128 0x28
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x17
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.2byte	0x1cd
	.4byte	0x262
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x30
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF84
	.byte	0x3
	.2byte	0x1ff
	.4byte	0x12e
	.uleb128 0x17
	.byte	0x7
	.4byte	0x2d
	.byte	0x3
	.2byte	0x407
	.4byte	0x3d2
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF105
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF106
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF137
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF138
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0x38
	.byte	0
	.uleb128 0x6
	.byte	0x10
	.byte	0x4
	.4byte	.LASF142
	.uleb128 0x29
	.byte	0x4
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.4byte	.LASF143
	.uleb128 0x1e
	.4byte	0x3db
	.uleb128 0x9
	.4byte	0x3e2
	.uleb128 0x6
	.byte	0x1
	.byte	0x2
	.4byte	.LASF144
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x53
	.byte	0x1
	.4byte	0x467
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF148
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF149
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF150
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF151
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF152
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF153
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF154
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF155
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF156
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF157
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF158
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF159
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF160
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0x10
	.byte	0
	.uleb128 0x4
	.4byte	.LASF162
	.byte	0x4
	.byte	0x65
	.byte	0x3
	.4byte	0x3f3
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x68
	.byte	0x1
	.4byte	0x4d5
	.uleb128 0x1
	.4byte	.LASF163
	.byte	0
	.uleb128 0x1
	.4byte	.LASF164
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF165
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF166
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF167
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF168
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF169
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF170
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF171
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF172
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF173
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF174
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF175
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF176
	.byte	0xc
	.byte	0
	.uleb128 0x4
	.4byte	.LASF177
	.byte	0x4
	.byte	0x78
	.byte	0x3
	.4byte	0x473
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x7b
	.byte	0x1
	.4byte	0x537
	.uleb128 0x1
	.4byte	.LASF178
	.byte	0
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF180
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF182
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF183
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF184
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF188
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF189
	.byte	0xb
	.byte	0
	.uleb128 0x4
	.4byte	.LASF190
	.byte	0x4
	.byte	0x88
	.byte	0x2
	.4byte	0x4e1
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x8b
	.byte	0x1
	.4byte	0x569
	.uleb128 0x1
	.4byte	.LASF191
	.byte	0
	.uleb128 0x1
	.4byte	.LASF192
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF193
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF194
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF195
	.byte	0x4
	.byte	0x90
	.byte	0x2
	.4byte	0x543
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x93
	.byte	0x1
	.4byte	0x59b
	.uleb128 0x1
	.4byte	.LASF196
	.byte	0
	.uleb128 0x1
	.4byte	.LASF197
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF198
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF199
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF200
	.byte	0x4
	.byte	0x98
	.byte	0x2
	.4byte	0x575
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0x9b
	.byte	0x1
	.4byte	0x5cd
	.uleb128 0x1
	.4byte	.LASF201
	.byte	0
	.uleb128 0x1
	.4byte	.LASF202
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF203
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF204
	.byte	0x2
	.byte	0
	.uleb128 0x4
	.4byte	.LASF205
	.byte	0x4
	.byte	0xa0
	.byte	0x2
	.4byte	0x5a7
	.uleb128 0x12
	.byte	0x20
	.byte	0x4
	.byte	0xa2
	.4byte	0x657
	.uleb128 0x3
	.4byte	.LASF206
	.byte	0x4
	.byte	0xa4
	.byte	0x15
	.4byte	0x5cd
	.byte	0
	.uleb128 0x3
	.4byte	.LASF207
	.byte	0x4
	.byte	0xa5
	.byte	0x19
	.4byte	0x4d5
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF208
	.byte	0x4
	.byte	0xa6
	.byte	0x19
	.4byte	0x537
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF209
	.byte	0x4
	.byte	0xa7
	.byte	0x19
	.4byte	0x537
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF210
	.byte	0x4
	.byte	0xa8
	.byte	0x24
	.4byte	0x467
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF211
	.byte	0x4
	.byte	0xa9
	.byte	0x1b
	.4byte	0x569
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF212
	.byte	0x4
	.byte	0xaa
	.byte	0x22
	.4byte	0x59b
	.byte	0x18
	.uleb128 0x3
	.4byte	.LASF213
	.byte	0x4
	.byte	0xab
	.byte	0xd
	.4byte	0xfc
	.byte	0x1c
	.uleb128 0x3
	.4byte	.LASF214
	.byte	0x4
	.byte	0xac
	.byte	0xd
	.4byte	0xfc
	.byte	0x1d
	.byte	0
	.uleb128 0x4
	.4byte	.LASF215
	.byte	0x4
	.byte	0xad
	.byte	0x3
	.4byte	0x5d9
	.uleb128 0x17
	.byte	0x5
	.4byte	0x127
	.byte	0x5
	.2byte	0x153
	.4byte	0x6a1
	.uleb128 0x8
	.4byte	.LASF216
	.sleb128 -7
	.uleb128 0x8
	.4byte	.LASF217
	.sleb128 -6
	.uleb128 0x8
	.4byte	.LASF218
	.sleb128 -5
	.uleb128 0x8
	.4byte	.LASF219
	.sleb128 -4
	.uleb128 0x8
	.4byte	.LASF220
	.sleb128 -3
	.uleb128 0x8
	.4byte	.LASF221
	.sleb128 -2
	.uleb128 0x8
	.4byte	.LASF222
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF223
	.byte	0
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF224
	.byte	0x5
	.2byte	0x15c
	.4byte	0x663
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.byte	0xda
	.byte	0xe
	.4byte	0x6c7
	.uleb128 0x1
	.4byte	.LASF225
	.byte	0
	.uleb128 0x1
	.4byte	.LASF226
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF227
	.byte	0x6
	.byte	0xdd
	.byte	0x3
	.4byte	0x6ad
	.uleb128 0x7
	.byte	0x5
	.4byte	0x127
	.byte	0x6
	.byte	0xe1
	.byte	0xe
	.4byte	0x6f9
	.uleb128 0x8
	.4byte	.LASF228
	.sleb128 -3
	.uleb128 0x8
	.4byte	.LASF229
	.sleb128 -2
	.uleb128 0x8
	.4byte	.LASF230
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF231
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF232
	.byte	0x6
	.byte	0xe6
	.byte	0x3
	.4byte	0x6d3
	.uleb128 0x7
	.byte	0x5
	.4byte	0x127
	.byte	0x7
	.byte	0x2e
	.byte	0x1
	.4byte	0x725
	.uleb128 0x8
	.4byte	.LASF233
	.sleb128 -2
	.uleb128 0x8
	.4byte	.LASF234
	.sleb128 -1
	.uleb128 0x1
	.4byte	.LASF235
	.byte	0
	.byte	0
	.uleb128 0x4
	.4byte	.LASF236
	.byte	0x7
	.byte	0x32
	.byte	0x3
	.4byte	0x705
	.uleb128 0x4
	.4byte	.LASF237
	.byte	0x7
	.byte	0x34
	.byte	0x10
	.4byte	0x73d
	.uleb128 0x9
	.4byte	0x742
	.uleb128 0x13
	.4byte	0x74d
	.uleb128 0x2
	.4byte	0xcf
	.byte	0
	.uleb128 0x12
	.byte	0x24
	.byte	0x7
	.byte	0x36
	.4byte	0x7d8
	.uleb128 0x3
	.4byte	.LASF238
	.byte	0x7
	.byte	0x38
	.byte	0xe
	.4byte	0x114
	.byte	0
	.uleb128 0x3
	.4byte	.LASF239
	.byte	0x7
	.byte	0x39
	.byte	0x14
	.4byte	0x262
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF240
	.byte	0x7
	.byte	0x3a
	.byte	0x14
	.4byte	0x262
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF241
	.byte	0x7
	.byte	0x3b
	.byte	0x14
	.4byte	0x262
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF242
	.byte	0x7
	.byte	0x3c
	.byte	0x15
	.4byte	0x6c7
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF243
	.byte	0x7
	.byte	0x3d
	.byte	0x15
	.4byte	0x6c7
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF244
	.byte	0x7
	.byte	0x3e
	.byte	0xd
	.4byte	0xe2
	.byte	0x18
	.uleb128 0x3
	.4byte	.LASF245
	.byte	0x7
	.byte	0x3f
	.byte	0xd
	.4byte	0xfc
	.byte	0x1c
	.uleb128 0x3
	.4byte	.LASF246
	.byte	0x7
	.byte	0x40
	.byte	0xd
	.4byte	0xfc
	.byte	0x1d
	.uleb128 0x3
	.4byte	.LASF247
	.byte	0x7
	.byte	0x41
	.byte	0x21
	.4byte	0x731
	.byte	0x20
	.byte	0
	.uleb128 0x4
	.4byte	.LASF248
	.byte	0x7
	.byte	0x42
	.byte	0x3
	.4byte	0x74d
	.uleb128 0x2a
	.4byte	0x7d8
	.uleb128 0x12
	.byte	0xc
	.byte	0x7
	.byte	0x44
	.4byte	0x819
	.uleb128 0x3
	.4byte	.LASF239
	.byte	0x7
	.byte	0x46
	.byte	0x14
	.4byte	0x262
	.byte	0
	.uleb128 0x3
	.4byte	.LASF249
	.byte	0x7
	.byte	0x47
	.byte	0x19
	.4byte	0x537
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF250
	.byte	0x7
	.byte	0x48
	.byte	0x19
	.4byte	0x537
	.byte	0x8
	.byte	0
	.uleb128 0x4
	.4byte	.LASF251
	.byte	0x7
	.byte	0x49
	.byte	0x2
	.4byte	0x7e9
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x37
	.byte	0xe
	.4byte	0x83f
	.uleb128 0x1
	.4byte	.LASF252
	.byte	0
	.uleb128 0x1
	.4byte	.LASF253
	.byte	0x1
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x3d
	.byte	0xe
	.4byte	0x865
	.uleb128 0x1
	.4byte	.LASF254
	.byte	0
	.uleb128 0x1
	.4byte	.LASF255
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF256
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF257
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF258
	.byte	0x8
	.byte	0x42
	.byte	0x3
	.4byte	0x83f
	.uleb128 0x7
	.byte	0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0x45
	.byte	0xe
	.4byte	0x8d9
	.uleb128 0x1
	.4byte	.LASF259
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF260
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF261
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF262
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF263
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF264
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF265
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF266
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF267
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF268
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF269
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF270
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF271
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF272
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF273
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.4byte	.LASF274
	.byte	0x8
	.byte	0x57
	.byte	0x3
	.4byte	0x871
	.uleb128 0x4
	.4byte	.LASF275
	.byte	0x8
	.byte	0x59
	.byte	0x10
	.4byte	0x8f1
	.uleb128 0x9
	.4byte	0x8f6
	.uleb128 0x13
	.4byte	0x916
	.uleb128 0x2
	.4byte	0x3d9
	.uleb128 0x2
	.4byte	0x3e7
	.uleb128 0x2
	.4byte	0x127
	.uleb128 0x2
	.4byte	0x865
	.uleb128 0x2
	.4byte	0x3e7
	.uleb128 0xf
	.byte	0
	.uleb128 0x4
	.4byte	.LASF276
	.byte	0x8
	.byte	0x5a
	.byte	0x10
	.4byte	0x922
	.uleb128 0x9
	.4byte	0x927
	.uleb128 0x13
	.4byte	0x951
	.uleb128 0x2
	.4byte	0x3d9
	.uleb128 0x2
	.4byte	0x3e7
	.uleb128 0x2
	.4byte	0x127
	.uleb128 0x2
	.4byte	0x865
	.uleb128 0x2
	.4byte	0x951
	.uleb128 0x2
	.4byte	0x127
	.uleb128 0x2
	.4byte	0x3e7
	.uleb128 0xf
	.byte	0
	.uleb128 0x9
	.4byte	0x956
	.uleb128 0x2b
	.uleb128 0x4
	.4byte	.LASF277
	.byte	0x8
	.byte	0x5b
	.byte	0x10
	.4byte	0x963
	.uleb128 0x9
	.4byte	0x968
	.uleb128 0x13
	.4byte	0x983
	.uleb128 0x2
	.4byte	0x3d9
	.uleb128 0x2
	.4byte	0x865
	.uleb128 0x2
	.4byte	0x3e7
	.uleb128 0x2
	.4byte	0x114
	.uleb128 0xf
	.byte	0
	.uleb128 0x4
	.4byte	.LASF278
	.byte	0x8
	.byte	0x5c
	.byte	0x14
	.4byte	0x98f
	.uleb128 0x9
	.4byte	0x994
	.uleb128 0x2c
	.4byte	0x114
	.4byte	0x9b7
	.uleb128 0x2
	.4byte	0x3d9
	.uleb128 0x2
	.4byte	0x865
	.uleb128 0x2
	.4byte	0x8d9
	.uleb128 0x2
	.4byte	0x9b7
	.uleb128 0x2
	.4byte	0x9bc
	.byte	0
	.uleb128 0x9
	.4byte	0x951
	.uleb128 0x9
	.4byte	0x114
	.uleb128 0x12
	.byte	0x1c
	.byte	0x8
	.byte	0x5e
	.4byte	0xa25
	.uleb128 0x3
	.4byte	.LASF279
	.byte	0x8
	.byte	0x5f
	.byte	0x11
	.4byte	0x3e7
	.byte	0
	.uleb128 0x3
	.4byte	.LASF280
	.byte	0x8
	.byte	0x60
	.byte	0xe
	.4byte	0x114
	.byte	0x4
	.uleb128 0x3
	.4byte	.LASF281
	.byte	0x8
	.byte	0x61
	.byte	0xe
	.4byte	0x114
	.byte	0x8
	.uleb128 0x3
	.4byte	.LASF282
	.byte	0x8
	.byte	0x62
	.byte	0xf
	.4byte	0x8e5
	.byte	0xc
	.uleb128 0x3
	.4byte	.LASF283
	.byte	0x8
	.byte	0x63
	.byte	0x15
	.4byte	0x916
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF284
	.byte	0x8
	.byte	0x64
	.byte	0x12
	.4byte	0x983
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF285
	.byte	0x8
	.byte	0x65
	.byte	0x10
	.4byte	0x957
	.byte	0x18
	.byte	0
	.uleb128 0x4
	.4byte	.LASF286
	.byte	0x8
	.byte	0x66
	.byte	0x3
	.4byte	0x9c1
	.uleb128 0x1f
	.4byte	.LASF287
	.byte	0x50
	.4byte	0xa25
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_comp_wheel
	.uleb128 0x2d
	.4byte	0x3e2
	.4byte	0xa51
	.uleb128 0x2e
	.4byte	0x2d
	.byte	0xa
	.byte	0
	.uleb128 0x1e
	.4byte	0xa41
	.uleb128 0x1f
	.4byte	.LASF288
	.byte	0x80
	.4byte	0xa51
	.uleb128 0x5
	.byte	0x3
	.4byte	log_control_block_mirror_comp_wheel
	.uleb128 0xa
	.4byte	.LASF289
	.byte	0x29
	.byte	0x29
	.4byte	0x7e4
	.uleb128 0x5
	.byte	0x3
	.4byte	comp_wheel_encoder
	.uleb128 0xa
	.4byte	.LASF290
	.byte	0x2a
	.byte	0x10
	.4byte	0xfc
	.uleb128 0x5
	.byte	0x3
	.4byte	current_state
	.uleb128 0xa
	.4byte	.LASF291
	.byte	0x2b
	.byte	0x10
	.4byte	0xfc
	.uleb128 0x5
	.byte	0x3
	.4byte	last_current_state
	.uleb128 0xa
	.4byte	.LASF292
	.byte	0x2c
	.byte	0x10
	.4byte	0xfc
	.uleb128 0x5
	.byte	0x3
	.4byte	g_comp1_vup_rladder_value
	.uleb128 0xa
	.4byte	.LASF293
	.byte	0x2d
	.byte	0x10
	.4byte	0xfc
	.uleb128 0x5
	.byte	0x3
	.4byte	g_comp1_vdn_rladder_value
	.uleb128 0xa
	.4byte	.LASF294
	.byte	0x2e
	.byte	0x10
	.4byte	0xfc
	.uleb128 0x5
	.byte	0x3
	.4byte	g_comp2_vup_rladder_value
	.uleb128 0xa
	.4byte	.LASF295
	.byte	0x2f
	.byte	0x10
	.4byte	0xfc
	.uleb128 0x5
	.byte	0x3
	.4byte	g_comp2_vdn_rladder_value
	.uleb128 0xa
	.4byte	.LASF296
	.byte	0x30
	.byte	0x10
	.4byte	0xfc
	.uleb128 0x5
	.byte	0x3
	.4byte	g_last_pina_state
	.uleb128 0xa
	.4byte	.LASF297
	.byte	0x31
	.byte	0x10
	.4byte	0xfc
	.uleb128 0x5
	.byte	0x3
	.4byte	g_last_pinb_state
	.uleb128 0x2f
	.4byte	.LASF330
	.byte	0x4
	.byte	0xbc
	.byte	0x6
	.4byte	0xb0d
	.uleb128 0xf
	.byte	0
	.uleb128 0x18
	.4byte	.LASF298
	.byte	0xb7
	.4byte	0xb1d
	.uleb128 0x2
	.4byte	0xb1d
	.byte	0
	.uleb128 0x9
	.4byte	0x657
	.uleb128 0x18
	.4byte	.LASF299
	.byte	0xb6
	.4byte	0xb32
	.uleb128 0x2
	.4byte	0xb1d
	.byte	0
	.uleb128 0x18
	.4byte	.LASF300
	.byte	0xb4
	.4byte	0xb42
	.uleb128 0x2
	.4byte	0x467
	.byte	0
	.uleb128 0x10
	.4byte	.LASF301
	.byte	0xb1
	.uleb128 0x10
	.4byte	.LASF302
	.byte	0xc1
	.uleb128 0x10
	.4byte	.LASF303
	.byte	0xbf
	.uleb128 0x10
	.4byte	.LASF304
	.byte	0xc0
	.uleb128 0x10
	.4byte	.LASF305
	.byte	0xbe
	.uleb128 0x20
	.4byte	.LASF306
	.byte	0x5
	.2byte	0x18d
	.byte	0x12
	.4byte	0x6a1
	.4byte	0xb77
	.uleb128 0x2
	.4byte	0x114
	.byte	0
	.uleb128 0x20
	.4byte	.LASF307
	.byte	0x6
	.2byte	0x13c
	.byte	0x13
	.4byte	0x6f9
	.4byte	0xb93
	.uleb128 0x2
	.4byte	0x262
	.uleb128 0x2
	.4byte	0x6c7
	.byte	0
	.uleb128 0x30
	.4byte	.LASF308
	.byte	0x8
	.2byte	0x129
	.byte	0xd
	.4byte	0xbb6
	.uleb128 0x2
	.4byte	0x3d9
	.uleb128 0x2
	.4byte	0x865
	.uleb128 0x2
	.4byte	0x3e7
	.uleb128 0x2
	.4byte	0x114
	.uleb128 0xf
	.byte	0
	.uleb128 0x31
	.4byte	.LASF310
	.byte	0x1
	.2byte	0x113
	.byte	0x6
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbd7
	.uleb128 0x21
	.4byte	.LVL44
	.4byte	0xaff
	.byte	0
	.uleb128 0x32
	.4byte	.LASF331
	.byte	0x1
	.byte	0xf9
	.byte	0x1b
	.4byte	0x725
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd05
	.uleb128 0x19
	.4byte	.LASF309
	.byte	0xf9
	.byte	0x46
	.4byte	0xd05
	.4byte	.LLST15
	.uleb128 0x19
	.4byte	.LASF247
	.byte	0xf9
	.byte	0x6b
	.4byte	0x731
	.4byte	.LLST16
	.uleb128 0x33
	.4byte	0xeb8
	.4byte	.LBB56
	.4byte	.LLRL17
	.byte	0x1
	.2byte	0x10f
	.byte	0x5
	.uleb128 0x5
	.4byte	0xecd
	.4byte	.LLST18
	.uleb128 0x5
	.4byte	0xec2
	.4byte	.LLST19
	.uleb128 0x11
	.4byte	0xf7f
	.4byte	.LBB58
	.4byte	.LLRL20
	.byte	0x9f
	.byte	0x5
	.4byte	0xc7f
	.uleb128 0x5
	.4byte	0xf94
	.4byte	.LLST21
	.uleb128 0x5
	.4byte	0xf9f
	.4byte	.LLST22
	.uleb128 0x5
	.4byte	0xf89
	.4byte	.LLST23
	.uleb128 0x1a
	.4byte	.LLRL20
	.uleb128 0x22
	.4byte	0xfaa
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x14
	.4byte	.LVL38
	.4byte	0xb22
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	0xf48
	.4byte	.LBB62
	.4byte	.LBE62-.LBB62
	.byte	0xa0
	.4byte	0xcc5
	.uleb128 0x5
	.4byte	0xf5d
	.4byte	.LLST24
	.uleb128 0x5
	.4byte	0xf68
	.4byte	.LLST25
	.uleb128 0x5
	.4byte	0xf52
	.4byte	.LLST26
	.uleb128 0x22
	.4byte	0xf73
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x14
	.4byte	.LVL39
	.4byte	0xb0d
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	0xf01
	.4byte	.LBB64
	.4byte	.LLRL27
	.byte	0xa3
	.byte	0x5
	.4byte	0xceb
	.uleb128 0x5
	.4byte	0xf19
	.4byte	.LLST28
	.uleb128 0x5
	.4byte	0xf0e
	.4byte	.LLST29
	.byte	0
	.uleb128 0x15
	.4byte	.LVL35
	.4byte	0xb42
	.uleb128 0x14
	.4byte	.LVL36
	.4byte	0xb32
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x3f
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0x819
	.uleb128 0x34
	.4byte	.LASF311
	.byte	0x1
	.byte	0xee
	.byte	0x6
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe6a
	.uleb128 0x19
	.4byte	.LASF312
	.byte	0xee
	.byte	0x24
	.4byte	0x108
	.4byte	.LLST3
	.uleb128 0x1b
	.4byte	0xe76
	.4byte	.LBB24
	.4byte	.LBE24-.LBB24
	.byte	0xf1
	.4byte	0xd54
	.uleb128 0x15
	.4byte	.LVL8
	.4byte	0xb5a
	.uleb128 0x15
	.4byte	.LVL9
	.4byte	0xb54
	.byte	0
	.uleb128 0x11
	.4byte	0xe7c
	.4byte	.LBB26
	.4byte	.LLRL4
	.byte	0xf3
	.byte	0x5
	.4byte	0xdea
	.uleb128 0x1a
	.4byte	.LLRL4
	.uleb128 0xe
	.4byte	0xe89
	.4byte	.LLST5
	.uleb128 0xe
	.4byte	0xe94
	.4byte	.LLST6
	.uleb128 0x11
	.4byte	0xed9
	.4byte	.LBB28
	.4byte	.LLRL7
	.byte	0xaa
	.byte	0x1d
	.4byte	0xdaa
	.uleb128 0x5
	.4byte	0xeea
	.4byte	.LLST8
	.uleb128 0x1a
	.4byte	.LLRL7
	.uleb128 0xe
	.4byte	0xef5
	.4byte	.LLST9
	.byte	0
	.byte	0
	.uleb128 0x35
	.4byte	0xe9f
	.4byte	.LBB32
	.4byte	.LBE32-.LBB32
	.4byte	0xdce
	.uleb128 0xe
	.4byte	0xea0
	.4byte	.LLST10
	.uleb128 0xe
	.4byte	0xeab
	.4byte	.LLST11
	.byte	0
	.uleb128 0x36
	.4byte	0xf2b
	.4byte	.LBB33
	.4byte	.LLRL12
	.byte	0x1
	.byte	0xd6
	.byte	0x9
	.uleb128 0x5
	.4byte	0xf3c
	.4byte	.LLST13
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	0xe6a
	.4byte	.LBB40
	.4byte	.LBE40-.LBB40
	.byte	0xf5
	.4byte	0xe0d
	.uleb128 0x37
	.4byte	0xf25
	.4byte	.LBB41
	.4byte	.LBE41-.LBB41
	.byte	0x1
	.byte	0xeb
	.byte	0x5
	.byte	0
	.uleb128 0x11
	.4byte	0xe70
	.4byte	.LBB43
	.4byte	.LLRL14
	.byte	0xf6
	.byte	0x5
	.4byte	0xe33
	.uleb128 0x15
	.4byte	.LVL26
	.4byte	0xb4e
	.uleb128 0x21
	.4byte	.LVL28
	.4byte	0xb48
	.byte	0
	.uleb128 0x23
	.4byte	.LVL7
	.4byte	0xb77
	.4byte	0xe46
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x23
	.4byte	.LVL10
	.4byte	0xb60
	.4byte	0xe5a
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.uleb128 0x14
	.4byte	.LVL24
	.4byte	0xb77
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x24
	.4byte	.LASF321
	.byte	0xe9
	.uleb128 0x25
	.4byte	.LASF313
	.byte	0xe2
	.uleb128 0x25
	.4byte	.LASF314
	.byte	0xdb
	.uleb128 0x38
	.4byte	.LASF332
	.byte	0x1
	.byte	0xa6
	.byte	0xd
	.byte	0x1
	.4byte	0xeb8
	.uleb128 0xc
	.4byte	.LASF242
	.byte	0xa9
	.byte	0xd
	.4byte	0xfc
	.uleb128 0xc
	.4byte	.LASF243
	.byte	0xba
	.byte	0xd
	.4byte	0xfc
	.uleb128 0x39
	.uleb128 0xc
	.4byte	.LASF315
	.byte	0xc5
	.byte	0x12
	.4byte	0x114
	.uleb128 0xc
	.4byte	.LASF316
	.byte	0xc6
	.byte	0x12
	.4byte	0x114
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF323
	.byte	0x9b
	.4byte	0xed9
	.uleb128 0xb
	.4byte	.LASF249
	.byte	0x9b
	.byte	0x35
	.4byte	0x537
	.uleb128 0xb
	.4byte	.LASF250
	.byte	0x9b
	.byte	0x50
	.4byte	0x537
	.byte	0
	.uleb128 0x3a
	.4byte	.LASF317
	.byte	0x1
	.byte	0x93
	.byte	0xa
	.4byte	0x108
	.byte	0x1
	.4byte	0xf01
	.uleb128 0xb
	.4byte	.LASF318
	.byte	0x93
	.byte	0x28
	.4byte	0xfc
	.uleb128 0xc
	.4byte	.LASF319
	.byte	0x95
	.byte	0xe
	.4byte	0x108
	.byte	0
	.uleb128 0x3b
	.4byte	.LASF320
	.byte	0x1
	.byte	0x8e
	.byte	0x6
	.byte	0x1
	.4byte	0xf25
	.uleb128 0xb
	.4byte	.LASF318
	.byte	0x8e
	.byte	0x24
	.4byte	0xfc
	.uleb128 0xb
	.4byte	.LASF319
	.byte	0x8e
	.byte	0x33
	.4byte	0x108
	.byte	0
	.uleb128 0x24
	.4byte	.LASF322
	.byte	0x80
	.uleb128 0x3c
	.4byte	.LASF333
	.byte	0x1
	.byte	0x57
	.byte	0x10
	.4byte	0xe2
	.byte	0x1
	.4byte	0xf48
	.uleb128 0xb
	.4byte	.LASF290
	.byte	0x57
	.byte	0x3b
	.4byte	0xfc
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF324
	.byte	0x45
	.4byte	0xf7f
	.uleb128 0xb
	.4byte	.LASF325
	.byte	0x45
	.byte	0x39
	.4byte	0x537
	.uleb128 0x16
	.string	"vup"
	.byte	0x45
	.byte	0x4a
	.4byte	0xfc
	.uleb128 0x16
	.string	"vdn"
	.byte	0x45
	.byte	0x56
	.4byte	0xfc
	.uleb128 0xc
	.4byte	.LASF326
	.byte	0x47
	.byte	0x1a
	.4byte	0x657
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF327
	.byte	0x33
	.4byte	0xfb6
	.uleb128 0xb
	.4byte	.LASF325
	.byte	0x33
	.byte	0x39
	.4byte	0x537
	.uleb128 0x16
	.string	"vup"
	.byte	0x33
	.byte	0x4a
	.4byte	0xfc
	.uleb128 0x16
	.string	"vdn"
	.byte	0x33
	.byte	0x56
	.4byte	0xfc
	.uleb128 0xc
	.4byte	.LASF326
	.byte	0x35
	.byte	0x1a
	.4byte	0x657
	.byte	0
	.uleb128 0x3d
	.4byte	0xf01
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xfda
	.uleb128 0x5
	.4byte	0xf0e
	.4byte	.LLST0
	.uleb128 0x3e
	.4byte	0xf19
	.uleb128 0x1
	.byte	0x5b
	.byte	0
	.uleb128 0x3f
	.4byte	0xed9
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x5
	.4byte	0xeea
	.4byte	.LLST1
	.uleb128 0xe
	.4byte	0xef5
	.4byte	.LLST2
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
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x6
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
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x1d
	.byte	0x1
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
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 13
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 40
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
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
	.uleb128 0x22
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x23
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
	.uleb128 0x24
	.uleb128 0x2e
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
	.sleb128 13
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 1
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x2e
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
	.sleb128 13
	.uleb128 0x20
	.uleb128 0x21
	.sleb128 1
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x29
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2c
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
	.uleb128 0x2d
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2f
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
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
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
	.uleb128 0x31
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
	.uleb128 0x32
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
	.uleb128 0x33
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x34
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
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x57
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x3a
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3b
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3d
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
	.uleb128 0x3e
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3f
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
.LLST15:
	.byte	0x6
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL32-.LVL31
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL32-.LVL31
	.uleb128 .LVL33-.LVL31
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL33-.LVL31
	.uleb128 .LVL41-.LVL31
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
	.uleb128 .LVL41-.LVL31
	.uleb128 .LVL42-.LVL31
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL42-.LVL31
	.uleb128 .LVL43-.LVL31
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
	.uleb128 .LVL43-.LVL31
	.uleb128 .LFE16-.LVL31
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST16:
	.byte	0x6
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL35-1-.LVL31
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL35-1-.LVL31
	.uleb128 .LVL41-.LVL31
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
	.uleb128 .LVL41-.LVL31
	.uleb128 .LFE16-.LVL31
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST18:
	.byte	0x6
	.4byte	.LVL34
	.byte	0x4
	.uleb128 .LVL34-.LVL34
	.uleb128 .LVL35-1-.LVL34
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL35-1-.LVL34
	.uleb128 .LVL40-.LVL34
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL34
	.byte	0x4
	.uleb128 .LVL34-.LVL34
	.uleb128 .LVL37-.LVL34
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL37-.LVL34
	.uleb128 .LVL38-1-.LVL34
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
.LLST21:
	.byte	0x8
	.4byte	.LVL36
	.uleb128 .LVL38-.LVL36
	.uleb128 0x3
	.byte	0x8
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST22:
	.byte	0x8
	.4byte	.LVL36
	.uleb128 .LVL38-.LVL36
	.uleb128 0x2
	.byte	0x40
	.byte	0x9f
	.byte	0
.LLST23:
	.byte	0x6
	.4byte	.LVL36
	.byte	0x4
	.uleb128 .LVL36-.LVL36
	.uleb128 .LVL37-.LVL36
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL37-.LVL36
	.uleb128 .LVL38-1-.LVL36
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
.LLST24:
	.byte	0x8
	.4byte	.LVL38
	.uleb128 .LVL39-.LVL38
	.uleb128 0x3
	.byte	0x8
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST25:
	.byte	0x8
	.4byte	.LVL38
	.uleb128 .LVL39-.LVL38
	.uleb128 0x2
	.byte	0x40
	.byte	0x9f
	.byte	0
.LLST26:
	.byte	0x8
	.4byte	.LVL38
	.uleb128 .LVL39-.LVL38
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST28:
	.byte	0x8
	.4byte	.LVL39
	.uleb128 .LVL40-.LVL39
	.uleb128 0x2
	.byte	0x33
	.byte	0x9f
	.byte	0
.LLST29:
	.byte	0x8
	.4byte	.LVL39
	.uleb128 .LVL40-.LVL39
	.uleb128 0x3
	.byte	0x8
	.byte	0x21
	.byte	0x9f
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL5
	.byte	0x4
	.uleb128 .LVL5-.LVL5
	.uleb128 .LVL6-.LVL5
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL6-.LVL5
	.uleb128 .LVL27-.LVL5
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL27-.LVL5
	.uleb128 .LFE15-.LVL5
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x3b
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL12
	.byte	0x4
	.uleb128 .LVL12-.LVL12
	.uleb128 .LVL13-.LVL12
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL13-.LVL12
	.uleb128 .LVL19-.LVL12
	.uleb128 0x5
	.byte	0x3
	.4byte	g_last_pina_state
	.byte	0x4
	.uleb128 .LVL28-.LVL12
	.uleb128 .LVL29-.LVL12
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL29-.LVL12
	.uleb128 .LVL30-.LVL12
	.uleb128 0x5
	.byte	0x3
	.4byte	g_last_pina_state
	.byte	0
.LLST6:
	.byte	0x6
	.4byte	.LVL14
	.byte	0x4
	.uleb128 .LVL14-.LVL14
	.uleb128 .LVL20-.LVL14
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL20-.LVL14
	.uleb128 .LVL23-.LVL14
	.uleb128 0x5
	.byte	0x3
	.4byte	g_last_pinb_state
	.byte	0x4
	.uleb128 .LVL29-.LVL14
	.uleb128 .LVL30-.LVL14
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL30-.LVL14
	.uleb128 .LFE15-.LVL14
	.uleb128 0x5
	.byte	0x3
	.4byte	g_last_pinb_state
	.byte	0
.LLST8:
	.byte	0x8
	.4byte	.LVL10
	.uleb128 .LVL11-.LVL10
	.uleb128 0x3
	.byte	0x8
	.byte	0x3b
	.byte	0x9f
	.byte	0
.LLST9:
	.byte	0x8
	.4byte	.LVL10
	.uleb128 .LVL11-.LVL10
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL15
	.byte	0x4
	.uleb128 .LVL15-.LVL15
	.uleb128 .LVL17-.LVL15
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL17-.LVL15
	.uleb128 .LVL19-.LVL15
	.uleb128 0xd
	.byte	0x3
	.4byte	g_comp2_vup_rladder_value
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x38
	.byte	0x24
	.byte	0x9f
	.byte	0
.LLST11:
	.byte	0x8
	.4byte	.LVL16
	.uleb128 .LVL18-.LVL16
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL21
	.byte	0x4
	.uleb128 .LVL21-.LVL21
	.uleb128 .LVL22-.LVL21
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL30-.LVL21
	.uleb128 .LFE15-.LVL21
	.uleb128 0x1
	.byte	0x5f
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
	.uleb128 .LFE8-.LVL0
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
	.uleb128 .LFE9-.LVL2
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
.LLST2:
	.byte	0x6
	.4byte	.LVL2
	.byte	0x4
	.uleb128 .LVL2-.LVL2
	.uleb128 .LVL4-.LVL2
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL4-.LVL2
	.uleb128 .LFE9-.LVL2
	.uleb128 0x1
	.byte	0x5a
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
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
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
.LLRL4:
	.byte	0x5
	.4byte	.LBB26
	.byte	0x4
	.uleb128 .LBB26-.LBB26
	.uleb128 .LBE26-.LBB26
	.byte	0x4
	.uleb128 .LBB39-.LBB26
	.uleb128 .LBE39-.LBB26
	.byte	0x4
	.uleb128 .LBB47-.LBB26
	.uleb128 .LBE47-.LBB26
	.byte	0
.LLRL7:
	.byte	0x5
	.4byte	.LBB28
	.byte	0x4
	.uleb128 .LBB28-.LBB28
	.uleb128 .LBE28-.LBB28
	.byte	0x4
	.uleb128 .LBB31-.LBB28
	.uleb128 .LBE31-.LBB28
	.byte	0
.LLRL12:
	.byte	0x5
	.4byte	.LBB33
	.byte	0x4
	.uleb128 .LBB33-.LBB33
	.uleb128 .LBE33-.LBB33
	.byte	0x4
	.uleb128 .LBB36-.LBB33
	.uleb128 .LBE36-.LBB33
	.byte	0
.LLRL14:
	.byte	0x5
	.4byte	.LBB43
	.byte	0x4
	.uleb128 .LBB43-.LBB43
	.uleb128 .LBE43-.LBB43
	.byte	0x4
	.uleb128 .LBB46-.LBB43
	.uleb128 .LBE46-.LBB43
	.byte	0
.LLRL17:
	.byte	0x5
	.4byte	.LBB56
	.byte	0x4
	.uleb128 .LBB56-.LBB56
	.uleb128 .LBE56-.LBB56
	.byte	0x4
	.uleb128 .LBB70-.LBB56
	.uleb128 .LBE70-.LBB56
	.byte	0x4
	.uleb128 .LBB71-.LBB56
	.uleb128 .LBE71-.LBB56
	.byte	0
.LLRL20:
	.byte	0x5
	.4byte	.LBB58
	.byte	0x4
	.uleb128 .LBB58-.LBB58
	.uleb128 .LBE58-.LBB58
	.byte	0x4
	.uleb128 .LBB61-.LBB58
	.uleb128 .LBE61-.LBB58
	.byte	0
.LLRL27:
	.byte	0x5
	.4byte	.LBB64
	.byte	0x4
	.uleb128 .LBB64-.LBB64
	.uleb128 .LBE64-.LBB64
	.byte	0x4
	.uleb128 .LBB67-.LBB64
	.uleb128 .LBE67-.LBB64
	.byte	0
.LLRL30:
	.byte	0x7
	.4byte	.LFB8
	.uleb128 .LFE8-.LFB8
	.byte	0x7
	.4byte	.LFB9
	.uleb128 .LFE9-.LFB9
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
.LASF243:
	.string	"pinb_state"
.LASF307:
	.string	"hal_gpio_set_output"
.LASF289:
	.string	"comp_wheel_encoder"
.LASF298:
	.string	"hal_comparator_analog_comp2_init"
.LASF105:
	.string	"HAL_EINT_NUMBER_20"
.LASF106:
	.string	"HAL_EINT_NUMBER_21"
.LASF107:
	.string	"HAL_EINT_NUMBER_22"
.LASF108:
	.string	"HAL_EINT_NUMBER_23"
.LASF109:
	.string	"HAL_EINT_NUMBER_24"
.LASF110:
	.string	"HAL_EINT_NUMBER_25"
.LASF16:
	.string	"MCU_DMA_IRQn"
.LASF112:
	.string	"HAL_EINT_NUMBER_27"
.LASF113:
	.string	"HAL_EINT_NUMBER_28"
.LASF114:
	.string	"HAL_EINT_NUMBER_29"
.LASF135:
	.string	"HAL_EINT_UART_2_RX"
.LASF177:
	.string	"hal_comp_mode_cfg_t"
.LASF261:
	.string	"LOG_TYPE_TEXTURE_LOG"
.LASF201:
	.string	"HAL_COMP_1"
.LASF202:
	.string	"HAL_COMP_2"
.LASF272:
	.string	"LOG_TYPE_SYSTEM_INFO"
.LASF254:
	.string	"PRINT_LEVEL_DEBUG"
.LASF136:
	.string	"HAL_EINT_USB0"
.LASF137:
	.string	"HAL_EINT_USB1"
.LASF138:
	.string	"HAL_EINT_USB2"
.LASF3:
	.string	"unsigned int"
.LASF288:
	.string	"log_control_block_mirror_comp_wheel"
.LASF164:
	.string	"HAL_COMP_SE_MODE_REF_ON_NM_MODE"
.LASF285:
	.string	"msg_id_handle"
.LASF306:
	.string	"hal_gpt_delay_us"
.LASF115:
	.string	"HAL_EINT_NUMBER_30"
.LASF116:
	.string	"HAL_EINT_NUMBER_31"
.LASF117:
	.string	"HAL_EINT_NUMBER_32"
.LASF118:
	.string	"HAL_EINT_NUMBER_33"
.LASF119:
	.string	"HAL_EINT_NUMBER_34"
.LASF120:
	.string	"HAL_EINT_NUMBER_35"
.LASF121:
	.string	"HAL_EINT_NUMBER_36"
.LASF122:
	.string	"HAL_EINT_NUMBER_37"
.LASF274:
	.string	"log_type_t"
.LASF124:
	.string	"HAL_EINT_NUMBER_39"
.LASF328:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF332:
	.string	"comp_wheel_get_pin_value"
.LASF246:
	.string	"dpc_state"
.LASF270:
	.string	"LOG_TYPE_MODULE_LOG_DATA"
.LASF11:
	.string	"SPI_MST1_IRQn"
.LASF207:
	.string	"mode"
.LASF234:
	.string	"COMP_WHEEL_STATUS_ERROR"
.LASF23:
	.string	"BT_IRQn"
.LASF240:
	.string	"pina"
.LASF241:
	.string	"pinb"
.LASF195:
	.string	"hal_comp_ref_in_cfg_t"
.LASF303:
	.string	"hal_comp1_disable"
.LASF158:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_VDD"
.LASF205:
	.string	"hal_comp_port_t"
.LASF24:
	.string	"IRQ_NUMBER_MAX"
.LASF125:
	.string	"HAL_EINT_NUMBER_40"
.LASF126:
	.string	"HAL_EINT_NUMBER_41"
.LASF127:
	.string	"HAL_EINT_NUMBER_42"
.LASF237:
	.string	"riscv_comp_wheel_callback_t"
.LASF129:
	.string	"HAL_EINT_NUMBER_44"
.LASF253:
	.string	"DEBUG_LOG_OFF"
.LASF131:
	.string	"HAL_EINT_NUMBER_46"
.LASF132:
	.string	"HAL_EINT_NUMBER_47"
.LASF326:
	.string	"comp_cfg"
.LASF166:
	.string	"HAL_COMP_SE_MODE_REF_OFF_LS_MODE"
.LASF62:
	.string	"HAL_GPIO_27"
.LASF257:
	.string	"PRINT_LEVEL_ERROR"
.LASF266:
	.string	"LOG_TYPE_COMMON_LOG_END"
.LASF33:
	.string	"uint32_t"
.LASF45:
	.string	"HAL_GPIO_10"
.LASF46:
	.string	"HAL_GPIO_11"
.LASF47:
	.string	"HAL_GPIO_12"
.LASF48:
	.string	"HAL_GPIO_13"
.LASF49:
	.string	"HAL_GPIO_14"
.LASF50:
	.string	"HAL_GPIO_15"
.LASF51:
	.string	"HAL_GPIO_16"
.LASF52:
	.string	"HAL_GPIO_17"
.LASF53:
	.string	"HAL_GPIO_18"
.LASF54:
	.string	"HAL_GPIO_19"
.LASF287:
	.string	"log_control_block_comp_wheel"
.LASF277:
	.string	"f_msg_id_t"
.LASF67:
	.string	"HAL_GPIO_32"
.LASF14:
	.string	"UART_DMA_IRQn"
.LASF146:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_1_2"
.LASF150:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_1_8"
.LASF27:
	.string	"int16_t"
.LASF315:
	.string	"vup_mask"
.LASF2:
	.string	"long long unsigned int"
.LASF154:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_8_CP2_2_4"
.LASF278:
	.string	"f_tlv_dump_t"
.LASF179:
	.string	"HAL_GPIO_SEL_GPIO25"
.LASF180:
	.string	"HAL_GPIO_SEL_GPIO26"
.LASF181:
	.string	"HAL_GPIO_SEL_GPIO27"
.LASF182:
	.string	"HAL_GPIO_SEL_GPIO28"
.LASF183:
	.string	"HAL_GPIO_SEL_GPIO29"
.LASF305:
	.string	"hal_comp1_enable"
.LASF55:
	.string	"HAL_GPIO_20"
.LASF56:
	.string	"HAL_GPIO_21"
.LASF57:
	.string	"HAL_GPIO_22"
.LASF58:
	.string	"HAL_GPIO_23"
.LASF59:
	.string	"HAL_GPIO_24"
.LASF60:
	.string	"HAL_GPIO_25"
.LASF61:
	.string	"HAL_GPIO_26"
.LASF267:
	.string	"LOG_TYPE_HCI_DATA"
.LASF63:
	.string	"HAL_GPIO_28"
.LASF64:
	.string	"HAL_GPIO_29"
.LASF174:
	.string	"HAL_COMP_DIFF_MODE_REF_OFF_NM_MODE"
.LASF221:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF184:
	.string	"HAL_GPIO_SEL_GPIO30"
.LASF273:
	.string	"LOG_TYPE_SPECIAL_LOG_END"
.LASF85:
	.string	"HAL_EINT_NUMBER_0"
.LASF86:
	.string	"HAL_EINT_NUMBER_1"
.LASF87:
	.string	"HAL_EINT_NUMBER_2"
.LASF88:
	.string	"HAL_EINT_NUMBER_3"
.LASF89:
	.string	"HAL_EINT_NUMBER_4"
.LASF90:
	.string	"HAL_EINT_NUMBER_5"
.LASF91:
	.string	"HAL_EINT_NUMBER_6"
.LASF92:
	.string	"HAL_EINT_NUMBER_7"
.LASF93:
	.string	"HAL_EINT_NUMBER_8"
.LASF94:
	.string	"HAL_EINT_NUMBER_9"
.LASF72:
	.string	"HAL_GPIO_37"
.LASF308:
	.string	"print_module_msgid_log"
.LASF172:
	.string	"HAL_COMP_DIFF_MODE_REF_ON_HS_MODE"
.LASF269:
	.string	"LOG_TYPE_BT_LMP_LLCP_DATA"
.LASF185:
	.string	"HAL_GPIO_SEL_GPIO31"
.LASF186:
	.string	"HAL_GPIO_SEL_GPIO32"
.LASF187:
	.string	"HAL_GPIO_SEL_GPIO33"
.LASF188:
	.string	"HAL_GPIO_SEL_GPIO34"
.LASF155:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_2_4"
.LASF65:
	.string	"HAL_GPIO_30"
.LASF66:
	.string	"HAL_GPIO_31"
.LASF144:
	.string	"_Bool"
.LASF68:
	.string	"HAL_GPIO_33"
.LASF69:
	.string	"HAL_GPIO_34"
.LASF70:
	.string	"HAL_GPIO_35"
.LASF71:
	.string	"HAL_GPIO_36"
.LASF83:
	.string	"HAL_GPIO_MAX"
.LASF73:
	.string	"HAL_GPIO_38"
.LASF74:
	.string	"HAL_GPIO_39"
.LASF291:
	.string	"last_current_state"
.LASF141:
	.string	"HAL_EINT_NUMBER_MAX"
.LASF214:
	.string	"vdn_rladder_value"
.LASF209:
	.string	"ref_in_gpio"
.LASF263:
	.string	"LOG_TYPE_EXCEPTION_STRING_LOG"
.LASF252:
	.string	"DEBUG_LOG_ON"
.LASF190:
	.string	"hal_comp_gpio_cfg_t"
.LASF204:
	.string	"HAL_COMP_MAX"
.LASF236:
	.string	"riscv_comp_wheel_status_t"
.LASF325:
	.string	"gpio_pin"
.LASF248:
	.string	"risvc_comp_wheel_info_t"
.LASF217:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF203:
	.string	"HAL_COMP_LP"
.LASF75:
	.string	"HAL_GPIO_40"
.LASF76:
	.string	"HAL_GPIO_41"
.LASF77:
	.string	"HAL_GPIO_42"
.LASF264:
	.string	"LOG_TYPE_EXCEPTION_BINARY_LOG"
.LASF331:
	.string	"comp_wheel_init"
.LASF262:
	.string	"LOG_TYPE_MSG_ID_LOG"
.LASF322:
	.string	"comp_wheel_encoder_process_event"
.LASF82:
	.string	"HAL_GPIO_47"
.LASF143:
	.string	"char"
.LASF268:
	.string	"LOG_TYPE_AUDIO_DATA"
.LASF206:
	.string	"comp_port"
.LASF31:
	.string	"uint8_t"
.LASF194:
	.string	"HAL_REF_V_SEL_LP_RLADDER"
.LASF327:
	.string	"comp_wheel_comp1_config"
.LASF165:
	.string	"HAL_COMP_SE_MODE_REF_ON_HS_MODE"
.LASF280:
	.string	"log_switch"
.LASF295:
	.string	"g_comp2_vdn_rladder_value"
.LASF302:
	.string	"hal_comp2_disable"
.LASF78:
	.string	"HAL_GPIO_43"
.LASF6:
	.string	"SW_IRQn"
.LASF80:
	.string	"HAL_GPIO_45"
.LASF81:
	.string	"HAL_GPIO_46"
.LASF242:
	.string	"pina_state"
.LASF35:
	.string	"HAL_GPIO_0"
.LASF36:
	.string	"HAL_GPIO_1"
.LASF275:
	.string	"f_print_t"
.LASF38:
	.string	"HAL_GPIO_3"
.LASF39:
	.string	"HAL_GPIO_4"
.LASF40:
	.string	"HAL_GPIO_5"
.LASF41:
	.string	"HAL_GPIO_6"
.LASF42:
	.string	"HAL_GPIO_7"
.LASF43:
	.string	"HAL_GPIO_8"
.LASF44:
	.string	"HAL_GPIO_9"
.LASF111:
	.string	"HAL_EINT_NUMBER_26"
.LASF134:
	.string	"HAL_EINT_UART_1_RX"
.LASF313:
	.string	"comp_wheel_disable"
.LASF79:
	.string	"HAL_GPIO_44"
.LASF220:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF299:
	.string	"hal_comparator_analog_comp1_init"
.LASF249:
	.string	"up_pin"
.LASF230:
	.string	"HAL_GPIO_STATUS_INVALID_PARAMETER"
.LASF199:
	.string	"HAL_LADDER_REF_V_SEL_VDD"
.LASF30:
	.string	"long long int"
.LASF145:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_1_2"
.LASF176:
	.string	"HAL_COMP_MODE_MAX"
.LASF19:
	.string	"I3C0_DMA_IRQn"
.LASF149:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_1_8"
.LASF84:
	.string	"hal_gpio_pin_t"
.LASF276:
	.string	"f_dump_buffer_t"
.LASF321:
	.string	"comp_wheel_encoder_imp"
.LASF239:
	.string	"pin_led"
.LASF260:
	.string	"LOG_TYPE_INTERNAL_LOG_END"
.LASF304:
	.string	"hal_comp2_enable"
.LASF232:
	.string	"hal_gpio_status_t"
.LASF215:
	.string	"hal_comparator_cfg_t"
.LASF296:
	.string	"g_last_pina_state"
.LASF21:
	.string	"IRQ_GEN_IRQn"
.LASF10:
	.string	"UART_IRQn"
.LASF255:
	.string	"PRINT_LEVEL_INFO"
.LASF317:
	.string	"comp_get_pmu_strup_rg"
.LASF250:
	.string	"down_pin"
.LASF170:
	.string	"HAL_COMP_DIFF_MODE_REF_ON_LS_MODE"
.LASF161:
	.string	"HAL_COMPARATOR_INT_REFF_MAX"
.LASF163:
	.string	"HAL_COMP_SE_MODE_REF_ON_LS_MODE"
.LASF200:
	.string	"hal_comp_ref_ladder_in_cfg_t"
.LASF22:
	.string	"USB_IRQn"
.LASF316:
	.string	"vdn_mask"
.LASF212:
	.string	"ladder_ref_sel"
.LASF123:
	.string	"HAL_EINT_NUMBER_38"
.LASF198:
	.string	"HAL_LADDER_REF_V_SEL_GPIO_IN"
.LASF208:
	.string	"input_gpio"
.LASF300:
	.string	"hal_comparator_analog_int_ref_on"
.LASF189:
	.string	"HAL_GPIO_SEL_MAX"
.LASF226:
	.string	"HAL_GPIO_DATA_HIGH"
.LASF319:
	.string	"data"
.LASF219:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF283:
	.string	"dump_handle"
.LASF175:
	.string	"HAL_COMP_DIFF_MODE_REF_OFF_HS_MODE"
.LASF142:
	.string	"long double"
.LASF294:
	.string	"g_comp2_vup_rladder_value"
.LASF178:
	.string	"HAL_GPIO_SEL_NO"
.LASF329:
	.string	"IRQn"
.LASF311:
	.string	"comp_wheel_scan_once"
.LASF171:
	.string	"HAL_COMP_DIFF_MODE_REF_ON_NM_MODE"
.LASF320:
	.string	"comp_set_pmu_strup_rg"
.LASF216:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF9:
	.string	"KEYSCAN_IRQn"
.LASF284:
	.string	"tlv_dump_handle"
.LASF309:
	.string	"config"
.LASF12:
	.string	"RTC_IRQn"
.LASF256:
	.string	"PRINT_LEVEL_WARNING"
.LASF26:
	.string	"short int"
.LASF167:
	.string	"HAL_COMP_SE_MODE_REF_OFF_NM_MODE"
.LASF223:
	.string	"HAL_GPT_STATUS_OK"
.LASF197:
	.string	"HAL_LADDER_REF_V_SEL_REF_ON_IN"
.LASF29:
	.string	"long int"
.LASF7:
	.string	"LED_IRQn"
.LASF228:
	.string	"HAL_GPIO_STATUS_ERROR"
.LASF233:
	.string	"COMP_WHEEL_STATUS_ERROR_INVALID_PARAMETER"
.LASF227:
	.string	"hal_gpio_data_t"
.LASF17:
	.string	"EINT_IRQn"
.LASF37:
	.string	"HAL_GPIO_2"
.LASF222:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF293:
	.string	"g_comp1_vdn_rladder_value"
.LASF20:
	.string	"SPI_MST0_IRQn"
.LASF13:
	.string	"GPT_IRQn"
.LASF128:
	.string	"HAL_EINT_NUMBER_43"
.LASF130:
	.string	"HAL_EINT_NUMBER_45"
.LASF244:
	.string	"relative_position"
.LASF330:
	.string	"hal_comparator_deinit"
.LASF282:
	.string	"print_handle"
.LASF140:
	.string	"HAL_EINT_RESERVED"
.LASF218:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF290:
	.string	"current_state"
.LASF160:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_VDD"
.LASF229:
	.string	"HAL_GPIO_STATUS_ERROR_PIN"
.LASF286:
	.string	"log_control_block_t"
.LASF211:
	.string	"ref_sel"
.LASF292:
	.string	"g_comp1_vup_rladder_value"
.LASF34:
	.string	"long unsigned int"
.LASF324:
	.string	"comp_wheel_comp2_config"
.LASF231:
	.string	"HAL_GPIO_STATUS_OK"
.LASF28:
	.string	"int32_t"
.LASF333:
	.string	"comp_wheel_encoder_update_position"
.LASF271:
	.string	"LOG_TYPE_AUDIO_V2_DATA"
.LASF224:
	.string	"hal_gpt_status_t"
.LASF32:
	.string	"uint16_t"
.LASF213:
	.string	"vup_rladder_value"
.LASF4:
	.string	"unsigned char"
.LASF156:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_2_4"
.LASF225:
	.string	"HAL_GPIO_DATA_LOW"
.LASF148:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_1_2"
.LASF162:
	.string	"hal_comparator_inter_ref_cfg_t"
.LASF152:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_VDD_CP2_1_8"
.LASF259:
	.string	"LOG_TYPE_INTERNAL_COMMAND"
.LASF245:
	.string	"pc_state"
.LASF251:
	.string	"riscv_comp_wheel_config_t"
.LASF196:
	.string	"HAL_LADDER_REF_V_SEL_AVSS"
.LASF279:
	.string	"module_name"
.LASF318:
	.string	"bank"
.LASF159:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_VDD"
.LASF297:
	.string	"g_last_pinb_state"
.LASF238:
	.string	"scan_cycle_us"
.LASF193:
	.string	"HAL_REF_V_SEL_GPIO_IN"
.LASF247:
	.string	"callback"
.LASF173:
	.string	"HAL_COMP_DIFF_MODE_REF_OFF_LS_MODE"
.LASF265:
	.string	"LOG_TYPE_EXCEPTION_MSGID_LOG"
.LASF18:
	.string	"I3C0_IRQn"
.LASF133:
	.string	"HAL_EINT_UART_0_RX"
.LASF281:
	.string	"print_level"
.LASF312:
	.string	"delay_us"
.LASF153:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_2_4"
.LASF314:
	.string	"comp_wheel_enable"
.LASF301:
	.string	"hal_comparator_analog_power_on"
.LASF25:
	.string	"signed char"
.LASF169:
	.string	"HAL_COMP_SE_MODE_MAX"
.LASF168:
	.string	"HAL_COMP_SE_MODE_REF_OFF_HS_MODE"
.LASF5:
	.string	"short unsigned int"
.LASF192:
	.string	"HAL_REF_V_SEL_INTERNAL_REF_IN"
.LASF15:
	.string	"PMU_IRQn"
.LASF210:
	.string	"internal_ref_cfg"
.LASF139:
	.string	"HAL_EINT_LPCOMP"
.LASF147:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_1_2"
.LASF151:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_2_4_CP2_1_8"
.LASF235:
	.string	"COMP_WHEEL_STATUS_OK"
.LASF157:
	.string	"HAL_COMPARATOR_INT_REFF_ON_CP1_1_2_CP2_VDD"
.LASF95:
	.string	"HAL_EINT_NUMBER_10"
.LASF96:
	.string	"HAL_EINT_NUMBER_11"
.LASF97:
	.string	"HAL_EINT_NUMBER_12"
.LASF98:
	.string	"HAL_EINT_NUMBER_13"
.LASF99:
	.string	"HAL_EINT_NUMBER_14"
.LASF100:
	.string	"HAL_EINT_NUMBER_15"
.LASF101:
	.string	"HAL_EINT_NUMBER_16"
.LASF102:
	.string	"HAL_EINT_NUMBER_17"
.LASF103:
	.string	"HAL_EINT_NUMBER_18"
.LASF104:
	.string	"HAL_EINT_NUMBER_19"
.LASF8:
	.string	"QDEC_IRQn"
.LASF323:
	.string	"comp_wheel_init_imp"
.LASF310:
	.string	"comp_wheel_deinit"
.LASF258:
	.string	"print_level_t"
.LASF191:
	.string	"HAL_REF_V_SEL_RLADDER"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/middleware/airoha/comp_wheel/src/comp_wheel.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
