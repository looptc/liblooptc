CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LIBRARY = liblooptc.a
EXAMPLE = looptc_example
SRC = liblooptc.c $(EXAMPLE).c
OBJ = $(SRC:.c=.o)
HEADER = looptc.h

all: $(LIBRARY) $(EXAMPLE)

$(LIBRARY): liblooptc.o
	ar rcs $@ $^

$(EXAMPLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIBRARY) $(EXAMPLE)
