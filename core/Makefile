CC = gcc
AR = ar

TARGET = libcore.a
SRCS = src/utils.c src/data_structures.c
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
