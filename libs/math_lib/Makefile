CC = gcc
AR = ar

TARGET = libmath_lib.a
SRCS = src/math_lib.c
OBJS = $(SRCS:.c=.o)
INCLUDES = -Iinclude

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
