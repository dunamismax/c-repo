#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h> // For size_t

/**
 * @brief A generic singly linked list node.
 */
typedef struct Node
{
    void *data;        /**< Pointer to the data of the node. */
    struct Node *next; /**< Pointer to the next node in the list. */
} Node;

/**
 * @brief A generic singly linked list.
 */
typedef struct
{
    Node *head;  /**< Pointer to the head of the list. */
    Node *tail;  /**< Pointer to the tail of the list. */
    size_t size; /**< The number of elements in the list. */
} LinkedList;

/**
 * @brief A function pointer type for a function that frees the data stored in a node.
 */
typedef void (*free_data_func)(void *data);

// LinkedList management functions
LinkedList *list_create();
void list_destroy(LinkedList *list, free_data_func free_func);

// Node manipulation functions
int list_append(LinkedList *list, void *data);
int list_prepend(LinkedList *list, void *data);
void *list_get(LinkedList *list, size_t index);
int list_remove(LinkedList *list, size_t index, free_data_func free_func);

// Function prototype for the prime number checker
int is_prime(int n);

// Function prototype for case-insensitive string comparison
char *str_case_str(const char *haystack, const char *needle);

/**
 * @brief Creates and initializes a new LinkedList.
 * @return A pointer to the newly created LinkedList, or NULL on failure.
 */
LinkedList *list_create()
{
    LinkedList *list = (LinkedList *)calloc(1, sizeof(LinkedList));
    if (list == NULL)
    {
        perror("Failed to create LinkedList");
    }
    return list;
}

/**
 * @brief Frees all memory associated with the LinkedList.
 * @param list The LinkedList to destroy.
 * @param free_func A function to free the data in each node.
 */
void list_destroy(LinkedList *list, free_data_func free_func)
{
    if (list == NULL)
        return;
    Node *current = list->head;
    Node *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        if (free_func != NULL)
        {
            free_func(current->data);
        }
        free(current);
        current = next_node;
    }
    free(list);
}

/**
 * @brief Appends a new node with the given data to the end of the list.
 * @param list The LinkedList to append to.
 * @param data The data to append.
 * @return 0 on success, -1 on failure.
 */
int list_append(LinkedList *list, void *data)
{
    if (list == NULL)
        return -1;
    Node *new_node = (Node *)calloc(1, sizeof(Node));
    if (new_node == NULL)
    {
        perror("Failed to create new node");
        return -1;
    }
    new_node->data = data;

    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return 0;
}

/**
 * @brief Prepends a new node with the given data to the start of the list.
 * @param list The LinkedList to prepend to.
 * @param data The data to prepend.
 * @return 0 on success, -1 on failure.
 */
int list_prepend(LinkedList *list, void *data)
{
    if (list == NULL)
        return -1;
    Node *new_node = (Node *)calloc(1, sizeof(Node));
    if (new_node == NULL)
    {
        perror("Failed to create new node");
        return -1;
    }
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    return 0;
}

/**
 * @brief Gets the data from a node at a specific index.
 * @param list The LinkedList to get data from.
 * @param index The index of the node.
 * @return A pointer to the data, or NULL if the index is out of bounds.
 */
void *list_get(LinkedList *list, size_t index)
{
    if (list == NULL || index >= list->size)
    {
        return NULL;
    }
    Node *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->data;
}

/**
 * @brief Removes a node from the list at a specific index.
 * @param list The LinkedList to remove from.
 * @param index The index of the node to remove.
 * @param free_func A function to free the data in the removed node.
 * @return 0 on success, -1 if the index is out of bounds.
 */
int list_remove(LinkedList *list, size_t index, free_data_func free_func)
{
    if (list == NULL || index >= list->size)
    {
        return -1;
    }

    Node *to_delete = NULL;
    if (index == 0)
    {
        to_delete = list->head;
        list->head = list->head->next;
        if (list->size == 1)
        {
            list->tail = NULL;
        }
    }
    else
    {
        Node *current = list->head;
        for (size_t i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        to_delete = current->next;
        current->next = to_delete->next;
        if (current->next == NULL)
        {
            list->tail = current;
        }
    }

    if (free_func != NULL)
    {
        free_func(to_delete->data);
    }
    free(to_delete);
    list->size--;

    return 0;
}

// Function to check if a number is prime
int is_prime(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// Case-insensitive string comparison
char *str_case_str(const char *haystack, const char *needle)
{
    if (!needle || !*needle)
    {
        return (char *)haystack;
    }

    while (*haystack)
    {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n)))
        {
            h++;
            n++;
        }
        if (!*n)
        {
            return (char *)haystack;
        }
        haystack++;
    }
    return NULL;
}

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
                if (list_append(word_list, new_word) != 0)
                {
                    free(new_word);
                    list_destroy(word_list, free_string);
                    return NULL;
                }
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

    if (word_list)
    {
        print_analysis(argv[1], &stats);
        list_destroy(word_list, free_string);
    }

    fclose(file);

    return EXIT_SUCCESS;
}