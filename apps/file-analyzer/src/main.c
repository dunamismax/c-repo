#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../core/include/data_structures.h"
#include "../../core/include/utils.h"

#define MAX_WORD_LEN 100

void free_string(void* data) {
    free(data);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    Node* head = NULL;
    char word[MAX_WORD_LEN];
    int word_len = 0;
    int char_count = 0;
    int line_count = 1;
    int word_count = 0;

    int c;
    while ((c = fgetc(file)) != EOF) {
        char_count++;
        if (c == '\n') {
            line_count++;
        }
        if (isspace(c) || ispunct(c)) {
            if (word_len > 0) {
                word[word_len] = '\0';
                char* new_word = strdup(word);
                append_node(&head, new_word);
                word_len = 0;
                word_count++;
            }
        }
 else {
            if (word_len < MAX_WORD_LEN - 1) {
                word[word_len++] = c;
            }
        }
    }

    if (word_len > 0) {
        word[word_len] = '\0';
        char* new_word = strdup(word);
        append_node(&head, new_word);
        word_count++;
    }

    printf("File Analysis for '%s':\n", argv[1]);
    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);

    if (is_prime(word_count)) {
        printf("The word count (%d) is a prime number.\n", word_count);
    } else {
        printf("The word count (%d) is not a prime number.\n", word_count);
    }

    free_list(head, free_string);
    fclose(file);

    return 0;
}
