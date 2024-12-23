#include "main.h"
__asm__(".include \"reg_rename.has\"\n");

// void interuptHandler(int sig) {
//     //save ALL registers
//     //print the current state
//     //restore ALL registers

//     // i = 0; //dummy stuff so there's something in the functions to set a breakpoint to
// }

uint64_t values[101];
uint8_t  scores[101];


int main() {
    __asm__(""
        "ldr vals, =values\n\t"
        "ldr scrs, =scores\n\n"
    );

    initSqrt();
    initFact();
    initDfact();

    signal(SIGINT, interuptHandler);

    __asm__("mov score, #2\n");
    MAINLOOP(000);
    MAINLOOP(001);
    MAINLOOP(010);
    MAINLOOP(011);
    MAINLOOP(100);
    MAINLOOP(101);
    MAINLOOP(110);
    __asm__("mov score, #3\n");
    MAINLOOP(111);

    // __asm__(""
    //     "# do {\n\t"
    //     "mov i, #0\n"
    // "mainloopstart:\n\t"
    //     "mov score, #3\n"
    // ); {

    // // digitOrder:
    //     holPattern(DIGIT1, DIGIT2, DIGIT3, DIGIT4);
    //     __asm__("mov score, #2\n");
    //     holPattern(DIGIT1, DIGIT2, DIGIT4, DIGIT3);
    //     holPattern(DIGIT1, DIGIT3, DIGIT2, DIGIT4);
    //     // holPattern(DIGIT1, DIGIT4, DIGIT2, DIGIT3);
    //     // holPattern(DIGIT1, DIGIT4, DIGIT3, DIGIT2);
    //     // holPattern(DIGIT1, DIGIT3, DIGIT4, DIGIT2);

    //     holPattern(DIGIT2, DIGIT1, DIGIT3, DIGIT4);
    //     holPattern(DIGIT2, DIGIT1, DIGIT4, DIGIT3);
    //     holPattern(DIGIT3, DIGIT1, DIGIT2, DIGIT4);
    //     // holPattern(DIGIT4, DIGIT1, DIGIT2, DIGIT3);
    //     // holPattern(DIGIT4, DIGIT1, DIGIT3, DIGIT2);
    //     // holPattern(DIGIT3, DIGIT1, DIGIT4, DIGIT2);

    //     holPattern(DIGIT3, DIGIT2, DIGIT1, DIGIT4);
    //     // holPattern(DIGIT4, DIGIT2, DIGIT1, DIGIT3);
    //     holPattern(DIGIT2, DIGIT3, DIGIT1, DIGIT4);
    //     holPattern(DIGIT2, DIGIT4, DIGIT1, DIGIT3);
    //     // holPattern(DIGIT3, DIGIT4, DIGIT1, DIGIT2);
    //     // holPattern(DIGIT4, DIGIT3, DIGIT1, DIGIT2);

    //     // holPattern(DIGIT4, DIGIT2, DIGIT3, DIGIT1);
    //     holPattern(DIGIT3, DIGIT2, DIGIT4, DIGIT1);
    //     // holPattern(DIGIT4, DIGIT3, DIGIT2, DIGIT1);
    //     // holPattern(DIGIT3, DIGIT4, DIGIT2, DIGIT1);
    //     holPattern(DIGIT2, DIGIT4, DIGIT3, DIGIT1);
    //     holPattern(DIGIT2, DIGIT3, DIGIT4, DIGIT1);

    // } __asm__(""
    //     "# i++\n\t"
    //     "add i, i, #1\n\t"
    //     "# } while (i)\n\t"
    //     "cmp i, #0\n\t"
    //     "bne mainloopstart\n"
    // );

    // for (i = 0; ; i++) {
    //     goto digitOrder;
    // mainloopend:
    // }

    return 0;
    // __asm__("# return 0;\n\t"
    //     "# Tricking it into including stuff after returning\n\t"
    //     "mov w0, #0\n\t"
    //     "ldp x29, x30, [sp], 16\n\t"
    //     // ".cfi_restore 30\n\t"
    //     // ".cfi_restore 29\n\t"
    //     // ".cfi_def_cfa_offset 0\n\t"
    //     "ret\n"
    //     // ".cfi_endproc\n"
    // );


    // __asm__(""
    //     "# MAKE SURE TO FIX REGISTER NUMBERS HERE!!!\n\t"
    //     "# THAT IS: w19:w22 -> hp0i:hp3i\n"
    // "holPattern:\n\t"
    //     "# back up the link register\n\t"
    //     "mov holPatternLR, lr\n\n\t"

    //     "# copy params to stable registers for this function\n\t"
    //     "mov hp0i, p0i\n\t"
    //     "mov hp1i, p1i\n\t"
    //     "mov hp2i, p2i\n\t"
    //     "mov hp3i, p3i\n\n"
    // );

    //     register int d1, d2, d3, d4;
    //     __asm__("sub score, score, #1\n");
    //     // 000
    //     binOpOrd0h(((d1*10 +d2)*10 +d3)*10 +d4);
    //     // 001
    //     binOpOrd1h((d1*10 +d2)*10 +d3, d4);
    //     // 010
    //     binOpOrd1h(d1*10 +d2, d3*10 +d4);
    //     // 011
    //     binOpOrd2h(d1*10 +d2, d3, d4);
    //     // 100
    //     binOpOrd1h(d1, (d2*10 +d3)*10 +d4);
    //     // 101
    //     binOpOrd2h(d1, d2*10 +d3, d4);
    //     // 110
    //     binOpOrd2h(d1, d2, d3*10 +d4);
    //     __asm__("add score, score, #1\n");
    //     // 111
    //     binOpOrd3h(d1, d2, d3, d4);

    // __asm__(""
    //     "# restore the link register\n\t"
    //     "mov lr, holPatternLR\n\n"
        
    //     "ret\n\n"
    // );
}

void binOpOrd3h(int n1, int n2, int n3, int n4) {
    // 123
        // get a
        // get unaries
        // get sign
        // get b
        // get unaries
        // get sign
        // get binary
        // get unaries
        // get sign
        // get c
        // get unaries
        // get sign
        // get binary
        // get unaries
        // get sign
        // get d
        // get unaries
        // get sign
        // get binary
        // get unaries
        // get sign
    // 132 (same as 231)
    // 213
    // 312
    // 321
}

void binOpOrd2h(int n1, int n2, int n3) {
    // 12
    // 21
}
