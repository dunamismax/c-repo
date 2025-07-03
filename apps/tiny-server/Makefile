CC = gcc
CFLAGS = -I../../libs/net_lib/include -I../../libs -Wall -Wextra -std=c99
LDFLAGS = -L../../libs/net_lib -lnet

SRCS = src/main.c
TARGET = tiny-server

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
