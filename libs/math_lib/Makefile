# math_lib Makefile
include ../../build/common.mk

# Override CFLAGS to include its own include directory
CFLAGS += -Iinclude

# Specifics for this target
SRCS = src/math_lib.c
OBJS = $(patsubst src/%.c,obj/math_lib/%.o,$(SRCS))
TARGET = lib/libmath.a

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

obj/math_lib/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)