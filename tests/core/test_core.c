#include <stdio.h>
#include <stdlib.h>
#include "../../core/include/data_structures.h"
#include "../../core/include/utils.h"

void test_linked_list() {
    printf("Testing Linked List...\n");
    Node* head = NULL;
    int* val1 = malloc(sizeof(int));
    *val1 = 10;
    append_node(&head, val1);
    int* val2 = malloc(sizeof(int));
    *val2 = 20;
    append_node(&head, val2);

    if (head != NULL && *(int*)head->data == 10 && head->next != NULL && *(int*)head->next->data == 20) {
        printf("  PASS: append_node\n");
    } else {
        printf("  FAIL: append_node\n");
    }
    free_list(head, free);
    printf("Linked List test complete.\n\n");
}

void test_prime_checker() {
    printf("Testing Prime Checker...\n");
    if (is_prime(7)) {
        printf("  PASS: is_prime(7)\n");
    } else {
        printf("  FAIL: is_prime(7)\n");
    }
    if (!is_prime(10)) {
        printf("  PASS: !is_prime(10)\n");
    }
    else {
        printf("  FAIL: !is_prime(10)\n");
    }
    printf("Prime Checker test complete.\n\n");
}

int main() {
    test_linked_list();
    test_prime_checker();
    return 0;
}
