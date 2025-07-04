# tiny-server app Makefile
include ../../build/common.mk

# Override CFLAGS to include required library headers
CFLAGS += -I$(ROOT_DIR)/libs/net_lib/include

# Specifics for this target
SRCS = src/main.c
OBJS = $(patsubst src/%.c,obj/tiny-server/%.o,$(SRCS))
TARGET = bin/tiny-server

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_DIR)/libnet.a
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

obj/tiny-server/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)