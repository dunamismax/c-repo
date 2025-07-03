CC = gcc
CFLAGS = -I../../libs/math_lib/include -Wall -Wextra -std=c99
LDFLAGS = -L../../libs/math_lib -lmath

SRCS = test_my_lib.c
TARGET = test_my_lib

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)