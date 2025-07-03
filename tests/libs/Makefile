CC = gcc
CFLAGS = -I../../libs/net_lib/include -Wall -Wextra -std=c99

BUILD_DIR = ../../build
OBJ_DIR = $(BUILD_DIR)/obj/test_net_lib
BIN_DIR = $(BUILD_DIR)/test
LIB_DIR = $(BUILD_DIR)/lib

SRCS = test_net_lib.c
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

TARGET = $(BIN_DIR)/test_net_lib

.PHONY: all clean

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIB_DIR) -lnet

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rmdir $(OBJ_DIR) 2>/dev/null || true
	rmdir $(BIN_DIR) 2>/dev/null || true