/* according to the linker script format, place some code in RAM */
/*
    example:
        // place all the code sections in the OBJECT files
        // containing mem*.o in the LIBRARY files matching
        // libc*.a into RAM for execution
        *libc*.a:*mem*.c.o(.text*)

        // place all code sections in OBJECT files matching
        // swap_helper.S.obj into RAM for execution
        *swap_helper.S.obj(.text*)
 */
