#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../core/include/data_structures.h"
#include "../../core/include/utils.h"

#define INITIAL_WORD_CAPACITY 16

/**
 * @brief Frees memory allocated for a string.
 * @param data A pointer to the string data to be freed.
 */
void free_string(void *data)
{
    free(data);
}

/**
 * @brief Represents the statistics of the file.
 */
typedef struct
{
    int char_count;
    int word_count;
    int line_count;
} FileStats;

/**
 * @brief Processes the given file and calculates statistics.
 *
 * @param file A pointer to the file to be analyzed.
 * @param stats A pointer to the FileStats struct to store the results.
 * @return A Node pointer to the head of the list of words.
 */
LinkedList *process_file(FILE *file, FileStats *stats)
{
    LinkedList *word_list = list_create();
    if (!word_list)
    {
        perror("Failed to create word list");
        return NULL;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        stats->line_count++;
        stats->char_count += strlen(line);

        char *token = strtok(line, " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL)
        {
            char *new_word = strdup(token);
            if (new_word)
            {
                list_append(word_list, new_word);
                stats->word_count++;
            }
            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }
    }

    return word_list;
}

/**
 * @brief Prints the analysis results to the console.
 *
 * @param filename The name of the analyzed file.
 * @param stats The statistics of the file.
 */
void print_analysis(const char *filename, const FileStats *stats)
{
    printf("File Analysis for '%s':\n", filename);
    printf("  Characters: %d\n", stats->char_count);
    printf("  Words: %d\n", stats->word_count);
    printf("  Lines: %d\n", stats->line_count);

    if (is_prime(stats->word_count))
    {
        printf("\nThe word count (%d) is a prime number!\n", stats->word_count);
    }
    else
    {
        printf("\nThe word count (%d) is not a prime number.\n", stats->word_count);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    FileStats stats = {0, 0, 1}; // Initialize stats
    if (feof(file))
        stats.line_count = 0; // Handle empty file case
    fseek(file, 0, SEEK_SET);

    LinkedList *word_list = process_file(file, &stats);

    print_analysis(argv[1], &stats);

    list_destroy(word_list, free_string);
    fclose(file);

    return EXIT_SUCCESS;
}
