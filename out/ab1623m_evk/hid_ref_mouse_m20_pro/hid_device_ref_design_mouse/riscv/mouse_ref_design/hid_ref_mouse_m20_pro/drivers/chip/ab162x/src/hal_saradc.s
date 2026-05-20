	.file	"hal_saradc.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_saradc.c"
	.section	.text.hal_saradc_set_mode,"ax",@progbits
	.align	1
	.globl	hal_saradc_set_mode
	.hidden	hal_saradc_set_mode
	.type	hal_saradc_set_mode, @function
hal_saradc_set_mode:
.LFB4:
	.file 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_saradc.c"
	.loc 1 45 1
	.cfi_startproc
.LVL0:
	.loc 1 46 5
	li	a5,1
	beq	a1,a5,.L2
	li	a5,2
	beq	a1,a5,.L3
	beq	a1,zero,.L4
.L9:
	.loc 1 63 20 is_stmt 0
	li	a0,-4
.LVL1:
	ret
.LVL2:
.L4:
	.loc 1 49 13 is_stmt 1
	.loc 1 49 50 is_stmt 0
	li	a5,1107820544
	addi	a5,a5,132
	li	a4,16
.L13:
	.loc 1 59 50
	sw	a4,0(a5)
	.loc 1 60 13 is_stmt 1
	.loc 1 60 50 is_stmt 0
	li	a5,1107820544
	addi	a5,a5,136
	sw	zero,0(a5)
	.loc 1 61 13 is_stmt 1
	j	.L6
.L2:
	.loc 1 54 13
	.loc 1 54 50 is_stmt 0
	li	a5,1107820544
	addi	a5,a5,132
	li	a4,16
	sw	a4,0(a5)
	.loc 1 55 13 is_stmt 1
	.loc 1 55 50 is_stmt 0
	li	a5,1107820544
	addi	a5,a5,136
	li	a4,16384
	sw	a4,0(a5)
	.loc 1 56 13 is_stmt 1
.L6:
	.loc 1 64 13
	.loc 1 67 5
	li	a5,1
	beq	a0,a5,.L7
	li	a3,2
	beq	a0,a3,.L8
	bne	a0,zero,.L9
	.loc 1 70 13
	.loc 1 70 60 is_stmt 0
	li	a5,1074593792
	sw	zero,168(a5)
	.loc 1 71 13 is_stmt 1
	.loc 1 71 50 is_stmt 0
	li	a5,1107820544
	addi	a5,a5,132
	li	a4,33
	sw	a4,0(a5)
	.loc 1 72 13 is_stmt 1
	.loc 1 72 16 is_stmt 0
	bne	a1,a3,.L10
	.loc 1 73 17 is_stmt 1
	.loc 1 73 54 is_stmt 0
	li	a4,16384
	addi	a4,a4,33
.L10:
	.loc 1 75 17 is_stmt 1
	.loc 1 75 54 is_stmt 0
	sw	a4,0(a5)
	.loc 1 77 13 is_stmt 1
	.loc 1 77 50 is_stmt 0
	li	a5,1107820544
	addi	a5,a5,140
	li	a4,320
	sw	a4,0(a5)
	.loc 1 78 13 is_stmt 1
.L12:
	.loc 1 98 12 is_stmt 0
	li	a0,0
.LVL3:
	.loc 1 99 1
	ret
.LVL4:
.L3:
	.loc 1 59 13 is_stmt 1
	.loc 1 59 50 is_stmt 0
	li	a5,1107820544
	li	a4,16384
	addi	a5,a5,132
	addi	a4,a4,16
	j	.L13
.L7:
	.loc 1 81 13 is_stmt 1
	.loc 1 81 60 is_stmt 0
	li	a5,1074593792
	sw	a0,168(a5)
	.loc 1 82 13 is_stmt 1
	.loc 1 82 50 is_stmt 0
	li	a5,1107820544
	addi	a5,a5,132
	li	a4,17
	sw	a4,0(a5)
	.loc 1 83 13 is_stmt 1
.L14:
	.loc 1 90 50 is_stmt 0
	sw	a4,0(a5)
	.loc 1 91 13 is_stmt 1
	.loc 1 91 50 is_stmt 0
	li	a5,1107820544
	addi	a5,a5,140
	sw	zero,0(a5)
	.loc 1 92 13 is_stmt 1
	j	.L12
.L8:
	.loc 1 88 13
	.loc 1 88 60 is_stmt 0
	li	a5,1074593792
	li	a4,5
	sw	a4,168(a5)
	.loc 1 89 13 is_stmt 1
	.loc 1 89 50 is_stmt 0
	li	a5,1107820544
	li	a4,16
	addi	a5,a5,132
	sw	a4,0(a5)
	.loc 1 90 13 is_stmt 1
	.loc 1 90 50 is_stmt 0
	li	a4,48
	j	.L14
	.cfi_endproc
.LFE4:
	.size	hal_saradc_set_mode, .-hal_saradc_set_mode
	.section	.text.hal_saradc_enable,"ax",@progbits
	.align	1
	.globl	hal_saradc_enable
	.hidden	hal_saradc_enable
	.type	hal_saradc_enable, @function
hal_saradc_enable:
.LFB5:
	.loc 1 102 1 is_stmt 1
	.cfi_startproc
	.loc 1 108 5
	.loc 1 102 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	s0,4(sp)
	.cfi_offset 8, -8
	.loc 1 108 53
	li	s0,1074593792
	lw	a5,172(s0)
	.loc 1 102 1
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 109 5
	li	a0,50
	.loc 1 108 65
	ori	a5,a5,1
	sw	a5,172(s0)
	.loc 1 109 5 is_stmt 1
	call	hal_gpt_delay_us
.LVL5:
	.loc 1 110 5
	.loc 1 110 65 is_stmt 0
	li	a5,257
	sw	a5,176(s0)
	.loc 1 111 5 is_stmt 1
	li	a0,50
	call	hal_gpt_delay_us
.LVL6:
	.loc 1 112 5
	.loc 1 114 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	lw	s0,4(sp)
	.cfi_restore 8
	.loc 1 112 42
	li	a5,1107820544
	addi	a5,a5,132
	li	a4,289
	sw	a4,0(a5)
	.loc 1 113 5 is_stmt 1
	.loc 1 114 1 is_stmt 0
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE5:
	.size	hal_saradc_enable, .-hal_saradc_enable
	.section	.text.hal_saradc_disable,"ax",@progbits
	.align	1
	.globl	hal_saradc_disable
	.hidden	hal_saradc_disable
	.type	hal_saradc_disable, @function
hal_saradc_disable:
.LFB6:
	.loc 1 117 1 is_stmt 1
	.cfi_startproc
	.loc 1 119 5
	.loc 1 119 65 is_stmt 0
	li	a5,1074593792
	sw	zero,176(a5)
	.loc 1 121 5 is_stmt 1
	.loc 1 121 65 is_stmt 0
	sw	zero,172(a5)
	.loc 1 126 5 is_stmt 1
	.loc 1 127 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE6:
	.size	hal_saradc_disable, .-hal_saradc_disable
	.section	.text.hal_saradc_set_gpio_mode,"ax",@progbits
	.align	1
	.globl	hal_saradc_set_gpio_mode
	.hidden	hal_saradc_set_gpio_mode
	.type	hal_saradc_set_gpio_mode, @function
hal_saradc_set_gpio_mode:
.LFB7:
	.loc 1 130 1 is_stmt 1
	.cfi_startproc
.LVL7:
	.loc 1 131 5
	.loc 1 132 5
	.loc 1 133 5
	.loc 1 133 10
	.loc 1 133 29 discriminator 1
	.loc 1 147 5
	.loc 1 148 1 is_stmt 0
	li	a0,0
.LVL8:
	ret
	.cfi_endproc
.LFE7:
	.size	hal_saradc_set_gpio_mode, .-hal_saradc_set_gpio_mode
	.section	.text.hal_saradc_get_data_immediately,"ax",@progbits
	.align	1
	.globl	hal_saradc_get_data_immediately
	.hidden	hal_saradc_get_data_immediately
	.type	hal_saradc_get_data_immediately, @function
hal_saradc_get_data_immediately:
.LFB8:
	.loc 1 151 1 is_stmt 1
	.cfi_startproc
.LVL9:
	.loc 1 152 5
	.loc 1 152 49 is_stmt 0
	li	a5,1074593792
	sw	zero,4(a5)
	.loc 1 153 5 is_stmt 1
	.loc 1 153 62 is_stmt 0
	lw	a3,0(a0)
	.loc 1 154 79 discriminator 1
	li	a4,1074593792
	.loc 1 153 49
	sw	a3,4(a5)
	.loc 1 154 5 is_stmt 1
.L20:
	.loc 1 154 12 discriminator 1
	.loc 1 154 79 is_stmt 0 discriminator 1
	lbu	a5,8(a4)
	.loc 1 154 12 discriminator 1
	andi	a5,a5,1
	bne	a5,zero,.L20
	addi	a0,a0,4
.LVL10:
.LBB2:
	.loc 1 156 44
	li	a1,1
	.loc 1 157 88
	li	t1,1074593792
	.loc 1 155 29 discriminator 1
	li	a2,32
.LVL11:
.L22:
	.loc 1 156 9 is_stmt 1
	.loc 1 156 44 is_stmt 0
	sll	a4,a1,a5
	.loc 1 156 39
	and	a4,a4,a3
	.loc 1 156 12
	beq	a4,zero,.L21
	.loc 1 157 13 is_stmt 1
	.loc 1 157 88 is_stmt 0
	addi	a4,a5,4
	slli	a4,a4,2
	add	a4,t1,a4
	lw	a4,0(a4)
	.loc 1 157 43
	sw	a4,0(a0)
.L21:
	.loc 1 155 37 is_stmt 1 discriminator 2
.LVL12:
	.loc 1 155 29 discriminator 1
	addi	a5,a5,1
.LVL13:
	addi	a0,a0,4
	bne	a5,a2,.L22
.LBE2:
	.loc 1 160 5
	.loc 1 161 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE8:
	.size	hal_saradc_get_data_immediately, .-hal_saradc_get_data_immediately
	.section	.text.hal_saradc_get_data_average,"ax",@progbits
	.align	1
	.globl	hal_saradc_get_data_average
	.hidden	hal_saradc_get_data_average
	.type	hal_saradc_get_data_average, @function
hal_saradc_get_data_average:
.LFB9:
	.loc 1 164 1 is_stmt 1
	.cfi_startproc
.LVL14:
	.loc 1 165 5
	.loc 1 165 52 is_stmt 0
	li	a5,1074593792
	sw	a1,180(a5)
	.loc 1 166 5 is_stmt 1
	.loc 1 166 49 is_stmt 0
	sw	zero,4(a5)
	.loc 1 167 5 is_stmt 1
.LBB3:
	.loc 1 167 10
.LVL15:
	.loc 1 167 29 discriminator 1
	.loc 1 168 24 is_stmt 0
	lw	a3,0(a0)
	li	a5,0
	.loc 1 168 44
	li	t0,1
	.loc 1 169 62
	li	a4,1074593792
	.loc 1 167 29 discriminator 1
	li	t1,32
.LVL16:
.L31:
	.loc 1 168 9 is_stmt 1
	.loc 1 168 44 is_stmt 0
	sll	a1,t0,a5
	.loc 1 168 39
	and	a2,a3,a1
	.loc 1 168 12
	beq	a2,zero,.L29
	.loc 1 169 13 is_stmt 1
	.loc 1 169 62 is_stmt 0
	lw	a2,12(a4)
	.loc 1 169 75
	ori	a2,a2,256
	sw	a2,12(a4)
	.loc 1 170 13 is_stmt 1
	.loc 1 170 57 is_stmt 0
	sw	a1,4(a4)
	.loc 1 171 13 is_stmt 1
.L30:
	.loc 1 171 69 discriminator 1
	.loc 1 171 50 is_stmt 0 discriminator 1
	lw	a2,184(a4)
	.loc 1 171 69 discriminator 1
	beq	a2,zero,.L30
