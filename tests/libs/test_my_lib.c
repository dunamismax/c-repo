#include <stdio.h>
#include "../../libs/math_lib/include/math_lib.h"

int main()
{
    printf("Testing Math Library...\n");

    if (add(2, 3) == 5)
    {
        printf("  PASS: add(2, 3)\n");
    }
    else
    {
        printf("  FAIL: add(2, 3)\n");
    }

    if (subtract(5, 2) == 3)
    {
        printf("  PASS: subtract(5, 2)\n");
    }
    else
    {
        printf("  FAIL: subtract(5, 2)\n");
    }

    if (multiply(3, 4) == 12)
    {
        printf("  PASS: multiply(3, 4)\n");
    }
    else
    {
        printf("  FAIL: multiply(3, 4)\n");
    }

    if (divide(10, 2) == 5)
    {
        printf("  PASS: divide(10, 2)\n");
    }
    else
    {
        printf("  FAIL: divide(10, 2)\n");
    }

    printf("Math Library test complete.\n");

    return 0;
}