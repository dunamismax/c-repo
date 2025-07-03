CC = gcc
CFLAGS = -I../../libs/math_lib/include -Wall -Wextra -std=c99

BUILD_DIR = ../../build
OBJ_DIR = $(BUILD_DIR)/obj/test_libs
TEST_DIR = $(BUILD_DIR)/test
LIB_DIR = $(BUILD_DIR)/lib

SRCS = test_my_lib.c
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

TARGET = $(TEST_DIR)/test_my_lib

.PHONY: all clean

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TEST_DIR):
	mkdir -p $(TEST_DIR)

$(TARGET): $(OBJS) $(TEST_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) -lmath

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rmdir $(OBJ_DIR) 2>/dev/null || true
	rmdir $(TEST_DIR) 2>/dev/null || true
