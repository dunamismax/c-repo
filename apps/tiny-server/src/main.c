#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include "net_lib.h"

#define PORT 8080
#define BUFFER_SIZE 1024

volatile sig_atomic_t server_fd = -1;

void handle_client(int client_socket);
void signal_handler(int signum);

int main(void)
{
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    signal(SIGINT, signal_handler);
    signal(SIGCHLD, SIG_IGN);

    server_fd = create_server_socket(PORT);
    if (server_fd < 0)
    {
        fprintf(stderr, "Failed to create server socket.\n");
        return 1;
    }
    printf("Server listening on port %d. Press Ctrl+C to exit.\n", PORT);

    while (1)
    {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0)
        {
            if (errno == EINTR)
            {
                break;
            }
            perror("accept");
            continue;
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            close(new_socket);
        }
        else if (pid == 0)
        { // Child process
            close(server_fd);
            handle_client(new_socket);
            exit(EXIT_SUCCESS);
        }
        else
        { // Parent process
            close(new_socket);
        }
    }

    printf("Server shutting down.\n");
    if (server_fd != -1)
    {
        close(server_fd);
    }
    return 0;
}

void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE] = {0};
    const char *response = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/plain\r\n"
                           "Content-Length: 13\r\n"
                           "\r\n"
                           "Hello, World!";

    long bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0)
    {
        printf("--- Received Request ---\n%s\n------------------------\n", buffer);
    }
    else if (bytes_read < 0)
    {
        perror("read");
    }

    if (write(client_socket, response, strlen(response)) < 0)
    {
        perror("write");
    }

    printf("Response sent and connection closed.\n");
    close(client_socket);
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