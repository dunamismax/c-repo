#ifndef NET_LIB_H
#define NET_LIB_H

#include <sys/socket.h>
#include <netinet/in.h>

int socket_create();
int socket_bind(int sockfd, int port);
int socket_listen(int sockfd, int backlog);
int create_server_socket(int port);

#endif /* NET_LIB_H */
