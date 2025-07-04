/*******************************************************************************
 * @file tiny-server.c
 * @brief A robust, minimalist, multi-threaded HTTP server.
 *
 * This server listens on a specified port for incoming HTTP connections.
 * It handles each connection in a separate thread, serving a dynamic homepage
 * for the root path (/) and a 404 Not Found error for all other paths.
 * The server is designed to be robust, with proper error handling, dynamic
 * response generation, and a graceful shutdown mechanism via SIGINT (Ctrl+C).
 *
 * @example
 *   # Compile the server
 *   gcc -Wall -Wextra -pthread tiny-server.c -o tiny-server
 *
 *   # Run the server
 *   ./tiny-server
 *
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
#include <arpa/inet.h> // For inet_ntop
#include <signal.h>
#include <pthread.h>
#include <errno.h>

// --- Constants ---

#define PORT 8080
#define BUFFER_SIZE 4096 // Increased buffer size for response generation
#define MAX_PENDING_CONNECTIONS 10

// --- Client Thread Data ---
// A struct to pass both the socket and address info to the thread.
typedef struct
{
    int socket;
    char ip_str[INET_ADDRSTRLEN];
} client_info_t;

// --- Global Variables ---

static volatile sig_atomic_t server_running = 1;
static int server_fd = -1;

// --- Function Prototypes ---
static int create_server_socket(int port);
static void *handle_client(void *arg);
static void signal_handler(int signum);
static void send_response(int client_socket, const char *status_code, const char *content_type, const char *body);

// --- Main Application Logic ---

int main(void)
{
    // Block SIGPIPE: If a client closes a connection while we're writing to it,
    // we get a SIGPIPE signal, which terminates the process. It's better to
    // handle the error from the send() call directly.
    signal(SIGPIPE, SIG_IGN);

    // Set up the signal handler for graceful shutdown.
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    server_fd = create_server_socket(PORT);
    if (server_fd < 0)
    {
        return EXIT_FAILURE;
    }

    printf("Server listening on http://localhost:%d. Press Ctrl+C to shut down.\n", PORT);

    while (server_running)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_socket < 0)
        {
            if (!server_running)
            { // Expected interruption after Ctrl+C
                break;
            }
            perror("accept failed");
            continue;
        }

        // Create a struct to hold client info
        client_info_t *client_info = malloc(sizeof(client_info_t));
        if (client_info == NULL)
        {
            perror("malloc for client_info failed");
            close(client_socket);
            continue;
        }
        client_info->socket = client_socket;
        // Log the client's IP address
        inet_ntop(AF_INET, &client_addr.sin_addr, client_info->ip_str, INET_ADDRSTRLEN);

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, client_info) != 0)
        {
            perror("pthread_create failed");
            close(client_socket);
            free(client_info);
        }
        else
        {
            pthread_detach(thread_id);
        }
    }

    printf("\nServer shutting down gracefully.\n");
    // The signal handler closes the socket, so no extra cleanup is needed here.
    return EXIT_SUCCESS;
}

// --- Server Setup Implementation ---

static int create_server_socket(int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket creation failed");
        return -1;
    }

    // Allow reusing the port immediately after the server is restarted.
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed");
        close(sockfd);
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all available interfaces
    server_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("socket bind failed");
        close(sockfd);
        return -1;
    }

    if (listen(sockfd, MAX_PENDING_CONNECTIONS) < 0)
    {
        perror("socket listen failed");
        close(sockfd);
        return -1;
    }
    return sockfd;
}

// --- Connection Handling Implementation ---

static void *handle_client(void *arg)
{
    client_info_t *info = (client_info_t *)arg;
    int client_socket = info->socket;

    printf("Accepted connection from %s\n", info->ip_str);

    char request_buffer[BUFFER_SIZE];
    memset(request_buffer, 0, BUFFER_SIZE);

    long bytes_read = recv(client_socket, request_buffer, BUFFER_SIZE - 1, 0);

    if (bytes_read > 0)
    {
        char method[16], path[256];
        // Basic parsing of the HTTP request line
        if (sscanf(request_buffer, "%15s %255s", method, path) == 2)
        {
            printf("Request from %s: %s %s\n", info->ip_str, method, path);

            if (strcmp(method, "GET") == 0)
            {
                if (strcmp(path, "/") == 0)
                {
                    const char *body = "<!DOCTYPE html>"
                                       "<html lang=\"en\">"
                                       "<head><meta charset=\"UTF-8\"><title>Tiny C Server</title>"
                                       "<style>body{font-family:sans-serif;background-color:#f0f0f0;text-align:center;} h1{color:#333;}</style>"
                                       "</head><body>"
                                       "<h1>Welcome!</h1><p>This page is served by a tiny C server.</p>"
                                       "</body></html>";
                    send_response(client_socket, "200 OK", "text/html", body);
                }
                else
                {
                    send_response(client_socket, "404 Not Found", "text/plain", "Not Found");
                }
            }
            else
            {
                // Method not supported
                send_response(client_socket, "405 Method Not Allowed", "text/plain", "Method Not Allowed");
            }
        }
        else
        {
            // Malformed request
            send_response(client_socket, "400 Bad Request", "text/plain", "Bad Request");
        }
    }
    else if (bytes_read < 0)
    {
        perror("recv failed");
    }
    // If bytes_read is 0, client closed the connection.

    printf("Closing connection for %s\n", info->ip_str);
    close(client_socket);
    free(info); // Free the memory allocated in main
    return NULL;
}

/**
 * @brief Constructs and sends a full HTTP response.
 * @param client_socket The socket to send the response to.
 * @param status_code The HTTP status (e.g., "200 OK").
 * @param content_type The MIME type of the body (e.g., "text/html").
 * @param body The content to send as the response body.
 */
