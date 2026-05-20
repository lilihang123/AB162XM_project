	.file	"hid_common.c"
	.option nopic
	.attribute arch, "rv32e1p9_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 4
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/workdir/airoha/risc-v" "/workdir/airoha/common/applications/hid/src/hid_common.c"
	.section	.text.hid_common_set_app_feature,"ax",@progbits
	.align	1
	.globl	hid_common_set_app_feature
	.hidden	hid_common_set_app_feature
	.type	hid_common_set_app_feature, @function
hid_common_set_app_feature:
.LFB15:
	.file 1 "/workdir/airoha/common/applications/hid/src/hid_common.c"
	.loc 1 58 1
	.cfi_startproc
.LVL0:
	.loc 1 59 5
	.loc 1 59 15 is_stmt 0
	lw	a4,hid_common
	.loc 1 59 39
	li	a5,1
	sll	a5,a5,a0
	.loc 1 59 30
	lw	a0,0(a4)
.LVL1:
	or	a0,a0,a5
	sw	a0,0(a4)
	.loc 1 60 1
	ret
	.cfi_endproc
.LFE15:
	.size	hid_common_set_app_feature, .-hid_common_set_app_feature
	.section	.text.hid_common_clear_app_feature,"ax",@progbits
	.align	1
	.globl	hid_common_clear_app_feature
	.hidden	hid_common_clear_app_feature
	.type	hid_common_clear_app_feature, @function
hid_common_clear_app_feature:
.LFB16:
	.loc 1 63 1 is_stmt 1
	.cfi_startproc
.LVL2:
	.loc 1 64 5
	.loc 1 64 15 is_stmt 0
	lw	a3,hid_common
	.loc 1 64 30
	lw	a4,0(a3)
	.loc 1 64 41
	li	a5,1
	sll	a5,a5,a0
	.loc 1 64 34
	not	a5,a5
	.loc 1 64 30
	and	a5,a4,a5
	sw	a5,0(a3)
	.loc 1 65 1
	ret
	.cfi_endproc
.LFE16:
	.size	hid_common_clear_app_feature, .-hid_common_clear_app_feature
	.section	.text.hid_common_set_app_para,"ax",@progbits
	.align	1
	.globl	hid_common_set_app_para
	.hidden	hid_common_set_app_para
	.type	hid_common_set_app_para, @function
hid_common_set_app_para:
.LFB17:
	.loc 1 69 1 is_stmt 1
	.cfi_startproc
.LVL3:
	.loc 1 70 5
	li	a4,7
	.loc 1 69 1 is_stmt 0
	mv	a5,a2
	.loc 1 70 5
	bgtu	a0,a4,.L3
	lla	a3,.L6
	slli	a0,a0,2
.LVL4:
	add	a0,a0,a3
	lw	a4,0(a0)
	add	a4,a4,a3
	jr	a4
	.section	.rodata.hid_common_set_app_para,"a",@progbits
	.align	2
	.align	2
.L6:
	.word	.L12-.L6
	.word	.L11-.L6
	.word	.L3-.L6
	.word	.L10-.L6
	.word	.L9-.L6
	.word	.L8-.L6
	.word	.L7-.L6
	.word	.L5-.L6
	.section	.text.hid_common_set_app_para
.L10:
	.loc 1 74 13 is_stmt 1
	.loc 1 74 16 is_stmt 0
	li	a4,2
	bne	a2,a4,.L3
	.loc 1 75 17 is_stmt 1
	.loc 1 75 24 is_stmt 0
	lw	a0,hid_common
	.loc 1 75 17
	li	a2,2
.LVL5:
	addi	a0,a0,57
.LVL6:
.L16:
.LBB2:
	.loc 1 119 13
	tail	memcpy
.LVL7:
.L9:
.LBE2:
.LBB3:
	.loc 1 82 13 is_stmt 1
	.loc 1 83 13
	.loc 1 84 13
	.loc 1 83 16 is_stmt 0
	li	a4,14
	andi	a2,a2,0xff
.LVL8:
	bleu	a5,a4,.L13
	li	a2,14
.L13:
	.loc 1 84 35
	lw	a0,hid_common
	.loc 1 84 13
	addi	a0,a0,32
	j	.L16
.LVL9:
.L7:
.LBE3:
.LBB4:
	.loc 1 91 13 is_stmt 1
	.loc 1 92 13
	.loc 1 93 13
	.loc 1 92 16 is_stmt 0
	li	a4,4
	andi	a2,a2,0xff
.LVL10:
	bleu	a5,a4,.L14
	li	a2,4
.L14:
	.loc 1 93 20
	lw	a0,hid_common
	.loc 1 93 13
	addi	a0,a0,24
	j	.L16
.LVL11:
.L5:
.LBE4:
	.loc 1 108 13 is_stmt 1
	.loc 1 108 52 is_stmt 0
	lbu	a4,0(a1)
	.loc 1 108 46
	lw	a5,hid_common
	.loc 1 108 52
	sw	a4,28(a5)
	.loc 1 110 9 is_stmt 1
	ret
.L8:
.LBB5:
	.loc 1 117 13
.LVL12:
	.loc 1 118 13
	.loc 1 119 13
	.loc 1 118 16 is_stmt 0
	li	a4,3
	andi	a2,a2,0xff
.LVL13:
	bleu	a5,a4,.L15
	li	a2,3
.L15:
	.loc 1 119 20
	lw	a0,hid_common
	.loc 1 119 13
	addi	a0,a0,59
	j	.L16
.LVL14:
.L12:
.LBE5:
	.loc 1 127 13 is_stmt 1
	.loc 1 127 48 is_stmt 0
	lbu	a4,0(a1)
	.loc 1 127 23
	lw	a5,hid_common
	.loc 1 127 42
	sb	a4,20(a5)
	.loc 1 128 13 is_stmt 1
	.loc 1 128 44 is_stmt 0
	lbu	a4,1(a1)
	sb	a4,21(a5)
	.loc 1 130 9 is_stmt 1
	ret
.L11:
	.loc 1 134 13
	.loc 1 134 50 is_stmt 0
	lbu	a4,0(a1)
	.loc 1 134 23
	lw	a5,hid_common
	.loc 1 134 44
	sb	a4,22(a5)
	.loc 1 135 13 is_stmt 1
	.loc 1 135 46 is_stmt 0
	lbu	a4,1(a1)
	sb	a4,23(a5)
	.loc 1 137 9 is_stmt 1
.L3:
	.loc 1 143 1 is_stmt 0
	ret
	.cfi_endproc
.LFE17:
	.size	hid_common_set_app_para, .-hid_common_set_app_para
	.section	.text.hid_common_set_hid_para,"ax",@progbits
	.align	1
	.globl	hid_common_set_hid_para
	.hidden	hid_common_set_hid_para
	.type	hid_common_set_hid_para, @function
hid_common_set_hid_para:
.LFB18:
	.loc 1 146 1 is_stmt 1
	.cfi_startproc
.LVL15:
	.loc 1 147 5
	.loc 1 148 5
	.loc 1 161 9
	.loc 1 164 5
	.loc 1 165 1 is_stmt 0
	li	a0,0
.LVL16:
	ret
	.cfi_endproc
.LFE18:
	.size	hid_common_set_hid_para, .-hid_common_set_hid_para
	.section	.text.hid_common_set_hid_exp_flag,"ax",@progbits
	.align	1
	.globl	hid_common_set_hid_exp_flag
	.hidden	hid_common_set_hid_exp_flag
	.type	hid_common_set_hid_exp_flag, @function
hid_common_set_hid_exp_flag:
.LFB19:
	.loc 1 168 1 is_stmt 1
	.cfi_startproc
.LVL17:
	.loc 1 169 5
	.loc 1 169 15 is_stmt 0
	lw	a4,hid_common
	.loc 1 169 36
	li	a5,1
	sll	a5,a5,a0
	.loc 1 169 27
	lw	a0,72(a4)
.LVL18:
	or	a0,a0,a5
	sw	a0,72(a4)
	.loc 1 170 1
	ret
	.cfi_endproc
.LFE19:
	.size	hid_common_set_hid_exp_flag, .-hid_common_set_hid_exp_flag
	.section	.text.hid_common_clear_hid_exp_flag,"ax",@progbits
	.align	1
	.globl	hid_common_clear_hid_exp_flag
	.hidden	hid_common_clear_hid_exp_flag
	.type	hid_common_clear_hid_exp_flag, @function
hid_common_clear_hid_exp_flag:
.LFB20:
	.loc 1 173 1 is_stmt 1
	.cfi_startproc
.LVL19:
	.loc 1 174 5
	.loc 1 174 15 is_stmt 0
	lw	a3,hid_common
	.loc 1 174 27
	lw	a4,72(a3)
	.loc 1 174 38
	li	a5,1
	sll	a5,a5,a0
	.loc 1 174 31
	not	a5,a5
	.loc 1 174 27
	and	a5,a4,a5
	sw	a5,72(a3)
	.loc 1 175 1
	ret
	.cfi_endproc
.LFE20:
	.size	hid_common_clear_hid_exp_flag, .-hid_common_clear_hid_exp_flag
	.section	.text.hid_common_set_dongle_scenario,"ax",@progbits
	.align	1
	.globl	hid_common_set_dongle_scenario
	.hidden	hid_common_set_dongle_scenario
	.type	hid_common_set_dongle_scenario, @function
hid_common_set_dongle_scenario:
.LFB21:
	.loc 1 178 1 is_stmt 1
	.cfi_startproc
.LVL20:
	.loc 1 179 5
	.loc 1 179 37 is_stmt 0
	lw	a5,hid_common
	sw	a0,68(a5)
	.loc 1 180 1
	ret
	.cfi_endproc
.LFE21:
	.size	hid_common_set_dongle_scenario, .-hid_common_set_dongle_scenario
	.section	.text.hid_common_set_hid_exp_features,"ax",@progbits
	.align	1
	.globl	hid_common_set_hid_exp_features
	.hidden	hid_common_set_hid_exp_features
	.type	hid_common_set_hid_exp_features, @function
hid_common_set_hid_exp_features:
.LFB22:
	.loc 1 183 1 is_stmt 1
	.cfi_startproc
.LVL21:
	.loc 1 184 5
	.loc 1 184 30 is_stmt 0
	lw	a5,hid_common
	sw	a0,76(a5)
	.loc 1 185 1
	ret
	.cfi_endproc
