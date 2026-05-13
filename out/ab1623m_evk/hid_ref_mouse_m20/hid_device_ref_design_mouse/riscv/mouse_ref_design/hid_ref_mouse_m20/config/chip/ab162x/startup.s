# 0 "/workdir/airoha/risc-v/config/chip/ab162x/startup.S"
# 1 "/workdir/airoha/risc-v//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/workdir/airoha/risc-v/config/chip/ab162x/startup.S"
# 35 "/workdir/airoha/risc-v/config/chip/ab162x/startup.S"
.section .text

.align 4
reset_handler:

    mv x1, x0
    mv x2, x0
    mv x3, x0
    mv x4, x0
    mv x5, x0
    mv x6, x0
    mv x7, x0
    mv x8, x0
    mv x9, x0
    mv x10, x0
    mv x11, x0
    mv x12, x0
    mv x13, x0
    mv x14, x0
    mv x15, x0
# 75 "/workdir/airoha/risc-v/config/chip/ab162x/startup.S"
    la x2, _stack_start

_start:
    .global _start


    la x3, _bss_start
    la x4, _bss_end

    bge x3, x4, zero_loop_end

zero_loop:
    sw x0, 0(x3)
    addi x3, x3, 4
    ble x3, x4, zero_loop
zero_loop_end:


    li x5, 0xA5A5A5A5
    la x3, _isr_stack_begin
    la x4, _isr_stack_end
    jal x1, fix_data_init

    la x3, _thread_stack_begin
    la x4, _thread_stack_end
    jal x1, fix_data_init

main_entry:

    addi x10, x0, 0
    addi x11, x0, 0
    jal x1, main
    j .



.extern aiorha_exc_handler
.extern airoha_int_handler
    .section .vectors, "ax"
    .option norvc;


    .org 0x00
    jal x0, aiorha_exc_handler
    .rept 30
    jal x0, airoha_int_handler
    .endr
    jal x0, aiorha_exc_handler


    .org 0x80
    jal x0, reset_handler


    .global fix_data_init

fix_data_init:
    bge x3, x4, fix_data_init_end
    sw x5, 0(x3)
    addi x3, x3, 4
    j fix_data_init
fix_data_init_end:
    ret
