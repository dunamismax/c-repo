CC = gcc
CFLAGS = -I../../core/include -Wall -Wextra -std=c99
LDFLAGS = -L../../core -lcore

SRCS = src/main.c
TARGET = file-analyzer

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)