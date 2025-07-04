# Libs tests Makefile
include ../../build/common.mk

# Override CFLAGS to include required library headers
CFLAGS += -I$(ROOT_DIR)/libs/math_lib/include -I$(ROOT_DIR)/libs/net_lib/include

# Specifics for this target
TEST_MATH_SRCS = test_math_lib.c
TEST_MATH_OBJS = $(patsubst %.c,obj/test_libs/%.o,$(TEST_MATH_SRCS))
TEST_MATH_TARGET = test/test_math_lib

TEST_NET_SRCS = test_net_lib.c
TEST_NET_OBJS = $(patsubst %.c,obj/test_libs/%.o,$(TEST_NET_SRCS))
TEST_NET_TARGET = test/test_net_lib

all: $(TEST_MATH_TARGET) $(TEST_NET_TARGET)

$(TEST_MATH_TARGET): $(TEST_MATH_OBJS) $(LIB_DIR)/libmath.a
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_NET_TARGET): $(TEST_NET_OBJS) $(LIB_DIR)/libnet.a
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

obj/test_libs/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TEST_MATH_OBJS) $(TEST_NET_OBJS) $(TEST_MATH_TARGET) $(TEST_NET_TARGET)