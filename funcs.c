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

__asm__(".text\n");

#define abs(reg) \
    "# Written as `#define abs(reg)` in funcs.c\n\t" \
    "# " reg " = abs(" reg "), clobbers flags\n\t" \
    "tst " reg ", " reg "\n\t" \
    "cneg " reg ", " reg ", MI\n\n\t"
    // "# " reg " = abs(" reg "), uses t0i\n\t" \
    // "eor t0i, " reg ", " reg " ASR #31\n\t" \
    // "sub " reg ", t0i, " reg " ASR #31\n\n\t" \

__asm__( ".global isqrt\nisqrt:\n\t"
    "# int isqrt(int v) {\n\t\t"
        "# abs(\"p0i\");\n\t\t"
        "# if (sqrtArr[v % SQRTARR_SIZE] * sqrtArr[v % SQRTARR_SIZE] != v) return 0;\n\t\t"
        "# return sqrtArr[v % SQRTARR_SIZE];\n\t"
    "# }\n\n\t"

    abs("p0i")

    "# t0i = p0i % SQRTARR_SIZE\n\t"
    "mov t1i, #0x2000000\n\t"
    "udiv t0i, p0i, t1i\n\t"
    "msub t0i, t0i, t1i, p0i\n\n\t"

    "# t1l = sqrtArr\n\t"
    "ldr t1l, =sqrtArr\n\t"
    "# t1i = (int*)t1l[t0i]\n\t"
    "ldr t1i, [t1l, t0l, LSL #2]\n\n\t"

    "# t0i = t1i * t1i\n\t"
    "mul t0i, t1i, t1i\n\t"
    "# if (t0i != p0i) return 0\n\t"
    "cmp t0i, p0i\n\t"
    "beq isqrt_good\n\t"
    "mov r0i, #0\n\t"
    "ret\n\n\t"

    "# else return t1i\n"
"isqrt_good:\n\t"
    "mov r0i, t1i\n\t"
    "ret\n"
);

__asm__( ".global fact\nfact:\n\t"
    abs("p0i")

    "# if (p0i >= FACTARR_SIZE) return 0\n\t"
    "cmp p0i, #13\n\t"
    "blt fact_good\n\t"
    "mov r0i, #0\n\t"
    "ret\n\n\t"

    "# else return factArr[p0i]\n"
"fact_good:\n\t"
    "# t0l = factArr\n\t"
    "ldr t0l, =factArr\n\t"
    "# r0i = (int*)t1l[p0i]\n\t"
    "ldr r0i, [t0l, p0l, LSL #2]\n\t"
    "ret\n\n\t"
);

__asm__( ".global dfact\ndfact:\n\t"
    abs("p0i")

    "# if (p0i >= DFACTARR_SIZE) return 0\n\t"
    "cmp p0i, #20\n\t"
    "blt dfact_good\n\t"
    "mov r0i, #0\n\t"
    "ret\n\n\t"

    "# else return dfactArr[p0i]\n"
"dfact_good:\n\t"
    "# t0l = dfactArr\n\t"
    "ldr t0l, =dfactArr\n\t"
    "# r0i = (int*)t1l[p0i]\n\t"
    "ldr r0i, [t0l, p0l, LSL #2]\n\t"
    "ret\n\n\t"
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