.LFE22:
	.size	hid_common_set_hid_exp_features, .-hid_common_set_hid_exp_features
	.section	.text.hid_common_get_hid_exp_features,"ax",@progbits
	.align	1
	.globl	hid_common_get_hid_exp_features
	.hidden	hid_common_get_hid_exp_features
	.type	hid_common_get_hid_exp_features, @function
hid_common_get_hid_exp_features:
.LFB23:
	.loc 1 188 1 is_stmt 1
	.cfi_startproc
.LVL22:
	.loc 1 189 5
	.loc 1 189 8 is_stmt 0
	beq	a0,zero,.L22
	.loc 1 190 9 is_stmt 1
	.loc 1 190 44 is_stmt 0
	lw	a5,hid_common
	lw	a5,76(a5)
	.loc 1 190 27
	sw	a5,0(a0)
.L22:
	.loc 1 192 1
	ret
	.cfi_endproc
.LFE23:
	.size	hid_common_get_hid_exp_features, .-hid_common_get_hid_exp_features
	.section	.text.hid_common_get_dongle_scenario,"ax",@progbits
	.align	1
	.globl	hid_common_get_dongle_scenario
	.hidden	hid_common_get_dongle_scenario
	.type	hid_common_get_dongle_scenario, @function
hid_common_get_dongle_scenario:
.LFB24:
	.loc 1 196 1 is_stmt 1
	.cfi_startproc
	.loc 1 197 5
	.loc 1 197 27 is_stmt 0
	lw	a5,hid_common
	.loc 1 198 1
	lw	a0,68(a5)
	ret
	.cfi_endproc
.LFE24:
	.size	hid_common_get_dongle_scenario, .-hid_common_get_dongle_scenario
	.section	.text.hid_common_sync_debug,"ax",@progbits
	.align	1
	.globl	hid_common_sync_debug
	.hidden	hid_common_sync_debug
	.type	hid_common_sync_debug, @function
hid_common_sync_debug:
.LFB25:
	.loc 1 201 1 is_stmt 1
	.cfi_startproc
.LVL23:
	.loc 1 202 5
	.loc 1 202 39 is_stmt 0
	lw	a1,hid_common
	.loc 1 202 5
	li	a2,10
	addi	a1,a1,88
	tail	memcpy
.LVL24:
	.cfi_endproc
.LFE25:
	.size	hid_common_sync_debug, .-hid_common_sync_debug
	.section	.text.hid_common_set_combo_key,"ax",@progbits
	.align	1
	.globl	hid_common_set_combo_key
	.hidden	hid_common_set_combo_key
	.type	hid_common_set_combo_key, @function
hid_common_set_combo_key:
.LFB26:
	.loc 1 207 1 is_stmt 1
	.cfi_startproc
.LVL25:
	.loc 1 208 5
	.loc 1 208 15 is_stmt 0
	lw	a5,hid_common
	.loc 1 208 36
	sw	a0,8(a5)
	.loc 1 209 5 is_stmt 1
	.loc 1 209 41 is_stmt 0
	sw	a1,12(a5)
	.loc 1 210 5 is_stmt 1
	.loc 1 210 34 is_stmt 0
	sw	a2,16(a5)
	.loc 1 211 1
	ret
	.cfi_endproc
.LFE26:
	.size	hid_common_set_combo_key, .-hid_common_set_combo_key
	.section	.text.hid_common_get_combo_key_list,"ax",@progbits
	.align	1
	.globl	hid_common_get_combo_key_list
	.hidden	hid_common_get_combo_key_list
	.type	hid_common_get_combo_key_list, @function
hid_common_get_combo_key_list:
.LFB27:
	.loc 1 214 1 is_stmt 1
	.cfi_startproc
.LVL26:
	.loc 1 215 5
	.loc 1 215 53 is_stmt 0
	lw	a5,hid_common
	.loc 1 215 58
	lw	a4,8(a5)
	.loc 1 215 21
	sw	a4,0(a0)
	.loc 1 216 5 is_stmt 1
	.loc 1 216 43 is_stmt 0
	lw	a4,12(a5)
	.loc 1 216 26
	sw	a4,0(a1)
	.loc 1 217 5 is_stmt 1
	.loc 1 217 36 is_stmt 0
	lw	a5,16(a5)
	.loc 1 217 19
	sw	a5,0(a2)
	.loc 1 218 1
	ret
	.cfi_endproc
.LFE27:
	.size	hid_common_get_combo_key_list, .-hid_common_get_combo_key_list
	.section	.text.hid_common_set_key_remap_data,"ax",@progbits
	.align	1
	.globl	hid_common_set_key_remap_data
	.hidden	hid_common_set_key_remap_data
	.type	hid_common_set_key_remap_data, @function
hid_common_set_key_remap_data:
.LFB28:
	.loc 1 223 1 is_stmt 1
	.cfi_startproc
.LVL27:
	.loc 1 224 5
	.loc 1 224 12 is_stmt 0
	slli	a5,a1,3
	add	a5,a5,a1
	slli	a5,a5,6
	addi	a5,a5,98
	lw	a4,hid_common
	.loc 1 224 5
	mv	a1,a0
.LVL28:
	li	a2,576
	add	a0,a4,a5
.LVL29:
	tail	memcpy
.LVL30:
	.cfi_endproc
.LFE28:
	.size	hid_common_set_key_remap_data, .-hid_common_set_key_remap_data
	.section	.text.hid_common_get_backend_key_remap_data,"ax",@progbits
	.align	1
	.globl	hid_common_get_backend_key_remap_data
	.hidden	hid_common_get_backend_key_remap_data
	.type	hid_common_get_backend_key_remap_data, @function
hid_common_get_backend_key_remap_data:
.LFB29:
	.loc 1 228 1 is_stmt 1
	.cfi_startproc
.LVL31:
	.loc 1 229 5
	.loc 1 229 58 is_stmt 0
	slli	a5,a1,3
	add	a5,a5,a1
	.loc 1 229 37
	lw	a4,hid_common
	.loc 1 229 58
	slli	a5,a5,6
	add	a1,a4,a5
.LVL32:
	lhu	a3,98(a1)
	lw	a4,100(a1)
	li	a5,65536
	addi	a5,a5,-1
	.loc 1 229 25
	sb	a3,0(a0)
	.loc 1 229 58
	and	a4,a4,a5
	.loc 1 229 25
	srli	a3,a3,8
	sb	a3,1(a0)
	slli	a3,a4,16
	sb	a4,2(a0)
	srli	a4,a3,24
	sb	a4,3(a0)
	.loc 1 230 5 is_stmt 1
	.loc 1 230 28 is_stmt 0
	lbu	a4,102(a1)
	sb	a4,4(a0)
	lhu	a4,102(a1)
	srli	a4,a4,8
	sb	a4,5(a0)
	.loc 1 231 5 is_stmt 1
	.loc 1 231 31 is_stmt 0
	lbu	a4,104(a1)
	sb	a4,6(a0)
	lbu	a4,105(a1)
	sb	a4,7(a0)
	.loc 1 232 5 is_stmt 1
	.loc 1 232 63 is_stmt 0
	lhu	a3,106(a1)
	lw	a4,108(a1)
	.loc 1 232 24
	sb	a3,8(a0)
	.loc 1 232 63
	and	a4,a4,a5
	.loc 1 232 24
	srli	a3,a3,8
	sb	a3,9(a0)
	slli	a3,a4,16
	sb	a4,10(a0)
	srli	a4,a3,24
	sb	a4,11(a0)
	.loc 1 233 5 is_stmt 1
	.loc 1 233 67 is_stmt 0
	lw	a4,392(a1)
	lhu	a3,390(a1)
	and	a5,a4,a5
	.loc 1 233 26
	slli	a4,a5,16
	sb	a3,12(a0)
	sb	a5,14(a0)
	srli	a3,a3,8
	srli	a5,a4,24
	sb	a3,13(a0)
	sb	a5,15(a0)
	.loc 1 234 1
	ret
	.cfi_endproc
.LFE29:
	.size	hid_common_get_backend_key_remap_data, .-hid_common_get_backend_key_remap_data
	.section	.text.hid_common_get_frontend_key_remap_data,"ax",@progbits
	.align	1
	.globl	hid_common_get_frontend_key_remap_data
	.hidden	hid_common_get_frontend_key_remap_data
	.type	hid_common_get_frontend_key_remap_data, @function
hid_common_get_frontend_key_remap_data:
.LFB30:
	.loc 1 237 1 is_stmt 1
	.cfi_startproc
.LVL33:
	.loc 1 238 5
	.loc 1 238 58 is_stmt 0
	slli	a4,a1,3
	add	a4,a4,a1
	.loc 1 238 37
	lw	a5,hid_common
	.loc 1 238 58
	slli	a4,a4,6
	add	a1,a5,a4
.LVL34:
	lhu	a4,98(a1)
	lw	a5,100(a1)
	li	a3,65536
	addi	a3,a3,-1
	and	a5,a5,a3
	.loc 1 238 25
	sb	a4,0(a0)
	srli	a4,a4,8
	sb	a4,1(a0)
	slli	a4,a5,16
	sb	a5,2(a0)
	srli	a5,a4,24
	sb	a5,3(a0)
	.loc 1 239 5 is_stmt 1
	.loc 1 239 56 is_stmt 0
	lhu	a4,102(a1)
	lw	a5,104(a1)
	.loc 1 239 23
	sb	a4,4(a0)
	.loc 1 239 56
	and	a5,a5,a3
	.loc 1 239 23
	srli	a4,a4,8
	sb	a4,5(a0)
	slli	a4,a5,16
	sb	a5,6(a0)
	srli	a5,a4,24
	sb	a5,7(a0)
	.loc 1 240 1
	ret
	.cfi_endproc
.LFE30:
	.size	hid_common_get_frontend_key_remap_data, .-hid_common_get_frontend_key_remap_data
	.section	.text.hid_common_clear_key_remap_data,"ax",@progbits
	.align	1
	.globl	hid_common_clear_key_remap_data
	.hidden	hid_common_clear_key_remap_data
	.type	hid_common_clear_key_remap_data, @function
hid_common_clear_key_remap_data:
.LFB31:
	.loc 1 243 1 is_stmt 1
	.cfi_startproc
