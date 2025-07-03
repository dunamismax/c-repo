#include <stdio.h>
#include "math_lib.h"

int main() {
    printf("Testing math_lib:\n");
    printf("5 + 3 = %d (expected 8)\n", add(5, 3));
    printf("5 - 3 = %d (expected 2)\n", subtract(5, 3));
    printf("5 * 3 = %d (expected 15)\n", multiply(5, 3));
    printf("5 / 2 = %.2f (expected 2.50)\n", divide(5, 2));
    printf("5 / 0 = %.2f (expected 0.00)\n", divide(5, 0));
    return 0;
}

