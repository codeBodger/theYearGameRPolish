#include <stdint.h>
#include <signal.h>

#include "funcs.h"

#define DIGIT1 2
#define DIGIT2 0
#define DIGIT3 2
#define DIGIT4 4

#define LSR(args) __asm__("lsr " args "\n")
#define AND(args) __asm__("and " args "\n")


#define MAINLOOP(holePatn) __asm__("" \
        "# do {\n\t" \
        "mov i, #0\n" \
    "mainloopstart:\n\t" \
        "mov score, #3\n" \
    ); \

    /* digitOrder: */ \
HOLE_PATTERN_##holePatn(DIGIT1, DIGIT2, DIGIT3, DIGIT4); \
__asm__("sub score, score, #1\n"); \
HOLE_PATTERN_##holePatn(DIGIT1, DIGIT2, DIGIT4, DIGIT3); \
HOLE_PATTERN_##holePatn(DIGIT1, DIGIT3, DIGIT2, DIGIT4); \
/* HOLE_PATTERN_##holePatn(DIGIT1, DIGIT4, DIGIT2, DIGIT3); */ \
/* HOLE_PATTERN_##holePatn(DIGIT1, DIGIT4, DIGIT3, DIGIT2); */ \
/* HOLE_PATTERN_##holePatn(DIGIT1, DIGIT3, DIGIT4, DIGIT2); */ \

HOLE_PATTERN_##holePatn(DIGIT2, DIGIT1, DIGIT3, DIGIT4); \
HOLE_PATTERN_##holePatn(DIGIT2, DIGIT1, DIGIT4, DIGIT3); \
HOLE_PATTERN_##holePatn(DIGIT3, DIGIT1, DIGIT2, DIGIT4); \
/* HOLE_PATTERN_##holePatn(DIGIT4, DIGIT1, DIGIT2, DIGIT3); */ \
/* HOLE_PATTERN_##holePatn(DIGIT4, DIGIT1, DIGIT3, DIGIT2); */ \
/* HOLE_PATTERN_##holePatn(DIGIT3, DIGIT1, DIGIT4, DIGIT2); */ \

HOLE_PATTERN_##holePatn(DIGIT3, DIGIT2, DIGIT1, DIGIT4); \
/* HOLE_PATTERN_##holePatn(DIGIT4, DIGIT2, DIGIT1, DIGIT3); */ \
HOLE_PATTERN_##holePatn(DIGIT2, DIGIT3, DIGIT1, DIGIT4); \
HOLE_PATTERN_##holePatn(DIGIT2, DIGIT4, DIGIT1, DIGIT3); \
/* HOLE_PATTERN_##holePatn(DIGIT3, DIGIT4, DIGIT1, DIGIT2); */ \
/* HOLE_PATTERN_##holePatn(DIGIT4, DIGIT3, DIGIT1, DIGIT2); */ \

/* HOLE_PATTERN_##holePatn(DIGIT4, DIGIT2, DIGIT3, DIGIT1); */ \
HOLE_PATTERN_##holePatn(DIGIT3, DIGIT2, DIGIT4, DIGIT1); \
/* HOLE_PATTERN_##holePatn(DIGIT4, DIGIT3, DIGIT2, DIGIT1); */ \
/* HOLE_PATTERN_##holePatn(DIGIT3, DIGIT4, DIGIT2, DIGIT1); */ \
HOLE_PATTERN_##holePatn(DIGIT2, DIGIT4, DIGIT3, DIGIT1); \
HOLE_PATTERN_##holePatn(DIGIT2, DIGIT3, DIGIT4, DIGIT1); \
__asm__("add score, score, #1\n") \

    __asm__("" \
        "# i++\n\t" \
        "add i, i, #1\n\t" \
        "# } while (i)\n\t" \
        "cmp i, #0\n\t" \
        "bne mainloopstart\n" \
    )

    // for (i = 0; ; i++) {
    //     goto digitOrder;
    // mainloopend:
    // }

// #define HOLE_PATTERN(d1, d2, d3, d4) HOLE_PATTERN_##holePatn(d1, d2, d3, d4)

#define HOLE_PATTERN_000 binOpOrd0h(((d1*10 +d2)*10 +d3)*10 +d4)
#define HOLE_PATTERN_001 binOpOrd1h((d1*10 +d2)*10 +d3, d4)
#define HOLE_PATTERN_010 binOpOrd1h(d1*10 +d2, d3*10 +d4)
#define HOLE_PATTERN_011 binOpOrd2h(d1*10 +d2, d3, d4)
#define HOLE_PATTERN_100 binOpOrd1h(d1, (d2*10 +d3)*10 +d4)
#define HOLE_PATTERN_101 binOpOrd2h(d1, d2*10 +d3, d4)
#define HOLE_PATTERN_110 binOpOrd2h(d1, d2, d3*10 +d4)
#define HOLE_PATTERN_111 binOpOrd3h(d1, d2, d3, d4)


// void digitOrder();
// void holPattern(int d1, int d2, int d3, int d4);
void binOpOrd3h(int n1, int n2, int n3, int n4);
void binOpOrd2h(int n1, int n2, int n3);
void binOpOrd1h(int n1, int n2);
void binOpOrd0h(int n1);

void interuptHandler(int sig);
