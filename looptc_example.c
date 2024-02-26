#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "looptc.h"

int main() {
    // Create two channels for read and write for each thread
    int parent_thread1, thread1_parent, parent_thread2, thread2_parent, thread1_thread2, thread2_thread1;

    // Create channels and check for errors
    parent_thread1 = looptc_create_new_channel();
    if (parent_thread1 < 0) {
        fprintf(stderr, "Error creating channel for parent_thread1\n");
        exit(EXIT_FAILURE);
    }
    parent_thread2 = looptc_create_new_channel();
    if (parent_thread2 < 0) {
        fprintf(stderr, "Error creating channel for parent_thread2\n");
        exit(EXIT_FAILURE);
    }
    thread1_parent = looptc_create_new_channel();
    if (thread1_parent < 0) {
        fprintf(stderr, "Error creating channel for thread1_parent\n");
        exit(EXIT_FAILURE);
    }
    thread2_parent = looptc_create_new_channel();
    if (thread2_parent < 0) {
        fprintf(stderr, "Error creating channel for thread2_parent\n");
        exit(EXIT_FAILURE);
    }
    thread1_thread2 = looptc_create_new_channel();
    if (thread1_thread2 < 0) {
        fprintf(stderr, "Error creating channel for thread1_thread2\n");
        exit(EXIT_FAILURE);
    }
    thread2_thread1 = looptc_create_new_channel();
    if (thread2_thread1 < 0) {
        fprintf(stderr, "Error creating channel for thread2_thread1\n");
        exit(EXIT_FAILURE);
    }

    // Fork first child (Thread 1)
    pid_t pid_thread1 = fork();
    if (pid_thread1 == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid_thread1 == 0) { // Child process (Thread 1)
        // Read message from parent
        char buffer[256];
        looptc_read_msg(parent_thread1, buffer, sizeof(buffer));
        printf("Thread 1 received from parent: %s\n", buffer);

        // Send message to parent
        char msg_to_parent[] = "Message from Thread 1 to parent\0";
        looptc_write_msg(thread1_parent, msg_to_parent, sizeof(msg_to_parent));

        // Send message to Thread 2
        char msg_to_thread2[] = "Message from Thread 1 to Thread 2\0";
        looptc_write_msg(thread1_thread2, msg_to_thread2, sizeof(msg_to_thread2));

        looptc_read_msg(thread2_thread1, buffer, sizeof(buffer));
        printf("Thread 1 received from Thread 2: %s\n", buffer);

        exit(EXIT_SUCCESS);
    }

    // Fork second child (Thread 2)
    pid_t pid_thread2 = fork();
    if (pid_thread2 == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid_thread2 == 0) { // Child process (Thread 2)


        // Read message from parent
        char buffer[256];
        looptc_read_msg(parent_thread2, buffer, sizeof(buffer));
        printf("Thread 2 received from parent: %s\n", buffer);

        looptc_read_msg(thread1_thread2, buffer, sizeof(buffer));
        printf("Thread 2 received from Thread 1: %s\n", buffer);

        // Send message to parent
        char msg_to_parent[] = "Message from Thread 2 to parent\0";
        looptc_write_msg(thread2_parent, msg_to_parent, sizeof(msg_to_parent));

        // Send message to parent
        char msg_to_thread1[] = "Message from Thread 2 to Thread1\0";
        looptc_write_msg(thread2_thread1, msg_to_thread1, sizeof(msg_to_parent));

        exit(EXIT_SUCCESS);
    }

    // Parent process

    // Send message to Thread 1
    char msg_to_thread1[] = "Message from Parent to Thread 1\0";
    looptc_write_msg(parent_thread1, msg_to_thread1, sizeof(msg_to_thread1));

    // Send message to Thread 2
    char msg_to_thread2[] = "Message from Parent to Thread 2\0";
    looptc_write_msg(parent_thread2, msg_to_thread2, sizeof(msg_to_thread2));

    // Read message from Thread 1
    char buffer_thread1[256];
    looptc_read_msg(thread1_parent, buffer_thread1, sizeof(buffer_thread1));
    printf("Parent received from Thread 1: %s\n", buffer_thread1);

    // Read message from Thread 2
    char buffer_thread2[256];
    looptc_read_msg(thread2_parent, buffer_thread2, sizeof(buffer_thread2));
    printf("Parent received from Thread 2: %s\n", buffer_thread2);

    wait(NULL);
    wait(NULL);

    return 0;
}
