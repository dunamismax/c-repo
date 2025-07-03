#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "data_structures.h"

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

    int ch;
    int char_count = 0;
    int word_count = 0;
    int line_count = 0;
    bool in_word = false;

    // Demonstrate core/utils.h
    printf("Is 7 a prime number? %s\n", is_prime(7) ? "Yes" : "No");
    printf("Is 10 a prime number? %s\n", is_prime(10) ? "Yes" : "No");

    // Demonstrate core/data_structures.h
    Node* head = NULL;
    insert_at_beginning(&head, 30);
    insert_at_beginning(&head, 20);
    insert_at_beginning(&head, 10);
    printf("Linked List: ");
    print_list(head);

    // Analyze file content
    while ((ch = fgetc(file)) != EOF) {
        char_count++;
        if (ch == '\n') {
            line_count++;
        }
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            in_word = false;
        } else if (!in_word) {
            word_count++;
            in_word = true;
        }
    }

    // Adjust line count for files not ending with a newline
    if (char_count > 0 && ch != '\n') {
        line_count++;
    }

    printf("\nFile Analysis for '%s':\n", argv[1]);
    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);

    fclose(file);

    // Free linked list memory
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}