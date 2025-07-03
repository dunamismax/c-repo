#include <stdio.h>
#include "utils.h"
#include "data_structures.h"

int main() {
    printf("Testing core/utils:\n");
    printf("Is 2 prime? %s\n", is_prime(2) ? "Yes" : "No");
    printf("Is 4 prime? %s\n", is_prime(4) ? "Yes" : "No");
    printf("Is 7 prime? %s\n", is_prime(7) ? "Yes" : "No");
    printf("Is 1 prime? %s\n", is_prime(1) ? "Yes" : "No");

    printf("\nTesting core/data_structures:\n");
    Node* head = NULL;
    insert_at_beginning(&head, 5);
    insert_at_beginning(&head, 10);
    insert_at_beginning(&head, 15);
    printf("List after insertions: ");
    print_list(head);

    // Free memory
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
