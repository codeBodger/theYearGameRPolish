.include "named_registers.has"

.data
handler_i_printString:
    .string "\ni:%16lx\n"
handlerLoopPrintString:
    .string "%3d: value:%16lx\tscore:%d\t\t%3d: value:%16lx\tscore:%d\n"
handlerPromptPrintString:
    .string "Would you like to stop the program? (y/N): "
handlerPromptScanString:
    .string "%c"

.text
    .global interuptHandler
interuptHandler:
    // Save ALL registers
    stp  x0,  x1, [SP, #-16]!
    stp  x2,  x3, [SP, #-16]!
    stp  x4,  x5, [SP, #-16]!
    stp  x6,  x7, [SP, #-16]!
    stp  x8,  x9, [SP, #-16]!
    stp x10, x11, [SP, #-16]!
    stp x12, x13, [SP, #-16]!
    stp x14, x15, [SP, #-16]!
    stp x16, x17, [SP, #-16]!
    stp x18, x19, [SP, #-16]!
    stp x20, x21, [SP, #-16]!
    stp x22, x23, [SP, #-16]!
    stp x24, x25, [SP, #-16]!
    stp x26, x27, [SP, #-16]!
    stp x28, x29, [SP, #-16]!
    stp lr,  xzr, [SP, #-16]!

    // Print the current state
    ldr x0, =handler_i_printString
    mov x1, i
    bl printf

    j  .req x19
    j_ .req x20
    mov j, #0
handlerloop:
    cmp j, #50
    bgt handlerloopE

    add j_, j, #50
    // get the values and store them in x21, x23
    ldr x21, [vals, j,  LSL #3]
    ldr x23, [vals, j_, LSL #3]

    // get the scores and store them in x22, x24
    ldrb w22, [scrs, j ]
    ldrb w24, [scrs, j_]

    #call printf
    ldr x0, =handlerLoopPrintString
    mov x1, j
    mov x2, x21
    mov x3, x22
    mov x4, j_
    mov x5, x23
    mov x6, x24
    bl printf

    add j, j, #1

    b handlerloop

handlerloopE:
    ldr x0, =handlerPromptPrintString
    bl printf
    ldr x0, =handlerPromptScanString
    mov x1, SP
    add x1, x1, #8
    bl scanf
    ldrb w0, [SP, #8]
    cmp x0, #'y'
    beq earlyExit

    // Restore ALL registers
    ldp lr,  xzr, [SP], #16
    ldp x28, x29, [SP], #16
    ldp x26, x27, [SP], #16
    ldp x24, x25, [SP], #16
    ldp x22, x23, [SP], #16
    ldp x20, x21, [SP], #16
    ldp x18, x19, [SP], #16
    ldp x16, x17, [SP], #16
    ldp x14, x15, [SP], #16
    ldp x12, x13, [SP], #16
    ldp x10, x11, [SP], #16
    ldp  x8,  x9, [SP], #16
    ldp  x6,  x7, [SP], #16
    ldp  x4,  x5, [SP], #16
    ldp  x2,  x3, [SP], #16
    ldp  x0,  x1, [SP], #16

    ret

earlyExit:
    mov x0, #1
    mov x8, #94
    svc #0
