/*******************************************************************************
 * @file contact-book.c
 * @brief A command-line contact management application.
 *
 * This program allows users to manage a list of contacts (name, phone, email)
 * which is stored in a CSV file. It supports adding, listing, finding, and
 * deleting contacts.
 *
 * @example
 *   ./contact-book add "John Doe" "555-1234" "john.doe@email.com"
 *   ./contact-book list
 *   ./contact-book find "John"
 *   ./contact-book delete "John Doe"
 *
 * @author Gemini
 * @date 2025-07-04
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// --- Constants and Type Definitions ---

#define CSV_FILENAME "contacts.csv"
#define MAX_LINE_LENGTH 1024
#define CSV_DELIMITERS ","

/**
 * @brief Represents a single contact with name, phone, and email.
 */
typedef struct
{
    char *name;
    char *phone;
    char *email;
} Contact;

/**
 * @brief A generic singly linked list node.
 */
typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

/**
 * @brief A generic singly linked list.
 */
typedef struct
{
    Node *head;
    Node *tail;
    size_t size;
} LinkedList;

/**
 * @brief Enumeration for the different commands the application can perform.
 */
typedef enum
{
    CMD_ADD,
    CMD_LIST,
    CMD_FIND,
    CMD_DELETE,
    CMD_UNKNOWN
} Command;

// --- Function Prototypes ---

// Command Handling
static Command parse_command(const char *cmd_str);
static void print_usage(const char *prog_name);
static void handle_add(LinkedList *list, int argc, char *argv[]);
static void handle_list(const LinkedList *list);
static void handle_find(const LinkedList *list, int argc, char *argv[]);
static void handle_delete(LinkedList *list, int argc, char *argv[]);

// Contact Management
static Contact *contact_create(const char *name, const char *phone, const char *email);
static void contact_free(void *data);

// CSV I/O
static int load_contacts_from_csv(LinkedList *list, const char *filename);
static int save_contacts_to_csv(const LinkedList *list, const char *filename);
static char *get_csv_field(char **line, const char *delimiters);

// Linked List Operations
static LinkedList *list_create(void);
static void list_destroy(LinkedList *list, void (*free_func)(void *));
static int list_append(LinkedList *list, void *data);
static void *list_get(const LinkedList *list, size_t index);
static int list_remove(LinkedList *list, size_t index, void (*free_func)(void *));

// Utility
static char *str_trim(char *str);
static char *str_case_str(const char *haystack, const char *needle);

// --- Main Application Logic ---

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    LinkedList *contact_list = list_create();
    if (contact_list == NULL)
    {
        return EXIT_FAILURE; // Error message printed in list_create
    }

    if (load_contacts_from_csv(contact_list, CSV_FILENAME) != 0)
    {
        // This is not a fatal error, maybe the file doesn't exist yet.
        fprintf(stderr, "Info: Could not load contacts from '%s'. Starting with an empty list.\n", CSV_FILENAME);
    }

    const Command cmd = parse_command(argv[1]);
    int needs_save = 0;

    switch (cmd)
    {
    case CMD_ADD:
        handle_add(contact_list, argc, argv);
        needs_save = 1;
        break;
    case CMD_LIST:
        handle_list(contact_list);
        break;
    case CMD_FIND:
        handle_find(contact_list, argc, argv);
        break;
    case CMD_DELETE:
        handle_delete(contact_list, argc, argv);
        needs_save = 1;
        break;
    default:
        fprintf(stderr, "Error: Unknown command '%s'.\n", argv[1]);
        print_usage(argv[0]);
        break;
    }

    if (needs_save)
    {
        if (save_contacts_to_csv(contact_list, CSV_FILENAME) != 0)
        {
            fprintf(stderr, "Error: Failed to save changes to '%s'.\n", CSV_FILENAME);
        }
    }

    list_destroy(contact_list, contact_free);
    return EXIT_SUCCESS;
}

// --- Command Handling Implementation ---

