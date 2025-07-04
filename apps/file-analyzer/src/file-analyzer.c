/*******************************************************************************
 *
 * @file file-analyzer.c
 * @brief A command-line utility to analyze text files.
 *
 * This program reads a specified text file and computes various statistics,
 * including the total number of characters, words, and lines. It also
 * provides a fun fact about the word count.
 *
 * @example
 *   ./file-analyzer my_document.txt
 *
 * @author Gemini
 * @date 2025-07-04
 *
 ******************************************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// --- Constants and Type Definitions ---

#define MAX_LINE_LENGTH 2048
#define WORD_DELIMITERS " \t\n\r.,;:!?\"'()[]{}<>&/"

/**
 * @brief Holds the statistics for an analyzed file.
 */
typedef struct {
    long long char_count;
    long long word_count;
    long long line_count;
} FileStats;

// --- Function Prototypes ---

// File Processing
static int analyze_file(const char *filename, FileStats *stats);
static void process_line(char *line, FileStats *stats);

// Analysis and Output
static void print_analysis(const char *filename, const FileStats *stats);
static bool is_prime(long long n);

// --- Main Application Logic ---

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        fprintf(stderr, "Analyzes a text file and reports statistics about it.\n");
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    FileStats stats = {0, 0, 0};

    if (analyze_file(filename, &stats) != 0) {
        // Error message is printed inside analyze_file
        return EXIT_FAILURE;
    }

    print_analysis(filename, &stats);

    return EXIT_SUCCESS;
}

// --- File Processing Implementation ---

/**
 * @brief Opens and processes a file, calculating statistics.
 * @param filename The path to the file.
 * @param stats A pointer to the FileStats struct to populate.
 * @return 0 on success, -1 on failure.
 */
static int analyze_file(const char *filename, FileStats *stats) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        stats->line_count++;
        stats->char_count += strlen(line);
        process_line(line, stats);
    }

    if (ferror(file)) {
        perror("Error reading from file");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

/**
 * @brief Processes a single line to count words.
 * @param line The line to process.
 * @param stats A pointer to the FileStats struct to update.
 */
static void process_line(char *line, FileStats *stats) {
    char *saveptr; // For strtok_r
    char *token = strtok_r(line, WORD_DELIMITERS, &saveptr);

    while (token != NULL) {
        stats->word_count++;
        token = strtok_r(NULL, WORD_DELIMITERS, &saveptr);
    }
}

// --- Analysis and Output Implementation ---

/**
 * @brief Prints the final analysis results to the console.
 * @param filename The name of the analyzed file.
 * @param stats The statistics of the file.
 */
static void print_analysis(const char *filename, const FileStats *stats) {
    printf("--- File Analysis for '%s' ---\n", filename);
    printf("  Characters: %-10lld\n", stats->char_count);
    printf("  Words:      %-10lld\n", stats->word_count);
    printf("  Lines:      %-10lld\n", stats->line_count);
    printf("------------------------------------\n");

    if (stats->word_count > 1) {
        if (is_prime(stats->word_count)) {
            printf("Fun Fact: The word count (%lld) is a prime number!\n", stats->word_count);
        } else {
            printf("Fun Fact: The word count (%lld) is not a prime number.\n", stats->word_count);
        }
    }
}

/**
 * @brief A simple and efficient check to determine if a number is prime.
 * @param n The number to check.
 * @return true if n is prime, false otherwise.
 */
static bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    // Check factors of the form 6k +/- 1 up to sqrt(n)
    for (long long i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}
