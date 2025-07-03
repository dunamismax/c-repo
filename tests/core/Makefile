CC = gcc

TARGET = test_core
SRCS = test_utils.c
OBJS = $(SRCS:.c=.o)

LIB_CORE_DIR = ../../core

INCLUDES = -I$(LIB_CORE_DIR)/include
LDFLAGS = -L$(LIB_CORE_DIR)
LDLIBS = -lcore

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