.LVL35:
	.loc 1 244 5
	.loc 1 244 12 is_stmt 0
	slli	a5,a0,3
	add	a5,a5,a0
	slli	a5,a5,6
	addi	a5,a5,98
	lw	a0,hid_common
.LVL36:
	.loc 1 244 5
	li	a2,576
	li	a1,0
	add	a0,a0,a5
	tail	memset
.LVL37:
	.cfi_endproc
.LFE31:
	.size	hid_common_clear_key_remap_data, .-hid_common_clear_key_remap_data
	.section	.text.hid_common_clear_all_key_remap_data,"ax",@progbits
	.align	1
	.globl	hid_common_clear_all_key_remap_data
	.hidden	hid_common_clear_all_key_remap_data
	.type	hid_common_clear_all_key_remap_data, @function
hid_common_clear_all_key_remap_data:
.LFB32:
	.loc 1 248 1 is_stmt 1
	.cfi_startproc
	.loc 1 249 5
	.loc 1 249 22 is_stmt 0
	lw	a0,hid_common
	.loc 1 249 5
	li	a2,4096
	addi	a2,a2,-1216
	li	a1,0
	addi	a0,a0,98
	tail	memset
.LVL38:
	.cfi_endproc
.LFE32:
	.size	hid_common_clear_all_key_remap_data, .-hid_common_clear_all_key_remap_data
	.hidden	hid_common
	.globl	hid_common
	.section	.sdata.hid_common,"aw"
	.align	2
	.type	hid_common, @object
	.size	hid_common, 4
hid_common:
	.word	ccm_hid_common_para
	.text
