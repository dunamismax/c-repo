#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

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

#endif /* DATA_STRUCTURES_H */