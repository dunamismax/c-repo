#!/bin/bash

# Exit on error
set -e

# Build all libraries
echo "Building libraries..."
make -C libs/math_lib
make -C libs/net_lib
make -C core

# Build all applications
echo "Building applications..."
make -C apps/calculator
make -C apps/file-analyzer
make -C apps/contact-book
make -C apps/tiny-server

# Run tests
echo "Running tests..."
make -C tests/libs
./tests/libs/test_my_lib
make -C tests/core
./tests/core/test_core

echo "Build and test complete."