.Letext0:
	.file 2 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stddef.h"
	.file 3 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h"
	.file 4 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
	.file 5 "/workdir/airoha/common/applications/hid/inc/hid_common_debug.h"
	.file 6 "/workdir/airoha/common/applications/hid/inc/hid_common_report_rate.h"
	.file 7 "/workdir/airoha/common/applications/hid/inc/hid_common_key_remap.h"
	.file 8 "/workdir/airoha/common/applications/hid/inc/hid_common_report_structure.h"
	.file 9 "/workdir/airoha/common/applications/hid/inc/hid_common.h"
	.file 10 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_eint_internal.h"
	.file 11 "/workdir/airoha/common/drivers/chip/ab162x/inc/hal_cross_core_config.h"
	.file 12 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/riscv-none-elf/include/string.h"
	.file 13 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xebc
	.2byte	0x5
	.byte	0x1
	.byte	0x4
	.4byte	.Ldebug_abbrev0
	.uleb128 0x23
	.4byte	.LASF224
	.byte	0x1d
	.4byte	.LASF0
	.4byte	.LASF1
	.4byte	.LLRL16
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x8
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
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
	.uleb128 0x24
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x2
	.byte	0xd6
	.byte	0x16
	.4byte	0x34
	.uleb128 0x8
	.byte	0x10
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x25
	.byte	0x4
	.uleb128 0x1a
	.4byte	0x7f
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x3
	.byte	0x22
	.byte	0x15
	.4byte	0x3b
	.uleb128 0x3
	.4byte	.LASF15
	.byte	0x3
	.byte	0x25
	.byte	0x13
	.4byte	0x42
	.uleb128 0x3
	.4byte	.LASF16
	.byte	0x3
	.byte	0x2e
	.byte	0x17
	.4byte	0x2d
	.uleb128 0x14
	.4byte	0xa5
	.uleb128 0x3
	.4byte	.LASF17
	.byte	0x3
	.byte	0x31
	.byte	0x1c
	.4byte	0x49
	.uleb128 0x3
	.4byte	.LASF18
	.byte	0x3
	.byte	0x34
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x14
	.4byte	0xc2
	.uleb128 0x26
	.4byte	.LASF225
	.byte	0x7
	.byte	0x4
	.4byte	0x34
	.byte	0xd
	.2byte	0x128
	.byte	0x11
	.4byte	0x159
	.uleb128 0x1
	.4byte	.LASF19
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF20
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF21
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF22
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF23
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF25
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF26
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF27
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF28
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF29
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF30
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF31
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF32
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF33
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF34
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF36
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF37
	.byte	0x1f
	.byte	0
	.uleb128 0xb
	.4byte	0xa5
	.4byte	0x169
	.uleb128 0xd
	.4byte	0x34
	.byte	0x1
	.byte	0
	.uleb128 0x15
	.4byte	0x34
	.byte	0x4
	.2byte	0x407
	.4byte	0x2cc
	.uleb128 0x1
	.4byte	.LASF38
	.byte	0
	.uleb128 0x1
	.4byte	.LASF39
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF40
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF41
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF42
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF43
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF44
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF45
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF46
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF47
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF48
	.byte	0xa
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0xb
	.uleb128 0x1
	.4byte	.LASF50
	.byte	0xc
	.uleb128 0x1
	.4byte	.LASF51
	.byte	0xd
	.uleb128 0x1
	.4byte	.LASF52
	.byte	0xe
	.uleb128 0x1
	.4byte	.LASF53
	.byte	0xf
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0x10
	.uleb128 0x1
	.4byte	.LASF55
	.byte	0x11
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x12
	.uleb128 0x1
	.4byte	.LASF57
	.byte	0x13
	.uleb128 0x1
	.4byte	.LASF58
	.byte	0x14
	.uleb128 0x1
	.4byte	.LASF59
	.byte	0x15
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x16
	.uleb128 0x1
	.4byte	.LASF61
	.byte	0x17
	.uleb128 0x1
	.4byte	.LASF62
	.byte	0x18
	.uleb128 0x1
	.4byte	.LASF63
	.byte	0x19
	.uleb128 0x1
	.4byte	.LASF64
	.byte	0x1a
	.uleb128 0x1
	.4byte	.LASF65
	.byte	0x1b
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0x1c
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1d
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x1e
	.uleb128 0x1
	.4byte	.LASF69
	.byte	0x1f
	.uleb128 0x1
	.4byte	.LASF70
	.byte	0x20
	.uleb128 0x1
	.4byte	.LASF71
	.byte	0x21
	.uleb128 0x1
	.4byte	.LASF72
	.byte	0x22
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0x23
	.uleb128 0x1
	.4byte	.LASF74
	.byte	0x24
	.uleb128 0x1
	.4byte	.LASF75
	.byte	0x25
	.uleb128 0x1
	.4byte	.LASF76
	.byte	0x26
	.uleb128 0x1
	.4byte	.LASF77
	.byte	0x27
	.uleb128 0x1
	.4byte	.LASF78
	.byte	0x28
	.uleb128 0x1
	.4byte	.LASF79
	.byte	0x29
	.uleb128 0x1
	.4byte	.LASF80
	.byte	0x2a
	.uleb128 0x1
	.4byte	.LASF81
	.byte	0x2b
	.uleb128 0x1
	.4byte	.LASF82
	.byte	0x2c
	.uleb128 0x1
	.4byte	.LASF83
	.byte	0x2d
	.uleb128 0x1
	.4byte	.LASF84
	.byte	0x2e
	.uleb128 0x1
	.4byte	.LASF85
	.byte	0x2f
	.uleb128 0x1
	.4byte	.LASF86
	.byte	0x30
	.uleb128 0x1
	.4byte	.LASF87
	.byte	0x31
	.uleb128 0x1
	.4byte	.LASF88
	.byte	0x32
	.uleb128 0x1
	.4byte	.LASF89
	.byte	0x33
	.uleb128 0x1
	.4byte	.LASF90
	.byte	0x34
	.uleb128 0x1
	.4byte	.LASF91
	.byte	0x35
	.uleb128 0x1
	.4byte	.LASF92
	.byte	0x36
	.uleb128 0x1
	.4byte	.LASF93
	.byte	0x37
	.uleb128 0x1
	.4byte	.LASF94
	.byte	0x38
	.byte	0
	.uleb128 0x16
	.4byte	0x34
	.byte	0x5
	.byte	0x50
	.byte	0xe
	.4byte	0x30f
	.uleb128 0x1
	.4byte	.LASF95
	.byte	0
	.uleb128 0x1
	.4byte	.LASF96
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF97
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF99
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF100
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF101
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF102
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF103
	.byte	0x8
	.byte	0
	.uleb128 0x7
	.byte	0xa
	.byte	0x5
	.byte	0x5e
	.4byte	0x332
	.uleb128 0x2
	.4byte	.LASF104
	.byte	0x5
	.byte	0x60
	.byte	0xe
	.4byte	0xb6
	.byte	0
	.uleb128 0x4
	.string	"pin"
	.byte	0x5
	.byte	0x61
	.byte	0xd
	.4byte	0x332
	.byte	0x2
	.byte	0
	.uleb128 0xb
	.4byte	0xa5
	.4byte	0x342
	.uleb128 0xd
	.4byte	0x34
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.4byte	.LASF105
	.byte	0x5
	.byte	0x62
	.byte	0x2
	.4byte	0x30f
	.uleb128 0x8
	.byte	0x1
	.byte	0x2
	.4byte	.LASF106
	.uleb128 0x16
	.4byte	0x34
	.byte	0x6
	.byte	0x31
	.byte	0x1
	.4byte	0x392
	.uleb128 0x1
	.4byte	.LASF107
	.byte	0
	.uleb128 0x1
	.4byte	.LASF108
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF109
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF110
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF111
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF112
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF113
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF114
	.byte	0x7
	.byte	0
	.uleb128 0x7
	.byte	0x2
	.byte	0x6
	.byte	0x3f
	.4byte	0x3b5
	.uleb128 0x2
	.4byte	.LASF115
	.byte	0x6
	.byte	0x41
	.byte	0xd
	.4byte	0xa5
	.byte	0
	.uleb128 0x2
	.4byte	.LASF116
	.byte	0x6
	.byte	0x42
	.byte	0xd
	.4byte	0xa5
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF117
	.byte	0x6
	.byte	0x44
	.byte	0x2
	.4byte	0x392
	.uleb128 0x1b
	.2byte	0x11c
	.2byte	0x109
	.byte	0xd
	.4byte	0x3e3
	.uleb128 0x11
	.4byte	.LASF118
	.2byte	0x10a
	.byte	0x1a
	.4byte	0x3e3
	.uleb128 0x1c
	.string	"x_y"
	.2byte	0x10c
	.4byte	0x3e3
	.byte	0
	.uleb128 0xb
	.4byte	0xc2
	.4byte	0x3f3
	.uleb128 0xd
	.4byte	0x34
	.byte	0x46
	.byte	0
	.uleb128 0x1d
	.2byte	0x23c
	.2byte	0x105
	.4byte	0x42b
	.uleb128 0xc
	.4byte	.LASF119
	.2byte	0x106
	.byte	0x16
	.4byte	0xb6
	.byte	0
	.uleb128 0xc
	.4byte	.LASF120
	.2byte	0x107
	.byte	0x16
	.4byte	0xb6
	.byte	0x2
	.uleb128 0xc
	.4byte	.LASF121
	.2byte	0x108
	.byte	0x16
	.4byte	0x3e3
	.byte	0x4
	.uleb128 0x27
	.4byte	0x3c1
	.2byte	0x120
	.byte	0
	.uleb128 0x1b
	.2byte	0x23c
	.2byte	0x103
	.byte	0x5
	.4byte	0x447
	.uleb128 0x11
	.4byte	.LASF122
	.2byte	0x104
	.byte	0x12
	.4byte	0xc2
	.uleb128 0x1e
	.4byte	0x3f3
	.byte	0
	.uleb128 0x1d
	.2byte	0x240
	.2byte	0x101
	.4byte	0x464
	.uleb128 0xc
	.4byte	.LASF123
	.2byte	0x102
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x12
	.4byte	0x42b
	.byte	0x4
	.byte	0
	.uleb128 0x17
	.4byte	.LASF124
	.2byte	0x111
	.4byte	0x447
	.uleb128 0x1f
	.byte	0x4
	.2byte	0x11b
	.byte	0xd
	.4byte	0x490
	.uleb128 0x11
	.4byte	.LASF118
	.2byte	0x11c
	.byte	0x1a
	.4byte	0xc2
	.uleb128 0x1c
	.string	"x_y"
	.2byte	0x11e
	.4byte	0xc2
	.byte	0
	.uleb128 0x18
	.byte	0xc
	.2byte	0x117
	.4byte	0x4c6
	.uleb128 0xc
	.4byte	.LASF119
	.2byte	0x118
	.byte	0x16
	.4byte	0xb6
	.byte	0
	.uleb128 0xc
	.4byte	.LASF120
	.2byte	0x119
	.byte	0x16
	.4byte	0xb6
	.byte	0x2
	.uleb128 0xc
	.4byte	.LASF121
	.2byte	0x11a
	.byte	0x16
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x12
	.4byte	0x46f
	.byte	0x8
	.byte	0
	.uleb128 0x1f
	.byte	0xc
	.2byte	0x115
	.byte	0x5
	.4byte	0x4e1
	.uleb128 0x11
	.4byte	.LASF122
	.2byte	0x116
	.byte	0x12
	.4byte	0xc2
	.uleb128 0x1e
	.4byte	0x490
	.byte	0
	.uleb128 0x18
	.byte	0x10
	.2byte	0x113
	.4byte	0x4fd
	.uleb128 0xc
	.4byte	.LASF123
	.2byte	0x114
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x12
	.4byte	0x4c6
	.byte	0x4
	.byte	0
	.uleb128 0x17
	.4byte	.LASF125
	.2byte	0x123
	.4byte	0x4e1
	.uleb128 0x18
	.byte	0x8
	.2byte	0x125
	.4byte	0x52b
	.uleb128 0xc
	.4byte	.LASF123
	.2byte	0x126
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0xc
	.4byte	.LASF122
	.2byte	0x127
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.byte	0
	.uleb128 0x17
	.4byte	.LASF126
	.2byte	0x128
	.4byte	0x508
	.uleb128 0x7
	.byte	0x8
	.byte	0x8
	.byte	0x50
	.4byte	0x585
	.uleb128 0x2
	.4byte	.LASF127
	.byte	0x8
	.byte	0x51
	.byte	0xd
	.4byte	0xa5
	.byte	0
	.uleb128 0x4
	.string	"k"
	.byte	0x8
	.byte	0x52
	.byte	0xd
	.4byte	0xa5
	.byte	0x1
	.uleb128 0x4
	.string	"x"
	.byte	0x8
	.byte	0x53
	.byte	0xd
	.4byte	0x99
	.byte	0x2
	.uleb128 0x4
	.string	"y"
	.byte	0x8
	.byte	0x54
	.byte	0xd
	.4byte	0x99
	.byte	0x4
	.uleb128 0x4
	.string	"z1"
	.byte	0x8
	.byte	0x55
	.byte	0xc
	.4byte	0x8d
	.byte	0x6
	.uleb128 0x4
	.string	"z2"
	.byte	0x8
	.byte	0x56
	.byte	0xc
	.4byte	0x8d
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.4byte	.LASF128
	.byte	0x8
	.byte	0x57
	.byte	0x1f
	.4byte	0x536
	.uleb128 0x7
	.byte	0x8
	.byte	0x8
	.byte	0x88
	.4byte	0x5d7
	.uleb128 0x2
	.4byte	.LASF127
	.byte	0x8
	.byte	0x89
	.byte	0xd
	.4byte	0xa5
	.byte	0
	.uleb128 0x2
	.4byte	.LASF129
	.byte	0x8
	.byte	0x8a
	.byte	0xd
	.4byte	0xa5
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF118
	.byte	0x8
	.byte	0x8b
	.byte	0xd
	.4byte	0x159
	.byte	0x2
	.uleb128 0x4
	.string	"x"
	.byte	0x8
	.byte	0x8c
	.byte	0xd
	.4byte	0x99
	.byte	0x4
	.uleb128 0x4
	.string	"y"
	.byte	0x8
	.byte	0x8d
	.byte	0xd
	.4byte	0x99
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.4byte	.LASF130
	.byte	0x8
	.byte	0x8e
	.byte	0x1e
	.4byte	0x591
	.uleb128 0x7
	.byte	0x8
	.byte	0x8
	.byte	0x90
	.4byte	0x629
	.uleb128 0x2
	.4byte	.LASF127
	.byte	0x8
	.byte	0x91
	.byte	0xd
	.4byte	0xa5
	.byte	0
	.uleb128 0x2
	.4byte	.LASF131
	.byte	0x8
	.byte	0x92
	.byte	0xe
	.4byte	0xb6
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF132
	.byte	0x8
	.byte	0x93
	.byte	0xd
	.4byte	0xa5
	.byte	0x3
	.uleb128 0x4
	.string	"x"
	.byte	0x8
	.byte	0x94
	.byte	0xd
	.4byte	0x99
	.byte	0x4
	.uleb128 0x4
	.string	"y"
	.byte	0x8
	.byte	0x95
	.byte	0xd
	.4byte	0x99
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.4byte	.LASF133
	.byte	0x8
	.byte	0x96
	.byte	0x1f
	.4byte	0x5e3
	.uleb128 0xb
	.4byte	0xa5
	.4byte	0x645
	.uleb128 0xd
	.4byte	0x34
	.byte	0x4
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.byte	0x8
	.byte	0xa2
	.4byte	0x682
	.uleb128 0x2
	.4byte	.LASF127
	.byte	0x8
	.byte	0xa3
	.byte	0xd
	.4byte	0xa5
	.byte	0
	.uleb128 0x2
	.4byte	.LASF129
	.byte	0x8
	.byte	0xa4
	.byte	0xd
	.4byte	0xa5
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF118
	.byte	0x8
	.byte	0xa5
	.byte	0xd
	.4byte	0x635
	.byte	0x2
	.uleb128 0x2
	.4byte	.LASF134
	.byte	0x8
	.byte	0xa6
	.byte	0xd
	.4byte	0xa5
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.4byte	.LASF135
	.byte	0x8
	.byte	0xa7
	.byte	0x1e
	.4byte	0x645
	.uleb128 0x7
	.byte	0x8
	.byte	0x8
	.byte	0xa9
	.4byte	0x6cb
	.uleb128 0x2
	.4byte	.LASF127
	.byte	0x8
	.byte	0xaa
	.byte	0xd
	.4byte	0xa5
	.byte	0
	.uleb128 0x2
	.4byte	.LASF131
	.byte	0x8
	.byte	0xab
	.byte	0xd
	.4byte	0x6cb
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF132
	.byte	0x8
	.byte	0xac
	.byte	0xd
	.4byte	0xa5
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF134
	.byte	0x8
	.byte	0xad
	.byte	0xd
	.4byte	0x159
	.byte	0x6
	.byte	0
	.uleb128 0xb
	.4byte	0xa5
	.4byte	0x6db
	.uleb128 0xd
	.4byte	0x34
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF136
	.byte	0x8
	.byte	0xae
	.byte	0x1f
	.4byte	0x68e
	.uleb128 0xb
	.4byte	0xa5
	.4byte	0x6f7
	.uleb128 0xd
	.4byte	0x34
	.byte	0x9
	.byte	0
	.uleb128 0x7
	.byte	0x2
	.byte	0x9
	.byte	0x49
	.4byte	0x719
	.uleb128 0x4
	.string	"id"
	.byte	0x9
	.byte	0x4b
	.byte	0xd
	.4byte	0xa5
	.byte	0
	.uleb128 0x2
	.4byte	.LASF137
	.byte	0x9
	.byte	0x4c
	.byte	0xd
	.4byte	0xa5
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF138
	.byte	0x9
	.byte	0x4d
	.byte	0x2
	.4byte	0x6f7
	.uleb128 0x28
	.byte	0x8
	.byte	0x9
	.byte	0x53
	.byte	0x5
	.4byte	0x766
	.uleb128 0x10
	.4byte	.LASF139
	.byte	0x54
	.byte	0x25
	.4byte	0x585
	.uleb128 0x10
	.4byte	.LASF140
	.byte	0x56
	.byte	0x23
	.4byte	0x5d7
	.uleb128 0x10
	.4byte	.LASF141
	.byte	0x57
	.byte	0x28
	.4byte	0x629
	.uleb128 0x10
	.4byte	.LASF142
	.byte	0x59
	.byte	0x20
	.4byte	0x682
	.uleb128 0x10
	.4byte	.LASF143
	.byte	0x5a
	.byte	0x25
	.4byte	0x6db
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.byte	0x9
	.byte	0x4f
	.4byte	0x775
	.uleb128 0x12
	.4byte	0x725
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF144
	.byte	0x9
	.byte	0x5f
	.byte	0xa
	.4byte	0x766
	.uleb128 0x7
	.byte	0x8
	.byte	0x9
	.byte	0x61
	.4byte	0x7a4
	.uleb128 0x2
	.4byte	.LASF145
	.byte	0x9
	.byte	0x62
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF146
	.byte	0x9
	.byte	0x63
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF147
	.byte	0x9
	.byte	0x67
	.byte	0x2
	.4byte	0x781
	.uleb128 0x29
	.4byte	0x7a4
	.uleb128 0x7
	.byte	0x3
	.byte	0x9
	.byte	0x69
	.4byte	0x7e5
	.uleb128 0x2
	.4byte	.LASF148
	.byte	0x9
	.byte	0x6a
	.byte	0xd
	.4byte	0xa5
	.byte	0
	.uleb128 0x2
	.4byte	.LASF149
	.byte	0x9
	.byte	0x6b
	.byte	0xd
	.4byte	0xa5
	.byte	0x1
	.uleb128 0x2
	.4byte	.LASF150
	.byte	0x9
	.byte	0x6c
	.byte	0xd
	.4byte	0xa5
	.byte	0x2
	.byte	0
	.uleb128 0x3
	.4byte	.LASF151
	.byte	0x9
	.byte	0x6d
	.byte	0x3
	.4byte	0x7b5
	.uleb128 0x7
	.byte	0x18
	.byte	0x9
	.byte	0x7e
	.4byte	0x848
	.uleb128 0x2
	.4byte	.LASF152
	.byte	0x9
	.byte	0x7f
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF153
	.byte	0x9
	.byte	0x80
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF154
	.byte	0x9
	.byte	0x81
	.byte	0xe
	.4byte	0xc2
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF155
	.byte	0x9
	.byte	0x82
	.byte	0xe
	.4byte	0xc2
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF156
	.byte	0x9
	.byte	0x83
	.byte	0x17
	.4byte	0xce
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF157
	.byte	0x9
	.byte	0x84
	.byte	0xd
	.4byte	0xa5
	.byte	0x14
	.byte	0
	.uleb128 0x3
	.4byte	.LASF158
	.byte	0x9
	.byte	0x94
	.byte	0x3
	.4byte	0x7f1
	.uleb128 0x7
	.byte	0x40
	.byte	0x9
	.byte	0x96
	.4byte	0x912
	.uleb128 0x2
	.4byte	.LASF155
	.byte	0x9
	.byte	0x97
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF159
	.byte	0x9
	.byte	0x98
	.byte	0xe
	.4byte	0xc2
	.byte	0x4
	.uleb128 0x2
	.4byte	.LASF160
	.byte	0x9
	.byte	0x9b
	.byte	0x1e
	.4byte	0x912
	.byte	0x8
	.uleb128 0x2
	.4byte	.LASF161
	.byte	0x9
	.byte	0x9c
	.byte	0xe
	.4byte	0xc2
	.byte	0xc
	.uleb128 0x2
	.4byte	.LASF162
	.byte	0x9
	.byte	0x9d
	.byte	0xe
	.4byte	0xc2
	.byte	0x10
	.uleb128 0x2
	.4byte	.LASF163
	.byte	0x9
	.byte	0x9f
	.byte	0x1e
	.4byte	0x719
	.byte	0x14
	.uleb128 0x2
	.4byte	.LASF164
	.byte	0x9
	.byte	0xa0
	.byte	0x1e
	.4byte	0x719
	.byte	0x16
	.uleb128 0x2
	.4byte	.LASF165
	.byte	0x9
	.byte	0xa5
	.byte	0xe
	.4byte	0xc2
	.byte	0x18
	.uleb128 0x2
	.4byte	.LASF166
	.byte	0x9
	.byte	0xa6
	.byte	0xe
	.4byte	0xc2
	.byte	0x1c
	.uleb128 0x2
	.4byte	.LASF167
	.byte	0x9
	.byte	0xae
	.byte	0xe
	.4byte	0x917
	.byte	0x20
	.uleb128 0x2
	.4byte	.LASF168
	.byte	0x9
	.byte	0xb1
	.byte	0xd
	.4byte	0x6e7
	.byte	0x2e
	.uleb128 0x2
	.4byte	.LASF169
	.byte	0x9
	.byte	0xb2
	.byte	0xd
	.4byte	0xa5
	.byte	0x38
	.uleb128 0x4
	.string	"rr"
	.byte	0x9
	.byte	0xbb
	.byte	0x1d
	.4byte	0x3b5
	.byte	0x39
	.uleb128 0x4
	.string	"deb"
	.byte	0x9
	.byte	0xbd
	.byte	0x17
	.4byte	0x7e5
	.byte	0x3b
	.byte	0
	.uleb128 0xa
	.4byte	0x7b0
	.uleb128 0xb
	.4byte	0xb6
	.4byte	0x927
	.uleb128 0xd
	.4byte	0x34
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.4byte	.LASF170
	.byte	0x9
	.byte	0xbf
	.byte	0x3
	.4byte	0x854
	.uleb128 0x2a
	.2byte	0x16ec
	.byte	0x9
	.byte	0xc1
	.byte	0x9
	.4byte	0x980
	.uleb128 0x4
	.string	"app"
	.byte	0x9
	.byte	0xc3
	.byte	0x1b
	.4byte	0x927
	.byte	0
	.uleb128 0x4
	.string	"hid"
	.byte	0x9
	.byte	0xc4
	.byte	0x1b
	.4byte	0x848
	.byte	0x40
	.uleb128 0x4
	.string	"dbg"
	.byte	0x9
	.byte	0xc5
	.byte	0x17
	.4byte	0x342
	.byte	0x58
	.uleb128 0x2
	.4byte	.LASF171
	.byte	0x9
	.byte	0xc7
	.byte	0x17
	.4byte	0x980
	.byte	0x62
	.uleb128 0x2b
	.4byte	.LASF172
	.byte	0x9
	.byte	0xca
	.byte	0x1d
	.4byte	0x990
	.2byte	0x16e2
	.byte	0
	.uleb128 0xb
	.4byte	0x464
	.4byte	0x990
	.uleb128 0xd
	.4byte	0x34
	.byte	0x9
	.byte	0
	.uleb128 0xb
	.4byte	0x775
	.4byte	0x9a0
	.uleb128 0xd
	.4byte	0x34
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF173
	.byte	0x9
	.byte	0xcc
	.byte	0x3
	.4byte	0x933
	.uleb128 0x20
	.4byte	.LASF195
	.byte	0x9
	.byte	0xd2
	.4byte	0x9b7
	.uleb128 0xa
	.4byte	0x9a0
	.uleb128 0x15
	.4byte	0x34
	.byte	0x9
	.2byte	0x131
	.4byte	0x9ff
	.uleb128 0x1
	.4byte	.LASF174
	.byte	0
	.uleb128 0x1
	.4byte	.LASF175
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF176
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF177
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF178
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF179
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF180
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF181
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF182
	.byte	0x8
	.byte	0
	.uleb128 0x15
	.4byte	0x34
	.byte	0x9
	.2byte	0x13f
	.4byte	0xa12
	.uleb128 0x1
	.4byte	.LASF183
	.byte	0
	.byte	0
	.uleb128 0xa
	.4byte	0xa1c
	.uleb128 0x1a
	.4byte	0xa12
	.uleb128 0x2c
	.uleb128 0xa
	.4byte	0xc2
	.uleb128 0x16
	.4byte	0x34
	.byte	0xa
	.byte	0x4b
	.byte	0xe
	.4byte	0xa71
	.uleb128 0x1
	.4byte	.LASF184
	.byte	0
	.uleb128 0x1
	.4byte	.LASF185
	.byte	0x1
	.uleb128 0x1
	.4byte	.LASF186
	.byte	0x2
	.uleb128 0x1
	.4byte	.LASF187
	.byte	0x3
	.uleb128 0x1
	.4byte	.LASF188
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF189
	.byte	0x5
	.uleb128 0x1
	.4byte	.LASF190
	.byte	0x6
	.uleb128 0x1
	.4byte	.LASF191
	.byte	0x7
	.uleb128 0x1
	.4byte	.LASF192
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF193
	.byte	0x9
	.uleb128 0x1
	.4byte	.LASF194
	.byte	0xa
	.byte	0
	.uleb128 0xa
	.4byte	0xa5
	.uleb128 0xb
	.4byte	0xb1
	.4byte	0xa87
	.uleb128 0x2d
	.4byte	0x34
	.2byte	0x16eb
	.byte	0
	.uleb128 0x14
	.4byte	0xa76
	.uleb128 0x20
	.4byte	.LASF196
	.byte	0xb
	.byte	0x9c
	.4byte	0xa87
	.uleb128 0x2e
	.4byte	0x9ac
	.byte	0x1
	.byte	0x35
	.byte	0x12
	.uleb128 0x5
	.byte	0x3
	.4byte	hid_common
	.uleb128 0x21
	.4byte	.LASF197
	.byte	0x21
	.4byte	0x7f
	.4byte	0xac3
	.uleb128 0xf
	.4byte	0x7f
	.uleb128 0xf
	.4byte	0x65
	.uleb128 0xf
	.4byte	0x6c
	.byte	0
	.uleb128 0x21
	.4byte	.LASF198
	.byte	0x1f
	.4byte	0x7f
	.4byte	0xae1
	.uleb128 0xf
	.4byte	0x81
	.uleb128 0xf
	.4byte	0xa17
	.uleb128 0xf
	.4byte	0x6c
	.byte	0
	.uleb128 0x2f
	.4byte	.LASF222
	.byte	0x1
	.byte	0xf7
	.byte	0x6
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb0e
	.uleb128 0x13
	.4byte	.LVL38
	.4byte	0xaa5
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0xb40
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	.LASF199
	.byte	0xf2
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb48
	.uleb128 0x9
	.4byte	.LASF201
	.byte	0xf2
	.byte	0x2e
	.4byte	0xa5
	.4byte	.LLST15
	.uleb128 0x13
	.4byte	.LVL37
	.4byte	0xaa5
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x1
	.byte	0x30
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x240
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	.LASF200
	.byte	0xec
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb79
	.uleb128 0x5
	.4byte	.LASF171
	.byte	0xec
	.byte	0x49
	.4byte	0xb79
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.4byte	.LASF201
	.byte	0xec
	.byte	0x5e
	.4byte	0xa5
	.4byte	.LLST14
	.byte	0
	.uleb128 0xa
	.4byte	0x52b
	.uleb128 0x6
	.4byte	.LASF202
	.byte	0xe3
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbaf
	.uleb128 0x5
	.4byte	.LASF171
	.byte	0xe3
	.byte	0x47
	.4byte	0xbaf
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.4byte	.LASF201
	.byte	0xe3
	.byte	0x5c
	.4byte	0xa5
	.4byte	.LLST13
	.byte	0
	.uleb128 0xa
	.4byte	0x4fd
	.uleb128 0x6
	.4byte	.LASF203
	.byte	0xde
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc05
	.uleb128 0x9
	.4byte	.LASF171
	.byte	0xde
	.byte	0x37
	.4byte	0xc05
	.4byte	.LLST11
	.uleb128 0x9
	.4byte	.LASF201
	.byte	0xde
	.byte	0x4c
	.4byte	0xa5
	.4byte	.LLST12
	.uleb128 0x13
	.4byte	.LVL30
	.4byte	0xac3
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x3
	.byte	0xa
	.2byte	0x240
	.byte	0
	.byte	0
	.uleb128 0xa
	.4byte	0x464
	.uleb128 0x6
	.4byte	.LASF204
	.byte	0xd5
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc46
	.uleb128 0x5
	.4byte	.LASF160
	.byte	0xd5
	.byte	0x38
	.4byte	0xc46
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.4byte	.LASF161
	.byte	0xd5
	.byte	0x52
	.4byte	0xa1d
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.4byte	.LASF162
	.byte	0xd5
	.byte	0x71
	.4byte	0xa1d
	.uleb128 0x1
	.byte	0x5c
	.byte	0
	.uleb128 0xa
	.4byte	0xc4b
	.uleb128 0xa
	.4byte	0x7a4
	.uleb128 0x6
	.4byte	.LASF205
	.byte	0xce
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc8c
	.uleb128 0x5
	.4byte	.LASF160
	.byte	0xce
	.byte	0x38
	.4byte	0x912
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x5
	.4byte	.LASF161
	.byte	0xce
	.byte	0x51
	.4byte	0xc2
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.4byte	.LASF162
	.byte	0xce
	.byte	0x6f
	.4byte	0xc2
	.uleb128 0x1
	.byte	0x5c
	.byte	0
	.uleb128 0x6
	.4byte	.LASF206
	.byte	0xc8
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xccc
	.uleb128 0x9
	.4byte	.LASF207
	.byte	0xc8
	.byte	0x2f
	.4byte	0xccc
	.4byte	.LLST10
	.uleb128 0x13
	.4byte	.LVL24
	.4byte	0xac3
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5a
	.uleb128 0x9
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xa
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.uleb128 0xe
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.byte	0
	.uleb128 0xa
	.4byte	0x342
	.uleb128 0x30
	.4byte	.LASF226
	.byte	0x1
	.byte	0xc3
	.byte	0xa
	.4byte	0xc2
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x6
	.4byte	.LASF208
	.byte	0xbb
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd09
	.uleb128 0x5
	.4byte	.LASF209
	.byte	0xbb
	.byte	0x30
	.4byte	0xa1d
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x6
	.4byte	.LASF210
	.byte	0xb6
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd2b
	.uleb128 0x5
	.4byte	.LASF209
	.byte	0xb6
	.byte	0x2f
	.4byte	0xc2
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x6
	.4byte	.LASF211
	.byte	0xb1
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd4d
	.uleb128 0x5
	.4byte	.LASF153
	.byte	0xb1
	.byte	0x2e
	.4byte	0xc2
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x6
	.4byte	.LASF212
	.byte	0xac
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd6f
	.uleb128 0x5
	.4byte	.LASF213
	.byte	0xac
	.byte	0x2c
	.4byte	0xa5
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x6
	.4byte	.LASF214
	.byte	0xa7
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd93
	.uleb128 0x9
	.4byte	.LASF213
	.byte	0xa7
	.byte	0x2a
	.4byte	0xa5
	.4byte	.LLST9
	.byte	0
	.uleb128 0x31
	.4byte	.LASF227
	.byte	0x1
	.byte	0x91
	.byte	0xa
	.4byte	0xc2
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xde4
	.uleb128 0x9
	.4byte	.LASF215
	.byte	0x91
	.byte	0x2a
	.4byte	0xa5
	.4byte	.LLST8
	.uleb128 0x5
	.4byte	.LASF216
	.byte	0x91
	.byte	0x3e
	.4byte	0xa71
	.uleb128 0x1
	.byte	0x5b
	.uleb128 0x5
	.4byte	.LASF217
	.byte	0x91
	.byte	0x4c
	.4byte	0xa5
	.uleb128 0x1
	.byte	0x5c
	.uleb128 0x32
	.string	"ret"
	.byte	0x1
	.byte	0x93
	.byte	0xe
	.4byte	0xc2
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	.LASF218
	.byte	0x44
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe7b
	.uleb128 0x9
	.4byte	.LASF215
	.byte	0x44
	.byte	0x26
	.4byte	0xa5
	.4byte	.LLST1
	.uleb128 0x9
	.4byte	.LASF216
	.byte	0x44
	.byte	0x3a
	.4byte	0xa71
	.4byte	.LLST2
	.uleb128 0x9
	.4byte	.LASF217
	.byte	0x44
	.byte	0x48
	.4byte	0xa5
	.4byte	.LLST3
	.uleb128 0x22
	.4byte	.LBB3
	.4byte	.LBE3-.LBB3
	.4byte	0xe41
	.uleb128 0x19
	.4byte	.LASF219
	.byte	0x52
	.4byte	0x6c
	.4byte	.LLST6
	.byte	0
	.uleb128 0x22
	.4byte	.LBB4
	.4byte	.LBE4-.LBB4
	.4byte	0xe5d
	.uleb128 0x19
	.4byte	.LASF219
	.byte	0x5b
	.4byte	0x6c
	.4byte	.LLST7
	.byte	0
	.uleb128 0x33
	.4byte	.LLRL4
	.uleb128 0x19
	.4byte	.LASF219
	.byte	0x75
	.4byte	0x6c
	.4byte	.LLST5
	.uleb128 0x34
	.4byte	.LVL7
	.4byte	0xac3
	.byte	0
	.byte	0
	.uleb128 0x6
	.4byte	.LASF220
	.byte	0x3e
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe9d
	.uleb128 0x5
	.4byte	.LASF221
	.byte	0x3e
	.byte	0x2b
	.4byte	0xa5
	.uleb128 0x1
	.byte	0x5a
	.byte	0
	.uleb128 0x35
	.4byte	.LASF223
	.byte	0x1
	.byte	0x39
	.byte	0x6
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x9
	.4byte	.LASF221
	.byte	0x39
	.byte	0x29
	.4byte	0xa5
	.4byte	.LLST0
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
	.uleb128 0x5
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
	.uleb128 0x7
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
	.uleb128 0xa
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
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
	.uleb128 0x49
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x7e
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
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
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 14
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x17
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 30
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x21
	.sleb128 20
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x37
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 26
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 9
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 7
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 25
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
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
	.uleb128 0x21
	.sleb128 12
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 8
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
	.uleb128 0x22
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
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.uleb128 0x27
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0x29
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
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
	.uleb128 0x2b
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
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x2e
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
	.uleb128 0x30
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
	.uleb128 0x32
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
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x34
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
	.4byte	.LVL35
	.byte	0x4
	.uleb128 .LVL35-.LVL35
	.uleb128 .LVL36-.LVL35
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL36-.LVL35
	.uleb128 .LFE31-.LVL35
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
	.4byte	.LVL33
	.byte	0x4
	.uleb128 .LVL33-.LVL33
	.uleb128 .LVL34-.LVL33
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL34-.LVL33
	.uleb128 .LFE30-.LVL33
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
.LLST13:
	.byte	0x6
	.4byte	.LVL31
	.byte	0x4
	.uleb128 .LVL31-.LVL31
	.uleb128 .LVL32-.LVL31
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL32-.LVL31
	.uleb128 .LFE29-.LVL31
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
.LLST11:
	.byte	0x6
	.4byte	.LVL27
	.byte	0x4
	.uleb128 .LVL27-.LVL27
	.uleb128 .LVL29-.LVL27
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL29-.LVL27
	.uleb128 .LVL30-1-.LVL27
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL30-1-.LVL27
	.uleb128 .LFE28-.LVL27
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
.LLST12:
	.byte	0x6
	.4byte	.LVL27
	.byte	0x4
	.uleb128 .LVL27-.LVL27
	.uleb128 .LVL28-.LVL27
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL28-.LVL27
	.uleb128 .LFE28-.LVL27
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
.LLST10:
	.byte	0x6
	.4byte	.LVL23
	.byte	0x4
	.uleb128 .LVL23-.LVL23
	.uleb128 .LVL24-1-.LVL23
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL24-1-.LVL23
	.uleb128 .LFE25-.LVL23
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
.LLST9:
	.byte	0x6
	.4byte	.LVL17
	.byte	0x4
	.uleb128 .LVL17-.LVL17
	.uleb128 .LVL18-.LVL17
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL18-.LVL17
	.uleb128 .LFE19-.LVL17
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
	.4byte	.LVL15
	.byte	0x4
	.uleb128 .LVL15-.LVL15
	.uleb128 .LVL16-.LVL15
	.uleb128 0x1
	.byte	0x5a
	.byte	0x4
	.uleb128 .LVL16-.LVL15
	.uleb128 .LFE18-.LVL15
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
	.uleb128 .LFE17-.LVL3
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
.LLST2:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL7-1-.LVL3
	.uleb128 0x1
	.byte	0x5b
	.byte	0x4
	.uleb128 .LVL7-1-.LVL3
	.uleb128 .LVL7-.LVL3
	.uleb128 0xa
	.byte	0xa3
	.uleb128 0x3
	.byte	0xa5
	.uleb128 0xb
	.uleb128 0x26
	.byte	0xa8
	.uleb128 0x34
	.byte	0xa8
	.uleb128 0
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL7-.LVL3
	.uleb128 .LFE17-.LVL3
	.uleb128 0x1
	.byte	0x5b
	.byte	0
