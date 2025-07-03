CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c99

SRCS = src/net_lib.c
OBJS = $(SRCS:.c=.o)

TARGET = libnet.a

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
