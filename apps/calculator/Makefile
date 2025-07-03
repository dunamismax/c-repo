CC = gcc
CFLAGS = -I../../libs/math_lib/include -Wall -Wextra -std=c99

BUILD_DIR = ../../build
OBJ_DIR = $(BUILD_DIR)/obj/calculator
BIN_DIR = $(BUILD_DIR)/bin
LIB_DIR = $(BUILD_DIR)/lib

SRCS = src/main.c
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

TARGET = $(BIN_DIR)/calculator

.PHONY: all clean

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) -lmath

$(OBJ_DIR)/%.o: src/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rmdir $(OBJ_DIR) 2>/dev/null || true
	rmdir $(BIN_DIR) 2>/dev/null || true
