/*******************************************************************************
 * @file tiny-server.c
 * @brief A minimalist, multi-threaded HTTP server.
 *
 * This server listens on a specified port for incoming HTTP connections.
 * It handles each connection in a separate thread, serving a basic homepage
 * for the root path (/) and a 404 Not Found error for all other paths.
 * The server can be shut down gracefully by sending a SIGINT (Ctrl+C).
 *
 * @example
 *   ./tiny-server
 *   Then, open a web browser to http://localhost:8080
 *
 * @author Gemini
 * @date 2025-07-04
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

// --- Constants ---

#define PORT 8080
#define BUFFER_SIZE 2048
#define MAX_PENDING_CONNECTIONS 10
#define HTTP_RESPONSE_200 "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 145\r\nConnection: close\r\n\r\n<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><title>Tiny C Server</title><style>body{font-family:sans-serif;background-color:#f0f0f0;}</style></head><body><h1>Welcome!</h1><p>This page is served by the tiny C server.</p></body></html>"
#define HTTP_RESPONSE_404 "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 9\r\nConnection: close\r\n\r\nNot Found"

// --- Global Variables ---

// Use volatile sig_atomic_t for variables accessed in signal handlers.
static volatile sig_atomic_t server_running = 1;
static int server_fd = -1;

// --- Function Prototypes ---

// Server setup
static int create_server_socket(int port);

// Connection handling
static void *handle_client(void *client_socket_ptr);

// Signal handling
static void signal_handler(int signum);

// --- Main Application Logic ---

int main(void) {
    // Set up the signal handler for graceful shutdown.
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    server_fd = create_server_socket(PORT);
    if (server_fd < 0) {
        fprintf(stderr, "Error: Failed to create server socket on port %d.\n", PORT);
        return EXIT_FAILURE;
    }

    printf("Server listening on http://localhost:%d. Press Ctrl+C to shut down.\n", PORT);

    while (server_running) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_socket < 0) {
            if (errno == EINTR && !server_running) {
                // Interrupted by signal handler, which is expected during shutdown.
                break;
            }
            perror("accept failed");
            continue;
        }

        // Allocate memory for the client socket descriptor to pass to the thread.
        int *client_socket_ptr = malloc(sizeof(int));
        if (client_socket_ptr == NULL) {
            perror("malloc for client socket failed");
            close(client_socket);
            continue;
        }
        *client_socket_ptr = client_socket;

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, client_socket_ptr) != 0) {
            perror("pthread_create failed");
            close(client_socket);
            free(client_socket_ptr);
        }
    }

    printf("\nServer shutting down gracefully.\n");
    if (server_fd != -1) {
        close(server_fd);
    }

    return EXIT_SUCCESS;
}

// --- Server Setup Implementation ---

/**
 * @brief Creates, binds, and listens on a server socket.
 * @param port The port number to listen on.
 * @return The file descriptor for the server socket, or -1 on failure.
 */
static int create_server_socket(int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        return -1;
    }

    // Allow reusing the port immediately after the server is restarted.
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        close(sockfd);
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("socket bind failed");
        close(sockfd);
        return -1;
    }

    if (listen(sockfd, MAX_PENDING_CONNECTIONS) < 0) {
        perror("socket listen failed");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

// --- Connection Handling Implementation ---

/**
 * @brief Handles a single client connection in a separate thread.
 * @param client_socket_ptr A pointer to the client's socket file descriptor.
 * @return NULL.
 */
static void *handle_client(void *client_socket_ptr) {
    // Detach the thread so its resources are automatically released on exit.
    pthread_detach(pthread_self());

    int client_socket = *(int *)client_socket_ptr;
    free(client_socket_ptr); // Free the memory allocated in main.

    char buffer[BUFFER_SIZE] = {0};
    const char *response;

    long bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_read > 0) {
        printf("--- Received Request ---\n%s\n------------------------\n", buffer);

        // Very basic HTTP request parsing to find the path.
        char method[16], path[256];
        if (sscanf(buffer, "%15s %255s", method, path) == 2) {
            if (strcmp(path, "/") == 0) {
                response = HTTP_RESPONSE_200;
            } else {
                response = HTTP_RESPONSE_404;
            }
        } else {
            // Malformed request, respond with 404.
            response = HTTP_RESPONSE_404;
        }

        if (send(client_socket, response, strlen(response), 0) < 0) {
            perror("send failed");
        }

    } else if (bytes_read < 0) {
        perror("recv failed");
    }
    // If bytes_read is 0, the client closed the connection.

    printf("Response sent and connection closed for socket %d.\n", client_socket);
    close(client_socket);
    return NULL;
}

// --- Signal Handling Implementation ---

/**
 * @brief Handles SIGINT and SIGTERM to allow for graceful shutdown.
 * @param signum The signal number received.
 */
static void signal_handler(int signum) {
    (void)signum; // Unused parameter
    server_running = 0;
    // Break the main accept() loop by closing the socket here.
    if (server_fd != -1) {
        // Use shutdown to unblock accept() immediately.
        shutdown(server_fd, SHUT_RDWR);
        close(server_fd);
        server_fd = -1; // Prevent double closing
    }
}
