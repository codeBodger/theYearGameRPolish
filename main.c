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

    __asm__(""
        "# do {\n\t"
        "mov i, #0\n"
    "mainloopstart:\n"
    );

// digitOrder:
    holPattern(DIGIT1, DIGIT2, DIGIT3, DIGIT4);
    holPattern(DIGIT1, DIGIT2, DIGIT4, DIGIT3);
    holPattern(DIGIT1, DIGIT3, DIGIT2, DIGIT4);
    // holPattern(DIGIT1, DIGIT4, DIGIT2, DIGIT3);
    // holPattern(DIGIT1, DIGIT4, DIGIT3, DIGIT2);
    // holPattern(DIGIT1, DIGIT3, DIGIT4, DIGIT2);

    holPattern(DIGIT2, DIGIT1, DIGIT3, DIGIT4);
    holPattern(DIGIT2, DIGIT1, DIGIT4, DIGIT3);
    holPattern(DIGIT3, DIGIT1, DIGIT2, DIGIT4);
    // holPattern(DIGIT4, DIGIT1, DIGIT2, DIGIT3);
    // holPattern(DIGIT4, DIGIT1, DIGIT3, DIGIT2);
    // holPattern(DIGIT3, DIGIT1, DIGIT4, DIGIT2);

    holPattern(DIGIT3, DIGIT2, DIGIT1, DIGIT4);
    // holPattern(DIGIT4, DIGIT2, DIGIT1, DIGIT3);
    holPattern(DIGIT2, DIGIT3, DIGIT1, DIGIT4);
    holPattern(DIGIT2, DIGIT4, DIGIT1, DIGIT3);
    // holPattern(DIGIT3, DIGIT4, DIGIT1, DIGIT2);
    // holPattern(DIGIT4, DIGIT3, DIGIT1, DIGIT2);

    // holPattern(DIGIT4, DIGIT2, DIGIT3, DIGIT1);
    holPattern(DIGIT3, DIGIT2, DIGIT4, DIGIT1);
    // holPattern(DIGIT4, DIGIT3, DIGIT2, DIGIT1);
    // holPattern(DIGIT3, DIGIT4, DIGIT2, DIGIT1);
    holPattern(DIGIT2, DIGIT4, DIGIT3, DIGIT1);
    holPattern(DIGIT2, DIGIT3, DIGIT4, DIGIT1);

    __asm__(""
        "# i++\n\t"
        "add i, i, #1\n\t"
        "# } while (i)\n\t"
        "cmp i, #0\n\t"
        "bne mainloopstart\n\t"
    );

    // for (i = 0; ; i++) {
    //     goto digitOrder;
    // mainloopend:
    // }
    return 0;
}


void holPattern(int d1, int d2, int d3, int d4) {
    // 000
    binOpOrd0h(((d1*10 +d2)*10 +d3)*10 +d4);
    // 001
    binOpOrd1h((d1*10 +d2)*10 +d3, d4);
    // 010
    binOpOrd1h(d1*10 +d2, d3*10 +d4);
    // 011
    binOpOrd2h(d1*10 +d2, d3, d4);
    // 100
    binOpOrd1h(d1, (d2*10 +d3)*10 +d4);
    // 101
    binOpOrd2h(d1, d2*10 +d3, d4);
    // 110
    binOpOrd2h(d1, d2, d3*10 +d4);
    // 111
    binOpOrd3h(d1, d2, d3, d4);
}

void binOpOrd3h(int n1, int n2, int n3, int n4) {

}

void binOpOrd2h(int n1, int n2, int n3) {

}

void binOpOrd1h(int n1, int n2) {

}

void binOpOrd0h(int n1) {

}