static void send_response(int client_socket, const char *status_code, const char *content_type, const char *body)
{
    char response_buffer[BUFFER_SIZE];
    size_t body_len = strlen(body);

    int response_len = snprintf(response_buffer, BUFFER_SIZE,
                                "HTTP/1.1 %s\r\n"
                                "Content-Type: %s\r\n"
                                "Content-Length: %zu\r\n"
                                "Connection: close\r\n\r\n"
                                "%s",
                                status_code, content_type, body_len, body);

    if (response_len < 0)
    {
        // This should be rare, but it's good practice to check.
        fprintf(stderr, "Error: snprintf failed when creating response.\n");
        return;
    }

    size_t len_to_send = (size_t)response_len;

    // If snprintf was truncated, it returns the number of bytes it *would* have
    // written. We must not send more than our buffer's actual size.
    if (len_to_send >= BUFFER_SIZE)
    {
        len_to_send = BUFFER_SIZE - 1; // The buffer is null-terminated.
    }

    // Send the response. It might take multiple calls if the buffer is large.
    ssize_t bytes_sent = send(client_socket, response_buffer, len_to_send, 0);
    if (bytes_sent < 0)
    {
        perror("send failed");
    }
    else if ((size_t)bytes_sent < len_to_send)
    {
        fprintf(stderr, "Warning: Only sent %zd of %zu bytes.\n", bytes_sent, len_to_send);
    }
}

// --- Signal Handling Implementation ---

/**
 * @brief Handles SIGINT/SIGTERM for graceful shutdown.
 * @param signum The signal number.
 */
static void signal_handler(int signum)
{
    (void)signum;
    server_running = 0;

    // The following is a pragmatic (but not strictly async-signal-safe) way
    // to unblock the main thread's blocking `accept()` call. In a real-world,
    // high-concurrency server, a "self-pipe trick" would be safer. For this
    // minimalist server, this is a reliable and simple solution.
    if (server_fd != -1)
    {
        shutdown(server_fd, SHUT_RD);
        close(server_fd);
        server_fd = -1; // Mark as closed
    }
}