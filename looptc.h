#ifndef LOOPTC_H
#define LOOPTC_H

#include <stddef.h>

// Error codes
#define LOOPTC_SOCKET_ERROR -1
#define LOOPTC_BIND_ERROR -2
#define LOOPTC_GETSOCKNAME_ERROR -3
#define LOOPTC_LISTEN_ERROR -4
#define LOOPTC_RECV_ERROR -5
#define LOOPTC_SEND_ERROR -6

// Function prototypes
int looptc_create_new_channel();
int looptc_read_msg(int sockfd, char *buffer, size_t buffer_size);
int looptc_write_msg(int sockfd, const char *buffer, size_t buffer_size);

#endif /* LOOPTC_H */
