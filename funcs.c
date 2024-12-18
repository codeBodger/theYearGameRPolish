#include "funcs.h"
__asm__(".include \"reg_rename.has\"\n\t");

inline int abs(int v) {
    __asm__(
        "# Written as `inline int abs(int v)` in main.c\n\t"
        "# r0i = abs(p0i), uses t0i\n\t"
        "eor t0i, p0i, p0i asr #31\n\t"
        "sub r0i, t0i, p0i asr #31\n\t"
    );
}
