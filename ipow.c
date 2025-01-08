// Modified from https://gist.github.com/orlp/3551590
int32_t ipow(register int32_t base, register int32_t exp) {
    __asm__("// remmember to add abs");

    static const uint8_t highest_bit_set[] = {
        0, 1, 2, 2, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5 // anything past 31 is a guaranteed overflow with base > 1
    };

    register int64_t result = 1;

    switch (highest_bit_set[exp]) {
        case 6:
            if (exp & 1) result *= base;
            exp >>= 1;
            base *= base;
        case 5:
            if (exp & 1) result *= base;
            exp >>= 1;
            base *= base;
        case 4:
            if (exp & 1) result *= base;
            exp >>= 1;
            base *= base;
        case 3:
            if (exp & 1) result *= base;
            exp >>= 1;
            base *= base;
        case 2:
            if (exp & 1) result *= base;
            exp >>= 1;
            base *= base;
        case 1:
            if (exp & 1) result *= base;
        case 0:
            return result;

        default: // deal with base of 1, return 0 on overflow/underflow
            if (base == 1) return 1;

            // unneeded due to abs
            // if (base == -1) return 1 - 2 * (exp & 1);

            return 0;
    }
}
