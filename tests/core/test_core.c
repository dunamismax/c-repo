#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../core/include/data_structures.h"
#include "../../core/include/utils.h"

void test_linked_list()
{
    printf("Testing LinkedList...\n");

    // 1. Create a new list
    LinkedList *list = list_create();
    assert(list != NULL);
    assert(list->head == NULL);
    assert(list->size == 0);
    printf("  PASS: list_create()\n");

    // 2. Append data
    int *val1 = malloc(sizeof(int));
    *val1 = 10;
    int *val2 = malloc(sizeof(int));
    *val2 = 20;
    list_append(list, val1);
    list_append(list, val2);
    assert(list->size == 2);
    assert(*(int *)list_get(list, 0) == 10);
    assert(*(int *)list_get(list, 1) == 20);
    printf("  PASS: list_append() and list_get()\n");

    // 3. Prepend data
    int *val0 = malloc(sizeof(int));
    *val0 = 5;
    list_prepend(list, val0);
    assert(list->size == 3);
    assert(*(int *)list_get(list, 0) == 5);
    assert(*(int *)list_get(list, 1) == 10);
    printf("  PASS: list_prepend()\n");

    // 4. Remove data
    list_remove(list, 1, free); // Remove the middle element (10)
    assert(list->size == 2);
    assert(*(int *)list_get(list, 0) == 5);
    assert(*(int *)list_get(list, 1) == 20);
    printf("  PASS: list_remove()\n");

    // 5. Destroy the list
    list_destroy(list, free);
    printf("LinkedList test complete.\n\n");
}

void test_prime_checker()
{
    printf("Testing Prime Checker...\n");
    assert(is_prime(2) == 1);
    assert(is_prime(3) == 1);
    assert(is_prime(5) == 1);
    assert(is_prime(7) == 1);
    assert(is_prime(11) == 1);
    assert(is_prime(1) == 0);
    assert(is_prime(4) == 0);
    assert(is_prime(9) == 0);
    assert(is_prime(15) == 0);
    printf("  PASS: is_prime() with various inputs\n");
    printf("Prime Checker test complete.\n\n");
}

int main()
{
    test_linked_list();
    test_prime_checker();
    return 0;
}