.L29:
	.loc 1 167 37 is_stmt 1 discriminator 2
.LVL17:
	.loc 1 167 29 discriminator 1
	addi	a5,a5,1
.LVL18:
	bne	a5,t1,.L31
	addi	a0,a0,4
.LVL19:
	li	a5,0
.LVL20:
.LBE3:
.LBB4:
	.loc 1 175 44 is_stmt 0
	li	a1,1
	.loc 1 176 85
	li	t1,1074593792
	.loc 1 174 29 discriminator 1
	li	a2,32
.LVL21:
.L33:
	.loc 1 175 9 is_stmt 1
	.loc 1 175 44 is_stmt 0
	sll	a4,a1,a5
	.loc 1 175 39
	and	a4,a4,a3
	.loc 1 175 12
	beq	a4,zero,.L32
	.loc 1 176 13 is_stmt 1
	.loc 1 176 85 is_stmt 0
	addi	a4,a5,64
	slli	a4,a4,2
	add	a4,t1,a4
	lw	a4,0(a4)
	.loc 1 176 90
	srli	a4,a4,3
	.loc 1 176 43
	sw	a4,0(a0)
.L32:
	.loc 1 174 37 is_stmt 1 discriminator 2
.LVL22:
	.loc 1 174 29 discriminator 1
	addi	a5,a5,1
.LVL23:
	addi	a0,a0,4
	bne	a5,a2,.L33
.LBE4:
	.loc 1 179 5
	.loc 1 180 1 is_stmt 0
	li	a0,0
	ret
	.cfi_endproc
.LFE9:
	.size	hal_saradc_get_data_average, .-hal_saradc_get_data_average
	.section	.text.hal_saradc_dma_init,"ax",@progbits
	.align	1
	.globl	hal_saradc_dma_init
	.hidden	hal_saradc_dma_init
	.type	hal_saradc_dma_init, @function
hal_saradc_dma_init:
.LFB10:
	.loc 1 201 1 is_stmt 1
	.cfi_startproc
	.loc 1 207 5
	.loc 1 207 47 is_stmt 0
	li	a5,1074003968
	li	a4,1
	sw	a4,116(a5)
	.loc 1 208 5 is_stmt 1
	.loc 1 208 52 is_stmt 0
	sw	a4,12(a5)
	.loc 1 210 5 is_stmt 1
	.loc 1 210 28 is_stmt 0
	addi	a5,a5,256
	sw	zero,0(a5)
	.loc 1 211 5 is_stmt 1
	.loc 1 211 28 is_stmt 0
	sw	zero,4(a5)
	.loc 1 212 5 is_stmt 1
	.loc 1 212 29 is_stmt 0
	sw	zero,8(a5)
	.loc 1 213 5 is_stmt 1
	.loc 1 213 29 is_stmt 0
	sw	zero,12(a5)
	.loc 1 214 5 is_stmt 1
	.loc 1 214 43 is_stmt 0
	sw	zero,20(a5)
	.loc 1 215 5 is_stmt 1
	.loc 1 215 30 is_stmt 0
	sw	zero,24(a5)
	.loc 1 216 5 is_stmt 1
	.loc 1 216 32 is_stmt 0
	sw	zero,40(a5)
	.loc 1 217 5 is_stmt 1
	.loc 1 217 31 is_stmt 0
	li	a4,32768
	sw	a4,32(a5)
	.loc 1 218 5 is_stmt 1
	.loc 1 218 30 is_stmt 0
	li	a4,16
	sw	a4,16(a5)
	.loc 1 219 5 is_stmt 1
	.loc 1 219 28 is_stmt 0
	li	a4,1074593792
	addi	a4,a4,16
	sw	a4,0(a5)
	.loc 1 220 5 is_stmt 1
	.loc 1 220 43 is_stmt 0
	li	a4,3
	sw	a4,20(a5)
	.loc 1 221 5 is_stmt 1
	.loc 1 221 33 is_stmt 0
	lw	a4,20(a5)
	.loc 1 222 43
	li	a3,524288
	.loc 1 227 1
	li	a0,0
	.loc 1 221 43
	ori	a4,a4,512
	sw	a4,20(a5)
	.loc 1 222 5 is_stmt 1
	.loc 1 222 33 is_stmt 0
	lw	a4,20(a5)
	.loc 1 222 43
	or	a4,a4,a3
	sw	a4,20(a5)
	.loc 1 223 5 is_stmt 1
	.loc 1 223 33 is_stmt 0
	lw	a4,20(a5)
	.loc 1 223 43
	sw	a4,20(a5)
	.loc 1 225 5 is_stmt 1
	.loc 1 225 49 is_stmt 0
	li	a5,1074593792
	sw	zero,4(a5)
	.loc 1 226 5 is_stmt 1
	.loc 1 227 1 is_stmt 0
	ret
	.cfi_endproc
.LFE10:
	.size	hal_saradc_dma_init, .-hal_saradc_dma_init
	.section	.text.hal_saradc_get_data_immediately_for_special,"ax",@progbits
	.align	1
	.globl	hal_saradc_get_data_immediately_for_special
	.hidden	hal_saradc_get_data_immediately_for_special
	.type	hal_saradc_get_data_immediately_for_special, @function
hal_saradc_get_data_immediately_for_special:
.LFB11:
	.loc 1 230 1 is_stmt 1
	.cfi_startproc
.LVL24:
	addi	sp,sp,-8
	.cfi_def_cfa_offset 8
	sw	a2,0(sp)
	sw	s0,4(sp)
	.cfi_offset 8, -4
	srli	a2,a2,24
.LVL25:
	.loc 1 231 5
	.loc 1 231 7 is_stmt 0
	bne	a2,zero,.L46
	.loc 1 233 9 is_stmt 1
	.loc 1 233 68 is_stmt 0
	slli	a5,a1,16
	srli	a5,a5,16
	.loc 1 233 53
	li	a4,1074593792
	sw	a5,4(a4)
.L46:
	.loc 1 237 5 is_stmt 1
	.loc 1 237 30 is_stmt 0
	li	a5,1074003968
	addi	a5,a5,256
	sw	zero,24(a5)
	.loc 1 240 5 is_stmt 1
	.loc 1 240 28 is_stmt 0
	sw	a0,4(a5)
	.loc 1 242 5 is_stmt 1
	.loc 1 242 79 is_stmt 0 discriminator 1
	li	a4,1074593792
.L47:
	.loc 1 242 12 is_stmt 1 discriminator 1
	.loc 1 242 79 is_stmt 0 discriminator 1
	lbu	a5,8(a4)
	.loc 1 242 12 discriminator 1
	andi	a5,a5,1
	bne	a5,zero,.L47
	.loc 1 245 5 is_stmt 1
	.loc 1 245 30 is_stmt 0
	li	a5,1074003968
	addi	a5,a5,256
	li	a0,32768
.LVL26:
	sw	a0,24(a5)
.LVL27:
	.loc 1 248 5 is_stmt 1
	.loc 1 248 49 is_stmt 0
	sw	zero,4(a4)
	.loc 1 250 5 is_stmt 1
	.loc 1 251 5
	.loc 1 252 5
.LVL28:
	.loc 1 253 5
	.loc 1 253 16 discriminator 1
.LBB5:
	.loc 1 264 22 is_stmt 0
	lw	t1,gpio_base
.LBE5:
	.loc 1 253 11
	li	a4,0
.LBB6:
	.loc 1 262 54
	li	t2,1
.LBE6:
	.loc 1 253 16 discriminator 1
	li	t0,3
.LVL29:
.L50:
.LBB7:
	.loc 1 255 9 is_stmt 1
	.loc 1 255 17 is_stmt 0
	add	a5,sp,a4
	lbu	a0,0(a5)
.LVL30:
	.loc 1 256 9 is_stmt 1
	.loc 1 258 9
	.loc 1 256 51 is_stmt 0
	sra	s0,a2,a4
	.loc 1 261 12
	andi	s0,s0,1
	.loc 1 258 17
	srli	a5,a0,5
.LVL31:
	.loc 1 259 9 is_stmt 1
	.loc 1 261 9
	.loc 1 262 54 is_stmt 0
	sll	a0,t2,a0
.LVL32:
	.loc 1 261 12
	beq	s0,zero,.L48
	.loc 1 262 13 is_stmt 1
	.loc 1 262 47 is_stmt 0
	addi	a5,a5,80
.LVL33:
.L57:
	.loc 1 264 47
	slli	a5,a5,2
	add	a5,t1,a5
	sw	a0,0(a5)
.LVL34:
.LBE7:
	.loc 1 253 20 is_stmt 1 discriminator 2
	addi	a4,a4,1
.LVL35:
	.loc 1 253 16 discriminator 1
	bne	a4,t0,.L50
	.loc 1 268 37 is_stmt 0 discriminator 1
	li	a4,1074003968
.LVL36:
.L51:
	.loc 1 268 11 is_stmt 1 discriminator 1
	.loc 1 268 37 is_stmt 0 discriminator 1
	lw	a5,0(a4)
	.loc 1 268 51 discriminator 1
	andi	a5,a5,1
	.loc 1 268 11 discriminator 1
	bne	a5,zero,.L51
	.loc 1 270 5 is_stmt 1
	.loc 1 270 44 is_stmt 0
	addi	a3,a3,-1
.LVL37:
	.loc 1 270 7
	beq	a2,a3,.L52
	.loc 1 271 9 is_stmt 1
	.loc 1 271 68 is_stmt 0
	slli	a1,a1,16
.LVL38:
	srli	a1,a1,16
	.loc 1 271 53
	li	a5,1074593792
	sw	a1,4(a5)
.L52:
	.loc 1 274 5 is_stmt 1
	.loc 1 275 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_remember_state
	.cfi_restore 8
	li	a0,0
	addi	sp,sp,8
	.cfi_def_cfa_offset 0
	jr	ra
.LVL39:
.L48:
	.cfi_restore_state
.LBB8:
	.loc 1 264 13 is_stmt 1
	.loc 1 264 47 is_stmt 0
	addi	a5,a5,84
.LVL40:
	j	.L57
.LBE8:
	.cfi_endproc
.LFE11:
	.size	hal_saradc_get_data_immediately_for_special, .-hal_saradc_get_data_immediately_for_special
	.globl	__floatunsisf
	.globl	__mulsf3
	.globl	__subsf3
	.globl	__addsf3
	.globl	__divsf3
	.globl	__fixunssfsi
	.section	.text.hal_saradc_get_calibration_voltage_mV,"ax",@progbits
	.align	1
	.globl	hal_saradc_get_calibration_voltage_mV
	.hidden	hal_saradc_get_calibration_voltage_mV
	.type	hal_saradc_get_calibration_voltage_mV, @function
hal_saradc_get_calibration_voltage_mV:
.LFB12:
	.loc 1 278 1 is_stmt 1
	.cfi_startproc
.LVL41:
	.loc 1 279 5
	.loc 1 280 5
	.loc 1 278 1 is_stmt 0
	addi	sp,sp,-16
	.cfi_def_cfa_offset 16
	sw	s1,4(sp)
	.cfi_offset 9, -12
	mv	s1,a0
	.loc 1 280 12
	mv	a0,a1