.LLST3:
	.byte	0x6
	.4byte	.LVL3
	.byte	0x4
	.uleb128 .LVL3-.LVL3
	.uleb128 .LVL5-.LVL3
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL5-.LVL3
	.uleb128 .LVL6-.LVL3
	.uleb128 0x1
	.byte	0x5f
	.byte	0x4
	.uleb128 .LVL7-.LVL3
	.uleb128 .LVL8-.LVL3
	.uleb128 0x13
	.byte	0x7c
	.sleb128 0
	.byte	0x12
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x3e
	.byte	0x16
	.byte	0x14
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x2d
	.byte	0x28
	.2byte	0x1
	.byte	0x16
	.byte	0x13
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL8-.LVL3
	.uleb128 .LVL9-.LVL3
	.uleb128 0x13
	.byte	0x7f
	.sleb128 0
	.byte	0x12
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x3e
	.byte	0x16
	.byte	0x14
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x2d
	.byte	0x28
	.2byte	0x1
	.byte	0x16
	.byte	0x13
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL9-.LVL3
	.uleb128 .LVL10-.LVL3
	.uleb128 0x13
	.byte	0x7c
	.sleb128 0
	.byte	0x12
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x34
	.byte	0x16
	.byte	0x14
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x2d
	.byte	0x28
	.2byte	0x1
	.byte	0x16
	.byte	0x13
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL10-.LVL3
	.uleb128 .LVL11-.LVL3
	.uleb128 0x13
	.byte	0x7f
	.sleb128 0
	.byte	0x12
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x34
	.byte	0x16
	.byte	0x14
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x2d
	.byte	0x28
	.2byte	0x1
	.byte	0x16
	.byte	0x13
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL11-.LVL3
	.uleb128 .LVL12-.LVL3
	.uleb128 0x1
	.byte	0x5c
	.byte	0x4
	.uleb128 .LVL12-.LVL3
	.uleb128 .LVL13-.LVL3
	.uleb128 0x13
	.byte	0x7c
	.sleb128 0
	.byte	0x12
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x33
	.byte	0x16
	.byte	0x14
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x2d
	.byte	0x28
	.2byte	0x1
	.byte	0x16
	.byte	0x13
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL13-.LVL3
	.uleb128 .LVL14-.LVL3
	.uleb128 0x13
	.byte	0x7f
	.sleb128 0
	.byte	0x12
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x33
	.byte	0x16
	.byte	0x14
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x2d
	.byte	0x28
	.2byte	0x1
	.byte	0x16
	.byte	0x13
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL14-.LVL3
	.uleb128 .LFE17-.LVL3
	.uleb128 0x1
	.byte	0x5c
	.byte	0
