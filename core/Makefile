# Core library Makefile
include ../build/common.mk

# Override CFLAGS to include its own include directory
CFLAGS += -Iinclude

# Specifics for this target
SRCS = src/data_structures.c src/utils.c
OBJS = $(patsubst src/%.c,obj/core/%.o,$(SRCS))
TARGET = lib/libcore.a

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

obj/core/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)