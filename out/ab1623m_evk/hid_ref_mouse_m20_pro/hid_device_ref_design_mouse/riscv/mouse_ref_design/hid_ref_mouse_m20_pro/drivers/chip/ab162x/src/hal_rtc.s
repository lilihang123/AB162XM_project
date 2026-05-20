	.file	"hal_rtc.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_rtc.c"
	.section	.text.rtc_reset_default_timer,"ax",@progbits
	.align	1
	.globl	rtc_reset_default_timer
	.hidden	rtc_reset_default_timer
	.type	rtc_reset_default_timer, @function
rtc_reset_default_timer:
.LFB4:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_rtc.c"
	.loc 1 53 1
	.cfi_startproc
.LVL0:
	.loc 1 54 5
	.loc 1 54 7 is_stmt 0
	li	a5,2
	.loc 1 55 17
	lw	a4,rtc_base
	.loc 1 54 7
	beq	a0,a5,.L2
	.loc 1 55 9 is_stmt 1
	.loc 1 55 70 is_stmt 0
	slli	a3,a0,8
	add	a2,a4,a3
	lw	a5,12(a2)
	andi	a5,a5,-2
	sw	a5,12(a2)
	.loc 1 56 9 is_stmt 1
	.loc 1 56 59 is_stmt 0
	sw	zero,0(a2)
	.loc 1 57 9 is_stmt 1
	.loc 1 57 59 is_stmt 0
	li	a5,1
	sw	a5,4(a2)
	.loc 1 58 9 is_stmt 1
	.loc 1 58 51 is_stmt 0 discriminator 1
	sll	a0,a5,a0
.LVL1:
.L3:
	.loc 1 58 16 is_stmt 1 discriminator 1
	.loc 1 58 40 is_stmt 0 discriminator 1
	lw	a5,1812(a4)
	.loc 1 58 46 discriminator 1
	and	a5,a5,a0
	.loc 1 58 16 discriminator 1
	beq	a5,zero,.L3
	.loc 1 59 9 is_stmt 1
	.loc 1 59 63 is_stmt 0
	add	a5,a4,a3
	li	a3,1
	sw	a3,20(a5)
	.loc 1 60 9 is_stmt 1
	.loc 1 60 63 is_stmt 0
	li	a3,-1
	sw	a3,28(a5)
	.loc 1 61 9 is_stmt 1
.L4:
	.loc 1 61 16 discriminator 1
	.loc 1 61 42 is_stmt 0 discriminator 1
	lw	a5,1816(a4)
	.loc 1 61 48 discriminator 1
	and	a5,a0,a5
	.loc 1 61 16 discriminator 1
	beq	a5,zero,.L4
	ret
.LVL2:
.L2:
.LBB4:
.LBB5:
	.loc 1 63 9 is_stmt 1
	.loc 1 63 57 is_stmt 0
	li	a5,4096
	add	a5,a4,a5
	lw	a3,-2036(a5)
	andi	a3,a3,-2
	sw	a3,-2036(a5)
	.loc 1 64 9 is_stmt 1
	.loc 1 64 46 is_stmt 0
	sw	zero,-2048(a5)
	.loc 1 65 9 is_stmt 1
	.loc 1 65 46 is_stmt 0
	li	a3,1
	sw	a3,-2044(a5)
	.loc 1 66 9 is_stmt 1
.L5:
	.loc 1 66 16 discriminator 1
	.loc 1 66 43 is_stmt 0 discriminator 1
	lw	a3,-236(a5)
	.loc 1 66 49 discriminator 1
	andi	a3,a3,1
	.loc 1 66 16 discriminator 1
	beq	a3,zero,.L5
	.loc 1 67 9 is_stmt 1
	.loc 1 67 50 is_stmt 0
	li	a3,1
	sw	a3,-2028(a5)
	.loc 1 68 9 is_stmt 1
	.loc 1 68 50 is_stmt 0
	li	a3,-1
	sw	a3,-2020(a5)
	.loc 1 69 9 is_stmt 1
	.loc 1 69 45 is_stmt 0 discriminator 1
	li	a5,4096
	add	a4,a4,a5
.L6:
	.loc 1 69 16 is_stmt 1 discriminator 1
	.loc 1 69 45 is_stmt 0 discriminator 1
	lw	a5,-232(a4)
	.loc 1 69 51 discriminator 1
	andi	a5,a5,1
	.loc 1 69 16 discriminator 1
	beq	a5,zero,.L6
.LBE5:
.LBE4:
	.loc 1 71 1
	ret
	.cfi_endproc
.LFE4:
	.size	rtc_reset_default_timer, .-rtc_reset_default_timer
	.section	.text.hal_rtc_timer_init,"ax",@progbits
	.align	1
	.globl	hal_rtc_timer_init
	.hidden	hal_rtc_timer_init
	.type	hal_rtc_timer_init, @function
hal_rtc_timer_init:
.LFB5:
	.loc 1 75 1 is_stmt 1
	.cfi_startproc
