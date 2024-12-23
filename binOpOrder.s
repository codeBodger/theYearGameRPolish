.include "reg_rename.has"


.macro GET_UNARIES, on0ret
adr bojt, getu_0_jt\@
    # load the address of the start of the jump table
getu_0_start\@:
    and bosw, bosi, #0xC000000000000000 // 3 from left
    lsr bosw, bosw, #59
    lsl bosi, bosi, #2
    add incshft, incshft, #2
    add bosw, bosw, bojt
    br bosw
getu_0_jt\@:
    # case 0:
    b getu_0_end\@
    nop

    # case 1:
    bl isqrt
    b getu_0_btm\@

    # case 2:
    bl fact
    b getu_0_btm\@

    # case 3:
    bl dfact

getu_0_btm\@:
    cmp r0i, #0
    beq \on0ret
    b getu_0_start\@
getu_0_end\@:
.endm


    .global binOpOrd0h
binOpOrd0h:
    # back up the link register
    mov binOpOrderLR, lr

    mov incshft, #-1

    # 0
        mov bosi, i
        # get a: nothing to do, it's already there
        # get unaries
        GET_UNARIES binOpOrd0h_0_end

        # get sign
            and bosw, bosi, #0x8000000000000000 // 1 from left
            lsl bosi, bosi, #1
            add incshft, incshft, #1
            cmp bosw, #0
            beq binOpOrd0h_0_sign_0_end
            sub r0i, wzr, r0i
        binOpOrd0h_0_sign_0_end:

        # check if in range
            cmp r0i, #0
            blt binOpOrd0h_0_end
            cmp r0i, #100
            bgt binOpOrd0h_0_end
        # check if better score
            ldr t0i, [scrs, r0l]
            cmp score, t0i
            ble binOpOrd0h_0_end
        # finally, we know it's better!
            str i, [vals, r0l, LSL #3]

    binOpOrd0h_0_end:
        # maxshft = max(incshft, maxshft)
        cmp incshft, maxshft
        csel maxshft, incshft, maxshft, GT

    # restore the link register
    mov lr, binOpOrderLR

    ret
