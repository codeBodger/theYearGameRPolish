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

#define abs(reg) __asm__(
    "# Written as `#define abs(reg)` in funcs.c\n\t"
    "# " reg "= abs(" reg "), uses t0i\n\t"
    "eor t0i, " reg ", " reg " asr #31\n\t"
    "sub " reg ", t0i , " reg " asr #31\n"
);


int isqrt(int v) {
    abs("p0i");
    if (sqrtArr[v % SQRTARR_SIZE] * sqrtArr[v % SQRTARR_SIZE] != v) return 0;
    return sqrtArr[v % SQRTARR_SIZE];
}


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
