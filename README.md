# liblooptc

## Description
liblooptc is a C library designed for facilitating inter-thread communication using loopback connections. It provides functions to create loopback channels, read messages from these channels, and write messages to them. The library is intended for scenarios where multiple threads need to communicate with each other within the same process.

## Features
- Create loopback channels for inter-thread communication.
- Read messages from loopback channels.
- Write messages to loopback channels.

## Usage
To use liblooptc in your project, follow these steps:

1. Clone the repository:
```bash
git clone <repository-url>
```
2. Include the header file `looptc.h` in your source code:
```c
#include "looptc.h"
```
3. Compile your source code with `liblooptc.a`:
```bash
gcc -o your_program your_program.c -L/path/to/liblooptc -llooptc
```
4. Ensure that liblooptc.a is present in your library path.
5. Start using the provided functions in your code.

## Example
You have `looptc_example.c` in this repository... if you want a simple one:
```c
#include <stdio.h>
#include "looptc.h"

int main() {
    int channel = looptc_create_new_channel();
    if (channel < 0) {
        fprintf(stderr, "Error creating channel\n");
        return EXIT_FAILURE;
    }

    char message[] = "Hello, world!";
    if (looptc_write_msg(channel, message, sizeof(message)) < 0) {
        fprintf(stderr, "Error writing message\n");
        return EXIT_FAILURE;
    }

    char buffer[256];
    if (looptc_read_msg(channel, buffer, sizeof(buffer)) < 0) {
        fprintf(stderr, "Error reading message\n");
        return EXIT_FAILURE;
    }

    printf("Received message: %s\n", buffer);

    return EXIT_SUCCESS;
}
```

## License

This project is licensed under the Public Domain.

## Author

liblooptc is developed by Abel Romero Pérez.
