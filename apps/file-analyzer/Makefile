# file-analyzer app Makefile
include ../../build/common.mk

# Override CFLAGS to include required library headers
CFLAGS += -I$(ROOT_DIR)/core/include

# Specifics for this target
SRCS = src/main.c
OBJS = $(patsubst src/%.c,obj/file-analyzer/%.o,$(SRCS))
TARGET = bin/file-analyzer

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_DIR)/libcore.a
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

obj/file-analyzer/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)