#include "../include/data_structures.h"
#include <stdlib.h>

// Function to create a new node with generic data
Node* create_node(void* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

// Function to append a node to the end of the list
void append_node(Node** head, void* data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

// Function to free the entire list, including the data in each node
void free_list(Node* head, free_data_func free_func) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        if (free_func != NULL) {
            free_func(tmp->data); // Free the data using the provided function
        }
        free(tmp); // Free the node itself
    }
}
