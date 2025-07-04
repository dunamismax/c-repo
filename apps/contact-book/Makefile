# contact-book app Makefile
include ../../build/common.mk

# Override CFLAGS to include required library headers
CFLAGS += -I$(ROOT_DIR)/core/include

# Specifics for this target
SRCS = src/main.c
OBJS = $(patsubst src/%.c,obj/contact-book/%.o,$(SRCS))
TARGET = bin/contact-book

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_DIR)/libcore.a
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

obj/contact-book/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)