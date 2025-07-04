# Common Makefile settings to be included in other Makefiles

# Compiler and flags
CC = gcc
# Add -arch arm64 for macOS on Apple Silicon
ifeq ($(shell uname -s), Darwin)
    ARCH_FLAGS = -arch arm64
else
    ARCH_FLAGS =
endif
CFLAGS = -Wall -Wextra -std=c99 $(ARCH_FLAGS)

# Project structure
ROOT_DIR = $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))/../..
BUILD_DIR = $(ROOT_DIR)/build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
LIB_DIR = $(BUILD_DIR)/lib
TEST_DIR = $(BUILD_DIR)/test

# Common directories
CORE_INC_DIR = $(ROOT_DIR)/core/include
MATH_LIB_INC_DIR = $(ROOT_DIR)/libs/math_lib/include
NET_LIB_INC_DIR = $(ROOT_DIR)/libs/net_lib/include

# Common libraries
CORE_LIB = $(LIB_DIR)/libcore.a
MATH_LIB = $(LIB_DIR)/libmath.a
NET_LIB = $(LIB_DIR)/libnet.a

# Phony targets
.PHONY: all clean

# Common rules
# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(TEST_DIR):
	mkdir -p $(TEST_DIR)

# Clean rule
distclean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR) $(TEST_DIR)
