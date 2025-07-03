#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../core/include/data_structures.h"

#define FILENAME "contacts.csv"
#define MAX_LINE_LEN 256

// Structure to hold contact information
typedef struct {
    char* name;
    char* phone;
    char* email;
} Contact;

// Function to free a Contact struct
void free_contact(void* data) {
    Contact* contact = (Contact*)data;
    free(contact->name);
    free(contact->phone);
    free(contact->email);
    free(contact);
}

// Function to load contacts from the CSV file into a linked list
void load_contacts(Node** head) {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        // If the file doesn't exist, it's not an error, it just means no contacts yet.
        return;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        Contact* contact = (Contact*)malloc(sizeof(Contact));
        char* token = strtok(line, ",");
        contact->name = strdup(token);
        token = strtok(NULL, ",");
        contact->phone = strdup(token);
        token = strtok(NULL, ",");
        contact->email = strdup(token);

        append_node(head, contact);
    }

    fclose(file);
}

// Function to save all contacts from the linked list to the CSV file
void save_contacts(Node* head) {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    Node* current = head;
    while (current != NULL) {
        Contact* contact = (Contact*)current->data;
        fprintf(file, "%s,%s,%s\n", contact->name, contact->phone, contact->email);
        current = current->next;
    }

    fclose(file);
}

// Function to add a new contact
void add_contact(Node** head, const char* name, const char* phone, const char* email) {
    Contact* contact = (Contact*)malloc(sizeof(Contact));
    contact->name = strdup(name);
    contact->phone = strdup(phone);
    contact->email = strdup(email);
    append_node(head, contact);
    printf("Contact added successfully.\n");
}

// Function to list all contacts
void list_contacts(Node* head) {
    if (head == NULL) {
        printf("No contacts to display.\n");
        return;
    }

    printf("--- Contact List ---\n");
    Node* current = head;
    int count = 1;
    while (current != NULL) {
        Contact* contact = (Contact*)current->data;
        printf("%d. Name: %s, Phone: %s, Email: %s\n", count++, contact->name, contact->phone, contact->email);
        current = current->next;
    }
    printf("--------------------\n");
}

// Function to find a contact by name
void find_contact(Node* head, const char* name) {
    if (head == NULL) {
        printf("No contacts to search.\n");
        return;
    }

    printf("--- Search Results ---\n");
    Node* current = head;
    int found = 0;
    while (current != NULL) {
        Contact* contact = (Contact*)current->data;
        if (strstr(contact->name, name) != NULL) {
            printf("Name: %s, Phone: %s, Email: %s\n", contact->name, contact->phone, contact->email);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No contact found with that name.\n");
    }
    printf("----------------------\n");
}

int main(int argc, char* argv[]) {
    Node* head = NULL;
    load_contacts(&head);

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [options]\n", argv[0]);
        fprintf(stderr, "Commands: add, list, find\n");
        return 1;
    }

    const char* command = argv[1];

    if (strcmp(command, "add") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Usage: %s add <name> <phone> <email>\n", argv[0]);
            return 1;
        }
        add_contact(&head, argv[2], argv[3], argv[4]);
        save_contacts(head);
    } else if (strcmp(command, "list") == 0) {
        list_contacts(head);
    } else if (strcmp(command, "find") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s find <name>\n", argv[0]);
            return 1;
        }
        find_contact(head, argv[2]);
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }

    free_list(head, free_contact);

    return 0;
}