static Command parse_command(const char *cmd_str)
{
    if (strcmp(cmd_str, "add") == 0)
        return CMD_ADD;
    if (strcmp(cmd_str, "list") == 0)
        return CMD_LIST;
    if (strcmp(cmd_str, "find") == 0)
        return CMD_FIND;
    if (strcmp(cmd_str, "delete") == 0)
        return CMD_DELETE;
    return CMD_UNKNOWN;
}

static void print_usage(const char *prog_name)
{
    fprintf(stderr, "Contact Book - A simple command-line contact manager.\n\n");
    fprintf(stderr, "Usage: %s <command> [options]\n\n", prog_name);
    fprintf(stderr, "Commands:\n");
    fprintf(stderr, "  add <name> <phone> <email>    Add a new contact.\n");
    fprintf(stderr, "  list                            List all contacts.\n");
    fprintf(stderr, "  find <term>                     Find contacts by case-insensitive name or email.\n");
    fprintf(stderr, "  delete <name>                   Delete a contact by exact name match.\n\n");
    fprintf(stderr, "Data is stored in '%s' in the current directory.\n", CSV_FILENAME);
}

static void handle_add(LinkedList *list, int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Error: Incorrect arguments for 'add' command.\n");
        print_usage(argv[0]);
        return;
    }
    Contact *contact = contact_create(argv[2], argv[3], argv[4]);
    if (contact == NULL)
    {
        return; // Error message printed in contact_create
    }
    if (list_append(list, contact) != 0)
    {
        fprintf(stderr, "Error: Could not append contact to the list.\n");
        contact_free(contact);
        return;
    }
    printf("Contact '%s' added successfully.\n", contact->name);
}

static void handle_list(const LinkedList *list)
{
    if (list->size == 0)
    {
        printf("The contact book is empty.\n");
        return;
    }
    printf("--- Contact List (%zu contacts) ---\n", list->size);
    for (size_t i = 0; i < list->size; ++i)
    {
        Contact *c = (Contact *)list_get(list, i);
        printf("%2zu. Name:  %s\n", i + 1, c->name);
        printf("     Phone: %s\n", c->phone);
        printf("     Email: %s\n", c->email);
        if (i < list->size - 1)
        {
            printf("     ---\n");
        }
    }
    printf("------------------------------------\n");
}

static void handle_find(const LinkedList *list, int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Error: Incorrect arguments for 'find' command.\n");
        print_usage(argv[0]);
        return;
    }
    const char *search_term = argv[2];
    printf("--- Search Results for '%s' ---\n", search_term);
    int found_count = 0;
    for (size_t i = 0; i < list->size; ++i)
    {
        Contact *c = (Contact *)list_get(list, i);
        if (str_case_str(c->name, search_term) != NULL ||
            str_case_str(c->email, search_term) != NULL)
        {
            if (found_count > 0)
                printf("     ---\n");
            printf("  Name:  %s\n  Phone: %s\n  Email: %s\n", c->name, c->phone, c->email);
            found_count++;
        }
    }
    if (found_count == 0)
    {
        printf("No contacts found matching that term.\n");
    }
    printf("------------------------------------\n");
}

static void handle_delete(LinkedList *list, int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Error: Incorrect arguments for 'delete' command.\n");
        print_usage(argv[0]);
        return;
    }
    const char *name_to_delete = argv[2];
    int deleted_count = 0;
    for (size_t i = 0; i < list->size;)
    {
        Contact *c = (Contact *)list_get(list, i);
        // Use case-sensitive comparison for deletion to be precise.
        if (strcmp(c->name, name_to_delete) == 0)
        {
            list_remove(list, i, contact_free);
            deleted_count++;
            // Don't increment i, as the list has shifted.
        }
        else
        {
            i++;
        }
    }
    if (deleted_count > 0)
    {
        printf("Successfully deleted %d contact(s) named '%s'.\n", deleted_count, name_to_delete);
    }
    else
    {
        printf("No contact found with the exact name '%s'.\n", name_to_delete);
    }
}

// --- Contact Management Implementation ---

