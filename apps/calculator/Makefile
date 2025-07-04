# Calculator app Makefile
include ../../build/common.mk

# Override CFLAGS to include required library headers
CFLAGS += -I$(ROOT_DIR)/libs/math_lib/include

# Specifics for this target
SRCS = src/main.c
OBJS = $(patsubst src/%.c,obj/calculator/%.o,$(SRCS))
TARGET = bin/calculator

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_DIR)/libmath.a
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

obj/calculator/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)