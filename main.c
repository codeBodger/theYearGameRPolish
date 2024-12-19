#include "main.h"

uint64_t i;

// void interuptHandler(int sig) {
//     //save ALL registers
//     //print the current state
//     //restore ALL registers

//     // i = 0; //dummy stuff so there's something in the functions to set a breakpoint to
// }

int main() {
    initSqrt();
    initFact();
    initDfact();

    signal(SIGINT, interuptHandler);

    for (i = 0; ; i++) {
        goto digitOrder;
    mainloopend:
    }
    return 0;

digitOrder:
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

    goto mainloopend;
}


void holPattern(int d1, int d2, int d3, int d4) {

}

void binOpOrd3h(int n1, int n2, int n3, int n4) {

}

void binOpOrd2h(int n1, int n2, int n3) {

}

void binOpOrd1h(int n1, int n2) {

}

void binOpOrd0h(int n1) {

}
