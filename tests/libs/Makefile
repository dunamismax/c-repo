CC = gcc

TARGET = test_my_lib
SRCS = test_my_lib.c
OBJS = $(SRCS:.c=.o)

LIB_MATH_DIR = ../../libs/math_lib

INCLUDES = -I$(LIB_MATH_DIR)/include
LDFLAGS = -L$(LIB_MATH_DIR)
LDLIBS = -lmath_lib

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
