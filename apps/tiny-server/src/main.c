#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include "net_lib.h"

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CONNECTIONS 10

volatile sig_atomic_t server_fd = -1;

void *handle_client(void *client_socket_ptr);
void signal_handler(int signum);

int main(void)
{
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    signal(SIGINT, signal_handler);

    server_fd = create_server_socket(PORT);
    if (server_fd < 0)
    {
        fprintf(stderr, "Failed to create server socket.\n");
        return 1;
    }
    printf("Server listening on port %d. Press Ctrl+C to exit.\n", PORT);

    while (1)
    {
        int *new_socket = malloc(sizeof(int));
        if (!new_socket)
        {
            perror("malloc failed");
            continue;
        }

        *new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (*new_socket < 0)
        {
            if (errno == EINTR)
            {
                break;
            }
            perror("accept");
            free(new_socket);
            continue;
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, new_socket) != 0)
        {
            perror("pthread_create failed");
            close(*new_socket);
            free(new_socket);
        }
    }

    printf("Server shutting down.\n");
    if (server_fd != -1)
    {
        close(server_fd);
    }
    return 0;
}

void *handle_client(void *client_socket_ptr)
{
    int client_socket = *(int *)client_socket_ptr;
    free(client_socket_ptr);

    char buffer[BUFFER_SIZE] = {0};
    const char *response_404 = "HTTP/1.1 404 Not Found\r\n"
                               "Content-Type: text/plain\r\n"
                               "Content-Length: 9\r\n"
                               "\r\n"
                               "Not Found";
    const char *response_200 = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html\r\n"
                           "Content-Length: 118\r\n"
                           "\r\n"
                           "<!DOCTYPE html><html><head><title>C-Repo</title></head><body><h1>Welcome</h1><p>to the tiny C server!</p></body></html>";

    long bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0)
    {
        printf("--- Received Request ---\n%s\n------------------------\n", buffer);

        // Simple request parsing
        char method[16], path[256];
        sscanf(buffer, "%s %s", method, path);

        if (strcmp(path, "/") == 0)
        {
            if (write(client_socket, response_200, strlen(response_200)) < 0)
            {
                perror("write");
            }
        }
        else
        {
            if (write(client_socket, response_404, strlen(response_404)) < 0)
            {
                perror("write");
            }
        }
    }
    else if (bytes_read < 0)
    {
        perror("read");
    }

    printf("Response sent and connection closed.\n");
    close(client_socket);
    pthread_detach(pthread_self());
    return NULL;
}

void signal_handler(int signum)
{
    printf("\nCaught signal %d. Shutting down server...\n", signum);
    if (server_fd != -1)
    {
        close(server_fd);
        server_fd = -1;
    }
}
