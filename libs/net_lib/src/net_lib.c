#include "../include/net_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Creates a new TCP socket.
 * @return The socket file descriptor, or -1 on failure.
 */
int socket_create() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket_create failed");
    }
    return sockfd;
}

/**
 * @brief Binds a socket to a specified port.
 * @param sockfd The socket file descriptor.
 * @param port The port to bind to.
 * @return 0 on success, -1 on failure.
 */
int socket_bind(int sockfd, int port) {
    struct sockaddr_in address;
    int opt = 1;

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("socket_bind failed");
        return -1;
    }
    return 0;
}

/**
 * @brief Puts a socket into listening mode.
 * @param sockfd The socket file descriptor.
 * @param backlog The maximum length of the queue of pending connections.
 * @return 0 on success, -1 on failure.
 */
int socket_listen(int sockfd, int backlog) {
    if (listen(sockfd, backlog) < 0) {
        perror("socket_listen failed");
        return -1;
    }
    return 0;
}

/**
 * @brief Creates a TCP server socket, binds it, and starts listening.
 * @param port The port to listen on.
 * @return The server socket file descriptor, or -1 on failure.
 */
int create_server_socket(int port) {
    int server_fd = socket_create();
    if (server_fd < 0) {
        return -1;
    }

    if (socket_bind(server_fd, port) < 0) {
        close(server_fd);
        return -1;
    }

    if (socket_listen(server_fd, 3) < 0) {
        close(server_fd);
        return -1;
    }

    return server_fd;
}
