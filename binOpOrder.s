.include "reg_rename.has"

    .global binOpOrd0h
binOpOrd0h:
    # back up the link register
    mov binOpOrderLR, lr

    # 0
        mov cur_i, i
        # get a: nothing to do, it's already there
        # get unaries
        adr bo9l, binOpOrd0h_0_getu_0_jt
            # load the address of the start of the jump table
        binOpOrd0h_0_getu_0_start:
            and bo8l, cur_i, #3
            lsl bo8l, bo8l, #3
            lsr cur_i, cur_i, #2
            add bo8l, bo8l, bo9l
            br bo8l
        binOpOrd0h_0_getu_0_jt:
            # case 0:
            b binOpOrd0h_0_getu_0_end
            nop

            # case 1:
            bl isqrt
            b binOpOrd0h_0_getu_0_btm

            # case 2:
            bl fact
            b binOpOrd0h_0_getu_0_btm

            # case 3:
            bl dfact
            
        binOpOrd0h_0_getu_0_btm:
            cmp r0i, #0
            beq binOpOrd0h_0_end
            b binOpOrd0h_0_getu_0_start
        binOpOrd0h_0_getu_0_end:

        # get sign
            and bo8l, cur_i, #1
            lsr cur_i, cur_i, #1
            cmp bo8l, #0
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

    # restore the link register
    mov lr, binOpOrderLR

    ret
