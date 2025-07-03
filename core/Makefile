CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c99

SRCS = src/data_structures.c src/utils.c
OBJS = $(SRCS:.c=.o)

TARGET = libcore.a

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)