.LLST6:
	.byte	0x8
	.4byte	.LVL7
	.uleb128 .LVL9-.LVL7
	.uleb128 0x2
	.byte	0x3e
	.byte	0x9f
	.byte	0
.LLST7:
	.byte	0x8
	.4byte	.LVL9
	.uleb128 .LVL11-.LVL9
	.uleb128 0x2
	.byte	0x34
	.byte	0x9f
	.byte	0
.LLST5:
	.byte	0x8
	.4byte	.LVL12
	.uleb128 .LVL14-.LVL12
	.uleb128 0x2
	.byte	0x33
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
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.4byte	0xa4
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
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.4byte	.LFB22
	.4byte	.LFE22-.LFB22
	.4byte	.LFB23
	.4byte	.LFE23-.LFB23
	.4byte	.LFB24
	.4byte	.LFE24-.LFB24
	.4byte	.LFB25
	.4byte	.LFE25-.LFB25
	.4byte	.LFB26
	.4byte	.LFE26-.LFB26
	.4byte	.LFB27
	.4byte	.LFE27-.LFB27
	.4byte	.LFB28
	.4byte	.LFE28-.LFB28
	.4byte	.LFB29
	.4byte	.LFE29-.LFB29
	.4byte	.LFB30
	.4byte	.LFE30-.LFB30
	.4byte	.LFB31
	.4byte	.LFE31-.LFB31
	.4byte	.LFB32
	.4byte	.LFE32-.LFB32
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
	.uleb128 .LBB5-.LBB2
	.uleb128 .LBE5-.LBB2
	.byte	0
