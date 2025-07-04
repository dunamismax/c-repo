# Core tests Makefile
include ../../build/common.mk

# Override CFLAGS to include required library headers
CFLAGS += -I$(ROOT_DIR)/core/include

# Specifics for this target
SRCS = test_core.c
OBJS = $(patsubst %.c,obj/test_core/%.o,$(SRCS))
TARGET = test/test_core

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB_DIR)/libcore.a
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

obj/test_core/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)