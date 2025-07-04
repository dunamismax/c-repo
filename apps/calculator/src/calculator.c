/*******************************************************************************
 * @file calculator.c
 * @brief A simple command-line calculator program.
 *
 * This program performs basic arithmetic operations (+, -, *, /) on two
 * numbers provided as command-line arguments. It includes robust error
 * handling for invalid input and division by zero.
 *
 * @example
 *   ./calculator 10 + 20
 *   ./calculator 5.5 '*' 2
 *   ./calculator 100 / 2.5
 *
 * @author Gemini
 * @date 2025-07-04
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>

// --- Function Prototypes ---

static void print_usage_and_exit(const char *prog_name);
static double parse_double(const char *str);
static double calculate(double num1, char op, double num2);

// --- Main Application Logic ---

/**
 * @brief The main entry point of the calculator application.
 *
 * Parses command-line arguments to perform a calculation.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int main(int argc, char *argv[])
{
    // Validate the number of command-line arguments.
    if (argc != 4)
    {
        print_usage_and_exit(argv[0]);
    }

    // The operator should be a single character.
    if (strlen(argv[2]) != 1)
    {
        fprintf(stderr, "Error: Invalid operator '%s'. Operator must be a single character: +, -, *, or /\n", argv[2]);
        return EXIT_FAILURE;
    }

    const char operator = argv[2][0];
    const double num1 = parse_double(argv[1]);
    const double num2 = parse_double(argv[3]);

    // Perform the calculation.
    const double result = calculate(num1, operator, num2);

    // Print the result with user-friendly formatting.
    printf("Result: %g %c %g = %g\n", num1, operator, num2, result);

    return EXIT_SUCCESS;
}

// --- Function Implementations ---

/**
 * @brief Prints the usage instructions for the program and exits.
 *
 * @param prog_name The name of the program executable.
 */
static void print_usage_and_exit(const char *prog_name)
{
    fprintf(stderr, "Usage: %s <number1> <operator> <number2>\n", prog_name);
    fprintf(stderr, "  A simple command-line calculator.\n\n");
    fprintf(stderr, "Arguments:\n");
    fprintf(stderr, "  number1    The first number (integer or floating-point).\n");
    fprintf(stderr, "  operator   One of the supported arithmetic operators: +, -, *, /.\n");
    fprintf(stderr, "  number2    The second number (integer or floating-point).\n\n");
    fprintf(stderr, "Example:\n");
    fprintf(stderr, "  %s 10.5 \"*\" 2\n", prog_name);
    exit(EXIT_FAILURE);
}

/**
 * @brief Parses a string to a double with robust error checking.
 *
 * This function attempts to convert a string to a double value. It handles
 * various error conditions, such as invalid number formats or values that
 * are out of the representable range for a double.
 *
 * @param str The string to convert.
 * @return The parsed double value. Exits the program on failure.
 */
static double parse_double(const char *str)
{
    char *endptr;
    errno = 0; // Reset errno before the call.

    const double value = strtod(str, &endptr);

    // Check for various conversion errors.
    if (endptr == str)
    {
        fprintf(stderr, "Error: Invalid number provided. '%s' is not a valid number.\n", str);
        exit(EXIT_FAILURE);
    }
    if (*endptr != '\0')
    {
        fprintf(stderr, "Error: Trailing characters found after number: '%s'\n", endptr);
        exit(EXIT_FAILURE);
    }
    if (errno == ERANGE)
    {
        fprintf(stderr, "Error: Number '%s' is out of the representable range.\n", str);
        exit(EXIT_FAILURE);
    }

    return value;
}

/**
 * @brief Performs the calculation based on the provided operator.
 *
 * @param num1 The first operand.
 * @param op The operator character (+, -, *, /).
 * @param num2 The second operand.
 * @return The result of the calculation. Exits the program on error (e.g., division by zero).
 */
static double calculate(double num1, char op, double num2)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        if (num2 == 0)
        {
            fprintf(stderr, "Error: Division by zero is not allowed.\n");
            exit(EXIT_FAILURE);
        }
        return num1 / num2;
    default:
        fprintf(stderr, "Error: Invalid operator '%c'. Supported operators are +, -, *, /\n", op);
        exit(EXIT_FAILURE);
    }
}