static Contact *contact_create(const char *name, const char *phone, const char *email)
{
    Contact *contact = (Contact *)malloc(sizeof(Contact));
    if (contact == NULL)
    {
        perror("Failed to allocate memory for contact");
        return NULL;
    }
    contact->name = strdup(name);
    contact->phone = strdup(phone);
    contact->email = strdup(email);

    if (contact->name == NULL || contact->phone == NULL || contact->email == NULL)
    {
        perror("Failed to allocate memory for contact details");
        contact_free(contact); // Cleans up partially allocated memory
        return NULL;
    }
    return contact;
}

static void contact_free(void *data)
{
    if (data == NULL)
        return;
    Contact *contact = (Contact *)data;
    free(contact->name);
    free(contact->phone);
    free(contact->email);
    free(contact);
}

// --- CSV I/O Implementation ---

static int load_contacts_from_csv(LinkedList *list, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        if (errno != ENOENT)
        {
            perror("Error opening contacts file for reading");
        }
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0; // Remove trailing newline

        char *line_ptr = line;
        char *name = get_csv_field(&line_ptr, CSV_DELIMITERS);
        char *phone = get_csv_field(&line_ptr, CSV_DELIMITERS);
        char *email = get_csv_field(&line_ptr, CSV_DELIMITERS);

        if (name && phone && email)
        {
            Contact *contact = contact_create(str_trim(name), str_trim(phone), str_trim(email));
            if (contact && list_append(list, contact) != 0)
            {
                contact_free(contact); // Clean up if append fails
            }
        }
    }
    fclose(file);
    return 0;
}

static int save_contacts_to_csv(const LinkedList *list, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening contacts file for writing");
        return -1;
    }
    for (size_t i = 0; i < list->size; ++i)
    {
        Contact *c = (Contact *)list_get(list, i);
        // Basic CSV writing; for robustness, would need to handle quotes/commas in fields
        fprintf(file, "%s,%s,%s\n", c->name, c->phone, c->email);
    }
    fclose(file);
    return 0;
}

static char *get_csv_field(char **line, const char *delimiters)
{
    char *token = strtok_r(*line, delimiters, line);
    return token;
}

// --- Linked List Implementation ---

static LinkedList *list_create(void)
{
    LinkedList *list = (LinkedList *)calloc(1, sizeof(LinkedList));
    if (list == NULL)
    {
        perror("Failed to allocate memory for LinkedList");
    }
    return list;
}

static void list_destroy(LinkedList *list, void (*free_func)(void *))
{
    if (list == NULL)
        return;
    Node *current = list->head;
    while (current != NULL)
    {
        Node *next_node = current->next;
        if (free_func != NULL && current->data != NULL)
        {
            free_func(current->data);
        }
        free(current);
        current = next_node;
    }
    free(list);
}

static int list_append(LinkedList *list, void *data)
{
    if (list == NULL)
        return -1;
    Node *new_node = (Node *)calloc(1, sizeof(Node));
    if (new_node == NULL)
    {
        perror("Failed to allocate memory for new node");
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

static void *list_get(const LinkedList *list, size_t index)
{
    if (list == NULL || index >= list->size)
        return NULL;
    Node *current = list->head;
    for (size_t i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->data;
}

static int list_remove(LinkedList *list, size_t index, void (*free_func)(void *))
{
    if (list == NULL || index >= list->size)
        return -1;
    Node *to_delete = NULL;
    if (index == 0)
    {
        to_delete = list->head;
        list->head = list->head->next;
        if (list->size == 1)
            list->tail = NULL;
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
    if (free_func != NULL && to_delete->data != NULL)
    {
        free_func(to_delete->data);
    }
    free(to_delete);
    list->size--;
    return 0;
}

// --- Utility Implementation ---

static char *str_trim(char *str)
{
    char *end;
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';
    return str;
}

static char *str_case_str(const char *haystack, const char *needle)
{
    if (!needle || !*needle)
        return (char *)haystack;
    for (; *haystack; ++haystack)
    {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n)))
        {
            h++;
            n++;
        }
        if (*n == '\0')
            return (char *)haystack;
    }
    return NULL;
}
