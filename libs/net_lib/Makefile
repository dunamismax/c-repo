CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c99

BUILD_DIR = ../../build
OBJ_DIR = $(BUILD_DIR)/obj/net_lib
LIB_DIR = $(BUILD_DIR)/lib

SRCS = src/net_lib.c
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

TARGET = $(LIB_DIR)/libnet.a

.PHONY: all clean

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(TARGET): $(OBJS) $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: src/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rmdir $(OBJ_DIR) 2>/dev/null || true
	rmdir $(LIB_DIR) 2>/dev/null || true