.LVL3:
	.loc 1 76 5
	.loc 1 75 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	sw	s0,12(sp)
	sw	ra,16(sp)
	sw	s1,8(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 76 7
	li	s0,1
	.loc 1 77 16
	li	a5,-3
	.loc 1 76 7
	beq	a0,s0,.L16
	.loc 1 80 5 is_stmt 1
	.loc 1 80 39 is_stmt 0
	slli	a4,a0,4
	lla	s1,g_rtc_context
	sw	a0,4(sp)
	add	a0,s1,a4
.LVL4:
	.loc 1 80 8
	lw	a2,0(a0)
	.loc 1 80 39
	sw	a4,0(sp)
	.loc 1 81 16
	li	a5,-2
	.loc 1 80 8
	beq	a2,s0,.L16
	.loc 1 80 75 discriminator 1
	lbu	a2,12(a0)
	bne	a2,zero,.L16
	.loc 1 84 5 is_stmt 1
	li	a2,16
	li	a1,0
	call	memset
.LVL5:
	.loc 1 85 5
	.loc 1 85 7 is_stmt 0
	lw	a3,4(sp)
	lla	a5,rtc_base
	li	a2,2
	lw	a4,0(sp)
	.loc 1 86 17
	lw	a5,0(a5)
	.loc 1 85 7
	beq	a3,a2,.L18
	.loc 1 86 9 is_stmt 1
	.loc 1 86 67 is_stmt 0
	slli	a2,a3,8
	add	a2,a5,a2
	lw	a1,0(a2)
	li	a0,65536
	.loc 1 87 33
	addi	a5,a5,1792
	.loc 1 86 67
	or	a1,a1,a0
	sw	a1,0(a2)
.LVL6:
	.loc 1 87 9 is_stmt 1
	.loc 1 87 33 is_stmt 0
	lw	a1,8(a5)
	.loc 1 87 46
	sll	s0,s0,a3
	.loc 1 87 42
	not	s0,s0
	.loc 1 87 39
	and	a3,a1,s0
	sw	a3,8(a5)
	.loc 1 88 9 is_stmt 1
	.loc 1 88 36 is_stmt 0
	lw	a3,16(a5)
	.loc 1 88 42
	and	s0,s0,a3
	sw	s0,16(a5)
	.loc 1 90 9 is_stmt 1
	.loc 1 90 70 is_stmt 0
	lw	a5,12(a2)
	andi	a5,a5,-2
	sw	a5,12(a2)
.L19:
	.loc 1 103 5 is_stmt 1
	.loc 1 103 50 is_stmt 0
	li	a5,1
	add	s1,s1,a4
	sb	a5,12(s1)
	.loc 1 104 5 is_stmt 1
	.loc 1 104 12 is_stmt 0
	li	a5,0
.L16:
	.loc 1 105 1
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
	mv	a0,a5
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL7:
.L18:
	.cfi_restore_state
	.loc 1 92 9 is_stmt 1
	.loc 1 92 54 is_stmt 0
	li	a3,4096
	add	a5,a5,a3
	addi	a3,a5,-2048
	lw	a2,0(a3)
	li	a1,65536
	.loc 1 93 36
	addi	a5,a5,-256
	.loc 1 92 54
	or	a2,a2,a1
	sw	a2,0(a3)
.LVL8:
	.loc 1 93 9 is_stmt 1
	.loc 1 93 36 is_stmt 0
	lw	a2,8(a5)
	.loc 1 93 42
	andi	a2,a2,-2
	sw	a2,8(a5)
	.loc 1 94 9 is_stmt 1
	.loc 1 94 39 is_stmt 0
	lw	a2,16(a5)
	.loc 1 94 45
	andi	a2,a2,-2
	sw	a2,16(a5)
	.loc 1 96 9 is_stmt 1
	.loc 1 96 57 is_stmt 0
	lw	a5,12(a3)
	andi	a5,a5,-2
	sw	a5,12(a3)
	j	.L19
	.cfi_endproc
.LFE5:
	.size	hal_rtc_timer_init, .-hal_rtc_timer_init
	.section	.text.hal_rtc_timer_deinit,"ax",@progbits
	.align	1
	.globl	hal_rtc_timer_deinit
	.hidden	hal_rtc_timer_deinit
	.type	hal_rtc_timer_deinit, @function
hal_rtc_timer_deinit:
.LFB6:
	.loc 1 108 1 is_stmt 1
	.cfi_startproc
.LVL9:
	.loc 1 109 5
	.loc 1 108 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	ra,12(sp)
	sw	s1,4(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.cfi_offset 9, -12
	.loc 1 109 7
	li	s0,1
	beq	a0,s0,.L26
	.loc 1 112 38
	slli	a4,a0,4
	lla	a5,g_rtc_context
	add	a5,a5,a4
	.loc 1 112 8
	lw	a4,0(a5)
	mv	s1,a0
	.loc 1 112 5 is_stmt 1
	.loc 1 113 16 is_stmt 0
	li	a0,-2
.LVL10:
	.loc 1 112 8
	beq	a4,s0,.L24
	.loc 1 116 5 is_stmt 1
	li	a2,16
	li	a1,0
	mv	a0,a5
	sw	a5,0(sp)
	call	memset
.LVL11:
	.loc 1 119 5
	.loc 1 119 50 is_stmt 0
	lw	a5,0(sp)
	.loc 1 121 41
	sll	s0,s0,s1
	.loc 1 122 5
	mv	a0,s1
	.loc 1 119 50
	sb	zero,12(a5)
	.loc 1 121 5 is_stmt 1
	.loc 1 121 13 is_stmt 0
	lw	a5,rtc_base
	.loc 1 121 29
	lw	a4,1800(a5)
	.loc 1 121 35
	or	s0,s0,a4
	sw	s0,1800(a5)
	.loc 1 122 5 is_stmt 1
	call	rtc_reset_default_timer
.LVL12:
	.loc 1 127 5
	.loc 1 127 12 is_stmt 0
	li	a0,0
.LVL13:
.L24:
	.loc 1 128 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL14:
.L26:
	.cfi_restore_state
	.loc 1 110 16
	li	a0,-3
.LVL15:
	j	.L24
	.cfi_endproc
.LFE6:
	.size	hal_rtc_timer_deinit, .-hal_rtc_timer_deinit
	.section	.text.hal_rtc_enable_time,"ax",@progbits
	.align	1
	.globl	hal_rtc_enable_time
	.hidden	hal_rtc_enable_time
	.type	hal_rtc_enable_time, @function
hal_rtc_enable_time:
.LFB7:
	.loc 1 129 43 is_stmt 1
	.cfi_startproc
	.loc 1 130 5
	.loc 1 131 5
	.loc 1 129 43 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 131 5
	mv	a0,sp
	.loc 1 129 43
	sw	s0,8(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	.loc 1 132 38
	lla	s0,g_rtc_context
	.loc 1 131 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL16:
	.loc 1 132 5 is_stmt 1
	.loc 1 132 7 is_stmt 0
	lbu	a5,28(s0)
	bne	a5,zero,.L30
	.loc 1 133 9 is_stmt 1
	li	a2,8
	li	a1,0
	lla	a0,sw_rtc_context
	call	memset
.LVL17:
	.loc 1 134 9
	.loc 1 149 13
	.loc 1 149 21 is_stmt 0
	lw	a5,rtc_base
	.loc 1 149 72
	addi	a4,a5,256
	lw	a3,0(a4)
	li	a2,-65536
	addi	a2,a2,-1
	and	a3,a3,a2
	sw	a3,0(a4)
	.loc 1 150 13 is_stmt 1
	.loc 1 150 37 is_stmt 0
	addi	a3,a5,1792
	lw	a2,8(a3)
	.loc 1 150 43
	andi	a2,a2,-3
	sw	a2,8(a3)
	.loc 1 151 13 is_stmt 1
	.loc 1 151 40 is_stmt 0
	lw	a2,16(a3)
	.loc 1 151 46
	andi	a2,a2,-3
	sw	a2,16(a3)
	.loc 1 152 13 is_stmt 1
	.loc 1 152 70 is_stmt 0
	lw	a3,8(a4)
	andi	a3,a3,-32
	ori	a3,a3,16
	sw	a3,8(a4)
	.loc 1 153 13 is_stmt 1
	.loc 1 153 71 is_stmt 0
	lw	a3,0(a4)
	andi	a3,a3,-769
	ori	a3,a3,512
	sw	a3,0(a4)
	.loc 1 154 13 is_stmt 1
	.loc 1 154 64 is_stmt 0
	li	a3,1
	sw	a3,4(a4)
	.loc 1 155 13 is_stmt 1
.L31:
	.loc 1 155 20 discriminator 1
	.loc 1 155 44 is_stmt 0 discriminator 1
	lw	a4,1812(a5)
	.loc 1 155 50 discriminator 1
	andi	a4,a4,2
	.loc 1 155 20 discriminator 1
	beq	a4,zero,.L31
	.loc 1 156 13 is_stmt 1
	.loc 1 156 68 is_stmt 0
	li	a4,1
	sw	a4,276(a5)
	.loc 1 157 13 is_stmt 1
	.loc 1 157 68 is_stmt 0
	li	a4,-1
	sw	a4,284(a5)
	.loc 1 158 13 is_stmt 1
.L32:
	.loc 1 158 20 discriminator 1
	.loc 1 158 46 is_stmt 0 discriminator 1
	lw	a4,1816(a5)
	.loc 1 158 52 discriminator 1
	andi	a4,a4,2
	.loc 1 158 20 discriminator 1
	beq	a4,zero,.L32
	.loc 1 159 13 is_stmt 1
	.loc 1 159 75 is_stmt 0
	addi	a5,a5,256
	lw	a4,12(a5)
	ori	a4,a4,1
	sw	a4,12(a5)
	.loc 1 160 13 is_stmt 1
	.loc 1 160 69 is_stmt 0
	lw	a4,0(a5)
	ori	a4,a4,1
	sw	a4,0(a5)
	.loc 1 162 9 is_stmt 1
	.loc 1 162 66 is_stmt 0
	lla	a5,sw_rtc_callback
	sw	a5,20(s0)
	.loc 1 163 9 is_stmt 1
	.loc 1 163 16 is_stmt 0
	sw	zero,sw_rtc,a5
	.loc 1 164 9 is_stmt 1
	.loc 1 164 67 is_stmt 0
	lla	a5,sw_rtc
	sw	a5,24(s0)
	.loc 1 165 9 is_stmt 1
	call	rtc_nvic_register
.LVL18:
	.loc 1 166 9
	.loc 1 166 55 is_stmt 0
	li	a5,1
	sb	a5,28(s0)
.L30:
	.loc 1 168 5 is_stmt 1
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL19:
	.loc 1 169 5
	.loc 1 170 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE7:
	.size	hal_rtc_enable_time, .-hal_rtc_enable_time
	.section	.text.hal_rtc_disable_time,"ax",@progbits
	.align	1
	.globl	hal_rtc_disable_time
	.hidden	hal_rtc_disable_time
	.type	hal_rtc_disable_time, @function
hal_rtc_disable_time:
.LFB8:
	.loc 1 172 44 is_stmt 1
	.cfi_startproc
	.loc 1 173 5
	.loc 1 174 5
	.loc 1 172 44 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	.loc 1 174 5
	mv	a0,sp
	.loc 1 172 44
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 174 5
	call	hal_nvic_save_and_set_interrupt_mask
.LVL20:
	.loc 1 175 5 is_stmt 1
	.loc 1 175 7 is_stmt 0
	lbu	a5,g_rtc_context+28
	beq	a5,zero,.L39
	.loc 1 176 9 is_stmt 1
	lw	a0,heap
	call	freeMinHeap
.LVL21:
	.loc 1 177 9
	li	a2,16
	li	a1,0
	lla	a0,g_rtc_context+16
	call	memset
.LVL22:
	.loc 1 178 9
	li	a2,8
	li	a1,0
	lla	a0,sw_rtc_context
	call	memset
.LVL23:
	.loc 1 179 9
	li	a0,1
	call	rtc_reset_default_timer
.LVL24:
	.loc 1 180 9
	.loc 1 180 55 is_stmt 0
	sb	zero,g_rtc_context+28,a5
.L39:
	.loc 1 182 5 is_stmt 1
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL25:
	.loc 1 183 5
	.loc 1 184 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE8:
	.size	hal_rtc_disable_time, .-hal_rtc_disable_time
	.section	.text.hal_rtc_alarm_get_handle,"ax",@progbits
	.align	1
	.globl	hal_rtc_alarm_get_handle
	.hidden	hal_rtc_alarm_get_handle
	.type	hal_rtc_alarm_get_handle, @function
hal_rtc_alarm_get_handle:
.LFB9:
	.loc 1 187 1 is_stmt 1
	.cfi_startproc
.LVL26:
	.loc 1 188 5
	.loc 1 189 5
	.loc 1 189 7 is_stmt 0
	lbu	a5,g_rtc_context+28
	beq	a5,zero,.L57
	.loc 1 187 1
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s0,8(sp)
	sw	ra,12(sp)
	.cfi_offset 8, -8
	.cfi_offset 1, -4
	mv	s0,a0
	.loc 1 192 5 is_stmt 1
	.loc 1 187 1 is_stmt 0
	sw	s1,4(sp)
	.cfi_offset 9, -12
	.loc 1 193 16
	li	a0,-1
.LVL27:
	.loc 1 192 8
	beq	s0,zero,.L44
	.loc 1 195 5 is_stmt 1
	.loc 1 195 22 is_stmt 0
	lla	a5,sw_rtc_context
	.loc 1 195 7
	lbu	a4,2(a5)
	lla	s1,heap
	bne	a4,zero,.L48
	.loc 1 196 9 is_stmt 1
	.loc 1 196 16 is_stmt 0
	li	a0,6
	call	createMinHeap
.LVL28:
	.loc 1 196 14 discriminator 1
	sw	a0,0(s1)
	.loc 1 197 9 is_stmt 1
	.loc 1 197 11 is_stmt 0
	beq	a0,zero,.L46
	.loc 1 200 9 is_stmt 1
	.loc 1 200 35 is_stmt 0
	li	a4,1
	lla	a5,sw_rtc_context
	sb	a4,2(a5)
.L48:
	.loc 1 202 5 is_stmt 1
	.loc 1 202 12 is_stmt 0
	lw	a5,0(s1)
	.loc 1 203 16
	li	a0,-4
	.loc 1 202 7
	lb	a4,9(a5)
	li	a5,5
	beq	a4,a5,.L44
	.loc 1 205 5 is_stmt 1
	mv	a0,sp
	call	hal_nvic_save_and_set_interrupt_mask
.LVL29:
	.loc 1 206 5
	.loc 1 206 7 is_stmt 0
	lw	a0,0(s1)
	call	getKey
.LVL30:
	mv	a5,a0
.LVL31:
	.loc 1 207 5 is_stmt 1
	.loc 1 207 7 is_stmt 0
	li	a4,-1
	lw	a0,0(sp)
.LVL32:
	bne	a5,a4,.L50
	.loc 1 208 9 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL33:
	.loc 1 209 9
.L46:
	.loc 1 190 16 is_stmt 0
	li	a0,-2
.L44:
	.loc 1 214 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL34:
	lw	s1,4(sp)
	.cfi_restore 9
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL35:
.L50:
	.cfi_restore_state
	.loc 1 211 5 is_stmt 1
	.loc 1 211 17 is_stmt 0
	li	a4,-1431699456
	or	a5,a5,a4
.LVL36:
	.loc 1 211 13
	sw	a5,0(s0)
	.loc 1 212 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL37:
	.loc 1 213 5
	.loc 1 213 12 is_stmt 0
	li	a0,0
	j	.L44
.LVL38:
.L57:
	.cfi_def_cfa_offset 0
	.cfi_restore 1
	.cfi_restore 8
	.cfi_restore 9
	.loc 1 190 16
	li	a0,-2
.LVL39:
	.loc 1 214 1
	ret
	.cfi_endproc
.LFE9:
	.size	hal_rtc_alarm_get_handle, .-hal_rtc_alarm_get_handle
	.section	.text.hal_rtc_alarm_free_handle,"ax",@progbits
	.align	1
	.globl	hal_rtc_alarm_free_handle
	.hidden	hal_rtc_alarm_free_handle
	.type	hal_rtc_alarm_free_handle, @function
hal_rtc_alarm_free_handle:
.LFB10:
	.loc 1 217 1 is_stmt 1
	.cfi_startproc
.LVL40:
	.loc 1 218 5
	.loc 1 219 5
	.loc 1 217 1 is_stmt 0
	addi	sp,sp,-20
	.cfi_def_cfa_offset 20
	.loc 1 220 17
	li	a5,-1431699456
	.loc 1 217 1
	sw	ra,16(sp)
	sw	s0,12(sp)
	sw	s1,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 219 26
	sw	zero,4(sp)
	.loc 1 220 5 is_stmt 1
	.loc 1 220 17 is_stmt 0
	and	a4,a0,a5
	.loc 1 220 8
	bne	a4,a5,.L64
	.loc 1 223 5 is_stmt 1
	.loc 1 223 7 is_stmt 0
	lbu	a5,sw_rtc_context+2
	bne	a5,zero,.L62
.LVL41:
.L63:
	.loc 1 224 16
	li	a0,-2
.L60:
	.loc 1 235 1
	lw	ra,16(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,12(sp)
	.cfi_restore 8
	lw	s1,8(sp)
	.cfi_restore 9
	addi	sp,sp,20
	.cfi_def_cfa_offset 0
	jr	ra
.LVL42:
.L62:
	.cfi_restore_state
	.loc 1 226 5 is_stmt 1
	.loc 1 227 5
	lla	s1,heap
	.loc 1 226 14 is_stmt 0
	slli	s0,a0,16
	.loc 1 227 5
	lw	a0,0(s1)
.LVL43:
	.loc 1 226 14
	srli	s0,s0,16
	.loc 1 227 5
	addi	a2,sp,4
	mv	a1,s0
	call	statusGetHeap
.LVL44:
	.loc 1 228 5 is_stmt 1
	.loc 1 228 7 is_stmt 0
	lw	a4,4(sp)
	li	a5,1
	bne	a4,a5,.L63
	.loc 1 231 5 is_stmt 1
	mv	a0,sp
	call	hal_nvic_save_and_set_interrupt_mask
.LVL45:
	.loc 1 232 5
	lw	a0,0(s1)
	li	a2,0
	mv	a1,s0
	call	statusChangeHeap
.LVL46:
	.loc 1 233 5
	lw	a0,0(sp)
	call	hal_nvic_restore_interrupt_mask
.LVL47:
	.loc 1 234 5
	.loc 1 234 12 is_stmt 0
	li	a0,0
	j	.L60
.LVL48:
.L64:
	.loc 1 221 16
	li	a0,-1
.LVL49:
	j	.L60
	.cfi_endproc
.LFE10:
	.size	hal_rtc_alarm_free_handle, .-hal_rtc_alarm_free_handle
	.section	.text.hal_rtc_set_alarm_ms,"ax",@progbits
	.align	1
	.globl	hal_rtc_set_alarm_ms
	.hidden	hal_rtc_set_alarm_ms
	.type	hal_rtc_set_alarm_ms, @function
hal_rtc_set_alarm_ms:
.LFB11:
	.loc 1 240 1 is_stmt 1
	.cfi_startproc
.LVL50:
	.loc 1 241 5
	.loc 1 241 7 is_stmt 0
	lbu	a5,sw_rtc_context+2
	beq	a5,zero,.L67
	.loc 1 244 5 is_stmt 1
	.loc 1 244 12 is_stmt 0
	tail	sw_rtc_timer_start
.LVL51:
.L67:
	.loc 1 245 1
	li	a0,-2
.LVL52:
	ret
	.cfi_endproc
.LFE11:
	.size	hal_rtc_set_alarm_ms, .-hal_rtc_set_alarm_ms
	.section	.text.hal_rtc_stop_alarm,"ax",@progbits
	.align	1
	.globl	hal_rtc_stop_alarm
	.hidden	hal_rtc_stop_alarm
	.type	hal_rtc_stop_alarm, @function
hal_rtc_stop_alarm:
.LFB12:
	.loc 1 248 1 is_stmt 1
	.cfi_startproc
.LVL53:
	.loc 1 249 5
	.loc 1 249 7 is_stmt 0
	lbu	a5,sw_rtc_context+2
	beq	a5,zero,.L69
	.loc 1 252 5 is_stmt 1
	.loc 1 252 12 is_stmt 0
	tail	sw_rtc_timer_stop
.LVL54:
.L69:
	.loc 1 253 1
	li	a0,-2
.LVL55:
	ret
	.cfi_endproc
.LFE12:
	.size	hal_rtc_stop_alarm, .-hal_rtc_stop_alarm
	.section	.text.hal_rtc_get_alarm_ms,"ax",@progbits
	.align	1
	.globl	hal_rtc_get_alarm_ms
	.hidden	hal_rtc_get_alarm_ms
	.type	hal_rtc_get_alarm_ms, @function
hal_rtc_get_alarm_ms:
.LFB14:
	.loc 1 269 78 is_stmt 1
	.cfi_startproc
.LVL56:
	.loc 1 270 5
	.loc 1 270 7 is_stmt 0
	lbu	a5,sw_rtc_context+2
	beq	a5,zero,.L71
	.loc 1 273 5 is_stmt 1
	.loc 1 273 12 is_stmt 0
	tail	sw_rtc_get_remaining_time
.LVL57:
.L71:
	.loc 1 274 1
	li	a0,-2
.LVL58:
	ret
	.cfi_endproc
.LFE14:
	.size	hal_rtc_get_alarm_ms, .-hal_rtc_get_alarm_ms
	.section	.text.hal_rtc_set_time,"ax",@progbits
	.align	1
	.globl	hal_rtc_set_time
	.hidden	hal_rtc_set_time
	.type	hal_rtc_set_time, @function
hal_rtc_set_time:
.LFB15:
	.loc 1 275 62 is_stmt 1
	.cfi_startproc
.LVL59:
	.loc 1 276 5
	.loc 1 277 5
	.loc 1 275 62 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	mv	a1,a0
	.loc 1 277 5
	li	a2,10
	lla	a0,init_time
.LVL60:
	.loc 1 275 62
	sw	ra,12(sp)
	.cfi_offset 1, -4
	.loc 1 277 5
	call	memcpy
.LVL61:
	.loc 1 278 5 is_stmt 1
	mv	a0,sp
	call	hal_nvic_save_and_set_interrupt_mask
.LVL62:
	.loc 1 279 5
	.loc 1 279 34 is_stmt 0
	li	a0,1
	call	hal_rtc_get_current
.LVL63:
	.loc 1 279 32 discriminator 1
	lla	a5,sw_rtc_context
	.loc 1 280 35
	lbu	a4,0(a5)
	.loc 1 279 32 discriminator 1
	sw	a0,4(a5)
	.loc 1 280 5 is_stmt 1
	.loc 1 281 5 is_stmt 0
	lw	a0,0(sp)
	.loc 1 280 35
	sb	a4,1(a5)
	.loc 1 281 5 is_stmt 1
	call	hal_nvic_restore_interrupt_mask
.LVL64:
	.loc 1 282 5
	.loc 1 283 1 is_stmt 0
	lw	ra,12(sp)
	.cfi_restore 1
	li	a0,0
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE15:
	.size	hal_rtc_set_time, .-hal_rtc_set_time
	.section	.text.hal_rtc_get_time,"ax",@progbits
	.align	1
	.globl	hal_rtc_get_time
	.hidden	hal_rtc_get_time
	.type	hal_rtc_get_time, @function
hal_rtc_get_time:
.LFB16:
	.loc 1 285 57 is_stmt 1
	.cfi_startproc
.LVL65:
	.loc 1 286 5
	.loc 1 287 5
	.loc 1 287 14 is_stmt 0
	tail	rtc_get_time
.LVL66:
	.cfi_endproc
.LFE16:
	.size	hal_rtc_get_time, .-hal_rtc_get_time
	.section	.text.hal_rtc_set_alarm,"ax",@progbits
	.align	1
	.globl	hal_rtc_set_alarm
	.hidden	hal_rtc_set_alarm
	.type	hal_rtc_set_alarm, @function
hal_rtc_set_alarm:
.LFB13:
	.loc 1 256 1 is_stmt 1
	.cfi_startproc
.LVL67:
	.loc 1 257 5
	.loc 1 256 1 is_stmt 0
	addi	sp,sp,-36
	.cfi_def_cfa_offset 36
	sw	a0,0(sp)
	.loc 1 257 32
	mv	a0,a1
.LVL68:
	.loc 1 256 1
	sw	ra,32(sp)
	sw	s0,28(sp)
	sw	s1,24(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.cfi_offset 9, -12
	.loc 1 256 1
	sw	a2,4(sp)
	sw	a3,8(sp)
	.loc 1 257 32
	call	rtc_time_diff
.LVL69:
	mv	s1,a0
	.loc 1 259 5
	addi	a0,sp,12
	.loc 1 257 32
	mv	s0,a1
.LVL70:
	.loc 1 258 5 is_stmt 1
	.loc 1 259 5
	call	hal_rtc_get_time
.LVL71:
	.loc 1 260 5
	.loc 1 260 32 is_stmt 0
	addi	a0,sp,12
	call	rtc_time_diff
.LVL72:
	.loc 1 261 5 is_stmt 1
	.loc 1 261 7 is_stmt 0
	bgtu	a1,s0,.L78
	lw	a4,8(sp)
	mv	a3,a1
	bne	a1,s0,.L79
	bgtu	a0,s1,.L78
.L79:
	.loc 1 264 9 is_stmt 1
.LVL73:
	.loc 1 266 5
	.loc 1 264 25 is_stmt 0
	sub	a1,s1,a0
.LVL74:
	sub	a2,s0,a3
	.loc 1 266 12
	lw	a0,0(sp)
.LVL75:
	lw	a3,4(sp)
	.loc 1 264 25
	sgtu	a5,a1,s1
	.loc 1 266 12
	sub	a2,a2,a5
	call	hal_rtc_set_alarm_ms
.LVL76:
.L75:
	.loc 1 267 1
	lw	ra,32(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,28(sp)
	.cfi_restore 8
	lw	s1,24(sp)
	.cfi_restore 9
	addi	sp,sp,36
	.cfi_def_cfa_offset 0
.LVL77:
	jr	ra
.LVL78:
.L78:
	.cfi_restore_state
	.loc 1 262 16
	li	a0,-1
.LVL79:
	j	.L75
	.cfi_endproc
.LFE13:
	.size	hal_rtc_set_alarm, .-hal_rtc_set_alarm
	.section	.text.hal_rtc_get_alarm,"ax",@progbits
	.align	1
	.globl	hal_rtc_get_alarm
	.hidden	hal_rtc_get_alarm
	.type	hal_rtc_get_alarm, @function
hal_rtc_get_alarm:
.LFB17:
	.loc 1 291 74 is_stmt 1
	.cfi_startproc
.LVL80:
	.loc 1 292 5
	.loc 1 293 5
	.loc 1 294 5
	.loc 1 291 74 is_stmt 0
	addi	sp,sp,-52
	.cfi_def_cfa_offset 52
	sw	s0,44(sp)
	.cfi_offset 8, -8
	addi	s0,sp,35
	andi	s0,s0,-8
	sw	s1,40(sp)
	.cfi_offset 9, -12
	mv	s1,a1
	.loc 1 294 14
	mv	a1,s0
.LVL81:
	.loc 1 291 74
	sw	ra,48(sp)
	.cfi_offset 1, -4
	.loc 1 294 14
	call	sw_rtc_get_remaining_time
.LVL82:
	.loc 1 295 5 is_stmt 1
	.loc 1 295 7 is_stmt 0
	bne	a0,zero,.L81
	.loc 1 298 5 is_stmt 1
	.loc 1 299 5
	li	a2,10
	li	a1,0
	addi	a0,sp,16
.LVL83:
	call	memset
.LVL84:
	.loc 1 300 5
	.loc 1 300 12 is_stmt 0
	li	a2,10
	addi	a1,sp,16
	mv	a0,sp
	call	memcpy
.LVL85:
	lw	a2,0(s0)
	lw	a3,4(s0)
	mv	a1,sp
	mv	a0,s1
	call	rtc_get_time_change
.LVL86:
.L81:
	.loc 1 301 1
	lw	ra,48(sp)
	.cfi_restore 1
	lw	s0,44(sp)
	.cfi_restore 8
	lw	s1,40(sp)
	.cfi_restore 9
.LVL87:
	addi	sp,sp,52
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE17:
	.size	hal_rtc_get_alarm, .-hal_rtc_get_alarm
	.hidden	init_time
	.globl	init_time
	.section	.data.init_time,"aw"
	.align	2
	.type	init_time, @object
	.size	init_time, 10
init_time:
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	1
	.half	2024
	.half	0
	.hidden	heap
	.globl	heap
	.section	.sbss.heap,"aw",@nobits
	.align	2
	.type	heap, @object
	.size	heap, 4
heap:
	.zero	4
	.hidden	rtc_unit
	.globl	rtc_unit
	.section	.sdata.rtc_unit,"aw"
	.align	1
	.type	rtc_unit, @object
	.size	rtc_unit, 2
rtc_unit:
	.half	1
	.hidden	sw_rtc
	.globl	sw_rtc
	.section	.sbss.sw_rtc,"aw",@nobits
	.align	2
	.type	sw_rtc, @object
	.size	sw_rtc, 4
sw_rtc:
	.zero	4
	.hidden	sw_rtc_context
	.globl	sw_rtc_context
	.section	.sbss.sw_rtc_context,"aw",@nobits
	.align	2
	.type	sw_rtc_context, @object
	.size	sw_rtc_context, 8
sw_rtc_context:
	.zero	8
	.hidden	g_rtc_context
	.globl	g_rtc_context
	.section	.bss.g_rtc_context,"aw",@nobits
	.align	2
	.type	g_rtc_context, @object
	.size	g_rtc_context, 48
g_rtc_context:
	.zero	48
	.hidden	rtc_base
	.globl	rtc_base
	.section	.sdata.rtc_base,"aw"
	.align	2
	.type	rtc_base, @object
	.size	rtc_base, 4
rtc_base:
	.word	1108344832
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rtc_timer.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 5 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_rtc.h"
	.file 7 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_rtc_internal.h"
	.file 8 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.file 9 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_nvic.h"
	.file 10 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.file 11 "<built-in>"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1466
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x27
	.4byte	.LASF206
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL25
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0xd
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0xd
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x28
	.4byte	.LASF207
	.byte	0x7
	.byte	0x4
	.4byte	0x2d
	.byte	0xa
	.2byte	0x128
	.byte	0x12
	.4byte	0xba
	.uleb128 0x3
	.4byte	.LASF4
	.byte	0x3
	.uleb128 0x3
	.4byte	.LASF5
	.byte	0x7
	.uleb128 0x3
	.4byte	.LASF6
	.byte	0xb
	.uleb128 0x3
	.4byte	.LASF7
	.byte	0x10
	.uleb128 0x3
	.4byte	.LASF8
	.byte	0x11
	.uleb128 0x3
	.4byte	.LASF9
	.byte	0x12
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x13
	.uleb128 0x3
	.4byte	.LASF11
	.byte	0x14
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x15
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x16
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x17
	.uleb128 0x3
	.4byte	.LASF15
	.byte	0x18
	.uleb128 0x3
	.4byte	.LASF16
	.byte	0x19
	.uleb128 0x3
	.4byte	.LASF17
	.byte	0x1a
	.uleb128 0x3
	.4byte	.LASF18
	.byte	0x1b
	.uleb128 0x3
	.4byte	.LASF19
	.byte	0x1c
	.uleb128 0x3
	.4byte	.LASF20
	.byte	0x1d
	.uleb128 0x3
	.4byte	.LASF21
	.byte	0x1e
	.uleb128 0x3
	.4byte	.LASF22
	.byte	0x1f
	.byte	0
	.uleb128 0x5
	.4byte	.LASF25
	.byte	0x2
	.byte	0x22
	.byte	0x15
	.4byte	0xc6
	.uleb128 0xd
	.byte	0x1
	.byte	0x6
	.4byte	.LASF23
	.uleb128 0xd
	.byte	0x2
	.byte	0x5
	.4byte	.LASF24
	.uleb128 0x5
	.4byte	.LASF26
	.byte	0x2
	.byte	0x28
	.byte	0x12
	.4byte	0xe0
	.uleb128 0xd
	.byte	0x4
	.byte	0x5
	.4byte	.LASF27
	.uleb128 0xd
	.byte	0x8
	.byte	0x5
	.4byte	.LASF28
	.uleb128 0x5
	.4byte	.LASF29
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0xfa
	.uleb128 0xd
	.byte	0x1
	.byte	0x8
	.4byte	.LASF30
	.uleb128 0x5
	.4byte	.LASF31
	.byte	0x2
	.byte	0x31
	.byte	0x1c
	.4byte	0x10d
	.uleb128 0xd
	.byte	0x2
	.byte	0x7
	.4byte	.LASF32
	.uleb128 0x5
	.4byte	.LASF33
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x12a
	.uleb128 0x29
	.4byte	0x114
	.uleb128 0x22
	.4byte	0x120
	.uleb128 0xd
	.byte	0x4
	.byte	0x7
	.4byte	.LASF34
	.uleb128 0x5
	.4byte	.LASF35
	.byte	0x2
	.byte	0x37
	.byte	0x20
	.4byte	0x26
	.uleb128 0x2a
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0x29
	.byte	0x5
	.4byte	0x19d
	.uleb128 0x2b
	.string	"EN0"
	.byte	0x3
	.byte	0x2a
	.byte	0x1b
	.4byte	0x120
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0x2b
	.byte	0x21
	.4byte	0x125
	.byte	0x7
	.byte	0x1
	.uleb128 0x4
	.4byte	.LASF37
	.byte	0x2c
	.byte	0x1b
	.4byte	0x120
	.byte	0x2
	.byte	0x8
	.uleb128 0x4
	.4byte	.LASF38
	.byte	0x2d
	.byte	0x21
	.4byte	0x125
	.byte	0x6
	.byte	0xa
	.uleb128 0x4
	.4byte	.LASF39
	.byte	0x2e
	.byte	0x1b
	.4byte	0x120
	.byte	0x1
	.byte	0x10
	.uleb128 0x4
	.4byte	.LASF40
	.byte	0x2f
	.byte	0x21
	.4byte	0x125
	.byte	0xf
	.byte	0x11
	.byte	0
	.uleb128 0xa
	.byte	0x28
	.4byte	0x1ba
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0x30
	.byte	0x7
	.4byte	0x144
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0x31
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF43
	.byte	0x3
	.byte	0x32
	.byte	0x3
	.4byte	0x19d
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0x3e
	.byte	0x5
	.4byte	0x1ea
	.uleb128 0x4
	.4byte	.LASF44
	.byte	0x3f
	.byte	0x1b
	.4byte	0x120
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0x40
	.byte	0x21
	.4byte	0x125
	.byte	0x1f
	.byte	0x1
	.byte	0
	.uleb128 0xa
	.byte	0x3d
	.4byte	0x207
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0x41
	.byte	0x7
	.4byte	0x1c6
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0x42
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF45
	.byte	0x3
	.byte	0x43
	.byte	0x3
	.4byte	0x1ea
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0x4b
	.byte	0x5
	.4byte	0x237
	.uleb128 0x4
	.4byte	.LASF46
	.byte	0x4c
	.byte	0x1b
	.4byte	0x120
	.byte	0x5
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0x4d
	.byte	0x21
	.4byte	0x125
	.byte	0x1b
	.byte	0x5
	.byte	0
	.uleb128 0xa
	.byte	0x4a
	.4byte	0x254
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0x4e
	.byte	0x7
	.4byte	0x213
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0x4f
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF47
	.byte	0x3
	.byte	0x50
	.byte	0x3
	.4byte	0x237
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0x58
	.byte	0x5
	.4byte	0x284
	.uleb128 0x4
	.4byte	.LASF48
	.byte	0x59
	.byte	0x1b
	.4byte	0x120
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0x5a
	.byte	0x21
	.4byte	0x125
	.byte	0x1f
	.byte	0x1
	.byte	0
	.uleb128 0xa
	.byte	0x57
	.4byte	0x2a1
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0x5b
	.byte	0x7
	.4byte	0x260
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0x5c
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF49
	.byte	0x3
	.byte	0x5d
	.byte	0x3
	.4byte	0x284
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0x65
	.byte	0x5
	.4byte	0x2d1
	.uleb128 0x4
	.4byte	.LASF50
	.byte	0x66
	.byte	0x21
	.4byte	0x125
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0x67
	.byte	0x21
	.4byte	0x125
	.byte	0x1f
	.byte	0x1
	.byte	0
	.uleb128 0xa
	.byte	0x64
	.4byte	0x2ee
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0x68
	.byte	0x7
	.4byte	0x2ad
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0x69
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF51
	.byte	0x3
	.byte	0x6a
	.byte	0x3
	.4byte	0x2d1
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0x72
	.byte	0x5
	.4byte	0x31e
	.uleb128 0x4
	.4byte	.LASF52
	.byte	0x73
	.byte	0x1b
	.4byte	0x120
	.byte	0x1
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0x74
	.byte	0x21
	.4byte	0x125
	.byte	0x1f
	.byte	0x1
	.byte	0
	.uleb128 0xa
	.byte	0x71
	.4byte	0x33b
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0x75
	.byte	0x7
	.4byte	0x2fa
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0x76
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF53
	.byte	0x3
	.byte	0x77
	.byte	0x3
	.4byte	0x31e
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0x7f
	.byte	0x5
	.4byte	0x35e
	.uleb128 0x4
	.4byte	.LASF54
	.byte	0x80
	.byte	0x21
	.4byte	0x125
	.byte	0x20
	.byte	0
	.byte	0
	.uleb128 0xa
	.byte	0x7e
	.4byte	0x37b
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0x81
	.byte	0x7
	.4byte	0x347
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0x82
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF55
	.byte	0x3
	.byte	0x83
	.byte	0x3
	.4byte	0x35e
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0x8b
	.byte	0x5
	.4byte	0x39e
	.uleb128 0x4
	.4byte	.LASF56
	.byte	0x8c
	.byte	0x1b
	.4byte	0x120
	.byte	0x20
	.byte	0
	.byte	0
	.uleb128 0xa
	.byte	0x8a
	.4byte	0x3bb
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0x8d
	.byte	0x7
	.4byte	0x387
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0x8e
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF57
	.byte	0x3
	.byte	0x8f
	.byte	0x3
	.4byte	0x39e
	.uleb128 0x23
	.2byte	0x100
	.byte	0x94
	.4byte	0x445
	.uleb128 0x7
	.4byte	.LASF58
	.byte	0x3
	.byte	0x95
	.byte	0xf
	.4byte	0x1ba
	.byte	0
	.uleb128 0x7
	.4byte	.LASF59
	.byte	0x3
	.byte	0x96
	.byte	0xf
	.4byte	0x207
	.byte	0x4
	.uleb128 0x7
	.4byte	.LASF60
	.byte	0x3
	.byte	0x97
	.byte	0xf
	.4byte	0x254
	.byte	0x8
	.uleb128 0x7
	.4byte	.LASF61
	.byte	0x3
	.byte	0x98
	.byte	0x12
	.4byte	0x2a1
	.byte	0xc
	.uleb128 0x7
	.4byte	.LASF62
	.byte	0x3
	.byte	0x99
	.byte	0x13
	.4byte	0x2ee
	.byte	0x10
	.uleb128 0x7
	.4byte	.LASF63
	.byte	0x3
	.byte	0x9a
	.byte	0x13
	.4byte	0x33b
	.byte	0x14
	.uleb128 0x7
	.4byte	.LASF64
	.byte	0x3
	.byte	0x9b
	.byte	0x11
	.4byte	0x37b
	.byte	0x18
	.uleb128 0x7
	.4byte	.LASF65
	.byte	0x3
	.byte	0x9c
	.byte	0x13
	.4byte	0x3bb
	.byte	0x1c
	.uleb128 0x7
	.4byte	.LASF36
	.byte	0x3
	.byte	0x9d
	.byte	0xe
	.4byte	0x445
	.byte	0x20
	.byte	0
	.uleb128 0x14
	.4byte	0x114
	.4byte	0x455
	.uleb128 0x19
	.4byte	0x2d
	.byte	0x37
	.byte	0
	.uleb128 0x5
	.4byte	.LASF66
	.byte	0x3
	.byte	0x9e
	.byte	0x2
	.4byte	0x3c7
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0xa2
	.byte	0x5
	.4byte	0x485
	.uleb128 0x4
	.4byte	.LASF67
	.byte	0xa3
	.byte	0x21
	.4byte	0x125
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0xa4
	.byte	0x21
	.4byte	0x125
	.byte	0x1d
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.byte	0xa1
	.4byte	0x4a2
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0xa5
	.byte	0x7
	.4byte	0x461
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0xa6
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF68
	.byte	0x3
	.byte	0xa7
	.byte	0x3
	.4byte	0x485
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0xaf
	.byte	0x5
	.4byte	0x4d2
	.uleb128 0x4
	.4byte	.LASF69
	.byte	0xb0
	.byte	0x1b
	.4byte	0x120
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0xb1
	.byte	0x21
	.4byte	0x125
	.byte	0x1d
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.byte	0xae
	.4byte	0x4ef
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0xb2
	.byte	0x7
	.4byte	0x4ae
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0xb3
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF70
	.byte	0x3
	.byte	0xb4
	.byte	0x3
	.4byte	0x4d2
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0xbc
	.byte	0x5
	.4byte	0x51f
	.uleb128 0x4
	.4byte	.LASF71
	.byte	0xbd
	.byte	0x1b
	.4byte	0x120
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0xbe
	.byte	0x21
	.4byte	0x125
	.byte	0x1d
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.byte	0xbb
	.4byte	0x53c
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0xbf
	.byte	0x7
	.4byte	0x4fb
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0xc0
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF72
	.byte	0x3
	.byte	0xc1
	.byte	0x3
	.4byte	0x51f
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0xc9
	.byte	0x5
	.4byte	0x56c
	.uleb128 0x4
	.4byte	.LASF73
	.byte	0xca
	.byte	0x1b
	.4byte	0x120
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0xcb
	.byte	0x21
	.4byte	0x125
	.byte	0x1d
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.byte	0xc8
	.4byte	0x589
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0xcc
	.byte	0x7
	.4byte	0x548
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0xcd
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF74
	.byte	0x3
	.byte	0xce
	.byte	0x3
	.4byte	0x56c
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0xd6
	.byte	0x5
	.4byte	0x5b9
	.uleb128 0x4
	.4byte	.LASF75
	.byte	0xd7
	.byte	0x1b
	.4byte	0x120
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0xd8
	.byte	0x21
	.4byte	0x125
	.byte	0x1d
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.byte	0xd5
	.4byte	0x5d6
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0xd9
	.byte	0x7
	.4byte	0x595
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0xda
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF76
	.byte	0x3
	.byte	0xdb
	.byte	0x3
	.4byte	0x5b9
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0xe3
	.byte	0x5
	.4byte	0x606
	.uleb128 0x4
	.4byte	.LASF77
	.byte	0xe4
	.byte	0x21
	.4byte	0x125
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0xe5
	.byte	0x21
	.4byte	0x125
	.byte	0x1d
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.byte	0xe2
	.4byte	0x623
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0xe6
	.byte	0x7
	.4byte	0x5e2
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0xe7
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF78
	.byte	0x3
	.byte	0xe8
	.byte	0x3
	.4byte	0x606
	.uleb128 0x9
	.byte	0x4
	.byte	0x3
	.byte	0xf0
	.byte	0x5
	.4byte	0x653
	.uleb128 0x4
	.4byte	.LASF79
	.byte	0xf1
	.byte	0x21
	.4byte	0x125
	.byte	0x3
	.byte	0
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0xf2
	.byte	0x21
	.4byte	0x125
	.byte	0x1d
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.byte	0xef
	.4byte	0x670
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0xf3
	.byte	0x7
	.4byte	0x62f
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0xf4
	.byte	0x17
	.4byte	0x120
	.byte	0
	.uleb128 0x5
	.4byte	.LASF80
	.byte	0x3
	.byte	0xf5
	.byte	0x3
	.4byte	0x653
	.uleb128 0x23
	.2byte	0xf1c
	.byte	0xfb
	.4byte	0x78b
	.uleb128 0x7
	.4byte	.LASF81
	.byte	0x3
	.byte	0xfc
	.byte	0x12
	.4byte	0x78b
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF40
	.byte	0xfd
	.byte	0xe
	.4byte	0x79b
	.2byte	0x200
	.uleb128 0x1f
	.4byte	.LASF82
	.byte	0xfe
	.byte	0x14
	.4byte	0x4a2
	.2byte	0x700
	.uleb128 0x1f
	.4byte	.LASF83
	.byte	0xff
	.byte	0x16
	.4byte	0x4ef
	.2byte	0x704
	.uleb128 0xb
	.4byte	.LASF84
	.2byte	0x100
	.byte	0x16
	.4byte	0x53c
	.2byte	0x708
	.uleb128 0xb
	.4byte	.LASF85
	.2byte	0x101
	.byte	0x19
	.4byte	0x589
	.2byte	0x70c
	.uleb128 0xb
	.4byte	.LASF86
	.2byte	0x102
	.byte	0x19
	.4byte	0x5d6
	.2byte	0x710
	.uleb128 0xb
	.4byte	.LASF87
	.2byte	0x103
	.byte	0x14
	.4byte	0x623
	.2byte	0x714
	.uleb128 0xb
	.4byte	.LASF88
	.2byte	0x104
	.byte	0x16
	.4byte	0x670
	.2byte	0x718
	.uleb128 0xb
	.4byte	.LASF89
	.2byte	0x105
	.byte	0xe
	.4byte	0x7ac
	.2byte	0x71c
	.uleb128 0xb
	.4byte	.LASF90
	.2byte	0x106
	.byte	0x12
	.4byte	0x455
	.2byte	0x800
	.uleb128 0xb
	.4byte	.LASF91
	.2byte	0x107
	.byte	0xe
	.4byte	0x7bc
	.2byte	0x900
	.uleb128 0xb
	.4byte	.LASF92
	.2byte	0x108
	.byte	0x14
	.4byte	0x4a2
	.2byte	0xf00
	.uleb128 0xb
	.4byte	.LASF93
	.2byte	0x109
	.byte	0x16
	.4byte	0x4ef
	.2byte	0xf04
	.uleb128 0xb
	.4byte	.LASF94
	.2byte	0x10a
	.byte	0x16
	.4byte	0x53c
	.2byte	0xf08
	.uleb128 0xb
	.4byte	.LASF95
	.2byte	0x10b
	.byte	0x19
	.4byte	0x589
	.2byte	0xf0c
	.uleb128 0xb
	.4byte	.LASF96
	.2byte	0x10c
	.byte	0x19
	.4byte	0x5d6
	.2byte	0xf10
	.uleb128 0xb
	.4byte	.LASF97
	.2byte	0x10d
	.byte	0x14
	.4byte	0x623
	.2byte	0xf14
	.uleb128 0xb
	.4byte	.LASF98
	.2byte	0x10e
	.byte	0x16
	.4byte	0x670
	.2byte	0xf18
	.byte	0
	.uleb128 0x14
	.4byte	0x455
	.4byte	0x79b
	.uleb128 0x19
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x14
	.4byte	0x114
	.4byte	0x7ac
	.uleb128 0x24
	.4byte	0x2d
	.2byte	0x13f
	.byte	0
	.uleb128 0x14
	.4byte	0x114
	.4byte	0x7bc
	.uleb128 0x19
	.4byte	0x2d
	.byte	0x38
	.byte	0
	.uleb128 0x14
	.4byte	0x114
	.4byte	0x7cd
	.uleb128 0x24
	.4byte	0x2d
	.2byte	0x17f
	.byte	0
	.uleb128 0x15
	.4byte	.LASF99
	.byte	0x3
	.2byte	0x10f
	.byte	0x3
	.4byte	0x67c
	.uleb128 0x20
	.byte	0x7
	.4byte	0x2d
	.byte	0x4
	.2byte	0x3c2
	.4byte	0x800
	.uleb128 0x3
	.4byte	.LASF100
	.byte	0
	.uleb128 0x3
	.4byte	.LASF101
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF102
	.byte	0x2
	.uleb128 0x3
	.4byte	.LASF103
	.byte	0x3
	.byte	0
	.uleb128 0x15
	.4byte	.LASF104
	.byte	0x4
	.2byte	0x3c7
	.byte	0x3
	.4byte	0x7da
	.uleb128 0x2c
	.byte	0xa
	.byte	0x4
	.2byte	0x3e3
	.byte	0x9
	.4byte	0x880
	.uleb128 0x12
	.4byte	.LASF105
	.2byte	0x3e4
	.byte	0xd
	.4byte	0xee
	.byte	0
	.uleb128 0x12
	.4byte	.LASF106
	.2byte	0x3e5
	.byte	0xd
	.4byte	0xee
	.byte	0x1
	.uleb128 0x12
	.4byte	.LASF107
	.2byte	0x3e6
	.byte	0xd
	.4byte	0xee
	.byte	0x2
	.uleb128 0x12
	.4byte	.LASF108
	.2byte	0x3e7
	.byte	0xd
	.4byte	0xee
	.byte	0x3
	.uleb128 0x12
	.4byte	.LASF109
	.2byte	0x3e8
	.byte	0xd
	.4byte	0xee
	.byte	0x4
	.uleb128 0x12
	.4byte	.LASF110
	.2byte	0x3e9
	.byte	0xd
	.4byte	0xee
	.byte	0x5
	.uleb128 0x12
	.4byte	.LASF111
	.2byte	0x3ea
	.byte	0xe
	.4byte	0x101
	.byte	0x6
	.uleb128 0x12
	.4byte	.LASF112
	.2byte	0x3eb
	.byte	0xe
	.4byte	0x101
	.byte	0x8
	.byte	0
	.uleb128 0x15
	.4byte	.LASF113
	.byte	0x4
	.2byte	0x3ec
	.byte	0x3
	.4byte	0x80d
	.uleb128 0x22
	.4byte	0x880
	.uleb128 0x5
	.4byte	.LASF114
	.byte	0x5
	.byte	0xd6
	.byte	0x16
	.4byte	0x2d
	.uleb128 0xd
	.byte	0x10
	.byte	0x4
	.4byte	.LASF115
	.uleb128 0x2d
	.byte	0x4
	.uleb128 0x25
	.4byte	0x8a5
	.uleb128 0xd
	.byte	0x1
	.byte	0x8
	.4byte	.LASF116
	.uleb128 0x20
	.byte	0x5
	.4byte	0x13d
	.byte	0x6
	.2byte	0x160
	.4byte	0x8df
	.uleb128 0x1a
	.4byte	.LASF117
	.sleb128 -4
	.uleb128 0x1a
	.4byte	.LASF118
	.sleb128 -3
	.uleb128 0x1a
	.4byte	.LASF119
	.sleb128 -2
	.uleb128 0x1a
	.4byte	.LASF120
	.sleb128 -1
	.uleb128 0x3
	.4byte	.LASF121
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LASF122
	.byte	0x6
	.2byte	0x166
	.byte	0x3
	.4byte	0x8b3
	.uleb128 0x20
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.2byte	0x169
	.4byte	0x906
	.uleb128 0x3
	.4byte	.LASF123
	.byte	0
	.uleb128 0x3
	.4byte	.LASF124
	.byte	0x1
	.byte	0
	.uleb128 0x15
	.4byte	.LASF125
	.byte	0x6
	.2byte	0x16c
	.byte	0x3
	.4byte	0x8ec
	.uleb128 0x15
	.4byte	.LASF126
	.byte	0x6
	.2byte	0x17a
	.byte	0x10
	.4byte	0x920
	.uleb128 0xe
	.4byte	0x925
	.uleb128 0x2e
	.4byte	0x930
	.uleb128 0x2
	.4byte	0x8a5
	.byte	0
	.uleb128 0x26
	.4byte	0x2d
	.byte	0x4b
	.4byte	0x94d
	.uleb128 0x3
	.4byte	.LASF127
	.byte	0
	.uleb128 0x3
	.4byte	.LASF128
	.byte	0x1
	.uleb128 0x3
	.4byte	.LASF129
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.4byte	.LASF130
	.byte	0x7
	.byte	0x4f
	.byte	0x2
	.4byte	0x930
	.uleb128 0x26
	.4byte	0x2d
	.byte	0x51
	.4byte	0x970
	.uleb128 0x3
	.4byte	.LASF131
	.byte	0
	.uleb128 0x3
	.4byte	.LASF132
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	.LASF133
	.byte	0x7
	.byte	0x54
	.byte	0x2
	.4byte	0x959
	.uleb128 0x9
	.byte	0x8
	.byte	0x7
	.byte	0x56
	.byte	0x9
	.4byte	0x9a0
	.uleb128 0x7
	.4byte	.LASF134
	.byte	0x7
	.byte	0x57
	.byte	0x1d
	.4byte	0x913
	.byte	0
	.uleb128 0x7
	.4byte	.LASF135
	.byte	0x7
	.byte	0x58
	.byte	0xb
	.4byte	0x8a5
	.byte	0x4
	.byte	0
	.uleb128 0x5
	.4byte	.LASF136
	.byte	0x7
	.byte	0x59
	.byte	0x3
	.4byte	0x97c
	.uleb128 0x9
	.byte	0x10
	.byte	0x7
	.byte	0x5c
	.byte	0x9
	.4byte	0x9dd
	.uleb128 0x7
	.4byte	.LASF137
	.byte	0x7
	.byte	0x5d
	.byte	0x1e
	.4byte	0x906
	.byte	0
	.uleb128 0x7
	.4byte	.LASF138
	.byte	0x7
	.byte	0x5e
	.byte	0x1c
	.4byte	0x9a0
	.byte	0x4
	.uleb128 0x7
	.4byte	.LASF139
	.byte	0x7
	.byte	0x5f
	.byte	0x1d
	.4byte	0x9dd
	.byte	0xc
	.byte	0
	.uleb128 0xd
	.byte	0x1
	.byte	0x2
	.4byte	.LASF140
	.uleb128 0x5
	.4byte	.LASF141
	.byte	0x7
	.byte	0x60
	.byte	0x3
	.4byte	0x9ac
	.uleb128 0x2f
	.4byte	.LASF146
	.byte	0x18
	.byte	0x7
	.byte	0x62
	.byte	0x10
	.4byte	0xa4c
	.uleb128 0x7
	.4byte	.LASF142
	.byte	0x7
	.byte	0x63
	.byte	0xd
	.4byte	0xd4
	.byte	0
	.uleb128 0x7
	.4byte	.LASF143
	.byte	0x7
	.byte	0x64
	.byte	0xe
	.4byte	0x114
	.byte	0x4
	.uleb128 0x7
	.4byte	.LASF144
	.byte	0x7
	.byte	0x65
	.byte	0xd
	.4byte	0xee
	.byte	0x8
	.uleb128 0x7
	.4byte	.LASF145
	.byte	0x7
	.byte	0x66
	.byte	0x1a
	.4byte	0x94d
	.byte	0xc
	.uleb128 0x7
	.4byte	.LASF134
	.byte	0x7
	.byte	0x67
	.byte	0x1d
	.4byte	0x913
	.byte	0x10
	.uleb128 0x7
	.4byte	.LASF135
	.byte	0x7
	.byte	0x68
	.byte	0xb
	.4byte	0x8a5
	.byte	0x14
	.byte	0
	.uleb128 0x5
	.4byte	.LASF146
	.byte	0x7
	.byte	0x69
	.byte	0x2
	.4byte	0x9f0
	.uleb128 0x9
	.byte	0xc
	.byte	0x7
	.byte	0x6b
	.byte	0x9
	.4byte	0xa96
	.uleb128 0x7
	.4byte	.LASF147
	.byte	0x7
	.byte	0x6c
	.byte	0x19
	.4byte	0xa96
	.byte	0
	.uleb128 0x7
	.4byte	.LASF148
	.byte	0x7
	.byte	0x6d
	.byte	0xa
	.4byte	0xa9b
	.byte	0x4
	.uleb128 0x7
	.4byte	.LASF149
	.byte	0x7
	.byte	0x6e
	.byte	0xc
	.4byte	0xba
	.byte	0x8
	.uleb128 0x7
	.4byte	.LASF150
	.byte	0x7
	.byte	0x6f
	.byte	0xc
	.4byte	0xba
	.byte	0x9
	.byte	0
	.uleb128 0xe
	.4byte	0xa4c
	.uleb128 0xe
	.4byte	0x13d
	.uleb128 0x5
	.4byte	.LASF151
	.byte	0x7
	.byte	0x70
	.byte	0x2
	.4byte	0xa58
	.uleb128 0x9
	.byte	0x8
	.byte	0x7
	.byte	0x72
	.byte	0x9
	.4byte	0xaf7
	.uleb128 0x7
	.4byte	.LASF152
	.byte	0x7
	.byte	0x73
	.byte	0xd
	.4byte	0xee
	.byte	0
	.uleb128 0x7
	.4byte	.LASF153
	.byte	0x7
	.byte	0x74
	.byte	0xd
	.4byte	0xee
	.byte	0x1
	.uleb128 0x7
	.4byte	.LASF154
	.byte	0x7
	.byte	0x75
	.byte	0xd
	.4byte	0x9dd
	.byte	0x2
	.uleb128 0x7
	.4byte	.LASF155
	.byte	0x7
	.byte	0x76
	.byte	0xd
	.4byte	0x9dd
	.byte	0x3
	.uleb128 0x7
	.4byte	.LASF156
	.byte	0x7
	.byte	0x77
	.byte	0xe
	.4byte	0x114
	.byte	0x4
	.byte	0
	.uleb128 0x5
	.4byte	.LASF157
	.byte	0x7
	.byte	0x78
	.byte	0x2
	.4byte	0xaac
	.uleb128 0xe
	.4byte	0xb0d
	.uleb128 0x25
	.4byte	0xb03
	.uleb128 0x30
	.uleb128 0xe
	.4byte	0x114
	.uleb128 0x13
	.4byte	.LASF158
	.byte	0x2a
	.byte	0x17
	.4byte	0xb24
	.uleb128 0x5
	.byte	0x3
	.4byte	rtc_base
	.uleb128 0xe
	.4byte	0x7cd
	.uleb128 0x14
	.4byte	0x9e4
	.4byte	0xb39
	.uleb128 0x19
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x13
	.4byte	.LASF159
	.byte	0x2c
	.byte	0xf
	.4byte	0xb29
	.uleb128 0x5
	.byte	0x3
	.4byte	g_rtc_context
	.uleb128 0x13
	.4byte	.LASF160
	.byte	0x2d
	.byte	0x12
	.4byte	0xaf7
	.uleb128 0x5
	.byte	0x3
	.4byte	sw_rtc_context
	.uleb128 0x13
	.4byte	.LASF161
	.byte	0x2e
	.byte	0x14
	.4byte	0x970
	.uleb128 0x5
	.byte	0x3
	.4byte	sw_rtc
	.uleb128 0x13
	.4byte	.LASF162
	.byte	0x2f
	.byte	0xa
	.4byte	0x101
	.uleb128 0x5
	.byte	0x3
	.4byte	rtc_unit
	.uleb128 0x13
	.4byte	.LASF163
	.byte	0x30
	.byte	0xa
	.4byte	0xb8e
	.uleb128 0x5
	.byte	0x3
	.4byte	heap
	.uleb128 0xe
	.4byte	0xaa0
	.uleb128 0x13
	.4byte	.LASF164
	.byte	0x31
	.byte	0x10
	.4byte	0x880
	.uleb128 0x5
	.byte	0x3
	.4byte	init_time
	.uleb128 0xf
	.4byte	.LASF165
	.byte	0x7
	.byte	0x87
	.byte	0x12
	.4byte	0x8df
	.4byte	0xbc4
	.uleb128 0x2
	.4byte	0xbc4
	.uleb128 0x2
	.4byte	0x880
	.uleb128 0x2
	.4byte	0x131
	.byte	0
	.uleb128 0xe
	.4byte	0x880
	.uleb128 0xf
	.4byte	.LASF166
	.byte	0x7
	.byte	0x88
	.byte	0x12
	.4byte	0x8df
	.4byte	0xbdf
	.uleb128 0x2
	.4byte	0xbc4
	.byte	0
	.uleb128 0xf
	.4byte	.LASF167
	.byte	0x7
	.byte	0x89
	.byte	0xa
	.4byte	0x114
	.4byte	0xbf5
	.uleb128 0x2
	.4byte	0x800
	.byte	0
	.uleb128 0xf
	.4byte	.LASF168
	.byte	0x8
	.byte	0x1f
	.byte	0x8
	.4byte	0x8a5
	.4byte	0xc15
	.uleb128 0x2
	.4byte	0x8a7
	.uleb128 0x2
	.4byte	0xb08
	.uleb128 0x2
	.4byte	0x892
	.byte	0
	.uleb128 0xf
	.4byte	.LASF169
	.byte	0x7
	.byte	0x86
	.byte	0x12
	.4byte	0x8df
	.4byte	0xc30
	.uleb128 0x2
	.4byte	0x114
	.uleb128 0x2
	.4byte	0xc30
	.byte	0
	.uleb128 0xe
	.4byte	0x131
	.uleb128 0xf
	.4byte	.LASF170
	.byte	0x7
	.byte	0x8a
	.byte	0xa
	.4byte	0x131
	.4byte	0xc4b
	.uleb128 0x2
	.4byte	0xc4b
	.byte	0
	.uleb128 0xe
	.4byte	0x88d
	.uleb128 0xf
	.4byte	.LASF171
	.byte	0x7
	.byte	0x85
	.byte	0x12
	.4byte	0x8df
	.4byte	0xc66
	.uleb128 0x2
	.4byte	0x114
	.byte	0
	.uleb128 0xf
	.4byte	.LASF172
	.byte	0x7
	.byte	0x84
	.byte	0x12
	.4byte	0x8df
	.4byte	0xc8b
	.uleb128 0x2
	.4byte	0x114
	.uleb128 0x2
	.4byte	0x131
	.uleb128 0x2
	.4byte	0x913
	.uleb128 0x2
	.4byte	0x8a5
	.byte	0
	.uleb128 0x17
	.4byte	.LASF176
	.byte	0x7
	.byte	0x7c
	.byte	0x6
	.4byte	0xca7
	.uleb128 0x2
	.4byte	0xb8e
	.uleb128 0x2
	.4byte	0x13d
	.uleb128 0x2
	.4byte	0x94d
	.byte	0
	.uleb128 0xf
	.4byte	.LASF173
	.byte	0x7
	.byte	0x7d
	.byte	0x5
	.4byte	0x13d
	.4byte	0xcc7
	.uleb128 0x2
	.4byte	0xb8e
	.uleb128 0x2
	.4byte	0x13d
	.uleb128 0x2
	.4byte	0xcc7
	.byte	0
	.uleb128 0xe
	.4byte	0x94d
	.uleb128 0xf
	.4byte	.LASF174
	.byte	0x7
	.byte	0x7b
	.byte	0x5
	.4byte	0x13d
	.4byte	0xce2
	.uleb128 0x2
	.4byte	0xb8e
	.byte	0
	.uleb128 0xf
	.4byte	.LASF175
	.byte	0x7
	.byte	0x7a
	.byte	0xa
	.4byte	0xb8e
	.4byte	0xcf8
	.uleb128 0x2
	.4byte	0x13d
	.byte	0
	.uleb128 0x17
	.4byte	.LASF177
	.byte	0x7
	.byte	0x7f
	.byte	0x6
	.4byte	0xd0a
	.uleb128 0x2
	.4byte	0xb8e
	.byte	0
	.uleb128 0x17
	.4byte	.LASF178
	.byte	0x9
	.byte	0x3f
	.byte	0xd
	.4byte	0xd1c
	.uleb128 0x2
	.4byte	0x114
	.byte	0
	.uleb128 0x31
	.4byte	.LASF208
	.byte	0x7
	.byte	0x83
	.byte	0x6
	.uleb128 0x17
	.4byte	.LASF179
	.byte	0x7
	.byte	0x82
	.byte	0x6
	.4byte	0xd36
	.uleb128 0x2
	.4byte	0xd36
	.byte	0
	.uleb128 0xe
	.4byte	0x970
	.uleb128 0x17
	.4byte	.LASF180
	.byte	0x9
	.byte	0x3e
	.byte	0xd
	.4byte	0xd4d
	.uleb128 0x2
	.4byte	0xb0e
	.byte	0
	.uleb128 0xf
	.4byte	.LASF181
	.byte	0x8
	.byte	0x21
	.byte	0x8
	.4byte	0x8a5
	.4byte	0xd6d
	.uleb128 0x2
	.4byte	0x8a5
	.uleb128 0x2
	.4byte	0x13d
	.uleb128 0x2
	.4byte	0x892
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF186
	.2byte	0x123
	.4byte	0x8df
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe49
	.uleb128 0x16
	.4byte	.LASF182
	.2byte	0x123
	.byte	0x2d
	.4byte	0x114
	.4byte	.LLST22
	.uleb128 0x16
	.4byte	.LASF183
	.2byte	0x123
	.byte	0x45
	.4byte	0xbc4
	.4byte	.LLST23
	.uleb128 0x1c
	.4byte	.LASF184
	.2byte	0x124
	.byte	0xe
	.4byte	0x131
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x21
	.4byte	.LASF145
	.2byte	0x125
	.byte	0x16
	.4byte	0x8df
	.4byte	.LLST24
	.uleb128 0x1c
	.4byte	.LASF185
	.2byte	0x12a
	.byte	0x14
	.4byte	0x880
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x8
	.4byte	.LVL82
	.4byte	0xc15
	.4byte	0xdf5
	.uleb128 0x1
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
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x8
	.4byte	.LVL84
	.4byte	0xd4d
	.4byte	0xe13
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.uleb128 0x8
	.4byte	.LVL85
	.4byte	0x145e
	.4byte	0xe32
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.uleb128 0x1d
	.4byte	.LVL86
	.4byte	0xba4
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF187
	.2byte	0x11d
	.4byte	0x8df
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe97
	.uleb128 0x16
	.4byte	.LASF183
	.2byte	0x11d
	.byte	0x33
	.4byte	0xbc4
	.4byte	.LLST15
	.uleb128 0x32
	.4byte	.LASF145
	.byte	0x1
	.2byte	0x11e
	.byte	0x16
	.4byte	0x8df
	.uleb128 0x1e
	.4byte	.LVL66
	.4byte	0xbc9
	.uleb128 0x1
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
	.uleb128 0x1b
	.4byte	.LASF188
	.2byte	0x113
	.4byte	0x8df
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf29
	.uleb128 0x16
	.4byte	.LASF183
	.2byte	0x113
	.byte	0x39
	.4byte	0xc4b
	.4byte	.LLST14
	.uleb128 0x1c
	.4byte	.LASF189
	.2byte	0x114
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x8
	.4byte	.LVL61
	.4byte	0xbf5
	.4byte	0xef8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	init_time
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
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
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.uleb128 0x8
	.4byte	.LVL62
	.4byte	0xd3b
	.4byte	0xf0c
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x8
	.4byte	.LVL63
	.4byte	0xbdf
	.4byte	0xf1f
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x10
	.4byte	.LVL64
	.4byte	0xd0a
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF190
	.2byte	0x10d
	.4byte	0x8df
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf87
	.uleb128 0x16
	.4byte	.LASF182
	.2byte	0x10d
	.byte	0x30
	.4byte	0x114
	.4byte	.LLST12
	.uleb128 0x16
	.4byte	.LASF184
	.2byte	0x10d
	.byte	0x42
	.4byte	0xc30
	.4byte	.LLST13
	.uleb128 0x1e
	.4byte	.LVL57
	.4byte	0xc15
	.uleb128 0x1
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
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	.LASF191
	.byte	0xff
	.4byte	0x8df
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1066
	.uleb128 0xc
	.4byte	.LASF182
	.byte	0xff
	.byte	0x2d
	.4byte	0x114
	.4byte	.LLST16
	.uleb128 0xc
	.4byte	.LASF183
	.byte	0xff
	.byte	0x4b
	.4byte	0xc4b
	.4byte	.LLST17
	.uleb128 0xc
	.4byte	.LASF134
	.byte	0xff
	.byte	0x69
	.4byte	0x913
	.4byte	.LLST18
	.uleb128 0xc
	.4byte	.LASF135
	.byte	0xff
	.byte	0x79
	.4byte	0x8a5
	.4byte	.LLST19
	.uleb128 0x21
	.4byte	.LASF192
	.2byte	0x101
	.byte	0xe
	.4byte	0x131
	.4byte	.LLST20
	.uleb128 0x1c
	.4byte	.LASF193
	.2byte	0x102
	.byte	0x14
	.4byte	0x880
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x21
	.4byte	.LASF194
	.2byte	0x104
	.byte	0xe
	.4byte	0x131
	.4byte	.LLST21
	.uleb128 0x8
	.4byte	.LVL69
	.4byte	0xc35
	.4byte	0x1025
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0
	.uleb128 0x8
	.4byte	.LVL71
	.4byte	0xe49
	.4byte	0x1039
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x8
	.4byte	.LVL72
	.4byte	0xc35
	.4byte	0x104d
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1d
	.4byte	.LVL76
	.4byte	0x10a5
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	.LASF195
	.byte	0xf7
	.4byte	0x8df
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10a5
	.uleb128 0xc
	.4byte	.LASF182
	.byte	0xf7
	.byte	0x2e
	.4byte	0x114
	.4byte	.LLST11
	.uleb128 0x1e
	.4byte	.LVL54
	.4byte	0xc50
	.uleb128 0x1
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
	.uleb128 0x11
	.4byte	.LASF196
	.byte	0xef
	.4byte	0x8df
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1139
	.uleb128 0xc
	.4byte	.LASF182
	.byte	0xef
	.byte	0x30
	.4byte	0x114
	.4byte	.LLST7
	.uleb128 0xc
	.4byte	.LASF192
	.byte	0xef
	.byte	0x41
	.4byte	0x131
	.4byte	.LLST8
	.uleb128 0xc
	.4byte	.LASF134
	.byte	0xef
	.byte	0x6a
	.4byte	0x913
	.4byte	.LLST9
	.uleb128 0xc
	.4byte	.LASF135
	.byte	0xef
	.byte	0x7a
	.4byte	0x8a5
	.4byte	.LLST10
	.uleb128 0x1e
	.4byte	.LVL51
	.4byte	0xc66
	.uleb128 0x1
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
	.uleb128 0x1
	.uleb128 0x6
	.byte	0x5b
	.byte	0x93
	.uleb128 0x4
	.byte	0x5c
	.byte	0x93
	.uleb128 0x4
	.uleb128 0x5
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5d
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xd
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5e
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xe
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	.LASF197
	.byte	0xd8
	.4byte	0x8df
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x11dd
	.uleb128 0xc
	.4byte	.LASF182
	.byte	0xd8
	.byte	0x35
	.4byte	0x114
	.4byte	.LLST5
	.uleb128 0x18
	.4byte	.LASF189
	.byte	0xda
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x18
	.4byte	.LASF145
	.byte	0xdb
	.byte	0x1a
	.4byte	0x94d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x33
	.4byte	.LASF198
	.byte	0x1
	.byte	0xe2
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST6
	.uleb128 0x8
	.4byte	.LVL44
	.4byte	0xca7
	.4byte	0x11a6
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x8
	.4byte	.LVL45
	.4byte	0xd3b
	.4byte	0x11ba
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x8
	.4byte	.LVL46
	.4byte	0xc8b
	.4byte	0x11d3
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x10
	.4byte	.LVL47
	.4byte	0xd0a
	.byte	0
	.uleb128 0x11
	.4byte	.LASF199
	.byte	0xba
	.4byte	0x8df
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1263
	.uleb128 0xc
	.4byte	.LASF182
	.byte	0xba
	.byte	0x35
	.4byte	0xb0e
	.4byte	.LLST3
	.uleb128 0x34
	.string	"i"
	.byte	0x1
	.byte	0xbc
	.byte	0xe
	.4byte	0x114
	.4byte	.LLST4
	.uleb128 0x18
	.4byte	.LASF189
	.byte	0xbc
	.byte	0x11
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x8
	.4byte	.LVL28
	.4byte	0xce2
	.4byte	0x1233
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x36
	.byte	0
	.uleb128 0x8
	.4byte	.LVL29
	.4byte	0xd3b
	.4byte	0x1247
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x10
	.4byte	.LVL30
	.4byte	0xccc
	.uleb128 0x10
	.4byte	.LVL33
	.4byte	0xd0a
	.uleb128 0x10
	.4byte	.LVL37
	.4byte	0xd0a
	.byte	0
	.uleb128 0x11
	.4byte	.LASF200
	.byte	0xac
	.4byte	0x8df
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1305
	.uleb128 0x18
	.4byte	.LASF189
	.byte	0xad
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x8
	.4byte	.LVL20
	.4byte	0xd3b
	.4byte	0x129d
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x10
	.4byte	.LVL21
	.4byte	0xcf8
	.uleb128 0x8
	.4byte	.LVL22
	.4byte	0xd4d
	.4byte	0x12c7
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	g_rtc_context+16
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x40
	.byte	0
	.uleb128 0x8
	.4byte	.LVL23
	.4byte	0xd4d
	.4byte	0x12e8
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	sw_rtc_context
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x38
	.byte	0
	.uleb128 0x8
	.4byte	.LVL24
	.4byte	0x1410
	.4byte	0x12fb
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x10
	.4byte	.LVL25
	.4byte	0xd0a
	.byte	0
	.uleb128 0x11
	.4byte	.LASF201
	.byte	0x81
	.4byte	0x8df
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1373
	.uleb128 0x18
	.4byte	.LASF189
	.byte	0x82
	.byte	0xe
	.4byte	0x114
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x8
	.4byte	.LVL16
	.4byte	0xd3b
	.4byte	0x133f
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
	.uleb128 0x8
	.4byte	.LVL17
	.4byte	0xd4d
	.4byte	0x1360
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.byte	0x3
	.4byte	sw_rtc_context
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x38
	.byte	0
	.uleb128 0x10
	.4byte	.LVL18
	.4byte	0xd1c
	.uleb128 0x10
	.4byte	.LVL19
	.4byte	0xd0a
	.byte	0
	.uleb128 0x11
	.4byte	.LASF202
	.byte	0x6b
	.4byte	0x8df
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x13ca
	.uleb128 0xc
	.4byte	.LASF203
	.byte	0x6b
	.byte	0x3c
	.4byte	0x800
	.4byte	.LLST2
	.uleb128 0x8
	.4byte	.LVL11
	.4byte	0xd4d
	.4byte	0x13b9
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x3
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x40
	.byte	0
	.uleb128 0x1d
	.4byte	.LVL12
	.4byte	0x1410
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x79
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	.LASF204
	.byte	0x4a
	.4byte	0x8df
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1410
	.uleb128 0xc
	.4byte	.LASF203
	.byte	0x4a
	.byte	0x3a
	.4byte	0x800
	.4byte	.LLST1
	.uleb128 0x1d
	.4byte	.LVL5
	.4byte	0xd4d
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x6
	.byte	0x79
	.sleb128 0
	.byte	0x72
	.sleb128 0
	.byte	0x6
	.byte	0x22
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x1
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x40
	.byte	0
	.byte	0
	.uleb128 0x35
	.4byte	.LASF205
	.byte	0x1
	.byte	0x34
	.byte	0x6
	.byte	0x1
	.4byte	0x142a
	.uleb128 0x36
	.4byte	.LASF203
	.byte	0x1
	.byte	0x34
	.byte	0x33
	.4byte	0x800
	.byte	0
	.uleb128 0x37
	.4byte	0x1410
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x145e
	.uleb128 0x38
	.4byte	0x141d
	.4byte	.LLST0
	.uleb128 0x39
	.4byte	0x1410
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.byte	0x1
	.byte	0x34
	.byte	0x6
	.uleb128 0x3a
	.4byte	0x141d
	.byte	0x2
	.byte	0
	.byte	0
	.uleb128 0x3b
	.4byte	.LASF168
	.4byte	.LASF209
	.byte	0xb
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
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
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x4
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
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0x6b
	.uleb128 0xb
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
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
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
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
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
	.uleb128 0x10
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
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
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 18
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
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
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
	.uleb128 0x16
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
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
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 18
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
	.uleb128 0x1c
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x48
	.byte	0x1
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x37
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x29
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0x6b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x2d
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x30
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x31
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
	.uleb128 0x32
	.uleb128 0x34
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
	.uleb128 0x33
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
	.uleb128 0x34
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x36
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
	.byte	0
	.byte	0
	.uleb128 0x37
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
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x1d
	.byte	0x1
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
	.uleb128 0x3a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
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
.LLST22:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL82-1-.LVL80
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL82-1-.LVL80
	.uleb128 .LFE17-.LVL80
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
.LLST23:
	.byte	0x6
	.4byte	.LVL80
	.byte	0x4
	.uleb128 .LVL80-.LVL80
	.uleb128 .LVL81-.LVL80
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL81-.LVL80
	.uleb128 .LVL87-.LVL80
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL87-.LVL80
	.uleb128 .LFE17-.LVL80
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
.LLST24:
	.byte	0x8
	.4byte	.LVL82
	.uleb128 .LVL83-.LVL82
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL65
	.byte	0x4
	.uleb128 .LVL65-.LVL65
	.uleb128 .LVL66-1-.LVL65
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL66-1-.LVL65
	.uleb128 .LFE16-.LVL65
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
.LLST14:
	.byte	0x6
	.4byte	.LVL59
	.byte	0x4
	.uleb128 .LVL59-.LVL59
	.uleb128 .LVL60-.LVL59
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL60-.LVL59
	.uleb128 .LVL61-1-.LVL59
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL61-1-.LVL59
	.uleb128 .LFE15-.LVL59
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
.LLST12:
	.byte	0x6
	.4byte	.LVL56
	.byte	0x4
	.uleb128 .LVL56-.LVL56
	.uleb128 .LVL57-1-.LVL56
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL57-1-.LVL56
	.uleb128 .LVL57-.LVL56
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
	.uleb128 .LVL57-.LVL56
	.uleb128 .LVL58-.LVL56
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL58-.LVL56
	.uleb128 .LFE14-.LVL56
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
.LLST13:
	.byte	0x6
	.4byte	.LVL56
	.byte	0x4
	.uleb128 .LVL56-.LVL56
	.uleb128 .LVL57-1-.LVL56
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL57-1-.LVL56
	.uleb128 .LVL57-.LVL56
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
	.uleb128 .LVL57-.LVL56
	.uleb128 .LFE14-.LVL56
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST16:
	.byte	0x6
	.4byte	.LVL67
	.byte	0x4
	.uleb128 .LVL67-.LVL67
	.uleb128 .LVL68-.LVL67
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL68-.LVL67
	.uleb128 .LVL77-.LVL67
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0x4
	.uleb128 .LVL77-.LVL67
	.uleb128 .LVL78-.LVL67
	.uleb128 0x2
	.byte	0x72
	.sleb128 -36
	.byte	0x4
	.uleb128 .LVL78-.LVL67
	.uleb128 .LFE13-.LVL67
	.uleb128 0x2
	.byte	0x72
	.sleb128 0
	.byte	0
.LLST17:
	.byte	0x6
	.4byte	.LVL67
	.byte	0x4
	.uleb128 .LVL67-.LVL67
	.uleb128 .LVL69-1-.LVL67
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL69-1-.LVL67
	.uleb128 .LFE13-.LVL67
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
.LLST18:
	.byte	0x6
	.4byte	.LVL67
	.byte	0x4
	.uleb128 .LVL67-.LVL67
	.uleb128 .LVL69-1-.LVL67
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL69-1-.LVL67
	.uleb128 .LVL77-.LVL67
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x4
	.uleb128 .LVL77-.LVL67
	.uleb128 .LVL78-.LVL67
	.uleb128 0x2
	.byte	0x72
	.sleb128 -32
	.byte	0x4
	.uleb128 .LVL78-.LVL67
	.uleb128 .LFE13-.LVL67
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
.LLST19:
	.byte	0x6
	.4byte	.LVL67
	.byte	0x4
	.uleb128 .LVL67-.LVL67
	.uleb128 .LVL69-1-.LVL67
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL69-1-.LVL67
	.uleb128 .LVL77-.LVL67
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0x4
	.uleb128 .LVL77-.LVL67
	.uleb128 .LVL78-.LVL67
	.uleb128 0x2
	.byte	0x72
	.sleb128 -28
	.byte	0x4
	.uleb128 .LVL78-.LVL67
	.uleb128 .LFE13-.LVL67
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
.LLST20:
	.byte	0x6
	.4byte	.LVL70
	.byte	0x4
	.uleb128 .LVL70-.LVL70
	.uleb128 .LVL73-.LVL70
	.uleb128 0x6
	.byte	0x59
	.byte	0x93
	.uleb128 0x4
	.byte	0x58
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL78-.LVL70
	.uleb128 .LFE13-.LVL70
	.uleb128 0x6
	.byte	0x59
	.byte	0x93
	.uleb128 0x4
	.byte	0x58
	.byte	0x93
	.uleb128 0x4
	.byte	0
.LLST21:
	.byte	0x6
	.4byte	.LVL72
	.byte	0x4
	.uleb128 .LVL72-.LVL72
	.uleb128 .LVL74-.LVL72
	.uleb128 0x6
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x5b
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL74-.LVL72
	.uleb128 .LVL75-.LVL72
	.uleb128 0x6
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x5d
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL78-.LVL72
	.uleb128 .LVL79-.LVL72
	.uleb128 0x6
	.byte	0x5a
	.byte	0x93
	.uleb128 0x4
	.byte	0x5b
	.byte	0x93
	.uleb128 0x4
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL53
	.byte	0x4
	.uleb128 .LVL53-.LVL53
	.uleb128 .LVL54-1-.LVL53
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL54-1-.LVL53
	.uleb128 .LVL54-.LVL53
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
	.uleb128 .LVL54-.LVL53
	.uleb128 .LVL55-.LVL53
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL55-.LVL53
	.uleb128 .LFE12-.LVL53
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
.LLST7:
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL51-1-.LVL50
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL51-1-.LVL50
	.uleb128 .LVL51-.LVL50
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
	.uleb128 .LVL51-.LVL50
	.uleb128 .LVL52-.LVL50
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL52-.LVL50
	.uleb128 .LFE11-.LVL50
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
.LLST8:
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL51-1-.LVL50
	.uleb128 0x6
	.byte	0x5b
	.byte	0x93
	.uleb128 0x4
	.byte	0x5c
	.byte	0x93
	.uleb128 0x4
	.byte	0x4
	.uleb128 .LVL51-1-.LVL50
	.uleb128 .LVL51-.LVL50
	.uleb128 0x6
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL51-.LVL50
	.uleb128 .LFE11-.LVL50
	.uleb128 0x6
	.byte	0x5b
	.byte	0x93
	.uleb128 0x4
	.byte	0x5c
	.byte	0x93
	.uleb128 0x4
	.byte	0
.LLST9:
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL51-1-.LVL50
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL51-1-.LVL50
	.uleb128 .LVL51-.LVL50
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xd
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL51-.LVL50
	.uleb128 .LFE11-.LVL50
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL50
	.byte	0x4
	.uleb128 .LVL50-.LVL50
	.uleb128 .LVL51-1-.LVL50
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL51-1-.LVL50
	.uleb128 .LVL51-.LVL50
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xe
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL51-.LVL50
	.uleb128 .LFE11-.LVL50
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST5:
	.byte	0x6
	.4byte	.LVL40
	.byte	0x4
	.uleb128 .LVL40-.LVL40
	.uleb128 .LVL41-.LVL40
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL41-.LVL40
	.uleb128 .LVL42-.LVL40
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
	.uleb128 .LVL42-.LVL40
	.uleb128 .LVL43-.LVL40
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL43-.LVL40
	.uleb128 .LVL48-.LVL40
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
	.uleb128 .LVL48-.LVL40
	.uleb128 .LVL49-.LVL40
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL49-.LVL40
	.uleb128 .LFE10-.LVL40
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
.LLST6:
	.byte	0x6
	.4byte	.LVL42
	.byte	0x4
	.uleb128 .LVL42-.LVL42
	.uleb128 .LVL43-.LVL42
	.uleb128 0x7
	.byte	0x7a
	.sleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL43-.LVL42
	.uleb128 .LVL48-.LVL42
	.uleb128 0xe
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0xa
	.2byte	0xffff
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL26
	.byte	0x4
	.uleb128 .LVL26-.LVL26
	.uleb128 .LVL27-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL27-.LVL26
	.uleb128 .LVL34-.LVL26
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL34-.LVL26
	.uleb128 .LVL35-.LVL26
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
	.uleb128 .LVL35-.LVL26
	.uleb128 .LVL38-.LVL26
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL38-.LVL26
	.uleb128 .LVL39-.LVL26
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL39-.LVL26
	.uleb128 .LFE9-.LVL26
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
.LLST4:
	.byte	0x6
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL32-.LVL31
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL32-.LVL31
	.uleb128 .LVL33-1-.LVL31
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL35-.LVL31
	.uleb128 .LVL36-.LVL31
	.uleb128 0x1
	.byte	0x5f
	.byte	0
.LLST2:
	.byte	0x6
	.4byte	.LVL9
	.byte	0x4
	.uleb128 .LVL9-.LVL9
	.uleb128 .LVL10-.LVL9
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL10-.LVL9
	.uleb128 .LVL13-.LVL9
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL13-.LVL9
	.uleb128 .LVL14-.LVL9
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
	.uleb128 .LVL14-.LVL9
	.uleb128 .LVL15-.LVL9
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL15-.LVL9
	.uleb128 .LFE6-.LVL9
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
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL4-.LVL3
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL4-.LVL3
	.uleb128 .LVL6-.LVL3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL6-.LVL3
	.uleb128 .LVL7-.LVL3
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
	.uleb128 .LVL7-.LVL3
	.uleb128 .LVL8-.LVL3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0x4
	.uleb128 .LVL8-.LVL3
	.uleb128 .LFE5-.LVL3
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
	.uleb128 .LVL2-.LVL0
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
	.uleb128 .LVL2-.LVL0
	.uleb128 .LFE4-.LVL0
	.uleb128 0x1
	.byte	0x5a
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
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
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
.LLRL25:
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
	.4byte	.LFB14
	.uleb128 .LFE14-.LFB14
	.byte	0x7
	.4byte	.LFB15
	.uleb128 .LFE15-.LFB15
	.byte	0x7
	.4byte	.LFB16
	.uleb128 .LFE16-.LFB16
	.byte	0x7
	.4byte	.LFB13
	.uleb128 .LFE13-.LFB13
	.byte	0x7
	.4byte	.LFB17
	.uleb128 .LFE17-.LFB17
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF174:
	.string	"getKey"
.LASF135:
	.string	"user_data"
.LASF149:
	.string	"capacity"
.LASF199:
	.string	"hal_rtc_alarm_get_handle"
.LASF157:
	.string	"sw_rtc_context_t"
.LASF188:
	.string	"hal_rtc_set_time"
.LASF117:
	.string	"HAL_RTC_STATUS_ERROR_PORT_USE_FULL"
.LASF37:
	.string	"MODE0"
.LASF114:
	.string	"size_t"
.LASF64:
	.string	"rtc_count"
.LASF178:
	.string	"hal_nvic_restore_interrupt_mask"
.LASF35:
	.string	"uint64_t"
.LASF53:
	.string	"RTC_IRQ_ACK_T"
.LASF71:
	.string	"IRQMASK1"
.LASF52:
	.string	"IRQACK0"
.LASF66:
	.string	"RTC_CONFIG_T"
.LASF186:
	.string	"hal_rtc_get_alarm"
.LASF206:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF177:
	.string	"freeMinHeap"
.LASF198:
	.string	"index"
.LASF105:
	.string	"rtc_sec"
.LASF57:
	.string	"RTC_COMPARE_T"
.LASF205:
	.string	"rtc_reset_default_timer"
.LASF6:
	.string	"QDEC_IRQn"
.LASF118:
	.string	"HAL_RTC_STATUS_ERROR_PORT"
.LASF184:
	.string	"remain_time"
.LASF130:
	.string	"sw_rtc_note_status_t"
.LASF5:
	.string	"LED_IRQn"
.LASF76:
	.string	"RTC_T_WAKEUPMASK1_T"
.LASF194:
	.string	"current_time_ms"
.LASF85:
	.string	"rtc_t_wakeupmask0"
.LASF86:
	.string	"rtc_t_wakeupmask1"
.LASF172:
	.string	"sw_rtc_timer_start"
.LASF171:
	.string	"sw_rtc_timer_stop"
.LASF28:
	.string	"long long int"
.LASF23:
	.string	"signed char"
.LASF41:
	.string	"field"
.LASF160:
	.string	"sw_rtc_context"
.LASF98:
	.string	"rtc_ao_t_wcompsta"
.LASF165:
	.string	"rtc_get_time_change"
.LASF156:
	.string	"timer_count"
.LASF2:
	.string	"long long unsigned int"
.LASF99:
	.string	"RTC_TIMER_REGISTER_T"
.LASF139:
	.string	"has_initilized"
.LASF173:
	.string	"statusGetHeap"
.LASF8:
	.string	"UART_IRQn"
.LASF161:
	.string	"sw_rtc"
.LASF68:
	.string	"RTC_T_IRQSTA_T"
.LASF27:
	.string	"long int"
.LASF153:
	.string	"timer_overflow"
.LASF56:
	.string	"COMPARE0"
.LASF113:
	.string	"hal_rtc_time_t"
.LASF122:
	.string	"hal_rtc_status_t"
.LASF141:
	.string	"rtc_context_t"
.LASF202:
	.string	"hal_rtc_timer_deinit"
.LASF168:
	.string	"memcpy"
.LASF155:
	.string	"sw_start_first"
.LASF119:
	.string	"HAL_RTC_STATUS_ERROR"
.LASF31:
	.string	"uint16_t"
.LASF208:
	.string	"rtc_nvic_register"
.LASF44:
	.string	"CLR0"
.LASF146:
	.string	"timeout_elements_t"
.LASF134:
	.string	"callback"
.LASF164:
	.string	"init_time"
.LASF137:
	.string	"running_status"
.LASF201:
	.string	"hal_rtc_enable_time"
.LASF103:
	.string	"HAL_RTC_TIMER_MAX"
.LASF36:
	.string	"__reserved_00"
.LASF38:
	.string	"__reserved_01"
.LASF40:
	.string	"__reserved_02"
.LASF89:
	.string	"__reserved_03"
.LASF91:
	.string	"__reserved_04"
.LASF189:
	.string	"mask"
.LASF81:
	.string	"rtc_config"
.LASF185:
	.string	"time0"
.LASF144:
	.string	"expire_overflow"
.LASF74:
	.string	"RTC_T_WAKEUPMASK0_T"
.LASF51:
	.string	"RTC_IRQ_STA_T"
.LASF15:
	.string	"EINT_IRQn"
.LASF17:
	.string	"I3C0_DMA_IRQn"
.LASF46:
	.string	"CLK0"
.LASF108:
	.string	"rtc_day"
.LASF58:
	.string	"rtc_con"
.LASF3:
	.string	"unsigned int"
.LASF95:
	.string	"rtc_ao_t_wakeupmask0"
.LASF96:
	.string	"rtc_ao_t_wakeupmask1"
.LASF34:
	.string	"long unsigned int"
.LASF26:
	.string	"int32_t"
.LASF136:
	.string	"rtc_callback_context_t"
.LASF80:
	.string	"RTC_T_WCOMPSTA_T"
.LASF97:
	.string	"rtc_ao_t_clrsta"
.LASF133:
	.string	"sw_rtc_user_type_t"
.LASF150:
	.string	"size"
.LASF32:
	.string	"short unsigned int"
.LASF128:
	.string	"SW_RTC_NOTE_STATUS_OF_ALLOC"
.LASF79:
	.string	"WCOMPSTA"
.LASF196:
	.string	"hal_rtc_set_alarm_ms"
.LASF93:
	.string	"rtc_ao_t_irqmask0"
.LASF94:
	.string	"rtc_ao_t_irqmask1"
.LASF83:
	.string	"rtc_t_irqmask0"
.LASF84:
	.string	"rtc_t_irqmask1"
.LASF166:
	.string	"rtc_get_time"
.LASF209:
	.string	"__builtin_memcpy"
.LASF193:
	.string	"current_time"
.LASF129:
	.string	"SW_RTC_NOTE_STATUS_OF_RUNING"
.LASF48:
	.string	"IRQEN0"
.LASF63:
	.string	"rtc_irq_ack"
.LASF18:
	.string	"SPI_MST0_IRQn"
.LASF9:
	.string	"SPI_MST1_IRQn"
.LASF182:
	.string	"handle"
.LASF200:
	.string	"hal_rtc_disable_time"
.LASF72:
	.string	"RTC_T_IRQMASK1_T"
.LASF61:
	.string	"rtc_irq_en"
.LASF207:
	.string	"IRQn"
.LASF175:
	.string	"createMinHeap"
.LASF158:
	.string	"rtc_base"
.LASF25:
	.string	"int8_t"
.LASF179:
	.string	"sw_rtc_callback"
.LASF148:
	.string	"user_index"
.LASF138:
	.string	"callback_context"
.LASF88:
	.string	"rtc_t_wcompsta"
.LASF90:
	.string	"rtc_ao_config"
.LASF11:
	.string	"GPT_IRQn"
.LASF77:
	.string	"CLRSTA"
.LASF132:
	.string	"SW_RTC_WITH_USER"
.LASF4:
	.string	"SW_IRQn"
.LASF20:
	.string	"USB_IRQn"
.LASF125:
	.string	"hal_rtc_running_status_t"
.LASF183:
	.string	"time"
.LASF73:
	.string	"EVENTMASK0"
.LASF75:
	.string	"EVENTMASK1"
.LASF143:
	.string	"expire_count"
.LASF180:
	.string	"hal_nvic_save_and_set_interrupt_mask"
.LASF107:
	.string	"rtc_hour"
.LASF92:
	.string	"rtc_ao_t_irqsta"
.LASF39:
	.string	"SW_CG0"
.LASF12:
	.string	"UART_DMA_IRQn"
.LASF110:
	.string	"rtc_week"
.LASF87:
	.string	"rtc_t_clrsta"
.LASF197:
	.string	"hal_rtc_alarm_free_handle"
.LASF140:
	.string	"_Bool"
.LASF124:
	.string	"HAL_RTC_RUNNING"
.LASF49:
	.string	"RTC_IRQ_EN_T"
.LASF70:
	.string	"RTC_T_IRQMASK0_T"
.LASF109:
	.string	"rtc_mon"
.LASF24:
	.string	"short int"
.LASF151:
	.string	"MinHeap"
.LASF45:
	.string	"RTC_CLR_T"
.LASF13:
	.string	"PMU_IRQn"
.LASF14:
	.string	"MCU_DMA_IRQn"
.LASF50:
	.string	"IRQSTA0"
.LASF187:
	.string	"hal_rtc_get_time"
.LASF170:
	.string	"rtc_time_diff"
.LASF121:
	.string	"HAL_RTC_STATUS_OK"
.LASF106:
	.string	"rtc_min"
.LASF127:
	.string	"SW_RTC_NOTE_STATUS_OF_FREE"
.LASF78:
	.string	"RTC_T_CLRSTA_T"
.LASF33:
	.string	"uint32_t"
.LASF67:
	.string	"IRQSTA"
.LASF167:
	.string	"hal_rtc_get_current"
.LASF163:
	.string	"heap"
.LASF65:
	.string	"rtc_compare"
.LASF115:
	.string	"long double"
.LASF116:
	.string	"char"
.LASF162:
	.string	"rtc_unit"
.LASF55:
	.string	"RTC_COUNT_T"
.LASF19:
	.string	"IRQ_GEN_IRQn"
.LASF176:
	.string	"statusChangeHeap"
.LASF104:
	.string	"hal_rtc_timer_port_t"
.LASF147:
	.string	"timeout_elements"
.LASF54:
	.string	"COUNTER0"
.LASF42:
	.string	"word"
.LASF112:
	.string	"rtc_milli_sec"
.LASF21:
	.string	"BT_IRQn"
.LASF142:
	.string	"user_id"
.LASF69:
	.string	"IRQMASK0"
.LASF30:
	.string	"unsigned char"
.LASF203:
	.string	"rtc_timer_port"
.LASF16:
	.string	"I3C0_IRQn"
.LASF82:
	.string	"rtc_t_irqsta"
.LASF131:
	.string	"SW_RTC_NOT_USER"
.LASF191:
	.string	"hal_rtc_set_alarm"
.LASF192:
	.string	"timeout_time_ms"
.LASF195:
	.string	"hal_rtc_stop_alarm"
.LASF152:
	.string	"current_overflow"
.LASF181:
	.string	"memset"
.LASF145:
	.string	"status"
.LASF154:
	.string	"creat_heap"
.LASF111:
	.string	"rtc_year"
.LASF62:
	.string	"rtc_irq_sta"
.LASF29:
	.string	"uint8_t"
.LASF169:
	.string	"sw_rtc_get_remaining_time"
.LASF60:
	.string	"rtc_clk"
.LASF100:
	.string	"HAL_RTC_TIMER_0"
.LASF101:
	.string	"HAL_RTC_TIMER_1"
.LASF102:
	.string	"HAL_RTC_TIMER_2"
.LASF59:
	.string	"rtc_clr"
.LASF47:
	.string	"RTC_CLK_T"
.LASF190:
	.string	"hal_rtc_get_alarm_ms"
.LASF204:
	.string	"hal_rtc_timer_init"
.LASF10:
	.string	"RTC_IRQn"
.LASF159:
	.string	"g_rtc_context"
.LASF120:
	.string	"HAL_RTC_STATUS_INVALID_PARAM"
.LASF7:
	.string	"KEYSCAN_IRQn"
.LASF123:
	.string	"HAL_RTC_STOPPED"
.LASF126:
	.string	"hal_rtc_time_callback_t"
.LASF43:
	.string	"RTC_CON_T"
.LASF22:
	.string	"IRQ_NUMBER_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_rtc.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
