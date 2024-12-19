#include "funcs.h"
__asm__(".include \"reg_rename.has\"\n\t");

int sqrtArr[SQRTARR_SIZE];
int factArr[FACTARR_SIZE];
int dfactArr[DFACTARR_SIZE];

inline int abs(int v) {
    __asm__(
        "# Written as `inline int abs(int v)` in main.c\n\t"
        "# r0i = abs(p0i), uses t0i\n\t"
        "eor t0i, p0i, p0i asr #31\n\t"
        "sub r0i, t0i, p0i asr #31\n\t"
    );
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
