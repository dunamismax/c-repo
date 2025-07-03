#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
void insert_at_beginning(Node** head, int data);
void print_list(Node* head);

#endif // DATA_STRUCTURES_H
