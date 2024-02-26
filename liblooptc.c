#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define LOOPBACK_ADDR INADDR_LOOPBACK
#define LOOPBACK_PORT 0

// Function to create a new loopback channel
int looptc_create_new_channel() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return -1;
    }

    // Set up the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(LOOPBACK_ADDR); // Connect to 127.0.0.1
    server_addr.sin_port = htons(LOOPBACK_PORT); // Bind to the same port

    // Bind the socket to the loopback address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        return -2;
    }

    // Get the port chosen by the OS
    if (getsockname(sockfd, (struct sockaddr *)&server_addr, &addr_len) < 0) {
        return -3;
    }

    // Connect to the loopback address (not necessary for loopback)
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        return -4;
    }

    return sockfd;
}

// Function to read a message from the loopback channel
int looptc_read_msg(int sockfd, char *buffer, int buffer_size) {
    int bytes_received;

    // Receive message from the socket
    bytes_received = recv(sockfd, buffer, buffer_size, 0);
    if (bytes_received < 0) {
        return -5;
    }

    return bytes_received;
}

// Function to write a message to the loopback channel
int looptc_write_msg(int sockfd, const char *buffer, int buffer_size) {
    int bytes_sent;

    // Send message through the socket
    bytes_sent = send(sockfd, buffer, buffer_size, 0);
    if (bytes_sent < 0) {
        return -6;
    }

    return bytes_sent;
}