.LVL42:
	.loc 1 278 1
	sw	ra,12(sp)
	sw	s0,8(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 278 1
	mv	s0,a2
	.loc 1 280 12
	call	__floatunsisf
.LVL43:
	.loc 1 280 29
	lw	a1,.LC0
	call	__mulsf3
.LVL44:
	.loc 1 280 39
	lw	a1,saradc_oe
	call	__subsf3
.LVL45:
	sw	a0,0(sp)
	.loc 1 280 80
	lw	a1,.LC1
	lw	a0,saradc_ge
	call	__addsf3
.LVL46:
	mv	a1,a0
	.loc 1 280 72
	lw	a0,saradc_vref_real
	call	__divsf3
.LVL47:
	mv	a1,a0
	.loc 1 280 8
	lw	a0,0(sp)
	call	__mulsf3
.LVL48:
	.loc 1 281 5 is_stmt 1
	li	a4,1
	beq	s1,a4,.L59
	li	a4,2
	beq	s1,a4,.L60
	li	a4,-4
	bne	s1,zero,.L58
.LVL49:
.L65:
	.loc 1 284 13
	.loc 1 284 45 is_stmt 0
	lw	a1,.LC2
.L66:
	call	__mulsf3
.LVL50:
	.loc 1 284 31
	call	__fixunssfsi
.LVL51:
	sw	a0,0(s0)
	.loc 1 285 13 is_stmt 1
	.loc 1 298 12 is_stmt 0
	li	a4,0
.L58:
	.loc 1 299 1
	lw	ra,12(sp)
	.cfi_remember_state
	.cfi_restore 1
	lw	s0,8(sp)
	.cfi_restore 8
.LVL52:
	lw	s1,4(sp)
	.cfi_restore 9
.LVL53:
	mv	a0,a4
	addi	sp,sp,16
	.cfi_def_cfa_offset 0
	jr	ra
.LVL54:
.L59:
	.cfi_restore_state
	.loc 1 288 13 is_stmt 1
	.loc 1 288 46 is_stmt 0
	lw	a1,.LC3
	call	__divsf3
.LVL55:
	j	.L65
.LVL56:
.L60:
	.loc 1 292 13 is_stmt 1
	.loc 1 292 46 is_stmt 0
	lw	a1,.LC4
	call	__subsf3
.LVL57:
	.loc 1 292 54
	lw	a1,.LC5
	j	.L66
	.cfi_endproc
.LFE12:
	.size	hal_saradc_get_calibration_voltage_mV, .-hal_saradc_get_calibration_voltage_mV
	.section	.text.hal_saradc_init,"ax",@progbits
	.align	1
	.globl	hal_saradc_init
	.hidden	hal_saradc_init
	.type	hal_saradc_init, @function
hal_saradc_init:
.LFB13:
	.loc 1 302 1 is_stmt 1
	.cfi_startproc
.LVL58:
	.loc 1 303 5
	.loc 1 302 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	sw	s0,4(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	.loc 1 303 5
	call	hal_saradc_set_mode
.LVL59:
	.loc 1 305 5 is_stmt 1
	.loc 1 305 42 is_stmt 0
	li	a4,16384
	li	a5,1107820544
	addi	a4,a4,1025
	sw	a4,72(a5)
	.loc 1 306 5 is_stmt 1
	.loc 1 306 42 is_stmt 0
	li	a5,1107820544
	li	a4,1807
	sw	a4,76(a5)
	.loc 1 307 5 is_stmt 1
	.loc 1 307 42 is_stmt 0
	li	a5,1107820544
	li	a4,1039
	sw	a4,80(a5)
	.loc 1 308 5 is_stmt 1
	.loc 1 308 42 is_stmt 0
	li	a4,65
	li	a5,1107820544
	sw	a4,92(a5)
	.loc 1 310 5 is_stmt 1
	.loc 1 310 42 is_stmt 0
	li	a5,1107492864
	addi	a5,a5,672
	sw	zero,0(a5)
	.loc 1 311 5 is_stmt 1
	.loc 1 311 52 is_stmt 0
	li	s0,1074593792
	li	a5,2
	sw	a5,200(s0)
	.loc 1 314 5 is_stmt 1
	call	hal_saradc_enable
.LVL60:
	.loc 1 316 5
	.loc 1 316 42 is_stmt 0
	li	a5,1107361792
	addi	a5,a5,264
	li	a4,3
	sw	a4,0(a5)
	.loc 1 317 5 is_stmt 1
	.loc 1 317 55 is_stmt 0
	li	a5,1
	.loc 1 319 1
	lw	ra,8(sp)
	.cfi_restore 1
	.loc 1 317 55
	sw	a5,192(s0)
	.loc 1 318 5 is_stmt 1
	.loc 1 319 1 is_stmt 0
	lw	s0,4(sp)
	.cfi_restore 8
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE13:
	.size	hal_saradc_init, .-hal_saradc_init
	.section	.text.hal_saradc_deinit,"ax",@progbits
	.align	1
	.globl	hal_saradc_deinit
	.hidden	hal_saradc_deinit
	.type	hal_saradc_deinit, @function
hal_saradc_deinit:
.LFB14:
	.loc 1 322 1 is_stmt 1
	.cfi_startproc
	.loc 1 324 5
	.loc 1 322 1 is_stmt 0
	addi	sp,sp,-12
	.cfi_def_cfa_offset 12
	sw	ra,8(sp)
	.cfi_offset 1, -4
	.loc 1 324 5
	call	hal_saradc_disable
.LVL61:
	.loc 1 325 5 is_stmt 1
	.loc 1 326 1 is_stmt 0
	lw	ra,8(sp)
	.cfi_restore 1
	li	a0,0
	addi	sp,sp,12
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE14:
	.size	hal_saradc_deinit, .-hal_saradc_deinit
	.hidden	g_sw_dma_reg
	.globl	g_sw_dma_reg
	.section	.srodata.g_sw_dma_reg,"a"
	.align	2
	.type	g_sw_dma_reg, @object
	.size	g_sw_dma_reg, 4
g_sw_dma_reg:
	.word	1074004224
	.hidden	g_sw_dma_reg_global_table
	.globl	g_sw_dma_reg_global_table
	.section	.srodata.g_sw_dma_reg_global_table,"a"
	.align	2
	.type	g_sw_dma_reg_global_table, @object
	.size	g_sw_dma_reg_global_table, 4
g_sw_dma_reg_global_table:
	.word	1074003968
	.hidden	saradc_ge
	.globl	saradc_ge
	.section	.sdata.saradc_ge,"aw"
	.align	2
	.type	saradc_ge, @object
	.size	saradc_ge, 4
saradc_ge:
	.word	-1185827049
	.hidden	saradc_oe
	.globl	saradc_oe
	.section	.sdata.saradc_oe,"aw"
	.align	2
	.type	saradc_oe, @object
	.size	saradc_oe, 4
saradc_oe:
	.word	-1185827049
	.hidden	saradc_vref_real
	.globl	saradc_vref_real
	.section	.sdata.saradc_vref_real,"aw"
	.align	2
	.type	saradc_vref_real, @object
	.size	saradc_vref_real, 4
saradc_vref_real:
	.word	1068675105
	.section	.srodata.cst4,"aM",@progbits,4
	.align	2
.LC0:
	.word	964689920
	.align	2
.LC1:
	.word	1065353216
	.align	2
.LC2:
	.word	1148846080
	.align	2
.LC3:
	.word	1052770304
	.align	2
.LC4:
	.word	1060320051
	.align	2
.LC5:
	.word	1157234688
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 3 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
	.file 4 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_adc.h"
	.file 5 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpio.h"
	.file 6 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 7 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_saradc.h"
	.file 8 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpt.h"
	.file 9 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_gpio_internal.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x10d6
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x20
	.4byte	.LASF276
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL23
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x8
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x8
	.byte	0x1
	.byte	0x6
	.4byte	.LASF5
	.uleb128 0x8
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x8
	.byte	0x2
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x8
	.byte	0x4
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x8
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x21
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x8
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x5
	.4byte	.LASF13
	.byte	0x2
	.byte	0x2e
	.byte	0x17
	.4byte	0x34
	.uleb128 0x9
	.4byte	0x7a
	.uleb128 0x11
	.4byte	0x86
	.uleb128 0x5
	.4byte	.LASF14
	.byte	0x2
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x9
	.4byte	0x90
	.uleb128 0x11
	.4byte	0x9c
	.uleb128 0x6
	.4byte	0x90
	.4byte	0xb6
	.uleb128 0x7
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	0x9c
	.4byte	0xc6
	.uleb128 0x7
	.4byte	0x2d
	.byte	0
	.byte	0
	.uleb128 0x9
	.4byte	0xb6
	.uleb128 0x6
	.4byte	0x9c
	.4byte	0xdb
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x4
	.byte	0
	.uleb128 0x9
	.4byte	0xcb
	.uleb128 0x6
	.4byte	0x9c
	.4byte	0xf0
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x1
	.byte	0
	.uleb128 0x9
	.4byte	0xe0
	.uleb128 0x4
	.byte	0x7c
	.byte	0x3
	.byte	0x43
	.4byte	0x250
	.uleb128 0x1
	.4byte	.LASF15
	.byte	0x3
	.byte	0x44
	.byte	0x1d
	.4byte	0xa1
	.byte	0
	.uleb128 0x1
	.4byte	.LASF16
	.byte	0x3
	.byte	0x45
	.byte	0x17
	.4byte	0xc6
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF17
	.byte	0x3
	.byte	0x46
	.byte	0x1d
	.4byte	0xa1
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF18
	.byte	0x3
	.byte	0x47
	.byte	0x17
	.4byte	0x9c
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x3
	.byte	0x48
	.byte	0x17
	.4byte	0x9c
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x3
	.byte	0x49
	.byte	0x1d
	.4byte	0xa1
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0x3
	.byte	0x4a
	.byte	0x17
	.4byte	0x9c
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x3
	.byte	0x4b
	.byte	0x17
	.4byte	0x9c
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x3
	.byte	0x4c
	.byte	0x1d
	.4byte	0xa1
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x3
	.byte	0x4d
	.byte	0x17
	.4byte	0xc6
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x3
	.byte	0x4e
	.byte	0x1d
	.4byte	0xa1
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x3
	.byte	0x4f
	.byte	0x17
	.4byte	0xdb
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x3
	.byte	0x50
	.byte	0x1d
	.4byte	0xa1
	.byte	0x40
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x3
	.byte	0x51
	.byte	0x1d
	.4byte	0xa1
	.byte	0x44
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x3
	.byte	0x52
	.byte	0x17
	.4byte	0xf0
	.byte	0x48
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x3
	.byte	0x53
	.byte	0x1d
	.4byte	0xa1
	.byte	0x50
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x3
	.byte	0x54
	.byte	0x17
	.4byte	0x9c
	.byte	0x54
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x3
	.byte	0x55
	.byte	0x17
	.4byte	0x9c
	.byte	0x58
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x3
	.byte	0x56
	.byte	0x17
	.4byte	0xc6
	.byte	0x5c
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x3
	.byte	0x57
	.byte	0x1d
	.4byte	0xa1
	.byte	0x60
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x3
	.byte	0x58
	.byte	0x17
	.4byte	0x9c
	.byte	0x64
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x3
	.byte	0x59
	.byte	0x17
	.4byte	0x9c
	.byte	0x68
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x3
	.byte	0x5a
	.byte	0x17
	.4byte	0xc6
	.byte	0x6c
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0x3
	.byte	0x5b
	.byte	0x1d
	.4byte	0xa1
	.byte	0x70
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x3
	.byte	0x5c
	.byte	0x17
	.4byte	0x9c
	.byte	0x74
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x3
	.byte	0x5d
	.byte	0x17
	.4byte	0x9c
	.byte	0x78
	.byte	0
	.uleb128 0x5
	.4byte	.LASF41
	.byte	0x3
	.byte	0x5e
	.byte	0x3
	.4byte	0xf5
	.uleb128 0x4
	.byte	0x4
	.byte	0x3
	.byte	0x68
	.4byte	0x299
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x3
	.byte	0x69
	.byte	0x1e
	.4byte	0x86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x3
	.byte	0x6a
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x3
	.byte	0x6b
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x3
	.byte	0x6c
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x3
	.byte	0x67
	.4byte	0x2b9
	.uleb128 0x3
	.4byte	.LASF46
	.byte	0x3
	.byte	0x6d
	.byte	0xb
	.4byte	0x25c
	.uleb128 0x3
	.4byte	.LASF47
	.byte	0x3
	.byte	0x6e
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x4
	.byte	0x2c
	.byte	0x3
	.byte	0x61
	.4byte	0x351
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0x3
	.byte	0x62
	.byte	0x17
	.4byte	0x9c
	.byte	0
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x3
	.byte	0x63
	.byte	0x17
	.4byte	0x9c
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0x3
	.byte	0x64
	.byte	0x17
	.4byte	0x9c
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0x3
	.byte	0x65
	.byte	0x17
	.4byte	0x9c
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0x3
	.byte	0x66
	.byte	0x17
	.4byte	0x9c
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0x3
	.byte	0x6f
	.byte	0x7
	.4byte	0x299
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x3
	.byte	0x70
	.byte	0x17
	.4byte	0x9c
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x3
	.byte	0x71
	.byte	0x17
	.4byte	0x9c
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x3
	.byte	0x72
	.byte	0x17
	.4byte	0x9c
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x3
	.byte	0x73
	.byte	0x1d
	.4byte	0xa1
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x3
	.byte	0x74
	.byte	0x17
	.4byte	0x9c
	.byte	0x28
	.byte	0
	.uleb128 0x5
	.4byte	.LASF59
	.byte	0x3
	.byte	0x75
	.byte	0x3
	.4byte	0x2b9
	.uleb128 0x6
	.4byte	0x9c
	.4byte	0x36d
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x5
	.byte	0
	.uleb128 0x9
	.4byte	0x35d
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x30
	.4byte	0x3af
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x4
	.byte	0x31
	.byte	0x24
	.4byte	0x8b
	.byte	0
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x4
	.byte	0x32
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x4
	.byte	0x33
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x4
	.byte	0x34
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x2f
	.4byte	0x3cf
	.uleb128 0x3
	.4byte	.LASF64
	.byte	0x4
	.byte	0x35
	.byte	0xb
	.4byte	0x372
	.uleb128 0x3
	.4byte	.LASF65
	.byte	0x4
	.byte	0x36
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x3a
	.4byte	0x40c
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x4
	.byte	0x3b
	.byte	0x1e
	.4byte	0x86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x4
	.byte	0x3c
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x4
	.byte	0x3d
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x4
	.byte	0x3e
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x39
	.4byte	0x42c
	.uleb128 0x3
	.4byte	.LASF70
	.byte	0x4
	.byte	0x3f
	.byte	0xb
	.4byte	0x3cf
	.uleb128 0x3
	.4byte	.LASF71
	.byte	0x4
	.byte	0x40
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x4a
	.4byte	0x469
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x4
	.byte	0x4b
	.byte	0x1e
	.4byte	0x86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x4
	.byte	0x4c
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x4
	.byte	0x4d
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x4
	.byte	0x4e
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x49
	.4byte	0x489
	.uleb128 0x3
	.4byte	.LASF76
	.byte	0x4
	.byte	0x4f
	.byte	0xb
	.4byte	0x42c
	.uleb128 0x3
	.4byte	.LASF77
	.byte	0x4
	.byte	0x50
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x54
	.4byte	0x4c6
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x4
	.byte	0x55
	.byte	0x1e
	.4byte	0x86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x4
	.byte	0x56
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x4
	.byte	0x57
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x4
	.byte	0x58
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x53
	.4byte	0x4e6
	.uleb128 0x3
	.4byte	.LASF82
	.byte	0x4
	.byte	0x59
	.byte	0xb
	.4byte	0x489
	.uleb128 0x3
	.4byte	.LASF83
	.byte	0x4
	.byte	0x5a
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x5e
	.4byte	0x523
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x4
	.byte	0x5f
	.byte	0x1e
	.4byte	0x86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x4
	.byte	0x60
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x4
	.byte	0x61
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x4
	.byte	0x62
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x5d
	.4byte	0x543
	.uleb128 0x3
	.4byte	.LASF88
	.byte	0x4
	.byte	0x63
	.byte	0xb
	.4byte	0x4e6
	.uleb128 0x3
	.4byte	.LASF84
	.byte	0x4
	.byte	0x64
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x6b
	.4byte	0x580
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x4
	.byte	0x6c
	.byte	0x1e
	.4byte	0x86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x4
	.byte	0x6d
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x4
	.byte	0x6e
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x4
	.byte	0x6f
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x6a
	.4byte	0x5a0
	.uleb128 0x3
	.4byte	.LASF93
	.byte	0x4
	.byte	0x70
	.byte	0xb
	.4byte	0x543
	.uleb128 0x3
	.4byte	.LASF94
	.byte	0x4
	.byte	0x71
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x76
	.4byte	0x5dd
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0x4
	.byte	0x77
	.byte	0x1e
	.4byte	0x86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x4
	.byte	0x78
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x4
	.byte	0x79
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x4
	.byte	0x7a
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x75
	.4byte	0x5fd
	.uleb128 0x3
	.4byte	.LASF99
	.byte	0x4
	.byte	0x7b
	.byte	0xb
	.4byte	0x5a0
	.uleb128 0x3
	.4byte	.LASF100
	.byte	0x4
	.byte	0x7c
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x8c
	.4byte	0x63a
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x4
	.byte	0x8d
	.byte	0x1e
	.4byte	0x86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x4
	.byte	0x8e
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x4
	.byte	0x8f
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF104
	.byte	0x4
	.byte	0x90
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x8b
	.4byte	0x65a
	.uleb128 0x3
	.4byte	.LASF105
	.byte	0x4
	.byte	0x91
	.byte	0xb
	.4byte	0x5fd
	.uleb128 0x3
	.4byte	.LASF106
	.byte	0x4
	.byte	0x92
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x4
	.byte	0x98
	.4byte	0x697
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0x4
	.byte	0x99
	.byte	0x1e
	.4byte	0x86
	.byte	0
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x4
	.byte	0x9a
	.byte	0x1e
	.4byte	0x86
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x4
	.byte	0x9b
	.byte	0x1e
	.4byte	0x86
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x4
	.byte	0x9c
	.byte	0x1e
	.4byte	0x86
	.byte	0x3
	.byte	0
	.uleb128 0xd
	.byte	0x4
	.byte	0x97
	.4byte	0x6b7
	.uleb128 0x3
	.4byte	.LASF110
	.byte	0x4
	.byte	0x9d
	.byte	0xb
	.4byte	0x65a
	.uleb128 0x3
	.4byte	.LASF111
	.byte	0x4
	.byte	0x9e
	.byte	0x1b
	.4byte	0x9c
	.byte	0
	.uleb128 0x1a
	.2byte	0x180
	.byte	0x4
	.byte	0x2c
	.4byte	0x813
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x4
	.byte	0x2d
	.byte	0xe
	.4byte	0xa6
	.byte	0
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x4
	.byte	0x2e
	.byte	0x17
	.4byte	0x9c
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x4
	.byte	0x37
	.byte	0x7
	.4byte	0x3af
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF115
	.byte	0x4
	.byte	0x41
	.byte	0x7
	.4byte	0x40c
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF116
	.byte	0x4
	.byte	0x43
	.byte	0x1d
	.4byte	0x828
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0x4
	.byte	0x45
	.byte	0x17
	.4byte	0x9c
	.byte	0x90
	.uleb128 0x1
	.4byte	.LASF118
	.byte	0x4
	.byte	0x46
	.byte	0x17
	.4byte	0x9c
	.byte	0x94
	.uleb128 0x1
	.4byte	.LASF119
	.byte	0x4
	.byte	0x47
	.byte	0x17
	.4byte	0x9c
	.byte	0x98
	.uleb128 0x1
	.4byte	.LASF120
	.byte	0x4
	.byte	0x51
	.byte	0x7
	.4byte	0x469
	.byte	0x9c
	.uleb128 0x1
	.4byte	.LASF121
	.byte	0x4
	.byte	0x5b
	.byte	0x7
	.4byte	0x4c6
	.byte	0xa0
	.uleb128 0x1
	.4byte	.LASF122
	.byte	0x4
	.byte	0x65
	.byte	0x7
	.4byte	0x523
	.byte	0xa4
	.uleb128 0x1
	.4byte	.LASF123
	.byte	0x4
	.byte	0x67
	.byte	0x17
	.4byte	0x9c
	.byte	0xa8
	.uleb128 0x1
	.4byte	.LASF124
	.byte	0x4
	.byte	0x72
	.byte	0x7
	.4byte	0x580
	.byte	0xac
	.uleb128 0x1
	.4byte	.LASF125
	.byte	0x4
	.byte	0x7d
	.byte	0x7
	.4byte	0x5dd
	.byte	0xb0
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x4
	.byte	0x7f
	.byte	0x17
	.4byte	0x9c
	.byte	0xb4
	.uleb128 0x1
	.4byte	.LASF127
	.byte	0x4
	.byte	0x81
	.byte	0x1d
	.4byte	0xa1
	.byte	0xb8
	.uleb128 0x1
	.4byte	.LASF128
	.byte	0x4
	.byte	0x83
	.byte	0x1d
	.4byte	0xa1
	.byte	0xbc
	.uleb128 0x1
	.4byte	.LASF129
	.byte	0x4
	.byte	0x85
	.byte	0x17
	.4byte	0x9c
	.byte	0xc0
	.uleb128 0x1
	.4byte	.LASF130
	.byte	0x4
	.byte	0x87
	.byte	0x17
	.4byte	0x9c
	.byte	0xc4
	.uleb128 0x1
	.4byte	.LASF131
	.byte	0x4
	.byte	0x89
	.byte	0x17
	.4byte	0x9c
	.byte	0xc8
	.uleb128 0x1
	.4byte	.LASF132
	.byte	0x4
	.byte	0x93
	.byte	0x7
	.4byte	0x63a
	.byte	0xcc
	.uleb128 0x1
	.4byte	.LASF133
	.byte	0x4
	.byte	0x95
	.byte	0x17
	.4byte	0x9c
	.byte	0xd0
	.uleb128 0x1
	.4byte	.LASF134
	.byte	0x4
	.byte	0x9f
	.byte	0x7
	.4byte	0x697
	.byte	0xd4
	.uleb128 0x1
	.4byte	.LASF135
	.byte	0x4
	.byte	0xa1
	.byte	0x17
	.4byte	0x9c
	.byte	0xd8
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x4
	.byte	0xa2
	.byte	0x17
	.4byte	0x83d
	.byte	0xdc
	.uleb128 0xa
	.4byte	.LASF137
	.byte	0x4
	.byte	0xa3
	.4byte	0x852
	.2byte	0x100
	.byte	0
	.uleb128 0x6
	.4byte	0xa1
	.4byte	0x823
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x1f
	.byte	0
	.uleb128 0x11
	.4byte	0x813
	.uleb128 0x9
	.4byte	0x823
	.uleb128 0x6
	.4byte	0x9c
	.4byte	0x83d
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x8
	.byte	0
	.uleb128 0x9
	.4byte	0x82d
	.uleb128 0x6
	.4byte	0x9c
	.4byte	0x852
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x1f
	.byte	0
	.uleb128 0x9
	.4byte	0x842
	.uleb128 0x5
	.4byte	.LASF138
	.byte	0x4
	.byte	0xa5
	.byte	0x3
	.4byte	0x6b7
	.uleb128 0x1a
	.2byte	0x318
	.byte	0x5
	.byte	0x2b
	.4byte	0x97e
	.uleb128 0x1
	.4byte	.LASF139
	.byte	0x5
	.byte	0x2d
	.byte	0x17
	.4byte	0xf0
	.byte	0
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x5
	.byte	0x2e
	.byte	0x17
	.4byte	0xf0
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF140
	.byte	0x5
	.byte	0x2f
	.byte	0x17
	.4byte	0xf0
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0x5
	.byte	0x30
	.byte	0x17
	.4byte	0xf0
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF141
	.byte	0x5
	.byte	0x31
	.byte	0x17
	.4byte	0xf0
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0x5
	.byte	0x32
	.byte	0x17
	.4byte	0xf0
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF143
	.byte	0x5
	.byte	0x33
	.byte	0x17
	.4byte	0x36d
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF144
	.byte	0x5
	.byte	0x34
	.byte	0x17
	.4byte	0xf0
	.byte	0x48
	.uleb128 0x1
	.4byte	.LASF145
	.byte	0x5
	.byte	0x35
	.byte	0x17
	.4byte	0x9c
	.byte	0x50
	.uleb128 0x1
	.4byte	.LASF146
	.byte	0x5
	.byte	0x36
	.byte	0x17
	.4byte	0x98e
	.byte	0x54
	.uleb128 0xa
	.4byte	.LASF147
	.byte	0x5
	.byte	0x38
	.4byte	0xf0
	.2byte	0x110
	.uleb128 0xa
	.4byte	.LASF148
	.byte	0x5
	.byte	0x39
	.4byte	0xf0
	.2byte	0x118
	.uleb128 0xa
	.4byte	.LASF149
	.byte	0x5
	.byte	0x3a
	.4byte	0xf0
	.2byte	0x120
	.uleb128 0xa
	.4byte	.LASF150
	.byte	0x5
	.byte	0x3b
	.4byte	0x36d
	.2byte	0x128
	.uleb128 0xa
	.4byte	.LASF151
	.byte	0x5
	.byte	0x3c
	.4byte	0xf0
	.2byte	0x140
	.uleb128 0xa
	.4byte	.LASF152
	.byte	0x5
	.byte	0x3d
	.4byte	0xf0
	.2byte	0x148
	.uleb128 0xa
	.4byte	.LASF153
	.byte	0x5
	.byte	0x3e
	.4byte	0xf0
	.2byte	0x150
	.uleb128 0xa
	.4byte	.LASF154
	.byte	0x5
	.byte	0x3f
	.4byte	0x9a3
	.2byte	0x158
	.uleb128 0xa
	.4byte	.LASF155
	.byte	0x5
	.byte	0x41
	.4byte	0x36d
	.2byte	0x200
	.uleb128 0xa
	.4byte	.LASF156
	.byte	0x5
	.byte	0x42
	.4byte	0x9b8
	.2byte	0x218
	.uleb128 0xa
	.4byte	.LASF157
	.byte	0x5
	.byte	0x44
	.4byte	0x36d
	.2byte	0x300
	.byte	0
	.uleb128 0x6
	.4byte	0x9c
	.4byte	0x98e
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x2e
	.byte	0
	.uleb128 0x9
	.4byte	0x97e
	.uleb128 0x6
	.4byte	0x9c
	.4byte	0x9a3
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x29
	.byte	0
	.uleb128 0x9
	.4byte	0x993
	.uleb128 0x6
	.4byte	0x9c
	.4byte	0x9b8
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x39
	.byte	0
	.uleb128 0x9
	.4byte	0x9a8
	.uleb128 0x5
	.4byte	.LASF158
	.byte	0x5
	.byte	0x45
	.byte	0x3
	.4byte	0x863
	.uleb128 0x1b
	.byte	0x7
	.4byte	0x2d
	.byte	0x6
	.2byte	0x27c
	.4byte	0xaa3
	.uleb128 0x2
	.4byte	.LASF159
	.byte	0
	.uleb128 0x2
	.4byte	.LASF160
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF161
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF162
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF163
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF164
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF165
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF166
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF167
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF168
	.byte	0x9
	.uleb128 0x2
	.4byte	.LASF169
	.byte	0xa
	.uleb128 0x2
	.4byte	.LASF170
	.byte	0xb
	.uleb128 0x2
	.4byte	.LASF171
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF172
	.byte	0xd
	.uleb128 0x2
	.4byte	.LASF173
	.byte	0xe
	.uleb128 0x2
	.4byte	.LASF174
	.byte	0xf
	.uleb128 0x2
	.4byte	.LASF175
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF176
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF177
	.byte	0x11
	.uleb128 0x2
	.4byte	.LASF178
	.byte	0x12
	.uleb128 0x2
	.4byte	.LASF179
	.byte	0x13
	.uleb128 0x2
	.4byte	.LASF180
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF181
	.byte	0x15
	.uleb128 0x2
	.4byte	.LASF182
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF183
	.byte	0x17
	.uleb128 0x2
	.4byte	.LASF184
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF185
	.byte	0x19
	.uleb128 0x2
	.4byte	.LASF186
	.byte	0x1a
	.uleb128 0x2
	.4byte	.LASF187
	.byte	0x1b
	.uleb128 0x2
	.4byte	.LASF188
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF189
	.byte	0x1d
	.uleb128 0x2
	.4byte	.LASF190
	.byte	0x1e
	.uleb128 0x2
	.4byte	.LASF191
	.byte	0x1f
	.uleb128 0x2
	.4byte	.LASF192
	.byte	0x20
	.byte	0
	.uleb128 0x12
	.byte	0x5
	.4byte	0x65
	.byte	0x2e
	.4byte	0xacd
	.uleb128 0xc
	.4byte	.LASF193
	.sleb128 -4
	.uleb128 0xc
	.4byte	.LASF194
	.sleb128 -3
	.uleb128 0xc
	.4byte	.LASF195
	.sleb128 -2
	.uleb128 0xc
	.4byte	.LASF196
	.sleb128 -1
	.uleb128 0x2
	.4byte	.LASF197
	.byte	0
	.byte	0
	.uleb128 0x5
	.4byte	.LASF198
	.byte	0x7
	.byte	0x34
	.byte	0x3
	.4byte	0xaa3
	.uleb128 0x12
	.byte	0x7
	.4byte	0x2d
	.byte	0x36
	.4byte	0xb1b
	.uleb128 0x2
	.4byte	.LASF199
	.byte	0
	.uleb128 0x2
	.4byte	.LASF200
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF201
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF202
	.byte	0x3
	.uleb128 0x2
	.4byte	.LASF203
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF204
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF205
	.byte	0x6
	.uleb128 0x2
	.4byte	.LASF206
	.byte	0x7
	.uleb128 0x2
	.4byte	.LASF207
	.byte	0x8
	.byte	0
	.uleb128 0x5
	.4byte	.LASF208
	.byte	0x7
	.byte	0x40
	.byte	0x3
	.4byte	0xad9
	.uleb128 0x12
	.byte	0x7
	.4byte	0x2d
	.byte	0x42
	.4byte	0xb4b
	.uleb128 0x2
	.4byte	.LASF209
	.byte	0
	.uleb128 0x2
	.4byte	.LASF210
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF211
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF212
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF213
	.byte	0x7
	.byte	0x47
	.byte	0x3
	.4byte	0xb27
	.uleb128 0x12
	.byte	0x7
	.4byte	0x2d
	.byte	0x49
	.4byte	0xb7b
	.uleb128 0x2
	.4byte	.LASF214
	.byte	0
	.uleb128 0x2
	.4byte	.LASF215
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF216
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF217
	.byte	0x3
	.byte	0
	.uleb128 0x5
	.4byte	.LASF218
	.byte	0x7
	.byte	0x4e
	.byte	0x3
	.4byte	0xb57
	.uleb128 0x12
	.byte	0x7
	.4byte	0x2d
	.byte	0x50
	.4byte	0xba5
	.uleb128 0x2
	.4byte	.LASF219
	.byte	0
	.uleb128 0x2
	.4byte	.LASF220
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF221
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.4byte	.LASF222
	.byte	0x7
	.byte	0x54
	.byte	0x3
	.4byte	0xb87
	.uleb128 0x4
	.byte	0x84
	.byte	0x7
	.byte	0x56
	.4byte	0xbd4
	.uleb128 0x1
	.4byte	.LASF223
	.byte	0x7
	.byte	0x57
	.byte	0xe
	.4byte	0x90
	.byte	0
	.uleb128 0x1
	.4byte	.LASF224
	.byte	0x7
	.byte	0x58
	.byte	0xe
	.4byte	0xbd4
	.byte	0x4
	.byte	0
	.uleb128 0x6
	.4byte	0x90
	.4byte	0xbe4
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x1f
	.byte	0
	.uleb128 0x5
	.4byte	.LASF225
	.byte	0x7
	.byte	0x59
	.byte	0x3
	.4byte	0xbb1
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.byte	0x5b
	.4byte	0xc13
	.uleb128 0x1
	.4byte	.LASF226
	.byte	0x7
	.byte	0x5c
	.byte	0xd
	.4byte	0xc13
	.byte	0
	.uleb128 0x1
	.4byte	.LASF227
	.byte	0x7
	.byte	0x5d
	.byte	0xd
	.4byte	0x7a
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.4byte	0x7a
	.4byte	0xc23
	.uleb128 0x7
	.4byte	0x2d
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.4byte	.LASF228
	.byte	0x7
	.byte	0x5e
	.byte	0x3
	.4byte	0xbf0
	.uleb128 0x1b
	.byte	0x5
	.4byte	0x65
	.byte	0x8
	.2byte	0x153
	.4byte	0xc6d
	.uleb128 0xc
	.4byte	.LASF229
	.sleb128 -7
	.uleb128 0xc
	.4byte	.LASF230
	.sleb128 -6
	.uleb128 0xc
	.4byte	.LASF231
	.sleb128 -5
	.uleb128 0xc
	.4byte	.LASF232
	.sleb128 -4
	.uleb128 0xc
	.4byte	.LASF233
	.sleb128 -3
	.uleb128 0xc
	.4byte	.LASF234
	.sleb128 -2
	.uleb128 0xc
	.4byte	.LASF235
	.sleb128 -1
	.uleb128 0x2
	.4byte	.LASF236
	.byte	0
	.byte	0
	.uleb128 0x22
	.4byte	.LASF237
	.byte	0x8
	.2byte	0x15c
	.byte	0x3
	.4byte	0xc2f
	.uleb128 0xf
	.4byte	0x90
	.uleb128 0x13
	.4byte	.LASF239
	.byte	0x2a
	.byte	0x7
	.4byte	0xc90
	.uleb128 0x5
	.byte	0x3
	.4byte	saradc_vref_real
	.uleb128 0x8
	.byte	0x4
	.byte	0x4
	.4byte	.LASF238
	.uleb128 0x13
	.4byte	.LASF240
	.byte	0x2a
	.byte	0x21
	.4byte	0xc90
	.uleb128 0x5
	.byte	0x3
	.4byte	saradc_oe
	.uleb128 0x13
	.4byte	.LASF241
	.byte	0x2a
	.byte	0x36
	.4byte	0xc90
	.uleb128 0x5
	.byte	0x3
	.4byte	saradc_ge
	.uleb128 0x23
	.4byte	.LASF242
	.byte	0x9
	.byte	0x8e
	.byte	0x1e
	.4byte	0xcc5
	.uleb128 0xf
	.4byte	0x9bd
	.uleb128 0x13
	.4byte	.LASF243
	.byte	0xc4
	.byte	0x1e
	.4byte	0xce0
	.uleb128 0x5
	.byte	0x3
	.4byte	g_sw_dma_reg_global_table
	.uleb128 0xf
	.4byte	0x250
	.uleb128 0x11
	.4byte	0xcdb
	.uleb128 0x13
	.4byte	.LASF244
	.byte	0xc5
	.byte	0x18
	.4byte	0xcfb
	.uleb128 0x5
	.byte	0x3
	.4byte	g_sw_dma_reg
	.uleb128 0xf
	.4byte	0x351
	.uleb128 0x11
	.4byte	0xcf6
	.uleb128 0x24
	.4byte	.LASF277
	.byte	0x8
	.2byte	0x18d
	.byte	0x12
	.4byte	0xc6d
	.4byte	0xd17
	.uleb128 0x25
	.4byte	0x90
	.byte	0
	.uleb128 0x26
	.4byte	.LASF267
	.byte	0x1
	.2byte	0x141
	.byte	0x12
	.4byte	0xacd
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd3c
	.uleb128 0xb
	.4byte	.LVL61
	.4byte	0x101b
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF247
	.2byte	0x12d
	.4byte	0xacd
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xda7
	.uleb128 0x14
	.4byte	.LASF245
	.2byte	0x12d
	.byte	0x39
	.4byte	0xb4b
	.4byte	.LLST21
	.uleb128 0x14
	.4byte	.LASF246
	.2byte	0x12d
	.byte	0x5e
	.4byte	0xb7b
	.4byte	.LLST22
	.uleb128 0x1d
	.4byte	.LVL59
	.4byte	0x106e
	.4byte	0xd9d
	.uleb128 0x16
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
	.uleb128 0x16
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
	.uleb128 0xb
	.4byte	.LVL60
	.4byte	0x102f
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF248
	.2byte	0x115
	.4byte	0xacd
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe5b
	.uleb128 0x14
	.4byte	.LASF246
	.2byte	0x115
	.byte	0x52
	.4byte	0xb7b
	.4byte	.LLST17
	.uleb128 0x14
	.4byte	.LASF249
	.2byte	0x115
	.byte	0x69
	.4byte	0x90
	.4byte	.LLST18
	.uleb128 0x14
	.4byte	.LASF250
	.2byte	0x115
	.byte	0x7d
	.4byte	0xc7a
	.4byte	.LLST19
	.uleb128 0x27
	.string	"mV"
	.byte	0x1
	.2byte	0x117
	.byte	0xb
	.4byte	0xc90
	.4byte	.LLST20
	.uleb128 0xb
	.4byte	.LVL43
	.4byte	0x10a3
	.uleb128 0xb
	.4byte	.LVL44
	.4byte	0x10ac
	.uleb128 0xb
	.4byte	.LVL45
	.4byte	0x10b5
	.uleb128 0xb
	.4byte	.LVL46
	.4byte	0x10be
	.uleb128 0xb
	.4byte	.LVL47
	.4byte	0x10c7
	.uleb128 0xb
	.4byte	.LVL48
	.4byte	0x10ac
	.uleb128 0xb
	.4byte	.LVL50
	.4byte	0x10ac
	.uleb128 0xb
	.4byte	.LVL51
	.4byte	0x10d0
	.uleb128 0xb
	.4byte	.LVL55
	.4byte	0x10c7
	.uleb128 0xb
	.4byte	.LVL57
	.4byte	0x10b5
	.byte	0
	.uleb128 0x15
	.4byte	.LASF251
	.byte	0xe5
	.4byte	0xacd
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf03
	.uleb128 0xe
	.4byte	.LASF252
	.byte	0xe5
	.byte	0x51
	.4byte	0xf03
	.4byte	.LLST8
	.uleb128 0xe
	.4byte	.LASF223
	.byte	0xe5
	.byte	0x68
	.4byte	0x90
	.4byte	.LLST9
	.uleb128 0x18
	.4byte	.LASF253
	.byte	0xe5
	.byte	0x94
	.4byte	0xc23
	.uleb128 0x5
	.byte	0x93
	.uleb128 0x3
	.byte	0x5c
	.byte	0x93
	.uleb128 0x1
	.uleb128 0xe
	.4byte	.LASF254
	.byte	0xe5
	.byte	0xa6
	.4byte	0x7a
	.4byte	.LLST10
	.uleb128 0x19
	.4byte	.LASF255
	.byte	0xfa
	.byte	0xe
	.4byte	0x90
	.4byte	.LLST11
	.uleb128 0x19
	.4byte	.LASF256
	.byte	0xfb
	.byte	0xe
	.4byte	0x90
	.4byte	.LLST12
	.uleb128 0x17
	.string	"i"
	.byte	0xfc
	.byte	0x9
	.4byte	0x65
	.4byte	.LLST13
	.uleb128 0x28
	.4byte	.LLRL14
	.uleb128 0x19
	.4byte	.LASF226
	.byte	0xff
	.byte	0x11
	.4byte	0x7a
	.4byte	.LLST15
	.uleb128 0x29
	.4byte	.LASF257
	.byte	0x1
	.2byte	0x100
	.byte	0x11
	.4byte	0x7a
	.4byte	.LLST16
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	0x9c
	.uleb128 0x1e
	.4byte	.LASF265
	.byte	0xc8
	.4byte	0xacd
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x15
	.4byte	.LASF258
	.byte	0xa3
	.4byte	0xacd
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf87
	.uleb128 0xe
	.4byte	.LASF259
	.byte	0xa3
	.byte	0x41
	.4byte	0xf87
	.4byte	.LLST4
	.uleb128 0xe
	.4byte	.LASF260
	.byte	0xa3
	.byte	0x60
	.4byte	0xb1b
	.4byte	.LLST5
	.uleb128 0x2a
	.4byte	.LBB3
	.4byte	.LBE3-.LBB3
	.4byte	0xf6e
	.uleb128 0x17
	.string	"ch"
	.byte	0xa7
	.byte	0x12
	.4byte	0x7a
	.4byte	.LLST6
	.byte	0
	.uleb128 0x1f
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.uleb128 0x17
	.string	"ch"
	.byte	0xae
	.byte	0x12
	.4byte	0x7a
	.4byte	.LLST7
	.byte	0
	.byte	0
	.uleb128 0xf
	.4byte	0xbe4
	.uleb128 0x15
	.4byte	.LASF261
	.byte	0x96
	.4byte	0xacd
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xfcc
	.uleb128 0xe
	.4byte	.LASF259
	.byte	0x96
	.byte	0x45
	.4byte	0xf87
	.4byte	.LLST2
	.uleb128 0x1f
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.uleb128 0x17
	.string	"ch"
	.byte	0x9b
	.byte	0x12
	.4byte	0x7a
	.4byte	.LLST3
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LASF262
	.byte	0x81
	.4byte	0xacd
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x101b
	.uleb128 0xe
	.4byte	.LASF223
	.byte	0x81
	.byte	0x34
	.4byte	0x90
	.4byte	.LLST1
	.uleb128 0x18
	.4byte	.LASF263
	.byte	0x81
	.byte	0x59
	.4byte	0xba5
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x2b
	.4byte	.LASF264
	.byte	0x1
	.byte	0x83
	.byte	0xe
	.4byte	0x90
	.byte	0
	.uleb128 0x2c
	.uleb128 0x2d
	.string	"ch"
	.byte	0x1
	.byte	0x85
	.byte	0x12
	.4byte	0x7a
	.byte	0
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF266
	.byte	0x74
	.4byte	0xacd
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x2e
	.4byte	.LASF268
	.byte	0x1
	.byte	0x65
	.byte	0x12
	.4byte	0xacd
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x106e
	.uleb128 0x1d
	.4byte	.LVL5
	.4byte	0xd00
	.4byte	0x105d
	.uleb128 0x16
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.uleb128 0x2f
	.4byte	.LVL6
	.4byte	0xd00
	.uleb128 0x16
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.byte	0
	.uleb128 0x15
	.4byte	.LASF269
	.byte	0x2c
	.4byte	0xacd
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10a3
	.uleb128 0xe
	.4byte	.LASF245
	.byte	0x2c
	.byte	0x3d
	.4byte	0xb4b
	.4byte	.LLST0
	.uleb128 0x18
	.4byte	.LASF246
	.byte	0x2c
	.byte	0x62
	.4byte	0xb7b
	.uleb128 0x1
	.byte	0x5b
	.byte	0
	.uleb128 0x10
	.4byte	.LASF270
	.4byte	.LASF270
	.uleb128 0x10
	.4byte	.LASF271
	.4byte	.LASF271
	.uleb128 0x10
	.4byte	.LASF272
	.4byte	.LASF272
	.uleb128 0x10
	.4byte	.LASF273
	.4byte	.LASF273
	.uleb128 0x10
	.4byte	.LASF274
	.4byte	.LASF274
	.uleb128 0x10
	.4byte	.LASF275
	.4byte	.LASF275
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
	.byte	0
	.byte	0
	.uleb128 0x4
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
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 23
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xf
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x15
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
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
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.sleb128 18
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
	.uleb128 0x1f
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x22
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x24
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
	.uleb128 0x25
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
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
	.uleb128 0x27
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
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
	.uleb128 0x28
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x2d
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
	.byte	0
	.byte	0
	.uleb128 0x2e
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
	.uleb128 0x2f
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
.LLST21:
	.byte	0x6
	.4byte	.LVL58
	.byte	0x4
	.uleb128 .LVL58-.LVL58
	.uleb128 .LVL59-1-.LVL58
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL59-1-.LVL58
	.uleb128 .LFE13-.LVL58
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
.LLST22:
	.byte	0x6
	.4byte	.LVL58
	.byte	0x4
	.uleb128 .LVL58-.LVL58
	.uleb128 .LVL59-1-.LVL58
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL59-1-.LVL58
	.uleb128 .LFE13-.LVL58
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
	.uleb128 .LVL53-.LVL41
	.uleb128 0x1
	.byte	0x59
	.byte	0x4
	.uleb128 .LVL53-.LVL41
	.uleb128 .LVL54-.LVL41
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
	.uleb128 .LVL54-.LVL41
	.uleb128 .LFE12-.LVL41
	.uleb128 0x1
	.byte	0x59
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
	.uleb128 .LFE12-.LVL41
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
.LLST19:
	.byte	0x6
	.4byte	.LVL41
	.byte	0x4
	.uleb128 .LVL41-.LVL41
	.uleb128 .LVL43-1-.LVL41
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL43-1-.LVL41
	.uleb128 .LVL52-.LVL41
	.uleb128 0x1
	.byte	0x58
	.byte	0x4
	.uleb128 .LVL52-.LVL41
	.uleb128 .LVL54-.LVL41
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xc
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x2d
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL54-.LVL41
	.uleb128 .LFE12-.LVL41
	.uleb128 0x1
	.byte	0x58
	.byte	0
.LLST20:
	.byte	0x6
	.4byte	.LVL41
	.byte	0x4
	.uleb128 .LVL41-.LVL41
	.uleb128 .LVL48-.LVL41
	.uleb128 0x6
	.byte	0x9e
	.uleb128 0x4
	.4byte	0
	.byte	0x4
	.uleb128 .LVL48-.LVL41
	.uleb128 .LVL49-.LVL41
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL54-.LVL41
	.uleb128 .LVL55-1-.LVL41
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL56-.LVL41
	.uleb128 .LVL57-1-.LVL41
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.LLST8:
	.byte	0x6
	.4byte	.LVL24
	.byte	0x4
	.uleb128 .LVL24-.LVL24
	.uleb128 .LVL26-.LVL24
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL26-.LVL24
	.uleb128 .LVL27-.LVL24
	.uleb128 0x2
	.byte	0x7f
	.sleb128 4
	.byte	0x4
	.uleb128 .LVL27-.LVL24
	.uleb128 .LFE11-.LVL24
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
.LLST9:
	.byte	0x6
	.4byte	.LVL24
	.byte	0x4
	.uleb128 .LVL24-.LVL24
	.uleb128 .LVL38-.LVL24
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL38-.LVL24
	.uleb128 .LVL39-.LVL24
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
	.uleb128 .LVL39-.LVL24
	.uleb128 .LFE11-.LVL24
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST10:
	.byte	0x6
	.4byte	.LVL24
	.byte	0x4
	.uleb128 .LVL24-.LVL24
	.uleb128 .LVL37-.LVL24
	.uleb128 0x1
	.byte	0x5d
	.byte	0x4
	.uleb128 .LVL37-.LVL24
	.uleb128 .LVL39-.LVL24
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xd
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL39-.LVL24
	.uleb128 .LFE11-.LVL24
	.uleb128 0x1
	.byte	0x5d
	.byte	0
.LLST11:
	.byte	0x6
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL33-.LVL31
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL33-.LVL31
	.uleb128 .LVL34-.LVL31
	.uleb128 0xf
	.byte	0x91
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x38
	.byte	0x1c
	.byte	0x94
	.byte	0x1
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x35
	.byte	0x25
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL39-.LVL31
	.uleb128 .LVL40-.LVL31
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL40-.LVL31
	.uleb128 .LFE11-.LVL31
	.uleb128 0x4
	.byte	0x7f
	.sleb128 -84
	.byte	0x9f
	.byte	0
.LLST12:
	.byte	0x6
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL32-.LVL31
	.uleb128 0x8
	.byte	0x7a
	.sleb128 0
	.byte	0x4f
	.byte	0x1a
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL32-.LVL31
	.uleb128 .LVL34-.LVL31
	.uleb128 0xf
	.byte	0x91
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x38
	.byte	0x1c
	.byte	0x94
	.byte	0x1
	.byte	0x4f
	.byte	0x1a
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL39-.LVL31
	.uleb128 .LFE11-.LVL31
	.uleb128 0xf
	.byte	0x91
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x38
	.byte	0x1c
	.byte	0x94
	.byte	0x1
	.byte	0x4f
	.byte	0x1a
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST13:
	.byte	0x6
	.4byte	.LVL28
	.byte	0x4
	.uleb128 .LVL28-.LVL28
	.uleb128 .LVL29-.LVL28
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL29-.LVL28
	.uleb128 .LVL36-.LVL28
	.uleb128 0x1
	.byte	0x5e
	.byte	0x4
	.uleb128 .LVL39-.LVL28
	.uleb128 .LFE11-.LVL28
	.uleb128 0x1
	.byte	0x5e
	.byte	0
.LLST15:
	.byte	0x6
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL32-.LVL30
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL32-.LVL30
	.uleb128 .LVL34-.LVL30
	.uleb128 0x7
	.byte	0x91
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x38
	.byte	0x1c
	.byte	0x4
	.uleb128 .LVL39-.LVL30
	.uleb128 .LFE11-.LVL30
	.uleb128 0x7
	.byte	0x91
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x22
	.byte	0x38
	.byte	0x1c
	.byte	0
.LLST16:
	.byte	0x6
	.4byte	.LVL30
	.byte	0x4
	.uleb128 .LVL30-.LVL30
	.uleb128 .LVL35-.LVL30
	.uleb128 0x8
	.byte	0x7c
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x26
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL35-.LVL30
	.uleb128 .LVL36-.LVL30
	.uleb128 0x8
	.byte	0x7c
	.sleb128 0
	.byte	0x7e
	.sleb128 -1
	.byte	0x26
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL39-.LVL30
	.uleb128 .LFE11-.LVL30
	.uleb128 0x8
	.byte	0x7c
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x26
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.byte	0
.LLST4:
	.byte	0x6
	.4byte	.LVL14
	.byte	0x4
	.uleb128 .LVL14-.LVL14
	.uleb128 .LVL19-.LVL14
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL19-.LVL14
	.uleb128 .LVL21-.LVL14
	.uleb128 0x3
	.byte	0x7a
	.sleb128 -4
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL21-.LVL14
	.uleb128 .LFE9-.LVL14
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
.LLST5:
	.byte	0x6
	.4byte	.LVL14
	.byte	0x4
	.uleb128 .LVL14-.LVL14
	.uleb128 .LVL16-.LVL14
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL16-.LVL14
	.uleb128 .LFE9-.LVL14
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
.LLST6:
	.byte	0x6
	.4byte	.LVL15
	.byte	0x4
	.uleb128 .LVL15-.LVL15
	.uleb128 .LVL16-.LVL15
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL16-.LVL15
	.uleb128 .LVL17-.LVL15
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL17-.LVL15
	.uleb128 .LVL18-.LVL15
	.uleb128 0x3
	.byte	0x7f
	.sleb128 1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL18-.LVL15
	.uleb128 .LVL20-.LVL15
	.uleb128 0x3
	.byte	0x7f
	.sleb128 0
	.byte	0x9f
	.byte	0
.LLST7:
	.byte	0x6
	.4byte	.LVL21
	.byte	0x4
	.uleb128 .LVL21-.LVL21
	.uleb128 .LVL22-.LVL21
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL22-.LVL21
	.uleb128 .LVL23-.LVL21
	.uleb128 0x3
	.byte	0x7f
	.sleb128 1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL23-.LVL21
	.uleb128 .LFE9-.LVL21
	.uleb128 0x3
	.byte	0x7f
	.sleb128 0
	.byte	0x9f
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
	.uleb128 .LVL11-.LVL9
	.uleb128 0x3
	.byte	0x7a
	.sleb128 -4
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL11-.LVL9
	.uleb128 .LFE8-.LVL9
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
	.4byte	.LVL11
	.byte	0x4
	.uleb128 .LVL11-.LVL11
	.uleb128 .LVL12-.LVL11
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL12-.LVL11
	.uleb128 .LVL13-.LVL11
	.uleb128 0x3
	.byte	0x7f
	.sleb128 1
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL13-.LVL11
	.uleb128 .LFE8-.LVL11
	.uleb128 0x3
	.byte	0x7f
	.sleb128 0
	.byte	0x9f
	.byte	0
.LLST1:
	.byte	0x6
	.4byte	.LVL7
	.byte	0x4
	.uleb128 .LVL7-.LVL7
	.uleb128 .LVL8-.LVL7
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL8-.LVL7
	.uleb128 .LFE7-.LVL7
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
	.uleb128 .LVL3-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL3-.LVL0
	.uleb128 .LVL4-.LVL0
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
	.uleb128 .LVL4-.LVL0
	.uleb128 .LFE4-.LVL0
	.uleb128 0x1
	.byte	0x5a
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0x6c
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
.LLRL14:
	.byte	0x5
	.4byte	.LBB5
	.byte	0x4
	.uleb128 .LBB5-.LBB5
	.uleb128 .LBE5-.LBB5
	.byte	0x4
	.uleb128 .LBB6-.LBB5
	.uleb128 .LBE6-.LBB5
	.byte	0x4
	.uleb128 .LBB7-.LBB5
	.uleb128 .LBE7-.LBB5
	.byte	0x4
	.uleb128 .LBB8-.LBB5
	.uleb128 .LBE8-.LBB5
	.byte	0
.LLRL23:
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
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF205:
	.string	"HAL_ADC_AVERAGE_256"
.LASF133:
	.string	"RG_D2A_SAR_CLK_EN"
.LASF253:
	.string	"gpio_cfg"
.LASF211:
	.string	"HAL_SARADC_DATA_RATE_LS_MODE"
.LASF223:
	.string	"channel_mask"
.LASF194:
	.string	"HAL_ADC_STATUS_ERROR_BUSY"
.LASF267:
	.string	"hal_saradc_deinit"
.LASF265:
	.string	"hal_saradc_dma_init"
.LASF60:
	.string	"ADC_STAT"
.LASF256:
	.string	"index_num"
.LASF110:
	.string	"ADC_SRAM_CON_CELLS"
.LASF193:
	.string	"HAL_ADC_STATUS_INVALID_PARAMETER"
.LASF102:
	.string	"AUXADC_MSB1_CON"
.LASF222:
	.string	"hal_saradc_gpio_mode_t"
.LASF252:
	.string	"dest_address"
.LASF43:
	.string	"GDMA_SIZE"
.LASF277:
	.string	"hal_gpt_delay_us"
.LASF276:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF39:
	.string	"RG_GLB_CLK_SET"
.LASF275:
	.string	"__fixunssfsi"
.LASF6:
	.string	"short int"
.LASF73:
	.string	"AUTO_SEL"
.LASF33:
	.string	"RESERVE5"
.LASF66:
	.string	"AUTO_AVG_EN"
.LASF263:
	.string	"mode"
.LASF221:
	.string	"HAL_SARADC_GPIO_MODE_MAX"
.LASF54:
	.string	"GDMA_START"
.LASF27:
	.string	"RG_GLB_BUSY"
.LASF140:
	.string	"GPIO_DOUT"
.LASF248:
	.string	"hal_saradc_get_calibration_voltage_mV"
.LASF141:
	.string	"GPIO_DIN"
.LASF139:
	.string	"GPIO_DIR"
.LASF113:
	.string	"AUXADC_CON1"
.LASF65:
	.string	"AUXADC_CON3"
.LASF71:
	.string	"AUXADC_CON4"
.LASF119:
	.string	"AUXADC_CON5"
.LASF77:
	.string	"AUXADC_CON6"
.LASF245:
	.string	"data_rate"
.LASF94:
	.string	"MACRO_CON2"
.LASF209:
	.string	"HAL_SARADC_DATA_RATE_HS_MODE"
.LASF254:
	.string	"mux_max_index"
.LASF118:
	.string	"AUXADC_SLP_STATE"
.LASF108:
	.string	"ADC_SRAM_CON_RESERVED0"
.LASF109:
	.string	"ADC_SRAM_CON_RESERVED1"
.LASF44:
	.string	"GDMA_SETTING"
.LASF14:
	.string	"uint32_t"
.LASF130:
	.string	"RG_AUXADC_DEBUG_EN"
.LASF57:
	.string	"GDMA_RLCT"
.LASF125:
	.string	"ANA_EN_CON_UNION"
.LASF138:
	.string	"ADC_REGISTER_T"
.LASF238:
	.string	"float"
.LASF40:
	.string	"RG_GLB_CLK_CLR"
.LASF85:
	.string	"EXT_AUX_EN"
.LASF91:
	.string	"MACRO_CON2_RESERVED0"
.LASF92:
	.string	"MACRO_CON2_RESERVED1"
.LASF96:
	.string	"RG_AUXADC_REF_SEL"
.LASF90:
	.string	"RG_AUXADC_LDO_OUT_EN"
.LASF41:
	.string	"DMA_REGISTER_GLOABL_T"
.LASF129:
	.string	"ACD_FUNC_MODE_CTL"
.LASF2:
	.string	"long long unsigned int"
.LASF127:
	.string	"AUXADC_AVG_READY"
.LASF105:
	.string	"AUXADC_MSB_CON_CELLS"
.LASF79:
	.string	"ACD_AUX_PWDB"
.LASF36:
	.string	"RG_GLB_CPU3_INT_CLR"
.LASF68:
	.string	"AUXADC_CON4_RESERVED0"
.LASF69:
	.string	"AUXADC_CON4_RESERVED1"
.LASF143:
	.string	"GPIO_MODE"
.LASF25:
	.string	"RG_GLB_LIMITER"
.LASF95:
	.string	"AUXADC_EN"
.LASF20:
	.string	"RG_GLB_CPU1_INT_CFG"
.LASF121:
	.string	"ACD_CON_SEL_UNION"
.LASF234:
	.string	"HAL_GPT_STATUS_ERROR_PORT"
.LASF18:
	.string	"RG_GLB_CPU0_INT_SET"
.LASF175:
	.string	"HAL_SARADC_CHANNEL_GPIO_MAX"
.LASF99:
	.string	"ANA_EN_CON_CELLS"
.LASF230:
	.string	"HAL_GPT_STATUS_ERROR_START_TOO_LONG"
.LASF213:
	.string	"hal_saradc_data_rate_t"
.LASF151:
	.string	"GPIO_DOUT_SET"
.LASF45:
	.string	"GDMA_ITEN"
.LASF93:
	.string	"MACRO_CON2_CELLS"
.LASF218:
	.string	"hal_saradc_measure_mode_t"
.LASF116:
	.string	"AUXADC_DATA"
.LASF59:
	.string	"GDMA_REGISTER_T"
.LASF135:
	.string	"AUXADC_RESERVE"
.LASF259:
	.string	"saradc_data"
.LASF268:
	.string	"hal_saradc_enable"
.LASF55:
	.string	"GDMA_INTSTA"
.LASF48:
	.string	"GDMA_SRC"
.LASF169:
	.string	"HAL_SARADC_CHANNEL_10"
.LASF170:
	.string	"HAL_SARADC_CHANNEL_11"
.LASF269:
	.string	"hal_saradc_set_mode"
.LASF172:
	.string	"HAL_SARADC_CHANNEL_13"
.LASF173:
	.string	"HAL_SARADC_CHANNEL_14"
.LASF174:
	.string	"HAL_SARADC_CHANNEL_15"
.LASF82:
	.string	"ACD_CON_SEL_CELLS"
.LASF177:
	.string	"HAL_SARADC_CHANNEL_17"
.LASF178:
	.string	"HAL_SARADC_CHANNEL_18"
.LASF179:
	.string	"HAL_SARADC_CHANNEL_19"
.LASF58:
	.string	"GDMA_LIMITER"
.LASF217:
	.string	"HAL_SARADC_MEASURE_MAX"
.LASF226:
	.string	"gpio_pin"
.LASF159:
	.string	"HAL_SARADC_CHANNEL_0"
.LASF160:
	.string	"HAL_SARADC_CHANNEL_1"
.LASF161:
	.string	"HAL_SARADC_CHANNEL_2"
.LASF162:
	.string	"HAL_SARADC_CHANNEL_3"
.LASF163:
	.string	"HAL_SARADC_CHANNEL_4"
.LASF164:
	.string	"HAL_SARADC_CHANNEL_5"
.LASF165:
	.string	"HAL_SARADC_CHANNEL_6"
.LASF166:
	.string	"HAL_SARADC_CHANNEL_7"
.LASF167:
	.string	"HAL_SARADC_CHANNEL_8"
.LASF168:
	.string	"HAL_SARADC_CHANNEL_9"
.LASF19:
	.string	"RG_GLB_CPU0_INT_CLR"
.LASF186:
	.string	"HAL_SARADC_CHANNEL_26"
.LASF62:
	.string	"AUXADC_CON3_RESERVED0"
.LASF63:
	.string	"AUXADC_CON3_RESERVED1"
.LASF12:
	.string	"char"
.LASF153:
	.string	"GPIO_DOUT_CLR"
.LASF101:
	.string	"AUXADC_MSB0_CON"
.LASF180:
	.string	"HAL_SARADC_CHANNEL_20"
.LASF181:
	.string	"HAL_SARADC_CHANNEL_21"
.LASF182:
	.string	"HAL_SARADC_CHANNEL_22"
.LASF183:
	.string	"HAL_SARADC_CHANNEL_23"
.LASF184:
	.string	"HAL_SARADC_CHANNEL_24"
.LASF185:
	.string	"HAL_SARADC_CHANNEL_25"
.LASF204:
	.string	"HAL_ADC_AVERAGE_128"
.LASF187:
	.string	"HAL_SARADC_CHANNEL_27"
.LASF188:
	.string	"HAL_SARADC_CHANNEL_28"
.LASF189:
	.string	"HAL_SARADC_CHANNEL_29"
.LASF117:
	.string	"AUXADC_SLP_LIST"
.LASF123:
	.string	"AUXADC_DIV_CON"
.LASF13:
	.string	"uint8_t"
.LASF227:
	.string	"mux_index"
.LASF15:
	.string	"RG_GLB_STA"
.LASF132:
	.string	"AUXADC_MSB_CON_UNION"
.LASF28:
	.string	"RG_GLB_INTR"
.LASF197:
	.string	"HAL_ADC_STATUS_OK"
.LASF233:
	.string	"HAL_GPT_STATUS_ERROR"
.LASF155:
	.string	"GPIO_MODE_SET"
.LASF97:
	.string	"ANA_EN_CON_RESERVED0"
.LASF98:
	.string	"ANA_EN_CON_RESERVED1"
.LASF137:
	.string	"AVG_DATA"
.LASF49:
	.string	"GDMA_DST"
.LASF190:
	.string	"HAL_SARADC_CHANNEL_30"
.LASF191:
	.string	"HAL_SARADC_CHANNEL_31"
.LASF10:
	.string	"long long int"
.LASF255:
	.string	"reg_num"
.LASF251:
	.string	"hal_saradc_get_data_immediately_for_special"
.LASF115:
	.string	"AUXADC_CON4_UNION"
.LASF270:
	.string	"__floatunsisf"
.LASF64:
	.string	"AUXADC_CON3_CELLS"
.LASF52:
	.string	"GDMA_COUNT"
.LASF111:
	.string	"ADC_SRAM_CON"
.LASF120:
	.string	"AUXADC_CON6_UNION"
.LASF244:
	.string	"g_sw_dma_reg"
.LASF50:
	.string	"GDMA_WPPT"
.LASF131:
	.string	"AUXADC_SPL_CON"
.LASF257:
	.string	"gpio_data"
.LASF53:
	.string	"GDMA_CON_UNION"
.LASF207:
	.string	"HAL_ADC_AVERAGE_MAX"
.LASF246:
	.string	"measure_mode"
.LASF145:
	.string	"GPIO_BACKUP"
.LASF106:
	.string	"AUXADC_MSB_CON"
.LASF30:
	.string	"RG_GLB_CPU2_INT_CFG"
.LASF242:
	.string	"gpio_base"
.LASF21:
	.string	"RG_GLB_CPU1_INT_SET"
.LASF70:
	.string	"AUXADC_CON4_CELLS"
.LASF157:
	.string	"GPIO_MODE_CLR"
.LASF219:
	.string	"HAL_SARADC_GPIO_DIGITAL_MODE"
.LASF247:
	.string	"hal_saradc_init"
.LASF128:
	.string	"AUXADC_AVG_DATA"
.LASF147:
	.string	"GPIO_DIR_SET"
.LASF76:
	.string	"AUXADC_CON6_CELLS"
.LASF236:
	.string	"HAL_GPT_STATUS_OK"
.LASF126:
	.string	"AUXADC_AVG_NUM"
.LASF232:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USED"
.LASF239:
	.string	"saradc_vref_real"
.LASF11:
	.string	"long double"
.LASF46:
	.string	"GDMA_CON_CELLS"
.LASF80:
	.string	"ACD_CON_SEL_RESERVED0"
.LASF81:
	.string	"ACD_CON_SEL_RESERVED1"
.LASF229:
	.string	"HAL_GPT_STATUS_ERROR_RESTART_ERROR"
.LASF272:
	.string	"__subsf3"
.LASF61:
	.string	"SOFT_RST"
.LASF112:
	.string	"RESERVED0"
.LASF136:
	.string	"RESERVED1"
.LASF142:
	.string	"RESERVED2"
.LASF144:
	.string	"RESERVED3"
.LASF146:
	.string	"RESERVED4"
.LASF148:
	.string	"RESERVED5"
.LASF261:
	.string	"hal_saradc_get_data_immediately"
.LASF152:
	.string	"RESERVED7"
.LASF154:
	.string	"RESERVED8"
.LASF156:
	.string	"RESERVED9"
.LASF107:
	.string	"RG_ADC2SRAM_EN"
.LASF258:
	.string	"hal_saradc_get_data_average"
.LASF8:
	.string	"long int"
.LASF22:
	.string	"RG_GLB_CPU1_INT_CLR"
.LASF208:
	.string	"hal_adc_average_t"
.LASF203:
	.string	"HAL_ADC_AVERAGE_64"
.LASF235:
	.string	"HAL_GPT_STATUS_INVALID_PARAMETER"
.LASF264:
	.string	"temp"
.LASF72:
	.string	"AUTO_AUXADC_EN"
.LASF266:
	.string	"hal_saradc_disable"
.LASF250:
	.string	"cal_voltage_mV"
.LASF149:
	.string	"GPIO_DIR_CLR"
.LASF215:
	.string	"HAL_SARADC_MEASURE_DIV_MODE"
.LASF220:
	.string	"HAL_SARADC_GPIO_ANALOG_MODE"
.LASF231:
	.string	"HAL_GPT_STATUS_ERROR_PORT_USE_FULL"
.LASF84:
	.string	"EXT_AUX_SEL"
.LASF3:
	.string	"unsigned int"
.LASF78:
	.string	"ACD_MODE"
.LASF262:
	.string	"hal_saradc_set_gpio_mode"
.LASF171:
	.string	"HAL_SARADC_CHANNEL_12"
.LASF198:
	.string	"hal_adc_status_t"
.LASF35:
	.string	"RG_GLB_CPU3_INT_SET"
.LASF176:
	.string	"HAL_SARADC_CHANNEL_16"
.LASF9:
	.string	"long unsigned int"
.LASF103:
	.string	"AUXADC_MSB_CON_RESERVED0"
.LASF104:
	.string	"AUXADC_MSB_CON_RESERVED1"
.LASF249:
	.string	"raw_data"
.LASF271:
	.string	"__mulsf3"
.LASF199:
	.string	"HAL_ADC_AVERAGE_1"
.LASF200:
	.string	"HAL_ADC_AVERAGE_2"
.LASF201:
	.string	"HAL_ADC_AVERAGE_4"
.LASF124:
	.string	"MACRO_CON2_UNION"
.LASF202:
	.string	"HAL_ADC_AVERAGE_8"
.LASF38:
	.string	"RG_GLB_CLK_CFG"
.LASF237:
	.string	"hal_gpt_status_t"
.LASF86:
	.string	"EXT_AUX_SEL_RESERVED0"
.LASF87:
	.string	"EXT_AUX_SEL_RESERVED1"
.LASF47:
	.string	"GDMA_CON"
.LASF4:
	.string	"unsigned char"
.LASF158:
	.string	"GPIO_BASE_REGISTER_T"
.LASF228:
	.string	"hal_saradc_special_gpio_cfg_t"
.LASF260:
	.string	"average_num"
.LASF83:
	.string	"ACD_CON_SEL"
.LASF243:
	.string	"g_sw_dma_reg_global_table"
.LASF122:
	.string	"EXT_AUX_SEL_UNION"
.LASF89:
	.string	"RG_AUXADC_LDO_EN"
.LASF34:
	.string	"RG_GLB_CPU3_INT_CFG"
.LASF192:
	.string	"HAL_SARADC_CHANNEL_MAX"
.LASF31:
	.string	"RG_GLB_CPU2_INT_SET"
.LASF56:
	.string	"GDMA_ACKINT"
.LASF23:
	.string	"RG_GLB_SWRST"
.LASF273:
	.string	"__addsf3"
.LASF74:
	.string	"AUXADC_CON6_RESERVED0"
.LASF75:
	.string	"AUXADC_CON6_RESERVED1"
.LASF51:
	.string	"GDMA_WPTO"
.LASF210:
	.string	"HAL_SARADC_DATA_RATE_MS_MODE"
.LASF100:
	.string	"ANA_EN_CON"
.LASF224:
	.string	"channel_data"
.LASF241:
	.string	"saradc_ge"
.LASF216:
	.string	"HAL_SARADC_MEASURE_DIFF_MODE"
.LASF5:
	.string	"signed char"
.LASF7:
	.string	"short unsigned int"
.LASF212:
	.string	"HAL_SARADC_DATA_RATE_MAX"
.LASF88:
	.string	"EXT_AUX_SEL_CELLS"
.LASF42:
	.string	"GDMA_DIRECTION"
.LASF114:
	.string	"AUXADC_CON3_UNION"
.LASF196:
	.string	"HAL_ADC_STATUS_ERROR"
.LASF206:
	.string	"HAL_ADC_AVERAGE_512"
.LASF274:
	.string	"__divsf3"
.LASF240:
	.string	"saradc_oe"
.LASF150:
	.string	"RESERVED6"
.LASF225:
	.string	"hal_saradc_data_t"
.LASF32:
	.string	"RG_GLB_CPU2_INT_CLR"
.LASF134:
	.string	"ADC_SRAM_CON_UNION"
.LASF195:
	.string	"HAL_ADC_STATUS_ERROR_CHANNEL"
.LASF16:
	.string	"RESERVE1"
.LASF24:
	.string	"RESERVE2"
.LASF26:
	.string	"RESERVE3"
.LASF29:
	.string	"RESERVE4"
.LASF67:
	.string	"AUTOSET"
.LASF37:
	.string	"RESERVE6"
.LASF17:
	.string	"RG_GLB_CPU0_INT_CFG"
.LASF214:
	.string	"HAL_SARADC_MEASURE_SE_MODE"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_saradc.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