.LLRL16:
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
	.byte	0x7
	.4byte	.LFB19
	.uleb128 .LFE19-.LFB19
	.byte	0x7
	.4byte	.LFB20
	.uleb128 .LFE20-.LFB20
	.byte	0x7
	.4byte	.LFB21
	.uleb128 .LFE21-.LFB21
	.byte	0x7
	.4byte	.LFB22
	.uleb128 .LFE22-.LFB22
	.byte	0x7
	.4byte	.LFB23
	.uleb128 .LFE23-.LFB23
	.byte	0x7
	.4byte	.LFB24
	.uleb128 .LFE24-.LFB24
	.byte	0x7
	.4byte	.LFB25
	.uleb128 .LFE25-.LFB25
	.byte	0x7
	.4byte	.LFB26
	.uleb128 .LFE26-.LFB26
	.byte	0x7
	.4byte	.LFB27
	.uleb128 .LFE27-.LFB27
	.byte	0x7
	.4byte	.LFB28
	.uleb128 .LFE28-.LFB28
	.byte	0x7
	.4byte	.LFB29
	.uleb128 .LFE29-.LFB29
	.byte	0x7
	.4byte	.LFB30
	.uleb128 .LFE30-.LFB30
	.byte	0x7
	.4byte	.LFB31
	.uleb128 .LFE31-.LFB31
	.byte	0x7
	.4byte	.LFB32
	.uleb128 .LFE32-.LFB32
	.byte	0
.Ldebug_ranges3:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF180:
	.string	"RAPA_TYPE_KEY_REMAP_ENABLE"
.LASF165:
	.string	"key_remap_enable"
.LASF144:
	.string	"T_HID_CCNI_USB_REPORT_S"
.LASF13:
	.string	"size_t"
.LASF209:
	.string	"hid_exp_features"
.LASF160:
	.string	"combo_key_list"
.LASF95:
	.string	"DBG_PIN_SPI_CB"
.LASF213:
	.string	"flag_id"
.LASF211:
	.string	"hid_common_set_dongle_scenario"
.LASF204:
	.string	"hid_common_get_combo_key_list"
.LASF5:
	.string	"signed char"
.LASF139:
	.string	"ms_s16_z8"
.LASF207:
	.string	"debug"
.LASF196:
	.string	"ccm_hid_common_para"
.LASF183:
	.string	"RAPA_TYPE_ACL_RESPONSE_VIA_HID_REPORT"
.LASF71:
	.string	"HAL_EINT_NUMBER_33"
.LASF2:
	.string	"long long unsigned int"
.LASF114:
	.string	"HID_REPORT_RATE_TOTAL_NUM"
.LASF21:
	.string	"QDEC_IRQn"
.LASF146:
	.string	"combo_bit_32_63"
.LASF20:
	.string	"LED_IRQn"
.LASF153:
	.string	"dongle_scenario"
.LASF169:
	.string	"mouse_key_num"
.LASF15:
	.string	"int16_t"
.LASF178:
	.string	"PARA_TYPE_RISCV_TRIGGER_TIME"
.LASF10:
	.string	"long long int"
.LASF90:
	.string	"HAL_EINT_USB1"
.LASF91:
	.string	"HAL_EINT_USB2"
.LASF163:
	.string	"irpt_ctrl"
.LASF221:
	.string	"feature_id"
.LASF115:
	.string	"rr_idx_2_4g"
.LASF27:
	.string	"UART_DMA_IRQn"
.LASF86:
	.string	"HAL_EINT_UART_0_RX"
.LASF128:
	.string	"T_HID_REPORT_MS_K8_S16_Z8_S"
.LASF214:
	.string	"hid_common_set_hid_exp_flag"
.LASF23:
	.string	"UART_IRQn"
.LASF108:
	.string	"HID_REPORT_RATE_250_HZ"
.LASF25:
	.string	"RTC_IRQn"
.LASF22:
	.string	"KEYSCAN_IRQn"
.LASF8:
	.string	"long int"
.LASF127:
	.string	"report_id"
.LASF126:
	.string	"T_HID_KEY_REMAP_FRONTEND_S"
.LASF210:
	.string	"hid_common_set_hid_exp_features"
.LASF198:
	.string	"memcpy"
.LASF65:
	.string	"HAL_EINT_NUMBER_27"
.LASF17:
	.string	"uint16_t"
.LASF113:
	.string	"HID_REPORT_RATE_8K_HZ"
.LASF195:
	.string	"hid_common"
.LASF147:
	.string	"T_AIR_COMBO_KEY_S"
.LASF130:
	.string	"T_HID_REPORT_KB_STD2_XY_S"
.LASF31:
	.string	"I3C0_IRQn"
.LASF176:
	.string	"PARA_TYPE_DEBUG_PIN"
.LASF134:
	.string	"dummy"
.LASF30:
	.string	"EINT_IRQn"
.LASF117:
	.string	"T_HID_REPORT_RATE_VAL_S"
.LASF32:
	.string	"I3C0_DMA_IRQn"
.LASF200:
	.string	"hid_common_get_frontend_key_remap_data"
.LASF124:
	.string	"T_HID_KEY_REMAP_S"
.LASF107:
	.string	"HID_REPORT_RATE_125_HZ"
.LASF4:
	.string	"unsigned int"
.LASF120:
	.string	"repeat_times"
.LASF98:
	.string	"DBG_PIN_GENERAL_DBG_1"
.LASF99:
	.string	"DBG_PIN_GENERAL_DBG_2"
.LASF203:
	.string	"hid_common_set_key_remap_data"
.LASF9:
	.string	"long unsigned int"
.LASF87:
	.string	"HAL_EINT_UART_1_RX"
.LASF140:
	.string	"kb_std2"
.LASF118:
	.string	"keycode"
.LASF142:
	.string	"kb_std5"
.LASF161:
	.string	"combo_key_list_size"
.LASF167:
	.string	"riscv_trigger_time"
