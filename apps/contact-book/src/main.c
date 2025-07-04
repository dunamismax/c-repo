#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    Node *tail;  /**< Pointer to the tail of the list. */
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

// Function prototype for the prime number checker
int is_prime(int n);

// Function prototype for case-insensitive string comparison
char *str_case_str(const char *haystack, const char *needle);

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

// Function to check if a number is prime
int is_prime(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// Case-insensitive string comparison
char *str_case_str(const char *haystack, const char *needle)
{
    if (!needle || !*needle)
    {
        return (char *)haystack;
    }

    while (*haystack)
    {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n)))
        {
            h++;
            n++;
        }
        if (!*n)
        {
            return (char *)haystack;
        }
        haystack++;
    }
    return NULL;
}

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
    if (!contact) return;
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

    if (!contact->name || !contact->phone || !contact->email) {
        free_contact(contact);
        perror("Failed to allocate memory for contact details");
        return;
    }

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
        if (str_case_str(contact->name, name) != NULL)
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
