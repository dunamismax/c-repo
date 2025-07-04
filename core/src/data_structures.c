#include "../include/data_structures.h"
#include <stdlib.h>
#include <stdio.h>

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
