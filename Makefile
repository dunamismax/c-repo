# Root Makefile

.PHONY: all clean build_libs build_apps build_tests run_tests

all:
	@mkdir -p build
	@$(MAKE) -C build -f ../Makefile.build

test: all
	@echo "Running tests..."
	@./build/test/test_core
	@./build/test/test_math_lib
	@./build/test/test_net_lib

clean:
	@rm -rf build

.PHONY: all clean test
