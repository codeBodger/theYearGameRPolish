#include "funcs.h"
__asm__(".include \"reg_rename.has\"\n");

int sqrtArr[SQRTARR_SIZE];
int factArr[FACTARR_SIZE];
int dfactArr[DFACTARR_SIZE];

// inline int abs(int v) {
//     __asm__(
//         "# Written as `inline int abs(int v)` in funcs.c\n\t"
//         "# r0i = abs(p0i), uses t0i\n\t"
//         "eor t0i, p0i, p0i asr #31\n\t"
//         "sub r0i, t0i, p0i asr #31\n\t"
//     );
// }

#define abs(reg) \
    "# Written as `#define abs(reg)` in funcs.c\n\t" \
    "# " reg " = abs(" reg "), uses t0i\n\t" \
    "eor t0i, " reg ", " reg " asr #31\n\t" \
    "sub " reg ", t0i, " reg " asr #31\n\n\t" \

isqrt:
__asm__(
    "# int isqrt(int v) {\n\t\t"
        "# abs(\"p0i\");\n\t\t"
        "# if (sqrtArr[v % SQRTARR_SIZE] * sqrtArr[v % SQRTARR_SIZE] != v) return 0;\n\t\t"
        "# return sqrtArr[v % SQRTARR_SIZE];\n\t"
    "# }\n\n\t"

    abs("p0i");

    "# t0i = p0i % SQRTARR_SIZE\n\t"
    "mov t1i, #0x2000000\n\t"
    "udiv t0i, p0i, t1i\n\t"
    "msub t0i, t0i, t1i, p0i\n\n\t"

    "# t1l = sqrtArr\n\t"
    "ldr t1l, =sqrtArr\n\t"
    "# t1i = (int*)t1l[t0i]\n\t"
    "ldr t1i, [t1l, t0i LSL #2]\n\n\t"

    "# t0i = t1i * t1i\n\t"
    "mul t0i, t1i, t1i\n\t"
    "# if (t0i != p0i) return 0\n\t"
    "cmp t0i, p0i\n\t"
    "beq isqrt_good\n\t"
    "mov r0i, #0\n\t"
    "ret\n\n"
"isqrt_good:\n\t"
    "move r0i, t1i\n\t"
    "ret\n"
);


#define MAX_SQUAREABLE 0xB504
void initSqrt() {
    for (int i = 0; i < MAX_SQUAREABLE; i++)
        sqrtArr[i*i % SQRTARR_SIZE] = i;
}

void initFact() {
    factArr[0] = 1;
    for (int i = 1; i < FACTARR_SIZE; i++)
        factArr[i] = factArr[i-1] * i;
}

void initDfact() {
    dfactArr[0] = dfactArr[1] = 1;
    for (int i = 2; i < DFACTARR_SIZE; i++)
        dfactArr[i] = dfactArr[i-2] * i;
}
