#include <stdint.h>
#include <signal.h>

#include "funcs.h"

#define DIGIT1 2
#define DIGIT2 0
#define DIGIT3 2
#define DIGIT4 4

// void digitOrder();
void holPattern(int d1, int d2, int d3, int d4);
void binOpOrd3h(int n1, int n2, int n3, int n4);
void binOpOrd2h(int n1, int n2, int n3);
void binOpOrd1h(int n1, int n2);
void binOpOrd0h(int n1);

void interuptHandler(int sig);
