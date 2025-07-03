#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "../../libs/net_lib/include/net_lib.h"

void test_socket_creation()
{
    printf("Testing Socket Creation...\n");
    int sockfd = socket_create();
    assert(sockfd > 0);
    printf("  PASS: socket_create()\n");
    close(sockfd);
}

void test_socket_bind()
{
    printf("Testing Socket Bind...\n");
    int sockfd = socket_create();
    assert(socket_bind(sockfd, 8081) == 0);
    printf("  PASS: socket_bind()\n");
    close(sockfd);
}

void test_socket_listen()
{
    printf("Testing Socket Listen...\n");
    int sockfd = socket_create();
    assert(socket_bind(sockfd, 8082) == 0);
    assert(socket_listen(sockfd, 5) == 0);
    printf("  PASS: socket_listen()\n");
    close(sockfd);
}

int main()
{
    test_socket_creation();
    test_socket_bind();
    test_socket_listen();
    return 0;
}
