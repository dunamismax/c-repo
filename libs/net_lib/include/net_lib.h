#ifndef NET_LIB_H
#define NET_LIB_H

#include <sys/socket.h>
#include <netinet/in.h>

// Function to create a TCP socket, bind it to a port, and start listening
int create_server_socket(int port);

#endif /* NET_LIB_H */