.LASF224:
	.string	"GNU C17 13.2.0 -mabi=ilp32e -mcmodel=medany -misa-spec=20191213 -march=rv32ec_zicsr_zifencei -g -Os -fvisibility=hidden -ffreestanding -ffunction-sections -fdata-sections"
.LASF133:
	.string	"T_HID_REPORT_KB_CONSUMER1_XY_S"
.LASF216:
	.string	"data"
.LASF202:
	.string	"hid_common_get_backend_key_remap_data"
.LASF7:
	.string	"short unsigned int"
.LASF94:
	.string	"HAL_EINT_NUMBER_MAX"
.LASF171:
	.string	"mapped_data"
.LASF38:
	.string	"HAL_EINT_NUMBER_0"
.LASF201:
	.string	"key_id"
.LASF40:
	.string	"HAL_EINT_NUMBER_2"
.LASF174:
	.string	"PARA_TYPE_IRPT_CTRL"
.LASF42:
	.string	"HAL_EINT_NUMBER_4"
.LASF43:
	.string	"HAL_EINT_NUMBER_5"
.LASF44:
	.string	"HAL_EINT_NUMBER_6"
.LASF45:
	.string	"HAL_EINT_NUMBER_7"
.LASF46:
	.string	"HAL_EINT_NUMBER_8"
.LASF47:
	.string	"HAL_EINT_NUMBER_9"
.LASF33:
	.string	"SPI_MST0_IRQn"
.LASF97:
	.string	"DBG_PIN_NACK"
.LASF68:
	.string	"HAL_EINT_NUMBER_30"
.LASF125:
	.string	"T_HID_KEY_REMAP_BACKEND_S"
.LASF156:
	.string	"outgoing_report_ready"
.LASF155:
	.string	"features"
.LASF72:
	.string	"HAL_EINT_NUMBER_34"
.LASF158:
	.string	"hid_shared_parameters"
.LASF111:
	.string	"HID_REPORT_RATE_2K_HZ"
.LASF41:
	.string	"HAL_EINT_NUMBER_3"
.LASF225:
	.string	"IRQn"
.LASF76:
	.string	"HAL_EINT_NUMBER_38"
.LASF184:
	.string	"EINT_COUNTER_NUMBER_0"
.LASF185:
	.string	"EINT_COUNTER_NUMBER_1"
.LASF186:
	.string	"EINT_COUNTER_NUMBER_2"
.LASF187:
	.string	"EINT_COUNTER_NUMBER_3"
.LASF188:
	.string	"EINT_COUNTER_NUMBER_4"
.LASF189:
	.string	"EINT_COUNTER_NUMBER_5"
.LASF190:
	.string	"EINT_COUNTER_NUMBER_6"
.LASF191:
	.string	"EINT_COUNTER_NUMBER_7"
.LASF192:
	.string	"EINT_COUNTER_NUMBER_8"
.LASF193:
	.string	"EINT_COUNTER_NUMBER_9"
.LASF26:
	.string	"GPT_IRQn"
.LASF102:
	.string	"DBG_PIN_USB_TX"
.LASF194:
	.string	"EINT_COUNTER_NUMBER_MUX"
.LASF19:
	.string	"SW_IRQn"
.LASF122:
	.string	"item"
.LASF151:
	.string	"T_DEBOUNCE_PARA_S"
.LASF35:
	.string	"USB_IRQn"
.LASF150:
	.string	"step_bt"
.LASF175:
	.string	"PARA_TYPE_SCROLL_CTRL"
.LASF24:
	.string	"SPI_MST1_IRQn"
.LASF199:
	.string	"hid_common_clear_key_remap_data"
.LASF218:
	.string	"hid_common_set_app_para"
.LASF168:
	.string	"mouse_key_list"
.LASF222:
	.string	"hid_common_clear_all_key_remap_data"
.LASF48:
	.string	"HAL_EINT_NUMBER_10"
.LASF49:
	.string	"HAL_EINT_NUMBER_11"
.LASF50:
	.string	"HAL_EINT_NUMBER_12"
.LASF205:
	.string	"hid_common_set_combo_key"
.LASF52:
	.string	"HAL_EINT_NUMBER_14"
.LASF53:
	.string	"HAL_EINT_NUMBER_15"
.LASF121:
	.string	"macro"
.LASF55:
	.string	"HAL_EINT_NUMBER_17"
.LASF56:
	.string	"HAL_EINT_NUMBER_18"
.LASF57:
	.string	"HAL_EINT_NUMBER_19"
.LASF149:
	.string	"step_2_4g"
.LASF182:
	.string	"RAPA_TYPE_KEY_NOT_REMAP_DISABLE"
.LASF208:
	.string	"hid_common_get_hid_exp_features"
.LASF106:
	.string	"_Bool"
.LASF3:
	.string	"unsigned char"
.LASF166:
	.string	"key_remap_fn_key"
.LASF93:
	.string	"HAL_EINT_RESERVED"
.LASF162:
	.string	"hold_timeout"
.LASF6:
	.string	"short int"
.LASF145:
	.string	"combo_bit_00_31"
.LASF28:
	.string	"PMU_IRQn"
.LASF29:
	.string	"MCU_DMA_IRQn"
.LASF132:
	.string	"numeric_key_pad"
.LASF119:
	.string	"play_mode"
.LASF109:
	.string	"HID_REPORT_RATE_500_HZ"
.LASF220:
	.string	"hid_common_clear_app_feature"
.LASF105:
	.string	"T_COMMON_LA_DBG_S"
.LASF179:
	.string	"PARA_TYPE_DEBOUNCE_CONFIG"
.LASF58:
	.string	"HAL_EINT_NUMBER_20"
.LASF59:
	.string	"HAL_EINT_NUMBER_21"
.LASF60:
	.string	"HAL_EINT_NUMBER_22"
.LASF61:
	.string	"HAL_EINT_NUMBER_23"
.LASF62:
	.string	"HAL_EINT_NUMBER_24"
.LASF63:
	.string	"HAL_EINT_NUMBER_25"
.LASF64:
	.string	"HAL_EINT_NUMBER_26"
.LASF18:
	.string	"uint32_t"
.LASF66:
	.string	"HAL_EINT_NUMBER_28"
.LASF67:
	.string	"HAL_EINT_NUMBER_29"
.LASF96:
	.string	"DBG_PIN_LATCH_REPORT"
.LASF85:
	.string	"HAL_EINT_NUMBER_47"
.LASF172:
	.string	"outgoing_report"
.LASF11:
	.string	"long double"
.LASF141:
	.string	"kb_consumer1"
.LASF143:
	.string	"kb_consumer2"
.LASF12:
	.string	"char"
.LASF226:
	.string	"hid_common_get_dongle_scenario"
.LASF34:
	.string	"IRQ_GEN_IRQn"
.LASF159:
	.string	"inActivity_timeout"
.LASF137:
	.string	"para"
.LASF206:
	.string	"hid_common_sync_debug"
.LASF181:
	.string	"RAPA_TYPE_REMAP_FN_KEY"
.LASF36:
	.string	"BT_IRQn"
.LASF148:
	.string	"step_wired"
.LASF173:
	.string	"hid_common_info"
.LASF116:
	.string	"rr_idx_usb"
.LASF92:
	.string	"HAL_EINT_LPCOMP"
.LASF217:
	.string	"length"
.LASF14:
	.string	"int8_t"
.LASF110:
	.string	"HID_REPORT_RATE_1K_HZ"
.LASF152:
	.string	"hid_scenario_type"
.LASF69:
	.string	"HAL_EINT_NUMBER_31"
.LASF70:
	.string	"HAL_EINT_NUMBER_32"
.LASF138:
	.string	"T_OUTPUT_CTRL_PIN_INFO_S"
.LASF129:
	.string	"combo"
.LASF73:
	.string	"HAL_EINT_NUMBER_35"
.LASF74:
	.string	"HAL_EINT_NUMBER_36"
.LASF75:
	.string	"HAL_EINT_NUMBER_37"
.LASF197:
	.string	"memset"
.LASF77:
	.string	"HAL_EINT_NUMBER_39"
.LASF154:
	.string	"flags"
.LASF219:
	.string	"max_len"
.LASF123:
	.string	"status"
.LASF227:
	.string	"hid_common_set_hid_para"
.LASF136:
	.string	"T_HID_REPORT_KB_CONSUMER2_S"
.LASF215:
	.string	"para_type"
.LASF131:
	.string	"consumer"
.LASF16:
	.string	"uint8_t"
.LASF135:
	.string	"T_HID_REPORT_KB_STD5_S"
.LASF212:
	.string	"hid_common_clear_hid_exp_flag"
.LASF89:
	.string	"HAL_EINT_USB0"
.LASF223:
	.string	"hid_common_set_app_feature"
.LASF177:
	.string	"PARA_TYPE_RR_IDX"
.LASF164:
	.string	"scroll_ctrl"
.LASF157:
	.string	"delay_for_key_polling_ms"
.LASF103:
	.string	"DBG_PIN_MAX"
.LASF170:
	.string	"app_shared_parameters"
.LASF101:
	.string	"DBG_PIN_USB_TX_SUCCESS"
.LASF39:
	.string	"HAL_EINT_NUMBER_1"
.LASF51:
	.string	"HAL_EINT_NUMBER_13"
.LASF112:
	.string	"HID_REPORT_RATE_4K_HZ"
.LASF88:
	.string	"HAL_EINT_UART_2_RX"
.LASF54:
	.string	"HAL_EINT_NUMBER_16"
.LASF100:
	.string	"DBG_PIN_USB_SOF"
.LASF104:
	.string	"enable_mask"
.LASF78:
	.string	"HAL_EINT_NUMBER_40"
.LASF79:
	.string	"HAL_EINT_NUMBER_41"
.LASF80:
	.string	"HAL_EINT_NUMBER_42"
.LASF81:
	.string	"HAL_EINT_NUMBER_43"
.LASF82:
	.string	"HAL_EINT_NUMBER_44"
.LASF83:
	.string	"HAL_EINT_NUMBER_45"
.LASF84:
	.string	"HAL_EINT_NUMBER_46"
.LASF37:
	.string	"IRQ_NUMBER_MAX"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/workdir/airoha/risc-v"
.LASF0:
	.string	"/workdir/airoha/common/applications/hid/src/hid_common.c"
	.ident	"GCC: (xPack GNU RISC-V Embedded GCC x86_64) 13.2.0"
