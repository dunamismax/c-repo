CC = gcc

TARGET = calculator
SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

LIB_MATH_DIR = ../../libs/math_lib
LIB_CORE_DIR = ../../core

INCLUDES = -I$(LIB_MATH_DIR)/include -I$(LIB_CORE_DIR)/include
LDFLAGS = -L$(LIB_MATH_DIR) -L$(LIB_CORE_DIR)
LDLIBS = -lmath_lib -lcore

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
