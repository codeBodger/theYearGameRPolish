.include "reg_rename.has"


.macro GET_BINARY, on0ret
adr bojt, getb_jt\@ // load the address of the start of the jump table

getb_start\@:
    and bosw, bosi, #0xC000000000000000 // 3 from left
    lsr bosw, bosw, #59
    lsl bosi, bosi, #2
    add incshft, incshft, #2
    add bosw, bosw, bojt
    br bosw
getb_jt\@:
    // case 0:
    add r0i, p0i, p1i
    b getb_end\@

    // case 1:
    mul r0i, p0i, p1i
    b getb_end\@

    // case 2:
    bl ipow
    b getb_0check\@

    // case 3:
    sdiv r0i, p0i, p1i
    // fall through to getb_0check\@

getb_0check\@:
    cmp r0i, #0
    beq \on0ret

getb_end\@:
.endm

.macro GET_UNARIES, on0ret
adr bojt, getu_0_jt\@
    // load the address of the start of the jump table
getu_0_start\@:
    and bosw, bosi, #0xC000000000000000 // 3 from left
    lsr bosw, bosw, #59
    lsl bosi, bosi, #2
    add incshft, incshft, #2
    add bosw, bosw, bojt
    br bosw
getu_0_jt\@:
    // case 0:
    b getu_0_end\@
    nop

    // case 1:
    bl isqrt
    b getu_0_btm\@

    // case 2:
    bl fact
    b getu_0_btm\@

    // case 3:
    bl dfact

getu_0_btm\@:
    cmp r0i, #0
    beq \on0ret
    b getu_0_start\@
getu_0_end\@:
.endm

.macro GET_SIGN
    and bosw, bosi, #0x8000000000000000 // 1 from left
    lsl bosi, bosi, #1
    add incshft, incshft, #1
    cmp bosw, #0
    beq sign_0_end\@
    sub r0i, wzr, r0i
sign_0_end\@:
.endm

.macro UPDATE_VALUE_SCORE_ARRS, onIrrelevant
// check if in range
    cmp r0i, #0
    blt \onIrrelevant
    cmp r0i, #100
    bgt \onIrrelevant
// check if better score
    ldr t0i, [scrs, r0l]
    cmp score, t0i
    ble \onIrrelevant
// finally, we know it's better!
    str i, [vals, r0l, LSL #3]
    str score, [scrs, r0l]
.endm

.macro UPDATE_MAXSHFT
    cmp incshft, maxshft
    csel maxshft, incshft, maxshft, GT
.endm


    .global binOpOrd0h
binOpOrd0h:
    // back up the link register
    mov binOpOrderLR, lr

    mov incshft, #-1

    // 0
        mov bosi, i
        // get a: nothing to do, it's already there
        // get unaries
        GET_UNARIES binOpOrd0h_0_end

        // get sign
        GET_SIGN

        UPDATE_VALUE_SCORE_ARRS binOpOrd0h_0_end

    binOpOrd0h_0_end:
        // maxshft = max(incshft, maxshft)
        UPDATE_MAXSHFT

    // restore the link register
    mov lr, binOpOrderLR

    ret

    .global binOpOrd1h
binOpOrd1h:
    // back up the link register
    mov binOpOrderLR, lr

    mov incshft, #-1

    // no need to store a: only one combination, immediately needed
    // store b in bobb
    mov bobb, p1i

    // 1
        mov bosi, i
        // get a: nothing to do, it's already there
        // get unaries, sign
        GET_UNARIES binOpOrd1h_1_end
        GET_SIGN

        // save a -> 1
        mov bo1b, r0i

        // get b
        mov p0i, bobb

        // get unaries, sign
        GET_UNARIES binOpOrd1h_1_end
        GET_SIGN

        // save b -> 2
        mov bo2b, r0i

        // get 1, 2
        mov p0i, bo1b
        mov p1i, bo2b

        // get binary
        GET_BINARY binOpOrd1h_1_end

        // get unaries, sign
        GET_UNARIES binOpOrd1h_1_end
        GET_SIGN

        // save 1: no need, we're done

        // update val, score, arrs
        UPDATE_VALUE_SCORE_ARRS binOpOrd1h_1_end

        // finish up
    binOpOrd1h_1_end:
        // maxshft = max(incshft, maxshft)
        UPDATE_MAXSHFT

    // restore the link register
    mov lr, binOpOrderLR

    ret
