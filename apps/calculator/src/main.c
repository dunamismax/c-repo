#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For strcmp
#include "math_lib.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <num1> <operator> <num2>\n", argv[0]);
        return 1;
    }

    char *endptr1, *endptr2;
    double num1 = strtod(argv[1], &endptr1);
    char *op = argv[2];
    double num2 = strtod(argv[3], &endptr2);

    // Check for conversion errors
    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Error: Invalid number provided.\n");
        return 1;
    }

    double result;

    if (strcmp(op, "+") == 0) {
        result = add(num1, num2);
    } else if (strcmp(op, "-") == 0) {
        result = subtract(num1, num2);
    } else if (strcmp(op, "*") == 0) {
        result = multiply(num1, num2);
    } else if (strcmp(op, "/") == 0) {
        if (num2 == 0) {
            fprintf(stderr, "Error: Division by zero is not allowed.\n");
            return 1;
        }
        result = divide(num1, num2);
    } else {
        fprintf(stderr, "Error: Invalid operator '%s'. Use +, -, *, or /\n", op);
        return 1;
    }

    printf("Result: %.2f\n", result);

    return 0;
}
