# net_lib Makefile
include ../../build/common.mk

# Override CFLAGS to include its own include directory
CFLAGS += -Iinclude

# Specifics for this target
SRCS = src/net_lib.c
OBJS = $(patsubst src/%.c,obj/net_lib/%.o,$(SRCS))
TARGET = lib/libnet.a

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

obj/net_lib/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)