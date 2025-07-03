#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Define the structure for a generic singly linked list node
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// A function pointer type for a function that frees the data stored in a node
typedef void (*free_data_func)(void*);

// Function prototypes for the linked list
Node* create_node(void* data);
void append_node(Node** head, void* data);
void free_list(Node* head, free_data_func free_func);

#endif /* DATA_STRUCTURES_H */