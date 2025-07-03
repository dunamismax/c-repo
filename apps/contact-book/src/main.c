#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../core/include/data_structures.h"

#define FILENAME "contacts.csv"
#define MAX_LINE_LEN 256

typedef struct
{
    char *name;
    char *phone;
    char *email;
} Contact;

void free_contact(void *data);
void load_contacts(LinkedList *list);
void save_contacts(LinkedList *list);
void add_contact(LinkedList *list, const char *name, const char *phone, const char *email);
void list_contacts(LinkedList *list);
void find_contact(LinkedList *list, const char *name);
void delete_contact(LinkedList *list, const char *name);
void print_usage(const char *prog_name);

void free_contact(void *data)
{
    Contact *contact = (Contact *)data;
    free(contact->name);
    free(contact->phone);
    free(contact->email);
    free(contact);
}

void load_contacts(LinkedList *list)
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
        return;

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0;

        Contact *contact = (Contact *)calloc(1, sizeof(Contact));
        if (!contact)
            continue;

        char *line_ptr = line;
        char *token = strsep(&line_ptr, ",");
        if (token)
            contact->name = strdup(token);

        token = strsep(&line_ptr, ",");
        if (token)
            contact->phone = strdup(token);

        token = strsep(&line_ptr, ",");
        if (token)
            contact->email = strdup(token);

        if (contact->name && contact->phone && contact->email)
        {
            list_append(list, contact);
        }
        else
        {
            free_contact(contact);
        }
    }
    fclose(file);
}

void save_contacts(LinkedList *list)
{
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        return;
    }
    for (Node *current = list->head; current != NULL; current = current->next)
    {
        Contact *contact = (Contact *)current->data;
        fprintf(file, "%s,%s,%s\n", contact->name, contact->phone, contact->email);
    }
    fclose(file);
}

void add_contact(LinkedList *list, const char *name, const char *phone, const char *email)
{
    Contact *contact = (Contact *)calloc(1, sizeof(Contact));
    if (!contact)
    {
        perror("Failed to allocate memory for contact");
        return;
    }
    contact->name = strdup(name);
    contact->phone = strdup(phone);
    contact->email = strdup(email);
    list_append(list, contact);
    printf("Contact '%s' added successfully.\n", name);
}

void list_contacts(LinkedList *list)
{
    if (list->size == 0)
    {
        printf("No contacts to display.\n");
        return;
    }
    printf("--- Contact List ---\n");
    int count = 1;
    for (Node *current = list->head; current != NULL; current = current->next)
    {
        Contact *contact = (Contact *)current->data;
        printf("%d. Name: %s, Phone: %s, Email: %s\n", count++, contact->name, contact->phone, contact->email);
    }
    printf("--------------------\n");
}

void find_contact(LinkedList *list, const char *name)
{
    printf("--- Search Results for '%s' ---\n", name);
    int found = 0;
    for (Node *current = list->head; current != NULL; current = current->next)
    {
        Contact *contact = (Contact *)current->data;
        if (strcasestr(contact->name, name) != NULL)
        {
            printf("  Name: %s, Phone: %s, Email: %s\n", contact->name, contact->phone, contact->email);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No contact found matching that name.\n");
    }
    printf("-------------------------------------\n");
}

void delete_contact(LinkedList *list, const char *name)
{
    int deleted = 0;
    for (size_t i = 0; i < list->size;)
    {
        Contact *contact = (Contact *)list_get(list, i);
        if (strcmp(contact->name, name) == 0)
        {
            list_remove(list, i, free_contact);
            printf("Contact '%s' deleted successfully.\n", name);
            deleted = 1;
        }
        else
        {
            i++;
        }
    }

    if (!deleted)
    {
        printf("No contact found with the exact name '%s'.\n", name);
    }
}

void print_usage(const char *prog_name)
{
    fprintf(stderr, "Usage: %s <command> [options]\n", prog_name);
    fprintf(stderr, "Commands:\n");
    fprintf(stderr, "  add <name> <phone> <email>  - Add a new contact\n");
    fprintf(stderr, "  list                          - List all contacts\n");
    fprintf(stderr, "  find <name>                   - Find contacts by name\n");
    fprintf(stderr, "  delete <name>                 - Delete a contact by exact name\n");
}

int main(int argc, char *argv[])
{
    LinkedList *contact_list = list_create();
    if (!contact_list)
    {
        return 1;
    }
    load_contacts(contact_list);

    if (argc < 2)
    {
        print_usage(argv[0]);
        list_destroy(contact_list, free_contact);
        return 1;
    }

    const char *command = argv[1];

    if (strcmp(command, "add") == 0)
    {
        if (argc != 5)
        {
            fprintf(stderr, "Error: Incorrect arguments for add.\n");
            print_usage(argv[0]);
        }
        else
        {
            add_contact(contact_list, argv[2], argv[3], argv[4]);
            save_contacts(contact_list);
        }
    }
    else if (strcmp(command, "list") == 0)
    {
        list_contacts(contact_list);
    }
    else if (strcmp(command, "find") == 0)
    {
        if (argc != 3)
        {
            fprintf(stderr, "Error: Incorrect arguments for find.\n");
            print_usage(argv[0]);
        }
        else
        {
            find_contact(contact_list, argv[2]);
        }
    }
    else if (strcmp(command, "delete") == 0)
    {
        if (argc != 3)
        {
            fprintf(stderr, "Error: Incorrect arguments for delete.\n");
            print_usage(argv[0]);
        }
        else
        {
            delete_contact(contact_list, argv[2]);
            save_contacts(contact_list);
        }
    }
    else
    {
        fprintf(stderr, "Unknown command: %s\n", command);
        print_usage(argv[0]);
    }

    list_destroy(contact_list, free_contact);

    return 0;
}
